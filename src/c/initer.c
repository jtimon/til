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

static void collect_enum_variants(Expr *body, Vec *variant_names, Vec *variant_types, Bool *has_payloads) {
    *has_payloads = 0;
    for (U32 j = 0; j < body->children.count; j++) {
        Expr *field = Expr_child(body, &(USize){(USize)(j)});
        if (field->data.data.Decl.is_namespace) continue;
        { Str *_p = Str_clone(&field->data.data.Decl.name); Vec_push(variant_names, _p); }
        { Str *_p = Str_clone(&field->data.data.Decl.explicit_type); Vec_push(variant_types, _p); }
        if (field->data.data.Decl.explicit_type.count > 0) *has_payloads = 1;
    }
}

static void generate_enum_variant_constructors(Expr *body, Str *ename, I32 line, I32 col, Str *path, Vec *variant_names, Vec *variant_types, Bool has_payloads) {
    if (!has_payloads) {
        for (U32 j = 0; j < variant_names->count; j++) {
            Expr *lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
            char buf[16];
            snprintf(buf, sizeof(buf), "%d", j);
            lit->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = *(Str *)Vec_get(variant_names, &(USize){(USize)(j)});
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, lit);
            Expr_add_child(body, decl);
        }
        return;
    }

    for (U32 j = 0; j < variant_names->count; j++) {
        Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
        fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_ExtFunc};
        if (((Str *)Vec_get(variant_types, &(USize){(USize)(j)}))->count > 0) {
            fdef->data.data.FuncDef.nparam = 1;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"val", .count = 3, .cap = CAP_LIT};
              _p->ptype = *(Str *)Vec_get(variant_types, &(USize){(USize)(j)});
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
        } else {
            fdef->data.data.FuncDef.nparam = 0;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
        }
        { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
        fdef->data.data.FuncDef.return_type = *ename;
        fdef->data.data.FuncDef.variadic_index = -1;
        fdef->data.data.FuncDef.kwargs_index = -1;
        Expr_add_child(fdef, Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path));
        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        decl->data.data.Decl.name = *(Str *)Vec_get(variant_names, &(USize){(USize)(j)});
        decl->data.data.Decl.is_namespace = true;
        Expr_add_child(decl, fdef);
        Expr_add_child(body, decl);
    }
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

        // Auto-generate is := func(self: E, other: E) returns Bool { return is(self, other) }
        if (!has_is) {
            Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            Expr *is_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            is_id->data.data.Ident = (Str){.c_str = (U8*)"is", .count = 2, .cap = CAP_LIT};
            Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
            Expr *other_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            other_id->data.data.Ident = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
            Expr *is_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(is_call, is_id);
            Expr_add_child(is_call, self_id);
            Expr_add_child(is_call, other_id);
            Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
            Expr_add_child(ret, is_call);
            Expr_add_child(func_body, ret);

            Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
            fdef->data.data.FuncDef.nparam = 2;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            fdef->data.data.FuncDef.return_type = (Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT};
            fdef->data.data.FuncDef.variadic_index = -1;
            fdef->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fdef, func_body);

            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = (Str){.c_str = (U8*)"is", .count = 2, .cap = CAP_LIT};
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fdef);
            Expr_add_child(body, decl);
        }

        // Auto-generate eq := func(self: E, other: E) returns Bool { if-chain }
        // Uses is_variant() for all variants, get_payload().eq() for payloads
        if (!has_eq) {
            Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            for (U32 j = 0; j < variant_names.count; j++) {
                // Build is_variant(self, E.Vj) call
                Str *vn = (Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                Expr *iv1 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                iv1->data.data.Ident = (Str){.c_str = (U8*)"is_variant", .count = 10, .cap = CAP_LIT};
                Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                Expr *et1 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                et1->data.data.Ident = *ename;
                Expr *vr1 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                vr1->data.data.FieldAccess = *vn;
                Expr_add_child(vr1, et1);
                Expr *is_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                Expr_add_child(is_call, iv1);
                Expr_add_child(is_call, self_id);
                Expr_add_child(is_call, vr1);

                Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

                if (((Str *)Vec_get(&variant_types, &(USize){(USize)(j)}))->count > 0) {
                    Str *vtype = (Str *)Vec_get(&variant_types, &(USize){(USize)(j)});
                    Bool is_funcsig = type_from_name_init(vtype, scope)->tag == TilType_TAG_FuncPtr;

                    // Payload variant:
                    //   if is_variant(other, E.Vj).not() { return false }
                    //   FuncSig: return true (tag-only eq)
                    //   Other:   ref _sp = get_payload(self); ref _op = get_payload(other); return _sp.eq(_op)
                    Expr *iv2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    iv2->data.data.Ident = (Str){.c_str = (U8*)"is_variant", .count = 10, .cap = CAP_LIT};
                    Expr *other_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    other_id->data.data.Ident = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
                    Expr *et2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    et2->data.data.Ident = *ename;
                    Expr *vr2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    vr2->data.data.FieldAccess = *vn;
                    Expr_add_child(vr2, et2);
                    Expr *is_call2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(is_call2, iv2);
                    Expr_add_child(is_call2, other_id);
                    Expr_add_child(is_call2, vr2);
                    Expr *not_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    not_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"not", .count = 3, .cap = CAP_LIT};
                    Expr_add_child(not_acc, is_call2);
                    Expr *not_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(not_call, not_acc);

                    Expr *ret_false = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                    Expr *false_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
                    false_lit->data.data.LiteralBool = 0;
                    Expr_add_child(ret_false, false_lit);
                    Expr *guard_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                    Expr_add_child(guard_body, ret_false);
                    Expr *guard_if = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                    Expr_add_child(guard_if, not_call);
                    Expr_add_child(guard_if, guard_body);
                    Expr_add_child(then_body, guard_if);

                    if (is_funcsig) {
                        // FuncSig payload: tag-only equality (return true)
                        Expr *ret_true = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr *true_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
                        true_lit->data.data.LiteralBool = 1;
                        Expr_add_child(ret_true, true_lit);
                        Expr_add_child(then_body, ret_true);
                    } else {
                        // ref _sp : PayloadType = get_payload(self)
                        // ref _op : PayloadType = get_payload(other)
                        // return _sp.eq(_op)
                        Str *vtype = (Str *)Vec_get(&variant_types, &(USize){(USize)(j)});

                        Expr *gp1 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        gp1->data.data.Ident = (Str){.c_str = (U8*)"get_payload", .count = 11, .cap = CAP_LIT};
                        Expr *self2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        self2->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                        Expr *gc1 = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(gc1, gp1); Expr_add_child(gc1, self2);
                        Expr *sd1 = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                        sd1->data.data.Decl.name = (Str){.c_str = (U8*)"_sp", .count = 3, .cap = CAP_LIT};
                        sd1->data.data.Decl.explicit_type = *vtype;
                        sd1->data.data.Decl.is_ref = true;
                        Expr_add_child(sd1, gc1);
                        Expr_add_child(then_body, sd1);

                        Expr *gp2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        gp2->data.data.Ident = (Str){.c_str = (U8*)"get_payload", .count = 11, .cap = CAP_LIT};
                        Expr *other2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        other2->data.data.Ident = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
                        Expr *gc2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(gc2, gp2); Expr_add_child(gc2, other2);
                        Expr *sd2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                        sd2->data.data.Decl.name = (Str){.c_str = (U8*)"_op", .count = 3, .cap = CAP_LIT};
                        sd2->data.data.Decl.explicit_type = *vtype;
                        sd2->data.data.Decl.is_ref = true;
                        Expr_add_child(sd2, gc2);
                        Expr_add_child(then_body, sd2);

                        Expr *sp_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        sp_id->data.data.Ident = (Str){.c_str = (U8*)"_sp", .count = 3, .cap = CAP_LIT};
                        Expr *eq_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        eq_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
                        Expr_add_child(eq_acc, sp_id);
                        Expr *op_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        op_id->data.data.Ident = (Str){.c_str = (U8*)"_op", .count = 3, .cap = CAP_LIT};
                        Expr *eq_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(eq_call, eq_acc);
                        Expr_add_child(eq_call, op_id);

                        Expr *ret_eq = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr_add_child(ret_eq, eq_call);
                        Expr_add_child(then_body, ret_eq);
                    }
                } else {
                    // No-payload variant: return is_variant(other, E.Vj)
                    Expr *iv3 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    iv3->data.data.Ident = (Str){.c_str = (U8*)"is_variant", .count = 10, .cap = CAP_LIT};
                    Expr *other_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    other_id->data.data.Ident = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
                    Expr *et3 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    et3->data.data.Ident = *ename;
                    Expr *vr3 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    vr3->data.data.FieldAccess = *vn;
                    Expr_add_child(vr3, et3);
                    Expr *is_call3 = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(is_call3, iv3);
                    Expr_add_child(is_call3, other_id);
                    Expr_add_child(is_call3, vr3);
                    Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                    Expr_add_child(ret, is_call3);
                    Expr_add_child(then_body, ret);
                }

                Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                Expr_add_child(if_node, is_call);
                Expr_add_child(if_node, then_body);
                Expr_add_child(func_body, if_node);
            }
            // return false
            Expr *ret_false = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
            Expr *false_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
            false_lit->data.data.LiteralBool = 0;
            Expr_add_child(ret_false, false_lit);
            Expr_add_child(func_body, ret_false);

            Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
            fdef->data.data.FuncDef.nparam = 2;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"other", .count = 5, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            fdef->data.data.FuncDef.return_type = (Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT};
            fdef->data.data.FuncDef.variadic_index = -1;
            fdef->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fdef, func_body);

            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fdef);
            Expr_add_child(body, decl);
        }

        // Auto-generate clone := func(self: E) returns E { if-chain }
        // Payload: if self.is_V() { return E.V(self.get_V()) } ... return E.Vn()
        // Simple:  if self.eq(E.V()) { return E.V() } ... return E.Vn()
        if (!has_clone) {
            Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            for (U32 j = 0; j < variant_names.count; j++) {
                // Build variant expression: E.V(self.get_V()) for payload, E.V for no-payload
                Expr *ename_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                ename_id->data.data.Ident = *ename;
                Expr *ctor_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                ctor_acc->data.data.FieldAccess = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                Expr_add_child(ctor_acc, ename_id);

                Expr *ctor_expr;
                Expr *pd = NULL;
                if (((Str *)Vec_get(&variant_types, &(USize){(USize)(j)}))->count > 0) {
                    // Payload variant: ref _pN : Type = get_payload(self); return E.V(_pN)
                    // pd is added to then_body below, not func_body
                    Str *vtype = (Str *)Vec_get(&variant_types, &(USize){(USize)(j)});
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
                    // No-payload variant: bare E.V (auto-called at runtime)
                    ctor_expr = ctor_acc;
                }

                Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                Expr_add_child(ret, ctor_expr);

                if (j < variant_names.count - 1) {
                    // Condition: payload uses is_V(), simple uses eq(E.V())
                    Expr *cond;
                    if (has_payloads) {
                        // is_variant(self, E.V)
                        Str *cvn = (Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
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
                        // self.eq(E.V) — bare field access as eq arg
                        Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                        Expr *eq_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        eq_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
                        Expr_add_child(eq_acc, self_id);

                        Expr *en2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        en2->data.data.Ident = *ename;
                        Expr *va2 = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        va2->data.data.FieldAccess = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
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
                    // Last variant: bare return (add pd for payload variants)
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

        // Auto-generate delete for all enums (same pattern):
        // delete := func(own self: E, call_free: Bool = true) {
        //     if call_free { free(own self) }
        // }
        // free() builtin handles payload cleanup for Value_TAG_Enum
        if (!has_delete) {
            Expr *proc_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
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

            Expr *default_true = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
            default_true->data.data.LiteralBool = 1;
            Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            // Note: is_core NOT set — auto-generated delete goes to per-module
            // file (same as clone), not to main file
            fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
            fdef->data.data.FuncDef.nparam = 2;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *ename;
              _p->is_own = true;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT};
              _p->ptype = (Str){.c_str = (U8*)"Bool", .count = 4, .cap = CAP_LIT};
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            { Str *_k = Str_clone(&(Str){.c_str = (U8*)"call_free", .count = 9, .cap = CAP_LIT}); Expr *_v = Expr_clone(default_true); Map_set(&fdef->data.data.FuncDef.param_defaults, _k, _v); }
            fdef->data.data.FuncDef.return_type = (Str){0};
            fdef->data.data.FuncDef.variadic_index = -1;
            fdef->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fdef, proc_body);
            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = (Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT};
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fdef);
            Expr_add_child(body, decl);
        }

        // Auto-generate to_str := func(self: E) returns Str { if-chain }
        if (!has_to_str) {
            Expr *func_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
            for (U32 j = 0; j < variant_names.count; j++) {
                if (has_payloads) {
                    // Payload enum to_str: if is_variant(self, E.V) { ... }
                    Str *tvn = (Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                    Expr *tiv = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    tiv->data.data.Ident = (Str){.c_str = (U8*)"is_variant", .count = 10, .cap = CAP_LIT};
                    Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                    Expr *tet = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    tet->data.data.Ident = *ename;
                    Expr *tvr = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    tvr->data.data.FieldAccess = *tvn;
                    Expr_add_child(tvr, tet);
                    Expr *is_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(is_call, tiv);
                    Expr_add_child(is_call, self_id);
                    Expr_add_child(is_call, tvr);

                    Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                    Str *vtype = (Str *)Vec_get(&variant_types, &(USize){(USize)(j)});
                    if (vtype && (*vtype).count > 0 && type_from_name_init(vtype, scope)->tag == TilType_TAG_FuncPtr) {
                        // FuncSig payload: return "Variant(func)"
                        char buf[256];
                        snprintf(buf, sizeof(buf), "%s(func)", ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                        Expr *ret_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                        ret_str->data.data.LiteralStr = *Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});
                        Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr_add_child(ret, ret_str);
                        Expr_add_child(then_body, ret);
                    } else if (vtype->count > 0) {
                        // ref _pN : Type = get_payload(self); return format("V(", _pN.to_str(), ")")
                        char pn_buf[128];
                        snprintf(pn_buf, sizeof(pn_buf), "_p_%s_%u", vtype->c_str, j);
                        Str pn = *Str_clone(&(Str){.c_str = (U8*)(pn_buf), .count = (U64)strlen((const char*)(pn_buf)), .cap = CAP_VIEW});
                        Expr *gp = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        gp->data.data.Ident = (Str){.c_str = (U8*)"get_payload", .count = 11, .cap = CAP_LIT};
                        Expr *self2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        self2->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                        Expr *gc = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(gc, gp); Expr_add_child(gc, self2);
                        Expr *pd = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                        pd->data.data.Decl.name = pn;
                        pd->data.data.Decl.explicit_type = *vtype;
                        pd->data.data.Decl.is_ref = true;
                        Expr_add_child(pd, gc);
                        Expr_add_child(then_body, pd);

                        Expr *fmt_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr *fmt_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        fmt_id->data.data.Ident = (Str){.c_str = (U8*)"format", .count = 6, .cap = CAP_LIT};
                        Expr_add_child(fmt_call, fmt_id);

                        char prefix_buf[256];
                        snprintf(prefix_buf, sizeof(prefix_buf), "%s(", ((Str *)Vec_get(&variant_names, &(USize){(USize)(j)}))->c_str);
                        Expr *prefix = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                        prefix->data.data.LiteralStr = *Str_clone(&(Str){.c_str = (U8*)(prefix_buf), .count = (U64)strlen((const char*)(prefix_buf)), .cap = CAP_VIEW});
                        Expr_add_child(fmt_call, prefix);

                        Expr *p_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                        p_id->data.data.Ident = pn;
                        Expr *tostr_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                        tostr_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"to_str", .count = 6, .cap = CAP_LIT};
                        Expr_add_child(tostr_acc, p_id);
                        Expr *tostr_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                        Expr_add_child(tostr_call, tostr_acc);
                        Expr_add_child(fmt_call, tostr_call);

                        Expr *suffix = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                        suffix->data.data.LiteralStr = (Str){.c_str = (U8*)")", .count = 1, .cap = CAP_LIT};
                        Expr_add_child(fmt_call, suffix);

                        Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr_add_child(ret, fmt_call);
                        Expr_add_child(then_body, ret);
                    } else {
                        // return "VariantName"
                        Expr *ret_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                        ret_str->data.data.LiteralStr = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                        Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                        Expr_add_child(ret, ret_str);
                        Expr_add_child(then_body, ret);
                    }

                    Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                    Expr_add_child(if_node, is_call);
                    Expr_add_child(if_node, then_body);
                    Expr_add_child(func_body, if_node);
                } else {
                    // Simple enum: if self.eq(EnumName.VariantName) { return "VariantName" }
                    Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    self_id->data.data.Ident = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
                    Expr *eq_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    eq_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
                    Expr_add_child(eq_acc, self_id);

                    // EnumName.VariantName (bare field access)
                    Expr *ename_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    ename_id->data.data.Ident = *ename;
                    Expr *var_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
                    var_acc->data.data.FieldAccess = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                    Expr_add_child(var_acc, ename_id);

                    Expr *eq_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                    Expr_add_child(eq_call, eq_acc);
                    Expr_add_child(eq_call, var_acc);

                    Expr *ret_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
                    ret_str->data.data.LiteralStr = *(Str *)Vec_get(&variant_names, &(USize){(USize)(j)});
                    Expr *ret = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
                    Expr_add_child(ret, ret_str);
                    Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                    Expr_add_child(then_body, ret);

                    Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                    Expr_add_child(if_node, eq_call);
                    Expr_add_child(if_node, then_body);
                    Expr_add_child(func_body, if_node);
                }
            }
            // return "unknown"
            Expr *unk = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
            unk->data.data.LiteralStr = (Str){.c_str = (U8*)"unknown", .count = 7, .cap = CAP_LIT};
            Expr *ret_unk = Expr_new(&(ExprData){.tag = ExprData_TAG_Return}, line, col, path);
            Expr_add_child(ret_unk, unk);
            Expr_add_child(func_body, ret_unk);

            Expr *fdef = Expr_new(&(ExprData){.tag = ExprData_TAG_FuncDef}, line, col, path);
            fdef->data.data.FuncDef.func_type = (FuncType){FuncType_TAG_Func};
            fdef->data.data.FuncDef.nparam = 1;
            { Vec *_v = Vec_new(&(Str){.c_str = (U8*)"Param", .count = 5, .cap = CAP_LIT}, &(USize){sizeof(Param)}); fdef->data.data.FuncDef.params = *_v; free(_v); }
            { Param *_p = calloc(1, sizeof(Param));
              _p->name = (Str){.c_str = (U8*)"self", .count = 4, .cap = CAP_LIT};
              _p->ptype = *ename;
              Vec_push(&fdef->data.data.FuncDef.params, _p); }
            { Map *_mp = Map_new(&(Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT}, &(USize){sizeof(Str)}, &(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fdef->data.data.FuncDef.param_defaults = *_mp; free(_mp); }
            fdef->data.data.FuncDef.return_type = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
            fdef->data.data.FuncDef.variadic_index = -1;
            fdef->data.data.FuncDef.kwargs_index = -1;
            Expr_add_child(fdef, func_body);

            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            decl->data.data.Decl.name = (Str){.c_str = (U8*)"to_str", .count = 6, .cap = CAP_LIT};
            decl->data.data.Decl.is_namespace = true;
            Expr_add_child(decl, fdef);
            Expr_add_child(body, decl);
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
