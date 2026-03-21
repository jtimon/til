#pragma once

#include "../../boot/modes.h"
#include <stdlib.h>

// Interpret a parsed program. Returns 0 on success, non-zero on error.
// If run_tests is true, ignores main/script body and runs all test functions.
I32 interpret(Expr *program, Mode *mode, Bool run_tests, Str *path, Str *user_c_path, Str *ext_c_path, Str *link_flags, Vec *user_argv);

// --- Value constructors ---
// Types (Value, StructInstance, EnumInstance, Cell, Binding, Scope)
// are defined in interpreter.til and generated into boot/modes.h.

static inline Value val_none(void) {
    return (Value){.tag = Value_TAG_None};
}
static inline Value val_i64(I64 v) { return (Value){.tag = Value_TAG_Int, .data.Int = v}; }
static inline Value val_u8(I64 v) { return (Value){.tag = Value_TAG_Byte, .data.Byte = (U8)(v & 0xFF)}; }
static inline Value val_i16(I64 v) { return (Value){.tag = Value_TAG_Short, .data.Short = (I16)v}; }
static inline Value val_i32(I64 v) { return (Value){.tag = Value_TAG_Int32, .data.Int32 = (I32)v}; }
static inline Value val_u32(I64 v) { return (Value){.tag = Value_TAG_Uint32, .data.Uint32 = (U32)(v & 0xFFFFFFFF)}; }
static inline Value val_u64(U64 v) { return (Value){.tag = Value_TAG_Uint64, .data.Uint64 = v}; }
static inline Value val_f32(F32 v) { return (Value){.tag = Value_TAG_Float, .data.Float = v}; }
static inline Value val_bool(Bool v) { return (Value){.tag = Value_TAG_Boolean, .data.Boolean = v}; }
static inline Value val_enum(Str *enum_name, I32 etag, Value payload) {
    Value r;
    r.tag = Value_TAG_Enum;
    r.data.Enum.enum_name = enum_name;
    r.data.Enum.tag = etag;
    r.data.Enum.payload = malloc(sizeof(Value));
    *r.data.Enum.payload = payload;
    return r;
}

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
