#ifndef TIL_INTERPRETER_H
#define TIL_INTERPRETER_H

#include "ast.h"
#include "ext.h"
#include <stdlib.h>

// Interpret a parsed program. `mode` is the mode string (e.g. "cli").
// Returns 0 on success, non-zero on error.
int interpret(Expr *program, Str *mode, const char *path);

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
    Str *struct_name;
    Str **field_names;
    int *field_muts;
    int nfields;
    Value *field_values;
};

struct Value {
    ValType type;
    union {
        til_I64 *i64;
        til_U8 *u8;
        Str *str;
        til_Bool *boolean;
        Expr *func;
        StructInstance *instance;
    };
};

static inline Value val_none(void) {
    return (Value){.type = VAL_NONE};
}
static inline Value val_i64(til_I64 v) { til_I64 *p = malloc(sizeof(til_I64)); *p = v; return (Value){.type = VAL_I64, .i64 = p}; }
static inline Value val_u8(long long v) { til_U8 *p = malloc(sizeof(til_U8)); *p = (til_U8)(v & 0xFF); return (Value){.type = VAL_U8, .u8 = p}; }
static inline Value val_bool(til_Bool v) { til_Bool *p = malloc(sizeof(til_Bool)); *p = v; return (Value){.type = VAL_BOOL, .boolean = p}; }
static inline Value val_str(Str *v) { return (Value){.type = VAL_STR, .str = v}; }

// --- Cells ---

typedef struct Cell Cell;
struct Cell {
    Value val;
};

// --- Scope ---

typedef struct {
    Str *name;
    Cell *cell;
    int cell_is_local;
} Binding;

typedef struct Scope Scope;
struct Scope {
    Binding *bindings;
    int len;
    int cap;
    Scope *parent;
};

// Functions used by dispatch and precomp
Value eval_expr(Scope *scope, Expr *e, const char *path);
Cell *scope_get(Scope *s, Str *name);
Scope *scope_new(Scope *parent);
void scope_set_owned(Scope *s, Str *name, Value val);
void scope_free(Scope *s);
void interpreter_init_ns(Scope *global, Expr *program, const char *path);

#endif
