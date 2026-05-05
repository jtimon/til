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
Array * Array_new(Str * elem_type, U32 * cap);
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
Array * Array_new(Str * elem_type, U32 * cap);
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
    Bool _t_Bool_153 = Str_is_empty(elem_type);
    (void)_t_Bool_153;
    if (_t_Bool_153) {
        Str *_t_Str_142 = Str_lit("Str", 3ULL);
        (void)_t_Str_142;
        U32 _t_U32_143 = 1;
        (void)_t_U32_143;
        Array *_va_Array_0 = Array_new(_t_Str_142, &_t_U32_143);
        (void)_va_Array_0;
        Str_delete(_t_Str_142, &(Bool){1});
        ;
        U32 _t_U32_144 = 0;
        (void)_t_U32_144;
        Str *_t_Str_145 = Str_lit("Vec.new: elem_type required", 27ULL);
        (void)_t_Str_145;
        Array_set(_va_Array_0, &_t_U32_144, _t_Str_145);
        ;
        Str *_t_Str_146 = Str_lit("./src/core/vec.til:24:19", 24ULL);
        (void)_t_Str_146;
        panic(_t_Str_146, _va_Array_0);
        Str_delete(_t_Str_146, &(Bool){1});
    }
    ;
    Str *_t_Str_154 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_154;
    Bool _t_Bool_155 = Str_eq(elem_type, _t_Str_154);
    (void)_t_Bool_155;
    Str_delete(_t_Str_154, &(Bool){1});
    if (_t_Bool_155) {
        U64 _t_U64_147 = 8;
        (void)_t_U64_147;
        void * _t_v_148 = malloc(_t_U64_147);
        (void)_t_v_148;
        ;
        U32 _t_U32_149 = 0;
        (void)_t_U32_149;
        I64 _t_I64_150 = 1;
        (void)_t_I64_150;
        I64 _t_I64_151 = 8;
        (void)_t_I64_151;
        Vec *_t_Vec_152 = malloc(sizeof(Vec));
        _t_Vec_152->data = _t_v_148;
        _t_Vec_152->count = _t_U32_149;
        _t_Vec_152->cap = _t_I64_150;
        _t_Vec_152->elem_size = _t_I64_151;
        { Str *_ca = Str_clone(elem_type); _t_Vec_152->elem_type = *_ca; free(_ca); }
        _t_Vec_152->elem_clone = (void *)(void *)default_clone;
        _t_Vec_152->elem_delete = (void *)(void *)default_delete;
        (void)_t_Vec_152;
        ;
        ;
        ;
        ;
        return _t_Vec_152;
    }
    ;
    U32 sz = dyn_size_of(elem_type);
    (void)sz;
    void * _t_v_156 = malloc(sz);
    (void)_t_v_156;
    U32 _t_U32_157 = 0;
    (void)_t_U32_157;
    I64 _t_I64_158 = 1;
    (void)_t_I64_158;
    void * _t_v_159 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_159;
    void * _t_v_160 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_160;
    Vec *_t_Vec_161 = malloc(sizeof(Vec));
    _t_Vec_161->data = _t_v_156;
    _t_Vec_161->count = _t_U32_157;
    _t_Vec_161->cap = _t_I64_158;
    _t_Vec_161->elem_size = sz;
    { Str *_ca = Str_clone(elem_type); _t_Vec_161->elem_type = *_ca; free(_ca); }
    _t_Vec_161->elem_clone = _t_v_159;
    _t_Vec_161->elem_delete = _t_v_160;
    (void)_t_Vec_161;
    ;
    ;
    ;
    return _t_Vec_161;
}

U32 Vec_len(Vec * self) {
    (void)self;
    return self->count;
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t_Bool_166 = U32_eq(self->count, self->cap);
    (void)_t_Bool_166;
    if (_t_Bool_166) {
        U32 _t_U32_162 = 2;
        (void)_t_U32_162;
        U32 new_cap = U32_mul(self->cap, _t_U32_162);
        (void)new_cap;
        ;
        U32 _t_U64_163 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_163;
        void * _t_v_164 = realloc(self->data, _t_U64_163);
        (void)_t_v_164;
        ;
        self->data = _t_v_164;
        U32 _t_U32_165 = U32_clone(&new_cap);
        (void)_t_U32_165;
        ;
        self->cap = _t_U32_165;
        ;
    }
    ;
    U32 _t_U64_167 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_167;
    void *_t_v_168 = ptr_add(self->data, _t_U64_167);
    (void)_t_v_168;
    memcpy(_t_v_168, val, self->elem_size);
    ;
    free(val);
    U32 _t_U32_169 = 1;
    (void)_t_U32_169;
    U32 _t_U32_170 = U32_add(self->count, _t_U32_169);
    (void)_t_U32_170;
    ;
    self->count = _t_U32_170;
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
        Str *_t_Str_171 = Str_lit("Str", 3ULL);
        (void)_t_Str_171;
        U32 _t_U32_172 = 1;
        (void)_t_U32_172;
        Array *_va_Array_1 = Array_new(_t_Str_171, &_t_U32_172);
        (void)_va_Array_1;
        Str_delete(_t_Str_171, &(Bool){1});
        ;
        U32 _t_U32_173 = 0;
        (void)_t_U32_173;
        Str *_t_Str_174 = Str_lit("Vec.append: incompatible vecs", 29ULL);
        (void)_t_Str_174;
        Array_set(_va_Array_1, &_t_U32_173, _t_Str_174);
        ;
        Str *_t_Str_175 = Str_lit("./src/core/vec.til:56:19", 24ULL);
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
    Bool _t_Bool_217 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_217;
    Bool _t_Bool_218 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_218;
    Bool _t_Bool_219 = not(_t_Bool_217);
    (void)_t_Bool_219;
    ;
    Bool _t_Bool_220 = not(_t_Bool_218);
    (void)_t_Bool_220;
    ;
    Bool _t_Bool_221 = or(_t_Bool_219, _t_Bool_220);
    (void)_t_Bool_221;
    ;
    ;
    if (_t_Bool_221) {
        Str *_t_Str_195 = Str_lit("Str", 3ULL);
        (void)_t_Str_195;
        U32 _t_U32_196 = 1;
        (void)_t_U32_196;
        Array *_va_Array_2 = Array_new(_t_Str_195, &_t_U32_196);
        (void)_va_Array_2;
        Str_delete(_t_Str_195, &(Bool){1});
        ;
        U32 _t_U32_197 = 0;
        (void)_t_U32_197;
        Str *_t_Str_198 = Str_lit("Vec.move_from: incompatible vecs", 32ULL);
        (void)_t_Str_198;
        Array_set(_va_Array_2, &_t_U32_197, _t_Str_198);
        ;
        Str *_t_Str_199 = Str_lit("./src/core/vec.til:83:19", 24ULL);
        (void)_t_Str_199;
        panic(_t_Str_199, _va_Array_2);
        Str_delete(_t_Str_199, &(Bool){1});
    }
    ;
    Bool _t_Bool_222 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_222;
    Str *_t_Str_223 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_223;
    Bool _t_Bool_224 = Str_eq(&self->elem_type, _t_Str_223);
    (void)_t_Bool_224;
    Str_delete(_t_Str_223, &(Bool){1});
    Bool _t_Bool_225 = not(_t_Bool_222);
    (void)_t_Bool_225;
    ;
    Bool _t_Bool_226 = not(_t_Bool_224);
    (void)_t_Bool_226;
    ;
    Bool _t_Bool_227 = and(_t_Bool_225, _t_Bool_226);
    (void)_t_Bool_227;
    ;
    ;
    if (_t_Bool_227) {
        {
            U32 _re_U32_200 = self->count;
            (void)_re_U32_200;
            U32 _rc_U32_200 = 0;
            (void)_rc_U32_200;
            Bool _t_Bool_209 = U32_lte(&_rc_U32_200, &_re_U32_200);
            (void)_t_Bool_209;
            if (_t_Bool_209) {
                while (1) {
                    Bool _wcond_Bool_201 = U32_lt(&_rc_U32_200, &_re_U32_200);
                    (void)_wcond_Bool_201;
                    if (_wcond_Bool_201) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_200);
                    (void)i;
                    U32_inc(&_rc_U32_200);
                    U32 _t_U64_202 = U32_mul(i, self->elem_size);
                    (void)_t_U64_202;
                    ;
                    void *_t_v_203 = ptr_add(self->data, _t_U64_202);
                    (void)_t_v_203;
                    Bool _t_Bool_204 = 0;
                    (void)_t_Bool_204;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_203, &_t_Bool_204);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_205 = U32_gt(&_rc_U32_200, &_re_U32_200);
                    (void)_wcond_Bool_205;
                    if (_wcond_Bool_205) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_200);
                    (void)i;
                    U32_dec(&_rc_U32_200);
                    U32 _t_U64_206 = U32_mul(i, self->elem_size);
                    (void)_t_U64_206;
                    ;
                    void *_t_v_207 = ptr_add(self->data, _t_U64_206);
                    (void)_t_v_207;
                    Bool _t_Bool_208 = 0;
                    (void)_t_Bool_208;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_207, &_t_Bool_208);
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
    Bool _t_Bool_228 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_228;
    if (_t_Bool_228) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_210 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_210;
            if (_wcond_Bool_210) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_211 = 2;
            (void)_t_U32_211;
            U32 _t_U32_212 = U32_mul(new_cap, _t_U32_211);
            (void)_t_U32_212;
            ;
            new_cap = _t_U32_212;
            ;
        }
        U32 _t_U64_213 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_213;
        void * _t_v_214 = realloc(self->data, _t_U64_213);
        (void)_t_v_214;
        ;
        self->data = _t_v_214;
        U32 _t_U32_215 = U32_clone(&new_cap);
        (void)_t_U32_215;
        ;
        self->cap = _t_U32_215;
        ;
    }
    ;
    U32 _t_U32_229 = 0;
    (void)_t_U32_229;
    Bool _t_Bool_230 = U32_gt(&needed, &_t_U32_229);
    (void)_t_Bool_230;
    ;
    if (_t_Bool_230) {
        U32 _t_U64_216 = U32_mul(needed, self->elem_size);
        (void)_t_U64_216;
        memcpy(self->data, other->data, _t_U64_216);
        ;
    }
    ;
    U32 _t_U32_231 = U32_clone(&needed);
    (void)_t_U32_231;
    ;
    self->count = _t_U32_231;
    ;
    U32 _t_U32_232 = 0;
    (void)_t_U32_232;
    other->count = _t_U32_232;
    ;
}

void * Vec_get(Vec * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_246 = U32_gte(i, &self->count);
    (void)_t_Bool_246;
    if (_t_Bool_246) {
        Str *_t_Str_233 = Str_lit("Str", 3ULL);
        (void)_t_Str_233;
        U32 _t_U32_234 = 5;
        (void)_t_U32_234;
        Array *_va_Array_3 = Array_new(_t_Str_233, &_t_U32_234);
        (void)_va_Array_3;
        Str_delete(_t_Str_233, &(Bool){1});
        ;
        U32 _t_U32_235 = 0;
        (void)_t_U32_235;
        Str *_t_Str_236 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t_Str_236;
        Array_set(_va_Array_3, &_t_U32_235, _t_Str_236);
        ;
        U32 _t_U32_237 = 1;
        (void)_t_U32_237;
        Str *_t_Str_238 = U32_to_str(i);
        (void)_t_Str_238;
        Array_set(_va_Array_3, &_t_U32_237, _t_Str_238);
        ;
        U32 _t_U32_239 = 2;
        (void)_t_U32_239;
        Str *_t_Str_240 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_240;
        Array_set(_va_Array_3, &_t_U32_239, _t_Str_240);
        ;
        U32 _t_U32_241 = 3;
        (void)_t_U32_241;
        Str *_t_Str_242 = U32_to_str(&self->count);
        (void)_t_Str_242;
        Array_set(_va_Array_3, &_t_U32_241, _t_Str_242);
        ;
        U32 _t_U32_243 = 4;
        (void)_t_U32_243;
        Str *_t_Str_244 = Str_lit(")", 1ULL);
        (void)_t_Str_244;
        Array_set(_va_Array_3, &_t_U32_243, _t_Str_244);
        ;
        Str *_t_Str_245 = Str_lit("./src/core/vec.til:110:19", 25ULL);
        (void)_t_Str_245;
        panic(_t_Str_245, _va_Array_3);
        Str_delete(_t_Str_245, &(Bool){1});
    }
    ;
    U32 _t_U64_247 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_247;
    void *_t_v_248 = ptr_add(self->data, _t_U64_247);
    (void)_t_v_248;
    ;
    return _t_v_248;
}

void * Vec_pop(Vec * self) {
    (void)self;
    U32 _t_U32_254 = 0;
    (void)_t_U32_254;
    Bool _t_Bool_255 = U32_eq(self->count, _t_U32_254);
    (void)_t_Bool_255;
    ;
    if (_t_Bool_255) {
        Str *_t_Str_249 = Str_lit("Str", 3ULL);
        (void)_t_Str_249;
        U32 _t_U32_250 = 1;
        (void)_t_U32_250;
        Array *_va_Array_4 = Array_new(_t_Str_249, &_t_U32_250);
        (void)_va_Array_4;
        Str_delete(_t_Str_249, &(Bool){1});
        ;
        U32 _t_U32_251 = 0;
        (void)_t_U32_251;
        Str *_t_Str_252 = Str_lit("Vec.pop: empty vec", 18ULL);
        (void)_t_Str_252;
        Array_set(_va_Array_4, &_t_U32_251, _t_Str_252);
        ;
        Str *_t_Str_253 = Str_lit("./src/core/vec.til:119:19", 25ULL);
        (void)_t_Str_253;
        panic(_t_Str_253, _va_Array_4);
        Str_delete(_t_Str_253, &(Bool){1});
    }
    ;
    U32 _t_U32_256 = 1;
    (void)_t_U32_256;
    U32 last = U32_sub(self->count, _t_U32_256);
    (void)last;
    ;
    void * out = malloc(self->elem_size);
    (void)out;
    U32 _t_U64_257 = U32_mul(last, self->elem_size);
    (void)_t_U64_257;
    void *_t_v_258 = ptr_add(self->data, _t_U64_257);
    (void)_t_v_258;
    memcpy(out, _t_v_258, self->elem_size);
    ;
    U32 _t_U32_259 = U32_clone(&last);
    (void)_t_U32_259;
    ;
    self->count = _t_U32_259;
    ;
    return out;
}

Vec * Vec_take_prefix(Vec * self, U32 * n) {
    (void)self;
    (void)n;
    Bool _t_Bool_278 = U32_gt(n, &self->count);
    (void)_t_Bool_278;
    if (_t_Bool_278) {
        Str *_t_Str_260 = Str_lit("Str", 3ULL);
        (void)_t_Str_260;
        U32 _t_U32_261 = 5;
        (void)_t_U32_261;
        Array *_va_Array_5 = Array_new(_t_Str_260, &_t_U32_261);
        (void)_va_Array_5;
        Str_delete(_t_Str_260, &(Bool){1});
        ;
        U32 _t_U32_262 = 0;
        (void)_t_U32_262;
        Str *_t_Str_263 = Str_lit("Vec.take_prefix: count ", 23ULL);
        (void)_t_Str_263;
        Array_set(_va_Array_5, &_t_U32_262, _t_Str_263);
        ;
        U32 _t_U32_264 = 1;
        (void)_t_U32_264;
        Str *_t_Str_265 = U32_to_str(n);
        (void)_t_Str_265;
        Array_set(_va_Array_5, &_t_U32_264, _t_Str_265);
        ;
        U32 _t_U32_266 = 2;
        (void)_t_U32_266;
        Str *_t_Str_267 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_267;
        Array_set(_va_Array_5, &_t_U32_266, _t_Str_267);
        ;
        U32 _t_U32_268 = 3;
        (void)_t_U32_268;
        Str *_t_Str_269 = U32_to_str(&self->count);
        (void)_t_Str_269;
        Array_set(_va_Array_5, &_t_U32_268, _t_Str_269);
        ;
        U32 _t_U32_270 = 4;
        (void)_t_U32_270;
        Str *_t_Str_271 = Str_lit(")", 1ULL);
        (void)_t_Str_271;
        Array_set(_va_Array_5, &_t_U32_270, _t_Str_271);
        ;
        Str *_t_Str_272 = Str_lit("./src/core/vec.til:132:19", 25ULL);
        (void)_t_Str_272;
        panic(_t_Str_272, _va_Array_5);
        Str_delete(_t_Str_272, &(Bool){1});
    }
    ;
    U32 prefix_cap = 1;
    (void)prefix_cap;
    U32 _t_U32_279 = 0;
    (void)_t_U32_279;
    Bool _t_Bool_280 = U32_gt(n, &_t_U32_279);
    (void)_t_Bool_280;
    ;
    if (_t_Bool_280) {
        U32 _t_U32_273 = U32_clone(n);
        (void)_t_U32_273;
        prefix_cap = _t_U32_273;
        ;
    }
    ;
    U32 _t_U64_281 = U32_mul(prefix_cap, self->elem_size);
    (void)_t_U64_281;
    void * prefix_data = malloc(_t_U64_281);
    (void)prefix_data;
    ;
    U32 _t_U32_282 = 0;
    (void)_t_U32_282;
    Bool _t_Bool_283 = U32_gt(n, &_t_U32_282);
    (void)_t_Bool_283;
    ;
    if (_t_Bool_283) {
        U32 _t_U64_274 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_274;
        memcpy(prefix_data, self->data, _t_U64_274);
        ;
    }
    ;
    U32 tail_count = U32_sub(self->count, DEREF(n));
    (void)tail_count;
    U32 _t_U32_284 = 0;
    (void)_t_U32_284;
    Bool _t_Bool_285 = U32_gt(&tail_count, &_t_U32_284);
    (void)_t_Bool_285;
    ;
    if (_t_Bool_285) {
        U32 _t_U64_275 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_275;
        void *_t_v_276 = ptr_add(self->data, _t_U64_275);
        (void)_t_v_276;
        U32 _t_U64_277 = U32_mul(tail_count, self->elem_size);
        (void)_t_U64_277;
        memmove(self->data, _t_v_276, _t_U64_277);
        ;
        ;
    }
    ;
    U32 _t_U32_286 = U32_clone(&tail_count);
    (void)_t_U32_286;
    ;
    self->count = _t_U32_286;
    ;
    Vec *_t_Vec_287 = malloc(sizeof(Vec));
    _t_Vec_287->data = prefix_data;
    _t_Vec_287->count = DEREF(n);
    _t_Vec_287->cap = prefix_cap;
    _t_Vec_287->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_287->elem_type = *_ca; free(_ca); }
    _t_Vec_287->elem_clone = (void *)self->elem_clone;
    _t_Vec_287->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_287;
    ;
    return _t_Vec_287;
}

void Vec_set(Vec * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_301 = U32_gte(i, &self->count);
    (void)_t_Bool_301;
    if (_t_Bool_301) {
        Str *_t_Str_288 = Str_lit("Str", 3ULL);
        (void)_t_Str_288;
        U32 _t_U32_289 = 5;
        (void)_t_U32_289;
        Array *_va_Array_6 = Array_new(_t_Str_288, &_t_U32_289);
        (void)_va_Array_6;
        Str_delete(_t_Str_288, &(Bool){1});
        ;
        U32 _t_U32_290 = 0;
        (void)_t_U32_290;
        Str *_t_Str_291 = Str_lit("Vec.set: index ", 15ULL);
        (void)_t_Str_291;
        Array_set(_va_Array_6, &_t_U32_290, _t_Str_291);
        ;
        U32 _t_U32_292 = 1;
        (void)_t_U32_292;
        Str *_t_Str_293 = U32_to_str(i);
        (void)_t_Str_293;
        Array_set(_va_Array_6, &_t_U32_292, _t_Str_293);
        ;
        U32 _t_U32_294 = 2;
        (void)_t_U32_294;
        Str *_t_Str_295 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_295;
        Array_set(_va_Array_6, &_t_U32_294, _t_Str_295);
        ;
        U32 _t_U32_296 = 3;
        (void)_t_U32_296;
        Str *_t_Str_297 = U32_to_str(&self->count);
        (void)_t_Str_297;
        Array_set(_va_Array_6, &_t_U32_296, _t_Str_297);
        ;
        U32 _t_U32_298 = 4;
        (void)_t_U32_298;
        Str *_t_Str_299 = Str_lit(")", 1ULL);
        (void)_t_Str_299;
        Array_set(_va_Array_6, &_t_U32_298, _t_Str_299);
        ;
        Str *_t_Str_300 = Str_lit("./src/core/vec.til:156:19", 25ULL);
        (void)_t_Str_300;
        panic(_t_Str_300, _va_Array_6);
        Str_delete(_t_Str_300, &(Bool){1});
    }
    ;
    U32 _t_U64_302 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_302;
    void *_t_v_303 = ptr_add(self->data, _t_U64_302);
    (void)_t_v_303;
    memcpy(_t_v_303, val, self->elem_size);
    ;
    free(val);
}

void Vec_push_take(Vec * self, Vec * src, U32 i) {
    (void)self;
    (void)src;
    (void)i;
    Bool _t_Bool_326 = U32_gte(&i, &src->count);
    (void)_t_Bool_326;
    if (_t_Bool_326) {
        Str *_t_Str_304 = Str_lit("Str", 3ULL);
        (void)_t_Str_304;
        U32 _t_U32_305 = 5;
        (void)_t_U32_305;
        Array *_va_Array_7 = Array_new(_t_Str_304, &_t_U32_305);
        (void)_va_Array_7;
        Str_delete(_t_Str_304, &(Bool){1});
        ;
        U32 _t_U32_306 = 0;
        (void)_t_U32_306;
        Str *_t_Str_307 = Str_lit("Vec.push_take: index ", 21ULL);
        (void)_t_Str_307;
        Array_set(_va_Array_7, &_t_U32_306, _t_Str_307);
        ;
        U32 _t_U32_308 = 1;
        (void)_t_U32_308;
        Str *_t_Str_309 = U32_to_str(&i);
        (void)_t_Str_309;
        Array_set(_va_Array_7, &_t_U32_308, _t_Str_309);
        ;
        U32 _t_U32_310 = 2;
        (void)_t_U32_310;
        Str *_t_Str_311 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_311;
        Array_set(_va_Array_7, &_t_U32_310, _t_Str_311);
        ;
        U32 _t_U32_312 = 3;
        (void)_t_U32_312;
        Str *_t_Str_313 = U32_to_str(&src->count);
        (void)_t_Str_313;
        Array_set(_va_Array_7, &_t_U32_312, _t_Str_313);
        ;
        U32 _t_U32_314 = 4;
        (void)_t_U32_314;
        Str *_t_Str_315 = Str_lit(")", 1ULL);
        (void)_t_Str_315;
        Array_set(_va_Array_7, &_t_U32_314, _t_Str_315);
        ;
        Str *_t_Str_316 = Str_lit("./src/core/vec.til:167:19", 25ULL);
        (void)_t_Str_316;
        panic(_t_Str_316, _va_Array_7);
        Str_delete(_t_Str_316, &(Bool){1});
    }
    ;
    Bool _t_Bool_327 = U32_eq(self->elem_size, src->elem_size);
    (void)_t_Bool_327;
    Bool _t_Bool_328 = Str_eq(&self->elem_type, &src->elem_type);
    (void)_t_Bool_328;
    Bool _t_Bool_329 = not(_t_Bool_327);
    (void)_t_Bool_329;
    ;
    Bool _t_Bool_330 = not(_t_Bool_328);
    (void)_t_Bool_330;
    ;
    Bool _t_Bool_331 = or(_t_Bool_329, _t_Bool_330);
    (void)_t_Bool_331;
    ;
    ;
    if (_t_Bool_331) {
        Str *_t_Str_317 = Str_lit("Str", 3ULL);
        (void)_t_Str_317;
        U32 _t_U32_318 = 1;
        (void)_t_U32_318;
        Array *_va_Array_8 = Array_new(_t_Str_317, &_t_U32_318);
        (void)_va_Array_8;
        Str_delete(_t_Str_317, &(Bool){1});
        ;
        U32 _t_U32_319 = 0;
        (void)_t_U32_319;
        Str *_t_Str_320 = Str_lit("Vec.push_take: incompatible vecs", 32ULL);
        (void)_t_Str_320;
        Array_set(_va_Array_8, &_t_U32_319, _t_Str_320);
        ;
        Str *_t_Str_321 = Str_lit("./src/core/vec.til:170:19", 25ULL);
        (void)_t_Str_321;
        panic(_t_Str_321, _va_Array_8);
        Str_delete(_t_Str_321, &(Bool){1});
    }
    ;
    Bool _t_Bool_332 = U32_eq(self->count, self->cap);
    (void)_t_Bool_332;
    if (_t_Bool_332) {
        U32 _t_U32_322 = 2;
        (void)_t_U32_322;
        U32 new_cap = U32_mul(self->cap, _t_U32_322);
        (void)new_cap;
        ;
        U32 _t_U64_323 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_323;
        void * _t_v_324 = realloc(self->data, _t_U64_323);
        (void)_t_v_324;
        ;
        self->data = _t_v_324;
        U32 _t_U32_325 = U32_clone(&new_cap);
        (void)_t_U32_325;
        ;
        self->cap = _t_U32_325;
        ;
    }
    ;
    U32 _t_U64_333 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_333;
    U32 _t_U64_334 = U32_mul(i, src->elem_size);
    (void)_t_U64_334;
    void *_t_v_335 = ptr_add(self->data, _t_U64_333);
    (void)_t_v_335;
    void *_t_v_336 = ptr_add(src->data, _t_U64_334);
    (void)_t_v_336;
    memcpy(_t_v_335, _t_v_336, self->elem_size);
    ;
    ;
    U32 _t_U64_337 = U32_mul(i, src->elem_size);
    (void)_t_U64_337;
    void *_t_v_338 = ptr_add(src->data, _t_U64_337);
    (void)_t_v_338;
    I32 _t_I32_339 = 0;
    (void)_t_I32_339;
    memset(_t_v_338, _t_I32_339, src->elem_size);
    ;
    ;
    U32 _t_U32_340 = 1;
    (void)_t_U32_340;
    U32 _t_U32_341 = U32_add(self->count, _t_U32_340);
    (void)_t_U32_341;
    ;
    self->count = _t_U32_341;
    ;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_353 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_353;
    Str *_t_Str_354 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_354;
    Bool _t_Bool_355 = Str_eq(&self->elem_type, _t_Str_354);
    (void)_t_Bool_355;
    Str_delete(_t_Str_354, &(Bool){1});
    Bool _t_Bool_356 = not(_t_Bool_353);
    (void)_t_Bool_356;
    ;
    Bool _t_Bool_357 = not(_t_Bool_355);
    (void)_t_Bool_357;
    ;
    Bool _t_Bool_358 = and(_t_Bool_356, _t_Bool_357);
    (void)_t_Bool_358;
    ;
    ;
    if (_t_Bool_358) {
        {
            U32 _re_U32_342 = self->count;
            (void)_re_U32_342;
            U32 _rc_U32_342 = 0;
            (void)_rc_U32_342;
            Bool _t_Bool_351 = U32_lte(&_rc_U32_342, &_re_U32_342);
            (void)_t_Bool_351;
            if (_t_Bool_351) {
                while (1) {
                    Bool _wcond_Bool_343 = U32_lt(&_rc_U32_342, &_re_U32_342);
                    (void)_wcond_Bool_343;
                    if (_wcond_Bool_343) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_342);
                    (void)i;
                    U32_inc(&_rc_U32_342);
                    U32 _t_U64_344 = U32_mul(i, self->elem_size);
                    (void)_t_U64_344;
                    ;
                    void *_t_v_345 = ptr_add(self->data, _t_U64_344);
                    (void)_t_v_345;
                    Bool _t_Bool_346 = 0;
                    (void)_t_Bool_346;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_345, &_t_Bool_346);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_347 = U32_gt(&_rc_U32_342, &_re_U32_342);
                    (void)_wcond_Bool_347;
                    if (_wcond_Bool_347) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_342);
                    (void)i;
                    U32_dec(&_rc_U32_342);
                    U32 _t_U64_348 = U32_mul(i, self->elem_size);
                    (void)_t_U64_348;
                    ;
                    void *_t_v_349 = ptr_add(self->data, _t_U64_348);
                    (void)_t_v_349;
                    Bool _t_Bool_350 = 0;
                    (void)_t_Bool_350;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_349, &_t_Bool_350);
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
    Bool _t_Bool_359 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_359;
    Bool _t_Bool_360 = not(_t_Bool_359);
    (void)_t_Bool_360;
    ;
    if (_t_Bool_360) {
        Bool _t_Bool_352 = 0;
        (void)_t_Bool_352;
        Str_delete(&self->elem_type, &_t_Bool_352);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U32 _t_U64_374 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_374;
    void * new_data = malloc(_t_U64_374);
    (void)new_data;
    ;
    Bool _t_Bool_375 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_375;
    Str *_t_Str_376 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_376;
    Bool _t_Bool_377 = Str_eq(&self->elem_type, _t_Str_376);
    (void)_t_Bool_377;
    Str_delete(_t_Str_376, &(Bool){1});
    Bool _t_Bool_378 = not(_t_Bool_375);
    (void)_t_Bool_378;
    ;
    Bool _t_Bool_379 = not(_t_Bool_377);
    (void)_t_Bool_379;
    ;
    Bool _t_Bool_380 = and(_t_Bool_378, _t_Bool_379);
    (void)_t_Bool_380;
    ;
    ;
    if (_t_Bool_380) {
        {
            U32 _re_U32_361 = self->count;
            (void)_re_U32_361;
            U32 _rc_U32_361 = 0;
            (void)_rc_U32_361;
            Bool _t_Bool_372 = U32_lte(&_rc_U32_361, &_re_U32_361);
            (void)_t_Bool_372;
            if (_t_Bool_372) {
                while (1) {
                    Bool _wcond_Bool_362 = U32_lt(&_rc_U32_361, &_re_U32_361);
                    (void)_wcond_Bool_362;
                    if (_wcond_Bool_362) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_361);
                    (void)i;
                    U32_inc(&_rc_U32_361);
                    U32 _t_U64_363 = U32_mul(i, self->elem_size);
                    (void)_t_U64_363;
                    void *_t_v_364 = ptr_add(self->data, _t_U64_363);
                    (void)_t_v_364;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_364);
                    (void)cloned;
                    ;
                    U32 _t_U64_365 = U32_mul(i, self->elem_size);
                    (void)_t_U64_365;
                    ;
                    void *_t_v_366 = ptr_add(new_data, _t_U64_365);
                    (void)_t_v_366;
                    memcpy(_t_v_366, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_367 = U32_gt(&_rc_U32_361, &_re_U32_361);
                    (void)_wcond_Bool_367;
                    if (_wcond_Bool_367) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_361);
                    (void)i;
                    U32_dec(&_rc_U32_361);
                    U32 _t_U64_368 = U32_mul(i, self->elem_size);
                    (void)_t_U64_368;
                    void *_t_v_369 = ptr_add(self->data, _t_U64_368);
                    (void)_t_v_369;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_369);
                    (void)cloned;
                    ;
                    U32 _t_U64_370 = U32_mul(i, self->elem_size);
                    (void)_t_U64_370;
                    ;
                    void *_t_v_371 = ptr_add(new_data, _t_U64_370);
                    (void)_t_v_371;
                    memcpy(_t_v_371, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            }
            ;
            ;
            ;
        }
    } else {
        U32 _t_U64_373 = U32_mul(self->count, self->elem_size);
        (void)_t_U64_373;
        memcpy(new_data, self->data, _t_U64_373);
        ;
    }
    ;
    Vec *_t_Vec_381 = malloc(sizeof(Vec));
    _t_Vec_381->data = new_data;
    _t_Vec_381->count = self->count;
    _t_Vec_381->cap = self->cap;
    _t_Vec_381->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_381->elem_type = *_ca; free(_ca); }
    _t_Vec_381->elem_clone = (void *)self->elem_clone;
    _t_Vec_381->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_381;
    return _t_Vec_381;
}

U32 Vec_size(void) {
    I64 _t_I64_382 = 56;
    (void)_t_I64_382;
    return _t_I64_382;
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    (void)total;
    {
        Array *_fc_Array_383 = parts;
        (void)_fc_Array_383;
        U32 _fi_USize_383 = 0;
        (void)_fi_USize_383;
        while (1) {
            U32 _t_U32_385; { U32 *_hp = (U32 *)Array_len(_fc_Array_383); _t_U32_385 = *_hp; free(_hp); }
            (void)_t_U32_385;
            Bool _wcond_Bool_384 = U32_lt(&_fi_USize_383, &_t_U32_385);
            (void)_wcond_Bool_384;
            ;
            if (_wcond_Bool_384) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_383, &_fi_USize_383);
            (void)s;
            U32 _t_U32_386 = 1;
            (void)_t_U32_386;
            U32 _t_U32_387 = U32_add(_fi_USize_383, _t_U32_386);
            (void)_t_U32_387;
            ;
            _fi_USize_383 = _t_U32_387;
            ;
            U32 _t_U32_388 = Str_len(s);
            (void)_t_U32_388;
            U32 _t_U32_389 = U32_add(total, _t_U32_388);
            (void)_t_U32_389;
            ;
            total = _t_U32_389;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    (void)out;
    ;
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
    Bool _t_Bool_400 = U32_gte(i, &self->count);
    (void)_t_Bool_400;
    if (_t_Bool_400) {
        Str *_t_Str_395 = Str_lit("Str", 3ULL);
        (void)_t_Str_395;
        U32 _t_U32_396 = 1;
        (void)_t_U32_396;
        Array *_va_Array_9 = Array_new(_t_Str_395, &_t_U32_396);
        (void)_va_Array_9;
        Str_delete(_t_Str_395, &(Bool){1});
        ;
        U32 _t_U32_397 = 0;
        (void)_t_U32_397;
        Str *_t_Str_398 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t_Str_398;
        Array_set(_va_Array_9, &_t_U32_397, _t_Str_398);
        ;
        Str *_t_Str_399 = Str_lit("./src/core/str.til:39:19", 24ULL);
        (void)_t_Str_399;
        panic(_t_Str_399, _va_Array_9);
        Str_delete(_t_Str_399, &(Bool){1});
    }
    ;
    void *_t_v_401 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_401;
    return _t_v_401;
}

U8 * Str_byte_at(Str * self, U32 * i) {
    (void)self;
    (void)i;
    void *_t_v_402 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_402;
    return _t_v_402;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    (void)min_len;
    Bool _t_Bool_411 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_411;
    if (_t_Bool_411) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_403 = U32_clone(&min_len);
        (void)_re_U32_403;
        U32 _rc_U32_403 = 0;
        (void)_rc_U32_403;
        Bool _t_Bool_410 = U32_lte(&_rc_U32_403, &_re_U32_403);
        (void)_t_Bool_410;
        if (_t_Bool_410) {
            while (1) {
                Bool _wcond_Bool_404 = U32_lt(&_rc_U32_403, &_re_U32_403);
                (void)_wcond_Bool_404;
                if (_wcond_Bool_404) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_403);
                (void)i;
                U32_inc(&_rc_U32_403);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_405 = 0;
                (void)_t_I64_405;
                Bool _t_Bool_406 = I64_neq(&c, &_t_I64_405);
                (void)_t_Bool_406;
                ;
                if (_t_Bool_406) {
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
                Bool _wcond_Bool_407 = U32_gt(&_rc_U32_403, &_re_U32_403);
                (void)_wcond_Bool_407;
                if (_wcond_Bool_407) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_403);
                (void)i;
                U32_dec(&_rc_U32_403);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_408 = 0;
                (void)_t_I64_408;
                Bool _t_Bool_409 = I64_neq(&c, &_t_I64_408);
                (void)_t_Bool_409;
                ;
                if (_t_Bool_409) {
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
    I64 _t_I64_412 = U32_cmp(a->count, b->count);
    (void)_t_I64_412;
    return _t_I64_412;
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_413 = U32_add(a->count, b->count);
    (void)_t_U32_413;
    Str *out = Str_with_capacity(&_t_U32_413);
    (void)out;
    ;
    Str_push_str(out, a);
    Str_push_str(out, b);
    return out;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_414 = 1;
    (void)_t_U32_414;
    U32 _t_U64_415 = U32_add(DEREF(n), _t_U32_414);
    (void)_t_U64_415;
    ;
    void * buf = malloc(_t_U64_415);
    (void)buf;
    ;
    I32 _t_I32_416 = 0;
    (void)_t_I32_416;
    U64 _t_U64_417 = 1;
    (void)_t_U64_417;
    memset(buf, _t_I32_416, _t_U64_417);
    ;
    ;
    I64 _t_I64_418 = 0;
    (void)_t_I64_418;
    Str *_t_Str_419 = malloc(sizeof(Str));
    _t_Str_419->c_str = buf;
    _t_Str_419->count = _t_I64_418;
    _t_Str_419->cap = DEREF(n);
    (void)_t_Str_419;
    ;
    return _t_Str_419;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_430 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_430;
    if (_t_Bool_430) {
        Str *_t_Str_420 = Str_lit("Str", 3ULL);
        (void)_t_Str_420;
        U32 _t_U32_421 = 1;
        (void)_t_U32_421;
        Array *_va_Array_10 = Array_new(_t_Str_420, &_t_U32_421);
        (void)_va_Array_10;
        Str_delete(_t_Str_420, &(Bool){1});
        ;
        U32 _t_U32_422 = 0;
        (void)_t_U32_422;
        Str *_t_Str_423 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t_Str_423;
        Array_set(_va_Array_10, &_t_U32_422, _t_Str_423);
        ;
        Str *_t_Str_424 = Str_lit("./src/core/str.til:82:19", 24ULL);
        (void)_t_Str_424;
        panic(_t_Str_424, _va_Array_10);
        Str_delete(_t_Str_424, &(Bool){1});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    (void)new_len;
    Bool _t_Bool_431 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_431;
    if (_t_Bool_431) {
        Str *_t_Str_425 = Str_lit("Str", 3ULL);
        (void)_t_Str_425;
        U32 _t_U32_426 = 1;
        (void)_t_U32_426;
        Array *_va_Array_11 = Array_new(_t_Str_425, &_t_U32_426);
        (void)_va_Array_11;
        Str_delete(_t_Str_425, &(Bool){1});
        ;
        U32 _t_U32_427 = 0;
        (void)_t_U32_427;
        Str *_t_Str_428 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t_Str_428;
        Array_set(_va_Array_11, &_t_U32_427, _t_Str_428);
        ;
        Str *_t_Str_429 = Str_lit("./src/core/str.til:86:19", 24ULL);
        (void)_t_Str_429;
        panic(_t_Str_429, _va_Array_11);
        Str_delete(_t_Str_429, &(Bool){1});
    }
    ;
    void *_t_v_432 = ptr_add(self->c_str, self->count);
    (void)_t_v_432;
    memcpy(_t_v_432, s->c_str, s->count);
    U32 _t_U32_433 = U32_clone(&new_len);
    (void)_t_U32_433;
    self->count = _t_U32_433;
    ;
    void *_t_v_434 = ptr_add(self->c_str, new_len);
    (void)_t_v_434;
    I32 _t_I32_435 = 0;
    (void)_t_I32_435;
    U64 _t_U64_436 = 1;
    (void)_t_U64_436;
    memset(_t_v_434, _t_I32_435, _t_U64_436);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_437 = 1;
    (void)_t_U32_437;
    U32 _t_U64_438 = U32_add(val->count, _t_U32_437);
    (void)_t_U64_438;
    ;
    void * new_data = malloc(_t_U64_438);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_439 = ptr_add(new_data, val->count);
    (void)_t_v_439;
    I32 _t_I32_440 = 0;
    (void)_t_I32_440;
    U64 _t_U64_441 = 1;
    (void)_t_U64_441;
    memset(_t_v_439, _t_I32_440, _t_U64_441);
    ;
    ;
    Str *_t_Str_442 = malloc(sizeof(Str));
    _t_Str_442->c_str = new_data;
    _t_Str_442->count = val->count;
    _t_Str_442->cap = val->count;
    (void)_t_Str_442;
    return _t_Str_442;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_443 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_443;
    if (_t_Bool_443) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t_Str_444 = Str_clone(val);
    (void)_t_Str_444;
    return _t_Str_444;
}

Str * Str_substr(Str * s, U32 * start, U32 * n) {
    (void)s;
    (void)start;
    (void)n;
    U32 st = U32_clone(start);
    (void)st;
    U32 ln = U32_clone(n);
    (void)ln;
    Bool _t_Bool_446 = U32_gt(&st, &s->count);
    (void)_t_Bool_446;
    if (_t_Bool_446) {
        st = s->count;
    }
    ;
    U32 _t_U32_447 = U32_add(st, ln);
    (void)_t_U32_447;
    Bool _t_Bool_448 = U32_gt(&_t_U32_447, &s->count);
    (void)_t_Bool_448;
    ;
    if (_t_Bool_448) {
        U32 _t_U32_445 = U32_sub(s->count, st);
        (void)_t_U32_445;
        ln = _t_U32_445;
        ;
    }
    ;
    void *_t_v_449 = ptr_add(s->c_str, st);
    (void)_t_v_449;
    Str *_t_Str_450 = malloc(sizeof(Str));
    _t_Str_450->c_str = _t_v_449;
    _t_Str_450->count = ln;
    _t_Str_450->cap = CAP_VIEW;
    (void)_t_Str_450;
    ;
    ;
    return _t_Str_450;
}

Bool Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_481 = 0;
    (void)_t_U32_481;
    Bool _t_Bool_482 = U32_eq(b->count, _t_U32_481);
    (void)_t_Bool_482;
    ;
    if (_t_Bool_482) {
        Bool _t_Bool_451 = 1;
        (void)_t_Bool_451;
        ;
        return _t_Bool_451;
    }
    ;
    Bool _t_Bool_483 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_483;
    if (_t_Bool_483) {
        Bool _t_Bool_452 = 0;
        (void)_t_Bool_452;
        ;
        return _t_Bool_452;
    }
    ;
    {
        U32 _t_U32_478 = U32_sub(a->count, b->count);
        (void)_t_U32_478;
        U32 _t_U32_479 = 1;
        (void)_t_U32_479;
        U32 _re_U32_453 = U32_add(_t_U32_478, _t_U32_479);
        (void)_re_U32_453;
        ;
        ;
        U32 _rc_U32_453 = 0;
        (void)_rc_U32_453;
        Bool _t_Bool_480 = U32_lte(&_rc_U32_453, &_re_U32_453);
        (void)_t_Bool_480;
        if (_t_Bool_480) {
            while (1) {
                Bool _wcond_Bool_454 = U32_lt(&_rc_U32_453, &_re_U32_453);
                (void)_wcond_Bool_454;
                if (_wcond_Bool_454) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_453);
                (void)i;
                U32_inc(&_rc_U32_453);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_455 = b->count;
                    (void)_re_U32_455;
                    U32 _rc_U32_455 = 0;
                    (void)_rc_U32_455;
                    Bool _t_Bool_464 = U32_lte(&_rc_U32_455, &_re_U32_455);
                    (void)_t_Bool_464;
                    if (_t_Bool_464) {
                        while (1) {
                            Bool _wcond_Bool_456 = U32_lt(&_rc_U32_455, &_re_U32_455);
                            (void)_wcond_Bool_456;
                            if (_wcond_Bool_456) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_455);
                            (void)j;
                            U32_inc(&_rc_U32_455);
                            U32 _t_U32_458 = U32_add(i, j);
                            (void)_t_U32_458;
                            U8 *ac = Str_get(a, &_t_U32_458);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_459 = U8_neq(ac, bc);
                            (void)_t_Bool_459;
                            ;
                            ;
                            if (_t_Bool_459) {
                                Bool _t_Bool_457 = 0;
                                (void)_t_Bool_457;
                                found = _t_Bool_457;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_460 = U32_gt(&_rc_U32_455, &_re_U32_455);
                            (void)_wcond_Bool_460;
                            if (_wcond_Bool_460) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_455);
                            (void)j;
                            U32_dec(&_rc_U32_455);
                            U32 _t_U32_462 = U32_add(i, j);
                            (void)_t_U32_462;
                            U8 *ac = Str_get(a, &_t_U32_462);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_463 = U8_neq(ac, bc);
                            (void)_t_Bool_463;
                            ;
                            ;
                            if (_t_Bool_463) {
                                Bool _t_Bool_461 = 0;
                                (void)_t_Bool_461;
                                found = _t_Bool_461;
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
                    Bool _t_Bool_465 = 1;
                    (void)_t_Bool_465;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_465;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_466 = U32_gt(&_rc_U32_453, &_re_U32_453);
                (void)_wcond_Bool_466;
                if (_wcond_Bool_466) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_453);
                (void)i;
                U32_dec(&_rc_U32_453);
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
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_484 = 0;
    (void)_t_Bool_484;
    return _t_Bool_484;
}

Bool Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_494 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_494;
    if (_t_Bool_494) {
        Bool _t_Bool_485 = 0;
        (void)_t_Bool_485;
        ;
        return _t_Bool_485;
    }
    ;
    {
        U32 _re_U32_486 = b->count;
        (void)_re_U32_486;
        U32 _rc_U32_486 = 0;
        (void)_rc_U32_486;
        Bool _t_Bool_493 = U32_lte(&_rc_U32_486, &_re_U32_486);
        (void)_t_Bool_493;
        if (_t_Bool_493) {
            while (1) {
                Bool _wcond_Bool_487 = U32_lt(&_rc_U32_486, &_re_U32_486);
                (void)_wcond_Bool_487;
                if (_wcond_Bool_487) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_486);
                (void)i;
                U32_inc(&_rc_U32_486);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_489 = U8_neq(ac, bc);
                (void)_t_Bool_489;
                ;
                if (_t_Bool_489) {
                    Bool _t_Bool_488 = 0;
                    (void)_t_Bool_488;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_488;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_490 = U32_gt(&_rc_U32_486, &_re_U32_486);
                (void)_wcond_Bool_490;
                if (_wcond_Bool_490) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_486);
                (void)i;
                U32_dec(&_rc_U32_486);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_492 = U8_neq(ac, bc);
                (void)_t_Bool_492;
                ;
                if (_t_Bool_492) {
                    Bool _t_Bool_491 = 0;
                    (void)_t_Bool_491;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_491;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_495 = 1;
    (void)_t_Bool_495;
    return _t_Bool_495;
}

Bool Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_507 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_507;
    if (_t_Bool_507) {
        Bool _t_Bool_496 = 0;
        (void)_t_Bool_496;
        ;
        return _t_Bool_496;
    }
    ;
    U32 offset = U32_sub(a->count, b->count);
    (void)offset;
    {
        U32 _re_U32_497 = b->count;
        (void)_re_U32_497;
        U32 _rc_U32_497 = 0;
        (void)_rc_U32_497;
        Bool _t_Bool_506 = U32_lte(&_rc_U32_497, &_re_U32_497);
        (void)_t_Bool_506;
        if (_t_Bool_506) {
            while (1) {
                Bool _wcond_Bool_498 = U32_lt(&_rc_U32_497, &_re_U32_497);
                (void)_wcond_Bool_498;
                if (_wcond_Bool_498) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_497);
                (void)i;
                U32_inc(&_rc_U32_497);
                U32 _t_U32_500 = U32_add(offset, i);
                (void)_t_U32_500;
                U8 *ac = Str_get(a, &_t_U32_500);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_501 = U8_neq(ac, bc);
                (void)_t_Bool_501;
                ;
                ;
                if (_t_Bool_501) {
                    Bool _t_Bool_499 = 0;
                    (void)_t_Bool_499;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_499;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_502 = U32_gt(&_rc_U32_497, &_re_U32_497);
                (void)_wcond_Bool_502;
                if (_wcond_Bool_502) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_497);
                (void)i;
                U32_dec(&_rc_U32_497);
                U32 _t_U32_504 = U32_add(offset, i);
                (void)_t_U32_504;
                U8 *ac = Str_get(a, &_t_U32_504);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_505 = U8_neq(ac, bc);
                (void)_t_Bool_505;
                ;
                ;
                if (_t_Bool_505) {
                    Bool _t_Bool_503 = 0;
                    (void)_t_Bool_503;
                    ;
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
    ;
    Bool _t_Bool_508 = 1;
    (void)_t_Bool_508;
    return _t_Bool_508;
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_509 = 0;
    (void)_t_U32_509;
    Bool _t_Bool_510 = U32_eq(self->count, _t_U32_509);
    (void)_t_Bool_510;
    ;
    return _t_Bool_510;
}

I64 Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_545 = 0;
    (void)_t_U32_545;
    Bool _t_Bool_546 = U32_eq(needle->count, _t_U32_545);
    (void)_t_Bool_546;
    ;
    if (_t_Bool_546) {
        I64 _t_I64_511 = 0;
        (void)_t_I64_511;
        I64 _t_I64_512 = 1;
        (void)_t_I64_512;
        I64 _t_I64_513 = I64_sub(_t_I64_511, _t_I64_512);
        (void)_t_I64_513;
        ;
        ;
        ;
        return _t_I64_513;
    }
    ;
    Bool _t_Bool_547 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_547;
    if (_t_Bool_547) {
        I64 _t_I64_514 = 0;
        (void)_t_I64_514;
        I64 _t_I64_515 = 1;
        (void)_t_I64_515;
        I64 _t_I64_516 = I64_sub(_t_I64_514, _t_I64_515);
        (void)_t_I64_516;
        ;
        ;
        ;
        return _t_I64_516;
    }
    ;
    {
        U32 _t_U32_542 = U32_sub(self->count, needle->count);
        (void)_t_U32_542;
        U32 _t_U32_543 = 1;
        (void)_t_U32_543;
        U32 _re_U32_517 = U32_add(_t_U32_542, _t_U32_543);
        (void)_re_U32_517;
        ;
        ;
        U32 _rc_U32_517 = 0;
        (void)_rc_U32_517;
        Bool _t_Bool_544 = U32_lte(&_rc_U32_517, &_re_U32_517);
        (void)_t_Bool_544;
        if (_t_Bool_544) {
            while (1) {
                Bool _wcond_Bool_518 = U32_lt(&_rc_U32_517, &_re_U32_517);
                (void)_wcond_Bool_518;
                if (_wcond_Bool_518) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_517);
                (void)i;
                U32_inc(&_rc_U32_517);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_519 = needle->count;
                    (void)_re_U32_519;
                    U32 _rc_U32_519 = 0;
                    (void)_rc_U32_519;
                    Bool _t_Bool_528 = U32_lte(&_rc_U32_519, &_re_U32_519);
                    (void)_t_Bool_528;
                    if (_t_Bool_528) {
                        while (1) {
                            Bool _wcond_Bool_520 = U32_lt(&_rc_U32_519, &_re_U32_519);
                            (void)_wcond_Bool_520;
                            if (_wcond_Bool_520) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_519);
                            (void)j;
                            U32_inc(&_rc_U32_519);
                            U32 _t_U32_522 = U32_add(i, j);
                            (void)_t_U32_522;
                            U8 *ac = Str_get(self, &_t_U32_522);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_523 = U8_neq(ac, bc);
                            (void)_t_Bool_523;
                            ;
                            ;
                            if (_t_Bool_523) {
                                Bool _t_Bool_521 = 0;
                                (void)_t_Bool_521;
                                found = _t_Bool_521;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_524 = U32_gt(&_rc_U32_519, &_re_U32_519);
                            (void)_wcond_Bool_524;
                            if (_wcond_Bool_524) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_519);
                            (void)j;
                            U32_dec(&_rc_U32_519);
                            U32 _t_U32_526 = U32_add(i, j);
                            (void)_t_U32_526;
                            U8 *ac = Str_get(self, &_t_U32_526);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_527 = U8_neq(ac, bc);
                            (void)_t_Bool_527;
                            ;
                            ;
                            if (_t_Bool_527) {
                                Bool _t_Bool_525 = 0;
                                (void)_t_Bool_525;
                                found = _t_Bool_525;
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
                    I64 _t_I64_529 = U32_to_i64(i);
                    (void)_t_I64_529;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_529;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_530 = U32_gt(&_rc_U32_517, &_re_U32_517);
                (void)_wcond_Bool_530;
                if (_wcond_Bool_530) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_517);
                (void)i;
                U32_dec(&_rc_U32_517);
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
        }
        ;
        ;
        ;
    }
    I64 _t_I64_548 = 0;
    (void)_t_I64_548;
    I64 _t_I64_549 = 1;
    (void)_t_I64_549;
    I64 _t_I64_550 = I64_sub(_t_I64_548, _t_I64_549);
    (void)_t_I64_550;
    ;
    ;
    return _t_I64_550;
}

I64 Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_585 = 0;
    (void)_t_U32_585;
    Bool _t_Bool_586 = U32_eq(needle->count, _t_U32_585);
    (void)_t_Bool_586;
    ;
    if (_t_Bool_586) {
        I64 _t_I64_551 = 0;
        (void)_t_I64_551;
        I64 _t_I64_552 = 1;
        (void)_t_I64_552;
        I64 _t_I64_553 = I64_sub(_t_I64_551, _t_I64_552);
        (void)_t_I64_553;
        ;
        ;
        ;
        return _t_I64_553;
    }
    ;
    Bool _t_Bool_587 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_587;
    if (_t_Bool_587) {
        I64 _t_I64_554 = 0;
        (void)_t_I64_554;
        I64 _t_I64_555 = 1;
        (void)_t_I64_555;
        I64 _t_I64_556 = I64_sub(_t_I64_554, _t_I64_555);
        (void)_t_I64_556;
        ;
        ;
        ;
        return _t_I64_556;
    }
    ;
    I64 _t_I64_588 = 0;
    (void)_t_I64_588;
    I64 _t_I64_589 = 1;
    (void)_t_I64_589;
    I64 last = I64_sub(_t_I64_588, _t_I64_589);
    (void)last;
    ;
    ;
    {
        U32 _t_U32_582 = U32_sub(self->count, needle->count);
        (void)_t_U32_582;
        U32 _t_U32_583 = 1;
        (void)_t_U32_583;
        U32 _re_U32_557 = U32_add(_t_U32_582, _t_U32_583);
        (void)_re_U32_557;
        ;
        ;
        U32 _rc_U32_557 = 0;
        (void)_rc_U32_557;
        Bool _t_Bool_584 = U32_lte(&_rc_U32_557, &_re_U32_557);
        (void)_t_Bool_584;
        if (_t_Bool_584) {
            while (1) {
                Bool _wcond_Bool_558 = U32_lt(&_rc_U32_557, &_re_U32_557);
                (void)_wcond_Bool_558;
                if (_wcond_Bool_558) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_557);
                (void)i;
                U32_inc(&_rc_U32_557);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_559 = needle->count;
                    (void)_re_U32_559;
                    U32 _rc_U32_559 = 0;
                    (void)_rc_U32_559;
                    Bool _t_Bool_568 = U32_lte(&_rc_U32_559, &_re_U32_559);
                    (void)_t_Bool_568;
                    if (_t_Bool_568) {
                        while (1) {
                            Bool _wcond_Bool_560 = U32_lt(&_rc_U32_559, &_re_U32_559);
                            (void)_wcond_Bool_560;
                            if (_wcond_Bool_560) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_559);
                            (void)j;
                            U32_inc(&_rc_U32_559);
                            U32 _t_U32_562 = U32_add(i, j);
                            (void)_t_U32_562;
                            U8 *ac = Str_get(self, &_t_U32_562);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_563 = U8_neq(ac, bc);
                            (void)_t_Bool_563;
                            ;
                            ;
                            if (_t_Bool_563) {
                                Bool _t_Bool_561 = 0;
                                (void)_t_Bool_561;
                                found = _t_Bool_561;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_564 = U32_gt(&_rc_U32_559, &_re_U32_559);
                            (void)_wcond_Bool_564;
                            if (_wcond_Bool_564) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_559);
                            (void)j;
                            U32_dec(&_rc_U32_559);
                            U32 _t_U32_566 = U32_add(i, j);
                            (void)_t_U32_566;
                            U8 *ac = Str_get(self, &_t_U32_566);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_567 = U8_neq(ac, bc);
                            (void)_t_Bool_567;
                            ;
                            ;
                            if (_t_Bool_567) {
                                Bool _t_Bool_565 = 0;
                                (void)_t_Bool_565;
                                found = _t_Bool_565;
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
                    I64 _t_I64_569 = U32_to_i64(i);
                    (void)_t_I64_569;
                    last = _t_I64_569;
                    ;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_570 = U32_gt(&_rc_U32_557, &_re_U32_557);
                (void)_wcond_Bool_570;
                if (_wcond_Bool_570) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_557);
                (void)i;
                U32_dec(&_rc_U32_557);
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
    U32 _t_U32_615 = 0;
    (void)_t_U32_615;
    Bool _t_Bool_616 = U32_eq(from->count, _t_U32_615);
    (void)_t_Bool_616;
    ;
    if (_t_Bool_616) {
        Str *_t_Str_590 = Str_clone(self);
        (void)_t_Str_590;
        ;
        return _t_Str_590;
    }
    ;
    U32 matches = 0;
    (void)matches;
    U32 start = 0;
    (void)start;
    while (1) {
        U32 _t_U32_592 = U32_sub(self->count, from->count);
        (void)_t_U32_592;
        Bool _wcond_Bool_591 = U32_lte(&start, &_t_U32_592);
        (void)_wcond_Bool_591;
        ;
        if (_wcond_Bool_591) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_593 = U32_sub(self->count, start);
        (void)_t_U32_593;
        Str *rest = Str_substr(self, &start, &_t_U32_593);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_594 = 0;
        (void)_t_I64_594;
        I64 _t_I64_595 = 1;
        (void)_t_I64_595;
        I64 _t_I64_596 = I64_sub(_t_I64_594, _t_I64_595);
        (void)_t_I64_596;
        ;
        ;
        Bool _t_Bool_597 = I64_eq(pos, _t_I64_596);
        (void)_t_Bool_597;
        ;
        if (_t_Bool_597) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        U32 _t_U32_598 = U32_add(start, pos_u);
        (void)_t_U32_598;
        ;
        U32 _t_U32_599 = U32_add(_t_U32_598, from->count);
        (void)_t_U32_599;
        ;
        start = _t_U32_599;
        ;
        U32 _t_U32_600 = 1;
        (void)_t_U32_600;
        U32 _t_U32_601 = U32_add(matches, _t_U32_600);
        (void)_t_U32_601;
        ;
        matches = _t_U32_601;
        ;
    }
    U32 _t_U32_617 = 0;
    (void)_t_U32_617;
    Bool _t_Bool_618 = U32_eq(matches, _t_U32_617);
    (void)_t_Bool_618;
    ;
    if (_t_Bool_618) {
        Str *_t_Str_602 = Str_clone(self);
        (void)_t_Str_602;
        ;
        ;
        ;
        return _t_Str_602;
    }
    ;
    U32 removed = U32_mul(matches, from->count);
    (void)removed;
    U32 added = U32_mul(matches, to->count);
    (void)added;
    ;
    U32 _t_U32_619 = U32_sub(self->count, removed);
    (void)_t_U32_619;
    ;
    U32 _t_U32_620 = U32_add(_t_U32_619, added);
    (void)_t_U32_620;
    ;
    ;
    Str *out = Str_with_capacity(&_t_U32_620);
    (void)out;
    ;
    U32 _t_U32_621 = 0;
    (void)_t_U32_621;
    start = _t_U32_621;
    ;
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
        Str *_t_Str_610 = Str_substr(self, &start, &pos_u);
        (void)_t_Str_610;
        Str_push_str(out, _t_Str_610);
        Str_delete(_t_Str_610, &(Bool){1});
        Str_push_str(out, to);
        U32 _t_U32_611 = U32_add(start, pos_u);
        (void)_t_U32_611;
        ;
        U32 _t_U32_612 = U32_add(_t_U32_611, from->count);
        (void)_t_U32_612;
        ;
        start = _t_U32_612;
        ;
    }
    Bool _t_Bool_622 = U32_lt(&start, &self->count);
    (void)_t_Bool_622;
    if (_t_Bool_622) {
        U32 _t_U32_613 = U32_sub(self->count, start);
        (void)_t_U32_613;
        Str *_t_Str_614 = Str_substr(self, &start, &_t_U32_613);
        (void)_t_Str_614;
        ;
        Str_push_str(out, _t_Str_614);
        Str_delete(_t_Str_614, &(Bool){1});
    }
    ;
    ;
    return out;
}

Str * Str_get_char(Str * self, U32 * i) {
    (void)self;
    (void)i;
    U32 _t_U32_623 = 1;
    (void)_t_U32_623;
    Str *_t_Str_624 = Str_substr(self, i, &_t_U32_623);
    (void)_t_Str_624;
    ;
    return _t_Str_624;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t_Bool_627 = Str_starts_with(self, prefix);
    (void)_t_Bool_627;
    if (_t_Bool_627) {
        U32 _t_U32_625 = U32_sub(self->count, prefix->count);
        (void)_t_U32_625;
        Str *_t_Str_626 = Str_substr(self, &prefix->count, &_t_U32_625);
        (void)_t_Str_626;
        ;
        ;
        return _t_Str_626;
    }
    ;
    Str *_t_Str_628 = Str_clone(self);
    (void)_t_Str_628;
    return _t_Str_628;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t_Bool_632 = Str_ends_with(self, suffix);
    (void)_t_Bool_632;
    if (_t_Bool_632) {
        U32 _t_U32_629 = 0;
        (void)_t_U32_629;
        U32 _t_U32_630 = U32_sub(self->count, suffix->count);
        (void)_t_U32_630;
        Str *_t_Str_631 = Str_substr(self, &_t_U32_629, &_t_U32_630);
        (void)_t_Str_631;
        ;
        ;
        ;
        return _t_Str_631;
    }
    ;
    Str *_t_Str_633 = Str_clone(self);
    (void)_t_Str_633;
    return _t_Str_633;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t_U64_634 = 2;
    (void)_t_U64_634;
    void * buf = malloc(_t_U64_634);
    (void)buf;
    ;
    U64 _t_U64_635 = 1;
    (void)_t_U64_635;
    memcpy(buf, byte, _t_U64_635);
    ;
    U64 _t_U64_636 = 1;
    (void)_t_U64_636;
    void *_t_v_637 = ptr_add(buf, _t_U64_636);
    (void)_t_v_637;
    I32 _t_I32_638 = 0;
    (void)_t_I32_638;
    U64 _t_U64_639 = 1;
    (void)_t_U64_639;
    memset(_t_v_637, _t_I32_638, _t_U64_639);
    ;
    ;
    ;
    I64 _t_I64_640 = 1;
    (void)_t_I64_640;
    I64 _t_I64_641 = 1;
    (void)_t_I64_641;
    Str *_t_Str_642 = malloc(sizeof(Str));
    _t_Str_642->c_str = buf;
    _t_Str_642->count = _t_I64_640;
    _t_Str_642->cap = _t_I64_641;
    (void)_t_Str_642;
    ;
    ;
    return _t_Str_642;
}

I64 Str_to_i64(Str * self) {
    (void)self;
    U32 _t_U32_699 = 0;
    (void)_t_U32_699;
    Bool _t_Bool_700 = U32_eq(self->count, _t_U32_699);
    (void)_t_Bool_700;
    ;
    if (_t_Bool_700) {
        Str *_t_Str_643 = Str_lit("Str", 3ULL);
        (void)_t_Str_643;
        U32 _t_U32_644 = 1;
        (void)_t_U32_644;
        Array *_va_Array_12 = Array_new(_t_Str_643, &_t_U32_644);
        (void)_va_Array_12;
        Str_delete(_t_Str_643, &(Bool){1});
        ;
        U32 _t_U32_645 = 0;
        (void)_t_U32_645;
        Str *_t_Str_646 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t_Str_646;
        Array_set(_va_Array_12, &_t_U32_645, _t_Str_646);
        ;
        Str *_t_Str_647 = Str_lit("./src/core/str.til:266:37", 25ULL);
        (void)_t_Str_647;
        panic(_t_Str_647, _va_Array_12);
        Str_delete(_t_Str_647, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_701 = 0;
    (void)_t_U32_701;
    U8 *first = Str_get(self, &_t_U32_701);
    (void)first;
    U8 _t_U8_702 = 45;
    (void)_t_U8_702;
    Bool _t_Bool_703 = U8_eq(DEREF(first), _t_U8_702);
    (void)_t_Bool_703;
    ;
    ;
    if (_t_Bool_703) {
        Bool _t_Bool_648 = 1;
        (void)_t_Bool_648;
        neg = _t_Bool_648;
        ;
        U32 _t_U32_649 = 1;
        (void)_t_U32_649;
        start = _t_U32_649;
        ;
    }
    ;
    Bool _t_Bool_704 = U32_eq(start, self->count);
    (void)_t_Bool_704;
    if (_t_Bool_704) {
        Str *_t_Str_650 = Str_lit("Str", 3ULL);
        (void)_t_Str_650;
        U32 _t_U32_651 = 1;
        (void)_t_U32_651;
        Array *_va_Array_13 = Array_new(_t_Str_650, &_t_U32_651);
        (void)_va_Array_13;
        Str_delete(_t_Str_650, &(Bool){1});
        ;
        U32 _t_U32_652 = 0;
        (void)_t_U32_652;
        Str *_t_Str_653 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t_Str_653;
        Array_set(_va_Array_13, &_t_U32_652, _t_Str_653);
        ;
        Str *_t_Str_654 = Str_lit("./src/core/str.til:275:41", 25ULL);
        (void)_t_Str_654;
        panic(_t_Str_654, _va_Array_13);
        Str_delete(_t_Str_654, &(Bool){1});
    }
    ;
    {
        U32 _re_U32_655 = self->count;
        (void)_re_U32_655;
        U32 _rc_U32_655 = U32_clone(&start);
        (void)_rc_U32_655;
        Bool _t_Bool_696 = U32_lte(&_rc_U32_655, &_re_U32_655);
        (void)_t_Bool_696;
        if (_t_Bool_696) {
            while (1) {
                Bool _wcond_Bool_656 = U32_lt(&_rc_U32_655, &_re_U32_655);
                (void)_wcond_Bool_656;
                if (_wcond_Bool_656) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_655);
                (void)i;
                U32_inc(&_rc_U32_655);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_666 = U8_to_i64(DEREF(ch));
                (void)_t_I64_666;
                ;
                I64 _t_I64_667 = 48;
                (void)_t_I64_667;
                I64 d = I64_sub(_t_I64_666, _t_I64_667);
                (void)d;
                ;
                ;
                I64 _t_I64_668 = 0;
                (void)_t_I64_668;
                I64 _t_I64_669 = 9;
                (void)_t_I64_669;
                Bool _t_Bool_670 = I64_lt(&d, &_t_I64_668);
                (void)_t_Bool_670;
                ;
                Bool _t_Bool_671 = I64_gt(&d, &_t_I64_669);
                (void)_t_Bool_671;
                ;
                Bool _t_Bool_672 = or(_t_Bool_670, _t_Bool_671);
                (void)_t_Bool_672;
                ;
                ;
                if (_t_Bool_672) {
                    Str *_t_Str_657 = Str_lit("Str", 3ULL);
                    (void)_t_Str_657;
                    U32 _t_U32_658 = 3;
                    (void)_t_U32_658;
                    Array *_va_Array_14 = Array_new(_t_Str_657, &_t_U32_658);
                    (void)_va_Array_14;
                    Str_delete(_t_Str_657, &(Bool){1});
                    ;
                    U32 _t_U32_659 = 0;
                    (void)_t_U32_659;
                    Str *_t_Str_660 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_660;
                    Array_set(_va_Array_14, &_t_U32_659, _t_Str_660);
                    ;
                    U32 _t_U32_661 = 1;
                    (void)_t_U32_661;
                    Str *_t_Str_662 = Str_clone(self);
                    (void)_t_Str_662;
                    Array_set(_va_Array_14, &_t_U32_661, _t_Str_662);
                    ;
                    U32 _t_U32_663 = 2;
                    (void)_t_U32_663;
                    Str *_t_Str_664 = Str_lit("'", 1ULL);
                    (void)_t_Str_664;
                    Array_set(_va_Array_14, &_t_U32_663, _t_Str_664);
                    ;
                    Str *_t_Str_665 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_665;
                    panic(_t_Str_665, _va_Array_14);
                    Str_delete(_t_Str_665, &(Bool){1});
                }
                ;
                I64 _t_I64_673 = 10;
                (void)_t_I64_673;
                I64 _t_I64_674 = I64_mul(result, _t_I64_673);
                (void)_t_I64_674;
                ;
                I64 _t_I64_675 = I64_add(_t_I64_674, d);
                (void)_t_I64_675;
                ;
                ;
                result = _t_I64_675;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_676 = U32_gt(&_rc_U32_655, &_re_U32_655);
                (void)_wcond_Bool_676;
                if (_wcond_Bool_676) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_655);
                (void)i;
                U32_dec(&_rc_U32_655);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_686 = U8_to_i64(DEREF(ch));
                (void)_t_I64_686;
                ;
                I64 _t_I64_687 = 48;
                (void)_t_I64_687;
                I64 d = I64_sub(_t_I64_686, _t_I64_687);
                (void)d;
                ;
                ;
                I64 _t_I64_688 = 0;
                (void)_t_I64_688;
                I64 _t_I64_689 = 9;
                (void)_t_I64_689;
                Bool _t_Bool_690 = I64_lt(&d, &_t_I64_688);
                (void)_t_Bool_690;
                ;
                Bool _t_Bool_691 = I64_gt(&d, &_t_I64_689);
                (void)_t_Bool_691;
                ;
                Bool _t_Bool_692 = or(_t_Bool_690, _t_Bool_691);
                (void)_t_Bool_692;
                ;
                ;
                if (_t_Bool_692) {
                    Str *_t_Str_677 = Str_lit("Str", 3ULL);
                    (void)_t_Str_677;
                    U32 _t_U32_678 = 3;
                    (void)_t_U32_678;
                    Array *_va_Array_15 = Array_new(_t_Str_677, &_t_U32_678);
                    (void)_va_Array_15;
                    Str_delete(_t_Str_677, &(Bool){1});
                    ;
                    U32 _t_U32_679 = 0;
                    (void)_t_U32_679;
                    Str *_t_Str_680 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_680;
                    Array_set(_va_Array_15, &_t_U32_679, _t_Str_680);
                    ;
                    U32 _t_U32_681 = 1;
                    (void)_t_U32_681;
                    Str *_t_Str_682 = Str_clone(self);
                    (void)_t_Str_682;
                    Array_set(_va_Array_15, &_t_U32_681, _t_Str_682);
                    ;
                    U32 _t_U32_683 = 2;
                    (void)_t_U32_683;
                    Str *_t_Str_684 = Str_lit("'", 1ULL);
                    (void)_t_Str_684;
                    Array_set(_va_Array_15, &_t_U32_683, _t_Str_684);
                    ;
                    Str *_t_Str_685 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_685;
                    panic(_t_Str_685, _va_Array_15);
                    Str_delete(_t_Str_685, &(Bool){1});
                }
                ;
                I64 _t_I64_693 = 10;
                (void)_t_I64_693;
                I64 _t_I64_694 = I64_mul(result, _t_I64_693);
                (void)_t_I64_694;
                ;
                I64 _t_I64_695 = I64_add(_t_I64_694, d);
                (void)_t_I64_695;
                ;
                ;
                result = _t_I64_695;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    if (neg) {
        I64 _t_I64_697 = 0;
        (void)_t_I64_697;
        I64 _t_I64_698 = I64_sub(_t_I64_697, result);
        (void)_t_I64_698;
        ;
        ;
        ;
        return _t_I64_698;
    }
    ;
    return result;
}

U8 Str_to_u8(Str * self) {
    (void)self;
    I64 _t_I64_705 = Str_to_i64(self);
    (void)_t_I64_705;
    U8 _t_U8_706 = I64_to_u8(_t_I64_705);
    (void)_t_U8_706;
    ;
    return _t_U8_706;
}

I32 Str_to_i32(Str * self) {
    (void)self;
    I64 _t_I64_707 = Str_to_i64(self);
    (void)_t_I64_707;
    I32 _t_I32_708 = I64_to_i32(_t_I64_707);
    (void)_t_I32_708;
    ;
    return _t_I32_708;
}

F32 Str_to_f32(Str * self) {
    (void)self;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_734 = Str_len(self);
    (void)_t_U32_734;
    U32 _t_U32_735 = 0;
    (void)_t_U32_735;
    U32 _t_U32_736 = 0;
    (void)_t_U32_736;
    U8 *_t_U8_737 = Str_get(self, &_t_U32_736);
    (void)_t_U8_737;
    U8 _t_U8_738 = 45;
    (void)_t_U8_738;
    Bool _t_Bool_739 = U32_gt(&_t_U32_734, &_t_U32_735);
    (void)_t_Bool_739;
    ;
    ;
    Bool _t_Bool_740 = U8_eq(DEREF(_t_U8_737), _t_U8_738);
    (void)_t_Bool_740;
    ;
    ;
    Bool _t_Bool_741 = and(_t_Bool_739, _t_Bool_740);
    (void)_t_Bool_741;
    ;
    ;
    if (_t_Bool_741) {
        Bool _t_Bool_709 = 1;
        (void)_t_Bool_709;
        neg = _t_Bool_709;
        ;
        U32 _t_U32_710 = 1;
        (void)_t_U32_710;
        start = _t_U32_710;
        ;
    }
    ;
    U32 _t_U32_742 = Str_len(self);
    (void)_t_U32_742;
    U32 _t_U32_743 = U32_sub(_t_U32_742, start);
    (void)_t_U32_743;
    ;
    Str *rest = Str_substr(self, &start, &_t_U32_743);
    (void)rest;
    ;
    ;
    Str *_t_Str_744 = Str_lit(".", 1ULL);
    (void)_t_Str_744;
    I64 dot = Str_find(rest, _t_Str_744);
    (void)dot;
    Str_delete(_t_Str_744, &(Bool){1});
    I64 _t_I64_745 = 0;
    (void)_t_I64_745;
    I64 _t_I64_746 = 1;
    (void)_t_I64_746;
    I64 _t_I64_747 = I64_sub(_t_I64_745, _t_I64_746);
    (void)_t_I64_747;
    ;
    ;
    Bool _t_Bool_748 = I64_eq(dot, _t_I64_747);
    (void)_t_Bool_748;
    ;
    if (_t_Bool_748) {
        I64 _t_I64_714 = Str_to_i64(rest);
        (void)_t_I64_714;
        F32 out = I64_to_f32(_t_I64_714);
        (void)out;
        ;
        if (neg) {
            I64 _t_I64_711 = 0;
            (void)_t_I64_711;
            F32 _t_F32_712 = I64_to_f32(_t_I64_711);
            (void)_t_F32_712;
            ;
            F32 _t_F32_713 = F32_sub(_t_F32_712, out);
            (void)_t_F32_713;
            ;
            ;
            ;
            ;
            ;
            Str_delete(rest, &(Bool){1});
            return _t_F32_713;
        }
        ;
        ;
        ;
        Str_delete(rest, &(Bool){1});
        return out;
    }
    ;
    U32 _t_U32_749 = 0;
    (void)_t_U32_749;
    U32 _t_U32_750 = I64_to_usize(dot);
    (void)_t_U32_750;
    Str *int_part = Str_substr(rest, &_t_U32_749, &_t_U32_750);
    (void)int_part;
    ;
    ;
    U32 _t_U32_751 = I64_to_usize(dot);
    (void)_t_U32_751;
    U32 _t_U32_752 = 1;
    (void)_t_U32_752;
    U32 _t_U32_753 = I64_to_usize(dot);
    (void)_t_U32_753;
    ;
    U32 _t_U32_754 = 1;
    (void)_t_U32_754;
    U32 _t_U32_755 = Str_len(rest);
    (void)_t_U32_755;
    U32 _t_U32_756 = U32_add(_t_U32_753, _t_U32_754);
    (void)_t_U32_756;
    ;
    ;
    U32 _t_U32_757 = U32_add(_t_U32_751, _t_U32_752);
    (void)_t_U32_757;
    ;
    ;
    U32 _t_U32_758 = U32_sub(_t_U32_755, _t_U32_756);
    (void)_t_U32_758;
    ;
    ;
    Str *frac_part = Str_substr(rest, &_t_U32_757, &_t_U32_758);
    (void)frac_part;
    ;
    ;
    Str_delete(rest, &(Bool){1});
    I64 _t_I64_759 = 0;
    (void)_t_I64_759;
    F32 out = I64_to_f32(_t_I64_759);
    (void)out;
    ;
    U32 _t_U32_760 = Str_len(int_part);
    (void)_t_U32_760;
    U32 _t_U32_761 = 0;
    (void)_t_U32_761;
    Bool _t_Bool_762 = U32_gt(&_t_U32_760, &_t_U32_761);
    (void)_t_Bool_762;
    ;
    ;
    if (_t_Bool_762) {
        I64 _t_I64_715 = Str_to_i64(int_part);
        (void)_t_I64_715;
        F32 _t_F32_716 = I64_to_f32(_t_I64_715);
        (void)_t_F32_716;
        ;
        out = _t_F32_716;
        ;
    }
    ;
    Str_delete(int_part, &(Bool){1});
    U32 _t_U32_763 = Str_len(frac_part);
    (void)_t_U32_763;
    U32 _t_U32_764 = 0;
    (void)_t_U32_764;
    Bool _t_Bool_765 = U32_gt(&_t_U32_763, &_t_U32_764);
    (void)_t_Bool_765;
    ;
    ;
    if (_t_Bool_765) {
        I64 _t_I64_727 = Str_to_i64(frac_part);
        (void)_t_I64_727;
        F32 frac = I64_to_f32(_t_I64_727);
        (void)frac;
        ;
        I64 _t_I64_728 = 1;
        (void)_t_I64_728;
        F32 scale = I64_to_f32(_t_I64_728);
        (void)scale;
        ;
        {
            U32 _re_U32_717 = Str_len(frac_part);
            (void)_re_U32_717;
            U32 _rc_U32_717 = 0;
            (void)_rc_U32_717;
            Bool _t_Bool_726 = U32_lte(&_rc_U32_717, &_re_U32_717);
            (void)_t_Bool_726;
            if (_t_Bool_726) {
                while (1) {
                    Bool _wcond_Bool_718 = U32_lt(&_rc_U32_717, &_re_U32_717);
                    (void)_wcond_Bool_718;
                    if (_wcond_Bool_718) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_717);
                    (void)_;
                    ;
                    U32_inc(&_rc_U32_717);
                    I64 _t_I64_719 = 10;
                    (void)_t_I64_719;
                    F32 _t_F32_720 = I64_to_f32(_t_I64_719);
                    (void)_t_F32_720;
                    ;
                    F32 _t_F32_721 = F32_mul(scale, _t_F32_720);
                    (void)_t_F32_721;
                    ;
                    scale = _t_F32_721;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_722 = U32_gt(&_rc_U32_717, &_re_U32_717);
                    (void)_wcond_Bool_722;
                    if (_wcond_Bool_722) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_717);
                    (void)_;
                    ;
                    U32_dec(&_rc_U32_717);
                    I64 _t_I64_723 = 10;
                    (void)_t_I64_723;
                    F32 _t_F32_724 = I64_to_f32(_t_I64_723);
                    (void)_t_F32_724;
                    ;
                    F32 _t_F32_725 = F32_mul(scale, _t_F32_724);
                    (void)_t_F32_725;
                    ;
                    scale = _t_F32_725;
                    ;
                }
            }
            ;
            ;
            ;
        }
        F32 _t_F32_729 = F32_div(frac, scale);
        (void)_t_F32_729;
        ;
        ;
        F32 _t_F32_730 = F32_add(out, _t_F32_729);
        (void)_t_F32_730;
        ;
        out = _t_F32_730;
        ;
    }
    ;
    Str_delete(frac_part, &(Bool){1});
    if (neg) {
        I64 _t_I64_731 = 0;
        (void)_t_I64_731;
        F32 _t_F32_732 = I64_to_f32(_t_I64_731);
        (void)_t_F32_732;
        ;
        F32 _t_F32_733 = F32_sub(_t_F32_732, out);
        (void)_t_F32_733;
        ;
        ;
        ;
        return _t_F32_733;
    }
    ;
    return out;
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t_Str_782 = Str_lit("Str", 3ULL);
    (void)_t_Str_782;
    Vec *parts = Vec_new(_t_Str_782);
    (void)parts;
    Str_delete(_t_Str_782, &(Bool){1});
    U32 _t_U32_783 = Str_len(delim);
    (void)_t_U32_783;
    U32 _t_U32_784 = 0;
    (void)_t_U32_784;
    Bool _t_Bool_785 = U32_eq(_t_U32_783, _t_U32_784);
    (void)_t_Bool_785;
    ;
    ;
    if (_t_Bool_785) {
        Str *_t_Str_766 = Str_clone(self);
        (void)_t_Str_766;
        Vec_push(parts, _t_Str_766);
        ;
        return parts;
    }
    ;
    U32 start = 0;
    (void)start;
    U32 pos = 0;
    (void)pos;
    while (1) {
        U32 _t_U32_776 = Str_len(self);
        (void)_t_U32_776;
        U32 _t_U32_777 = Str_len(delim);
        (void)_t_U32_777;
        U32 _t_U32_778 = U32_sub(_t_U32_776, _t_U32_777);
        (void)_t_U32_778;
        ;
        ;
        Bool _wcond_Bool_767 = U32_lte(&pos, &_t_U32_778);
        (void)_wcond_Bool_767;
        ;
        if (_wcond_Bool_767) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_779 = Str_len(delim);
        (void)_t_U32_779;
        Str *_t_Str_780 = Str_substr(self, &pos, &_t_U32_779);
        (void)_t_Str_780;
        ;
        Bool _t_Bool_781 = Str_eq(_t_Str_780, delim);
        (void)_t_Bool_781;
        Str_delete(_t_Str_780, &(Bool){1});
        if (_t_Bool_781) {
            U32 _t_U32_768 = U32_sub(pos, start);
            (void)_t_U32_768;
            Str *_t_Str_769 = Str_substr(self, &start, &_t_U32_768);
            (void)_t_Str_769;
            ;
            Str *_t_Str_770 = Str_clone(_t_Str_769);
            (void)_t_Str_770;
            Str_delete(_t_Str_769, &(Bool){1});
            Vec_push(parts, _t_Str_770);
            U32 _t_U32_771 = Str_len(delim);
            (void)_t_U32_771;
            U32 _t_U32_772 = U32_add(pos, _t_U32_771);
            (void)_t_U32_772;
            ;
            start = _t_U32_772;
            ;
            U32 _t_U32_773 = U32_clone(&start);
            (void)_t_U32_773;
            pos = _t_U32_773;
            ;
        } else {
            U32 _t_U32_774 = 1;
            (void)_t_U32_774;
            U32 _t_U32_775 = U32_add(pos, _t_U32_774);
            (void)_t_U32_775;
            ;
            pos = _t_U32_775;
            ;
        }
        ;
    }
    ;
    U32 _t_U32_786 = Str_len(self);
    (void)_t_U32_786;
    U32 _t_U32_787 = U32_sub(_t_U32_786, start);
    (void)_t_U32_787;
    ;
    Str *_t_Str_788 = Str_substr(self, &start, &_t_U32_787);
    (void)_t_Str_788;
    ;
    ;
    Str *_t_Str_789 = Str_clone(_t_Str_788);
    (void)_t_Str_789;
    Str_delete(_t_Str_788, &(Bool){1});
    Vec_push(parts, _t_Str_789);
    return parts;
}

U32 Str_size(void) {
    I64 _t_I64_790 = 16;
    (void)_t_I64_790;
    return _t_I64_790;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_791 = Str_cmp(a, b);
    (void)_t_I64_791;
    I64 _t_I64_792 = 0;
    (void)_t_I64_792;
    Bool _t_Bool_793 = I64_eq(_t_I64_791, _t_I64_792);
    (void)_t_Bool_793;
    ;
    ;
    return _t_Bool_793;
}

Bool Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_794 = 0;
    (void)_t_I64_794;
    I64 _t_I64_795 = 1;
    (void)_t_I64_795;
    I64 _t_I64_796 = Str_cmp(a, b);
    (void)_t_I64_796;
    I64 _t_I64_797 = I64_sub(_t_I64_794, _t_I64_795);
    (void)_t_I64_797;
    ;
    ;
    Bool _t_Bool_798 = I64_eq(_t_I64_796, _t_I64_797);
    (void)_t_Bool_798;
    ;
    ;
    return _t_Bool_798;
}

Bool Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_799 = Str_cmp(a, b);
    (void)_t_I64_799;
    I64 _t_I64_800 = 1;
    (void)_t_I64_800;
    Bool _t_Bool_801 = I64_eq(_t_I64_799, _t_I64_800);
    (void)_t_Bool_801;
    ;
    ;
    return _t_Bool_801;
}

Bool Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_802 = Str_eq(a, b);
    (void)_t_Bool_802;
    Bool _t_Bool_803 = not(_t_Bool_802);
    (void)_t_Bool_803;
    ;
    return _t_Bool_803;
}

Bool Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_804 = Str_gt(a, b);
    (void)_t_Bool_804;
    Bool _t_Bool_805 = not(_t_Bool_804);
    (void)_t_Bool_805;
    ;
    return _t_Bool_805;
}

Bool Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_806 = Str_lt(a, b);
    (void)_t_Bool_806;
    Bool _t_Bool_807 = not(_t_Bool_806);
    (void)_t_Bool_807;
    ;
    return _t_Bool_807;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_839 = 8;
    (void)_t_I64_839;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_839; return _r; }
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
    I64 _t_I64_842 = I16_to_i64(DEREF(val));
    (void)_t_I64_842;
    Str *_t_Str_843 = I64_to_str(&_t_I64_842);
    (void)_t_Str_843;
    ;
    return _t_Str_843;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t_I16_844 = 1;
    (void)_t_I16_844;
    I16 _t_I16_845 = I16_add(DEREF(self), _t_I16_844);
    (void)_t_I16_845;
    ;
    *self = _t_I16_845;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t_I16_846 = 1;
    (void)_t_I16_846;
    I16 _t_I16_847 = I16_sub(DEREF(self), _t_I16_846);
    (void)_t_I16_847;
    ;
    *self = _t_I16_847;
    ;
}

I16 * I16_unity(I16 * _self) {
    (void)_self;
    I64 _t_I64_848 = 1;
    (void)_t_I64_848;
    I16 _t_I16_849 = I64_to_i16(_t_I64_848);
    (void)_t_I16_849;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_849; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t_I64_850 = 0;
    (void)_t_I64_850;
    I64 _t_I64_851 = I16_to_i64(DEREF(a));
    (void)_t_I64_851;
    I64 _t_I64_852 = I64_sub(_t_I64_850, _t_I64_851);
    (void)_t_I64_852;
    ;
    ;
    I16 _t_I16_853 = I64_to_i16(_t_I64_852);
    (void)_t_I16_853;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_853; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t_I64_858 = I16_to_i64(DEREF(a));
    (void)_t_I64_858;
    I64 _t_I64_859 = 0;
    (void)_t_I64_859;
    Bool _t_Bool_860 = I64_lt(&_t_I64_858, &_t_I64_859);
    (void)_t_Bool_860;
    ;
    ;
    if (_t_Bool_860) {
        I64 _t_I64_854 = 0;
        (void)_t_I64_854;
        I64 _t_I64_855 = I16_to_i64(DEREF(a));
        (void)_t_I64_855;
        I64 _t_I64_856 = I64_sub(_t_I64_854, _t_I64_855);
        (void)_t_I64_856;
        ;
        ;
        I16 _t_I16_857 = I64_to_i16(_t_I64_856);
        (void)_t_I16_857;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_857; return _r; }
    }
    ;
    I16 _t_I16_861 = I16_clone(a);
    (void)_t_I16_861;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_861; return _r; }
}

U64 I16_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I16 *au = a;
    (void)au;
    I16 *bu = b;
    (void)bu;
    Bool _t_Bool_865 = I16_lte(au, bu);
    (void)_t_Bool_865;
    if (_t_Bool_865) {
        I16 _t_I16_862 = I16_sub(DEREF(bu), DEREF(au));
        (void)_t_I16_862;
        I64 _t_I64_863 = I16_to_i64(_t_I16_862);
        (void)_t_I64_863;
        ;
        U64 _t_U64_864 = I64_to_u64(_t_I64_863);
        (void)_t_U64_864;
        ;
        ;
        return _t_U64_864;
    }
    ;
    I16 _t_I16_866 = I16_sub(DEREF(au), DEREF(bu));
    (void)_t_I16_866;
    I64 _t_I64_867 = I16_to_i64(_t_I16_866);
    (void)_t_I64_867;
    ;
    U64 _t_U64_868 = I64_to_u64(_t_I64_867);
    (void)_t_U64_868;
    ;
    return _t_U64_868;
}

void I16_delete(I16 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I16_size(void) {
    I64 _t_I64_869 = 2;
    (void)_t_I64_869;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_869; return _r; }
}

Bool I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_870 = 0;
    (void)_t_I64_870;
    I64 _t_I64_871 = 1;
    (void)_t_I64_871;
    I64 _t_I64_872 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_872;
    I64 _t_I64_873 = I64_sub(_t_I64_870, _t_I64_871);
    (void)_t_I64_873;
    ;
    ;
    Bool _t_Bool_874 = I64_eq(_t_I64_872, _t_I64_873);
    (void)_t_Bool_874;
    ;
    ;
    return _t_Bool_874;
}

Bool I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_875 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_875;
    I64 _t_I64_876 = 1;
    (void)_t_I64_876;
    Bool _t_Bool_877 = I64_eq(_t_I64_875, _t_I64_876);
    (void)_t_Bool_877;
    ;
    ;
    return _t_Bool_877;
}

Bool I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_878 = I16_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_878;
    Bool _t_Bool_879 = not(_t_Bool_878);
    (void)_t_Bool_879;
    ;
    return _t_Bool_879;
}

Bool I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_880 = I16_gt(a, b);
    (void)_t_Bool_880;
    Bool _t_Bool_881 = not(_t_Bool_880);
    (void)_t_Bool_881;
    ;
    return _t_Bool_881;
}

Bool I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_882 = I16_lt(a, b);
    (void)_t_Bool_882;
    Bool _t_Bool_883 = not(_t_Bool_882);
    (void)_t_Bool_883;
    ;
    return _t_Bool_883;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_920 = 0;
    (void)_t_I64_920;
    Bool _t_Bool_921 = I64_eq(DEREF(val), _t_I64_920);
    (void)_t_Bool_921;
    ;
    if (_t_Bool_921) {
        U64 _t_U64_884 = 2;
        (void)_t_U64_884;
        void * buf = malloc(_t_U64_884);
        (void)buf;
        ;
        I64 _t_I64_885 = 48;
        (void)_t_I64_885;
        U64 _t_U64_886 = 1;
        (void)_t_U64_886;
        memcpy(buf, &_t_I64_885, _t_U64_886);
        ;
        ;
        U64 _t_U64_887 = 1;
        (void)_t_U64_887;
        void *_t_v_888 = ptr_add(buf, _t_U64_887);
        (void)_t_v_888;
        I32 _t_I32_889 = 0;
        (void)_t_I32_889;
        U64 _t_U64_890 = 1;
        (void)_t_U64_890;
        memset(_t_v_888, _t_I32_889, _t_U64_890);
        ;
        ;
        ;
        I64 _t_I64_891 = 1;
        (void)_t_I64_891;
        I64 _t_I64_892 = 1;
        (void)_t_I64_892;
        Str *_t_Str_893 = malloc(sizeof(Str));
        _t_Str_893->c_str = buf;
        _t_Str_893->count = _t_I64_891;
        _t_Str_893->cap = _t_I64_892;
        (void)_t_Str_893;
        ;
        ;
        ;
        return _t_Str_893;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t_I64_922 = 0;
    (void)_t_I64_922;
    Bool _t_Bool_923 = I64_lt(val, &_t_I64_922);
    (void)_t_Bool_923;
    ;
    if (_t_Bool_923) {
        Bool _t_Bool_894 = 1;
        (void)_t_Bool_894;
        is_neg = _t_Bool_894;
        ;
        I64 _t_I64_895 = 0;
        (void)_t_I64_895;
        I64 _t_I64_896 = I64_sub(_t_I64_895, DEREF(val));
        (void)_t_I64_896;
        ;
        v = _t_I64_896;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&v);
    (void)tmp;
    while (1) {
        I64 _t_I64_898 = 0;
        (void)_t_I64_898;
        Bool _wcond_Bool_897 = I64_gt(&tmp, &_t_I64_898);
        (void)_wcond_Bool_897;
        ;
        if (_wcond_Bool_897) {
        } else {
            ;
            break;
        }
        ;
        U64 _t_U64_899 = 1;
        (void)_t_U64_899;
        U64 _t_U64_900 = U64_add(ndigits, _t_U64_899);
        (void)_t_U64_900;
        ;
        ndigits = _t_U64_900;
        ;
        I64 _t_I64_901 = 10;
        (void)_t_I64_901;
        I64 _t_I64_902 = I64_div(tmp, _t_I64_901);
        (void)_t_I64_902;
        ;
        tmp = _t_I64_902;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    (void)total;
    ;
    if (is_neg) {
        U64 _t_U64_903 = 1;
        (void)_t_U64_903;
        U64 _t_U64_904 = U64_add(total, _t_U64_903);
        (void)_t_U64_904;
        ;
        total = _t_U64_904;
        ;
    }
    U64 _t_U64_924 = 1;
    (void)_t_U64_924;
    U64 _t_U64_925 = U64_add(total, _t_U64_924);
    (void)_t_U64_925;
    ;
    void * buf = malloc(_t_U64_925);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t_I64_905 = 45;
        (void)_t_I64_905;
        U64 _t_U64_906 = 1;
        (void)_t_U64_906;
        memcpy(buf, &_t_I64_905, _t_U64_906);
        ;
        ;
    }
    ;
    U64 _t_U64_926 = 1;
    (void)_t_U64_926;
    U64 i = U64_sub(total, _t_U64_926);
    (void)i;
    ;
    while (1) {
        I64 _t_I64_908 = 0;
        (void)_t_I64_908;
        Bool _wcond_Bool_907 = I64_gt(&v, &_t_I64_908);
        (void)_wcond_Bool_907;
        ;
        if (_wcond_Bool_907) {
        } else {
            ;
            break;
        }
        ;
        I64 _t_I64_909 = 10;
        (void)_t_I64_909;
        I64 _t_I64_910 = I64_mod(v, _t_I64_909);
        (void)_t_I64_910;
        ;
        I64 _t_I64_911 = 48;
        (void)_t_I64_911;
        I64 _t_I64_912 = I64_add(_t_I64_910, _t_I64_911);
        (void)_t_I64_912;
        ;
        ;
        void *_t_v_913 = ptr_add(buf, i);
        (void)_t_v_913;
        U8 _t_U8_914 = I64_to_u8(_t_I64_912);
        (void)_t_U8_914;
        ;
        U64 _t_U64_915 = 1;
        (void)_t_U64_915;
        memcpy(_t_v_913, &_t_U8_914, _t_U64_915);
        ;
        ;
        I64 _t_I64_916 = 10;
        (void)_t_I64_916;
        I64 _t_I64_917 = I64_div(v, _t_I64_916);
        (void)_t_I64_917;
        ;
        v = _t_I64_917;
        ;
        U64 _t_U64_918 = 1;
        (void)_t_U64_918;
        U64 _t_U64_919 = U64_sub(i, _t_U64_918);
        (void)_t_U64_919;
        ;
        i = _t_U64_919;
        ;
    }
    ;
    ;
    void *_t_v_927 = ptr_add(buf, total);
    (void)_t_v_927;
    I32 _t_I32_928 = 0;
    (void)_t_I32_928;
    U64 _t_U64_929 = 1;
    (void)_t_U64_929;
    memset(_t_v_927, _t_I32_928, _t_U64_929);
    ;
    ;
    Str *_t_Str_930 = malloc(sizeof(Str));
    _t_Str_930->c_str = buf;
    _t_Str_930->count = total;
    _t_Str_930->cap = total;
    (void)_t_Str_930;
    ;
    return _t_Str_930;
}

U32 I64_to_usize(I64 val) {
    (void)val;
    U32 _t_U32_931 = I64_to_u32(val);
    (void)_t_U32_931;
    return _t_U32_931;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t_I64_932 = 1;
    (void)_t_I64_932;
    I64 _t_I64_933 = I64_add(DEREF(self), _t_I64_932);
    (void)_t_I64_933;
    ;
    *self = _t_I64_933;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t_I64_934 = 1;
    (void)_t_I64_934;
    I64 _t_I64_935 = I64_sub(DEREF(self), _t_I64_934);
    (void)_t_I64_935;
    ;
    *self = _t_I64_935;
    ;
}

I64 * I64_unity(I64 * _self) {
    (void)_self;
    I64 _t_I64_936 = 1;
    (void)_t_I64_936;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_936; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t_I64_937 = 0;
    (void)_t_I64_937;
    I64 _t_I64_938 = I64_sub(_t_I64_937, DEREF(a));
    (void)_t_I64_938;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_938; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t_I64_941 = 0;
    (void)_t_I64_941;
    Bool _t_Bool_942 = I64_lt(a, &_t_I64_941);
    (void)_t_Bool_942;
    ;
    if (_t_Bool_942) {
        I64 _t_I64_939 = 0;
        (void)_t_I64_939;
        I64 _t_I64_940 = I64_sub(_t_I64_939, DEREF(a));
        (void)_t_I64_940;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_940; return _r; }
    }
    ;
    I64 _t_I64_943 = I64_clone(a);
    (void)_t_I64_943;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_943; return _r; }
}

U64 I64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I64 *au = a;
    (void)au;
    I64 *bu = b;
    (void)bu;
    Bool _t_Bool_946 = I64_lte(au, bu);
    (void)_t_Bool_946;
    if (_t_Bool_946) {
        I64 _t_I64_944 = I64_sub(DEREF(bu), DEREF(au));
        (void)_t_I64_944;
        U64 _t_U64_945 = I64_to_u64(_t_I64_944);
        (void)_t_U64_945;
        ;
        ;
        return _t_U64_945;
    }
    ;
    I64 _t_I64_947 = I64_sub(DEREF(au), DEREF(bu));
    (void)_t_I64_947;
    U64 _t_U64_948 = I64_to_u64(_t_I64_947);
    (void)_t_U64_948;
    ;
    return _t_U64_948;
}

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_949 = 8;
    (void)_t_I64_949;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_949; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_950 = 0;
    (void)_t_I64_950;
    I64 _t_I64_951 = 1;
    (void)_t_I64_951;
    I64 _t_I64_952 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_952;
    I64 _t_I64_953 = I64_sub(_t_I64_950, _t_I64_951);
    (void)_t_I64_953;
    ;
    ;
    Bool _t_Bool_954 = I64_eq(_t_I64_952, _t_I64_953);
    (void)_t_Bool_954;
    ;
    ;
    return _t_Bool_954;
}

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_955 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_955;
    I64 _t_I64_956 = 1;
    (void)_t_I64_956;
    Bool _t_Bool_957 = I64_eq(_t_I64_955, _t_I64_956);
    (void)_t_Bool_957;
    ;
    ;
    return _t_Bool_957;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_958 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_958;
    Bool _t_Bool_959 = not(_t_Bool_958);
    (void)_t_Bool_959;
    ;
    return _t_Bool_959;
}

Bool I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_960 = I64_gt(a, b);
    (void)_t_Bool_960;
    Bool _t_Bool_961 = not(_t_Bool_960);
    (void)_t_Bool_961;
    ;
    return _t_Bool_961;
}

Bool I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_962 = I64_lt(a, b);
    (void)_t_Bool_962;
    Bool _t_Bool_963 = not(_t_Bool_962);
    (void)_t_Bool_963;
    ;
    return _t_Bool_963;
}

Str * Bool_to_str(Bool * b) {
    (void)b;
    if (DEREF(b)) {
        Str *_t_Str_964 = Str_lit("true", 4ULL);
        (void)_t_Str_964;
        return _t_Str_964;
    } else {
        Str *_t_Str_965 = Str_lit("false", 5ULL);
        (void)_t_Str_965;
        return _t_Str_965;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_970 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_970;
    if (_t_Bool_970) {
        I64 _t_I64_966 = 0;
        (void)_t_I64_966;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_966; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_967 = 0;
        (void)_t_I64_967;
        I64 _t_I64_968 = 1;
        (void)_t_I64_968;
        I64 _t_I64_969 = I64_sub(_t_I64_967, _t_I64_968);
        (void)_t_I64_969;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_969; return _r; }
    }
    I64 _t_I64_971 = 1;
    (void)_t_I64_971;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_971; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_972 = 1;
    (void)_t_I64_972;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_972; return _r; }
}

Bool Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_973 = 0;
    (void)_t_I64_973;
    I64 _t_I64_974 = 1;
    (void)_t_I64_974;
    I64 _t_I64_975; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_975 = *_hp; free(_hp); }
    (void)_t_I64_975;
    I64 _t_I64_976 = I64_sub(_t_I64_973, _t_I64_974);
    (void)_t_I64_976;
    ;
    ;
    Bool _t_Bool_977 = I64_eq(_t_I64_975, _t_I64_976);
    (void)_t_Bool_977;
    ;
    ;
    return _t_Bool_977;
}

Bool Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_978; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_978 = *_hp; free(_hp); }
    (void)_t_I64_978;
    I64 _t_I64_979 = 1;
    (void)_t_I64_979;
    Bool _t_Bool_980 = I64_eq(_t_I64_978, _t_I64_979);
    (void)_t_Bool_980;
    ;
    ;
    return _t_Bool_980;
}

Bool Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_981 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_981;
    Bool _t_Bool_982 = not(_t_Bool_981);
    (void)_t_Bool_982;
    ;
    return _t_Bool_982;
}

Bool Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_983 = Bool_gt(a, b);
    (void)_t_Bool_983;
    Bool _t_Bool_984 = not(_t_Bool_983);
    (void)_t_Bool_984;
    ;
    return _t_Bool_984;
}

Bool Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_985 = Bool_lt(a, b);
    (void)_t_Bool_985;
    Bool _t_Bool_986 = not(_t_Bool_985);
    (void)_t_Bool_986;
    ;
    return _t_Bool_986;
}

Array * Array_new(Str * elem_type, U32 * cap) {
    (void)elem_type;
    (void)cap;
    Bool _t_Bool_992 = Str_is_empty(elem_type);
    (void)_t_Bool_992;
    if (_t_Bool_992) {
        Str *_t_Str_987 = Str_lit("Str", 3ULL);
        (void)_t_Str_987;
        U32 _t_U32_988 = 1;
        (void)_t_U32_988;
        Array *_va_Array_16 = Array_new(_t_Str_987, &_t_U32_988);
        (void)_va_Array_16;
        Str_delete(_t_Str_987, &(Bool){1});
        ;
        U32 _t_U32_989 = 0;
        (void)_t_U32_989;
        Str *_t_Str_990 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_990;
        Array_set(_va_Array_16, &_t_U32_989, _t_Str_990);
        ;
        Str *_t_Str_991 = Str_lit("./src/core/array.til:22:41", 26ULL);
        (void)_t_Str_991;
        panic(_t_Str_991, _va_Array_16);
        Str_delete(_t_Str_991, &(Bool){1});
    }
    ;
    U32 elem_size = dyn_size_of(elem_type);
    (void)elem_size;
    void * _t_v_993 = calloc(DEREF(cap), elem_size);
    (void)_t_v_993;
    void * _t_v_994 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_994;
    void * _t_v_995 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_995;
    Array *_t_Array_996 = malloc(sizeof(Array));
    _t_Array_996->data = _t_v_993;
    _t_Array_996->cap = DEREF(cap);
    _t_Array_996->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); _t_Array_996->elem_type = *_ca; free(_ca); }
    _t_Array_996->elem_clone = _t_v_994;
    _t_Array_996->elem_delete = _t_v_995;
    (void)_t_Array_996;
    ;
    return _t_Array_996;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_1010 = U32_gte(i, &self->cap);
    (void)_t_Bool_1010;
    if (_t_Bool_1010) {
        Str *_t_Str_997 = Str_lit("Str", 3ULL);
        (void)_t_Str_997;
        U32 _t_U32_998 = 5;
        (void)_t_U32_998;
        Array *_va_Array_17 = Array_new(_t_Str_997, &_t_U32_998);
        (void)_va_Array_17;
        Str_delete(_t_Str_997, &(Bool){1});
        ;
        U32 _t_U32_999 = 0;
        (void)_t_U32_999;
        Str *_t_Str_1000 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_1000;
        Array_set(_va_Array_17, &_t_U32_999, _t_Str_1000);
        ;
        U32 _t_U32_1001 = 1;
        (void)_t_U32_1001;
        Str *_t_Str_1002 = U32_to_str(i);
        (void)_t_Str_1002;
        Array_set(_va_Array_17, &_t_U32_1001, _t_Str_1002);
        ;
        U32 _t_U32_1003 = 2;
        (void)_t_U32_1003;
        Str *_t_Str_1004 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1004;
        Array_set(_va_Array_17, &_t_U32_1003, _t_Str_1004);
        ;
        U32 _t_U32_1005 = 3;
        (void)_t_U32_1005;
        Str *_t_Str_1006 = U32_to_str(&self->cap);
        (void)_t_Str_1006;
        Array_set(_va_Array_17, &_t_U32_1005, _t_Str_1006);
        ;
        U32 _t_U32_1007 = 4;
        (void)_t_U32_1007;
        Str *_t_Str_1008 = Str_lit(")", 1ULL);
        (void)_t_Str_1008;
        Array_set(_va_Array_17, &_t_U32_1007, _t_Str_1008);
        ;
        Str *_t_Str_1009 = Str_lit("./src/core/array.til:35:19", 26ULL);
        (void)_t_Str_1009;
        panic(_t_Str_1009, _va_Array_17);
        Str_delete(_t_Str_1009, &(Bool){1});
    }
    ;
    U32 _t_U64_1011 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1011;
    void *_t_v_1012 = ptr_add(self->data, _t_U64_1011);
    (void)_t_v_1012;
    ;
    return _t_v_1012;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_1026 = U32_gte(i, &self->cap);
    (void)_t_Bool_1026;
    if (_t_Bool_1026) {
        Str *_t_Str_1013 = Str_lit("Str", 3ULL);
        (void)_t_Str_1013;
        U32 _t_U32_1014 = 5;
        (void)_t_U32_1014;
        Array *_va_Array_18 = Array_new(_t_Str_1013, &_t_U32_1014);
        (void)_va_Array_18;
        Str_delete(_t_Str_1013, &(Bool){1});
        ;
        U32 _t_U32_1015 = 0;
        (void)_t_U32_1015;
        Str *_t_Str_1016 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_1016;
        Array_set(_va_Array_18, &_t_U32_1015, _t_Str_1016);
        ;
        U32 _t_U32_1017 = 1;
        (void)_t_U32_1017;
        Str *_t_Str_1018 = U32_to_str(i);
        (void)_t_Str_1018;
        Array_set(_va_Array_18, &_t_U32_1017, _t_Str_1018);
        ;
        U32 _t_U32_1019 = 2;
        (void)_t_U32_1019;
        Str *_t_Str_1020 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1020;
        Array_set(_va_Array_18, &_t_U32_1019, _t_Str_1020);
        ;
        U32 _t_U32_1021 = 3;
        (void)_t_U32_1021;
        Str *_t_Str_1022 = U32_to_str(&self->cap);
        (void)_t_Str_1022;
        Array_set(_va_Array_18, &_t_U32_1021, _t_Str_1022);
        ;
        U32 _t_U32_1023 = 4;
        (void)_t_U32_1023;
        Str *_t_Str_1024 = Str_lit(")", 1ULL);
        (void)_t_Str_1024;
        Array_set(_va_Array_18, &_t_U32_1023, _t_Str_1024);
        ;
        Str *_t_Str_1025 = Str_lit("./src/core/array.til:44:19", 26ULL);
        (void)_t_Str_1025;
        panic(_t_Str_1025, _va_Array_18);
        Str_delete(_t_Str_1025, &(Bool){1});
    }
    ;
    U32 _t_U64_1027 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1027;
    void *_t_v_1028 = ptr_add(self->data, _t_U64_1027);
    (void)_t_v_1028;
    Bool _t_Bool_1029 = 0;
    (void)_t_Bool_1029;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1028, &_t_Bool_1029);
    ;
    ;
    U32 _t_U64_1030 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1030;
    void *_t_v_1031 = ptr_add(self->data, _t_U64_1030);
    (void)_t_v_1031;
    memcpy(_t_v_1031, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_1032 = self->cap;
        (void)_re_U32_1032;
        U32 _rc_U32_1032 = 0;
        (void)_rc_U32_1032;
        Bool _t_Bool_1041 = U32_lte(&_rc_U32_1032, &_re_U32_1032);
        (void)_t_Bool_1041;
        if (_t_Bool_1041) {
            while (1) {
                Bool _wcond_Bool_1033 = U32_lt(&_rc_U32_1032, &_re_U32_1032);
                (void)_wcond_Bool_1033;
                if (_wcond_Bool_1033) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1032);
                (void)i;
                U32_inc(&_rc_U32_1032);
                U32 _t_U64_1034 = U32_mul(i, self->elem_size);
                (void)_t_U64_1034;
                ;
                void *_t_v_1035 = ptr_add(self->data, _t_U64_1034);
                (void)_t_v_1035;
                Bool _t_Bool_1036 = 0;
                (void)_t_Bool_1036;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1035, &_t_Bool_1036);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1037 = U32_gt(&_rc_U32_1032, &_re_U32_1032);
                (void)_wcond_Bool_1037;
                if (_wcond_Bool_1037) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1032);
                (void)i;
                U32_dec(&_rc_U32_1032);
                U32 _t_U64_1038 = U32_mul(i, self->elem_size);
                (void)_t_U64_1038;
                ;
                void *_t_v_1039 = ptr_add(self->data, _t_U64_1038);
                (void)_t_v_1039;
                Bool _t_Bool_1040 = 0;
                (void)_t_Bool_1040;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1039, &_t_Bool_1040);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_1042 = 0;
    (void)_t_Bool_1042;
    Str_delete(&self->elem_type, &_t_Bool_1042);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_1055 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_1055;
    void * new_data = malloc(_t_U64_1055);
    (void)new_data;
    ;
    {
        U32 _re_U32_1043 = self->cap;
        (void)_re_U32_1043;
        U32 _rc_U32_1043 = 0;
        (void)_rc_U32_1043;
        Bool _t_Bool_1054 = U32_lte(&_rc_U32_1043, &_re_U32_1043);
        (void)_t_Bool_1054;
        if (_t_Bool_1054) {
            while (1) {
                Bool _wcond_Bool_1044 = U32_lt(&_rc_U32_1043, &_re_U32_1043);
                (void)_wcond_Bool_1044;
                if (_wcond_Bool_1044) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1043);
                (void)i;
                U32_inc(&_rc_U32_1043);
                U32 _t_U64_1045 = U32_mul(i, self->elem_size);
                (void)_t_U64_1045;
                void *_t_v_1046 = ptr_add(self->data, _t_U64_1045);
                (void)_t_v_1046;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1046);
                (void)cloned;
                ;
                U32 _t_U64_1047 = U32_mul(i, self->elem_size);
                (void)_t_U64_1047;
                ;
                void *_t_v_1048 = ptr_add(new_data, _t_U64_1047);
                (void)_t_v_1048;
                memcpy(_t_v_1048, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1049 = U32_gt(&_rc_U32_1043, &_re_U32_1043);
                (void)_wcond_Bool_1049;
                if (_wcond_Bool_1049) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1043);
                (void)i;
                U32_dec(&_rc_U32_1043);
                U32 _t_U64_1050 = U32_mul(i, self->elem_size);
                (void)_t_U64_1050;
                void *_t_v_1051 = ptr_add(self->data, _t_U64_1050);
                (void)_t_v_1051;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1051);
                (void)cloned;
                ;
                U32 _t_U64_1052 = U32_mul(i, self->elem_size);
                (void)_t_U64_1052;
                ;
                void *_t_v_1053 = ptr_add(new_data, _t_U64_1052);
                (void)_t_v_1053;
                memcpy(_t_v_1053, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_1056 = malloc(sizeof(Array));
    _t_Array_1056->data = new_data;
    _t_Array_1056->cap = self->cap;
    _t_Array_1056->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_1056->elem_type = *_ca; free(_ca); }
    _t_Array_1056->elem_clone = (void *)self->elem_clone;
    _t_Array_1056->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_1056;
    return _t_Array_1056;
}

U32 Array_size(void) {
    I64 _t_I64_1057 = 48;
    (void)_t_I64_1057;
    return _t_I64_1057;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2618 = Str_lit("Str", 3ULL);
    (void)_t_Str_2618;
    U32 _t_U32_2619 = 3;
    (void)_t_U32_2619;
    Array *_va_Array_92 = Array_new(_t_Str_2618, &_t_U32_2619);
    (void)_va_Array_92;
    Str_delete(_t_Str_2618, &(Bool){1});
    ;
    U32 _t_U32_2620 = 0;
    (void)_t_U32_2620;
    Str *_t_Str_2621 = Str_clone(loc_str);
    (void)_t_Str_2621;
    Array_set(_va_Array_92, &_t_U32_2620, _t_Str_2621);
    ;
    U32 _t_U32_2622 = 1;
    (void)_t_U32_2622;
    Str *_t_Str_2623 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2623;
    Array_set(_va_Array_92, &_t_U32_2622, _t_Str_2623);
    ;
    Array *_t_Array_2624 = Array_clone(parts);
    (void)_t_Array_2624;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2625 = 2;
    (void)_t_U32_2625;
    Str *_t_Str_2626 = format(_t_Array_2624);
    (void)_t_Str_2626;
    Array_set(_va_Array_92, &_t_U32_2625, _t_Str_2626);
    ;
    println(_va_Array_92);
    I64 _t_I64_2627 = 1;
    (void)_t_I64_2627;
    exit(_t_I64_2627);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2643 = not(DEREF(cond));
    (void)_t_Bool_2643;
    if (_t_Bool_2643) {
        Str *_t_Str_2639 = Str_lit("Str", 3ULL);
        (void)_t_Str_2639;
        U32 _t_U32_2640 = 1;
        (void)_t_U32_2640;
        Array *_va_Array_95 = Array_new(_t_Str_2639, &_t_U32_2640);
        (void)_va_Array_95;
        Str_delete(_t_Str_2639, &(Bool){1});
        ;
        U32 _t_U32_2641 = 0;
        (void)_t_U32_2641;
        Str *_t_Str_2642 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2642;
        Array_set(_va_Array_95, &_t_U32_2641, _t_Str_2642);
        ;
        panic(loc_str, _va_Array_95);
    }
    ;
    Bool _t_Bool_2644 = 1;
    (void)_t_Bool_2644;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2644; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2665 = I64_neq(a, b);
    (void)_t_Bool_2665;
    if (_t_Bool_2665) {
        Str *_t_Str_2653 = Str_lit("Str", 3ULL);
        (void)_t_Str_2653;
        U32 _t_U32_2654 = 5;
        (void)_t_U32_2654;
        Array *_va_Array_97 = Array_new(_t_Str_2653, &_t_U32_2654);
        (void)_va_Array_97;
        Str_delete(_t_Str_2653, &(Bool){1});
        ;
        U32 _t_U32_2655 = 0;
        (void)_t_U32_2655;
        Str *_t_Str_2656 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2656;
        Array_set(_va_Array_97, &_t_U32_2655, _t_Str_2656);
        ;
        U32 _t_U32_2657 = 1;
        (void)_t_U32_2657;
        Str *_t_Str_2658 = I64_to_str(a);
        (void)_t_Str_2658;
        Array_set(_va_Array_97, &_t_U32_2657, _t_Str_2658);
        ;
        U32 _t_U32_2659 = 2;
        (void)_t_U32_2659;
        Str *_t_Str_2660 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2660;
        Array_set(_va_Array_97, &_t_U32_2659, _t_Str_2660);
        ;
        U32 _t_U32_2661 = 3;
        (void)_t_U32_2661;
        Str *_t_Str_2662 = I64_to_str(b);
        (void)_t_Str_2662;
        Array_set(_va_Array_97, &_t_U32_2661, _t_Str_2662);
        ;
        U32 _t_U32_2663 = 4;
        (void)_t_U32_2663;
        Str *_t_Str_2664 = Str_lit("'", 1ULL);
        (void)_t_Str_2664;
        Array_set(_va_Array_97, &_t_U32_2663, _t_Str_2664);
        ;
        panic(loc_str, _va_Array_97);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2680 = parts;
        (void)_fc_Array_2680;
        U32 _fi_USize_2680 = 0;
        (void)_fi_USize_2680;
        while (1) {
            U32 _t_U32_2682; { U32 *_hp = (U32 *)Array_len(_fc_Array_2680); _t_U32_2682 = *_hp; free(_hp); }
            (void)_t_U32_2682;
            Bool _wcond_Bool_2681 = U32_lt(&_fi_USize_2680, &_t_U32_2682);
            (void)_wcond_Bool_2681;
            ;
            if (_wcond_Bool_2681) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2680, &_fi_USize_2680);
            (void)s;
            U32 _t_U32_2683 = 1;
            (void)_t_U32_2683;
            U32 _t_U32_2684 = U32_add(_fi_USize_2680, _t_U32_2683);
            (void)_t_U32_2684;
            ;
            _fi_USize_2680 = _t_U32_2684;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

void test_simple_add(void) {
    I64 _t_I64_2870 = 1;
    (void)_t_I64_2870;
    I64 _t_I64_2871 = 2;
    (void)_t_I64_2871;
    I64 result = 3;
    (void)result;
    ;
    ;
    Str *_t_Str_2872 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_2872;
    I64 _t_I64_2873 = 3;
    (void)_t_I64_2873;
    assert_eq(_t_Str_2872, &result, &_t_I64_2873);
    ;
    Str_delete(_t_Str_2872, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 _t_I64_2874 = 1;
    (void)_t_I64_2874;
    I64 _t_I64_2875 = 2;
    (void)_t_I64_2875;
    I64 _t_I64_2876 = 10;
    (void)_t_I64_2876;
    I64 _t_I64_2877 = 5;
    (void)_t_I64_2877;
    I64 _t_I64_2878 = 3;
    (void)_t_I64_2878;
    ;
    ;
    I64 _t_I64_2879 = 5;
    (void)_t_I64_2879;
    ;
    ;
    I64 result = 15;
    (void)result;
    ;
    ;
    Str *_t_Str_2880 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_2880;
    I64 _t_I64_2881 = 15;
    (void)_t_I64_2881;
    assert_eq(_t_Str_2880, &result, &_t_I64_2881);
    ;
    Str_delete(_t_Str_2880, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 _t_I64_2882 = 2;
    (void)_t_I64_2882;
    I64 _t_I64_2883 = 3;
    (void)_t_I64_2883;
    I64 _t_I64_2884 = 4;
    (void)_t_I64_2884;
    I64 _t_I64_2885 = 5;
    (void)_t_I64_2885;
    I64 _t_I64_2886 = 6;
    (void)_t_I64_2886;
    ;
    ;
    I64 _t_I64_2887 = 20;
    (void)_t_I64_2887;
    ;
    ;
    I64 result = 26;
    (void)result;
    ;
    ;
    Str *_t_Str_2888 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_2888;
    I64 _t_I64_2889 = 26;
    (void)_t_I64_2889;
    assert_eq(_t_Str_2888, &result, &_t_I64_2889);
    ;
    Str_delete(_t_Str_2888, &(Bool){1});
    ;
}

Str * poem(I64 * depth, Str * current, Str * s1, Str * s2) {
    (void)depth;
    (void)current;
    (void)s1;
    (void)s2;
    I64 _t_I64_2897 = 4;
    (void)_t_I64_2897;
    Bool _t_Bool_2898 = I64_eq(DEREF(depth), _t_I64_2897);
    (void)_t_Bool_2898;
    ;
    if (_t_Bool_2898) {
        Str *_t_Str_2890 = Str_lit("\n", 2ULL);
        (void)_t_Str_2890;
        Str *_t_Str_2891 = Str_concat(current, _t_Str_2890);
        (void)_t_Str_2891;
        Str_delete(_t_Str_2890, &(Bool){1});
        ;
        return _t_Str_2891;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    I64 _t_I64_2899 = 1;
    (void)_t_I64_2899;
    I64 _t_I64_2900 = I64_add(DEREF(depth), _t_I64_2899);
    (void)_t_I64_2900;
    ;
    Str *_t_Str_2901 = Str_concat(current, s1);
    (void)_t_Str_2901;
    Str *_t_Str_2902 = poem(&_t_I64_2900, _t_Str_2901, s1, s2);
    (void)_t_Str_2902;
    ;
    Str_delete(_t_Str_2901, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2902); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2902, &(Bool){1});
    I64 _t_I64_2903 = 1;
    (void)_t_I64_2903;
    I64 _t_I64_2904 = I64_add(DEREF(depth), _t_I64_2903);
    (void)_t_I64_2904;
    ;
    Str *_t_Str_2905 = Str_concat(current, s2);
    (void)_t_Str_2905;
    Str *_t_Str_2906 = poem(&_t_I64_2904, _t_Str_2905, s1, s2);
    (void)_t_Str_2906;
    ;
    Str_delete(_t_Str_2905, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2906); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2906, &(Bool){1});
    I64 _t_I64_2907 = 2;
    (void)_t_I64_2907;
    Bool _t_Bool_2908 = I64_eq(DEREF(depth), _t_I64_2907);
    (void)_t_Bool_2908;
    ;
    if (_t_Bool_2908) {
        I64 _t_I64_2892 = 1;
        (void)_t_I64_2892;
        Str *_t_Str_2893 = Str_lit("lei", 3ULL);
        (void)_t_Str_2893;
        I64 _t_I64_2894 = I64_add(DEREF(depth), _t_I64_2892);
        (void)_t_I64_2894;
        ;
        Str *_t_Str_2895 = Str_concat(current, _t_Str_2893);
        (void)_t_Str_2895;
        Str_delete(_t_Str_2893, &(Bool){1});
        Str *_t_Str_2896 = poem(&_t_I64_2894, _t_Str_2895, s1, s2);
        (void)_t_Str_2896;
        ;
        Str_delete(_t_Str_2895, &(Bool){1});
        { Str *_old = result; result = Str_concat(result, _t_Str_2896); Str_delete(_old, &(Bool){1}); }
        Str_delete(_t_Str_2896, &(Bool){1});
    }
    ;
    return result;
}

Str * make_poem(Str * s1, Str * s2) {
    (void)s1;
    (void)s2;
    I64 _t_I64_2909 = 0;
    (void)_t_I64_2909;
    Str *_t_Str_2910 = Str_lit("", 0ULL);
    (void)_t_Str_2910;
    Str *_t_Str_2911 = poem(&_t_I64_2909, _t_Str_2910, s1, s2);
    (void)_t_Str_2911;
    ;
    Str_delete(_t_Str_2910, &(Bool){1});
    return _t_Str_2911;
}

void test_lolalalo(void) {
    Str *_t_Str_2912 = Str_lit("lo", 2ULL);
    (void)_t_Str_2912;
    Str *_t_Str_2913 = Str_lit("la", 2ULL);
    (void)_t_Str_2913;
    Str *lo_la = make_poem(_t_Str_2912, _t_Str_2913);
    (void)lo_la;
    Str_delete(_t_Str_2912, &(Bool){1});
    Str_delete(_t_Str_2913, &(Bool){1});
    Str *_t_Str_2914 = Str_lit("la", 2ULL);
    (void)_t_Str_2914;
    Str *_t_Str_2915 = Str_lit("lo", 2ULL);
    (void)_t_Str_2915;
    Str *la_lo = make_poem(_t_Str_2914, _t_Str_2915);
    (void)la_lo;
    Str_delete(_t_Str_2914, &(Bool){1});
    Str_delete(_t_Str_2915, &(Bool){1});
    Str *_t_Str_2916 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_2916;
    Str *_t_Str_2917 = Str_lit("src/test/constfold.til:56:12", 28ULL);
    (void)_t_Str_2917;
    Bool _t_Bool_2918 = Str_contains(lo_la, _t_Str_2916);
    (void)_t_Bool_2918;
    Str_delete(_t_Str_2916, &(Bool){1});
    Bool _t_Bool_2919; { Bool *_hp = (Bool *)assert(_t_Str_2917, &_t_Bool_2918); _t_Bool_2919 = *_hp; free(_hp); }
    (void)_t_Bool_2919;
    ;
    ;
    Str_delete(_t_Str_2917, &(Bool){1});
    Str *_t_Str_2920 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_2920;
    Str *_t_Str_2921 = Str_lit("src/test/constfold.til:57:12", 28ULL);
    (void)_t_Str_2921;
    Bool _t_Bool_2922 = Str_contains(la_lo, _t_Str_2920);
    (void)_t_Bool_2922;
    Str_delete(_t_Str_2920, &(Bool){1});
    Bool _t_Bool_2923; { Bool *_hp = (Bool *)assert(_t_Str_2921, &_t_Bool_2922); _t_Bool_2923 = *_hp; free(_hp); }
    (void)_t_Bool_2923;
    ;
    ;
    Str_delete(_t_Str_2921, &(Bool){1});
    Str *_t_Str_2924 = Str_lit("lolei", 5ULL);
    (void)_t_Str_2924;
    Str *_t_Str_2925 = Str_lit("src/test/constfold.til:59:12", 28ULL);
    (void)_t_Str_2925;
    Bool _t_Bool_2926 = Str_contains(lo_la, _t_Str_2924);
    (void)_t_Bool_2926;
    Str_delete(_t_Str_2924, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    Bool _t_Bool_2927; { Bool *_hp = (Bool *)assert(_t_Str_2925, &_t_Bool_2926); _t_Bool_2927 = *_hp; free(_hp); }
    (void)_t_Bool_2927;
    ;
    ;
    Str_delete(_t_Str_2925, &(Bool){1});
    Str *_t_Str_2928 = Str_lit("lalei", 5ULL);
    (void)_t_Str_2928;
    Str *_t_Str_2929 = Str_lit("src/test/constfold.til:60:12", 28ULL);
    (void)_t_Str_2929;
    Bool _t_Bool_2930 = Str_contains(la_lo, _t_Str_2928);
    (void)_t_Bool_2930;
    Str_delete(_t_Str_2928, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    Bool _t_Bool_2931; { Bool *_hp = (Bool *)assert(_t_Str_2929, &_t_Bool_2930); _t_Bool_2931 = *_hp; free(_hp); }
    (void)_t_Bool_2931;
    ;
    ;
    Str_delete(_t_Str_2929, &(Bool){1});
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
    I64 _t_I64_833 = 0;
    (void)_t_I64_833;
    I64 _t_I64_834 = 1;
    (void)_t_I64_834;
    I64 _t_I64_835 = I64_sub(_t_I64_833, _t_I64_834);
    (void)_t_I64_835;
    CAP_LIT = I64_to_usize(_t_I64_835);
    (void)CAP_LIT;
    I64 _t_I64_836 = 0;
    (void)_t_I64_836;
    I64 _t_I64_837 = 2;
    (void)_t_I64_837;
    I64 _t_I64_838 = I64_sub(_t_I64_836, _t_I64_837);
    (void)_t_I64_838;
    CAP_VIEW = I64_to_usize(_t_I64_838);
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
