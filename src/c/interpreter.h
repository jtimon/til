#ifndef TIL_INTERPRETER_H
#define TIL_INTERPRETER_H

#include "../../bootstrap/ast.h"
#include "modes.h"
#include <stdlib.h>

// Interpret a parsed program. Returns 0 on success, non-zero on error.
// If run_tests is true, ignores main/script body and runs all test functions.
I32 interpret(Expr *program, const Mode *mode, Bool run_tests, Str *path, Str *user_c_path, Str *ext_c_path, Str *link_flags, Vec *user_argv);

// --- Values ---

typedef enum {
    VAL_NONE,
    VAL_I64,
    VAL_U8,
    VAL_I16,
    VAL_I32,
    VAL_U32,
    VAL_U64,
    VAL_F32,
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
    Bool borrowed;          // if true, data points into parent buffer — don't free
};

struct Value {
    ValType type;
    union {
        I64 *i64;
        U8 *u8;
        I16 *i16;
        I32 *i32;
        U32 *u32;
        U64 *u64;
        F32 *f32;
        Bool *boolean;
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
static inline Value val_i64(I64 v) { I64 *p = malloc(sizeof(I64)); *p = v; return (Value){.type = VAL_I64, .i64 = p}; }
static inline Value val_u8(I64 v) { U8 *p = malloc(sizeof(U8)); *p = (U8)(v & 0xFF); return (Value){.type = VAL_U8, .u8 = p}; }
static inline Value val_i16(I64 v) { I16 *p = malloc(sizeof(I16)); *p = (I16)v; return (Value){.type = VAL_I16, .i16 = p}; }
static inline Value val_i32(I64 v) { I32 *p = malloc(sizeof(I32)); *p = (I32)v; return (Value){.type = VAL_I32, .i32 = p}; }
static inline Value val_u32(I64 v) { U32 *p = malloc(sizeof(U32)); *p = (U32)(v & 0xFFFFFFFF); return (Value){.type = VAL_U32, .u32 = p}; }
static inline Value val_u64(U64 v) { U64 *p = malloc(sizeof(U64)); *p = v; return (Value){.type = VAL_U64, .u64 = p}; }
static inline Value val_f32(F32 v) { F32 *p = malloc(sizeof(F32)); *p = v; return (Value){.type = VAL_F32, .f32 = p}; }
static inline Value val_bool(Bool v) { Bool *p = malloc(sizeof(Bool)); *p = v; return (Value){.type = VAL_BOOL, .boolean = p}; }
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
Value make_str_value(const char *data, U64 len);
Value make_str_value_own(char *data, U64 len);
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
