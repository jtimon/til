#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef struct Array Array;
typedef struct Dynamic Dynamic;
typedef struct Vec Vec;
typedef struct Str Str;

typedef void * (*CloneFn)(void *);
typedef void (*DeleteFn)(void *, Bool *);


typedef struct Dynamic {
    char _;
} Dynamic;






typedef struct Str {
    U8 *c_str;
    U32 count;
    U32 cap;
} Str;





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
void panic(Str * loc_str, Array * parts);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
F32 * F32_from_i64(I64 * val);
void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
Bool F32_lt(F32 * a, F32 * b);
Bool F32_gt(F32 * a, F32 * b);
Bool F32_neq(F32 * a, F32 * b);
Bool F32_lte(F32 * a, F32 * b);
Bool F32_gte(F32 * a, F32 * b);
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
void println(Array * parts);
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
void panic(Str * loc_str, Array * parts);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
F32 * F32_from_i64(I64 * val);
void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
Bool F32_lt(F32 * a, F32 * b);
Bool F32_gt(F32 * a, F32 * b);
Bool F32_neq(F32 * a, F32 * b);
Bool F32_lte(F32 * a, F32 * b);
Bool F32_gte(F32 * a, F32 * b);
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
void println(Array * parts);
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

Str __til_docs_blob__;
Str __til_kinds_blob__;
U32 CAP_LIT;
U32 CAP_VIEW;

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

Str * Bool_to_str(Bool * b) {
    (void)b;
    if (DEREF(b)) {
        Str *_t_Str_1328 = Str_lit("true", 4ULL);
        (void)_t_Str_1328;
        return _t_Str_1328;
    } else {
        Str *_t_Str_1329 = Str_lit("false", 5ULL);
        (void)_t_Str_1329;
        return _t_Str_1329;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1334 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_1334;
    if (_t_Bool_1334) {
        I64 _t_I64_1330 = 0;
        (void)_t_I64_1330;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_1330; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_1331 = 0;
        (void)_t_I64_1331;
        I64 _t_I64_1332 = 1;
        (void)_t_I64_1332;
        I64 _t_I64_1333 = I64_sub(_t_I64_1331, _t_I64_1332);
        (void)_t_I64_1333;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_1333; return _r; }
    }
    I64 _t_I64_1335 = 1;
    (void)_t_I64_1335;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_1335; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_1336 = 1;
    (void)_t_I64_1336;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_1336; return _r; }
}

Bool Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_1337 = 0;
    (void)_t_I64_1337;
    I64 _t_I64_1338 = 1;
    (void)_t_I64_1338;
    I64 _t_I64_1339; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_1339 = *_hp; free(_hp); }
    (void)_t_I64_1339;
    I64 _t_I64_1340 = I64_sub(_t_I64_1337, _t_I64_1338);
    (void)_t_I64_1340;
    ;
    ;
    Bool _t_Bool_1341 = I64_eq(_t_I64_1339, _t_I64_1340);
    (void)_t_Bool_1341;
    ;
    ;
    return _t_Bool_1341;
}

Bool Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_1342; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_1342 = *_hp; free(_hp); }
    (void)_t_I64_1342;
    I64 _t_I64_1343 = 1;
    (void)_t_I64_1343;
    Bool _t_Bool_1344 = I64_eq(_t_I64_1342, _t_I64_1343);
    (void)_t_Bool_1344;
    ;
    ;
    return _t_Bool_1344;
}

Bool Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1345 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_1345;
    Bool _t_Bool_1346 = not(_t_Bool_1345);
    (void)_t_Bool_1346;
    ;
    return _t_Bool_1346;
}

Bool Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1347 = Bool_gt(a, b);
    (void)_t_Bool_1347;
    Bool _t_Bool_1348 = not(_t_Bool_1347);
    (void)_t_Bool_1348;
    ;
    return _t_Bool_1348;
}

Bool Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1349 = Bool_lt(a, b);
    (void)_t_Bool_1349;
    Bool _t_Bool_1350 = not(_t_Bool_1349);
    (void)_t_Bool_1350;
    ;
    return _t_Bool_1350;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_1430 = 8;
    (void)_t_I64_1430;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_1430; return _r; }
}

void * default_clone(void * v) {
    (void)v;
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

Vec * Vec_new(Str * elem_type, U32 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t_Bool_1443 = Str_is_empty(elem_type);
    (void)_t_Bool_1443;
    if (_t_Bool_1443) {
        Str *_t_Str_1433 = Str_lit("Str", 3ULL);
        (void)_t_Str_1433;
        U32 _t_U32_1434 = 16;
        (void)_t_U32_1434;
        U32 _t_U32_1435 = 1;
        (void)_t_U32_1435;
        Array *_va_Array_59 = Array_new(_t_Str_1433, &_t_U32_1434, &_t_U32_1435);
        (void)_va_Array_59;
        Str_delete(_t_Str_1433, &(Bool){1});
        ;
        ;
        U32 _t_U32_1436 = 0;
        (void)_t_U32_1436;
        Str *_t_Str_1437 = Str_lit("Vec.new: elem_type required", 27ULL);
        (void)_t_Str_1437;
        Array_set(_va_Array_59, &_t_U32_1436, _t_Str_1437);
        ;
        Str *_t_Str_1438 = Str_lit("./src/core/vec.til:18:19", 24ULL);
        (void)_t_Str_1438;
        panic(_t_Str_1438, _va_Array_59);
        Str_delete(_t_Str_1438, &(Bool){1});
    }
    ;
    Str *_t_Str_1444 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1444;
    Bool _t_Bool_1445 = Str_eq(elem_type, _t_Str_1444);
    (void)_t_Bool_1445;
    Str_delete(_t_Str_1444, &(Bool){1});
    if (_t_Bool_1445) {
        void * _t_v_1439 = malloc(DEREF(elem_size));
        (void)_t_v_1439;
        U32 _t_U32_1440 = 0;
        (void)_t_U32_1440;
        I64 _t_I64_1441 = 1;
        (void)_t_I64_1441;
        Vec *_t_Vec_1442 = malloc(sizeof(Vec));
        _t_Vec_1442->data = _t_v_1439;
        _t_Vec_1442->count = _t_U32_1440;
        _t_Vec_1442->cap = _t_I64_1441;
        _t_Vec_1442->elem_size = DEREF(elem_size);
        { Str *_ca = Str_clone(elem_type); _t_Vec_1442->elem_type = *_ca; free(_ca); }
        _t_Vec_1442->elem_clone = (void *)(void *)default_clone;
        _t_Vec_1442->elem_delete = (void *)(void *)default_delete;
        (void)_t_Vec_1442;
        ;
        ;
        ;
        return _t_Vec_1442;
    }
    ;
    void * _t_v_1446 = malloc(DEREF(elem_size));
    (void)_t_v_1446;
    U32 _t_U32_1447 = 0;
    (void)_t_U32_1447;
    I64 _t_I64_1448 = 1;
    (void)_t_I64_1448;
    void * _t_v_1449 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1449;
    void * _t_v_1450 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1450;
    Vec *_t_Vec_1451 = malloc(sizeof(Vec));
    _t_Vec_1451->data = _t_v_1446;
    _t_Vec_1451->count = _t_U32_1447;
    _t_Vec_1451->cap = _t_I64_1448;
    _t_Vec_1451->elem_size = DEREF(elem_size);
    { Str *_ca = Str_clone(elem_type); _t_Vec_1451->elem_type = *_ca; free(_ca); }
    _t_Vec_1451->elem_clone = _t_v_1449;
    _t_Vec_1451->elem_delete = _t_v_1450;
    (void)_t_Vec_1451;
    ;
    ;
    return _t_Vec_1451;
}

U32 Vec_len(Vec * self) {
    (void)self;
    return self->count;
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t_Bool_1456 = U32_eq(self->count, self->cap);
    (void)_t_Bool_1456;
    if (_t_Bool_1456) {
        U32 _t_U32_1452 = 2;
        (void)_t_U32_1452;
        U32 new_cap = U32_mul(self->cap, _t_U32_1452);
        (void)new_cap;
        ;
        U32 _t_U64_1453 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1453;
        void * _t_v_1454 = realloc(self->data, _t_U64_1453);
        (void)_t_v_1454;
        ;
        self->data = _t_v_1454;
        U32 _t_U32_1455 = U32_clone(&new_cap);
        (void)_t_U32_1455;
        ;
        self->cap = _t_U32_1455;
        ;
    }
    ;
    U32 _t_U64_1457 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_1457;
    void *_t_v_1458 = ptr_add(self->data, _t_U64_1457);
    (void)_t_v_1458;
    memcpy(_t_v_1458, val, self->elem_size);
    ;
    free(val);
    U32 _t_U32_1459 = 1;
    (void)_t_U32_1459;
    U32 _t_U32_1460 = U32_add(self->count, _t_U32_1459);
    (void)_t_U32_1460;
    ;
    self->count = _t_U32_1460;
    ;
}

void Vec_append(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_1473 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_1473;
    Bool _t_Bool_1474 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_1474;
    Bool _t_Bool_1475 = not(_t_Bool_1473);
    (void)_t_Bool_1475;
    ;
    Bool _t_Bool_1476 = not(_t_Bool_1474);
    (void)_t_Bool_1476;
    ;
    Bool _t_Bool_1477 = or(_t_Bool_1475, _t_Bool_1476);
    (void)_t_Bool_1477;
    ;
    ;
    if (_t_Bool_1477) {
        Str *_t_Str_1461 = Str_lit("Str", 3ULL);
        (void)_t_Str_1461;
        U32 _t_U32_1462 = 16;
        (void)_t_U32_1462;
        U32 _t_U32_1463 = 1;
        (void)_t_U32_1463;
        Array *_va_Array_60 = Array_new(_t_Str_1461, &_t_U32_1462, &_t_U32_1463);
        (void)_va_Array_60;
        Str_delete(_t_Str_1461, &(Bool){1});
        ;
        ;
        U32 _t_U32_1464 = 0;
        (void)_t_U32_1464;
        Str *_t_Str_1465 = Str_lit("Vec.append: incompatible vecs", 29ULL);
        (void)_t_Str_1465;
        Array_set(_va_Array_60, &_t_U32_1464, _t_Str_1465);
        ;
        Str *_t_Str_1466 = Str_lit("./src/core/vec.til:45:19", 24ULL);
        (void)_t_Str_1466;
        panic(_t_Str_1466, _va_Array_60);
        Str_delete(_t_Str_1466, &(Bool){1});
    }
    ;
    U32 _t_U32_1478 = 0;
    (void)_t_U32_1478;
    Bool _t_Bool_1479 = U32_eq(other->count, _t_U32_1478);
    (void)_t_Bool_1479;
    ;
    if (_t_Bool_1479) {
        ;
        Vec_delete(other, &(Bool){0});
        return;
    }
    ;
    U32 needed = U32_add(self->count, other->count);
    (void)needed;
    Bool _t_Bool_1480 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_1480;
    if (_t_Bool_1480) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_1467 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_1467;
            if (_wcond_Bool_1467) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_1468 = 2;
            (void)_t_U32_1468;
            U32 _t_U32_1469 = U32_mul(new_cap, _t_U32_1468);
            (void)_t_U32_1469;
            ;
            new_cap = _t_U32_1469;
            ;
        }
        U32 _t_U64_1470 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1470;
        void * _t_v_1471 = realloc(self->data, _t_U64_1470);
        (void)_t_v_1471;
        ;
        self->data = _t_v_1471;
        U32 _t_U32_1472 = U32_clone(&new_cap);
        (void)_t_U32_1472;
        ;
        self->cap = _t_U32_1472;
        ;
    }
    ;
    U32 _t_U64_1481 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_1481;
    void *_t_v_1482 = ptr_add(self->data, _t_U64_1481);
    (void)_t_v_1482;
    U32 _t_U64_1483 = U32_mul(other->count, self->elem_size);
    (void)_t_U64_1483;
    memcpy(_t_v_1482, other->data, _t_U64_1483);
    ;
    ;
    U32 _t_U32_1484 = U32_clone(&needed);
    (void)_t_U32_1484;
    ;
    self->count = _t_U32_1484;
    ;
    U32 _t_U32_1485 = 0;
    (void)_t_U32_1485;
    other->count = _t_U32_1485;
    ;
    Vec_delete(other, &(Bool){0});
}

void Vec_move_from(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_1509 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_1509;
    Bool _t_Bool_1510 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_1510;
    Bool _t_Bool_1511 = not(_t_Bool_1509);
    (void)_t_Bool_1511;
    ;
    Bool _t_Bool_1512 = not(_t_Bool_1510);
    (void)_t_Bool_1512;
    ;
    Bool _t_Bool_1513 = or(_t_Bool_1511, _t_Bool_1512);
    (void)_t_Bool_1513;
    ;
    ;
    if (_t_Bool_1513) {
        Str *_t_Str_1486 = Str_lit("Str", 3ULL);
        (void)_t_Str_1486;
        U32 _t_U32_1487 = 16;
        (void)_t_U32_1487;
        U32 _t_U32_1488 = 1;
        (void)_t_U32_1488;
        Array *_va_Array_61 = Array_new(_t_Str_1486, &_t_U32_1487, &_t_U32_1488);
        (void)_va_Array_61;
        Str_delete(_t_Str_1486, &(Bool){1});
        ;
        ;
        U32 _t_U32_1489 = 0;
        (void)_t_U32_1489;
        Str *_t_Str_1490 = Str_lit("Vec.move_from: incompatible vecs", 32ULL);
        (void)_t_Str_1490;
        Array_set(_va_Array_61, &_t_U32_1489, _t_Str_1490);
        ;
        Str *_t_Str_1491 = Str_lit("./src/core/vec.til:72:19", 24ULL);
        (void)_t_Str_1491;
        panic(_t_Str_1491, _va_Array_61);
        Str_delete(_t_Str_1491, &(Bool){1});
    }
    ;
    Bool _t_Bool_1514 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1514;
    Str *_t_Str_1515 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1515;
    Bool _t_Bool_1516 = Str_eq(&self->elem_type, _t_Str_1515);
    (void)_t_Bool_1516;
    Str_delete(_t_Str_1515, &(Bool){1});
    Bool _t_Bool_1517 = not(_t_Bool_1514);
    (void)_t_Bool_1517;
    ;
    Bool _t_Bool_1518 = not(_t_Bool_1516);
    (void)_t_Bool_1518;
    ;
    Bool _t_Bool_1519 = and(_t_Bool_1517, _t_Bool_1518);
    (void)_t_Bool_1519;
    ;
    ;
    if (_t_Bool_1519) {
        {
            U32 _re_U32_1492 = self->count;
            (void)_re_U32_1492;
            U32 _rc_U32_1492 = 0;
            (void)_rc_U32_1492;
            Bool _t_Bool_1501 = U32_lte(&_rc_U32_1492, &_re_U32_1492);
            (void)_t_Bool_1501;
            if (_t_Bool_1501) {
                while (1) {
                    Bool _wcond_Bool_1493 = U32_lt(&_rc_U32_1492, &_re_U32_1492);
                    (void)_wcond_Bool_1493;
                    if (_wcond_Bool_1493) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1492);
                    (void)i;
                    U32_inc(&_rc_U32_1492);
                    U32 _t_U64_1494 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1494;
                    ;
                    void *_t_v_1495 = ptr_add(self->data, _t_U64_1494);
                    (void)_t_v_1495;
                    Bool _t_Bool_1496 = 0;
                    (void)_t_Bool_1496;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1495, &_t_Bool_1496);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1497 = U32_gt(&_rc_U32_1492, &_re_U32_1492);
                    (void)_wcond_Bool_1497;
                    if (_wcond_Bool_1497) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1492);
                    (void)i;
                    U32_dec(&_rc_U32_1492);
                    U32 _t_U64_1498 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1498;
                    ;
                    void *_t_v_1499 = ptr_add(self->data, _t_U64_1498);
                    (void)_t_v_1499;
                    Bool _t_Bool_1500 = 0;
                    (void)_t_Bool_1500;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1499, &_t_Bool_1500);
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
    Bool _t_Bool_1520 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_1520;
    if (_t_Bool_1520) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_1502 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_1502;
            if (_wcond_Bool_1502) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_1503 = 2;
            (void)_t_U32_1503;
            U32 _t_U32_1504 = U32_mul(new_cap, _t_U32_1503);
            (void)_t_U32_1504;
            ;
            new_cap = _t_U32_1504;
            ;
        }
        U32 _t_U64_1505 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1505;
        void * _t_v_1506 = realloc(self->data, _t_U64_1505);
        (void)_t_v_1506;
        ;
        self->data = _t_v_1506;
        U32 _t_U32_1507 = U32_clone(&new_cap);
        (void)_t_U32_1507;
        ;
        self->cap = _t_U32_1507;
        ;
    }
    ;
    U32 _t_U32_1521 = 0;
    (void)_t_U32_1521;
    Bool _t_Bool_1522 = U32_gt(&needed, &_t_U32_1521);
    (void)_t_Bool_1522;
    ;
    if (_t_Bool_1522) {
        U32 _t_U64_1508 = U32_mul(needed, self->elem_size);
        (void)_t_U64_1508;
        memcpy(self->data, other->data, _t_U64_1508);
        ;
    }
    ;
    U32 _t_U32_1523 = U32_clone(&needed);
    (void)_t_U32_1523;
    ;
    self->count = _t_U32_1523;
    ;
    U32 _t_U32_1524 = 0;
    (void)_t_U32_1524;
    other->count = _t_U32_1524;
    ;
}

void * Vec_get(Vec * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_1539 = U32_gte(i, &self->count);
    (void)_t_Bool_1539;
    if (_t_Bool_1539) {
        Str *_t_Str_1525 = Str_lit("Str", 3ULL);
        (void)_t_Str_1525;
        U32 _t_U32_1526 = 16;
        (void)_t_U32_1526;
        U32 _t_U32_1527 = 5;
        (void)_t_U32_1527;
        Array *_va_Array_62 = Array_new(_t_Str_1525, &_t_U32_1526, &_t_U32_1527);
        (void)_va_Array_62;
        Str_delete(_t_Str_1525, &(Bool){1});
        ;
        ;
        U32 _t_U32_1528 = 0;
        (void)_t_U32_1528;
        Str *_t_Str_1529 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t_Str_1529;
        Array_set(_va_Array_62, &_t_U32_1528, _t_Str_1529);
        ;
        U32 _t_U32_1530 = 1;
        (void)_t_U32_1530;
        Str *_t_Str_1531 = U32_to_str(i);
        (void)_t_Str_1531;
        Array_set(_va_Array_62, &_t_U32_1530, _t_Str_1531);
        ;
        U32 _t_U32_1532 = 2;
        (void)_t_U32_1532;
        Str *_t_Str_1533 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1533;
        Array_set(_va_Array_62, &_t_U32_1532, _t_Str_1533);
        ;
        U32 _t_U32_1534 = 3;
        (void)_t_U32_1534;
        Str *_t_Str_1535 = U32_to_str(&self->count);
        (void)_t_Str_1535;
        Array_set(_va_Array_62, &_t_U32_1534, _t_Str_1535);
        ;
        U32 _t_U32_1536 = 4;
        (void)_t_U32_1536;
        Str *_t_Str_1537 = Str_lit(")", 1ULL);
        (void)_t_Str_1537;
        Array_set(_va_Array_62, &_t_U32_1536, _t_Str_1537);
        ;
        Str *_t_Str_1538 = Str_lit("./src/core/vec.til:97:19", 24ULL);
        (void)_t_Str_1538;
        panic(_t_Str_1538, _va_Array_62);
        Str_delete(_t_Str_1538, &(Bool){1});
    }
    ;
    U32 _t_U64_1540 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1540;
    void *_t_v_1541 = ptr_add(self->data, _t_U64_1540);
    (void)_t_v_1541;
    ;
    return _t_v_1541;
}

void * Vec_pop(Vec * self) {
    (void)self;
    U32 _t_U32_1548 = 0;
    (void)_t_U32_1548;
    Bool _t_Bool_1549 = U32_eq(self->count, _t_U32_1548);
    (void)_t_Bool_1549;
    ;
    if (_t_Bool_1549) {
        Str *_t_Str_1542 = Str_lit("Str", 3ULL);
        (void)_t_Str_1542;
        U32 _t_U32_1543 = 16;
        (void)_t_U32_1543;
        U32 _t_U32_1544 = 1;
        (void)_t_U32_1544;
        Array *_va_Array_63 = Array_new(_t_Str_1542, &_t_U32_1543, &_t_U32_1544);
        (void)_va_Array_63;
        Str_delete(_t_Str_1542, &(Bool){1});
        ;
        ;
        U32 _t_U32_1545 = 0;
        (void)_t_U32_1545;
        Str *_t_Str_1546 = Str_lit("Vec.pop: empty vec", 18ULL);
        (void)_t_Str_1546;
        Array_set(_va_Array_63, &_t_U32_1545, _t_Str_1546);
        ;
        Str *_t_Str_1547 = Str_lit("./src/core/vec.til:104:19", 25ULL);
        (void)_t_Str_1547;
        panic(_t_Str_1547, _va_Array_63);
        Str_delete(_t_Str_1547, &(Bool){1});
    }
    ;
    U32 _t_U32_1550 = 1;
    (void)_t_U32_1550;
    U32 last = U32_sub(self->count, _t_U32_1550);
    (void)last;
    ;
    void * out = malloc(self->elem_size);
    (void)out;
    U32 _t_U64_1551 = U32_mul(last, self->elem_size);
    (void)_t_U64_1551;
    void *_t_v_1552 = ptr_add(self->data, _t_U64_1551);
    (void)_t_v_1552;
    memcpy(out, _t_v_1552, self->elem_size);
    ;
    U32 _t_U32_1553 = U32_clone(&last);
    (void)_t_U32_1553;
    ;
    self->count = _t_U32_1553;
    ;
    return out;
}

Vec * Vec_take_prefix(Vec * self, U32 * n) {
    (void)self;
    (void)n;
    Bool _t_Bool_1573 = U32_gt(n, &self->count);
    (void)_t_Bool_1573;
    if (_t_Bool_1573) {
        Str *_t_Str_1554 = Str_lit("Str", 3ULL);
        (void)_t_Str_1554;
        U32 _t_U32_1555 = 16;
        (void)_t_U32_1555;
        U32 _t_U32_1556 = 5;
        (void)_t_U32_1556;
        Array *_va_Array_64 = Array_new(_t_Str_1554, &_t_U32_1555, &_t_U32_1556);
        (void)_va_Array_64;
        Str_delete(_t_Str_1554, &(Bool){1});
        ;
        ;
        U32 _t_U32_1557 = 0;
        (void)_t_U32_1557;
        Str *_t_Str_1558 = Str_lit("Vec.take_prefix: count ", 23ULL);
        (void)_t_Str_1558;
        Array_set(_va_Array_64, &_t_U32_1557, _t_Str_1558);
        ;
        U32 _t_U32_1559 = 1;
        (void)_t_U32_1559;
        Str *_t_Str_1560 = U32_to_str(n);
        (void)_t_Str_1560;
        Array_set(_va_Array_64, &_t_U32_1559, _t_Str_1560);
        ;
        U32 _t_U32_1561 = 2;
        (void)_t_U32_1561;
        Str *_t_Str_1562 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1562;
        Array_set(_va_Array_64, &_t_U32_1561, _t_Str_1562);
        ;
        U32 _t_U32_1563 = 3;
        (void)_t_U32_1563;
        Str *_t_Str_1564 = U32_to_str(&self->count);
        (void)_t_Str_1564;
        Array_set(_va_Array_64, &_t_U32_1563, _t_Str_1564);
        ;
        U32 _t_U32_1565 = 4;
        (void)_t_U32_1565;
        Str *_t_Str_1566 = Str_lit(")", 1ULL);
        (void)_t_Str_1566;
        Array_set(_va_Array_64, &_t_U32_1565, _t_Str_1566);
        ;
        Str *_t_Str_1567 = Str_lit("./src/core/vec.til:115:19", 25ULL);
        (void)_t_Str_1567;
        panic(_t_Str_1567, _va_Array_64);
        Str_delete(_t_Str_1567, &(Bool){1});
    }
    ;
    U32 prefix_cap = 1;
    (void)prefix_cap;
    U32 _t_U32_1574 = 0;
    (void)_t_U32_1574;
    Bool _t_Bool_1575 = U32_gt(n, &_t_U32_1574);
    (void)_t_Bool_1575;
    ;
    if (_t_Bool_1575) {
        U32 _t_U32_1568 = U32_clone(n);
        (void)_t_U32_1568;
        prefix_cap = _t_U32_1568;
        ;
    }
    ;
    U32 _t_U64_1576 = U32_mul(prefix_cap, self->elem_size);
    (void)_t_U64_1576;
    void * prefix_data = malloc(_t_U64_1576);
    (void)prefix_data;
    ;
    U32 _t_U32_1577 = 0;
    (void)_t_U32_1577;
    Bool _t_Bool_1578 = U32_gt(n, &_t_U32_1577);
    (void)_t_Bool_1578;
    ;
    if (_t_Bool_1578) {
        U32 _t_U64_1569 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_1569;
        memcpy(prefix_data, self->data, _t_U64_1569);
        ;
    }
    ;
    U32 tail_count = U32_sub(self->count, DEREF(n));
    (void)tail_count;
    U32 _t_U32_1579 = 0;
    (void)_t_U32_1579;
    Bool _t_Bool_1580 = U32_gt(&tail_count, &_t_U32_1579);
    (void)_t_Bool_1580;
    ;
    if (_t_Bool_1580) {
        U32 _t_U64_1570 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_1570;
        void *_t_v_1571 = ptr_add(self->data, _t_U64_1570);
        (void)_t_v_1571;
        U32 _t_U64_1572 = U32_mul(tail_count, self->elem_size);
        (void)_t_U64_1572;
        memmove(self->data, _t_v_1571, _t_U64_1572);
        ;
        ;
    }
    ;
    U32 _t_U32_1581 = U32_clone(&tail_count);
    (void)_t_U32_1581;
    ;
    self->count = _t_U32_1581;
    ;
    Vec *_t_Vec_1582 = malloc(sizeof(Vec));
    _t_Vec_1582->data = prefix_data;
    _t_Vec_1582->count = DEREF(n);
    _t_Vec_1582->cap = prefix_cap;
    _t_Vec_1582->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_1582->elem_type = *_ca; free(_ca); }
    _t_Vec_1582->elem_clone = (void *)self->elem_clone;
    _t_Vec_1582->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_1582;
    ;
    return _t_Vec_1582;
}

void Vec_set(Vec * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_1597 = U32_gte(i, &self->count);
    (void)_t_Bool_1597;
    if (_t_Bool_1597) {
        Str *_t_Str_1583 = Str_lit("Str", 3ULL);
        (void)_t_Str_1583;
        U32 _t_U32_1584 = 16;
        (void)_t_U32_1584;
        U32 _t_U32_1585 = 5;
        (void)_t_U32_1585;
        Array *_va_Array_65 = Array_new(_t_Str_1583, &_t_U32_1584, &_t_U32_1585);
        (void)_va_Array_65;
        Str_delete(_t_Str_1583, &(Bool){1});
        ;
        ;
        U32 _t_U32_1586 = 0;
        (void)_t_U32_1586;
        Str *_t_Str_1587 = Str_lit("Vec.set: index ", 15ULL);
        (void)_t_Str_1587;
        Array_set(_va_Array_65, &_t_U32_1586, _t_Str_1587);
        ;
        U32 _t_U32_1588 = 1;
        (void)_t_U32_1588;
        Str *_t_Str_1589 = U32_to_str(i);
        (void)_t_Str_1589;
        Array_set(_va_Array_65, &_t_U32_1588, _t_Str_1589);
        ;
        U32 _t_U32_1590 = 2;
        (void)_t_U32_1590;
        Str *_t_Str_1591 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1591;
        Array_set(_va_Array_65, &_t_U32_1590, _t_Str_1591);
        ;
        U32 _t_U32_1592 = 3;
        (void)_t_U32_1592;
        Str *_t_Str_1593 = U32_to_str(&self->count);
        (void)_t_Str_1593;
        Array_set(_va_Array_65, &_t_U32_1592, _t_Str_1593);
        ;
        U32 _t_U32_1594 = 4;
        (void)_t_U32_1594;
        Str *_t_Str_1595 = Str_lit(")", 1ULL);
        (void)_t_Str_1595;
        Array_set(_va_Array_65, &_t_U32_1594, _t_Str_1595);
        ;
        Str *_t_Str_1596 = Str_lit("./src/core/vec.til:137:19", 25ULL);
        (void)_t_Str_1596;
        panic(_t_Str_1596, _va_Array_65);
        Str_delete(_t_Str_1596, &(Bool){1});
    }
    ;
    U32 _t_U64_1598 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1598;
    void *_t_v_1599 = ptr_add(self->data, _t_U64_1598);
    (void)_t_v_1599;
    memcpy(_t_v_1599, val, self->elem_size);
    ;
    free(val);
}

void Vec_push_take(Vec * self, Vec * src, U32 i) {
    (void)self;
    (void)src;
    (void)i;
    Bool _t_Bool_1624 = U32_gte(&i, &src->count);
    (void)_t_Bool_1624;
    if (_t_Bool_1624) {
        Str *_t_Str_1600 = Str_lit("Str", 3ULL);
        (void)_t_Str_1600;
        U32 _t_U32_1601 = 16;
        (void)_t_U32_1601;
        U32 _t_U32_1602 = 5;
        (void)_t_U32_1602;
        Array *_va_Array_66 = Array_new(_t_Str_1600, &_t_U32_1601, &_t_U32_1602);
        (void)_va_Array_66;
        Str_delete(_t_Str_1600, &(Bool){1});
        ;
        ;
        U32 _t_U32_1603 = 0;
        (void)_t_U32_1603;
        Str *_t_Str_1604 = Str_lit("Vec.push_take: index ", 21ULL);
        (void)_t_Str_1604;
        Array_set(_va_Array_66, &_t_U32_1603, _t_Str_1604);
        ;
        U32 _t_U32_1605 = 1;
        (void)_t_U32_1605;
        Str *_t_Str_1606 = U32_to_str(&i);
        (void)_t_Str_1606;
        Array_set(_va_Array_66, &_t_U32_1605, _t_Str_1606);
        ;
        U32 _t_U32_1607 = 2;
        (void)_t_U32_1607;
        Str *_t_Str_1608 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1608;
        Array_set(_va_Array_66, &_t_U32_1607, _t_Str_1608);
        ;
        U32 _t_U32_1609 = 3;
        (void)_t_U32_1609;
        Str *_t_Str_1610 = U32_to_str(&src->count);
        (void)_t_Str_1610;
        Array_set(_va_Array_66, &_t_U32_1609, _t_Str_1610);
        ;
        U32 _t_U32_1611 = 4;
        (void)_t_U32_1611;
        Str *_t_Str_1612 = Str_lit(")", 1ULL);
        (void)_t_Str_1612;
        Array_set(_va_Array_66, &_t_U32_1611, _t_Str_1612);
        ;
        Str *_t_Str_1613 = Str_lit("./src/core/vec.til:148:19", 25ULL);
        (void)_t_Str_1613;
        panic(_t_Str_1613, _va_Array_66);
        Str_delete(_t_Str_1613, &(Bool){1});
    }
    ;
    Bool _t_Bool_1625 = U32_eq(self->elem_size, src->elem_size);
    (void)_t_Bool_1625;
    Bool _t_Bool_1626 = Str_eq(&self->elem_type, &src->elem_type);
    (void)_t_Bool_1626;
    Bool _t_Bool_1627 = not(_t_Bool_1625);
    (void)_t_Bool_1627;
    ;
    Bool _t_Bool_1628 = not(_t_Bool_1626);
    (void)_t_Bool_1628;
    ;
    Bool _t_Bool_1629 = or(_t_Bool_1627, _t_Bool_1628);
    (void)_t_Bool_1629;
    ;
    ;
    if (_t_Bool_1629) {
        Str *_t_Str_1614 = Str_lit("Str", 3ULL);
        (void)_t_Str_1614;
        U32 _t_U32_1615 = 16;
        (void)_t_U32_1615;
        U32 _t_U32_1616 = 1;
        (void)_t_U32_1616;
        Array *_va_Array_67 = Array_new(_t_Str_1614, &_t_U32_1615, &_t_U32_1616);
        (void)_va_Array_67;
        Str_delete(_t_Str_1614, &(Bool){1});
        ;
        ;
        U32 _t_U32_1617 = 0;
        (void)_t_U32_1617;
        Str *_t_Str_1618 = Str_lit("Vec.push_take: incompatible vecs", 32ULL);
        (void)_t_Str_1618;
        Array_set(_va_Array_67, &_t_U32_1617, _t_Str_1618);
        ;
        Str *_t_Str_1619 = Str_lit("./src/core/vec.til:151:19", 25ULL);
        (void)_t_Str_1619;
        panic(_t_Str_1619, _va_Array_67);
        Str_delete(_t_Str_1619, &(Bool){1});
    }
    ;
    Bool _t_Bool_1630 = U32_eq(self->count, self->cap);
    (void)_t_Bool_1630;
    if (_t_Bool_1630) {
        U32 _t_U32_1620 = 2;
        (void)_t_U32_1620;
        U32 new_cap = U32_mul(self->cap, _t_U32_1620);
        (void)new_cap;
        ;
        U32 _t_U64_1621 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1621;
        void * _t_v_1622 = realloc(self->data, _t_U64_1621);
        (void)_t_v_1622;
        ;
        self->data = _t_v_1622;
        U32 _t_U32_1623 = U32_clone(&new_cap);
        (void)_t_U32_1623;
        ;
        self->cap = _t_U32_1623;
        ;
    }
    ;
    U32 _t_U64_1631 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_1631;
    U32 _t_U64_1632 = U32_mul(i, src->elem_size);
    (void)_t_U64_1632;
    void *_t_v_1633 = ptr_add(self->data, _t_U64_1631);
    (void)_t_v_1633;
    void *_t_v_1634 = ptr_add(src->data, _t_U64_1632);
    (void)_t_v_1634;
    memcpy(_t_v_1633, _t_v_1634, self->elem_size);
    ;
    ;
    U32 _t_U64_1635 = U32_mul(i, src->elem_size);
    (void)_t_U64_1635;
    void *_t_v_1636 = ptr_add(src->data, _t_U64_1635);
    (void)_t_v_1636;
    I32 _t_I32_1637 = 0;
    (void)_t_I32_1637;
    memset(_t_v_1636, _t_I32_1637, src->elem_size);
    ;
    ;
    U32 _t_U32_1638 = 1;
    (void)_t_U32_1638;
    U32 _t_U32_1639 = U32_add(self->count, _t_U32_1638);
    (void)_t_U32_1639;
    ;
    self->count = _t_U32_1639;
    ;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_1651 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1651;
    Str *_t_Str_1652 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1652;
    Bool _t_Bool_1653 = Str_eq(&self->elem_type, _t_Str_1652);
    (void)_t_Bool_1653;
    Str_delete(_t_Str_1652, &(Bool){1});
    Bool _t_Bool_1654 = not(_t_Bool_1651);
    (void)_t_Bool_1654;
    ;
    Bool _t_Bool_1655 = not(_t_Bool_1653);
    (void)_t_Bool_1655;
    ;
    Bool _t_Bool_1656 = and(_t_Bool_1654, _t_Bool_1655);
    (void)_t_Bool_1656;
    ;
    ;
    if (_t_Bool_1656) {
        {
            U32 _re_U32_1640 = self->count;
            (void)_re_U32_1640;
            U32 _rc_U32_1640 = 0;
            (void)_rc_U32_1640;
            Bool _t_Bool_1649 = U32_lte(&_rc_U32_1640, &_re_U32_1640);
            (void)_t_Bool_1649;
            if (_t_Bool_1649) {
                while (1) {
                    Bool _wcond_Bool_1641 = U32_lt(&_rc_U32_1640, &_re_U32_1640);
                    (void)_wcond_Bool_1641;
                    if (_wcond_Bool_1641) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1640);
                    (void)i;
                    U32_inc(&_rc_U32_1640);
                    U32 _t_U64_1642 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1642;
                    ;
                    void *_t_v_1643 = ptr_add(self->data, _t_U64_1642);
                    (void)_t_v_1643;
                    Bool _t_Bool_1644 = 0;
                    (void)_t_Bool_1644;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1643, &_t_Bool_1644);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1645 = U32_gt(&_rc_U32_1640, &_re_U32_1640);
                    (void)_wcond_Bool_1645;
                    if (_wcond_Bool_1645) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1640);
                    (void)i;
                    U32_dec(&_rc_U32_1640);
                    U32 _t_U64_1646 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1646;
                    ;
                    void *_t_v_1647 = ptr_add(self->data, _t_U64_1646);
                    (void)_t_v_1647;
                    Bool _t_Bool_1648 = 0;
                    (void)_t_Bool_1648;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1647, &_t_Bool_1648);
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
    Bool _t_Bool_1657 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1657;
    Bool _t_Bool_1658 = not(_t_Bool_1657);
    (void)_t_Bool_1658;
    ;
    if (_t_Bool_1658) {
        Bool _t_Bool_1650 = 0;
        (void)_t_Bool_1650;
        Str_delete(&self->elem_type, &_t_Bool_1650);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U32 _t_U64_1672 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_1672;
    void * new_data = malloc(_t_U64_1672);
    (void)new_data;
    ;
    Bool _t_Bool_1673 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1673;
    Str *_t_Str_1674 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1674;
    Bool _t_Bool_1675 = Str_eq(&self->elem_type, _t_Str_1674);
    (void)_t_Bool_1675;
    Str_delete(_t_Str_1674, &(Bool){1});
    Bool _t_Bool_1676 = not(_t_Bool_1673);
    (void)_t_Bool_1676;
    ;
    Bool _t_Bool_1677 = not(_t_Bool_1675);
    (void)_t_Bool_1677;
    ;
    Bool _t_Bool_1678 = and(_t_Bool_1676, _t_Bool_1677);
    (void)_t_Bool_1678;
    ;
    ;
    if (_t_Bool_1678) {
        {
            U32 _re_U32_1659 = self->count;
            (void)_re_U32_1659;
            U32 _rc_U32_1659 = 0;
            (void)_rc_U32_1659;
            Bool _t_Bool_1670 = U32_lte(&_rc_U32_1659, &_re_U32_1659);
            (void)_t_Bool_1670;
            if (_t_Bool_1670) {
                while (1) {
                    Bool _wcond_Bool_1660 = U32_lt(&_rc_U32_1659, &_re_U32_1659);
                    (void)_wcond_Bool_1660;
                    if (_wcond_Bool_1660) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1659);
                    (void)i;
                    U32_inc(&_rc_U32_1659);
                    U32 _t_U64_1661 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1661;
                    void *_t_v_1662 = ptr_add(self->data, _t_U64_1661);
                    (void)_t_v_1662;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1662);
                    (void)cloned;
                    ;
                    U32 _t_U64_1663 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1663;
                    ;
                    void *_t_v_1664 = ptr_add(new_data, _t_U64_1663);
                    (void)_t_v_1664;
                    memcpy(_t_v_1664, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1665 = U32_gt(&_rc_U32_1659, &_re_U32_1659);
                    (void)_wcond_Bool_1665;
                    if (_wcond_Bool_1665) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1659);
                    (void)i;
                    U32_dec(&_rc_U32_1659);
                    U32 _t_U64_1666 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1666;
                    void *_t_v_1667 = ptr_add(self->data, _t_U64_1666);
                    (void)_t_v_1667;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1667);
                    (void)cloned;
                    ;
                    U32 _t_U64_1668 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1668;
                    ;
                    void *_t_v_1669 = ptr_add(new_data, _t_U64_1668);
                    (void)_t_v_1669;
                    memcpy(_t_v_1669, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            }
            ;
            ;
            ;
        }
    } else {
        U32 _t_U64_1671 = U32_mul(self->count, self->elem_size);
        (void)_t_U64_1671;
        memcpy(new_data, self->data, _t_U64_1671);
        ;
    }
    ;
    Vec *_t_Vec_1679 = malloc(sizeof(Vec));
    _t_Vec_1679->data = new_data;
    _t_Vec_1679->count = self->count;
    _t_Vec_1679->cap = self->cap;
    _t_Vec_1679->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_1679->elem_type = *_ca; free(_ca); }
    _t_Vec_1679->elem_clone = (void *)self->elem_clone;
    _t_Vec_1679->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_1679;
    return _t_Vec_1679;
}

U32 Vec_size(void) {
    I64 _t_I64_1680 = 56;
    (void)_t_I64_1680;
    return _t_I64_1680;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_1918 = Str_lit("Str", 3ULL);
    (void)_t_Str_1918;
    U32 _t_U32_1919 = 16;
    (void)_t_U32_1919;
    U32 _t_U32_1920 = 3;
    (void)_t_U32_1920;
    Array *_va_Array_73 = Array_new(_t_Str_1918, &_t_U32_1919, &_t_U32_1920);
    (void)_va_Array_73;
    Str_delete(_t_Str_1918, &(Bool){1});
    ;
    ;
    U32 _t_U32_1921 = 0;
    (void)_t_U32_1921;
    Str *_t_Str_1922 = Str_clone(loc_str);
    (void)_t_Str_1922;
    Array_set(_va_Array_73, &_t_U32_1921, _t_Str_1922);
    ;
    U32 _t_U32_1923 = 1;
    (void)_t_U32_1923;
    Str *_t_Str_1924 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_1924;
    Array_set(_va_Array_73, &_t_U32_1923, _t_Str_1924);
    ;
    U32 _t_U32_1925 = 2;
    (void)_t_U32_1925;
    Str *_t_Str_1926 = format(parts);
    (void)_t_Str_1926;
    Array_set(_va_Array_73, &_t_U32_1925, _t_Str_1926);
    ;
    println(_va_Array_73);
    I64 _t_I64_1927 = 1;
    (void)_t_I64_1927;
    exit(_t_I64_1927);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_1945 = not(DEREF(cond));
    (void)_t_Bool_1945;
    if (_t_Bool_1945) {
        Str *_t_Str_1940 = Str_lit("Str", 3ULL);
        (void)_t_Str_1940;
        U32 _t_U32_1941 = 16;
        (void)_t_U32_1941;
        U32 _t_U32_1942 = 1;
        (void)_t_U32_1942;
        Array *_va_Array_76 = Array_new(_t_Str_1940, &_t_U32_1941, &_t_U32_1942);
        (void)_va_Array_76;
        Str_delete(_t_Str_1940, &(Bool){1});
        ;
        ;
        U32 _t_U32_1943 = 0;
        (void)_t_U32_1943;
        Str *_t_Str_1944 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_1944;
        Array_set(_va_Array_76, &_t_U32_1943, _t_Str_1944);
        ;
        panic(loc_str, _va_Array_76);
    }
    ;
    Bool _t_Bool_1946 = 1;
    (void)_t_Bool_1946;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_1946; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_1968 = I64_neq(a, b);
    (void)_t_Bool_1968;
    if (_t_Bool_1968) {
        Str *_t_Str_1955 = Str_lit("Str", 3ULL);
        (void)_t_Str_1955;
        U32 _t_U32_1956 = 16;
        (void)_t_U32_1956;
        U32 _t_U32_1957 = 5;
        (void)_t_U32_1957;
        Array *_va_Array_78 = Array_new(_t_Str_1955, &_t_U32_1956, &_t_U32_1957);
        (void)_va_Array_78;
        Str_delete(_t_Str_1955, &(Bool){1});
        ;
        ;
        U32 _t_U32_1958 = 0;
        (void)_t_U32_1958;
        Str *_t_Str_1959 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_1959;
        Array_set(_va_Array_78, &_t_U32_1958, _t_Str_1959);
        ;
        U32 _t_U32_1960 = 1;
        (void)_t_U32_1960;
        Str *_t_Str_1961 = I64_to_str(a);
        (void)_t_Str_1961;
        Array_set(_va_Array_78, &_t_U32_1960, _t_Str_1961);
        ;
        U32 _t_U32_1962 = 2;
        (void)_t_U32_1962;
        Str *_t_Str_1963 = Str_lit("', found '", 10ULL);
        (void)_t_Str_1963;
        Array_set(_va_Array_78, &_t_U32_1962, _t_Str_1963);
        ;
        U32 _t_U32_1964 = 3;
        (void)_t_U32_1964;
        Str *_t_Str_1965 = I64_to_str(b);
        (void)_t_Str_1965;
        Array_set(_va_Array_78, &_t_U32_1964, _t_Str_1965);
        ;
        U32 _t_U32_1966 = 4;
        (void)_t_U32_1966;
        Str *_t_Str_1967 = Str_lit("'", 1ULL);
        (void)_t_Str_1967;
        Array_set(_va_Array_78, &_t_U32_1966, _t_Str_1967);
        ;
        panic(loc_str, _va_Array_78);
    }
    ;
}

F32 * F32_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func F32_from_i64_ext */
    F32 _t_F32_1984 = F32_from_i64_ext(val);
    (void)_t_F32_1984;
    { F32 *_r = malloc(sizeof(F32)); *_r = _t_F32_1984; return _r; }
}

void F32_delete(F32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * F32_size(void) {
    I64 _t_I64_1985 = 4;
    (void)_t_I64_1985;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_1985; return _r; }
}

Bool F32_lt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_1986 = 0;
    (void)_t_I64_1986;
    I64 _t_I64_1987 = 1;
    (void)_t_I64_1987;
    I64 _t_I64_1988 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_1988;
    I64 _t_I64_1989 = I64_sub(_t_I64_1986, _t_I64_1987);
    (void)_t_I64_1989;
    ;
    ;
    Bool _t_Bool_1990 = I64_eq(_t_I64_1988, _t_I64_1989);
    (void)_t_Bool_1990;
    ;
    ;
    return _t_Bool_1990;
}

Bool F32_gt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_1991 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_1991;
    I64 _t_I64_1992 = 1;
    (void)_t_I64_1992;
    Bool _t_Bool_1993 = I64_eq(_t_I64_1991, _t_I64_1992);
    (void)_t_Bool_1993;
    ;
    ;
    return _t_Bool_1993;
}

Bool F32_neq(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1994 = F32_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_1994;
    Bool _t_Bool_1995 = not(_t_Bool_1994);
    (void)_t_Bool_1995;
    ;
    return _t_Bool_1995;
}

Bool F32_lte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1996 = F32_gt(a, b);
    (void)_t_Bool_1996;
    Bool _t_Bool_1997 = not(_t_Bool_1996);
    (void)_t_Bool_1997;
    ;
    return _t_Bool_1997;
}

Bool F32_gte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1998 = F32_lt(a, b);
    (void)_t_Bool_1998;
    Bool _t_Bool_1999 = not(_t_Bool_1998);
    (void)_t_Bool_1999;
    ;
    return _t_Bool_1999;
}

Str * I16_to_str(I16 * val) {
    (void)val;
    I64 _t_I64_2000 = I16_to_i64(DEREF(val));
    (void)_t_I64_2000;
    Str *_t_Str_2001 = I64_to_str(&_t_I64_2000);
    (void)_t_Str_2001;
    ;
    return _t_Str_2001;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t_I16_2002 = 1;
    (void)_t_I16_2002;
    I16 _t_I16_2003 = I16_add(DEREF(self), _t_I16_2002);
    (void)_t_I16_2003;
    ;
    *self = _t_I16_2003;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t_I16_2004 = 1;
    (void)_t_I16_2004;
    I16 _t_I16_2005 = I16_sub(DEREF(self), _t_I16_2004);
    (void)_t_I16_2005;
    ;
    *self = _t_I16_2005;
    ;
}

I16 * I16_unity(I16 * _self) {
    (void)_self;
    I64 _t_I64_2006 = 1;
    (void)_t_I64_2006;
    I16 _t_I16_2007 = I64_to_i16(_t_I64_2006);
    (void)_t_I16_2007;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2007; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t_I64_2008 = 0;
    (void)_t_I64_2008;
    I64 _t_I64_2009 = I16_to_i64(DEREF(a));
    (void)_t_I64_2009;
    I64 _t_I64_2010 = I64_sub(_t_I64_2008, _t_I64_2009);
    (void)_t_I64_2010;
    ;
    ;
    I16 _t_I16_2011 = I64_to_i16(_t_I64_2010);
    (void)_t_I16_2011;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2011; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t_I64_2016 = I16_to_i64(DEREF(a));
    (void)_t_I64_2016;
    I64 _t_I64_2017 = 0;
    (void)_t_I64_2017;
    Bool _t_Bool_2018 = I64_lt(&_t_I64_2016, &_t_I64_2017);
    (void)_t_Bool_2018;
    ;
    ;
    if (_t_Bool_2018) {
        I64 _t_I64_2012 = 0;
        (void)_t_I64_2012;
        I64 _t_I64_2013 = I16_to_i64(DEREF(a));
        (void)_t_I64_2013;
        I64 _t_I64_2014 = I64_sub(_t_I64_2012, _t_I64_2013);
        (void)_t_I64_2014;
        ;
        ;
        I16 _t_I16_2015 = I64_to_i16(_t_I64_2014);
        (void)_t_I16_2015;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2015; return _r; }
    }
    ;
    I16 _t_I16_2019 = I16_clone(a);
    (void)_t_I16_2019;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2019; return _r; }
}

U64 I16_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I16 *au = a;
    (void)au;
    I16 *bu = b;
    (void)bu;
    Bool _t_Bool_2023 = I16_lte(au, bu);
    (void)_t_Bool_2023;
    if (_t_Bool_2023) {
        I16 _t_I16_2020 = I16_sub(DEREF(bu), DEREF(au));
        (void)_t_I16_2020;
        I64 _t_I64_2021 = I16_to_i64(_t_I16_2020);
        (void)_t_I64_2021;
        ;
        U64 _t_U64_2022 = I64_to_u64(_t_I64_2021);
        (void)_t_U64_2022;
        ;
        ;
        return _t_U64_2022;
    }
    ;
    I16 _t_I16_2024 = I16_sub(DEREF(au), DEREF(bu));
    (void)_t_I16_2024;
    I64 _t_I64_2025 = I16_to_i64(_t_I16_2024);
    (void)_t_I64_2025;
    ;
    U64 _t_U64_2026 = I64_to_u64(_t_I64_2025);
    (void)_t_U64_2026;
    ;
    return _t_U64_2026;
}

void I16_delete(I16 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I16_size(void) {
    I64 _t_I64_2027 = 2;
    (void)_t_I64_2027;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2027; return _r; }
}

Bool I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2028 = 0;
    (void)_t_I64_2028;
    I64 _t_I64_2029 = 1;
    (void)_t_I64_2029;
    I64 _t_I64_2030 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2030;
    I64 _t_I64_2031 = I64_sub(_t_I64_2028, _t_I64_2029);
    (void)_t_I64_2031;
    ;
    ;
    Bool _t_Bool_2032 = I64_eq(_t_I64_2030, _t_I64_2031);
    (void)_t_Bool_2032;
    ;
    ;
    return _t_Bool_2032;
}

Bool I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2033 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2033;
    I64 _t_I64_2034 = 1;
    (void)_t_I64_2034;
    Bool _t_Bool_2035 = I64_eq(_t_I64_2033, _t_I64_2034);
    (void)_t_Bool_2035;
    ;
    ;
    return _t_Bool_2035;
}

Bool I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2036 = I16_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2036;
    Bool _t_Bool_2037 = not(_t_Bool_2036);
    (void)_t_Bool_2037;
    ;
    return _t_Bool_2037;
}

Bool I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2038 = I16_gt(a, b);
    (void)_t_Bool_2038;
    Bool _t_Bool_2039 = not(_t_Bool_2038);
    (void)_t_Bool_2039;
    ;
    return _t_Bool_2039;
}

Bool I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2040 = I16_lt(a, b);
    (void)_t_Bool_2040;
    Bool _t_Bool_2041 = not(_t_Bool_2040);
    (void)_t_Bool_2041;
    ;
    return _t_Bool_2041;
}

Str * I32_to_str(I32 * val) {
    (void)val;
    I64 _t_I64_2042 = I32_to_i64(DEREF(val));
    (void)_t_I64_2042;
    Str *_t_Str_2043 = I64_to_str(&_t_I64_2042);
    (void)_t_Str_2043;
    ;
    return _t_Str_2043;
}

void I32_inc(I32 * self) {
    (void)self;
    I32 _t_I32_2044 = 1;
    (void)_t_I32_2044;
    I32 _t_I32_2045 = I32_add(DEREF(self), _t_I32_2044);
    (void)_t_I32_2045;
    ;
    *self = _t_I32_2045;
    ;
}

void I32_dec(I32 * self) {
    (void)self;
    I32 _t_I32_2046 = 1;
    (void)_t_I32_2046;
    I32 _t_I32_2047 = I32_sub(DEREF(self), _t_I32_2046);
    (void)_t_I32_2047;
    ;
    *self = _t_I32_2047;
    ;
}

I32 * I32_unity(I32 * _self) {
    (void)_self;
    I64 _t_I64_2048 = 1;
    (void)_t_I64_2048;
    I32 _t_I32_2049 = I64_to_i32(_t_I64_2048);
    (void)_t_I32_2049;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_2049; return _r; }
}

I32 * I32_neg(I32 * a) {
    (void)a;
    I64 _t_I64_2050 = 0;
    (void)_t_I64_2050;
    I64 _t_I64_2051 = I32_to_i64(DEREF(a));
    (void)_t_I64_2051;
    I64 _t_I64_2052 = I64_sub(_t_I64_2050, _t_I64_2051);
    (void)_t_I64_2052;
    ;
    ;
    I32 _t_I32_2053 = I64_to_i32(_t_I64_2052);
    (void)_t_I32_2053;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_2053; return _r; }
}

I32 * I32_abs(I32 * a) {
    (void)a;
    I64 _t_I64_2058 = I32_to_i64(DEREF(a));
    (void)_t_I64_2058;
    I64 _t_I64_2059 = 0;
    (void)_t_I64_2059;
    Bool _t_Bool_2060 = I64_lt(&_t_I64_2058, &_t_I64_2059);
    (void)_t_Bool_2060;
    ;
    ;
    if (_t_Bool_2060) {
        I64 _t_I64_2054 = 0;
        (void)_t_I64_2054;
        I64 _t_I64_2055 = I32_to_i64(DEREF(a));
        (void)_t_I64_2055;
        I64 _t_I64_2056 = I64_sub(_t_I64_2054, _t_I64_2055);
        (void)_t_I64_2056;
        ;
        ;
        I32 _t_I32_2057 = I64_to_i32(_t_I64_2056);
        (void)_t_I32_2057;
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_2057; return _r; }
    }
    ;
    I32 _t_I32_2061 = I32_clone(a);
    (void)_t_I32_2061;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_2061; return _r; }
}

U64 I32_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I32 *au = a;
    (void)au;
    I32 *bu = b;
    (void)bu;
    Bool _t_Bool_2065 = I32_lte(au, bu);
    (void)_t_Bool_2065;
    if (_t_Bool_2065) {
        I32 _t_I32_2062 = I32_sub(DEREF(bu), DEREF(au));
        (void)_t_I32_2062;
        I64 _t_I64_2063 = I32_to_i64(_t_I32_2062);
        (void)_t_I64_2063;
        ;
        U64 _t_U64_2064 = I64_to_u64(_t_I64_2063);
        (void)_t_U64_2064;
        ;
        ;
        return _t_U64_2064;
    }
    ;
    I32 _t_I32_2066 = I32_sub(DEREF(au), DEREF(bu));
    (void)_t_I32_2066;
    I64 _t_I64_2067 = I32_to_i64(_t_I32_2066);
    (void)_t_I64_2067;
    ;
    U64 _t_U64_2068 = I64_to_u64(_t_I64_2067);
    (void)_t_U64_2068;
    ;
    return _t_U64_2068;
}

void I32_delete(I32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I32_size(void) {
    I64 _t_I64_2069 = 4;
    (void)_t_I64_2069;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2069; return _r; }
}

Bool I32_lt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2070 = 0;
    (void)_t_I64_2070;
    I64 _t_I64_2071 = 1;
    (void)_t_I64_2071;
    I64 _t_I64_2072 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2072;
    I64 _t_I64_2073 = I64_sub(_t_I64_2070, _t_I64_2071);
    (void)_t_I64_2073;
    ;
    ;
    Bool _t_Bool_2074 = I64_eq(_t_I64_2072, _t_I64_2073);
    (void)_t_Bool_2074;
    ;
    ;
    return _t_Bool_2074;
}

Bool I32_gt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2075 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2075;
    I64 _t_I64_2076 = 1;
    (void)_t_I64_2076;
    Bool _t_Bool_2077 = I64_eq(_t_I64_2075, _t_I64_2076);
    (void)_t_Bool_2077;
    ;
    ;
    return _t_Bool_2077;
}

Bool I32_neq(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2078 = I32_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2078;
    Bool _t_Bool_2079 = not(_t_Bool_2078);
    (void)_t_Bool_2079;
    ;
    return _t_Bool_2079;
}

Bool I32_lte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2080 = I32_gt(a, b);
    (void)_t_Bool_2080;
    Bool _t_Bool_2081 = not(_t_Bool_2080);
    (void)_t_Bool_2081;
    ;
    return _t_Bool_2081;
}

Bool I32_gte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2082 = I32_lt(a, b);
    (void)_t_Bool_2082;
    Bool _t_Bool_2083 = not(_t_Bool_2082);
    (void)_t_Bool_2083;
    ;
    return _t_Bool_2083;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_2120 = 0;
    (void)_t_I64_2120;
    Bool _t_Bool_2121 = I64_eq(DEREF(val), _t_I64_2120);
    (void)_t_Bool_2121;
    ;
    if (_t_Bool_2121) {
        U64 _t_U64_2084 = 2;
        (void)_t_U64_2084;
        void * buf = malloc(_t_U64_2084);
        (void)buf;
        ;
        I64 _t_I64_2085 = 48;
        (void)_t_I64_2085;
        U64 _t_U64_2086 = 1;
        (void)_t_U64_2086;
        memcpy(buf, &_t_I64_2085, _t_U64_2086);
        ;
        ;
        U64 _t_U64_2087 = 1;
        (void)_t_U64_2087;
        void *_t_v_2088 = ptr_add(buf, _t_U64_2087);
        (void)_t_v_2088;
        I32 _t_I32_2089 = 0;
        (void)_t_I32_2089;
        U64 _t_U64_2090 = 1;
        (void)_t_U64_2090;
        memset(_t_v_2088, _t_I32_2089, _t_U64_2090);
        ;
        ;
        ;
        I64 _t_I64_2091 = 1;
        (void)_t_I64_2091;
        I64 _t_I64_2092 = 1;
        (void)_t_I64_2092;
        Str *_t_Str_2093 = malloc(sizeof(Str));
        _t_Str_2093->c_str = buf;
        _t_Str_2093->count = _t_I64_2091;
        _t_Str_2093->cap = _t_I64_2092;
        (void)_t_Str_2093;
        ;
        ;
        ;
        return _t_Str_2093;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t_I64_2122 = 0;
    (void)_t_I64_2122;
    Bool _t_Bool_2123 = I64_lt(val, &_t_I64_2122);
    (void)_t_Bool_2123;
    ;
    if (_t_Bool_2123) {
        Bool _t_Bool_2094 = 1;
        (void)_t_Bool_2094;
        is_neg = _t_Bool_2094;
        ;
        I64 _t_I64_2095 = 0;
        (void)_t_I64_2095;
        I64 _t_I64_2096 = I64_sub(_t_I64_2095, DEREF(val));
        (void)_t_I64_2096;
        ;
        v = _t_I64_2096;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&v);
    (void)tmp;
    while (1) {
        I64 _t_I64_2098 = 0;
        (void)_t_I64_2098;
        Bool _wcond_Bool_2097 = I64_gt(&tmp, &_t_I64_2098);
        (void)_wcond_Bool_2097;
        ;
        if (_wcond_Bool_2097) {
        } else {
            ;
            break;
        }
        ;
        U64 _t_U64_2099 = 1;
        (void)_t_U64_2099;
        U64 _t_U64_2100 = U64_add(ndigits, _t_U64_2099);
        (void)_t_U64_2100;
        ;
        ndigits = _t_U64_2100;
        ;
        I64 _t_I64_2101 = 10;
        (void)_t_I64_2101;
        I64 _t_I64_2102 = I64_div(tmp, _t_I64_2101);
        (void)_t_I64_2102;
        ;
        tmp = _t_I64_2102;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    (void)total;
    ;
    if (is_neg) {
        U64 _t_U64_2103 = 1;
        (void)_t_U64_2103;
        U64 _t_U64_2104 = U64_add(total, _t_U64_2103);
        (void)_t_U64_2104;
        ;
        total = _t_U64_2104;
        ;
    }
    U64 _t_U64_2124 = 1;
    (void)_t_U64_2124;
    U64 _t_U64_2125 = U64_add(total, _t_U64_2124);
    (void)_t_U64_2125;
    ;
    void * buf = malloc(_t_U64_2125);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t_I64_2105 = 45;
        (void)_t_I64_2105;
        U64 _t_U64_2106 = 1;
        (void)_t_U64_2106;
        memcpy(buf, &_t_I64_2105, _t_U64_2106);
        ;
        ;
    }
    ;
    U64 _t_U64_2126 = 1;
    (void)_t_U64_2126;
    U64 i = U64_sub(total, _t_U64_2126);
    (void)i;
    ;
    while (1) {
        I64 _t_I64_2108 = 0;
        (void)_t_I64_2108;
        Bool _wcond_Bool_2107 = I64_gt(&v, &_t_I64_2108);
        (void)_wcond_Bool_2107;
        ;
        if (_wcond_Bool_2107) {
        } else {
            ;
            break;
        }
        ;
        I64 _t_I64_2109 = 10;
        (void)_t_I64_2109;
        I64 _t_I64_2110 = I64_mod(v, _t_I64_2109);
        (void)_t_I64_2110;
        ;
        I64 _t_I64_2111 = 48;
        (void)_t_I64_2111;
        I64 _t_I64_2112 = I64_add(_t_I64_2110, _t_I64_2111);
        (void)_t_I64_2112;
        ;
        ;
        void *_t_v_2113 = ptr_add(buf, i);
        (void)_t_v_2113;
        U8 _t_U8_2114 = I64_to_u8(_t_I64_2112);
        (void)_t_U8_2114;
        ;
        U64 _t_U64_2115 = 1;
        (void)_t_U64_2115;
        memcpy(_t_v_2113, &_t_U8_2114, _t_U64_2115);
        ;
        ;
        I64 _t_I64_2116 = 10;
        (void)_t_I64_2116;
        I64 _t_I64_2117 = I64_div(v, _t_I64_2116);
        (void)_t_I64_2117;
        ;
        v = _t_I64_2117;
        ;
        U64 _t_U64_2118 = 1;
        (void)_t_U64_2118;
        U64 _t_U64_2119 = U64_sub(i, _t_U64_2118);
        (void)_t_U64_2119;
        ;
        i = _t_U64_2119;
        ;
    }
    ;
    ;
    void *_t_v_2127 = ptr_add(buf, total);
    (void)_t_v_2127;
    I32 _t_I32_2128 = 0;
    (void)_t_I32_2128;
    U64 _t_U64_2129 = 1;
    (void)_t_U64_2129;
    memset(_t_v_2127, _t_I32_2128, _t_U64_2129);
    ;
    ;
    Str *_t_Str_2130 = malloc(sizeof(Str));
    _t_Str_2130->c_str = buf;
    _t_Str_2130->count = total;
    _t_Str_2130->cap = total;
    (void)_t_Str_2130;
    ;
    return _t_Str_2130;
}

U32 I64_to_usize(I64 val) {
    (void)val;
    U32 _t_U32_2131 = I64_to_u32(val);
    (void)_t_U32_2131;
    return _t_U32_2131;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t_I64_2132 = 1;
    (void)_t_I64_2132;
    I64 _t_I64_2133 = I64_add(DEREF(self), _t_I64_2132);
    (void)_t_I64_2133;
    ;
    *self = _t_I64_2133;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t_I64_2134 = 1;
    (void)_t_I64_2134;
    I64 _t_I64_2135 = I64_sub(DEREF(self), _t_I64_2134);
    (void)_t_I64_2135;
    ;
    *self = _t_I64_2135;
    ;
}

I64 * I64_unity(I64 * _self) {
    (void)_self;
    I64 _t_I64_2136 = 1;
    (void)_t_I64_2136;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2136; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t_I64_2137 = 0;
    (void)_t_I64_2137;
    I64 _t_I64_2138 = I64_sub(_t_I64_2137, DEREF(a));
    (void)_t_I64_2138;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2138; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t_I64_2141 = 0;
    (void)_t_I64_2141;
    Bool _t_Bool_2142 = I64_lt(a, &_t_I64_2141);
    (void)_t_Bool_2142;
    ;
    if (_t_Bool_2142) {
        I64 _t_I64_2139 = 0;
        (void)_t_I64_2139;
        I64 _t_I64_2140 = I64_sub(_t_I64_2139, DEREF(a));
        (void)_t_I64_2140;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2140; return _r; }
    }
    ;
    I64 _t_I64_2143 = I64_clone(a);
    (void)_t_I64_2143;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2143; return _r; }
}

U64 I64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I64 *au = a;
    (void)au;
    I64 *bu = b;
    (void)bu;
    Bool _t_Bool_2146 = I64_lte(au, bu);
    (void)_t_Bool_2146;
    if (_t_Bool_2146) {
        I64 _t_I64_2144 = I64_sub(DEREF(bu), DEREF(au));
        (void)_t_I64_2144;
        U64 _t_U64_2145 = I64_to_u64(_t_I64_2144);
        (void)_t_U64_2145;
        ;
        ;
        return _t_U64_2145;
    }
    ;
    I64 _t_I64_2147 = I64_sub(DEREF(au), DEREF(bu));
    (void)_t_I64_2147;
    U64 _t_U64_2148 = I64_to_u64(_t_I64_2147);
    (void)_t_U64_2148;
    ;
    return _t_U64_2148;
}

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_2149 = 8;
    (void)_t_I64_2149;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2149; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2150 = 0;
    (void)_t_I64_2150;
    I64 _t_I64_2151 = 1;
    (void)_t_I64_2151;
    I64 _t_I64_2152 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2152;
    I64 _t_I64_2153 = I64_sub(_t_I64_2150, _t_I64_2151);
    (void)_t_I64_2153;
    ;
    ;
    Bool _t_Bool_2154 = I64_eq(_t_I64_2152, _t_I64_2153);
    (void)_t_Bool_2154;
    ;
    ;
    return _t_Bool_2154;
}

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2155 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2155;
    I64 _t_I64_2156 = 1;
    (void)_t_I64_2156;
    Bool _t_Bool_2157 = I64_eq(_t_I64_2155, _t_I64_2156);
    (void)_t_Bool_2157;
    ;
    ;
    return _t_Bool_2157;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2158 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2158;
    Bool _t_Bool_2159 = not(_t_Bool_2158);
    (void)_t_Bool_2159;
    ;
    return _t_Bool_2159;
}

Bool I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2160 = I64_gt(a, b);
    (void)_t_Bool_2160;
    Bool _t_Bool_2161 = not(_t_Bool_2160);
    (void)_t_Bool_2161;
    ;
    return _t_Bool_2161;
}

Bool I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2162 = I64_lt(a, b);
    (void)_t_Bool_2162;
    Bool _t_Bool_2163 = not(_t_Bool_2162);
    (void)_t_Bool_2163;
    ;
    return _t_Bool_2163;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2164 = parts;
        (void)_fc_Array_2164;
        U32 _fi_USize_2164 = 0;
        (void)_fi_USize_2164;
        while (1) {
            U32 _t_U32_2166; { U32 *_hp = (U32 *)Array_len(_fc_Array_2164); _t_U32_2166 = *_hp; free(_hp); }
            (void)_t_U32_2166;
            Bool _wcond_Bool_2165 = U32_lt(&_fi_USize_2164, &_t_U32_2166);
            (void)_wcond_Bool_2165;
            ;
            if (_wcond_Bool_2165) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2164, &_fi_USize_2164);
            (void)s;
            U32 _t_U32_2167 = 1;
            (void)_t_U32_2167;
            U32 _t_U32_2168 = U32_add(_fi_USize_2164, _t_U32_2167);
            (void)_t_U32_2168;
            ;
            _fi_USize_2164 = _t_U32_2168;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    (void)total;
    {
        Array *_fc_Array_2310 = parts;
        (void)_fc_Array_2310;
        U32 _fi_USize_2310 = 0;
        (void)_fi_USize_2310;
        while (1) {
            U32 _t_U32_2312; { U32 *_hp = (U32 *)Array_len(_fc_Array_2310); _t_U32_2312 = *_hp; free(_hp); }
            (void)_t_U32_2312;
            Bool _wcond_Bool_2311 = U32_lt(&_fi_USize_2310, &_t_U32_2312);
            (void)_wcond_Bool_2311;
            ;
            if (_wcond_Bool_2311) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2310, &_fi_USize_2310);
            (void)s;
            U32 _t_U32_2313 = 1;
            (void)_t_U32_2313;
            U32 _t_U32_2314 = U32_add(_fi_USize_2310, _t_U32_2313);
            (void)_t_U32_2314;
            ;
            _fi_USize_2310 = _t_U32_2314;
            ;
            U32 _t_U32_2315 = Str_len(s);
            (void)_t_U32_2315;
            U32 _t_U32_2316 = U32_add(total, _t_U32_2315);
            (void)_t_U32_2316;
            ;
            total = _t_U32_2316;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    (void)out;
    ;
    {
        Array *_fc_Array_2317 = parts;
        (void)_fc_Array_2317;
        U32 _fi_USize_2317 = 0;
        (void)_fi_USize_2317;
        while (1) {
            U32 _t_U32_2319; { U32 *_hp = (U32 *)Array_len(_fc_Array_2317); _t_U32_2319 = *_hp; free(_hp); }
            (void)_t_U32_2319;
            Bool _wcond_Bool_2318 = U32_lt(&_fi_USize_2317, &_t_U32_2319);
            (void)_wcond_Bool_2318;
            ;
            if (_wcond_Bool_2318) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2317, &_fi_USize_2317);
            (void)s;
            U32 _t_U32_2320 = 1;
            (void)_t_U32_2320;
            U32 _t_U32_2321 = U32_add(_fi_USize_2317, _t_U32_2320);
            (void)_t_U32_2321;
            ;
            _fi_USize_2317 = _t_U32_2321;
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
    Bool _t_Bool_2328 = U32_gte(i, &self->count);
    (void)_t_Bool_2328;
    if (_t_Bool_2328) {
        Str *_t_Str_2322 = Str_lit("Str", 3ULL);
        (void)_t_Str_2322;
        U32 _t_U32_2323 = 16;
        (void)_t_U32_2323;
        U32 _t_U32_2324 = 1;
        (void)_t_U32_2324;
        Array *_va_Array_84 = Array_new(_t_Str_2322, &_t_U32_2323, &_t_U32_2324);
        (void)_va_Array_84;
        Str_delete(_t_Str_2322, &(Bool){1});
        ;
        ;
        U32 _t_U32_2325 = 0;
        (void)_t_U32_2325;
        Str *_t_Str_2326 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t_Str_2326;
        Array_set(_va_Array_84, &_t_U32_2325, _t_Str_2326);
        ;
        Str *_t_Str_2327 = Str_lit("./src/core/str.til:30:19", 24ULL);
        (void)_t_Str_2327;
        panic(_t_Str_2327, _va_Array_84);
        Str_delete(_t_Str_2327, &(Bool){1});
    }
    ;
    void *_t_v_2329 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_2329;
    return _t_v_2329;
}

U8 * Str_byte_at(Str * self, U32 * i) {
    (void)self;
    (void)i;
    void *_t_v_2330 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_2330;
    return _t_v_2330;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    (void)min_len;
    Bool _t_Bool_2339 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_2339;
    if (_t_Bool_2339) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_2331 = U32_clone(&min_len);
        (void)_re_U32_2331;
        U32 _rc_U32_2331 = 0;
        (void)_rc_U32_2331;
        Bool _t_Bool_2338 = U32_lte(&_rc_U32_2331, &_re_U32_2331);
        (void)_t_Bool_2338;
        if (_t_Bool_2338) {
            while (1) {
                Bool _wcond_Bool_2332 = U32_lt(&_rc_U32_2331, &_re_U32_2331);
                (void)_wcond_Bool_2332;
                if (_wcond_Bool_2332) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2331);
                (void)i;
                U32_inc(&_rc_U32_2331);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_2333 = 0;
                (void)_t_I64_2333;
                Bool _t_Bool_2334 = I64_neq(&c, &_t_I64_2333);
                (void)_t_Bool_2334;
                ;
                if (_t_Bool_2334) {
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
                Bool _wcond_Bool_2335 = U32_gt(&_rc_U32_2331, &_re_U32_2331);
                (void)_wcond_Bool_2335;
                if (_wcond_Bool_2335) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2331);
                (void)i;
                U32_dec(&_rc_U32_2331);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_2336 = 0;
                (void)_t_I64_2336;
                Bool _t_Bool_2337 = I64_neq(&c, &_t_I64_2336);
                (void)_t_Bool_2337;
                ;
                if (_t_Bool_2337) {
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
    I64 _t_I64_2340 = U32_cmp(a->count, b->count);
    (void)_t_I64_2340;
    return _t_I64_2340;
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_2341 = U32_add(a->count, b->count);
    (void)_t_U32_2341;
    Str *out = Str_with_capacity(&_t_U32_2341);
    (void)out;
    ;
    Str_push_str(out, a);
    Str_push_str(out, b);
    return out;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_2342 = 1;
    (void)_t_U32_2342;
    U32 _t_U64_2343 = U32_add(DEREF(n), _t_U32_2342);
    (void)_t_U64_2343;
    ;
    void * buf = malloc(_t_U64_2343);
    (void)buf;
    ;
    I32 _t_I32_2344 = 0;
    (void)_t_I32_2344;
    U64 _t_U64_2345 = 1;
    (void)_t_U64_2345;
    memset(buf, _t_I32_2344, _t_U64_2345);
    ;
    ;
    I64 _t_I64_2346 = 0;
    (void)_t_I64_2346;
    Str *_t_Str_2347 = malloc(sizeof(Str));
    _t_Str_2347->c_str = buf;
    _t_Str_2347->count = _t_I64_2346;
    _t_Str_2347->cap = DEREF(n);
    (void)_t_Str_2347;
    ;
    return _t_Str_2347;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_2360 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_2360;
    if (_t_Bool_2360) {
        Str *_t_Str_2348 = Str_lit("Str", 3ULL);
        (void)_t_Str_2348;
        U32 _t_U32_2349 = 16;
        (void)_t_U32_2349;
        U32 _t_U32_2350 = 1;
        (void)_t_U32_2350;
        Array *_va_Array_85 = Array_new(_t_Str_2348, &_t_U32_2349, &_t_U32_2350);
        (void)_va_Array_85;
        Str_delete(_t_Str_2348, &(Bool){1});
        ;
        ;
        U32 _t_U32_2351 = 0;
        (void)_t_U32_2351;
        Str *_t_Str_2352 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t_Str_2352;
        Array_set(_va_Array_85, &_t_U32_2351, _t_Str_2352);
        ;
        Str *_t_Str_2353 = Str_lit("./src/core/str.til:67:19", 24ULL);
        (void)_t_Str_2353;
        panic(_t_Str_2353, _va_Array_85);
        Str_delete(_t_Str_2353, &(Bool){1});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    (void)new_len;
    Bool _t_Bool_2361 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_2361;
    if (_t_Bool_2361) {
        Str *_t_Str_2354 = Str_lit("Str", 3ULL);
        (void)_t_Str_2354;
        U32 _t_U32_2355 = 16;
        (void)_t_U32_2355;
        U32 _t_U32_2356 = 1;
        (void)_t_U32_2356;
        Array *_va_Array_86 = Array_new(_t_Str_2354, &_t_U32_2355, &_t_U32_2356);
        (void)_va_Array_86;
        Str_delete(_t_Str_2354, &(Bool){1});
        ;
        ;
        U32 _t_U32_2357 = 0;
        (void)_t_U32_2357;
        Str *_t_Str_2358 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t_Str_2358;
        Array_set(_va_Array_86, &_t_U32_2357, _t_Str_2358);
        ;
        Str *_t_Str_2359 = Str_lit("./src/core/str.til:71:19", 24ULL);
        (void)_t_Str_2359;
        panic(_t_Str_2359, _va_Array_86);
        Str_delete(_t_Str_2359, &(Bool){1});
    }
    ;
    void *_t_v_2362 = ptr_add(self->c_str, self->count);
    (void)_t_v_2362;
    memcpy(_t_v_2362, s->c_str, s->count);
    U32 _t_U32_2363 = U32_clone(&new_len);
    (void)_t_U32_2363;
    self->count = _t_U32_2363;
    ;
    void *_t_v_2364 = ptr_add(self->c_str, new_len);
    (void)_t_v_2364;
    I32 _t_I32_2365 = 0;
    (void)_t_I32_2365;
    U64 _t_U64_2366 = 1;
    (void)_t_U64_2366;
    memset(_t_v_2364, _t_I32_2365, _t_U64_2366);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_2367 = 1;
    (void)_t_U32_2367;
    U32 _t_U64_2368 = U32_add(val->count, _t_U32_2367);
    (void)_t_U64_2368;
    ;
    void * new_data = malloc(_t_U64_2368);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_2369 = ptr_add(new_data, val->count);
    (void)_t_v_2369;
    I32 _t_I32_2370 = 0;
    (void)_t_I32_2370;
    U64 _t_U64_2371 = 1;
    (void)_t_U64_2371;
    memset(_t_v_2369, _t_I32_2370, _t_U64_2371);
    ;
    ;
    Str *_t_Str_2372 = malloc(sizeof(Str));
    _t_Str_2372->c_str = new_data;
    _t_Str_2372->count = val->count;
    _t_Str_2372->cap = val->count;
    (void)_t_Str_2372;
    return _t_Str_2372;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_2373 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_2373;
    if (_t_Bool_2373) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t_Str_2374 = Str_clone(val);
    (void)_t_Str_2374;
    return _t_Str_2374;
}

Str * Str_substr(Str * s, U32 * start, U32 * n) {
    (void)s;
    (void)start;
    (void)n;
    U32 st = U32_clone(start);
    (void)st;
    U32 ln = U32_clone(n);
    (void)ln;
    Bool _t_Bool_2376 = U32_gt(&st, &s->count);
    (void)_t_Bool_2376;
    if (_t_Bool_2376) {
        st = s->count;
    }
    ;
    U32 _t_U32_2377 = U32_add(st, ln);
    (void)_t_U32_2377;
    Bool _t_Bool_2378 = U32_gt(&_t_U32_2377, &s->count);
    (void)_t_Bool_2378;
    ;
    if (_t_Bool_2378) {
        U32 _t_U32_2375 = U32_sub(s->count, st);
        (void)_t_U32_2375;
        ln = _t_U32_2375;
        ;
    }
    ;
    void *_t_v_2379 = ptr_add(s->c_str, st);
    (void)_t_v_2379;
    Str *_t_Str_2380 = malloc(sizeof(Str));
    _t_Str_2380->c_str = _t_v_2379;
    _t_Str_2380->count = ln;
    _t_Str_2380->cap = CAP_VIEW;
    (void)_t_Str_2380;
    ;
    ;
    return _t_Str_2380;
}

Bool Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_2411 = 0;
    (void)_t_U32_2411;
    Bool _t_Bool_2412 = U32_eq(b->count, _t_U32_2411);
    (void)_t_Bool_2412;
    ;
    if (_t_Bool_2412) {
        Bool _t_Bool_2381 = 1;
        (void)_t_Bool_2381;
        ;
        return _t_Bool_2381;
    }
    ;
    Bool _t_Bool_2413 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_2413;
    if (_t_Bool_2413) {
        Bool _t_Bool_2382 = 0;
        (void)_t_Bool_2382;
        ;
        return _t_Bool_2382;
    }
    ;
    {
        U32 _t_U32_2408 = U32_sub(a->count, b->count);
        (void)_t_U32_2408;
        U32 _t_U32_2409 = 1;
        (void)_t_U32_2409;
        U32 _re_U32_2383 = U32_add(_t_U32_2408, _t_U32_2409);
        (void)_re_U32_2383;
        ;
        ;
        U32 _rc_U32_2383 = 0;
        (void)_rc_U32_2383;
        Bool _t_Bool_2410 = U32_lte(&_rc_U32_2383, &_re_U32_2383);
        (void)_t_Bool_2410;
        if (_t_Bool_2410) {
            while (1) {
                Bool _wcond_Bool_2384 = U32_lt(&_rc_U32_2383, &_re_U32_2383);
                (void)_wcond_Bool_2384;
                if (_wcond_Bool_2384) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2383);
                (void)i;
                U32_inc(&_rc_U32_2383);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_2385 = b->count;
                    (void)_re_U32_2385;
                    U32 _rc_U32_2385 = 0;
                    (void)_rc_U32_2385;
                    Bool _t_Bool_2394 = U32_lte(&_rc_U32_2385, &_re_U32_2385);
                    (void)_t_Bool_2394;
                    if (_t_Bool_2394) {
                        while (1) {
                            Bool _wcond_Bool_2386 = U32_lt(&_rc_U32_2385, &_re_U32_2385);
                            (void)_wcond_Bool_2386;
                            if (_wcond_Bool_2386) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2385);
                            (void)j;
                            U32_inc(&_rc_U32_2385);
                            U32 _t_U32_2388 = U32_add(i, j);
                            (void)_t_U32_2388;
                            U8 *ac = Str_get(a, &_t_U32_2388);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_2389 = U8_neq(ac, bc);
                            (void)_t_Bool_2389;
                            ;
                            ;
                            if (_t_Bool_2389) {
                                Bool _t_Bool_2387 = 0;
                                (void)_t_Bool_2387;
                                found = _t_Bool_2387;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_2390 = U32_gt(&_rc_U32_2385, &_re_U32_2385);
                            (void)_wcond_Bool_2390;
                            if (_wcond_Bool_2390) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2385);
                            (void)j;
                            U32_dec(&_rc_U32_2385);
                            U32 _t_U32_2392 = U32_add(i, j);
                            (void)_t_U32_2392;
                            U8 *ac = Str_get(a, &_t_U32_2392);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_2393 = U8_neq(ac, bc);
                            (void)_t_Bool_2393;
                            ;
                            ;
                            if (_t_Bool_2393) {
                                Bool _t_Bool_2391 = 0;
                                (void)_t_Bool_2391;
                                found = _t_Bool_2391;
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
                    Bool _t_Bool_2395 = 1;
                    (void)_t_Bool_2395;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_2395;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2396 = U32_gt(&_rc_U32_2383, &_re_U32_2383);
                (void)_wcond_Bool_2396;
                if (_wcond_Bool_2396) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2383);
                (void)i;
                U32_dec(&_rc_U32_2383);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_2397 = b->count;
                    (void)_re_U32_2397;
                    U32 _rc_U32_2397 = 0;
                    (void)_rc_U32_2397;
                    Bool _t_Bool_2406 = U32_lte(&_rc_U32_2397, &_re_U32_2397);
                    (void)_t_Bool_2406;
                    if (_t_Bool_2406) {
                        while (1) {
                            Bool _wcond_Bool_2398 = U32_lt(&_rc_U32_2397, &_re_U32_2397);
                            (void)_wcond_Bool_2398;
                            if (_wcond_Bool_2398) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2397);
                            (void)j;
                            U32_inc(&_rc_U32_2397);
                            U32 _t_U32_2400 = U32_add(i, j);
                            (void)_t_U32_2400;
                            U8 *ac = Str_get(a, &_t_U32_2400);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_2401 = U8_neq(ac, bc);
                            (void)_t_Bool_2401;
                            ;
                            ;
                            if (_t_Bool_2401) {
                                Bool _t_Bool_2399 = 0;
                                (void)_t_Bool_2399;
                                found = _t_Bool_2399;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_2402 = U32_gt(&_rc_U32_2397, &_re_U32_2397);
                            (void)_wcond_Bool_2402;
                            if (_wcond_Bool_2402) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2397);
                            (void)j;
                            U32_dec(&_rc_U32_2397);
                            U32 _t_U32_2404 = U32_add(i, j);
                            (void)_t_U32_2404;
                            U8 *ac = Str_get(a, &_t_U32_2404);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_2405 = U8_neq(ac, bc);
                            (void)_t_Bool_2405;
                            ;
                            ;
                            if (_t_Bool_2405) {
                                Bool _t_Bool_2403 = 0;
                                (void)_t_Bool_2403;
                                found = _t_Bool_2403;
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
                    Bool _t_Bool_2407 = 1;
                    (void)_t_Bool_2407;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_2407;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_2414 = 0;
    (void)_t_Bool_2414;
    return _t_Bool_2414;
}

Bool Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2424 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_2424;
    if (_t_Bool_2424) {
        Bool _t_Bool_2415 = 0;
        (void)_t_Bool_2415;
        ;
        return _t_Bool_2415;
    }
    ;
    {
        U32 _re_U32_2416 = b->count;
        (void)_re_U32_2416;
        U32 _rc_U32_2416 = 0;
        (void)_rc_U32_2416;
        Bool _t_Bool_2423 = U32_lte(&_rc_U32_2416, &_re_U32_2416);
        (void)_t_Bool_2423;
        if (_t_Bool_2423) {
            while (1) {
                Bool _wcond_Bool_2417 = U32_lt(&_rc_U32_2416, &_re_U32_2416);
                (void)_wcond_Bool_2417;
                if (_wcond_Bool_2417) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2416);
                (void)i;
                U32_inc(&_rc_U32_2416);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_2419 = U8_neq(ac, bc);
                (void)_t_Bool_2419;
                ;
                if (_t_Bool_2419) {
                    Bool _t_Bool_2418 = 0;
                    (void)_t_Bool_2418;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_2418;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2420 = U32_gt(&_rc_U32_2416, &_re_U32_2416);
                (void)_wcond_Bool_2420;
                if (_wcond_Bool_2420) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2416);
                (void)i;
                U32_dec(&_rc_U32_2416);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_2422 = U8_neq(ac, bc);
                (void)_t_Bool_2422;
                ;
                if (_t_Bool_2422) {
                    Bool _t_Bool_2421 = 0;
                    (void)_t_Bool_2421;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_2421;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_2425 = 1;
    (void)_t_Bool_2425;
    return _t_Bool_2425;
}

Bool Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2437 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_2437;
    if (_t_Bool_2437) {
        Bool _t_Bool_2426 = 0;
        (void)_t_Bool_2426;
        ;
        return _t_Bool_2426;
    }
    ;
    U32 offset = U32_sub(a->count, b->count);
    (void)offset;
    {
        U32 _re_U32_2427 = b->count;
        (void)_re_U32_2427;
        U32 _rc_U32_2427 = 0;
        (void)_rc_U32_2427;
        Bool _t_Bool_2436 = U32_lte(&_rc_U32_2427, &_re_U32_2427);
        (void)_t_Bool_2436;
        if (_t_Bool_2436) {
            while (1) {
                Bool _wcond_Bool_2428 = U32_lt(&_rc_U32_2427, &_re_U32_2427);
                (void)_wcond_Bool_2428;
                if (_wcond_Bool_2428) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2427);
                (void)i;
                U32_inc(&_rc_U32_2427);
                U32 _t_U32_2430 = U32_add(offset, i);
                (void)_t_U32_2430;
                U8 *ac = Str_get(a, &_t_U32_2430);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_2431 = U8_neq(ac, bc);
                (void)_t_Bool_2431;
                ;
                ;
                if (_t_Bool_2431) {
                    Bool _t_Bool_2429 = 0;
                    (void)_t_Bool_2429;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_2429;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2432 = U32_gt(&_rc_U32_2427, &_re_U32_2427);
                (void)_wcond_Bool_2432;
                if (_wcond_Bool_2432) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2427);
                (void)i;
                U32_dec(&_rc_U32_2427);
                U32 _t_U32_2434 = U32_add(offset, i);
                (void)_t_U32_2434;
                U8 *ac = Str_get(a, &_t_U32_2434);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_2435 = U8_neq(ac, bc);
                (void)_t_Bool_2435;
                ;
                ;
                if (_t_Bool_2435) {
                    Bool _t_Bool_2433 = 0;
                    (void)_t_Bool_2433;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_2433;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    Bool _t_Bool_2438 = 1;
    (void)_t_Bool_2438;
    return _t_Bool_2438;
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_2439 = 0;
    (void)_t_U32_2439;
    Bool _t_Bool_2440 = U32_eq(self->count, _t_U32_2439);
    (void)_t_Bool_2440;
    ;
    return _t_Bool_2440;
}

I64 Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_2475 = 0;
    (void)_t_U32_2475;
    Bool _t_Bool_2476 = U32_eq(needle->count, _t_U32_2475);
    (void)_t_Bool_2476;
    ;
    if (_t_Bool_2476) {
        I64 _t_I64_2441 = 0;
        (void)_t_I64_2441;
        I64 _t_I64_2442 = 1;
        (void)_t_I64_2442;
        I64 _t_I64_2443 = I64_sub(_t_I64_2441, _t_I64_2442);
        (void)_t_I64_2443;
        ;
        ;
        ;
        return _t_I64_2443;
    }
    ;
    Bool _t_Bool_2477 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_2477;
    if (_t_Bool_2477) {
        I64 _t_I64_2444 = 0;
        (void)_t_I64_2444;
        I64 _t_I64_2445 = 1;
        (void)_t_I64_2445;
        I64 _t_I64_2446 = I64_sub(_t_I64_2444, _t_I64_2445);
        (void)_t_I64_2446;
        ;
        ;
        ;
        return _t_I64_2446;
    }
    ;
    {
        U32 _t_U32_2472 = U32_sub(self->count, needle->count);
        (void)_t_U32_2472;
        U32 _t_U32_2473 = 1;
        (void)_t_U32_2473;
        U32 _re_U32_2447 = U32_add(_t_U32_2472, _t_U32_2473);
        (void)_re_U32_2447;
        ;
        ;
        U32 _rc_U32_2447 = 0;
        (void)_rc_U32_2447;
        Bool _t_Bool_2474 = U32_lte(&_rc_U32_2447, &_re_U32_2447);
        (void)_t_Bool_2474;
        if (_t_Bool_2474) {
            while (1) {
                Bool _wcond_Bool_2448 = U32_lt(&_rc_U32_2447, &_re_U32_2447);
                (void)_wcond_Bool_2448;
                if (_wcond_Bool_2448) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2447);
                (void)i;
                U32_inc(&_rc_U32_2447);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_2449 = needle->count;
                    (void)_re_U32_2449;
                    U32 _rc_U32_2449 = 0;
                    (void)_rc_U32_2449;
                    Bool _t_Bool_2458 = U32_lte(&_rc_U32_2449, &_re_U32_2449);
                    (void)_t_Bool_2458;
                    if (_t_Bool_2458) {
                        while (1) {
                            Bool _wcond_Bool_2450 = U32_lt(&_rc_U32_2449, &_re_U32_2449);
                            (void)_wcond_Bool_2450;
                            if (_wcond_Bool_2450) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2449);
                            (void)j;
                            U32_inc(&_rc_U32_2449);
                            U32 _t_U32_2452 = U32_add(i, j);
                            (void)_t_U32_2452;
                            U8 *ac = Str_get(self, &_t_U32_2452);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_2453 = U8_neq(ac, bc);
                            (void)_t_Bool_2453;
                            ;
                            ;
                            if (_t_Bool_2453) {
                                Bool _t_Bool_2451 = 0;
                                (void)_t_Bool_2451;
                                found = _t_Bool_2451;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_2454 = U32_gt(&_rc_U32_2449, &_re_U32_2449);
                            (void)_wcond_Bool_2454;
                            if (_wcond_Bool_2454) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2449);
                            (void)j;
                            U32_dec(&_rc_U32_2449);
                            U32 _t_U32_2456 = U32_add(i, j);
                            (void)_t_U32_2456;
                            U8 *ac = Str_get(self, &_t_U32_2456);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_2457 = U8_neq(ac, bc);
                            (void)_t_Bool_2457;
                            ;
                            ;
                            if (_t_Bool_2457) {
                                Bool _t_Bool_2455 = 0;
                                (void)_t_Bool_2455;
                                found = _t_Bool_2455;
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
                    I64 _t_I64_2459 = U32_to_i64(i);
                    (void)_t_I64_2459;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_2459;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2460 = U32_gt(&_rc_U32_2447, &_re_U32_2447);
                (void)_wcond_Bool_2460;
                if (_wcond_Bool_2460) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2447);
                (void)i;
                U32_dec(&_rc_U32_2447);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_2461 = needle->count;
                    (void)_re_U32_2461;
                    U32 _rc_U32_2461 = 0;
                    (void)_rc_U32_2461;
                    Bool _t_Bool_2470 = U32_lte(&_rc_U32_2461, &_re_U32_2461);
                    (void)_t_Bool_2470;
                    if (_t_Bool_2470) {
                        while (1) {
                            Bool _wcond_Bool_2462 = U32_lt(&_rc_U32_2461, &_re_U32_2461);
                            (void)_wcond_Bool_2462;
                            if (_wcond_Bool_2462) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2461);
                            (void)j;
                            U32_inc(&_rc_U32_2461);
                            U32 _t_U32_2464 = U32_add(i, j);
                            (void)_t_U32_2464;
                            U8 *ac = Str_get(self, &_t_U32_2464);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_2465 = U8_neq(ac, bc);
                            (void)_t_Bool_2465;
                            ;
                            ;
                            if (_t_Bool_2465) {
                                Bool _t_Bool_2463 = 0;
                                (void)_t_Bool_2463;
                                found = _t_Bool_2463;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_2466 = U32_gt(&_rc_U32_2461, &_re_U32_2461);
                            (void)_wcond_Bool_2466;
                            if (_wcond_Bool_2466) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2461);
                            (void)j;
                            U32_dec(&_rc_U32_2461);
                            U32 _t_U32_2468 = U32_add(i, j);
                            (void)_t_U32_2468;
                            U8 *ac = Str_get(self, &_t_U32_2468);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_2469 = U8_neq(ac, bc);
                            (void)_t_Bool_2469;
                            ;
                            ;
                            if (_t_Bool_2469) {
                                Bool _t_Bool_2467 = 0;
                                (void)_t_Bool_2467;
                                found = _t_Bool_2467;
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
                    I64 _t_I64_2471 = U32_to_i64(i);
                    (void)_t_I64_2471;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_2471;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    I64 _t_I64_2478 = 0;
    (void)_t_I64_2478;
    I64 _t_I64_2479 = 1;
    (void)_t_I64_2479;
    I64 _t_I64_2480 = I64_sub(_t_I64_2478, _t_I64_2479);
    (void)_t_I64_2480;
    ;
    ;
    return _t_I64_2480;
}

I64 Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_2515 = 0;
    (void)_t_U32_2515;
    Bool _t_Bool_2516 = U32_eq(needle->count, _t_U32_2515);
    (void)_t_Bool_2516;
    ;
    if (_t_Bool_2516) {
        I64 _t_I64_2481 = 0;
        (void)_t_I64_2481;
        I64 _t_I64_2482 = 1;
        (void)_t_I64_2482;
        I64 _t_I64_2483 = I64_sub(_t_I64_2481, _t_I64_2482);
        (void)_t_I64_2483;
        ;
        ;
        ;
        return _t_I64_2483;
    }
    ;
    Bool _t_Bool_2517 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_2517;
    if (_t_Bool_2517) {
        I64 _t_I64_2484 = 0;
        (void)_t_I64_2484;
        I64 _t_I64_2485 = 1;
        (void)_t_I64_2485;
        I64 _t_I64_2486 = I64_sub(_t_I64_2484, _t_I64_2485);
        (void)_t_I64_2486;
        ;
        ;
        ;
        return _t_I64_2486;
    }
    ;
    I64 _t_I64_2518 = 0;
    (void)_t_I64_2518;
    I64 _t_I64_2519 = 1;
    (void)_t_I64_2519;
    I64 last = I64_sub(_t_I64_2518, _t_I64_2519);
    (void)last;
    ;
    ;
    {
        U32 _t_U32_2512 = U32_sub(self->count, needle->count);
        (void)_t_U32_2512;
        U32 _t_U32_2513 = 1;
        (void)_t_U32_2513;
        U32 _re_U32_2487 = U32_add(_t_U32_2512, _t_U32_2513);
        (void)_re_U32_2487;
        ;
        ;
        U32 _rc_U32_2487 = 0;
        (void)_rc_U32_2487;
        Bool _t_Bool_2514 = U32_lte(&_rc_U32_2487, &_re_U32_2487);
        (void)_t_Bool_2514;
        if (_t_Bool_2514) {
            while (1) {
                Bool _wcond_Bool_2488 = U32_lt(&_rc_U32_2487, &_re_U32_2487);
                (void)_wcond_Bool_2488;
                if (_wcond_Bool_2488) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2487);
                (void)i;
                U32_inc(&_rc_U32_2487);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_2489 = needle->count;
                    (void)_re_U32_2489;
                    U32 _rc_U32_2489 = 0;
                    (void)_rc_U32_2489;
                    Bool _t_Bool_2498 = U32_lte(&_rc_U32_2489, &_re_U32_2489);
                    (void)_t_Bool_2498;
                    if (_t_Bool_2498) {
                        while (1) {
                            Bool _wcond_Bool_2490 = U32_lt(&_rc_U32_2489, &_re_U32_2489);
                            (void)_wcond_Bool_2490;
                            if (_wcond_Bool_2490) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2489);
                            (void)j;
                            U32_inc(&_rc_U32_2489);
                            U32 _t_U32_2492 = U32_add(i, j);
                            (void)_t_U32_2492;
                            U8 *ac = Str_get(self, &_t_U32_2492);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_2493 = U8_neq(ac, bc);
                            (void)_t_Bool_2493;
                            ;
                            ;
                            if (_t_Bool_2493) {
                                Bool _t_Bool_2491 = 0;
                                (void)_t_Bool_2491;
                                found = _t_Bool_2491;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_2494 = U32_gt(&_rc_U32_2489, &_re_U32_2489);
                            (void)_wcond_Bool_2494;
                            if (_wcond_Bool_2494) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2489);
                            (void)j;
                            U32_dec(&_rc_U32_2489);
                            U32 _t_U32_2496 = U32_add(i, j);
                            (void)_t_U32_2496;
                            U8 *ac = Str_get(self, &_t_U32_2496);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_2497 = U8_neq(ac, bc);
                            (void)_t_Bool_2497;
                            ;
                            ;
                            if (_t_Bool_2497) {
                                Bool _t_Bool_2495 = 0;
                                (void)_t_Bool_2495;
                                found = _t_Bool_2495;
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
                    I64 _t_I64_2499 = U32_to_i64(i);
                    (void)_t_I64_2499;
                    last = _t_I64_2499;
                    ;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2500 = U32_gt(&_rc_U32_2487, &_re_U32_2487);
                (void)_wcond_Bool_2500;
                if (_wcond_Bool_2500) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2487);
                (void)i;
                U32_dec(&_rc_U32_2487);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_2501 = needle->count;
                    (void)_re_U32_2501;
                    U32 _rc_U32_2501 = 0;
                    (void)_rc_U32_2501;
                    Bool _t_Bool_2510 = U32_lte(&_rc_U32_2501, &_re_U32_2501);
                    (void)_t_Bool_2510;
                    if (_t_Bool_2510) {
                        while (1) {
                            Bool _wcond_Bool_2502 = U32_lt(&_rc_U32_2501, &_re_U32_2501);
                            (void)_wcond_Bool_2502;
                            if (_wcond_Bool_2502) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2501);
                            (void)j;
                            U32_inc(&_rc_U32_2501);
                            U32 _t_U32_2504 = U32_add(i, j);
                            (void)_t_U32_2504;
                            U8 *ac = Str_get(self, &_t_U32_2504);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_2505 = U8_neq(ac, bc);
                            (void)_t_Bool_2505;
                            ;
                            ;
                            if (_t_Bool_2505) {
                                Bool _t_Bool_2503 = 0;
                                (void)_t_Bool_2503;
                                found = _t_Bool_2503;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_2506 = U32_gt(&_rc_U32_2501, &_re_U32_2501);
                            (void)_wcond_Bool_2506;
                            if (_wcond_Bool_2506) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_2501);
                            (void)j;
                            U32_dec(&_rc_U32_2501);
                            U32 _t_U32_2508 = U32_add(i, j);
                            (void)_t_U32_2508;
                            U8 *ac = Str_get(self, &_t_U32_2508);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_2509 = U8_neq(ac, bc);
                            (void)_t_Bool_2509;
                            ;
                            ;
                            if (_t_Bool_2509) {
                                Bool _t_Bool_2507 = 0;
                                (void)_t_Bool_2507;
                                found = _t_Bool_2507;
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
                    I64 _t_I64_2511 = U32_to_i64(i);
                    (void)_t_I64_2511;
                    last = _t_I64_2511;
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
    U32 _t_U32_2545 = 0;
    (void)_t_U32_2545;
    Bool _t_Bool_2546 = U32_eq(from->count, _t_U32_2545);
    (void)_t_Bool_2546;
    ;
    if (_t_Bool_2546) {
        Str *_t_Str_2520 = Str_clone(self);
        (void)_t_Str_2520;
        ;
        return _t_Str_2520;
    }
    ;
    U32 matches = 0;
    (void)matches;
    U32 start = 0;
    (void)start;
    while (1) {
        U32 _t_U32_2522 = U32_sub(self->count, from->count);
        (void)_t_U32_2522;
        Bool _wcond_Bool_2521 = U32_lte(&start, &_t_U32_2522);
        (void)_wcond_Bool_2521;
        ;
        if (_wcond_Bool_2521) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_2523 = U32_sub(self->count, start);
        (void)_t_U32_2523;
        Str *rest = Str_substr(self, &start, &_t_U32_2523);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_2524 = 0;
        (void)_t_I64_2524;
        I64 _t_I64_2525 = 1;
        (void)_t_I64_2525;
        I64 _t_I64_2526 = I64_sub(_t_I64_2524, _t_I64_2525);
        (void)_t_I64_2526;
        ;
        ;
        Bool _t_Bool_2527 = I64_eq(pos, _t_I64_2526);
        (void)_t_Bool_2527;
        ;
        if (_t_Bool_2527) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        U32 _t_U32_2528 = U32_add(start, pos_u);
        (void)_t_U32_2528;
        ;
        U32 _t_U32_2529 = U32_add(_t_U32_2528, from->count);
        (void)_t_U32_2529;
        ;
        start = _t_U32_2529;
        ;
        U32 _t_U32_2530 = 1;
        (void)_t_U32_2530;
        U32 _t_U32_2531 = U32_add(matches, _t_U32_2530);
        (void)_t_U32_2531;
        ;
        matches = _t_U32_2531;
        ;
    }
    U32 _t_U32_2547 = 0;
    (void)_t_U32_2547;
    Bool _t_Bool_2548 = U32_eq(matches, _t_U32_2547);
    (void)_t_Bool_2548;
    ;
    if (_t_Bool_2548) {
        Str *_t_Str_2532 = Str_clone(self);
        (void)_t_Str_2532;
        ;
        ;
        ;
        return _t_Str_2532;
    }
    ;
    U32 removed = U32_mul(matches, from->count);
    (void)removed;
    U32 added = U32_mul(matches, to->count);
    (void)added;
    ;
    U32 _t_U32_2549 = U32_sub(self->count, removed);
    (void)_t_U32_2549;
    ;
    U32 _t_U32_2550 = U32_add(_t_U32_2549, added);
    (void)_t_U32_2550;
    ;
    ;
    Str *out = Str_with_capacity(&_t_U32_2550);
    (void)out;
    ;
    U32 _t_U32_2551 = 0;
    (void)_t_U32_2551;
    start = _t_U32_2551;
    ;
    while (1) {
        U32 _t_U32_2534 = U32_sub(self->count, from->count);
        (void)_t_U32_2534;
        Bool _wcond_Bool_2533 = U32_lte(&start, &_t_U32_2534);
        (void)_wcond_Bool_2533;
        ;
        if (_wcond_Bool_2533) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_2535 = U32_sub(self->count, start);
        (void)_t_U32_2535;
        Str *rest = Str_substr(self, &start, &_t_U32_2535);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_2536 = 0;
        (void)_t_I64_2536;
        I64 _t_I64_2537 = 1;
        (void)_t_I64_2537;
        I64 _t_I64_2538 = I64_sub(_t_I64_2536, _t_I64_2537);
        (void)_t_I64_2538;
        ;
        ;
        Bool _t_Bool_2539 = I64_eq(pos, _t_I64_2538);
        (void)_t_Bool_2539;
        ;
        if (_t_Bool_2539) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        Str *_t_Str_2540 = Str_substr(self, &start, &pos_u);
        (void)_t_Str_2540;
        Str_push_str(out, _t_Str_2540);
        Str_delete(_t_Str_2540, &(Bool){1});
        Str_push_str(out, to);
        U32 _t_U32_2541 = U32_add(start, pos_u);
        (void)_t_U32_2541;
        ;
        U32 _t_U32_2542 = U32_add(_t_U32_2541, from->count);
        (void)_t_U32_2542;
        ;
        start = _t_U32_2542;
        ;
    }
    Bool _t_Bool_2552 = U32_lt(&start, &self->count);
    (void)_t_Bool_2552;
    if (_t_Bool_2552) {
        U32 _t_U32_2543 = U32_sub(self->count, start);
        (void)_t_U32_2543;
        Str *_t_Str_2544 = Str_substr(self, &start, &_t_U32_2543);
        (void)_t_Str_2544;
        ;
        Str_push_str(out, _t_Str_2544);
        Str_delete(_t_Str_2544, &(Bool){1});
    }
    ;
    ;
    return out;
}

Str * Str_get_char(Str * self, U32 * i) {
    (void)self;
    (void)i;
    U32 _t_U32_2553 = 1;
    (void)_t_U32_2553;
    Str *_t_Str_2554 = Str_substr(self, i, &_t_U32_2553);
    (void)_t_Str_2554;
    ;
    return _t_Str_2554;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t_Bool_2557 = Str_starts_with(self, prefix);
    (void)_t_Bool_2557;
    if (_t_Bool_2557) {
        U32 _t_U32_2555 = U32_sub(self->count, prefix->count);
        (void)_t_U32_2555;
        Str *_t_Str_2556 = Str_substr(self, &prefix->count, &_t_U32_2555);
        (void)_t_Str_2556;
        ;
        ;
        return _t_Str_2556;
    }
    ;
    Str *_t_Str_2558 = Str_clone(self);
    (void)_t_Str_2558;
    return _t_Str_2558;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t_Bool_2562 = Str_ends_with(self, suffix);
    (void)_t_Bool_2562;
    if (_t_Bool_2562) {
        U32 _t_U32_2559 = 0;
        (void)_t_U32_2559;
        U32 _t_U32_2560 = U32_sub(self->count, suffix->count);
        (void)_t_U32_2560;
        Str *_t_Str_2561 = Str_substr(self, &_t_U32_2559, &_t_U32_2560);
        (void)_t_Str_2561;
        ;
        ;
        ;
        return _t_Str_2561;
    }
    ;
    Str *_t_Str_2563 = Str_clone(self);
    (void)_t_Str_2563;
    return _t_Str_2563;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t_U64_2564 = 2;
    (void)_t_U64_2564;
    void * buf = malloc(_t_U64_2564);
    (void)buf;
    ;
    U64 _t_U64_2565 = 1;
    (void)_t_U64_2565;
    memcpy(buf, byte, _t_U64_2565);
    ;
    U64 _t_U64_2566 = 1;
    (void)_t_U64_2566;
    void *_t_v_2567 = ptr_add(buf, _t_U64_2566);
    (void)_t_v_2567;
    I32 _t_I32_2568 = 0;
    (void)_t_I32_2568;
    U64 _t_U64_2569 = 1;
    (void)_t_U64_2569;
    memset(_t_v_2567, _t_I32_2568, _t_U64_2569);
    ;
    ;
    ;
    I64 _t_I64_2570 = 1;
    (void)_t_I64_2570;
    I64 _t_I64_2571 = 1;
    (void)_t_I64_2571;
    Str *_t_Str_2572 = malloc(sizeof(Str));
    _t_Str_2572->c_str = buf;
    _t_Str_2572->count = _t_I64_2570;
    _t_Str_2572->cap = _t_I64_2571;
    (void)_t_Str_2572;
    ;
    ;
    return _t_Str_2572;
}

I64 Str_to_i64(Str * self) {
    (void)self;
    U32 _t_U32_2633 = 0;
    (void)_t_U32_2633;
    Bool _t_Bool_2634 = U32_eq(self->count, _t_U32_2633);
    (void)_t_Bool_2634;
    ;
    if (_t_Bool_2634) {
        Str *_t_Str_2573 = Str_lit("Str", 3ULL);
        (void)_t_Str_2573;
        U32 _t_U32_2574 = 16;
        (void)_t_U32_2574;
        U32 _t_U32_2575 = 1;
        (void)_t_U32_2575;
        Array *_va_Array_87 = Array_new(_t_Str_2573, &_t_U32_2574, &_t_U32_2575);
        (void)_va_Array_87;
        Str_delete(_t_Str_2573, &(Bool){1});
        ;
        ;
        U32 _t_U32_2576 = 0;
        (void)_t_U32_2576;
        Str *_t_Str_2577 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t_Str_2577;
        Array_set(_va_Array_87, &_t_U32_2576, _t_Str_2577);
        ;
        Str *_t_Str_2578 = Str_lit("./src/core/str.til:233:37", 25ULL);
        (void)_t_Str_2578;
        panic(_t_Str_2578, _va_Array_87);
        Str_delete(_t_Str_2578, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_2635 = 0;
    (void)_t_U32_2635;
    U8 *first = Str_get(self, &_t_U32_2635);
    (void)first;
    U8 _t_U8_2636 = 45;
    (void)_t_U8_2636;
    Bool _t_Bool_2637 = U8_eq(DEREF(first), _t_U8_2636);
    (void)_t_Bool_2637;
    ;
    ;
    if (_t_Bool_2637) {
        Bool _t_Bool_2579 = 1;
        (void)_t_Bool_2579;
        neg = _t_Bool_2579;
        ;
        U32 _t_U32_2580 = 1;
        (void)_t_U32_2580;
        start = _t_U32_2580;
        ;
    }
    ;
    Bool _t_Bool_2638 = U32_eq(start, self->count);
    (void)_t_Bool_2638;
    if (_t_Bool_2638) {
        Str *_t_Str_2581 = Str_lit("Str", 3ULL);
        (void)_t_Str_2581;
        U32 _t_U32_2582 = 16;
        (void)_t_U32_2582;
        U32 _t_U32_2583 = 1;
        (void)_t_U32_2583;
        Array *_va_Array_88 = Array_new(_t_Str_2581, &_t_U32_2582, &_t_U32_2583);
        (void)_va_Array_88;
        Str_delete(_t_Str_2581, &(Bool){1});
        ;
        ;
        U32 _t_U32_2584 = 0;
        (void)_t_U32_2584;
        Str *_t_Str_2585 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t_Str_2585;
        Array_set(_va_Array_88, &_t_U32_2584, _t_Str_2585);
        ;
        Str *_t_Str_2586 = Str_lit("./src/core/str.til:242:41", 25ULL);
        (void)_t_Str_2586;
        panic(_t_Str_2586, _va_Array_88);
        Str_delete(_t_Str_2586, &(Bool){1});
    }
    ;
    {
        U32 _re_U32_2587 = self->count;
        (void)_re_U32_2587;
        U32 _rc_U32_2587 = U32_clone(&start);
        (void)_rc_U32_2587;
        Bool _t_Bool_2630 = U32_lte(&_rc_U32_2587, &_re_U32_2587);
        (void)_t_Bool_2630;
        if (_t_Bool_2630) {
            while (1) {
                Bool _wcond_Bool_2588 = U32_lt(&_rc_U32_2587, &_re_U32_2587);
                (void)_wcond_Bool_2588;
                if (_wcond_Bool_2588) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2587);
                (void)i;
                U32_inc(&_rc_U32_2587);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_2599 = U8_to_i64(DEREF(ch));
                (void)_t_I64_2599;
                ;
                I64 _t_I64_2600 = 48;
                (void)_t_I64_2600;
                I64 d = I64_sub(_t_I64_2599, _t_I64_2600);
                (void)d;
                ;
                ;
                I64 _t_I64_2601 = 0;
                (void)_t_I64_2601;
                I64 _t_I64_2602 = 9;
                (void)_t_I64_2602;
                Bool _t_Bool_2603 = I64_lt(&d, &_t_I64_2601);
                (void)_t_Bool_2603;
                ;
                Bool _t_Bool_2604 = I64_gt(&d, &_t_I64_2602);
                (void)_t_Bool_2604;
                ;
                Bool _t_Bool_2605 = or(_t_Bool_2603, _t_Bool_2604);
                (void)_t_Bool_2605;
                ;
                ;
                if (_t_Bool_2605) {
                    Str *_t_Str_2589 = Str_lit("Str", 3ULL);
                    (void)_t_Str_2589;
                    U32 _t_U32_2590 = 16;
                    (void)_t_U32_2590;
                    U32 _t_U32_2591 = 3;
                    (void)_t_U32_2591;
                    Array *_va_Array_89 = Array_new(_t_Str_2589, &_t_U32_2590, &_t_U32_2591);
                    (void)_va_Array_89;
                    Str_delete(_t_Str_2589, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_2592 = 0;
                    (void)_t_U32_2592;
                    Str *_t_Str_2593 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_2593;
                    Array_set(_va_Array_89, &_t_U32_2592, _t_Str_2593);
                    ;
                    U32 _t_U32_2594 = 1;
                    (void)_t_U32_2594;
                    Str *_t_Str_2595 = Str_clone(self);
                    (void)_t_Str_2595;
                    Array_set(_va_Array_89, &_t_U32_2594, _t_Str_2595);
                    ;
                    U32 _t_U32_2596 = 2;
                    (void)_t_U32_2596;
                    Str *_t_Str_2597 = Str_lit("'", 1ULL);
                    (void)_t_Str_2597;
                    Array_set(_va_Array_89, &_t_U32_2596, _t_Str_2597);
                    ;
                    Str *_t_Str_2598 = Str_lit("./src/core/str.til:247:23", 25ULL);
                    (void)_t_Str_2598;
                    panic(_t_Str_2598, _va_Array_89);
                    Str_delete(_t_Str_2598, &(Bool){1});
                }
                ;
                I64 _t_I64_2606 = 10;
                (void)_t_I64_2606;
                I64 _t_I64_2607 = I64_mul(result, _t_I64_2606);
                (void)_t_I64_2607;
                ;
                I64 _t_I64_2608 = I64_add(_t_I64_2607, d);
                (void)_t_I64_2608;
                ;
                ;
                result = _t_I64_2608;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2609 = U32_gt(&_rc_U32_2587, &_re_U32_2587);
                (void)_wcond_Bool_2609;
                if (_wcond_Bool_2609) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2587);
                (void)i;
                U32_dec(&_rc_U32_2587);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_2620 = U8_to_i64(DEREF(ch));
                (void)_t_I64_2620;
                ;
                I64 _t_I64_2621 = 48;
                (void)_t_I64_2621;
                I64 d = I64_sub(_t_I64_2620, _t_I64_2621);
                (void)d;
                ;
                ;
                I64 _t_I64_2622 = 0;
                (void)_t_I64_2622;
                I64 _t_I64_2623 = 9;
                (void)_t_I64_2623;
                Bool _t_Bool_2624 = I64_lt(&d, &_t_I64_2622);
                (void)_t_Bool_2624;
                ;
                Bool _t_Bool_2625 = I64_gt(&d, &_t_I64_2623);
                (void)_t_Bool_2625;
                ;
                Bool _t_Bool_2626 = or(_t_Bool_2624, _t_Bool_2625);
                (void)_t_Bool_2626;
                ;
                ;
                if (_t_Bool_2626) {
                    Str *_t_Str_2610 = Str_lit("Str", 3ULL);
                    (void)_t_Str_2610;
                    U32 _t_U32_2611 = 16;
                    (void)_t_U32_2611;
                    U32 _t_U32_2612 = 3;
                    (void)_t_U32_2612;
                    Array *_va_Array_90 = Array_new(_t_Str_2610, &_t_U32_2611, &_t_U32_2612);
                    (void)_va_Array_90;
                    Str_delete(_t_Str_2610, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_2613 = 0;
                    (void)_t_U32_2613;
                    Str *_t_Str_2614 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_2614;
                    Array_set(_va_Array_90, &_t_U32_2613, _t_Str_2614);
                    ;
                    U32 _t_U32_2615 = 1;
                    (void)_t_U32_2615;
                    Str *_t_Str_2616 = Str_clone(self);
                    (void)_t_Str_2616;
                    Array_set(_va_Array_90, &_t_U32_2615, _t_Str_2616);
                    ;
                    U32 _t_U32_2617 = 2;
                    (void)_t_U32_2617;
                    Str *_t_Str_2618 = Str_lit("'", 1ULL);
                    (void)_t_Str_2618;
                    Array_set(_va_Array_90, &_t_U32_2617, _t_Str_2618);
                    ;
                    Str *_t_Str_2619 = Str_lit("./src/core/str.til:247:23", 25ULL);
                    (void)_t_Str_2619;
                    panic(_t_Str_2619, _va_Array_90);
                    Str_delete(_t_Str_2619, &(Bool){1});
                }
                ;
                I64 _t_I64_2627 = 10;
                (void)_t_I64_2627;
                I64 _t_I64_2628 = I64_mul(result, _t_I64_2627);
                (void)_t_I64_2628;
                ;
                I64 _t_I64_2629 = I64_add(_t_I64_2628, d);
                (void)_t_I64_2629;
                ;
                ;
                result = _t_I64_2629;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    if (neg) {
        I64 _t_I64_2631 = 0;
        (void)_t_I64_2631;
        I64 _t_I64_2632 = I64_sub(_t_I64_2631, result);
        (void)_t_I64_2632;
        ;
        ;
        ;
        return _t_I64_2632;
    }
    ;
    return result;
}

U8 Str_to_u8(Str * self) {
    (void)self;
    I64 _t_I64_2639 = Str_to_i64(self);
    (void)_t_I64_2639;
    U8 _t_U8_2640 = I64_to_u8(_t_I64_2639);
    (void)_t_U8_2640;
    ;
    return _t_U8_2640;
}

I32 Str_to_i32(Str * self) {
    (void)self;
    I64 _t_I64_2641 = Str_to_i64(self);
    (void)_t_I64_2641;
    I32 _t_I32_2642 = I64_to_i32(_t_I64_2641);
    (void)_t_I32_2642;
    ;
    return _t_I32_2642;
}

F32 Str_to_f32(Str * self) {
    (void)self;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_2668 = Str_len(self);
    (void)_t_U32_2668;
    U32 _t_U32_2669 = 0;
    (void)_t_U32_2669;
    U32 _t_U32_2670 = 0;
    (void)_t_U32_2670;
    U8 *_t_U8_2671 = Str_get(self, &_t_U32_2670);
    (void)_t_U8_2671;
    U8 _t_U8_2672 = 45;
    (void)_t_U8_2672;
    Bool _t_Bool_2673 = U32_gt(&_t_U32_2668, &_t_U32_2669);
    (void)_t_Bool_2673;
    ;
    ;
    Bool _t_Bool_2674 = U8_eq(DEREF(_t_U8_2671), _t_U8_2672);
    (void)_t_Bool_2674;
    ;
    ;
    Bool _t_Bool_2675 = and(_t_Bool_2673, _t_Bool_2674);
    (void)_t_Bool_2675;
    ;
    ;
    if (_t_Bool_2675) {
        Bool _t_Bool_2643 = 1;
        (void)_t_Bool_2643;
        neg = _t_Bool_2643;
        ;
        U32 _t_U32_2644 = 1;
        (void)_t_U32_2644;
        start = _t_U32_2644;
        ;
    }
    ;
    U32 _t_U32_2676 = Str_len(self);
    (void)_t_U32_2676;
    U32 _t_U32_2677 = U32_sub(_t_U32_2676, start);
    (void)_t_U32_2677;
    ;
    Str *rest = Str_substr(self, &start, &_t_U32_2677);
    (void)rest;
    ;
    ;
    Str *_t_Str_2678 = Str_lit(".", 1ULL);
    (void)_t_Str_2678;
    I64 dot = Str_find(rest, _t_Str_2678);
    (void)dot;
    Str_delete(_t_Str_2678, &(Bool){1});
    I64 _t_I64_2679 = 0;
    (void)_t_I64_2679;
    I64 _t_I64_2680 = 1;
    (void)_t_I64_2680;
    I64 _t_I64_2681 = I64_sub(_t_I64_2679, _t_I64_2680);
    (void)_t_I64_2681;
    ;
    ;
    Bool _t_Bool_2682 = I64_eq(dot, _t_I64_2681);
    (void)_t_Bool_2682;
    ;
    if (_t_Bool_2682) {
        I64 _t_I64_2648 = Str_to_i64(rest);
        (void)_t_I64_2648;
        F32 out = I64_to_f32(_t_I64_2648);
        (void)out;
        ;
        if (neg) {
            I64 _t_I64_2645 = 0;
            (void)_t_I64_2645;
            F32 _t_F32_2646 = I64_to_f32(_t_I64_2645);
            (void)_t_F32_2646;
            ;
            F32 _t_F32_2647 = F32_sub(_t_F32_2646, out);
            (void)_t_F32_2647;
            ;
            ;
            ;
            ;
            ;
            Str_delete(rest, &(Bool){1});
            return _t_F32_2647;
        }
        ;
        ;
        ;
        Str_delete(rest, &(Bool){1});
        return out;
    }
    ;
    U32 _t_U32_2683 = 0;
    (void)_t_U32_2683;
    U32 _t_U32_2684 = I64_to_usize(dot);
    (void)_t_U32_2684;
    Str *int_part = Str_substr(rest, &_t_U32_2683, &_t_U32_2684);
    (void)int_part;
    ;
    ;
    U32 _t_U32_2685 = I64_to_usize(dot);
    (void)_t_U32_2685;
    U32 _t_U32_2686 = 1;
    (void)_t_U32_2686;
    U32 _t_U32_2687 = I64_to_usize(dot);
    (void)_t_U32_2687;
    ;
    U32 _t_U32_2688 = 1;
    (void)_t_U32_2688;
    U32 _t_U32_2689 = Str_len(rest);
    (void)_t_U32_2689;
    U32 _t_U32_2690 = U32_add(_t_U32_2687, _t_U32_2688);
    (void)_t_U32_2690;
    ;
    ;
    U32 _t_U32_2691 = U32_add(_t_U32_2685, _t_U32_2686);
    (void)_t_U32_2691;
    ;
    ;
    U32 _t_U32_2692 = U32_sub(_t_U32_2689, _t_U32_2690);
    (void)_t_U32_2692;
    ;
    ;
    Str *frac_part = Str_substr(rest, &_t_U32_2691, &_t_U32_2692);
    (void)frac_part;
    ;
    ;
    Str_delete(rest, &(Bool){1});
    I64 _t_I64_2693 = 0;
    (void)_t_I64_2693;
    F32 out = I64_to_f32(_t_I64_2693);
    (void)out;
    ;
    U32 _t_U32_2694 = Str_len(int_part);
    (void)_t_U32_2694;
    U32 _t_U32_2695 = 0;
    (void)_t_U32_2695;
    Bool _t_Bool_2696 = U32_gt(&_t_U32_2694, &_t_U32_2695);
    (void)_t_Bool_2696;
    ;
    ;
    if (_t_Bool_2696) {
        I64 _t_I64_2649 = Str_to_i64(int_part);
        (void)_t_I64_2649;
        F32 _t_F32_2650 = I64_to_f32(_t_I64_2649);
        (void)_t_F32_2650;
        ;
        out = _t_F32_2650;
        ;
    }
    ;
    Str_delete(int_part, &(Bool){1});
    U32 _t_U32_2697 = Str_len(frac_part);
    (void)_t_U32_2697;
    U32 _t_U32_2698 = 0;
    (void)_t_U32_2698;
    Bool _t_Bool_2699 = U32_gt(&_t_U32_2697, &_t_U32_2698);
    (void)_t_Bool_2699;
    ;
    ;
    if (_t_Bool_2699) {
        I64 _t_I64_2661 = Str_to_i64(frac_part);
        (void)_t_I64_2661;
        F32 frac = I64_to_f32(_t_I64_2661);
        (void)frac;
        ;
        I64 _t_I64_2662 = 1;
        (void)_t_I64_2662;
        F32 scale = I64_to_f32(_t_I64_2662);
        (void)scale;
        ;
        {
            U32 _re_U32_2651 = Str_len(frac_part);
            (void)_re_U32_2651;
            U32 _rc_U32_2651 = 0;
            (void)_rc_U32_2651;
            Bool _t_Bool_2660 = U32_lte(&_rc_U32_2651, &_re_U32_2651);
            (void)_t_Bool_2660;
            if (_t_Bool_2660) {
                while (1) {
                    Bool _wcond_Bool_2652 = U32_lt(&_rc_U32_2651, &_re_U32_2651);
                    (void)_wcond_Bool_2652;
                    if (_wcond_Bool_2652) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_2651);
                    (void)_;
                    ;
                    U32_inc(&_rc_U32_2651);
                    I64 _t_I64_2653 = 10;
                    (void)_t_I64_2653;
                    F32 _t_F32_2654 = I64_to_f32(_t_I64_2653);
                    (void)_t_F32_2654;
                    ;
                    F32 _t_F32_2655 = F32_mul(scale, _t_F32_2654);
                    (void)_t_F32_2655;
                    ;
                    scale = _t_F32_2655;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_2656 = U32_gt(&_rc_U32_2651, &_re_U32_2651);
                    (void)_wcond_Bool_2656;
                    if (_wcond_Bool_2656) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_2651);
                    (void)_;
                    ;
                    U32_dec(&_rc_U32_2651);
                    I64 _t_I64_2657 = 10;
                    (void)_t_I64_2657;
                    F32 _t_F32_2658 = I64_to_f32(_t_I64_2657);
                    (void)_t_F32_2658;
                    ;
                    F32 _t_F32_2659 = F32_mul(scale, _t_F32_2658);
                    (void)_t_F32_2659;
                    ;
                    scale = _t_F32_2659;
                    ;
                }
            }
            ;
            ;
            ;
        }
        F32 _t_F32_2663 = F32_div(frac, scale);
        (void)_t_F32_2663;
        ;
        ;
        F32 _t_F32_2664 = F32_add(out, _t_F32_2663);
        (void)_t_F32_2664;
        ;
        out = _t_F32_2664;
        ;
    }
    ;
    Str_delete(frac_part, &(Bool){1});
    if (neg) {
        I64 _t_I64_2665 = 0;
        (void)_t_I64_2665;
        F32 _t_F32_2666 = I64_to_f32(_t_I64_2665);
        (void)_t_F32_2666;
        ;
        F32 _t_F32_2667 = F32_sub(_t_F32_2666, out);
        (void)_t_F32_2667;
        ;
        ;
        ;
        return _t_F32_2667;
    }
    ;
    return out;
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t_Str_2716 = Str_lit("Str", 3ULL);
    (void)_t_Str_2716;
    U32 _t_U32_2717 = 16;
    (void)_t_U32_2717;
    Vec *parts = Vec_new(_t_Str_2716, &_t_U32_2717);
    (void)parts;
    Str_delete(_t_Str_2716, &(Bool){1});
    ;
    U32 _t_U32_2718 = Str_len(delim);
    (void)_t_U32_2718;
    U32 _t_U32_2719 = 0;
    (void)_t_U32_2719;
    Bool _t_Bool_2720 = U32_eq(_t_U32_2718, _t_U32_2719);
    (void)_t_Bool_2720;
    ;
    ;
    if (_t_Bool_2720) {
        Str *_t_Str_2700 = Str_clone(self);
        (void)_t_Str_2700;
        Vec_push(parts, _t_Str_2700);
        ;
        return parts;
    }
    ;
    U32 start = 0;
    (void)start;
    U32 pos = 0;
    (void)pos;
    while (1) {
        U32 _t_U32_2710 = Str_len(self);
        (void)_t_U32_2710;
        U32 _t_U32_2711 = Str_len(delim);
        (void)_t_U32_2711;
        U32 _t_U32_2712 = U32_sub(_t_U32_2710, _t_U32_2711);
        (void)_t_U32_2712;
        ;
        ;
        Bool _wcond_Bool_2701 = U32_lte(&pos, &_t_U32_2712);
        (void)_wcond_Bool_2701;
        ;
        if (_wcond_Bool_2701) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_2713 = Str_len(delim);
        (void)_t_U32_2713;
        Str *_t_Str_2714 = Str_substr(self, &pos, &_t_U32_2713);
        (void)_t_Str_2714;
        ;
        Bool _t_Bool_2715 = Str_eq(_t_Str_2714, delim);
        (void)_t_Bool_2715;
        Str_delete(_t_Str_2714, &(Bool){1});
        if (_t_Bool_2715) {
            U32 _t_U32_2702 = U32_sub(pos, start);
            (void)_t_U32_2702;
            Str *_t_Str_2703 = Str_substr(self, &start, &_t_U32_2702);
            (void)_t_Str_2703;
            ;
            Str *_t_Str_2704 = Str_clone(_t_Str_2703);
            (void)_t_Str_2704;
            Str_delete(_t_Str_2703, &(Bool){1});
            Vec_push(parts, _t_Str_2704);
            U32 _t_U32_2705 = Str_len(delim);
            (void)_t_U32_2705;
            U32 _t_U32_2706 = U32_add(pos, _t_U32_2705);
            (void)_t_U32_2706;
            ;
            start = _t_U32_2706;
            ;
            U32 _t_U32_2707 = U32_clone(&start);
            (void)_t_U32_2707;
            pos = _t_U32_2707;
            ;
        } else {
            U32 _t_U32_2708 = 1;
            (void)_t_U32_2708;
            U32 _t_U32_2709 = U32_add(pos, _t_U32_2708);
            (void)_t_U32_2709;
            ;
            pos = _t_U32_2709;
            ;
        }
        ;
    }
    ;
    U32 _t_U32_2721 = Str_len(self);
    (void)_t_U32_2721;
    U32 _t_U32_2722 = U32_sub(_t_U32_2721, start);
    (void)_t_U32_2722;
    ;
    Str *_t_Str_2723 = Str_substr(self, &start, &_t_U32_2722);
    (void)_t_Str_2723;
    ;
    ;
    Str *_t_Str_2724 = Str_clone(_t_Str_2723);
    (void)_t_Str_2724;
    Str_delete(_t_Str_2723, &(Bool){1});
    Vec_push(parts, _t_Str_2724);
    return parts;
}

U32 Str_size(void) {
    I64 _t_I64_2725 = 16;
    (void)_t_I64_2725;
    return _t_I64_2725;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2726 = Str_cmp(a, b);
    (void)_t_I64_2726;
    I64 _t_I64_2727 = 0;
    (void)_t_I64_2727;
    Bool _t_Bool_2728 = I64_eq(_t_I64_2726, _t_I64_2727);
    (void)_t_Bool_2728;
    ;
    ;
    return _t_Bool_2728;
}

Bool Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2729 = 0;
    (void)_t_I64_2729;
    I64 _t_I64_2730 = 1;
    (void)_t_I64_2730;
    I64 _t_I64_2731 = Str_cmp(a, b);
    (void)_t_I64_2731;
    I64 _t_I64_2732 = I64_sub(_t_I64_2729, _t_I64_2730);
    (void)_t_I64_2732;
    ;
    ;
    Bool _t_Bool_2733 = I64_eq(_t_I64_2731, _t_I64_2732);
    (void)_t_Bool_2733;
    ;
    ;
    return _t_Bool_2733;
}

Bool Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2734 = Str_cmp(a, b);
    (void)_t_I64_2734;
    I64 _t_I64_2735 = 1;
    (void)_t_I64_2735;
    Bool _t_Bool_2736 = I64_eq(_t_I64_2734, _t_I64_2735);
    (void)_t_Bool_2736;
    ;
    ;
    return _t_Bool_2736;
}

Bool Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2737 = Str_eq(a, b);
    (void)_t_Bool_2737;
    Bool _t_Bool_2738 = not(_t_Bool_2737);
    (void)_t_Bool_2738;
    ;
    return _t_Bool_2738;
}

Bool Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2739 = Str_gt(a, b);
    (void)_t_Bool_2739;
    Bool _t_Bool_2740 = not(_t_Bool_2739);
    (void)_t_Bool_2740;
    ;
    return _t_Bool_2740;
}

Bool Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2741 = Str_lt(a, b);
    (void)_t_Bool_2741;
    Bool _t_Bool_2742 = not(_t_Bool_2741);
    (void)_t_Bool_2742;
    ;
    return _t_Bool_2742;
}

Str * U32_to_str(U32 * val) {
    (void)val;
    I64 _t_I64_2795 = U32_to_i64(DEREF(val));
    (void)_t_I64_2795;
    Str *_t_Str_2796 = I64_to_str(&_t_I64_2795);
    (void)_t_Str_2796;
    ;
    return _t_Str_2796;
}

void U32_inc(U32 * self) {
    (void)self;
    U32 _t_U32_2797 = 1;
    (void)_t_U32_2797;
    U32 _t_U32_2798 = U32_add(DEREF(self), _t_U32_2797);
    (void)_t_U32_2798;
    ;
    *self = _t_U32_2798;
    ;
}

void U32_dec(U32 * self) {
    (void)self;
    U32 _t_U32_2799 = 1;
    (void)_t_U32_2799;
    U32 _t_U32_2800 = U32_sub(DEREF(self), _t_U32_2799);
    (void)_t_U32_2800;
    ;
    *self = _t_U32_2800;
    ;
}

U32 * U32_unity(U32 * _self) {
    (void)_self;
    I64 _t_I64_2801 = 1;
    (void)_t_I64_2801;
    U32 _t_U32_2802 = I64_to_u32(_t_I64_2801);
    (void)_t_U32_2802;
    ;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_U32_2802; return _r; }
}

U64 U32_distance(void * a, void * b) {
    (void)a;
    (void)b;
    U32 *au = a;
    (void)au;
    U32 *bu = b;
    (void)bu;
    Bool _t_Bool_2806 = U32_lte(au, bu);
    (void)_t_Bool_2806;
    if (_t_Bool_2806) {
        U32 _t_U32_2803 = U32_sub(DEREF(bu), DEREF(au));
        (void)_t_U32_2803;
        I64 _t_I64_2804 = U32_to_i64(_t_U32_2803);
        (void)_t_I64_2804;
        ;
        U64 _t_U64_2805 = I64_to_u64(_t_I64_2804);
        (void)_t_U64_2805;
        ;
        ;
        return _t_U64_2805;
    }
    ;
    U32 _t_U32_2807 = U32_sub(DEREF(au), DEREF(bu));
    (void)_t_U32_2807;
    I64 _t_I64_2808 = U32_to_i64(_t_U32_2807);
    (void)_t_I64_2808;
    ;
    U64 _t_U64_2809 = I64_to_u64(_t_I64_2808);
    (void)_t_U64_2809;
    ;
    return _t_U64_2809;
}

void U32_delete(U32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U32_size(void) {
    I64 _t_I64_2810 = 4;
    (void)_t_I64_2810;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2810; return _r; }
}

Bool U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2811 = 0;
    (void)_t_I64_2811;
    I64 _t_I64_2812 = 1;
    (void)_t_I64_2812;
    I64 _t_I64_2813 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2813;
    I64 _t_I64_2814 = I64_sub(_t_I64_2811, _t_I64_2812);
    (void)_t_I64_2814;
    ;
    ;
    Bool _t_Bool_2815 = I64_eq(_t_I64_2813, _t_I64_2814);
    (void)_t_Bool_2815;
    ;
    ;
    return _t_Bool_2815;
}

Bool U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2816 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2816;
    I64 _t_I64_2817 = 1;
    (void)_t_I64_2817;
    Bool _t_Bool_2818 = I64_eq(_t_I64_2816, _t_I64_2817);
    (void)_t_Bool_2818;
    ;
    ;
    return _t_Bool_2818;
}

Bool U32_neq(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2819 = U32_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2819;
    Bool _t_Bool_2820 = not(_t_Bool_2819);
    (void)_t_Bool_2820;
    ;
    return _t_Bool_2820;
}

Bool U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2821 = U32_gt(a, b);
    (void)_t_Bool_2821;
    Bool _t_Bool_2822 = not(_t_Bool_2821);
    (void)_t_Bool_2822;
    ;
    return _t_Bool_2822;
}

Bool U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2823 = U32_lt(a, b);
    (void)_t_Bool_2823;
    Bool _t_Bool_2824 = not(_t_Bool_2823);
    (void)_t_Bool_2824;
    ;
    return _t_Bool_2824;
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t_Str_2825 = U64_to_str_ext(val);
    (void)_t_Str_2825;
    return _t_Str_2825;
}

U64 * U64_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func U64_from_i64_ext */
    U64 _t_U64_2826 = U64_from_i64_ext(val);
    (void)_t_U64_2826;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t_U64_2826; return _r; }
}

void U64_inc(U64 * self) {
    (void)self;
    U64 _t_U64_2827 = 1;
    (void)_t_U64_2827;
    U64 _t_U64_2828 = U64_add(DEREF(self), _t_U64_2827);
    (void)_t_U64_2828;
    ;
    *self = _t_U64_2828;
    ;
}

void U64_dec(U64 * self) {
    (void)self;
    U64 _t_U64_2829 = 1;
    (void)_t_U64_2829;
    U64 _t_U64_2830 = U64_sub(DEREF(self), _t_U64_2829);
    (void)_t_U64_2830;
    ;
    *self = _t_U64_2830;
    ;
}

U64 * U64_unity(U64 * _self) {
    (void)_self;
    I64 _t_I64_2831 = 1;
    (void)_t_I64_2831;
    U64 _t_U64_2832 = I64_to_u64(_t_I64_2831);
    (void)_t_U64_2832;
    ;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t_U64_2832; return _r; }
}

U64 U64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    U64 *au = a;
    (void)au;
    U64 *bu = b;
    (void)bu;
    Bool _t_Bool_2834 = U64_lte(au, bu);
    (void)_t_Bool_2834;
    if (_t_Bool_2834) {
        U64 _t_U64_2833 = U64_sub(DEREF(bu), DEREF(au));
        (void)_t_U64_2833;
        ;
        return _t_U64_2833;
    }
    ;
    U64 _t_U64_2835 = U64_sub(DEREF(au), DEREF(bu));
    (void)_t_U64_2835;
    return _t_U64_2835;
}

void U64_delete(U64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U64_size(void) {
    I64 _t_I64_2836 = 8;
    (void)_t_I64_2836;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2836; return _r; }
}

Bool U64_lt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2837 = 0;
    (void)_t_I64_2837;
    I64 _t_I64_2838 = 1;
    (void)_t_I64_2838;
    I64 _t_I64_2839 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2839;
    I64 _t_I64_2840 = I64_sub(_t_I64_2837, _t_I64_2838);
    (void)_t_I64_2840;
    ;
    ;
    Bool _t_Bool_2841 = I64_eq(_t_I64_2839, _t_I64_2840);
    (void)_t_Bool_2841;
    ;
    ;
    return _t_Bool_2841;
}

Bool U64_gt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2842 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2842;
    I64 _t_I64_2843 = 1;
    (void)_t_I64_2843;
    Bool _t_Bool_2844 = I64_eq(_t_I64_2842, _t_I64_2843);
    (void)_t_Bool_2844;
    ;
    ;
    return _t_Bool_2844;
}

Bool U64_neq(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2845 = U64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2845;
    Bool _t_Bool_2846 = not(_t_Bool_2845);
    (void)_t_Bool_2846;
    ;
    return _t_Bool_2846;
}

Bool U64_lte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2847 = U64_gt(a, b);
    (void)_t_Bool_2847;
    Bool _t_Bool_2848 = not(_t_Bool_2847);
    (void)_t_Bool_2848;
    ;
    return _t_Bool_2848;
}

Bool U64_gte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2849 = U64_lt(a, b);
    (void)_t_Bool_2849;
    Bool _t_Bool_2850 = not(_t_Bool_2849);
    (void)_t_Bool_2850;
    ;
    return _t_Bool_2850;
}

Str * U8_to_str(U8 * val) {
    (void)val;
    I64 _t_I64_2851 = U8_to_i64(DEREF(val));
    (void)_t_I64_2851;
    Str *_t_Str_2852 = I64_to_str(&_t_I64_2851);
    (void)_t_Str_2852;
    ;
    return _t_Str_2852;
}

void U8_inc(U8 * self) {
    (void)self;
    U8 _t_U8_2853 = 1;
    (void)_t_U8_2853;
    U8 _t_U8_2854 = U8_add(DEREF(self), _t_U8_2853);
    (void)_t_U8_2854;
    ;
    *self = _t_U8_2854;
    ;
}

void U8_dec(U8 * self) {
    (void)self;
    U8 _t_U8_2855 = 1;
    (void)_t_U8_2855;
    U8 _t_U8_2856 = U8_sub(DEREF(self), _t_U8_2855);
    (void)_t_U8_2856;
    ;
    *self = _t_U8_2856;
    ;
}

U8 * U8_unity(U8 * _self) {
    (void)_self;
    I64 _t_I64_2857 = 1;
    (void)_t_I64_2857;
    U8 _t_U8_2858 = I64_to_u8(_t_I64_2857);
    (void)_t_U8_2858;
    ;
    { U8 *_r = malloc(sizeof(U8)); *_r = _t_U8_2858; return _r; }
}

U64 U8_distance(void * a, void * b) {
    (void)a;
    (void)b;
    U8 *au = a;
    (void)au;
    U8 *bu = b;
    (void)bu;
    Bool _t_Bool_2861 = U8_lte(au, bu);
    (void)_t_Bool_2861;
    if (_t_Bool_2861) {
        U8 _t_U8_2859 = U8_sub(DEREF(bu), DEREF(au));
        (void)_t_U8_2859;
        U64 _t_U64_2860 = U8_to_u64(_t_U8_2859);
        (void)_t_U64_2860;
        ;
        ;
        return _t_U64_2860;
    }
    ;
    U8 _t_U8_2862 = U8_sub(DEREF(au), DEREF(bu));
    (void)_t_U8_2862;
    U64 _t_U64_2863 = U8_to_u64(_t_U8_2862);
    (void)_t_U64_2863;
    ;
    return _t_U64_2863;
}

void U8_delete(U8 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U8_size(void) {
    I64 _t_I64_2864 = 1;
    (void)_t_I64_2864;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2864; return _r; }
}

Bool U8_lt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2865 = 0;
    (void)_t_I64_2865;
    I64 _t_I64_2866 = 1;
    (void)_t_I64_2866;
    I64 _t_I64_2867 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2867;
    I64 _t_I64_2868 = I64_sub(_t_I64_2865, _t_I64_2866);
    (void)_t_I64_2868;
    ;
    ;
    Bool _t_Bool_2869 = I64_eq(_t_I64_2867, _t_I64_2868);
    (void)_t_Bool_2869;
    ;
    ;
    return _t_Bool_2869;
}

Bool U8_gt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2870 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2870;
    I64 _t_I64_2871 = 1;
    (void)_t_I64_2871;
    Bool _t_Bool_2872 = I64_eq(_t_I64_2870, _t_I64_2871);
    (void)_t_Bool_2872;
    ;
    ;
    return _t_Bool_2872;
}

Bool U8_neq(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2873 = U8_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2873;
    Bool _t_Bool_2874 = not(_t_Bool_2873);
    (void)_t_Bool_2874;
    ;
    return _t_Bool_2874;
}

Bool U8_lte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2875 = U8_gt(a, b);
    (void)_t_Bool_2875;
    Bool _t_Bool_2876 = not(_t_Bool_2875);
    (void)_t_Bool_2876;
    ;
    return _t_Bool_2876;
}

Bool U8_gte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2877 = U8_lt(a, b);
    (void)_t_Bool_2877;
    Bool _t_Bool_2878 = not(_t_Bool_2877);
    (void)_t_Bool_2878;
    ;
    return _t_Bool_2878;
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
void *Vec_len_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = Vec_len(_a0); return _r;
}
void Vec_push_take_dyn(void *_a0, void *_a1, void *_a2) {
    Vec_push_take(_a0, _a1, *(U32 *)_a2);
}
void *Vec_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Vec_size(); return _r;
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
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Array_new;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Array_len;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Array_get;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)Array_set;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Array_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Array_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Array_size_dyn;
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
    fprintf(stderr, "dyn_fn: unknown %s.%s\n", (char*)type_name->c_str, (char*)method->c_str);
    exit(1);
}

int main(void) {
    __til_docs_blob__ = (Str){.c_str=(U8*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)__til_docs_blob__;
    __til_kinds_blob__ = (Str){.c_str=(U8*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)__til_kinds_blob__;
    I64 _t_I64_2768 = 0;
    (void)_t_I64_2768;
    I64 _t_I64_2769 = 1;
    (void)_t_I64_2769;
    I64 _t_I64_2770 = I64_sub(_t_I64_2768, _t_I64_2769);
    (void)_t_I64_2770;
    CAP_LIT = I64_to_usize(_t_I64_2770);
    (void)CAP_LIT;
    I64 _t_I64_2771 = 0;
    (void)_t_I64_2771;
    I64 _t_I64_2772 = 2;
    (void)_t_I64_2772;
    I64 _t_I64_2773 = I64_sub(_t_I64_2771, _t_I64_2772);
    (void)_t_I64_2773;
    CAP_VIEW = I64_to_usize(_t_I64_2773);
    (void)CAP_VIEW;
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
