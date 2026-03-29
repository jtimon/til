#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LIT(s) (&(Str){.c_str=(U8 *)(s), .count=(U64)(sizeof(s) - 1), .cap=CAP_LIT})
#define STR_VIEW(s) (&(Str){.c_str=(U8 *)(s), .count=(U64)strlen((const char *)(s)), .cap=CAP_VIEW})

// --- Type inference/checking pass ---

static Expr *find_namespace_func(Expr *sdef, Str *method) {
        if (!sdef) return NULL;
        Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *field = Expr_child(body, &(USize){(USize)(i)});
            if (field->data.data.Decl.is_namespace &&
                Str_eq(&field->data.data.Decl.name, method) &&
                Expr_child(field, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef) {
                return Expr_child(field, &(USize){(USize)(0)});
            }
        }
        return NULL;
}

static Bool infer_func_ptr_field_call(TypeScope *scope, Expr *e, Expr *fa, Expr *obj, Expr *sdef, Str *method, I32 in_func) {
        if (!sdef || (obj->til_type.tag != TilType_TAG_Struct && obj->til_type.tag != TilType_TAG_Enum)) return false;
        Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
        for (U32 fi = 0; fi < body->children.count; fi++) {
            Expr *field = Expr_child(body, &(USize){(USize)(fi)});
            if (field->data.tag != ExprData_TAG_Decl || field->data.data.Decl.is_namespace) continue;
            if (!Str_eq(&field->data.data.Decl.name, method)) continue;
            if (field->data.data.Decl.explicit_type.count == 0) continue;
            ScopeFind *_sf_ftb = TypeScope_find(scope, &field->data.data.Decl.explicit_type);
            TypeBinding *ftb = _sf_ftb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ftb) : NULL;
            if (ftb && ftb->func_def && ftb->func_def->children.count == 0) {
                fa->til_type = (TilType){TilType_TAG_FuncPtr};
                fa->fn_sig = ftb->func_def;
                Expr *sig = ftb->func_def;
                U32 nargs = e->children.count - 1;
                if (nargs != sig->data.data.FuncDef.nparam) {
                    char buf2[128];
                    snprintf(buf2, sizeof(buf2), "function pointer field '%s' expects %u args, got %u",
                             method->c_str, sig->data.data.FuncDef.nparam, nargs);
                    type_error(e, STR_VIEW(buf2));
                }
                for (U32 ai = 0; ai < nargs && ai < sig->data.data.FuncDef.nparam; ai++) {
                    infer_expr(scope, Expr_child(e, &(USize){(USize)(ai + 1)}), in_func);
                }
                e->fn_sig = sig;
                e->data.data.FCall.fn_sig = sig;
                if (sig->data.data.FuncDef.return_type.count > 0) {
                    e->til_type = *type_from_name(&sig->data.data.FuncDef.return_type, scope);
                    if ((e->til_type.tag == TilType_TAG_Struct || e->til_type.tag == TilType_TAG_Enum))
                        e->struct_name = *Str_clone(&sig->data.data.FuncDef.return_type);
                } else {
                    e->til_type = (TilType){TilType_TAG_None};
                }
                return true;
            }
        }
        return false;
}

static Bool try_ufcs_rewrite(TypeScope *scope, Expr *e, Expr *fa, Expr *obj, Str *method, Str *type_name) {
        ScopeFind *_sf_top = TypeScope_find(scope, method);
        TypeBinding *top = _sf_top->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_top) : NULL;
        Bool ufcs_match = 0;
        if (top && top->func_def &&
            top->func_def->data.data.FuncDef.nparam > 0 &&
            ((Param*)Vec_get(&top->func_def->data.data.FuncDef.params, &(USize){(USize)(0)}))->ptype.count > 0) {
            Str *first_param = &((Param*)Vec_get(&top->func_def->data.data.FuncDef.params, &(USize){(USize)(0)}))->ptype;
            if (type_name && Str_eq(first_param, type_name)) {
                ufcs_match = 1;
            } else if (!type_name && obj->til_type.tag == TilType_TAG_Dynamic) {
                TilType pt = *type_from_name(first_param, scope);
                narrow_dynamic(obj, &pt, first_param);
                ufcs_match = 1;
            }
        }
        if (!ufcs_match) return false;
        Expr *fn_ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, fa->line, fa->col, &fa->path);
        fn_ident->data.data.Ident = *method;
        *(Expr*)Vec_get(&e->children, &(USize){(USize)(0)}) = *fn_ident;
        Expr *instance = obj;
        Expr dummy = {0};
        { Expr *_p = malloc(sizeof(Expr)); *_p = dummy; Vec_push(&e->children, _p); }
        {
            Expr *ch = (Expr *)e->children.data;
            memmove(&ch[2], &ch[1], (e->children.count - 2) * sizeof(Expr));
        }
        *(Expr*)Vec_get(&e->children, &(USize){(USize)(1)}) = *Expr_clone(instance);
        return true;
}

static Bool infer_field_access_fcall(TypeScope *scope, Expr *e, I32 in_func) {
        Expr *fa = Expr_child(e, &(USize){(USize)(0)});
        Expr *obj = Expr_child(fa, &(USize){(USize)(0)});
        Str *method = &fa->data.data.FieldAccess;
        infer_expr(scope, obj, in_func);

        ScopeFind *_sf_tb = (obj->data.tag == ExprData_TAG_Ident)
            ? TypeScope_find(scope, &obj->data.data.Ident) : NULL;
        TypeBinding *tb = (_sf_tb && _sf_tb->tag == ScopeFind_TAG_Found) ? (TypeBinding*)get_payload(_sf_tb) : NULL;
        Bool obj_is_type = (tb && tb->struct_def);

        Bool ufcs_desugared = 0;
        if (!obj_is_type) {
            Str *type_name = NULL;
            if (obj->til_type.tag >= TilType_TAG_I64 && obj->til_type.tag <= TilType_TAG_Bool)
                type_name = til_type_name_c(&obj->til_type);
            else if ((obj->til_type.tag == TilType_TAG_Struct || obj->til_type.tag == TilType_TAG_Enum) && obj->struct_name.count > 0)
                type_name = &obj->struct_name;

            Expr *sdef = type_name ? TypeScope_get_struct(scope, type_name) : NULL;
            Expr *ns_func = find_namespace_func(sdef, method);
            if (!ns_func) {
                if (try_ufcs_rewrite(scope, e, fa, obj, method, type_name)) {
                    return false;
                }
                if (infer_func_ptr_field_call(scope, e, fa, obj, sdef, method, in_func)) {
                    return true;
                }
                char buf[256];
                if (!type_name && obj->til_type.tag == TilType_TAG_Dynamic) {
                    snprintf(buf, sizeof(buf),
                             "cannot call method '%s' on Dynamic value; "
                             "use 'ref x : Type = ...' to declare with an explicit type first",
                             method->c_str);
                } else {
                    snprintf(buf, sizeof(buf), "no method '%s' for type '%s'",
                             (const char *)method->c_str, type_name ? (const char *)type_name->c_str : "unknown");
                }
                type_error(e, STR_VIEW(buf));
                e->til_type = (TilType){TilType_TAG_Unknown};
                return true;
            }
            ufcs_desugared = 1;
            Expr *instance = Expr_clone(obj);
            Expr *type_ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, obj->line, obj->col, &obj->path);
            type_ident->data.data.Ident = *type_name;
            *(Expr*)Vec_get(&fa->children, &(USize){(USize)(0)}) = *type_ident;
            Expr dummy = {0};
            { Expr *_p = malloc(sizeof(Expr)); *_p = dummy; Vec_push(&e->children, _p); }
            {
                Expr *ch = (Expr *)e->children.data;
                memmove(&ch[2], &ch[1], (e->children.count - 2) * sizeof(Expr));
            }
            *(Expr*)Vec_get(&e->children, &(USize){(USize)(1)}) = *instance;
            fa = Expr_child(e, &(USize){(USize)(0)});
            method = &fa->data.data.FieldAccess;
        }

        obj = Expr_child(fa, &(USize){(USize)(0)});
        if (obj->til_type.tag == TilType_TAG_Unknown) {
            infer_expr(scope, obj, in_func);
        }
        Expr *sdef = (obj->struct_name).count > 0 ? TypeScope_get_struct(scope, &obj->struct_name) : NULL;
        Expr *ns_func = find_namespace_func(sdef, method);
        if (!ns_func) {
            char buf[128];
            snprintf(buf, sizeof(buf), "no namespace function '%s'", method->c_str);
            type_error(e, STR_VIEW(buf));
            e->til_type = (TilType){TilType_TAG_Unknown};
            return true;
        }
        fa->is_ns_field = true;
        {
            U32 np = ns_func->data.data.FuncDef.nparam;
            Expr **new_args = calloc(np, sizeof(Expr *));
            U32 pos_idx = 0;
            Bool seen_named = 0;
            for (U32 i = 1; i < e->children.count; i++) {
                Expr *arg = Expr_child(e, &(USize){(USize)(i)});
                if (arg->data.tag == ExprData_TAG_NamedArg) {
                    seen_named = 1;
                    Str *aname = &arg->data.data.Ident;
                    I32 slot = -1;
                    for (U32 j = 0; j < np; j++) {
                        if (Str_eq(&((Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(j)}))->name, aname)) {
                            slot = j;
                            break;
                        }
                    }
                    if (slot < 0) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "no parameter '%s'", aname->c_str);
                        type_error(arg, STR_VIEW(buf));
                    } else if (new_args[slot]) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "duplicate argument for parameter '%s'", aname->c_str);
                        type_error(arg, STR_VIEW(buf));
                    } else {
                        new_args[slot] = Expr_clone(Expr_child(arg, &(USize){(USize)(0)}));
                    }
                } else {
                    if (seen_named) {
                        type_error(arg, STR_LIT("positional argument after named argument"));
                    }
                    if (pos_idx < np) {
                        new_args[pos_idx] = Expr_clone(arg);
                    }
                    pos_idx++;
                }
            }
            for (U32 i = 0; i < np; i++) {
                if (!new_args[i]) {
                    Str *_pn = &((Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(i)}))->name;
                    if (Map_has(&ns_func->data.data.FuncDef.param_defaults, _pn)) {
                        new_args[i] = Expr_clone((Expr*)Map_get(&ns_func->data.data.FuncDef.param_defaults, _pn));
                    } else {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "missing argument for parameter '%s'", _pn->c_str);
                        type_error(e, STR_VIEW(buf));
                    }
                }
            }
            if (pos_idx > np) {
                char buf[128];
                snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d", np, pos_idx);
                type_error(e, STR_VIEW(buf));
            }
            Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
            Expr *callee = Expr_child(e, &(USize){(USize)(0)});
            Vec_push(&new_ch, Expr_clone(callee));
            for (U32 i = 0; i < np; i++) {
                Vec_push(&new_ch, new_args[i]);
            }
            Vec_delete(&e->children, &(Bool){0});
            e->children = new_ch;
            free(new_args);
        }
        for (U32 i = 1; i < e->children.count; i++) {
            infer_expr(scope, Expr_child(e, &(USize){(USize)(i)}), in_func);
        }
        for (U32 i = 1; i < e->children.count && i - 1 < ns_func->data.data.FuncDef.nparam; i++) {
            Str *ptype = &((Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(i - 1)}))->ptype;
            if (ptype)
                narrow_dynamic(Expr_child(e, &(USize){(USize)(i)}), type_from_name(ptype, scope), ptype);
        }
        for (U32 i = 1; i < e->children.count && i - 1 < ns_func->data.data.FuncDef.nparam; i++) {
            Str *ptype_name = &((Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(i - 1)}))->ptype;
            if (!ptype_name) continue;
            Expr *arg = Expr_child(e, &(USize){(USize)(i)});
            if (arg->til_type.tag == TilType_TAG_Dynamic) continue;
            TilType ptype = *type_from_name(ptype_name, scope);
            if (ptype.tag == TilType_TAG_Dynamic) continue;
            if (arg->data.tag == ExprData_TAG_LiteralNum && is_numeric_type(&ptype)) {
                if (!literal_in_range(&arg->data.data.Ident, &ptype)) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "integer literal %s out of range for %s",
                             arg->data.data.Ident.c_str, til_type_name_c(&ptype)->c_str);
                    type_error(arg, STR_VIEW(buf));
                }
                arg->til_type = ptype;
                continue;
            }
            if (can_implicit_widen(&arg->til_type, &ptype) ||
                can_implicit_usize_coerce(&arg->til_type, &ptype, ptype_name)) {
                arg->til_type = ptype;
                continue;
            }
            if (arg->til_type.tag != ptype.tag) {
                char buf[256];
                snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                         ((Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(i - 1)}))->name.c_str,
                         ptype_name->c_str, til_type_name_c(&arg->til_type)->c_str);
                type_error(arg, STR_VIEW(buf));
            } else if ((ptype.tag == TilType_TAG_Struct || ptype.tag == TilType_TAG_Enum) &&
                       (arg->struct_name).count > 0 && !Str_eq(ptype_name, &arg->struct_name)) {
                char buf[256];
                snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                         ((Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(i - 1)}))->name.c_str,
                         ptype_name->c_str, arg->struct_name.c_str);
                type_error(arg, STR_VIEW(buf));
            }
        }
        if (ufcs_desugared && Expr_child(e, &(USize){(USize)(0)})->is_own_arg && e->children.count > 1) {
            Expr_child(e, &(USize){(USize)(1)})->is_own_arg = 1;
        }
        {
            U32 np = ns_func->data.data.FuncDef.nparam;
            if (ns_func->data.data.FuncDef.params.count > 0) {
                for (U32 i = 1; i < e->children.count && i - 1 < np; i++) {
                    Param *_pp = (Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(i - 1)});
                    Bool pown = _pp->is_own;
                    if (pown && !Expr_child(e, &(USize){(USize)(i)})->is_own_arg) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "argument for 'own' parameter '%s' must be marked 'own'",
                                 _pp->name.c_str);
                        type_error(Expr_child(e, &(USize){(USize)(i)}), STR_VIEW(buf));
                    } else if (!pown && Expr_child(e, &(USize){(USize)(i)})->is_own_arg) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                                 _pp->name.c_str);
                        type_error(Expr_child(e, &(USize){(USize)(i)}), STR_VIEW(buf));
                    }
                    if (pown && Expr_child(e, &(USize){(USize)(i)})->data.tag == ExprData_TAG_Ident) {
                        ScopeFind *_sf_ab = TypeScope_find(scope, &Expr_child(e, &(USize){(USize)(i)})->data.data.Ident);
                        TypeBinding *ab = _sf_ab->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ab) : NULL;
                        if (ab && ab->is_ref) type_error(Expr_child(e, &(USize){(USize)(i)}), STR_LIT("cannot pass ref variable to 'own' parameter; use .clone() to make an owned copy"));
                    }
                    if (pown && Expr_child(e, &(USize){(USize)(i)})->data.tag == ExprData_TAG_LiteralNull)
                        type_error(Expr_child(e, &(USize){(USize)(i)}), STR_LIT("cannot pass null to 'own' parameter"));
                    if (_pp->is_shallow && Expr_child(e, &(USize){(USize)(i)})->data.tag == ExprData_TAG_LiteralNull)
                        type_error(Expr_child(e, &(USize){(USize)(i)}), STR_LIT("cannot pass null to 'shallow' parameter"));
                }
            }
        }
        TilType rt = (TilType){TilType_TAG_None};
        if (ns_func->data.data.FuncDef.return_type.count > 0) {
            rt = *type_from_name(&ns_func->data.data.FuncDef.return_type, scope);
        }
        e->til_type = rt;
        if ((rt.tag == TilType_TAG_Struct || rt.tag == TilType_TAG_Enum) && (ns_func->data.data.FuncDef.return_type).count > 0) {
            e->struct_name = *Str_clone(&ns_func->data.data.FuncDef.return_type);
        }
        return true;
}

static Bool infer_struct_constructor_fcall(TypeScope *scope, Expr *e, Str *name, I32 in_func) {
        Expr *sdef = TypeScope_get_struct(scope, name);
        if (!sdef) return false;
        ScopeFind *_sf_sb = TypeScope_find(scope, name);
        TypeBinding *sb = _sf_sb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_sb) : NULL;
        if (sb && sb->is_builtin && !sb->is_ext) {
            char buf[128];
            snprintf(buf, sizeof(buf), "cannot instantiate builtin type '%s'", name->c_str);
            type_error(e, STR_VIEW(buf));
            e->til_type = (TilType){TilType_TAG_Unknown};
            return true;
        }
        Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
        U32 nfields = 0;
        for (U32 i = 0; i < body->children.count; i++) {
            if (!Expr_child(body, &(USize){(USize)(i)})->data.data.Decl.is_namespace) nfields++;
        }
        Expr **field_vals = calloc(nfields, sizeof(Expr *));
        I32 *field_idx = malloc(nfields * sizeof(I32));
        { I32 k = 0;
          for (U32 i = 0; i < body->children.count; i++) {
              if (!Expr_child(body, &(USize){(USize)(i)})->data.data.Decl.is_namespace) field_idx[k++] = i;
          }
        }
        for (U32 i = 1; i < e->children.count; i++) {
            Expr *arg = Expr_child(e, &(USize){(USize)(i)});
            if (arg->data.tag != ExprData_TAG_NamedArg) {
                type_error(arg, STR_LIT("struct instantiation requires named arguments"));
                continue;
            }
            Str *aname = &arg->data.data.Ident;
            I32 slot = -1;
            for (U32 j = 0; j < nfields; j++) {
                if (Str_eq(&Expr_child(body, &(USize){(USize)(field_idx[j])})->data.data.Decl.name, aname)) {
                    slot = j;
                    break;
                }
            }
            if (slot < 0) {
                char buf[128];
                snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'", name->c_str, aname->c_str);
                type_error(arg, STR_VIEW(buf));
            } else if (field_vals[slot]) {
                char buf[128];
                snprintf(buf, sizeof(buf), "duplicate argument for field '%s'", aname->c_str);
                type_error(arg, STR_VIEW(buf));
            } else {
                field_vals[slot] = Expr_clone(Expr_child(arg, &(USize){(USize)(0)}));
            }
        }
        for (U32 i = 0; i < nfields; i++) {
            if (!field_vals[i]) {
                field_vals[i] = Expr_clone(Expr_child(Expr_child(body, &(USize){(USize)(field_idx[i])}), &(USize){(USize)(0)}));
            }
        }
        Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
        Expr *callee = Expr_child(e, &(USize){(USize)(0)});
        Vec_push(&new_ch, Expr_clone(callee));
        for (U32 i = 0; i < nfields; i++) {
            Vec_push(&new_ch, field_vals[i]);
        }
        Vec_delete(&e->children, &(Bool){0});
        e->children = new_ch;
        free(field_vals);
        free(field_idx);
        for (U32 i = 1; i < e->children.count; i++) {
            if (Expr_child(e, &(USize){(USize)(i)})->til_type.tag == TilType_TAG_Unknown) {
                infer_expr(scope, Expr_child(e, &(USize){(USize)(i)}), in_func);
            }
        }
        { U32 fi = 0;
          for (U32 bi = 0; bi < body->children.count && fi < e->children.count - 1; bi++) {
            Expr *fld = Expr_child(body, &(USize){(USize)(bi)});
            if (fld->data.data.Decl.is_namespace) continue;
            I32 ai = fi + 1;
            fi++;
            if (fld->data.data.Decl.is_ref) continue;
            if (!fld->data.data.Decl.is_own && !type_ctor_consumes(&fld->til_type)) continue;
            Expr_child(e, &(USize){(USize)(ai)})->is_own_arg = 1;
          }
        }
        e->til_type = (TilType){TilType_TAG_Struct};
        e->struct_name = *Str_clone(resolve_type_alias(scope, name));
        return true;
}

static void desugar_user_func_fcall_args(Expr *e, Str *name, TypeBinding *callee_bind) {
        Expr *fdef = callee_bind->func_def;
        U32 nparam = fdef->data.data.FuncDef.nparam;
        I32 vi = fdef->data.data.FuncDef.variadic_index;
        I32 kwi = fdef->data.data.FuncDef.kwargs_index;
        U32 fixed_count = (vi >= 0) ? (U32)vi : nparam;
        Vec va_args; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); va_args = *_vp; free(_vp); }
        Vec kw_args; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); kw_args = *_vp; free(_vp); }
        Expr **new_args = calloc(nparam, sizeof(Expr *));
        U32 pos_idx = 0;
        Bool seen_named = 0;
        for (U32 i = 1; i < e->children.count; i++) {
            Expr *arg = Expr_child(e, &(USize){(USize)(i)});
            if (arg->data.tag == ExprData_TAG_NamedArg) {
                seen_named = 1;
                Str *aname = &arg->data.data.Ident;
                I32 slot = -1;
                for (U32 j = 0; j < nparam; j++) {
                    if ((I32)j == vi) continue;
                    if ((I32)j == kwi) continue;
                    if (Str_eq(&((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(j)}))->name, aname)) {
                        slot = j;
                        break;
                    }
                }
                if (slot < 0 && kwi >= 0) {
                    { Expr **_p = malloc(sizeof(Expr *)); *_p = arg; Vec_push(&kw_args, _p); }
                } else if (slot < 0) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' has no parameter '%s'", name->c_str, aname->c_str);
                    type_error(arg, STR_VIEW(buf));
                } else if (new_args[slot]) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "duplicate argument for parameter '%s'", aname->c_str);
                    type_error(arg, STR_VIEW(buf));
                } else {
                    new_args[slot] = Expr_clone(Expr_child(arg, &(USize){(USize)(0)}));
                }
            } else {
                if (seen_named) {
                    type_error(arg, STR_LIT("positional argument after named argument"));
                }
                if (vi >= 0 && pos_idx >= fixed_count) {
                    { Expr **_p = malloc(sizeof(Expr *)); *_p = arg; Vec_push(&va_args, _p); }
                } else if (pos_idx < nparam) {
                    new_args[pos_idx] = Expr_clone(arg);
                }
                pos_idx++;
            }
        }
        for (U32 i = 0; i < nparam; i++) {
            if ((I32)i == vi) continue;
            if ((I32)i == kwi) continue;
            if (!new_args[i]) {
                Str *_pn = &((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(i)}))->name;
                if (Map_has(&fdef->data.data.FuncDef.param_defaults, _pn)) {
                    new_args[i] = Expr_clone((Expr*)Map_get(&fdef->data.data.FuncDef.param_defaults, _pn));
                } else {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "missing argument for parameter '%s'", _pn->c_str);
                    type_error(e, STR_VIEW(buf));
                }
            }
        }
        U32 max_pos = nparam - (kwi >= 0 ? 1 : 0);
        if (vi < 0 && pos_idx > max_pos) {
            char buf[128];
            snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d", nparam, pos_idx);
            type_error(e, STR_VIEW(buf));
        }
        Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
        Expr *callee = Expr_child(e, &(USize){(USize)(0)});
        Vec_push(&new_ch, Expr_clone(callee));
        for (U32 i = 0; i < nparam; i++) {
            if ((I32)i == vi) {
                e->data.data.FCall.variadic_index = new_ch.count;
                for (U32 j = 0; j < va_args.count; j++) {
                    Expr *va = *(Expr **)Vec_get(&va_args, &(USize){(USize)(j)});
                    Vec_push(&new_ch, Expr_clone(va));
                }
                e->data.data.FCall.variadic_count = va_args.count;
            } else if ((I32)i == kwi) {
                e->data.data.FCall.kwargs_index = new_ch.count;
                for (U32 j = 0; j < kw_args.count; j++) {
                    Expr *kw = *(Expr **)Vec_get(&kw_args, &(USize){(USize)(j)});
                    Vec_push(&new_ch, Expr_clone(kw));
                }
                e->data.data.FCall.kwargs_count = kw_args.count;
            } else {
                Vec_push(&new_ch, new_args[i]);
            }
        }
        Vec_delete(&e->children, &(Bool){0});
        e->children = new_ch;
        free(new_args);
        Vec_delete(&va_args, &(Bool){0});
        Vec_delete(&kw_args, &(Bool){0});
}

static void infer_and_validate_fcall_args(TypeScope *scope, Expr *e, TypeBinding *callee_bind, I32 in_func) {
        for (U32 i = 1; i < e->children.count; i++) {
            infer_expr(scope, Expr_child(e, &(USize){(USize)(i)}), in_func);
        }
        if (!(callee_bind && callee_bind->func_def)) return;
        Expr *fdef = callee_bind->func_def;
        I32 fvi = fdef->data.data.FuncDef.variadic_index;
        I32 fkwi = fdef->data.data.FuncDef.kwargs_index;
        U32 fvc = (fvi >= 0) ? e->data.data.FCall.variadic_count : 0;
        U32 fkc = (fkwi >= 0) ? e->data.data.FCall.kwargs_count : 0;
        U32 ci = 1;
        for (U32 pi = 0; pi < fdef->data.data.FuncDef.nparam && ci < e->children.count; pi++) {
            if (fvi >= 0 && (I32)pi == fvi) { ci += fvc; continue; }
            if (fkwi >= 0 && (I32)pi == fkwi) { ci += fkc; continue; }
            Str *ptype = &((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(pi)}))->ptype;
            if (ptype)
                narrow_dynamic(Expr_child(e, &(USize){(USize)(ci)}), type_from_name(ptype, scope), ptype);
            ci++;
        }
        ci = 1;
        for (U32 pi = 0; pi < fdef->data.data.FuncDef.nparam && ci < e->children.count; pi++) {
            if (fvi >= 0 && (I32)pi == fvi) { ci += fvc; continue; }
            if (fkwi >= 0 && (I32)pi == fkwi) { ci += fkc; continue; }
            Str *ptype_name = &((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(pi)}))->ptype;
            if (!ptype_name) { ci++; continue; }
            Expr *arg = Expr_child(e, &(USize){(USize)(ci)});
            if (arg->til_type.tag == TilType_TAG_Dynamic) { ci++; continue; }
            TilType ptype = *type_from_name(ptype_name, scope);
            if (ptype.tag == TilType_TAG_Dynamic) { ci++; continue; }
            if (arg->data.tag == ExprData_TAG_LiteralNum && is_numeric_type(&ptype)) {
                if (!literal_in_range(&arg->data.data.Ident, &ptype)) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "integer literal %s out of range for %s",
                             arg->data.data.Ident.c_str, til_type_name_c(&ptype)->c_str);
                    type_error(arg, STR_VIEW(buf));
                }
                arg->til_type = ptype; ci++; continue;
            }
            if (can_implicit_widen(&arg->til_type, &ptype) ||
                can_implicit_usize_coerce(&arg->til_type, &ptype, ptype_name)) {
                arg->til_type = ptype; ci++; continue;
            }
            if (arg->til_type.tag != ptype.tag) {
                char buf[256];
                snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                         ((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(pi)}))->name.c_str,
                         ptype_name->c_str, til_type_name_c(&arg->til_type)->c_str);
                type_error(arg, STR_VIEW(buf));
            } else if ((ptype.tag == TilType_TAG_Struct || ptype.tag == TilType_TAG_Enum) &&
                       (arg->struct_name).count > 0 && !Str_eq(ptype_name, &arg->struct_name)) {
                char buf[256];
                snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                         ((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(pi)}))->name.c_str,
                         ptype_name->c_str, arg->struct_name.c_str);
                type_error(arg, STR_VIEW(buf));
            }
            ci++;
        }
}

static void validate_fcall_own_args(TypeScope *scope, Expr *e, TypeBinding *callee_bind) {
        if (!(callee_bind && callee_bind->func_def)) return;
        Expr *fdef = callee_bind->func_def;
        I32 fvi = fdef->data.data.FuncDef.variadic_index;
        I32 fkwi = fdef->data.data.FuncDef.kwargs_index;
        U32 fvc = (fvi >= 0) ? e->data.data.FCall.variadic_count : 0;
        U32 fkc = (fkwi >= 0) ? e->data.data.FCall.kwargs_count : 0;
        U32 ci = 1;
        for (U32 pi = 0; pi < fdef->data.data.FuncDef.nparam && ci < e->children.count; pi++) {
            if (fvi >= 0 && (I32)pi == fvi) { ci += fvc; continue; }
            if (fkwi >= 0 && (I32)pi == fkwi) { ci += fkc; continue; }
            Param *_pp2 = (Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(pi)});
            Bool pown = _pp2->is_own;
            if (pown && !Expr_child(e, &(USize){(USize)(ci)})->is_own_arg) {
                char buf[128];
                snprintf(buf, sizeof(buf), "argument for 'own' parameter '%s' must be marked 'own'",
                         _pp2->name.c_str);
                type_error(Expr_child(e, &(USize){(USize)(ci)}), STR_VIEW(buf));
            } else if (!pown && Expr_child(e, &(USize){(USize)(ci)})->is_own_arg) {
                char buf[128];
                snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                         _pp2->name.c_str);
                type_error(Expr_child(e, &(USize){(USize)(ci)}), STR_VIEW(buf));
            }
            if (pown && Expr_child(e, &(USize){(USize)(ci)})->data.tag == ExprData_TAG_Ident) {
                ScopeFind *_sf_ab2 = TypeScope_find(scope, &Expr_child(e, &(USize){(USize)(ci)})->data.data.Ident);
                TypeBinding *ab = _sf_ab2->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ab2) : NULL;
                if (ab && ab->is_ref) type_error(Expr_child(e, &(USize){(USize)(ci)}), STR_LIT("cannot pass ref variable to 'own' parameter; use .clone() to make an owned copy"));
            }
            if (pown && Expr_child(e, &(USize){(USize)(ci)})->data.tag == ExprData_TAG_LiteralNull)
                type_error(Expr_child(e, &(USize){(USize)(ci)}), STR_LIT("cannot pass null to 'own' parameter"));
            if (_pp2->is_shallow && Expr_child(e, &(USize){(USize)(ci)})->data.tag == ExprData_TAG_LiteralNull)
                type_error(Expr_child(e, &(USize){(USize)(ci)}), STR_LIT("cannot pass null to 'shallow' parameter"));
            ci++;
        }
}

static void resolve_fcall_return_type(TypeScope *scope, Expr *e, Str *name, TypeBinding *callee_bind, I32 in_func) {
        if (((name->count == 8 && memcmp(name->c_str, "dyn_call", 8) == 0) || (name->count == 12 && memcmp(name->c_str, "dyn_call_ret", 12) == 0) ||
             (name->count == 14 && memcmp(name->c_str, "dyn_has_method", 14) == 0) || (name->count == 6 && memcmp(name->c_str, "dyn_fn", 6) == 0)) &&
            e->children.count >= 3) {
            Expr *method_arg = Expr_child(e, &(USize){(USize)(2)});
            if (method_arg->data.tag != ExprData_TAG_LiteralStr) {
                type_error(method_arg, STR_LIT("dyn_call method argument must be a string literal"));
            }
        }
        if (((name->count == 5 && memcmp(name->c_str, "array", 5) == 0) || (name->count == 3 && memcmp(name->c_str, "vec", 3) == 0)) &&
            e->children.count >= 2) {
            Expr *type_arg = Expr_child(e, &(USize){(USize)(1)});
            if (type_arg->data.tag != ExprData_TAG_LiteralStr) {
                type_error(type_arg, STR_LIT("array/vec type_name argument must be a string literal"));
            }
        }
        TilType fn_type = *TypeScope_get_type(scope, name);
        if (fn_type.tag == TilType_TAG_Unknown) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined function '%s'", name->c_str);
            type_error(e, STR_VIEW(buf));
        }
        if (fn_type.tag == TilType_TAG_FuncPtr && callee_bind && callee_bind->is_proc < 0) {
            Expr_child(e, &(USize){(USize)(0)})->til_type = (TilType){TilType_TAG_FuncPtr};
            if (callee_bind && callee_bind->func_def) {
                e->fn_sig = callee_bind->func_def;
                e->data.data.FCall.fn_sig = callee_bind->func_def;
            }
            if (callee_bind && callee_bind->func_def &&
                (callee_bind->func_def->data.data.FuncDef.return_type).count > 0) {
                TilType rt = *type_from_name(&callee_bind->func_def->data.data.FuncDef.return_type, scope);
                e->til_type = rt;
                if ((rt.tag == TilType_TAG_Struct || rt.tag == TilType_TAG_Enum))
                    e->struct_name = *Str_clone(&callee_bind->func_def->data.data.FuncDef.return_type);
            } else {
                e->til_type = (TilType){TilType_TAG_Dynamic};
            }
            if (callee_bind && callee_bind->func_def) {
                Expr *sig = callee_bind->func_def;
                U32 nargs = e->children.count - 1;
                if (nargs != sig->data.data.FuncDef.nparam) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "function pointer '%s' expects %u args, got %u",
                             name->c_str, sig->data.data.FuncDef.nparam, nargs);
                    type_error(e, STR_VIEW(buf));
                }
                for (U32 ai = 0; ai < nargs && ai < sig->data.data.FuncDef.nparam; ai++) {
                    Expr *arg = Expr_child(e, &(USize){(USize)(ai + 1)});
                    Str *expected_name = &((Param*)Vec_get(&sig->data.data.FuncDef.params, &(USize){(USize)(ai)}))->ptype;
                    if (!expected_name) continue;
                    TilType expected = *type_from_name(expected_name, scope);
                    if (expected.tag == TilType_TAG_Unknown || expected.tag == TilType_TAG_Dynamic) continue;
                    if (arg->til_type.tag == TilType_TAG_Dynamic) continue;
                    if (arg->til_type.tag != expected.tag) {
                        char buf[256];
                        snprintf(buf, sizeof(buf), "function pointer '%s' param %u: expected %s, got %s",
                                 name->c_str, ai + 1, expected_name->c_str,
                                 til_type_name_c(&arg->til_type)->c_str);
                        type_error(e, STR_VIEW(buf));
                    }
                }
            }
        } else {
            e->til_type = fn_type;
            if ((fn_type.tag == TilType_TAG_Struct || fn_type.tag == TilType_TAG_Enum) && callee_bind && callee_bind->func_def &&
                (callee_bind->func_def->data.data.FuncDef.return_type).count > 0) {
                e->struct_name = *Str_clone(&callee_bind->func_def->data.data.FuncDef.return_type);
            }
            if (fn_type.tag == TilType_TAG_FuncPtr && callee_bind && callee_bind->func_def &&
                (callee_bind->func_def->data.data.FuncDef.return_type).count > 0) {
                ScopeFind *_sf_rsb = TypeScope_find(scope, &callee_bind->func_def->data.data.FuncDef.return_type);
                TypeBinding *rsb = _sf_rsb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_rsb) : NULL;
                if (rsb && rsb->func_def && rsb->func_def->children.count == 0) {
                    e->fn_sig = rsb->func_def;
                    e->data.data.FCall.fn_sig = rsb->func_def;
                }
            }
        }
        Bool debug_exempt = current_mode.debug_prints &&
            ((name->count == 5 && memcmp(name->c_str, "print", 5) == 0) || (name->count == 7 && memcmp(name->c_str, "println", 7) == 0));
        if (fn_type.tag != TilType_TAG_FuncPtr &&
            in_func && TypeScope_is_proc(scope, name) == 1 && !(name->count == 5 && memcmp(name->c_str, "panic", 5) == 0) && !debug_exempt) {
            char buf[128];
            snprintf(buf, sizeof(buf), "func cannot call proc '%s'", name->c_str);
            type_error(e, STR_VIEW(buf));
        }
        if (TypeScope_is_proc(scope, name) == 2) {
            char buf[128];
            snprintf(buf, sizeof(buf), "test functions cannot be called ('%s')", name->c_str);
            type_error(e, STR_VIEW(buf));
        }
}

void infer_fcall_expr(TypeScope *scope, Expr *e, I32 in_func) {
        if (Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess) {
            if (infer_field_access_fcall(scope, e, in_func)) return;
        }
        Str _name_val = Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
        Str *name = &_name_val;
        Str *resolved_name = resolve_type_alias(scope, name);
        if (resolved_name != name) {
            Expr_child(e, &(USize){(USize)(0)})->data.data.Ident = *resolved_name;
            _name_val = *resolved_name;
        }
        if (infer_struct_constructor_fcall(scope, e, name, in_func)) return;
        ScopeFind *_sf_cb = TypeScope_find(scope, name);
        TypeBinding *callee_bind = _sf_cb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_cb) : NULL;
        if (callee_bind && callee_bind->func_def &&
            (!callee_bind->is_builtin || !callee_bind->func_def->is_core)) {
            desugar_user_func_fcall_args(e, name, callee_bind);
        }
        infer_and_validate_fcall_args(scope, e, callee_bind, in_func);
        validate_fcall_own_args(scope, e, callee_bind);
        resolve_fcall_return_type(scope, e, name, callee_bind, in_func);
        return;
}

// --- Collection literal helpers ---

// --- Set literal desugaring ---
// Transforms s := {v1, v2, v3} into:
//   mut s := Set.new(elem_type, elem_size)
//   Set.add(s, own v1)
//   Set.add(s, own v2)
//   Set.add(s, own v3)

// --- Map literal desugaring ---
// Transforms m := {k1: v1, k2: v2} into:
//   mut m := Map.new(key_type, key_size, val_type, val_size)
//   Map.set(m, own k1, own v1)
//   Map.set(m, own k2, own v2)

// --- Variadic call desugaring ---
// Transforms variadic function calls into Array.new + Array.set + normal call.
// Must run before hoisting so that synthetic Array calls get hoisted too.

// Create a namespace method call: StructName.method(args...)
// --- Kwargs call desugaring ---
// Transforms kwargs function calls into Map.new + Map.set + normal call.

// --- Argument hoisting ---


// Check if a function call returns ref

// --- Delete call insertion ---
