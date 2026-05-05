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
Vec * Vec_new_newi(TilType * T);
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
Vec * Vec_new_newi(TilType * T);
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

Vec * Vec_new_newi(TilType * T) {
    (void)T;
    Vec *_t_Vec_1502 = Vec_new(T);
    (void)_t_Vec_1502;
    return _t_Vec_1502;
}

U32 Vec_len(Vec * self) {
    (void)self;
    return self->count;
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t_Bool_1507 = U32_eq(self->count, self->cap);
    (void)_t_Bool_1507;
    if (_t_Bool_1507) {
        U32 _t_U32_1503 = 2;
        (void)_t_U32_1503;
        U32 new_cap = U32_mul(self->cap, _t_U32_1503);
        (void)new_cap;
        ;
        U32 _t_U64_1504 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1504;
        void * _t_v_1505 = realloc(self->data, _t_U64_1504);
        (void)_t_v_1505;
        ;
        self->data = _t_v_1505;
        U32 _t_U32_1506 = U32_clone(&new_cap);
        (void)_t_U32_1506;
        ;
        self->cap = _t_U32_1506;
        ;
    }
    ;
    U32 _t_U64_1508 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_1508;
    void *_t_v_1509 = ptr_add(self->data, _t_U64_1508);
    (void)_t_v_1509;
    memcpy(_t_v_1509, val, self->elem_size);
    ;
    free(val);
    U32 _t_U32_1510 = 1;
    (void)_t_U32_1510;
    U32 _t_U32_1511 = U32_add(self->count, _t_U32_1510);
    (void)_t_U32_1511;
    ;
    self->count = _t_U32_1511;
    ;
}

void Vec_append(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_1523 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_1523;
    Bool _t_Bool_1524 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_1524;
    Bool _t_Bool_1525 = not(_t_Bool_1523);
    (void)_t_Bool_1525;
    ;
    Bool _t_Bool_1526 = not(_t_Bool_1524);
    (void)_t_Bool_1526;
    ;
    Bool _t_Bool_1527 = or(_t_Bool_1525, _t_Bool_1526);
    (void)_t_Bool_1527;
    ;
    ;
    if (_t_Bool_1527) {
        Str *_t_Str_1512 = Str_lit("Str", 3ULL);
        (void)_t_Str_1512;
        U32 _t_U32_1513 = 1;
        (void)_t_U32_1513;
        Array *_va_Array_58 = Array_new(_t_Str_1512, &_t_U32_1513);
        (void)_va_Array_58;
        Str_delete(_t_Str_1512, &(Bool){1});
        ;
        U32 _t_U32_1514 = 0;
        (void)_t_U32_1514;
        Str *_t_Str_1515 = Str_lit("Vec.append: incompatible vecs", 29ULL);
        (void)_t_Str_1515;
        Array_set(_va_Array_58, &_t_U32_1514, _t_Str_1515);
        ;
        Str *_t_Str_1516 = Str_lit("./src/core/vec.til:66:19", 24ULL);
        (void)_t_Str_1516;
        panic(_t_Str_1516, _va_Array_58);
        Str_delete(_t_Str_1516, &(Bool){1});
    }
    ;
    U32 _t_U32_1528 = 0;
    (void)_t_U32_1528;
    Bool _t_Bool_1529 = U32_eq(other->count, _t_U32_1528);
    (void)_t_Bool_1529;
    ;
    if (_t_Bool_1529) {
        ;
        Vec_delete(other, &(Bool){0});
        return;
    }
    ;
    U32 needed = U32_add(self->count, other->count);
    (void)needed;
    Bool _t_Bool_1530 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_1530;
    if (_t_Bool_1530) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_1517 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_1517;
            if (_wcond_Bool_1517) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_1518 = 2;
            (void)_t_U32_1518;
            U32 _t_U32_1519 = U32_mul(new_cap, _t_U32_1518);
            (void)_t_U32_1519;
            ;
            new_cap = _t_U32_1519;
            ;
        }
        U32 _t_U64_1520 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1520;
        void * _t_v_1521 = realloc(self->data, _t_U64_1520);
        (void)_t_v_1521;
        ;
        self->data = _t_v_1521;
        U32 _t_U32_1522 = U32_clone(&new_cap);
        (void)_t_U32_1522;
        ;
        self->cap = _t_U32_1522;
        ;
    }
    ;
    U32 _t_U64_1531 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_1531;
    void *_t_v_1532 = ptr_add(self->data, _t_U64_1531);
    (void)_t_v_1532;
    U32 _t_U64_1533 = U32_mul(other->count, self->elem_size);
    (void)_t_U64_1533;
    memcpy(_t_v_1532, other->data, _t_U64_1533);
    ;
    ;
    U32 _t_U32_1534 = U32_clone(&needed);
    (void)_t_U32_1534;
    ;
    self->count = _t_U32_1534;
    ;
    U32 _t_U32_1535 = 0;
    (void)_t_U32_1535;
    other->count = _t_U32_1535;
    ;
    Vec_delete(other, &(Bool){0});
}

void Vec_move_from(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_1558 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_1558;
    Bool _t_Bool_1559 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_1559;
    Bool _t_Bool_1560 = not(_t_Bool_1558);
    (void)_t_Bool_1560;
    ;
    Bool _t_Bool_1561 = not(_t_Bool_1559);
    (void)_t_Bool_1561;
    ;
    Bool _t_Bool_1562 = or(_t_Bool_1560, _t_Bool_1561);
    (void)_t_Bool_1562;
    ;
    ;
    if (_t_Bool_1562) {
        Str *_t_Str_1536 = Str_lit("Str", 3ULL);
        (void)_t_Str_1536;
        U32 _t_U32_1537 = 1;
        (void)_t_U32_1537;
        Array *_va_Array_59 = Array_new(_t_Str_1536, &_t_U32_1537);
        (void)_va_Array_59;
        Str_delete(_t_Str_1536, &(Bool){1});
        ;
        U32 _t_U32_1538 = 0;
        (void)_t_U32_1538;
        Str *_t_Str_1539 = Str_lit("Vec.move_from: incompatible vecs", 32ULL);
        (void)_t_Str_1539;
        Array_set(_va_Array_59, &_t_U32_1538, _t_Str_1539);
        ;
        Str *_t_Str_1540 = Str_lit("./src/core/vec.til:93:19", 24ULL);
        (void)_t_Str_1540;
        panic(_t_Str_1540, _va_Array_59);
        Str_delete(_t_Str_1540, &(Bool){1});
    }
    ;
    Bool _t_Bool_1563 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1563;
    Str *_t_Str_1564 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1564;
    Bool _t_Bool_1565 = Str_eq(&self->elem_type, _t_Str_1564);
    (void)_t_Bool_1565;
    Str_delete(_t_Str_1564, &(Bool){1});
    Bool _t_Bool_1566 = not(_t_Bool_1563);
    (void)_t_Bool_1566;
    ;
    Bool _t_Bool_1567 = not(_t_Bool_1565);
    (void)_t_Bool_1567;
    ;
    Bool _t_Bool_1568 = and(_t_Bool_1566, _t_Bool_1567);
    (void)_t_Bool_1568;
    ;
    ;
    if (_t_Bool_1568) {
        {
            U32 _re_U32_1541 = self->count;
            (void)_re_U32_1541;
            U32 _rc_U32_1541 = 0;
            (void)_rc_U32_1541;
            Bool _t_Bool_1550 = U32_lte(&_rc_U32_1541, &_re_U32_1541);
            (void)_t_Bool_1550;
            if (_t_Bool_1550) {
                while (1) {
                    Bool _wcond_Bool_1542 = U32_lt(&_rc_U32_1541, &_re_U32_1541);
                    (void)_wcond_Bool_1542;
                    if (_wcond_Bool_1542) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1541);
                    (void)i;
                    U32_inc(&_rc_U32_1541);
                    U32 _t_U64_1543 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1543;
                    ;
                    void *_t_v_1544 = ptr_add(self->data, _t_U64_1543);
                    (void)_t_v_1544;
                    Bool _t_Bool_1545 = 0;
                    (void)_t_Bool_1545;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1544, &_t_Bool_1545);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1546 = U32_gt(&_rc_U32_1541, &_re_U32_1541);
                    (void)_wcond_Bool_1546;
                    if (_wcond_Bool_1546) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1541);
                    (void)i;
                    U32_dec(&_rc_U32_1541);
                    U32 _t_U64_1547 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1547;
                    ;
                    void *_t_v_1548 = ptr_add(self->data, _t_U64_1547);
                    (void)_t_v_1548;
                    Bool _t_Bool_1549 = 0;
                    (void)_t_Bool_1549;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1548, &_t_Bool_1549);
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
    Bool _t_Bool_1569 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_1569;
    if (_t_Bool_1569) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_1551 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_1551;
            if (_wcond_Bool_1551) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_1552 = 2;
            (void)_t_U32_1552;
            U32 _t_U32_1553 = U32_mul(new_cap, _t_U32_1552);
            (void)_t_U32_1553;
            ;
            new_cap = _t_U32_1553;
            ;
        }
        U32 _t_U64_1554 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1554;
        void * _t_v_1555 = realloc(self->data, _t_U64_1554);
        (void)_t_v_1555;
        ;
        self->data = _t_v_1555;
        U32 _t_U32_1556 = U32_clone(&new_cap);
        (void)_t_U32_1556;
        ;
        self->cap = _t_U32_1556;
        ;
    }
    ;
    U32 _t_U32_1570 = 0;
    (void)_t_U32_1570;
    Bool _t_Bool_1571 = U32_gt(&needed, &_t_U32_1570);
    (void)_t_Bool_1571;
    ;
    if (_t_Bool_1571) {
        U32 _t_U64_1557 = U32_mul(needed, self->elem_size);
        (void)_t_U64_1557;
        memcpy(self->data, other->data, _t_U64_1557);
        ;
    }
    ;
    U32 _t_U32_1572 = U32_clone(&needed);
    (void)_t_U32_1572;
    ;
    self->count = _t_U32_1572;
    ;
    U32 _t_U32_1573 = 0;
    (void)_t_U32_1573;
    other->count = _t_U32_1573;
    ;
}

void * Vec_get(Vec * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_1587 = U32_gte(i, &self->count);
    (void)_t_Bool_1587;
    if (_t_Bool_1587) {
        Str *_t_Str_1574 = Str_lit("Str", 3ULL);
        (void)_t_Str_1574;
        U32 _t_U32_1575 = 5;
        (void)_t_U32_1575;
        Array *_va_Array_60 = Array_new(_t_Str_1574, &_t_U32_1575);
        (void)_va_Array_60;
        Str_delete(_t_Str_1574, &(Bool){1});
        ;
        U32 _t_U32_1576 = 0;
        (void)_t_U32_1576;
        Str *_t_Str_1577 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t_Str_1577;
        Array_set(_va_Array_60, &_t_U32_1576, _t_Str_1577);
        ;
        U32 _t_U32_1578 = 1;
        (void)_t_U32_1578;
        Str *_t_Str_1579 = U32_to_str(i);
        (void)_t_Str_1579;
        Array_set(_va_Array_60, &_t_U32_1578, _t_Str_1579);
        ;
        U32 _t_U32_1580 = 2;
        (void)_t_U32_1580;
        Str *_t_Str_1581 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1581;
        Array_set(_va_Array_60, &_t_U32_1580, _t_Str_1581);
        ;
        U32 _t_U32_1582 = 3;
        (void)_t_U32_1582;
        Str *_t_Str_1583 = U32_to_str(&self->count);
        (void)_t_Str_1583;
        Array_set(_va_Array_60, &_t_U32_1582, _t_Str_1583);
        ;
        U32 _t_U32_1584 = 4;
        (void)_t_U32_1584;
        Str *_t_Str_1585 = Str_lit(")", 1ULL);
        (void)_t_Str_1585;
        Array_set(_va_Array_60, &_t_U32_1584, _t_Str_1585);
        ;
        Str *_t_Str_1586 = Str_lit("./src/core/vec.til:120:19", 25ULL);
        (void)_t_Str_1586;
        panic(_t_Str_1586, _va_Array_60);
        Str_delete(_t_Str_1586, &(Bool){1});
    }
    ;
    U32 _t_U64_1588 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1588;
    void *_t_v_1589 = ptr_add(self->data, _t_U64_1588);
    (void)_t_v_1589;
    ;
    return _t_v_1589;
}

void * Vec_pop(Vec * self) {
    (void)self;
    U32 _t_U32_1595 = 0;
    (void)_t_U32_1595;
    Bool _t_Bool_1596 = U32_eq(self->count, _t_U32_1595);
    (void)_t_Bool_1596;
    ;
    if (_t_Bool_1596) {
        Str *_t_Str_1590 = Str_lit("Str", 3ULL);
        (void)_t_Str_1590;
        U32 _t_U32_1591 = 1;
        (void)_t_U32_1591;
        Array *_va_Array_61 = Array_new(_t_Str_1590, &_t_U32_1591);
        (void)_va_Array_61;
        Str_delete(_t_Str_1590, &(Bool){1});
        ;
        U32 _t_U32_1592 = 0;
        (void)_t_U32_1592;
        Str *_t_Str_1593 = Str_lit("Vec.pop: empty vec", 18ULL);
        (void)_t_Str_1593;
        Array_set(_va_Array_61, &_t_U32_1592, _t_Str_1593);
        ;
        Str *_t_Str_1594 = Str_lit("./src/core/vec.til:129:19", 25ULL);
        (void)_t_Str_1594;
        panic(_t_Str_1594, _va_Array_61);
        Str_delete(_t_Str_1594, &(Bool){1});
    }
    ;
    U32 _t_U32_1597 = 1;
    (void)_t_U32_1597;
    U32 last = U32_sub(self->count, _t_U32_1597);
    (void)last;
    ;
    void * out = malloc(self->elem_size);
    (void)out;
    U32 _t_U64_1598 = U32_mul(last, self->elem_size);
    (void)_t_U64_1598;
    void *_t_v_1599 = ptr_add(self->data, _t_U64_1598);
    (void)_t_v_1599;
    memcpy(out, _t_v_1599, self->elem_size);
    ;
    U32 _t_U32_1600 = U32_clone(&last);
    (void)_t_U32_1600;
    ;
    self->count = _t_U32_1600;
    ;
    return out;
}

Vec * Vec_take_prefix(Vec * self, U32 * n) {
    (void)self;
    (void)n;
    Bool _t_Bool_1619 = U32_gt(n, &self->count);
    (void)_t_Bool_1619;
    if (_t_Bool_1619) {
        Str *_t_Str_1601 = Str_lit("Str", 3ULL);
        (void)_t_Str_1601;
        U32 _t_U32_1602 = 5;
        (void)_t_U32_1602;
        Array *_va_Array_62 = Array_new(_t_Str_1601, &_t_U32_1602);
        (void)_va_Array_62;
        Str_delete(_t_Str_1601, &(Bool){1});
        ;
        U32 _t_U32_1603 = 0;
        (void)_t_U32_1603;
        Str *_t_Str_1604 = Str_lit("Vec.take_prefix: count ", 23ULL);
        (void)_t_Str_1604;
        Array_set(_va_Array_62, &_t_U32_1603, _t_Str_1604);
        ;
        U32 _t_U32_1605 = 1;
        (void)_t_U32_1605;
        Str *_t_Str_1606 = U32_to_str(n);
        (void)_t_Str_1606;
        Array_set(_va_Array_62, &_t_U32_1605, _t_Str_1606);
        ;
        U32 _t_U32_1607 = 2;
        (void)_t_U32_1607;
        Str *_t_Str_1608 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1608;
        Array_set(_va_Array_62, &_t_U32_1607, _t_Str_1608);
        ;
        U32 _t_U32_1609 = 3;
        (void)_t_U32_1609;
        Str *_t_Str_1610 = U32_to_str(&self->count);
        (void)_t_Str_1610;
        Array_set(_va_Array_62, &_t_U32_1609, _t_Str_1610);
        ;
        U32 _t_U32_1611 = 4;
        (void)_t_U32_1611;
        Str *_t_Str_1612 = Str_lit(")", 1ULL);
        (void)_t_Str_1612;
        Array_set(_va_Array_62, &_t_U32_1611, _t_Str_1612);
        ;
        Str *_t_Str_1613 = Str_lit("./src/core/vec.til:142:19", 25ULL);
        (void)_t_Str_1613;
        panic(_t_Str_1613, _va_Array_62);
        Str_delete(_t_Str_1613, &(Bool){1});
    }
    ;
    U32 prefix_cap = 1;
    (void)prefix_cap;
    U32 _t_U32_1620 = 0;
    (void)_t_U32_1620;
    Bool _t_Bool_1621 = U32_gt(n, &_t_U32_1620);
    (void)_t_Bool_1621;
    ;
    if (_t_Bool_1621) {
        U32 _t_U32_1614 = U32_clone(n);
        (void)_t_U32_1614;
        prefix_cap = _t_U32_1614;
        ;
    }
    ;
    U32 _t_U64_1622 = U32_mul(prefix_cap, self->elem_size);
    (void)_t_U64_1622;
    void * prefix_data = malloc(_t_U64_1622);
    (void)prefix_data;
    ;
    U32 _t_U32_1623 = 0;
    (void)_t_U32_1623;
    Bool _t_Bool_1624 = U32_gt(n, &_t_U32_1623);
    (void)_t_Bool_1624;
    ;
    if (_t_Bool_1624) {
        U32 _t_U64_1615 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_1615;
        memcpy(prefix_data, self->data, _t_U64_1615);
        ;
    }
    ;
    U32 tail_count = U32_sub(self->count, DEREF(n));
    (void)tail_count;
    U32 _t_U32_1625 = 0;
    (void)_t_U32_1625;
    Bool _t_Bool_1626 = U32_gt(&tail_count, &_t_U32_1625);
    (void)_t_Bool_1626;
    ;
    if (_t_Bool_1626) {
        U32 _t_U64_1616 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_1616;
        void *_t_v_1617 = ptr_add(self->data, _t_U64_1616);
        (void)_t_v_1617;
        U32 _t_U64_1618 = U32_mul(tail_count, self->elem_size);
        (void)_t_U64_1618;
        memmove(self->data, _t_v_1617, _t_U64_1618);
        ;
        ;
    }
    ;
    U32 _t_U32_1627 = U32_clone(&tail_count);
    (void)_t_U32_1627;
    ;
    self->count = _t_U32_1627;
    ;
    Vec *_t_Vec_1628 = malloc(sizeof(Vec));
    _t_Vec_1628->data = prefix_data;
    _t_Vec_1628->count = DEREF(n);
    _t_Vec_1628->cap = prefix_cap;
    _t_Vec_1628->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_1628->elem_type = *_ca; free(_ca); }
    _t_Vec_1628->elem_clone = (void *)self->elem_clone;
    _t_Vec_1628->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_1628;
    ;
    return _t_Vec_1628;
}

void Vec_set(Vec * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_1642 = U32_gte(i, &self->count);
    (void)_t_Bool_1642;
    if (_t_Bool_1642) {
        Str *_t_Str_1629 = Str_lit("Str", 3ULL);
        (void)_t_Str_1629;
        U32 _t_U32_1630 = 5;
        (void)_t_U32_1630;
        Array *_va_Array_63 = Array_new(_t_Str_1629, &_t_U32_1630);
        (void)_va_Array_63;
        Str_delete(_t_Str_1629, &(Bool){1});
        ;
        U32 _t_U32_1631 = 0;
        (void)_t_U32_1631;
        Str *_t_Str_1632 = Str_lit("Vec.set: index ", 15ULL);
        (void)_t_Str_1632;
        Array_set(_va_Array_63, &_t_U32_1631, _t_Str_1632);
        ;
        U32 _t_U32_1633 = 1;
        (void)_t_U32_1633;
        Str *_t_Str_1634 = U32_to_str(i);
        (void)_t_Str_1634;
        Array_set(_va_Array_63, &_t_U32_1633, _t_Str_1634);
        ;
        U32 _t_U32_1635 = 2;
        (void)_t_U32_1635;
        Str *_t_Str_1636 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1636;
        Array_set(_va_Array_63, &_t_U32_1635, _t_Str_1636);
        ;
        U32 _t_U32_1637 = 3;
        (void)_t_U32_1637;
        Str *_t_Str_1638 = U32_to_str(&self->count);
        (void)_t_Str_1638;
        Array_set(_va_Array_63, &_t_U32_1637, _t_Str_1638);
        ;
        U32 _t_U32_1639 = 4;
        (void)_t_U32_1639;
        Str *_t_Str_1640 = Str_lit(")", 1ULL);
        (void)_t_Str_1640;
        Array_set(_va_Array_63, &_t_U32_1639, _t_Str_1640);
        ;
        Str *_t_Str_1641 = Str_lit("./src/core/vec.til:166:19", 25ULL);
        (void)_t_Str_1641;
        panic(_t_Str_1641, _va_Array_63);
        Str_delete(_t_Str_1641, &(Bool){1});
    }
    ;
    U32 _t_U64_1643 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_1643;
    void *_t_v_1644 = ptr_add(self->data, _t_U64_1643);
    (void)_t_v_1644;
    memcpy(_t_v_1644, val, self->elem_size);
    ;
    free(val);
}

void Vec_push_take(Vec * self, Vec * src, U32 i) {
    (void)self;
    (void)src;
    (void)i;
    Bool _t_Bool_1667 = U32_gte(&i, &src->count);
    (void)_t_Bool_1667;
    if (_t_Bool_1667) {
        Str *_t_Str_1645 = Str_lit("Str", 3ULL);
        (void)_t_Str_1645;
        U32 _t_U32_1646 = 5;
        (void)_t_U32_1646;
        Array *_va_Array_64 = Array_new(_t_Str_1645, &_t_U32_1646);
        (void)_va_Array_64;
        Str_delete(_t_Str_1645, &(Bool){1});
        ;
        U32 _t_U32_1647 = 0;
        (void)_t_U32_1647;
        Str *_t_Str_1648 = Str_lit("Vec.push_take: index ", 21ULL);
        (void)_t_Str_1648;
        Array_set(_va_Array_64, &_t_U32_1647, _t_Str_1648);
        ;
        U32 _t_U32_1649 = 1;
        (void)_t_U32_1649;
        Str *_t_Str_1650 = U32_to_str(&i);
        (void)_t_Str_1650;
        Array_set(_va_Array_64, &_t_U32_1649, _t_Str_1650);
        ;
        U32 _t_U32_1651 = 2;
        (void)_t_U32_1651;
        Str *_t_Str_1652 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_1652;
        Array_set(_va_Array_64, &_t_U32_1651, _t_Str_1652);
        ;
        U32 _t_U32_1653 = 3;
        (void)_t_U32_1653;
        Str *_t_Str_1654 = U32_to_str(&src->count);
        (void)_t_Str_1654;
        Array_set(_va_Array_64, &_t_U32_1653, _t_Str_1654);
        ;
        U32 _t_U32_1655 = 4;
        (void)_t_U32_1655;
        Str *_t_Str_1656 = Str_lit(")", 1ULL);
        (void)_t_Str_1656;
        Array_set(_va_Array_64, &_t_U32_1655, _t_Str_1656);
        ;
        Str *_t_Str_1657 = Str_lit("./src/core/vec.til:177:19", 25ULL);
        (void)_t_Str_1657;
        panic(_t_Str_1657, _va_Array_64);
        Str_delete(_t_Str_1657, &(Bool){1});
    }
    ;
    Bool _t_Bool_1668 = U32_eq(self->elem_size, src->elem_size);
    (void)_t_Bool_1668;
    Bool _t_Bool_1669 = Str_eq(&self->elem_type, &src->elem_type);
    (void)_t_Bool_1669;
    Bool _t_Bool_1670 = not(_t_Bool_1668);
    (void)_t_Bool_1670;
    ;
    Bool _t_Bool_1671 = not(_t_Bool_1669);
    (void)_t_Bool_1671;
    ;
    Bool _t_Bool_1672 = or(_t_Bool_1670, _t_Bool_1671);
    (void)_t_Bool_1672;
    ;
    ;
    if (_t_Bool_1672) {
        Str *_t_Str_1658 = Str_lit("Str", 3ULL);
        (void)_t_Str_1658;
        U32 _t_U32_1659 = 1;
        (void)_t_U32_1659;
        Array *_va_Array_65 = Array_new(_t_Str_1658, &_t_U32_1659);
        (void)_va_Array_65;
        Str_delete(_t_Str_1658, &(Bool){1});
        ;
        U32 _t_U32_1660 = 0;
        (void)_t_U32_1660;
        Str *_t_Str_1661 = Str_lit("Vec.push_take: incompatible vecs", 32ULL);
        (void)_t_Str_1661;
        Array_set(_va_Array_65, &_t_U32_1660, _t_Str_1661);
        ;
        Str *_t_Str_1662 = Str_lit("./src/core/vec.til:180:19", 25ULL);
        (void)_t_Str_1662;
        panic(_t_Str_1662, _va_Array_65);
        Str_delete(_t_Str_1662, &(Bool){1});
    }
    ;
    Bool _t_Bool_1673 = U32_eq(self->count, self->cap);
    (void)_t_Bool_1673;
    if (_t_Bool_1673) {
        U32 _t_U32_1663 = 2;
        (void)_t_U32_1663;
        U32 new_cap = U32_mul(self->cap, _t_U32_1663);
        (void)new_cap;
        ;
        U32 _t_U64_1664 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_1664;
        void * _t_v_1665 = realloc(self->data, _t_U64_1664);
        (void)_t_v_1665;
        ;
        self->data = _t_v_1665;
        U32 _t_U32_1666 = U32_clone(&new_cap);
        (void)_t_U32_1666;
        ;
        self->cap = _t_U32_1666;
        ;
    }
    ;
    U32 _t_U64_1674 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_1674;
    U32 _t_U64_1675 = U32_mul(i, src->elem_size);
    (void)_t_U64_1675;
    void *_t_v_1676 = ptr_add(self->data, _t_U64_1674);
    (void)_t_v_1676;
    void *_t_v_1677 = ptr_add(src->data, _t_U64_1675);
    (void)_t_v_1677;
    memcpy(_t_v_1676, _t_v_1677, self->elem_size);
    ;
    ;
    U32 _t_U64_1678 = U32_mul(i, src->elem_size);
    (void)_t_U64_1678;
    void *_t_v_1679 = ptr_add(src->data, _t_U64_1678);
    (void)_t_v_1679;
    I32 _t_I32_1680 = 0;
    (void)_t_I32_1680;
    memset(_t_v_1679, _t_I32_1680, src->elem_size);
    ;
    ;
    U32 _t_U32_1681 = 1;
    (void)_t_U32_1681;
    U32 _t_U32_1682 = U32_add(self->count, _t_U32_1681);
    (void)_t_U32_1682;
    ;
    self->count = _t_U32_1682;
    ;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_1694 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1694;
    Str *_t_Str_1695 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1695;
    Bool _t_Bool_1696 = Str_eq(&self->elem_type, _t_Str_1695);
    (void)_t_Bool_1696;
    Str_delete(_t_Str_1695, &(Bool){1});
    Bool _t_Bool_1697 = not(_t_Bool_1694);
    (void)_t_Bool_1697;
    ;
    Bool _t_Bool_1698 = not(_t_Bool_1696);
    (void)_t_Bool_1698;
    ;
    Bool _t_Bool_1699 = and(_t_Bool_1697, _t_Bool_1698);
    (void)_t_Bool_1699;
    ;
    ;
    if (_t_Bool_1699) {
        {
            U32 _re_U32_1683 = self->count;
            (void)_re_U32_1683;
            U32 _rc_U32_1683 = 0;
            (void)_rc_U32_1683;
            Bool _t_Bool_1692 = U32_lte(&_rc_U32_1683, &_re_U32_1683);
            (void)_t_Bool_1692;
            if (_t_Bool_1692) {
                while (1) {
                    Bool _wcond_Bool_1684 = U32_lt(&_rc_U32_1683, &_re_U32_1683);
                    (void)_wcond_Bool_1684;
                    if (_wcond_Bool_1684) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1683);
                    (void)i;
                    U32_inc(&_rc_U32_1683);
                    U32 _t_U64_1685 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1685;
                    ;
                    void *_t_v_1686 = ptr_add(self->data, _t_U64_1685);
                    (void)_t_v_1686;
                    Bool _t_Bool_1687 = 0;
                    (void)_t_Bool_1687;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1686, &_t_Bool_1687);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1688 = U32_gt(&_rc_U32_1683, &_re_U32_1683);
                    (void)_wcond_Bool_1688;
                    if (_wcond_Bool_1688) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1683);
                    (void)i;
                    U32_dec(&_rc_U32_1683);
                    U32 _t_U64_1689 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1689;
                    ;
                    void *_t_v_1690 = ptr_add(self->data, _t_U64_1689);
                    (void)_t_v_1690;
                    Bool _t_Bool_1691 = 0;
                    (void)_t_Bool_1691;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_1690, &_t_Bool_1691);
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
    Bool _t_Bool_1700 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1700;
    Bool _t_Bool_1701 = not(_t_Bool_1700);
    (void)_t_Bool_1701;
    ;
    if (_t_Bool_1701) {
        Bool _t_Bool_1693 = 0;
        (void)_t_Bool_1693;
        Str_delete(&self->elem_type, &_t_Bool_1693);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U32 _t_U64_1715 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_1715;
    void * new_data = malloc(_t_U64_1715);
    (void)new_data;
    ;
    Bool _t_Bool_1716 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_1716;
    Str *_t_Str_1717 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_1717;
    Bool _t_Bool_1718 = Str_eq(&self->elem_type, _t_Str_1717);
    (void)_t_Bool_1718;
    Str_delete(_t_Str_1717, &(Bool){1});
    Bool _t_Bool_1719 = not(_t_Bool_1716);
    (void)_t_Bool_1719;
    ;
    Bool _t_Bool_1720 = not(_t_Bool_1718);
    (void)_t_Bool_1720;
    ;
    Bool _t_Bool_1721 = and(_t_Bool_1719, _t_Bool_1720);
    (void)_t_Bool_1721;
    ;
    ;
    if (_t_Bool_1721) {
        {
            U32 _re_U32_1702 = self->count;
            (void)_re_U32_1702;
            U32 _rc_U32_1702 = 0;
            (void)_rc_U32_1702;
            Bool _t_Bool_1713 = U32_lte(&_rc_U32_1702, &_re_U32_1702);
            (void)_t_Bool_1713;
            if (_t_Bool_1713) {
                while (1) {
                    Bool _wcond_Bool_1703 = U32_lt(&_rc_U32_1702, &_re_U32_1702);
                    (void)_wcond_Bool_1703;
                    if (_wcond_Bool_1703) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1702);
                    (void)i;
                    U32_inc(&_rc_U32_1702);
                    U32 _t_U64_1704 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1704;
                    void *_t_v_1705 = ptr_add(self->data, _t_U64_1704);
                    (void)_t_v_1705;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1705);
                    (void)cloned;
                    ;
                    U32 _t_U64_1706 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1706;
                    ;
                    void *_t_v_1707 = ptr_add(new_data, _t_U64_1706);
                    (void)_t_v_1707;
                    memcpy(_t_v_1707, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_1708 = U32_gt(&_rc_U32_1702, &_re_U32_1702);
                    (void)_wcond_Bool_1708;
                    if (_wcond_Bool_1708) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_1702);
                    (void)i;
                    U32_dec(&_rc_U32_1702);
                    U32 _t_U64_1709 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1709;
                    void *_t_v_1710 = ptr_add(self->data, _t_U64_1709);
                    (void)_t_v_1710;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_1710);
                    (void)cloned;
                    ;
                    U32 _t_U64_1711 = U32_mul(i, self->elem_size);
                    (void)_t_U64_1711;
                    ;
                    void *_t_v_1712 = ptr_add(new_data, _t_U64_1711);
                    (void)_t_v_1712;
                    memcpy(_t_v_1712, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            }
            ;
            ;
            ;
        }
    } else {
        U32 _t_U64_1714 = U32_mul(self->count, self->elem_size);
        (void)_t_U64_1714;
        memcpy(new_data, self->data, _t_U64_1714);
        ;
    }
    ;
    Vec *_t_Vec_1722 = malloc(sizeof(Vec));
    _t_Vec_1722->data = new_data;
    _t_Vec_1722->count = self->count;
    _t_Vec_1722->cap = self->cap;
    _t_Vec_1722->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_1722->elem_type = *_ca; free(_ca); }
    _t_Vec_1722->elem_clone = (void *)self->elem_clone;
    _t_Vec_1722->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_1722;
    return _t_Vec_1722;
}

U32 Vec_size(void) {
    I64 _t_I64_1723 = 56;
    (void)_t_I64_1723;
    return _t_I64_1723;
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    (void)total;
    {
        Array *_fc_Array_1724 = parts;
        (void)_fc_Array_1724;
        U32 _fi_USize_1724 = 0;
        (void)_fi_USize_1724;
        while (1) {
            U32 _t_U32_1726; { U32 *_hp = (U32 *)Array_len(_fc_Array_1724); _t_U32_1726 = *_hp; free(_hp); }
            (void)_t_U32_1726;
            Bool _wcond_Bool_1725 = U32_lt(&_fi_USize_1724, &_t_U32_1726);
            (void)_wcond_Bool_1725;
            ;
            if (_wcond_Bool_1725) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_1724, &_fi_USize_1724);
            (void)s;
            U32 _t_U32_1727 = 1;
            (void)_t_U32_1727;
            U32 _t_U32_1728 = U32_add(_fi_USize_1724, _t_U32_1727);
            (void)_t_U32_1728;
            ;
            _fi_USize_1724 = _t_U32_1728;
            ;
            U32 _t_U32_1729 = Str_len(s);
            (void)_t_U32_1729;
            U32 _t_U32_1730 = U32_add(total, _t_U32_1729);
            (void)_t_U32_1730;
            ;
            total = _t_U32_1730;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    (void)out;
    ;
    {
        Array *_fc_Array_1731 = parts;
        (void)_fc_Array_1731;
        U32 _fi_USize_1731 = 0;
        (void)_fi_USize_1731;
        while (1) {
            U32 _t_U32_1733; { U32 *_hp = (U32 *)Array_len(_fc_Array_1731); _t_U32_1733 = *_hp; free(_hp); }
            (void)_t_U32_1733;
            Bool _wcond_Bool_1732 = U32_lt(&_fi_USize_1731, &_t_U32_1733);
            (void)_wcond_Bool_1732;
            ;
            if (_wcond_Bool_1732) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_1731, &_fi_USize_1731);
            (void)s;
            U32 _t_U32_1734 = 1;
            (void)_t_U32_1734;
            U32 _t_U32_1735 = U32_add(_fi_USize_1731, _t_U32_1734);
            (void)_t_U32_1735;
            ;
            _fi_USize_1731 = _t_U32_1735;
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
    Bool _t_Bool_1741 = U32_gte(i, &self->count);
    (void)_t_Bool_1741;
    if (_t_Bool_1741) {
        Str *_t_Str_1736 = Str_lit("Str", 3ULL);
        (void)_t_Str_1736;
        U32 _t_U32_1737 = 1;
        (void)_t_U32_1737;
        Array *_va_Array_66 = Array_new(_t_Str_1736, &_t_U32_1737);
        (void)_va_Array_66;
        Str_delete(_t_Str_1736, &(Bool){1});
        ;
        U32 _t_U32_1738 = 0;
        (void)_t_U32_1738;
        Str *_t_Str_1739 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t_Str_1739;
        Array_set(_va_Array_66, &_t_U32_1738, _t_Str_1739);
        ;
        Str *_t_Str_1740 = Str_lit("./src/core/str.til:39:19", 24ULL);
        (void)_t_Str_1740;
        panic(_t_Str_1740, _va_Array_66);
        Str_delete(_t_Str_1740, &(Bool){1});
    }
    ;
    void *_t_v_1742 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_1742;
    return _t_v_1742;
}

U8 * Str_byte_at(Str * self, U32 * i) {
    (void)self;
    (void)i;
    void *_t_v_1743 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_1743;
    return _t_v_1743;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    (void)min_len;
    Bool _t_Bool_1752 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_1752;
    if (_t_Bool_1752) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_1744 = U32_clone(&min_len);
        (void)_re_U32_1744;
        U32 _rc_U32_1744 = 0;
        (void)_rc_U32_1744;
        Bool _t_Bool_1751 = U32_lte(&_rc_U32_1744, &_re_U32_1744);
        (void)_t_Bool_1751;
        if (_t_Bool_1751) {
            while (1) {
                Bool _wcond_Bool_1745 = U32_lt(&_rc_U32_1744, &_re_U32_1744);
                (void)_wcond_Bool_1745;
                if (_wcond_Bool_1745) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1744);
                (void)i;
                U32_inc(&_rc_U32_1744);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_1746 = 0;
                (void)_t_I64_1746;
                Bool _t_Bool_1747 = I64_neq(&c, &_t_I64_1746);
                (void)_t_Bool_1747;
                ;
                if (_t_Bool_1747) {
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
                Bool _wcond_Bool_1748 = U32_gt(&_rc_U32_1744, &_re_U32_1744);
                (void)_wcond_Bool_1748;
                if (_wcond_Bool_1748) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1744);
                (void)i;
                U32_dec(&_rc_U32_1744);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_1749 = 0;
                (void)_t_I64_1749;
                Bool _t_Bool_1750 = I64_neq(&c, &_t_I64_1749);
                (void)_t_Bool_1750;
                ;
                if (_t_Bool_1750) {
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
    I64 _t_I64_1753 = U32_cmp(a->count, b->count);
    (void)_t_I64_1753;
    return _t_I64_1753;
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_1754 = U32_add(a->count, b->count);
    (void)_t_U32_1754;
    Str *out = Str_with_capacity(&_t_U32_1754);
    (void)out;
    ;
    Str_push_str(out, a);
    Str_push_str(out, b);
    return out;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_1755 = 1;
    (void)_t_U32_1755;
    U32 _t_U64_1756 = U32_add(DEREF(n), _t_U32_1755);
    (void)_t_U64_1756;
    ;
    void * buf = malloc(_t_U64_1756);
    (void)buf;
    ;
    I32 _t_I32_1757 = 0;
    (void)_t_I32_1757;
    U64 _t_U64_1758 = 1;
    (void)_t_U64_1758;
    memset(buf, _t_I32_1757, _t_U64_1758);
    ;
    ;
    I64 _t_I64_1759 = 0;
    (void)_t_I64_1759;
    Str *_t_Str_1760 = malloc(sizeof(Str));
    _t_Str_1760->c_str = buf;
    _t_Str_1760->count = _t_I64_1759;
    _t_Str_1760->cap = DEREF(n);
    (void)_t_Str_1760;
    ;
    return _t_Str_1760;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_1771 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_1771;
    if (_t_Bool_1771) {
        Str *_t_Str_1761 = Str_lit("Str", 3ULL);
        (void)_t_Str_1761;
        U32 _t_U32_1762 = 1;
        (void)_t_U32_1762;
        Array *_va_Array_67 = Array_new(_t_Str_1761, &_t_U32_1762);
        (void)_va_Array_67;
        Str_delete(_t_Str_1761, &(Bool){1});
        ;
        U32 _t_U32_1763 = 0;
        (void)_t_U32_1763;
        Str *_t_Str_1764 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t_Str_1764;
        Array_set(_va_Array_67, &_t_U32_1763, _t_Str_1764);
        ;
        Str *_t_Str_1765 = Str_lit("./src/core/str.til:82:19", 24ULL);
        (void)_t_Str_1765;
        panic(_t_Str_1765, _va_Array_67);
        Str_delete(_t_Str_1765, &(Bool){1});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    (void)new_len;
    Bool _t_Bool_1772 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_1772;
    if (_t_Bool_1772) {
        Str *_t_Str_1766 = Str_lit("Str", 3ULL);
        (void)_t_Str_1766;
        U32 _t_U32_1767 = 1;
        (void)_t_U32_1767;
        Array *_va_Array_68 = Array_new(_t_Str_1766, &_t_U32_1767);
        (void)_va_Array_68;
        Str_delete(_t_Str_1766, &(Bool){1});
        ;
        U32 _t_U32_1768 = 0;
        (void)_t_U32_1768;
        Str *_t_Str_1769 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t_Str_1769;
        Array_set(_va_Array_68, &_t_U32_1768, _t_Str_1769);
        ;
        Str *_t_Str_1770 = Str_lit("./src/core/str.til:86:19", 24ULL);
        (void)_t_Str_1770;
        panic(_t_Str_1770, _va_Array_68);
        Str_delete(_t_Str_1770, &(Bool){1});
    }
    ;
    void *_t_v_1773 = ptr_add(self->c_str, self->count);
    (void)_t_v_1773;
    memcpy(_t_v_1773, s->c_str, s->count);
    U32 _t_U32_1774 = U32_clone(&new_len);
    (void)_t_U32_1774;
    self->count = _t_U32_1774;
    ;
    void *_t_v_1775 = ptr_add(self->c_str, new_len);
    (void)_t_v_1775;
    I32 _t_I32_1776 = 0;
    (void)_t_I32_1776;
    U64 _t_U64_1777 = 1;
    (void)_t_U64_1777;
    memset(_t_v_1775, _t_I32_1776, _t_U64_1777);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_1778 = 1;
    (void)_t_U32_1778;
    U32 _t_U64_1779 = U32_add(val->count, _t_U32_1778);
    (void)_t_U64_1779;
    ;
    void * new_data = malloc(_t_U64_1779);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_1780 = ptr_add(new_data, val->count);
    (void)_t_v_1780;
    I32 _t_I32_1781 = 0;
    (void)_t_I32_1781;
    U64 _t_U64_1782 = 1;
    (void)_t_U64_1782;
    memset(_t_v_1780, _t_I32_1781, _t_U64_1782);
    ;
    ;
    Str *_t_Str_1783 = malloc(sizeof(Str));
    _t_Str_1783->c_str = new_data;
    _t_Str_1783->count = val->count;
    _t_Str_1783->cap = val->count;
    (void)_t_Str_1783;
    return _t_Str_1783;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_1784 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_1784;
    if (_t_Bool_1784) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t_Str_1785 = Str_clone(val);
    (void)_t_Str_1785;
    return _t_Str_1785;
}

Str * Str_substr(Str * s, U32 * start, U32 * n) {
    (void)s;
    (void)start;
    (void)n;
    U32 st = U32_clone(start);
    (void)st;
    U32 ln = U32_clone(n);
    (void)ln;
    Bool _t_Bool_1787 = U32_gt(&st, &s->count);
    (void)_t_Bool_1787;
    if (_t_Bool_1787) {
        st = s->count;
    }
    ;
    U32 _t_U32_1788 = U32_add(st, ln);
    (void)_t_U32_1788;
    Bool _t_Bool_1789 = U32_gt(&_t_U32_1788, &s->count);
    (void)_t_Bool_1789;
    ;
    if (_t_Bool_1789) {
        U32 _t_U32_1786 = U32_sub(s->count, st);
        (void)_t_U32_1786;
        ln = _t_U32_1786;
        ;
    }
    ;
    void *_t_v_1790 = ptr_add(s->c_str, st);
    (void)_t_v_1790;
    Str *_t_Str_1791 = malloc(sizeof(Str));
    _t_Str_1791->c_str = _t_v_1790;
    _t_Str_1791->count = ln;
    _t_Str_1791->cap = CAP_VIEW;
    (void)_t_Str_1791;
    ;
    ;
    return _t_Str_1791;
}

Bool Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_1822 = 0;
    (void)_t_U32_1822;
    Bool _t_Bool_1823 = U32_eq(b->count, _t_U32_1822);
    (void)_t_Bool_1823;
    ;
    if (_t_Bool_1823) {
        Bool _t_Bool_1792 = 1;
        (void)_t_Bool_1792;
        ;
        return _t_Bool_1792;
    }
    ;
    Bool _t_Bool_1824 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_1824;
    if (_t_Bool_1824) {
        Bool _t_Bool_1793 = 0;
        (void)_t_Bool_1793;
        ;
        return _t_Bool_1793;
    }
    ;
    {
        U32 _t_U32_1819 = U32_sub(a->count, b->count);
        (void)_t_U32_1819;
        U32 _t_U32_1820 = 1;
        (void)_t_U32_1820;
        U32 _re_U32_1794 = U32_add(_t_U32_1819, _t_U32_1820);
        (void)_re_U32_1794;
        ;
        ;
        U32 _rc_U32_1794 = 0;
        (void)_rc_U32_1794;
        Bool _t_Bool_1821 = U32_lte(&_rc_U32_1794, &_re_U32_1794);
        (void)_t_Bool_1821;
        if (_t_Bool_1821) {
            while (1) {
                Bool _wcond_Bool_1795 = U32_lt(&_rc_U32_1794, &_re_U32_1794);
                (void)_wcond_Bool_1795;
                if (_wcond_Bool_1795) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1794);
                (void)i;
                U32_inc(&_rc_U32_1794);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1796 = b->count;
                    (void)_re_U32_1796;
                    U32 _rc_U32_1796 = 0;
                    (void)_rc_U32_1796;
                    Bool _t_Bool_1805 = U32_lte(&_rc_U32_1796, &_re_U32_1796);
                    (void)_t_Bool_1805;
                    if (_t_Bool_1805) {
                        while (1) {
                            Bool _wcond_Bool_1797 = U32_lt(&_rc_U32_1796, &_re_U32_1796);
                            (void)_wcond_Bool_1797;
                            if (_wcond_Bool_1797) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1796);
                            (void)j;
                            U32_inc(&_rc_U32_1796);
                            U32 _t_U32_1799 = U32_add(i, j);
                            (void)_t_U32_1799;
                            U8 *ac = Str_get(a, &_t_U32_1799);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_1800 = U8_neq(ac, bc);
                            (void)_t_Bool_1800;
                            ;
                            ;
                            if (_t_Bool_1800) {
                                Bool _t_Bool_1798 = 0;
                                (void)_t_Bool_1798;
                                found = _t_Bool_1798;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1801 = U32_gt(&_rc_U32_1796, &_re_U32_1796);
                            (void)_wcond_Bool_1801;
                            if (_wcond_Bool_1801) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1796);
                            (void)j;
                            U32_dec(&_rc_U32_1796);
                            U32 _t_U32_1803 = U32_add(i, j);
                            (void)_t_U32_1803;
                            U8 *ac = Str_get(a, &_t_U32_1803);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_1804 = U8_neq(ac, bc);
                            (void)_t_Bool_1804;
                            ;
                            ;
                            if (_t_Bool_1804) {
                                Bool _t_Bool_1802 = 0;
                                (void)_t_Bool_1802;
                                found = _t_Bool_1802;
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
                    Bool _t_Bool_1806 = 1;
                    (void)_t_Bool_1806;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1806;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1807 = U32_gt(&_rc_U32_1794, &_re_U32_1794);
                (void)_wcond_Bool_1807;
                if (_wcond_Bool_1807) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1794);
                (void)i;
                U32_dec(&_rc_U32_1794);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1808 = b->count;
                    (void)_re_U32_1808;
                    U32 _rc_U32_1808 = 0;
                    (void)_rc_U32_1808;
                    Bool _t_Bool_1817 = U32_lte(&_rc_U32_1808, &_re_U32_1808);
                    (void)_t_Bool_1817;
                    if (_t_Bool_1817) {
                        while (1) {
                            Bool _wcond_Bool_1809 = U32_lt(&_rc_U32_1808, &_re_U32_1808);
                            (void)_wcond_Bool_1809;
                            if (_wcond_Bool_1809) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1808);
                            (void)j;
                            U32_inc(&_rc_U32_1808);
                            U32 _t_U32_1811 = U32_add(i, j);
                            (void)_t_U32_1811;
                            U8 *ac = Str_get(a, &_t_U32_1811);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_1812 = U8_neq(ac, bc);
                            (void)_t_Bool_1812;
                            ;
                            ;
                            if (_t_Bool_1812) {
                                Bool _t_Bool_1810 = 0;
                                (void)_t_Bool_1810;
                                found = _t_Bool_1810;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1813 = U32_gt(&_rc_U32_1808, &_re_U32_1808);
                            (void)_wcond_Bool_1813;
                            if (_wcond_Bool_1813) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1808);
                            (void)j;
                            U32_dec(&_rc_U32_1808);
                            U32 _t_U32_1815 = U32_add(i, j);
                            (void)_t_U32_1815;
                            U8 *ac = Str_get(a, &_t_U32_1815);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_1816 = U8_neq(ac, bc);
                            (void)_t_Bool_1816;
                            ;
                            ;
                            if (_t_Bool_1816) {
                                Bool _t_Bool_1814 = 0;
                                (void)_t_Bool_1814;
                                found = _t_Bool_1814;
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
                    Bool _t_Bool_1818 = 1;
                    (void)_t_Bool_1818;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1818;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_1825 = 0;
    (void)_t_Bool_1825;
    return _t_Bool_1825;
}

Bool Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1835 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_1835;
    if (_t_Bool_1835) {
        Bool _t_Bool_1826 = 0;
        (void)_t_Bool_1826;
        ;
        return _t_Bool_1826;
    }
    ;
    {
        U32 _re_U32_1827 = b->count;
        (void)_re_U32_1827;
        U32 _rc_U32_1827 = 0;
        (void)_rc_U32_1827;
        Bool _t_Bool_1834 = U32_lte(&_rc_U32_1827, &_re_U32_1827);
        (void)_t_Bool_1834;
        if (_t_Bool_1834) {
            while (1) {
                Bool _wcond_Bool_1828 = U32_lt(&_rc_U32_1827, &_re_U32_1827);
                (void)_wcond_Bool_1828;
                if (_wcond_Bool_1828) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1827);
                (void)i;
                U32_inc(&_rc_U32_1827);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_1830 = U8_neq(ac, bc);
                (void)_t_Bool_1830;
                ;
                if (_t_Bool_1830) {
                    Bool _t_Bool_1829 = 0;
                    (void)_t_Bool_1829;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1829;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1831 = U32_gt(&_rc_U32_1827, &_re_U32_1827);
                (void)_wcond_Bool_1831;
                if (_wcond_Bool_1831) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1827);
                (void)i;
                U32_dec(&_rc_U32_1827);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_1833 = U8_neq(ac, bc);
                (void)_t_Bool_1833;
                ;
                if (_t_Bool_1833) {
                    Bool _t_Bool_1832 = 0;
                    (void)_t_Bool_1832;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1832;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_1836 = 1;
    (void)_t_Bool_1836;
    return _t_Bool_1836;
}

Bool Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1848 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_1848;
    if (_t_Bool_1848) {
        Bool _t_Bool_1837 = 0;
        (void)_t_Bool_1837;
        ;
        return _t_Bool_1837;
    }
    ;
    U32 offset = U32_sub(a->count, b->count);
    (void)offset;
    {
        U32 _re_U32_1838 = b->count;
        (void)_re_U32_1838;
        U32 _rc_U32_1838 = 0;
        (void)_rc_U32_1838;
        Bool _t_Bool_1847 = U32_lte(&_rc_U32_1838, &_re_U32_1838);
        (void)_t_Bool_1847;
        if (_t_Bool_1847) {
            while (1) {
                Bool _wcond_Bool_1839 = U32_lt(&_rc_U32_1838, &_re_U32_1838);
                (void)_wcond_Bool_1839;
                if (_wcond_Bool_1839) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1838);
                (void)i;
                U32_inc(&_rc_U32_1838);
                U32 _t_U32_1841 = U32_add(offset, i);
                (void)_t_U32_1841;
                U8 *ac = Str_get(a, &_t_U32_1841);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_1842 = U8_neq(ac, bc);
                (void)_t_Bool_1842;
                ;
                ;
                if (_t_Bool_1842) {
                    Bool _t_Bool_1840 = 0;
                    (void)_t_Bool_1840;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1840;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1843 = U32_gt(&_rc_U32_1838, &_re_U32_1838);
                (void)_wcond_Bool_1843;
                if (_wcond_Bool_1843) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1838);
                (void)i;
                U32_dec(&_rc_U32_1838);
                U32 _t_U32_1845 = U32_add(offset, i);
                (void)_t_U32_1845;
                U8 *ac = Str_get(a, &_t_U32_1845);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_1846 = U8_neq(ac, bc);
                (void)_t_Bool_1846;
                ;
                ;
                if (_t_Bool_1846) {
                    Bool _t_Bool_1844 = 0;
                    (void)_t_Bool_1844;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_1844;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    Bool _t_Bool_1849 = 1;
    (void)_t_Bool_1849;
    return _t_Bool_1849;
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_1850 = 0;
    (void)_t_U32_1850;
    Bool _t_Bool_1851 = U32_eq(self->count, _t_U32_1850);
    (void)_t_Bool_1851;
    ;
    return _t_Bool_1851;
}

I64 Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_1886 = 0;
    (void)_t_U32_1886;
    Bool _t_Bool_1887 = U32_eq(needle->count, _t_U32_1886);
    (void)_t_Bool_1887;
    ;
    if (_t_Bool_1887) {
        I64 _t_I64_1852 = 0;
        (void)_t_I64_1852;
        I64 _t_I64_1853 = 1;
        (void)_t_I64_1853;
        I64 _t_I64_1854 = I64_sub(_t_I64_1852, _t_I64_1853);
        (void)_t_I64_1854;
        ;
        ;
        ;
        return _t_I64_1854;
    }
    ;
    Bool _t_Bool_1888 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_1888;
    if (_t_Bool_1888) {
        I64 _t_I64_1855 = 0;
        (void)_t_I64_1855;
        I64 _t_I64_1856 = 1;
        (void)_t_I64_1856;
        I64 _t_I64_1857 = I64_sub(_t_I64_1855, _t_I64_1856);
        (void)_t_I64_1857;
        ;
        ;
        ;
        return _t_I64_1857;
    }
    ;
    {
        U32 _t_U32_1883 = U32_sub(self->count, needle->count);
        (void)_t_U32_1883;
        U32 _t_U32_1884 = 1;
        (void)_t_U32_1884;
        U32 _re_U32_1858 = U32_add(_t_U32_1883, _t_U32_1884);
        (void)_re_U32_1858;
        ;
        ;
        U32 _rc_U32_1858 = 0;
        (void)_rc_U32_1858;
        Bool _t_Bool_1885 = U32_lte(&_rc_U32_1858, &_re_U32_1858);
        (void)_t_Bool_1885;
        if (_t_Bool_1885) {
            while (1) {
                Bool _wcond_Bool_1859 = U32_lt(&_rc_U32_1858, &_re_U32_1858);
                (void)_wcond_Bool_1859;
                if (_wcond_Bool_1859) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1858);
                (void)i;
                U32_inc(&_rc_U32_1858);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1860 = needle->count;
                    (void)_re_U32_1860;
                    U32 _rc_U32_1860 = 0;
                    (void)_rc_U32_1860;
                    Bool _t_Bool_1869 = U32_lte(&_rc_U32_1860, &_re_U32_1860);
                    (void)_t_Bool_1869;
                    if (_t_Bool_1869) {
                        while (1) {
                            Bool _wcond_Bool_1861 = U32_lt(&_rc_U32_1860, &_re_U32_1860);
                            (void)_wcond_Bool_1861;
                            if (_wcond_Bool_1861) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1860);
                            (void)j;
                            U32_inc(&_rc_U32_1860);
                            U32 _t_U32_1863 = U32_add(i, j);
                            (void)_t_U32_1863;
                            U8 *ac = Str_get(self, &_t_U32_1863);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1864 = U8_neq(ac, bc);
                            (void)_t_Bool_1864;
                            ;
                            ;
                            if (_t_Bool_1864) {
                                Bool _t_Bool_1862 = 0;
                                (void)_t_Bool_1862;
                                found = _t_Bool_1862;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1865 = U32_gt(&_rc_U32_1860, &_re_U32_1860);
                            (void)_wcond_Bool_1865;
                            if (_wcond_Bool_1865) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1860);
                            (void)j;
                            U32_dec(&_rc_U32_1860);
                            U32 _t_U32_1867 = U32_add(i, j);
                            (void)_t_U32_1867;
                            U8 *ac = Str_get(self, &_t_U32_1867);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1868 = U8_neq(ac, bc);
                            (void)_t_Bool_1868;
                            ;
                            ;
                            if (_t_Bool_1868) {
                                Bool _t_Bool_1866 = 0;
                                (void)_t_Bool_1866;
                                found = _t_Bool_1866;
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
                    I64 _t_I64_1870 = U32_to_i64(i);
                    (void)_t_I64_1870;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_1870;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1871 = U32_gt(&_rc_U32_1858, &_re_U32_1858);
                (void)_wcond_Bool_1871;
                if (_wcond_Bool_1871) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1858);
                (void)i;
                U32_dec(&_rc_U32_1858);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1872 = needle->count;
                    (void)_re_U32_1872;
                    U32 _rc_U32_1872 = 0;
                    (void)_rc_U32_1872;
                    Bool _t_Bool_1881 = U32_lte(&_rc_U32_1872, &_re_U32_1872);
                    (void)_t_Bool_1881;
                    if (_t_Bool_1881) {
                        while (1) {
                            Bool _wcond_Bool_1873 = U32_lt(&_rc_U32_1872, &_re_U32_1872);
                            (void)_wcond_Bool_1873;
                            if (_wcond_Bool_1873) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1872);
                            (void)j;
                            U32_inc(&_rc_U32_1872);
                            U32 _t_U32_1875 = U32_add(i, j);
                            (void)_t_U32_1875;
                            U8 *ac = Str_get(self, &_t_U32_1875);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1876 = U8_neq(ac, bc);
                            (void)_t_Bool_1876;
                            ;
                            ;
                            if (_t_Bool_1876) {
                                Bool _t_Bool_1874 = 0;
                                (void)_t_Bool_1874;
                                found = _t_Bool_1874;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1877 = U32_gt(&_rc_U32_1872, &_re_U32_1872);
                            (void)_wcond_Bool_1877;
                            if (_wcond_Bool_1877) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1872);
                            (void)j;
                            U32_dec(&_rc_U32_1872);
                            U32 _t_U32_1879 = U32_add(i, j);
                            (void)_t_U32_1879;
                            U8 *ac = Str_get(self, &_t_U32_1879);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1880 = U8_neq(ac, bc);
                            (void)_t_Bool_1880;
                            ;
                            ;
                            if (_t_Bool_1880) {
                                Bool _t_Bool_1878 = 0;
                                (void)_t_Bool_1878;
                                found = _t_Bool_1878;
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
                    I64 _t_I64_1882 = U32_to_i64(i);
                    (void)_t_I64_1882;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_1882;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    I64 _t_I64_1889 = 0;
    (void)_t_I64_1889;
    I64 _t_I64_1890 = 1;
    (void)_t_I64_1890;
    I64 _t_I64_1891 = I64_sub(_t_I64_1889, _t_I64_1890);
    (void)_t_I64_1891;
    ;
    ;
    return _t_I64_1891;
}

I64 Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_1926 = 0;
    (void)_t_U32_1926;
    Bool _t_Bool_1927 = U32_eq(needle->count, _t_U32_1926);
    (void)_t_Bool_1927;
    ;
    if (_t_Bool_1927) {
        I64 _t_I64_1892 = 0;
        (void)_t_I64_1892;
        I64 _t_I64_1893 = 1;
        (void)_t_I64_1893;
        I64 _t_I64_1894 = I64_sub(_t_I64_1892, _t_I64_1893);
        (void)_t_I64_1894;
        ;
        ;
        ;
        return _t_I64_1894;
    }
    ;
    Bool _t_Bool_1928 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_1928;
    if (_t_Bool_1928) {
        I64 _t_I64_1895 = 0;
        (void)_t_I64_1895;
        I64 _t_I64_1896 = 1;
        (void)_t_I64_1896;
        I64 _t_I64_1897 = I64_sub(_t_I64_1895, _t_I64_1896);
        (void)_t_I64_1897;
        ;
        ;
        ;
        return _t_I64_1897;
    }
    ;
    I64 _t_I64_1929 = 0;
    (void)_t_I64_1929;
    I64 _t_I64_1930 = 1;
    (void)_t_I64_1930;
    I64 last = I64_sub(_t_I64_1929, _t_I64_1930);
    (void)last;
    ;
    ;
    {
        U32 _t_U32_1923 = U32_sub(self->count, needle->count);
        (void)_t_U32_1923;
        U32 _t_U32_1924 = 1;
        (void)_t_U32_1924;
        U32 _re_U32_1898 = U32_add(_t_U32_1923, _t_U32_1924);
        (void)_re_U32_1898;
        ;
        ;
        U32 _rc_U32_1898 = 0;
        (void)_rc_U32_1898;
        Bool _t_Bool_1925 = U32_lte(&_rc_U32_1898, &_re_U32_1898);
        (void)_t_Bool_1925;
        if (_t_Bool_1925) {
            while (1) {
                Bool _wcond_Bool_1899 = U32_lt(&_rc_U32_1898, &_re_U32_1898);
                (void)_wcond_Bool_1899;
                if (_wcond_Bool_1899) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1898);
                (void)i;
                U32_inc(&_rc_U32_1898);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1900 = needle->count;
                    (void)_re_U32_1900;
                    U32 _rc_U32_1900 = 0;
                    (void)_rc_U32_1900;
                    Bool _t_Bool_1909 = U32_lte(&_rc_U32_1900, &_re_U32_1900);
                    (void)_t_Bool_1909;
                    if (_t_Bool_1909) {
                        while (1) {
                            Bool _wcond_Bool_1901 = U32_lt(&_rc_U32_1900, &_re_U32_1900);
                            (void)_wcond_Bool_1901;
                            if (_wcond_Bool_1901) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1900);
                            (void)j;
                            U32_inc(&_rc_U32_1900);
                            U32 _t_U32_1903 = U32_add(i, j);
                            (void)_t_U32_1903;
                            U8 *ac = Str_get(self, &_t_U32_1903);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1904 = U8_neq(ac, bc);
                            (void)_t_Bool_1904;
                            ;
                            ;
                            if (_t_Bool_1904) {
                                Bool _t_Bool_1902 = 0;
                                (void)_t_Bool_1902;
                                found = _t_Bool_1902;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1905 = U32_gt(&_rc_U32_1900, &_re_U32_1900);
                            (void)_wcond_Bool_1905;
                            if (_wcond_Bool_1905) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1900);
                            (void)j;
                            U32_dec(&_rc_U32_1900);
                            U32 _t_U32_1907 = U32_add(i, j);
                            (void)_t_U32_1907;
                            U8 *ac = Str_get(self, &_t_U32_1907);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1908 = U8_neq(ac, bc);
                            (void)_t_Bool_1908;
                            ;
                            ;
                            if (_t_Bool_1908) {
                                Bool _t_Bool_1906 = 0;
                                (void)_t_Bool_1906;
                                found = _t_Bool_1906;
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
                    I64 _t_I64_1910 = U32_to_i64(i);
                    (void)_t_I64_1910;
                    last = _t_I64_1910;
                    ;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1911 = U32_gt(&_rc_U32_1898, &_re_U32_1898);
                (void)_wcond_Bool_1911;
                if (_wcond_Bool_1911) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1898);
                (void)i;
                U32_dec(&_rc_U32_1898);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_1912 = needle->count;
                    (void)_re_U32_1912;
                    U32 _rc_U32_1912 = 0;
                    (void)_rc_U32_1912;
                    Bool _t_Bool_1921 = U32_lte(&_rc_U32_1912, &_re_U32_1912);
                    (void)_t_Bool_1921;
                    if (_t_Bool_1921) {
                        while (1) {
                            Bool _wcond_Bool_1913 = U32_lt(&_rc_U32_1912, &_re_U32_1912);
                            (void)_wcond_Bool_1913;
                            if (_wcond_Bool_1913) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1912);
                            (void)j;
                            U32_inc(&_rc_U32_1912);
                            U32 _t_U32_1915 = U32_add(i, j);
                            (void)_t_U32_1915;
                            U8 *ac = Str_get(self, &_t_U32_1915);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1916 = U8_neq(ac, bc);
                            (void)_t_Bool_1916;
                            ;
                            ;
                            if (_t_Bool_1916) {
                                Bool _t_Bool_1914 = 0;
                                (void)_t_Bool_1914;
                                found = _t_Bool_1914;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_1917 = U32_gt(&_rc_U32_1912, &_re_U32_1912);
                            (void)_wcond_Bool_1917;
                            if (_wcond_Bool_1917) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_1912);
                            (void)j;
                            U32_dec(&_rc_U32_1912);
                            U32 _t_U32_1919 = U32_add(i, j);
                            (void)_t_U32_1919;
                            U8 *ac = Str_get(self, &_t_U32_1919);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_1920 = U8_neq(ac, bc);
                            (void)_t_Bool_1920;
                            ;
                            ;
                            if (_t_Bool_1920) {
                                Bool _t_Bool_1918 = 0;
                                (void)_t_Bool_1918;
                                found = _t_Bool_1918;
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
                    I64 _t_I64_1922 = U32_to_i64(i);
                    (void)_t_I64_1922;
                    last = _t_I64_1922;
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
    U32 _t_U32_1956 = 0;
    (void)_t_U32_1956;
    Bool _t_Bool_1957 = U32_eq(from->count, _t_U32_1956);
    (void)_t_Bool_1957;
    ;
    if (_t_Bool_1957) {
        Str *_t_Str_1931 = Str_clone(self);
        (void)_t_Str_1931;
        ;
        return _t_Str_1931;
    }
    ;
    U32 matches = 0;
    (void)matches;
    U32 start = 0;
    (void)start;
    while (1) {
        U32 _t_U32_1933 = U32_sub(self->count, from->count);
        (void)_t_U32_1933;
        Bool _wcond_Bool_1932 = U32_lte(&start, &_t_U32_1933);
        (void)_wcond_Bool_1932;
        ;
        if (_wcond_Bool_1932) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_1934 = U32_sub(self->count, start);
        (void)_t_U32_1934;
        Str *rest = Str_substr(self, &start, &_t_U32_1934);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_1935 = 0;
        (void)_t_I64_1935;
        I64 _t_I64_1936 = 1;
        (void)_t_I64_1936;
        I64 _t_I64_1937 = I64_sub(_t_I64_1935, _t_I64_1936);
        (void)_t_I64_1937;
        ;
        ;
        Bool _t_Bool_1938 = I64_eq(pos, _t_I64_1937);
        (void)_t_Bool_1938;
        ;
        if (_t_Bool_1938) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        U32 _t_U32_1939 = U32_add(start, pos_u);
        (void)_t_U32_1939;
        ;
        U32 _t_U32_1940 = U32_add(_t_U32_1939, from->count);
        (void)_t_U32_1940;
        ;
        start = _t_U32_1940;
        ;
        U32 _t_U32_1941 = 1;
        (void)_t_U32_1941;
        U32 _t_U32_1942 = U32_add(matches, _t_U32_1941);
        (void)_t_U32_1942;
        ;
        matches = _t_U32_1942;
        ;
    }
    U32 _t_U32_1958 = 0;
    (void)_t_U32_1958;
    Bool _t_Bool_1959 = U32_eq(matches, _t_U32_1958);
    (void)_t_Bool_1959;
    ;
    if (_t_Bool_1959) {
        Str *_t_Str_1943 = Str_clone(self);
        (void)_t_Str_1943;
        ;
        ;
        ;
        return _t_Str_1943;
    }
    ;
    U32 removed = U32_mul(matches, from->count);
    (void)removed;
    U32 added = U32_mul(matches, to->count);
    (void)added;
    ;
    U32 _t_U32_1960 = U32_sub(self->count, removed);
    (void)_t_U32_1960;
    ;
    U32 _t_U32_1961 = U32_add(_t_U32_1960, added);
    (void)_t_U32_1961;
    ;
    ;
    Str *out = Str_with_capacity(&_t_U32_1961);
    (void)out;
    ;
    U32 _t_U32_1962 = 0;
    (void)_t_U32_1962;
    start = _t_U32_1962;
    ;
    while (1) {
        U32 _t_U32_1945 = U32_sub(self->count, from->count);
        (void)_t_U32_1945;
        Bool _wcond_Bool_1944 = U32_lte(&start, &_t_U32_1945);
        (void)_wcond_Bool_1944;
        ;
        if (_wcond_Bool_1944) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_1946 = U32_sub(self->count, start);
        (void)_t_U32_1946;
        Str *rest = Str_substr(self, &start, &_t_U32_1946);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_1947 = 0;
        (void)_t_I64_1947;
        I64 _t_I64_1948 = 1;
        (void)_t_I64_1948;
        I64 _t_I64_1949 = I64_sub(_t_I64_1947, _t_I64_1948);
        (void)_t_I64_1949;
        ;
        ;
        Bool _t_Bool_1950 = I64_eq(pos, _t_I64_1949);
        (void)_t_Bool_1950;
        ;
        if (_t_Bool_1950) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        Str *_t_Str_1951 = Str_substr(self, &start, &pos_u);
        (void)_t_Str_1951;
        Str_push_str(out, _t_Str_1951);
        Str_delete(_t_Str_1951, &(Bool){1});
        Str_push_str(out, to);
        U32 _t_U32_1952 = U32_add(start, pos_u);
        (void)_t_U32_1952;
        ;
        U32 _t_U32_1953 = U32_add(_t_U32_1952, from->count);
        (void)_t_U32_1953;
        ;
        start = _t_U32_1953;
        ;
    }
    Bool _t_Bool_1963 = U32_lt(&start, &self->count);
    (void)_t_Bool_1963;
    if (_t_Bool_1963) {
        U32 _t_U32_1954 = U32_sub(self->count, start);
        (void)_t_U32_1954;
        Str *_t_Str_1955 = Str_substr(self, &start, &_t_U32_1954);
        (void)_t_Str_1955;
        ;
        Str_push_str(out, _t_Str_1955);
        Str_delete(_t_Str_1955, &(Bool){1});
    }
    ;
    ;
    return out;
}

Str * Str_get_char(Str * self, U32 * i) {
    (void)self;
    (void)i;
    U32 _t_U32_1964 = 1;
    (void)_t_U32_1964;
    Str *_t_Str_1965 = Str_substr(self, i, &_t_U32_1964);
    (void)_t_Str_1965;
    ;
    return _t_Str_1965;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t_Bool_1968 = Str_starts_with(self, prefix);
    (void)_t_Bool_1968;
    if (_t_Bool_1968) {
        U32 _t_U32_1966 = U32_sub(self->count, prefix->count);
        (void)_t_U32_1966;
        Str *_t_Str_1967 = Str_substr(self, &prefix->count, &_t_U32_1966);
        (void)_t_Str_1967;
        ;
        ;
        return _t_Str_1967;
    }
    ;
    Str *_t_Str_1969 = Str_clone(self);
    (void)_t_Str_1969;
    return _t_Str_1969;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t_Bool_1973 = Str_ends_with(self, suffix);
    (void)_t_Bool_1973;
    if (_t_Bool_1973) {
        U32 _t_U32_1970 = 0;
        (void)_t_U32_1970;
        U32 _t_U32_1971 = U32_sub(self->count, suffix->count);
        (void)_t_U32_1971;
        Str *_t_Str_1972 = Str_substr(self, &_t_U32_1970, &_t_U32_1971);
        (void)_t_Str_1972;
        ;
        ;
        ;
        return _t_Str_1972;
    }
    ;
    Str *_t_Str_1974 = Str_clone(self);
    (void)_t_Str_1974;
    return _t_Str_1974;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t_U64_1975 = 2;
    (void)_t_U64_1975;
    void * buf = malloc(_t_U64_1975);
    (void)buf;
    ;
    U64 _t_U64_1976 = 1;
    (void)_t_U64_1976;
    memcpy(buf, byte, _t_U64_1976);
    ;
    U64 _t_U64_1977 = 1;
    (void)_t_U64_1977;
    void *_t_v_1978 = ptr_add(buf, _t_U64_1977);
    (void)_t_v_1978;
    I32 _t_I32_1979 = 0;
    (void)_t_I32_1979;
    U64 _t_U64_1980 = 1;
    (void)_t_U64_1980;
    memset(_t_v_1978, _t_I32_1979, _t_U64_1980);
    ;
    ;
    ;
    I64 _t_I64_1981 = 1;
    (void)_t_I64_1981;
    I64 _t_I64_1982 = 1;
    (void)_t_I64_1982;
    Str *_t_Str_1983 = malloc(sizeof(Str));
    _t_Str_1983->c_str = buf;
    _t_Str_1983->count = _t_I64_1981;
    _t_Str_1983->cap = _t_I64_1982;
    (void)_t_Str_1983;
    ;
    ;
    return _t_Str_1983;
}

I64 Str_to_i64(Str * self) {
    (void)self;
    U32 _t_U32_2040 = 0;
    (void)_t_U32_2040;
    Bool _t_Bool_2041 = U32_eq(self->count, _t_U32_2040);
    (void)_t_Bool_2041;
    ;
    if (_t_Bool_2041) {
        Str *_t_Str_1984 = Str_lit("Str", 3ULL);
        (void)_t_Str_1984;
        U32 _t_U32_1985 = 1;
        (void)_t_U32_1985;
        Array *_va_Array_69 = Array_new(_t_Str_1984, &_t_U32_1985);
        (void)_va_Array_69;
        Str_delete(_t_Str_1984, &(Bool){1});
        ;
        U32 _t_U32_1986 = 0;
        (void)_t_U32_1986;
        Str *_t_Str_1987 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t_Str_1987;
        Array_set(_va_Array_69, &_t_U32_1986, _t_Str_1987);
        ;
        Str *_t_Str_1988 = Str_lit("./src/core/str.til:266:37", 25ULL);
        (void)_t_Str_1988;
        panic(_t_Str_1988, _va_Array_69);
        Str_delete(_t_Str_1988, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_2042 = 0;
    (void)_t_U32_2042;
    U8 *first = Str_get(self, &_t_U32_2042);
    (void)first;
    U8 _t_U8_2043 = 45;
    (void)_t_U8_2043;
    Bool _t_Bool_2044 = U8_eq(DEREF(first), _t_U8_2043);
    (void)_t_Bool_2044;
    ;
    ;
    if (_t_Bool_2044) {
        Bool _t_Bool_1989 = 1;
        (void)_t_Bool_1989;
        neg = _t_Bool_1989;
        ;
        U32 _t_U32_1990 = 1;
        (void)_t_U32_1990;
        start = _t_U32_1990;
        ;
    }
    ;
    Bool _t_Bool_2045 = U32_eq(start, self->count);
    (void)_t_Bool_2045;
    if (_t_Bool_2045) {
        Str *_t_Str_1991 = Str_lit("Str", 3ULL);
        (void)_t_Str_1991;
        U32 _t_U32_1992 = 1;
        (void)_t_U32_1992;
        Array *_va_Array_70 = Array_new(_t_Str_1991, &_t_U32_1992);
        (void)_va_Array_70;
        Str_delete(_t_Str_1991, &(Bool){1});
        ;
        U32 _t_U32_1993 = 0;
        (void)_t_U32_1993;
        Str *_t_Str_1994 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t_Str_1994;
        Array_set(_va_Array_70, &_t_U32_1993, _t_Str_1994);
        ;
        Str *_t_Str_1995 = Str_lit("./src/core/str.til:275:41", 25ULL);
        (void)_t_Str_1995;
        panic(_t_Str_1995, _va_Array_70);
        Str_delete(_t_Str_1995, &(Bool){1});
    }
    ;
    {
        U32 _re_U32_1996 = self->count;
        (void)_re_U32_1996;
        U32 _rc_U32_1996 = U32_clone(&start);
        (void)_rc_U32_1996;
        Bool _t_Bool_2037 = U32_lte(&_rc_U32_1996, &_re_U32_1996);
        (void)_t_Bool_2037;
        if (_t_Bool_2037) {
            while (1) {
                Bool _wcond_Bool_1997 = U32_lt(&_rc_U32_1996, &_re_U32_1996);
                (void)_wcond_Bool_1997;
                if (_wcond_Bool_1997) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1996);
                (void)i;
                U32_inc(&_rc_U32_1996);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_2007 = U8_to_i64(DEREF(ch));
                (void)_t_I64_2007;
                ;
                I64 _t_I64_2008 = 48;
                (void)_t_I64_2008;
                I64 d = I64_sub(_t_I64_2007, _t_I64_2008);
                (void)d;
                ;
                ;
                I64 _t_I64_2009 = 0;
                (void)_t_I64_2009;
                I64 _t_I64_2010 = 9;
                (void)_t_I64_2010;
                Bool _t_Bool_2011 = I64_lt(&d, &_t_I64_2009);
                (void)_t_Bool_2011;
                ;
                Bool _t_Bool_2012 = I64_gt(&d, &_t_I64_2010);
                (void)_t_Bool_2012;
                ;
                Bool _t_Bool_2013 = or(_t_Bool_2011, _t_Bool_2012);
                (void)_t_Bool_2013;
                ;
                ;
                if (_t_Bool_2013) {
                    Str *_t_Str_1998 = Str_lit("Str", 3ULL);
                    (void)_t_Str_1998;
                    U32 _t_U32_1999 = 3;
                    (void)_t_U32_1999;
                    Array *_va_Array_71 = Array_new(_t_Str_1998, &_t_U32_1999);
                    (void)_va_Array_71;
                    Str_delete(_t_Str_1998, &(Bool){1});
                    ;
                    U32 _t_U32_2000 = 0;
                    (void)_t_U32_2000;
                    Str *_t_Str_2001 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_2001;
                    Array_set(_va_Array_71, &_t_U32_2000, _t_Str_2001);
                    ;
                    U32 _t_U32_2002 = 1;
                    (void)_t_U32_2002;
                    Str *_t_Str_2003 = Str_clone(self);
                    (void)_t_Str_2003;
                    Array_set(_va_Array_71, &_t_U32_2002, _t_Str_2003);
                    ;
                    U32 _t_U32_2004 = 2;
                    (void)_t_U32_2004;
                    Str *_t_Str_2005 = Str_lit("'", 1ULL);
                    (void)_t_Str_2005;
                    Array_set(_va_Array_71, &_t_U32_2004, _t_Str_2005);
                    ;
                    Str *_t_Str_2006 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_2006;
                    panic(_t_Str_2006, _va_Array_71);
                    Str_delete(_t_Str_2006, &(Bool){1});
                }
                ;
                I64 _t_I64_2014 = 10;
                (void)_t_I64_2014;
                I64 _t_I64_2015 = I64_mul(result, _t_I64_2014);
                (void)_t_I64_2015;
                ;
                I64 _t_I64_2016 = I64_add(_t_I64_2015, d);
                (void)_t_I64_2016;
                ;
                ;
                result = _t_I64_2016;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2017 = U32_gt(&_rc_U32_1996, &_re_U32_1996);
                (void)_wcond_Bool_2017;
                if (_wcond_Bool_2017) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_1996);
                (void)i;
                U32_dec(&_rc_U32_1996);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_2027 = U8_to_i64(DEREF(ch));
                (void)_t_I64_2027;
                ;
                I64 _t_I64_2028 = 48;
                (void)_t_I64_2028;
                I64 d = I64_sub(_t_I64_2027, _t_I64_2028);
                (void)d;
                ;
                ;
                I64 _t_I64_2029 = 0;
                (void)_t_I64_2029;
                I64 _t_I64_2030 = 9;
                (void)_t_I64_2030;
                Bool _t_Bool_2031 = I64_lt(&d, &_t_I64_2029);
                (void)_t_Bool_2031;
                ;
                Bool _t_Bool_2032 = I64_gt(&d, &_t_I64_2030);
                (void)_t_Bool_2032;
                ;
                Bool _t_Bool_2033 = or(_t_Bool_2031, _t_Bool_2032);
                (void)_t_Bool_2033;
                ;
                ;
                if (_t_Bool_2033) {
                    Str *_t_Str_2018 = Str_lit("Str", 3ULL);
                    (void)_t_Str_2018;
                    U32 _t_U32_2019 = 3;
                    (void)_t_U32_2019;
                    Array *_va_Array_72 = Array_new(_t_Str_2018, &_t_U32_2019);
                    (void)_va_Array_72;
                    Str_delete(_t_Str_2018, &(Bool){1});
                    ;
                    U32 _t_U32_2020 = 0;
                    (void)_t_U32_2020;
                    Str *_t_Str_2021 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_2021;
                    Array_set(_va_Array_72, &_t_U32_2020, _t_Str_2021);
                    ;
                    U32 _t_U32_2022 = 1;
                    (void)_t_U32_2022;
                    Str *_t_Str_2023 = Str_clone(self);
                    (void)_t_Str_2023;
                    Array_set(_va_Array_72, &_t_U32_2022, _t_Str_2023);
                    ;
                    U32 _t_U32_2024 = 2;
                    (void)_t_U32_2024;
                    Str *_t_Str_2025 = Str_lit("'", 1ULL);
                    (void)_t_Str_2025;
                    Array_set(_va_Array_72, &_t_U32_2024, _t_Str_2025);
                    ;
                    Str *_t_Str_2026 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_2026;
                    panic(_t_Str_2026, _va_Array_72);
                    Str_delete(_t_Str_2026, &(Bool){1});
                }
                ;
                I64 _t_I64_2034 = 10;
                (void)_t_I64_2034;
                I64 _t_I64_2035 = I64_mul(result, _t_I64_2034);
                (void)_t_I64_2035;
                ;
                I64 _t_I64_2036 = I64_add(_t_I64_2035, d);
                (void)_t_I64_2036;
                ;
                ;
                result = _t_I64_2036;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    if (neg) {
        I64 _t_I64_2038 = 0;
        (void)_t_I64_2038;
        I64 _t_I64_2039 = I64_sub(_t_I64_2038, result);
        (void)_t_I64_2039;
        ;
        ;
        ;
        return _t_I64_2039;
    }
    ;
    return result;
}

U8 Str_to_u8(Str * self) {
    (void)self;
    I64 _t_I64_2046 = Str_to_i64(self);
    (void)_t_I64_2046;
    U8 _t_U8_2047 = I64_to_u8(_t_I64_2046);
    (void)_t_U8_2047;
    ;
    return _t_U8_2047;
}

I32 Str_to_i32(Str * self) {
    (void)self;
    I64 _t_I64_2048 = Str_to_i64(self);
    (void)_t_I64_2048;
    I32 _t_I32_2049 = I64_to_i32(_t_I64_2048);
    (void)_t_I32_2049;
    ;
    return _t_I32_2049;
}

F32 Str_to_f32(Str * self) {
    (void)self;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_2075 = Str_len(self);
    (void)_t_U32_2075;
    U32 _t_U32_2076 = 0;
    (void)_t_U32_2076;
    U32 _t_U32_2077 = 0;
    (void)_t_U32_2077;
    U8 *_t_U8_2078 = Str_get(self, &_t_U32_2077);
    (void)_t_U8_2078;
    U8 _t_U8_2079 = 45;
    (void)_t_U8_2079;
    Bool _t_Bool_2080 = U32_gt(&_t_U32_2075, &_t_U32_2076);
    (void)_t_Bool_2080;
    ;
    ;
    Bool _t_Bool_2081 = U8_eq(DEREF(_t_U8_2078), _t_U8_2079);
    (void)_t_Bool_2081;
    ;
    ;
    Bool _t_Bool_2082 = and(_t_Bool_2080, _t_Bool_2081);
    (void)_t_Bool_2082;
    ;
    ;
    if (_t_Bool_2082) {
        Bool _t_Bool_2050 = 1;
        (void)_t_Bool_2050;
        neg = _t_Bool_2050;
        ;
        U32 _t_U32_2051 = 1;
        (void)_t_U32_2051;
        start = _t_U32_2051;
        ;
    }
    ;
    U32 _t_U32_2083 = Str_len(self);
    (void)_t_U32_2083;
    U32 _t_U32_2084 = U32_sub(_t_U32_2083, start);
    (void)_t_U32_2084;
    ;
    Str *rest = Str_substr(self, &start, &_t_U32_2084);
    (void)rest;
    ;
    ;
    Str *_t_Str_2085 = Str_lit(".", 1ULL);
    (void)_t_Str_2085;
    I64 dot = Str_find(rest, _t_Str_2085);
    (void)dot;
    Str_delete(_t_Str_2085, &(Bool){1});
    I64 _t_I64_2086 = 0;
    (void)_t_I64_2086;
    I64 _t_I64_2087 = 1;
    (void)_t_I64_2087;
    I64 _t_I64_2088 = I64_sub(_t_I64_2086, _t_I64_2087);
    (void)_t_I64_2088;
    ;
    ;
    Bool _t_Bool_2089 = I64_eq(dot, _t_I64_2088);
    (void)_t_Bool_2089;
    ;
    if (_t_Bool_2089) {
        I64 _t_I64_2055 = Str_to_i64(rest);
        (void)_t_I64_2055;
        F32 out = I64_to_f32(_t_I64_2055);
        (void)out;
        ;
        if (neg) {
            I64 _t_I64_2052 = 0;
            (void)_t_I64_2052;
            F32 _t_F32_2053 = I64_to_f32(_t_I64_2052);
            (void)_t_F32_2053;
            ;
            F32 _t_F32_2054 = F32_sub(_t_F32_2053, out);
            (void)_t_F32_2054;
            ;
            ;
            ;
            ;
            ;
            Str_delete(rest, &(Bool){1});
            return _t_F32_2054;
        }
        ;
        ;
        ;
        Str_delete(rest, &(Bool){1});
        return out;
    }
    ;
    U32 _t_U32_2090 = 0;
    (void)_t_U32_2090;
    U32 _t_U32_2091 = I64_to_usize(dot);
    (void)_t_U32_2091;
    Str *int_part = Str_substr(rest, &_t_U32_2090, &_t_U32_2091);
    (void)int_part;
    ;
    ;
    U32 _t_U32_2092 = I64_to_usize(dot);
    (void)_t_U32_2092;
    U32 _t_U32_2093 = 1;
    (void)_t_U32_2093;
    U32 _t_U32_2094 = I64_to_usize(dot);
    (void)_t_U32_2094;
    ;
    U32 _t_U32_2095 = 1;
    (void)_t_U32_2095;
    U32 _t_U32_2096 = Str_len(rest);
    (void)_t_U32_2096;
    U32 _t_U32_2097 = U32_add(_t_U32_2094, _t_U32_2095);
    (void)_t_U32_2097;
    ;
    ;
    U32 _t_U32_2098 = U32_add(_t_U32_2092, _t_U32_2093);
    (void)_t_U32_2098;
    ;
    ;
    U32 _t_U32_2099 = U32_sub(_t_U32_2096, _t_U32_2097);
    (void)_t_U32_2099;
    ;
    ;
    Str *frac_part = Str_substr(rest, &_t_U32_2098, &_t_U32_2099);
    (void)frac_part;
    ;
    ;
    Str_delete(rest, &(Bool){1});
    I64 _t_I64_2100 = 0;
    (void)_t_I64_2100;
    F32 out = I64_to_f32(_t_I64_2100);
    (void)out;
    ;
    U32 _t_U32_2101 = Str_len(int_part);
    (void)_t_U32_2101;
    U32 _t_U32_2102 = 0;
    (void)_t_U32_2102;
    Bool _t_Bool_2103 = U32_gt(&_t_U32_2101, &_t_U32_2102);
    (void)_t_Bool_2103;
    ;
    ;
    if (_t_Bool_2103) {
        I64 _t_I64_2056 = Str_to_i64(int_part);
        (void)_t_I64_2056;
        F32 _t_F32_2057 = I64_to_f32(_t_I64_2056);
        (void)_t_F32_2057;
        ;
        out = _t_F32_2057;
        ;
    }
    ;
    Str_delete(int_part, &(Bool){1});
    U32 _t_U32_2104 = Str_len(frac_part);
    (void)_t_U32_2104;
    U32 _t_U32_2105 = 0;
    (void)_t_U32_2105;
    Bool _t_Bool_2106 = U32_gt(&_t_U32_2104, &_t_U32_2105);
    (void)_t_Bool_2106;
    ;
    ;
    if (_t_Bool_2106) {
        I64 _t_I64_2068 = Str_to_i64(frac_part);
        (void)_t_I64_2068;
        F32 frac = I64_to_f32(_t_I64_2068);
        (void)frac;
        ;
        I64 _t_I64_2069 = 1;
        (void)_t_I64_2069;
        F32 scale = I64_to_f32(_t_I64_2069);
        (void)scale;
        ;
        {
            U32 _re_U32_2058 = Str_len(frac_part);
            (void)_re_U32_2058;
            U32 _rc_U32_2058 = 0;
            (void)_rc_U32_2058;
            Bool _t_Bool_2067 = U32_lte(&_rc_U32_2058, &_re_U32_2058);
            (void)_t_Bool_2067;
            if (_t_Bool_2067) {
                while (1) {
                    Bool _wcond_Bool_2059 = U32_lt(&_rc_U32_2058, &_re_U32_2058);
                    (void)_wcond_Bool_2059;
                    if (_wcond_Bool_2059) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_2058);
                    (void)_;
                    ;
                    U32_inc(&_rc_U32_2058);
                    I64 _t_I64_2060 = 10;
                    (void)_t_I64_2060;
                    F32 _t_F32_2061 = I64_to_f32(_t_I64_2060);
                    (void)_t_F32_2061;
                    ;
                    F32 _t_F32_2062 = F32_mul(scale, _t_F32_2061);
                    (void)_t_F32_2062;
                    ;
                    scale = _t_F32_2062;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_2063 = U32_gt(&_rc_U32_2058, &_re_U32_2058);
                    (void)_wcond_Bool_2063;
                    if (_wcond_Bool_2063) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_2058);
                    (void)_;
                    ;
                    U32_dec(&_rc_U32_2058);
                    I64 _t_I64_2064 = 10;
                    (void)_t_I64_2064;
                    F32 _t_F32_2065 = I64_to_f32(_t_I64_2064);
                    (void)_t_F32_2065;
                    ;
                    F32 _t_F32_2066 = F32_mul(scale, _t_F32_2065);
                    (void)_t_F32_2066;
                    ;
                    scale = _t_F32_2066;
                    ;
                }
            }
            ;
            ;
            ;
        }
        F32 _t_F32_2070 = F32_div(frac, scale);
        (void)_t_F32_2070;
        ;
        ;
        F32 _t_F32_2071 = F32_add(out, _t_F32_2070);
        (void)_t_F32_2071;
        ;
        out = _t_F32_2071;
        ;
    }
    ;
    Str_delete(frac_part, &(Bool){1});
    if (neg) {
        I64 _t_I64_2072 = 0;
        (void)_t_I64_2072;
        F32 _t_F32_2073 = I64_to_f32(_t_I64_2072);
        (void)_t_F32_2073;
        ;
        F32 _t_F32_2074 = F32_sub(_t_F32_2073, out);
        (void)_t_F32_2074;
        ;
        ;
        ;
        return _t_F32_2074;
    }
    ;
    return out;
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t_Str_2123 = Str_lit("Str", 3ULL);
    (void)_t_Str_2123;
    TilType *_t_TilType_2124 = TilType_Struct(_t_Str_2123);
    (void)_t_TilType_2124;
    Str_delete(_t_Str_2123, &(Bool){1});
    Vec *parts = Vec_new(_t_TilType_2124);
    (void)parts;
    TilType_delete(_t_TilType_2124, &(Bool){1});
    U32 _t_U32_2125 = Str_len(delim);
    (void)_t_U32_2125;
    U32 _t_U32_2126 = 0;
    (void)_t_U32_2126;
    Bool _t_Bool_2127 = U32_eq(_t_U32_2125, _t_U32_2126);
    (void)_t_Bool_2127;
    ;
    ;
    if (_t_Bool_2127) {
        Str *_t_Str_2107 = Str_clone(self);
        (void)_t_Str_2107;
        Vec_push(parts, _t_Str_2107);
        ;
        return parts;
    }
    ;
    U32 start = 0;
    (void)start;
    U32 pos = 0;
    (void)pos;
    while (1) {
        U32 _t_U32_2117 = Str_len(self);
        (void)_t_U32_2117;
        U32 _t_U32_2118 = Str_len(delim);
        (void)_t_U32_2118;
        U32 _t_U32_2119 = U32_sub(_t_U32_2117, _t_U32_2118);
        (void)_t_U32_2119;
        ;
        ;
        Bool _wcond_Bool_2108 = U32_lte(&pos, &_t_U32_2119);
        (void)_wcond_Bool_2108;
        ;
        if (_wcond_Bool_2108) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_2120 = Str_len(delim);
        (void)_t_U32_2120;
        Str *_t_Str_2121 = Str_substr(self, &pos, &_t_U32_2120);
        (void)_t_Str_2121;
        ;
        Bool _t_Bool_2122 = Str_eq(_t_Str_2121, delim);
        (void)_t_Bool_2122;
        Str_delete(_t_Str_2121, &(Bool){1});
        if (_t_Bool_2122) {
            U32 _t_U32_2109 = U32_sub(pos, start);
            (void)_t_U32_2109;
            Str *_t_Str_2110 = Str_substr(self, &start, &_t_U32_2109);
            (void)_t_Str_2110;
            ;
            Str *_t_Str_2111 = Str_clone(_t_Str_2110);
            (void)_t_Str_2111;
            Str_delete(_t_Str_2110, &(Bool){1});
            Vec_push(parts, _t_Str_2111);
            U32 _t_U32_2112 = Str_len(delim);
            (void)_t_U32_2112;
            U32 _t_U32_2113 = U32_add(pos, _t_U32_2112);
            (void)_t_U32_2113;
            ;
            start = _t_U32_2113;
            ;
            U32 _t_U32_2114 = U32_clone(&start);
            (void)_t_U32_2114;
            pos = _t_U32_2114;
            ;
        } else {
            U32 _t_U32_2115 = 1;
            (void)_t_U32_2115;
            U32 _t_U32_2116 = U32_add(pos, _t_U32_2115);
            (void)_t_U32_2116;
            ;
            pos = _t_U32_2116;
            ;
        }
        ;
    }
    ;
    U32 _t_U32_2128 = Str_len(self);
    (void)_t_U32_2128;
    U32 _t_U32_2129 = U32_sub(_t_U32_2128, start);
    (void)_t_U32_2129;
    ;
    Str *_t_Str_2130 = Str_substr(self, &start, &_t_U32_2129);
    (void)_t_Str_2130;
    ;
    ;
    Str *_t_Str_2131 = Str_clone(_t_Str_2130);
    (void)_t_Str_2131;
    Str_delete(_t_Str_2130, &(Bool){1});
    Vec_push(parts, _t_Str_2131);
    return parts;
}

U32 Str_size(void) {
    I64 _t_I64_2132 = 16;
    (void)_t_I64_2132;
    return _t_I64_2132;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2133 = Str_cmp(a, b);
    (void)_t_I64_2133;
    I64 _t_I64_2134 = 0;
    (void)_t_I64_2134;
    Bool _t_Bool_2135 = I64_eq(_t_I64_2133, _t_I64_2134);
    (void)_t_Bool_2135;
    ;
    ;
    return _t_Bool_2135;
}

Bool Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2136 = 0;
    (void)_t_I64_2136;
    I64 _t_I64_2137 = 1;
    (void)_t_I64_2137;
    I64 _t_I64_2138 = Str_cmp(a, b);
    (void)_t_I64_2138;
    I64 _t_I64_2139 = I64_sub(_t_I64_2136, _t_I64_2137);
    (void)_t_I64_2139;
    ;
    ;
    Bool _t_Bool_2140 = I64_eq(_t_I64_2138, _t_I64_2139);
    (void)_t_Bool_2140;
    ;
    ;
    return _t_Bool_2140;
}

Bool Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2141 = Str_cmp(a, b);
    (void)_t_I64_2141;
    I64 _t_I64_2142 = 1;
    (void)_t_I64_2142;
    Bool _t_Bool_2143 = I64_eq(_t_I64_2141, _t_I64_2142);
    (void)_t_Bool_2143;
    ;
    ;
    return _t_Bool_2143;
}

Bool Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2144 = Str_eq(a, b);
    (void)_t_Bool_2144;
    Bool _t_Bool_2145 = not(_t_Bool_2144);
    (void)_t_Bool_2145;
    ;
    return _t_Bool_2145;
}

Bool Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2146 = Str_gt(a, b);
    (void)_t_Bool_2146;
    Bool _t_Bool_2147 = not(_t_Bool_2146);
    (void)_t_Bool_2147;
    ;
    return _t_Bool_2147;
}

Bool Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2148 = Str_lt(a, b);
    (void)_t_Bool_2148;
    Bool _t_Bool_2149 = not(_t_Bool_2148);
    (void)_t_Bool_2149;
    ;
    return _t_Bool_2149;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_2181 = 8;
    (void)_t_I64_2181;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2181; return _r; }
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
    I64 _t_I64_2184 = I16_to_i64(DEREF(val));
    (void)_t_I64_2184;
    Str *_t_Str_2185 = I64_to_str(&_t_I64_2184);
    (void)_t_Str_2185;
    ;
    return _t_Str_2185;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t_I16_2186 = 1;
    (void)_t_I16_2186;
    I16 _t_I16_2187 = I16_add(DEREF(self), _t_I16_2186);
    (void)_t_I16_2187;
    ;
    *self = _t_I16_2187;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t_I16_2188 = 1;
    (void)_t_I16_2188;
    I16 _t_I16_2189 = I16_sub(DEREF(self), _t_I16_2188);
    (void)_t_I16_2189;
    ;
    *self = _t_I16_2189;
    ;
}

I16 * I16_unity(I16 * _self) {
    (void)_self;
    I64 _t_I64_2190 = 1;
    (void)_t_I64_2190;
    I16 _t_I16_2191 = I64_to_i16(_t_I64_2190);
    (void)_t_I16_2191;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2191; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t_I64_2192 = 0;
    (void)_t_I64_2192;
    I64 _t_I64_2193 = I16_to_i64(DEREF(a));
    (void)_t_I64_2193;
    I64 _t_I64_2194 = I64_sub(_t_I64_2192, _t_I64_2193);
    (void)_t_I64_2194;
    ;
    ;
    I16 _t_I16_2195 = I64_to_i16(_t_I64_2194);
    (void)_t_I16_2195;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2195; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t_I64_2200 = I16_to_i64(DEREF(a));
    (void)_t_I64_2200;
    I64 _t_I64_2201 = 0;
    (void)_t_I64_2201;
    Bool _t_Bool_2202 = I64_lt(&_t_I64_2200, &_t_I64_2201);
    (void)_t_Bool_2202;
    ;
    ;
    if (_t_Bool_2202) {
        I64 _t_I64_2196 = 0;
        (void)_t_I64_2196;
        I64 _t_I64_2197 = I16_to_i64(DEREF(a));
        (void)_t_I64_2197;
        I64 _t_I64_2198 = I64_sub(_t_I64_2196, _t_I64_2197);
        (void)_t_I64_2198;
        ;
        ;
        I16 _t_I16_2199 = I64_to_i16(_t_I64_2198);
        (void)_t_I16_2199;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2199; return _r; }
    }
    ;
    I16 _t_I16_2203 = I16_clone(a);
    (void)_t_I16_2203;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_2203; return _r; }
}

U64 I16_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I16 *au = a;
    (void)au;
    I16 *bu = b;
    (void)bu;
    Bool _t_Bool_2207 = I16_lte(au, bu);
    (void)_t_Bool_2207;
    if (_t_Bool_2207) {
        I16 _t_I16_2204 = I16_sub(DEREF(bu), DEREF(au));
        (void)_t_I16_2204;
        I64 _t_I64_2205 = I16_to_i64(_t_I16_2204);
        (void)_t_I64_2205;
        ;
        U64 _t_U64_2206 = I64_to_u64(_t_I64_2205);
        (void)_t_U64_2206;
        ;
        ;
        return _t_U64_2206;
    }
    ;
    I16 _t_I16_2208 = I16_sub(DEREF(au), DEREF(bu));
    (void)_t_I16_2208;
    I64 _t_I64_2209 = I16_to_i64(_t_I16_2208);
    (void)_t_I64_2209;
    ;
    U64 _t_U64_2210 = I64_to_u64(_t_I64_2209);
    (void)_t_U64_2210;
    ;
    return _t_U64_2210;
}

void I16_delete(I16 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I16_size(void) {
    I64 _t_I64_2211 = 2;
    (void)_t_I64_2211;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2211; return _r; }
}

Bool I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2212 = 0;
    (void)_t_I64_2212;
    I64 _t_I64_2213 = 1;
    (void)_t_I64_2213;
    I64 _t_I64_2214 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2214;
    I64 _t_I64_2215 = I64_sub(_t_I64_2212, _t_I64_2213);
    (void)_t_I64_2215;
    ;
    ;
    Bool _t_Bool_2216 = I64_eq(_t_I64_2214, _t_I64_2215);
    (void)_t_Bool_2216;
    ;
    ;
    return _t_Bool_2216;
}

Bool I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2217 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2217;
    I64 _t_I64_2218 = 1;
    (void)_t_I64_2218;
    Bool _t_Bool_2219 = I64_eq(_t_I64_2217, _t_I64_2218);
    (void)_t_Bool_2219;
    ;
    ;
    return _t_Bool_2219;
}

Bool I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2220 = I16_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2220;
    Bool _t_Bool_2221 = not(_t_Bool_2220);
    (void)_t_Bool_2221;
    ;
    return _t_Bool_2221;
}

Bool I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2222 = I16_gt(a, b);
    (void)_t_Bool_2222;
    Bool _t_Bool_2223 = not(_t_Bool_2222);
    (void)_t_Bool_2223;
    ;
    return _t_Bool_2223;
}

Bool I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2224 = I16_lt(a, b);
    (void)_t_Bool_2224;
    Bool _t_Bool_2225 = not(_t_Bool_2224);
    (void)_t_Bool_2225;
    ;
    return _t_Bool_2225;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_2262 = 0;
    (void)_t_I64_2262;
    Bool _t_Bool_2263 = I64_eq(DEREF(val), _t_I64_2262);
    (void)_t_Bool_2263;
    ;
    if (_t_Bool_2263) {
        U64 _t_U64_2226 = 2;
        (void)_t_U64_2226;
        void * buf = malloc(_t_U64_2226);
        (void)buf;
        ;
        I64 _t_I64_2227 = 48;
        (void)_t_I64_2227;
        U64 _t_U64_2228 = 1;
        (void)_t_U64_2228;
        memcpy(buf, &_t_I64_2227, _t_U64_2228);
        ;
        ;
        U64 _t_U64_2229 = 1;
        (void)_t_U64_2229;
        void *_t_v_2230 = ptr_add(buf, _t_U64_2229);
        (void)_t_v_2230;
        I32 _t_I32_2231 = 0;
        (void)_t_I32_2231;
        U64 _t_U64_2232 = 1;
        (void)_t_U64_2232;
        memset(_t_v_2230, _t_I32_2231, _t_U64_2232);
        ;
        ;
        ;
        I64 _t_I64_2233 = 1;
        (void)_t_I64_2233;
        I64 _t_I64_2234 = 1;
        (void)_t_I64_2234;
        Str *_t_Str_2235 = malloc(sizeof(Str));
        _t_Str_2235->c_str = buf;
        _t_Str_2235->count = _t_I64_2233;
        _t_Str_2235->cap = _t_I64_2234;
        (void)_t_Str_2235;
        ;
        ;
        ;
        return _t_Str_2235;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t_I64_2264 = 0;
    (void)_t_I64_2264;
    Bool _t_Bool_2265 = I64_lt(val, &_t_I64_2264);
    (void)_t_Bool_2265;
    ;
    if (_t_Bool_2265) {
        Bool _t_Bool_2236 = 1;
        (void)_t_Bool_2236;
        is_neg = _t_Bool_2236;
        ;
        I64 _t_I64_2237 = 0;
        (void)_t_I64_2237;
        I64 _t_I64_2238 = I64_sub(_t_I64_2237, DEREF(val));
        (void)_t_I64_2238;
        ;
        v = _t_I64_2238;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&v);
    (void)tmp;
    while (1) {
        I64 _t_I64_2240 = 0;
        (void)_t_I64_2240;
        Bool _wcond_Bool_2239 = I64_gt(&tmp, &_t_I64_2240);
        (void)_wcond_Bool_2239;
        ;
        if (_wcond_Bool_2239) {
        } else {
            ;
            break;
        }
        ;
        U64 _t_U64_2241 = 1;
        (void)_t_U64_2241;
        U64 _t_U64_2242 = U64_add(ndigits, _t_U64_2241);
        (void)_t_U64_2242;
        ;
        ndigits = _t_U64_2242;
        ;
        I64 _t_I64_2243 = 10;
        (void)_t_I64_2243;
        I64 _t_I64_2244 = I64_div(tmp, _t_I64_2243);
        (void)_t_I64_2244;
        ;
        tmp = _t_I64_2244;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    (void)total;
    ;
    if (is_neg) {
        U64 _t_U64_2245 = 1;
        (void)_t_U64_2245;
        U64 _t_U64_2246 = U64_add(total, _t_U64_2245);
        (void)_t_U64_2246;
        ;
        total = _t_U64_2246;
        ;
    }
    U64 _t_U64_2266 = 1;
    (void)_t_U64_2266;
    U64 _t_U64_2267 = U64_add(total, _t_U64_2266);
    (void)_t_U64_2267;
    ;
    void * buf = malloc(_t_U64_2267);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t_I64_2247 = 45;
        (void)_t_I64_2247;
        U64 _t_U64_2248 = 1;
        (void)_t_U64_2248;
        memcpy(buf, &_t_I64_2247, _t_U64_2248);
        ;
        ;
    }
    ;
    U64 _t_U64_2268 = 1;
    (void)_t_U64_2268;
    U64 i = U64_sub(total, _t_U64_2268);
    (void)i;
    ;
    while (1) {
        I64 _t_I64_2250 = 0;
        (void)_t_I64_2250;
        Bool _wcond_Bool_2249 = I64_gt(&v, &_t_I64_2250);
        (void)_wcond_Bool_2249;
        ;
        if (_wcond_Bool_2249) {
        } else {
            ;
            break;
        }
        ;
        I64 _t_I64_2251 = 10;
        (void)_t_I64_2251;
        I64 _t_I64_2252 = I64_mod(v, _t_I64_2251);
        (void)_t_I64_2252;
        ;
        I64 _t_I64_2253 = 48;
        (void)_t_I64_2253;
        I64 _t_I64_2254 = I64_add(_t_I64_2252, _t_I64_2253);
        (void)_t_I64_2254;
        ;
        ;
        void *_t_v_2255 = ptr_add(buf, i);
        (void)_t_v_2255;
        U8 _t_U8_2256 = I64_to_u8(_t_I64_2254);
        (void)_t_U8_2256;
        ;
        U64 _t_U64_2257 = 1;
        (void)_t_U64_2257;
        memcpy(_t_v_2255, &_t_U8_2256, _t_U64_2257);
        ;
        ;
        I64 _t_I64_2258 = 10;
        (void)_t_I64_2258;
        I64 _t_I64_2259 = I64_div(v, _t_I64_2258);
        (void)_t_I64_2259;
        ;
        v = _t_I64_2259;
        ;
        U64 _t_U64_2260 = 1;
        (void)_t_U64_2260;
        U64 _t_U64_2261 = U64_sub(i, _t_U64_2260);
        (void)_t_U64_2261;
        ;
        i = _t_U64_2261;
        ;
    }
    ;
    ;
    void *_t_v_2269 = ptr_add(buf, total);
    (void)_t_v_2269;
    I32 _t_I32_2270 = 0;
    (void)_t_I32_2270;
    U64 _t_U64_2271 = 1;
    (void)_t_U64_2271;
    memset(_t_v_2269, _t_I32_2270, _t_U64_2271);
    ;
    ;
    Str *_t_Str_2272 = malloc(sizeof(Str));
    _t_Str_2272->c_str = buf;
    _t_Str_2272->count = total;
    _t_Str_2272->cap = total;
    (void)_t_Str_2272;
    ;
    return _t_Str_2272;
}

U32 I64_to_usize(I64 val) {
    (void)val;
    U32 _t_U32_2273 = I64_to_u32(val);
    (void)_t_U32_2273;
    return _t_U32_2273;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t_I64_2274 = 1;
    (void)_t_I64_2274;
    I64 _t_I64_2275 = I64_add(DEREF(self), _t_I64_2274);
    (void)_t_I64_2275;
    ;
    *self = _t_I64_2275;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t_I64_2276 = 1;
    (void)_t_I64_2276;
    I64 _t_I64_2277 = I64_sub(DEREF(self), _t_I64_2276);
    (void)_t_I64_2277;
    ;
    *self = _t_I64_2277;
    ;
}

I64 * I64_unity(I64 * _self) {
    (void)_self;
    I64 _t_I64_2278 = 1;
    (void)_t_I64_2278;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2278; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t_I64_2279 = 0;
    (void)_t_I64_2279;
    I64 _t_I64_2280 = I64_sub(_t_I64_2279, DEREF(a));
    (void)_t_I64_2280;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2280; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t_I64_2283 = 0;
    (void)_t_I64_2283;
    Bool _t_Bool_2284 = I64_lt(a, &_t_I64_2283);
    (void)_t_Bool_2284;
    ;
    if (_t_Bool_2284) {
        I64 _t_I64_2281 = 0;
        (void)_t_I64_2281;
        I64 _t_I64_2282 = I64_sub(_t_I64_2281, DEREF(a));
        (void)_t_I64_2282;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2282; return _r; }
    }
    ;
    I64 _t_I64_2285 = I64_clone(a);
    (void)_t_I64_2285;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2285; return _r; }
}

U64 I64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I64 *au = a;
    (void)au;
    I64 *bu = b;
    (void)bu;
    Bool _t_Bool_2288 = I64_lte(au, bu);
    (void)_t_Bool_2288;
    if (_t_Bool_2288) {
        I64 _t_I64_2286 = I64_sub(DEREF(bu), DEREF(au));
        (void)_t_I64_2286;
        U64 _t_U64_2287 = I64_to_u64(_t_I64_2286);
        (void)_t_U64_2287;
        ;
        ;
        return _t_U64_2287;
    }
    ;
    I64 _t_I64_2289 = I64_sub(DEREF(au), DEREF(bu));
    (void)_t_I64_2289;
    U64 _t_U64_2290 = I64_to_u64(_t_I64_2289);
    (void)_t_U64_2290;
    ;
    return _t_U64_2290;
}

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_2291 = 8;
    (void)_t_I64_2291;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2291; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2292 = 0;
    (void)_t_I64_2292;
    I64 _t_I64_2293 = 1;
    (void)_t_I64_2293;
    I64 _t_I64_2294 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2294;
    I64 _t_I64_2295 = I64_sub(_t_I64_2292, _t_I64_2293);
    (void)_t_I64_2295;
    ;
    ;
    Bool _t_Bool_2296 = I64_eq(_t_I64_2294, _t_I64_2295);
    (void)_t_Bool_2296;
    ;
    ;
    return _t_Bool_2296;
}

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2297 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_2297;
    I64 _t_I64_2298 = 1;
    (void)_t_I64_2298;
    Bool _t_Bool_2299 = I64_eq(_t_I64_2297, _t_I64_2298);
    (void)_t_Bool_2299;
    ;
    ;
    return _t_Bool_2299;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2300 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2300;
    Bool _t_Bool_2301 = not(_t_Bool_2300);
    (void)_t_Bool_2301;
    ;
    return _t_Bool_2301;
}

Bool I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2302 = I64_gt(a, b);
    (void)_t_Bool_2302;
    Bool _t_Bool_2303 = not(_t_Bool_2302);
    (void)_t_Bool_2303;
    ;
    return _t_Bool_2303;
}

Bool I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2304 = I64_lt(a, b);
    (void)_t_Bool_2304;
    Bool _t_Bool_2305 = not(_t_Bool_2304);
    (void)_t_Bool_2305;
    ;
    return _t_Bool_2305;
}

Str * Bool_to_str(Bool * b) {
    (void)b;
    if (DEREF(b)) {
        Str *_t_Str_2306 = Str_lit("true", 4ULL);
        (void)_t_Str_2306;
        return _t_Str_2306;
    } else {
        Str *_t_Str_2307 = Str_lit("false", 5ULL);
        (void)_t_Str_2307;
        return _t_Str_2307;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2312 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2312;
    if (_t_Bool_2312) {
        I64 _t_I64_2308 = 0;
        (void)_t_I64_2308;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2308; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_2309 = 0;
        (void)_t_I64_2309;
        I64 _t_I64_2310 = 1;
        (void)_t_I64_2310;
        I64 _t_I64_2311 = I64_sub(_t_I64_2309, _t_I64_2310);
        (void)_t_I64_2311;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2311; return _r; }
    }
    I64 _t_I64_2313 = 1;
    (void)_t_I64_2313;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_2313; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_2314 = 1;
    (void)_t_I64_2314;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_2314; return _r; }
}

Bool Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2315 = 0;
    (void)_t_I64_2315;
    I64 _t_I64_2316 = 1;
    (void)_t_I64_2316;
    I64 _t_I64_2317; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_2317 = *_hp; free(_hp); }
    (void)_t_I64_2317;
    I64 _t_I64_2318 = I64_sub(_t_I64_2315, _t_I64_2316);
    (void)_t_I64_2318;
    ;
    ;
    Bool _t_Bool_2319 = I64_eq(_t_I64_2317, _t_I64_2318);
    (void)_t_Bool_2319;
    ;
    ;
    return _t_Bool_2319;
}

Bool Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_2320; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_2320 = *_hp; free(_hp); }
    (void)_t_I64_2320;
    I64 _t_I64_2321 = 1;
    (void)_t_I64_2321;
    Bool _t_Bool_2322 = I64_eq(_t_I64_2320, _t_I64_2321);
    (void)_t_Bool_2322;
    ;
    ;
    return _t_Bool_2322;
}

Bool Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2323 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_2323;
    Bool _t_Bool_2324 = not(_t_Bool_2323);
    (void)_t_Bool_2324;
    ;
    return _t_Bool_2324;
}

Bool Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2325 = Bool_gt(a, b);
    (void)_t_Bool_2325;
    Bool _t_Bool_2326 = not(_t_Bool_2325);
    (void)_t_Bool_2326;
    ;
    return _t_Bool_2326;
}

Bool Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_2327 = Bool_lt(a, b);
    (void)_t_Bool_2327;
    Bool _t_Bool_2328 = not(_t_Bool_2327);
    (void)_t_Bool_2328;
    ;
    return _t_Bool_2328;
}

Array * Array_new(Str * elem_type, U32 * cap) {
    (void)elem_type;
    (void)cap;
    Bool _t_Bool_2334 = Str_is_empty(elem_type);
    (void)_t_Bool_2334;
    if (_t_Bool_2334) {
        Str *_t_Str_2329 = Str_lit("Str", 3ULL);
        (void)_t_Str_2329;
        U32 _t_U32_2330 = 1;
        (void)_t_U32_2330;
        Array *_va_Array_73 = Array_new(_t_Str_2329, &_t_U32_2330);
        (void)_va_Array_73;
        Str_delete(_t_Str_2329, &(Bool){1});
        ;
        U32 _t_U32_2331 = 0;
        (void)_t_U32_2331;
        Str *_t_Str_2332 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_2332;
        Array_set(_va_Array_73, &_t_U32_2331, _t_Str_2332);
        ;
        Str *_t_Str_2333 = Str_lit("./src/core/array.til:22:41", 26ULL);
        (void)_t_Str_2333;
        panic(_t_Str_2333, _va_Array_73);
        Str_delete(_t_Str_2333, &(Bool){1});
    }
    ;
    U32 elem_size = dyn_size_of(elem_type);
    (void)elem_size;
    void * _t_v_2335 = calloc(DEREF(cap), elem_size);
    (void)_t_v_2335;
    void * _t_v_2336 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2336;
    void * _t_v_2337 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2337;
    Array *_t_Array_2338 = malloc(sizeof(Array));
    _t_Array_2338->data = _t_v_2335;
    _t_Array_2338->cap = DEREF(cap);
    _t_Array_2338->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); _t_Array_2338->elem_type = *_ca; free(_ca); }
    _t_Array_2338->elem_clone = _t_v_2336;
    _t_Array_2338->elem_delete = _t_v_2337;
    (void)_t_Array_2338;
    ;
    return _t_Array_2338;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_2352 = U32_gte(i, &self->cap);
    (void)_t_Bool_2352;
    if (_t_Bool_2352) {
        Str *_t_Str_2339 = Str_lit("Str", 3ULL);
        (void)_t_Str_2339;
        U32 _t_U32_2340 = 5;
        (void)_t_U32_2340;
        Array *_va_Array_74 = Array_new(_t_Str_2339, &_t_U32_2340);
        (void)_va_Array_74;
        Str_delete(_t_Str_2339, &(Bool){1});
        ;
        U32 _t_U32_2341 = 0;
        (void)_t_U32_2341;
        Str *_t_Str_2342 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_2342;
        Array_set(_va_Array_74, &_t_U32_2341, _t_Str_2342);
        ;
        U32 _t_U32_2343 = 1;
        (void)_t_U32_2343;
        Str *_t_Str_2344 = U32_to_str(i);
        (void)_t_Str_2344;
        Array_set(_va_Array_74, &_t_U32_2343, _t_Str_2344);
        ;
        U32 _t_U32_2345 = 2;
        (void)_t_U32_2345;
        Str *_t_Str_2346 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2346;
        Array_set(_va_Array_74, &_t_U32_2345, _t_Str_2346);
        ;
        U32 _t_U32_2347 = 3;
        (void)_t_U32_2347;
        Str *_t_Str_2348 = U32_to_str(&self->cap);
        (void)_t_Str_2348;
        Array_set(_va_Array_74, &_t_U32_2347, _t_Str_2348);
        ;
        U32 _t_U32_2349 = 4;
        (void)_t_U32_2349;
        Str *_t_Str_2350 = Str_lit(")", 1ULL);
        (void)_t_Str_2350;
        Array_set(_va_Array_74, &_t_U32_2349, _t_Str_2350);
        ;
        Str *_t_Str_2351 = Str_lit("./src/core/array.til:35:19", 26ULL);
        (void)_t_Str_2351;
        panic(_t_Str_2351, _va_Array_74);
        Str_delete(_t_Str_2351, &(Bool){1});
    }
    ;
    U32 _t_U64_2353 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2353;
    void *_t_v_2354 = ptr_add(self->data, _t_U64_2353);
    (void)_t_v_2354;
    ;
    return _t_v_2354;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_2368 = U32_gte(i, &self->cap);
    (void)_t_Bool_2368;
    if (_t_Bool_2368) {
        Str *_t_Str_2355 = Str_lit("Str", 3ULL);
        (void)_t_Str_2355;
        U32 _t_U32_2356 = 5;
        (void)_t_U32_2356;
        Array *_va_Array_75 = Array_new(_t_Str_2355, &_t_U32_2356);
        (void)_va_Array_75;
        Str_delete(_t_Str_2355, &(Bool){1});
        ;
        U32 _t_U32_2357 = 0;
        (void)_t_U32_2357;
        Str *_t_Str_2358 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_2358;
        Array_set(_va_Array_75, &_t_U32_2357, _t_Str_2358);
        ;
        U32 _t_U32_2359 = 1;
        (void)_t_U32_2359;
        Str *_t_Str_2360 = U32_to_str(i);
        (void)_t_Str_2360;
        Array_set(_va_Array_75, &_t_U32_2359, _t_Str_2360);
        ;
        U32 _t_U32_2361 = 2;
        (void)_t_U32_2361;
        Str *_t_Str_2362 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2362;
        Array_set(_va_Array_75, &_t_U32_2361, _t_Str_2362);
        ;
        U32 _t_U32_2363 = 3;
        (void)_t_U32_2363;
        Str *_t_Str_2364 = U32_to_str(&self->cap);
        (void)_t_Str_2364;
        Array_set(_va_Array_75, &_t_U32_2363, _t_Str_2364);
        ;
        U32 _t_U32_2365 = 4;
        (void)_t_U32_2365;
        Str *_t_Str_2366 = Str_lit(")", 1ULL);
        (void)_t_Str_2366;
        Array_set(_va_Array_75, &_t_U32_2365, _t_Str_2366);
        ;
        Str *_t_Str_2367 = Str_lit("./src/core/array.til:44:19", 26ULL);
        (void)_t_Str_2367;
        panic(_t_Str_2367, _va_Array_75);
        Str_delete(_t_Str_2367, &(Bool){1});
    }
    ;
    U32 _t_U64_2369 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2369;
    void *_t_v_2370 = ptr_add(self->data, _t_U64_2369);
    (void)_t_v_2370;
    Bool _t_Bool_2371 = 0;
    (void)_t_Bool_2371;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2370, &_t_Bool_2371);
    ;
    ;
    U32 _t_U64_2372 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2372;
    void *_t_v_2373 = ptr_add(self->data, _t_U64_2372);
    (void)_t_v_2373;
    memcpy(_t_v_2373, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_2374 = self->cap;
        (void)_re_U32_2374;
        U32 _rc_U32_2374 = 0;
        (void)_rc_U32_2374;
        Bool _t_Bool_2383 = U32_lte(&_rc_U32_2374, &_re_U32_2374);
        (void)_t_Bool_2383;
        if (_t_Bool_2383) {
            while (1) {
                Bool _wcond_Bool_2375 = U32_lt(&_rc_U32_2374, &_re_U32_2374);
                (void)_wcond_Bool_2375;
                if (_wcond_Bool_2375) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2374);
                (void)i;
                U32_inc(&_rc_U32_2374);
                U32 _t_U64_2376 = U32_mul(i, self->elem_size);
                (void)_t_U64_2376;
                ;
                void *_t_v_2377 = ptr_add(self->data, _t_U64_2376);
                (void)_t_v_2377;
                Bool _t_Bool_2378 = 0;
                (void)_t_Bool_2378;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2377, &_t_Bool_2378);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2379 = U32_gt(&_rc_U32_2374, &_re_U32_2374);
                (void)_wcond_Bool_2379;
                if (_wcond_Bool_2379) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2374);
                (void)i;
                U32_dec(&_rc_U32_2374);
                U32 _t_U64_2380 = U32_mul(i, self->elem_size);
                (void)_t_U64_2380;
                ;
                void *_t_v_2381 = ptr_add(self->data, _t_U64_2380);
                (void)_t_v_2381;
                Bool _t_Bool_2382 = 0;
                (void)_t_Bool_2382;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2381, &_t_Bool_2382);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_2384 = 0;
    (void)_t_Bool_2384;
    Str_delete(&self->elem_type, &_t_Bool_2384);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_2397 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_2397;
    void * new_data = malloc(_t_U64_2397);
    (void)new_data;
    ;
    {
        U32 _re_U32_2385 = self->cap;
        (void)_re_U32_2385;
        U32 _rc_U32_2385 = 0;
        (void)_rc_U32_2385;
        Bool _t_Bool_2396 = U32_lte(&_rc_U32_2385, &_re_U32_2385);
        (void)_t_Bool_2396;
        if (_t_Bool_2396) {
            while (1) {
                Bool _wcond_Bool_2386 = U32_lt(&_rc_U32_2385, &_re_U32_2385);
                (void)_wcond_Bool_2386;
                if (_wcond_Bool_2386) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2385);
                (void)i;
                U32_inc(&_rc_U32_2385);
                U32 _t_U64_2387 = U32_mul(i, self->elem_size);
                (void)_t_U64_2387;
                void *_t_v_2388 = ptr_add(self->data, _t_U64_2387);
                (void)_t_v_2388;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2388);
                (void)cloned;
                ;
                U32 _t_U64_2389 = U32_mul(i, self->elem_size);
                (void)_t_U64_2389;
                ;
                void *_t_v_2390 = ptr_add(new_data, _t_U64_2389);
                (void)_t_v_2390;
                memcpy(_t_v_2390, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2391 = U32_gt(&_rc_U32_2385, &_re_U32_2385);
                (void)_wcond_Bool_2391;
                if (_wcond_Bool_2391) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2385);
                (void)i;
                U32_dec(&_rc_U32_2385);
                U32 _t_U64_2392 = U32_mul(i, self->elem_size);
                (void)_t_U64_2392;
                void *_t_v_2393 = ptr_add(self->data, _t_U64_2392);
                (void)_t_v_2393;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2393);
                (void)cloned;
                ;
                U32 _t_U64_2394 = U32_mul(i, self->elem_size);
                (void)_t_U64_2394;
                ;
                void *_t_v_2395 = ptr_add(new_data, _t_U64_2394);
                (void)_t_v_2395;
                memcpy(_t_v_2395, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_2398 = malloc(sizeof(Array));
    _t_Array_2398->data = new_data;
    _t_Array_2398->cap = self->cap;
    _t_Array_2398->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_2398->elem_type = *_ca; free(_ca); }
    _t_Array_2398->elem_clone = (void *)self->elem_clone;
    _t_Array_2398->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_2398;
    return _t_Array_2398;
}

U32 Array_size(void) {
    I64 _t_I64_2399 = 48;
    (void)_t_I64_2399;
    return _t_I64_2399;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2622 = Str_lit("Str", 3ULL);
    (void)_t_Str_2622;
    U32 _t_U32_2623 = 3;
    (void)_t_U32_2623;
    Array *_va_Array_92 = Array_new(_t_Str_2622, &_t_U32_2623);
    (void)_va_Array_92;
    Str_delete(_t_Str_2622, &(Bool){1});
    ;
    U32 _t_U32_2624 = 0;
    (void)_t_U32_2624;
    Str *_t_Str_2625 = Str_clone(loc_str);
    (void)_t_Str_2625;
    Array_set(_va_Array_92, &_t_U32_2624, _t_Str_2625);
    ;
    U32 _t_U32_2626 = 1;
    (void)_t_U32_2626;
    Str *_t_Str_2627 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2627;
    Array_set(_va_Array_92, &_t_U32_2626, _t_Str_2627);
    ;
    Array *_t_Array_2628 = Array_clone(parts);
    (void)_t_Array_2628;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2629 = 2;
    (void)_t_U32_2629;
    Str *_t_Str_2630 = format(_t_Array_2628);
    (void)_t_Str_2630;
    Array_set(_va_Array_92, &_t_U32_2629, _t_Str_2630);
    ;
    println(_va_Array_92);
    I64 _t_I64_2631 = 1;
    (void)_t_I64_2631;
    exit(_t_I64_2631);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2647 = not(DEREF(cond));
    (void)_t_Bool_2647;
    if (_t_Bool_2647) {
        Str *_t_Str_2643 = Str_lit("Str", 3ULL);
        (void)_t_Str_2643;
        U32 _t_U32_2644 = 1;
        (void)_t_U32_2644;
        Array *_va_Array_95 = Array_new(_t_Str_2643, &_t_U32_2644);
        (void)_va_Array_95;
        Str_delete(_t_Str_2643, &(Bool){1});
        ;
        U32 _t_U32_2645 = 0;
        (void)_t_U32_2645;
        Str *_t_Str_2646 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2646;
        Array_set(_va_Array_95, &_t_U32_2645, _t_Str_2646);
        ;
        panic(loc_str, _va_Array_95);
    }
    ;
    Bool _t_Bool_2648 = 1;
    (void)_t_Bool_2648;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2648; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2669 = I64_neq(a, b);
    (void)_t_Bool_2669;
    if (_t_Bool_2669) {
        Str *_t_Str_2657 = Str_lit("Str", 3ULL);
        (void)_t_Str_2657;
        U32 _t_U32_2658 = 5;
        (void)_t_U32_2658;
        Array *_va_Array_97 = Array_new(_t_Str_2657, &_t_U32_2658);
        (void)_va_Array_97;
        Str_delete(_t_Str_2657, &(Bool){1});
        ;
        U32 _t_U32_2659 = 0;
        (void)_t_U32_2659;
        Str *_t_Str_2660 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2660;
        Array_set(_va_Array_97, &_t_U32_2659, _t_Str_2660);
        ;
        U32 _t_U32_2661 = 1;
        (void)_t_U32_2661;
        Str *_t_Str_2662 = I64_to_str(a);
        (void)_t_Str_2662;
        Array_set(_va_Array_97, &_t_U32_2661, _t_Str_2662);
        ;
        U32 _t_U32_2663 = 2;
        (void)_t_U32_2663;
        Str *_t_Str_2664 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2664;
        Array_set(_va_Array_97, &_t_U32_2663, _t_Str_2664);
        ;
        U32 _t_U32_2665 = 3;
        (void)_t_U32_2665;
        Str *_t_Str_2666 = I64_to_str(b);
        (void)_t_Str_2666;
        Array_set(_va_Array_97, &_t_U32_2665, _t_Str_2666);
        ;
        U32 _t_U32_2667 = 4;
        (void)_t_U32_2667;
        Str *_t_Str_2668 = Str_lit("'", 1ULL);
        (void)_t_Str_2668;
        Array_set(_va_Array_97, &_t_U32_2667, _t_Str_2668);
        ;
        panic(loc_str, _va_Array_97);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2684 = parts;
        (void)_fc_Array_2684;
        U32 _fi_USize_2684 = 0;
        (void)_fi_USize_2684;
        while (1) {
            U32 _t_U32_2686; { U32 *_hp = (U32 *)Array_len(_fc_Array_2684); _t_U32_2686 = *_hp; free(_hp); }
            (void)_t_U32_2686;
            Bool _wcond_Bool_2685 = U32_lt(&_fi_USize_2684, &_t_U32_2686);
            (void)_wcond_Bool_2685;
            ;
            if (_wcond_Bool_2685) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2684, &_fi_USize_2684);
            (void)s;
            U32 _t_U32_2687 = 1;
            (void)_t_U32_2687;
            U32 _t_U32_2688 = U32_add(_fi_USize_2684, _t_U32_2687);
            (void)_t_U32_2688;
            ;
            _fi_USize_2684 = _t_U32_2688;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

void test_simple_add(void) {
    I64 _t_I64_2874 = 1;
    (void)_t_I64_2874;
    I64 _t_I64_2875 = 2;
    (void)_t_I64_2875;
    I64 result = 3;
    (void)result;
    ;
    ;
    Str *_t_Str_2876 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_2876;
    I64 _t_I64_2877 = 3;
    (void)_t_I64_2877;
    assert_eq(_t_Str_2876, &result, &_t_I64_2877);
    ;
    Str_delete(_t_Str_2876, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 _t_I64_2878 = 1;
    (void)_t_I64_2878;
    I64 _t_I64_2879 = 2;
    (void)_t_I64_2879;
    I64 _t_I64_2880 = 10;
    (void)_t_I64_2880;
    I64 _t_I64_2881 = 5;
    (void)_t_I64_2881;
    I64 _t_I64_2882 = 3;
    (void)_t_I64_2882;
    ;
    ;
    I64 _t_I64_2883 = 5;
    (void)_t_I64_2883;
    ;
    ;
    I64 result = 15;
    (void)result;
    ;
    ;
    Str *_t_Str_2884 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_2884;
    I64 _t_I64_2885 = 15;
    (void)_t_I64_2885;
    assert_eq(_t_Str_2884, &result, &_t_I64_2885);
    ;
    Str_delete(_t_Str_2884, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 _t_I64_2886 = 2;
    (void)_t_I64_2886;
    I64 _t_I64_2887 = 3;
    (void)_t_I64_2887;
    I64 _t_I64_2888 = 4;
    (void)_t_I64_2888;
    I64 _t_I64_2889 = 5;
    (void)_t_I64_2889;
    I64 _t_I64_2890 = 6;
    (void)_t_I64_2890;
    ;
    ;
    I64 _t_I64_2891 = 20;
    (void)_t_I64_2891;
    ;
    ;
    I64 result = 26;
    (void)result;
    ;
    ;
    Str *_t_Str_2892 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_2892;
    I64 _t_I64_2893 = 26;
    (void)_t_I64_2893;
    assert_eq(_t_Str_2892, &result, &_t_I64_2893);
    ;
    Str_delete(_t_Str_2892, &(Bool){1});
    ;
}

Str * poem(I64 * depth, Str * current, Str * s1, Str * s2) {
    (void)depth;
    (void)current;
    (void)s1;
    (void)s2;
    I64 _t_I64_2901 = 4;
    (void)_t_I64_2901;
    Bool _t_Bool_2902 = I64_eq(DEREF(depth), _t_I64_2901);
    (void)_t_Bool_2902;
    ;
    if (_t_Bool_2902) {
        Str *_t_Str_2894 = Str_lit("\n", 2ULL);
        (void)_t_Str_2894;
        Str *_t_Str_2895 = Str_concat(current, _t_Str_2894);
        (void)_t_Str_2895;
        Str_delete(_t_Str_2894, &(Bool){1});
        ;
        return _t_Str_2895;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    I64 _t_I64_2903 = 1;
    (void)_t_I64_2903;
    I64 _t_I64_2904 = I64_add(DEREF(depth), _t_I64_2903);
    (void)_t_I64_2904;
    ;
    Str *_t_Str_2905 = Str_concat(current, s1);
    (void)_t_Str_2905;
    Str *_t_Str_2906 = poem(&_t_I64_2904, _t_Str_2905, s1, s2);
    (void)_t_Str_2906;
    ;
    Str_delete(_t_Str_2905, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2906); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2906, &(Bool){1});
    I64 _t_I64_2907 = 1;
    (void)_t_I64_2907;
    I64 _t_I64_2908 = I64_add(DEREF(depth), _t_I64_2907);
    (void)_t_I64_2908;
    ;
    Str *_t_Str_2909 = Str_concat(current, s2);
    (void)_t_Str_2909;
    Str *_t_Str_2910 = poem(&_t_I64_2908, _t_Str_2909, s1, s2);
    (void)_t_Str_2910;
    ;
    Str_delete(_t_Str_2909, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_2910); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_2910, &(Bool){1});
    I64 _t_I64_2911 = 2;
    (void)_t_I64_2911;
    Bool _t_Bool_2912 = I64_eq(DEREF(depth), _t_I64_2911);
    (void)_t_Bool_2912;
    ;
    if (_t_Bool_2912) {
        I64 _t_I64_2896 = 1;
        (void)_t_I64_2896;
        Str *_t_Str_2897 = Str_lit("lei", 3ULL);
        (void)_t_Str_2897;
        I64 _t_I64_2898 = I64_add(DEREF(depth), _t_I64_2896);
        (void)_t_I64_2898;
        ;
        Str *_t_Str_2899 = Str_concat(current, _t_Str_2897);
        (void)_t_Str_2899;
        Str_delete(_t_Str_2897, &(Bool){1});
        Str *_t_Str_2900 = poem(&_t_I64_2898, _t_Str_2899, s1, s2);
        (void)_t_Str_2900;
        ;
        Str_delete(_t_Str_2899, &(Bool){1});
        { Str *_old = result; result = Str_concat(result, _t_Str_2900); Str_delete(_old, &(Bool){1}); }
        Str_delete(_t_Str_2900, &(Bool){1});
    }
    ;
    return result;
}

Str * make_poem(Str * s1, Str * s2) {
    (void)s1;
    (void)s2;
    I64 _t_I64_2913 = 0;
    (void)_t_I64_2913;
    Str *_t_Str_2914 = Str_lit("", 0ULL);
    (void)_t_Str_2914;
    Str *_t_Str_2915 = poem(&_t_I64_2913, _t_Str_2914, s1, s2);
    (void)_t_Str_2915;
    ;
    Str_delete(_t_Str_2914, &(Bool){1});
    return _t_Str_2915;
}

void test_lolalalo(void) {
    Str *_t_Str_2916 = Str_lit("lo", 2ULL);
    (void)_t_Str_2916;
    Str *_t_Str_2917 = Str_lit("la", 2ULL);
    (void)_t_Str_2917;
    Str *lo_la = make_poem(_t_Str_2916, _t_Str_2917);
    (void)lo_la;
    Str_delete(_t_Str_2916, &(Bool){1});
    Str_delete(_t_Str_2917, &(Bool){1});
    Str *_t_Str_2918 = Str_lit("la", 2ULL);
    (void)_t_Str_2918;
    Str *_t_Str_2919 = Str_lit("lo", 2ULL);
    (void)_t_Str_2919;
    Str *la_lo = make_poem(_t_Str_2918, _t_Str_2919);
    (void)la_lo;
    Str_delete(_t_Str_2918, &(Bool){1});
    Str_delete(_t_Str_2919, &(Bool){1});
    Str *_t_Str_2920 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_2920;
    Str *_t_Str_2921 = Str_lit("src/test/constfold.til:56:12", 28ULL);
    (void)_t_Str_2921;
    Bool _t_Bool_2922 = Str_contains(lo_la, _t_Str_2920);
    (void)_t_Bool_2922;
    Str_delete(_t_Str_2920, &(Bool){1});
    Bool _t_Bool_2923; { Bool *_hp = (Bool *)assert(_t_Str_2921, &_t_Bool_2922); _t_Bool_2923 = *_hp; free(_hp); }
    (void)_t_Bool_2923;
    ;
    ;
    Str_delete(_t_Str_2921, &(Bool){1});
    Str *_t_Str_2924 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_2924;
    Str *_t_Str_2925 = Str_lit("src/test/constfold.til:57:12", 28ULL);
    (void)_t_Str_2925;
    Bool _t_Bool_2926 = Str_contains(la_lo, _t_Str_2924);
    (void)_t_Bool_2926;
    Str_delete(_t_Str_2924, &(Bool){1});
    Bool _t_Bool_2927; { Bool *_hp = (Bool *)assert(_t_Str_2925, &_t_Bool_2926); _t_Bool_2927 = *_hp; free(_hp); }
    (void)_t_Bool_2927;
    ;
    ;
    Str_delete(_t_Str_2925, &(Bool){1});
    Str *_t_Str_2928 = Str_lit("lolei", 5ULL);
    (void)_t_Str_2928;
    Str *_t_Str_2929 = Str_lit("src/test/constfold.til:59:12", 28ULL);
    (void)_t_Str_2929;
    Bool _t_Bool_2930 = Str_contains(lo_la, _t_Str_2928);
    (void)_t_Bool_2930;
    Str_delete(_t_Str_2928, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    Bool _t_Bool_2931; { Bool *_hp = (Bool *)assert(_t_Str_2929, &_t_Bool_2930); _t_Bool_2931 = *_hp; free(_hp); }
    (void)_t_Bool_2931;
    ;
    ;
    Str_delete(_t_Str_2929, &(Bool){1});
    Str *_t_Str_2932 = Str_lit("lalei", 5ULL);
    (void)_t_Str_2932;
    Str *_t_Str_2933 = Str_lit("src/test/constfold.til:60:12", 28ULL);
    (void)_t_Str_2933;
    Bool _t_Bool_2934 = Str_contains(la_lo, _t_Str_2932);
    (void)_t_Bool_2934;
    Str_delete(_t_Str_2932, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    Bool _t_Bool_2935; { Bool *_hp = (Bool *)assert(_t_Str_2933, &_t_Bool_2934); _t_Bool_2935 = *_hp; free(_hp); }
    (void)_t_Bool_2935;
    ;
    ;
    Str_delete(_t_Str_2933, &(Bool){1});
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "new_newi", 8ULL) == 0) return (void*)Vec_new_newi;
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
    I64 _t_I64_2175 = 0;
    (void)_t_I64_2175;
    I64 _t_I64_2176 = 1;
    (void)_t_I64_2176;
    I64 _t_I64_2177 = I64_sub(_t_I64_2175, _t_I64_2176);
    (void)_t_I64_2177;
    CAP_LIT = I64_to_usize(_t_I64_2177);
    (void)CAP_LIT;
    I64 _t_I64_2178 = 0;
    (void)_t_I64_2178;
    I64 _t_I64_2179 = 2;
    (void)_t_I64_2179;
    I64 _t_I64_2180 = I64_sub(_t_I64_2178, _t_I64_2179);
    (void)_t_I64_2180;
    CAP_VIEW = I64_to_usize(_t_I64_2180);
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
