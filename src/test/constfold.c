#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef struct Vec Vec;
typedef struct Str Str;
typedef struct Dynamic Dynamic;
typedef enum {
    Type_TAG_Unknown,
    Type_TAG_None,
    Type_TAG_I64,
    Type_TAG_U8,
    Type_TAG_I16,
    Type_TAG_I32,
    Type_TAG_U32,
    Type_TAG_U64,
    Type_TAG_F32,
    Type_TAG_Bool,
    Type_TAG_Struct,
    Type_TAG_StructDef,
    Type_TAG_Enum,
    Type_TAG_EnumDef,
    Type_TAG_FuncDef,
    Type_TAG_FuncPtr,
    Type_TAG_Dynamic,
    Type_TAG_Custom
} Type_tag;
typedef struct Type Type;
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





struct Type {
    Type_tag tag;
    union {
        Str Struct;
        Str Enum;
        Str Custom;
    } data;
};

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
Vec * Vec_new_type_name(Str * elem_type);
Vec * Vec_new(Type * T);
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
Bool Type_eq(Type * a, Type * b);
Bool Type_is(Type * self, Type * other);
void Type_delete(Type * self, Bool * call_free);
Str * Type_to_str(Type * self);
Type * Type_clone(Type * self);
U32 Type_size(void);
Array * Array_new_type_name(Str * elem_type, U32 * cap);
Array * Array_new(Type * T, U32 * cap);
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
Vec * Vec_new_type_name(Str * elem_type);
Vec * Vec_new(Type * T);
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
Bool Type_eq(Type * a, Type * b);
Bool Type_is(Type * self, Type * other);
void Type_delete(Type * self, Bool * call_free);
Str * Type_to_str(Type * self);
Type * Type_clone(Type * self);
U32 Type_size(void);
Array * Array_new_type_name(Str * elem_type, U32 * cap);
Array * Array_new(Type * T, U32 * cap);
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
Bool Type_eq(Type *, Type *);
Type *Type_Unknown();
Type *Type_None();
Type *Type_I64();
Type *Type_U8();
Type *Type_I16();
Type *Type_I32();
Type *Type_U32();
Type *Type_U64();
Type *Type_F32();
Type *Type_Bool();
Type *Type_Struct(Str *);
Type *Type_StructDef();
Type *Type_Enum(Str *);
Type *Type_EnumDef();
Type *Type_FuncDef();
Type *Type_FuncPtr();
Type *Type_Dynamic();
Type *Type_Custom(Str *);

void *dyn_fn(Str *type_name, Str *method);
U32 dyn_size_of(Str *type_name);
Str *dyn_type_to_str(Type *type);

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

Vec * Vec_new_type_name(Str * elem_type) {
    (void)elem_type;
    Bool _t_Bool_154 = Str_is_empty(elem_type);
    (void)_t_Bool_154;
    if (_t_Bool_154) {
        Str *_t_Str_142 = Str_lit("Str", 3ULL);
        (void)_t_Str_142;
        Type *_t_Type_143 = Type_Struct(_t_Str_142);
        (void)_t_Type_143;
        Str_delete(_t_Str_142, &(Bool){1});
        U32 _t_U32_144 = 1;
        (void)_t_U32_144;
        Array *_va_Array_0 = Array_new(_t_Type_143, &_t_U32_144);
        (void)_va_Array_0;
        Type_delete(_t_Type_143, &(Bool){1});
        ;
        U32 _t_U32_145 = 0;
        (void)_t_U32_145;
        Str *_t_Str_146 = Str_lit("Vec.new: elem_type required", 27ULL);
        (void)_t_Str_146;
        Array_set(_va_Array_0, &_t_U32_145, _t_Str_146);
        ;
        Str *_t_Str_147 = Str_lit("./src/core/vec.til:25:19", 24ULL);
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

Vec * Vec_new(Type * T) {
    (void)T;
    Str *elem_type = dyn_type_to_str(T);
    (void)elem_type;
    Vec *_t_Vec_163 = Vec_new_type_name(elem_type);
    (void)_t_Vec_163;
    Str_delete(elem_type, &(Bool){1});
    return _t_Vec_163;
}

U32 Vec_len(Vec * self) {
    (void)self;
    return self->count;
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    (void)val;
    Bool _t_Bool_168 = U32_eq(self->count, self->cap);
    (void)_t_Bool_168;
    if (_t_Bool_168) {
        U32 _t_U32_164 = 2;
        (void)_t_U32_164;
        U32 new_cap = U32_mul(self->cap, _t_U32_164);
        (void)new_cap;
        ;
        U32 _t_U64_165 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_165;
        void * _t_v_166 = realloc(self->data, _t_U64_165);
        (void)_t_v_166;
        ;
        self->data = _t_v_166;
        U32 _t_U32_167 = U32_clone(&new_cap);
        (void)_t_U32_167;
        ;
        self->cap = _t_U32_167;
        ;
    }
    ;
    U32 _t_U64_169 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_169;
    void *_t_v_170 = ptr_add(self->data, _t_U64_169);
    (void)_t_v_170;
    memcpy(_t_v_170, val, self->elem_size);
    ;
    free(val);
    U32 _t_U32_171 = 1;
    (void)_t_U32_171;
    U32 _t_U32_172 = U32_add(self->count, _t_U32_171);
    (void)_t_U32_172;
    ;
    self->count = _t_U32_172;
    ;
}

void Vec_append(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_185 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_185;
    Bool _t_Bool_186 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_186;
    Bool _t_Bool_187 = not(_t_Bool_185);
    (void)_t_Bool_187;
    ;
    Bool _t_Bool_188 = not(_t_Bool_186);
    (void)_t_Bool_188;
    ;
    Bool _t_Bool_189 = or(_t_Bool_187, _t_Bool_188);
    (void)_t_Bool_189;
    ;
    ;
    if (_t_Bool_189) {
        Str *_t_Str_173 = Str_lit("Str", 3ULL);
        (void)_t_Str_173;
        Type *_t_Type_174 = Type_Struct(_t_Str_173);
        (void)_t_Type_174;
        Str_delete(_t_Str_173, &(Bool){1});
        U32 _t_U32_175 = 1;
        (void)_t_U32_175;
        Array *_va_Array_1 = Array_new(_t_Type_174, &_t_U32_175);
        (void)_va_Array_1;
        Type_delete(_t_Type_174, &(Bool){1});
        ;
        U32 _t_U32_176 = 0;
        (void)_t_U32_176;
        Str *_t_Str_177 = Str_lit("Vec.append: incompatible vecs", 29ULL);
        (void)_t_Str_177;
        Array_set(_va_Array_1, &_t_U32_176, _t_Str_177);
        ;
        Str *_t_Str_178 = Str_lit("./src/core/vec.til:62:19", 24ULL);
        (void)_t_Str_178;
        panic(_t_Str_178, _va_Array_1);
        Str_delete(_t_Str_178, &(Bool){1});
    }
    ;
    U32 _t_U32_190 = 0;
    (void)_t_U32_190;
    Bool _t_Bool_191 = U32_eq(other->count, _t_U32_190);
    (void)_t_Bool_191;
    ;
    if (_t_Bool_191) {
        ;
        Vec_delete(other, &(Bool){0});
        return;
    }
    ;
    U32 needed = U32_add(self->count, other->count);
    (void)needed;
    Bool _t_Bool_192 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_192;
    if (_t_Bool_192) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_179 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_179;
            if (_wcond_Bool_179) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_180 = 2;
            (void)_t_U32_180;
            U32 _t_U32_181 = U32_mul(new_cap, _t_U32_180);
            (void)_t_U32_181;
            ;
            new_cap = _t_U32_181;
            ;
        }
        U32 _t_U64_182 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_182;
        void * _t_v_183 = realloc(self->data, _t_U64_182);
        (void)_t_v_183;
        ;
        self->data = _t_v_183;
        U32 _t_U32_184 = U32_clone(&new_cap);
        (void)_t_U32_184;
        ;
        self->cap = _t_U32_184;
        ;
    }
    ;
    U32 _t_U64_193 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_193;
    void *_t_v_194 = ptr_add(self->data, _t_U64_193);
    (void)_t_v_194;
    U32 _t_U64_195 = U32_mul(other->count, self->elem_size);
    (void)_t_U64_195;
    memcpy(_t_v_194, other->data, _t_U64_195);
    ;
    ;
    U32 _t_U32_196 = U32_clone(&needed);
    (void)_t_U32_196;
    ;
    self->count = _t_U32_196;
    ;
    U32 _t_U32_197 = 0;
    (void)_t_U32_197;
    other->count = _t_U32_197;
    ;
    Vec_delete(other, &(Bool){0});
}

void Vec_move_from(Vec * self, Vec * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_221 = U32_eq(self->elem_size, other->elem_size);
    (void)_t_Bool_221;
    Bool _t_Bool_222 = Str_eq(&self->elem_type, &other->elem_type);
    (void)_t_Bool_222;
    Bool _t_Bool_223 = not(_t_Bool_221);
    (void)_t_Bool_223;
    ;
    Bool _t_Bool_224 = not(_t_Bool_222);
    (void)_t_Bool_224;
    ;
    Bool _t_Bool_225 = or(_t_Bool_223, _t_Bool_224);
    (void)_t_Bool_225;
    ;
    ;
    if (_t_Bool_225) {
        Str *_t_Str_198 = Str_lit("Str", 3ULL);
        (void)_t_Str_198;
        Type *_t_Type_199 = Type_Struct(_t_Str_198);
        (void)_t_Type_199;
        Str_delete(_t_Str_198, &(Bool){1});
        U32 _t_U32_200 = 1;
        (void)_t_U32_200;
        Array *_va_Array_2 = Array_new(_t_Type_199, &_t_U32_200);
        (void)_va_Array_2;
        Type_delete(_t_Type_199, &(Bool){1});
        ;
        U32 _t_U32_201 = 0;
        (void)_t_U32_201;
        Str *_t_Str_202 = Str_lit("Vec.move_from: incompatible vecs", 32ULL);
        (void)_t_Str_202;
        Array_set(_va_Array_2, &_t_U32_201, _t_Str_202);
        ;
        Str *_t_Str_203 = Str_lit("./src/core/vec.til:89:19", 24ULL);
        (void)_t_Str_203;
        panic(_t_Str_203, _va_Array_2);
        Str_delete(_t_Str_203, &(Bool){1});
    }
    ;
    Bool _t_Bool_226 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_226;
    Str *_t_Str_227 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_227;
    Bool _t_Bool_228 = Str_eq(&self->elem_type, _t_Str_227);
    (void)_t_Bool_228;
    Str_delete(_t_Str_227, &(Bool){1});
    Bool _t_Bool_229 = not(_t_Bool_226);
    (void)_t_Bool_229;
    ;
    Bool _t_Bool_230 = not(_t_Bool_228);
    (void)_t_Bool_230;
    ;
    Bool _t_Bool_231 = and(_t_Bool_229, _t_Bool_230);
    (void)_t_Bool_231;
    ;
    ;
    if (_t_Bool_231) {
        {
            U32 _re_U32_204 = self->count;
            (void)_re_U32_204;
            U32 _rc_U32_204 = 0;
            (void)_rc_U32_204;
            Bool _t_Bool_213 = U32_lte(&_rc_U32_204, &_re_U32_204);
            (void)_t_Bool_213;
            if (_t_Bool_213) {
                while (1) {
                    Bool _wcond_Bool_205 = U32_lt(&_rc_U32_204, &_re_U32_204);
                    (void)_wcond_Bool_205;
                    if (_wcond_Bool_205) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_204);
                    (void)i;
                    U32_inc(&_rc_U32_204);
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
            } else {
                while (1) {
                    Bool _wcond_Bool_209 = U32_gt(&_rc_U32_204, &_re_U32_204);
                    (void)_wcond_Bool_209;
                    if (_wcond_Bool_209) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_204);
                    (void)i;
                    U32_dec(&_rc_U32_204);
                    U32 _t_U64_210 = U32_mul(i, self->elem_size);
                    (void)_t_U64_210;
                    ;
                    void *_t_v_211 = ptr_add(self->data, _t_U64_210);
                    (void)_t_v_211;
                    Bool _t_Bool_212 = 0;
                    (void)_t_Bool_212;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_211, &_t_Bool_212);
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
    Bool _t_Bool_232 = U32_gt(&needed, &self->cap);
    (void)_t_Bool_232;
    if (_t_Bool_232) {
        U32 new_cap = self->cap;
        (void)new_cap;
        while (1) {
            Bool _wcond_Bool_214 = U32_gt(&needed, &new_cap);
            (void)_wcond_Bool_214;
            if (_wcond_Bool_214) {
            } else {
                ;
                break;
            }
            ;
            U32 _t_U32_215 = 2;
            (void)_t_U32_215;
            U32 _t_U32_216 = U32_mul(new_cap, _t_U32_215);
            (void)_t_U32_216;
            ;
            new_cap = _t_U32_216;
            ;
        }
        U32 _t_U64_217 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_217;
        void * _t_v_218 = realloc(self->data, _t_U64_217);
        (void)_t_v_218;
        ;
        self->data = _t_v_218;
        U32 _t_U32_219 = U32_clone(&new_cap);
        (void)_t_U32_219;
        ;
        self->cap = _t_U32_219;
        ;
    }
    ;
    U32 _t_U32_233 = 0;
    (void)_t_U32_233;
    Bool _t_Bool_234 = U32_gt(&needed, &_t_U32_233);
    (void)_t_Bool_234;
    ;
    if (_t_Bool_234) {
        U32 _t_U64_220 = U32_mul(needed, self->elem_size);
        (void)_t_U64_220;
        memcpy(self->data, other->data, _t_U64_220);
        ;
    }
    ;
    U32 _t_U32_235 = U32_clone(&needed);
    (void)_t_U32_235;
    ;
    self->count = _t_U32_235;
    ;
    U32 _t_U32_236 = 0;
    (void)_t_U32_236;
    other->count = _t_U32_236;
    ;
}

void * Vec_get(Vec * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_251 = U32_gte(i, &self->count);
    (void)_t_Bool_251;
    if (_t_Bool_251) {
        Str *_t_Str_237 = Str_lit("Str", 3ULL);
        (void)_t_Str_237;
        Type *_t_Type_238 = Type_Struct(_t_Str_237);
        (void)_t_Type_238;
        Str_delete(_t_Str_237, &(Bool){1});
        U32 _t_U32_239 = 5;
        (void)_t_U32_239;
        Array *_va_Array_3 = Array_new(_t_Type_238, &_t_U32_239);
        (void)_va_Array_3;
        Type_delete(_t_Type_238, &(Bool){1});
        ;
        U32 _t_U32_240 = 0;
        (void)_t_U32_240;
        Str *_t_Str_241 = Str_lit("Vec.get: index ", 15ULL);
        (void)_t_Str_241;
        Array_set(_va_Array_3, &_t_U32_240, _t_Str_241);
        ;
        U32 _t_U32_242 = 1;
        (void)_t_U32_242;
        Str *_t_Str_243 = U32_to_str(i);
        (void)_t_Str_243;
        Array_set(_va_Array_3, &_t_U32_242, _t_Str_243);
        ;
        U32 _t_U32_244 = 2;
        (void)_t_U32_244;
        Str *_t_Str_245 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_245;
        Array_set(_va_Array_3, &_t_U32_244, _t_Str_245);
        ;
        U32 _t_U32_246 = 3;
        (void)_t_U32_246;
        Str *_t_Str_247 = U32_to_str(&self->count);
        (void)_t_Str_247;
        Array_set(_va_Array_3, &_t_U32_246, _t_Str_247);
        ;
        U32 _t_U32_248 = 4;
        (void)_t_U32_248;
        Str *_t_Str_249 = Str_lit(")", 1ULL);
        (void)_t_Str_249;
        Array_set(_va_Array_3, &_t_U32_248, _t_Str_249);
        ;
        Str *_t_Str_250 = Str_lit("./src/core/vec.til:116:19", 25ULL);
        (void)_t_Str_250;
        panic(_t_Str_250, _va_Array_3);
        Str_delete(_t_Str_250, &(Bool){1});
    }
    ;
    U32 _t_U64_252 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_252;
    void *_t_v_253 = ptr_add(self->data, _t_U64_252);
    (void)_t_v_253;
    ;
    return _t_v_253;
}

void * Vec_pop(Vec * self) {
    (void)self;
    U32 _t_U32_260 = 0;
    (void)_t_U32_260;
    Bool _t_Bool_261 = U32_eq(self->count, _t_U32_260);
    (void)_t_Bool_261;
    ;
    if (_t_Bool_261) {
        Str *_t_Str_254 = Str_lit("Str", 3ULL);
        (void)_t_Str_254;
        Type *_t_Type_255 = Type_Struct(_t_Str_254);
        (void)_t_Type_255;
        Str_delete(_t_Str_254, &(Bool){1});
        U32 _t_U32_256 = 1;
        (void)_t_U32_256;
        Array *_va_Array_4 = Array_new(_t_Type_255, &_t_U32_256);
        (void)_va_Array_4;
        Type_delete(_t_Type_255, &(Bool){1});
        ;
        U32 _t_U32_257 = 0;
        (void)_t_U32_257;
        Str *_t_Str_258 = Str_lit("Vec.pop: empty vec", 18ULL);
        (void)_t_Str_258;
        Array_set(_va_Array_4, &_t_U32_257, _t_Str_258);
        ;
        Str *_t_Str_259 = Str_lit("./src/core/vec.til:125:19", 25ULL);
        (void)_t_Str_259;
        panic(_t_Str_259, _va_Array_4);
        Str_delete(_t_Str_259, &(Bool){1});
    }
    ;
    U32 _t_U32_262 = 1;
    (void)_t_U32_262;
    U32 last = U32_sub(self->count, _t_U32_262);
    (void)last;
    ;
    void * out = malloc(self->elem_size);
    (void)out;
    U32 _t_U64_263 = U32_mul(last, self->elem_size);
    (void)_t_U64_263;
    void *_t_v_264 = ptr_add(self->data, _t_U64_263);
    (void)_t_v_264;
    memcpy(out, _t_v_264, self->elem_size);
    ;
    U32 _t_U32_265 = U32_clone(&last);
    (void)_t_U32_265;
    ;
    self->count = _t_U32_265;
    ;
    return out;
}

Vec * Vec_take_prefix(Vec * self, U32 * n) {
    (void)self;
    (void)n;
    Bool _t_Bool_285 = U32_gt(n, &self->count);
    (void)_t_Bool_285;
    if (_t_Bool_285) {
        Str *_t_Str_266 = Str_lit("Str", 3ULL);
        (void)_t_Str_266;
        Type *_t_Type_267 = Type_Struct(_t_Str_266);
        (void)_t_Type_267;
        Str_delete(_t_Str_266, &(Bool){1});
        U32 _t_U32_268 = 5;
        (void)_t_U32_268;
        Array *_va_Array_5 = Array_new(_t_Type_267, &_t_U32_268);
        (void)_va_Array_5;
        Type_delete(_t_Type_267, &(Bool){1});
        ;
        U32 _t_U32_269 = 0;
        (void)_t_U32_269;
        Str *_t_Str_270 = Str_lit("Vec.take_prefix: count ", 23ULL);
        (void)_t_Str_270;
        Array_set(_va_Array_5, &_t_U32_269, _t_Str_270);
        ;
        U32 _t_U32_271 = 1;
        (void)_t_U32_271;
        Str *_t_Str_272 = U32_to_str(n);
        (void)_t_Str_272;
        Array_set(_va_Array_5, &_t_U32_271, _t_Str_272);
        ;
        U32 _t_U32_273 = 2;
        (void)_t_U32_273;
        Str *_t_Str_274 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_274;
        Array_set(_va_Array_5, &_t_U32_273, _t_Str_274);
        ;
        U32 _t_U32_275 = 3;
        (void)_t_U32_275;
        Str *_t_Str_276 = U32_to_str(&self->count);
        (void)_t_Str_276;
        Array_set(_va_Array_5, &_t_U32_275, _t_Str_276);
        ;
        U32 _t_U32_277 = 4;
        (void)_t_U32_277;
        Str *_t_Str_278 = Str_lit(")", 1ULL);
        (void)_t_Str_278;
        Array_set(_va_Array_5, &_t_U32_277, _t_Str_278);
        ;
        Str *_t_Str_279 = Str_lit("./src/core/vec.til:138:19", 25ULL);
        (void)_t_Str_279;
        panic(_t_Str_279, _va_Array_5);
        Str_delete(_t_Str_279, &(Bool){1});
    }
    ;
    U32 prefix_cap = 1;
    (void)prefix_cap;
    U32 _t_U32_286 = 0;
    (void)_t_U32_286;
    Bool _t_Bool_287 = U32_gt(n, &_t_U32_286);
    (void)_t_Bool_287;
    ;
    if (_t_Bool_287) {
        U32 _t_U32_280 = U32_clone(n);
        (void)_t_U32_280;
        prefix_cap = _t_U32_280;
        ;
    }
    ;
    U32 _t_U64_288 = U32_mul(prefix_cap, self->elem_size);
    (void)_t_U64_288;
    void * prefix_data = malloc(_t_U64_288);
    (void)prefix_data;
    ;
    U32 _t_U32_289 = 0;
    (void)_t_U32_289;
    Bool _t_Bool_290 = U32_gt(n, &_t_U32_289);
    (void)_t_Bool_290;
    ;
    if (_t_Bool_290) {
        U32 _t_U64_281 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_281;
        memcpy(prefix_data, self->data, _t_U64_281);
        ;
    }
    ;
    U32 tail_count = U32_sub(self->count, DEREF(n));
    (void)tail_count;
    U32 _t_U32_291 = 0;
    (void)_t_U32_291;
    Bool _t_Bool_292 = U32_gt(&tail_count, &_t_U32_291);
    (void)_t_Bool_292;
    ;
    if (_t_Bool_292) {
        U32 _t_U64_282 = U32_mul(DEREF(n), self->elem_size);
        (void)_t_U64_282;
        void *_t_v_283 = ptr_add(self->data, _t_U64_282);
        (void)_t_v_283;
        U32 _t_U64_284 = U32_mul(tail_count, self->elem_size);
        (void)_t_U64_284;
        memmove(self->data, _t_v_283, _t_U64_284);
        ;
        ;
    }
    ;
    U32 _t_U32_293 = U32_clone(&tail_count);
    (void)_t_U32_293;
    ;
    self->count = _t_U32_293;
    ;
    Vec *_t_Vec_294 = malloc(sizeof(Vec));
    _t_Vec_294->data = prefix_data;
    _t_Vec_294->count = DEREF(n);
    _t_Vec_294->cap = prefix_cap;
    _t_Vec_294->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_294->elem_type = *_ca; free(_ca); }
    _t_Vec_294->elem_clone = (void *)self->elem_clone;
    _t_Vec_294->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_294;
    ;
    return _t_Vec_294;
}

void Vec_set(Vec * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_309 = U32_gte(i, &self->count);
    (void)_t_Bool_309;
    if (_t_Bool_309) {
        Str *_t_Str_295 = Str_lit("Str", 3ULL);
        (void)_t_Str_295;
        Type *_t_Type_296 = Type_Struct(_t_Str_295);
        (void)_t_Type_296;
        Str_delete(_t_Str_295, &(Bool){1});
        U32 _t_U32_297 = 5;
        (void)_t_U32_297;
        Array *_va_Array_6 = Array_new(_t_Type_296, &_t_U32_297);
        (void)_va_Array_6;
        Type_delete(_t_Type_296, &(Bool){1});
        ;
        U32 _t_U32_298 = 0;
        (void)_t_U32_298;
        Str *_t_Str_299 = Str_lit("Vec.set: index ", 15ULL);
        (void)_t_Str_299;
        Array_set(_va_Array_6, &_t_U32_298, _t_Str_299);
        ;
        U32 _t_U32_300 = 1;
        (void)_t_U32_300;
        Str *_t_Str_301 = U32_to_str(i);
        (void)_t_Str_301;
        Array_set(_va_Array_6, &_t_U32_300, _t_Str_301);
        ;
        U32 _t_U32_302 = 2;
        (void)_t_U32_302;
        Str *_t_Str_303 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_303;
        Array_set(_va_Array_6, &_t_U32_302, _t_Str_303);
        ;
        U32 _t_U32_304 = 3;
        (void)_t_U32_304;
        Str *_t_Str_305 = U32_to_str(&self->count);
        (void)_t_Str_305;
        Array_set(_va_Array_6, &_t_U32_304, _t_Str_305);
        ;
        U32 _t_U32_306 = 4;
        (void)_t_U32_306;
        Str *_t_Str_307 = Str_lit(")", 1ULL);
        (void)_t_Str_307;
        Array_set(_va_Array_6, &_t_U32_306, _t_Str_307);
        ;
        Str *_t_Str_308 = Str_lit("./src/core/vec.til:162:19", 25ULL);
        (void)_t_Str_308;
        panic(_t_Str_308, _va_Array_6);
        Str_delete(_t_Str_308, &(Bool){1});
    }
    ;
    U32 _t_U64_310 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_310;
    void *_t_v_311 = ptr_add(self->data, _t_U64_310);
    (void)_t_v_311;
    memcpy(_t_v_311, val, self->elem_size);
    ;
    free(val);
}

void Vec_push_take(Vec * self, Vec * src, U32 i) {
    (void)self;
    (void)src;
    (void)i;
    Bool _t_Bool_336 = U32_gte(&i, &src->count);
    (void)_t_Bool_336;
    if (_t_Bool_336) {
        Str *_t_Str_312 = Str_lit("Str", 3ULL);
        (void)_t_Str_312;
        Type *_t_Type_313 = Type_Struct(_t_Str_312);
        (void)_t_Type_313;
        Str_delete(_t_Str_312, &(Bool){1});
        U32 _t_U32_314 = 5;
        (void)_t_U32_314;
        Array *_va_Array_7 = Array_new(_t_Type_313, &_t_U32_314);
        (void)_va_Array_7;
        Type_delete(_t_Type_313, &(Bool){1});
        ;
        U32 _t_U32_315 = 0;
        (void)_t_U32_315;
        Str *_t_Str_316 = Str_lit("Vec.push_take: index ", 21ULL);
        (void)_t_Str_316;
        Array_set(_va_Array_7, &_t_U32_315, _t_Str_316);
        ;
        U32 _t_U32_317 = 1;
        (void)_t_U32_317;
        Str *_t_Str_318 = U32_to_str(&i);
        (void)_t_Str_318;
        Array_set(_va_Array_7, &_t_U32_317, _t_Str_318);
        ;
        U32 _t_U32_319 = 2;
        (void)_t_U32_319;
        Str *_t_Str_320 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_320;
        Array_set(_va_Array_7, &_t_U32_319, _t_Str_320);
        ;
        U32 _t_U32_321 = 3;
        (void)_t_U32_321;
        Str *_t_Str_322 = U32_to_str(&src->count);
        (void)_t_Str_322;
        Array_set(_va_Array_7, &_t_U32_321, _t_Str_322);
        ;
        U32 _t_U32_323 = 4;
        (void)_t_U32_323;
        Str *_t_Str_324 = Str_lit(")", 1ULL);
        (void)_t_Str_324;
        Array_set(_va_Array_7, &_t_U32_323, _t_Str_324);
        ;
        Str *_t_Str_325 = Str_lit("./src/core/vec.til:173:19", 25ULL);
        (void)_t_Str_325;
        panic(_t_Str_325, _va_Array_7);
        Str_delete(_t_Str_325, &(Bool){1});
    }
    ;
    Bool _t_Bool_337 = U32_eq(self->elem_size, src->elem_size);
    (void)_t_Bool_337;
    Bool _t_Bool_338 = Str_eq(&self->elem_type, &src->elem_type);
    (void)_t_Bool_338;
    Bool _t_Bool_339 = not(_t_Bool_337);
    (void)_t_Bool_339;
    ;
    Bool _t_Bool_340 = not(_t_Bool_338);
    (void)_t_Bool_340;
    ;
    Bool _t_Bool_341 = or(_t_Bool_339, _t_Bool_340);
    (void)_t_Bool_341;
    ;
    ;
    if (_t_Bool_341) {
        Str *_t_Str_326 = Str_lit("Str", 3ULL);
        (void)_t_Str_326;
        Type *_t_Type_327 = Type_Struct(_t_Str_326);
        (void)_t_Type_327;
        Str_delete(_t_Str_326, &(Bool){1});
        U32 _t_U32_328 = 1;
        (void)_t_U32_328;
        Array *_va_Array_8 = Array_new(_t_Type_327, &_t_U32_328);
        (void)_va_Array_8;
        Type_delete(_t_Type_327, &(Bool){1});
        ;
        U32 _t_U32_329 = 0;
        (void)_t_U32_329;
        Str *_t_Str_330 = Str_lit("Vec.push_take: incompatible vecs", 32ULL);
        (void)_t_Str_330;
        Array_set(_va_Array_8, &_t_U32_329, _t_Str_330);
        ;
        Str *_t_Str_331 = Str_lit("./src/core/vec.til:176:19", 25ULL);
        (void)_t_Str_331;
        panic(_t_Str_331, _va_Array_8);
        Str_delete(_t_Str_331, &(Bool){1});
    }
    ;
    Bool _t_Bool_342 = U32_eq(self->count, self->cap);
    (void)_t_Bool_342;
    if (_t_Bool_342) {
        U32 _t_U32_332 = 2;
        (void)_t_U32_332;
        U32 new_cap = U32_mul(self->cap, _t_U32_332);
        (void)new_cap;
        ;
        U32 _t_U64_333 = U32_mul(new_cap, self->elem_size);
        (void)_t_U64_333;
        void * _t_v_334 = realloc(self->data, _t_U64_333);
        (void)_t_v_334;
        ;
        self->data = _t_v_334;
        U32 _t_U32_335 = U32_clone(&new_cap);
        (void)_t_U32_335;
        ;
        self->cap = _t_U32_335;
        ;
    }
    ;
    U32 _t_U64_343 = U32_mul(self->count, self->elem_size);
    (void)_t_U64_343;
    U32 _t_U64_344 = U32_mul(i, src->elem_size);
    (void)_t_U64_344;
    void *_t_v_345 = ptr_add(self->data, _t_U64_343);
    (void)_t_v_345;
    void *_t_v_346 = ptr_add(src->data, _t_U64_344);
    (void)_t_v_346;
    memcpy(_t_v_345, _t_v_346, self->elem_size);
    ;
    ;
    U32 _t_U64_347 = U32_mul(i, src->elem_size);
    (void)_t_U64_347;
    void *_t_v_348 = ptr_add(src->data, _t_U64_347);
    (void)_t_v_348;
    I32 _t_I32_349 = 0;
    (void)_t_I32_349;
    memset(_t_v_348, _t_I32_349, src->elem_size);
    ;
    ;
    U32 _t_U32_350 = 1;
    (void)_t_U32_350;
    U32 _t_U32_351 = U32_add(self->count, _t_U32_350);
    (void)_t_U32_351;
    ;
    self->count = _t_U32_351;
    ;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_363 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_363;
    Str *_t_Str_364 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_364;
    Bool _t_Bool_365 = Str_eq(&self->elem_type, _t_Str_364);
    (void)_t_Bool_365;
    Str_delete(_t_Str_364, &(Bool){1});
    Bool _t_Bool_366 = not(_t_Bool_363);
    (void)_t_Bool_366;
    ;
    Bool _t_Bool_367 = not(_t_Bool_365);
    (void)_t_Bool_367;
    ;
    Bool _t_Bool_368 = and(_t_Bool_366, _t_Bool_367);
    (void)_t_Bool_368;
    ;
    ;
    if (_t_Bool_368) {
        {
            U32 _re_U32_352 = self->count;
            (void)_re_U32_352;
            U32 _rc_U32_352 = 0;
            (void)_rc_U32_352;
            Bool _t_Bool_361 = U32_lte(&_rc_U32_352, &_re_U32_352);
            (void)_t_Bool_361;
            if (_t_Bool_361) {
                while (1) {
                    Bool _wcond_Bool_353 = U32_lt(&_rc_U32_352, &_re_U32_352);
                    (void)_wcond_Bool_353;
                    if (_wcond_Bool_353) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_352);
                    (void)i;
                    U32_inc(&_rc_U32_352);
                    U32 _t_U64_354 = U32_mul(i, self->elem_size);
                    (void)_t_U64_354;
                    ;
                    void *_t_v_355 = ptr_add(self->data, _t_U64_354);
                    (void)_t_v_355;
                    Bool _t_Bool_356 = 0;
                    (void)_t_Bool_356;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_355, &_t_Bool_356);
                    ;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_357 = U32_gt(&_rc_U32_352, &_re_U32_352);
                    (void)_wcond_Bool_357;
                    if (_wcond_Bool_357) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_352);
                    (void)i;
                    U32_dec(&_rc_U32_352);
                    U32 _t_U64_358 = U32_mul(i, self->elem_size);
                    (void)_t_U64_358;
                    ;
                    void *_t_v_359 = ptr_add(self->data, _t_U64_358);
                    (void)_t_v_359;
                    Bool _t_Bool_360 = 0;
                    (void)_t_Bool_360;
                    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_359, &_t_Bool_360);
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
    Bool _t_Bool_369 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_369;
    Bool _t_Bool_370 = not(_t_Bool_369);
    (void)_t_Bool_370;
    ;
    if (_t_Bool_370) {
        Bool _t_Bool_362 = 0;
        (void)_t_Bool_362;
        Str_delete(&self->elem_type, &_t_Bool_362);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U32 _t_U64_384 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_384;
    void * new_data = malloc(_t_U64_384);
    (void)new_data;
    ;
    Bool _t_Bool_385 = Str_is_empty(&self->elem_type);
    (void)_t_Bool_385;
    Str *_t_Str_386 = Str_lit("Dynamic", 7ULL);
    (void)_t_Str_386;
    Bool _t_Bool_387 = Str_eq(&self->elem_type, _t_Str_386);
    (void)_t_Bool_387;
    Str_delete(_t_Str_386, &(Bool){1});
    Bool _t_Bool_388 = not(_t_Bool_385);
    (void)_t_Bool_388;
    ;
    Bool _t_Bool_389 = not(_t_Bool_387);
    (void)_t_Bool_389;
    ;
    Bool _t_Bool_390 = and(_t_Bool_388, _t_Bool_389);
    (void)_t_Bool_390;
    ;
    ;
    if (_t_Bool_390) {
        {
            U32 _re_U32_371 = self->count;
            (void)_re_U32_371;
            U32 _rc_U32_371 = 0;
            (void)_rc_U32_371;
            Bool _t_Bool_382 = U32_lte(&_rc_U32_371, &_re_U32_371);
            (void)_t_Bool_382;
            if (_t_Bool_382) {
                while (1) {
                    Bool _wcond_Bool_372 = U32_lt(&_rc_U32_371, &_re_U32_371);
                    (void)_wcond_Bool_372;
                    if (_wcond_Bool_372) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_371);
                    (void)i;
                    U32_inc(&_rc_U32_371);
                    U32 _t_U64_373 = U32_mul(i, self->elem_size);
                    (void)_t_U64_373;
                    void *_t_v_374 = ptr_add(self->data, _t_U64_373);
                    (void)_t_v_374;
                    void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_374);
                    (void)cloned;
                    ;
                    U32 _t_U64_375 = U32_mul(i, self->elem_size);
                    (void)_t_U64_375;
                    ;
                    void *_t_v_376 = ptr_add(new_data, _t_U64_375);
                    (void)_t_v_376;
                    memcpy(_t_v_376, cloned, self->elem_size);
                    ;
                    free(cloned);
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_377 = U32_gt(&_rc_U32_371, &_re_U32_371);
                    (void)_wcond_Bool_377;
                    if (_wcond_Bool_377) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 i = U32_clone(&_rc_U32_371);
                    (void)i;
                    U32_dec(&_rc_U32_371);
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
            }
            ;
            ;
            ;
        }
    } else {
        U32 _t_U64_383 = U32_mul(self->count, self->elem_size);
        (void)_t_U64_383;
        memcpy(new_data, self->data, _t_U64_383);
        ;
    }
    ;
    Vec *_t_Vec_391 = malloc(sizeof(Vec));
    _t_Vec_391->data = new_data;
    _t_Vec_391->count = self->count;
    _t_Vec_391->cap = self->cap;
    _t_Vec_391->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Vec_391->elem_type = *_ca; free(_ca); }
    _t_Vec_391->elem_clone = (void *)self->elem_clone;
    _t_Vec_391->elem_delete = (void *)self->elem_delete;
    (void)_t_Vec_391;
    return _t_Vec_391;
}

U32 Vec_size(void) {
    I64 _t_I64_392 = 56;
    (void)_t_I64_392;
    return _t_I64_392;
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    (void)total;
    {
        Array *_fc_Array_393 = parts;
        (void)_fc_Array_393;
        U32 _fi_USize_393 = 0;
        (void)_fi_USize_393;
        while (1) {
            U32 _t_U32_395; { U32 *_hp = (U32 *)Array_len(_fc_Array_393); _t_U32_395 = *_hp; free(_hp); }
            (void)_t_U32_395;
            Bool _wcond_Bool_394 = U32_lt(&_fi_USize_393, &_t_U32_395);
            (void)_wcond_Bool_394;
            ;
            if (_wcond_Bool_394) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_393, &_fi_USize_393);
            (void)s;
            U32 _t_U32_396 = 1;
            (void)_t_U32_396;
            U32 _t_U32_397 = U32_add(_fi_USize_393, _t_U32_396);
            (void)_t_U32_397;
            ;
            _fi_USize_393 = _t_U32_397;
            ;
            U32 _t_U32_398 = Str_len(s);
            (void)_t_U32_398;
            U32 _t_U32_399 = U32_add(total, _t_U32_398);
            (void)_t_U32_399;
            ;
            total = _t_U32_399;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    (void)out;
    ;
    {
        Array *_fc_Array_400 = parts;
        (void)_fc_Array_400;
        U32 _fi_USize_400 = 0;
        (void)_fi_USize_400;
        while (1) {
            U32 _t_U32_402; { U32 *_hp = (U32 *)Array_len(_fc_Array_400); _t_U32_402 = *_hp; free(_hp); }
            (void)_t_U32_402;
            Bool _wcond_Bool_401 = U32_lt(&_fi_USize_400, &_t_U32_402);
            (void)_wcond_Bool_401;
            ;
            if (_wcond_Bool_401) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_400, &_fi_USize_400);
            (void)s;
            U32 _t_U32_403 = 1;
            (void)_t_U32_403;
            U32 _t_U32_404 = U32_add(_fi_USize_400, _t_U32_403);
            (void)_t_U32_404;
            ;
            _fi_USize_400 = _t_U32_404;
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
    Bool _t_Bool_411 = U32_gte(i, &self->count);
    (void)_t_Bool_411;
    if (_t_Bool_411) {
        Str *_t_Str_405 = Str_lit("Str", 3ULL);
        (void)_t_Str_405;
        Type *_t_Type_406 = Type_Struct(_t_Str_405);
        (void)_t_Type_406;
        Str_delete(_t_Str_405, &(Bool){1});
        U32 _t_U32_407 = 1;
        (void)_t_U32_407;
        Array *_va_Array_9 = Array_new(_t_Type_406, &_t_U32_407);
        (void)_va_Array_9;
        Type_delete(_t_Type_406, &(Bool){1});
        ;
        U32 _t_U32_408 = 0;
        (void)_t_U32_408;
        Str *_t_Str_409 = Str_lit("Str.get: index out of bounds", 28ULL);
        (void)_t_Str_409;
        Array_set(_va_Array_9, &_t_U32_408, _t_Str_409);
        ;
        Str *_t_Str_410 = Str_lit("./src/core/str.til:39:19", 24ULL);
        (void)_t_Str_410;
        panic(_t_Str_410, _va_Array_9);
        Str_delete(_t_Str_410, &(Bool){1});
    }
    ;
    void *_t_v_412 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_412;
    return _t_v_412;
}

U8 * Str_byte_at(Str * self, U32 * i) {
    (void)self;
    (void)i;
    void *_t_v_413 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_413;
    return _t_v_413;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    (void)min_len;
    Bool _t_Bool_422 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_422;
    if (_t_Bool_422) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_414 = U32_clone(&min_len);
        (void)_re_U32_414;
        U32 _rc_U32_414 = 0;
        (void)_rc_U32_414;
        Bool _t_Bool_421 = U32_lte(&_rc_U32_414, &_re_U32_414);
        (void)_t_Bool_421;
        if (_t_Bool_421) {
            while (1) {
                Bool _wcond_Bool_415 = U32_lt(&_rc_U32_414, &_re_U32_414);
                (void)_wcond_Bool_415;
                if (_wcond_Bool_415) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_414);
                (void)i;
                U32_inc(&_rc_U32_414);
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
        } else {
            while (1) {
                Bool _wcond_Bool_418 = U32_gt(&_rc_U32_414, &_re_U32_414);
                (void)_wcond_Bool_418;
                if (_wcond_Bool_418) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_414);
                (void)i;
                U32_dec(&_rc_U32_414);
                U8 *ab = Str_get(a, &i);
                (void)ab;
                U8 *bb = Str_get(b, &i);
                (void)bb;
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                (void)c;
                ;
                I64 _t_I64_419 = 0;
                (void)_t_I64_419;
                Bool _t_Bool_420 = I64_neq(&c, &_t_I64_419);
                (void)_t_Bool_420;
                ;
                if (_t_Bool_420) {
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
    I64 _t_I64_423 = U32_cmp(a->count, b->count);
    (void)_t_I64_423;
    return _t_I64_423;
}

Str * Str_concat(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_424 = U32_add(a->count, b->count);
    (void)_t_U32_424;
    Str *out = Str_with_capacity(&_t_U32_424);
    (void)out;
    ;
    Str_push_str(out, a);
    Str_push_str(out, b);
    return out;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_425 = 1;
    (void)_t_U32_425;
    U32 _t_U64_426 = U32_add(DEREF(n), _t_U32_425);
    (void)_t_U64_426;
    ;
    void * buf = malloc(_t_U64_426);
    (void)buf;
    ;
    I32 _t_I32_427 = 0;
    (void)_t_I32_427;
    U64 _t_U64_428 = 1;
    (void)_t_U64_428;
    memset(buf, _t_I32_427, _t_U64_428);
    ;
    ;
    I64 _t_I64_429 = 0;
    (void)_t_I64_429;
    Str *_t_Str_430 = malloc(sizeof(Str));
    _t_Str_430->c_str = buf;
    _t_Str_430->count = _t_I64_429;
    _t_Str_430->cap = DEREF(n);
    (void)_t_Str_430;
    ;
    return _t_Str_430;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_443 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_443;
    if (_t_Bool_443) {
        Str *_t_Str_431 = Str_lit("Str", 3ULL);
        (void)_t_Str_431;
        Type *_t_Type_432 = Type_Struct(_t_Str_431);
        (void)_t_Type_432;
        Str_delete(_t_Str_431, &(Bool){1});
        U32 _t_U32_433 = 1;
        (void)_t_U32_433;
        Array *_va_Array_10 = Array_new(_t_Type_432, &_t_U32_433);
        (void)_va_Array_10;
        Type_delete(_t_Type_432, &(Bool){1});
        ;
        U32 _t_U32_434 = 0;
        (void)_t_U32_434;
        Str *_t_Str_435 = Str_lit("Str.push_str: cannot mutate a string view or literal", 52ULL);
        (void)_t_Str_435;
        Array_set(_va_Array_10, &_t_U32_434, _t_Str_435);
        ;
        Str *_t_Str_436 = Str_lit("./src/core/str.til:82:19", 24ULL);
        (void)_t_Str_436;
        panic(_t_Str_436, _va_Array_10);
        Str_delete(_t_Str_436, &(Bool){1});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    (void)new_len;
    Bool _t_Bool_444 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_444;
    if (_t_Bool_444) {
        Str *_t_Str_437 = Str_lit("Str", 3ULL);
        (void)_t_Str_437;
        Type *_t_Type_438 = Type_Struct(_t_Str_437);
        (void)_t_Type_438;
        Str_delete(_t_Str_437, &(Bool){1});
        U32 _t_U32_439 = 1;
        (void)_t_U32_439;
        Array *_va_Array_11 = Array_new(_t_Type_438, &_t_U32_439);
        (void)_va_Array_11;
        Type_delete(_t_Type_438, &(Bool){1});
        ;
        U32 _t_U32_440 = 0;
        (void)_t_U32_440;
        Str *_t_Str_441 = Str_lit("Str.push_str: capacity exceeded", 31ULL);
        (void)_t_Str_441;
        Array_set(_va_Array_11, &_t_U32_440, _t_Str_441);
        ;
        Str *_t_Str_442 = Str_lit("./src/core/str.til:86:19", 24ULL);
        (void)_t_Str_442;
        panic(_t_Str_442, _va_Array_11);
        Str_delete(_t_Str_442, &(Bool){1});
    }
    ;
    void *_t_v_445 = ptr_add(self->c_str, self->count);
    (void)_t_v_445;
    memcpy(_t_v_445, s->c_str, s->count);
    U32 _t_U32_446 = U32_clone(&new_len);
    (void)_t_U32_446;
    self->count = _t_U32_446;
    ;
    void *_t_v_447 = ptr_add(self->c_str, new_len);
    (void)_t_v_447;
    I32 _t_I32_448 = 0;
    (void)_t_I32_448;
    U64 _t_U64_449 = 1;
    (void)_t_U64_449;
    memset(_t_v_447, _t_I32_448, _t_U64_449);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_450 = 1;
    (void)_t_U32_450;
    U32 _t_U64_451 = U32_add(val->count, _t_U32_450);
    (void)_t_U64_451;
    ;
    void * new_data = malloc(_t_U64_451);
    (void)new_data;
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_452 = ptr_add(new_data, val->count);
    (void)_t_v_452;
    I32 _t_I32_453 = 0;
    (void)_t_I32_453;
    U64 _t_U64_454 = 1;
    (void)_t_U64_454;
    memset(_t_v_452, _t_I32_453, _t_U64_454);
    ;
    ;
    Str *_t_Str_455 = malloc(sizeof(Str));
    _t_Str_455->c_str = new_data;
    _t_Str_455->count = val->count;
    _t_Str_455->cap = val->count;
    (void)_t_Str_455;
    return _t_Str_455;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_456 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_456;
    if (_t_Bool_456) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    (void)val;
    Str *_t_Str_457 = Str_clone(val);
    (void)_t_Str_457;
    return _t_Str_457;
}

Str * Str_substr(Str * s, U32 * start, U32 * n) {
    (void)s;
    (void)start;
    (void)n;
    U32 st = U32_clone(start);
    (void)st;
    U32 ln = U32_clone(n);
    (void)ln;
    Bool _t_Bool_459 = U32_gt(&st, &s->count);
    (void)_t_Bool_459;
    if (_t_Bool_459) {
        st = s->count;
    }
    ;
    U32 _t_U32_460 = U32_add(st, ln);
    (void)_t_U32_460;
    Bool _t_Bool_461 = U32_gt(&_t_U32_460, &s->count);
    (void)_t_Bool_461;
    ;
    if (_t_Bool_461) {
        U32 _t_U32_458 = U32_sub(s->count, st);
        (void)_t_U32_458;
        ln = _t_U32_458;
        ;
    }
    ;
    void *_t_v_462 = ptr_add(s->c_str, st);
    (void)_t_v_462;
    Str *_t_Str_463 = malloc(sizeof(Str));
    _t_Str_463->c_str = _t_v_462;
    _t_Str_463->count = ln;
    _t_Str_463->cap = CAP_VIEW;
    (void)_t_Str_463;
    ;
    ;
    return _t_Str_463;
}

Bool Str_contains(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 _t_U32_494 = 0;
    (void)_t_U32_494;
    Bool _t_Bool_495 = U32_eq(b->count, _t_U32_494);
    (void)_t_Bool_495;
    ;
    if (_t_Bool_495) {
        Bool _t_Bool_464 = 1;
        (void)_t_Bool_464;
        ;
        return _t_Bool_464;
    }
    ;
    Bool _t_Bool_496 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_496;
    if (_t_Bool_496) {
        Bool _t_Bool_465 = 0;
        (void)_t_Bool_465;
        ;
        return _t_Bool_465;
    }
    ;
    {
        U32 _t_U32_491 = U32_sub(a->count, b->count);
        (void)_t_U32_491;
        U32 _t_U32_492 = 1;
        (void)_t_U32_492;
        U32 _re_U32_466 = U32_add(_t_U32_491, _t_U32_492);
        (void)_re_U32_466;
        ;
        ;
        U32 _rc_U32_466 = 0;
        (void)_rc_U32_466;
        Bool _t_Bool_493 = U32_lte(&_rc_U32_466, &_re_U32_466);
        (void)_t_Bool_493;
        if (_t_Bool_493) {
            while (1) {
                Bool _wcond_Bool_467 = U32_lt(&_rc_U32_466, &_re_U32_466);
                (void)_wcond_Bool_467;
                if (_wcond_Bool_467) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_466);
                (void)i;
                U32_inc(&_rc_U32_466);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_468 = b->count;
                    (void)_re_U32_468;
                    U32 _rc_U32_468 = 0;
                    (void)_rc_U32_468;
                    Bool _t_Bool_477 = U32_lte(&_rc_U32_468, &_re_U32_468);
                    (void)_t_Bool_477;
                    if (_t_Bool_477) {
                        while (1) {
                            Bool _wcond_Bool_469 = U32_lt(&_rc_U32_468, &_re_U32_468);
                            (void)_wcond_Bool_469;
                            if (_wcond_Bool_469) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_468);
                            (void)j;
                            U32_inc(&_rc_U32_468);
                            U32 _t_U32_471 = U32_add(i, j);
                            (void)_t_U32_471;
                            U8 *ac = Str_get(a, &_t_U32_471);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_472 = U8_neq(ac, bc);
                            (void)_t_Bool_472;
                            ;
                            ;
                            if (_t_Bool_472) {
                                Bool _t_Bool_470 = 0;
                                (void)_t_Bool_470;
                                found = _t_Bool_470;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_473 = U32_gt(&_rc_U32_468, &_re_U32_468);
                            (void)_wcond_Bool_473;
                            if (_wcond_Bool_473) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_468);
                            (void)j;
                            U32_dec(&_rc_U32_468);
                            U32 _t_U32_475 = U32_add(i, j);
                            (void)_t_U32_475;
                            U8 *ac = Str_get(a, &_t_U32_475);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_476 = U8_neq(ac, bc);
                            (void)_t_Bool_476;
                            ;
                            ;
                            if (_t_Bool_476) {
                                Bool _t_Bool_474 = 0;
                                (void)_t_Bool_474;
                                found = _t_Bool_474;
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
                    Bool _t_Bool_478 = 1;
                    (void)_t_Bool_478;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_478;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_479 = U32_gt(&_rc_U32_466, &_re_U32_466);
                (void)_wcond_Bool_479;
                if (_wcond_Bool_479) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_466);
                (void)i;
                U32_dec(&_rc_U32_466);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_480 = b->count;
                    (void)_re_U32_480;
                    U32 _rc_U32_480 = 0;
                    (void)_rc_U32_480;
                    Bool _t_Bool_489 = U32_lte(&_rc_U32_480, &_re_U32_480);
                    (void)_t_Bool_489;
                    if (_t_Bool_489) {
                        while (1) {
                            Bool _wcond_Bool_481 = U32_lt(&_rc_U32_480, &_re_U32_480);
                            (void)_wcond_Bool_481;
                            if (_wcond_Bool_481) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_480);
                            (void)j;
                            U32_inc(&_rc_U32_480);
                            U32 _t_U32_483 = U32_add(i, j);
                            (void)_t_U32_483;
                            U8 *ac = Str_get(a, &_t_U32_483);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_484 = U8_neq(ac, bc);
                            (void)_t_Bool_484;
                            ;
                            ;
                            if (_t_Bool_484) {
                                Bool _t_Bool_482 = 0;
                                (void)_t_Bool_482;
                                found = _t_Bool_482;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_485 = U32_gt(&_rc_U32_480, &_re_U32_480);
                            (void)_wcond_Bool_485;
                            if (_wcond_Bool_485) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_480);
                            (void)j;
                            U32_dec(&_rc_U32_480);
                            U32 _t_U32_487 = U32_add(i, j);
                            (void)_t_U32_487;
                            U8 *ac = Str_get(a, &_t_U32_487);
                            (void)ac;
                            U8 *bc = Str_get(b, &j);
                            (void)bc;
                            Bool _t_Bool_488 = U8_neq(ac, bc);
                            (void)_t_Bool_488;
                            ;
                            ;
                            if (_t_Bool_488) {
                                Bool _t_Bool_486 = 0;
                                (void)_t_Bool_486;
                                found = _t_Bool_486;
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
                    Bool _t_Bool_490 = 1;
                    (void)_t_Bool_490;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_490;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_497 = 0;
    (void)_t_Bool_497;
    return _t_Bool_497;
}

Bool Str_starts_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_507 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_507;
    if (_t_Bool_507) {
        Bool _t_Bool_498 = 0;
        (void)_t_Bool_498;
        ;
        return _t_Bool_498;
    }
    ;
    {
        U32 _re_U32_499 = b->count;
        (void)_re_U32_499;
        U32 _rc_U32_499 = 0;
        (void)_rc_U32_499;
        Bool _t_Bool_506 = U32_lte(&_rc_U32_499, &_re_U32_499);
        (void)_t_Bool_506;
        if (_t_Bool_506) {
            while (1) {
                Bool _wcond_Bool_500 = U32_lt(&_rc_U32_499, &_re_U32_499);
                (void)_wcond_Bool_500;
                if (_wcond_Bool_500) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_499);
                (void)i;
                U32_inc(&_rc_U32_499);
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
        } else {
            while (1) {
                Bool _wcond_Bool_503 = U32_gt(&_rc_U32_499, &_re_U32_499);
                (void)_wcond_Bool_503;
                if (_wcond_Bool_503) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_499);
                (void)i;
                U32_dec(&_rc_U32_499);
                U8 *ac = Str_get(a, &i);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_505 = U8_neq(ac, bc);
                (void)_t_Bool_505;
                ;
                if (_t_Bool_505) {
                    Bool _t_Bool_504 = 0;
                    (void)_t_Bool_504;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_504;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    Bool _t_Bool_508 = 1;
    (void)_t_Bool_508;
    return _t_Bool_508;
}

Bool Str_ends_with(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_520 = U32_gt(&b->count, &a->count);
    (void)_t_Bool_520;
    if (_t_Bool_520) {
        Bool _t_Bool_509 = 0;
        (void)_t_Bool_509;
        ;
        return _t_Bool_509;
    }
    ;
    U32 offset = U32_sub(a->count, b->count);
    (void)offset;
    {
        U32 _re_U32_510 = b->count;
        (void)_re_U32_510;
        U32 _rc_U32_510 = 0;
        (void)_rc_U32_510;
        Bool _t_Bool_519 = U32_lte(&_rc_U32_510, &_re_U32_510);
        (void)_t_Bool_519;
        if (_t_Bool_519) {
            while (1) {
                Bool _wcond_Bool_511 = U32_lt(&_rc_U32_510, &_re_U32_510);
                (void)_wcond_Bool_511;
                if (_wcond_Bool_511) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_510);
                (void)i;
                U32_inc(&_rc_U32_510);
                U32 _t_U32_513 = U32_add(offset, i);
                (void)_t_U32_513;
                U8 *ac = Str_get(a, &_t_U32_513);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_514 = U8_neq(ac, bc);
                (void)_t_Bool_514;
                ;
                ;
                if (_t_Bool_514) {
                    Bool _t_Bool_512 = 0;
                    (void)_t_Bool_512;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_512;
                }
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_515 = U32_gt(&_rc_U32_510, &_re_U32_510);
                (void)_wcond_Bool_515;
                if (_wcond_Bool_515) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_510);
                (void)i;
                U32_dec(&_rc_U32_510);
                U32 _t_U32_517 = U32_add(offset, i);
                (void)_t_U32_517;
                U8 *ac = Str_get(a, &_t_U32_517);
                (void)ac;
                U8 *bc = Str_get(b, &i);
                (void)bc;
                Bool _t_Bool_518 = U8_neq(ac, bc);
                (void)_t_Bool_518;
                ;
                ;
                if (_t_Bool_518) {
                    Bool _t_Bool_516 = 0;
                    (void)_t_Bool_516;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_Bool_516;
                }
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    Bool _t_Bool_521 = 1;
    (void)_t_Bool_521;
    return _t_Bool_521;
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_522 = 0;
    (void)_t_U32_522;
    Bool _t_Bool_523 = U32_eq(self->count, _t_U32_522);
    (void)_t_Bool_523;
    ;
    return _t_Bool_523;
}

I64 Str_find(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_558 = 0;
    (void)_t_U32_558;
    Bool _t_Bool_559 = U32_eq(needle->count, _t_U32_558);
    (void)_t_Bool_559;
    ;
    if (_t_Bool_559) {
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
    Bool _t_Bool_560 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_560;
    if (_t_Bool_560) {
        I64 _t_I64_527 = 0;
        (void)_t_I64_527;
        I64 _t_I64_528 = 1;
        (void)_t_I64_528;
        I64 _t_I64_529 = I64_sub(_t_I64_527, _t_I64_528);
        (void)_t_I64_529;
        ;
        ;
        ;
        return _t_I64_529;
    }
    ;
    {
        U32 _t_U32_555 = U32_sub(self->count, needle->count);
        (void)_t_U32_555;
        U32 _t_U32_556 = 1;
        (void)_t_U32_556;
        U32 _re_U32_530 = U32_add(_t_U32_555, _t_U32_556);
        (void)_re_U32_530;
        ;
        ;
        U32 _rc_U32_530 = 0;
        (void)_rc_U32_530;
        Bool _t_Bool_557 = U32_lte(&_rc_U32_530, &_re_U32_530);
        (void)_t_Bool_557;
        if (_t_Bool_557) {
            while (1) {
                Bool _wcond_Bool_531 = U32_lt(&_rc_U32_530, &_re_U32_530);
                (void)_wcond_Bool_531;
                if (_wcond_Bool_531) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_530);
                (void)i;
                U32_inc(&_rc_U32_530);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_532 = needle->count;
                    (void)_re_U32_532;
                    U32 _rc_U32_532 = 0;
                    (void)_rc_U32_532;
                    Bool _t_Bool_541 = U32_lte(&_rc_U32_532, &_re_U32_532);
                    (void)_t_Bool_541;
                    if (_t_Bool_541) {
                        while (1) {
                            Bool _wcond_Bool_533 = U32_lt(&_rc_U32_532, &_re_U32_532);
                            (void)_wcond_Bool_533;
                            if (_wcond_Bool_533) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_532);
                            (void)j;
                            U32_inc(&_rc_U32_532);
                            U32 _t_U32_535 = U32_add(i, j);
                            (void)_t_U32_535;
                            U8 *ac = Str_get(self, &_t_U32_535);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_536 = U8_neq(ac, bc);
                            (void)_t_Bool_536;
                            ;
                            ;
                            if (_t_Bool_536) {
                                Bool _t_Bool_534 = 0;
                                (void)_t_Bool_534;
                                found = _t_Bool_534;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_537 = U32_gt(&_rc_U32_532, &_re_U32_532);
                            (void)_wcond_Bool_537;
                            if (_wcond_Bool_537) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_532);
                            (void)j;
                            U32_dec(&_rc_U32_532);
                            U32 _t_U32_539 = U32_add(i, j);
                            (void)_t_U32_539;
                            U8 *ac = Str_get(self, &_t_U32_539);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_540 = U8_neq(ac, bc);
                            (void)_t_Bool_540;
                            ;
                            ;
                            if (_t_Bool_540) {
                                Bool _t_Bool_538 = 0;
                                (void)_t_Bool_538;
                                found = _t_Bool_538;
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
                    I64 _t_I64_542 = U32_to_i64(i);
                    (void)_t_I64_542;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_542;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_543 = U32_gt(&_rc_U32_530, &_re_U32_530);
                (void)_wcond_Bool_543;
                if (_wcond_Bool_543) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_530);
                (void)i;
                U32_dec(&_rc_U32_530);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_544 = needle->count;
                    (void)_re_U32_544;
                    U32 _rc_U32_544 = 0;
                    (void)_rc_U32_544;
                    Bool _t_Bool_553 = U32_lte(&_rc_U32_544, &_re_U32_544);
                    (void)_t_Bool_553;
                    if (_t_Bool_553) {
                        while (1) {
                            Bool _wcond_Bool_545 = U32_lt(&_rc_U32_544, &_re_U32_544);
                            (void)_wcond_Bool_545;
                            if (_wcond_Bool_545) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_544);
                            (void)j;
                            U32_inc(&_rc_U32_544);
                            U32 _t_U32_547 = U32_add(i, j);
                            (void)_t_U32_547;
                            U8 *ac = Str_get(self, &_t_U32_547);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_548 = U8_neq(ac, bc);
                            (void)_t_Bool_548;
                            ;
                            ;
                            if (_t_Bool_548) {
                                Bool _t_Bool_546 = 0;
                                (void)_t_Bool_546;
                                found = _t_Bool_546;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_549 = U32_gt(&_rc_U32_544, &_re_U32_544);
                            (void)_wcond_Bool_549;
                            if (_wcond_Bool_549) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_544);
                            (void)j;
                            U32_dec(&_rc_U32_544);
                            U32 _t_U32_551 = U32_add(i, j);
                            (void)_t_U32_551;
                            U8 *ac = Str_get(self, &_t_U32_551);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_552 = U8_neq(ac, bc);
                            (void)_t_Bool_552;
                            ;
                            ;
                            if (_t_Bool_552) {
                                Bool _t_Bool_550 = 0;
                                (void)_t_Bool_550;
                                found = _t_Bool_550;
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
                    I64 _t_I64_554 = U32_to_i64(i);
                    (void)_t_I64_554;
                    ;
                    ;
                    ;
                    ;
                    ;
                    return _t_I64_554;
                }
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    I64 _t_I64_561 = 0;
    (void)_t_I64_561;
    I64 _t_I64_562 = 1;
    (void)_t_I64_562;
    I64 _t_I64_563 = I64_sub(_t_I64_561, _t_I64_562);
    (void)_t_I64_563;
    ;
    ;
    return _t_I64_563;
}

I64 Str_rfind(Str * self, Str * needle) {
    (void)self;
    (void)needle;
    U32 _t_U32_598 = 0;
    (void)_t_U32_598;
    Bool _t_Bool_599 = U32_eq(needle->count, _t_U32_598);
    (void)_t_Bool_599;
    ;
    if (_t_Bool_599) {
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
    Bool _t_Bool_600 = U32_gt(&needle->count, &self->count);
    (void)_t_Bool_600;
    if (_t_Bool_600) {
        I64 _t_I64_567 = 0;
        (void)_t_I64_567;
        I64 _t_I64_568 = 1;
        (void)_t_I64_568;
        I64 _t_I64_569 = I64_sub(_t_I64_567, _t_I64_568);
        (void)_t_I64_569;
        ;
        ;
        ;
        return _t_I64_569;
    }
    ;
    I64 _t_I64_601 = 0;
    (void)_t_I64_601;
    I64 _t_I64_602 = 1;
    (void)_t_I64_602;
    I64 last = I64_sub(_t_I64_601, _t_I64_602);
    (void)last;
    ;
    ;
    {
        U32 _t_U32_595 = U32_sub(self->count, needle->count);
        (void)_t_U32_595;
        U32 _t_U32_596 = 1;
        (void)_t_U32_596;
        U32 _re_U32_570 = U32_add(_t_U32_595, _t_U32_596);
        (void)_re_U32_570;
        ;
        ;
        U32 _rc_U32_570 = 0;
        (void)_rc_U32_570;
        Bool _t_Bool_597 = U32_lte(&_rc_U32_570, &_re_U32_570);
        (void)_t_Bool_597;
        if (_t_Bool_597) {
            while (1) {
                Bool _wcond_Bool_571 = U32_lt(&_rc_U32_570, &_re_U32_570);
                (void)_wcond_Bool_571;
                if (_wcond_Bool_571) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_570);
                (void)i;
                U32_inc(&_rc_U32_570);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_572 = needle->count;
                    (void)_re_U32_572;
                    U32 _rc_U32_572 = 0;
                    (void)_rc_U32_572;
                    Bool _t_Bool_581 = U32_lte(&_rc_U32_572, &_re_U32_572);
                    (void)_t_Bool_581;
                    if (_t_Bool_581) {
                        while (1) {
                            Bool _wcond_Bool_573 = U32_lt(&_rc_U32_572, &_re_U32_572);
                            (void)_wcond_Bool_573;
                            if (_wcond_Bool_573) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_572);
                            (void)j;
                            U32_inc(&_rc_U32_572);
                            U32 _t_U32_575 = U32_add(i, j);
                            (void)_t_U32_575;
                            U8 *ac = Str_get(self, &_t_U32_575);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_576 = U8_neq(ac, bc);
                            (void)_t_Bool_576;
                            ;
                            ;
                            if (_t_Bool_576) {
                                Bool _t_Bool_574 = 0;
                                (void)_t_Bool_574;
                                found = _t_Bool_574;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_577 = U32_gt(&_rc_U32_572, &_re_U32_572);
                            (void)_wcond_Bool_577;
                            if (_wcond_Bool_577) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_572);
                            (void)j;
                            U32_dec(&_rc_U32_572);
                            U32 _t_U32_579 = U32_add(i, j);
                            (void)_t_U32_579;
                            U8 *ac = Str_get(self, &_t_U32_579);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_580 = U8_neq(ac, bc);
                            (void)_t_Bool_580;
                            ;
                            ;
                            if (_t_Bool_580) {
                                Bool _t_Bool_578 = 0;
                                (void)_t_Bool_578;
                                found = _t_Bool_578;
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
                    I64 _t_I64_582 = U32_to_i64(i);
                    (void)_t_I64_582;
                    last = _t_I64_582;
                    ;
                }
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_583 = U32_gt(&_rc_U32_570, &_re_U32_570);
                (void)_wcond_Bool_583;
                if (_wcond_Bool_583) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_570);
                (void)i;
                U32_dec(&_rc_U32_570);
                Bool found = 1;
                (void)found;
                {
                    U32 _re_U32_584 = needle->count;
                    (void)_re_U32_584;
                    U32 _rc_U32_584 = 0;
                    (void)_rc_U32_584;
                    Bool _t_Bool_593 = U32_lte(&_rc_U32_584, &_re_U32_584);
                    (void)_t_Bool_593;
                    if (_t_Bool_593) {
                        while (1) {
                            Bool _wcond_Bool_585 = U32_lt(&_rc_U32_584, &_re_U32_584);
                            (void)_wcond_Bool_585;
                            if (_wcond_Bool_585) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_584);
                            (void)j;
                            U32_inc(&_rc_U32_584);
                            U32 _t_U32_587 = U32_add(i, j);
                            (void)_t_U32_587;
                            U8 *ac = Str_get(self, &_t_U32_587);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_588 = U8_neq(ac, bc);
                            (void)_t_Bool_588;
                            ;
                            ;
                            if (_t_Bool_588) {
                                Bool _t_Bool_586 = 0;
                                (void)_t_Bool_586;
                                found = _t_Bool_586;
                                ;
                            }
                            ;
                        }
                    } else {
                        while (1) {
                            Bool _wcond_Bool_589 = U32_gt(&_rc_U32_584, &_re_U32_584);
                            (void)_wcond_Bool_589;
                            if (_wcond_Bool_589) {
                            } else {
                                ;
                                break;
                            }
                            ;
                            U32 j = U32_clone(&_rc_U32_584);
                            (void)j;
                            U32_dec(&_rc_U32_584);
                            U32 _t_U32_591 = U32_add(i, j);
                            (void)_t_U32_591;
                            U8 *ac = Str_get(self, &_t_U32_591);
                            (void)ac;
                            U8 *bc = Str_get(needle, &j);
                            (void)bc;
                            Bool _t_Bool_592 = U8_neq(ac, bc);
                            (void)_t_Bool_592;
                            ;
                            ;
                            if (_t_Bool_592) {
                                Bool _t_Bool_590 = 0;
                                (void)_t_Bool_590;
                                found = _t_Bool_590;
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
                    I64 _t_I64_594 = U32_to_i64(i);
                    (void)_t_I64_594;
                    last = _t_I64_594;
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
    U32 _t_U32_628 = 0;
    (void)_t_U32_628;
    Bool _t_Bool_629 = U32_eq(from->count, _t_U32_628);
    (void)_t_Bool_629;
    ;
    if (_t_Bool_629) {
        Str *_t_Str_603 = Str_clone(self);
        (void)_t_Str_603;
        ;
        return _t_Str_603;
    }
    ;
    U32 matches = 0;
    (void)matches;
    U32 start = 0;
    (void)start;
    while (1) {
        U32 _t_U32_605 = U32_sub(self->count, from->count);
        (void)_t_U32_605;
        Bool _wcond_Bool_604 = U32_lte(&start, &_t_U32_605);
        (void)_wcond_Bool_604;
        ;
        if (_wcond_Bool_604) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_606 = U32_sub(self->count, start);
        (void)_t_U32_606;
        Str *rest = Str_substr(self, &start, &_t_U32_606);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_607 = 0;
        (void)_t_I64_607;
        I64 _t_I64_608 = 1;
        (void)_t_I64_608;
        I64 _t_I64_609 = I64_sub(_t_I64_607, _t_I64_608);
        (void)_t_I64_609;
        ;
        ;
        Bool _t_Bool_610 = I64_eq(pos, _t_I64_609);
        (void)_t_Bool_610;
        ;
        if (_t_Bool_610) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        U32 _t_U32_611 = U32_add(start, pos_u);
        (void)_t_U32_611;
        ;
        U32 _t_U32_612 = U32_add(_t_U32_611, from->count);
        (void)_t_U32_612;
        ;
        start = _t_U32_612;
        ;
        U32 _t_U32_613 = 1;
        (void)_t_U32_613;
        U32 _t_U32_614 = U32_add(matches, _t_U32_613);
        (void)_t_U32_614;
        ;
        matches = _t_U32_614;
        ;
    }
    U32 _t_U32_630 = 0;
    (void)_t_U32_630;
    Bool _t_Bool_631 = U32_eq(matches, _t_U32_630);
    (void)_t_Bool_631;
    ;
    if (_t_Bool_631) {
        Str *_t_Str_615 = Str_clone(self);
        (void)_t_Str_615;
        ;
        ;
        ;
        return _t_Str_615;
    }
    ;
    U32 removed = U32_mul(matches, from->count);
    (void)removed;
    U32 added = U32_mul(matches, to->count);
    (void)added;
    ;
    U32 _t_U32_632 = U32_sub(self->count, removed);
    (void)_t_U32_632;
    ;
    U32 _t_U32_633 = U32_add(_t_U32_632, added);
    (void)_t_U32_633;
    ;
    ;
    Str *out = Str_with_capacity(&_t_U32_633);
    (void)out;
    ;
    U32 _t_U32_634 = 0;
    (void)_t_U32_634;
    start = _t_U32_634;
    ;
    while (1) {
        U32 _t_U32_617 = U32_sub(self->count, from->count);
        (void)_t_U32_617;
        Bool _wcond_Bool_616 = U32_lte(&start, &_t_U32_617);
        (void)_wcond_Bool_616;
        ;
        if (_wcond_Bool_616) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_618 = U32_sub(self->count, start);
        (void)_t_U32_618;
        Str *rest = Str_substr(self, &start, &_t_U32_618);
        (void)rest;
        ;
        I64 pos = Str_find(rest, from);
        (void)pos;
        Str_delete(rest, &(Bool){1});
        I64 _t_I64_619 = 0;
        (void)_t_I64_619;
        I64 _t_I64_620 = 1;
        (void)_t_I64_620;
        I64 _t_I64_621 = I64_sub(_t_I64_619, _t_I64_620);
        (void)_t_I64_621;
        ;
        ;
        Bool _t_Bool_622 = I64_eq(pos, _t_I64_621);
        (void)_t_Bool_622;
        ;
        if (_t_Bool_622) {
            ;
            ;
            break;
        }
        ;
        U32 pos_u = I64_to_usize(pos);
        (void)pos_u;
        ;
        Str *_t_Str_623 = Str_substr(self, &start, &pos_u);
        (void)_t_Str_623;
        Str_push_str(out, _t_Str_623);
        Str_delete(_t_Str_623, &(Bool){1});
        Str_push_str(out, to);
        U32 _t_U32_624 = U32_add(start, pos_u);
        (void)_t_U32_624;
        ;
        U32 _t_U32_625 = U32_add(_t_U32_624, from->count);
        (void)_t_U32_625;
        ;
        start = _t_U32_625;
        ;
    }
    Bool _t_Bool_635 = U32_lt(&start, &self->count);
    (void)_t_Bool_635;
    if (_t_Bool_635) {
        U32 _t_U32_626 = U32_sub(self->count, start);
        (void)_t_U32_626;
        Str *_t_Str_627 = Str_substr(self, &start, &_t_U32_626);
        (void)_t_Str_627;
        ;
        Str_push_str(out, _t_Str_627);
        Str_delete(_t_Str_627, &(Bool){1});
    }
    ;
    ;
    return out;
}

Str * Str_get_char(Str * self, U32 * i) {
    (void)self;
    (void)i;
    U32 _t_U32_636 = 1;
    (void)_t_U32_636;
    Str *_t_Str_637 = Str_substr(self, i, &_t_U32_636);
    (void)_t_Str_637;
    ;
    return _t_Str_637;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    (void)prefix;
    Bool _t_Bool_640 = Str_starts_with(self, prefix);
    (void)_t_Bool_640;
    if (_t_Bool_640) {
        U32 _t_U32_638 = U32_sub(self->count, prefix->count);
        (void)_t_U32_638;
        Str *_t_Str_639 = Str_substr(self, &prefix->count, &_t_U32_638);
        (void)_t_Str_639;
        ;
        ;
        return _t_Str_639;
    }
    ;
    Str *_t_Str_641 = Str_clone(self);
    (void)_t_Str_641;
    return _t_Str_641;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    (void)suffix;
    Bool _t_Bool_645 = Str_ends_with(self, suffix);
    (void)_t_Bool_645;
    if (_t_Bool_645) {
        U32 _t_U32_642 = 0;
        (void)_t_U32_642;
        U32 _t_U32_643 = U32_sub(self->count, suffix->count);
        (void)_t_U32_643;
        Str *_t_Str_644 = Str_substr(self, &_t_U32_642, &_t_U32_643);
        (void)_t_Str_644;
        ;
        ;
        ;
        return _t_Str_644;
    }
    ;
    Str *_t_Str_646 = Str_clone(self);
    (void)_t_Str_646;
    return _t_Str_646;
}

Str * Str_from_byte(U8 * byte) {
    (void)byte;
    U64 _t_U64_647 = 2;
    (void)_t_U64_647;
    void * buf = malloc(_t_U64_647);
    (void)buf;
    ;
    U64 _t_U64_648 = 1;
    (void)_t_U64_648;
    memcpy(buf, byte, _t_U64_648);
    ;
    U64 _t_U64_649 = 1;
    (void)_t_U64_649;
    void *_t_v_650 = ptr_add(buf, _t_U64_649);
    (void)_t_v_650;
    I32 _t_I32_651 = 0;
    (void)_t_I32_651;
    U64 _t_U64_652 = 1;
    (void)_t_U64_652;
    memset(_t_v_650, _t_I32_651, _t_U64_652);
    ;
    ;
    ;
    I64 _t_I64_653 = 1;
    (void)_t_I64_653;
    I64 _t_I64_654 = 1;
    (void)_t_I64_654;
    Str *_t_Str_655 = malloc(sizeof(Str));
    _t_Str_655->c_str = buf;
    _t_Str_655->count = _t_I64_653;
    _t_Str_655->cap = _t_I64_654;
    (void)_t_Str_655;
    ;
    ;
    return _t_Str_655;
}

I64 Str_to_i64(Str * self) {
    (void)self;
    U32 _t_U32_716 = 0;
    (void)_t_U32_716;
    Bool _t_Bool_717 = U32_eq(self->count, _t_U32_716);
    (void)_t_Bool_717;
    ;
    if (_t_Bool_717) {
        Str *_t_Str_656 = Str_lit("Str", 3ULL);
        (void)_t_Str_656;
        Type *_t_Type_657 = Type_Struct(_t_Str_656);
        (void)_t_Type_657;
        Str_delete(_t_Str_656, &(Bool){1});
        U32 _t_U32_658 = 1;
        (void)_t_U32_658;
        Array *_va_Array_12 = Array_new(_t_Type_657, &_t_U32_658);
        (void)_va_Array_12;
        Type_delete(_t_Type_657, &(Bool){1});
        ;
        U32 _t_U32_659 = 0;
        (void)_t_U32_659;
        Str *_t_Str_660 = Str_lit("Str.to_i64: empty string", 24ULL);
        (void)_t_Str_660;
        Array_set(_va_Array_12, &_t_U32_659, _t_Str_660);
        ;
        Str *_t_Str_661 = Str_lit("./src/core/str.til:266:37", 25ULL);
        (void)_t_Str_661;
        panic(_t_Str_661, _va_Array_12);
        Str_delete(_t_Str_661, &(Bool){1});
    }
    ;
    I64 result = 0;
    (void)result;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_718 = 0;
    (void)_t_U32_718;
    U8 *first = Str_get(self, &_t_U32_718);
    (void)first;
    U8 _t_U8_719 = 45;
    (void)_t_U8_719;
    Bool _t_Bool_720 = U8_eq(DEREF(first), _t_U8_719);
    (void)_t_Bool_720;
    ;
    ;
    if (_t_Bool_720) {
        Bool _t_Bool_662 = 1;
        (void)_t_Bool_662;
        neg = _t_Bool_662;
        ;
        U32 _t_U32_663 = 1;
        (void)_t_U32_663;
        start = _t_U32_663;
        ;
    }
    ;
    Bool _t_Bool_721 = U32_eq(start, self->count);
    (void)_t_Bool_721;
    if (_t_Bool_721) {
        Str *_t_Str_664 = Str_lit("Str", 3ULL);
        (void)_t_Str_664;
        Type *_t_Type_665 = Type_Struct(_t_Str_664);
        (void)_t_Type_665;
        Str_delete(_t_Str_664, &(Bool){1});
        U32 _t_U32_666 = 1;
        (void)_t_U32_666;
        Array *_va_Array_13 = Array_new(_t_Type_665, &_t_U32_666);
        (void)_va_Array_13;
        Type_delete(_t_Type_665, &(Bool){1});
        ;
        U32 _t_U32_667 = 0;
        (void)_t_U32_667;
        Str *_t_Str_668 = Str_lit("Str.to_i64: no digits", 21ULL);
        (void)_t_Str_668;
        Array_set(_va_Array_13, &_t_U32_667, _t_Str_668);
        ;
        Str *_t_Str_669 = Str_lit("./src/core/str.til:275:41", 25ULL);
        (void)_t_Str_669;
        panic(_t_Str_669, _va_Array_13);
        Str_delete(_t_Str_669, &(Bool){1});
    }
    ;
    {
        U32 _re_U32_670 = self->count;
        (void)_re_U32_670;
        U32 _rc_U32_670 = U32_clone(&start);
        (void)_rc_U32_670;
        Bool _t_Bool_713 = U32_lte(&_rc_U32_670, &_re_U32_670);
        (void)_t_Bool_713;
        if (_t_Bool_713) {
            while (1) {
                Bool _wcond_Bool_671 = U32_lt(&_rc_U32_670, &_re_U32_670);
                (void)_wcond_Bool_671;
                if (_wcond_Bool_671) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_670);
                (void)i;
                U32_inc(&_rc_U32_670);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_682 = U8_to_i64(DEREF(ch));
                (void)_t_I64_682;
                ;
                I64 _t_I64_683 = 48;
                (void)_t_I64_683;
                I64 d = I64_sub(_t_I64_682, _t_I64_683);
                (void)d;
                ;
                ;
                I64 _t_I64_684 = 0;
                (void)_t_I64_684;
                I64 _t_I64_685 = 9;
                (void)_t_I64_685;
                Bool _t_Bool_686 = I64_lt(&d, &_t_I64_684);
                (void)_t_Bool_686;
                ;
                Bool _t_Bool_687 = I64_gt(&d, &_t_I64_685);
                (void)_t_Bool_687;
                ;
                Bool _t_Bool_688 = or(_t_Bool_686, _t_Bool_687);
                (void)_t_Bool_688;
                ;
                ;
                if (_t_Bool_688) {
                    Str *_t_Str_672 = Str_lit("Str", 3ULL);
                    (void)_t_Str_672;
                    Type *_t_Type_673 = Type_Struct(_t_Str_672);
                    (void)_t_Type_673;
                    Str_delete(_t_Str_672, &(Bool){1});
                    U32 _t_U32_674 = 3;
                    (void)_t_U32_674;
                    Array *_va_Array_14 = Array_new(_t_Type_673, &_t_U32_674);
                    (void)_va_Array_14;
                    Type_delete(_t_Type_673, &(Bool){1});
                    ;
                    U32 _t_U32_675 = 0;
                    (void)_t_U32_675;
                    Str *_t_Str_676 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_676;
                    Array_set(_va_Array_14, &_t_U32_675, _t_Str_676);
                    ;
                    U32 _t_U32_677 = 1;
                    (void)_t_U32_677;
                    Str *_t_Str_678 = Str_clone(self);
                    (void)_t_Str_678;
                    Array_set(_va_Array_14, &_t_U32_677, _t_Str_678);
                    ;
                    U32 _t_U32_679 = 2;
                    (void)_t_U32_679;
                    Str *_t_Str_680 = Str_lit("'", 1ULL);
                    (void)_t_Str_680;
                    Array_set(_va_Array_14, &_t_U32_679, _t_Str_680);
                    ;
                    Str *_t_Str_681 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_681;
                    panic(_t_Str_681, _va_Array_14);
                    Str_delete(_t_Str_681, &(Bool){1});
                }
                ;
                I64 _t_I64_689 = 10;
                (void)_t_I64_689;
                I64 _t_I64_690 = I64_mul(result, _t_I64_689);
                (void)_t_I64_690;
                ;
                I64 _t_I64_691 = I64_add(_t_I64_690, d);
                (void)_t_I64_691;
                ;
                ;
                result = _t_I64_691;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_692 = U32_gt(&_rc_U32_670, &_re_U32_670);
                (void)_wcond_Bool_692;
                if (_wcond_Bool_692) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_670);
                (void)i;
                U32_dec(&_rc_U32_670);
                U8 *ch = Str_get(self, &i);
                (void)ch;
                I64 _t_I64_703 = U8_to_i64(DEREF(ch));
                (void)_t_I64_703;
                ;
                I64 _t_I64_704 = 48;
                (void)_t_I64_704;
                I64 d = I64_sub(_t_I64_703, _t_I64_704);
                (void)d;
                ;
                ;
                I64 _t_I64_705 = 0;
                (void)_t_I64_705;
                I64 _t_I64_706 = 9;
                (void)_t_I64_706;
                Bool _t_Bool_707 = I64_lt(&d, &_t_I64_705);
                (void)_t_Bool_707;
                ;
                Bool _t_Bool_708 = I64_gt(&d, &_t_I64_706);
                (void)_t_Bool_708;
                ;
                Bool _t_Bool_709 = or(_t_Bool_707, _t_Bool_708);
                (void)_t_Bool_709;
                ;
                ;
                if (_t_Bool_709) {
                    Str *_t_Str_693 = Str_lit("Str", 3ULL);
                    (void)_t_Str_693;
                    Type *_t_Type_694 = Type_Struct(_t_Str_693);
                    (void)_t_Type_694;
                    Str_delete(_t_Str_693, &(Bool){1});
                    U32 _t_U32_695 = 3;
                    (void)_t_U32_695;
                    Array *_va_Array_15 = Array_new(_t_Type_694, &_t_U32_695);
                    (void)_va_Array_15;
                    Type_delete(_t_Type_694, &(Bool){1});
                    ;
                    U32 _t_U32_696 = 0;
                    (void)_t_U32_696;
                    Str *_t_Str_697 = Str_lit("Str.to_i64: invalid char in '", 29ULL);
                    (void)_t_Str_697;
                    Array_set(_va_Array_15, &_t_U32_696, _t_Str_697);
                    ;
                    U32 _t_U32_698 = 1;
                    (void)_t_U32_698;
                    Str *_t_Str_699 = Str_clone(self);
                    (void)_t_Str_699;
                    Array_set(_va_Array_15, &_t_U32_698, _t_Str_699);
                    ;
                    U32 _t_U32_700 = 2;
                    (void)_t_U32_700;
                    Str *_t_Str_701 = Str_lit("'", 1ULL);
                    (void)_t_Str_701;
                    Array_set(_va_Array_15, &_t_U32_700, _t_Str_701);
                    ;
                    Str *_t_Str_702 = Str_lit("./src/core/str.til:280:23", 25ULL);
                    (void)_t_Str_702;
                    panic(_t_Str_702, _va_Array_15);
                    Str_delete(_t_Str_702, &(Bool){1});
                }
                ;
                I64 _t_I64_710 = 10;
                (void)_t_I64_710;
                I64 _t_I64_711 = I64_mul(result, _t_I64_710);
                (void)_t_I64_711;
                ;
                I64 _t_I64_712 = I64_add(_t_I64_711, d);
                (void)_t_I64_712;
                ;
                ;
                result = _t_I64_712;
                ;
            }
        }
        ;
        ;
        ;
    }
    ;
    if (neg) {
        I64 _t_I64_714 = 0;
        (void)_t_I64_714;
        I64 _t_I64_715 = I64_sub(_t_I64_714, result);
        (void)_t_I64_715;
        ;
        ;
        ;
        return _t_I64_715;
    }
    ;
    return result;
}

U8 Str_to_u8(Str * self) {
    (void)self;
    I64 _t_I64_722 = Str_to_i64(self);
    (void)_t_I64_722;
    U8 _t_U8_723 = I64_to_u8(_t_I64_722);
    (void)_t_U8_723;
    ;
    return _t_U8_723;
}

I32 Str_to_i32(Str * self) {
    (void)self;
    I64 _t_I64_724 = Str_to_i64(self);
    (void)_t_I64_724;
    I32 _t_I32_725 = I64_to_i32(_t_I64_724);
    (void)_t_I32_725;
    ;
    return _t_I32_725;
}

F32 Str_to_f32(Str * self) {
    (void)self;
    U32 start = 0;
    (void)start;
    Bool neg = 0;
    (void)neg;
    U32 _t_U32_751 = Str_len(self);
    (void)_t_U32_751;
    U32 _t_U32_752 = 0;
    (void)_t_U32_752;
    U32 _t_U32_753 = 0;
    (void)_t_U32_753;
    U8 *_t_U8_754 = Str_get(self, &_t_U32_753);
    (void)_t_U8_754;
    U8 _t_U8_755 = 45;
    (void)_t_U8_755;
    Bool _t_Bool_756 = U32_gt(&_t_U32_751, &_t_U32_752);
    (void)_t_Bool_756;
    ;
    ;
    Bool _t_Bool_757 = U8_eq(DEREF(_t_U8_754), _t_U8_755);
    (void)_t_Bool_757;
    ;
    ;
    Bool _t_Bool_758 = and(_t_Bool_756, _t_Bool_757);
    (void)_t_Bool_758;
    ;
    ;
    if (_t_Bool_758) {
        Bool _t_Bool_726 = 1;
        (void)_t_Bool_726;
        neg = _t_Bool_726;
        ;
        U32 _t_U32_727 = 1;
        (void)_t_U32_727;
        start = _t_U32_727;
        ;
    }
    ;
    U32 _t_U32_759 = Str_len(self);
    (void)_t_U32_759;
    U32 _t_U32_760 = U32_sub(_t_U32_759, start);
    (void)_t_U32_760;
    ;
    Str *rest = Str_substr(self, &start, &_t_U32_760);
    (void)rest;
    ;
    ;
    Str *_t_Str_761 = Str_lit(".", 1ULL);
    (void)_t_Str_761;
    I64 dot = Str_find(rest, _t_Str_761);
    (void)dot;
    Str_delete(_t_Str_761, &(Bool){1});
    I64 _t_I64_762 = 0;
    (void)_t_I64_762;
    I64 _t_I64_763 = 1;
    (void)_t_I64_763;
    I64 _t_I64_764 = I64_sub(_t_I64_762, _t_I64_763);
    (void)_t_I64_764;
    ;
    ;
    Bool _t_Bool_765 = I64_eq(dot, _t_I64_764);
    (void)_t_Bool_765;
    ;
    if (_t_Bool_765) {
        I64 _t_I64_731 = Str_to_i64(rest);
        (void)_t_I64_731;
        F32 out = I64_to_f32(_t_I64_731);
        (void)out;
        ;
        if (neg) {
            I64 _t_I64_728 = 0;
            (void)_t_I64_728;
            F32 _t_F32_729 = I64_to_f32(_t_I64_728);
            (void)_t_F32_729;
            ;
            F32 _t_F32_730 = F32_sub(_t_F32_729, out);
            (void)_t_F32_730;
            ;
            ;
            ;
            ;
            ;
            Str_delete(rest, &(Bool){1});
            return _t_F32_730;
        }
        ;
        ;
        ;
        Str_delete(rest, &(Bool){1});
        return out;
    }
    ;
    U32 _t_U32_766 = 0;
    (void)_t_U32_766;
    U32 _t_U32_767 = I64_to_usize(dot);
    (void)_t_U32_767;
    Str *int_part = Str_substr(rest, &_t_U32_766, &_t_U32_767);
    (void)int_part;
    ;
    ;
    U32 _t_U32_768 = I64_to_usize(dot);
    (void)_t_U32_768;
    U32 _t_U32_769 = 1;
    (void)_t_U32_769;
    U32 _t_U32_770 = I64_to_usize(dot);
    (void)_t_U32_770;
    ;
    U32 _t_U32_771 = 1;
    (void)_t_U32_771;
    U32 _t_U32_772 = Str_len(rest);
    (void)_t_U32_772;
    U32 _t_U32_773 = U32_add(_t_U32_770, _t_U32_771);
    (void)_t_U32_773;
    ;
    ;
    U32 _t_U32_774 = U32_add(_t_U32_768, _t_U32_769);
    (void)_t_U32_774;
    ;
    ;
    U32 _t_U32_775 = U32_sub(_t_U32_772, _t_U32_773);
    (void)_t_U32_775;
    ;
    ;
    Str *frac_part = Str_substr(rest, &_t_U32_774, &_t_U32_775);
    (void)frac_part;
    ;
    ;
    Str_delete(rest, &(Bool){1});
    I64 _t_I64_776 = 0;
    (void)_t_I64_776;
    F32 out = I64_to_f32(_t_I64_776);
    (void)out;
    ;
    U32 _t_U32_777 = Str_len(int_part);
    (void)_t_U32_777;
    U32 _t_U32_778 = 0;
    (void)_t_U32_778;
    Bool _t_Bool_779 = U32_gt(&_t_U32_777, &_t_U32_778);
    (void)_t_Bool_779;
    ;
    ;
    if (_t_Bool_779) {
        I64 _t_I64_732 = Str_to_i64(int_part);
        (void)_t_I64_732;
        F32 _t_F32_733 = I64_to_f32(_t_I64_732);
        (void)_t_F32_733;
        ;
        out = _t_F32_733;
        ;
    }
    ;
    Str_delete(int_part, &(Bool){1});
    U32 _t_U32_780 = Str_len(frac_part);
    (void)_t_U32_780;
    U32 _t_U32_781 = 0;
    (void)_t_U32_781;
    Bool _t_Bool_782 = U32_gt(&_t_U32_780, &_t_U32_781);
    (void)_t_Bool_782;
    ;
    ;
    if (_t_Bool_782) {
        I64 _t_I64_744 = Str_to_i64(frac_part);
        (void)_t_I64_744;
        F32 frac = I64_to_f32(_t_I64_744);
        (void)frac;
        ;
        I64 _t_I64_745 = 1;
        (void)_t_I64_745;
        F32 scale = I64_to_f32(_t_I64_745);
        (void)scale;
        ;
        {
            U32 _re_U32_734 = Str_len(frac_part);
            (void)_re_U32_734;
            U32 _rc_U32_734 = 0;
            (void)_rc_U32_734;
            Bool _t_Bool_743 = U32_lte(&_rc_U32_734, &_re_U32_734);
            (void)_t_Bool_743;
            if (_t_Bool_743) {
                while (1) {
                    Bool _wcond_Bool_735 = U32_lt(&_rc_U32_734, &_re_U32_734);
                    (void)_wcond_Bool_735;
                    if (_wcond_Bool_735) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_734);
                    (void)_;
                    ;
                    U32_inc(&_rc_U32_734);
                    I64 _t_I64_736 = 10;
                    (void)_t_I64_736;
                    F32 _t_F32_737 = I64_to_f32(_t_I64_736);
                    (void)_t_F32_737;
                    ;
                    F32 _t_F32_738 = F32_mul(scale, _t_F32_737);
                    (void)_t_F32_738;
                    ;
                    scale = _t_F32_738;
                    ;
                }
            } else {
                while (1) {
                    Bool _wcond_Bool_739 = U32_gt(&_rc_U32_734, &_re_U32_734);
                    (void)_wcond_Bool_739;
                    if (_wcond_Bool_739) {
                    } else {
                        ;
                        break;
                    }
                    ;
                    U32 _ = U32_clone(&_rc_U32_734);
                    (void)_;
                    ;
                    U32_dec(&_rc_U32_734);
                    I64 _t_I64_740 = 10;
                    (void)_t_I64_740;
                    F32 _t_F32_741 = I64_to_f32(_t_I64_740);
                    (void)_t_F32_741;
                    ;
                    F32 _t_F32_742 = F32_mul(scale, _t_F32_741);
                    (void)_t_F32_742;
                    ;
                    scale = _t_F32_742;
                    ;
                }
            }
            ;
            ;
            ;
        }
        F32 _t_F32_746 = F32_div(frac, scale);
        (void)_t_F32_746;
        ;
        ;
        F32 _t_F32_747 = F32_add(out, _t_F32_746);
        (void)_t_F32_747;
        ;
        out = _t_F32_747;
        ;
    }
    ;
    Str_delete(frac_part, &(Bool){1});
    if (neg) {
        I64 _t_I64_748 = 0;
        (void)_t_I64_748;
        F32 _t_F32_749 = I64_to_f32(_t_I64_748);
        (void)_t_F32_749;
        ;
        F32 _t_F32_750 = F32_sub(_t_F32_749, out);
        (void)_t_F32_750;
        ;
        ;
        ;
        return _t_F32_750;
    }
    ;
    return out;
}

Vec * Str_split(Str * self, Str * delim) {
    (void)self;
    (void)delim;
    Str *_t_Str_799 = Str_lit("Str", 3ULL);
    (void)_t_Str_799;
    Type *_t_Type_800 = Type_Struct(_t_Str_799);
    (void)_t_Type_800;
    Str_delete(_t_Str_799, &(Bool){1});
    Vec *parts = Vec_new(_t_Type_800);
    (void)parts;
    Type_delete(_t_Type_800, &(Bool){1});
    U32 _t_U32_801 = Str_len(delim);
    (void)_t_U32_801;
    U32 _t_U32_802 = 0;
    (void)_t_U32_802;
    Bool _t_Bool_803 = U32_eq(_t_U32_801, _t_U32_802);
    (void)_t_Bool_803;
    ;
    ;
    if (_t_Bool_803) {
        Str *_t_Str_783 = Str_clone(self);
        (void)_t_Str_783;
        Vec_push(parts, _t_Str_783);
        ;
        return parts;
    }
    ;
    U32 start = 0;
    (void)start;
    U32 pos = 0;
    (void)pos;
    while (1) {
        U32 _t_U32_793 = Str_len(self);
        (void)_t_U32_793;
        U32 _t_U32_794 = Str_len(delim);
        (void)_t_U32_794;
        U32 _t_U32_795 = U32_sub(_t_U32_793, _t_U32_794);
        (void)_t_U32_795;
        ;
        ;
        Bool _wcond_Bool_784 = U32_lte(&pos, &_t_U32_795);
        (void)_wcond_Bool_784;
        ;
        if (_wcond_Bool_784) {
        } else {
            ;
            break;
        }
        ;
        U32 _t_U32_796 = Str_len(delim);
        (void)_t_U32_796;
        Str *_t_Str_797 = Str_substr(self, &pos, &_t_U32_796);
        (void)_t_Str_797;
        ;
        Bool _t_Bool_798 = Str_eq(_t_Str_797, delim);
        (void)_t_Bool_798;
        Str_delete(_t_Str_797, &(Bool){1});
        if (_t_Bool_798) {
            U32 _t_U32_785 = U32_sub(pos, start);
            (void)_t_U32_785;
            Str *_t_Str_786 = Str_substr(self, &start, &_t_U32_785);
            (void)_t_Str_786;
            ;
            Str *_t_Str_787 = Str_clone(_t_Str_786);
            (void)_t_Str_787;
            Str_delete(_t_Str_786, &(Bool){1});
            Vec_push(parts, _t_Str_787);
            U32 _t_U32_788 = Str_len(delim);
            (void)_t_U32_788;
            U32 _t_U32_789 = U32_add(pos, _t_U32_788);
            (void)_t_U32_789;
            ;
            start = _t_U32_789;
            ;
            U32 _t_U32_790 = U32_clone(&start);
            (void)_t_U32_790;
            pos = _t_U32_790;
            ;
        } else {
            U32 _t_U32_791 = 1;
            (void)_t_U32_791;
            U32 _t_U32_792 = U32_add(pos, _t_U32_791);
            (void)_t_U32_792;
            ;
            pos = _t_U32_792;
            ;
        }
        ;
    }
    ;
    U32 _t_U32_804 = Str_len(self);
    (void)_t_U32_804;
    U32 _t_U32_805 = U32_sub(_t_U32_804, start);
    (void)_t_U32_805;
    ;
    Str *_t_Str_806 = Str_substr(self, &start, &_t_U32_805);
    (void)_t_Str_806;
    ;
    ;
    Str *_t_Str_807 = Str_clone(_t_Str_806);
    (void)_t_Str_807;
    Str_delete(_t_Str_806, &(Bool){1});
    Vec_push(parts, _t_Str_807);
    return parts;
}

U32 Str_size(void) {
    I64 _t_I64_808 = 16;
    (void)_t_I64_808;
    return _t_I64_808;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_809 = Str_cmp(a, b);
    (void)_t_I64_809;
    I64 _t_I64_810 = 0;
    (void)_t_I64_810;
    Bool _t_Bool_811 = I64_eq(_t_I64_809, _t_I64_810);
    (void)_t_Bool_811;
    ;
    ;
    return _t_Bool_811;
}

Bool Str_lt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_812 = 0;
    (void)_t_I64_812;
    I64 _t_I64_813 = 1;
    (void)_t_I64_813;
    I64 _t_I64_814 = Str_cmp(a, b);
    (void)_t_I64_814;
    I64 _t_I64_815 = I64_sub(_t_I64_812, _t_I64_813);
    (void)_t_I64_815;
    ;
    ;
    Bool _t_Bool_816 = I64_eq(_t_I64_814, _t_I64_815);
    (void)_t_Bool_816;
    ;
    ;
    return _t_Bool_816;
}

Bool Str_gt(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_817 = Str_cmp(a, b);
    (void)_t_I64_817;
    I64 _t_I64_818 = 1;
    (void)_t_I64_818;
    Bool _t_Bool_819 = I64_eq(_t_I64_817, _t_I64_818);
    (void)_t_Bool_819;
    ;
    ;
    return _t_Bool_819;
}

Bool Str_neq(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_820 = Str_eq(a, b);
    (void)_t_Bool_820;
    Bool _t_Bool_821 = not(_t_Bool_820);
    (void)_t_Bool_821;
    ;
    return _t_Bool_821;
}

Bool Str_lte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_822 = Str_gt(a, b);
    (void)_t_Bool_822;
    Bool _t_Bool_823 = not(_t_Bool_822);
    (void)_t_Bool_823;
    ;
    return _t_Bool_823;
}

Bool Str_gte(Str * a, Str * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_824 = Str_lt(a, b);
    (void)_t_Bool_824;
    Bool _t_Bool_825 = not(_t_Bool_824);
    (void)_t_Bool_825;
    ;
    return _t_Bool_825;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_857 = 8;
    (void)_t_I64_857;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_857; return _r; }
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
    I64 _t_I64_860 = I16_to_i64(DEREF(val));
    (void)_t_I64_860;
    Str *_t_Str_861 = I64_to_str(&_t_I64_860);
    (void)_t_Str_861;
    ;
    return _t_Str_861;
}

void I16_inc(I16 * self) {
    (void)self;
    I16 _t_I16_862 = 1;
    (void)_t_I16_862;
    I16 _t_I16_863 = I16_add(DEREF(self), _t_I16_862);
    (void)_t_I16_863;
    ;
    *self = _t_I16_863;
    ;
}

void I16_dec(I16 * self) {
    (void)self;
    I16 _t_I16_864 = 1;
    (void)_t_I16_864;
    I16 _t_I16_865 = I16_sub(DEREF(self), _t_I16_864);
    (void)_t_I16_865;
    ;
    *self = _t_I16_865;
    ;
}

I16 * I16_unity(I16 * _self) {
    (void)_self;
    I64 _t_I64_866 = 1;
    (void)_t_I64_866;
    I16 _t_I16_867 = I64_to_i16(_t_I64_866);
    (void)_t_I16_867;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_867; return _r; }
}

I16 * I16_neg(I16 * a) {
    (void)a;
    I64 _t_I64_868 = 0;
    (void)_t_I64_868;
    I64 _t_I64_869 = I16_to_i64(DEREF(a));
    (void)_t_I64_869;
    I64 _t_I64_870 = I64_sub(_t_I64_868, _t_I64_869);
    (void)_t_I64_870;
    ;
    ;
    I16 _t_I16_871 = I64_to_i16(_t_I64_870);
    (void)_t_I16_871;
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_871; return _r; }
}

I16 * I16_abs(I16 * a) {
    (void)a;
    I64 _t_I64_876 = I16_to_i64(DEREF(a));
    (void)_t_I64_876;
    I64 _t_I64_877 = 0;
    (void)_t_I64_877;
    Bool _t_Bool_878 = I64_lt(&_t_I64_876, &_t_I64_877);
    (void)_t_Bool_878;
    ;
    ;
    if (_t_Bool_878) {
        I64 _t_I64_872 = 0;
        (void)_t_I64_872;
        I64 _t_I64_873 = I16_to_i64(DEREF(a));
        (void)_t_I64_873;
        I64 _t_I64_874 = I64_sub(_t_I64_872, _t_I64_873);
        (void)_t_I64_874;
        ;
        ;
        I16 _t_I16_875 = I64_to_i16(_t_I64_874);
        (void)_t_I16_875;
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_875; return _r; }
    }
    ;
    I16 _t_I16_879 = I16_clone(a);
    (void)_t_I16_879;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t_I16_879; return _r; }
}

U64 I16_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I16 *au = a;
    (void)au;
    I16 *bu = b;
    (void)bu;
    Bool _t_Bool_883 = I16_lte(au, bu);
    (void)_t_Bool_883;
    if (_t_Bool_883) {
        I16 _t_I16_880 = I16_sub(DEREF(bu), DEREF(au));
        (void)_t_I16_880;
        I64 _t_I64_881 = I16_to_i64(_t_I16_880);
        (void)_t_I64_881;
        ;
        U64 _t_U64_882 = I64_to_u64(_t_I64_881);
        (void)_t_U64_882;
        ;
        ;
        return _t_U64_882;
    }
    ;
    I16 _t_I16_884 = I16_sub(DEREF(au), DEREF(bu));
    (void)_t_I16_884;
    I64 _t_I64_885 = I16_to_i64(_t_I16_884);
    (void)_t_I64_885;
    ;
    U64 _t_U64_886 = I64_to_u64(_t_I64_885);
    (void)_t_U64_886;
    ;
    return _t_U64_886;
}

void I16_delete(I16 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I16_size(void) {
    I64 _t_I64_887 = 2;
    (void)_t_I64_887;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_887; return _r; }
}

Bool I16_lt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_888 = 0;
    (void)_t_I64_888;
    I64 _t_I64_889 = 1;
    (void)_t_I64_889;
    I64 _t_I64_890 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_890;
    I64 _t_I64_891 = I64_sub(_t_I64_888, _t_I64_889);
    (void)_t_I64_891;
    ;
    ;
    Bool _t_Bool_892 = I64_eq(_t_I64_890, _t_I64_891);
    (void)_t_Bool_892;
    ;
    ;
    return _t_Bool_892;
}

Bool I16_gt(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_893 = I16_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_893;
    I64 _t_I64_894 = 1;
    (void)_t_I64_894;
    Bool _t_Bool_895 = I64_eq(_t_I64_893, _t_I64_894);
    (void)_t_Bool_895;
    ;
    ;
    return _t_Bool_895;
}

Bool I16_neq(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_896 = I16_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_896;
    Bool _t_Bool_897 = not(_t_Bool_896);
    (void)_t_Bool_897;
    ;
    return _t_Bool_897;
}

Bool I16_lte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_898 = I16_gt(a, b);
    (void)_t_Bool_898;
    Bool _t_Bool_899 = not(_t_Bool_898);
    (void)_t_Bool_899;
    ;
    return _t_Bool_899;
}

Bool I16_gte(I16 * a, I16 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_900 = I16_lt(a, b);
    (void)_t_Bool_900;
    Bool _t_Bool_901 = not(_t_Bool_900);
    (void)_t_Bool_901;
    ;
    return _t_Bool_901;
}

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_938 = 0;
    (void)_t_I64_938;
    Bool _t_Bool_939 = I64_eq(DEREF(val), _t_I64_938);
    (void)_t_Bool_939;
    ;
    if (_t_Bool_939) {
        U64 _t_U64_902 = 2;
        (void)_t_U64_902;
        void * buf = malloc(_t_U64_902);
        (void)buf;
        ;
        I64 _t_I64_903 = 48;
        (void)_t_I64_903;
        U64 _t_U64_904 = 1;
        (void)_t_U64_904;
        memcpy(buf, &_t_I64_903, _t_U64_904);
        ;
        ;
        U64 _t_U64_905 = 1;
        (void)_t_U64_905;
        void *_t_v_906 = ptr_add(buf, _t_U64_905);
        (void)_t_v_906;
        I32 _t_I32_907 = 0;
        (void)_t_I32_907;
        U64 _t_U64_908 = 1;
        (void)_t_U64_908;
        memset(_t_v_906, _t_I32_907, _t_U64_908);
        ;
        ;
        ;
        I64 _t_I64_909 = 1;
        (void)_t_I64_909;
        I64 _t_I64_910 = 1;
        (void)_t_I64_910;
        Str *_t_Str_911 = malloc(sizeof(Str));
        _t_Str_911->c_str = buf;
        _t_Str_911->count = _t_I64_909;
        _t_Str_911->cap = _t_I64_910;
        (void)_t_Str_911;
        ;
        ;
        ;
        return _t_Str_911;
    }
    ;
    Bool is_neg = 0;
    (void)is_neg;
    I64 v = I64_clone(val);
    (void)v;
    I64 _t_I64_940 = 0;
    (void)_t_I64_940;
    Bool _t_Bool_941 = I64_lt(val, &_t_I64_940);
    (void)_t_Bool_941;
    ;
    if (_t_Bool_941) {
        Bool _t_Bool_912 = 1;
        (void)_t_Bool_912;
        is_neg = _t_Bool_912;
        ;
        I64 _t_I64_913 = 0;
        (void)_t_I64_913;
        I64 _t_I64_914 = I64_sub(_t_I64_913, DEREF(val));
        (void)_t_I64_914;
        ;
        v = _t_I64_914;
        ;
    }
    ;
    U64 ndigits = 0;
    (void)ndigits;
    I64 tmp = I64_clone(&v);
    (void)tmp;
    while (1) {
        I64 _t_I64_916 = 0;
        (void)_t_I64_916;
        Bool _wcond_Bool_915 = I64_gt(&tmp, &_t_I64_916);
        (void)_wcond_Bool_915;
        ;
        if (_wcond_Bool_915) {
        } else {
            ;
            break;
        }
        ;
        U64 _t_U64_917 = 1;
        (void)_t_U64_917;
        U64 _t_U64_918 = U64_add(ndigits, _t_U64_917);
        (void)_t_U64_918;
        ;
        ndigits = _t_U64_918;
        ;
        I64 _t_I64_919 = 10;
        (void)_t_I64_919;
        I64 _t_I64_920 = I64_div(tmp, _t_I64_919);
        (void)_t_I64_920;
        ;
        tmp = _t_I64_920;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    (void)total;
    ;
    if (is_neg) {
        U64 _t_U64_921 = 1;
        (void)_t_U64_921;
        U64 _t_U64_922 = U64_add(total, _t_U64_921);
        (void)_t_U64_922;
        ;
        total = _t_U64_922;
        ;
    }
    U64 _t_U64_942 = 1;
    (void)_t_U64_942;
    U64 _t_U64_943 = U64_add(total, _t_U64_942);
    (void)_t_U64_943;
    ;
    void * buf = malloc(_t_U64_943);
    (void)buf;
    ;
    if (is_neg) {
        I64 _t_I64_923 = 45;
        (void)_t_I64_923;
        U64 _t_U64_924 = 1;
        (void)_t_U64_924;
        memcpy(buf, &_t_I64_923, _t_U64_924);
        ;
        ;
    }
    ;
    U64 _t_U64_944 = 1;
    (void)_t_U64_944;
    U64 i = U64_sub(total, _t_U64_944);
    (void)i;
    ;
    while (1) {
        I64 _t_I64_926 = 0;
        (void)_t_I64_926;
        Bool _wcond_Bool_925 = I64_gt(&v, &_t_I64_926);
        (void)_wcond_Bool_925;
        ;
        if (_wcond_Bool_925) {
        } else {
            ;
            break;
        }
        ;
        I64 _t_I64_927 = 10;
        (void)_t_I64_927;
        I64 _t_I64_928 = I64_mod(v, _t_I64_927);
        (void)_t_I64_928;
        ;
        I64 _t_I64_929 = 48;
        (void)_t_I64_929;
        I64 _t_I64_930 = I64_add(_t_I64_928, _t_I64_929);
        (void)_t_I64_930;
        ;
        ;
        void *_t_v_931 = ptr_add(buf, i);
        (void)_t_v_931;
        U8 _t_U8_932 = I64_to_u8(_t_I64_930);
        (void)_t_U8_932;
        ;
        U64 _t_U64_933 = 1;
        (void)_t_U64_933;
        memcpy(_t_v_931, &_t_U8_932, _t_U64_933);
        ;
        ;
        I64 _t_I64_934 = 10;
        (void)_t_I64_934;
        I64 _t_I64_935 = I64_div(v, _t_I64_934);
        (void)_t_I64_935;
        ;
        v = _t_I64_935;
        ;
        U64 _t_U64_936 = 1;
        (void)_t_U64_936;
        U64 _t_U64_937 = U64_sub(i, _t_U64_936);
        (void)_t_U64_937;
        ;
        i = _t_U64_937;
        ;
    }
    ;
    ;
    void *_t_v_945 = ptr_add(buf, total);
    (void)_t_v_945;
    I32 _t_I32_946 = 0;
    (void)_t_I32_946;
    U64 _t_U64_947 = 1;
    (void)_t_U64_947;
    memset(_t_v_945, _t_I32_946, _t_U64_947);
    ;
    ;
    Str *_t_Str_948 = malloc(sizeof(Str));
    _t_Str_948->c_str = buf;
    _t_Str_948->count = total;
    _t_Str_948->cap = total;
    (void)_t_Str_948;
    ;
    return _t_Str_948;
}

void I64_inc(I64 * self) {
    (void)self;
    I64 _t_I64_949 = 1;
    (void)_t_I64_949;
    I64 _t_I64_950 = I64_add(DEREF(self), _t_I64_949);
    (void)_t_I64_950;
    ;
    *self = _t_I64_950;
    ;
}

void I64_dec(I64 * self) {
    (void)self;
    I64 _t_I64_951 = 1;
    (void)_t_I64_951;
    I64 _t_I64_952 = I64_sub(DEREF(self), _t_I64_951);
    (void)_t_I64_952;
    ;
    *self = _t_I64_952;
    ;
}

I64 * I64_unity(I64 * _self) {
    (void)_self;
    I64 _t_I64_953 = 1;
    (void)_t_I64_953;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_953; return _r; }
}

I64 * I64_neg(I64 * a) {
    (void)a;
    I64 _t_I64_954 = 0;
    (void)_t_I64_954;
    I64 _t_I64_955 = I64_sub(_t_I64_954, DEREF(a));
    (void)_t_I64_955;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_955; return _r; }
}

I64 * I64_abs(I64 * a) {
    (void)a;
    I64 _t_I64_958 = 0;
    (void)_t_I64_958;
    Bool _t_Bool_959 = I64_lt(a, &_t_I64_958);
    (void)_t_Bool_959;
    ;
    if (_t_Bool_959) {
        I64 _t_I64_956 = 0;
        (void)_t_I64_956;
        I64 _t_I64_957 = I64_sub(_t_I64_956, DEREF(a));
        (void)_t_I64_957;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_957; return _r; }
    }
    ;
    I64 _t_I64_960 = I64_clone(a);
    (void)_t_I64_960;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_960; return _r; }
}

U64 I64_distance(void * a, void * b) {
    (void)a;
    (void)b;
    I64 *au = a;
    (void)au;
    I64 *bu = b;
    (void)bu;
    Bool _t_Bool_963 = I64_lte(au, bu);
    (void)_t_Bool_963;
    if (_t_Bool_963) {
        I64 _t_I64_961 = I64_sub(DEREF(bu), DEREF(au));
        (void)_t_I64_961;
        U64 _t_U64_962 = I64_to_u64(_t_I64_961);
        (void)_t_U64_962;
        ;
        ;
        return _t_U64_962;
    }
    ;
    I64 _t_I64_964 = I64_sub(DEREF(au), DEREF(bu));
    (void)_t_I64_964;
    U64 _t_U64_965 = I64_to_u64(_t_I64_964);
    (void)_t_U64_965;
    ;
    return _t_U64_965;
}

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_966 = 8;
    (void)_t_I64_966;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_966; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_967 = 0;
    (void)_t_I64_967;
    I64 _t_I64_968 = 1;
    (void)_t_I64_968;
    I64 _t_I64_969 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_969;
    I64 _t_I64_970 = I64_sub(_t_I64_967, _t_I64_968);
    (void)_t_I64_970;
    ;
    ;
    Bool _t_Bool_971 = I64_eq(_t_I64_969, _t_I64_970);
    (void)_t_Bool_971;
    ;
    ;
    return _t_Bool_971;
}

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_972 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_972;
    I64 _t_I64_973 = 1;
    (void)_t_I64_973;
    Bool _t_Bool_974 = I64_eq(_t_I64_972, _t_I64_973);
    (void)_t_Bool_974;
    ;
    ;
    return _t_Bool_974;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_975 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_975;
    Bool _t_Bool_976 = not(_t_Bool_975);
    (void)_t_Bool_976;
    ;
    return _t_Bool_976;
}

Bool I64_lte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_977 = I64_gt(a, b);
    (void)_t_Bool_977;
    Bool _t_Bool_978 = not(_t_Bool_977);
    (void)_t_Bool_978;
    ;
    return _t_Bool_978;
}

Bool I64_gte(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_979 = I64_lt(a, b);
    (void)_t_Bool_979;
    Bool _t_Bool_980 = not(_t_Bool_979);
    (void)_t_Bool_980;
    ;
    return _t_Bool_980;
}

Str * Bool_to_str(Bool * b) {
    (void)b;
    if (DEREF(b)) {
        Str *_t_Str_981 = Str_lit("true", 4ULL);
        (void)_t_Str_981;
        return _t_Str_981;
    } else {
        Str *_t_Str_982 = Str_lit("false", 5ULL);
        (void)_t_Str_982;
        return _t_Str_982;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_987 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_987;
    if (_t_Bool_987) {
        I64 _t_I64_983 = 0;
        (void)_t_I64_983;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_983; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_984 = 0;
        (void)_t_I64_984;
        I64 _t_I64_985 = 1;
        (void)_t_I64_985;
        I64 _t_I64_986 = I64_sub(_t_I64_984, _t_I64_985);
        (void)_t_I64_986;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_986; return _r; }
    }
    I64 _t_I64_988 = 1;
    (void)_t_I64_988;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_988; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_989 = 1;
    (void)_t_I64_989;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_989; return _r; }
}

Bool Bool_lt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_990 = 0;
    (void)_t_I64_990;
    I64 _t_I64_991 = 1;
    (void)_t_I64_991;
    I64 _t_I64_992; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_992 = *_hp; free(_hp); }
    (void)_t_I64_992;
    I64 _t_I64_993 = I64_sub(_t_I64_990, _t_I64_991);
    (void)_t_I64_993;
    ;
    ;
    Bool _t_Bool_994 = I64_eq(_t_I64_992, _t_I64_993);
    (void)_t_Bool_994;
    ;
    ;
    return _t_Bool_994;
}

Bool Bool_gt(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    I64 _t_I64_995; { I64 *_hp = (I64 *)Bool_cmp(a, b); _t_I64_995 = *_hp; free(_hp); }
    (void)_t_I64_995;
    I64 _t_I64_996 = 1;
    (void)_t_I64_996;
    Bool _t_Bool_997 = I64_eq(_t_I64_995, _t_I64_996);
    (void)_t_Bool_997;
    ;
    ;
    return _t_Bool_997;
}

Bool Bool_neq(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_998 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_998;
    Bool _t_Bool_999 = not(_t_Bool_998);
    (void)_t_Bool_999;
    ;
    return _t_Bool_999;
}

Bool Bool_lte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1000 = Bool_gt(a, b);
    (void)_t_Bool_1000;
    Bool _t_Bool_1001 = not(_t_Bool_1000);
    (void)_t_Bool_1001;
    ;
    return _t_Bool_1001;
}

Bool Bool_gte(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1002 = Bool_lt(a, b);
    (void)_t_Bool_1002;
    Bool _t_Bool_1003 = not(_t_Bool_1002);
    (void)_t_Bool_1003;
    ;
    return _t_Bool_1003;
}

Type *Type_Unknown() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Unknown;
    return r;
}
Type *Type_None() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_None;
    return r;
}
Type *Type_I64() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_I64;
    return r;
}
Type *Type_U8() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_U8;
    return r;
}
Type *Type_I16() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_I16;
    return r;
}
Type *Type_I32() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_I32;
    return r;
}
Type *Type_U32() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_U32;
    return r;
}
Type *Type_U64() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_U64;
    return r;
}
Type *Type_F32() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_F32;
    return r;
}
Type *Type_Bool() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Bool;
    return r;
}
Type *Type_Struct(Str * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Struct;
    { Str * _tmp = Str_clone(val); r->data.Struct = *_tmp; free(_tmp); }
    return r;
}
Type *Type_StructDef() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_StructDef;
    return r;
}
Type *Type_Enum(Str * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Enum;
    { Str * _tmp = Str_clone(val); r->data.Enum = *_tmp; free(_tmp); }
    return r;
}
Type *Type_EnumDef() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_EnumDef;
    return r;
}
Type *Type_FuncDef() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_FuncDef;
    return r;
}
Type *Type_FuncPtr() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_FuncPtr;
    return r;
}
Type *Type_Dynamic() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Dynamic;
    return r;
}
Type *Type_Custom(Str * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Custom;
    { Str * _tmp = Str_clone(val); r->data.Custom = *_tmp; free(_tmp); }
    return r;
}
Bool Type_eq(Type * a, Type * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_1163 = Type_is(a, &(Type){.tag = Type_TAG_Custom});
    (void)_t_Bool_1163;
    Bool _t_Bool_1164 = Type_is(a, &(Type){.tag = Type_TAG_Struct});
    (void)_t_Bool_1164;
    Bool _t_Bool_1165 = or(_t_Bool_1163, _t_Bool_1164);
    (void)_t_Bool_1165;
    ;
    ;
    Bool _t_Bool_1166 = Type_is(a, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1166;
    Bool a_named = or(_t_Bool_1165, _t_Bool_1166);
    (void)a_named;
    ;
    ;
    Bool _t_Bool_1167 = Type_is(b, &(Type){.tag = Type_TAG_Custom});
    (void)_t_Bool_1167;
    Bool _t_Bool_1168 = Type_is(b, &(Type){.tag = Type_TAG_Struct});
    (void)_t_Bool_1168;
    Bool _t_Bool_1169 = or(_t_Bool_1167, _t_Bool_1168);
    (void)_t_Bool_1169;
    ;
    ;
    Bool _t_Bool_1170 = Type_is(b, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1170;
    Bool b_named = or(_t_Bool_1169, _t_Bool_1170);
    (void)b_named;
    ;
    ;
    Bool _t_Bool_1171 = and(a_named, b_named);
    (void)_t_Bool_1171;
    if (_t_Bool_1171) {
        Str *an = get_payload(a);
        (void)an;
        Str *bn = get_payload(b);
        (void)bn;
        Bool _t_Bool_1146 = Str_eq(an, bn);
        (void)_t_Bool_1146;
        ;
        ;
        ;
        return _t_Bool_1146;
    }
    ;
    Bool _t_Bool_1172 = or(a_named, b_named);
    (void)_t_Bool_1172;
    ;
    ;
    if (_t_Bool_1172) {
        Bool _t_Bool_1147 = 0;
        (void)_t_Bool_1147;
        ;
        return _t_Bool_1147;
    }
    ;
    Bool _t_Bool_1173 = Type_is(a, &(Type){.tag = Type_TAG_Unknown});
    (void)_t_Bool_1173;
    if (_t_Bool_1173) {
        Bool _t_Bool_1148 = Type_is(b, &(Type){.tag = Type_TAG_Unknown});
        (void)_t_Bool_1148;
        ;
        return _t_Bool_1148;
    }
    ;
    Bool _t_Bool_1174 = Type_is(a, &(Type){.tag = Type_TAG_None});
    (void)_t_Bool_1174;
    if (_t_Bool_1174) {
        Bool _t_Bool_1149 = Type_is(b, &(Type){.tag = Type_TAG_None});
        (void)_t_Bool_1149;
        ;
        return _t_Bool_1149;
    }
    ;
    Bool _t_Bool_1175 = Type_is(a, &(Type){.tag = Type_TAG_I64});
    (void)_t_Bool_1175;
    if (_t_Bool_1175) {
        Bool _t_Bool_1150 = Type_is(b, &(Type){.tag = Type_TAG_I64});
        (void)_t_Bool_1150;
        ;
        return _t_Bool_1150;
    }
    ;
    Bool _t_Bool_1176 = Type_is(a, &(Type){.tag = Type_TAG_U8});
    (void)_t_Bool_1176;
    if (_t_Bool_1176) {
        Bool _t_Bool_1151 = Type_is(b, &(Type){.tag = Type_TAG_U8});
        (void)_t_Bool_1151;
        ;
        return _t_Bool_1151;
    }
    ;
    Bool _t_Bool_1177 = Type_is(a, &(Type){.tag = Type_TAG_I16});
    (void)_t_Bool_1177;
    if (_t_Bool_1177) {
        Bool _t_Bool_1152 = Type_is(b, &(Type){.tag = Type_TAG_I16});
        (void)_t_Bool_1152;
        ;
        return _t_Bool_1152;
    }
    ;
    Bool _t_Bool_1178 = Type_is(a, &(Type){.tag = Type_TAG_I32});
    (void)_t_Bool_1178;
    if (_t_Bool_1178) {
        Bool _t_Bool_1153 = Type_is(b, &(Type){.tag = Type_TAG_I32});
        (void)_t_Bool_1153;
        ;
        return _t_Bool_1153;
    }
    ;
    Bool _t_Bool_1179 = Type_is(a, &(Type){.tag = Type_TAG_U32});
    (void)_t_Bool_1179;
    if (_t_Bool_1179) {
        Bool _t_Bool_1154 = Type_is(b, &(Type){.tag = Type_TAG_U32});
        (void)_t_Bool_1154;
        ;
        return _t_Bool_1154;
    }
    ;
    Bool _t_Bool_1180 = Type_is(a, &(Type){.tag = Type_TAG_U64});
    (void)_t_Bool_1180;
    if (_t_Bool_1180) {
        Bool _t_Bool_1155 = Type_is(b, &(Type){.tag = Type_TAG_U64});
        (void)_t_Bool_1155;
        ;
        return _t_Bool_1155;
    }
    ;
    Bool _t_Bool_1181 = Type_is(a, &(Type){.tag = Type_TAG_F32});
    (void)_t_Bool_1181;
    if (_t_Bool_1181) {
        Bool _t_Bool_1156 = Type_is(b, &(Type){.tag = Type_TAG_F32});
        (void)_t_Bool_1156;
        ;
        return _t_Bool_1156;
    }
    ;
    Bool _t_Bool_1182 = Type_is(a, &(Type){.tag = Type_TAG_Bool});
    (void)_t_Bool_1182;
    if (_t_Bool_1182) {
        Bool _t_Bool_1157 = Type_is(b, &(Type){.tag = Type_TAG_Bool});
        (void)_t_Bool_1157;
        ;
        return _t_Bool_1157;
    }
    ;
    Bool _t_Bool_1183 = Type_is(a, &(Type){.tag = Type_TAG_StructDef});
    (void)_t_Bool_1183;
    if (_t_Bool_1183) {
        Bool _t_Bool_1158 = Type_is(b, &(Type){.tag = Type_TAG_StructDef});
        (void)_t_Bool_1158;
        ;
        return _t_Bool_1158;
    }
    ;
    Bool _t_Bool_1184 = Type_is(a, &(Type){.tag = Type_TAG_EnumDef});
    (void)_t_Bool_1184;
    if (_t_Bool_1184) {
        Bool _t_Bool_1159 = Type_is(b, &(Type){.tag = Type_TAG_EnumDef});
        (void)_t_Bool_1159;
        ;
        return _t_Bool_1159;
    }
    ;
    Bool _t_Bool_1185 = Type_is(a, &(Type){.tag = Type_TAG_FuncDef});
    (void)_t_Bool_1185;
    if (_t_Bool_1185) {
        Bool _t_Bool_1160 = Type_is(b, &(Type){.tag = Type_TAG_FuncDef});
        (void)_t_Bool_1160;
        ;
        return _t_Bool_1160;
    }
    ;
    Bool _t_Bool_1186 = Type_is(a, &(Type){.tag = Type_TAG_FuncPtr});
    (void)_t_Bool_1186;
    if (_t_Bool_1186) {
        Bool _t_Bool_1161 = Type_is(b, &(Type){.tag = Type_TAG_FuncPtr});
        (void)_t_Bool_1161;
        ;
        return _t_Bool_1161;
    }
    ;
    Bool _t_Bool_1187 = Type_is(a, &(Type){.tag = Type_TAG_Dynamic});
    (void)_t_Bool_1187;
    if (_t_Bool_1187) {
        Bool _t_Bool_1162 = Type_is(b, &(Type){.tag = Type_TAG_Dynamic});
        (void)_t_Bool_1162;
        ;
        return _t_Bool_1162;
    }
    ;
    Bool _t_Bool_1188 = 0;
    (void)_t_Bool_1188;
    return _t_Bool_1188;
}

Bool Type_is(Type * self, Type * other) {
    (void)self;
    (void)other;
    Bool _t_Bool_1189 = is(self, other);
    (void)_t_Bool_1189;
    return _t_Bool_1189;
}

void Type_delete(Type * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_1196 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)_t_Bool_1196;
    if (_t_Bool_1196) {
        Str *_t_Str_1190 = get_payload(self);
        (void)_t_Str_1190;
        Bool _t_Bool_1191 = 0;
        (void)_t_Bool_1191;
        Str_delete(_t_Str_1190, &_t_Bool_1191);
        ;
    }
    ;
    Bool _t_Bool_1197 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1197;
    if (_t_Bool_1197) {
        Str *_t_Str_1192 = get_payload(self);
        (void)_t_Str_1192;
        Bool _t_Bool_1193 = 0;
        (void)_t_Bool_1193;
        Str_delete(_t_Str_1192, &_t_Bool_1193);
        ;
    }
    ;
    Bool _t_Bool_1198 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)_t_Bool_1198;
    if (_t_Bool_1198) {
        Str *_t_Str_1194 = get_payload(self);
        (void)_t_Str_1194;
        Bool _t_Bool_1195 = 0;
        (void)_t_Bool_1195;
        Str_delete(_t_Str_1194, &_t_Bool_1195);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Type_to_str(Type * self) {
    (void)self;
    Bool _t_Bool_1244 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)_t_Bool_1244;
    if (_t_Bool_1244) {
        Str *_t_Str_1199 = Str_lit("Unknown", 7ULL);
        (void)_t_Str_1199;
        ;
        return _t_Str_1199;
    }
    ;
    Bool _t_Bool_1245 = is(self, &(Type){.tag = Type_TAG_None});
    (void)_t_Bool_1245;
    if (_t_Bool_1245) {
        Str *_t_Str_1200 = Str_lit("None", 4ULL);
        (void)_t_Str_1200;
        ;
        return _t_Str_1200;
    }
    ;
    Bool _t_Bool_1246 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)_t_Bool_1246;
    if (_t_Bool_1246) {
        Str *_t_Str_1201 = Str_lit("I64", 3ULL);
        (void)_t_Str_1201;
        ;
        return _t_Str_1201;
    }
    ;
    Bool _t_Bool_1247 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)_t_Bool_1247;
    if (_t_Bool_1247) {
        Str *_t_Str_1202 = Str_lit("U8", 2ULL);
        (void)_t_Str_1202;
        ;
        return _t_Str_1202;
    }
    ;
    Bool _t_Bool_1248 = is(self, &(Type){.tag = Type_TAG_I16});
    (void)_t_Bool_1248;
    if (_t_Bool_1248) {
        Str *_t_Str_1203 = Str_lit("I16", 3ULL);
        (void)_t_Str_1203;
        ;
        return _t_Str_1203;
    }
    ;
    Bool _t_Bool_1249 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)_t_Bool_1249;
    if (_t_Bool_1249) {
        Str *_t_Str_1204 = Str_lit("I32", 3ULL);
        (void)_t_Str_1204;
        ;
        return _t_Str_1204;
    }
    ;
    Bool _t_Bool_1250 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)_t_Bool_1250;
    if (_t_Bool_1250) {
        Str *_t_Str_1205 = Str_lit("U32", 3ULL);
        (void)_t_Str_1205;
        ;
        return _t_Str_1205;
    }
    ;
    Bool _t_Bool_1251 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)_t_Bool_1251;
    if (_t_Bool_1251) {
        Str *_t_Str_1206 = Str_lit("U64", 3ULL);
        (void)_t_Str_1206;
        ;
        return _t_Str_1206;
    }
    ;
    Bool _t_Bool_1252 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)_t_Bool_1252;
    if (_t_Bool_1252) {
        Str *_t_Str_1207 = Str_lit("F32", 3ULL);
        (void)_t_Str_1207;
        ;
        return _t_Str_1207;
    }
    ;
    Bool _t_Bool_1253 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)_t_Bool_1253;
    if (_t_Bool_1253) {
        Str *_t_Str_1208 = Str_lit("Bool", 4ULL);
        (void)_t_Str_1208;
        ;
        return _t_Str_1208;
    }
    ;
    Bool _t_Bool_1254 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)_t_Bool_1254;
    if (_t_Bool_1254) {
        Str *_p_Str_10 = get_payload(self);
        (void)_p_Str_10;
        Str *_t_Str_1209 = Str_lit("Str", 3ULL);
        (void)_t_Str_1209;
        Type *_t_Type_1210 = Type_Struct(_t_Str_1209);
        (void)_t_Type_1210;
        Str_delete(_t_Str_1209, &(Bool){1});
        U32 _t_U32_1211 = 3;
        (void)_t_U32_1211;
        Array *_va_Array_20 = Array_new(_t_Type_1210, &_t_U32_1211);
        (void)_va_Array_20;
        Type_delete(_t_Type_1210, &(Bool){1});
        ;
        U32 _t_U32_1212 = 0;
        (void)_t_U32_1212;
        Str *_t_Str_1213 = Str_lit("Struct(", 7ULL);
        (void)_t_Str_1213;
        Array_set(_va_Array_20, &_t_U32_1212, _t_Str_1213);
        ;
        U32 _t_U32_1214 = 1;
        (void)_t_U32_1214;
        Str *_t_Str_1215 = Str_to_str(_p_Str_10);
        (void)_t_Str_1215;
        Array_set(_va_Array_20, &_t_U32_1214, _t_Str_1215);
        ;
        U32 _t_U32_1216 = 2;
        (void)_t_U32_1216;
        Str *_t_Str_1217 = Str_lit(")", 1ULL);
        (void)_t_Str_1217;
        Array_set(_va_Array_20, &_t_U32_1216, _t_Str_1217);
        ;
        Str *_t_Str_1218 = format(_va_Array_20);
        (void)_t_Str_1218;
        ;
        return _t_Str_1218;
    }
    ;
    Bool _t_Bool_1255 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)_t_Bool_1255;
    if (_t_Bool_1255) {
        Str *_t_Str_1219 = Str_lit("StructDef", 9ULL);
        (void)_t_Str_1219;
        ;
        return _t_Str_1219;
    }
    ;
    Bool _t_Bool_1256 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1256;
    if (_t_Bool_1256) {
        Str *_p_Str_12 = get_payload(self);
        (void)_p_Str_12;
        Str *_t_Str_1220 = Str_lit("Str", 3ULL);
        (void)_t_Str_1220;
        Type *_t_Type_1221 = Type_Struct(_t_Str_1220);
        (void)_t_Type_1221;
        Str_delete(_t_Str_1220, &(Bool){1});
        U32 _t_U32_1222 = 3;
        (void)_t_U32_1222;
        Array *_va_Array_21 = Array_new(_t_Type_1221, &_t_U32_1222);
        (void)_va_Array_21;
        Type_delete(_t_Type_1221, &(Bool){1});
        ;
        U32 _t_U32_1223 = 0;
        (void)_t_U32_1223;
        Str *_t_Str_1224 = Str_lit("Enum(", 5ULL);
        (void)_t_Str_1224;
        Array_set(_va_Array_21, &_t_U32_1223, _t_Str_1224);
        ;
        U32 _t_U32_1225 = 1;
        (void)_t_U32_1225;
        Str *_t_Str_1226 = Str_to_str(_p_Str_12);
        (void)_t_Str_1226;
        Array_set(_va_Array_21, &_t_U32_1225, _t_Str_1226);
        ;
        U32 _t_U32_1227 = 2;
        (void)_t_U32_1227;
        Str *_t_Str_1228 = Str_lit(")", 1ULL);
        (void)_t_Str_1228;
        Array_set(_va_Array_21, &_t_U32_1227, _t_Str_1228);
        ;
        Str *_t_Str_1229 = format(_va_Array_21);
        (void)_t_Str_1229;
        ;
        return _t_Str_1229;
    }
    ;
    Bool _t_Bool_1257 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)_t_Bool_1257;
    if (_t_Bool_1257) {
        Str *_t_Str_1230 = Str_lit("EnumDef", 7ULL);
        (void)_t_Str_1230;
        ;
        return _t_Str_1230;
    }
    ;
    Bool _t_Bool_1258 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)_t_Bool_1258;
    if (_t_Bool_1258) {
        Str *_t_Str_1231 = Str_lit("FuncDef", 7ULL);
        (void)_t_Str_1231;
        ;
        return _t_Str_1231;
    }
    ;
    Bool _t_Bool_1259 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)_t_Bool_1259;
    if (_t_Bool_1259) {
        Str *_t_Str_1232 = Str_lit("FuncPtr", 7ULL);
        (void)_t_Str_1232;
        ;
        return _t_Str_1232;
    }
    ;
    Bool _t_Bool_1260 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)_t_Bool_1260;
    if (_t_Bool_1260) {
        Str *_t_Str_1233 = Str_lit("Dynamic", 7ULL);
        (void)_t_Str_1233;
        ;
        return _t_Str_1233;
    }
    ;
    Bool _t_Bool_1261 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)_t_Bool_1261;
    if (_t_Bool_1261) {
        Str *_p_Str_17 = get_payload(self);
        (void)_p_Str_17;
        Str *_t_Str_1234 = Str_lit("Str", 3ULL);
        (void)_t_Str_1234;
        Type *_t_Type_1235 = Type_Struct(_t_Str_1234);
        (void)_t_Type_1235;
        Str_delete(_t_Str_1234, &(Bool){1});
        U32 _t_U32_1236 = 3;
        (void)_t_U32_1236;
        Array *_va_Array_22 = Array_new(_t_Type_1235, &_t_U32_1236);
        (void)_va_Array_22;
        Type_delete(_t_Type_1235, &(Bool){1});
        ;
        U32 _t_U32_1237 = 0;
        (void)_t_U32_1237;
        Str *_t_Str_1238 = Str_lit("Custom(", 7ULL);
        (void)_t_Str_1238;
        Array_set(_va_Array_22, &_t_U32_1237, _t_Str_1238);
        ;
        U32 _t_U32_1239 = 1;
        (void)_t_U32_1239;
        Str *_t_Str_1240 = Str_to_str(_p_Str_17);
        (void)_t_Str_1240;
        Array_set(_va_Array_22, &_t_U32_1239, _t_Str_1240);
        ;
        U32 _t_U32_1241 = 2;
        (void)_t_U32_1241;
        Str *_t_Str_1242 = Str_lit(")", 1ULL);
        (void)_t_Str_1242;
        Array_set(_va_Array_22, &_t_U32_1241, _t_Str_1242);
        ;
        Str *_t_Str_1243 = format(_va_Array_22);
        (void)_t_Str_1243;
        ;
        return _t_Str_1243;
    }
    ;
    Str *_t_Str_1262 = Str_lit("unknown", 7ULL);
    (void)_t_Str_1262;
    return _t_Str_1262;
}

Type * Type_clone(Type * self) {
    (void)self;
    Bool _t_Bool_1265 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)_t_Bool_1265;
    if (_t_Bool_1265) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown; return _r; }
    }
    ;
    Bool _t_Bool_1266 = is(self, &(Type){.tag = Type_TAG_None});
    (void)_t_Bool_1266;
    if (_t_Bool_1266) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None; return _r; }
    }
    ;
    Bool _t_Bool_1267 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)_t_Bool_1267;
    if (_t_Bool_1267) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64; return _r; }
    }
    ;
    Bool _t_Bool_1268 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)_t_Bool_1268;
    if (_t_Bool_1268) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8; return _r; }
    }
    ;
    Bool _t_Bool_1269 = is(self, &(Type){.tag = Type_TAG_I16});
    (void)_t_Bool_1269;
    if (_t_Bool_1269) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I16; return _r; }
    }
    ;
    Bool _t_Bool_1270 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)_t_Bool_1270;
    if (_t_Bool_1270) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32; return _r; }
    }
    ;
    Bool _t_Bool_1271 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)_t_Bool_1271;
    if (_t_Bool_1271) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32; return _r; }
    }
    ;
    Bool _t_Bool_1272 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)_t_Bool_1272;
    if (_t_Bool_1272) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64; return _r; }
    }
    ;
    Bool _t_Bool_1273 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)_t_Bool_1273;
    if (_t_Bool_1273) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32; return _r; }
    }
    ;
    Bool _t_Bool_1274 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)_t_Bool_1274;
    if (_t_Bool_1274) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool; return _r; }
    }
    ;
    Bool _t_Bool_1275 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)_t_Bool_1275;
    if (_t_Bool_1275) {
        Str *_clone_payload_Struct_10 = get_payload(self);
        (void)_clone_payload_Struct_10;
        Type *_t_Type_1263 = Type_Struct(_clone_payload_Struct_10);
        (void)_t_Type_1263;
        ;
        return _t_Type_1263;
    }
    ;
    Bool _t_Bool_1276 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)_t_Bool_1276;
    if (_t_Bool_1276) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef; return _r; }
    }
    ;
    Bool _t_Bool_1277 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1277;
    if (_t_Bool_1277) {
        Str *_clone_payload_Enum_12 = get_payload(self);
        (void)_clone_payload_Enum_12;
        Type *_t_Type_1264 = Type_Enum(_clone_payload_Enum_12);
        (void)_t_Type_1264;
        ;
        return _t_Type_1264;
    }
    ;
    Bool _t_Bool_1278 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)_t_Bool_1278;
    if (_t_Bool_1278) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef; return _r; }
    }
    ;
    Bool _t_Bool_1279 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)_t_Bool_1279;
    if (_t_Bool_1279) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef; return _r; }
    }
    ;
    Bool _t_Bool_1280 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)_t_Bool_1280;
    if (_t_Bool_1280) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr; return _r; }
    }
    ;
    Bool _t_Bool_1281 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)_t_Bool_1281;
    if (_t_Bool_1281) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic; return _r; }
    }
    ;
    Str *_clone_payload_Custom_17 = get_payload(self);
    (void)_clone_payload_Custom_17;
    Type *_t_Type_1282 = Type_Custom(_clone_payload_Custom_17);
    (void)_t_Type_1282;
    return _t_Type_1282;
}

U32 Type_size(void) {
    I64 _t_I64_1283 = 24;
    (void)_t_I64_1283;
    return _t_I64_1283;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    (void)elem_type;
    (void)cap;
    Bool _t_Bool_2406 = Str_is_empty(elem_type);
    (void)_t_Bool_2406;
    if (_t_Bool_2406) {
        Str *_t_Str_2400 = Str_lit("Str", 3ULL);
        (void)_t_Str_2400;
        Type *_t_Type_2401 = Type_Struct(_t_Str_2400);
        (void)_t_Type_2401;
        Str_delete(_t_Str_2400, &(Bool){1});
        U32 _t_U32_2402 = 1;
        (void)_t_U32_2402;
        Array *_va_Array_73 = Array_new(_t_Type_2401, &_t_U32_2402);
        (void)_va_Array_73;
        Type_delete(_t_Type_2401, &(Bool){1});
        ;
        U32 _t_U32_2403 = 0;
        (void)_t_U32_2403;
        Str *_t_Str_2404 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_2404;
        Array_set(_va_Array_73, &_t_U32_2403, _t_Str_2404);
        ;
        Str *_t_Str_2405 = Str_lit("./src/core/array.til:23:41", 26ULL);
        (void)_t_Str_2405;
        panic(_t_Str_2405, _va_Array_73);
        Str_delete(_t_Str_2405, &(Bool){1});
    }
    ;
    U32 elem_size = dyn_size_of(elem_type);
    (void)elem_size;
    void * _t_v_2407 = calloc(DEREF(cap), elem_size);
    (void)_t_v_2407;
    void * _t_v_2408 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2408;
    void * _t_v_2409 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2409;
    Array *_t_Array_2410 = malloc(sizeof(Array));
    _t_Array_2410->data = _t_v_2407;
    _t_Array_2410->cap = DEREF(cap);
    _t_Array_2410->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); _t_Array_2410->elem_type = *_ca; free(_ca); }
    _t_Array_2410->elem_clone = _t_v_2408;
    _t_Array_2410->elem_delete = _t_v_2409;
    (void)_t_Array_2410;
    ;
    return _t_Array_2410;
}

Array * Array_new(Type * T, U32 * cap) {
    (void)T;
    (void)cap;
    Str *elem_type = dyn_type_to_str(T);
    (void)elem_type;
    Array *_t_Array_2411 = Array_new_type_name(elem_type, cap);
    (void)_t_Array_2411;
    Str_delete(elem_type, &(Bool){1});
    return _t_Array_2411;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_2426 = U32_gte(i, &self->cap);
    (void)_t_Bool_2426;
    if (_t_Bool_2426) {
        Str *_t_Str_2412 = Str_lit("Str", 3ULL);
        (void)_t_Str_2412;
        Type *_t_Type_2413 = Type_Struct(_t_Str_2412);
        (void)_t_Type_2413;
        Str_delete(_t_Str_2412, &(Bool){1});
        U32 _t_U32_2414 = 5;
        (void)_t_U32_2414;
        Array *_va_Array_74 = Array_new(_t_Type_2413, &_t_U32_2414);
        (void)_va_Array_74;
        Type_delete(_t_Type_2413, &(Bool){1});
        ;
        U32 _t_U32_2415 = 0;
        (void)_t_U32_2415;
        Str *_t_Str_2416 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_2416;
        Array_set(_va_Array_74, &_t_U32_2415, _t_Str_2416);
        ;
        U32 _t_U32_2417 = 1;
        (void)_t_U32_2417;
        Str *_t_Str_2418 = U32_to_str(i);
        (void)_t_Str_2418;
        Array_set(_va_Array_74, &_t_U32_2417, _t_Str_2418);
        ;
        U32 _t_U32_2419 = 2;
        (void)_t_U32_2419;
        Str *_t_Str_2420 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2420;
        Array_set(_va_Array_74, &_t_U32_2419, _t_Str_2420);
        ;
        U32 _t_U32_2421 = 3;
        (void)_t_U32_2421;
        Str *_t_Str_2422 = U32_to_str(&self->cap);
        (void)_t_Str_2422;
        Array_set(_va_Array_74, &_t_U32_2421, _t_Str_2422);
        ;
        U32 _t_U32_2423 = 4;
        (void)_t_U32_2423;
        Str *_t_Str_2424 = Str_lit(")", 1ULL);
        (void)_t_Str_2424;
        Array_set(_va_Array_74, &_t_U32_2423, _t_Str_2424);
        ;
        Str *_t_Str_2425 = Str_lit("./src/core/array.til:41:19", 26ULL);
        (void)_t_Str_2425;
        panic(_t_Str_2425, _va_Array_74);
        Str_delete(_t_Str_2425, &(Bool){1});
    }
    ;
    U32 _t_U64_2427 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2427;
    void *_t_v_2428 = ptr_add(self->data, _t_U64_2427);
    (void)_t_v_2428;
    ;
    return _t_v_2428;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_2443 = U32_gte(i, &self->cap);
    (void)_t_Bool_2443;
    if (_t_Bool_2443) {
        Str *_t_Str_2429 = Str_lit("Str", 3ULL);
        (void)_t_Str_2429;
        Type *_t_Type_2430 = Type_Struct(_t_Str_2429);
        (void)_t_Type_2430;
        Str_delete(_t_Str_2429, &(Bool){1});
        U32 _t_U32_2431 = 5;
        (void)_t_U32_2431;
        Array *_va_Array_75 = Array_new(_t_Type_2430, &_t_U32_2431);
        (void)_va_Array_75;
        Type_delete(_t_Type_2430, &(Bool){1});
        ;
        U32 _t_U32_2432 = 0;
        (void)_t_U32_2432;
        Str *_t_Str_2433 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_2433;
        Array_set(_va_Array_75, &_t_U32_2432, _t_Str_2433);
        ;
        U32 _t_U32_2434 = 1;
        (void)_t_U32_2434;
        Str *_t_Str_2435 = U32_to_str(i);
        (void)_t_Str_2435;
        Array_set(_va_Array_75, &_t_U32_2434, _t_Str_2435);
        ;
        U32 _t_U32_2436 = 2;
        (void)_t_U32_2436;
        Str *_t_Str_2437 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2437;
        Array_set(_va_Array_75, &_t_U32_2436, _t_Str_2437);
        ;
        U32 _t_U32_2438 = 3;
        (void)_t_U32_2438;
        Str *_t_Str_2439 = U32_to_str(&self->cap);
        (void)_t_Str_2439;
        Array_set(_va_Array_75, &_t_U32_2438, _t_Str_2439);
        ;
        U32 _t_U32_2440 = 4;
        (void)_t_U32_2440;
        Str *_t_Str_2441 = Str_lit(")", 1ULL);
        (void)_t_Str_2441;
        Array_set(_va_Array_75, &_t_U32_2440, _t_Str_2441);
        ;
        Str *_t_Str_2442 = Str_lit("./src/core/array.til:50:19", 26ULL);
        (void)_t_Str_2442;
        panic(_t_Str_2442, _va_Array_75);
        Str_delete(_t_Str_2442, &(Bool){1});
    }
    ;
    U32 _t_U64_2444 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2444;
    void *_t_v_2445 = ptr_add(self->data, _t_U64_2444);
    (void)_t_v_2445;
    Bool _t_Bool_2446 = 0;
    (void)_t_Bool_2446;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2445, &_t_Bool_2446);
    ;
    ;
    U32 _t_U64_2447 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2447;
    void *_t_v_2448 = ptr_add(self->data, _t_U64_2447);
    (void)_t_v_2448;
    memcpy(_t_v_2448, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_2449 = self->cap;
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
                U32 i = U32_clone(&_rc_U32_2449);
                (void)i;
                U32_inc(&_rc_U32_2449);
                U32 _t_U64_2451 = U32_mul(i, self->elem_size);
                (void)_t_U64_2451;
                ;
                void *_t_v_2452 = ptr_add(self->data, _t_U64_2451);
                (void)_t_v_2452;
                Bool _t_Bool_2453 = 0;
                (void)_t_Bool_2453;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2452, &_t_Bool_2453);
                ;
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
                U32 i = U32_clone(&_rc_U32_2449);
                (void)i;
                U32_dec(&_rc_U32_2449);
                U32 _t_U64_2455 = U32_mul(i, self->elem_size);
                (void)_t_U64_2455;
                ;
                void *_t_v_2456 = ptr_add(self->data, _t_U64_2455);
                (void)_t_v_2456;
                Bool _t_Bool_2457 = 0;
                (void)_t_Bool_2457;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2456, &_t_Bool_2457);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_2459 = 0;
    (void)_t_Bool_2459;
    Str_delete(&self->elem_type, &_t_Bool_2459);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_2472 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_2472;
    void * new_data = malloc(_t_U64_2472);
    (void)new_data;
    ;
    {
        U32 _re_U32_2460 = self->cap;
        (void)_re_U32_2460;
        U32 _rc_U32_2460 = 0;
        (void)_rc_U32_2460;
        Bool _t_Bool_2471 = U32_lte(&_rc_U32_2460, &_re_U32_2460);
        (void)_t_Bool_2471;
        if (_t_Bool_2471) {
            while (1) {
                Bool _wcond_Bool_2461 = U32_lt(&_rc_U32_2460, &_re_U32_2460);
                (void)_wcond_Bool_2461;
                if (_wcond_Bool_2461) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2460);
                (void)i;
                U32_inc(&_rc_U32_2460);
                U32 _t_U64_2462 = U32_mul(i, self->elem_size);
                (void)_t_U64_2462;
                void *_t_v_2463 = ptr_add(self->data, _t_U64_2462);
                (void)_t_v_2463;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2463);
                (void)cloned;
                ;
                U32 _t_U64_2464 = U32_mul(i, self->elem_size);
                (void)_t_U64_2464;
                ;
                void *_t_v_2465 = ptr_add(new_data, _t_U64_2464);
                (void)_t_v_2465;
                memcpy(_t_v_2465, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2466 = U32_gt(&_rc_U32_2460, &_re_U32_2460);
                (void)_wcond_Bool_2466;
                if (_wcond_Bool_2466) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2460);
                (void)i;
                U32_dec(&_rc_U32_2460);
                U32 _t_U64_2467 = U32_mul(i, self->elem_size);
                (void)_t_U64_2467;
                void *_t_v_2468 = ptr_add(self->data, _t_U64_2467);
                (void)_t_v_2468;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2468);
                (void)cloned;
                ;
                U32 _t_U64_2469 = U32_mul(i, self->elem_size);
                (void)_t_U64_2469;
                ;
                void *_t_v_2470 = ptr_add(new_data, _t_U64_2469);
                (void)_t_v_2470;
                memcpy(_t_v_2470, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_2473 = malloc(sizeof(Array));
    _t_Array_2473->data = new_data;
    _t_Array_2473->cap = self->cap;
    _t_Array_2473->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_2473->elem_type = *_ca; free(_ca); }
    _t_Array_2473->elem_clone = (void *)self->elem_clone;
    _t_Array_2473->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_2473;
    return _t_Array_2473;
}

U32 Array_size(void) {
    I64 _t_I64_2474 = 48;
    (void)_t_I64_2474;
    return _t_I64_2474;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2713 = Str_lit("Str", 3ULL);
    (void)_t_Str_2713;
    Type *_t_Type_2714 = Type_Struct(_t_Str_2713);
    (void)_t_Type_2714;
    Str_delete(_t_Str_2713, &(Bool){1});
    U32 _t_U32_2715 = 3;
    (void)_t_U32_2715;
    Array *_va_Array_92 = Array_new(_t_Type_2714, &_t_U32_2715);
    (void)_va_Array_92;
    Type_delete(_t_Type_2714, &(Bool){1});
    ;
    U32 _t_U32_2716 = 0;
    (void)_t_U32_2716;
    Str *_t_Str_2717 = Str_clone(loc_str);
    (void)_t_Str_2717;
    Array_set(_va_Array_92, &_t_U32_2716, _t_Str_2717);
    ;
    U32 _t_U32_2718 = 1;
    (void)_t_U32_2718;
    Str *_t_Str_2719 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2719;
    Array_set(_va_Array_92, &_t_U32_2718, _t_Str_2719);
    ;
    Array *_t_Array_2720 = Array_clone(parts);
    (void)_t_Array_2720;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2721 = 2;
    (void)_t_U32_2721;
    Str *_t_Str_2722 = format(_t_Array_2720);
    (void)_t_Str_2722;
    Array_set(_va_Array_92, &_t_U32_2721, _t_Str_2722);
    ;
    println(_va_Array_92);
    I64 _t_I64_2723 = 1;
    (void)_t_I64_2723;
    exit(_t_I64_2723);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2742 = not(DEREF(cond));
    (void)_t_Bool_2742;
    if (_t_Bool_2742) {
        Str *_t_Str_2737 = Str_lit("Str", 3ULL);
        (void)_t_Str_2737;
        Type *_t_Type_2738 = Type_Struct(_t_Str_2737);
        (void)_t_Type_2738;
        Str_delete(_t_Str_2737, &(Bool){1});
        U32 _t_U32_2739 = 1;
        (void)_t_U32_2739;
        Array *_va_Array_95 = Array_new(_t_Type_2738, &_t_U32_2739);
        (void)_va_Array_95;
        Type_delete(_t_Type_2738, &(Bool){1});
        ;
        U32 _t_U32_2740 = 0;
        (void)_t_U32_2740;
        Str *_t_Str_2741 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2741;
        Array_set(_va_Array_95, &_t_U32_2740, _t_Str_2741);
        ;
        panic(loc_str, _va_Array_95);
    }
    ;
    Bool _t_Bool_2743 = 1;
    (void)_t_Bool_2743;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2743; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2766 = I64_neq(a, b);
    (void)_t_Bool_2766;
    if (_t_Bool_2766) {
        Str *_t_Str_2753 = Str_lit("Str", 3ULL);
        (void)_t_Str_2753;
        Type *_t_Type_2754 = Type_Struct(_t_Str_2753);
        (void)_t_Type_2754;
        Str_delete(_t_Str_2753, &(Bool){1});
        U32 _t_U32_2755 = 5;
        (void)_t_U32_2755;
        Array *_va_Array_97 = Array_new(_t_Type_2754, &_t_U32_2755);
        (void)_va_Array_97;
        Type_delete(_t_Type_2754, &(Bool){1});
        ;
        U32 _t_U32_2756 = 0;
        (void)_t_U32_2756;
        Str *_t_Str_2757 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2757;
        Array_set(_va_Array_97, &_t_U32_2756, _t_Str_2757);
        ;
        U32 _t_U32_2758 = 1;
        (void)_t_U32_2758;
        Str *_t_Str_2759 = I64_to_str(a);
        (void)_t_Str_2759;
        Array_set(_va_Array_97, &_t_U32_2758, _t_Str_2759);
        ;
        U32 _t_U32_2760 = 2;
        (void)_t_U32_2760;
        Str *_t_Str_2761 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2761;
        Array_set(_va_Array_97, &_t_U32_2760, _t_Str_2761);
        ;
        U32 _t_U32_2762 = 3;
        (void)_t_U32_2762;
        Str *_t_Str_2763 = I64_to_str(b);
        (void)_t_Str_2763;
        Array_set(_va_Array_97, &_t_U32_2762, _t_Str_2763);
        ;
        U32 _t_U32_2764 = 4;
        (void)_t_U32_2764;
        Str *_t_Str_2765 = Str_lit("'", 1ULL);
        (void)_t_Str_2765;
        Array_set(_va_Array_97, &_t_U32_2764, _t_Str_2765);
        ;
        panic(loc_str, _va_Array_97);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2782 = parts;
        (void)_fc_Array_2782;
        U32 _fi_USize_2782 = 0;
        (void)_fi_USize_2782;
        while (1) {
            U32 _t_U32_2784; { U32 *_hp = (U32 *)Array_len(_fc_Array_2782); _t_U32_2784 = *_hp; free(_hp); }
            (void)_t_U32_2784;
            Bool _wcond_Bool_2783 = U32_lt(&_fi_USize_2782, &_t_U32_2784);
            (void)_wcond_Bool_2783;
            ;
            if (_wcond_Bool_2783) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2782, &_fi_USize_2782);
            (void)s;
            U32 _t_U32_2785 = 1;
            (void)_t_U32_2785;
            U32 _t_U32_2786 = U32_add(_fi_USize_2782, _t_U32_2785);
            (void)_t_U32_2786;
            ;
            _fi_USize_2782 = _t_U32_2786;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

void test_simple_add(void) {
    I64 _t_I64_2978 = 1;
    (void)_t_I64_2978;
    I64 _t_I64_2979 = 2;
    (void)_t_I64_2979;
    I64 result = 3;
    (void)result;
    ;
    ;
    Str *_t_Str_2980 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_2980;
    I64 _t_I64_2981 = 3;
    (void)_t_I64_2981;
    assert_eq(_t_Str_2980, &result, &_t_I64_2981);
    ;
    Str_delete(_t_Str_2980, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 _t_I64_2982 = 1;
    (void)_t_I64_2982;
    I64 _t_I64_2983 = 2;
    (void)_t_I64_2983;
    I64 _t_I64_2984 = 10;
    (void)_t_I64_2984;
    I64 _t_I64_2985 = 5;
    (void)_t_I64_2985;
    I64 _t_I64_2986 = 3;
    (void)_t_I64_2986;
    ;
    ;
    I64 _t_I64_2987 = 5;
    (void)_t_I64_2987;
    ;
    ;
    I64 result = 15;
    (void)result;
    ;
    ;
    Str *_t_Str_2988 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_2988;
    I64 _t_I64_2989 = 15;
    (void)_t_I64_2989;
    assert_eq(_t_Str_2988, &result, &_t_I64_2989);
    ;
    Str_delete(_t_Str_2988, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 _t_I64_2990 = 2;
    (void)_t_I64_2990;
    I64 _t_I64_2991 = 3;
    (void)_t_I64_2991;
    I64 _t_I64_2992 = 4;
    (void)_t_I64_2992;
    I64 _t_I64_2993 = 5;
    (void)_t_I64_2993;
    I64 _t_I64_2994 = 6;
    (void)_t_I64_2994;
    ;
    ;
    I64 _t_I64_2995 = 20;
    (void)_t_I64_2995;
    ;
    ;
    I64 result = 26;
    (void)result;
    ;
    ;
    Str *_t_Str_2996 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_2996;
    I64 _t_I64_2997 = 26;
    (void)_t_I64_2997;
    assert_eq(_t_Str_2996, &result, &_t_I64_2997);
    ;
    Str_delete(_t_Str_2996, &(Bool){1});
    ;
}

Str * poem(I64 * depth, Str * current, Str * s1, Str * s2) {
    (void)depth;
    (void)current;
    (void)s1;
    (void)s2;
    I64 _t_I64_3005 = 4;
    (void)_t_I64_3005;
    Bool _t_Bool_3006 = I64_eq(DEREF(depth), _t_I64_3005);
    (void)_t_Bool_3006;
    ;
    if (_t_Bool_3006) {
        Str *_t_Str_2998 = Str_lit("\n", 2ULL);
        (void)_t_Str_2998;
        Str *_t_Str_2999 = Str_concat(current, _t_Str_2998);
        (void)_t_Str_2999;
        Str_delete(_t_Str_2998, &(Bool){1});
        ;
        return _t_Str_2999;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    (void)result;
    I64 _t_I64_3007 = 1;
    (void)_t_I64_3007;
    I64 _t_I64_3008 = I64_add(DEREF(depth), _t_I64_3007);
    (void)_t_I64_3008;
    ;
    Str *_t_Str_3009 = Str_concat(current, s1);
    (void)_t_Str_3009;
    Str *_t_Str_3010 = poem(&_t_I64_3008, _t_Str_3009, s1, s2);
    (void)_t_Str_3010;
    ;
    Str_delete(_t_Str_3009, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_3010); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_3010, &(Bool){1});
    I64 _t_I64_3011 = 1;
    (void)_t_I64_3011;
    I64 _t_I64_3012 = I64_add(DEREF(depth), _t_I64_3011);
    (void)_t_I64_3012;
    ;
    Str *_t_Str_3013 = Str_concat(current, s2);
    (void)_t_Str_3013;
    Str *_t_Str_3014 = poem(&_t_I64_3012, _t_Str_3013, s1, s2);
    (void)_t_Str_3014;
    ;
    Str_delete(_t_Str_3013, &(Bool){1});
    { Str *_old = result; result = Str_concat(result, _t_Str_3014); Str_delete(_old, &(Bool){1}); }
    Str_delete(_t_Str_3014, &(Bool){1});
    I64 _t_I64_3015 = 2;
    (void)_t_I64_3015;
    Bool _t_Bool_3016 = I64_eq(DEREF(depth), _t_I64_3015);
    (void)_t_Bool_3016;
    ;
    if (_t_Bool_3016) {
        I64 _t_I64_3000 = 1;
        (void)_t_I64_3000;
        Str *_t_Str_3001 = Str_lit("lei", 3ULL);
        (void)_t_Str_3001;
        I64 _t_I64_3002 = I64_add(DEREF(depth), _t_I64_3000);
        (void)_t_I64_3002;
        ;
        Str *_t_Str_3003 = Str_concat(current, _t_Str_3001);
        (void)_t_Str_3003;
        Str_delete(_t_Str_3001, &(Bool){1});
        Str *_t_Str_3004 = poem(&_t_I64_3002, _t_Str_3003, s1, s2);
        (void)_t_Str_3004;
        ;
        Str_delete(_t_Str_3003, &(Bool){1});
        { Str *_old = result; result = Str_concat(result, _t_Str_3004); Str_delete(_old, &(Bool){1}); }
        Str_delete(_t_Str_3004, &(Bool){1});
    }
    ;
    return result;
}

Str * make_poem(Str * s1, Str * s2) {
    (void)s1;
    (void)s2;
    I64 _t_I64_3017 = 0;
    (void)_t_I64_3017;
    Str *_t_Str_3018 = Str_lit("", 0ULL);
    (void)_t_Str_3018;
    Str *_t_Str_3019 = poem(&_t_I64_3017, _t_Str_3018, s1, s2);
    (void)_t_Str_3019;
    ;
    Str_delete(_t_Str_3018, &(Bool){1});
    return _t_Str_3019;
}

void test_lolalalo(void) {
    Str *_t_Str_3020 = Str_lit("lo", 2ULL);
    (void)_t_Str_3020;
    Str *_t_Str_3021 = Str_lit("la", 2ULL);
    (void)_t_Str_3021;
    Str *lo_la = make_poem(_t_Str_3020, _t_Str_3021);
    (void)lo_la;
    Str_delete(_t_Str_3020, &(Bool){1});
    Str_delete(_t_Str_3021, &(Bool){1});
    Str *_t_Str_3022 = Str_lit("la", 2ULL);
    (void)_t_Str_3022;
    Str *_t_Str_3023 = Str_lit("lo", 2ULL);
    (void)_t_Str_3023;
    Str *la_lo = make_poem(_t_Str_3022, _t_Str_3023);
    (void)la_lo;
    Str_delete(_t_Str_3022, &(Bool){1});
    Str_delete(_t_Str_3023, &(Bool){1});
    Str *_t_Str_3024 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_3024;
    Str *_t_Str_3025 = Str_lit("src/test/constfold.til:56:12", 28ULL);
    (void)_t_Str_3025;
    Bool _t_Bool_3026 = Str_contains(lo_la, _t_Str_3024);
    (void)_t_Bool_3026;
    Str_delete(_t_Str_3024, &(Bool){1});
    Bool _t_Bool_3027; { Bool *_hp = (Bool *)assert(_t_Str_3025, &_t_Bool_3026); _t_Bool_3027 = *_hp; free(_hp); }
    (void)_t_Bool_3027;
    ;
    ;
    Str_delete(_t_Str_3025, &(Bool){1});
    Str *_t_Str_3028 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_3028;
    Str *_t_Str_3029 = Str_lit("src/test/constfold.til:57:12", 28ULL);
    (void)_t_Str_3029;
    Bool _t_Bool_3030 = Str_contains(la_lo, _t_Str_3028);
    (void)_t_Bool_3030;
    Str_delete(_t_Str_3028, &(Bool){1});
    Bool _t_Bool_3031; { Bool *_hp = (Bool *)assert(_t_Str_3029, &_t_Bool_3030); _t_Bool_3031 = *_hp; free(_hp); }
    (void)_t_Bool_3031;
    ;
    ;
    Str_delete(_t_Str_3029, &(Bool){1});
    Str *_t_Str_3032 = Str_lit("lolei", 5ULL);
    (void)_t_Str_3032;
    Str *_t_Str_3033 = Str_lit("src/test/constfold.til:59:12", 28ULL);
    (void)_t_Str_3033;
    Bool _t_Bool_3034 = Str_contains(lo_la, _t_Str_3032);
    (void)_t_Bool_3034;
    Str_delete(_t_Str_3032, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    Bool _t_Bool_3035; { Bool *_hp = (Bool *)assert(_t_Str_3033, &_t_Bool_3034); _t_Bool_3035 = *_hp; free(_hp); }
    (void)_t_Bool_3035;
    ;
    ;
    Str_delete(_t_Str_3033, &(Bool){1});
    Str *_t_Str_3036 = Str_lit("lalei", 5ULL);
    (void)_t_Str_3036;
    Str *_t_Str_3037 = Str_lit("src/test/constfold.til:60:12", 28ULL);
    (void)_t_Str_3037;
    Bool _t_Bool_3038 = Str_contains(la_lo, _t_Str_3036);
    (void)_t_Bool_3038;
    Str_delete(_t_Str_3036, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    Bool _t_Bool_3039; { Bool *_hp = (Bool *)assert(_t_Str_3037, &_t_Bool_3038); _t_Bool_3039 = *_hp; free(_hp); }
    (void)_t_Bool_3039;
    ;
    ;
    Str_delete(_t_Str_3037, &(Bool){1});
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
void *Type_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Type_eq(_a0, _a1); return _r;
}
void *Type_is_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Type_is(_a0, _a1); return _r;
}
void *Type_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Type_size(); return _r;
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
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Type_eq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Unknown", 7ULL) == 0) return (void*)Type_Unknown;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "None", 4ULL) == 0) return (void*)Type_None;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "I64", 3ULL) == 0) return (void*)Type_I64;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "U8", 2ULL) == 0) return (void*)Type_U8;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "I16", 3ULL) == 0) return (void*)Type_I16;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "I32", 3ULL) == 0) return (void*)Type_I32;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "U32", 3ULL) == 0) return (void*)Type_U32;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "U64", 3ULL) == 0) return (void*)Type_U64;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "F32", 3ULL) == 0) return (void*)Type_F32;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Bool", 4ULL) == 0) return (void*)Type_Bool;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Struct", 6ULL) == 0) return (void*)Type_Struct;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "StructDef", 9ULL) == 0) return (void*)Type_StructDef;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Enum", 4ULL) == 0) return (void*)Type_Enum;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "EnumDef", 7ULL) == 0) return (void*)Type_EnumDef;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncDef", 7ULL) == 0) return (void*)Type_FuncDef;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncPtr", 7ULL) == 0) return (void*)Type_FuncPtr;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Dynamic", 7ULL) == 0) return (void*)Type_Dynamic;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Custom", 6ULL) == 0) return (void*)Type_Custom;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "is", 2ULL) == 0) return (void*)Type_is_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Type_delete;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)Type_to_str;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Type_clone;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Type_size_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "new_type_name", 13ULL) == 0) return (void*)Array_new_type_name;
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
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) return sizeof(Type);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) return sizeof(Array);
    fprintf(stderr, "dyn_size_of: unknown type %.*s\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *dyn_type_to_str(Type *type) {
    switch (type->tag) {
    case Type_TAG_Unknown: return Str_lit("", 0ULL);
    case Type_TAG_None: return Str_lit("", 0ULL);
    case Type_TAG_I64: return Str_lit("I64", 3ULL);
    case Type_TAG_U8: return Str_lit("U8", 2ULL);
    case Type_TAG_I16: return Str_lit("I16", 3ULL);
    case Type_TAG_I32: return Str_lit("I32", 3ULL);
    case Type_TAG_U32: return Str_lit("U32", 3ULL);
    case Type_TAG_U64: return Str_lit("U64", 3ULL);
    case Type_TAG_F32: return Str_lit("F32", 3ULL);
    case Type_TAG_Bool: return Str_lit("Bool", 4ULL);
    case Type_TAG_Struct: return Str_clone(&type->data.Struct);
    case Type_TAG_StructDef: return Str_lit("StructDef", 9ULL);
    case Type_TAG_Enum: return Str_clone(&type->data.Enum);
    case Type_TAG_EnumDef: return Str_lit("EnumDef", 7ULL);
    case Type_TAG_FuncDef: return Str_lit("FunctionDef", 11ULL);
    case Type_TAG_FuncPtr: return Str_lit("Fn", 2ULL);
    case Type_TAG_Dynamic: return Str_lit("Dynamic", 7ULL);
    case Type_TAG_Custom: return Str_clone(&type->data.Custom);
    }
    return Str_lit("?", 1ULL);
}

int main(void) {
    I64 _t_I64_851 = 0;
    (void)_t_I64_851;
    I64 _t_I64_852 = 1;
    (void)_t_I64_852;
    I64 _t_I64_853 = I64_sub(_t_I64_851, _t_I64_852);
    (void)_t_I64_853;
    CAP_LIT = I64_to_usize(_t_I64_853);
    (void)CAP_LIT;
    I64 _t_I64_854 = 0;
    (void)_t_I64_854;
    I64 _t_I64_855 = 2;
    (void)_t_I64_855;
    I64 _t_I64_856 = I64_sub(_t_I64_854, _t_I64_855);
    (void)_t_I64_856;
    CAP_VIEW = I64_to_usize(_t_I64_856);
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
