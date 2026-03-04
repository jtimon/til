#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "precomp.h"
#include "interpreter.h"

// --- Macro and pure func name sets ---

static Str **macro_names = NULL;
static int macro_count = 0, macro_cap = 0;

static Str **func_names = NULL;
static int func_count = 0, func_cap = 0;

static int is_macro(Str *name) {
    for (int i = 0; i < macro_count; i++)
        if (Str_eq(macro_names[i], name)) return 1;
    return 0;
}

static int is_pure_func(Str *name) {
    for (int i = 0; i < func_count; i++)
        if (Str_eq(func_names[i], name)) return 1;
    return 0;
}

// --- Compile-time known values ---

typedef struct {
    Str *name;
    Value val;
} KnownEntry;

typedef struct {
    KnownEntry *entries;
    int len, cap;
} KnownMap;

static KnownMap known_new(void) {
    return (KnownMap){NULL, 0, 0};
}

static void known_set(KnownMap *m, Str *name, Value val) {
    for (int i = 0; i < m->len; i++) {
        if (Str_eq(m->entries[i].name, name)) {
            m->entries[i].val = val;
            return;
        }
    }
    if (m->len == m->cap) {
        m->cap = m->cap ? m->cap * 2 : 8;
        m->entries = realloc(m->entries, m->cap * sizeof(KnownEntry));
    }
    m->entries[m->len++] = (KnownEntry){name, val};
}

static Value *known_get(KnownMap *m, Str *name) {
    for (int i = 0; i < m->len; i++)
        if (Str_eq(m->entries[i].name, name)) return &m->entries[i].val;
    return NULL;
}

static void known_free(KnownMap *m) {
    free(m->entries);
}

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
static int is_known(Expr *e, KnownMap *known, Value *out) {
    if (e->type == NODE_LITERAL_NUM || e->type == NODE_LITERAL_STR ||
        e->type == NODE_LITERAL_BOOL) {
        *out = expr_to_value(e);
        return 1;
    }
    if (e->type == NODE_IDENT) {
        Value *v = known_get(known, e->data.str_val);
        if (v) { *out = *v; return 1; }
    }
    return 0;
}

// Check if a NODE_FCALL is a macro call
static int is_macro_call(Expr *e) {
    return e->type == NODE_FCALL &&
           e->nchildren > 0 &&
           e->children[0]->type == NODE_IDENT &&
           is_macro(e->children[0]->data.str_val);
}

// Check if a NODE_FCALL is a pure func call
static int is_func_call(Expr *e) {
    return e->type == NODE_FCALL &&
           e->nchildren > 0 &&
           e->children[0]->type == NODE_IDENT &&
           is_pure_func(e->children[0]->data.str_val);
}

// Try to evaluate a call at compile time.
// require_known=1 (macro): error if arg not known. require_known=0 (func): return NULL silently.
static Expr *try_eval_call(Scope *scope, Expr *fcall, KnownMap *known,
                           const char *path, int require_known) {
    // Build a call with literal args for the interpreter
    int nargs = fcall->nchildren - 1;
    Expr *eval_call = expr_new(NODE_FCALL, fcall->line, fcall->col);
    eval_call->til_type = fcall->til_type;
    eval_call->struct_name = fcall->struct_name;
    expr_add_child(eval_call, fcall->children[0]); // callee ident

    for (int i = 0; i < nargs; i++) {
        Expr *arg = fcall->children[i + 1];
        Value arg_val;
        if (!is_known(arg, known, &arg_val)) {
            if (require_known) {
                fprintf(stderr, "%s:%d:%d: error: macro argument must be known at compile time\n",
                        path, arg->line, arg->col);
            }
            // Clean up: detach callee so it's not double-freed
            eval_call->children[0] = NULL;
            eval_call->nchildren = 0;
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
    eval_call->children[0] = NULL;
    for (int i = 1; i < eval_call->nchildren; i++)
        expr_free(eval_call->children[i]);
    free(eval_call->children);
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
static void track_literal(KnownMap *known, Str *name, Expr *rhs) {
    Value v;
    if (is_known(rhs, known, &v)) {
        known_set(known, name, v);
    }
}

// Process a body, replacing macro calls with literals
static void process_body(Scope *scope, Expr *body, KnownMap *known,
                         const char *path) {
    for (int i = 0; i < body->nchildren; i++) {
        Expr *stmt = body->children[i];

        switch (stmt->type) {
        case NODE_DECL:
            if (stmt->children[0]->type == NODE_FUNC_DEF ||
                stmt->children[0]->type == NODE_STRUCT_DEF ||
                stmt->children[0]->type == NODE_ENUM_DEF) {
                // Recurse into func/proc/macro bodies
                if (stmt->children[0]->type == NODE_FUNC_DEF &&
                    stmt->children[0]->nchildren > 0) {
                    process_body(scope, stmt->children[0]->children[0], known, path);
                }
                break;
            }
            // Check if RHS is a macro or pure func call
            if (is_macro_call(stmt->children[0])) {
                Expr *lit = try_eval_call(scope, stmt->children[0], known, path, 1);
                if (lit) {
                    expr_free(stmt->children[0]);
                    stmt->children[0] = lit;
                    track_literal(known, stmt->data.decl.name, lit);
                }
            } else if (is_func_call(stmt->children[0])) {
                Expr *lit = try_eval_call(scope, stmt->children[0], known, path, 0);
                if (lit) {
                    expr_free(stmt->children[0]);
                    stmt->children[0] = lit;
                    track_literal(known, stmt->data.decl.name, lit);
                } else {
                    track_literal(known, stmt->data.decl.name, stmt->children[0]);
                }
            } else {
                // Track compile-time known value
                track_literal(known, stmt->data.decl.name, stmt->children[0]);
            }
            break;

        case NODE_IF:
            if (stmt->nchildren > 1)
                process_body(scope, stmt->children[1], known, path);
            if (stmt->nchildren > 2)
                process_body(scope, stmt->children[2], known, path);
            break;

        case NODE_WHILE:
            if (stmt->nchildren > 1)
                process_body(scope, stmt->children[1], known, path);
            break;

        case NODE_FCALL:
            // Bare macro or pure func call (not in a declaration)
            if (is_macro_call(stmt)) {
                Expr *lit = try_eval_call(scope, stmt, known, path, 1);
                if (lit) {
                    expr_free(stmt);
                    body->children[i] = lit;
                }
            } else if (is_func_call(stmt)) {
                Expr *lit = try_eval_call(scope, stmt, known, path, 0);
                if (lit) {
                    expr_free(stmt);
                    body->children[i] = lit;
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
    macro_names = NULL; macro_count = 0; macro_cap = 0;
    func_names = NULL; func_count = 0; func_cap = 0;
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_FUNC_DEF) {
            FuncType ft = stmt->children[0]->data.func_def.func_type;
            if (ft == FUNC_MACRO) {
                if (macro_count == macro_cap) {
                    macro_cap = macro_cap ? macro_cap * 2 : 8;
                    macro_names = realloc(macro_names, macro_cap * sizeof(Str *));
                }
                macro_names[macro_count++] = stmt->data.decl.name;
            } else if (ft == FUNC_FUNC) {
                if (func_count == func_cap) {
                    func_cap = func_cap ? func_cap * 2 : 8;
                    func_names = realloc(func_names, func_cap * sizeof(Str *));
                }
                func_names[func_count++] = stmt->data.decl.name;
            }
        }
    }

    // Nothing to fold?
    if (macro_count == 0 && func_count == 0) {
        free(macro_names); macro_names = NULL;
        free(func_names); func_names = NULL;
        return;
    }

    // 2. Set up interpreter scope (same as interpret() does)
    Scope *global = scope_new(NULL);
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL &&
            (stmt->children[0]->type == NODE_FUNC_DEF ||
             stmt->children[0]->type == NODE_STRUCT_DEF ||
             stmt->children[0]->type == NODE_ENUM_DEF)) {
            Value val = {.type = VAL_FUNC, .func = stmt->children[0]};
            scope_set_owned(global, stmt->data.decl.name, val);
        }
    }
    interpreter_init_ns(global, program, path);

    // 3. Process the program body
    KnownMap known = known_new();
    process_body(global, program, &known, path);

    // Cleanup
    known_free(&known);
    scope_free(global);
    free(macro_names); macro_names = NULL; macro_count = 0;
    free(func_names); func_names = NULL; func_count = 0;
}
