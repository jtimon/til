#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "precomp.h"
#include "interpreter.h"
#include "map.h"

static Set macros, funcs;
static Map known;

// --- Value → Expr conversion ---

static Expr *value_to_expr(Value val, int line, int col) {
    Expr *e;
    switch (val.type) {
    case VAL_I64: {
        e = expr_new(NODE_LITERAL_NUM, line, col);
        char buf[32];
        snprintf(buf, sizeof(buf), "%lld", (long long)*val.i64);
        e->data.str_val = Str_new(buf);
        e->til_type = TIL_TYPE_I64;
        return e;
    }
    case VAL_U8: {
        e = expr_new(NODE_LITERAL_NUM, line, col);
        char buf[32];
        snprintf(buf, sizeof(buf), "%u", (unsigned)*val.u8);
        e->data.str_val = Str_new(buf);
        e->til_type = TIL_TYPE_U8;
        return e;
    }
    case VAL_STR: {
        e = expr_new(NODE_LITERAL_STR, line, col);
        e->data.str_val = Str_clone(val.str);
        e->til_type = TIL_TYPE_STR;
        return e;
    }
    case VAL_BOOL: {
        e = expr_new(NODE_LITERAL_BOOL, line, col);
        e->data.str_val = Str_new(*val.boolean ? "true" : "false");
        e->til_type = TIL_TYPE_BOOL;
        return e;
    }
    default:
        return NULL;
    }
}

// --- Expr → Value conversion (for building args to pass to interpreter) ---

static Value expr_to_value(Expr *e) {
    switch (e->type) {
    case NODE_LITERAL_NUM:
        if (e->til_type == TIL_TYPE_U8)
            return val_u8(atoll(e->data.str_val->c_str));
        return val_i64(atoll(e->data.str_val->c_str));
    case NODE_LITERAL_STR:
        return val_str(Str_clone(e->data.str_val));
    case NODE_LITERAL_BOOL:
        return val_bool(strcmp(e->data.str_val->c_str, "true") == 0);
    default:
        return val_none();
    }
}

// Check if an expression is compile-time known and return its value
static int is_known(Expr *e, Value *out) {
    if (e->type == NODE_LITERAL_NUM || e->type == NODE_LITERAL_STR ||
        e->type == NODE_LITERAL_BOOL) {
        *out = expr_to_value(e);
        return 1;
    }
    if (e->type == NODE_IDENT) {
        Value *v = Map_get(&known, &e->data.str_val);
        if (v) { *out = *v; return 1; }
    }
    return 0;
}

// Check if a NODE_FCALL is a macro call
static int is_macro_call(Expr *e) {
    return e->type == NODE_FCALL &&
           e->children.len > 0 &&
           expr_child(e, 0)->type == NODE_IDENT &&
           Set_has(&macros, &expr_child(e, 0)->data.str_val);
}

// Check if a NODE_FCALL is a pure func call
static int is_func_call(Expr *e) {
    return e->type == NODE_FCALL &&
           e->children.len > 0 &&
           expr_child(e, 0)->type == NODE_IDENT &&
           Set_has(&funcs, &expr_child(e, 0)->data.str_val);
}

// Try to evaluate a call at compile time.
// require_known=1 (macro): error if arg not known. require_known=0 (func): return NULL silently.
static Expr *try_eval_call(Scope *scope, Expr *fcall,
                           const char *path, int require_known) {
    // Build a call with literal args for the interpreter
    int nargs = fcall->children.len - 1;
    Expr *eval_call = expr_new(NODE_FCALL, fcall->line, fcall->col);
    eval_call->til_type = fcall->til_type;
    eval_call->struct_name = fcall->struct_name;
    expr_add_child(eval_call, expr_child(fcall, 0)); // callee ident

    for (int i = 0; i < nargs; i++) {
        Expr *arg = expr_child(fcall, i + 1);
        Value arg_val;
        if (!is_known(arg, &arg_val)) {
            if (require_known) {
                fprintf(stderr, "%s:%d:%d: error: macro argument must be known at compile time\n",
                        path, arg->line, arg->col);
            }
            // Clean up: detach callee so it's not double-freed
            expr_child(eval_call, 0) = NULL;
            eval_call->children.len = 0;
            expr_free(eval_call);
            return NULL;
        }
        // Create a literal expression from the value
        Expr *lit = value_to_expr(arg_val, arg->line, arg->col);
        expr_add_child(eval_call, lit);
    }

    // Evaluate the call using the interpreter
    Value result = eval_expr(scope, eval_call, path);

    // Clean up eval_call (detach callee ident first — it's shared with original)
    expr_child(eval_call, 0) = NULL;
    for (int i = 1; i < eval_call->children.len; i++)
        expr_free(expr_child(eval_call, i));
    Vec_delete(&eval_call->children);
    free(eval_call);

    // Convert result to AST
    Expr *lit = value_to_expr(result, fcall->line, fcall->col);
    if (!lit) {
        if (require_known) {
            fprintf(stderr, "%s:%d:%d: error: macro returned non-primitive type\n",
                    path, fcall->line, fcall->col);
        }
    }
    return lit;
}

// Track a literal value from a declaration
static void track_literal(Str *name, Expr *rhs) {
    Value v;
    if (is_known(rhs, &v)) {
        Map_set(&known, &name, &v);
    }
}

// Process a body, replacing macro calls with literals
static void process_body(Scope *scope, Expr *body, const char *path) {
    for (int i = 0; i < body->children.len; i++) {
        Expr *stmt = expr_child(body, i);

        switch (stmt->type) {
        case NODE_DECL:
            if (stmt->children.len == 0) break; // variant registry (payload enums)
            if (expr_child(stmt, 0)->type == NODE_FUNC_DEF ||
                expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
                expr_child(stmt, 0)->type == NODE_ENUM_DEF) {
                // Recurse into func/proc/macro bodies
                if (expr_child(stmt, 0)->type == NODE_FUNC_DEF &&
                    expr_child(stmt, 0)->children.len > 0) {
                    process_body(scope, expr_child(expr_child(stmt, 0), 0), path);
                }
                break;
            }
            // ref declarations must keep the function call — no folding
            if (stmt->data.decl.is_ref) break;
            // Check if RHS is a macro or pure func call
            if (is_macro_call(expr_child(stmt, 0))) {
                Expr *lit = try_eval_call(scope, expr_child(stmt, 0), path, 1);
                if (lit) {
                    expr_free(expr_child(stmt, 0));
                    expr_child(stmt, 0) = lit;
                    track_literal(stmt->data.decl.name, lit);
                }
            } else if (is_func_call(expr_child(stmt, 0))) {
                Expr *lit = try_eval_call(scope, expr_child(stmt, 0), path, 0);
                if (lit) {
                    expr_free(expr_child(stmt, 0));
                    expr_child(stmt, 0) = lit;
                    track_literal(stmt->data.decl.name, lit);
                } else {
                    track_literal(stmt->data.decl.name, expr_child(stmt, 0));
                }
            } else {
                // Track compile-time known value
                track_literal(stmt->data.decl.name, expr_child(stmt, 0));
            }
            break;

        case NODE_IF:
            if (stmt->children.len > 1)
                process_body(scope, expr_child(stmt, 1), path);
            if (stmt->children.len > 2)
                process_body(scope, expr_child(stmt, 2), path);
            break;

        case NODE_WHILE:
            if (stmt->children.len > 1)
                process_body(scope, expr_child(stmt, 1), path);
            break;

        case NODE_FCALL:
            // Bare macro or pure func call (not in a declaration)
            if (is_macro_call(stmt)) {
                Expr *lit = try_eval_call(scope, stmt, path, 1);
                if (lit) {
                    expr_free(stmt);
                    expr_child(body, i) = lit;
                }
            } else if (is_func_call(stmt)) {
                Expr *lit = try_eval_call(scope, stmt, path, 0);
                if (lit) {
                    expr_free(stmt);
                    expr_child(body, i) = lit;
                }
            }
            break;

        default:
            break;
        }
    }
}

void precomp(Expr *program, const char *path) {
    // 1. Collect macro and pure func names
    macros = Set_new(sizeof(Str *), str_ptr_cmp);
    funcs = Set_new(sizeof(Str *), str_ptr_cmp);
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL && stmt->children.len > 0 && expr_child(stmt, 0)->type == NODE_FUNC_DEF) {
            FuncType ft = expr_child(stmt, 0)->data.func_def.func_type;
            if (ft == FUNC_MACRO)
                Set_add(&macros, &stmt->data.decl.name);
            else if (ft == FUNC_FUNC)
                Set_add(&funcs, &stmt->data.decl.name);
        }
    }

    // Nothing to fold?
    if (Set_len(&macros) == 0 && Set_len(&funcs) == 0) {
        Set_delete(&macros);
        Set_delete(&funcs);
        return;
    }

    // 2. Set up interpreter scope (same as interpret() does)
    Scope *global = scope_new(NULL);
    for (int i = 0; i < program->children.len; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type == NODE_DECL &&
            (expr_child(stmt, 0)->type == NODE_FUNC_DEF ||
             expr_child(stmt, 0)->type == NODE_STRUCT_DEF ||
             expr_child(stmt, 0)->type == NODE_ENUM_DEF)) {
            Value val = {.type = VAL_FUNC, .func = expr_child(stmt, 0)};
            scope_set_owned(global, stmt->data.decl.name, val);
        }
    }
    interpreter_init_ns(global, program, path);

    // 3. Process the program body
    known = Map_new(sizeof(Str *), sizeof(Value), str_ptr_cmp);
    process_body(global, program, path);

    // Cleanup
    Map_delete(&known);
    scope_free(global);
    Set_delete(&macros);
    Set_delete(&funcs);
}
