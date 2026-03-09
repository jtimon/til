#pragma once
#include "ext.h"

typedef struct Array Array;
typedef struct Map Map;
typedef struct Set Set;
typedef struct Str Str;
typedef struct Vec Vec;
typedef struct StructDef StructDef;
typedef struct EnumDef EnumDef;
typedef struct FunctionDef FunctionDef;
typedef struct Dynamic Dynamic;
typedef struct U8 U8;
typedef struct I16 I16;
typedef struct I32 I32;
typedef struct F32 F32;
typedef struct U32 U32;
typedef struct I64 I64;
typedef struct Range Range;
typedef struct Bool Bool;


typedef struct Map {
    U8 *key_data;
    U8 *val_data;
    I64 count;
    I64 cap;
    I64 key_size;
    Str key_type;
    I64 val_size;
    Str val_type;
} Map;


typedef struct Set {
    U8 *data;
    I64 count;
    I64 cap;
    I64 elem_size;
    Str elem_type;
} Set;



typedef struct Vec {
    U8 *data;
    I64 count;
    I64 cap;
    I64 elem_size;
    Str elem_type;
} Vec;


typedef struct StructDef {
    char _;
} StructDef;


typedef struct EnumDef {
    char _;
} EnumDef;


typedef struct FunctionDef {
    char _;
} FunctionDef;


typedef struct Dynamic {
    char _;
} Dynamic;


typedef struct U8 {
    char _;
} U8;


typedef struct I16 {
    char _;
} I16;


typedef struct I32 {
    char _;
} I32;


typedef struct F32 {
    char _;
} F32;


typedef struct U32 {
    char _;
} U32;


typedef struct I64 {
    char _;
} I64;


typedef struct Range {
    I64 start;
    I64 end;
} Range;


typedef struct Bool {
    char _;
} Bool;


Array * Array_new(Str * elem_type, I64 * elem_size, I64 * cap);
I64 * Array_len(Array * self);
void * Array_get(Array * self, I64 * i);
void Array_set(Array * self, I64 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
I64 * Array_size(void);
Map * Map_new(Str * key_type, I64 * key_size, Str * val_type, I64 * val_size);
I64 * Map_len(Map * self);
Bool * Map_has(Map * self, void * key);
void * Map_get(Map * self, void * key);
void Map_set(Map * self, void * key, void * val);
void Map_delete(Map * self, Bool * call_free);
Map * Map_clone(Map * self);
I64 * Map_size(void);
Set * Set_new(Str * elem_type, I64 * elem_size);
I64 * Set_len(Set * self);
Bool * Set_has(Set * self, void * val);
void Set_add(Set * self, void * val);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
I64 * Set_size(void);
I64 * Str_len(Str * self);
U8 * Str_get(Str * self, I64 * i);
I64 * Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_with_capacity(I64 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_to_str(Str * val);
Str * Str_substr(Str * s, I64 * start, I64 * n);
Bool * Str_contains(Str * a, Str * b);
Bool * Str_starts_with(Str * a, Str * b);
Bool * Str_ends_with(Str * a, Str * b);
Bool * Str_is_empty(Str * self);
I64 * Str_find(Str * self, Str * needle);
I64 * Str_rfind(Str * self, Str * needle);
Str * Str_replace(Str * self, Str * from, Str * to);
Str * Str_get_char(Str * self, I64 * i);
Str * Str_strip_prefix(Str * self, Str * prefix);
Str * Str_strip_suffix(Str * self, Str * suffix);
Str * Str_from_byte(U8 * byte);
I64 * Str_to_i64(Str * self);
I64 * Str_size(void);
Bool * Str_eq(Str * a, Str * b);
Bool * Str_lt(Str * a, Str * b);
Bool * Str_gt(Str * a, Str * b);
Bool * Str_neq(Str * a, Str * b);
Bool * Str_lte(Str * a, Str * b);
Bool * Str_gte(Str * a, Str * b);
Vec * Vec_new(Str * elem_type, I64 * elem_size);
I64 * Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void * Vec_get(Vec * self, I64 * i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
I64 * Vec_size(void);
Vec * split(Str * s, Str * delim);
Str * join(Vec * parts, Str * sep);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool * call_free);
I64 * EnumDef_size(void);
Str * U8_to_str(U8 * val);
U8 * U8_from_i64(I64 * val);
I64 * U8_size(void);
Bool * U8_lt(U8 * a, U8 * b);
Bool * U8_gt(U8 * a, U8 * b);
Bool * U8_neq(U8 * a, U8 * b);
Bool * U8_lte(U8 * a, U8 * b);
Bool * U8_gte(U8 * a, U8 * b);
Str * I16_to_str(I16 * val);
I16 * I16_from_i64(I64 * val);
I16 * I16_neg(I16 * a);
I16 * I16_abs(I16 * a);
I64 * I16_size(void);
Bool * I16_lt(I16 * a, I16 * b);
Bool * I16_gt(I16 * a, I16 * b);
Bool * I16_neq(I16 * a, I16 * b);
Bool * I16_lte(I16 * a, I16 * b);
Bool * I16_gte(I16 * a, I16 * b);
Str * I32_to_str(I32 * val);
I32 * I32_from_i64(I64 * val);
I32 * I32_neg(I32 * a);
I32 * I32_abs(I32 * a);
I64 * I32_size(void);
Bool * I32_lt(I32 * a, I32 * b);
Bool * I32_gt(I32 * a, I32 * b);
Bool * I32_neq(I32 * a, I32 * b);
Bool * I32_lte(I32 * a, I32 * b);
Bool * I32_gte(I32 * a, I32 * b);
F32 * F32_from_i64(I64 * val);
I64 * F32_size(void);
Bool * F32_lt(F32 * a, F32 * b);
Bool * F32_gt(F32 * a, F32 * b);
Bool * F32_neq(F32 * a, F32 * b);
Bool * F32_lte(F32 * a, F32 * b);
Bool * F32_gte(F32 * a, F32 * b);
Str * U32_to_str(U32 * val);
U32 * U32_from_i64(I64 * val);
I64 * U32_size(void);
Bool * U32_lt(U32 * a, U32 * b);
Bool * U32_gt(U32 * a, U32 * b);
Bool * U32_neq(U32 * a, U32 * b);
Bool * U32_lte(U32 * a, U32 * b);
Bool * U32_gte(U32 * a, U32 * b);
Str * I64_to_str(I64 * val);
I64 * I64_neg(I64 * a);
I64 * I64_abs(I64 * a);
I64 * I64_size(void);
Bool * I64_lt(I64 * a, I64 * b);
Bool * I64_gt(I64 * a, I64 * b);
Bool * I64_neq(I64 * a, I64 * b);
Bool * I64_lte(I64 * a, I64 * b);
Bool * I64_gte(I64 * a, I64 * b);
Range * Range_new(I64 * start, I64 * end);
I64 * Range_len(Range * self);
I64 * Range_get(Range * self, I64 * i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
I64 * Range_size(void);
Str * Bool_to_str(Bool * b);
I64 * Bool_cmp(Bool * a, Bool * b);
I64 * Bool_size(void);
Bool * Bool_lt(Bool * a, Bool * b);
Bool * Bool_gt(Bool * a, Bool * b);
Bool * Bool_neq(Bool * a, Bool * b);
Bool * Bool_lte(Bool * a, Bool * b);
Bool * Bool_gte(Bool * a, Bool * b);
void println(Array * parts);
void print(Array * parts);
Str * format(Array * parts);
I64 * wait_cmd(I64 * pid);
I64 * run_cmd(Str * output, Array * args);
void panic(Str * loc_str, Array * parts);
void TODO(Str * loc_str, Array * parts);
void UNREACHABLE(Str * loc_str);
Bool * assertm(Str * loc_str, Bool * cond, Array * parts);
Bool * assert(Str * loc_str, Bool * cond);
void test_expect(Str * loc_str, Bool * cond, Array * parts);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);

