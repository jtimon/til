#include "typer.h"
#include "initer.h"
#include "vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Type inference/checking pass ---

static int errors;

static void type_error(const char *path, Expr *e, const char *msg) {
    fprintf(stderr, "%s:%d:%d: type error: %s\n", path, e->line, e->col, msg);
    errors++;
}

// Parse a type name string to TilType (scope-aware for user-defined struct types)
static TilType type_from_name(Str *name, TypeScope *scope) {
    if (Str_eq_c(name, "I64"))  return TIL_TYPE_I64;
    if (Str_eq_c(name, "U8"))   return TIL_TYPE_U8;
    if (Str_eq_c(name, "Str"))  return TIL_TYPE_STR;
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

static void infer_expr(TypeScope *scope, Expr *e, const char *path, int in_func);
static void infer_body(TypeScope *scope, Expr *body, const char *path, int in_func, int owns_scope, int in_loop);
static const char *type_to_name(TilType type, Str *struct_name);
static Expr *make_clone_call(const char *type_name, TilType type, Expr *arg, int line, int col);
static int fcall_returns_ref(Expr *fcall, TypeScope *scope);

static void infer_expr(TypeScope *scope, Expr *e, const char *path, int in_func) {
    switch (e->type) {
    case NODE_LITERAL_STR:
        e->til_type = TIL_TYPE_STR;
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
            type_error(path, e, buf);
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
            int is_func = (e->data.func_def.func_type == FUNC_FUNC);
            int is_macro = (e->data.func_def.func_type == FUNC_MACRO);
            TypeScope *func_scope = tscope_new(scope);
            // Bind parameters
            for (int i = 0; i < e->data.func_def.nparam; i++) {
                Str *ptn = e->data.func_def.param_types[i];
                TilType pt = type_from_name(ptn, scope);
                if (pt == TIL_TYPE_UNKNOWN) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", ptn->c_str);
                    type_error(path, e, buf);
                }
                int pmut = e->data.func_def.param_muts ? e->data.func_def.param_muts[i] : 0;
                int pown = e->data.func_def.param_owns ? e->data.func_def.param_owns[i] : 0;
                tscope_set(func_scope, e->data.func_def.param_names[i], pt, -1, pmut, e->line, e->col, 1, pown);
                // For struct/enum-typed params, store struct_name
                if (pt == TIL_TYPE_STRUCT || pt == TIL_TYPE_ENUM) {
                    TypeBinding *pb = tscope_find(func_scope, e->data.func_def.param_names[i]);
                    if (pb) pb->struct_name = ptn;
                }
            }
            infer_body(func_scope, expr_child(e, 0), path, is_func, 1, 0);
            // Check: func/macro must have a return type
            if ((is_func || is_macro) && !e->data.func_def.return_type) {
                type_error(path, e, is_macro ? "macro must declare a return type"
                                             : "func must declare a return type");
            }
            // Validate ref returns: every return value must be a param or ref variable
            if (e->data.func_def.return_is_ref) {
                Expr *body = expr_child(e, 0);
                for (int ri = 0; ri < body->children.len; ri++) {
                    Expr *s = expr_child(body, ri);
                    if (s->type != NODE_RETURN || s->children.len == 0) continue;
                    Expr *rv = expr_child(s, 0);
                    int ok = 0;
                    if (rv->type == NODE_IDENT) {
                        TypeBinding *rb = tscope_find(func_scope, rv->data.str_val);
                        if (rb && (rb->is_param || rb->is_ref)) ok = 1;
                    }
                    if (rv->type == NODE_FCALL && fcall_returns_ref(rv, func_scope)) ok = 1;
                    if (!ok) type_error(path, s, "ref function must return a parameter or ref variable");
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
        infer_body(inner, expr_child(e, 0), path, 0, 0, 0);
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
            infer_expr(scope, obj, path, in_func);

            // Check: is obj a type name (has struct_def) or an instance/value?
            TypeBinding *tb = (obj->type == NODE_IDENT)
                ? tscope_find(scope, obj->data.str_val) : NULL;
            int obj_is_type = (tb && tb->struct_def);

            if (!obj_is_type) {
                // UFCS: instance.method(args) -> Type.method(instance, args)
                Str *type_name = NULL;
                if (obj->til_type == TIL_TYPE_I64)  type_name = Str_new("I64");
                else if (obj->til_type == TIL_TYPE_U8)   type_name = Str_new("U8");
                else if (obj->til_type == TIL_TYPE_BOOL) type_name = Str_new("Bool");
                else if (obj->til_type == TIL_TYPE_STR)  type_name = Str_new("Str");
                else if ((obj->til_type == TIL_TYPE_STRUCT || obj->til_type == TIL_TYPE_ENUM) && obj->struct_name)
                    type_name = obj->struct_name;

                Expr *sdef = type_name ? tscope_get_struct(scope, type_name) : NULL;
                Expr *ns_func = NULL;
                if (sdef) {
                    Expr *body = expr_child(sdef, 0);
                    for (int i = 0; i < body->children.len; i++) {
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
                    snprintf(buf, sizeof(buf), "no method '%s' for type '%s'",
                             method->c_str, type_name ? type_name->c_str : "unknown");
                    type_error(path, e, buf);
                    e->til_type = TIL_TYPE_UNKNOWN;
                    break;
                }
                // Desugar: rewrite AST to Type.method(instance, args)
                Expr *instance = obj;
                Expr *type_ident = expr_new(NODE_IDENT, obj->line, obj->col);
                type_ident->data.str_val = type_name;
                expr_child(fa, 0) = type_ident;
                // Insert instance as first arg
                Expr *dummy = NULL;
                Vec_push(&e->children, &dummy);
                memmove(&expr_child(e, 2), &expr_child(e, 1), (e->children.len - 2) * sizeof(Expr *));
                expr_child(e, 1) = instance;
                // Fall through -- existing code below handles Type.method(instance, args)
            }

            // Type the (possibly new) object and look up namespace func
            obj = expr_child(fa, 0);
            if (obj->til_type == TIL_TYPE_UNKNOWN) {
                infer_expr(scope, obj, path, in_func);
            }
            Expr *sdef = obj->struct_name ? tscope_get_struct(scope, obj->struct_name) : NULL;
            Expr *ns_func = NULL;
            if (sdef) {
                Expr *body = expr_child(sdef, 0);
                for (int i = 0; i < body->children.len; i++) {
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
                type_error(path, e, buf);
                e->til_type = TIL_TYPE_UNKNOWN;
                break;
            }
            fa->is_ns_field = true;
            // Desugar named/optional args for namespace methods
            {
                int np = ns_func->data.func_def.nparam;
                Expr **new_args = calloc(np, sizeof(Expr *));
                int pos_idx = 0;
                int seen_named = 0;
                for (int i = 1; i < e->children.len; i++) {
                    Expr *arg = expr_child(e, i);
                    if (arg->type == NODE_NAMED_ARG) {
                        seen_named = 1;
                        Str *aname = arg->data.str_val;
                        int slot = -1;
                        for (int j = 0; j < np; j++) {
                            if (Str_eq(ns_func->data.func_def.param_names[j], aname)) {
                                slot = j;
                                break;
                            }
                        }
                        if (slot < 0) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "no parameter '%s'", aname->c_str);
                            type_error(path, arg, buf);
                        } else if (new_args[slot]) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "duplicate argument for parameter '%s'", aname->c_str);
                            type_error(path, arg, buf);
                        } else {
                            new_args[slot] = expr_child(arg, 0); // unwrap NODE_NAMED_ARG
                        }
                    } else {
                        if (seen_named) {
                            type_error(path, arg, "positional argument after named argument");
                        }
                        if (pos_idx < np) {
                            new_args[pos_idx] = arg;
                        }
                        pos_idx++;
                    }
                }
                // Fill defaults for missing args
                for (int i = 0; i < np; i++) {
                    if (!new_args[i]) {
                        if (ns_func->data.func_def.param_defaults &&
                            ns_func->data.func_def.param_defaults[i]) {
                            new_args[i] = expr_clone(ns_func->data.func_def.param_defaults[i]);
                        } else {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "missing argument for parameter '%s'",
                                     ns_func->data.func_def.param_names[i]->c_str);
                            type_error(path, e, buf);
                        }
                    }
                }
                if (pos_idx > np) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d", np, pos_idx);
                    type_error(path, e, buf);
                }
                // Rebuild children: callee + desugared args
                Vec new_ch = Vec_new(sizeof(Expr *));
                Expr *callee = expr_child(e, 0);
                Vec_push(&new_ch, &callee);
                for (int i = 0; i < np; i++)
                    Vec_push(&new_ch, &new_args[i]);
                Vec_delete(&e->children);
                e->children = new_ch;
                free(new_args);
            }
            // Infer arg types
            for (int i = 1; i < e->children.len; i++) {
                infer_expr(scope, expr_child(e, i), path, in_func);
            }
            // Validate 'own' markers on arguments
            {
                bool *po = ns_func->data.func_def.param_owns;
                if (po) {
                    int np = ns_func->data.func_def.nparam;
                    for (int i = 1; i < e->children.len && i - 1 < np; i++) {
                        int pown = po[i - 1];
                        if (pown && !expr_child(e, i)->is_own_arg) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "argument for 'own' parameter '%s' must be marked 'own'",
                                     ns_func->data.func_def.param_names[i - 1]->c_str);
                            type_error(path, expr_child(e, i), buf);
                        } else if (!pown && expr_child(e, i)->is_own_arg) {
                            char buf[128];
                            snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                                     ns_func->data.func_def.param_names[i - 1]->c_str);
                            type_error(path, expr_child(e, i), buf);
                        }
                        if (pown && expr_child(e, i)->type == NODE_IDENT) {
                            TypeBinding *ab = tscope_find(scope, expr_child(e, i)->data.str_val);
                            if (ab && ab->is_ref) type_error(path, expr_child(e, i), "cannot pass ref variable to 'own' parameter");
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
        // Resolve callee
        Str *name = expr_child(e, 0)->data.str_val;
        // Struct instantiation: Point() or Point(x=1, y=2)
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) {
            TypeBinding *sb = tscope_find(scope, name);
            if (sb && sb->is_builtin && !sb->is_ext) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot instantiate builtin type '%s'", name->c_str);
                type_error(path, e, buf);
                e->til_type = TIL_TYPE_UNKNOWN;
                break;
            }
            Expr *body = expr_child(sdef, 0);
            // Count instance fields (skip namespace)
            int nfields = 0;
            for (int i = 0; i < body->children.len; i++) {
                if (!expr_child(body, i)->data.decl.is_namespace) nfields++;
            }
            // Desugar named args into positional (one per instance field)
            Expr **field_vals = calloc(nfields, sizeof(Expr *));
            // Map: field_idx[k] = index into body->children for k-th instance field
            int *field_idx = malloc(nfields * sizeof(int));
            { int k = 0;
              for (int i = 0; i < body->children.len; i++) {
                  if (!expr_child(body, i)->data.decl.is_namespace) field_idx[k++] = i;
              }
            }
            for (int i = 1; i < e->children.len; i++) {
                Expr *arg = expr_child(e, i);
                if (arg->type != NODE_NAMED_ARG) {
                    type_error(path, arg, "struct instantiation requires named arguments");
                    continue;
                }
                Str *aname = arg->data.str_val;
                int slot = -1;
                for (int j = 0; j < nfields; j++) {
                    if (Str_eq(expr_child(body, field_idx[j])->data.decl.name, aname)) {
                        slot = j;
                        break;
                    }
                }
                if (slot < 0) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'", name->c_str, aname->c_str);
                    type_error(path, arg, buf);
                } else if (field_vals[slot]) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "duplicate argument for field '%s'", aname->c_str);
                    type_error(path, arg, buf);
                } else {
                    field_vals[slot] = expr_child(arg, 0); // unwrap NODE_NAMED_ARG
                }
            }
            // Fill remaining from struct field defaults (clone to avoid shared ownership)
            for (int i = 0; i < nfields; i++) {
                if (!field_vals[i]) {
                    field_vals[i] = expr_clone(expr_child(expr_child(body, field_idx[i]), 0));
                }
            }
            // Rebuild children: callee + instance field values
            Vec new_ch = Vec_new(sizeof(Expr *));
            Expr *callee = expr_child(e, 0);
            Vec_push(&new_ch, &callee);
            for (int i = 0; i < nfields; i++)
                Vec_push(&new_ch, &field_vals[i]);
            Vec_delete(&e->children);
            e->children = new_ch;
            free(field_vals);
            free(field_idx);
            // Type-check args (skip already-inferred defaults)
            for (int i = 1; i < e->children.len; i++) {
                if (expr_child(e, i)->til_type == TIL_TYPE_UNKNOWN) {
                    infer_expr(scope, expr_child(e, i), path, in_func);
                }
            }
            // Auto-insert clone for constructor args that are identifiers
            for (int i = 1; i < e->children.len; i++) {
                if (expr_child(e, i)->type == NODE_IDENT) {
                    const char *tname = type_to_name(expr_child(e, i)->til_type,
                                                      expr_child(e, i)->struct_name);
                    if (tname) {
                        expr_child(e, i) = make_clone_call(tname,
                            expr_child(e, i)->til_type, expr_child(e, i),
                            expr_child(e, i)->line, expr_child(e, i)->col);
                    }
                }
            }
            e->til_type = TIL_TYPE_STRUCT;
            e->struct_name = name;
            break;
        }
        // Desugar named/optional args for user-defined functions (skip builtins)
        TypeBinding *callee_bind = tscope_find(scope, name);
        if (callee_bind && callee_bind->func_def && !callee_bind->is_builtin) {
            Expr *fdef = callee_bind->func_def;
            int nparam = fdef->data.func_def.nparam;
            // Build new args array (slot per param)
            Expr **new_args = calloc(nparam, sizeof(Expr *));
            int pos_idx = 0;
            int seen_named = 0;
            for (int i = 1; i < e->children.len; i++) {
                Expr *arg = expr_child(e, i);
                if (arg->type == NODE_NAMED_ARG) {
                    seen_named = 1;
                    Str *aname = arg->data.str_val;
                    int slot = -1;
                    for (int j = 0; j < nparam; j++) {
                        if (Str_eq(fdef->data.func_def.param_names[j], aname)) {
                            slot = j;
                            break;
                        }
                    }
                    if (slot < 0) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' has no parameter '%s'", name->c_str, aname->c_str);
                        type_error(path, arg, buf);
                    } else if (new_args[slot]) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "duplicate argument for parameter '%s'", aname->c_str);
                        type_error(path, arg, buf);
                    } else {
                        new_args[slot] = expr_child(arg, 0); // unwrap NODE_NAMED_ARG
                    }
                } else {
                    if (seen_named) {
                        type_error(path, arg, "positional argument after named argument");
                    }
                    if (pos_idx < nparam) {
                        new_args[pos_idx] = arg;
                    }
                    pos_idx++;
                }
            }
            // Fill defaults for missing args
            for (int i = 0; i < nparam; i++) {
                if (!new_args[i]) {
                    if (fdef->data.func_def.param_defaults &&
                        fdef->data.func_def.param_defaults[i]) {
                        new_args[i] = expr_clone(fdef->data.func_def.param_defaults[i]);
                    } else {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "missing argument for parameter '%s'",
                                 fdef->data.func_def.param_names[i]->c_str);
                        type_error(path, e, buf);
                    }
                }
            }
            if (pos_idx > nparam) {
                char buf[128];
                snprintf(buf, sizeof(buf), "too many arguments: expected %d, got %d",
                         nparam, pos_idx);
                type_error(path, e, buf);
            }
            // Rebuild children: callee + desugared args
            Vec new_ch = Vec_new(sizeof(Expr *));
            Expr *callee = expr_child(e, 0);
            Vec_push(&new_ch, &callee);
            for (int i = 0; i < nparam; i++)
                Vec_push(&new_ch, &new_args[i]);
            Vec_delete(&e->children);
            e->children = new_ch;
            free(new_args);
        }
        // Infer types of all arguments
        for (int i = 1; i < e->children.len; i++) {
            infer_expr(scope, expr_child(e, i), path, in_func);
        }
        // Validate 'own' markers on arguments
        if (callee_bind && callee_bind->func_def) {
            Expr *fdef = callee_bind->func_def;
            bool *po = fdef->data.func_def.param_owns;
            for (int i = 1; i < e->children.len && i - 1 < fdef->data.func_def.nparam; i++) {
                int pown = po ? po[i - 1] : 0;
                if (pown && !expr_child(e, i)->is_own_arg) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "argument for 'own' parameter '%s' must be marked 'own'",
                             fdef->data.func_def.param_names[i - 1]->c_str);
                    type_error(path, expr_child(e, i), buf);
                } else if (!pown && expr_child(e, i)->is_own_arg) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                             fdef->data.func_def.param_names[i - 1]->c_str);
                    type_error(path, expr_child(e, i), buf);
                }
                if (pown && expr_child(e, i)->type == NODE_IDENT) {
                    TypeBinding *ab = tscope_find(scope, expr_child(e, i)->data.str_val);
                    if (ab && ab->is_ref) type_error(path, expr_child(e, i), "cannot pass ref variable to 'own' parameter");
                }
            }
        }
        // Resolve return type from scope (covers builtins and user-defined)
        TilType fn_type = tscope_get(scope, name);
        if (fn_type == TIL_TYPE_UNKNOWN) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined function '%s'", name->c_str);
            type_error(path, e, buf);
        }
        e->til_type = fn_type;
        // Propagate struct_name for struct-returning functions
        if ((fn_type == TIL_TYPE_STRUCT || fn_type == TIL_TYPE_ENUM) && callee_bind && callee_bind->func_def &&
            callee_bind->func_def->data.func_def.return_type) {
            e->struct_name = callee_bind->func_def->data.func_def.return_type;
        }
        // Check: func cannot call proc (panic is exempt)
        if (in_func && tscope_is_proc(scope, name) == 1 && !Str_eq_c(name, "panic")) {
            char buf[128];
            snprintf(buf, sizeof(buf), "func cannot call proc '%s'", name->c_str);
            type_error(path, e, buf);
        }
        break;
    }
    case NODE_FIELD_ACCESS: {
        infer_expr(scope, expr_child(e, 0), path, in_func);
        Expr *obj = expr_child(e, 0);
        if (obj->struct_name) {
            Expr *sdef = tscope_get_struct(scope, obj->struct_name);
            if (sdef) {
                Expr *body = expr_child(sdef, 0);
                Str *fname = e->data.str_val;
                int found = 0;
                for (int i = 0; i < body->children.len; i++) {
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
                            field->children.len > 0) {
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
                    type_error(path, e, buf);
                    e->til_type = TIL_TYPE_UNKNOWN;
                }
            }
        } else {
            type_error(path, e, "field access on non-struct value");
            e->til_type = TIL_TYPE_UNKNOWN;
        }
        break;
    }
    default:
        e->til_type = TIL_TYPE_UNKNOWN;
        break;
    }
}

// --- Argument hoisting ---

static int expr_contains_fcall(Expr *e) {
    if (e->type == NODE_FCALL) return 1;
    for (int i = 0; i < e->children.len; i++) {
        if (expr_contains_fcall(expr_child(e, i))) return 1;
    }
    return 0;
}

// Check if a function call returns ref
static int fcall_returns_ref(Expr *fcall, TypeScope *scope) {
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
        for (int j = 0; j < body->children.len; j++) {
            Expr *f = expr_child(body, j);
            if (f->type == NODE_DECL && f->data.decl.is_namespace &&
                Str_eq(f->data.decl.name, callee->data.str_val) &&
                expr_child(f, 0)->type == NODE_FUNC_DEF)
                return expr_child(f, 0)->data.func_def.return_is_ref;
        }
    }
    return 0;
}

static int hoist_counter = 0;

// Create a temp decl for an expression, register in scope, return the replacement ident.
// Adds the decl to the hoisted list.
static Expr *hoist_to_temp(Expr *val, Expr ***hoisted, int *nhoisted, int *cap, TypeScope *scope) {
    char name_buf[32];
    snprintf(name_buf, sizeof(name_buf), "_t%d", hoist_counter++);
    Str *tname = Str_new(name_buf);
    Expr *decl = expr_new(NODE_DECL, val->line, val->col);
    decl->data.decl.name = tname;
    decl->data.decl.explicit_type = NULL;
    decl->data.decl.is_mut = false;
    decl->data.decl.is_namespace = false;
    decl->til_type = val->til_type;
    expr_add_child(decl, val);
    Expr *ident = expr_new(NODE_IDENT, val->line, val->col);
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
static void hoist_expr(Expr *e, Expr ***hoisted, int *nhoisted, int *cap, TypeScope *scope) {
    // Don't recurse into scope boundaries -- those have their own infer_body calls
    if (e->type == NODE_FUNC_DEF || e->type == NODE_STRUCT_DEF || e->type == NODE_ENUM_DEF || e->type == NODE_BODY) return;
    // Recurse into children first (depth-first: inner fcalls hoisted before outer)
    for (int i = 0; i < e->children.len; i++) {
        hoist_expr(expr_child(e, i), hoisted, nhoisted, cap, scope);
    }
    if (e->type != NODE_FCALL) return;

    // For struct constructors, find field info to skip hoisting inline compound args
    Expr *ctor_body = NULL;
    if (e->struct_name && e->children.len > 0 &&
        Str_eq(expr_child(e, 0)->data.str_val, e->struct_name)) {
        Expr *sdef = tscope_get_struct(scope, e->struct_name);
        if (sdef) ctor_body = expr_child(sdef, 0);
    }

    // Check each argument (children[1..n])
    int fi = 0; // instance field index for struct constructors
    for (int i = 1; i < e->children.len; i++) {
        if (expr_child(e, i)->type != NODE_FCALL &&
            expr_child(e, i)->type != NODE_LITERAL_NUM &&
            expr_child(e, i)->type != NODE_LITERAL_STR &&
            expr_child(e, i)->type != NODE_LITERAL_BOOL) continue;

        // Skip hoisting inline compound field args in struct constructors
        if (ctor_body) {
            // Find the fi-th instance field
            int is_own = 0;
            TilType ft = TIL_TYPE_NONE;
            for (; fi < ctor_body->children.len; fi++) {
                Expr *field = expr_child(ctor_body, fi);
                if (!field->data.decl.is_namespace) {
                    is_own = field->data.decl.is_own;
                    ft = expr_child(field, 0)->til_type;
                    fi++;
                    break;
                }
            }
            if (!is_own && (ft == TIL_TYPE_STR || ft == TIL_TYPE_STRUCT || ft == TIL_TYPE_ENUM))
                continue; // don't hoist — ccodegen handles directly
        }

        expr_child(e, i) = hoist_to_temp(expr_child(e, i), hoisted, nhoisted, cap, scope);
    }
}

static void hoist_fcall_args(Expr *body, TypeScope *scope) {
    Vec new_ch = Vec_new(sizeof(Expr *));
    for (int i = 0; i < body->children.len; i++) {
        Expr *stmt = expr_child(body, i);
        // Collect hoisted decls from this statement
        Expr **hoisted = NULL;
        int nhoisted = 0, hcap = 0;
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
            if (stmt->children.len > 0) {
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
            int do_hoist = 1;
            TypeBinding *ab = tscope_find(scope, stmt->data.str_val);
            if (ab && !ab->is_param) {
                TilType t = ab->type;
                if (t == TIL_TYPE_STR || t == TIL_TYPE_STRUCT || t == TIL_TYPE_ENUM)
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
            int fa_hoist = 1;
            if (!stmt->is_own_field) {
                TilType ft = expr_child(stmt, 1)->til_type;
                if (ft == TIL_TYPE_STR || ft == TIL_TYPE_STRUCT || ft == TIL_TYPE_ENUM)
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
        for (int j = 0; j < nhoisted; j++)
            Vec_push(&new_ch, &hoisted[j]);
        free(hoisted);
        // Add original statement
        Vec_push(&new_ch, &stmt);
    }
    if (new_ch.len != body->children.len) {
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
        case TIL_TYPE_STR:  return "Str";
        case TIL_TYPE_BOOL: return "Bool";
        default: return NULL;
    }
}

static Expr *make_delete_call(Str *var_name, TilType type, Str *struct_name, int line, int col) {
    const char *tname = type_to_name(type, struct_name);
    if (!tname) return NULL;

    Expr *call = expr_new(NODE_FCALL, line, col);
    call->til_type = TIL_TYPE_NONE;

    Expr *type_id = expr_new(NODE_IDENT, line, col);
    type_id->data.str_val = Str_new(tname);
    type_id->struct_name = Str_new(tname);

    Expr *fa = expr_new(NODE_FIELD_ACCESS, line, col);
    fa->data.str_val = Str_new("delete");
    fa->is_ns_field = true;
    expr_add_child(fa, type_id);
    expr_add_child(call, fa);

    Expr *arg = expr_new(NODE_IDENT, line, col);
    arg->data.str_val = var_name;
    arg->til_type = type;
    arg->struct_name = struct_name;
    arg->is_own_arg = true;
    expr_add_child(call, arg);

    // call_free=true (ASAP delete should free the top-level allocation)
    Expr *true_lit = expr_new(NODE_LITERAL_BOOL, line, col);
    true_lit->data.str_val = Str_new("true");
    true_lit->til_type = TIL_TYPE_BOOL;
    expr_add_child(call, true_lit);

    return call;
}

// Build Type.delete(obj.field, call_free) for field reassignment.
// is_own: true for own (pointer) fields, false for inline (value) fields.
static Expr *make_field_delete(Expr *field_assign, int is_own) {
    Expr *rhs = expr_child(field_assign, 1);
    const char *tname = type_to_name(rhs->til_type, rhs->struct_name);
    if (!tname) return NULL;
    int line = field_assign->line, col = field_assign->col;

    Expr *call = expr_new(NODE_FCALL, line, col);
    call->til_type = TIL_TYPE_NONE;

    Expr *type_id = expr_new(NODE_IDENT, line, col);
    type_id->data.str_val = Str_new(tname);
    type_id->struct_name = Str_new(tname);

    Expr *fa = expr_new(NODE_FIELD_ACCESS, line, col);
    fa->data.str_val = Str_new("delete");
    fa->is_ns_field = true;
    expr_add_child(fa, type_id);
    expr_add_child(call, fa);

    // arg: obj.field_name (clone the obj expr, build field access)
    Expr *field_acc = expr_new(NODE_FIELD_ACCESS, line, col);
    field_acc->data.str_val = field_assign->data.str_val;
    field_acc->is_own_field = is_own;
    field_acc->til_type = rhs->til_type;
    field_acc->struct_name = rhs->struct_name;
    expr_add_child(field_acc, expr_clone(expr_child(field_assign, 0)));
    expr_add_child(call, field_acc);

    Expr *cf_lit = expr_new(NODE_LITERAL_BOOL, line, col);
    cf_lit->data.str_val = Str_new(is_own ? "true" : "false");
    cf_lit->til_type = TIL_TYPE_BOOL;
    expr_add_child(call, cf_lit);

    return call;
}

// Insert delete calls before field reassignments (own and inline compound)
static void insert_field_deletes(Expr *body) {
    Vec new_ch = Vec_new(sizeof(Expr *));
    int changed = 0;

    for (int i = 0; i < body->children.len; i++) {
        Expr *stmt = expr_child(body, i);
        if (stmt->type == NODE_FIELD_ASSIGN) {
            int need_delete = 0;
            int is_own = stmt->is_own_field;
            if (is_own) {
                need_delete = 1;
            } else {
                TilType ft = expr_child(stmt, 1)->til_type;
                if (ft == TIL_TYPE_STR || ft == TIL_TYPE_STRUCT || ft == TIL_TYPE_ENUM)
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

static Expr *make_clone_call(const char *type_name, TilType type, Expr *arg, int line, int col) {
    Expr *call = expr_new(NODE_FCALL, line, col);
    call->til_type = type;
    call->struct_name = (type == TIL_TYPE_STRUCT || type == TIL_TYPE_ENUM) ? Str_new(type_name) : NULL;

    Expr *type_id = expr_new(NODE_IDENT, line, col);
    type_id->data.str_val = Str_new(type_name);
    type_id->struct_name = Str_new(type_name);

    Expr *fa = expr_new(NODE_FIELD_ACCESS, line, col);
    fa->data.str_val = Str_new("clone");
    fa->is_ns_field = true;
    expr_add_child(fa, type_id);
    expr_add_child(call, fa);

    expr_add_child(call, arg);
    return call;
}

static int expr_uses_var(Expr *e, Str *name) {
    if (e->type == NODE_FUNC_DEF) return 0;
    if (e->type == NODE_IDENT && Str_eq(e->data.str_val, name)) return 1;
    if (e->type == NODE_ASSIGN && Str_eq(e->data.str_val, name)) return 1;
    for (int i = 0; i < e->children.len; i++) {
        if (expr_uses_var(expr_child(e, i), name)) return 1;
    }
    return 0;
}

static int expr_contains_decl(Expr *e, Str *name) {
    if (e->type == NODE_FUNC_DEF) return 0;
    if (e->type == NODE_DECL && Str_eq(e->data.decl.name, name)) return 1;
    for (int i = 0; i < e->children.len; i++) {
        if (expr_contains_decl(expr_child(e, i), name)) return 1;
    }
    return 0;
}

// Helper: given a func_def, check if var_name is passed to an own param
static int check_own_args(Expr *fdef, Expr *fcall, Str *var_name) {
    bool *po = fdef->data.func_def.param_owns;
    if (!po) return 0;
    int np = fdef->data.func_def.nparam;
    for (int i = 0; i < np && i + 1 < fcall->children.len; i++) {
        if (po[i] && expr_child(fcall, i + 1)->type == NODE_IDENT &&
            Str_eq(expr_child(fcall, i + 1)->data.str_val, var_name)) {
            return 1;
        }
    }
    return 0;
}

static int fcall_has_own_arg(Expr *fcall, Str *var_name, TypeScope *scope) {
    if (fcall->type != NODE_FCALL || fcall->children.len < 2) return 0;
    // Struct constructor: check if var is in an own field position
    if (fcall->struct_name && expr_child(fcall, 0)->type == NODE_IDENT &&
        Str_eq(expr_child(fcall, 0)->data.str_val, fcall->struct_name)) {
        Expr *sdef = tscope_get_struct(scope, fcall->struct_name);
        if (sdef) {
            Expr *body = expr_child(sdef, 0);
            int fi = 0;
            for (int i = 0; i < body->children.len; i++) {
                if (expr_child(body, i)->type != NODE_DECL ||
                    expr_child(body, i)->data.decl.is_namespace) continue;
                int arg_idx = fi + 1;
                fi++;
                if (arg_idx < fcall->children.len &&
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
        for (int i = 0; i < body->children.len; i++) {
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

static int expr_transfers_own(Expr *e, Str *var_name, TypeScope *scope) {
    if (e->type == NODE_FUNC_DEF) return 0;
    if (fcall_has_own_arg(e, var_name, scope)) return 1;
    // Own field assignment: RHS ownership transfers to the field
    if (e->type == NODE_FIELD_ASSIGN && e->is_own_field &&
        expr_child(e, 1)->type == NODE_IDENT &&
        Str_eq(expr_child(e, 1)->data.str_val, var_name)) {
        return 1;
    }
    for (int i = 0; i < e->children.len; i++) {
        if (expr_transfers_own(expr_child(e, i), var_name, scope)) return 1;
    }
    return 0;
}

typedef struct {
    Str *name;
    TilType type;
    Str *struct_name;
    int decl_index;
    int last_use;
    int own_transfer;  // index of stmt that transfers ownership, -1 if none
} LocalInfo;

// Insert deletes for live parent-scope locals before early exits in body.
// return_only=1: only before NODE_RETURN (used when propagating into while bodies,
// since break/continue don't leave the parent scope).
static void insert_exit_deletes(Expr *body, LocalInfo *live, int n_live, int return_only) {
    Vec new_ch = Vec_new(sizeof(Expr *));
    for (int i = 0; i < body->children.len; i++) {
        Expr *stmt = expr_child(body, i);
        if (stmt->type == NODE_IF) {
            for (int c = 1; c < stmt->children.len; c++)
                insert_exit_deletes(expr_child(stmt, c), live, n_live, return_only);
        }
        if (stmt->type == NODE_WHILE) {
            insert_exit_deletes(expr_child(stmt, 1), live, n_live, 1);
        }
        if (stmt->type == NODE_RETURN ||
            (!return_only && (stmt->type == NODE_BREAK || stmt->type == NODE_CONTINUE))) {
            for (int j = 0; j < n_live; j++) {
                if (stmt->children.len > 0 &&
                    expr_uses_var(expr_child(stmt, 0), live[j].name)) continue;
                Expr *del = make_delete_call(
                    live[j].name, live[j].type, live[j].struct_name,
                    stmt->line, stmt->col);
                if (del) Vec_push(&new_ch, &del);
            }
        }
        Vec_push(&new_ch, &stmt);
    }
    if (new_ch.len != body->children.len) {
        Vec_delete(&body->children);
        body->children = new_ch;
    } else {
        Vec_delete(&new_ch);
    }
}

static void insert_free_calls(Expr *body, TypeScope *scope, int scope_exit, const char *path) {
    if (!scope_exit) return;

    // Phase 1: collect locals with lifetime info
    // Start from 0 (not locals_start) to include own params, which are added before the body
    Vec locals_vec = Vec_new(sizeof(LocalInfo));
    for (int i = 0; i < Map_len(&scope->bindings); i++) {
        TypeBinding *b = (TypeBinding *)Vec_get(&scope->bindings.vals, i);
        if ((b->is_param && !b->is_own) || b->struct_def || b->func_def || b->is_ref) continue;

        // Find decl_index: direct child first, then nested
        int decl_idx = -1;
        for (int j = 0; j < body->children.len; j++) {
            Expr *s = expr_child(body, j);
            if (s->type == NODE_DECL && Str_eq(s->data.decl.name, b->name)) {
                decl_idx = j;
                break;
            }
        }
        if (decl_idx == -1) {
            for (int j = 0; j < body->children.len; j++) {
                if (expr_contains_decl(expr_child(body, j), b->name)) {
                    decl_idx = j;
                    break;
                }
            }
        }

        // Find last_use and own_transfer
        int last_use = -1;
        int own_transfer = -1;
        int scan_from = decl_idx >= 0 ? decl_idx + 1 : 0;
        for (int j = scan_from; j < body->children.len; j++) {
            if (expr_uses_var(expr_child(body, j), b->name)) {
                last_use = j;
            }
            if (own_transfer == -1 && expr_transfers_own(expr_child(body, j), b->name, scope)) {
                own_transfer = j;
            }
        }

        LocalInfo li = {b->name, b->type, b->struct_name, decl_idx, last_use, own_transfer};
        Vec_push(&locals_vec, &li);
    }

    if (locals_vec.len == 0) { Vec_delete(&locals_vec); return; }
    int n_locals = locals_vec.len;
    LocalInfo *locals = Vec_take(&locals_vec);

    // Extend lifetimes for args to ref-returning calls:
    // If ref m := f(x, y), then x and y must outlive m
    for (int i = 0; i < body->children.len; i++) {
        Expr *stmt = expr_child(body, i);
        if (stmt->type != NODE_DECL || !stmt->data.decl.is_ref) continue;
        Expr *rhs = expr_child(stmt, 0);
        if (rhs->type != NODE_FCALL) continue;
        // Find ref var's last_use (scan forward from decl)
        int ref_last = -1;
        for (int j = i + 1; j < body->children.len; j++) {
            if (expr_uses_var(expr_child(body, j), stmt->data.decl.name))
                ref_last = j;
        }
        if (ref_last == -1) ref_last = i; // at least until the decl itself
        // Extend last_use of all ident args in the fcall
        for (int a = 1; a < rhs->children.len; a++) {
            if (expr_child(rhs, a)->type != NODE_IDENT) continue;
            Str *aname = expr_child(rhs, a)->data.str_val;
            for (int j = 0; j < n_locals; j++) {
                if (Str_eq(locals[j].name, aname) && locals[j].last_use < ref_last) {
                    locals[j].last_use = ref_last;
                }
            }
        }
    }

    // Check for use after ownership transfer
    for (int j = 0; j < n_locals; j++) {
        if (locals[j].own_transfer >= 0 && locals[j].last_use > locals[j].own_transfer) {
            Expr *stmt = expr_child(body, locals[j].last_use);
            char buf[128];
            snprintf(buf, sizeof(buf), "use of '%s' after ownership transfer", locals[j].name->c_str);
            type_error(path, stmt, buf);
            Expr *xfer = expr_child(body, locals[j].own_transfer);
            fprintf(stderr, "%s:%d:%d: note: ownership transferred here\n",
                    path, xfer->line, xfer->col);
            fprintf(stderr, "  help: pass a clone instead: own %s.clone()\n",
                    locals[j].name->c_str);
        }
    }

    // Phase 2: rebuild body with ASAP frees
    Vec new_ch = Vec_new(sizeof(Expr *));

    for (int i = 0; i < body->children.len; i++) {
        Expr *stmt = expr_child(body, i);

        // Before NODE_RETURN/NODE_BREAK/NODE_CONTINUE: free locals not yet freed
        if (stmt->type == NODE_RETURN || stmt->type == NODE_BREAK || stmt->type == NODE_CONTINUE) {
            for (int j = 0; j < n_locals; j++) {
                if (stmt->children.len > 0 && expr_uses_var(expr_child(stmt, 0), locals[j].name)) continue;
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].decl_index < i &&
                    (locals[j].last_use >= i || locals[j].last_use == -1)) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt->line, stmt->col);
                    if (del) Vec_push(&new_ch, &del);
                }
            }
        }

        // For NODE_IF/NODE_WHILE: insert frees before nested early exits
        if (stmt->type == NODE_IF || stmt->type == NODE_WHILE) {
            Vec live_vec = Vec_new(sizeof(LocalInfo));
            for (int j = 0; j < n_locals; j++) {
                if (locals[j].own_transfer >= 0) continue;
                if (locals[j].decl_index < i &&
                    (locals[j].last_use >= i || locals[j].last_use == -1)) {
                    Vec_push(&live_vec, &locals[j]);
                }
            }
            if (live_vec.len > 0) {
                int n_live = live_vec.len;
                LocalInfo *live = Vec_take(&live_vec);
                if (stmt->type == NODE_IF) {
                    for (int c = 1; c < stmt->children.len; c++)
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
            for (int j = 0; j < n_locals; j++) {
                if (!Str_eq(locals[j].name, vname)) continue;
                TilType t = locals[j].type;
                if (t == TIL_TYPE_STR || t == TIL_TYPE_STRUCT || t == TIL_TYPE_ENUM) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt->line, stmt->col);
                    if (del) Vec_push(&new_ch, &del);
                }
                break;
            }
        }

        // Add original statement
        Vec_push(&new_ch, &stmt);

        // After non-exit statements: free locals whose last use is this statement
        if (stmt->type != NODE_RETURN && stmt->type != NODE_BREAK && stmt->type != NODE_CONTINUE) {
            for (int j = 0; j < n_locals; j++) {
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].last_use == i) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt->line, stmt->col);
                    if (del) Vec_push(&new_ch, &del);
                }
                // Never used after declaration: free immediately
                if (locals[j].last_use == -1 && locals[j].decl_index == i) {
                    Expr *del = make_delete_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt->line, stmt->col);
                    if (del) Vec_push(&new_ch, &del);
                }
            }
        }
    }

    Vec_delete(&body->children);
    body->children = new_ch;
    free(locals);
}

static void infer_body(TypeScope *scope, Expr *body, const char *path, int in_func, int owns_scope, int in_loop) {
    body->til_type = TIL_TYPE_NONE;
    for (int i = 0; i < body->children.len; i++) {
        Expr *stmt = expr_child(body, i);
        switch (stmt->type) {
        case NODE_DECL:
            // Skip variant registry entries (payload enum: no children)
            if (stmt->children.len == 0) break;
            infer_expr(scope, expr_child(stmt, 0), path, in_func);
            // For struct/enum defs, register type in scope
            if (expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
                int is_enum = (expr_child(stmt, 0)->type == NODE_ENUM_DEF);
                // Check explicit type annotation if present
                if (stmt->data.decl.explicit_type) {
                    TilType declared = type_from_name(stmt->data.decl.explicit_type, scope);
                    TilType expected = is_enum ? TIL_TYPE_ENUM_DEF : TIL_TYPE_STRUCT_DEF;
                    if (declared != expected) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                                 stmt->data.decl.name->c_str, stmt->data.decl.explicit_type->c_str,
                                 is_enum ? "EnumDef" : "StructDef");
                        type_error(path, stmt, buf);
                    }
                }
                stmt->til_type = TIL_TYPE_NONE;
                Str *sname = stmt->data.decl.name;
                // Check if this is a builtin type
                TilType builtin_type = is_enum ? TIL_TYPE_ENUM : TIL_TYPE_STRUCT;
                int is_builtin = 0;
                if (Str_eq_c(sname, "I64"))  { builtin_type = TIL_TYPE_I64;  is_builtin = 1; }
                else if (Str_eq_c(sname, "U8"))   { builtin_type = TIL_TYPE_U8;   is_builtin = 1; }
                else if (Str_eq_c(sname, "Str"))  { builtin_type = TIL_TYPE_STR;  is_builtin = 1; }
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
                        type_error(path, stmt, buf);
                    }
                }
                FuncType ft = expr_child(stmt, 0)->data.func_def.func_type;
                int callee_is_proc = (ft == FUNC_PROC || ft == FUNC_EXT_PROC);
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
                    type_error(path, stmt, buf);
                } else if (expr_child(stmt, 0)->type == NODE_LITERAL_NUM &&
                           (declared == TIL_TYPE_I64 || declared == TIL_TYPE_U8 || declared == TIL_TYPE_DYNAMIC)) {
                    // Numeric literals can be used with numeric types and Dynamic (0 = null)
                    expr_child(stmt, 0)->til_type = declared;
                } else if (expr_child(stmt, 0)->til_type != declared &&
                           expr_child(stmt, 0)->til_type != TIL_TYPE_DYNAMIC) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.decl.name->c_str, til_type_name_c(declared),
                             til_type_name_c(expr_child(stmt, 0)->til_type));
                    type_error(path, stmt, buf);
                } else if ((declared == TIL_TYPE_STRUCT || declared == TIL_TYPE_ENUM) &&
                           expr_child(stmt, 0)->struct_name &&
                           !Str_eq(etn, expr_child(stmt, 0)->struct_name)) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.decl.name->c_str, etn->c_str, expr_child(stmt, 0)->struct_name->c_str);
                    type_error(path, stmt, buf);
                }
                stmt->til_type = declared;
                // For struct/enum types, propagate struct_name from explicit type
                if (declared == TIL_TYPE_STRUCT || declared == TIL_TYPE_ENUM) {
                    expr_child(stmt, 0)->struct_name = etn;
                }
            } else {
                stmt->til_type = expr_child(stmt, 0)->til_type;
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
                int ok = 0;
                if (rhs->type == NODE_FCALL && fcall_returns_ref(rhs, scope)) ok = 1;
                if (rhs->type == NODE_IDENT) {
                    TypeBinding *rb = tscope_find(scope, rhs->data.str_val);
                    if (rb && (rb->is_ref || (rb->is_param && !rb->is_own))) ok = 1;
                }
                if (!ok) type_error(path, stmt, "'ref' declaration requires a ref-returning function or ref/param variable");
            }
            // Auto-insert clone for declarations from identifiers (skip ref decls)
            if (expr_child(stmt, 0)->type == NODE_IDENT && !stmt->data.decl.is_ref) {
                const char *tname = type_to_name(stmt->til_type, expr_child(stmt, 0)->struct_name);
                if (tname) {
                    expr_child(stmt, 0) = make_clone_call(
                        tname, stmt->til_type,
                        expr_child(stmt, 0),
                        stmt->line, stmt->col);
                }
            }
            break;
        case NODE_ASSIGN: {
            infer_expr(scope, expr_child(stmt, 0), path, in_func);
            stmt->til_type = expr_child(stmt, 0)->til_type;
            Str *aname = stmt->data.str_val;
            TilType existing = tscope_get(scope, aname);
            if (existing == TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined symbol '%s'", aname->c_str);
                type_error(path, stmt, buf);
            } else if (!tscope_is_mut(scope, aname)) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot assign to immutable variable '%s'", aname->c_str);
                type_error(path, stmt, buf);
                TypeBinding *b = tscope_find(scope, aname);
                if (b && b->is_param) {
                    fprintf(stderr, "%s:%d:%d: note: '%s' is a function parameter\n",
                            path, b->line, b->col, aname->c_str);
                } else if (b) {
                    fprintf(stderr, "%s:%d:%d: note: '%s' declared here, consider adding 'mut'\n",
                            path, b->line, b->col, aname->c_str);
                }
            } else if (expr_child(stmt, 0)->til_type != existing &&
                       expr_child(stmt, 0)->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "'%s' is %s but assigned %s",
                         aname->c_str, til_type_name_c(existing),
                         til_type_name_c(expr_child(stmt, 0)->til_type));
                type_error(path, stmt, buf);
            }
            // Auto-insert clone for assignments from identifiers
            if (expr_child(stmt, 0)->type == NODE_IDENT) {
                const char *tname = type_to_name(expr_child(stmt, 0)->til_type, expr_child(stmt, 0)->struct_name);
                if (tname) {
                    expr_child(stmt, 0) = make_clone_call(
                        tname, expr_child(stmt, 0)->til_type,
                        expr_child(stmt, 0),
                        stmt->line, stmt->col);
                }
            }
            break;
        }
        case NODE_FIELD_ASSIGN: {
            infer_expr(scope, expr_child(stmt, 0), path, in_func); // object
            infer_expr(scope, expr_child(stmt, 1), path, in_func); // value
            Expr *obj = expr_child(stmt, 0);
            Str *fname = stmt->data.str_val;
            if (obj->struct_name) {
                Expr *sdef = tscope_get_struct(scope, obj->struct_name);
                if (sdef) {
                    Expr *body = expr_child(sdef, 0);
                    int found = 0;
                    for (int i = 0; i < body->children.len; i++) {
                        Expr *field = expr_child(body, i);
                        if (Str_eq(field->data.decl.name, fname)) {
                            found = 1;
                            stmt->is_ns_field = field->data.decl.is_namespace;
                            stmt->is_own_field = field->data.decl.is_own;
                            if (!field->data.decl.is_mut) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "cannot assign to immutable field '%s'", fname->c_str);
                                type_error(path, stmt, buf);
                            }
                            if (expr_child(stmt, 1)->til_type != field->til_type &&
                                expr_child(stmt, 1)->til_type != TIL_TYPE_UNKNOWN &&
                                expr_child(stmt, 1)->til_type != TIL_TYPE_DYNAMIC) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "field '%s' is %s but assigned %s",
                                         fname->c_str, til_type_name_c(field->til_type),
                                         til_type_name_c(expr_child(stmt, 1)->til_type));
                                type_error(path, stmt, buf);
                            }
                            break;
                        }
                    }
                    if (!found) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'",
                                 obj->struct_name->c_str, fname->c_str);
                        type_error(path, stmt, buf);
                    }
                }
            } else {
                type_error(path, stmt, "field assignment on non-struct value");
            }
            stmt->til_type = TIL_TYPE_NONE;
            // Auto-insert clone for field assignments from identifiers
            if (expr_child(stmt, 1)->type == NODE_IDENT) {
                const char *tname = type_to_name(expr_child(stmt, 1)->til_type,
                                                  expr_child(stmt, 1)->struct_name);
                if (tname) {
                    expr_child(stmt, 1) = make_clone_call(tname,
                        expr_child(stmt, 1)->til_type, expr_child(stmt, 1),
                        expr_child(stmt, 1)->line, expr_child(stmt, 1)->col);
                }
            }
            break;
        }
        case NODE_FCALL:
            infer_expr(scope, stmt, path, in_func);
            break;
        case NODE_RETURN:
            if (stmt->children.len > 0) {
                infer_expr(scope, expr_child(stmt, 0), path, in_func);
                stmt->til_type = expr_child(stmt, 0)->til_type;
            } else {
                stmt->til_type = TIL_TYPE_NONE;
            }
            break;
        case NODE_BREAK:
            if (!in_loop) {
                type_error(path, stmt, "break outside loop");
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        case NODE_CONTINUE:
            if (!in_loop) {
                type_error(path, stmt, "continue outside loop");
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        case NODE_IF:
            infer_expr(scope, expr_child(stmt, 0), path, in_func); // condition
            if (expr_child(stmt, 0)->til_type != TIL_TYPE_BOOL &&
                expr_child(stmt, 0)->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "if condition must be Bool, got %s",
                         til_type_name_c(expr_child(stmt, 0)->til_type));
                type_error(path, stmt, buf);
            }
            {
                TypeScope *then_scope = tscope_new(scope);
                infer_body(then_scope, expr_child(stmt, 1), path, in_func, 1, in_loop);
                tscope_free(then_scope);
            }
            if (stmt->children.len > 2) {
                TypeScope *else_scope = tscope_new(scope);
                infer_body(else_scope, expr_child(stmt, 2), path, in_func, 1, in_loop);
                tscope_free(else_scope);
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        case NODE_BODY: {
            TypeScope *block_scope = tscope_new(scope);
            infer_body(block_scope, stmt, path, in_func, 1, in_loop);
            tscope_free(block_scope);
            break;
        }
        case NODE_WHILE:
            infer_expr(scope, expr_child(stmt, 0), path, in_func); // condition
            if (expr_child(stmt, 0)->til_type != TIL_TYPE_BOOL &&
                expr_child(stmt, 0)->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "while condition must be Bool, got %s",
                         til_type_name_c(expr_child(stmt, 0)->til_type));
                type_error(path, stmt, buf);
            }
            // Transform: while COND { BODY } -> while true { _wcond := COND; if _wcond {} else { break }; BODY }
            // This lets ASAP destruction free the condition result each iteration.
            if (expr_contains_fcall(expr_child(stmt, 0))) {
                int line = expr_child(stmt, 0)->line;
                int col = expr_child(stmt, 0)->col;
                Expr *cond = expr_child(stmt, 0);
                Expr *body = expr_child(stmt, 1);
                // _wcondN := COND
                char name_buf[32];
                snprintf(name_buf, sizeof(name_buf), "_wcond%d", hoist_counter++);
                Str *wname = Str_new(name_buf);
                Expr *decl = expr_new(NODE_DECL, line, col);
                decl->data.decl.name = wname;
                decl->data.decl.explicit_type = NULL;
                decl->data.decl.is_mut = false;
                decl->data.decl.is_namespace = false;
                decl->til_type = cond->til_type;
                expr_add_child(decl, cond);
                // if _wcondN {} else { break }
                Expr *ident = expr_new(NODE_IDENT, line, col);
                ident->data.str_val = wname;
                ident->til_type = TIL_TYPE_BOOL;
                Expr *if_node = expr_new(NODE_IF, line, col);
                if_node->til_type = TIL_TYPE_NONE;
                expr_add_child(if_node, ident);
                Expr *then_body = expr_new(NODE_BODY, line, col);
                then_body->til_type = TIL_TYPE_NONE;
                expr_add_child(if_node, then_body);
                Expr *else_body = expr_new(NODE_BODY, line, col);
                else_body->til_type = TIL_TYPE_NONE;
                Expr *brk = expr_new(NODE_BREAK, line, col);
                brk->til_type = TIL_TYPE_NONE;
                expr_add_child(else_body, brk);
                expr_add_child(if_node, else_body);
                // Prepend decl + if to body
                Vec new_ch = Vec_new(sizeof(Expr *));
                Vec_push(&new_ch, &decl);
                Vec_push(&new_ch, &if_node);
                for (int j = 0; j < body->children.len; j++) {
                    Expr *ch = expr_child(body, j);
                    Vec_push(&new_ch, &ch);
                }
                Vec_delete(&body->children);
                body->children = new_ch;
                // Replace condition with true
                Expr *true_lit = expr_new(NODE_LITERAL_BOOL, line, col);
                true_lit->data.str_val = Str_new("true");
                true_lit->til_type = TIL_TYPE_BOOL;
                expr_child(stmt, 0) = true_lit;
            }
            {
                TypeScope *while_scope = tscope_new(scope);
                infer_body(while_scope, expr_child(stmt, 1), path, in_func, 1, 1);
                tscope_free(while_scope);
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        default:
            stmt->til_type = TIL_TYPE_NONE;
            break;
        }
    }
    if (owns_scope) hoist_fcall_args(body, scope);
    insert_field_deletes(body);
    insert_free_calls(body, scope, owns_scope, path);
}

int type_check(Expr *program, const char *path, TypeScope *scope) {
    errors = 0;
    infer_body(scope, program, path, 0, 1, 0);
    return errors;
}
