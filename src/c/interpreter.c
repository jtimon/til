#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Values ---

typedef enum {
    VAL_NONE,
    VAL_I64,
    VAL_STR,
    VAL_BOOL,
    VAL_FUNC,   // pointer to a func/proc AST node
    VAL_STRUCT, // struct instance
} ValType;

typedef struct StructInstance StructInstance;
typedef struct Value Value;

struct StructInstance {
    const char *struct_name;
    const char **field_names;
    int *field_muts;
    int nfields;
    Value *field_values;
};

struct Value {
    ValType type;
    union {
        long long i64;
        const char *str;
        int boolean;
        Expr *func;
        StructInstance *instance;
    };
};

static Value val_none(void) {
    return (Value){.type = VAL_NONE};
}

// --- Return value mechanism ---
static int has_return;
static Value return_value;

// --- Scope / environment ---

typedef struct {
    const char *name;
    Value val;
} Binding;

typedef struct Scope Scope;
struct Scope {
    Binding *bindings;
    int len;
    int cap;
    Scope *parent;
};

static Scope *scope_new(Scope *parent) {
    Scope *s = calloc(1, sizeof(Scope));
    s->parent = parent;
    return s;
}

static void scope_free(Scope *s) {
    free(s->bindings);
    free(s);
}

static void scope_set(Scope *s, const char *name, Value val) {
    // Check if already exists in this scope
    for (int i = 0; i < s->len; i++) {
        if (strcmp(s->bindings[i].name, name) == 0) {
            s->bindings[i].val = val;
            return;
        }
    }
    // Add new binding
    if (s->len >= s->cap) {
        s->cap = s->cap ? s->cap * 2 : 8;
        s->bindings = realloc(s->bindings, s->cap * sizeof(Binding));
    }
    s->bindings[s->len++] = (Binding){name, val};
}

static Value *scope_get(Scope *s, const char *name) {
    for (Scope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return &cur->bindings[i].val;
            }
        }
    }
    return NULL;
}

// --- Eval ---

static Value eval_expr(Scope *scope, Expr *e, const char *path);
static void eval_body(Scope *scope, Expr *body, const char *path);

static Value eval_call(Scope *scope, Expr *e, const char *path) {
    // children[0] = callee ident, children[1..] = args
    Expr *callee_expr = e->children[0];
    const char *name = callee_expr->data.str_val;

    // Built-in: println
    if (strcmp(name, "println") == 0) {
        for (int i = 1; i < e->nchildren; i++) {
            Value arg = eval_expr(scope, e->children[i], path);
            switch (arg.type) {
            case VAL_STR:  printf("%s", arg.str); break;
            case VAL_I64:  printf("%lld", arg.i64); break;
            case VAL_BOOL: printf("%s", arg.boolean ? "true" : "false"); break;
            case VAL_NONE:   printf("(none)"); break;
            case VAL_FUNC:   printf("(func)"); break;
            case VAL_STRUCT: printf("(%s)", arg.instance->struct_name); break;
            }
        }
        printf("\n");
        return val_none();
    }

    // Built-in: print (same but no newline)
    if (strcmp(name, "print") == 0) {
        for (int i = 1; i < e->nchildren; i++) {
            Value arg = eval_expr(scope, e->children[i], path);
            switch (arg.type) {
            case VAL_STR:  printf("%s", arg.str); break;
            case VAL_I64:  printf("%lld", arg.i64); break;
            case VAL_BOOL: printf("%s", arg.boolean ? "true" : "false"); break;
            case VAL_NONE:   printf("(none)"); break;
            case VAL_FUNC:   printf("(func)"); break;
            case VAL_STRUCT: printf("(%s)", arg.instance->struct_name); break;
            }
        }
        return val_none();
    }

    // Built-in: add(a, b)
    if (strcmp(name, "add") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return (Value){.type = VAL_I64, .i64 = a.i64 + b.i64};
    }

    // Built-in: sub(a, b)
    if (strcmp(name, "sub") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return (Value){.type = VAL_I64, .i64 = a.i64 - b.i64};
    }

    // Built-in: mul(a, b)
    if (strcmp(name, "mul") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return (Value){.type = VAL_I64, .i64 = a.i64 * b.i64};
    }

    // Built-in: div(a, b)
    if (strcmp(name, "div") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        if (b.i64 == 0) {
            fprintf(stderr, "%s:%d:%d: runtime error: division by zero\n",
                    path, e->line, e->col);
            exit(1);
        }
        return (Value){.type = VAL_I64, .i64 = a.i64 / b.i64};
    }

    // Built-in: mod(a, b)
    if (strcmp(name, "mod") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        if (b.i64 == 0) {
            fprintf(stderr, "%s:%d:%d: runtime error: division by zero\n",
                    path, e->line, e->col);
            exit(1);
        }
        return (Value){.type = VAL_I64, .i64 = a.i64 % b.i64};
    }

    // Built-in: to_str(val)
    if (strcmp(name, "to_str") == 0) {
        Value v = eval_expr(scope, e->children[1], path);
        if (v.type == VAL_STR) return v;
        if (v.type == VAL_BOOL) return (Value){.type = VAL_STR, .str = v.boolean ? "true" : "false"};
        char *buf = malloc(32);
        snprintf(buf, 32, "%lld", v.i64);
        return (Value){.type = VAL_STR, .str = buf};
    }

    // Built-in: eq(a, b)
    if (strcmp(name, "eq") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return (Value){.type = VAL_BOOL, .boolean = a.i64 == b.i64};
    }

    // Built-in: lt(a, b)
    if (strcmp(name, "lt") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return (Value){.type = VAL_BOOL, .boolean = a.i64 < b.i64};
    }

    // Built-in: gt(a, b)
    if (strcmp(name, "gt") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return (Value){.type = VAL_BOOL, .boolean = a.i64 > b.i64};
    }

    // Built-in: and(a, b)
    if (strcmp(name, "and") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return (Value){.type = VAL_BOOL, .boolean = a.boolean && b.boolean};
    }

    // Built-in: or(a, b)
    if (strcmp(name, "or") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return (Value){.type = VAL_BOOL, .boolean = a.boolean || b.boolean};
    }

    // Built-in: format(..Str) -> Str (variadic)
    if (strcmp(name, "format") == 0) {
        // First pass: compute total length
        int total = 0;
        for (int i = 1; i < e->nchildren; i++) {
            Value v = eval_expr(scope, e->children[i], path);
            total += (int)strlen(v.str);
        }
        char *buf = malloc(total + 1);
        int off = 0;
        for (int i = 1; i < e->nchildren; i++) {
            Value v = eval_expr(scope, e->children[i], path);
            int len = (int)strlen(v.str);
            memcpy(buf + off, v.str, len);
            off += len;
        }
        buf[off] = '\0';
        return (Value){.type = VAL_STR, .str = buf};
    }

    // Built-in: exit(code)
    if (strcmp(name, "exit") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        exit((int)a.i64);
    }

    // Built-in: not(a)
    if (strcmp(name, "not") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        return (Value){.type = VAL_BOOL, .boolean = !a.boolean};
    }

    // User-defined function or struct instantiation
    Value *fn = scope_get(scope, name);
    if (!fn) {
        fprintf(stderr, "%s:%d:%d: runtime error: undefined function '%s'\n",
                path, e->line, e->col, name);
        exit(1);
    }

    // Struct instantiation: Point()
    if (fn->type == VAL_FUNC && fn->func->type == NODE_STRUCT_DEF) {
        Expr *sdef = fn->func;
        Expr *body = sdef->children[0];
        int nfields = body->nchildren;
        StructInstance *inst = malloc(sizeof(StructInstance));
        inst->struct_name = name;
        inst->nfields = nfields;
        inst->field_names = malloc(nfields * sizeof(char *));
        inst->field_muts = malloc(nfields * sizeof(int));
        inst->field_values = malloc(nfields * sizeof(Value));
        for (int i = 0; i < nfields; i++) {
            Expr *field = body->children[i];
            inst->field_names[i] = field->data.decl.name;
            inst->field_muts[i] = field->data.decl.is_mut;
            inst->field_values[i] = eval_expr(scope, field->children[0], path);
        }
        return (Value){.type = VAL_STRUCT, .instance = inst};
    }

    if (fn->type != VAL_FUNC) {
        fprintf(stderr, "%s:%d:%d: runtime error: '%s' is not a function\n",
                path, e->line, e->col, name);
        exit(1);
    }

    Expr *func_def = fn->func;
    Expr *body = func_def->children[0];

    Scope *call_scope = scope_new(scope);
    // Bind arguments to parameters
    for (int i = 0; i < func_def->data.func_def.nparam; i++) {
        Value arg = eval_expr(scope, e->children[i + 1], path);
        scope_set(call_scope, func_def->data.func_def.param_names[i], arg);
    }

    has_return = 0;
    eval_body(call_scope, body, path);
    scope_free(call_scope);

    Value result = val_none();
    if (has_return) {
        result = return_value;
        has_return = 0;
    }
    return result;
}

static Value eval_expr(Scope *scope, Expr *e, const char *path) {
    switch (e->type) {
    case NODE_LITERAL_STR:
        return (Value){.type = VAL_STR, .str = e->data.str_val};
    case NODE_LITERAL_NUM:
        return (Value){.type = VAL_I64, .i64 = atoll(e->data.str_val)};
    case NODE_LITERAL_BOOL:
        return (Value){.type = VAL_BOOL, .boolean = strcmp(e->data.str_val, "true") == 0};
    case NODE_IDENT: {
        Value *v = scope_get(scope, e->data.str_val);
        if (!v) {
            fprintf(stderr, "%s:%d:%d: runtime error: undefined variable '%s'\n",
                    path, e->line, e->col, e->data.str_val);
            exit(1);
        }
        return *v;
    }
    case NODE_FCALL:
        return eval_call(scope, e, path);
    case NODE_FUNC_DEF:
        return (Value){.type = VAL_FUNC, .func = e};
    case NODE_STRUCT_DEF:
        return (Value){.type = VAL_FUNC, .func = e};
    case NODE_FIELD_ACCESS: {
        Value obj = eval_expr(scope, e->children[0], path);
        if (obj.type != VAL_STRUCT) {
            fprintf(stderr, "%s:%d:%d: runtime error: field access on non-struct\n",
                    path, e->line, e->col);
            exit(1);
        }
        const char *fname = e->data.str_val;
        for (int i = 0; i < obj.instance->nfields; i++) {
            if (strcmp(obj.instance->field_names[i], fname) == 0) {
                return obj.instance->field_values[i];
            }
        }
        fprintf(stderr, "%s:%d:%d: runtime error: no field '%s'\n",
                path, e->line, e->col, fname);
        exit(1);
    }
    default:
        fprintf(stderr, "%s:%d:%d: runtime error: cannot evaluate node type %d as expression\n",
                path, e->line, e->col, e->type);
        exit(1);
    }
}

static void eval_body(Scope *scope, Expr *body, const char *path) {
    for (int i = 0; i < body->nchildren; i++) {
        if (has_return) return;
        Expr *stmt = body->children[i];
        switch (stmt->type) {
        case NODE_DECL: {
            Value val = eval_expr(scope, stmt->children[0], path);
            scope_set(scope, stmt->data.decl.name, val);
            break;
        }
        case NODE_ASSIGN: {
            Value val = eval_expr(scope, stmt->children[0], path);
            // Find in current or parent scope
            Value *existing = scope_get(scope, stmt->data.str_val);
            if (!existing) {
                fprintf(stderr, "%s:%d:%d: runtime error: undefined variable '%s'\n",
                        path, stmt->line, stmt->col, stmt->data.str_val);
                exit(1);
            }
            *existing = val;
            break;
        }
        case NODE_FIELD_ASSIGN: {
            // children[0] = object, children[1] = value
            Value obj = eval_expr(scope, stmt->children[0], path);
            Value val = eval_expr(scope, stmt->children[1], path);
            if (obj.type != VAL_STRUCT) {
                fprintf(stderr, "%s:%d:%d: runtime error: field assign on non-struct\n",
                        path, stmt->line, stmt->col);
                exit(1);
            }
            const char *fname = stmt->data.str_val;
            for (int i = 0; i < obj.instance->nfields; i++) {
                if (strcmp(obj.instance->field_names[i], fname) == 0) {
                    obj.instance->field_values[i] = val;
                    break;
                }
            }
            break;
        }
        case NODE_FCALL:
            eval_call(scope, stmt, path);
            break;
        case NODE_BODY: {
            Scope *block_scope = scope_new(scope);
            eval_body(block_scope, stmt, path);
            scope_free(block_scope);
            break;
        }
        case NODE_IF: {
            Value cond = eval_expr(scope, stmt->children[0], path);
            if (cond.boolean) {
                eval_body(scope, stmt->children[1], path);
            } else if (stmt->nchildren > 2) {
                eval_body(scope, stmt->children[2], path);
            }
            break;
        }
        case NODE_WHILE: {
            while (1) {
                if (has_return) break;
                Value cond = eval_expr(scope, stmt->children[0], path);
                if (!cond.boolean) break;
                eval_body(scope, stmt->children[1], path);
            }
            break;
        }
        case NODE_RETURN:
            if (stmt->nchildren > 0) {
                return_value = eval_expr(scope, stmt->children[0], path);
            } else {
                return_value = val_none();
            }
            has_return = 1;
            return;
        default:
            fprintf(stderr, "%s:%d:%d: runtime error: unexpected statement type %d\n",
                    path, stmt->line, stmt->col, stmt->type);
            exit(1);
        }
    }
}

int interpret(Expr *program, const char *mode, const char *path) {
    Scope *global = scope_new(NULL);

    // Evaluate top-level declarations
    eval_body(global, program, path);

    // In cli mode, call main()
    if (mode && strcmp(mode, "cli") == 0) {
        Value *main_fn = scope_get(global, "main");
        if (!main_fn || main_fn->type != VAL_FUNC) {
            fprintf(stderr, "%s: error: mode 'cli' requires a 'main' proc\n", path);
            scope_free(global);
            return 1;
        }
        Expr *func_def = main_fn->func;
        Expr *body = func_def->children[0];
        Scope *main_scope = scope_new(global);
        eval_body(main_scope, body, path);
        scope_free(main_scope);
    }

    scope_free(global);
    return 0;
}
