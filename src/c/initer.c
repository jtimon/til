#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void generate_missing_struct_clones(Expr *program, TypeScope *scope) {
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_StructDef) continue;

        Str *sname = &stmt->data.data.Decl.name;

        // Skip meta-types and core ext_structs (C side provides clone)
        if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0) ||
            (sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0)) continue;

        Expr *sdef = Expr_child(stmt, &(USize){(USize)(0)});
        if (sdef->is_ext && stmt->is_core) continue;

        Expr *body = Expr_child(sdef, &(USize){(USize)(0)}); // ExprData_TAG_Body

        // Check if clone already exists in namespace
        Bool has_clone = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.tag == ExprData_TAG_Decl && field->data.data.Decl.is_namespace &&
                (field->data.data.Decl.name.count == 5 && memcmp(field->data.data.Decl.name.c_str, "clone", 5) == 0)) {
                has_clone = 1;
                break;
            }
        }
        if (has_clone) continue;

        // Collect instance field names and ref/funcptr flags
        Vec field_names; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); field_names = *_vp; free(_vp); }
        Vec field_refs; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(I32)}); field_refs = *_vp; free(_vp); }
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.tag == ExprData_TAG_Decl && !field->data.data.Decl.is_namespace) {
                { Str **_p = malloc(sizeof(Str *)); *_p = &field->data.data.Decl.name; Vec_push(&field_names, _p); }
                I32 ref_flag = field->data.data.Decl.is_ref ? 1 : 0;
                // FuncSig-typed fields are just pointers — treat like ref for clone (no .clone())
                if (!ref_flag && field->data.data.Decl.explicit_type.count > 0 &&
                    type_from_name_init(&field->data.data.Decl.explicit_type, scope)->tag == TilType_TAG_FuncPtr)
                    ref_flag = 1;
                { I32 *_p = malloc(sizeof(I32)); *_p = ref_flag; Vec_push(&field_refs, _p); }
            }
        }

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = &stmt->path;
        Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

        if (field_names.count == 0) {
            // No instance fields: return Type()
            Expr *ctor = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr *ctor_name = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            ctor_name->data.data.Ident = *sname;
            Expr_add_child(ctor, ctor_name);

            Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
            Expr_add_child(ret, ctor);
            Expr_add_child(func_body, ret);
        } else {
            // With fields: return StructName(f1=self.f1.clone(), ...)
            Expr *ctor = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr *ctor_name = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            ctor_name->data.data.Ident = *sname;
            Expr_add_child(ctor, ctor_name);

            for (U32 j = 0; j < field_names.count; j++) {
                Str *fname = *(Str **)Vec_get(&field_names, &(USize){(USize)(j)});
                I32 fref = *(I32 *)Vec_get(&field_refs, &(USize){(USize)(j)});
                // self.field_name
                Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                Expr *field_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                field_acc->data.data.FieldAccess = *fname;
                Expr_add_child(field_acc, self_id);

                Expr *val_expr;
                if (fref) {
                    // ref field: copy pointer, don't clone
                    val_expr = field_acc;
                } else {
                    // self.field_name.clone()
                    Expr *clone_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    clone_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"clone", .count = 5, .cap = CAP_LIT};
                    Expr_add_child(clone_acc, field_acc);
                    Expr *clone_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(clone_call, clone_acc);
                    val_expr = clone_call;
                }

                // Named arg: field_name=value
                Expr *named = Expr_new(&(ExprData){.tag = ExprData_TAG_NamedArg}, line, col, path);
                named->data.data.NamedArg = *fname;
                Expr_add_child(named, val_expr);
                Expr_add_child(ctor, named);
            }

            Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
            Expr_add_child(ret, ctor);
            Expr_add_child(func_body, ret);
        }

        // func def
        Expr *func_def = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
        func_def->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
        func_def->data.data.FuncDef.nparam = 1;
        { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); func_def->data.data.FuncDef.params = *_v; free(_v); }
        { Param *_p = calloc(1, sizeof(Param));
          _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
          _p->ptype = *sname;
          Vec_push(&func_def->data.data.FuncDef.params, _p); }
        { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); func_def->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
        func_def->data.data.FuncDef.return_type = *sname;
        func_def->data.data.FuncDef.variadic_index = -1;
        func_def->data.data.FuncDef.kwargs_index = -1;
        Expr_add_child(func_def, func_body);

        // clone := func(...)  (namespace decl)
        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        decl->data.data.Decl.name = (Str){.c_str = (U8*)"clone", .count = 5, .cap = CAP_LIT};
        decl->data.data.Decl.is_namespace = true;
        decl->data.data.Decl.is_mut = false;
        decl->data.data.Decl.explicit_type = (Str){0};
        Expr_add_child(decl, func_def);

        // Add to struct body
        Expr_add_child(body, decl);
        Vec_delete(&field_names, &(Bool){0});
        Vec_delete(&field_refs, &(Bool){0});
    }

}

static void generate_missing_struct_deletes(Expr *program, TypeScope *scope) {
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_StructDef) continue;

        Str *sname = &stmt->data.data.Decl.name;

        // Skip meta-types and core ext_structs (C side provides delete)
        if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0) ||
            (sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0)) continue;

        Expr *sdef = Expr_child(stmt, &(USize){(USize)(0)});
        if (sdef->is_ext && stmt->is_core) continue;

        Expr *body = Expr_child(sdef, &(USize){(USize)(0)}); // ExprData_TAG_Body

        // Check if delete already exists in namespace
        Bool has_delete = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.tag == ExprData_TAG_Decl && field->data.data.Decl.is_namespace &&
                (field->data.data.Decl.name.count == 6 && memcmp(field->data.data.Decl.name.c_str, "delete", 6) == 0)) {
                has_delete = 1;
                break;
            }
        }
        if (has_delete) continue;

        // Collect instance field names and own flags (skip ref and func ptr fields)
        Vec field_names; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str *)}); field_names = *_vp; free(_vp); }
        Vec field_owns; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(I32)}); field_owns = *_vp; free(_vp); }
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *field = Expr_child(body, &(USize){(USize)(j)});
            if (field->data.tag == ExprData_TAG_Decl && !field->data.data.Decl.is_namespace &&
                !field->data.data.Decl.is_ref) {
                // Skip FuncSig-typed fields — func ptrs don't need delete
                if ((field->data.data.Decl.explicit_type).count > 0 &&
                    type_from_name_init(&field->data.data.Decl.explicit_type, scope)->tag == TilType_TAG_FuncPtr)
                    continue;
                { Str **_p = malloc(sizeof(Str *)); *_p = &field->data.data.Decl.name; Vec_push(&field_names, _p); }
                { I32 *_p = malloc(sizeof(I32)); *_p = field->data.data.Decl.is_own; Vec_push(&field_owns, _p); }
            }
        }

        I32 line = stmt->line;
        I32 col = stmt->col;
        Str *path = &stmt->path;
        Expr *proc_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

        // For each field: self.field.delete(call_free=<true for own, false for inline>)
        for (U32 j = 0; j < field_names.count; j++) {
            Str *fname = *(Str **)Vec_get(&field_names, &(USize){(USize)(j)});
            I32 fown = *(I32 *)Vec_get(&field_owns, &(USize){(USize)(j)});
            Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
            Expr *field_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            field_acc->data.data.FieldAccess = *fname;
            field_acc->is_own_arg = true; // delete takes own self
            Expr_add_child(field_acc, self_id);

            Expr *del_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            del_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT};
            Expr_add_child(del_acc, field_acc);
            Expr *del_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(del_call, del_acc);

            // call_free=true for own fields (separate allocation), false for inline
            Expr *cf_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
            cf_lit->data.data.LiteralBool = fown;
            Expr_add_child(del_call, cf_lit);

            Expr_add_child(proc_body, del_call);
        }

        // if call_free { free(own self) }
        Expr *cond = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
        cond->data.data.Ident = (Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT};
        Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
        Expr *free_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
        Expr *free_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
        free_id->data.data.Ident = (Str){.c_str = (U8*)"free", .count = 4, .cap = CAP_LIT};
        Expr_add_child(free_call, free_id);
        Expr *self_arg = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
        self_arg->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
        self_arg->is_own_arg = true;
        Expr_add_child(free_call, self_arg);
        Expr_add_child(then_body, free_call);
        Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
        Expr_add_child(if_node, cond);
        Expr_add_child(if_node, then_body);
        Expr_add_child(proc_body, if_node);

        // func def: delete(own self: Type, call_free: Bool = true)
        Expr *default_true = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
        default_true->data.data.LiteralBool = 1;

        Expr *proc_def = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
        // Note: is_core NOT set — auto-generated delete goes to per-module
        // file (same as clone), not to main file
        proc_def->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
        proc_def->data.data.FuncDef.nparam = 2;
        { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); proc_def->data.data.FuncDef.params = *_v; free(_v); }
        { Param *_p = calloc(1, sizeof(Param));
          _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
          _p->ptype = *sname;
          _p->is_own = true;
          Vec_push(&proc_def->data.data.FuncDef.params, _p); }
        { Param *_p = calloc(1, sizeof(Param));
          _p->name = (Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT};
          _p->ptype = (Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT};
          Vec_push(&proc_def->data.data.FuncDef.params, _p); }
        { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); proc_def->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
        { Str *_k = Str_clone(&(Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT}); Expr *_v = Expr_clone(default_true); Map_set(&proc_def->data.data.FuncDef.param_defaults, _k, _v); }
        proc_def->data.data.FuncDef.return_type = (Str){0};
        proc_def->data.data.FuncDef.variadic_index = -1;
        proc_def->data.data.FuncDef.kwargs_index = -1;
        Expr_add_child(proc_def, proc_body);

        // delete := func(...)  (namespace decl)
        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        decl->data.data.Decl.name = (Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT};
        decl->data.data.Decl.is_namespace = true;
        decl->data.data.Decl.is_mut = false;
        decl->data.data.Decl.explicit_type = (Str){0};
        Expr_add_child(decl, proc_def);

        // Add to struct body
        Expr_add_child(body, decl);
        Vec_delete(&field_names, &(Bool){0});
        Vec_delete(&field_owns, &(Bool){0});
    }

}

static void generate_enum_clone_method(Expr *body, Str *ename, I32 line, I32 col, Str *path, Vec *variant_names, Vec *variant_types, Bool has_payloads) {
    Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
    for (U32 j = 0; j < variant_names->count; j++) {
        Expr *ename_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
        ename_id->data.data.Ident = *ename;
        Expr *ctor_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
        ctor_acc->data.data.FieldAccess = *(Str *)Vec_get(variant_names, &(USize){(USize)(j)});
        Expr_add_child(ctor_acc, ename_id);

        Expr *ctor_expr;
        Expr *pd = NULL;
        if (((Str *)Vec_get(variant_types, &(USize){(USize)(j)}))->count > 0) {
            Str *vtype = (Str *)Vec_get(variant_types, &(USize){(USize)(j)});
            char pn_buf[128];
            snprintf(pn_buf, sizeof(pn_buf), "_p_%s_%u", vtype->c_str, j);
            Str pn = *Str_clone(&(Str){.c_str = (U8*)(pn_buf), .count = (U64)strlen((const char*)(pn_buf)), .cap = CAP_VIEW});
            Expr *gp = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            gp->data.data.Ident = (Str){.c_str = (U8*)"get_payload", .count = 11, .cap = CAP_LIT};
            Expr *self_g = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_g->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
            Expr *gc = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(gc, gp); Expr_add_child(gc, self_g);
            pd = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            pd->data.data.Decl.name = pn;
            pd->data.data.Decl.explicit_type = *vtype;
            pd->data.data.Decl.is_ref = true;
            Expr_add_child(pd, gc);
            Expr *ctor_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(ctor_call, ctor_acc);
            Expr *p_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            p_id->data.data.Ident = pn;
            Expr_add_child(ctor_call, p_id);
            ctor_expr = ctor_call;
        } else {
            ctor_expr = ctor_acc;
        }

        Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
        Expr_add_child(ret, ctor_expr);

        if (j < variant_names->count - 1) {
            Expr *cond;
            if (has_payloads) {
                Str *cvn = (Str *)Vec_get(variant_names, &(USize){(USize)(j)});
                Expr *civ = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                civ->data.data.Ident = (Str){.c_str = (U8*)"is_variant", .count = 10, .cap = CAP_LIT};
                Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                Expr *cet = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                cet->data.data.Ident = *ename;
                Expr *cvr = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                cvr->data.data.FieldAccess = *cvn;
                Expr_add_child(cvr, cet);
                cond = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                Expr_add_child(cond, civ);
                Expr_add_child(cond, self_id);
                Expr_add_child(cond, cvr);
            } else {
                Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                Expr *eq_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                eq_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
                Expr_add_child(eq_acc, self_id);

                Expr *en2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                en2->data.data.Ident = *ename;
                Expr *va2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                va2->data.data.FieldAccess = *(Str *)Vec_get(variant_names, &(USize){(USize)(j)});
                Expr_add_child(va2, en2);

                cond = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                Expr_add_child(cond, eq_acc);
                Expr_add_child(cond, va2);
            }

            Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            if (pd) Expr_add_child(then_body, pd);
            Expr_add_child(then_body, ret);

            Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
            Expr_add_child(if_node, cond);
            Expr_add_child(if_node, then_body);
            Expr_add_child(func_body, if_node);
        } else {
            if (pd) Expr_add_child(func_body, pd);
            Expr_add_child(func_body, ret);
        }
    }

    Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
    fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
    fdef->data.data.FuncDef.nparam = 1;
    { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
    { Param *_p = calloc(1, sizeof(Param));
      _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
      _p->ptype = *ename;
      Vec_push(&fdef->data.data.FuncDef.params, _p); }
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
    fdef->data.data.FuncDef.return_type = *ename;
    fdef->data.data.FuncDef.variadic_index = -1;
    fdef->data.data.FuncDef.kwargs_index = -1;
    Expr_add_child(fdef, func_body);

    Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
    decl->data.data.Decl.name = (Str){.c_str = (U8*)"clone", .count = 5, .cap = CAP_LIT};
    decl->data.data.Decl.is_namespace = true;
    Expr_add_child(decl, fdef);
    Expr_add_child(body, decl);
}

static I32 register_enums_and_generate_methods(Expr *program, TypeScope *scope) {
    I32 errors = 0;
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_EnumDef) continue;

        Str *ename = &stmt->data.data.Decl.name;
        I32 line = stmt->line, col = stmt->col;
        Str *path = &stmt->path;

        I32 reg_errors = register_enum_definition(stmt, scope);
        errors += reg_errors;
        if (reg_errors > 0) continue;

        Expr *body = Expr_child(Expr_child(stmt, &(USize){(USize)(0)}), &(USize){(USize)(0)});

        Vec variant_names; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str)}); variant_names = *_vp; free(_vp); }
        Vec variant_types; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str)}); variant_types = *_vp; free(_vp); }
        Bool has_payloads = 0;
        collect_enum_variants(body, &variant_names, &variant_types, &has_payloads);
        generate_enum_variant_constructors(body, ename, line, col, path, &variant_names, &variant_types, has_payloads);

        // Check existing methods
        Bool has_is = 0, has_eq = 0, has_clone = 0, has_delete = 0, has_to_str = 0;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *f = Expr_child(body, &(USize){(USize)(j)});
            if (f->data.tag != ExprData_TAG_Decl || !f->data.data.Decl.is_namespace) continue;
            if (f->children.count == 0 || Expr_child(f, &(USize){(USize)(0)})->data.tag != ExprData_TAG_FuncDef) continue;
            if ((f->data.data.Decl.name.count == 2 && memcmp(f->data.data.Decl.name.c_str, "is", 2) == 0)) has_is = 1;
            if ((f->data.data.Decl.name.count == 2 && memcmp(f->data.data.Decl.name.c_str, "eq", 2) == 0)) has_eq = 1;
            if ((f->data.data.Decl.name.count == 5 && memcmp(f->data.data.Decl.name.c_str, "clone", 5) == 0)) has_clone = 1;
            if ((f->data.data.Decl.name.count == 6 && memcmp(f->data.data.Decl.name.c_str, "delete", 6) == 0)) has_delete = 1;
            if ((f->data.data.Decl.name.count == 6 && memcmp(f->data.data.Decl.name.c_str, "to_str", 6) == 0)) has_to_str = 1;
        }

        if (!has_is) {
            generate_enum_is_method(body, ename, line, col, path);
        }

        if (!has_eq) {
            generate_enum_eq_method(body, ename, line, col, path, &variant_names, &variant_types, scope);
        }

        if (!has_clone) {
            generate_enum_clone_method(body, ename, line, col, path, &variant_names, &variant_types, has_payloads);
        }

        // Auto-generate delete for all enums (same pattern):
        // delete := func(own self: E, call_free: Bool = true) {
        //     if call_free { free(own self) }
        // }
        // free() builtin handles payload cleanup for Value_TAG_Enum
        if (!has_delete) {
            generate_enum_delete_method(body, ename, line, col, path);
        }

        if (!has_to_str) {
            generate_enum_to_str_method(body, ename, line, col, path, &variant_names, &variant_types, has_payloads, scope);
        }

        Vec_delete(&variant_names, &(Bool){0});
        Vec_delete(&variant_types, &(Bool){0});
    }
    return errors;
}

static Bool should_skip_size_generation(Expr *stmt, Expr *def) {
    Str *sname = &stmt->data.data.Decl.name;
    if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0) ||
        (sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0)) return 1;
    if (def->is_ext && stmt->is_core) return 1;
    return 0;
}

static Bool has_namespace_size_method(Expr *body) {
    for (U32 j = 0; j < body->children.count; j++) {
        Expr *field = Expr_child(body, &(USize){(USize)(j)});
        if (field->data.tag == ExprData_TAG_Decl && field->data.data.Decl.is_namespace &&
            (field->data.data.Decl.name.count == 4 && memcmp(field->data.data.Decl.name.c_str, "size", 4) == 0)) {
            return 1;
        }
    }
    return 0;
}

static void add_size_method(Expr *stmt, Expr *body, I32 sz) {
    I32 line = stmt->line;
    I32 col = stmt->col;
    Str *path = &stmt->path;
    char sz_buf[16];
    snprintf(sz_buf, sizeof(sz_buf), "%d", sz);

    Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
    Expr *size_expr = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
    size_expr->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(sz_buf), .count = (U64)strlen((const char*)(sz_buf)), .cap = CAP_VIEW});
    Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
    Expr_add_child(ret, size_expr);
    Expr_add_child(func_body, ret);

    Expr *func_def = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
    func_def->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
    func_def->data.data.FuncDef.nparam = 0;
    { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); func_def->data.data.FuncDef.params = *_v; free(_v); }
    { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); func_def->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
    func_def->data.data.FuncDef.return_type = (Str){.c_str = (U8*)"USize", .count = 5, .cap = CAP_LIT};
    func_def->data.data.FuncDef.variadic_index = -1;
    func_def->data.data.FuncDef.kwargs_index = -1;
    Expr_add_child(func_def, func_body);

    Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
    decl->data.data.Decl.name = (Str){.c_str = (U8*)"size", .count = 4, .cap = CAP_LIT};
    decl->data.data.Decl.is_namespace = true;
    decl->data.data.Decl.is_mut = false;
    decl->data.data.Decl.explicit_type = (Str){0};
    Expr_add_child(decl, func_def);

    Expr_add_child(body, decl);
}

static void generate_enum_size_methods(Expr *program) {
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = Expr_child(program, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl) continue;
        Expr *def = Expr_child(stmt, &(USize){(USize)(0)});
        if (def->data.tag != ExprData_TAG_EnumDef) continue;
        if (should_skip_size_generation(stmt, def)) continue;

        Expr *body = Expr_child(def, &(USize){(USize)(0)});
        if (has_namespace_size_method(body)) continue;

        add_size_method(stmt, body, enum_has_payloads(def) ? 8 : 4);
    }
}

static void generate_size_methods(Expr *program, TypeScope *scope) {
    (void)scope;
    generate_struct_size_methods(program);
    generate_enum_size_methods(program);
}

static void generate_derived_methods(Expr *program, TypeScope *scope) {
    generate_cmp_derived_methods(program, scope);
    generate_unity_derived_methods(program, scope);
}

I32 init_declarations(Expr *program, TypeScope *scope) {
    I32 errors = 0;

    // Pass 1: register all struct definitions
    errors += register_struct_definitions(program, scope);

    // Pass 1.1: pre-register FuncSig type aliases (bodyless func/proc defs)
    // Needed before struct layout/clone/delete so FuncSig-typed struct fields are recognized
    register_funcsig_aliases(program, scope);

    // Pass 1.5: auto-generate clone methods for all structs
    generate_missing_struct_clones(program, scope);

    // Pass 1.7: auto-generate delete methods for all structs
    generate_missing_struct_deletes(program, scope);

    // Pass 1.8: register enum definitions, generate variants + methods
    errors += register_enums_and_generate_methods(program, scope);

    // Pass 1.85: register type aliases (Name := ExistingType where RHS is a known type name)
    // Must run after Pass 1 (structs), Pass 1.1 (FuncSigs), and Pass 1.8 (enums)
    register_type_aliases(program, scope);

    // Pass 1.9: compute flat struct layout (field offsets and sizes)
    // Must run BEFORE size method synthesis so total_struct_size is available
    compute_all_struct_layouts(program, scope);

    // Pass 1.92: auto-generate size methods for structs and enums
    // Uses total_struct_size computed above for correct values (includes alignment padding)
    generate_size_methods(program, scope);

    // Pass 1.95: auto-generate derived methods
    // From cmp: eq, neq, lt, gt, lte, gte (if missing)
    // From add+unity: inc (if missing). From sub+unity: dec (if missing)
    generate_derived_methods(program, scope);

    // Pass 2: register all func/proc definitions
    register_function_definitions(program, scope);

    // Pass 3: pre-register top-level value declarations so functions can
    // reference module globals before their declaration appears.
    register_top_level_values(program, scope);

    return errors;
}
