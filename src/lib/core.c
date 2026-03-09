#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "ext.h"

typedef struct Map Map;
typedef struct Set Set;
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

Bool Bool_and(Bool, Bool);
Bool Bool_or(Bool, Bool);
Bool Bool_not(Bool);
void print_single(Str *);
void print_flush(void);
void exit(I64);
void free(void *);
Bool is_null(void *);
void * malloc(I64);
void * calloc(I64, I64);
void * realloc(void *, I64);
void * ptr_add(void *, I64);
void memcpy(void *, void *, I64);
void memmove(void *, void *, I64);
void dyn_call1(Str *, Str *, void *);
void dyn_call2(Str *, Str *, void *, void *);
void * dyn_call1_ret(Str *, Str *, void *);
void * dyn_call2_ret(Str *, Str *, void *, void *);
Bool * dyn_has_method(Str *, Str *);
Array * array(Str *, Array *);
Vec * vec(Str *, Array *);
I64 * spawn_cmd(Str *);
I64 * check_cmd_status(I64);
void sleep_ms(I64);
Str * readfile(Str *);
void writefile(Str *, Str *);
I64 * file_mtime(Str *);
I64 * clock_ms(void);
I64 * get_thread_count(void);

static Str *Str_lit(const char *s, long long cap);
static void print_single(Str *s);
static void print_flush();

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
I64 U8_to_i64(U8 val);
Str * U8_to_str(U8 * val);
U8 * U8_from_i64(I64 * val);
U8 U8_add(U8 a, U8 b);
U8 U8_sub(U8 a, U8 b);
U8 U8_mul(U8 a, U8 b);
U8 U8_div(U8 a, U8 b);
U8 U8_mod(U8 a, U8 b);
U8 U8_inc(U8 a);
U8 U8_dec(U8 a);
Bool U8_eq(U8 a, U8 b);
I64 U8_cmp(U8 a, U8 b);
U8 U8_and(U8 a, U8 b);
U8 U8_or(U8 a, U8 b);
U8 U8_xor(U8 a, U8 b);
U8 * U8_clone(U8 * val);
void U8_delete(U8 * self, Bool * call_free);
I64 * U8_size(void);
Bool * U8_lt(U8 * a, U8 * b);
Bool * U8_gt(U8 * a, U8 * b);
Bool * U8_neq(U8 * a, U8 * b);
Bool * U8_lte(U8 * a, U8 * b);
Bool * U8_gte(U8 * a, U8 * b);
I64 I16_to_i64(I16 val);
Str * I16_to_str(I16 * val);
I16 * I16_from_i64(I64 * val);
I16 I16_add(I16 a, I16 b);
I16 I16_sub(I16 a, I16 b);
I16 I16_mul(I16 a, I16 b);
I16 I16_div(I16 a, I16 b);
I16 I16_mod(I16 a, I16 b);
I16 I16_inc(I16 a);
I16 I16_dec(I16 a);
Bool I16_eq(I16 a, I16 b);
I64 I16_cmp(I16 a, I16 b);
I16 * I16_neg(I16 * a);
I16 * I16_abs(I16 * a);
I16 I16_and(I16 a, I16 b);
I16 I16_or(I16 a, I16 b);
I16 I16_xor(I16 a, I16 b);
I16 * I16_clone(I16 * val);
void I16_delete(I16 * self, Bool * call_free);
I64 * I16_size(void);
Bool * I16_lt(I16 * a, I16 * b);
Bool * I16_gt(I16 * a, I16 * b);
Bool * I16_neq(I16 * a, I16 * b);
Bool * I16_lte(I16 * a, I16 * b);
Bool * I16_gte(I16 * a, I16 * b);
I64 I32_to_i64(I32 val);
Str * I32_to_str(I32 * val);
I32 * I32_from_i64(I64 * val);
I32 I32_add(I32 a, I32 b);
I32 I32_sub(I32 a, I32 b);
I32 I32_mul(I32 a, I32 b);
I32 I32_div(I32 a, I32 b);
I32 I32_mod(I32 a, I32 b);
I32 I32_inc(I32 a);
I32 I32_dec(I32 a);
Bool I32_eq(I32 a, I32 b);
I64 I32_cmp(I32 a, I32 b);
I32 * I32_neg(I32 * a);
I32 * I32_abs(I32 * a);
I32 I32_and(I32 a, I32 b);
I32 I32_or(I32 a, I32 b);
I32 I32_xor(I32 a, I32 b);
I32 * I32_clone(I32 * val);
void I32_delete(I32 * self, Bool * call_free);
I64 * I32_size(void);
Bool * I32_lt(I32 * a, I32 * b);
Bool * I32_gt(I32 * a, I32 * b);
Bool * I32_neq(I32 * a, I32 * b);
Bool * I32_lte(I32 * a, I32 * b);
Bool * I32_gte(I32 * a, I32 * b);
I64 F32_to_i64(F32 val);
Str * F32_to_str(F32 val);
F32 * F32_from_i64(I64 * val);
F32 F32_add(F32 a, F32 b);
F32 F32_sub(F32 a, F32 b);
F32 F32_mul(F32 a, F32 b);
F32 F32_div(F32 a, F32 b);
Bool F32_eq(F32 a, F32 b);
I64 F32_cmp(F32 a, F32 b);
F32 * F32_clone(F32 * val);
void F32_delete(F32 * self, Bool * call_free);
I64 * F32_size(void);
Bool * F32_lt(F32 * a, F32 * b);
Bool * F32_gt(F32 * a, F32 * b);
Bool * F32_neq(F32 * a, F32 * b);
Bool * F32_lte(F32 * a, F32 * b);
Bool * F32_gte(F32 * a, F32 * b);
I64 U32_to_i64(U32 val);
Str * U32_to_str(U32 * val);
U32 * U32_from_i64(I64 * val);
U32 U32_add(U32 a, U32 b);
U32 U32_sub(U32 a, U32 b);
U32 U32_mul(U32 a, U32 b);
U32 U32_div(U32 a, U32 b);
U32 U32_mod(U32 a, U32 b);
U32 U32_inc(U32 a);
U32 U32_dec(U32 a);
Bool U32_eq(U32 a, U32 b);
I64 U32_cmp(U32 a, U32 b);
U32 U32_and(U32 a, U32 b);
U32 U32_or(U32 a, U32 b);
U32 U32_xor(U32 a, U32 b);
U32 * U32_clone(U32 * val);
void U32_delete(U32 * self, Bool * call_free);
I64 * U32_size(void);
Bool * U32_lt(U32 * a, U32 * b);
Bool * U32_gt(U32 * a, U32 * b);
Bool * U32_neq(U32 * a, U32 * b);
Bool * U32_lte(U32 * a, U32 * b);
Bool * U32_gte(U32 * a, U32 * b);
Str * I64_to_str(I64 * val);
I64 I64_add(I64 a, I64 b);
I64 I64_sub(I64 a, I64 b);
I64 I64_mul(I64 a, I64 b);
I64 I64_div(I64 a, I64 b);
I64 I64_mod(I64 a, I64 b);
I64 I64_inc(I64 a);
I64 I64_dec(I64 a);
Bool I64_eq(I64 a, I64 b);
I64 I64_cmp(I64 a, I64 b);
I64 * I64_neg(I64 * a);
I64 * I64_abs(I64 * a);
I64 I64_and(I64 a, I64 b);
I64 I64_or(I64 a, I64 b);
I64 I64_xor(I64 a, I64 b);
I64 * I64_clone(I64 * val);
void I64_delete(I64 * self, Bool * call_free);
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
Bool Bool_eq(Bool a, Bool b);
I64 * Bool_cmp(Bool * a, Bool * b);
Bool * Bool_clone(Bool * val);
void Bool_delete(Bool * self, Bool * call_free);
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

void dyn_call_delete(Str *type_name, void *val, void *arg2);
void *dyn_call_clone(Str *type_name, void *val);
void *dyn_call_cmp(Str *type_name, void *val, void *arg2);

Bool *dyn_has_cmp(Str *type_name);


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


#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
__attribute__((unused))
#define TIL_CAP_LIT (-1LL)
static Str *Str_lit(const char *s, long long len) {
    Str *r = malloc(sizeof(Str));
    r->c_str = (U8 *)s;
    r->count = len;
    r->cap = TIL_CAP_LIT;
    return r;
}
__attribute__((unused))
static void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
__attribute__((unused))
static void print_flush() {
    putchar('\n');
}

static I64 *_t1062;
static I64 *_t1063;
static I64 *CAP_LIT;
static I64 *_t1064;
static I64 *_t1065;
static I64 *CAP_VIEW;

Array * Array_new(Str * elem_type, I64 * elem_size, I64 * cap) {
    void *_t0 = calloc(DEREF(cap), DEREF(elem_size));
    I64 *_t1 = I64_clone(cap);
    I64 *_t2 = I64_clone(elem_size);
    Array *_t3 = malloc(sizeof(Array));
    _t3->data = _t0;
    _t3->cap = DEREF(_t1);
    _t3->elem_size = DEREF(_t2);
    { Str *_ca = Str_clone(elem_type); _t3->elem_type = *_ca; free(_ca); }
    I64_delete(_t1, &(Bool){1});
    I64_delete(_t2, &(Bool){1});
    return _t3;
}

I64 * Array_len(Array * self) {
    { I64 *_r = malloc(sizeof(I64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, I64 * i) {
    I64 *_t18 = malloc(sizeof(I64));
    *_t18 = 0;
    Bool *_t19 = I64_lt(i, _t18);
    I64_delete(_t18, &(Bool){1});
    Bool *_t20 = I64_gte(i, &self->cap);
    Bool *_t21 = malloc(sizeof(Bool)); *_t21 = Bool_or(DEREF(_t19), DEREF(_t20));
    Bool_delete(_t19, &(Bool){1});
    Bool_delete(_t20, &(Bool){1});
    if (DEREF(_t21)) {
        Str *_t4 = Str_lit("Str", 3);
        I64 *_t5 = Str_size();
        I64 *_t6 = malloc(sizeof(I64));
        *_t6 = 5;
        Array *_va0 = Array_new(_t4, _t5, _t6);
        Str_delete(_t4, &(Bool){1});
        I64_delete(_t5, &(Bool){1});
        I64_delete(_t6, &(Bool){1});
        I64 *_t7 = malloc(sizeof(I64));
        *_t7 = 0;
        Str *_t8 = Str_lit("index ", 6);
        Array_set(_va0, _t7, _t8);
        I64_delete(_t7, &(Bool){1});
        I64 *_t9 = malloc(sizeof(I64));
        *_t9 = 1;
        Str *_t10 = I64_to_str(i);
        Array_set(_va0, _t9, _t10);
        I64_delete(_t9, &(Bool){1});
        I64 *_t11 = malloc(sizeof(I64));
        *_t11 = 2;
        Str *_t12 = Str_lit(" out of bounds (len ", 20);
        Array_set(_va0, _t11, _t12);
        I64_delete(_t11, &(Bool){1});
        I64 *_t13 = malloc(sizeof(I64));
        *_t13 = 3;
        Str *_t14 = I64_to_str(&self->cap);
        Array_set(_va0, _t13, _t14);
        I64_delete(_t13, &(Bool){1});
        I64 *_t15 = malloc(sizeof(I64));
        *_t15 = 4;
        Str *_t16 = Str_lit(")", 1);
        Array_set(_va0, _t15, _t16);
        I64_delete(_t15, &(Bool){1});
        Str *_t17 = Str_lit("Array.get", 9);
        panic(_t17, _va0);
        Str_delete(_t17, &(Bool){1});
        Array_delete(_va0, &(Bool){1});
    }
    Bool_delete(_t21, &(Bool){1});
    I64 *_t22 = malloc(sizeof(I64)); *_t22 = I64_mul(DEREF(i), self->elem_size);
    void *_t23 = ptr_add(self->data, DEREF(_t22));
    I64_delete(_t22, &(Bool){1});
    return _t23;
}

void Array_set(Array * self, I64 * i, void * val) {
    I64 *_t38 = malloc(sizeof(I64));
    *_t38 = 0;
    Bool *_t39 = I64_lt(i, _t38);
    I64_delete(_t38, &(Bool){1});
    Bool *_t40 = I64_gte(i, &self->cap);
    Bool *_t41 = malloc(sizeof(Bool)); *_t41 = Bool_or(DEREF(_t39), DEREF(_t40));
    Bool_delete(_t39, &(Bool){1});
    Bool_delete(_t40, &(Bool){1});
    if (DEREF(_t41)) {
        Str *_t24 = Str_lit("Str", 3);
        I64 *_t25 = Str_size();
        I64 *_t26 = malloc(sizeof(I64));
        *_t26 = 5;
        Array *_va1 = Array_new(_t24, _t25, _t26);
        Str_delete(_t24, &(Bool){1});
        I64_delete(_t25, &(Bool){1});
        I64_delete(_t26, &(Bool){1});
        I64 *_t27 = malloc(sizeof(I64));
        *_t27 = 0;
        Str *_t28 = Str_lit("index ", 6);
        Array_set(_va1, _t27, _t28);
        I64_delete(_t27, &(Bool){1});
        I64 *_t29 = malloc(sizeof(I64));
        *_t29 = 1;
        Str *_t30 = I64_to_str(i);
        Array_set(_va1, _t29, _t30);
        I64_delete(_t29, &(Bool){1});
        I64 *_t31 = malloc(sizeof(I64));
        *_t31 = 2;
        Str *_t32 = Str_lit(" out of bounds (len ", 20);
        Array_set(_va1, _t31, _t32);
        I64_delete(_t31, &(Bool){1});
        I64 *_t33 = malloc(sizeof(I64));
        *_t33 = 3;
        Str *_t34 = I64_to_str(&self->cap);
        Array_set(_va1, _t33, _t34);
        I64_delete(_t33, &(Bool){1});
        I64 *_t35 = malloc(sizeof(I64));
        *_t35 = 4;
        Str *_t36 = Str_lit(")", 1);
        Array_set(_va1, _t35, _t36);
        I64_delete(_t35, &(Bool){1});
        Str *_t37 = Str_lit("Array.set", 9);
        panic(_t37, _va1);
        Str_delete(_t37, &(Bool){1});
        Array_delete(_va1, &(Bool){1});
    }
    Bool_delete(_t41, &(Bool){1});
    I64 *_t42 = malloc(sizeof(I64)); *_t42 = I64_mul(DEREF(i), self->elem_size);
    void *_t43 = ptr_add(self->data, DEREF(_t42));
    Bool *_t44 = malloc(sizeof(Bool));
    *_t44 = 0;
    dyn_call_delete(&self->elem_type, _t43, _t44);
    I64_delete(_t42, &(Bool){1});
    Bool_delete(_t44, &(Bool){1});
    I64 *_t45 = malloc(sizeof(I64)); *_t45 = I64_mul(DEREF(i), self->elem_size);
    void *_t46 = ptr_add(self->data, DEREF(_t45));
    memcpy(_t46, val, self->elem_size);
    I64_delete(_t45, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        I64 *_fi47 = malloc(sizeof(I64));
        *_fi47 = 0;
        while (1) {
            I64 *_t49 = malloc(sizeof(I64));
            *_t49 = 0;
            Range *_t50 = Range_new(_t49, &self->cap);
            I64_delete(_t49, &(Bool){1});
            I64 *_t51 = Range_len(_t50);
            Range_delete(_t50, &(Bool){1});
            Bool *_wcond48 = I64_lt(_fi47, _t51);
            I64_delete(_t51, &(Bool){1});
            if (DEREF(_wcond48)) {
            } else {
                Bool_delete(_wcond48, &(Bool){1});
                break;
            }
            Bool_delete(_wcond48, &(Bool){1});
            I64 *_t52 = malloc(sizeof(I64));
            *_t52 = 0;
            Range *_t53 = Range_new(_t52, &self->cap);
            I64_delete(_t52, &(Bool){1});
            I64 *i = Range_get(_t53, _fi47);
            Range_delete(_t53, &(Bool){1});
            I64 *_t54 = malloc(sizeof(I64));
            *_t54 = 1;
            I64 *_t55 = malloc(sizeof(I64)); *_t55 = I64_add(DEREF(_fi47), DEREF(_t54));
            I64_delete(_t54, &(Bool){1});
            *_fi47 = DEREF(_t55);
            I64_delete(_t55, &(Bool){1});
            I64 *_t56 = malloc(sizeof(I64)); *_t56 = I64_mul(DEREF(i), self->elem_size);
            I64_delete(i, &(Bool){1});
            void *_t57 = ptr_add(self->data, DEREF(_t56));
            Bool *_t58 = malloc(sizeof(Bool));
            *_t58 = 0;
            dyn_call_delete(&self->elem_type, _t57, _t58);
            I64_delete(_t56, &(Bool){1});
            Bool_delete(_t58, &(Bool){1});
        }
        I64_delete(_fi47, &(Bool){1});
    }
    free(self->data);
    Bool *_t59 = malloc(sizeof(Bool));
    *_t59 = 0;
    Str_delete(&self->elem_type, _t59);
    Bool_delete(_t59, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    I64 *_t73 = malloc(sizeof(I64)); *_t73 = I64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t73));
    I64_delete(_t73, &(Bool){1});
    {
        I64 *_fi60 = malloc(sizeof(I64));
        *_fi60 = 0;
        while (1) {
            I64 *_t62 = malloc(sizeof(I64));
            *_t62 = 0;
            Range *_t63 = Range_new(_t62, &self->cap);
            I64_delete(_t62, &(Bool){1});
            I64 *_t64 = Range_len(_t63);
            Range_delete(_t63, &(Bool){1});
            Bool *_wcond61 = I64_lt(_fi60, _t64);
            I64_delete(_t64, &(Bool){1});
            if (DEREF(_wcond61)) {
            } else {
                Bool_delete(_wcond61, &(Bool){1});
                break;
            }
            Bool_delete(_wcond61, &(Bool){1});
            I64 *_t65 = malloc(sizeof(I64));
            *_t65 = 0;
            Range *_t66 = Range_new(_t65, &self->cap);
            I64_delete(_t65, &(Bool){1});
            I64 *i = Range_get(_t66, _fi60);
            Range_delete(_t66, &(Bool){1});
            I64 *_t67 = malloc(sizeof(I64));
            *_t67 = 1;
            I64 *_t68 = malloc(sizeof(I64)); *_t68 = I64_add(DEREF(_fi60), DEREF(_t67));
            I64_delete(_t67, &(Bool){1});
            *_fi60 = DEREF(_t68);
            I64_delete(_t68, &(Bool){1});
            I64 *_t69 = malloc(sizeof(I64)); *_t69 = I64_mul(DEREF(i), self->elem_size);
            void *_t70 = ptr_add(self->data, DEREF(_t69));
            void *cloned = dyn_call_clone(&self->elem_type, _t70);
            I64_delete(_t69, &(Bool){1});
            I64 *_t71 = malloc(sizeof(I64)); *_t71 = I64_mul(DEREF(i), self->elem_size);
            I64_delete(i, &(Bool){1});
            void *_t72 = ptr_add(new_data, DEREF(_t71));
            memcpy(_t72, cloned, self->elem_size);
            I64_delete(_t71, &(Bool){1});
            free(cloned);
        }
        I64_delete(_fi60, &(Bool){1});
    }
    Array *_t74 = malloc(sizeof(Array));
    _t74->data = new_data;
    _t74->cap = self->cap;
    _t74->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t74->elem_type = *_ca; free(_ca); }
    return _t74;
}

I64 *Array_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(Array);
    return r;
}

Map * Map_new(Str * key_type, I64 * key_size, Str * val_type, I64 * val_size) {
    Bool *_t86 = dyn_has_cmp(key_type);
    Bool *_t87 = malloc(sizeof(Bool)); *_t87 = Bool_not(DEREF(_t86));
    Bool_delete(_t86, &(Bool){1});
    if (DEREF(_t87)) {
        Str *_t76 = Str_lit("Str", 3);
        I64 *_t77 = Str_size();
        I64 *_t78 = malloc(sizeof(I64));
        *_t78 = 3;
        Array *_va2 = Array_new(_t76, _t77, _t78);
        Str_delete(_t76, &(Bool){1});
        I64_delete(_t77, &(Bool){1});
        I64_delete(_t78, &(Bool){1});
        I64 *_t79 = malloc(sizeof(I64));
        *_t79 = 0;
        Str *_t80 = Str_lit("type ", 5);
        Array_set(_va2, _t79, _t80);
        I64_delete(_t79, &(Bool){1});
        I64 *_t81 = malloc(sizeof(I64));
        *_t81 = 1;
        Str *_t82 = Str_clone(key_type);
        Array_set(_va2, _t81, _t82);
        I64_delete(_t81, &(Bool){1});
        I64 *_t83 = malloc(sizeof(I64));
        *_t83 = 2;
        Str *_t84 = Str_lit(" must implement cmp", 19);
        Array_set(_va2, _t83, _t84);
        I64_delete(_t83, &(Bool){1});
        Str *_t85 = Str_lit("Map.new", 7);
        panic(_t85, _va2);
        Str_delete(_t85, &(Bool){1});
        Array_delete(_va2, &(Bool){1});
    }
    Bool_delete(_t87, &(Bool){1});
    void *_t88 = malloc(DEREF(key_size));
    void *_t89 = malloc(DEREF(val_size));
    I64 *_t90 = malloc(sizeof(I64));
    *_t90 = 0;
    I64 *_t91 = malloc(sizeof(I64));
    *_t91 = 1;
    I64 *_t92 = I64_clone(key_size);
    I64 *_t93 = I64_clone(val_size);
    Map *_t94 = malloc(sizeof(Map));
    _t94->key_data = _t88;
    _t94->val_data = _t89;
    _t94->count = DEREF(_t90);
    _t94->cap = DEREF(_t91);
    _t94->key_size = DEREF(_t92);
    { Str *_ca = Str_clone(key_type); _t94->key_type = *_ca; free(_ca); }
    _t94->val_size = DEREF(_t93);
    { Str *_ca = Str_clone(val_type); _t94->val_type = *_ca; free(_ca); }
    I64_delete(_t90, &(Bool){1});
    I64_delete(_t91, &(Bool){1});
    I64_delete(_t92, &(Bool){1});
    I64_delete(_t93, &(Bool){1});
    return _t94;
}

I64 * Map_len(Map * self) {
    { I64 *_r = malloc(sizeof(I64)); *_r = self->count; return _r; }
}

Bool * Map_has(Map * self, void * key) {
    I64 *lo = malloc(sizeof(I64));
    *lo = 0;
    I64 *hi = malloc(sizeof(I64));
    *hi = self->count;
    while (1) {
        Bool *_wcond95 = I64_lt(lo, hi);
        if (DEREF(_wcond95)) {
        } else {
            Bool_delete(_wcond95, &(Bool){1});
            break;
        }
        Bool_delete(_wcond95, &(Bool){1});
        I64 *_t102 = malloc(sizeof(I64)); *_t102 = I64_sub(DEREF(hi), DEREF(lo));
        I64 *_t103 = malloc(sizeof(I64));
        *_t103 = 2;
        I64 *_t104 = malloc(sizeof(I64)); *_t104 = I64_div(DEREF(_t102), DEREF(_t103));
        I64_delete(_t102, &(Bool){1});
        I64_delete(_t103, &(Bool){1});
        I64 *mid = malloc(sizeof(I64)); *mid = I64_add(DEREF(lo), DEREF(_t104));
        I64_delete(_t104, &(Bool){1});
        I64 *_t105 = malloc(sizeof(I64)); *_t105 = I64_mul(DEREF(mid), self->key_size);
        void *_t106 = ptr_add(self->key_data, DEREF(_t105));
        I64 *c = dyn_call_cmp(&self->key_type, _t106, key);
        I64_delete(_t105, &(Bool){1});
        I64 *_t107 = malloc(sizeof(I64));
        *_t107 = 0;
        Bool *_t108 = I64_lt(c, _t107);
        I64_delete(_t107, &(Bool){1});
        if (DEREF(_t108)) {
            I64 *_t96 = malloc(sizeof(I64));
            *_t96 = 1;
            I64 *_t97 = malloc(sizeof(I64)); *_t97 = I64_add(DEREF(mid), DEREF(_t96));
            I64_delete(_t96, &(Bool){1});
            *lo = DEREF(_t97);
            I64_delete(_t97, &(Bool){1});
        } else {
            I64 *_t100 = malloc(sizeof(I64));
            *_t100 = 0;
            Bool *_t101 = I64_gt(c, _t100);
            I64_delete(_t100, &(Bool){1});
            if (DEREF(_t101)) {
                I64 *_t98 = I64_clone(mid);
                *hi = DEREF(_t98);
                I64_delete(_t98, &(Bool){1});
            } else {
                Bool *_t99 = malloc(sizeof(Bool));
                *_t99 = 1;
                Bool_delete(_t101, &(Bool){1});
                Bool_delete(_t108, &(Bool){1});
                I64_delete(c, &(Bool){1});
                I64_delete(mid, &(Bool){1});
                I64_delete(hi, &(Bool){1});
                I64_delete(lo, &(Bool){1});
                return _t99;
            }
            Bool_delete(_t101, &(Bool){1});
        }
        Bool_delete(_t108, &(Bool){1});
        I64_delete(c, &(Bool){1});
        I64_delete(mid, &(Bool){1});
    }
    I64_delete(hi, &(Bool){1});
    I64_delete(lo, &(Bool){1});
    Bool *_t109 = malloc(sizeof(Bool));
    *_t109 = 0;
    return _t109;
}

void * Map_get(Map * self, void * key) {
    I64 *lo = malloc(sizeof(I64));
    *lo = 0;
    I64 *hi = malloc(sizeof(I64));
    *hi = self->count;
    while (1) {
        Bool *_wcond110 = I64_lt(lo, hi);
        if (DEREF(_wcond110)) {
        } else {
            Bool_delete(_wcond110, &(Bool){1});
            break;
        }
        Bool_delete(_wcond110, &(Bool){1});
        I64 *_t118 = malloc(sizeof(I64)); *_t118 = I64_sub(DEREF(hi), DEREF(lo));
        I64 *_t119 = malloc(sizeof(I64));
        *_t119 = 2;
        I64 *_t120 = malloc(sizeof(I64)); *_t120 = I64_div(DEREF(_t118), DEREF(_t119));
        I64_delete(_t118, &(Bool){1});
        I64_delete(_t119, &(Bool){1});
        I64 *mid = malloc(sizeof(I64)); *mid = I64_add(DEREF(lo), DEREF(_t120));
        I64_delete(_t120, &(Bool){1});
        I64 *_t121 = malloc(sizeof(I64)); *_t121 = I64_mul(DEREF(mid), self->key_size);
        void *_t122 = ptr_add(self->key_data, DEREF(_t121));
        I64 *c = dyn_call_cmp(&self->key_type, _t122, key);
        I64_delete(_t121, &(Bool){1});
        I64 *_t123 = malloc(sizeof(I64));
        *_t123 = 0;
        Bool *_t124 = I64_lt(c, _t123);
        I64_delete(_t123, &(Bool){1});
        if (DEREF(_t124)) {
            I64 *_t111 = malloc(sizeof(I64));
            *_t111 = 1;
            I64 *_t112 = malloc(sizeof(I64)); *_t112 = I64_add(DEREF(mid), DEREF(_t111));
            I64_delete(_t111, &(Bool){1});
            *lo = DEREF(_t112);
            I64_delete(_t112, &(Bool){1});
        } else {
            I64 *_t116 = malloc(sizeof(I64));
            *_t116 = 0;
            Bool *_t117 = I64_gt(c, _t116);
            I64_delete(_t116, &(Bool){1});
            if (DEREF(_t117)) {
                I64 *_t113 = I64_clone(mid);
                *hi = DEREF(_t113);
                I64_delete(_t113, &(Bool){1});
            } else {
                I64 *_t114 = malloc(sizeof(I64)); *_t114 = I64_mul(DEREF(mid), self->val_size);
                void *_t115 = ptr_add(self->val_data, DEREF(_t114));
                I64_delete(_t114, &(Bool){1});
                Bool_delete(_t117, &(Bool){1});
                Bool_delete(_t124, &(Bool){1});
                I64_delete(c, &(Bool){1});
                I64_delete(mid, &(Bool){1});
                I64_delete(hi, &(Bool){1});
                I64_delete(lo, &(Bool){1});
                return _t115;
            }
            Bool_delete(_t117, &(Bool){1});
        }
        Bool_delete(_t124, &(Bool){1});
        I64_delete(c, &(Bool){1});
        I64_delete(mid, &(Bool){1});
    }
    I64_delete(hi, &(Bool){1});
    I64_delete(lo, &(Bool){1});
    Str *_t125 = Str_lit("Str", 3);
    I64 *_t126 = Str_size();
    I64 *_t127 = malloc(sizeof(I64));
    *_t127 = 1;
    Array *_va3 = Array_new(_t125, _t126, _t127);
    Str_delete(_t125, &(Bool){1});
    I64_delete(_t126, &(Bool){1});
    I64_delete(_t127, &(Bool){1});
    I64 *_t128 = malloc(sizeof(I64));
    *_t128 = 0;
    Str *_t129 = Str_lit("key not found", 13);
    Array_set(_va3, _t128, _t129);
    I64_delete(_t128, &(Bool){1});
    Str *_t130 = Str_lit("Map.get", 7);
    panic(_t130, _va3);
    Str_delete(_t130, &(Bool){1});
    Array_delete(_va3, &(Bool){1});
    I64 *_t131 = malloc(sizeof(I64));
    *_t131 = 0;
    void *_t132 = ptr_add(self->val_data, DEREF(_t131));
    I64_delete(_t131, &(Bool){1});
    return _t132;
}

void Map_set(Map * self, void * key, void * val) {
    I64 *lo = malloc(sizeof(I64));
    *lo = 0;
    I64 *hi = malloc(sizeof(I64));
    *hi = self->count;
    Bool *found = malloc(sizeof(Bool));
    *found = 0;
    while (1) {
        Bool *_wcond133 = I64_lt(lo, hi);
        if (DEREF(_wcond133)) {
        } else {
            Bool_delete(_wcond133, &(Bool){1});
            break;
        }
        Bool_delete(_wcond133, &(Bool){1});
        I64 *_t142 = malloc(sizeof(I64)); *_t142 = I64_sub(DEREF(hi), DEREF(lo));
        I64 *_t143 = malloc(sizeof(I64));
        *_t143 = 2;
        I64 *_t144 = malloc(sizeof(I64)); *_t144 = I64_div(DEREF(_t142), DEREF(_t143));
        I64_delete(_t142, &(Bool){1});
        I64_delete(_t143, &(Bool){1});
        I64 *mid = malloc(sizeof(I64)); *mid = I64_add(DEREF(lo), DEREF(_t144));
        I64_delete(_t144, &(Bool){1});
        I64 *_t145 = malloc(sizeof(I64)); *_t145 = I64_mul(DEREF(mid), self->key_size);
        void *_t146 = ptr_add(self->key_data, DEREF(_t145));
        I64 *c = dyn_call_cmp(&self->key_type, _t146, key);
        I64_delete(_t145, &(Bool){1});
        I64 *_t147 = malloc(sizeof(I64));
        *_t147 = 0;
        Bool *_t148 = I64_lt(c, _t147);
        I64_delete(_t147, &(Bool){1});
        if (DEREF(_t148)) {
            I64 *_t134 = malloc(sizeof(I64));
            *_t134 = 1;
            I64 *_t135 = malloc(sizeof(I64)); *_t135 = I64_add(DEREF(mid), DEREF(_t134));
            I64_delete(_t134, &(Bool){1});
            *lo = DEREF(_t135);
            I64_delete(_t135, &(Bool){1});
        } else {
            I64 *_t140 = malloc(sizeof(I64));
            *_t140 = 0;
            Bool *_t141 = I64_gt(c, _t140);
            I64_delete(_t140, &(Bool){1});
            if (DEREF(_t141)) {
                I64 *_t136 = I64_clone(mid);
                *hi = DEREF(_t136);
                I64_delete(_t136, &(Bool){1});
            } else {
                Bool *_t137 = malloc(sizeof(Bool));
                *_t137 = 1;
                *found = DEREF(_t137);
                Bool_delete(_t137, &(Bool){1});
                I64 *_t138 = I64_clone(mid);
                *lo = DEREF(_t138);
                I64_delete(_t138, &(Bool){1});
                I64 *_t139 = I64_clone(mid);
                *hi = DEREF(_t139);
                I64_delete(_t139, &(Bool){1});
            }
            Bool_delete(_t141, &(Bool){1});
        }
        Bool_delete(_t148, &(Bool){1});
        I64_delete(c, &(Bool){1});
        I64_delete(mid, &(Bool){1});
    }
    I64_delete(hi, &(Bool){1});
    if (DEREF(found)) {
        Bool *_t149 = malloc(sizeof(Bool));
        *_t149 = 0;
        dyn_call_delete(&self->key_type, key, _t149);
        Bool_delete(_t149, &(Bool){1});
        free(key);
        I64 *_t150 = malloc(sizeof(I64)); *_t150 = I64_mul(DEREF(lo), self->val_size);
        void *_t151 = ptr_add(self->val_data, DEREF(_t150));
        Bool *_t152 = malloc(sizeof(Bool));
        *_t152 = 0;
        dyn_call_delete(&self->val_type, _t151, _t152);
        I64_delete(_t150, &(Bool){1});
        Bool_delete(_t152, &(Bool){1});
        I64 *_t153 = malloc(sizeof(I64)); *_t153 = I64_mul(DEREF(lo), self->val_size);
        void *_t154 = ptr_add(self->val_data, DEREF(_t153));
        memcpy(_t154, val, self->val_size);
        I64_delete(_t153, &(Bool){1});
        free(val);
    } else {
        Bool *_t161 = malloc(sizeof(Bool)); *_t161 = I64_eq(self->count, self->cap);
        if (DEREF(_t161)) {
            I64 *_t155 = malloc(sizeof(I64));
            *_t155 = 2;
            I64 *new_cap = malloc(sizeof(I64)); *new_cap = I64_mul(self->cap, DEREF(_t155));
            I64_delete(_t155, &(Bool){1});
            I64 *_t156 = malloc(sizeof(I64)); *_t156 = I64_mul(DEREF(new_cap), self->key_size);
            void *_t157 = realloc(self->key_data, DEREF(_t156));
            I64_delete(_t156, &(Bool){1});
            self->key_data = _t157;
            I64 *_t158 = malloc(sizeof(I64)); *_t158 = I64_mul(DEREF(new_cap), self->val_size);
            void *_t159 = realloc(self->val_data, DEREF(_t158));
            I64_delete(_t158, &(Bool){1});
            self->val_data = _t159;
            I64 *_t160 = I64_clone(new_cap);
            I64_delete(new_cap, &(Bool){1});
            self->cap = DEREF(_t160);
            I64_delete(_t160, &(Bool){1});
        }
        Bool_delete(_t161, &(Bool){1});
        I64 *_t162 = malloc(sizeof(I64));
        *_t162 = 1;
        I64 *_t163 = malloc(sizeof(I64)); *_t163 = I64_add(DEREF(lo), DEREF(_t162));
        I64_delete(_t162, &(Bool){1});
        I64 *_t164 = malloc(sizeof(I64)); *_t164 = I64_mul(DEREF(_t163), self->key_size);
        I64_delete(_t163, &(Bool){1});
        I64 *_t165 = malloc(sizeof(I64)); *_t165 = I64_mul(DEREF(lo), self->key_size);
        I64 *_t166 = malloc(sizeof(I64)); *_t166 = I64_sub(self->count, DEREF(lo));
        void *_t167 = ptr_add(self->key_data, DEREF(_t164));
        void *_t168 = ptr_add(self->key_data, DEREF(_t165));
        I64 *_t169 = malloc(sizeof(I64)); *_t169 = I64_mul(DEREF(_t166), self->key_size);
        I64_delete(_t166, &(Bool){1});
        memmove(_t167, _t168, DEREF(_t169));
        I64_delete(_t164, &(Bool){1});
        I64_delete(_t165, &(Bool){1});
        I64_delete(_t169, &(Bool){1});
        I64 *_t170 = malloc(sizeof(I64));
        *_t170 = 1;
        I64 *_t171 = malloc(sizeof(I64)); *_t171 = I64_add(DEREF(lo), DEREF(_t170));
        I64_delete(_t170, &(Bool){1});
        I64 *_t172 = malloc(sizeof(I64)); *_t172 = I64_mul(DEREF(_t171), self->val_size);
        I64_delete(_t171, &(Bool){1});
        I64 *_t173 = malloc(sizeof(I64)); *_t173 = I64_mul(DEREF(lo), self->val_size);
        I64 *_t174 = malloc(sizeof(I64)); *_t174 = I64_sub(self->count, DEREF(lo));
        void *_t175 = ptr_add(self->val_data, DEREF(_t172));
        void *_t176 = ptr_add(self->val_data, DEREF(_t173));
        I64 *_t177 = malloc(sizeof(I64)); *_t177 = I64_mul(DEREF(_t174), self->val_size);
        I64_delete(_t174, &(Bool){1});
        memmove(_t175, _t176, DEREF(_t177));
        I64_delete(_t172, &(Bool){1});
        I64_delete(_t173, &(Bool){1});
        I64_delete(_t177, &(Bool){1});
        I64 *_t178 = malloc(sizeof(I64)); *_t178 = I64_mul(DEREF(lo), self->key_size);
        void *_t179 = ptr_add(self->key_data, DEREF(_t178));
        memcpy(_t179, key, self->key_size);
        I64_delete(_t178, &(Bool){1});
        I64 *_t180 = malloc(sizeof(I64)); *_t180 = I64_mul(DEREF(lo), self->val_size);
        void *_t181 = ptr_add(self->val_data, DEREF(_t180));
        memcpy(_t181, val, self->val_size);
        I64_delete(_t180, &(Bool){1});
        free(key);
        free(val);
        I64 *_t182 = malloc(sizeof(I64));
        *_t182 = 1;
        I64 *_t183 = malloc(sizeof(I64)); *_t183 = I64_add(self->count, DEREF(_t182));
        I64_delete(_t182, &(Bool){1});
        self->count = DEREF(_t183);
        I64_delete(_t183, &(Bool){1});
    }
    Bool_delete(found, &(Bool){1});
    I64_delete(lo, &(Bool){1});
}

void Map_delete(Map * self, Bool * call_free) {
    {
        I64 *_fi184 = malloc(sizeof(I64));
        *_fi184 = 0;
        while (1) {
            I64 *_t186 = malloc(sizeof(I64));
            *_t186 = 0;
            Range *_t187 = Range_new(_t186, &self->count);
            I64_delete(_t186, &(Bool){1});
            I64 *_t188 = Range_len(_t187);
            Range_delete(_t187, &(Bool){1});
            Bool *_wcond185 = I64_lt(_fi184, _t188);
            I64_delete(_t188, &(Bool){1});
            if (DEREF(_wcond185)) {
            } else {
                Bool_delete(_wcond185, &(Bool){1});
                break;
            }
            Bool_delete(_wcond185, &(Bool){1});
            I64 *_t189 = malloc(sizeof(I64));
            *_t189 = 0;
            Range *_t190 = Range_new(_t189, &self->count);
            I64_delete(_t189, &(Bool){1});
            I64 *i = Range_get(_t190, _fi184);
            Range_delete(_t190, &(Bool){1});
            I64 *_t191 = malloc(sizeof(I64));
            *_t191 = 1;
            I64 *_t192 = malloc(sizeof(I64)); *_t192 = I64_add(DEREF(_fi184), DEREF(_t191));
            I64_delete(_t191, &(Bool){1});
            *_fi184 = DEREF(_t192);
            I64_delete(_t192, &(Bool){1});
            I64 *_t193 = malloc(sizeof(I64)); *_t193 = I64_mul(DEREF(i), self->key_size);
            void *_t194 = ptr_add(self->key_data, DEREF(_t193));
            Bool *_t195 = malloc(sizeof(Bool));
            *_t195 = 0;
            dyn_call_delete(&self->key_type, _t194, _t195);
            I64_delete(_t193, &(Bool){1});
            Bool_delete(_t195, &(Bool){1});
            I64 *_t196 = malloc(sizeof(I64)); *_t196 = I64_mul(DEREF(i), self->val_size);
            I64_delete(i, &(Bool){1});
            void *_t197 = ptr_add(self->val_data, DEREF(_t196));
            Bool *_t198 = malloc(sizeof(Bool));
            *_t198 = 0;
            dyn_call_delete(&self->val_type, _t197, _t198);
            I64_delete(_t196, &(Bool){1});
            Bool_delete(_t198, &(Bool){1});
        }
        I64_delete(_fi184, &(Bool){1});
    }
    free(self->key_data);
    free(self->val_data);
    Bool *_t199 = malloc(sizeof(Bool));
    *_t199 = 0;
    Str_delete(&self->key_type, _t199);
    Bool_delete(_t199, &(Bool){1});
    Bool *_t200 = malloc(sizeof(Bool));
    *_t200 = 0;
    Str_delete(&self->val_type, _t200);
    Bool_delete(_t200, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    I64 *_t218 = malloc(sizeof(I64)); *_t218 = I64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(DEREF(_t218));
    I64_delete(_t218, &(Bool){1});
    I64 *_t219 = malloc(sizeof(I64)); *_t219 = I64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(DEREF(_t219));
    I64_delete(_t219, &(Bool){1});
    {
        I64 *_fi201 = malloc(sizeof(I64));
        *_fi201 = 0;
        while (1) {
            I64 *_t203 = malloc(sizeof(I64));
            *_t203 = 0;
            Range *_t204 = Range_new(_t203, &self->count);
            I64_delete(_t203, &(Bool){1});
            I64 *_t205 = Range_len(_t204);
            Range_delete(_t204, &(Bool){1});
            Bool *_wcond202 = I64_lt(_fi201, _t205);
            I64_delete(_t205, &(Bool){1});
            if (DEREF(_wcond202)) {
            } else {
                Bool_delete(_wcond202, &(Bool){1});
                break;
            }
            Bool_delete(_wcond202, &(Bool){1});
            I64 *_t206 = malloc(sizeof(I64));
            *_t206 = 0;
            Range *_t207 = Range_new(_t206, &self->count);
            I64_delete(_t206, &(Bool){1});
            I64 *i = Range_get(_t207, _fi201);
            Range_delete(_t207, &(Bool){1});
            I64 *_t208 = malloc(sizeof(I64));
            *_t208 = 1;
            I64 *_t209 = malloc(sizeof(I64)); *_t209 = I64_add(DEREF(_fi201), DEREF(_t208));
            I64_delete(_t208, &(Bool){1});
            *_fi201 = DEREF(_t209);
            I64_delete(_t209, &(Bool){1});
            I64 *_t210 = malloc(sizeof(I64)); *_t210 = I64_mul(DEREF(i), self->key_size);
            void *_t211 = ptr_add(self->key_data, DEREF(_t210));
            void *ck = dyn_call_clone(&self->key_type, _t211);
            I64_delete(_t210, &(Bool){1});
            I64 *_t212 = malloc(sizeof(I64)); *_t212 = I64_mul(DEREF(i), self->key_size);
            void *_t213 = ptr_add(new_keys, DEREF(_t212));
            memcpy(_t213, ck, self->key_size);
            I64_delete(_t212, &(Bool){1});
            free(ck);
            I64 *_t214 = malloc(sizeof(I64)); *_t214 = I64_mul(DEREF(i), self->val_size);
            void *_t215 = ptr_add(self->val_data, DEREF(_t214));
            void *cv = dyn_call_clone(&self->val_type, _t215);
            I64_delete(_t214, &(Bool){1});
            I64 *_t216 = malloc(sizeof(I64)); *_t216 = I64_mul(DEREF(i), self->val_size);
            I64_delete(i, &(Bool){1});
            void *_t217 = ptr_add(new_vals, DEREF(_t216));
            memcpy(_t217, cv, self->val_size);
            I64_delete(_t216, &(Bool){1});
            free(cv);
        }
        I64_delete(_fi201, &(Bool){1});
    }
    Map *_t220 = malloc(sizeof(Map));
    _t220->key_data = new_keys;
    _t220->val_data = new_vals;
    _t220->count = self->count;
    _t220->cap = self->cap;
    _t220->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t220->key_type = *_ca; free(_ca); }
    _t220->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t220->val_type = *_ca; free(_ca); }
    return _t220;
}

I64 *Map_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, I64 * elem_size) {
    Bool *_t232 = dyn_has_cmp(elem_type);
    Bool *_t233 = malloc(sizeof(Bool)); *_t233 = Bool_not(DEREF(_t232));
    Bool_delete(_t232, &(Bool){1});
    if (DEREF(_t233)) {
        Str *_t222 = Str_lit("Str", 3);
        I64 *_t223 = Str_size();
        I64 *_t224 = malloc(sizeof(I64));
        *_t224 = 3;
        Array *_va4 = Array_new(_t222, _t223, _t224);
        Str_delete(_t222, &(Bool){1});
        I64_delete(_t223, &(Bool){1});
        I64_delete(_t224, &(Bool){1});
        I64 *_t225 = malloc(sizeof(I64));
        *_t225 = 0;
        Str *_t226 = Str_lit("type ", 5);
        Array_set(_va4, _t225, _t226);
        I64_delete(_t225, &(Bool){1});
        I64 *_t227 = malloc(sizeof(I64));
        *_t227 = 1;
        Str *_t228 = Str_clone(elem_type);
        Array_set(_va4, _t227, _t228);
        I64_delete(_t227, &(Bool){1});
        I64 *_t229 = malloc(sizeof(I64));
        *_t229 = 2;
        Str *_t230 = Str_lit(" must implement cmp", 19);
        Array_set(_va4, _t229, _t230);
        I64_delete(_t229, &(Bool){1});
        Str *_t231 = Str_lit("Set.new", 7);
        panic(_t231, _va4);
        Str_delete(_t231, &(Bool){1});
        Array_delete(_va4, &(Bool){1});
    }
    Bool_delete(_t233, &(Bool){1});
    void *_t234 = malloc(DEREF(elem_size));
    I64 *_t235 = malloc(sizeof(I64));
    *_t235 = 0;
    I64 *_t236 = malloc(sizeof(I64));
    *_t236 = 1;
    I64 *_t237 = I64_clone(elem_size);
    Set *_t238 = malloc(sizeof(Set));
    _t238->data = _t234;
    _t238->count = DEREF(_t235);
    _t238->cap = DEREF(_t236);
    _t238->elem_size = DEREF(_t237);
    { Str *_ca = Str_clone(elem_type); _t238->elem_type = *_ca; free(_ca); }
    I64_delete(_t235, &(Bool){1});
    I64_delete(_t236, &(Bool){1});
    I64_delete(_t237, &(Bool){1});
    return _t238;
}

I64 * Set_len(Set * self) {
    { I64 *_r = malloc(sizeof(I64)); *_r = self->count; return _r; }
}

Bool * Set_has(Set * self, void * val) {
    I64 *lo = malloc(sizeof(I64));
    *lo = 0;
    I64 *hi = malloc(sizeof(I64));
    *hi = self->count;
    while (1) {
        Bool *_wcond239 = I64_lt(lo, hi);
        if (DEREF(_wcond239)) {
        } else {
            Bool_delete(_wcond239, &(Bool){1});
            break;
        }
        Bool_delete(_wcond239, &(Bool){1});
        I64 *_t246 = malloc(sizeof(I64)); *_t246 = I64_sub(DEREF(hi), DEREF(lo));
        I64 *_t247 = malloc(sizeof(I64));
        *_t247 = 2;
        I64 *_t248 = malloc(sizeof(I64)); *_t248 = I64_div(DEREF(_t246), DEREF(_t247));
        I64_delete(_t246, &(Bool){1});
        I64_delete(_t247, &(Bool){1});
        I64 *mid = malloc(sizeof(I64)); *mid = I64_add(DEREF(lo), DEREF(_t248));
        I64_delete(_t248, &(Bool){1});
        I64 *_t249 = malloc(sizeof(I64)); *_t249 = I64_mul(DEREF(mid), self->elem_size);
        void *_t250 = ptr_add(self->data, DEREF(_t249));
        I64 *c = dyn_call_cmp(&self->elem_type, _t250, val);
        I64_delete(_t249, &(Bool){1});
        I64 *_t251 = malloc(sizeof(I64));
        *_t251 = 0;
        Bool *_t252 = I64_lt(c, _t251);
        I64_delete(_t251, &(Bool){1});
        if (DEREF(_t252)) {
            I64 *_t240 = malloc(sizeof(I64));
            *_t240 = 1;
            I64 *_t241 = malloc(sizeof(I64)); *_t241 = I64_add(DEREF(mid), DEREF(_t240));
            I64_delete(_t240, &(Bool){1});
            *lo = DEREF(_t241);
            I64_delete(_t241, &(Bool){1});
        } else {
            I64 *_t244 = malloc(sizeof(I64));
            *_t244 = 0;
            Bool *_t245 = I64_gt(c, _t244);
            I64_delete(_t244, &(Bool){1});
            if (DEREF(_t245)) {
                I64 *_t242 = I64_clone(mid);
                *hi = DEREF(_t242);
                I64_delete(_t242, &(Bool){1});
            } else {
                Bool *_t243 = malloc(sizeof(Bool));
                *_t243 = 1;
                Bool_delete(_t245, &(Bool){1});
                Bool_delete(_t252, &(Bool){1});
                I64_delete(c, &(Bool){1});
                I64_delete(mid, &(Bool){1});
                I64_delete(hi, &(Bool){1});
                I64_delete(lo, &(Bool){1});
                return _t243;
            }
            Bool_delete(_t245, &(Bool){1});
        }
        Bool_delete(_t252, &(Bool){1});
        I64_delete(c, &(Bool){1});
        I64_delete(mid, &(Bool){1});
    }
    I64_delete(hi, &(Bool){1});
    I64_delete(lo, &(Bool){1});
    Bool *_t253 = malloc(sizeof(Bool));
    *_t253 = 0;
    return _t253;
}

void Set_add(Set * self, void * val) {
    I64 *lo = malloc(sizeof(I64));
    *lo = 0;
    I64 *hi = malloc(sizeof(I64));
    *hi = self->count;
    Bool *found = malloc(sizeof(Bool));
    *found = 0;
    while (1) {
        Bool *_wcond254 = I64_lt(lo, hi);
        if (DEREF(_wcond254)) {
        } else {
            Bool_delete(_wcond254, &(Bool){1});
            break;
        }
        Bool_delete(_wcond254, &(Bool){1});
        I64 *_t263 = malloc(sizeof(I64)); *_t263 = I64_sub(DEREF(hi), DEREF(lo));
        I64 *_t264 = malloc(sizeof(I64));
        *_t264 = 2;
        I64 *_t265 = malloc(sizeof(I64)); *_t265 = I64_div(DEREF(_t263), DEREF(_t264));
        I64_delete(_t263, &(Bool){1});
        I64_delete(_t264, &(Bool){1});
        I64 *mid = malloc(sizeof(I64)); *mid = I64_add(DEREF(lo), DEREF(_t265));
        I64_delete(_t265, &(Bool){1});
        I64 *_t266 = malloc(sizeof(I64)); *_t266 = I64_mul(DEREF(mid), self->elem_size);
        void *_t267 = ptr_add(self->data, DEREF(_t266));
        I64 *c = dyn_call_cmp(&self->elem_type, _t267, val);
        I64_delete(_t266, &(Bool){1});
        I64 *_t268 = malloc(sizeof(I64));
        *_t268 = 0;
        Bool *_t269 = I64_lt(c, _t268);
        I64_delete(_t268, &(Bool){1});
        if (DEREF(_t269)) {
            I64 *_t255 = malloc(sizeof(I64));
            *_t255 = 1;
            I64 *_t256 = malloc(sizeof(I64)); *_t256 = I64_add(DEREF(mid), DEREF(_t255));
            I64_delete(_t255, &(Bool){1});
            *lo = DEREF(_t256);
            I64_delete(_t256, &(Bool){1});
        } else {
            I64 *_t261 = malloc(sizeof(I64));
            *_t261 = 0;
            Bool *_t262 = I64_gt(c, _t261);
            I64_delete(_t261, &(Bool){1});
            if (DEREF(_t262)) {
                I64 *_t257 = I64_clone(mid);
                *hi = DEREF(_t257);
                I64_delete(_t257, &(Bool){1});
            } else {
                Bool *_t258 = malloc(sizeof(Bool));
                *_t258 = 1;
                *found = DEREF(_t258);
                Bool_delete(_t258, &(Bool){1});
                I64 *_t259 = I64_clone(mid);
                *lo = DEREF(_t259);
                I64_delete(_t259, &(Bool){1});
                I64 *_t260 = I64_clone(mid);
                *hi = DEREF(_t260);
                I64_delete(_t260, &(Bool){1});
            }
            Bool_delete(_t262, &(Bool){1});
        }
        Bool_delete(_t269, &(Bool){1});
        I64_delete(c, &(Bool){1});
        I64_delete(mid, &(Bool){1});
    }
    I64_delete(hi, &(Bool){1});
    if (DEREF(found)) {
        Bool *_t270 = malloc(sizeof(Bool));
        *_t270 = 0;
        dyn_call_delete(&self->elem_type, val, _t270);
        Bool_delete(_t270, &(Bool){1});
        free(val);
    } else {
        Bool *_t275 = malloc(sizeof(Bool)); *_t275 = I64_eq(self->count, self->cap);
        if (DEREF(_t275)) {
            I64 *_t271 = malloc(sizeof(I64));
            *_t271 = 2;
            I64 *new_cap = malloc(sizeof(I64)); *new_cap = I64_mul(self->cap, DEREF(_t271));
            I64_delete(_t271, &(Bool){1});
            I64 *_t272 = malloc(sizeof(I64)); *_t272 = I64_mul(DEREF(new_cap), self->elem_size);
            void *_t273 = realloc(self->data, DEREF(_t272));
            I64_delete(_t272, &(Bool){1});
            self->data = _t273;
            I64 *_t274 = I64_clone(new_cap);
            I64_delete(new_cap, &(Bool){1});
            self->cap = DEREF(_t274);
            I64_delete(_t274, &(Bool){1});
        }
        Bool_delete(_t275, &(Bool){1});
        I64 *_t276 = malloc(sizeof(I64));
        *_t276 = 1;
        I64 *_t277 = malloc(sizeof(I64)); *_t277 = I64_add(DEREF(lo), DEREF(_t276));
        I64_delete(_t276, &(Bool){1});
        I64 *_t278 = malloc(sizeof(I64)); *_t278 = I64_mul(DEREF(_t277), self->elem_size);
        I64_delete(_t277, &(Bool){1});
        I64 *_t279 = malloc(sizeof(I64)); *_t279 = I64_mul(DEREF(lo), self->elem_size);
        I64 *_t280 = malloc(sizeof(I64)); *_t280 = I64_sub(self->count, DEREF(lo));
        void *_t281 = ptr_add(self->data, DEREF(_t278));
        void *_t282 = ptr_add(self->data, DEREF(_t279));
        I64 *_t283 = malloc(sizeof(I64)); *_t283 = I64_mul(DEREF(_t280), self->elem_size);
        I64_delete(_t280, &(Bool){1});
        memmove(_t281, _t282, DEREF(_t283));
        I64_delete(_t278, &(Bool){1});
        I64_delete(_t279, &(Bool){1});
        I64_delete(_t283, &(Bool){1});
        I64 *_t284 = malloc(sizeof(I64)); *_t284 = I64_mul(DEREF(lo), self->elem_size);
        void *_t285 = ptr_add(self->data, DEREF(_t284));
        memcpy(_t285, val, self->elem_size);
        I64_delete(_t284, &(Bool){1});
        free(val);
        I64 *_t286 = malloc(sizeof(I64));
        *_t286 = 1;
        I64 *_t287 = malloc(sizeof(I64)); *_t287 = I64_add(self->count, DEREF(_t286));
        I64_delete(_t286, &(Bool){1});
        self->count = DEREF(_t287);
        I64_delete(_t287, &(Bool){1});
    }
    Bool_delete(found, &(Bool){1});
    I64_delete(lo, &(Bool){1});
}

void Set_delete(Set * self, Bool * call_free) {
    {
        I64 *_fi288 = malloc(sizeof(I64));
        *_fi288 = 0;
        while (1) {
            I64 *_t290 = malloc(sizeof(I64));
            *_t290 = 0;
            Range *_t291 = Range_new(_t290, &self->count);
            I64_delete(_t290, &(Bool){1});
            I64 *_t292 = Range_len(_t291);
            Range_delete(_t291, &(Bool){1});
            Bool *_wcond289 = I64_lt(_fi288, _t292);
            I64_delete(_t292, &(Bool){1});
            if (DEREF(_wcond289)) {
            } else {
                Bool_delete(_wcond289, &(Bool){1});
                break;
            }
            Bool_delete(_wcond289, &(Bool){1});
            I64 *_t293 = malloc(sizeof(I64));
            *_t293 = 0;
            Range *_t294 = Range_new(_t293, &self->count);
            I64_delete(_t293, &(Bool){1});
            I64 *i = Range_get(_t294, _fi288);
            Range_delete(_t294, &(Bool){1});
            I64 *_t295 = malloc(sizeof(I64));
            *_t295 = 1;
            I64 *_t296 = malloc(sizeof(I64)); *_t296 = I64_add(DEREF(_fi288), DEREF(_t295));
            I64_delete(_t295, &(Bool){1});
            *_fi288 = DEREF(_t296);
            I64_delete(_t296, &(Bool){1});
            I64 *_t297 = malloc(sizeof(I64)); *_t297 = I64_mul(DEREF(i), self->elem_size);
            I64_delete(i, &(Bool){1});
            void *_t298 = ptr_add(self->data, DEREF(_t297));
            Bool *_t299 = malloc(sizeof(Bool));
            *_t299 = 0;
            dyn_call_delete(&self->elem_type, _t298, _t299);
            I64_delete(_t297, &(Bool){1});
            Bool_delete(_t299, &(Bool){1});
        }
        I64_delete(_fi288, &(Bool){1});
    }
    free(self->data);
    Bool *_t300 = malloc(sizeof(Bool));
    *_t300 = 0;
    Str_delete(&self->elem_type, _t300);
    Bool_delete(_t300, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    I64 *_t314 = malloc(sizeof(I64)); *_t314 = I64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t314));
    I64_delete(_t314, &(Bool){1});
    {
        I64 *_fi301 = malloc(sizeof(I64));
        *_fi301 = 0;
        while (1) {
            I64 *_t303 = malloc(sizeof(I64));
            *_t303 = 0;
            Range *_t304 = Range_new(_t303, &self->count);
            I64_delete(_t303, &(Bool){1});
            I64 *_t305 = Range_len(_t304);
            Range_delete(_t304, &(Bool){1});
            Bool *_wcond302 = I64_lt(_fi301, _t305);
            I64_delete(_t305, &(Bool){1});
            if (DEREF(_wcond302)) {
            } else {
                Bool_delete(_wcond302, &(Bool){1});
                break;
            }
            Bool_delete(_wcond302, &(Bool){1});
            I64 *_t306 = malloc(sizeof(I64));
            *_t306 = 0;
            Range *_t307 = Range_new(_t306, &self->count);
            I64_delete(_t306, &(Bool){1});
            I64 *i = Range_get(_t307, _fi301);
            Range_delete(_t307, &(Bool){1});
            I64 *_t308 = malloc(sizeof(I64));
            *_t308 = 1;
            I64 *_t309 = malloc(sizeof(I64)); *_t309 = I64_add(DEREF(_fi301), DEREF(_t308));
            I64_delete(_t308, &(Bool){1});
            *_fi301 = DEREF(_t309);
            I64_delete(_t309, &(Bool){1});
            I64 *_t310 = malloc(sizeof(I64)); *_t310 = I64_mul(DEREF(i), self->elem_size);
            void *_t311 = ptr_add(self->data, DEREF(_t310));
            void *cloned = dyn_call_clone(&self->elem_type, _t311);
            I64_delete(_t310, &(Bool){1});
            I64 *_t312 = malloc(sizeof(I64)); *_t312 = I64_mul(DEREF(i), self->elem_size);
            I64_delete(i, &(Bool){1});
            void *_t313 = ptr_add(new_data, DEREF(_t312));
            memcpy(_t313, cloned, self->elem_size);
            I64_delete(_t312, &(Bool){1});
            free(cloned);
        }
        I64_delete(_fi301, &(Bool){1});
    }
    Set *_t315 = malloc(sizeof(Set));
    _t315->data = new_data;
    _t315->count = self->count;
    _t315->cap = self->cap;
    _t315->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t315->elem_type = *_ca; free(_ca); }
    return _t315;
}

I64 *Set_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(Set);
    return r;
}

I64 * Str_len(Str * self) {
    { I64 *_r = malloc(sizeof(I64)); *_r = self->count; return _r; }
}

U8 * Str_get(Str * self, I64 * i) {
    I64 *_t323 = malloc(sizeof(I64));
    *_t323 = 0;
    Bool *_t324 = I64_lt(i, _t323);
    I64_delete(_t323, &(Bool){1});
    Bool *_t325 = I64_gte(i, &self->count);
    Bool *_t326 = malloc(sizeof(Bool)); *_t326 = Bool_or(DEREF(_t324), DEREF(_t325));
    Bool_delete(_t324, &(Bool){1});
    Bool_delete(_t325, &(Bool){1});
    if (DEREF(_t326)) {
        Str *_t317 = Str_lit("Str", 3);
        I64 *_t318 = Str_size();
        I64 *_t319 = malloc(sizeof(I64));
        *_t319 = 1;
        Array *_va5 = Array_new(_t317, _t318, _t319);
        Str_delete(_t317, &(Bool){1});
        I64_delete(_t318, &(Bool){1});
        I64_delete(_t319, &(Bool){1});
        I64 *_t320 = malloc(sizeof(I64));
        *_t320 = 0;
        Str *_t321 = Str_lit("index out of bounds", 19);
        Array_set(_va5, _t320, _t321);
        I64_delete(_t320, &(Bool){1});
        Str *_t322 = Str_lit("Str.get", 7);
        panic(_t322, _va5);
        Str_delete(_t322, &(Bool){1});
        Array_delete(_va5, &(Bool){1});
    }
    Bool_delete(_t326, &(Bool){1});
    void *_t327 = ptr_add(self->c_str, DEREF(i));
    return _t327;
}

I64 * Str_cmp(Str * a, Str * b) {
    I64 *i = malloc(sizeof(I64));
    *i = 0;
    I64 *min_len = malloc(sizeof(I64));
    *min_len = a->count;
    Bool *_t333 = I64_lt(&b->count, &a->count);
    if (DEREF(_t333)) {
        *min_len = b->count;
    }
    Bool_delete(_t333, &(Bool){1});
    while (1) {
        Bool *_wcond328 = I64_lt(i, min_len);
        if (DEREF(_wcond328)) {
        } else {
            Bool_delete(_wcond328, &(Bool){1});
            break;
        }
        Bool_delete(_wcond328, &(Bool){1});
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 *_t329 = malloc(sizeof(I64));
        *_t329 = 0;
        Bool *_t330 = I64_neq(c, _t329);
        I64_delete(_t329, &(Bool){1});
        if (DEREF(_t330)) {
            Bool_delete(_t330, &(Bool){1});
            I64_delete(i, &(Bool){1});
            I64_delete(min_len, &(Bool){1});
            return c;
        }
        Bool_delete(_t330, &(Bool){1});
        I64_delete(c, &(Bool){1});
        I64 *_t331 = malloc(sizeof(I64));
        *_t331 = 1;
        I64 *_t332 = malloc(sizeof(I64)); *_t332 = I64_add(DEREF(i), DEREF(_t331));
        I64_delete(_t331, &(Bool){1});
        *i = DEREF(_t332);
        I64_delete(_t332, &(Bool){1});
    }
    I64_delete(i, &(Bool){1});
    I64_delete(min_len, &(Bool){1});
    I64 *_t334 = malloc(sizeof(I64)); *_t334 = I64_cmp(a->count, b->count);
    return _t334;
}

Str * Str_concat(Str * a, Str * b) {
    I64 *new_len = malloc(sizeof(I64)); *new_len = I64_add(a->count, b->count);
    I64 *_t335 = malloc(sizeof(I64));
    *_t335 = 1;
    I64 *_t336 = malloc(sizeof(I64)); *_t336 = I64_add(DEREF(new_len), DEREF(_t335));
    I64_delete(_t335, &(Bool){1});
    U8 *new_data = malloc(DEREF(_t336));
    I64_delete(_t336, &(Bool){1});
    memcpy(new_data, a->c_str, a->count);
    void *_t337 = ptr_add(new_data, a->count);
    memcpy(_t337, b->c_str, b->count);
    I64 *_t338 = malloc(sizeof(I64));
    *_t338 = 0;
    void *_t339 = ptr_add(new_data, DEREF(new_len));
    U8 *_t340 = U8_from_i64(_t338);
    I64_delete(_t338, &(Bool){1});
    I64 *_t341 = malloc(sizeof(I64));
    *_t341 = 1;
    memcpy(_t339, _t340, DEREF(_t341));
    U8_delete(_t340, &(Bool){1});
    I64_delete(_t341, &(Bool){1});
    I64 *_t342 = I64_clone(new_len);
    I64 *_t343 = I64_clone(new_len);
    I64_delete(new_len, &(Bool){1});
    Str *_t344 = malloc(sizeof(Str));
    _t344->c_str = new_data;
    _t344->count = DEREF(_t342);
    _t344->cap = DEREF(_t343);
    I64_delete(_t342, &(Bool){1});
    I64_delete(_t343, &(Bool){1});
    return _t344;
}

Str * Str_with_capacity(I64 * n) {
    I64 *_t345 = malloc(sizeof(I64));
    *_t345 = 1;
    I64 *_t346 = malloc(sizeof(I64)); *_t346 = I64_add(DEREF(n), DEREF(_t345));
    I64_delete(_t345, &(Bool){1});
    U8 *buf = malloc(DEREF(_t346));
    I64_delete(_t346, &(Bool){1});
    I64 *_t347 = malloc(sizeof(I64));
    *_t347 = 0;
    U8 *_t348 = U8_from_i64(_t347);
    I64_delete(_t347, &(Bool){1});
    I64 *_t349 = malloc(sizeof(I64));
    *_t349 = 1;
    memcpy(buf, _t348, DEREF(_t349));
    U8_delete(_t348, &(Bool){1});
    I64_delete(_t349, &(Bool){1});
    I64 *_t350 = malloc(sizeof(I64));
    *_t350 = 0;
    I64 *_t351 = I64_clone(n);
    Str *_t352 = malloc(sizeof(Str));
    _t352->c_str = buf;
    _t352->count = DEREF(_t350);
    _t352->cap = DEREF(_t351);
    I64_delete(_t350, &(Bool){1});
    I64_delete(_t351, &(Bool){1});
    return _t352;
}

void Str_push_str(Str * self, Str * s) {
    I64 *_t365 = malloc(sizeof(I64));
    *_t365 = 0;
    Bool *_t366 = I64_lt(&self->cap, _t365);
    I64_delete(_t365, &(Bool){1});
    if (DEREF(_t366)) {
        Str *_t353 = Str_lit("Str", 3);
        I64 *_t354 = Str_size();
        I64 *_t355 = malloc(sizeof(I64));
        *_t355 = 1;
        Array *_va6 = Array_new(_t353, _t354, _t355);
        Str_delete(_t353, &(Bool){1});
        I64_delete(_t354, &(Bool){1});
        I64_delete(_t355, &(Bool){1});
        I64 *_t356 = malloc(sizeof(I64));
        *_t356 = 0;
        Str *_t357 = Str_lit("cannot mutate a string view or literal", 38);
        Array_set(_va6, _t356, _t357);
        I64_delete(_t356, &(Bool){1});
        Str *_t358 = Str_lit("Str.push_str", 12);
        panic(_t358, _va6);
        Str_delete(_t358, &(Bool){1});
        Array_delete(_va6, &(Bool){1});
    }
    Bool_delete(_t366, &(Bool){1});
    I64 *new_len = malloc(sizeof(I64)); *new_len = I64_add(self->count, s->count);
    Bool *_t367 = I64_gt(new_len, &self->cap);
    if (DEREF(_t367)) {
        Str *_t359 = Str_lit("Str", 3);
        I64 *_t360 = Str_size();
        I64 *_t361 = malloc(sizeof(I64));
        *_t361 = 1;
        Array *_va7 = Array_new(_t359, _t360, _t361);
        Str_delete(_t359, &(Bool){1});
        I64_delete(_t360, &(Bool){1});
        I64_delete(_t361, &(Bool){1});
        I64 *_t362 = malloc(sizeof(I64));
        *_t362 = 0;
        Str *_t363 = Str_lit("capacity exceeded", 17);
        Array_set(_va7, _t362, _t363);
        I64_delete(_t362, &(Bool){1});
        Str *_t364 = Str_lit("Str.push_str", 12);
        panic(_t364, _va7);
        Str_delete(_t364, &(Bool){1});
        Array_delete(_va7, &(Bool){1});
    }
    Bool_delete(_t367, &(Bool){1});
    void *_t368 = ptr_add(self->c_str, self->count);
    memcpy(_t368, s->c_str, s->count);
    I64 *_t369 = I64_clone(new_len);
    self->count = DEREF(_t369);
    I64_delete(_t369, &(Bool){1});
    I64 *_t370 = malloc(sizeof(I64));
    *_t370 = 0;
    void *_t371 = ptr_add(self->c_str, DEREF(new_len));
    U8 *_t372 = U8_from_i64(_t370);
    I64_delete(_t370, &(Bool){1});
    I64 *_t373 = malloc(sizeof(I64));
    *_t373 = 1;
    memcpy(_t371, _t372, DEREF(_t373));
    U8_delete(_t372, &(Bool){1});
    I64_delete(_t373, &(Bool){1});
    I64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    I64 *_t374 = malloc(sizeof(I64));
    *_t374 = 1;
    I64 *_t375 = malloc(sizeof(I64)); *_t375 = I64_add(val->count, DEREF(_t374));
    I64_delete(_t374, &(Bool){1});
    U8 *new_data = malloc(DEREF(_t375));
    I64_delete(_t375, &(Bool){1});
    memcpy(new_data, val->c_str, val->count);
    I64 *_t376 = malloc(sizeof(I64));
    *_t376 = 0;
    void *_t377 = ptr_add(new_data, val->count);
    U8 *_t378 = U8_from_i64(_t376);
    I64_delete(_t376, &(Bool){1});
    I64 *_t379 = malloc(sizeof(I64));
    *_t379 = 1;
    memcpy(_t377, _t378, DEREF(_t379));
    U8_delete(_t378, &(Bool){1});
    I64_delete(_t379, &(Bool){1});
    Str *_t380 = malloc(sizeof(Str));
    _t380->c_str = new_data;
    _t380->count = val->count;
    _t380->cap = val->count;
    return _t380;
}

void Str_delete(Str * self, Bool * call_free) {
    I64 *_t381 = malloc(sizeof(I64));
    *_t381 = 0;
    Bool *_t382 = I64_gte(&self->cap, _t381);
    I64_delete(_t381, &(Bool){1});
    if (DEREF(_t382)) {
        free(self->c_str);
    }
    Bool_delete(_t382, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t383 = Str_clone(val);
    return _t383;
}

Str * Str_substr(Str * s, I64 * start, I64 * n) {
    I64 *st = I64_clone(start);
    I64 *ln = I64_clone(n);
    I64 *_t387 = malloc(sizeof(I64));
    *_t387 = 0;
    Bool *_t388 = I64_lt(st, _t387);
    I64_delete(_t387, &(Bool){1});
    if (DEREF(_t388)) {
        I64 *_t384 = malloc(sizeof(I64));
        *_t384 = 0;
        *st = DEREF(_t384);
        I64_delete(_t384, &(Bool){1});
    }
    Bool_delete(_t388, &(Bool){1});
    Bool *_t389 = I64_gt(st, &s->count);
    if (DEREF(_t389)) {
        *st = s->count;
    }
    Bool_delete(_t389, &(Bool){1});
    I64 *_t390 = malloc(sizeof(I64));
    *_t390 = 0;
    Bool *_t391 = I64_lt(ln, _t390);
    I64_delete(_t390, &(Bool){1});
    if (DEREF(_t391)) {
        I64 *_t385 = malloc(sizeof(I64));
        *_t385 = 0;
        *ln = DEREF(_t385);
        I64_delete(_t385, &(Bool){1});
    }
    Bool_delete(_t391, &(Bool){1});
    I64 *_t392 = malloc(sizeof(I64)); *_t392 = I64_add(DEREF(st), DEREF(ln));
    Bool *_t393 = I64_gt(_t392, &s->count);
    I64_delete(_t392, &(Bool){1});
    if (DEREF(_t393)) {
        I64 *_t386 = malloc(sizeof(I64)); *_t386 = I64_sub(s->count, DEREF(st));
        *ln = DEREF(_t386);
        I64_delete(_t386, &(Bool){1});
    }
    Bool_delete(_t393, &(Bool){1});
    void *_t394 = ptr_add(s->c_str, DEREF(st));
    I64 *_t395 = I64_clone(ln);
    I64_delete(ln, &(Bool){1});
    I64 *_t396 = I64_clone(CAP_VIEW);
    Str *_t397 = malloc(sizeof(Str));
    _t397->c_str = _t394;
    _t397->count = DEREF(_t395);
    _t397->cap = DEREF(_t396);
    I64_delete(_t395, &(Bool){1});
    I64_delete(_t396, &(Bool){1});
    I64_delete(st, &(Bool){1});
    return _t397;
}

Bool * Str_contains(Str * a, Str * b) {
    I64 *_t411 = malloc(sizeof(I64));
    *_t411 = 0;
    Bool *_t412 = malloc(sizeof(Bool)); *_t412 = I64_eq(b->count, DEREF(_t411));
    I64_delete(_t411, &(Bool){1});
    if (DEREF(_t412)) {
        Bool *_t398 = malloc(sizeof(Bool));
        *_t398 = 1;
        Bool_delete(_t412, &(Bool){1});
        return _t398;
    }
    Bool_delete(_t412, &(Bool){1});
    Bool *_t413 = I64_gt(&b->count, &a->count);
    if (DEREF(_t413)) {
        Bool *_t399 = malloc(sizeof(Bool));
        *_t399 = 0;
        Bool_delete(_t413, &(Bool){1});
        return _t399;
    }
    Bool_delete(_t413, &(Bool){1});
    I64 *i = malloc(sizeof(I64));
    *i = 0;
    while (1) {
        I64 *_t408 = malloc(sizeof(I64)); *_t408 = I64_sub(a->count, b->count);
        Bool *_wcond400 = I64_lte(i, _t408);
        I64_delete(_t408, &(Bool){1});
        if (DEREF(_wcond400)) {
        } else {
            Bool_delete(_wcond400, &(Bool){1});
            break;
        }
        Bool_delete(_wcond400, &(Bool){1});
        I64 *j = malloc(sizeof(I64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond401 = I64_lt(j, &b->count);
            if (DEREF(_wcond401)) {
            } else {
                Bool_delete(_wcond401, &(Bool){1});
                break;
            }
            Bool_delete(_wcond401, &(Bool){1});
            I64 *_t403 = malloc(sizeof(I64)); *_t403 = I64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(a, _t403);
            U8 *bc = Str_get(b, j);
            Bool *_t404 = U8_neq(ac, bc);
            I64_delete(_t403, &(Bool){1});
            if (DEREF(_t404)) {
                Bool *_t402 = malloc(sizeof(Bool));
                *_t402 = 0;
                *found = DEREF(_t402);
                Bool_delete(_t402, &(Bool){1});
            }
            Bool_delete(_t404, &(Bool){1});
            I64 *_t405 = malloc(sizeof(I64));
            *_t405 = 1;
            I64 *_t406 = malloc(sizeof(I64)); *_t406 = I64_add(DEREF(j), DEREF(_t405));
            I64_delete(_t405, &(Bool){1});
            *j = DEREF(_t406);
            I64_delete(_t406, &(Bool){1});
        }
        I64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            Bool *_t407 = malloc(sizeof(Bool));
            *_t407 = 1;
            Bool_delete(found, &(Bool){1});
            I64_delete(i, &(Bool){1});
            return _t407;
        }
        Bool_delete(found, &(Bool){1});
        I64 *_t409 = malloc(sizeof(I64));
        *_t409 = 1;
        I64 *_t410 = malloc(sizeof(I64)); *_t410 = I64_add(DEREF(i), DEREF(_t409));
        I64_delete(_t409, &(Bool){1});
        *i = DEREF(_t410);
        I64_delete(_t410, &(Bool){1});
    }
    I64_delete(i, &(Bool){1});
    Bool *_t414 = malloc(sizeof(Bool));
    *_t414 = 0;
    return _t414;
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool *_t421 = I64_gt(&b->count, &a->count);
    if (DEREF(_t421)) {
        Bool *_t415 = malloc(sizeof(Bool));
        *_t415 = 0;
        Bool_delete(_t421, &(Bool){1});
        return _t415;
    }
    Bool_delete(_t421, &(Bool){1});
    I64 *i = malloc(sizeof(I64));
    *i = 0;
    while (1) {
        Bool *_wcond416 = I64_lt(i, &b->count);
        if (DEREF(_wcond416)) {
        } else {
            Bool_delete(_wcond416, &(Bool){1});
            break;
        }
        Bool_delete(_wcond416, &(Bool){1});
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool *_t418 = U8_neq(ac, bc);
        if (DEREF(_t418)) {
            Bool *_t417 = malloc(sizeof(Bool));
            *_t417 = 0;
            Bool_delete(_t418, &(Bool){1});
            I64_delete(i, &(Bool){1});
            return _t417;
        }
        Bool_delete(_t418, &(Bool){1});
        I64 *_t419 = malloc(sizeof(I64));
        *_t419 = 1;
        I64 *_t420 = malloc(sizeof(I64)); *_t420 = I64_add(DEREF(i), DEREF(_t419));
        I64_delete(_t419, &(Bool){1});
        *i = DEREF(_t420);
        I64_delete(_t420, &(Bool){1});
    }
    I64_delete(i, &(Bool){1});
    Bool *_t422 = malloc(sizeof(Bool));
    *_t422 = 1;
    return _t422;
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool *_t430 = I64_gt(&b->count, &a->count);
    if (DEREF(_t430)) {
        Bool *_t423 = malloc(sizeof(Bool));
        *_t423 = 0;
        Bool_delete(_t430, &(Bool){1});
        return _t423;
    }
    Bool_delete(_t430, &(Bool){1});
    I64 *offset = malloc(sizeof(I64)); *offset = I64_sub(a->count, b->count);
    I64 *i = malloc(sizeof(I64));
    *i = 0;
    while (1) {
        Bool *_wcond424 = I64_lt(i, &b->count);
        if (DEREF(_wcond424)) {
        } else {
            Bool_delete(_wcond424, &(Bool){1});
            break;
        }
        Bool_delete(_wcond424, &(Bool){1});
        I64 *_t426 = malloc(sizeof(I64)); *_t426 = I64_add(DEREF(offset), DEREF(i));
        U8 *ac = Str_get(a, _t426);
        U8 *bc = Str_get(b, i);
        Bool *_t427 = U8_neq(ac, bc);
        I64_delete(_t426, &(Bool){1});
        if (DEREF(_t427)) {
            Bool *_t425 = malloc(sizeof(Bool));
            *_t425 = 0;
            Bool_delete(_t427, &(Bool){1});
            I64_delete(i, &(Bool){1});
            I64_delete(offset, &(Bool){1});
            return _t425;
        }
        Bool_delete(_t427, &(Bool){1});
        I64 *_t428 = malloc(sizeof(I64));
        *_t428 = 1;
        I64 *_t429 = malloc(sizeof(I64)); *_t429 = I64_add(DEREF(i), DEREF(_t428));
        I64_delete(_t428, &(Bool){1});
        *i = DEREF(_t429);
        I64_delete(_t429, &(Bool){1});
    }
    I64_delete(i, &(Bool){1});
    I64_delete(offset, &(Bool){1});
    Bool *_t431 = malloc(sizeof(Bool));
    *_t431 = 1;
    return _t431;
}

Bool * Str_is_empty(Str * self) {
    I64 *_t432 = malloc(sizeof(I64));
    *_t432 = 0;
    Bool *_t433 = malloc(sizeof(Bool)); *_t433 = I64_eq(self->count, DEREF(_t432));
    I64_delete(_t432, &(Bool){1});
    return _t433;
}

I64 * Str_find(Str * self, Str * needle) {
    I64 *_t450 = malloc(sizeof(I64));
    *_t450 = 0;
    Bool *_t451 = malloc(sizeof(Bool)); *_t451 = I64_eq(needle->count, DEREF(_t450));
    I64_delete(_t450, &(Bool){1});
    if (DEREF(_t451)) {
        I64 *_t434 = malloc(sizeof(I64));
        *_t434 = 0;
        I64 *_t435 = malloc(sizeof(I64));
        *_t435 = 1;
        I64 *_t436 = malloc(sizeof(I64)); *_t436 = I64_sub(DEREF(_t434), DEREF(_t435));
        I64_delete(_t434, &(Bool){1});
        I64_delete(_t435, &(Bool){1});
        Bool_delete(_t451, &(Bool){1});
        return _t436;
    }
    Bool_delete(_t451, &(Bool){1});
    Bool *_t452 = I64_gt(&needle->count, &self->count);
    if (DEREF(_t452)) {
        I64 *_t437 = malloc(sizeof(I64));
        *_t437 = 0;
        I64 *_t438 = malloc(sizeof(I64));
        *_t438 = 1;
        I64 *_t439 = malloc(sizeof(I64)); *_t439 = I64_sub(DEREF(_t437), DEREF(_t438));
        I64_delete(_t437, &(Bool){1});
        I64_delete(_t438, &(Bool){1});
        Bool_delete(_t452, &(Bool){1});
        return _t439;
    }
    Bool_delete(_t452, &(Bool){1});
    I64 *i = malloc(sizeof(I64));
    *i = 0;
    while (1) {
        I64 *_t447 = malloc(sizeof(I64)); *_t447 = I64_sub(self->count, needle->count);
        Bool *_wcond440 = I64_lte(i, _t447);
        I64_delete(_t447, &(Bool){1});
        if (DEREF(_wcond440)) {
        } else {
            Bool_delete(_wcond440, &(Bool){1});
            break;
        }
        Bool_delete(_wcond440, &(Bool){1});
        I64 *j = malloc(sizeof(I64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond441 = I64_lt(j, &needle->count);
            if (DEREF(_wcond441)) {
            } else {
                Bool_delete(_wcond441, &(Bool){1});
                break;
            }
            Bool_delete(_wcond441, &(Bool){1});
            I64 *_t443 = malloc(sizeof(I64)); *_t443 = I64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(self, _t443);
            U8 *bc = Str_get(needle, j);
            Bool *_t444 = U8_neq(ac, bc);
            I64_delete(_t443, &(Bool){1});
            if (DEREF(_t444)) {
                Bool *_t442 = malloc(sizeof(Bool));
                *_t442 = 0;
                *found = DEREF(_t442);
                Bool_delete(_t442, &(Bool){1});
            }
            Bool_delete(_t444, &(Bool){1});
            I64 *_t445 = malloc(sizeof(I64));
            *_t445 = 1;
            I64 *_t446 = malloc(sizeof(I64)); *_t446 = I64_add(DEREF(j), DEREF(_t445));
            I64_delete(_t445, &(Bool){1});
            *j = DEREF(_t446);
            I64_delete(_t446, &(Bool){1});
        }
        I64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            Bool_delete(found, &(Bool){1});
            return i;
        }
        Bool_delete(found, &(Bool){1});
        I64 *_t448 = malloc(sizeof(I64));
        *_t448 = 1;
        I64 *_t449 = malloc(sizeof(I64)); *_t449 = I64_add(DEREF(i), DEREF(_t448));
        I64_delete(_t448, &(Bool){1});
        *i = DEREF(_t449);
        I64_delete(_t449, &(Bool){1});
    }
    I64_delete(i, &(Bool){1});
    I64 *_t453 = malloc(sizeof(I64));
    *_t453 = 0;
    I64 *_t454 = malloc(sizeof(I64));
    *_t454 = 1;
    I64 *_t455 = malloc(sizeof(I64)); *_t455 = I64_sub(DEREF(_t453), DEREF(_t454));
    I64_delete(_t453, &(Bool){1});
    I64_delete(_t454, &(Bool){1});
    return _t455;
}

I64 * Str_rfind(Str * self, Str * needle) {
    I64 *_t473 = malloc(sizeof(I64));
    *_t473 = 0;
    Bool *_t474 = malloc(sizeof(Bool)); *_t474 = I64_eq(needle->count, DEREF(_t473));
    I64_delete(_t473, &(Bool){1});
    if (DEREF(_t474)) {
        I64 *_t456 = malloc(sizeof(I64));
        *_t456 = 0;
        I64 *_t457 = malloc(sizeof(I64));
        *_t457 = 1;
        I64 *_t458 = malloc(sizeof(I64)); *_t458 = I64_sub(DEREF(_t456), DEREF(_t457));
        I64_delete(_t456, &(Bool){1});
        I64_delete(_t457, &(Bool){1});
        Bool_delete(_t474, &(Bool){1});
        return _t458;
    }
    Bool_delete(_t474, &(Bool){1});
    Bool *_t475 = I64_gt(&needle->count, &self->count);
    if (DEREF(_t475)) {
        I64 *_t459 = malloc(sizeof(I64));
        *_t459 = 0;
        I64 *_t460 = malloc(sizeof(I64));
        *_t460 = 1;
        I64 *_t461 = malloc(sizeof(I64)); *_t461 = I64_sub(DEREF(_t459), DEREF(_t460));
        I64_delete(_t459, &(Bool){1});
        I64_delete(_t460, &(Bool){1});
        Bool_delete(_t475, &(Bool){1});
        return _t461;
    }
    Bool_delete(_t475, &(Bool){1});
    I64 *_t476 = malloc(sizeof(I64));
    *_t476 = 0;
    I64 *_t477 = malloc(sizeof(I64));
    *_t477 = 1;
    I64 *last = malloc(sizeof(I64)); *last = I64_sub(DEREF(_t476), DEREF(_t477));
    I64_delete(_t476, &(Bool){1});
    I64_delete(_t477, &(Bool){1});
    I64 *i = malloc(sizeof(I64));
    *i = 0;
    while (1) {
        I64 *_t470 = malloc(sizeof(I64)); *_t470 = I64_sub(self->count, needle->count);
        Bool *_wcond462 = I64_lte(i, _t470);
        I64_delete(_t470, &(Bool){1});
        if (DEREF(_wcond462)) {
        } else {
            Bool_delete(_wcond462, &(Bool){1});
            break;
        }
        Bool_delete(_wcond462, &(Bool){1});
        I64 *j = malloc(sizeof(I64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond463 = I64_lt(j, &needle->count);
            if (DEREF(_wcond463)) {
            } else {
                Bool_delete(_wcond463, &(Bool){1});
                break;
            }
            Bool_delete(_wcond463, &(Bool){1});
            I64 *_t465 = malloc(sizeof(I64)); *_t465 = I64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(self, _t465);
            U8 *bc = Str_get(needle, j);
            Bool *_t466 = U8_neq(ac, bc);
            I64_delete(_t465, &(Bool){1});
            if (DEREF(_t466)) {
                Bool *_t464 = malloc(sizeof(Bool));
                *_t464 = 0;
                *found = DEREF(_t464);
                Bool_delete(_t464, &(Bool){1});
            }
            Bool_delete(_t466, &(Bool){1});
            I64 *_t467 = malloc(sizeof(I64));
            *_t467 = 1;
            I64 *_t468 = malloc(sizeof(I64)); *_t468 = I64_add(DEREF(j), DEREF(_t467));
            I64_delete(_t467, &(Bool){1});
            *j = DEREF(_t468);
            I64_delete(_t468, &(Bool){1});
        }
        I64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            I64 *_t469 = I64_clone(i);
            *last = DEREF(_t469);
            I64_delete(_t469, &(Bool){1});
        }
        Bool_delete(found, &(Bool){1});
        I64 *_t471 = malloc(sizeof(I64));
        *_t471 = 1;
        I64 *_t472 = malloc(sizeof(I64)); *_t472 = I64_add(DEREF(i), DEREF(_t471));
        I64_delete(_t471, &(Bool){1});
        *i = DEREF(_t472);
        I64_delete(_t472, &(Bool){1});
    }
    I64_delete(i, &(Bool){1});
    return last;
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    I64 *_t491 = malloc(sizeof(I64));
    *_t491 = 0;
    Bool *_t492 = malloc(sizeof(Bool)); *_t492 = I64_eq(from->count, DEREF(_t491));
    I64_delete(_t491, &(Bool){1});
    if (DEREF(_t492)) {
        Str *_t478 = Str_clone(self);
        Bool_delete(_t492, &(Bool){1});
        return _t478;
    }
    Bool_delete(_t492, &(Bool){1});
    Str *result = Str_lit("", 0);
    I64 *start = malloc(sizeof(I64));
    *start = 0;
    while (1) {
        I64 *_t480 = malloc(sizeof(I64)); *_t480 = I64_sub(self->count, from->count);
        Bool *_wcond479 = I64_lte(start, _t480);
        I64_delete(_t480, &(Bool){1});
        if (DEREF(_wcond479)) {
        } else {
            Bool_delete(_wcond479, &(Bool){1});
            break;
        }
        Bool_delete(_wcond479, &(Bool){1});
        I64 *_t481 = malloc(sizeof(I64)); *_t481 = I64_sub(self->count, DEREF(start));
        Str *rest = Str_substr(self, start, _t481);
        I64_delete(_t481, &(Bool){1});
        I64 *pos = Str_find(rest, from);
        I64 *_t482 = malloc(sizeof(I64));
        *_t482 = 0;
        I64 *_t483 = malloc(sizeof(I64));
        *_t483 = 1;
        I64 *_t484 = malloc(sizeof(I64)); *_t484 = I64_sub(DEREF(_t482), DEREF(_t483));
        I64_delete(_t482, &(Bool){1});
        I64_delete(_t483, &(Bool){1});
        Bool *_t485 = malloc(sizeof(Bool)); *_t485 = I64_eq(DEREF(pos), DEREF(_t484));
        I64_delete(_t484, &(Bool){1});
        if (DEREF(_t485)) {
            result = Str_concat(result, rest);
            Bool_delete(_t485, &(Bool){1});
            I64_delete(pos, &(Bool){1});
            Str_delete(rest, &(Bool){1});
            I64_delete(start, &(Bool){1});
            return result;
        }
        Bool_delete(_t485, &(Bool){1});
        Str_delete(rest, &(Bool){1});
        Str *_t486 = Str_substr(self, start, pos);
        result = Str_concat(result, _t486);
        Str_delete(_t486, &(Bool){1});
        result = Str_concat(result, to);
        I64 *_t487 = malloc(sizeof(I64)); *_t487 = I64_add(DEREF(start), DEREF(pos));
        I64_delete(pos, &(Bool){1});
        I64 *_t488 = malloc(sizeof(I64)); *_t488 = I64_add(DEREF(_t487), from->count);
        I64_delete(_t487, &(Bool){1});
        *start = DEREF(_t488);
        I64_delete(_t488, &(Bool){1});
    }
    Bool *_t493 = I64_lt(start, &self->count);
    if (DEREF(_t493)) {
        I64 *_t489 = malloc(sizeof(I64)); *_t489 = I64_sub(self->count, DEREF(start));
        Str *_t490 = Str_substr(self, start, _t489);
        I64_delete(_t489, &(Bool){1});
        result = Str_concat(result, _t490);
        Str_delete(_t490, &(Bool){1});
    }
    Bool_delete(_t493, &(Bool){1});
    I64_delete(start, &(Bool){1});
    return result;
}

Str * Str_get_char(Str * self, I64 * i) {
    I64 *_t494 = malloc(sizeof(I64));
    *_t494 = 1;
    Str *_t495 = Str_substr(self, i, _t494);
    I64_delete(_t494, &(Bool){1});
    return _t495;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    Bool *_t498 = Str_starts_with(self, prefix);
    if (DEREF(_t498)) {
        I64 *_t496 = malloc(sizeof(I64)); *_t496 = I64_sub(self->count, prefix->count);
        Str *_t497 = Str_substr(self, &prefix->count, _t496);
        I64_delete(_t496, &(Bool){1});
        Bool_delete(_t498, &(Bool){1});
        return _t497;
    }
    Bool_delete(_t498, &(Bool){1});
    Str *_t499 = Str_clone(self);
    return _t499;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    Bool *_t503 = Str_ends_with(self, suffix);
    if (DEREF(_t503)) {
        I64 *_t500 = malloc(sizeof(I64));
        *_t500 = 0;
        I64 *_t501 = malloc(sizeof(I64)); *_t501 = I64_sub(self->count, suffix->count);
        Str *_t502 = Str_substr(self, _t500, _t501);
        I64_delete(_t500, &(Bool){1});
        I64_delete(_t501, &(Bool){1});
        Bool_delete(_t503, &(Bool){1});
        return _t502;
    }
    Bool_delete(_t503, &(Bool){1});
    Str *_t504 = Str_clone(self);
    return _t504;
}

Str * Str_from_byte(U8 * byte) {
    I64 *_t505 = malloc(sizeof(I64));
    *_t505 = 2;
    U8 *buf = malloc(DEREF(_t505));
    I64_delete(_t505, &(Bool){1});
    I64 *_t506 = malloc(sizeof(I64));
    *_t506 = 1;
    memcpy(buf, byte, DEREF(_t506));
    I64_delete(_t506, &(Bool){1});
    I64 *_t507 = malloc(sizeof(I64));
    *_t507 = 1;
    I64 *_t508 = malloc(sizeof(I64));
    *_t508 = 0;
    void *_t509 = ptr_add(buf, DEREF(_t507));
    U8 *_t510 = U8_from_i64(_t508);
    I64_delete(_t508, &(Bool){1});
    I64 *_t511 = malloc(sizeof(I64));
    *_t511 = 1;
    memcpy(_t509, _t510, DEREF(_t511));
    I64_delete(_t507, &(Bool){1});
    U8_delete(_t510, &(Bool){1});
    I64_delete(_t511, &(Bool){1});
    I64 *_t512 = malloc(sizeof(I64));
    *_t512 = 1;
    I64 *_t513 = malloc(sizeof(I64));
    *_t513 = 1;
    Str *_t514 = malloc(sizeof(Str));
    _t514->c_str = buf;
    _t514->count = DEREF(_t512);
    _t514->cap = DEREF(_t513);
    I64_delete(_t512, &(Bool){1});
    I64_delete(_t513, &(Bool){1});
    return _t514;
}

I64 * Str_to_i64(Str * self) {
    I64 *_t554 = malloc(sizeof(I64));
    *_t554 = 0;
    Bool *_t555 = malloc(sizeof(Bool)); *_t555 = I64_eq(self->count, DEREF(_t554));
    I64_delete(_t554, &(Bool){1});
    if (DEREF(_t555)) {
        Str *_t515 = Str_lit("Str", 3);
        I64 *_t516 = Str_size();
        I64 *_t517 = malloc(sizeof(I64));
        *_t517 = 1;
        Array *_va8 = Array_new(_t515, _t516, _t517);
        Str_delete(_t515, &(Bool){1});
        I64_delete(_t516, &(Bool){1});
        I64_delete(_t517, &(Bool){1});
        I64 *_t518 = malloc(sizeof(I64));
        *_t518 = 0;
        Str *_t519 = Str_lit("empty string", 12);
        Array_set(_va8, _t518, _t519);
        I64_delete(_t518, &(Bool){1});
        Str *_t520 = Str_lit("Str.to_i64", 10);
        panic(_t520, _va8);
        Str_delete(_t520, &(Bool){1});
        Array_delete(_va8, &(Bool){1});
    }
    Bool_delete(_t555, &(Bool){1});
    I64 *result = malloc(sizeof(I64));
    *result = 0;
    I64 *i = malloc(sizeof(I64));
    *i = 0;
    Bool *neg = malloc(sizeof(Bool));
    *neg = 0;
    I64 *_t556 = malloc(sizeof(I64));
    *_t556 = 0;
    U8 *first = Str_get(self, _t556);
    I64 *_t557 = malloc(sizeof(I64));
    *_t557 = 45;
    U8 *_t558 = U8_from_i64(_t557);
    I64_delete(_t557, &(Bool){1});
    Bool *_t559 = malloc(sizeof(Bool)); *_t559 = U8_eq(DEREF(first), DEREF(_t558));
    I64_delete(_t556, &(Bool){1});
    U8_delete(_t558, &(Bool){1});
    if (DEREF(_t559)) {
        Bool *_t521 = malloc(sizeof(Bool));
        *_t521 = 1;
        *neg = DEREF(_t521);
        Bool_delete(_t521, &(Bool){1});
        I64 *_t522 = malloc(sizeof(I64));
        *_t522 = 1;
        *i = DEREF(_t522);
        I64_delete(_t522, &(Bool){1});
    }
    Bool_delete(_t559, &(Bool){1});
    Bool *_t560 = malloc(sizeof(Bool)); *_t560 = I64_eq(DEREF(i), self->count);
    if (DEREF(_t560)) {
        Str *_t523 = Str_lit("Str", 3);
        I64 *_t524 = Str_size();
        I64 *_t525 = malloc(sizeof(I64));
        *_t525 = 1;
        Array *_va9 = Array_new(_t523, _t524, _t525);
        Str_delete(_t523, &(Bool){1});
        I64_delete(_t524, &(Bool){1});
        I64_delete(_t525, &(Bool){1});
        I64 *_t526 = malloc(sizeof(I64));
        *_t526 = 0;
        Str *_t527 = Str_lit("no digits", 9);
        Array_set(_va9, _t526, _t527);
        I64_delete(_t526, &(Bool){1});
        Str *_t528 = Str_lit("Str.to_i64", 10);
        panic(_t528, _va9);
        Str_delete(_t528, &(Bool){1});
        Array_delete(_va9, &(Bool){1});
    }
    Bool_delete(_t560, &(Bool){1});
    while (1) {
        Bool *_wcond529 = I64_lt(i, &self->count);
        if (DEREF(_wcond529)) {
        } else {
            Bool_delete(_wcond529, &(Bool){1});
            break;
        }
        Bool_delete(_wcond529, &(Bool){1});
        U8 *ch = Str_get(self, i);
        I64 *_t540 = malloc(sizeof(I64)); *_t540 = U8_to_i64(DEREF(ch));
        I64 *_t541 = malloc(sizeof(I64));
        *_t541 = 48;
        I64 *d = malloc(sizeof(I64)); *d = I64_sub(DEREF(_t540), DEREF(_t541));
        I64_delete(_t540, &(Bool){1});
        I64_delete(_t541, &(Bool){1});
        I64 *_t542 = malloc(sizeof(I64));
        *_t542 = 0;
        I64 *_t543 = malloc(sizeof(I64));
        *_t543 = 9;
        Bool *_t544 = I64_lt(d, _t542);
        I64_delete(_t542, &(Bool){1});
        Bool *_t545 = I64_gt(d, _t543);
        I64_delete(_t543, &(Bool){1});
        Bool *_t546 = malloc(sizeof(Bool)); *_t546 = Bool_or(DEREF(_t544), DEREF(_t545));
        Bool_delete(_t544, &(Bool){1});
        Bool_delete(_t545, &(Bool){1});
        if (DEREF(_t546)) {
            Str *_t530 = Str_lit("Str", 3);
            I64 *_t531 = Str_size();
            I64 *_t532 = malloc(sizeof(I64));
            *_t532 = 3;
            Array *_va10 = Array_new(_t530, _t531, _t532);
            Str_delete(_t530, &(Bool){1});
            I64_delete(_t531, &(Bool){1});
            I64_delete(_t532, &(Bool){1});
            I64 *_t533 = malloc(sizeof(I64));
            *_t533 = 0;
            Str *_t534 = Str_lit("invalid char in '", 17);
            Array_set(_va10, _t533, _t534);
            I64_delete(_t533, &(Bool){1});
            I64 *_t535 = malloc(sizeof(I64));
            *_t535 = 1;
            Str *_t536 = Str_clone(self);
            Array_set(_va10, _t535, _t536);
            I64_delete(_t535, &(Bool){1});
            I64 *_t537 = malloc(sizeof(I64));
            *_t537 = 2;
            Str *_t538 = Str_lit("'", 1);
            Array_set(_va10, _t537, _t538);
            I64_delete(_t537, &(Bool){1});
            Str *_t539 = Str_lit("Str.to_i64", 10);
            panic(_t539, _va10);
            Str_delete(_t539, &(Bool){1});
            Array_delete(_va10, &(Bool){1});
        }
        Bool_delete(_t546, &(Bool){1});
        I64 *_t547 = malloc(sizeof(I64));
        *_t547 = 10;
        I64 *_t548 = malloc(sizeof(I64)); *_t548 = I64_mul(DEREF(result), DEREF(_t547));
        I64_delete(_t547, &(Bool){1});
        I64 *_t549 = malloc(sizeof(I64)); *_t549 = I64_add(DEREF(_t548), DEREF(d));
        I64_delete(_t548, &(Bool){1});
        I64_delete(d, &(Bool){1});
        *result = DEREF(_t549);
        I64_delete(_t549, &(Bool){1});
        I64 *_t550 = malloc(sizeof(I64));
        *_t550 = 1;
        I64 *_t551 = malloc(sizeof(I64)); *_t551 = I64_add(DEREF(i), DEREF(_t550));
        I64_delete(_t550, &(Bool){1});
        *i = DEREF(_t551);
        I64_delete(_t551, &(Bool){1});
    }
    I64_delete(i, &(Bool){1});
    if (DEREF(neg)) {
        I64 *_t552 = malloc(sizeof(I64));
        *_t552 = 0;
        I64 *_t553 = malloc(sizeof(I64)); *_t553 = I64_sub(DEREF(_t552), DEREF(result));
        I64_delete(_t552, &(Bool){1});
        Bool_delete(neg, &(Bool){1});
        I64_delete(result, &(Bool){1});
        return _t553;
    }
    Bool_delete(neg, &(Bool){1});
    return result;
}

I64 *Str_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    I64 *_t562 = Str_cmp(a, b);
    I64 *_t563 = malloc(sizeof(I64));
    *_t563 = 0;
    Bool *_t564 = malloc(sizeof(Bool)); *_t564 = I64_eq(DEREF(_t562), DEREF(_t563));
    I64_delete(_t562, &(Bool){1});
    I64_delete(_t563, &(Bool){1});
    return _t564;
}

Bool * Str_lt(Str * a, Str * b) {
    I64 *_t565 = malloc(sizeof(I64));
    *_t565 = 0;
    I64 *_t566 = malloc(sizeof(I64));
    *_t566 = 1;
    I64 *_t567 = Str_cmp(a, b);
    I64 *_t568 = malloc(sizeof(I64)); *_t568 = I64_sub(DEREF(_t565), DEREF(_t566));
    I64_delete(_t565, &(Bool){1});
    I64_delete(_t566, &(Bool){1});
    Bool *_t569 = malloc(sizeof(Bool)); *_t569 = I64_eq(DEREF(_t567), DEREF(_t568));
    I64_delete(_t567, &(Bool){1});
    I64_delete(_t568, &(Bool){1});
    return _t569;
}

Bool * Str_gt(Str * a, Str * b) {
    I64 *_t570 = Str_cmp(a, b);
    I64 *_t571 = malloc(sizeof(I64));
    *_t571 = 1;
    Bool *_t572 = malloc(sizeof(Bool)); *_t572 = I64_eq(DEREF(_t570), DEREF(_t571));
    I64_delete(_t570, &(Bool){1});
    I64_delete(_t571, &(Bool){1});
    return _t572;
}

Bool * Str_neq(Str * a, Str * b) {
    Bool *_t573 = Str_eq(a, b);
    Bool *_t574 = malloc(sizeof(Bool)); *_t574 = Bool_not(DEREF(_t573));
    Bool_delete(_t573, &(Bool){1});
    return _t574;
}

Bool * Str_lte(Str * a, Str * b) {
    Bool *_t575 = Str_gt(a, b);
    Bool *_t576 = malloc(sizeof(Bool)); *_t576 = Bool_not(DEREF(_t575));
    Bool_delete(_t575, &(Bool){1});
    return _t576;
}

Bool * Str_gte(Str * a, Str * b) {
    Bool *_t577 = Str_lt(a, b);
    Bool *_t578 = malloc(sizeof(Bool)); *_t578 = Bool_not(DEREF(_t577));
    Bool_delete(_t577, &(Bool){1});
    return _t578;
}

Vec * Vec_new(Str * elem_type, I64 * elem_size) {
    void *_t579 = malloc(DEREF(elem_size));
    I64 *_t580 = malloc(sizeof(I64));
    *_t580 = 0;
    I64 *_t581 = malloc(sizeof(I64));
    *_t581 = 1;
    I64 *_t582 = I64_clone(elem_size);
    Vec *_t583 = malloc(sizeof(Vec));
    _t583->data = _t579;
    _t583->count = DEREF(_t580);
    _t583->cap = DEREF(_t581);
    _t583->elem_size = DEREF(_t582);
    { Str *_ca = Str_clone(elem_type); _t583->elem_type = *_ca; free(_ca); }
    I64_delete(_t580, &(Bool){1});
    I64_delete(_t581, &(Bool){1});
    I64_delete(_t582, &(Bool){1});
    return _t583;
}

I64 * Vec_len(Vec * self) {
    { I64 *_r = malloc(sizeof(I64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    Bool *_t588 = malloc(sizeof(Bool)); *_t588 = I64_eq(self->count, self->cap);
    if (DEREF(_t588)) {
        I64 *_t584 = malloc(sizeof(I64));
        *_t584 = 2;
        I64 *new_cap = malloc(sizeof(I64)); *new_cap = I64_mul(self->cap, DEREF(_t584));
        I64_delete(_t584, &(Bool){1});
        I64 *_t585 = malloc(sizeof(I64)); *_t585 = I64_mul(DEREF(new_cap), self->elem_size);
        void *_t586 = realloc(self->data, DEREF(_t585));
        I64_delete(_t585, &(Bool){1});
        self->data = _t586;
        I64 *_t587 = I64_clone(new_cap);
        I64_delete(new_cap, &(Bool){1});
        self->cap = DEREF(_t587);
        I64_delete(_t587, &(Bool){1});
    }
    Bool_delete(_t588, &(Bool){1});
    I64 *_t589 = malloc(sizeof(I64)); *_t589 = I64_mul(self->count, self->elem_size);
    void *_t590 = ptr_add(self->data, DEREF(_t589));
    memcpy(_t590, val, self->elem_size);
    I64_delete(_t589, &(Bool){1});
    free(val);
    I64 *_t591 = malloc(sizeof(I64));
    *_t591 = 1;
    I64 *_t592 = malloc(sizeof(I64)); *_t592 = I64_add(self->count, DEREF(_t591));
    I64_delete(_t591, &(Bool){1});
    self->count = DEREF(_t592);
    I64_delete(_t592, &(Bool){1});
}

void * Vec_get(Vec * self, I64 * i) {
    I64 *_t607 = malloc(sizeof(I64));
    *_t607 = 0;
    Bool *_t608 = I64_lt(i, _t607);
    I64_delete(_t607, &(Bool){1});
    Bool *_t609 = I64_gte(i, &self->count);
    Bool *_t610 = malloc(sizeof(Bool)); *_t610 = Bool_or(DEREF(_t608), DEREF(_t609));
    Bool_delete(_t608, &(Bool){1});
    Bool_delete(_t609, &(Bool){1});
    if (DEREF(_t610)) {
        Str *_t593 = Str_lit("Str", 3);
        I64 *_t594 = Str_size();
        I64 *_t595 = malloc(sizeof(I64));
        *_t595 = 5;
        Array *_va11 = Array_new(_t593, _t594, _t595);
        Str_delete(_t593, &(Bool){1});
        I64_delete(_t594, &(Bool){1});
        I64_delete(_t595, &(Bool){1});
        I64 *_t596 = malloc(sizeof(I64));
        *_t596 = 0;
        Str *_t597 = Str_lit("index ", 6);
        Array_set(_va11, _t596, _t597);
        I64_delete(_t596, &(Bool){1});
        I64 *_t598 = malloc(sizeof(I64));
        *_t598 = 1;
        Str *_t599 = I64_to_str(i);
        Array_set(_va11, _t598, _t599);
        I64_delete(_t598, &(Bool){1});
        I64 *_t600 = malloc(sizeof(I64));
        *_t600 = 2;
        Str *_t601 = Str_lit(" out of bounds (len ", 20);
        Array_set(_va11, _t600, _t601);
        I64_delete(_t600, &(Bool){1});
        I64 *_t602 = malloc(sizeof(I64));
        *_t602 = 3;
        Str *_t603 = I64_to_str(&self->count);
        Array_set(_va11, _t602, _t603);
        I64_delete(_t602, &(Bool){1});
        I64 *_t604 = malloc(sizeof(I64));
        *_t604 = 4;
        Str *_t605 = Str_lit(")", 1);
        Array_set(_va11, _t604, _t605);
        I64_delete(_t604, &(Bool){1});
        Str *_t606 = Str_lit("Vec.get", 7);
        panic(_t606, _va11);
        Str_delete(_t606, &(Bool){1});
        Array_delete(_va11, &(Bool){1});
    }
    Bool_delete(_t610, &(Bool){1});
    I64 *_t611 = malloc(sizeof(I64)); *_t611 = I64_mul(DEREF(i), self->elem_size);
    void *_t612 = ptr_add(self->data, DEREF(_t611));
    I64_delete(_t611, &(Bool){1});
    return _t612;
}

void Vec_delete(Vec * self, Bool * call_free) {
    {
        I64 *_fi613 = malloc(sizeof(I64));
        *_fi613 = 0;
        while (1) {
            I64 *_t615 = malloc(sizeof(I64));
            *_t615 = 0;
            Range *_t616 = Range_new(_t615, &self->count);
            I64_delete(_t615, &(Bool){1});
            I64 *_t617 = Range_len(_t616);
            Range_delete(_t616, &(Bool){1});
            Bool *_wcond614 = I64_lt(_fi613, _t617);
            I64_delete(_t617, &(Bool){1});
            if (DEREF(_wcond614)) {
            } else {
                Bool_delete(_wcond614, &(Bool){1});
                break;
            }
            Bool_delete(_wcond614, &(Bool){1});
            I64 *_t618 = malloc(sizeof(I64));
            *_t618 = 0;
            Range *_t619 = Range_new(_t618, &self->count);
            I64_delete(_t618, &(Bool){1});
            I64 *i = Range_get(_t619, _fi613);
            Range_delete(_t619, &(Bool){1});
            I64 *_t620 = malloc(sizeof(I64));
            *_t620 = 1;
            I64 *_t621 = malloc(sizeof(I64)); *_t621 = I64_add(DEREF(_fi613), DEREF(_t620));
            I64_delete(_t620, &(Bool){1});
            *_fi613 = DEREF(_t621);
            I64_delete(_t621, &(Bool){1});
            I64 *_t622 = malloc(sizeof(I64)); *_t622 = I64_mul(DEREF(i), self->elem_size);
            I64_delete(i, &(Bool){1});
            void *_t623 = ptr_add(self->data, DEREF(_t622));
            Bool *_t624 = malloc(sizeof(Bool));
            *_t624 = 0;
            dyn_call_delete(&self->elem_type, _t623, _t624);
            I64_delete(_t622, &(Bool){1});
            Bool_delete(_t624, &(Bool){1});
        }
        I64_delete(_fi613, &(Bool){1});
    }
    free(self->data);
    Bool *_t625 = malloc(sizeof(Bool));
    *_t625 = 0;
    Str_delete(&self->elem_type, _t625);
    Bool_delete(_t625, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    I64 *_t639 = malloc(sizeof(I64)); *_t639 = I64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t639));
    I64_delete(_t639, &(Bool){1});
    {
        I64 *_fi626 = malloc(sizeof(I64));
        *_fi626 = 0;
        while (1) {
            I64 *_t628 = malloc(sizeof(I64));
            *_t628 = 0;
            Range *_t629 = Range_new(_t628, &self->count);
            I64_delete(_t628, &(Bool){1});
            I64 *_t630 = Range_len(_t629);
            Range_delete(_t629, &(Bool){1});
            Bool *_wcond627 = I64_lt(_fi626, _t630);
            I64_delete(_t630, &(Bool){1});
            if (DEREF(_wcond627)) {
            } else {
                Bool_delete(_wcond627, &(Bool){1});
                break;
            }
            Bool_delete(_wcond627, &(Bool){1});
            I64 *_t631 = malloc(sizeof(I64));
            *_t631 = 0;
            Range *_t632 = Range_new(_t631, &self->count);
            I64_delete(_t631, &(Bool){1});
            I64 *i = Range_get(_t632, _fi626);
            Range_delete(_t632, &(Bool){1});
            I64 *_t633 = malloc(sizeof(I64));
            *_t633 = 1;
            I64 *_t634 = malloc(sizeof(I64)); *_t634 = I64_add(DEREF(_fi626), DEREF(_t633));
            I64_delete(_t633, &(Bool){1});
            *_fi626 = DEREF(_t634);
            I64_delete(_t634, &(Bool){1});
            I64 *_t635 = malloc(sizeof(I64)); *_t635 = I64_mul(DEREF(i), self->elem_size);
            void *_t636 = ptr_add(self->data, DEREF(_t635));
            void *cloned = dyn_call_clone(&self->elem_type, _t636);
            I64_delete(_t635, &(Bool){1});
            I64 *_t637 = malloc(sizeof(I64)); *_t637 = I64_mul(DEREF(i), self->elem_size);
            I64_delete(i, &(Bool){1});
            void *_t638 = ptr_add(new_data, DEREF(_t637));
            memcpy(_t638, cloned, self->elem_size);
            I64_delete(_t637, &(Bool){1});
            free(cloned);
        }
        I64_delete(_fi626, &(Bool){1});
    }
    Vec *_t640 = malloc(sizeof(Vec));
    _t640->data = new_data;
    _t640->count = self->count;
    _t640->cap = self->cap;
    _t640->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t640->elem_type = *_ca; free(_ca); }
    return _t640;
}

I64 *Vec_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    Str *_t658 = Str_lit("Str", 3);
    I64 *_t659 = Str_size();
    Vec *parts = Vec_new(_t658, _t659);
    Str_delete(_t658, &(Bool){1});
    I64_delete(_t659, &(Bool){1});
    I64 *_t660 = Str_len(delim);
    I64 *_t661 = malloc(sizeof(I64));
    *_t661 = 0;
    Bool *_t662 = malloc(sizeof(Bool)); *_t662 = I64_eq(DEREF(_t660), DEREF(_t661));
    I64_delete(_t660, &(Bool){1});
    I64_delete(_t661, &(Bool){1});
    if (DEREF(_t662)) {
        Str *_t642 = Str_clone(s);
        Vec_push(parts, _t642);
        Bool_delete(_t662, &(Bool){1});
        return parts;
    }
    Bool_delete(_t662, &(Bool){1});
    I64 *start = malloc(sizeof(I64));
    *start = 0;
    I64 *pos = malloc(sizeof(I64));
    *pos = 0;
    while (1) {
        I64 *_t652 = Str_len(s);
        I64 *_t653 = Str_len(delim);
        I64 *_t654 = malloc(sizeof(I64)); *_t654 = I64_sub(DEREF(_t652), DEREF(_t653));
        I64_delete(_t652, &(Bool){1});
        I64_delete(_t653, &(Bool){1});
        Bool *_wcond643 = I64_lte(pos, _t654);
        I64_delete(_t654, &(Bool){1});
        if (DEREF(_wcond643)) {
        } else {
            Bool_delete(_wcond643, &(Bool){1});
            break;
        }
        Bool_delete(_wcond643, &(Bool){1});
        I64 *_t655 = Str_len(delim);
        Str *_t656 = Str_substr(s, pos, _t655);
        I64_delete(_t655, &(Bool){1});
        Bool *_t657 = Str_eq(_t656, delim);
        Str_delete(_t656, &(Bool){1});
        if (DEREF(_t657)) {
            I64 *_t644 = malloc(sizeof(I64)); *_t644 = I64_sub(DEREF(pos), DEREF(start));
            Str *_t645 = Str_substr(s, start, _t644);
            I64_delete(_t644, &(Bool){1});
            Str *_t646 = Str_clone(_t645);
            Str_delete(_t645, &(Bool){1});
            Vec_push(parts, _t646);
            I64 *_t647 = Str_len(delim);
            I64 *_t648 = malloc(sizeof(I64)); *_t648 = I64_add(DEREF(pos), DEREF(_t647));
            I64_delete(_t647, &(Bool){1});
            *start = DEREF(_t648);
            I64_delete(_t648, &(Bool){1});
            I64 *_t649 = I64_clone(start);
            *pos = DEREF(_t649);
            I64_delete(_t649, &(Bool){1});
        } else {
            I64 *_t650 = malloc(sizeof(I64));
            *_t650 = 1;
            I64 *_t651 = malloc(sizeof(I64)); *_t651 = I64_add(DEREF(pos), DEREF(_t650));
            I64_delete(_t650, &(Bool){1});
            *pos = DEREF(_t651);
            I64_delete(_t651, &(Bool){1});
        }
        Bool_delete(_t657, &(Bool){1});
    }
    I64_delete(pos, &(Bool){1});
    I64 *_t663 = Str_len(s);
    I64 *_t664 = malloc(sizeof(I64)); *_t664 = I64_sub(DEREF(_t663), DEREF(start));
    I64_delete(_t663, &(Bool){1});
    Str *_t665 = Str_substr(s, start, _t664);
    I64_delete(_t664, &(Bool){1});
    I64_delete(start, &(Bool){1});
    Str *_t666 = Str_clone(_t665);
    Str_delete(_t665, &(Bool){1});
    Vec_push(parts, _t666);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    I64 *_t674 = Vec_len(parts);
    I64 *_t675 = malloc(sizeof(I64));
    *_t675 = 0;
    Bool *_t676 = malloc(sizeof(Bool)); *_t676 = I64_eq(DEREF(_t674), DEREF(_t675));
    I64_delete(_t674, &(Bool){1});
    I64_delete(_t675, &(Bool){1});
    if (DEREF(_t676)) {
        Str *_t667 = Str_lit("", 0);
        Bool_delete(_t676, &(Bool){1});
        return _t667;
    }
    Bool_delete(_t676, &(Bool){1});
    Str *result = Str_lit("", 0);
    I64 *i = malloc(sizeof(I64));
    *i = 0;
    while (1) {
        I64 *_t669 = Vec_len(parts);
        Bool *_wcond668 = I64_lt(i, _t669);
        I64_delete(_t669, &(Bool){1});
        if (DEREF(_wcond668)) {
        } else {
            Bool_delete(_wcond668, &(Bool){1});
            break;
        }
        Bool_delete(_wcond668, &(Bool){1});
        I64 *_t670 = malloc(sizeof(I64));
        *_t670 = 0;
        Bool *_t671 = I64_gt(i, _t670);
        I64_delete(_t670, &(Bool){1});
        if (DEREF(_t671)) {
            result = Str_concat(result, sep);
        }
        Bool_delete(_t671, &(Bool){1});
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        I64 *_t672 = malloc(sizeof(I64));
        *_t672 = 1;
        I64 *_t673 = malloc(sizeof(I64)); *_t673 = I64_add(DEREF(i), DEREF(_t672));
        I64_delete(_t672, &(Bool){1});
        *i = DEREF(_t673);
        I64_delete(_t673, &(Bool){1});
    }
    I64_delete(i, &(Bool){1});
    return result;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *_t677 = malloc(sizeof(EnumDef));
    return _t677;
}

void EnumDef_delete(EnumDef * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

I64 *EnumDef_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(EnumDef);
    return r;
}

Str * U8_to_str(U8 * val) {
    I64 *_t679 = malloc(sizeof(I64)); *_t679 = U8_to_i64(DEREF(val));
    Str *_t680 = I64_to_str(_t679);
    I64_delete(_t679, &(Bool){1});
    return _t680;
}

U8 * U8_from_i64(I64 * val) {
    I64 *_t687 = malloc(sizeof(I64));
    *_t687 = 0;
    I64 *_t688 = malloc(sizeof(I64));
    *_t688 = 255;
    Bool *_t689 = I64_lt(val, _t687);
    I64_delete(_t687, &(Bool){1});
    Bool *_t690 = I64_gt(val, _t688);
    I64_delete(_t688, &(Bool){1});
    Bool *_t691 = malloc(sizeof(Bool)); *_t691 = Bool_or(DEREF(_t689), DEREF(_t690));
    Bool_delete(_t689, &(Bool){1});
    Bool_delete(_t690, &(Bool){1});
    if (DEREF(_t691)) {
        Str *_t681 = Str_lit("Str", 3);
        I64 *_t682 = Str_size();
        I64 *_t683 = malloc(sizeof(I64));
        *_t683 = 1;
        Array *_va12 = Array_new(_t681, _t682, _t683);
        Str_delete(_t681, &(Bool){1});
        I64_delete(_t682, &(Bool){1});
        I64_delete(_t683, &(Bool){1});
        I64 *_t684 = malloc(sizeof(I64));
        *_t684 = 0;
        Str *_t685 = Str_lit("value out of range (0-255)", 26);
        Array_set(_va12, _t684, _t685);
        I64_delete(_t684, &(Bool){1});
        Str *_t686 = Str_lit("U8.from_i64", 11);
        panic(_t686, _va12);
        Str_delete(_t686, &(Bool){1});
        Array_delete(_va12, &(Bool){1});
    }
    Bool_delete(_t691, &(Bool){1});
    /* TODO: nested func U8_from_i64_ext */
    U8 *_t692 = U8_from_i64_ext(val);
    return _t692;
}

I64 *U8_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(U8);
    return r;
}

Bool * U8_lt(U8 * a, U8 * b) {
    I64 *_t694 = malloc(sizeof(I64));
    *_t694 = 0;
    I64 *_t695 = malloc(sizeof(I64));
    *_t695 = 1;
    I64 *_t696 = malloc(sizeof(I64)); *_t696 = U8_cmp(DEREF(a), DEREF(b));
    I64 *_t697 = malloc(sizeof(I64)); *_t697 = I64_sub(DEREF(_t694), DEREF(_t695));
    I64_delete(_t694, &(Bool){1});
    I64_delete(_t695, &(Bool){1});
    Bool *_t698 = malloc(sizeof(Bool)); *_t698 = I64_eq(DEREF(_t696), DEREF(_t697));
    I64_delete(_t696, &(Bool){1});
    I64_delete(_t697, &(Bool){1});
    return _t698;
}

Bool * U8_gt(U8 * a, U8 * b) {
    I64 *_t699 = malloc(sizeof(I64)); *_t699 = U8_cmp(DEREF(a), DEREF(b));
    I64 *_t700 = malloc(sizeof(I64));
    *_t700 = 1;
    Bool *_t701 = malloc(sizeof(Bool)); *_t701 = I64_eq(DEREF(_t699), DEREF(_t700));
    I64_delete(_t699, &(Bool){1});
    I64_delete(_t700, &(Bool){1});
    return _t701;
}

Bool * U8_neq(U8 * a, U8 * b) {
    Bool *_t702 = malloc(sizeof(Bool)); *_t702 = U8_eq(DEREF(a), DEREF(b));
    Bool *_t703 = malloc(sizeof(Bool)); *_t703 = Bool_not(DEREF(_t702));
    Bool_delete(_t702, &(Bool){1});
    return _t703;
}

Bool * U8_lte(U8 * a, U8 * b) {
    Bool *_t704 = U8_gt(a, b);
    Bool *_t705 = malloc(sizeof(Bool)); *_t705 = Bool_not(DEREF(_t704));
    Bool_delete(_t704, &(Bool){1});
    return _t705;
}

Bool * U8_gte(U8 * a, U8 * b) {
    Bool *_t706 = U8_lt(a, b);
    Bool *_t707 = malloc(sizeof(Bool)); *_t707 = Bool_not(DEREF(_t706));
    Bool_delete(_t706, &(Bool){1});
    return _t707;
}

Str * I16_to_str(I16 * val) {
    I64 *_t708 = malloc(sizeof(I64)); *_t708 = I16_to_i64(DEREF(val));
    Str *_t709 = I64_to_str(_t708);
    I64_delete(_t708, &(Bool){1});
    return _t709;
}

I16 * I16_from_i64(I64 * val) {
    I64 *_t716 = malloc(sizeof(I64));
    *_t716 = 32768;
    I64 *_t717 = I64_neg(_t716);
    I64_delete(_t716, &(Bool){1});
    I64 *_t718 = malloc(sizeof(I64));
    *_t718 = 32767;
    Bool *_t719 = I64_lt(val, _t717);
    I64_delete(_t717, &(Bool){1});
    Bool *_t720 = I64_gt(val, _t718);
    I64_delete(_t718, &(Bool){1});
    Bool *_t721 = malloc(sizeof(Bool)); *_t721 = Bool_or(DEREF(_t719), DEREF(_t720));
    Bool_delete(_t719, &(Bool){1});
    Bool_delete(_t720, &(Bool){1});
    if (DEREF(_t721)) {
        Str *_t710 = Str_lit("Str", 3);
        I64 *_t711 = Str_size();
        I64 *_t712 = malloc(sizeof(I64));
        *_t712 = 1;
        Array *_va13 = Array_new(_t710, _t711, _t712);
        Str_delete(_t710, &(Bool){1});
        I64_delete(_t711, &(Bool){1});
        I64_delete(_t712, &(Bool){1});
        I64 *_t713 = malloc(sizeof(I64));
        *_t713 = 0;
        Str *_t714 = Str_lit("value out of range (-32768 to 32767)", 36);
        Array_set(_va13, _t713, _t714);
        I64_delete(_t713, &(Bool){1});
        Str *_t715 = Str_lit("I16.from_i64", 12);
        panic(_t715, _va13);
        Str_delete(_t715, &(Bool){1});
        Array_delete(_va13, &(Bool){1});
    }
    Bool_delete(_t721, &(Bool){1});
    /* TODO: nested func I16_from_i64_ext */
    I16 *_t722 = I16_from_i64_ext(val);
    return _t722;
}

I16 * I16_neg(I16 * a) {
    I64 *_t723 = malloc(sizeof(I64));
    *_t723 = 0;
    I64 *_t724 = malloc(sizeof(I64)); *_t724 = I16_to_i64(DEREF(a));
    I64 *_t725 = malloc(sizeof(I64)); *_t725 = I64_sub(DEREF(_t723), DEREF(_t724));
    I64_delete(_t723, &(Bool){1});
    I64_delete(_t724, &(Bool){1});
    I16 *_t726 = I16_from_i64(_t725);
    I64_delete(_t725, &(Bool){1});
    return _t726;
}

I16 * I16_abs(I16 * a) {
    I64 *_t731 = malloc(sizeof(I64)); *_t731 = I16_to_i64(DEREF(a));
    I64 *_t732 = malloc(sizeof(I64));
    *_t732 = 0;
    Bool *_t733 = I64_lt(_t731, _t732);
    I64_delete(_t731, &(Bool){1});
    I64_delete(_t732, &(Bool){1});
    if (DEREF(_t733)) {
        I64 *_t727 = malloc(sizeof(I64));
        *_t727 = 0;
        I64 *_t728 = malloc(sizeof(I64)); *_t728 = I16_to_i64(DEREF(a));
        I64 *_t729 = malloc(sizeof(I64)); *_t729 = I64_sub(DEREF(_t727), DEREF(_t728));
        I64_delete(_t727, &(Bool){1});
        I64_delete(_t728, &(Bool){1});
        I16 *_t730 = I16_from_i64(_t729);
        I64_delete(_t729, &(Bool){1});
        Bool_delete(_t733, &(Bool){1});
        return _t730;
    }
    Bool_delete(_t733, &(Bool){1});
    I16 *_t734 = I16_clone(a);
    return _t734;
}

I64 *I16_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(I16);
    return r;
}

Bool * I16_lt(I16 * a, I16 * b) {
    I64 *_t736 = malloc(sizeof(I64));
    *_t736 = 0;
    I64 *_t737 = malloc(sizeof(I64));
    *_t737 = 1;
    I64 *_t738 = malloc(sizeof(I64)); *_t738 = I16_cmp(DEREF(a), DEREF(b));
    I64 *_t739 = malloc(sizeof(I64)); *_t739 = I64_sub(DEREF(_t736), DEREF(_t737));
    I64_delete(_t736, &(Bool){1});
    I64_delete(_t737, &(Bool){1});
    Bool *_t740 = malloc(sizeof(Bool)); *_t740 = I64_eq(DEREF(_t738), DEREF(_t739));
    I64_delete(_t738, &(Bool){1});
    I64_delete(_t739, &(Bool){1});
    return _t740;
}

Bool * I16_gt(I16 * a, I16 * b) {
    I64 *_t741 = malloc(sizeof(I64)); *_t741 = I16_cmp(DEREF(a), DEREF(b));
    I64 *_t742 = malloc(sizeof(I64));
    *_t742 = 1;
    Bool *_t743 = malloc(sizeof(Bool)); *_t743 = I64_eq(DEREF(_t741), DEREF(_t742));
    I64_delete(_t741, &(Bool){1});
    I64_delete(_t742, &(Bool){1});
    return _t743;
}

Bool * I16_neq(I16 * a, I16 * b) {
    Bool *_t744 = malloc(sizeof(Bool)); *_t744 = I16_eq(DEREF(a), DEREF(b));
    Bool *_t745 = malloc(sizeof(Bool)); *_t745 = Bool_not(DEREF(_t744));
    Bool_delete(_t744, &(Bool){1});
    return _t745;
}

Bool * I16_lte(I16 * a, I16 * b) {
    Bool *_t746 = I16_gt(a, b);
    Bool *_t747 = malloc(sizeof(Bool)); *_t747 = Bool_not(DEREF(_t746));
    Bool_delete(_t746, &(Bool){1});
    return _t747;
}

Bool * I16_gte(I16 * a, I16 * b) {
    Bool *_t748 = I16_lt(a, b);
    Bool *_t749 = malloc(sizeof(Bool)); *_t749 = Bool_not(DEREF(_t748));
    Bool_delete(_t748, &(Bool){1});
    return _t749;
}

Str * I32_to_str(I32 * val) {
    I64 *_t750 = malloc(sizeof(I64)); *_t750 = I32_to_i64(DEREF(val));
    Str *_t751 = I64_to_str(_t750);
    I64_delete(_t750, &(Bool){1});
    return _t751;
}

I32 * I32_from_i64(I64 * val) {
    I64 *_t758 = malloc(sizeof(I64));
    *_t758 = 2147483648;
    I64 *_t759 = I64_neg(_t758);
    I64_delete(_t758, &(Bool){1});
    I64 *_t760 = malloc(sizeof(I64));
    *_t760 = 2147483647;
    Bool *_t761 = I64_lt(val, _t759);
    I64_delete(_t759, &(Bool){1});
    Bool *_t762 = I64_gt(val, _t760);
    I64_delete(_t760, &(Bool){1});
    Bool *_t763 = malloc(sizeof(Bool)); *_t763 = Bool_or(DEREF(_t761), DEREF(_t762));
    Bool_delete(_t761, &(Bool){1});
    Bool_delete(_t762, &(Bool){1});
    if (DEREF(_t763)) {
        Str *_t752 = Str_lit("Str", 3);
        I64 *_t753 = Str_size();
        I64 *_t754 = malloc(sizeof(I64));
        *_t754 = 1;
        Array *_va14 = Array_new(_t752, _t753, _t754);
        Str_delete(_t752, &(Bool){1});
        I64_delete(_t753, &(Bool){1});
        I64_delete(_t754, &(Bool){1});
        I64 *_t755 = malloc(sizeof(I64));
        *_t755 = 0;
        Str *_t756 = Str_lit("value out of range (-2147483648 to 2147483647)", 46);
        Array_set(_va14, _t755, _t756);
        I64_delete(_t755, &(Bool){1});
        Str *_t757 = Str_lit("I32.from_i64", 12);
        panic(_t757, _va14);
        Str_delete(_t757, &(Bool){1});
        Array_delete(_va14, &(Bool){1});
    }
    Bool_delete(_t763, &(Bool){1});
    /* TODO: nested func I32_from_i64_ext */
    I32 *_t764 = I32_from_i64_ext(val);
    return _t764;
}

I32 * I32_neg(I32 * a) {
    I64 *_t765 = malloc(sizeof(I64));
    *_t765 = 0;
    I64 *_t766 = malloc(sizeof(I64)); *_t766 = I32_to_i64(DEREF(a));
    I64 *_t767 = malloc(sizeof(I64)); *_t767 = I64_sub(DEREF(_t765), DEREF(_t766));
    I64_delete(_t765, &(Bool){1});
    I64_delete(_t766, &(Bool){1});
    I32 *_t768 = I32_from_i64(_t767);
    I64_delete(_t767, &(Bool){1});
    return _t768;
}

I32 * I32_abs(I32 * a) {
    I64 *_t773 = malloc(sizeof(I64)); *_t773 = I32_to_i64(DEREF(a));
    I64 *_t774 = malloc(sizeof(I64));
    *_t774 = 0;
    Bool *_t775 = I64_lt(_t773, _t774);
    I64_delete(_t773, &(Bool){1});
    I64_delete(_t774, &(Bool){1});
    if (DEREF(_t775)) {
        I64 *_t769 = malloc(sizeof(I64));
        *_t769 = 0;
        I64 *_t770 = malloc(sizeof(I64)); *_t770 = I32_to_i64(DEREF(a));
        I64 *_t771 = malloc(sizeof(I64)); *_t771 = I64_sub(DEREF(_t769), DEREF(_t770));
        I64_delete(_t769, &(Bool){1});
        I64_delete(_t770, &(Bool){1});
        I32 *_t772 = I32_from_i64(_t771);
        I64_delete(_t771, &(Bool){1});
        Bool_delete(_t775, &(Bool){1});
        return _t772;
    }
    Bool_delete(_t775, &(Bool){1});
    I32 *_t776 = I32_clone(a);
    return _t776;
}

I64 *I32_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(I32);
    return r;
}

Bool * I32_lt(I32 * a, I32 * b) {
    I64 *_t778 = malloc(sizeof(I64));
    *_t778 = 0;
    I64 *_t779 = malloc(sizeof(I64));
    *_t779 = 1;
    I64 *_t780 = malloc(sizeof(I64)); *_t780 = I32_cmp(DEREF(a), DEREF(b));
    I64 *_t781 = malloc(sizeof(I64)); *_t781 = I64_sub(DEREF(_t778), DEREF(_t779));
    I64_delete(_t778, &(Bool){1});
    I64_delete(_t779, &(Bool){1});
    Bool *_t782 = malloc(sizeof(Bool)); *_t782 = I64_eq(DEREF(_t780), DEREF(_t781));
    I64_delete(_t780, &(Bool){1});
    I64_delete(_t781, &(Bool){1});
    return _t782;
}

Bool * I32_gt(I32 * a, I32 * b) {
    I64 *_t783 = malloc(sizeof(I64)); *_t783 = I32_cmp(DEREF(a), DEREF(b));
    I64 *_t784 = malloc(sizeof(I64));
    *_t784 = 1;
    Bool *_t785 = malloc(sizeof(Bool)); *_t785 = I64_eq(DEREF(_t783), DEREF(_t784));
    I64_delete(_t783, &(Bool){1});
    I64_delete(_t784, &(Bool){1});
    return _t785;
}

Bool * I32_neq(I32 * a, I32 * b) {
    Bool *_t786 = malloc(sizeof(Bool)); *_t786 = I32_eq(DEREF(a), DEREF(b));
    Bool *_t787 = malloc(sizeof(Bool)); *_t787 = Bool_not(DEREF(_t786));
    Bool_delete(_t786, &(Bool){1});
    return _t787;
}

Bool * I32_lte(I32 * a, I32 * b) {
    Bool *_t788 = I32_gt(a, b);
    Bool *_t789 = malloc(sizeof(Bool)); *_t789 = Bool_not(DEREF(_t788));
    Bool_delete(_t788, &(Bool){1});
    return _t789;
}

Bool * I32_gte(I32 * a, I32 * b) {
    Bool *_t790 = I32_lt(a, b);
    Bool *_t791 = malloc(sizeof(Bool)); *_t791 = Bool_not(DEREF(_t790));
    Bool_delete(_t790, &(Bool){1});
    return _t791;
}

F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 *_t792 = F32_from_i64_ext(val);
    return _t792;
}

I64 *F32_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(F32);
    return r;
}

Bool * F32_lt(F32 * a, F32 * b) {
    I64 *_t794 = malloc(sizeof(I64));
    *_t794 = 0;
    I64 *_t795 = malloc(sizeof(I64));
    *_t795 = 1;
    I64 *_t796 = malloc(sizeof(I64)); *_t796 = F32_cmp(DEREF(a), DEREF(b));
    I64 *_t797 = malloc(sizeof(I64)); *_t797 = I64_sub(DEREF(_t794), DEREF(_t795));
    I64_delete(_t794, &(Bool){1});
    I64_delete(_t795, &(Bool){1});
    Bool *_t798 = malloc(sizeof(Bool)); *_t798 = I64_eq(DEREF(_t796), DEREF(_t797));
    I64_delete(_t796, &(Bool){1});
    I64_delete(_t797, &(Bool){1});
    return _t798;
}

Bool * F32_gt(F32 * a, F32 * b) {
    I64 *_t799 = malloc(sizeof(I64)); *_t799 = F32_cmp(DEREF(a), DEREF(b));
    I64 *_t800 = malloc(sizeof(I64));
    *_t800 = 1;
    Bool *_t801 = malloc(sizeof(Bool)); *_t801 = I64_eq(DEREF(_t799), DEREF(_t800));
    I64_delete(_t799, &(Bool){1});
    I64_delete(_t800, &(Bool){1});
    return _t801;
}

Bool * F32_neq(F32 * a, F32 * b) {
    Bool *_t802 = malloc(sizeof(Bool)); *_t802 = F32_eq(DEREF(a), DEREF(b));
    Bool *_t803 = malloc(sizeof(Bool)); *_t803 = Bool_not(DEREF(_t802));
    Bool_delete(_t802, &(Bool){1});
    return _t803;
}

Bool * F32_lte(F32 * a, F32 * b) {
    Bool *_t804 = F32_gt(a, b);
    Bool *_t805 = malloc(sizeof(Bool)); *_t805 = Bool_not(DEREF(_t804));
    Bool_delete(_t804, &(Bool){1});
    return _t805;
}

Bool * F32_gte(F32 * a, F32 * b) {
    Bool *_t806 = F32_lt(a, b);
    Bool *_t807 = malloc(sizeof(Bool)); *_t807 = Bool_not(DEREF(_t806));
    Bool_delete(_t806, &(Bool){1});
    return _t807;
}

Str * U32_to_str(U32 * val) {
    I64 *_t808 = malloc(sizeof(I64)); *_t808 = U32_to_i64(DEREF(val));
    Str *_t809 = I64_to_str(_t808);
    I64_delete(_t808, &(Bool){1});
    return _t809;
}

U32 * U32_from_i64(I64 * val) {
    I64 *_t816 = malloc(sizeof(I64));
    *_t816 = 0;
    I64 *_t817 = malloc(sizeof(I64));
    *_t817 = 4294967295;
    Bool *_t818 = I64_lt(val, _t816);
    I64_delete(_t816, &(Bool){1});
    Bool *_t819 = I64_gt(val, _t817);
    I64_delete(_t817, &(Bool){1});
    Bool *_t820 = malloc(sizeof(Bool)); *_t820 = Bool_or(DEREF(_t818), DEREF(_t819));
    Bool_delete(_t818, &(Bool){1});
    Bool_delete(_t819, &(Bool){1});
    if (DEREF(_t820)) {
        Str *_t810 = Str_lit("Str", 3);
        I64 *_t811 = Str_size();
        I64 *_t812 = malloc(sizeof(I64));
        *_t812 = 1;
        Array *_va15 = Array_new(_t810, _t811, _t812);
        Str_delete(_t810, &(Bool){1});
        I64_delete(_t811, &(Bool){1});
        I64_delete(_t812, &(Bool){1});
        I64 *_t813 = malloc(sizeof(I64));
        *_t813 = 0;
        Str *_t814 = Str_lit("value out of range (0-4294967295)", 33);
        Array_set(_va15, _t813, _t814);
        I64_delete(_t813, &(Bool){1});
        Str *_t815 = Str_lit("U32.from_i64", 12);
        panic(_t815, _va15);
        Str_delete(_t815, &(Bool){1});
        Array_delete(_va15, &(Bool){1});
    }
    Bool_delete(_t820, &(Bool){1});
    /* TODO: nested func U32_from_i64_ext */
    U32 *_t821 = U32_from_i64_ext(val);
    return _t821;
}

I64 *U32_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(U32);
    return r;
}

Bool * U32_lt(U32 * a, U32 * b) {
    I64 *_t823 = malloc(sizeof(I64));
    *_t823 = 0;
    I64 *_t824 = malloc(sizeof(I64));
    *_t824 = 1;
    I64 *_t825 = malloc(sizeof(I64)); *_t825 = U32_cmp(DEREF(a), DEREF(b));
    I64 *_t826 = malloc(sizeof(I64)); *_t826 = I64_sub(DEREF(_t823), DEREF(_t824));
    I64_delete(_t823, &(Bool){1});
    I64_delete(_t824, &(Bool){1});
    Bool *_t827 = malloc(sizeof(Bool)); *_t827 = I64_eq(DEREF(_t825), DEREF(_t826));
    I64_delete(_t825, &(Bool){1});
    I64_delete(_t826, &(Bool){1});
    return _t827;
}

Bool * U32_gt(U32 * a, U32 * b) {
    I64 *_t828 = malloc(sizeof(I64)); *_t828 = U32_cmp(DEREF(a), DEREF(b));
    I64 *_t829 = malloc(sizeof(I64));
    *_t829 = 1;
    Bool *_t830 = malloc(sizeof(Bool)); *_t830 = I64_eq(DEREF(_t828), DEREF(_t829));
    I64_delete(_t828, &(Bool){1});
    I64_delete(_t829, &(Bool){1});
    return _t830;
}

Bool * U32_neq(U32 * a, U32 * b) {
    Bool *_t831 = malloc(sizeof(Bool)); *_t831 = U32_eq(DEREF(a), DEREF(b));
    Bool *_t832 = malloc(sizeof(Bool)); *_t832 = Bool_not(DEREF(_t831));
    Bool_delete(_t831, &(Bool){1});
    return _t832;
}

Bool * U32_lte(U32 * a, U32 * b) {
    Bool *_t833 = U32_gt(a, b);
    Bool *_t834 = malloc(sizeof(Bool)); *_t834 = Bool_not(DEREF(_t833));
    Bool_delete(_t833, &(Bool){1});
    return _t834;
}

Bool * U32_gte(U32 * a, U32 * b) {
    Bool *_t835 = U32_lt(a, b);
    Bool *_t836 = malloc(sizeof(Bool)); *_t836 = Bool_not(DEREF(_t835));
    Bool_delete(_t835, &(Bool){1});
    return _t836;
}

Str * I64_to_str(I64 * val) {
    I64 *_t876 = malloc(sizeof(I64));
    *_t876 = 0;
    Bool *_t877 = malloc(sizeof(Bool)); *_t877 = I64_eq(DEREF(val), DEREF(_t876));
    I64_delete(_t876, &(Bool){1});
    if (DEREF(_t877)) {
        I64 *_t837 = malloc(sizeof(I64));
        *_t837 = 2;
        U8 *buf = malloc(DEREF(_t837));
        I64_delete(_t837, &(Bool){1});
        I64 *_t838 = malloc(sizeof(I64));
        *_t838 = 48;
        U8 *_t839 = U8_from_i64(_t838);
        I64_delete(_t838, &(Bool){1});
        I64 *_t840 = malloc(sizeof(I64));
        *_t840 = 1;
        memcpy(buf, _t839, DEREF(_t840));
        U8_delete(_t839, &(Bool){1});
        I64_delete(_t840, &(Bool){1});
        I64 *_t841 = malloc(sizeof(I64));
        *_t841 = 1;
        I64 *_t842 = malloc(sizeof(I64));
        *_t842 = 0;
        void *_t843 = ptr_add(buf, DEREF(_t841));
        U8 *_t844 = U8_from_i64(_t842);
        I64_delete(_t842, &(Bool){1});
        I64 *_t845 = malloc(sizeof(I64));
        *_t845 = 1;
        memcpy(_t843, _t844, DEREF(_t845));
        I64_delete(_t841, &(Bool){1});
        U8_delete(_t844, &(Bool){1});
        I64_delete(_t845, &(Bool){1});
        I64 *_t846 = malloc(sizeof(I64));
        *_t846 = 1;
        I64 *_t847 = malloc(sizeof(I64));
        *_t847 = 1;
        Str *_t848 = malloc(sizeof(Str));
        _t848->c_str = buf;
        _t848->count = DEREF(_t846);
        _t848->cap = DEREF(_t847);
        I64_delete(_t846, &(Bool){1});
        I64_delete(_t847, &(Bool){1});
        Bool_delete(_t877, &(Bool){1});
        return _t848;
    }
    Bool_delete(_t877, &(Bool){1});
    Bool *is_neg = malloc(sizeof(Bool));
    *is_neg = 0;
    I64 *v = I64_clone(val);
    I64 *_t878 = malloc(sizeof(I64));
    *_t878 = 0;
    Bool *_t879 = I64_lt(val, _t878);
    I64_delete(_t878, &(Bool){1});
    if (DEREF(_t879)) {
        Bool *_t849 = malloc(sizeof(Bool));
        *_t849 = 1;
        *is_neg = DEREF(_t849);
        Bool_delete(_t849, &(Bool){1});
        I64 *_t850 = malloc(sizeof(I64));
        *_t850 = 0;
        I64 *_t851 = malloc(sizeof(I64)); *_t851 = I64_sub(DEREF(_t850), DEREF(val));
        I64_delete(_t850, &(Bool){1});
        *v = DEREF(_t851);
        I64_delete(_t851, &(Bool){1});
    }
    Bool_delete(_t879, &(Bool){1});
    I64 *ndigits = malloc(sizeof(I64));
    *ndigits = 0;
    I64 *tmp = I64_clone(v);
    while (1) {
        I64 *_t853 = malloc(sizeof(I64));
        *_t853 = 0;
        Bool *_wcond852 = I64_gt(tmp, _t853);
        I64_delete(_t853, &(Bool){1});
        if (DEREF(_wcond852)) {
        } else {
            Bool_delete(_wcond852, &(Bool){1});
            break;
        }
        Bool_delete(_wcond852, &(Bool){1});
        I64 *_t854 = malloc(sizeof(I64));
        *_t854 = 1;
        I64 *_t855 = malloc(sizeof(I64)); *_t855 = I64_add(DEREF(ndigits), DEREF(_t854));
        I64_delete(_t854, &(Bool){1});
        *ndigits = DEREF(_t855);
        I64_delete(_t855, &(Bool){1});
        I64 *_t856 = malloc(sizeof(I64));
        *_t856 = 10;
        I64 *_t857 = malloc(sizeof(I64)); *_t857 = I64_div(DEREF(tmp), DEREF(_t856));
        I64_delete(_t856, &(Bool){1});
        *tmp = DEREF(_t857);
        I64_delete(_t857, &(Bool){1});
    }
    I64_delete(tmp, &(Bool){1});
    I64 *total = I64_clone(ndigits);
    I64_delete(ndigits, &(Bool){1});
    if (DEREF(is_neg)) {
        I64 *_t858 = malloc(sizeof(I64));
        *_t858 = 1;
        I64 *_t859 = malloc(sizeof(I64)); *_t859 = I64_add(DEREF(total), DEREF(_t858));
        I64_delete(_t858, &(Bool){1});
        *total = DEREF(_t859);
        I64_delete(_t859, &(Bool){1});
    }
    I64 *_t880 = malloc(sizeof(I64));
    *_t880 = 1;
    I64 *_t881 = malloc(sizeof(I64)); *_t881 = I64_add(DEREF(total), DEREF(_t880));
    I64_delete(_t880, &(Bool){1});
    U8 *buf = malloc(DEREF(_t881));
    I64_delete(_t881, &(Bool){1});
    if (DEREF(is_neg)) {
        I64 *_t860 = malloc(sizeof(I64));
        *_t860 = 45;
        U8 *_t861 = U8_from_i64(_t860);
        I64_delete(_t860, &(Bool){1});
        I64 *_t862 = malloc(sizeof(I64));
        *_t862 = 1;
        memcpy(buf, _t861, DEREF(_t862));
        U8_delete(_t861, &(Bool){1});
        I64_delete(_t862, &(Bool){1});
    }
    Bool_delete(is_neg, &(Bool){1});
    I64 *_t882 = malloc(sizeof(I64));
    *_t882 = 1;
    I64 *i = malloc(sizeof(I64)); *i = I64_sub(DEREF(total), DEREF(_t882));
    I64_delete(_t882, &(Bool){1});
    while (1) {
        I64 *_t864 = malloc(sizeof(I64));
        *_t864 = 0;
        Bool *_wcond863 = I64_gt(v, _t864);
        I64_delete(_t864, &(Bool){1});
        if (DEREF(_wcond863)) {
        } else {
            Bool_delete(_wcond863, &(Bool){1});
            break;
        }
        Bool_delete(_wcond863, &(Bool){1});
        I64 *_t865 = malloc(sizeof(I64));
        *_t865 = 10;
        I64 *_t866 = malloc(sizeof(I64)); *_t866 = I64_mod(DEREF(v), DEREF(_t865));
        I64_delete(_t865, &(Bool){1});
        I64 *_t867 = malloc(sizeof(I64));
        *_t867 = 48;
        I64 *_t868 = malloc(sizeof(I64)); *_t868 = I64_add(DEREF(_t866), DEREF(_t867));
        I64_delete(_t866, &(Bool){1});
        I64_delete(_t867, &(Bool){1});
        void *_t869 = ptr_add(buf, DEREF(i));
        U8 *_t870 = U8_from_i64(_t868);
        I64_delete(_t868, &(Bool){1});
        I64 *_t871 = malloc(sizeof(I64));
        *_t871 = 1;
        memcpy(_t869, _t870, DEREF(_t871));
        U8_delete(_t870, &(Bool){1});
        I64_delete(_t871, &(Bool){1});
        I64 *_t872 = malloc(sizeof(I64));
        *_t872 = 10;
        I64 *_t873 = malloc(sizeof(I64)); *_t873 = I64_div(DEREF(v), DEREF(_t872));
        I64_delete(_t872, &(Bool){1});
        *v = DEREF(_t873);
        I64_delete(_t873, &(Bool){1});
        I64 *_t874 = malloc(sizeof(I64));
        *_t874 = 1;
        I64 *_t875 = malloc(sizeof(I64)); *_t875 = I64_sub(DEREF(i), DEREF(_t874));
        I64_delete(_t874, &(Bool){1});
        *i = DEREF(_t875);
        I64_delete(_t875, &(Bool){1});
    }
    I64_delete(i, &(Bool){1});
    I64_delete(v, &(Bool){1});
    I64 *_t883 = malloc(sizeof(I64));
    *_t883 = 0;
    void *_t884 = ptr_add(buf, DEREF(total));
    U8 *_t885 = U8_from_i64(_t883);
    I64_delete(_t883, &(Bool){1});
    I64 *_t886 = malloc(sizeof(I64));
    *_t886 = 1;
    memcpy(_t884, _t885, DEREF(_t886));
    U8_delete(_t885, &(Bool){1});
    I64_delete(_t886, &(Bool){1});
    I64 *_t887 = I64_clone(total);
    I64 *_t888 = I64_clone(total);
    I64_delete(total, &(Bool){1});
    Str *_t889 = malloc(sizeof(Str));
    _t889->c_str = buf;
    _t889->count = DEREF(_t887);
    _t889->cap = DEREF(_t888);
    I64_delete(_t887, &(Bool){1});
    I64_delete(_t888, &(Bool){1});
    return _t889;
}

I64 * I64_neg(I64 * a) {
    I64 *_t890 = malloc(sizeof(I64));
    *_t890 = 0;
    I64 *_t891 = malloc(sizeof(I64)); *_t891 = I64_sub(DEREF(_t890), DEREF(a));
    I64_delete(_t890, &(Bool){1});
    return _t891;
}

I64 * I64_abs(I64 * a) {
    I64 *_t894 = malloc(sizeof(I64));
    *_t894 = 0;
    Bool *_t895 = I64_lt(a, _t894);
    I64_delete(_t894, &(Bool){1});
    if (DEREF(_t895)) {
        I64 *_t892 = malloc(sizeof(I64));
        *_t892 = 0;
        I64 *_t893 = malloc(sizeof(I64)); *_t893 = I64_sub(DEREF(_t892), DEREF(a));
        I64_delete(_t892, &(Bool){1});
        Bool_delete(_t895, &(Bool){1});
        return _t893;
    }
    Bool_delete(_t895, &(Bool){1});
    I64 *_t896 = I64_clone(a);
    return _t896;
}

I64 *I64_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(I64);
    return r;
}

Bool * I64_lt(I64 * a, I64 * b) {
    I64 *_t898 = malloc(sizeof(I64));
    *_t898 = 0;
    I64 *_t899 = malloc(sizeof(I64));
    *_t899 = 1;
    I64 *_t900 = malloc(sizeof(I64)); *_t900 = I64_cmp(DEREF(a), DEREF(b));
    I64 *_t901 = malloc(sizeof(I64)); *_t901 = I64_sub(DEREF(_t898), DEREF(_t899));
    I64_delete(_t898, &(Bool){1});
    I64_delete(_t899, &(Bool){1});
    Bool *_t902 = malloc(sizeof(Bool)); *_t902 = I64_eq(DEREF(_t900), DEREF(_t901));
    I64_delete(_t900, &(Bool){1});
    I64_delete(_t901, &(Bool){1});
    return _t902;
}

Bool * I64_gt(I64 * a, I64 * b) {
    I64 *_t903 = malloc(sizeof(I64)); *_t903 = I64_cmp(DEREF(a), DEREF(b));
    I64 *_t904 = malloc(sizeof(I64));
    *_t904 = 1;
    Bool *_t905 = malloc(sizeof(Bool)); *_t905 = I64_eq(DEREF(_t903), DEREF(_t904));
    I64_delete(_t903, &(Bool){1});
    I64_delete(_t904, &(Bool){1});
    return _t905;
}

Bool * I64_neq(I64 * a, I64 * b) {
    Bool *_t906 = malloc(sizeof(Bool)); *_t906 = I64_eq(DEREF(a), DEREF(b));
    Bool *_t907 = malloc(sizeof(Bool)); *_t907 = Bool_not(DEREF(_t906));
    Bool_delete(_t906, &(Bool){1});
    return _t907;
}

Bool * I64_lte(I64 * a, I64 * b) {
    Bool *_t908 = I64_gt(a, b);
    Bool *_t909 = malloc(sizeof(Bool)); *_t909 = Bool_not(DEREF(_t908));
    Bool_delete(_t908, &(Bool){1});
    return _t909;
}

Bool * I64_gte(I64 * a, I64 * b) {
    Bool *_t910 = I64_lt(a, b);
    Bool *_t911 = malloc(sizeof(Bool)); *_t911 = Bool_not(DEREF(_t910));
    Bool_delete(_t910, &(Bool){1});
    return _t911;
}

Range * Range_new(I64 * start, I64 * end) {
    I64 *_t912 = I64_clone(start);
    I64 *_t913 = I64_clone(end);
    Range *_t914 = malloc(sizeof(Range));
    _t914->start = DEREF(_t912);
    _t914->end = DEREF(_t913);
    I64_delete(_t912, &(Bool){1});
    I64_delete(_t913, &(Bool){1});
    return _t914;
}

I64 * Range_len(Range * self) {
    Bool *_t916 = I64_lte(&self->start, &self->end);
    if (DEREF(_t916)) {
        I64 *_t915 = malloc(sizeof(I64)); *_t915 = I64_sub(self->end, self->start);
        Bool_delete(_t916, &(Bool){1});
        return _t915;
    }
    Bool_delete(_t916, &(Bool){1});
    I64 *_t917 = malloc(sizeof(I64)); *_t917 = I64_sub(self->start, self->end);
    return _t917;
}

I64 * Range_get(Range * self, I64 * i) {
    Bool *_t919 = I64_lte(&self->start, &self->end);
    if (DEREF(_t919)) {
        I64 *_t918 = malloc(sizeof(I64)); *_t918 = I64_add(self->start, DEREF(i));
        Bool_delete(_t919, &(Bool){1});
        return _t918;
    }
    Bool_delete(_t919, &(Bool){1});
    I64 *_t920 = malloc(sizeof(I64)); *_t920 = I64_sub(self->start, DEREF(i));
    return _t920;
}

Range * Range_clone(Range * val) {
    Range *_t921 = malloc(sizeof(Range));
    _t921->start = val->start;
    _t921->end = val->end;
    return _t921;
}

void Range_delete(Range * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

I64 *Range_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(Range);
    return r;
}

Str * Bool_to_str(Bool * b) {
    if (DEREF(b)) {
        Str *_t923 = Str_lit("true", 4);
        return _t923;
    } else {
        Str *_t924 = Str_lit("false", 5);
        return _t924;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool *_t929 = malloc(sizeof(Bool)); *_t929 = Bool_eq(DEREF(a), DEREF(b));
    if (DEREF(_t929)) {
        I64 *_t925 = malloc(sizeof(I64));
        *_t925 = 0;
        Bool_delete(_t929, &(Bool){1});
        return _t925;
    }
    Bool_delete(_t929, &(Bool){1});
    if (DEREF(b)) {
        I64 *_t926 = malloc(sizeof(I64));
        *_t926 = 0;
        I64 *_t927 = malloc(sizeof(I64));
        *_t927 = 1;
        I64 *_t928 = malloc(sizeof(I64)); *_t928 = I64_sub(DEREF(_t926), DEREF(_t927));
        I64_delete(_t926, &(Bool){1});
        I64_delete(_t927, &(Bool){1});
        return _t928;
    }
    I64 *_t930 = malloc(sizeof(I64));
    *_t930 = 1;
    return _t930;
}

I64 *Bool_size(void) {
    I64 *r = malloc(sizeof(I64));
    *r = (I64)sizeof(Bool);
    return r;
}

Bool * Bool_lt(Bool * a, Bool * b) {
    I64 *_t932 = malloc(sizeof(I64));
    *_t932 = 0;
    I64 *_t933 = malloc(sizeof(I64));
    *_t933 = 1;
    I64 *_t934 = Bool_cmp(a, b);
    I64 *_t935 = malloc(sizeof(I64)); *_t935 = I64_sub(DEREF(_t932), DEREF(_t933));
    I64_delete(_t932, &(Bool){1});
    I64_delete(_t933, &(Bool){1});
    Bool *_t936 = malloc(sizeof(Bool)); *_t936 = I64_eq(DEREF(_t934), DEREF(_t935));
    I64_delete(_t934, &(Bool){1});
    I64_delete(_t935, &(Bool){1});
    return _t936;
}

Bool * Bool_gt(Bool * a, Bool * b) {
    I64 *_t937 = Bool_cmp(a, b);
    I64 *_t938 = malloc(sizeof(I64));
    *_t938 = 1;
    Bool *_t939 = malloc(sizeof(Bool)); *_t939 = I64_eq(DEREF(_t937), DEREF(_t938));
    I64_delete(_t937, &(Bool){1});
    I64_delete(_t938, &(Bool){1});
    return _t939;
}

Bool * Bool_neq(Bool * a, Bool * b) {
    Bool *_t940 = malloc(sizeof(Bool)); *_t940 = Bool_eq(DEREF(a), DEREF(b));
    Bool *_t941 = malloc(sizeof(Bool)); *_t941 = Bool_not(DEREF(_t940));
    Bool_delete(_t940, &(Bool){1});
    return _t941;
}

Bool * Bool_lte(Bool * a, Bool * b) {
    Bool *_t942 = Bool_gt(a, b);
    Bool *_t943 = malloc(sizeof(Bool)); *_t943 = Bool_not(DEREF(_t942));
    Bool_delete(_t942, &(Bool){1});
    return _t943;
}

Bool * Bool_gte(Bool * a, Bool * b) {
    Bool *_t944 = Bool_lt(a, b);
    Bool *_t945 = malloc(sizeof(Bool)); *_t945 = Bool_not(DEREF(_t944));
    Bool_delete(_t944, &(Bool){1});
    return _t945;
}

void println(Array * parts) {
    {
        I64 *_fi946 = malloc(sizeof(I64));
        *_fi946 = 0;
        while (1) {
            I64 *_t948 = Array_len(parts);
            Bool *_wcond947 = I64_lt(_fi946, _t948);
            I64_delete(_t948, &(Bool){1});
            if (DEREF(_wcond947)) {
            } else {
                Bool_delete(_wcond947, &(Bool){1});
                break;
            }
            Bool_delete(_wcond947, &(Bool){1});
            Str *s = Array_get(parts, _fi946);
            I64 *_t949 = malloc(sizeof(I64));
            *_t949 = 1;
            I64 *_t950 = malloc(sizeof(I64)); *_t950 = I64_add(DEREF(_fi946), DEREF(_t949));
            I64_delete(_t949, &(Bool){1});
            *_fi946 = DEREF(_t950);
            I64_delete(_t950, &(Bool){1});
            print_single(s);
        }
        I64_delete(_fi946, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    {
        I64 *_fi951 = malloc(sizeof(I64));
        *_fi951 = 0;
        while (1) {
            I64 *_t953 = Array_len(parts);
            Bool *_wcond952 = I64_lt(_fi951, _t953);
            I64_delete(_t953, &(Bool){1});
            if (DEREF(_wcond952)) {
            } else {
                Bool_delete(_wcond952, &(Bool){1});
                break;
            }
            Bool_delete(_wcond952, &(Bool){1});
            Str *s = Array_get(parts, _fi951);
            I64 *_t954 = malloc(sizeof(I64));
            *_t954 = 1;
            I64 *_t955 = malloc(sizeof(I64)); *_t955 = I64_add(DEREF(_fi951), DEREF(_t954));
            I64_delete(_t954, &(Bool){1});
            *_fi951 = DEREF(_t955);
            I64_delete(_t955, &(Bool){1});
            print_single(s);
        }
        I64_delete(_fi951, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    I64 *total = malloc(sizeof(I64));
    *total = 0;
    {
        I64 *_fi956 = malloc(sizeof(I64));
        *_fi956 = 0;
        while (1) {
            I64 *_t958 = Array_len(parts);
            Bool *_wcond957 = I64_lt(_fi956, _t958);
            I64_delete(_t958, &(Bool){1});
            if (DEREF(_wcond957)) {
            } else {
                Bool_delete(_wcond957, &(Bool){1});
                break;
            }
            Bool_delete(_wcond957, &(Bool){1});
            Str *s = Array_get(parts, _fi956);
            I64 *_t959 = malloc(sizeof(I64));
            *_t959 = 1;
            I64 *_t960 = malloc(sizeof(I64)); *_t960 = I64_add(DEREF(_fi956), DEREF(_t959));
            I64_delete(_t959, &(Bool){1});
            *_fi956 = DEREF(_t960);
            I64_delete(_t960, &(Bool){1});
            I64 *_t961 = Str_len(s);
            I64 *_t962 = malloc(sizeof(I64)); *_t962 = I64_add(DEREF(total), DEREF(_t961));
            I64_delete(_t961, &(Bool){1});
            *total = DEREF(_t962);
            I64_delete(_t962, &(Bool){1});
        }
        I64_delete(_fi956, &(Bool){1});
    }
    U8 *buf = malloc(DEREF(total));
    I64 *offset = malloc(sizeof(I64));
    *offset = 0;
    {
        I64 *_fi963 = malloc(sizeof(I64));
        *_fi963 = 0;
        while (1) {
            I64 *_t965 = Array_len(parts);
            Bool *_wcond964 = I64_lt(_fi963, _t965);
            I64_delete(_t965, &(Bool){1});
            if (DEREF(_wcond964)) {
            } else {
                Bool_delete(_wcond964, &(Bool){1});
                break;
            }
            Bool_delete(_wcond964, &(Bool){1});
            Str *s = Array_get(parts, _fi963);
            I64 *_t966 = malloc(sizeof(I64));
            *_t966 = 1;
            I64 *_t967 = malloc(sizeof(I64)); *_t967 = I64_add(DEREF(_fi963), DEREF(_t966));
            I64_delete(_t966, &(Bool){1});
            *_fi963 = DEREF(_t967);
            I64_delete(_t967, &(Bool){1});
            void *_t968 = ptr_add(buf, DEREF(offset));
            I64 *_t969 = Str_len(s);
            memcpy(_t968, s->c_str, DEREF(_t969));
            I64_delete(_t969, &(Bool){1});
            I64 *_t970 = Str_len(s);
            I64 *_t971 = malloc(sizeof(I64)); *_t971 = I64_add(DEREF(offset), DEREF(_t970));
            I64_delete(_t970, &(Bool){1});
            *offset = DEREF(_t971);
            I64_delete(_t971, &(Bool){1});
        }
        I64_delete(_fi963, &(Bool){1});
    }
    I64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    I64 *_t972 = I64_clone(total);
    I64 *_t973 = I64_clone(total);
    I64_delete(total, &(Bool){1});
    Str *_t974 = malloc(sizeof(Str));
    _t974->c_str = buf;
    _t974->count = DEREF(_t972);
    _t974->cap = DEREF(_t973);
    I64_delete(_t972, &(Bool){1});
    I64_delete(_t973, &(Bool){1});
    return _t974;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 *status = check_cmd_status(DEREF(pid));
        I64 *_t975 = malloc(sizeof(I64));
        *_t975 = 0;
        I64 *_t976 = malloc(sizeof(I64));
        *_t976 = 1;
        I64 *_t977 = malloc(sizeof(I64)); *_t977 = I64_sub(DEREF(_t975), DEREF(_t976));
        I64_delete(_t975, &(Bool){1});
        I64_delete(_t976, &(Bool){1});
        Bool *_t978 = I64_neq(status, _t977);
        I64_delete(_t977, &(Bool){1});
        if (DEREF(_t978)) {
            Bool_delete(_t978, &(Bool){1});
            return status;
        }
        Bool_delete(_t978, &(Bool){1});
        I64_delete(status, &(Bool){1});
        I64 *_t979 = malloc(sizeof(I64));
        *_t979 = 50;
        sleep_ms(DEREF(_t979));
        I64_delete(_t979, &(Bool){1});
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0);
    I64 *i = malloc(sizeof(I64));
    *i = 0;
    while (1) {
        I64 *_t985 = Array_len(args);
        Bool *_wcond980 = I64_lt(i, _t985);
        I64_delete(_t985, &(Bool){1});
        if (DEREF(_wcond980)) {
        } else {
            Bool_delete(_wcond980, &(Bool){1});
            break;
        }
        Bool_delete(_wcond980, &(Bool){1});
        Str *arg = Array_get(args, i);
        I64 *_t986 = malloc(sizeof(I64));
        *_t986 = 0;
        Bool *_t987 = I64_gt(i, _t986);
        I64_delete(_t986, &(Bool){1});
        if (DEREF(_t987)) {
            Str *_t981 = Str_lit(" '", 2);
            Str *_t982 = Str_concat(cmd, _t981);
            Str_delete(_t981, &(Bool){1});
            Str *_t983 = Str_concat(_t982, arg);
            Str_delete(_t982, &(Bool){1});
            Str *_t984 = Str_lit("'", 1);
            cmd = Str_concat(_t983, _t984);
            Str_delete(_t983, &(Bool){1});
            Str_delete(_t984, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        Bool_delete(_t987, &(Bool){1});
        I64 *_t988 = malloc(sizeof(I64));
        *_t988 = 1;
        I64 *_t989 = malloc(sizeof(I64)); *_t989 = I64_add(DEREF(i), DEREF(_t988));
        I64_delete(_t988, &(Bool){1});
        *i = DEREF(_t989);
        I64_delete(_t989, &(Bool){1});
    }
    Array_delete(args, &(Bool){1});
    I64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16);
    Str *_t990 = Str_lit(" > ", 3);
    Str *_t991 = Str_concat(cmd, _t990);
    Str_delete(_t990, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t992 = Str_concat(_t991, tmpf);
    Str_delete(_t991, &(Bool){1});
    Str *_t993 = Str_lit(" 2>&1", 5);
    Str *_t994 = Str_concat(_t992, _t993);
    Str_delete(_t992, &(Bool){1});
    Str_delete(_t993, &(Bool){1});
    I64 *pid = spawn_cmd(_t994);
    Str_delete(_t994, &(Bool){1});
    I64 *ec = wait_cmd(pid);
    I64_delete(pid, &(Bool){1});
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    I64 *_t995 = Str_size();
    memcpy(output, content, DEREF(_t995));
    I64_delete(_t995, &(Bool){1});
    free(content);
    return ec;
}

void panic(Str * loc_str, Array * parts) {
    Str *_t996 = Str_lit("Str", 3);
    I64 *_t997 = Str_size();
    I64 *_t998 = malloc(sizeof(I64));
    *_t998 = 3;
    Array *_va16 = Array_new(_t996, _t997, _t998);
    Str_delete(_t996, &(Bool){1});
    I64_delete(_t997, &(Bool){1});
    I64_delete(_t998, &(Bool){1});
    I64 *_t999 = malloc(sizeof(I64));
    *_t999 = 0;
    Str *_t1000 = Str_clone(loc_str);
    Array_set(_va16, _t999, _t1000);
    I64_delete(_t999, &(Bool){1});
    I64 *_t1001 = malloc(sizeof(I64));
    *_t1001 = 1;
    Str *_t1002 = Str_lit(": panic: ", 9);
    Array_set(_va16, _t1001, _t1002);
    I64_delete(_t1001, &(Bool){1});
    I64 *_t1003 = malloc(sizeof(I64));
    *_t1003 = 2;
    Str *_t1004 = format(parts);
    Array_set(_va16, _t1003, _t1004);
    I64_delete(_t1003, &(Bool){1});
    println(_va16);
    I64 *_t1005 = malloc(sizeof(I64));
    *_t1005 = 1;
    exit(DEREF(_t1005));
    I64_delete(_t1005, &(Bool){1});
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t1006 = Str_lit("Str", 3);
    I64 *_t1007 = Str_size();
    I64 *_t1008 = malloc(sizeof(I64));
    *_t1008 = 2;
    Array *_va17 = Array_new(_t1006, _t1007, _t1008);
    Str_delete(_t1006, &(Bool){1});
    I64_delete(_t1007, &(Bool){1});
    I64_delete(_t1008, &(Bool){1});
    I64 *_t1009 = malloc(sizeof(I64));
    *_t1009 = 0;
    Str *_t1010 = Str_lit("TODO: ", 6);
    Array_set(_va17, _t1009, _t1010);
    I64_delete(_t1009, &(Bool){1});
    I64 *_t1011 = malloc(sizeof(I64));
    *_t1011 = 1;
    Str *_t1012 = format(parts);
    Array_set(_va17, _t1011, _t1012);
    I64_delete(_t1011, &(Bool){1});
    panic(loc_str, _va17);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t1013 = Str_lit("Str", 3);
    I64 *_t1014 = Str_size();
    I64 *_t1015 = malloc(sizeof(I64));
    *_t1015 = 1;
    Array *_va18 = Array_new(_t1013, _t1014, _t1015);
    Str_delete(_t1013, &(Bool){1});
    I64_delete(_t1014, &(Bool){1});
    I64_delete(_t1015, &(Bool){1});
    I64 *_t1016 = malloc(sizeof(I64));
    *_t1016 = 0;
    Str *_t1017 = Str_lit("unreachable", 11);
    Array_set(_va18, _t1016, _t1017);
    I64_delete(_t1016, &(Bool){1});
    panic(loc_str, _va18);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool *_t1025 = malloc(sizeof(Bool)); *_t1025 = Bool_not(DEREF(cond));
    if (DEREF(_t1025)) {
        Str *_t1018 = Str_lit("Str", 3);
        I64 *_t1019 = Str_size();
        I64 *_t1020 = malloc(sizeof(I64));
        *_t1020 = 2;
        Array *_va19 = Array_new(_t1018, _t1019, _t1020);
        Str_delete(_t1018, &(Bool){1});
        I64_delete(_t1019, &(Bool){1});
        I64_delete(_t1020, &(Bool){1});
        I64 *_t1021 = malloc(sizeof(I64));
        *_t1021 = 0;
        Str *_t1022 = Str_lit("assert failed: ", 15);
        Array_set(_va19, _t1021, _t1022);
        I64_delete(_t1021, &(Bool){1});
        I64 *_t1023 = malloc(sizeof(I64));
        *_t1023 = 1;
        Str *_t1024 = format(parts);
        Array_set(_va19, _t1023, _t1024);
        I64_delete(_t1023, &(Bool){1});
        panic(loc_str, _va19);
    }
    Bool_delete(_t1025, &(Bool){1});
    Bool *_t1026 = malloc(sizeof(Bool));
    *_t1026 = 1;
    return _t1026;
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t1027 = Str_lit("Str", 3);
    I64 *_t1028 = Str_size();
    I64 *_t1029 = malloc(sizeof(I64));
    *_t1029 = 0;
    Array *_va20 = Array_new(_t1027, _t1028, _t1029);
    Str_delete(_t1027, &(Bool){1});
    I64_delete(_t1028, &(Bool){1});
    I64_delete(_t1029, &(Bool){1});
    Bool *_t1030 = assertm(loc_str, cond, _va20);
    return _t1030;
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t1031 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool *_t1032 = assertm(loc_str, cond, _t1031);
    Bool_delete(_t1032, &(Bool){1});
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool *_t1046 = I64_neq(a, b);
    if (DEREF(_t1046)) {
        Str *_t1033 = Str_lit("Str", 3);
        I64 *_t1034 = Str_size();
        I64 *_t1035 = malloc(sizeof(I64));
        *_t1035 = 5;
        Array *_va21 = Array_new(_t1033, _t1034, _t1035);
        Str_delete(_t1033, &(Bool){1});
        I64_delete(_t1034, &(Bool){1});
        I64_delete(_t1035, &(Bool){1});
        I64 *_t1036 = malloc(sizeof(I64));
        *_t1036 = 0;
        Str *_t1037 = Str_lit("assert_eq failed: expected '", 28);
        Array_set(_va21, _t1036, _t1037);
        I64_delete(_t1036, &(Bool){1});
        I64 *_t1038 = malloc(sizeof(I64));
        *_t1038 = 1;
        Str *_t1039 = I64_to_str(a);
        Array_set(_va21, _t1038, _t1039);
        I64_delete(_t1038, &(Bool){1});
        I64 *_t1040 = malloc(sizeof(I64));
        *_t1040 = 2;
        Str *_t1041 = Str_lit("', found '", 10);
        Array_set(_va21, _t1040, _t1041);
        I64_delete(_t1040, &(Bool){1});
        I64 *_t1042 = malloc(sizeof(I64));
        *_t1042 = 3;
        Str *_t1043 = I64_to_str(b);
        Array_set(_va21, _t1042, _t1043);
        I64_delete(_t1042, &(Bool){1});
        I64 *_t1044 = malloc(sizeof(I64));
        *_t1044 = 4;
        Str *_t1045 = Str_lit("'", 1);
        Array_set(_va21, _t1044, _t1045);
        I64_delete(_t1044, &(Bool){1});
        panic(loc_str, _va21);
    }
    Bool_delete(_t1046, &(Bool){1});
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool *_t1060 = Str_eq(a, b);
    Bool *_t1061 = malloc(sizeof(Bool)); *_t1061 = Bool_not(DEREF(_t1060));
    Bool_delete(_t1060, &(Bool){1});
    if (DEREF(_t1061)) {
        Str *_t1047 = Str_lit("Str", 3);
        I64 *_t1048 = Str_size();
        I64 *_t1049 = malloc(sizeof(I64));
        *_t1049 = 5;
        Array *_va22 = Array_new(_t1047, _t1048, _t1049);
        Str_delete(_t1047, &(Bool){1});
        I64_delete(_t1048, &(Bool){1});
        I64_delete(_t1049, &(Bool){1});
        I64 *_t1050 = malloc(sizeof(I64));
        *_t1050 = 0;
        Str *_t1051 = Str_lit("assert_eq_str failed: expected '", 32);
        Array_set(_va22, _t1050, _t1051);
        I64_delete(_t1050, &(Bool){1});
        I64 *_t1052 = malloc(sizeof(I64));
        *_t1052 = 1;
        Str *_t1053 = Str_clone(a);
        Array_set(_va22, _t1052, _t1053);
        I64_delete(_t1052, &(Bool){1});
        I64 *_t1054 = malloc(sizeof(I64));
        *_t1054 = 2;
        Str *_t1055 = Str_lit("', found '", 10);
        Array_set(_va22, _t1054, _t1055);
        I64_delete(_t1054, &(Bool){1});
        I64 *_t1056 = malloc(sizeof(I64));
        *_t1056 = 3;
        Str *_t1057 = Str_clone(b);
        Array_set(_va22, _t1056, _t1057);
        I64_delete(_t1056, &(Bool){1});
        I64 *_t1058 = malloc(sizeof(I64));
        *_t1058 = 4;
        Str *_t1059 = Str_lit("'", 1);
        Array_set(_va22, _t1058, _t1059);
        I64_delete(_t1058, &(Bool){1});
        panic(loc_str, _va22);
    }
    Bool_delete(_t1061, &(Bool){1});
}

void dyn_call_delete(Str *type_name, void *val, void *arg2) {
    if (type_name->count == 5 && memcmp(type_name->c_str, "Array", 5) == 0) { Array_delete(val, arg2); return; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "Map", 3) == 0) { Map_delete(val, arg2); return; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "Set", 3) == 0) { Set_delete(val, arg2); return; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "Str", 3) == 0) { Str_delete(val, arg2); return; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "Vec", 3) == 0) { Vec_delete(val, arg2); return; }
    if (type_name->count == 7 && memcmp(type_name->c_str, "EnumDef", 7) == 0) { EnumDef_delete(val, arg2); return; }
    if (type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0) { U8_delete(val, arg2); return; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0) { I16_delete(val, arg2); return; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0) { I32_delete(val, arg2); return; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "F32", 3) == 0) { F32_delete(val, arg2); return; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0) { U32_delete(val, arg2); return; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0) { I64_delete(val, arg2); return; }
    if (type_name->count == 5 && memcmp(type_name->c_str, "Range", 5) == 0) { Range_delete(val, arg2); return; }
    if (type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0) { Bool_delete(val, arg2); return; }
    fprintf(stderr, "dyn_call: unknown type for delete\n");
    exit(1);
}

void *dyn_call_clone(Str *type_name, void *val) {
    if (type_name->count == 5 && memcmp(type_name->c_str, "Array", 5) == 0) return (void *)Array_clone(val);
    if (type_name->count == 3 && memcmp(type_name->c_str, "Map", 3) == 0) return (void *)Map_clone(val);
    if (type_name->count == 3 && memcmp(type_name->c_str, "Set", 3) == 0) return (void *)Set_clone(val);
    if (type_name->count == 3 && memcmp(type_name->c_str, "Str", 3) == 0) return (void *)Str_clone(val);
    if (type_name->count == 3 && memcmp(type_name->c_str, "Vec", 3) == 0) return (void *)Vec_clone(val);
    if (type_name->count == 7 && memcmp(type_name->c_str, "EnumDef", 7) == 0) return (void *)EnumDef_clone(val);
    if (type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0) return (void *)U8_clone(val);
    if (type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0) return (void *)I16_clone(val);
    if (type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0) return (void *)I32_clone(val);
    if (type_name->count == 3 && memcmp(type_name->c_str, "F32", 3) == 0) return (void *)F32_clone(val);
    if (type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0) return (void *)U32_clone(val);
    if (type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0) return (void *)I64_clone(val);
    if (type_name->count == 5 && memcmp(type_name->c_str, "Range", 5) == 0) return (void *)Range_clone(val);
    if (type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0) return (void *)Bool_clone(val);
    fprintf(stderr, "dyn_call: unknown type for clone\n");
    exit(1);
}

void *dyn_call_cmp(Str *type_name, void *val, void *arg2) {
    if (type_name->count == 3 && memcmp(type_name->c_str, "Str", 3) == 0) return (void *)Str_cmp(val, arg2);
    if (type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = U8_cmp(*(U8 *)val, *(U8 *)arg2); return _r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I16_cmp(*(I16 *)val, *(I16 *)arg2); return _r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I32_cmp(*(I32 *)val, *(I32 *)arg2); return _r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "F32", 3) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = F32_cmp(*(F32 *)val, *(F32 *)arg2); return _r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = U32_cmp(*(U32 *)val, *(U32 *)arg2); return _r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I64_cmp(*(I64 *)val, *(I64 *)arg2); return _r; }
    if (type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0) return (void *)Bool_cmp(val, arg2);
    fprintf(stderr, "dyn_call: unknown type for cmp\n");
    exit(1);
}

Bool *dyn_has_cmp(Str *type_name) {
    (void)type_name;
    if (type_name->count == 3 && memcmp(type_name->c_str, "Str", 3) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 2 && memcmp(type_name->c_str, "U8", 2) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "I16", 3) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "I32", 3) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "F32", 3) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "U32", 3) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3 && memcmp(type_name->c_str, "I64", 3) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 4 && memcmp(type_name->c_str, "Bool", 4) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    Bool *r = malloc(sizeof(Bool)); *r = 0; return r;
}

