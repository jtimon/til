#include "typer.h"
#include "initer.h"
#include "vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type inference/checking pass ---

static I32 errors;
static const Mode *current_mode;

static void type_error(Expr *e, const char *msg) {
    fprintf(stderr, "%s:%u:%u: type error: %s\n", e->path->c_str, e->line, e->col, msg);
    errors++;
}

// Parse a type name string to TilType (scope-aware for user-defined struct types)
static TilType type_from_name(Str *name, TypeScope *scope) {
    if (Str_eq_c(name, "I64"))  return TIL_TYPE_I64;
    if (Str_eq_c(name, "U8"))   return TIL_TYPE_U8;
    if (Str_eq_c(name, "I16"))  return TIL_TYPE_I16;
    if (Str_eq_c(name, "I32"))  return TIL_TYPE_I32;
    if (Str_eq_c(name, "U32"))  return TIL_TYPE_U32;
    if (Str_eq_c(name, "Str"))  return TIL_TYPE_STRUCT;
    if (Str_eq_c(name, "Bool")) return TIL_TYPE_BOOL;
    if (Str_eq_c(name, "StructDef"))    return TIL_TYPE_STRUCT_DEF;
    if (Str_eq_c(name, "EnumDef"))      return TIL_TYPE_ENUM_DEF;
    if (Str_eq_c(name, "FunctionDef"))  return TIL_TYPE_FUNC_DEF;
    if (Str_eq_c(name, "Dynamic"))     return TIL_TYPE_DYNAMIC;
    // Check scope for user-defined struct/enum types
    if (scope) {
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) return (sdef->type == NODE_ENUM_DEF) ? TIL_TYPE_ENUM : TIL_TYPE_STRUCT;
    }
    return TIL_TYPE_UNKNOWN;
}

static void infer_expr(TypeScope *scope, Expr *e, I32 in_func);
static void infer_body(TypeScope *scope, Expr *body, I32 in_func, I32 owns_scope, I32 in_loop);
static const char *type_to_name(TilType type, Str *struct_name);
static Expr *make_clone_call(const char *type_name, TilType type, Expr *arg, Expr *src);
static I32 fcall_returns_ref(Expr *fcall, TypeScope *scope);

// Narrow a Dynamic-typed expression to a concrete target type.
// Used for both declarations with explicit types and function arguments.
static void narrow_dynamic(Expr *expr, TilType target, Str *target_struct_name) {
    if (expr->til_type != TIL_TYPE_DYNAMIC || target == TIL_TYPE_DYNAMIC ||
        target == TIL_TYPE_UNKNOWN)
        return;
    expr->til_type = target;
    if (target == TIL_TYPE_STRUCT || target == TIL_TYPE_ENUM)
        expr->struct_name = target_struct_name;
}

static void infer_expr(TypeScope *scope, Expr *e, I32 in_func) {
    switch (e->type) {
    case NODE_LITERAL_STR:
        e->til_type = TIL_TYPE_STRUCT;
        e->struct_name = Str_new("Str");
        break;
    case NODE_LITERAL_NUM:
        e->til_type = TIL_TYPE_I64;
        break;
    case NODE_LITERAL_BOOL:
        e->til_type = TIL_TYPE_BOOL;
        break;
    case NODE_IDENT: {
        TilType t = tscope_get(scope, e->data.str_val);
        if (t == TIL_TYPE_UNKNOWN) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined symbol '%s'", e->data.str_val->c_str);
            type_error(e, buf);
        }
        e->til_type = t;
        if (t == TIL_TYPE_STRUCT || t == TIL_TYPE_ENUM) {
            TypeBinding *b = tscope_find(scope, e->data.str_val);
            if (b) e->struct_name = b->struct_name;
        }
        // Struct type names: allow field access for namespace fields
        TypeBinding *ib = tscope_find(scope, e->data.str_val);
        if (ib && ib->struct_def) {
            e->struct_name = e->data.str_val;
        }
        break;
    }
    case NODE_FUNC_DEF:
        e->til_type = TIL_TYPE_NONE;
        // Type the body
        {
            FuncType ftype = e->data.func_def.func_type;
            Bool is_func = (ftype == FUNC_FUNC);
            Bool is_macro = (ftype == FUNC_MACRO);
            // Test function constraints
            if (ftype == FUNC_TEST) {
                if (scope->parent != NULL)
                    type_error(e, "test functions can only be declared in root scope");
                if (e->data.func_def.return_type)
                    type_error(e, "test functions cannot have a return type");
                if (e->data.func_def.nparam > 0)
                    type_error(e, "test functions cannot have parameters");
            }
            // Pure mode: reject user-declared procs (allow core procs)
            if (current_mode && current_mode->is_pure && ftype == FUNC_PROC && !e->is_core)
                type_error(e, "proc not allowed in pure mode");
            TypeScope *func_scope = tscope_new(scope);
            // Bind parameters
            for (U32 i = 0; i < e->data.func_def.nparam; i++) {
                Str *ptn = e->data.func_def.param_types[i];
                TilType pt = type_from_name(ptn, scope);
                if (pt == TIL_TYPE_UNKNOWN) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", ptn->c_str);
                    type_error(e, buf);
                }
                Bool pmut = e->data.func_def.param_muts ? e->data.func_def.param_muts[i] : 0;
                Bool pown = e->data.func_def.param_owns ? e->data.func_def.param_owns[i] : 0;
                // Variadic param: bind as Array (element type already validated above)
                if ((I32)i == e->data.func_def.variadic_index) {
                    if (e->data.func_def.param_owns) e->data.func_def.param_owns[i] = true;
                    tscope_set(func_scope, e->data.func_def.param_names[i], TIL_TYPE_STRUCT, -1, 0, e->line, e->col, 1, 1);
                    TypeBinding *pb = tscope_find(func_scope, e->data.func_def.param_names[i]);
                    if (pb) pb->struct_name = Str_new("Array");
                } else {
                    tscope_set(func_scope, e->data.func_def.param_names[i], pt, -1, pmut, e->line, e->col, 1, pown);
                    // For struct/enum-typed params, store struct_name
                    if (pt == TIL_TYPE_STRUCT || pt == TIL_TYPE_ENUM) {
                        TypeBinding *pb = tscope_find(func_scope, e->data.func_def.param_names[i]);
                        if (pb) pb->struct_name = ptn;
                    }
                }
            }
            infer_body(func_scope, expr_child(e, 0), is_func, 1, 0);
            // Check: func/macro must have a return type
            if ((is_func || is_macro) && !e->data.func_def.return_type) {
                type_error(e, is_macro ? "macro must declare a return type"
                                             : "func must declare a return type");
            }
            // Validate ref returns: every return value must be a param or ref variable
            if (e->data.func_def.return_is_ref) {
                Expr *body = expr_child(e, 0);
                for (U32 ri = 0; ri < body->children.count; ri++) {
                    Expr *s = expr_child(body, ri);
                    if (s->type != NODE_RETURN || s->children.count == 0) continue;
                    Expr *rv = expr_child(s, 0);
                    Bool ok = 0;
                    if (rv->type == NODE_IDENT) {
                        TypeBinding *rb = tscope_find(func_scope, rv->data.str_val);
                        if (rb && (rb->is_param || rb->is_ref)) ok = 1;
                    }
                    if (rv->type == NODE_FCALL && fcall_returns_ref(rv, func_scope)) ok = 1;
                    if (!ok) type_error(s, "ref function must return a parameter or ref variable");
                }
            }
            tscope_free(func_scope);
        }
        break;
    case NODE_STRUCT_DEF:
    case NODE_ENUM_DEF: {
        e->til_type = TIL_TYPE_NONE;
        // Type-check field declarations in a child scope so fields
        // don't leak into outer scope's locals for free-call insertion
        TypeScope *inner = tscope_new(scope);
        infer_body(inner, expr_child(e, 0), 0, 0, 0);
        tscope_free(inner);
        break;
    }
    case NODE_FCALL: {
        // Namespace method call or UFCS: Type.method(args) or instance.method(args)
        if (expr_child(e, 0)->type == NODE_FIELD_ACCESS) {
            Expr *fa = expr_child(e, 0);
            Expr *obj = expr_child(fa, 0);
            Str *method = fa->data.str_val;

            // Type just the object first (not the full field access)
            infer_expr(scope, obj, in_func);

            // Check: is obj a type name (has struct_def) or an instance/value?
            TypeBinding *tb = (obj->type == NODE_IDENT)
                ? tscope_find(scope, obj->data.str_val) : NULL;
            Bool obj_is_type = (tb && tb->struct_def);

            if (!obj_is_type) {
                // UFCS: instance.method(args) -> Type.method(instance, args)
                Str *type_name = NULL;
                if (obj->til_type == TIL_TYPE_I64)  type_name = Str_new("I64");
                else if (obj->til_type == TIL_TYPE_U8)   type_name = Str_new("U8");
                else if (obj->til_type == TIL_TYPE_I16)  type_name = Str_new("I16");
                else if (obj->til_type == TIL_TYPE_I32)  type_name = Str_new("I32");
                else if (obj->til_type == TIL_TYPE_U32)  type_name = Str_new("U32");
                else if (obj->til_type == TIL_TYPE_BOOL) type_name = Str_new("Bool");
                else if ((obj->til_type == TIL_TYPE_STRUCT || obj->til_type == TIL_TYPE_ENUM) && obj->struct_name)
                    type_name = obj->struct_name;

                Expr *sdef = type_name ? tscope_get_struct(scope, type_name) : NULL;
                Expr *ns_func = NULL;
                if (sdef) {
                    Expr *body = expr_child(sdef, 0);
                    for (U32 i = 0; i < body->children.count; i++) {
                        Expr *field = expr_child(body, i);
                        if (field->data.decl.is_namespace &&
                            Str_eq(field->data.decl.name, method) &&
                            expr_child(field, 0)->type == NODE_FUNC_DEF) {
                            ns_func = expr_child(field, 0);
                            break;
                        }
                    }
                }
                if (!ns_func) {
                    // UFCS fallback: check top-level for f(a: T, ...)
                    TypeBinding *top = tscope_find(scope, method);
                    Bool ufcs_match = 0;
                    if (top && top->func_def &&
                        top->func_def->data.func_def.nparam > 0 &&
                        top->func_def->data.func_def.param_types[0]) {
                        Str *first_param = top->func_def->data.func_def.param_types[0];
                        if (type_name && Str_eq(first_param, type_name)) {
                            ufcs_match = 1; // known type matches first param
                        } else if (!type_name && obj->til_type == TIL_TYPE_DYNAMIC) {
                            // Dynamic receiver: narrow to first param type
                            TilType pt = type_from_name(first_param, scope);
                            narrow_dynamic(obj, pt, first_param);
                            ufcs_match = 1;
                        }
                    }
                    if (ufcs_match) {
                        // Rewrite: a.f(b) → f(a, b)
                        Expr *fn_ident = expr_new(NODE_IDENT, fa->line, fa->col, fa->path);
                        fn_ident->data.str_val = method;
                        expr_child(e, 0) = fn_ident;
                        // Insert instance as first arg
                        Expr *instance = obj;
                        Expr *dummy = NULL;
                        Vec_push(&e->children, &dummy);
                        memmove(&expr_child(e, 2), &expr_child(e, 1),
                                (e->children.count - 2) * sizeof(Expr *));
                        expr_child(e, 1) = instance;
                        goto regular_call;
                    }
                    char buf[256];
                    if (!type_name && obj->til_type == TIL_TYPE_DYNAMIC) {
                        snprintf(buf, sizeof(buf),
                                 "cannot call method '%s' on Dynamic value; "
                                 "use 'ref x : Type = ...' to declare with an explicit type first",
                                 method->c_str);
                    } else {
                        snprintf(buf, sizeof(buf), "no method '%s' for type '%s'",
                                 method->c_str, type_name ? type_name->c_str : "unknown");
                    }
                    type_error(e, buf);
                    e->til_type = TIL_TYPE_UNKNOWN;
                    break;
                }
                // Desugar: rewrite AST to Type.method(instance, args)
                Expr *instance = obj;
                Expr *type_ident = expr_new(NODE_IDENT, obj->line, obj->col, obj->path);
                type_ident->data.str_val = type_name;
                expr_child(fa, 0) = type_ident;
                // Insert instance as first arg
                Expr *dummy = NULL;
                Vec_push(&e->children, &dummy);
                memmove(&expr_child(e, 2), &expr_child(e, 1), (e->children.count - 2) * sizeof(Expr *));
                expr_child(e, 1) = instance;
                // Fall through -- existing code below handles Type.method(instance, args)
            }

            // Type the (possibly new) object and look up namespace func
            obj = expr_child(fa, 0);
            if (obj->til_type == TIL_TYPE_UNKNOWN) {
                infer_expr(scope, obj, in_func);
            }
            Expr *sdef = obj->struct_name ? tscope_get_struct(scope, obj->struct_name) : NULL;
            Expr *ns_func = NULL;
            if (sdef) {
                Expr *body = expr_child(sdef, 0);
                for (U32 i = 0; i < body->children.count; i++) {
                    Expr *field = expr_child(body, i);
                    if (field->data.decl.is_namespace &&
                        Str_eq(field->data.decl.name, method) &&
                        expr_child(field, 0)->type == NODE_FUNC_DEF) {
                        ns_func = expr_child(field, 0);
                        break;
                    }
                }
            }
            if (!ns_func) {
                char buf[128];
                snprintf(buf, sizeof(buf), "no namespace function '%s'", method->c_str);
                type_error(e, buf);
                e->til_type = TIL_TYPE_UNKNOWN;
                break;
            }
            fa->is_ns_field = true;
            // Desugar named/optional args for namespace methods
            {
                U32 np = ns_func->data.func_def.nparam;
                Expr **new_args = calloc(np, sizeof(Expr *));
                U32 pos_idx = 0;
                Bool seen_named = 0;
                for (U32 i = 1; i < e->children.count; i++) {
                    Expr *arg = expr_child(e, i);
                    if (arg->type == NODE_NAMED_ARG) {
                        seen_named = 1;
                        Str *aname = arg->data.str_val;
                        I32 slot = -1;
                        for (U32 j = 0; j < np; j++) {
                            if (Str_eq(ns_func->data.func_def.param_names[j], aname)) {
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
                            new_args[slot] = expr_child(arg, 0); // unwrap NODE_NAMED_ARG
                        }
                    } else {
                        if (seen_named) {
                            type_error(arg, "positional argument after named argument");
                        }
                        if (pos_idx < np) {
                            new_args[pos_idx] = arg;
                        }
                        pos_idx++;
                    }
                }
                // Fill defaults for missing args
                for (U32 i = 0; i < np; i++) {
                    if (!new_args[i]) {
                        if (ns_func->data.func_def.param_defaults &&
                            ns_func->data.func_def.param_defaults[i]) {
                            new_args[i] = expr_clone(ns_func->data.func_def.param_defaults[i]);
                        } else {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "missing argument for parameter '%s'",
                                     ns_func->data.func_def.param_names[i]->c_str);
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
                Vec new_ch = Vec_new(sizeof(Expr *));
                Expr *callee = expr_child(e, 0);
                Vec_push(&new_ch, &callee);
                for (U32 i = 0; i < np; i++)
                    Vec_push(&new_ch, &new_args[i]);
                Vec_delete(&e->children);
                e->children = new_ch;
                free(new_args);
            }
            // Infer arg types
            for (U32 i = 1; i < e->children.count; i++) {
                infer_expr(scope, expr_child(e, i), in_func);
            }
            // Narrow Dynamic args to parameter types
            for (U32 i = 1; i < e->children.count && i - 1 < ns_func->data.func_def.nparam; i++) {
                Str *ptype = ns_func->data.func_def.param_types[i - 1];
                if (ptype)
                    narrow_dynamic(expr_child(e, i), type_from_name(ptype, scope), ptype);
            }
            // Validate arg types against param types
            for (U32 i = 1; i < e->children.count && i - 1 < ns_func->data.func_def.nparam; i++) {
                Str *ptype_name = ns_func->data.func_def.param_types[i - 1];
                if (!ptype_name) continue;
                Expr *arg = expr_child(e, i);
                if (arg->til_type == TIL_TYPE_DYNAMIC) continue;
                TilType ptype = type_from_name(ptype_name, scope);
                if (ptype == TIL_TYPE_DYNAMIC) continue;
                if (arg->type == NODE_LITERAL_NUM && (ptype == TIL_TYPE_I64 || ptype == TIL_TYPE_U8 || ptype == TIL_TYPE_I16 || ptype == TIL_TYPE_I32 || ptype == TIL_TYPE_U32))
                    continue;
                if (arg->til_type != ptype) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             ns_func->data.func_def.param_names[i - 1]->c_str,
                             ptype_name->c_str, til_type_name_c(arg->til_type));
                    type_error(arg, buf);
                } else if ((ptype == TIL_TYPE_STRUCT || ptype == TIL_TYPE_ENUM) &&
                           arg->struct_name && !Str_eq(ptype_name, arg->struct_name)) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             ns_func->data.func_def.param_names[i - 1]->c_str,
                             ptype_name->c_str, arg->struct_name->c_str);
                    type_error(arg, buf);
                }
            }
            // Validate 'own' markers on arguments
            {
                bool *po = ns_func->data.func_def.param_owns;
                if (po) {
                    U32 np = ns_func->data.func_def.nparam;
                    for (U32 i = 1; i < e->children.count && i - 1 < np; i++) {
                        Bool pown = po[i - 1];
                        if (pown && !expr_child(e, i)->is_own_arg) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "argument for 'own' parameter '%s' must be marked 'own'",
                                     ns_func->data.func_def.param_names[i - 1]->c_str);
                            type_error(expr_child(e, i), buf);
                        } else if (!pown && expr_child(e, i)->is_own_arg) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                                     ns_func->data.func_def.param_names[i - 1]->c_str);
                            type_error(expr_child(e, i), buf);
                        }
                        if (pown && expr_child(e, i)->type == NODE_IDENT) {
                            TypeBinding *ab = tscope_find(scope, expr_child(e, i)->data.str_val);
                            if (ab && ab->is_ref) type_error(expr_child(e, i), "cannot pass ref variable to 'own' parameter");
                        }
                    }
                }
            }
            // Set return type
            TilType rt = TIL_TYPE_NONE;
            if (ns_func->data.func_def.return_type) {
                rt = type_from_name(ns_func->data.func_def.return_type, scope);
            }
            e->til_type = rt;
            if ((rt == TIL_TYPE_STRUCT || rt == TIL_TYPE_ENUM) && ns_func->data.func_def.return_type) {
                e->struct_name = ns_func->data.func_def.return_type;
            }
            break;
        }
        regular_call:;
        // Resolve callee
        Str *name = expr_child(e, 0)->data.str_val;
        // Struct instantiation: Point() or Point(x=1, y=2)
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) {
            TypeBinding *sb = tscope_find(scope, name);
            if (sb && sb->is_builtin && !sb->is_ext) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot instantiate builtin type '%s'", name->c_str);
                type_error(e, buf);
                e->til_type = TIL_TYPE_UNKNOWN;
                break;
            }
            Expr *body = expr_child(sdef, 0);
            // Count instance fields (skip namespace)
            U32 nfields = 0;
            for (U32 i = 0; i < body->children.count; i++) {
                if (!expr_child(body, i)->data.decl.is_namespace) nfields++;
            }
            // Desugar named args into positional (one per instance field)
            Expr **field_vals = calloc(nfields, sizeof(Expr *));
            // Map: field_idx[k] = index into body->children for k-th instance field
            I32 *field_idx = malloc(nfields * sizeof(I32));
            { I32 k = 0;
              for (U32 i = 0; i < body->children.count; i++) {
                  if (!expr_child(body, i)->data.decl.is_namespace) field_idx[k++] = i;
              }
            }
            for (U32 i = 1; i < e->children.count; i++) {
                Expr *arg = expr_child(e, i);
                if (arg->type != NODE_NAMED_ARG) {
                    type_error(arg, "struct instantiation requires named arguments");
                    continue;
                }
                Str *aname = arg->data.str_val;
                I32 slot = -1;
                for (U32 j = 0; j < nfields; j++) {
                    if (Str_eq(expr_child(body, field_idx[j])->data.decl.name, aname)) {
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
                    field_vals[slot] = expr_child(arg, 0); // unwrap NODE_NAMED_ARG
                }
            }
            // Fill remaining from struct field defaults (clone to avoid shared ownership)
            for (U32 i = 0; i < nfields; i++) {
                if (!field_vals[i]) {
                    field_vals[i] = expr_clone(expr_child(expr_child(body, field_idx[i]), 0));
                }
            }
            // Rebuild children: callee + instance field values
            Vec new_ch = Vec_new(sizeof(Expr *));
            Expr *callee = expr_child(e, 0);
            Vec_push(&new_ch, &callee);
            for (U32 i = 0; i < nfields; i++)
                Vec_push(&new_ch, &field_vals[i]);
            Vec_delete(&e->children);
            e->children = new_ch;
            free(field_vals);
            free(field_idx);
            // Type-check args (skip already-inferred defaults)
            for (U32 i = 1; i < e->children.count; i++) {
                if (expr_child(e, i)->til_type == TIL_TYPE_UNKNOWN) {
                    infer_expr(scope, expr_child(e, i), in_func);
                }
            }
            // Auto-insert clone for constructor args that are identifiers
            // Skip clone for `own` fields — use move semantics instead
            { U32 fi = 0;
              for (U32 bi = 0; bi < body->children.count && fi < e->children.count - 1; bi++) {
                Expr *fld = expr_child(body, bi);
                if (fld->data.decl.is_namespace) continue;
                I32 ai = fi + 1; // arg index (children[0] is callee)
                fi++;
                if (fld->data.decl.is_own) {
                    // own field: mark for move, don't clone
                    if (expr_child(e, ai)->type == NODE_IDENT)
                        expr_child(e, ai)->is_own_arg = 1;
                    continue;
                }
                if (expr_child(e, ai)->type == NODE_IDENT) {
                    const char *tname = type_to_name(expr_child(e, ai)->til_type,
                                                      expr_child(e, ai)->struct_name);
                    if (tname) {
                        expr_child(e, ai) = make_clone_call(tname,
                            expr_child(e, ai)->til_type, expr_child(e, ai),
                            expr_child(e, ai));
                    }
                }
              }
            }
            e->til_type = TIL_TYPE_STRUCT;
            e->struct_name = name;
            break;
        }
        // Desugar named/optional args for user-defined functions (skip core builtins)
        TypeBinding *callee_bind = tscope_find(scope, name);
        if (callee_bind && callee_bind->func_def &&
            (!callee_bind->is_builtin || !callee_bind->func_def->is_core)) {
            Expr *fdef = callee_bind->func_def;
            U32 nparam = fdef->data.func_def.nparam;
            I32 vi = fdef->data.func_def.variadic_index; // -1 if not variadic
            U32 fixed_count = (vi >= 0) ? (U32)vi : nparam; // params before variadic
            // Collect positional and named args
            Vec va_args = Vec_new(sizeof(Expr *)); // variadic args (only if vi >= 0)
            Expr **new_args = calloc(nparam, sizeof(Expr *));
            U32 pos_idx = 0;
            Bool seen_named = 0;
            for (U32 i = 1; i < e->children.count; i++) {
                Expr *arg = expr_child(e, i);
                if (arg->type == NODE_NAMED_ARG) {
                    seen_named = 1;
                    Str *aname = arg->data.str_val;
                    I32 slot = -1;
                    for (U32 j = 0; j < nparam; j++) {
                        if ((I32)j == vi) continue; // can't name the variadic param
                        if (Str_eq(fdef->data.func_def.param_names[j], aname)) {
                            slot = j;
                            break;
                        }
                    }
                    if (slot < 0) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' has no parameter '%s'", name->c_str, aname->c_str);
                        type_error(arg, buf);
                    } else if (new_args[slot]) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "duplicate argument for parameter '%s'", aname->c_str);
                        type_error(arg, buf);
                    } else {
                        new_args[slot] = expr_child(arg, 0); // unwrap NODE_NAMED_ARG
                    }
                } else {
                    if (seen_named) {
                        type_error(arg, "positional argument after named argument");
                    }
                    if (vi >= 0 && pos_idx >= fixed_count) {
                        // Variadic arg
                        Vec_push(&va_args, &arg);
                    } else if (pos_idx < nparam) {
                        new_args[pos_idx] = arg;
                    }
                    pos_idx++;
                }
            }
            // Fill defaults for missing non-variadic params
            for (U32 i = 0; i < nparam; i++) {
                if ((I32)i == vi) continue; // variadic param handled separately
                if (!new_args[i]) {
                    if (fdef->data.func_def.param_defaults &&
                        fdef->data.func_def.param_defaults[i]) {
                        new_args[i] = expr_clone(fdef->data.func_def.param_defaults[i]);
                    } else {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "missing argument for parameter '%s'",
                                 fdef->data.func_def.param_names[i]->c_str);
                        type_error(e, buf);
                    }
                }
            }
            if (vi < 0 && pos_idx > nparam) {
                char buf[128];
                snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d",
                         nparam, pos_idx);
                type_error(e, buf);
            }
            // Rebuild children: callee + args_before_variadic + variadic_args + args_after_variadic
            Vec new_ch = Vec_new(sizeof(Expr *));
            Expr *callee = expr_child(e, 0);
            Vec_push(&new_ch, &callee);
            for (U32 i = 0; i < nparam; i++) {
                if ((I32)i == vi) {
                    e->variadic_index = new_ch.count; // children index of first variadic arg
                    for (U32 j = 0; j < va_args.count; j++) {
                        Expr *va = *(Expr **)Vec_get(&va_args, j);
                        Vec_push(&new_ch, &va);
                    }
                    e->variadic_count = va_args.count;
                } else {
                    Vec_push(&new_ch, &new_args[i]);
                }
            }
            Vec_delete(&e->children);
            e->children = new_ch;
            free(new_args);
            Vec_delete(&va_args);
        }
        // Infer types of all arguments
        for (U32 i = 1; i < e->children.count; i++) {
            infer_expr(scope, expr_child(e, i), in_func);
        }
        // Narrow Dynamic args to parameter types, then validate arg types
        if (callee_bind && callee_bind->func_def) {
            Expr *fdef = callee_bind->func_def;
            I32 fvi = fdef->data.func_def.variadic_index;
            U32 fvc = (fvi >= 0) ? e->variadic_count : 0;
            U32 ci = 1;
            for (U32 pi = 0; pi < fdef->data.func_def.nparam && ci < e->children.count; pi++) {
                if (fvi >= 0 && (I32)pi == fvi) { ci += fvc; continue; }
                Str *ptype = fdef->data.func_def.param_types[pi];
                if (ptype)
                    narrow_dynamic(expr_child(e, ci), type_from_name(ptype, scope), ptype);
                ci++;
            }
            // Validate arg types against param types
            ci = 1;
            for (U32 pi = 0; pi < fdef->data.func_def.nparam && ci < e->children.count; pi++) {
                if (fvi >= 0 && (I32)pi == fvi) { ci += fvc; continue; }
                Str *ptype_name = fdef->data.func_def.param_types[pi];
                if (!ptype_name) { ci++; continue; }
                Expr *arg = expr_child(e, ci);
                if (arg->til_type == TIL_TYPE_DYNAMIC) { ci++; continue; }
                TilType ptype = type_from_name(ptype_name, scope);
                if (ptype == TIL_TYPE_DYNAMIC) { ci++; continue; }
                if (arg->type == NODE_LITERAL_NUM && (ptype == TIL_TYPE_I64 || ptype == TIL_TYPE_U8 || ptype == TIL_TYPE_I16 || ptype == TIL_TYPE_I32 || ptype == TIL_TYPE_U32))
                    { ci++; continue; }
                if (arg->til_type != ptype) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             fdef->data.func_def.param_names[pi]->c_str,
                             ptype_name->c_str, til_type_name_c(arg->til_type));
                    type_error(arg, buf);
                } else if ((ptype == TIL_TYPE_STRUCT || ptype == TIL_TYPE_ENUM) &&
                           arg->struct_name && !Str_eq(ptype_name, arg->struct_name)) {
                    char buf[256];
                    snprintf(buf, sizeof(buf), "argument type mismatch for '%s': expected %s, got %s",
                             fdef->data.func_def.param_names[pi]->c_str,
                             ptype_name->c_str, arg->struct_name->c_str);
                    type_error(arg, buf);
                }
                ci++;
            }
        }
        // dyn_call variants: method (2nd arg) must be a string literal
        if ((Str_eq_c(name, "dyn_call1") || Str_eq_c(name, "dyn_call2") ||
             Str_eq_c(name, "dyn_call1_ret") || Str_eq_c(name, "dyn_call2_ret") ||
             Str_eq_c(name, "dyn_has_method")) &&
            e->children.count >= 3) {
            Expr *method_arg = expr_child(e, 2);
            if (method_arg->type != NODE_LITERAL_STR) {
                type_error(method_arg, "dyn_call method argument must be a string literal");
            }
        }
        // array/vec builtins: type_name (1st arg) must be a string literal
        if ((Str_eq_c(name, "array") || Str_eq_c(name, "vec")) &&
            e->children.count >= 2) {
            Expr *type_arg = expr_child(e, 1);
            if (type_arg->type != NODE_LITERAL_STR) {
                type_error(type_arg, "array/vec type_name argument must be a string literal");
            }
        }
        // Validate 'own' markers on arguments (variadic-aware)
        if (callee_bind && callee_bind->func_def) {
            Expr *fdef = callee_bind->func_def;
            bool *po = fdef->data.func_def.param_owns;
            I32 fvi = fdef->data.func_def.variadic_index;
            U32 fvc = (fvi >= 0) ? e->variadic_count : 0;
            U32 ci = 1; // children index
            for (U32 pi = 0; pi < fdef->data.func_def.nparam && ci < e->children.count; pi++) {
                if (fvi >= 0 && (I32)pi == fvi) {
                    ci += fvc; // skip variadic args
                    continue;
                }
                Bool pown = po ? po[pi] : 0;
                if (pown && !expr_child(e, ci)->is_own_arg) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "argument for 'own' parameter '%s' must be marked 'own'",
                             fdef->data.func_def.param_names[pi]->c_str);
                    type_error(expr_child(e, ci), buf);
                } else if (!pown && expr_child(e, ci)->is_own_arg) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                             fdef->data.func_def.param_names[pi]->c_str);
                    type_error(expr_child(e, ci), buf);
                }
                if (pown && expr_child(e, ci)->type == NODE_IDENT) {
                    TypeBinding *ab = tscope_find(scope, expr_child(e, ci)->data.str_val);
                    if (ab && ab->is_ref) type_error(expr_child(e, ci), "cannot pass ref variable to 'own' parameter");
                }
                ci++;
            }
        }
        // Resolve return type from scope (covers builtins and user-defined)
        TilType fn_type = tscope_get(scope, name);
        if (fn_type == TIL_TYPE_UNKNOWN) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined function '%s'", name->c_str);
            type_error(e, buf);
        }
        e->til_type = fn_type;
        // Propagate struct_name for struct-returning functions
        if ((fn_type == TIL_TYPE_STRUCT || fn_type == TIL_TYPE_ENUM) && callee_bind && callee_bind->func_def &&
            callee_bind->func_def->data.func_def.return_type) {
            e->struct_name = callee_bind->func_def->data.func_def.return_type;
        }
        // Check: func cannot call proc (panic is exempt; print/println exempt in debug_prints modes)
        Bool debug_exempt = current_mode && current_mode->debug_prints &&
            (Str_eq_c(name, "print") || Str_eq_c(name, "println"));
        if (in_func && tscope_is_proc(scope, name) == 1 && !Str_eq_c(name, "panic") && !debug_exempt) {
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
        break;
    }
    case NODE_FIELD_ACCESS: {
        infer_expr(scope, expr_child(e, 0), in_func);
        Expr *obj = expr_child(e, 0);
        if (obj->struct_name) {
            Expr *sdef = tscope_get_struct(scope, obj->struct_name);
            if (sdef) {
                Expr *body = expr_child(sdef, 0);
                Str *fname = e->data.str_val;
                Bool found = 0;
                for (U32 i = 0; i < body->children.count; i++) {
                    Expr *field = expr_child(body, i);
                    // Skip variant registry entries (non-namespace) in enum bodies
                    if (sdef->type == NODE_ENUM_DEF && !field->data.decl.is_namespace)
                        continue;
                    if (Str_eq(field->data.decl.name, fname)) {
                        e->til_type = field->til_type;
                        e->is_ns_field = field->data.decl.is_namespace;
                        e->is_own_field = field->data.decl.is_own;
                        if (field->til_type == TIL_TYPE_STRUCT || field->til_type == TIL_TYPE_ENUM) {
                            e->struct_name = expr_child(field, 0)->struct_name;
                        } else {
                            e->struct_name = obj->struct_name;
                        }
                        // Enum variant access: override type to enum for:
                        // 1. I64 literal variants (simple enums)
                        // 2. Zero-arg ext_func constructors (no-payload in payload enums)
                        if (sdef->type == NODE_ENUM_DEF &&
                            field->data.decl.is_namespace &&
                            field->children.count > 0) {
                            Expr *fc = expr_child(field, 0);
                            if (fc->type != NODE_FUNC_DEF) {
                                // I64 literal variant
                                e->til_type = TIL_TYPE_ENUM;
                                e->struct_name = obj->struct_name;
                            } else if (fc->data.func_def.func_type == FUNC_EXT_FUNC &&
                                       fc->data.func_def.nparam == 0 &&
                                       fc->data.func_def.return_type &&
                                       Str_eq(fc->data.func_def.return_type, obj->struct_name)) {
                                // Zero-arg ext_func constructor (auto-callable)
                                e->til_type = TIL_TYPE_ENUM;
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
                             sdef->type == NODE_ENUM_DEF ? "enum" : "struct",
                             obj->struct_name->c_str, fname->c_str);
                    type_error(e, buf);
                    e->til_type = TIL_TYPE_UNKNOWN;
                }
            }
        } else {
            type_error(e, "field access on non-struct value");
            e->til_type = TIL_TYPE_UNKNOWN;
        }
        break;
    }
    default:
        e->til_type = TIL_TYPE_UNKNOWN;
        break;
    }
}

// --- Variadic call desugaring ---
// Transforms variadic function calls into Array.new + Array.set + normal call.
// Must run before hoisting so that synthetic Array calls get hoisted too.

static Expr *find_variadic_fcall(Expr *e) {
    if (!e) return NULL;
    if (e->type == NODE_FUNC_DEF || e->type == NODE_STRUCT_DEF ||
        e->type == NODE_ENUM_DEF || e->type == NODE_BODY) return NULL;
    if (e->type == NODE_FCALL && e->variadic_index >= 0) {
        // Skip array/vec builtins — handled specially like dyn_call
        if (expr_child(e, 0)->type == NODE_IDENT) {
            Str *cn = expr_child(e, 0)->data.str_val;
            if (Str_eq_c(cn, "array") || Str_eq_c(cn, "vec")) return NULL;
        }
        return e;
    }
    for (U32 i = 0; i < e->children.count; i++) {
        Expr *found = find_variadic_fcall(expr_child(e, i));
        if (found) return found;
    }
    return NULL;
}

// Create a namespace method call: StructName.method(args...)
static Expr *make_ns_call(const char *sname, const char *method,
                           TilType ret_type, Str *ret_sname, Expr *src) {
    I32 line = src->line, col = src->col;
    Str *path = src->path;
    Expr *call = expr_new(NODE_FCALL, line, col, path);
    call->til_type = ret_type;
    call->struct_name = ret_sname;
    Expr *type_id = expr_new(NODE_IDENT, line, col, path);
    type_id->data.str_val = Str_new(sname);
    type_id->struct_name = Str_new(sname);
    Expr *fa = expr_new(NODE_FIELD_ACCESS, line, col, path);
    fa->data.str_val = Str_new(method);
    fa->is_ns_field = true;
    expr_add_child(fa, type_id);
    expr_add_child(call, fa);
    return call;
}

static I32 _va_counter = 0;

static void desugar_variadic_calls(Expr *body, TypeScope *scope) {
    Vec new_ch = Vec_new(sizeof(Expr *));
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);
        Expr *fcall = find_variadic_fcall(stmt);
        if (!fcall) {
            Vec_push(&new_ch, &stmt);
            continue;
        }
        changed = 1;
        I32 vi = fcall->variadic_index;
        U32 vc = fcall->variadic_count;
        I32 line = fcall->line, col = fcall->col;
        Str *path = fcall->path;

        // Find element type from func_def
        Str *elem_type = NULL;
        Expr *callee = expr_child(fcall, 0);
        if (callee->type == NODE_IDENT) {
            TypeBinding *tb = tscope_find(scope, callee->data.str_val);
            if (tb && tb->func_def) {
                I32 fvi = tb->func_def->data.func_def.variadic_index;
                if (fvi >= 0)
                    elem_type = tb->func_def->data.func_def.param_types[fvi];
            }
        } else if (callee->type == NODE_FIELD_ACCESS && callee->is_ns_field) {
            Expr *type_node = expr_child(callee, 0);
            if (type_node->type == NODE_IDENT) {
                Expr *sdef = tscope_get_struct(scope, type_node->data.str_val);
                if (sdef) {
                    Expr *sbody = expr_child(sdef, 0);
                    for (U32 j = 0; j < sbody->children.count; j++) {
                        Expr *f = expr_child(sbody, j);
                        if (f->type == NODE_DECL && f->data.decl.is_namespace &&
                            Str_eq(f->data.decl.name, callee->data.str_val) &&
                            expr_child(f, 0)->type == NODE_FUNC_DEF) {
                            I32 fvi = expr_child(f, 0)->data.func_def.variadic_index;
                            if (fvi >= 0)
                                elem_type = expr_child(f, 0)->data.func_def.param_types[fvi];
                            break;
                        }
                    }
                }
            }
        }
        if (!elem_type) {
            Vec_push(&new_ch, &stmt);
            continue;
        }

        // Create temp variable name
        char buf[32];
        snprintf(buf, sizeof(buf), "_va%d", _va_counter++);
        Str *va_name = Str_new(buf);

        // 1. _va := Array.new(elem_type_str, ElemType.size(), count)
        Expr *new_call = make_ns_call("Array", "new", TIL_TYPE_STRUCT,
                                       Str_new("Array"), fcall);
        // Arg: elem_type string
        Expr *et = expr_new(NODE_LITERAL_STR, line, col, path);
        et->data.str_val = Str_new(elem_type->c_str);
        et->til_type = TIL_TYPE_STRUCT;
        et->struct_name = Str_new("Str");
        expr_add_child(new_call, et);
        // Arg: ElemType.size()
        Expr *sz = make_ns_call(elem_type->c_str, "size", TIL_TYPE_I64,
                                 NULL, fcall);
        expr_add_child(new_call, sz);
        // Arg: count
        Expr *cap = expr_new(NODE_LITERAL_NUM, line, col, path);
        char cap_buf[16];
        snprintf(cap_buf, sizeof(cap_buf), "%d", vc);
        cap->data.str_val = Str_new(cap_buf);
        cap->til_type = TIL_TYPE_I64;
        expr_add_child(new_call, cap);

        // DECL _va := Array.new(...)
        Expr *va_decl = expr_new(NODE_DECL, line, col, path);
        va_decl->data.decl.name = va_name;
        va_decl->til_type = TIL_TYPE_STRUCT;
        expr_add_child(va_decl, new_call);

        // Register _va in scope
        tscope_set(scope, va_name, TIL_TYPE_STRUCT, -1, 0, line, col, 0, 0);
        TypeBinding *vab = tscope_find(scope, va_name);
        if (vab) vab->struct_name = Str_new("Array");

        Vec_push(&new_ch, &va_decl);

        // 2. Array.set calls for each variadic arg
        for (U32 j = 0; j < vc; j++) {
            Expr *set_call = make_ns_call("Array", "set", TIL_TYPE_NONE,
                                           NULL, fcall);
            // Arg: self = _va
            Expr *self_id = expr_new(NODE_IDENT, line, col, path);
            self_id->data.str_val = va_name;
            self_id->til_type = TIL_TYPE_STRUCT;
            self_id->struct_name = Str_new("Array");
            expr_add_child(set_call, self_id);
            // Arg: index
            Expr *idx = expr_new(NODE_LITERAL_NUM, line, col, path);
            char idx_buf[16];
            snprintf(idx_buf, sizeof(idx_buf), "%d", j);
            idx->data.str_val = Str_new(idx_buf);
            idx->til_type = TIL_TYPE_I64;
            expr_add_child(set_call, idx);
            // Arg: val — clone if NODE_IDENT to preserve caller's variable
            Expr *val = expr_child(fcall, vi + j);
            if (val->type == NODE_IDENT) {
                const char *tname = type_to_name(val->til_type, val->struct_name);
                if (tname)
                    val = make_clone_call(tname, val->til_type, val, val);
            }
            val->is_own_arg = true;
            expr_add_child(set_call, val);

            Vec_push(&new_ch, &set_call);
        }

        // 3. Replace variadic args in FCALL with _va ident
        Vec fcall_new_ch = Vec_new(sizeof(Expr *));
        Bool va_inserted = 0;
        for (U32 j = 0; j < fcall->children.count; j++) {
            if ((I32)j >= vi && (I32)j < vi + (I32)vc) {
                if (!va_inserted) {
                    Expr *va_id = expr_new(NODE_IDENT, line, col, path);
                    va_id->data.str_val = va_name;
                    va_id->til_type = TIL_TYPE_STRUCT;
                    va_id->struct_name = Str_new("Array");
                    va_id->is_own_arg = true;
                    Vec_push(&fcall_new_ch, &va_id);
                    va_inserted = 1;
                }
                continue;
            }
            // Insert _va before post-variadic args when vc==0
            if ((I32)j == vi && !va_inserted) {
                Expr *va_id = expr_new(NODE_IDENT, line, col, path);
                va_id->data.str_val = va_name;
                va_id->til_type = TIL_TYPE_STRUCT;
                va_id->struct_name = Str_new("Array");
                va_id->is_own_arg = true;
                Vec_push(&fcall_new_ch, &va_id);
                va_inserted = 1;
            }
            Expr *ch = expr_child(fcall, j);
            Vec_push(&fcall_new_ch, &ch);
        }
        // Insert _va at end if variadic was last param and vc==0
        if (!va_inserted) {
            Expr *va_id = expr_new(NODE_IDENT, line, col, path);
            va_id->data.str_val = va_name;
            va_id->til_type = TIL_TYPE_STRUCT;
            va_id->struct_name = Str_new("Array");
            va_id->is_own_arg = true;
            Vec_push(&fcall_new_ch, &va_id);
        }
        Vec_delete(&fcall->children);
        fcall->children = fcall_new_ch;
        fcall->variadic_index = -1;
        fcall->variadic_count = 0;

        // Insert the original statement
        Vec_push(&new_ch, &stmt);
    }

    if (changed) {
        Vec_delete(&body->children);
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch);
    }
}

// --- Argument hoisting ---

static Bool expr_contains_fcall(Expr *e) {
    if (e->type == NODE_FCALL) return 1;
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_contains_fcall(expr_child(e, i))) return 1;
    }
    return 0;
}

// Check if a function call returns ref
static I32 fcall_returns_ref(Expr *fcall, TypeScope *scope) {
    if (fcall->type != NODE_FCALL) return 0;
    Expr *callee = expr_child(fcall, 0);
    if (callee->type == NODE_IDENT) {
        TypeBinding *cb = tscope_find(scope, callee->data.str_val);
        return (cb && cb->func_def) ? cb->func_def->data.func_def.return_is_ref : 0;
    }
    if (callee->type == NODE_FIELD_ACCESS && callee->is_ns_field) {
        Expr *sdef = tscope_get_struct(scope, expr_child(callee, 0)->data.str_val);
        if (!sdef) return 0;
        Expr *body = expr_child(sdef, 0);
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *f = expr_child(body, j);
            if (f->type == NODE_DECL && f->data.decl.is_namespace &&
                Str_eq(f->data.decl.name, callee->data.str_val) &&
                expr_child(f, 0)->type == NODE_FUNC_DEF)
                return expr_child(f, 0)->data.func_def.return_is_ref;
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
    Str *tname = Str_new(name_buf);
    Expr *decl = expr_new(NODE_DECL, val->line, val->col, val->path);
    decl->data.decl.name = tname;
    decl->data.decl.explicit_type = NULL;
    decl->data.decl.is_mut = false;
    decl->data.decl.is_namespace = false;
    decl->til_type = val->til_type;
    expr_add_child(decl, val);
    Expr *ident = expr_new(NODE_IDENT, val->line, val->col, val->path);
    ident->data.str_val = tname;
    ident->til_type = val->til_type;
    ident->struct_name = val->struct_name;
    ident->is_own_arg = val->is_own_arg;
    tscope_set(scope, tname, val->til_type, -1, 0, val->line, val->col, 0, 0);
    TypeBinding *tb = tscope_find(scope, tname);
    if (tb) tb->struct_name = val->struct_name;
    if (val->type == NODE_FCALL && fcall_returns_ref(val, scope)) {
        decl->data.decl.is_ref = true;
        if (tb) tb->is_ref = 1;
    }
    if (*nhoisted >= *cap) {
        *cap = *cap ? *cap * 2 : 8;
        *hoisted = realloc(*hoisted, *cap * sizeof(Expr *));
    }
    (*hoisted)[(*nhoisted)++] = decl;
    return ident;
}

// Walk expression tree depth-first. For each NODE_FCALL, hoist any arg that is itself a NODE_FCALL.
// Does NOT recurse into scope boundaries (func/struct defs, bodies).
static void hoist_expr(Expr *e, Expr ***hoisted, U32 *nhoisted, U32 *cap, TypeScope *scope) {
    // Don't recurse into scope boundaries -- those have their own infer_body calls
    if (e->type == NODE_FUNC_DEF || e->type == NODE_STRUCT_DEF || e->type == NODE_ENUM_DEF || e->type == NODE_BODY) return;
    // Recurse into children first (depth-first: inner fcalls hoisted before outer)
    for (U32 i = 0; i < e->children.count; i++) {
        hoist_expr(expr_child(e, i), hoisted, nhoisted, cap, scope);
    }
    if (e->type != NODE_FCALL) return;

    // For struct constructors, find field info to skip hoisting inline compound args
    Expr *ctor_body = NULL;
    if (e->struct_name && e->children.count > 0 &&
        Str_eq(expr_child(e, 0)->data.str_val, e->struct_name)) {
        Expr *sdef = tscope_get_struct(scope, e->struct_name);
        if (sdef) ctor_body = expr_child(sdef, 0);
    }

    // Check each argument (children[1..n])
    // dyn_call variants: don't hoist the method arg (2nd) — codegen needs it as a literal
    Bool is_dyn_call = 0;
    if (expr_child(e, 0)->type == NODE_IDENT) {
        Str *cn = expr_child(e, 0)->data.str_val;
        is_dyn_call = Str_eq_c(cn, "dyn_call1") || Str_eq_c(cn, "dyn_call2") ||
                      Str_eq_c(cn, "dyn_call1_ret") || Str_eq_c(cn, "dyn_call2_ret") ||
                      Str_eq_c(cn, "dyn_has_method");
    }
    Bool is_array_vec = 0;
    if (expr_child(e, 0)->type == NODE_IDENT) {
        Str *cn = expr_child(e, 0)->data.str_val;
        is_array_vec = Str_eq_c(cn, "array") || Str_eq_c(cn, "vec");
    }
    U32 fi = 0; // instance field index for struct constructors
    for (U32 i = 1; i < e->children.count; i++) {
        if (is_dyn_call && i == 2) continue; // keep method as NODE_LITERAL_STR
        if (is_array_vec && i == 1) continue; // keep type_name as NODE_LITERAL_STR
        if (expr_child(e, i)->type != NODE_FCALL &&
            expr_child(e, i)->type != NODE_LITERAL_NUM &&
            expr_child(e, i)->type != NODE_LITERAL_STR &&
            expr_child(e, i)->type != NODE_LITERAL_BOOL) continue;

        // Skip hoisting inline compound field args in struct constructors
        if (ctor_body) {
            // Find the fi-th instance field
            Bool is_own = 0;
            TilType ft = TIL_TYPE_NONE;
            for (; fi < ctor_body->children.count; fi++) {
                Expr *field = expr_child(ctor_body, fi);
                if (!field->data.decl.is_namespace) {
                    is_own = field->data.decl.is_own;
                    ft = expr_child(field, 0)->til_type;
                    fi++;
                    break;
                }
            }
            if (!is_own && (ft == TIL_TYPE_STRUCT || ft == TIL_TYPE_ENUM))
                continue; // don't hoist — ccodegen handles directly
        }

        expr_child(e, i) = hoist_to_temp(expr_child(e, i), hoisted, nhoisted, cap, scope);
    }
}

static void hoist_fcall_args(Expr *body, TypeScope *scope) {
    Vec new_ch = Vec_new(sizeof(Expr *));
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);
        // Collect hoisted decls from this statement
        Expr **hoisted = NULL;
        U32 nhoisted = 0, hcap = 0;
        // Walk the appropriate expression tree based on statement type
        switch (stmt->type) {
        case NODE_DECL:
            hoist_expr(expr_child(stmt, 0), &hoisted, &nhoisted, &hcap, scope);
            break;
        case NODE_FCALL:
            hoist_expr(stmt, &hoisted, &nhoisted, &hcap, scope);
            if (stmt->til_type != TIL_TYPE_NONE) {
                hoist_to_temp(stmt, &hoisted, &nhoisted, &hcap, scope);
                stmt = hoisted[--nhoisted];
                expr_child(body, i) = stmt;
            }
            break;
        case NODE_RETURN:
            if (stmt->children.count > 0) {
                hoist_expr(expr_child(stmt, 0), &hoisted, &nhoisted, &hcap, scope);
                if (expr_child(stmt, 0)->type == NODE_FCALL ||
                    expr_child(stmt, 0)->type == NODE_LITERAL_NUM ||
                    expr_child(stmt, 0)->type == NODE_LITERAL_STR ||
                    expr_child(stmt, 0)->type == NODE_LITERAL_BOOL) {
                    expr_child(stmt, 0) = hoist_to_temp(expr_child(stmt, 0), &hoisted, &nhoisted, &hcap, scope);
                }
            }
            break;
        case NODE_ASSIGN: {
            hoist_expr(expr_child(stmt, 0), &hoisted, &nhoisted, &hcap, scope);
            // Skip top-level hoisting for compound-type locals — ccodegen
            // uses pointer-assign (typer inserts delete before reassignment).
            // Keep hoisting for scalars (deref-assign) and params (write-through).
            Bool do_hoist = 1;
            TypeBinding *ab = tscope_find(scope, stmt->data.str_val);
            if (ab && !ab->is_param) {
                TilType t = ab->type;
                if (t == TIL_TYPE_STRUCT || t == TIL_TYPE_ENUM)
                    do_hoist = 0;
            }
            if (do_hoist && (expr_child(stmt, 0)->type == NODE_FCALL ||
                expr_child(stmt, 0)->type == NODE_LITERAL_NUM ||
                expr_child(stmt, 0)->type == NODE_LITERAL_STR ||
                expr_child(stmt, 0)->type == NODE_LITERAL_BOOL)) {
                expr_child(stmt, 0) = hoist_to_temp(expr_child(stmt, 0), &hoisted, &nhoisted, &hcap, scope);
            }
            break;
        }
        case NODE_FIELD_ASSIGN: {
            hoist_expr(expr_child(stmt, 1), &hoisted, &nhoisted, &hcap, scope);
            // Skip hoisting for inline compound fields (same as constructor args)
            Bool fa_hoist = 1;
            if (!stmt->is_own_field) {
                TilType ft = expr_child(stmt, 1)->til_type;
                if (ft == TIL_TYPE_STRUCT || ft == TIL_TYPE_ENUM)
                    fa_hoist = 0;
            }
            if (fa_hoist && (expr_child(stmt, 1)->type == NODE_FCALL ||
                expr_child(stmt, 1)->type == NODE_LITERAL_NUM ||
                expr_child(stmt, 1)->type == NODE_LITERAL_STR ||
                expr_child(stmt, 1)->type == NODE_LITERAL_BOOL)) {
                expr_child(stmt, 1) = hoist_to_temp(expr_child(stmt, 1), &hoisted, &nhoisted, &hcap, scope);
            }
            break;
        }
        case NODE_IF:
            hoist_expr(expr_child(stmt, 0), &hoisted, &nhoisted, &hcap, scope);
            if (expr_child(stmt, 0)->type == NODE_FCALL) {
                expr_child(stmt, 0) = hoist_to_temp(expr_child(stmt, 0), &hoisted, &nhoisted, &hcap, scope);
            }
            break;
        // NODE_WHILE: skip condition -- hoisting changes loop semantics
        default: break;
        }
        // Insert hoisted decls before the statement
        for (U32 j = 0; j < nhoisted; j++)
            Vec_push(&new_ch, &hoisted[j]);
        free(hoisted);
        // Add original statement
        Vec_push(&new_ch, &stmt);
    }
    if (new_ch.count != body->children.count) {
        Vec_delete(&body->children);
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch);
    }
}

// --- Delete call insertion ---

static const char *type_to_name(TilType type, Str *struct_name) {
    if (struct_name) return struct_name->c_str;
    switch (type) {
        case TIL_TYPE_I64:  return "I64";
        case TIL_TYPE_U8:   return "U8";
        case TIL_TYPE_I16:  return "I16";
        case TIL_TYPE_I32:  return "I32";
        case TIL_TYPE_U32:  return "U32";
        case TIL_TYPE_BOOL: return "Bool";
        default: return NULL;
    }
}

static Expr *make_delete_call(Str *var_name, TilType type, Str *struct_name, Expr *src) {
    const char *tname = type_to_name(type, struct_name);
    if (!tname) return NULL;
    I32 line = src->line, col = src->col;
    Str *path = src->path;

    Expr *call = expr_new(NODE_FCALL, line, col, path);
    call->til_type = TIL_TYPE_NONE;

    Expr *type_id = expr_new(NODE_IDENT, line, col, path);
    type_id->data.str_val = Str_new(tname);
    type_id->struct_name = Str_new(tname);

    Expr *fa = expr_new(NODE_FIELD_ACCESS, line, col, path);
    fa->data.str_val = Str_new("delete");
    fa->is_ns_field = true;
    expr_add_child(fa, type_id);
    expr_add_child(call, fa);

    Expr *arg = expr_new(NODE_IDENT, line, col, path);
    arg->data.str_val = var_name;
    arg->til_type = type;
    arg->struct_name = struct_name;
    arg->is_own_arg = true;
    expr_add_child(call, arg);

    // call_free=true (ASAP delete should free the top-level allocation)
    Expr *true_lit = expr_new(NODE_LITERAL_BOOL, line, col, path);
    true_lit->data.str_val = Str_new("true");
    true_lit->til_type = TIL_TYPE_BOOL;
    expr_add_child(call, true_lit);

    return call;
}

// Build Type.delete(obj.field, call_free) for field reassignment.
// is_own: true for own (pointer) fields, false for inline (value) fields.
static Expr *make_field_delete(Expr *field_assign, Bool is_own) {
    Expr *rhs = expr_child(field_assign, 1);
    const char *tname = type_to_name(rhs->til_type, rhs->struct_name);
    if (!tname) return NULL;
    I32 line = field_assign->line, col = field_assign->col;
    Str *path = field_assign->path;

    Expr *call = expr_new(NODE_FCALL, line, col, path);
    call->til_type = TIL_TYPE_NONE;

    Expr *type_id = expr_new(NODE_IDENT, line, col, path);
    type_id->data.str_val = Str_new(tname);
    type_id->struct_name = Str_new(tname);

    Expr *fa = expr_new(NODE_FIELD_ACCESS, line, col, path);
    fa->data.str_val = Str_new("delete");
    fa->is_ns_field = true;
    expr_add_child(fa, type_id);
    expr_add_child(call, fa);

    // arg: obj.field_name (clone the obj expr, build field access)
    Expr *field_acc = expr_new(NODE_FIELD_ACCESS, line, col, path);
    field_acc->data.str_val = field_assign->data.str_val;
    field_acc->is_own_field = is_own;
    field_acc->til_type = rhs->til_type;
    field_acc->struct_name = rhs->struct_name;
    expr_add_child(field_acc, expr_clone(expr_child(field_assign, 0)));
    expr_add_child(call, field_acc);

    Expr *cf_lit = expr_new(NODE_LITERAL_BOOL, line, col, path);
    cf_lit->data.str_val = Str_new(is_own ? "true" : "false");
    cf_lit->til_type = TIL_TYPE_BOOL;
    expr_add_child(call, cf_lit);

    return call;
}

// Insert delete calls before field reassignments (own and inline compound)
static void insert_field_deletes(Expr *body) {
    Vec new_ch = Vec_new(sizeof(Expr *));
    Bool changed = 0;

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);
        if (stmt->type == NODE_FIELD_ASSIGN) {
            Bool need_delete = 0;
            Bool is_own = stmt->is_own_field;
            if (is_own) {
                need_delete = 1;
            } else {
                TilType ft = expr_child(stmt, 1)->til_type;
                if (ft == TIL_TYPE_STRUCT || ft == TIL_TYPE_ENUM)
                    need_delete = 1;
            }
            if (need_delete) {
                Expr *del = make_field_delete(stmt, is_own);
                if (del) {
                    Vec_push(&new_ch, &del);
                    changed = 1;
                }
            }
        }
        Vec_push(&new_ch, &stmt);
    }
    if (changed) {
        Vec_delete(&body->children);
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch);
    }
}

static Expr *make_clone_call(const char *type_name, TilType type, Expr *arg, Expr *src) {
    I32 line = src->line, col = src->col;
    Str *path = src->path;

    Expr *call = expr_new(NODE_FCALL, line, col, path);
    call->til_type = type;
    call->struct_name = (type == TIL_TYPE_STRUCT || type == TIL_TYPE_ENUM) ? Str_new(type_name) : NULL;

    Expr *type_id = expr_new(NODE_IDENT, line, col, path);
    type_id->data.str_val = Str_new(type_name);
    type_id->struct_name = Str_new(type_name);

    Expr *fa = expr_new(NODE_FIELD_ACCESS, line, col, path);
    fa->data.str_val = Str_new("clone");
    fa->is_ns_field = true;
    expr_add_child(fa, type_id);
    expr_add_child(call, fa);

    expr_add_child(call, arg);
    return call;
}

static Bool expr_uses_var(Expr *e, Str *name) {
    if (e->type == NODE_FUNC_DEF) return 0;
    if (e->type == NODE_IDENT && Str_eq(e->data.str_val, name)) return 1;
    if (e->type == NODE_ASSIGN && Str_eq(e->data.str_val, name)) return 1;
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_uses_var(expr_child(e, i), name)) return 1;
    }
    return 0;
}

// Check if name is referenced inside any nested func/proc body in this subtree,
// excluding cases where the name is shadowed by a parameter of that function.
static Bool expr_used_in_nested_func(Expr *e, Str *name) {
    if (e->type == NODE_FUNC_DEF) {
        // Check if name is shadowed by a parameter
        for (U32 i = 0; i < e->data.func_def.nparam; i++) {
            if (Str_eq(e->data.func_def.param_names[i], name)) return 0;
        }
        // Not a param — recurse into body to find uses
        if (e->children.count > 0) return expr_uses_var(expr_child(e, 0), name);
        return 0;
    }
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_used_in_nested_func(expr_child(e, i), name)) return 1;
    }
    return 0;
}

static Bool expr_contains_decl(Expr *e, Str *name) {
    if (e->type == NODE_FUNC_DEF) return 0;
    if (e->type == NODE_DECL && Str_eq(e->data.decl.name, name)) return 1;
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_contains_decl(expr_child(e, i), name)) return 1;
    }
    return 0;
}

// Helper: given a func_def, check if var_name is passed to an own param
static Bool check_own_args(Expr *fdef, Expr *fcall, Str *var_name) {
    bool *po = fdef->data.func_def.param_owns;
    if (!po) return 0;
    U32 np = fdef->data.func_def.nparam;
    for (U32 i = 0; i < np && i + 1 < fcall->children.count; i++) {
        if (po[i] && expr_child(fcall, i + 1)->type == NODE_IDENT &&
            Str_eq(expr_child(fcall, i + 1)->data.str_val, var_name)) {
            return 1;
        }
    }
    return 0;
}

static Bool fcall_has_own_arg(Expr *fcall, Str *var_name, TypeScope *scope) {
    if (fcall->type != NODE_FCALL || fcall->children.count < 2) return 0;
    // Struct constructor: check if var is in an own field position
    if (fcall->struct_name && expr_child(fcall, 0)->type == NODE_IDENT &&
        Str_eq(expr_child(fcall, 0)->data.str_val, fcall->struct_name)) {
        Expr *sdef = tscope_get_struct(scope, fcall->struct_name);
        if (sdef) {
            Expr *body = expr_child(sdef, 0);
            U32 fi = 0;
            for (U32 i = 0; i < body->children.count; i++) {
                if (expr_child(body, i)->type != NODE_DECL ||
                    expr_child(body, i)->data.decl.is_namespace) continue;
                U32 arg_idx = fi + 1;
                fi++;
                if (arg_idx < fcall->children.count &&
                    expr_child(fcall, arg_idx)->type == NODE_IDENT &&
                    Str_eq(expr_child(fcall, arg_idx)->data.str_val, var_name) &&
                    expr_child(body, i)->data.decl.is_own) {
                    return 1;
                }
            }
        }
    }
    // Direct call: look up func def in scope
    if (expr_child(fcall, 0)->type == NODE_IDENT) {
        Str *fn_name = expr_child(fcall, 0)->data.str_val;
        TypeBinding *fb = tscope_find(scope, fn_name);
        if (!fb || !fb->func_def) return 0;
        return check_own_args(fb->func_def, fcall, var_name);
    }
    // Namespace method call: look up in struct definition
    if (expr_child(fcall, 0)->type == NODE_FIELD_ACCESS && expr_child(fcall, 0)->is_ns_field) {
        Str *method = expr_child(fcall, 0)->data.str_val;
        Expr *type_node = expr_child(expr_child(fcall, 0), 0);
        if (type_node->type != NODE_IDENT) return 0;
        Expr *sdef = tscope_get_struct(scope, type_node->data.str_val);
        if (!sdef) return 0;
        Expr *body = expr_child(sdef, 0);
        for (U32 i = 0; i < body->children.count; i++) {
            Expr *field = expr_child(body, i);
            if (field->type == NODE_DECL && field->data.decl.is_namespace &&
                Str_eq(field->data.decl.name, method) &&
                expr_child(field, 0)->type == NODE_FUNC_DEF) {
                return check_own_args(expr_child(field, 0), fcall, var_name);
            }
        }
    }
    return 0;
}

static Bool expr_transfers_own(Expr *e, Str *var_name, TypeScope *scope) {
    if (e->type == NODE_FUNC_DEF) return 0;
    if (fcall_has_own_arg(e, var_name, scope)) return 1;
    // Own field assignment: RHS ownership transfers to the field
    if (e->type == NODE_FIELD_ASSIGN && e->is_own_field &&
        expr_child(e, 1)->type == NODE_IDENT &&
        Str_eq(expr_child(e, 1)->data.str_val, var_name)) {
        return 1;
    }
    for (U32 i = 0; i < e->children.count; i++) {
        if (expr_transfers_own(expr_child(e, i), var_name, scope)) return 1;
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
} LocalInfo;

// Insert deletes for live parent-scope locals before early exits in body.
// return_only=1: only before NODE_RETURN (used when propagating into while bodies,
// since break/continue don't leave the parent scope).
static void insert_exit_deletes(Expr *body, LocalInfo *live, U32 n_live, Bool return_only) {
    Vec new_ch = Vec_new(sizeof(Expr *));
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);
        if (stmt->type == NODE_IF) {
            for (U32 c = 1; c < stmt->children.count; c++)
                insert_exit_deletes(expr_child(stmt, c), live, n_live, return_only);
        }
        if (stmt->type == NODE_WHILE) {
            insert_exit_deletes(expr_child(stmt, 1), live, n_live, 1);
        }
        if (stmt->type == NODE_RETURN ||
            (!return_only && (stmt->type == NODE_BREAK || stmt->type == NODE_CONTINUE))) {
            for (U32 j = 0; j < n_live; j++) {
                if (stmt->children.count > 0 &&
                    expr_uses_var(expr_child(stmt, 0), live[j].name)) continue;
                Expr *del = make_delete_call(
                    live[j].name, live[j].type, live[j].struct_name, stmt);
                if (del) Vec_push(&new_ch, &del);
            }
        }
        Vec_push(&new_ch, &stmt);
    }
    if (new_ch.count != body->children.count) {
        Vec_delete(&body->children);
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch);
    }
}

static void insert_free_calls(Expr *body, TypeScope *scope, I32 scope_exit) {
    if (!scope_exit) return;

    // Phase 1: collect locals with lifetime info
    // Start from 0 (not locals_start) to include own params, which are added before the body
    Vec locals_vec = Vec_new(sizeof(LocalInfo));
    for (U32 i = 0; i < Map_len(&scope->bindings); i++) {
        TypeBinding *b = (TypeBinding *)Vec_get(&scope->bindings.vals, i);
        if ((b->is_param && !b->is_own) || b->struct_def || b->func_def || b->is_ref) continue;

        // Find decl_index: direct child first, then nested
        I32 decl_idx = -1;
        for (U32 j = 0; j < body->children.count; j++) {
            Expr *s = expr_child(body, j);
            if (s->type == NODE_DECL && Str_eq(s->data.decl.name, b->name)) {
                decl_idx = j;
                break;
            }
        }
        if (decl_idx == -1) {
            for (U32 j = 0; j < body->children.count; j++) {
                if (expr_contains_decl(expr_child(body, j), b->name)) {
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
            if (expr_uses_var(expr_child(body, j), b->name)) {
                last_use = j;
            }
            if (own_transfer == -1 && expr_transfers_own(expr_child(body, j), b->name, scope)) {
                own_transfer = j;
            }
        }

        // If captured by a nested func/proc, don't ASAP-delete — the nested
        // function may be called after this scope's body finishes (e.g. cli mode main)
        Bool captured = 0;
        for (U32 j = scan_from; j < body->children.count; j++) {
            if (expr_used_in_nested_func(expr_child(body, j), b->name)) {
                captured = 1;
                break;
            }
        }
        if (captured) continue;

        LocalInfo li = {b->name, b->type, b->struct_name, decl_idx, last_use, own_transfer};
        Vec_push(&locals_vec, &li);
    }

    if (locals_vec.count == 0) { Vec_delete(&locals_vec); return; }
    U32 n_locals = locals_vec.count;
    LocalInfo *locals = Vec_take(&locals_vec);

    // Extend lifetimes for args to ref-returning calls:
    // If ref m := f(x, y), then x and y must outlive m
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);
        if (stmt->type != NODE_DECL || !stmt->data.decl.is_ref) continue;
        Expr *rhs = expr_child(stmt, 0);
        if (rhs->type != NODE_FCALL) continue;
        // Find ref var's last_use (scan forward from decl)
        I32 ref_last = -1;
        for (U32 j = i + 1; j < body->children.count; j++) {
            if (expr_uses_var(expr_child(body, j), stmt->data.decl.name))
                ref_last = j;
        }
        if (ref_last == -1) ref_last = i; // at least until the decl itself
        // Extend last_use of all ident args in the fcall
        for (U32 a = 1; a < rhs->children.count; a++) {
            if (expr_child(rhs, a)->type != NODE_IDENT) continue;
            Str *aname = expr_child(rhs, a)->data.str_val;
            for (U32 j = 0; j < n_locals; j++) {
                if (Str_eq(locals[j].name, aname) && locals[j].last_use < ref_last) {
                    locals[j].last_use = ref_last;
                }
            }
        }
    }

    // Check for use after ownership transfer
    for (U32 j = 0; j < n_locals; j++) {
        if (locals[j].own_transfer >= 0 && locals[j].last_use > locals[j].own_transfer) {
            Expr *stmt = expr_child(body, locals[j].last_use);
            char buf[128];
            snprintf(buf, sizeof(buf), "use of '%s' after ownership transfer", locals[j].name->c_str);
            type_error(stmt, buf);
            Expr *xfer = expr_child(body, locals[j].own_transfer);
            fprintf(stderr, "%s:%u:%u: note: ownership transferred here\n",
                    xfer->path->c_str, xfer->line, xfer->col);
            fprintf(stderr, "  help: pass a clone instead: own %s.clone()\n",
                    locals[j].name->c_str);
        }
    }

    // Phase 2: rebuild body with ASAP frees
    Vec new_ch = Vec_new(sizeof(Expr *));

    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);

        // Before NODE_RETURN/NODE_BREAK/NODE_CONTINUE: free locals not yet freed
        if (stmt->type == NODE_RETURN || stmt->type == NODE_BREAK || stmt->type == NODE_CONTINUE) {
            for (U32 j = 0; j < n_locals; j++) {
                if (stmt->children.count > 0 && expr_uses_var(expr_child(stmt, 0), locals[j].name)) continue;
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].decl_index < (I32)i &&
                    (locals[j].last_use >= (I32)i || locals[j].last_use == -1)) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt);
                    if (del) Vec_push(&new_ch, &del);
                }
            }
        }

        // For NODE_IF/NODE_WHILE: insert frees before nested early exits
        if (stmt->type == NODE_IF || stmt->type == NODE_WHILE) {
            Vec live_vec = Vec_new(sizeof(LocalInfo));
            for (U32 j = 0; j < n_locals; j++) {
                if (locals[j].own_transfer >= 0) continue;
                if (locals[j].decl_index < (I32)i &&
                    (locals[j].last_use >= (I32)i || locals[j].last_use == -1)) {
                    Vec_push(&live_vec, &locals[j]);
                }
            }
            if (live_vec.count > 0) {
                U32 n_live = live_vec.count;
                LocalInfo *live = Vec_take(&live_vec);
                if (stmt->type == NODE_IF) {
                    for (U32 c = 1; c < stmt->children.count; c++)
                        insert_exit_deletes(expr_child(stmt, c), live, n_live, 0);
                } else {
                    // While: only free before return (break/continue stay in parent scope)
                    insert_exit_deletes(expr_child(stmt, 1), live, n_live, 1);
                }
                free(live);
            } else {
                Vec_delete(&live_vec);
            }
        }

        // Before NODE_ASSIGN: delete old compound-type value
        if (stmt->type == NODE_ASSIGN) {
            Str *vname = stmt->data.str_val;
            for (U32 j = 0; j < n_locals; j++) {
                if (!Str_eq(locals[j].name, vname)) continue;
                TilType t = locals[j].type;
                if (t == TIL_TYPE_STRUCT || t == TIL_TYPE_ENUM) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt);
                    if (del) Vec_push(&new_ch, &del);
                }
                break;
            }
        }

        // Add original statement
        Vec_push(&new_ch, &stmt);

        // After non-exit statements: free locals whose last use is this statement
        if (stmt->type != NODE_RETURN && stmt->type != NODE_BREAK && stmt->type != NODE_CONTINUE) {
            for (U32 j = 0; j < n_locals; j++) {
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].last_use == (I32)i) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt);
                    if (del) Vec_push(&new_ch, &del);
                }
                // Never used after declaration: free immediately
                if (locals[j].last_use == -1 && locals[j].decl_index == (I32)i) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt);
                    if (del) Vec_push(&new_ch, &del);
                }
            }
        }
    }

    Vec_delete(&body->children);
    body->children = new_ch;
    free(locals);
}

static void infer_body(TypeScope *scope, Expr *body, I32 in_func, I32 owns_scope, I32 in_loop) {
    body->til_type = TIL_TYPE_NONE;
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);
        switch (stmt->type) {
        case NODE_DECL:
            // Skip variant registry entries (payload enum: no children)
            if (stmt->children.count == 0) break;
            infer_expr(scope, expr_child(stmt, 0), in_func);
            // For struct/enum defs, register type in scope
            if (expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
                Bool is_enum = (expr_child(stmt, 0)->type == NODE_ENUM_DEF);
                // Check explicit type annotation if present
                if (stmt->data.decl.explicit_type) {
                    TilType declared = type_from_name(stmt->data.decl.explicit_type, scope);
                    TilType expected = is_enum ? TIL_TYPE_ENUM_DEF : TIL_TYPE_STRUCT_DEF;
                    if (declared != expected) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                                 stmt->data.decl.name->c_str, stmt->data.decl.explicit_type->c_str,
                                 is_enum ? "EnumDef" : "StructDef");
                        type_error(stmt, buf);
                    }
                }
                stmt->til_type = TIL_TYPE_NONE;
                Str *sname = stmt->data.decl.name;
                // Check if this is a builtin type
                TilType builtin_type = is_enum ? TIL_TYPE_ENUM : TIL_TYPE_STRUCT;
                Bool is_builtin = 0;
                if (Str_eq_c(sname, "I64"))  { builtin_type = TIL_TYPE_I64;  is_builtin = 1; }
                else if (Str_eq_c(sname, "U8"))   { builtin_type = TIL_TYPE_U8;   is_builtin = 1; }
                else if (Str_eq_c(sname, "I16"))  { builtin_type = TIL_TYPE_I16;  is_builtin = 1; }
                else if (Str_eq_c(sname, "I32"))  { builtin_type = TIL_TYPE_I32;  is_builtin = 1; }
                else if (Str_eq_c(sname, "U32"))  { builtin_type = TIL_TYPE_U32;  is_builtin = 1; }
                else if (Str_eq_c(sname, "Str"))  { is_builtin = 0; } // Str is a regular struct now
                else if (Str_eq_c(sname, "Bool")) { builtin_type = TIL_TYPE_BOOL; is_builtin = 1; }
                else if (Str_eq_c(sname, "StructDef"))    { builtin_type = TIL_TYPE_STRUCT_DEF; is_builtin = 1; }
                else if (Str_eq_c(sname, "EnumDef"))      { builtin_type = TIL_TYPE_ENUM_DEF;   is_builtin = 1; }
                else if (Str_eq_c(sname, "FunctionDef"))  { builtin_type = TIL_TYPE_FUNC_DEF;   is_builtin = 1; }
                else if (Str_eq_c(sname, "Dynamic"))      { builtin_type = TIL_TYPE_DYNAMIC;    is_builtin = 1; }
                tscope_set(scope, sname, builtin_type, -1, 0, stmt->line, stmt->col, 0, 0);
                // Store struct def pointer and builtin flag in the binding
                TypeBinding *b = tscope_find(scope, sname);
                b->struct_def = expr_child(stmt, 0);
                b->is_builtin = is_builtin;
                b->is_ext = expr_child(stmt, 0)->is_ext;
                break;
            }
            // For func/proc defs, store return type and func/proc-ness in scope
            if (expr_child(stmt, 0)->type == NODE_FUNC_DEF) {
                // Check explicit type annotation if present
                if (stmt->data.decl.explicit_type) {
                    TilType declared = type_from_name(stmt->data.decl.explicit_type, scope);
                    if (declared != TIL_TYPE_FUNC_DEF) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is FunctionDef",
                                 stmt->data.decl.name->c_str, stmt->data.decl.explicit_type->c_str);
                        type_error(stmt, buf);
                    }
                }
                FuncType ft = expr_child(stmt, 0)->data.func_def.func_type;
                I32 callee_is_proc = (ft == FUNC_TEST) ? 2 : (ft == FUNC_PROC || ft == FUNC_EXT_PROC) ? 1 : 0;
                TilType rt = TIL_TYPE_NONE;
                if (expr_child(stmt, 0)->data.func_def.return_type) {
                    rt = type_from_name(expr_child(stmt, 0)->data.func_def.return_type, scope);
                }
                stmt->til_type = rt;
                tscope_set(scope, stmt->data.decl.name, rt, callee_is_proc, 0, stmt->line, stmt->col, 0, 0);
                // Store func_def pointer and builtin flag
                TypeBinding *fb = tscope_find(scope, stmt->data.decl.name);
                if (fb) {
                    fb->func_def = expr_child(stmt, 0);
                    if (ft == FUNC_EXT_FUNC || ft == FUNC_EXT_PROC)
                        fb->is_builtin = 1;
                }
                break;
            }
            if (stmt->data.decl.explicit_type) {
                Str *etn = stmt->data.decl.explicit_type;
                TilType declared = type_from_name(etn, scope);
                if (declared == TIL_TYPE_UNKNOWN) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", etn->c_str);
                    type_error(stmt, buf);
                } else if (declared == TIL_TYPE_DYNAMIC && !stmt->data.decl.is_own) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "cannot store Dynamic in '%s'; use 'own' with Dynamic type",
                             stmt->data.decl.name->c_str);
                    type_error(stmt, buf);
                } else if (expr_child(stmt, 0)->type == NODE_LITERAL_NUM &&
                           (declared == TIL_TYPE_I64 || declared == TIL_TYPE_U8 || declared == TIL_TYPE_I16 || declared == TIL_TYPE_I32 || declared == TIL_TYPE_U32 || declared == TIL_TYPE_DYNAMIC)) {
                    // Numeric literals can be used with numeric types and Dynamic (0 = null)
                    expr_child(stmt, 0)->til_type = declared;
                } else if (expr_child(stmt, 0)->til_type != declared &&
                           expr_child(stmt, 0)->til_type != TIL_TYPE_DYNAMIC) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.decl.name->c_str, til_type_name_c(declared),
                             til_type_name_c(expr_child(stmt, 0)->til_type));
                    type_error(stmt, buf);
                } else if ((declared == TIL_TYPE_STRUCT || declared == TIL_TYPE_ENUM) &&
                           expr_child(stmt, 0)->struct_name &&
                           !Str_eq(etn, expr_child(stmt, 0)->struct_name)) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.decl.name->c_str, etn->c_str, expr_child(stmt, 0)->struct_name->c_str);
                    type_error(stmt, buf);
                }
                stmt->til_type = declared;
                // Narrow Dynamic RHS to declared type
                narrow_dynamic(expr_child(stmt, 0), declared, etn);
                // For struct/enum types, propagate struct_name from explicit type
                if (declared == TIL_TYPE_STRUCT || declared == TIL_TYPE_ENUM) {
                    expr_child(stmt, 0)->struct_name = etn;
                }
            } else {
                stmt->til_type = expr_child(stmt, 0)->til_type;
                if (stmt->til_type == TIL_TYPE_DYNAMIC) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "cannot store Dynamic in '%s'; add explicit type annotation",
                             stmt->data.decl.name->c_str);
                    type_error(stmt, buf);
                }
            }
            tscope_set(scope, stmt->data.decl.name, stmt->til_type, -1, stmt->data.decl.is_mut, stmt->line, stmt->col, 0, 0);
            if ((stmt->til_type == TIL_TYPE_STRUCT || stmt->til_type == TIL_TYPE_ENUM) && expr_child(stmt, 0)->struct_name) {
                TypeBinding *b = tscope_find(scope, stmt->data.decl.name);
                if (b) b->struct_name = expr_child(stmt, 0)->struct_name;
            }
            if (stmt->data.decl.is_ref) {
                TypeBinding *b = tscope_find(scope, stmt->data.decl.name);
                if (b) b->is_ref = 1;
                // Validate ref RHS: must be a ref-returning fcall or a ref/param variable
                Expr *rhs = expr_child(stmt, 0);
                Bool ok = 0;
                if (rhs->type == NODE_FCALL && fcall_returns_ref(rhs, scope)) ok = 1;
                if (rhs->type == NODE_IDENT) {
                    TypeBinding *rb = tscope_find(scope, rhs->data.str_val);
                    if (rb && (rb->is_ref || (rb->is_param && !rb->is_own))) ok = 1;
                }
                if (!ok) type_error(stmt, "'ref' declaration requires a ref-returning function or ref/param variable");
            }
            // Auto-insert clone for declarations from identifiers (skip ref decls)
            if (expr_child(stmt, 0)->type == NODE_IDENT && !stmt->data.decl.is_ref) {
                const char *tname = type_to_name(stmt->til_type, expr_child(stmt, 0)->struct_name);
                if (tname) {
                    expr_child(stmt, 0) = make_clone_call(
                        tname, stmt->til_type,
                        expr_child(stmt, 0), stmt);
                }
            }
            break;
        case NODE_ASSIGN: {
            infer_expr(scope, expr_child(stmt, 0), in_func);
            stmt->til_type = expr_child(stmt, 0)->til_type;
            Str *aname = stmt->data.str_val;
            TilType existing = tscope_get(scope, aname);
            if (existing == TIL_TYPE_UNKNOWN) {
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
                            stmt->path->c_str, b->line, b->col, aname->c_str);
                } else if (b) {
                    fprintf(stderr, "%s:%u:%u: note: '%s' declared here, consider adding 'mut'\n",
                            stmt->path->c_str, b->line, b->col, aname->c_str);
                }
            } else if (expr_child(stmt, 0)->til_type != existing &&
                       expr_child(stmt, 0)->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "'%s' is %s but assigned %s",
                         aname->c_str, til_type_name_c(existing),
                         til_type_name_c(expr_child(stmt, 0)->til_type));
                type_error(stmt, buf);
            }
            // Auto-insert clone for assignments from identifiers
            if (expr_child(stmt, 0)->type == NODE_IDENT) {
                const char *tname = type_to_name(expr_child(stmt, 0)->til_type, expr_child(stmt, 0)->struct_name);
                if (tname) {
                    expr_child(stmt, 0) = make_clone_call(
                        tname, expr_child(stmt, 0)->til_type,
                        expr_child(stmt, 0), stmt);
                }
            }
            break;
        }
        case NODE_FIELD_ASSIGN: {
            infer_expr(scope, expr_child(stmt, 0), in_func); // object
            infer_expr(scope, expr_child(stmt, 1), in_func); // value
            Expr *obj = expr_child(stmt, 0);
            Str *fname = stmt->data.str_val;
            if (obj->struct_name) {
                Expr *sdef = tscope_get_struct(scope, obj->struct_name);
                if (sdef) {
                    Expr *body = expr_child(sdef, 0);
                    Bool found = 0;
                    for (U32 i = 0; i < body->children.count; i++) {
                        Expr *field = expr_child(body, i);
                        if (Str_eq(field->data.decl.name, fname)) {
                            found = 1;
                            stmt->is_ns_field = field->data.decl.is_namespace;
                            stmt->is_own_field = field->data.decl.is_own;
                            if (!field->data.decl.is_mut) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "cannot assign to immutable field '%s'", fname->c_str);
                                type_error(stmt, buf);
                            }
                            if (expr_child(stmt, 1)->til_type != field->til_type &&
                                expr_child(stmt, 1)->til_type != TIL_TYPE_UNKNOWN &&
                                expr_child(stmt, 1)->til_type != TIL_TYPE_DYNAMIC) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "field '%s' is %s but assigned %s",
                                         fname->c_str, til_type_name_c(field->til_type),
                                         til_type_name_c(expr_child(stmt, 1)->til_type));
                                type_error(stmt, buf);
                            }
                            break;
                        }
                    }
                    if (!found) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'",
                                 obj->struct_name->c_str, fname->c_str);
                        type_error(stmt, buf);
                    }
                }
            } else {
                type_error(stmt, "field assignment on non-struct value");
            }
            stmt->til_type = TIL_TYPE_NONE;
            // Auto-insert clone for field assignments from identifiers
            if (expr_child(stmt, 1)->type == NODE_IDENT) {
                const char *tname = type_to_name(expr_child(stmt, 1)->til_type,
                                                  expr_child(stmt, 1)->struct_name);
                if (tname) {
                    expr_child(stmt, 1) = make_clone_call(tname,
                        expr_child(stmt, 1)->til_type, expr_child(stmt, 1),
                        expr_child(stmt, 1));
                }
            }
            break;
        }
        case NODE_FCALL:
            infer_expr(scope, stmt, in_func);
            break;
        case NODE_RETURN:
            if (stmt->children.count > 0) {
                infer_expr(scope, expr_child(stmt, 0), in_func);
                stmt->til_type = expr_child(stmt, 0)->til_type;
            } else {
                stmt->til_type = TIL_TYPE_NONE;
            }
            break;
        case NODE_BREAK:
            if (!in_loop) {
                type_error(stmt, "break outside loop");
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        case NODE_CONTINUE:
            if (!in_loop) {
                type_error(stmt, "continue outside loop");
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        case NODE_IF:
            infer_expr(scope, expr_child(stmt, 0), in_func); // condition
            if (expr_child(stmt, 0)->til_type != TIL_TYPE_BOOL &&
                expr_child(stmt, 0)->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "if condition must be Bool, got %s",
                         til_type_name_c(expr_child(stmt, 0)->til_type));
                type_error(stmt, buf);
            }
            {
                TypeScope *then_scope = tscope_new(scope);
                infer_body(then_scope, expr_child(stmt, 1), in_func, 1, in_loop);
                tscope_free(then_scope);
            }
            if (stmt->children.count > 2) {
                TypeScope *else_scope = tscope_new(scope);
                infer_body(else_scope, expr_child(stmt, 2), in_func, 1, in_loop);
                tscope_free(else_scope);
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        case NODE_BODY: {
            TypeScope *block_scope = tscope_new(scope);
            infer_body(block_scope, stmt, in_func, 1, in_loop);
            tscope_free(block_scope);
            break;
        }
        case NODE_WHILE:
            infer_expr(scope, expr_child(stmt, 0), in_func); // condition
            if (expr_child(stmt, 0)->til_type != TIL_TYPE_BOOL &&
                expr_child(stmt, 0)->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "while condition must be Bool, got %s",
                         til_type_name_c(expr_child(stmt, 0)->til_type));
                type_error(stmt, buf);
            }
            // Transform: while COND { BODY } -> while true { _wcond := COND; if _wcond {} else { break }; BODY }
            // This lets ASAP destruction free the condition result each iteration.
            if (expr_contains_fcall(expr_child(stmt, 0))) {
                Expr *cond = expr_child(stmt, 0);
                I32 line = cond->line;
                I32 col = cond->col;
                Str *path = cond->path;
                Expr *body = expr_child(stmt, 1);
                // _wcondN := COND
                char name_buf[32];
                snprintf(name_buf, sizeof(name_buf), "_wcond%d", hoist_counter++);
                Str *wname = Str_new(name_buf);
                Expr *decl = expr_new(NODE_DECL, line, col, path);
                decl->data.decl.name = wname;
                decl->data.decl.explicit_type = NULL;
                decl->data.decl.is_mut = false;
                decl->data.decl.is_namespace = false;
                decl->til_type = cond->til_type;
                expr_add_child(decl, cond);
                // if _wcondN {} else { break }
                Expr *ident = expr_new(NODE_IDENT, line, col, path);
                ident->data.str_val = wname;
                ident->til_type = TIL_TYPE_BOOL;
                Expr *if_node = expr_new(NODE_IF, line, col, path);
                if_node->til_type = TIL_TYPE_NONE;
                expr_add_child(if_node, ident);
                Expr *then_body = expr_new(NODE_BODY, line, col, path);
                then_body->til_type = TIL_TYPE_NONE;
                expr_add_child(if_node, then_body);
                Expr *else_body = expr_new(NODE_BODY, line, col, path);
                else_body->til_type = TIL_TYPE_NONE;
                Expr *brk = expr_new(NODE_BREAK, line, col, path);
                brk->til_type = TIL_TYPE_NONE;
                expr_add_child(else_body, brk);
                expr_add_child(if_node, else_body);
                // Prepend decl + if to body
                Vec new_ch = Vec_new(sizeof(Expr *));
                Vec_push(&new_ch, &decl);
                Vec_push(&new_ch, &if_node);
                for (U32 j = 0; j < body->children.count; j++) {
                    Expr *ch = expr_child(body, j);
                    Vec_push(&new_ch, &ch);
                }
                Vec_delete(&body->children);
                body->children = new_ch;
                // Replace condition with true
                Expr *true_lit = expr_new(NODE_LITERAL_BOOL, line, col, path);
                true_lit->data.str_val = Str_new("true");
                true_lit->til_type = TIL_TYPE_BOOL;
                expr_child(stmt, 0) = true_lit;
            }
            {
                TypeScope *while_scope = tscope_new(scope);
                infer_body(while_scope, expr_child(stmt, 1), in_func, 1, 1);
                tscope_free(while_scope);
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        default:
            stmt->til_type = TIL_TYPE_NONE;
            break;
        }
    }
    if (owns_scope) desugar_variadic_calls(body, scope);
    if (owns_scope) hoist_fcall_args(body, scope);
    insert_field_deletes(body);
    insert_free_calls(body, scope, owns_scope);
}

I32 type_check(Expr *program, TypeScope *scope, const Mode *mode) {
    errors = 0;
    current_mode = mode;
    infer_body(scope, program, 0, 1, 0);
    return errors;
}
