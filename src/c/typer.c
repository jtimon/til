#include "../../boot/modes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations for til-generated functions (typer.til)
Bool is_numeric_type(TilType *t);
Bool is_integral_numeric_type(TilType *t);
Bool is_usize_name(Str *name);
Bool can_implicit_usize_coerce(TilType *from, TilType *to, Str *to_name);
Bool literal_in_range(Str *val_str, TilType *target);
Bool can_implicit_widen(TilType *from, TilType *to);
TilType *type_from_name(Str *name, TypeScope *scope);
Str *resolve_type_alias(TypeScope *scope, Str *name);
Str *usize_name(TypeScope *scope);
TilType *usize_type(TypeScope *scope);
Bool expr_contains_fcall(Expr *e);
Bool expr_uses_var(Expr *e, Str *name);
Bool expr_contains_decl(Expr *e, Str *name);
Bool expr_used_in_nested_func(Expr *e, Str *name);
Bool check_own_args(Expr *fdef, Expr *fcall, Str *var_name);
Bool fcall_has_own_arg(Expr *fcall, Str *var_name, TypeScope *scope);
Bool expr_transfers_own(Expr *e, Str *var_name, TypeScope *scope);
Bool alias_used_in_expr(Expr *body, Str *name, Expr *expr);
I32 fcall_returns_ref(Expr *fcall, TypeScope *scope);
void narrow_dynamic(Expr *expr, TilType *target, Str *target_struct_name);
Bool field_assign_needs_delete(Expr *stmt);
void type_error(Expr *e, Str *msg);

#define STR_LIT(s) (&(Str){.c_str=(U8 *)(s), .count=(U64)(sizeof(s) - 1), .cap=CAP_LIT})
#define STR_VIEW(s) (&(Str){.c_str=(U8 *)(s), .count=(U64)strlen((const char *)(s)), .cap=CAP_VIEW})

// --- Type inference/checking pass ---


void infer_expr(TypeScope *scope, Expr *e, I32 in_func);
void infer_body(TypeScope *scope, Expr *body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body);

static void infer_fcall_expr(TypeScope *scope, Expr *e, I32 in_func);
static void infer_func_def_expr(TypeScope *scope, Expr *e);
static void infer_func_sig_expr(TypeScope *scope, Expr *e);
static void infer_func_params(TypeScope *scope, TypeScope *func_scope, Expr *e);
static void check_ref_function_returns(TypeScope *func_scope, Expr *e);
void infer_type_def_expr(TypeScope *scope, Expr *e);
void infer_field_access_expr(TypeScope *scope, Expr *e, I32 in_func);
void infer_decl_stmt(TypeScope *scope, Expr *stmt, I32 in_func, I32 in_type_body);
Bool infer_decl_type_def(TypeScope *scope, Expr *stmt);
Bool infer_decl_func_def(TypeScope *scope, Expr *stmt);
Bool infer_decl_type_alias_passthrough(TypeScope *scope, Expr *stmt);
void infer_decl_typed_value(TypeScope *scope, Expr *stmt);
void infer_decl_untyped_value(Expr *stmt);
void finalize_decl_binding(TypeScope *scope, Expr *stmt, I32 in_type_body);
void infer_while_stmt(TypeScope *scope, Expr *stmt, I32 in_func, I32 returns_ref);
void infer_switch_stmt(TypeScope *scope, Expr *body, U32 stmt_idx, I32 in_func);
void init_switch_enum_coverage(TypeScope *scope, Expr *sw_expr, Expr **switch_enum_def, Array **covered_variants, U32 *n_variants);
void mark_switch_case_covered_variant(Expr *switch_enum_def, Vec *covered_variants, I32 n_variants, Expr *sw_expr, Expr *match_expr);
Expr *make_switch_case_condition(TypeScope *scope, Expr *case_body, Expr *match_expr, Str *sw_name, U32 sw_line, U32 sw_col, Str *sw_path);
void replace_switch_stmt_with_block(Expr *body, U32 stmt_idx, Expr *block);

static void infer_func_sig_expr(TypeScope *scope, Expr *e) {
    if (e->data.data.FuncDef.return_type.count > 0)
        e->data.data.FuncDef.return_type = *resolve_type_alias(scope, &e->data.data.FuncDef.return_type);
    for (U32 i = 0; i < e->data.data.FuncDef.nparam; i++) {
        Param *_pi = (Param*)Vec_get(&e->data.data.FuncDef.params, &(USize){(USize)(i)});
        _pi->ptype = *resolve_type_alias(scope, &_pi->ptype);
    }
    e->til_type = (TilType){TilType_TAG_FuncPtr};
}

static void infer_func_params(TypeScope *scope, TypeScope *func_scope, Expr *e) {
    if (e->data.data.FuncDef.return_type.count > 0)
        e->data.data.FuncDef.return_type = *resolve_type_alias(scope, &e->data.data.FuncDef.return_type);
    for (U32 i = 0; i < e->data.data.FuncDef.nparam; i++) {
        Param *_pi = (Param*)Vec_get(&e->data.data.FuncDef.params, &(USize){(USize)(i)});
        _pi->ptype = *resolve_type_alias(scope, &_pi->ptype);
        Str *ptn = &_pi->ptype;
        TilType pt = *type_from_name(ptn, scope);
        if (pt.tag == TilType_TAG_Unknown) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined type '%s'", ptn->c_str);
            type_error(e, STR_VIEW(buf));
        }
        Bool pmut = _pi->is_mut;
        Bool pown = _pi->is_own;
        Bool pshallow = _pi->is_shallow;
        if (pshallow) {
            Bool is_scalar = (pt.tag == TilType_TAG_I64 || pt.tag == TilType_TAG_U8 || pt.tag == TilType_TAG_I16 ||
                              pt.tag == TilType_TAG_I32 || pt.tag == TilType_TAG_U32 || pt.tag == TilType_TAG_U64 || pt.tag == TilType_TAG_F32 || pt.tag == TilType_TAG_Bool);
            if (!is_scalar && pt.tag != TilType_TAG_Struct && pt.tag != TilType_TAG_StructDef && pt.tag != TilType_TAG_Enum) {
                char buf[128];
                snprintf(buf, sizeof(buf), "shallow parameter '%s' must be a scalar or struct type",
                         _pi->name.c_str);
                type_error(e, STR_VIEW(buf));
            }
            if (pown) type_error(e, STR_LIT("parameter cannot be both 'shallow' and 'own'"));
        }
        if ((I32)i == e->data.data.FuncDef.variadic_index) {
            _pi->is_own = true;
            TypeScope_set(func_scope, &_pi->name, &(TilType){TilType_TAG_Struct}, -1, 0, e->line, e->col, 1, 1);
            TypeBinding *pb = Map_get(&func_scope->bindings, &_pi->name);
            pb->struct_name = *Str_clone(&(Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT});
        } else if ((I32)i == e->data.data.FuncDef.kwargs_index) {
            _pi->is_own = true;
            TypeScope_set(func_scope, &_pi->name, &(TilType){TilType_TAG_Struct}, -1, 0, e->line, e->col, 1, 1);
            TypeBinding *pb = Map_get(&func_scope->bindings, &_pi->name);
            pb->struct_name = *Str_clone(&(Str){.c_str = (U8*)"DynMap", .count = 6, .cap = CAP_LIT});
        } else {
            TypeScope_set(func_scope, &_pi->name, &pt, -1, pmut, e->line, e->col, 1, pown);
            TypeBinding *pb = Map_get(&func_scope->bindings, &_pi->name);
            if (pt.tag == TilType_TAG_Struct || pt.tag == TilType_TAG_Enum) {
                pb->struct_name = *Str_clone(ptn);
            }
            if (pt.tag == TilType_TAG_FuncPtr) {
                ScopeFind *_sf_fsb = TypeScope_find(scope, ptn);
                TypeBinding *fsb = _sf_fsb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_fsb) : NULL;
                if (fsb && fsb->func_def && fsb->func_def->children.count == 0) {
                    pb->func_def = fsb->func_def;
                }
            }
        }
    }
}

static void check_ref_function_returns(TypeScope *func_scope, Expr *e) {
    if (!e->data.data.FuncDef.return_is_ref) return;
    Expr *body = Expr_child(e, &(USize){(USize)(0)});
    for (U32 ri = 0; ri < body->children.count; ri++) {
        Expr *s = Expr_child(body, &(USize){(USize)(ri)});
        if (s->data.tag != ExprData_TAG_Return || s->children.count == 0) continue;
        Expr *rv = Expr_child(s, &(USize){(USize)(0)});
        Bool ok = expr_is_borrow_source(rv, func_scope);
        if (!ok) type_error(s, STR_LIT("ref function must return a parameter or ref variable"));
    }
}

static void infer_func_def_expr(TypeScope *scope, Expr *e) {
    if (e->children.count == 0) {
        infer_func_sig_expr(scope, e);
        return;
    }
    e->til_type = (TilType){TilType_TAG_None};
    {
        FuncType ftype = e->data.data.FuncDef.func_type;
        Bool is_func = (ftype.tag == FuncType_TAG_Func);
        Bool is_macro = (ftype.tag == FuncType_TAG_Macro);
        if (ftype.tag == FuncType_TAG_Test) {
            if (scope->parent != NULL)
                type_error(e, STR_LIT("test functions can only be declared in root scope"));
            if (e->data.data.FuncDef.return_type.count > 0)
                type_error(e, STR_LIT("test functions cannot have a return type"));
            if (e->data.data.FuncDef.nparam > 0)
                type_error(e, STR_LIT("test functions cannot have parameters"));
        }
        if (current_mode.is_pure && ftype.tag == FuncType_TAG_Proc && !e->is_core)
            type_error(e, STR_LIT("proc not allowed in pure mode"));
        TypeScope *func_scope = TypeScope_new(scope);
        infer_func_params(scope, func_scope, e);
        infer_body(func_scope, Expr_child(e, &(USize){(USize)(0)}), is_func, 1, 0, e->data.data.FuncDef.return_is_ref, 0);
        if (is_macro && (e->data.data.FuncDef.return_type).count == 0) {
            type_error(e, STR_LIT("macro must declare a return type"));
        }
        check_ref_function_returns(func_scope, e);
        TypeScope_delete(func_scope, &(Bool){1});
    }
}

void infer_expr(TypeScope *scope, Expr *e, I32 in_func) {
    switch (e->data.tag) {
    case ExprData_TAG_LiteralStr:
    case ExprData_TAG_LiteralNum:
    case ExprData_TAG_LiteralBool:
    case ExprData_TAG_LiteralNull:
        infer_literal_expr(e);
        break;
    case ExprData_TAG_Ident:
        infer_ident_expr(scope, e);
        break;
    case ExprData_TAG_FuncDef:
        infer_func_def_expr(scope, e);
        break;
    case ExprData_TAG_StructDef:
    case ExprData_TAG_EnumDef: {
        infer_type_def_expr(scope, e);
        break;
    }
    case ExprData_TAG_FCall:
        infer_fcall_expr(scope, e, in_func);
        break;
    case ExprData_TAG_FieldAccess: {
        infer_field_access_expr(scope, e, in_func);
        break;
    }
    case ExprData_TAG_MapLit:
        infer_map_lit_expr(scope, e, in_func);
        break;
    case ExprData_TAG_SetLit:
        infer_set_lit_expr(scope, e, in_func);
        break;
    case ExprData_TAG_NamedArg:
        infer_named_arg_expr(scope, e, in_func);
        break;
    default:
        e->til_type = (TilType){TilType_TAG_Unknown};
        break;
    }
}

static void infer_fcall_expr(TypeScope *scope, Expr *e, I32 in_func) {
        // Namespace method call or UFCS: Type.method(args) or instance.method(args)
        if (Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess) {
            Expr *fa = Expr_child(e, &(USize){(USize)(0)});
            Expr *obj = Expr_child(fa, &(USize){(USize)(0)});
            Str *method = &fa->data.data.FieldAccess;

            // Type just the object first (not the full field access)
            infer_expr(scope, obj, in_func);

            // Check: is obj a type name (has struct_def) or an instance/value?
            ScopeFind *_sf_tb = (obj->data.tag == ExprData_TAG_Ident)
                ? TypeScope_find(scope, &obj->data.data.Ident) : NULL;
            TypeBinding *tb = (_sf_tb && _sf_tb->tag == ScopeFind_TAG_Found) ? (TypeBinding*)get_payload(_sf_tb) : NULL;
            Bool obj_is_type = (tb && tb->struct_def);

            Bool ufcs_desugared = 0; // #88: true if UFCS rewrote instance.method → Type.method(instance)
            if (!obj_is_type) {
                // UFCS: instance.method(args) -> Type.method(instance, args)
                Str *type_name = NULL;
                if (obj->til_type.tag >= TilType_TAG_I64 && obj->til_type.tag <= TilType_TAG_Bool)
                    type_name = til_type_name_c(&obj->til_type);
                else if ((obj->til_type.tag == TilType_TAG_Struct || obj->til_type.tag == TilType_TAG_Enum) && obj->struct_name.count > 0)
                    type_name = &obj->struct_name;

                Expr *sdef = type_name ? TypeScope_get_struct(scope, type_name) : NULL;
                Expr *ns_func = NULL;
                if (sdef) {
                    Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
                    for (U32 i = 0; i < body->children.count; i++) {
                        Expr *field = Expr_child(body, &(USize){(USize)(i)});
                        if (field->data.data.Decl.is_namespace &&
                            Str_eq(&field->data.data.Decl.name, method) &&
                            Expr_child(field, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef) {
                            ns_func = Expr_child(field, &(USize){(USize)(0)});
                            break;
                        }
                    }
                }
                if (!ns_func) {
                    // UFCS fallback: check top-level for f(a: T, ...)
                    ScopeFind *_sf_top = TypeScope_find(scope, method);
                    TypeBinding *top = _sf_top->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_top) : NULL;
                    Bool ufcs_match = 0;
                    if (top && top->func_def &&
                        top->func_def->data.data.FuncDef.nparam > 0 &&
                        ((Param*)Vec_get(&top->func_def->data.data.FuncDef.params, &(USize){(USize)(0)}))->ptype.count > 0) {
                        Str *first_param = &((Param*)Vec_get(&top->func_def->data.data.FuncDef.params, &(USize){(USize)(0)}))->ptype;
                        if (type_name && Str_eq(first_param, type_name)) {
                            ufcs_match = 1; // known type matches first param
                        } else if (!type_name && obj->til_type.tag == TilType_TAG_Dynamic) {
                            // Dynamic receiver: narrow to first param type
                            TilType pt = *type_from_name(first_param, scope);
                            narrow_dynamic(obj, &pt, first_param);
                            ufcs_match = 1;
                        }
                    }
                    if (ufcs_match) {
                        // Rewrite: a.f(b) → f(a, b)
                        Expr *fn_ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, fa->line, fa->col, &fa->path);
                        fn_ident->data.data.Ident = *method;
                        *(Expr*)Vec_get(&e->children, &(USize){(USize)(0)}) = *fn_ident;
                        // Insert instance as first arg
                        Expr *instance = obj;
                        Expr dummy = {0};
                        { Expr *_p = malloc(sizeof(Expr)); *_p = dummy; Vec_push(&e->children, _p); }
                        {
                            Expr *ch = (Expr *)e->children.data;
                            memmove(&ch[2], &ch[1], (e->children.count - 2) * sizeof(Expr));
                        }
                        *(Expr*)Vec_get(&e->children, &(USize){(USize)(1)}) = *Expr_clone(instance);
                        goto regular_call;
                    }
                    // Fallback: check if method is a FuncSig-typed struct field
                    // e.g. h.on_click(3, 5) where on_click is a BinaryOp field
                    if (sdef && (obj->til_type.tag == TilType_TAG_Struct || obj->til_type.tag == TilType_TAG_Enum)) {
                        Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
                        for (U32 fi = 0; fi < body->children.count; fi++) {
                            Expr *field = Expr_child(body, &(USize){(USize)(fi)});
                            if (field->data.tag != ExprData_TAG_Decl || field->data.data.Decl.is_namespace) continue;
                            if (!Str_eq(&field->data.data.Decl.name, method)) continue;
                            if (field->data.data.Decl.explicit_type.count == 0) continue;
                            ScopeFind *_sf_ftb = TypeScope_find(scope, &field->data.data.Decl.explicit_type);
                            TypeBinding *ftb = _sf_ftb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ftb) : NULL;
                            if (ftb && ftb->func_def && ftb->func_def->children.count == 0) {
                                // Rewrite: h.on_click(3, 5) → indirect call through field access
                                // The field access node becomes the callee, typed as FUNC_PTR
                                fa->til_type = (TilType){TilType_TAG_FuncPtr};
                                fa->fn_sig = ftb->func_def;
                                // Type-check and resolve like a func ptr call
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
                                goto done_fcall;
                            }
                        }
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
                    return;
                }
                // Desugar: rewrite AST to Type.method(instance, args)
                ufcs_desugared = 1; // #88
                Expr *instance = Expr_clone(obj); // clone before fa->children overwrite
                Expr *type_ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, obj->line, obj->col, &obj->path);
                type_ident->data.data.Ident = *type_name;
                *(Expr*)Vec_get(&fa->children, &(USize){(USize)(0)}) = *type_ident;
                // Insert instance as first arg
                Expr dummy = {0};
                { Expr *_p = malloc(sizeof(Expr)); *_p = dummy; Vec_push(&e->children, _p); }
                {
                    Expr *ch = (Expr *)e->children.data;
                    memmove(&ch[2], &ch[1], (e->children.count - 2) * sizeof(Expr));
                }
                *(Expr*)Vec_get(&e->children, &(USize){(USize)(1)}) = *instance;
                // Fall through -- existing code below handles Type.method(instance, args)
                // Re-fetch after e->children mutation (push may realloc)
                fa = Expr_child(e, &(USize){(USize)(0)});
                method = &fa->data.data.FieldAccess;
            }

            // Type the (possibly new) object and look up namespace func
            obj = Expr_child(fa, &(USize){(USize)(0)});
            if (obj->til_type.tag == TilType_TAG_Unknown) {
                infer_expr(scope, obj, in_func);
            }
            Expr *sdef = (obj->struct_name).count > 0 ? TypeScope_get_struct(scope, &obj->struct_name) : NULL;
            Expr *ns_func = NULL;
            if (sdef) {
                Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
                for (U32 i = 0; i < body->children.count; i++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(i)});
                    if (field->data.data.Decl.is_namespace &&
                        Str_eq(&field->data.data.Decl.name, method) &&
                        Expr_child(field, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef) {
                        ns_func = Expr_child(field, &(USize){(USize)(0)});
                        break;
                    }
                }
            }
            if (!ns_func) {
                char buf[128];
                snprintf(buf, sizeof(buf), "no namespace function '%s'", method->c_str);
                type_error(e, STR_VIEW(buf));
                e->til_type = (TilType){TilType_TAG_Unknown};
                return;
            }
            fa->is_ns_field = true;
            // Desugar named/optional args for namespace methods
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
                            new_args[slot] = Expr_clone(Expr_child(arg, &(USize){(USize)(0)})); // unwrap ExprData_TAG_NamedArg
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
                // Fill defaults for missing args
                for (U32 i = 0; i < np; i++) {
                    if (!new_args[i]) {
                        Str *_pn = &((Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(i)}))->name;
                        if (Map_has(&ns_func->data.data.FuncDef.param_defaults, _pn)) {
                            new_args[i] = Expr_clone((Expr*)Map_get(&ns_func->data.data.FuncDef.param_defaults, _pn));
                        } else {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "missing argument for parameter '%s'",
                                     _pn->c_str);
                            type_error(e, STR_VIEW(buf));
                        }
                    }
                }
                if (pos_idx > np) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d", np, pos_idx);
                    type_error(e, STR_VIEW(buf));
                }
                // Rebuild children: callee + desugared args
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
            // Infer arg types
            for (U32 i = 1; i < e->children.count; i++) {
                infer_expr(scope, Expr_child(e, &(USize){(USize)(i)}), in_func);
            }
            // Narrow Dynamic args to parameter types
            for (U32 i = 1; i < e->children.count && i - 1 < ns_func->data.data.FuncDef.nparam; i++) {
                Str *ptype = &((Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(i - 1)}))->ptype;
                if (ptype)
                    narrow_dynamic(Expr_child(e, &(USize){(USize)(i)}), type_from_name(ptype, scope), ptype);
            }
            // Validate arg types against param types
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
                    arg->til_type = ptype; continue;
                }
                if (can_implicit_widen(&arg->til_type, &ptype) ||
                    can_implicit_usize_coerce(&arg->til_type, &ptype, ptype_name)) {
                    arg->til_type = ptype; continue;
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
            // #88: own p.delete() — propagate own from FieldAccess callee to UFCS-inserted first arg
            if (ufcs_desugared && Expr_child(e, &(USize){(USize)(0)})->is_own_arg && e->children.count > 1) {
                Expr_child(e, &(USize){(USize)(1)})->is_own_arg = 1;
            }
            // Validate 'own' markers on arguments
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
            // Set return type
            TilType rt = (TilType){TilType_TAG_None};
            if (ns_func->data.data.FuncDef.return_type.count > 0) {
                rt = *type_from_name(&ns_func->data.data.FuncDef.return_type, scope);
            }
            e->til_type = rt;
            if ((rt.tag == TilType_TAG_Struct || rt.tag == TilType_TAG_Enum) && (ns_func->data.data.FuncDef.return_type).count > 0) {
                e->struct_name = *Str_clone(&ns_func->data.data.FuncDef.return_type);
            }
            return;
        }
        regular_call:;
        // Resolve callee
        Str _name_val = Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
        Str *name = &_name_val;
        // Resolve type alias for struct constructors (Point2 → Point)
        Str *resolved_name = resolve_type_alias(scope, name);
        if (resolved_name != name) {
            // Rewrite callee Ident to canonical name so builder emits correct constructor
            Expr_child(e, &(USize){(USize)(0)})->data.data.Ident = *resolved_name;
            _name_val = *resolved_name;
        }
        // Struct instantiation: Point() or Point(x=1, y=2)
        Expr *sdef = TypeScope_get_struct(scope, name);
        if (sdef) {
            ScopeFind *_sf_sb = TypeScope_find(scope, name);
            TypeBinding *sb = _sf_sb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_sb) : NULL;
            if (sb && sb->is_builtin && !sb->is_ext) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot instantiate builtin type '%s'", name->c_str);
                type_error(e, STR_VIEW(buf));
                e->til_type = (TilType){TilType_TAG_Unknown};
                return;
            }
            Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
            // Count instance fields (skip namespace)
            U32 nfields = 0;
            for (U32 i = 0; i < body->children.count; i++) {
                if (!Expr_child(body, &(USize){(USize)(i)})->data.data.Decl.is_namespace) nfields++;
            }
            // Desugar named args into positional (one per instance field)
            Expr **field_vals = calloc(nfields, sizeof(Expr *));
            // Map: field_idx[k] = index into body->children for k-th instance field
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
                    field_vals[slot] = Expr_clone(Expr_child(arg, &(USize){(USize)(0)})); // unwrap ExprData_TAG_NamedArg
                }
            }
            // Fill remaining from struct field defaults (clone to avoid shared ownership)
            for (U32 i = 0; i < nfields; i++) {
                if (!field_vals[i]) {
                    field_vals[i] = Expr_clone(Expr_child(Expr_child(body, &(USize){(USize)(field_idx[i])}), &(USize){(USize)(0)}));
                }
            }
            // Rebuild children: callee + instance field values
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
            // Type-check args (skip already-inferred defaults)
            for (U32 i = 1; i < e->children.count; i++) {
                if (Expr_child(e, &(USize){(USize)(i)})->til_type.tag == TilType_TAG_Unknown) {
                    infer_expr(scope, Expr_child(e, &(USize){(USize)(i)}), in_func);
                }
            }
            // Struct literals consume all non-ref field args.
            { U32 fi = 0;
              for (U32 bi = 0; bi < body->children.count && fi < e->children.count - 1; bi++) {
                Expr *fld = Expr_child(body, &(USize){(USize)(bi)});
                if (fld->data.data.Decl.is_namespace) continue;
                I32 ai = fi + 1; // arg index (children[0] is callee)
                fi++;
                if (fld->data.data.Decl.is_ref) {
                    continue;
                }
                if (!fld->data.data.Decl.is_own && !type_ctor_consumes(&fld->til_type)) {
                    continue;
                }
                Expr_child(e, &(USize){(USize)(ai)})->is_own_arg = 1;
              }
            }
            e->til_type = (TilType){TilType_TAG_Struct};
            e->struct_name = *Str_clone(resolve_type_alias(scope, name));
            return;
        }
        // Desugar named/optional args for user-defined functions (skip core builtins)
        ScopeFind *_sf_cb = TypeScope_find(scope, name);
        TypeBinding *callee_bind = _sf_cb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_cb) : NULL;
        if (callee_bind && callee_bind->func_def &&
            (!callee_bind->is_builtin || !callee_bind->func_def->is_core)) {
            Expr *fdef = callee_bind->func_def;
            U32 nparam = fdef->data.data.FuncDef.nparam;
            I32 vi = fdef->data.data.FuncDef.variadic_index; // -1 if not variadic
            I32 kwi = fdef->data.data.FuncDef.kwargs_index;  // -1 if no kwargs
            U32 fixed_count = (vi >= 0) ? (U32)vi : nparam; // params before variadic
            // Collect positional and named args
            Vec va_args; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); va_args = *_vp; free(_vp); } // variadic args (only if vi >= 0)
            Vec kw_args; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Dynamic", .count = 7, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); kw_args = *_vp; free(_vp); } // kwargs args (ExprData_TAG_NamedArg nodes)
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
                        if ((I32)j == vi) continue; // can't name the variadic param
                        if ((I32)j == kwi) continue; // can't name the kwargs param
                        if (Str_eq(&((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(j)}))->name, aname)) {
                            slot = j;
                            break;
                        }
                    }
                    if (slot < 0 && kwi >= 0) {
                        // Unmatched named arg goes to kwargs
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
                        new_args[slot] = Expr_clone(Expr_child(arg, &(USize){(USize)(0)})); // unwrap ExprData_TAG_NamedArg
                    }
                } else {
                    if (seen_named) {
                        type_error(arg, STR_LIT("positional argument after named argument"));
                    }
                    if (vi >= 0 && pos_idx >= fixed_count) {
                        // Variadic arg
                        { Expr **_p = malloc(sizeof(Expr *)); *_p = arg; Vec_push(&va_args, _p); }
                    } else if (pos_idx < nparam) {
                        new_args[pos_idx] = Expr_clone(arg);
                    }
                    pos_idx++;
                }
            }
            // Fill defaults for missing non-variadic/non-kwargs params
            for (U32 i = 0; i < nparam; i++) {
                if ((I32)i == vi) continue; // variadic param handled separately
                if ((I32)i == kwi) continue; // kwargs param handled separately
                if (!new_args[i]) {
                    Str *_pn = &((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(i)}))->name;
                    if (Map_has(&fdef->data.data.FuncDef.param_defaults, _pn)) {
                        new_args[i] = Expr_clone((Expr*)Map_get(&fdef->data.data.FuncDef.param_defaults, _pn));
                    } else {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "missing argument for parameter '%s'",
                                 _pn->c_str);
                        type_error(e, STR_VIEW(buf));
                    }
                }
            }
            U32 max_pos = nparam - (kwi >= 0 ? 1 : 0);
            if (vi < 0 && pos_idx > max_pos) {
                char buf[128];
                snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d",
                         nparam, pos_idx);
                type_error(e, STR_VIEW(buf));
            }
            // Rebuild children: callee + args_before_variadic + variadic_args + args_after_variadic
            Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"Expr", .count = 4, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
            Expr *callee = Expr_child(e, &(USize){(USize)(0)});
            Vec_push(&new_ch, Expr_clone(callee));
            for (U32 i = 0; i < nparam; i++) {
                if ((I32)i == vi) {
                    e->data.data.FCall.variadic_index = new_ch.count; // children index of first variadic arg
                    for (U32 j = 0; j < va_args.count; j++) {
                        Expr *va = *(Expr **)Vec_get(&va_args, &(USize){(USize)(j)});
                        Vec_push(&new_ch, Expr_clone(va));
                    }
                    e->data.data.FCall.variadic_count = va_args.count;
                } else if ((I32)i == kwi) {
                    e->data.data.FCall.kwargs_index = new_ch.count; // children index of first kwargs arg
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
        // Infer types of all arguments
        for (U32 i = 1; i < e->children.count; i++) {
            infer_expr(scope, Expr_child(e, &(USize){(USize)(i)}), in_func);
        }
        // Narrow Dynamic args to parameter types, then validate arg types
        if (callee_bind && callee_bind->func_def) {
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
            // Validate arg types against param types
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
        // dyn_call variants: method (2nd arg) must be a string literal
        if (((name->count == 8 && memcmp(name->c_str, "dyn_call", 8) == 0) || (name->count == 12 && memcmp(name->c_str, "dyn_call_ret", 12) == 0) ||
             (name->count == 14 && memcmp(name->c_str, "dyn_has_method", 14) == 0) || (name->count == 6 && memcmp(name->c_str, "dyn_fn", 6) == 0)) &&
            e->children.count >= 3) {
            Expr *method_arg = Expr_child(e, &(USize){(USize)(2)});
            if (method_arg->data.tag != ExprData_TAG_LiteralStr) {
                type_error(method_arg, STR_LIT("dyn_call method argument must be a string literal"));
            }
        }
        // array/vec builtins: type_name (1st arg) must be a string literal
        if (((name->count == 5 && memcmp(name->c_str, "array", 5) == 0) || (name->count == 3 && memcmp(name->c_str, "vec", 3) == 0)) &&
            e->children.count >= 2) {
            Expr *type_arg = Expr_child(e, &(USize){(USize)(1)});
            if (type_arg->data.tag != ExprData_TAG_LiteralStr) {
                type_error(type_arg, STR_LIT("array/vec type_name argument must be a string literal"));
            }
        }
        // Validate 'own' markers on arguments (variadic-aware)
        if (callee_bind && callee_bind->func_def) {
            Expr *fdef = callee_bind->func_def;
            I32 fvi = fdef->data.data.FuncDef.variadic_index;
            I32 fkwi = fdef->data.data.FuncDef.kwargs_index;
            U32 fvc = (fvi >= 0) ? e->data.data.FCall.variadic_count : 0;
            U32 fkc = (fkwi >= 0) ? e->data.data.FCall.kwargs_count : 0;
            U32 ci = 1; // children index
            for (U32 pi = 0; pi < fdef->data.data.FuncDef.nparam && ci < e->children.count; pi++) {
                if (fvi >= 0 && (I32)pi == fvi) {
                    ci += fvc; // skip variadic args
                    continue;
                }
                if (fkwi >= 0 && (I32)pi == fkwi) {
                    ci += fkc; // skip kwargs args
                    continue;
                }
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
        // Resolve return type from scope (covers builtins and user-defined)
        TilType fn_type = *TypeScope_get_type(scope, name);
        if (fn_type.tag == TilType_TAG_Unknown) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined function '%s'", name->c_str);
            type_error(e, STR_VIEW(buf));
        }
        // Function pointer call: resolve return type from func_def if available
        // Only for actual func ptr variables (is_proc == -1), not functions returning func ptrs
        if (fn_type.tag == TilType_TAG_FuncPtr && callee_bind && callee_bind->is_proc < 0) {
            Expr_child(e, &(USize){(USize)(0)})->til_type = (TilType){TilType_TAG_FuncPtr}; // mark callee for builder
            // Store signature on FCALL for builder to use
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
            // Type check: verify argument count and types against signature
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
            // Propagate struct_name for struct-returning functions
            if ((fn_type.tag == TilType_TAG_Struct || fn_type.tag == TilType_TAG_Enum) && callee_bind && callee_bind->func_def &&
                (callee_bind->func_def->data.data.FuncDef.return_type).count > 0) {
                e->struct_name = *Str_clone(&callee_bind->func_def->data.data.FuncDef.return_type);
            }
            // Propagate FuncSig for functions returning func ptrs
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
        // Check: func cannot call proc (panic is exempt; print/println exempt in debug_prints modes)
        // Skip for function pointer calls (callee proc-ness unknown at compile time)
        Bool debug_exempt = current_mode.debug_prints &&
            ((name->count == 5 && memcmp(name->c_str, "print", 5) == 0) || (name->count == 7 && memcmp(name->c_str, "println", 7) == 0));
        if (fn_type.tag != TilType_TAG_FuncPtr &&
            in_func && TypeScope_is_proc(scope, name) == 1 && !(name->count == 5 && memcmp(name->c_str, "panic", 5) == 0) && !debug_exempt) {
            char buf[128];
            snprintf(buf, sizeof(buf), "func cannot call proc '%s'", name->c_str);
            type_error(e, STR_VIEW(buf));
        }
        // Check: test functions cannot be called by anyone
        if (TypeScope_is_proc(scope, name) == 2) {
            char buf[128];
            snprintf(buf, sizeof(buf), "test functions cannot be called ('%s')", name->c_str);
            type_error(e, STR_VIEW(buf));
        }
        done_fcall:
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


I32 type_check(Expr *program, TypeScope *scope, Mode *mode) {
    errors = 0;
    current_mode = *mode;
    infer_body(scope, program, 0, 1, 0, 0, 0);
    return errors;
}
