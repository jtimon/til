#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef struct Array Array;
typedef struct Vec Vec;
typedef struct Str Str;
typedef struct Dynamic Dynamic;

typedef void * (*CloneFn)(void *);
typedef void (*DeleteFn)(void *, Bool *);

typedef struct Str {
    U8 *c_str;
    U32 count;
    U32 cap;
} Str;










typedef struct Dynamic {
    char _;
} Dynamic;


typedef struct Array {
    U8 *data;
    U32 cap;
    U32 elem_size;
    Str elem_type;
    void * elem_clone;
    void * elem_delete;
} Array;


typedef struct Vec {
    U8 *data;
    U32 count;
    U32 cap;
    U32 elem_size;
    Str elem_type;
    void * elem_clone;
    void * elem_delete;
} Vec;


Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap);
U32 * Array_len(Array * self);
void * Array_get(Array * self, U32 * i);
void Array_set(Array * self, U32 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
Vec * Vec_new(Str * elem_type, U32 * elem_size);
U32 Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void Vec_append(Vec * self, Vec * other);
void Vec_move_from(Vec * self, Vec * other);
void * Vec_get(Vec * self, U32 * i);
void * Vec_pop(Vec * self);
Vec * Vec_take_prefix(Vec * self, U32 * n);
void Vec_set(Vec * self, U32 * i, void * val);
void Vec_push_take(Vec * self, Vec * src, U32 i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U32 Vec_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
U8 * Str_get(Str * self, U32 * i);
U8 * Str_byte_at(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_with_capacity(U32 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_to_str(Str * val);
Str * Str_substr(Str * s, U32 * start, U32 * n);
Bool Str_contains(Str * a, Str * b);
Bool Str_starts_with(Str * a, Str * b);
Bool Str_ends_with(Str * a, Str * b);
Bool Str_is_empty(Str * self);
I64 Str_find(Str * self, Str * needle);
I64 Str_rfind(Str * self, Str * needle);
Str * Str_replace(Str * self, Str * from, Str * to);
Str * Str_get_char(Str * self, U32 * i);
Str * Str_strip_prefix(Str * self, Str * prefix);
Str * Str_strip_suffix(Str * self, Str * suffix);
Str * Str_from_byte(U8 * byte);
I64 Str_to_i64(Str * self);
U8 Str_to_u8(Str * self);
I32 Str_to_i32(Str * self);
F32 Str_to_f32(Str * self);
Vec * Str_split(Str * self, Str * delim);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
Bool Str_lt(Str * a, Str * b);
Bool Str_gt(Str * a, Str * b);
Bool Str_neq(Str * a, Str * b);
Bool Str_lte(Str * a, Str * b);
Bool Str_gte(Str * a, Str * b);
Str * U8_to_str(U8 * val);
void U8_inc(U8 * self);
void U8_dec(U8 * self);
U8 * U8_unity(U8 * _self);
U64 U8_distance(void * a, void * b);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Bool U8_lt(U8 * a, U8 * b);
Bool U8_gt(U8 * a, U8 * b);
Bool U8_neq(U8 * a, U8 * b);
Bool U8_lte(U8 * a, U8 * b);
Bool U8_gte(U8 * a, U8 * b);
Str * I16_to_str(I16 * val);
void I16_inc(I16 * self);
void I16_dec(I16 * self);
I16 * I16_unity(I16 * _self);
I16 * I16_neg(I16 * a);
I16 * I16_abs(I16 * a);
U64 I16_distance(void * a, void * b);
void I16_delete(I16 * self, Bool * call_free);
U32 * I16_size(void);
Bool I16_lt(I16 * a, I16 * b);
Bool I16_gt(I16 * a, I16 * b);
Bool I16_neq(I16 * a, I16 * b);
Bool I16_lte(I16 * a, I16 * b);
Bool I16_gte(I16 * a, I16 * b);
Str * I32_to_str(I32 * val);
void I32_inc(I32 * self);
void I32_dec(I32 * self);
I32 * I32_unity(I32 * _self);
I32 * I32_neg(I32 * a);
I32 * I32_abs(I32 * a);
U64 I32_distance(void * a, void * b);
void I32_delete(I32 * self, Bool * call_free);
U32 * I32_size(void);
Bool I32_lt(I32 * a, I32 * b);
Bool I32_gt(I32 * a, I32 * b);
Bool I32_neq(I32 * a, I32 * b);
Bool I32_lte(I32 * a, I32 * b);
Bool I32_gte(I32 * a, I32 * b);
F32 * F32_from_i64(I64 * val);
void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
Bool F32_lt(F32 * a, F32 * b);
Bool F32_gt(F32 * a, F32 * b);
Bool F32_neq(F32 * a, F32 * b);
Bool F32_lte(F32 * a, F32 * b);
Bool F32_gte(F32 * a, F32 * b);
Str * U32_to_str(U32 * val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
U32 * U32_unity(U32 * _self);
U64 U32_distance(void * a, void * b);
void U32_delete(U32 * self, Bool * call_free);
U32 * U32_size(void);
Bool U32_lt(U32 * a, U32 * b);
Bool U32_gt(U32 * a, U32 * b);
Bool U32_neq(U32 * a, U32 * b);
Bool U32_lte(U32 * a, U32 * b);
Bool U32_gte(U32 * a, U32 * b);
Str * U64_to_str(U64 val);
U64 * U64_from_i64(I64 * val);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
U64 * U64_unity(U64 * _self);
U64 U64_distance(void * a, void * b);
void U64_delete(U64 * self, Bool * call_free);
U32 * U64_size(void);
Bool U64_lt(U64 * a, U64 * b);
Bool U64_gt(U64 * a, U64 * b);
Bool U64_neq(U64 * a, U64 * b);
Bool U64_lte(U64 * a, U64 * b);
Bool U64_gte(U64 * a, U64 * b);
Str * I64_to_str(I64 * val);
U32 I64_to_usize(I64 val);
void I64_inc(I64 * self);
void I64_dec(I64 * self);
I64 * I64_unity(I64 * _self);
I64 * I64_neg(I64 * a);
I64 * I64_abs(I64 * a);
U64 I64_distance(void * a, void * b);
void I64_delete(I64 * self, Bool * call_free);
U32 * I64_size(void);
Bool I64_lt(I64 * a, I64 * b);
Bool I64_gt(I64 * a, I64 * b);
Bool I64_neq(I64 * a, I64 * b);
Bool I64_lte(I64 * a, I64 * b);
Bool I64_gte(I64 * a, I64 * b);
Str * Bool_to_str(Bool * b);
I64 * Bool_cmp(Bool * a, Bool * b);
void Bool_delete(Bool * self, Bool * call_free);
U32 * Bool_size(void);
Bool Bool_lt(Bool * a, Bool * b);
Bool Bool_gt(Bool * a, Bool * b);
Bool Bool_neq(Bool * a, Bool * b);
Bool Bool_lte(Bool * a, Bool * b);
Bool Bool_gte(Bool * a, Bool * b);
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
void println(Array * parts);
void panic(Str * loc_str, Array * parts);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
Str * poem(I64 * depth, Str * current, Str * s1, Str * s2);
Str * make_poem(Str * s1, Str * s2);
void test_lolalalo(void);
#include "ext.h"


Str *Str_lit(const char *s, unsigned long long len);
void print_single(Str *s);
void print_flush();

Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap);
U32 * Array_len(Array * self);
void * Array_get(Array * self, U32 * i);
void Array_set(Array * self, U32 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
Vec * Vec_new(Str * elem_type, U32 * elem_size);
U32 Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void Vec_append(Vec * self, Vec * other);
void Vec_move_from(Vec * self, Vec * other);
void * Vec_get(Vec * self, U32 * i);
void * Vec_pop(Vec * self);
Vec * Vec_take_prefix(Vec * self, U32 * n);
void Vec_set(Vec * self, U32 * i, void * val);
void Vec_push_take(Vec * self, Vec * src, U32 i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U32 Vec_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
U8 * Str_get(Str * self, U32 * i);
U8 * Str_byte_at(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_with_capacity(U32 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_to_str(Str * val);
Str * Str_substr(Str * s, U32 * start, U32 * n);
Bool Str_contains(Str * a, Str * b);
Bool Str_starts_with(Str * a, Str * b);
Bool Str_ends_with(Str * a, Str * b);
Bool Str_is_empty(Str * self);
I64 Str_find(Str * self, Str * needle);
I64 Str_rfind(Str * self, Str * needle);
Str * Str_replace(Str * self, Str * from, Str * to);
Str * Str_get_char(Str * self, U32 * i);
Str * Str_strip_prefix(Str * self, Str * prefix);
Str * Str_strip_suffix(Str * self, Str * suffix);
Str * Str_from_byte(U8 * byte);
I64 Str_to_i64(Str * self);
U8 Str_to_u8(Str * self);
I32 Str_to_i32(Str * self);
F32 Str_to_f32(Str * self);
Vec * Str_split(Str * self, Str * delim);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
Bool Str_lt(Str * a, Str * b);
Bool Str_gt(Str * a, Str * b);
Bool Str_neq(Str * a, Str * b);
Bool Str_lte(Str * a, Str * b);
Bool Str_gte(Str * a, Str * b);
Str * U8_to_str(U8 * val);
void U8_inc(U8 * self);
void U8_dec(U8 * self);
U8 * U8_unity(U8 * _self);
U64 U8_distance(void * a, void * b);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Bool U8_lt(U8 * a, U8 * b);
Bool U8_gt(U8 * a, U8 * b);
Bool U8_neq(U8 * a, U8 * b);
Bool U8_lte(U8 * a, U8 * b);
Bool U8_gte(U8 * a, U8 * b);
Str * I16_to_str(I16 * val);
void I16_inc(I16 * self);
void I16_dec(I16 * self);
I16 * I16_unity(I16 * _self);
I16 * I16_neg(I16 * a);
I16 * I16_abs(I16 * a);
U64 I16_distance(void * a, void * b);
void I16_delete(I16 * self, Bool * call_free);
U32 * I16_size(void);
Bool I16_lt(I16 * a, I16 * b);
Bool I16_gt(I16 * a, I16 * b);
Bool I16_neq(I16 * a, I16 * b);
Bool I16_lte(I16 * a, I16 * b);
Bool I16_gte(I16 * a, I16 * b);
Str * I32_to_str(I32 * val);
void I32_inc(I32 * self);
void I32_dec(I32 * self);
I32 * I32_unity(I32 * _self);
I32 * I32_neg(I32 * a);
I32 * I32_abs(I32 * a);
U64 I32_distance(void * a, void * b);
void I32_delete(I32 * self, Bool * call_free);
U32 * I32_size(void);
Bool I32_lt(I32 * a, I32 * b);
Bool I32_gt(I32 * a, I32 * b);
Bool I32_neq(I32 * a, I32 * b);
Bool I32_lte(I32 * a, I32 * b);
Bool I32_gte(I32 * a, I32 * b);
F32 * F32_from_i64(I64 * val);
void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
Bool F32_lt(F32 * a, F32 * b);
Bool F32_gt(F32 * a, F32 * b);
Bool F32_neq(F32 * a, F32 * b);
Bool F32_lte(F32 * a, F32 * b);
Bool F32_gte(F32 * a, F32 * b);
Str * U32_to_str(U32 * val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
U32 * U32_unity(U32 * _self);
U64 U32_distance(void * a, void * b);
void U32_delete(U32 * self, Bool * call_free);
U32 * U32_size(void);
Bool U32_lt(U32 * a, U32 * b);
Bool U32_gt(U32 * a, U32 * b);
Bool U32_neq(U32 * a, U32 * b);
Bool U32_lte(U32 * a, U32 * b);
Bool U32_gte(U32 * a, U32 * b);
Str * U64_to_str(U64 val);
U64 * U64_from_i64(I64 * val);
void U64_inc(U64 * self);
void U64_dec(U64 * self);
U64 * U64_unity(U64 * _self);
U64 U64_distance(void * a, void * b);
void U64_delete(U64 * self, Bool * call_free);
U32 * U64_size(void);
Bool U64_lt(U64 * a, U64 * b);
Bool U64_gt(U64 * a, U64 * b);
Bool U64_neq(U64 * a, U64 * b);
Bool U64_lte(U64 * a, U64 * b);
Bool U64_gte(U64 * a, U64 * b);
Str * I64_to_str(I64 * val);
U32 I64_to_usize(I64 val);
void I64_inc(I64 * self);
void I64_dec(I64 * self);
I64 * I64_unity(I64 * _self);
I64 * I64_neg(I64 * a);
I64 * I64_abs(I64 * a);
U64 I64_distance(void * a, void * b);
void I64_delete(I64 * self, Bool * call_free);
U32 * I64_size(void);
Bool I64_lt(I64 * a, I64 * b);
Bool I64_gt(I64 * a, I64 * b);
Bool I64_neq(I64 * a, I64 * b);
Bool I64_lte(I64 * a, I64 * b);
Bool I64_gte(I64 * a, I64 * b);
Str * Bool_to_str(Bool * b);
I64 * Bool_cmp(Bool * a, Bool * b);
void Bool_delete(Bool * self, Bool * call_free);
U32 * Bool_size(void);
Bool Bool_lt(Bool * a, Bool * b);
Bool Bool_gt(Bool * a, Bool * b);
Bool Bool_neq(Bool * a, Bool * b);
Bool Bool_lte(Bool * a, Bool * b);
Bool Bool_gte(Bool * a, Bool * b);
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
void println(Array * parts);
void panic(Str * loc_str, Array * parts);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
Str * poem(I64 * depth, Str * current, Str * s1, Str * s2);
Str * make_poem(Str * s1, Str * s2);
void test_lolalalo(void);

void *dyn_fn(Str *type_name, Str *method);

#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
#define TIL_CAP_LIT ((USize)-1)
Str *Str_lit(const char *s, unsigned long long len) {
    (void)len;
    Str *r = malloc(sizeof(Str));
    r->c_str = (U8 *)s;
    r->count = (USize)strlen(s);
    r->cap = TIL_CAP_LIT;
    return r;
}
void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
void print_flush() {
    putchar('\n');
}

U32 CAP_LIT;
U32 CAP_VIEW;
Str __til_docs_blob__;
Str __til_kinds_blob__;

Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    Bool _t_Bool_6 = Str_is_empty(elem_type);
    (void)_t_Bool_6;
    if (_t_Bool_6) {
        Str *_t_Str_0 = Str_lit("Str", 3ULL);
        (void)_t_Str_0;
        U32 _t_U32_1 = 16;
        (void)_t_U32_1;
        U32 _t_U32_2 = 1;
        (void)_t_U32_2;
        Array *_va_Array_0 = Array_new(_t_Str_0, &_t_U32_1, &_t_U32_2);
        (void)_va_Array_0;
        Str_delete(_t_Str_0, &(Bool){1});
        ;
        ;
        U32 _t_U32_3 = 0;
        (void)_t_U32_3;
        Str *_t_Str_4 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_4;
        Array_set(_va_Array_0, &_t_U32_3, _t_Str_4);
        ;
        Str *_t_Str_5 = Str_lit("./src/core/array.til:16:41", 26ULL);
        (void)_t_Str_5;
        panic(_t_Str_5, _va_Array_0);
        Str_delete(_t_Str_5, &(Bool){1});
    }
    ;
    void * _t_v_7 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t_v_7;
    void * _t_v_8 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_8;
    void * _t_v_9 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_9;
    Array *_t_Array_10 = malloc(sizeof(Array));
    _t_Array_10->data = _t_v_7;
    _t_Array_10->cap = DEREF(cap);
    _t_Array_10->elem_size = DEREF(elem_size);
    { Str *_ca = Str_clone(elem_type); _t_Array_10->elem_type = *_ca; free(_ca); }
    _t_Array_10->elem_clone = _t_v_8;
    _t_Array_10->elem_delete = _t_v_9;
    (void)_t_Array_10;
    return _t_Array_10;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_25 = U32_gte(i, &self->cap);
    (void)_t_Bool_25;
    if (_t_Bool_25) {
        Str *_t_Str_11 = Str_lit("Str", 3ULL);
        (void)_t_Str_11;
        U32 _t_U32_12 = 16;
        (void)_t_U32_12;
        U32 _t_U32_13 = 5;
        (void)_t_U32_13;
        Array *_va_Array_1 = Array_new(_t_Str_11, &_t_U32_12, &_t_U32_13);
        (void)_va_Array_1;
        Str_delete(_t_Str_11, &(Bool){1});
        ;
        ;
        U32 _t_U32_14 = 0;
        (void)_t_U32_14;
        Str *_t_Str_15 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_15;
        Array_set(_va_Array_1, &_t_U32_14, _t_Str_15);
        ;
        U32 _t_U32_16 = 1;
        (void)_t_U32_16;
        Str *_t_Str_17 = U32_to_str(i);
        (void)_t_Str_17;
        Array_set(_va_Array_1, &_t_U32_16, _t_Str_17);
        ;
        U32 _t_U32_18 = 2;
        (void)_t_U32_18;
        Str *_t_Str_19 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_19;
        Array_set(_va_Array_1, &_t_U32_18, _t_Str_19);
        ;
        U32 _t_U32_20 = 3;
        (void)_t_U32_20;
        Str *_t_Str_21 = U32_to_str(&self->cap);
        (void)_t_Str_21;
        Array_set(_va_Array_1, &_t_U32_20, _t_Str_21);
        ;
        U32 _t_U32_22 = 4;
        (void)_t_U32_22;
        Str *_t_Str_23 = Str_lit(")", 1ULL);
        (void)_t_Str_23;
        Array_set(_va_Array_1, &_t_U32_22, _t_Str_23);
        ;
        Str *_t_Str_24 = Str_lit("./src/core/array.til:27:19", 26ULL);
        (void)_t_Str_24;
        panic(_t_Str_24, _va_Array_1);
        Str_delete(_t_Str_24, &(Bool){1});
    }
    ;
    U32 _t_U64_26 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_26;
    void *_t_v_27 = ptr_add(self->data, _t_U64_26);
    (void)_t_v_27;
    ;
    return _t_v_27;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_42 = U32_gte(i, &self->cap);
    (void)_t_Bool_42;
    if (_t_Bool_42) {
        Str *_t_Str_28 = Str_lit("Str", 3ULL);
        (void)_t_Str_28;
        U32 _t_U32_29 = 16;
        (void)_t_U32_29;
        U32 _t_U32_30 = 5;
        (void)_t_U32_30;
        Array *_va_Array_2 = Array_new(_t_Str_28, &_t_U32_29, &_t_U32_30);
        (void)_va_Array_2;
        Str_delete(_t_Str_28, &(Bool){1});
        ;
        ;
        U32 _t_U32_31 = 0;
        (void)_t_U32_31;
        Str *_t_Str_32 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_32;
        Array_set(_va_Array_2, &_t_U32_31, _t_Str_32);
        ;
        U32 _t_U32_33 = 1;
        (void)_t_U32_33;
        Str *_t_Str_34 = U32_to_str(i);
        (void)_t_Str_34;
        Array_set(_va_Array_2, &_t_U32_33, _t_Str_34);
        ;
        U32 _t_U32_35 = 2;
        (void)_t_U32_35;
        Str *_t_Str_36 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_36;
        Array_set(_va_Array_2, &_t_U32_35, _t_Str_36);
        ;
        U32 _t_U32_37 = 3;
        (void)_t_U32_37;
        Str *_t_Str_38 = U32_to_str(&self->cap);
        (void)_t_Str_38;
        Array_set(_va_Array_2, &_t_U32_37, _t_Str_38);
        ;
        U32 _t_U32_39 = 4;
        (void)_t_U32_39;
        Str *_t_Str_40 = Str_lit(")", 1ULL);
        (void)_t_Str_40;
        Array_set(_va_Array_2, &_t_U32_39, _t_Str_40);
        ;
        Str *_t_Str_41 = Str_lit("./src/core/array.til:35:19", 26ULL);
        (void)_t_Str_41;
        panic(_t_Str_41, _va_Array_2);
        Str_delete(_t_Str_41, &(Bool){1});
    }
    ;
    U32 _t_U64_43 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_43;
    void *_t_v_44 = ptr_add(self->data, _t_U64_43);
    (void)_t_v_44;
    Bool _t_Bool_45 = 0;
    (void)_t_Bool_45;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_44, &_t_Bool_45);
    ;
    ;
    U32 _t_U64_46 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_46;
    void *_t_v_47 = ptr_add(self->data, _t_U64_46);
    (void)_t_v_47;
    memcpy(_t_v_47, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_48 = self->cap;
        (void)_re_U32_48;
        U32 _rc_U32_48 = 0;
        (void)_rc_U32_48;
        Bool _t_Bool_57 = U32_lte(&_rc_U32_48, &_re_U32_48);
        (void)_t_Bool_57;
        if (_t_Bool_57) {
            while (1) {
                Bool _wcond_Bool_49 = U32_lt(&_rc_U32_48, &_re_U32_48);
                (void)_wcond_Bool_49;
                if (_wcond_Bool_49) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_48);
                (void)i;
                U32_inc(&_rc_U32_48);
                U32 _t_U64_50 = U32_mul(i, self->elem_size);
                (void)_t_U64_50;
                ;
                void *_t_v_51 = ptr_add(self->data, _t_U64_50);
                (void)_t_v_51;
                Bool _t_Bool_52 = 0;
                (void)_t_Bool_52;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_51, &_t_Bool_52);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_53 = U32_gt(&_rc_U32_48, &_re_U32_48);
                (void)_wcond_Bool_53;
                if (_wcond_Bool_53) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_48);
                (void)i;
                U32_dec(&_rc_U32_48);
                U32 _t_U64_54 = U32_mul(i, self->elem_size);
                (void)_t_U64_54;
                ;
                void *_t_v_55 = ptr_add(self->data, _t_U64_54);
                (void)_t_v_55;
                Bool _t_Bool_56 = 0;
                (void)_t_Bool_56;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_55, &_t_Bool_56);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_58 = 0;
    (void)_t_Bool_58;
    Str_delete(&self->elem_type, &_t_Bool_58);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_71 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_71;
    void * new_data = malloc(_t_U64_71);
    (void)new_data;
    ;
    {
        U32 _re_U32_59 = self->cap;
        (void)_re_U32_59;
        U32 _rc_U32_59 = 0;
        (void)_rc_U32_59;
        Bool _t_Bool_70 = U32_lte(&_rc_U32_59, &_re_U32_59);
        (void)_t_Bool_70;
        if (_t_Bool_70) {
            while (1) {
                Bool _wcond_Bool_60 = U32_lt(&_rc_U32_59, &_re_U32_59);
                (void)_wcond_Bool_60;
                if (_wcond_Bool_60) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_59);
                (void)i;
                U32_inc(&_rc_U32_59);
                U32 _t_U64_61 = U32_mul(i, self->elem_size);
                (void)_t_U64_61;
                void *_t_v_62 = ptr_add(self->data, _t_U64_61);
                (void)_t_v_62;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_62);
                (void)cloned;
                ;
                U32 _t_U64_63 = U32_mul(i, self->elem_size);
                (void)_t_U64_63;
                ;
                void *_t_v_64 = ptr_add(new_data, _t_U64_63);
                (void)_t_v_64;
                memcpy(_t_v_64, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_65 = U32_gt(&_rc_U32_59, &_re_U32_59);
                (void)_wcond_Bool_65;
                if (_wcond_Bool_65) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_59);
                (void)i;
                U32_dec(&_rc_U32_59);
                U32 _t_U64_66 = U32_mul(i, self->elem_size);
                (void)_t_U64_66;
                void *_t_v_67 = ptr_add(self->data, _t_U64_66);
                (void)_t_v_67;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_67);
                (void)cloned;
                ;
                U32 _t_U64_68 = U32_mul(i, self->elem_size);
                (void)_t_U64_68;
                ;
                void *_t_v_69 = ptr_add(new_data, _t_U64_68);
                (void)_t_v_69;
                memcpy(_t_v_69, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_72 = malloc(sizeof(Array));
    _t_Array_72->data = new_data;
    _t_Array_72->cap = self->cap;
    _t_Array_72->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_72->elem_type = *_ca; free(_ca); }
    _t_Array_72->elem_clone = (void *)self->elem_clone;
    _t_Array_72->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_72;
    return _t_Array_72;
}

U32 Array_size(void) {
    I64 _t_I64_73 = 48;
    (void)_t_I64_73;
    return _t_I64_73;
}

Vec * Vec_new(Str * elem_type, U32 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t_Bool_84 = Str_is_empty(elem_type);
    (void)_t_Bool_84;
    if (_t_Bool_84) {
        Str *_t_Str_74 = Str_lit("Str", 3ULL);
        (void)_t_Str_74;
        U32 _t_U32_75 = 16;
        (void)_t_U32_75;
        U32 _t_U32_76 = 1;
        (void)_t_U32_76;
        Array *_va_Array_3 = Array_new(_t_Str_74, &_t_U32_75, &_t_U32_76);
        (void)_va_Array_3;
        Str_delete(_t_Str_74, &(Bool){1});
        ;
        ;
        U32 _t_U32_77 = 0;
        (void)_t_U32_77;
        Str *_t_Str_78 = Str_lit("Vec.new: elem_type required", 27ULL);
        (void)_t_Str_78;
        Array_set(_va_Array_3, &_t_U32_77, _t_Str_78);
        ;
        Str *_t_Str_79 = Str_lit("./src/core/vec.til:18:19", 24ULL);
        (void)_t_Str_79;
        panic(_t_Str_79, _va_Array_3);
        Str_delete(_t_Str_79, &(Bool){1});
    }
    ;
    Str *_t_Str_85 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_85;
    Bool _t_Bool_86 = Str_eq(elem_type, _t_Str_85);
    (void)_t_Bool_86;
    Str_delete(_t_Str_85, &(Bool){1});
    if (_t_Bool_86) {
        void * _t_v_80 = malloc(DEREF(elem_size));
        (void)_t_v_80;
        U32 _t_U32_81 = 0;
        (void)_t_U32_81;
        I64 _t_I64_82 = 1;
        (void)_t_I64_82;
        Vec *_t_Vec_83 = malloc(sizeof(Vec));
        _t_Vec_83->data = _t_v_80;
        _t_Vec_83->count = _t_U32_81;
        _t_Vec_83->cap = _t_I64_82;
        _t_Vec_83->elem_size = DEREF(elem_size);
        { Str *_ca = Str_clone(elem_type); _t_Vec_83->elem_type = *_ca; free(_ca); }
        _t_Vec_83->elem_clone = (void *)(void *)default_clone;
        _t_Vec_83->elem_delete = (void *)(void *)default_delete;
        (void)_t_Vec_83;
        ;
        ;
        ;
        return _t_Vec_83;
    }
    ;
    void * _t_v_87 = malloc(DEREF(elem_size));
    (void)_t_v_87;
    U32 _t_U32_88 = 0;
    (void)_t_U32_88;
    I64 _t_I64_89 = 1;
    (void)_t_I64_89;
    void * _t_v_90 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_90;
    void * _t_v_91 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_91;
    Vec *_t_Vec_92 = malloc(sizeof(Vec));
    _t_Vec_92->data = _t_v_87;
    _t_Vec_92->count = _t_U32_88;
    _t_Vec_92->cap = _t_I64_89;
    _t_Vec_92->elem_size = DEREF(elem_size);
    { Str *_ca = Str_clone(elem_type); _t_Vec_92->elem_type = *_ca; free(_ca); }
    _t_Vec_92->elem_clone = _t_v_90;
    _t_Vec_92->elem_delete = _t_v_91;
    (void)_t_Vec_92;
    ;
    ;
    return _t_Vec_92;
}

U32 Vec_len(Vec * self) {
    (void)self;
    return self->count;
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t_Bool_97 = U32_eq(self->count, self->cap);
    (void)_t_Bool_97;
    if (_t_Bool_97) {
        U32 _t_U32_93 = 2;
        (void)_t_U32_93;
        U32 new_cap = U32_mul(self->cap, _t_U32_93);
        (void)new_cap;
        ;
        U32 _t_U64_94 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_94;
        void * _t_v_95 = realloc(self->data, _t_U64_94);
        (void)_t_v_95;
        ;
        self->data = _t_v_95;
        U32 _t_U32_96 = U32_clone(&new_cap);
        (void)_t_U32_96;
        ;
        self->cap = _t_U32_96;
        ;
    }
    ;
    U32 _t_U64_98 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_98;
    void *_t_v_99 = ptr_add(self->data, _t_U64_98);
    (void)_t_v_99;
    memcpy(_t_v_99, val, self->elem_size);
    ;
    free(val);
    U32 _t_U32_100 = 1;
    (void)_t_U32_100;
    U32 _t_U32_101 = U32_add(self->count, _t_U32_100);
    (void)_t_U32_101;
    ;
    self->count = _t_U32_101;
    ;
}

void Vec_append(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_114 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_114;
    Bool _t_Bool_115 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_115;
    Bool _t_Bool_116 = not(_t_Bool_114);
    (void)_t_Bool_116;
    ;
    Bool _t_Bool_117 = not(_t_Bool_115);
    (void)_t_Bool_117;
    ;
    Bool _t_Bool_118 = or(_t_Bool_116, _t_Bool_117);
    (void)_t_Bool_118;
    ;
    ;
    if (_t_Bool_118) {
        Str *_t_Str_102 = Str_lit("Str", 3ULL);
        (void)_t_Str_102;
        U32 _t_U32_103 = 16;
        (void)_t_U32_103;
        U32 _t_U32_104 = 1;
        (void)_t_U32_104;
        Array *_va_Array_4 = Array_new(_t_Str_102, &_t_U32_103, &_t_U32_104);
        (void)_va_Array_4;
        Str_delete(_t_Str_102, &(Bool){1});
        ;
        ;
        U32 _t_U32_105 = 0;
        (void)_t_U32_105;
        Str *_t_Str_106 = Str_lit("Vec.append: incompatible vecs", 29ULL);
        (void)_t_Str_106;
        Array_set(_va_Array_4, &_t_U32_105, _t_Str_106);
        ;
        Str *_t_Str_107 = Str_lit("./src/core/vec.til:45:19", 24ULL);
        (void)_t_Str_107;
        panic(_t_Str_107, _va_Array_4);
        Str_delete(_t_Str_107, &(Bool){1});
    }
    ;
    U32 _t_U32_119 = 0;
    (void)_t_U32_119;
    Bool _t_Bool_120 = U32_eq(other->count, _t_U32_119);
    (void)_t_Bool_120;
    ;
    if (_t_Bool_120) {
        ;
        Vec_delete(other, &(Bool){0});
        return;
    }
    ;
    U32 needed = U32_add(self->count, other->count);
    (void)needed;
    Bool _t_Bool_121 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_121;
    if (_t_Bool_121) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_108 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_108;
            if (_wcond_Bool_108) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_109 = 2;
            (void)_t_U32_109;
            U32 _t_U32_110 = U32_mul(new_cap, _t_U32_109);
            (void)_t_U32_110;
            ;
            new_cap = _t_U32_110;
            ;
        }
        U32 _t_U64_111 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_111;
        void * _t_v_112 = realloc(self->data, _t_U64_111);
        (void)_t_v_112;
        ;
        self->data = _t_v_112;
        U32 _t_U32_113 = U32_clone(&new_cap);
        (void)_t_U32_113;
        ;
        self->cap = _t_U32_113;
        ;
    }
    ;
    U32 _t_U64_122 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_122;
    void *_t_v_123 = ptr_add(self->data, _t_U64_122);
    (void)_t_v_123;
    U32 _t_U64_124 = U32_mul(other->count, self->elem_size);
    (void)_t_U64_124;
    memcpy(_t_v_123, other->data, _t_U64_124);
    ;
    ;
    U32 _t_U32_125 = U32_clone(&needed);
    (void)_t_U32_125;
    ;
    self->count = _t_U32_125;
    ;
    U32 _t_U32_126 = 0;
    (void)_t_U32_126;
    other->count = _t_U32_126;
    ;
    Vec_delete(other, &(Bool){0});
}

void Vec_move_from(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_150 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_150;
    Bool _t_Bool_151 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_151;
    Bool _t_Bool_152 = not(_t_Bool_150);
    (void)_t_Bool_152;
    ;
    Bool _t_Bool_153 = not(_t_Bool_151);
    (void)_t_Bool_153;
    ;
    Bool _t_Bool_154 = or(_t_Bool_152, _t_Bool_153);
    (void)_t_Bool_154;
    ;
    ;
    if (_t_Bool_154) {
        Str *_t_Str_127 = Str_lit("Str", 3ULL);
        (void)_t_Str_127;
        U32 _t_U32_128 = 16;
        (void)_t_U32_128;
        U32 _t_U32_129 = 1;
        (void)_t_U32_129;
        Array *_va_Array_5 = Array_new(_t_Str_127, &_t_U32_128, &_t_U32_129);
        (void)_va_Array_5;
        Str_delete(_t_Str_127, &(Bool){1});
        ;
        ;
        U32 _t_U32_130 = 0;
        (void)_t_U32_130;
        Str *_t_Str_131 = Str_lit("Vec.move_from: incompatible vecs", 32ULL);
        (void)_t_Str_131;
        Array_set(_va_Array_5, &_t_U32_130, _t_Str_131);
        ;
        Str *_t_Str_132 = Str_lit("./src/core/vec.til:72:19", 24ULL);
        (void)_t_Str_132;
        panic(_t_Str_132, _va_Array_5);
        Str_delete(_t_Str_132, &(Bool){1});
    }
    ;
    Bool _t_Bool_155 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_155;
    Str *_t_Str_156 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_156;
    Bool _t_Bool_157 = Str_eq(&self->elem_type, _t_Str_156);
    (void)_t_Bool_157;
    Str_delete(_t_Str_156, &(Bool){1});
    Bool _t_Bool_158 = not(_t_Bool_155);
    (void)_t_Bool_158;
    ;
    Bool _t_Bool_159 = not(_t_Bool_157);
    (void)_t_Bool_159;
    ;
    Bool _t_Bool_160 = and(_t_Bool_158, _t_Bool_159);
    (void)_t_Bool_160;
    ;
    ;
    if (_t_Bool_160) {
        {
            U32 _re_U32_133 = self->count;
            (void)_re_U32_133;
            U32 _rc_U32_133 = 0;
            (void)_rc_U32_133;
            Bool _t_Bool_142 = U32_lte(&_rc_U32_133, &_re_U32_133);
            (void)_t_Bool_142;
            if (_t_Bool_142) {
                while (1) {
                    Bool _wcond_Bool_134 = U32_lt(&_rc_U32_133, &_re_U32_133);
                    (void)_wcond_Bool_134;
                    if (_wcond_Bool_134) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_133);
                    (void)i;
                    U32_inc(&_rc_U32_133);
                    U32 _t_U64_135 = U32_mul(i, self->elem_size);
                    (void)_t_U64_135;
                    ;
                    void *_t_v_136 = ptr_add(self->data, _t_U64_135);
                    (void)_t_v_136;
                    Bool _t_Bool_137 = 0;
                    (void)_t_Bool_137;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_136, &_t_Bool_137);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_138 = U32_gt(&_rc_U32_133, &_re_U32_133);
                    (void)_wcond_Bool_138;
                    if (_wcond_Bool_138) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_133);
                    (void)i;
                    U32_dec(&_rc_U32_133);
                    U32 _t_U64_139 = U32_mul(i, self->elem_size);
                    (void)_t_U64_139;
                    ;
                    void *_t_v_140 = ptr_add(self->data, _t_U64_139);
                    (void)_t_v_140;
                    Bool _t_Bool_141 = 0;
                    (void)_t_Bool_141;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_140, &_t_Bool_141);
                    ;
                    ;
                }
            }
            ;
            ;
            ;
        }
    }
    ;
    U32 needed = other->count;
    (void)needed;
    Bool _t_Bool_161 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_161;
    if (_t_Bool_161) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_143 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_143;
            if (_wcond_Bool_143) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_144 = 2;
            (void)_t_U32_144;
            U32 _t_U32_145 = U32_mul(new_cap, _t_U32_144);
            (void)_t_U32_145;
            ;
            new_cap = _t_U32_145;
            ;
        }
        U32 _t_U64_146 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_146;
        void * _t_v_147 = realloc(self->data, _t_U64_146);
        (void)_t_v_147;
        ;
        self->data = _t_v_147;
        U32 _t_U32_148 = U32_clone(&new_cap);
        (void)_t_U32_148;
        ;
        self->cap = _t_U32_148;
        ;
    }
    ;
    U32 _t_U32_162 = 0;
    (void)_t_U32_162;
    Bool _t_Bool_163 = U32_gt(&needed, &_t_U32_162);
    (void)_t_Bool_163;
    ;
    if (_t_Bool_163) {
        U32 _t_U64_149 = U32_mul(needed, self->elem_size);
        (void)_t_U64_149;
        memcpy(self->data, other->data, _t_U64_149);
        ;
    }
    ;
    U32 _t_U32_164 = U32_clone(&needed);
    (void)_t_U32_164;
    ;
    self->count = _t_U32_164;
    ;
    U32 _t_U32_165 = 0;
    (void)_t_U32_165;
    other->count = _t_U32_165;
    ;
}

void * Vec_get(Vec * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_180 = U32_gte(i, &self->count);
    (void)_t_Bool_180;
    if (_t_Bool_180) {
        Str *_t_Str_166 = Str_lit("Str", 3ULL);
        (void)_t_Str_166;
        U32 _t_U32_167 = 16;
        (void)_t_U32_167;
        U32 _t_U32_168 = 5;
        (void)_t_U32_168;
        Array *_va_Array_6 = Array_new(_t_Str_166, &_t_U32_167, &_t_U32_168);
        (void)_va_Array_6;
        Str_delete(_t_Str_166, &(Bool){1});
        ;
        ;
        U32 _t_U32_169 = 0;
        (void)_t_U32_169;
        Str *_t_Str_170 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t_Str_170;
        Array_set(_va_Array_6, &_t_U32_169, _t_Str_170);
        ;
        U32 _t_U32_171 = 1;
        (void)_t_U32_171;
        Str *_t_Str_172 = U32_to_str(i);
        (void)_t_Str_172;
        Array_set(_va_Array_6, &_t_U32_171, _t_Str_172);
        ;
        U32 _t_U32_173 = 2;
        (void)_t_U32_173;
        Str *_t_Str_174 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_174;
        Array_set(_va_Array_6, &_t_U32_173, _t_Str_174);
        ;
        U32 _t_U32_175 = 3;
        (void)_t_U32_175;
        Str *_t_Str_176 = U32_to_str(&self->count);
        (void)_t_Str_176;
        Array_set(_va_Array_6, &_t_U32_175, _t_Str_176);
        ;
        U32 _t_U32_177 = 4;
        (void)_t_U32_177;
        Str *_t_Str_178 = Str_lit(")", 1ULL);
        (void)_t_Str_178;
        Array_set(_va_Array_6, &_t_U32_177, _t_Str_178);
        ;
        Str *_t_Str_179 = Str_lit("./src/core/vec.til:97:19", 24ULL);
        (void)_t_Str_179;
        panic(_t_Str_179, _va_Array_6);
        Str_delete(_t_Str_179, &(Bool){1});
    }
    ;
    U32 _t_U64_181 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_181;
    void *_t_v_182 = ptr_add(self->data, _t_U64_181);
    (void)_t_v_182;
    ;
    return _t_v_182;
}

void * Vec_pop(Vec * self) {
    (void)self;
    U32 _t_U32_189 = 0;
    (void)_t_U32_189;
    Bool _t_Bool_190 = U32_eq(self->count, _t_U32_189);
    (void)_t_Bool_190;
    ;
    if (_t_Bool_190) {
        Str *_t_Str_183 = Str_lit("Str", 3ULL);
        (void)_t_Str_183;
        U32 _t_U32_184 = 16;
        (void)_t_U32_184;
        U32 _t_U32_185 = 1;
        (void)_t_U32_185;
        Array *_va_Array_7 = Array_new(_t_Str_183, &_t_U32_184, &_t_U32_185);
        (void)_va_Array_7;
        Str_delete(_t_Str_183, &(Bool){1});
        ;
        ;
        U32 _t_U32_186 = 0;
        (void)_t_U32_186;
        Str *_t_Str_187 = Str_lit("Vec.pop: empty vec", 18ULL);
        (void)_t_Str_187;
        Array_set(_va_Array_7, &_t_U32_186, _t_Str_187);
        ;
        Str *_t_Str_188 = Str_lit("./src/core/vec.til:104:19", 25ULL);
        (void)_t_Str_188;
        panic(_t_Str_188, _va_Array_7);
        Str_delete(_t_Str_188, &(Bool){1});
    }
    ;
    U32 _t_U32_191 = 1;
    (void)_t_U32_191;
    U32 last = U32_sub(self->count, _t_U32_191);
    (void)last;
    ;
    void * out = malloc(self->elem_size);
    (void)out;
    U32 _t_U64_192 = U32_mul(last, self->elem_size);
    (void)_t_U64_192;
    void *_t_v_193 = ptr_add(self->data, _t_U64_192);
    (void)_t_v_193;
    memcpy(out, _t_v_193, self->elem_size);
    ;
    U32 _t_U32_194 = U32_clone(&last);
    (void)_t_U32_194;
    ;
    self->count = _t_U32_194;
    ;
    return out;
}

Vec * Vec_take_prefix(Vec * self, U32 * n) {
    (void)self;
    (void)n;
    Bool _t_Bool_214 = U32_gt(n, &self->count);
    (void)_t_Bool_214;
    if (_t_Bool_214) {
        Str *_t_Str_195 = Str_lit("Str", 3ULL);
        (void)_t_Str_195;
        U32 _t_U32_196 = 16;
        (void)_t_U32_196;
        U32 _t_U32_197 = 5;
        (void)_t_U32_197;
        Array *_va_Array_8 = Array_new(_t_Str_195, &_t_U32_196, &_t_U32_197);
        (void)_va_Array_8;
        Str_delete(_t_Str_195, &(Bool){1});
        ;
        ;
        U32 _t_U32_198 = 0;
        (void)_t_U32_198;
        Str *_t_Str_199 = Str_lit("Vec.take_prefix: count ", 23ULL);
        (void)_t_Str_199;
        Array_set(_va_Array_8, &_t_U32_198, _t_Str_199);
        ;
        U32 _t_U32_200 = 1;
        (void)_t_U32_200;
        Str *_t_Str_201 = U32_to_str(n);
        (void)_t_Str_201;
        Array_set(_va_Array_8, &_t_U32_200, _t_Str_201);
        ;
        U32 _t_U32_202 = 2;
        (void)_t_U32_202;
        Str *_t_Str_203 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_203;
        Array_set(_va_Array_8, &_t_U32_202, _t_Str_203);
        ;
        U32 _t_U32_204 = 3;
        (void)_t_U32_204;
        Str *_t_Str_205 = U32_to_str(&self->count);
        (void)_t_Str_205;
        Array_set(_va_Array_8, &_t_U32_204, _t_Str_205);
        ;
        U32 _t_U32_206 = 4;
        (void)_t_U32_206;
        Str *_t_Str_207 = Str_lit(")", 1ULL);
        (void)_t_Str_207;
        Array_set(_va_Array_8, &_t_U32_206, _t_Str_207);
        ;
        Str *_t_Str_208 = Str_lit("./src/core/vec.til:115:19", 25ULL);
        (void)_t_Str_208;
        panic(_t_Str_208, _va_Array_8);
        Str_delete(_t_Str_208, &(Bool){1});
    }
    ;
    U32 prefix_cap = 1;
    (void)prefix_cap;
    U32 _t_U32_215 = 0;
    (void)_t_U32_215;
    Bool _t_Bool_216 = U32_gt(n, &_t_U32_215);
    (void)_t_Bool_216;
    ;
    if (_t_Bool_216) {
        U32 _t_U32_209 = U32_clone(n);
        (void)_t_U32_209;
        prefix_cap = _t_U32_209;
        ;
    }
    ;
    U32 _t_U64_217 = U32_mul(prefix_cap, self->elem_size);
    (void)_t_U64_217;
    void * prefix_data = malloc(_t_U64_217);
    (void)prefix_data;
    ;
    U32 _t_U32_218 = 0;
    (void)_t_U32_218;
    Bool _t_Bool_219 = U32_gt(n, &_t_U32_218);
    (void)_t_Bool_219;
    ;
    if (_t_Bool_219) {
        U32 _t_U64_210 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_210;
        memcpy(prefix_data, self->data, _t_U64_210);
        ;
    }
    ;
    U32 tail_count = U32_sub(self->count, DEREF(n));
    (void)tail_count;
    U32 _t_U32_220 = 0;
    (void)_t_U32_220;
    Bool _t_Bool_221 = U32_gt(&tail_count, &_t_U32_220);
    (void)_t_Bool_221;
    ;
    if (_t_Bool_221) {
        U32 _t_U64_211 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_211;
        void *_t_v_212 = ptr_add(self->data, _t_U64_211);
        (void)_t_v_212;
        U32 _t_U64_213 = U32_mul(tail_count, self->elem_size);
        (void)_t_U64_213;
        memmove(self->data, _t_v_212, _t_U64_213);
        ;
        ;
    }
    ;
    U32 _t_U32_222 = U32_clone(&tail_count);
    (void)_t_U32_222;
    ;
    self->count = _t_U32_222;
    ;
    Vec *_t_Vec_223 = malloc(sizeof(Vec));
    _t_Vec_223->data = prefix_data;
    _t_Vec_223->count = DEREF(n);
    _t_Vec_223->cap = prefix_cap;
    _t_Vec_223->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_223->elem_type = *_ca; free(_ca); }
    _t_Vec_223->elem_clone = (void *)self->elem_clone;
    _t_Vec_223->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_223;
    ;
    return _t_Vec_223;
}

void Vec_set(Vec * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_238 = U32_gte(i, &self->count);
    (void)_t_Bool_238;
    if (_t_Bool_238) {
        Str *_t_Str_224 = Str_lit("Str", 3ULL);
        (void)_t_Str_224;
        U32 _t_U32_225 = 16;
        (void)_t_U32_225;
        U32 _t_U32_226 = 5;
        (void)_t_U32_226;
        Array *_va_Array_9 = Array_new(_t_Str_224, &_t_U32_225, &_t_U32_226);
        (void)_va_Array_9;
        Str_delete(_t_Str_224, &(Bool){1});
        ;
        ;
        U32 _t_U32_227 = 0;
        (void)_t_U32_227;
        Str *_t_Str_228 = Str_lit("Vec.set: index ", 15ULL);
        (void)_t_Str_228;
        Array_set(_va_Array_9, &_t_U32_227, _t_Str_228);
        ;
        U32 _t_U32_229 = 1;
        (void)_t_U32_229;
        Str *_t_Str_230 = U32_to_str(i);
        (void)_t_Str_230;
        Array_set(_va_Array_9, &_t_U32_229, _t_Str_230);
        ;
        U32 _t_U32_231 = 2;
        (void)_t_U32_231;
        Str *_t_Str_232 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_232;
        Array_set(_va_Array_9, &_t_U32_231, _t_Str_232);
        ;
        U32 _t_U32_233 = 3;
        (void)_t_U32_233;
        Str *_t_Str_234 = U32_to_str(&self->count);
        (void)_t_Str_234;
        Array_set(_va_Array_9, &_t_U32_233, _t_Str_234);
        ;
        U32 _t_U32_235 = 4;
        (void)_t_U32_235;
        Str *_t_Str_236 = Str_lit(")", 1ULL);
        (void)_t_Str_236;
        Array_set(_va_Array_9, &_t_U32_235, _t_Str_236);
        ;
        Str *_t_Str_237 = Str_lit("./src/core/vec.til:137:19", 25ULL);
        (void)_t_Str_237;
        panic(_t_Str_237, _va_Array_9);
        Str_delete(_t_Str_237, &(Bool){1});
    }
    ;
    U32 _t_U64_239 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_239;
    void *_t_v_240 = ptr_add(self->data, _t_U64_239);
    (void)_t_v_240;
    memcpy(_t_v_240, val, self->elem_size);
    ;
    free(val);
}

void Vec_push_take(Vec * self, Vec * src, U32 i) {
    (void)self;
    (void)src;
    (void)i;
    Bool _t_Bool_265 = U32_gte(&i, &src->count);
    (void)_t_Bool_265;
    if (_t_Bool_265) {
        Str *_t_Str_241 = Str_lit("Str", 3ULL);
        (void)_t_Str_241;
        U32 _t_U32_242 = 16;
        (void)_t_U32_242;
        U32 _t_U32_243 = 5;
        (void)_t_U32_243;
        Array *_va_Array_10 = Array_new(_t_Str_241, &_t_U32_242, &_t_U32_243);
        (void)_va_Array_10;
        Str_delete(_t_Str_241, &(Bool){1});
        ;
        ;
        U32 _t_U32_244 = 0;
        (void)_t_U32_244;
        Str *_t_Str_245 = Str_lit("Vec.push_take: index ", 21ULL);
        (void)_t_Str_245;
        Array_set(_va_Array_10, &_t_U32_244, _t_Str_245);
        ;
        U32 _t_U32_246 = 1;
        (void)_t_U32_246;
        Str *_t_Str_247 = U32_to_str(&i);
        (void)_t_Str_247;
        Array_set(_va_Array_10, &_t_U32_246, _t_Str_247);
        ;
        U32 _t_U32_248 = 2;
        (void)_t_U32_248;
        Str *_t_Str_249 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_249;
        Array_set(_va_Array_10, &_t_U32_248, _t_Str_249);
        ;
        U32 _t_U32_250 = 3;
        (void)_t_U32_250;
        Str *_t_Str_251 = U32_to_str(&src->count);
        (void)_t_Str_251;
        Array_set(_va_Array_10, &_t_U32_250, _t_Str_251);
        ;
        U32 _t_U32_252 = 4;
        (void)_t_U32_252;
        Str *_t_Str_253 = Str_lit(")", 1ULL);
        (void)_t_Str_253;
        Array_set(_va_Array_10, &_t_U32_252, _t_Str_253);
        ;
        Str *_t_Str_254 = Str_lit("./src/core/vec.til:148:19", 25ULL);
        (void)_t_Str_254;
        panic(_t_Str_254, _va_Array_10);
        Str_delete(_t_Str_254, &(Bool){1});
    }
    ;
    Bool _t_Bool_266 = U32_eq(self->elem_size, src->elem_size);
    (void)_t_Bool_266;
    Bool _t_Bool_267 = Str_eq(&self->elem_type, &src->elem_type);
    (void)_t_Bool_267;
    Bool _t_Bool_268 = not(_t_Bool_266);
    (void)_t_Bool_268;
    ;
    Bool _t_Bool_269 = not(_t_Bool_267);
    (void)_t_Bool_269;
    ;
    Bool _t_Bool_270 = or(_t_Bool_268, _t_Bool_269);
    (void)_t_Bool_270;
    ;
    ;
    if (_t_Bool_270) {
        Str *_t_Str_255 = Str_lit("Str", 3ULL);
        (void)_t_Str_255;
        U32 _t_U32_256 = 16;
        (void)_t_U32_256;
        U32 _t_U32_257 = 1;
        (void)_t_U32_257;
        Array *_va_Array_11 = Array_new(_t_Str_255, &_t_U32_256, &_t_U32_257);
        (void)_va_Array_11;
        Str_delete(_t_Str_255, &(Bool){1});
        ;
        ;
        U32 _t_U32_258 = 0;
        (void)_t_U32_258;
        Str *_t_Str_259 = Str_lit("Vec.push_take: incompatible vecs", 32ULL);
        (void)_t_Str_259;
        Array_set(_va_Array_11, &_t_U32_258, _t_Str_259);
        ;
        Str *_t_Str_260 = Str_lit("./src/core/vec.til:151:19", 25ULL);
        (void)_t_Str_260;
        panic(_t_Str_260, _va_Array_11);
        Str_delete(_t_Str_260, &(Bool){1});
    }
    ;
    Bool _t_Bool_271 = U32_eq(self->count, self->cap);
    (void)_t_Bool_271;
    if (_t_Bool_271) {
        U32 _t_U32_261 = 2;
        (void)_t_U32_261;
        U32 new_cap = U32_mul(self->cap, _t_U32_261);
        (void)new_cap;
        ;
        U32 _t_U64_262 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_262;
        void * _t_v_263 = realloc(self->data, _t_U64_262);
        (void)_t_v_263;
        ;
        self->data = _t_v_263;
        U32 _t_U32_264 = U32_clone(&new_cap);
        (void)_t_U32_264;
        ;
        self->cap = _t_U32_264;
        ;
    }
    ;
    U32 _t_U64_272 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_272;
    U32 _t_U64_273 = U32_mul(i, src->elem_size);
    (void)_t_U64_273;
    void *_t_v_274 = ptr_add(self->data, _t_U64_272);
    (void)_t_v_274;
    void *_t_v_275 = ptr_add(src->data, _t_U64_273);
    (void)_t_v_275;
    memcpy(_t_v_274, _t_v_275, self->elem_size);
    ;
    ;
    U32 _t_U64_276 = U32_mul(i, src->elem_size);
    (void)_t_U64_276;
    void *_t_v_277 = ptr_add(src->data, _t_U64_276);
    (void)_t_v_277;
    I32 _t_I32_278 = 0;
    (void)_t_I32_278;
    memset(_t_v_277, _t_I32_278, src->elem_size);
    ;
    ;
    U32 _t_U32_279 = 1;
    (void)_t_U32_279;
    U32 _t_U32_280 = U32_add(self->count, _t_U32_279);
    (void)_t_U32_280;
    ;
    self->count = _t_U32_280;
    ;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_292 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_292;
    Str *_t_Str_293 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_293;
    Bool _t_Bool_294 = Str_eq(&self->elem_type, _t_Str_293);
    (void)_t_Bool_294;
    Str_delete(_t_Str_293, &(Bool){1});
    Bool _t_Bool_295 = not(_t_Bool_292);
    (void)_t_Bool_295;
    ;
    Bool _t_Bool_296 = not(_t_Bool_294);
    (void)_t_Bool_296;
    ;
    Bool _t_Bool_297 = and(_t_Bool_295, _t_Bool_296);
    (void)_t_Bool_297;
    ;
    ;
    if (_t_Bool_297) {
        {
            U32 _re_U32_281 = self->count;
            (void)_re_U32_281;
            U32 _rc_U32_281 = 0;
            (void)_rc_U32_281;
            Bool _t_Bool_290 = U32_lte(&_rc_U32_281, &_re_U32_281);
            (void)_t_Bool_290;
            if (_t_Bool_290) {
                while (1) {
                    Bool _wcond_Bool_282 = U32_lt(&_rc_U32_281, &_re_U32_281);
                    (void)_wcond_Bool_282;
                    if (_wcond_Bool_282) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_281);
                    (void)i;
                    U32_inc(&_rc_U32_281);
                    U32 _t_U64_283 = U32_mul(i, self->elem_size);
                    (void)_t_U64_283;
                    ;
                    void *_t_v_284 = ptr_add(self->data, _t_U64_283);
                    (void)_t_v_284;
                    Bool _t_Bool_285 = 0;
                    (void)_t_Bool_285;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_284, &_t_Bool_285);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_286 = U32_gt(&_rc_U32_281, &_re_U32_281);
                    (void)_wcond_Bool_286;
                    if (_wcond_Bool_286) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_281);
                    (void)i;
                    U32_dec(&_rc_U32_281);
                    U32 _t_U64_287 = U32_mul(i, self->elem_size);
                    (void)_t_U64_287;
                    ;
                    void *_t_v_288 = ptr_add(self->data, _t_U64_287);
                    (void)_t_v_288;
                    Bool _t_Bool_289 = 0;
                    (void)_t_Bool_289;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_288, &_t_Bool_289);
                    ;
                    ;
                }
            }
            ;
            ;
            ;
        }
    }
    ;
    free(self->data);
    Bool _t_Bool_298 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_298;
    Bool _t_Bool_299 = not(_t_Bool_298);
    (void)_t_Bool_299;
    ;
    if (_t_Bool_299) {
        Bool _t_Bool_291 = 0;
        (void)_t_Bool_291;
        Str_delete(&self->elem_type, &_t_Bool_291);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U32 _t_U64_313 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_313;
    void * new_data = malloc(_t_U64_313);
    (void)new_data;
    ;
    Bool _t_Bool_314 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_314;
    Str *_t_Str_315 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_315;
    Bool _t_Bool_316 = Str_eq(&self->elem_type, _t_Str_315);
    (void)_t_Bool_316;
    Str_delete(_t_Str_315, &(Bool){1});
    Bool _t_Bool_317 = not(_t_Bool_314);
    (void)_t_Bool_317;
    ;
    Bool _t_Bool_318 = not(_t_Bool_316);
    (void)_t_Bool_318;
    ;
    Bool _t_Bool_319 = and(_t_Bool_317, _t_Bool_318);
    (void)_t_Bool_319;
    ;
    ;
    if (_t_Bool_319) {
        {
            U32 _re_U32_300 = self->count;
            (void)_re_U32_300;
            U32 _rc_U32_300 = 0;
            (void)_rc_U32_300;
            Bool _t_Bool_311 = U32_lte(&_rc_U32_300, &_re_U32_300);
            (void)_t_Bool_311;
            if (_t_Bool_311) {
                while (1) {
                    Bool _wcond_Bool_301 = U32_lt(&_rc_U32_300, &_re_U32_300);
                    (void)_wcond_Bool_301;
                    if (_wcond_Bool_301) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_300);
                    (void)i;
                    U32_inc(&_rc_U32_300);
                    U32 _t_U64_302 = U32_mul(i, self->elem_size);
                    (void)_t_U64_302;
                    void *_t_v_303 = ptr_add(self->data, _t_U64_302);
                    (void)_t_v_303;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_303);
                    (void)cloned;
                    ;
                    U32 _t_U64_304 = U32_mul(i, self->elem_size);
                    (void)_t_U64_304;
                    ;
                    void *_t_v_305 = ptr_add(new_data, _t_U64_304);
                    (void)_t_v_305;
                    memcpy(_t_v_305, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_306 = U32_gt(&_rc_U32_300, &_re_U32_300);
                    (void)_wcond_Bool_306;
                    if (_wcond_Bool_306) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_300);
                    (void)i;
                    U32_dec(&_rc_U32_300);
                    U32 _t_U64_307 = U32_mul(i, self->elem_size);
                    (void)_t_U64_307;
                    void *_t_v_308 = ptr_add(self->data, _t_U64_307);
                    (void)_t_v_308;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_308);
                    (void)cloned;
                    ;
                    U32 _t_U64_309 = U32_mul(i, self->elem_size);
                    (void)_t_U64_309;
                    ;
                    void *_t_v_310 = ptr_add(new_data, _t_U64_309);
                    (void)_t_v_310;
                    memcpy(_t_v_310, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            }
            ;
            ;
            ;
        }
    } else {
        U32 _t_U64_312 = U32_mul(self->count, self->elem_size);
        (void)_t_U64_312;
        memcpy(new_data, self->data, _t_U64_312);
        ;
    }
    ;
    Vec *_t_Vec_320 = malloc(sizeof(Vec));
    _t_Vec_320->data = new_data;
    _t_Vec_320->count = self->count;
    _t_Vec_320->cap = self->cap;
    _t_Vec_320->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_320->elem_type = *_ca; free(_ca); }
    _t_Vec_320->elem_clone = (void *)self->elem_clone;
    _t_Vec_320->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_320;
    return _t_Vec_320;
}

U32 Vec_size(void) {
    I64 _t_I64_321 = 56;
    (void)_t_I64_321;
    return _t_I64_321;
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    (void)total;
    {
        Array *_fc_Array_666 = parts;
        (void)_fc_Array_666;
        U32 _fi_USize_666 = 0;
        (void)_fi_USize_666;
        while (1) {
            U32 _t_U32_668; { U32 *_hp = (U32 *)Array_len(_fc_Array_666); _t_U32_668 = *_hp; free(_hp); }
            (void)_t_U32_668;
            Bool _wcond_Bool_667 = U32_lt(&_fi_USize_666, &_t_U32_668);
            (void)_wcond_Bool_667;
            ;
            if (_wcond_Bool_667) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_666, &_fi_USize_666);
            (void)s;
            U32 _t_U32_669 = 1;
            (void)_t_U32_669;
            U32 _t_U32_670 = U32_add(_fi_USize_666, _t_U32_669);
            (void)_t_U32_670;
            ;
            _fi_USize_666 = _t_U32_670;
            ;
            U32 _t_U32_671 = Str_len(s);
            (void)_t_U32_671;
            U32 _t_U32_672 = U32_add(total, _t_U32_671);
            (void)_t_U32_672;
            ;
            total = _t_U32_672;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    (void)out;
    ;
    {
        Array *_fc_Array_673 = parts;
        (void)_fc_Array_673;
        U32 _fi_USize_673 = 0;
        (void)_fi_USize_673;
        while (1) {
            U32 _t_U32_675; { U32 *_hp = (U32 *)Array_len(_fc_Array_673); _t_U32_675 = *_hp; free(_hp); }
            (void)_t_U32_675;
            Bool _wcond_Bool_674 = U32_lt(&_fi_USize_673, &_t_U32_675);
            (void)_wcond_Bool_674;
            ;
            if (_wcond_Bool_674) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_673, &_fi_USize_673);
            (void)s;
            U32 _t_U32_676 = 1;
            (void)_t_U32_676;
            U32 _t_U32_677 = U32_add(_fi_USize_673, _t_U32_676);
            (void)_t_U32_677;
            ;
            _fi_USize_673 = _t_U32_677;
            ;
            Str_push_str(out, s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    return out;
}

U32 Str_len(Str * self) {
    (void)self;
    return self->count;
}

U8 * Str_get(Str * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_684 = U32_gte(i, &self->count);
    (void)_t_Bool_684;
    if (_t_Bool_684) {
        Str *_t_Str_678 = Str_lit("Str", 3ULL);
        (void)_t_Str_678;
        U32 _t_U32_679 = 16;
        (void)_t_U32_679;
        U32 _t_U32_680 = 1;
        (void)_t_U32_680;
        Array *_va_Array_19 = Array_new(_t_Str_678, &_t_U32_679, &_t_U32_680);
        (void)_va_Array_19;
        Str_delete(_t_Str_678, &(Bool){1});
        ;
        ;
        U32 _t_U32_681 = 0;
        (void)_t_U32_681;
        Str *_t_Str_682 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t_Str_682;
        Array_set(_va_Array_19, &_t_U32_681, _t_Str_682);
        ;
        Str *_t_Str_683 = Str_lit("./src/core/str.til:30:19", 24ULL);
        (void)_t_Str_683;
        panic(_t_Str_683, _va_Array_19);
        Str_delete(_t_Str_683, &(Bool){1});
    }
    ;
    void *_t_v_685 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_685;
    return _t_v_685;
}

U8 * Str_byte_at(Str * self, U32 * i) {
    (void)self;
    (void)i;
    void *_t_v_686 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_686;
    return _t_v_686;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    (void)min_len;
    Bool _t_Bool_695 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_695;
    if (_t_Bool_695) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_687 = U32_clone(&min_len);
        (void)_re_U32_687;
        U32 _rc_U32_687 = 0;
        (void)_rc_U32_687;
        Bool _t_Bool_694 = U32_lte(&_rc_U32_687, &_re_U32_687);
        (void)_t_Bool_694;
        if (_t_Bool_694) {
            while (1) {
                Bool _wcond_Bool_688 = U32_lt(&_rc_U32_687, &_re_U32_687);
                (void)_wcond_Bool_688;
                if (_wcond_Bool_688) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_687);
                (void)i;
                U32_inc(&_rc_U32_687);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_689 = 0;
                (void)_t_I64_689;
                Bool _t_Bool_690 = I64_neq(&c, &_t_I64_689);
                (void)_t_Bool_690;
                ;
                if (_t_Bool_690) {
                    ;
                    ;
                    ;
                    ;
                    ;
                    return c;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_691 = U32_gt(&_rc_U32_687, &_re_U32_687);
                (void)_wcond_Bool_691;
                if (_wcond_Bool_691) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_687);
                (void)i;
                U32_dec(&_rc_U32_687);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_692 = 0;
                (void)_t_I64_692;
                Bool _t_Bool_693 = I64_neq(&c, &_t_I64_692);
                (void)_t_Bool_693;
                ;
                if (_t_Bool_693) {
                    ;
                    ;
                    ;
                    ;
                    ;
                    return c;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    I64 _t_I64_696 = U32_cmp(a->count, b->count);
    (void)_t_I64_696;
    return _t_I64_696;
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_697 = U32_add(a->count, b->count);
    (void)_t_U32_697;
    Str *out = Str_with_capacity(&_t_U32_697);
    (void)out;
    ;
    Str_push_str(out, a);
    Str_push_str(out, b);
    return out;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_698 = 1;
    (void)_t_U32_698;
    U32 _t_U64_699 = U32_add(DEREF(n), _t_U32_698);
    (void)_t_U64_699;
    ;
    void * buf = malloc(_t_U64_699);
    (void)buf;
    ;
    I32 _t_I32_700 = 0;
    (void)_t_I32_700;
    U64 _t_U64_701 = 1;
    (void)_t_U64_701;
    memset(buf, _t_I32_700, _t_U64_701);
    ;
    ;
    I64 _t_I64_702 = 0;
    (void)_t_I64_702;
    Str *_t_Str_703 = malloc(sizeof(Str));
    _t_Str_703->c_str = buf;
    _t_Str_703->count = _t_I64_702;
    _t_Str_703->cap = DEREF(n);
    (void)_t_Str_703;
    ;
    return _t_Str_703;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_716 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_716;
    if (_t_Bool_716) {
        Str *_t_Str_704 = Str_lit("Str", 3ULL);
        (void)_t_Str_704;
        U32 _t_U32_705 = 16;
        (void)_t_U32_705;
        U32 _t_U32_706 = 1;
        (void)_t_U32_706;
        Array *_va_Array_20 = Array_new(_t_Str_704, &_t_U32_705, &_t_U32_706);
        (void)_va_Array_20;
        Str_delete(_t_Str_704, &(Bool){1});
        ;
        ;
        U32 _t_U32_707 = 0;
        (void)_t_U32_707;
        Str *_t_Str_708 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t_Str_708;
        Array_set(_va_Array_20, &_t_U32_707, _t_Str_708);
        ;
        Str *_t_Str_709 = Str_lit("./src/core/str.til:67:19", 24ULL);
        (void)_t_Str_709;
        panic(_t_Str_709, _va_Array_20);
        Str_delete(_t_Str_709, &(Bool){1});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    (void)new_len;
    Bool _t_Bool_717 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_717;
    if (_t_Bool_717) {
        Str *_t_Str_710 = Str_lit("Str", 3ULL);
        (void)_t_Str_710;
        U32 _t_U32_711 = 16;
        (void)_t_U32_711;
        U32 _t_U32_712 = 1;
        (void)_t_U32_712;
        Array *_va_Array_21 = Array_new(_t_Str_710, &_t_U32_711, &_t_U32_712);
        (void)_va_Array_21;
        Str_delete(_t_Str_710, &(Bool){1});
        ;
        ;
        U32 _t_U32_713 = 0;
        (void)_t_U32_713;
        Str *_t_Str_714 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t_Str_714;
        Array_set(_va_Array_21, &_t_U32_713, _t_Str_714);
        ;
        Str *_t_Str_715 = Str_lit("./src/core/str.til:71:19", 24ULL);
        (void)_t_Str_715;
        panic(_t_Str_715, _va_Array_21);
        Str_delete(_t_Str_715, &(Bool){1});
    }
    ;
    void *_t_v_718 = ptr_add(self->c_str, self->count);
    (void)_t_v_718;
    memcpy(_t_v_718, s->c_str, s->count);
    U32 _t_U32_719 = U32_clone(&new_len);
    (void)_t_U32_719;
    self->count = _t_U32_719;
    ;
    void *_t_v_720 = ptr_add(self->c_str, new_len);
    (void)_t_v_720;
    I32 _t_I32_721 = 0;
    (void)_t_I32_721;
    U64 _t_U64_722 = 1;
    (void)_t_U64_722;
    memset(_t_v_720, _t_I32_721, _t_U64_722);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_723 = 1;
    (void)_t_U32_723;
    U32 _t_U64_724 = U32_add(val->count, _t_U32_723);
    (void)_t_U64_724;
    ;
    void * new_data = malloc(_t_U64_724);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_725 = ptr_add(new_data, val->count);
    (void)_t_v_725;
    I32 _t_I32_726 = 0;
    (void)_t_I32_726;
    U64 _t_U64_727 = 1;
    (void)_t_U64_727;
    memset(_t_v_725, _t_I32_726, _t_U64_727);
    ;
    ;
    Str *_t_Str_728 = malloc(sizeof(Str));
    _t_Str_728->c_str = new_data;
    _t_Str_728->count = val->count;
    _t_Str_728->cap = val->count;
    (void)_t_Str_728;
    return _t_Str_728;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_729 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_729;
    if (_t_Bool_729) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t_Str_730 = Str_clone(val);
    (void)_t_Str_730;
    return _t_Str_730;
}

Str * Str_substr(Str * s, U32 * start, U32 * n) {
    (void)s;
    (void)start;
    (void)n;
    U32 st = U32_clone(start);
    (void)st;
    U32 ln = U32_clone(n);
    (void)ln;
    Bool _t_Bool_732 = U32_gt(&st, &s->count);
    (void)_t_Bool_732;
    if (_t_Bool_732) {
        st = s->count;
    }
    ;
    U32 _t_U32_733 = U32_add(st, ln);
    (void)_t_U32_733;
    Bool _t_Bool_734 = U32_gt(&_t_U32_733, &s->count);
    (void)_t_Bool_734;
    ;
    if (_t_Bool_734) {
        U32 _t_U32_731 = U32_sub(s->count, st);
        (void)_t_U32_731;
        ln = _t_U32_731;
        ;
    }
    ;
    void *_t_v_735 = ptr_add(s->c_str, st);
    (void)_t_v_735;
    Str *_t_Str_736 = malloc(sizeof(Str));
    _t_Str_736->c_str = _t_v_735;
    _t_Str_736->count = ln;
    _t_Str_736->cap = CAP_VIEW;
    (void)_t_Str_736;
    ;
    ;
    return _t_Str_736;
}

Bool Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_767 = 0;
    (void)_t_U32_767;
    Bool _t_Bool_768 = U32_eq(b->count, _t_U32_767);
    (void)_t_Bool_768;
    ;
    if (_t_Bool_768) {
        Bool _t_Bool_737 = 1;
        (void)_t_Bool_737;
        ;
        return _t_Bool_737;
    }
    ;
    Bool _t_Bool_769 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_769;
    if (_t_Bool_769) {
        Bool _t_Bool_738 = 0;
        (void)_t_Bool_738;
        ;
        return _t_Bool_738;
    }
    ;
    {
        U32 _t_U32_764 = U32_sub(a->count, b->count);
        (void)_t_U32_764;
        U32 _t_U32_765 = 1;
        (void)_t_U32_765;
        U32 _re_U32_739 = U32_add(_t_U32_764, _t_U32_765);
        (void)_re_U32_739;
        ;
        ;
        U32 _rc_U32_739 = 0;
        (void)_rc_U32_739;
        Bool _t_Bool_766 = U32_lte(&_rc_U32_739, &_re_U32_739);
        (void)_t_Bool_766;
        if (_t_Bool_766) {
            while (1) {
                Bool _wcond_Bool_740 = U32_lt(&_rc_U32_739, &_re_U32_739);
                (void)_wcond_Bool_740;
                if (_wcond_Bool_740) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_739);
                (void)i;
                U32_inc(&_rc_U32_739);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_741 = b->count;
                    (void)_re_U32_741;
                    U32 _rc_U32_741 = 0;
                    (void)_rc_U32_741;
                    Bool _t_Bool_750 = U32_lte(&_rc_U32_741, &_re_U32_741);
                    (void)_t_Bool_750;
                    if (_t_Bool_750) {
                        while (1) {
                            Bool _wcond_Bool_742 = U32_lt(&_rc_U32_741, &_re_U32_741);
                            (void)_wcond_Bool_742;
                            if (_wcond_Bool_742) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_741);
                            (void)j;
                            U32_inc(&_rc_U32_741);
                            U32 _t_U32_744 = U32_add(i, j);
                            (void)_t_U32_744;
                            U8 *ac = Str_get(a, &_t_U32_744);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_745 = U8_neq(ac, bc);
                            (void)_t_Bool_745;
                            ;
                            ;
                            if (_t_Bool_745) {
                                Bool _t_Bool_743 = 0;
                                (void)_t_Bool_743;
                                found = _t_Bool_743;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_746 = U32_gt(&_rc_U32_741, &_re_U32_741);
                            (void)_wcond_Bool_746;
                            if (_wcond_Bool_746) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_741);
                            (void)j;
                            U32_dec(&_rc_U32_741);
                            U32 _t_U32_748 = U32_add(i, j);
                            (void)_t_U32_748;
                            U8 *ac = Str_get(a, &_t_U32_748);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_749 = U8_neq(ac, bc);
                            (void)_t_Bool_749;
                            ;
                            ;
                            if (_t_Bool_749) {
                                Bool _t_Bool_747 = 0;
                                (void)_t_Bool_747;
                                found = _t_Bool_747;
                                ;
                            }
                            ;
                        }
                    }
                    ;
                    ;
                    ;
                }
                ;
                if (found) {
                    Bool _t_Bool_751 = 1;
                    (void)_t_Bool_751;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_751;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_752 = U32_gt(&_rc_U32_739, &_re_U32_739);
                (void)_wcond_Bool_752;
                if (_wcond_Bool_752) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_739);
                (void)i;
                U32_dec(&_rc_U32_739);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_753 = b->count;
                    (void)_re_U32_753;
                    U32 _rc_U32_753 = 0;
                    (void)_rc_U32_753;
                    Bool _t_Bool_762 = U32_lte(&_rc_U32_753, &_re_U32_753);
                    (void)_t_Bool_762;
                    if (_t_Bool_762) {
                        while (1) {
                            Bool _wcond_Bool_754 = U32_lt(&_rc_U32_753, &_re_U32_753);
                            (void)_wcond_Bool_754;
                            if (_wcond_Bool_754) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_753);
                            (void)j;
                            U32_inc(&_rc_U32_753);
                            U32 _t_U32_756 = U32_add(i, j);
                            (void)_t_U32_756;
                            U8 *ac = Str_get(a, &_t_U32_756);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_757 = U8_neq(ac, bc);
                            (void)_t_Bool_757;
                            ;
                            ;
                            if (_t_Bool_757) {
                                Bool _t_Bool_755 = 0;
                                (void)_t_Bool_755;
                                found = _t_Bool_755;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_758 = U32_gt(&_rc_U32_753, &_re_U32_753);
                            (void)_wcond_Bool_758;
                            if (_wcond_Bool_758) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_753);
                            (void)j;
                            U32_dec(&_rc_U32_753);
                            U32 _t_U32_760 = U32_add(i, j);
                            (void)_t_U32_760;
                            U8 *ac = Str_get(a, &_t_U32_760);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_761 = U8_neq(ac, bc);
                            (void)_t_Bool_761;
                            ;
                            ;
                            if (_t_Bool_761) {
                                Bool _t_Bool_759 = 0;
                                (void)_t_Bool_759;
                                found = _t_Bool_759;
                                ;
                            }
                            ;
                        }
                    }
                    ;
                    ;
                    ;
                }
                ;
                if (found) {
                    Bool _t_Bool_763 = 1;
                    (void)_t_Bool_763;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_763;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_770 = 0;
    (void)_t_Bool_770;
    return _t_Bool_770;
}

Bool Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_780 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_780;
    if (_t_Bool_780) {
        Bool _t_Bool_771 = 0;
        (void)_t_Bool_771;
        ;
        return _t_Bool_771;
    }
    ;
    {
        U32 _re_U32_772 = b->count;
        (void)_re_U32_772;
        U32 _rc_U32_772 = 0;
        (void)_rc_U32_772;
        Bool _t_Bool_779 = U32_lte(&_rc_U32_772, &_re_U32_772);
        (void)_t_Bool_779;
        if (_t_Bool_779) {
            while (1) {
                Bool _wcond_Bool_773 = U32_lt(&_rc_U32_772, &_re_U32_772);
                (void)_wcond_Bool_773;
                if (_wcond_Bool_773) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_772);
                (void)i;
                U32_inc(&_rc_U32_772);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_775 = U8_neq(ac, bc);
                (void)_t_Bool_775;
                ;
                if (_t_Bool_775) {
                    Bool _t_Bool_774 = 0;
                    (void)_t_Bool_774;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_774;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_776 = U32_gt(&_rc_U32_772, &_re_U32_772);
                (void)_wcond_Bool_776;
                if (_wcond_Bool_776) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_772);
                (void)i;
                U32_dec(&_rc_U32_772);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_778 = U8_neq(ac, bc);
                (void)_t_Bool_778;
                ;
                if (_t_Bool_778) {
                    Bool _t_Bool_777 = 0;
                    (void)_t_Bool_777;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_777;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_781 = 1;
    (void)_t_Bool_781;
    return _t_Bool_781;
}

Bool Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_793 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_793;
    if (_t_Bool_793) {
        Bool _t_Bool_782 = 0;
        (void)_t_Bool_782;
        ;
        return _t_Bool_782;
    }
    ;
    U32 offset = U32_sub(a->count, b->count);
    (void)offset;
    {
        U32 _re_U32_783 = b->count;
        (void)_re_U32_783;
        U32 _rc_U32_783 = 0;
        (void)_rc_U32_783;
        Bool _t_Bool_792 = U32_lte(&_rc_U32_783, &_re_U32_783);
        (void)_t_Bool_792;
        if (_t_Bool_792) {
            while (1) {
                Bool _wcond_Bool_784 = U32_lt(&_rc_U32_783, &_re_U32_783);
                (void)_wcond_Bool_784;
                if (_wcond_Bool_784) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_783);
                (void)i;
                U32_inc(&_rc_U32_783);
                U32 _t_U32_786 = U32_add(offset, i);
                (void)_t_U32_786;
                U8 *ac = Str_get(a, &_t_U32_786);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_787 = U8_neq(ac, bc);
                (void)_t_Bool_787;
                ;
                ;
                if (_t_Bool_787) {
                    Bool _t_Bool_785 = 0;
                    (void)_t_Bool_785;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_785;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_788 = U32_gt(&_rc_U32_783, &_re_U32_783);
                (void)_wcond_Bool_788;
                if (_wcond_Bool_788) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_783);
                (void)i;
                U32_dec(&_rc_U32_783);
                U32 _t_U32_790 = U32_add(offset, i);
                (void)_t_U32_790;
                U8 *ac = Str_get(a, &_t_U32_790);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_791 = U8_neq(ac, bc);
                (void)_t_Bool_791;
                ;
                ;
                if (_t_Bool_791) {
                    Bool _t_Bool_789 = 0;
                    (void)_t_Bool_789;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_789;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    Bool _t_Bool_794 = 1;
    (void)_t_Bool_794;
    return _t_Bool_794;
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_795 = 0;
    (void)_t_U32_795;
    Bool _t_Bool_796 = U32_eq(self->count, _t_U32_795);
    (void)_t_Bool_796;
    ;
    return _t_Bool_796;
}

I64 Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_831 = 0;
    (void)_t_U32_831;
    Bool _t_Bool_832 = U32_eq(needle->count, _t_U32_831);
    (void)_t_Bool_832;
    ;
    if (_t_Bool_832) {
        I64 _t_I64_797 = 0;
        (void)_t_I64_797;
        I64 _t_I64_798 = 1;
        (void)_t_I64_798;
        I64 _t_I64_799 = I64_sub(_t_I64_797, _t_I64_798);
        (void)_t_I64_799;
        ;
        ;
        ;
        return _t_I64_799;
    }
    ;
    Bool _t_Bool_833 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_833;
    if (_t_Bool_833) {
        I64 _t_I64_800 = 0;
        (void)_t_I64_800;
        I64 _t_I64_801 = 1;
        (void)_t_I64_801;
        I64 _t_I64_802 = I64_sub(_t_I64_800, _t_I64_801);
        (void)_t_I64_802;
        ;
        ;
        ;
        return _t_I64_802;
    }
    ;
    {
        U32 _t_U32_828 = U32_sub(self->count, needle->count);
        (void)_t_U32_828;
        U32 _t_U32_829 = 1;
        (void)_t_U32_829;
        U32 _re_U32_803 = U32_add(_t_U32_828, _t_U32_829);
        (void)_re_U32_803;
        ;
        ;
        U32 _rc_U32_803 = 0;
        (void)_rc_U32_803;
        Bool _t_Bool_830 = U32_lte(&_rc_U32_803, &_re_U32_803);
        (void)_t_Bool_830;
        if (_t_Bool_830) {
            while (1) {
                Bool _wcond_Bool_804 = U32_lt(&_rc_U32_803, &_re_U32_803);
                (void)_wcond_Bool_804;
                if (_wcond_Bool_804) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_803);
                (void)i;
                U32_inc(&_rc_U32_803);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_805 = needle->count;
                    (void)_re_U32_805;
                    U32 _rc_U32_805 = 0;
                    (void)_rc_U32_805;
                    Bool _t_Bool_814 = U32_lte(&_rc_U32_805, &_re_U32_805);
                    (void)_t_Bool_814;
                    if (_t_Bool_814) {
                        while (1) {
                            Bool _wcond_Bool_806 = U32_lt(&_rc_U32_805, &_re_U32_805);
                            (void)_wcond_Bool_806;
                            if (_wcond_Bool_806) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_805);
                            (void)j;
                            U32_inc(&_rc_U32_805);
                            U32 _t_U32_808 = U32_add(i, j);
                            (void)_t_U32_808;
                            U8 *ac = Str_get(self, &_t_U32_808);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_809 = U8_neq(ac, bc);
                            (void)_t_Bool_809;
                            ;
                            ;
                            if (_t_Bool_809) {
                                Bool _t_Bool_807 = 0;
                                (void)_t_Bool_807;
                                found = _t_Bool_807;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_810 = U32_gt(&_rc_U32_805, &_re_U32_805);
                            (void)_wcond_Bool_810;
                            if (_wcond_Bool_810) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_805);
                            (void)j;
                            U32_dec(&_rc_U32_805);
                            U32 _t_U32_812 = U32_add(i, j);
                            (void)_t_U32_812;
                            U8 *ac = Str_get(self, &_t_U32_812);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_813 = U8_neq(ac, bc);
                            (void)_t_Bool_813;
                            ;
                            ;
                            if (_t_Bool_813) {
                                Bool _t_Bool_811 = 0;
                                (void)_t_Bool_811;
                                found = _t_Bool_811;
                                ;
                            }
                            ;
                        }
                    }
                    ;
                    ;
                    ;
                }
                if (found) {
                    I64 _t_I64_815 = U32_to_i64(i);
                    (void)_t_I64_815;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_815;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_816 = U32_gt(&_rc_U32_803, &_re_U32_803);
                (void)_wcond_Bool_816;
                if (_wcond_Bool_816) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_803);
                (void)i;
                U32_dec(&_rc_U32_803);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_817 = needle->count;
                    (void)_re_U32_817;
                    U32 _rc_U32_817 = 0;
                    (void)_rc_U32_817;
                    Bool _t_Bool_826 = U32_lte(&_rc_U32_817, &_re_U32_817);
                    (void)_t_Bool_826;
                    if (_t_Bool_826) {
                        while (1) {
                            Bool _wcond_Bool_818 = U32_lt(&_rc_U32_817, &_re_U32_817);
                            (void)_wcond_Bool_818;
                            if (_wcond_Bool_818) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_817);
                            (void)j;
                            U32_inc(&_rc_U32_817);
                            U32 _t_U32_820 = U32_add(i, j);
                            (void)_t_U32_820;
                            U8 *ac = Str_get(self, &_t_U32_820);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_821 = U8_neq(ac, bc);
                            (void)_t_Bool_821;
                            ;
                            ;
                            if (_t_Bool_821) {
                                Bool _t_Bool_819 = 0;
                                (void)_t_Bool_819;
                                found = _t_Bool_819;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_822 = U32_gt(&_rc_U32_817, &_re_U32_817);
                            (void)_wcond_Bool_822;
                            if (_wcond_Bool_822) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_817);
                            (void)j;
                            U32_dec(&_rc_U32_817);
                            U32 _t_U32_824 = U32_add(i, j);
                            (void)_t_U32_824;
                            U8 *ac = Str_get(self, &_t_U32_824);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_825 = U8_neq(ac, bc);
                            (void)_t_Bool_825;
                            ;
                            ;
                            if (_t_Bool_825) {
                                Bool _t_Bool_823 = 0;
                                (void)_t_Bool_823;
                                found = _t_Bool_823;
                                ;
                            }
                            ;
                        }
                    }
                    ;
                    ;
                    ;
                }
                if (found) {
                    I64 _t_I64_827 = U32_to_i64(i);
                    (void)_t_I64_827;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_827;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    I64 _t_I64_834 = 0;
    (void)_t_I64_834;
    I64 _t_I64_835 = 1;
    (void)_t_I64_835;
    I64 _t_I64_836 = I64_sub(_t_I64_834, _t_I64_835);
    (void)_t_I64_836;
    ;
    ;
    return _t_I64_836;
}

I64 Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_871 = 0;
    (void)_t_U32_871;
    Bool _t_Bool_872 = U32_eq(needle->count, _t_U32_871);
    (void)_t_Bool_872;
    ;
    if (_t_Bool_872) {
        I64 _t_I64_837 = 0;
        (void)_t_I64_837;
        I64 _t_I64_838 = 1;
        (void)_t_I64_838;
        I64 _t_I64_839 = I64_sub(_t_I64_837, _t_I64_838);
        (void)_t_I64_839;
        ;
        ;
        ;
        return _t_I64_839;
    }
    ;
    Bool _t_Bool_873 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_873;
    if (_t_Bool_873) {
        I64 _t_I64_840 = 0;
        (void)_t_I64_840;
        I64 _t_I64_841 = 1;
        (void)_t_I64_841;
        I64 _t_I64_842 = I64_sub(_t_I64_840, _t_I64_841);
        (void)_t_I64_842;
        ;
        ;
        ;
        return _t_I64_842;
    }
    ;
    I64 _t_I64_874 = 0;
    (void)_t_I64_874;
    I64 _t_I64_875 = 1;
    (void)_t_I64_875;
    I64 last = I64_sub(_t_I64_874, _t_I64_875);
    (void)last;
    ;
    ;
    {
        U32 _t_U32_868 = U32_sub(self->count, needle->count);
        (void)_t_U32_868;
        U32 _t_U32_869 = 1;
        (void)_t_U32_869;
        U32 _re_U32_843 = U32_add(_t_U32_868, _t_U32_869);
        (void)_re_U32_843;
        ;
        ;
        U32 _rc_U32_843 = 0;
        (void)_rc_U32_843;
        Bool _t_Bool_870 = U32_lte(&_rc_U32_843, &_re_U32_843);
        (void)_t_Bool_870;
        if (_t_Bool_870) {
            while (1) {
                Bool _wcond_Bool_844 = U32_lt(&_rc_U32_843, &_re_U32_843);
                (void)_wcond_Bool_844;
                if (_wcond_Bool_844) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_843);
                (void)i;
                U32_inc(&_rc_U32_843);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_845 = needle->count;
                    (void)_re_U32_845;
                    U32 _rc_U32_845 = 0;
                    (void)_rc_U32_845;
                    Bool _t_Bool_854 = U32_lte(&_rc_U32_845, &_re_U32_845);
                    (void)_t_Bool_854;
                    if (_t_Bool_854) {
                        while (1) {
                            Bool _wcond_Bool_846 = U32_lt(&_rc_U32_845, &_re_U32_845);
                            (void)_wcond_Bool_846;
                            if (_wcond_Bool_846) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_845);
                            (void)j;
                            U32_inc(&_rc_U32_845);
                            U32 _t_U32_848 = U32_add(i, j);
                            (void)_t_U32_848;
                            U8 *ac = Str_get(self, &_t_U32_848);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_849 = U8_neq(ac, bc);
                            (void)_t_Bool_849;
                            ;
                            ;
                            if (_t_Bool_849) {
                                Bool _t_Bool_847 = 0;
                                (void)_t_Bool_847;
                                found = _t_Bool_847;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_850 = U32_gt(&_rc_U32_845, &_re_U32_845);
                            (void)_wcond_Bool_850;
                            if (_wcond_Bool_850) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_845);
                            (void)j;
                            U32_dec(&_rc_U32_845);
                            U32 _t_U32_852 = U32_add(i, j);
                            (void)_t_U32_852;
                            U8 *ac = Str_get(self, &_t_U32_852);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_853 = U8_neq(ac, bc);
                            (void)_t_Bool_853;
                            ;
                            ;
                            if (_t_Bool_853) {
                                Bool _t_Bool_851 = 0;
                                (void)_t_Bool_851;
                                found = _t_Bool_851;
                                ;
                            }
                            ;
                        }
                    }
                    ;
                    ;
                    ;
                }
                if (found) {
                    I64 _t_I64_855 = U32_to_i64(i);
                    (void)_t_I64_855;
                    last = _t_I64_855;
                    ;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_856 = U32_gt(&_rc_U32_843, &_re_U32_843);
                (void)_wcond_Bool_856;
                if (_wcond_Bool_856) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_843);
                (void)i;
                U32_dec(&_rc_U32_843);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_857 = needle->count;
                    (void)_re_U32_857;
                    U32 _rc_U32_857 = 0;
                    (void)_rc_U32_857;
                    Bool _t_Bool_866 = U32_lte(&_rc_U32_857, &_re_U32_857);
                    (void)_t_Bool_866;
                    if (_t_Bool_866) {
                        while (1) {
                            Bool _wcond_Bool_858 = U32_lt(&_rc_U32_857, &_re_U32_857);
                            (void)_wcond_Bool_858;
                            if (_wcond_Bool_858) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_857);
                            (void)j;
                            U32_inc(&_rc_U32_857);
                            U32 _t_U32_860 = U32_add(i, j);
                            (void)_t_U32_860;
                            U8 *ac = Str_get(self, &_t_U32_860);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_861 = U8_neq(ac, bc);
                            (void)_t_Bool_861;
                            ;
                            ;
                            if (_t_Bool_861) {
                                Bool _t_Bool_859 = 0;
                                (void)_t_Bool_859;
                                found = _t_Bool_859;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_862 = U32_gt(&_rc_U32_857, &_re_U32_857);
                            (void)_wcond_Bool_862;
                            if (_wcond_Bool_862) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_857);
                            (void)j;
                            U32_dec(&_rc_U32_857);
                            U32 _t_U32_864 = U32_add(i, j);
                            (void)_t_U32_864;
                            U8 *ac = Str_get(self, &_t_U32_864);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_865 = U8_neq(ac, bc);
                            (void)_t_Bool_865;
                            ;
                            ;
                            if (_t_Bool_865) {
                                Bool _t_Bool_863 = 0;
                                (void)_t_Bool_863;
                                found = _t_Bool_863;
                                ;
                            }
                            ;
                        }
                    }
                    ;
                    ;
                    ;
                }
                if (found) {
                    I64 _t_I64_867 = U32_to_i64(i);
                    (void)_t_I64_867;
                    last = _t_I64_867;
                    ;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    return last;
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    (void)from;
    (void)to;
    U32 _t_U32_901 = 0;
    (void)_t_U32_901;
    Bool _t_Bool_902 = U32_eq(from->count, _t_U32_901);
    (void)_t_Bool_902;
    ;
    if (_t_Bool_902) {
        Str *_t_Str_876 = Str_clone(self);
        (void)_t_Str_876;
        ;
        return _t_Str_876;
    }
    ;
    U32 matches = 0;
    (void)matches;
    U32 start = 0;
    (void)start;
    while (1) {
        U32 _t_U32_878 = U32_sub(self->count, from->count);
        (void)_t_U32_878;
        Bool _wcond_Bool_877 = U32_lte(&start, &_t_U32_878);
        (void)_wcond_Bool_877;
        ;
        if (_wcond_Bool_877) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_879 = U32_sub(self->count, start);
        (void)_t_U32_879;
        Str *rest = Str_substr(self, &start, &_t_U32_879);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_880 = 0;
        (void)_t_I64_880;
        I64 _t_I64_881 = 1;
        (void)_t_I64_881;
        I64 _t_I64_882 = I64_sub(_t_I64_880, _t_I64_881);
        (void)_t_I64_882;
        ;
        ;
        Bool _t_Bool_883 = I64_eq(pos, _t_I64_882);
        (void)_t_Bool_883;
        ;
        if (_t_Bool_883) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        U32 _t_U32_884 = U32_add(start, pos_u);
        (void)_t_U32_884;
        ;
        U32 _t_U32_885 = U32_add(_t_U32_884, from->count);
        (void)_t_U32_885;
        ;
        start = _t_U32_885;
        ;
        U32 _t_U32_886 = 1;
        (void)_t_U32_886;
        U32 _t_U32_887 = U32_add(matches, _t_U32_886);
        (void)_t_U32_887;
        ;
        matches = _t_U32_887;
        ;
    }
    U32 _t_U32_903 = 0;
    (void)_t_U32_903;
    Bool _t_Bool_904 = U32_eq(matches, _t_U32_903);
    (void)_t_Bool_904;
    ;
    if (_t_Bool_904) {
        Str *_t_Str_888 = Str_clone(self);
        (void)_t_Str_888;
        ;
        ;
        ;
        return _t_Str_888;
    }
    ;
    U32 removed = U32_mul(matches, from->count);
    (void)removed;
    U32 added = U32_mul(matches, to->count);
    (void)added;
    ;
    U32 _t_U32_905 = U32_sub(self->count, removed);
    (void)_t_U32_905;
    ;
    U32 _t_U32_906 = U32_add(_t_U32_905, added);
    (void)_t_U32_906;
    ;
    ;
    Str *out = Str_with_capacity(&_t_U32_906);
    (void)out;
    ;
    U32 _t_U32_907 = 0;
    (void)_t_U32_907;
    start = _t_U32_907;
    ;
    while (1) {
        U32 _t_U32_890 = U32_sub(self->count, from->count);
        (void)_t_U32_890;
        Bool _wcond_Bool_889 = U32_lte(&start, &_t_U32_890);
        (void)_wcond_Bool_889;
        ;
        if (_wcond_Bool_889) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_891 = U32_sub(self->count, start);
        (void)_t_U32_891;
        Str *rest = Str_substr(self, &start, &_t_U32_891);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_892 = 0;
        (void)_t_I64_892;
        I64 _t_I64_893 = 1;
        (void)_t_I64_893;
        I64 _t_I64_894 = I64_sub(_t_I64_892, _t_I64_893);
        (void)_t_I64_894;
        ;
        ;
        Bool _t_Bool_895 = I64_eq(pos, _t_I64_894);
        (void)_t_Bool_895;
        ;
        if (_t_Bool_895) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        Str *_t_Str_896 = Str_substr(self, &start, &pos_u);
        (void)_t_Str_896;
        Str_push_str(out, _t_Str_896);
        Str_delete(_t_Str_896, &(Bool){1});
        Str_push_str(out, to);
        U32 _t_U32_897 = U32_add(start, pos_u);
        (void)_t_U32_897;
        ;
        U32 _t_U32_898 = U32_add(_t_U32_897, from->count);
        (void)_t_U32_898;
        ;
        start = _t_U32_898;
        ;
    }
    Bool _t_Bool_908 = U32_lt(&start, &self->count);
    (void)_t_Bool_908;
    if (_t_Bool_908) {
        U32 _t_U32_899 = U32_sub(self->count, start);
        (void)_t_U32_899;
        Str *_t_Str_900 = Str_substr(self, &start, &_t_U32_899);
        (void)_t_Str_900;
        ;
        Str_push_str(out, _t_Str_900);
        Str_delete(_t_Str_900, &(Bool){1});
    }
    ;
    ;
    return out;
}

Str * Str_get_char(Str * self, U32 * i) {
    (void)self;
    (void)i;
    U32 _t_U32_909 = 1;
    (void)_t_U32_909;
    Str *_t_Str_910 = Str_substr(self, i, &_t_U32_909);
    (void)_t_Str_910;
    ;
    return _t_Str_910;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t_Bool_913 = Str_starts_with(self, prefix);
    (void)_t_Bool_913;
    if (_t_Bool_913) {
        U32 _t_U32_911 = U32_sub(self->count, prefix->count);
        (void)_t_U32_911;
        Str *_t_Str_912 = Str_substr(self, &prefix->count, &_t_U32_911);
        (void)_t_Str_912;
        ;
        ;
        return _t_Str_912;
    }
    ;
    Str *_t_Str_914 = Str_clone(self);
    (void)_t_Str_914;
    return _t_Str_914;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t_Bool_918 = Str_ends_with(self, suffix);
    (void)_t_Bool_918;
    if (_t_Bool_918) {
        U32 _t_U32_915 = 0;
        (void)_t_U32_915;
        U32 _t_U32_916 = U32_sub(self->count, suffix->count);
        (void)_t_U32_916;
        Str *_t_Str_917 = Str_substr(self, &_t_U32_915, &_t_U32_916);
        (void)_t_Str_917;
        ;
        ;
        ;
        return _t_Str_917;
    }
    ;
    Str *_t_Str_919 = Str_clone(self);
    (void)_t_Str_919;
    return _t_Str_919;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t_U64_920 = 2;
    (void)_t_U64_920;
    void * buf = malloc(_t_U64_920);
    (void)buf;
    ;
    U64 _t_U64_921 = 1;
    (void)_t_U64_921;
    memcpy(buf, byte, _t_U64_921);
    ;
    U64 _t_U64_922 = 1;
    (void)_t_U64_922;
    void *_t_v_923 = ptr_add(buf, _t_U64_922);
    (void)_t_v_923;
    I32 _t_I32_924 = 0;
    (void)_t_I32_924;
    U64 _t_U64_925 = 1;
    (void)_t_U64_925;
    memset(_t_v_923, _t_I32_924, _t_U64_925);
    ;
    ;
    ;
    I64 _t_I64_926 = 1;
    (void)_t_I64_926;
    I64 _t_I64_927 = 1;
    (void)_t_I64_927;
    Str *_t_Str_928 = malloc(sizeof(Str));
    _t_Str_928->c_str = buf;
    _t_Str_928->count = _t_I64_926;
    _t_Str_928->cap = _t_I64_927;
    (void)_t_Str_928;
    ;
    ;
    return _t_Str_928;
}

I64 Str_to_i64(Str * self) {
    (void)self;
    U32 _t_U32_989 = 0;
    (void)_t_U32_989;
    Bool _t_Bool_990 = U32_eq(self->count, _t_U32_989);
    (void)_t_Bool_990;
    ;
    if (_t_Bool_990) {
        Str *_t_Str_929 = Str_lit("Str", 3ULL);
        (void)_t_Str_929;
        U32 _t_U32_930 = 16;
        (void)_t_U32_930;
        U32 _t_U32_931 = 1;
        (void)_t_U32_931;
        Array *_va_Array_22 = Array_new(_t_Str_929, &_t_U32_930, &_t_U32_931);
        (void)_va_Array_22;
        Str_delete(_t_Str_929, &(Bool){1});
        ;
        ;
        U32 _t_U32_932 = 0;
        (void)_t_U32_932;
        Str *_t_Str_933 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t_Str_933;
        Array_set(_va_Array_22, &_t_U32_932, _t_Str_933);
        ;
        Str *_t_Str_934 = Str_lit("./src/core/str.til:233:37", 25ULL);
        (void)_t_Str_934;
        panic(_t_Str_934, _va_Array_22);
        Str_delete(_t_Str_934, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_991 = 0;
    (void)_t_U32_991;
    U8 *first = Str_get(self, &_t_U32_991);
    (void)first;
    U8 _t_U8_992 = 45;
    (void)_t_U8_992;
    Bool _t_Bool_993 = U8_eq(DEREF(first), _t_U8_992);
    (void)_t_Bool_993;
    ;
    ;
    if (_t_Bool_993) {
        Bool _t_Bool_935 = 1;
        (void)_t_Bool_935;
        neg = _t_Bool_935;
        ;
        U32 _t_U32_936 = 1;
        (void)_t_U32_936;
        start = _t_U32_936;
        ;
    }
    ;
    Bool _t_Bool_994 = U32_eq(start, self->count);
    (void)_t_Bool_994;
    if (_t_Bool_994) {
        Str *_t_Str_937 = Str_lit("Str", 3ULL);
        (void)_t_Str_937;
        U32 _t_U32_938 = 16;
        (void)_t_U32_938;
        U32 _t_U32_939 = 1;
        (void)_t_U32_939;
        Array *_va_Array_23 = Array_new(_t_Str_937, &_t_U32_938, &_t_U32_939);
        (void)_va_Array_23;
        Str_delete(_t_Str_937, &(Bool){1});
        ;
        ;
        U32 _t_U32_940 = 0;
        (void)_t_U32_940;
        Str *_t_Str_941 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t_Str_941;
        Array_set(_va_Array_23, &_t_U32_940, _t_Str_941);
        ;
        Str *_t_Str_942 = Str_lit("./src/core/str.til:242:41", 25ULL);
        (void)_t_Str_942;
        panic(_t_Str_942, _va_Array_23);
        Str_delete(_t_Str_942, &(Bool){1});
    }
    ;
    {
        U32 _re_U32_943 = self->count;
        (void)_re_U32_943;
        U32 _rc_U32_943 = U32_clone(&start);
        (void)_rc_U32_943;
        Bool _t_Bool_986 = U32_lte(&_rc_U32_943, &_re_U32_943);
        (void)_t_Bool_986;
        if (_t_Bool_986) {
            while (1) {
                Bool _wcond_Bool_944 = U32_lt(&_rc_U32_943, &_re_U32_943);
                (void)_wcond_Bool_944;
                if (_wcond_Bool_944) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_943);
                (void)i;
                U32_inc(&_rc_U32_943);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_955 = U8_to_i64(DEREF(ch));
                (void)_t_I64_955;
                ;
                I64 _t_I64_956 = 48;
                (void)_t_I64_956;
                I64 d = I64_sub(_t_I64_955, _t_I64_956);
                (void)d;
                ;
                ;
                I64 _t_I64_957 = 0;
                (void)_t_I64_957;
                I64 _t_I64_958 = 9;
                (void)_t_I64_958;
                Bool _t_Bool_959 = I64_lt(&d, &_t_I64_957);
                (void)_t_Bool_959;
                ;
                Bool _t_Bool_960 = I64_gt(&d, &_t_I64_958);
                (void)_t_Bool_960;
                ;
                Bool _t_Bool_961 = or(_t_Bool_959, _t_Bool_960);
                (void)_t_Bool_961;
                ;
                ;
                if (_t_Bool_961) {
                    Str *_t_Str_945 = Str_lit("Str", 3ULL);
                    (void)_t_Str_945;
                    U32 _t_U32_946 = 16;
                    (void)_t_U32_946;
                    U32 _t_U32_947 = 3;
                    (void)_t_U32_947;
                    Array *_va_Array_24 = Array_new(_t_Str_945, &_t_U32_946, &_t_U32_947);
                    (void)_va_Array_24;
                    Str_delete(_t_Str_945, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_948 = 0;
                    (void)_t_U32_948;
                    Str *_t_Str_949 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_949;
                    Array_set(_va_Array_24, &_t_U32_948, _t_Str_949);
                    ;
                    U32 _t_U32_950 = 1;
                    (void)_t_U32_950;
                    Str *_t_Str_951 = Str_clone(self);
                    (void)_t_Str_951;
                    Array_set(_va_Array_24, &_t_U32_950, _t_Str_951);
                    ;
                    U32 _t_U32_952 = 2;
                    (void)_t_U32_952;
                    Str *_t_Str_953 = Str_lit("'", 1ULL);
                    (void)_t_Str_953;
                    Array_set(_va_Array_24, &_t_U32_952, _t_Str_953);
                    ;
                    Str *_t_Str_954 = Str_lit("./src/core/str.til:247:23", 25ULL);
                    (void)_t_Str_954;
                    panic(_t_Str_954, _va_Array_24);
                    Str_delete(_t_Str_954, &(Bool){1});
                }
                ;
                I64 _t_I64_962 = 10;
                (void)_t_I64_962;
                I64 _t_I64_963 = I64_mul(result, _t_I64_962);
                (void)_t_I64_963;
                ;
                I64 _t_I64_964 = I64_add(_t_I64_963, d);
                (void)_t_I64_964;
                ;
                ;
                result = _t_I64_964;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_965 = U32_gt(&_rc_U32_943, &_re_U32_943);
                (void)_wcond_Bool_965;
                if (_wcond_Bool_965) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_943);
                (void)i;
                U32_dec(&_rc_U32_943);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_976 = U8_to_i64(DEREF(ch));
                (void)_t_I64_976;
                ;
                I64 _t_I64_977 = 48;
                (void)_t_I64_977;
                I64 d = I64_sub(_t_I64_976, _t_I64_977);
                (void)d;
                ;
                ;
                I64 _t_I64_978 = 0;
                (void)_t_I64_978;
                I64 _t_I64_979 = 9;
                (void)_t_I64_979;
                Bool _t_Bool_980 = I64_lt(&d, &_t_I64_978);
                (void)_t_Bool_980;
                ;
                Bool _t_Bool_981 = I64_gt(&d, &_t_I64_979);
                (void)_t_Bool_981;
                ;
                Bool _t_Bool_982 = or(_t_Bool_980, _t_Bool_981);
                (void)_t_Bool_982;
                ;
                ;
                if (_t_Bool_982) {
                    Str *_t_Str_966 = Str_lit("Str", 3ULL);
                    (void)_t_Str_966;
                    U32 _t_U32_967 = 16;
                    (void)_t_U32_967;
                    U32 _t_U32_968 = 3;
                    (void)_t_U32_968;
                    Array *_va_Array_25 = Array_new(_t_Str_966, &_t_U32_967, &_t_U32_968);
                    (void)_va_Array_25;
                    Str_delete(_t_Str_966, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_969 = 0;
                    (void)_t_U32_969;
                    Str *_t_Str_970 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_970;
                    Array_set(_va_Array_25, &_t_U32_969, _t_Str_970);
                    ;
                    U32 _t_U32_971 = 1;
                    (void)_t_U32_971;
                    Str *_t_Str_972 = Str_clone(self);
                    (void)_t_Str_972;
                    Array_set(_va_Array_25, &_t_U32_971, _t_Str_972);
                    ;
                    U32 _t_U32_973 = 2;
                    (void)_t_U32_973;
                    Str *_t_Str_974 = Str_lit("'", 1ULL);
                    (void)_t_Str_974;
                    Array_set(_va_Array_25, &_t_U32_973, _t_Str_974);
                    ;
                    Str *_t_Str_975 = Str_lit("./src/core/str.til:247:23", 25ULL);
                    (void)_t_Str_975;
                    panic(_t_Str_975, _va_Array_25);
                    Str_delete(_t_Str_975, &(Bool){1});
                }
                ;
                I64 _t_I64_983 = 10;
                (void)_t_I64_983;
                I64 _t_I64_984 = I64_mul(result, _t_I64_983);
                (void)_t_I64_984;
                ;
                I64 _t_I64_985 = I64_add(_t_I64_984, d);
                (void)_t_I64_985;
                ;
                ;
                result = _t_I64_985;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    if (neg) {
        I64 _t_I64_987 = 0;
        (void)_t_I64_987;
        I64 _t_I64_988 = I64_sub(_t_I64_987, result);
        (void)_t_I64_988;
        ;
        ;
        ;
        return _t_I64_988;
    }
    ;
    return result;
}

U8 Str_to_u8(Str * self) {
    (void)self;
    I64 _t_I64_995 = Str_to_i64(self);
    (void)_t_I64_995;
    U8 _t_U8_996 = I64_to_u8(_t_I64_995);
    (void)_t_U8_996;
    ;
    return _t_U8_996;
}

I32 Str_to_i32(Str * self) {
    (void)self;
    I64 _t_I64_997 = Str_to_i64(self);
    (void)_t_I64_997;
    I32 _t_I32_998 = I64_to_i32(_t_I64_997);
    (void)_t_I32_998;
    ;
    return _t_I32_998;
}

F32 Str_to_f32(Str * self) {
    (void)self;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_1024 = Str_len(self);
    (void)_t_U32_1024;
    U32 _t_U32_1025 = 0;
    (void)_t_U32_1025;
    U32 _t_U32_1026 = 0;
    (void)_t_U32_1026;
    U8 *_t_U8_1027 = Str_get(self, &_t_U32_1026);
    (void)_t_U8_1027;
    U8 _t_U8_1028 = 45;
    (void)_t_U8_1028;
    Bool _t_Bool_1029 = U32_gt(&_t_U32_1024, &_t_U32_1025);
    (void)_t_Bool_1029;
    ;
    ;
    Bool _t_Bool_1030 = U8_eq(DEREF(_t_U8_1027), _t_U8_1028);
    (void)_t_Bool_1030;
    ;
    ;
    Bool _t_Bool_1031 = and(_t_Bool_1029, _t_Bool_1030);
    (void)_t_Bool_1031;
    ;
    ;
    if (_t_Bool_1031) {
        Bool _t_Bool_999 = 1;
        (void)_t_Bool_999;
        neg = _t_Bool_999;
        ;
        U32 _t_U32_1000 = 1;
        (void)_t_U32_1000;
        start = _t_U32_1000;
        ;
    }
    ;
    U32 _t_U32_1032 = Str_len(self);
    (void)_t_U32_1032;
    U32 _t_U32_1033 = U32_sub(_t_U32_1032, start);
    (void)_t_U32_1033;
    ;
    Str *rest = Str_substr(self, &start, &_t_U32_1033);
    (void)rest;
    ;
    ;
    Str *_t_Str_1034 = Str_lit(".", 1ULL);
    (void)_t_Str_1034;
    I64 dot = Str_find(rest, _t_Str_1034);
    (void)dot;
    Str_delete(_t_Str_1034, &(Bool){1});
    I64 _t_I64_1035 = 0;
    (void)_t_I64_1035;
    I64 _t_I64_1036 = 1;
    (void)_t_I64_1036;
    I64 _t_I64_1037 = I64_sub(_t_I64_1035, _t_I64_1036);
    (void)_t_I64_1037;
    ;
    ;
    Bool _t_Bool_1038 = I64_eq(dot, _t_I64_1037);
    (void)_t_Bool_1038;
    ;
    if (_t_Bool_1038) {
        I64 _t_I64_1004 = Str_to_i64(rest);
        (void)_t_I64_1004;
        F32 out = I64_to_f32(_t_I64_1004);
        (void)out;
        ;
        if (neg) {
            I64 _t_I64_1001 = 0;
            (void)_t_I64_1001;
            F32 _t_F32_1002 = I64_to_f32(_t_I64_1001);
            (void)_t_F32_1002;
            ;
            F32 _t_F32_1003 = F32_sub(_t_F32_1002, out);
            (void)_t_F32_1003;
            ;
            ;
            ;
            ;
            ;
            Str_delete(rest, &(Bool){1});
            return _t_F32_1003;
        }
        ;
        ;
        ;
        Str_delete(rest, &(Bool){1});
        return out;
    }
    ;
    U32 _t_U32_1039 = 0;
    (void)_t_U32_1039;
    U32 _t_U32_1040 = I64_to_usize(dot);
    (void)_t_U32_1040;
    Str *int_part = Str_substr(rest, &_t_U32_1039, &_t_U32_1040);
    (void)int_part;
    ;
    ;
    U32 _t_U32_1041 = I64_to_usize(dot);
    (void)_t_U32_1041;
    U32 _t_U32_1042 = 1;
    (void)_t_U32_1042;
    U32 _t_U32_1043 = I64_to_usize(dot);
    (void)_t_U32_1043;
    ;
    U32 _t_U32_1044 = 1;
    (void)_t_U32_1044;
    U32 _t_U32_1045 = Str_len(rest);
    (void)_t_U32_1045;
    U32 _t_U32_1046 = U32_add(_t_U32_1043, _t_U32_1044);
    (void)_t_U32_1046;
    ;
    ;
    U32 _t_U32_1047 = U32_add(_t_U32_1041, _t_U32_1042);
    (void)_t_U32_1047;
    ;
    ;
    U32 _t_U32_1048 = U32_sub(_t_U32_1045, _t_U32_1046);
    (void)_t_U32_1048;
    ;
    ;
    Str *frac_part = Str_substr(rest, &_t_U32_1047, &_t_U32_1048);
    (void)frac_part;
    ;
    ;
    Str_delete(rest, &(Bool){1});
    I64 _t_I64_1049 = 0;
    (void)_t_I64_1049;
    F32 out = I64_to_f32(_t_I64_1049);
    (void)out;
    ;
    U32 _t_U32_1050 = Str_len(int_part);
    (void)_t_U32_1050;
    U32 _t_U32_1051 = 0;
    (void)_t_U32_1051;
    Bool _t_Bool_1052 = U32_gt(&_t_U32_1050, &_t_U32_1051);
    (void)_t_Bool_1052;
    ;
    ;
    if (_t_Bool_1052) {
        I64 _t_I64_1005 = Str_to_i64(int_part);
        (void)_t_I64_1005;
        F32 _t_F32_1006 = I64_to_f32(_t_I64_1005);
        (void)_t_F32_1006;
        ;
        out = _t_F32_1006;
        ;
    }
    ;
    Str_delete(int_part, &(Bool){1});
    U32 _t_U32_1053 = Str_len(frac_part);
    (void)_t_U32_1053;
    U32 _t_U32_1054 = 0;
    (void)_t_U32_1054;
    Bool _t_Bool_1055 = U32_gt(&_t_U32_1053, &_t_U32_1054);
    (void)_t_Bool_1055;
    ;
    ;
    if (_t_Bool_1055) {
        I64 _t_I64_1017 = Str_to_i64(frac_part);
        (void)_t_I64_1017;
        F32 frac = I64_to_f32(_t_I64_1017);
        (void)frac;
        ;
        I64 _t_I64_1018 = 1;
        (void)_t_I64_1018;
        F32 scale = I64_to_f32(_t_I64_1018);
        (void)scale;
        ;
        {
            U32 _re_U32_1007 = Str_len(frac_part);
            (void)_re_U32_1007;
            U32 _rc_U32_1007 = 0;
            (void)_rc_U32_1007;
            Bool _t_Bool_1016 = U32_lte(&_rc_U32_1007, &_re_U32_1007);
            (void)_t_Bool_1016;
            if (_t_Bool_1016) {
                while (1) {
                    Bool _wcond_Bool_1008 = U32_lt(&_rc_U32_1007, &_re_U32_1007);
                    (void)_wcond_Bool_1008;
                    if (_wcond_Bool_1008) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_1007);
                    (void)_;
                    ;
                    U32_inc(&_rc_U32_1007);
                    I64 _t_I64_1009 = 10;
                    (void)_t_I64_1009;
                    F32 _t_F32_1010 = I64_to_f32(_t_I64_1009);
                    (void)_t_F32_1010;
                    ;
                    F32 _t_F32_1011 = F32_mul(scale, _t_F32_1010);
                    (void)_t_F32_1011;
                    ;
                    scale = _t_F32_1011;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1012 = U32_gt(&_rc_U32_1007, &_re_U32_1007);
                    (void)_wcond_Bool_1012;
                    if (_wcond_Bool_1012) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_1007);
                    (void)_;
                    ;
                    U32_dec(&_rc_U32_1007);
                    I64 _t_I64_1013 = 10;
                    (void)_t_I64_1013;
                    F32 _t_F32_1014 = I64_to_f32(_t_I64_1013);
                    (void)_t_F32_1014;
                    ;
                    F32 _t_F32_1015 = F32_mul(scale, _t_F32_1014);
                    (void)_t_F32_1015;
                    ;
                    scale = _t_F32_1015;
                    ;
                }
            }
            ;
            ;
            ;
        }
        F32 _t_F32_1019 = F32_div(frac, scale);
        (void)_t_F32_1019;
        ;
        ;
        F32 _t_F32_1020 = F32_add(out, _t_F32_1019);
        (void)_t_F32_1020;
        ;
        out = _t_F32_1020;
        ;
    }
    ;
    Str_delete(frac_part, &(Bool){1});
    if (neg) {
        I64 _t_I64_1021 = 0;
        (void)_t_I64_1021;
        F32 _t_F32_1022 = I64_to_f32(_t_I64_1021);
        (void)_t_F32_1022;
        ;
        F32 _t_F32_1023 = F32_sub(_t_F32_1022, out);
        (void)_t_F32_1023;
        ;
        ;
        ;
        return _t_F32_1023;
    }
    ;
    return out;
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t_Str_1072 = Str_lit("Str", 3ULL);
    (void)_t_Str_1072;
    U32 _t_U32_1073 = 16;
    (void)_t_U32_1073;
    Vec *parts = Vec_new(_t_Str_1072, &_t_U32_1073);
    (void)parts;
    Str_delete(_t_Str_1072, &(Bool){1});
    ;
    U32 _t_U32_1074 = Str_len(delim);
    (void)_t_U32_1074;
    U32 _t_U32_1075 = 0;
    (void)_t_U32_1075;
    Bool _t_Bool_1076 = U32_eq(_t_U32_1074, _t_U32_1075);
    (void)_t_Bool_1076;
    ;
    ;
    if (_t_Bool_1076) {
        Str *_t_Str_1056 = Str_clone(self);
        (void)_t_Str_1056;
        Vec_push(parts, _t_Str_1056);
        ;
        return parts;
    }
    ;
    U32 start = 0;
    (void)start;
    U32 pos = 0;
    (void)pos;
    while (1) {
        U32 _t_U32_1066 = Str_len(self);
        (void)_t_U32_1066;
        U32 _t_U32_1067 = Str_len(delim);
        (void)_t_U32_1067;
        U32 _t_U32_1068 = U32_sub(_t_U32_1066, _t_U32_1067);
        (void)_t_U32_1068;
        ;
        ;
        Bool _wcond_Bool_1057 = U32_lte(&pos, &_t_U32_1068);
        (void)_wcond_Bool_1057;
        ;
        if (_wcond_Bool_1057) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_1069 = Str_len(delim);
        (void)_t_U32_1069;
        Str *_t_Str_1070 = Str_substr(self, &pos, &_t_U32_1069);
        (void)_t_Str_1070;
        ;
        Bool _t_Bool_1071 = Str_eq(_t_Str_1070, delim);
        (void)_t_Bool_1071;
        Str_delete(_t_Str_1070, &(Bool){1});
        if (_t_Bool_1071) {
            U32 _t_U32_1058 = U32_sub(pos, start);
            (void)_t_U32_1058;
            Str *_t_Str_1059 = Str_substr(self, &start, &_t_U32_1058);
            (void)_t_Str_1059;
            ;
            Str *_t_Str_1060 = Str_clone(_t_Str_1059);
            (void)_t_Str_1060;
            Str_delete(_t_Str_1059, &(Bool){1});
            Vec_push(parts, _t_Str_1060);
            U32 _t_U32_1061 = Str_len(delim);
            (void)_t_U32_1061;
            U32 _t_U32_1062 = U32_add(pos, _t_U32_1061);
            (void)_t_U32_1062;
            ;
            start = _t_U32_1062;
            ;
            U32 _t_U32_1063 = U32_clone(&start);
            (void)_t_U32_1063;
            pos = _t_U32_1063;
            ;
        } else {
            U32 _t_U32_1064 = 1;
            (void)_t_U32_1064;
            U32 _t_U32_1065 = U32_add(pos, _t_U32_1064);
            (void)_t_U32_1065;
            ;
            pos = _t_U32_1065;
            ;
        }
        ;
    }
    ;
    U32 _t_U32_1077 = Str_len(self);
    (void)_t_U32_1077;
    U32 _t_U32_1078 = U32_sub(_t_U32_1077, start);
    (void)_t_U32_1078;
    ;
    Str *_t_Str_1079 = Str_substr(self, &start, &_t_U32_1078);
    (void)_t_Str_1079;
    ;
    ;
    Str *_t_Str_1080 = Str_clone(_t_Str_1079);
    (void)_t_Str_1080;
    Str_delete(_t_Str_1079, &(Bool){1});
    Vec_push(parts, _t_Str_1080);
    return parts;
}

U32 Str_size(void) {
    I64 _t_I64_1081 = 16;
    (void)_t_I64_1081;
    return _t_I64_1081;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_1082 = Str_cmp(a, b);
    (void)_t_I64_1082;
    I64 _t_I64_1083 = 0;
    (void)_t_I64_1083;
    Bool _t_Bool_1084 = I64_eq(_t_I64_1082, _t_I64_1083);
    (void)_t_Bool_1084;
    ;
    ;
    return _t_Bool_1084;
}

Bool Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_1085 = 0;
    (void)_t_I64_1085;
    I64 _t_I64_1086 = 1;
    (void)_t_I64_1086;
    I64 _t_I64_1087 = Str_cmp(a, b);
    (void)_t_I64_1087;
    I64 _t_I64_1088 = I64_sub(_t_I64_1085, _t_I64_1086);
    (void)_t_I64_1088;
    ;
    ;
    Bool _t_Bool_1089 = I64_eq(_t_I64_1087, _t_I64_1088);
    (void)_t_Bool_1089;
    ;
    ;
    return _t_Bool_1089;
}

Bool Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_1090 = Str_cmp(a, b);
    (void)_t_I64_1090;
    I64 _t_I64_1091 = 1;
    (void)_t_I64_1091;
    Bool _t_Bool_1092 = I64_eq(_t_I64_1090, _t_I64_1091);
    (void)_t_Bool_1092;
    ;
    ;
    return _t_Bool_1092;
}

Bool Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1093 = Str_eq(a, b);
    (void)_t_Bool_1093;
    Bool _t_Bool_1094 = not(_t_Bool_1093);
    (void)_t_Bool_1094;
    ;
    return _t_Bool_1094;
}

Bool Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1095 = Str_gt(a, b);
    (void)_t_Bool_1095;
    Bool _t_Bool_1096 = not(_t_Bool_1095);
    (void)_t_Bool_1096;
    ;
    return _t_Bool_1096;
}

Bool Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1097 = Str_lt(a, b);
    (void)_t_Bool_1097;
    Bool _t_Bool_1098 = not(_t_Bool_1097);
    (void)_t_Bool_1098;
    ;
    return _t_Bool_1098;
}

Str * U8_to_str(U8 * val) {
    (void)val;
    I64 _t_I64_2384 = U8_to_i64(DEREF(val));
    (void)_t_I64_2384;
    Str *_t_Str_2385 = I64_to_str(&_t_I64_2384);
    (void)_t_Str_2385;
    ;
    return _t_Str_2385;
}

void U8_inc(U8 * self) {
    (void)self;
    U8 _t_U8_2386 = 1;
    (void)_t_U8_2386;
    U8 _t_U8_2387 = U8_add(DEREF(self), _t_U8_2386);
    (void)_t_U8_2387;
    ;
    *self = _t_U8_2387;
    ;
}

void U8_dec(U8 * self) {
    (void)self;
    U8 _t_U8_2388 = 1;
    (void)_t_U8_2388;
    U8 _t_U8_2389 = U8_sub(DEREF(self), _t_U8_2388);
    (void)_t_U8_2389;
    ;
    *self = _t_U8_2389;
    ;
}

U8 * U8_unity(U8 * _self) {
    (void)_self;
    I64 _t_I64_2390 = 1;
    (void)_t_I64_2390;
    U8 _t_U8_2391 = I64_to_u8(_t_I64_2390);
    (void)_t_U8_2391;
    ;
    { U8 *_r = malloc(sizeof(U8)); *_r = _t_U8_2391; return _r; }
}

U64 U8_distance(void * a, void * b) {
    (void)a;
    (void)b;
    U8 *au = a;
    (void)au;
    U8 *bu = b;
    (void)bu;
    Bool _t_Bool_2394 = U8_lte(au, bu);
    (void)_t_Bool_2394;
    if (_t_Bool_2394) {
        U8 _t_U8_2392 = U8_sub(DEREF(bu), DEREF(au));
        (void)_t_U8_2392;
        U64 _t_U64_2393 = U8_to_u64(_t_U8_2392);
        (void)_t_U64_2393;
        ;
        ;
        return _t_U64_2393;
    }
    ;
    U8 _t_U8_2395 = U8_sub(DEREF(au), DEREF(bu));
    (void)_t_U8_2395;
    U64 _t_U64_2396 = U8_to_u64(_t_U8_2395);
    (void)_t_U64_2396;
    ;
    return _t_U64_2396;
}

void U8_delete(U8 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U8_size(void) {
    I64 _t_I64_2397 = 1;
    (void)_t_I64_2397;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2397; return _r; }
}

Bool U8_lt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2398 = 0;
    (void)_t_I64_2398;
    I64 _t_I64_2399 = 1;
    (void)_t_I64_2399;
    I64 _t_I64_2400 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2400;
    I64 _t_I64_2401 = I64_sub(_t_I64_2398, _t_I64_2399);
    (void)_t_I64_2401;
    ;
    ;
    Bool _t_Bool_2402 = I64_eq(_t_I64_2400, _t_I64_2401);
    (void)_t_Bool_2402;
    ;
    ;
    return _t_Bool_2402;
}

Bool U8_gt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2403 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2403;
    I64 _t_I64_2404 = 1;
    (void)_t_I64_2404;
    Bool _t_Bool_2405 = I64_eq(_t_I64_2403, _t_I64_2404);
    (void)_t_Bool_2405;
    ;
    ;
    return _t_Bool_2405;
}

Bool U8_neq(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2406 = U8_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2406;
    Bool _t_Bool_2407 = not(_t_Bool_2406);
    (void)_t_Bool_2407;
    ;
    return _t_Bool_2407;
}

Bool U8_lte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2408 = U8_gt(a, b);
    (void)_t_Bool_2408;
    Bool _t_Bool_2409 = not(_t_Bool_2408);
    (void)_t_Bool_2409;
    ;
    return _t_Bool_2409;
}

Bool U8_gte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2410 = U8_lt(a, b);
    (void)_t_Bool_2410;
    Bool _t_Bool_2411 = not(_t_Bool_2410);
    (void)_t_Bool_2411;
    ;
    return _t_Bool_2411;
}

Str * I16_to_str(I16 * val) {
    (void)val;
    I64 _t_I64_2412 = I16_to_i64(DEREF(val));
    (void)_t_I64_2412;
    Str *_t_Str_2413 = I64_to_str(&_t_I64_2412);
    (void)_t_Str_2413;
    ;
    return _t_Str_2413;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t_I16_2414 = 1;
    (void)_t_I16_2414;
    I16 _t_I16_2415 = I16_add(DEREF(self), _t_I16_2414);
    (void)_t_I16_2415;
    ;
    *self = _t_I16_2415;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t_I16_2416 = 1;
    (void)_t_I16_2416;
    I16 _t_I16_2417 = I16_sub(DEREF(self), _t_I16_2416);
    (void)_t_I16_2417;
    ;
    *self = _t_I16_2417;
    ;
}

I16 * I16_unity(I16 * _self) {
    (void)_self;
    I64 _t_I64_2418 = 1;
    (void)_t_I64_2418;
    I16 _t_I16_2419 = I64_to_i16(_t_I64_2418);
    (void)_t_I16_2419;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2419; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t_I64_2420 = 0;
    (void)_t_I64_2420;
    I64 _t_I64_2421 = I16_to_i64(DEREF(a));
    (void)_t_I64_2421;
    I64 _t_I64_2422 = I64_sub(_t_I64_2420, _t_I64_2421);
    (void)_t_I64_2422;
    ;
    ;
    I16 _t_I16_2423 = I64_to_i16(_t_I64_2422);
    (void)_t_I16_2423;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2423; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t_I64_2428 = I16_to_i64(DEREF(a));
    (void)_t_I64_2428;
    I64 _t_I64_2429 = 0;
    (void)_t_I64_2429;
    Bool _t_Bool_2430 = I64_lt(&_t_I64_2428, &_t_I64_2429);
    (void)_t_Bool_2430;
    ;
    ;
    if (_t_Bool_2430) {
        I64 _t_I64_2424 = 0;
        (void)_t_I64_2424;
        I64 _t_I64_2425 = I16_to_i64(DEREF(a));
        (void)_t_I64_2425;
        I64 _t_I64_2426 = I64_sub(_t_I64_2424, _t_I64_2425);
        (void)_t_I64_2426;
        ;
        ;
        I16 _t_I16_2427 = I64_to_i16(_t_I64_2426);
        (void)_t_I16_2427;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2427; return _r; }
    }
    ;
    I16 _t_I16_2431 = I16_clone(a);
    (void)_t_I16_2431;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2431; return _r; }
}

U64 I16_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I16 *au = a;
    (void)au;
    I16 *bu = b;
    (void)bu;
    Bool _t_Bool_2435 = I16_lte(au, bu);
    (void)_t_Bool_2435;
    if (_t_Bool_2435) {
        I16 _t_I16_2432 = I16_sub(DEREF(bu), DEREF(au));
        (void)_t_I16_2432;
        I64 _t_I64_2433 = I16_to_i64(_t_I16_2432);
        (void)_t_I64_2433;
        ;
        U64 _t_U64_2434 = I64_to_u64(_t_I64_2433);
        (void)_t_U64_2434;
        ;
        ;
        return _t_U64_2434;
    }
    ;
    I16 _t_I16_2436 = I16_sub(DEREF(au), DEREF(bu));
    (void)_t_I16_2436;
    I64 _t_I64_2437 = I16_to_i64(_t_I16_2436);
    (void)_t_I64_2437;
    ;
    U64 _t_U64_2438 = I64_to_u64(_t_I64_2437);
    (void)_t_U64_2438;
    ;
    return _t_U64_2438;
}

void I16_delete(I16 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I16_size(void) {
    I64 _t_I64_2439 = 2;
    (void)_t_I64_2439;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2439; return _r; }
}

Bool I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2440 = 0;
    (void)_t_I64_2440;
    I64 _t_I64_2441 = 1;
    (void)_t_I64_2441;
    I64 _t_I64_2442 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2442;
    I64 _t_I64_2443 = I64_sub(_t_I64_2440, _t_I64_2441);
    (void)_t_I64_2443;
    ;
    ;
    Bool _t_Bool_2444 = I64_eq(_t_I64_2442, _t_I64_2443);
    (void)_t_Bool_2444;
    ;
    ;
    return _t_Bool_2444;
}

Bool I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2445 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2445;
    I64 _t_I64_2446 = 1;
    (void)_t_I64_2446;
    Bool _t_Bool_2447 = I64_eq(_t_I64_2445, _t_I64_2446);
    (void)_t_Bool_2447;
    ;
    ;
    return _t_Bool_2447;
}

Bool I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2448 = I16_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2448;
    Bool _t_Bool_2449 = not(_t_Bool_2448);
    (void)_t_Bool_2449;
    ;
    return _t_Bool_2449;
}

Bool I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2450 = I16_gt(a, b);
    (void)_t_Bool_2450;
    Bool _t_Bool_2451 = not(_t_Bool_2450);
    (void)_t_Bool_2451;
    ;
    return _t_Bool_2451;
}

Bool I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2452 = I16_lt(a, b);
    (void)_t_Bool_2452;
    Bool _t_Bool_2453 = not(_t_Bool_2452);
    (void)_t_Bool_2453;
    ;
    return _t_Bool_2453;
}

Str * I32_to_str(I32 * val) {
    (void)val;
    I64 _t_I64_2454 = I32_to_i64(DEREF(val));
    (void)_t_I64_2454;
    Str *_t_Str_2455 = I64_to_str(&_t_I64_2454);
    (void)_t_Str_2455;
    ;
    return _t_Str_2455;
}

void I32_inc(I32 * self) {
    (void)self;
    I32 _t_I32_2456 = 1;
    (void)_t_I32_2456;
    I32 _t_I32_2457 = I32_add(DEREF(self), _t_I32_2456);
    (void)_t_I32_2457;
    ;
    *self = _t_I32_2457;
    ;
}

void I32_dec(I32 * self) {
    (void)self;
    I32 _t_I32_2458 = 1;
    (void)_t_I32_2458;
    I32 _t_I32_2459 = I32_sub(DEREF(self), _t_I32_2458);
    (void)_t_I32_2459;
    ;
    *self = _t_I32_2459;
    ;
}

I32 * I32_unity(I32 * _self) {
    (void)_self;
    I64 _t_I64_2460 = 1;
    (void)_t_I64_2460;
    I32 _t_I32_2461 = I64_to_i32(_t_I64_2460);
    (void)_t_I32_2461;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_2461; return _r; }
}

I32 * I32_neg(I32 * a) {
    (void)a;
    I64 _t_I64_2462 = 0;
    (void)_t_I64_2462;
    I64 _t_I64_2463 = I32_to_i64(DEREF(a));
    (void)_t_I64_2463;
    I64 _t_I64_2464 = I64_sub(_t_I64_2462, _t_I64_2463);
    (void)_t_I64_2464;
    ;
    ;
    I32 _t_I32_2465 = I64_to_i32(_t_I64_2464);
    (void)_t_I32_2465;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_2465; return _r; }
}

I32 * I32_abs(I32 * a) {
    (void)a;
    I64 _t_I64_2470 = I32_to_i64(DEREF(a));
    (void)_t_I64_2470;
    I64 _t_I64_2471 = 0;
    (void)_t_I64_2471;
    Bool _t_Bool_2472 = I64_lt(&_t_I64_2470, &_t_I64_2471);
    (void)_t_Bool_2472;
    ;
    ;
    if (_t_Bool_2472) {
        I64 _t_I64_2466 = 0;
        (void)_t_I64_2466;
        I64 _t_I64_2467 = I32_to_i64(DEREF(a));
        (void)_t_I64_2467;
        I64 _t_I64_2468 = I64_sub(_t_I64_2466, _t_I64_2467);
        (void)_t_I64_2468;
        ;
        ;
        I32 _t_I32_2469 = I64_to_i32(_t_I64_2468);
        (void)_t_I32_2469;
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_2469; return _r; }
    }
    ;
    I32 _t_I32_2473 = I32_clone(a);
    (void)_t_I32_2473;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_2473; return _r; }
}

U64 I32_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I32 *au = a;
    (void)au;
    I32 *bu = b;
    (void)bu;
    Bool _t_Bool_2477 = I32_lte(au, bu);
    (void)_t_Bool_2477;
    if (_t_Bool_2477) {
        I32 _t_I32_2474 = I32_sub(DEREF(bu), DEREF(au));
        (void)_t_I32_2474;
        I64 _t_I64_2475 = I32_to_i64(_t_I32_2474);
        (void)_t_I64_2475;
        ;
        U64 _t_U64_2476 = I64_to_u64(_t_I64_2475);
        (void)_t_U64_2476;
        ;
        ;
        return _t_U64_2476;
    }
    ;
    I32 _t_I32_2478 = I32_sub(DEREF(au), DEREF(bu));
    (void)_t_I32_2478;
    I64 _t_I64_2479 = I32_to_i64(_t_I32_2478);
    (void)_t_I64_2479;
    ;
    U64 _t_U64_2480 = I64_to_u64(_t_I64_2479);
    (void)_t_U64_2480;
    ;
    return _t_U64_2480;
}

void I32_delete(I32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I32_size(void) {
    I64 _t_I64_2481 = 4;
    (void)_t_I64_2481;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2481; return _r; }
}

Bool I32_lt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2482 = 0;
    (void)_t_I64_2482;
    I64 _t_I64_2483 = 1;
    (void)_t_I64_2483;
    I64 _t_I64_2484 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2484;
    I64 _t_I64_2485 = I64_sub(_t_I64_2482, _t_I64_2483);
    (void)_t_I64_2485;
    ;
    ;
    Bool _t_Bool_2486 = I64_eq(_t_I64_2484, _t_I64_2485);
    (void)_t_Bool_2486;
    ;
    ;
    return _t_Bool_2486;
}

Bool I32_gt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2487 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2487;
    I64 _t_I64_2488 = 1;
    (void)_t_I64_2488;
    Bool _t_Bool_2489 = I64_eq(_t_I64_2487, _t_I64_2488);
    (void)_t_Bool_2489;
    ;
    ;
    return _t_Bool_2489;
}

Bool I32_neq(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2490 = I32_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2490;
    Bool _t_Bool_2491 = not(_t_Bool_2490);
    (void)_t_Bool_2491;
    ;
    return _t_Bool_2491;
}

Bool I32_lte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2492 = I32_gt(a, b);
    (void)_t_Bool_2492;
    Bool _t_Bool_2493 = not(_t_Bool_2492);
    (void)_t_Bool_2493;
    ;
    return _t_Bool_2493;
}

Bool I32_gte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2494 = I32_lt(a, b);
    (void)_t_Bool_2494;
    Bool _t_Bool_2495 = not(_t_Bool_2494);
    (void)_t_Bool_2495;
    ;
    return _t_Bool_2495;
}

F32 * F32_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func F32_from_i64_ext */
    F32 _t_F32_2496 = F32_from_i64_ext(val);
    (void)_t_F32_2496;
    { F32 *_r = malloc(sizeof(F32)); *_r = _t_F32_2496; return _r; }
}

void F32_delete(F32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * F32_size(void) {
    I64 _t_I64_2497 = 4;
    (void)_t_I64_2497;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2497; return _r; }
}

Bool F32_lt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2498 = 0;
    (void)_t_I64_2498;
    I64 _t_I64_2499 = 1;
    (void)_t_I64_2499;
    I64 _t_I64_2500 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2500;
    I64 _t_I64_2501 = I64_sub(_t_I64_2498, _t_I64_2499);
    (void)_t_I64_2501;
    ;
    ;
    Bool _t_Bool_2502 = I64_eq(_t_I64_2500, _t_I64_2501);
    (void)_t_Bool_2502;
    ;
    ;
    return _t_Bool_2502;
}

Bool F32_gt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2503 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2503;
    I64 _t_I64_2504 = 1;
    (void)_t_I64_2504;
    Bool _t_Bool_2505 = I64_eq(_t_I64_2503, _t_I64_2504);
    (void)_t_Bool_2505;
    ;
    ;
    return _t_Bool_2505;
}

Bool F32_neq(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2506 = F32_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2506;
    Bool _t_Bool_2507 = not(_t_Bool_2506);
    (void)_t_Bool_2507;
    ;
    return _t_Bool_2507;
}

Bool F32_lte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2508 = F32_gt(a, b);
    (void)_t_Bool_2508;
    Bool _t_Bool_2509 = not(_t_Bool_2508);
    (void)_t_Bool_2509;
    ;
    return _t_Bool_2509;
}

Bool F32_gte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2510 = F32_lt(a, b);
    (void)_t_Bool_2510;
    Bool _t_Bool_2511 = not(_t_Bool_2510);
    (void)_t_Bool_2511;
    ;
    return _t_Bool_2511;
}

Str * U32_to_str(U32 * val) {
    (void)val;
    I64 _t_I64_2512 = U32_to_i64(DEREF(val));
    (void)_t_I64_2512;
    Str *_t_Str_2513 = I64_to_str(&_t_I64_2512);
    (void)_t_Str_2513;
    ;
    return _t_Str_2513;
}

void U32_inc(U32 * self) {
    (void)self;
    U32 _t_U32_2514 = 1;
    (void)_t_U32_2514;
    U32 _t_U32_2515 = U32_add(DEREF(self), _t_U32_2514);
    (void)_t_U32_2515;
    ;
    *self = _t_U32_2515;
    ;
}

void U32_dec(U32 * self) {
    (void)self;
    U32 _t_U32_2516 = 1;
    (void)_t_U32_2516;
    U32 _t_U32_2517 = U32_sub(DEREF(self), _t_U32_2516);
    (void)_t_U32_2517;
    ;
    *self = _t_U32_2517;
    ;
}

U32 * U32_unity(U32 * _self) {
    (void)_self;
    I64 _t_I64_2518 = 1;
    (void)_t_I64_2518;
    U32 _t_U32_2519 = I64_to_u32(_t_I64_2518);
    (void)_t_U32_2519;
    ;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_U32_2519; return _r; }
}

U64 U32_distance(void * a, void * b) {
    (void)a;
    (void)b;
    U32 *au = a;
    (void)au;
    U32 *bu = b;
    (void)bu;
    Bool _t_Bool_2523 = U32_lte(au, bu);
    (void)_t_Bool_2523;
    if (_t_Bool_2523) {
        U32 _t_U32_2520 = U32_sub(DEREF(bu), DEREF(au));
        (void)_t_U32_2520;
        I64 _t_I64_2521 = U32_to_i64(_t_U32_2520);
        (void)_t_I64_2521;
        ;
        U64 _t_U64_2522 = I64_to_u64(_t_I64_2521);
        (void)_t_U64_2522;
        ;
        ;
        return _t_U64_2522;
    }
    ;
    U32 _t_U32_2524 = U32_sub(DEREF(au), DEREF(bu));
    (void)_t_U32_2524;
    I64 _t_I64_2525 = U32_to_i64(_t_U32_2524);
    (void)_t_I64_2525;
    ;
    U64 _t_U64_2526 = I64_to_u64(_t_I64_2525);
    (void)_t_U64_2526;
    ;
    return _t_U64_2526;
}

void U32_delete(U32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U32_size(void) {
    I64 _t_I64_2527 = 4;
    (void)_t_I64_2527;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2527; return _r; }
}

Bool U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2528 = 0;
    (void)_t_I64_2528;
    I64 _t_I64_2529 = 1;
    (void)_t_I64_2529;
    I64 _t_I64_2530 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2530;
    I64 _t_I64_2531 = I64_sub(_t_I64_2528, _t_I64_2529);
    (void)_t_I64_2531;
    ;
    ;
    Bool _t_Bool_2532 = I64_eq(_t_I64_2530, _t_I64_2531);
    (void)_t_Bool_2532;
    ;
    ;
    return _t_Bool_2532;
}

Bool U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2533 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2533;
    I64 _t_I64_2534 = 1;
    (void)_t_I64_2534;
    Bool _t_Bool_2535 = I64_eq(_t_I64_2533, _t_I64_2534);
    (void)_t_Bool_2535;
    ;
    ;
    return _t_Bool_2535;
}

Bool U32_neq(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2536 = U32_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2536;
    Bool _t_Bool_2537 = not(_t_Bool_2536);
    (void)_t_Bool_2537;
    ;
    return _t_Bool_2537;
}

Bool U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2538 = U32_gt(a, b);
    (void)_t_Bool_2538;
    Bool _t_Bool_2539 = not(_t_Bool_2538);
    (void)_t_Bool_2539;
    ;
    return _t_Bool_2539;
}

Bool U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2540 = U32_lt(a, b);
    (void)_t_Bool_2540;
    Bool _t_Bool_2541 = not(_t_Bool_2540);
    (void)_t_Bool_2541;
    ;
    return _t_Bool_2541;
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t_Str_2542 = U64_to_str_ext(val);
    (void)_t_Str_2542;
    return _t_Str_2542;
}

U64 * U64_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func U64_from_i64_ext */
    U64 _t_U64_2543 = U64_from_i64_ext(val);
    (void)_t_U64_2543;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t_U64_2543; return _r; }
}

void U64_inc(U64 * self) {
    (void)self;
    U64 _t_U64_2544 = 1;
    (void)_t_U64_2544;
    U64 _t_U64_2545 = U64_add(DEREF(self), _t_U64_2544);
    (void)_t_U64_2545;
    ;
    *self = _t_U64_2545;
    ;
}

void U64_dec(U64 * self) {
    (void)self;
    U64 _t_U64_2546 = 1;
    (void)_t_U64_2546;
    U64 _t_U64_2547 = U64_sub(DEREF(self), _t_U64_2546);
    (void)_t_U64_2547;
    ;
    *self = _t_U64_2547;
    ;
}

U64 * U64_unity(U64 * _self) {
    (void)_self;
    I64 _t_I64_2548 = 1;
    (void)_t_I64_2548;
    U64 _t_U64_2549 = I64_to_u64(_t_I64_2548);
    (void)_t_U64_2549;
    ;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t_U64_2549; return _r; }
}

U64 U64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    U64 *au = a;
    (void)au;
    U64 *bu = b;
    (void)bu;
    Bool _t_Bool_2551 = U64_lte(au, bu);
    (void)_t_Bool_2551;
    if (_t_Bool_2551) {
        U64 _t_U64_2550 = U64_sub(DEREF(bu), DEREF(au));
        (void)_t_U64_2550;
        ;
        return _t_U64_2550;
    }
    ;
    U64 _t_U64_2552 = U64_sub(DEREF(au), DEREF(bu));
    (void)_t_U64_2552;
    return _t_U64_2552;
}

void U64_delete(U64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U64_size(void) {
    I64 _t_I64_2553 = 8;
    (void)_t_I64_2553;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2553; return _r; }
}

Bool U64_lt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2554 = 0;
    (void)_t_I64_2554;
    I64 _t_I64_2555 = 1;
    (void)_t_I64_2555;
    I64 _t_I64_2556 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2556;
    I64 _t_I64_2557 = I64_sub(_t_I64_2554, _t_I64_2555);
    (void)_t_I64_2557;
    ;
    ;
    Bool _t_Bool_2558 = I64_eq(_t_I64_2556, _t_I64_2557);
    (void)_t_Bool_2558;
    ;
    ;
    return _t_Bool_2558;
}

Bool U64_gt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2559 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2559;
    I64 _t_I64_2560 = 1;
    (void)_t_I64_2560;
    Bool _t_Bool_2561 = I64_eq(_t_I64_2559, _t_I64_2560);
    (void)_t_Bool_2561;
    ;
    ;
    return _t_Bool_2561;
}

Bool U64_neq(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2562 = U64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2562;
    Bool _t_Bool_2563 = not(_t_Bool_2562);
    (void)_t_Bool_2563;
    ;
    return _t_Bool_2563;
}

Bool U64_lte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2564 = U64_gt(a, b);
    (void)_t_Bool_2564;
    Bool _t_Bool_2565 = not(_t_Bool_2564);
    (void)_t_Bool_2565;
    ;
    return _t_Bool_2565;
}

Bool U64_gte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2566 = U64_lt(a, b);
    (void)_t_Bool_2566;
    Bool _t_Bool_2567 = not(_t_Bool_2566);
    (void)_t_Bool_2567;
    ;
    return _t_Bool_2567;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_2604 = 0;
    (void)_t_I64_2604;
    Bool _t_Bool_2605 = I64_eq(DEREF(val), _t_I64_2604);
    (void)_t_Bool_2605;
    ;
    if (_t_Bool_2605) {
        U64 _t_U64_2568 = 2;
        (void)_t_U64_2568;
        void * buf = malloc(_t_U64_2568);
        (void)buf;
        ;
        I64 _t_I64_2569 = 48;
        (void)_t_I64_2569;
        U64 _t_U64_2570 = 1;
        (void)_t_U64_2570;
        memcpy(buf, &_t_I64_2569, _t_U64_2570);
        ;
        ;
        U64 _t_U64_2571 = 1;
        (void)_t_U64_2571;
        void *_t_v_2572 = ptr_add(buf, _t_U64_2571);
        (void)_t_v_2572;
        I32 _t_I32_2573 = 0;
        (void)_t_I32_2573;
        U64 _t_U64_2574 = 1;
        (void)_t_U64_2574;
        memset(_t_v_2572, _t_I32_2573, _t_U64_2574);
        ;
        ;
        ;
        I64 _t_I64_2575 = 1;
        (void)_t_I64_2575;
        I64 _t_I64_2576 = 1;
        (void)_t_I64_2576;
        Str *_t_Str_2577 = malloc(sizeof(Str));
        _t_Str_2577->c_str = buf;
        _t_Str_2577->count = _t_I64_2575;
        _t_Str_2577->cap = _t_I64_2576;
        (void)_t_Str_2577;
        ;
        ;
        ;
        return _t_Str_2577;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t_I64_2606 = 0;
    (void)_t_I64_2606;
    Bool _t_Bool_2607 = I64_lt(val, &_t_I64_2606);
    (void)_t_Bool_2607;
    ;
    if (_t_Bool_2607) {
        Bool _t_Bool_2578 = 1;
        (void)_t_Bool_2578;
        is_neg = _t_Bool_2578;
        ;
        I64 _t_I64_2579 = 0;
        (void)_t_I64_2579;
        I64 _t_I64_2580 = I64_sub(_t_I64_2579, DEREF(val));
        (void)_t_I64_2580;
        ;
        v = _t_I64_2580;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&v);
    (void)tmp;
    while (1) {
        I64 _t_I64_2582 = 0;
        (void)_t_I64_2582;
        Bool _wcond_Bool_2581 = I64_gt(&tmp, &_t_I64_2582);
        (void)_wcond_Bool_2581;
        ;
        if (_wcond_Bool_2581) {
        } else {
            ;
            break;
        }
        ;
        U64 _t_U64_2583 = 1;
        (void)_t_U64_2583;
        U64 _t_U64_2584 = U64_add(ndigits, _t_U64_2583);
        (void)_t_U64_2584;
        ;
        ndigits = _t_U64_2584;
        ;
        I64 _t_I64_2585 = 10;
        (void)_t_I64_2585;
        I64 _t_I64_2586 = I64_div(tmp, _t_I64_2585);
        (void)_t_I64_2586;
        ;
        tmp = _t_I64_2586;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    (void)total;
    ;
    if (is_neg) {
        U64 _t_U64_2587 = 1;
        (void)_t_U64_2587;
        U64 _t_U64_2588 = U64_add(total, _t_U64_2587);
        (void)_t_U64_2588;
        ;
        total = _t_U64_2588;
        ;
    }
    U64 _t_U64_2608 = 1;
    (void)_t_U64_2608;
    U64 _t_U64_2609 = U64_add(total, _t_U64_2608);
    (void)_t_U64_2609;
    ;
    void * buf = malloc(_t_U64_2609);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t_I64_2589 = 45;
        (void)_t_I64_2589;
        U64 _t_U64_2590 = 1;
        (void)_t_U64_2590;
        memcpy(buf, &_t_I64_2589, _t_U64_2590);
        ;
        ;
    }
    ;
    U64 _t_U64_2610 = 1;
    (void)_t_U64_2610;
    U64 i = U64_sub(total, _t_U64_2610);
    (void)i;
    ;
    while (1) {
        I64 _t_I64_2592 = 0;
        (void)_t_I64_2592;
        Bool _wcond_Bool_2591 = I64_gt(&v, &_t_I64_2592);
        (void)_wcond_Bool_2591;
        ;
        if (_wcond_Bool_2591) {
        } else {
            ;
            break;
        }
        ;
        I64 _t_I64_2593 = 10;
        (void)_t_I64_2593;
        I64 _t_I64_2594 = I64_mod(v, _t_I64_2593);
        (void)_t_I64_2594;
        ;
        I64 _t_I64_2595 = 48;
        (void)_t_I64_2595;
        I64 _t_I64_2596 = I64_add(_t_I64_2594, _t_I64_2595);
        (void)_t_I64_2596;
        ;
        ;
        void *_t_v_2597 = ptr_add(buf, i);
        (void)_t_v_2597;
        U8 _t_U8_2598 = I64_to_u8(_t_I64_2596);
        (void)_t_U8_2598;
        ;
        U64 _t_U64_2599 = 1;
        (void)_t_U64_2599;
        memcpy(_t_v_2597, &_t_U8_2598, _t_U64_2599);
        ;
        ;
        I64 _t_I64_2600 = 10;
        (void)_t_I64_2600;
        I64 _t_I64_2601 = I64_div(v, _t_I64_2600);
        (void)_t_I64_2601;
        ;
        v = _t_I64_2601;
        ;
        U64 _t_U64_2602 = 1;
        (void)_t_U64_2602;
        U64 _t_U64_2603 = U64_sub(i, _t_U64_2602);
        (void)_t_U64_2603;
        ;
        i = _t_U64_2603;
        ;
    }
    ;
    ;
    void *_t_v_2611 = ptr_add(buf, total);
    (void)_t_v_2611;
    I32 _t_I32_2612 = 0;
    (void)_t_I32_2612;
    U64 _t_U64_2613 = 1;
    (void)_t_U64_2613;
    memset(_t_v_2611, _t_I32_2612, _t_U64_2613);
    ;
    ;
    Str *_t_Str_2614 = malloc(sizeof(Str));
    _t_Str_2614->c_str = buf;
    _t_Str_2614->count = total;
    _t_Str_2614->cap = total;
    (void)_t_Str_2614;
    ;
    return _t_Str_2614;
}

U32 I64_to_usize(I64 val) {
    (void)val;
    U32 _t_U32_2615 = I64_to_u32(val);
    (void)_t_U32_2615;
    return _t_U32_2615;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t_I64_2616 = 1;
    (void)_t_I64_2616;
    I64 _t_I64_2617 = I64_add(DEREF(self), _t_I64_2616);
    (void)_t_I64_2617;
    ;
    *self = _t_I64_2617;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t_I64_2618 = 1;
    (void)_t_I64_2618;
    I64 _t_I64_2619 = I64_sub(DEREF(self), _t_I64_2618);
    (void)_t_I64_2619;
    ;
    *self = _t_I64_2619;
    ;
}

I64 * I64_unity(I64 * _self) {
    (void)_self;
    I64 _t_I64_2620 = 1;
    (void)_t_I64_2620;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2620; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t_I64_2621 = 0;
    (void)_t_I64_2621;
    I64 _t_I64_2622 = I64_sub(_t_I64_2621, DEREF(a));
    (void)_t_I64_2622;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2622; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t_I64_2625 = 0;
    (void)_t_I64_2625;
    Bool _t_Bool_2626 = I64_lt(a, &_t_I64_2625);
    (void)_t_Bool_2626;
    ;
    if (_t_Bool_2626) {
        I64 _t_I64_2623 = 0;
        (void)_t_I64_2623;
        I64 _t_I64_2624 = I64_sub(_t_I64_2623, DEREF(a));
        (void)_t_I64_2624;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2624; return _r; }
    }
    ;
    I64 _t_I64_2627 = I64_clone(a);
    (void)_t_I64_2627;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2627; return _r; }
}

U64 I64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I64 *au = a;
    (void)au;
    I64 *bu = b;
    (void)bu;
    Bool _t_Bool_2630 = I64_lte(au, bu);
    (void)_t_Bool_2630;
    if (_t_Bool_2630) {
        I64 _t_I64_2628 = I64_sub(DEREF(bu), DEREF(au));
        (void)_t_I64_2628;
        U64 _t_U64_2629 = I64_to_u64(_t_I64_2628);
        (void)_t_U64_2629;
        ;
        ;
        return _t_U64_2629;
    }
    ;
    I64 _t_I64_2631 = I64_sub(DEREF(au), DEREF(bu));
    (void)_t_I64_2631;
    U64 _t_U64_2632 = I64_to_u64(_t_I64_2631);
    (void)_t_U64_2632;
    ;
    return _t_U64_2632;
}

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_2633 = 8;
    (void)_t_I64_2633;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2633; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2634 = 0;
    (void)_t_I64_2634;
    I64 _t_I64_2635 = 1;
    (void)_t_I64_2635;
    I64 _t_I64_2636 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2636;
    I64 _t_I64_2637 = I64_sub(_t_I64_2634, _t_I64_2635);
    (void)_t_I64_2637;
    ;
    ;
    Bool _t_Bool_2638 = I64_eq(_t_I64_2636, _t_I64_2637);
    (void)_t_Bool_2638;
    ;
    ;
    return _t_Bool_2638;
}

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2639 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2639;
    I64 _t_I64_2640 = 1;
    (void)_t_I64_2640;
    Bool _t_Bool_2641 = I64_eq(_t_I64_2639, _t_I64_2640);
    (void)_t_Bool_2641;
    ;
    ;
    return _t_Bool_2641;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2642 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2642;
    Bool _t_Bool_2643 = not(_t_Bool_2642);
    (void)_t_Bool_2643;
    ;
    return _t_Bool_2643;
}

Bool I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2644 = I64_gt(a, b);
    (void)_t_Bool_2644;
    Bool _t_Bool_2645 = not(_t_Bool_2644);
    (void)_t_Bool_2645;
    ;
    return _t_Bool_2645;
}

Bool I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2646 = I64_lt(a, b);
    (void)_t_Bool_2646;
    Bool _t_Bool_2647 = not(_t_Bool_2646);
    (void)_t_Bool_2647;
    ;
    return _t_Bool_2647;
}

Str * Bool_to_str(Bool * b) {
    (void)b;
    if (DEREF(b)) {
        Str *_t_Str_2657 = Str_lit("true", 4ULL);
        (void)_t_Str_2657;
        return _t_Str_2657;
    } else {
        Str *_t_Str_2658 = Str_lit("false", 5ULL);
        (void)_t_Str_2658;
        return _t_Str_2658;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2663 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2663;
    if (_t_Bool_2663) {
        I64 _t_I64_2659 = 0;
        (void)_t_I64_2659;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2659; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_2660 = 0;
        (void)_t_I64_2660;
        I64 _t_I64_2661 = 1;
        (void)_t_I64_2661;
        I64 _t_I64_2662 = I64_sub(_t_I64_2660, _t_I64_2661);
        (void)_t_I64_2662;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2662; return _r; }
    }
    I64 _t_I64_2664 = 1;
    (void)_t_I64_2664;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2664; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_2665 = 1;
    (void)_t_I64_2665;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2665; return _r; }
}

Bool Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2666 = 0;
    (void)_t_I64_2666;
    I64 _t_I64_2667 = 1;
    (void)_t_I64_2667;
    I64 _t_I64_2668; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_2668 = *_hp; free(_hp); }
    (void)_t_I64_2668;
    I64 _t_I64_2669 = I64_sub(_t_I64_2666, _t_I64_2667);
    (void)_t_I64_2669;
    ;
    ;
    Bool _t_Bool_2670 = I64_eq(_t_I64_2668, _t_I64_2669);
    (void)_t_Bool_2670;
    ;
    ;
    return _t_Bool_2670;
}

Bool Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2671; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_2671 = *_hp; free(_hp); }
    (void)_t_I64_2671;
    I64 _t_I64_2672 = 1;
    (void)_t_I64_2672;
    Bool _t_Bool_2673 = I64_eq(_t_I64_2671, _t_I64_2672);
    (void)_t_Bool_2673;
    ;
    ;
    return _t_Bool_2673;
}

Bool Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2674 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2674;
    Bool _t_Bool_2675 = not(_t_Bool_2674);
    (void)_t_Bool_2675;
    ;
    return _t_Bool_2675;
}

Bool Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2676 = Bool_gt(a, b);
    (void)_t_Bool_2676;
    Bool _t_Bool_2677 = not(_t_Bool_2676);
    (void)_t_Bool_2677;
    ;
    return _t_Bool_2677;
}

Bool Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2678 = Bool_lt(a, b);
    (void)_t_Bool_2678;
    Bool _t_Bool_2679 = not(_t_Bool_2678);
    (void)_t_Bool_2679;
    ;
    return _t_Bool_2679;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_2680 = 8;
    (void)_t_I64_2680;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2680; return _r; }
}

void * default_clone(void * v) {
    (void)v;
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2683 = parts;
        (void)_fc_Array_2683;
        U32 _fi_USize_2683 = 0;
        (void)_fi_USize_2683;
        while (1) {
            U32 _t_U32_2685; { U32 *_hp = (U32 *)Array_len(_fc_Array_2683); _t_U32_2685 = *_hp; free(_hp); }
            (void)_t_U32_2685;
            Bool _wcond_Bool_2684 = U32_lt(&_fi_USize_2683, &_t_U32_2685);
            (void)_wcond_Bool_2684;
            ;
            if (_wcond_Bool_2684) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2683, &_fi_USize_2683);
            (void)s;
            U32 _t_U32_2686 = 1;
            (void)_t_U32_2686;
            U32 _t_U32_2687 = U32_add(_fi_USize_2683, _t_U32_2686);
            (void)_t_U32_2687;
            ;
            _fi_USize_2683 = _t_U32_2687;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2734 = Str_lit("Str", 3ULL);
    (void)_t_Str_2734;
    U32 _t_U32_2735 = 16;
    (void)_t_U32_2735;
    U32 _t_U32_2736 = 3;
    (void)_t_U32_2736;
    Array *_va_Array_81 = Array_new(_t_Str_2734, &_t_U32_2735, &_t_U32_2736);
    (void)_va_Array_81;
    Str_delete(_t_Str_2734, &(Bool){1});
    ;
    ;
    U32 _t_U32_2737 = 0;
    (void)_t_U32_2737;
    Str *_t_Str_2738 = Str_clone(loc_str);
    (void)_t_Str_2738;
    Array_set(_va_Array_81, &_t_U32_2737, _t_Str_2738);
    ;
    U32 _t_U32_2739 = 1;
    (void)_t_U32_2739;
    Str *_t_Str_2740 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2740;
    Array_set(_va_Array_81, &_t_U32_2739, _t_Str_2740);
    ;
    U32 _t_U32_2741 = 2;
    (void)_t_U32_2741;
    Str *_t_Str_2742 = format(parts);
    (void)_t_Str_2742;
    Array_set(_va_Array_81, &_t_U32_2741, _t_Str_2742);
    ;
    println(_va_Array_81);
    I64 _t_I64_2743 = 1;
    (void)_t_I64_2743;
    exit(_t_I64_2743);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2761 = not(DEREF(cond));
    (void)_t_Bool_2761;
    if (_t_Bool_2761) {
        Str *_t_Str_2756 = Str_lit("Str", 3ULL);
        (void)_t_Str_2756;
        U32 _t_U32_2757 = 16;
        (void)_t_U32_2757;
        U32 _t_U32_2758 = 1;
        (void)_t_U32_2758;
        Array *_va_Array_84 = Array_new(_t_Str_2756, &_t_U32_2757, &_t_U32_2758);
        (void)_va_Array_84;
        Str_delete(_t_Str_2756, &(Bool){1});
        ;
        ;
        U32 _t_U32_2759 = 0;
        (void)_t_U32_2759;
        Str *_t_Str_2760 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2760;
        Array_set(_va_Array_84, &_t_U32_2759, _t_Str_2760);
        ;
        panic(loc_str, _va_Array_84);
    }
    ;
    Bool _t_Bool_2762 = 1;
    (void)_t_Bool_2762;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2762; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2784 = I64_neq(a, b);
    (void)_t_Bool_2784;
    if (_t_Bool_2784) {
        Str *_t_Str_2771 = Str_lit("Str", 3ULL);
        (void)_t_Str_2771;
        U32 _t_U32_2772 = 16;
        (void)_t_U32_2772;
        U32 _t_U32_2773 = 5;
        (void)_t_U32_2773;
        Array *_va_Array_86 = Array_new(_t_Str_2771, &_t_U32_2772, &_t_U32_2773);
        (void)_va_Array_86;
        Str_delete(_t_Str_2771, &(Bool){1});
        ;
        ;
        U32 _t_U32_2774 = 0;
        (void)_t_U32_2774;
        Str *_t_Str_2775 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2775;
        Array_set(_va_Array_86, &_t_U32_2774, _t_Str_2775);
        ;
        U32 _t_U32_2776 = 1;
        (void)_t_U32_2776;
        Str *_t_Str_2777 = I64_to_str(a);
        (void)_t_Str_2777;
        Array_set(_va_Array_86, &_t_U32_2776, _t_Str_2777);
        ;
        U32 _t_U32_2778 = 2;
        (void)_t_U32_2778;
        Str *_t_Str_2779 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2779;
        Array_set(_va_Array_86, &_t_U32_2778, _t_Str_2779);
        ;
        U32 _t_U32_2780 = 3;
        (void)_t_U32_2780;
        Str *_t_Str_2781 = I64_to_str(b);
        (void)_t_Str_2781;
        Array_set(_va_Array_86, &_t_U32_2780, _t_Str_2781);
        ;
        U32 _t_U32_2782 = 4;
        (void)_t_U32_2782;
        Str *_t_Str_2783 = Str_lit("'", 1ULL);
        (void)_t_Str_2783;
        Array_set(_va_Array_86, &_t_U32_2782, _t_Str_2783);
        ;
        panic(loc_str, _va_Array_86);
    }
    ;
}

void test_simple_add(void) {
    I64 _t_I64_2885 = 1;
    (void)_t_I64_2885;
    I64 _t_I64_2886 = 2;
    (void)_t_I64_2886;
    I64 result = 3;
    (void)result;
    ;
    ;
    Str *_t_Str_2887 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_2887;
    I64 _t_I64_2888 = 3;
    (void)_t_I64_2888;
    assert_eq(_t_Str_2887, &result, &_t_I64_2888);
    ;
    Str_delete(_t_Str_2887, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 _t_I64_2889 = 1;
    (void)_t_I64_2889;
    I64 _t_I64_2890 = 2;
    (void)_t_I64_2890;
    I64 _t_I64_2891 = 10;
    (void)_t_I64_2891;
    I64 _t_I64_2892 = 5;
    (void)_t_I64_2892;
    I64 _t_I64_2893 = 3;
    (void)_t_I64_2893;
    ;
    ;
    I64 _t_I64_2894 = 5;
    (void)_t_I64_2894;
    ;
    ;
    I64 result = 15;
    (void)result;
    ;
    ;
    Str *_t_Str_2895 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_2895;
    I64 _t_I64_2896 = 15;
    (void)_t_I64_2896;
    assert_eq(_t_Str_2895, &result, &_t_I64_2896);
    ;
    Str_delete(_t_Str_2895, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 _t_I64_2897 = 2;
    (void)_t_I64_2897;
    I64 _t_I64_2898 = 3;
    (void)_t_I64_2898;
    I64 _t_I64_2899 = 4;
    (void)_t_I64_2899;
    I64 _t_I64_2900 = 5;
    (void)_t_I64_2900;
    I64 _t_I64_2901 = 6;
    (void)_t_I64_2901;
    ;
    ;
    I64 _t_I64_2902 = 20;
    (void)_t_I64_2902;
    ;
    ;
    I64 result = 26;
    (void)result;
    ;
    ;
    Str *_t_Str_2903 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_2903;
    I64 _t_I64_2904 = 26;
    (void)_t_I64_2904;
    assert_eq(_t_Str_2903, &result, &_t_I64_2904);
    ;
    Str_delete(_t_Str_2903, &(Bool){1});
    ;
}

Str * poem(I64 * depth, Str * current, Str * s1, Str * s2) {
    (void)depth;
    (void)current;
    (void)s1;
    (void)s2;
    I64 _t_I64_2912 = 4;
    (void)_t_I64_2912;
    Bool _t_Bool_2913 = I64_eq(DEREF(depth), _t_I64_2912);
    (void)_t_Bool_2913;
    ;
    if (_t_Bool_2913) {
        Str *_t_Str_2905 = Str_lit("\n", 2ULL);
        (void)_t_Str_2905;
        Str *_t_Str_2906 = Str_concat(current, _t_Str_2905);
        (void)_t_Str_2906;
        Str_delete(_t_Str_2905, &(Bool){1});
        ;
        return _t_Str_2906;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    I64 _t_I64_2914 = 1;
    (void)_t_I64_2914;
    I64 _t_I64_2915 = I64_add(DEREF(depth), _t_I64_2914);
    (void)_t_I64_2915;
    ;
    Str *_t_Str_2916 = Str_concat(current, s1);
    (void)_t_Str_2916;
    Str *_t_Str_2917 = poem(&_t_I64_2915, _t_Str_2916, s1, s2);
    (void)_t_Str_2917;
    ;
    Str_delete(_t_Str_2916, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2917); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2917, &(Bool){1});
    I64 _t_I64_2918 = 1;
    (void)_t_I64_2918;
    I64 _t_I64_2919 = I64_add(DEREF(depth), _t_I64_2918);
    (void)_t_I64_2919;
    ;
    Str *_t_Str_2920 = Str_concat(current, s2);
    (void)_t_Str_2920;
    Str *_t_Str_2921 = poem(&_t_I64_2919, _t_Str_2920, s1, s2);
    (void)_t_Str_2921;
    ;
    Str_delete(_t_Str_2920, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2921); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2921, &(Bool){1});
    I64 _t_I64_2922 = 2;
    (void)_t_I64_2922;
    Bool _t_Bool_2923 = I64_eq(DEREF(depth), _t_I64_2922);
    (void)_t_Bool_2923;
    ;
    if (_t_Bool_2923) {
        I64 _t_I64_2907 = 1;
        (void)_t_I64_2907;
        Str *_t_Str_2908 = Str_lit("lei", 3ULL);
        (void)_t_Str_2908;
        I64 _t_I64_2909 = I64_add(DEREF(depth), _t_I64_2907);
        (void)_t_I64_2909;
        ;
        Str *_t_Str_2910 = Str_concat(current, _t_Str_2908);
        (void)_t_Str_2910;
        Str_delete(_t_Str_2908, &(Bool){1});
        Str *_t_Str_2911 = poem(&_t_I64_2909, _t_Str_2910, s1, s2);
        (void)_t_Str_2911;
        ;
        Str_delete(_t_Str_2910, &(Bool){1});
        result = Str_concat(result, _t_Str_2911);
        Str_delete(_t_Str_2911, &(Bool){1});
    }
    ;
    return result;
}

Str * make_poem(Str * s1, Str * s2) {
    (void)s1;
    (void)s2;
    I64 _t_I64_2924 = 0;
    (void)_t_I64_2924;
    Str *_t_Str_2925 = Str_lit("", 0ULL);
    (void)_t_Str_2925;
    Str *_t_Str_2926 = poem(&_t_I64_2924, _t_Str_2925, s1, s2);
    (void)_t_Str_2926;
    ;
    Str_delete(_t_Str_2925, &(Bool){1});
    return _t_Str_2926;
}

void test_lolalalo(void) {
    Str *_t_Str_2927 = Str_lit("lo", 2ULL);
    (void)_t_Str_2927;
    Str *_t_Str_2928 = Str_lit("la", 2ULL);
    (void)_t_Str_2928;
    Str *lo_la = make_poem(_t_Str_2927, _t_Str_2928);
    (void)lo_la;
    Str_delete(_t_Str_2927, &(Bool){1});
    Str_delete(_t_Str_2928, &(Bool){1});
    Str *_t_Str_2929 = Str_lit("la", 2ULL);
    (void)_t_Str_2929;
    Str *_t_Str_2930 = Str_lit("lo", 2ULL);
    (void)_t_Str_2930;
    Str *la_lo = make_poem(_t_Str_2929, _t_Str_2930);
    (void)la_lo;
    Str_delete(_t_Str_2929, &(Bool){1});
    Str_delete(_t_Str_2930, &(Bool){1});
    Str *_t_Str_2931 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_2931;
    Str *_t_Str_2932 = Str_lit("src/test/constfold.til:56:12", 28ULL);
    (void)_t_Str_2932;
    Bool _t_Bool_2933 = Str_contains(lo_la, _t_Str_2931);
    (void)_t_Bool_2933;
    Str_delete(_t_Str_2931, &(Bool){1});
    Bool _t_Bool_2934; { Bool *_hp = (Bool *)assert(_t_Str_2932, &_t_Bool_2933); _t_Bool_2934 = *_hp; free(_hp); }
    (void)_t_Bool_2934;
    ;
    ;
    Str_delete(_t_Str_2932, &(Bool){1});
    Str *_t_Str_2935 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_2935;
    Str *_t_Str_2936 = Str_lit("src/test/constfold.til:57:12", 28ULL);
    (void)_t_Str_2936;
    Bool _t_Bool_2937 = Str_contains(la_lo, _t_Str_2935);
    (void)_t_Bool_2937;
    Str_delete(_t_Str_2935, &(Bool){1});
    Bool _t_Bool_2938; { Bool *_hp = (Bool *)assert(_t_Str_2936, &_t_Bool_2937); _t_Bool_2938 = *_hp; free(_hp); }
    (void)_t_Bool_2938;
    ;
    ;
    Str_delete(_t_Str_2936, &(Bool){1});
    Str *_t_Str_2939 = Str_lit("lolei", 5ULL);
    (void)_t_Str_2939;
    Str *_t_Str_2940 = Str_lit("src/test/constfold.til:59:12", 28ULL);
    (void)_t_Str_2940;
    Bool _t_Bool_2941 = Str_contains(lo_la, _t_Str_2939);
    (void)_t_Bool_2941;
    Str_delete(_t_Str_2939, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    Bool _t_Bool_2942; { Bool *_hp = (Bool *)assert(_t_Str_2940, &_t_Bool_2941); _t_Bool_2942 = *_hp; free(_hp); }
    (void)_t_Bool_2942;
    ;
    ;
    Str_delete(_t_Str_2940, &(Bool){1});
    Str *_t_Str_2943 = Str_lit("lalei", 5ULL);
    (void)_t_Str_2943;
    Str *_t_Str_2944 = Str_lit("src/test/constfold.til:60:12", 28ULL);
    (void)_t_Str_2944;
    Bool _t_Bool_2945 = Str_contains(la_lo, _t_Str_2943);
    (void)_t_Bool_2945;
    Str_delete(_t_Str_2943, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    Bool _t_Bool_2946; { Bool *_hp = (Bool *)assert(_t_Str_2944, &_t_Bool_2945); _t_Bool_2946 = *_hp; free(_hp); }
    (void)_t_Bool_2946;
    ;
    ;
    Str_delete(_t_Str_2944, &(Bool){1});
}

void *Array_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Array_size(); return _r;
}
void *Vec_len_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = Vec_len(_a0); return _r;
}
void Vec_push_take_dyn(void *_a0, void *_a1, void *_a2) {
    Vec_push_take(_a0, _a1, *(U32 *)_a2);
}
void *Vec_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Vec_size(); return _r;
}
void *Str_len_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = Str_len(_a0); return _r;
}
void *Str_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = Str_cmp(_a0, _a1); return _r;
}
void *Str_contains_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_contains(_a0, _a1); return _r;
}
void *Str_starts_with_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_starts_with(_a0, _a1); return _r;
}
void *Str_ends_with_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_ends_with(_a0, _a1); return _r;
}
void *Str_is_empty_dyn(void *_a0) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_is_empty(_a0); return _r;
}
void *Str_find_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = Str_find(_a0, _a1); return _r;
}
void *Str_rfind_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = Str_rfind(_a0, _a1); return _r;
}
void *Str_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = Str_to_i64(_a0); return _r;
}
void *Str_to_u8_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = Str_to_u8(_a0); return _r;
}
void *Str_to_i32_dyn(void *_a0) {
    I32 *_r = malloc(sizeof(I32)); *_r = Str_to_i32(_a0); return _r;
}
void *Str_to_f32_dyn(void *_a0) {
    F32 *_r = malloc(sizeof(F32)); *_r = Str_to_f32(_a0); return _r;
}
void *Str_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Str_size(); return _r;
}
void *Str_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_eq(_a0, _a1); return _r;
}
void *Str_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_lt(_a0, _a1); return _r;
}
void *Str_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_gt(_a0, _a1); return _r;
}
void *Str_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_neq(_a0, _a1); return _r;
}
void *Str_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_lte(_a0, _a1); return _r;
}
void *Str_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_gte(_a0, _a1); return _r;
}
void *U8_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = U8_to_i64(*(U8 *)_a0); return _r;
}
void *U8_to_u64_dyn(void *_a0) {
    U64 *_r = malloc(sizeof(U64)); *_r = U8_to_u64(*(U8 *)_a0); return _r;
}
void *U8_add_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_add(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_sub_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_sub(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_mul_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_mul(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_div_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_div(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_mod_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_mod(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U8_eq(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U8_cmp(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_and_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_and(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_or_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_or(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_xor_dyn(void *_a0, void *_a1) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_xor(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_clone_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(_a0); return _r;
}
void *U8_distance_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U8_distance(_a0, _a1); return _r;
}
void *U8_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U8_lt(_a0, _a1); return _r;
}
void *U8_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U8_gt(_a0, _a1); return _r;
}
void *U8_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U8_neq(_a0, _a1); return _r;
}
void *U8_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U8_lte(_a0, _a1); return _r;
}
void *U8_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U8_gte(_a0, _a1); return _r;
}
void *I16_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = I16_to_i64(*(I16 *)_a0); return _r;
}
void *I16_add_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_add(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_sub_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_sub(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_mul_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_mul(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_div_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_div(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_mod_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_mod(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I16_eq(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I16_cmp(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_and_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_and(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_or_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_or(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_xor_dyn(void *_a0, void *_a1) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_xor(*(I16 *)_a0, *(I16 *)_a1); return _r;
}
void *I16_clone_dyn(void *_a0) {
    I16 *_r = malloc(sizeof(I16)); *_r = I16_clone(_a0); return _r;
}
void *I16_distance_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = I16_distance(_a0, _a1); return _r;
}
void *I16_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I16_lt(_a0, _a1); return _r;
}
void *I16_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I16_gt(_a0, _a1); return _r;
}
void *I16_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I16_neq(_a0, _a1); return _r;
}
void *I16_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I16_lte(_a0, _a1); return _r;
}
void *I16_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I16_gte(_a0, _a1); return _r;
}
void *I32_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = I32_to_i64(*(I32 *)_a0); return _r;
}
void *I32_to_u32_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = I32_to_u32(*(I32 *)_a0); return _r;
}
void *I32_add_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_add(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_sub_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_sub(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_mul_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_mul(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_div_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_div(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_mod_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_mod(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I32_eq(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I32_cmp(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_and_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_and(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_or_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_or(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_xor_dyn(void *_a0, void *_a1) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_xor(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_clone_dyn(void *_a0) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(_a0); return _r;
}
void *I32_distance_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = I32_distance(_a0, _a1); return _r;
}
void *I32_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I32_lt(_a0, _a1); return _r;
}
void *I32_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I32_gt(_a0, _a1); return _r;
}
void *I32_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I32_neq(_a0, _a1); return _r;
}
void *I32_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I32_lte(_a0, _a1); return _r;
}
void *I32_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I32_gte(_a0, _a1); return _r;
}
void *F32_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = F32_to_i64(*(F32 *)_a0); return _r;
}
void *F32_to_str_dyn(void *_a0) {
    return (void *)F32_to_str(*(F32 *)_a0);
}
void *F32_add_dyn(void *_a0, void *_a1) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_add(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_sub_dyn(void *_a0, void *_a1) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_sub(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_mul_dyn(void *_a0, void *_a1) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_mul(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_div_dyn(void *_a0, void *_a1) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_div(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = F32_eq(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = F32_cmp(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_clone_dyn(void *_a0) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(_a0); return _r;
}
void *F32_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = F32_lt(_a0, _a1); return _r;
}
void *F32_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = F32_gt(_a0, _a1); return _r;
}
void *F32_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = F32_neq(_a0, _a1); return _r;
}
void *F32_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = F32_lte(_a0, _a1); return _r;
}
void *F32_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = F32_gte(_a0, _a1); return _r;
}
void *U32_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = U32_to_i64(*(U32 *)_a0); return _r;
}
void *U32_to_u64_dyn(void *_a0) {
    U64 *_r = malloc(sizeof(U64)); *_r = U32_to_u64(*(U32 *)_a0); return _r;
}
void *U32_add_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_add(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_sub_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_sub(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_mul_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_mul(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_div_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_div(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_mod_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_mod(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_eq(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U32_cmp(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_and_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_and(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_or_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_or(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_xor_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_xor(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_clone_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(_a0); return _r;
}
void *U32_distance_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U32_distance(_a0, _a1); return _r;
}
void *U32_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_lt(_a0, _a1); return _r;
}
void *U32_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_gt(_a0, _a1); return _r;
}
void *U32_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_neq(_a0, _a1); return _r;
}
void *U32_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_lte(_a0, _a1); return _r;
}
void *U32_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_gte(_a0, _a1); return _r;
}
void *U64_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = U64_to_i64(*(U64 *)_a0); return _r;
}
void *U64_to_str_dyn(void *_a0) {
    return (void *)U64_to_str(*(U64 *)_a0);
}
void *U64_add_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_add(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_sub_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_sub(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_mul_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_mul(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_div_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_div(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_mod_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_mod(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U64_eq(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U64_cmp(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_and_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_and(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_or_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_or(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_xor_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_xor(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_clone_dyn(void *_a0) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(_a0); return _r;
}
void *U64_distance_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_distance(_a0, _a1); return _r;
}
void *U64_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U64_lt(_a0, _a1); return _r;
}
void *U64_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U64_gt(_a0, _a1); return _r;
}
void *U64_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U64_neq(_a0, _a1); return _r;
}
void *U64_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U64_lte(_a0, _a1); return _r;
}
void *U64_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U64_gte(_a0, _a1); return _r;
}
void *I64_to_u8_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = I64_to_u8(*(I64 *)_a0); return _r;
}
void *I64_to_i16_dyn(void *_a0) {
    I16 *_r = malloc(sizeof(I16)); *_r = I64_to_i16(*(I64 *)_a0); return _r;
}
void *I64_to_i32_dyn(void *_a0) {
    I32 *_r = malloc(sizeof(I32)); *_r = I64_to_i32(*(I64 *)_a0); return _r;
}
void *I64_to_u32_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = I64_to_u32(*(I64 *)_a0); return _r;
}
void *I64_to_usize_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = I64_to_usize(*(I64 *)_a0); return _r;
}
void *I64_to_u64_dyn(void *_a0) {
    U64 *_r = malloc(sizeof(U64)); *_r = I64_to_u64(*(I64 *)_a0); return _r;
}
void *I64_to_f32_dyn(void *_a0) {
    F32 *_r = malloc(sizeof(F32)); *_r = I64_to_f32(*(I64 *)_a0); return _r;
}
void *I64_add_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_add(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_sub_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_sub(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_mul_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_mul(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_div_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_div(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_mod_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_mod(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_eq(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_cmp(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_and_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_and(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_or_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_or(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_xor_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_xor(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_clone_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(_a0); return _r;
}
void *I64_distance_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = I64_distance(_a0, _a1); return _r;
}
void *I64_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_lt(_a0, _a1); return _r;
}
void *I64_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_gt(_a0, _a1); return _r;
}
void *I64_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_neq(_a0, _a1); return _r;
}
void *I64_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_lte(_a0, _a1); return _r;
}
void *I64_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_gte(_a0, _a1); return _r;
}
void *Bool_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_eq(*(Bool *)_a0, *(Bool *)_a1); return _r;
}
void *Bool_clone_dyn(void *_a0) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(_a0); return _r;
}
void *Bool_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_lt(_a0, _a1); return _r;
}
void *Bool_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_gt(_a0, _a1); return _r;
}
void *Bool_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_neq(_a0, _a1); return _r;
}
void *Bool_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_lte(_a0, _a1); return _r;
}
void *Bool_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_gte(_a0, _a1); return _r;
}
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Array_new;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Array_len;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Array_get;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)Array_set;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Array_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Array_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Array_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Vec_new;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Vec_len_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "push", 4ULL) == 0) return (void*)Vec_push;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "append", 6ULL) == 0) return (void*)Vec_append;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "move_from", 9ULL) == 0) return (void*)Vec_move_from;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Vec_get;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "pop", 3ULL) == 0) return (void*)Vec_pop;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "take_prefix", 11ULL) == 0) return (void*)Vec_take_prefix;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)Vec_set;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "push_take", 9ULL) == 0) return (void*)Vec_push_take_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Vec_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Vec_clone;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Vec_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Str_len_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Str_get;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "byte_at", 7ULL) == 0) return (void*)Str_byte_at;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Str_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "concat", 6ULL) == 0) return (void*)Str_concat;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)Str_with_capacity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)Str_push_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Str_clone;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Str_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)Str_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "substr", 6ULL) == 0) return (void*)Str_substr;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "contains", 8ULL) == 0) return (void*)Str_contains_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 11ULL && memcmp(method->c_str, "starts_with", 11ULL) == 0) return (void*)Str_starts_with_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "ends_with", 9ULL) == 0) return (void*)Str_ends_with_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_empty", 8ULL) == 0) return (void*)Str_is_empty_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "find", 4ULL) == 0) return (void*)Str_find_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "rfind", 5ULL) == 0) return (void*)Str_rfind_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "replace", 7ULL) == 0) return (void*)Str_replace;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "get_char", 8ULL) == 0) return (void*)Str_get_char;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "strip_prefix", 12ULL) == 0) return (void*)Str_strip_prefix;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 12ULL && memcmp(method->c_str, "strip_suffix", 12ULL) == 0) return (void*)Str_strip_suffix;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "from_byte", 9ULL) == 0) return (void*)Str_from_byte;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)Str_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "to_u8", 5ULL) == 0) return (void*)Str_to_u8_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i32", 6ULL) == 0) return (void*)Str_to_i32_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_f32", 6ULL) == 0) return (void*)Str_to_f32_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "split", 5ULL) == 0) return (void*)Str_split;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Str_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Str_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)Str_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)Str_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)Str_neq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)Str_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)Str_gte_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)U8_to_i64_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_u64", 6ULL) == 0) return (void*)U8_to_u64_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)U8_to_str;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U8_add_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U8_sub_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)U8_mul_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)U8_div_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)U8_mod_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)U8_inc;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)U8_dec;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)U8_unity;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)U8_eq_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)U8_and_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)U8_or_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)U8_xor_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "distance", 8ULL) == 0) return (void*)U8_distance_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U8_delete;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U8_size;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U8_lt_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U8_gt_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)U8_neq_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U8_lte_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U8_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)I16_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)I16_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)I16_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)I16_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)I16_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)I16_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)I16_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)I16_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)I16_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)I16_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)I16_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I16_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neg", 3ULL) == 0) return (void*)I16_neg;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "abs", 3ULL) == 0) return (void*)I16_abs;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)I16_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)I16_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)I16_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I16_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "distance", 8ULL) == 0) return (void*)I16_distance_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I16_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I16_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I16_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I16_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I16_neq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)I16_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)I16_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)I32_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_u32", 6ULL) == 0) return (void*)I32_to_u32_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)I32_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)I32_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)I32_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)I32_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)I32_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)I32_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)I32_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)I32_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)I32_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)I32_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neg", 3ULL) == 0) return (void*)I32_neg;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "abs", 3ULL) == 0) return (void*)I32_abs;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)I32_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)I32_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)I32_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "distance", 8ULL) == 0) return (void*)I32_distance_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I32_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I32_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I32_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I32_neq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)I32_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)I32_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)F32_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)F32_to_str_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "from_i64", 8ULL) == 0) return (void*)F32_from_i64;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)F32_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)F32_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)F32_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)F32_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)F32_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)F32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)F32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)F32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)F32_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)F32_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)F32_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)F32_neq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)F32_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)F32_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)U32_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_u64", 6ULL) == 0) return (void*)U32_to_u64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)U32_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U32_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U32_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)U32_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)U32_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)U32_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)U32_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)U32_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)U32_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)U32_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)U32_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)U32_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)U32_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "distance", 8ULL) == 0) return (void*)U32_distance_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U32_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U32_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U32_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)U32_neq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U32_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U32_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)U64_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)U64_to_str_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "from_i64", 8ULL) == 0) return (void*)U64_from_i64;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)U64_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)U64_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)U64_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)U64_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)U64_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)U64_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)U64_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)U64_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)U64_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)U64_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "distance", 8ULL) == 0) return (void*)U64_distance_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U64_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U64_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U64_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U64_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)U64_neq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U64_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U64_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)I64_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "to_u8", 5ULL) == 0) return (void*)I64_to_u8_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i16", 6ULL) == 0) return (void*)I64_to_i16_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i32", 6ULL) == 0) return (void*)I64_to_i32_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_u32", 6ULL) == 0) return (void*)I64_to_u32_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "to_usize", 8ULL) == 0) return (void*)I64_to_usize_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_u64", 6ULL) == 0) return (void*)I64_to_u64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_f32", 6ULL) == 0) return (void*)I64_to_f32_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)I64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)I64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)I64_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)I64_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)I64_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)I64_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)I64_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "unity", 5ULL) == 0) return (void*)I64_unity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)I64_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neg", 3ULL) == 0) return (void*)I64_neg;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "abs", 3ULL) == 0) return (void*)I64_abs;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "and", 3ULL) == 0) return (void*)I64_and_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "or", 2ULL) == 0) return (void*)I64_or_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "xor", 3ULL) == 0) return (void*)I64_xor_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "distance", 8ULL) == 0) return (void*)I64_distance_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I64_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I64_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I64_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I64_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I64_neq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)I64_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)I64_gte_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)Bool_to_str;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Bool_eq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Bool_cmp;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Bool_clone_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Bool_delete;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Bool_size;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)Bool_lt_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)Bool_gt_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)Bool_neq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)Bool_lte_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)Bool_gte_dyn;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Dynamic_size;
    fprintf(stderr, "dyn_fn: unknown %s.%s\n", (char*)type_name->c_str, (char*)method->c_str);
    exit(1);
}

int main(void) {
    I64 _t_I64_1124 = 0;
    (void)_t_I64_1124;
    I64 _t_I64_1125 = 1;
    (void)_t_I64_1125;
    I64 _t_I64_1126 = I64_sub(_t_I64_1124, _t_I64_1125);
    (void)_t_I64_1126;
    CAP_LIT = I64_to_usize(_t_I64_1126);
    (void)CAP_LIT;
    I64 _t_I64_1127 = 0;
    (void)_t_I64_1127;
    I64 _t_I64_1128 = 2;
    (void)_t_I64_1128;
    I64 _t_I64_1129 = I64_sub(_t_I64_1127, _t_I64_1128);
    (void)_t_I64_1129;
    CAP_VIEW = I64_to_usize(_t_I64_1129);
    (void)CAP_VIEW;
    __til_docs_blob__ = (Str){.c_str=(U8*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)__til_docs_blob__;
    __til_kinds_blob__ = (Str){.c_str=(U8*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)__til_kinds_blob__;
    test_simple_add();
    fprintf(stderr, "  pass: %s\n", "test_simple_add");
    test_nested_arithmetic();
    fprintf(stderr, "  pass: %s\n", "test_nested_arithmetic");
    test_deeply_nested();
    fprintf(stderr, "  pass: %s\n", "test_deeply_nested");
    test_lolalalo();
    fprintf(stderr, "  pass: %s\n", "test_lolalalo");
    fprintf(stderr, "4/4 tests passed\n");
    return 0;
}
