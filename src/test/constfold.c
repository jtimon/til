#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef enum {
    TilType_TAG_Unknown,
    TilType_TAG_None,
    TilType_TAG_I64,
    TilType_TAG_U8,
    TilType_TAG_I16,
    TilType_TAG_I32,
    TilType_TAG_U32,
    TilType_TAG_U64,
    TilType_TAG_F32,
    TilType_TAG_Bool,
    TilType_TAG_Struct,
    TilType_TAG_StructDef,
    TilType_TAG_Enum,
    TilType_TAG_EnumDef,
    TilType_TAG_FuncDef,
    TilType_TAG_FuncPtr,
    TilType_TAG_Dynamic,
    TilType_TAG_Custom
} TilType_tag;
typedef struct TilType TilType;
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


struct TilType {
    TilType_tag tag;
    union {
        Str Struct;
        Str Enum;
        Str Custom;
    } data;
};

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
Bool TilType_eq(TilType * a, TilType * b);
Bool TilType_is(TilType * self, TilType * other);
void TilType_delete(TilType * self, Bool * call_free);
Str * TilType_to_str(TilType * self);
TilType * TilType_clone(TilType * self);
U32 TilType_size(void);
Vec * Vec_new_type_name(Str * elem_type);
Vec * Vec_new(TilType * T);
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
Bool TilType_eq(TilType * a, TilType * b);
Bool TilType_is(TilType * self, TilType * other);
void TilType_delete(TilType * self, Bool * call_free);
Str * TilType_to_str(TilType * self);
TilType * TilType_clone(TilType * self);
U32 TilType_size(void);
Vec * Vec_new_type_name(Str * elem_type);
Vec * Vec_new(TilType * T);
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
Bool TilType_eq(TilType *, TilType *);
TilType *TilType_Unknown();
TilType *TilType_None();
TilType *TilType_I64();
TilType *TilType_U8();
TilType *TilType_I16();
TilType *TilType_I32();
TilType *TilType_U32();
TilType *TilType_U64();
TilType *TilType_F32();
TilType *TilType_Bool();
TilType *TilType_Struct(Str *);
TilType *TilType_StructDef();
TilType *TilType_Enum(Str *);
TilType *TilType_EnumDef();
TilType *TilType_FuncDef();
TilType *TilType_FuncPtr();
TilType *TilType_Dynamic();
TilType *TilType_Custom(Str *);

void *dyn_fn(Str *type_name, Str *method);
U32 dyn_size_of(Str *type_name);
Str *dyn_type_to_str(TilType *type);

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

TilType *TilType_Unknown() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_Unknown;
    return r;
}
TilType *TilType_None() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_None;
    return r;
}
TilType *TilType_I64() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_I64;
    return r;
}
TilType *TilType_U8() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_U8;
    return r;
}
TilType *TilType_I16() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_I16;
    return r;
}
TilType *TilType_I32() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_I32;
    return r;
}
TilType *TilType_U32() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_U32;
    return r;
}
TilType *TilType_U64() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_U64;
    return r;
}
TilType *TilType_F32() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_F32;
    return r;
}
TilType *TilType_Bool() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_Bool;
    return r;
}
TilType *TilType_Struct(Str * val) {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_Struct;
    { Str * _tmp = Str_clone(val); r->data.Struct = *_tmp; free(_tmp); }
    return r;
}
TilType *TilType_StructDef() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_StructDef;
    return r;
}
TilType *TilType_Enum(Str * val) {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_Enum;
    { Str * _tmp = Str_clone(val); r->data.Enum = *_tmp; free(_tmp); }
    return r;
}
TilType *TilType_EnumDef() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_EnumDef;
    return r;
}
TilType *TilType_FuncDef() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_FuncDef;
    return r;
}
TilType *TilType_FuncPtr() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_FuncPtr;
    return r;
}
TilType *TilType_Dynamic() {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_Dynamic;
    return r;
}
TilType *TilType_Custom(Str * val) {
    TilType *r = malloc(sizeof(TilType));
    r->tag = TilType_TAG_Custom;
    { Str * _tmp = Str_clone(val); r->data.Custom = *_tmp; free(_tmp); }
    return r;
}
Bool TilType_eq(TilType * a, TilType * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_297 = TilType_is(a, &(TilType){.tag = TilType_TAG_Custom});
    (void)_t_Bool_297;
    Bool _t_Bool_298 = TilType_is(a, &(TilType){.tag = TilType_TAG_Struct});
    (void)_t_Bool_298;
    Bool _t_Bool_299 = or(_t_Bool_297, _t_Bool_298);
    (void)_t_Bool_299;
    ;
    ;
    Bool _t_Bool_300 = TilType_is(a, &(TilType){.tag = TilType_TAG_Enum});
    (void)_t_Bool_300;
    Bool a_named = or(_t_Bool_299, _t_Bool_300);
    (void)a_named;
    ;
    ;
    Bool _t_Bool_301 = TilType_is(b, &(TilType){.tag = TilType_TAG_Custom});
    (void)_t_Bool_301;
    Bool _t_Bool_302 = TilType_is(b, &(TilType){.tag = TilType_TAG_Struct});
    (void)_t_Bool_302;
    Bool _t_Bool_303 = or(_t_Bool_301, _t_Bool_302);
    (void)_t_Bool_303;
    ;
    ;
    Bool _t_Bool_304 = TilType_is(b, &(TilType){.tag = TilType_TAG_Enum});
    (void)_t_Bool_304;
    Bool b_named = or(_t_Bool_303, _t_Bool_304);
    (void)b_named;
    ;
    ;
    Bool _t_Bool_305 = and(a_named, b_named);
    (void)_t_Bool_305;
    if (_t_Bool_305) {
        Str *an = get_payload(a);
        (void)an;
        Str *bn = get_payload(b);
        (void)bn;
        Bool _t_Bool_280 = Str_eq(an, bn);
        (void)_t_Bool_280;
        ;
        ;
        ;
        return _t_Bool_280;
    }
    ;
    Bool _t_Bool_306 = or(a_named, b_named);
    (void)_t_Bool_306;
    ;
    ;
    if (_t_Bool_306) {
        Bool _t_Bool_281 = 0;
        (void)_t_Bool_281;
        ;
        return _t_Bool_281;
    }
    ;
    Bool _t_Bool_307 = TilType_is(a, &(TilType){.tag = TilType_TAG_Unknown});
    (void)_t_Bool_307;
    if (_t_Bool_307) {
        Bool _t_Bool_282 = TilType_is(b, &(TilType){.tag = TilType_TAG_Unknown});
        (void)_t_Bool_282;
        ;
        return _t_Bool_282;
    }
    ;
    Bool _t_Bool_308 = TilType_is(a, &(TilType){.tag = TilType_TAG_None});
    (void)_t_Bool_308;
    if (_t_Bool_308) {
        Bool _t_Bool_283 = TilType_is(b, &(TilType){.tag = TilType_TAG_None});
        (void)_t_Bool_283;
        ;
        return _t_Bool_283;
    }
    ;
    Bool _t_Bool_309 = TilType_is(a, &(TilType){.tag = TilType_TAG_I64});
    (void)_t_Bool_309;
    if (_t_Bool_309) {
        Bool _t_Bool_284 = TilType_is(b, &(TilType){.tag = TilType_TAG_I64});
        (void)_t_Bool_284;
        ;
        return _t_Bool_284;
    }
    ;
    Bool _t_Bool_310 = TilType_is(a, &(TilType){.tag = TilType_TAG_U8});
    (void)_t_Bool_310;
    if (_t_Bool_310) {
        Bool _t_Bool_285 = TilType_is(b, &(TilType){.tag = TilType_TAG_U8});
        (void)_t_Bool_285;
        ;
        return _t_Bool_285;
    }
    ;
    Bool _t_Bool_311 = TilType_is(a, &(TilType){.tag = TilType_TAG_I16});
    (void)_t_Bool_311;
    if (_t_Bool_311) {
        Bool _t_Bool_286 = TilType_is(b, &(TilType){.tag = TilType_TAG_I16});
        (void)_t_Bool_286;
        ;
        return _t_Bool_286;
    }
    ;
    Bool _t_Bool_312 = TilType_is(a, &(TilType){.tag = TilType_TAG_I32});
    (void)_t_Bool_312;
    if (_t_Bool_312) {
        Bool _t_Bool_287 = TilType_is(b, &(TilType){.tag = TilType_TAG_I32});
        (void)_t_Bool_287;
        ;
        return _t_Bool_287;
    }
    ;
    Bool _t_Bool_313 = TilType_is(a, &(TilType){.tag = TilType_TAG_U32});
    (void)_t_Bool_313;
    if (_t_Bool_313) {
        Bool _t_Bool_288 = TilType_is(b, &(TilType){.tag = TilType_TAG_U32});
        (void)_t_Bool_288;
        ;
        return _t_Bool_288;
    }
    ;
    Bool _t_Bool_314 = TilType_is(a, &(TilType){.tag = TilType_TAG_U64});
    (void)_t_Bool_314;
    if (_t_Bool_314) {
        Bool _t_Bool_289 = TilType_is(b, &(TilType){.tag = TilType_TAG_U64});
        (void)_t_Bool_289;
        ;
        return _t_Bool_289;
    }
    ;
    Bool _t_Bool_315 = TilType_is(a, &(TilType){.tag = TilType_TAG_F32});
    (void)_t_Bool_315;
    if (_t_Bool_315) {
        Bool _t_Bool_290 = TilType_is(b, &(TilType){.tag = TilType_TAG_F32});
        (void)_t_Bool_290;
        ;
        return _t_Bool_290;
    }
    ;
    Bool _t_Bool_316 = TilType_is(a, &(TilType){.tag = TilType_TAG_Bool});
    (void)_t_Bool_316;
    if (_t_Bool_316) {
        Bool _t_Bool_291 = TilType_is(b, &(TilType){.tag = TilType_TAG_Bool});
        (void)_t_Bool_291;
        ;
        return _t_Bool_291;
    }
    ;
    Bool _t_Bool_317 = TilType_is(a, &(TilType){.tag = TilType_TAG_StructDef});
    (void)_t_Bool_317;
    if (_t_Bool_317) {
        Bool _t_Bool_292 = TilType_is(b, &(TilType){.tag = TilType_TAG_StructDef});
        (void)_t_Bool_292;
        ;
        return _t_Bool_292;
    }
    ;
    Bool _t_Bool_318 = TilType_is(a, &(TilType){.tag = TilType_TAG_EnumDef});
    (void)_t_Bool_318;
    if (_t_Bool_318) {
        Bool _t_Bool_293 = TilType_is(b, &(TilType){.tag = TilType_TAG_EnumDef});
        (void)_t_Bool_293;
        ;
        return _t_Bool_293;
    }
    ;
    Bool _t_Bool_319 = TilType_is(a, &(TilType){.tag = TilType_TAG_FuncDef});
    (void)_t_Bool_319;
    if (_t_Bool_319) {
        Bool _t_Bool_294 = TilType_is(b, &(TilType){.tag = TilType_TAG_FuncDef});
        (void)_t_Bool_294;
        ;
        return _t_Bool_294;
    }
    ;
    Bool _t_Bool_320 = TilType_is(a, &(TilType){.tag = TilType_TAG_FuncPtr});
    (void)_t_Bool_320;
    if (_t_Bool_320) {
        Bool _t_Bool_295 = TilType_is(b, &(TilType){.tag = TilType_TAG_FuncPtr});
        (void)_t_Bool_295;
        ;
        return _t_Bool_295;
    }
    ;
    Bool _t_Bool_321 = TilType_is(a, &(TilType){.tag = TilType_TAG_Dynamic});
    (void)_t_Bool_321;
    if (_t_Bool_321) {
        Bool _t_Bool_296 = TilType_is(b, &(TilType){.tag = TilType_TAG_Dynamic});
        (void)_t_Bool_296;
        ;
        return _t_Bool_296;
    }
    ;
    Bool _t_Bool_322 = 0;
    (void)_t_Bool_322;
    return _t_Bool_322;
}

Bool TilType_is(TilType * self, TilType * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_323 = is(self, other);
    (void)_t_Bool_323;
    return _t_Bool_323;
}

void TilType_delete(TilType * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_330 = is(self, &(TilType){.tag = TilType_TAG_Struct});
    (void)_t_Bool_330;
    if (_t_Bool_330) {
        Str *_t_Str_324 = get_payload(self);
        (void)_t_Str_324;
        Bool _t_Bool_325 = 0;
        (void)_t_Bool_325;
        Str_delete(_t_Str_324, &_t_Bool_325);
        ;
    }
    ;
    Bool _t_Bool_331 = is(self, &(TilType){.tag = TilType_TAG_Enum});
    (void)_t_Bool_331;
    if (_t_Bool_331) {
        Str *_t_Str_326 = get_payload(self);
        (void)_t_Str_326;
        Bool _t_Bool_327 = 0;
        (void)_t_Bool_327;
        Str_delete(_t_Str_326, &_t_Bool_327);
        ;
    }
    ;
    Bool _t_Bool_332 = is(self, &(TilType){.tag = TilType_TAG_Custom});
    (void)_t_Bool_332;
    if (_t_Bool_332) {
        Str *_t_Str_328 = get_payload(self);
        (void)_t_Str_328;
        Bool _t_Bool_329 = 0;
        (void)_t_Bool_329;
        Str_delete(_t_Str_328, &_t_Bool_329);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * TilType_to_str(TilType * self) {
    (void)self;
    Bool _t_Bool_375 = is(self, &(TilType){.tag = TilType_TAG_Unknown});
    (void)_t_Bool_375;
    if (_t_Bool_375) {
        Str *_t_Str_333 = Str_lit("Unknown", 7ULL);
        (void)_t_Str_333;
        ;
        return _t_Str_333;
    }
    ;
    Bool _t_Bool_376 = is(self, &(TilType){.tag = TilType_TAG_None});
    (void)_t_Bool_376;
    if (_t_Bool_376) {
        Str *_t_Str_334 = Str_lit("None", 4ULL);
        (void)_t_Str_334;
        ;
        return _t_Str_334;
    }
    ;
    Bool _t_Bool_377 = is(self, &(TilType){.tag = TilType_TAG_I64});
    (void)_t_Bool_377;
    if (_t_Bool_377) {
        Str *_t_Str_335 = Str_lit("I64", 3ULL);
        (void)_t_Str_335;
        ;
        return _t_Str_335;
    }
    ;
    Bool _t_Bool_378 = is(self, &(TilType){.tag = TilType_TAG_U8});
    (void)_t_Bool_378;
    if (_t_Bool_378) {
        Str *_t_Str_336 = Str_lit("U8", 2ULL);
        (void)_t_Str_336;
        ;
        return _t_Str_336;
    }
    ;
    Bool _t_Bool_379 = is(self, &(TilType){.tag = TilType_TAG_I16});
    (void)_t_Bool_379;
    if (_t_Bool_379) {
        Str *_t_Str_337 = Str_lit("I16", 3ULL);
        (void)_t_Str_337;
        ;
        return _t_Str_337;
    }
    ;
    Bool _t_Bool_380 = is(self, &(TilType){.tag = TilType_TAG_I32});
    (void)_t_Bool_380;
    if (_t_Bool_380) {
        Str *_t_Str_338 = Str_lit("I32", 3ULL);
        (void)_t_Str_338;
        ;
        return _t_Str_338;
    }
    ;
    Bool _t_Bool_381 = is(self, &(TilType){.tag = TilType_TAG_U32});
    (void)_t_Bool_381;
    if (_t_Bool_381) {
        Str *_t_Str_339 = Str_lit("U32", 3ULL);
        (void)_t_Str_339;
        ;
        return _t_Str_339;
    }
    ;
    Bool _t_Bool_382 = is(self, &(TilType){.tag = TilType_TAG_U64});
    (void)_t_Bool_382;
    if (_t_Bool_382) {
        Str *_t_Str_340 = Str_lit("U64", 3ULL);
        (void)_t_Str_340;
        ;
        return _t_Str_340;
    }
    ;
    Bool _t_Bool_383 = is(self, &(TilType){.tag = TilType_TAG_F32});
    (void)_t_Bool_383;
    if (_t_Bool_383) {
        Str *_t_Str_341 = Str_lit("F32", 3ULL);
        (void)_t_Str_341;
        ;
        return _t_Str_341;
    }
    ;
    Bool _t_Bool_384 = is(self, &(TilType){.tag = TilType_TAG_Bool});
    (void)_t_Bool_384;
    if (_t_Bool_384) {
        Str *_t_Str_342 = Str_lit("Bool", 4ULL);
        (void)_t_Str_342;
        ;
        return _t_Str_342;
    }
    ;
    Bool _t_Bool_385 = is(self, &(TilType){.tag = TilType_TAG_Struct});
    (void)_t_Bool_385;
    if (_t_Bool_385) {
        Str *_p_Str_10 = get_payload(self);
        (void)_p_Str_10;
        Str *_t_Str_343 = Str_lit("Str", 3ULL);
        (void)_t_Str_343;
        U32 _t_U32_344 = 3;
        (void)_t_U32_344;
        Array *_va_Array_4 = Array_new(_t_Str_343, &_t_U32_344);
        (void)_va_Array_4;
        Str_delete(_t_Str_343, &(Bool){1});
        ;
        U32 _t_U32_345 = 0;
        (void)_t_U32_345;
        Str *_t_Str_346 = Str_lit("Struct(", 7ULL);
        (void)_t_Str_346;
        Array_set(_va_Array_4, &_t_U32_345, _t_Str_346);
        ;
        U32 _t_U32_347 = 1;
        (void)_t_U32_347;
        Str *_t_Str_348 = Str_to_str(_p_Str_10);
        (void)_t_Str_348;
        Array_set(_va_Array_4, &_t_U32_347, _t_Str_348);
        ;
        U32 _t_U32_349 = 2;
        (void)_t_U32_349;
        Str *_t_Str_350 = Str_lit(")", 1ULL);
        (void)_t_Str_350;
        Array_set(_va_Array_4, &_t_U32_349, _t_Str_350);
        ;
        Str *_t_Str_351 = format(_va_Array_4);
        (void)_t_Str_351;
        ;
        return _t_Str_351;
    }
    ;
    Bool _t_Bool_386 = is(self, &(TilType){.tag = TilType_TAG_StructDef});
    (void)_t_Bool_386;
    if (_t_Bool_386) {
        Str *_t_Str_352 = Str_lit("StructDef", 9ULL);
        (void)_t_Str_352;
        ;
        return _t_Str_352;
    }
    ;
    Bool _t_Bool_387 = is(self, &(TilType){.tag = TilType_TAG_Enum});
    (void)_t_Bool_387;
    if (_t_Bool_387) {
        Str *_p_Str_12 = get_payload(self);
        (void)_p_Str_12;
        Str *_t_Str_353 = Str_lit("Str", 3ULL);
        (void)_t_Str_353;
        U32 _t_U32_354 = 3;
        (void)_t_U32_354;
        Array *_va_Array_5 = Array_new(_t_Str_353, &_t_U32_354);
        (void)_va_Array_5;
        Str_delete(_t_Str_353, &(Bool){1});
        ;
        U32 _t_U32_355 = 0;
        (void)_t_U32_355;
        Str *_t_Str_356 = Str_lit("Enum(", 5ULL);
        (void)_t_Str_356;
        Array_set(_va_Array_5, &_t_U32_355, _t_Str_356);
        ;
        U32 _t_U32_357 = 1;
        (void)_t_U32_357;
        Str *_t_Str_358 = Str_to_str(_p_Str_12);
        (void)_t_Str_358;
        Array_set(_va_Array_5, &_t_U32_357, _t_Str_358);
        ;
        U32 _t_U32_359 = 2;
        (void)_t_U32_359;
        Str *_t_Str_360 = Str_lit(")", 1ULL);
        (void)_t_Str_360;
        Array_set(_va_Array_5, &_t_U32_359, _t_Str_360);
        ;
        Str *_t_Str_361 = format(_va_Array_5);
        (void)_t_Str_361;
        ;
        return _t_Str_361;
    }
    ;
    Bool _t_Bool_388 = is(self, &(TilType){.tag = TilType_TAG_EnumDef});
    (void)_t_Bool_388;
    if (_t_Bool_388) {
        Str *_t_Str_362 = Str_lit("EnumDef", 7ULL);
        (void)_t_Str_362;
        ;
        return _t_Str_362;
    }
    ;
    Bool _t_Bool_389 = is(self, &(TilType){.tag = TilType_TAG_FuncDef});
    (void)_t_Bool_389;
    if (_t_Bool_389) {
        Str *_t_Str_363 = Str_lit("FuncDef", 7ULL);
        (void)_t_Str_363;
        ;
        return _t_Str_363;
    }
    ;
    Bool _t_Bool_390 = is(self, &(TilType){.tag = TilType_TAG_FuncPtr});
    (void)_t_Bool_390;
    if (_t_Bool_390) {
        Str *_t_Str_364 = Str_lit("FuncPtr", 7ULL);
        (void)_t_Str_364;
        ;
        return _t_Str_364;
    }
    ;
    Bool _t_Bool_391 = is(self, &(TilType){.tag = TilType_TAG_Dynamic});
    (void)_t_Bool_391;
    if (_t_Bool_391) {
        Str *_t_Str_365 = Str_lit("Dynamic", 7ULL);
        (void)_t_Str_365;
        ;
        return _t_Str_365;
    }
    ;
    Bool _t_Bool_392 = is(self, &(TilType){.tag = TilType_TAG_Custom});
    (void)_t_Bool_392;
    if (_t_Bool_392) {
        Str *_p_Str_17 = get_payload(self);
        (void)_p_Str_17;
        Str *_t_Str_366 = Str_lit("Str", 3ULL);
        (void)_t_Str_366;
        U32 _t_U32_367 = 3;
        (void)_t_U32_367;
        Array *_va_Array_6 = Array_new(_t_Str_366, &_t_U32_367);
        (void)_va_Array_6;
        Str_delete(_t_Str_366, &(Bool){1});
        ;
        U32 _t_U32_368 = 0;
        (void)_t_U32_368;
        Str *_t_Str_369 = Str_lit("Custom(", 7ULL);
        (void)_t_Str_369;
        Array_set(_va_Array_6, &_t_U32_368, _t_Str_369);
        ;
        U32 _t_U32_370 = 1;
        (void)_t_U32_370;
        Str *_t_Str_371 = Str_to_str(_p_Str_17);
        (void)_t_Str_371;
        Array_set(_va_Array_6, &_t_U32_370, _t_Str_371);
        ;
        U32 _t_U32_372 = 2;
        (void)_t_U32_372;
        Str *_t_Str_373 = Str_lit(")", 1ULL);
        (void)_t_Str_373;
        Array_set(_va_Array_6, &_t_U32_372, _t_Str_373);
        ;
        Str *_t_Str_374 = format(_va_Array_6);
        (void)_t_Str_374;
        ;
        return _t_Str_374;
    }
    ;
    Str *_t_Str_393 = Str_lit("unknown", 7ULL);
    (void)_t_Str_393;
    return _t_Str_393;
}

TilType * TilType_clone(TilType * self) {
    (void)self;
    Bool _t_Bool_396 = is(self, &(TilType){.tag = TilType_TAG_Unknown});
    (void)_t_Bool_396;
    if (_t_Bool_396) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_Unknown; return _r; }
    }
    ;
    Bool _t_Bool_397 = is(self, &(TilType){.tag = TilType_TAG_None});
    (void)_t_Bool_397;
    if (_t_Bool_397) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_None; return _r; }
    }
    ;
    Bool _t_Bool_398 = is(self, &(TilType){.tag = TilType_TAG_I64});
    (void)_t_Bool_398;
    if (_t_Bool_398) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_I64; return _r; }
    }
    ;
    Bool _t_Bool_399 = is(self, &(TilType){.tag = TilType_TAG_U8});
    (void)_t_Bool_399;
    if (_t_Bool_399) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_U8; return _r; }
    }
    ;
    Bool _t_Bool_400 = is(self, &(TilType){.tag = TilType_TAG_I16});
    (void)_t_Bool_400;
    if (_t_Bool_400) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_I16; return _r; }
    }
    ;
    Bool _t_Bool_401 = is(self, &(TilType){.tag = TilType_TAG_I32});
    (void)_t_Bool_401;
    if (_t_Bool_401) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_I32; return _r; }
    }
    ;
    Bool _t_Bool_402 = is(self, &(TilType){.tag = TilType_TAG_U32});
    (void)_t_Bool_402;
    if (_t_Bool_402) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_U32; return _r; }
    }
    ;
    Bool _t_Bool_403 = is(self, &(TilType){.tag = TilType_TAG_U64});
    (void)_t_Bool_403;
    if (_t_Bool_403) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_U64; return _r; }
    }
    ;
    Bool _t_Bool_404 = is(self, &(TilType){.tag = TilType_TAG_F32});
    (void)_t_Bool_404;
    if (_t_Bool_404) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_F32; return _r; }
    }
    ;
    Bool _t_Bool_405 = is(self, &(TilType){.tag = TilType_TAG_Bool});
    (void)_t_Bool_405;
    if (_t_Bool_405) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_Bool; return _r; }
    }
    ;
    Bool _t_Bool_406 = is(self, &(TilType){.tag = TilType_TAG_Struct});
    (void)_t_Bool_406;
    if (_t_Bool_406) {
        Str *_clone_payload_Struct_10 = get_payload(self);
        (void)_clone_payload_Struct_10;
        TilType *_t_TilType_394 = TilType_Struct(_clone_payload_Struct_10);
        (void)_t_TilType_394;
        ;
        return _t_TilType_394;
    }
    ;
    Bool _t_Bool_407 = is(self, &(TilType){.tag = TilType_TAG_StructDef});
    (void)_t_Bool_407;
    if (_t_Bool_407) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_StructDef; return _r; }
    }
    ;
    Bool _t_Bool_408 = is(self, &(TilType){.tag = TilType_TAG_Enum});
    (void)_t_Bool_408;
    if (_t_Bool_408) {
        Str *_clone_payload_Enum_12 = get_payload(self);
        (void)_clone_payload_Enum_12;
        TilType *_t_TilType_395 = TilType_Enum(_clone_payload_Enum_12);
        (void)_t_TilType_395;
        ;
        return _t_TilType_395;
    }
    ;
    Bool _t_Bool_409 = is(self, &(TilType){.tag = TilType_TAG_EnumDef});
    (void)_t_Bool_409;
    if (_t_Bool_409) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_EnumDef; return _r; }
    }
    ;
    Bool _t_Bool_410 = is(self, &(TilType){.tag = TilType_TAG_FuncDef});
    (void)_t_Bool_410;
    if (_t_Bool_410) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_FuncDef; return _r; }
    }
    ;
    Bool _t_Bool_411 = is(self, &(TilType){.tag = TilType_TAG_FuncPtr});
    (void)_t_Bool_411;
    if (_t_Bool_411) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_FuncPtr; return _r; }
    }
    ;
    Bool _t_Bool_412 = is(self, &(TilType){.tag = TilType_TAG_Dynamic});
    (void)_t_Bool_412;
    if (_t_Bool_412) {
        ;
        { TilType *_r = malloc(sizeof(TilType)); _r->tag = TilType_TAG_Dynamic; return _r; }
    }
    ;
    Str *_clone_payload_Custom_17 = get_payload(self);
    (void)_clone_payload_Custom_17;
    TilType *_t_TilType_413 = TilType_Custom(_clone_payload_Custom_17);
    (void)_t_TilType_413;
    return _t_TilType_413;
}

U32 TilType_size(void) {
    I64 _t_I64_414 = 24;
    (void)_t_I64_414;
    return _t_I64_414;
}


Vec * Vec_new_type_name(Str * elem_type) {
    (void)elem_type;
    Bool _t_Bool_1492 = Str_is_empty(elem_type);
    (void)_t_Bool_1492;
    if (_t_Bool_1492) {
        Str *_t_Str_1481 = Str_lit("Str", 3ULL);
        (void)_t_Str_1481;
        U32 _t_U32_1482 = 1;
        (void)_t_U32_1482;
        Array *_va_Array_57 = Array_new(_t_Str_1481, &_t_U32_1482);
        (void)_va_Array_57;
        Str_delete(_t_Str_1481, &(Bool){1});
        ;
        U32 _t_U32_1483 = 0;
        (void)_t_U32_1483;
        Str *_t_Str_1484 = Str_lit("Vec.new: elem_type required", 27ULL);
        (void)_t_Str_1484;
        Array_set(_va_Array_57, &_t_U32_1483, _t_Str_1484);
        ;
        Str *_t_Str_1485 = Str_lit("./src/core/vec.til:25:19", 24ULL);
        (void)_t_Str_1485;
        panic(_t_Str_1485, _va_Array_57);
        Str_delete(_t_Str_1485, &(Bool){1});
    }
    ;
    Str *_t_Str_1493 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1493;
    Bool _t_Bool_1494 = Str_eq(elem_type, _t_Str_1493);
    (void)_t_Bool_1494;
    Str_delete(_t_Str_1493, &(Bool){1});
    if (_t_Bool_1494) {
        U64 _t_U64_1486 = 8;
        (void)_t_U64_1486;
        void * _t_v_1487 = malloc(_t_U64_1486);
        (void)_t_v_1487;
        ;
        U32 _t_U32_1488 = 0;
        (void)_t_U32_1488;
        I64 _t_I64_1489 = 1;
        (void)_t_I64_1489;
        I64 _t_I64_1490 = 8;
        (void)_t_I64_1490;
        Vec *_t_Vec_1491 = malloc(sizeof(Vec));
        _t_Vec_1491->data = _t_v_1487;
        _t_Vec_1491->count = _t_U32_1488;
        _t_Vec_1491->cap = _t_I64_1489;
        _t_Vec_1491->elem_size = _t_I64_1490;
        { Str *_ca = Str_clone(elem_type); _t_Vec_1491->elem_type = *_ca; free(_ca); }
        _t_Vec_1491->elem_clone = (void *)(void *)default_clone;
        _t_Vec_1491->elem_delete = (void *)(void *)default_delete;
        (void)_t_Vec_1491;
        ;
        ;
        ;
        ;
        return _t_Vec_1491;
    }
    ;
    U32 sz = dyn_size_of(elem_type);
    (void)sz;
    void * _t_v_1495 = malloc(sz);
    (void)_t_v_1495;
    U32 _t_U32_1496 = 0;
    (void)_t_U32_1496;
    I64 _t_I64_1497 = 1;
    (void)_t_I64_1497;
    void * _t_v_1498 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1498;
    void * _t_v_1499 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_1499;
    Vec *_t_Vec_1500 = malloc(sizeof(Vec));
    _t_Vec_1500->data = _t_v_1495;
    _t_Vec_1500->count = _t_U32_1496;
    _t_Vec_1500->cap = _t_I64_1497;
    _t_Vec_1500->elem_size = sz;
    { Str *_ca = Str_clone(elem_type); _t_Vec_1500->elem_type = *_ca; free(_ca); }
    _t_Vec_1500->elem_clone = _t_v_1498;
    _t_Vec_1500->elem_delete = _t_v_1499;
    (void)_t_Vec_1500;
    ;
    ;
    ;
    return _t_Vec_1500;
}

Vec * Vec_new(TilType * T) {
    (void)T;
    Str *elem_type = dyn_type_to_str(T);
    (void)elem_type;
    Vec *_t_Vec_1501 = Vec_new_type_name(elem_type);
    (void)_t_Vec_1501;
    Str_delete(elem_type, &(Bool){1});
    return _t_Vec_1501;
}

U32 Vec_len(Vec * self) {
    (void)self;
    return self->count;
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t_Bool_1506 = U32_eq(self->count, self->cap);
    (void)_t_Bool_1506;
    if (_t_Bool_1506) {
        U32 _t_U32_1502 = 2;
        (void)_t_U32_1502;
        U32 new_cap = U32_mul(self->cap, _t_U32_1502);
        (void)new_cap;
        ;
        U32 _t_U64_1503 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1503;
        void * _t_v_1504 = realloc(self->data, _t_U64_1503);
        (void)_t_v_1504;
        ;
        self->data = _t_v_1504;
        U32 _t_U32_1505 = U32_clone(&new_cap);
        (void)_t_U32_1505;
        ;
        self->cap = _t_U32_1505;
        ;
    }
    ;
    U32 _t_U64_1507 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_1507;
    void *_t_v_1508 = ptr_add(self->data, _t_U64_1507);
    (void)_t_v_1508;
    memcpy(_t_v_1508, val, self->elem_size);
    ;
    free(val);
    U32 _t_U32_1509 = 1;
    (void)_t_U32_1509;
    U32 _t_U32_1510 = U32_add(self->count, _t_U32_1509);
    (void)_t_U32_1510;
    ;
    self->count = _t_U32_1510;
    ;
}

void Vec_append(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_1522 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_1522;
    Bool _t_Bool_1523 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_1523;
    Bool _t_Bool_1524 = not(_t_Bool_1522);
    (void)_t_Bool_1524;
    ;
    Bool _t_Bool_1525 = not(_t_Bool_1523);
    (void)_t_Bool_1525;
    ;
    Bool _t_Bool_1526 = or(_t_Bool_1524, _t_Bool_1525);
    (void)_t_Bool_1526;
    ;
    ;
    if (_t_Bool_1526) {
        Str *_t_Str_1511 = Str_lit("Str", 3ULL);
        (void)_t_Str_1511;
        U32 _t_U32_1512 = 1;
        (void)_t_U32_1512;
        Array *_va_Array_58 = Array_new(_t_Str_1511, &_t_U32_1512);
        (void)_va_Array_58;
        Str_delete(_t_Str_1511, &(Bool){1});
        ;
        U32 _t_U32_1513 = 0;
        (void)_t_U32_1513;
        Str *_t_Str_1514 = Str_lit("Vec.append: incompatible vecs", 29ULL);
        (void)_t_Str_1514;
        Array_set(_va_Array_58, &_t_U32_1513, _t_Str_1514);
        ;
        Str *_t_Str_1515 = Str_lit("./src/core/vec.til:62:19", 24ULL);
        (void)_t_Str_1515;
        panic(_t_Str_1515, _va_Array_58);
        Str_delete(_t_Str_1515, &(Bool){1});
    }
    ;
    U32 _t_U32_1527 = 0;
    (void)_t_U32_1527;
    Bool _t_Bool_1528 = U32_eq(other->count, _t_U32_1527);
    (void)_t_Bool_1528;
    ;
    if (_t_Bool_1528) {
        ;
        Vec_delete(other, &(Bool){0});
        return;
    }
    ;
    U32 needed = U32_add(self->count, other->count);
    (void)needed;
    Bool _t_Bool_1529 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_1529;
    if (_t_Bool_1529) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_1516 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_1516;
            if (_wcond_Bool_1516) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_1517 = 2;
            (void)_t_U32_1517;
            U32 _t_U32_1518 = U32_mul(new_cap, _t_U32_1517);
            (void)_t_U32_1518;
            ;
            new_cap = _t_U32_1518;
            ;
        }
        U32 _t_U64_1519 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1519;
        void * _t_v_1520 = realloc(self->data, _t_U64_1519);
        (void)_t_v_1520;
        ;
        self->data = _t_v_1520;
        U32 _t_U32_1521 = U32_clone(&new_cap);
        (void)_t_U32_1521;
        ;
        self->cap = _t_U32_1521;
        ;
    }
    ;
    U32 _t_U64_1530 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_1530;
    void *_t_v_1531 = ptr_add(self->data, _t_U64_1530);
    (void)_t_v_1531;
    U32 _t_U64_1532 = U32_mul(other->count, self->elem_size);
    (void)_t_U64_1532;
    memcpy(_t_v_1531, other->data, _t_U64_1532);
    ;
    ;
    U32 _t_U32_1533 = U32_clone(&needed);
    (void)_t_U32_1533;
    ;
    self->count = _t_U32_1533;
    ;
    U32 _t_U32_1534 = 0;
    (void)_t_U32_1534;
    other->count = _t_U32_1534;
    ;
    Vec_delete(other, &(Bool){0});
}

void Vec_move_from(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_1557 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_1557;
    Bool _t_Bool_1558 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_1558;
    Bool _t_Bool_1559 = not(_t_Bool_1557);
    (void)_t_Bool_1559;
    ;
    Bool _t_Bool_1560 = not(_t_Bool_1558);
    (void)_t_Bool_1560;
    ;
    Bool _t_Bool_1561 = or(_t_Bool_1559, _t_Bool_1560);
    (void)_t_Bool_1561;
    ;
    ;
    if (_t_Bool_1561) {
        Str *_t_Str_1535 = Str_lit("Str", 3ULL);
        (void)_t_Str_1535;
        U32 _t_U32_1536 = 1;
        (void)_t_U32_1536;
        Array *_va_Array_59 = Array_new(_t_Str_1535, &_t_U32_1536);
        (void)_va_Array_59;
        Str_delete(_t_Str_1535, &(Bool){1});
        ;
        U32 _t_U32_1537 = 0;
        (void)_t_U32_1537;
        Str *_t_Str_1538 = Str_lit("Vec.move_from: incompatible vecs", 32ULL);
        (void)_t_Str_1538;
        Array_set(_va_Array_59, &_t_U32_1537, _t_Str_1538);
        ;
        Str *_t_Str_1539 = Str_lit("./src/core/vec.til:89:19", 24ULL);
        (void)_t_Str_1539;
        panic(_t_Str_1539, _va_Array_59);
        Str_delete(_t_Str_1539, &(Bool){1});
    }
    ;
    Bool _t_Bool_1562 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1562;
    Str *_t_Str_1563 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1563;
    Bool _t_Bool_1564 = Str_eq(&self->elem_type, _t_Str_1563);
    (void)_t_Bool_1564;
    Str_delete(_t_Str_1563, &(Bool){1});
    Bool _t_Bool_1565 = not(_t_Bool_1562);
    (void)_t_Bool_1565;
    ;
    Bool _t_Bool_1566 = not(_t_Bool_1564);
    (void)_t_Bool_1566;
    ;
    Bool _t_Bool_1567 = and(_t_Bool_1565, _t_Bool_1566);
    (void)_t_Bool_1567;
    ;
    ;
    if (_t_Bool_1567) {
        {
            U32 _re_U32_1540 = self->count;
            (void)_re_U32_1540;
            U32 _rc_U32_1540 = 0;
            (void)_rc_U32_1540;
            Bool _t_Bool_1549 = U32_lte(&_rc_U32_1540, &_re_U32_1540);
            (void)_t_Bool_1549;
            if (_t_Bool_1549) {
                while (1) {
                    Bool _wcond_Bool_1541 = U32_lt(&_rc_U32_1540, &_re_U32_1540);
                    (void)_wcond_Bool_1541;
                    if (_wcond_Bool_1541) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1540);
                    (void)i;
                    U32_inc(&_rc_U32_1540);
                    U32 _t_U64_1542 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1542;
                    ;
                    void *_t_v_1543 = ptr_add(self->data, _t_U64_1542);
                    (void)_t_v_1543;
                    Bool _t_Bool_1544 = 0;
                    (void)_t_Bool_1544;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1543, &_t_Bool_1544);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1545 = U32_gt(&_rc_U32_1540, &_re_U32_1540);
                    (void)_wcond_Bool_1545;
                    if (_wcond_Bool_1545) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1540);
                    (void)i;
                    U32_dec(&_rc_U32_1540);
                    U32 _t_U64_1546 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1546;
                    ;
                    void *_t_v_1547 = ptr_add(self->data, _t_U64_1546);
                    (void)_t_v_1547;
                    Bool _t_Bool_1548 = 0;
                    (void)_t_Bool_1548;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1547, &_t_Bool_1548);
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
    Bool _t_Bool_1568 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_1568;
    if (_t_Bool_1568) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_1550 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_1550;
            if (_wcond_Bool_1550) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_1551 = 2;
            (void)_t_U32_1551;
            U32 _t_U32_1552 = U32_mul(new_cap, _t_U32_1551);
            (void)_t_U32_1552;
            ;
            new_cap = _t_U32_1552;
            ;
        }
        U32 _t_U64_1553 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1553;
        void * _t_v_1554 = realloc(self->data, _t_U64_1553);
        (void)_t_v_1554;
        ;
        self->data = _t_v_1554;
        U32 _t_U32_1555 = U32_clone(&new_cap);
        (void)_t_U32_1555;
        ;
        self->cap = _t_U32_1555;
        ;
    }
    ;
    U32 _t_U32_1569 = 0;
    (void)_t_U32_1569;
    Bool _t_Bool_1570 = U32_gt(&needed, &_t_U32_1569);
    (void)_t_Bool_1570;
    ;
    if (_t_Bool_1570) {
        U32 _t_U64_1556 = U32_mul(needed, self->elem_size);
        (void)_t_U64_1556;
        memcpy(self->data, other->data, _t_U64_1556);
        ;
    }
    ;
    U32 _t_U32_1571 = U32_clone(&needed);
    (void)_t_U32_1571;
    ;
    self->count = _t_U32_1571;
    ;
    U32 _t_U32_1572 = 0;
    (void)_t_U32_1572;
    other->count = _t_U32_1572;
    ;
}

void * Vec_get(Vec * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_1586 = U32_gte(i, &self->count);
    (void)_t_Bool_1586;
    if (_t_Bool_1586) {
        Str *_t_Str_1573 = Str_lit("Str", 3ULL);
        (void)_t_Str_1573;
        U32 _t_U32_1574 = 5;
        (void)_t_U32_1574;
        Array *_va_Array_60 = Array_new(_t_Str_1573, &_t_U32_1574);
        (void)_va_Array_60;
        Str_delete(_t_Str_1573, &(Bool){1});
        ;
        U32 _t_U32_1575 = 0;
        (void)_t_U32_1575;
        Str *_t_Str_1576 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t_Str_1576;
        Array_set(_va_Array_60, &_t_U32_1575, _t_Str_1576);
        ;
        U32 _t_U32_1577 = 1;
        (void)_t_U32_1577;
        Str *_t_Str_1578 = U32_to_str(i);
        (void)_t_Str_1578;
        Array_set(_va_Array_60, &_t_U32_1577, _t_Str_1578);
        ;
        U32 _t_U32_1579 = 2;
        (void)_t_U32_1579;
        Str *_t_Str_1580 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1580;
        Array_set(_va_Array_60, &_t_U32_1579, _t_Str_1580);
        ;
        U32 _t_U32_1581 = 3;
        (void)_t_U32_1581;
        Str *_t_Str_1582 = U32_to_str(&self->count);
        (void)_t_Str_1582;
        Array_set(_va_Array_60, &_t_U32_1581, _t_Str_1582);
        ;
        U32 _t_U32_1583 = 4;
        (void)_t_U32_1583;
        Str *_t_Str_1584 = Str_lit(")", 1ULL);
        (void)_t_Str_1584;
        Array_set(_va_Array_60, &_t_U32_1583, _t_Str_1584);
        ;
        Str *_t_Str_1585 = Str_lit("./src/core/vec.til:116:19", 25ULL);
        (void)_t_Str_1585;
        panic(_t_Str_1585, _va_Array_60);
        Str_delete(_t_Str_1585, &(Bool){1});
    }
    ;
    U32 _t_U64_1587 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1587;
    void *_t_v_1588 = ptr_add(self->data, _t_U64_1587);
    (void)_t_v_1588;
    ;
    return _t_v_1588;
}

void * Vec_pop(Vec * self) {
    (void)self;
    U32 _t_U32_1594 = 0;
    (void)_t_U32_1594;
    Bool _t_Bool_1595 = U32_eq(self->count, _t_U32_1594);
    (void)_t_Bool_1595;
    ;
    if (_t_Bool_1595) {
        Str *_t_Str_1589 = Str_lit("Str", 3ULL);
        (void)_t_Str_1589;
        U32 _t_U32_1590 = 1;
        (void)_t_U32_1590;
        Array *_va_Array_61 = Array_new(_t_Str_1589, &_t_U32_1590);
        (void)_va_Array_61;
        Str_delete(_t_Str_1589, &(Bool){1});
        ;
        U32 _t_U32_1591 = 0;
        (void)_t_U32_1591;
        Str *_t_Str_1592 = Str_lit("Vec.pop: empty vec", 18ULL);
        (void)_t_Str_1592;
        Array_set(_va_Array_61, &_t_U32_1591, _t_Str_1592);
        ;
        Str *_t_Str_1593 = Str_lit("./src/core/vec.til:125:19", 25ULL);
        (void)_t_Str_1593;
        panic(_t_Str_1593, _va_Array_61);
        Str_delete(_t_Str_1593, &(Bool){1});
    }
    ;
    U32 _t_U32_1596 = 1;
    (void)_t_U32_1596;
    U32 last = U32_sub(self->count, _t_U32_1596);
    (void)last;
    ;
    void * out = malloc(self->elem_size);
    (void)out;
    U32 _t_U64_1597 = U32_mul(last, self->elem_size);
    (void)_t_U64_1597;
    void *_t_v_1598 = ptr_add(self->data, _t_U64_1597);
    (void)_t_v_1598;
    memcpy(out, _t_v_1598, self->elem_size);
    ;
    U32 _t_U32_1599 = U32_clone(&last);
    (void)_t_U32_1599;
    ;
    self->count = _t_U32_1599;
    ;
    return out;
}

Vec * Vec_take_prefix(Vec * self, U32 * n) {
    (void)self;
    (void)n;
    Bool _t_Bool_1618 = U32_gt(n, &self->count);
    (void)_t_Bool_1618;
    if (_t_Bool_1618) {
        Str *_t_Str_1600 = Str_lit("Str", 3ULL);
        (void)_t_Str_1600;
        U32 _t_U32_1601 = 5;
        (void)_t_U32_1601;
        Array *_va_Array_62 = Array_new(_t_Str_1600, &_t_U32_1601);
        (void)_va_Array_62;
        Str_delete(_t_Str_1600, &(Bool){1});
        ;
        U32 _t_U32_1602 = 0;
        (void)_t_U32_1602;
        Str *_t_Str_1603 = Str_lit("Vec.take_prefix: count ", 23ULL);
        (void)_t_Str_1603;
        Array_set(_va_Array_62, &_t_U32_1602, _t_Str_1603);
        ;
        U32 _t_U32_1604 = 1;
        (void)_t_U32_1604;
        Str *_t_Str_1605 = U32_to_str(n);
        (void)_t_Str_1605;
        Array_set(_va_Array_62, &_t_U32_1604, _t_Str_1605);
        ;
        U32 _t_U32_1606 = 2;
        (void)_t_U32_1606;
        Str *_t_Str_1607 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1607;
        Array_set(_va_Array_62, &_t_U32_1606, _t_Str_1607);
        ;
        U32 _t_U32_1608 = 3;
        (void)_t_U32_1608;
        Str *_t_Str_1609 = U32_to_str(&self->count);
        (void)_t_Str_1609;
        Array_set(_va_Array_62, &_t_U32_1608, _t_Str_1609);
        ;
        U32 _t_U32_1610 = 4;
        (void)_t_U32_1610;
        Str *_t_Str_1611 = Str_lit(")", 1ULL);
        (void)_t_Str_1611;
        Array_set(_va_Array_62, &_t_U32_1610, _t_Str_1611);
        ;
        Str *_t_Str_1612 = Str_lit("./src/core/vec.til:138:19", 25ULL);
        (void)_t_Str_1612;
        panic(_t_Str_1612, _va_Array_62);
        Str_delete(_t_Str_1612, &(Bool){1});
    }
    ;
    U32 prefix_cap = 1;
    (void)prefix_cap;
    U32 _t_U32_1619 = 0;
    (void)_t_U32_1619;
    Bool _t_Bool_1620 = U32_gt(n, &_t_U32_1619);
    (void)_t_Bool_1620;
    ;
    if (_t_Bool_1620) {
        U32 _t_U32_1613 = U32_clone(n);
        (void)_t_U32_1613;
        prefix_cap = _t_U32_1613;
        ;
    }
    ;
    U32 _t_U64_1621 = U32_mul(prefix_cap, self->elem_size);
    (void)_t_U64_1621;
    void * prefix_data = malloc(_t_U64_1621);
    (void)prefix_data;
    ;
    U32 _t_U32_1622 = 0;
    (void)_t_U32_1622;
    Bool _t_Bool_1623 = U32_gt(n, &_t_U32_1622);
    (void)_t_Bool_1623;
    ;
    if (_t_Bool_1623) {
        U32 _t_U64_1614 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_1614;
        memcpy(prefix_data, self->data, _t_U64_1614);
        ;
    }
    ;
    U32 tail_count = U32_sub(self->count, DEREF(n));
    (void)tail_count;
    U32 _t_U32_1624 = 0;
    (void)_t_U32_1624;
    Bool _t_Bool_1625 = U32_gt(&tail_count, &_t_U32_1624);
    (void)_t_Bool_1625;
    ;
    if (_t_Bool_1625) {
        U32 _t_U64_1615 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_1615;
        void *_t_v_1616 = ptr_add(self->data, _t_U64_1615);
        (void)_t_v_1616;
        U32 _t_U64_1617 = U32_mul(tail_count, self->elem_size);
        (void)_t_U64_1617;
        memmove(self->data, _t_v_1616, _t_U64_1617);
        ;
        ;
    }
    ;
    U32 _t_U32_1626 = U32_clone(&tail_count);
    (void)_t_U32_1626;
    ;
    self->count = _t_U32_1626;
    ;
    Vec *_t_Vec_1627 = malloc(sizeof(Vec));
    _t_Vec_1627->data = prefix_data;
    _t_Vec_1627->count = DEREF(n);
    _t_Vec_1627->cap = prefix_cap;
    _t_Vec_1627->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_1627->elem_type = *_ca; free(_ca); }
    _t_Vec_1627->elem_clone = (void *)self->elem_clone;
    _t_Vec_1627->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_1627;
    ;
    return _t_Vec_1627;
}

void Vec_set(Vec * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_1641 = U32_gte(i, &self->count);
    (void)_t_Bool_1641;
    if (_t_Bool_1641) {
        Str *_t_Str_1628 = Str_lit("Str", 3ULL);
        (void)_t_Str_1628;
        U32 _t_U32_1629 = 5;
        (void)_t_U32_1629;
        Array *_va_Array_63 = Array_new(_t_Str_1628, &_t_U32_1629);
        (void)_va_Array_63;
        Str_delete(_t_Str_1628, &(Bool){1});
        ;
        U32 _t_U32_1630 = 0;
        (void)_t_U32_1630;
        Str *_t_Str_1631 = Str_lit("Vec.set: index ", 15ULL);
        (void)_t_Str_1631;
        Array_set(_va_Array_63, &_t_U32_1630, _t_Str_1631);
        ;
        U32 _t_U32_1632 = 1;
        (void)_t_U32_1632;
        Str *_t_Str_1633 = U32_to_str(i);
        (void)_t_Str_1633;
        Array_set(_va_Array_63, &_t_U32_1632, _t_Str_1633);
        ;
        U32 _t_U32_1634 = 2;
        (void)_t_U32_1634;
        Str *_t_Str_1635 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1635;
        Array_set(_va_Array_63, &_t_U32_1634, _t_Str_1635);
        ;
        U32 _t_U32_1636 = 3;
        (void)_t_U32_1636;
        Str *_t_Str_1637 = U32_to_str(&self->count);
        (void)_t_Str_1637;
        Array_set(_va_Array_63, &_t_U32_1636, _t_Str_1637);
        ;
        U32 _t_U32_1638 = 4;
        (void)_t_U32_1638;
        Str *_t_Str_1639 = Str_lit(")", 1ULL);
        (void)_t_Str_1639;
        Array_set(_va_Array_63, &_t_U32_1638, _t_Str_1639);
        ;
        Str *_t_Str_1640 = Str_lit("./src/core/vec.til:162:19", 25ULL);
        (void)_t_Str_1640;
        panic(_t_Str_1640, _va_Array_63);
        Str_delete(_t_Str_1640, &(Bool){1});
    }
    ;
    U32 _t_U64_1642 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1642;
    void *_t_v_1643 = ptr_add(self->data, _t_U64_1642);
    (void)_t_v_1643;
    memcpy(_t_v_1643, val, self->elem_size);
    ;
    free(val);
}

void Vec_push_take(Vec * self, Vec * src, U32 i) {
    (void)self;
    (void)src;
    (void)i;
    Bool _t_Bool_1666 = U32_gte(&i, &src->count);
    (void)_t_Bool_1666;
    if (_t_Bool_1666) {
        Str *_t_Str_1644 = Str_lit("Str", 3ULL);
        (void)_t_Str_1644;
        U32 _t_U32_1645 = 5;
        (void)_t_U32_1645;
        Array *_va_Array_64 = Array_new(_t_Str_1644, &_t_U32_1645);
        (void)_va_Array_64;
        Str_delete(_t_Str_1644, &(Bool){1});
        ;
        U32 _t_U32_1646 = 0;
        (void)_t_U32_1646;
        Str *_t_Str_1647 = Str_lit("Vec.push_take: index ", 21ULL);
        (void)_t_Str_1647;
        Array_set(_va_Array_64, &_t_U32_1646, _t_Str_1647);
        ;
        U32 _t_U32_1648 = 1;
        (void)_t_U32_1648;
        Str *_t_Str_1649 = U32_to_str(&i);
        (void)_t_Str_1649;
        Array_set(_va_Array_64, &_t_U32_1648, _t_Str_1649);
        ;
        U32 _t_U32_1650 = 2;
        (void)_t_U32_1650;
        Str *_t_Str_1651 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1651;
        Array_set(_va_Array_64, &_t_U32_1650, _t_Str_1651);
        ;
        U32 _t_U32_1652 = 3;
        (void)_t_U32_1652;
        Str *_t_Str_1653 = U32_to_str(&src->count);
        (void)_t_Str_1653;
        Array_set(_va_Array_64, &_t_U32_1652, _t_Str_1653);
        ;
        U32 _t_U32_1654 = 4;
        (void)_t_U32_1654;
        Str *_t_Str_1655 = Str_lit(")", 1ULL);
        (void)_t_Str_1655;
        Array_set(_va_Array_64, &_t_U32_1654, _t_Str_1655);
        ;
        Str *_t_Str_1656 = Str_lit("./src/core/vec.til:173:19", 25ULL);
        (void)_t_Str_1656;
        panic(_t_Str_1656, _va_Array_64);
        Str_delete(_t_Str_1656, &(Bool){1});
    }
    ;
    Bool _t_Bool_1667 = U32_eq(self->elem_size, src->elem_size);
    (void)_t_Bool_1667;
    Bool _t_Bool_1668 = Str_eq(&self->elem_type, &src->elem_type);
    (void)_t_Bool_1668;
    Bool _t_Bool_1669 = not(_t_Bool_1667);
    (void)_t_Bool_1669;
    ;
    Bool _t_Bool_1670 = not(_t_Bool_1668);
    (void)_t_Bool_1670;
    ;
    Bool _t_Bool_1671 = or(_t_Bool_1669, _t_Bool_1670);
    (void)_t_Bool_1671;
    ;
    ;
    if (_t_Bool_1671) {
        Str *_t_Str_1657 = Str_lit("Str", 3ULL);
        (void)_t_Str_1657;
        U32 _t_U32_1658 = 1;
        (void)_t_U32_1658;
        Array *_va_Array_65 = Array_new(_t_Str_1657, &_t_U32_1658);
        (void)_va_Array_65;
        Str_delete(_t_Str_1657, &(Bool){1});
        ;
        U32 _t_U32_1659 = 0;
        (void)_t_U32_1659;
        Str *_t_Str_1660 = Str_lit("Vec.push_take: incompatible vecs", 32ULL);
        (void)_t_Str_1660;
        Array_set(_va_Array_65, &_t_U32_1659, _t_Str_1660);
        ;
        Str *_t_Str_1661 = Str_lit("./src/core/vec.til:176:19", 25ULL);
        (void)_t_Str_1661;
        panic(_t_Str_1661, _va_Array_65);
        Str_delete(_t_Str_1661, &(Bool){1});
    }
    ;
    Bool _t_Bool_1672 = U32_eq(self->count, self->cap);
    (void)_t_Bool_1672;
    if (_t_Bool_1672) {
        U32 _t_U32_1662 = 2;
        (void)_t_U32_1662;
        U32 new_cap = U32_mul(self->cap, _t_U32_1662);
        (void)new_cap;
        ;
        U32 _t_U64_1663 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1663;
        void * _t_v_1664 = realloc(self->data, _t_U64_1663);
        (void)_t_v_1664;
        ;
        self->data = _t_v_1664;
        U32 _t_U32_1665 = U32_clone(&new_cap);
        (void)_t_U32_1665;
        ;
        self->cap = _t_U32_1665;
        ;
    }
    ;
    U32 _t_U64_1673 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_1673;
    U32 _t_U64_1674 = U32_mul(i, src->elem_size);
    (void)_t_U64_1674;
    void *_t_v_1675 = ptr_add(self->data, _t_U64_1673);
    (void)_t_v_1675;
    void *_t_v_1676 = ptr_add(src->data, _t_U64_1674);
    (void)_t_v_1676;
    memcpy(_t_v_1675, _t_v_1676, self->elem_size);
    ;
    ;
    U32 _t_U64_1677 = U32_mul(i, src->elem_size);
    (void)_t_U64_1677;
    void *_t_v_1678 = ptr_add(src->data, _t_U64_1677);
    (void)_t_v_1678;
    I32 _t_I32_1679 = 0;
    (void)_t_I32_1679;
    memset(_t_v_1678, _t_I32_1679, src->elem_size);
    ;
    ;
    U32 _t_U32_1680 = 1;
    (void)_t_U32_1680;
    U32 _t_U32_1681 = U32_add(self->count, _t_U32_1680);
    (void)_t_U32_1681;
    ;
    self->count = _t_U32_1681;
    ;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_1693 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1693;
    Str *_t_Str_1694 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1694;
    Bool _t_Bool_1695 = Str_eq(&self->elem_type, _t_Str_1694);
    (void)_t_Bool_1695;
    Str_delete(_t_Str_1694, &(Bool){1});
    Bool _t_Bool_1696 = not(_t_Bool_1693);
    (void)_t_Bool_1696;
    ;
    Bool _t_Bool_1697 = not(_t_Bool_1695);
    (void)_t_Bool_1697;
    ;
    Bool _t_Bool_1698 = and(_t_Bool_1696, _t_Bool_1697);
    (void)_t_Bool_1698;
    ;
    ;
    if (_t_Bool_1698) {
        {
            U32 _re_U32_1682 = self->count;
            (void)_re_U32_1682;
            U32 _rc_U32_1682 = 0;
            (void)_rc_U32_1682;
            Bool _t_Bool_1691 = U32_lte(&_rc_U32_1682, &_re_U32_1682);
            (void)_t_Bool_1691;
            if (_t_Bool_1691) {
                while (1) {
                    Bool _wcond_Bool_1683 = U32_lt(&_rc_U32_1682, &_re_U32_1682);
                    (void)_wcond_Bool_1683;
                    if (_wcond_Bool_1683) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1682);
                    (void)i;
                    U32_inc(&_rc_U32_1682);
                    U32 _t_U64_1684 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1684;
                    ;
                    void *_t_v_1685 = ptr_add(self->data, _t_U64_1684);
                    (void)_t_v_1685;
                    Bool _t_Bool_1686 = 0;
                    (void)_t_Bool_1686;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1685, &_t_Bool_1686);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1687 = U32_gt(&_rc_U32_1682, &_re_U32_1682);
                    (void)_wcond_Bool_1687;
                    if (_wcond_Bool_1687) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1682);
                    (void)i;
                    U32_dec(&_rc_U32_1682);
                    U32 _t_U64_1688 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1688;
                    ;
                    void *_t_v_1689 = ptr_add(self->data, _t_U64_1688);
                    (void)_t_v_1689;
                    Bool _t_Bool_1690 = 0;
                    (void)_t_Bool_1690;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1689, &_t_Bool_1690);
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
    Bool _t_Bool_1699 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1699;
    Bool _t_Bool_1700 = not(_t_Bool_1699);
    (void)_t_Bool_1700;
    ;
    if (_t_Bool_1700) {
        Bool _t_Bool_1692 = 0;
        (void)_t_Bool_1692;
        Str_delete(&self->elem_type, &_t_Bool_1692);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U32 _t_U64_1714 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_1714;
    void * new_data = malloc(_t_U64_1714);
    (void)new_data;
    ;
    Bool _t_Bool_1715 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1715;
    Str *_t_Str_1716 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1716;
    Bool _t_Bool_1717 = Str_eq(&self->elem_type, _t_Str_1716);
    (void)_t_Bool_1717;
    Str_delete(_t_Str_1716, &(Bool){1});
    Bool _t_Bool_1718 = not(_t_Bool_1715);
    (void)_t_Bool_1718;
    ;
    Bool _t_Bool_1719 = not(_t_Bool_1717);
    (void)_t_Bool_1719;
    ;
    Bool _t_Bool_1720 = and(_t_Bool_1718, _t_Bool_1719);
    (void)_t_Bool_1720;
    ;
    ;
    if (_t_Bool_1720) {
        {
            U32 _re_U32_1701 = self->count;
            (void)_re_U32_1701;
            U32 _rc_U32_1701 = 0;
            (void)_rc_U32_1701;
            Bool _t_Bool_1712 = U32_lte(&_rc_U32_1701, &_re_U32_1701);
            (void)_t_Bool_1712;
            if (_t_Bool_1712) {
                while (1) {
                    Bool _wcond_Bool_1702 = U32_lt(&_rc_U32_1701, &_re_U32_1701);
                    (void)_wcond_Bool_1702;
                    if (_wcond_Bool_1702) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1701);
                    (void)i;
                    U32_inc(&_rc_U32_1701);
                    U32 _t_U64_1703 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1703;
                    void *_t_v_1704 = ptr_add(self->data, _t_U64_1703);
                    (void)_t_v_1704;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1704);
                    (void)cloned;
                    ;
                    U32 _t_U64_1705 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1705;
                    ;
                    void *_t_v_1706 = ptr_add(new_data, _t_U64_1705);
                    (void)_t_v_1706;
                    memcpy(_t_v_1706, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1707 = U32_gt(&_rc_U32_1701, &_re_U32_1701);
                    (void)_wcond_Bool_1707;
                    if (_wcond_Bool_1707) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1701);
                    (void)i;
                    U32_dec(&_rc_U32_1701);
                    U32 _t_U64_1708 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1708;
                    void *_t_v_1709 = ptr_add(self->data, _t_U64_1708);
                    (void)_t_v_1709;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1709);
                    (void)cloned;
                    ;
                    U32 _t_U64_1710 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1710;
                    ;
                    void *_t_v_1711 = ptr_add(new_data, _t_U64_1710);
                    (void)_t_v_1711;
                    memcpy(_t_v_1711, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            }
            ;
            ;
            ;
        }
    } else {
        U32 _t_U64_1713 = U32_mul(self->count, self->elem_size);
        (void)_t_U64_1713;
        memcpy(new_data, self->data, _t_U64_1713);
        ;
    }
    ;
    Vec *_t_Vec_1721 = malloc(sizeof(Vec));
    _t_Vec_1721->data = new_data;
    _t_Vec_1721->count = self->count;
    _t_Vec_1721->cap = self->cap;
    _t_Vec_1721->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_1721->elem_type = *_ca; free(_ca); }
    _t_Vec_1721->elem_clone = (void *)self->elem_clone;
    _t_Vec_1721->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_1721;
    return _t_Vec_1721;
}

U32 Vec_size(void) {
    I64 _t_I64_1722 = 56;
    (void)_t_I64_1722;
    return _t_I64_1722;
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    (void)total;
    {
        Array *_fc_Array_1723 = parts;
        (void)_fc_Array_1723;
        U32 _fi_USize_1723 = 0;
        (void)_fi_USize_1723;
        while (1) {
            U32 _t_U32_1725; { U32 *_hp = (U32 *)Array_len(_fc_Array_1723); _t_U32_1725 = *_hp; free(_hp); }
            (void)_t_U32_1725;
            Bool _wcond_Bool_1724 = U32_lt(&_fi_USize_1723, &_t_U32_1725);
            (void)_wcond_Bool_1724;
            ;
            if (_wcond_Bool_1724) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_1723, &_fi_USize_1723);
            (void)s;
            U32 _t_U32_1726 = 1;
            (void)_t_U32_1726;
            U32 _t_U32_1727 = U32_add(_fi_USize_1723, _t_U32_1726);
            (void)_t_U32_1727;
            ;
            _fi_USize_1723 = _t_U32_1727;
            ;
            U32 _t_U32_1728 = Str_len(s);
            (void)_t_U32_1728;
            U32 _t_U32_1729 = U32_add(total, _t_U32_1728);
            (void)_t_U32_1729;
            ;
            total = _t_U32_1729;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    (void)out;
    ;
    {
        Array *_fc_Array_1730 = parts;
        (void)_fc_Array_1730;
        U32 _fi_USize_1730 = 0;
        (void)_fi_USize_1730;
        while (1) {
            U32 _t_U32_1732; { U32 *_hp = (U32 *)Array_len(_fc_Array_1730); _t_U32_1732 = *_hp; free(_hp); }
            (void)_t_U32_1732;
            Bool _wcond_Bool_1731 = U32_lt(&_fi_USize_1730, &_t_U32_1732);
            (void)_wcond_Bool_1731;
            ;
            if (_wcond_Bool_1731) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_1730, &_fi_USize_1730);
            (void)s;
            U32 _t_U32_1733 = 1;
            (void)_t_U32_1733;
            U32 _t_U32_1734 = U32_add(_fi_USize_1730, _t_U32_1733);
            (void)_t_U32_1734;
            ;
            _fi_USize_1730 = _t_U32_1734;
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
    Bool _t_Bool_1740 = U32_gte(i, &self->count);
    (void)_t_Bool_1740;
    if (_t_Bool_1740) {
        Str *_t_Str_1735 = Str_lit("Str", 3ULL);
        (void)_t_Str_1735;
        U32 _t_U32_1736 = 1;
        (void)_t_U32_1736;
        Array *_va_Array_66 = Array_new(_t_Str_1735, &_t_U32_1736);
        (void)_va_Array_66;
        Str_delete(_t_Str_1735, &(Bool){1});
        ;
        U32 _t_U32_1737 = 0;
        (void)_t_U32_1737;
        Str *_t_Str_1738 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t_Str_1738;
        Array_set(_va_Array_66, &_t_U32_1737, _t_Str_1738);
        ;
        Str *_t_Str_1739 = Str_lit("./src/core/str.til:39:19", 24ULL);
        (void)_t_Str_1739;
        panic(_t_Str_1739, _va_Array_66);
        Str_delete(_t_Str_1739, &(Bool){1});
    }
    ;
    void *_t_v_1741 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_1741;
    return _t_v_1741;
}

U8 * Str_byte_at(Str * self, U32 * i) {
    (void)self;
    (void)i;
    void *_t_v_1742 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_1742;
    return _t_v_1742;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    (void)min_len;
    Bool _t_Bool_1751 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_1751;
    if (_t_Bool_1751) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_1743 = U32_clone(&min_len);
        (void)_re_U32_1743;
        U32 _rc_U32_1743 = 0;
        (void)_rc_U32_1743;
        Bool _t_Bool_1750 = U32_lte(&_rc_U32_1743, &_re_U32_1743);
        (void)_t_Bool_1750;
        if (_t_Bool_1750) {
            while (1) {
                Bool _wcond_Bool_1744 = U32_lt(&_rc_U32_1743, &_re_U32_1743);
                (void)_wcond_Bool_1744;
                if (_wcond_Bool_1744) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1743);
                (void)i;
                U32_inc(&_rc_U32_1743);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_1745 = 0;
                (void)_t_I64_1745;
                Bool _t_Bool_1746 = I64_neq(&c, &_t_I64_1745);
                (void)_t_Bool_1746;
                ;
                if (_t_Bool_1746) {
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
                Bool _wcond_Bool_1747 = U32_gt(&_rc_U32_1743, &_re_U32_1743);
                (void)_wcond_Bool_1747;
                if (_wcond_Bool_1747) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1743);
                (void)i;
                U32_dec(&_rc_U32_1743);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_1748 = 0;
                (void)_t_I64_1748;
                Bool _t_Bool_1749 = I64_neq(&c, &_t_I64_1748);
                (void)_t_Bool_1749;
                ;
                if (_t_Bool_1749) {
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
    I64 _t_I64_1752 = U32_cmp(a->count, b->count);
    (void)_t_I64_1752;
    return _t_I64_1752;
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_1753 = U32_add(a->count, b->count);
    (void)_t_U32_1753;
    Str *out = Str_with_capacity(&_t_U32_1753);
    (void)out;
    ;
    Str_push_str(out, a);
    Str_push_str(out, b);
    return out;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_1754 = 1;
    (void)_t_U32_1754;
    U32 _t_U64_1755 = U32_add(DEREF(n), _t_U32_1754);
    (void)_t_U64_1755;
    ;
    void * buf = malloc(_t_U64_1755);
    (void)buf;
    ;
    I32 _t_I32_1756 = 0;
    (void)_t_I32_1756;
    U64 _t_U64_1757 = 1;
    (void)_t_U64_1757;
    memset(buf, _t_I32_1756, _t_U64_1757);
    ;
    ;
    I64 _t_I64_1758 = 0;
    (void)_t_I64_1758;
    Str *_t_Str_1759 = malloc(sizeof(Str));
    _t_Str_1759->c_str = buf;
    _t_Str_1759->count = _t_I64_1758;
    _t_Str_1759->cap = DEREF(n);
    (void)_t_Str_1759;
    ;
    return _t_Str_1759;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_1770 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_1770;
    if (_t_Bool_1770) {
        Str *_t_Str_1760 = Str_lit("Str", 3ULL);
        (void)_t_Str_1760;
        U32 _t_U32_1761 = 1;
        (void)_t_U32_1761;
        Array *_va_Array_67 = Array_new(_t_Str_1760, &_t_U32_1761);
        (void)_va_Array_67;
        Str_delete(_t_Str_1760, &(Bool){1});
        ;
        U32 _t_U32_1762 = 0;
        (void)_t_U32_1762;
        Str *_t_Str_1763 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t_Str_1763;
        Array_set(_va_Array_67, &_t_U32_1762, _t_Str_1763);
        ;
        Str *_t_Str_1764 = Str_lit("./src/core/str.til:82:19", 24ULL);
        (void)_t_Str_1764;
        panic(_t_Str_1764, _va_Array_67);
        Str_delete(_t_Str_1764, &(Bool){1});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    (void)new_len;
    Bool _t_Bool_1771 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_1771;
    if (_t_Bool_1771) {
        Str *_t_Str_1765 = Str_lit("Str", 3ULL);
        (void)_t_Str_1765;
        U32 _t_U32_1766 = 1;
        (void)_t_U32_1766;
        Array *_va_Array_68 = Array_new(_t_Str_1765, &_t_U32_1766);
        (void)_va_Array_68;
        Str_delete(_t_Str_1765, &(Bool){1});
        ;
        U32 _t_U32_1767 = 0;
        (void)_t_U32_1767;
        Str *_t_Str_1768 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t_Str_1768;
        Array_set(_va_Array_68, &_t_U32_1767, _t_Str_1768);
        ;
        Str *_t_Str_1769 = Str_lit("./src/core/str.til:86:19", 24ULL);
        (void)_t_Str_1769;
        panic(_t_Str_1769, _va_Array_68);
        Str_delete(_t_Str_1769, &(Bool){1});
    }
    ;
    void *_t_v_1772 = ptr_add(self->c_str, self->count);
    (void)_t_v_1772;
    memcpy(_t_v_1772, s->c_str, s->count);
    U32 _t_U32_1773 = U32_clone(&new_len);
    (void)_t_U32_1773;
    self->count = _t_U32_1773;
    ;
    void *_t_v_1774 = ptr_add(self->c_str, new_len);
    (void)_t_v_1774;
    I32 _t_I32_1775 = 0;
    (void)_t_I32_1775;
    U64 _t_U64_1776 = 1;
    (void)_t_U64_1776;
    memset(_t_v_1774, _t_I32_1775, _t_U64_1776);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_1777 = 1;
    (void)_t_U32_1777;
    U32 _t_U64_1778 = U32_add(val->count, _t_U32_1777);
    (void)_t_U64_1778;
    ;
    void * new_data = malloc(_t_U64_1778);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_1779 = ptr_add(new_data, val->count);
    (void)_t_v_1779;
    I32 _t_I32_1780 = 0;
    (void)_t_I32_1780;
    U64 _t_U64_1781 = 1;
    (void)_t_U64_1781;
    memset(_t_v_1779, _t_I32_1780, _t_U64_1781);
    ;
    ;
    Str *_t_Str_1782 = malloc(sizeof(Str));
    _t_Str_1782->c_str = new_data;
    _t_Str_1782->count = val->count;
    _t_Str_1782->cap = val->count;
    (void)_t_Str_1782;
    return _t_Str_1782;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_1783 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_1783;
    if (_t_Bool_1783) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t_Str_1784 = Str_clone(val);
    (void)_t_Str_1784;
    return _t_Str_1784;
}

Str * Str_substr(Str * s, U32 * start, U32 * n) {
    (void)s;
    (void)start;
    (void)n;
    U32 st = U32_clone(start);
    (void)st;
    U32 ln = U32_clone(n);
    (void)ln;
    Bool _t_Bool_1786 = U32_gt(&st, &s->count);
    (void)_t_Bool_1786;
    if (_t_Bool_1786) {
        st = s->count;
    }
    ;
    U32 _t_U32_1787 = U32_add(st, ln);
    (void)_t_U32_1787;
    Bool _t_Bool_1788 = U32_gt(&_t_U32_1787, &s->count);
    (void)_t_Bool_1788;
    ;
    if (_t_Bool_1788) {
        U32 _t_U32_1785 = U32_sub(s->count, st);
        (void)_t_U32_1785;
        ln = _t_U32_1785;
        ;
    }
    ;
    void *_t_v_1789 = ptr_add(s->c_str, st);
    (void)_t_v_1789;
    Str *_t_Str_1790 = malloc(sizeof(Str));
    _t_Str_1790->c_str = _t_v_1789;
    _t_Str_1790->count = ln;
    _t_Str_1790->cap = CAP_VIEW;
    (void)_t_Str_1790;
    ;
    ;
    return _t_Str_1790;
}

Bool Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_1821 = 0;
    (void)_t_U32_1821;
    Bool _t_Bool_1822 = U32_eq(b->count, _t_U32_1821);
    (void)_t_Bool_1822;
    ;
    if (_t_Bool_1822) {
        Bool _t_Bool_1791 = 1;
        (void)_t_Bool_1791;
        ;
        return _t_Bool_1791;
    }
    ;
    Bool _t_Bool_1823 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_1823;
    if (_t_Bool_1823) {
        Bool _t_Bool_1792 = 0;
        (void)_t_Bool_1792;
        ;
        return _t_Bool_1792;
    }
    ;
    {
        U32 _t_U32_1818 = U32_sub(a->count, b->count);
        (void)_t_U32_1818;
        U32 _t_U32_1819 = 1;
        (void)_t_U32_1819;
        U32 _re_U32_1793 = U32_add(_t_U32_1818, _t_U32_1819);
        (void)_re_U32_1793;
        ;
        ;
        U32 _rc_U32_1793 = 0;
        (void)_rc_U32_1793;
        Bool _t_Bool_1820 = U32_lte(&_rc_U32_1793, &_re_U32_1793);
        (void)_t_Bool_1820;
        if (_t_Bool_1820) {
            while (1) {
                Bool _wcond_Bool_1794 = U32_lt(&_rc_U32_1793, &_re_U32_1793);
                (void)_wcond_Bool_1794;
                if (_wcond_Bool_1794) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1793);
                (void)i;
                U32_inc(&_rc_U32_1793);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1795 = b->count;
                    (void)_re_U32_1795;
                    U32 _rc_U32_1795 = 0;
                    (void)_rc_U32_1795;
                    Bool _t_Bool_1804 = U32_lte(&_rc_U32_1795, &_re_U32_1795);
                    (void)_t_Bool_1804;
                    if (_t_Bool_1804) {
                        while (1) {
                            Bool _wcond_Bool_1796 = U32_lt(&_rc_U32_1795, &_re_U32_1795);
                            (void)_wcond_Bool_1796;
                            if (_wcond_Bool_1796) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1795);
                            (void)j;
                            U32_inc(&_rc_U32_1795);
                            U32 _t_U32_1798 = U32_add(i, j);
                            (void)_t_U32_1798;
                            U8 *ac = Str_get(a, &_t_U32_1798);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_1799 = U8_neq(ac, bc);
                            (void)_t_Bool_1799;
                            ;
                            ;
                            if (_t_Bool_1799) {
                                Bool _t_Bool_1797 = 0;
                                (void)_t_Bool_1797;
                                found = _t_Bool_1797;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1800 = U32_gt(&_rc_U32_1795, &_re_U32_1795);
                            (void)_wcond_Bool_1800;
                            if (_wcond_Bool_1800) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1795);
                            (void)j;
                            U32_dec(&_rc_U32_1795);
                            U32 _t_U32_1802 = U32_add(i, j);
                            (void)_t_U32_1802;
                            U8 *ac = Str_get(a, &_t_U32_1802);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_1803 = U8_neq(ac, bc);
                            (void)_t_Bool_1803;
                            ;
                            ;
                            if (_t_Bool_1803) {
                                Bool _t_Bool_1801 = 0;
                                (void)_t_Bool_1801;
                                found = _t_Bool_1801;
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
                    Bool _t_Bool_1805 = 1;
                    (void)_t_Bool_1805;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1805;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1806 = U32_gt(&_rc_U32_1793, &_re_U32_1793);
                (void)_wcond_Bool_1806;
                if (_wcond_Bool_1806) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1793);
                (void)i;
                U32_dec(&_rc_U32_1793);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1807 = b->count;
                    (void)_re_U32_1807;
                    U32 _rc_U32_1807 = 0;
                    (void)_rc_U32_1807;
                    Bool _t_Bool_1816 = U32_lte(&_rc_U32_1807, &_re_U32_1807);
                    (void)_t_Bool_1816;
                    if (_t_Bool_1816) {
                        while (1) {
                            Bool _wcond_Bool_1808 = U32_lt(&_rc_U32_1807, &_re_U32_1807);
                            (void)_wcond_Bool_1808;
                            if (_wcond_Bool_1808) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1807);
                            (void)j;
                            U32_inc(&_rc_U32_1807);
                            U32 _t_U32_1810 = U32_add(i, j);
                            (void)_t_U32_1810;
                            U8 *ac = Str_get(a, &_t_U32_1810);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_1811 = U8_neq(ac, bc);
                            (void)_t_Bool_1811;
                            ;
                            ;
                            if (_t_Bool_1811) {
                                Bool _t_Bool_1809 = 0;
                                (void)_t_Bool_1809;
                                found = _t_Bool_1809;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1812 = U32_gt(&_rc_U32_1807, &_re_U32_1807);
                            (void)_wcond_Bool_1812;
                            if (_wcond_Bool_1812) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1807);
                            (void)j;
                            U32_dec(&_rc_U32_1807);
                            U32 _t_U32_1814 = U32_add(i, j);
                            (void)_t_U32_1814;
                            U8 *ac = Str_get(a, &_t_U32_1814);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_1815 = U8_neq(ac, bc);
                            (void)_t_Bool_1815;
                            ;
                            ;
                            if (_t_Bool_1815) {
                                Bool _t_Bool_1813 = 0;
                                (void)_t_Bool_1813;
                                found = _t_Bool_1813;
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
                    Bool _t_Bool_1817 = 1;
                    (void)_t_Bool_1817;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1817;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_1824 = 0;
    (void)_t_Bool_1824;
    return _t_Bool_1824;
}

Bool Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1834 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_1834;
    if (_t_Bool_1834) {
        Bool _t_Bool_1825 = 0;
        (void)_t_Bool_1825;
        ;
        return _t_Bool_1825;
    }
    ;
    {
        U32 _re_U32_1826 = b->count;
        (void)_re_U32_1826;
        U32 _rc_U32_1826 = 0;
        (void)_rc_U32_1826;
        Bool _t_Bool_1833 = U32_lte(&_rc_U32_1826, &_re_U32_1826);
        (void)_t_Bool_1833;
        if (_t_Bool_1833) {
            while (1) {
                Bool _wcond_Bool_1827 = U32_lt(&_rc_U32_1826, &_re_U32_1826);
                (void)_wcond_Bool_1827;
                if (_wcond_Bool_1827) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1826);
                (void)i;
                U32_inc(&_rc_U32_1826);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_1829 = U8_neq(ac, bc);
                (void)_t_Bool_1829;
                ;
                if (_t_Bool_1829) {
                    Bool _t_Bool_1828 = 0;
                    (void)_t_Bool_1828;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1828;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1830 = U32_gt(&_rc_U32_1826, &_re_U32_1826);
                (void)_wcond_Bool_1830;
                if (_wcond_Bool_1830) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1826);
                (void)i;
                U32_dec(&_rc_U32_1826);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_1832 = U8_neq(ac, bc);
                (void)_t_Bool_1832;
                ;
                if (_t_Bool_1832) {
                    Bool _t_Bool_1831 = 0;
                    (void)_t_Bool_1831;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1831;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_1835 = 1;
    (void)_t_Bool_1835;
    return _t_Bool_1835;
}

Bool Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1847 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_1847;
    if (_t_Bool_1847) {
        Bool _t_Bool_1836 = 0;
        (void)_t_Bool_1836;
        ;
        return _t_Bool_1836;
    }
    ;
    U32 offset = U32_sub(a->count, b->count);
    (void)offset;
    {
        U32 _re_U32_1837 = b->count;
        (void)_re_U32_1837;
        U32 _rc_U32_1837 = 0;
        (void)_rc_U32_1837;
        Bool _t_Bool_1846 = U32_lte(&_rc_U32_1837, &_re_U32_1837);
        (void)_t_Bool_1846;
        if (_t_Bool_1846) {
            while (1) {
                Bool _wcond_Bool_1838 = U32_lt(&_rc_U32_1837, &_re_U32_1837);
                (void)_wcond_Bool_1838;
                if (_wcond_Bool_1838) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1837);
                (void)i;
                U32_inc(&_rc_U32_1837);
                U32 _t_U32_1840 = U32_add(offset, i);
                (void)_t_U32_1840;
                U8 *ac = Str_get(a, &_t_U32_1840);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_1841 = U8_neq(ac, bc);
                (void)_t_Bool_1841;
                ;
                ;
                if (_t_Bool_1841) {
                    Bool _t_Bool_1839 = 0;
                    (void)_t_Bool_1839;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1839;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1842 = U32_gt(&_rc_U32_1837, &_re_U32_1837);
                (void)_wcond_Bool_1842;
                if (_wcond_Bool_1842) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1837);
                (void)i;
                U32_dec(&_rc_U32_1837);
                U32 _t_U32_1844 = U32_add(offset, i);
                (void)_t_U32_1844;
                U8 *ac = Str_get(a, &_t_U32_1844);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_1845 = U8_neq(ac, bc);
                (void)_t_Bool_1845;
                ;
                ;
                if (_t_Bool_1845) {
                    Bool _t_Bool_1843 = 0;
                    (void)_t_Bool_1843;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1843;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    Bool _t_Bool_1848 = 1;
    (void)_t_Bool_1848;
    return _t_Bool_1848;
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_1849 = 0;
    (void)_t_U32_1849;
    Bool _t_Bool_1850 = U32_eq(self->count, _t_U32_1849);
    (void)_t_Bool_1850;
    ;
    return _t_Bool_1850;
}

I64 Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_1885 = 0;
    (void)_t_U32_1885;
    Bool _t_Bool_1886 = U32_eq(needle->count, _t_U32_1885);
    (void)_t_Bool_1886;
    ;
    if (_t_Bool_1886) {
        I64 _t_I64_1851 = 0;
        (void)_t_I64_1851;
        I64 _t_I64_1852 = 1;
        (void)_t_I64_1852;
        I64 _t_I64_1853 = I64_sub(_t_I64_1851, _t_I64_1852);
        (void)_t_I64_1853;
        ;
        ;
        ;
        return _t_I64_1853;
    }
    ;
    Bool _t_Bool_1887 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_1887;
    if (_t_Bool_1887) {
        I64 _t_I64_1854 = 0;
        (void)_t_I64_1854;
        I64 _t_I64_1855 = 1;
        (void)_t_I64_1855;
        I64 _t_I64_1856 = I64_sub(_t_I64_1854, _t_I64_1855);
        (void)_t_I64_1856;
        ;
        ;
        ;
        return _t_I64_1856;
    }
    ;
    {
        U32 _t_U32_1882 = U32_sub(self->count, needle->count);
        (void)_t_U32_1882;
        U32 _t_U32_1883 = 1;
        (void)_t_U32_1883;
        U32 _re_U32_1857 = U32_add(_t_U32_1882, _t_U32_1883);
        (void)_re_U32_1857;
        ;
        ;
        U32 _rc_U32_1857 = 0;
        (void)_rc_U32_1857;
        Bool _t_Bool_1884 = U32_lte(&_rc_U32_1857, &_re_U32_1857);
        (void)_t_Bool_1884;
        if (_t_Bool_1884) {
            while (1) {
                Bool _wcond_Bool_1858 = U32_lt(&_rc_U32_1857, &_re_U32_1857);
                (void)_wcond_Bool_1858;
                if (_wcond_Bool_1858) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1857);
                (void)i;
                U32_inc(&_rc_U32_1857);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1859 = needle->count;
                    (void)_re_U32_1859;
                    U32 _rc_U32_1859 = 0;
                    (void)_rc_U32_1859;
                    Bool _t_Bool_1868 = U32_lte(&_rc_U32_1859, &_re_U32_1859);
                    (void)_t_Bool_1868;
                    if (_t_Bool_1868) {
                        while (1) {
                            Bool _wcond_Bool_1860 = U32_lt(&_rc_U32_1859, &_re_U32_1859);
                            (void)_wcond_Bool_1860;
                            if (_wcond_Bool_1860) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1859);
                            (void)j;
                            U32_inc(&_rc_U32_1859);
                            U32 _t_U32_1862 = U32_add(i, j);
                            (void)_t_U32_1862;
                            U8 *ac = Str_get(self, &_t_U32_1862);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1863 = U8_neq(ac, bc);
                            (void)_t_Bool_1863;
                            ;
                            ;
                            if (_t_Bool_1863) {
                                Bool _t_Bool_1861 = 0;
                                (void)_t_Bool_1861;
                                found = _t_Bool_1861;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1864 = U32_gt(&_rc_U32_1859, &_re_U32_1859);
                            (void)_wcond_Bool_1864;
                            if (_wcond_Bool_1864) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1859);
                            (void)j;
                            U32_dec(&_rc_U32_1859);
                            U32 _t_U32_1866 = U32_add(i, j);
                            (void)_t_U32_1866;
                            U8 *ac = Str_get(self, &_t_U32_1866);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1867 = U8_neq(ac, bc);
                            (void)_t_Bool_1867;
                            ;
                            ;
                            if (_t_Bool_1867) {
                                Bool _t_Bool_1865 = 0;
                                (void)_t_Bool_1865;
                                found = _t_Bool_1865;
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
                    I64 _t_I64_1869 = U32_to_i64(i);
                    (void)_t_I64_1869;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_1869;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1870 = U32_gt(&_rc_U32_1857, &_re_U32_1857);
                (void)_wcond_Bool_1870;
                if (_wcond_Bool_1870) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1857);
                (void)i;
                U32_dec(&_rc_U32_1857);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1871 = needle->count;
                    (void)_re_U32_1871;
                    U32 _rc_U32_1871 = 0;
                    (void)_rc_U32_1871;
                    Bool _t_Bool_1880 = U32_lte(&_rc_U32_1871, &_re_U32_1871);
                    (void)_t_Bool_1880;
                    if (_t_Bool_1880) {
                        while (1) {
                            Bool _wcond_Bool_1872 = U32_lt(&_rc_U32_1871, &_re_U32_1871);
                            (void)_wcond_Bool_1872;
                            if (_wcond_Bool_1872) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1871);
                            (void)j;
                            U32_inc(&_rc_U32_1871);
                            U32 _t_U32_1874 = U32_add(i, j);
                            (void)_t_U32_1874;
                            U8 *ac = Str_get(self, &_t_U32_1874);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1875 = U8_neq(ac, bc);
                            (void)_t_Bool_1875;
                            ;
                            ;
                            if (_t_Bool_1875) {
                                Bool _t_Bool_1873 = 0;
                                (void)_t_Bool_1873;
                                found = _t_Bool_1873;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1876 = U32_gt(&_rc_U32_1871, &_re_U32_1871);
                            (void)_wcond_Bool_1876;
                            if (_wcond_Bool_1876) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1871);
                            (void)j;
                            U32_dec(&_rc_U32_1871);
                            U32 _t_U32_1878 = U32_add(i, j);
                            (void)_t_U32_1878;
                            U8 *ac = Str_get(self, &_t_U32_1878);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1879 = U8_neq(ac, bc);
                            (void)_t_Bool_1879;
                            ;
                            ;
                            if (_t_Bool_1879) {
                                Bool _t_Bool_1877 = 0;
                                (void)_t_Bool_1877;
                                found = _t_Bool_1877;
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
                    I64 _t_I64_1881 = U32_to_i64(i);
                    (void)_t_I64_1881;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_1881;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    I64 _t_I64_1888 = 0;
    (void)_t_I64_1888;
    I64 _t_I64_1889 = 1;
    (void)_t_I64_1889;
    I64 _t_I64_1890 = I64_sub(_t_I64_1888, _t_I64_1889);
    (void)_t_I64_1890;
    ;
    ;
    return _t_I64_1890;
}

I64 Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_1925 = 0;
    (void)_t_U32_1925;
    Bool _t_Bool_1926 = U32_eq(needle->count, _t_U32_1925);
    (void)_t_Bool_1926;
    ;
    if (_t_Bool_1926) {
        I64 _t_I64_1891 = 0;
        (void)_t_I64_1891;
        I64 _t_I64_1892 = 1;
        (void)_t_I64_1892;
        I64 _t_I64_1893 = I64_sub(_t_I64_1891, _t_I64_1892);
        (void)_t_I64_1893;
        ;
        ;
        ;
        return _t_I64_1893;
    }
    ;
    Bool _t_Bool_1927 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_1927;
    if (_t_Bool_1927) {
        I64 _t_I64_1894 = 0;
        (void)_t_I64_1894;
        I64 _t_I64_1895 = 1;
        (void)_t_I64_1895;
        I64 _t_I64_1896 = I64_sub(_t_I64_1894, _t_I64_1895);
        (void)_t_I64_1896;
        ;
        ;
        ;
        return _t_I64_1896;
    }
    ;
    I64 _t_I64_1928 = 0;
    (void)_t_I64_1928;
    I64 _t_I64_1929 = 1;
    (void)_t_I64_1929;
    I64 last = I64_sub(_t_I64_1928, _t_I64_1929);
    (void)last;
    ;
    ;
    {
        U32 _t_U32_1922 = U32_sub(self->count, needle->count);
        (void)_t_U32_1922;
        U32 _t_U32_1923 = 1;
        (void)_t_U32_1923;
        U32 _re_U32_1897 = U32_add(_t_U32_1922, _t_U32_1923);
        (void)_re_U32_1897;
        ;
        ;
        U32 _rc_U32_1897 = 0;
        (void)_rc_U32_1897;
        Bool _t_Bool_1924 = U32_lte(&_rc_U32_1897, &_re_U32_1897);
        (void)_t_Bool_1924;
        if (_t_Bool_1924) {
            while (1) {
                Bool _wcond_Bool_1898 = U32_lt(&_rc_U32_1897, &_re_U32_1897);
                (void)_wcond_Bool_1898;
                if (_wcond_Bool_1898) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1897);
                (void)i;
                U32_inc(&_rc_U32_1897);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1899 = needle->count;
                    (void)_re_U32_1899;
                    U32 _rc_U32_1899 = 0;
                    (void)_rc_U32_1899;
                    Bool _t_Bool_1908 = U32_lte(&_rc_U32_1899, &_re_U32_1899);
                    (void)_t_Bool_1908;
                    if (_t_Bool_1908) {
                        while (1) {
                            Bool _wcond_Bool_1900 = U32_lt(&_rc_U32_1899, &_re_U32_1899);
                            (void)_wcond_Bool_1900;
                            if (_wcond_Bool_1900) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1899);
                            (void)j;
                            U32_inc(&_rc_U32_1899);
                            U32 _t_U32_1902 = U32_add(i, j);
                            (void)_t_U32_1902;
                            U8 *ac = Str_get(self, &_t_U32_1902);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1903 = U8_neq(ac, bc);
                            (void)_t_Bool_1903;
                            ;
                            ;
                            if (_t_Bool_1903) {
                                Bool _t_Bool_1901 = 0;
                                (void)_t_Bool_1901;
                                found = _t_Bool_1901;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1904 = U32_gt(&_rc_U32_1899, &_re_U32_1899);
                            (void)_wcond_Bool_1904;
                            if (_wcond_Bool_1904) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1899);
                            (void)j;
                            U32_dec(&_rc_U32_1899);
                            U32 _t_U32_1906 = U32_add(i, j);
                            (void)_t_U32_1906;
                            U8 *ac = Str_get(self, &_t_U32_1906);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1907 = U8_neq(ac, bc);
                            (void)_t_Bool_1907;
                            ;
                            ;
                            if (_t_Bool_1907) {
                                Bool _t_Bool_1905 = 0;
                                (void)_t_Bool_1905;
                                found = _t_Bool_1905;
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
                    I64 _t_I64_1909 = U32_to_i64(i);
                    (void)_t_I64_1909;
                    last = _t_I64_1909;
                    ;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1910 = U32_gt(&_rc_U32_1897, &_re_U32_1897);
                (void)_wcond_Bool_1910;
                if (_wcond_Bool_1910) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1897);
                (void)i;
                U32_dec(&_rc_U32_1897);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1911 = needle->count;
                    (void)_re_U32_1911;
                    U32 _rc_U32_1911 = 0;
                    (void)_rc_U32_1911;
                    Bool _t_Bool_1920 = U32_lte(&_rc_U32_1911, &_re_U32_1911);
                    (void)_t_Bool_1920;
                    if (_t_Bool_1920) {
                        while (1) {
                            Bool _wcond_Bool_1912 = U32_lt(&_rc_U32_1911, &_re_U32_1911);
                            (void)_wcond_Bool_1912;
                            if (_wcond_Bool_1912) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1911);
                            (void)j;
                            U32_inc(&_rc_U32_1911);
                            U32 _t_U32_1914 = U32_add(i, j);
                            (void)_t_U32_1914;
                            U8 *ac = Str_get(self, &_t_U32_1914);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1915 = U8_neq(ac, bc);
                            (void)_t_Bool_1915;
                            ;
                            ;
                            if (_t_Bool_1915) {
                                Bool _t_Bool_1913 = 0;
                                (void)_t_Bool_1913;
                                found = _t_Bool_1913;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1916 = U32_gt(&_rc_U32_1911, &_re_U32_1911);
                            (void)_wcond_Bool_1916;
                            if (_wcond_Bool_1916) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1911);
                            (void)j;
                            U32_dec(&_rc_U32_1911);
                            U32 _t_U32_1918 = U32_add(i, j);
                            (void)_t_U32_1918;
                            U8 *ac = Str_get(self, &_t_U32_1918);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1919 = U8_neq(ac, bc);
                            (void)_t_Bool_1919;
                            ;
                            ;
                            if (_t_Bool_1919) {
                                Bool _t_Bool_1917 = 0;
                                (void)_t_Bool_1917;
                                found = _t_Bool_1917;
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
                    I64 _t_I64_1921 = U32_to_i64(i);
                    (void)_t_I64_1921;
                    last = _t_I64_1921;
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
    U32 _t_U32_1955 = 0;
    (void)_t_U32_1955;
    Bool _t_Bool_1956 = U32_eq(from->count, _t_U32_1955);
    (void)_t_Bool_1956;
    ;
    if (_t_Bool_1956) {
        Str *_t_Str_1930 = Str_clone(self);
        (void)_t_Str_1930;
        ;
        return _t_Str_1930;
    }
    ;
    U32 matches = 0;
    (void)matches;
    U32 start = 0;
    (void)start;
    while (1) {
        U32 _t_U32_1932 = U32_sub(self->count, from->count);
        (void)_t_U32_1932;
        Bool _wcond_Bool_1931 = U32_lte(&start, &_t_U32_1932);
        (void)_wcond_Bool_1931;
        ;
        if (_wcond_Bool_1931) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_1933 = U32_sub(self->count, start);
        (void)_t_U32_1933;
        Str *rest = Str_substr(self, &start, &_t_U32_1933);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_1934 = 0;
        (void)_t_I64_1934;
        I64 _t_I64_1935 = 1;
        (void)_t_I64_1935;
        I64 _t_I64_1936 = I64_sub(_t_I64_1934, _t_I64_1935);
        (void)_t_I64_1936;
        ;
        ;
        Bool _t_Bool_1937 = I64_eq(pos, _t_I64_1936);
        (void)_t_Bool_1937;
        ;
        if (_t_Bool_1937) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        U32 _t_U32_1938 = U32_add(start, pos_u);
        (void)_t_U32_1938;
        ;
        U32 _t_U32_1939 = U32_add(_t_U32_1938, from->count);
        (void)_t_U32_1939;
        ;
        start = _t_U32_1939;
        ;
        U32 _t_U32_1940 = 1;
        (void)_t_U32_1940;
        U32 _t_U32_1941 = U32_add(matches, _t_U32_1940);
        (void)_t_U32_1941;
        ;
        matches = _t_U32_1941;
        ;
    }
    U32 _t_U32_1957 = 0;
    (void)_t_U32_1957;
    Bool _t_Bool_1958 = U32_eq(matches, _t_U32_1957);
    (void)_t_Bool_1958;
    ;
    if (_t_Bool_1958) {
        Str *_t_Str_1942 = Str_clone(self);
        (void)_t_Str_1942;
        ;
        ;
        ;
        return _t_Str_1942;
    }
    ;
    U32 removed = U32_mul(matches, from->count);
    (void)removed;
    U32 added = U32_mul(matches, to->count);
    (void)added;
    ;
    U32 _t_U32_1959 = U32_sub(self->count, removed);
    (void)_t_U32_1959;
    ;
    U32 _t_U32_1960 = U32_add(_t_U32_1959, added);
    (void)_t_U32_1960;
    ;
    ;
    Str *out = Str_with_capacity(&_t_U32_1960);
    (void)out;
    ;
    U32 _t_U32_1961 = 0;
    (void)_t_U32_1961;
    start = _t_U32_1961;
    ;
    while (1) {
        U32 _t_U32_1944 = U32_sub(self->count, from->count);
        (void)_t_U32_1944;
        Bool _wcond_Bool_1943 = U32_lte(&start, &_t_U32_1944);
        (void)_wcond_Bool_1943;
        ;
        if (_wcond_Bool_1943) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_1945 = U32_sub(self->count, start);
        (void)_t_U32_1945;
        Str *rest = Str_substr(self, &start, &_t_U32_1945);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_1946 = 0;
        (void)_t_I64_1946;
        I64 _t_I64_1947 = 1;
        (void)_t_I64_1947;
        I64 _t_I64_1948 = I64_sub(_t_I64_1946, _t_I64_1947);
        (void)_t_I64_1948;
        ;
        ;
        Bool _t_Bool_1949 = I64_eq(pos, _t_I64_1948);
        (void)_t_Bool_1949;
        ;
        if (_t_Bool_1949) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        Str *_t_Str_1950 = Str_substr(self, &start, &pos_u);
        (void)_t_Str_1950;
        Str_push_str(out, _t_Str_1950);
        Str_delete(_t_Str_1950, &(Bool){1});
        Str_push_str(out, to);
        U32 _t_U32_1951 = U32_add(start, pos_u);
        (void)_t_U32_1951;
        ;
        U32 _t_U32_1952 = U32_add(_t_U32_1951, from->count);
        (void)_t_U32_1952;
        ;
        start = _t_U32_1952;
        ;
    }
    Bool _t_Bool_1962 = U32_lt(&start, &self->count);
    (void)_t_Bool_1962;
    if (_t_Bool_1962) {
        U32 _t_U32_1953 = U32_sub(self->count, start);
        (void)_t_U32_1953;
        Str *_t_Str_1954 = Str_substr(self, &start, &_t_U32_1953);
        (void)_t_Str_1954;
        ;
        Str_push_str(out, _t_Str_1954);
        Str_delete(_t_Str_1954, &(Bool){1});
    }
    ;
    ;
    return out;
}

Str * Str_get_char(Str * self, U32 * i) {
    (void)self;
    (void)i;
    U32 _t_U32_1963 = 1;
    (void)_t_U32_1963;
    Str *_t_Str_1964 = Str_substr(self, i, &_t_U32_1963);
    (void)_t_Str_1964;
    ;
    return _t_Str_1964;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t_Bool_1967 = Str_starts_with(self, prefix);
    (void)_t_Bool_1967;
    if (_t_Bool_1967) {
        U32 _t_U32_1965 = U32_sub(self->count, prefix->count);
        (void)_t_U32_1965;
        Str *_t_Str_1966 = Str_substr(self, &prefix->count, &_t_U32_1965);
        (void)_t_Str_1966;
        ;
        ;
        return _t_Str_1966;
    }
    ;
    Str *_t_Str_1968 = Str_clone(self);
    (void)_t_Str_1968;
    return _t_Str_1968;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t_Bool_1972 = Str_ends_with(self, suffix);
    (void)_t_Bool_1972;
    if (_t_Bool_1972) {
        U32 _t_U32_1969 = 0;
        (void)_t_U32_1969;
        U32 _t_U32_1970 = U32_sub(self->count, suffix->count);
        (void)_t_U32_1970;
        Str *_t_Str_1971 = Str_substr(self, &_t_U32_1969, &_t_U32_1970);
        (void)_t_Str_1971;
        ;
        ;
        ;
        return _t_Str_1971;
    }
    ;
    Str *_t_Str_1973 = Str_clone(self);
    (void)_t_Str_1973;
    return _t_Str_1973;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t_U64_1974 = 2;
    (void)_t_U64_1974;
    void * buf = malloc(_t_U64_1974);
    (void)buf;
    ;
    U64 _t_U64_1975 = 1;
    (void)_t_U64_1975;
    memcpy(buf, byte, _t_U64_1975);
    ;
    U64 _t_U64_1976 = 1;
    (void)_t_U64_1976;
    void *_t_v_1977 = ptr_add(buf, _t_U64_1976);
    (void)_t_v_1977;
    I32 _t_I32_1978 = 0;
    (void)_t_I32_1978;
    U64 _t_U64_1979 = 1;
    (void)_t_U64_1979;
    memset(_t_v_1977, _t_I32_1978, _t_U64_1979);
    ;
    ;
    ;
    I64 _t_I64_1980 = 1;
    (void)_t_I64_1980;
    I64 _t_I64_1981 = 1;
    (void)_t_I64_1981;
    Str *_t_Str_1982 = malloc(sizeof(Str));
    _t_Str_1982->c_str = buf;
    _t_Str_1982->count = _t_I64_1980;
    _t_Str_1982->cap = _t_I64_1981;
    (void)_t_Str_1982;
    ;
    ;
    return _t_Str_1982;
}

I64 Str_to_i64(Str * self) {
    (void)self;
    U32 _t_U32_2039 = 0;
    (void)_t_U32_2039;
    Bool _t_Bool_2040 = U32_eq(self->count, _t_U32_2039);
    (void)_t_Bool_2040;
    ;
    if (_t_Bool_2040) {
        Str *_t_Str_1983 = Str_lit("Str", 3ULL);
        (void)_t_Str_1983;
        U32 _t_U32_1984 = 1;
        (void)_t_U32_1984;
        Array *_va_Array_69 = Array_new(_t_Str_1983, &_t_U32_1984);
        (void)_va_Array_69;
        Str_delete(_t_Str_1983, &(Bool){1});
        ;
        U32 _t_U32_1985 = 0;
        (void)_t_U32_1985;
        Str *_t_Str_1986 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t_Str_1986;
        Array_set(_va_Array_69, &_t_U32_1985, _t_Str_1986);
        ;
        Str *_t_Str_1987 = Str_lit("./src/core/str.til:266:37", 25ULL);
        (void)_t_Str_1987;
        panic(_t_Str_1987, _va_Array_69);
        Str_delete(_t_Str_1987, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_2041 = 0;
    (void)_t_U32_2041;
    U8 *first = Str_get(self, &_t_U32_2041);
    (void)first;
    U8 _t_U8_2042 = 45;
    (void)_t_U8_2042;
    Bool _t_Bool_2043 = U8_eq(DEREF(first), _t_U8_2042);
    (void)_t_Bool_2043;
    ;
    ;
    if (_t_Bool_2043) {
        Bool _t_Bool_1988 = 1;
        (void)_t_Bool_1988;
        neg = _t_Bool_1988;
        ;
        U32 _t_U32_1989 = 1;
        (void)_t_U32_1989;
        start = _t_U32_1989;
        ;
    }
    ;
    Bool _t_Bool_2044 = U32_eq(start, self->count);
    (void)_t_Bool_2044;
    if (_t_Bool_2044) {
        Str *_t_Str_1990 = Str_lit("Str", 3ULL);
        (void)_t_Str_1990;
        U32 _t_U32_1991 = 1;
        (void)_t_U32_1991;
        Array *_va_Array_70 = Array_new(_t_Str_1990, &_t_U32_1991);
        (void)_va_Array_70;
        Str_delete(_t_Str_1990, &(Bool){1});
        ;
        U32 _t_U32_1992 = 0;
        (void)_t_U32_1992;
        Str *_t_Str_1993 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t_Str_1993;
        Array_set(_va_Array_70, &_t_U32_1992, _t_Str_1993);
        ;
        Str *_t_Str_1994 = Str_lit("./src/core/str.til:275:41", 25ULL);
        (void)_t_Str_1994;
        panic(_t_Str_1994, _va_Array_70);
        Str_delete(_t_Str_1994, &(Bool){1});
    }
    ;
    {
        U32 _re_U32_1995 = self->count;
        (void)_re_U32_1995;
        U32 _rc_U32_1995 = U32_clone(&start);
        (void)_rc_U32_1995;
        Bool _t_Bool_2036 = U32_lte(&_rc_U32_1995, &_re_U32_1995);
        (void)_t_Bool_2036;
        if (_t_Bool_2036) {
            while (1) {
                Bool _wcond_Bool_1996 = U32_lt(&_rc_U32_1995, &_re_U32_1995);
                (void)_wcond_Bool_1996;
                if (_wcond_Bool_1996) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1995);
                (void)i;
                U32_inc(&_rc_U32_1995);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_2006 = U8_to_i64(DEREF(ch));
                (void)_t_I64_2006;
                ;
                I64 _t_I64_2007 = 48;
                (void)_t_I64_2007;
                I64 d = I64_sub(_t_I64_2006, _t_I64_2007);
                (void)d;
                ;
                ;
                I64 _t_I64_2008 = 0;
                (void)_t_I64_2008;
                I64 _t_I64_2009 = 9;
                (void)_t_I64_2009;
                Bool _t_Bool_2010 = I64_lt(&d, &_t_I64_2008);
                (void)_t_Bool_2010;
                ;
                Bool _t_Bool_2011 = I64_gt(&d, &_t_I64_2009);
                (void)_t_Bool_2011;
                ;
                Bool _t_Bool_2012 = or(_t_Bool_2010, _t_Bool_2011);
                (void)_t_Bool_2012;
                ;
                ;
                if (_t_Bool_2012) {
                    Str *_t_Str_1997 = Str_lit("Str", 3ULL);
                    (void)_t_Str_1997;
                    U32 _t_U32_1998 = 3;
                    (void)_t_U32_1998;
                    Array *_va_Array_71 = Array_new(_t_Str_1997, &_t_U32_1998);
                    (void)_va_Array_71;
                    Str_delete(_t_Str_1997, &(Bool){1});
                    ;
                    U32 _t_U32_1999 = 0;
                    (void)_t_U32_1999;
                    Str *_t_Str_2000 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_2000;
                    Array_set(_va_Array_71, &_t_U32_1999, _t_Str_2000);
                    ;
                    U32 _t_U32_2001 = 1;
                    (void)_t_U32_2001;
                    Str *_t_Str_2002 = Str_clone(self);
                    (void)_t_Str_2002;
                    Array_set(_va_Array_71, &_t_U32_2001, _t_Str_2002);
                    ;
                    U32 _t_U32_2003 = 2;
                    (void)_t_U32_2003;
                    Str *_t_Str_2004 = Str_lit("'", 1ULL);
                    (void)_t_Str_2004;
                    Array_set(_va_Array_71, &_t_U32_2003, _t_Str_2004);
                    ;
                    Str *_t_Str_2005 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_2005;
                    panic(_t_Str_2005, _va_Array_71);
                    Str_delete(_t_Str_2005, &(Bool){1});
                }
                ;
                I64 _t_I64_2013 = 10;
                (void)_t_I64_2013;
                I64 _t_I64_2014 = I64_mul(result, _t_I64_2013);
                (void)_t_I64_2014;
                ;
                I64 _t_I64_2015 = I64_add(_t_I64_2014, d);
                (void)_t_I64_2015;
                ;
                ;
                result = _t_I64_2015;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2016 = U32_gt(&_rc_U32_1995, &_re_U32_1995);
                (void)_wcond_Bool_2016;
                if (_wcond_Bool_2016) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1995);
                (void)i;
                U32_dec(&_rc_U32_1995);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_2026 = U8_to_i64(DEREF(ch));
                (void)_t_I64_2026;
                ;
                I64 _t_I64_2027 = 48;
                (void)_t_I64_2027;
                I64 d = I64_sub(_t_I64_2026, _t_I64_2027);
                (void)d;
                ;
                ;
                I64 _t_I64_2028 = 0;
                (void)_t_I64_2028;
                I64 _t_I64_2029 = 9;
                (void)_t_I64_2029;
                Bool _t_Bool_2030 = I64_lt(&d, &_t_I64_2028);
                (void)_t_Bool_2030;
                ;
                Bool _t_Bool_2031 = I64_gt(&d, &_t_I64_2029);
                (void)_t_Bool_2031;
                ;
                Bool _t_Bool_2032 = or(_t_Bool_2030, _t_Bool_2031);
                (void)_t_Bool_2032;
                ;
                ;
                if (_t_Bool_2032) {
                    Str *_t_Str_2017 = Str_lit("Str", 3ULL);
                    (void)_t_Str_2017;
                    U32 _t_U32_2018 = 3;
                    (void)_t_U32_2018;
                    Array *_va_Array_72 = Array_new(_t_Str_2017, &_t_U32_2018);
                    (void)_va_Array_72;
                    Str_delete(_t_Str_2017, &(Bool){1});
                    ;
                    U32 _t_U32_2019 = 0;
                    (void)_t_U32_2019;
                    Str *_t_Str_2020 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_2020;
                    Array_set(_va_Array_72, &_t_U32_2019, _t_Str_2020);
                    ;
                    U32 _t_U32_2021 = 1;
                    (void)_t_U32_2021;
                    Str *_t_Str_2022 = Str_clone(self);
                    (void)_t_Str_2022;
                    Array_set(_va_Array_72, &_t_U32_2021, _t_Str_2022);
                    ;
                    U32 _t_U32_2023 = 2;
                    (void)_t_U32_2023;
                    Str *_t_Str_2024 = Str_lit("'", 1ULL);
                    (void)_t_Str_2024;
                    Array_set(_va_Array_72, &_t_U32_2023, _t_Str_2024);
                    ;
                    Str *_t_Str_2025 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_2025;
                    panic(_t_Str_2025, _va_Array_72);
                    Str_delete(_t_Str_2025, &(Bool){1});
                }
                ;
                I64 _t_I64_2033 = 10;
                (void)_t_I64_2033;
                I64 _t_I64_2034 = I64_mul(result, _t_I64_2033);
                (void)_t_I64_2034;
                ;
                I64 _t_I64_2035 = I64_add(_t_I64_2034, d);
                (void)_t_I64_2035;
                ;
                ;
                result = _t_I64_2035;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    if (neg) {
        I64 _t_I64_2037 = 0;
        (void)_t_I64_2037;
        I64 _t_I64_2038 = I64_sub(_t_I64_2037, result);
        (void)_t_I64_2038;
        ;
        ;
        ;
        return _t_I64_2038;
    }
    ;
    return result;
}

U8 Str_to_u8(Str * self) {
    (void)self;
    I64 _t_I64_2045 = Str_to_i64(self);
    (void)_t_I64_2045;
    U8 _t_U8_2046 = I64_to_u8(_t_I64_2045);
    (void)_t_U8_2046;
    ;
    return _t_U8_2046;
}

I32 Str_to_i32(Str * self) {
    (void)self;
    I64 _t_I64_2047 = Str_to_i64(self);
    (void)_t_I64_2047;
    I32 _t_I32_2048 = I64_to_i32(_t_I64_2047);
    (void)_t_I32_2048;
    ;
    return _t_I32_2048;
}

F32 Str_to_f32(Str * self) {
    (void)self;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_2074 = Str_len(self);
    (void)_t_U32_2074;
    U32 _t_U32_2075 = 0;
    (void)_t_U32_2075;
    U32 _t_U32_2076 = 0;
    (void)_t_U32_2076;
    U8 *_t_U8_2077 = Str_get(self, &_t_U32_2076);
    (void)_t_U8_2077;
    U8 _t_U8_2078 = 45;
    (void)_t_U8_2078;
    Bool _t_Bool_2079 = U32_gt(&_t_U32_2074, &_t_U32_2075);
    (void)_t_Bool_2079;
    ;
    ;
    Bool _t_Bool_2080 = U8_eq(DEREF(_t_U8_2077), _t_U8_2078);
    (void)_t_Bool_2080;
    ;
    ;
    Bool _t_Bool_2081 = and(_t_Bool_2079, _t_Bool_2080);
    (void)_t_Bool_2081;
    ;
    ;
    if (_t_Bool_2081) {
        Bool _t_Bool_2049 = 1;
        (void)_t_Bool_2049;
        neg = _t_Bool_2049;
        ;
        U32 _t_U32_2050 = 1;
        (void)_t_U32_2050;
        start = _t_U32_2050;
        ;
    }
    ;
    U32 _t_U32_2082 = Str_len(self);
    (void)_t_U32_2082;
    U32 _t_U32_2083 = U32_sub(_t_U32_2082, start);
    (void)_t_U32_2083;
    ;
    Str *rest = Str_substr(self, &start, &_t_U32_2083);
    (void)rest;
    ;
    ;
    Str *_t_Str_2084 = Str_lit(".", 1ULL);
    (void)_t_Str_2084;
    I64 dot = Str_find(rest, _t_Str_2084);
    (void)dot;
    Str_delete(_t_Str_2084, &(Bool){1});
    I64 _t_I64_2085 = 0;
    (void)_t_I64_2085;
    I64 _t_I64_2086 = 1;
    (void)_t_I64_2086;
    I64 _t_I64_2087 = I64_sub(_t_I64_2085, _t_I64_2086);
    (void)_t_I64_2087;
    ;
    ;
    Bool _t_Bool_2088 = I64_eq(dot, _t_I64_2087);
    (void)_t_Bool_2088;
    ;
    if (_t_Bool_2088) {
        I64 _t_I64_2054 = Str_to_i64(rest);
        (void)_t_I64_2054;
        F32 out = I64_to_f32(_t_I64_2054);
        (void)out;
        ;
        if (neg) {
            I64 _t_I64_2051 = 0;
            (void)_t_I64_2051;
            F32 _t_F32_2052 = I64_to_f32(_t_I64_2051);
            (void)_t_F32_2052;
            ;
            F32 _t_F32_2053 = F32_sub(_t_F32_2052, out);
            (void)_t_F32_2053;
            ;
            ;
            ;
            ;
            ;
            Str_delete(rest, &(Bool){1});
            return _t_F32_2053;
        }
        ;
        ;
        ;
        Str_delete(rest, &(Bool){1});
        return out;
    }
    ;
    U32 _t_U32_2089 = 0;
    (void)_t_U32_2089;
    U32 _t_U32_2090 = I64_to_usize(dot);
    (void)_t_U32_2090;
    Str *int_part = Str_substr(rest, &_t_U32_2089, &_t_U32_2090);
    (void)int_part;
    ;
    ;
    U32 _t_U32_2091 = I64_to_usize(dot);
    (void)_t_U32_2091;
    U32 _t_U32_2092 = 1;
    (void)_t_U32_2092;
    U32 _t_U32_2093 = I64_to_usize(dot);
    (void)_t_U32_2093;
    ;
    U32 _t_U32_2094 = 1;
    (void)_t_U32_2094;
    U32 _t_U32_2095 = Str_len(rest);
    (void)_t_U32_2095;
    U32 _t_U32_2096 = U32_add(_t_U32_2093, _t_U32_2094);
    (void)_t_U32_2096;
    ;
    ;
    U32 _t_U32_2097 = U32_add(_t_U32_2091, _t_U32_2092);
    (void)_t_U32_2097;
    ;
    ;
    U32 _t_U32_2098 = U32_sub(_t_U32_2095, _t_U32_2096);
    (void)_t_U32_2098;
    ;
    ;
    Str *frac_part = Str_substr(rest, &_t_U32_2097, &_t_U32_2098);
    (void)frac_part;
    ;
    ;
    Str_delete(rest, &(Bool){1});
    I64 _t_I64_2099 = 0;
    (void)_t_I64_2099;
    F32 out = I64_to_f32(_t_I64_2099);
    (void)out;
    ;
    U32 _t_U32_2100 = Str_len(int_part);
    (void)_t_U32_2100;
    U32 _t_U32_2101 = 0;
    (void)_t_U32_2101;
    Bool _t_Bool_2102 = U32_gt(&_t_U32_2100, &_t_U32_2101);
    (void)_t_Bool_2102;
    ;
    ;
    if (_t_Bool_2102) {
        I64 _t_I64_2055 = Str_to_i64(int_part);
        (void)_t_I64_2055;
        F32 _t_F32_2056 = I64_to_f32(_t_I64_2055);
        (void)_t_F32_2056;
        ;
        out = _t_F32_2056;
        ;
    }
    ;
    Str_delete(int_part, &(Bool){1});
    U32 _t_U32_2103 = Str_len(frac_part);
    (void)_t_U32_2103;
    U32 _t_U32_2104 = 0;
    (void)_t_U32_2104;
    Bool _t_Bool_2105 = U32_gt(&_t_U32_2103, &_t_U32_2104);
    (void)_t_Bool_2105;
    ;
    ;
    if (_t_Bool_2105) {
        I64 _t_I64_2067 = Str_to_i64(frac_part);
        (void)_t_I64_2067;
        F32 frac = I64_to_f32(_t_I64_2067);
        (void)frac;
        ;
        I64 _t_I64_2068 = 1;
        (void)_t_I64_2068;
        F32 scale = I64_to_f32(_t_I64_2068);
        (void)scale;
        ;
        {
            U32 _re_U32_2057 = Str_len(frac_part);
            (void)_re_U32_2057;
            U32 _rc_U32_2057 = 0;
            (void)_rc_U32_2057;
            Bool _t_Bool_2066 = U32_lte(&_rc_U32_2057, &_re_U32_2057);
            (void)_t_Bool_2066;
            if (_t_Bool_2066) {
                while (1) {
                    Bool _wcond_Bool_2058 = U32_lt(&_rc_U32_2057, &_re_U32_2057);
                    (void)_wcond_Bool_2058;
                    if (_wcond_Bool_2058) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_2057);
                    (void)_;
                    ;
                    U32_inc(&_rc_U32_2057);
                    I64 _t_I64_2059 = 10;
                    (void)_t_I64_2059;
                    F32 _t_F32_2060 = I64_to_f32(_t_I64_2059);
                    (void)_t_F32_2060;
                    ;
                    F32 _t_F32_2061 = F32_mul(scale, _t_F32_2060);
                    (void)_t_F32_2061;
                    ;
                    scale = _t_F32_2061;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_2062 = U32_gt(&_rc_U32_2057, &_re_U32_2057);
                    (void)_wcond_Bool_2062;
                    if (_wcond_Bool_2062) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_2057);
                    (void)_;
                    ;
                    U32_dec(&_rc_U32_2057);
                    I64 _t_I64_2063 = 10;
                    (void)_t_I64_2063;
                    F32 _t_F32_2064 = I64_to_f32(_t_I64_2063);
                    (void)_t_F32_2064;
                    ;
                    F32 _t_F32_2065 = F32_mul(scale, _t_F32_2064);
                    (void)_t_F32_2065;
                    ;
                    scale = _t_F32_2065;
                    ;
                }
            }
            ;
            ;
            ;
        }
        F32 _t_F32_2069 = F32_div(frac, scale);
        (void)_t_F32_2069;
        ;
        ;
        F32 _t_F32_2070 = F32_add(out, _t_F32_2069);
        (void)_t_F32_2070;
        ;
        out = _t_F32_2070;
        ;
    }
    ;
    Str_delete(frac_part, &(Bool){1});
    if (neg) {
        I64 _t_I64_2071 = 0;
        (void)_t_I64_2071;
        F32 _t_F32_2072 = I64_to_f32(_t_I64_2071);
        (void)_t_F32_2072;
        ;
        F32 _t_F32_2073 = F32_sub(_t_F32_2072, out);
        (void)_t_F32_2073;
        ;
        ;
        ;
        return _t_F32_2073;
    }
    ;
    return out;
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t_Str_2122 = Str_lit("Str", 3ULL);
    (void)_t_Str_2122;
    TilType *_t_TilType_2123 = TilType_Struct(_t_Str_2122);
    (void)_t_TilType_2123;
    Str_delete(_t_Str_2122, &(Bool){1});
    Vec *parts = Vec_new(_t_TilType_2123);
    (void)parts;
    TilType_delete(_t_TilType_2123, &(Bool){1});
    U32 _t_U32_2124 = Str_len(delim);
    (void)_t_U32_2124;
    U32 _t_U32_2125 = 0;
    (void)_t_U32_2125;
    Bool _t_Bool_2126 = U32_eq(_t_U32_2124, _t_U32_2125);
    (void)_t_Bool_2126;
    ;
    ;
    if (_t_Bool_2126) {
        Str *_t_Str_2106 = Str_clone(self);
        (void)_t_Str_2106;
        Vec_push(parts, _t_Str_2106);
        ;
        return parts;
    }
    ;
    U32 start = 0;
    (void)start;
    U32 pos = 0;
    (void)pos;
    while (1) {
        U32 _t_U32_2116 = Str_len(self);
        (void)_t_U32_2116;
        U32 _t_U32_2117 = Str_len(delim);
        (void)_t_U32_2117;
        U32 _t_U32_2118 = U32_sub(_t_U32_2116, _t_U32_2117);
        (void)_t_U32_2118;
        ;
        ;
        Bool _wcond_Bool_2107 = U32_lte(&pos, &_t_U32_2118);
        (void)_wcond_Bool_2107;
        ;
        if (_wcond_Bool_2107) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_2119 = Str_len(delim);
        (void)_t_U32_2119;
        Str *_t_Str_2120 = Str_substr(self, &pos, &_t_U32_2119);
        (void)_t_Str_2120;
        ;
        Bool _t_Bool_2121 = Str_eq(_t_Str_2120, delim);
        (void)_t_Bool_2121;
        Str_delete(_t_Str_2120, &(Bool){1});
        if (_t_Bool_2121) {
            U32 _t_U32_2108 = U32_sub(pos, start);
            (void)_t_U32_2108;
            Str *_t_Str_2109 = Str_substr(self, &start, &_t_U32_2108);
            (void)_t_Str_2109;
            ;
            Str *_t_Str_2110 = Str_clone(_t_Str_2109);
            (void)_t_Str_2110;
            Str_delete(_t_Str_2109, &(Bool){1});
            Vec_push(parts, _t_Str_2110);
            U32 _t_U32_2111 = Str_len(delim);
            (void)_t_U32_2111;
            U32 _t_U32_2112 = U32_add(pos, _t_U32_2111);
            (void)_t_U32_2112;
            ;
            start = _t_U32_2112;
            ;
            U32 _t_U32_2113 = U32_clone(&start);
            (void)_t_U32_2113;
            pos = _t_U32_2113;
            ;
        } else {
            U32 _t_U32_2114 = 1;
            (void)_t_U32_2114;
            U32 _t_U32_2115 = U32_add(pos, _t_U32_2114);
            (void)_t_U32_2115;
            ;
            pos = _t_U32_2115;
            ;
        }
        ;
    }
    ;
    U32 _t_U32_2127 = Str_len(self);
    (void)_t_U32_2127;
    U32 _t_U32_2128 = U32_sub(_t_U32_2127, start);
    (void)_t_U32_2128;
    ;
    Str *_t_Str_2129 = Str_substr(self, &start, &_t_U32_2128);
    (void)_t_Str_2129;
    ;
    ;
    Str *_t_Str_2130 = Str_clone(_t_Str_2129);
    (void)_t_Str_2130;
    Str_delete(_t_Str_2129, &(Bool){1});
    Vec_push(parts, _t_Str_2130);
    return parts;
}

U32 Str_size(void) {
    I64 _t_I64_2131 = 16;
    (void)_t_I64_2131;
    return _t_I64_2131;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2132 = Str_cmp(a, b);
    (void)_t_I64_2132;
    I64 _t_I64_2133 = 0;
    (void)_t_I64_2133;
    Bool _t_Bool_2134 = I64_eq(_t_I64_2132, _t_I64_2133);
    (void)_t_Bool_2134;
    ;
    ;
    return _t_Bool_2134;
}

Bool Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2135 = 0;
    (void)_t_I64_2135;
    I64 _t_I64_2136 = 1;
    (void)_t_I64_2136;
    I64 _t_I64_2137 = Str_cmp(a, b);
    (void)_t_I64_2137;
    I64 _t_I64_2138 = I64_sub(_t_I64_2135, _t_I64_2136);
    (void)_t_I64_2138;
    ;
    ;
    Bool _t_Bool_2139 = I64_eq(_t_I64_2137, _t_I64_2138);
    (void)_t_Bool_2139;
    ;
    ;
    return _t_Bool_2139;
}

Bool Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2140 = Str_cmp(a, b);
    (void)_t_I64_2140;
    I64 _t_I64_2141 = 1;
    (void)_t_I64_2141;
    Bool _t_Bool_2142 = I64_eq(_t_I64_2140, _t_I64_2141);
    (void)_t_Bool_2142;
    ;
    ;
    return _t_Bool_2142;
}

Bool Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2143 = Str_eq(a, b);
    (void)_t_Bool_2143;
    Bool _t_Bool_2144 = not(_t_Bool_2143);
    (void)_t_Bool_2144;
    ;
    return _t_Bool_2144;
}

Bool Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2145 = Str_gt(a, b);
    (void)_t_Bool_2145;
    Bool _t_Bool_2146 = not(_t_Bool_2145);
    (void)_t_Bool_2146;
    ;
    return _t_Bool_2146;
}

Bool Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2147 = Str_lt(a, b);
    (void)_t_Bool_2147;
    Bool _t_Bool_2148 = not(_t_Bool_2147);
    (void)_t_Bool_2148;
    ;
    return _t_Bool_2148;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_2180 = 8;
    (void)_t_I64_2180;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2180; return _r; }
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
    I64 _t_I64_2183 = I16_to_i64(DEREF(val));
    (void)_t_I64_2183;
    Str *_t_Str_2184 = I64_to_str(&_t_I64_2183);
    (void)_t_Str_2184;
    ;
    return _t_Str_2184;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t_I16_2185 = 1;
    (void)_t_I16_2185;
    I16 _t_I16_2186 = I16_add(DEREF(self), _t_I16_2185);
    (void)_t_I16_2186;
    ;
    *self = _t_I16_2186;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t_I16_2187 = 1;
    (void)_t_I16_2187;
    I16 _t_I16_2188 = I16_sub(DEREF(self), _t_I16_2187);
    (void)_t_I16_2188;
    ;
    *self = _t_I16_2188;
    ;
}

I16 * I16_unity(I16 * _self) {
    (void)_self;
    I64 _t_I64_2189 = 1;
    (void)_t_I64_2189;
    I16 _t_I16_2190 = I64_to_i16(_t_I64_2189);
    (void)_t_I16_2190;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2190; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t_I64_2191 = 0;
    (void)_t_I64_2191;
    I64 _t_I64_2192 = I16_to_i64(DEREF(a));
    (void)_t_I64_2192;
    I64 _t_I64_2193 = I64_sub(_t_I64_2191, _t_I64_2192);
    (void)_t_I64_2193;
    ;
    ;
    I16 _t_I16_2194 = I64_to_i16(_t_I64_2193);
    (void)_t_I16_2194;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2194; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t_I64_2199 = I16_to_i64(DEREF(a));
    (void)_t_I64_2199;
    I64 _t_I64_2200 = 0;
    (void)_t_I64_2200;
    Bool _t_Bool_2201 = I64_lt(&_t_I64_2199, &_t_I64_2200);
    (void)_t_Bool_2201;
    ;
    ;
    if (_t_Bool_2201) {
        I64 _t_I64_2195 = 0;
        (void)_t_I64_2195;
        I64 _t_I64_2196 = I16_to_i64(DEREF(a));
        (void)_t_I64_2196;
        I64 _t_I64_2197 = I64_sub(_t_I64_2195, _t_I64_2196);
        (void)_t_I64_2197;
        ;
        ;
        I16 _t_I16_2198 = I64_to_i16(_t_I64_2197);
        (void)_t_I16_2198;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2198; return _r; }
    }
    ;
    I16 _t_I16_2202 = I16_clone(a);
    (void)_t_I16_2202;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2202; return _r; }
}

U64 I16_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I16 *au = a;
    (void)au;
    I16 *bu = b;
    (void)bu;
    Bool _t_Bool_2206 = I16_lte(au, bu);
    (void)_t_Bool_2206;
    if (_t_Bool_2206) {
        I16 _t_I16_2203 = I16_sub(DEREF(bu), DEREF(au));
        (void)_t_I16_2203;
        I64 _t_I64_2204 = I16_to_i64(_t_I16_2203);
        (void)_t_I64_2204;
        ;
        U64 _t_U64_2205 = I64_to_u64(_t_I64_2204);
        (void)_t_U64_2205;
        ;
        ;
        return _t_U64_2205;
    }
    ;
    I16 _t_I16_2207 = I16_sub(DEREF(au), DEREF(bu));
    (void)_t_I16_2207;
    I64 _t_I64_2208 = I16_to_i64(_t_I16_2207);
    (void)_t_I64_2208;
    ;
    U64 _t_U64_2209 = I64_to_u64(_t_I64_2208);
    (void)_t_U64_2209;
    ;
    return _t_U64_2209;
}

void I16_delete(I16 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I16_size(void) {
    I64 _t_I64_2210 = 2;
    (void)_t_I64_2210;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2210; return _r; }
}

Bool I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2211 = 0;
    (void)_t_I64_2211;
    I64 _t_I64_2212 = 1;
    (void)_t_I64_2212;
    I64 _t_I64_2213 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2213;
    I64 _t_I64_2214 = I64_sub(_t_I64_2211, _t_I64_2212);
    (void)_t_I64_2214;
    ;
    ;
    Bool _t_Bool_2215 = I64_eq(_t_I64_2213, _t_I64_2214);
    (void)_t_Bool_2215;
    ;
    ;
    return _t_Bool_2215;
}

Bool I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2216 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2216;
    I64 _t_I64_2217 = 1;
    (void)_t_I64_2217;
    Bool _t_Bool_2218 = I64_eq(_t_I64_2216, _t_I64_2217);
    (void)_t_Bool_2218;
    ;
    ;
    return _t_Bool_2218;
}

Bool I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2219 = I16_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2219;
    Bool _t_Bool_2220 = not(_t_Bool_2219);
    (void)_t_Bool_2220;
    ;
    return _t_Bool_2220;
}

Bool I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2221 = I16_gt(a, b);
    (void)_t_Bool_2221;
    Bool _t_Bool_2222 = not(_t_Bool_2221);
    (void)_t_Bool_2222;
    ;
    return _t_Bool_2222;
}

Bool I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2223 = I16_lt(a, b);
    (void)_t_Bool_2223;
    Bool _t_Bool_2224 = not(_t_Bool_2223);
    (void)_t_Bool_2224;
    ;
    return _t_Bool_2224;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_2261 = 0;
    (void)_t_I64_2261;
    Bool _t_Bool_2262 = I64_eq(DEREF(val), _t_I64_2261);
    (void)_t_Bool_2262;
    ;
    if (_t_Bool_2262) {
        U64 _t_U64_2225 = 2;
        (void)_t_U64_2225;
        void * buf = malloc(_t_U64_2225);
        (void)buf;
        ;
        I64 _t_I64_2226 = 48;
        (void)_t_I64_2226;
        U64 _t_U64_2227 = 1;
        (void)_t_U64_2227;
        memcpy(buf, &_t_I64_2226, _t_U64_2227);
        ;
        ;
        U64 _t_U64_2228 = 1;
        (void)_t_U64_2228;
        void *_t_v_2229 = ptr_add(buf, _t_U64_2228);
        (void)_t_v_2229;
        I32 _t_I32_2230 = 0;
        (void)_t_I32_2230;
        U64 _t_U64_2231 = 1;
        (void)_t_U64_2231;
        memset(_t_v_2229, _t_I32_2230, _t_U64_2231);
        ;
        ;
        ;
        I64 _t_I64_2232 = 1;
        (void)_t_I64_2232;
        I64 _t_I64_2233 = 1;
        (void)_t_I64_2233;
        Str *_t_Str_2234 = malloc(sizeof(Str));
        _t_Str_2234->c_str = buf;
        _t_Str_2234->count = _t_I64_2232;
        _t_Str_2234->cap = _t_I64_2233;
        (void)_t_Str_2234;
        ;
        ;
        ;
        return _t_Str_2234;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t_I64_2263 = 0;
    (void)_t_I64_2263;
    Bool _t_Bool_2264 = I64_lt(val, &_t_I64_2263);
    (void)_t_Bool_2264;
    ;
    if (_t_Bool_2264) {
        Bool _t_Bool_2235 = 1;
        (void)_t_Bool_2235;
        is_neg = _t_Bool_2235;
        ;
        I64 _t_I64_2236 = 0;
        (void)_t_I64_2236;
        I64 _t_I64_2237 = I64_sub(_t_I64_2236, DEREF(val));
        (void)_t_I64_2237;
        ;
        v = _t_I64_2237;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&v);
    (void)tmp;
    while (1) {
        I64 _t_I64_2239 = 0;
        (void)_t_I64_2239;
        Bool _wcond_Bool_2238 = I64_gt(&tmp, &_t_I64_2239);
        (void)_wcond_Bool_2238;
        ;
        if (_wcond_Bool_2238) {
        } else {
            ;
            break;
        }
        ;
        U64 _t_U64_2240 = 1;
        (void)_t_U64_2240;
        U64 _t_U64_2241 = U64_add(ndigits, _t_U64_2240);
        (void)_t_U64_2241;
        ;
        ndigits = _t_U64_2241;
        ;
        I64 _t_I64_2242 = 10;
        (void)_t_I64_2242;
        I64 _t_I64_2243 = I64_div(tmp, _t_I64_2242);
        (void)_t_I64_2243;
        ;
        tmp = _t_I64_2243;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    (void)total;
    ;
    if (is_neg) {
        U64 _t_U64_2244 = 1;
        (void)_t_U64_2244;
        U64 _t_U64_2245 = U64_add(total, _t_U64_2244);
        (void)_t_U64_2245;
        ;
        total = _t_U64_2245;
        ;
    }
    U64 _t_U64_2265 = 1;
    (void)_t_U64_2265;
    U64 _t_U64_2266 = U64_add(total, _t_U64_2265);
    (void)_t_U64_2266;
    ;
    void * buf = malloc(_t_U64_2266);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t_I64_2246 = 45;
        (void)_t_I64_2246;
        U64 _t_U64_2247 = 1;
        (void)_t_U64_2247;
        memcpy(buf, &_t_I64_2246, _t_U64_2247);
        ;
        ;
    }
    ;
    U64 _t_U64_2267 = 1;
    (void)_t_U64_2267;
    U64 i = U64_sub(total, _t_U64_2267);
    (void)i;
    ;
    while (1) {
        I64 _t_I64_2249 = 0;
        (void)_t_I64_2249;
        Bool _wcond_Bool_2248 = I64_gt(&v, &_t_I64_2249);
        (void)_wcond_Bool_2248;
        ;
        if (_wcond_Bool_2248) {
        } else {
            ;
            break;
        }
        ;
        I64 _t_I64_2250 = 10;
        (void)_t_I64_2250;
        I64 _t_I64_2251 = I64_mod(v, _t_I64_2250);
        (void)_t_I64_2251;
        ;
        I64 _t_I64_2252 = 48;
        (void)_t_I64_2252;
        I64 _t_I64_2253 = I64_add(_t_I64_2251, _t_I64_2252);
        (void)_t_I64_2253;
        ;
        ;
        void *_t_v_2254 = ptr_add(buf, i);
        (void)_t_v_2254;
        U8 _t_U8_2255 = I64_to_u8(_t_I64_2253);
        (void)_t_U8_2255;
        ;
        U64 _t_U64_2256 = 1;
        (void)_t_U64_2256;
        memcpy(_t_v_2254, &_t_U8_2255, _t_U64_2256);
        ;
        ;
        I64 _t_I64_2257 = 10;
        (void)_t_I64_2257;
        I64 _t_I64_2258 = I64_div(v, _t_I64_2257);
        (void)_t_I64_2258;
        ;
        v = _t_I64_2258;
        ;
        U64 _t_U64_2259 = 1;
        (void)_t_U64_2259;
        U64 _t_U64_2260 = U64_sub(i, _t_U64_2259);
        (void)_t_U64_2260;
        ;
        i = _t_U64_2260;
        ;
    }
    ;
    ;
    void *_t_v_2268 = ptr_add(buf, total);
    (void)_t_v_2268;
    I32 _t_I32_2269 = 0;
    (void)_t_I32_2269;
    U64 _t_U64_2270 = 1;
    (void)_t_U64_2270;
    memset(_t_v_2268, _t_I32_2269, _t_U64_2270);
    ;
    ;
    Str *_t_Str_2271 = malloc(sizeof(Str));
    _t_Str_2271->c_str = buf;
    _t_Str_2271->count = total;
    _t_Str_2271->cap = total;
    (void)_t_Str_2271;
    ;
    return _t_Str_2271;
}

U32 I64_to_usize(I64 val) {
    (void)val;
    U32 _t_U32_2272 = I64_to_u32(val);
    (void)_t_U32_2272;
    return _t_U32_2272;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t_I64_2273 = 1;
    (void)_t_I64_2273;
    I64 _t_I64_2274 = I64_add(DEREF(self), _t_I64_2273);
    (void)_t_I64_2274;
    ;
    *self = _t_I64_2274;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t_I64_2275 = 1;
    (void)_t_I64_2275;
    I64 _t_I64_2276 = I64_sub(DEREF(self), _t_I64_2275);
    (void)_t_I64_2276;
    ;
    *self = _t_I64_2276;
    ;
}

I64 * I64_unity(I64 * _self) {
    (void)_self;
    I64 _t_I64_2277 = 1;
    (void)_t_I64_2277;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2277; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t_I64_2278 = 0;
    (void)_t_I64_2278;
    I64 _t_I64_2279 = I64_sub(_t_I64_2278, DEREF(a));
    (void)_t_I64_2279;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2279; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t_I64_2282 = 0;
    (void)_t_I64_2282;
    Bool _t_Bool_2283 = I64_lt(a, &_t_I64_2282);
    (void)_t_Bool_2283;
    ;
    if (_t_Bool_2283) {
        I64 _t_I64_2280 = 0;
        (void)_t_I64_2280;
        I64 _t_I64_2281 = I64_sub(_t_I64_2280, DEREF(a));
        (void)_t_I64_2281;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2281; return _r; }
    }
    ;
    I64 _t_I64_2284 = I64_clone(a);
    (void)_t_I64_2284;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2284; return _r; }
}

U64 I64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I64 *au = a;
    (void)au;
    I64 *bu = b;
    (void)bu;
    Bool _t_Bool_2287 = I64_lte(au, bu);
    (void)_t_Bool_2287;
    if (_t_Bool_2287) {
        I64 _t_I64_2285 = I64_sub(DEREF(bu), DEREF(au));
        (void)_t_I64_2285;
        U64 _t_U64_2286 = I64_to_u64(_t_I64_2285);
        (void)_t_U64_2286;
        ;
        ;
        return _t_U64_2286;
    }
    ;
    I64 _t_I64_2288 = I64_sub(DEREF(au), DEREF(bu));
    (void)_t_I64_2288;
    U64 _t_U64_2289 = I64_to_u64(_t_I64_2288);
    (void)_t_U64_2289;
    ;
    return _t_U64_2289;
}

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_2290 = 8;
    (void)_t_I64_2290;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2290; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2291 = 0;
    (void)_t_I64_2291;
    I64 _t_I64_2292 = 1;
    (void)_t_I64_2292;
    I64 _t_I64_2293 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2293;
    I64 _t_I64_2294 = I64_sub(_t_I64_2291, _t_I64_2292);
    (void)_t_I64_2294;
    ;
    ;
    Bool _t_Bool_2295 = I64_eq(_t_I64_2293, _t_I64_2294);
    (void)_t_Bool_2295;
    ;
    ;
    return _t_Bool_2295;
}

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2296 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2296;
    I64 _t_I64_2297 = 1;
    (void)_t_I64_2297;
    Bool _t_Bool_2298 = I64_eq(_t_I64_2296, _t_I64_2297);
    (void)_t_Bool_2298;
    ;
    ;
    return _t_Bool_2298;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2299 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2299;
    Bool _t_Bool_2300 = not(_t_Bool_2299);
    (void)_t_Bool_2300;
    ;
    return _t_Bool_2300;
}

Bool I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2301 = I64_gt(a, b);
    (void)_t_Bool_2301;
    Bool _t_Bool_2302 = not(_t_Bool_2301);
    (void)_t_Bool_2302;
    ;
    return _t_Bool_2302;
}

Bool I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2303 = I64_lt(a, b);
    (void)_t_Bool_2303;
    Bool _t_Bool_2304 = not(_t_Bool_2303);
    (void)_t_Bool_2304;
    ;
    return _t_Bool_2304;
}

Str * Bool_to_str(Bool * b) {
    (void)b;
    if (DEREF(b)) {
        Str *_t_Str_2305 = Str_lit("true", 4ULL);
        (void)_t_Str_2305;
        return _t_Str_2305;
    } else {
        Str *_t_Str_2306 = Str_lit("false", 5ULL);
        (void)_t_Str_2306;
        return _t_Str_2306;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2311 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2311;
    if (_t_Bool_2311) {
        I64 _t_I64_2307 = 0;
        (void)_t_I64_2307;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2307; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_2308 = 0;
        (void)_t_I64_2308;
        I64 _t_I64_2309 = 1;
        (void)_t_I64_2309;
        I64 _t_I64_2310 = I64_sub(_t_I64_2308, _t_I64_2309);
        (void)_t_I64_2310;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2310; return _r; }
    }
    I64 _t_I64_2312 = 1;
    (void)_t_I64_2312;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2312; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_2313 = 1;
    (void)_t_I64_2313;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2313; return _r; }
}

Bool Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2314 = 0;
    (void)_t_I64_2314;
    I64 _t_I64_2315 = 1;
    (void)_t_I64_2315;
    I64 _t_I64_2316; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_2316 = *_hp; free(_hp); }
    (void)_t_I64_2316;
    I64 _t_I64_2317 = I64_sub(_t_I64_2314, _t_I64_2315);
    (void)_t_I64_2317;
    ;
    ;
    Bool _t_Bool_2318 = I64_eq(_t_I64_2316, _t_I64_2317);
    (void)_t_Bool_2318;
    ;
    ;
    return _t_Bool_2318;
}

Bool Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2319; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_2319 = *_hp; free(_hp); }
    (void)_t_I64_2319;
    I64 _t_I64_2320 = 1;
    (void)_t_I64_2320;
    Bool _t_Bool_2321 = I64_eq(_t_I64_2319, _t_I64_2320);
    (void)_t_Bool_2321;
    ;
    ;
    return _t_Bool_2321;
}

Bool Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2322 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2322;
    Bool _t_Bool_2323 = not(_t_Bool_2322);
    (void)_t_Bool_2323;
    ;
    return _t_Bool_2323;
}

Bool Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2324 = Bool_gt(a, b);
    (void)_t_Bool_2324;
    Bool _t_Bool_2325 = not(_t_Bool_2324);
    (void)_t_Bool_2325;
    ;
    return _t_Bool_2325;
}

Bool Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2326 = Bool_lt(a, b);
    (void)_t_Bool_2326;
    Bool _t_Bool_2327 = not(_t_Bool_2326);
    (void)_t_Bool_2327;
    ;
    return _t_Bool_2327;
}

Array * Array_new(Str * elem_type, U32 * cap) {
    (void)elem_type;
    (void)cap;
    Bool _t_Bool_2333 = Str_is_empty(elem_type);
    (void)_t_Bool_2333;
    if (_t_Bool_2333) {
        Str *_t_Str_2328 = Str_lit("Str", 3ULL);
        (void)_t_Str_2328;
        U32 _t_U32_2329 = 1;
        (void)_t_U32_2329;
        Array *_va_Array_73 = Array_new(_t_Str_2328, &_t_U32_2329);
        (void)_va_Array_73;
        Str_delete(_t_Str_2328, &(Bool){1});
        ;
        U32 _t_U32_2330 = 0;
        (void)_t_U32_2330;
        Str *_t_Str_2331 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_2331;
        Array_set(_va_Array_73, &_t_U32_2330, _t_Str_2331);
        ;
        Str *_t_Str_2332 = Str_lit("./src/core/array.til:22:41", 26ULL);
        (void)_t_Str_2332;
        panic(_t_Str_2332, _va_Array_73);
        Str_delete(_t_Str_2332, &(Bool){1});
    }
    ;
    U32 elem_size = dyn_size_of(elem_type);
    (void)elem_size;
    void * _t_v_2334 = calloc(DEREF(cap), elem_size);
    (void)_t_v_2334;
    void * _t_v_2335 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2335;
    void * _t_v_2336 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2336;
    Array *_t_Array_2337 = malloc(sizeof(Array));
    _t_Array_2337->data = _t_v_2334;
    _t_Array_2337->cap = DEREF(cap);
    _t_Array_2337->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); _t_Array_2337->elem_type = *_ca; free(_ca); }
    _t_Array_2337->elem_clone = _t_v_2335;
    _t_Array_2337->elem_delete = _t_v_2336;
    (void)_t_Array_2337;
    ;
    return _t_Array_2337;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_2351 = U32_gte(i, &self->cap);
    (void)_t_Bool_2351;
    if (_t_Bool_2351) {
        Str *_t_Str_2338 = Str_lit("Str", 3ULL);
        (void)_t_Str_2338;
        U32 _t_U32_2339 = 5;
        (void)_t_U32_2339;
        Array *_va_Array_74 = Array_new(_t_Str_2338, &_t_U32_2339);
        (void)_va_Array_74;
        Str_delete(_t_Str_2338, &(Bool){1});
        ;
        U32 _t_U32_2340 = 0;
        (void)_t_U32_2340;
        Str *_t_Str_2341 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_2341;
        Array_set(_va_Array_74, &_t_U32_2340, _t_Str_2341);
        ;
        U32 _t_U32_2342 = 1;
        (void)_t_U32_2342;
        Str *_t_Str_2343 = U32_to_str(i);
        (void)_t_Str_2343;
        Array_set(_va_Array_74, &_t_U32_2342, _t_Str_2343);
        ;
        U32 _t_U32_2344 = 2;
        (void)_t_U32_2344;
        Str *_t_Str_2345 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2345;
        Array_set(_va_Array_74, &_t_U32_2344, _t_Str_2345);
        ;
        U32 _t_U32_2346 = 3;
        (void)_t_U32_2346;
        Str *_t_Str_2347 = U32_to_str(&self->cap);
        (void)_t_Str_2347;
        Array_set(_va_Array_74, &_t_U32_2346, _t_Str_2347);
        ;
        U32 _t_U32_2348 = 4;
        (void)_t_U32_2348;
        Str *_t_Str_2349 = Str_lit(")", 1ULL);
        (void)_t_Str_2349;
        Array_set(_va_Array_74, &_t_U32_2348, _t_Str_2349);
        ;
        Str *_t_Str_2350 = Str_lit("./src/core/array.til:35:19", 26ULL);
        (void)_t_Str_2350;
        panic(_t_Str_2350, _va_Array_74);
        Str_delete(_t_Str_2350, &(Bool){1});
    }
    ;
    U32 _t_U64_2352 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2352;
    void *_t_v_2353 = ptr_add(self->data, _t_U64_2352);
    (void)_t_v_2353;
    ;
    return _t_v_2353;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_2367 = U32_gte(i, &self->cap);
    (void)_t_Bool_2367;
    if (_t_Bool_2367) {
        Str *_t_Str_2354 = Str_lit("Str", 3ULL);
        (void)_t_Str_2354;
        U32 _t_U32_2355 = 5;
        (void)_t_U32_2355;
        Array *_va_Array_75 = Array_new(_t_Str_2354, &_t_U32_2355);
        (void)_va_Array_75;
        Str_delete(_t_Str_2354, &(Bool){1});
        ;
        U32 _t_U32_2356 = 0;
        (void)_t_U32_2356;
        Str *_t_Str_2357 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_2357;
        Array_set(_va_Array_75, &_t_U32_2356, _t_Str_2357);
        ;
        U32 _t_U32_2358 = 1;
        (void)_t_U32_2358;
        Str *_t_Str_2359 = U32_to_str(i);
        (void)_t_Str_2359;
        Array_set(_va_Array_75, &_t_U32_2358, _t_Str_2359);
        ;
        U32 _t_U32_2360 = 2;
        (void)_t_U32_2360;
        Str *_t_Str_2361 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2361;
        Array_set(_va_Array_75, &_t_U32_2360, _t_Str_2361);
        ;
        U32 _t_U32_2362 = 3;
        (void)_t_U32_2362;
        Str *_t_Str_2363 = U32_to_str(&self->cap);
        (void)_t_Str_2363;
        Array_set(_va_Array_75, &_t_U32_2362, _t_Str_2363);
        ;
        U32 _t_U32_2364 = 4;
        (void)_t_U32_2364;
        Str *_t_Str_2365 = Str_lit(")", 1ULL);
        (void)_t_Str_2365;
        Array_set(_va_Array_75, &_t_U32_2364, _t_Str_2365);
        ;
        Str *_t_Str_2366 = Str_lit("./src/core/array.til:44:19", 26ULL);
        (void)_t_Str_2366;
        panic(_t_Str_2366, _va_Array_75);
        Str_delete(_t_Str_2366, &(Bool){1});
    }
    ;
    U32 _t_U64_2368 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2368;
    void *_t_v_2369 = ptr_add(self->data, _t_U64_2368);
    (void)_t_v_2369;
    Bool _t_Bool_2370 = 0;
    (void)_t_Bool_2370;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2369, &_t_Bool_2370);
    ;
    ;
    U32 _t_U64_2371 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2371;
    void *_t_v_2372 = ptr_add(self->data, _t_U64_2371);
    (void)_t_v_2372;
    memcpy(_t_v_2372, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_2373 = self->cap;
        (void)_re_U32_2373;
        U32 _rc_U32_2373 = 0;
        (void)_rc_U32_2373;
        Bool _t_Bool_2382 = U32_lte(&_rc_U32_2373, &_re_U32_2373);
        (void)_t_Bool_2382;
        if (_t_Bool_2382) {
            while (1) {
                Bool _wcond_Bool_2374 = U32_lt(&_rc_U32_2373, &_re_U32_2373);
                (void)_wcond_Bool_2374;
                if (_wcond_Bool_2374) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2373);
                (void)i;
                U32_inc(&_rc_U32_2373);
                U32 _t_U64_2375 = U32_mul(i, self->elem_size);
                (void)_t_U64_2375;
                ;
                void *_t_v_2376 = ptr_add(self->data, _t_U64_2375);
                (void)_t_v_2376;
                Bool _t_Bool_2377 = 0;
                (void)_t_Bool_2377;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2376, &_t_Bool_2377);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2378 = U32_gt(&_rc_U32_2373, &_re_U32_2373);
                (void)_wcond_Bool_2378;
                if (_wcond_Bool_2378) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2373);
                (void)i;
                U32_dec(&_rc_U32_2373);
                U32 _t_U64_2379 = U32_mul(i, self->elem_size);
                (void)_t_U64_2379;
                ;
                void *_t_v_2380 = ptr_add(self->data, _t_U64_2379);
                (void)_t_v_2380;
                Bool _t_Bool_2381 = 0;
                (void)_t_Bool_2381;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2380, &_t_Bool_2381);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_2383 = 0;
    (void)_t_Bool_2383;
    Str_delete(&self->elem_type, &_t_Bool_2383);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_2396 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_2396;
    void * new_data = malloc(_t_U64_2396);
    (void)new_data;
    ;
    {
        U32 _re_U32_2384 = self->cap;
        (void)_re_U32_2384;
        U32 _rc_U32_2384 = 0;
        (void)_rc_U32_2384;
        Bool _t_Bool_2395 = U32_lte(&_rc_U32_2384, &_re_U32_2384);
        (void)_t_Bool_2395;
        if (_t_Bool_2395) {
            while (1) {
                Bool _wcond_Bool_2385 = U32_lt(&_rc_U32_2384, &_re_U32_2384);
                (void)_wcond_Bool_2385;
                if (_wcond_Bool_2385) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2384);
                (void)i;
                U32_inc(&_rc_U32_2384);
                U32 _t_U64_2386 = U32_mul(i, self->elem_size);
                (void)_t_U64_2386;
                void *_t_v_2387 = ptr_add(self->data, _t_U64_2386);
                (void)_t_v_2387;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2387);
                (void)cloned;
                ;
                U32 _t_U64_2388 = U32_mul(i, self->elem_size);
                (void)_t_U64_2388;
                ;
                void *_t_v_2389 = ptr_add(new_data, _t_U64_2388);
                (void)_t_v_2389;
                memcpy(_t_v_2389, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2390 = U32_gt(&_rc_U32_2384, &_re_U32_2384);
                (void)_wcond_Bool_2390;
                if (_wcond_Bool_2390) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2384);
                (void)i;
                U32_dec(&_rc_U32_2384);
                U32 _t_U64_2391 = U32_mul(i, self->elem_size);
                (void)_t_U64_2391;
                void *_t_v_2392 = ptr_add(self->data, _t_U64_2391);
                (void)_t_v_2392;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2392);
                (void)cloned;
                ;
                U32 _t_U64_2393 = U32_mul(i, self->elem_size);
                (void)_t_U64_2393;
                ;
                void *_t_v_2394 = ptr_add(new_data, _t_U64_2393);
                (void)_t_v_2394;
                memcpy(_t_v_2394, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_2397 = malloc(sizeof(Array));
    _t_Array_2397->data = new_data;
    _t_Array_2397->cap = self->cap;
    _t_Array_2397->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_2397->elem_type = *_ca; free(_ca); }
    _t_Array_2397->elem_clone = (void *)self->elem_clone;
    _t_Array_2397->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_2397;
    return _t_Array_2397;
}

U32 Array_size(void) {
    I64 _t_I64_2398 = 48;
    (void)_t_I64_2398;
    return _t_I64_2398;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2621 = Str_lit("Str", 3ULL);
    (void)_t_Str_2621;
    U32 _t_U32_2622 = 3;
    (void)_t_U32_2622;
    Array *_va_Array_92 = Array_new(_t_Str_2621, &_t_U32_2622);
    (void)_va_Array_92;
    Str_delete(_t_Str_2621, &(Bool){1});
    ;
    U32 _t_U32_2623 = 0;
    (void)_t_U32_2623;
    Str *_t_Str_2624 = Str_clone(loc_str);
    (void)_t_Str_2624;
    Array_set(_va_Array_92, &_t_U32_2623, _t_Str_2624);
    ;
    U32 _t_U32_2625 = 1;
    (void)_t_U32_2625;
    Str *_t_Str_2626 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2626;
    Array_set(_va_Array_92, &_t_U32_2625, _t_Str_2626);
    ;
    Array *_t_Array_2627 = Array_clone(parts);
    (void)_t_Array_2627;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2628 = 2;
    (void)_t_U32_2628;
    Str *_t_Str_2629 = format(_t_Array_2627);
    (void)_t_Str_2629;
    Array_set(_va_Array_92, &_t_U32_2628, _t_Str_2629);
    ;
    println(_va_Array_92);
    I64 _t_I64_2630 = 1;
    (void)_t_I64_2630;
    exit(_t_I64_2630);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2646 = not(DEREF(cond));
    (void)_t_Bool_2646;
    if (_t_Bool_2646) {
        Str *_t_Str_2642 = Str_lit("Str", 3ULL);
        (void)_t_Str_2642;
        U32 _t_U32_2643 = 1;
        (void)_t_U32_2643;
        Array *_va_Array_95 = Array_new(_t_Str_2642, &_t_U32_2643);
        (void)_va_Array_95;
        Str_delete(_t_Str_2642, &(Bool){1});
        ;
        U32 _t_U32_2644 = 0;
        (void)_t_U32_2644;
        Str *_t_Str_2645 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2645;
        Array_set(_va_Array_95, &_t_U32_2644, _t_Str_2645);
        ;
        panic(loc_str, _va_Array_95);
    }
    ;
    Bool _t_Bool_2647 = 1;
    (void)_t_Bool_2647;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2647; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2668 = I64_neq(a, b);
    (void)_t_Bool_2668;
    if (_t_Bool_2668) {
        Str *_t_Str_2656 = Str_lit("Str", 3ULL);
        (void)_t_Str_2656;
        U32 _t_U32_2657 = 5;
        (void)_t_U32_2657;
        Array *_va_Array_97 = Array_new(_t_Str_2656, &_t_U32_2657);
        (void)_va_Array_97;
        Str_delete(_t_Str_2656, &(Bool){1});
        ;
        U32 _t_U32_2658 = 0;
        (void)_t_U32_2658;
        Str *_t_Str_2659 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2659;
        Array_set(_va_Array_97, &_t_U32_2658, _t_Str_2659);
        ;
        U32 _t_U32_2660 = 1;
        (void)_t_U32_2660;
        Str *_t_Str_2661 = I64_to_str(a);
        (void)_t_Str_2661;
        Array_set(_va_Array_97, &_t_U32_2660, _t_Str_2661);
        ;
        U32 _t_U32_2662 = 2;
        (void)_t_U32_2662;
        Str *_t_Str_2663 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2663;
        Array_set(_va_Array_97, &_t_U32_2662, _t_Str_2663);
        ;
        U32 _t_U32_2664 = 3;
        (void)_t_U32_2664;
        Str *_t_Str_2665 = I64_to_str(b);
        (void)_t_Str_2665;
        Array_set(_va_Array_97, &_t_U32_2664, _t_Str_2665);
        ;
        U32 _t_U32_2666 = 4;
        (void)_t_U32_2666;
        Str *_t_Str_2667 = Str_lit("'", 1ULL);
        (void)_t_Str_2667;
        Array_set(_va_Array_97, &_t_U32_2666, _t_Str_2667);
        ;
        panic(loc_str, _va_Array_97);
    }
    ;
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

void test_simple_add(void) {
    I64 _t_I64_2873 = 1;
    (void)_t_I64_2873;
    I64 _t_I64_2874 = 2;
    (void)_t_I64_2874;
    I64 result = 3;
    (void)result;
    ;
    ;
    Str *_t_Str_2875 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_2875;
    I64 _t_I64_2876 = 3;
    (void)_t_I64_2876;
    assert_eq(_t_Str_2875, &result, &_t_I64_2876);
    ;
    Str_delete(_t_Str_2875, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 _t_I64_2877 = 1;
    (void)_t_I64_2877;
    I64 _t_I64_2878 = 2;
    (void)_t_I64_2878;
    I64 _t_I64_2879 = 10;
    (void)_t_I64_2879;
    I64 _t_I64_2880 = 5;
    (void)_t_I64_2880;
    I64 _t_I64_2881 = 3;
    (void)_t_I64_2881;
    ;
    ;
    I64 _t_I64_2882 = 5;
    (void)_t_I64_2882;
    ;
    ;
    I64 result = 15;
    (void)result;
    ;
    ;
    Str *_t_Str_2883 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_2883;
    I64 _t_I64_2884 = 15;
    (void)_t_I64_2884;
    assert_eq(_t_Str_2883, &result, &_t_I64_2884);
    ;
    Str_delete(_t_Str_2883, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 _t_I64_2885 = 2;
    (void)_t_I64_2885;
    I64 _t_I64_2886 = 3;
    (void)_t_I64_2886;
    I64 _t_I64_2887 = 4;
    (void)_t_I64_2887;
    I64 _t_I64_2888 = 5;
    (void)_t_I64_2888;
    I64 _t_I64_2889 = 6;
    (void)_t_I64_2889;
    ;
    ;
    I64 _t_I64_2890 = 20;
    (void)_t_I64_2890;
    ;
    ;
    I64 result = 26;
    (void)result;
    ;
    ;
    Str *_t_Str_2891 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_2891;
    I64 _t_I64_2892 = 26;
    (void)_t_I64_2892;
    assert_eq(_t_Str_2891, &result, &_t_I64_2892);
    ;
    Str_delete(_t_Str_2891, &(Bool){1});
    ;
}

Str * poem(I64 * depth, Str * current, Str * s1, Str * s2) {
    (void)depth;
    (void)current;
    (void)s1;
    (void)s2;
    I64 _t_I64_2900 = 4;
    (void)_t_I64_2900;
    Bool _t_Bool_2901 = I64_eq(DEREF(depth), _t_I64_2900);
    (void)_t_Bool_2901;
    ;
    if (_t_Bool_2901) {
        Str *_t_Str_2893 = Str_lit("\n", 2ULL);
        (void)_t_Str_2893;
        Str *_t_Str_2894 = Str_concat(current, _t_Str_2893);
        (void)_t_Str_2894;
        Str_delete(_t_Str_2893, &(Bool){1});
        ;
        return _t_Str_2894;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    I64 _t_I64_2902 = 1;
    (void)_t_I64_2902;
    I64 _t_I64_2903 = I64_add(DEREF(depth), _t_I64_2902);
    (void)_t_I64_2903;
    ;
    Str *_t_Str_2904 = Str_concat(current, s1);
    (void)_t_Str_2904;
    Str *_t_Str_2905 = poem(&_t_I64_2903, _t_Str_2904, s1, s2);
    (void)_t_Str_2905;
    ;
    Str_delete(_t_Str_2904, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2905); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2905, &(Bool){1});
    I64 _t_I64_2906 = 1;
    (void)_t_I64_2906;
    I64 _t_I64_2907 = I64_add(DEREF(depth), _t_I64_2906);
    (void)_t_I64_2907;
    ;
    Str *_t_Str_2908 = Str_concat(current, s2);
    (void)_t_Str_2908;
    Str *_t_Str_2909 = poem(&_t_I64_2907, _t_Str_2908, s1, s2);
    (void)_t_Str_2909;
    ;
    Str_delete(_t_Str_2908, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2909); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2909, &(Bool){1});
    I64 _t_I64_2910 = 2;
    (void)_t_I64_2910;
    Bool _t_Bool_2911 = I64_eq(DEREF(depth), _t_I64_2910);
    (void)_t_Bool_2911;
    ;
    if (_t_Bool_2911) {
        I64 _t_I64_2895 = 1;
        (void)_t_I64_2895;
        Str *_t_Str_2896 = Str_lit("lei", 3ULL);
        (void)_t_Str_2896;
        I64 _t_I64_2897 = I64_add(DEREF(depth), _t_I64_2895);
        (void)_t_I64_2897;
        ;
        Str *_t_Str_2898 = Str_concat(current, _t_Str_2896);
        (void)_t_Str_2898;
        Str_delete(_t_Str_2896, &(Bool){1});
        Str *_t_Str_2899 = poem(&_t_I64_2897, _t_Str_2898, s1, s2);
        (void)_t_Str_2899;
        ;
        Str_delete(_t_Str_2898, &(Bool){1});
        { Str *_old = result; result = Str_concat(result, _t_Str_2899); Str_delete(_old, &(Bool){1}); }
        Str_delete(_t_Str_2899, &(Bool){1});
    }
    ;
    return result;
}

Str * make_poem(Str * s1, Str * s2) {
    (void)s1;
    (void)s2;
    I64 _t_I64_2912 = 0;
    (void)_t_I64_2912;
    Str *_t_Str_2913 = Str_lit("", 0ULL);
    (void)_t_Str_2913;
    Str *_t_Str_2914 = poem(&_t_I64_2912, _t_Str_2913, s1, s2);
    (void)_t_Str_2914;
    ;
    Str_delete(_t_Str_2913, &(Bool){1});
    return _t_Str_2914;
}

void test_lolalalo(void) {
    Str *_t_Str_2915 = Str_lit("lo", 2ULL);
    (void)_t_Str_2915;
    Str *_t_Str_2916 = Str_lit("la", 2ULL);
    (void)_t_Str_2916;
    Str *lo_la = make_poem(_t_Str_2915, _t_Str_2916);
    (void)lo_la;
    Str_delete(_t_Str_2915, &(Bool){1});
    Str_delete(_t_Str_2916, &(Bool){1});
    Str *_t_Str_2917 = Str_lit("la", 2ULL);
    (void)_t_Str_2917;
    Str *_t_Str_2918 = Str_lit("lo", 2ULL);
    (void)_t_Str_2918;
    Str *la_lo = make_poem(_t_Str_2917, _t_Str_2918);
    (void)la_lo;
    Str_delete(_t_Str_2917, &(Bool){1});
    Str_delete(_t_Str_2918, &(Bool){1});
    Str *_t_Str_2919 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_2919;
    Str *_t_Str_2920 = Str_lit("src/test/constfold.til:56:12", 28ULL);
    (void)_t_Str_2920;
    Bool _t_Bool_2921 = Str_contains(lo_la, _t_Str_2919);
    (void)_t_Bool_2921;
    Str_delete(_t_Str_2919, &(Bool){1});
    Bool _t_Bool_2922; { Bool *_hp = (Bool *)assert(_t_Str_2920, &_t_Bool_2921); _t_Bool_2922 = *_hp; free(_hp); }
    (void)_t_Bool_2922;
    ;
    ;
    Str_delete(_t_Str_2920, &(Bool){1});
    Str *_t_Str_2923 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_2923;
    Str *_t_Str_2924 = Str_lit("src/test/constfold.til:57:12", 28ULL);
    (void)_t_Str_2924;
    Bool _t_Bool_2925 = Str_contains(la_lo, _t_Str_2923);
    (void)_t_Bool_2925;
    Str_delete(_t_Str_2923, &(Bool){1});
    Bool _t_Bool_2926; { Bool *_hp = (Bool *)assert(_t_Str_2924, &_t_Bool_2925); _t_Bool_2926 = *_hp; free(_hp); }
    (void)_t_Bool_2926;
    ;
    ;
    Str_delete(_t_Str_2924, &(Bool){1});
    Str *_t_Str_2927 = Str_lit("lolei", 5ULL);
    (void)_t_Str_2927;
    Str *_t_Str_2928 = Str_lit("src/test/constfold.til:59:12", 28ULL);
    (void)_t_Str_2928;
    Bool _t_Bool_2929 = Str_contains(lo_la, _t_Str_2927);
    (void)_t_Bool_2929;
    Str_delete(_t_Str_2927, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    Bool _t_Bool_2930; { Bool *_hp = (Bool *)assert(_t_Str_2928, &_t_Bool_2929); _t_Bool_2930 = *_hp; free(_hp); }
    (void)_t_Bool_2930;
    ;
    ;
    Str_delete(_t_Str_2928, &(Bool){1});
    Str *_t_Str_2931 = Str_lit("lalei", 5ULL);
    (void)_t_Str_2931;
    Str *_t_Str_2932 = Str_lit("src/test/constfold.til:60:12", 28ULL);
    (void)_t_Str_2932;
    Bool _t_Bool_2933 = Str_contains(la_lo, _t_Str_2931);
    (void)_t_Bool_2933;
    Str_delete(_t_Str_2931, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    Bool _t_Bool_2934; { Bool *_hp = (Bool *)assert(_t_Str_2932, &_t_Bool_2933); _t_Bool_2934 = *_hp; free(_hp); }
    (void)_t_Bool_2934;
    ;
    ;
    Str_delete(_t_Str_2932, &(Bool){1});
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
void *TilType_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = TilType_eq(_a0, _a1); return _r;
}
void *TilType_is_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = TilType_is(_a0, _a1); return _r;
}
void *TilType_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = TilType_size(); return _r;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)TilType_eq_dyn;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Unknown", 7ULL) == 0) return (void*)TilType_Unknown;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "None", 4ULL) == 0) return (void*)TilType_None;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "I64", 3ULL) == 0) return (void*)TilType_I64;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "U8", 2ULL) == 0) return (void*)TilType_U8;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "I16", 3ULL) == 0) return (void*)TilType_I16;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "I32", 3ULL) == 0) return (void*)TilType_I32;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "U32", 3ULL) == 0) return (void*)TilType_U32;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "U64", 3ULL) == 0) return (void*)TilType_U64;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "F32", 3ULL) == 0) return (void*)TilType_F32;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Bool", 4ULL) == 0) return (void*)TilType_Bool;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Struct", 6ULL) == 0) return (void*)TilType_Struct;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "StructDef", 9ULL) == 0) return (void*)TilType_StructDef;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Enum", 4ULL) == 0) return (void*)TilType_Enum;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "EnumDef", 7ULL) == 0) return (void*)TilType_EnumDef;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncDef", 7ULL) == 0) return (void*)TilType_FuncDef;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncPtr", 7ULL) == 0) return (void*)TilType_FuncPtr;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Dynamic", 7ULL) == 0) return (void*)TilType_Dynamic;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Custom", 6ULL) == 0) return (void*)TilType_Custom;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "is", 2ULL) == 0) return (void*)TilType_is_dyn;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)TilType_delete;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)TilType_to_str;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)TilType_clone;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)TilType_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "new_type_name", 13ULL) == 0) return (void*)Vec_new_type_name;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "TilType", 7ULL) == 0) return sizeof(TilType);
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

Str *dyn_type_to_str(TilType *type) {
    switch (type->tag) {
    case TilType_TAG_Unknown: return Str_lit("", 0ULL);
    case TilType_TAG_None: return Str_lit("", 0ULL);
    case TilType_TAG_I64: return Str_lit("I64", 3ULL);
    case TilType_TAG_U8: return Str_lit("U8", 2ULL);
    case TilType_TAG_I16: return Str_lit("I16", 3ULL);
    case TilType_TAG_I32: return Str_lit("I32", 3ULL);
    case TilType_TAG_U32: return Str_lit("U32", 3ULL);
    case TilType_TAG_U64: return Str_lit("U64", 3ULL);
    case TilType_TAG_F32: return Str_lit("F32", 3ULL);
    case TilType_TAG_Bool: return Str_lit("Bool", 4ULL);
    case TilType_TAG_Struct: return Str_clone(&type->data.Struct);
    case TilType_TAG_StructDef: return Str_lit("StructDef", 9ULL);
    case TilType_TAG_Enum: return Str_clone(&type->data.Enum);
    case TilType_TAG_EnumDef: return Str_lit("EnumDef", 7ULL);
    case TilType_TAG_FuncDef: return Str_lit("FunctionDef", 11ULL);
    case TilType_TAG_FuncPtr: return Str_lit("Fn", 2ULL);
    case TilType_TAG_Dynamic: return Str_lit("Dynamic", 7ULL);
    case TilType_TAG_Custom: return Str_clone(&type->data.Custom);
    }
    return Str_lit("?", 1ULL);
}

int main(void) {
    I64 _t_I64_2174 = 0;
    (void)_t_I64_2174;
    I64 _t_I64_2175 = 1;
    (void)_t_I64_2175;
    I64 _t_I64_2176 = I64_sub(_t_I64_2174, _t_I64_2175);
    (void)_t_I64_2176;
    CAP_LIT = I64_to_usize(_t_I64_2176);
    (void)CAP_LIT;
    I64 _t_I64_2177 = 0;
    (void)_t_I64_2177;
    I64 _t_I64_2178 = 2;
    (void)_t_I64_2178;
    I64 _t_I64_2179 = I64_sub(_t_I64_2177, _t_I64_2178);
    (void)_t_I64_2179;
    CAP_VIEW = I64_to_usize(_t_I64_2179);
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
