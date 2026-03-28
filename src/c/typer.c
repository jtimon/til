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

// --- Type inference/checking pass ---

static I32 errors;
static Mode *current_mode;

static void type_error(Expr *e, const char *msg) {
    fprintf(stderr, "%s:%u:%u: type error: %s\n", e->path.c_str, e->line, e->col, msg);
    errors++;
}


static void infer_expr(TypeScope *scope, Expr *e, I32 in_func);
static void infer_body(TypeScope *scope, Expr *body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body);
static Expr *make_clone_call(const char *type_name, TilType type, Expr *arg, Expr *src);
static Expr *make_ns_call(const char *sname, const char *method,
                           TilType ret_type, Str *ret_sname, Expr *src);







static void infer_expr(TypeScope *scope, Expr *e, I32 in_func) {
    switch (e->data.tag) {
    case ExprData_TAG_LiteralStr:
        e->til_type = (TilType){TilType_TAG_Struct};
        e->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        break;
    case ExprData_TAG_LiteralNum:
        if (e->til_type.tag != TilType_TAG_U8)
            e->til_type = (TilType){TilType_TAG_I64};
        break;
    case ExprData_TAG_LiteralBool:
        e->til_type = (TilType){TilType_TAG_Bool};
        break;
    case ExprData_TAG_LiteralNull:
        e->til_type = (TilType){TilType_TAG_Dynamic};
        break;
    case ExprData_TAG_Ident: {
        TilType t = *TypeScope_get_type(scope, &e->data.data.Ident);
        if (t.tag == TilType_TAG_Unknown) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined symbol '%s'", e->data.data.Ident.c_str);
            type_error(e, buf);
        }
        e->til_type = t;
        ScopeFind *_sf_id = TypeScope_find(scope, &e->data.data.Ident);
        TypeBinding *ib = _sf_id->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_id) : NULL;
        if (ib && (t.tag == TilType_TAG_Struct || t.tag == TilType_TAG_Enum)) {
            if (ib->struct_name.count > 0) e->struct_name = *Str_clone(&ib->struct_name);
        }
        // Function references: identifier refers to a function → Fn type
        if (ib && ib->func_def) {
            e->til_type = (TilType){TilType_TAG_FuncPtr};
        }
        // Struct type names: allow field access for namespace fields
        if (ib && ib->struct_def) {
            e->struct_name = *Str_clone(resolve_type_alias(scope, &e->data.data.Ident));
        }
        break;
    }
    case ExprData_TAG_FuncDef:
        if (e->children.count == 0) {
            // Bodyless = FuncSig type definition, no body to type
            // Resolve aliases in return type and param types (#79)
            if (e->data.data.FuncDef.return_type.count > 0)
                e->data.data.FuncDef.return_type = *resolve_type_alias(scope, &e->data.data.FuncDef.return_type);
            for (U32 i = 0; i < e->data.data.FuncDef.nparam; i++) {
                Param *_pi = (Param*)Vec_get(&e->data.data.FuncDef.params, &(USize){(USize)(i)});
                _pi->ptype = *resolve_type_alias(scope, &_pi->ptype);
            }
            e->til_type = (TilType){TilType_TAG_FuncPtr};
            break;
        }
        e->til_type = (TilType){TilType_TAG_None};
        // Type the body
        {
            FuncType ftype = e->data.data.FuncDef.func_type;
            Bool is_func = (ftype.tag == FuncType_TAG_Func);
            Bool is_macro = (ftype.tag == FuncType_TAG_Macro);
            // Test function constraints
            if (ftype.tag == FuncType_TAG_Test) {
                if (scope->parent != NULL)
                    type_error(e, "test functions can only be declared in root scope");
                if (e->data.data.FuncDef.return_type.count > 0)
                    type_error(e, "test functions cannot have a return type");
                if (e->data.data.FuncDef.nparam > 0)
                    type_error(e, "test functions cannot have parameters");
            }
            // Pure mode: reject user-declared procs (allow core procs)
            if (current_mode && current_mode->is_pure && ftype.tag == FuncType_TAG_Proc && !e->is_core)
                type_error(e, "proc not allowed in pure mode");
            TypeScope *func_scope = TypeScope_new(scope);
            // Resolve return type alias
            if (e->data.data.FuncDef.return_type.count > 0)
                e->data.data.FuncDef.return_type = *resolve_type_alias(scope, &e->data.data.FuncDef.return_type);
            // Bind parameters
            for (U32 i = 0; i < e->data.data.FuncDef.nparam; i++) {
                Param *_pi = (Param*)Vec_get(&e->data.data.FuncDef.params, &(USize){(USize)(i)});
                _pi->ptype = *resolve_type_alias(scope, &_pi->ptype);
                Str *ptn = &_pi->ptype;
                TilType pt = *type_from_name(ptn, scope);
                if (pt.tag == TilType_TAG_Unknown) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", ptn->c_str);
                    type_error(e, buf);
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
                        type_error(e, buf);
                    }
                    if (pown) type_error(e, "parameter cannot be both 'shallow' and 'own'");
                }
                // Variadic param: bind as Array (element type already validated above)
                if ((I32)i == e->data.data.FuncDef.variadic_index) {
                    _pi->is_own = true;
                    TypeScope_set(func_scope, &_pi->name, &(TilType){TilType_TAG_Struct}, -1, 0, e->line, e->col, 1, 1);
                    TypeBinding *pb = Map_get(&func_scope->bindings, &_pi->name);
                    pb->struct_name = *Str_clone(&(Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT});
                } else if ((I32)i == e->data.data.FuncDef.kwargs_index) {
                    // Kwargs param: bind as Map
                    _pi->is_own = true;
                    TypeScope_set(func_scope, &_pi->name, &(TilType){TilType_TAG_Struct}, -1, 0, e->line, e->col, 1, 1);
                    TypeBinding *pb = Map_get(&func_scope->bindings, &_pi->name);
                    pb->struct_name = *Str_clone(&(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT});
                } else {
                    TypeScope_set(func_scope, &_pi->name, &pt, -1, pmut, e->line, e->col, 1, pown);
                    // For struct/enum-typed params, store struct_name
                    TypeBinding *pb = Map_get(&func_scope->bindings, &_pi->name);
                    if (pt.tag == TilType_TAG_Struct || pt.tag == TilType_TAG_Enum) {
                        pb->struct_name = *Str_clone(ptn);
                    }
                    // For Fn-typed params, resolve func_def by type name from scope
                    if (pt.tag == TilType_TAG_FuncPtr) {
                        ScopeFind *_sf_fsb = TypeScope_find(scope, ptn);
                        TypeBinding *fsb = _sf_fsb->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_fsb) : NULL;
                        if (fsb && fsb->func_def && fsb->func_def->children.count == 0) {
                            pb->func_def = fsb->func_def;
                        }
                    }
                }
            }
            infer_body(func_scope, Expr_child(e, &(USize){(USize)(0)}), is_func, 1, 0, e->data.data.FuncDef.return_is_ref, 0);
            // Check: macro must have a return type (funcs allowed without)
            if (is_macro && (e->data.data.FuncDef.return_type).count == 0) {
                type_error(e, "macro must declare a return type");
            }
            // Validate ref returns: every return value must be a param or ref variable
            if (e->data.data.FuncDef.return_is_ref) {
                Expr *body = Expr_child(e, &(USize){(USize)(0)});
                for (U32 ri = 0; ri < body->children.count; ri++) {
                    Expr *s = Expr_child(body, &(USize){(USize)(ri)});
                    if (s->data.tag != ExprData_TAG_Return || s->children.count == 0) continue;
                    Expr *rv = Expr_child(s, &(USize){(USize)(0)});
                    Bool ok = expr_is_borrow_source(rv, func_scope);
                    if (!ok) type_error(s, "ref function must return a parameter or ref variable");
                }
            }
            TypeScope_delete(func_scope, &(Bool){1});
        }
        break;
    case ExprData_TAG_StructDef:
    case ExprData_TAG_EnumDef: {
        e->til_type = (TilType){TilType_TAG_None};
        // Reject ref payloads in tagged enum variants
        if (e->data.tag == ExprData_TAG_EnumDef) {
            Expr *body = Expr_child(e, &(USize){(USize)(0)});
            for (U32 vi = 0; vi < body->children.count; vi++) {
                Expr *v = Expr_child(body, &(USize){(USize)(vi)});
                if (v->data.tag == ExprData_TAG_Decl && !v->data.data.Decl.is_namespace &&
                    (v->data.data.Decl.explicit_type).count > 0 && v->data.data.Decl.is_ref) {
                    type_error(v, "ref payloads in tagged enum variants are not supported");
                }
            }
        }
        // Type-check field declarations in a child scope so fields
        // don't leak into outer scope's locals for free-call insertion
        TypeScope *inner = TypeScope_new(scope);
        infer_body(inner, Expr_child(e, &(USize){(USize)(0)}), 0, 0, 0, 0, 1);
        TypeScope_delete(inner, &(Bool){1});
        break;
    }
    case ExprData_TAG_FCall: {
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
                                    type_error(e, buf2);
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
                    type_error(e, buf);
                    e->til_type = (TilType){TilType_TAG_Unknown};
                    break;
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
                type_error(e, buf);
                e->til_type = (TilType){TilType_TAG_Unknown};
                break;
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
                            type_error(arg, buf);
                        } else if (new_args[slot]) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "duplicate argument for parameter '%s'", aname->c_str);
                            type_error(arg, buf);
                        } else {
                            new_args[slot] = Expr_clone(Expr_child(arg, &(USize){(USize)(0)})); // unwrap ExprData_TAG_NamedArg
                        }
                    } else {
                        if (seen_named) {
                            type_error(arg, "positional argument after named argument");
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
                            type_error(e, buf);
                        }
                    }
                }
                if (pos_idx > np) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d", np, pos_idx);
                    type_error(e, buf);
                }
                // Rebuild children: callee + desugared args
                Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
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
                        type_error(arg, buf);
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
                    type_error(arg, buf);
                } else if ((ptype.tag == TilType_TAG_Struct || ptype.tag == TilType_TAG_Enum) &&
                           (arg->struct_name).count > 0 && !Str_eq(ptype_name, &arg->struct_name)) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             ((Param*)Vec_get(&ns_func->data.data.FuncDef.params, &(USize){(USize)(i - 1)}))->name.c_str,
                             ptype_name->c_str, arg->struct_name.c_str);
                    type_error(arg, buf);
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
                            type_error(Expr_child(e, &(USize){(USize)(i)}), buf);
                        } else if (!pown && Expr_child(e, &(USize){(USize)(i)})->is_own_arg) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                                     _pp->name.c_str);
                            type_error(Expr_child(e, &(USize){(USize)(i)}), buf);
                        }
                        if (pown && Expr_child(e, &(USize){(USize)(i)})->data.tag == ExprData_TAG_Ident) {
                            ScopeFind *_sf_ab = TypeScope_find(scope, &Expr_child(e, &(USize){(USize)(i)})->data.data.Ident);
                            TypeBinding *ab = _sf_ab->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ab) : NULL;
                            if (ab && ab->is_ref) type_error(Expr_child(e, &(USize){(USize)(i)}), "cannot pass ref variable to 'own' parameter; use .clone() to make an owned copy");
                        }
                        if (pown && Expr_child(e, &(USize){(USize)(i)})->data.tag == ExprData_TAG_LiteralNull)
                            type_error(Expr_child(e, &(USize){(USize)(i)}), "cannot pass null to 'own' parameter");
                        if (_pp->is_shallow && Expr_child(e, &(USize){(USize)(i)})->data.tag == ExprData_TAG_LiteralNull)
                            type_error(Expr_child(e, &(USize){(USize)(i)}), "cannot pass null to 'shallow' parameter");
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
            break;
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
                type_error(e, buf);
                e->til_type = (TilType){TilType_TAG_Unknown};
                break;
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
                    type_error(arg, "struct instantiation requires named arguments");
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
                    type_error(arg, buf);
                } else if (field_vals[slot]) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "duplicate argument for field '%s'", aname->c_str);
                    type_error(arg, buf);
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
            Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
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
            // Auto-insert clone for constructor args that are identifiers
            // Skip clone for `own` fields — use move semantics instead
            { U32 fi = 0;
              for (U32 bi = 0; bi < body->children.count && fi < e->children.count - 1; bi++) {
                Expr *fld = Expr_child(body, &(USize){(USize)(bi)});
                if (fld->data.data.Decl.is_namespace) continue;
                I32 ai = fi + 1; // arg index (children[0] is callee)
                fi++;
                if (fld->data.data.Decl.is_own) {
                    // own field: mark for move, don't clone
                    if (Expr_child(e, &(USize){(USize)(ai)})->data.tag == ExprData_TAG_Ident)
                        Expr_child(e, &(USize){(USize)(ai)})->is_own_arg = 1;
                    continue;
                }
                if (fld->data.data.Decl.is_ref) {
                    // ref field: store pointer, don't clone
                    continue;
                }
                if (Expr_child(e, &(USize){(USize)(ai)})->data.tag == ExprData_TAG_Ident) {
                    Str *tname = type_to_name(&Expr_child(e, &(USize){(USize)(ai)})->til_type,
                                              &Expr_child(e, &(USize){(USize)(ai)})->struct_name);
                    if (tname->count > 0) {
                        Expr *_mc = make_clone_call((const char *)tname->c_str,
                            Expr_child(e, &(USize){(USize)(ai)})->til_type, Expr_child(e, &(USize){(USize)(ai)}),
                            Expr_child(e, &(USize){(USize)(ai)}));
                        *(Expr*)Vec_get(&e->children, &(USize){(USize)(ai)}) = *_mc;
                        memset(_mc, 0, sizeof(Expr)); free(_mc);
                    }
                }
              }
            }
            e->til_type = (TilType){TilType_TAG_Struct};
            e->struct_name = *Str_clone(resolve_type_alias(scope, name));
            break;
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
            Vec va_args; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); va_args = *_vp; free(_vp); } // variadic args (only if vi >= 0)
            Vec kw_args; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr *)}); kw_args = *_vp; free(_vp); } // kwargs args (ExprData_TAG_NamedArg nodes)
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
                        type_error(arg, buf);
                    } else if (new_args[slot]) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "duplicate argument for parameter '%s'", aname->c_str);
                        type_error(arg, buf);
                    } else {
                        new_args[slot] = Expr_clone(Expr_child(arg, &(USize){(USize)(0)})); // unwrap ExprData_TAG_NamedArg
                    }
                } else {
                    if (seen_named) {
                        type_error(arg, "positional argument after named argument");
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
                        type_error(e, buf);
                    }
                }
            }
            U32 max_pos = nparam - (kwi >= 0 ? 1 : 0);
            if (vi < 0 && pos_idx > max_pos) {
                char buf[128];
                snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d",
                         nparam, pos_idx);
                type_error(e, buf);
            }
            // Rebuild children: callee + args_before_variadic + variadic_args + args_after_variadic
            Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
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
                        type_error(arg, buf);
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
                    type_error(arg, buf);
                } else if ((ptype.tag == TilType_TAG_Struct || ptype.tag == TilType_TAG_Enum) &&
                           (arg->struct_name).count > 0 && !Str_eq(ptype_name, &arg->struct_name)) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             ((Param*)Vec_get(&fdef->data.data.FuncDef.params, &(USize){(USize)(pi)}))->name.c_str,
                             ptype_name->c_str, arg->struct_name.c_str);
                    type_error(arg, buf);
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
                type_error(method_arg, "dyn_call method argument must be a string literal");
            }
        }
        // array/vec builtins: type_name (1st arg) must be a string literal
        if (((name->count == 5 && memcmp(name->c_str, "array", 5) == 0) || (name->count == 3 && memcmp(name->c_str, "vec", 3) == 0)) &&
            e->children.count >= 2) {
            Expr *type_arg = Expr_child(e, &(USize){(USize)(1)});
            if (type_arg->data.tag != ExprData_TAG_LiteralStr) {
                type_error(type_arg, "array/vec type_name argument must be a string literal");
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
                    type_error(Expr_child(e, &(USize){(USize)(ci)}), buf);
                } else if (!pown && Expr_child(e, &(USize){(USize)(ci)})->is_own_arg) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                             _pp2->name.c_str);
                    type_error(Expr_child(e, &(USize){(USize)(ci)}), buf);
                }
                if (pown && Expr_child(e, &(USize){(USize)(ci)})->data.tag == ExprData_TAG_Ident) {
                    ScopeFind *_sf_ab2 = TypeScope_find(scope, &Expr_child(e, &(USize){(USize)(ci)})->data.data.Ident);
                    TypeBinding *ab = _sf_ab2->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ab2) : NULL;
                    if (ab && ab->is_ref) type_error(Expr_child(e, &(USize){(USize)(ci)}), "cannot pass ref variable to 'own' parameter; use .clone() to make an owned copy");
                }
                if (pown && Expr_child(e, &(USize){(USize)(ci)})->data.tag == ExprData_TAG_LiteralNull)
                    type_error(Expr_child(e, &(USize){(USize)(ci)}), "cannot pass null to 'own' parameter");
                if (_pp2->is_shallow && Expr_child(e, &(USize){(USize)(ci)})->data.tag == ExprData_TAG_LiteralNull)
                    type_error(Expr_child(e, &(USize){(USize)(ci)}), "cannot pass null to 'shallow' parameter");
                ci++;
            }
        }
        // Resolve return type from scope (covers builtins and user-defined)
        TilType fn_type = *TypeScope_get_type(scope, name);
        if (fn_type.tag == TilType_TAG_Unknown) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined function '%s'", name->c_str);
            type_error(e, buf);
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
                    type_error(e, buf);
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
                        type_error(e, buf);
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
        Bool debug_exempt = current_mode && current_mode->debug_prints &&
            ((name->count == 5 && memcmp(name->c_str, "print", 5) == 0) || (name->count == 7 && memcmp(name->c_str, "println", 7) == 0));
        if (fn_type.tag != TilType_TAG_FuncPtr &&
            in_func && TypeScope_is_proc(scope, name) == 1 && !(name->count == 5 && memcmp(name->c_str, "panic", 5) == 0) && !debug_exempt) {
            char buf[128];
            snprintf(buf, sizeof(buf), "func cannot call proc '%s'", name->c_str);
            type_error(e, buf);
        }
        // Check: test functions cannot be called by anyone
        if (TypeScope_is_proc(scope, name) == 2) {
            char buf[128];
            snprintf(buf, sizeof(buf), "test functions cannot be called ('%s')", name->c_str);
            type_error(e, buf);
        }
        done_fcall:
        break;
    }
    case ExprData_TAG_FieldAccess: {
        infer_expr(scope, Expr_child(e, &(USize){(USize)(0)}), in_func);
        Expr *obj = Expr_child(e, &(USize){(USize)(0)});
        if (obj->struct_name.count > 0) {
            Expr *sdef = TypeScope_get_struct(scope, &obj->struct_name);
            if (sdef) {
                Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
                Str *fname = &e->data.data.Ident;
                Bool found = 0;
                for (U32 i = 0; i < body->children.count; i++) {
                    Expr *field = Expr_child(body, &(USize){(USize)(i)});
                    // Skip variant registry entries (non-namespace) in enum bodies
                    if (sdef->data.tag == ExprData_TAG_EnumDef && !field->data.data.Decl.is_namespace)
                        continue;
                    if (Str_eq(&field->data.data.Decl.name, fname)) {
                        e->til_type = field->til_type;
                        e->is_ns_field = field->data.data.Decl.is_namespace;
                        e->is_own_field = field->data.data.Decl.is_own || field->data.data.Decl.is_ref;
                        e->is_ref_field = field->data.data.Decl.is_ref;
                        if (field->til_type.tag == TilType_TAG_Struct || field->til_type.tag == TilType_TAG_Enum) {
                            Str *field_sname = &Expr_child(field, &(USize){(USize)(0)})->struct_name;
                            if (field_sname->count > 0) e->struct_name = *Str_clone(field_sname);
                        } else {
                            if (obj->struct_name.count > 0) e->struct_name = *Str_clone(&obj->struct_name);
                        }
                        // Enum variant access: override type to enum for:
                        // 1. I64 literal variants (simple enums)
                        // 2. Zero-arg ext_func constructors (no-payload in payload enums)
                        // 3. Payload variant constructors used bare (Shape.Dot without args)
                        if (sdef->data.tag == ExprData_TAG_EnumDef &&
                            field->data.data.Decl.is_namespace &&
                            field->children.count > 0) {
                            Expr *fc = Expr_child(field, &(USize){(USize)(0)});
                            if (fc->data.tag != ExprData_TAG_FuncDef) {
                                // I64 literal variant
                                e->til_type = (TilType){TilType_TAG_Enum};
                                if (obj->struct_name.count > 0) e->struct_name = *Str_clone(&obj->struct_name);
                            } else if (fc->data.data.FuncDef.func_type.tag == FuncType_TAG_ExtFunc &&
                                       (fc->data.data.FuncDef.return_type).count > 0 &&
                                       Str_eq(&fc->data.data.FuncDef.return_type, &obj->struct_name)) {
                                // Variant constructor (zero-arg or payload) -- bare reference
                                e->til_type = (TilType){TilType_TAG_Enum};
                                if (obj->struct_name.count > 0) e->struct_name = *Str_clone(&obj->struct_name);
                            }
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "%s '%s' has no field '%s'",
                             sdef->data.tag == ExprData_TAG_EnumDef ? "enum" : "struct",
                             obj->struct_name.c_str, fname->c_str);
                    type_error(e, buf);
                    e->til_type = (TilType){TilType_TAG_Unknown};
                }
            }
        } else {
            type_error(e, "field access on non-struct value");
            e->til_type = (TilType){TilType_TAG_Unknown};
        }
        break;
    }
    case ExprData_TAG_MapLit:
        for (U32 i = 0; i < e->children.count; i++)
            infer_expr(scope, Expr_child(e, &(USize){(USize)(i)}), in_func);
        e->til_type = (TilType){TilType_TAG_Struct};
        e->struct_name = (Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT};
        break;
    case ExprData_TAG_SetLit:
        for (U32 i = 0; i < e->children.count; i++)
            infer_expr(scope, Expr_child(e, &(USize){(USize)(i)}), in_func);
        e->til_type = (TilType){TilType_TAG_Struct};
        e->struct_name = (Str){.c_str = (U8*)"Set", .count = 3, .cap = CAP_LIT};
        break;
    case ExprData_TAG_NamedArg:
        // Infer the value inside the named arg (child[0])
        if (e->children.count > 0) {
            infer_expr(scope, Expr_child(e, &(USize){(USize)(0)}), in_func);
            Expr *val = Expr_child(e, &(USize){(USize)(0)});
            e->til_type = val->til_type;
            if (val->struct_name.count > 0) e->struct_name = *Str_clone(&val->struct_name);
        }
        break;
    default:
        e->til_type = (TilType){TilType_TAG_Unknown};
        break;
    }
}

// --- Collection literal helpers ---

// --- Set literal desugaring ---
// Transforms s := {v1, v2, v3} into:
//   mut s := Set.new(elem_type, elem_size)
//   Set.add(s, own v1)
//   Set.add(s, own v2)
//   Set.add(s, own v3)

static void desugar_set_literals(Expr *body, TypeScope *scope) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl || stmt->children.count == 0 ||
            Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_SetLit) {
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        changed = 1;
        Expr *set_lit = Expr_child(stmt, &(USize){(USize)(0)});
        U32 line = set_lit->line, col = set_lit->col;
        Str *path = &set_lit->path;
        Str *var_name = &stmt->data.data.Decl.name;

        if (set_lit->children.count == 0) {
            type_error(set_lit, "set literal must have at least one element");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Get element type from first entry
        Expr *first = Expr_child(set_lit, &(USize){(USize)(0)});
        Str *elem_type = type_to_name(&first->til_type, &first->struct_name);
        if (elem_type->count == 0) {
            type_error(first, "set literal: cannot determine element type");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Validate element type has cmp
        if (!type_has_cmp(scope, elem_type)) {
            char buf[128];
            snprintf(buf, sizeof(buf), "set literal: element type '%s' must implement cmp", elem_type->c_str);
            type_error(first, buf);
        }

        // Validate all elements have consistent type
        for (U32 j = 1; j < set_lit->children.count; j++) {
            Expr *v = Expr_child(set_lit, &(USize){(USize)(j)});
            Str *vt = type_to_name(&v->til_type, &v->struct_name);
            if (vt->count == 0 || !Str_eq(vt, elem_type))
                type_error(v, "set literal: all elements must be the same type");
        }

        // Build: mut var_name := Set.new(elem_type_str, ElemType.size())
        Expr *new_call = make_ns_call("Set", "new", (TilType){TilType_TAG_Struct},
                                       &(Str){.c_str = (U8*)"Set", .count = 3, .cap = CAP_LIT}, set_lit);
        Expr *et_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        et_str->data.data.LiteralStr = *Str_clone(elem_type);
        et_str->til_type = (TilType){TilType_TAG_Struct};
        et_str->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, et_str);
        Expr *esz = make_ns_call((const char *)elem_type->c_str, "size", *usize_type(scope), NULL, set_lit);
        Expr_add_child(new_call, esz);

        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, stmt->line, stmt->col, path);
        decl->data.data.Decl.name = *var_name;
        decl->data.data.Decl.is_mut = true;
        decl->til_type = (TilType){TilType_TAG_Struct};
        Expr_add_child(decl, new_call);

        TypeScope_set(scope, var_name, &(TilType){TilType_TAG_Struct}, -1, 1, stmt->line, stmt->col, 0, 0);
        TypeBinding *vb = Map_get(&scope->bindings, var_name);
        vb->struct_name = *Str_clone(&(Str){.c_str = (U8*)"Set", .count = 3, .cap = CAP_LIT});

        Vec_push(&new_ch, decl);

        // Build .add calls for each element
        for (U32 j = 0; j < set_lit->children.count; j++) {
            Expr *add_call = make_ns_call("Set", "add", (TilType){TilType_TAG_None}, NULL, set_lit);
            Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_id->data.data.Ident = *var_name;
            self_id->til_type = (TilType){TilType_TAG_Struct};
            self_id->struct_name = (Str){.c_str = (U8*)"Set", .count = 3, .cap = CAP_LIT};
            Expr_add_child(add_call, self_id);
            Expr *val = Expr_clone(Expr_child(set_lit, &(USize){(USize)(j)}));
            val->is_own_arg = true;
            Expr_add_child(add_call, val);
            Vec_push(&new_ch, add_call);
        }
    }

    if (changed) {
        Vec_delete(&body->children, &(Bool){0});
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch, &(Bool){0});
    }
}

// --- Map literal desugaring ---
// Transforms m := {k1: v1, k2: v2} into:
//   mut m := Map.new(key_type, key_size, val_type, val_size)
//   Map.set(m, own k1, own v1)
//   Map.set(m, own k2, own v2)

static void desugar_map_literals(Expr *body, TypeScope *scope) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
        // Only handle: name := {k: v, ...}
        if (stmt->data.tag != ExprData_TAG_Decl || stmt->children.count == 0 ||
            Expr_child(stmt, &(USize){(USize)(0)})->data.tag != ExprData_TAG_MapLit) {
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        changed = 1;
        Expr *map_lit = Expr_child(stmt, &(USize){(USize)(0)});
        U32 line = map_lit->line, col = map_lit->col;
        Str *path = &map_lit->path;
        Str *var_name = &stmt->data.data.Decl.name;
        U32 n_pairs = map_lit->children.count / 2;

        if (map_lit->children.count == 0) {
            type_error(map_lit, "map literal must have at least one entry");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        if (map_lit->children.count % 2 != 0) {
            type_error(map_lit, "map literal has mismatched key/value pairs");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Get key/val types from first entry (already inferred)
        Expr *first_key = Expr_child(map_lit, &(USize){(USize)(0)});
        Expr *first_val = Expr_child(map_lit, &(USize){(USize)(1)});
        Str *key_type = type_to_name(&first_key->til_type, &first_key->struct_name);
        Str *val_type = type_to_name(&first_val->til_type, &first_val->struct_name);

        if (key_type->count == 0) {
            type_error(first_key, "map literal: cannot determine key type");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        if (val_type->count == 0) {
            type_error(first_val, "map literal: cannot determine value type");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Validate key type has cmp
        if (!type_has_cmp(scope, key_type)) {
            char buf[128];
            snprintf(buf, sizeof(buf), "map literal: key type '%s' must implement cmp", key_type->c_str);
            type_error(first_key, buf);
        }

        // Validate all entries have consistent types
        for (U32 j = 2; j < map_lit->children.count; j += 2) {
            Expr *k = Expr_child(map_lit, &(USize){(USize)(j)});
            Expr *v = Expr_child(map_lit, &(USize){(USize)(j + 1)});
            Str *kt = type_to_name(&k->til_type, &k->struct_name);
            Str *vt = type_to_name(&v->til_type, &v->struct_name);
            if (kt->count == 0 || !Str_eq(kt, key_type))
                type_error(k, "map literal: all keys must be the same type");
            if (vt->count == 0 || !Str_eq(vt, val_type))
                type_error(v, "map literal: all values must be the same type");
        }

        // Build: mut var_name := Map.new(key_type_str, KeyType.size(), val_type_str, ValType.size())
        Expr *new_call = make_ns_call("Map", "new", (TilType){TilType_TAG_Struct},
                                       &(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT}, map_lit);
        // Arg 1: key_type string
        Expr *kt_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        kt_str->data.data.LiteralStr = *Str_clone(key_type);
        kt_str->til_type = (TilType){TilType_TAG_Struct};
        kt_str->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, kt_str);
        // Arg 2: KeyType.size()
        Expr *ksz = make_ns_call((const char *)key_type->c_str, "size", *usize_type(scope), NULL, map_lit);
        Expr_add_child(new_call, ksz);
        // Arg 3: val_type string
        Expr *vt_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        vt_str->data.data.LiteralStr = *Str_clone(val_type);
        vt_str->til_type = (TilType){TilType_TAG_Struct};
        vt_str->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, vt_str);
        // Arg 4: ValType.size()
        Expr *vsz = make_ns_call((const char *)val_type->c_str, "size", *usize_type(scope), NULL, map_lit);
        Expr_add_child(new_call, vsz);

        // Build declaration node (mut, so .set can work)
        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, stmt->line, stmt->col, path);
        decl->data.data.Decl.name = *var_name;
        decl->data.data.Decl.is_mut = true;
        decl->til_type = (TilType){TilType_TAG_Struct};
        Expr_add_child(decl, new_call);

        // Register in scope
        TypeScope_set(scope, var_name, &(TilType){TilType_TAG_Struct}, -1, 1, stmt->line, stmt->col, 0, 0);
        TypeBinding *vb = Map_get(&scope->bindings, var_name);
        vb->struct_name = *Str_clone(&(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT});

        Vec_push(&new_ch, decl);

        // Build .set calls for each key-value pair
        for (U32 j = 0; j < n_pairs; j++) {
            Expr *set_call = make_ns_call("Map", "set", (TilType){TilType_TAG_None}, NULL, map_lit);
            // Arg: self
            Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_id->data.data.Ident = *var_name;
            self_id->til_type = (TilType){TilType_TAG_Struct};
            self_id->struct_name = (Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT};
            Expr_add_child(set_call, self_id);
            // Arg: own key
            Expr *key = Expr_clone(Expr_child(map_lit, &(USize){(USize)(j * 2)}));
            key->is_own_arg = true;
            Expr_add_child(set_call, key);
            // Arg: own val
            Expr *mval = Expr_clone(Expr_child(map_lit, &(USize){(USize)(j * 2 + 1)}));
            mval->is_own_arg = true;
            Expr_add_child(set_call, mval);

            Vec_push(&new_ch, set_call);
        }
    }

    if (changed) {
        Vec_delete(&body->children, &(Bool){0});
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch, &(Bool){0});
    }
}

// --- Variadic call desugaring ---
// Transforms variadic function calls into Array.new + Array.set + normal call.
// Must run before hoisting so that synthetic Array calls get hoisted too.

// Create a namespace method call: StructName.method(args...)
static Expr *make_ns_call(const char *sname, const char *method,
                           TilType ret_type, Str *ret_sname, Expr *src) {
    I32 line = src->line, col = src->col;
    Str *path = &src->path;
    Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
    call->til_type = ret_type;
    if (ret_sname && ret_sname->count > 0) call->struct_name = *Str_clone(ret_sname);
    Expr *type_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
    type_id->data.data.Ident = *Str_clone(&(Str){.c_str = (U8*)(sname), .count = (U64)strlen((const char*)(sname)), .cap = CAP_VIEW});
    type_id->struct_name = *Str_clone(&(Str){.c_str = (U8*)(sname), .count = (U64)strlen((const char*)(sname)), .cap = CAP_VIEW});
    Expr *fa = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
    fa->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(method), .count = (U64)strlen((const char*)(method)), .cap = CAP_VIEW});
    fa->is_ns_field = true;
    Expr_add_child(fa, type_id);
    Expr_add_child(call, fa);
    return call;
}

static void desugar_variadic_calls(Expr *body, TypeScope *scope) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
        Expr *fcall = find_variadic_fcall(stmt);
        if (!fcall) {
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        changed = 1;
        I32 vi = fcall->data.data.FCall.variadic_index;
        U32 vc = fcall->data.data.FCall.variadic_count;
        I32 line = fcall->line, col = fcall->col;
        Str *path = &fcall->path;

        // Find element type from func_def
        Str *elem_type = NULL;
        Expr *callee = Expr_child(fcall, &(USize){(USize)(0)});
        if (callee->data.tag == ExprData_TAG_Ident) {
            ScopeFind *_sf_tb2 = TypeScope_find(scope, &callee->data.data.Ident);
            TypeBinding *tb = _sf_tb2->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_tb2) : NULL;
            if (tb && tb->func_def) {
                I32 fvi = tb->func_def->data.data.FuncDef.variadic_index;
                if (fvi >= 0)
                    elem_type = &((Param*)Vec_get(&tb->func_def->data.data.FuncDef.params, &(USize){(USize)(fvi)}))->ptype;
            }
        } else if (callee->data.tag == ExprData_TAG_FieldAccess && callee->is_ns_field) {
            Expr *type_node = Expr_child(callee, &(USize){(USize)(0)});
            if (type_node->data.tag == ExprData_TAG_Ident) {
                Expr *sdef = TypeScope_get_struct(scope, &type_node->data.data.Ident);
                if (sdef) {
                    Expr *sbody = Expr_child(sdef, &(USize){(USize)(0)});
                    for (U32 j = 0; j < sbody->children.count; j++) {
                        Expr *f = Expr_child(sbody, &(USize){(USize)(j)});
                        if (f->data.tag == ExprData_TAG_Decl && f->data.data.Decl.is_namespace &&
                            Str_eq(&f->data.data.Decl.name, &callee->data.data.Ident) &&
                            Expr_child(f, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef) {
                            I32 fvi = Expr_child(f, &(USize){(USize)(0)})->data.data.FuncDef.variadic_index;
                            if (fvi >= 0)
                                elem_type = &((Param*)Vec_get(&Expr_child(f, &(USize){(USize)(0)})->data.data.FuncDef.params, &(USize){(USize)(fvi)}))->ptype;
                            break;
                        }
                    }
                }
            }
        }
        if (!elem_type) {
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Pure splat: f(fixed, ..arr) — pass array directly, skip Array construction
        if (vc == 1 && Expr_child(fcall, &(USize){(USize)(vi)})->is_splat) {
            Expr *splat = Expr_child(fcall, &(USize){(USize)(vi)});
            splat->is_splat = false;
            // Clone if ident so caller keeps their copy; otherwise clone borrowed ref
            if (splat->data.tag == ExprData_TAG_Ident) {
                splat = make_clone_call("Array", (TilType){TilType_TAG_Struct}, splat, splat);
            } else {
                splat = Expr_clone(splat);
            }
            splat->is_own_arg = true;
            // Rebuild fcall children replacing variadic slot with splat
            Vec fcall_new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fcall_new_ch = *_vp; free(_vp); }
            for (U32 j = 0; j < fcall->children.count; j++) {
                if ((I32)j == vi) {
                    Vec_push(&fcall_new_ch, splat);
                } else {
                    Expr *ch = Expr_child(fcall, &(USize){(USize)(j)});
                    Vec_push(&fcall_new_ch, Expr_clone(ch));
                }
            }
            Vec_delete(&fcall->children, &(Bool){0});
            fcall->children = fcall_new_ch;
            fcall->data.data.FCall.variadic_index = -1;
            fcall->data.data.FCall.variadic_count = 0;
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Create temp variable name
        char buf[128];
        snprintf(buf, sizeof(buf), "_va_Array_%d", _va_counter++);
        Str *va_name = Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});

        // 1. _va := Array.new(elem_type_str, ElemType.size(), count)
        Expr *new_call = make_ns_call("Array", "new", (TilType){TilType_TAG_Struct},
                                       &(Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT}, fcall);
        // Arg: elem_type string
        Expr *et = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        et->data.data.LiteralStr = *Str_clone(elem_type);
        et->til_type = (TilType){TilType_TAG_Struct};
        et->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, et);
        // Arg: ElemType.size()
        Expr *sz = make_ns_call((const char *)elem_type->c_str, "size", *usize_type(scope),
                                 NULL, fcall);
        Expr_add_child(new_call, sz);
        // Arg: count
        Expr *cap = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
        char cap_buf[16];
        snprintf(cap_buf, sizeof(cap_buf), "%d", vc);
        cap->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(cap_buf), .count = (U64)strlen((const char*)(cap_buf)), .cap = CAP_VIEW});
        cap->til_type = *usize_type(scope);
        Expr_add_child(new_call, cap);

        // DECL _va := Array.new(...)
        Expr *va_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        va_decl->data.data.Decl.name = *va_name;
        va_decl->til_type = (TilType){TilType_TAG_Struct};
        Expr_add_child(va_decl, new_call);

        // Register _va in scope
        TypeScope_set(scope, va_name, &(TilType){TilType_TAG_Struct}, -1, 0, line, col, 0, 0);
        TypeBinding *vab = Map_get(&scope->bindings, va_name);
        vab->struct_name = *Str_clone(&(Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT});

        Vec_push(&new_ch, va_decl);

        // 2. Array.set calls for each variadic arg
        for (U32 j = 0; j < vc; j++) {
            Expr *set_call = make_ns_call("Array", "set", (TilType){TilType_TAG_None},
                                           NULL, fcall);
            // Arg: self = _va
            Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_id->data.data.Ident = *va_name;
            self_id->til_type = (TilType){TilType_TAG_Struct};
            self_id->struct_name = (Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT};
            Expr_add_child(set_call, self_id);
            // Arg: index
            Expr *idx = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
            char idx_buf[16];
            snprintf(idx_buf, sizeof(idx_buf), "%d", j);
            idx->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(idx_buf), .count = (U64)strlen((const char*)(idx_buf)), .cap = CAP_VIEW});
            idx->til_type = *usize_type(scope);
            Expr_add_child(set_call, idx);
            // Arg: val — clone idents and field accesses so Array_set
            // doesn't free the caller's variable or an interior pointer
            Expr *val = Expr_child(fcall, &(USize){(USize)(vi + j)});
            if (val->data.tag == ExprData_TAG_Ident || val->data.tag == ExprData_TAG_FieldAccess) {
                Str *tname = type_to_name(&val->til_type, &val->struct_name);
                if (tname->count > 0)
                    val = make_clone_call((const char *)tname->c_str, val->til_type, val, val);
                else
                    val = Expr_clone(val);
            } else {
                val = Expr_clone(val);
            }
            val->is_own_arg = true;
            Expr_add_child(set_call, val);

            Vec_push(&new_ch, set_call);
        }

        // 3. Replace variadic args in FCALL with _va ident
        Vec fcall_new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fcall_new_ch = *_vp; free(_vp); }
        Bool va_inserted = 0;
        for (U32 j = 0; j < fcall->children.count; j++) {
            if ((I32)j >= vi && (I32)j < vi + (I32)vc) {
                if (!va_inserted) {
                    Expr *va_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    va_id->data.data.Ident = *va_name;
                    va_id->til_type = (TilType){TilType_TAG_Struct};
                    va_id->struct_name = (Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT};
                    va_id->is_own_arg = true;
                    Vec_push(&fcall_new_ch, va_id);
                    va_inserted = 1;
                }
                continue;
            }
            // Insert _va before post-variadic args when vc==0
            if ((I32)j == vi && !va_inserted) {
                Expr *va_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                va_id->data.data.Ident = *va_name;
                va_id->til_type = (TilType){TilType_TAG_Struct};
                va_id->struct_name = (Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT};
                va_id->is_own_arg = true;
                Vec_push(&fcall_new_ch, va_id);
                va_inserted = 1;
            }
            Expr *ch = Expr_child(fcall, &(USize){(USize)(j)});
            Vec_push(&fcall_new_ch, Expr_clone(ch));
        }
        // Insert _va at end if variadic was last param and vc==0
        if (!va_inserted) {
            Expr *va_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            va_id->data.data.Ident = *va_name;
            va_id->til_type = (TilType){TilType_TAG_Struct};
            va_id->struct_name = (Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT};
            va_id->is_own_arg = true;
            Vec_push(&fcall_new_ch, va_id);
        }
        Vec_delete(&fcall->children, &(Bool){0});
        fcall->children = fcall_new_ch;
        fcall->data.data.FCall.variadic_index = -1;
        fcall->data.data.FCall.variadic_count = 0;

        // Insert the original statement
        Vec_push(&new_ch, Expr_clone(stmt));
    }

    if (changed) {
        Vec_delete(&body->children, &(Bool){0});
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch, &(Bool){0});
    }
}

// --- Kwargs call desugaring ---
// Transforms kwargs function calls into Map.new + Map.set + normal call.

static void desugar_kwargs_calls(Expr *body, TypeScope *scope) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
        Expr *fcall = find_kwargs_fcall(stmt);
        if (!fcall) {
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        changed = 1;
        I32 ki = fcall->data.data.FCall.kwargs_index;
        U32 kc = fcall->data.data.FCall.kwargs_count;
        I32 line = fcall->line, col = fcall->col;
        Str *path = &fcall->path;

        // Create temp variable name
        char buf[32];
        snprintf(buf, sizeof(buf), "_kw%d", _kw_counter++);
        Str *kw_name = Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});

        // Find the widest value type among kwargs args for val_size
        const char *val_size_type = "I64"; // default: 8 bytes for primitives
        for (U32 j = 0; j < kc; j++) {
            Expr *na = Expr_child(fcall, &(USize){(USize)(ki + j)});
            Expr *v = Expr_child(na, &(USize){(USize)(0)});
            if (v->til_type.tag == TilType_TAG_Struct && v->struct_name.count > 0) {
                val_size_type = (const char *)v->struct_name.c_str;
                break; // struct types are bigger than primitives
            }
        }

        // 1. _kw := Map.new("Str", Str.size(), "", MaxType.size())
        // Use empty val_type to skip dyn_call delete/clone on values
        Expr *new_call = make_ns_call("Map", "new", (TilType){TilType_TAG_Struct},
                                       &(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT}, fcall);
        // Arg: key_type = "Str"
        Expr *kt = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        kt->data.data.LiteralStr = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        kt->til_type = (TilType){TilType_TAG_Struct};
        kt->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, kt);
        // Arg: Str.size()
        Expr *ksz = make_ns_call("Str", "size", *usize_type(scope), NULL, fcall);
        Expr_add_child(new_call, ksz);
        // Arg: val_type = "" (skip dyn_call on values)
        Expr *vt = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        vt->data.data.LiteralStr = (Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
        vt->til_type = (TilType){TilType_TAG_Struct};
        vt->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, vt);
        // Arg: val_size = widest type's .size()
        Expr *vsz = make_ns_call(val_size_type, "size", *usize_type(scope), NULL, fcall);
        Expr_add_child(new_call, vsz);

        // DECL _kw := Map.new(...)
        Expr *kw_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        kw_decl->data.data.Decl.name = *kw_name;
        kw_decl->til_type = (TilType){TilType_TAG_Struct};
        Expr_add_child(kw_decl, new_call);

        // Register _kw in scope
        TypeScope_set(scope, kw_name, &(TilType){TilType_TAG_Struct}, -1, 0, line, col, 0, 0);
        TypeBinding *kwb = Map_get(&scope->bindings, kw_name);
        kwb->struct_name = *Str_clone(&(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT});

        Vec_push(&new_ch, kw_decl);

        // 2. Map.set calls for each kwargs arg
        for (U32 j = 0; j < kc; j++) {
            Expr *named_arg = Expr_child(fcall, &(USize){(USize)(ki + j)});
            // named_arg is ExprData_TAG_NamedArg with str_val = key name, child[0] = value
            Str *key_name = &named_arg->data.data.NamedArg;
            Expr *val = Expr_child(named_arg, &(USize){(USize)(0)});

            Expr *set_call = make_ns_call("Map", "set", (TilType){TilType_TAG_None}, NULL, fcall);
            // Arg: self = _kw (mut)
            Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_id->data.data.Ident = *kw_name;
            self_id->til_type = (TilType){TilType_TAG_Struct};
            self_id->struct_name = (Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT};
            Expr_add_child(set_call, self_id);
            // Arg: key string
            Expr *key_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
            key_lit->data.data.LiteralStr = *Str_clone(key_name);
            key_lit->til_type = (TilType){TilType_TAG_Struct};
            key_lit->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
            key_lit->is_own_arg = true;
            Expr_add_child(set_call, key_lit);
            // Arg: value (clone idents to prevent double-free)
            if (val->data.tag == ExprData_TAG_Ident || val->data.tag == ExprData_TAG_FieldAccess) {
                Str *tname = type_to_name(&val->til_type, &val->struct_name);
                if (tname->count > 0)
                    val = make_clone_call((const char *)tname->c_str, val->til_type, val, val);
                else
                    val = Expr_clone(val);
            } else {
                val = Expr_clone(val);
            }
            val->is_own_arg = true;
            Expr_add_child(set_call, val);

            Vec_push(&new_ch, set_call);
        }

        // 3. Replace kwargs args in FCALL with _kw ident
        Vec fcall_new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); fcall_new_ch = *_vp; free(_vp); }
        Bool kw_inserted = 0;
        for (U32 j = 0; j < fcall->children.count; j++) {
            if ((I32)j >= ki && (I32)j < ki + (I32)kc) {
                if (!kw_inserted) {
                    Expr *kw_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                    kw_id->data.data.Ident = *kw_name;
                    kw_id->til_type = (TilType){TilType_TAG_Struct};
                    kw_id->struct_name = (Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT};
                    kw_id->is_own_arg = true;
                    Vec_push(&fcall_new_ch, kw_id);
                    kw_inserted = 1;
                }
                continue;
            }
            // Insert _kw when kc==0 (no kwargs args, but still need empty Map)
            if ((I32)j == ki && !kw_inserted) {
                Expr *kw_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                kw_id->data.data.Ident = *kw_name;
                kw_id->til_type = (TilType){TilType_TAG_Struct};
                kw_id->struct_name = (Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT};
                kw_id->is_own_arg = true;
                Vec_push(&fcall_new_ch, kw_id);
                kw_inserted = 1;
            }
            Expr *ch = Expr_child(fcall, &(USize){(USize)(j)});
            Vec_push(&fcall_new_ch, Expr_clone(ch));
        }
        // Insert _kw at end if kwargs was last param and kc==0
        if (!kw_inserted) {
            Expr *kw_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            kw_id->data.data.Ident = *kw_name;
            kw_id->til_type = (TilType){TilType_TAG_Struct};
            kw_id->struct_name = (Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT};
            kw_id->is_own_arg = true;
            Vec_push(&fcall_new_ch, kw_id);
        }
        Vec_delete(&fcall->children, &(Bool){0});
        fcall->children = fcall_new_ch;
        fcall->data.data.FCall.kwargs_index = -1;
        fcall->data.data.FCall.kwargs_count = 0;

        // Insert the original statement
        Vec_push(&new_ch, Expr_clone(stmt));
    }

    if (changed) {
        Vec_delete(&body->children, &(Bool){0});
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch, &(Bool){0});
    }
}

// --- Argument hoisting ---


// Check if a function call returns ref

// Create a temp decl for an expression, register in scope, return the replacement ident.
// Adds the decl to the hoisted list.
static Expr *hoist_to_temp(Expr *val, Expr ***hoisted, U32 *nhoisted, U32 *cap, TypeScope *scope) {
    char name_buf[128];
    Str *tp = type_prefix(&val->til_type, &val->struct_name);
    snprintf(name_buf, sizeof(name_buf), "_t_%s_%d", tp->c_str, hoist_counter++);
    Str *tname = Str_clone(&(Str){.c_str = (U8*)(name_buf), .count = (U64)strlen((const char*)(name_buf)), .cap = CAP_VIEW});
    Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, val->line, val->col, &val->path);
    decl->data.data.Decl.name = *tname;
    decl->data.data.Decl.explicit_type = (Str){0};
    decl->data.data.Decl.is_mut = false;
    decl->data.data.Decl.is_namespace = false;
    decl->til_type = val->til_type;
    if (val->struct_name.count > 0) decl->struct_name = *Str_clone(&val->struct_name);
    U32 val_line = val->line;
    U32 val_col = val->col;
    Str val_path = val->path;
    TilType val_type = val->til_type;
    Str val_struct_name = val->struct_name;
    Bool val_is_own_arg = val->is_own_arg;
    Bool val_is_ref = (val->data.tag == ExprData_TAG_FCall && fcall_returns_ref(val, scope));
    Expr_add_child(decl, Expr_clone(val));
    Expr *ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, val_line, val_col, &val_path);
    ident->data.data.Ident = *tname;
    ident->til_type = val_type;
    if (val_struct_name.count > 0) ident->struct_name = *Str_clone(&val_struct_name);
    ident->is_own_arg = val_is_own_arg;
    TypeScope_set(scope, tname, &val_type, -1, 0, val_line, val_col, 0, 0);
    TypeBinding *tb = Map_get(&scope->bindings, tname);
    tb->struct_name = *Str_clone(&val_struct_name);
    if (val_is_ref) {
        decl->data.data.Decl.is_ref = true;
        if (tb) tb->is_ref = 1;
    }
    if (*nhoisted >= *cap) {
        *cap = *cap ? *cap * 2 : 8;
        *hoisted = realloc(*hoisted, *cap * sizeof(Expr *));
    }
    (*hoisted)[(*nhoisted)++] = decl;
    return ident;
}

// Walk expression tree depth-first. For each ExprData_TAG_FCall, hoist any arg that is itself a ExprData_TAG_FCall.
// Does NOT recurse into scope boundaries (func/struct defs, bodies).
static void hoist_expr(Expr *e, Expr ***hoisted, U32 *nhoisted, U32 *cap, TypeScope *scope) {
    // Don't recurse into scope boundaries -- those have their own infer_body calls
    if (e->data.tag == ExprData_TAG_FuncDef || e->data.tag == ExprData_TAG_StructDef || e->data.tag == ExprData_TAG_EnumDef || e->data.tag == ExprData_TAG_Body) return;
    // Recurse into children first (depth-first: inner fcalls hoisted before outer)
    for (U32 i = 0; i < e->children.count; i++) {
        hoist_expr(Expr_child(e, &(USize){(USize)(i)}), hoisted, nhoisted, cap, scope);
    }
    if (e->data.tag != ExprData_TAG_FCall) return;

    // For struct constructors, find field info to skip hoisting inline compound args
    Expr *ctor_body = NULL;
    if ((e->struct_name).count > 0 && e->children.count > 0 &&
        Str_eq(&Expr_child(e, &(USize){(USize)(0)})->data.data.Ident, &e->struct_name)) {
        Expr *sdef = TypeScope_get_struct(scope, &e->struct_name);
        if (sdef) ctor_body = Expr_child(sdef, &(USize){(USize)(0)});
    }

    // Check each argument (children[1..n])
    // dyn_call variants: don't hoist the method arg (2nd) — codegen needs it as a literal
    Bool is_dyn_call = 0;
    if (Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
        Str *cn = &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
        is_dyn_call = (cn->count == 8 && memcmp(cn->c_str, "dyn_call", 8) == 0) || (cn->count == 12 && memcmp(cn->c_str, "dyn_call_ret", 12) == 0) ||
                      (cn->count == 14 && memcmp(cn->c_str, "dyn_has_method", 14) == 0) || (cn->count == 6 && memcmp(cn->c_str, "dyn_fn", 6) == 0);
    }
    Bool is_array_vec = 0;
    if (Expr_child(e, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
        Str *cn = &Expr_child(e, &(USize){(USize)(0)})->data.data.Ident;
        is_array_vec = (cn->count == 5 && memcmp(cn->c_str, "array", 5) == 0) || (cn->count == 3 && memcmp(cn->c_str, "vec", 3) == 0);
    }
    U32 fi = 0; // instance field index for struct constructors
    for (U32 i = 1; i < e->children.count; i++) {
        if (is_dyn_call && (i == 2 || i == 3)) continue; // keep method and arity as literals
        if (is_array_vec && i == 1) continue; // keep type_name as ExprData_TAG_LiteralStr
        if (Expr_child(e, &(USize){(USize)(i)})->data.tag != ExprData_TAG_FCall &&
            Expr_child(e, &(USize){(USize)(i)})->data.tag != ExprData_TAG_LiteralNum &&
            Expr_child(e, &(USize){(USize)(i)})->data.tag != ExprData_TAG_LiteralStr &&
            Expr_child(e, &(USize){(USize)(i)})->data.tag != ExprData_TAG_LiteralBool) continue;

        // Skip hoisting inline compound field args in struct constructors
        if (ctor_body) {
            // Find the fi-th instance field
            Bool is_own = 0;
            TilType ft = (TilType){TilType_TAG_None};
            for (; fi < ctor_body->children.count; fi++) {
                Expr *field = Expr_child(ctor_body, &(USize){(USize)(fi)});
                if (!field->data.data.Decl.is_namespace) {
                    is_own = field->data.data.Decl.is_own;
                    ft = Expr_child(field, &(USize){(USize)(0)})->til_type;
                    fi++;
                    break;
                }
            }
            if (!is_own && (ft.tag == TilType_TAG_Struct || ft.tag == TilType_TAG_Enum))
                continue; // don't hoist — builder handles directly
        }

        *(Expr*)Vec_get(&e->children, &(USize){(USize)(i)}) = *hoist_to_temp(Expr_clone(Expr_child(e, &(USize){(USize)(i)})), hoisted, nhoisted, cap, scope);
    }
}

static void hoist_fcall_args(Expr *body, TypeScope *scope) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
        // Collect hoisted decls from this statement
        Expr **hoisted = NULL;
        U32 nhoisted = 0, hcap = 0;
        // Walk the appropriate expression tree based on statement type
        switch (stmt->data.tag) {
        case ExprData_TAG_Decl:
            hoist_expr(Expr_child(stmt, &(USize){(USize)(0)}), &hoisted, &nhoisted, &hcap, scope);
            break;
        case ExprData_TAG_FCall:
            hoist_expr(stmt, &hoisted, &nhoisted, &hcap, scope);
            if (stmt->til_type.tag != TilType_TAG_None) {
                hoist_to_temp(stmt, &hoisted, &nhoisted, &hcap, scope);
                stmt = hoisted[--nhoisted];
                *(Expr*)Vec_get(&body->children, &(USize){(USize)(i)}) = *stmt;
            }
            break;
        case ExprData_TAG_Return:
            if (stmt->children.count > 0) {
                hoist_expr(Expr_child(stmt, &(USize){(USize)(0)}), &hoisted, &nhoisted, &hcap, scope);
                if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FCall ||
                    Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_LiteralNum ||
                    Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_LiteralStr ||
                    Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_LiteralBool) {
                    *(Expr*)Vec_get(&stmt->children, &(USize){(USize)(0)}) = *hoist_to_temp(Expr_clone(Expr_child(stmt, &(USize){(USize)(0)})), &hoisted, &nhoisted, &hcap, scope);
                }
            }
            break;
        case ExprData_TAG_Assign: {
            hoist_expr(Expr_child(stmt, &(USize){(USize)(0)}), &hoisted, &nhoisted, &hcap, scope);
            // Skip top-level hoisting for compound-type locals — builder
            // uses pointer-assign (typer inserts delete before reassignment).
            // Keep hoisting for scalars (deref-assign) and params (write-through).
            Bool do_hoist = 1;
            ScopeFind *_sf_ab3 = TypeScope_find(scope, &stmt->data.data.Ident);
            TypeBinding *ab = _sf_ab3->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ab3) : NULL;
            if (ab && !ab->is_param) {
                TilType t = ab->type;
                if (t.tag == TilType_TAG_Struct || t.tag == TilType_TAG_Enum)
                    do_hoist = 0;
            }
            if (do_hoist && (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FCall ||
                Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_LiteralNum ||
                Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_LiteralStr ||
                Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_LiteralBool)) {
                *(Expr*)Vec_get(&stmt->children, &(USize){(USize)(0)}) = *hoist_to_temp(Expr_clone(Expr_child(stmt, &(USize){(USize)(0)})), &hoisted, &nhoisted, &hcap, scope);
            }
            // For mut struct/enum params, replace assignment with swap so
            // ASAP delete of the temp frees the OLD value, not the new one.
            // Re-query: hoist_to_temp may have realloc'd the Map, invalidating ab.
            _sf_ab3 = TypeScope_find(scope, &stmt->data.data.Ident);
            ab = _sf_ab3->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ab3) : NULL;
            if (ab && ab->is_param && ab->is_mut &&
                (ab->type.tag == TilType_TAG_Struct || ab->type.tag == TilType_TAG_Enum)) {
                I32 line = stmt->line, col = stmt->col;
                Str *path = &stmt->path;
                // Build: swap(param, temp, Type.size())
                Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
                call->til_type = (TilType){TilType_TAG_None};
                Expr *fn = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                fn->data.data.Ident = (Str){.c_str = (U8*)"swap", .count = 4, .cap = CAP_LIT};
                Expr_add_child(call, fn);
                // arg0: the param variable
                Expr *a = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                a->data.data.Ident = stmt->data.data.Ident;
                a->til_type = ab->type;
                if (ab->struct_name.count > 0) a->struct_name = *Str_clone(&ab->struct_name);
                Expr_add_child(call, a);
                // arg1: the RHS (hoisted temp ident)
                Expr_add_child(call, Expr_clone(Expr_child(stmt, &(USize){(USize)(0)})));
                // arg2: Type.size() — hoist to temp so builder emits deref correctly
                Str *tname = type_to_name(&ab->type, &ab->struct_name);
                Expr *sz_call = make_ns_call((const char *)tname->c_str, "size", *usize_type(scope), NULL, stmt);
                Expr *sz = hoist_to_temp(sz_call, &hoisted, &nhoisted, &hcap, scope);
                Expr_add_child(call, sz);
                // Replace stmt in-place
                *stmt = *call;
            }
            break;
        }
        case ExprData_TAG_FieldAssign: {
            hoist_expr(Expr_child(stmt, &(USize){(USize)(1)}), &hoisted, &nhoisted, &hcap, scope);
            // Skip hoisting for inline compound fields (same as constructor args)
            Bool fa_hoist = 1;
            if (!stmt->is_own_field) {
                TilType ft = Expr_child(stmt, &(USize){(USize)(1)})->til_type;
                if (ft.tag == TilType_TAG_Struct || ft.tag == TilType_TAG_Enum)
                    fa_hoist = 0;
            }
            if (fa_hoist && (Expr_child(stmt, &(USize){(USize)(1)})->data.tag == ExprData_TAG_FCall ||
                Expr_child(stmt, &(USize){(USize)(1)})->data.tag == ExprData_TAG_LiteralNum ||
                Expr_child(stmt, &(USize){(USize)(1)})->data.tag == ExprData_TAG_LiteralStr ||
                Expr_child(stmt, &(USize){(USize)(1)})->data.tag == ExprData_TAG_LiteralBool)) {
                *(Expr*)Vec_get(&stmt->children, &(USize){(USize)(1)}) = *hoist_to_temp(Expr_clone(Expr_child(stmt, &(USize){(USize)(1)})), &hoisted, &nhoisted, &hcap, scope);
            }
            break;
        }
        case ExprData_TAG_If:
            hoist_expr(Expr_child(stmt, &(USize){(USize)(0)}), &hoisted, &nhoisted, &hcap, scope);
            if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FCall) {
                *(Expr*)Vec_get(&stmt->children, &(USize){(USize)(0)}) = *hoist_to_temp(Expr_clone(Expr_child(stmt, &(USize){(USize)(0)})), &hoisted, &nhoisted, &hcap, scope);
            }
            break;
        // ExprData_TAG_While: skip condition -- hoisting changes loop semantics
        default: break;
        }
        // Insert hoisted decls before the statement
        for (U32 j = 0; j < nhoisted; j++) {
            Vec_push(&new_ch, hoisted[j]);
        }
        free(hoisted);
        // Add original statement
        Vec_push(&new_ch, Expr_clone(stmt));
    }
    if (new_ch.count != body->children.count) {
        Vec_delete(&body->children, &(Bool){0});
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch, &(Bool){0});
    }
}

// --- Delete call insertion ---

// Insert delete calls before field reassignments (own and inline compound)
static void insert_field_deletes(Expr *body) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
        if (stmt->data.tag == ExprData_TAG_FieldAssign) {
            Bool is_own = stmt->is_own_field;
            if (field_assign_needs_delete(stmt)) {
                Expr *del = make_field_delete(stmt, is_own);
                if (del) {
                    Vec_push(&new_ch, del);
                    changed = 1;
                }
            }
        }
        Vec_push(&new_ch, Expr_clone(stmt));
    }
    if (changed) {
        Vec_delete(&body->children, &(Bool){0});
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch, &(Bool){0});
    }
}

static Expr *make_clone_call(const char *type_name, TilType type, Expr *arg, Expr *src) {
    I32 line = src->line, col = src->col;
    Str *path = &src->path;

    Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
    call->til_type = type;
    if (type.tag == TilType_TAG_Struct || type.tag == TilType_TAG_Enum) call->struct_name = *Str_clone(&(Str){.c_str = (U8*)(type_name), .count = (U64)strlen((const char*)(type_name)), .cap = CAP_VIEW});

    Expr *type_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
    type_id->data.data.Ident = *Str_clone(&(Str){.c_str = (U8*)(type_name), .count = (U64)strlen((const char*)(type_name)), .cap = CAP_VIEW});
    type_id->struct_name = *Str_clone(&(Str){.c_str = (U8*)(type_name), .count = (U64)strlen((const char*)(type_name)), .cap = CAP_VIEW});

    Expr *fa = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
    fa->data.data.FieldAccess = (Str){.c_str = (U8*)"clone", .count = 5, .cap = CAP_LIT};
    fa->is_ns_field = true;
    Expr_add_child(fa, type_id);
    Expr_add_child(call, fa);

    Expr_add_child(call, Expr_clone(arg));
    return call;
}



// Insert deletes for live parent-scope locals before early exits in body.
// return_only=1: only before ExprData_TAG_Return (used when propagating into while bodies,
// since break/continue don't leave the parent scope).
static void insert_exit_deletes(Expr *body, LocalInfo *live, U32 n_live, Bool return_only) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
        if (stmt->data.tag == ExprData_TAG_If) {
            for (U32 c = 1; c < stmt->children.count; c++)
                insert_exit_deletes(Expr_child(stmt, &(USize){(USize)(c)}), live, n_live, return_only);
        }
        if (stmt->data.tag == ExprData_TAG_While) {
            insert_exit_deletes(Expr_child(stmt, &(USize){(USize)(1)}), live, n_live, 1);
        }
        if (stmt->data.tag == ExprData_TAG_Return ||
            (!return_only && (stmt->data.tag == ExprData_TAG_Break || stmt->data.tag == ExprData_TAG_Continue))) {
            for (U32 j = 0; j < n_live; j++) {
                if (stmt->children.count > 0 &&
                    (expr_uses_var(Expr_child(stmt, &(USize){(USize)(0)}), live[j].name) ||
                     alias_used_in_expr(body, live[j].name, Expr_child(stmt, &(USize){(USize)(0)})))) continue;
                Expr *del = make_delete_call(
                    live[j].name, live[j].type, live[j].struct_name, true, true, stmt);
                if (del) Vec_push(&new_ch, del);
            }
        }
        Vec_push(&new_ch, Expr_clone(stmt));
    }
    if (new_ch.count != body->children.count) {
        Vec_delete(&body->children, &(Bool){0});
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch, &(Bool){0});
    }
}

static void insert_free_calls(Expr *body, TypeScope *scope, I32 scope_exit) {
    if (!scope_exit) return;
    Bool is_program_scope = !scope->parent;

    // Phase 1: collect locals with lifetime info
    // Start from 0 (not locals_start) to include own params, which are added before the body
    Vec locals_vec; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(LocalInfo)}); locals_vec = *_vp; free(_vp); }
    for (U32 i = 0; i < scope->bindings.count; i++) {
        TypeBinding *b = (TypeBinding *)(scope->bindings.val_data + i * scope->bindings.val_size);
        if ((b->is_param && !b->is_own) || b->struct_def || b->func_def) continue;

        // Find decl_index: direct child first, then nested
        I32 decl_idx = -1;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *s = Expr_child(body, &(USize){(USize)(j)});
            if (s->data.tag == ExprData_TAG_Decl && Str_eq(&s->data.data.Decl.name, b->name)) {
                decl_idx = j;
                break;
            }
        }
        if (decl_idx == -1) {
            for (U32 j = 0; j < body->children.count; j++) {
                if (expr_contains_decl(Expr_child(body, &(USize){(USize)(j)}), b->name)) {
                    decl_idx = j;
                    break;
                }
            }
        }

        // Find last_use and own_transfer
        I32 last_use = -1;
        I32 own_transfer = -1;
        I32 scan_from = decl_idx >= 0 ? decl_idx + 1 : 0;
        for (U32 j = scan_from; j < body->children.count; j++) {
            if (expr_uses_var(Expr_child(body, &(USize){(USize)(j)}), b->name)) {
                last_use = j;
            }
            if (own_transfer == -1 && expr_transfers_own(Expr_child(body, &(USize){(USize)(j)}), b->name, scope)) {
                own_transfer = j;
            }
        }

        // Program-scope globals live for the program's lifetime — no ASAP deletion.
        // Still collect them for ownership-transfer and overwrite-delete checks.
        Bool skip_scope_delete = is_program_scope && decl_idx >= 0;

        if (!skip_scope_delete) {
            // If captured by a nested func/proc, don't ASAP-delete — the nested
            // function may be called after this scope's body finishes (e.g. cli mode main)
            for (U32 j = scan_from; j < body->children.count; j++) {
                if (expr_used_in_nested_func(Expr_child(body, &(USize){(USize)(j)}), b->name)) {
                    skip_scope_delete = 1;
                    break;
                }
            }
        }
        // Ref bindings don't own their data — never delete, but track for lifetime extension
        if (b->is_ref) skip_scope_delete = 1;

        LocalInfo li = {b->name, b->type, &b->struct_name, decl_idx, last_use, own_transfer, skip_scope_delete};
        { LocalInfo *_p = malloc(sizeof(LocalInfo)); *_p = li; Vec_push(&locals_vec, _p); }
    }

    if (locals_vec.count == 0) { Vec_delete(&locals_vec, &(Bool){0}); return; }
    U32 n_locals = locals_vec.count;
    LocalInfo *locals = Vec_take(&locals_vec);

    // Extend lifetimes for args to ref-returning calls:
    // If ref m := f(x, y), then x and y must outlive m.
    // Use fixed-point iteration to propagate through ref chains:
    // ref a = f(owner.x) → owner extended to a's last use
    // ref b = g(a.y)     → a extended to b's last use → owner extended too
    Bool ref_changed = 1;
    while (ref_changed) {
        ref_changed = 0;
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
            if (stmt->data.tag != ExprData_TAG_Decl || !stmt->data.data.Decl.is_ref) continue;
            Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});

            // Compute ref_last: max of AST uses and extended last_use in locals
            I32 ref_last = -1;
            for (U32 j = i + 1; j < body->children.count; j++) {
                if (expr_uses_var(Expr_child(body, &(USize){(USize)(j)}), &stmt->data.data.Decl.name))
                    ref_last = j;
            }
            if (ref_last == -1) ref_last = i;
            for (U32 j = 0; j < n_locals; j++) {
                if (Str_eq(locals[j].name, &stmt->data.data.Decl.name) && locals[j].last_use > ref_last)
                    ref_last = locals[j].last_use;
            }

            if (rhs->data.tag == ExprData_TAG_Ident) {
                // Direct alias: source must outlive alias
                Str *src_name = &rhs->data.data.Ident;
                for (U32 j = 0; j < n_locals; j++) {
                    if (Str_eq(locals[j].name, src_name) && locals[j].last_use < ref_last) {
                        locals[j].last_use = ref_last;
                        ref_changed = 1;
                    }
                }
                continue;
            }
            if (rhs->data.tag != ExprData_TAG_FCall) continue;
            // Extend last_use of all ident args in the fcall
            // Walk field-access chains to find root ident (e.g. root.children → root)
            for (U32 a = 1; a < rhs->children.count; a++) {
                Expr *arg = Expr_child(rhs, &(USize){(USize)(a)});
                while (arg->data.tag == ExprData_TAG_FieldAccess && arg->children.count > 0)
                    arg = Expr_child(arg, &(USize){(USize)(0)});
                if (arg->data.tag != ExprData_TAG_Ident) continue;
                Str *aname = &arg->data.data.Ident;
                for (U32 j = 0; j < n_locals; j++) {
                    if (Str_eq(locals[j].name, aname) && locals[j].last_use < ref_last) {
                        locals[j].last_use = ref_last;
                        ref_changed = 1;
                    }
                }
            }
        }
    }

    // Check for use after ownership transfer
    for (U32 j = 0; j < n_locals; j++) {
        if (locals[j].own_transfer >= 0 && locals[j].last_use > locals[j].own_transfer) {
            Expr *stmt = Expr_child(body, &(USize){(USize)(locals[j].last_use)});
            char buf[128];
            snprintf(buf, sizeof(buf), "use of '%s' after ownership transfer", locals[j].name->c_str);
            type_error(stmt, buf);
            Expr *xfer = Expr_child(body, &(USize){(USize)(locals[j].own_transfer)});
            fprintf(stderr, "%s:%u:%u: note: ownership transferred here\n",
                    xfer->path.c_str, xfer->line, xfer->col);
            fprintf(stderr, "  help: pass a clone instead: own %s.clone()\n",
                    locals[j].name->c_str);
        }
    }

    // Phase 2: rebuild body with ASAP frees
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});

        // Before ExprData_TAG_Return/ExprData_TAG_Break/ExprData_TAG_Continue: free locals not yet freed
        if (stmt->data.tag == ExprData_TAG_Return || stmt->data.tag == ExprData_TAG_Break || stmt->data.tag == ExprData_TAG_Continue) {
            for (U32 j = 0; j < n_locals; j++) {
                if (stmt->children.count > 0 &&
                    (expr_uses_var(Expr_child(stmt, &(USize){(USize)(0)}), locals[j].name) ||
                     alias_used_in_expr(body, locals[j].name, Expr_child(stmt, &(USize){(USize)(0)})))) continue;
                if (locals[j].skip_scope_delete) continue;
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].decl_index < (I32)i &&
                    (locals[j].last_use >= (I32)i || locals[j].last_use == -1)) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, false, false, stmt);
                    if (del) Vec_push(&new_ch, del);
                }
            }
        }

        // For ExprData_TAG_If/ExprData_TAG_While: insert frees before nested early exits
        if (stmt->data.tag == ExprData_TAG_If || stmt->data.tag == ExprData_TAG_While) {
            Vec live_vec; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(LocalInfo)}); live_vec = *_vp; free(_vp); }
            for (U32 j = 0; j < n_locals; j++) {
                    if (locals[j].skip_scope_delete) continue;
                    if (locals[j].own_transfer >= 0) continue;
                    if (locals[j].decl_index < (I32)i &&
                        (locals[j].last_use >= (I32)i || locals[j].last_use == -1)) {
                    { LocalInfo *_p = malloc(sizeof(LocalInfo)); *_p = locals[j]; Vec_push(&live_vec, _p); }
                }
            }
            if (live_vec.count > 0) {
                U32 n_live = live_vec.count;
                LocalInfo *live = Vec_take(&live_vec);
                if (stmt->data.tag == ExprData_TAG_If) {
                    for (U32 c = 1; c < stmt->children.count; c++)
                        insert_exit_deletes(Expr_child(stmt, &(USize){(USize)(c)}), live, n_live, 0);
                } else {
                    // While: only free before return (break/continue stay in parent scope)
                    insert_exit_deletes(Expr_child(stmt, &(USize){(USize)(1)}), live, n_live, 1);
                }
                free(live);
            } else {
                Vec_delete(&live_vec, &(Bool){0});
            }
        }

        // Before ExprData_TAG_Assign: delete old compound-type value
        if (stmt->data.tag == ExprData_TAG_Assign) {
            Str *vname = &stmt->data.data.Ident;
            for (U32 j = 0; j < n_locals; j++) {
                if (!Str_eq(locals[j].name, vname)) continue;
                TilType t = locals[j].type;
                if (t.tag == TilType_TAG_Struct || t.tag == TilType_TAG_Enum) {
                    Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
                    if (expr_uses_var(rhs, vname)) {
                        // RHS reads this var — can't delete before assignment.
                        // Flag so builder emits save-old-delete pattern.
                        stmt->save_old_delete = true;
                        if (locals[j].struct_name && locals[j].struct_name->count > 0)
                            stmt->struct_name = *Str_clone(locals[j].struct_name);
                    } else {
                        Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, false, false, stmt);
                        if (del) Vec_push(&new_ch, del);
                    }
                }
                break;
            }
        }

        // Add original statement
        Vec_push(&new_ch, Expr_clone(stmt));

        // After non-exit statements: free locals whose last use is this statement
        if (stmt->data.tag != ExprData_TAG_Return && stmt->data.tag != ExprData_TAG_Break && stmt->data.tag != ExprData_TAG_Continue) {
            for (U32 j = 0; j < n_locals; j++) {
                if (locals[j].skip_scope_delete) continue;
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].last_use == (I32)i) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, false, false, stmt);
                    if (del) Vec_push(&new_ch, del);
                }
                // Never used after declaration: free immediately
                if (locals[j].last_use == -1 && locals[j].decl_index == (I32)i) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, false, false, stmt);
                    if (del) Vec_push(&new_ch, del);
                }
            }
        }
    }

    Vec_delete(&body->children, &(Bool){0});
    body->children = new_ch;
    free(locals);
}

static void infer_body(TypeScope *scope, Expr *body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref, I32 in_type_body) {
    body->til_type = (TilType){TilType_TAG_None};
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(USize){(USize)(i)});
        switch (stmt->data.tag) {
        case ExprData_TAG_Decl:
            // Skip variant registry entries (payload enum: no children)
            if (stmt->children.count == 0) break;
            infer_expr(scope, Expr_child(stmt, &(USize){(USize)(0)}), in_func);
            // For struct/enum defs, register type in scope
            if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_StructDef ||
                Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_EnumDef) {
                Bool is_enum = (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_EnumDef);
                // Check explicit type annotation if present
                if (stmt->data.data.Decl.explicit_type.count > 0) {
                    TilType declared = *type_from_name(&stmt->data.data.Decl.explicit_type, scope);
                    TilType expected = is_enum ? (TilType){TilType_TAG_EnumDef} : (TilType){TilType_TAG_StructDef};
                    if (declared.tag != expected.tag) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                                 stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.explicit_type.c_str,
                                 is_enum ? "EnumDef" : "StructDef");
                        type_error(stmt, buf);
                    }
                }
                stmt->til_type = (TilType){TilType_TAG_None};
                Str *sname = &stmt->data.data.Decl.name;

                // Check for redeclaration: existing binding with a different struct_def
                ScopeFind *_sf_ex = TypeScope_find(scope, sname);
                TypeBinding *existing = _sf_ex->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ex) : NULL;
                if (existing && existing->struct_def && existing->struct_def != Expr_child(stmt, &(USize){(USize)(0)})) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "%s '%s' already declared at %s:%u:%u",
                             is_enum ? "enum" : "struct", sname->c_str,
                             existing->struct_def->path.c_str, existing->line, existing->col);
                    type_error(stmt, buf);
                    break;
                }

                // Check if this is a builtin type
                TilType builtin_type = is_enum ? (TilType){TilType_TAG_Enum} : (TilType){TilType_TAG_Struct};
                Bool is_builtin = 0;
                if ((sname->count == 3 && memcmp(sname->c_str, "I64", 3) == 0))  { builtin_type = (TilType){TilType_TAG_I64};  is_builtin = 1; }
                else if ((sname->count == 2 && memcmp(sname->c_str, "U8", 2) == 0))   { builtin_type = (TilType){TilType_TAG_U8};   is_builtin = 1; }
                else if ((sname->count == 3 && memcmp(sname->c_str, "I16", 3) == 0))  { builtin_type = (TilType){TilType_TAG_I16};  is_builtin = 1; }
                else if ((sname->count == 3 && memcmp(sname->c_str, "I32", 3) == 0))  { builtin_type = (TilType){TilType_TAG_I32};  is_builtin = 1; }
                else if ((sname->count == 3 && memcmp(sname->c_str, "U32", 3) == 0))  { builtin_type = (TilType){TilType_TAG_U32};  is_builtin = 1; }
                else if ((sname->count == 3 && memcmp(sname->c_str, "U64", 3) == 0))  { builtin_type = (TilType){TilType_TAG_U64};  is_builtin = 1; }
                else if ((sname->count == 3 && memcmp(sname->c_str, "F32", 3) == 0))  { builtin_type = (TilType){TilType_TAG_F32};  is_builtin = 1; }
                else if ((sname->count == 3 && memcmp(sname->c_str, "Str", 3) == 0))  { is_builtin = 0; } // Str is a regular struct now
                else if ((sname->count == 4 && memcmp(sname->c_str, "Bool", 4) == 0)) { builtin_type = (TilType){TilType_TAG_Bool}; is_builtin = 1; }
                else if ((sname->count == 9 && memcmp(sname->c_str, "StructDef", 9) == 0))    { builtin_type = (TilType){TilType_TAG_StructDef}; is_builtin = 1; }
                else if ((sname->count == 7 && memcmp(sname->c_str, "EnumDef", 7) == 0))      { builtin_type = (TilType){TilType_TAG_EnumDef};   is_builtin = 1; }
                else if ((sname->count == 11 && memcmp(sname->c_str, "FunctionDef", 11) == 0))  { is_builtin = 0; } // regular struct like Str
                else if ((sname->count == 7 && memcmp(sname->c_str, "Dynamic", 7) == 0))      { builtin_type = (TilType){TilType_TAG_Dynamic};    is_builtin = 1; }
                TypeScope_set(scope, sname, &builtin_type, -1, 0, stmt->line, stmt->col, 0, 0);
                // Store struct def pointer and builtin flag in the binding
                TypeBinding *b = Map_get(&scope->bindings, sname);
                b->struct_def = Expr_child(stmt, &(USize){(USize)(0)});
                b->is_builtin = is_builtin;
                b->is_ext = Expr_child(stmt, &(USize){(USize)(0)})->is_ext;
                break;
            }
            // For func/proc defs, store return type and func/proc-ness in scope
            if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FuncDef) {
                // Check explicit type annotation if present
                if (stmt->data.data.Decl.explicit_type.count > 0) {
                    if (!(stmt->data.data.Decl.explicit_type.count == 11 && memcmp(stmt->data.data.Decl.explicit_type.c_str, "FunctionDef", 11) == 0)) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is FunctionDef",
                                 stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.explicit_type.c_str);
                        type_error(stmt, buf);
                    }
                }
                FuncType ft = Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.func_type;
                I32 callee_is_proc = (ft.tag == FuncType_TAG_Test) ? 2 : (ft.tag == FuncType_TAG_Proc || ft.tag == FuncType_TAG_ExtProc) ? 1 : 0;
                TilType rt = (TilType){TilType_TAG_None};
                if ((Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.return_type.count > 0)) {
                    rt = *type_from_name(&Expr_child(stmt, &(USize){(USize)(0)})->data.data.FuncDef.return_type, scope);
                }
                stmt->til_type = rt;
                TypeScope_set(scope, &stmt->data.data.Decl.name, &rt, callee_is_proc, 0, stmt->line, stmt->col, 0, 0);
                // Store func_def pointer and builtin flag
                TypeBinding *fb = Map_get(&scope->bindings, &stmt->data.data.Decl.name);
                {
                    fb->func_def = Expr_child(stmt, &(USize){(USize)(0)});
                    if (ft.tag == FuncType_TAG_ExtFunc || ft.tag == FuncType_TAG_ExtProc)
                        fb->is_builtin = 1;
                }
                break;
            }
            // Type alias: Decl where RHS is Ident referring to a type (already registered by initer)
            if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
                ScopeFind *_sf_al = TypeScope_find(scope, &stmt->data.data.Decl.name);
                TypeBinding *alias_b = _sf_al->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_al) : NULL;
                if (alias_b && alias_b->is_type_alias) {
                    stmt->til_type = (TilType){TilType_TAG_None};
                    break;
                }
            }
            if (stmt->data.data.Decl.explicit_type.count > 0) {
                Str *etn = &stmt->data.data.Decl.explicit_type;
                TilType declared = *type_from_name(etn, scope);
                if (declared.tag == TilType_TAG_Unknown) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", etn->c_str);
                    type_error(stmt, buf);
                } else if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_LiteralNum &&
                           (is_numeric_type(&declared) || declared.tag == TilType_TAG_Dynamic)) {
                    // Numeric literals can be used with numeric types and Dynamic (0 = null)
                    if (is_numeric_type(&declared) && !literal_in_range(&Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident, &declared)) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "integer literal %s out of range for %s",
                                 Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident.c_str, til_type_name_c(&declared)->c_str);
                        type_error(Expr_child(stmt, &(USize){(USize)(0)}), buf);
                    }
                    Expr_child(stmt, &(USize){(USize)(0)})->til_type = declared;
                } else if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_LiteralNull && !stmt->data.data.Decl.is_ref) {
                    type_error(stmt, "null can only be assigned to 'ref' declarations");
                } else if (!stmt->data.data.Decl.is_ref &&
                           declared.tag != TilType_TAG_Dynamic &&
                           Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag == TilType_TAG_Dynamic) {
                    char buf[256];
                    snprintf(buf, sizeof(buf),
                             "cannot store owned Dynamic in '%s'; write '%s : Dynamic = ...' and borrow with 'ref' for typed access",
                             stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.name.c_str);
                    type_error(stmt, buf);
                } else if (!can_implicit_usize_coerce(&Expr_child(stmt, &(USize){(USize)(0)})->til_type, &declared, etn) &&
                           Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag != declared.tag &&
                           Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag != TilType_TAG_Dynamic) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.data.Decl.name.c_str, til_type_name_c(&declared)->c_str,
                             til_type_name_c(&Expr_child(stmt, &(USize){(USize)(0)})->til_type)->c_str);
                    type_error(stmt, buf);
                } else if ((declared.tag == TilType_TAG_Struct || declared.tag == TilType_TAG_Enum) &&
                           (Expr_child(stmt, &(USize){(USize)(0)})->struct_name.count > 0) &&
                           !Str_eq(resolve_type_alias(scope, etn), &Expr_child(stmt, &(USize){(USize)(0)})->struct_name)) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.data.Decl.name.c_str, etn->c_str, Expr_child(stmt, &(USize){(USize)(0)})->struct_name.c_str);
                    type_error(stmt, buf);
                }
                stmt->til_type = declared;
                if (can_implicit_usize_coerce(&Expr_child(stmt, &(USize){(USize)(0)})->til_type, &declared, etn))
                    Expr_child(stmt, &(USize){(USize)(0)})->til_type = declared;
                // Narrow Dynamic RHS to declared type
                narrow_dynamic(Expr_child(stmt, &(USize){(USize)(0)}), &declared, etn);
                // For struct/enum types, propagate struct_name from explicit type (resolved through aliases)
                if (declared.tag == TilType_TAG_Struct || declared.tag == TilType_TAG_Enum) {
                    Expr_child(stmt, &(USize){(USize)(0)})->struct_name = *Str_clone(resolve_type_alias(scope, etn));
                }
            } else {
                stmt->til_type = Expr_child(stmt, &(USize){(USize)(0)})->til_type;
                if (Expr_child(stmt, &(USize){(USize)(0)})->struct_name.count > 0)
                    stmt->struct_name = *Str_clone(&Expr_child(stmt, &(USize){(USize)(0)})->struct_name);
                if (stmt->til_type.tag == TilType_TAG_Dynamic) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "cannot store Dynamic in '%s'; add a type annotation like '%s : Type = ...' to specify the concrete type",
                             stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.name.c_str);
                    type_error(stmt, buf);
                }
            }
            if (!in_type_body && stmt->data.data.Decl.is_own) {
                char buf[256];
                if (stmt->data.data.Decl.is_mut) {
                    snprintf(buf, sizeof(buf),
                             "no need for 'own' on mutable local '%s'; write 'mut %s := ...'",
                             stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.name.c_str);
                } else {
                    snprintf(buf, sizeof(buf),
                             "no need for 'own' on local '%s'; locals are owned by default",
                             stmt->data.data.Decl.name.c_str);
                }
                type_error(stmt, buf);
            }
            TypeScope_set(scope, &stmt->data.data.Decl.name, &stmt->til_type, -1, stmt->data.data.Decl.is_mut, stmt->line, stmt->col, 0, 0);
            TypeBinding *_decl_b = Map_get(&scope->bindings, &stmt->data.data.Decl.name);
            if ((stmt->til_type.tag == TilType_TAG_Struct || stmt->til_type.tag == TilType_TAG_Enum) && (Expr_child(stmt, &(USize){(USize)(0)})->struct_name.count > 0)) {
                _decl_b->struct_name = *Str_clone(&Expr_child(stmt, &(USize){(USize)(0)})->struct_name);
            }
            // For function pointer variables, propagate func_def from source or fn_sig
            if (stmt->til_type.tag == TilType_TAG_FuncPtr) {
                // Explicit Fn signature on decl takes priority
                if (stmt->data.data.Decl.fn_sig) {
                    _decl_b->func_def = stmt->data.data.Decl.fn_sig;
                } else if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
                    ScopeFind *_sf_src = TypeScope_find(scope, &Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident);
                    TypeBinding *src = _sf_src->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_src) : NULL;
                    if (src && src->func_def) _decl_b->func_def = src->func_def;
                } else if (Expr_child(stmt, &(USize){(USize)(0)})->fn_sig) {
                    _decl_b->func_def = Expr_child(stmt, &(USize){(USize)(0)})->fn_sig;
                }
                // Named FuncSig type in explicit type position
                if (!_decl_b->func_def && stmt->data.data.Decl.explicit_type.count > 0) {
                    ScopeFind *_sf_fsb2 = TypeScope_find(scope, &stmt->data.data.Decl.explicit_type);
                    TypeBinding *fsb = _sf_fsb2->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_fsb2) : NULL;
                    if (fsb && fsb->func_def && fsb->func_def->children.count == 0)
                        _decl_b->func_def = fsb->func_def;
                }
            }
            if (stmt->data.data.Decl.is_ref) {
                _decl_b->is_ref = 1;
                // Validate ref RHS: must be null, a ref-returning fcall, or a ref/param variable
                Expr *rhs = Expr_child(stmt, &(USize){(USize)(0)});
                Bool ok = expr_is_ref_decl_source(rhs, scope);
                if (!ok) type_error(stmt, "'ref' declaration requires null, a ref-returning function, or ref/param variable");
            }
            // Error: owning result of ref-returning function without ref
            if (!stmt->data.data.Decl.is_ref && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FCall &&
                fcall_returns_ref(Expr_child(stmt, &(USize){(USize)(0)}), scope)) {
                type_error(stmt, "cannot own result of ref-returning function; use 'ref' or Type.clone()");
            }
            // Auto-alias: immutable ident → immutable dest becomes ref (skip for Fn)
            // Eligible sources: immutable locals, immutable params, other auto-aliases
            // Excluded: mut (value can change), own (ownership transfer),
            //           explicit ref (user intends to clone from borrowed value)
            if (!stmt->data.data.Decl.is_ref && !stmt->data.data.Decl.is_mut &&
                stmt->til_type.tag != TilType_TAG_FuncPtr &&
                Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
                ScopeFind *_sf_rb3 = TypeScope_find(scope, &Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident);
                TypeBinding *rb = _sf_rb3->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_rb3) : NULL;
                if (rb && !rb->is_mut && !rb->is_own &&
                    (!rb->is_ref || rb->is_alias) && !rb->is_param) {
                    stmt->data.data.Decl.is_ref = true;
                    _decl_b->is_ref = 1; _decl_b->is_alias = 1;
                }
            }
            // Auto-insert clone for declarations from identifiers (skip ref decls)
            if ((Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident ||
                 (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                  (Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag == TilType_TAG_Struct ||
                   Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag == TilType_TAG_Enum))) &&
                !stmt->data.data.Decl.is_ref) {
                Str *tname = type_to_name(&stmt->til_type, &Expr_child(stmt, &(USize){(USize)(0)})->struct_name);
                if (tname->count > 0) {
                    Expr *_mc = make_clone_call((const char *)tname->c_str, stmt->til_type,
                        Expr_child(stmt, &(USize){(USize)(0)}), stmt);
                    *(Expr*)Vec_get(&stmt->children, &(USize){(USize)(0)}) = *_mc;
                    memset(_mc, 0, sizeof(Expr)); free(_mc);
                }
            }
            break;
        case ExprData_TAG_Assign: {
            infer_expr(scope, Expr_child(stmt, &(USize){(USize)(0)}), in_func);
            stmt->til_type = Expr_child(stmt, &(USize){(USize)(0)})->til_type;
            if (Expr_child(stmt, &(USize){(USize)(0)})->struct_name.count > 0)
                stmt->struct_name = *Str_clone(&Expr_child(stmt, &(USize){(USize)(0)})->struct_name);
            Str *aname = &stmt->data.data.Ident;
            TilType existing = *TypeScope_get_type(scope, aname);
            if (existing.tag == TilType_TAG_Unknown) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined symbol '%s'", aname->c_str);
                type_error(stmt, buf);
            } else if (!TypeScope_is_mut(scope, aname)) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot assign to immutable variable '%s'", aname->c_str);
                type_error(stmt, buf);
                ScopeFind *_sf_asgn = TypeScope_find(scope, aname);
                TypeBinding *b = _sf_asgn->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_asgn) : NULL;
                if (b && b->is_param) {
                    fprintf(stderr, "%s:%u:%u: note: '%s' is a function parameter\n",
                            stmt->path.c_str, b->line, b->col, aname->c_str);
                } else if (b) {
                    fprintf(stderr, "%s:%u:%u: note: '%s' declared here, consider adding 'mut'\n",
                            stmt->path.c_str, b->line, b->col, aname->c_str);
                }
            } else if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_LiteralNum && is_numeric_type(&existing)) {
                if (!literal_in_range(&Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident, &existing)) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "integer literal %s out of range for %s",
                             Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident.c_str, til_type_name_c(&existing)->c_str);
                    type_error(stmt, buf);
                }
                Expr_child(stmt, &(USize){(USize)(0)})->til_type = existing;
                stmt->til_type = existing;
            } else if (Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag != existing.tag &&
                       Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag != TilType_TAG_Unknown) {
                char buf[128];
                snprintf(buf, sizeof(buf), "'%s' is %s but assigned %s",
                         aname->c_str, til_type_name_c(&existing)->c_str,
                         til_type_name_c(&Expr_child(stmt, &(USize){(USize)(0)})->til_type)->c_str);
                type_error(stmt, buf);
            }
            // Auto-insert clone for assignments from identifiers
            if (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident ||
                (Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                 (Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag == TilType_TAG_Struct ||
                  Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag == TilType_TAG_Enum))) {
                Str *tname = type_to_name(&Expr_child(stmt, &(USize){(USize)(0)})->til_type, &Expr_child(stmt, &(USize){(USize)(0)})->struct_name);
                if (tname->count > 0) {
                    Expr *_mc = make_clone_call((const char *)tname->c_str, Expr_child(stmt, &(USize){(USize)(0)})->til_type,
                        Expr_child(stmt, &(USize){(USize)(0)}), stmt);
                    *(Expr*)Vec_get(&stmt->children, &(USize){(USize)(0)}) = *_mc;
                    memset(_mc, 0, sizeof(Expr)); free(_mc);
                }
            }
            break;
        }
        case ExprData_TAG_FieldAssign: {
            infer_expr(scope, Expr_child(stmt, &(USize){(USize)(0)}), in_func); // object
            infer_expr(scope, Expr_child(stmt, &(USize){(USize)(1)}), in_func); // value
            Expr *obj = Expr_child(stmt, &(USize){(USize)(0)});
            Str *fname = &stmt->data.data.Ident;
            if (obj->struct_name.count > 0) {
                Expr *sdef = TypeScope_get_struct(scope, &obj->struct_name);
                if (sdef) {
                    Expr *body = Expr_child(sdef, &(USize){(USize)(0)});
                    Bool found = 0;
                    for (U32 i = 0; i < body->children.count; i++) {
                        Expr *field = Expr_child(body, &(USize){(USize)(i)});
                        if (Str_eq(&field->data.data.Decl.name, fname)) {
                            found = 1;
                            stmt->is_ns_field = field->data.data.Decl.is_namespace;
                            stmt->is_own_field = field->data.data.Decl.is_own || field->data.data.Decl.is_ref;
                            stmt->is_ref_field = field->data.data.Decl.is_ref;
                            if (!field->data.data.Decl.is_mut) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "cannot assign to immutable field '%s'", fname->c_str);
                                type_error(stmt, buf);
                            }
                            if (Expr_child(stmt, &(USize){(USize)(1)})->data.tag == ExprData_TAG_LiteralNum && is_numeric_type(&field->til_type)) {
                                if (!literal_in_range(&Expr_child(stmt, &(USize){(USize)(1)})->data.data.Ident, &field->til_type)) {
                                    char buf[128];
                                    snprintf(buf, sizeof(buf), "integer literal %s out of range for field '%s' (%s)",
                                             Expr_child(stmt, &(USize){(USize)(1)})->data.data.Ident.c_str, fname->c_str, til_type_name_c(&field->til_type)->c_str);
                                    type_error(Expr_child(stmt, &(USize){(USize)(1)}), buf);
                                }
                                Expr_child(stmt, &(USize){(USize)(1)})->til_type = field->til_type;
                            } else if (Expr_child(stmt, &(USize){(USize)(1)})->til_type.tag != field->til_type.tag &&
                                Expr_child(stmt, &(USize){(USize)(1)})->til_type.tag != TilType_TAG_Unknown &&
                                Expr_child(stmt, &(USize){(USize)(1)})->til_type.tag != TilType_TAG_Dynamic) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "field '%s' is %s but assigned %s",
                                         fname->c_str, til_type_name_c(&field->til_type)->c_str,
                                         til_type_name_c(&Expr_child(stmt, &(USize){(USize)(1)})->til_type)->c_str);
                                type_error(stmt, buf);
                            }
                            break;
                        }
                    }
                    if (!found) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'",
                                 obj->struct_name.c_str, fname->c_str);
                        type_error(stmt, buf);
                    }
                }
            } else {
                type_error(stmt, "field assignment on non-struct value");
            }
            stmt->til_type = (TilType){TilType_TAG_None};
            // Auto-insert clone for field assignments from identifiers
            // Skip clone for ref fields — they store pointers, not owned copies
            if (!stmt->is_ref_field &&
                (Expr_child(stmt, &(USize){(USize)(1)})->data.tag == ExprData_TAG_Ident ||
                 (Expr_child(stmt, &(USize){(USize)(1)})->data.tag == ExprData_TAG_FieldAccess &&
                  (Expr_child(stmt, &(USize){(USize)(1)})->til_type.tag == TilType_TAG_Struct ||
                   Expr_child(stmt, &(USize){(USize)(1)})->til_type.tag == TilType_TAG_Enum)))) {
                Str *tname = type_to_name(&Expr_child(stmt, &(USize){(USize)(1)})->til_type,
                                          &Expr_child(stmt, &(USize){(USize)(1)})->struct_name);
                if (tname->count > 0) {
                    Expr *_mc = make_clone_call((const char *)tname->c_str,
                        Expr_child(stmt, &(USize){(USize)(1)})->til_type, Expr_child(stmt, &(USize){(USize)(1)}),
                        Expr_child(stmt, &(USize){(USize)(1)}));
                    *(Expr*)Vec_get(&stmt->children, &(USize){(USize)(1)}) = *_mc;
                    memset(_mc, 0, sizeof(Expr)); free(_mc);
                }
            }
            break;
        }
        case ExprData_TAG_FCall:
            infer_expr(scope, stmt, in_func);
            break;
        case ExprData_TAG_Return:
            if (stmt->children.count > 0) {
                infer_expr(scope, Expr_child(stmt, &(USize){(USize)(0)}), in_func);
                stmt->til_type = Expr_child(stmt, &(USize){(USize)(0)})->til_type;
                // Error: returning an explicit ref variable from a non-ref function
                if (!returns_ref && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
                    ScopeFind *_sf_ret1 = TypeScope_find(scope, &Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident);
                    TypeBinding *b = _sf_ret1->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ret1) : NULL;
                    if (b && b->is_ref && !b->is_alias && !b->is_param) {
                        type_error(stmt, "cannot return ref variable from non-ref function; use .clone() or 'returns ref'");
                    }
                }
                // Auto-insert clone when returning a borrowed param or auto-alias
                // (prevents use-after-free: aliases share storage with locals,
                //  params are borrowed — both need cloning to return safely)
                if (!returns_ref && Expr_child(stmt, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
                    ScopeFind *_sf_ret2 = TypeScope_find(scope, &Expr_child(stmt, &(USize){(USize)(0)})->data.data.Ident);
                    TypeBinding *b = _sf_ret2->tag == ScopeFind_TAG_Found ? (TypeBinding*)get_payload(_sf_ret2) : NULL;
                    if (b && ((b->is_ref && b->is_alias) || (b->is_param && !b->is_own))) {
                        Str *tname = type_to_name(&stmt->til_type, &Expr_child(stmt, &(USize){(USize)(0)})->struct_name);
                        if (tname->count > 0) {
                            Expr *_mc = make_clone_call((const char *)tname->c_str, stmt->til_type,
                                Expr_child(stmt, &(USize){(USize)(0)}), stmt);
                            *(Expr*)Vec_get(&stmt->children, &(USize){(USize)(0)}) = *_mc;
                            memset(_mc, 0, sizeof(Expr)); free(_mc);
                        }
                    }
                }
            } else {
                stmt->til_type = (TilType){TilType_TAG_None};
            }
            break;
        case ExprData_TAG_Break:
            if (!in_loop) {
                type_error(stmt, "break outside loop");
            }
            stmt->til_type = (TilType){TilType_TAG_None};
            break;
        case ExprData_TAG_Continue:
            if (!in_loop) {
                type_error(stmt, "continue outside loop");
            }
            stmt->til_type = (TilType){TilType_TAG_None};
            break;
        case ExprData_TAG_If:
            infer_expr(scope, Expr_child(stmt, &(USize){(USize)(0)}), in_func); // condition
            if (Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag != TilType_TAG_Bool &&
                Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag != TilType_TAG_Unknown) {
                char buf[128];
                snprintf(buf, sizeof(buf), "if condition must be Bool, got %s",
                         til_type_name_c(&Expr_child(stmt, &(USize){(USize)(0)})->til_type)->c_str);
                type_error(stmt, buf);
            }
            {
                TypeScope *then_scope = TypeScope_new(scope);
                infer_body(then_scope, Expr_child(stmt, &(USize){(USize)(1)}), in_func, 1, in_loop, returns_ref, 0);
                TypeScope_delete(then_scope, &(Bool){1});
            }
            if (stmt->children.count > 2) {
                TypeScope *else_scope = TypeScope_new(scope);
                infer_body(else_scope, Expr_child(stmt, &(USize){(USize)(2)}), in_func, 1, in_loop, returns_ref, 0);
                TypeScope_delete(else_scope, &(Bool){1});
            }
            stmt->til_type = (TilType){TilType_TAG_None};
            break;
        case ExprData_TAG_Body: {
            TypeScope *block_scope = TypeScope_new(scope);
            infer_body(block_scope, stmt, in_func, 1, in_loop, returns_ref, 0);
            TypeScope_delete(block_scope, &(Bool){1});
            break;
        }
        case ExprData_TAG_While:
            infer_expr(scope, Expr_child(stmt, &(USize){(USize)(0)}), in_func); // condition
            if (Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag != TilType_TAG_Bool &&
                Expr_child(stmt, &(USize){(USize)(0)})->til_type.tag != TilType_TAG_Unknown) {
                char buf[128];
                snprintf(buf, sizeof(buf), "while condition must be Bool, got %s",
                         til_type_name_c(&Expr_child(stmt, &(USize){(USize)(0)})->til_type)->c_str);
                type_error(stmt, buf);
            }
            // Transform: while COND { BODY } -> while true { _wcond := COND; if _wcond {} else { break }; BODY }
            // This lets ASAP destruction free the condition result each iteration.
            if (expr_contains_fcall(Expr_child(stmt, &(USize){(USize)(0)}))) {
                Expr *cond = Expr_child(stmt, &(USize){(USize)(0)});
                I32 line = cond->line;
                I32 col = cond->col;
                Str *path = &cond->path;
                Expr *body = Expr_child(stmt, &(USize){(USize)(1)});
                // _wcondN := COND
                char name_buf[128];
                snprintf(name_buf, sizeof(name_buf), "_wcond_Bool_%d", hoist_counter++);
                Str *wname = Str_clone(&(Str){.c_str = (U8*)(name_buf), .count = (U64)strlen((const char*)(name_buf)), .cap = CAP_VIEW});
                Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                decl->data.data.Decl.name = *wname;
                decl->data.data.Decl.explicit_type = (Str){0};
                decl->data.data.Decl.is_mut = false;
                decl->data.data.Decl.is_namespace = false;
                decl->til_type = cond->til_type;
                Expr_add_child(decl, Expr_clone(cond));
                // if _wcondN {} else { break }
                Expr *ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
                ident->data.data.Ident = *wname;
                ident->til_type = (TilType){TilType_TAG_Bool};
                Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                if_node->til_type = (TilType){TilType_TAG_None};
                Expr_add_child(if_node, ident);
                Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                then_body->til_type = (TilType){TilType_TAG_None};
                Expr_add_child(if_node, then_body);
                Expr *else_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                else_body->til_type = (TilType){TilType_TAG_None};
                Expr *brk = Expr_new(&(ExprData){.tag = ExprData_TAG_Break}, line, col, path);
                brk->til_type = (TilType){TilType_TAG_None};
                Expr_add_child(else_body, brk);
                Expr_add_child(if_node, else_body);
                // Prepend decl + if to body
                Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
                Vec_push(&new_ch, decl);
                Vec_push(&new_ch, if_node);
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *ch = Expr_child(body, &(USize){(USize)(j)});
                    Vec_push(&new_ch, Expr_clone(ch));
                }
                Vec_delete(&body->children, &(Bool){0});
                body->children = new_ch;
                // Replace condition with true
                Expr *true_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
                true_lit->data.data.LiteralBool = 1;
                true_lit->til_type = (TilType){TilType_TAG_Bool};
                *(Expr*)Vec_get(&stmt->children, &(USize){(USize)(0)}) = *true_lit;
            }
            {
                TypeScope *while_scope = TypeScope_new(scope);
                infer_body(while_scope, Expr_child(stmt, &(USize){(USize)(1)}), in_func, 1, 1, returns_ref, 0);
                TypeScope_delete(while_scope, &(Bool){1});
            }
            stmt->til_type = (TilType){TilType_TAG_None};
            break;
        case ExprData_TAG_Switch: {
            // Desugar: switch expr { case v1: B1  case v2: B2  case: B3 }
            // Into:   { _swN := expr; if _swN.eq(v1) { B1 } else if _swN.eq(v2) { B2 } else { B3 } }
            Expr *sw_expr = Expr_child(stmt, &(USize){(USize)(0)});
            I32 sw_line = stmt->line, sw_col = stmt->col;
            Str *sw_path = &stmt->path;
            infer_expr(scope, sw_expr, in_func);
            Expr *switch_enum_def = NULL;
            Bool *covered_variants = NULL;
            U32 n_variants = 0;
            Bool has_default_case = 0;

            if (sw_expr->til_type.tag == TilType_TAG_Enum && sw_expr->struct_name.count > 0) {
                switch_enum_def = TypeScope_get_struct(scope, &sw_expr->struct_name);
                if (switch_enum_def && switch_enum_def->data.tag == ExprData_TAG_EnumDef) {
                    Expr *enum_body = Expr_child(switch_enum_def, &(USize){0});
                    for (U32 vi = 0; vi < enum_body->children.count; vi++) {
                        Expr *variant = Expr_child(enum_body, &(USize){vi});
                        if (variant->data.tag == ExprData_TAG_Decl && !variant->data.data.Decl.is_namespace)
                            n_variants++;
                    }
                    if (n_variants > 0) covered_variants = calloc(n_variants, sizeof(Bool));
                } else {
                    switch_enum_def = NULL;
                }
            }

            // Unique switch variable name
            char sw_buf[128];
            Str *tp = type_prefix(&sw_expr->til_type, &sw_expr->struct_name);
            snprintf(sw_buf, sizeof(sw_buf), "_sw_%s_%d", tp->c_str, hoist_counter++);
            Str *sw_name = Str_clone(&(Str){.c_str = (U8*)(sw_buf), .count = (U64)strlen((const char*)(sw_buf)), .cap = CAP_VIEW});

            // Outer anonymous scope
            Expr *block = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, sw_line, sw_col, sw_path);

            // _swN := expr
            Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, sw_line, sw_col, sw_path);
            decl->data.data.Decl.name = *sw_name;
            decl->data.data.Decl.explicit_type = (Str){0};
            decl->data.data.Decl.is_mut = false;
            decl->data.data.Decl.is_namespace = false;
            decl->data.data.Decl.is_ref = false;
            decl->data.data.Decl.is_own = false;
            Expr_add_child(decl, Expr_clone(sw_expr));
            Expr_add_child(block, decl);

            // Build if/else chain from cases (children[1..])
            Expr *first_if = NULL;
            Expr *last_if = NULL;
            Expr *default_body = NULL;

            for (U32 ci = 1; ci < stmt->children.count; ci++) {
                Expr *case_node = Expr_child(stmt, &(USize){(USize)(ci)});
                if (case_node->children.count == 1) {
                    // Default case — just body, no match expr
                    default_body = Expr_child(case_node, &(USize){(USize)(0)});
                    has_default_case = 1;
                    continue;
                }
                Expr *match_expr = Expr_child(case_node, &(USize){(USize)(0)});
                Expr *case_body = Expr_child(case_node, &(USize){(USize)(1)});
                Expr *condition = NULL;

                if (switch_enum_def && covered_variants) {
                    Str *covered_variant_name = NULL;

                    // case Enum.Variant:
                    if (match_expr->data.tag == ExprData_TAG_FieldAccess &&
                        match_expr->children.count > 0 &&
                        Expr_child(match_expr, &(USize){0})->data.tag == ExprData_TAG_Ident &&
                        Str_eq(&Expr_child(match_expr, &(USize){0})->data.data.Ident, &sw_expr->struct_name)) {
                        covered_variant_name = &match_expr->data.data.FieldAccess;
                    }

                    // case Enum.Variant(binding): covers the whole variant
                    if (!covered_variant_name &&
                        match_expr->data.tag == ExprData_TAG_FCall &&
                        match_expr->children.count == 2 &&
                        Expr_child(match_expr, &(USize){0})->data.tag == ExprData_TAG_FieldAccess &&
                        Expr_child(Expr_child(match_expr, &(USize){0}), &(USize){0})->data.tag == ExprData_TAG_Ident &&
                        Expr_child(match_expr, &(USize){1})->data.tag == ExprData_TAG_Ident &&
                        Str_eq(&Expr_child(Expr_child(match_expr, &(USize){0}), &(USize){0})->data.data.Ident, &sw_expr->struct_name)) {
                        covered_variant_name = &Expr_child(match_expr, &(USize){0})->data.data.FieldAccess;
                    }

                    if (covered_variant_name) {
                        I32 covered_tag = *enum_variant_tag(switch_enum_def, covered_variant_name);
                        if (covered_tag >= 0 && (U32)covered_tag < n_variants) {
                            covered_variants[covered_tag] = 1;
                        }
                    }
                }

                // Phase 2: Range case — case A..B: → _sw.gte(A).and(_sw.lte(B))
                // Detect Range.new(start, end) pattern from parser's .. desugaring
                if (match_expr->data.tag == ExprData_TAG_FCall &&
                    match_expr->children.count == 3 &&
                    Expr_child(match_expr, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                    (Expr_child(match_expr, &(USize){(USize)(0)})->data.data.Ident.count == 3 && memcmp(Expr_child(match_expr, &(USize){(USize)(0)})->data.data.Ident.c_str, "new", 3) == 0) &&
                    Expr_child(Expr_child(match_expr, &(USize){(USize)(0)}), &(USize){0})->data.tag == ExprData_TAG_Ident &&
                    (Expr_child(Expr_child(match_expr, &(USize){(USize)(0)}), &(USize){0})->data.data.Ident.count == 5 && memcmp(Expr_child(Expr_child(match_expr, &(USize){(USize)(0)}), &(USize){0})->data.data.Ident.c_str, "Range", 5) == 0)) {
                    Expr *start_expr = Expr_child(match_expr, &(USize){(USize)(1)});
                    Expr *end_expr = Expr_child(match_expr, &(USize){(USize)(2)});

                    // _sw.gte(start)
                    Expr *sw1 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                    sw1->data.data.Ident = *sw_name;
                    Expr *gte_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, sw_line, sw_col, sw_path);
                    gte_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"gte", .count = 3, .cap = CAP_LIT};
                    Expr_add_child(gte_acc, sw1);
                    Expr *gte_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                    Expr_add_child(gte_call, gte_acc);
                    Expr_add_child(gte_call, Expr_clone(start_expr));

                    // _sw.lte(end) — inclusive for case ranges
                    Expr *sw2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                    sw2->data.data.Ident = *sw_name;
                    Expr *lte_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, sw_line, sw_col, sw_path);
                    lte_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"lte", .count = 3, .cap = CAP_LIT};
                    Expr_add_child(lte_acc, sw2);
                    Expr *lte_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                    Expr_add_child(lte_call, lte_acc);
                    Expr_add_child(lte_call, Expr_clone(end_expr));

                    // gte_call.and(lte_call)
                    Expr *and_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, sw_line, sw_col, sw_path);
                    and_acc->data.data.FieldAccess = (Str){.c_str = (U8*)"and", .count = 3, .cap = CAP_LIT};
                    Expr_add_child(and_acc, gte_call);
                    condition = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                    Expr_add_child(condition, and_acc);
                    Expr_add_child(condition, lte_call);
                }

                // Phase 4: Enum payload extraction — case Enum.Variant(binding):
                // Detect EnumType.Variant(ident) where variant has a payload
                if (!condition &&
                    match_expr->data.tag == ExprData_TAG_FCall &&
                    match_expr->children.count == 2 &&
                    Expr_child(match_expr, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                    Expr_child(Expr_child(match_expr, &(USize){(USize)(0)}), &(USize){0})->data.tag == ExprData_TAG_Ident &&
                    Expr_child(match_expr, &(USize){(USize)(1)})->data.tag == ExprData_TAG_Ident) {
                    Expr *callee = Expr_child(match_expr, &(USize){(USize)(0)});
                    Str *type_name = &Expr_child(callee, &(USize){(USize)(0)})->data.data.Ident;
                    Str *variant_name = &callee->data.data.Ident;
                    Str *binding_name = &Expr_child(match_expr, &(USize){(USize)(1)})->data.data.Ident;
                    Expr *enum_def = TypeScope_get_struct(scope, type_name);
                    if (enum_def && enum_def->data.tag == ExprData_TAG_EnumDef) {
                        I32 tag = *enum_variant_tag(enum_def, variant_name);
                        Str *payload_type = (tag >= 0) ? enum_variant_type(enum_def, tag) : NULL;
                        if (payload_type && payload_type->count > 0) {
                            // Build is_variant(_sw, EnumType.Variant)
                            Expr *iv_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            iv_id->data.data.Ident = (Str){.c_str = (U8*)"is_variant", .count = 10, .cap = CAP_LIT};
                            Expr *sw_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            sw_id->data.data.Ident = *sw_name;
                            Expr *vtype_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            vtype_id->data.data.Ident = *type_name;
                            Expr *vref = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, sw_line, sw_col, sw_path);
                            vref->data.data.FieldAccess = *variant_name;
                            Expr_add_child(vref, vtype_id);
                            condition = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                            Expr_add_child(condition, iv_id);
                            Expr_add_child(condition, sw_id);
                            Expr_add_child(condition, vref);

                            // Prepend binding: ref binding_name : PayloadType = get_payload(_sw)
                            Expr *gp_ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            gp_ident->data.data.Ident = (Str){.c_str = (U8*)"get_payload", .count = 11, .cap = CAP_LIT};
                            Expr *sw_id2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            sw_id2->data.data.Ident = *sw_name;
                            Expr *get_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                            Expr_add_child(get_call, gp_ident);
                            Expr_add_child(get_call, sw_id2);

                            Expr *bind_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, sw_line, sw_col, sw_path);
                            bind_decl->data.data.Decl.name = *binding_name;
                            bind_decl->data.data.Decl.explicit_type = *payload_type;
                            bind_decl->data.data.Decl.is_mut = false;
                            bind_decl->data.data.Decl.is_namespace = false;
                            bind_decl->data.data.Decl.is_ref = true;
                            bind_decl->data.data.Decl.is_own = false;
                            Expr_add_child(bind_decl, get_call);

                            // Prepend to case body
                            Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(USize){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
                            Vec_push(&new_ch, bind_decl);
                            for (U32 bi = 0; bi < case_body->children.count; bi++) {
                                Expr *ch = Expr_child(case_body, &(USize){(USize)(bi)});
                                Vec_push(&new_ch, Expr_clone(ch));
                            }
                            Vec_delete(&case_body->children, &(Bool){0});
                            case_body->children = new_ch;
                        }
                    }
                }

                // Phase 5: Payload enum tag-only match — case Enum.Variant: (no binding)
                // Detect FieldAccess on an enum type where the variant has a payload
                if (!condition &&
                    match_expr->data.tag == ExprData_TAG_FieldAccess &&
                    match_expr->children.count > 0 &&
                    Expr_child(match_expr, &(USize){(USize)(0)})->data.tag == ExprData_TAG_Ident) {
                    Str *type_name = &Expr_child(match_expr, &(USize){(USize)(0)})->data.data.Ident;
                    Str *variant_name = &match_expr->data.data.FieldAccess;
                    Expr *enum_def = TypeScope_get_struct(scope, type_name);
                    if (enum_def && enum_def->data.tag == ExprData_TAG_EnumDef) {
                        I32 tag = *enum_variant_tag(enum_def, variant_name);
                        Str *payload_type = (tag >= 0) ? enum_variant_type(enum_def, tag) : NULL;
                        if (payload_type && payload_type->count > 0) {
                            // Payload variant without binding — use is_variant(_sw, E.V)
                            Expr *iv_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            iv_id->data.data.Ident = (Str){.c_str = (U8*)"is_variant", .count = 10, .cap = CAP_LIT};
                            Expr *sw_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            sw_id->data.data.Ident = *sw_name;
                            Expr *vtype_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            vtype_id->data.data.Ident = *type_name;
                            Expr *vref = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, sw_line, sw_col, sw_path);
                            vref->data.data.FieldAccess = *variant_name;
                            Expr_add_child(vref, vtype_id);
                            condition = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                            Expr_add_child(condition, iv_id);
                            Expr_add_child(condition, sw_id);
                            Expr_add_child(condition, vref);
                        }
                    }
                }

                // Phase 1/3: Default — _sw.eq(match_expr)
                if (!condition) {
                    Expr *sw_ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                    sw_ident->data.data.Ident = *sw_name;
                    Expr *eq_access = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, sw_line, sw_col, sw_path);
                    eq_access->data.data.FieldAccess = (Str){.c_str = (U8*)"eq", .count = 2, .cap = CAP_LIT};
                    Expr_add_child(eq_access, sw_ident);
                    condition = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                    Expr_add_child(condition, eq_access);
                    Expr_add_child(condition, Expr_clone(match_expr));
                }

                Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, case_node->line, case_node->col, sw_path);
                Expr_add_child(if_node, condition);  // condition
                Expr_add_child(if_node, Expr_clone(case_body));  // then body

                if (!first_if) {
                    first_if = if_node;
                    last_if = if_node;
                } else {
                    // Chain as else-if
                    Expr *else_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, case_node->line, case_node->col, sw_path);
                    Expr_add_child(else_body, if_node);
                    Expr_add_child(last_if, else_body);
                    last_if = Expr_child(Expr_child(last_if, &(USize){(USize)(last_if->children.count - 1)}), &(USize){(USize)(0)});
                }
            }

            // Attach default as final else
            if (default_body && last_if) {
                Expr_add_child(last_if, Expr_clone(default_body));
            } else if (default_body && !first_if) {
                // Only a default case — just emit the body
                first_if = default_body;
            }

            if (switch_enum_def && covered_variants && !has_default_case) {
                Expr *enum_body = Expr_child(switch_enum_def, &(USize){0});
                char buf[1024];
                size_t used = snprintf(buf, sizeof(buf),
                                       "non-exhaustive switch on enum '%s'; missing cases:",
                                       sw_expr->struct_name.c_str);
                U32 variant_idx = 0;
                Bool missing = 0;
                for (U32 vi = 0; vi < enum_body->children.count; vi++) {
                    Expr *variant = Expr_child(enum_body, &(USize){vi});
                    if (variant->data.tag != ExprData_TAG_Decl || variant->data.data.Decl.is_namespace) continue;
                    if (!covered_variants[variant_idx]) {
                        missing = 1;
                        used += snprintf(buf + used, sizeof(buf) - used, "%s %s",
                                         used > 0 && buf[used - 1] == ':' ? "" : ",",
                                         variant->data.data.Decl.name.c_str);
                    }
                    variant_idx++;
                }
                if (missing) type_error(stmt, buf);
            }

            free(covered_variants);

            if (first_if) Expr_add_child(block, first_if);

            // Replace ExprData_TAG_Switch with desugared block
            {
                Expr *slot = (Expr*)Vec_get(&body->children, &(USize){(USize)(i)});
                *slot = *block;
                // Deep-copy children buffer so slot doesn't share with block
                U64 sz = block->children.count * block->children.elem_size;
                slot->children.data = malloc(sz ? sz : 1);
                memcpy(slot->children.data, block->children.data, sz);
                slot->children.cap = block->children.count ? block->children.count : 1;
                block->children = (Vec){0};
            }
            i--; // re-visit to type-check
            break;
        }
        case ExprData_TAG_ForIn: {
            // Validate iterable and desugar to while loop in anonymous scope
            Expr *iter = Expr_child(stmt, &(USize){(USize)(0)});

            // #100: Detect Range.new(start, end) from parser's .. desugaring
            // For scalar types, desugar directly to while loop with inc/dec
            // instead of going through Range.new/len/get
            if (iter->data.tag == ExprData_TAG_FCall &&
                iter->children.count == 3 &&
                Expr_child(iter, &(USize){(USize)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                (Expr_child(iter, &(USize){(USize)(0)})->data.data.FieldAccess.count == 3 && memcmp(Expr_child(iter, &(USize){(USize)(0)})->data.data.FieldAccess.c_str, "new", 3) == 0) &&
                Expr_child(Expr_child(iter, &(USize){(USize)(0)}), &(USize){0})->data.tag == ExprData_TAG_Ident &&
                (Expr_child(Expr_child(iter, &(USize){(USize)(0)}), &(USize){0})->data.data.Ident.count == 5 && memcmp(Expr_child(Expr_child(iter, &(USize){(USize)(0)}), &(USize){0})->data.data.Ident.c_str, "Range", 5) == 0)) {
                Expr *start_expr = Expr_child(iter, &(USize){(USize)(1)});
                Expr *end_expr = Expr_child(iter, &(USize){(USize)(2)});
                // Infer operand types to determine T
                infer_expr(scope, start_expr, in_func);
                infer_expr(scope, end_expr, in_func);
                // T: non-literal wins, both literals -> I64
                Str *elem_type = &stmt->struct_name; // explicit annotation
                if (!elem_type || elem_type->count == 0) {
                    Expr *type_src;
                    if (start_expr->data.tag == ExprData_TAG_LiteralNum && end_expr->data.tag != ExprData_TAG_LiteralNum)
                        type_src = end_expr;
                    else if (end_expr->data.tag == ExprData_TAG_LiteralNum && start_expr->data.tag != ExprData_TAG_LiteralNum)
                        type_src = start_expr;
                    else
                        type_src = start_expr; // both lit -> I64 (default)
                    if ((type_src->til_type.tag == TilType_TAG_Struct || type_src->til_type.tag == TilType_TAG_Enum) &&
                        type_src->struct_name.count > 0)
                        elem_type = &type_src->struct_name;
                    else
                        elem_type = Str_clone(til_type_name_c(&type_src->til_type));
                }

                Str *var_name = &stmt->data.data.Ident;
                Expr *for_body = Expr_child(stmt, &(USize){(USize)(1)});
                I32 line = stmt->line, col = stmt->col;
                Str *path = &stmt->path;
                int counter = hoist_counter++;
                char end_buf[128], cur_buf[128];
                snprintf(end_buf, sizeof(end_buf), "_re_%s_%d", elem_type->c_str, counter);
                snprintf(cur_buf, sizeof(cur_buf), "_rc_%s_%d", elem_type->c_str, counter);
                Str *end_name = Str_clone(&(Str){.c_str = (U8*)(end_buf), .count = (U64)strlen((const char*)(end_buf)), .cap = CAP_VIEW});
                Str *cur_name = Str_clone(&(Str){.c_str = (U8*)(cur_buf), .count = (U64)strlen((const char*)(cur_buf)), .cap = CAP_VIEW});

                // Helper: build id(name)
                #define RID(n) ({ Expr *_e = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path); _e->data.data.Ident = *(n); _e; })
                // Helper: build a.method(b)
                #define RCALL1(obj, meth, mlen, arg) ({ \
                    Expr *_fa = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path); \
                    _fa->data.data.FieldAccess = (Str){.c_str = (U8*)(meth), .count = (mlen), .cap = CAP_LIT}; \
                    Expr_add_child(_fa, obj); \
                    Expr *_fc = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path); \
                    Expr_add_child(_fc, _fa); Expr_add_child(_fc, arg); _fc; })
                // Helper: build a.method()
                #define RCALL0(obj, meth, mlen) ({ \
                    Expr *_fa = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path); \
                    _fa->data.data.FieldAccess = (Str){.c_str = (U8*)(meth), .count = (mlen), .cap = CAP_LIT}; \
                    Expr_add_child(_fa, obj); \
                    Expr *_fc = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path); \
                    Expr_add_child(_fc, _fa); _fc; })

                // Outer block
                Expr *block = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

                // _reN : T = end
                Expr *end_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                end_decl->data.data.Decl.name = *end_name;
                end_decl->data.data.Decl.explicit_type = *elem_type;
                Expr_add_child(end_decl, Expr_clone(end_expr));
                Expr_add_child(block, end_decl);

                // mut _rcN : T = start
                Expr *cur_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                cur_decl->data.data.Decl.name = *cur_name;
                cur_decl->data.data.Decl.explicit_type = *elem_type;
                cur_decl->data.data.Decl.is_mut = true;
                Expr_add_child(cur_decl, Expr_clone(start_expr));
                Expr_add_child(block, cur_decl);

                // Build ascending while: while _rcN.lt(_reN) { i = _rcN; _rcN.inc(); body }
                // Build descending while: while _rcN.gt(_reN) { i = _rcN; _rcN.dec(); body }
                // Wrap in: if _rcN.lte(_reN) { asc_while } else { desc_while }
                Expr *build_while_body(Str *var_name, Str *cur_name, const char *step, U64 step_len, Expr *for_body, I32 line, I32 col, Str *path, Str *elem_type) {
                    Expr *wb = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                    // i : T = _rcN
                    Expr *vd = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
                    vd->data.data.Decl.name = *var_name;
                    vd->data.data.Decl.explicit_type = *elem_type;
                    Expr_add_child(vd, RID(cur_name));
                    Expr_add_child(wb, vd);
                    // _rcN.inc() or _rcN.dec()  -- before body for continue safety
                    Expr_add_child(wb, RCALL0(RID(cur_name), step, step_len));
                    // Copy body
                    for (U32 bi = 0; bi < for_body->children.count; bi++)
                        Expr_add_child(wb, Expr_clone(Expr_child(for_body, &(USize){(USize)(bi)})));
                    return wb;
                }

                // Ascending while: while _rcN.lt(_reN) { ... }
                Expr *asc_while = Expr_new(&(ExprData){.tag = ExprData_TAG_While}, line, col, path);
                Expr_add_child(asc_while, RCALL1(RID(cur_name), "lt", 2, RID(end_name)));
                Expr_add_child(asc_while, build_while_body(var_name, cur_name, "inc", 3, for_body, line, col, path, elem_type));

                // Descending while: while _rcN.gt(_reN) { ... }
                Expr *desc_while = Expr_new(&(ExprData){.tag = ExprData_TAG_While}, line, col, path);
                Expr_add_child(desc_while, RCALL1(RID(cur_name), "gt", 2, RID(end_name)));
                Expr_add_child(desc_while, build_while_body(var_name, cur_name, "dec", 3, for_body, line, col, path, elem_type));

                // if _rcN.lte(_reN) { asc_while } else { desc_while }
                Expr *if_node = Expr_new(&(ExprData){.tag = ExprData_TAG_If}, line, col, path);
                Expr_add_child(if_node, RCALL1(RID(cur_name), "lte", 3, RID(end_name)));
                Expr *then_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                Expr_add_child(then_body, asc_while);
                Expr_add_child(if_node, then_body);
                Expr *else_body = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);
                Expr_add_child(else_body, desc_while);
                Expr_add_child(if_node, else_body);
                Expr_add_child(block, if_node);

                #undef RID
                #undef RCALL1
                #undef RCALL0

                // Replace ForIn with desugared block
                {
                    Expr *slot = (Expr*)Vec_get(&body->children, &(USize){(USize)(i)});
                    *slot = *block;
                    U64 sz = block->children.count * block->children.elem_size;
                    slot->children.data = malloc(sz ? sz : 1);
                    memcpy(slot->children.data, block->children.data, sz);
                    slot->children.cap = block->children.count ? block->children.count : 1;
                    block->children = (Vec){0};
                }
                i--; // re-visit to type-check
                break;
            }

            infer_expr(scope, iter, in_func);

            // Iterable must be a struct type
            Str *type_name = NULL;
            if ((iter->til_type.tag == TilType_TAG_Struct || iter->til_type.tag == TilType_TAG_Enum) && iter->struct_name.count > 0)
                type_name = &iter->struct_name;
            if (!type_name) {
                type_error(stmt, "for-in requires a collection type with get() and len() methods");
                break;
            }

            Expr *sdef = TypeScope_get_struct(scope, type_name);
            if (!sdef) {
                type_error(stmt, "for-in requires a collection type with get() and len() methods");
                break;
            }

            // Find len() and get() in namespace, validate signatures
            Expr *len_func = NULL, *get_func = NULL;
            Expr *sbody = Expr_child(sdef, &(USize){(USize)(0)});
            for (U32 fi = 0; fi < sbody->children.count; fi++) {
                Expr *field = Expr_child(sbody, &(USize){(USize)(fi)});
                if (!field->data.data.Decl.is_namespace) continue;
                if (Expr_child(field, &(USize){(USize)(0)})->data.tag != ExprData_TAG_FuncDef) continue;
                if ((field->data.data.Decl.name.count == 3 && memcmp(field->data.data.Decl.name.c_str, "len", 3) == 0)) len_func = Expr_child(field, &(USize){(USize)(0)});
                if ((field->data.data.Decl.name.count == 3 && memcmp(field->data.data.Decl.name.c_str, "get", 3) == 0)) get_func = Expr_child(field, &(USize){(USize)(0)});
            }

            if (!len_func) {
                char buf[128];
                snprintf(buf, sizeof(buf), "type '%s' has no 'len' method (required for for-in)", type_name->c_str);
                type_error(stmt, buf);
                break;
            }
            if (len_func->data.data.FuncDef.nparam != 1 || (len_func->data.data.FuncDef.return_type).count == 0) {
                char buf[128];
                snprintf(buf, sizeof(buf), "type '%s' len() must take 1 param and return a scalar for for-in", type_name->c_str);
                type_error(stmt, buf);
                break;
            }
            Str *idx_type = &len_func->data.data.FuncDef.return_type;
            if (!get_func) {
                char buf[128];
                snprintf(buf, sizeof(buf), "type '%s' has no 'get' method (required for for-in)", type_name->c_str);
                type_error(stmt, buf);
                break;
            }
            if (get_func->data.data.FuncDef.nparam != 2 || ((Param*)Vec_get(&get_func->data.data.FuncDef.params, &(USize){(USize)(1)}))->ptype.count == 0 ||
                !Str_eq(&((Param*)Vec_get(&get_func->data.data.FuncDef.params, &(USize){(USize)(1)}))->ptype, idx_type)) {
                char buf[128];
                snprintf(buf, sizeof(buf), "type '%s' get() second param must match len() return type for for-in", type_name->c_str);
                type_error(stmt, buf);
                break;
            }

            // Determine element type
            Str *elem_type = &stmt->struct_name; // explicit type annotation from parser
            if (!elem_type) {
                // Infer from get() return type
                Str *ret = &get_func->data.data.FuncDef.return_type;
                if (!ret || (ret->count == 7 && memcmp(ret->c_str, "Dynamic", 7) == 0)) {
                    char buf[192];
                    snprintf(buf, sizeof(buf),
                        "cannot infer element type for '%s', use explicit type: for x : Type in ...",
                        type_name->c_str);
                    type_error(stmt, buf);
                    break;
                }
                elem_type = ret;
            }

            // Build desugared AST:
            // {
            //     mut _fiN := 0
            //     while _fiN.lt(collection.len()) {
            //         ref varname : ElemType = collection.get(_fiN)
            //         _fiN = _fiN.add(1)   // before body so continue doesn't skip
            //         ...body...
            //     }
            // }
            Str *var_name = &stmt->data.data.Ident;
            Expr *for_body = Expr_child(stmt, &(USize){(USize)(1)});
            I32 line = stmt->line;
            I32 col = stmt->col;
            Str *path = &stmt->path;

            // Unique variable names
            int counter = hoist_counter++;
            char col_buf[128], idx_buf[128];
            snprintf(col_buf, sizeof(col_buf), "_fc_%s_%d", type_name->c_str, counter);
            snprintf(idx_buf, sizeof(idx_buf), "_fi_USize_%d", counter);
            Str *col_name = Str_clone(&(Str){.c_str = (U8*)(col_buf), .count = (U64)strlen((const char*)(col_buf)), .cap = CAP_VIEW});
            Str *idx_name = Str_clone(&(Str){.c_str = (U8*)(idx_buf), .count = (U64)strlen((const char*)(idx_buf)), .cap = CAP_VIEW});

            // Outer block (anonymous scope)
            Expr *block = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

            // _fcN := iterable  (hoist iterable into temp, evaluated once)
            Expr *col_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            col_decl->data.data.Decl.name = *col_name;
            col_decl->data.data.Decl.is_mut = false;
            col_decl->data.data.Decl.is_namespace = false;
            col_decl->data.data.Decl.is_ref = false;
            col_decl->data.data.Decl.is_own = false;
            Expr_add_child(col_decl, Expr_clone(iter));
            Expr_add_child(block, col_decl);

            // mut _fiN : IdxType = 0
            Expr *idx_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            idx_decl->data.data.Decl.name = *idx_name;
            idx_decl->data.data.Decl.explicit_type = *idx_type;
            idx_decl->data.data.Decl.is_mut = true;
            idx_decl->data.data.Decl.is_namespace = false;
            idx_decl->data.data.Decl.is_ref = false;
            idx_decl->data.data.Decl.is_own = false;
            Expr *zero = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
            zero->data.data.LiteralNum = (Str){.c_str = (U8*)"0", .count = 1, .cap = CAP_LIT};
            Expr_add_child(idx_decl, zero);
            Expr_add_child(block, idx_decl);

            // while _fiN.lt(collection.len()) { ... }
            Expr *while_node = Expr_new(&(ExprData){.tag = ExprData_TAG_While}, line, col, path);

            // Condition: _fiN.lt(_fcN.len())
            Expr *col_ident_len = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            col_ident_len->data.data.Ident = *col_name;
            Expr *iter_len = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            iter_len->data.data.FieldAccess = (Str){.c_str = (U8*)"len", .count = 3, .cap = CAP_LIT};
            Expr_add_child(iter_len, col_ident_len);
            Expr *len_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(len_call, iter_len);

            // Build: _fiN.lt(len_call) → ExprData_TAG_FCall(ExprData_TAG_FieldAccess(idx_ident, "lt"), len_call)
            Expr *idx_ident_cond = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            idx_ident_cond->data.data.Ident = *idx_name;
            Expr *lt_access = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            lt_access->data.data.FieldAccess = (Str){.c_str = (U8*)"lt", .count = 2, .cap = CAP_LIT};
            Expr_add_child(lt_access, idx_ident_cond);
            Expr *lt_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(lt_call, lt_access);
            Expr_add_child(lt_call, len_call);
            Expr_add_child(while_node, lt_call);

            // While body
            Expr *wbody = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

            // ref varname : ElemType = collection.get(_fiN)  (ref if get returns ref)
            Bool get_returns_ref = get_func->data.data.FuncDef.return_is_ref;
            Expr *elem_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
            elem_decl->data.data.Decl.name = *var_name;
            elem_decl->data.data.Decl.explicit_type = *elem_type;
            elem_decl->data.data.Decl.is_ref = get_returns_ref;
            elem_decl->data.data.Decl.is_mut = false;
            elem_decl->data.data.Decl.is_namespace = false;
            elem_decl->data.data.Decl.is_own = false;

            // _fcN.get(_fiN)
            Expr *col_ident_get = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            col_ident_get->data.data.Ident = *col_name;
            Expr *iter_get = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            iter_get->data.data.FieldAccess = (Str){.c_str = (U8*)"get", .count = 3, .cap = CAP_LIT};
            Expr_add_child(iter_get, col_ident_get);
            Expr *idx_ident_get = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            idx_ident_get->data.data.Ident = *idx_name;
            Expr *get_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(get_call, iter_get);
            Expr_add_child(get_call, idx_ident_get);
            Expr_add_child(elem_decl, get_call);
            Expr_add_child(wbody, elem_decl);

            // _fiN = _fiN.add(1) — placed before user body so continue doesn't skip it
            Expr *idx_assign = Expr_new(&(ExprData){.tag = ExprData_TAG_Assign}, line, col, path);
            idx_assign->data.data.Assign = *idx_name;
            Expr *idx_ident_inc = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            idx_ident_inc->data.data.Ident = *idx_name;
            Expr *add_access = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            add_access->data.data.FieldAccess = (Str){.c_str = (U8*)"add", .count = 3, .cap = CAP_LIT};
            Expr_add_child(add_access, idx_ident_inc);
            Expr *one = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
            one->data.data.LiteralNum = (Str){.c_str = (U8*)"1", .count = 1, .cap = CAP_LIT};
            Expr *add_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
            Expr_add_child(add_call, add_access);
            Expr_add_child(add_call, one);
            Expr_add_child(idx_assign, add_call);
            Expr_add_child(wbody, idx_assign);

            // Copy original body statements
            for (U32 bi = 0; bi < for_body->children.count; bi++) {
                Expr_add_child(wbody, Expr_clone(Expr_child(for_body, &(USize){(USize)(bi)})));
            }

            Expr_add_child(while_node, wbody);
            Expr_add_child(block, while_node);

            // Replace FOR_IN with the desugared block in parent body
            {
                Expr *slot = (Expr*)Vec_get(&body->children, &(USize){(USize)(i)});
                *slot = *block;
                U64 sz = block->children.count * block->children.elem_size;
                slot->children.data = malloc(sz ? sz : 1);
                memcpy(slot->children.data, block->children.data, sz);
                slot->children.cap = block->children.count ? block->children.count : 1;
                block->children = (Vec){0};
            }
            i--; // re-visit to type-check the replacement
            break;
        }
        default:
            stmt->til_type = (TilType){TilType_TAG_None};
            break;
        }
    }
    if (owns_scope) desugar_set_literals(body, scope);
    if (owns_scope) desugar_map_literals(body, scope);
    if (owns_scope) desugar_variadic_calls(body, scope);
    if (owns_scope) desugar_kwargs_calls(body, scope);
    if (owns_scope) hoist_fcall_args(body, scope);
    insert_field_deletes(body);
    insert_free_calls(body, scope, owns_scope);
}

I32 type_check(Expr *program, TypeScope *scope, Mode *mode) {
    errors = 0;
    current_mode = mode;
    infer_body(scope, program, 0, 1, 0, 0, 0);
    return errors;
}
