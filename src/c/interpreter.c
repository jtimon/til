#include "interpreter.h"
#include "ext.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Values ---

typedef enum {
    VAL_NONE,
    VAL_I64,
    VAL_U8,
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
        long long *i64;
        const char **str;
        int *boolean;
        Expr *func;
        StructInstance *instance;
    };
};

static Value val_none(void) {
    return (Value){.type = VAL_NONE};
}
static Value val_i64(long long v) { long long *p = malloc(sizeof(long long)); *p = v; return (Value){.type = VAL_I64, .i64 = p}; }
static Value val_u8(long long v) { long long *p = malloc(sizeof(long long)); *p = v & 0xFF; return (Value){.type = VAL_U8, .i64 = p}; }
static Value val_bool(int v) { int *p = malloc(sizeof(int)); *p = v; return (Value){.type = VAL_BOOL, .boolean = p}; }
static Value val_str(const char *v) { const char **p = malloc(sizeof(const char *)); *p = v; return (Value){.type = VAL_STR, .str = p}; }

// --- Cells (heap-allocated value containers) ---

typedef struct Cell Cell;
struct Cell {
    Value val;
};

static Value value_deep_copy(Value v) {
    switch (v.type) {
    case VAL_I64: return val_i64(*v.i64);
    case VAL_U8: return val_u8(*v.i64);
    case VAL_BOOL: return val_bool(*v.boolean);
    case VAL_STR: return val_str(*v.str);
    case VAL_STRUCT: {
        StructInstance *old = v.instance;
        StructInstance *inst = malloc(sizeof(StructInstance));
        inst->struct_name = old->struct_name;
        inst->nfields = old->nfields;
        inst->field_names = malloc(inst->nfields * sizeof(char *));
        inst->field_muts = malloc(inst->nfields * sizeof(int));
        inst->field_values = malloc(inst->nfields * sizeof(Value));
        for (int i = 0; i < inst->nfields; i++) {
            inst->field_names[i] = old->field_names[i];
            inst->field_muts[i] = old->field_muts[i];
            inst->field_values[i] = value_deep_copy(old->field_values[i]);
        }
        return (Value){.type = VAL_STRUCT, .instance = inst};
    }
    default: return v;
    }
}

// --- Return value mechanism ---
static int has_return;
static int has_break;
static int has_continue;
static Value return_value;

// --- Namespace fields (static struct fields) ---

typedef struct {
    const char *struct_name;
    const char *field_name;
    Value val;
} NsField;

static NsField *ns_fields;
static int ns_count;
static int ns_cap;

static Value *ns_get(const char *sname, const char *fname) {
    for (int i = 0; i < ns_count; i++) {
        if (strcmp(ns_fields[i].struct_name, sname) == 0 &&
            strcmp(ns_fields[i].field_name, fname) == 0) {
            return &ns_fields[i].val;
        }
    }
    return NULL;
}

static void ns_set(const char *sname, const char *fname, Value val) {
    Value *existing = ns_get(sname, fname);
    if (existing) { *existing = val; return; }
    if (ns_count >= ns_cap) {
        ns_cap = ns_cap ? ns_cap * 2 : 8;
        ns_fields = realloc(ns_fields, ns_cap * sizeof(NsField));
    }
    ns_fields[ns_count++] = (NsField){sname, fname, val};
}

// --- Scope / environment ---

typedef struct {
    const char *name;
    Cell *cell;
    int cell_is_local; // 1 = cell malloc'd by this scope, 0 = shared from caller
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
    for (int i = 0; i < s->len; i++) {
        if (s->bindings[i].cell_is_local) {
            free(s->bindings[i].cell);
        }
    }
    free(s->bindings);
    free(s);
}

static void scope_set_owned(Scope *s, const char *name, Value val) {
    // Check if already exists in this scope
    for (int i = 0; i < s->len; i++) {
        if (strcmp(s->bindings[i].name, name) == 0) {
            s->bindings[i].cell->val = val;
            return;
        }
    }
    // Add new binding with a locally allocated cell
    Cell *cell = malloc(sizeof(Cell));
    cell->val = val;
    if (s->len >= s->cap) {
        s->cap = s->cap ? s->cap * 2 : 8;
        s->bindings = realloc(s->bindings, s->cap * sizeof(Binding));
    }
    s->bindings[s->len++] = (Binding){name, cell, 1};
}

static void scope_set_borrowed(Scope *s, const char *name, Cell *cell) {
    if (s->len >= s->cap) {
        s->cap = s->cap ? s->cap * 2 : 8;
        s->bindings = realloc(s->bindings, s->cap * sizeof(Binding));
    }
    s->bindings[s->len++] = (Binding){name, cell, 0};
}

static Cell *scope_get(Scope *s, const char *name) {
    for (Scope *cur = s; cur; cur = cur->parent) {
        for (int i = 0; i < cur->len; i++) {
            if (strcmp(cur->bindings[i].name, name) == 0) {
                return cur->bindings[i].cell;
            }
        }
    }
    return NULL;
}

// --- Eval ---

static Value eval_expr(Scope *scope, Expr *e, const char *path);
static void eval_body(Scope *scope, Expr *body, const char *path);

static Value eval_call(Scope *scope, Expr *e, const char *path) {
    // children[0] = callee ident or field access, children[1..] = args
    Expr *callee_expr = e->children[0];

    // Namespace method call: Struct.method(args)
    if (callee_expr->type == NODE_FIELD_ACCESS) {
        Value fn_val = eval_expr(scope, callee_expr, path);
        if (fn_val.type != VAL_FUNC) {
            fprintf(stderr, "%s:%d:%d: runtime error: namespace field is not a function\n",
                    path, e->line, e->col);
            exit(1);
        }
        Expr *func_def = fn_val.func;
        Expr *body = func_def->children[0];
        Scope *call_scope = scope_new(scope);
        for (int i = 0; i < func_def->data.func_def.nparam; i++) {
            Expr *arg_expr = e->children[i + 1];
            if (arg_expr->type == NODE_IDENT) {
                Cell *arg_cell = scope_get(scope, arg_expr->data.str_val);
                scope_set_borrowed(call_scope, func_def->data.func_def.param_names[i], arg_cell);
            } else {
                Value arg = eval_expr(scope, arg_expr, path);
                scope_set_owned(call_scope, func_def->data.func_def.param_names[i], arg);
            }
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

    const char *name = callee_expr->data.str_val;

    // Built-in: println
    if (strcmp(name, "println") == 0) {
        for (int i = 1; i < e->nchildren; i++) {
            Value arg = eval_expr(scope, e->children[i], path);
            switch (arg.type) {
            case VAL_STR:  printf("%s", *arg.str); break;
            case VAL_I64:  printf("%lld", *arg.i64); break;
            case VAL_U8:   printf("%u", (unsigned)*arg.i64); break;
            case VAL_BOOL: printf("%s", *arg.boolean ? "true" : "false"); break;
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
            case VAL_STR:  printf("%s", *arg.str); break;
            case VAL_I64:  printf("%lld", *arg.i64); break;
            case VAL_U8:   printf("%u", (unsigned)*arg.i64); break;
            case VAL_BOOL: printf("%s", *arg.boolean ? "true" : "false"); break;
            case VAL_NONE:   printf("(none)"); break;
            case VAL_FUNC:   printf("(func)"); break;
            case VAL_STRUCT: printf("(%s)", arg.instance->struct_name); break;
            }
        }
        return val_none();
    }

    // Built-in: i64_add(a, b)
    if (strcmp(name, "i64_add") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_i64(*a.i64 + *b.i64);
    }

    // Built-in: i64_sub(a, b)
    if (strcmp(name, "i64_sub") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_i64(*a.i64 - *b.i64);
    }

    // Built-in: i64_mul(a, b)
    if (strcmp(name, "i64_mul") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_i64(*a.i64 * *b.i64);
    }

    // Built-in: i64_div(a, b)
    if (strcmp(name, "i64_div") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_i64(*b.i64 == 0 ? 0 : *a.i64 / *b.i64);
    }

    // Built-in: i64_mod(a, b)
    if (strcmp(name, "i64_mod") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_i64(*b.i64 == 0 ? 0 : *a.i64 % *b.i64);
    }

    // Built-in: i64_to_str(val)
    if (strcmp(name, "i64_to_str") == 0) {
        Value v = eval_expr(scope, e->children[1], path);
        return (Value){.type = VAL_STR, .str = til_i64_to_str(v.i64)};
    }

    // Built-in: i64_eq(a, b)
    if (strcmp(name, "i64_eq") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_bool(*a.i64 == *b.i64);
    }

    // Built-in: i64_lt(a, b)
    if (strcmp(name, "i64_lt") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_bool(*a.i64 < *b.i64);
    }

    // Built-in: i64_gt(a, b)
    if (strcmp(name, "i64_gt") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_bool(*a.i64 > *b.i64);
    }

    // Built-in: i64_and(a, b)
    if (strcmp(name, "i64_and") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_i64(*a.i64 & *b.i64);
    }

    // Built-in: i64_or(a, b)
    if (strcmp(name, "i64_or") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_i64(*a.i64 | *b.i64);
    }

    // Built-in: i64_xor(a, b)
    if (strcmp(name, "i64_xor") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_i64(*a.i64 ^ *b.i64);
    }

    // Built-in: u8_add(a, b)
    if (strcmp(name, "u8_add") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_u8(*a.i64 + *b.i64);
    }

    // Built-in: u8_sub(a, b)
    if (strcmp(name, "u8_sub") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_u8(*a.i64 - *b.i64 + 256);
    }

    // Built-in: u8_mul(a, b)
    if (strcmp(name, "u8_mul") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_u8(*a.i64 * *b.i64);
    }

    // Built-in: u8_div(a, b)
    if (strcmp(name, "u8_div") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_u8(*b.i64 == 0 ? 0 : *a.i64 / *b.i64);
    }

    // Built-in: u8_mod(a, b)
    if (strcmp(name, "u8_mod") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_u8(*b.i64 == 0 ? 0 : *a.i64 % *b.i64);
    }

    // Built-in: u8_eq(a, b)
    if (strcmp(name, "u8_eq") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_bool(*a.i64 == *b.i64);
    }

    // Built-in: u8_lt(a, b)
    if (strcmp(name, "u8_lt") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_bool(*a.i64 < *b.i64);
    }

    // Built-in: u8_gt(a, b)
    if (strcmp(name, "u8_gt") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_bool(*a.i64 > *b.i64);
    }

    // Built-in: u8_and(a, b)
    if (strcmp(name, "u8_and") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_u8(*a.i64 & *b.i64);
    }

    // Built-in: u8_or(a, b)
    if (strcmp(name, "u8_or") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_u8(*a.i64 | *b.i64);
    }

    // Built-in: u8_xor(a, b)
    if (strcmp(name, "u8_xor") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_u8(*a.i64 ^ *b.i64);
    }

    // Built-in: u8_to_str(val)
    if (strcmp(name, "u8_to_str") == 0) {
        Value v = eval_expr(scope, e->children[1], path);
        return (Value){.type = VAL_STR, .str = til_u8_to_str((unsigned char *)v.i64)};
    }

    // Built-in: u8_to_i64(val)
    if (strcmp(name, "u8_to_i64") == 0) {
        Value v = eval_expr(scope, e->children[1], path);
        return val_i64(*v.i64);
    }

    // Built-in: u8_from_i64(val)
    if (strcmp(name, "u8_from_i64") == 0) {
        Value v = eval_expr(scope, e->children[1], path);
        return val_u8(*v.i64);
    }

    // Built-in: bool_and(a, b)
    if (strcmp(name, "bool_and") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_bool(*a.boolean && *b.boolean);
    }

    // Built-in: bool_or(a, b)
    if (strcmp(name, "bool_or") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return val_bool(*a.boolean || *b.boolean);
    }

    // Built-in: str_eq(a, b)
    if (strcmp(name, "str_eq") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        Value b = eval_expr(scope, e->children[2], path);
        return (Value){.type = VAL_BOOL, .boolean = til_str_eq(a.str, b.str)};
    }

    // Built-in: format(..Str) -> Str (variadic)
    if (strcmp(name, "format") == 0) {
        int nargs = e->nchildren - 1;
        const char *strs[64];
        int total = 0;
        for (int i = 0; i < nargs; i++) {
            Value v = eval_expr(scope, e->children[i + 1], path);
            strs[i] = *v.str;
            total += (int)strlen(strs[i]);
        }
        char *buf = malloc(total + 1);
        int off = 0;
        for (int i = 0; i < nargs; i++) {
            int len = (int)strlen(strs[i]);
            memcpy(buf + off, strs[i], len);
            off += len;
        }
        buf[off] = '\0';
        return val_str(buf);
    }

    // Built-in: exit(code)
    if (strcmp(name, "exit") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        til_exit(a.i64);
    }

    // Built-in: bool_not(a)
    if (strcmp(name, "bool_not") == 0) {
        Value a = eval_expr(scope, e->children[1], path);
        return val_bool(!*a.boolean);
    }

    // Built-in: free(val)
    if (strcmp(name, "free") == 0) {
        Cell *cell = scope_get(scope, e->children[1]->data.str_val);
        if (cell->val.type == VAL_STRUCT && cell->val.instance) {
            til_free(cell->val.instance->field_names);
            til_free(cell->val.instance->field_muts);
            til_free(cell->val.instance->field_values);
            til_free(cell->val.instance);
        } else if (cell->val.type == VAL_I64 || cell->val.type == VAL_U8) {
            til_free(cell->val.i64);
        } else if (cell->val.type == VAL_BOOL) {
            til_free(cell->val.boolean);
        } else if (cell->val.type == VAL_STR) {
            til_free(cell->val.str);
        }
        cell->val = val_none();
        return val_none();
    }

    // User-defined function or struct instantiation
    Cell *fn_cell = scope_get(scope, name);
    if (!fn_cell) {
        fprintf(stderr, "%s:%d:%d: runtime error: undefined function '%s'\n",
                path, e->line, e->col, name);
        exit(1);
    }

    // Struct instantiation: Point() or Point(x=1)
    if (fn_cell->val.type == VAL_FUNC && fn_cell->val.func->type == NODE_STRUCT_DEF) {
        Expr *sdef = fn_cell->val.func;
        Expr *body = sdef->children[0];
        // Count instance fields (skip namespace)
        int nfields = 0;
        for (int i = 0; i < body->nchildren; i++) {
            if (!body->children[i]->data.decl.is_namespace) nfields++;
        }
        StructInstance *inst = malloc(sizeof(StructInstance));
        inst->struct_name = name;
        inst->nfields = nfields;
        inst->field_names = malloc(nfields * sizeof(char *));
        inst->field_muts = malloc(nfields * sizeof(int));
        inst->field_values = malloc(nfields * sizeof(Value));
        int arg_idx = 1; // index into desugared args
        int fi = 0;      // index into instance fields
        for (int i = 0; i < body->nchildren; i++) {
            Expr *field = body->children[i];
            if (field->data.decl.is_namespace) continue;
            inst->field_names[fi] = field->data.decl.name;
            inst->field_muts[fi] = field->data.decl.is_mut;
            if (e->nchildren > 1) {
                inst->field_values[fi] = eval_expr(scope, e->children[arg_idx++], path);
            } else {
                inst->field_values[fi] = eval_expr(scope, field->children[0], path);
            }
            fi++;
        }
        return (Value){.type = VAL_STRUCT, .instance = inst};
    }

    if (fn_cell->val.type != VAL_FUNC) {
        fprintf(stderr, "%s:%d:%d: runtime error: '%s' is not a function\n",
                path, e->line, e->col, name);
        exit(1);
    }

    Expr *func_def = fn_cell->val.func;
    Expr *body = func_def->children[0];

    Scope *call_scope = scope_new(scope);
    // Bind arguments to parameters (borrowed refs for idents, owned for expressions)
    for (int i = 0; i < func_def->data.func_def.nparam; i++) {
        Expr *arg_expr = e->children[i + 1];
        if (arg_expr->type == NODE_IDENT) {
            Cell *arg_cell = scope_get(scope, arg_expr->data.str_val);
            scope_set_borrowed(call_scope, func_def->data.func_def.param_names[i], arg_cell);
        } else {
            Value arg = eval_expr(scope, arg_expr, path);
            scope_set_owned(call_scope, func_def->data.func_def.param_names[i], arg);
        }
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
        return val_str(e->data.str_val);
    case NODE_LITERAL_NUM:
        if (e->til_type == TIL_TYPE_U8)
            return val_u8(atoll(e->data.str_val));
        return val_i64(atoll(e->data.str_val));
    case NODE_LITERAL_BOOL:
        return val_bool(strcmp(e->data.str_val, "true") == 0);
    case NODE_IDENT: {
        Cell *cell = scope_get(scope, e->data.str_val);
        if (!cell) {
            fprintf(stderr, "%s:%d:%d: runtime error: undefined variable '%s'\n",
                    path, e->line, e->col, e->data.str_val);
            exit(1);
        }
        return value_deep_copy(cell->val);
    }
    case NODE_FCALL:
        return eval_call(scope, e, path);
    case NODE_FUNC_DEF:
        return (Value){.type = VAL_FUNC, .func = e};
    case NODE_STRUCT_DEF:
        return (Value){.type = VAL_FUNC, .func = e};
    case NODE_FIELD_ACCESS: {
        Value obj = eval_expr(scope, e->children[0], path);
        const char *fname = e->data.str_val;
        if (e->is_ns_field) {
            const char *sname = obj.type == VAL_STRUCT
                ? obj.instance->struct_name : e->children[0]->data.str_val;
            Value *nsv = ns_get(sname, fname);
            if (nsv) return *nsv;
            fprintf(stderr, "%s:%d:%d: runtime error: no namespace field '%s'\n",
                    path, e->line, e->col, fname);
            exit(1);
        }
        if (obj.type != VAL_STRUCT) {
            fprintf(stderr, "%s:%d:%d: runtime error: field access on non-struct\n",
                    path, e->line, e->col);
            exit(1);
        }
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
        if (has_return || has_break || has_continue) return;
        Expr *stmt = body->children[i];
        switch (stmt->type) {
        case NODE_DECL: {
            Value val = eval_expr(scope, stmt->children[0], path);
            scope_set_owned(scope, stmt->data.decl.name, val);
            break;
        }
        case NODE_ASSIGN: {
            Value val = eval_expr(scope, stmt->children[0], path);
            Cell *cell = scope_get(scope, stmt->data.str_val);
            if (!cell) {
                fprintf(stderr, "%s:%d:%d: runtime error: undefined variable '%s'\n",
                        path, stmt->line, stmt->col, stmt->data.str_val);
                exit(1);
            }
            cell->val = val;
            break;
        }
        case NODE_FIELD_ASSIGN: {
            Value val = eval_expr(scope, stmt->children[1], path);
            const char *fname = stmt->data.str_val;
            if (stmt->is_ns_field) {
                Value obj = eval_expr(scope, stmt->children[0], path);
                const char *sname = obj.type == VAL_STRUCT
                    ? obj.instance->struct_name : stmt->children[0]->data.str_val;
                ns_set(sname, fname, val);
            } else {
                // Resolve the object to a mutable StructInstance without copying
                StructInstance *inst = NULL;
                Expr *obj_expr = stmt->children[0];
                if (obj_expr->type == NODE_IDENT) {
                    Cell *cell = scope_get(scope, obj_expr->data.str_val);
                    if (cell && cell->val.type == VAL_STRUCT) inst = cell->val.instance;
                } else if (obj_expr->type == NODE_FIELD_ACCESS) {
                    // Chained: e.g. l1.start.x — resolve l1.start to its StructInstance
                    // Walk the chain: find root ident, then follow fields
                    Expr *chain[32]; int depth = 0;
                    Expr *cur = obj_expr;
                    while (cur->type == NODE_FIELD_ACCESS) {
                        chain[depth++] = cur;
                        cur = cur->children[0];
                    }
                    Cell *cell = scope_get(scope, cur->data.str_val);
                    if (cell && cell->val.type == VAL_STRUCT) {
                        inst = cell->val.instance;
                        for (int d = depth - 1; d >= 0; d--) {
                            const char *fn = chain[d]->data.str_val;
                            StructInstance *next = NULL;
                            for (int j = 0; j < inst->nfields; j++) {
                                if (strcmp(inst->field_names[j], fn) == 0 &&
                                    inst->field_values[j].type == VAL_STRUCT) {
                                    next = inst->field_values[j].instance;
                                    break;
                                }
                            }
                            inst = next;
                            if (!inst) break;
                        }
                    }
                }
                if (!inst) {
                    fprintf(stderr, "%s:%d:%d: runtime error: field assign on non-struct\n",
                            path, stmt->line, stmt->col);
                    exit(1);
                }
                for (int i = 0; i < inst->nfields; i++) {
                    if (strcmp(inst->field_names[i], fname) == 0) {
                        inst->field_values[i] = val;
                        break;
                    }
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
            if (*cond.boolean) {
                Scope *then_scope = scope_new(scope);
                eval_body(then_scope, stmt->children[1], path);
                scope_free(then_scope);
            } else if (stmt->nchildren > 2) {
                Scope *else_scope = scope_new(scope);
                eval_body(else_scope, stmt->children[2], path);
                scope_free(else_scope);
            }
            break;
        }
        case NODE_WHILE: {
            while (1) {
                if (has_return) break;
                Value cond = eval_expr(scope, stmt->children[0], path);
                if (!*cond.boolean) break;
                Scope *while_scope = scope_new(scope);
                eval_body(while_scope, stmt->children[1], path);
                scope_free(while_scope);
                if (has_break) { has_break = 0; break; }
                if (has_continue) { has_continue = 0; }
            }
            break;
        }
        case NODE_BREAK:
            has_break = 1;
            return;
        case NODE_CONTINUE:
            has_continue = 1;
            return;
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

    // Pre-register all top-level func/proc/struct definitions for forward references
    ns_fields = NULL; ns_count = 0; ns_cap = 0;
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL &&
            (stmt->children[0]->type == NODE_FUNC_DEF ||
             stmt->children[0]->type == NODE_STRUCT_DEF)) {
            Value val = {.type = VAL_FUNC, .func = stmt->children[0]};
            scope_set_owned(global, stmt->data.decl.name, val);
        }
    }

    // Initialize namespace fields for all structs
    for (int i = 0; i < program->nchildren; i++) {
        Expr *stmt = program->children[i];
        if (stmt->type == NODE_DECL && stmt->children[0]->type == NODE_STRUCT_DEF) {
            const char *sname = stmt->data.decl.name;
            Expr *body = stmt->children[0]->children[0];
            for (int j = 0; j < body->nchildren; j++) {
                Expr *field = body->children[j];
                if (field->data.decl.is_namespace) {
                    Value fval = eval_expr(global, field->children[0], path);
                    ns_set(sname, field->data.decl.name, fval);
                }
            }
        }
    }

    // Evaluate top-level declarations
    eval_body(global, program, path);

    // In cli mode, call main()
    if (mode && strcmp(mode, "cli") == 0) {
        Cell *main_cell = scope_get(global, "main");
        if (!main_cell || main_cell->val.type != VAL_FUNC) {
            fprintf(stderr, "%s: error: mode 'cli' requires a 'main' proc\n", path);
            scope_free(global);
            return 1;
        }
        Expr *func_def = main_cell->val.func;
        Expr *body = func_def->children[0];
        Scope *main_scope = scope_new(global);
        eval_body(main_scope, body, path);
        scope_free(main_scope);
    }

    scope_free(global);
    return 0;
}
