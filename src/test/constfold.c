#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef struct Vec Vec;
typedef struct Str Str;
typedef struct Dynamic Dynamic;
typedef struct Array Array;

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


F32 * F32_from_i64(I64 * val);
void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
Bool F32_lt(F32 * a, F32 * b);
Bool F32_gt(F32 * a, F32 * b);
Bool F32_neq(F32 * a, F32 * b);
Bool F32_lte(F32 * a, F32 * b);
Bool F32_gte(F32 * a, F32 * b);
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
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
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
Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap);
U32 * Array_len(Array * self);
void * Array_get(Array * self, U32 * i);
void Array_set(Array * self, U32 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
void panic(Str * loc_str, Array * parts);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void println(Array * parts);
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

F32 * F32_from_i64(I64 * val);
void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
Bool F32_lt(F32 * a, F32 * b);
Bool F32_gt(F32 * a, F32 * b);
Bool F32_neq(F32 * a, F32 * b);
Bool F32_lte(F32 * a, F32 * b);
Bool F32_gte(F32 * a, F32 * b);
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
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
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
Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap);
U32 * Array_len(Array * self);
void * Array_get(Array * self, U32 * i);
void Array_set(Array * self, U32 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
void panic(Str * loc_str, Array * parts);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void println(Array * parts);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
Str * poem(I64 * depth, Str * current, Str * s1, Str * s2);
Str * make_poem(Str * s1, Str * s2);
void test_lolalalo(void);

void *dyn_fn(Str *type_name, Str *method);
U32 dyn_size_of(Str *type_name);

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

F32 * F32_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func F32_from_i64_ext */
    F32 _t_F32_0 = F32_from_i64_ext(val);
    (void)_t_F32_0;
    { F32 *_r = malloc(sizeof(F32)); *_r = _t_F32_0; return _r; }
}

void F32_delete(F32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * F32_size(void) {
    I64 _t_I64_1 = 4;
    (void)_t_I64_1;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_1; return _r; }
}

Bool F32_lt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2 = 0;
    (void)_t_I64_2;
    I64 _t_I64_3 = 1;
    (void)_t_I64_3;
    I64 _t_I64_4 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_4;
    I64 _t_I64_5 = I64_sub(_t_I64_2, _t_I64_3);
    (void)_t_I64_5;
    ;
    ;
    Bool _t_Bool_6 = I64_eq(_t_I64_4, _t_I64_5);
    (void)_t_Bool_6;
    ;
    ;
    return _t_Bool_6;
}

Bool F32_gt(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_7 = F32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_7;
    I64 _t_I64_8 = 1;
    (void)_t_I64_8;
    Bool _t_Bool_9 = I64_eq(_t_I64_7, _t_I64_8);
    (void)_t_Bool_9;
    ;
    ;
    return _t_Bool_9;
}

Bool F32_neq(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_10 = F32_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_10;
    Bool _t_Bool_11 = not(_t_Bool_10);
    (void)_t_Bool_11;
    ;
    return _t_Bool_11;
}

Bool F32_lte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_12 = F32_gt(a, b);
    (void)_t_Bool_12;
    Bool _t_Bool_13 = not(_t_Bool_12);
    (void)_t_Bool_13;
    ;
    return _t_Bool_13;
}

Bool F32_gte(F32 * a, F32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_14 = F32_lt(a, b);
    (void)_t_Bool_14;
    Bool _t_Bool_15 = not(_t_Bool_14);
    (void)_t_Bool_15;
    ;
    return _t_Bool_15;
}

Str * U64_to_str(U64 val) {
    (void)val;
    /* TODO: nested func U64_to_str_ext */
    Str *_t_Str_16 = U64_to_str_ext(val);
    (void)_t_Str_16;
    return _t_Str_16;
}

U64 * U64_from_i64(I64 * val) {
    (void)val;
    /* TODO: nested func U64_from_i64_ext */
    U64 _t_U64_17 = U64_from_i64_ext(val);
    (void)_t_U64_17;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t_U64_17; return _r; }
}

void U64_inc(U64 * self) {
    (void)self;
    U64 _t_U64_18 = 1;
    (void)_t_U64_18;
    U64 _t_U64_19 = U64_add(DEREF(self), _t_U64_18);
    (void)_t_U64_19;
    ;
    *self = _t_U64_19;
    ;
}

void U64_dec(U64 * self) {
    (void)self;
    U64 _t_U64_20 = 1;
    (void)_t_U64_20;
    U64 _t_U64_21 = U64_sub(DEREF(self), _t_U64_20);
    (void)_t_U64_21;
    ;
    *self = _t_U64_21;
    ;
}

U64 * U64_unity(U64 * _self) {
    (void)_self;
    I64 _t_I64_22 = 1;
    (void)_t_I64_22;
    U64 _t_U64_23 = I64_to_u64(_t_I64_22);
    (void)_t_U64_23;
    ;
    { U64 *_r = malloc(sizeof(U64)); *_r = _t_U64_23; return _r; }
}

U64 U64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    U64 *au = a;
    (void)au;
    U64 *bu = b;
    (void)bu;
    Bool _t_Bool_25 = U64_lte(au, bu);
    (void)_t_Bool_25;
    if (_t_Bool_25) {
        U64 _t_U64_24 = U64_sub(DEREF(bu), DEREF(au));
        (void)_t_U64_24;
        ;
        return _t_U64_24;
    }
    ;
    U64 _t_U64_26 = U64_sub(DEREF(au), DEREF(bu));
    (void)_t_U64_26;
    return _t_U64_26;
}

void U64_delete(U64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U64_size(void) {
    I64 _t_I64_27 = 8;
    (void)_t_I64_27;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_27; return _r; }
}

Bool U64_lt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_28 = 0;
    (void)_t_I64_28;
    I64 _t_I64_29 = 1;
    (void)_t_I64_29;
    I64 _t_I64_30 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_30;
    I64 _t_I64_31 = I64_sub(_t_I64_28, _t_I64_29);
    (void)_t_I64_31;
    ;
    ;
    Bool _t_Bool_32 = I64_eq(_t_I64_30, _t_I64_31);
    (void)_t_Bool_32;
    ;
    ;
    return _t_Bool_32;
}

Bool U64_gt(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_33 = U64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_33;
    I64 _t_I64_34 = 1;
    (void)_t_I64_34;
    Bool _t_Bool_35 = I64_eq(_t_I64_33, _t_I64_34);
    (void)_t_Bool_35;
    ;
    ;
    return _t_Bool_35;
}

Bool U64_neq(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_36 = U64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_36;
    Bool _t_Bool_37 = not(_t_Bool_36);
    (void)_t_Bool_37;
    ;
    return _t_Bool_37;
}

Bool U64_lte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_38 = U64_gt(a, b);
    (void)_t_Bool_38;
    Bool _t_Bool_39 = not(_t_Bool_38);
    (void)_t_Bool_39;
    ;
    return _t_Bool_39;
}

Bool U64_gte(U64 * a, U64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_40 = U64_lt(a, b);
    (void)_t_Bool_40;
    Bool _t_Bool_41 = not(_t_Bool_40);
    (void)_t_Bool_41;
    ;
    return _t_Bool_41;
}

Str * U32_to_str(U32 * val) {
    (void)val;
    I64 _t_I64_42 = U32_to_i64(DEREF(val));
    (void)_t_I64_42;
    Str *_t_Str_43 = I64_to_str(&_t_I64_42);
    (void)_t_Str_43;
    ;
    return _t_Str_43;
}

void U32_inc(U32 * self) {
    (void)self;
    U32 _t_U32_44 = 1;
    (void)_t_U32_44;
    U32 _t_U32_45 = U32_add(DEREF(self), _t_U32_44);
    (void)_t_U32_45;
    ;
    *self = _t_U32_45;
    ;
}

void U32_dec(U32 * self) {
    (void)self;
    U32 _t_U32_46 = 1;
    (void)_t_U32_46;
    U32 _t_U32_47 = U32_sub(DEREF(self), _t_U32_46);
    (void)_t_U32_47;
    ;
    *self = _t_U32_47;
    ;
}

U32 * U32_unity(U32 * _self) {
    (void)_self;
    I64 _t_I64_48 = 1;
    (void)_t_I64_48;
    U32 _t_U32_49 = I64_to_u32(_t_I64_48);
    (void)_t_U32_49;
    ;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_U32_49; return _r; }
}

U64 U32_distance(void * a, void * b) {
    (void)a;
    (void)b;
    U32 *au = a;
    (void)au;
    U32 *bu = b;
    (void)bu;
    Bool _t_Bool_53 = U32_lte(au, bu);
    (void)_t_Bool_53;
    if (_t_Bool_53) {
        U32 _t_U32_50 = U32_sub(DEREF(bu), DEREF(au));
        (void)_t_U32_50;
        I64 _t_I64_51 = U32_to_i64(_t_U32_50);
        (void)_t_I64_51;
        ;
        U64 _t_U64_52 = I64_to_u64(_t_I64_51);
        (void)_t_U64_52;
        ;
        ;
        return _t_U64_52;
    }
    ;
    U32 _t_U32_54 = U32_sub(DEREF(au), DEREF(bu));
    (void)_t_U32_54;
    I64 _t_I64_55 = U32_to_i64(_t_U32_54);
    (void)_t_I64_55;
    ;
    U64 _t_U64_56 = I64_to_u64(_t_I64_55);
    (void)_t_U64_56;
    ;
    return _t_U64_56;
}

void U32_delete(U32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U32_size(void) {
    I64 _t_I64_57 = 4;
    (void)_t_I64_57;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_57; return _r; }
}

Bool U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_58 = 0;
    (void)_t_I64_58;
    I64 _t_I64_59 = 1;
    (void)_t_I64_59;
    I64 _t_I64_60 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_60;
    I64 _t_I64_61 = I64_sub(_t_I64_58, _t_I64_59);
    (void)_t_I64_61;
    ;
    ;
    Bool _t_Bool_62 = I64_eq(_t_I64_60, _t_I64_61);
    (void)_t_Bool_62;
    ;
    ;
    return _t_Bool_62;
}

Bool U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_63 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_63;
    I64 _t_I64_64 = 1;
    (void)_t_I64_64;
    Bool _t_Bool_65 = I64_eq(_t_I64_63, _t_I64_64);
    (void)_t_Bool_65;
    ;
    ;
    return _t_Bool_65;
}

Bool U32_neq(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_66 = U32_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_66;
    Bool _t_Bool_67 = not(_t_Bool_66);
    (void)_t_Bool_67;
    ;
    return _t_Bool_67;
}

Bool U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_68 = U32_gt(a, b);
    (void)_t_Bool_68;
    Bool _t_Bool_69 = not(_t_Bool_68);
    (void)_t_Bool_69;
    ;
    return _t_Bool_69;
}

Bool U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_70 = U32_lt(a, b);
    (void)_t_Bool_70;
    Bool _t_Bool_71 = not(_t_Bool_70);
    (void)_t_Bool_71;
    ;
    return _t_Bool_71;
}

Str * I32_to_str(I32 * val) {
    (void)val;
    I64 _t_I64_72 = I32_to_i64(DEREF(val));
    (void)_t_I64_72;
    Str *_t_Str_73 = I64_to_str(&_t_I64_72);
    (void)_t_Str_73;
    ;
    return _t_Str_73;
}

void I32_inc(I32 * self) {
    (void)self;
    I32 _t_I32_74 = 1;
    (void)_t_I32_74;
    I32 _t_I32_75 = I32_add(DEREF(self), _t_I32_74);
    (void)_t_I32_75;
    ;
    *self = _t_I32_75;
    ;
}

void I32_dec(I32 * self) {
    (void)self;
    I32 _t_I32_76 = 1;
    (void)_t_I32_76;
    I32 _t_I32_77 = I32_sub(DEREF(self), _t_I32_76);
    (void)_t_I32_77;
    ;
    *self = _t_I32_77;
    ;
}

I32 * I32_unity(I32 * _self) {
    (void)_self;
    I64 _t_I64_78 = 1;
    (void)_t_I64_78;
    I32 _t_I32_79 = I64_to_i32(_t_I64_78);
    (void)_t_I32_79;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_79; return _r; }
}

I32 * I32_neg(I32 * a) {
    (void)a;
    I64 _t_I64_80 = 0;
    (void)_t_I64_80;
    I64 _t_I64_81 = I32_to_i64(DEREF(a));
    (void)_t_I64_81;
    I64 _t_I64_82 = I64_sub(_t_I64_80, _t_I64_81);
    (void)_t_I64_82;
    ;
    ;
    I32 _t_I32_83 = I64_to_i32(_t_I64_82);
    (void)_t_I32_83;
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_83; return _r; }
}

I32 * I32_abs(I32 * a) {
    (void)a;
    I64 _t_I64_88 = I32_to_i64(DEREF(a));
    (void)_t_I64_88;
    I64 _t_I64_89 = 0;
    (void)_t_I64_89;
    Bool _t_Bool_90 = I64_lt(&_t_I64_88, &_t_I64_89);
    (void)_t_Bool_90;
    ;
    ;
    if (_t_Bool_90) {
        I64 _t_I64_84 = 0;
        (void)_t_I64_84;
        I64 _t_I64_85 = I32_to_i64(DEREF(a));
        (void)_t_I64_85;
        I64 _t_I64_86 = I64_sub(_t_I64_84, _t_I64_85);
        (void)_t_I64_86;
        ;
        ;
        I32 _t_I32_87 = I64_to_i32(_t_I64_86);
        (void)_t_I32_87;
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_87; return _r; }
    }
    ;
    I32 _t_I32_91 = I32_clone(a);
    (void)_t_I32_91;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t_I32_91; return _r; }
}

U64 I32_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I32 *au = a;
    (void)au;
    I32 *bu = b;
    (void)bu;
    Bool _t_Bool_95 = I32_lte(au, bu);
    (void)_t_Bool_95;
    if (_t_Bool_95) {
        I32 _t_I32_92 = I32_sub(DEREF(bu), DEREF(au));
        (void)_t_I32_92;
        I64 _t_I64_93 = I32_to_i64(_t_I32_92);
        (void)_t_I64_93;
        ;
        U64 _t_U64_94 = I64_to_u64(_t_I64_93);
        (void)_t_U64_94;
        ;
        ;
        return _t_U64_94;
    }
    ;
    I32 _t_I32_96 = I32_sub(DEREF(au), DEREF(bu));
    (void)_t_I32_96;
    I64 _t_I64_97 = I32_to_i64(_t_I32_96);
    (void)_t_I64_97;
    ;
    U64 _t_U64_98 = I64_to_u64(_t_I64_97);
    (void)_t_U64_98;
    ;
    return _t_U64_98;
}

void I32_delete(I32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I32_size(void) {
    I64 _t_I64_99 = 4;
    (void)_t_I64_99;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_99; return _r; }
}

Bool I32_lt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_100 = 0;
    (void)_t_I64_100;
    I64 _t_I64_101 = 1;
    (void)_t_I64_101;
    I64 _t_I64_102 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_102;
    I64 _t_I64_103 = I64_sub(_t_I64_100, _t_I64_101);
    (void)_t_I64_103;
    ;
    ;
    Bool _t_Bool_104 = I64_eq(_t_I64_102, _t_I64_103);
    (void)_t_Bool_104;
    ;
    ;
    return _t_Bool_104;
}

Bool I32_gt(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_105 = I32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_105;
    I64 _t_I64_106 = 1;
    (void)_t_I64_106;
    Bool _t_Bool_107 = I64_eq(_t_I64_105, _t_I64_106);
    (void)_t_Bool_107;
    ;
    ;
    return _t_Bool_107;
}

Bool I32_neq(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_108 = I32_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_108;
    Bool _t_Bool_109 = not(_t_Bool_108);
    (void)_t_Bool_109;
    ;
    return _t_Bool_109;
}

Bool I32_lte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_110 = I32_gt(a, b);
    (void)_t_Bool_110;
    Bool _t_Bool_111 = not(_t_Bool_110);
    (void)_t_Bool_111;
    ;
    return _t_Bool_111;
}

Bool I32_gte(I32 * a, I32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_112 = I32_lt(a, b);
    (void)_t_Bool_112;
    Bool _t_Bool_113 = not(_t_Bool_112);
    (void)_t_Bool_113;
    ;
    return _t_Bool_113;
}

Str * U8_to_str(U8 * val) {
    (void)val;
    I64 _t_I64_114 = U8_to_i64(DEREF(val));
    (void)_t_I64_114;
    Str *_t_Str_115 = I64_to_str(&_t_I64_114);
    (void)_t_Str_115;
    ;
    return _t_Str_115;
}

void U8_inc(U8 * self) {
    (void)self;
    U8 _t_U8_116 = 1;
    (void)_t_U8_116;
    U8 _t_U8_117 = U8_add(DEREF(self), _t_U8_116);
    (void)_t_U8_117;
    ;
    *self = _t_U8_117;
    ;
}

void U8_dec(U8 * self) {
    (void)self;
    U8 _t_U8_118 = 1;
    (void)_t_U8_118;
    U8 _t_U8_119 = U8_sub(DEREF(self), _t_U8_118);
    (void)_t_U8_119;
    ;
    *self = _t_U8_119;
    ;
}

U8 * U8_unity(U8 * _self) {
    (void)_self;
    I64 _t_I64_120 = 1;
    (void)_t_I64_120;
    U8 _t_U8_121 = I64_to_u8(_t_I64_120);
    (void)_t_U8_121;
    ;
    { U8 *_r = malloc(sizeof(U8)); *_r = _t_U8_121; return _r; }
}

U64 U8_distance(void * a, void * b) {
    (void)a;
    (void)b;
    U8 *au = a;
    (void)au;
    U8 *bu = b;
    (void)bu;
    Bool _t_Bool_124 = U8_lte(au, bu);
    (void)_t_Bool_124;
    if (_t_Bool_124) {
        U8 _t_U8_122 = U8_sub(DEREF(bu), DEREF(au));
        (void)_t_U8_122;
        U64 _t_U64_123 = U8_to_u64(_t_U8_122);
        (void)_t_U64_123;
        ;
        ;
        return _t_U64_123;
    }
    ;
    U8 _t_U8_125 = U8_sub(DEREF(au), DEREF(bu));
    (void)_t_U8_125;
    U64 _t_U64_126 = U8_to_u64(_t_U8_125);
    (void)_t_U64_126;
    ;
    return _t_U64_126;
}

void U8_delete(U8 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U8_size(void) {
    I64 _t_I64_127 = 1;
    (void)_t_I64_127;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_127; return _r; }
}

Bool U8_lt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_128 = 0;
    (void)_t_I64_128;
    I64 _t_I64_129 = 1;
    (void)_t_I64_129;
    I64 _t_I64_130 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_130;
    I64 _t_I64_131 = I64_sub(_t_I64_128, _t_I64_129);
    (void)_t_I64_131;
    ;
    ;
    Bool _t_Bool_132 = I64_eq(_t_I64_130, _t_I64_131);
    (void)_t_Bool_132;
    ;
    ;
    return _t_Bool_132;
}

Bool U8_gt(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_133 = U8_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_133;
    I64 _t_I64_134 = 1;
    (void)_t_I64_134;
    Bool _t_Bool_135 = I64_eq(_t_I64_133, _t_I64_134);
    (void)_t_Bool_135;
    ;
    ;
    return _t_Bool_135;
}

Bool U8_neq(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_136 = U8_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_136;
    Bool _t_Bool_137 = not(_t_Bool_136);
    (void)_t_Bool_137;
    ;
    return _t_Bool_137;
}

Bool U8_lte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_138 = U8_gt(a, b);
    (void)_t_Bool_138;
    Bool _t_Bool_139 = not(_t_Bool_138);
    (void)_t_Bool_139;
    ;
    return _t_Bool_139;
}

Bool U8_gte(U8 * a, U8 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_140 = U8_lt(a, b);
    (void)_t_Bool_140;
    Bool _t_Bool_141 = not(_t_Bool_140);
    (void)_t_Bool_141;
    ;
    return _t_Bool_141;
}

Vec * Vec_new(Str * elem_type, U32 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t_Bool_152 = Str_is_empty(elem_type);
    (void)_t_Bool_152;
    if (_t_Bool_152) {
        Str *_t_Str_142 = Str_lit("Str", 3ULL);
        (void)_t_Str_142;
        U32 _t_U32_143 = 16;
        (void)_t_U32_143;
        U32 _t_U32_144 = 1;
        (void)_t_U32_144;
        Array *_va_Array_0 = Array_new(_t_Str_142, &_t_U32_143, &_t_U32_144);
        (void)_va_Array_0;
        Str_delete(_t_Str_142, &(Bool){1});
        ;
        ;
        U32 _t_U32_145 = 0;
        (void)_t_U32_145;
        Str *_t_Str_146 = Str_lit("Vec.new: elem_type required", 27ULL);
        (void)_t_Str_146;
        Array_set(_va_Array_0, &_t_U32_145, _t_Str_146);
        ;
        Str *_t_Str_147 = Str_lit("./src/core/vec.til:23:19", 24ULL);
        (void)_t_Str_147;
        panic(_t_Str_147, _va_Array_0);
        Str_delete(_t_Str_147, &(Bool){1});
    }
    ;
    Str *_t_Str_153 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_153;
    Bool _t_Bool_154 = Str_eq(elem_type, _t_Str_153);
    (void)_t_Bool_154;
    Str_delete(_t_Str_153, &(Bool){1});
    if (_t_Bool_154) {
        void * _t_v_148 = malloc(DEREF(elem_size));
        (void)_t_v_148;
        U32 _t_U32_149 = 0;
        (void)_t_U32_149;
        I64 _t_I64_150 = 1;
        (void)_t_I64_150;
        Vec *_t_Vec_151 = malloc(sizeof(Vec));
        _t_Vec_151->data = _t_v_148;
        _t_Vec_151->count = _t_U32_149;
        _t_Vec_151->cap = _t_I64_150;
        _t_Vec_151->elem_size = DEREF(elem_size);
        { Str *_ca = Str_clone(elem_type); _t_Vec_151->elem_type = *_ca; free(_ca); }
        _t_Vec_151->elem_clone = (void *)(void *)default_clone;
        _t_Vec_151->elem_delete = (void *)(void *)default_delete;
        (void)_t_Vec_151;
        ;
        ;
        ;
        return _t_Vec_151;
    }
    ;
    void * _t_v_155 = malloc(DEREF(elem_size));
    (void)_t_v_155;
    U32 _t_U32_156 = 0;
    (void)_t_U32_156;
    I64 _t_I64_157 = 1;
    (void)_t_I64_157;
    void * _t_v_158 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_158;
    void * _t_v_159 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_159;
    Vec *_t_Vec_160 = malloc(sizeof(Vec));
    _t_Vec_160->data = _t_v_155;
    _t_Vec_160->count = _t_U32_156;
    _t_Vec_160->cap = _t_I64_157;
    _t_Vec_160->elem_size = DEREF(elem_size);
    { Str *_ca = Str_clone(elem_type); _t_Vec_160->elem_type = *_ca; free(_ca); }
    _t_Vec_160->elem_clone = _t_v_158;
    _t_Vec_160->elem_delete = _t_v_159;
    (void)_t_Vec_160;
    ;
    ;
    return _t_Vec_160;
}

U32 Vec_len(Vec * self) {
    (void)self;
    return self->count;
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t_Bool_165 = U32_eq(self->count, self->cap);
    (void)_t_Bool_165;
    if (_t_Bool_165) {
        U32 _t_U32_161 = 2;
        (void)_t_U32_161;
        U32 new_cap = U32_mul(self->cap, _t_U32_161);
        (void)new_cap;
        ;
        U32 _t_U64_162 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_162;
        void * _t_v_163 = realloc(self->data, _t_U64_162);
        (void)_t_v_163;
        ;
        self->data = _t_v_163;
        U32 _t_U32_164 = U32_clone(&new_cap);
        (void)_t_U32_164;
        ;
        self->cap = _t_U32_164;
        ;
    }
    ;
    U32 _t_U64_166 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_166;
    void *_t_v_167 = ptr_add(self->data, _t_U64_166);
    (void)_t_v_167;
    memcpy(_t_v_167, val, self->elem_size);
    ;
    free(val);
    U32 _t_U32_168 = 1;
    (void)_t_U32_168;
    U32 _t_U32_169 = U32_add(self->count, _t_U32_168);
    (void)_t_U32_169;
    ;
    self->count = _t_U32_169;
    ;
}

void Vec_append(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_182 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_182;
    Bool _t_Bool_183 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_183;
    Bool _t_Bool_184 = not(_t_Bool_182);
    (void)_t_Bool_184;
    ;
    Bool _t_Bool_185 = not(_t_Bool_183);
    (void)_t_Bool_185;
    ;
    Bool _t_Bool_186 = or(_t_Bool_184, _t_Bool_185);
    (void)_t_Bool_186;
    ;
    ;
    if (_t_Bool_186) {
        Str *_t_Str_170 = Str_lit("Str", 3ULL);
        (void)_t_Str_170;
        U32 _t_U32_171 = 16;
        (void)_t_U32_171;
        U32 _t_U32_172 = 1;
        (void)_t_U32_172;
        Array *_va_Array_1 = Array_new(_t_Str_170, &_t_U32_171, &_t_U32_172);
        (void)_va_Array_1;
        Str_delete(_t_Str_170, &(Bool){1});
        ;
        ;
        U32 _t_U32_173 = 0;
        (void)_t_U32_173;
        Str *_t_Str_174 = Str_lit("Vec.append: incompatible vecs", 29ULL);
        (void)_t_Str_174;
        Array_set(_va_Array_1, &_t_U32_173, _t_Str_174);
        ;
        Str *_t_Str_175 = Str_lit("./src/core/vec.til:50:19", 24ULL);
        (void)_t_Str_175;
        panic(_t_Str_175, _va_Array_1);
        Str_delete(_t_Str_175, &(Bool){1});
    }
    ;
    U32 _t_U32_187 = 0;
    (void)_t_U32_187;
    Bool _t_Bool_188 = U32_eq(other->count, _t_U32_187);
    (void)_t_Bool_188;
    ;
    if (_t_Bool_188) {
        ;
        Vec_delete(other, &(Bool){0});
        return;
    }
    ;
    U32 needed = U32_add(self->count, other->count);
    (void)needed;
    Bool _t_Bool_189 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_189;
    if (_t_Bool_189) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_176 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_176;
            if (_wcond_Bool_176) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_177 = 2;
            (void)_t_U32_177;
            U32 _t_U32_178 = U32_mul(new_cap, _t_U32_177);
            (void)_t_U32_178;
            ;
            new_cap = _t_U32_178;
            ;
        }
        U32 _t_U64_179 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_179;
        void * _t_v_180 = realloc(self->data, _t_U64_179);
        (void)_t_v_180;
        ;
        self->data = _t_v_180;
        U32 _t_U32_181 = U32_clone(&new_cap);
        (void)_t_U32_181;
        ;
        self->cap = _t_U32_181;
        ;
    }
    ;
    U32 _t_U64_190 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_190;
    void *_t_v_191 = ptr_add(self->data, _t_U64_190);
    (void)_t_v_191;
    U32 _t_U64_192 = U32_mul(other->count, self->elem_size);
    (void)_t_U64_192;
    memcpy(_t_v_191, other->data, _t_U64_192);
    ;
    ;
    U32 _t_U32_193 = U32_clone(&needed);
    (void)_t_U32_193;
    ;
    self->count = _t_U32_193;
    ;
    U32 _t_U32_194 = 0;
    (void)_t_U32_194;
    other->count = _t_U32_194;
    ;
    Vec_delete(other, &(Bool){0});
}

void Vec_move_from(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_218 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_218;
    Bool _t_Bool_219 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_219;
    Bool _t_Bool_220 = not(_t_Bool_218);
    (void)_t_Bool_220;
    ;
    Bool _t_Bool_221 = not(_t_Bool_219);
    (void)_t_Bool_221;
    ;
    Bool _t_Bool_222 = or(_t_Bool_220, _t_Bool_221);
    (void)_t_Bool_222;
    ;
    ;
    if (_t_Bool_222) {
        Str *_t_Str_195 = Str_lit("Str", 3ULL);
        (void)_t_Str_195;
        U32 _t_U32_196 = 16;
        (void)_t_U32_196;
        U32 _t_U32_197 = 1;
        (void)_t_U32_197;
        Array *_va_Array_2 = Array_new(_t_Str_195, &_t_U32_196, &_t_U32_197);
        (void)_va_Array_2;
        Str_delete(_t_Str_195, &(Bool){1});
        ;
        ;
        U32 _t_U32_198 = 0;
        (void)_t_U32_198;
        Str *_t_Str_199 = Str_lit("Vec.move_from: incompatible vecs", 32ULL);
        (void)_t_Str_199;
        Array_set(_va_Array_2, &_t_U32_198, _t_Str_199);
        ;
        Str *_t_Str_200 = Str_lit("./src/core/vec.til:77:19", 24ULL);
        (void)_t_Str_200;
        panic(_t_Str_200, _va_Array_2);
        Str_delete(_t_Str_200, &(Bool){1});
    }
    ;
    Bool _t_Bool_223 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_223;
    Str *_t_Str_224 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_224;
    Bool _t_Bool_225 = Str_eq(&self->elem_type, _t_Str_224);
    (void)_t_Bool_225;
    Str_delete(_t_Str_224, &(Bool){1});
    Bool _t_Bool_226 = not(_t_Bool_223);
    (void)_t_Bool_226;
    ;
    Bool _t_Bool_227 = not(_t_Bool_225);
    (void)_t_Bool_227;
    ;
    Bool _t_Bool_228 = and(_t_Bool_226, _t_Bool_227);
    (void)_t_Bool_228;
    ;
    ;
    if (_t_Bool_228) {
        {
            U32 _re_U32_201 = self->count;
            (void)_re_U32_201;
            U32 _rc_U32_201 = 0;
            (void)_rc_U32_201;
            Bool _t_Bool_210 = U32_lte(&_rc_U32_201, &_re_U32_201);
            (void)_t_Bool_210;
            if (_t_Bool_210) {
                while (1) {
                    Bool _wcond_Bool_202 = U32_lt(&_rc_U32_201, &_re_U32_201);
                    (void)_wcond_Bool_202;
                    if (_wcond_Bool_202) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_201);
                    (void)i;
                    U32_inc(&_rc_U32_201);
                    U32 _t_U64_203 = U32_mul(i, self->elem_size);
                    (void)_t_U64_203;
                    ;
                    void *_t_v_204 = ptr_add(self->data, _t_U64_203);
                    (void)_t_v_204;
                    Bool _t_Bool_205 = 0;
                    (void)_t_Bool_205;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_204, &_t_Bool_205);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_206 = U32_gt(&_rc_U32_201, &_re_U32_201);
                    (void)_wcond_Bool_206;
                    if (_wcond_Bool_206) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_201);
                    (void)i;
                    U32_dec(&_rc_U32_201);
                    U32 _t_U64_207 = U32_mul(i, self->elem_size);
                    (void)_t_U64_207;
                    ;
                    void *_t_v_208 = ptr_add(self->data, _t_U64_207);
                    (void)_t_v_208;
                    Bool _t_Bool_209 = 0;
                    (void)_t_Bool_209;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_208, &_t_Bool_209);
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
    Bool _t_Bool_229 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_229;
    if (_t_Bool_229) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_211 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_211;
            if (_wcond_Bool_211) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_212 = 2;
            (void)_t_U32_212;
            U32 _t_U32_213 = U32_mul(new_cap, _t_U32_212);
            (void)_t_U32_213;
            ;
            new_cap = _t_U32_213;
            ;
        }
        U32 _t_U64_214 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_214;
        void * _t_v_215 = realloc(self->data, _t_U64_214);
        (void)_t_v_215;
        ;
        self->data = _t_v_215;
        U32 _t_U32_216 = U32_clone(&new_cap);
        (void)_t_U32_216;
        ;
        self->cap = _t_U32_216;
        ;
    }
    ;
    U32 _t_U32_230 = 0;
    (void)_t_U32_230;
    Bool _t_Bool_231 = U32_gt(&needed, &_t_U32_230);
    (void)_t_Bool_231;
    ;
    if (_t_Bool_231) {
        U32 _t_U64_217 = U32_mul(needed, self->elem_size);
        (void)_t_U64_217;
        memcpy(self->data, other->data, _t_U64_217);
        ;
    }
    ;
    U32 _t_U32_232 = U32_clone(&needed);
    (void)_t_U32_232;
    ;
    self->count = _t_U32_232;
    ;
    U32 _t_U32_233 = 0;
    (void)_t_U32_233;
    other->count = _t_U32_233;
    ;
}

void * Vec_get(Vec * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_248 = U32_gte(i, &self->count);
    (void)_t_Bool_248;
    if (_t_Bool_248) {
        Str *_t_Str_234 = Str_lit("Str", 3ULL);
        (void)_t_Str_234;
        U32 _t_U32_235 = 16;
        (void)_t_U32_235;
        U32 _t_U32_236 = 5;
        (void)_t_U32_236;
        Array *_va_Array_3 = Array_new(_t_Str_234, &_t_U32_235, &_t_U32_236);
        (void)_va_Array_3;
        Str_delete(_t_Str_234, &(Bool){1});
        ;
        ;
        U32 _t_U32_237 = 0;
        (void)_t_U32_237;
        Str *_t_Str_238 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t_Str_238;
        Array_set(_va_Array_3, &_t_U32_237, _t_Str_238);
        ;
        U32 _t_U32_239 = 1;
        (void)_t_U32_239;
        Str *_t_Str_240 = U32_to_str(i);
        (void)_t_Str_240;
        Array_set(_va_Array_3, &_t_U32_239, _t_Str_240);
        ;
        U32 _t_U32_241 = 2;
        (void)_t_U32_241;
        Str *_t_Str_242 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_242;
        Array_set(_va_Array_3, &_t_U32_241, _t_Str_242);
        ;
        U32 _t_U32_243 = 3;
        (void)_t_U32_243;
        Str *_t_Str_244 = U32_to_str(&self->count);
        (void)_t_Str_244;
        Array_set(_va_Array_3, &_t_U32_243, _t_Str_244);
        ;
        U32 _t_U32_245 = 4;
        (void)_t_U32_245;
        Str *_t_Str_246 = Str_lit(")", 1ULL);
        (void)_t_Str_246;
        Array_set(_va_Array_3, &_t_U32_245, _t_Str_246);
        ;
        Str *_t_Str_247 = Str_lit("./src/core/vec.til:102:19", 25ULL);
        (void)_t_Str_247;
        panic(_t_Str_247, _va_Array_3);
        Str_delete(_t_Str_247, &(Bool){1});
    }
    ;
    U32 _t_U64_249 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_249;
    void *_t_v_250 = ptr_add(self->data, _t_U64_249);
    (void)_t_v_250;
    ;
    return _t_v_250;
}

void * Vec_pop(Vec * self) {
    (void)self;
    U32 _t_U32_257 = 0;
    (void)_t_U32_257;
    Bool _t_Bool_258 = U32_eq(self->count, _t_U32_257);
    (void)_t_Bool_258;
    ;
    if (_t_Bool_258) {
        Str *_t_Str_251 = Str_lit("Str", 3ULL);
        (void)_t_Str_251;
        U32 _t_U32_252 = 16;
        (void)_t_U32_252;
        U32 _t_U32_253 = 1;
        (void)_t_U32_253;
        Array *_va_Array_4 = Array_new(_t_Str_251, &_t_U32_252, &_t_U32_253);
        (void)_va_Array_4;
        Str_delete(_t_Str_251, &(Bool){1});
        ;
        ;
        U32 _t_U32_254 = 0;
        (void)_t_U32_254;
        Str *_t_Str_255 = Str_lit("Vec.pop: empty vec", 18ULL);
        (void)_t_Str_255;
        Array_set(_va_Array_4, &_t_U32_254, _t_Str_255);
        ;
        Str *_t_Str_256 = Str_lit("./src/core/vec.til:109:19", 25ULL);
        (void)_t_Str_256;
        panic(_t_Str_256, _va_Array_4);
        Str_delete(_t_Str_256, &(Bool){1});
    }
    ;
    U32 _t_U32_259 = 1;
    (void)_t_U32_259;
    U32 last = U32_sub(self->count, _t_U32_259);
    (void)last;
    ;
    void * out = malloc(self->elem_size);
    (void)out;
    U32 _t_U64_260 = U32_mul(last, self->elem_size);
    (void)_t_U64_260;
    void *_t_v_261 = ptr_add(self->data, _t_U64_260);
    (void)_t_v_261;
    memcpy(out, _t_v_261, self->elem_size);
    ;
    U32 _t_U32_262 = U32_clone(&last);
    (void)_t_U32_262;
    ;
    self->count = _t_U32_262;
    ;
    return out;
}

Vec * Vec_take_prefix(Vec * self, U32 * n) {
    (void)self;
    (void)n;
    Bool _t_Bool_282 = U32_gt(n, &self->count);
    (void)_t_Bool_282;
    if (_t_Bool_282) {
        Str *_t_Str_263 = Str_lit("Str", 3ULL);
        (void)_t_Str_263;
        U32 _t_U32_264 = 16;
        (void)_t_U32_264;
        U32 _t_U32_265 = 5;
        (void)_t_U32_265;
        Array *_va_Array_5 = Array_new(_t_Str_263, &_t_U32_264, &_t_U32_265);
        (void)_va_Array_5;
        Str_delete(_t_Str_263, &(Bool){1});
        ;
        ;
        U32 _t_U32_266 = 0;
        (void)_t_U32_266;
        Str *_t_Str_267 = Str_lit("Vec.take_prefix: count ", 23ULL);
        (void)_t_Str_267;
        Array_set(_va_Array_5, &_t_U32_266, _t_Str_267);
        ;
        U32 _t_U32_268 = 1;
        (void)_t_U32_268;
        Str *_t_Str_269 = U32_to_str(n);
        (void)_t_Str_269;
        Array_set(_va_Array_5, &_t_U32_268, _t_Str_269);
        ;
        U32 _t_U32_270 = 2;
        (void)_t_U32_270;
        Str *_t_Str_271 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_271;
        Array_set(_va_Array_5, &_t_U32_270, _t_Str_271);
        ;
        U32 _t_U32_272 = 3;
        (void)_t_U32_272;
        Str *_t_Str_273 = U32_to_str(&self->count);
        (void)_t_Str_273;
        Array_set(_va_Array_5, &_t_U32_272, _t_Str_273);
        ;
        U32 _t_U32_274 = 4;
        (void)_t_U32_274;
        Str *_t_Str_275 = Str_lit(")", 1ULL);
        (void)_t_Str_275;
        Array_set(_va_Array_5, &_t_U32_274, _t_Str_275);
        ;
        Str *_t_Str_276 = Str_lit("./src/core/vec.til:120:19", 25ULL);
        (void)_t_Str_276;
        panic(_t_Str_276, _va_Array_5);
        Str_delete(_t_Str_276, &(Bool){1});
    }
    ;
    U32 prefix_cap = 1;
    (void)prefix_cap;
    U32 _t_U32_283 = 0;
    (void)_t_U32_283;
    Bool _t_Bool_284 = U32_gt(n, &_t_U32_283);
    (void)_t_Bool_284;
    ;
    if (_t_Bool_284) {
        U32 _t_U32_277 = U32_clone(n);
        (void)_t_U32_277;
        prefix_cap = _t_U32_277;
        ;
    }
    ;
    U32 _t_U64_285 = U32_mul(prefix_cap, self->elem_size);
    (void)_t_U64_285;
    void * prefix_data = malloc(_t_U64_285);
    (void)prefix_data;
    ;
    U32 _t_U32_286 = 0;
    (void)_t_U32_286;
    Bool _t_Bool_287 = U32_gt(n, &_t_U32_286);
    (void)_t_Bool_287;
    ;
    if (_t_Bool_287) {
        U32 _t_U64_278 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_278;
        memcpy(prefix_data, self->data, _t_U64_278);
        ;
    }
    ;
    U32 tail_count = U32_sub(self->count, DEREF(n));
    (void)tail_count;
    U32 _t_U32_288 = 0;
    (void)_t_U32_288;
    Bool _t_Bool_289 = U32_gt(&tail_count, &_t_U32_288);
    (void)_t_Bool_289;
    ;
    if (_t_Bool_289) {
        U32 _t_U64_279 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_279;
        void *_t_v_280 = ptr_add(self->data, _t_U64_279);
        (void)_t_v_280;
        U32 _t_U64_281 = U32_mul(tail_count, self->elem_size);
        (void)_t_U64_281;
        memmove(self->data, _t_v_280, _t_U64_281);
        ;
        ;
    }
    ;
    U32 _t_U32_290 = U32_clone(&tail_count);
    (void)_t_U32_290;
    ;
    self->count = _t_U32_290;
    ;
    Vec *_t_Vec_291 = malloc(sizeof(Vec));
    _t_Vec_291->data = prefix_data;
    _t_Vec_291->count = DEREF(n);
    _t_Vec_291->cap = prefix_cap;
    _t_Vec_291->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_291->elem_type = *_ca; free(_ca); }
    _t_Vec_291->elem_clone = (void *)self->elem_clone;
    _t_Vec_291->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_291;
    ;
    return _t_Vec_291;
}

void Vec_set(Vec * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_306 = U32_gte(i, &self->count);
    (void)_t_Bool_306;
    if (_t_Bool_306) {
        Str *_t_Str_292 = Str_lit("Str", 3ULL);
        (void)_t_Str_292;
        U32 _t_U32_293 = 16;
        (void)_t_U32_293;
        U32 _t_U32_294 = 5;
        (void)_t_U32_294;
        Array *_va_Array_6 = Array_new(_t_Str_292, &_t_U32_293, &_t_U32_294);
        (void)_va_Array_6;
        Str_delete(_t_Str_292, &(Bool){1});
        ;
        ;
        U32 _t_U32_295 = 0;
        (void)_t_U32_295;
        Str *_t_Str_296 = Str_lit("Vec.set: index ", 15ULL);
        (void)_t_Str_296;
        Array_set(_va_Array_6, &_t_U32_295, _t_Str_296);
        ;
        U32 _t_U32_297 = 1;
        (void)_t_U32_297;
        Str *_t_Str_298 = U32_to_str(i);
        (void)_t_Str_298;
        Array_set(_va_Array_6, &_t_U32_297, _t_Str_298);
        ;
        U32 _t_U32_299 = 2;
        (void)_t_U32_299;
        Str *_t_Str_300 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_300;
        Array_set(_va_Array_6, &_t_U32_299, _t_Str_300);
        ;
        U32 _t_U32_301 = 3;
        (void)_t_U32_301;
        Str *_t_Str_302 = U32_to_str(&self->count);
        (void)_t_Str_302;
        Array_set(_va_Array_6, &_t_U32_301, _t_Str_302);
        ;
        U32 _t_U32_303 = 4;
        (void)_t_U32_303;
        Str *_t_Str_304 = Str_lit(")", 1ULL);
        (void)_t_Str_304;
        Array_set(_va_Array_6, &_t_U32_303, _t_Str_304);
        ;
        Str *_t_Str_305 = Str_lit("./src/core/vec.til:142:19", 25ULL);
        (void)_t_Str_305;
        panic(_t_Str_305, _va_Array_6);
        Str_delete(_t_Str_305, &(Bool){1});
    }
    ;
    U32 _t_U64_307 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_307;
    void *_t_v_308 = ptr_add(self->data, _t_U64_307);
    (void)_t_v_308;
    memcpy(_t_v_308, val, self->elem_size);
    ;
    free(val);
}

void Vec_push_take(Vec * self, Vec * src, U32 i) {
    (void)self;
    (void)src;
    (void)i;
    Bool _t_Bool_333 = U32_gte(&i, &src->count);
    (void)_t_Bool_333;
    if (_t_Bool_333) {
        Str *_t_Str_309 = Str_lit("Str", 3ULL);
        (void)_t_Str_309;
        U32 _t_U32_310 = 16;
        (void)_t_U32_310;
        U32 _t_U32_311 = 5;
        (void)_t_U32_311;
        Array *_va_Array_7 = Array_new(_t_Str_309, &_t_U32_310, &_t_U32_311);
        (void)_va_Array_7;
        Str_delete(_t_Str_309, &(Bool){1});
        ;
        ;
        U32 _t_U32_312 = 0;
        (void)_t_U32_312;
        Str *_t_Str_313 = Str_lit("Vec.push_take: index ", 21ULL);
        (void)_t_Str_313;
        Array_set(_va_Array_7, &_t_U32_312, _t_Str_313);
        ;
        U32 _t_U32_314 = 1;
        (void)_t_U32_314;
        Str *_t_Str_315 = U32_to_str(&i);
        (void)_t_Str_315;
        Array_set(_va_Array_7, &_t_U32_314, _t_Str_315);
        ;
        U32 _t_U32_316 = 2;
        (void)_t_U32_316;
        Str *_t_Str_317 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_317;
        Array_set(_va_Array_7, &_t_U32_316, _t_Str_317);
        ;
        U32 _t_U32_318 = 3;
        (void)_t_U32_318;
        Str *_t_Str_319 = U32_to_str(&src->count);
        (void)_t_Str_319;
        Array_set(_va_Array_7, &_t_U32_318, _t_Str_319);
        ;
        U32 _t_U32_320 = 4;
        (void)_t_U32_320;
        Str *_t_Str_321 = Str_lit(")", 1ULL);
        (void)_t_Str_321;
        Array_set(_va_Array_7, &_t_U32_320, _t_Str_321);
        ;
        Str *_t_Str_322 = Str_lit("./src/core/vec.til:153:19", 25ULL);
        (void)_t_Str_322;
        panic(_t_Str_322, _va_Array_7);
        Str_delete(_t_Str_322, &(Bool){1});
    }
    ;
    Bool _t_Bool_334 = U32_eq(self->elem_size, src->elem_size);
    (void)_t_Bool_334;
    Bool _t_Bool_335 = Str_eq(&self->elem_type, &src->elem_type);
    (void)_t_Bool_335;
    Bool _t_Bool_336 = not(_t_Bool_334);
    (void)_t_Bool_336;
    ;
    Bool _t_Bool_337 = not(_t_Bool_335);
    (void)_t_Bool_337;
    ;
    Bool _t_Bool_338 = or(_t_Bool_336, _t_Bool_337);
    (void)_t_Bool_338;
    ;
    ;
    if (_t_Bool_338) {
        Str *_t_Str_323 = Str_lit("Str", 3ULL);
        (void)_t_Str_323;
        U32 _t_U32_324 = 16;
        (void)_t_U32_324;
        U32 _t_U32_325 = 1;
        (void)_t_U32_325;
        Array *_va_Array_8 = Array_new(_t_Str_323, &_t_U32_324, &_t_U32_325);
        (void)_va_Array_8;
        Str_delete(_t_Str_323, &(Bool){1});
        ;
        ;
        U32 _t_U32_326 = 0;
        (void)_t_U32_326;
        Str *_t_Str_327 = Str_lit("Vec.push_take: incompatible vecs", 32ULL);
        (void)_t_Str_327;
        Array_set(_va_Array_8, &_t_U32_326, _t_Str_327);
        ;
        Str *_t_Str_328 = Str_lit("./src/core/vec.til:156:19", 25ULL);
        (void)_t_Str_328;
        panic(_t_Str_328, _va_Array_8);
        Str_delete(_t_Str_328, &(Bool){1});
    }
    ;
    Bool _t_Bool_339 = U32_eq(self->count, self->cap);
    (void)_t_Bool_339;
    if (_t_Bool_339) {
        U32 _t_U32_329 = 2;
        (void)_t_U32_329;
        U32 new_cap = U32_mul(self->cap, _t_U32_329);
        (void)new_cap;
        ;
        U32 _t_U64_330 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_330;
        void * _t_v_331 = realloc(self->data, _t_U64_330);
        (void)_t_v_331;
        ;
        self->data = _t_v_331;
        U32 _t_U32_332 = U32_clone(&new_cap);
        (void)_t_U32_332;
        ;
        self->cap = _t_U32_332;
        ;
    }
    ;
    U32 _t_U64_340 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_340;
    U32 _t_U64_341 = U32_mul(i, src->elem_size);
    (void)_t_U64_341;
    void *_t_v_342 = ptr_add(self->data, _t_U64_340);
    (void)_t_v_342;
    void *_t_v_343 = ptr_add(src->data, _t_U64_341);
    (void)_t_v_343;
    memcpy(_t_v_342, _t_v_343, self->elem_size);
    ;
    ;
    U32 _t_U64_344 = U32_mul(i, src->elem_size);
    (void)_t_U64_344;
    void *_t_v_345 = ptr_add(src->data, _t_U64_344);
    (void)_t_v_345;
    I32 _t_I32_346 = 0;
    (void)_t_I32_346;
    memset(_t_v_345, _t_I32_346, src->elem_size);
    ;
    ;
    U32 _t_U32_347 = 1;
    (void)_t_U32_347;
    U32 _t_U32_348 = U32_add(self->count, _t_U32_347);
    (void)_t_U32_348;
    ;
    self->count = _t_U32_348;
    ;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_360 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_360;
    Str *_t_Str_361 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_361;
    Bool _t_Bool_362 = Str_eq(&self->elem_type, _t_Str_361);
    (void)_t_Bool_362;
    Str_delete(_t_Str_361, &(Bool){1});
    Bool _t_Bool_363 = not(_t_Bool_360);
    (void)_t_Bool_363;
    ;
    Bool _t_Bool_364 = not(_t_Bool_362);
    (void)_t_Bool_364;
    ;
    Bool _t_Bool_365 = and(_t_Bool_363, _t_Bool_364);
    (void)_t_Bool_365;
    ;
    ;
    if (_t_Bool_365) {
        {
            U32 _re_U32_349 = self->count;
            (void)_re_U32_349;
            U32 _rc_U32_349 = 0;
            (void)_rc_U32_349;
            Bool _t_Bool_358 = U32_lte(&_rc_U32_349, &_re_U32_349);
            (void)_t_Bool_358;
            if (_t_Bool_358) {
                while (1) {
                    Bool _wcond_Bool_350 = U32_lt(&_rc_U32_349, &_re_U32_349);
                    (void)_wcond_Bool_350;
                    if (_wcond_Bool_350) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_349);
                    (void)i;
                    U32_inc(&_rc_U32_349);
                    U32 _t_U64_351 = U32_mul(i, self->elem_size);
                    (void)_t_U64_351;
                    ;
                    void *_t_v_352 = ptr_add(self->data, _t_U64_351);
                    (void)_t_v_352;
                    Bool _t_Bool_353 = 0;
                    (void)_t_Bool_353;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_352, &_t_Bool_353);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_354 = U32_gt(&_rc_U32_349, &_re_U32_349);
                    (void)_wcond_Bool_354;
                    if (_wcond_Bool_354) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_349);
                    (void)i;
                    U32_dec(&_rc_U32_349);
                    U32 _t_U64_355 = U32_mul(i, self->elem_size);
                    (void)_t_U64_355;
                    ;
                    void *_t_v_356 = ptr_add(self->data, _t_U64_355);
                    (void)_t_v_356;
                    Bool _t_Bool_357 = 0;
                    (void)_t_Bool_357;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_356, &_t_Bool_357);
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
    Bool _t_Bool_366 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_366;
    Bool _t_Bool_367 = not(_t_Bool_366);
    (void)_t_Bool_367;
    ;
    if (_t_Bool_367) {
        Bool _t_Bool_359 = 0;
        (void)_t_Bool_359;
        Str_delete(&self->elem_type, &_t_Bool_359);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U32 _t_U64_381 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_381;
    void * new_data = malloc(_t_U64_381);
    (void)new_data;
    ;
    Bool _t_Bool_382 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_382;
    Str *_t_Str_383 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_383;
    Bool _t_Bool_384 = Str_eq(&self->elem_type, _t_Str_383);
    (void)_t_Bool_384;
    Str_delete(_t_Str_383, &(Bool){1});
    Bool _t_Bool_385 = not(_t_Bool_382);
    (void)_t_Bool_385;
    ;
    Bool _t_Bool_386 = not(_t_Bool_384);
    (void)_t_Bool_386;
    ;
    Bool _t_Bool_387 = and(_t_Bool_385, _t_Bool_386);
    (void)_t_Bool_387;
    ;
    ;
    if (_t_Bool_387) {
        {
            U32 _re_U32_368 = self->count;
            (void)_re_U32_368;
            U32 _rc_U32_368 = 0;
            (void)_rc_U32_368;
            Bool _t_Bool_379 = U32_lte(&_rc_U32_368, &_re_U32_368);
            (void)_t_Bool_379;
            if (_t_Bool_379) {
                while (1) {
                    Bool _wcond_Bool_369 = U32_lt(&_rc_U32_368, &_re_U32_368);
                    (void)_wcond_Bool_369;
                    if (_wcond_Bool_369) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_368);
                    (void)i;
                    U32_inc(&_rc_U32_368);
                    U32 _t_U64_370 = U32_mul(i, self->elem_size);
                    (void)_t_U64_370;
                    void *_t_v_371 = ptr_add(self->data, _t_U64_370);
                    (void)_t_v_371;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_371);
                    (void)cloned;
                    ;
                    U32 _t_U64_372 = U32_mul(i, self->elem_size);
                    (void)_t_U64_372;
                    ;
                    void *_t_v_373 = ptr_add(new_data, _t_U64_372);
                    (void)_t_v_373;
                    memcpy(_t_v_373, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_374 = U32_gt(&_rc_U32_368, &_re_U32_368);
                    (void)_wcond_Bool_374;
                    if (_wcond_Bool_374) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_368);
                    (void)i;
                    U32_dec(&_rc_U32_368);
                    U32 _t_U64_375 = U32_mul(i, self->elem_size);
                    (void)_t_U64_375;
                    void *_t_v_376 = ptr_add(self->data, _t_U64_375);
                    (void)_t_v_376;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_376);
                    (void)cloned;
                    ;
                    U32 _t_U64_377 = U32_mul(i, self->elem_size);
                    (void)_t_U64_377;
                    ;
                    void *_t_v_378 = ptr_add(new_data, _t_U64_377);
                    (void)_t_v_378;
                    memcpy(_t_v_378, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            }
            ;
            ;
            ;
        }
    } else {
        U32 _t_U64_380 = U32_mul(self->count, self->elem_size);
        (void)_t_U64_380;
        memcpy(new_data, self->data, _t_U64_380);
        ;
    }
    ;
    Vec *_t_Vec_388 = malloc(sizeof(Vec));
    _t_Vec_388->data = new_data;
    _t_Vec_388->count = self->count;
    _t_Vec_388->cap = self->cap;
    _t_Vec_388->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_388->elem_type = *_ca; free(_ca); }
    _t_Vec_388->elem_clone = (void *)self->elem_clone;
    _t_Vec_388->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_388;
    return _t_Vec_388;
}

U32 Vec_size(void) {
    I64 _t_I64_389 = 56;
    (void)_t_I64_389;
    return _t_I64_389;
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    (void)total;
    {
        Array *_fc_Array_390 = parts;
        (void)_fc_Array_390;
        U32 _fi_USize_390 = 0;
        (void)_fi_USize_390;
        while (1) {
            U32 _t_U32_392; { U32 *_hp = (U32 *)Array_len(_fc_Array_390); _t_U32_392 = *_hp; free(_hp); }
            (void)_t_U32_392;
            Bool _wcond_Bool_391 = U32_lt(&_fi_USize_390, &_t_U32_392);
            (void)_wcond_Bool_391;
            ;
            if (_wcond_Bool_391) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_390, &_fi_USize_390);
            (void)s;
            U32 _t_U32_393 = 1;
            (void)_t_U32_393;
            U32 _t_U32_394 = U32_add(_fi_USize_390, _t_U32_393);
            (void)_t_U32_394;
            ;
            _fi_USize_390 = _t_U32_394;
            ;
            U32 _t_U32_395 = Str_len(s);
            (void)_t_U32_395;
            U32 _t_U32_396 = U32_add(total, _t_U32_395);
            (void)_t_U32_396;
            ;
            total = _t_U32_396;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    (void)out;
    ;
    {
        Array *_fc_Array_397 = parts;
        (void)_fc_Array_397;
        U32 _fi_USize_397 = 0;
        (void)_fi_USize_397;
        while (1) {
            U32 _t_U32_399; { U32 *_hp = (U32 *)Array_len(_fc_Array_397); _t_U32_399 = *_hp; free(_hp); }
            (void)_t_U32_399;
            Bool _wcond_Bool_398 = U32_lt(&_fi_USize_397, &_t_U32_399);
            (void)_wcond_Bool_398;
            ;
            if (_wcond_Bool_398) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_397, &_fi_USize_397);
            (void)s;
            U32 _t_U32_400 = 1;
            (void)_t_U32_400;
            U32 _t_U32_401 = U32_add(_fi_USize_397, _t_U32_400);
            (void)_t_U32_401;
            ;
            _fi_USize_397 = _t_U32_401;
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
    Bool _t_Bool_408 = U32_gte(i, &self->count);
    (void)_t_Bool_408;
    if (_t_Bool_408) {
        Str *_t_Str_402 = Str_lit("Str", 3ULL);
        (void)_t_Str_402;
        U32 _t_U32_403 = 16;
        (void)_t_U32_403;
        U32 _t_U32_404 = 1;
        (void)_t_U32_404;
        Array *_va_Array_9 = Array_new(_t_Str_402, &_t_U32_403, &_t_U32_404);
        (void)_va_Array_9;
        Str_delete(_t_Str_402, &(Bool){1});
        ;
        ;
        U32 _t_U32_405 = 0;
        (void)_t_U32_405;
        Str *_t_Str_406 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t_Str_406;
        Array_set(_va_Array_9, &_t_U32_405, _t_Str_406);
        ;
        Str *_t_Str_407 = Str_lit("./src/core/str.til:38:19", 24ULL);
        (void)_t_Str_407;
        panic(_t_Str_407, _va_Array_9);
        Str_delete(_t_Str_407, &(Bool){1});
    }
    ;
    void *_t_v_409 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_409;
    return _t_v_409;
}

U8 * Str_byte_at(Str * self, U32 * i) {
    (void)self;
    (void)i;
    void *_t_v_410 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_410;
    return _t_v_410;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    (void)min_len;
    Bool _t_Bool_419 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_419;
    if (_t_Bool_419) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_411 = U32_clone(&min_len);
        (void)_re_U32_411;
        U32 _rc_U32_411 = 0;
        (void)_rc_U32_411;
        Bool _t_Bool_418 = U32_lte(&_rc_U32_411, &_re_U32_411);
        (void)_t_Bool_418;
        if (_t_Bool_418) {
            while (1) {
                Bool _wcond_Bool_412 = U32_lt(&_rc_U32_411, &_re_U32_411);
                (void)_wcond_Bool_412;
                if (_wcond_Bool_412) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_411);
                (void)i;
                U32_inc(&_rc_U32_411);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_413 = 0;
                (void)_t_I64_413;
                Bool _t_Bool_414 = I64_neq(&c, &_t_I64_413);
                (void)_t_Bool_414;
                ;
                if (_t_Bool_414) {
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
                Bool _wcond_Bool_415 = U32_gt(&_rc_U32_411, &_re_U32_411);
                (void)_wcond_Bool_415;
                if (_wcond_Bool_415) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_411);
                (void)i;
                U32_dec(&_rc_U32_411);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_416 = 0;
                (void)_t_I64_416;
                Bool _t_Bool_417 = I64_neq(&c, &_t_I64_416);
                (void)_t_Bool_417;
                ;
                if (_t_Bool_417) {
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
    I64 _t_I64_420 = U32_cmp(a->count, b->count);
    (void)_t_I64_420;
    return _t_I64_420;
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_421 = U32_add(a->count, b->count);
    (void)_t_U32_421;
    Str *out = Str_with_capacity(&_t_U32_421);
    (void)out;
    ;
    Str_push_str(out, a);
    Str_push_str(out, b);
    return out;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_422 = 1;
    (void)_t_U32_422;
    U32 _t_U64_423 = U32_add(DEREF(n), _t_U32_422);
    (void)_t_U64_423;
    ;
    void * buf = malloc(_t_U64_423);
    (void)buf;
    ;
    I32 _t_I32_424 = 0;
    (void)_t_I32_424;
    U64 _t_U64_425 = 1;
    (void)_t_U64_425;
    memset(buf, _t_I32_424, _t_U64_425);
    ;
    ;
    I64 _t_I64_426 = 0;
    (void)_t_I64_426;
    Str *_t_Str_427 = malloc(sizeof(Str));
    _t_Str_427->c_str = buf;
    _t_Str_427->count = _t_I64_426;
    _t_Str_427->cap = DEREF(n);
    (void)_t_Str_427;
    ;
    return _t_Str_427;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_440 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_440;
    if (_t_Bool_440) {
        Str *_t_Str_428 = Str_lit("Str", 3ULL);
        (void)_t_Str_428;
        U32 _t_U32_429 = 16;
        (void)_t_U32_429;
        U32 _t_U32_430 = 1;
        (void)_t_U32_430;
        Array *_va_Array_10 = Array_new(_t_Str_428, &_t_U32_429, &_t_U32_430);
        (void)_va_Array_10;
        Str_delete(_t_Str_428, &(Bool){1});
        ;
        ;
        U32 _t_U32_431 = 0;
        (void)_t_U32_431;
        Str *_t_Str_432 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t_Str_432;
        Array_set(_va_Array_10, &_t_U32_431, _t_Str_432);
        ;
        Str *_t_Str_433 = Str_lit("./src/core/str.til:75:19", 24ULL);
        (void)_t_Str_433;
        panic(_t_Str_433, _va_Array_10);
        Str_delete(_t_Str_433, &(Bool){1});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    (void)new_len;
    Bool _t_Bool_441 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_441;
    if (_t_Bool_441) {
        Str *_t_Str_434 = Str_lit("Str", 3ULL);
        (void)_t_Str_434;
        U32 _t_U32_435 = 16;
        (void)_t_U32_435;
        U32 _t_U32_436 = 1;
        (void)_t_U32_436;
        Array *_va_Array_11 = Array_new(_t_Str_434, &_t_U32_435, &_t_U32_436);
        (void)_va_Array_11;
        Str_delete(_t_Str_434, &(Bool){1});
        ;
        ;
        U32 _t_U32_437 = 0;
        (void)_t_U32_437;
        Str *_t_Str_438 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t_Str_438;
        Array_set(_va_Array_11, &_t_U32_437, _t_Str_438);
        ;
        Str *_t_Str_439 = Str_lit("./src/core/str.til:79:19", 24ULL);
        (void)_t_Str_439;
        panic(_t_Str_439, _va_Array_11);
        Str_delete(_t_Str_439, &(Bool){1});
    }
    ;
    void *_t_v_442 = ptr_add(self->c_str, self->count);
    (void)_t_v_442;
    memcpy(_t_v_442, s->c_str, s->count);
    U32 _t_U32_443 = U32_clone(&new_len);
    (void)_t_U32_443;
    self->count = _t_U32_443;
    ;
    void *_t_v_444 = ptr_add(self->c_str, new_len);
    (void)_t_v_444;
    I32 _t_I32_445 = 0;
    (void)_t_I32_445;
    U64 _t_U64_446 = 1;
    (void)_t_U64_446;
    memset(_t_v_444, _t_I32_445, _t_U64_446);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_447 = 1;
    (void)_t_U32_447;
    U32 _t_U64_448 = U32_add(val->count, _t_U32_447);
    (void)_t_U64_448;
    ;
    void * new_data = malloc(_t_U64_448);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_449 = ptr_add(new_data, val->count);
    (void)_t_v_449;
    I32 _t_I32_450 = 0;
    (void)_t_I32_450;
    U64 _t_U64_451 = 1;
    (void)_t_U64_451;
    memset(_t_v_449, _t_I32_450, _t_U64_451);
    ;
    ;
    Str *_t_Str_452 = malloc(sizeof(Str));
    _t_Str_452->c_str = new_data;
    _t_Str_452->count = val->count;
    _t_Str_452->cap = val->count;
    (void)_t_Str_452;
    return _t_Str_452;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_453 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_453;
    if (_t_Bool_453) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t_Str_454 = Str_clone(val);
    (void)_t_Str_454;
    return _t_Str_454;
}

Str * Str_substr(Str * s, U32 * start, U32 * n) {
    (void)s;
    (void)start;
    (void)n;
    U32 st = U32_clone(start);
    (void)st;
    U32 ln = U32_clone(n);
    (void)ln;
    Bool _t_Bool_456 = U32_gt(&st, &s->count);
    (void)_t_Bool_456;
    if (_t_Bool_456) {
        st = s->count;
    }
    ;
    U32 _t_U32_457 = U32_add(st, ln);
    (void)_t_U32_457;
    Bool _t_Bool_458 = U32_gt(&_t_U32_457, &s->count);
    (void)_t_Bool_458;
    ;
    if (_t_Bool_458) {
        U32 _t_U32_455 = U32_sub(s->count, st);
        (void)_t_U32_455;
        ln = _t_U32_455;
        ;
    }
    ;
    void *_t_v_459 = ptr_add(s->c_str, st);
    (void)_t_v_459;
    Str *_t_Str_460 = malloc(sizeof(Str));
    _t_Str_460->c_str = _t_v_459;
    _t_Str_460->count = ln;
    _t_Str_460->cap = CAP_VIEW;
    (void)_t_Str_460;
    ;
    ;
    return _t_Str_460;
}

Bool Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_491 = 0;
    (void)_t_U32_491;
    Bool _t_Bool_492 = U32_eq(b->count, _t_U32_491);
    (void)_t_Bool_492;
    ;
    if (_t_Bool_492) {
        Bool _t_Bool_461 = 1;
        (void)_t_Bool_461;
        ;
        return _t_Bool_461;
    }
    ;
    Bool _t_Bool_493 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_493;
    if (_t_Bool_493) {
        Bool _t_Bool_462 = 0;
        (void)_t_Bool_462;
        ;
        return _t_Bool_462;
    }
    ;
    {
        U32 _t_U32_488 = U32_sub(a->count, b->count);
        (void)_t_U32_488;
        U32 _t_U32_489 = 1;
        (void)_t_U32_489;
        U32 _re_U32_463 = U32_add(_t_U32_488, _t_U32_489);
        (void)_re_U32_463;
        ;
        ;
        U32 _rc_U32_463 = 0;
        (void)_rc_U32_463;
        Bool _t_Bool_490 = U32_lte(&_rc_U32_463, &_re_U32_463);
        (void)_t_Bool_490;
        if (_t_Bool_490) {
            while (1) {
                Bool _wcond_Bool_464 = U32_lt(&_rc_U32_463, &_re_U32_463);
                (void)_wcond_Bool_464;
                if (_wcond_Bool_464) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_463);
                (void)i;
                U32_inc(&_rc_U32_463);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_465 = b->count;
                    (void)_re_U32_465;
                    U32 _rc_U32_465 = 0;
                    (void)_rc_U32_465;
                    Bool _t_Bool_474 = U32_lte(&_rc_U32_465, &_re_U32_465);
                    (void)_t_Bool_474;
                    if (_t_Bool_474) {
                        while (1) {
                            Bool _wcond_Bool_466 = U32_lt(&_rc_U32_465, &_re_U32_465);
                            (void)_wcond_Bool_466;
                            if (_wcond_Bool_466) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_465);
                            (void)j;
                            U32_inc(&_rc_U32_465);
                            U32 _t_U32_468 = U32_add(i, j);
                            (void)_t_U32_468;
                            U8 *ac = Str_get(a, &_t_U32_468);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_469 = U8_neq(ac, bc);
                            (void)_t_Bool_469;
                            ;
                            ;
                            if (_t_Bool_469) {
                                Bool _t_Bool_467 = 0;
                                (void)_t_Bool_467;
                                found = _t_Bool_467;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_470 = U32_gt(&_rc_U32_465, &_re_U32_465);
                            (void)_wcond_Bool_470;
                            if (_wcond_Bool_470) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_465);
                            (void)j;
                            U32_dec(&_rc_U32_465);
                            U32 _t_U32_472 = U32_add(i, j);
                            (void)_t_U32_472;
                            U8 *ac = Str_get(a, &_t_U32_472);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_473 = U8_neq(ac, bc);
                            (void)_t_Bool_473;
                            ;
                            ;
                            if (_t_Bool_473) {
                                Bool _t_Bool_471 = 0;
                                (void)_t_Bool_471;
                                found = _t_Bool_471;
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
                    Bool _t_Bool_475 = 1;
                    (void)_t_Bool_475;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_475;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_476 = U32_gt(&_rc_U32_463, &_re_U32_463);
                (void)_wcond_Bool_476;
                if (_wcond_Bool_476) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_463);
                (void)i;
                U32_dec(&_rc_U32_463);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_477 = b->count;
                    (void)_re_U32_477;
                    U32 _rc_U32_477 = 0;
                    (void)_rc_U32_477;
                    Bool _t_Bool_486 = U32_lte(&_rc_U32_477, &_re_U32_477);
                    (void)_t_Bool_486;
                    if (_t_Bool_486) {
                        while (1) {
                            Bool _wcond_Bool_478 = U32_lt(&_rc_U32_477, &_re_U32_477);
                            (void)_wcond_Bool_478;
                            if (_wcond_Bool_478) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_477);
                            (void)j;
                            U32_inc(&_rc_U32_477);
                            U32 _t_U32_480 = U32_add(i, j);
                            (void)_t_U32_480;
                            U8 *ac = Str_get(a, &_t_U32_480);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_481 = U8_neq(ac, bc);
                            (void)_t_Bool_481;
                            ;
                            ;
                            if (_t_Bool_481) {
                                Bool _t_Bool_479 = 0;
                                (void)_t_Bool_479;
                                found = _t_Bool_479;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_482 = U32_gt(&_rc_U32_477, &_re_U32_477);
                            (void)_wcond_Bool_482;
                            if (_wcond_Bool_482) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_477);
                            (void)j;
                            U32_dec(&_rc_U32_477);
                            U32 _t_U32_484 = U32_add(i, j);
                            (void)_t_U32_484;
                            U8 *ac = Str_get(a, &_t_U32_484);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_485 = U8_neq(ac, bc);
                            (void)_t_Bool_485;
                            ;
                            ;
                            if (_t_Bool_485) {
                                Bool _t_Bool_483 = 0;
                                (void)_t_Bool_483;
                                found = _t_Bool_483;
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
                    Bool _t_Bool_487 = 1;
                    (void)_t_Bool_487;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_487;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_494 = 0;
    (void)_t_Bool_494;
    return _t_Bool_494;
}

Bool Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_504 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_504;
    if (_t_Bool_504) {
        Bool _t_Bool_495 = 0;
        (void)_t_Bool_495;
        ;
        return _t_Bool_495;
    }
    ;
    {
        U32 _re_U32_496 = b->count;
        (void)_re_U32_496;
        U32 _rc_U32_496 = 0;
        (void)_rc_U32_496;
        Bool _t_Bool_503 = U32_lte(&_rc_U32_496, &_re_U32_496);
        (void)_t_Bool_503;
        if (_t_Bool_503) {
            while (1) {
                Bool _wcond_Bool_497 = U32_lt(&_rc_U32_496, &_re_U32_496);
                (void)_wcond_Bool_497;
                if (_wcond_Bool_497) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_496);
                (void)i;
                U32_inc(&_rc_U32_496);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_499 = U8_neq(ac, bc);
                (void)_t_Bool_499;
                ;
                if (_t_Bool_499) {
                    Bool _t_Bool_498 = 0;
                    (void)_t_Bool_498;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_498;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_500 = U32_gt(&_rc_U32_496, &_re_U32_496);
                (void)_wcond_Bool_500;
                if (_wcond_Bool_500) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_496);
                (void)i;
                U32_dec(&_rc_U32_496);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_502 = U8_neq(ac, bc);
                (void)_t_Bool_502;
                ;
                if (_t_Bool_502) {
                    Bool _t_Bool_501 = 0;
                    (void)_t_Bool_501;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_501;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_505 = 1;
    (void)_t_Bool_505;
    return _t_Bool_505;
}

Bool Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_517 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_517;
    if (_t_Bool_517) {
        Bool _t_Bool_506 = 0;
        (void)_t_Bool_506;
        ;
        return _t_Bool_506;
    }
    ;
    U32 offset = U32_sub(a->count, b->count);
    (void)offset;
    {
        U32 _re_U32_507 = b->count;
        (void)_re_U32_507;
        U32 _rc_U32_507 = 0;
        (void)_rc_U32_507;
        Bool _t_Bool_516 = U32_lte(&_rc_U32_507, &_re_U32_507);
        (void)_t_Bool_516;
        if (_t_Bool_516) {
            while (1) {
                Bool _wcond_Bool_508 = U32_lt(&_rc_U32_507, &_re_U32_507);
                (void)_wcond_Bool_508;
                if (_wcond_Bool_508) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_507);
                (void)i;
                U32_inc(&_rc_U32_507);
                U32 _t_U32_510 = U32_add(offset, i);
                (void)_t_U32_510;
                U8 *ac = Str_get(a, &_t_U32_510);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_511 = U8_neq(ac, bc);
                (void)_t_Bool_511;
                ;
                ;
                if (_t_Bool_511) {
                    Bool _t_Bool_509 = 0;
                    (void)_t_Bool_509;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_509;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_512 = U32_gt(&_rc_U32_507, &_re_U32_507);
                (void)_wcond_Bool_512;
                if (_wcond_Bool_512) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_507);
                (void)i;
                U32_dec(&_rc_U32_507);
                U32 _t_U32_514 = U32_add(offset, i);
                (void)_t_U32_514;
                U8 *ac = Str_get(a, &_t_U32_514);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_515 = U8_neq(ac, bc);
                (void)_t_Bool_515;
                ;
                ;
                if (_t_Bool_515) {
                    Bool _t_Bool_513 = 0;
                    (void)_t_Bool_513;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_513;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    Bool _t_Bool_518 = 1;
    (void)_t_Bool_518;
    return _t_Bool_518;
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_519 = 0;
    (void)_t_U32_519;
    Bool _t_Bool_520 = U32_eq(self->count, _t_U32_519);
    (void)_t_Bool_520;
    ;
    return _t_Bool_520;
}

I64 Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_555 = 0;
    (void)_t_U32_555;
    Bool _t_Bool_556 = U32_eq(needle->count, _t_U32_555);
    (void)_t_Bool_556;
    ;
    if (_t_Bool_556) {
        I64 _t_I64_521 = 0;
        (void)_t_I64_521;
        I64 _t_I64_522 = 1;
        (void)_t_I64_522;
        I64 _t_I64_523 = I64_sub(_t_I64_521, _t_I64_522);
        (void)_t_I64_523;
        ;
        ;
        ;
        return _t_I64_523;
    }
    ;
    Bool _t_Bool_557 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_557;
    if (_t_Bool_557) {
        I64 _t_I64_524 = 0;
        (void)_t_I64_524;
        I64 _t_I64_525 = 1;
        (void)_t_I64_525;
        I64 _t_I64_526 = I64_sub(_t_I64_524, _t_I64_525);
        (void)_t_I64_526;
        ;
        ;
        ;
        return _t_I64_526;
    }
    ;
    {
        U32 _t_U32_552 = U32_sub(self->count, needle->count);
        (void)_t_U32_552;
        U32 _t_U32_553 = 1;
        (void)_t_U32_553;
        U32 _re_U32_527 = U32_add(_t_U32_552, _t_U32_553);
        (void)_re_U32_527;
        ;
        ;
        U32 _rc_U32_527 = 0;
        (void)_rc_U32_527;
        Bool _t_Bool_554 = U32_lte(&_rc_U32_527, &_re_U32_527);
        (void)_t_Bool_554;
        if (_t_Bool_554) {
            while (1) {
                Bool _wcond_Bool_528 = U32_lt(&_rc_U32_527, &_re_U32_527);
                (void)_wcond_Bool_528;
                if (_wcond_Bool_528) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_527);
                (void)i;
                U32_inc(&_rc_U32_527);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_529 = needle->count;
                    (void)_re_U32_529;
                    U32 _rc_U32_529 = 0;
                    (void)_rc_U32_529;
                    Bool _t_Bool_538 = U32_lte(&_rc_U32_529, &_re_U32_529);
                    (void)_t_Bool_538;
                    if (_t_Bool_538) {
                        while (1) {
                            Bool _wcond_Bool_530 = U32_lt(&_rc_U32_529, &_re_U32_529);
                            (void)_wcond_Bool_530;
                            if (_wcond_Bool_530) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_529);
                            (void)j;
                            U32_inc(&_rc_U32_529);
                            U32 _t_U32_532 = U32_add(i, j);
                            (void)_t_U32_532;
                            U8 *ac = Str_get(self, &_t_U32_532);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_533 = U8_neq(ac, bc);
                            (void)_t_Bool_533;
                            ;
                            ;
                            if (_t_Bool_533) {
                                Bool _t_Bool_531 = 0;
                                (void)_t_Bool_531;
                                found = _t_Bool_531;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_534 = U32_gt(&_rc_U32_529, &_re_U32_529);
                            (void)_wcond_Bool_534;
                            if (_wcond_Bool_534) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_529);
                            (void)j;
                            U32_dec(&_rc_U32_529);
                            U32 _t_U32_536 = U32_add(i, j);
                            (void)_t_U32_536;
                            U8 *ac = Str_get(self, &_t_U32_536);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_537 = U8_neq(ac, bc);
                            (void)_t_Bool_537;
                            ;
                            ;
                            if (_t_Bool_537) {
                                Bool _t_Bool_535 = 0;
                                (void)_t_Bool_535;
                                found = _t_Bool_535;
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
                    I64 _t_I64_539 = U32_to_i64(i);
                    (void)_t_I64_539;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_539;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_540 = U32_gt(&_rc_U32_527, &_re_U32_527);
                (void)_wcond_Bool_540;
                if (_wcond_Bool_540) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_527);
                (void)i;
                U32_dec(&_rc_U32_527);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_541 = needle->count;
                    (void)_re_U32_541;
                    U32 _rc_U32_541 = 0;
                    (void)_rc_U32_541;
                    Bool _t_Bool_550 = U32_lte(&_rc_U32_541, &_re_U32_541);
                    (void)_t_Bool_550;
                    if (_t_Bool_550) {
                        while (1) {
                            Bool _wcond_Bool_542 = U32_lt(&_rc_U32_541, &_re_U32_541);
                            (void)_wcond_Bool_542;
                            if (_wcond_Bool_542) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_541);
                            (void)j;
                            U32_inc(&_rc_U32_541);
                            U32 _t_U32_544 = U32_add(i, j);
                            (void)_t_U32_544;
                            U8 *ac = Str_get(self, &_t_U32_544);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_545 = U8_neq(ac, bc);
                            (void)_t_Bool_545;
                            ;
                            ;
                            if (_t_Bool_545) {
                                Bool _t_Bool_543 = 0;
                                (void)_t_Bool_543;
                                found = _t_Bool_543;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_546 = U32_gt(&_rc_U32_541, &_re_U32_541);
                            (void)_wcond_Bool_546;
                            if (_wcond_Bool_546) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_541);
                            (void)j;
                            U32_dec(&_rc_U32_541);
                            U32 _t_U32_548 = U32_add(i, j);
                            (void)_t_U32_548;
                            U8 *ac = Str_get(self, &_t_U32_548);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_549 = U8_neq(ac, bc);
                            (void)_t_Bool_549;
                            ;
                            ;
                            if (_t_Bool_549) {
                                Bool _t_Bool_547 = 0;
                                (void)_t_Bool_547;
                                found = _t_Bool_547;
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
                    I64 _t_I64_551 = U32_to_i64(i);
                    (void)_t_I64_551;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_551;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    I64 _t_I64_558 = 0;
    (void)_t_I64_558;
    I64 _t_I64_559 = 1;
    (void)_t_I64_559;
    I64 _t_I64_560 = I64_sub(_t_I64_558, _t_I64_559);
    (void)_t_I64_560;
    ;
    ;
    return _t_I64_560;
}

I64 Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_595 = 0;
    (void)_t_U32_595;
    Bool _t_Bool_596 = U32_eq(needle->count, _t_U32_595);
    (void)_t_Bool_596;
    ;
    if (_t_Bool_596) {
        I64 _t_I64_561 = 0;
        (void)_t_I64_561;
        I64 _t_I64_562 = 1;
        (void)_t_I64_562;
        I64 _t_I64_563 = I64_sub(_t_I64_561, _t_I64_562);
        (void)_t_I64_563;
        ;
        ;
        ;
        return _t_I64_563;
    }
    ;
    Bool _t_Bool_597 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_597;
    if (_t_Bool_597) {
        I64 _t_I64_564 = 0;
        (void)_t_I64_564;
        I64 _t_I64_565 = 1;
        (void)_t_I64_565;
        I64 _t_I64_566 = I64_sub(_t_I64_564, _t_I64_565);
        (void)_t_I64_566;
        ;
        ;
        ;
        return _t_I64_566;
    }
    ;
    I64 _t_I64_598 = 0;
    (void)_t_I64_598;
    I64 _t_I64_599 = 1;
    (void)_t_I64_599;
    I64 last = I64_sub(_t_I64_598, _t_I64_599);
    (void)last;
    ;
    ;
    {
        U32 _t_U32_592 = U32_sub(self->count, needle->count);
        (void)_t_U32_592;
        U32 _t_U32_593 = 1;
        (void)_t_U32_593;
        U32 _re_U32_567 = U32_add(_t_U32_592, _t_U32_593);
        (void)_re_U32_567;
        ;
        ;
        U32 _rc_U32_567 = 0;
        (void)_rc_U32_567;
        Bool _t_Bool_594 = U32_lte(&_rc_U32_567, &_re_U32_567);
        (void)_t_Bool_594;
        if (_t_Bool_594) {
            while (1) {
                Bool _wcond_Bool_568 = U32_lt(&_rc_U32_567, &_re_U32_567);
                (void)_wcond_Bool_568;
                if (_wcond_Bool_568) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_567);
                (void)i;
                U32_inc(&_rc_U32_567);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_569 = needle->count;
                    (void)_re_U32_569;
                    U32 _rc_U32_569 = 0;
                    (void)_rc_U32_569;
                    Bool _t_Bool_578 = U32_lte(&_rc_U32_569, &_re_U32_569);
                    (void)_t_Bool_578;
                    if (_t_Bool_578) {
                        while (1) {
                            Bool _wcond_Bool_570 = U32_lt(&_rc_U32_569, &_re_U32_569);
                            (void)_wcond_Bool_570;
                            if (_wcond_Bool_570) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_569);
                            (void)j;
                            U32_inc(&_rc_U32_569);
                            U32 _t_U32_572 = U32_add(i, j);
                            (void)_t_U32_572;
                            U8 *ac = Str_get(self, &_t_U32_572);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_573 = U8_neq(ac, bc);
                            (void)_t_Bool_573;
                            ;
                            ;
                            if (_t_Bool_573) {
                                Bool _t_Bool_571 = 0;
                                (void)_t_Bool_571;
                                found = _t_Bool_571;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_574 = U32_gt(&_rc_U32_569, &_re_U32_569);
                            (void)_wcond_Bool_574;
                            if (_wcond_Bool_574) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_569);
                            (void)j;
                            U32_dec(&_rc_U32_569);
                            U32 _t_U32_576 = U32_add(i, j);
                            (void)_t_U32_576;
                            U8 *ac = Str_get(self, &_t_U32_576);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_577 = U8_neq(ac, bc);
                            (void)_t_Bool_577;
                            ;
                            ;
                            if (_t_Bool_577) {
                                Bool _t_Bool_575 = 0;
                                (void)_t_Bool_575;
                                found = _t_Bool_575;
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
                    I64 _t_I64_579 = U32_to_i64(i);
                    (void)_t_I64_579;
                    last = _t_I64_579;
                    ;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_580 = U32_gt(&_rc_U32_567, &_re_U32_567);
                (void)_wcond_Bool_580;
                if (_wcond_Bool_580) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_567);
                (void)i;
                U32_dec(&_rc_U32_567);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_581 = needle->count;
                    (void)_re_U32_581;
                    U32 _rc_U32_581 = 0;
                    (void)_rc_U32_581;
                    Bool _t_Bool_590 = U32_lte(&_rc_U32_581, &_re_U32_581);
                    (void)_t_Bool_590;
                    if (_t_Bool_590) {
                        while (1) {
                            Bool _wcond_Bool_582 = U32_lt(&_rc_U32_581, &_re_U32_581);
                            (void)_wcond_Bool_582;
                            if (_wcond_Bool_582) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_581);
                            (void)j;
                            U32_inc(&_rc_U32_581);
                            U32 _t_U32_584 = U32_add(i, j);
                            (void)_t_U32_584;
                            U8 *ac = Str_get(self, &_t_U32_584);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_585 = U8_neq(ac, bc);
                            (void)_t_Bool_585;
                            ;
                            ;
                            if (_t_Bool_585) {
                                Bool _t_Bool_583 = 0;
                                (void)_t_Bool_583;
                                found = _t_Bool_583;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_586 = U32_gt(&_rc_U32_581, &_re_U32_581);
                            (void)_wcond_Bool_586;
                            if (_wcond_Bool_586) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_581);
                            (void)j;
                            U32_dec(&_rc_U32_581);
                            U32 _t_U32_588 = U32_add(i, j);
                            (void)_t_U32_588;
                            U8 *ac = Str_get(self, &_t_U32_588);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_589 = U8_neq(ac, bc);
                            (void)_t_Bool_589;
                            ;
                            ;
                            if (_t_Bool_589) {
                                Bool _t_Bool_587 = 0;
                                (void)_t_Bool_587;
                                found = _t_Bool_587;
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
                    I64 _t_I64_591 = U32_to_i64(i);
                    (void)_t_I64_591;
                    last = _t_I64_591;
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
    U32 _t_U32_625 = 0;
    (void)_t_U32_625;
    Bool _t_Bool_626 = U32_eq(from->count, _t_U32_625);
    (void)_t_Bool_626;
    ;
    if (_t_Bool_626) {
        Str *_t_Str_600 = Str_clone(self);
        (void)_t_Str_600;
        ;
        return _t_Str_600;
    }
    ;
    U32 matches = 0;
    (void)matches;
    U32 start = 0;
    (void)start;
    while (1) {
        U32 _t_U32_602 = U32_sub(self->count, from->count);
        (void)_t_U32_602;
        Bool _wcond_Bool_601 = U32_lte(&start, &_t_U32_602);
        (void)_wcond_Bool_601;
        ;
        if (_wcond_Bool_601) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_603 = U32_sub(self->count, start);
        (void)_t_U32_603;
        Str *rest = Str_substr(self, &start, &_t_U32_603);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_604 = 0;
        (void)_t_I64_604;
        I64 _t_I64_605 = 1;
        (void)_t_I64_605;
        I64 _t_I64_606 = I64_sub(_t_I64_604, _t_I64_605);
        (void)_t_I64_606;
        ;
        ;
        Bool _t_Bool_607 = I64_eq(pos, _t_I64_606);
        (void)_t_Bool_607;
        ;
        if (_t_Bool_607) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        U32 _t_U32_608 = U32_add(start, pos_u);
        (void)_t_U32_608;
        ;
        U32 _t_U32_609 = U32_add(_t_U32_608, from->count);
        (void)_t_U32_609;
        ;
        start = _t_U32_609;
        ;
        U32 _t_U32_610 = 1;
        (void)_t_U32_610;
        U32 _t_U32_611 = U32_add(matches, _t_U32_610);
        (void)_t_U32_611;
        ;
        matches = _t_U32_611;
        ;
    }
    U32 _t_U32_627 = 0;
    (void)_t_U32_627;
    Bool _t_Bool_628 = U32_eq(matches, _t_U32_627);
    (void)_t_Bool_628;
    ;
    if (_t_Bool_628) {
        Str *_t_Str_612 = Str_clone(self);
        (void)_t_Str_612;
        ;
        ;
        ;
        return _t_Str_612;
    }
    ;
    U32 removed = U32_mul(matches, from->count);
    (void)removed;
    U32 added = U32_mul(matches, to->count);
    (void)added;
    ;
    U32 _t_U32_629 = U32_sub(self->count, removed);
    (void)_t_U32_629;
    ;
    U32 _t_U32_630 = U32_add(_t_U32_629, added);
    (void)_t_U32_630;
    ;
    ;
    Str *out = Str_with_capacity(&_t_U32_630);
    (void)out;
    ;
    U32 _t_U32_631 = 0;
    (void)_t_U32_631;
    start = _t_U32_631;
    ;
    while (1) {
        U32 _t_U32_614 = U32_sub(self->count, from->count);
        (void)_t_U32_614;
        Bool _wcond_Bool_613 = U32_lte(&start, &_t_U32_614);
        (void)_wcond_Bool_613;
        ;
        if (_wcond_Bool_613) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_615 = U32_sub(self->count, start);
        (void)_t_U32_615;
        Str *rest = Str_substr(self, &start, &_t_U32_615);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_616 = 0;
        (void)_t_I64_616;
        I64 _t_I64_617 = 1;
        (void)_t_I64_617;
        I64 _t_I64_618 = I64_sub(_t_I64_616, _t_I64_617);
        (void)_t_I64_618;
        ;
        ;
        Bool _t_Bool_619 = I64_eq(pos, _t_I64_618);
        (void)_t_Bool_619;
        ;
        if (_t_Bool_619) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        Str *_t_Str_620 = Str_substr(self, &start, &pos_u);
        (void)_t_Str_620;
        Str_push_str(out, _t_Str_620);
        Str_delete(_t_Str_620, &(Bool){1});
        Str_push_str(out, to);
        U32 _t_U32_621 = U32_add(start, pos_u);
        (void)_t_U32_621;
        ;
        U32 _t_U32_622 = U32_add(_t_U32_621, from->count);
        (void)_t_U32_622;
        ;
        start = _t_U32_622;
        ;
    }
    Bool _t_Bool_632 = U32_lt(&start, &self->count);
    (void)_t_Bool_632;
    if (_t_Bool_632) {
        U32 _t_U32_623 = U32_sub(self->count, start);
        (void)_t_U32_623;
        Str *_t_Str_624 = Str_substr(self, &start, &_t_U32_623);
        (void)_t_Str_624;
        ;
        Str_push_str(out, _t_Str_624);
        Str_delete(_t_Str_624, &(Bool){1});
    }
    ;
    ;
    return out;
}

Str * Str_get_char(Str * self, U32 * i) {
    (void)self;
    (void)i;
    U32 _t_U32_633 = 1;
    (void)_t_U32_633;
    Str *_t_Str_634 = Str_substr(self, i, &_t_U32_633);
    (void)_t_Str_634;
    ;
    return _t_Str_634;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t_Bool_637 = Str_starts_with(self, prefix);
    (void)_t_Bool_637;
    if (_t_Bool_637) {
        U32 _t_U32_635 = U32_sub(self->count, prefix->count);
        (void)_t_U32_635;
        Str *_t_Str_636 = Str_substr(self, &prefix->count, &_t_U32_635);
        (void)_t_Str_636;
        ;
        ;
        return _t_Str_636;
    }
    ;
    Str *_t_Str_638 = Str_clone(self);
    (void)_t_Str_638;
    return _t_Str_638;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t_Bool_642 = Str_ends_with(self, suffix);
    (void)_t_Bool_642;
    if (_t_Bool_642) {
        U32 _t_U32_639 = 0;
        (void)_t_U32_639;
        U32 _t_U32_640 = U32_sub(self->count, suffix->count);
        (void)_t_U32_640;
        Str *_t_Str_641 = Str_substr(self, &_t_U32_639, &_t_U32_640);
        (void)_t_Str_641;
        ;
        ;
        ;
        return _t_Str_641;
    }
    ;
    Str *_t_Str_643 = Str_clone(self);
    (void)_t_Str_643;
    return _t_Str_643;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t_U64_644 = 2;
    (void)_t_U64_644;
    void * buf = malloc(_t_U64_644);
    (void)buf;
    ;
    U64 _t_U64_645 = 1;
    (void)_t_U64_645;
    memcpy(buf, byte, _t_U64_645);
    ;
    U64 _t_U64_646 = 1;
    (void)_t_U64_646;
    void *_t_v_647 = ptr_add(buf, _t_U64_646);
    (void)_t_v_647;
    I32 _t_I32_648 = 0;
    (void)_t_I32_648;
    U64 _t_U64_649 = 1;
    (void)_t_U64_649;
    memset(_t_v_647, _t_I32_648, _t_U64_649);
    ;
    ;
    ;
    I64 _t_I64_650 = 1;
    (void)_t_I64_650;
    I64 _t_I64_651 = 1;
    (void)_t_I64_651;
    Str *_t_Str_652 = malloc(sizeof(Str));
    _t_Str_652->c_str = buf;
    _t_Str_652->count = _t_I64_650;
    _t_Str_652->cap = _t_I64_651;
    (void)_t_Str_652;
    ;
    ;
    return _t_Str_652;
}

I64 Str_to_i64(Str * self) {
    (void)self;
    U32 _t_U32_713 = 0;
    (void)_t_U32_713;
    Bool _t_Bool_714 = U32_eq(self->count, _t_U32_713);
    (void)_t_Bool_714;
    ;
    if (_t_Bool_714) {
        Str *_t_Str_653 = Str_lit("Str", 3ULL);
        (void)_t_Str_653;
        U32 _t_U32_654 = 16;
        (void)_t_U32_654;
        U32 _t_U32_655 = 1;
        (void)_t_U32_655;
        Array *_va_Array_12 = Array_new(_t_Str_653, &_t_U32_654, &_t_U32_655);
        (void)_va_Array_12;
        Str_delete(_t_Str_653, &(Bool){1});
        ;
        ;
        U32 _t_U32_656 = 0;
        (void)_t_U32_656;
        Str *_t_Str_657 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t_Str_657;
        Array_set(_va_Array_12, &_t_U32_656, _t_Str_657);
        ;
        Str *_t_Str_658 = Str_lit("./src/core/str.til:241:37", 25ULL);
        (void)_t_Str_658;
        panic(_t_Str_658, _va_Array_12);
        Str_delete(_t_Str_658, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_715 = 0;
    (void)_t_U32_715;
    U8 *first = Str_get(self, &_t_U32_715);
    (void)first;
    U8 _t_U8_716 = 45;
    (void)_t_U8_716;
    Bool _t_Bool_717 = U8_eq(DEREF(first), _t_U8_716);
    (void)_t_Bool_717;
    ;
    ;
    if (_t_Bool_717) {
        Bool _t_Bool_659 = 1;
        (void)_t_Bool_659;
        neg = _t_Bool_659;
        ;
        U32 _t_U32_660 = 1;
        (void)_t_U32_660;
        start = _t_U32_660;
        ;
    }
    ;
    Bool _t_Bool_718 = U32_eq(start, self->count);
    (void)_t_Bool_718;
    if (_t_Bool_718) {
        Str *_t_Str_661 = Str_lit("Str", 3ULL);
        (void)_t_Str_661;
        U32 _t_U32_662 = 16;
        (void)_t_U32_662;
        U32 _t_U32_663 = 1;
        (void)_t_U32_663;
        Array *_va_Array_13 = Array_new(_t_Str_661, &_t_U32_662, &_t_U32_663);
        (void)_va_Array_13;
        Str_delete(_t_Str_661, &(Bool){1});
        ;
        ;
        U32 _t_U32_664 = 0;
        (void)_t_U32_664;
        Str *_t_Str_665 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t_Str_665;
        Array_set(_va_Array_13, &_t_U32_664, _t_Str_665);
        ;
        Str *_t_Str_666 = Str_lit("./src/core/str.til:250:41", 25ULL);
        (void)_t_Str_666;
        panic(_t_Str_666, _va_Array_13);
        Str_delete(_t_Str_666, &(Bool){1});
    }
    ;
    {
        U32 _re_U32_667 = self->count;
        (void)_re_U32_667;
        U32 _rc_U32_667 = U32_clone(&start);
        (void)_rc_U32_667;
        Bool _t_Bool_710 = U32_lte(&_rc_U32_667, &_re_U32_667);
        (void)_t_Bool_710;
        if (_t_Bool_710) {
            while (1) {
                Bool _wcond_Bool_668 = U32_lt(&_rc_U32_667, &_re_U32_667);
                (void)_wcond_Bool_668;
                if (_wcond_Bool_668) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_667);
                (void)i;
                U32_inc(&_rc_U32_667);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_679 = U8_to_i64(DEREF(ch));
                (void)_t_I64_679;
                ;
                I64 _t_I64_680 = 48;
                (void)_t_I64_680;
                I64 d = I64_sub(_t_I64_679, _t_I64_680);
                (void)d;
                ;
                ;
                I64 _t_I64_681 = 0;
                (void)_t_I64_681;
                I64 _t_I64_682 = 9;
                (void)_t_I64_682;
                Bool _t_Bool_683 = I64_lt(&d, &_t_I64_681);
                (void)_t_Bool_683;
                ;
                Bool _t_Bool_684 = I64_gt(&d, &_t_I64_682);
                (void)_t_Bool_684;
                ;
                Bool _t_Bool_685 = or(_t_Bool_683, _t_Bool_684);
                (void)_t_Bool_685;
                ;
                ;
                if (_t_Bool_685) {
                    Str *_t_Str_669 = Str_lit("Str", 3ULL);
                    (void)_t_Str_669;
                    U32 _t_U32_670 = 16;
                    (void)_t_U32_670;
                    U32 _t_U32_671 = 3;
                    (void)_t_U32_671;
                    Array *_va_Array_14 = Array_new(_t_Str_669, &_t_U32_670, &_t_U32_671);
                    (void)_va_Array_14;
                    Str_delete(_t_Str_669, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_672 = 0;
                    (void)_t_U32_672;
                    Str *_t_Str_673 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_673;
                    Array_set(_va_Array_14, &_t_U32_672, _t_Str_673);
                    ;
                    U32 _t_U32_674 = 1;
                    (void)_t_U32_674;
                    Str *_t_Str_675 = Str_clone(self);
                    (void)_t_Str_675;
                    Array_set(_va_Array_14, &_t_U32_674, _t_Str_675);
                    ;
                    U32 _t_U32_676 = 2;
                    (void)_t_U32_676;
                    Str *_t_Str_677 = Str_lit("'", 1ULL);
                    (void)_t_Str_677;
                    Array_set(_va_Array_14, &_t_U32_676, _t_Str_677);
                    ;
                    Str *_t_Str_678 = Str_lit("./src/core/str.til:255:23", 25ULL);
                    (void)_t_Str_678;
                    panic(_t_Str_678, _va_Array_14);
                    Str_delete(_t_Str_678, &(Bool){1});
                }
                ;
                I64 _t_I64_686 = 10;
                (void)_t_I64_686;
                I64 _t_I64_687 = I64_mul(result, _t_I64_686);
                (void)_t_I64_687;
                ;
                I64 _t_I64_688 = I64_add(_t_I64_687, d);
                (void)_t_I64_688;
                ;
                ;
                result = _t_I64_688;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_689 = U32_gt(&_rc_U32_667, &_re_U32_667);
                (void)_wcond_Bool_689;
                if (_wcond_Bool_689) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_667);
                (void)i;
                U32_dec(&_rc_U32_667);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_700 = U8_to_i64(DEREF(ch));
                (void)_t_I64_700;
                ;
                I64 _t_I64_701 = 48;
                (void)_t_I64_701;
                I64 d = I64_sub(_t_I64_700, _t_I64_701);
                (void)d;
                ;
                ;
                I64 _t_I64_702 = 0;
                (void)_t_I64_702;
                I64 _t_I64_703 = 9;
                (void)_t_I64_703;
                Bool _t_Bool_704 = I64_lt(&d, &_t_I64_702);
                (void)_t_Bool_704;
                ;
                Bool _t_Bool_705 = I64_gt(&d, &_t_I64_703);
                (void)_t_Bool_705;
                ;
                Bool _t_Bool_706 = or(_t_Bool_704, _t_Bool_705);
                (void)_t_Bool_706;
                ;
                ;
                if (_t_Bool_706) {
                    Str *_t_Str_690 = Str_lit("Str", 3ULL);
                    (void)_t_Str_690;
                    U32 _t_U32_691 = 16;
                    (void)_t_U32_691;
                    U32 _t_U32_692 = 3;
                    (void)_t_U32_692;
                    Array *_va_Array_15 = Array_new(_t_Str_690, &_t_U32_691, &_t_U32_692);
                    (void)_va_Array_15;
                    Str_delete(_t_Str_690, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_693 = 0;
                    (void)_t_U32_693;
                    Str *_t_Str_694 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_694;
                    Array_set(_va_Array_15, &_t_U32_693, _t_Str_694);
                    ;
                    U32 _t_U32_695 = 1;
                    (void)_t_U32_695;
                    Str *_t_Str_696 = Str_clone(self);
                    (void)_t_Str_696;
                    Array_set(_va_Array_15, &_t_U32_695, _t_Str_696);
                    ;
                    U32 _t_U32_697 = 2;
                    (void)_t_U32_697;
                    Str *_t_Str_698 = Str_lit("'", 1ULL);
                    (void)_t_Str_698;
                    Array_set(_va_Array_15, &_t_U32_697, _t_Str_698);
                    ;
                    Str *_t_Str_699 = Str_lit("./src/core/str.til:255:23", 25ULL);
                    (void)_t_Str_699;
                    panic(_t_Str_699, _va_Array_15);
                    Str_delete(_t_Str_699, &(Bool){1});
                }
                ;
                I64 _t_I64_707 = 10;
                (void)_t_I64_707;
                I64 _t_I64_708 = I64_mul(result, _t_I64_707);
                (void)_t_I64_708;
                ;
                I64 _t_I64_709 = I64_add(_t_I64_708, d);
                (void)_t_I64_709;
                ;
                ;
                result = _t_I64_709;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    if (neg) {
        I64 _t_I64_711 = 0;
        (void)_t_I64_711;
        I64 _t_I64_712 = I64_sub(_t_I64_711, result);
        (void)_t_I64_712;
        ;
        ;
        ;
        return _t_I64_712;
    }
    ;
    return result;
}

U8 Str_to_u8(Str * self) {
    (void)self;
    I64 _t_I64_719 = Str_to_i64(self);
    (void)_t_I64_719;
    U8 _t_U8_720 = I64_to_u8(_t_I64_719);
    (void)_t_U8_720;
    ;
    return _t_U8_720;
}

I32 Str_to_i32(Str * self) {
    (void)self;
    I64 _t_I64_721 = Str_to_i64(self);
    (void)_t_I64_721;
    I32 _t_I32_722 = I64_to_i32(_t_I64_721);
    (void)_t_I32_722;
    ;
    return _t_I32_722;
}

F32 Str_to_f32(Str * self) {
    (void)self;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_748 = Str_len(self);
    (void)_t_U32_748;
    U32 _t_U32_749 = 0;
    (void)_t_U32_749;
    U32 _t_U32_750 = 0;
    (void)_t_U32_750;
    U8 *_t_U8_751 = Str_get(self, &_t_U32_750);
    (void)_t_U8_751;
    U8 _t_U8_752 = 45;
    (void)_t_U8_752;
    Bool _t_Bool_753 = U32_gt(&_t_U32_748, &_t_U32_749);
    (void)_t_Bool_753;
    ;
    ;
    Bool _t_Bool_754 = U8_eq(DEREF(_t_U8_751), _t_U8_752);
    (void)_t_Bool_754;
    ;
    ;
    Bool _t_Bool_755 = and(_t_Bool_753, _t_Bool_754);
    (void)_t_Bool_755;
    ;
    ;
    if (_t_Bool_755) {
        Bool _t_Bool_723 = 1;
        (void)_t_Bool_723;
        neg = _t_Bool_723;
        ;
        U32 _t_U32_724 = 1;
        (void)_t_U32_724;
        start = _t_U32_724;
        ;
    }
    ;
    U32 _t_U32_756 = Str_len(self);
    (void)_t_U32_756;
    U32 _t_U32_757 = U32_sub(_t_U32_756, start);
    (void)_t_U32_757;
    ;
    Str *rest = Str_substr(self, &start, &_t_U32_757);
    (void)rest;
    ;
    ;
    Str *_t_Str_758 = Str_lit(".", 1ULL);
    (void)_t_Str_758;
    I64 dot = Str_find(rest, _t_Str_758);
    (void)dot;
    Str_delete(_t_Str_758, &(Bool){1});
    I64 _t_I64_759 = 0;
    (void)_t_I64_759;
    I64 _t_I64_760 = 1;
    (void)_t_I64_760;
    I64 _t_I64_761 = I64_sub(_t_I64_759, _t_I64_760);
    (void)_t_I64_761;
    ;
    ;
    Bool _t_Bool_762 = I64_eq(dot, _t_I64_761);
    (void)_t_Bool_762;
    ;
    if (_t_Bool_762) {
        I64 _t_I64_728 = Str_to_i64(rest);
        (void)_t_I64_728;
        F32 out = I64_to_f32(_t_I64_728);
        (void)out;
        ;
        if (neg) {
            I64 _t_I64_725 = 0;
            (void)_t_I64_725;
            F32 _t_F32_726 = I64_to_f32(_t_I64_725);
            (void)_t_F32_726;
            ;
            F32 _t_F32_727 = F32_sub(_t_F32_726, out);
            (void)_t_F32_727;
            ;
            ;
            ;
            ;
            ;
            Str_delete(rest, &(Bool){1});
            return _t_F32_727;
        }
        ;
        ;
        ;
        Str_delete(rest, &(Bool){1});
        return out;
    }
    ;
    U32 _t_U32_763 = 0;
    (void)_t_U32_763;
    U32 _t_U32_764 = I64_to_usize(dot);
    (void)_t_U32_764;
    Str *int_part = Str_substr(rest, &_t_U32_763, &_t_U32_764);
    (void)int_part;
    ;
    ;
    U32 _t_U32_765 = I64_to_usize(dot);
    (void)_t_U32_765;
    U32 _t_U32_766 = 1;
    (void)_t_U32_766;
    U32 _t_U32_767 = I64_to_usize(dot);
    (void)_t_U32_767;
    ;
    U32 _t_U32_768 = 1;
    (void)_t_U32_768;
    U32 _t_U32_769 = Str_len(rest);
    (void)_t_U32_769;
    U32 _t_U32_770 = U32_add(_t_U32_767, _t_U32_768);
    (void)_t_U32_770;
    ;
    ;
    U32 _t_U32_771 = U32_add(_t_U32_765, _t_U32_766);
    (void)_t_U32_771;
    ;
    ;
    U32 _t_U32_772 = U32_sub(_t_U32_769, _t_U32_770);
    (void)_t_U32_772;
    ;
    ;
    Str *frac_part = Str_substr(rest, &_t_U32_771, &_t_U32_772);
    (void)frac_part;
    ;
    ;
    Str_delete(rest, &(Bool){1});
    I64 _t_I64_773 = 0;
    (void)_t_I64_773;
    F32 out = I64_to_f32(_t_I64_773);
    (void)out;
    ;
    U32 _t_U32_774 = Str_len(int_part);
    (void)_t_U32_774;
    U32 _t_U32_775 = 0;
    (void)_t_U32_775;
    Bool _t_Bool_776 = U32_gt(&_t_U32_774, &_t_U32_775);
    (void)_t_Bool_776;
    ;
    ;
    if (_t_Bool_776) {
        I64 _t_I64_729 = Str_to_i64(int_part);
        (void)_t_I64_729;
        F32 _t_F32_730 = I64_to_f32(_t_I64_729);
        (void)_t_F32_730;
        ;
        out = _t_F32_730;
        ;
    }
    ;
    Str_delete(int_part, &(Bool){1});
    U32 _t_U32_777 = Str_len(frac_part);
    (void)_t_U32_777;
    U32 _t_U32_778 = 0;
    (void)_t_U32_778;
    Bool _t_Bool_779 = U32_gt(&_t_U32_777, &_t_U32_778);
    (void)_t_Bool_779;
    ;
    ;
    if (_t_Bool_779) {
        I64 _t_I64_741 = Str_to_i64(frac_part);
        (void)_t_I64_741;
        F32 frac = I64_to_f32(_t_I64_741);
        (void)frac;
        ;
        I64 _t_I64_742 = 1;
        (void)_t_I64_742;
        F32 scale = I64_to_f32(_t_I64_742);
        (void)scale;
        ;
        {
            U32 _re_U32_731 = Str_len(frac_part);
            (void)_re_U32_731;
            U32 _rc_U32_731 = 0;
            (void)_rc_U32_731;
            Bool _t_Bool_740 = U32_lte(&_rc_U32_731, &_re_U32_731);
            (void)_t_Bool_740;
            if (_t_Bool_740) {
                while (1) {
                    Bool _wcond_Bool_732 = U32_lt(&_rc_U32_731, &_re_U32_731);
                    (void)_wcond_Bool_732;
                    if (_wcond_Bool_732) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_731);
                    (void)_;
                    ;
                    U32_inc(&_rc_U32_731);
                    I64 _t_I64_733 = 10;
                    (void)_t_I64_733;
                    F32 _t_F32_734 = I64_to_f32(_t_I64_733);
                    (void)_t_F32_734;
                    ;
                    F32 _t_F32_735 = F32_mul(scale, _t_F32_734);
                    (void)_t_F32_735;
                    ;
                    scale = _t_F32_735;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_736 = U32_gt(&_rc_U32_731, &_re_U32_731);
                    (void)_wcond_Bool_736;
                    if (_wcond_Bool_736) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_731);
                    (void)_;
                    ;
                    U32_dec(&_rc_U32_731);
                    I64 _t_I64_737 = 10;
                    (void)_t_I64_737;
                    F32 _t_F32_738 = I64_to_f32(_t_I64_737);
                    (void)_t_F32_738;
                    ;
                    F32 _t_F32_739 = F32_mul(scale, _t_F32_738);
                    (void)_t_F32_739;
                    ;
                    scale = _t_F32_739;
                    ;
                }
            }
            ;
            ;
            ;
        }
        F32 _t_F32_743 = F32_div(frac, scale);
        (void)_t_F32_743;
        ;
        ;
        F32 _t_F32_744 = F32_add(out, _t_F32_743);
        (void)_t_F32_744;
        ;
        out = _t_F32_744;
        ;
    }
    ;
    Str_delete(frac_part, &(Bool){1});
    if (neg) {
        I64 _t_I64_745 = 0;
        (void)_t_I64_745;
        F32 _t_F32_746 = I64_to_f32(_t_I64_745);
        (void)_t_F32_746;
        ;
        F32 _t_F32_747 = F32_sub(_t_F32_746, out);
        (void)_t_F32_747;
        ;
        ;
        ;
        return _t_F32_747;
    }
    ;
    return out;
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t_Str_796 = Str_lit("Str", 3ULL);
    (void)_t_Str_796;
    U32 _t_U32_797 = 16;
    (void)_t_U32_797;
    Vec *parts = Vec_new(_t_Str_796, &_t_U32_797);
    (void)parts;
    Str_delete(_t_Str_796, &(Bool){1});
    ;
    U32 _t_U32_798 = Str_len(delim);
    (void)_t_U32_798;
    U32 _t_U32_799 = 0;
    (void)_t_U32_799;
    Bool _t_Bool_800 = U32_eq(_t_U32_798, _t_U32_799);
    (void)_t_Bool_800;
    ;
    ;
    if (_t_Bool_800) {
        Str *_t_Str_780 = Str_clone(self);
        (void)_t_Str_780;
        Vec_push(parts, _t_Str_780);
        ;
        return parts;
    }
    ;
    U32 start = 0;
    (void)start;
    U32 pos = 0;
    (void)pos;
    while (1) {
        U32 _t_U32_790 = Str_len(self);
        (void)_t_U32_790;
        U32 _t_U32_791 = Str_len(delim);
        (void)_t_U32_791;
        U32 _t_U32_792 = U32_sub(_t_U32_790, _t_U32_791);
        (void)_t_U32_792;
        ;
        ;
        Bool _wcond_Bool_781 = U32_lte(&pos, &_t_U32_792);
        (void)_wcond_Bool_781;
        ;
        if (_wcond_Bool_781) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_793 = Str_len(delim);
        (void)_t_U32_793;
        Str *_t_Str_794 = Str_substr(self, &pos, &_t_U32_793);
        (void)_t_Str_794;
        ;
        Bool _t_Bool_795 = Str_eq(_t_Str_794, delim);
        (void)_t_Bool_795;
        Str_delete(_t_Str_794, &(Bool){1});
        if (_t_Bool_795) {
            U32 _t_U32_782 = U32_sub(pos, start);
            (void)_t_U32_782;
            Str *_t_Str_783 = Str_substr(self, &start, &_t_U32_782);
            (void)_t_Str_783;
            ;
            Str *_t_Str_784 = Str_clone(_t_Str_783);
            (void)_t_Str_784;
            Str_delete(_t_Str_783, &(Bool){1});
            Vec_push(parts, _t_Str_784);
            U32 _t_U32_785 = Str_len(delim);
            (void)_t_U32_785;
            U32 _t_U32_786 = U32_add(pos, _t_U32_785);
            (void)_t_U32_786;
            ;
            start = _t_U32_786;
            ;
            U32 _t_U32_787 = U32_clone(&start);
            (void)_t_U32_787;
            pos = _t_U32_787;
            ;
        } else {
            U32 _t_U32_788 = 1;
            (void)_t_U32_788;
            U32 _t_U32_789 = U32_add(pos, _t_U32_788);
            (void)_t_U32_789;
            ;
            pos = _t_U32_789;
            ;
        }
        ;
    }
    ;
    U32 _t_U32_801 = Str_len(self);
    (void)_t_U32_801;
    U32 _t_U32_802 = U32_sub(_t_U32_801, start);
    (void)_t_U32_802;
    ;
    Str *_t_Str_803 = Str_substr(self, &start, &_t_U32_802);
    (void)_t_Str_803;
    ;
    ;
    Str *_t_Str_804 = Str_clone(_t_Str_803);
    (void)_t_Str_804;
    Str_delete(_t_Str_803, &(Bool){1});
    Vec_push(parts, _t_Str_804);
    return parts;
}

U32 Str_size(void) {
    I64 _t_I64_805 = 16;
    (void)_t_I64_805;
    return _t_I64_805;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_806 = Str_cmp(a, b);
    (void)_t_I64_806;
    I64 _t_I64_807 = 0;
    (void)_t_I64_807;
    Bool _t_Bool_808 = I64_eq(_t_I64_806, _t_I64_807);
    (void)_t_Bool_808;
    ;
    ;
    return _t_Bool_808;
}

Bool Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_809 = 0;
    (void)_t_I64_809;
    I64 _t_I64_810 = 1;
    (void)_t_I64_810;
    I64 _t_I64_811 = Str_cmp(a, b);
    (void)_t_I64_811;
    I64 _t_I64_812 = I64_sub(_t_I64_809, _t_I64_810);
    (void)_t_I64_812;
    ;
    ;
    Bool _t_Bool_813 = I64_eq(_t_I64_811, _t_I64_812);
    (void)_t_Bool_813;
    ;
    ;
    return _t_Bool_813;
}

Bool Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_814 = Str_cmp(a, b);
    (void)_t_I64_814;
    I64 _t_I64_815 = 1;
    (void)_t_I64_815;
    Bool _t_Bool_816 = I64_eq(_t_I64_814, _t_I64_815);
    (void)_t_Bool_816;
    ;
    ;
    return _t_Bool_816;
}

Bool Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_817 = Str_eq(a, b);
    (void)_t_Bool_817;
    Bool _t_Bool_818 = not(_t_Bool_817);
    (void)_t_Bool_818;
    ;
    return _t_Bool_818;
}

Bool Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_819 = Str_gt(a, b);
    (void)_t_Bool_819;
    Bool _t_Bool_820 = not(_t_Bool_819);
    (void)_t_Bool_820;
    ;
    return _t_Bool_820;
}

Bool Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_821 = Str_lt(a, b);
    (void)_t_Bool_821;
    Bool _t_Bool_822 = not(_t_Bool_821);
    (void)_t_Bool_822;
    ;
    return _t_Bool_822;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_854 = 8;
    (void)_t_I64_854;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_854; return _r; }
}

void * default_clone(void * v) {
    (void)v;
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

Str * I16_to_str(I16 * val) {
    (void)val;
    I64 _t_I64_857 = I16_to_i64(DEREF(val));
    (void)_t_I64_857;
    Str *_t_Str_858 = I64_to_str(&_t_I64_857);
    (void)_t_Str_858;
    ;
    return _t_Str_858;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t_I16_859 = 1;
    (void)_t_I16_859;
    I16 _t_I16_860 = I16_add(DEREF(self), _t_I16_859);
    (void)_t_I16_860;
    ;
    *self = _t_I16_860;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t_I16_861 = 1;
    (void)_t_I16_861;
    I16 _t_I16_862 = I16_sub(DEREF(self), _t_I16_861);
    (void)_t_I16_862;
    ;
    *self = _t_I16_862;
    ;
}

I16 * I16_unity(I16 * _self) {
    (void)_self;
    I64 _t_I64_863 = 1;
    (void)_t_I64_863;
    I16 _t_I16_864 = I64_to_i16(_t_I64_863);
    (void)_t_I16_864;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_864; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t_I64_865 = 0;
    (void)_t_I64_865;
    I64 _t_I64_866 = I16_to_i64(DEREF(a));
    (void)_t_I64_866;
    I64 _t_I64_867 = I64_sub(_t_I64_865, _t_I64_866);
    (void)_t_I64_867;
    ;
    ;
    I16 _t_I16_868 = I64_to_i16(_t_I64_867);
    (void)_t_I16_868;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_868; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t_I64_873 = I16_to_i64(DEREF(a));
    (void)_t_I64_873;
    I64 _t_I64_874 = 0;
    (void)_t_I64_874;
    Bool _t_Bool_875 = I64_lt(&_t_I64_873, &_t_I64_874);
    (void)_t_Bool_875;
    ;
    ;
    if (_t_Bool_875) {
        I64 _t_I64_869 = 0;
        (void)_t_I64_869;
        I64 _t_I64_870 = I16_to_i64(DEREF(a));
        (void)_t_I64_870;
        I64 _t_I64_871 = I64_sub(_t_I64_869, _t_I64_870);
        (void)_t_I64_871;
        ;
        ;
        I16 _t_I16_872 = I64_to_i16(_t_I64_871);
        (void)_t_I16_872;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_872; return _r; }
    }
    ;
    I16 _t_I16_876 = I16_clone(a);
    (void)_t_I16_876;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_876; return _r; }
}

U64 I16_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I16 *au = a;
    (void)au;
    I16 *bu = b;
    (void)bu;
    Bool _t_Bool_880 = I16_lte(au, bu);
    (void)_t_Bool_880;
    if (_t_Bool_880) {
        I16 _t_I16_877 = I16_sub(DEREF(bu), DEREF(au));
        (void)_t_I16_877;
        I64 _t_I64_878 = I16_to_i64(_t_I16_877);
        (void)_t_I64_878;
        ;
        U64 _t_U64_879 = I64_to_u64(_t_I64_878);
        (void)_t_U64_879;
        ;
        ;
        return _t_U64_879;
    }
    ;
    I16 _t_I16_881 = I16_sub(DEREF(au), DEREF(bu));
    (void)_t_I16_881;
    I64 _t_I64_882 = I16_to_i64(_t_I16_881);
    (void)_t_I64_882;
    ;
    U64 _t_U64_883 = I64_to_u64(_t_I64_882);
    (void)_t_U64_883;
    ;
    return _t_U64_883;
}

void I16_delete(I16 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I16_size(void) {
    I64 _t_I64_884 = 2;
    (void)_t_I64_884;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_884; return _r; }
}

Bool I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_885 = 0;
    (void)_t_I64_885;
    I64 _t_I64_886 = 1;
    (void)_t_I64_886;
    I64 _t_I64_887 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_887;
    I64 _t_I64_888 = I64_sub(_t_I64_885, _t_I64_886);
    (void)_t_I64_888;
    ;
    ;
    Bool _t_Bool_889 = I64_eq(_t_I64_887, _t_I64_888);
    (void)_t_Bool_889;
    ;
    ;
    return _t_Bool_889;
}

Bool I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_890 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_890;
    I64 _t_I64_891 = 1;
    (void)_t_I64_891;
    Bool _t_Bool_892 = I64_eq(_t_I64_890, _t_I64_891);
    (void)_t_Bool_892;
    ;
    ;
    return _t_Bool_892;
}

Bool I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_893 = I16_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_893;
    Bool _t_Bool_894 = not(_t_Bool_893);
    (void)_t_Bool_894;
    ;
    return _t_Bool_894;
}

Bool I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_895 = I16_gt(a, b);
    (void)_t_Bool_895;
    Bool _t_Bool_896 = not(_t_Bool_895);
    (void)_t_Bool_896;
    ;
    return _t_Bool_896;
}

Bool I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_897 = I16_lt(a, b);
    (void)_t_Bool_897;
    Bool _t_Bool_898 = not(_t_Bool_897);
    (void)_t_Bool_898;
    ;
    return _t_Bool_898;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_935 = 0;
    (void)_t_I64_935;
    Bool _t_Bool_936 = I64_eq(DEREF(val), _t_I64_935);
    (void)_t_Bool_936;
    ;
    if (_t_Bool_936) {
        U64 _t_U64_899 = 2;
        (void)_t_U64_899;
        void * buf = malloc(_t_U64_899);
        (void)buf;
        ;
        I64 _t_I64_900 = 48;
        (void)_t_I64_900;
        U64 _t_U64_901 = 1;
        (void)_t_U64_901;
        memcpy(buf, &_t_I64_900, _t_U64_901);
        ;
        ;
        U64 _t_U64_902 = 1;
        (void)_t_U64_902;
        void *_t_v_903 = ptr_add(buf, _t_U64_902);
        (void)_t_v_903;
        I32 _t_I32_904 = 0;
        (void)_t_I32_904;
        U64 _t_U64_905 = 1;
        (void)_t_U64_905;
        memset(_t_v_903, _t_I32_904, _t_U64_905);
        ;
        ;
        ;
        I64 _t_I64_906 = 1;
        (void)_t_I64_906;
        I64 _t_I64_907 = 1;
        (void)_t_I64_907;
        Str *_t_Str_908 = malloc(sizeof(Str));
        _t_Str_908->c_str = buf;
        _t_Str_908->count = _t_I64_906;
        _t_Str_908->cap = _t_I64_907;
        (void)_t_Str_908;
        ;
        ;
        ;
        return _t_Str_908;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t_I64_937 = 0;
    (void)_t_I64_937;
    Bool _t_Bool_938 = I64_lt(val, &_t_I64_937);
    (void)_t_Bool_938;
    ;
    if (_t_Bool_938) {
        Bool _t_Bool_909 = 1;
        (void)_t_Bool_909;
        is_neg = _t_Bool_909;
        ;
        I64 _t_I64_910 = 0;
        (void)_t_I64_910;
        I64 _t_I64_911 = I64_sub(_t_I64_910, DEREF(val));
        (void)_t_I64_911;
        ;
        v = _t_I64_911;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&v);
    (void)tmp;
    while (1) {
        I64 _t_I64_913 = 0;
        (void)_t_I64_913;
        Bool _wcond_Bool_912 = I64_gt(&tmp, &_t_I64_913);
        (void)_wcond_Bool_912;
        ;
        if (_wcond_Bool_912) {
        } else {
            ;
            break;
        }
        ;
        U64 _t_U64_914 = 1;
        (void)_t_U64_914;
        U64 _t_U64_915 = U64_add(ndigits, _t_U64_914);
        (void)_t_U64_915;
        ;
        ndigits = _t_U64_915;
        ;
        I64 _t_I64_916 = 10;
        (void)_t_I64_916;
        I64 _t_I64_917 = I64_div(tmp, _t_I64_916);
        (void)_t_I64_917;
        ;
        tmp = _t_I64_917;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    (void)total;
    ;
    if (is_neg) {
        U64 _t_U64_918 = 1;
        (void)_t_U64_918;
        U64 _t_U64_919 = U64_add(total, _t_U64_918);
        (void)_t_U64_919;
        ;
        total = _t_U64_919;
        ;
    }
    U64 _t_U64_939 = 1;
    (void)_t_U64_939;
    U64 _t_U64_940 = U64_add(total, _t_U64_939);
    (void)_t_U64_940;
    ;
    void * buf = malloc(_t_U64_940);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t_I64_920 = 45;
        (void)_t_I64_920;
        U64 _t_U64_921 = 1;
        (void)_t_U64_921;
        memcpy(buf, &_t_I64_920, _t_U64_921);
        ;
        ;
    }
    ;
    U64 _t_U64_941 = 1;
    (void)_t_U64_941;
    U64 i = U64_sub(total, _t_U64_941);
    (void)i;
    ;
    while (1) {
        I64 _t_I64_923 = 0;
        (void)_t_I64_923;
        Bool _wcond_Bool_922 = I64_gt(&v, &_t_I64_923);
        (void)_wcond_Bool_922;
        ;
        if (_wcond_Bool_922) {
        } else {
            ;
            break;
        }
        ;
        I64 _t_I64_924 = 10;
        (void)_t_I64_924;
        I64 _t_I64_925 = I64_mod(v, _t_I64_924);
        (void)_t_I64_925;
        ;
        I64 _t_I64_926 = 48;
        (void)_t_I64_926;
        I64 _t_I64_927 = I64_add(_t_I64_925, _t_I64_926);
        (void)_t_I64_927;
        ;
        ;
        void *_t_v_928 = ptr_add(buf, i);
        (void)_t_v_928;
        U8 _t_U8_929 = I64_to_u8(_t_I64_927);
        (void)_t_U8_929;
        ;
        U64 _t_U64_930 = 1;
        (void)_t_U64_930;
        memcpy(_t_v_928, &_t_U8_929, _t_U64_930);
        ;
        ;
        I64 _t_I64_931 = 10;
        (void)_t_I64_931;
        I64 _t_I64_932 = I64_div(v, _t_I64_931);
        (void)_t_I64_932;
        ;
        v = _t_I64_932;
        ;
        U64 _t_U64_933 = 1;
        (void)_t_U64_933;
        U64 _t_U64_934 = U64_sub(i, _t_U64_933);
        (void)_t_U64_934;
        ;
        i = _t_U64_934;
        ;
    }
    ;
    ;
    void *_t_v_942 = ptr_add(buf, total);
    (void)_t_v_942;
    I32 _t_I32_943 = 0;
    (void)_t_I32_943;
    U64 _t_U64_944 = 1;
    (void)_t_U64_944;
    memset(_t_v_942, _t_I32_943, _t_U64_944);
    ;
    ;
    Str *_t_Str_945 = malloc(sizeof(Str));
    _t_Str_945->c_str = buf;
    _t_Str_945->count = total;
    _t_Str_945->cap = total;
    (void)_t_Str_945;
    ;
    return _t_Str_945;
}

U32 I64_to_usize(I64 val) {
    (void)val;
    U32 _t_U32_946 = I64_to_u32(val);
    (void)_t_U32_946;
    return _t_U32_946;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t_I64_947 = 1;
    (void)_t_I64_947;
    I64 _t_I64_948 = I64_add(DEREF(self), _t_I64_947);
    (void)_t_I64_948;
    ;
    *self = _t_I64_948;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t_I64_949 = 1;
    (void)_t_I64_949;
    I64 _t_I64_950 = I64_sub(DEREF(self), _t_I64_949);
    (void)_t_I64_950;
    ;
    *self = _t_I64_950;
    ;
}

I64 * I64_unity(I64 * _self) {
    (void)_self;
    I64 _t_I64_951 = 1;
    (void)_t_I64_951;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_951; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t_I64_952 = 0;
    (void)_t_I64_952;
    I64 _t_I64_953 = I64_sub(_t_I64_952, DEREF(a));
    (void)_t_I64_953;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_953; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t_I64_956 = 0;
    (void)_t_I64_956;
    Bool _t_Bool_957 = I64_lt(a, &_t_I64_956);
    (void)_t_Bool_957;
    ;
    if (_t_Bool_957) {
        I64 _t_I64_954 = 0;
        (void)_t_I64_954;
        I64 _t_I64_955 = I64_sub(_t_I64_954, DEREF(a));
        (void)_t_I64_955;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_955; return _r; }
    }
    ;
    I64 _t_I64_958 = I64_clone(a);
    (void)_t_I64_958;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_958; return _r; }
}

U64 I64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I64 *au = a;
    (void)au;
    I64 *bu = b;
    (void)bu;
    Bool _t_Bool_961 = I64_lte(au, bu);
    (void)_t_Bool_961;
    if (_t_Bool_961) {
        I64 _t_I64_959 = I64_sub(DEREF(bu), DEREF(au));
        (void)_t_I64_959;
        U64 _t_U64_960 = I64_to_u64(_t_I64_959);
        (void)_t_U64_960;
        ;
        ;
        return _t_U64_960;
    }
    ;
    I64 _t_I64_962 = I64_sub(DEREF(au), DEREF(bu));
    (void)_t_I64_962;
    U64 _t_U64_963 = I64_to_u64(_t_I64_962);
    (void)_t_U64_963;
    ;
    return _t_U64_963;
}

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_964 = 8;
    (void)_t_I64_964;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_964; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_965 = 0;
    (void)_t_I64_965;
    I64 _t_I64_966 = 1;
    (void)_t_I64_966;
    I64 _t_I64_967 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_967;
    I64 _t_I64_968 = I64_sub(_t_I64_965, _t_I64_966);
    (void)_t_I64_968;
    ;
    ;
    Bool _t_Bool_969 = I64_eq(_t_I64_967, _t_I64_968);
    (void)_t_Bool_969;
    ;
    ;
    return _t_Bool_969;
}

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_970 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_970;
    I64 _t_I64_971 = 1;
    (void)_t_I64_971;
    Bool _t_Bool_972 = I64_eq(_t_I64_970, _t_I64_971);
    (void)_t_Bool_972;
    ;
    ;
    return _t_Bool_972;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_973 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_973;
    Bool _t_Bool_974 = not(_t_Bool_973);
    (void)_t_Bool_974;
    ;
    return _t_Bool_974;
}

Bool I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_975 = I64_gt(a, b);
    (void)_t_Bool_975;
    Bool _t_Bool_976 = not(_t_Bool_975);
    (void)_t_Bool_976;
    ;
    return _t_Bool_976;
}

Bool I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_977 = I64_lt(a, b);
    (void)_t_Bool_977;
    Bool _t_Bool_978 = not(_t_Bool_977);
    (void)_t_Bool_978;
    ;
    return _t_Bool_978;
}

Str * Bool_to_str(Bool * b) {
    (void)b;
    if (DEREF(b)) {
        Str *_t_Str_979 = Str_lit("true", 4ULL);
        (void)_t_Str_979;
        return _t_Str_979;
    } else {
        Str *_t_Str_980 = Str_lit("false", 5ULL);
        (void)_t_Str_980;
        return _t_Str_980;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_985 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_985;
    if (_t_Bool_985) {
        I64 _t_I64_981 = 0;
        (void)_t_I64_981;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_981; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_982 = 0;
        (void)_t_I64_982;
        I64 _t_I64_983 = 1;
        (void)_t_I64_983;
        I64 _t_I64_984 = I64_sub(_t_I64_982, _t_I64_983);
        (void)_t_I64_984;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_984; return _r; }
    }
    I64 _t_I64_986 = 1;
    (void)_t_I64_986;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_986; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_987 = 1;
    (void)_t_I64_987;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_987; return _r; }
}

Bool Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_988 = 0;
    (void)_t_I64_988;
    I64 _t_I64_989 = 1;
    (void)_t_I64_989;
    I64 _t_I64_990; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_990 = *_hp; free(_hp); }
    (void)_t_I64_990;
    I64 _t_I64_991 = I64_sub(_t_I64_988, _t_I64_989);
    (void)_t_I64_991;
    ;
    ;
    Bool _t_Bool_992 = I64_eq(_t_I64_990, _t_I64_991);
    (void)_t_Bool_992;
    ;
    ;
    return _t_Bool_992;
}

Bool Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_993; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_993 = *_hp; free(_hp); }
    (void)_t_I64_993;
    I64 _t_I64_994 = 1;
    (void)_t_I64_994;
    Bool _t_Bool_995 = I64_eq(_t_I64_993, _t_I64_994);
    (void)_t_Bool_995;
    ;
    ;
    return _t_Bool_995;
}

Bool Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_996 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_996;
    Bool _t_Bool_997 = not(_t_Bool_996);
    (void)_t_Bool_997;
    ;
    return _t_Bool_997;
}

Bool Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_998 = Bool_gt(a, b);
    (void)_t_Bool_998;
    Bool _t_Bool_999 = not(_t_Bool_998);
    (void)_t_Bool_999;
    ;
    return _t_Bool_999;
}

Bool Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1000 = Bool_lt(a, b);
    (void)_t_Bool_1000;
    Bool _t_Bool_1001 = not(_t_Bool_1000);
    (void)_t_Bool_1001;
    ;
    return _t_Bool_1001;
}

Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    Bool _t_Bool_1008 = Str_is_empty(elem_type);
    (void)_t_Bool_1008;
    if (_t_Bool_1008) {
        Str *_t_Str_1002 = Str_lit("Str", 3ULL);
        (void)_t_Str_1002;
        U32 _t_U32_1003 = 16;
        (void)_t_U32_1003;
        U32 _t_U32_1004 = 1;
        (void)_t_U32_1004;
        Array *_va_Array_16 = Array_new(_t_Str_1002, &_t_U32_1003, &_t_U32_1004);
        (void)_va_Array_16;
        Str_delete(_t_Str_1002, &(Bool){1});
        ;
        ;
        U32 _t_U32_1005 = 0;
        (void)_t_U32_1005;
        Str *_t_Str_1006 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_1006;
        Array_set(_va_Array_16, &_t_U32_1005, _t_Str_1006);
        ;
        Str *_t_Str_1007 = Str_lit("./src/core/array.til:21:41", 26ULL);
        (void)_t_Str_1007;
        panic(_t_Str_1007, _va_Array_16);
        Str_delete(_t_Str_1007, &(Bool){1});
    }
    ;
    void * _t_v_1009 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t_v_1009;
    void * _t_v_1010 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1010;
    void * _t_v_1011 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1011;
    Array *_t_Array_1012 = malloc(sizeof(Array));
    _t_Array_1012->data = _t_v_1009;
    _t_Array_1012->cap = DEREF(cap);
    _t_Array_1012->elem_size = DEREF(elem_size);
    { Str *_ca = Str_clone(elem_type); _t_Array_1012->elem_type = *_ca; free(_ca); }
    _t_Array_1012->elem_clone = _t_v_1010;
    _t_Array_1012->elem_delete = _t_v_1011;
    (void)_t_Array_1012;
    return _t_Array_1012;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_1027 = U32_gte(i, &self->cap);
    (void)_t_Bool_1027;
    if (_t_Bool_1027) {
        Str *_t_Str_1013 = Str_lit("Str", 3ULL);
        (void)_t_Str_1013;
        U32 _t_U32_1014 = 16;
        (void)_t_U32_1014;
        U32 _t_U32_1015 = 5;
        (void)_t_U32_1015;
        Array *_va_Array_17 = Array_new(_t_Str_1013, &_t_U32_1014, &_t_U32_1015);
        (void)_va_Array_17;
        Str_delete(_t_Str_1013, &(Bool){1});
        ;
        ;
        U32 _t_U32_1016 = 0;
        (void)_t_U32_1016;
        Str *_t_Str_1017 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_1017;
        Array_set(_va_Array_17, &_t_U32_1016, _t_Str_1017);
        ;
        U32 _t_U32_1018 = 1;
        (void)_t_U32_1018;
        Str *_t_Str_1019 = U32_to_str(i);
        (void)_t_Str_1019;
        Array_set(_va_Array_17, &_t_U32_1018, _t_Str_1019);
        ;
        U32 _t_U32_1020 = 2;
        (void)_t_U32_1020;
        Str *_t_Str_1021 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1021;
        Array_set(_va_Array_17, &_t_U32_1020, _t_Str_1021);
        ;
        U32 _t_U32_1022 = 3;
        (void)_t_U32_1022;
        Str *_t_Str_1023 = U32_to_str(&self->cap);
        (void)_t_Str_1023;
        Array_set(_va_Array_17, &_t_U32_1022, _t_Str_1023);
        ;
        U32 _t_U32_1024 = 4;
        (void)_t_U32_1024;
        Str *_t_Str_1025 = Str_lit(")", 1ULL);
        (void)_t_Str_1025;
        Array_set(_va_Array_17, &_t_U32_1024, _t_Str_1025);
        ;
        Str *_t_Str_1026 = Str_lit("./src/core/array.til:32:19", 26ULL);
        (void)_t_Str_1026;
        panic(_t_Str_1026, _va_Array_17);
        Str_delete(_t_Str_1026, &(Bool){1});
    }
    ;
    U32 _t_U64_1028 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1028;
    void *_t_v_1029 = ptr_add(self->data, _t_U64_1028);
    (void)_t_v_1029;
    ;
    return _t_v_1029;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_1044 = U32_gte(i, &self->cap);
    (void)_t_Bool_1044;
    if (_t_Bool_1044) {
        Str *_t_Str_1030 = Str_lit("Str", 3ULL);
        (void)_t_Str_1030;
        U32 _t_U32_1031 = 16;
        (void)_t_U32_1031;
        U32 _t_U32_1032 = 5;
        (void)_t_U32_1032;
        Array *_va_Array_18 = Array_new(_t_Str_1030, &_t_U32_1031, &_t_U32_1032);
        (void)_va_Array_18;
        Str_delete(_t_Str_1030, &(Bool){1});
        ;
        ;
        U32 _t_U32_1033 = 0;
        (void)_t_U32_1033;
        Str *_t_Str_1034 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_1034;
        Array_set(_va_Array_18, &_t_U32_1033, _t_Str_1034);
        ;
        U32 _t_U32_1035 = 1;
        (void)_t_U32_1035;
        Str *_t_Str_1036 = U32_to_str(i);
        (void)_t_Str_1036;
        Array_set(_va_Array_18, &_t_U32_1035, _t_Str_1036);
        ;
        U32 _t_U32_1037 = 2;
        (void)_t_U32_1037;
        Str *_t_Str_1038 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1038;
        Array_set(_va_Array_18, &_t_U32_1037, _t_Str_1038);
        ;
        U32 _t_U32_1039 = 3;
        (void)_t_U32_1039;
        Str *_t_Str_1040 = U32_to_str(&self->cap);
        (void)_t_Str_1040;
        Array_set(_va_Array_18, &_t_U32_1039, _t_Str_1040);
        ;
        U32 _t_U32_1041 = 4;
        (void)_t_U32_1041;
        Str *_t_Str_1042 = Str_lit(")", 1ULL);
        (void)_t_Str_1042;
        Array_set(_va_Array_18, &_t_U32_1041, _t_Str_1042);
        ;
        Str *_t_Str_1043 = Str_lit("./src/core/array.til:40:19", 26ULL);
        (void)_t_Str_1043;
        panic(_t_Str_1043, _va_Array_18);
        Str_delete(_t_Str_1043, &(Bool){1});
    }
    ;
    U32 _t_U64_1045 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1045;
    void *_t_v_1046 = ptr_add(self->data, _t_U64_1045);
    (void)_t_v_1046;
    Bool _t_Bool_1047 = 0;
    (void)_t_Bool_1047;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1046, &_t_Bool_1047);
    ;
    ;
    U32 _t_U64_1048 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1048;
    void *_t_v_1049 = ptr_add(self->data, _t_U64_1048);
    (void)_t_v_1049;
    memcpy(_t_v_1049, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_1050 = self->cap;
        (void)_re_U32_1050;
        U32 _rc_U32_1050 = 0;
        (void)_rc_U32_1050;
        Bool _t_Bool_1059 = U32_lte(&_rc_U32_1050, &_re_U32_1050);
        (void)_t_Bool_1059;
        if (_t_Bool_1059) {
            while (1) {
                Bool _wcond_Bool_1051 = U32_lt(&_rc_U32_1050, &_re_U32_1050);
                (void)_wcond_Bool_1051;
                if (_wcond_Bool_1051) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1050);
                (void)i;
                U32_inc(&_rc_U32_1050);
                U32 _t_U64_1052 = U32_mul(i, self->elem_size);
                (void)_t_U64_1052;
                ;
                void *_t_v_1053 = ptr_add(self->data, _t_U64_1052);
                (void)_t_v_1053;
                Bool _t_Bool_1054 = 0;
                (void)_t_Bool_1054;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1053, &_t_Bool_1054);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1055 = U32_gt(&_rc_U32_1050, &_re_U32_1050);
                (void)_wcond_Bool_1055;
                if (_wcond_Bool_1055) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1050);
                (void)i;
                U32_dec(&_rc_U32_1050);
                U32 _t_U64_1056 = U32_mul(i, self->elem_size);
                (void)_t_U64_1056;
                ;
                void *_t_v_1057 = ptr_add(self->data, _t_U64_1056);
                (void)_t_v_1057;
                Bool _t_Bool_1058 = 0;
                (void)_t_Bool_1058;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1057, &_t_Bool_1058);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_1060 = 0;
    (void)_t_Bool_1060;
    Str_delete(&self->elem_type, &_t_Bool_1060);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_1073 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_1073;
    void * new_data = malloc(_t_U64_1073);
    (void)new_data;
    ;
    {
        U32 _re_U32_1061 = self->cap;
        (void)_re_U32_1061;
        U32 _rc_U32_1061 = 0;
        (void)_rc_U32_1061;
        Bool _t_Bool_1072 = U32_lte(&_rc_U32_1061, &_re_U32_1061);
        (void)_t_Bool_1072;
        if (_t_Bool_1072) {
            while (1) {
                Bool _wcond_Bool_1062 = U32_lt(&_rc_U32_1061, &_re_U32_1061);
                (void)_wcond_Bool_1062;
                if (_wcond_Bool_1062) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1061);
                (void)i;
                U32_inc(&_rc_U32_1061);
                U32 _t_U64_1063 = U32_mul(i, self->elem_size);
                (void)_t_U64_1063;
                void *_t_v_1064 = ptr_add(self->data, _t_U64_1063);
                (void)_t_v_1064;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1064);
                (void)cloned;
                ;
                U32 _t_U64_1065 = U32_mul(i, self->elem_size);
                (void)_t_U64_1065;
                ;
                void *_t_v_1066 = ptr_add(new_data, _t_U64_1065);
                (void)_t_v_1066;
                memcpy(_t_v_1066, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1067 = U32_gt(&_rc_U32_1061, &_re_U32_1061);
                (void)_wcond_Bool_1067;
                if (_wcond_Bool_1067) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1061);
                (void)i;
                U32_dec(&_rc_U32_1061);
                U32 _t_U64_1068 = U32_mul(i, self->elem_size);
                (void)_t_U64_1068;
                void *_t_v_1069 = ptr_add(self->data, _t_U64_1068);
                (void)_t_v_1069;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1069);
                (void)cloned;
                ;
                U32 _t_U64_1070 = U32_mul(i, self->elem_size);
                (void)_t_U64_1070;
                ;
                void *_t_v_1071 = ptr_add(new_data, _t_U64_1070);
                (void)_t_v_1071;
                memcpy(_t_v_1071, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_1074 = malloc(sizeof(Array));
    _t_Array_1074->data = new_data;
    _t_Array_1074->cap = self->cap;
    _t_Array_1074->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_1074->elem_type = *_ca; free(_ca); }
    _t_Array_1074->elem_clone = (void *)self->elem_clone;
    _t_Array_1074->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_1074;
    return _t_Array_1074;
}

U32 Array_size(void) {
    I64 _t_I64_1075 = 48;
    (void)_t_I64_1075;
    return _t_I64_1075;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2642 = Str_lit("Str", 3ULL);
    (void)_t_Str_2642;
    U32 _t_U32_2643 = 16;
    (void)_t_U32_2643;
    U32 _t_U32_2644 = 3;
    (void)_t_U32_2644;
    Array *_va_Array_80 = Array_new(_t_Str_2642, &_t_U32_2643, &_t_U32_2644);
    (void)_va_Array_80;
    Str_delete(_t_Str_2642, &(Bool){1});
    ;
    ;
    U32 _t_U32_2645 = 0;
    (void)_t_U32_2645;
    Str *_t_Str_2646 = Str_clone(loc_str);
    (void)_t_Str_2646;
    Array_set(_va_Array_80, &_t_U32_2645, _t_Str_2646);
    ;
    U32 _t_U32_2647 = 1;
    (void)_t_U32_2647;
    Str *_t_Str_2648 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2648;
    Array_set(_va_Array_80, &_t_U32_2647, _t_Str_2648);
    ;
    U32 _t_U32_2649 = 2;
    (void)_t_U32_2649;
    Str *_t_Str_2650 = format(parts);
    (void)_t_Str_2650;
    Array_set(_va_Array_80, &_t_U32_2649, _t_Str_2650);
    ;
    println(_va_Array_80);
    I64 _t_I64_2651 = 1;
    (void)_t_I64_2651;
    exit(_t_I64_2651);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2669 = not(DEREF(cond));
    (void)_t_Bool_2669;
    if (_t_Bool_2669) {
        Str *_t_Str_2664 = Str_lit("Str", 3ULL);
        (void)_t_Str_2664;
        U32 _t_U32_2665 = 16;
        (void)_t_U32_2665;
        U32 _t_U32_2666 = 1;
        (void)_t_U32_2666;
        Array *_va_Array_83 = Array_new(_t_Str_2664, &_t_U32_2665, &_t_U32_2666);
        (void)_va_Array_83;
        Str_delete(_t_Str_2664, &(Bool){1});
        ;
        ;
        U32 _t_U32_2667 = 0;
        (void)_t_U32_2667;
        Str *_t_Str_2668 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2668;
        Array_set(_va_Array_83, &_t_U32_2667, _t_Str_2668);
        ;
        panic(loc_str, _va_Array_83);
    }
    ;
    Bool _t_Bool_2670 = 1;
    (void)_t_Bool_2670;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2670; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2692 = I64_neq(a, b);
    (void)_t_Bool_2692;
    if (_t_Bool_2692) {
        Str *_t_Str_2679 = Str_lit("Str", 3ULL);
        (void)_t_Str_2679;
        U32 _t_U32_2680 = 16;
        (void)_t_U32_2680;
        U32 _t_U32_2681 = 5;
        (void)_t_U32_2681;
        Array *_va_Array_85 = Array_new(_t_Str_2679, &_t_U32_2680, &_t_U32_2681);
        (void)_va_Array_85;
        Str_delete(_t_Str_2679, &(Bool){1});
        ;
        ;
        U32 _t_U32_2682 = 0;
        (void)_t_U32_2682;
        Str *_t_Str_2683 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2683;
        Array_set(_va_Array_85, &_t_U32_2682, _t_Str_2683);
        ;
        U32 _t_U32_2684 = 1;
        (void)_t_U32_2684;
        Str *_t_Str_2685 = I64_to_str(a);
        (void)_t_Str_2685;
        Array_set(_va_Array_85, &_t_U32_2684, _t_Str_2685);
        ;
        U32 _t_U32_2686 = 2;
        (void)_t_U32_2686;
        Str *_t_Str_2687 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2687;
        Array_set(_va_Array_85, &_t_U32_2686, _t_Str_2687);
        ;
        U32 _t_U32_2688 = 3;
        (void)_t_U32_2688;
        Str *_t_Str_2689 = I64_to_str(b);
        (void)_t_Str_2689;
        Array_set(_va_Array_85, &_t_U32_2688, _t_Str_2689);
        ;
        U32 _t_U32_2690 = 4;
        (void)_t_U32_2690;
        Str *_t_Str_2691 = Str_lit("'", 1ULL);
        (void)_t_Str_2691;
        Array_set(_va_Array_85, &_t_U32_2690, _t_Str_2691);
        ;
        panic(loc_str, _va_Array_85);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2708 = parts;
        (void)_fc_Array_2708;
        U32 _fi_USize_2708 = 0;
        (void)_fi_USize_2708;
        while (1) {
            U32 _t_U32_2710; { U32 *_hp = (U32 *)Array_len(_fc_Array_2708); _t_U32_2710 = *_hp; free(_hp); }
            (void)_t_U32_2710;
            Bool _wcond_Bool_2709 = U32_lt(&_fi_USize_2708, &_t_U32_2710);
            (void)_wcond_Bool_2709;
            ;
            if (_wcond_Bool_2709) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2708, &_fi_USize_2708);
            (void)s;
            U32 _t_U32_2711 = 1;
            (void)_t_U32_2711;
            U32 _t_U32_2712 = U32_add(_fi_USize_2708, _t_U32_2711);
            (void)_t_U32_2712;
            ;
            _fi_USize_2708 = _t_U32_2712;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

void test_simple_add(void) {
    I64 _t_I64_2881 = 1;
    (void)_t_I64_2881;
    I64 _t_I64_2882 = 2;
    (void)_t_I64_2882;
    I64 result = 3;
    (void)result;
    ;
    ;
    Str *_t_Str_2883 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_2883;
    I64 _t_I64_2884 = 3;
    (void)_t_I64_2884;
    assert_eq(_t_Str_2883, &result, &_t_I64_2884);
    ;
    Str_delete(_t_Str_2883, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 _t_I64_2885 = 1;
    (void)_t_I64_2885;
    I64 _t_I64_2886 = 2;
    (void)_t_I64_2886;
    I64 _t_I64_2887 = 10;
    (void)_t_I64_2887;
    I64 _t_I64_2888 = 5;
    (void)_t_I64_2888;
    I64 _t_I64_2889 = 3;
    (void)_t_I64_2889;
    ;
    ;
    I64 _t_I64_2890 = 5;
    (void)_t_I64_2890;
    ;
    ;
    I64 result = 15;
    (void)result;
    ;
    ;
    Str *_t_Str_2891 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_2891;
    I64 _t_I64_2892 = 15;
    (void)_t_I64_2892;
    assert_eq(_t_Str_2891, &result, &_t_I64_2892);
    ;
    Str_delete(_t_Str_2891, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 _t_I64_2893 = 2;
    (void)_t_I64_2893;
    I64 _t_I64_2894 = 3;
    (void)_t_I64_2894;
    I64 _t_I64_2895 = 4;
    (void)_t_I64_2895;
    I64 _t_I64_2896 = 5;
    (void)_t_I64_2896;
    I64 _t_I64_2897 = 6;
    (void)_t_I64_2897;
    ;
    ;
    I64 _t_I64_2898 = 20;
    (void)_t_I64_2898;
    ;
    ;
    I64 result = 26;
    (void)result;
    ;
    ;
    Str *_t_Str_2899 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_2899;
    I64 _t_I64_2900 = 26;
    (void)_t_I64_2900;
    assert_eq(_t_Str_2899, &result, &_t_I64_2900);
    ;
    Str_delete(_t_Str_2899, &(Bool){1});
    ;
}

Str * poem(I64 * depth, Str * current, Str * s1, Str * s2) {
    (void)depth;
    (void)current;
    (void)s1;
    (void)s2;
    I64 _t_I64_2908 = 4;
    (void)_t_I64_2908;
    Bool _t_Bool_2909 = I64_eq(DEREF(depth), _t_I64_2908);
    (void)_t_Bool_2909;
    ;
    if (_t_Bool_2909) {
        Str *_t_Str_2901 = Str_lit("\n", 2ULL);
        (void)_t_Str_2901;
        Str *_t_Str_2902 = Str_concat(current, _t_Str_2901);
        (void)_t_Str_2902;
        Str_delete(_t_Str_2901, &(Bool){1});
        ;
        return _t_Str_2902;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    I64 _t_I64_2910 = 1;
    (void)_t_I64_2910;
    I64 _t_I64_2911 = I64_add(DEREF(depth), _t_I64_2910);
    (void)_t_I64_2911;
    ;
    Str *_t_Str_2912 = Str_concat(current, s1);
    (void)_t_Str_2912;
    Str *_t_Str_2913 = poem(&_t_I64_2911, _t_Str_2912, s1, s2);
    (void)_t_Str_2913;
    ;
    Str_delete(_t_Str_2912, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2913); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2913, &(Bool){1});
    I64 _t_I64_2914 = 1;
    (void)_t_I64_2914;
    I64 _t_I64_2915 = I64_add(DEREF(depth), _t_I64_2914);
    (void)_t_I64_2915;
    ;
    Str *_t_Str_2916 = Str_concat(current, s2);
    (void)_t_Str_2916;
    Str *_t_Str_2917 = poem(&_t_I64_2915, _t_Str_2916, s1, s2);
    (void)_t_Str_2917;
    ;
    Str_delete(_t_Str_2916, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2917); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2917, &(Bool){1});
    I64 _t_I64_2918 = 2;
    (void)_t_I64_2918;
    Bool _t_Bool_2919 = I64_eq(DEREF(depth), _t_I64_2918);
    (void)_t_Bool_2919;
    ;
    if (_t_Bool_2919) {
        I64 _t_I64_2903 = 1;
        (void)_t_I64_2903;
        Str *_t_Str_2904 = Str_lit("lei", 3ULL);
        (void)_t_Str_2904;
        I64 _t_I64_2905 = I64_add(DEREF(depth), _t_I64_2903);
        (void)_t_I64_2905;
        ;
        Str *_t_Str_2906 = Str_concat(current, _t_Str_2904);
        (void)_t_Str_2906;
        Str_delete(_t_Str_2904, &(Bool){1});
        Str *_t_Str_2907 = poem(&_t_I64_2905, _t_Str_2906, s1, s2);
        (void)_t_Str_2907;
        ;
        Str_delete(_t_Str_2906, &(Bool){1});
        result = Str_concat(result, _t_Str_2907);
        Str_delete(_t_Str_2907, &(Bool){1});
    }
    ;
    return result;
}

Str * make_poem(Str * s1, Str * s2) {
    (void)s1;
    (void)s2;
    I64 _t_I64_2920 = 0;
    (void)_t_I64_2920;
    Str *_t_Str_2921 = Str_lit("", 0ULL);
    (void)_t_Str_2921;
    Str *_t_Str_2922 = poem(&_t_I64_2920, _t_Str_2921, s1, s2);
    (void)_t_Str_2922;
    ;
    Str_delete(_t_Str_2921, &(Bool){1});
    return _t_Str_2922;
}

void test_lolalalo(void) {
    Str *_t_Str_2923 = Str_lit("lo", 2ULL);
    (void)_t_Str_2923;
    Str *_t_Str_2924 = Str_lit("la", 2ULL);
    (void)_t_Str_2924;
    Str *lo_la = make_poem(_t_Str_2923, _t_Str_2924);
    (void)lo_la;
    Str_delete(_t_Str_2923, &(Bool){1});
    Str_delete(_t_Str_2924, &(Bool){1});
    Str *_t_Str_2925 = Str_lit("la", 2ULL);
    (void)_t_Str_2925;
    Str *_t_Str_2926 = Str_lit("lo", 2ULL);
    (void)_t_Str_2926;
    Str *la_lo = make_poem(_t_Str_2925, _t_Str_2926);
    (void)la_lo;
    Str_delete(_t_Str_2925, &(Bool){1});
    Str_delete(_t_Str_2926, &(Bool){1});
    Str *_t_Str_2927 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_2927;
    Str *_t_Str_2928 = Str_lit("src/test/constfold.til:56:12", 28ULL);
    (void)_t_Str_2928;
    Bool _t_Bool_2929 = Str_contains(lo_la, _t_Str_2927);
    (void)_t_Bool_2929;
    Str_delete(_t_Str_2927, &(Bool){1});
    Bool _t_Bool_2930; { Bool *_hp = (Bool *)assert(_t_Str_2928, &_t_Bool_2929); _t_Bool_2930 = *_hp; free(_hp); }
    (void)_t_Bool_2930;
    ;
    ;
    Str_delete(_t_Str_2928, &(Bool){1});
    Str *_t_Str_2931 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_2931;
    Str *_t_Str_2932 = Str_lit("src/test/constfold.til:57:12", 28ULL);
    (void)_t_Str_2932;
    Bool _t_Bool_2933 = Str_contains(la_lo, _t_Str_2931);
    (void)_t_Bool_2933;
    Str_delete(_t_Str_2931, &(Bool){1});
    Bool _t_Bool_2934; { Bool *_hp = (Bool *)assert(_t_Str_2932, &_t_Bool_2933); _t_Bool_2934 = *_hp; free(_hp); }
    (void)_t_Bool_2934;
    ;
    ;
    Str_delete(_t_Str_2932, &(Bool){1});
    Str *_t_Str_2935 = Str_lit("lolei", 5ULL);
    (void)_t_Str_2935;
    Str *_t_Str_2936 = Str_lit("src/test/constfold.til:59:12", 28ULL);
    (void)_t_Str_2936;
    Bool _t_Bool_2937 = Str_contains(lo_la, _t_Str_2935);
    (void)_t_Bool_2937;
    Str_delete(_t_Str_2935, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    Bool _t_Bool_2938; { Bool *_hp = (Bool *)assert(_t_Str_2936, &_t_Bool_2937); _t_Bool_2938 = *_hp; free(_hp); }
    (void)_t_Bool_2938;
    ;
    ;
    Str_delete(_t_Str_2936, &(Bool){1});
    Str *_t_Str_2939 = Str_lit("lalei", 5ULL);
    (void)_t_Str_2939;
    Str *_t_Str_2940 = Str_lit("src/test/constfold.til:60:12", 28ULL);
    (void)_t_Str_2940;
    Bool _t_Bool_2941 = Str_contains(la_lo, _t_Str_2939);
    (void)_t_Bool_2941;
    Str_delete(_t_Str_2939, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    Bool _t_Bool_2942; { Bool *_hp = (Bool *)assert(_t_Str_2940, &_t_Bool_2941); _t_Bool_2942 = *_hp; free(_hp); }
    (void)_t_Bool_2942;
    ;
    ;
    Str_delete(_t_Str_2940, &(Bool){1});
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
void *Array_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Array_size(); return _r;
}
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Dynamic_size;
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
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Array_new;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Array_len;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Array_get;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)Array_set;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Array_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Array_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Array_size_dyn;
    fprintf(stderr, "dyn_fn: unknown %s.%s\n", (char*)type_name->c_str, (char*)method->c_str);
    exit(1);
}

U32 dyn_size_of(Str *type_name) {
    (void)type_name;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return sizeof(F32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return sizeof(U64);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return sizeof(U32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return sizeof(I32);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return sizeof(U8);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) return sizeof(Vec);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return sizeof(Str);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return sizeof(Dynamic);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) return sizeof(I16);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return sizeof(I64);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return sizeof(Bool);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) return sizeof(Array);
    fprintf(stderr, "dyn_size_of: unknown type %.*s\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

int main(void) {
    I64 _t_I64_848 = 0;
    (void)_t_I64_848;
    I64 _t_I64_849 = 1;
    (void)_t_I64_849;
    I64 _t_I64_850 = I64_sub(_t_I64_848, _t_I64_849);
    (void)_t_I64_850;
    CAP_LIT = I64_to_usize(_t_I64_850);
    (void)CAP_LIT;
    I64 _t_I64_851 = 0;
    (void)_t_I64_851;
    I64 _t_I64_852 = 2;
    (void)_t_I64_852;
    I64 _t_I64_853 = I64_sub(_t_I64_851, _t_I64_852);
    (void)_t_I64_853;
    CAP_VIEW = I64_to_usize(_t_I64_853);
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
