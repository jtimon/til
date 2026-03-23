#pragma once

#include "../../boot/modes.h"
#include <stdlib.h>
#include <string.h>

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
// Enum payload offset: tag is I32 (4 bytes), aligned to I64 (8 bytes)
#define ENUM_PAYLOAD_OFFSET ((I32)sizeof(I64))

// Compute total flat buffer size for a payload enum.
// Layout: { I32 tag; padding; union payload } where union size = max variant size.
// Get size of a type by name (for enum payload sizing)
static inline I32 type_size_by_name(Str *tname) {
    if (!tname || tname->count == 0) return 0;
    if (tname->count == 3 && memcmp(tname->c_str, "I64", 3) == 0) return sizeof(I64);
    if (tname->count == 2 && memcmp(tname->c_str, "U8", 2) == 0) return sizeof(U8);
    if (tname->count == 3 && memcmp(tname->c_str, "I16", 3) == 0) return sizeof(I16);
    if (tname->count == 3 && memcmp(tname->c_str, "I32", 3) == 0) return sizeof(I32);
    if (tname->count == 3 && memcmp(tname->c_str, "U32", 3) == 0) return sizeof(U32);
    if (tname->count == 3 && memcmp(tname->c_str, "U64", 3) == 0) return sizeof(U64);
    if (tname->count == 5 && memcmp(tname->c_str, "USize", 5) == 0) return sizeof(U32);
    if (tname->count == 3 && memcmp(tname->c_str, "F32", 3) == 0) return sizeof(F32);
    if (tname->count == 4 && memcmp(tname->c_str, "Bool", 4) == 0) return sizeof(Bool);
    if (tname->count == 3 && memcmp(tname->c_str, "Str", 3) == 0) return sizeof(Str);
    // Struct/enum: look up field_struct_def for size, or use pointer size
    return sizeof(void *); // fallback: assume pointer-sized
}

static inline I32 enum_flat_size(Expr *enum_def) {
    if (!enum_def) return (I32)sizeof(I64);
    if (enum_def->total_struct_size > 0) return enum_def->total_struct_size;
    // Compute: ENUM_PAYLOAD_OFFSET + max payload size
    I32 max_psz = 0;
    Expr *body = Expr_child(enum_def, &(USize){0});
    for (U32 i = 0; i < body->children.count; i++) {
        Expr *v = Expr_child(body, &(USize){i});
        if (v->data.data.Decl.is_namespace) continue;
        Str *vtype = &v->data.data.Decl.explicit_type;
        I32 fsz = type_size_by_name(vtype);
        // For struct/enum payloads, use field_struct_def if available
        if (fsz == sizeof(void *) && v->data.data.Decl.field_struct_def)
            fsz = v->data.data.Decl.field_struct_def->total_struct_size;
        if (fsz > max_psz) max_psz = fsz;
    }
    I32 total = ENUM_PAYLOAD_OFFSET + max_psz;
    if (total < (I32)sizeof(I64)) total = sizeof(I64);
    enum_def->total_struct_size = total; // cache for next time
    return total;
}

// Create enum value with flat buffer layout matching compiled C.
// For simple enums (no payload): pass enum_def=NULL, payload_data=NULL, payload_size=0.
// For payload enums: pass pointer to raw payload data and its size.
static inline Value val_enum_flat(Str *enum_name, Expr *enum_def, I32 etag,
                                   void *payload_data, I32 payload_size) {
    Value r;
    r.tag = Value_TAG_Enum;
    r.data.Enum.enum_name = enum_name;
    r.data.Enum.enum_def = enum_def;
    I32 total = ENUM_PAYLOAD_OFFSET + payload_size;
    if (total < (I32)sizeof(I64)) total = sizeof(I64);
    r.data.Enum.data = calloc(1, total);
    r.data.Enum.data_size = total;
    *(I32 *)r.data.Enum.data = etag;
    if (payload_data && payload_size > 0)
        memcpy(r.data.Enum.data + ENUM_PAYLOAD_OFFSET, payload_data, payload_size);
    return r;
}

// Convenience: create simple enum (tag only, no payload)
static inline Value val_enum_simple(Str *enum_name, I32 etag) {
    return val_enum_flat(enum_name, NULL, etag, NULL, 0);
}

// Read tag from enum flat buffer
static inline I32 enum_tag(Value v) {
    return *(I32 *)v.data.Enum.data;
}

// Read payload pointer from enum flat buffer
static inline void *enum_payload_ptr(Value v) {
    return v.data.Enum.data + ENUM_PAYLOAD_OFFSET;
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
