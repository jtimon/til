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
U32 * vec_size_of(Str * elem_type);
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
U32 * vec_size_of(Str * elem_type);
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

U32 * vec_size_of(Str * elem_type) {
    (void)elem_type;
    Str *_t_Str_144 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_144;
    Bool _t_Bool_145 = Str_eq(elem_type, _t_Str_144);
    (void)_t_Bool_145;
    Str_delete(_t_Str_144, &(Bool){1});
    if (_t_Bool_145) {
        I64 _t_I64_142 = 8;
        (void)_t_I64_142;
        U32 _t_U32_143 = I64_to_u32(_t_I64_142);
        (void)_t_U32_143;
        ;
        ;
        { U32 *_r = malloc(sizeof(U32)); *_r = _t_U32_143; return _r; }
    }
    ;
    U32 _t_USize_146 = dyn_size_of(elem_type);
    (void)_t_USize_146;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_USize_146; return _r; }
}

Vec * Vec_new(Str * elem_type, U32 * elem_size) {
    (void)elem_type;
    (void)elem_size;
    Bool _t_Bool_158 = Str_is_empty(elem_type);
    (void)_t_Bool_158;
    if (_t_Bool_158) {
        Str *_t_Str_147 = Str_lit("Str", 3ULL);
        (void)_t_Str_147;
        U32 _t_U32_148 = 16;
        (void)_t_U32_148;
        U32 _t_U32_149 = 1;
        (void)_t_U32_149;
        Array *_va_Array_0 = Array_new(_t_Str_147, &_t_U32_148, &_t_U32_149);
        (void)_va_Array_0;
        Str_delete(_t_Str_147, &(Bool){1});
        ;
        ;
        U32 _t_U32_150 = 0;
        (void)_t_U32_150;
        Str *_t_Str_151 = Str_lit("Vec.new: elem_type required", 27ULL);
        (void)_t_Str_151;
        Array_set(_va_Array_0, &_t_U32_150, _t_Str_151);
        ;
        Str *_t_Str_152 = Str_lit("./src/core/vec.til:38:19", 24ULL);
        (void)_t_Str_152;
        panic(_t_Str_152, _va_Array_0);
        Str_delete(_t_Str_152, &(Bool){1});
    }
    ;
    U32 sz = U32_clone(elem_size);
    (void)sz;
    U32 _t_U32_159 = 0;
    (void)_t_U32_159;
    Bool _t_Bool_160 = U32_eq(sz, _t_U32_159);
    (void)_t_Bool_160;
    ;
    if (_t_Bool_160) {
        U32 _t_U32_153; { U32 *_hp = (U32 *)vec_size_of(elem_type); _t_U32_153 = *_hp; free(_hp); }
        (void)_t_U32_153;
        sz = _t_U32_153;
        ;
    }
    ;
    Str *_t_Str_161 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_161;
    Bool _t_Bool_162 = Str_eq(elem_type, _t_Str_161);
    (void)_t_Bool_162;
    Str_delete(_t_Str_161, &(Bool){1});
    if (_t_Bool_162) {
        void * _t_v_154 = malloc(sz);
        (void)_t_v_154;
        U32 _t_U32_155 = 0;
        (void)_t_U32_155;
        I64 _t_I64_156 = 1;
        (void)_t_I64_156;
        Vec *_t_Vec_157 = malloc(sizeof(Vec));
        _t_Vec_157->data = _t_v_154;
        _t_Vec_157->count = _t_U32_155;
        _t_Vec_157->cap = _t_I64_156;
        _t_Vec_157->elem_size = sz;
        { Str *_ca = Str_clone(elem_type); _t_Vec_157->elem_type = *_ca; free(_ca); }
        _t_Vec_157->elem_clone = (void *)(void *)default_clone;
        _t_Vec_157->elem_delete = (void *)(void *)default_delete;
        (void)_t_Vec_157;
        ;
        ;
        ;
        ;
        return _t_Vec_157;
    }
    ;
    void * _t_v_163 = malloc(sz);
    (void)_t_v_163;
    U32 _t_U32_164 = 0;
    (void)_t_U32_164;
    I64 _t_I64_165 = 1;
    (void)_t_I64_165;
    void * _t_v_166 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_166;
    void * _t_v_167 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_167;
    Vec *_t_Vec_168 = malloc(sizeof(Vec));
    _t_Vec_168->data = _t_v_163;
    _t_Vec_168->count = _t_U32_164;
    _t_Vec_168->cap = _t_I64_165;
    _t_Vec_168->elem_size = sz;
    { Str *_ca = Str_clone(elem_type); _t_Vec_168->elem_type = *_ca; free(_ca); }
    _t_Vec_168->elem_clone = _t_v_166;
    _t_Vec_168->elem_delete = _t_v_167;
    (void)_t_Vec_168;
    ;
    ;
    ;
    return _t_Vec_168;
}

U32 Vec_len(Vec * self) {
    (void)self;
    return self->count;
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t_Bool_173 = U32_eq(self->count, self->cap);
    (void)_t_Bool_173;
    if (_t_Bool_173) {
        U32 _t_U32_169 = 2;
        (void)_t_U32_169;
        U32 new_cap = U32_mul(self->cap, _t_U32_169);
        (void)new_cap;
        ;
        U32 _t_U64_170 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_170;
        void * _t_v_171 = realloc(self->data, _t_U64_170);
        (void)_t_v_171;
        ;
        self->data = _t_v_171;
        U32 _t_U32_172 = U32_clone(&new_cap);
        (void)_t_U32_172;
        ;
        self->cap = _t_U32_172;
        ;
    }
    ;
    U32 _t_U64_174 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_174;
    void *_t_v_175 = ptr_add(self->data, _t_U64_174);
    (void)_t_v_175;
    memcpy(_t_v_175, val, self->elem_size);
    ;
    free(val);
    U32 _t_U32_176 = 1;
    (void)_t_U32_176;
    U32 _t_U32_177 = U32_add(self->count, _t_U32_176);
    (void)_t_U32_177;
    ;
    self->count = _t_U32_177;
    ;
}

void Vec_append(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_190 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_190;
    Bool _t_Bool_191 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_191;
    Bool _t_Bool_192 = not(_t_Bool_190);
    (void)_t_Bool_192;
    ;
    Bool _t_Bool_193 = not(_t_Bool_191);
    (void)_t_Bool_193;
    ;
    Bool _t_Bool_194 = or(_t_Bool_192, _t_Bool_193);
    (void)_t_Bool_194;
    ;
    ;
    if (_t_Bool_194) {
        Str *_t_Str_178 = Str_lit("Str", 3ULL);
        (void)_t_Str_178;
        U32 _t_U32_179 = 16;
        (void)_t_U32_179;
        U32 _t_U32_180 = 1;
        (void)_t_U32_180;
        Array *_va_Array_1 = Array_new(_t_Str_178, &_t_U32_179, &_t_U32_180);
        (void)_va_Array_1;
        Str_delete(_t_Str_178, &(Bool){1});
        ;
        ;
        U32 _t_U32_181 = 0;
        (void)_t_U32_181;
        Str *_t_Str_182 = Str_lit("Vec.append: incompatible vecs", 29ULL);
        (void)_t_Str_182;
        Array_set(_va_Array_1, &_t_U32_181, _t_Str_182);
        ;
        Str *_t_Str_183 = Str_lit("./src/core/vec.til:71:19", 24ULL);
        (void)_t_Str_183;
        panic(_t_Str_183, _va_Array_1);
        Str_delete(_t_Str_183, &(Bool){1});
    }
    ;
    U32 _t_U32_195 = 0;
    (void)_t_U32_195;
    Bool _t_Bool_196 = U32_eq(other->count, _t_U32_195);
    (void)_t_Bool_196;
    ;
    if (_t_Bool_196) {
        ;
        Vec_delete(other, &(Bool){0});
        return;
    }
    ;
    U32 needed = U32_add(self->count, other->count);
    (void)needed;
    Bool _t_Bool_197 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_197;
    if (_t_Bool_197) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_184 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_184;
            if (_wcond_Bool_184) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_185 = 2;
            (void)_t_U32_185;
            U32 _t_U32_186 = U32_mul(new_cap, _t_U32_185);
            (void)_t_U32_186;
            ;
            new_cap = _t_U32_186;
            ;
        }
        U32 _t_U64_187 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_187;
        void * _t_v_188 = realloc(self->data, _t_U64_187);
        (void)_t_v_188;
        ;
        self->data = _t_v_188;
        U32 _t_U32_189 = U32_clone(&new_cap);
        (void)_t_U32_189;
        ;
        self->cap = _t_U32_189;
        ;
    }
    ;
    U32 _t_U64_198 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_198;
    void *_t_v_199 = ptr_add(self->data, _t_U64_198);
    (void)_t_v_199;
    U32 _t_U64_200 = U32_mul(other->count, self->elem_size);
    (void)_t_U64_200;
    memcpy(_t_v_199, other->data, _t_U64_200);
    ;
    ;
    U32 _t_U32_201 = U32_clone(&needed);
    (void)_t_U32_201;
    ;
    self->count = _t_U32_201;
    ;
    U32 _t_U32_202 = 0;
    (void)_t_U32_202;
    other->count = _t_U32_202;
    ;
    Vec_delete(other, &(Bool){0});
}

void Vec_move_from(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_226 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_226;
    Bool _t_Bool_227 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_227;
    Bool _t_Bool_228 = not(_t_Bool_226);
    (void)_t_Bool_228;
    ;
    Bool _t_Bool_229 = not(_t_Bool_227);
    (void)_t_Bool_229;
    ;
    Bool _t_Bool_230 = or(_t_Bool_228, _t_Bool_229);
    (void)_t_Bool_230;
    ;
    ;
    if (_t_Bool_230) {
        Str *_t_Str_203 = Str_lit("Str", 3ULL);
        (void)_t_Str_203;
        U32 _t_U32_204 = 16;
        (void)_t_U32_204;
        U32 _t_U32_205 = 1;
        (void)_t_U32_205;
        Array *_va_Array_2 = Array_new(_t_Str_203, &_t_U32_204, &_t_U32_205);
        (void)_va_Array_2;
        Str_delete(_t_Str_203, &(Bool){1});
        ;
        ;
        U32 _t_U32_206 = 0;
        (void)_t_U32_206;
        Str *_t_Str_207 = Str_lit("Vec.move_from: incompatible vecs", 32ULL);
        (void)_t_Str_207;
        Array_set(_va_Array_2, &_t_U32_206, _t_Str_207);
        ;
        Str *_t_Str_208 = Str_lit("./src/core/vec.til:98:19", 24ULL);
        (void)_t_Str_208;
        panic(_t_Str_208, _va_Array_2);
        Str_delete(_t_Str_208, &(Bool){1});
    }
    ;
    Bool _t_Bool_231 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_231;
    Str *_t_Str_232 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_232;
    Bool _t_Bool_233 = Str_eq(&self->elem_type, _t_Str_232);
    (void)_t_Bool_233;
    Str_delete(_t_Str_232, &(Bool){1});
    Bool _t_Bool_234 = not(_t_Bool_231);
    (void)_t_Bool_234;
    ;
    Bool _t_Bool_235 = not(_t_Bool_233);
    (void)_t_Bool_235;
    ;
    Bool _t_Bool_236 = and(_t_Bool_234, _t_Bool_235);
    (void)_t_Bool_236;
    ;
    ;
    if (_t_Bool_236) {
        {
            U32 _re_U32_209 = self->count;
            (void)_re_U32_209;
            U32 _rc_U32_209 = 0;
            (void)_rc_U32_209;
            Bool _t_Bool_218 = U32_lte(&_rc_U32_209, &_re_U32_209);
            (void)_t_Bool_218;
            if (_t_Bool_218) {
                while (1) {
                    Bool _wcond_Bool_210 = U32_lt(&_rc_U32_209, &_re_U32_209);
                    (void)_wcond_Bool_210;
                    if (_wcond_Bool_210) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_209);
                    (void)i;
                    U32_inc(&_rc_U32_209);
                    U32 _t_U64_211 = U32_mul(i, self->elem_size);
                    (void)_t_U64_211;
                    ;
                    void *_t_v_212 = ptr_add(self->data, _t_U64_211);
                    (void)_t_v_212;
                    Bool _t_Bool_213 = 0;
                    (void)_t_Bool_213;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_212, &_t_Bool_213);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_214 = U32_gt(&_rc_U32_209, &_re_U32_209);
                    (void)_wcond_Bool_214;
                    if (_wcond_Bool_214) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_209);
                    (void)i;
                    U32_dec(&_rc_U32_209);
                    U32 _t_U64_215 = U32_mul(i, self->elem_size);
                    (void)_t_U64_215;
                    ;
                    void *_t_v_216 = ptr_add(self->data, _t_U64_215);
                    (void)_t_v_216;
                    Bool _t_Bool_217 = 0;
                    (void)_t_Bool_217;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_216, &_t_Bool_217);
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
    Bool _t_Bool_237 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_237;
    if (_t_Bool_237) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_219 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_219;
            if (_wcond_Bool_219) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_220 = 2;
            (void)_t_U32_220;
            U32 _t_U32_221 = U32_mul(new_cap, _t_U32_220);
            (void)_t_U32_221;
            ;
            new_cap = _t_U32_221;
            ;
        }
        U32 _t_U64_222 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_222;
        void * _t_v_223 = realloc(self->data, _t_U64_222);
        (void)_t_v_223;
        ;
        self->data = _t_v_223;
        U32 _t_U32_224 = U32_clone(&new_cap);
        (void)_t_U32_224;
        ;
        self->cap = _t_U32_224;
        ;
    }
    ;
    U32 _t_U32_238 = 0;
    (void)_t_U32_238;
    Bool _t_Bool_239 = U32_gt(&needed, &_t_U32_238);
    (void)_t_Bool_239;
    ;
    if (_t_Bool_239) {
        U32 _t_U64_225 = U32_mul(needed, self->elem_size);
        (void)_t_U64_225;
        memcpy(self->data, other->data, _t_U64_225);
        ;
    }
    ;
    U32 _t_U32_240 = U32_clone(&needed);
    (void)_t_U32_240;
    ;
    self->count = _t_U32_240;
    ;
    U32 _t_U32_241 = 0;
    (void)_t_U32_241;
    other->count = _t_U32_241;
    ;
}

void * Vec_get(Vec * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_256 = U32_gte(i, &self->count);
    (void)_t_Bool_256;
    if (_t_Bool_256) {
        Str *_t_Str_242 = Str_lit("Str", 3ULL);
        (void)_t_Str_242;
        U32 _t_U32_243 = 16;
        (void)_t_U32_243;
        U32 _t_U32_244 = 5;
        (void)_t_U32_244;
        Array *_va_Array_3 = Array_new(_t_Str_242, &_t_U32_243, &_t_U32_244);
        (void)_va_Array_3;
        Str_delete(_t_Str_242, &(Bool){1});
        ;
        ;
        U32 _t_U32_245 = 0;
        (void)_t_U32_245;
        Str *_t_Str_246 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t_Str_246;
        Array_set(_va_Array_3, &_t_U32_245, _t_Str_246);
        ;
        U32 _t_U32_247 = 1;
        (void)_t_U32_247;
        Str *_t_Str_248 = U32_to_str(i);
        (void)_t_Str_248;
        Array_set(_va_Array_3, &_t_U32_247, _t_Str_248);
        ;
        U32 _t_U32_249 = 2;
        (void)_t_U32_249;
        Str *_t_Str_250 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_250;
        Array_set(_va_Array_3, &_t_U32_249, _t_Str_250);
        ;
        U32 _t_U32_251 = 3;
        (void)_t_U32_251;
        Str *_t_Str_252 = U32_to_str(&self->count);
        (void)_t_Str_252;
        Array_set(_va_Array_3, &_t_U32_251, _t_Str_252);
        ;
        U32 _t_U32_253 = 4;
        (void)_t_U32_253;
        Str *_t_Str_254 = Str_lit(")", 1ULL);
        (void)_t_Str_254;
        Array_set(_va_Array_3, &_t_U32_253, _t_Str_254);
        ;
        Str *_t_Str_255 = Str_lit("./src/core/vec.til:125:19", 25ULL);
        (void)_t_Str_255;
        panic(_t_Str_255, _va_Array_3);
        Str_delete(_t_Str_255, &(Bool){1});
    }
    ;
    U32 _t_U64_257 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_257;
    void *_t_v_258 = ptr_add(self->data, _t_U64_257);
    (void)_t_v_258;
    ;
    return _t_v_258;
}

void * Vec_pop(Vec * self) {
    (void)self;
    U32 _t_U32_265 = 0;
    (void)_t_U32_265;
    Bool _t_Bool_266 = U32_eq(self->count, _t_U32_265);
    (void)_t_Bool_266;
    ;
    if (_t_Bool_266) {
        Str *_t_Str_259 = Str_lit("Str", 3ULL);
        (void)_t_Str_259;
        U32 _t_U32_260 = 16;
        (void)_t_U32_260;
        U32 _t_U32_261 = 1;
        (void)_t_U32_261;
        Array *_va_Array_4 = Array_new(_t_Str_259, &_t_U32_260, &_t_U32_261);
        (void)_va_Array_4;
        Str_delete(_t_Str_259, &(Bool){1});
        ;
        ;
        U32 _t_U32_262 = 0;
        (void)_t_U32_262;
        Str *_t_Str_263 = Str_lit("Vec.pop: empty vec", 18ULL);
        (void)_t_Str_263;
        Array_set(_va_Array_4, &_t_U32_262, _t_Str_263);
        ;
        Str *_t_Str_264 = Str_lit("./src/core/vec.til:134:19", 25ULL);
        (void)_t_Str_264;
        panic(_t_Str_264, _va_Array_4);
        Str_delete(_t_Str_264, &(Bool){1});
    }
    ;
    U32 _t_U32_267 = 1;
    (void)_t_U32_267;
    U32 last = U32_sub(self->count, _t_U32_267);
    (void)last;
    ;
    void * out = malloc(self->elem_size);
    (void)out;
    U32 _t_U64_268 = U32_mul(last, self->elem_size);
    (void)_t_U64_268;
    void *_t_v_269 = ptr_add(self->data, _t_U64_268);
    (void)_t_v_269;
    memcpy(out, _t_v_269, self->elem_size);
    ;
    U32 _t_U32_270 = U32_clone(&last);
    (void)_t_U32_270;
    ;
    self->count = _t_U32_270;
    ;
    return out;
}

Vec * Vec_take_prefix(Vec * self, U32 * n) {
    (void)self;
    (void)n;
    Bool _t_Bool_290 = U32_gt(n, &self->count);
    (void)_t_Bool_290;
    if (_t_Bool_290) {
        Str *_t_Str_271 = Str_lit("Str", 3ULL);
        (void)_t_Str_271;
        U32 _t_U32_272 = 16;
        (void)_t_U32_272;
        U32 _t_U32_273 = 5;
        (void)_t_U32_273;
        Array *_va_Array_5 = Array_new(_t_Str_271, &_t_U32_272, &_t_U32_273);
        (void)_va_Array_5;
        Str_delete(_t_Str_271, &(Bool){1});
        ;
        ;
        U32 _t_U32_274 = 0;
        (void)_t_U32_274;
        Str *_t_Str_275 = Str_lit("Vec.take_prefix: count ", 23ULL);
        (void)_t_Str_275;
        Array_set(_va_Array_5, &_t_U32_274, _t_Str_275);
        ;
        U32 _t_U32_276 = 1;
        (void)_t_U32_276;
        Str *_t_Str_277 = U32_to_str(n);
        (void)_t_Str_277;
        Array_set(_va_Array_5, &_t_U32_276, _t_Str_277);
        ;
        U32 _t_U32_278 = 2;
        (void)_t_U32_278;
        Str *_t_Str_279 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_279;
        Array_set(_va_Array_5, &_t_U32_278, _t_Str_279);
        ;
        U32 _t_U32_280 = 3;
        (void)_t_U32_280;
        Str *_t_Str_281 = U32_to_str(&self->count);
        (void)_t_Str_281;
        Array_set(_va_Array_5, &_t_U32_280, _t_Str_281);
        ;
        U32 _t_U32_282 = 4;
        (void)_t_U32_282;
        Str *_t_Str_283 = Str_lit(")", 1ULL);
        (void)_t_Str_283;
        Array_set(_va_Array_5, &_t_U32_282, _t_Str_283);
        ;
        Str *_t_Str_284 = Str_lit("./src/core/vec.til:147:19", 25ULL);
        (void)_t_Str_284;
        panic(_t_Str_284, _va_Array_5);
        Str_delete(_t_Str_284, &(Bool){1});
    }
    ;
    U32 prefix_cap = 1;
    (void)prefix_cap;
    U32 _t_U32_291 = 0;
    (void)_t_U32_291;
    Bool _t_Bool_292 = U32_gt(n, &_t_U32_291);
    (void)_t_Bool_292;
    ;
    if (_t_Bool_292) {
        U32 _t_U32_285 = U32_clone(n);
        (void)_t_U32_285;
        prefix_cap = _t_U32_285;
        ;
    }
    ;
    U32 _t_U64_293 = U32_mul(prefix_cap, self->elem_size);
    (void)_t_U64_293;
    void * prefix_data = malloc(_t_U64_293);
    (void)prefix_data;
    ;
    U32 _t_U32_294 = 0;
    (void)_t_U32_294;
    Bool _t_Bool_295 = U32_gt(n, &_t_U32_294);
    (void)_t_Bool_295;
    ;
    if (_t_Bool_295) {
        U32 _t_U64_286 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_286;
        memcpy(prefix_data, self->data, _t_U64_286);
        ;
    }
    ;
    U32 tail_count = U32_sub(self->count, DEREF(n));
    (void)tail_count;
    U32 _t_U32_296 = 0;
    (void)_t_U32_296;
    Bool _t_Bool_297 = U32_gt(&tail_count, &_t_U32_296);
    (void)_t_Bool_297;
    ;
    if (_t_Bool_297) {
        U32 _t_U64_287 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_287;
        void *_t_v_288 = ptr_add(self->data, _t_U64_287);
        (void)_t_v_288;
        U32 _t_U64_289 = U32_mul(tail_count, self->elem_size);
        (void)_t_U64_289;
        memmove(self->data, _t_v_288, _t_U64_289);
        ;
        ;
    }
    ;
    U32 _t_U32_298 = U32_clone(&tail_count);
    (void)_t_U32_298;
    ;
    self->count = _t_U32_298;
    ;
    Vec *_t_Vec_299 = malloc(sizeof(Vec));
    _t_Vec_299->data = prefix_data;
    _t_Vec_299->count = DEREF(n);
    _t_Vec_299->cap = prefix_cap;
    _t_Vec_299->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_299->elem_type = *_ca; free(_ca); }
    _t_Vec_299->elem_clone = (void *)self->elem_clone;
    _t_Vec_299->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_299;
    ;
    return _t_Vec_299;
}

void Vec_set(Vec * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_314 = U32_gte(i, &self->count);
    (void)_t_Bool_314;
    if (_t_Bool_314) {
        Str *_t_Str_300 = Str_lit("Str", 3ULL);
        (void)_t_Str_300;
        U32 _t_U32_301 = 16;
        (void)_t_U32_301;
        U32 _t_U32_302 = 5;
        (void)_t_U32_302;
        Array *_va_Array_6 = Array_new(_t_Str_300, &_t_U32_301, &_t_U32_302);
        (void)_va_Array_6;
        Str_delete(_t_Str_300, &(Bool){1});
        ;
        ;
        U32 _t_U32_303 = 0;
        (void)_t_U32_303;
        Str *_t_Str_304 = Str_lit("Vec.set: index ", 15ULL);
        (void)_t_Str_304;
        Array_set(_va_Array_6, &_t_U32_303, _t_Str_304);
        ;
        U32 _t_U32_305 = 1;
        (void)_t_U32_305;
        Str *_t_Str_306 = U32_to_str(i);
        (void)_t_Str_306;
        Array_set(_va_Array_6, &_t_U32_305, _t_Str_306);
        ;
        U32 _t_U32_307 = 2;
        (void)_t_U32_307;
        Str *_t_Str_308 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_308;
        Array_set(_va_Array_6, &_t_U32_307, _t_Str_308);
        ;
        U32 _t_U32_309 = 3;
        (void)_t_U32_309;
        Str *_t_Str_310 = U32_to_str(&self->count);
        (void)_t_Str_310;
        Array_set(_va_Array_6, &_t_U32_309, _t_Str_310);
        ;
        U32 _t_U32_311 = 4;
        (void)_t_U32_311;
        Str *_t_Str_312 = Str_lit(")", 1ULL);
        (void)_t_Str_312;
        Array_set(_va_Array_6, &_t_U32_311, _t_Str_312);
        ;
        Str *_t_Str_313 = Str_lit("./src/core/vec.til:171:19", 25ULL);
        (void)_t_Str_313;
        panic(_t_Str_313, _va_Array_6);
        Str_delete(_t_Str_313, &(Bool){1});
    }
    ;
    U32 _t_U64_315 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_315;
    void *_t_v_316 = ptr_add(self->data, _t_U64_315);
    (void)_t_v_316;
    memcpy(_t_v_316, val, self->elem_size);
    ;
    free(val);
}

void Vec_push_take(Vec * self, Vec * src, U32 i) {
    (void)self;
    (void)src;
    (void)i;
    Bool _t_Bool_341 = U32_gte(&i, &src->count);
    (void)_t_Bool_341;
    if (_t_Bool_341) {
        Str *_t_Str_317 = Str_lit("Str", 3ULL);
        (void)_t_Str_317;
        U32 _t_U32_318 = 16;
        (void)_t_U32_318;
        U32 _t_U32_319 = 5;
        (void)_t_U32_319;
        Array *_va_Array_7 = Array_new(_t_Str_317, &_t_U32_318, &_t_U32_319);
        (void)_va_Array_7;
        Str_delete(_t_Str_317, &(Bool){1});
        ;
        ;
        U32 _t_U32_320 = 0;
        (void)_t_U32_320;
        Str *_t_Str_321 = Str_lit("Vec.push_take: index ", 21ULL);
        (void)_t_Str_321;
        Array_set(_va_Array_7, &_t_U32_320, _t_Str_321);
        ;
        U32 _t_U32_322 = 1;
        (void)_t_U32_322;
        Str *_t_Str_323 = U32_to_str(&i);
        (void)_t_Str_323;
        Array_set(_va_Array_7, &_t_U32_322, _t_Str_323);
        ;
        U32 _t_U32_324 = 2;
        (void)_t_U32_324;
        Str *_t_Str_325 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_325;
        Array_set(_va_Array_7, &_t_U32_324, _t_Str_325);
        ;
        U32 _t_U32_326 = 3;
        (void)_t_U32_326;
        Str *_t_Str_327 = U32_to_str(&src->count);
        (void)_t_Str_327;
        Array_set(_va_Array_7, &_t_U32_326, _t_Str_327);
        ;
        U32 _t_U32_328 = 4;
        (void)_t_U32_328;
        Str *_t_Str_329 = Str_lit(")", 1ULL);
        (void)_t_Str_329;
        Array_set(_va_Array_7, &_t_U32_328, _t_Str_329);
        ;
        Str *_t_Str_330 = Str_lit("./src/core/vec.til:182:19", 25ULL);
        (void)_t_Str_330;
        panic(_t_Str_330, _va_Array_7);
        Str_delete(_t_Str_330, &(Bool){1});
    }
    ;
    Bool _t_Bool_342 = U32_eq(self->elem_size, src->elem_size);
    (void)_t_Bool_342;
    Bool _t_Bool_343 = Str_eq(&self->elem_type, &src->elem_type);
    (void)_t_Bool_343;
    Bool _t_Bool_344 = not(_t_Bool_342);
    (void)_t_Bool_344;
    ;
    Bool _t_Bool_345 = not(_t_Bool_343);
    (void)_t_Bool_345;
    ;
    Bool _t_Bool_346 = or(_t_Bool_344, _t_Bool_345);
    (void)_t_Bool_346;
    ;
    ;
    if (_t_Bool_346) {
        Str *_t_Str_331 = Str_lit("Str", 3ULL);
        (void)_t_Str_331;
        U32 _t_U32_332 = 16;
        (void)_t_U32_332;
        U32 _t_U32_333 = 1;
        (void)_t_U32_333;
        Array *_va_Array_8 = Array_new(_t_Str_331, &_t_U32_332, &_t_U32_333);
        (void)_va_Array_8;
        Str_delete(_t_Str_331, &(Bool){1});
        ;
        ;
        U32 _t_U32_334 = 0;
        (void)_t_U32_334;
        Str *_t_Str_335 = Str_lit("Vec.push_take: incompatible vecs", 32ULL);
        (void)_t_Str_335;
        Array_set(_va_Array_8, &_t_U32_334, _t_Str_335);
        ;
        Str *_t_Str_336 = Str_lit("./src/core/vec.til:185:19", 25ULL);
        (void)_t_Str_336;
        panic(_t_Str_336, _va_Array_8);
        Str_delete(_t_Str_336, &(Bool){1});
    }
    ;
    Bool _t_Bool_347 = U32_eq(self->count, self->cap);
    (void)_t_Bool_347;
    if (_t_Bool_347) {
        U32 _t_U32_337 = 2;
        (void)_t_U32_337;
        U32 new_cap = U32_mul(self->cap, _t_U32_337);
        (void)new_cap;
        ;
        U32 _t_U64_338 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_338;
        void * _t_v_339 = realloc(self->data, _t_U64_338);
        (void)_t_v_339;
        ;
        self->data = _t_v_339;
        U32 _t_U32_340 = U32_clone(&new_cap);
        (void)_t_U32_340;
        ;
        self->cap = _t_U32_340;
        ;
    }
    ;
    U32 _t_U64_348 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_348;
    U32 _t_U64_349 = U32_mul(i, src->elem_size);
    (void)_t_U64_349;
    void *_t_v_350 = ptr_add(self->data, _t_U64_348);
    (void)_t_v_350;
    void *_t_v_351 = ptr_add(src->data, _t_U64_349);
    (void)_t_v_351;
    memcpy(_t_v_350, _t_v_351, self->elem_size);
    ;
    ;
    U32 _t_U64_352 = U32_mul(i, src->elem_size);
    (void)_t_U64_352;
    void *_t_v_353 = ptr_add(src->data, _t_U64_352);
    (void)_t_v_353;
    I32 _t_I32_354 = 0;
    (void)_t_I32_354;
    memset(_t_v_353, _t_I32_354, src->elem_size);
    ;
    ;
    U32 _t_U32_355 = 1;
    (void)_t_U32_355;
    U32 _t_U32_356 = U32_add(self->count, _t_U32_355);
    (void)_t_U32_356;
    ;
    self->count = _t_U32_356;
    ;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_368 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_368;
    Str *_t_Str_369 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_369;
    Bool _t_Bool_370 = Str_eq(&self->elem_type, _t_Str_369);
    (void)_t_Bool_370;
    Str_delete(_t_Str_369, &(Bool){1});
    Bool _t_Bool_371 = not(_t_Bool_368);
    (void)_t_Bool_371;
    ;
    Bool _t_Bool_372 = not(_t_Bool_370);
    (void)_t_Bool_372;
    ;
    Bool _t_Bool_373 = and(_t_Bool_371, _t_Bool_372);
    (void)_t_Bool_373;
    ;
    ;
    if (_t_Bool_373) {
        {
            U32 _re_U32_357 = self->count;
            (void)_re_U32_357;
            U32 _rc_U32_357 = 0;
            (void)_rc_U32_357;
            Bool _t_Bool_366 = U32_lte(&_rc_U32_357, &_re_U32_357);
            (void)_t_Bool_366;
            if (_t_Bool_366) {
                while (1) {
                    Bool _wcond_Bool_358 = U32_lt(&_rc_U32_357, &_re_U32_357);
                    (void)_wcond_Bool_358;
                    if (_wcond_Bool_358) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_357);
                    (void)i;
                    U32_inc(&_rc_U32_357);
                    U32 _t_U64_359 = U32_mul(i, self->elem_size);
                    (void)_t_U64_359;
                    ;
                    void *_t_v_360 = ptr_add(self->data, _t_U64_359);
                    (void)_t_v_360;
                    Bool _t_Bool_361 = 0;
                    (void)_t_Bool_361;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_360, &_t_Bool_361);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_362 = U32_gt(&_rc_U32_357, &_re_U32_357);
                    (void)_wcond_Bool_362;
                    if (_wcond_Bool_362) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_357);
                    (void)i;
                    U32_dec(&_rc_U32_357);
                    U32 _t_U64_363 = U32_mul(i, self->elem_size);
                    (void)_t_U64_363;
                    ;
                    void *_t_v_364 = ptr_add(self->data, _t_U64_363);
                    (void)_t_v_364;
                    Bool _t_Bool_365 = 0;
                    (void)_t_Bool_365;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_364, &_t_Bool_365);
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
    Bool _t_Bool_374 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_374;
    Bool _t_Bool_375 = not(_t_Bool_374);
    (void)_t_Bool_375;
    ;
    if (_t_Bool_375) {
        Bool _t_Bool_367 = 0;
        (void)_t_Bool_367;
        Str_delete(&self->elem_type, &_t_Bool_367);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U32 _t_U64_389 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_389;
    void * new_data = malloc(_t_U64_389);
    (void)new_data;
    ;
    Bool _t_Bool_390 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_390;
    Str *_t_Str_391 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_391;
    Bool _t_Bool_392 = Str_eq(&self->elem_type, _t_Str_391);
    (void)_t_Bool_392;
    Str_delete(_t_Str_391, &(Bool){1});
    Bool _t_Bool_393 = not(_t_Bool_390);
    (void)_t_Bool_393;
    ;
    Bool _t_Bool_394 = not(_t_Bool_392);
    (void)_t_Bool_394;
    ;
    Bool _t_Bool_395 = and(_t_Bool_393, _t_Bool_394);
    (void)_t_Bool_395;
    ;
    ;
    if (_t_Bool_395) {
        {
            U32 _re_U32_376 = self->count;
            (void)_re_U32_376;
            U32 _rc_U32_376 = 0;
            (void)_rc_U32_376;
            Bool _t_Bool_387 = U32_lte(&_rc_U32_376, &_re_U32_376);
            (void)_t_Bool_387;
            if (_t_Bool_387) {
                while (1) {
                    Bool _wcond_Bool_377 = U32_lt(&_rc_U32_376, &_re_U32_376);
                    (void)_wcond_Bool_377;
                    if (_wcond_Bool_377) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_376);
                    (void)i;
                    U32_inc(&_rc_U32_376);
                    U32 _t_U64_378 = U32_mul(i, self->elem_size);
                    (void)_t_U64_378;
                    void *_t_v_379 = ptr_add(self->data, _t_U64_378);
                    (void)_t_v_379;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_379);
                    (void)cloned;
                    ;
                    U32 _t_U64_380 = U32_mul(i, self->elem_size);
                    (void)_t_U64_380;
                    ;
                    void *_t_v_381 = ptr_add(new_data, _t_U64_380);
                    (void)_t_v_381;
                    memcpy(_t_v_381, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_382 = U32_gt(&_rc_U32_376, &_re_U32_376);
                    (void)_wcond_Bool_382;
                    if (_wcond_Bool_382) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_376);
                    (void)i;
                    U32_dec(&_rc_U32_376);
                    U32 _t_U64_383 = U32_mul(i, self->elem_size);
                    (void)_t_U64_383;
                    void *_t_v_384 = ptr_add(self->data, _t_U64_383);
                    (void)_t_v_384;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_384);
                    (void)cloned;
                    ;
                    U32 _t_U64_385 = U32_mul(i, self->elem_size);
                    (void)_t_U64_385;
                    ;
                    void *_t_v_386 = ptr_add(new_data, _t_U64_385);
                    (void)_t_v_386;
                    memcpy(_t_v_386, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            }
            ;
            ;
            ;
        }
    } else {
        U32 _t_U64_388 = U32_mul(self->count, self->elem_size);
        (void)_t_U64_388;
        memcpy(new_data, self->data, _t_U64_388);
        ;
    }
    ;
    Vec *_t_Vec_396 = malloc(sizeof(Vec));
    _t_Vec_396->data = new_data;
    _t_Vec_396->count = self->count;
    _t_Vec_396->cap = self->cap;
    _t_Vec_396->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_396->elem_type = *_ca; free(_ca); }
    _t_Vec_396->elem_clone = (void *)self->elem_clone;
    _t_Vec_396->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_396;
    return _t_Vec_396;
}

U32 Vec_size(void) {
    I64 _t_I64_397 = 56;
    (void)_t_I64_397;
    return _t_I64_397;
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    (void)total;
    {
        Array *_fc_Array_398 = parts;
        (void)_fc_Array_398;
        U32 _fi_USize_398 = 0;
        (void)_fi_USize_398;
        while (1) {
            U32 _t_U32_400; { U32 *_hp = (U32 *)Array_len(_fc_Array_398); _t_U32_400 = *_hp; free(_hp); }
            (void)_t_U32_400;
            Bool _wcond_Bool_399 = U32_lt(&_fi_USize_398, &_t_U32_400);
            (void)_wcond_Bool_399;
            ;
            if (_wcond_Bool_399) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_398, &_fi_USize_398);
            (void)s;
            U32 _t_U32_401 = 1;
            (void)_t_U32_401;
            U32 _t_U32_402 = U32_add(_fi_USize_398, _t_U32_401);
            (void)_t_U32_402;
            ;
            _fi_USize_398 = _t_U32_402;
            ;
            U32 _t_U32_403 = Str_len(s);
            (void)_t_U32_403;
            U32 _t_U32_404 = U32_add(total, _t_U32_403);
            (void)_t_U32_404;
            ;
            total = _t_U32_404;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    (void)out;
    ;
    {
        Array *_fc_Array_405 = parts;
        (void)_fc_Array_405;
        U32 _fi_USize_405 = 0;
        (void)_fi_USize_405;
        while (1) {
            U32 _t_U32_407; { U32 *_hp = (U32 *)Array_len(_fc_Array_405); _t_U32_407 = *_hp; free(_hp); }
            (void)_t_U32_407;
            Bool _wcond_Bool_406 = U32_lt(&_fi_USize_405, &_t_U32_407);
            (void)_wcond_Bool_406;
            ;
            if (_wcond_Bool_406) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_405, &_fi_USize_405);
            (void)s;
            U32 _t_U32_408 = 1;
            (void)_t_U32_408;
            U32 _t_U32_409 = U32_add(_fi_USize_405, _t_U32_408);
            (void)_t_U32_409;
            ;
            _fi_USize_405 = _t_U32_409;
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
    Bool _t_Bool_416 = U32_gte(i, &self->count);
    (void)_t_Bool_416;
    if (_t_Bool_416) {
        Str *_t_Str_410 = Str_lit("Str", 3ULL);
        (void)_t_Str_410;
        U32 _t_U32_411 = 16;
        (void)_t_U32_411;
        U32 _t_U32_412 = 1;
        (void)_t_U32_412;
        Array *_va_Array_9 = Array_new(_t_Str_410, &_t_U32_411, &_t_U32_412);
        (void)_va_Array_9;
        Str_delete(_t_Str_410, &(Bool){1});
        ;
        ;
        U32 _t_U32_413 = 0;
        (void)_t_U32_413;
        Str *_t_Str_414 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t_Str_414;
        Array_set(_va_Array_9, &_t_U32_413, _t_Str_414);
        ;
        Str *_t_Str_415 = Str_lit("./src/core/str.til:39:19", 24ULL);
        (void)_t_Str_415;
        panic(_t_Str_415, _va_Array_9);
        Str_delete(_t_Str_415, &(Bool){1});
    }
    ;
    void *_t_v_417 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_417;
    return _t_v_417;
}

U8 * Str_byte_at(Str * self, U32 * i) {
    (void)self;
    (void)i;
    void *_t_v_418 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_418;
    return _t_v_418;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    (void)min_len;
    Bool _t_Bool_427 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_427;
    if (_t_Bool_427) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_419 = U32_clone(&min_len);
        (void)_re_U32_419;
        U32 _rc_U32_419 = 0;
        (void)_rc_U32_419;
        Bool _t_Bool_426 = U32_lte(&_rc_U32_419, &_re_U32_419);
        (void)_t_Bool_426;
        if (_t_Bool_426) {
            while (1) {
                Bool _wcond_Bool_420 = U32_lt(&_rc_U32_419, &_re_U32_419);
                (void)_wcond_Bool_420;
                if (_wcond_Bool_420) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_419);
                (void)i;
                U32_inc(&_rc_U32_419);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_421 = 0;
                (void)_t_I64_421;
                Bool _t_Bool_422 = I64_neq(&c, &_t_I64_421);
                (void)_t_Bool_422;
                ;
                if (_t_Bool_422) {
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
                Bool _wcond_Bool_423 = U32_gt(&_rc_U32_419, &_re_U32_419);
                (void)_wcond_Bool_423;
                if (_wcond_Bool_423) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_419);
                (void)i;
                U32_dec(&_rc_U32_419);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_424 = 0;
                (void)_t_I64_424;
                Bool _t_Bool_425 = I64_neq(&c, &_t_I64_424);
                (void)_t_Bool_425;
                ;
                if (_t_Bool_425) {
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
    I64 _t_I64_428 = U32_cmp(a->count, b->count);
    (void)_t_I64_428;
    return _t_I64_428;
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_429 = U32_add(a->count, b->count);
    (void)_t_U32_429;
    Str *out = Str_with_capacity(&_t_U32_429);
    (void)out;
    ;
    Str_push_str(out, a);
    Str_push_str(out, b);
    return out;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_430 = 1;
    (void)_t_U32_430;
    U32 _t_U64_431 = U32_add(DEREF(n), _t_U32_430);
    (void)_t_U64_431;
    ;
    void * buf = malloc(_t_U64_431);
    (void)buf;
    ;
    I32 _t_I32_432 = 0;
    (void)_t_I32_432;
    U64 _t_U64_433 = 1;
    (void)_t_U64_433;
    memset(buf, _t_I32_432, _t_U64_433);
    ;
    ;
    I64 _t_I64_434 = 0;
    (void)_t_I64_434;
    Str *_t_Str_435 = malloc(sizeof(Str));
    _t_Str_435->c_str = buf;
    _t_Str_435->count = _t_I64_434;
    _t_Str_435->cap = DEREF(n);
    (void)_t_Str_435;
    ;
    return _t_Str_435;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_448 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_448;
    if (_t_Bool_448) {
        Str *_t_Str_436 = Str_lit("Str", 3ULL);
        (void)_t_Str_436;
        U32 _t_U32_437 = 16;
        (void)_t_U32_437;
        U32 _t_U32_438 = 1;
        (void)_t_U32_438;
        Array *_va_Array_10 = Array_new(_t_Str_436, &_t_U32_437, &_t_U32_438);
        (void)_va_Array_10;
        Str_delete(_t_Str_436, &(Bool){1});
        ;
        ;
        U32 _t_U32_439 = 0;
        (void)_t_U32_439;
        Str *_t_Str_440 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t_Str_440;
        Array_set(_va_Array_10, &_t_U32_439, _t_Str_440);
        ;
        Str *_t_Str_441 = Str_lit("./src/core/str.til:82:19", 24ULL);
        (void)_t_Str_441;
        panic(_t_Str_441, _va_Array_10);
        Str_delete(_t_Str_441, &(Bool){1});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    (void)new_len;
    Bool _t_Bool_449 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_449;
    if (_t_Bool_449) {
        Str *_t_Str_442 = Str_lit("Str", 3ULL);
        (void)_t_Str_442;
        U32 _t_U32_443 = 16;
        (void)_t_U32_443;
        U32 _t_U32_444 = 1;
        (void)_t_U32_444;
        Array *_va_Array_11 = Array_new(_t_Str_442, &_t_U32_443, &_t_U32_444);
        (void)_va_Array_11;
        Str_delete(_t_Str_442, &(Bool){1});
        ;
        ;
        U32 _t_U32_445 = 0;
        (void)_t_U32_445;
        Str *_t_Str_446 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t_Str_446;
        Array_set(_va_Array_11, &_t_U32_445, _t_Str_446);
        ;
        Str *_t_Str_447 = Str_lit("./src/core/str.til:86:19", 24ULL);
        (void)_t_Str_447;
        panic(_t_Str_447, _va_Array_11);
        Str_delete(_t_Str_447, &(Bool){1});
    }
    ;
    void *_t_v_450 = ptr_add(self->c_str, self->count);
    (void)_t_v_450;
    memcpy(_t_v_450, s->c_str, s->count);
    U32 _t_U32_451 = U32_clone(&new_len);
    (void)_t_U32_451;
    self->count = _t_U32_451;
    ;
    void *_t_v_452 = ptr_add(self->c_str, new_len);
    (void)_t_v_452;
    I32 _t_I32_453 = 0;
    (void)_t_I32_453;
    U64 _t_U64_454 = 1;
    (void)_t_U64_454;
    memset(_t_v_452, _t_I32_453, _t_U64_454);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_455 = 1;
    (void)_t_U32_455;
    U32 _t_U64_456 = U32_add(val->count, _t_U32_455);
    (void)_t_U64_456;
    ;
    void * new_data = malloc(_t_U64_456);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_457 = ptr_add(new_data, val->count);
    (void)_t_v_457;
    I32 _t_I32_458 = 0;
    (void)_t_I32_458;
    U64 _t_U64_459 = 1;
    (void)_t_U64_459;
    memset(_t_v_457, _t_I32_458, _t_U64_459);
    ;
    ;
    Str *_t_Str_460 = malloc(sizeof(Str));
    _t_Str_460->c_str = new_data;
    _t_Str_460->count = val->count;
    _t_Str_460->cap = val->count;
    (void)_t_Str_460;
    return _t_Str_460;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_461 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_461;
    if (_t_Bool_461) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t_Str_462 = Str_clone(val);
    (void)_t_Str_462;
    return _t_Str_462;
}

Str * Str_substr(Str * s, U32 * start, U32 * n) {
    (void)s;
    (void)start;
    (void)n;
    U32 st = U32_clone(start);
    (void)st;
    U32 ln = U32_clone(n);
    (void)ln;
    Bool _t_Bool_464 = U32_gt(&st, &s->count);
    (void)_t_Bool_464;
    if (_t_Bool_464) {
        st = s->count;
    }
    ;
    U32 _t_U32_465 = U32_add(st, ln);
    (void)_t_U32_465;
    Bool _t_Bool_466 = U32_gt(&_t_U32_465, &s->count);
    (void)_t_Bool_466;
    ;
    if (_t_Bool_466) {
        U32 _t_U32_463 = U32_sub(s->count, st);
        (void)_t_U32_463;
        ln = _t_U32_463;
        ;
    }
    ;
    void *_t_v_467 = ptr_add(s->c_str, st);
    (void)_t_v_467;
    Str *_t_Str_468 = malloc(sizeof(Str));
    _t_Str_468->c_str = _t_v_467;
    _t_Str_468->count = ln;
    _t_Str_468->cap = CAP_VIEW;
    (void)_t_Str_468;
    ;
    ;
    return _t_Str_468;
}

Bool Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_499 = 0;
    (void)_t_U32_499;
    Bool _t_Bool_500 = U32_eq(b->count, _t_U32_499);
    (void)_t_Bool_500;
    ;
    if (_t_Bool_500) {
        Bool _t_Bool_469 = 1;
        (void)_t_Bool_469;
        ;
        return _t_Bool_469;
    }
    ;
    Bool _t_Bool_501 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_501;
    if (_t_Bool_501) {
        Bool _t_Bool_470 = 0;
        (void)_t_Bool_470;
        ;
        return _t_Bool_470;
    }
    ;
    {
        U32 _t_U32_496 = U32_sub(a->count, b->count);
        (void)_t_U32_496;
        U32 _t_U32_497 = 1;
        (void)_t_U32_497;
        U32 _re_U32_471 = U32_add(_t_U32_496, _t_U32_497);
        (void)_re_U32_471;
        ;
        ;
        U32 _rc_U32_471 = 0;
        (void)_rc_U32_471;
        Bool _t_Bool_498 = U32_lte(&_rc_U32_471, &_re_U32_471);
        (void)_t_Bool_498;
        if (_t_Bool_498) {
            while (1) {
                Bool _wcond_Bool_472 = U32_lt(&_rc_U32_471, &_re_U32_471);
                (void)_wcond_Bool_472;
                if (_wcond_Bool_472) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_471);
                (void)i;
                U32_inc(&_rc_U32_471);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_473 = b->count;
                    (void)_re_U32_473;
                    U32 _rc_U32_473 = 0;
                    (void)_rc_U32_473;
                    Bool _t_Bool_482 = U32_lte(&_rc_U32_473, &_re_U32_473);
                    (void)_t_Bool_482;
                    if (_t_Bool_482) {
                        while (1) {
                            Bool _wcond_Bool_474 = U32_lt(&_rc_U32_473, &_re_U32_473);
                            (void)_wcond_Bool_474;
                            if (_wcond_Bool_474) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_473);
                            (void)j;
                            U32_inc(&_rc_U32_473);
                            U32 _t_U32_476 = U32_add(i, j);
                            (void)_t_U32_476;
                            U8 *ac = Str_get(a, &_t_U32_476);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_477 = U8_neq(ac, bc);
                            (void)_t_Bool_477;
                            ;
                            ;
                            if (_t_Bool_477) {
                                Bool _t_Bool_475 = 0;
                                (void)_t_Bool_475;
                                found = _t_Bool_475;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_478 = U32_gt(&_rc_U32_473, &_re_U32_473);
                            (void)_wcond_Bool_478;
                            if (_wcond_Bool_478) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_473);
                            (void)j;
                            U32_dec(&_rc_U32_473);
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
                    }
                    ;
                    ;
                    ;
                }
                ;
                if (found) {
                    Bool _t_Bool_483 = 1;
                    (void)_t_Bool_483;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_483;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_484 = U32_gt(&_rc_U32_471, &_re_U32_471);
                (void)_wcond_Bool_484;
                if (_wcond_Bool_484) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_471);
                (void)i;
                U32_dec(&_rc_U32_471);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_485 = b->count;
                    (void)_re_U32_485;
                    U32 _rc_U32_485 = 0;
                    (void)_rc_U32_485;
                    Bool _t_Bool_494 = U32_lte(&_rc_U32_485, &_re_U32_485);
                    (void)_t_Bool_494;
                    if (_t_Bool_494) {
                        while (1) {
                            Bool _wcond_Bool_486 = U32_lt(&_rc_U32_485, &_re_U32_485);
                            (void)_wcond_Bool_486;
                            if (_wcond_Bool_486) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_485);
                            (void)j;
                            U32_inc(&_rc_U32_485);
                            U32 _t_U32_488 = U32_add(i, j);
                            (void)_t_U32_488;
                            U8 *ac = Str_get(a, &_t_U32_488);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_489 = U8_neq(ac, bc);
                            (void)_t_Bool_489;
                            ;
                            ;
                            if (_t_Bool_489) {
                                Bool _t_Bool_487 = 0;
                                (void)_t_Bool_487;
                                found = _t_Bool_487;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_490 = U32_gt(&_rc_U32_485, &_re_U32_485);
                            (void)_wcond_Bool_490;
                            if (_wcond_Bool_490) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_485);
                            (void)j;
                            U32_dec(&_rc_U32_485);
                            U32 _t_U32_492 = U32_add(i, j);
                            (void)_t_U32_492;
                            U8 *ac = Str_get(a, &_t_U32_492);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_493 = U8_neq(ac, bc);
                            (void)_t_Bool_493;
                            ;
                            ;
                            if (_t_Bool_493) {
                                Bool _t_Bool_491 = 0;
                                (void)_t_Bool_491;
                                found = _t_Bool_491;
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
                    Bool _t_Bool_495 = 1;
                    (void)_t_Bool_495;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_495;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_502 = 0;
    (void)_t_Bool_502;
    return _t_Bool_502;
}

Bool Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_512 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_512;
    if (_t_Bool_512) {
        Bool _t_Bool_503 = 0;
        (void)_t_Bool_503;
        ;
        return _t_Bool_503;
    }
    ;
    {
        U32 _re_U32_504 = b->count;
        (void)_re_U32_504;
        U32 _rc_U32_504 = 0;
        (void)_rc_U32_504;
        Bool _t_Bool_511 = U32_lte(&_rc_U32_504, &_re_U32_504);
        (void)_t_Bool_511;
        if (_t_Bool_511) {
            while (1) {
                Bool _wcond_Bool_505 = U32_lt(&_rc_U32_504, &_re_U32_504);
                (void)_wcond_Bool_505;
                if (_wcond_Bool_505) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_504);
                (void)i;
                U32_inc(&_rc_U32_504);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_507 = U8_neq(ac, bc);
                (void)_t_Bool_507;
                ;
                if (_t_Bool_507) {
                    Bool _t_Bool_506 = 0;
                    (void)_t_Bool_506;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_506;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_508 = U32_gt(&_rc_U32_504, &_re_U32_504);
                (void)_wcond_Bool_508;
                if (_wcond_Bool_508) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_504);
                (void)i;
                U32_dec(&_rc_U32_504);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_510 = U8_neq(ac, bc);
                (void)_t_Bool_510;
                ;
                if (_t_Bool_510) {
                    Bool _t_Bool_509 = 0;
                    (void)_t_Bool_509;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_509;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_513 = 1;
    (void)_t_Bool_513;
    return _t_Bool_513;
}

Bool Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_525 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_525;
    if (_t_Bool_525) {
        Bool _t_Bool_514 = 0;
        (void)_t_Bool_514;
        ;
        return _t_Bool_514;
    }
    ;
    U32 offset = U32_sub(a->count, b->count);
    (void)offset;
    {
        U32 _re_U32_515 = b->count;
        (void)_re_U32_515;
        U32 _rc_U32_515 = 0;
        (void)_rc_U32_515;
        Bool _t_Bool_524 = U32_lte(&_rc_U32_515, &_re_U32_515);
        (void)_t_Bool_524;
        if (_t_Bool_524) {
            while (1) {
                Bool _wcond_Bool_516 = U32_lt(&_rc_U32_515, &_re_U32_515);
                (void)_wcond_Bool_516;
                if (_wcond_Bool_516) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_515);
                (void)i;
                U32_inc(&_rc_U32_515);
                U32 _t_U32_518 = U32_add(offset, i);
                (void)_t_U32_518;
                U8 *ac = Str_get(a, &_t_U32_518);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_519 = U8_neq(ac, bc);
                (void)_t_Bool_519;
                ;
                ;
                if (_t_Bool_519) {
                    Bool _t_Bool_517 = 0;
                    (void)_t_Bool_517;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_517;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_520 = U32_gt(&_rc_U32_515, &_re_U32_515);
                (void)_wcond_Bool_520;
                if (_wcond_Bool_520) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_515);
                (void)i;
                U32_dec(&_rc_U32_515);
                U32 _t_U32_522 = U32_add(offset, i);
                (void)_t_U32_522;
                U8 *ac = Str_get(a, &_t_U32_522);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_523 = U8_neq(ac, bc);
                (void)_t_Bool_523;
                ;
                ;
                if (_t_Bool_523) {
                    Bool _t_Bool_521 = 0;
                    (void)_t_Bool_521;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_521;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    Bool _t_Bool_526 = 1;
    (void)_t_Bool_526;
    return _t_Bool_526;
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_527 = 0;
    (void)_t_U32_527;
    Bool _t_Bool_528 = U32_eq(self->count, _t_U32_527);
    (void)_t_Bool_528;
    ;
    return _t_Bool_528;
}

I64 Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_563 = 0;
    (void)_t_U32_563;
    Bool _t_Bool_564 = U32_eq(needle->count, _t_U32_563);
    (void)_t_Bool_564;
    ;
    if (_t_Bool_564) {
        I64 _t_I64_529 = 0;
        (void)_t_I64_529;
        I64 _t_I64_530 = 1;
        (void)_t_I64_530;
        I64 _t_I64_531 = I64_sub(_t_I64_529, _t_I64_530);
        (void)_t_I64_531;
        ;
        ;
        ;
        return _t_I64_531;
    }
    ;
    Bool _t_Bool_565 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_565;
    if (_t_Bool_565) {
        I64 _t_I64_532 = 0;
        (void)_t_I64_532;
        I64 _t_I64_533 = 1;
        (void)_t_I64_533;
        I64 _t_I64_534 = I64_sub(_t_I64_532, _t_I64_533);
        (void)_t_I64_534;
        ;
        ;
        ;
        return _t_I64_534;
    }
    ;
    {
        U32 _t_U32_560 = U32_sub(self->count, needle->count);
        (void)_t_U32_560;
        U32 _t_U32_561 = 1;
        (void)_t_U32_561;
        U32 _re_U32_535 = U32_add(_t_U32_560, _t_U32_561);
        (void)_re_U32_535;
        ;
        ;
        U32 _rc_U32_535 = 0;
        (void)_rc_U32_535;
        Bool _t_Bool_562 = U32_lte(&_rc_U32_535, &_re_U32_535);
        (void)_t_Bool_562;
        if (_t_Bool_562) {
            while (1) {
                Bool _wcond_Bool_536 = U32_lt(&_rc_U32_535, &_re_U32_535);
                (void)_wcond_Bool_536;
                if (_wcond_Bool_536) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_535);
                (void)i;
                U32_inc(&_rc_U32_535);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_537 = needle->count;
                    (void)_re_U32_537;
                    U32 _rc_U32_537 = 0;
                    (void)_rc_U32_537;
                    Bool _t_Bool_546 = U32_lte(&_rc_U32_537, &_re_U32_537);
                    (void)_t_Bool_546;
                    if (_t_Bool_546) {
                        while (1) {
                            Bool _wcond_Bool_538 = U32_lt(&_rc_U32_537, &_re_U32_537);
                            (void)_wcond_Bool_538;
                            if (_wcond_Bool_538) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_537);
                            (void)j;
                            U32_inc(&_rc_U32_537);
                            U32 _t_U32_540 = U32_add(i, j);
                            (void)_t_U32_540;
                            U8 *ac = Str_get(self, &_t_U32_540);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_541 = U8_neq(ac, bc);
                            (void)_t_Bool_541;
                            ;
                            ;
                            if (_t_Bool_541) {
                                Bool _t_Bool_539 = 0;
                                (void)_t_Bool_539;
                                found = _t_Bool_539;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_542 = U32_gt(&_rc_U32_537, &_re_U32_537);
                            (void)_wcond_Bool_542;
                            if (_wcond_Bool_542) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_537);
                            (void)j;
                            U32_dec(&_rc_U32_537);
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
                    }
                    ;
                    ;
                    ;
                }
                if (found) {
                    I64 _t_I64_547 = U32_to_i64(i);
                    (void)_t_I64_547;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_547;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_548 = U32_gt(&_rc_U32_535, &_re_U32_535);
                (void)_wcond_Bool_548;
                if (_wcond_Bool_548) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_535);
                (void)i;
                U32_dec(&_rc_U32_535);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_549 = needle->count;
                    (void)_re_U32_549;
                    U32 _rc_U32_549 = 0;
                    (void)_rc_U32_549;
                    Bool _t_Bool_558 = U32_lte(&_rc_U32_549, &_re_U32_549);
                    (void)_t_Bool_558;
                    if (_t_Bool_558) {
                        while (1) {
                            Bool _wcond_Bool_550 = U32_lt(&_rc_U32_549, &_re_U32_549);
                            (void)_wcond_Bool_550;
                            if (_wcond_Bool_550) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_549);
                            (void)j;
                            U32_inc(&_rc_U32_549);
                            U32 _t_U32_552 = U32_add(i, j);
                            (void)_t_U32_552;
                            U8 *ac = Str_get(self, &_t_U32_552);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_553 = U8_neq(ac, bc);
                            (void)_t_Bool_553;
                            ;
                            ;
                            if (_t_Bool_553) {
                                Bool _t_Bool_551 = 0;
                                (void)_t_Bool_551;
                                found = _t_Bool_551;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_554 = U32_gt(&_rc_U32_549, &_re_U32_549);
                            (void)_wcond_Bool_554;
                            if (_wcond_Bool_554) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_549);
                            (void)j;
                            U32_dec(&_rc_U32_549);
                            U32 _t_U32_556 = U32_add(i, j);
                            (void)_t_U32_556;
                            U8 *ac = Str_get(self, &_t_U32_556);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_557 = U8_neq(ac, bc);
                            (void)_t_Bool_557;
                            ;
                            ;
                            if (_t_Bool_557) {
                                Bool _t_Bool_555 = 0;
                                (void)_t_Bool_555;
                                found = _t_Bool_555;
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
                    I64 _t_I64_559 = U32_to_i64(i);
                    (void)_t_I64_559;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_559;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    I64 _t_I64_566 = 0;
    (void)_t_I64_566;
    I64 _t_I64_567 = 1;
    (void)_t_I64_567;
    I64 _t_I64_568 = I64_sub(_t_I64_566, _t_I64_567);
    (void)_t_I64_568;
    ;
    ;
    return _t_I64_568;
}

I64 Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_603 = 0;
    (void)_t_U32_603;
    Bool _t_Bool_604 = U32_eq(needle->count, _t_U32_603);
    (void)_t_Bool_604;
    ;
    if (_t_Bool_604) {
        I64 _t_I64_569 = 0;
        (void)_t_I64_569;
        I64 _t_I64_570 = 1;
        (void)_t_I64_570;
        I64 _t_I64_571 = I64_sub(_t_I64_569, _t_I64_570);
        (void)_t_I64_571;
        ;
        ;
        ;
        return _t_I64_571;
    }
    ;
    Bool _t_Bool_605 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_605;
    if (_t_Bool_605) {
        I64 _t_I64_572 = 0;
        (void)_t_I64_572;
        I64 _t_I64_573 = 1;
        (void)_t_I64_573;
        I64 _t_I64_574 = I64_sub(_t_I64_572, _t_I64_573);
        (void)_t_I64_574;
        ;
        ;
        ;
        return _t_I64_574;
    }
    ;
    I64 _t_I64_606 = 0;
    (void)_t_I64_606;
    I64 _t_I64_607 = 1;
    (void)_t_I64_607;
    I64 last = I64_sub(_t_I64_606, _t_I64_607);
    (void)last;
    ;
    ;
    {
        U32 _t_U32_600 = U32_sub(self->count, needle->count);
        (void)_t_U32_600;
        U32 _t_U32_601 = 1;
        (void)_t_U32_601;
        U32 _re_U32_575 = U32_add(_t_U32_600, _t_U32_601);
        (void)_re_U32_575;
        ;
        ;
        U32 _rc_U32_575 = 0;
        (void)_rc_U32_575;
        Bool _t_Bool_602 = U32_lte(&_rc_U32_575, &_re_U32_575);
        (void)_t_Bool_602;
        if (_t_Bool_602) {
            while (1) {
                Bool _wcond_Bool_576 = U32_lt(&_rc_U32_575, &_re_U32_575);
                (void)_wcond_Bool_576;
                if (_wcond_Bool_576) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_575);
                (void)i;
                U32_inc(&_rc_U32_575);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_577 = needle->count;
                    (void)_re_U32_577;
                    U32 _rc_U32_577 = 0;
                    (void)_rc_U32_577;
                    Bool _t_Bool_586 = U32_lte(&_rc_U32_577, &_re_U32_577);
                    (void)_t_Bool_586;
                    if (_t_Bool_586) {
                        while (1) {
                            Bool _wcond_Bool_578 = U32_lt(&_rc_U32_577, &_re_U32_577);
                            (void)_wcond_Bool_578;
                            if (_wcond_Bool_578) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_577);
                            (void)j;
                            U32_inc(&_rc_U32_577);
                            U32 _t_U32_580 = U32_add(i, j);
                            (void)_t_U32_580;
                            U8 *ac = Str_get(self, &_t_U32_580);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_581 = U8_neq(ac, bc);
                            (void)_t_Bool_581;
                            ;
                            ;
                            if (_t_Bool_581) {
                                Bool _t_Bool_579 = 0;
                                (void)_t_Bool_579;
                                found = _t_Bool_579;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_582 = U32_gt(&_rc_U32_577, &_re_U32_577);
                            (void)_wcond_Bool_582;
                            if (_wcond_Bool_582) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_577);
                            (void)j;
                            U32_dec(&_rc_U32_577);
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
                    }
                    ;
                    ;
                    ;
                }
                if (found) {
                    I64 _t_I64_587 = U32_to_i64(i);
                    (void)_t_I64_587;
                    last = _t_I64_587;
                    ;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_588 = U32_gt(&_rc_U32_575, &_re_U32_575);
                (void)_wcond_Bool_588;
                if (_wcond_Bool_588) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_575);
                (void)i;
                U32_dec(&_rc_U32_575);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_589 = needle->count;
                    (void)_re_U32_589;
                    U32 _rc_U32_589 = 0;
                    (void)_rc_U32_589;
                    Bool _t_Bool_598 = U32_lte(&_rc_U32_589, &_re_U32_589);
                    (void)_t_Bool_598;
                    if (_t_Bool_598) {
                        while (1) {
                            Bool _wcond_Bool_590 = U32_lt(&_rc_U32_589, &_re_U32_589);
                            (void)_wcond_Bool_590;
                            if (_wcond_Bool_590) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_589);
                            (void)j;
                            U32_inc(&_rc_U32_589);
                            U32 _t_U32_592 = U32_add(i, j);
                            (void)_t_U32_592;
                            U8 *ac = Str_get(self, &_t_U32_592);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_593 = U8_neq(ac, bc);
                            (void)_t_Bool_593;
                            ;
                            ;
                            if (_t_Bool_593) {
                                Bool _t_Bool_591 = 0;
                                (void)_t_Bool_591;
                                found = _t_Bool_591;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_594 = U32_gt(&_rc_U32_589, &_re_U32_589);
                            (void)_wcond_Bool_594;
                            if (_wcond_Bool_594) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_589);
                            (void)j;
                            U32_dec(&_rc_U32_589);
                            U32 _t_U32_596 = U32_add(i, j);
                            (void)_t_U32_596;
                            U8 *ac = Str_get(self, &_t_U32_596);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_597 = U8_neq(ac, bc);
                            (void)_t_Bool_597;
                            ;
                            ;
                            if (_t_Bool_597) {
                                Bool _t_Bool_595 = 0;
                                (void)_t_Bool_595;
                                found = _t_Bool_595;
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
                    I64 _t_I64_599 = U32_to_i64(i);
                    (void)_t_I64_599;
                    last = _t_I64_599;
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
    U32 _t_U32_633 = 0;
    (void)_t_U32_633;
    Bool _t_Bool_634 = U32_eq(from->count, _t_U32_633);
    (void)_t_Bool_634;
    ;
    if (_t_Bool_634) {
        Str *_t_Str_608 = Str_clone(self);
        (void)_t_Str_608;
        ;
        return _t_Str_608;
    }
    ;
    U32 matches = 0;
    (void)matches;
    U32 start = 0;
    (void)start;
    while (1) {
        U32 _t_U32_610 = U32_sub(self->count, from->count);
        (void)_t_U32_610;
        Bool _wcond_Bool_609 = U32_lte(&start, &_t_U32_610);
        (void)_wcond_Bool_609;
        ;
        if (_wcond_Bool_609) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_611 = U32_sub(self->count, start);
        (void)_t_U32_611;
        Str *rest = Str_substr(self, &start, &_t_U32_611);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_612 = 0;
        (void)_t_I64_612;
        I64 _t_I64_613 = 1;
        (void)_t_I64_613;
        I64 _t_I64_614 = I64_sub(_t_I64_612, _t_I64_613);
        (void)_t_I64_614;
        ;
        ;
        Bool _t_Bool_615 = I64_eq(pos, _t_I64_614);
        (void)_t_Bool_615;
        ;
        if (_t_Bool_615) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        U32 _t_U32_616 = U32_add(start, pos_u);
        (void)_t_U32_616;
        ;
        U32 _t_U32_617 = U32_add(_t_U32_616, from->count);
        (void)_t_U32_617;
        ;
        start = _t_U32_617;
        ;
        U32 _t_U32_618 = 1;
        (void)_t_U32_618;
        U32 _t_U32_619 = U32_add(matches, _t_U32_618);
        (void)_t_U32_619;
        ;
        matches = _t_U32_619;
        ;
    }
    U32 _t_U32_635 = 0;
    (void)_t_U32_635;
    Bool _t_Bool_636 = U32_eq(matches, _t_U32_635);
    (void)_t_Bool_636;
    ;
    if (_t_Bool_636) {
        Str *_t_Str_620 = Str_clone(self);
        (void)_t_Str_620;
        ;
        ;
        ;
        return _t_Str_620;
    }
    ;
    U32 removed = U32_mul(matches, from->count);
    (void)removed;
    U32 added = U32_mul(matches, to->count);
    (void)added;
    ;
    U32 _t_U32_637 = U32_sub(self->count, removed);
    (void)_t_U32_637;
    ;
    U32 _t_U32_638 = U32_add(_t_U32_637, added);
    (void)_t_U32_638;
    ;
    ;
    Str *out = Str_with_capacity(&_t_U32_638);
    (void)out;
    ;
    U32 _t_U32_639 = 0;
    (void)_t_U32_639;
    start = _t_U32_639;
    ;
    while (1) {
        U32 _t_U32_622 = U32_sub(self->count, from->count);
        (void)_t_U32_622;
        Bool _wcond_Bool_621 = U32_lte(&start, &_t_U32_622);
        (void)_wcond_Bool_621;
        ;
        if (_wcond_Bool_621) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_623 = U32_sub(self->count, start);
        (void)_t_U32_623;
        Str *rest = Str_substr(self, &start, &_t_U32_623);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_624 = 0;
        (void)_t_I64_624;
        I64 _t_I64_625 = 1;
        (void)_t_I64_625;
        I64 _t_I64_626 = I64_sub(_t_I64_624, _t_I64_625);
        (void)_t_I64_626;
        ;
        ;
        Bool _t_Bool_627 = I64_eq(pos, _t_I64_626);
        (void)_t_Bool_627;
        ;
        if (_t_Bool_627) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        Str *_t_Str_628 = Str_substr(self, &start, &pos_u);
        (void)_t_Str_628;
        Str_push_str(out, _t_Str_628);
        Str_delete(_t_Str_628, &(Bool){1});
        Str_push_str(out, to);
        U32 _t_U32_629 = U32_add(start, pos_u);
        (void)_t_U32_629;
        ;
        U32 _t_U32_630 = U32_add(_t_U32_629, from->count);
        (void)_t_U32_630;
        ;
        start = _t_U32_630;
        ;
    }
    Bool _t_Bool_640 = U32_lt(&start, &self->count);
    (void)_t_Bool_640;
    if (_t_Bool_640) {
        U32 _t_U32_631 = U32_sub(self->count, start);
        (void)_t_U32_631;
        Str *_t_Str_632 = Str_substr(self, &start, &_t_U32_631);
        (void)_t_Str_632;
        ;
        Str_push_str(out, _t_Str_632);
        Str_delete(_t_Str_632, &(Bool){1});
    }
    ;
    ;
    return out;
}

Str * Str_get_char(Str * self, U32 * i) {
    (void)self;
    (void)i;
    U32 _t_U32_641 = 1;
    (void)_t_U32_641;
    Str *_t_Str_642 = Str_substr(self, i, &_t_U32_641);
    (void)_t_Str_642;
    ;
    return _t_Str_642;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t_Bool_645 = Str_starts_with(self, prefix);
    (void)_t_Bool_645;
    if (_t_Bool_645) {
        U32 _t_U32_643 = U32_sub(self->count, prefix->count);
        (void)_t_U32_643;
        Str *_t_Str_644 = Str_substr(self, &prefix->count, &_t_U32_643);
        (void)_t_Str_644;
        ;
        ;
        return _t_Str_644;
    }
    ;
    Str *_t_Str_646 = Str_clone(self);
    (void)_t_Str_646;
    return _t_Str_646;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t_Bool_650 = Str_ends_with(self, suffix);
    (void)_t_Bool_650;
    if (_t_Bool_650) {
        U32 _t_U32_647 = 0;
        (void)_t_U32_647;
        U32 _t_U32_648 = U32_sub(self->count, suffix->count);
        (void)_t_U32_648;
        Str *_t_Str_649 = Str_substr(self, &_t_U32_647, &_t_U32_648);
        (void)_t_Str_649;
        ;
        ;
        ;
        return _t_Str_649;
    }
    ;
    Str *_t_Str_651 = Str_clone(self);
    (void)_t_Str_651;
    return _t_Str_651;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t_U64_652 = 2;
    (void)_t_U64_652;
    void * buf = malloc(_t_U64_652);
    (void)buf;
    ;
    U64 _t_U64_653 = 1;
    (void)_t_U64_653;
    memcpy(buf, byte, _t_U64_653);
    ;
    U64 _t_U64_654 = 1;
    (void)_t_U64_654;
    void *_t_v_655 = ptr_add(buf, _t_U64_654);
    (void)_t_v_655;
    I32 _t_I32_656 = 0;
    (void)_t_I32_656;
    U64 _t_U64_657 = 1;
    (void)_t_U64_657;
    memset(_t_v_655, _t_I32_656, _t_U64_657);
    ;
    ;
    ;
    I64 _t_I64_658 = 1;
    (void)_t_I64_658;
    I64 _t_I64_659 = 1;
    (void)_t_I64_659;
    Str *_t_Str_660 = malloc(sizeof(Str));
    _t_Str_660->c_str = buf;
    _t_Str_660->count = _t_I64_658;
    _t_Str_660->cap = _t_I64_659;
    (void)_t_Str_660;
    ;
    ;
    return _t_Str_660;
}

I64 Str_to_i64(Str * self) {
    (void)self;
    U32 _t_U32_721 = 0;
    (void)_t_U32_721;
    Bool _t_Bool_722 = U32_eq(self->count, _t_U32_721);
    (void)_t_Bool_722;
    ;
    if (_t_Bool_722) {
        Str *_t_Str_661 = Str_lit("Str", 3ULL);
        (void)_t_Str_661;
        U32 _t_U32_662 = 16;
        (void)_t_U32_662;
        U32 _t_U32_663 = 1;
        (void)_t_U32_663;
        Array *_va_Array_12 = Array_new(_t_Str_661, &_t_U32_662, &_t_U32_663);
        (void)_va_Array_12;
        Str_delete(_t_Str_661, &(Bool){1});
        ;
        ;
        U32 _t_U32_664 = 0;
        (void)_t_U32_664;
        Str *_t_Str_665 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t_Str_665;
        Array_set(_va_Array_12, &_t_U32_664, _t_Str_665);
        ;
        Str *_t_Str_666 = Str_lit("./src/core/str.til:266:37", 25ULL);
        (void)_t_Str_666;
        panic(_t_Str_666, _va_Array_12);
        Str_delete(_t_Str_666, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_723 = 0;
    (void)_t_U32_723;
    U8 *first = Str_get(self, &_t_U32_723);
    (void)first;
    U8 _t_U8_724 = 45;
    (void)_t_U8_724;
    Bool _t_Bool_725 = U8_eq(DEREF(first), _t_U8_724);
    (void)_t_Bool_725;
    ;
    ;
    if (_t_Bool_725) {
        Bool _t_Bool_667 = 1;
        (void)_t_Bool_667;
        neg = _t_Bool_667;
        ;
        U32 _t_U32_668 = 1;
        (void)_t_U32_668;
        start = _t_U32_668;
        ;
    }
    ;
    Bool _t_Bool_726 = U32_eq(start, self->count);
    (void)_t_Bool_726;
    if (_t_Bool_726) {
        Str *_t_Str_669 = Str_lit("Str", 3ULL);
        (void)_t_Str_669;
        U32 _t_U32_670 = 16;
        (void)_t_U32_670;
        U32 _t_U32_671 = 1;
        (void)_t_U32_671;
        Array *_va_Array_13 = Array_new(_t_Str_669, &_t_U32_670, &_t_U32_671);
        (void)_va_Array_13;
        Str_delete(_t_Str_669, &(Bool){1});
        ;
        ;
        U32 _t_U32_672 = 0;
        (void)_t_U32_672;
        Str *_t_Str_673 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t_Str_673;
        Array_set(_va_Array_13, &_t_U32_672, _t_Str_673);
        ;
        Str *_t_Str_674 = Str_lit("./src/core/str.til:275:41", 25ULL);
        (void)_t_Str_674;
        panic(_t_Str_674, _va_Array_13);
        Str_delete(_t_Str_674, &(Bool){1});
    }
    ;
    {
        U32 _re_U32_675 = self->count;
        (void)_re_U32_675;
        U32 _rc_U32_675 = U32_clone(&start);
        (void)_rc_U32_675;
        Bool _t_Bool_718 = U32_lte(&_rc_U32_675, &_re_U32_675);
        (void)_t_Bool_718;
        if (_t_Bool_718) {
            while (1) {
                Bool _wcond_Bool_676 = U32_lt(&_rc_U32_675, &_re_U32_675);
                (void)_wcond_Bool_676;
                if (_wcond_Bool_676) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_675);
                (void)i;
                U32_inc(&_rc_U32_675);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_687 = U8_to_i64(DEREF(ch));
                (void)_t_I64_687;
                ;
                I64 _t_I64_688 = 48;
                (void)_t_I64_688;
                I64 d = I64_sub(_t_I64_687, _t_I64_688);
                (void)d;
                ;
                ;
                I64 _t_I64_689 = 0;
                (void)_t_I64_689;
                I64 _t_I64_690 = 9;
                (void)_t_I64_690;
                Bool _t_Bool_691 = I64_lt(&d, &_t_I64_689);
                (void)_t_Bool_691;
                ;
                Bool _t_Bool_692 = I64_gt(&d, &_t_I64_690);
                (void)_t_Bool_692;
                ;
                Bool _t_Bool_693 = or(_t_Bool_691, _t_Bool_692);
                (void)_t_Bool_693;
                ;
                ;
                if (_t_Bool_693) {
                    Str *_t_Str_677 = Str_lit("Str", 3ULL);
                    (void)_t_Str_677;
                    U32 _t_U32_678 = 16;
                    (void)_t_U32_678;
                    U32 _t_U32_679 = 3;
                    (void)_t_U32_679;
                    Array *_va_Array_14 = Array_new(_t_Str_677, &_t_U32_678, &_t_U32_679);
                    (void)_va_Array_14;
                    Str_delete(_t_Str_677, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_680 = 0;
                    (void)_t_U32_680;
                    Str *_t_Str_681 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_681;
                    Array_set(_va_Array_14, &_t_U32_680, _t_Str_681);
                    ;
                    U32 _t_U32_682 = 1;
                    (void)_t_U32_682;
                    Str *_t_Str_683 = Str_clone(self);
                    (void)_t_Str_683;
                    Array_set(_va_Array_14, &_t_U32_682, _t_Str_683);
                    ;
                    U32 _t_U32_684 = 2;
                    (void)_t_U32_684;
                    Str *_t_Str_685 = Str_lit("'", 1ULL);
                    (void)_t_Str_685;
                    Array_set(_va_Array_14, &_t_U32_684, _t_Str_685);
                    ;
                    Str *_t_Str_686 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_686;
                    panic(_t_Str_686, _va_Array_14);
                    Str_delete(_t_Str_686, &(Bool){1});
                }
                ;
                I64 _t_I64_694 = 10;
                (void)_t_I64_694;
                I64 _t_I64_695 = I64_mul(result, _t_I64_694);
                (void)_t_I64_695;
                ;
                I64 _t_I64_696 = I64_add(_t_I64_695, d);
                (void)_t_I64_696;
                ;
                ;
                result = _t_I64_696;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_697 = U32_gt(&_rc_U32_675, &_re_U32_675);
                (void)_wcond_Bool_697;
                if (_wcond_Bool_697) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_675);
                (void)i;
                U32_dec(&_rc_U32_675);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_708 = U8_to_i64(DEREF(ch));
                (void)_t_I64_708;
                ;
                I64 _t_I64_709 = 48;
                (void)_t_I64_709;
                I64 d = I64_sub(_t_I64_708, _t_I64_709);
                (void)d;
                ;
                ;
                I64 _t_I64_710 = 0;
                (void)_t_I64_710;
                I64 _t_I64_711 = 9;
                (void)_t_I64_711;
                Bool _t_Bool_712 = I64_lt(&d, &_t_I64_710);
                (void)_t_Bool_712;
                ;
                Bool _t_Bool_713 = I64_gt(&d, &_t_I64_711);
                (void)_t_Bool_713;
                ;
                Bool _t_Bool_714 = or(_t_Bool_712, _t_Bool_713);
                (void)_t_Bool_714;
                ;
                ;
                if (_t_Bool_714) {
                    Str *_t_Str_698 = Str_lit("Str", 3ULL);
                    (void)_t_Str_698;
                    U32 _t_U32_699 = 16;
                    (void)_t_U32_699;
                    U32 _t_U32_700 = 3;
                    (void)_t_U32_700;
                    Array *_va_Array_15 = Array_new(_t_Str_698, &_t_U32_699, &_t_U32_700);
                    (void)_va_Array_15;
                    Str_delete(_t_Str_698, &(Bool){1});
                    ;
                    ;
                    U32 _t_U32_701 = 0;
                    (void)_t_U32_701;
                    Str *_t_Str_702 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_702;
                    Array_set(_va_Array_15, &_t_U32_701, _t_Str_702);
                    ;
                    U32 _t_U32_703 = 1;
                    (void)_t_U32_703;
                    Str *_t_Str_704 = Str_clone(self);
                    (void)_t_Str_704;
                    Array_set(_va_Array_15, &_t_U32_703, _t_Str_704);
                    ;
                    U32 _t_U32_705 = 2;
                    (void)_t_U32_705;
                    Str *_t_Str_706 = Str_lit("'", 1ULL);
                    (void)_t_Str_706;
                    Array_set(_va_Array_15, &_t_U32_705, _t_Str_706);
                    ;
                    Str *_t_Str_707 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_707;
                    panic(_t_Str_707, _va_Array_15);
                    Str_delete(_t_Str_707, &(Bool){1});
                }
                ;
                I64 _t_I64_715 = 10;
                (void)_t_I64_715;
                I64 _t_I64_716 = I64_mul(result, _t_I64_715);
                (void)_t_I64_716;
                ;
                I64 _t_I64_717 = I64_add(_t_I64_716, d);
                (void)_t_I64_717;
                ;
                ;
                result = _t_I64_717;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    if (neg) {
        I64 _t_I64_719 = 0;
        (void)_t_I64_719;
        I64 _t_I64_720 = I64_sub(_t_I64_719, result);
        (void)_t_I64_720;
        ;
        ;
        ;
        return _t_I64_720;
    }
    ;
    return result;
}

U8 Str_to_u8(Str * self) {
    (void)self;
    I64 _t_I64_727 = Str_to_i64(self);
    (void)_t_I64_727;
    U8 _t_U8_728 = I64_to_u8(_t_I64_727);
    (void)_t_U8_728;
    ;
    return _t_U8_728;
}

I32 Str_to_i32(Str * self) {
    (void)self;
    I64 _t_I64_729 = Str_to_i64(self);
    (void)_t_I64_729;
    I32 _t_I32_730 = I64_to_i32(_t_I64_729);
    (void)_t_I32_730;
    ;
    return _t_I32_730;
}

F32 Str_to_f32(Str * self) {
    (void)self;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_756 = Str_len(self);
    (void)_t_U32_756;
    U32 _t_U32_757 = 0;
    (void)_t_U32_757;
    U32 _t_U32_758 = 0;
    (void)_t_U32_758;
    U8 *_t_U8_759 = Str_get(self, &_t_U32_758);
    (void)_t_U8_759;
    U8 _t_U8_760 = 45;
    (void)_t_U8_760;
    Bool _t_Bool_761 = U32_gt(&_t_U32_756, &_t_U32_757);
    (void)_t_Bool_761;
    ;
    ;
    Bool _t_Bool_762 = U8_eq(DEREF(_t_U8_759), _t_U8_760);
    (void)_t_Bool_762;
    ;
    ;
    Bool _t_Bool_763 = and(_t_Bool_761, _t_Bool_762);
    (void)_t_Bool_763;
    ;
    ;
    if (_t_Bool_763) {
        Bool _t_Bool_731 = 1;
        (void)_t_Bool_731;
        neg = _t_Bool_731;
        ;
        U32 _t_U32_732 = 1;
        (void)_t_U32_732;
        start = _t_U32_732;
        ;
    }
    ;
    U32 _t_U32_764 = Str_len(self);
    (void)_t_U32_764;
    U32 _t_U32_765 = U32_sub(_t_U32_764, start);
    (void)_t_U32_765;
    ;
    Str *rest = Str_substr(self, &start, &_t_U32_765);
    (void)rest;
    ;
    ;
    Str *_t_Str_766 = Str_lit(".", 1ULL);
    (void)_t_Str_766;
    I64 dot = Str_find(rest, _t_Str_766);
    (void)dot;
    Str_delete(_t_Str_766, &(Bool){1});
    I64 _t_I64_767 = 0;
    (void)_t_I64_767;
    I64 _t_I64_768 = 1;
    (void)_t_I64_768;
    I64 _t_I64_769 = I64_sub(_t_I64_767, _t_I64_768);
    (void)_t_I64_769;
    ;
    ;
    Bool _t_Bool_770 = I64_eq(dot, _t_I64_769);
    (void)_t_Bool_770;
    ;
    if (_t_Bool_770) {
        I64 _t_I64_736 = Str_to_i64(rest);
        (void)_t_I64_736;
        F32 out = I64_to_f32(_t_I64_736);
        (void)out;
        ;
        if (neg) {
            I64 _t_I64_733 = 0;
            (void)_t_I64_733;
            F32 _t_F32_734 = I64_to_f32(_t_I64_733);
            (void)_t_F32_734;
            ;
            F32 _t_F32_735 = F32_sub(_t_F32_734, out);
            (void)_t_F32_735;
            ;
            ;
            ;
            ;
            ;
            Str_delete(rest, &(Bool){1});
            return _t_F32_735;
        }
        ;
        ;
        ;
        Str_delete(rest, &(Bool){1});
        return out;
    }
    ;
    U32 _t_U32_771 = 0;
    (void)_t_U32_771;
    U32 _t_U32_772 = I64_to_usize(dot);
    (void)_t_U32_772;
    Str *int_part = Str_substr(rest, &_t_U32_771, &_t_U32_772);
    (void)int_part;
    ;
    ;
    U32 _t_U32_773 = I64_to_usize(dot);
    (void)_t_U32_773;
    U32 _t_U32_774 = 1;
    (void)_t_U32_774;
    U32 _t_U32_775 = I64_to_usize(dot);
    (void)_t_U32_775;
    ;
    U32 _t_U32_776 = 1;
    (void)_t_U32_776;
    U32 _t_U32_777 = Str_len(rest);
    (void)_t_U32_777;
    U32 _t_U32_778 = U32_add(_t_U32_775, _t_U32_776);
    (void)_t_U32_778;
    ;
    ;
    U32 _t_U32_779 = U32_add(_t_U32_773, _t_U32_774);
    (void)_t_U32_779;
    ;
    ;
    U32 _t_U32_780 = U32_sub(_t_U32_777, _t_U32_778);
    (void)_t_U32_780;
    ;
    ;
    Str *frac_part = Str_substr(rest, &_t_U32_779, &_t_U32_780);
    (void)frac_part;
    ;
    ;
    Str_delete(rest, &(Bool){1});
    I64 _t_I64_781 = 0;
    (void)_t_I64_781;
    F32 out = I64_to_f32(_t_I64_781);
    (void)out;
    ;
    U32 _t_U32_782 = Str_len(int_part);
    (void)_t_U32_782;
    U32 _t_U32_783 = 0;
    (void)_t_U32_783;
    Bool _t_Bool_784 = U32_gt(&_t_U32_782, &_t_U32_783);
    (void)_t_Bool_784;
    ;
    ;
    if (_t_Bool_784) {
        I64 _t_I64_737 = Str_to_i64(int_part);
        (void)_t_I64_737;
        F32 _t_F32_738 = I64_to_f32(_t_I64_737);
        (void)_t_F32_738;
        ;
        out = _t_F32_738;
        ;
    }
    ;
    Str_delete(int_part, &(Bool){1});
    U32 _t_U32_785 = Str_len(frac_part);
    (void)_t_U32_785;
    U32 _t_U32_786 = 0;
    (void)_t_U32_786;
    Bool _t_Bool_787 = U32_gt(&_t_U32_785, &_t_U32_786);
    (void)_t_Bool_787;
    ;
    ;
    if (_t_Bool_787) {
        I64 _t_I64_749 = Str_to_i64(frac_part);
        (void)_t_I64_749;
        F32 frac = I64_to_f32(_t_I64_749);
        (void)frac;
        ;
        I64 _t_I64_750 = 1;
        (void)_t_I64_750;
        F32 scale = I64_to_f32(_t_I64_750);
        (void)scale;
        ;
        {
            U32 _re_U32_739 = Str_len(frac_part);
            (void)_re_U32_739;
            U32 _rc_U32_739 = 0;
            (void)_rc_U32_739;
            Bool _t_Bool_748 = U32_lte(&_rc_U32_739, &_re_U32_739);
            (void)_t_Bool_748;
            if (_t_Bool_748) {
                while (1) {
                    Bool _wcond_Bool_740 = U32_lt(&_rc_U32_739, &_re_U32_739);
                    (void)_wcond_Bool_740;
                    if (_wcond_Bool_740) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_739);
                    (void)_;
                    ;
                    U32_inc(&_rc_U32_739);
                    I64 _t_I64_741 = 10;
                    (void)_t_I64_741;
                    F32 _t_F32_742 = I64_to_f32(_t_I64_741);
                    (void)_t_F32_742;
                    ;
                    F32 _t_F32_743 = F32_mul(scale, _t_F32_742);
                    (void)_t_F32_743;
                    ;
                    scale = _t_F32_743;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_744 = U32_gt(&_rc_U32_739, &_re_U32_739);
                    (void)_wcond_Bool_744;
                    if (_wcond_Bool_744) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_739);
                    (void)_;
                    ;
                    U32_dec(&_rc_U32_739);
                    I64 _t_I64_745 = 10;
                    (void)_t_I64_745;
                    F32 _t_F32_746 = I64_to_f32(_t_I64_745);
                    (void)_t_F32_746;
                    ;
                    F32 _t_F32_747 = F32_mul(scale, _t_F32_746);
                    (void)_t_F32_747;
                    ;
                    scale = _t_F32_747;
                    ;
                }
            }
            ;
            ;
            ;
        }
        F32 _t_F32_751 = F32_div(frac, scale);
        (void)_t_F32_751;
        ;
        ;
        F32 _t_F32_752 = F32_add(out, _t_F32_751);
        (void)_t_F32_752;
        ;
        out = _t_F32_752;
        ;
    }
    ;
    Str_delete(frac_part, &(Bool){1});
    if (neg) {
        I64 _t_I64_753 = 0;
        (void)_t_I64_753;
        F32 _t_F32_754 = I64_to_f32(_t_I64_753);
        (void)_t_F32_754;
        ;
        F32 _t_F32_755 = F32_sub(_t_F32_754, out);
        (void)_t_F32_755;
        ;
        ;
        ;
        return _t_F32_755;
    }
    ;
    return out;
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t_Str_804 = Str_lit("Str", 3ULL);
    (void)_t_Str_804;
    U32 _t_U32_805 = 0;
    (void)_t_U32_805;
    Vec *parts = Vec_new(_t_Str_804, &_t_U32_805);
    (void)parts;
    Str_delete(_t_Str_804, &(Bool){1});
    ;
    U32 _t_U32_806 = Str_len(delim);
    (void)_t_U32_806;
    U32 _t_U32_807 = 0;
    (void)_t_U32_807;
    Bool _t_Bool_808 = U32_eq(_t_U32_806, _t_U32_807);
    (void)_t_Bool_808;
    ;
    ;
    if (_t_Bool_808) {
        Str *_t_Str_788 = Str_clone(self);
        (void)_t_Str_788;
        Vec_push(parts, _t_Str_788);
        ;
        return parts;
    }
    ;
    U32 start = 0;
    (void)start;
    U32 pos = 0;
    (void)pos;
    while (1) {
        U32 _t_U32_798 = Str_len(self);
        (void)_t_U32_798;
        U32 _t_U32_799 = Str_len(delim);
        (void)_t_U32_799;
        U32 _t_U32_800 = U32_sub(_t_U32_798, _t_U32_799);
        (void)_t_U32_800;
        ;
        ;
        Bool _wcond_Bool_789 = U32_lte(&pos, &_t_U32_800);
        (void)_wcond_Bool_789;
        ;
        if (_wcond_Bool_789) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_801 = Str_len(delim);
        (void)_t_U32_801;
        Str *_t_Str_802 = Str_substr(self, &pos, &_t_U32_801);
        (void)_t_Str_802;
        ;
        Bool _t_Bool_803 = Str_eq(_t_Str_802, delim);
        (void)_t_Bool_803;
        Str_delete(_t_Str_802, &(Bool){1});
        if (_t_Bool_803) {
            U32 _t_U32_790 = U32_sub(pos, start);
            (void)_t_U32_790;
            Str *_t_Str_791 = Str_substr(self, &start, &_t_U32_790);
            (void)_t_Str_791;
            ;
            Str *_t_Str_792 = Str_clone(_t_Str_791);
            (void)_t_Str_792;
            Str_delete(_t_Str_791, &(Bool){1});
            Vec_push(parts, _t_Str_792);
            U32 _t_U32_793 = Str_len(delim);
            (void)_t_U32_793;
            U32 _t_U32_794 = U32_add(pos, _t_U32_793);
            (void)_t_U32_794;
            ;
            start = _t_U32_794;
            ;
            U32 _t_U32_795 = U32_clone(&start);
            (void)_t_U32_795;
            pos = _t_U32_795;
            ;
        } else {
            U32 _t_U32_796 = 1;
            (void)_t_U32_796;
            U32 _t_U32_797 = U32_add(pos, _t_U32_796);
            (void)_t_U32_797;
            ;
            pos = _t_U32_797;
            ;
        }
        ;
    }
    ;
    U32 _t_U32_809 = Str_len(self);
    (void)_t_U32_809;
    U32 _t_U32_810 = U32_sub(_t_U32_809, start);
    (void)_t_U32_810;
    ;
    Str *_t_Str_811 = Str_substr(self, &start, &_t_U32_810);
    (void)_t_Str_811;
    ;
    ;
    Str *_t_Str_812 = Str_clone(_t_Str_811);
    (void)_t_Str_812;
    Str_delete(_t_Str_811, &(Bool){1});
    Vec_push(parts, _t_Str_812);
    return parts;
}

U32 Str_size(void) {
    I64 _t_I64_813 = 16;
    (void)_t_I64_813;
    return _t_I64_813;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_814 = Str_cmp(a, b);
    (void)_t_I64_814;
    I64 _t_I64_815 = 0;
    (void)_t_I64_815;
    Bool _t_Bool_816 = I64_eq(_t_I64_814, _t_I64_815);
    (void)_t_Bool_816;
    ;
    ;
    return _t_Bool_816;
}

Bool Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_817 = 0;
    (void)_t_I64_817;
    I64 _t_I64_818 = 1;
    (void)_t_I64_818;
    I64 _t_I64_819 = Str_cmp(a, b);
    (void)_t_I64_819;
    I64 _t_I64_820 = I64_sub(_t_I64_817, _t_I64_818);
    (void)_t_I64_820;
    ;
    ;
    Bool _t_Bool_821 = I64_eq(_t_I64_819, _t_I64_820);
    (void)_t_Bool_821;
    ;
    ;
    return _t_Bool_821;
}

Bool Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_822 = Str_cmp(a, b);
    (void)_t_I64_822;
    I64 _t_I64_823 = 1;
    (void)_t_I64_823;
    Bool _t_Bool_824 = I64_eq(_t_I64_822, _t_I64_823);
    (void)_t_Bool_824;
    ;
    ;
    return _t_Bool_824;
}

Bool Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_825 = Str_eq(a, b);
    (void)_t_Bool_825;
    Bool _t_Bool_826 = not(_t_Bool_825);
    (void)_t_Bool_826;
    ;
    return _t_Bool_826;
}

Bool Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_827 = Str_gt(a, b);
    (void)_t_Bool_827;
    Bool _t_Bool_828 = not(_t_Bool_827);
    (void)_t_Bool_828;
    ;
    return _t_Bool_828;
}

Bool Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_829 = Str_lt(a, b);
    (void)_t_Bool_829;
    Bool _t_Bool_830 = not(_t_Bool_829);
    (void)_t_Bool_830;
    ;
    return _t_Bool_830;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_862 = 8;
    (void)_t_I64_862;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_862; return _r; }
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
    I64 _t_I64_865 = I16_to_i64(DEREF(val));
    (void)_t_I64_865;
    Str *_t_Str_866 = I64_to_str(&_t_I64_865);
    (void)_t_Str_866;
    ;
    return _t_Str_866;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t_I16_867 = 1;
    (void)_t_I16_867;
    I16 _t_I16_868 = I16_add(DEREF(self), _t_I16_867);
    (void)_t_I16_868;
    ;
    *self = _t_I16_868;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t_I16_869 = 1;
    (void)_t_I16_869;
    I16 _t_I16_870 = I16_sub(DEREF(self), _t_I16_869);
    (void)_t_I16_870;
    ;
    *self = _t_I16_870;
    ;
}

I16 * I16_unity(I16 * _self) {
    (void)_self;
    I64 _t_I64_871 = 1;
    (void)_t_I64_871;
    I16 _t_I16_872 = I64_to_i16(_t_I64_871);
    (void)_t_I16_872;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_872; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t_I64_873 = 0;
    (void)_t_I64_873;
    I64 _t_I64_874 = I16_to_i64(DEREF(a));
    (void)_t_I64_874;
    I64 _t_I64_875 = I64_sub(_t_I64_873, _t_I64_874);
    (void)_t_I64_875;
    ;
    ;
    I16 _t_I16_876 = I64_to_i16(_t_I64_875);
    (void)_t_I16_876;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_876; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t_I64_881 = I16_to_i64(DEREF(a));
    (void)_t_I64_881;
    I64 _t_I64_882 = 0;
    (void)_t_I64_882;
    Bool _t_Bool_883 = I64_lt(&_t_I64_881, &_t_I64_882);
    (void)_t_Bool_883;
    ;
    ;
    if (_t_Bool_883) {
        I64 _t_I64_877 = 0;
        (void)_t_I64_877;
        I64 _t_I64_878 = I16_to_i64(DEREF(a));
        (void)_t_I64_878;
        I64 _t_I64_879 = I64_sub(_t_I64_877, _t_I64_878);
        (void)_t_I64_879;
        ;
        ;
        I16 _t_I16_880 = I64_to_i16(_t_I64_879);
        (void)_t_I16_880;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_880; return _r; }
    }
    ;
    I16 _t_I16_884 = I16_clone(a);
    (void)_t_I16_884;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_884; return _r; }
}

U64 I16_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I16 *au = a;
    (void)au;
    I16 *bu = b;
    (void)bu;
    Bool _t_Bool_888 = I16_lte(au, bu);
    (void)_t_Bool_888;
    if (_t_Bool_888) {
        I16 _t_I16_885 = I16_sub(DEREF(bu), DEREF(au));
        (void)_t_I16_885;
        I64 _t_I64_886 = I16_to_i64(_t_I16_885);
        (void)_t_I64_886;
        ;
        U64 _t_U64_887 = I64_to_u64(_t_I64_886);
        (void)_t_U64_887;
        ;
        ;
        return _t_U64_887;
    }
    ;
    I16 _t_I16_889 = I16_sub(DEREF(au), DEREF(bu));
    (void)_t_I16_889;
    I64 _t_I64_890 = I16_to_i64(_t_I16_889);
    (void)_t_I64_890;
    ;
    U64 _t_U64_891 = I64_to_u64(_t_I64_890);
    (void)_t_U64_891;
    ;
    return _t_U64_891;
}

void I16_delete(I16 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I16_size(void) {
    I64 _t_I64_892 = 2;
    (void)_t_I64_892;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_892; return _r; }
}

Bool I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_893 = 0;
    (void)_t_I64_893;
    I64 _t_I64_894 = 1;
    (void)_t_I64_894;
    I64 _t_I64_895 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_895;
    I64 _t_I64_896 = I64_sub(_t_I64_893, _t_I64_894);
    (void)_t_I64_896;
    ;
    ;
    Bool _t_Bool_897 = I64_eq(_t_I64_895, _t_I64_896);
    (void)_t_Bool_897;
    ;
    ;
    return _t_Bool_897;
}

Bool I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_898 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_898;
    I64 _t_I64_899 = 1;
    (void)_t_I64_899;
    Bool _t_Bool_900 = I64_eq(_t_I64_898, _t_I64_899);
    (void)_t_Bool_900;
    ;
    ;
    return _t_Bool_900;
}

Bool I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_901 = I16_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_901;
    Bool _t_Bool_902 = not(_t_Bool_901);
    (void)_t_Bool_902;
    ;
    return _t_Bool_902;
}

Bool I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_903 = I16_gt(a, b);
    (void)_t_Bool_903;
    Bool _t_Bool_904 = not(_t_Bool_903);
    (void)_t_Bool_904;
    ;
    return _t_Bool_904;
}

Bool I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_905 = I16_lt(a, b);
    (void)_t_Bool_905;
    Bool _t_Bool_906 = not(_t_Bool_905);
    (void)_t_Bool_906;
    ;
    return _t_Bool_906;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_943 = 0;
    (void)_t_I64_943;
    Bool _t_Bool_944 = I64_eq(DEREF(val), _t_I64_943);
    (void)_t_Bool_944;
    ;
    if (_t_Bool_944) {
        U64 _t_U64_907 = 2;
        (void)_t_U64_907;
        void * buf = malloc(_t_U64_907);
        (void)buf;
        ;
        I64 _t_I64_908 = 48;
        (void)_t_I64_908;
        U64 _t_U64_909 = 1;
        (void)_t_U64_909;
        memcpy(buf, &_t_I64_908, _t_U64_909);
        ;
        ;
        U64 _t_U64_910 = 1;
        (void)_t_U64_910;
        void *_t_v_911 = ptr_add(buf, _t_U64_910);
        (void)_t_v_911;
        I32 _t_I32_912 = 0;
        (void)_t_I32_912;
        U64 _t_U64_913 = 1;
        (void)_t_U64_913;
        memset(_t_v_911, _t_I32_912, _t_U64_913);
        ;
        ;
        ;
        I64 _t_I64_914 = 1;
        (void)_t_I64_914;
        I64 _t_I64_915 = 1;
        (void)_t_I64_915;
        Str *_t_Str_916 = malloc(sizeof(Str));
        _t_Str_916->c_str = buf;
        _t_Str_916->count = _t_I64_914;
        _t_Str_916->cap = _t_I64_915;
        (void)_t_Str_916;
        ;
        ;
        ;
        return _t_Str_916;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t_I64_945 = 0;
    (void)_t_I64_945;
    Bool _t_Bool_946 = I64_lt(val, &_t_I64_945);
    (void)_t_Bool_946;
    ;
    if (_t_Bool_946) {
        Bool _t_Bool_917 = 1;
        (void)_t_Bool_917;
        is_neg = _t_Bool_917;
        ;
        I64 _t_I64_918 = 0;
        (void)_t_I64_918;
        I64 _t_I64_919 = I64_sub(_t_I64_918, DEREF(val));
        (void)_t_I64_919;
        ;
        v = _t_I64_919;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&v);
    (void)tmp;
    while (1) {
        I64 _t_I64_921 = 0;
        (void)_t_I64_921;
        Bool _wcond_Bool_920 = I64_gt(&tmp, &_t_I64_921);
        (void)_wcond_Bool_920;
        ;
        if (_wcond_Bool_920) {
        } else {
            ;
            break;
        }
        ;
        U64 _t_U64_922 = 1;
        (void)_t_U64_922;
        U64 _t_U64_923 = U64_add(ndigits, _t_U64_922);
        (void)_t_U64_923;
        ;
        ndigits = _t_U64_923;
        ;
        I64 _t_I64_924 = 10;
        (void)_t_I64_924;
        I64 _t_I64_925 = I64_div(tmp, _t_I64_924);
        (void)_t_I64_925;
        ;
        tmp = _t_I64_925;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    (void)total;
    ;
    if (is_neg) {
        U64 _t_U64_926 = 1;
        (void)_t_U64_926;
        U64 _t_U64_927 = U64_add(total, _t_U64_926);
        (void)_t_U64_927;
        ;
        total = _t_U64_927;
        ;
    }
    U64 _t_U64_947 = 1;
    (void)_t_U64_947;
    U64 _t_U64_948 = U64_add(total, _t_U64_947);
    (void)_t_U64_948;
    ;
    void * buf = malloc(_t_U64_948);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t_I64_928 = 45;
        (void)_t_I64_928;
        U64 _t_U64_929 = 1;
        (void)_t_U64_929;
        memcpy(buf, &_t_I64_928, _t_U64_929);
        ;
        ;
    }
    ;
    U64 _t_U64_949 = 1;
    (void)_t_U64_949;
    U64 i = U64_sub(total, _t_U64_949);
    (void)i;
    ;
    while (1) {
        I64 _t_I64_931 = 0;
        (void)_t_I64_931;
        Bool _wcond_Bool_930 = I64_gt(&v, &_t_I64_931);
        (void)_wcond_Bool_930;
        ;
        if (_wcond_Bool_930) {
        } else {
            ;
            break;
        }
        ;
        I64 _t_I64_932 = 10;
        (void)_t_I64_932;
        I64 _t_I64_933 = I64_mod(v, _t_I64_932);
        (void)_t_I64_933;
        ;
        I64 _t_I64_934 = 48;
        (void)_t_I64_934;
        I64 _t_I64_935 = I64_add(_t_I64_933, _t_I64_934);
        (void)_t_I64_935;
        ;
        ;
        void *_t_v_936 = ptr_add(buf, i);
        (void)_t_v_936;
        U8 _t_U8_937 = I64_to_u8(_t_I64_935);
        (void)_t_U8_937;
        ;
        U64 _t_U64_938 = 1;
        (void)_t_U64_938;
        memcpy(_t_v_936, &_t_U8_937, _t_U64_938);
        ;
        ;
        I64 _t_I64_939 = 10;
        (void)_t_I64_939;
        I64 _t_I64_940 = I64_div(v, _t_I64_939);
        (void)_t_I64_940;
        ;
        v = _t_I64_940;
        ;
        U64 _t_U64_941 = 1;
        (void)_t_U64_941;
        U64 _t_U64_942 = U64_sub(i, _t_U64_941);
        (void)_t_U64_942;
        ;
        i = _t_U64_942;
        ;
    }
    ;
    ;
    void *_t_v_950 = ptr_add(buf, total);
    (void)_t_v_950;
    I32 _t_I32_951 = 0;
    (void)_t_I32_951;
    U64 _t_U64_952 = 1;
    (void)_t_U64_952;
    memset(_t_v_950, _t_I32_951, _t_U64_952);
    ;
    ;
    Str *_t_Str_953 = malloc(sizeof(Str));
    _t_Str_953->c_str = buf;
    _t_Str_953->count = total;
    _t_Str_953->cap = total;
    (void)_t_Str_953;
    ;
    return _t_Str_953;
}

U32 I64_to_usize(I64 val) {
    (void)val;
    U32 _t_U32_954 = I64_to_u32(val);
    (void)_t_U32_954;
    return _t_U32_954;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t_I64_955 = 1;
    (void)_t_I64_955;
    I64 _t_I64_956 = I64_add(DEREF(self), _t_I64_955);
    (void)_t_I64_956;
    ;
    *self = _t_I64_956;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t_I64_957 = 1;
    (void)_t_I64_957;
    I64 _t_I64_958 = I64_sub(DEREF(self), _t_I64_957);
    (void)_t_I64_958;
    ;
    *self = _t_I64_958;
    ;
}

I64 * I64_unity(I64 * _self) {
    (void)_self;
    I64 _t_I64_959 = 1;
    (void)_t_I64_959;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_959; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t_I64_960 = 0;
    (void)_t_I64_960;
    I64 _t_I64_961 = I64_sub(_t_I64_960, DEREF(a));
    (void)_t_I64_961;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_961; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t_I64_964 = 0;
    (void)_t_I64_964;
    Bool _t_Bool_965 = I64_lt(a, &_t_I64_964);
    (void)_t_Bool_965;
    ;
    if (_t_Bool_965) {
        I64 _t_I64_962 = 0;
        (void)_t_I64_962;
        I64 _t_I64_963 = I64_sub(_t_I64_962, DEREF(a));
        (void)_t_I64_963;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_963; return _r; }
    }
    ;
    I64 _t_I64_966 = I64_clone(a);
    (void)_t_I64_966;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_966; return _r; }
}

U64 I64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I64 *au = a;
    (void)au;
    I64 *bu = b;
    (void)bu;
    Bool _t_Bool_969 = I64_lte(au, bu);
    (void)_t_Bool_969;
    if (_t_Bool_969) {
        I64 _t_I64_967 = I64_sub(DEREF(bu), DEREF(au));
        (void)_t_I64_967;
        U64 _t_U64_968 = I64_to_u64(_t_I64_967);
        (void)_t_U64_968;
        ;
        ;
        return _t_U64_968;
    }
    ;
    I64 _t_I64_970 = I64_sub(DEREF(au), DEREF(bu));
    (void)_t_I64_970;
    U64 _t_U64_971 = I64_to_u64(_t_I64_970);
    (void)_t_U64_971;
    ;
    return _t_U64_971;
}

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_972 = 8;
    (void)_t_I64_972;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_972; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_973 = 0;
    (void)_t_I64_973;
    I64 _t_I64_974 = 1;
    (void)_t_I64_974;
    I64 _t_I64_975 = I64_cmp(DEREF(a), DEREF(b));
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

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_978 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_978;
    I64 _t_I64_979 = 1;
    (void)_t_I64_979;
    Bool _t_Bool_980 = I64_eq(_t_I64_978, _t_I64_979);
    (void)_t_Bool_980;
    ;
    ;
    return _t_Bool_980;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_981 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_981;
    Bool _t_Bool_982 = not(_t_Bool_981);
    (void)_t_Bool_982;
    ;
    return _t_Bool_982;
}

Bool I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_983 = I64_gt(a, b);
    (void)_t_Bool_983;
    Bool _t_Bool_984 = not(_t_Bool_983);
    (void)_t_Bool_984;
    ;
    return _t_Bool_984;
}

Bool I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_985 = I64_lt(a, b);
    (void)_t_Bool_985;
    Bool _t_Bool_986 = not(_t_Bool_985);
    (void)_t_Bool_986;
    ;
    return _t_Bool_986;
}

Str * Bool_to_str(Bool * b) {
    (void)b;
    if (DEREF(b)) {
        Str *_t_Str_987 = Str_lit("true", 4ULL);
        (void)_t_Str_987;
        return _t_Str_987;
    } else {
        Str *_t_Str_988 = Str_lit("false", 5ULL);
        (void)_t_Str_988;
        return _t_Str_988;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_993 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_993;
    if (_t_Bool_993) {
        I64 _t_I64_989 = 0;
        (void)_t_I64_989;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_989; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_990 = 0;
        (void)_t_I64_990;
        I64 _t_I64_991 = 1;
        (void)_t_I64_991;
        I64 _t_I64_992 = I64_sub(_t_I64_990, _t_I64_991);
        (void)_t_I64_992;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_992; return _r; }
    }
    I64 _t_I64_994 = 1;
    (void)_t_I64_994;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_994; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_995 = 1;
    (void)_t_I64_995;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_995; return _r; }
}

Bool Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_996 = 0;
    (void)_t_I64_996;
    I64 _t_I64_997 = 1;
    (void)_t_I64_997;
    I64 _t_I64_998; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_998 = *_hp; free(_hp); }
    (void)_t_I64_998;
    I64 _t_I64_999 = I64_sub(_t_I64_996, _t_I64_997);
    (void)_t_I64_999;
    ;
    ;
    Bool _t_Bool_1000 = I64_eq(_t_I64_998, _t_I64_999);
    (void)_t_Bool_1000;
    ;
    ;
    return _t_Bool_1000;
}

Bool Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_1001; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_1001 = *_hp; free(_hp); }
    (void)_t_I64_1001;
    I64 _t_I64_1002 = 1;
    (void)_t_I64_1002;
    Bool _t_Bool_1003 = I64_eq(_t_I64_1001, _t_I64_1002);
    (void)_t_Bool_1003;
    ;
    ;
    return _t_Bool_1003;
}

Bool Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1004 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_1004;
    Bool _t_Bool_1005 = not(_t_Bool_1004);
    (void)_t_Bool_1005;
    ;
    return _t_Bool_1005;
}

Bool Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1006 = Bool_gt(a, b);
    (void)_t_Bool_1006;
    Bool _t_Bool_1007 = not(_t_Bool_1006);
    (void)_t_Bool_1007;
    ;
    return _t_Bool_1007;
}

Bool Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1008 = Bool_lt(a, b);
    (void)_t_Bool_1008;
    Bool _t_Bool_1009 = not(_t_Bool_1008);
    (void)_t_Bool_1009;
    ;
    return _t_Bool_1009;
}

Array * Array_new(Str * elem_type, U32 * elem_size, U32 * cap) {
    (void)elem_type;
    (void)elem_size;
    (void)cap;
    Bool _t_Bool_1016 = Str_is_empty(elem_type);
    (void)_t_Bool_1016;
    if (_t_Bool_1016) {
        Str *_t_Str_1010 = Str_lit("Str", 3ULL);
        (void)_t_Str_1010;
        U32 _t_U32_1011 = 16;
        (void)_t_U32_1011;
        U32 _t_U32_1012 = 1;
        (void)_t_U32_1012;
        Array *_va_Array_16 = Array_new(_t_Str_1010, &_t_U32_1011, &_t_U32_1012);
        (void)_va_Array_16;
        Str_delete(_t_Str_1010, &(Bool){1});
        ;
        ;
        U32 _t_U32_1013 = 0;
        (void)_t_U32_1013;
        Str *_t_Str_1014 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_1014;
        Array_set(_va_Array_16, &_t_U32_1013, _t_Str_1014);
        ;
        Str *_t_Str_1015 = Str_lit("./src/core/array.til:22:41", 26ULL);
        (void)_t_Str_1015;
        panic(_t_Str_1015, _va_Array_16);
        Str_delete(_t_Str_1015, &(Bool){1});
    }
    ;
    void * _t_v_1017 = calloc(DEREF(cap), DEREF(elem_size));
    (void)_t_v_1017;
    void * _t_v_1018 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1018;
    void * _t_v_1019 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1019;
    Array *_t_Array_1020 = malloc(sizeof(Array));
    _t_Array_1020->data = _t_v_1017;
    _t_Array_1020->cap = DEREF(cap);
    _t_Array_1020->elem_size = DEREF(elem_size);
    { Str *_ca = Str_clone(elem_type); _t_Array_1020->elem_type = *_ca; free(_ca); }
    _t_Array_1020->elem_clone = _t_v_1018;
    _t_Array_1020->elem_delete = _t_v_1019;
    (void)_t_Array_1020;
    return _t_Array_1020;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_1035 = U32_gte(i, &self->cap);
    (void)_t_Bool_1035;
    if (_t_Bool_1035) {
        Str *_t_Str_1021 = Str_lit("Str", 3ULL);
        (void)_t_Str_1021;
        U32 _t_U32_1022 = 16;
        (void)_t_U32_1022;
        U32 _t_U32_1023 = 5;
        (void)_t_U32_1023;
        Array *_va_Array_17 = Array_new(_t_Str_1021, &_t_U32_1022, &_t_U32_1023);
        (void)_va_Array_17;
        Str_delete(_t_Str_1021, &(Bool){1});
        ;
        ;
        U32 _t_U32_1024 = 0;
        (void)_t_U32_1024;
        Str *_t_Str_1025 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_1025;
        Array_set(_va_Array_17, &_t_U32_1024, _t_Str_1025);
        ;
        U32 _t_U32_1026 = 1;
        (void)_t_U32_1026;
        Str *_t_Str_1027 = U32_to_str(i);
        (void)_t_Str_1027;
        Array_set(_va_Array_17, &_t_U32_1026, _t_Str_1027);
        ;
        U32 _t_U32_1028 = 2;
        (void)_t_U32_1028;
        Str *_t_Str_1029 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1029;
        Array_set(_va_Array_17, &_t_U32_1028, _t_Str_1029);
        ;
        U32 _t_U32_1030 = 3;
        (void)_t_U32_1030;
        Str *_t_Str_1031 = U32_to_str(&self->cap);
        (void)_t_Str_1031;
        Array_set(_va_Array_17, &_t_U32_1030, _t_Str_1031);
        ;
        U32 _t_U32_1032 = 4;
        (void)_t_U32_1032;
        Str *_t_Str_1033 = Str_lit(")", 1ULL);
        (void)_t_Str_1033;
        Array_set(_va_Array_17, &_t_U32_1032, _t_Str_1033);
        ;
        Str *_t_Str_1034 = Str_lit("./src/core/array.til:34:19", 26ULL);
        (void)_t_Str_1034;
        panic(_t_Str_1034, _va_Array_17);
        Str_delete(_t_Str_1034, &(Bool){1});
    }
    ;
    U32 _t_U64_1036 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1036;
    void *_t_v_1037 = ptr_add(self->data, _t_U64_1036);
    (void)_t_v_1037;
    ;
    return _t_v_1037;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_1052 = U32_gte(i, &self->cap);
    (void)_t_Bool_1052;
    if (_t_Bool_1052) {
        Str *_t_Str_1038 = Str_lit("Str", 3ULL);
        (void)_t_Str_1038;
        U32 _t_U32_1039 = 16;
        (void)_t_U32_1039;
        U32 _t_U32_1040 = 5;
        (void)_t_U32_1040;
        Array *_va_Array_18 = Array_new(_t_Str_1038, &_t_U32_1039, &_t_U32_1040);
        (void)_va_Array_18;
        Str_delete(_t_Str_1038, &(Bool){1});
        ;
        ;
        U32 _t_U32_1041 = 0;
        (void)_t_U32_1041;
        Str *_t_Str_1042 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_1042;
        Array_set(_va_Array_18, &_t_U32_1041, _t_Str_1042);
        ;
        U32 _t_U32_1043 = 1;
        (void)_t_U32_1043;
        Str *_t_Str_1044 = U32_to_str(i);
        (void)_t_Str_1044;
        Array_set(_va_Array_18, &_t_U32_1043, _t_Str_1044);
        ;
        U32 _t_U32_1045 = 2;
        (void)_t_U32_1045;
        Str *_t_Str_1046 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1046;
        Array_set(_va_Array_18, &_t_U32_1045, _t_Str_1046);
        ;
        U32 _t_U32_1047 = 3;
        (void)_t_U32_1047;
        Str *_t_Str_1048 = U32_to_str(&self->cap);
        (void)_t_Str_1048;
        Array_set(_va_Array_18, &_t_U32_1047, _t_Str_1048);
        ;
        U32 _t_U32_1049 = 4;
        (void)_t_U32_1049;
        Str *_t_Str_1050 = Str_lit(")", 1ULL);
        (void)_t_Str_1050;
        Array_set(_va_Array_18, &_t_U32_1049, _t_Str_1050);
        ;
        Str *_t_Str_1051 = Str_lit("./src/core/array.til:43:19", 26ULL);
        (void)_t_Str_1051;
        panic(_t_Str_1051, _va_Array_18);
        Str_delete(_t_Str_1051, &(Bool){1});
    }
    ;
    U32 _t_U64_1053 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1053;
    void *_t_v_1054 = ptr_add(self->data, _t_U64_1053);
    (void)_t_v_1054;
    Bool _t_Bool_1055 = 0;
    (void)_t_Bool_1055;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1054, &_t_Bool_1055);
    ;
    ;
    U32 _t_U64_1056 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1056;
    void *_t_v_1057 = ptr_add(self->data, _t_U64_1056);
    (void)_t_v_1057;
    memcpy(_t_v_1057, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_1058 = self->cap;
        (void)_re_U32_1058;
        U32 _rc_U32_1058 = 0;
        (void)_rc_U32_1058;
        Bool _t_Bool_1067 = U32_lte(&_rc_U32_1058, &_re_U32_1058);
        (void)_t_Bool_1067;
        if (_t_Bool_1067) {
            while (1) {
                Bool _wcond_Bool_1059 = U32_lt(&_rc_U32_1058, &_re_U32_1058);
                (void)_wcond_Bool_1059;
                if (_wcond_Bool_1059) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1058);
                (void)i;
                U32_inc(&_rc_U32_1058);
                U32 _t_U64_1060 = U32_mul(i, self->elem_size);
                (void)_t_U64_1060;
                ;
                void *_t_v_1061 = ptr_add(self->data, _t_U64_1060);
                (void)_t_v_1061;
                Bool _t_Bool_1062 = 0;
                (void)_t_Bool_1062;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1061, &_t_Bool_1062);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1063 = U32_gt(&_rc_U32_1058, &_re_U32_1058);
                (void)_wcond_Bool_1063;
                if (_wcond_Bool_1063) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1058);
                (void)i;
                U32_dec(&_rc_U32_1058);
                U32 _t_U64_1064 = U32_mul(i, self->elem_size);
                (void)_t_U64_1064;
                ;
                void *_t_v_1065 = ptr_add(self->data, _t_U64_1064);
                (void)_t_v_1065;
                Bool _t_Bool_1066 = 0;
                (void)_t_Bool_1066;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1065, &_t_Bool_1066);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_1068 = 0;
    (void)_t_Bool_1068;
    Str_delete(&self->elem_type, &_t_Bool_1068);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_1081 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_1081;
    void * new_data = malloc(_t_U64_1081);
    (void)new_data;
    ;
    {
        U32 _re_U32_1069 = self->cap;
        (void)_re_U32_1069;
        U32 _rc_U32_1069 = 0;
        (void)_rc_U32_1069;
        Bool _t_Bool_1080 = U32_lte(&_rc_U32_1069, &_re_U32_1069);
        (void)_t_Bool_1080;
        if (_t_Bool_1080) {
            while (1) {
                Bool _wcond_Bool_1070 = U32_lt(&_rc_U32_1069, &_re_U32_1069);
                (void)_wcond_Bool_1070;
                if (_wcond_Bool_1070) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1069);
                (void)i;
                U32_inc(&_rc_U32_1069);
                U32 _t_U64_1071 = U32_mul(i, self->elem_size);
                (void)_t_U64_1071;
                void *_t_v_1072 = ptr_add(self->data, _t_U64_1071);
                (void)_t_v_1072;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1072);
                (void)cloned;
                ;
                U32 _t_U64_1073 = U32_mul(i, self->elem_size);
                (void)_t_U64_1073;
                ;
                void *_t_v_1074 = ptr_add(new_data, _t_U64_1073);
                (void)_t_v_1074;
                memcpy(_t_v_1074, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1075 = U32_gt(&_rc_U32_1069, &_re_U32_1069);
                (void)_wcond_Bool_1075;
                if (_wcond_Bool_1075) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1069);
                (void)i;
                U32_dec(&_rc_U32_1069);
                U32 _t_U64_1076 = U32_mul(i, self->elem_size);
                (void)_t_U64_1076;
                void *_t_v_1077 = ptr_add(self->data, _t_U64_1076);
                (void)_t_v_1077;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1077);
                (void)cloned;
                ;
                U32 _t_U64_1078 = U32_mul(i, self->elem_size);
                (void)_t_U64_1078;
                ;
                void *_t_v_1079 = ptr_add(new_data, _t_U64_1078);
                (void)_t_v_1079;
                memcpy(_t_v_1079, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_1082 = malloc(sizeof(Array));
    _t_Array_1082->data = new_data;
    _t_Array_1082->cap = self->cap;
    _t_Array_1082->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_1082->elem_type = *_ca; free(_ca); }
    _t_Array_1082->elem_clone = (void *)self->elem_clone;
    _t_Array_1082->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_1082;
    return _t_Array_1082;
}

U32 Array_size(void) {
    I64 _t_I64_1083 = 48;
    (void)_t_I64_1083;
    return _t_I64_1083;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2722 = Str_lit("Str", 3ULL);
    (void)_t_Str_2722;
    U32 _t_U32_2723 = 16;
    (void)_t_U32_2723;
    U32 _t_U32_2724 = 3;
    (void)_t_U32_2724;
    Array *_va_Array_92 = Array_new(_t_Str_2722, &_t_U32_2723, &_t_U32_2724);
    (void)_va_Array_92;
    Str_delete(_t_Str_2722, &(Bool){1});
    ;
    ;
    U32 _t_U32_2725 = 0;
    (void)_t_U32_2725;
    Str *_t_Str_2726 = Str_clone(loc_str);
    (void)_t_Str_2726;
    Array_set(_va_Array_92, &_t_U32_2725, _t_Str_2726);
    ;
    U32 _t_U32_2727 = 1;
    (void)_t_U32_2727;
    Str *_t_Str_2728 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2728;
    Array_set(_va_Array_92, &_t_U32_2727, _t_Str_2728);
    ;
    Array *_t_Array_2729 = Array_clone(parts);
    (void)_t_Array_2729;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2730 = 2;
    (void)_t_U32_2730;
    Str *_t_Str_2731 = format(_t_Array_2729);
    (void)_t_Str_2731;
    Array_set(_va_Array_92, &_t_U32_2730, _t_Str_2731);
    ;
    println(_va_Array_92);
    I64 _t_I64_2732 = 1;
    (void)_t_I64_2732;
    exit(_t_I64_2732);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2751 = not(DEREF(cond));
    (void)_t_Bool_2751;
    if (_t_Bool_2751) {
        Str *_t_Str_2746 = Str_lit("Str", 3ULL);
        (void)_t_Str_2746;
        U32 _t_U32_2747 = 16;
        (void)_t_U32_2747;
        U32 _t_U32_2748 = 1;
        (void)_t_U32_2748;
        Array *_va_Array_95 = Array_new(_t_Str_2746, &_t_U32_2747, &_t_U32_2748);
        (void)_va_Array_95;
        Str_delete(_t_Str_2746, &(Bool){1});
        ;
        ;
        U32 _t_U32_2749 = 0;
        (void)_t_U32_2749;
        Str *_t_Str_2750 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2750;
        Array_set(_va_Array_95, &_t_U32_2749, _t_Str_2750);
        ;
        panic(loc_str, _va_Array_95);
    }
    ;
    Bool _t_Bool_2752 = 1;
    (void)_t_Bool_2752;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2752; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2775 = I64_neq(a, b);
    (void)_t_Bool_2775;
    if (_t_Bool_2775) {
        Str *_t_Str_2762 = Str_lit("Str", 3ULL);
        (void)_t_Str_2762;
        U32 _t_U32_2763 = 16;
        (void)_t_U32_2763;
        U32 _t_U32_2764 = 5;
        (void)_t_U32_2764;
        Array *_va_Array_97 = Array_new(_t_Str_2762, &_t_U32_2763, &_t_U32_2764);
        (void)_va_Array_97;
        Str_delete(_t_Str_2762, &(Bool){1});
        ;
        ;
        U32 _t_U32_2765 = 0;
        (void)_t_U32_2765;
        Str *_t_Str_2766 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2766;
        Array_set(_va_Array_97, &_t_U32_2765, _t_Str_2766);
        ;
        U32 _t_U32_2767 = 1;
        (void)_t_U32_2767;
        Str *_t_Str_2768 = I64_to_str(a);
        (void)_t_Str_2768;
        Array_set(_va_Array_97, &_t_U32_2767, _t_Str_2768);
        ;
        U32 _t_U32_2769 = 2;
        (void)_t_U32_2769;
        Str *_t_Str_2770 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2770;
        Array_set(_va_Array_97, &_t_U32_2769, _t_Str_2770);
        ;
        U32 _t_U32_2771 = 3;
        (void)_t_U32_2771;
        Str *_t_Str_2772 = I64_to_str(b);
        (void)_t_Str_2772;
        Array_set(_va_Array_97, &_t_U32_2771, _t_Str_2772);
        ;
        U32 _t_U32_2773 = 4;
        (void)_t_U32_2773;
        Str *_t_Str_2774 = Str_lit("'", 1ULL);
        (void)_t_Str_2774;
        Array_set(_va_Array_97, &_t_U32_2773, _t_Str_2774);
        ;
        panic(loc_str, _va_Array_97);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2791 = parts;
        (void)_fc_Array_2791;
        U32 _fi_USize_2791 = 0;
        (void)_fi_USize_2791;
        while (1) {
            U32 _t_U32_2793; { U32 *_hp = (U32 *)Array_len(_fc_Array_2791); _t_U32_2793 = *_hp; free(_hp); }
            (void)_t_U32_2793;
            Bool _wcond_Bool_2792 = U32_lt(&_fi_USize_2791, &_t_U32_2793);
            (void)_wcond_Bool_2792;
            ;
            if (_wcond_Bool_2792) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2791, &_fi_USize_2791);
            (void)s;
            U32 _t_U32_2794 = 1;
            (void)_t_U32_2794;
            U32 _t_U32_2795 = U32_add(_fi_USize_2791, _t_U32_2794);
            (void)_t_U32_2795;
            ;
            _fi_USize_2791 = _t_U32_2795;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

void test_simple_add(void) {
    I64 _t_I64_2987 = 1;
    (void)_t_I64_2987;
    I64 _t_I64_2988 = 2;
    (void)_t_I64_2988;
    I64 result = 3;
    (void)result;
    ;
    ;
    Str *_t_Str_2989 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_2989;
    I64 _t_I64_2990 = 3;
    (void)_t_I64_2990;
    assert_eq(_t_Str_2989, &result, &_t_I64_2990);
    ;
    Str_delete(_t_Str_2989, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 _t_I64_2991 = 1;
    (void)_t_I64_2991;
    I64 _t_I64_2992 = 2;
    (void)_t_I64_2992;
    I64 _t_I64_2993 = 10;
    (void)_t_I64_2993;
    I64 _t_I64_2994 = 5;
    (void)_t_I64_2994;
    I64 _t_I64_2995 = 3;
    (void)_t_I64_2995;
    ;
    ;
    I64 _t_I64_2996 = 5;
    (void)_t_I64_2996;
    ;
    ;
    I64 result = 15;
    (void)result;
    ;
    ;
    Str *_t_Str_2997 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_2997;
    I64 _t_I64_2998 = 15;
    (void)_t_I64_2998;
    assert_eq(_t_Str_2997, &result, &_t_I64_2998);
    ;
    Str_delete(_t_Str_2997, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 _t_I64_2999 = 2;
    (void)_t_I64_2999;
    I64 _t_I64_3000 = 3;
    (void)_t_I64_3000;
    I64 _t_I64_3001 = 4;
    (void)_t_I64_3001;
    I64 _t_I64_3002 = 5;
    (void)_t_I64_3002;
    I64 _t_I64_3003 = 6;
    (void)_t_I64_3003;
    ;
    ;
    I64 _t_I64_3004 = 20;
    (void)_t_I64_3004;
    ;
    ;
    I64 result = 26;
    (void)result;
    ;
    ;
    Str *_t_Str_3005 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_3005;
    I64 _t_I64_3006 = 26;
    (void)_t_I64_3006;
    assert_eq(_t_Str_3005, &result, &_t_I64_3006);
    ;
    Str_delete(_t_Str_3005, &(Bool){1});
    ;
}

Str * poem(I64 * depth, Str * current, Str * s1, Str * s2) {
    (void)depth;
    (void)current;
    (void)s1;
    (void)s2;
    I64 _t_I64_3014 = 4;
    (void)_t_I64_3014;
    Bool _t_Bool_3015 = I64_eq(DEREF(depth), _t_I64_3014);
    (void)_t_Bool_3015;
    ;
    if (_t_Bool_3015) {
        Str *_t_Str_3007 = Str_lit("\n", 2ULL);
        (void)_t_Str_3007;
        Str *_t_Str_3008 = Str_concat(current, _t_Str_3007);
        (void)_t_Str_3008;
        Str_delete(_t_Str_3007, &(Bool){1});
        ;
        return _t_Str_3008;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    I64 _t_I64_3016 = 1;
    (void)_t_I64_3016;
    I64 _t_I64_3017 = I64_add(DEREF(depth), _t_I64_3016);
    (void)_t_I64_3017;
    ;
    Str *_t_Str_3018 = Str_concat(current, s1);
    (void)_t_Str_3018;
    Str *_t_Str_3019 = poem(&_t_I64_3017, _t_Str_3018, s1, s2);
    (void)_t_Str_3019;
    ;
    Str_delete(_t_Str_3018, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_3019); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_3019, &(Bool){1});
    I64 _t_I64_3020 = 1;
    (void)_t_I64_3020;
    I64 _t_I64_3021 = I64_add(DEREF(depth), _t_I64_3020);
    (void)_t_I64_3021;
    ;
    Str *_t_Str_3022 = Str_concat(current, s2);
    (void)_t_Str_3022;
    Str *_t_Str_3023 = poem(&_t_I64_3021, _t_Str_3022, s1, s2);
    (void)_t_Str_3023;
    ;
    Str_delete(_t_Str_3022, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_3023); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_3023, &(Bool){1});
    I64 _t_I64_3024 = 2;
    (void)_t_I64_3024;
    Bool _t_Bool_3025 = I64_eq(DEREF(depth), _t_I64_3024);
    (void)_t_Bool_3025;
    ;
    if (_t_Bool_3025) {
        I64 _t_I64_3009 = 1;
        (void)_t_I64_3009;
        Str *_t_Str_3010 = Str_lit("lei", 3ULL);
        (void)_t_Str_3010;
        I64 _t_I64_3011 = I64_add(DEREF(depth), _t_I64_3009);
        (void)_t_I64_3011;
        ;
        Str *_t_Str_3012 = Str_concat(current, _t_Str_3010);
        (void)_t_Str_3012;
        Str_delete(_t_Str_3010, &(Bool){1});
        Str *_t_Str_3013 = poem(&_t_I64_3011, _t_Str_3012, s1, s2);
        (void)_t_Str_3013;
        ;
        Str_delete(_t_Str_3012, &(Bool){1});
        { Str *_old = result; result = Str_concat(result, _t_Str_3013); Str_delete(_old, &(Bool){1}); }
        Str_delete(_t_Str_3013, &(Bool){1});
    }
    ;
    return result;
}

Str * make_poem(Str * s1, Str * s2) {
    (void)s1;
    (void)s2;
    I64 _t_I64_3026 = 0;
    (void)_t_I64_3026;
    Str *_t_Str_3027 = Str_lit("", 0ULL);
    (void)_t_Str_3027;
    Str *_t_Str_3028 = poem(&_t_I64_3026, _t_Str_3027, s1, s2);
    (void)_t_Str_3028;
    ;
    Str_delete(_t_Str_3027, &(Bool){1});
    return _t_Str_3028;
}

void test_lolalalo(void) {
    Str *_t_Str_3029 = Str_lit("lo", 2ULL);
    (void)_t_Str_3029;
    Str *_t_Str_3030 = Str_lit("la", 2ULL);
    (void)_t_Str_3030;
    Str *lo_la = make_poem(_t_Str_3029, _t_Str_3030);
    (void)lo_la;
    Str_delete(_t_Str_3029, &(Bool){1});
    Str_delete(_t_Str_3030, &(Bool){1});
    Str *_t_Str_3031 = Str_lit("la", 2ULL);
    (void)_t_Str_3031;
    Str *_t_Str_3032 = Str_lit("lo", 2ULL);
    (void)_t_Str_3032;
    Str *la_lo = make_poem(_t_Str_3031, _t_Str_3032);
    (void)la_lo;
    Str_delete(_t_Str_3031, &(Bool){1});
    Str_delete(_t_Str_3032, &(Bool){1});
    Str *_t_Str_3033 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_3033;
    Str *_t_Str_3034 = Str_lit("src/test/constfold.til:56:12", 28ULL);
    (void)_t_Str_3034;
    Bool _t_Bool_3035 = Str_contains(lo_la, _t_Str_3033);
    (void)_t_Bool_3035;
    Str_delete(_t_Str_3033, &(Bool){1});
    Bool _t_Bool_3036; { Bool *_hp = (Bool *)assert(_t_Str_3034, &_t_Bool_3035); _t_Bool_3036 = *_hp; free(_hp); }
    (void)_t_Bool_3036;
    ;
    ;
    Str_delete(_t_Str_3034, &(Bool){1});
    Str *_t_Str_3037 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_3037;
    Str *_t_Str_3038 = Str_lit("src/test/constfold.til:57:12", 28ULL);
    (void)_t_Str_3038;
    Bool _t_Bool_3039 = Str_contains(la_lo, _t_Str_3037);
    (void)_t_Bool_3039;
    Str_delete(_t_Str_3037, &(Bool){1});
    Bool _t_Bool_3040; { Bool *_hp = (Bool *)assert(_t_Str_3038, &_t_Bool_3039); _t_Bool_3040 = *_hp; free(_hp); }
    (void)_t_Bool_3040;
    ;
    ;
    Str_delete(_t_Str_3038, &(Bool){1});
    Str *_t_Str_3041 = Str_lit("lolei", 5ULL);
    (void)_t_Str_3041;
    Str *_t_Str_3042 = Str_lit("src/test/constfold.til:59:12", 28ULL);
    (void)_t_Str_3042;
    Bool _t_Bool_3043 = Str_contains(lo_la, _t_Str_3041);
    (void)_t_Bool_3043;
    Str_delete(_t_Str_3041, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    Bool _t_Bool_3044; { Bool *_hp = (Bool *)assert(_t_Str_3042, &_t_Bool_3043); _t_Bool_3044 = *_hp; free(_hp); }
    (void)_t_Bool_3044;
    ;
    ;
    Str_delete(_t_Str_3042, &(Bool){1});
    Str *_t_Str_3045 = Str_lit("lalei", 5ULL);
    (void)_t_Str_3045;
    Str *_t_Str_3046 = Str_lit("src/test/constfold.til:60:12", 28ULL);
    (void)_t_Str_3046;
    Bool _t_Bool_3047 = Str_contains(la_lo, _t_Str_3045);
    (void)_t_Bool_3047;
    Str_delete(_t_Str_3045, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    Bool _t_Bool_3048; { Bool *_hp = (Bool *)assert(_t_Str_3046, &_t_Bool_3047); _t_Bool_3048 = *_hp; free(_hp); }
    (void)_t_Bool_3048;
    ;
    ;
    Str_delete(_t_Str_3046, &(Bool){1});
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
    I64 _t_I64_856 = 0;
    (void)_t_I64_856;
    I64 _t_I64_857 = 1;
    (void)_t_I64_857;
    I64 _t_I64_858 = I64_sub(_t_I64_856, _t_I64_857);
    (void)_t_I64_858;
    CAP_LIT = I64_to_usize(_t_I64_858);
    (void)CAP_LIT;
    I64 _t_I64_859 = 0;
    (void)_t_I64_859;
    I64 _t_I64_860 = 2;
    (void)_t_I64_860;
    I64 _t_I64_861 = I64_sub(_t_I64_859, _t_I64_860);
    (void)_t_I64_861;
    CAP_VIEW = I64_to_usize(_t_I64_861);
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
