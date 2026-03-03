#include "typer.h"
#include "initer.h"
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
static TilType type_from_name(const char *name, TypeScope *scope) {
    if (strcmp(name, "I64") == 0)  return TIL_TYPE_I64;
    if (strcmp(name, "U8") == 0)   return TIL_TYPE_U8;
    if (strcmp(name, "Str") == 0)  return TIL_TYPE_STR;
    if (strcmp(name, "Bool") == 0) return TIL_TYPE_BOOL;
    if (strcmp(name, "StructDef") == 0)    return TIL_TYPE_STRUCT_DEF;
    if (strcmp(name, "FunctionDef") == 0)  return TIL_TYPE_FUNC_DEF;
    if (strcmp(name, "Dynamic") == 0)     return TIL_TYPE_DYNAMIC;
    // Check scope for user-defined struct types
    if (scope) {
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) return TIL_TYPE_STRUCT;
    }
    return TIL_TYPE_UNKNOWN;
}

static void infer_expr(TypeScope *scope, Expr *e, const char *path, int in_func);
static void infer_body(TypeScope *scope, Expr *body, const char *path, int in_func, int owns_scope);

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
            snprintf(buf, sizeof(buf), "undefined symbol '%s'", e->data.str_val);
            type_error(path, e, buf);
        }
        e->til_type = t;
        if (t == TIL_TYPE_STRUCT) {
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
            TypeScope *func_scope = tscope_new(scope);
            // Bind parameters
            for (int i = 0; i < e->data.func_def.nparam; i++) {
                const char *ptn = e->data.func_def.param_types[i];
                TilType pt = type_from_name(ptn, scope);
                if (pt == TIL_TYPE_UNKNOWN) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", ptn);
                    type_error(path, e, buf);
                }
                int pmut = e->data.func_def.param_muts ? e->data.func_def.param_muts[i] : 0;
                int pown = e->data.func_def.param_owns ? e->data.func_def.param_owns[i] : 0;
                tscope_set(func_scope, e->data.func_def.param_names[i], pt, -1, pmut, e->line, e->col, 1, pown);
                // For struct-typed params, store struct_name
                if (pt == TIL_TYPE_STRUCT) {
                    TypeBinding *pb = tscope_find(func_scope, e->data.func_def.param_names[i]);
                    if (pb) pb->struct_name = ptn;
                }
            }
            infer_body(func_scope, e->children[0], path, is_func, 1);
            // Check: func must have a return type
            if (is_func && !e->data.func_def.return_type) {
                type_error(path, e, "func must declare a return type");
            }
            tscope_free(func_scope);
        }
        break;
    case NODE_STRUCT_DEF: {
        e->til_type = TIL_TYPE_NONE;
        // Type-check field declarations (save/restore scope len so fields
        // don't leak into outer scope's locals for free-call insertion)
        int saved_len = scope->len;
        infer_body(scope, e->children[0], path, 0, 0);
        scope->len = saved_len;
        break;
    }
    case NODE_FCALL: {
        // Namespace method call or UFCS: Type.method(args) or instance.method(args)
        if (e->children[0]->type == NODE_FIELD_ACCESS) {
            Expr *fa = e->children[0];
            Expr *obj = fa->children[0];
            const char *method = fa->data.str_val;

            // Type just the object first (not the full field access)
            infer_expr(scope, obj, path, in_func);

            // Check: is obj a type name (has struct_def) or an instance/value?
            TypeBinding *tb = (obj->type == NODE_IDENT)
                ? tscope_find(scope, obj->data.str_val) : NULL;
            int obj_is_type = (tb && tb->struct_def);

            if (!obj_is_type) {
                // UFCS: instance.method(args) → Type.method(instance, args)
                const char *type_name = NULL;
                if (obj->til_type == TIL_TYPE_I64)  type_name = "I64";
                else if (obj->til_type == TIL_TYPE_U8)   type_name = "U8";
                else if (obj->til_type == TIL_TYPE_BOOL) type_name = "Bool";
                else if (obj->til_type == TIL_TYPE_STR)  type_name = "Str";
                else if (obj->til_type == TIL_TYPE_STRUCT && obj->struct_name)
                    type_name = obj->struct_name;

                Expr *sdef = type_name ? tscope_get_struct(scope, type_name) : NULL;
                Expr *ns_func = NULL;
                if (sdef) {
                    Expr *body = sdef->children[0];
                    for (int i = 0; i < body->nchildren; i++) {
                        Expr *field = body->children[i];
                        if (field->data.decl.is_namespace &&
                            strcmp(field->data.decl.name, method) == 0 &&
                            field->children[0]->type == NODE_FUNC_DEF) {
                            ns_func = field->children[0];
                            break;
                        }
                    }
                }
                if (!ns_func) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "no method '%s' for type '%s'",
                             method, type_name ? type_name : "unknown");
                    type_error(path, e, buf);
                    e->til_type = TIL_TYPE_UNKNOWN;
                    break;
                }
                // Desugar: rewrite AST to Type.method(instance, args)
                Expr *instance = obj;
                Expr *type_ident = expr_new(NODE_IDENT, obj->line, obj->col);
                type_ident->data.str_val = type_name;
                fa->children[0] = type_ident;
                // Insert instance as first arg
                e->children = realloc(e->children, (e->nchildren + 1) * sizeof(Expr *));
                memmove(&e->children[2], &e->children[1], (e->nchildren - 1) * sizeof(Expr *));
                e->children[1] = instance;
                e->nchildren++;
                // Fall through — existing code below handles Type.method(instance, args)
            }

            // Type the (possibly new) object and look up namespace func
            obj = fa->children[0];
            if (obj->til_type == TIL_TYPE_UNKNOWN) {
                infer_expr(scope, obj, path, in_func);
            }
            Expr *sdef = obj->struct_name ? tscope_get_struct(scope, obj->struct_name) : NULL;
            Expr *ns_func = NULL;
            if (sdef) {
                Expr *body = sdef->children[0];
                for (int i = 0; i < body->nchildren; i++) {
                    Expr *field = body->children[i];
                    if (field->data.decl.is_namespace &&
                        strcmp(field->data.decl.name, method) == 0 &&
                        field->children[0]->type == NODE_FUNC_DEF) {
                        ns_func = field->children[0];
                        break;
                    }
                }
            }
            if (!ns_func) {
                char buf[128];
                snprintf(buf, sizeof(buf), "no namespace function '%s'", method);
                type_error(path, e, buf);
                e->til_type = TIL_TYPE_UNKNOWN;
                break;
            }
            // Infer arg types
            for (int i = 1; i < e->nchildren; i++) {
                infer_expr(scope, e->children[i], path, in_func);
            }
            // Set return type
            TilType rt = TIL_TYPE_NONE;
            if (ns_func->data.func_def.return_type) {
                rt = type_from_name(ns_func->data.func_def.return_type, scope);
            }
            e->til_type = rt;
            break;
        }
        // Resolve callee
        const char *name = e->children[0]->data.str_val;
        // Struct instantiation: Point() or Point(x=1, y=2)
        Expr *sdef = tscope_get_struct(scope, name);
        if (sdef) {
            TypeBinding *sb = tscope_find(scope, name);
            if (sb && sb->is_builtin) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot instantiate builtin type '%s'", name);
                type_error(path, e, buf);
                e->til_type = TIL_TYPE_UNKNOWN;
                break;
            }
            Expr *body = sdef->children[0];
            // Count instance fields (skip namespace)
            int nfields = 0;
            for (int i = 0; i < body->nchildren; i++) {
                if (!body->children[i]->data.decl.is_namespace) nfields++;
            }
            // Desugar named args into positional (one per instance field)
            Expr **field_vals = calloc(nfields, sizeof(Expr *));
            // Map: field_idx[k] = index into body->children for k-th instance field
            int *field_idx = malloc(nfields * sizeof(int));
            { int k = 0;
              for (int i = 0; i < body->nchildren; i++) {
                  if (!body->children[i]->data.decl.is_namespace) field_idx[k++] = i;
              }
            }
            for (int i = 1; i < e->nchildren; i++) {
                Expr *arg = e->children[i];
                if (arg->type != NODE_NAMED_ARG) {
                    type_error(path, arg, "struct instantiation requires named arguments");
                    continue;
                }
                const char *aname = arg->data.str_val;
                int slot = -1;
                for (int j = 0; j < nfields; j++) {
                    if (strcmp(body->children[field_idx[j]]->data.decl.name, aname) == 0) {
                        slot = j;
                        break;
                    }
                }
                if (slot < 0) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'", name, aname);
                    type_error(path, arg, buf);
                } else if (field_vals[slot]) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "duplicate argument for field '%s'", aname);
                    type_error(path, arg, buf);
                } else {
                    field_vals[slot] = arg->children[0]; // unwrap NODE_NAMED_ARG
                }
            }
            // Fill remaining from struct field defaults (clone to avoid shared ownership)
            for (int i = 0; i < nfields; i++) {
                if (!field_vals[i]) {
                    field_vals[i] = expr_clone(body->children[field_idx[i]]->children[0]);
                }
            }
            // Rebuild children: callee + instance field values
            Expr **new_children = malloc((nfields + 1) * sizeof(Expr *));
            new_children[0] = e->children[0]; // callee
            for (int i = 0; i < nfields; i++) {
                new_children[i + 1] = field_vals[i];
            }
            free(e->children);
            e->children = new_children;
            e->nchildren = nfields + 1;
            free(field_vals);
            free(field_idx);
            // Type-check args (skip already-inferred defaults)
            for (int i = 1; i < e->nchildren; i++) {
                if (e->children[i]->til_type == TIL_TYPE_UNKNOWN) {
                    infer_expr(scope, e->children[i], path, in_func);
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
            for (int i = 1; i < e->nchildren; i++) {
                Expr *arg = e->children[i];
                if (arg->type == NODE_NAMED_ARG) {
                    seen_named = 1;
                    const char *aname = arg->data.str_val;
                    int slot = -1;
                    for (int j = 0; j < nparam; j++) {
                        if (strcmp(fdef->data.func_def.param_names[j], aname) == 0) {
                            slot = j;
                            break;
                        }
                    }
                    if (slot < 0) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' has no parameter '%s'", name, aname);
                        type_error(path, arg, buf);
                    } else if (new_args[slot]) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "duplicate argument for parameter '%s'", aname);
                        type_error(path, arg, buf);
                    } else {
                        new_args[slot] = arg->children[0]; // unwrap NODE_NAMED_ARG
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
                                 fdef->data.func_def.param_names[i]);
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
            Expr **new_children = malloc((nparam + 1) * sizeof(Expr *));
            new_children[0] = e->children[0]; // callee
            for (int i = 0; i < nparam; i++) {
                new_children[i + 1] = new_args[i];
            }
            free(e->children);
            e->children = new_children;
            e->nchildren = nparam + 1;
            free(new_args);
        }
        // Infer types of all arguments
        for (int i = 1; i < e->nchildren; i++) {
            infer_expr(scope, e->children[i], path, in_func);
        }
        // Validate 'own' markers on arguments
        if (callee_bind && callee_bind->func_def) {
            Expr *fdef = callee_bind->func_def;
            bool *po = fdef->data.func_def.param_owns;
            for (int i = 1; i < e->nchildren && i - 1 < fdef->data.func_def.nparam; i++) {
                int pown = po ? po[i - 1] : 0;
                if (pown && !e->children[i]->is_own_arg) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "argument for 'own' parameter '%s' must be marked 'own'",
                             fdef->data.func_def.param_names[i - 1]);
                    type_error(path, e->children[i], buf);
                } else if (!pown && e->children[i]->is_own_arg) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'own' on argument but parameter '%s' is not 'own'",
                             fdef->data.func_def.param_names[i - 1]);
                    type_error(path, e->children[i], buf);
                }
            }
        }
        // Resolve return type from scope (covers builtins and user-defined)
        TilType fn_type = tscope_get(scope, name);
        if (fn_type == TIL_TYPE_UNKNOWN) {
            char buf[128];
            snprintf(buf, sizeof(buf), "undefined function '%s'", name);
            type_error(path, e, buf);
        }
        e->til_type = fn_type;
        // Propagate struct_name for struct-returning functions
        if (fn_type == TIL_TYPE_STRUCT && callee_bind && callee_bind->func_def &&
            callee_bind->func_def->data.func_def.return_type) {
            e->struct_name = callee_bind->func_def->data.func_def.return_type;
        }
        // Check: func cannot call proc (panic is exempt)
        if (in_func && tscope_is_proc(scope, name) == 1 && strcmp(name, "panic") != 0) {
            char buf[128];
            snprintf(buf, sizeof(buf), "func cannot call proc '%s'", name);
            type_error(path, e, buf);
        }
        break;
    }
    case NODE_FIELD_ACCESS: {
        infer_expr(scope, e->children[0], path, in_func);
        Expr *obj = e->children[0];
        if (obj->struct_name) {
            Expr *sdef = tscope_get_struct(scope, obj->struct_name);
            if (sdef) {
                Expr *body = sdef->children[0];
                const char *fname = e->data.str_val;
                int found = 0;
                for (int i = 0; i < body->nchildren; i++) {
                    Expr *field = body->children[i];
                    if (strcmp(field->data.decl.name, fname) == 0) {
                        e->til_type = field->til_type;
                        if (field->til_type == TIL_TYPE_STRUCT) {
                            e->struct_name = field->children[0]->struct_name;
                        } else {
                            e->struct_name = obj->struct_name;
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'",
                             obj->struct_name, fname);
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
    for (int i = 0; i < e->nchildren; i++) {
        if (expr_contains_fcall(e->children[i])) return 1;
    }
    return 0;
}

static int hoist_counter = 0;

// Create a temp decl for an expression, register in scope, return the replacement ident.
// Adds the decl to the hoisted list.
static Expr *hoist_to_temp(Expr *val, Expr ***hoisted, int *nhoisted, int *cap, TypeScope *scope) {
    char name_buf[32];
    snprintf(name_buf, sizeof(name_buf), "_t%d", hoist_counter++);
    const char *tname = strdup(name_buf);
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
    // Don't recurse into scope boundaries — those have their own infer_body calls
    if (e->type == NODE_FUNC_DEF || e->type == NODE_STRUCT_DEF || e->type == NODE_BODY) return;
    // Recurse into children first (depth-first: inner fcalls hoisted before outer)
    for (int i = 0; i < e->nchildren; i++) {
        hoist_expr(e->children[i], hoisted, nhoisted, cap, scope);
    }
    if (e->type != NODE_FCALL) return;
    // Check each argument (children[1..n])
    for (int i = 1; i < e->nchildren; i++) {
        if (e->children[i]->type != NODE_FCALL) continue;
        e->children[i] = hoist_to_temp(e->children[i], hoisted, nhoisted, cap, scope);
    }
}

static void hoist_fcall_args(Expr *body, TypeScope *scope) {
    Expr **new_ch = NULL;
    int new_n = 0, new_cap = 0;
    for (int i = 0; i < body->nchildren; i++) {
        Expr *stmt = body->children[i];
        // Collect hoisted decls from this statement
        Expr **hoisted = NULL;
        int nhoisted = 0, hcap = 0;
        // Walk the appropriate expression tree based on statement type
        switch (stmt->type) {
        case NODE_DECL:
            hoist_expr(stmt->children[0], &hoisted, &nhoisted, &hcap, scope);
            break;
        case NODE_FCALL:
            hoist_expr(stmt, &hoisted, &nhoisted, &hcap, scope);
            if (stmt->til_type != TIL_TYPE_NONE) {
                hoist_to_temp(stmt, &hoisted, &nhoisted, &hcap, scope);
                stmt = hoisted[--nhoisted];
                body->children[i] = stmt;
            }
            break;
        case NODE_RETURN:
            if (stmt->nchildren > 0) {
                hoist_expr(stmt->children[0], &hoisted, &nhoisted, &hcap, scope);
                if (stmt->children[0]->type == NODE_FCALL) {
                    stmt->children[0] = hoist_to_temp(stmt->children[0], &hoisted, &nhoisted, &hcap, scope);
                }
            }
            break;
        case NODE_ASSIGN:
            hoist_expr(stmt->children[0], &hoisted, &nhoisted, &hcap, scope);
            if (stmt->children[0]->type == NODE_FCALL) {
                stmt->children[0] = hoist_to_temp(stmt->children[0], &hoisted, &nhoisted, &hcap, scope);
            }
            break;
        case NODE_FIELD_ASSIGN:
            hoist_expr(stmt->children[1], &hoisted, &nhoisted, &hcap, scope);
            if (stmt->children[1]->type == NODE_FCALL) {
                stmt->children[1] = hoist_to_temp(stmt->children[1], &hoisted, &nhoisted, &hcap, scope);
            }
            break;
        case NODE_IF:
            hoist_expr(stmt->children[0], &hoisted, &nhoisted, &hcap, scope);
            if (stmt->children[0]->type == NODE_FCALL) {
                stmt->children[0] = hoist_to_temp(stmt->children[0], &hoisted, &nhoisted, &hcap, scope);
            }
            break;
        // NODE_WHILE: skip condition — hoisting changes loop semantics
        default: break;
        }
        // Insert hoisted decls before the statement
        for (int j = 0; j < nhoisted; j++) {
            if (new_n >= new_cap) {
                new_cap = new_cap ? new_cap * 2 : body->nchildren * 2;
                new_ch = realloc(new_ch, new_cap * sizeof(Expr *));
            }
            new_ch[new_n++] = hoisted[j];
        }
        free(hoisted);
        // Add original statement
        if (new_n >= new_cap) {
            new_cap = new_cap ? new_cap * 2 : body->nchildren * 2;
            new_ch = realloc(new_ch, new_cap * sizeof(Expr *));
        }
        new_ch[new_n++] = stmt;
    }
    if (new_n != body->nchildren) {
        free(body->children);
        body->children = new_ch;
        body->nchildren = new_n;
    } else {
        free(new_ch);
    }
}

// --- Free call insertion ---

static Expr *make_free_call(const char *var_name, TilType type, const char *struct_name, int line, int col) {
    Expr *call = expr_new(NODE_FCALL, line, col);
    call->til_type = TIL_TYPE_NONE;
    Expr *callee = expr_new(NODE_IDENT, line, col);
    callee->data.str_val = "free";
    callee->til_type = TIL_TYPE_NONE;
    expr_add_child(call, callee);
    Expr *arg = expr_new(NODE_IDENT, line, col);
    arg->data.str_val = var_name;
    arg->til_type = type;
    arg->struct_name = struct_name;
    expr_add_child(call, arg);
    return call;
}

static int expr_uses_var(Expr *e, const char *name) {
    if (e->type == NODE_IDENT && strcmp(e->data.str_val, name) == 0) return 1;
    if (e->type == NODE_ASSIGN && strcmp(e->data.str_val, name) == 0) return 1;
    for (int i = 0; i < e->nchildren; i++) {
        if (expr_uses_var(e->children[i], name)) return 1;
    }
    return 0;
}

static int expr_contains_decl(Expr *e, const char *name) {
    if (e->type == NODE_DECL && strcmp(e->data.decl.name, name) == 0) return 1;
    for (int i = 0; i < e->nchildren; i++) {
        if (expr_contains_decl(e->children[i], name)) return 1;
    }
    return 0;
}

static int fcall_has_own_arg(Expr *fcall, const char *var_name, TypeScope *scope) {
    if (fcall->type != NODE_FCALL || fcall->nchildren < 2) return 0;
    if (fcall->children[0]->type != NODE_IDENT) return 0;
    const char *fn_name = fcall->children[0]->data.str_val;
    TypeBinding *fb = tscope_find(scope, fn_name);
    if (!fb || !fb->func_def) return 0;
    bool *po = fb->func_def->data.func_def.param_owns;
    if (!po) return 0;
    int np = fb->func_def->data.func_def.nparam;
    for (int i = 0; i < np && i + 1 < fcall->nchildren; i++) {
        if (po[i] && fcall->children[i + 1]->type == NODE_IDENT &&
            strcmp(fcall->children[i + 1]->data.str_val, var_name) == 0) {
            return 1;
        }
    }
    return 0;
}

static int expr_transfers_own(Expr *e, const char *var_name, TypeScope *scope) {
    if (fcall_has_own_arg(e, var_name, scope)) return 1;
    for (int i = 0; i < e->nchildren; i++) {
        if (expr_transfers_own(e->children[i], var_name, scope)) return 1;
    }
    return 0;
}

typedef struct {
    const char *name;
    TilType type;
    const char *struct_name;
    int decl_index;
    int last_use;
    int own_transfer;  // index of stmt that transfers ownership, -1 if none
} LocalInfo;

static void insert_free_calls(Expr *body, TypeScope *scope, int scope_exit, const char *path) {
    if (!scope_exit) return;

    // Phase 1: collect locals with lifetime info
    // Start from 0 (not locals_start) to include own params, which are added before the body
    int n_locals = 0;
    LocalInfo *locals = NULL;
    for (int i = 0; i < scope->len; i++) {
        TypeBinding *b = &scope->bindings[i];
        if ((b->is_param && !b->is_own) || b->struct_def || b->func_def) continue;

        // Find decl_index: direct child first, then nested
        int decl_idx = -1;
        for (int j = 0; j < body->nchildren; j++) {
            Expr *s = body->children[j];
            if (s->type == NODE_DECL && strcmp(s->data.decl.name, b->name) == 0) {
                decl_idx = j;
                break;
            }
        }
        if (decl_idx == -1) {
            for (int j = 0; j < body->nchildren; j++) {
                if (expr_contains_decl(body->children[j], b->name)) {
                    decl_idx = j;
                    break;
                }
            }
        }

        // Find last_use and own_transfer
        int last_use = -1;
        int own_transfer = -1;
        int scan_from = decl_idx >= 0 ? decl_idx + 1 : 0;
        for (int j = scan_from; j < body->nchildren; j++) {
            if (expr_uses_var(body->children[j], b->name)) {
                last_use = j;
            }
            if (own_transfer == -1 && expr_transfers_own(body->children[j], b->name, scope)) {
                own_transfer = j;
            }
        }

        n_locals++;
        locals = realloc(locals, n_locals * sizeof(LocalInfo));
        locals[n_locals - 1] = (LocalInfo){b->name, b->type, b->struct_name, decl_idx, last_use, own_transfer};
    }

    if (n_locals == 0) return;

    // Check for use after ownership transfer
    for (int j = 0; j < n_locals; j++) {
        if (locals[j].own_transfer >= 0 && locals[j].last_use > locals[j].own_transfer) {
            // Find the statement for error location
            Expr *stmt = body->children[locals[j].last_use];
            char buf[128];
            snprintf(buf, sizeof(buf), "use of '%s' after ownership transfer", locals[j].name);
            type_error(path, stmt, buf);
        }
    }

    // Phase 2: rebuild body with ASAP frees
    Expr **new_ch = NULL;
    int new_n = 0;

    for (int i = 0; i < body->nchildren; i++) {
        Expr *stmt = body->children[i];

        // Before NODE_RETURN: free locals not yet freed (skip those used in return expr)
        if (stmt->type == NODE_RETURN) {
            for (int j = 0; j < n_locals; j++) {
                if (stmt->nchildren > 0 && expr_uses_var(stmt->children[0], locals[j].name)) continue;
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].decl_index < i &&
                    (locals[j].last_use >= i || locals[j].last_use == -1)) {
                    new_n++;
                    new_ch = realloc(new_ch, new_n * sizeof(Expr *));
                    new_ch[new_n - 1] = make_free_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt->line, stmt->col);
                }
            }
        }

        // Add original statement
        new_n++;
        new_ch = realloc(new_ch, new_n * sizeof(Expr *));
        new_ch[new_n - 1] = stmt;

        // After non-return statements: free locals whose last use is this statement
        if (stmt->type != NODE_RETURN) {
            for (int j = 0; j < n_locals; j++) {
                if (locals[j].own_transfer >= 0) continue; // callee frees
                if (locals[j].last_use == i) {
                    new_n++;
                    new_ch = realloc(new_ch, new_n * sizeof(Expr *));
                    new_ch[new_n - 1] = make_free_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt->line, stmt->col);
                }
                // Never used after declaration: free immediately
                if (locals[j].last_use == -1 && locals[j].decl_index == i) {
                    new_n++;
                    new_ch = realloc(new_ch, new_n * sizeof(Expr *));
                    new_ch[new_n - 1] = make_free_call(locals[j].name, locals[j].type, locals[j].struct_name, stmt->line, stmt->col);
                }
            }
        }
    }

    free(body->children);
    body->children = new_ch;
    body->nchildren = new_n;
    free(locals);
}

static void infer_body(TypeScope *scope, Expr *body, const char *path, int in_func, int owns_scope) {
    body->til_type = TIL_TYPE_NONE;
    for (int i = 0; i < body->nchildren; i++) {
        Expr *stmt = body->children[i];
        switch (stmt->type) {
        case NODE_DECL:
            infer_expr(scope, stmt->children[0], path, in_func);
            // For struct defs, register struct type in scope
            if (stmt->children[0]->type == NODE_STRUCT_DEF) {
                // Check explicit type annotation if present
                if (stmt->data.decl.explicit_type) {
                    TilType declared = type_from_name(stmt->data.decl.explicit_type, scope);
                    if (declared != TIL_TYPE_STRUCT_DEF) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is StructDef",
                                 stmt->data.decl.name, stmt->data.decl.explicit_type);
                        type_error(path, stmt, buf);
                    }
                }
                stmt->til_type = TIL_TYPE_NONE;
                const char *sname = stmt->data.decl.name;
                // Check if this is a builtin type
                TilType builtin_type = TIL_TYPE_STRUCT;
                int is_builtin = 0;
                if (strcmp(sname, "I64") == 0)  { builtin_type = TIL_TYPE_I64;  is_builtin = 1; }
                else if (strcmp(sname, "U8") == 0)   { builtin_type = TIL_TYPE_U8;   is_builtin = 1; }
                else if (strcmp(sname, "Str") == 0)  { builtin_type = TIL_TYPE_STR;  is_builtin = 1; }
                else if (strcmp(sname, "Bool") == 0) { builtin_type = TIL_TYPE_BOOL; is_builtin = 1; }
                else if (strcmp(sname, "StructDef") == 0)    { builtin_type = TIL_TYPE_STRUCT_DEF; is_builtin = 1; }
                else if (strcmp(sname, "FunctionDef") == 0)  { builtin_type = TIL_TYPE_FUNC_DEF;   is_builtin = 1; }
                else if (strcmp(sname, "Dynamic") == 0)      { builtin_type = TIL_TYPE_DYNAMIC;    is_builtin = 1; }
                tscope_set(scope, sname, builtin_type, -1, 0, stmt->line, stmt->col, 0, 0);
                // Store struct def pointer and builtin flag in the binding
                TypeBinding *b = tscope_find(scope, sname);
                b->struct_def = stmt->children[0];
                b->is_builtin = is_builtin;
                break;
            }
            // For func/proc defs, store return type and func/proc-ness in scope
            if (stmt->children[0]->type == NODE_FUNC_DEF) {
                // Check explicit type annotation if present
                if (stmt->data.decl.explicit_type) {
                    TilType declared = type_from_name(stmt->data.decl.explicit_type, scope);
                    if (declared != TIL_TYPE_FUNC_DEF) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "'%s' declared as %s but value is FunctionDef",
                                 stmt->data.decl.name, stmt->data.decl.explicit_type);
                        type_error(path, stmt, buf);
                    }
                }
                FuncType ft = stmt->children[0]->data.func_def.func_type;
                int callee_is_proc = (ft == FUNC_PROC || ft == FUNC_EXT_PROC);
                TilType rt = TIL_TYPE_NONE;
                if (stmt->children[0]->data.func_def.return_type) {
                    rt = type_from_name(stmt->children[0]->data.func_def.return_type, scope);
                }
                stmt->til_type = rt;
                tscope_set(scope, stmt->data.decl.name, rt, callee_is_proc, 0, stmt->line, stmt->col, 0, 0);
                // Store func_def pointer and builtin flag
                TypeBinding *fb = tscope_find(scope, stmt->data.decl.name);
                if (fb) {
                    fb->func_def = stmt->children[0];
                    if (ft == FUNC_EXT_FUNC || ft == FUNC_EXT_PROC)
                        fb->is_builtin = 1;
                }
                break;
            }
            if (stmt->data.decl.explicit_type) {
                const char *etn = stmt->data.decl.explicit_type;
                TilType declared = type_from_name(etn, scope);
                if (declared == TIL_TYPE_UNKNOWN) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "undefined type '%s'", etn);
                    type_error(path, stmt, buf);
                } else if (stmt->children[0]->type == NODE_LITERAL_NUM &&
                           (declared == TIL_TYPE_I64 || declared == TIL_TYPE_U8)) {
                    // Numeric literals can be used with any numeric type
                    stmt->children[0]->til_type = declared;
                } else if (stmt->children[0]->til_type != declared) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.decl.name, til_type_name(declared),
                             til_type_name(stmt->children[0]->til_type));
                    type_error(path, stmt, buf);
                } else if (declared == TIL_TYPE_STRUCT &&
                           stmt->children[0]->struct_name &&
                           strcmp(etn, stmt->children[0]->struct_name) != 0) {
                    char buf[128];
                    snprintf(buf, sizeof(buf), "'%s' declared as %s but value is %s",
                             stmt->data.decl.name, etn, stmt->children[0]->struct_name);
                    type_error(path, stmt, buf);
                }
                stmt->til_type = declared;
                // For struct types, propagate struct_name from explicit type
                if (declared == TIL_TYPE_STRUCT) {
                    stmt->children[0]->struct_name = etn;
                }
            } else {
                stmt->til_type = stmt->children[0]->til_type;
            }
            tscope_set(scope, stmt->data.decl.name, stmt->til_type, -1, stmt->data.decl.is_mut, stmt->line, stmt->col, 0, 0);
            if (stmt->til_type == TIL_TYPE_STRUCT && stmt->children[0]->struct_name) {
                TypeBinding *b = tscope_find(scope, stmt->data.decl.name);
                if (b) b->struct_name = stmt->children[0]->struct_name;
            }
            break;
        case NODE_ASSIGN: {
            infer_expr(scope, stmt->children[0], path, in_func);
            stmt->til_type = stmt->children[0]->til_type;
            const char *aname = stmt->data.str_val;
            TilType existing = tscope_get(scope, aname);
            if (existing == TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "undefined symbol '%s'", aname);
                type_error(path, stmt, buf);
            } else if (!tscope_is_mut(scope, aname)) {
                char buf[128];
                snprintf(buf, sizeof(buf), "cannot assign to immutable variable '%s'", aname);
                type_error(path, stmt, buf);
                TypeBinding *b = tscope_find(scope, aname);
                if (b && b->is_param) {
                    fprintf(stderr, "%s:%d:%d: note: '%s' is a function parameter\n",
                            path, b->line, b->col, aname);
                } else if (b) {
                    fprintf(stderr, "%s:%d:%d: note: '%s' declared here, consider adding 'mut'\n",
                            path, b->line, b->col, aname);
                }
            } else if (stmt->children[0]->til_type != existing &&
                       stmt->children[0]->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "'%s' is %s but assigned %s",
                         aname, til_type_name(existing),
                         til_type_name(stmt->children[0]->til_type));
                type_error(path, stmt, buf);
            }
            break;
        }
        case NODE_FIELD_ASSIGN: {
            infer_expr(scope, stmt->children[0], path, in_func); // object
            infer_expr(scope, stmt->children[1], path, in_func); // value
            Expr *obj = stmt->children[0];
            const char *fname = stmt->data.str_val;
            if (obj->struct_name) {
                Expr *sdef = tscope_get_struct(scope, obj->struct_name);
                if (sdef) {
                    Expr *body = sdef->children[0];
                    int found = 0;
                    for (int i = 0; i < body->nchildren; i++) {
                        Expr *field = body->children[i];
                        if (strcmp(field->data.decl.name, fname) == 0) {
                            found = 1;
                            if (!field->data.decl.is_mut) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "cannot assign to immutable field '%s'", fname);
                                type_error(path, stmt, buf);
                            }
                            if (stmt->children[1]->til_type != field->til_type &&
                                stmt->children[1]->til_type != TIL_TYPE_UNKNOWN) {
                                char buf[128];
                                snprintf(buf, sizeof(buf), "field '%s' is %s but assigned %s",
                                         fname, til_type_name(field->til_type),
                                         til_type_name(stmt->children[1]->til_type));
                                type_error(path, stmt, buf);
                            }
                            break;
                        }
                    }
                    if (!found) {
                        char buf[128];
                        snprintf(buf, sizeof(buf), "struct '%s' has no field '%s'",
                                 obj->struct_name, fname);
                        type_error(path, stmt, buf);
                    }
                }
            } else {
                type_error(path, stmt, "field assignment on non-struct value");
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        }
        case NODE_FCALL:
            infer_expr(scope, stmt, path, in_func);
            break;
        case NODE_RETURN:
            if (stmt->nchildren > 0) {
                infer_expr(scope, stmt->children[0], path, in_func);
                stmt->til_type = stmt->children[0]->til_type;
            } else {
                stmt->til_type = TIL_TYPE_NONE;
            }
            break;
        case NODE_IF:
            infer_expr(scope, stmt->children[0], path, in_func); // condition
            if (stmt->children[0]->til_type != TIL_TYPE_BOOL &&
                stmt->children[0]->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "if condition must be Bool, got %s",
                         til_type_name(stmt->children[0]->til_type));
                type_error(path, stmt, buf);
            }
            {
                TypeScope *then_scope = tscope_new(scope);
                infer_body(then_scope, stmt->children[1], path, in_func, 1);
                tscope_free(then_scope);
            }
            if (stmt->nchildren > 2) {
                TypeScope *else_scope = tscope_new(scope);
                infer_body(else_scope, stmt->children[2], path, in_func, 1);
                tscope_free(else_scope);
            }
            stmt->til_type = TIL_TYPE_NONE;
            break;
        case NODE_BODY: {
            TypeScope *block_scope = tscope_new(scope);
            infer_body(block_scope, stmt, path, in_func, 1);
            tscope_free(block_scope);
            break;
        }
        case NODE_WHILE:
            infer_expr(scope, stmt->children[0], path, in_func); // condition
            if (stmt->children[0]->til_type != TIL_TYPE_BOOL &&
                stmt->children[0]->til_type != TIL_TYPE_UNKNOWN) {
                char buf[128];
                snprintf(buf, sizeof(buf), "while condition must be Bool, got %s",
                         til_type_name(stmt->children[0]->til_type));
                type_error(path, stmt, buf);
            }
            // Transform: while COND { BODY } → while true { _wcond := COND; if _wcond {} else { break }; BODY }
            // This lets ASAP destruction free the condition result each iteration.
            if (expr_contains_fcall(stmt->children[0])) {
                int line = stmt->children[0]->line;
                int col = stmt->children[0]->col;
                Expr *cond = stmt->children[0];
                Expr *body = stmt->children[1];
                // _wcondN := COND
                char name_buf[32];
                snprintf(name_buf, sizeof(name_buf), "_wcond%d", hoist_counter++);
                const char *wname = strdup(name_buf);
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
                Expr *free_wcond = make_free_call(wname, TIL_TYPE_BOOL, NULL, line, col);
                expr_add_child(else_body, free_wcond);
                Expr *brk = expr_new(NODE_BREAK, line, col);
                brk->til_type = TIL_TYPE_NONE;
                expr_add_child(else_body, brk);
                expr_add_child(if_node, else_body);
                // Prepend decl + if to body
                int old_n = body->nchildren;
                int new_n = old_n + 2;
                Expr **new_ch = malloc(new_n * sizeof(Expr *));
                new_ch[0] = decl;
                new_ch[1] = if_node;
                for (int j = 0; j < old_n; j++) new_ch[j + 2] = body->children[j];
                free(body->children);
                body->children = new_ch;
                body->nchildren = new_n;
                // Replace condition with true
                Expr *true_lit = expr_new(NODE_LITERAL_BOOL, line, col);
                true_lit->data.str_val = "true";
                true_lit->til_type = TIL_TYPE_BOOL;
                stmt->children[0] = true_lit;
            }
            {
                TypeScope *while_scope = tscope_new(scope);
                infer_body(while_scope, stmt->children[1], path, in_func, 1);
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
    insert_free_calls(body, scope, owns_scope, path);
}

int type_check(Expr *program, const char *path, TypeScope *scope) {
    errors = 0;
    infer_body(scope, program, path, 0, 1);
    return errors;
}
