#ifndef TIL_INTERPRETER_H
#define TIL_INTERPRETER_H

#include "ast.h"
#include "ext.h"
#include "map.h"
#include <stdlib.h>

// Interpret a parsed program. `mode` is the mode string (e.g. "cli").
// Returns 0 on success, non-zero on error.
I32 interpret(Expr *program, Str *mode, const char *path, const char *user_c_path, const char *ext_c_path, const char *link_flags, I32 user_argc, char **user_argv);

// --- Values ---

typedef enum {
    VAL_NONE,
    VAL_I64,
    VAL_U8,
    VAL_BOOL,
    VAL_FUNC,   // pointer to a func/proc AST node
    VAL_STRUCT, // struct instance (including Str)
    VAL_ENUM,   // enum instance (tagged union with optional payload)
    VAL_PTR,    // raw buffer (Value array for malloc/ptr_add/memcpy)
} ValType;

typedef struct StructInstance StructInstance;
typedef struct EnumInstance EnumInstance;
typedef struct Value Value;

struct StructInstance {
    Str *struct_name;       // borrowed from AST (no alloc, no free)
    Expr *struct_def;       // borrowed pointer to NODE_STRUCT_DEF
    void *data;             // flat buffer, same layout as C struct
};

struct Value {
    ValType type;
    union {
        til_I64 *i64;
        til_U8 *u8;
        til_Bool *boolean;
        Expr *func;
        StructInstance *instance;
        EnumInstance *enum_inst;
        void *ptr;
    };
};

struct EnumInstance {
    Str *enum_name;
    I32 tag;
    Value payload;  // VAL_NONE for no-payload variants
};

static inline Value val_none(void) {
    return (Value){.type = VAL_NONE};
}
static inline Value val_i64(til_I64 v) { til_I64 *p = malloc(sizeof(til_I64)); *p = v; return (Value){.type = VAL_I64, .i64 = p}; }
static inline Value val_u8(I64 v) { til_U8 *p = malloc(sizeof(til_U8)); *p = (til_U8)(v & 0xFF); return (Value){.type = VAL_U8, .u8 = p}; }
static inline Value val_bool(til_Bool v) { til_Bool *p = malloc(sizeof(til_Bool)); *p = v; return (Value){.type = VAL_BOOL, .boolean = p}; }
static inline Value val_enum(Str *enum_name, I32 tag, Value payload) {
    EnumInstance *ei = malloc(sizeof(EnumInstance));
    ei->enum_name = enum_name;
    ei->tag = tag;
    ei->payload = payload;
    return (Value){.type = VAL_ENUM, .enum_inst = ei};
}

// --- Cells ---

typedef struct Cell Cell;
struct Cell {
    Value val;
};

// --- Scope ---

typedef struct {
    Str *name;
    Cell *cell;
    Bool cell_is_local;
} Binding;

typedef struct Scope Scope;
struct Scope {
    Map bindings;
    Scope *parent;
};

// Functions used by dispatch and precomp
Value eval_expr(Scope *scope, Expr *e);
Value eval_call(Scope *scope, Expr *e);
Value clone_value(Value v);
void free_value(Value v);
Bool values_equal(Value a, Value b);
Cell *scope_get(Scope *s, Str *name);
Scope *scope_new(Scope *parent);
void scope_set_owned(Scope *s, Str *name, Value val);
void scope_free(Scope *s);
void interpreter_init_ns(Scope *global, Expr *program);
Value *ns_get(Str *sname, Str *fname);

// Str StructInstance helpers (used by dispatch.c and precomp.c)
Value make_str_value(const char *data, I64 cap);
Value make_str_value_own(char *data, I64 cap);
Str str_view(Value v);

// Cached struct defs for C-side construction (set during interpreter_init_ns)
extern Expr *cached_str_def;
extern Str *cached_str_name;
extern Expr *cached_array_def;
extern Str *cached_array_name;
extern Expr *cached_vec_def;
extern Str *cached_vec_name;

// Find a non-namespace field decl by name in a struct_def
Expr *find_field_decl(Expr *struct_def, Str *fname);

// Write a Value into flat buffer at a field decl's offset
void write_field(StructInstance *inst, Expr *fdecl, Value val);

#endif
