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
Vec * Vec_new(Str * elem_type);
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
Vec * Vec_new(Str * elem_type);
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
Str __til_info_blob__;

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

Vec * Vec_new(Str * elem_type) {
    (void)elem_type;
    Bool _t_Bool_154 = Str_is_empty(elem_type);
    (void)_t_Bool_154;
    if (_t_Bool_154) {
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
        Str *_t_Str_147 = Str_lit("./src/core/vec.til:24:19", 24ULL);
        (void)_t_Str_147;
        panic(_t_Str_147, _va_Array_0);
        Str_delete(_t_Str_147, &(Bool){1});
    }
    ;
    Str *_t_Str_155 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_155;
    Bool _t_Bool_156 = Str_eq(elem_type, _t_Str_155);
    (void)_t_Bool_156;
    Str_delete(_t_Str_155, &(Bool){1});
    if (_t_Bool_156) {
        U64 _t_U64_148 = 8;
        (void)_t_U64_148;
        void * _t_v_149 = malloc(_t_U64_148);
        (void)_t_v_149;
        ;
        U32 _t_U32_150 = 0;
        (void)_t_U32_150;
        I64 _t_I64_151 = 1;
        (void)_t_I64_151;
        I64 _t_I64_152 = 8;
        (void)_t_I64_152;
        Vec *_t_Vec_153 = malloc(sizeof(Vec));
        _t_Vec_153->data = _t_v_149;
        _t_Vec_153->count = _t_U32_150;
        _t_Vec_153->cap = _t_I64_151;
        _t_Vec_153->elem_size = _t_I64_152;
        { Str *_ca = Str_clone(elem_type); _t_Vec_153->elem_type = *_ca; free(_ca); }
        _t_Vec_153->elem_clone = (void *)(void *)default_clone;
        _t_Vec_153->elem_delete = (void *)(void *)default_delete;
        (void)_t_Vec_153;
        ;
        ;
        ;
        ;
        return _t_Vec_153;
    }
    ;
    U32 sz = dyn_size_of(elem_type);
    (void)sz;
    void * _t_v_157 = malloc(sz);
    (void)_t_v_157;
    U32 _t_U32_158 = 0;
    (void)_t_U32_158;
    I64 _t_I64_159 = 1;
    (void)_t_I64_159;
    void * _t_v_160 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_160;
    void * _t_v_161 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_161;
    Vec *_t_Vec_162 = malloc(sizeof(Vec));
    _t_Vec_162->data = _t_v_157;
    _t_Vec_162->count = _t_U32_158;
    _t_Vec_162->cap = _t_I64_159;
    _t_Vec_162->elem_size = sz;
    { Str *_ca = Str_clone(elem_type); _t_Vec_162->elem_type = *_ca; free(_ca); }
    _t_Vec_162->elem_clone = _t_v_160;
    _t_Vec_162->elem_delete = _t_v_161;
    (void)_t_Vec_162;
    ;
    ;
    ;
    return _t_Vec_162;
}

U32 Vec_len(Vec * self) {
    (void)self;
    return self->count;
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t_Bool_167 = U32_eq(self->count, self->cap);
    (void)_t_Bool_167;
    if (_t_Bool_167) {
        U32 _t_U32_163 = 2;
        (void)_t_U32_163;
        U32 new_cap = U32_mul(self->cap, _t_U32_163);
        (void)new_cap;
        ;
        U32 _t_U64_164 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_164;
        void * _t_v_165 = realloc(self->data, _t_U64_164);
        (void)_t_v_165;
        ;
        self->data = _t_v_165;
        U32 _t_U32_166 = U32_clone(&new_cap);
        (void)_t_U32_166;
        ;
        self->cap = _t_U32_166;
        ;
    }
    ;
    U32 _t_U64_168 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_168;
    void *_t_v_169 = ptr_add(self->data, _t_U64_168);
    (void)_t_v_169;
    memcpy(_t_v_169, val, self->elem_size);
    ;
    free(val);
    U32 _t_U32_170 = 1;
    (void)_t_U32_170;
    U32 _t_U32_171 = U32_add(self->count, _t_U32_170);
    (void)_t_U32_171;
    ;
    self->count = _t_U32_171;
    ;
}

void Vec_append(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_184 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_184;
    Bool _t_Bool_185 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_185;
    Bool _t_Bool_186 = not(_t_Bool_184);
    (void)_t_Bool_186;
    ;
    Bool _t_Bool_187 = not(_t_Bool_185);
    (void)_t_Bool_187;
    ;
    Bool _t_Bool_188 = or(_t_Bool_186, _t_Bool_187);
    (void)_t_Bool_188;
    ;
    ;
    if (_t_Bool_188) {
        Str *_t_Str_172 = Str_lit("Str", 3ULL);
        (void)_t_Str_172;
        U32 _t_U32_173 = 16;
        (void)_t_U32_173;
        U32 _t_U32_174 = 1;
        (void)_t_U32_174;
        Array *_va_Array_1 = Array_new(_t_Str_172, &_t_U32_173, &_t_U32_174);
        (void)_va_Array_1;
        Str_delete(_t_Str_172, &(Bool){1});
        ;
        ;
        U32 _t_U32_175 = 0;
        (void)_t_U32_175;
        Str *_t_Str_176 = Str_lit("Vec.append: incompatible vecs", 29ULL);
        (void)_t_Str_176;
        Array_set(_va_Array_1, &_t_U32_175, _t_Str_176);
        ;
        Str *_t_Str_177 = Str_lit("./src/core/vec.til:56:19", 24ULL);
        (void)_t_Str_177;
        panic(_t_Str_177, _va_Array_1);
        Str_delete(_t_Str_177, &(Bool){1});
    }
    ;
    U32 _t_U32_189 = 0;
    (void)_t_U32_189;
    Bool _t_Bool_190 = U32_eq(other->count, _t_U32_189);
    (void)_t_Bool_190;
    ;
    if (_t_Bool_190) {
        ;
        Vec_delete(other, &(Bool){0});
        return;
    }
    ;
    U32 needed = U32_add(self->count, other->count);
    (void)needed;
    Bool _t_Bool_191 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_191;
    if (_t_Bool_191) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_178 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_178;
            if (_wcond_Bool_178) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_179 = 2;
            (void)_t_U32_179;
            U32 _t_U32_180 = U32_mul(new_cap, _t_U32_179);
            (void)_t_U32_180;
            ;
            new_cap = _t_U32_180;
            ;
        }
        U32 _t_U64_181 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_181;
        void * _t_v_182 = realloc(self->data, _t_U64_181);
        (void)_t_v_182;
        ;
        self->data = _t_v_182;
        U32 _t_U32_183 = U32_clone(&new_cap);
        (void)_t_U32_183;
        ;
        self->cap = _t_U32_183;
        ;
    }
    ;
    U32 _t_U64_192 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_192;
    void *_t_v_193 = ptr_add(self->data, _t_U64_192);
    (void)_t_v_193;
    U32 _t_U64_194 = U32_mul(other->count, self->elem_size);
    (void)_t_U64_194;
    memcpy(_t_v_193, other->data, _t_U64_194);
    ;
    ;
    U32 _t_U32_195 = U32_clone(&needed);
    (void)_t_U32_195;
    ;
    self->count = _t_U32_195;
    ;
    U32 _t_U32_196 = 0;
    (void)_t_U32_196;
    other->count = _t_U32_196;
    ;
    Vec_delete(other, &(Bool){0});
}

void Vec_move_from(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_220 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_220;
    Bool _t_Bool_221 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_221;
    Bool _t_Bool_222 = not(_t_Bool_220);
    (void)_t_Bool_222;
    ;
    Bool _t_Bool_223 = not(_t_Bool_221);
    (void)_t_Bool_223;
    ;
    Bool _t_Bool_224 = or(_t_Bool_222, _t_Bool_223);
    (void)_t_Bool_224;
    ;
    ;
    if (_t_Bool_224) {
        Str *_t_Str_197 = Str_lit("Str", 3ULL);
        (void)_t_Str_197;
        U32 _t_U32_198 = 16;
        (void)_t_U32_198;
        U32 _t_U32_199 = 1;
        (void)_t_U32_199;
        Array *_va_Array_2 = Array_new(_t_Str_197, &_t_U32_198, &_t_U32_199);
        (void)_va_Array_2;
        Str_delete(_t_Str_197, &(Bool){1});
        ;
        ;
        U32 _t_U32_200 = 0;
        (void)_t_U32_200;
        Str *_t_Str_201 = Str_lit("Vec.move_from: incompatible vecs", 32ULL);
        (void)_t_Str_201;
        Array_set(_va_Array_2, &_t_U32_200, _t_Str_201);
        ;
        Str *_t_Str_202 = Str_lit("./src/core/vec.til:83:19", 24ULL);
        (void)_t_Str_202;
        panic(_t_Str_202, _va_Array_2);
        Str_delete(_t_Str_202, &(Bool){1});
    }
    ;
    Bool _t_Bool_225 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_225;
    Str *_t_Str_226 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_226;
    Bool _t_Bool_227 = Str_eq(&self->elem_type, _t_Str_226);
    (void)_t_Bool_227;
    Str_delete(_t_Str_226, &(Bool){1});
    Bool _t_Bool_228 = not(_t_Bool_225);
    (void)_t_Bool_228;
    ;
    Bool _t_Bool_229 = not(_t_Bool_227);
    (void)_t_Bool_229;
    ;
    Bool _t_Bool_230 = and(_t_Bool_228, _t_Bool_229);
    (void)_t_Bool_230;
    ;
    ;
    if (_t_Bool_230) {
        {
            U32 _re_U32_203 = self->count;
            (void)_re_U32_203;
            U32 _rc_U32_203 = 0;
            (void)_rc_U32_203;
            Bool _t_Bool_212 = U32_lte(&_rc_U32_203, &_re_U32_203);
            (void)_t_Bool_212;
            if (_t_Bool_212) {
                while (1) {
                    Bool _wcond_Bool_204 = U32_lt(&_rc_U32_203, &_re_U32_203);
                    (void)_wcond_Bool_204;
                    if (_wcond_Bool_204) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_203);
                    (void)i;
                    U32_inc(&_rc_U32_203);
                    U32 _t_U64_205 = U32_mul(i, self->elem_size);
                    (void)_t_U64_205;
                    ;
                    void *_t_v_206 = ptr_add(self->data, _t_U64_205);
                    (void)_t_v_206;
                    Bool _t_Bool_207 = 0;
                    (void)_t_Bool_207;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_206, &_t_Bool_207);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_208 = U32_gt(&_rc_U32_203, &_re_U32_203);
                    (void)_wcond_Bool_208;
                    if (_wcond_Bool_208) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_203);
                    (void)i;
                    U32_dec(&_rc_U32_203);
                    U32 _t_U64_209 = U32_mul(i, self->elem_size);
                    (void)_t_U64_209;
                    ;
                    void *_t_v_210 = ptr_add(self->data, _t_U64_209);
                    (void)_t_v_210;
                    Bool _t_Bool_211 = 0;
                    (void)_t_Bool_211;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_210, &_t_Bool_211);
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
    Bool _t_Bool_231 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_231;
    if (_t_Bool_231) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_213 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_213;
            if (_wcond_Bool_213) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_214 = 2;
            (void)_t_U32_214;
            U32 _t_U32_215 = U32_mul(new_cap, _t_U32_214);
            (void)_t_U32_215;
            ;
            new_cap = _t_U32_215;
            ;
        }
        U32 _t_U64_216 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_216;
        void * _t_v_217 = realloc(self->data, _t_U64_216);
        (void)_t_v_217;
        ;
        self->data = _t_v_217;
        U32 _t_U32_218 = U32_clone(&new_cap);
        (void)_t_U32_218;
        ;
        self->cap = _t_U32_218;
        ;
    }
    ;
    U32 _t_U32_232 = 0;
    (void)_t_U32_232;
    Bool _t_Bool_233 = U32_gt(&needed, &_t_U32_232);
    (void)_t_Bool_233;
    ;
    if (_t_Bool_233) {
        U32 _t_U64_219 = U32_mul(needed, self->elem_size);
        (void)_t_U64_219;
        memcpy(self->data, other->data, _t_U64_219);
        ;
    }
    ;
    U32 _t_U32_234 = U32_clone(&needed);
    (void)_t_U32_234;
    ;
    self->count = _t_U32_234;
    ;
    U32 _t_U32_235 = 0;
    (void)_t_U32_235;
    other->count = _t_U32_235;
    ;
}

void * Vec_get(Vec * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_250 = U32_gte(i, &self->count);
    (void)_t_Bool_250;
    if (_t_Bool_250) {
        Str *_t_Str_236 = Str_lit("Str", 3ULL);
        (void)_t_Str_236;
        U32 _t_U32_237 = 16;
        (void)_t_U32_237;
        U32 _t_U32_238 = 5;
        (void)_t_U32_238;
        Array *_va_Array_3 = Array_new(_t_Str_236, &_t_U32_237, &_t_U32_238);
        (void)_va_Array_3;
        Str_delete(_t_Str_236, &(Bool){1});
        ;
        ;
        U32 _t_U32_239 = 0;
        (void)_t_U32_239;
        Str *_t_Str_240 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t_Str_240;
        Array_set(_va_Array_3, &_t_U32_239, _t_Str_240);
        ;
        U32 _t_U32_241 = 1;
        (void)_t_U32_241;
        Str *_t_Str_242 = U32_to_str(i);
        (void)_t_Str_242;
        Array_set(_va_Array_3, &_t_U32_241, _t_Str_242);
        ;
        U32 _t_U32_243 = 2;
        (void)_t_U32_243;
        Str *_t_Str_244 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_244;
        Array_set(_va_Array_3, &_t_U32_243, _t_Str_244);
        ;
        U32 _t_U32_245 = 3;
        (void)_t_U32_245;
        Str *_t_Str_246 = U32_to_str(&self->count);
        (void)_t_Str_246;
        Array_set(_va_Array_3, &_t_U32_245, _t_Str_246);
        ;
        U32 _t_U32_247 = 4;
        (void)_t_U32_247;
        Str *_t_Str_248 = Str_lit(")", 1ULL);
        (void)_t_Str_248;
        Array_set(_va_Array_3, &_t_U32_247, _t_Str_248);
        ;
        Str *_t_Str_249 = Str_lit("./src/core/vec.til:110:19", 25ULL);
        (void)_t_Str_249;
        panic(_t_Str_249, _va_Array_3);
        Str_delete(_t_Str_249, &(Bool){1});
    }
    ;
    U32 _t_U64_251 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_251;
    void *_t_v_252 = ptr_add(self->data, _t_U64_251);
    (void)_t_v_252;
    ;
    return _t_v_252;
}

void * Vec_pop(Vec * self) {
    (void)self;
    U32 _t_U32_259 = 0;
    (void)_t_U32_259;
    Bool _t_Bool_260 = U32_eq(self->count, _t_U32_259);
    (void)_t_Bool_260;
    ;
    if (_t_Bool_260) {
        Str *_t_Str_253 = Str_lit("Str", 3ULL);
        (void)_t_Str_253;
        U32 _t_U32_254 = 16;
        (void)_t_U32_254;
        U32 _t_U32_255 = 1;
        (void)_t_U32_255;
        Array *_va_Array_4 = Array_new(_t_Str_253, &_t_U32_254, &_t_U32_255);
        (void)_va_Array_4;
        Str_delete(_t_Str_253, &(Bool){1});
        ;
        ;
        U32 _t_U32_256 = 0;
        (void)_t_U32_256;
        Str *_t_Str_257 = Str_lit("Vec.pop: empty vec", 18ULL);
        (void)_t_Str_257;
        Array_set(_va_Array_4, &_t_U32_256, _t_Str_257);
        ;
        Str *_t_Str_258 = Str_lit("./src/core/vec.til:119:19", 25ULL);
        (void)_t_Str_258;
        panic(_t_Str_258, _va_Array_4);
        Str_delete(_t_Str_258, &(Bool){1});
    }
    ;
    U32 _t_U32_261 = 1;
    (void)_t_U32_261;
    U32 last = U32_sub(self->count, _t_U32_261);
    (void)last;
    ;
    void * out = malloc(self->elem_size);
    (void)out;
    U32 _t_U64_262 = U32_mul(last, self->elem_size);
    (void)_t_U64_262;
    void *_t_v_263 = ptr_add(self->data, _t_U64_262);
    (void)_t_v_263;
    memcpy(out, _t_v_263, self->elem_size);
    ;
    U32 _t_U32_264 = U32_clone(&last);
    (void)_t_U32_264;
    ;
    self->count = _t_U32_264;
    ;
    return out;
}

Vec * Vec_take_prefix(Vec * self, U32 * n) {
    (void)self;
    (void)n;
    Bool _t_Bool_284 = U32_gt(n, &self->count);
    (void)_t_Bool_284;
    if (_t_Bool_284) {
        Str *_t_Str_265 = Str_lit("Str", 3ULL);
        (void)_t_Str_265;
        U32 _t_U32_266 = 16;
        (void)_t_U32_266;
        U32 _t_U32_267 = 5;
        (void)_t_U32_267;
        Array *_va_Array_5 = Array_new(_t_Str_265, &_t_U32_266, &_t_U32_267);
        (void)_va_Array_5;
        Str_delete(_t_Str_265, &(Bool){1});
        ;
        ;
        U32 _t_U32_268 = 0;
        (void)_t_U32_268;
        Str *_t_Str_269 = Str_lit("Vec.take_prefix: count ", 23ULL);
        (void)_t_Str_269;
        Array_set(_va_Array_5, &_t_U32_268, _t_Str_269);
        ;
        U32 _t_U32_270 = 1;
        (void)_t_U32_270;
        Str *_t_Str_271 = U32_to_str(n);
        (void)_t_Str_271;
        Array_set(_va_Array_5, &_t_U32_270, _t_Str_271);
        ;
        U32 _t_U32_272 = 2;
        (void)_t_U32_272;
        Str *_t_Str_273 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_273;
        Array_set(_va_Array_5, &_t_U32_272, _t_Str_273);
        ;
        U32 _t_U32_274 = 3;
        (void)_t_U32_274;
        Str *_t_Str_275 = U32_to_str(&self->count);
        (void)_t_Str_275;
        Array_set(_va_Array_5, &_t_U32_274, _t_Str_275);
        ;
        U32 _t_U32_276 = 4;
        (void)_t_U32_276;
        Str *_t_Str_277 = Str_lit(")", 1ULL);
        (void)_t_Str_277;
        Array_set(_va_Array_5, &_t_U32_276, _t_Str_277);
        ;
        Str *_t_Str_278 = Str_lit("./src/core/vec.til:132:19", 25ULL);
        (void)_t_Str_278;
        panic(_t_Str_278, _va_Array_5);
        Str_delete(_t_Str_278, &(Bool){1});
    }
    ;
    U32 prefix_cap = 1;
    (void)prefix_cap;
    U32 _t_U32_285 = 0;
    (void)_t_U32_285;
    Bool _t_Bool_286 = U32_gt(n, &_t_U32_285);
    (void)_t_Bool_286;
    ;
    if (_t_Bool_286) {
        U32 _t_U32_279 = U32_clone(n);
        (void)_t_U32_279;
        prefix_cap = _t_U32_279;
        ;
    }
    ;
    U32 _t_U64_287 = U32_mul(prefix_cap, self->elem_size);
    (void)_t_U64_287;
    void * prefix_data = malloc(_t_U64_287);
    (void)prefix_data;
    ;
    U32 _t_U32_288 = 0;
    (void)_t_U32_288;
    Bool _t_Bool_289 = U32_gt(n, &_t_U32_288);
    (void)_t_Bool_289;
    ;
    if (_t_Bool_289) {
        U32 _t_U64_280 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_280;
        memcpy(prefix_data, self->data, _t_U64_280);
        ;
    }
    ;
    U32 tail_count = U32_sub(self->count, DEREF(n));
    (void)tail_count;
    U32 _t_U32_290 = 0;
    (void)_t_U32_290;
    Bool _t_Bool_291 = U32_gt(&tail_count, &_t_U32_290);
    (void)_t_Bool_291;
    ;
    if (_t_Bool_291) {
        U32 _t_U64_281 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_281;
        void *_t_v_282 = ptr_add(self->data, _t_U64_281);
        (void)_t_v_282;
        U32 _t_U64_283 = U32_mul(tail_count, self->elem_size);
        (void)_t_U64_283;
        memmove(self->data, _t_v_282, _t_U64_283);
        ;
        ;
    }
    ;
    U32 _t_U32_292 = U32_clone(&tail_count);
    (void)_t_U32_292;
    ;
    self->count = _t_U32_292;
    ;
    Vec *_t_Vec_293 = malloc(sizeof(Vec));
    _t_Vec_293->data = prefix_data;
    _t_Vec_293->count = DEREF(n);
    _t_Vec_293->cap = prefix_cap;
    _t_Vec_293->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_293->elem_type = *_ca; free(_ca); }
    _t_Vec_293->elem_clone = (void *)self->elem_clone;
    _t_Vec_293->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_293;
    ;
    return _t_Vec_293;
}

void Vec_set(Vec * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_308 = U32_gte(i, &self->count);
    (void)_t_Bool_308;
    if (_t_Bool_308) {
        Str *_t_Str_294 = Str_lit("Str", 3ULL);
        (void)_t_Str_294;
        U32 _t_U32_295 = 16;
        (void)_t_U32_295;
        U32 _t_U32_296 = 5;
        (void)_t_U32_296;
        Array *_va_Array_6 = Array_new(_t_Str_294, &_t_U32_295, &_t_U32_296);
        (void)_va_Array_6;
        Str_delete(_t_Str_294, &(Bool){1});
        ;
        ;
        U32 _t_U32_297 = 0;
        (void)_t_U32_297;
        Str *_t_Str_298 = Str_lit("Vec.set: index ", 15ULL);
        (void)_t_Str_298;
        Array_set(_va_Array_6, &_t_U32_297, _t_Str_298);
        ;
        U32 _t_U32_299 = 1;
        (void)_t_U32_299;
        Str *_t_Str_300 = U32_to_str(i);
        (void)_t_Str_300;
        Array_set(_va_Array_6, &_t_U32_299, _t_Str_300);
        ;
        U32 _t_U32_301 = 2;
        (void)_t_U32_301;
        Str *_t_Str_302 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_302;
        Array_set(_va_Array_6, &_t_U32_301, _t_Str_302);
        ;
        U32 _t_U32_303 = 3;
        (void)_t_U32_303;
        Str *_t_Str_304 = U32_to_str(&self->count);
        (void)_t_Str_304;
        Array_set(_va_Array_6, &_t_U32_303, _t_Str_304);
        ;
        U32 _t_U32_305 = 4;
        (void)_t_U32_305;
        Str *_t_Str_306 = Str_lit(")", 1ULL);
        (void)_t_Str_306;
        Array_set(_va_Array_6, &_t_U32_305, _t_Str_306);
        ;
        Str *_t_Str_307 = Str_lit("./src/core/vec.til:156:19", 25ULL);
        (void)_t_Str_307;
        panic(_t_Str_307, _va_Array_6);
        Str_delete(_t_Str_307, &(Bool){1});
    }
    ;
    U32 _t_U64_309 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_309;
    void *_t_v_310 = ptr_add(self->data, _t_U64_309);
    (void)_t_v_310;
    memcpy(_t_v_310, val, self->elem_size);
    ;
    free(val);
}

void Vec_push_take(Vec * self, Vec * src, U32 i) {
    (void)self;
    (void)src;
    (void)i;
    Bool _t_Bool_335 = U32_gte(&i, &src->count);
    (void)_t_Bool_335;
    if (_t_Bool_335) {
        Str *_t_Str_311 = Str_lit("Str", 3ULL);
        (void)_t_Str_311;
        U32 _t_U32_312 = 16;
        (void)_t_U32_312;
        U32 _t_U32_313 = 5;
        (void)_t_U32_313;
        Array *_va_Array_7 = Array_new(_t_Str_311, &_t_U32_312, &_t_U32_313);
        (void)_va_Array_7;
        Str_delete(_t_Str_311, &(Bool){1});
        ;
        ;
        U32 _t_U32_314 = 0;
        (void)_t_U32_314;
        Str *_t_Str_315 = Str_lit("Vec.push_take: index ", 21ULL);
        (void)_t_Str_315;
        Array_set(_va_Array_7, &_t_U32_314, _t_Str_315);
        ;
        U32 _t_U32_316 = 1;
        (void)_t_U32_316;
        Str *_t_Str_317 = U32_to_str(&i);
        (void)_t_Str_317;
        Array_set(_va_Array_7, &_t_U32_316, _t_Str_317);
        ;
        U32 _t_U32_318 = 2;
        (void)_t_U32_318;
        Str *_t_Str_319 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_319;
        Array_set(_va_Array_7, &_t_U32_318, _t_Str_319);
        ;
        U32 _t_U32_320 = 3;
        (void)_t_U32_320;
        Str *_t_Str_321 = U32_to_str(&src->count);
        (void)_t_Str_321;
        Array_set(_va_Array_7, &_t_U32_320, _t_Str_321);
        ;
        U32 _t_U32_322 = 4;
        (void)_t_U32_322;
        Str *_t_Str_323 = Str_lit(")", 1ULL);
        (void)_t_Str_323;
        Array_set(_va_Array_7, &_t_U32_322, _t_Str_323);
        ;
        Str *_t_Str_324 = Str_lit("./src/core/vec.til:167:19", 25ULL);
        (void)_t_Str_324;
        panic(_t_Str_324, _va_Array_7);
        Str_delete(_t_Str_324, &(Bool){1});
    }
    ;
    Bool _t_Bool_336 = U32_eq(self->elem_size, src->elem_size);
    (void)_t_Bool_336;
    Bool _t_Bool_337 = Str_eq(&self->elem_type, &src->elem_type);
    (void)_t_Bool_337;
    Bool _t_Bool_338 = not(_t_Bool_336);
    (void)_t_Bool_338;
    ;
    Bool _t_Bool_339 = not(_t_Bool_337);
    (void)_t_Bool_339;
    ;
    Bool _t_Bool_340 = or(_t_Bool_338, _t_Bool_339);
    (void)_t_Bool_340;
    ;
    ;
    if (_t_Bool_340) {
        Str *_t_Str_325 = Str_lit("Str", 3ULL);
        (void)_t_Str_325;
        U32 _t_U32_326 = 16;
        (void)_t_U32_326;
        U32 _t_U32_327 = 1;
        (void)_t_U32_327;
        Array *_va_Array_8 = Array_new(_t_Str_325, &_t_U32_326, &_t_U32_327);
        (void)_va_Array_8;
        Str_delete(_t_Str_325, &(Bool){1});
        ;
        ;
        U32 _t_U32_328 = 0;
        (void)_t_U32_328;
        Str *_t_Str_329 = Str_lit("Vec.push_take: incompatible vecs", 32ULL);
        (void)_t_Str_329;
        Array_set(_va_Array_8, &_t_U32_328, _t_Str_329);
        ;
        Str *_t_Str_330 = Str_lit("./src/core/vec.til:170:19", 25ULL);
        (void)_t_Str_330;
        panic(_t_Str_330, _va_Array_8);
        Str_delete(_t_Str_330, &(Bool){1});
    }
    ;
    Bool _t_Bool_341 = U32_eq(self->count, self->cap);
    (void)_t_Bool_341;
    if (_t_Bool_341) {
        U32 _t_U32_331 = 2;
        (void)_t_U32_331;
        U32 new_cap = U32_mul(self->cap, _t_U32_331);
        (void)new_cap;
        ;
        U32 _t_U64_332 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_332;
        void * _t_v_333 = realloc(self->data, _t_U64_332);
        (void)_t_v_333;
        ;
        self->data = _t_v_333;
        U32 _t_U32_334 = U32_clone(&new_cap);
        (void)_t_U32_334;
        ;
        self->cap = _t_U32_334;
        ;
    }
    ;
    U32 _t_U64_342 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_342;
    U32 _t_U64_343 = U32_mul(i, src->elem_size);
    (void)_t_U64_343;
    void *_t_v_344 = ptr_add(self->data, _t_U64_342);
    (void)_t_v_344;
    void *_t_v_345 = ptr_add(src->data, _t_U64_343);
    (void)_t_v_345;
    memcpy(_t_v_344, _t_v_345, self->elem_size);
    ;
    ;
    U32 _t_U64_346 = U32_mul(i, src->elem_size);
    (void)_t_U64_346;
    void *_t_v_347 = ptr_add(src->data, _t_U64_346);
    (void)_t_v_347;
    I32 _t_I32_348 = 0;
    (void)_t_I32_348;
    memset(_t_v_347, _t_I32_348, src->elem_size);
    ;
    ;
    U32 _t_U32_349 = 1;
    (void)_t_U32_349;
    U32 _t_U32_350 = U32_add(self->count, _t_U32_349);
    (void)_t_U32_350;
    ;
    self->count = _t_U32_350;
    ;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_362 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_362;
    Str *_t_Str_363 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_363;
    Bool _t_Bool_364 = Str_eq(&self->elem_type, _t_Str_363);
    (void)_t_Bool_364;
    Str_delete(_t_Str_363, &(Bool){1});
    Bool _t_Bool_365 = not(_t_Bool_362);
    (void)_t_Bool_365;
    ;
    Bool _t_Bool_366 = not(_t_Bool_364);
    (void)_t_Bool_366;
    ;
    Bool _t_Bool_367 = and(_t_Bool_365, _t_Bool_366);
    (void)_t_Bool_367;
    ;
    ;
    if (_t_Bool_367) {
        {
            U32 _re_U32_351 = self->count;
            (void)_re_U32_351;
            U32 _rc_U32_351 = 0;
            (void)_rc_U32_351;
            Bool _t_Bool_360 = U32_lte(&_rc_U32_351, &_re_U32_351);
            (void)_t_Bool_360;
            if (_t_Bool_360) {
                while (1) {
                    Bool _wcond_Bool_352 = U32_lt(&_rc_U32_351, &_re_U32_351);
                    (void)_wcond_Bool_352;
                    if (_wcond_Bool_352) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_351);
                    (void)i;
                    U32_inc(&_rc_U32_351);
                    U32 _t_U64_353 = U32_mul(i, self->elem_size);
                    (void)_t_U64_353;
                    ;
                    void *_t_v_354 = ptr_add(self->data, _t_U64_353);
                    (void)_t_v_354;
                    Bool _t_Bool_355 = 0;
                    (void)_t_Bool_355;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_354, &_t_Bool_355);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_356 = U32_gt(&_rc_U32_351, &_re_U32_351);
                    (void)_wcond_Bool_356;
                    if (_wcond_Bool_356) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_351);
                    (void)i;
                    U32_dec(&_rc_U32_351);
                    U32 _t_U64_357 = U32_mul(i, self->elem_size);
                    (void)_t_U64_357;
                    ;
                    void *_t_v_358 = ptr_add(self->data, _t_U64_357);
                    (void)_t_v_358;
                    Bool _t_Bool_359 = 0;
                    (void)_t_Bool_359;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_358, &_t_Bool_359);
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
    Bool _t_Bool_368 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_368;
    Bool _t_Bool_369 = not(_t_Bool_368);
    (void)_t_Bool_369;
    ;
    if (_t_Bool_369) {
        Bool _t_Bool_361 = 0;
        (void)_t_Bool_361;
        Str_delete(&self->elem_type, &_t_Bool_361);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U32 _t_U64_383 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_383;
    void * new_data = malloc(_t_U64_383);
    (void)new_data;
    ;
    Bool _t_Bool_384 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_384;
    Str *_t_Str_385 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_385;
    Bool _t_Bool_386 = Str_eq(&self->elem_type, _t_Str_385);
    (void)_t_Bool_386;
    Str_delete(_t_Str_385, &(Bool){1});
    Bool _t_Bool_387 = not(_t_Bool_384);
    (void)_t_Bool_387;
    ;
    Bool _t_Bool_388 = not(_t_Bool_386);
    (void)_t_Bool_388;
    ;
    Bool _t_Bool_389 = and(_t_Bool_387, _t_Bool_388);
    (void)_t_Bool_389;
    ;
    ;
    if (_t_Bool_389) {
        {
            U32 _re_U32_370 = self->count;
            (void)_re_U32_370;
            U32 _rc_U32_370 = 0;
            (void)_rc_U32_370;
            Bool _t_Bool_381 = U32_lte(&_rc_U32_370, &_re_U32_370);
            (void)_t_Bool_381;
            if (_t_Bool_381) {
                while (1) {
                    Bool _wcond_Bool_371 = U32_lt(&_rc_U32_370, &_re_U32_370);
                    (void)_wcond_Bool_371;
                    if (_wcond_Bool_371) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_370);
                    (void)i;
                    U32_inc(&_rc_U32_370);
                    U32 _t_U64_372 = U32_mul(i, self->elem_size);
                    (void)_t_U64_372;
                    void *_t_v_373 = ptr_add(self->data, _t_U64_372);
                    (void)_t_v_373;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_373);
                    (void)cloned;
                    ;
                    U32 _t_U64_374 = U32_mul(i, self->elem_size);
                    (void)_t_U64_374;
                    ;
                    void *_t_v_375 = ptr_add(new_data, _t_U64_374);
                    (void)_t_v_375;
                    memcpy(_t_v_375, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_376 = U32_gt(&_rc_U32_370, &_re_U32_370);
                    (void)_wcond_Bool_376;
                    if (_wcond_Bool_376) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_370);
                    (void)i;
                    U32_dec(&_rc_U32_370);
                    U32 _t_U64_377 = U32_mul(i, self->elem_size);
                    (void)_t_U64_377;
                    void *_t_v_378 = ptr_add(self->data, _t_U64_377);
                    (void)_t_v_378;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_378);
                    (void)cloned;
                    ;
                    U32 _t_U64_379 = U32_mul(i, self->elem_size);
                    (void)_t_U64_379;
                    ;
                    void *_t_v_380 = ptr_add(new_data, _t_U64_379);
                    (void)_t_v_380;
                    memcpy(_t_v_380, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            }
            ;
            ;
            ;
        }
    } else {
        U32 _t_U64_382 = U32_mul(self->count, self->elem_size);
        (void)_t_U64_382;
        memcpy(new_data, self->data, _t_U64_382);
        ;
    }
    ;
    Vec *_t_Vec_390 = malloc(sizeof(Vec));
    _t_Vec_390->data = new_data;
    _t_Vec_390->count = self->count;
    _t_Vec_390->cap = self->cap;
    _t_Vec_390->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_390->elem_type = *_ca; free(_ca); }
    _t_Vec_390->elem_clone = (void *)self->elem_clone;
    _t_Vec_390->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_390;
    return _t_Vec_390;
}

U32 Vec_size(void) {
    I64 _t_I64_391 = 56;
    (void)_t_I64_391;
    return _t_I64_391;
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    (void)total;
    {
        Array *_fc_Array_392 = parts;
        (void)_fc_Array_392;
        U32 _fi_USize_392 = 0;
        (void)_fi_USize_392;
        while (1) {
            U32 _t_U32_394; { U32 *_hp = (U32 *)Array_len(_fc_Array_392); _t_U32_394 = *_hp; free(_hp); }
            (void)_t_U32_394;
            Bool _wcond_Bool_393 = U32_lt(&_fi_USize_392, &_t_U32_394);
            (void)_wcond_Bool_393;
            ;
            if (_wcond_Bool_393) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_392, &_fi_USize_392);
            (void)s;
            U32 _t_U32_395 = 1;
            (void)_t_U32_395;
            U32 _t_U32_396 = U32_add(_fi_USize_392, _t_U32_395);
            (void)_t_U32_396;
            ;
            _fi_USize_392 = _t_U32_396;
            ;
            U32 _t_U32_397 = Str_len(s);
            (void)_t_U32_397;
            U32 _t_U32_398 = U32_add(total, _t_U32_397);
            (void)_t_U32_398;
            ;
            total = _t_U32_398;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    (void)out;
    ;
    {
        Array *_fc_Array_399 = parts;
        (void)_fc_Array_399;
        U32 _fi_USize_399 = 0;
        (void)_fi_USize_399;
        while (1) {
            U32 _t_U32_401; { U32 *_hp = (U32 *)Array_len(_fc_Array_399); _t_U32_401 = *_hp; free(_hp); }
            (void)_t_U32_401;
            Bool _wcond_Bool_400 = U32_lt(&_fi_USize_399, &_t_U32_401);
            (void)_wcond_Bool_400;
            ;
            if (_wcond_Bool_400) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_399, &_fi_USize_399);
            (void)s;
            U32 _t_U32_402 = 1;
            (void)_t_U32_402;
            U32 _t_U32_403 = U32_add(_fi_USize_399, _t_U32_402);
            (void)_t_U32_403;
            ;
            _fi_USize_399 = _t_U32_403;
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
    Bool _t_Bool_410 = U32_gte(i, &self->count);
    (void)_t_Bool_410;
    if (_t_Bool_410) {
        Str *_t_Str_404 = Str_lit("Str", 3ULL);
        (void)_t_Str_404;
        U32 _t_U32_405 = 16;
        (void)_t_U32_405;
        U32 _t_U32_406 = 1;
        (void)_t_U32_406;
        Array *_va_Array_9 = Array_new(_t_Str_404, &_t_U32_405, &_t_U32_406);
        (void)_va_Array_9;
        Str_delete(_t_Str_404, &(Bool){1});
        ;
        ;
        U32 _t_U32_407 = 0;
        (void)_t_U32_407;
        Str *_t_Str_408 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t_Str_408;
        Array_set(_va_Array_9, &_t_U32_407, _t_Str_408);
        ;
        Str *_t_Str_409 = Str_lit("./src/core/str.til:39:19", 24ULL);
        (void)_t_Str_409;
        panic(_t_Str_409, _va_Array_9);
        Str_delete(_t_Str_409, &(Bool){1});
    }
    ;
    void *_t_v_411 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_411;
    return _t_v_411;
}

U8 * Str_byte_at(Str * self, U32 * i) {
    (void)self;
    (void)i;
    void *_t_v_412 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_412;
    return _t_v_412;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    (void)min_len;
    Bool _t_Bool_421 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_421;
    if (_t_Bool_421) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_413 = U32_clone(&min_len);
        (void)_re_U32_413;
        U32 _rc_U32_413 = 0;
        (void)_rc_U32_413;
        Bool _t_Bool_420 = U32_lte(&_rc_U32_413, &_re_U32_413);
        (void)_t_Bool_420;
        if (_t_Bool_420) {
            while (1) {
                Bool _wcond_Bool_414 = U32_lt(&_rc_U32_413, &_re_U32_413);
                (void)_wcond_Bool_414;
                if (_wcond_Bool_414) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_413);
                (void)i;
                U32_inc(&_rc_U32_413);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_415 = 0;
                (void)_t_I64_415;
                Bool _t_Bool_416 = I64_neq(&c, &_t_I64_415);
                (void)_t_Bool_416;
                ;
                if (_t_Bool_416) {
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
                Bool _wcond_Bool_417 = U32_gt(&_rc_U32_413, &_re_U32_413);
                (void)_wcond_Bool_417;
                if (_wcond_Bool_417) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_413);
                (void)i;
                U32_dec(&_rc_U32_413);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_418 = 0;
                (void)_t_I64_418;
                Bool _t_Bool_419 = I64_neq(&c, &_t_I64_418);
                (void)_t_Bool_419;
                ;
                if (_t_Bool_419) {
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
    I64 _t_I64_422 = U32_cmp(a->count, b->count);
    (void)_t_I64_422;
    return _t_I64_422;
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_423 = U32_add(a->count, b->count);
    (void)_t_U32_423;
    Str *out = Str_with_capacity(&_t_U32_423);
    (void)out;
    ;
    Str_push_str(out, a);
    Str_push_str(out, b);
    return out;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_424 = 1;
    (void)_t_U32_424;
    U32 _t_U64_425 = U32_add(DEREF(n), _t_U32_424);
    (void)_t_U64_425;
    ;
    void * buf = malloc(_t_U64_425);
    (void)buf;
    ;
    I32 _t_I32_426 = 0;
    (void)_t_I32_426;
    U64 _t_U64_427 = 1;
    (void)_t_U64_427;
    memset(buf, _t_I32_426, _t_U64_427);
    ;
    ;
    I64 _t_I64_428 = 0;
    (void)_t_I64_428;
    Str *_t_Str_429 = malloc(sizeof(Str));
    _t_Str_429->c_str = buf;
    _t_Str_429->count = _t_I64_428;
    _t_Str_429->cap = DEREF(n);
    (void)_t_Str_429;
    ;
    return _t_Str_429;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_442 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_442;
    if (_t_Bool_442) {
        Str *_t_Str_430 = Str_lit("Str", 3ULL);
        (void)_t_Str_430;
        U32 _t_U32_431 = 16;
        (void)_t_U32_431;
        U32 _t_U32_432 = 1;
        (void)_t_U32_432;
        Array *_va_Array_10 = Array_new(_t_Str_430, &_t_U32_431, &_t_U32_432);
        (void)_va_Array_10;
        Str_delete(_t_Str_430, &(Bool){1});
        ;
        ;
        U32 _t_U32_433 = 0;
        (void)_t_U32_433;
        Str *_t_Str_434 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t_Str_434;
        Array_set(_va_Array_10, &_t_U32_433, _t_Str_434);
        ;
        Str *_t_Str_435 = Str_lit("./src/core/str.til:82:19", 24ULL);
        (void)_t_Str_435;
        panic(_t_Str_435, _va_Array_10);
        Str_delete(_t_Str_435, &(Bool){1});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    (void)new_len;
    Bool _t_Bool_443 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_443;
    if (_t_Bool_443) {
        Str *_t_Str_436 = Str_lit("Str", 3ULL);
        (void)_t_Str_436;
        U32 _t_U32_437 = 16;
        (void)_t_U32_437;
        U32 _t_U32_438 = 1;
        (void)_t_U32_438;
        Array *_va_Array_11 = Array_new(_t_Str_436, &_t_U32_437, &_t_U32_438);
        (void)_va_Array_11;
        Str_delete(_t_Str_436, &(Bool){1});
        ;
        ;
        U32 _t_U32_439 = 0;
        (void)_t_U32_439;
        Str *_t_Str_440 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t_Str_440;
        Array_set(_va_Array_11, &_t_U32_439, _t_Str_440);
        ;
        Str *_t_Str_441 = Str_lit("./src/core/str.til:86:19", 24ULL);
        (void)_t_Str_441;
        panic(_t_Str_441, _va_Array_11);
        Str_delete(_t_Str_441, &(Bool){1});
    }
    ;
    void *_t_v_444 = ptr_add(self->c_str, self->count);
    (void)_t_v_444;
    memcpy(_t_v_444, s->c_str, s->count);
    U32 _t_U32_445 = U32_clone(&new_len);
    (void)_t_U32_445;
    self->count = _t_U32_445;
    ;
    void *_t_v_446 = ptr_add(self->c_str, new_len);
    (void)_t_v_446;
    I32 _t_I32_447 = 0;
    (void)_t_I32_447;
    U64 _t_U64_448 = 1;
    (void)_t_U64_448;
    memset(_t_v_446, _t_I32_447, _t_U64_448);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_449 = 1;
    (void)_t_U32_449;
    U32 _t_U64_450 = U32_add(val->count, _t_U32_449);
    (void)_t_U64_450;
    ;
    void * new_data = malloc(_t_U64_450);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_451 = ptr_add(new_data, val->count);
    (void)_t_v_451;
    I32 _t_I32_452 = 0;
    (void)_t_I32_452;
    U64 _t_U64_453 = 1;
    (void)_t_U64_453;
    memset(_t_v_451, _t_I32_452, _t_U64_453);
    ;
    ;
    Str *_t_Str_454 = malloc(sizeof(Str));
    _t_Str_454->c_str = new_data;
    _t_Str_454->count = val->count;
    _t_Str_454->cap = val->count;
    (void)_t_Str_454;
    return _t_Str_454;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_455 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_455;
    if (_t_Bool_455) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t_Str_456 = Str_clone(val);
    (void)_t_Str_456;
    return _t_Str_456;
}

Str * Str_substr(Str * s, U32 * start, U32 * n) {
    (void)s;
    (void)start;
    (void)n;
    U32 st = U32_clone(start);
    (void)st;
    U32 ln = U32_clone(n);
    (void)ln;
    Bool _t_Bool_458 = U32_gt(&st, &s->count);
    (void)_t_Bool_458;
    if (_t_Bool_458) {
        st = s->count;
    }
    ;
    U32 _t_U32_459 = U32_add(st, ln);
    (void)_t_U32_459;
    Bool _t_Bool_460 = U32_gt(&_t_U32_459, &s->count);
    (void)_t_Bool_460;
    ;
    if (_t_Bool_460) {
        U32 _t_U32_457 = U32_sub(s->count, st);
        (void)_t_U32_457;
        ln = _t_U32_457;
        ;
    }
    ;
    void *_t_v_461 = ptr_add(s->c_str, st);
    (void)_t_v_461;
    Str *_t_Str_462 = malloc(sizeof(Str));
    _t_Str_462->c_str = _t_v_461;
    _t_Str_462->count = ln;
    _t_Str_462->cap = CAP_VIEW;
    (void)_t_Str_462;
    ;
    ;
    return _t_Str_462;
}

Bool Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_493 = 0;
    (void)_t_U32_493;
    Bool _t_Bool_494 = U32_eq(b->count, _t_U32_493);
    (void)_t_Bool_494;
    ;
    if (_t_Bool_494) {
        Bool _t_Bool_463 = 1;
        (void)_t_Bool_463;
        ;
        return _t_Bool_463;
    }
    ;
    Bool _t_Bool_495 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_495;
    if (_t_Bool_495) {
        Bool _t_Bool_464 = 0;
        (void)_t_Bool_464;
        ;
        return _t_Bool_464;
    }
    ;
    {
        U32 _t_U32_490 = U32_sub(a->count, b->count);
        (void)_t_U32_490;
        U32 _t_U32_491 = 1;
        (void)_t_U32_491;
        U32 _re_U32_465 = U32_add(_t_U32_490, _t_U32_491);
        (void)_re_U32_465;
        ;
        ;
        U32 _rc_U32_465 = 0;
        (void)_rc_U32_465;
        Bool _t_Bool_492 = U32_lte(&_rc_U32_465, &_re_U32_465);
        (void)_t_Bool_492;
        if (_t_Bool_492) {
            while (1) {
                Bool _wcond_Bool_466 = U32_lt(&_rc_U32_465, &_re_U32_465);
                (void)_wcond_Bool_466;
                if (_wcond_Bool_466) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_465);
                (void)i;
                U32_inc(&_rc_U32_465);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_467 = b->count;
                    (void)_re_U32_467;
                    U32 _rc_U32_467 = 0;
                    (void)_rc_U32_467;
                    Bool _t_Bool_476 = U32_lte(&_rc_U32_467, &_re_U32_467);
                    (void)_t_Bool_476;
                    if (_t_Bool_476) {
                        while (1) {
                            Bool _wcond_Bool_468 = U32_lt(&_rc_U32_467, &_re_U32_467);
                            (void)_wcond_Bool_468;
                            if (_wcond_Bool_468) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_467);
                            (void)j;
                            U32_inc(&_rc_U32_467);
                            U32 _t_U32_470 = U32_add(i, j);
                            (void)_t_U32_470;
                            U8 *ac = Str_get(a, &_t_U32_470);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_471 = U8_neq(ac, bc);
                            (void)_t_Bool_471;
                            ;
                            ;
                            if (_t_Bool_471) {
                                Bool _t_Bool_469 = 0;
                                (void)_t_Bool_469;
                                found = _t_Bool_469;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_472 = U32_gt(&_rc_U32_467, &_re_U32_467);
                            (void)_wcond_Bool_472;
                            if (_wcond_Bool_472) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_467);
                            (void)j;
                            U32_dec(&_rc_U32_467);
                            U32 _t_U32_474 = U32_add(i, j);
                            (void)_t_U32_474;
                            U8 *ac = Str_get(a, &_t_U32_474);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_475 = U8_neq(ac, bc);
                            (void)_t_Bool_475;
                            ;
                            ;
                            if (_t_Bool_475) {
                                Bool _t_Bool_473 = 0;
                                (void)_t_Bool_473;
                                found = _t_Bool_473;
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
                    Bool _t_Bool_477 = 1;
                    (void)_t_Bool_477;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_477;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_478 = U32_gt(&_rc_U32_465, &_re_U32_465);
                (void)_wcond_Bool_478;
                if (_wcond_Bool_478) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_465);
                (void)i;
                U32_dec(&_rc_U32_465);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_479 = b->count;
                    (void)_re_U32_479;
                    U32 _rc_U32_479 = 0;
                    (void)_rc_U32_479;
                    Bool _t_Bool_488 = U32_lte(&_rc_U32_479, &_re_U32_479);
                    (void)_t_Bool_488;
                    if (_t_Bool_488) {
                        while (1) {
                            Bool _wcond_Bool_480 = U32_lt(&_rc_U32_479, &_re_U32_479);
                            (void)_wcond_Bool_480;
                            if (_wcond_Bool_480) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_479);
                            (void)j;
                            U32_inc(&_rc_U32_479);
                            U32 _t_U32_482 = U32_add(i, j);
                            (void)_t_U32_482;
                            U8 *ac = Str_get(a, &_t_U32_482);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_483 = U8_neq(ac, bc);
                            (void)_t_Bool_483;
                            ;
                            ;
                            if (_t_Bool_483) {
                                Bool _t_Bool_481 = 0;
                                (void)_t_Bool_481;
                                found = _t_Bool_481;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_484 = U32_gt(&_rc_U32_479, &_re_U32_479);
                            (void)_wcond_Bool_484;
                            if (_wcond_Bool_484) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_479);
                            (void)j;
                            U32_dec(&_rc_U32_479);
                            U32 _t_U32_486 = U32_add(i, j);
                            (void)_t_U32_486;
                            U8 *ac = Str_get(a, &_t_U32_486);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_487 = U8_neq(ac, bc);
                            (void)_t_Bool_487;
                            ;
                            ;
                            if (_t_Bool_487) {
                                Bool _t_Bool_485 = 0;
                                (void)_t_Bool_485;
                                found = _t_Bool_485;
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
                    Bool _t_Bool_489 = 1;
                    (void)_t_Bool_489;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_489;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_496 = 0;
    (void)_t_Bool_496;
    return _t_Bool_496;
}

Bool Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_506 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_506;
    if (_t_Bool_506) {
        Bool _t_Bool_497 = 0;
        (void)_t_Bool_497;
        ;
        return _t_Bool_497;
    }
    ;
    {
        U32 _re_U32_498 = b->count;
        (void)_re_U32_498;
        U32 _rc_U32_498 = 0;
        (void)_rc_U32_498;
        Bool _t_Bool_505 = U32_lte(&_rc_U32_498, &_re_U32_498);
        (void)_t_Bool_505;
        if (_t_Bool_505) {
            while (1) {
                Bool _wcond_Bool_499 = U32_lt(&_rc_U32_498, &_re_U32_498);
                (void)_wcond_Bool_499;
                if (_wcond_Bool_499) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_498);
                (void)i;
                U32_inc(&_rc_U32_498);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_501 = U8_neq(ac, bc);
                (void)_t_Bool_501;
                ;
                if (_t_Bool_501) {
                    Bool _t_Bool_500 = 0;
                    (void)_t_Bool_500;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_500;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_502 = U32_gt(&_rc_U32_498, &_re_U32_498);
                (void)_wcond_Bool_502;
                if (_wcond_Bool_502) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_498);
                (void)i;
                U32_dec(&_rc_U32_498);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_504 = U8_neq(ac, bc);
                (void)_t_Bool_504;
                ;
                if (_t_Bool_504) {
                    Bool _t_Bool_503 = 0;
                    (void)_t_Bool_503;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_503;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_507 = 1;
    (void)_t_Bool_507;
    return _t_Bool_507;
}

Bool Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_519 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_519;
    if (_t_Bool_519) {
        Bool _t_Bool_508 = 0;
        (void)_t_Bool_508;
        ;
        return _t_Bool_508;
    }
    ;
    U32 offset = U32_sub(a->count, b->count);
    (void)offset;
    {
        U32 _re_U32_509 = b->count;
        (void)_re_U32_509;
        U32 _rc_U32_509 = 0;
        (void)_rc_U32_509;
        Bool _t_Bool_518 = U32_lte(&_rc_U32_509, &_re_U32_509);
        (void)_t_Bool_518;
        if (_t_Bool_518) {
            while (1) {
                Bool _wcond_Bool_510 = U32_lt(&_rc_U32_509, &_re_U32_509);
                (void)_wcond_Bool_510;
                if (_wcond_Bool_510) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_509);
                (void)i;
                U32_inc(&_rc_U32_509);
                U32 _t_U32_512 = U32_add(offset, i);
                (void)_t_U32_512;
                U8 *ac = Str_get(a, &_t_U32_512);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_513 = U8_neq(ac, bc);
                (void)_t_Bool_513;
                ;
                ;
                if (_t_Bool_513) {
                    Bool _t_Bool_511 = 0;
                    (void)_t_Bool_511;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_511;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_514 = U32_gt(&_rc_U32_509, &_re_U32_509);
                (void)_wcond_Bool_514;
                if (_wcond_Bool_514) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_509);
                (void)i;
                U32_dec(&_rc_U32_509);
                U32 _t_U32_516 = U32_add(offset, i);
                (void)_t_U32_516;
                U8 *ac = Str_get(a, &_t_U32_516);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_517 = U8_neq(ac, bc);
                (void)_t_Bool_517;
                ;
                ;
                if (_t_Bool_517) {
                    Bool _t_Bool_515 = 0;
                    (void)_t_Bool_515;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_515;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    Bool _t_Bool_520 = 1;
    (void)_t_Bool_520;
    return _t_Bool_520;
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_521 = 0;
    (void)_t_U32_521;
    Bool _t_Bool_522 = U32_eq(self->count, _t_U32_521);
    (void)_t_Bool_522;
    ;
    return _t_Bool_522;
}

I64 Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_557 = 0;
    (void)_t_U32_557;
    Bool _t_Bool_558 = U32_eq(needle->count, _t_U32_557);
    (void)_t_Bool_558;
    ;
    if (_t_Bool_558) {
        I64 _t_I64_523 = 0;
        (void)_t_I64_523;
        I64 _t_I64_524 = 1;
        (void)_t_I64_524;
        I64 _t_I64_525 = I64_sub(_t_I64_523, _t_I64_524);
        (void)_t_I64_525;
        ;
        ;
        ;
        return _t_I64_525;
    }
    ;
    Bool _t_Bool_559 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_559;
    if (_t_Bool_559) {
        I64 _t_I64_526 = 0;
        (void)_t_I64_526;
        I64 _t_I64_527 = 1;
        (void)_t_I64_527;
        I64 _t_I64_528 = I64_sub(_t_I64_526, _t_I64_527);
        (void)_t_I64_528;
        ;
        ;
        ;
        return _t_I64_528;
    }
    ;
    {
        U32 _t_U32_554 = U32_sub(self->count, needle->count);
        (void)_t_U32_554;
        U32 _t_U32_555 = 1;
        (void)_t_U32_555;
        U32 _re_U32_529 = U32_add(_t_U32_554, _t_U32_555);
        (void)_re_U32_529;
        ;
        ;
        U32 _rc_U32_529 = 0;
        (void)_rc_U32_529;
        Bool _t_Bool_556 = U32_lte(&_rc_U32_529, &_re_U32_529);
        (void)_t_Bool_556;
        if (_t_Bool_556) {
            while (1) {
                Bool _wcond_Bool_530 = U32_lt(&_rc_U32_529, &_re_U32_529);
                (void)_wcond_Bool_530;
                if (_wcond_Bool_530) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_529);
                (void)i;
                U32_inc(&_rc_U32_529);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_531 = needle->count;
                    (void)_re_U32_531;
                    U32 _rc_U32_531 = 0;
                    (void)_rc_U32_531;
                    Bool _t_Bool_540 = U32_lte(&_rc_U32_531, &_re_U32_531);
                    (void)_t_Bool_540;
                    if (_t_Bool_540) {
                        while (1) {
                            Bool _wcond_Bool_532 = U32_lt(&_rc_U32_531, &_re_U32_531);
                            (void)_wcond_Bool_532;
                            if (_wcond_Bool_532) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_531);
                            (void)j;
                            U32_inc(&_rc_U32_531);
                            U32 _t_U32_534 = U32_add(i, j);
                            (void)_t_U32_534;
                            U8 *ac = Str_get(self, &_t_U32_534);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_535 = U8_neq(ac, bc);
                            (void)_t_Bool_535;
                            ;
                            ;
                            if (_t_Bool_535) {
                                Bool _t_Bool_533 = 0;
                                (void)_t_Bool_533;
                                found = _t_Bool_533;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_536 = U32_gt(&_rc_U32_531, &_re_U32_531);
                            (void)_wcond_Bool_536;
                            if (_wcond_Bool_536) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_531);
                            (void)j;
                            U32_dec(&_rc_U32_531);
                            U32 _t_U32_538 = U32_add(i, j);
                            (void)_t_U32_538;
                            U8 *ac = Str_get(self, &_t_U32_538);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_539 = U8_neq(ac, bc);
                            (void)_t_Bool_539;
                            ;
                            ;
                            if (_t_Bool_539) {
                                Bool _t_Bool_537 = 0;
                                (void)_t_Bool_537;
                                found = _t_Bool_537;
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
                    I64 _t_I64_541 = U32_to_i64(i);
                    (void)_t_I64_541;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_541;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_542 = U32_gt(&_rc_U32_529, &_re_U32_529);
                (void)_wcond_Bool_542;
                if (_wcond_Bool_542) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_529);
                (void)i;
                U32_dec(&_rc_U32_529);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_543 = needle->count;
                    (void)_re_U32_543;
                    U32 _rc_U32_543 = 0;
                    (void)_rc_U32_543;
                    Bool _t_Bool_552 = U32_lte(&_rc_U32_543, &_re_U32_543);
                    (void)_t_Bool_552;
                    if (_t_Bool_552) {
                        while (1) {
                            Bool _wcond_Bool_544 = U32_lt(&_rc_U32_543, &_re_U32_543);
                            (void)_wcond_Bool_544;
                            if (_wcond_Bool_544) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_543);
                            (void)j;
                            U32_inc(&_rc_U32_543);
                            U32 _t_U32_546 = U32_add(i, j);
                            (void)_t_U32_546;
                            U8 *ac = Str_get(self, &_t_U32_546);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_547 = U8_neq(ac, bc);
                            (void)_t_Bool_547;
                            ;
                            ;
                            if (_t_Bool_547) {
                                Bool _t_Bool_545 = 0;
                                (void)_t_Bool_545;
                                found = _t_Bool_545;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_548 = U32_gt(&_rc_U32_543, &_re_U32_543);
                            (void)_wcond_Bool_548;
                            if (_wcond_Bool_548) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_543);
                            (void)j;
                            U32_dec(&_rc_U32_543);
                            U32 _t_U32_550 = U32_add(i, j);
                            (void)_t_U32_550;
                            U8 *ac = Str_get(self, &_t_U32_550);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_551 = U8_neq(ac, bc);
                            (void)_t_Bool_551;
                            ;
                            ;
                            if (_t_Bool_551) {
                                Bool _t_Bool_549 = 0;
                                (void)_t_Bool_549;
                                found = _t_Bool_549;
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
                    I64 _t_I64_553 = U32_to_i64(i);
                    (void)_t_I64_553;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_553;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    I64 _t_I64_560 = 0;
    (void)_t_I64_560;
    I64 _t_I64_561 = 1;
    (void)_t_I64_561;
    I64 _t_I64_562 = I64_sub(_t_I64_560, _t_I64_561);
    (void)_t_I64_562;
    ;
    ;
    return _t_I64_562;
}

I64 Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_597 = 0;
    (void)_t_U32_597;
    Bool _t_Bool_598 = U32_eq(needle->count, _t_U32_597);
    (void)_t_Bool_598;
    ;
    if (_t_Bool_598) {
        I64 _t_I64_563 = 0;
        (void)_t_I64_563;
        I64 _t_I64_564 = 1;
        (void)_t_I64_564;
        I64 _t_I64_565 = I64_sub(_t_I64_563, _t_I64_564);
        (void)_t_I64_565;
        ;
        ;
        ;
        return _t_I64_565;
    }
    ;
    Bool _t_Bool_599 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_599;
    if (_t_Bool_599) {
        I64 _t_I64_566 = 0;
        (void)_t_I64_566;
        I64 _t_I64_567 = 1;
        (void)_t_I64_567;
        I64 _t_I64_568 = I64_sub(_t_I64_566, _t_I64_567);
        (void)_t_I64_568;
        ;
        ;
        ;
        return _t_I64_568;
    }
    ;
    I64 _t_I64_600 = 0;
    (void)_t_I64_600;
    I64 _t_I64_601 = 1;
    (void)_t_I64_601;
    I64 last = I64_sub(_t_I64_600, _t_I64_601);
    (void)last;
    ;
    ;
    {
        U32 _t_U32_594 = U32_sub(self->count, needle->count);
        (void)_t_U32_594;
        U32 _t_U32_595 = 1;
        (void)_t_U32_595;
        U32 _re_U32_569 = U32_add(_t_U32_594, _t_U32_595);
        (void)_re_U32_569;
        ;
        ;
        U32 _rc_U32_569 = 0;
        (void)_rc_U32_569;
        Bool _t_Bool_596 = U32_lte(&_rc_U32_569, &_re_U32_569);
        (void)_t_Bool_596;
        if (_t_Bool_596) {
            while (1) {
                Bool _wcond_Bool_570 = U32_lt(&_rc_U32_569, &_re_U32_569);
                (void)_wcond_Bool_570;
                if (_wcond_Bool_570) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_569);
                (void)i;
                U32_inc(&_rc_U32_569);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_571 = needle->count;
                    (void)_re_U32_571;
                    U32 _rc_U32_571 = 0;
                    (void)_rc_U32_571;
                    Bool _t_Bool_580 = U32_lte(&_rc_U32_571, &_re_U32_571);
                    (void)_t_Bool_580;
                    if (_t_Bool_580) {
                        while (1) {
                            Bool _wcond_Bool_572 = U32_lt(&_rc_U32_571, &_re_U32_571);
                            (void)_wcond_Bool_572;
                            if (_wcond_Bool_572) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_571);
                            (void)j;
                            U32_inc(&_rc_U32_571);
                            U32 _t_U32_574 = U32_add(i, j);
                            (void)_t_U32_574;
                            U8 *ac = Str_get(self, &_t_U32_574);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_575 = U8_neq(ac, bc);
                            (void)_t_Bool_575;
                            ;
                            ;
                            if (_t_Bool_575) {
                                Bool _t_Bool_573 = 0;
                                (void)_t_Bool_573;
                                found = _t_Bool_573;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_576 = U32_gt(&_rc_U32_571, &_re_U32_571);
                            (void)_wcond_Bool_576;
                            if (_wcond_Bool_576) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_571);
                            (void)j;
                            U32_dec(&_rc_U32_571);
                            U32 _t_U32_578 = U32_add(i, j);
                            (void)_t_U32_578;
                            U8 *ac = Str_get(self, &_t_U32_578);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_579 = U8_neq(ac, bc);
                            (void)_t_Bool_579;
                            ;
                            ;
                            if (_t_Bool_579) {
                                Bool _t_Bool_577 = 0;
                                (void)_t_Bool_577;
                                found = _t_Bool_577;
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
                    I64 _t_I64_581 = U32_to_i64(i);
                    (void)_t_I64_581;
                    last = _t_I64_581;
                    ;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_582 = U32_gt(&_rc_U32_569, &_re_U32_569);
                (void)_wcond_Bool_582;
                if (_wcond_Bool_582) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_569);
                (void)i;
                U32_dec(&_rc_U32_569);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_583 = needle->count;
                    (void)_re_U32_583;
                    U32 _rc_U32_583 = 0;
                    (void)_rc_U32_583;
                    Bool _t_Bool_592 = U32_lte(&_rc_U32_583, &_re_U32_583);
                    (void)_t_Bool_592;
                    if (_t_Bool_592) {
                        while (1) {
                            Bool _wcond_Bool_584 = U32_lt(&_rc_U32_583, &_re_U32_583);
                            (void)_wcond_Bool_584;
                            if (_wcond_Bool_584) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_583);
                            (void)j;
                            U32_inc(&_rc_U32_583);
                            U32 _t_U32_586 = U32_add(i, j);
                            (void)_t_U32_586;
                            U8 *ac = Str_get(self, &_t_U32_586);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_587 = U8_neq(ac, bc);
                            (void)_t_Bool_587;
                            ;
                            ;
                            if (_t_Bool_587) {
                                Bool _t_Bool_585 = 0;
                                (void)_t_Bool_585;
                                found = _t_Bool_585;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_588 = U32_gt(&_rc_U32_583, &_re_U32_583);
                            (void)_wcond_Bool_588;
                            if (_wcond_Bool_588) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_583);
                            (void)j;
                            U32_dec(&_rc_U32_583);
                            U32 _t_U32_590 = U32_add(i, j);
                            (void)_t_U32_590;
                            U8 *ac = Str_get(self, &_t_U32_590);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_591 = U8_neq(ac, bc);
                            (void)_t_Bool_591;
                            ;
                            ;
                            if (_t_Bool_591) {
                                Bool _t_Bool_589 = 0;
                                (void)_t_Bool_589;
                                found = _t_Bool_589;
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
                    I64 _t_I64_593 = U32_to_i64(i);
                    (void)_t_I64_593;
                    last = _t_I64_593;
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
    U32 _t_U32_627 = 0;
    (void)_t_U32_627;
    Bool _t_Bool_628 = U32_eq(from->count, _t_U32_627);
    (void)_t_Bool_628;
    ;
    if (_t_Bool_628) {
        Str *_t_Str_602 = Str_clone(self);
        (void)_t_Str_602;
        ;
        return _t_Str_602;
    }
    ;
    U32 matches = 0;
    (void)matches;
    U32 start = 0;
    (void)start;
    while (1) {
        U32 _t_U32_604 = U32_sub(self->count, from->count);
        (void)_t_U32_604;
        Bool _wcond_Bool_603 = U32_lte(&start, &_t_U32_604);
        (void)_wcond_Bool_603;
        ;
        if (_wcond_Bool_603) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_605 = U32_sub(self->count, start);
        (void)_t_U32_605;
        Str *rest = Str_substr(self, &start, &_t_U32_605);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_606 = 0;
        (void)_t_I64_606;
        I64 _t_I64_607 = 1;
        (void)_t_I64_607;
        I64 _t_I64_608 = I64_sub(_t_I64_606, _t_I64_607);
        (void)_t_I64_608;
        ;
        ;
        Bool _t_Bool_609 = I64_eq(pos, _t_I64_608);
        (void)_t_Bool_609;
        ;
        if (_t_Bool_609) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        U32 _t_U32_610 = U32_add(start, pos_u);
        (void)_t_U32_610;
        ;
        U32 _t_U32_611 = U32_add(_t_U32_610, from->count);
        (void)_t_U32_611;
        ;
        start = _t_U32_611;
        ;
        U32 _t_U32_612 = 1;
        (void)_t_U32_612;
        U32 _t_U32_613 = U32_add(matches, _t_U32_612);
        (void)_t_U32_613;
        ;
        matches = _t_U32_613;
        ;
    }
    U32 _t_U32_629 = 0;
    (void)_t_U32_629;
    Bool _t_Bool_630 = U32_eq(matches, _t_U32_629);
    (void)_t_Bool_630;
    ;
    if (_t_Bool_630) {
        Str *_t_Str_614 = Str_clone(self);
        (void)_t_Str_614;
        ;
        ;
        ;
        return _t_Str_614;
    }
    ;
    U32 removed = U32_mul(matches, from->count);
    (void)removed;
    U32 added = U32_mul(matches, to->count);
    (void)added;
    ;
    U32 _t_U32_631 = U32_sub(self->count, removed);
    (void)_t_U32_631;
    ;
    U32 _t_U32_632 = U32_add(_t_U32_631, added);
    (void)_t_U32_632;
    ;
    ;
    Str *out = Str_with_capacity(&_t_U32_632);
    (void)out;
    ;
    U32 _t_U32_633 = 0;
    (void)_t_U32_633;
    start = _t_U32_633;
    ;
    while (1) {
        U32 _t_U32_616 = U32_sub(self->count, from->count);
        (void)_t_U32_616;
        Bool _wcond_Bool_615 = U32_lte(&start, &_t_U32_616);
        (void)_wcond_Bool_615;
        ;
        if (_wcond_Bool_615) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_617 = U32_sub(self->count, start);
        (void)_t_U32_617;
        Str *rest = Str_substr(self, &start, &_t_U32_617);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_618 = 0;
        (void)_t_I64_618;
        I64 _t_I64_619 = 1;
        (void)_t_I64_619;
        I64 _t_I64_620 = I64_sub(_t_I64_618, _t_I64_619);
        (void)_t_I64_620;
        ;
        ;
        Bool _t_Bool_621 = I64_eq(pos, _t_I64_620);
        (void)_t_Bool_621;
        ;
        if (_t_Bool_621) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        Str *_t_Str_622 = Str_substr(self, &start, &pos_u);
        (void)_t_Str_622;
        Str_push_str(out, _t_Str_622);
        Str_delete(_t_Str_622, &(Bool){1});
        Str_push_str(out, to);
        U32 _t_U32_623 = U32_add(start, pos_u);
        (void)_t_U32_623;
        ;
        U32 _t_U32_624 = U32_add(_t_U32_623, from->count);
        (void)_t_U32_624;
        ;
        start = _t_U32_624;
        ;
    }
    Bool _t_Bool_634 = U32_lt(&start, &self->count);
    (void)_t_Bool_634;
    if (_t_Bool_634) {
        U32 _t_U32_625 = U32_sub(self->count, start);
        (void)_t_U32_625;
        Str *_t_Str_626 = Str_substr(self, &start, &_t_U32_625);
        (void)_t_Str_626;
        ;
        Str_push_str(out, _t_Str_626);
        Str_delete(_t_Str_626, &(Bool){1});
    }
    ;
    ;
    return out;
}

Str * Str_get_char(Str * self, U32 * i) {
    (void)self;
    (void)i;
    U32 _t_U32_635 = 1;
    (void)_t_U32_635;
    Str *_t_Str_636 = Str_substr(self, i, &_t_U32_635);
    (void)_t_Str_636;
    ;
    return _t_Str_636;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t_Bool_639 = Str_starts_with(self, prefix);
    (void)_t_Bool_639;
    if (_t_Bool_639) {
        U32 _t_U32_637 = U32_sub(self->count, prefix->count);
        (void)_t_U32_637;
        Str *_t_Str_638 = Str_substr(self, &prefix->count, &_t_U32_637);
        (void)_t_Str_638;
        ;
        ;
        return _t_Str_638;
    }
    ;
    Str *_t_Str_640 = Str_clone(self);
    (void)_t_Str_640;
    return _t_Str_640;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t_Bool_644 = Str_ends_with(self, suffix);
    (void)_t_Bool_644;
    if (_t_Bool_644) {
        U32 _t_U32_641 = 0;
        (void)_t_U32_641;
        U32 _t_U32_642 = U32_sub(self->count, suffix->count);
        (void)_t_U32_642;
        Str *_t_Str_643 = Str_substr(self, &_t_U32_641, &_t_U32_642);
        (void)_t_Str_643;
        ;
        ;
        ;
        return _t_Str_643;
    }
    ;
    Str *_t_Str_645 = Str_clone(self);
    (void)_t_Str_645;
    return _t_Str_645;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t_U64_646 = 2;
    (void)_t_U64_646;
    void * buf = malloc(_t_U64_646);
    (void)buf;
    ;
    U64 _t_U64_647 = 1;
    (void)_t_U64_647;
    memcpy(buf, byte, _t_U64_647);
    ;
    U64 _t_U64_648 = 1;
    (void)_t_U64_648;
    void *_t_v_649 = ptr_add(buf, _t_U64_648);
    (void)_t_v_649;
    I32 _t_I32_650 = 0;
    (void)_t_I32_650;
    U64 _t_U64_651 = 1;
    (void)_t_U64_651;
    memset(_t_v_649, _t_I32_650, _t_U64_651);
    ;
    ;
    ;
    I64 _t_I64_652 = 1;
    (void)_t_I64_652;
    I64 _t_I64_653 = 1;
    (void)_t_I64_653;
    Str *_t_Str_654 = malloc(sizeof(Str));
    _t_Str_654->c_str = buf;
    _t_Str_654->count = _t_I64_652;
    _t_Str_654->cap = _t_I64_653;
    (void)_t_Str_654;
    ;
    ;
    return _t_Str_654;
}

I64 Str_to_i64(Str * self) {
    (void)self;
    U32 _t_U32_715 = 0;
    (void)_t_U32_715;
    Bool _t_Bool_716 = U32_eq(self->count, _t_U32_715);
    (void)_t_Bool_716;
    ;
    if (_t_Bool_716) {
        Str *_t_Str_655 = Str_lit("Str", 3ULL);
        (void)_t_Str_655;
        U32 _t_U32_656 = 16;
        (void)_t_U32_656;
        U32 _t_U32_657 = 1;
        (void)_t_U32_657;
        Array *_va_Array_12 = Array_new(_t_Str_655, &_t_U32_656, &_t_U32_657);
        (void)_va_Array_12;
        Str_delete(_t_Str_655, &(Bool){1});
        ;
        ;
        U32 _t_U32_658 = 0;
        (void)_t_U32_658;
        Str *_t_Str_659 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t_Str_659;
        Array_set(_va_Array_12, &_t_U32_658, _t_Str_659);
        ;
        Str *_t_Str_660 = Str_lit("./src/core/str.til:266:37", 25ULL);
        (void)_t_Str_660;
        panic(_t_Str_660, _va_Array_12);
        Str_delete(_t_Str_660, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_717 = 0;
    (void)_t_U32_717;
    U8 *first = Str_get(self, &_t_U32_717);
    (void)first;
    U8 _t_U8_718 = 45;
    (void)_t_U8_718;
    Bool _t_Bool_719 = U8_eq(DEREF(first), _t_U8_718);
    (void)_t_Bool_719;
    ;
    ;
    if (_t_Bool_719) {
        Bool _t_Bool_661 = 1;
        (void)_t_Bool_661;
        neg = _t_Bool_661;
        ;
        U32 _t_U32_662 = 1;
        (void)_t_U32_662;
        start = _t_U32_662;
        ;
    }
    ;
    Bool _t_Bool_720 = U32_eq(start, self->count);
    (void)_t_Bool_720;
    if (_t_Bool_720) {
        Str *_t_Str_663 = Str_lit("Str", 3ULL);
        (void)_t_Str_663;
        U32 _t_U32_664 = 16;
        (void)_t_U32_664;
        U32 _t_U32_665 = 1;
        (void)_t_U32_665;
        Array *_va_Array_13 = Array_new(_t_Str_663, &_t_U32_664, &_t_U32_665);
        (void)_va_Array_13;
        Str_delete(_t_Str_663, &(Bool){1});
        ;
        ;
        U32 _t_U32_666 = 0;
        (void)_t_U32_666;
        Str *_t_Str_667 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t_Str_667;
        Array_set(_va_Array_13, &_t_U32_666, _t_Str_667);
        ;
        Str *_t_Str_668 = Str_lit("./src/core/str.til:275:41", 25ULL);
        (void)_t_Str_668;
        panic(_t_Str_668, _va_Array_13);
        Str_delete(_t_Str_668, &(Bool){1});
    }
    ;
    {
        U32 _re_U32_669 = self->count;
        (void)_re_U32_669;
        U32 _rc_U32_669 = U32_clone(&start);
        (void)_rc_U32_669;
        Bool _t_Bool_712 = U32_lte(&_rc_U32_669, &_re_U32_669);
        (void)_t_Bool_712;
        if (_t_Bool_712) {
            while (1) {
                Bool _wcond_Bool_670 = U32_lt(&_rc_U32_669, &_re_U32_669);
                (void)_wcond_Bool_670;
                if (_wcond_Bool_670) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_669);
                (void)i;
                U32_inc(&_rc_U32_669);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_681 = U8_to_i64(DEREF(ch));
                (void)_t_I64_681;
                ;
                I64 _t_I64_682 = 48;
                (void)_t_I64_682;
                I64 d = I64_sub(_t_I64_681, _t_I64_682);
                (void)d;
                ;
                ;
                I64 _t_I64_683 = 0;
                (void)_t_I64_683;
                I64 _t_I64_684 = 9;
                (void)_t_I64_684;
                Bool _t_Bool_685 = I64_lt(&d, &_t_I64_683);
                (void)_t_Bool_685;
                ;
                Bool _t_Bool_686 = I64_gt(&d, &_t_I64_684);
                (void)_t_Bool_686;
                ;
                Bool _t_Bool_687 = or(_t_Bool_685, _t_Bool_686);
                (void)_t_Bool_687;
                ;
                ;
                if (_t_Bool_687) {
                    Str *_t_Str_671 = Str_lit("Str", 3ULL);
                    (void)_t_Str_671;
                    U32 _t_U32_672 = 16;
                    (void)_t_U32_672;
                    U32 _t_U32_673 = 3;
                    (void)_t_U32_673;
                    Array *_va_Array_14 = Array_new(_t_Str_671, &_t_U32_672, &_t_U32_673);
                    (void)_va_Array_14;
                    Str_delete(_t_Str_671, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_674 = 0;
                    (void)_t_U32_674;
                    Str *_t_Str_675 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_675;
                    Array_set(_va_Array_14, &_t_U32_674, _t_Str_675);
                    ;
                    U32 _t_U32_676 = 1;
                    (void)_t_U32_676;
                    Str *_t_Str_677 = Str_clone(self);
                    (void)_t_Str_677;
                    Array_set(_va_Array_14, &_t_U32_676, _t_Str_677);
                    ;
                    U32 _t_U32_678 = 2;
                    (void)_t_U32_678;
                    Str *_t_Str_679 = Str_lit("'", 1ULL);
                    (void)_t_Str_679;
                    Array_set(_va_Array_14, &_t_U32_678, _t_Str_679);
                    ;
                    Str *_t_Str_680 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_680;
                    panic(_t_Str_680, _va_Array_14);
                    Str_delete(_t_Str_680, &(Bool){1});
                }
                ;
                I64 _t_I64_688 = 10;
                (void)_t_I64_688;
                I64 _t_I64_689 = I64_mul(result, _t_I64_688);
                (void)_t_I64_689;
                ;
                I64 _t_I64_690 = I64_add(_t_I64_689, d);
                (void)_t_I64_690;
                ;
                ;
                result = _t_I64_690;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_691 = U32_gt(&_rc_U32_669, &_re_U32_669);
                (void)_wcond_Bool_691;
                if (_wcond_Bool_691) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_669);
                (void)i;
                U32_dec(&_rc_U32_669);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_702 = U8_to_i64(DEREF(ch));
                (void)_t_I64_702;
                ;
                I64 _t_I64_703 = 48;
                (void)_t_I64_703;
                I64 d = I64_sub(_t_I64_702, _t_I64_703);
                (void)d;
                ;
                ;
                I64 _t_I64_704 = 0;
                (void)_t_I64_704;
                I64 _t_I64_705 = 9;
                (void)_t_I64_705;
                Bool _t_Bool_706 = I64_lt(&d, &_t_I64_704);
                (void)_t_Bool_706;
                ;
                Bool _t_Bool_707 = I64_gt(&d, &_t_I64_705);
                (void)_t_Bool_707;
                ;
                Bool _t_Bool_708 = or(_t_Bool_706, _t_Bool_707);
                (void)_t_Bool_708;
                ;
                ;
                if (_t_Bool_708) {
                    Str *_t_Str_692 = Str_lit("Str", 3ULL);
                    (void)_t_Str_692;
                    U32 _t_U32_693 = 16;
                    (void)_t_U32_693;
                    U32 _t_U32_694 = 3;
                    (void)_t_U32_694;
                    Array *_va_Array_15 = Array_new(_t_Str_692, &_t_U32_693, &_t_U32_694);
                    (void)_va_Array_15;
                    Str_delete(_t_Str_692, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_695 = 0;
                    (void)_t_U32_695;
                    Str *_t_Str_696 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_696;
                    Array_set(_va_Array_15, &_t_U32_695, _t_Str_696);
                    ;
                    U32 _t_U32_697 = 1;
                    (void)_t_U32_697;
                    Str *_t_Str_698 = Str_clone(self);
                    (void)_t_Str_698;
                    Array_set(_va_Array_15, &_t_U32_697, _t_Str_698);
                    ;
                    U32 _t_U32_699 = 2;
                    (void)_t_U32_699;
                    Str *_t_Str_700 = Str_lit("'", 1ULL);
                    (void)_t_Str_700;
                    Array_set(_va_Array_15, &_t_U32_699, _t_Str_700);
                    ;
                    Str *_t_Str_701 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_701;
                    panic(_t_Str_701, _va_Array_15);
                    Str_delete(_t_Str_701, &(Bool){1});
                }
                ;
                I64 _t_I64_709 = 10;
                (void)_t_I64_709;
                I64 _t_I64_710 = I64_mul(result, _t_I64_709);
                (void)_t_I64_710;
                ;
                I64 _t_I64_711 = I64_add(_t_I64_710, d);
                (void)_t_I64_711;
                ;
                ;
                result = _t_I64_711;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    if (neg) {
        I64 _t_I64_713 = 0;
        (void)_t_I64_713;
        I64 _t_I64_714 = I64_sub(_t_I64_713, result);
        (void)_t_I64_714;
        ;
        ;
        ;
        return _t_I64_714;
    }
    ;
    return result;
}

U8 Str_to_u8(Str * self) {
    (void)self;
    I64 _t_I64_721 = Str_to_i64(self);
    (void)_t_I64_721;
    U8 _t_U8_722 = I64_to_u8(_t_I64_721);
    (void)_t_U8_722;
    ;
    return _t_U8_722;
}

I32 Str_to_i32(Str * self) {
    (void)self;
    I64 _t_I64_723 = Str_to_i64(self);
    (void)_t_I64_723;
    I32 _t_I32_724 = I64_to_i32(_t_I64_723);
    (void)_t_I32_724;
    ;
    return _t_I32_724;
}

F32 Str_to_f32(Str * self) {
    (void)self;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_750 = Str_len(self);
    (void)_t_U32_750;
    U32 _t_U32_751 = 0;
    (void)_t_U32_751;
    U32 _t_U32_752 = 0;
    (void)_t_U32_752;
    U8 *_t_U8_753 = Str_get(self, &_t_U32_752);
    (void)_t_U8_753;
    U8 _t_U8_754 = 45;
    (void)_t_U8_754;
    Bool _t_Bool_755 = U32_gt(&_t_U32_750, &_t_U32_751);
    (void)_t_Bool_755;
    ;
    ;
    Bool _t_Bool_756 = U8_eq(DEREF(_t_U8_753), _t_U8_754);
    (void)_t_Bool_756;
    ;
    ;
    Bool _t_Bool_757 = and(_t_Bool_755, _t_Bool_756);
    (void)_t_Bool_757;
    ;
    ;
    if (_t_Bool_757) {
        Bool _t_Bool_725 = 1;
        (void)_t_Bool_725;
        neg = _t_Bool_725;
        ;
        U32 _t_U32_726 = 1;
        (void)_t_U32_726;
        start = _t_U32_726;
        ;
    }
    ;
    U32 _t_U32_758 = Str_len(self);
    (void)_t_U32_758;
    U32 _t_U32_759 = U32_sub(_t_U32_758, start);
    (void)_t_U32_759;
    ;
    Str *rest = Str_substr(self, &start, &_t_U32_759);
    (void)rest;
    ;
    ;
    Str *_t_Str_760 = Str_lit(".", 1ULL);
    (void)_t_Str_760;
    I64 dot = Str_find(rest, _t_Str_760);
    (void)dot;
    Str_delete(_t_Str_760, &(Bool){1});
    I64 _t_I64_761 = 0;
    (void)_t_I64_761;
    I64 _t_I64_762 = 1;
    (void)_t_I64_762;
    I64 _t_I64_763 = I64_sub(_t_I64_761, _t_I64_762);
    (void)_t_I64_763;
    ;
    ;
    Bool _t_Bool_764 = I64_eq(dot, _t_I64_763);
    (void)_t_Bool_764;
    ;
    if (_t_Bool_764) {
        I64 _t_I64_730 = Str_to_i64(rest);
        (void)_t_I64_730;
        F32 out = I64_to_f32(_t_I64_730);
        (void)out;
        ;
        if (neg) {
            I64 _t_I64_727 = 0;
            (void)_t_I64_727;
            F32 _t_F32_728 = I64_to_f32(_t_I64_727);
            (void)_t_F32_728;
            ;
            F32 _t_F32_729 = F32_sub(_t_F32_728, out);
            (void)_t_F32_729;
            ;
            ;
            ;
            ;
            ;
            Str_delete(rest, &(Bool){1});
            return _t_F32_729;
        }
        ;
        ;
        ;
        Str_delete(rest, &(Bool){1});
        return out;
    }
    ;
    U32 _t_U32_765 = 0;
    (void)_t_U32_765;
    U32 _t_U32_766 = I64_to_usize(dot);
    (void)_t_U32_766;
    Str *int_part = Str_substr(rest, &_t_U32_765, &_t_U32_766);
    (void)int_part;
    ;
    ;
    U32 _t_U32_767 = I64_to_usize(dot);
    (void)_t_U32_767;
    U32 _t_U32_768 = 1;
    (void)_t_U32_768;
    U32 _t_U32_769 = I64_to_usize(dot);
    (void)_t_U32_769;
    ;
    U32 _t_U32_770 = 1;
    (void)_t_U32_770;
    U32 _t_U32_771 = Str_len(rest);
    (void)_t_U32_771;
    U32 _t_U32_772 = U32_add(_t_U32_769, _t_U32_770);
    (void)_t_U32_772;
    ;
    ;
    U32 _t_U32_773 = U32_add(_t_U32_767, _t_U32_768);
    (void)_t_U32_773;
    ;
    ;
    U32 _t_U32_774 = U32_sub(_t_U32_771, _t_U32_772);
    (void)_t_U32_774;
    ;
    ;
    Str *frac_part = Str_substr(rest, &_t_U32_773, &_t_U32_774);
    (void)frac_part;
    ;
    ;
    Str_delete(rest, &(Bool){1});
    I64 _t_I64_775 = 0;
    (void)_t_I64_775;
    F32 out = I64_to_f32(_t_I64_775);
    (void)out;
    ;
    U32 _t_U32_776 = Str_len(int_part);
    (void)_t_U32_776;
    U32 _t_U32_777 = 0;
    (void)_t_U32_777;
    Bool _t_Bool_778 = U32_gt(&_t_U32_776, &_t_U32_777);
    (void)_t_Bool_778;
    ;
    ;
    if (_t_Bool_778) {
        I64 _t_I64_731 = Str_to_i64(int_part);
        (void)_t_I64_731;
        F32 _t_F32_732 = I64_to_f32(_t_I64_731);
        (void)_t_F32_732;
        ;
        out = _t_F32_732;
        ;
    }
    ;
    Str_delete(int_part, &(Bool){1});
    U32 _t_U32_779 = Str_len(frac_part);
    (void)_t_U32_779;
    U32 _t_U32_780 = 0;
    (void)_t_U32_780;
    Bool _t_Bool_781 = U32_gt(&_t_U32_779, &_t_U32_780);
    (void)_t_Bool_781;
    ;
    ;
    if (_t_Bool_781) {
        I64 _t_I64_743 = Str_to_i64(frac_part);
        (void)_t_I64_743;
        F32 frac = I64_to_f32(_t_I64_743);
        (void)frac;
        ;
        I64 _t_I64_744 = 1;
        (void)_t_I64_744;
        F32 scale = I64_to_f32(_t_I64_744);
        (void)scale;
        ;
        {
            U32 _re_U32_733 = Str_len(frac_part);
            (void)_re_U32_733;
            U32 _rc_U32_733 = 0;
            (void)_rc_U32_733;
            Bool _t_Bool_742 = U32_lte(&_rc_U32_733, &_re_U32_733);
            (void)_t_Bool_742;
            if (_t_Bool_742) {
                while (1) {
                    Bool _wcond_Bool_734 = U32_lt(&_rc_U32_733, &_re_U32_733);
                    (void)_wcond_Bool_734;
                    if (_wcond_Bool_734) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_733);
                    (void)_;
                    ;
                    U32_inc(&_rc_U32_733);
                    I64 _t_I64_735 = 10;
                    (void)_t_I64_735;
                    F32 _t_F32_736 = I64_to_f32(_t_I64_735);
                    (void)_t_F32_736;
                    ;
                    F32 _t_F32_737 = F32_mul(scale, _t_F32_736);
                    (void)_t_F32_737;
                    ;
                    scale = _t_F32_737;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_738 = U32_gt(&_rc_U32_733, &_re_U32_733);
                    (void)_wcond_Bool_738;
                    if (_wcond_Bool_738) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_733);
                    (void)_;
                    ;
                    U32_dec(&_rc_U32_733);
                    I64 _t_I64_739 = 10;
                    (void)_t_I64_739;
                    F32 _t_F32_740 = I64_to_f32(_t_I64_739);
                    (void)_t_F32_740;
                    ;
                    F32 _t_F32_741 = F32_mul(scale, _t_F32_740);
                    (void)_t_F32_741;
                    ;
                    scale = _t_F32_741;
                    ;
                }
            }
            ;
            ;
            ;
        }
        F32 _t_F32_745 = F32_div(frac, scale);
        (void)_t_F32_745;
        ;
        ;
        F32 _t_F32_746 = F32_add(out, _t_F32_745);
        (void)_t_F32_746;
        ;
        out = _t_F32_746;
        ;
    }
    ;
    Str_delete(frac_part, &(Bool){1});
    if (neg) {
        I64 _t_I64_747 = 0;
        (void)_t_I64_747;
        F32 _t_F32_748 = I64_to_f32(_t_I64_747);
        (void)_t_F32_748;
        ;
        F32 _t_F32_749 = F32_sub(_t_F32_748, out);
        (void)_t_F32_749;
        ;
        ;
        ;
        return _t_F32_749;
    }
    ;
    return out;
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t_Str_798 = Str_lit("Str", 3ULL);
    (void)_t_Str_798;
    Vec *parts = Vec_new(_t_Str_798);
    (void)parts;
    Str_delete(_t_Str_798, &(Bool){1});
    U32 _t_U32_799 = Str_len(delim);
    (void)_t_U32_799;
    U32 _t_U32_800 = 0;
    (void)_t_U32_800;
    Bool _t_Bool_801 = U32_eq(_t_U32_799, _t_U32_800);
    (void)_t_Bool_801;
    ;
    ;
    if (_t_Bool_801) {
        Str *_t_Str_782 = Str_clone(self);
        (void)_t_Str_782;
        Vec_push(parts, _t_Str_782);
        ;
        return parts;
    }
    ;
    U32 start = 0;
    (void)start;
    U32 pos = 0;
    (void)pos;
    while (1) {
        U32 _t_U32_792 = Str_len(self);
        (void)_t_U32_792;
        U32 _t_U32_793 = Str_len(delim);
        (void)_t_U32_793;
        U32 _t_U32_794 = U32_sub(_t_U32_792, _t_U32_793);
        (void)_t_U32_794;
        ;
        ;
        Bool _wcond_Bool_783 = U32_lte(&pos, &_t_U32_794);
        (void)_wcond_Bool_783;
        ;
        if (_wcond_Bool_783) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_795 = Str_len(delim);
        (void)_t_U32_795;
        Str *_t_Str_796 = Str_substr(self, &pos, &_t_U32_795);
        (void)_t_Str_796;
        ;
        Bool _t_Bool_797 = Str_eq(_t_Str_796, delim);
        (void)_t_Bool_797;
        Str_delete(_t_Str_796, &(Bool){1});
        if (_t_Bool_797) {
            U32 _t_U32_784 = U32_sub(pos, start);
            (void)_t_U32_784;
            Str *_t_Str_785 = Str_substr(self, &start, &_t_U32_784);
            (void)_t_Str_785;
            ;
            Str *_t_Str_786 = Str_clone(_t_Str_785);
            (void)_t_Str_786;
            Str_delete(_t_Str_785, &(Bool){1});
            Vec_push(parts, _t_Str_786);
            U32 _t_U32_787 = Str_len(delim);
            (void)_t_U32_787;
            U32 _t_U32_788 = U32_add(pos, _t_U32_787);
            (void)_t_U32_788;
            ;
            start = _t_U32_788;
            ;
            U32 _t_U32_789 = U32_clone(&start);
            (void)_t_U32_789;
            pos = _t_U32_789;
            ;
        } else {
            U32 _t_U32_790 = 1;
            (void)_t_U32_790;
            U32 _t_U32_791 = U32_add(pos, _t_U32_790);
            (void)_t_U32_791;
            ;
            pos = _t_U32_791;
            ;
        }
        ;
    }
    ;
    U32 _t_U32_802 = Str_len(self);
    (void)_t_U32_802;
    U32 _t_U32_803 = U32_sub(_t_U32_802, start);
    (void)_t_U32_803;
    ;
    Str *_t_Str_804 = Str_substr(self, &start, &_t_U32_803);
    (void)_t_Str_804;
    ;
    ;
    Str *_t_Str_805 = Str_clone(_t_Str_804);
    (void)_t_Str_805;
    Str_delete(_t_Str_804, &(Bool){1});
    Vec_push(parts, _t_Str_805);
    return parts;
}

U32 Str_size(void) {
    I64 _t_I64_806 = 16;
    (void)_t_I64_806;
    return _t_I64_806;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_807 = Str_cmp(a, b);
    (void)_t_I64_807;
    I64 _t_I64_808 = 0;
    (void)_t_I64_808;
    Bool _t_Bool_809 = I64_eq(_t_I64_807, _t_I64_808);
    (void)_t_Bool_809;
    ;
    ;
    return _t_Bool_809;
}

Bool Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_810 = 0;
    (void)_t_I64_810;
    I64 _t_I64_811 = 1;
    (void)_t_I64_811;
    I64 _t_I64_812 = Str_cmp(a, b);
    (void)_t_I64_812;
    I64 _t_I64_813 = I64_sub(_t_I64_810, _t_I64_811);
    (void)_t_I64_813;
    ;
    ;
    Bool _t_Bool_814 = I64_eq(_t_I64_812, _t_I64_813);
    (void)_t_Bool_814;
    ;
    ;
    return _t_Bool_814;
}

Bool Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_815 = Str_cmp(a, b);
    (void)_t_I64_815;
    I64 _t_I64_816 = 1;
    (void)_t_I64_816;
    Bool _t_Bool_817 = I64_eq(_t_I64_815, _t_I64_816);
    (void)_t_Bool_817;
    ;
    ;
    return _t_Bool_817;
}

Bool Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_818 = Str_eq(a, b);
    (void)_t_Bool_818;
    Bool _t_Bool_819 = not(_t_Bool_818);
    (void)_t_Bool_819;
    ;
    return _t_Bool_819;
}

Bool Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_820 = Str_gt(a, b);
    (void)_t_Bool_820;
    Bool _t_Bool_821 = not(_t_Bool_820);
    (void)_t_Bool_821;
    ;
    return _t_Bool_821;
}

Bool Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_822 = Str_lt(a, b);
    (void)_t_Bool_822;
    Bool _t_Bool_823 = not(_t_Bool_822);
    (void)_t_Bool_823;
    ;
    return _t_Bool_823;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_855 = 8;
    (void)_t_I64_855;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_855; return _r; }
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
    I64 _t_I64_858 = I16_to_i64(DEREF(val));
    (void)_t_I64_858;
    Str *_t_Str_859 = I64_to_str(&_t_I64_858);
    (void)_t_Str_859;
    ;
    return _t_Str_859;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t_I16_860 = 1;
    (void)_t_I16_860;
    I16 _t_I16_861 = I16_add(DEREF(self), _t_I16_860);
    (void)_t_I16_861;
    ;
    *self = _t_I16_861;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t_I16_862 = 1;
    (void)_t_I16_862;
    I16 _t_I16_863 = I16_sub(DEREF(self), _t_I16_862);
    (void)_t_I16_863;
    ;
    *self = _t_I16_863;
    ;
}

I16 * I16_unity(I16 * _self) {
    (void)_self;
    I64 _t_I64_864 = 1;
    (void)_t_I64_864;
    I16 _t_I16_865 = I64_to_i16(_t_I64_864);
    (void)_t_I16_865;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_865; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t_I64_866 = 0;
    (void)_t_I64_866;
    I64 _t_I64_867 = I16_to_i64(DEREF(a));
    (void)_t_I64_867;
    I64 _t_I64_868 = I64_sub(_t_I64_866, _t_I64_867);
    (void)_t_I64_868;
    ;
    ;
    I16 _t_I16_869 = I64_to_i16(_t_I64_868);
    (void)_t_I16_869;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_869; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t_I64_874 = I16_to_i64(DEREF(a));
    (void)_t_I64_874;
    I64 _t_I64_875 = 0;
    (void)_t_I64_875;
    Bool _t_Bool_876 = I64_lt(&_t_I64_874, &_t_I64_875);
    (void)_t_Bool_876;
    ;
    ;
    if (_t_Bool_876) {
        I64 _t_I64_870 = 0;
        (void)_t_I64_870;
        I64 _t_I64_871 = I16_to_i64(DEREF(a));
        (void)_t_I64_871;
        I64 _t_I64_872 = I64_sub(_t_I64_870, _t_I64_871);
        (void)_t_I64_872;
        ;
        ;
        I16 _t_I16_873 = I64_to_i16(_t_I64_872);
        (void)_t_I16_873;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_873; return _r; }
    }
    ;
    I16 _t_I16_877 = I16_clone(a);
    (void)_t_I16_877;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_877; return _r; }
}

U64 I16_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I16 *au = a;
    (void)au;
    I16 *bu = b;
    (void)bu;
    Bool _t_Bool_881 = I16_lte(au, bu);
    (void)_t_Bool_881;
    if (_t_Bool_881) {
        I16 _t_I16_878 = I16_sub(DEREF(bu), DEREF(au));
        (void)_t_I16_878;
        I64 _t_I64_879 = I16_to_i64(_t_I16_878);
        (void)_t_I64_879;
        ;
        U64 _t_U64_880 = I64_to_u64(_t_I64_879);
        (void)_t_U64_880;
        ;
        ;
        return _t_U64_880;
    }
    ;
    I16 _t_I16_882 = I16_sub(DEREF(au), DEREF(bu));
    (void)_t_I16_882;
    I64 _t_I64_883 = I16_to_i64(_t_I16_882);
    (void)_t_I64_883;
    ;
    U64 _t_U64_884 = I64_to_u64(_t_I64_883);
    (void)_t_U64_884;
    ;
    return _t_U64_884;
}

void I16_delete(I16 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I16_size(void) {
    I64 _t_I64_885 = 2;
    (void)_t_I64_885;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_885; return _r; }
}

Bool I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_886 = 0;
    (void)_t_I64_886;
    I64 _t_I64_887 = 1;
    (void)_t_I64_887;
    I64 _t_I64_888 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_888;
    I64 _t_I64_889 = I64_sub(_t_I64_886, _t_I64_887);
    (void)_t_I64_889;
    ;
    ;
    Bool _t_Bool_890 = I64_eq(_t_I64_888, _t_I64_889);
    (void)_t_Bool_890;
    ;
    ;
    return _t_Bool_890;
}

Bool I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_891 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_891;
    I64 _t_I64_892 = 1;
    (void)_t_I64_892;
    Bool _t_Bool_893 = I64_eq(_t_I64_891, _t_I64_892);
    (void)_t_Bool_893;
    ;
    ;
    return _t_Bool_893;
}

Bool I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_894 = I16_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_894;
    Bool _t_Bool_895 = not(_t_Bool_894);
    (void)_t_Bool_895;
    ;
    return _t_Bool_895;
}

Bool I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_896 = I16_gt(a, b);
    (void)_t_Bool_896;
    Bool _t_Bool_897 = not(_t_Bool_896);
    (void)_t_Bool_897;
    ;
    return _t_Bool_897;
}

Bool I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_898 = I16_lt(a, b);
    (void)_t_Bool_898;
    Bool _t_Bool_899 = not(_t_Bool_898);
    (void)_t_Bool_899;
    ;
    return _t_Bool_899;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_936 = 0;
    (void)_t_I64_936;
    Bool _t_Bool_937 = I64_eq(DEREF(val), _t_I64_936);
    (void)_t_Bool_937;
    ;
    if (_t_Bool_937) {
        U64 _t_U64_900 = 2;
        (void)_t_U64_900;
        void * buf = malloc(_t_U64_900);
        (void)buf;
        ;
        I64 _t_I64_901 = 48;
        (void)_t_I64_901;
        U64 _t_U64_902 = 1;
        (void)_t_U64_902;
        memcpy(buf, &_t_I64_901, _t_U64_902);
        ;
        ;
        U64 _t_U64_903 = 1;
        (void)_t_U64_903;
        void *_t_v_904 = ptr_add(buf, _t_U64_903);
        (void)_t_v_904;
        I32 _t_I32_905 = 0;
        (void)_t_I32_905;
        U64 _t_U64_906 = 1;
        (void)_t_U64_906;
        memset(_t_v_904, _t_I32_905, _t_U64_906);
        ;
        ;
        ;
        I64 _t_I64_907 = 1;
        (void)_t_I64_907;
        I64 _t_I64_908 = 1;
        (void)_t_I64_908;
        Str *_t_Str_909 = malloc(sizeof(Str));
        _t_Str_909->c_str = buf;
        _t_Str_909->count = _t_I64_907;
        _t_Str_909->cap = _t_I64_908;
        (void)_t_Str_909;
        ;
        ;
        ;
        return _t_Str_909;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t_I64_938 = 0;
    (void)_t_I64_938;
    Bool _t_Bool_939 = I64_lt(val, &_t_I64_938);
    (void)_t_Bool_939;
    ;
    if (_t_Bool_939) {
        Bool _t_Bool_910 = 1;
        (void)_t_Bool_910;
        is_neg = _t_Bool_910;
        ;
        I64 _t_I64_911 = 0;
        (void)_t_I64_911;
        I64 _t_I64_912 = I64_sub(_t_I64_911, DEREF(val));
        (void)_t_I64_912;
        ;
        v = _t_I64_912;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&v);
    (void)tmp;
    while (1) {
        I64 _t_I64_914 = 0;
        (void)_t_I64_914;
        Bool _wcond_Bool_913 = I64_gt(&tmp, &_t_I64_914);
        (void)_wcond_Bool_913;
        ;
        if (_wcond_Bool_913) {
        } else {
            ;
            break;
        }
        ;
        U64 _t_U64_915 = 1;
        (void)_t_U64_915;
        U64 _t_U64_916 = U64_add(ndigits, _t_U64_915);
        (void)_t_U64_916;
        ;
        ndigits = _t_U64_916;
        ;
        I64 _t_I64_917 = 10;
        (void)_t_I64_917;
        I64 _t_I64_918 = I64_div(tmp, _t_I64_917);
        (void)_t_I64_918;
        ;
        tmp = _t_I64_918;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    (void)total;
    ;
    if (is_neg) {
        U64 _t_U64_919 = 1;
        (void)_t_U64_919;
        U64 _t_U64_920 = U64_add(total, _t_U64_919);
        (void)_t_U64_920;
        ;
        total = _t_U64_920;
        ;
    }
    U64 _t_U64_940 = 1;
    (void)_t_U64_940;
    U64 _t_U64_941 = U64_add(total, _t_U64_940);
    (void)_t_U64_941;
    ;
    void * buf = malloc(_t_U64_941);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t_I64_921 = 45;
        (void)_t_I64_921;
        U64 _t_U64_922 = 1;
        (void)_t_U64_922;
        memcpy(buf, &_t_I64_921, _t_U64_922);
        ;
        ;
    }
    ;
    U64 _t_U64_942 = 1;
    (void)_t_U64_942;
    U64 i = U64_sub(total, _t_U64_942);
    (void)i;
    ;
    while (1) {
        I64 _t_I64_924 = 0;
        (void)_t_I64_924;
        Bool _wcond_Bool_923 = I64_gt(&v, &_t_I64_924);
        (void)_wcond_Bool_923;
        ;
        if (_wcond_Bool_923) {
        } else {
            ;
            break;
        }
        ;
        I64 _t_I64_925 = 10;
        (void)_t_I64_925;
        I64 _t_I64_926 = I64_mod(v, _t_I64_925);
        (void)_t_I64_926;
        ;
        I64 _t_I64_927 = 48;
        (void)_t_I64_927;
        I64 _t_I64_928 = I64_add(_t_I64_926, _t_I64_927);
        (void)_t_I64_928;
        ;
        ;
        void *_t_v_929 = ptr_add(buf, i);
        (void)_t_v_929;
        U8 _t_U8_930 = I64_to_u8(_t_I64_928);
        (void)_t_U8_930;
        ;
        U64 _t_U64_931 = 1;
        (void)_t_U64_931;
        memcpy(_t_v_929, &_t_U8_930, _t_U64_931);
        ;
        ;
        I64 _t_I64_932 = 10;
        (void)_t_I64_932;
        I64 _t_I64_933 = I64_div(v, _t_I64_932);
        (void)_t_I64_933;
        ;
        v = _t_I64_933;
        ;
        U64 _t_U64_934 = 1;
        (void)_t_U64_934;
        U64 _t_U64_935 = U64_sub(i, _t_U64_934);
        (void)_t_U64_935;
        ;
        i = _t_U64_935;
        ;
    }
    ;
    ;
    void *_t_v_943 = ptr_add(buf, total);
    (void)_t_v_943;
    I32 _t_I32_944 = 0;
    (void)_t_I32_944;
    U64 _t_U64_945 = 1;
    (void)_t_U64_945;
    memset(_t_v_943, _t_I32_944, _t_U64_945);
    ;
    ;
    Str *_t_Str_946 = malloc(sizeof(Str));
    _t_Str_946->c_str = buf;
    _t_Str_946->count = total;
    _t_Str_946->cap = total;
    (void)_t_Str_946;
    ;
    return _t_Str_946;
}

U32 I64_to_usize(I64 val) {
    (void)val;
    U32 _t_U32_947 = I64_to_u32(val);
    (void)_t_U32_947;
    return _t_U32_947;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t_I64_948 = 1;
    (void)_t_I64_948;
    I64 _t_I64_949 = I64_add(DEREF(self), _t_I64_948);
    (void)_t_I64_949;
    ;
    *self = _t_I64_949;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t_I64_950 = 1;
    (void)_t_I64_950;
    I64 _t_I64_951 = I64_sub(DEREF(self), _t_I64_950);
    (void)_t_I64_951;
    ;
    *self = _t_I64_951;
    ;
}

I64 * I64_unity(I64 * _self) {
    (void)_self;
    I64 _t_I64_952 = 1;
    (void)_t_I64_952;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_952; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t_I64_953 = 0;
    (void)_t_I64_953;
    I64 _t_I64_954 = I64_sub(_t_I64_953, DEREF(a));
    (void)_t_I64_954;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_954; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t_I64_957 = 0;
    (void)_t_I64_957;
    Bool _t_Bool_958 = I64_lt(a, &_t_I64_957);
    (void)_t_Bool_958;
    ;
    if (_t_Bool_958) {
        I64 _t_I64_955 = 0;
        (void)_t_I64_955;
        I64 _t_I64_956 = I64_sub(_t_I64_955, DEREF(a));
        (void)_t_I64_956;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_956; return _r; }
    }
    ;
    I64 _t_I64_959 = I64_clone(a);
    (void)_t_I64_959;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_959; return _r; }
}

U64 I64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I64 *au = a;
    (void)au;
    I64 *bu = b;
    (void)bu;
    Bool _t_Bool_962 = I64_lte(au, bu);
    (void)_t_Bool_962;
    if (_t_Bool_962) {
        I64 _t_I64_960 = I64_sub(DEREF(bu), DEREF(au));
        (void)_t_I64_960;
        U64 _t_U64_961 = I64_to_u64(_t_I64_960);
        (void)_t_U64_961;
        ;
        ;
        return _t_U64_961;
    }
    ;
    I64 _t_I64_963 = I64_sub(DEREF(au), DEREF(bu));
    (void)_t_I64_963;
    U64 _t_U64_964 = I64_to_u64(_t_I64_963);
    (void)_t_U64_964;
    ;
    return _t_U64_964;
}

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_965 = 8;
    (void)_t_I64_965;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_965; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_966 = 0;
    (void)_t_I64_966;
    I64 _t_I64_967 = 1;
    (void)_t_I64_967;
    I64 _t_I64_968 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_968;
    I64 _t_I64_969 = I64_sub(_t_I64_966, _t_I64_967);
    (void)_t_I64_969;
    ;
    ;
    Bool _t_Bool_970 = I64_eq(_t_I64_968, _t_I64_969);
    (void)_t_Bool_970;
    ;
    ;
    return _t_Bool_970;
}

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_971 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_971;
    I64 _t_I64_972 = 1;
    (void)_t_I64_972;
    Bool _t_Bool_973 = I64_eq(_t_I64_971, _t_I64_972);
    (void)_t_Bool_973;
    ;
    ;
    return _t_Bool_973;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_974 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_974;
    Bool _t_Bool_975 = not(_t_Bool_974);
    (void)_t_Bool_975;
    ;
    return _t_Bool_975;
}

Bool I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_976 = I64_gt(a, b);
    (void)_t_Bool_976;
    Bool _t_Bool_977 = not(_t_Bool_976);
    (void)_t_Bool_977;
    ;
    return _t_Bool_977;
}

Bool I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_978 = I64_lt(a, b);
    (void)_t_Bool_978;
    Bool _t_Bool_979 = not(_t_Bool_978);
    (void)_t_Bool_979;
    ;
    return _t_Bool_979;
}

Str * Bool_to_str(Bool * b) {
    (void)b;
    if (DEREF(b)) {
        Str *_t_Str_980 = Str_lit("true", 4ULL);
        (void)_t_Str_980;
        return _t_Str_980;
    } else {
        Str *_t_Str_981 = Str_lit("false", 5ULL);
        (void)_t_Str_981;
        return _t_Str_981;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_986 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_986;
    if (_t_Bool_986) {
        I64 _t_I64_982 = 0;
        (void)_t_I64_982;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_982; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_983 = 0;
        (void)_t_I64_983;
        I64 _t_I64_984 = 1;
        (void)_t_I64_984;
        I64 _t_I64_985 = I64_sub(_t_I64_983, _t_I64_984);
        (void)_t_I64_985;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_985; return _r; }
    }
    I64 _t_I64_987 = 1;
    (void)_t_I64_987;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_987; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_988 = 1;
    (void)_t_I64_988;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_988; return _r; }
}

Bool Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_989 = 0;
    (void)_t_I64_989;
    I64 _t_I64_990 = 1;
    (void)_t_I64_990;
    I64 _t_I64_991; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_991 = *_hp; free(_hp); }
    (void)_t_I64_991;
    I64 _t_I64_992 = I64_sub(_t_I64_989, _t_I64_990);
    (void)_t_I64_992;
    ;
    ;
    Bool _t_Bool_993 = I64_eq(_t_I64_991, _t_I64_992);
    (void)_t_Bool_993;
    ;
    ;
    return _t_Bool_993;
}

Bool Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_994; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_994 = *_hp; free(_hp); }
    (void)_t_I64_994;
    I64 _t_I64_995 = 1;
    (void)_t_I64_995;
    Bool _t_Bool_996 = I64_eq(_t_I64_994, _t_I64_995);
    (void)_t_Bool_996;
    ;
    ;
    return _t_Bool_996;
}

Bool Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_997 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_997;
    Bool _t_Bool_998 = not(_t_Bool_997);
    (void)_t_Bool_998;
    ;
    return _t_Bool_998;
}

Bool Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_999 = Bool_gt(a, b);
    (void)_t_Bool_999;
    Bool _t_Bool_1000 = not(_t_Bool_999);
    (void)_t_Bool_1000;
    ;
    return _t_Bool_1000;
}

Bool Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1001 = Bool_lt(a, b);
    (void)_t_Bool_1001;
    Bool _t_Bool_1002 = not(_t_Bool_1001);
    (void)_t_Bool_1002;
    ;
    return _t_Bool_1002;
}

Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    Bool _t_Bool_1009 = Str_is_empty(elem_type);
    (void)_t_Bool_1009;
    if (_t_Bool_1009) {
        Str *_t_Str_1003 = Str_lit("Str", 3ULL);
        (void)_t_Str_1003;
        U32 _t_U32_1004 = 16;
        (void)_t_U32_1004;
        U32 _t_U32_1005 = 1;
        (void)_t_U32_1005;
        Array *_va_Array_16 = Array_new(_t_Str_1003, &_t_U32_1004, &_t_U32_1005);
        (void)_va_Array_16;
        Str_delete(_t_Str_1003, &(Bool){1});
        ;
        ;
        U32 _t_U32_1006 = 0;
        (void)_t_U32_1006;
        Str *_t_Str_1007 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_1007;
        Array_set(_va_Array_16, &_t_U32_1006, _t_Str_1007);
        ;
        Str *_t_Str_1008 = Str_lit("./src/core/array.til:22:41", 26ULL);
        (void)_t_Str_1008;
        panic(_t_Str_1008, _va_Array_16);
        Str_delete(_t_Str_1008, &(Bool){1});
    }
    ;
    void * _t_v_1010 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t_v_1010;
    void * _t_v_1011 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1011;
    void * _t_v_1012 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1012;
    Array *_t_Array_1013 = malloc(sizeof(Array));
    _t_Array_1013->data = _t_v_1010;
    _t_Array_1013->cap = DEREF(cap);
    _t_Array_1013->elem_size = DEREF(elem_size);
    { Str *_ca = Str_clone(elem_type); _t_Array_1013->elem_type = *_ca; free(_ca); }
    _t_Array_1013->elem_clone = _t_v_1011;
    _t_Array_1013->elem_delete = _t_v_1012;
    (void)_t_Array_1013;
    return _t_Array_1013;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_1028 = U32_gte(i, &self->cap);
    (void)_t_Bool_1028;
    if (_t_Bool_1028) {
        Str *_t_Str_1014 = Str_lit("Str", 3ULL);
        (void)_t_Str_1014;
        U32 _t_U32_1015 = 16;
        (void)_t_U32_1015;
        U32 _t_U32_1016 = 5;
        (void)_t_U32_1016;
        Array *_va_Array_17 = Array_new(_t_Str_1014, &_t_U32_1015, &_t_U32_1016);
        (void)_va_Array_17;
        Str_delete(_t_Str_1014, &(Bool){1});
        ;
        ;
        U32 _t_U32_1017 = 0;
        (void)_t_U32_1017;
        Str *_t_Str_1018 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_1018;
        Array_set(_va_Array_17, &_t_U32_1017, _t_Str_1018);
        ;
        U32 _t_U32_1019 = 1;
        (void)_t_U32_1019;
        Str *_t_Str_1020 = U32_to_str(i);
        (void)_t_Str_1020;
        Array_set(_va_Array_17, &_t_U32_1019, _t_Str_1020);
        ;
        U32 _t_U32_1021 = 2;
        (void)_t_U32_1021;
        Str *_t_Str_1022 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1022;
        Array_set(_va_Array_17, &_t_U32_1021, _t_Str_1022);
        ;
        U32 _t_U32_1023 = 3;
        (void)_t_U32_1023;
        Str *_t_Str_1024 = U32_to_str(&self->cap);
        (void)_t_Str_1024;
        Array_set(_va_Array_17, &_t_U32_1023, _t_Str_1024);
        ;
        U32 _t_U32_1025 = 4;
        (void)_t_U32_1025;
        Str *_t_Str_1026 = Str_lit(")", 1ULL);
        (void)_t_Str_1026;
        Array_set(_va_Array_17, &_t_U32_1025, _t_Str_1026);
        ;
        Str *_t_Str_1027 = Str_lit("./src/core/array.til:34:19", 26ULL);
        (void)_t_Str_1027;
        panic(_t_Str_1027, _va_Array_17);
        Str_delete(_t_Str_1027, &(Bool){1});
    }
    ;
    U32 _t_U64_1029 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1029;
    void *_t_v_1030 = ptr_add(self->data, _t_U64_1029);
    (void)_t_v_1030;
    ;
    return _t_v_1030;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_1045 = U32_gte(i, &self->cap);
    (void)_t_Bool_1045;
    if (_t_Bool_1045) {
        Str *_t_Str_1031 = Str_lit("Str", 3ULL);
        (void)_t_Str_1031;
        U32 _t_U32_1032 = 16;
        (void)_t_U32_1032;
        U32 _t_U32_1033 = 5;
        (void)_t_U32_1033;
        Array *_va_Array_18 = Array_new(_t_Str_1031, &_t_U32_1032, &_t_U32_1033);
        (void)_va_Array_18;
        Str_delete(_t_Str_1031, &(Bool){1});
        ;
        ;
        U32 _t_U32_1034 = 0;
        (void)_t_U32_1034;
        Str *_t_Str_1035 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_1035;
        Array_set(_va_Array_18, &_t_U32_1034, _t_Str_1035);
        ;
        U32 _t_U32_1036 = 1;
        (void)_t_U32_1036;
        Str *_t_Str_1037 = U32_to_str(i);
        (void)_t_Str_1037;
        Array_set(_va_Array_18, &_t_U32_1036, _t_Str_1037);
        ;
        U32 _t_U32_1038 = 2;
        (void)_t_U32_1038;
        Str *_t_Str_1039 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1039;
        Array_set(_va_Array_18, &_t_U32_1038, _t_Str_1039);
        ;
        U32 _t_U32_1040 = 3;
        (void)_t_U32_1040;
        Str *_t_Str_1041 = U32_to_str(&self->cap);
        (void)_t_Str_1041;
        Array_set(_va_Array_18, &_t_U32_1040, _t_Str_1041);
        ;
        U32 _t_U32_1042 = 4;
        (void)_t_U32_1042;
        Str *_t_Str_1043 = Str_lit(")", 1ULL);
        (void)_t_Str_1043;
        Array_set(_va_Array_18, &_t_U32_1042, _t_Str_1043);
        ;
        Str *_t_Str_1044 = Str_lit("./src/core/array.til:43:19", 26ULL);
        (void)_t_Str_1044;
        panic(_t_Str_1044, _va_Array_18);
        Str_delete(_t_Str_1044, &(Bool){1});
    }
    ;
    U32 _t_U64_1046 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1046;
    void *_t_v_1047 = ptr_add(self->data, _t_U64_1046);
    (void)_t_v_1047;
    Bool _t_Bool_1048 = 0;
    (void)_t_Bool_1048;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1047, &_t_Bool_1048);
    ;
    ;
    U32 _t_U64_1049 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1049;
    void *_t_v_1050 = ptr_add(self->data, _t_U64_1049);
    (void)_t_v_1050;
    memcpy(_t_v_1050, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_1051 = self->cap;
        (void)_re_U32_1051;
        U32 _rc_U32_1051 = 0;
        (void)_rc_U32_1051;
        Bool _t_Bool_1060 = U32_lte(&_rc_U32_1051, &_re_U32_1051);
        (void)_t_Bool_1060;
        if (_t_Bool_1060) {
            while (1) {
                Bool _wcond_Bool_1052 = U32_lt(&_rc_U32_1051, &_re_U32_1051);
                (void)_wcond_Bool_1052;
                if (_wcond_Bool_1052) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1051);
                (void)i;
                U32_inc(&_rc_U32_1051);
                U32 _t_U64_1053 = U32_mul(i, self->elem_size);
                (void)_t_U64_1053;
                ;
                void *_t_v_1054 = ptr_add(self->data, _t_U64_1053);
                (void)_t_v_1054;
                Bool _t_Bool_1055 = 0;
                (void)_t_Bool_1055;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1054, &_t_Bool_1055);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1056 = U32_gt(&_rc_U32_1051, &_re_U32_1051);
                (void)_wcond_Bool_1056;
                if (_wcond_Bool_1056) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1051);
                (void)i;
                U32_dec(&_rc_U32_1051);
                U32 _t_U64_1057 = U32_mul(i, self->elem_size);
                (void)_t_U64_1057;
                ;
                void *_t_v_1058 = ptr_add(self->data, _t_U64_1057);
                (void)_t_v_1058;
                Bool _t_Bool_1059 = 0;
                (void)_t_Bool_1059;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1058, &_t_Bool_1059);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_1061 = 0;
    (void)_t_Bool_1061;
    Str_delete(&self->elem_type, &_t_Bool_1061);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_1074 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_1074;
    void * new_data = malloc(_t_U64_1074);
    (void)new_data;
    ;
    {
        U32 _re_U32_1062 = self->cap;
        (void)_re_U32_1062;
        U32 _rc_U32_1062 = 0;
        (void)_rc_U32_1062;
        Bool _t_Bool_1073 = U32_lte(&_rc_U32_1062, &_re_U32_1062);
        (void)_t_Bool_1073;
        if (_t_Bool_1073) {
            while (1) {
                Bool _wcond_Bool_1063 = U32_lt(&_rc_U32_1062, &_re_U32_1062);
                (void)_wcond_Bool_1063;
                if (_wcond_Bool_1063) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1062);
                (void)i;
                U32_inc(&_rc_U32_1062);
                U32 _t_U64_1064 = U32_mul(i, self->elem_size);
                (void)_t_U64_1064;
                void *_t_v_1065 = ptr_add(self->data, _t_U64_1064);
                (void)_t_v_1065;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1065);
                (void)cloned;
                ;
                U32 _t_U64_1066 = U32_mul(i, self->elem_size);
                (void)_t_U64_1066;
                ;
                void *_t_v_1067 = ptr_add(new_data, _t_U64_1066);
                (void)_t_v_1067;
                memcpy(_t_v_1067, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1068 = U32_gt(&_rc_U32_1062, &_re_U32_1062);
                (void)_wcond_Bool_1068;
                if (_wcond_Bool_1068) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1062);
                (void)i;
                U32_dec(&_rc_U32_1062);
                U32 _t_U64_1069 = U32_mul(i, self->elem_size);
                (void)_t_U64_1069;
                void *_t_v_1070 = ptr_add(self->data, _t_U64_1069);
                (void)_t_v_1070;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1070);
                (void)cloned;
                ;
                U32 _t_U64_1071 = U32_mul(i, self->elem_size);
                (void)_t_U64_1071;
                ;
                void *_t_v_1072 = ptr_add(new_data, _t_U64_1071);
                (void)_t_v_1072;
                memcpy(_t_v_1072, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_1075 = malloc(sizeof(Array));
    _t_Array_1075->data = new_data;
    _t_Array_1075->cap = self->cap;
    _t_Array_1075->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_1075->elem_type = *_ca; free(_ca); }
    _t_Array_1075->elem_clone = (void *)self->elem_clone;
    _t_Array_1075->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_1075;
    return _t_Array_1075;
}

U32 Array_size(void) {
    I64 _t_I64_1076 = 48;
    (void)_t_I64_1076;
    return _t_I64_1076;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2710 = Str_lit("Str", 3ULL);
    (void)_t_Str_2710;
    U32 _t_U32_2711 = 16;
    (void)_t_U32_2711;
    U32 _t_U32_2712 = 3;
    (void)_t_U32_2712;
    Array *_va_Array_92 = Array_new(_t_Str_2710, &_t_U32_2711, &_t_U32_2712);
    (void)_va_Array_92;
    Str_delete(_t_Str_2710, &(Bool){1});
    ;
    ;
    U32 _t_U32_2713 = 0;
    (void)_t_U32_2713;
    Str *_t_Str_2714 = Str_clone(loc_str);
    (void)_t_Str_2714;
    Array_set(_va_Array_92, &_t_U32_2713, _t_Str_2714);
    ;
    U32 _t_U32_2715 = 1;
    (void)_t_U32_2715;
    Str *_t_Str_2716 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2716;
    Array_set(_va_Array_92, &_t_U32_2715, _t_Str_2716);
    ;
    Array *_t_Array_2717 = Array_clone(parts);
    (void)_t_Array_2717;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2718 = 2;
    (void)_t_U32_2718;
    Str *_t_Str_2719 = format(_t_Array_2717);
    (void)_t_Str_2719;
    Array_set(_va_Array_92, &_t_U32_2718, _t_Str_2719);
    ;
    println(_va_Array_92);
    I64 _t_I64_2720 = 1;
    (void)_t_I64_2720;
    exit(_t_I64_2720);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2739 = not(DEREF(cond));
    (void)_t_Bool_2739;
    if (_t_Bool_2739) {
        Str *_t_Str_2734 = Str_lit("Str", 3ULL);
        (void)_t_Str_2734;
        U32 _t_U32_2735 = 16;
        (void)_t_U32_2735;
        U32 _t_U32_2736 = 1;
        (void)_t_U32_2736;
        Array *_va_Array_95 = Array_new(_t_Str_2734, &_t_U32_2735, &_t_U32_2736);
        (void)_va_Array_95;
        Str_delete(_t_Str_2734, &(Bool){1});
        ;
        ;
        U32 _t_U32_2737 = 0;
        (void)_t_U32_2737;
        Str *_t_Str_2738 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2738;
        Array_set(_va_Array_95, &_t_U32_2737, _t_Str_2738);
        ;
        panic(loc_str, _va_Array_95);
    }
    ;
    Bool _t_Bool_2740 = 1;
    (void)_t_Bool_2740;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2740; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2763 = I64_neq(a, b);
    (void)_t_Bool_2763;
    if (_t_Bool_2763) {
        Str *_t_Str_2750 = Str_lit("Str", 3ULL);
        (void)_t_Str_2750;
        U32 _t_U32_2751 = 16;
        (void)_t_U32_2751;
        U32 _t_U32_2752 = 5;
        (void)_t_U32_2752;
        Array *_va_Array_97 = Array_new(_t_Str_2750, &_t_U32_2751, &_t_U32_2752);
        (void)_va_Array_97;
        Str_delete(_t_Str_2750, &(Bool){1});
        ;
        ;
        U32 _t_U32_2753 = 0;
        (void)_t_U32_2753;
        Str *_t_Str_2754 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2754;
        Array_set(_va_Array_97, &_t_U32_2753, _t_Str_2754);
        ;
        U32 _t_U32_2755 = 1;
        (void)_t_U32_2755;
        Str *_t_Str_2756 = I64_to_str(a);
        (void)_t_Str_2756;
        Array_set(_va_Array_97, &_t_U32_2755, _t_Str_2756);
        ;
        U32 _t_U32_2757 = 2;
        (void)_t_U32_2757;
        Str *_t_Str_2758 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2758;
        Array_set(_va_Array_97, &_t_U32_2757, _t_Str_2758);
        ;
        U32 _t_U32_2759 = 3;
        (void)_t_U32_2759;
        Str *_t_Str_2760 = I64_to_str(b);
        (void)_t_Str_2760;
        Array_set(_va_Array_97, &_t_U32_2759, _t_Str_2760);
        ;
        U32 _t_U32_2761 = 4;
        (void)_t_U32_2761;
        Str *_t_Str_2762 = Str_lit("'", 1ULL);
        (void)_t_Str_2762;
        Array_set(_va_Array_97, &_t_U32_2761, _t_Str_2762);
        ;
        panic(loc_str, _va_Array_97);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2779 = parts;
        (void)_fc_Array_2779;
        U32 _fi_USize_2779 = 0;
        (void)_fi_USize_2779;
        while (1) {
            U32 _t_U32_2781; { U32 *_hp = (U32 *)Array_len(_fc_Array_2779); _t_U32_2781 = *_hp; free(_hp); }
            (void)_t_U32_2781;
            Bool _wcond_Bool_2780 = U32_lt(&_fi_USize_2779, &_t_U32_2781);
            (void)_wcond_Bool_2780;
            ;
            if (_wcond_Bool_2780) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2779, &_fi_USize_2779);
            (void)s;
            U32 _t_U32_2782 = 1;
            (void)_t_U32_2782;
            U32 _t_U32_2783 = U32_add(_fi_USize_2779, _t_U32_2782);
            (void)_t_U32_2783;
            ;
            _fi_USize_2779 = _t_U32_2783;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

void test_simple_add(void) {
    I64 _t_I64_2975 = 1;
    (void)_t_I64_2975;
    I64 _t_I64_2976 = 2;
    (void)_t_I64_2976;
    I64 result = 3;
    (void)result;
    ;
    ;
    Str *_t_Str_2977 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_2977;
    I64 _t_I64_2978 = 3;
    (void)_t_I64_2978;
    assert_eq(_t_Str_2977, &result, &_t_I64_2978);
    ;
    Str_delete(_t_Str_2977, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 _t_I64_2979 = 1;
    (void)_t_I64_2979;
    I64 _t_I64_2980 = 2;
    (void)_t_I64_2980;
    I64 _t_I64_2981 = 10;
    (void)_t_I64_2981;
    I64 _t_I64_2982 = 5;
    (void)_t_I64_2982;
    I64 _t_I64_2983 = 3;
    (void)_t_I64_2983;
    ;
    ;
    I64 _t_I64_2984 = 5;
    (void)_t_I64_2984;
    ;
    ;
    I64 result = 15;
    (void)result;
    ;
    ;
    Str *_t_Str_2985 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_2985;
    I64 _t_I64_2986 = 15;
    (void)_t_I64_2986;
    assert_eq(_t_Str_2985, &result, &_t_I64_2986);
    ;
    Str_delete(_t_Str_2985, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 _t_I64_2987 = 2;
    (void)_t_I64_2987;
    I64 _t_I64_2988 = 3;
    (void)_t_I64_2988;
    I64 _t_I64_2989 = 4;
    (void)_t_I64_2989;
    I64 _t_I64_2990 = 5;
    (void)_t_I64_2990;
    I64 _t_I64_2991 = 6;
    (void)_t_I64_2991;
    ;
    ;
    I64 _t_I64_2992 = 20;
    (void)_t_I64_2992;
    ;
    ;
    I64 result = 26;
    (void)result;
    ;
    ;
    Str *_t_Str_2993 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_2993;
    I64 _t_I64_2994 = 26;
    (void)_t_I64_2994;
    assert_eq(_t_Str_2993, &result, &_t_I64_2994);
    ;
    Str_delete(_t_Str_2993, &(Bool){1});
    ;
}

Str * poem(I64 * depth, Str * current, Str * s1, Str * s2) {
    (void)depth;
    (void)current;
    (void)s1;
    (void)s2;
    I64 _t_I64_3002 = 4;
    (void)_t_I64_3002;
    Bool _t_Bool_3003 = I64_eq(DEREF(depth), _t_I64_3002);
    (void)_t_Bool_3003;
    ;
    if (_t_Bool_3003) {
        Str *_t_Str_2995 = Str_lit("\n", 2ULL);
        (void)_t_Str_2995;
        Str *_t_Str_2996 = Str_concat(current, _t_Str_2995);
        (void)_t_Str_2996;
        Str_delete(_t_Str_2995, &(Bool){1});
        ;
        return _t_Str_2996;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    I64 _t_I64_3004 = 1;
    (void)_t_I64_3004;
    I64 _t_I64_3005 = I64_add(DEREF(depth), _t_I64_3004);
    (void)_t_I64_3005;
    ;
    Str *_t_Str_3006 = Str_concat(current, s1);
    (void)_t_Str_3006;
    Str *_t_Str_3007 = poem(&_t_I64_3005, _t_Str_3006, s1, s2);
    (void)_t_Str_3007;
    ;
    Str_delete(_t_Str_3006, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_3007); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_3007, &(Bool){1});
    I64 _t_I64_3008 = 1;
    (void)_t_I64_3008;
    I64 _t_I64_3009 = I64_add(DEREF(depth), _t_I64_3008);
    (void)_t_I64_3009;
    ;
    Str *_t_Str_3010 = Str_concat(current, s2);
    (void)_t_Str_3010;
    Str *_t_Str_3011 = poem(&_t_I64_3009, _t_Str_3010, s1, s2);
    (void)_t_Str_3011;
    ;
    Str_delete(_t_Str_3010, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_3011); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_3011, &(Bool){1});
    I64 _t_I64_3012 = 2;
    (void)_t_I64_3012;
    Bool _t_Bool_3013 = I64_eq(DEREF(depth), _t_I64_3012);
    (void)_t_Bool_3013;
    ;
    if (_t_Bool_3013) {
        I64 _t_I64_2997 = 1;
        (void)_t_I64_2997;
        Str *_t_Str_2998 = Str_lit("lei", 3ULL);
        (void)_t_Str_2998;
        I64 _t_I64_2999 = I64_add(DEREF(depth), _t_I64_2997);
        (void)_t_I64_2999;
        ;
        Str *_t_Str_3000 = Str_concat(current, _t_Str_2998);
        (void)_t_Str_3000;
        Str_delete(_t_Str_2998, &(Bool){1});
        Str *_t_Str_3001 = poem(&_t_I64_2999, _t_Str_3000, s1, s2);
        (void)_t_Str_3001;
        ;
        Str_delete(_t_Str_3000, &(Bool){1});
        { Str *_old = result; result = Str_concat(result, _t_Str_3001); Str_delete(_old, &(Bool){1}); }
        Str_delete(_t_Str_3001, &(Bool){1});
    }
    ;
    return result;
}

Str * make_poem(Str * s1, Str * s2) {
    (void)s1;
    (void)s2;
    I64 _t_I64_3014 = 0;
    (void)_t_I64_3014;
    Str *_t_Str_3015 = Str_lit("", 0ULL);
    (void)_t_Str_3015;
    Str *_t_Str_3016 = poem(&_t_I64_3014, _t_Str_3015, s1, s2);
    (void)_t_Str_3016;
    ;
    Str_delete(_t_Str_3015, &(Bool){1});
    return _t_Str_3016;
}

void test_lolalalo(void) {
    Str *_t_Str_3017 = Str_lit("lo", 2ULL);
    (void)_t_Str_3017;
    Str *_t_Str_3018 = Str_lit("la", 2ULL);
    (void)_t_Str_3018;
    Str *lo_la = make_poem(_t_Str_3017, _t_Str_3018);
    (void)lo_la;
    Str_delete(_t_Str_3017, &(Bool){1});
    Str_delete(_t_Str_3018, &(Bool){1});
    Str *_t_Str_3019 = Str_lit("la", 2ULL);
    (void)_t_Str_3019;
    Str *_t_Str_3020 = Str_lit("lo", 2ULL);
    (void)_t_Str_3020;
    Str *la_lo = make_poem(_t_Str_3019, _t_Str_3020);
    (void)la_lo;
    Str_delete(_t_Str_3019, &(Bool){1});
    Str_delete(_t_Str_3020, &(Bool){1});
    Str *_t_Str_3021 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_3021;
    Str *_t_Str_3022 = Str_lit("src/test/constfold.til:56:12", 28ULL);
    (void)_t_Str_3022;
    Bool _t_Bool_3023 = Str_contains(lo_la, _t_Str_3021);
    (void)_t_Bool_3023;
    Str_delete(_t_Str_3021, &(Bool){1});
    Bool _t_Bool_3024; { Bool *_hp = (Bool *)assert(_t_Str_3022, &_t_Bool_3023); _t_Bool_3024 = *_hp; free(_hp); }
    (void)_t_Bool_3024;
    ;
    ;
    Str_delete(_t_Str_3022, &(Bool){1});
    Str *_t_Str_3025 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_3025;
    Str *_t_Str_3026 = Str_lit("src/test/constfold.til:57:12", 28ULL);
    (void)_t_Str_3026;
    Bool _t_Bool_3027 = Str_contains(la_lo, _t_Str_3025);
    (void)_t_Bool_3027;
    Str_delete(_t_Str_3025, &(Bool){1});
    Bool _t_Bool_3028; { Bool *_hp = (Bool *)assert(_t_Str_3026, &_t_Bool_3027); _t_Bool_3028 = *_hp; free(_hp); }
    (void)_t_Bool_3028;
    ;
    ;
    Str_delete(_t_Str_3026, &(Bool){1});
    Str *_t_Str_3029 = Str_lit("lolei", 5ULL);
    (void)_t_Str_3029;
    Str *_t_Str_3030 = Str_lit("src/test/constfold.til:59:12", 28ULL);
    (void)_t_Str_3030;
    Bool _t_Bool_3031 = Str_contains(lo_la, _t_Str_3029);
    (void)_t_Bool_3031;
    Str_delete(_t_Str_3029, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    Bool _t_Bool_3032; { Bool *_hp = (Bool *)assert(_t_Str_3030, &_t_Bool_3031); _t_Bool_3032 = *_hp; free(_hp); }
    (void)_t_Bool_3032;
    ;
    ;
    Str_delete(_t_Str_3030, &(Bool){1});
    Str *_t_Str_3033 = Str_lit("lalei", 5ULL);
    (void)_t_Str_3033;
    Str *_t_Str_3034 = Str_lit("src/test/constfold.til:60:12", 28ULL);
    (void)_t_Str_3034;
    Bool _t_Bool_3035 = Str_contains(la_lo, _t_Str_3033);
    (void)_t_Bool_3035;
    Str_delete(_t_Str_3033, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    Bool _t_Bool_3036; { Bool *_hp = (Bool *)assert(_t_Str_3034, &_t_Bool_3035); _t_Bool_3036 = *_hp; free(_hp); }
    (void)_t_Bool_3036;
    ;
    ;
    Str_delete(_t_Str_3034, &(Bool){1});
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return 8;
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
    I64 _t_I64_849 = 0;
    (void)_t_I64_849;
    I64 _t_I64_850 = 1;
    (void)_t_I64_850;
    I64 _t_I64_851 = I64_sub(_t_I64_849, _t_I64_850);
    (void)_t_I64_851;
    CAP_LIT = I64_to_usize(_t_I64_851);
    (void)CAP_LIT;
    I64 _t_I64_852 = 0;
    (void)_t_I64_852;
    I64 _t_I64_853 = 2;
    (void)_t_I64_853;
    I64 _t_I64_854 = I64_sub(_t_I64_852, _t_I64_853);
    (void)_t_I64_854;
    CAP_VIEW = I64_to_usize(_t_I64_854);
    (void)CAP_VIEW;
    __til_docs_blob__ = (Str){.c_str=(U8*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)__til_docs_blob__;
    __til_info_blob__ = (Str){.c_str=(U8*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)__til_info_blob__;
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
