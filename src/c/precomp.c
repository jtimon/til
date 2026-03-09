#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "precomp.h"
#include "interpreter.h"
#include "dispatch.h"
#include "map.h"

static Set macros, funcs;
static Map known;

// --- Value → Expr conversion ---

static Expr *value_to_expr(Value val, Expr *src) {
    I32 line = src->line, col = src->col;
    Str *path = src->path;
    Expr *e;
    switch (val.type) {
    case VAL_I64: {
        e = expr_new(NODE_LITERAL_NUM, line, col, path);
        char buf[32];
        snprintf(buf, sizeof(buf), "%lld", (long long)*val.i64);
        e->type.str_val = Str_new(buf);
        e->til_type = TIL_TYPE_I64;
        return e;
    }
    case VAL_U8: {
        e = expr_new(NODE_LITERAL_NUM, line, col, path);
        char buf[32];
        snprintf(buf, sizeof(buf), "%u", (unsigned)*val.u8);
        e->type.str_val = Str_new(buf);
        e->til_type = TIL_TYPE_U8;
        return e;
    }
    case VAL_STRUCT: {
        if (Str_eq_c(val.instance->struct_name, "Str")) {
            Str sv = str_view(val);
            e = expr_new(NODE_LITERAL_STR, line, col, path);
            e->type.str_val = Str_new_len(sv.c_str, sv.count);
            e->til_type = TIL_TYPE_STRUCT;
            e->struct_name = Str_new("Str");
            return e;
        }
        return NULL; // other struct types not supported in precomp
    }
    case VAL_BOOL: {
        e = expr_new(NODE_LITERAL_BOOL, line, col, path);
        e->type.str_val = Str_new(*val.boolean ? "true" : "false");
        e->til_type = TIL_TYPE_BOOL;
        return e;
    }
    default:
        return NULL;
    }
}

// --- Expr → Value conversion (for building args to pass to interpreter) ---

static Value expr_to_value(Expr *e) {
    switch (e->type.tag) {
    case NODE_LITERAL_NUM:
        if (e->til_type == TIL_TYPE_U8)
            return val_u8(atoll(e->type.str_val->c_str));
        return val_i64(atoll(e->type.str_val->c_str));
    case NODE_LITERAL_STR:
        return make_str_value(e->type.str_val->c_str, e->type.str_val->count);
    case NODE_LITERAL_BOOL:
        return val_bool(strcmp(e->type.str_val->c_str, "true") == 0);
    default:
        return val_none();
    }
}

// Check if an expression is compile-time known and return its value
static Bool is_known(Expr *e, Value *out) {
    if (e->type.tag == NODE_LITERAL_NUM || e->type.tag == NODE_LITERAL_STR ||
        e->type.tag == NODE_LITERAL_BOOL) {
        *out = expr_to_value(e);
        return 1;
    }
    if (e->type.tag == NODE_IDENT) {
        Value *v = Map_get(&known, &e->type.str_val);
        if (v) { *out = *v; return 1; }
    }
    return 0;
}

// Check if a NODE_FCALL is a macro call
static Bool is_macro_call(Expr *e) {
    return e->type.tag == NODE_FCALL &&
           e->children.count > 0 &&
           expr_child(e, 0)->type.tag == NODE_IDENT &&
           Set_has(&macros, &expr_child(e, 0)->type.str_val);
}

// Check if a NODE_FCALL is a pure func call
static Bool is_func_call(Expr *e) {
    return e->type.tag == NODE_FCALL &&
           e->children.count > 0 &&
           expr_child(e, 0)->type.tag == NODE_IDENT &&
           Set_has(&funcs, &expr_child(e, 0)->type.str_val);
}

// Check if a func body references identifiers not available at precomp time.
// Something is available if it's a parameter, in the known map, or in the precomp scope
// (funcs, structs, enums are pre-registered there).
static Bool func_uses_unknown_globals(Expr *e, Expr *func_def, Scope *precomp_scope) {
    if (e->type.tag == NODE_FUNC_DEF) return 0; // don't recurse into nested funcs
    if (e->type.tag == NODE_IDENT) {
        Str *name = e->type.str_val;
        for (U32 i = 0; i < func_def->type.func_def.nparam; i++) {
            if (Str_eq(func_def->type.func_def.param_names[i], name)) return 0;
        }
        if (Map_get(&known, &name)) return 0;
        if (scope_get(precomp_scope, name)) return 0;
        return 1;
    }
    for (U32 i = 0; i < e->children.count; i++) {
        if (func_uses_unknown_globals(expr_child(e, i), func_def, precomp_scope)) return 1;
    }
    return 0;
}

// Try to evaluate a call at compile time.
// require_known=1 (macro): error if arg not known. require_known=0 (func): return NULL silently.
static Expr *try_eval_call(Scope *scope, Expr *fcall, Bool require_known) {
    // Check if the function body references unknown globals
    Str *callee_name = expr_child(fcall, 0)->type.str_val;
    Cell *fn_cell = scope_get(scope, callee_name);
    if (fn_cell && fn_cell->val.type == VAL_FUNC && fn_cell->val.func->type.tag == NODE_FUNC_DEF) {
        Expr *fdef = fn_cell->val.func;
        if (fdef->children.count > 0 && func_uses_unknown_globals(expr_child(fdef, 0), fdef, scope)) {
            return NULL;
        }
    }

    // Build a call with literal args for the interpreter
    U32 nargs = fcall->children.count - 1;
    Expr *eval_call = expr_new(NODE_FCALL, fcall->line, fcall->col, fcall->path);
    eval_call->til_type = fcall->til_type;
    eval_call->struct_name = fcall->struct_name;
    expr_add_child(eval_call, expr_child(fcall, 0)); // callee ident

    for (U32 i = 0; i < nargs; i++) {
        Expr *arg = expr_child(fcall, i + 1);
        Value arg_val;
        if (!is_known(arg, &arg_val)) {
            if (require_known) {
                expr_error(arg, "macro argument must be known at compile time");
            }
            // Clean up: detach callee so it's not double-freed
            expr_child(eval_call, 0) = NULL;
            eval_call->children.count = 0;
            expr_free(eval_call);
            return NULL;
        }
        // Create a literal expression from the value
        Expr *lit = value_to_expr(arg_val, arg);
        expr_add_child(eval_call, lit);
    }

    // Evaluate the call using the interpreter
    Value result = eval_expr(scope, eval_call);

    // Clean up eval_call (detach callee ident first — it's shared with original)
    expr_child(eval_call, 0) = NULL;
    for (U32 i = 1; i < eval_call->children.count; i++)
        expr_free(expr_child(eval_call, i));
    Vec_delete(&eval_call->children);
    free(eval_call);

    // Convert result to AST
    Expr *lit = value_to_expr(result, fcall);
    if (!lit) {
        if (require_known) {
            expr_error(fcall, "macro returned non-primitive type");
        }
    }
    return lit;
}

// Track a literal value from a declaration — also add to precomp scope
// so the interpreter can find it when folding func calls
static void track_literal(Scope *scope, Str *name, Expr *rhs) {
    Value v;
    if (is_known(rhs, &v)) {
        Map_set(&known, &name, &v);
        scope_set_owned(scope, name, v);
    }
}

// Process a body, replacing macro calls with literals
static void process_body(Scope *scope, Expr *body) {
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *stmt = expr_child(body, i);

        switch (stmt->type.tag) {
        case NODE_DECL:
            if (stmt->children.count == 0) break; // variant registry (payload enums)
            if (expr_child(stmt, 0)->type.tag == NODE_FUNC_DEF ||
                expr_child(stmt, 0)->type.tag == NODE_STRUCT_DEF ||
                expr_child(stmt, 0)->type.tag == NODE_ENUM_DEF) {
                // Recurse into func/proc/macro bodies
                if (expr_child(stmt, 0)->type.tag == NODE_FUNC_DEF &&
                    expr_child(stmt, 0)->children.count > 0) {
                    process_body(scope, expr_child(expr_child(stmt, 0), 0));
                }
                break;
            }
            // ref declarations must keep the function call — no folding
            if (stmt->type.decl.is_ref) break;
            // Check if RHS is a macro or pure func call
            if (is_macro_call(expr_child(stmt, 0))) {
                Expr *lit = try_eval_call(scope, expr_child(stmt, 0), 1);
                if (lit) {
                    expr_free(expr_child(stmt, 0));
                    expr_child(stmt, 0) = lit;
                    track_literal(scope, stmt->type.decl.name, lit);
                }
            } else if (is_func_call(expr_child(stmt, 0))) {
                Expr *lit = try_eval_call(scope, expr_child(stmt, 0), 0);
                if (lit) {
                    expr_free(expr_child(stmt, 0));
                    expr_child(stmt, 0) = lit;
                    track_literal(scope, stmt->type.decl.name, lit);
                } else {
                    track_literal(scope, stmt->type.decl.name, expr_child(stmt, 0));
                }
            } else {
                // Track compile-time known value
                track_literal(scope, stmt->type.decl.name, expr_child(stmt, 0));
            }
            break;

        case NODE_IF:
            if (stmt->children.count > 1)
                process_body(scope, expr_child(stmt, 1));
            if (stmt->children.count > 2)
                process_body(scope, expr_child(stmt, 2));
            break;

        case NODE_WHILE:
            if (stmt->children.count > 1)
                process_body(scope, expr_child(stmt, 1));
            break;

        case NODE_FCALL:
            // Bare macro or pure func call (not in a declaration)
            if (is_macro_call(stmt)) {
                Expr *lit = try_eval_call(scope, stmt, 1);
                if (lit) {
                    expr_free(stmt);
                    expr_child(body, i) = lit;
                }
            } else if (is_func_call(stmt)) {
                Expr *lit = try_eval_call(scope, stmt, 0);
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

void precomp(Expr *program) {
    // 1. Collect macro and pure func names
    macros = Set_new(sizeof(Str *), str_ptr_cmp);
    funcs = Set_new(sizeof(Str *), str_ptr_cmp);
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag == NODE_DECL && stmt->children.count > 0 && expr_child(stmt, 0)->type.tag == NODE_FUNC_DEF) {
            FuncType ft = expr_child(stmt, 0)->type.func_def.func_type;
            if (ft == FUNC_MACRO)
                Set_add(&macros, &stmt->type.decl.name);
            else if (ft == FUNC_FUNC)
                Set_add(&funcs, &stmt->type.decl.name);
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
    for (U32 i = 0; i < program->children.count; i++) {
        Expr *stmt = expr_child(program, i);
        if (stmt->type.tag == NODE_DECL &&
            (expr_child(stmt, 0)->type.tag == NODE_FUNC_DEF ||
             expr_child(stmt, 0)->type.tag == NODE_STRUCT_DEF ||
             expr_child(stmt, 0)->type.tag == NODE_ENUM_DEF)) {
            Value val = {.type = VAL_FUNC, .func = expr_child(stmt, 0)};
            scope_set_owned(global, stmt->type.decl.name, val);
        }
    }
    interpreter_init_ns(global, program);

    // 2b. Init FFI so ext_func calls (e.g. auto-delete) work during folding
    ffi_init(program, NULL, NULL, NULL);

    // 3. Process the program body
    known = Map_new(sizeof(Str *), sizeof(Value), str_ptr_cmp);
    process_body(global, program);

    // Cleanup
    Map_delete(&known);
    scope_free(global);
    Set_delete(&macros);
    Set_delete(&funcs);
}
