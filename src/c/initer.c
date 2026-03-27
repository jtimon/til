#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_enum_clone_method(Expr *body, Str *ename, I32 line, I32 col, Str *path, Vec *variant_names, Vec *variant_types, Bool has_payloads) {
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

void generate_enum_clone_method_for_body(Expr *body, Str *ename, I32 line, I32 col, Str *path) {
    Vec variant_names; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str)}); variant_names = *_vp; free(_vp); }
    Vec variant_types; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Str)}); variant_types = *_vp; free(_vp); }
    Bool has_payloads = 0;
    collect_enum_variants(body, &variant_names, &variant_types, &has_payloads);
    generate_enum_clone_method(body, ename, line, col, path, &variant_names, &variant_types, has_payloads);
    Vec_delete(&variant_names, &(Bool){0});
    Vec_delete(&variant_types, &(Bool){0});
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
