#include "typer.h"
#include "ast.h"
#include "pre70.h"
#include "initer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type inference/checking pass ---

static I32 errors;
static const Mode *current_mode;

static void type_error(Expr *e, const char *msg) {
    fprintf(stderr, "%s:%u:%u: type error: %s\n", e->path.c_str, e->line, e->col, msg);
    errors++;
}

// Parse a type name string to TilType (scope-aware for user-defined struct types)
static TilType type_from_name(Str *name, TypeScope *scope) {
    if ((name->count == 3 && memcmp(name->c_str, "I64", 3) == 0))  return (TilType){TilType_TAG_I64};
    if ((name->count == 2 && memcmp(name->c_str, "U8", 2) == 0))   return (TilType){TilType_TAG_U8};
    if ((name->count == 3 && memcmp(name->c_str, "I16", 3) == 0))  return (TilType){TilType_TAG_I16};
    if ((name->count == 3 && memcmp(name->c_str, "I32", 3) == 0))  return (TilType){TilType_TAG_I32};
    if ((name->count == 3 && memcmp(name->c_str, "U32", 3) == 0))  return (TilType){TilType_TAG_U32};
    if ((name->count == 3 && memcmp(name->c_str, "U64", 3) == 0))  return (TilType){TilType_TAG_U64};
    if ((name->count == 3 && memcmp(name->c_str, "F32", 3) == 0))  return (TilType){TilType_TAG_F32};
    if ((name->count == 3 && memcmp(name->c_str, "Str", 3) == 0))  return (TilType){TilType_TAG_Struct};
    if ((name->count == 4 && memcmp(name->c_str, "Bool", 4) == 0)) return (TilType){TilType_TAG_Bool};
    if ((name->count == 9 && memcmp(name->c_str, "StructDef", 9) == 0))    return (TilType){TilType_TAG_StructDef};
    if ((name->count == 7 && memcmp(name->c_str, "EnumDef", 7) == 0))      return (TilType){TilType_TAG_EnumDef};
    // FunctionDef: regular struct (like Str), resolved via scope lookup
    if ((name->count == 2 && memcmp(name->c_str, "Fn", 2) == 0))          return (TilType){TilType_TAG_FuncPtr};
    if ((name->count == 7 && memcmp(name->c_str, "Dynamic", 7) == 0))     return (TilType){TilType_TAG_Dynamic};
    // Check scope for user-defined struct/enum types
    if (scope) {
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) return (sdef->data.tag == ExprData_TAG_EnumDef) ? (TilType){TilType_TAG_Enum} : (TilType){TilType_TAG_Struct};
        // Named FuncSig type (bodyless func/proc)
        TypeBinding *b = tscope_find(scope, name);
        if (b && b->func_def && b->func_def->children.count == 0)
            return (TilType){TilType_TAG_FuncPtr};
    }
    return (TilType){TilType_TAG_Unknown};
}

static void infer_expr(TypeScope *scope, Expr *e, I32 in_func);
static void infer_body(TypeScope *scope, Expr *body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref);
static const char *type_to_name(TilType type, Str *struct_name);
static Expr *make_clone_call(const char *type_name, TilType type, Expr *arg, Expr *src);
static Expr *make_ns_call(const char *sname, const char *method,
                           TilType ret_type, Str *ret_sname, Expr *src);
static I32 fcall_returns_ref(Expr *fcall, TypeScope *scope);

// Narrow a Dynamic-typed expression to a concrete target type.
// Used for both declarations with explicit types and function arguments.
static void narrow_dynamic(Expr *expr, TilType target, Str *target_struct_name) {
    if (expr->til_type.tag != TilType_TAG_Dynamic || target.tag == TilType_TAG_Dynamic ||
        target.tag == TilType_TAG_Unknown)
        return;
    expr->til_type = target;
    if (target.tag == TilType_TAG_Struct || target.tag == TilType_TAG_Enum)
        expr->struct_name = *target_struct_name;
}

static Bool is_numeric_type(TilType t) {
    return t.tag == TilType_TAG_I64 || t.tag == TilType_TAG_U8 || t.tag == TilType_TAG_I16 ||
           t.tag == TilType_TAG_I32 || t.tag == TilType_TAG_U32 || t.tag == TilType_TAG_U64 ||
           t.tag == TilType_TAG_F32;
}

static Bool literal_in_range(const char *val_str, TilType target) {
    long long val = strtoll(val_str, NULL, 10);
    switch (target.tag) {
        case TilType_TAG_U8:  return val >= 0 && val <= 255;
        case TilType_TAG_I16: return val >= -32768 && val <= 32767;
        case TilType_TAG_I32: return val >= -2147483648LL && val <= 2147483647LL;
        case TilType_TAG_U32: return val >= 0 && val <= 4294967295LL;
        case TilType_TAG_U64: return val >= 0;
        case TilType_TAG_I64: return 1;
        case TilType_TAG_F32: return 1;
        default: return 1;
    }
}

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
        TilType t = tscope_get(scope, &e->data.data.Ident);
        if (t.tag == TilType_TAG_Unknown) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined symbol '%s'", e->data.data.Ident.c_str);
            type_error(e, buf);
        }
        e->til_type = t;
        if (t.tag == TilType_TAG_Struct || t.tag == TilType_TAG_Enum) {
            TypeBinding *b = tscope_find(scope, &e->data.data.Ident);
            if (b && b->struct_name) e->struct_name = *b->struct_name;
        }
        // Function references: identifier refers to a function → Fn type
        {
            TypeBinding *fb = tscope_find(scope, &e->data.data.Ident);
            if (fb && fb->func_def) {
                e->til_type = (TilType){TilType_TAG_FuncPtr};
            }
        }
        // Struct type names: allow field access for namespace fields
        TypeBinding *ib = tscope_find(scope, &e->data.data.Ident);
        if (ib && ib->struct_def) {
            e->struct_name = e->data.data.Ident;
        }
        break;
    }
    case ExprData_TAG_FuncDef:
        if (e->children.count == 0) {
            // Bodyless = FuncSig type definition, no body to type
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
            TypeScope *func_scope = tscope_new(scope);
            // Bind parameters
            for (U32 i = 0; i < e->data.data.FuncDef.nparam; i++) {
                Str *ptn = ((Str*)Vec_get(&e->data.data.FuncDef.param_types, &(U64){(U64)(i)}));
                TilType pt = type_from_name(ptn, scope);
                if (pt.tag == TilType_TAG_Unknown) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", ptn->c_str);
                    type_error(e, buf);
                }
                Bool pmut = e->data.data.FuncDef.param_muts.count > 0 ? (*(Bool*)Vec_get(&e->data.data.FuncDef.param_muts, &(U64){(U64)(i)})) : 0;
                Bool pown = e->data.data.FuncDef.param_owns.count > 0 ? (*(Bool*)Vec_get(&e->data.data.FuncDef.param_owns, &(U64){(U64)(i)})) : 0;
                Bool pshallow = e->data.data.FuncDef.param_shallows.count > 0 ? (*(Bool*)Vec_get(&e->data.data.FuncDef.param_shallows, &(U64){(U64)(i)})) : 0;
                if (pshallow) {
                    Bool is_scalar = (pt.tag == TilType_TAG_I64 || pt.tag == TilType_TAG_U8 || pt.tag == TilType_TAG_I16 ||
                                      pt.tag == TilType_TAG_I32 || pt.tag == TilType_TAG_U32 || pt.tag == TilType_TAG_U64 || pt.tag == TilType_TAG_F32 || pt.tag == TilType_TAG_Bool);
                    if (!is_scalar && pt.tag != TilType_TAG_Struct && pt.tag != TilType_TAG_StructDef) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "shallow parameter '%s' must be a scalar or struct type",
                                 ((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)}))->c_str);
                        type_error(e, buf);
                    }
                    if (pown) type_error(e, "parameter cannot be both 'shallow' and 'own'");
                }
                // Variadic param: bind as Array (element type already validated above)
                if ((I32)i == e->data.data.FuncDef.variadic_index) {
                    if (VEC_SET(e->data.data.FuncDef.param_owns)) (*(Bool*)Vec_get(&e->data.data.FuncDef.param_owns, &(U64){(U64)(i)})) = true;
                    tscope_set(func_scope, ((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)})), (TilType){TilType_TAG_Struct}, -1, 0, e->line, e->col, 1, 1);
                    TypeBinding *pb = tscope_find(func_scope, ((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)})));
                    if (pb) pb->struct_name = Str_clone(&(Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT});
                } else if ((I32)i == e->data.data.FuncDef.kwargs_index) {
                    // Kwargs param: bind as Map
                    if (VEC_SET(e->data.data.FuncDef.param_owns)) (*(Bool*)Vec_get(&e->data.data.FuncDef.param_owns, &(U64){(U64)(i)})) = true;
                    tscope_set(func_scope, ((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)})), (TilType){TilType_TAG_Struct}, -1, 0, e->line, e->col, 1, 1);
                    TypeBinding *pb = tscope_find(func_scope, ((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)})));
                    if (pb) pb->struct_name = Str_clone(&(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT});
                } else {
                    tscope_set(func_scope, ((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)})), pt, -1, pmut, e->line, e->col, 1, pown);
                    // For struct/enum-typed params, store struct_name
                    if (pt.tag == TilType_TAG_Struct || pt.tag == TilType_TAG_Enum) {
                        TypeBinding *pb = tscope_find(func_scope, ((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)})));
                        if (pb) pb->struct_name = ptn;
                    }
                    // For Fn-typed params with signature, propagate func_def
                    if (pt.tag == TilType_TAG_FuncPtr && e->data.data.FuncDef.param_fn_sigs.count > 0 &&
                        (*(Expr**)Vec_get(&e->data.data.FuncDef.param_fn_sigs, &(U64){(U64)(i)}))) {
                        TypeBinding *pb = tscope_find(func_scope, ((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)})));
                        if (pb) pb->func_def = (*(Expr**)Vec_get(&e->data.data.FuncDef.param_fn_sigs, &(U64){(U64)(i)}));
                    }
                    // For named FuncSig params (no inline sig), resolve from outer scope
                    if (pt.tag == TilType_TAG_FuncPtr &&
                        !(VEC_SET(e->data.data.FuncDef.param_fn_sigs) && (*(Expr**)Vec_get(&e->data.data.FuncDef.param_fn_sigs, &(U64){(U64)(i)})))) {
                        TypeBinding *fsb = tscope_find(scope, ptn);
                        if (fsb && fsb->func_def && fsb->func_def->children.count == 0) {
                            TypeBinding *pb = tscope_find(func_scope, ((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)})));
                            if (pb) pb->func_def = fsb->func_def;
                        }
                    }
                }
            }
            infer_body(func_scope, Expr_child(e, &(I64){(I64)(0)}), is_func, 1, 0, e->data.data.FuncDef.return_is_ref);
            // Check: func/macro must have a return type
            if ((is_func || is_macro) && (e->data.data.FuncDef.return_type).count == 0) {
                type_error(e, is_macro ? "macro must declare a return type"
                                             : "func must declare a return type");
            }
            // Validate ref returns: every return value must be a param or ref variable
            if (e->data.data.FuncDef.return_is_ref) {
                Expr *body = Expr_child(e, &(I64){(I64)(0)});
                for (U32 ri = 0; ri < body->children.count; ri++) {
                    Expr *s = Expr_child(body, &(I64){(I64)(ri)});
                    if (s->data.tag != ExprData_TAG_Return || s->children.count == 0) continue;
                    Expr *rv = Expr_child(s, &(I64){(I64)(0)});
                    Bool ok = 0;
                    if (rv->data.tag == ExprData_TAG_Ident) {
                        TypeBinding *rb = tscope_find(func_scope, &rv->data.data.Ident);
                        if (rb && (rb->is_param || rb->is_ref)) ok = 1;
                    }
                    if (rv->data.tag == ExprData_TAG_FCall && fcall_returns_ref(rv, func_scope)) ok = 1;
                    if (!ok) type_error(s, "ref function must return a parameter or ref variable");
                }
            }
            tscope_free(func_scope);
        }
        break;
    case ExprData_TAG_StructDef:
    case ExprData_TAG_EnumDef: {
        e->til_type = (TilType){TilType_TAG_None};
        // Reject ref payloads in tagged enum variants
        if (e->data.tag == ExprData_TAG_EnumDef) {
            Expr *body = Expr_child(e, &(I64){(I64)(0)});
            for (U32 vi = 0; vi < body->children.count; vi++) {
                Expr *v = Expr_child(body, &(I64){(I64)(vi)});
                if (v->data.tag == ExprData_TAG_Decl && !v->data.data.Decl.is_namespace &&
                    (v->data.data.Decl.explicit_type).count > 0 && v->data.data.Decl.is_ref) {
                    type_error(v, "ref payloads in tagged enum variants are not supported");
                }
            }
        }
        // Type-check field declarations in a child scope so fields
        // don't leak into outer scope's locals for free-call insertion
        TypeScope *inner = tscope_new(scope);
        infer_body(inner, Expr_child(e, &(I64){(I64)(0)}), 0, 0, 0, 0);
        tscope_free(inner);
        break;
    }
    case ExprData_TAG_FCall: {
        // Namespace method call or UFCS: Type.method(args) or instance.method(args)
        if (Expr_child(e, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FieldAccess) {
            Expr *fa = Expr_child(e, &(I64){(I64)(0)});
            Expr *obj = Expr_child(fa, &(I64){(I64)(0)});
            Str *method = &fa->data.data.FieldAccess;

            // Type just the object first (not the full field access)
            infer_expr(scope, obj, in_func);

            // Check: is obj a type name (has struct_def) or an instance/value?
            TypeBinding *tb = (obj->data.tag == ExprData_TAG_Ident)
                ? tscope_find(scope, &obj->data.data.Ident) : NULL;
            Bool obj_is_type = (tb && tb->struct_def);

            if (!obj_is_type) {
                // UFCS: instance.method(args) -> Type.method(instance, args)
                Str *type_name = NULL;
                if (obj->til_type.tag >= TilType_TAG_I64 && obj->til_type.tag <= TilType_TAG_Bool)
                    type_name = til_type_name_c(&obj->til_type);
                else if ((obj->til_type.tag == TilType_TAG_Struct || obj->til_type.tag == TilType_TAG_Enum) && obj->struct_name.count > 0)
                    type_name = &obj->struct_name;

                Expr *sdef = type_name ? tscope_get_struct(scope, type_name) : NULL;
                Expr *ns_func = NULL;
                if (sdef) {
                    Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
                    for (U32 i = 0; i < body->children.count; i++) {
                        Expr *field = Expr_child(body, &(I64){(I64)(i)});
                        if (field->data.data.Decl.is_namespace &&
                            *Str_eq(&field->data.data.Decl.name, method) &&
                            Expr_child(field, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FuncDef) {
                            ns_func = Expr_child(field, &(I64){(I64)(0)});
                            break;
                        }
                    }
                }
                if (!ns_func) {
                    // UFCS fallback: check top-level for f(a: T, ...)
                    TypeBinding *top = tscope_find(scope, method);
                    Bool ufcs_match = 0;
                    if (top && top->func_def &&
                        top->func_def->data.data.FuncDef.nparam > 0 &&
                        ((Str*)Vec_get(&top->func_def->data.data.FuncDef.param_types, &(U64){(U64)(0)}))) {
                        Str *first_param = ((Str*)Vec_get(&top->func_def->data.data.FuncDef.param_types, &(U64){(U64)(0)}));
                        if (type_name && *Str_eq(first_param, type_name)) {
                            ufcs_match = 1; // known type matches first param
                        } else if (!type_name && obj->til_type.tag == TilType_TAG_Dynamic) {
                            // Dynamic receiver: narrow to first param type
                            TilType pt = type_from_name(first_param, scope);
                            narrow_dynamic(obj, pt, first_param);
                            ufcs_match = 1;
                        }
                    }
                    if (ufcs_match) {
                        // Rewrite: a.f(b) → f(a, b)
                        Expr *fn_ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, fa->line, fa->col, &fa->path);
                        fn_ident->data.data.Ident = *method;
                        *(Expr*)Vec_get(&e->children, &(U64){(U64)(0)}) = *fn_ident;
                        // Insert instance as first arg
                        Expr *instance = obj;
                        Expr dummy = {0};
                        { Expr *_p = malloc(sizeof(Expr)); *_p = dummy; Vec_push(&e->children, _p); }
                        {
                            Expr *ch = (Expr *)e->children.data;
                            memmove(&ch[2], &ch[1], (e->children.count - 2) * sizeof(Expr));
                        }
                        *(Expr*)Vec_get(&e->children, &(U64){(U64)(1)}) = *Expr_clone(instance);
                        goto regular_call;
                    }
                    // Fallback: check if method is a FuncSig-typed struct field
                    // e.g. h.on_click(3, 5) where on_click is a BinaryOp field
                    if (sdef && (obj->til_type.tag == TilType_TAG_Struct || obj->til_type.tag == TilType_TAG_Enum)) {
                        Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
                        for (U32 fi = 0; fi < body->children.count; fi++) {
                            Expr *field = Expr_child(body, &(I64){(I64)(fi)});
                            if (field->data.tag != ExprData_TAG_Decl || field->data.data.Decl.is_namespace) continue;
                            if (!*Str_eq(&field->data.data.Decl.name, method)) continue;
                            if (field->data.data.Decl.explicit_type.count == 0) continue;
                            TypeBinding *ftb = tscope_find(scope, &field->data.data.Decl.explicit_type);
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
                                    infer_expr(scope, Expr_child(e, &(I64){(I64)(ai + 1)}), in_func);
                                }
                                e->fn_sig = sig;
                                if (sig->data.data.FuncDef.return_type.count > 0) {
                                    e->til_type = type_from_name(&sig->data.data.FuncDef.return_type, scope);
                                    if ((e->til_type.tag == TilType_TAG_Struct || e->til_type.tag == TilType_TAG_Enum))
                                        e->struct_name = sig->data.data.FuncDef.return_type;
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
                Expr *instance = Expr_clone(obj); // clone before fa->children overwrite
                Expr *type_ident = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, obj->line, obj->col, &obj->path);
                type_ident->data.data.Ident = *type_name;
                *(Expr*)Vec_get(&fa->children, &(U64){(U64)(0)}) = *type_ident;
                // Insert instance as first arg
                Expr dummy = {0};
                { Expr *_p = malloc(sizeof(Expr)); *_p = dummy; Vec_push(&e->children, _p); }
                {
                    Expr *ch = (Expr *)e->children.data;
                    memmove(&ch[2], &ch[1], (e->children.count - 2) * sizeof(Expr));
                }
                *(Expr*)Vec_get(&e->children, &(U64){(U64)(1)}) = *instance;
                // Fall through -- existing code below handles Type.method(instance, args)
                // Re-fetch after e->children mutation (push may realloc)
                fa = Expr_child(e, &(I64){(I64)(0)});
                method = &fa->data.data.FieldAccess;
            }

            // Type the (possibly new) object and look up namespace func
            obj = Expr_child(fa, &(I64){(I64)(0)});
            if (obj->til_type.tag == TilType_TAG_Unknown) {
                infer_expr(scope, obj, in_func);
            }
            Expr *sdef = (obj->struct_name).count > 0 ? tscope_get_struct(scope, &obj->struct_name) : NULL;
            Expr *ns_func = NULL;
            if (sdef) {
                Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
                for (U32 i = 0; i < body->children.count; i++) {
                    Expr *field = Expr_child(body, &(I64){(I64)(i)});
                    if (field->data.data.Decl.is_namespace &&
                        *Str_eq(&field->data.data.Decl.name, method) &&
                        Expr_child(field, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FuncDef) {
                        ns_func = Expr_child(field, &(I64){(I64)(0)});
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
                    Expr *arg = Expr_child(e, &(I64){(I64)(i)});
                    if (arg->data.tag == ExprData_TAG_NamedArg) {
                        seen_named = 1;
                        Str *aname = &arg->data.data.Ident;
                        I32 slot = -1;
                        for (U32 j = 0; j < np; j++) {
                            if (*Str_eq(((Str*)Vec_get(&ns_func->data.data.FuncDef.param_names, &(U64){(U64)(j)})), aname)) {
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
                            new_args[slot] = Expr_clone(Expr_child(arg, &(I64){(I64)(0)})); // unwrap ExprData_TAG_NamedArg
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
                        if (VEC_SET(ns_func->data.data.FuncDef.param_defaults) &&
                            (*(Expr**)Vec_get(&ns_func->data.data.FuncDef.param_defaults, &(U64){(U64)(i)}))) {
                            new_args[i] = Expr_clone((*(Expr**)Vec_get(&ns_func->data.data.FuncDef.param_defaults, &(U64){(U64)(i)})));
                        } else {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "missing argument for parameter '%s'",
                                     ((Str*)Vec_get(&ns_func->data.data.FuncDef.param_names, &(U64){(U64)(i)}))->c_str);
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
                Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
                Expr *callee = Expr_child(e, &(I64){(I64)(0)});
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
                infer_expr(scope, Expr_child(e, &(I64){(I64)(i)}), in_func);
            }
            // Narrow Dynamic args to parameter types
            for (U32 i = 1; i < e->children.count && i - 1 < ns_func->data.data.FuncDef.nparam; i++) {
                Str *ptype = ((Str*)Vec_get(&ns_func->data.data.FuncDef.param_types, &(U64){(U64)(i - 1)}));
                if (ptype)
                    narrow_dynamic(Expr_child(e, &(I64){(I64)(i)}), type_from_name(ptype, scope), ptype);
            }
            // Validate arg types against param types
            for (U32 i = 1; i < e->children.count && i - 1 < ns_func->data.data.FuncDef.nparam; i++) {
                Str *ptype_name = ((Str*)Vec_get(&ns_func->data.data.FuncDef.param_types, &(U64){(U64)(i - 1)}));
                if (!ptype_name) continue;
                Expr *arg = Expr_child(e, &(I64){(I64)(i)});
                if (arg->til_type.tag == TilType_TAG_Dynamic) continue;
                TilType ptype = type_from_name(ptype_name, scope);
                if (ptype.tag == TilType_TAG_Dynamic) continue;
                if (arg->data.tag == ExprData_TAG_LiteralNum && is_numeric_type(ptype)) {
                    if (!literal_in_range((const char *)arg->data.data.Ident.c_str, ptype)) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "integer literal %s out of range for %s",
                                 arg->data.data.Ident.c_str, til_type_name_c(&ptype)->c_str);
                        type_error(arg, buf);
                    }
                    arg->til_type = ptype; continue;
                }
                if (arg->til_type.tag != ptype.tag) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             ((Str*)Vec_get(&ns_func->data.data.FuncDef.param_names, &(U64){(U64)(i - 1)}))->c_str,
                             ptype_name->c_str, til_type_name_c(&arg->til_type)->c_str);
                    type_error(arg, buf);
                } else if ((ptype.tag == TilType_TAG_Struct || ptype.tag == TilType_TAG_Enum) &&
                           (arg->struct_name).count > 0 && !*Str_eq(ptype_name, &arg->struct_name)) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             ((Str*)Vec_get(&ns_func->data.data.FuncDef.param_names, &(U64){(U64)(i - 1)}))->c_str,
                             ptype_name->c_str, arg->struct_name.c_str);
                    type_error(arg, buf);
                }
            }
            // Validate 'own' markers on arguments
            {
                Vec po = ns_func->data.data.FuncDef.param_owns;
                if (VEC_SET(po)) {
                    U32 np = ns_func->data.data.FuncDef.nparam;
                    for (U32 i = 1; i < e->children.count && i - 1 < np; i++) {
                        Bool pown = (*(Bool*)Vec_get(&po, &(U64){(U64)(i - 1)}));
                        if (pown && !Expr_child(e, &(I64){(I64)(i)})->is_own_arg) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "argument for 'own' parameter '%s' must be marked 'own' [tag=%d own=%d]",
                                     ((Str*)Vec_get(&ns_func->data.data.FuncDef.param_names, &(U64){(U64)(i - 1)}))->c_str,
                                     Expr_child(e, &(I64){(I64)(i)})->data.tag,
                                     Expr_child(e, &(I64){(I64)(i)})->is_own_arg);
                            type_error(Expr_child(e, &(I64){(I64)(i)}), buf);
                        } else if (!pown && Expr_child(e, &(I64){(I64)(i)})->is_own_arg) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                                     ((Str*)Vec_get(&ns_func->data.data.FuncDef.param_names, &(U64){(U64)(i - 1)}))->c_str);
                            type_error(Expr_child(e, &(I64){(I64)(i)}), buf);
                        }
                        if (pown && Expr_child(e, &(I64){(I64)(i)})->data.tag == ExprData_TAG_Ident) {
                            TypeBinding *ab = tscope_find(scope, &Expr_child(e, &(I64){(I64)(i)})->data.data.Ident);
                            if (ab && ab->is_ref) type_error(Expr_child(e, &(I64){(I64)(i)}), "cannot pass ref variable to 'own' parameter; use .clone() to make an owned copy");
                        }
                        if (pown && Expr_child(e, &(I64){(I64)(i)})->data.tag == ExprData_TAG_LiteralNull)
                            type_error(Expr_child(e, &(I64){(I64)(i)}), "cannot pass null to 'own' parameter");
                        Vec ps_vec = ns_func->data.data.FuncDef.param_shallows;
                        if (VEC_SET(ps_vec) && (*(Bool*)Vec_get(&ps_vec, &(U64){(U64)(i - 1)})) && Expr_child(e, &(I64){(I64)(i)})->data.tag == ExprData_TAG_LiteralNull)
                            type_error(Expr_child(e, &(I64){(I64)(i)}), "cannot pass null to 'shallow' parameter");
                    }
                }
            }
            // Set return type
            TilType rt = (TilType){TilType_TAG_None};
            if (ns_func->data.data.FuncDef.return_type.count > 0) {
                rt = type_from_name(&ns_func->data.data.FuncDef.return_type, scope);
            }
            e->til_type = rt;
            if ((rt.tag == TilType_TAG_Struct || rt.tag == TilType_TAG_Enum) && (ns_func->data.data.FuncDef.return_type).count > 0) {
                e->struct_name = ns_func->data.data.FuncDef.return_type;
            }
            break;
        }
        regular_call:;
        // Resolve callee
        Str _name_val = Expr_child(e, &(I64){(I64)(0)})->data.data.Ident;
        Str *name = &_name_val;
        // Struct instantiation: Point() or Point(x=1, y=2)
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) {
            TypeBinding *sb = tscope_find(scope, name);
            if (sb && sb->is_builtin && !sb->is_ext) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot instantiate builtin type '%s'", name->c_str);
                type_error(e, buf);
                e->til_type = (TilType){TilType_TAG_Unknown};
                break;
            }
            Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
            // Count instance fields (skip namespace)
            U32 nfields = 0;
            for (U32 i = 0; i < body->children.count; i++) {
                if (!Expr_child(body, &(I64){(I64)(i)})->data.data.Decl.is_namespace) nfields++;
            }
            // Desugar named args into positional (one per instance field)
            Expr **field_vals = calloc(nfields, sizeof(Expr *));
            // Map: field_idx[k] = index into body->children for k-th instance field
            I32 *field_idx = malloc(nfields * sizeof(I32));
            { I32 k = 0;
              for (U32 i = 0; i < body->children.count; i++) {
                  if (!Expr_child(body, &(I64){(I64)(i)})->data.data.Decl.is_namespace) field_idx[k++] = i;
              }
            }
            for (U32 i = 1; i < e->children.count; i++) {
                Expr *arg = Expr_child(e, &(I64){(I64)(i)});
                if (arg->data.tag != ExprData_TAG_NamedArg) {
                    type_error(arg, "struct instantiation requires named arguments");
                    continue;
                }
                Str *aname = &arg->data.data.Ident;
                I32 slot = -1;
                for (U32 j = 0; j < nfields; j++) {
                    if (*Str_eq(&Expr_child(body, &(I64){(I64)(field_idx[j])})->data.data.Decl.name, aname)) {
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
                    field_vals[slot] = Expr_clone(Expr_child(arg, &(I64){(I64)(0)})); // unwrap ExprData_TAG_NamedArg
                }
            }
            // Fill remaining from struct field defaults (clone to avoid shared ownership)
            for (U32 i = 0; i < nfields; i++) {
                if (!field_vals[i]) {
                    field_vals[i] = Expr_clone(Expr_child(Expr_child(body, &(I64){(I64)(field_idx[i])}), &(I64){(I64)(0)}));
                }
            }
            // Rebuild children: callee + instance field values
            Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
            Expr *callee = Expr_child(e, &(I64){(I64)(0)});
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
                if (Expr_child(e, &(I64){(I64)(i)})->til_type.tag == TilType_TAG_Unknown) {
                    infer_expr(scope, Expr_child(e, &(I64){(I64)(i)}), in_func);
                }
            }
            // Auto-insert clone for constructor args that are identifiers
            // Skip clone for `own` fields — use move semantics instead
            { U32 fi = 0;
              for (U32 bi = 0; bi < body->children.count && fi < e->children.count - 1; bi++) {
                Expr *fld = Expr_child(body, &(I64){(I64)(bi)});
                if (fld->data.data.Decl.is_namespace) continue;
                I32 ai = fi + 1; // arg index (children[0] is callee)
                fi++;
                if (fld->data.data.Decl.is_own) {
                    // own field: mark for move, don't clone
                    if (Expr_child(e, &(I64){(I64)(ai)})->data.tag == ExprData_TAG_Ident)
                        Expr_child(e, &(I64){(I64)(ai)})->is_own_arg = 1;
                    continue;
                }
                if (fld->data.data.Decl.is_ref) {
                    // ref field: store pointer, don't clone
                    continue;
                }
                if (Expr_child(e, &(I64){(I64)(ai)})->data.tag == ExprData_TAG_Ident) {
                    const char *tname = type_to_name(Expr_child(e, &(I64){(I64)(ai)})->til_type,
                                                      &Expr_child(e, &(I64){(I64)(ai)})->struct_name);
                    if (tname) {
                        *(Expr*)Vec_get(&e->children, &(U64){(U64)(ai)}) = *make_clone_call(tname,
                            Expr_child(e, &(I64){(I64)(ai)})->til_type, Expr_child(e, &(I64){(I64)(ai)}),
                            Expr_child(e, &(I64){(I64)(ai)}));
                    }
                }
              }
            }
            e->til_type = (TilType){TilType_TAG_Struct};
            e->struct_name = *name;
            break;
        }
        // Desugar named/optional args for user-defined functions (skip core builtins)
        TypeBinding *callee_bind = tscope_find(scope, name);
        if (callee_bind && callee_bind->func_def &&
            (!callee_bind->is_builtin || !callee_bind->func_def->is_core)) {
            Expr *fdef = callee_bind->func_def;
            U32 nparam = fdef->data.data.FuncDef.nparam;
            I32 vi = fdef->data.data.FuncDef.variadic_index; // -1 if not variadic
            I32 kwi = fdef->data.data.FuncDef.kwargs_index;  // -1 if no kwargs
            U32 fixed_count = (vi >= 0) ? (U32)vi : nparam; // params before variadic
            // Collect positional and named args
            Vec va_args; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); va_args = *_vp; free(_vp); } // variadic args (only if vi >= 0)
            Vec kw_args; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr *)}); kw_args = *_vp; free(_vp); } // kwargs args (ExprData_TAG_NamedArg nodes)
            Expr **new_args = calloc(nparam, sizeof(Expr *));
            U32 pos_idx = 0;
            Bool seen_named = 0;
            for (U32 i = 1; i < e->children.count; i++) {
                Expr *arg = Expr_child(e, &(I64){(I64)(i)});
                if (arg->data.tag == ExprData_TAG_NamedArg) {
                    seen_named = 1;
                    Str *aname = &arg->data.data.Ident;
                    I32 slot = -1;
                    for (U32 j = 0; j < nparam; j++) {
                        if ((I32)j == vi) continue; // can't name the variadic param
                        if ((I32)j == kwi) continue; // can't name the kwargs param
                        if (*Str_eq(((Str*)Vec_get(&fdef->data.data.FuncDef.param_names, &(U64){(U64)(j)})), aname)) {
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
                        new_args[slot] = Expr_clone(Expr_child(arg, &(I64){(I64)(0)})); // unwrap ExprData_TAG_NamedArg
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
                    if (VEC_SET(fdef->data.data.FuncDef.param_defaults) &&
                        (*(Expr**)Vec_get(&fdef->data.data.FuncDef.param_defaults, &(U64){(U64)(i)}))) {
                        new_args[i] = Expr_clone((*(Expr**)Vec_get(&fdef->data.data.FuncDef.param_defaults, &(U64){(U64)(i)})));
                    } else {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "missing argument for parameter '%s'",
                                 ((Str*)Vec_get(&fdef->data.data.FuncDef.param_names, &(U64){(U64)(i)}))->c_str);
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
            Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
            Expr *callee = Expr_child(e, &(I64){(I64)(0)});
            Vec_push(&new_ch, Expr_clone(callee));
            for (U32 i = 0; i < nparam; i++) {
                if ((I32)i == vi) {
                    e->variadic_index = new_ch.count; // children index of first variadic arg
                    for (U32 j = 0; j < va_args.count; j++) {
                        Expr *va = *(Expr **)Vec_get(&va_args, &(U64){(U64)(j)});
                        Vec_push(&new_ch, Expr_clone(va));
                    }
                    e->variadic_count = va_args.count;
                } else if ((I32)i == kwi) {
                    e->kwargs_index = new_ch.count; // children index of first kwargs arg
                    for (U32 j = 0; j < kw_args.count; j++) {
                        Expr *kw = *(Expr **)Vec_get(&kw_args, &(U64){(U64)(j)});
                        Vec_push(&new_ch, Expr_clone(kw));
                    }
                    e->kwargs_count = kw_args.count;
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
            infer_expr(scope, Expr_child(e, &(I64){(I64)(i)}), in_func);
        }
        // Narrow Dynamic args to parameter types, then validate arg types
        if (callee_bind && callee_bind->func_def) {
            Expr *fdef = callee_bind->func_def;
            I32 fvi = fdef->data.data.FuncDef.variadic_index;
            I32 fkwi = fdef->data.data.FuncDef.kwargs_index;
            U32 fvc = (fvi >= 0) ? e->variadic_count : 0;
            U32 fkc = (fkwi >= 0) ? e->kwargs_count : 0;
            U32 ci = 1;
            for (U32 pi = 0; pi < fdef->data.data.FuncDef.nparam && ci < e->children.count; pi++) {
                if (fvi >= 0 && (I32)pi == fvi) { ci += fvc; continue; }
                if (fkwi >= 0 && (I32)pi == fkwi) { ci += fkc; continue; }
                Str *ptype = ((Str*)Vec_get(&fdef->data.data.FuncDef.param_types, &(U64){(U64)(pi)}));
                if (ptype)
                    narrow_dynamic(Expr_child(e, &(I64){(I64)(ci)}), type_from_name(ptype, scope), ptype);
                ci++;
            }
            // Validate arg types against param types
            ci = 1;
            for (U32 pi = 0; pi < fdef->data.data.FuncDef.nparam && ci < e->children.count; pi++) {
                if (fvi >= 0 && (I32)pi == fvi) { ci += fvc; continue; }
                if (fkwi >= 0 && (I32)pi == fkwi) { ci += fkc; continue; }
                Str *ptype_name = ((Str*)Vec_get(&fdef->data.data.FuncDef.param_types, &(U64){(U64)(pi)}));
                if (!ptype_name) { ci++; continue; }
                Expr *arg = Expr_child(e, &(I64){(I64)(ci)});
                if (arg->til_type.tag == TilType_TAG_Dynamic) { ci++; continue; }
                TilType ptype = type_from_name(ptype_name, scope);
                if (ptype.tag == TilType_TAG_Dynamic) { ci++; continue; }
                if (arg->data.tag == ExprData_TAG_LiteralNum && is_numeric_type(ptype)) {
                    if (!literal_in_range((const char *)arg->data.data.Ident.c_str, ptype)) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "integer literal %s out of range for %s",
                                 arg->data.data.Ident.c_str, til_type_name_c(&ptype)->c_str);
                        type_error(arg, buf);
                    }
                    arg->til_type = ptype; ci++; continue;
                }
                if (arg->til_type.tag != ptype.tag) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             ((Str*)Vec_get(&fdef->data.data.FuncDef.param_names, &(U64){(U64)(pi)}))->c_str,
                             ptype_name->c_str, til_type_name_c(&arg->til_type)->c_str);
                    type_error(arg, buf);
                } else if ((ptype.tag == TilType_TAG_Struct || ptype.tag == TilType_TAG_Enum) &&
                           (arg->struct_name).count > 0 && !*Str_eq(ptype_name, &arg->struct_name)) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             ((Str*)Vec_get(&fdef->data.data.FuncDef.param_names, &(U64){(U64)(pi)}))->c_str,
                             ptype_name->c_str, arg->struct_name.c_str);
                    type_error(arg, buf);
                }
                ci++;
            }
        }
        // dyn_call variants: method (2nd arg) must be a string literal
        if (((name->count == 8 && memcmp(name->c_str, "dyn_call", 8) == 0) || (name->count == 12 && memcmp(name->c_str, "dyn_call_ret", 12) == 0) ||
             (name->count == 14 && memcmp(name->c_str, "dyn_has_method", 14) == 0)) &&
            e->children.count >= 3) {
            Expr *method_arg = Expr_child(e, &(I64){(I64)(2)});
            if (method_arg->data.tag != ExprData_TAG_LiteralStr) {
                type_error(method_arg, "dyn_call method argument must be a string literal");
            }
        }
        // array/vec builtins: type_name (1st arg) must be a string literal
        if (((name->count == 5 && memcmp(name->c_str, "array", 5) == 0) || (name->count == 3 && memcmp(name->c_str, "vec", 3) == 0)) &&
            e->children.count >= 2) {
            Expr *type_arg = Expr_child(e, &(I64){(I64)(1)});
            if (type_arg->data.tag != ExprData_TAG_LiteralStr) {
                type_error(type_arg, "array/vec type_name argument must be a string literal");
            }
        }
        // Validate 'own' markers on arguments (variadic-aware)
        if (callee_bind && callee_bind->func_def) {
            Expr *fdef = callee_bind->func_def;
            Vec po_vec = fdef->data.data.FuncDef.param_owns;
            I32 fvi = fdef->data.data.FuncDef.variadic_index;
            I32 fkwi = fdef->data.data.FuncDef.kwargs_index;
            U32 fvc = (fvi >= 0) ? e->variadic_count : 0;
            U32 fkc = (fkwi >= 0) ? e->kwargs_count : 0;
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
                Bool pown = VEC_SET(po_vec) ? (*(Bool*)Vec_get(&po_vec, &(U64){(U64)(pi)})) : 0;
                if (pown && !Expr_child(e, &(I64){(I64)(ci)})->is_own_arg) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "argument for 'own' parameter '%s' must be marked 'own'",
                             ((Str*)Vec_get(&fdef->data.data.FuncDef.param_names, &(U64){(U64)(pi)}))->c_str);
                    type_error(Expr_child(e, &(I64){(I64)(ci)}), buf);
                } else if (!pown && Expr_child(e, &(I64){(I64)(ci)})->is_own_arg) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                             ((Str*)Vec_get(&fdef->data.data.FuncDef.param_names, &(U64){(U64)(pi)}))->c_str);
                    type_error(Expr_child(e, &(I64){(I64)(ci)}), buf);
                }
                if (pown && Expr_child(e, &(I64){(I64)(ci)})->data.tag == ExprData_TAG_Ident) {
                    TypeBinding *ab = tscope_find(scope, &Expr_child(e, &(I64){(I64)(ci)})->data.data.Ident);
                    if (ab && ab->is_ref) type_error(Expr_child(e, &(I64){(I64)(ci)}), "cannot pass ref variable to 'own' parameter; use .clone() to make an owned copy");
                }
                if (pown && Expr_child(e, &(I64){(I64)(ci)})->data.tag == ExprData_TAG_LiteralNull)
                    type_error(Expr_child(e, &(I64){(I64)(ci)}), "cannot pass null to 'own' parameter");
                Vec ps_vec2 = fdef->data.data.FuncDef.param_shallows;
                if (VEC_SET(ps_vec2) && (*(Bool*)Vec_get(&ps_vec2, &(U64){(U64)(pi)})) && Expr_child(e, &(I64){(I64)(ci)})->data.tag == ExprData_TAG_LiteralNull)
                    type_error(Expr_child(e, &(I64){(I64)(ci)}), "cannot pass null to 'shallow' parameter");
                ci++;
            }
        }
        // Resolve return type from scope (covers builtins and user-defined)
        TilType fn_type = tscope_get(scope, name);
        if (fn_type.tag == TilType_TAG_Unknown) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined function '%s'", name->c_str);
            type_error(e, buf);
        }
        // Function pointer call: resolve return type from func_def if available
        // Only for actual func ptr variables (is_proc == -1), not functions returning func ptrs
        if (fn_type.tag == TilType_TAG_FuncPtr && callee_bind && callee_bind->is_proc < 0) {
            Expr_child(e, &(I64){(I64)(0)})->til_type = (TilType){TilType_TAG_FuncPtr}; // mark callee for builder
            // Store signature on FCALL for builder to use
            if (callee_bind && callee_bind->func_def)
                e->fn_sig = callee_bind->func_def;
            if (callee_bind && callee_bind->func_def &&
                (callee_bind->func_def->data.data.FuncDef.return_type).count > 0) {
                TilType rt = type_from_name(&callee_bind->func_def->data.data.FuncDef.return_type, scope);
                e->til_type = rt;
                if ((rt.tag == TilType_TAG_Struct || rt.tag == TilType_TAG_Enum))
                    e->struct_name = callee_bind->func_def->data.data.FuncDef.return_type;
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
                    Expr *arg = Expr_child(e, &(I64){(I64)(ai + 1)});
                    Str *expected_name = ((Str*)Vec_get(&sig->data.data.FuncDef.param_types, &(U64){(U64)(ai)}));
                    if (!expected_name) continue;
                    TilType expected = type_from_name(expected_name, scope);
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
                e->struct_name = callee_bind->func_def->data.data.FuncDef.return_type;
            }
            // Propagate FuncSig for functions returning func ptrs
            if (fn_type.tag == TilType_TAG_FuncPtr && callee_bind && callee_bind->func_def &&
                (callee_bind->func_def->data.data.FuncDef.return_type).count > 0) {
                TypeBinding *rsb = tscope_find(scope, &callee_bind->func_def->data.data.FuncDef.return_type);
                if (rsb && rsb->func_def && rsb->func_def->children.count == 0)
                    e->fn_sig = rsb->func_def;
            }
        }
        // Check: func cannot call proc (panic is exempt; print/println exempt in debug_prints modes)
        // Skip for function pointer calls (callee proc-ness unknown at compile time)
        Bool debug_exempt = current_mode && current_mode->debug_prints &&
            ((name->count == 5 && memcmp(name->c_str, "print", 5) == 0) || (name->count == 7 && memcmp(name->c_str, "println", 7) == 0));
        if (fn_type.tag != TilType_TAG_FuncPtr &&
            in_func && tscope_is_proc(scope, name) == 1 && !(name->count == 5 && memcmp(name->c_str, "panic", 5) == 0) && !debug_exempt) {
            char buf[128];
            snprintf(buf, sizeof(buf), "func cannot call proc '%s'", name->c_str);
            type_error(e, buf);
        }
        // Check: test functions cannot be called by anyone
        if (tscope_is_proc(scope, name) == 2) {
            char buf[128];
            snprintf(buf, sizeof(buf), "test functions cannot be called ('%s')", name->c_str);
            type_error(e, buf);
        }
        done_fcall:
        break;
    }
    case ExprData_TAG_FieldAccess: {
        infer_expr(scope, Expr_child(e, &(I64){(I64)(0)}), in_func);
        Expr *obj = Expr_child(e, &(I64){(I64)(0)});
        if (obj->struct_name.count > 0) {
            Expr *sdef = tscope_get_struct(scope, &obj->struct_name);
            if (sdef) {
                Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
                Str *fname = &e->data.data.Ident;
                Bool found = 0;
                for (U32 i = 0; i < body->children.count; i++) {
                    Expr *field = Expr_child(body, &(I64){(I64)(i)});
                    // Skip variant registry entries (non-namespace) in enum bodies
                    if (sdef->data.tag == ExprData_TAG_EnumDef && !field->data.data.Decl.is_namespace)
                        continue;
                    if (*Str_eq(&field->data.data.Decl.name, fname)) {
                        e->til_type = field->til_type;
                        e->is_ns_field = field->data.data.Decl.is_namespace;
                        e->is_own_field = field->data.data.Decl.is_own || field->data.data.Decl.is_ref;
                        e->is_ref_field = field->data.data.Decl.is_ref;
                        if (field->til_type.tag == TilType_TAG_Struct || field->til_type.tag == TilType_TAG_Enum) {
                            e->struct_name = Expr_child(field, &(I64){(I64)(0)})->struct_name;
                        } else {
                            e->struct_name = obj->struct_name;
                        }
                        // Enum variant access: override type to enum for:
                        // 1. I64 literal variants (simple enums)
                        // 2. Zero-arg ext_func constructors (no-payload in payload enums)
                        if (sdef->data.tag == ExprData_TAG_EnumDef &&
                            field->data.data.Decl.is_namespace &&
                            field->children.count > 0) {
                            Expr *fc = Expr_child(field, &(I64){(I64)(0)});
                            if (fc->data.tag != ExprData_TAG_FuncDef) {
                                // I64 literal variant
                                e->til_type = (TilType){TilType_TAG_Enum};
                                e->struct_name = obj->struct_name;
                            } else if (fc->data.data.FuncDef.func_type.tag == FuncType_TAG_ExtFunc &&
                                       fc->data.data.FuncDef.nparam == 0 &&
                                       (fc->data.data.FuncDef.return_type).count > 0 &&
                                       *Str_eq(&fc->data.data.FuncDef.return_type, &obj->struct_name)) {
                                // Zero-arg ext_func constructor (auto-callable)
                                e->til_type = (TilType){TilType_TAG_Enum};
                                e->struct_name = obj->struct_name;
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
            infer_expr(scope, Expr_child(e, &(I64){(I64)(i)}), in_func);
        e->til_type = (TilType){TilType_TAG_Struct};
        e->struct_name = (Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT};
        break;
    case ExprData_TAG_SetLit:
        for (U32 i = 0; i < e->children.count; i++)
            infer_expr(scope, Expr_child(e, &(I64){(I64)(i)}), in_func);
        e->til_type = (TilType){TilType_TAG_Struct};
        e->struct_name = (Str){.c_str = (U8*)"Set", .count = 3, .cap = CAP_LIT};
        break;
    case ExprData_TAG_NamedArg:
        // Infer the value inside the named arg (child[0])
        if (e->children.count > 0) {
            infer_expr(scope, Expr_child(e, &(I64){(I64)(0)}), in_func);
            Expr *val = Expr_child(e, &(I64){(I64)(0)});
            e->til_type = val->til_type;
            e->struct_name = val->struct_name;
        }
        break;
    default:
        e->til_type = (TilType){TilType_TAG_Unknown};
        break;
    }
}

// --- Collection literal helpers ---

static Bool type_has_cmp(TypeScope *scope, const char *type_name) {
    Expr *sdef = tscope_get_struct(scope, Str_clone(&(Str){.c_str = (U8*)(type_name), .count = (U64)strlen((const char*)(type_name)), .cap = CAP_VIEW}));
    if (!sdef) return 0;
    Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *f = Expr_child(body, &(I64){(I64)(i)});
        if (f->data.tag == ExprData_TAG_Decl && f->data.data.Decl.is_namespace &&
            (f->data.data.Decl.name.count == 3 && memcmp(f->data.data.Decl.name.c_str, "cmp", 3) == 0))
            return 1;
    }
    return 0;
}

// --- Set literal desugaring ---
// Transforms s := {v1, v2, v3} into:
//   mut s := Set.new(elem_type, elem_size)
//   Set.add(s, own v1)
//   Set.add(s, own v2)
//   Set.add(s, own v3)

static void desugar_set_literals(Expr *body, TypeScope *scope) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
        if (stmt->data.tag != ExprData_TAG_Decl || stmt->children.count == 0 ||
            Expr_child(stmt, &(I64){(I64)(0)})->data.tag != ExprData_TAG_SetLit) {
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        changed = 1;
        Expr *set_lit = Expr_child(stmt, &(I64){(I64)(0)});
        U32 line = set_lit->line, col = set_lit->col;
        Str *path = &set_lit->path;
        Str *var_name = &stmt->data.data.Decl.name;

        if (set_lit->children.count == 0) {
            type_error(set_lit, "set literal must have at least one element");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Get element type from first entry
        Expr *first = Expr_child(set_lit, &(I64){(I64)(0)});
        const char *elem_type = type_to_name(first->til_type, &first->struct_name);
        if (!elem_type) {
            type_error(first, "set literal: cannot determine element type");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Validate element type has cmp
        if (!type_has_cmp(scope, elem_type)) {
            char buf[128];
            snprintf(buf, sizeof(buf), "set literal: element type '%s' must implement cmp", elem_type);
            type_error(first, buf);
        }

        // Validate all elements have consistent type
        for (U32 j = 1; j < set_lit->children.count; j++) {
            Expr *v = Expr_child(set_lit, &(I64){(I64)(j)});
            const char *vt = type_to_name(v->til_type, &v->struct_name);
            if (!vt || strcmp(vt, elem_type) != 0)
                type_error(v, "set literal: all elements must be the same type");
        }

        // Build: mut var_name := Set.new(elem_type_str, ElemType.size())
        Expr *new_call = make_ns_call("Set", "new", (TilType){TilType_TAG_Struct},
                                       &(Str){.c_str = (U8*)"Set", .count = 3, .cap = CAP_LIT}, set_lit);
        Expr *et_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        et_str->data.data.LiteralStr = *Str_clone(&(Str){.c_str = (U8*)(elem_type), .count = (U64)strlen((const char*)(elem_type)), .cap = CAP_VIEW});
        et_str->til_type = (TilType){TilType_TAG_Struct};
        et_str->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, et_str);
        Expr *esz = make_ns_call(elem_type, "size", (TilType){TilType_TAG_I64}, NULL, set_lit);
        Expr_add_child(new_call, esz);

        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, stmt->line, stmt->col, path);
        decl->data.data.Decl.name = *var_name;
        decl->data.data.Decl.is_mut = true;
        decl->til_type = (TilType){TilType_TAG_Struct};
        Expr_add_child(decl, new_call);

        tscope_set(scope, var_name, (TilType){TilType_TAG_Struct}, -1, 1, stmt->line, stmt->col, 0, 0);
        TypeBinding *vb = tscope_find(scope, var_name);
        if (vb) vb->struct_name = Str_clone(&(Str){.c_str = (U8*)"Set", .count = 3, .cap = CAP_LIT});

        Vec_push(&new_ch, decl);

        // Build .add calls for each element
        for (U32 j = 0; j < set_lit->children.count; j++) {
            Expr *add_call = make_ns_call("Set", "add", (TilType){TilType_TAG_None}, NULL, set_lit);
            Expr *self_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
            self_id->data.data.Ident = *var_name;
            self_id->til_type = (TilType){TilType_TAG_Struct};
            self_id->struct_name = (Str){.c_str = (U8*)"Set", .count = 3, .cap = CAP_LIT};
            Expr_add_child(add_call, self_id);
            Expr *val = Expr_clone(Expr_child(set_lit, &(I64){(I64)(j)}));
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
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
        // Only handle: name := {k: v, ...}
        if (stmt->data.tag != ExprData_TAG_Decl || stmt->children.count == 0 ||
            Expr_child(stmt, &(I64){(I64)(0)})->data.tag != ExprData_TAG_MapLit) {
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        changed = 1;
        Expr *map_lit = Expr_child(stmt, &(I64){(I64)(0)});
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
        Expr *first_key = Expr_child(map_lit, &(I64){(I64)(0)});
        Expr *first_val = Expr_child(map_lit, &(I64){(I64)(1)});
        const char *key_type = type_to_name(first_key->til_type, &first_key->struct_name);
        const char *val_type = type_to_name(first_val->til_type, &first_val->struct_name);

        if (!key_type) {
            type_error(first_key, "map literal: cannot determine key type");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        if (!val_type) {
            type_error(first_val, "map literal: cannot determine value type");
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Validate key type has cmp
        if (!type_has_cmp(scope, key_type)) {
            char buf[128];
            snprintf(buf, sizeof(buf), "map literal: key type '%s' must implement cmp", key_type);
            type_error(first_key, buf);
        }

        // Validate all entries have consistent types
        for (U32 j = 2; j < map_lit->children.count; j += 2) {
            Expr *k = Expr_child(map_lit, &(I64){(I64)(j)});
            Expr *v = Expr_child(map_lit, &(I64){(I64)(j + 1)});
            const char *kt = type_to_name(k->til_type, &k->struct_name);
            const char *vt = type_to_name(v->til_type, &v->struct_name);
            if (!kt || strcmp(kt, key_type) != 0)
                type_error(k, "map literal: all keys must be the same type");
            if (!vt || strcmp(vt, val_type) != 0)
                type_error(v, "map literal: all values must be the same type");
        }

        // Build: mut var_name := Map.new(key_type_str, KeyType.size(), val_type_str, ValType.size())
        Expr *new_call = make_ns_call("Map", "new", (TilType){TilType_TAG_Struct},
                                       &(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT}, map_lit);
        // Arg 1: key_type string
        Expr *kt_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        kt_str->data.data.LiteralStr = *Str_clone(&(Str){.c_str = (U8*)(key_type), .count = (U64)strlen((const char*)(key_type)), .cap = CAP_VIEW});
        kt_str->til_type = (TilType){TilType_TAG_Struct};
        kt_str->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, kt_str);
        // Arg 2: KeyType.size()
        Expr *ksz = make_ns_call(key_type, "size", (TilType){TilType_TAG_I64}, NULL, map_lit);
        Expr_add_child(new_call, ksz);
        // Arg 3: val_type string
        Expr *vt_str = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        vt_str->data.data.LiteralStr = *Str_clone(&(Str){.c_str = (U8*)(val_type), .count = (U64)strlen((const char*)(val_type)), .cap = CAP_VIEW});
        vt_str->til_type = (TilType){TilType_TAG_Struct};
        vt_str->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, vt_str);
        // Arg 4: ValType.size()
        Expr *vsz = make_ns_call(val_type, "size", (TilType){TilType_TAG_I64}, NULL, map_lit);
        Expr_add_child(new_call, vsz);

        // Build declaration node (mut, so .set can work)
        Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, stmt->line, stmt->col, path);
        decl->data.data.Decl.name = *var_name;
        decl->data.data.Decl.is_mut = true;
        decl->til_type = (TilType){TilType_TAG_Struct};
        Expr_add_child(decl, new_call);

        // Register in scope
        tscope_set(scope, var_name, (TilType){TilType_TAG_Struct}, -1, 1, stmt->line, stmt->col, 0, 0);
        TypeBinding *vb = tscope_find(scope, var_name);
        if (vb) vb->struct_name = Str_clone(&(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT});

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
            Expr *key = Expr_clone(Expr_child(map_lit, &(I64){(I64)(j * 2)}));
            key->is_own_arg = true;
            Expr_add_child(set_call, key);
            // Arg: own val
            Expr *mval = Expr_clone(Expr_child(map_lit, &(I64){(I64)(j * 2 + 1)}));
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

static Expr *find_variadic_fcall(Expr *e) {
    if (!e) return NULL;
    if (e->data.tag == ExprData_TAG_FuncDef || e->data.tag == ExprData_TAG_StructDef ||
        e->data.tag == ExprData_TAG_EnumDef || e->data.tag == ExprData_TAG_Body) return NULL;
    if (e->data.tag == ExprData_TAG_FCall && e->variadic_index >= 0) {
        // Skip array/vec builtins — handled specially like dyn_call
        if (Expr_child(e, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident) {
            Str *cn = &Expr_child(e, &(I64){(I64)(0)})->data.data.Ident;
            if ((cn->count == 5 && memcmp(cn->c_str, "array", 5) == 0) || (cn->count == 3 && memcmp(cn->c_str, "vec", 3) == 0)) return NULL;
        }
        return e;
    }
    for (U32 i = 0; i < e->children.count; i++) {
        Expr *found = find_variadic_fcall(Expr_child(e, &(I64){(I64)(i)}));
        if (found) return found;
    }
    return NULL;
}

// Create a namespace method call: StructName.method(args...)
static Expr *make_ns_call(const char *sname, const char *method,
                           TilType ret_type, Str *ret_sname, Expr *src) {
    I32 line = src->line, col = src->col;
    Str *path = &src->path;
    Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
    call->til_type = ret_type;
    if (ret_sname) call->struct_name = *ret_sname;
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

static I32 _va_counter = 0;

static void desugar_variadic_calls(Expr *body, TypeScope *scope) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
        Expr *fcall = find_variadic_fcall(stmt);
        if (!fcall) {
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        changed = 1;
        I32 vi = fcall->variadic_index;
        U32 vc = fcall->variadic_count;
        I32 line = fcall->line, col = fcall->col;
        Str *path = &fcall->path;

        // Find element type from func_def
        Str *elem_type = NULL;
        Expr *callee = Expr_child(fcall, &(I64){(I64)(0)});
        if (callee->data.tag == ExprData_TAG_Ident) {
            TypeBinding *tb = tscope_find(scope, &callee->data.data.Ident);
            if (tb && tb->func_def) {
                I32 fvi = tb->func_def->data.data.FuncDef.variadic_index;
                if (fvi >= 0)
                    elem_type = ((Str*)Vec_get(&tb->func_def->data.data.FuncDef.param_types, &(U64){(U64)(fvi)}));
            }
        } else if (callee->data.tag == ExprData_TAG_FieldAccess && callee->is_ns_field) {
            Expr *type_node = Expr_child(callee, &(I64){(I64)(0)});
            if (type_node->data.tag == ExprData_TAG_Ident) {
                Expr *sdef = tscope_get_struct(scope, &type_node->data.data.Ident);
                if (sdef) {
                    Expr *sbody = Expr_child(sdef, &(I64){(I64)(0)});
                    for (U32 j = 0; j < sbody->children.count; j++) {
                        Expr *f = Expr_child(sbody, &(I64){(I64)(j)});
                        if (f->data.tag == ExprData_TAG_Decl && f->data.data.Decl.is_namespace &&
                            *Str_eq(&f->data.data.Decl.name, &callee->data.data.Ident) &&
                            Expr_child(f, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FuncDef) {
                            I32 fvi = Expr_child(f, &(I64){(I64)(0)})->data.data.FuncDef.variadic_index;
                            if (fvi >= 0)
                                elem_type = ((Str*)Vec_get(&Expr_child(f, &(I64){(I64)(0)})->data.data.FuncDef.param_types, &(U64){(U64)(fvi)}));
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
        if (vc == 1 && Expr_child(fcall, &(I64){(I64)(vi)})->is_splat) {
            Expr *splat = Expr_child(fcall, &(I64){(I64)(vi)});
            splat->is_splat = false;
            // Clone if ident so caller keeps their copy; otherwise clone borrowed ref
            if (splat->data.tag == ExprData_TAG_Ident) {
                splat = make_clone_call("Array", (TilType){TilType_TAG_Struct}, splat, splat);
            } else {
                splat = Expr_clone(splat);
            }
            splat->is_own_arg = true;
            // Rebuild fcall children replacing variadic slot with splat
            Vec fcall_new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); fcall_new_ch = *_vp; free(_vp); }
            for (U32 j = 0; j < fcall->children.count; j++) {
                if ((I32)j == vi) {
                    Vec_push(&fcall_new_ch, splat);
                } else {
                    Expr *ch = Expr_child(fcall, &(I64){(I64)(j)});
                    Vec_push(&fcall_new_ch, Expr_clone(ch));
                }
            }
            Vec_delete(&fcall->children, &(Bool){0});
            fcall->children = fcall_new_ch;
            fcall->variadic_index = -1;
            fcall->variadic_count = 0;
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }

        // Create temp variable name
        char buf[32];
        snprintf(buf, sizeof(buf), "_va%d", _va_counter++);
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
        Expr *sz = make_ns_call((const char *)elem_type->c_str, "size", (TilType){TilType_TAG_U64},
                                 NULL, fcall);
        Expr_add_child(new_call, sz);
        // Arg: count
        Expr *cap = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralNum}, line, col, path);
        char cap_buf[16];
        snprintf(cap_buf, sizeof(cap_buf), "%d", vc);
        cap->data.data.LiteralNum = *Str_clone(&(Str){.c_str = (U8*)(cap_buf), .count = (U64)strlen((const char*)(cap_buf)), .cap = CAP_VIEW});
        cap->til_type = (TilType){TilType_TAG_U64};
        Expr_add_child(new_call, cap);

        // DECL _va := Array.new(...)
        Expr *va_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        va_decl->data.data.Decl.name = *va_name;
        va_decl->til_type = (TilType){TilType_TAG_Struct};
        Expr_add_child(va_decl, new_call);

        // Register _va in scope
        tscope_set(scope, va_name, (TilType){TilType_TAG_Struct}, -1, 0, line, col, 0, 0);
        TypeBinding *vab = tscope_find(scope, va_name);
        if (vab) vab->struct_name = Str_clone(&(Str){.c_str = (U8*)"Array", .count = 5, .cap = CAP_LIT});

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
            idx->til_type = (TilType){TilType_TAG_U64};
            Expr_add_child(set_call, idx);
            // Arg: val — clone idents and field accesses so Array_set
            // doesn't free the caller's variable or an interior pointer
            Expr *val = Expr_child(fcall, &(I64){(I64)(vi + j)});
            if (val->data.tag == ExprData_TAG_Ident || val->data.tag == ExprData_TAG_FieldAccess) {
                const char *tname = type_to_name(val->til_type, &val->struct_name);
                if (tname)
                    val = make_clone_call(tname, val->til_type, val, val);
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
        Vec fcall_new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); fcall_new_ch = *_vp; free(_vp); }
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
            Expr *ch = Expr_child(fcall, &(I64){(I64)(j)});
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
        fcall->variadic_index = -1;
        fcall->variadic_count = 0;

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

static Expr *find_kwargs_fcall(Expr *e) {
    if (!e) return NULL;
    if (e->data.tag == ExprData_TAG_FuncDef || e->data.tag == ExprData_TAG_StructDef ||
        e->data.tag == ExprData_TAG_EnumDef || e->data.tag == ExprData_TAG_Body) return NULL;
    if (e->data.tag == ExprData_TAG_FCall && e->kwargs_index >= 0) return e;
    for (U32 i = 0; i < e->children.count; i++) {
        Expr *found = find_kwargs_fcall(Expr_child(e, &(I64){(I64)(i)}));
        if (found) return found;
    }
    return NULL;
}

static I32 _kw_counter = 0;

static void desugar_kwargs_calls(Expr *body, TypeScope *scope) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
        Expr *fcall = find_kwargs_fcall(stmt);
        if (!fcall) {
            Vec_push(&new_ch, Expr_clone(stmt));
            continue;
        }
        changed = 1;
        I32 ki = fcall->kwargs_index;
        U32 kc = fcall->kwargs_count;
        I32 line = fcall->line, col = fcall->col;
        Str *path = &fcall->path;

        // Create temp variable name
        char buf[32];
        snprintf(buf, sizeof(buf), "_kw%d", _kw_counter++);
        Str *kw_name = Str_clone(&(Str){.c_str = (U8*)(buf), .count = (U64)strlen((const char*)(buf)), .cap = CAP_VIEW});

        // Find the widest value type among kwargs args for val_size
        const char *val_size_type = "I64"; // default: 8 bytes for primitives
        for (U32 j = 0; j < kc; j++) {
            Expr *na = Expr_child(fcall, &(I64){(I64)(ki + j)});
            Expr *v = Expr_child(na, &(I64){(I64)(0)});
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
        Expr *ksz = make_ns_call("Str", "size", (TilType){TilType_TAG_U64}, NULL, fcall);
        Expr_add_child(new_call, ksz);
        // Arg: val_type = "" (skip dyn_call on values)
        Expr *vt = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralStr}, line, col, path);
        vt->data.data.LiteralStr = (Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT};
        vt->til_type = (TilType){TilType_TAG_Struct};
        vt->struct_name = (Str){.c_str = (U8*)"Str", .count = 3, .cap = CAP_LIT};
        Expr_add_child(new_call, vt);
        // Arg: val_size = widest type's .size()
        Expr *vsz = make_ns_call(val_size_type, "size", (TilType){TilType_TAG_U64}, NULL, fcall);
        Expr_add_child(new_call, vsz);

        // DECL _kw := Map.new(...)
        Expr *kw_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, line, col, path);
        kw_decl->data.data.Decl.name = *kw_name;
        kw_decl->til_type = (TilType){TilType_TAG_Struct};
        Expr_add_child(kw_decl, new_call);

        // Register _kw in scope
        tscope_set(scope, kw_name, (TilType){TilType_TAG_Struct}, -1, 0, line, col, 0, 0);
        TypeBinding *kwb = tscope_find(scope, kw_name);
        if (kwb) kwb->struct_name = Str_clone(&(Str){.c_str = (U8*)"Map", .count = 3, .cap = CAP_LIT});

        Vec_push(&new_ch, kw_decl);

        // 2. Map.set calls for each kwargs arg
        for (U32 j = 0; j < kc; j++) {
            Expr *named_arg = Expr_child(fcall, &(I64){(I64)(ki + j)});
            // named_arg is ExprData_TAG_NamedArg with str_val = key name, child[0] = value
            Str *key_name = &named_arg->data.data.NamedArg;
            Expr *val = Expr_child(named_arg, &(I64){(I64)(0)});

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
                const char *tname = type_to_name(val->til_type, &val->struct_name);
                if (tname)
                    val = make_clone_call(tname, val->til_type, val, val);
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
        Vec fcall_new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); fcall_new_ch = *_vp; free(_vp); }
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
            Expr *ch = Expr_child(fcall, &(I64){(I64)(j)});
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
        fcall->kwargs_index = -1;
        fcall->kwargs_count = 0;

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

static Bool expr_contains_fcall(Expr *e) {
    if (e->data.tag == ExprData_TAG_FCall) return 1;
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_contains_fcall(Expr_child(e, &(I64){(I64)(i)}))) return 1;
    }
    return 0;
}

// Check if a function call returns ref
static I32 fcall_returns_ref(Expr *fcall, TypeScope *scope) {
    if (fcall->data.tag != ExprData_TAG_FCall) return 0;
    Expr *callee = Expr_child(fcall, &(I64){(I64)(0)});
    if (callee->data.tag == ExprData_TAG_Ident) {
        TypeBinding *cb = tscope_find(scope, &callee->data.data.Ident);
        return (cb && cb->func_def) ? cb->func_def->data.data.FuncDef.return_is_ref : 0;
    }
    if (callee->data.tag == ExprData_TAG_FieldAccess && callee->is_ns_field) {
        Expr *sdef = tscope_get_struct(scope, &Expr_child(callee, &(I64){(I64)(0)})->data.data.Ident);
        if (!sdef) return 0;
        Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *f = Expr_child(body, &(I64){(I64)(j)});
            if (f->data.tag == ExprData_TAG_Decl && f->data.data.Decl.is_namespace &&
                *Str_eq(&f->data.data.Decl.name, &callee->data.data.Ident) &&
                Expr_child(f, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FuncDef)
                return Expr_child(f, &(I64){(I64)(0)})->data.data.FuncDef.return_is_ref;
        }
    }
    return 0;
}

static I32 hoist_counter = 0;

// Create a temp decl for an expression, register in scope, return the replacement ident.
// Adds the decl to the hoisted list.
static Expr *hoist_to_temp(Expr *val, Expr ***hoisted, U32 *nhoisted, U32 *cap, TypeScope *scope) {
    char name_buf[32];
    snprintf(name_buf, sizeof(name_buf), "_t%d", hoist_counter++);
    Str *tname = Str_clone(&(Str){.c_str = (U8*)(name_buf), .count = (U64)strlen((const char*)(name_buf)), .cap = CAP_VIEW});
    Expr *decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, val->line, val->col, &val->path);
    decl->data.data.Decl.name = *tname;
    decl->data.data.Decl.explicit_type = (Str){0};
    decl->data.data.Decl.is_mut = false;
    decl->data.data.Decl.is_namespace = false;
    decl->til_type = val->til_type;
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
    ident->struct_name = val_struct_name;
    ident->is_own_arg = val_is_own_arg;
    tscope_set(scope, tname, val_type, -1, 0, val_line, val_col, 0, 0);
    TypeBinding *tb = tscope_find(scope, tname);
    if (tb) tb->struct_name = Str_clone(&val_struct_name);
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
        hoist_expr(Expr_child(e, &(I64){(I64)(i)}), hoisted, nhoisted, cap, scope);
    }
    if (e->data.tag != ExprData_TAG_FCall) return;

    // For struct constructors, find field info to skip hoisting inline compound args
    Expr *ctor_body = NULL;
    if ((e->struct_name).count > 0 && e->children.count > 0 &&
        *Str_eq(&Expr_child(e, &(I64){(I64)(0)})->data.data.Ident, &e->struct_name)) {
        Expr *sdef = tscope_get_struct(scope, &e->struct_name);
        if (sdef) ctor_body = Expr_child(sdef, &(I64){(I64)(0)});
    }

    // Check each argument (children[1..n])
    // dyn_call variants: don't hoist the method arg (2nd) — codegen needs it as a literal
    Bool is_dyn_call = 0;
    if (Expr_child(e, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident) {
        Str *cn = &Expr_child(e, &(I64){(I64)(0)})->data.data.Ident;
        is_dyn_call = (cn->count == 8 && memcmp(cn->c_str, "dyn_call", 8) == 0) || (cn->count == 12 && memcmp(cn->c_str, "dyn_call_ret", 12) == 0) ||
                      (cn->count == 14 && memcmp(cn->c_str, "dyn_has_method", 14) == 0);
    }
    Bool is_array_vec = 0;
    if (Expr_child(e, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident) {
        Str *cn = &Expr_child(e, &(I64){(I64)(0)})->data.data.Ident;
        is_array_vec = (cn->count == 5 && memcmp(cn->c_str, "array", 5) == 0) || (cn->count == 3 && memcmp(cn->c_str, "vec", 3) == 0);
    }
    U32 fi = 0; // instance field index for struct constructors
    for (U32 i = 1; i < e->children.count; i++) {
        if (is_dyn_call && (i == 2 || i == 3)) continue; // keep method and arity as literals
        if (is_array_vec && i == 1) continue; // keep type_name as ExprData_TAG_LiteralStr
        if (Expr_child(e, &(I64){(I64)(i)})->data.tag != ExprData_TAG_FCall &&
            Expr_child(e, &(I64){(I64)(i)})->data.tag != ExprData_TAG_LiteralNum &&
            Expr_child(e, &(I64){(I64)(i)})->data.tag != ExprData_TAG_LiteralStr &&
            Expr_child(e, &(I64){(I64)(i)})->data.tag != ExprData_TAG_LiteralBool) continue;

        // Skip hoisting inline compound field args in struct constructors
        if (ctor_body) {
            // Find the fi-th instance field
            Bool is_own = 0;
            TilType ft = (TilType){TilType_TAG_None};
            for (; fi < ctor_body->children.count; fi++) {
                Expr *field = Expr_child(ctor_body, &(I64){(I64)(fi)});
                if (!field->data.data.Decl.is_namespace) {
                    is_own = field->data.data.Decl.is_own;
                    ft = Expr_child(field, &(I64){(I64)(0)})->til_type;
                    fi++;
                    break;
                }
            }
            if (!is_own && (ft.tag == TilType_TAG_Struct || ft.tag == TilType_TAG_Enum))
                continue; // don't hoist — builder handles directly
        }

        *(Expr*)Vec_get(&e->children, &(U64){(U64)(i)}) = *hoist_to_temp(Expr_clone(Expr_child(e, &(I64){(I64)(i)})), hoisted, nhoisted, cap, scope);
    }
}

static void hoist_fcall_args(Expr *body, TypeScope *scope) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
        // Collect hoisted decls from this statement
        Expr **hoisted = NULL;
        U32 nhoisted = 0, hcap = 0;
        // Walk the appropriate expression tree based on statement type
        switch (stmt->data.tag) {
        case ExprData_TAG_Decl:
            hoist_expr(Expr_child(stmt, &(I64){(I64)(0)}), &hoisted, &nhoisted, &hcap, scope);
            break;
        case ExprData_TAG_FCall:
            hoist_expr(stmt, &hoisted, &nhoisted, &hcap, scope);
            if (stmt->til_type.tag != TilType_TAG_None) {
                hoist_to_temp(stmt, &hoisted, &nhoisted, &hcap, scope);
                stmt = hoisted[--nhoisted];
                *(Expr*)Vec_get(&body->children, &(U64){(U64)(i)}) = *stmt;
            }
            break;
        case ExprData_TAG_Return:
            if (stmt->children.count > 0) {
                hoist_expr(Expr_child(stmt, &(I64){(I64)(0)}), &hoisted, &nhoisted, &hcap, scope);
                if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FCall ||
                    Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_LiteralNum ||
                    Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_LiteralStr ||
                    Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_LiteralBool) {
                    *(Expr*)Vec_get(&stmt->children, &(U64){(U64)(0)}) = *hoist_to_temp(Expr_clone(Expr_child(stmt, &(I64){(I64)(0)})), &hoisted, &nhoisted, &hcap, scope);
                }
            }
            break;
        case ExprData_TAG_Assign: {
            hoist_expr(Expr_child(stmt, &(I64){(I64)(0)}), &hoisted, &nhoisted, &hcap, scope);
            // Skip top-level hoisting for compound-type locals — builder
            // uses pointer-assign (typer inserts delete before reassignment).
            // Keep hoisting for scalars (deref-assign) and params (write-through).
            Bool do_hoist = 1;
            TypeBinding *ab = tscope_find(scope, &stmt->data.data.Ident);
            if (ab && !ab->is_param) {
                TilType t = ab->type;
                if (t.tag == TilType_TAG_Struct || t.tag == TilType_TAG_Enum)
                    do_hoist = 0;
            }
            if (do_hoist && (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FCall ||
                Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_LiteralNum ||
                Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_LiteralStr ||
                Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_LiteralBool)) {
                *(Expr*)Vec_get(&stmt->children, &(U64){(U64)(0)}) = *hoist_to_temp(Expr_clone(Expr_child(stmt, &(I64){(I64)(0)})), &hoisted, &nhoisted, &hcap, scope);
            }
            // For mut struct/enum params, replace assignment with swap so
            // ASAP delete of the temp frees the OLD value, not the new one.
            // Re-query: hoist_to_temp may have realloc'd the Map, invalidating ab.
            ab = tscope_find(scope, &stmt->data.data.Ident);
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
                if (ab->struct_name) a->struct_name = *ab->struct_name;
                Expr_add_child(call, a);
                // arg1: the RHS (hoisted temp ident)
                Expr_add_child(call, Expr_clone(Expr_child(stmt, &(I64){(I64)(0)})));
                // arg2: Type.size() — hoist to temp so builder emits deref correctly
                const char *tname = type_to_name(ab->type, ab->struct_name);
                Expr *sz_call = make_ns_call(tname, "size", (TilType){TilType_TAG_U64}, NULL, stmt);
                Expr *sz = hoist_to_temp(sz_call, &hoisted, &nhoisted, &hcap, scope);
                Expr_add_child(call, sz);
                // Replace stmt in-place
                *stmt = *call;
            }
            break;
        }
        case ExprData_TAG_FieldAssign: {
            hoist_expr(Expr_child(stmt, &(I64){(I64)(1)}), &hoisted, &nhoisted, &hcap, scope);
            // Skip hoisting for inline compound fields (same as constructor args)
            Bool fa_hoist = 1;
            if (!stmt->is_own_field) {
                TilType ft = Expr_child(stmt, &(I64){(I64)(1)})->til_type;
                if (ft.tag == TilType_TAG_Struct || ft.tag == TilType_TAG_Enum)
                    fa_hoist = 0;
            }
            if (fa_hoist && (Expr_child(stmt, &(I64){(I64)(1)})->data.tag == ExprData_TAG_FCall ||
                Expr_child(stmt, &(I64){(I64)(1)})->data.tag == ExprData_TAG_LiteralNum ||
                Expr_child(stmt, &(I64){(I64)(1)})->data.tag == ExprData_TAG_LiteralStr ||
                Expr_child(stmt, &(I64){(I64)(1)})->data.tag == ExprData_TAG_LiteralBool)) {
                *(Expr*)Vec_get(&stmt->children, &(U64){(U64)(1)}) = *hoist_to_temp(Expr_clone(Expr_child(stmt, &(I64){(I64)(1)})), &hoisted, &nhoisted, &hcap, scope);
            }
            break;
        }
        case ExprData_TAG_If:
            hoist_expr(Expr_child(stmt, &(I64){(I64)(0)}), &hoisted, &nhoisted, &hcap, scope);
            if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FCall) {
                *(Expr*)Vec_get(&stmt->children, &(U64){(U64)(0)}) = *hoist_to_temp(Expr_clone(Expr_child(stmt, &(I64){(I64)(0)})), &hoisted, &nhoisted, &hcap, scope);
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

static const char *type_to_name(TilType type, Str *struct_name) {
    if (struct_name && struct_name->count > 0) return (const char *)struct_name->c_str;
    switch (type.tag) {
        case TilType_TAG_I64:  return "I64";
        case TilType_TAG_U8:   return "U8";
        case TilType_TAG_I16:  return "I16";
        case TilType_TAG_I32:  return "I32";
        case TilType_TAG_U32:  return "U32";
        case TilType_TAG_U64:  return "U64";
        case TilType_TAG_F32:  return "F32";
        case TilType_TAG_Bool: return "Bool";
        default: return NULL;
    }
}

static Expr *make_delete_call(Str *var_name, TilType type, Str *struct_name, Expr *src) {
    const char *tname = type_to_name(type, struct_name);
    if (!tname) return NULL;
    I32 line = src->line, col = src->col;
    Str *path = &src->path;

    Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
    call->til_type = (TilType){TilType_TAG_None};

    Expr *type_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
    type_id->data.data.Ident = *Str_clone(&(Str){.c_str = (U8*)tname, .count = (U64)strlen(tname), .cap = CAP_VIEW});
    type_id->struct_name = *Str_clone(&(Str){.c_str = (U8*)tname, .count = (U64)strlen(tname), .cap = CAP_VIEW});

    Expr *fa = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
    fa->data.data.FieldAccess = (Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT};
    fa->is_ns_field = true;
    Expr_add_child(fa, type_id);
    Expr_add_child(call, fa);

    Expr *arg = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
    arg->data.data.Ident = *var_name;
    arg->til_type = type;
    if (struct_name) arg->struct_name = *struct_name;
    arg->is_own_arg = true;
    Expr_add_child(call, arg);

    // call_free=true (ASAP delete should free the top-level allocation)
    Expr *true_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
    true_lit->data.data.LiteralBool = (Str){.c_str = (U8*)"true", .count = 4, .cap = CAP_LIT};
    true_lit->til_type = (TilType){TilType_TAG_Bool};
    Expr_add_child(call, true_lit);

    return call;
}

// Build Type.delete(obj.field, call_free) for field reassignment.
// is_own: true for own (pointer) fields, false for inline (value) fields.
static Expr *make_field_delete(Expr *field_assign, Bool is_own) {
    Expr *rhs = Expr_child(field_assign, &(I64){(I64)(1)});
    const char *tname = type_to_name(rhs->til_type, &rhs->struct_name);
    if (!tname) return NULL;
    I32 line = field_assign->line, col = field_assign->col;
    Str *path = &field_assign->path;

    Expr *call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, line, col, path);
    call->til_type = (TilType){TilType_TAG_None};

    Expr *type_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, line, col, path);
    type_id->data.data.Ident = *Str_clone(&(Str){.c_str = (U8*)(tname), .count = (U64)strlen((const char*)(tname)), .cap = CAP_VIEW});
    type_id->struct_name = *Str_clone(&(Str){.c_str = (U8*)(tname), .count = (U64)strlen((const char*)(tname)), .cap = CAP_VIEW});

    Expr *fa = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
    fa->data.data.FieldAccess = (Str){.c_str = (U8*)"delete", .count = 6, .cap = CAP_LIT};
    fa->is_ns_field = true;
    Expr_add_child(fa, type_id);
    Expr_add_child(call, fa);

    // arg: obj.field_name (clone the obj expr, build field access)
    Expr *field_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
    field_acc->data.data.FieldAccess = field_assign->data.data.FieldAssign;
    field_acc->is_own_field = is_own;
    field_acc->til_type = rhs->til_type;
    field_acc->struct_name = rhs->struct_name;
    Expr_add_child(field_acc, Expr_clone(Expr_child(field_assign, &(I64){(I64)(0)})));
    Expr_add_child(call, field_acc);

    Expr *cf_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
    cf_lit->data.data.LiteralBool = (is_own ? (Str){.c_str = (U8*)"true", .count = 4, .cap = CAP_LIT} : (Str){.c_str = (U8*)"false", .count = 5, .cap = CAP_LIT});
    cf_lit->til_type = (TilType){TilType_TAG_Bool};
    Expr_add_child(call, cf_lit);

    return call;
}

// Insert delete calls before field reassignments (own and inline compound)
static void insert_field_deletes(Expr *body) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
        if (stmt->data.tag == ExprData_TAG_FieldAssign) {
            Bool need_delete = 0;
            Bool is_own = stmt->is_own_field;
            if (stmt->is_ref_field) {
                // ref fields don't own their data — no delete on reassignment
                need_delete = 0;
            } else if (is_own) {
                need_delete = 1;
            } else {
                TilType ft = Expr_child(stmt, &(I64){(I64)(1)})->til_type;
                if (ft.tag == TilType_TAG_Struct || ft.tag == TilType_TAG_Enum)
                    need_delete = 1;
            }
            if (need_delete) {
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

static Bool expr_uses_var(Expr *e, Str *name) {
    if (e->data.tag == ExprData_TAG_FuncDef) return 0;
    if (e->data.tag == ExprData_TAG_Ident && *Str_eq(&e->data.data.Ident, name)) return 1;
    if (e->data.tag == ExprData_TAG_Assign && *Str_eq(&e->data.data.Ident, name)) return 1;
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_uses_var(Expr_child(e, &(I64){(I64)(i)}), name)) return 1;
    }
    return 0;
}

// Check if name is referenced inside any nested func/proc body in this subtree,
// excluding cases where the name is shadowed by a parameter of that function.
static Bool expr_used_in_nested_func(Expr *e, Str *name) {
    if (e->data.tag == ExprData_TAG_FuncDef) {
        // Check if name is shadowed by a parameter
        for (U32 i = 0; i < e->data.data.FuncDef.nparam; i++) {
            if (*Str_eq(((Str*)Vec_get(&e->data.data.FuncDef.param_names, &(U64){(U64)(i)})), name)) return 0;
        }
        // Not a param — recurse into body to find uses
        if (e->children.count > 0) return expr_uses_var(Expr_child(e, &(I64){(I64)(0)}), name);
        return 0;
    }
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_used_in_nested_func(Expr_child(e, &(I64){(I64)(i)}), name)) return 1;
    }
    return 0;
}

static Bool expr_contains_decl(Expr *e, Str *name) {
    if (e->data.tag == ExprData_TAG_FuncDef) return 0;
    if (e->data.tag == ExprData_TAG_Decl && *Str_eq(&e->data.data.Decl.name, name)) return 1;
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_contains_decl(Expr_child(e, &(I64){(I64)(i)}), name)) return 1;
    }
    return 0;
}

// Helper: given a func_def, check if var_name is passed to an own param
static Bool check_own_args(Expr *fdef, Expr *fcall, Str *var_name) {
    Vec po3 = fdef->data.data.FuncDef.param_owns;
    if (!VEC_SET(po3)) return 0;
    U32 np = fdef->data.data.FuncDef.nparam;
    for (U32 i = 0; i < np && i + 1 < fcall->children.count; i++) {
        if ((*(Bool*)Vec_get(&po3, &(U64){(U64)(i)})) && Expr_child(fcall, &(I64){(I64)(i + 1)})->data.tag == ExprData_TAG_Ident &&
            *Str_eq(&Expr_child(fcall, &(I64){(I64)(i + 1)})->data.data.Ident, var_name)) {
            return 1;
        }
    }
    return 0;
}

static Bool fcall_has_own_arg(Expr *fcall, Str *var_name, TypeScope *scope) {
    if (fcall->data.tag != ExprData_TAG_FCall || fcall->children.count < 2) return 0;
    // Struct constructor: check if var is in an own field position
    if ((fcall->struct_name).count > 0 && Expr_child(fcall, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident &&
        *Str_eq(&Expr_child(fcall, &(I64){(I64)(0)})->data.data.Ident, &fcall->struct_name)) {
        Expr *sdef = tscope_get_struct(scope, &fcall->struct_name);
        if (sdef) {
            Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
            U32 fi = 0;
            for (U32 i = 0; i < body->children.count; i++) {
                if (Expr_child(body, &(I64){(I64)(i)})->data.tag != ExprData_TAG_Decl ||
                    Expr_child(body, &(I64){(I64)(i)})->data.data.Decl.is_namespace) continue;
                U32 arg_idx = fi + 1;
                fi++;
                if (arg_idx < fcall->children.count &&
                    Expr_child(fcall, &(I64){(I64)(arg_idx)})->data.tag == ExprData_TAG_Ident &&
                    *Str_eq(&Expr_child(fcall, &(I64){(I64)(arg_idx)})->data.data.Ident, var_name) &&
                    Expr_child(body, &(I64){(I64)(i)})->data.data.Decl.is_own) {
                    return 1;
                }
            }
        }
    }
    // Direct call: look up func def in scope
    if (Expr_child(fcall, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident) {
        Str *fn_name = &Expr_child(fcall, &(I64){(I64)(0)})->data.data.Ident;
        TypeBinding *fb = tscope_find(scope, fn_name);
        if (!fb || !fb->func_def) return 0;
        return check_own_args(fb->func_def, fcall, var_name);
    }
    // Namespace method call: look up in struct definition
    if (Expr_child(fcall, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FieldAccess && Expr_child(fcall, &(I64){(I64)(0)})->is_ns_field) {
        Str *method = &Expr_child(fcall, &(I64){(I64)(0)})->data.data.Ident;
        Expr *type_node = Expr_child(Expr_child(fcall, &(I64){(I64)(0)}), &(I64){0});
        if (type_node->data.tag != ExprData_TAG_Ident) return 0;
        Expr *sdef = tscope_get_struct(scope, &type_node->data.data.Ident);
        if (!sdef) return 0;
        Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *field = Expr_child(body, &(I64){(I64)(i)});
            if (field->data.tag == ExprData_TAG_Decl && field->data.data.Decl.is_namespace &&
                *Str_eq(&field->data.data.Decl.name, method) &&
                Expr_child(field, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FuncDef) {
                return check_own_args(Expr_child(field, &(I64){(I64)(0)}), fcall, var_name);
            }
        }
    }
    return 0;
}

static Bool expr_transfers_own(Expr *e, Str *var_name, TypeScope *scope) {
    if (e->data.tag == ExprData_TAG_FuncDef) return 0;
    if (fcall_has_own_arg(e, var_name, scope)) return 1;
    // Own field assignment: RHS ownership transfers to the field
    if (e->data.tag == ExprData_TAG_FieldAssign && e->is_own_field &&
        Expr_child(e, &(I64){(I64)(1)})->data.tag == ExprData_TAG_Ident &&
        *Str_eq(&Expr_child(e, &(I64){(I64)(1)})->data.data.Ident, var_name)) {
        return 1;
    }
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_transfers_own(Expr_child(e, &(I64){(I64)(i)}), var_name, scope)) return 1;
    }
    return 0;
}

typedef struct {
    Str *name;
    TilType type;
    Str *struct_name;
    I32 decl_index;
    I32 last_use;
    I32 own_transfer;  // index of stmt that transfers ownership, -1 if none
    Bool skip_delete;  // don't ASAP-delete (globals, captured vars)
} LocalInfo;

// Check if any alias (ref decl sourced from 'name') is used in expr
static Bool alias_used_in_expr(Expr *body, Str *name, Expr *expr) {
    for (U32 k = 0; k < body->children.count; k++) {
        Expr *d = Expr_child(body, &(I64){(I64)(k)});
        if (d->data.tag == ExprData_TAG_Decl && d->data.data.Decl.is_ref &&
            Expr_child(d, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident &&
            *Str_eq(&Expr_child(d, &(I64){(I64)(0)})->data.data.Ident, name)) {
            if (expr_uses_var(expr, &d->data.data.Decl.name))
                return 1;
        }
    }
    return 0;
}

// Insert deletes for live parent-scope locals before early exits in body.
// return_only=1: only before ExprData_TAG_Return (used when propagating into while bodies,
// since break/continue don't leave the parent scope).
static void insert_exit_deletes(Expr *body, LocalInfo *live, U32 n_live, Bool return_only) {
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
        if (stmt->data.tag == ExprData_TAG_If) {
            for (U32 c = 1; c < stmt->children.count; c++)
                insert_exit_deletes(Expr_child(stmt, &(I64){(I64)(c)}), live, n_live, return_only);
        }
        if (stmt->data.tag == ExprData_TAG_While) {
            insert_exit_deletes(Expr_child(stmt, &(I64){(I64)(1)}), live, n_live, 1);
        }
        if (stmt->data.tag == ExprData_TAG_Return ||
            (!return_only && (stmt->data.tag == ExprData_TAG_Break || stmt->data.tag == ExprData_TAG_Continue))) {
            for (U32 j = 0; j < n_live; j++) {
                if (stmt->children.count > 0 &&
                    (expr_uses_var(Expr_child(stmt, &(I64){(I64)(0)}), live[j].name) ||
                     alias_used_in_expr(body, live[j].name, Expr_child(stmt, &(I64){(I64)(0)})))) continue;
                Expr *del = make_delete_call(
                    live[j].name, live[j].type, live[j].struct_name, stmt);
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
    Vec locals_vec; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(LocalInfo)}); locals_vec = *_vp; free(_vp); }
    for (U32 i = 0; i < scope->bindings.count; i++) {
        TypeBinding *b = (TypeBinding *)(scope->bindings.val_data + i * scope->bindings.val_size);
        if ((b->is_param && !b->is_own) || b->struct_def || b->func_def) continue;

        // Find decl_index: direct child first, then nested
        I32 decl_idx = -1;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *s = Expr_child(body, &(I64){(I64)(j)});
            if (s->data.tag == ExprData_TAG_Decl && *Str_eq(&s->data.data.Decl.name, b->name)) {
                decl_idx = j;
                break;
            }
        }
        if (decl_idx == -1) {
            for (U32 j = 0; j < body->children.count; j++) {
                if (expr_contains_decl(Expr_child(body, &(I64){(I64)(j)}), b->name)) {
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
            if (expr_uses_var(Expr_child(body, &(I64){(I64)(j)}), b->name)) {
                last_use = j;
            }
            if (own_transfer == -1 && expr_transfers_own(Expr_child(body, &(I64){(I64)(j)}), b->name, scope)) {
                own_transfer = j;
            }
        }

        // Program-scope globals live for the program's lifetime — no ASAP deletion.
        // Still collect them for ownership-transfer checks, but mark for skip.
        Bool skip_delete = is_program_scope && decl_idx >= 0;

        if (!skip_delete) {
            // If captured by a nested func/proc, don't ASAP-delete — the nested
            // function may be called after this scope's body finishes (e.g. cli mode main)
            for (U32 j = scan_from; j < body->children.count; j++) {
                if (expr_used_in_nested_func(Expr_child(body, &(I64){(I64)(j)}), b->name)) {
                    skip_delete = 1;
                    break;
                }
            }
        }
        // Ref bindings don't own their data — never delete, but track for lifetime extension
        if (b->is_ref) skip_delete = 1;

        LocalInfo li = {b->name, b->type, b->struct_name, decl_idx, last_use, own_transfer, skip_delete};
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
            Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
            if (stmt->data.tag != ExprData_TAG_Decl || !stmt->data.data.Decl.is_ref) continue;
            Expr *rhs = Expr_child(stmt, &(I64){(I64)(0)});

            // Compute ref_last: max of AST uses and extended last_use in locals
            I32 ref_last = -1;
            for (U32 j = i + 1; j < body->children.count; j++) {
                if (expr_uses_var(Expr_child(body, &(I64){(I64)(j)}), &stmt->data.data.Decl.name))
                    ref_last = j;
            }
            if (ref_last == -1) ref_last = i;
            for (U32 j = 0; j < n_locals; j++) {
                if (*Str_eq(locals[j].name, &stmt->data.data.Decl.name) && locals[j].last_use > ref_last)
                    ref_last = locals[j].last_use;
            }

            if (rhs->data.tag == ExprData_TAG_Ident) {
                // Direct alias: source must outlive alias
                Str *src_name = &rhs->data.data.Ident;
                for (U32 j = 0; j < n_locals; j++) {
                    if (*Str_eq(locals[j].name, src_name) && locals[j].last_use < ref_last) {
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
                Expr *arg = Expr_child(rhs, &(I64){(I64)(a)});
                while (arg->data.tag == ExprData_TAG_FieldAccess && arg->children.count > 0)
                    arg = Expr_child(arg, &(I64){(I64)(0)});
                if (arg->data.tag != ExprData_TAG_Ident) continue;
                Str *aname = &arg->data.data.Ident;
                for (U32 j = 0; j < n_locals; j++) {
                    if (*Str_eq(locals[j].name, aname) && locals[j].last_use < ref_last) {
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
            Expr *stmt = Expr_child(body, &(I64){(I64)(locals[j].last_use)});
            char buf[128];
            snprintf(buf, sizeof(buf), "use of '%s' after ownership transfer", locals[j].name->c_str);
            type_error(stmt, buf);
            Expr *xfer = Expr_child(body, &(I64){(I64)(locals[j].own_transfer)});
            fprintf(stderr, "%s:%u:%u: note: ownership transferred here\n",
                    xfer->path.c_str, xfer->line, xfer->col);
            fprintf(stderr, "  help: pass a clone instead: own %s.clone()\n",
                    locals[j].name->c_str);
        }
    }

    // Phase 2: rebuild body with ASAP frees
    Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});

        // Before ExprData_TAG_Return/ExprData_TAG_Break/ExprData_TAG_Continue: free locals not yet freed
        if (stmt->data.tag == ExprData_TAG_Return || stmt->data.tag == ExprData_TAG_Break || stmt->data.tag == ExprData_TAG_Continue) {
            for (U32 j = 0; j < n_locals; j++) {
                if (stmt->children.count > 0 &&
                    (expr_uses_var(Expr_child(stmt, &(I64){(I64)(0)}), locals[j].name) ||
                     alias_used_in_expr(body, locals[j].name, Expr_child(stmt, &(I64){(I64)(0)})))) continue;
                if (locals[j].skip_delete) continue;
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].decl_index < (I32)i &&
                    (locals[j].last_use >= (I32)i || locals[j].last_use == -1)) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt);
                    if (del) Vec_push(&new_ch, del);
                }
            }
        }

        // For ExprData_TAG_If/ExprData_TAG_While: insert frees before nested early exits
        if (stmt->data.tag == ExprData_TAG_If || stmt->data.tag == ExprData_TAG_While) {
            Vec live_vec; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(LocalInfo)}); live_vec = *_vp; free(_vp); }
            for (U32 j = 0; j < n_locals; j++) {
                if (locals[j].skip_delete) continue;
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
                        insert_exit_deletes(Expr_child(stmt, &(I64){(I64)(c)}), live, n_live, 0);
                } else {
                    // While: only free before return (break/continue stay in parent scope)
                    insert_exit_deletes(Expr_child(stmt, &(I64){(I64)(1)}), live, n_live, 1);
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
                if (!*Str_eq(locals[j].name, vname)) continue;
                if (locals[j].skip_delete) break;
                TilType t = locals[j].type;
                if (t.tag == TilType_TAG_Struct || t.tag == TilType_TAG_Enum) {
                    Expr *rhs = Expr_child(stmt, &(I64){(I64)(0)});
                    if (expr_uses_var(rhs, vname)) {
                        // RHS reads this var — can't delete before assignment.
                        // Flag so builder emits save-old-delete pattern.
                        stmt->save_old_delete = true;
                        if (locals[j].struct_name) stmt->struct_name = *locals[j].struct_name;
                    } else {
                        Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt);
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
                if (locals[j].skip_delete) continue;
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].last_use == (I32)i) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt);
                    if (del) Vec_push(&new_ch, del);
                }
                // Never used after declaration: free immediately
                if (locals[j].last_use == -1 && locals[j].decl_index == (I32)i) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt);
                    if (del) Vec_push(&new_ch, del);
                }
            }
        }
    }

    Vec_delete(&body->children, &(Bool){0});
    body->children = new_ch;
    free(locals);
}

static void infer_body(TypeScope *scope, Expr *body, I32 in_func, I32 owns_scope, I32 in_loop, I32 returns_ref) {
    body->til_type = (TilType){TilType_TAG_None};
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = Expr_child(body, &(I64){(I64)(i)});
        switch (stmt->data.tag) {
        case ExprData_TAG_Decl:
            // Skip variant registry entries (payload enum: no children)
            if (stmt->children.count == 0) break;
            infer_expr(scope, Expr_child(stmt, &(I64){(I64)(0)}), in_func);
            // For struct/enum defs, register type in scope
            if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_StructDef ||
                Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_EnumDef) {
                Bool is_enum = (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_EnumDef);
                // Check explicit type annotation if present
                if (stmt->data.data.Decl.explicit_type.count > 0) {
                    TilType declared = type_from_name(&stmt->data.data.Decl.explicit_type, scope);
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
                TypeBinding *existing = tscope_find(scope, sname);
                if (existing && existing->struct_def && existing->struct_def != Expr_child(stmt, &(I64){(I64)(0)})) {
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
                tscope_set(scope, sname, builtin_type, -1, 0, stmt->line, stmt->col, 0, 0);
                // Store struct def pointer and builtin flag in the binding
                TypeBinding *b = tscope_find(scope, sname);
                b->struct_def = Expr_child(stmt, &(I64){(I64)(0)});
                b->is_builtin = is_builtin;
                b->is_ext = Expr_child(stmt, &(I64){(I64)(0)})->is_ext;
                break;
            }
            // For func/proc defs, store return type and func/proc-ness in scope
            if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FuncDef) {
                // Check explicit type annotation if present
                if (stmt->data.data.Decl.explicit_type.count > 0) {
                    if (!(stmt->data.data.Decl.explicit_type.count == 11 && memcmp(stmt->data.data.Decl.explicit_type.c_str, "FunctionDef", 11) == 0)) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is FunctionDef",
                                 stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.explicit_type.c_str);
                        type_error(stmt, buf);
                    }
                }
                FuncType ft = Expr_child(stmt, &(I64){(I64)(0)})->data.data.FuncDef.func_type;
                I32 callee_is_proc = (ft.tag == FuncType_TAG_Test) ? 2 : (ft.tag == FuncType_TAG_Proc || ft.tag == FuncType_TAG_ExtProc) ? 1 : 0;
                TilType rt = (TilType){TilType_TAG_None};
                if ((Expr_child(stmt, &(I64){(I64)(0)})->data.data.FuncDef.return_type.count > 0)) {
                    rt = type_from_name(&Expr_child(stmt, &(I64){(I64)(0)})->data.data.FuncDef.return_type, scope);
                }
                stmt->til_type = rt;
                tscope_set(scope, &stmt->data.data.Decl.name, rt, callee_is_proc, 0, stmt->line, stmt->col, 0, 0);
                // Store func_def pointer and builtin flag
                TypeBinding *fb = tscope_find(scope, &stmt->data.data.Decl.name);
                if (fb) {
                    fb->func_def = Expr_child(stmt, &(I64){(I64)(0)});
                    if (ft.tag == FuncType_TAG_ExtFunc || ft.tag == FuncType_TAG_ExtProc)
                        fb->is_builtin = 1;
                }
                break;
            }
            if (stmt->data.data.Decl.explicit_type.count > 0) {
                Str *etn = &stmt->data.data.Decl.explicit_type;
                TilType declared = type_from_name(etn, scope);
                if (declared.tag == TilType_TAG_Unknown) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", etn->c_str);
                    type_error(stmt, buf);
                } else if (declared.tag == TilType_TAG_Dynamic && !stmt->data.data.Decl.is_own) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "cannot store Dynamic in '%s'; use 'own' with Dynamic type",
                             stmt->data.data.Decl.name.c_str);
                    type_error(stmt, buf);
                } else if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_LiteralNum &&
                           (is_numeric_type(declared) || declared.tag == TilType_TAG_Dynamic)) {
                    // Numeric literals can be used with numeric types and Dynamic (0 = null)
                    if (is_numeric_type(declared) && !literal_in_range((const char *)Expr_child(stmt, &(I64){(I64)(0)})->data.data.Ident.c_str, declared)) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "integer literal %s out of range for %s",
                                 Expr_child(stmt, &(I64){(I64)(0)})->data.data.Ident.c_str, til_type_name_c(&declared)->c_str);
                        type_error(Expr_child(stmt, &(I64){(I64)(0)}), buf);
                    }
                    Expr_child(stmt, &(I64){(I64)(0)})->til_type = declared;
                } else if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_LiteralNull && !stmt->data.data.Decl.is_ref) {
                    type_error(stmt, "null can only be assigned to 'ref' declarations");
                } else if (Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag != declared.tag &&
                           Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag != TilType_TAG_Dynamic) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.data.Decl.name.c_str, til_type_name_c(&declared)->c_str,
                             til_type_name_c(&Expr_child(stmt, &(I64){(I64)(0)})->til_type)->c_str);
                    type_error(stmt, buf);
                } else if ((declared.tag == TilType_TAG_Struct || declared.tag == TilType_TAG_Enum) &&
                           (Expr_child(stmt, &(I64){(I64)(0)})->struct_name.count > 0) &&
                           !*Str_eq(etn, &Expr_child(stmt, &(I64){(I64)(0)})->struct_name)) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.data.Decl.name.c_str, etn->c_str, Expr_child(stmt, &(I64){(I64)(0)})->struct_name.c_str);
                    type_error(stmt, buf);
                }
                stmt->til_type = declared;
                // Narrow Dynamic RHS to declared type
                narrow_dynamic(Expr_child(stmt, &(I64){(I64)(0)}), declared, etn);
                // For struct/enum types, propagate struct_name from explicit type
                if (declared.tag == TilType_TAG_Struct || declared.tag == TilType_TAG_Enum) {
                    Expr_child(stmt, &(I64){(I64)(0)})->struct_name = *etn;
                }
            } else {
                stmt->til_type = Expr_child(stmt, &(I64){(I64)(0)})->til_type;
                if (stmt->til_type.tag == TilType_TAG_Dynamic) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "cannot store Dynamic in '%s'; add a type annotation like '%s : Type = ...' to specify the concrete type",
                             stmt->data.data.Decl.name.c_str, stmt->data.data.Decl.name.c_str);
                    type_error(stmt, buf);
                }
            }
            tscope_set(scope, &stmt->data.data.Decl.name, stmt->til_type, -1, stmt->data.data.Decl.is_mut, stmt->line, stmt->col, 0, 0);
            if ((stmt->til_type.tag == TilType_TAG_Struct || stmt->til_type.tag == TilType_TAG_Enum) && (Expr_child(stmt, &(I64){(I64)(0)})->struct_name.count > 0)) {
                TypeBinding *b = tscope_find(scope, &stmt->data.data.Decl.name);
                if (b) b->struct_name = Str_clone(&Expr_child(stmt, &(I64){(I64)(0)})->struct_name);
            }
            // For function pointer variables, propagate func_def from source or fn_sig
            if (stmt->til_type.tag == TilType_TAG_FuncPtr) {
                TypeBinding *dst = tscope_find(scope, &stmt->data.data.Decl.name);
                // Explicit Fn signature on decl takes priority
                if (dst && stmt->data.data.Decl.fn_sig) {
                    dst->func_def = stmt->data.data.Decl.fn_sig;
                } else if (dst && Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident) {
                    TypeBinding *src = tscope_find(scope, &Expr_child(stmt, &(I64){(I64)(0)})->data.data.Ident);
                    if (src && src->func_def) dst->func_def = src->func_def;
                } else if (dst && Expr_child(stmt, &(I64){(I64)(0)})->fn_sig) {
                    dst->func_def = Expr_child(stmt, &(I64){(I64)(0)})->fn_sig;
                }
                // Named FuncSig type in explicit type position
                if (dst && !dst->func_def && stmt->data.data.Decl.explicit_type.count > 0) {
                    TypeBinding *fsb = tscope_find(scope, &stmt->data.data.Decl.explicit_type);
                    if (fsb && fsb->func_def && fsb->func_def->children.count == 0)
                        dst->func_def = fsb->func_def;
                }
            }
            if (stmt->data.data.Decl.is_ref) {
                TypeBinding *b = tscope_find(scope, &stmt->data.data.Decl.name);
                if (b) b->is_ref = 1;
                // Validate ref RHS: must be null, a ref-returning fcall, or a ref/param variable
                Expr *rhs = Expr_child(stmt, &(I64){(I64)(0)});
                Bool ok = 0;
                if (rhs->data.tag == ExprData_TAG_LiteralNull) ok = 1;
                if (rhs->data.tag == ExprData_TAG_FCall && fcall_returns_ref(rhs, scope)) ok = 1;
                if (rhs->data.tag == ExprData_TAG_Ident) {
                    TypeBinding *rb = tscope_find(scope, &rhs->data.data.Ident);
                    if (rb && (rb->is_ref || (rb->is_param && !rb->is_own))) ok = 1;
                }
                if (!ok) type_error(stmt, "'ref' declaration requires null, a ref-returning function, or ref/param variable");
            }
            // Error: owning result of ref-returning function without ref
            if (!stmt->data.data.Decl.is_ref && Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FCall &&
                fcall_returns_ref(Expr_child(stmt, &(I64){(I64)(0)}), scope)) {
                type_error(stmt, "cannot own result of ref-returning function; use 'ref' or Type.clone()");
            }
            // Auto-alias: immutable ident → immutable dest becomes ref (skip for Fn)
            // Eligible sources: immutable locals, immutable params, other auto-aliases
            // Excluded: mut (value can change), own (ownership transfer),
            //           explicit ref (user intends to clone from borrowed value)
            if (!stmt->data.data.Decl.is_ref && !stmt->data.data.Decl.is_mut &&
                stmt->til_type.tag != TilType_TAG_FuncPtr &&
                Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident) {
                TypeBinding *rb = tscope_find(scope, &Expr_child(stmt, &(I64){(I64)(0)})->data.data.Ident);
                if (rb && !rb->is_mut && !rb->is_own &&
                    (!rb->is_ref || rb->is_alias) && !rb->is_param) {
                    stmt->data.data.Decl.is_ref = true;
                    TypeBinding *b = tscope_find(scope, &stmt->data.data.Decl.name);
                    if (b) { b->is_ref = 1; b->is_alias = 1; }
                }
            }
            // Auto-insert clone for declarations from identifiers (skip ref decls)
            if ((Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident ||
                 (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                  (Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag == TilType_TAG_Struct ||
                   Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag == TilType_TAG_Enum))) &&
                !stmt->data.data.Decl.is_ref) {
                const char *tname = type_to_name(stmt->til_type, &Expr_child(stmt, &(I64){(I64)(0)})->struct_name);
                if (tname) {
                    *(Expr*)Vec_get(&stmt->children, &(U64){(U64)(0)}) = *make_clone_call(
                        tname, stmt->til_type,
                        Expr_child(stmt, &(I64){(I64)(0)}), stmt);
                }
            }
            break;
        case ExprData_TAG_Assign: {
            infer_expr(scope, Expr_child(stmt, &(I64){(I64)(0)}), in_func);
            stmt->til_type = Expr_child(stmt, &(I64){(I64)(0)})->til_type;
            Str *aname = &stmt->data.data.Ident;
            TilType existing = tscope_get(scope, aname);
            if (existing.tag == TilType_TAG_Unknown) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined symbol '%s'", aname->c_str);
                type_error(stmt, buf);
            } else if (!tscope_is_mut(scope, aname)) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot assign to immutable variable '%s'", aname->c_str);
                type_error(stmt, buf);
                TypeBinding *b = tscope_find(scope, aname);
                if (b && b->is_param) {
                    fprintf(stderr, "%s:%u:%u: note: '%s' is a function parameter\n",
                            stmt->path.c_str, b->line, b->col, aname->c_str);
                } else if (b) {
                    fprintf(stderr, "%s:%u:%u: note: '%s' declared here, consider adding 'mut'\n",
                            stmt->path.c_str, b->line, b->col, aname->c_str);
                }
            } else if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_LiteralNum && is_numeric_type(existing)) {
                if (!literal_in_range((const char *)Expr_child(stmt, &(I64){(I64)(0)})->data.data.Ident.c_str, existing)) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "integer literal %s out of range for %s",
                             Expr_child(stmt, &(I64){(I64)(0)})->data.data.Ident.c_str, til_type_name_c(&existing)->c_str);
                    type_error(stmt, buf);
                }
                Expr_child(stmt, &(I64){(I64)(0)})->til_type = existing;
                stmt->til_type = existing;
            } else if (Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag != existing.tag &&
                       Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag != TilType_TAG_Unknown) {
                char buf[128];
                snprintf(buf, sizeof(buf), "'%s' is %s but assigned %s",
                         aname->c_str, til_type_name_c(&existing)->c_str,
                         til_type_name_c(&Expr_child(stmt, &(I64){(I64)(0)})->til_type)->c_str);
                type_error(stmt, buf);
            }
            // Auto-insert clone for assignments from identifiers
            if (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident ||
                (Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                 (Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag == TilType_TAG_Struct ||
                  Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag == TilType_TAG_Enum))) {
                const char *tname = type_to_name(Expr_child(stmt, &(I64){(I64)(0)})->til_type, &Expr_child(stmt, &(I64){(I64)(0)})->struct_name);
                if (tname) {
                    *(Expr*)Vec_get(&stmt->children, &(U64){(U64)(0)}) = *make_clone_call(
                        tname, Expr_child(stmt, &(I64){(I64)(0)})->til_type,
                        Expr_child(stmt, &(I64){(I64)(0)}), stmt);
                }
            }
            break;
        }
        case ExprData_TAG_FieldAssign: {
            infer_expr(scope, Expr_child(stmt, &(I64){(I64)(0)}), in_func); // object
            infer_expr(scope, Expr_child(stmt, &(I64){(I64)(1)}), in_func); // value
            Expr *obj = Expr_child(stmt, &(I64){(I64)(0)});
            Str *fname = &stmt->data.data.Ident;
            if (obj->struct_name.count > 0) {
                Expr *sdef = tscope_get_struct(scope, &obj->struct_name);
                if (sdef) {
                    Expr *body = Expr_child(sdef, &(I64){(I64)(0)});
                    Bool found = 0;
                    for (U32 i = 0; i < body->children.count; i++) {
                        Expr *field = Expr_child(body, &(I64){(I64)(i)});
                        if (*Str_eq(&field->data.data.Decl.name, fname)) {
                            found = 1;
                            stmt->is_ns_field = field->data.data.Decl.is_namespace;
                            stmt->is_own_field = field->data.data.Decl.is_own || field->data.data.Decl.is_ref;
                            stmt->is_ref_field = field->data.data.Decl.is_ref;
                            if (!field->data.data.Decl.is_mut) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "cannot assign to immutable field '%s'", fname->c_str);
                                type_error(stmt, buf);
                            }
                            if (Expr_child(stmt, &(I64){(I64)(1)})->data.tag == ExprData_TAG_LiteralNum && is_numeric_type(field->til_type)) {
                                if (!literal_in_range((const char *)Expr_child(stmt, &(I64){(I64)(1)})->data.data.Ident.c_str, field->til_type)) {
                                    char buf[128];
                                    snprintf(buf, sizeof(buf), "integer literal %s out of range for field '%s' (%s)",
                                             Expr_child(stmt, &(I64){(I64)(1)})->data.data.Ident.c_str, fname->c_str, til_type_name_c(&field->til_type)->c_str);
                                    type_error(Expr_child(stmt, &(I64){(I64)(1)}), buf);
                                }
                                Expr_child(stmt, &(I64){(I64)(1)})->til_type = field->til_type;
                            } else if (Expr_child(stmt, &(I64){(I64)(1)})->til_type.tag != field->til_type.tag &&
                                Expr_child(stmt, &(I64){(I64)(1)})->til_type.tag != TilType_TAG_Unknown &&
                                Expr_child(stmt, &(I64){(I64)(1)})->til_type.tag != TilType_TAG_Dynamic) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "field '%s' is %s but assigned %s",
                                         fname->c_str, til_type_name_c(&field->til_type)->c_str,
                                         til_type_name_c(&Expr_child(stmt, &(I64){(I64)(1)})->til_type)->c_str);
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
                (Expr_child(stmt, &(I64){(I64)(1)})->data.tag == ExprData_TAG_Ident ||
                 (Expr_child(stmt, &(I64){(I64)(1)})->data.tag == ExprData_TAG_FieldAccess &&
                  (Expr_child(stmt, &(I64){(I64)(1)})->til_type.tag == TilType_TAG_Struct ||
                   Expr_child(stmt, &(I64){(I64)(1)})->til_type.tag == TilType_TAG_Enum)))) {
                const char *tname = type_to_name(Expr_child(stmt, &(I64){(I64)(1)})->til_type,
                                                  &Expr_child(stmt, &(I64){(I64)(1)})->struct_name);
                if (tname) {
                    *(Expr*)Vec_get(&stmt->children, &(U64){(U64)(1)}) = *make_clone_call(tname,
                        Expr_child(stmt, &(I64){(I64)(1)})->til_type, Expr_child(stmt, &(I64){(I64)(1)}),
                        Expr_child(stmt, &(I64){(I64)(1)}));
                }
            }
            break;
        }
        case ExprData_TAG_FCall:
            infer_expr(scope, stmt, in_func);
            break;
        case ExprData_TAG_Return:
            if (stmt->children.count > 0) {
                infer_expr(scope, Expr_child(stmt, &(I64){(I64)(0)}), in_func);
                stmt->til_type = Expr_child(stmt, &(I64){(I64)(0)})->til_type;
                // Error: returning an explicit ref variable from a non-ref function
                if (!returns_ref && Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident) {
                    TypeBinding *b = tscope_find(scope, &Expr_child(stmt, &(I64){(I64)(0)})->data.data.Ident);
                    if (b && b->is_ref && !b->is_alias && !b->is_param) {
                        type_error(stmt, "cannot return ref variable from non-ref function; use .clone() or 'returns ref'");
                    }
                }
                // Auto-insert clone when returning a borrowed param or auto-alias
                // (prevents use-after-free: aliases share storage with locals,
                //  params are borrowed — both need cloning to return safely)
                if (!returns_ref && Expr_child(stmt, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident) {
                    TypeBinding *b = tscope_find(scope, &Expr_child(stmt, &(I64){(I64)(0)})->data.data.Ident);
                    if (b && ((b->is_ref && b->is_alias) || (b->is_param && !b->is_own))) {
                        const char *tname = type_to_name(stmt->til_type, &Expr_child(stmt, &(I64){(I64)(0)})->struct_name);
                        if (tname) {
                            *(Expr*)Vec_get(&stmt->children, &(U64){(U64)(0)}) = *make_clone_call(
                                tname, stmt->til_type,
                                Expr_child(stmt, &(I64){(I64)(0)}), stmt);
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
            infer_expr(scope, Expr_child(stmt, &(I64){(I64)(0)}), in_func); // condition
            if (Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag != TilType_TAG_Bool &&
                Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag != TilType_TAG_Unknown) {
                char buf[128];
                snprintf(buf, sizeof(buf), "if condition must be Bool, got %s",
                         til_type_name_c(&Expr_child(stmt, &(I64){(I64)(0)})->til_type)->c_str);
                type_error(stmt, buf);
            }
            {
                TypeScope *then_scope = tscope_new(scope);
                infer_body(then_scope, Expr_child(stmt, &(I64){(I64)(1)}), in_func, 1, in_loop, returns_ref);
                tscope_free(then_scope);
            }
            if (stmt->children.count > 2) {
                TypeScope *else_scope = tscope_new(scope);
                infer_body(else_scope, Expr_child(stmt, &(I64){(I64)(2)}), in_func, 1, in_loop, returns_ref);
                tscope_free(else_scope);
            }
            stmt->til_type = (TilType){TilType_TAG_None};
            break;
        case ExprData_TAG_Body: {
            TypeScope *block_scope = tscope_new(scope);
            infer_body(block_scope, stmt, in_func, 1, in_loop, returns_ref);
            tscope_free(block_scope);
            break;
        }
        case ExprData_TAG_While:
            infer_expr(scope, Expr_child(stmt, &(I64){(I64)(0)}), in_func); // condition
            if (Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag != TilType_TAG_Bool &&
                Expr_child(stmt, &(I64){(I64)(0)})->til_type.tag != TilType_TAG_Unknown) {
                char buf[128];
                snprintf(buf, sizeof(buf), "while condition must be Bool, got %s",
                         til_type_name_c(&Expr_child(stmt, &(I64){(I64)(0)})->til_type)->c_str);
                type_error(stmt, buf);
            }
            // Transform: while COND { BODY } -> while true { _wcond := COND; if _wcond {} else { break }; BODY }
            // This lets ASAP destruction free the condition result each iteration.
            if (expr_contains_fcall(Expr_child(stmt, &(I64){(I64)(0)}))) {
                Expr *cond = Expr_child(stmt, &(I64){(I64)(0)});
                I32 line = cond->line;
                I32 col = cond->col;
                Str *path = &cond->path;
                Expr *body = Expr_child(stmt, &(I64){(I64)(1)});
                // _wcondN := COND
                char name_buf[32];
                snprintf(name_buf, sizeof(name_buf), "_wcond%d", hoist_counter++);
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
                Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
                Vec_push(&new_ch, decl);
                Vec_push(&new_ch, if_node);
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *ch = Expr_child(body, &(I64){(I64)(j)});
                    Vec_push(&new_ch, Expr_clone(ch));
                }
                Vec_delete(&body->children, &(Bool){0});
                body->children = new_ch;
                // Replace condition with true
                Expr *true_lit = Expr_new(&(ExprData){.tag = ExprData_TAG_LiteralBool}, line, col, path);
                true_lit->data.data.LiteralBool = (Str){.c_str = (U8*)"true", .count = 4, .cap = CAP_LIT};
                true_lit->til_type = (TilType){TilType_TAG_Bool};
                *(Expr*)Vec_get(&stmt->children, &(U64){(U64)(0)}) = *true_lit;
            }
            {
                TypeScope *while_scope = tscope_new(scope);
                infer_body(while_scope, Expr_child(stmt, &(I64){(I64)(1)}), in_func, 1, 1, returns_ref);
                tscope_free(while_scope);
            }
            stmt->til_type = (TilType){TilType_TAG_None};
            break;
        case ExprData_TAG_Switch: {
            // Desugar: switch expr { case v1: B1  case v2: B2  case: B3 }
            // Into:   { _swN := expr; if _swN.eq(v1) { B1 } else if _swN.eq(v2) { B2 } else { B3 } }
            Expr *sw_expr = Expr_child(stmt, &(I64){(I64)(0)});
            I32 sw_line = stmt->line, sw_col = stmt->col;
            Str *sw_path = &stmt->path;

            // Unique switch variable name
            char sw_buf[32];
            snprintf(sw_buf, sizeof(sw_buf), "_sw%d", hoist_counter++);
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
                Expr *case_node = Expr_child(stmt, &(I64){(I64)(ci)});
                if (case_node->children.count == 1) {
                    // Default case — just body, no match expr
                    default_body = Expr_child(case_node, &(I64){(I64)(0)});
                    continue;
                }
                Expr *match_expr = Expr_child(case_node, &(I64){(I64)(0)});
                Expr *case_body = Expr_child(case_node, &(I64){(I64)(1)});
                Expr *condition = NULL;

                // Phase 2: Range case — case A..B: → _sw.gte(A).and(_sw.lte(B))
                // Detect Range.new(start, end) pattern from parser's .. desugaring
                if (match_expr->data.tag == ExprData_TAG_FCall &&
                    match_expr->children.count == 3 &&
                    Expr_child(match_expr, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                    (Expr_child(match_expr, &(I64){(I64)(0)})->data.data.Ident.count == 3 && memcmp(Expr_child(match_expr, &(I64){(I64)(0)})->data.data.Ident.c_str, "new", 3) == 0) &&
                    Expr_child(Expr_child(match_expr, &(I64){(I64)(0)}), &(I64){0})->data.tag == ExprData_TAG_Ident &&
                    (Expr_child(Expr_child(match_expr, &(I64){(I64)(0)}), &(I64){0})->data.data.Ident.count == 5 && memcmp(Expr_child(Expr_child(match_expr, &(I64){(I64)(0)}), &(I64){0})->data.data.Ident.c_str, "Range", 5) == 0)) {
                    Expr *start_expr = Expr_child(match_expr, &(I64){(I64)(1)});
                    Expr *end_expr = Expr_child(match_expr, &(I64){(I64)(2)});

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
                    Expr_child(match_expr, &(I64){(I64)(0)})->data.tag == ExprData_TAG_FieldAccess &&
                    Expr_child(Expr_child(match_expr, &(I64){(I64)(0)}), &(I64){0})->data.tag == ExprData_TAG_Ident &&
                    Expr_child(match_expr, &(I64){(I64)(1)})->data.tag == ExprData_TAG_Ident) {
                    Expr *callee = Expr_child(match_expr, &(I64){(I64)(0)});
                    Str *type_name = &Expr_child(callee, &(I64){(I64)(0)})->data.data.Ident;
                    Str *variant_name = &callee->data.data.Ident;
                    Str *binding_name = &Expr_child(match_expr, &(I64){(I64)(1)})->data.data.Ident;
                    Expr *enum_def = tscope_get_struct(scope, type_name);
                    if (enum_def && enum_def->data.tag == ExprData_TAG_EnumDef) {
                        I32 tag = *enum_variant_tag(enum_def, variant_name);
                        Str *payload_type = (tag >= 0) ? enum_variant_type(enum_def, tag) : NULL;
                        if (payload_type && payload_type->count > 0) {
                            // Build _sw.is_Variant()
                            char is_buf[256];
                            snprintf(is_buf, sizeof(is_buf), "is_%s", variant_name->c_str);
                            Expr *sw_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            sw_id->data.data.Ident = *sw_name;
                            Expr *is_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, sw_line, sw_col, sw_path);
                            is_acc->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(is_buf), .count = (U64)strlen((const char*)(is_buf)), .cap = CAP_VIEW});
                            Expr_add_child(is_acc, sw_id);
                            condition = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                            Expr_add_child(condition, is_acc);

                            // Prepend binding: binding_name := _sw.get_Variant()
                            char get_buf[256];
                            snprintf(get_buf, sizeof(get_buf), "get_%s", variant_name->c_str);
                            Expr *sw_id2 = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            sw_id2->data.data.Ident = *sw_name;
                            Expr *get_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, sw_line, sw_col, sw_path);
                            get_acc->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(get_buf), .count = (U64)strlen((const char*)(get_buf)), .cap = CAP_VIEW});
                            Expr_add_child(get_acc, sw_id2);
                            Expr *get_call = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                            Expr_add_child(get_call, get_acc);

                            Expr *bind_decl = Expr_new(&(ExprData){.tag = ExprData_TAG_Decl}, sw_line, sw_col, sw_path);
                            bind_decl->data.data.Decl.name = *binding_name;
                            bind_decl->data.data.Decl.explicit_type = *payload_type;
                            bind_decl->data.data.Decl.is_mut = false;
                            bind_decl->data.data.Decl.is_namespace = false;
                            bind_decl->data.data.Decl.is_ref = false;
                            bind_decl->data.data.Decl.is_own = false;
                            Expr_add_child(bind_decl, get_call);

                            // Prepend to case body
                            Vec new_ch; { Vec *_vp = Vec_new(&(Str){.c_str = (U8*)"", .count = 0, .cap = CAP_LIT}, &(U64){sizeof(Expr)}); new_ch = *_vp; free(_vp); }
                            Vec_push(&new_ch, bind_decl);
                            for (U32 bi = 0; bi < case_body->children.count; bi++) {
                                Expr *ch = Expr_child(case_body, &(I64){(I64)(bi)});
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
                    Expr_child(match_expr, &(I64){(I64)(0)})->data.tag == ExprData_TAG_Ident) {
                    Str *type_name = &Expr_child(match_expr, &(I64){(I64)(0)})->data.data.Ident;
                    Str *variant_name = &match_expr->data.data.FieldAccess;
                    Expr *enum_def = tscope_get_struct(scope, type_name);
                    if (enum_def && enum_def->data.tag == ExprData_TAG_EnumDef) {
                        I32 tag = *enum_variant_tag(enum_def, variant_name);
                        Str *payload_type = (tag >= 0) ? enum_variant_type(enum_def, tag) : NULL;
                        if (payload_type && payload_type->count > 0) {
                            // Payload variant without binding — use is_Variant()
                            char is_buf[256];
                            snprintf(is_buf, sizeof(is_buf), "is_%s", variant_name->c_str);
                            Expr *sw_id = Expr_new(&(ExprData){.tag = ExprData_TAG_Ident}, sw_line, sw_col, sw_path);
                            sw_id->data.data.Ident = *sw_name;
                            Expr *is_acc = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, sw_line, sw_col, sw_path);
                            is_acc->data.data.FieldAccess = *Str_clone(&(Str){.c_str = (U8*)(is_buf), .count = (U64)strlen((const char*)(is_buf)), .cap = CAP_VIEW});
                            Expr_add_child(is_acc, sw_id);
                            condition = Expr_new(&(ExprData){.tag = ExprData_TAG_FCall}, sw_line, sw_col, sw_path);
                            Expr_add_child(condition, is_acc);
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
                    last_if = Expr_child(Expr_child(last_if, &(I64){(I64)(last_if->children.count - 1)}), &(I64){(I64)(0)});
                }
            }

            // Attach default as final else
            if (default_body && last_if) {
                Expr_add_child(last_if, Expr_clone(default_body));
            } else if (default_body && !first_if) {
                // Only a default case — just emit the body
                first_if = default_body;
            }

            if (first_if) Expr_add_child(block, first_if);

            // Replace ExprData_TAG_Switch with desugared block
            {
                Expr *slot = (Expr*)Vec_get(&body->children, &(U64){(U64)(i)});
                *slot = *block;
                // Deep-copy children buffer so slot doesn't share with block
                U64 sz = block->children.count * block->children.elem_size;
                slot->children.data = malloc(sz ? sz : 1);
                memcpy(slot->children.data, block->children.data, sz);
                slot->children.cap = block->children.count ? block->children.count : 1;
            }
            i--; // re-visit to type-check
            break;
        }
        case ExprData_TAG_ForIn: {
            // Validate iterable and desugar to while loop in anonymous scope
            Expr *iter = Expr_child(stmt, &(I64){(I64)(0)});
            infer_expr(scope, iter, in_func);

            // Iterable must be a struct type
            Str *type_name = NULL;
            if ((iter->til_type.tag == TilType_TAG_Struct || iter->til_type.tag == TilType_TAG_Enum) && iter->struct_name.count > 0)
                type_name = &iter->struct_name;
            if (!type_name) {
                type_error(stmt, "for-in requires a collection type with get() and len() methods");
                break;
            }

            Expr *sdef = tscope_get_struct(scope, type_name);
            if (!sdef) {
                type_error(stmt, "for-in requires a collection type with get() and len() methods");
                break;
            }

            // Find len() and get() in namespace, validate signatures
            Expr *len_func = NULL, *get_func = NULL;
            Expr *sbody = Expr_child(sdef, &(I64){(I64)(0)});
            for (U32 fi = 0; fi < sbody->children.count; fi++) {
                Expr *field = Expr_child(sbody, &(I64){(I64)(fi)});
                if (!field->data.data.Decl.is_namespace) continue;
                if (Expr_child(field, &(I64){(I64)(0)})->data.tag != ExprData_TAG_FuncDef) continue;
                if ((field->data.data.Decl.name.count == 3 && memcmp(field->data.data.Decl.name.c_str, "len", 3) == 0)) len_func = Expr_child(field, &(I64){(I64)(0)});
                if ((field->data.data.Decl.name.count == 3 && memcmp(field->data.data.Decl.name.c_str, "get", 3) == 0)) get_func = Expr_child(field, &(I64){(I64)(0)});
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
            if (get_func->data.data.FuncDef.nparam != 2 || !((Str*)Vec_get(&get_func->data.data.FuncDef.param_types, &(U64){(U64)(1)})) ||
                !*Str_eq(((Str*)Vec_get(&get_func->data.data.FuncDef.param_types, &(U64){(U64)(1)})), idx_type)) {
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
            Expr *for_body = Expr_child(stmt, &(I64){(I64)(1)});
            I32 line = stmt->line;
            I32 col = stmt->col;
            Str *path = &stmt->path;

            // Unique index variable name
            char idx_buf[32];
            snprintf(idx_buf, sizeof(idx_buf), "_fi%d", hoist_counter++);
            Str *idx_name = Str_clone(&(Str){.c_str = (U8*)(idx_buf), .count = (U64)strlen((const char*)(idx_buf)), .cap = CAP_VIEW});

            // Outer block (anonymous scope)
            Expr *block = Expr_new(&(ExprData){.tag = ExprData_TAG_Body}, line, col, path);

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

            // Condition: _fiN.lt(collection.len())
            // Build: collection.len() → ExprData_TAG_FCall(ExprData_TAG_FieldAccess(iter_clone, "len"))
            Expr *iter_len = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            iter_len->data.data.FieldAccess = (Str){.c_str = (U8*)"len", .count = 3, .cap = CAP_LIT};
            Expr_add_child(iter_len, Expr_clone(iter));
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

            // collection.get(_fiN) → ExprData_TAG_FCall(ExprData_TAG_FieldAccess(iter_clone, "get"), idx_ident)
            Expr *iter_get = Expr_new(&(ExprData){.tag = ExprData_TAG_FieldAccess}, line, col, path);
            iter_get->data.data.FieldAccess = (Str){.c_str = (U8*)"get", .count = 3, .cap = CAP_LIT};
            Expr_add_child(iter_get, Expr_clone(iter));
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
                Expr_add_child(wbody, Expr_clone(Expr_child(for_body, &(I64){(I64)(bi)})));
            }

            Expr_add_child(while_node, wbody);
            Expr_add_child(block, while_node);

            // Replace FOR_IN with the desugared block in parent body
            {
                Expr *slot = (Expr*)Vec_get(&body->children, &(U64){(U64)(i)});
                *slot = *block;
                U64 sz = block->children.count * block->children.elem_size;
                slot->children.data = malloc(sz ? sz : 1);
                memcpy(slot->children.data, block->children.data, sz);
                slot->children.cap = block->children.count ? block->children.count : 1;
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

I32 type_check(Expr *program, TypeScope *scope, const Mode *mode) {
    errors = 0;
    current_mode = mode;
    infer_body(scope, program, 0, 1, 0, 0);
    return errors;
}
