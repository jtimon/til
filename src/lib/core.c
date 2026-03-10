#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
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
typedef struct U64 U64;
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
void * malloc(U64);
void * calloc(U64, U64);
void * realloc(void *, U64);
void * ptr_add(void *, U64);
void memcpy(void *, void *, U64);
void memmove(void *, void *, U64);
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

static Str *Str_lit(const char *s, unsigned long long len);
static void print_single(Str *s);
static void print_flush();

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap);
U64 * Array_len(Array * self);
void * Array_get(Array * self, U64 * i);
void Array_set(Array * self, U64 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U64 * Array_size(void);
Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size);
U64 * Map_len(Map * self);
Bool * Map_has(Map * self, void * key);
void * Map_get(Map * self, void * key);
void Map_set(Map * self, void * key, void * val);
void Map_delete(Map * self, Bool * call_free);
Map * Map_clone(Map * self);
U64 * Map_size(void);
Set * Set_new(Str * elem_type, U64 * elem_size);
U64 * Set_len(Set * self);
Bool * Set_has(Set * self, void * val);
void Set_add(Set * self, void * val);
void Set_delete(Set * self, Bool * call_free);
Set * Set_clone(Set * self);
U64 * Set_size(void);
U64 * Str_len(Str * self);
U8 * Str_get(Str * self, U64 * i);
I64 * Str_cmp(Str * a, Str * b);
Str * Str_concat(Str * a, Str * b);
Str * Str_with_capacity(U64 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Str * Str_to_str(Str * val);
Str * Str_substr(Str * s, U64 * start, U64 * n);
Bool * Str_contains(Str * a, Str * b);
Bool * Str_starts_with(Str * a, Str * b);
Bool * Str_ends_with(Str * a, Str * b);
Bool * Str_is_empty(Str * self);
I64 * Str_find(Str * self, Str * needle);
I64 * Str_rfind(Str * self, Str * needle);
Str * Str_replace(Str * self, Str * from, Str * to);
Str * Str_get_char(Str * self, U64 * i);
Str * Str_strip_prefix(Str * self, Str * prefix);
Str * Str_strip_suffix(Str * self, Str * suffix);
Str * Str_from_byte(U8 * byte);
I64 * Str_to_i64(Str * self);
U64 * Str_size(void);
Bool * Str_eq(Str * a, Str * b);
Bool * Str_lt(Str * a, Str * b);
Bool * Str_gt(Str * a, Str * b);
Bool * Str_neq(Str * a, Str * b);
Bool * Str_lte(Str * a, Str * b);
Bool * Str_gte(Str * a, Str * b);
Vec * Vec_new(Str * elem_type, U64 * elem_size);
U64 * Vec_len(Vec * self);
void Vec_push(Vec * self, void * val);
void * Vec_get(Vec * self, U64 * i);
void Vec_delete(Vec * self, Bool * call_free);
Vec * Vec_clone(Vec * self);
U64 * Vec_size(void);
Vec * split(Str * s, Str * delim);
Str * join(Vec * parts, Str * sep);
EnumDef * EnumDef_clone(EnumDef * self);
void EnumDef_delete(EnumDef * self, Bool * call_free);
U64 * EnumDef_size(void);
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
U64 * U8_size(void);
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
U64 * I16_size(void);
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
U64 * I32_size(void);
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
U64 * F32_size(void);
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
U64 * U32_size(void);
Bool * U32_lt(U32 * a, U32 * b);
Bool * U32_gt(U32 * a, U32 * b);
Bool * U32_neq(U32 * a, U32 * b);
Bool * U32_lte(U32 * a, U32 * b);
Bool * U32_gte(U32 * a, U32 * b);
I64 U64_to_i64(U64 val);
Str * U64_to_str(U64 val);
U64 * U64_from_i64(I64 * val);
U64 U64_add(U64 a, U64 b);
U64 U64_sub(U64 a, U64 b);
U64 U64_mul(U64 a, U64 b);
U64 U64_div(U64 a, U64 b);
U64 U64_mod(U64 a, U64 b);
U64 U64_inc(U64 a);
U64 U64_dec(U64 a);
Bool U64_eq(U64 a, U64 b);
I64 U64_cmp(U64 a, U64 b);
U64 U64_and(U64 a, U64 b);
U64 U64_or(U64 a, U64 b);
U64 U64_xor(U64 a, U64 b);
U64 * U64_clone(U64 * val);
void U64_delete(U64 * self, Bool * call_free);
U64 * U64_size(void);
Bool * U64_lt(U64 * a, U64 * b);
Bool * U64_gt(U64 * a, U64 * b);
Bool * U64_neq(U64 * a, U64 * b);
Bool * U64_lte(U64 * a, U64 * b);
Bool * U64_gte(U64 * a, U64 * b);
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
U64 * I64_size(void);
Bool * I64_lt(I64 * a, I64 * b);
Bool * I64_gt(I64 * a, I64 * b);
Bool * I64_neq(I64 * a, I64 * b);
Bool * I64_lte(I64 * a, I64 * b);
Bool * I64_gte(I64 * a, I64 * b);
Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
Str * Bool_to_str(Bool * b);
Bool Bool_eq(Bool a, Bool b);
I64 * Bool_cmp(Bool * a, Bool * b);
Bool * Bool_clone(Bool * val);
void Bool_delete(Bool * self, Bool * call_free);
U64 * Bool_size(void);
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
    U64 count;
    U64 cap;
    U64 key_size;
    Str key_type;
    U64 val_size;
    Str val_type;
} Map;


typedef struct Set {
    U8 *data;
    U64 count;
    U64 cap;
    U64 elem_size;
    Str elem_type;
} Set;



typedef struct Vec {
    U8 *data;
    U64 count;
    U64 cap;
    U64 elem_size;
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


typedef struct U64 {
    char _;
} U64;


typedef struct I64 {
    char _;
} I64;


typedef struct Range {
    U64 start;
    U64 end;
} Range;


typedef struct Bool {
    char _;
} Bool;


#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
__attribute__((unused))
#define TIL_CAP_LIT ULLONG_MAX
static Str *Str_lit(const char *s, unsigned long long len) {
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

static I64 *_t1063;
static I64 *_t1064;
static I64 *_t1065;
static U64 *CAP_LIT;
static I64 *_t1066;
static I64 *_t1067;
static I64 *_t1068;
static U64 *CAP_VIEW;

Array * Array_new(Str * elem_type, U64 * elem_size, U64 * cap) {
    void *_t0 = calloc(DEREF(cap), DEREF(elem_size));
    U64 *_t1 = U64_clone(cap);
    U64 *_t2 = U64_clone(elem_size);
    Array *_t3 = malloc(sizeof(Array));
    _t3->data = _t0;
    _t3->cap = DEREF(_t1);
    _t3->elem_size = DEREF(_t2);
    { Str *_ca = Str_clone(elem_type); _t3->elem_type = *_ca; free(_ca); }
    U64_delete(_t1, &(Bool){1});
    U64_delete(_t2, &(Bool){1});
    return _t3;
}

U64 * Array_len(Array * self) {
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    Bool *_t18 = U64_gte(i, &self->cap);
    if (DEREF(_t18)) {
        Str *_t4 = Str_lit("Str", 3ULL);
        I64 *_t5 = Str_size();
        I64 *_t6 = malloc(sizeof(I64));
        *_t6 = 5;
        Array *_va0 = Array_new(_t4, _t5, _t6);
        Str_delete(_t4, &(Bool){1});
        I64_delete(_t5, &(Bool){1});
        I64_delete(_t6, &(Bool){1});
        I64 *_t7 = malloc(sizeof(I64));
        *_t7 = 0;
        Str *_t8 = Str_lit("index ", 6ULL);
        Array_set(_va0, _t7, _t8);
        I64_delete(_t7, &(Bool){1});
        I64 *_t9 = malloc(sizeof(I64));
        *_t9 = 1;
        Str *_t10 = U64_to_str(DEREF(i));
        Array_set(_va0, _t9, _t10);
        I64_delete(_t9, &(Bool){1});
        I64 *_t11 = malloc(sizeof(I64));
        *_t11 = 2;
        Str *_t12 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va0, _t11, _t12);
        I64_delete(_t11, &(Bool){1});
        I64 *_t13 = malloc(sizeof(I64));
        *_t13 = 3;
        Str *_t14 = U64_to_str(self->cap);
        Array_set(_va0, _t13, _t14);
        I64_delete(_t13, &(Bool){1});
        I64 *_t15 = malloc(sizeof(I64));
        *_t15 = 4;
        Str *_t16 = Str_lit(")", 1ULL);
        Array_set(_va0, _t15, _t16);
        I64_delete(_t15, &(Bool){1});
        Str *_t17 = Str_lit("Array.get", 9ULL);
        panic(_t17, _va0);
        Str_delete(_t17, &(Bool){1});
        Array_delete(_va0, &(Bool){1});
    }
    Bool_delete(_t18, &(Bool){1});
    U64 *_t19 = malloc(sizeof(U64)); *_t19 = U64_mul(DEREF(i), self->elem_size);
    void *_t20 = ptr_add(self->data, DEREF(_t19));
    U64_delete(_t19, &(Bool){1});
    return _t20;
}

void Array_set(Array * self, U64 * i, void * val) {
    Bool *_t35 = U64_gte(i, &self->cap);
    if (DEREF(_t35)) {
        Str *_t21 = Str_lit("Str", 3ULL);
        I64 *_t22 = Str_size();
        I64 *_t23 = malloc(sizeof(I64));
        *_t23 = 5;
        Array *_va1 = Array_new(_t21, _t22, _t23);
        Str_delete(_t21, &(Bool){1});
        I64_delete(_t22, &(Bool){1});
        I64_delete(_t23, &(Bool){1});
        I64 *_t24 = malloc(sizeof(I64));
        *_t24 = 0;
        Str *_t25 = Str_lit("index ", 6ULL);
        Array_set(_va1, _t24, _t25);
        I64_delete(_t24, &(Bool){1});
        I64 *_t26 = malloc(sizeof(I64));
        *_t26 = 1;
        Str *_t27 = U64_to_str(DEREF(i));
        Array_set(_va1, _t26, _t27);
        I64_delete(_t26, &(Bool){1});
        I64 *_t28 = malloc(sizeof(I64));
        *_t28 = 2;
        Str *_t29 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va1, _t28, _t29);
        I64_delete(_t28, &(Bool){1});
        I64 *_t30 = malloc(sizeof(I64));
        *_t30 = 3;
        Str *_t31 = U64_to_str(self->cap);
        Array_set(_va1, _t30, _t31);
        I64_delete(_t30, &(Bool){1});
        I64 *_t32 = malloc(sizeof(I64));
        *_t32 = 4;
        Str *_t33 = Str_lit(")", 1ULL);
        Array_set(_va1, _t32, _t33);
        I64_delete(_t32, &(Bool){1});
        Str *_t34 = Str_lit("Array.set", 9ULL);
        panic(_t34, _va1);
        Str_delete(_t34, &(Bool){1});
        Array_delete(_va1, &(Bool){1});
    }
    Bool_delete(_t35, &(Bool){1});
    U64 *_t36 = malloc(sizeof(U64)); *_t36 = U64_mul(DEREF(i), self->elem_size);
    void *_t37 = ptr_add(self->data, DEREF(_t36));
    Bool *_t38 = malloc(sizeof(Bool));
    *_t38 = 0;
    dyn_call_delete(&self->elem_type, _t37, _t38);
    U64_delete(_t36, &(Bool){1});
    Bool_delete(_t38, &(Bool){1});
    U64 *_t39 = malloc(sizeof(U64)); *_t39 = U64_mul(DEREF(i), self->elem_size);
    void *_t40 = ptr_add(self->data, DEREF(_t39));
    memcpy(_t40, val, self->elem_size);
    U64_delete(_t39, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U64 *_fi41 = malloc(sizeof(U64));
        *_fi41 = 0;
        while (1) {
            I64 *_t43 = malloc(sizeof(I64));
            *_t43 = 0;
            Range *_t44 = Range_new(DEREF(_t43), self->cap);
            I64_delete(_t43, &(Bool){1});
            U64 *_t45 = Range_len(_t44);
            Range_delete(_t44, &(Bool){1});
            Bool *_wcond42 = U64_lt(_fi41, _t45);
            U64_delete(_t45, &(Bool){1});
            if (DEREF(_wcond42)) {
            } else {
                Bool_delete(_wcond42, &(Bool){1});
                break;
            }
            Bool_delete(_wcond42, &(Bool){1});
            I64 *_t46 = malloc(sizeof(I64));
            *_t46 = 0;
            Range *_t47 = Range_new(DEREF(_t46), self->cap);
            I64_delete(_t46, &(Bool){1});
            U64 *i = Range_get(_t47, DEREF(_fi41));
            Range_delete(_t47, &(Bool){1});
            I64 *_t48 = malloc(sizeof(I64));
            *_t48 = 1;
            U64 *_t49 = malloc(sizeof(U64)); *_t49 = U64_add(DEREF(_fi41), DEREF(_t48));
            I64_delete(_t48, &(Bool){1});
            *_fi41 = DEREF(_t49);
            U64_delete(_t49, &(Bool){1});
            U64 *_t50 = malloc(sizeof(U64)); *_t50 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t51 = ptr_add(self->data, DEREF(_t50));
            Bool *_t52 = malloc(sizeof(Bool));
            *_t52 = 0;
            dyn_call_delete(&self->elem_type, _t51, _t52);
            U64_delete(_t50, &(Bool){1});
            Bool_delete(_t52, &(Bool){1});
        }
        U64_delete(_fi41, &(Bool){1});
    }
    free(self->data);
    Bool *_t53 = malloc(sizeof(Bool));
    *_t53 = 0;
    Str_delete(&self->elem_type, _t53);
    Bool_delete(_t53, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U64 *_t67 = malloc(sizeof(U64)); *_t67 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t67));
    U64_delete(_t67, &(Bool){1});
    {
        U64 *_fi54 = malloc(sizeof(U64));
        *_fi54 = 0;
        while (1) {
            I64 *_t56 = malloc(sizeof(I64));
            *_t56 = 0;
            Range *_t57 = Range_new(DEREF(_t56), self->cap);
            I64_delete(_t56, &(Bool){1});
            U64 *_t58 = Range_len(_t57);
            Range_delete(_t57, &(Bool){1});
            Bool *_wcond55 = U64_lt(_fi54, _t58);
            U64_delete(_t58, &(Bool){1});
            if (DEREF(_wcond55)) {
            } else {
                Bool_delete(_wcond55, &(Bool){1});
                break;
            }
            Bool_delete(_wcond55, &(Bool){1});
            I64 *_t59 = malloc(sizeof(I64));
            *_t59 = 0;
            Range *_t60 = Range_new(DEREF(_t59), self->cap);
            I64_delete(_t59, &(Bool){1});
            U64 *i = Range_get(_t60, DEREF(_fi54));
            Range_delete(_t60, &(Bool){1});
            I64 *_t61 = malloc(sizeof(I64));
            *_t61 = 1;
            U64 *_t62 = malloc(sizeof(U64)); *_t62 = U64_add(DEREF(_fi54), DEREF(_t61));
            I64_delete(_t61, &(Bool){1});
            *_fi54 = DEREF(_t62);
            U64_delete(_t62, &(Bool){1});
            U64 *_t63 = malloc(sizeof(U64)); *_t63 = U64_mul(DEREF(i), self->elem_size);
            void *_t64 = ptr_add(self->data, DEREF(_t63));
            void *cloned = dyn_call_clone(&self->elem_type, _t64);
            U64_delete(_t63, &(Bool){1});
            U64 *_t65 = malloc(sizeof(U64)); *_t65 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t66 = ptr_add(new_data, DEREF(_t65));
            memcpy(_t66, cloned, self->elem_size);
            U64_delete(_t65, &(Bool){1});
            free(cloned);
        }
        U64_delete(_fi54, &(Bool){1});
    }
    Array *_t68 = malloc(sizeof(Array));
    _t68->data = new_data;
    _t68->cap = self->cap;
    _t68->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t68->elem_type = *_ca; free(_ca); }
    return _t68;
}

U64 *Array_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Array);
    return r;
}

Map * Map_new(Str * key_type, U64 * key_size, Str * val_type, U64 * val_size) {
    Bool *_t80 = dyn_has_cmp(key_type);
    Bool *_t81 = malloc(sizeof(Bool)); *_t81 = Bool_not(DEREF(_t80));
    Bool_delete(_t80, &(Bool){1});
    if (DEREF(_t81)) {
        Str *_t70 = Str_lit("Str", 3ULL);
        I64 *_t71 = Str_size();
        I64 *_t72 = malloc(sizeof(I64));
        *_t72 = 3;
        Array *_va2 = Array_new(_t70, _t71, _t72);
        Str_delete(_t70, &(Bool){1});
        I64_delete(_t71, &(Bool){1});
        I64_delete(_t72, &(Bool){1});
        I64 *_t73 = malloc(sizeof(I64));
        *_t73 = 0;
        Str *_t74 = Str_lit("type ", 5ULL);
        Array_set(_va2, _t73, _t74);
        I64_delete(_t73, &(Bool){1});
        I64 *_t75 = malloc(sizeof(I64));
        *_t75 = 1;
        Str *_t76 = Str_clone(key_type);
        Array_set(_va2, _t75, _t76);
        I64_delete(_t75, &(Bool){1});
        I64 *_t77 = malloc(sizeof(I64));
        *_t77 = 2;
        Str *_t78 = Str_lit(" must implement cmp", 19ULL);
        Array_set(_va2, _t77, _t78);
        I64_delete(_t77, &(Bool){1});
        Str *_t79 = Str_lit("Map.new", 7ULL);
        panic(_t79, _va2);
        Str_delete(_t79, &(Bool){1});
        Array_delete(_va2, &(Bool){1});
    }
    Bool_delete(_t81, &(Bool){1});
    void *_t82 = malloc(DEREF(key_size));
    void *_t83 = malloc(DEREF(val_size));
    U64 *_t84 = malloc(sizeof(U64));
    *_t84 = 0;
    I64 *_t85 = malloc(sizeof(I64));
    *_t85 = 1;
    U64 *_t86 = U64_clone(key_size);
    U64 *_t87 = U64_clone(val_size);
    Map *_t88 = malloc(sizeof(Map));
    _t88->key_data = _t82;
    _t88->val_data = _t83;
    _t88->count = DEREF(_t84);
    _t88->cap = DEREF(_t85);
    _t88->key_size = DEREF(_t86);
    { Str *_ca = Str_clone(key_type); _t88->key_type = *_ca; free(_ca); }
    _t88->val_size = DEREF(_t87);
    { Str *_ca = Str_clone(val_type); _t88->val_type = *_ca; free(_ca); }
    U64_delete(_t84, &(Bool){1});
    I64_delete(_t85, &(Bool){1});
    U64_delete(_t86, &(Bool){1});
    U64_delete(_t87, &(Bool){1});
    return _t88;
}

U64 * Map_len(Map * self) {
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Map_has(Map * self, void * key) {
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    while (1) {
        Bool *_wcond89 = U64_lt(lo, hi);
        if (DEREF(_wcond89)) {
        } else {
            Bool_delete(_wcond89, &(Bool){1});
            break;
        }
        Bool_delete(_wcond89, &(Bool){1});
        U64 *_t96 = malloc(sizeof(U64)); *_t96 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t97 = malloc(sizeof(I64));
        *_t97 = 2;
        U64 *_t98 = malloc(sizeof(U64)); *_t98 = U64_div(DEREF(_t96), DEREF(_t97));
        U64_delete(_t96, &(Bool){1});
        I64_delete(_t97, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t98));
        U64_delete(_t98, &(Bool){1});
        U64 *_t99 = malloc(sizeof(U64)); *_t99 = U64_mul(DEREF(mid), self->key_size);
        void *_t100 = ptr_add(self->key_data, DEREF(_t99));
        I64 *c = dyn_call_cmp(&self->key_type, _t100, key);
        U64_delete(_t99, &(Bool){1});
        I64 *_t101 = malloc(sizeof(I64));
        *_t101 = 0;
        Bool *_t102 = I64_lt(c, _t101);
        I64_delete(_t101, &(Bool){1});
        if (DEREF(_t102)) {
            I64 *_t90 = malloc(sizeof(I64));
            *_t90 = 1;
            U64 *_t91 = malloc(sizeof(U64)); *_t91 = U64_add(DEREF(mid), DEREF(_t90));
            I64_delete(_t90, &(Bool){1});
            *lo = DEREF(_t91);
            U64_delete(_t91, &(Bool){1});
        } else {
            I64 *_t94 = malloc(sizeof(I64));
            *_t94 = 0;
            Bool *_t95 = I64_gt(c, _t94);
            I64_delete(_t94, &(Bool){1});
            if (DEREF(_t95)) {
                U64 *_t92 = U64_clone(mid);
                *hi = DEREF(_t92);
                U64_delete(_t92, &(Bool){1});
            } else {
                Bool *_t93 = malloc(sizeof(Bool));
                *_t93 = 1;
                Bool_delete(_t95, &(Bool){1});
                Bool_delete(_t102, &(Bool){1});
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                U64_delete(hi, &(Bool){1});
                U64_delete(lo, &(Bool){1});
                return _t93;
            }
            Bool_delete(_t95, &(Bool){1});
        }
        Bool_delete(_t102, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    U64_delete(lo, &(Bool){1});
    Bool *_t103 = malloc(sizeof(Bool));
    *_t103 = 0;
    return _t103;
}

void * Map_get(Map * self, void * key) {
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    while (1) {
        Bool *_wcond104 = U64_lt(lo, hi);
        if (DEREF(_wcond104)) {
        } else {
            Bool_delete(_wcond104, &(Bool){1});
            break;
        }
        Bool_delete(_wcond104, &(Bool){1});
        U64 *_t112 = malloc(sizeof(U64)); *_t112 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t113 = malloc(sizeof(I64));
        *_t113 = 2;
        U64 *_t114 = malloc(sizeof(U64)); *_t114 = U64_div(DEREF(_t112), DEREF(_t113));
        U64_delete(_t112, &(Bool){1});
        I64_delete(_t113, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t114));
        U64_delete(_t114, &(Bool){1});
        U64 *_t115 = malloc(sizeof(U64)); *_t115 = U64_mul(DEREF(mid), self->key_size);
        void *_t116 = ptr_add(self->key_data, DEREF(_t115));
        I64 *c = dyn_call_cmp(&self->key_type, _t116, key);
        U64_delete(_t115, &(Bool){1});
        I64 *_t117 = malloc(sizeof(I64));
        *_t117 = 0;
        Bool *_t118 = I64_lt(c, _t117);
        I64_delete(_t117, &(Bool){1});
        if (DEREF(_t118)) {
            I64 *_t105 = malloc(sizeof(I64));
            *_t105 = 1;
            U64 *_t106 = malloc(sizeof(U64)); *_t106 = U64_add(DEREF(mid), DEREF(_t105));
            I64_delete(_t105, &(Bool){1});
            *lo = DEREF(_t106);
            U64_delete(_t106, &(Bool){1});
        } else {
            I64 *_t110 = malloc(sizeof(I64));
            *_t110 = 0;
            Bool *_t111 = I64_gt(c, _t110);
            I64_delete(_t110, &(Bool){1});
            if (DEREF(_t111)) {
                U64 *_t107 = U64_clone(mid);
                *hi = DEREF(_t107);
                U64_delete(_t107, &(Bool){1});
            } else {
                U64 *_t108 = malloc(sizeof(U64)); *_t108 = U64_mul(DEREF(mid), self->val_size);
                void *_t109 = ptr_add(self->val_data, DEREF(_t108));
                U64_delete(_t108, &(Bool){1});
                Bool_delete(_t111, &(Bool){1});
                Bool_delete(_t118, &(Bool){1});
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                U64_delete(hi, &(Bool){1});
                U64_delete(lo, &(Bool){1});
                return _t109;
            }
            Bool_delete(_t111, &(Bool){1});
        }
        Bool_delete(_t118, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    U64_delete(lo, &(Bool){1});
    Str *_t119 = Str_lit("Str", 3ULL);
    I64 *_t120 = Str_size();
    I64 *_t121 = malloc(sizeof(I64));
    *_t121 = 1;
    Array *_va3 = Array_new(_t119, _t120, _t121);
    Str_delete(_t119, &(Bool){1});
    I64_delete(_t120, &(Bool){1});
    I64_delete(_t121, &(Bool){1});
    I64 *_t122 = malloc(sizeof(I64));
    *_t122 = 0;
    Str *_t123 = Str_lit("key not found", 13ULL);
    Array_set(_va3, _t122, _t123);
    I64_delete(_t122, &(Bool){1});
    Str *_t124 = Str_lit("Map.get", 7ULL);
    panic(_t124, _va3);
    Str_delete(_t124, &(Bool){1});
    Array_delete(_va3, &(Bool){1});
    I64 *_t125 = malloc(sizeof(I64));
    *_t125 = 0;
    void *_t126 = ptr_add(self->val_data, DEREF(_t125));
    I64_delete(_t125, &(Bool){1});
    return _t126;
}

void Map_set(Map * self, void * key, void * val) {
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    Bool *found = malloc(sizeof(Bool));
    *found = 0;
    while (1) {
        Bool *_wcond127 = U64_lt(lo, hi);
        if (DEREF(_wcond127)) {
        } else {
            Bool_delete(_wcond127, &(Bool){1});
            break;
        }
        Bool_delete(_wcond127, &(Bool){1});
        U64 *_t136 = malloc(sizeof(U64)); *_t136 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t137 = malloc(sizeof(I64));
        *_t137 = 2;
        U64 *_t138 = malloc(sizeof(U64)); *_t138 = U64_div(DEREF(_t136), DEREF(_t137));
        U64_delete(_t136, &(Bool){1});
        I64_delete(_t137, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t138));
        U64_delete(_t138, &(Bool){1});
        U64 *_t139 = malloc(sizeof(U64)); *_t139 = U64_mul(DEREF(mid), self->key_size);
        void *_t140 = ptr_add(self->key_data, DEREF(_t139));
        I64 *c = dyn_call_cmp(&self->key_type, _t140, key);
        U64_delete(_t139, &(Bool){1});
        I64 *_t141 = malloc(sizeof(I64));
        *_t141 = 0;
        Bool *_t142 = I64_lt(c, _t141);
        I64_delete(_t141, &(Bool){1});
        if (DEREF(_t142)) {
            I64 *_t128 = malloc(sizeof(I64));
            *_t128 = 1;
            U64 *_t129 = malloc(sizeof(U64)); *_t129 = U64_add(DEREF(mid), DEREF(_t128));
            I64_delete(_t128, &(Bool){1});
            *lo = DEREF(_t129);
            U64_delete(_t129, &(Bool){1});
        } else {
            I64 *_t134 = malloc(sizeof(I64));
            *_t134 = 0;
            Bool *_t135 = I64_gt(c, _t134);
            I64_delete(_t134, &(Bool){1});
            if (DEREF(_t135)) {
                U64 *_t130 = U64_clone(mid);
                *hi = DEREF(_t130);
                U64_delete(_t130, &(Bool){1});
            } else {
                Bool *_t131 = malloc(sizeof(Bool));
                *_t131 = 1;
                *found = DEREF(_t131);
                Bool_delete(_t131, &(Bool){1});
                U64 *_t132 = U64_clone(mid);
                *lo = DEREF(_t132);
                U64_delete(_t132, &(Bool){1});
                U64 *_t133 = U64_clone(mid);
                *hi = DEREF(_t133);
                U64_delete(_t133, &(Bool){1});
            }
            Bool_delete(_t135, &(Bool){1});
        }
        Bool_delete(_t142, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    if (DEREF(found)) {
        Bool *_t143 = malloc(sizeof(Bool));
        *_t143 = 0;
        dyn_call_delete(&self->key_type, key, _t143);
        Bool_delete(_t143, &(Bool){1});
        free(key);
        U64 *_t144 = malloc(sizeof(U64)); *_t144 = U64_mul(DEREF(lo), self->val_size);
        void *_t145 = ptr_add(self->val_data, DEREF(_t144));
        Bool *_t146 = malloc(sizeof(Bool));
        *_t146 = 0;
        dyn_call_delete(&self->val_type, _t145, _t146);
        U64_delete(_t144, &(Bool){1});
        Bool_delete(_t146, &(Bool){1});
        U64 *_t147 = malloc(sizeof(U64)); *_t147 = U64_mul(DEREF(lo), self->val_size);
        void *_t148 = ptr_add(self->val_data, DEREF(_t147));
        memcpy(_t148, val, self->val_size);
        U64_delete(_t147, &(Bool){1});
        free(val);
    } else {
        Bool *_t155 = malloc(sizeof(Bool)); *_t155 = U64_eq(self->count, self->cap);
        if (DEREF(_t155)) {
            I64 *_t149 = malloc(sizeof(I64));
            *_t149 = 2;
            U64 *new_cap = malloc(sizeof(U64)); *new_cap = U64_mul(self->cap, DEREF(_t149));
            I64_delete(_t149, &(Bool){1});
            U64 *_t150 = malloc(sizeof(U64)); *_t150 = U64_mul(DEREF(new_cap), self->key_size);
            void *_t151 = realloc(self->key_data, DEREF(_t150));
            U64_delete(_t150, &(Bool){1});
            self->key_data = _t151;
            U64 *_t152 = malloc(sizeof(U64)); *_t152 = U64_mul(DEREF(new_cap), self->val_size);
            void *_t153 = realloc(self->val_data, DEREF(_t152));
            U64_delete(_t152, &(Bool){1});
            self->val_data = _t153;
            U64 *_t154 = U64_clone(new_cap);
            U64_delete(new_cap, &(Bool){1});
            self->cap = DEREF(_t154);
            U64_delete(_t154, &(Bool){1});
        }
        Bool_delete(_t155, &(Bool){1});
        I64 *_t156 = malloc(sizeof(I64));
        *_t156 = 1;
        U64 *_t157 = malloc(sizeof(U64)); *_t157 = U64_add(DEREF(lo), DEREF(_t156));
        I64_delete(_t156, &(Bool){1});
        U64 *_t158 = malloc(sizeof(U64)); *_t158 = U64_mul(DEREF(_t157), self->key_size);
        U64_delete(_t157, &(Bool){1});
        U64 *_t159 = malloc(sizeof(U64)); *_t159 = U64_mul(DEREF(lo), self->key_size);
        U64 *_t160 = malloc(sizeof(U64)); *_t160 = U64_sub(self->count, DEREF(lo));
        void *_t161 = ptr_add(self->key_data, DEREF(_t158));
        void *_t162 = ptr_add(self->key_data, DEREF(_t159));
        U64 *_t163 = malloc(sizeof(U64)); *_t163 = U64_mul(DEREF(_t160), self->key_size);
        U64_delete(_t160, &(Bool){1});
        memmove(_t161, _t162, DEREF(_t163));
        U64_delete(_t158, &(Bool){1});
        U64_delete(_t159, &(Bool){1});
        U64_delete(_t163, &(Bool){1});
        I64 *_t164 = malloc(sizeof(I64));
        *_t164 = 1;
        U64 *_t165 = malloc(sizeof(U64)); *_t165 = U64_add(DEREF(lo), DEREF(_t164));
        I64_delete(_t164, &(Bool){1});
        U64 *_t166 = malloc(sizeof(U64)); *_t166 = U64_mul(DEREF(_t165), self->val_size);
        U64_delete(_t165, &(Bool){1});
        U64 *_t167 = malloc(sizeof(U64)); *_t167 = U64_mul(DEREF(lo), self->val_size);
        U64 *_t168 = malloc(sizeof(U64)); *_t168 = U64_sub(self->count, DEREF(lo));
        void *_t169 = ptr_add(self->val_data, DEREF(_t166));
        void *_t170 = ptr_add(self->val_data, DEREF(_t167));
        U64 *_t171 = malloc(sizeof(U64)); *_t171 = U64_mul(DEREF(_t168), self->val_size);
        U64_delete(_t168, &(Bool){1});
        memmove(_t169, _t170, DEREF(_t171));
        U64_delete(_t166, &(Bool){1});
        U64_delete(_t167, &(Bool){1});
        U64_delete(_t171, &(Bool){1});
        U64 *_t172 = malloc(sizeof(U64)); *_t172 = U64_mul(DEREF(lo), self->key_size);
        void *_t173 = ptr_add(self->key_data, DEREF(_t172));
        memcpy(_t173, key, self->key_size);
        U64_delete(_t172, &(Bool){1});
        U64 *_t174 = malloc(sizeof(U64)); *_t174 = U64_mul(DEREF(lo), self->val_size);
        void *_t175 = ptr_add(self->val_data, DEREF(_t174));
        memcpy(_t175, val, self->val_size);
        U64_delete(_t174, &(Bool){1});
        free(key);
        free(val);
        I64 *_t176 = malloc(sizeof(I64));
        *_t176 = 1;
        U64 *_t177 = malloc(sizeof(U64)); *_t177 = U64_add(self->count, DEREF(_t176));
        I64_delete(_t176, &(Bool){1});
        self->count = DEREF(_t177);
        U64_delete(_t177, &(Bool){1});
    }
    Bool_delete(found, &(Bool){1});
    U64_delete(lo, &(Bool){1});
}

void Map_delete(Map * self, Bool * call_free) {
    {
        U64 *_fi178 = malloc(sizeof(U64));
        *_fi178 = 0;
        while (1) {
            I64 *_t180 = malloc(sizeof(I64));
            *_t180 = 0;
            Range *_t181 = Range_new(DEREF(_t180), self->count);
            I64_delete(_t180, &(Bool){1});
            U64 *_t182 = Range_len(_t181);
            Range_delete(_t181, &(Bool){1});
            Bool *_wcond179 = U64_lt(_fi178, _t182);
            U64_delete(_t182, &(Bool){1});
            if (DEREF(_wcond179)) {
            } else {
                Bool_delete(_wcond179, &(Bool){1});
                break;
            }
            Bool_delete(_wcond179, &(Bool){1});
            I64 *_t183 = malloc(sizeof(I64));
            *_t183 = 0;
            Range *_t184 = Range_new(DEREF(_t183), self->count);
            I64_delete(_t183, &(Bool){1});
            U64 *i = Range_get(_t184, DEREF(_fi178));
            Range_delete(_t184, &(Bool){1});
            I64 *_t185 = malloc(sizeof(I64));
            *_t185 = 1;
            U64 *_t186 = malloc(sizeof(U64)); *_t186 = U64_add(DEREF(_fi178), DEREF(_t185));
            I64_delete(_t185, &(Bool){1});
            *_fi178 = DEREF(_t186);
            U64_delete(_t186, &(Bool){1});
            U64 *_t187 = malloc(sizeof(U64)); *_t187 = U64_mul(DEREF(i), self->key_size);
            void *_t188 = ptr_add(self->key_data, DEREF(_t187));
            Bool *_t189 = malloc(sizeof(Bool));
            *_t189 = 0;
            dyn_call_delete(&self->key_type, _t188, _t189);
            U64_delete(_t187, &(Bool){1});
            Bool_delete(_t189, &(Bool){1});
            U64 *_t190 = malloc(sizeof(U64)); *_t190 = U64_mul(DEREF(i), self->val_size);
            U64_delete(i, &(Bool){1});
            void *_t191 = ptr_add(self->val_data, DEREF(_t190));
            Bool *_t192 = malloc(sizeof(Bool));
            *_t192 = 0;
            dyn_call_delete(&self->val_type, _t191, _t192);
            U64_delete(_t190, &(Bool){1});
            Bool_delete(_t192, &(Bool){1});
        }
        U64_delete(_fi178, &(Bool){1});
    }
    free(self->key_data);
    free(self->val_data);
    Bool *_t193 = malloc(sizeof(Bool));
    *_t193 = 0;
    Str_delete(&self->key_type, _t193);
    Bool_delete(_t193, &(Bool){1});
    Bool *_t194 = malloc(sizeof(Bool));
    *_t194 = 0;
    Str_delete(&self->val_type, _t194);
    Bool_delete(_t194, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    U64 *_t212 = malloc(sizeof(U64)); *_t212 = U64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(DEREF(_t212));
    U64_delete(_t212, &(Bool){1});
    U64 *_t213 = malloc(sizeof(U64)); *_t213 = U64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(DEREF(_t213));
    U64_delete(_t213, &(Bool){1});
    {
        U64 *_fi195 = malloc(sizeof(U64));
        *_fi195 = 0;
        while (1) {
            I64 *_t197 = malloc(sizeof(I64));
            *_t197 = 0;
            Range *_t198 = Range_new(DEREF(_t197), self->count);
            I64_delete(_t197, &(Bool){1});
            U64 *_t199 = Range_len(_t198);
            Range_delete(_t198, &(Bool){1});
            Bool *_wcond196 = U64_lt(_fi195, _t199);
            U64_delete(_t199, &(Bool){1});
            if (DEREF(_wcond196)) {
            } else {
                Bool_delete(_wcond196, &(Bool){1});
                break;
            }
            Bool_delete(_wcond196, &(Bool){1});
            I64 *_t200 = malloc(sizeof(I64));
            *_t200 = 0;
            Range *_t201 = Range_new(DEREF(_t200), self->count);
            I64_delete(_t200, &(Bool){1});
            U64 *i = Range_get(_t201, DEREF(_fi195));
            Range_delete(_t201, &(Bool){1});
            I64 *_t202 = malloc(sizeof(I64));
            *_t202 = 1;
            U64 *_t203 = malloc(sizeof(U64)); *_t203 = U64_add(DEREF(_fi195), DEREF(_t202));
            I64_delete(_t202, &(Bool){1});
            *_fi195 = DEREF(_t203);
            U64_delete(_t203, &(Bool){1});
            U64 *_t204 = malloc(sizeof(U64)); *_t204 = U64_mul(DEREF(i), self->key_size);
            void *_t205 = ptr_add(self->key_data, DEREF(_t204));
            void *ck = dyn_call_clone(&self->key_type, _t205);
            U64_delete(_t204, &(Bool){1});
            U64 *_t206 = malloc(sizeof(U64)); *_t206 = U64_mul(DEREF(i), self->key_size);
            void *_t207 = ptr_add(new_keys, DEREF(_t206));
            memcpy(_t207, ck, self->key_size);
            U64_delete(_t206, &(Bool){1});
            free(ck);
            U64 *_t208 = malloc(sizeof(U64)); *_t208 = U64_mul(DEREF(i), self->val_size);
            void *_t209 = ptr_add(self->val_data, DEREF(_t208));
            void *cv = dyn_call_clone(&self->val_type, _t209);
            U64_delete(_t208, &(Bool){1});
            U64 *_t210 = malloc(sizeof(U64)); *_t210 = U64_mul(DEREF(i), self->val_size);
            U64_delete(i, &(Bool){1});
            void *_t211 = ptr_add(new_vals, DEREF(_t210));
            memcpy(_t211, cv, self->val_size);
            U64_delete(_t210, &(Bool){1});
            free(cv);
        }
        U64_delete(_fi195, &(Bool){1});
    }
    Map *_t214 = malloc(sizeof(Map));
    _t214->key_data = new_keys;
    _t214->val_data = new_vals;
    _t214->count = self->count;
    _t214->cap = self->cap;
    _t214->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t214->key_type = *_ca; free(_ca); }
    _t214->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t214->val_type = *_ca; free(_ca); }
    return _t214;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    Bool *_t226 = dyn_has_cmp(elem_type);
    Bool *_t227 = malloc(sizeof(Bool)); *_t227 = Bool_not(DEREF(_t226));
    Bool_delete(_t226, &(Bool){1});
    if (DEREF(_t227)) {
        Str *_t216 = Str_lit("Str", 3ULL);
        I64 *_t217 = Str_size();
        I64 *_t218 = malloc(sizeof(I64));
        *_t218 = 3;
        Array *_va4 = Array_new(_t216, _t217, _t218);
        Str_delete(_t216, &(Bool){1});
        I64_delete(_t217, &(Bool){1});
        I64_delete(_t218, &(Bool){1});
        I64 *_t219 = malloc(sizeof(I64));
        *_t219 = 0;
        Str *_t220 = Str_lit("type ", 5ULL);
        Array_set(_va4, _t219, _t220);
        I64_delete(_t219, &(Bool){1});
        I64 *_t221 = malloc(sizeof(I64));
        *_t221 = 1;
        Str *_t222 = Str_clone(elem_type);
        Array_set(_va4, _t221, _t222);
        I64_delete(_t221, &(Bool){1});
        I64 *_t223 = malloc(sizeof(I64));
        *_t223 = 2;
        Str *_t224 = Str_lit(" must implement cmp", 19ULL);
        Array_set(_va4, _t223, _t224);
        I64_delete(_t223, &(Bool){1});
        Str *_t225 = Str_lit("Set.new", 7ULL);
        panic(_t225, _va4);
        Str_delete(_t225, &(Bool){1});
        Array_delete(_va4, &(Bool){1});
    }
    Bool_delete(_t227, &(Bool){1});
    void *_t228 = malloc(DEREF(elem_size));
    U64 *_t229 = malloc(sizeof(U64));
    *_t229 = 0;
    I64 *_t230 = malloc(sizeof(I64));
    *_t230 = 1;
    U64 *_t231 = U64_clone(elem_size);
    Set *_t232 = malloc(sizeof(Set));
    _t232->data = _t228;
    _t232->count = DEREF(_t229);
    _t232->cap = DEREF(_t230);
    _t232->elem_size = DEREF(_t231);
    { Str *_ca = Str_clone(elem_type); _t232->elem_type = *_ca; free(_ca); }
    U64_delete(_t229, &(Bool){1});
    I64_delete(_t230, &(Bool){1});
    U64_delete(_t231, &(Bool){1});
    return _t232;
}

U64 * Set_len(Set * self) {
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Set_has(Set * self, void * val) {
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    while (1) {
        Bool *_wcond233 = U64_lt(lo, hi);
        if (DEREF(_wcond233)) {
        } else {
            Bool_delete(_wcond233, &(Bool){1});
            break;
        }
        Bool_delete(_wcond233, &(Bool){1});
        U64 *_t240 = malloc(sizeof(U64)); *_t240 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t241 = malloc(sizeof(I64));
        *_t241 = 2;
        U64 *_t242 = malloc(sizeof(U64)); *_t242 = U64_div(DEREF(_t240), DEREF(_t241));
        U64_delete(_t240, &(Bool){1});
        I64_delete(_t241, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t242));
        U64_delete(_t242, &(Bool){1});
        U64 *_t243 = malloc(sizeof(U64)); *_t243 = U64_mul(DEREF(mid), self->elem_size);
        void *_t244 = ptr_add(self->data, DEREF(_t243));
        I64 *c = dyn_call_cmp(&self->elem_type, _t244, val);
        U64_delete(_t243, &(Bool){1});
        I64 *_t245 = malloc(sizeof(I64));
        *_t245 = 0;
        Bool *_t246 = I64_lt(c, _t245);
        I64_delete(_t245, &(Bool){1});
        if (DEREF(_t246)) {
            I64 *_t234 = malloc(sizeof(I64));
            *_t234 = 1;
            U64 *_t235 = malloc(sizeof(U64)); *_t235 = U64_add(DEREF(mid), DEREF(_t234));
            I64_delete(_t234, &(Bool){1});
            *lo = DEREF(_t235);
            U64_delete(_t235, &(Bool){1});
        } else {
            I64 *_t238 = malloc(sizeof(I64));
            *_t238 = 0;
            Bool *_t239 = I64_gt(c, _t238);
            I64_delete(_t238, &(Bool){1});
            if (DEREF(_t239)) {
                U64 *_t236 = U64_clone(mid);
                *hi = DEREF(_t236);
                U64_delete(_t236, &(Bool){1});
            } else {
                Bool *_t237 = malloc(sizeof(Bool));
                *_t237 = 1;
                Bool_delete(_t239, &(Bool){1});
                Bool_delete(_t246, &(Bool){1});
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                U64_delete(hi, &(Bool){1});
                U64_delete(lo, &(Bool){1});
                return _t237;
            }
            Bool_delete(_t239, &(Bool){1});
        }
        Bool_delete(_t246, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    U64_delete(lo, &(Bool){1});
    Bool *_t247 = malloc(sizeof(Bool));
    *_t247 = 0;
    return _t247;
}

void Set_add(Set * self, void * val) {
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    Bool *found = malloc(sizeof(Bool));
    *found = 0;
    while (1) {
        Bool *_wcond248 = U64_lt(lo, hi);
        if (DEREF(_wcond248)) {
        } else {
            Bool_delete(_wcond248, &(Bool){1});
            break;
        }
        Bool_delete(_wcond248, &(Bool){1});
        U64 *_t257 = malloc(sizeof(U64)); *_t257 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t258 = malloc(sizeof(I64));
        *_t258 = 2;
        U64 *_t259 = malloc(sizeof(U64)); *_t259 = U64_div(DEREF(_t257), DEREF(_t258));
        U64_delete(_t257, &(Bool){1});
        I64_delete(_t258, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t259));
        U64_delete(_t259, &(Bool){1});
        U64 *_t260 = malloc(sizeof(U64)); *_t260 = U64_mul(DEREF(mid), self->elem_size);
        void *_t261 = ptr_add(self->data, DEREF(_t260));
        I64 *c = dyn_call_cmp(&self->elem_type, _t261, val);
        U64_delete(_t260, &(Bool){1});
        I64 *_t262 = malloc(sizeof(I64));
        *_t262 = 0;
        Bool *_t263 = I64_lt(c, _t262);
        I64_delete(_t262, &(Bool){1});
        if (DEREF(_t263)) {
            I64 *_t249 = malloc(sizeof(I64));
            *_t249 = 1;
            U64 *_t250 = malloc(sizeof(U64)); *_t250 = U64_add(DEREF(mid), DEREF(_t249));
            I64_delete(_t249, &(Bool){1});
            *lo = DEREF(_t250);
            U64_delete(_t250, &(Bool){1});
        } else {
            I64 *_t255 = malloc(sizeof(I64));
            *_t255 = 0;
            Bool *_t256 = I64_gt(c, _t255);
            I64_delete(_t255, &(Bool){1});
            if (DEREF(_t256)) {
                U64 *_t251 = U64_clone(mid);
                *hi = DEREF(_t251);
                U64_delete(_t251, &(Bool){1});
            } else {
                Bool *_t252 = malloc(sizeof(Bool));
                *_t252 = 1;
                *found = DEREF(_t252);
                Bool_delete(_t252, &(Bool){1});
                U64 *_t253 = U64_clone(mid);
                *lo = DEREF(_t253);
                U64_delete(_t253, &(Bool){1});
                U64 *_t254 = U64_clone(mid);
                *hi = DEREF(_t254);
                U64_delete(_t254, &(Bool){1});
            }
            Bool_delete(_t256, &(Bool){1});
        }
        Bool_delete(_t263, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    if (DEREF(found)) {
        Bool *_t264 = malloc(sizeof(Bool));
        *_t264 = 0;
        dyn_call_delete(&self->elem_type, val, _t264);
        Bool_delete(_t264, &(Bool){1});
        free(val);
    } else {
        Bool *_t269 = malloc(sizeof(Bool)); *_t269 = U64_eq(self->count, self->cap);
        if (DEREF(_t269)) {
            I64 *_t265 = malloc(sizeof(I64));
            *_t265 = 2;
            U64 *new_cap = malloc(sizeof(U64)); *new_cap = U64_mul(self->cap, DEREF(_t265));
            I64_delete(_t265, &(Bool){1});
            U64 *_t266 = malloc(sizeof(U64)); *_t266 = U64_mul(DEREF(new_cap), self->elem_size);
            void *_t267 = realloc(self->data, DEREF(_t266));
            U64_delete(_t266, &(Bool){1});
            self->data = _t267;
            U64 *_t268 = U64_clone(new_cap);
            U64_delete(new_cap, &(Bool){1});
            self->cap = DEREF(_t268);
            U64_delete(_t268, &(Bool){1});
        }
        Bool_delete(_t269, &(Bool){1});
        I64 *_t270 = malloc(sizeof(I64));
        *_t270 = 1;
        U64 *_t271 = malloc(sizeof(U64)); *_t271 = U64_add(DEREF(lo), DEREF(_t270));
        I64_delete(_t270, &(Bool){1});
        U64 *_t272 = malloc(sizeof(U64)); *_t272 = U64_mul(DEREF(_t271), self->elem_size);
        U64_delete(_t271, &(Bool){1});
        U64 *_t273 = malloc(sizeof(U64)); *_t273 = U64_mul(DEREF(lo), self->elem_size);
        U64 *_t274 = malloc(sizeof(U64)); *_t274 = U64_sub(self->count, DEREF(lo));
        void *_t275 = ptr_add(self->data, DEREF(_t272));
        void *_t276 = ptr_add(self->data, DEREF(_t273));
        U64 *_t277 = malloc(sizeof(U64)); *_t277 = U64_mul(DEREF(_t274), self->elem_size);
        U64_delete(_t274, &(Bool){1});
        memmove(_t275, _t276, DEREF(_t277));
        U64_delete(_t272, &(Bool){1});
        U64_delete(_t273, &(Bool){1});
        U64_delete(_t277, &(Bool){1});
        U64 *_t278 = malloc(sizeof(U64)); *_t278 = U64_mul(DEREF(lo), self->elem_size);
        void *_t279 = ptr_add(self->data, DEREF(_t278));
        memcpy(_t279, val, self->elem_size);
        U64_delete(_t278, &(Bool){1});
        free(val);
        I64 *_t280 = malloc(sizeof(I64));
        *_t280 = 1;
        U64 *_t281 = malloc(sizeof(U64)); *_t281 = U64_add(self->count, DEREF(_t280));
        I64_delete(_t280, &(Bool){1});
        self->count = DEREF(_t281);
        U64_delete(_t281, &(Bool){1});
    }
    Bool_delete(found, &(Bool){1});
    U64_delete(lo, &(Bool){1});
}

void Set_delete(Set * self, Bool * call_free) {
    {
        U64 *_fi282 = malloc(sizeof(U64));
        *_fi282 = 0;
        while (1) {
            I64 *_t284 = malloc(sizeof(I64));
            *_t284 = 0;
            Range *_t285 = Range_new(DEREF(_t284), self->count);
            I64_delete(_t284, &(Bool){1});
            U64 *_t286 = Range_len(_t285);
            Range_delete(_t285, &(Bool){1});
            Bool *_wcond283 = U64_lt(_fi282, _t286);
            U64_delete(_t286, &(Bool){1});
            if (DEREF(_wcond283)) {
            } else {
                Bool_delete(_wcond283, &(Bool){1});
                break;
            }
            Bool_delete(_wcond283, &(Bool){1});
            I64 *_t287 = malloc(sizeof(I64));
            *_t287 = 0;
            Range *_t288 = Range_new(DEREF(_t287), self->count);
            I64_delete(_t287, &(Bool){1});
            U64 *i = Range_get(_t288, DEREF(_fi282));
            Range_delete(_t288, &(Bool){1});
            I64 *_t289 = malloc(sizeof(I64));
            *_t289 = 1;
            U64 *_t290 = malloc(sizeof(U64)); *_t290 = U64_add(DEREF(_fi282), DEREF(_t289));
            I64_delete(_t289, &(Bool){1});
            *_fi282 = DEREF(_t290);
            U64_delete(_t290, &(Bool){1});
            U64 *_t291 = malloc(sizeof(U64)); *_t291 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t292 = ptr_add(self->data, DEREF(_t291));
            Bool *_t293 = malloc(sizeof(Bool));
            *_t293 = 0;
            dyn_call_delete(&self->elem_type, _t292, _t293);
            U64_delete(_t291, &(Bool){1});
            Bool_delete(_t293, &(Bool){1});
        }
        U64_delete(_fi282, &(Bool){1});
    }
    free(self->data);
    Bool *_t294 = malloc(sizeof(Bool));
    *_t294 = 0;
    Str_delete(&self->elem_type, _t294);
    Bool_delete(_t294, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    U64 *_t308 = malloc(sizeof(U64)); *_t308 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t308));
    U64_delete(_t308, &(Bool){1});
    {
        U64 *_fi295 = malloc(sizeof(U64));
        *_fi295 = 0;
        while (1) {
            I64 *_t297 = malloc(sizeof(I64));
            *_t297 = 0;
            Range *_t298 = Range_new(DEREF(_t297), self->count);
            I64_delete(_t297, &(Bool){1});
            U64 *_t299 = Range_len(_t298);
            Range_delete(_t298, &(Bool){1});
            Bool *_wcond296 = U64_lt(_fi295, _t299);
            U64_delete(_t299, &(Bool){1});
            if (DEREF(_wcond296)) {
            } else {
                Bool_delete(_wcond296, &(Bool){1});
                break;
            }
            Bool_delete(_wcond296, &(Bool){1});
            I64 *_t300 = malloc(sizeof(I64));
            *_t300 = 0;
            Range *_t301 = Range_new(DEREF(_t300), self->count);
            I64_delete(_t300, &(Bool){1});
            U64 *i = Range_get(_t301, DEREF(_fi295));
            Range_delete(_t301, &(Bool){1});
            I64 *_t302 = malloc(sizeof(I64));
            *_t302 = 1;
            U64 *_t303 = malloc(sizeof(U64)); *_t303 = U64_add(DEREF(_fi295), DEREF(_t302));
            I64_delete(_t302, &(Bool){1});
            *_fi295 = DEREF(_t303);
            U64_delete(_t303, &(Bool){1});
            U64 *_t304 = malloc(sizeof(U64)); *_t304 = U64_mul(DEREF(i), self->elem_size);
            void *_t305 = ptr_add(self->data, DEREF(_t304));
            void *cloned = dyn_call_clone(&self->elem_type, _t305);
            U64_delete(_t304, &(Bool){1});
            U64 *_t306 = malloc(sizeof(U64)); *_t306 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t307 = ptr_add(new_data, DEREF(_t306));
            memcpy(_t307, cloned, self->elem_size);
            U64_delete(_t306, &(Bool){1});
            free(cloned);
        }
        U64_delete(_fi295, &(Bool){1});
    }
    Set *_t309 = malloc(sizeof(Set));
    _t309->data = new_data;
    _t309->count = self->count;
    _t309->cap = self->cap;
    _t309->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t309->elem_type = *_ca; free(_ca); }
    return _t309;
}

U64 *Set_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Set);
    return r;
}

U64 * Str_len(Str * self) {
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

U8 * Str_get(Str * self, U64 * i) {
    Bool *_t317 = U64_gte(i, &self->count);
    if (DEREF(_t317)) {
        Str *_t311 = Str_lit("Str", 3ULL);
        I64 *_t312 = Str_size();
        I64 *_t313 = malloc(sizeof(I64));
        *_t313 = 1;
        Array *_va5 = Array_new(_t311, _t312, _t313);
        Str_delete(_t311, &(Bool){1});
        I64_delete(_t312, &(Bool){1});
        I64_delete(_t313, &(Bool){1});
        I64 *_t314 = malloc(sizeof(I64));
        *_t314 = 0;
        Str *_t315 = Str_lit("index out of bounds", 19ULL);
        Array_set(_va5, _t314, _t315);
        I64_delete(_t314, &(Bool){1});
        Str *_t316 = Str_lit("Str.get", 7ULL);
        panic(_t316, _va5);
        Str_delete(_t316, &(Bool){1});
        Array_delete(_va5, &(Bool){1});
    }
    Bool_delete(_t317, &(Bool){1});
    void *_t318 = ptr_add(self->c_str, DEREF(i));
    return _t318;
}

I64 * Str_cmp(Str * a, Str * b) {
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    U64 *min_len = malloc(sizeof(U64));
    *min_len = a->count;
    Bool *_t324 = U64_lt(&b->count, &a->count);
    if (DEREF(_t324)) {
        *min_len = b->count;
    }
    Bool_delete(_t324, &(Bool){1});
    while (1) {
        Bool *_wcond319 = U64_lt(i, min_len);
        if (DEREF(_wcond319)) {
        } else {
            Bool_delete(_wcond319, &(Bool){1});
            break;
        }
        Bool_delete(_wcond319, &(Bool){1});
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 *_t320 = malloc(sizeof(I64));
        *_t320 = 0;
        Bool *_t321 = I64_neq(c, _t320);
        I64_delete(_t320, &(Bool){1});
        if (DEREF(_t321)) {
            Bool_delete(_t321, &(Bool){1});
            U64_delete(i, &(Bool){1});
            U64_delete(min_len, &(Bool){1});
            return c;
        }
        Bool_delete(_t321, &(Bool){1});
        I64_delete(c, &(Bool){1});
        I64 *_t322 = malloc(sizeof(I64));
        *_t322 = 1;
        U64 *_t323 = malloc(sizeof(U64)); *_t323 = U64_add(DEREF(i), DEREF(_t322));
        I64_delete(_t322, &(Bool){1});
        *i = DEREF(_t323);
        U64_delete(_t323, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    U64_delete(min_len, &(Bool){1});
    I64 *_t325 = malloc(sizeof(I64)); *_t325 = U64_cmp(a->count, b->count);
    return _t325;
}

Str * Str_concat(Str * a, Str * b) {
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    I64 *_t326 = malloc(sizeof(I64));
    *_t326 = 1;
    U64 *_t327 = malloc(sizeof(U64)); *_t327 = U64_add(DEREF(new_len), DEREF(_t326));
    I64_delete(_t326, &(Bool){1});
    U8 *new_data = malloc(DEREF(_t327));
    U64_delete(_t327, &(Bool){1});
    memcpy(new_data, a->c_str, a->count);
    void *_t328 = ptr_add(new_data, a->count);
    memcpy(_t328, b->c_str, b->count);
    I64 *_t329 = malloc(sizeof(I64));
    *_t329 = 0;
    void *_t330 = ptr_add(new_data, DEREF(new_len));
    U8 *_t331 = U8_from_i64(_t329);
    I64_delete(_t329, &(Bool){1});
    I64 *_t332 = malloc(sizeof(I64));
    *_t332 = 1;
    memcpy(_t330, _t331, DEREF(_t332));
    U8_delete(_t331, &(Bool){1});
    I64_delete(_t332, &(Bool){1});
    U64 *_t333 = U64_clone(new_len);
    U64 *_t334 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t335 = malloc(sizeof(Str));
    _t335->c_str = new_data;
    _t335->count = DEREF(_t333);
    _t335->cap = DEREF(_t334);
    U64_delete(_t333, &(Bool){1});
    U64_delete(_t334, &(Bool){1});
    return _t335;
}

Str * Str_with_capacity(U64 * n) {
    I64 *_t336 = malloc(sizeof(I64));
    *_t336 = 1;
    U64 *_t337 = malloc(sizeof(U64)); *_t337 = U64_add(DEREF(n), DEREF(_t336));
    I64_delete(_t336, &(Bool){1});
    U8 *buf = malloc(DEREF(_t337));
    U64_delete(_t337, &(Bool){1});
    I64 *_t338 = malloc(sizeof(I64));
    *_t338 = 0;
    U8 *_t339 = U8_from_i64(_t338);
    I64_delete(_t338, &(Bool){1});
    I64 *_t340 = malloc(sizeof(I64));
    *_t340 = 1;
    memcpy(buf, _t339, DEREF(_t340));
    U8_delete(_t339, &(Bool){1});
    I64_delete(_t340, &(Bool){1});
    I64 *_t341 = malloc(sizeof(I64));
    *_t341 = 0;
    U64 *_t342 = U64_clone(n);
    Str *_t343 = malloc(sizeof(Str));
    _t343->c_str = buf;
    _t343->count = DEREF(_t341);
    _t343->cap = DEREF(_t342);
    I64_delete(_t341, &(Bool){1});
    U64_delete(_t342, &(Bool){1});
    return _t343;
}

void Str_push_str(Str * self, Str * s) {
    Bool *_t356 = U64_gte(&self->cap, CAP_VIEW);
    if (DEREF(_t356)) {
        Str *_t344 = Str_lit("Str", 3ULL);
        I64 *_t345 = Str_size();
        I64 *_t346 = malloc(sizeof(I64));
        *_t346 = 1;
        Array *_va6 = Array_new(_t344, _t345, _t346);
        Str_delete(_t344, &(Bool){1});
        I64_delete(_t345, &(Bool){1});
        I64_delete(_t346, &(Bool){1});
        I64 *_t347 = malloc(sizeof(I64));
        *_t347 = 0;
        Str *_t348 = Str_lit("cannot mutate a string view or literal", 38ULL);
        Array_set(_va6, _t347, _t348);
        I64_delete(_t347, &(Bool){1});
        Str *_t349 = Str_lit("Str.push_str", 12ULL);
        panic(_t349, _va6);
        Str_delete(_t349, &(Bool){1});
        Array_delete(_va6, &(Bool){1});
    }
    Bool_delete(_t356, &(Bool){1});
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool *_t357 = U64_gt(new_len, &self->cap);
    if (DEREF(_t357)) {
        Str *_t350 = Str_lit("Str", 3ULL);
        I64 *_t351 = Str_size();
        I64 *_t352 = malloc(sizeof(I64));
        *_t352 = 1;
        Array *_va7 = Array_new(_t350, _t351, _t352);
        Str_delete(_t350, &(Bool){1});
        I64_delete(_t351, &(Bool){1});
        I64_delete(_t352, &(Bool){1});
        I64 *_t353 = malloc(sizeof(I64));
        *_t353 = 0;
        Str *_t354 = Str_lit("capacity exceeded", 17ULL);
        Array_set(_va7, _t353, _t354);
        I64_delete(_t353, &(Bool){1});
        Str *_t355 = Str_lit("Str.push_str", 12ULL);
        panic(_t355, _va7);
        Str_delete(_t355, &(Bool){1});
        Array_delete(_va7, &(Bool){1});
    }
    Bool_delete(_t357, &(Bool){1});
    void *_t358 = ptr_add(self->c_str, self->count);
    memcpy(_t358, s->c_str, s->count);
    U64 *_t359 = U64_clone(new_len);
    self->count = DEREF(_t359);
    U64_delete(_t359, &(Bool){1});
    I64 *_t360 = malloc(sizeof(I64));
    *_t360 = 0;
    void *_t361 = ptr_add(self->c_str, DEREF(new_len));
    U8 *_t362 = U8_from_i64(_t360);
    I64_delete(_t360, &(Bool){1});
    I64 *_t363 = malloc(sizeof(I64));
    *_t363 = 1;
    memcpy(_t361, _t362, DEREF(_t363));
    U8_delete(_t362, &(Bool){1});
    I64_delete(_t363, &(Bool){1});
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    I64 *_t364 = malloc(sizeof(I64));
    *_t364 = 1;
    U64 *_t365 = malloc(sizeof(U64)); *_t365 = U64_add(val->count, DEREF(_t364));
    I64_delete(_t364, &(Bool){1});
    U8 *new_data = malloc(DEREF(_t365));
    U64_delete(_t365, &(Bool){1});
    memcpy(new_data, val->c_str, val->count);
    I64 *_t366 = malloc(sizeof(I64));
    *_t366 = 0;
    void *_t367 = ptr_add(new_data, val->count);
    U8 *_t368 = U8_from_i64(_t366);
    I64_delete(_t366, &(Bool){1});
    I64 *_t369 = malloc(sizeof(I64));
    *_t369 = 1;
    memcpy(_t367, _t368, DEREF(_t369));
    U8_delete(_t368, &(Bool){1});
    I64_delete(_t369, &(Bool){1});
    Str *_t370 = malloc(sizeof(Str));
    _t370->c_str = new_data;
    _t370->count = val->count;
    _t370->cap = val->count;
    return _t370;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool *_t371 = U64_lt(&self->cap, CAP_VIEW);
    if (DEREF(_t371)) {
        free(self->c_str);
    }
    Bool_delete(_t371, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t372 = Str_clone(val);
    return _t372;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = U64_clone(start);
    U64 *ln = U64_clone(n);
    Bool *_t374 = U64_gt(st, &s->count);
    if (DEREF(_t374)) {
        *st = s->count;
    }
    Bool_delete(_t374, &(Bool){1});
    U64 *_t375 = malloc(sizeof(U64)); *_t375 = U64_add(DEREF(st), DEREF(ln));
    Bool *_t376 = U64_gt(_t375, &s->count);
    U64_delete(_t375, &(Bool){1});
    if (DEREF(_t376)) {
        U64 *_t373 = malloc(sizeof(U64)); *_t373 = U64_sub(s->count, DEREF(st));
        *ln = DEREF(_t373);
        U64_delete(_t373, &(Bool){1});
    }
    Bool_delete(_t376, &(Bool){1});
    void *_t377 = ptr_add(s->c_str, DEREF(st));
    U64 *_t378 = U64_clone(ln);
    U64_delete(ln, &(Bool){1});
    U64 *_t379 = U64_clone(CAP_VIEW);
    Str *_t380 = malloc(sizeof(Str));
    _t380->c_str = _t377;
    _t380->count = DEREF(_t378);
    _t380->cap = DEREF(_t379);
    U64_delete(_t378, &(Bool){1});
    U64_delete(_t379, &(Bool){1});
    U64_delete(st, &(Bool){1});
    return _t380;
}

Bool * Str_contains(Str * a, Str * b) {
    I64 *_t394 = malloc(sizeof(I64));
    *_t394 = 0;
    Bool *_t395 = malloc(sizeof(Bool)); *_t395 = U64_eq(b->count, DEREF(_t394));
    I64_delete(_t394, &(Bool){1});
    if (DEREF(_t395)) {
        Bool *_t381 = malloc(sizeof(Bool));
        *_t381 = 1;
        Bool_delete(_t395, &(Bool){1});
        return _t381;
    }
    Bool_delete(_t395, &(Bool){1});
    Bool *_t396 = U64_gt(&b->count, &a->count);
    if (DEREF(_t396)) {
        Bool *_t382 = malloc(sizeof(Bool));
        *_t382 = 0;
        Bool_delete(_t396, &(Bool){1});
        return _t382;
    }
    Bool_delete(_t396, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t391 = malloc(sizeof(U64)); *_t391 = U64_sub(a->count, b->count);
        Bool *_wcond383 = U64_lte(i, _t391);
        U64_delete(_t391, &(Bool){1});
        if (DEREF(_wcond383)) {
        } else {
            Bool_delete(_wcond383, &(Bool){1});
            break;
        }
        Bool_delete(_wcond383, &(Bool){1});
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond384 = U64_lt(j, &b->count);
            if (DEREF(_wcond384)) {
            } else {
                Bool_delete(_wcond384, &(Bool){1});
                break;
            }
            Bool_delete(_wcond384, &(Bool){1});
            U64 *_t386 = malloc(sizeof(U64)); *_t386 = U64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(a, _t386);
            U8 *bc = Str_get(b, j);
            Bool *_t387 = U8_neq(ac, bc);
            U64_delete(_t386, &(Bool){1});
            if (DEREF(_t387)) {
                Bool *_t385 = malloc(sizeof(Bool));
                *_t385 = 0;
                *found = DEREF(_t385);
                Bool_delete(_t385, &(Bool){1});
            }
            Bool_delete(_t387, &(Bool){1});
            I64 *_t388 = malloc(sizeof(I64));
            *_t388 = 1;
            U64 *_t389 = malloc(sizeof(U64)); *_t389 = U64_add(DEREF(j), DEREF(_t388));
            I64_delete(_t388, &(Bool){1});
            *j = DEREF(_t389);
            U64_delete(_t389, &(Bool){1});
        }
        U64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            Bool *_t390 = malloc(sizeof(Bool));
            *_t390 = 1;
            Bool_delete(found, &(Bool){1});
            U64_delete(i, &(Bool){1});
            return _t390;
        }
        Bool_delete(found, &(Bool){1});
        I64 *_t392 = malloc(sizeof(I64));
        *_t392 = 1;
        U64 *_t393 = malloc(sizeof(U64)); *_t393 = U64_add(DEREF(i), DEREF(_t392));
        I64_delete(_t392, &(Bool){1});
        *i = DEREF(_t393);
        U64_delete(_t393, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    Bool *_t397 = malloc(sizeof(Bool));
    *_t397 = 0;
    return _t397;
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool *_t404 = U64_gt(&b->count, &a->count);
    if (DEREF(_t404)) {
        Bool *_t398 = malloc(sizeof(Bool));
        *_t398 = 0;
        Bool_delete(_t404, &(Bool){1});
        return _t398;
    }
    Bool_delete(_t404, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool *_wcond399 = U64_lt(i, &b->count);
        if (DEREF(_wcond399)) {
        } else {
            Bool_delete(_wcond399, &(Bool){1});
            break;
        }
        Bool_delete(_wcond399, &(Bool){1});
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool *_t401 = U8_neq(ac, bc);
        if (DEREF(_t401)) {
            Bool *_t400 = malloc(sizeof(Bool));
            *_t400 = 0;
            Bool_delete(_t401, &(Bool){1});
            U64_delete(i, &(Bool){1});
            return _t400;
        }
        Bool_delete(_t401, &(Bool){1});
        I64 *_t402 = malloc(sizeof(I64));
        *_t402 = 1;
        U64 *_t403 = malloc(sizeof(U64)); *_t403 = U64_add(DEREF(i), DEREF(_t402));
        I64_delete(_t402, &(Bool){1});
        *i = DEREF(_t403);
        U64_delete(_t403, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    Bool *_t405 = malloc(sizeof(Bool));
    *_t405 = 1;
    return _t405;
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool *_t413 = U64_gt(&b->count, &a->count);
    if (DEREF(_t413)) {
        Bool *_t406 = malloc(sizeof(Bool));
        *_t406 = 0;
        Bool_delete(_t413, &(Bool){1});
        return _t406;
    }
    Bool_delete(_t413, &(Bool){1});
    U64 *offset = malloc(sizeof(U64)); *offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool *_wcond407 = U64_lt(i, &b->count);
        if (DEREF(_wcond407)) {
        } else {
            Bool_delete(_wcond407, &(Bool){1});
            break;
        }
        Bool_delete(_wcond407, &(Bool){1});
        U64 *_t409 = malloc(sizeof(U64)); *_t409 = U64_add(DEREF(offset), DEREF(i));
        U8 *ac = Str_get(a, _t409);
        U8 *bc = Str_get(b, i);
        Bool *_t410 = U8_neq(ac, bc);
        U64_delete(_t409, &(Bool){1});
        if (DEREF(_t410)) {
            Bool *_t408 = malloc(sizeof(Bool));
            *_t408 = 0;
            Bool_delete(_t410, &(Bool){1});
            U64_delete(i, &(Bool){1});
            U64_delete(offset, &(Bool){1});
            return _t408;
        }
        Bool_delete(_t410, &(Bool){1});
        I64 *_t411 = malloc(sizeof(I64));
        *_t411 = 1;
        U64 *_t412 = malloc(sizeof(U64)); *_t412 = U64_add(DEREF(i), DEREF(_t411));
        I64_delete(_t411, &(Bool){1});
        *i = DEREF(_t412);
        U64_delete(_t412, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    Bool *_t414 = malloc(sizeof(Bool));
    *_t414 = 1;
    return _t414;
}

Bool * Str_is_empty(Str * self) {
    I64 *_t415 = malloc(sizeof(I64));
    *_t415 = 0;
    Bool *_t416 = malloc(sizeof(Bool)); *_t416 = U64_eq(self->count, DEREF(_t415));
    I64_delete(_t415, &(Bool){1});
    return _t416;
}

I64 * Str_find(Str * self, Str * needle) {
    I64 *_t434 = malloc(sizeof(I64));
    *_t434 = 0;
    Bool *_t435 = malloc(sizeof(Bool)); *_t435 = U64_eq(needle->count, DEREF(_t434));
    I64_delete(_t434, &(Bool){1});
    if (DEREF(_t435)) {
        I64 *_t417 = malloc(sizeof(I64));
        *_t417 = 0;
        I64 *_t418 = malloc(sizeof(I64));
        *_t418 = 1;
        I64 *_t419 = malloc(sizeof(I64)); *_t419 = I64_sub(DEREF(_t417), DEREF(_t418));
        I64_delete(_t417, &(Bool){1});
        I64_delete(_t418, &(Bool){1});
        Bool_delete(_t435, &(Bool){1});
        return _t419;
    }
    Bool_delete(_t435, &(Bool){1});
    Bool *_t436 = U64_gt(&needle->count, &self->count);
    if (DEREF(_t436)) {
        I64 *_t420 = malloc(sizeof(I64));
        *_t420 = 0;
        I64 *_t421 = malloc(sizeof(I64));
        *_t421 = 1;
        I64 *_t422 = malloc(sizeof(I64)); *_t422 = I64_sub(DEREF(_t420), DEREF(_t421));
        I64_delete(_t420, &(Bool){1});
        I64_delete(_t421, &(Bool){1});
        Bool_delete(_t436, &(Bool){1});
        return _t422;
    }
    Bool_delete(_t436, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t431 = malloc(sizeof(U64)); *_t431 = U64_sub(self->count, needle->count);
        Bool *_wcond423 = U64_lte(i, _t431);
        U64_delete(_t431, &(Bool){1});
        if (DEREF(_wcond423)) {
        } else {
            Bool_delete(_wcond423, &(Bool){1});
            break;
        }
        Bool_delete(_wcond423, &(Bool){1});
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond424 = U64_lt(j, &needle->count);
            if (DEREF(_wcond424)) {
            } else {
                Bool_delete(_wcond424, &(Bool){1});
                break;
            }
            Bool_delete(_wcond424, &(Bool){1});
            U64 *_t426 = malloc(sizeof(U64)); *_t426 = U64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(self, _t426);
            U8 *bc = Str_get(needle, j);
            Bool *_t427 = U8_neq(ac, bc);
            U64_delete(_t426, &(Bool){1});
            if (DEREF(_t427)) {
                Bool *_t425 = malloc(sizeof(Bool));
                *_t425 = 0;
                *found = DEREF(_t425);
                Bool_delete(_t425, &(Bool){1});
            }
            Bool_delete(_t427, &(Bool){1});
            I64 *_t428 = malloc(sizeof(I64));
            *_t428 = 1;
            U64 *_t429 = malloc(sizeof(U64)); *_t429 = U64_add(DEREF(j), DEREF(_t428));
            I64_delete(_t428, &(Bool){1});
            *j = DEREF(_t429);
            U64_delete(_t429, &(Bool){1});
        }
        U64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            I64 *_t430 = malloc(sizeof(I64)); *_t430 = U64_to_i64(DEREF(i));
            Bool_delete(found, &(Bool){1});
            U64_delete(i, &(Bool){1});
            return _t430;
        }
        Bool_delete(found, &(Bool){1});
        I64 *_t432 = malloc(sizeof(I64));
        *_t432 = 1;
        U64 *_t433 = malloc(sizeof(U64)); *_t433 = U64_add(DEREF(i), DEREF(_t432));
        I64_delete(_t432, &(Bool){1});
        *i = DEREF(_t433);
        U64_delete(_t433, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    I64 *_t437 = malloc(sizeof(I64));
    *_t437 = 0;
    I64 *_t438 = malloc(sizeof(I64));
    *_t438 = 1;
    I64 *_t439 = malloc(sizeof(I64)); *_t439 = I64_sub(DEREF(_t437), DEREF(_t438));
    I64_delete(_t437, &(Bool){1});
    I64_delete(_t438, &(Bool){1});
    return _t439;
}

I64 * Str_rfind(Str * self, Str * needle) {
    I64 *_t457 = malloc(sizeof(I64));
    *_t457 = 0;
    Bool *_t458 = malloc(sizeof(Bool)); *_t458 = U64_eq(needle->count, DEREF(_t457));
    I64_delete(_t457, &(Bool){1});
    if (DEREF(_t458)) {
        I64 *_t440 = malloc(sizeof(I64));
        *_t440 = 0;
        I64 *_t441 = malloc(sizeof(I64));
        *_t441 = 1;
        I64 *_t442 = malloc(sizeof(I64)); *_t442 = I64_sub(DEREF(_t440), DEREF(_t441));
        I64_delete(_t440, &(Bool){1});
        I64_delete(_t441, &(Bool){1});
        Bool_delete(_t458, &(Bool){1});
        return _t442;
    }
    Bool_delete(_t458, &(Bool){1});
    Bool *_t459 = U64_gt(&needle->count, &self->count);
    if (DEREF(_t459)) {
        I64 *_t443 = malloc(sizeof(I64));
        *_t443 = 0;
        I64 *_t444 = malloc(sizeof(I64));
        *_t444 = 1;
        I64 *_t445 = malloc(sizeof(I64)); *_t445 = I64_sub(DEREF(_t443), DEREF(_t444));
        I64_delete(_t443, &(Bool){1});
        I64_delete(_t444, &(Bool){1});
        Bool_delete(_t459, &(Bool){1});
        return _t445;
    }
    Bool_delete(_t459, &(Bool){1});
    I64 *_t460 = malloc(sizeof(I64));
    *_t460 = 0;
    I64 *_t461 = malloc(sizeof(I64));
    *_t461 = 1;
    I64 *last = malloc(sizeof(I64)); *last = I64_sub(DEREF(_t460), DEREF(_t461));
    I64_delete(_t460, &(Bool){1});
    I64_delete(_t461, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t454 = malloc(sizeof(U64)); *_t454 = U64_sub(self->count, needle->count);
        Bool *_wcond446 = U64_lte(i, _t454);
        U64_delete(_t454, &(Bool){1});
        if (DEREF(_wcond446)) {
        } else {
            Bool_delete(_wcond446, &(Bool){1});
            break;
        }
        Bool_delete(_wcond446, &(Bool){1});
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond447 = U64_lt(j, &needle->count);
            if (DEREF(_wcond447)) {
            } else {
                Bool_delete(_wcond447, &(Bool){1});
                break;
            }
            Bool_delete(_wcond447, &(Bool){1});
            U64 *_t449 = malloc(sizeof(U64)); *_t449 = U64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(self, _t449);
            U8 *bc = Str_get(needle, j);
            Bool *_t450 = U8_neq(ac, bc);
            U64_delete(_t449, &(Bool){1});
            if (DEREF(_t450)) {
                Bool *_t448 = malloc(sizeof(Bool));
                *_t448 = 0;
                *found = DEREF(_t448);
                Bool_delete(_t448, &(Bool){1});
            }
            Bool_delete(_t450, &(Bool){1});
            I64 *_t451 = malloc(sizeof(I64));
            *_t451 = 1;
            U64 *_t452 = malloc(sizeof(U64)); *_t452 = U64_add(DEREF(j), DEREF(_t451));
            I64_delete(_t451, &(Bool){1});
            *j = DEREF(_t452);
            U64_delete(_t452, &(Bool){1});
        }
        U64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            I64 *_t453 = malloc(sizeof(I64)); *_t453 = U64_to_i64(DEREF(i));
            *last = DEREF(_t453);
            I64_delete(_t453, &(Bool){1});
        }
        Bool_delete(found, &(Bool){1});
        I64 *_t455 = malloc(sizeof(I64));
        *_t455 = 1;
        U64 *_t456 = malloc(sizeof(U64)); *_t456 = U64_add(DEREF(i), DEREF(_t455));
        I64_delete(_t455, &(Bool){1});
        *i = DEREF(_t456);
        U64_delete(_t456, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    return last;
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    I64 *_t477 = malloc(sizeof(I64));
    *_t477 = 0;
    Bool *_t478 = malloc(sizeof(Bool)); *_t478 = U64_eq(from->count, DEREF(_t477));
    I64_delete(_t477, &(Bool){1});
    if (DEREF(_t478)) {
        Str *_t462 = Str_clone(self);
        Bool_delete(_t478, &(Bool){1});
        return _t462;
    }
    Bool_delete(_t478, &(Bool){1});
    Str *result = Str_lit("", 0ULL);
    U64 *start = malloc(sizeof(U64));
    *start = 0;
    while (1) {
        U64 *_t464 = malloc(sizeof(U64)); *_t464 = U64_sub(self->count, from->count);
        Bool *_wcond463 = U64_lte(start, _t464);
        U64_delete(_t464, &(Bool){1});
        if (DEREF(_wcond463)) {
        } else {
            Bool_delete(_wcond463, &(Bool){1});
            break;
        }
        Bool_delete(_wcond463, &(Bool){1});
        U64 *_t465 = malloc(sizeof(U64)); *_t465 = U64_sub(self->count, DEREF(start));
        Str *rest = Str_substr(self, start, _t465);
        U64_delete(_t465, &(Bool){1});
        I64 *pos = Str_find(rest, from);
        I64 *_t466 = malloc(sizeof(I64));
        *_t466 = 0;
        I64 *_t467 = malloc(sizeof(I64));
        *_t467 = 1;
        I64 *_t468 = malloc(sizeof(I64)); *_t468 = I64_sub(DEREF(_t466), DEREF(_t467));
        I64_delete(_t466, &(Bool){1});
        I64_delete(_t467, &(Bool){1});
        Bool *_t469 = malloc(sizeof(Bool)); *_t469 = I64_eq(DEREF(pos), DEREF(_t468));
        I64_delete(_t468, &(Bool){1});
        if (DEREF(_t469)) {
            result = Str_concat(result, rest);
            Bool_delete(_t469, &(Bool){1});
            I64_delete(pos, &(Bool){1});
            Str_delete(rest, &(Bool){1});
            U64_delete(start, &(Bool){1});
            return result;
        }
        Bool_delete(_t469, &(Bool){1});
        Str_delete(rest, &(Bool){1});
        U64 *_t470 = U64_from_i64(pos);
        Str *_t471 = Str_substr(self, start, _t470);
        U64_delete(_t470, &(Bool){1});
        result = Str_concat(result, _t471);
        Str_delete(_t471, &(Bool){1});
        result = Str_concat(result, to);
        U64 *_t472 = U64_from_i64(pos);
        I64_delete(pos, &(Bool){1});
        U64 *_t473 = malloc(sizeof(U64)); *_t473 = U64_add(DEREF(start), DEREF(_t472));
        U64_delete(_t472, &(Bool){1});
        U64 *_t474 = malloc(sizeof(U64)); *_t474 = U64_add(DEREF(_t473), from->count);
        U64_delete(_t473, &(Bool){1});
        *start = DEREF(_t474);
        U64_delete(_t474, &(Bool){1});
    }
    Bool *_t479 = U64_lt(start, &self->count);
    if (DEREF(_t479)) {
        U64 *_t475 = malloc(sizeof(U64)); *_t475 = U64_sub(self->count, DEREF(start));
        Str *_t476 = Str_substr(self, start, _t475);
        U64_delete(_t475, &(Bool){1});
        result = Str_concat(result, _t476);
        Str_delete(_t476, &(Bool){1});
    }
    Bool_delete(_t479, &(Bool){1});
    U64_delete(start, &(Bool){1});
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    I64 *_t480 = malloc(sizeof(I64));
    *_t480 = 1;
    Str *_t481 = Str_substr(self, i, _t480);
    I64_delete(_t480, &(Bool){1});
    return _t481;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    Bool *_t484 = Str_starts_with(self, prefix);
    if (DEREF(_t484)) {
        U64 *_t482 = malloc(sizeof(U64)); *_t482 = U64_sub(self->count, prefix->count);
        Str *_t483 = Str_substr(self, &prefix->count, _t482);
        U64_delete(_t482, &(Bool){1});
        Bool_delete(_t484, &(Bool){1});
        return _t483;
    }
    Bool_delete(_t484, &(Bool){1});
    Str *_t485 = Str_clone(self);
    return _t485;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    Bool *_t489 = Str_ends_with(self, suffix);
    if (DEREF(_t489)) {
        I64 *_t486 = malloc(sizeof(I64));
        *_t486 = 0;
        U64 *_t487 = malloc(sizeof(U64)); *_t487 = U64_sub(self->count, suffix->count);
        Str *_t488 = Str_substr(self, _t486, _t487);
        I64_delete(_t486, &(Bool){1});
        U64_delete(_t487, &(Bool){1});
        Bool_delete(_t489, &(Bool){1});
        return _t488;
    }
    Bool_delete(_t489, &(Bool){1});
    Str *_t490 = Str_clone(self);
    return _t490;
}

Str * Str_from_byte(U8 * byte) {
    I64 *_t491 = malloc(sizeof(I64));
    *_t491 = 2;
    U8 *buf = malloc(DEREF(_t491));
    I64_delete(_t491, &(Bool){1});
    I64 *_t492 = malloc(sizeof(I64));
    *_t492 = 1;
    memcpy(buf, byte, DEREF(_t492));
    I64_delete(_t492, &(Bool){1});
    I64 *_t493 = malloc(sizeof(I64));
    *_t493 = 1;
    I64 *_t494 = malloc(sizeof(I64));
    *_t494 = 0;
    void *_t495 = ptr_add(buf, DEREF(_t493));
    U8 *_t496 = U8_from_i64(_t494);
    I64_delete(_t494, &(Bool){1});
    I64 *_t497 = malloc(sizeof(I64));
    *_t497 = 1;
    memcpy(_t495, _t496, DEREF(_t497));
    I64_delete(_t493, &(Bool){1});
    U8_delete(_t496, &(Bool){1});
    I64_delete(_t497, &(Bool){1});
    I64 *_t498 = malloc(sizeof(I64));
    *_t498 = 1;
    I64 *_t499 = malloc(sizeof(I64));
    *_t499 = 1;
    Str *_t500 = malloc(sizeof(Str));
    _t500->c_str = buf;
    _t500->count = DEREF(_t498);
    _t500->cap = DEREF(_t499);
    I64_delete(_t498, &(Bool){1});
    I64_delete(_t499, &(Bool){1});
    return _t500;
}

I64 * Str_to_i64(Str * self) {
    I64 *_t541 = malloc(sizeof(I64));
    *_t541 = 0;
    Bool *_t542 = malloc(sizeof(Bool)); *_t542 = U64_eq(self->count, DEREF(_t541));
    I64_delete(_t541, &(Bool){1});
    if (DEREF(_t542)) {
        Str *_t501 = Str_lit("Str", 3ULL);
        I64 *_t502 = Str_size();
        I64 *_t503 = malloc(sizeof(I64));
        *_t503 = 1;
        Array *_va8 = Array_new(_t501, _t502, _t503);
        Str_delete(_t501, &(Bool){1});
        I64_delete(_t502, &(Bool){1});
        I64_delete(_t503, &(Bool){1});
        I64 *_t504 = malloc(sizeof(I64));
        *_t504 = 0;
        Str *_t505 = Str_lit("empty string", 12ULL);
        Array_set(_va8, _t504, _t505);
        I64_delete(_t504, &(Bool){1});
        Str *_t506 = Str_lit("Str.to_i64", 10ULL);
        panic(_t506, _va8);
        Str_delete(_t506, &(Bool){1});
        Array_delete(_va8, &(Bool){1});
    }
    Bool_delete(_t542, &(Bool){1});
    I64 *result = malloc(sizeof(I64));
    *result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool *neg = malloc(sizeof(Bool));
    *neg = 0;
    I64 *_t543 = malloc(sizeof(I64));
    *_t543 = 0;
    U8 *first = Str_get(self, _t543);
    I64 *_t544 = malloc(sizeof(I64));
    *_t544 = 45;
    U8 *_t545 = U8_from_i64(_t544);
    I64_delete(_t544, &(Bool){1});
    Bool *_t546 = malloc(sizeof(Bool)); *_t546 = U8_eq(DEREF(first), DEREF(_t545));
    I64_delete(_t543, &(Bool){1});
    U8_delete(_t545, &(Bool){1});
    if (DEREF(_t546)) {
        Bool *_t507 = malloc(sizeof(Bool));
        *_t507 = 1;
        *neg = DEREF(_t507);
        Bool_delete(_t507, &(Bool){1});
        I64 *_t508 = malloc(sizeof(I64));
        *_t508 = 1;
        U64 *_t509 = U64_from_i64(_t508);
        I64_delete(_t508, &(Bool){1});
        *i = DEREF(_t509);
        U64_delete(_t509, &(Bool){1});
    }
    Bool_delete(_t546, &(Bool){1});
    Bool *_t547 = malloc(sizeof(Bool)); *_t547 = U64_eq(DEREF(i), self->count);
    if (DEREF(_t547)) {
        Str *_t510 = Str_lit("Str", 3ULL);
        I64 *_t511 = Str_size();
        I64 *_t512 = malloc(sizeof(I64));
        *_t512 = 1;
        Array *_va9 = Array_new(_t510, _t511, _t512);
        Str_delete(_t510, &(Bool){1});
        I64_delete(_t511, &(Bool){1});
        I64_delete(_t512, &(Bool){1});
        I64 *_t513 = malloc(sizeof(I64));
        *_t513 = 0;
        Str *_t514 = Str_lit("no digits", 9ULL);
        Array_set(_va9, _t513, _t514);
        I64_delete(_t513, &(Bool){1});
        Str *_t515 = Str_lit("Str.to_i64", 10ULL);
        panic(_t515, _va9);
        Str_delete(_t515, &(Bool){1});
        Array_delete(_va9, &(Bool){1});
    }
    Bool_delete(_t547, &(Bool){1});
    while (1) {
        Bool *_wcond516 = U64_lt(i, &self->count);
        if (DEREF(_wcond516)) {
        } else {
            Bool_delete(_wcond516, &(Bool){1});
            break;
        }
        Bool_delete(_wcond516, &(Bool){1});
        U8 *ch = Str_get(self, i);
        I64 *_t527 = malloc(sizeof(I64)); *_t527 = U8_to_i64(DEREF(ch));
        I64 *_t528 = malloc(sizeof(I64));
        *_t528 = 48;
        I64 *d = malloc(sizeof(I64)); *d = I64_sub(DEREF(_t527), DEREF(_t528));
        I64_delete(_t527, &(Bool){1});
        I64_delete(_t528, &(Bool){1});
        I64 *_t529 = malloc(sizeof(I64));
        *_t529 = 0;
        I64 *_t530 = malloc(sizeof(I64));
        *_t530 = 9;
        Bool *_t531 = I64_lt(d, _t529);
        I64_delete(_t529, &(Bool){1});
        Bool *_t532 = I64_gt(d, _t530);
        I64_delete(_t530, &(Bool){1});
        Bool *_t533 = malloc(sizeof(Bool)); *_t533 = Bool_or(DEREF(_t531), DEREF(_t532));
        Bool_delete(_t531, &(Bool){1});
        Bool_delete(_t532, &(Bool){1});
        if (DEREF(_t533)) {
            Str *_t517 = Str_lit("Str", 3ULL);
            I64 *_t518 = Str_size();
            I64 *_t519 = malloc(sizeof(I64));
            *_t519 = 3;
            Array *_va10 = Array_new(_t517, _t518, _t519);
            Str_delete(_t517, &(Bool){1});
            I64_delete(_t518, &(Bool){1});
            I64_delete(_t519, &(Bool){1});
            I64 *_t520 = malloc(sizeof(I64));
            *_t520 = 0;
            Str *_t521 = Str_lit("invalid char in '", 17ULL);
            Array_set(_va10, _t520, _t521);
            I64_delete(_t520, &(Bool){1});
            I64 *_t522 = malloc(sizeof(I64));
            *_t522 = 1;
            Str *_t523 = Str_clone(self);
            Array_set(_va10, _t522, _t523);
            I64_delete(_t522, &(Bool){1});
            I64 *_t524 = malloc(sizeof(I64));
            *_t524 = 2;
            Str *_t525 = Str_lit("'", 1ULL);
            Array_set(_va10, _t524, _t525);
            I64_delete(_t524, &(Bool){1});
            Str *_t526 = Str_lit("Str.to_i64", 10ULL);
            panic(_t526, _va10);
            Str_delete(_t526, &(Bool){1});
            Array_delete(_va10, &(Bool){1});
        }
        Bool_delete(_t533, &(Bool){1});
        I64 *_t534 = malloc(sizeof(I64));
        *_t534 = 10;
        I64 *_t535 = malloc(sizeof(I64)); *_t535 = I64_mul(DEREF(result), DEREF(_t534));
        I64_delete(_t534, &(Bool){1});
        I64 *_t536 = malloc(sizeof(I64)); *_t536 = I64_add(DEREF(_t535), DEREF(d));
        I64_delete(_t535, &(Bool){1});
        I64_delete(d, &(Bool){1});
        *result = DEREF(_t536);
        I64_delete(_t536, &(Bool){1});
        I64 *_t537 = malloc(sizeof(I64));
        *_t537 = 1;
        U64 *_t538 = malloc(sizeof(U64)); *_t538 = U64_add(DEREF(i), DEREF(_t537));
        I64_delete(_t537, &(Bool){1});
        *i = DEREF(_t538);
        U64_delete(_t538, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    if (DEREF(neg)) {
        I64 *_t539 = malloc(sizeof(I64));
        *_t539 = 0;
        I64 *_t540 = malloc(sizeof(I64)); *_t540 = I64_sub(DEREF(_t539), DEREF(result));
        I64_delete(_t539, &(Bool){1});
        Bool_delete(neg, &(Bool){1});
        I64_delete(result, &(Bool){1});
        return _t540;
    }
    Bool_delete(neg, &(Bool){1});
    return result;
}

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    I64 *_t549 = Str_cmp(a, b);
    I64 *_t550 = malloc(sizeof(I64));
    *_t550 = 0;
    Bool *_t551 = malloc(sizeof(Bool)); *_t551 = I64_eq(DEREF(_t549), DEREF(_t550));
    I64_delete(_t549, &(Bool){1});
    I64_delete(_t550, &(Bool){1});
    return _t551;
}

Bool * Str_lt(Str * a, Str * b) {
    I64 *_t552 = malloc(sizeof(I64));
    *_t552 = 0;
    I64 *_t553 = malloc(sizeof(I64));
    *_t553 = 1;
    I64 *_t554 = Str_cmp(a, b);
    I64 *_t555 = malloc(sizeof(I64)); *_t555 = I64_sub(DEREF(_t552), DEREF(_t553));
    I64_delete(_t552, &(Bool){1});
    I64_delete(_t553, &(Bool){1});
    Bool *_t556 = malloc(sizeof(Bool)); *_t556 = I64_eq(DEREF(_t554), DEREF(_t555));
    I64_delete(_t554, &(Bool){1});
    I64_delete(_t555, &(Bool){1});
    return _t556;
}

Bool * Str_gt(Str * a, Str * b) {
    I64 *_t557 = Str_cmp(a, b);
    I64 *_t558 = malloc(sizeof(I64));
    *_t558 = 1;
    Bool *_t559 = malloc(sizeof(Bool)); *_t559 = I64_eq(DEREF(_t557), DEREF(_t558));
    I64_delete(_t557, &(Bool){1});
    I64_delete(_t558, &(Bool){1});
    return _t559;
}

Bool * Str_neq(Str * a, Str * b) {
    Bool *_t560 = Str_eq(a, b);
    Bool *_t561 = malloc(sizeof(Bool)); *_t561 = Bool_not(DEREF(_t560));
    Bool_delete(_t560, &(Bool){1});
    return _t561;
}

Bool * Str_lte(Str * a, Str * b) {
    Bool *_t562 = Str_gt(a, b);
    Bool *_t563 = malloc(sizeof(Bool)); *_t563 = Bool_not(DEREF(_t562));
    Bool_delete(_t562, &(Bool){1});
    return _t563;
}

Bool * Str_gte(Str * a, Str * b) {
    Bool *_t564 = Str_lt(a, b);
    Bool *_t565 = malloc(sizeof(Bool)); *_t565 = Bool_not(DEREF(_t564));
    Bool_delete(_t564, &(Bool){1});
    return _t565;
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t566 = malloc(DEREF(elem_size));
    U64 *_t567 = malloc(sizeof(U64));
    *_t567 = 0;
    I64 *_t568 = malloc(sizeof(I64));
    *_t568 = 1;
    U64 *_t569 = U64_clone(elem_size);
    Vec *_t570 = malloc(sizeof(Vec));
    _t570->data = _t566;
    _t570->count = DEREF(_t567);
    _t570->cap = DEREF(_t568);
    _t570->elem_size = DEREF(_t569);
    { Str *_ca = Str_clone(elem_type); _t570->elem_type = *_ca; free(_ca); }
    U64_delete(_t567, &(Bool){1});
    I64_delete(_t568, &(Bool){1});
    U64_delete(_t569, &(Bool){1});
    return _t570;
}

U64 * Vec_len(Vec * self) {
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    Bool *_t575 = malloc(sizeof(Bool)); *_t575 = U64_eq(self->count, self->cap);
    if (DEREF(_t575)) {
        I64 *_t571 = malloc(sizeof(I64));
        *_t571 = 2;
        U64 *new_cap = malloc(sizeof(U64)); *new_cap = U64_mul(self->cap, DEREF(_t571));
        I64_delete(_t571, &(Bool){1});
        U64 *_t572 = malloc(sizeof(U64)); *_t572 = U64_mul(DEREF(new_cap), self->elem_size);
        void *_t573 = realloc(self->data, DEREF(_t572));
        U64_delete(_t572, &(Bool){1});
        self->data = _t573;
        U64 *_t574 = U64_clone(new_cap);
        U64_delete(new_cap, &(Bool){1});
        self->cap = DEREF(_t574);
        U64_delete(_t574, &(Bool){1});
    }
    Bool_delete(_t575, &(Bool){1});
    U64 *_t576 = malloc(sizeof(U64)); *_t576 = U64_mul(self->count, self->elem_size);
    void *_t577 = ptr_add(self->data, DEREF(_t576));
    memcpy(_t577, val, self->elem_size);
    U64_delete(_t576, &(Bool){1});
    free(val);
    I64 *_t578 = malloc(sizeof(I64));
    *_t578 = 1;
    U64 *_t579 = malloc(sizeof(U64)); *_t579 = U64_add(self->count, DEREF(_t578));
    I64_delete(_t578, &(Bool){1});
    self->count = DEREF(_t579);
    U64_delete(_t579, &(Bool){1});
}

void * Vec_get(Vec * self, U64 * i) {
    Bool *_t594 = U64_gte(i, &self->count);
    if (DEREF(_t594)) {
        Str *_t580 = Str_lit("Str", 3ULL);
        I64 *_t581 = Str_size();
        I64 *_t582 = malloc(sizeof(I64));
        *_t582 = 5;
        Array *_va11 = Array_new(_t580, _t581, _t582);
        Str_delete(_t580, &(Bool){1});
        I64_delete(_t581, &(Bool){1});
        I64_delete(_t582, &(Bool){1});
        I64 *_t583 = malloc(sizeof(I64));
        *_t583 = 0;
        Str *_t584 = Str_lit("index ", 6ULL);
        Array_set(_va11, _t583, _t584);
        I64_delete(_t583, &(Bool){1});
        I64 *_t585 = malloc(sizeof(I64));
        *_t585 = 1;
        Str *_t586 = U64_to_str(DEREF(i));
        Array_set(_va11, _t585, _t586);
        I64_delete(_t585, &(Bool){1});
        I64 *_t587 = malloc(sizeof(I64));
        *_t587 = 2;
        Str *_t588 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va11, _t587, _t588);
        I64_delete(_t587, &(Bool){1});
        I64 *_t589 = malloc(sizeof(I64));
        *_t589 = 3;
        Str *_t590 = U64_to_str(self->count);
        Array_set(_va11, _t589, _t590);
        I64_delete(_t589, &(Bool){1});
        I64 *_t591 = malloc(sizeof(I64));
        *_t591 = 4;
        Str *_t592 = Str_lit(")", 1ULL);
        Array_set(_va11, _t591, _t592);
        I64_delete(_t591, &(Bool){1});
        Str *_t593 = Str_lit("Vec.get", 7ULL);
        panic(_t593, _va11);
        Str_delete(_t593, &(Bool){1});
        Array_delete(_va11, &(Bool){1});
    }
    Bool_delete(_t594, &(Bool){1});
    U64 *_t595 = malloc(sizeof(U64)); *_t595 = U64_mul(DEREF(i), self->elem_size);
    void *_t596 = ptr_add(self->data, DEREF(_t595));
    U64_delete(_t595, &(Bool){1});
    return _t596;
}

void Vec_delete(Vec * self, Bool * call_free) {
    {
        U64 *_fi597 = malloc(sizeof(U64));
        *_fi597 = 0;
        while (1) {
            I64 *_t599 = malloc(sizeof(I64));
            *_t599 = 0;
            Range *_t600 = Range_new(DEREF(_t599), self->count);
            I64_delete(_t599, &(Bool){1});
            U64 *_t601 = Range_len(_t600);
            Range_delete(_t600, &(Bool){1});
            Bool *_wcond598 = U64_lt(_fi597, _t601);
            U64_delete(_t601, &(Bool){1});
            if (DEREF(_wcond598)) {
            } else {
                Bool_delete(_wcond598, &(Bool){1});
                break;
            }
            Bool_delete(_wcond598, &(Bool){1});
            I64 *_t602 = malloc(sizeof(I64));
            *_t602 = 0;
            Range *_t603 = Range_new(DEREF(_t602), self->count);
            I64_delete(_t602, &(Bool){1});
            U64 *i = Range_get(_t603, DEREF(_fi597));
            Range_delete(_t603, &(Bool){1});
            I64 *_t604 = malloc(sizeof(I64));
            *_t604 = 1;
            U64 *_t605 = malloc(sizeof(U64)); *_t605 = U64_add(DEREF(_fi597), DEREF(_t604));
            I64_delete(_t604, &(Bool){1});
            *_fi597 = DEREF(_t605);
            U64_delete(_t605, &(Bool){1});
            U64 *_t606 = malloc(sizeof(U64)); *_t606 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t607 = ptr_add(self->data, DEREF(_t606));
            Bool *_t608 = malloc(sizeof(Bool));
            *_t608 = 0;
            dyn_call_delete(&self->elem_type, _t607, _t608);
            U64_delete(_t606, &(Bool){1});
            Bool_delete(_t608, &(Bool){1});
        }
        U64_delete(_fi597, &(Bool){1});
    }
    free(self->data);
    Bool *_t609 = malloc(sizeof(Bool));
    *_t609 = 0;
    Str_delete(&self->elem_type, _t609);
    Bool_delete(_t609, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    U64 *_t623 = malloc(sizeof(U64)); *_t623 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t623));
    U64_delete(_t623, &(Bool){1});
    {
        U64 *_fi610 = malloc(sizeof(U64));
        *_fi610 = 0;
        while (1) {
            I64 *_t612 = malloc(sizeof(I64));
            *_t612 = 0;
            Range *_t613 = Range_new(DEREF(_t612), self->count);
            I64_delete(_t612, &(Bool){1});
            U64 *_t614 = Range_len(_t613);
            Range_delete(_t613, &(Bool){1});
            Bool *_wcond611 = U64_lt(_fi610, _t614);
            U64_delete(_t614, &(Bool){1});
            if (DEREF(_wcond611)) {
            } else {
                Bool_delete(_wcond611, &(Bool){1});
                break;
            }
            Bool_delete(_wcond611, &(Bool){1});
            I64 *_t615 = malloc(sizeof(I64));
            *_t615 = 0;
            Range *_t616 = Range_new(DEREF(_t615), self->count);
            I64_delete(_t615, &(Bool){1});
            U64 *i = Range_get(_t616, DEREF(_fi610));
            Range_delete(_t616, &(Bool){1});
            I64 *_t617 = malloc(sizeof(I64));
            *_t617 = 1;
            U64 *_t618 = malloc(sizeof(U64)); *_t618 = U64_add(DEREF(_fi610), DEREF(_t617));
            I64_delete(_t617, &(Bool){1});
            *_fi610 = DEREF(_t618);
            U64_delete(_t618, &(Bool){1});
            U64 *_t619 = malloc(sizeof(U64)); *_t619 = U64_mul(DEREF(i), self->elem_size);
            void *_t620 = ptr_add(self->data, DEREF(_t619));
            void *cloned = dyn_call_clone(&self->elem_type, _t620);
            U64_delete(_t619, &(Bool){1});
            U64 *_t621 = malloc(sizeof(U64)); *_t621 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t622 = ptr_add(new_data, DEREF(_t621));
            memcpy(_t622, cloned, self->elem_size);
            U64_delete(_t621, &(Bool){1});
            free(cloned);
        }
        U64_delete(_fi610, &(Bool){1});
    }
    Vec *_t624 = malloc(sizeof(Vec));
    _t624->data = new_data;
    _t624->count = self->count;
    _t624->cap = self->cap;
    _t624->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t624->elem_type = *_ca; free(_ca); }
    return _t624;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    Str *_t642 = Str_lit("Str", 3ULL);
    U64 *_t643 = Str_size();
    Vec *parts = Vec_new(_t642, _t643);
    Str_delete(_t642, &(Bool){1});
    U64_delete(_t643, &(Bool){1});
    U64 *_t644 = Str_len(delim);
    I64 *_t645 = malloc(sizeof(I64));
    *_t645 = 0;
    Bool *_t646 = malloc(sizeof(Bool)); *_t646 = U64_eq(DEREF(_t644), DEREF(_t645));
    U64_delete(_t644, &(Bool){1});
    I64_delete(_t645, &(Bool){1});
    if (DEREF(_t646)) {
        Str *_t626 = Str_clone(s);
        Vec_push(parts, _t626);
        Bool_delete(_t646, &(Bool){1});
        return parts;
    }
    Bool_delete(_t646, &(Bool){1});
    U64 *start = malloc(sizeof(U64));
    *start = 0;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    while (1) {
        U64 *_t636 = Str_len(s);
        U64 *_t637 = Str_len(delim);
        U64 *_t638 = malloc(sizeof(U64)); *_t638 = U64_sub(DEREF(_t636), DEREF(_t637));
        U64_delete(_t636, &(Bool){1});
        U64_delete(_t637, &(Bool){1});
        Bool *_wcond627 = U64_lte(pos, _t638);
        U64_delete(_t638, &(Bool){1});
        if (DEREF(_wcond627)) {
        } else {
            Bool_delete(_wcond627, &(Bool){1});
            break;
        }
        Bool_delete(_wcond627, &(Bool){1});
        U64 *_t639 = Str_len(delim);
        Str *_t640 = Str_substr(s, pos, _t639);
        U64_delete(_t639, &(Bool){1});
        Bool *_t641 = Str_eq(_t640, delim);
        Str_delete(_t640, &(Bool){1});
        if (DEREF(_t641)) {
            U64 *_t628 = malloc(sizeof(U64)); *_t628 = U64_sub(DEREF(pos), DEREF(start));
            Str *_t629 = Str_substr(s, start, _t628);
            U64_delete(_t628, &(Bool){1});
            Str *_t630 = Str_clone(_t629);
            Str_delete(_t629, &(Bool){1});
            Vec_push(parts, _t630);
            U64 *_t631 = Str_len(delim);
            U64 *_t632 = malloc(sizeof(U64)); *_t632 = U64_add(DEREF(pos), DEREF(_t631));
            U64_delete(_t631, &(Bool){1});
            *start = DEREF(_t632);
            U64_delete(_t632, &(Bool){1});
            U64 *_t633 = U64_clone(start);
            *pos = DEREF(_t633);
            U64_delete(_t633, &(Bool){1});
        } else {
            I64 *_t634 = malloc(sizeof(I64));
            *_t634 = 1;
            U64 *_t635 = malloc(sizeof(U64)); *_t635 = U64_add(DEREF(pos), DEREF(_t634));
            I64_delete(_t634, &(Bool){1});
            *pos = DEREF(_t635);
            U64_delete(_t635, &(Bool){1});
        }
        Bool_delete(_t641, &(Bool){1});
    }
    U64_delete(pos, &(Bool){1});
    U64 *_t647 = Str_len(s);
    U64 *_t648 = malloc(sizeof(U64)); *_t648 = U64_sub(DEREF(_t647), DEREF(start));
    U64_delete(_t647, &(Bool){1});
    Str *_t649 = Str_substr(s, start, _t648);
    U64_delete(_t648, &(Bool){1});
    U64_delete(start, &(Bool){1});
    Str *_t650 = Str_clone(_t649);
    Str_delete(_t649, &(Bool){1});
    Vec_push(parts, _t650);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 *_t658 = Vec_len(parts);
    I64 *_t659 = malloc(sizeof(I64));
    *_t659 = 0;
    Bool *_t660 = malloc(sizeof(Bool)); *_t660 = U64_eq(DEREF(_t658), DEREF(_t659));
    U64_delete(_t658, &(Bool){1});
    I64_delete(_t659, &(Bool){1});
    if (DEREF(_t660)) {
        Str *_t651 = Str_lit("", 0ULL);
        Bool_delete(_t660, &(Bool){1});
        return _t651;
    }
    Bool_delete(_t660, &(Bool){1});
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t653 = Vec_len(parts);
        Bool *_wcond652 = U64_lt(i, _t653);
        U64_delete(_t653, &(Bool){1});
        if (DEREF(_wcond652)) {
        } else {
            Bool_delete(_wcond652, &(Bool){1});
            break;
        }
        Bool_delete(_wcond652, &(Bool){1});
        I64 *_t654 = malloc(sizeof(I64));
        *_t654 = 0;
        Bool *_t655 = U64_gt(i, _t654);
        I64_delete(_t654, &(Bool){1});
        if (DEREF(_t655)) {
            result = Str_concat(result, sep);
        }
        Bool_delete(_t655, &(Bool){1});
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        I64 *_t656 = malloc(sizeof(I64));
        *_t656 = 1;
        U64 *_t657 = malloc(sizeof(U64)); *_t657 = U64_add(DEREF(i), DEREF(_t656));
        I64_delete(_t656, &(Bool){1});
        *i = DEREF(_t657);
        U64_delete(_t657, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    return result;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *_t661 = malloc(sizeof(EnumDef));
    return _t661;
}

void EnumDef_delete(EnumDef * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *EnumDef_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(EnumDef);
    return r;
}

Str * U8_to_str(U8 * val) {
    I64 *_t663 = malloc(sizeof(I64)); *_t663 = U8_to_i64(DEREF(val));
    Str *_t664 = I64_to_str(_t663);
    I64_delete(_t663, &(Bool){1});
    return _t664;
}

U8 * U8_from_i64(I64 * val) {
    I64 *_t671 = malloc(sizeof(I64));
    *_t671 = 0;
    I64 *_t672 = malloc(sizeof(I64));
    *_t672 = 255;
    Bool *_t673 = I64_lt(val, _t671);
    I64_delete(_t671, &(Bool){1});
    Bool *_t674 = I64_gt(val, _t672);
    I64_delete(_t672, &(Bool){1});
    Bool *_t675 = malloc(sizeof(Bool)); *_t675 = Bool_or(DEREF(_t673), DEREF(_t674));
    Bool_delete(_t673, &(Bool){1});
    Bool_delete(_t674, &(Bool){1});
    if (DEREF(_t675)) {
        Str *_t665 = Str_lit("Str", 3ULL);
        I64 *_t666 = Str_size();
        I64 *_t667 = malloc(sizeof(I64));
        *_t667 = 1;
        Array *_va12 = Array_new(_t665, _t666, _t667);
        Str_delete(_t665, &(Bool){1});
        I64_delete(_t666, &(Bool){1});
        I64_delete(_t667, &(Bool){1});
        I64 *_t668 = malloc(sizeof(I64));
        *_t668 = 0;
        Str *_t669 = Str_lit("value out of range (0-255)", 26ULL);
        Array_set(_va12, _t668, _t669);
        I64_delete(_t668, &(Bool){1});
        Str *_t670 = Str_lit("U8.from_i64", 11ULL);
        panic(_t670, _va12);
        Str_delete(_t670, &(Bool){1});
        Array_delete(_va12, &(Bool){1});
    }
    Bool_delete(_t675, &(Bool){1});
    /* TODO: nested func U8_from_i64_ext */
    U8 *_t676 = U8_from_i64_ext(val);
    return _t676;
}

U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

Bool * U8_lt(U8 * a, U8 * b) {
    I64 *_t678 = malloc(sizeof(I64));
    *_t678 = 0;
    I64 *_t679 = malloc(sizeof(I64));
    *_t679 = 1;
    I64 *_t680 = malloc(sizeof(I64)); *_t680 = U8_cmp(DEREF(a), DEREF(b));
    I64 *_t681 = malloc(sizeof(I64)); *_t681 = I64_sub(DEREF(_t678), DEREF(_t679));
    I64_delete(_t678, &(Bool){1});
    I64_delete(_t679, &(Bool){1});
    Bool *_t682 = malloc(sizeof(Bool)); *_t682 = I64_eq(DEREF(_t680), DEREF(_t681));
    I64_delete(_t680, &(Bool){1});
    I64_delete(_t681, &(Bool){1});
    return _t682;
}

Bool * U8_gt(U8 * a, U8 * b) {
    I64 *_t683 = malloc(sizeof(I64)); *_t683 = U8_cmp(DEREF(a), DEREF(b));
    I64 *_t684 = malloc(sizeof(I64));
    *_t684 = 1;
    Bool *_t685 = malloc(sizeof(Bool)); *_t685 = I64_eq(DEREF(_t683), DEREF(_t684));
    I64_delete(_t683, &(Bool){1});
    I64_delete(_t684, &(Bool){1});
    return _t685;
}

Bool * U8_neq(U8 * a, U8 * b) {
    Bool *_t686 = malloc(sizeof(Bool)); *_t686 = U8_eq(DEREF(a), DEREF(b));
    Bool *_t687 = malloc(sizeof(Bool)); *_t687 = Bool_not(DEREF(_t686));
    Bool_delete(_t686, &(Bool){1});
    return _t687;
}

Bool * U8_lte(U8 * a, U8 * b) {
    Bool *_t688 = U8_gt(a, b);
    Bool *_t689 = malloc(sizeof(Bool)); *_t689 = Bool_not(DEREF(_t688));
    Bool_delete(_t688, &(Bool){1});
    return _t689;
}

Bool * U8_gte(U8 * a, U8 * b) {
    Bool *_t690 = U8_lt(a, b);
    Bool *_t691 = malloc(sizeof(Bool)); *_t691 = Bool_not(DEREF(_t690));
    Bool_delete(_t690, &(Bool){1});
    return _t691;
}

Str * I16_to_str(I16 * val) {
    I64 *_t692 = malloc(sizeof(I64)); *_t692 = I16_to_i64(DEREF(val));
    Str *_t693 = I64_to_str(_t692);
    I64_delete(_t692, &(Bool){1});
    return _t693;
}

I16 * I16_from_i64(I64 * val) {
    I64 *_t700 = malloc(sizeof(I64));
    *_t700 = 32768;
    I64 *_t701 = I64_neg(_t700);
    I64_delete(_t700, &(Bool){1});
    I64 *_t702 = malloc(sizeof(I64));
    *_t702 = 32767;
    Bool *_t703 = I64_lt(val, _t701);
    I64_delete(_t701, &(Bool){1});
    Bool *_t704 = I64_gt(val, _t702);
    I64_delete(_t702, &(Bool){1});
    Bool *_t705 = malloc(sizeof(Bool)); *_t705 = Bool_or(DEREF(_t703), DEREF(_t704));
    Bool_delete(_t703, &(Bool){1});
    Bool_delete(_t704, &(Bool){1});
    if (DEREF(_t705)) {
        Str *_t694 = Str_lit("Str", 3ULL);
        I64 *_t695 = Str_size();
        I64 *_t696 = malloc(sizeof(I64));
        *_t696 = 1;
        Array *_va13 = Array_new(_t694, _t695, _t696);
        Str_delete(_t694, &(Bool){1});
        I64_delete(_t695, &(Bool){1});
        I64_delete(_t696, &(Bool){1});
        I64 *_t697 = malloc(sizeof(I64));
        *_t697 = 0;
        Str *_t698 = Str_lit("value out of range (-32768 to 32767)", 36ULL);
        Array_set(_va13, _t697, _t698);
        I64_delete(_t697, &(Bool){1});
        Str *_t699 = Str_lit("I16.from_i64", 12ULL);
        panic(_t699, _va13);
        Str_delete(_t699, &(Bool){1});
        Array_delete(_va13, &(Bool){1});
    }
    Bool_delete(_t705, &(Bool){1});
    /* TODO: nested func I16_from_i64_ext */
    I16 *_t706 = I16_from_i64_ext(val);
    return _t706;
}

I16 * I16_neg(I16 * a) {
    I64 *_t707 = malloc(sizeof(I64));
    *_t707 = 0;
    I64 *_t708 = malloc(sizeof(I64)); *_t708 = I16_to_i64(DEREF(a));
    I64 *_t709 = malloc(sizeof(I64)); *_t709 = I64_sub(DEREF(_t707), DEREF(_t708));
    I64_delete(_t707, &(Bool){1});
    I64_delete(_t708, &(Bool){1});
    I16 *_t710 = I16_from_i64(_t709);
    I64_delete(_t709, &(Bool){1});
    return _t710;
}

I16 * I16_abs(I16 * a) {
    I64 *_t715 = malloc(sizeof(I64)); *_t715 = I16_to_i64(DEREF(a));
    I64 *_t716 = malloc(sizeof(I64));
    *_t716 = 0;
    Bool *_t717 = I64_lt(_t715, _t716);
    I64_delete(_t715, &(Bool){1});
    I64_delete(_t716, &(Bool){1});
    if (DEREF(_t717)) {
        I64 *_t711 = malloc(sizeof(I64));
        *_t711 = 0;
        I64 *_t712 = malloc(sizeof(I64)); *_t712 = I16_to_i64(DEREF(a));
        I64 *_t713 = malloc(sizeof(I64)); *_t713 = I64_sub(DEREF(_t711), DEREF(_t712));
        I64_delete(_t711, &(Bool){1});
        I64_delete(_t712, &(Bool){1});
        I16 *_t714 = I16_from_i64(_t713);
        I64_delete(_t713, &(Bool){1});
        Bool_delete(_t717, &(Bool){1});
        return _t714;
    }
    Bool_delete(_t717, &(Bool){1});
    I16 *_t718 = I16_clone(a);
    return _t718;
}

U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

Bool * I16_lt(I16 * a, I16 * b) {
    I64 *_t720 = malloc(sizeof(I64));
    *_t720 = 0;
    I64 *_t721 = malloc(sizeof(I64));
    *_t721 = 1;
    I64 *_t722 = malloc(sizeof(I64)); *_t722 = I16_cmp(DEREF(a), DEREF(b));
    I64 *_t723 = malloc(sizeof(I64)); *_t723 = I64_sub(DEREF(_t720), DEREF(_t721));
    I64_delete(_t720, &(Bool){1});
    I64_delete(_t721, &(Bool){1});
    Bool *_t724 = malloc(sizeof(Bool)); *_t724 = I64_eq(DEREF(_t722), DEREF(_t723));
    I64_delete(_t722, &(Bool){1});
    I64_delete(_t723, &(Bool){1});
    return _t724;
}

Bool * I16_gt(I16 * a, I16 * b) {
    I64 *_t725 = malloc(sizeof(I64)); *_t725 = I16_cmp(DEREF(a), DEREF(b));
    I64 *_t726 = malloc(sizeof(I64));
    *_t726 = 1;
    Bool *_t727 = malloc(sizeof(Bool)); *_t727 = I64_eq(DEREF(_t725), DEREF(_t726));
    I64_delete(_t725, &(Bool){1});
    I64_delete(_t726, &(Bool){1});
    return _t727;
}

Bool * I16_neq(I16 * a, I16 * b) {
    Bool *_t728 = malloc(sizeof(Bool)); *_t728 = I16_eq(DEREF(a), DEREF(b));
    Bool *_t729 = malloc(sizeof(Bool)); *_t729 = Bool_not(DEREF(_t728));
    Bool_delete(_t728, &(Bool){1});
    return _t729;
}

Bool * I16_lte(I16 * a, I16 * b) {
    Bool *_t730 = I16_gt(a, b);
    Bool *_t731 = malloc(sizeof(Bool)); *_t731 = Bool_not(DEREF(_t730));
    Bool_delete(_t730, &(Bool){1});
    return _t731;
}

Bool * I16_gte(I16 * a, I16 * b) {
    Bool *_t732 = I16_lt(a, b);
    Bool *_t733 = malloc(sizeof(Bool)); *_t733 = Bool_not(DEREF(_t732));
    Bool_delete(_t732, &(Bool){1});
    return _t733;
}

Str * I32_to_str(I32 * val) {
    I64 *_t734 = malloc(sizeof(I64)); *_t734 = I32_to_i64(DEREF(val));
    Str *_t735 = I64_to_str(_t734);
    I64_delete(_t734, &(Bool){1});
    return _t735;
}

I32 * I32_from_i64(I64 * val) {
    I64 *_t742 = malloc(sizeof(I64));
    *_t742 = 2147483648;
    I64 *_t743 = I64_neg(_t742);
    I64_delete(_t742, &(Bool){1});
    I64 *_t744 = malloc(sizeof(I64));
    *_t744 = 2147483647;
    Bool *_t745 = I64_lt(val, _t743);
    I64_delete(_t743, &(Bool){1});
    Bool *_t746 = I64_gt(val, _t744);
    I64_delete(_t744, &(Bool){1});
    Bool *_t747 = malloc(sizeof(Bool)); *_t747 = Bool_or(DEREF(_t745), DEREF(_t746));
    Bool_delete(_t745, &(Bool){1});
    Bool_delete(_t746, &(Bool){1});
    if (DEREF(_t747)) {
        Str *_t736 = Str_lit("Str", 3ULL);
        I64 *_t737 = Str_size();
        I64 *_t738 = malloc(sizeof(I64));
        *_t738 = 1;
        Array *_va14 = Array_new(_t736, _t737, _t738);
        Str_delete(_t736, &(Bool){1});
        I64_delete(_t737, &(Bool){1});
        I64_delete(_t738, &(Bool){1});
        I64 *_t739 = malloc(sizeof(I64));
        *_t739 = 0;
        Str *_t740 = Str_lit("value out of range (-2147483648 to 2147483647)", 46ULL);
        Array_set(_va14, _t739, _t740);
        I64_delete(_t739, &(Bool){1});
        Str *_t741 = Str_lit("I32.from_i64", 12ULL);
        panic(_t741, _va14);
        Str_delete(_t741, &(Bool){1});
        Array_delete(_va14, &(Bool){1});
    }
    Bool_delete(_t747, &(Bool){1});
    /* TODO: nested func I32_from_i64_ext */
    I32 *_t748 = I32_from_i64_ext(val);
    return _t748;
}

I32 * I32_neg(I32 * a) {
    I64 *_t749 = malloc(sizeof(I64));
    *_t749 = 0;
    I64 *_t750 = malloc(sizeof(I64)); *_t750 = I32_to_i64(DEREF(a));
    I64 *_t751 = malloc(sizeof(I64)); *_t751 = I64_sub(DEREF(_t749), DEREF(_t750));
    I64_delete(_t749, &(Bool){1});
    I64_delete(_t750, &(Bool){1});
    I32 *_t752 = I32_from_i64(_t751);
    I64_delete(_t751, &(Bool){1});
    return _t752;
}

I32 * I32_abs(I32 * a) {
    I64 *_t757 = malloc(sizeof(I64)); *_t757 = I32_to_i64(DEREF(a));
    I64 *_t758 = malloc(sizeof(I64));
    *_t758 = 0;
    Bool *_t759 = I64_lt(_t757, _t758);
    I64_delete(_t757, &(Bool){1});
    I64_delete(_t758, &(Bool){1});
    if (DEREF(_t759)) {
        I64 *_t753 = malloc(sizeof(I64));
        *_t753 = 0;
        I64 *_t754 = malloc(sizeof(I64)); *_t754 = I32_to_i64(DEREF(a));
        I64 *_t755 = malloc(sizeof(I64)); *_t755 = I64_sub(DEREF(_t753), DEREF(_t754));
        I64_delete(_t753, &(Bool){1});
        I64_delete(_t754, &(Bool){1});
        I32 *_t756 = I32_from_i64(_t755);
        I64_delete(_t755, &(Bool){1});
        Bool_delete(_t759, &(Bool){1});
        return _t756;
    }
    Bool_delete(_t759, &(Bool){1});
    I32 *_t760 = I32_clone(a);
    return _t760;
}

U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

Bool * I32_lt(I32 * a, I32 * b) {
    I64 *_t762 = malloc(sizeof(I64));
    *_t762 = 0;
    I64 *_t763 = malloc(sizeof(I64));
    *_t763 = 1;
    I64 *_t764 = malloc(sizeof(I64)); *_t764 = I32_cmp(DEREF(a), DEREF(b));
    I64 *_t765 = malloc(sizeof(I64)); *_t765 = I64_sub(DEREF(_t762), DEREF(_t763));
    I64_delete(_t762, &(Bool){1});
    I64_delete(_t763, &(Bool){1});
    Bool *_t766 = malloc(sizeof(Bool)); *_t766 = I64_eq(DEREF(_t764), DEREF(_t765));
    I64_delete(_t764, &(Bool){1});
    I64_delete(_t765, &(Bool){1});
    return _t766;
}

Bool * I32_gt(I32 * a, I32 * b) {
    I64 *_t767 = malloc(sizeof(I64)); *_t767 = I32_cmp(DEREF(a), DEREF(b));
    I64 *_t768 = malloc(sizeof(I64));
    *_t768 = 1;
    Bool *_t769 = malloc(sizeof(Bool)); *_t769 = I64_eq(DEREF(_t767), DEREF(_t768));
    I64_delete(_t767, &(Bool){1});
    I64_delete(_t768, &(Bool){1});
    return _t769;
}

Bool * I32_neq(I32 * a, I32 * b) {
    Bool *_t770 = malloc(sizeof(Bool)); *_t770 = I32_eq(DEREF(a), DEREF(b));
    Bool *_t771 = malloc(sizeof(Bool)); *_t771 = Bool_not(DEREF(_t770));
    Bool_delete(_t770, &(Bool){1});
    return _t771;
}

Bool * I32_lte(I32 * a, I32 * b) {
    Bool *_t772 = I32_gt(a, b);
    Bool *_t773 = malloc(sizeof(Bool)); *_t773 = Bool_not(DEREF(_t772));
    Bool_delete(_t772, &(Bool){1});
    return _t773;
}

Bool * I32_gte(I32 * a, I32 * b) {
    Bool *_t774 = I32_lt(a, b);
    Bool *_t775 = malloc(sizeof(Bool)); *_t775 = Bool_not(DEREF(_t774));
    Bool_delete(_t774, &(Bool){1});
    return _t775;
}

F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 *_t776 = F32_from_i64_ext(val);
    return _t776;
}

U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

Bool * F32_lt(F32 * a, F32 * b) {
    I64 *_t778 = malloc(sizeof(I64));
    *_t778 = 0;
    I64 *_t779 = malloc(sizeof(I64));
    *_t779 = 1;
    I64 *_t780 = malloc(sizeof(I64)); *_t780 = F32_cmp(DEREF(a), DEREF(b));
    I64 *_t781 = malloc(sizeof(I64)); *_t781 = I64_sub(DEREF(_t778), DEREF(_t779));
    I64_delete(_t778, &(Bool){1});
    I64_delete(_t779, &(Bool){1});
    Bool *_t782 = malloc(sizeof(Bool)); *_t782 = I64_eq(DEREF(_t780), DEREF(_t781));
    I64_delete(_t780, &(Bool){1});
    I64_delete(_t781, &(Bool){1});
    return _t782;
}

Bool * F32_gt(F32 * a, F32 * b) {
    I64 *_t783 = malloc(sizeof(I64)); *_t783 = F32_cmp(DEREF(a), DEREF(b));
    I64 *_t784 = malloc(sizeof(I64));
    *_t784 = 1;
    Bool *_t785 = malloc(sizeof(Bool)); *_t785 = I64_eq(DEREF(_t783), DEREF(_t784));
    I64_delete(_t783, &(Bool){1});
    I64_delete(_t784, &(Bool){1});
    return _t785;
}

Bool * F32_neq(F32 * a, F32 * b) {
    Bool *_t786 = malloc(sizeof(Bool)); *_t786 = F32_eq(DEREF(a), DEREF(b));
    Bool *_t787 = malloc(sizeof(Bool)); *_t787 = Bool_not(DEREF(_t786));
    Bool_delete(_t786, &(Bool){1});
    return _t787;
}

Bool * F32_lte(F32 * a, F32 * b) {
    Bool *_t788 = F32_gt(a, b);
    Bool *_t789 = malloc(sizeof(Bool)); *_t789 = Bool_not(DEREF(_t788));
    Bool_delete(_t788, &(Bool){1});
    return _t789;
}

Bool * F32_gte(F32 * a, F32 * b) {
    Bool *_t790 = F32_lt(a, b);
    Bool *_t791 = malloc(sizeof(Bool)); *_t791 = Bool_not(DEREF(_t790));
    Bool_delete(_t790, &(Bool){1});
    return _t791;
}

Str * U32_to_str(U32 * val) {
    I64 *_t792 = malloc(sizeof(I64)); *_t792 = U32_to_i64(DEREF(val));
    Str *_t793 = I64_to_str(_t792);
    I64_delete(_t792, &(Bool){1});
    return _t793;
}

U32 * U32_from_i64(I64 * val) {
    I64 *_t800 = malloc(sizeof(I64));
    *_t800 = 0;
    I64 *_t801 = malloc(sizeof(I64));
    *_t801 = 4294967295;
    Bool *_t802 = I64_lt(val, _t800);
    I64_delete(_t800, &(Bool){1});
    Bool *_t803 = I64_gt(val, _t801);
    I64_delete(_t801, &(Bool){1});
    Bool *_t804 = malloc(sizeof(Bool)); *_t804 = Bool_or(DEREF(_t802), DEREF(_t803));
    Bool_delete(_t802, &(Bool){1});
    Bool_delete(_t803, &(Bool){1});
    if (DEREF(_t804)) {
        Str *_t794 = Str_lit("Str", 3ULL);
        I64 *_t795 = Str_size();
        I64 *_t796 = malloc(sizeof(I64));
        *_t796 = 1;
        Array *_va15 = Array_new(_t794, _t795, _t796);
        Str_delete(_t794, &(Bool){1});
        I64_delete(_t795, &(Bool){1});
        I64_delete(_t796, &(Bool){1});
        I64 *_t797 = malloc(sizeof(I64));
        *_t797 = 0;
        Str *_t798 = Str_lit("value out of range (0-4294967295)", 33ULL);
        Array_set(_va15, _t797, _t798);
        I64_delete(_t797, &(Bool){1});
        Str *_t799 = Str_lit("U32.from_i64", 12ULL);
        panic(_t799, _va15);
        Str_delete(_t799, &(Bool){1});
        Array_delete(_va15, &(Bool){1});
    }
    Bool_delete(_t804, &(Bool){1});
    /* TODO: nested func U32_from_i64_ext */
    U32 *_t805 = U32_from_i64_ext(val);
    return _t805;
}

U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

Bool * U32_lt(U32 * a, U32 * b) {
    I64 *_t807 = malloc(sizeof(I64));
    *_t807 = 0;
    I64 *_t808 = malloc(sizeof(I64));
    *_t808 = 1;
    I64 *_t809 = malloc(sizeof(I64)); *_t809 = U32_cmp(DEREF(a), DEREF(b));
    I64 *_t810 = malloc(sizeof(I64)); *_t810 = I64_sub(DEREF(_t807), DEREF(_t808));
    I64_delete(_t807, &(Bool){1});
    I64_delete(_t808, &(Bool){1});
    Bool *_t811 = malloc(sizeof(Bool)); *_t811 = I64_eq(DEREF(_t809), DEREF(_t810));
    I64_delete(_t809, &(Bool){1});
    I64_delete(_t810, &(Bool){1});
    return _t811;
}

Bool * U32_gt(U32 * a, U32 * b) {
    I64 *_t812 = malloc(sizeof(I64)); *_t812 = U32_cmp(DEREF(a), DEREF(b));
    I64 *_t813 = malloc(sizeof(I64));
    *_t813 = 1;
    Bool *_t814 = malloc(sizeof(Bool)); *_t814 = I64_eq(DEREF(_t812), DEREF(_t813));
    I64_delete(_t812, &(Bool){1});
    I64_delete(_t813, &(Bool){1});
    return _t814;
}

Bool * U32_neq(U32 * a, U32 * b) {
    Bool *_t815 = malloc(sizeof(Bool)); *_t815 = U32_eq(DEREF(a), DEREF(b));
    Bool *_t816 = malloc(sizeof(Bool)); *_t816 = Bool_not(DEREF(_t815));
    Bool_delete(_t815, &(Bool){1});
    return _t816;
}

Bool * U32_lte(U32 * a, U32 * b) {
    Bool *_t817 = U32_gt(a, b);
    Bool *_t818 = malloc(sizeof(Bool)); *_t818 = Bool_not(DEREF(_t817));
    Bool_delete(_t817, &(Bool){1});
    return _t818;
}

Bool * U32_gte(U32 * a, U32 * b) {
    Bool *_t819 = U32_lt(a, b);
    Bool *_t820 = malloc(sizeof(Bool)); *_t820 = Bool_not(DEREF(_t819));
    Bool_delete(_t819, &(Bool){1});
    return _t820;
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t821 = U64_to_str_ext(&(U64){val});
    return _t821;
}

U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 *_t822 = U64_from_i64_ext(val);
    return _t822;
}

U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

Bool * U64_lt(U64 * a, U64 * b) {
    I64 *_t824 = malloc(sizeof(I64));
    *_t824 = 0;
    I64 *_t825 = malloc(sizeof(I64));
    *_t825 = 1;
    I64 *_t826 = malloc(sizeof(I64)); *_t826 = U64_cmp(DEREF(a), DEREF(b));
    I64 *_t827 = malloc(sizeof(I64)); *_t827 = I64_sub(DEREF(_t824), DEREF(_t825));
    I64_delete(_t824, &(Bool){1});
    I64_delete(_t825, &(Bool){1});
    Bool *_t828 = malloc(sizeof(Bool)); *_t828 = I64_eq(DEREF(_t826), DEREF(_t827));
    I64_delete(_t826, &(Bool){1});
    I64_delete(_t827, &(Bool){1});
    return _t828;
}

Bool * U64_gt(U64 * a, U64 * b) {
    I64 *_t829 = malloc(sizeof(I64)); *_t829 = U64_cmp(DEREF(a), DEREF(b));
    I64 *_t830 = malloc(sizeof(I64));
    *_t830 = 1;
    Bool *_t831 = malloc(sizeof(Bool)); *_t831 = I64_eq(DEREF(_t829), DEREF(_t830));
    I64_delete(_t829, &(Bool){1});
    I64_delete(_t830, &(Bool){1});
    return _t831;
}

Bool * U64_neq(U64 * a, U64 * b) {
    Bool *_t832 = malloc(sizeof(Bool)); *_t832 = U64_eq(DEREF(a), DEREF(b));
    Bool *_t833 = malloc(sizeof(Bool)); *_t833 = Bool_not(DEREF(_t832));
    Bool_delete(_t832, &(Bool){1});
    return _t833;
}

Bool * U64_lte(U64 * a, U64 * b) {
    Bool *_t834 = U64_gt(a, b);
    Bool *_t835 = malloc(sizeof(Bool)); *_t835 = Bool_not(DEREF(_t834));
    Bool_delete(_t834, &(Bool){1});
    return _t835;
}

Bool * U64_gte(U64 * a, U64 * b) {
    Bool *_t836 = U64_lt(a, b);
    Bool *_t837 = malloc(sizeof(Bool)); *_t837 = Bool_not(DEREF(_t836));
    Bool_delete(_t836, &(Bool){1});
    return _t837;
}

Str * I64_to_str(I64 * val) {
    I64 *_t877 = malloc(sizeof(I64));
    *_t877 = 0;
    Bool *_t878 = malloc(sizeof(Bool)); *_t878 = I64_eq(DEREF(val), DEREF(_t877));
    I64_delete(_t877, &(Bool){1});
    if (DEREF(_t878)) {
        I64 *_t838 = malloc(sizeof(I64));
        *_t838 = 2;
        U8 *buf = malloc(DEREF(_t838));
        I64_delete(_t838, &(Bool){1});
        I64 *_t839 = malloc(sizeof(I64));
        *_t839 = 48;
        U8 *_t840 = U8_from_i64(_t839);
        I64_delete(_t839, &(Bool){1});
        I64 *_t841 = malloc(sizeof(I64));
        *_t841 = 1;
        memcpy(buf, _t840, DEREF(_t841));
        U8_delete(_t840, &(Bool){1});
        I64_delete(_t841, &(Bool){1});
        I64 *_t842 = malloc(sizeof(I64));
        *_t842 = 1;
        I64 *_t843 = malloc(sizeof(I64));
        *_t843 = 0;
        void *_t844 = ptr_add(buf, DEREF(_t842));
        U8 *_t845 = U8_from_i64(_t843);
        I64_delete(_t843, &(Bool){1});
        I64 *_t846 = malloc(sizeof(I64));
        *_t846 = 1;
        memcpy(_t844, _t845, DEREF(_t846));
        I64_delete(_t842, &(Bool){1});
        U8_delete(_t845, &(Bool){1});
        I64_delete(_t846, &(Bool){1});
        I64 *_t847 = malloc(sizeof(I64));
        *_t847 = 1;
        I64 *_t848 = malloc(sizeof(I64));
        *_t848 = 1;
        Str *_t849 = malloc(sizeof(Str));
        _t849->c_str = buf;
        _t849->count = DEREF(_t847);
        _t849->cap = DEREF(_t848);
        I64_delete(_t847, &(Bool){1});
        I64_delete(_t848, &(Bool){1});
        Bool_delete(_t878, &(Bool){1});
        return _t849;
    }
    Bool_delete(_t878, &(Bool){1});
    Bool *is_neg = malloc(sizeof(Bool));
    *is_neg = 0;
    I64 *v = I64_clone(val);
    I64 *_t879 = malloc(sizeof(I64));
    *_t879 = 0;
    Bool *_t880 = I64_lt(val, _t879);
    I64_delete(_t879, &(Bool){1});
    if (DEREF(_t880)) {
        Bool *_t850 = malloc(sizeof(Bool));
        *_t850 = 1;
        *is_neg = DEREF(_t850);
        Bool_delete(_t850, &(Bool){1});
        I64 *_t851 = malloc(sizeof(I64));
        *_t851 = 0;
        I64 *_t852 = malloc(sizeof(I64)); *_t852 = I64_sub(DEREF(_t851), DEREF(val));
        I64_delete(_t851, &(Bool){1});
        *v = DEREF(_t852);
        I64_delete(_t852, &(Bool){1});
    }
    Bool_delete(_t880, &(Bool){1});
    U64 *ndigits = malloc(sizeof(U64));
    *ndigits = 0;
    I64 *tmp = I64_clone(v);
    while (1) {
        I64 *_t854 = malloc(sizeof(I64));
        *_t854 = 0;
        Bool *_wcond853 = I64_gt(tmp, _t854);
        I64_delete(_t854, &(Bool){1});
        if (DEREF(_wcond853)) {
        } else {
            Bool_delete(_wcond853, &(Bool){1});
            break;
        }
        Bool_delete(_wcond853, &(Bool){1});
        I64 *_t855 = malloc(sizeof(I64));
        *_t855 = 1;
        U64 *_t856 = malloc(sizeof(U64)); *_t856 = U64_add(DEREF(ndigits), DEREF(_t855));
        I64_delete(_t855, &(Bool){1});
        *ndigits = DEREF(_t856);
        U64_delete(_t856, &(Bool){1});
        I64 *_t857 = malloc(sizeof(I64));
        *_t857 = 10;
        I64 *_t858 = malloc(sizeof(I64)); *_t858 = I64_div(DEREF(tmp), DEREF(_t857));
        I64_delete(_t857, &(Bool){1});
        *tmp = DEREF(_t858);
        I64_delete(_t858, &(Bool){1});
    }
    I64_delete(tmp, &(Bool){1});
    U64 *total = U64_clone(ndigits);
    U64_delete(ndigits, &(Bool){1});
    if (DEREF(is_neg)) {
        I64 *_t859 = malloc(sizeof(I64));
        *_t859 = 1;
        U64 *_t860 = malloc(sizeof(U64)); *_t860 = U64_add(DEREF(total), DEREF(_t859));
        I64_delete(_t859, &(Bool){1});
        *total = DEREF(_t860);
        U64_delete(_t860, &(Bool){1});
    }
    I64 *_t881 = malloc(sizeof(I64));
    *_t881 = 1;
    U64 *_t882 = malloc(sizeof(U64)); *_t882 = U64_add(DEREF(total), DEREF(_t881));
    I64_delete(_t881, &(Bool){1});
    U8 *buf = malloc(DEREF(_t882));
    U64_delete(_t882, &(Bool){1});
    if (DEREF(is_neg)) {
        I64 *_t861 = malloc(sizeof(I64));
        *_t861 = 45;
        U8 *_t862 = U8_from_i64(_t861);
        I64_delete(_t861, &(Bool){1});
        I64 *_t863 = malloc(sizeof(I64));
        *_t863 = 1;
        memcpy(buf, _t862, DEREF(_t863));
        U8_delete(_t862, &(Bool){1});
        I64_delete(_t863, &(Bool){1});
    }
    Bool_delete(is_neg, &(Bool){1});
    I64 *_t883 = malloc(sizeof(I64));
    *_t883 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), DEREF(_t883));
    I64_delete(_t883, &(Bool){1});
    while (1) {
        I64 *_t865 = malloc(sizeof(I64));
        *_t865 = 0;
        Bool *_wcond864 = I64_gt(v, _t865);
        I64_delete(_t865, &(Bool){1});
        if (DEREF(_wcond864)) {
        } else {
            Bool_delete(_wcond864, &(Bool){1});
            break;
        }
        Bool_delete(_wcond864, &(Bool){1});
        I64 *_t866 = malloc(sizeof(I64));
        *_t866 = 10;
        I64 *_t867 = malloc(sizeof(I64)); *_t867 = I64_mod(DEREF(v), DEREF(_t866));
        I64_delete(_t866, &(Bool){1});
        I64 *_t868 = malloc(sizeof(I64));
        *_t868 = 48;
        I64 *_t869 = malloc(sizeof(I64)); *_t869 = I64_add(DEREF(_t867), DEREF(_t868));
        I64_delete(_t867, &(Bool){1});
        I64_delete(_t868, &(Bool){1});
        void *_t870 = ptr_add(buf, DEREF(i));
        U8 *_t871 = U8_from_i64(_t869);
        I64_delete(_t869, &(Bool){1});
        I64 *_t872 = malloc(sizeof(I64));
        *_t872 = 1;
        memcpy(_t870, _t871, DEREF(_t872));
        U8_delete(_t871, &(Bool){1});
        I64_delete(_t872, &(Bool){1});
        I64 *_t873 = malloc(sizeof(I64));
        *_t873 = 10;
        I64 *_t874 = malloc(sizeof(I64)); *_t874 = I64_div(DEREF(v), DEREF(_t873));
        I64_delete(_t873, &(Bool){1});
        *v = DEREF(_t874);
        I64_delete(_t874, &(Bool){1});
        I64 *_t875 = malloc(sizeof(I64));
        *_t875 = 1;
        U64 *_t876 = malloc(sizeof(U64)); *_t876 = U64_sub(DEREF(i), DEREF(_t875));
        I64_delete(_t875, &(Bool){1});
        *i = DEREF(_t876);
        U64_delete(_t876, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    I64_delete(v, &(Bool){1});
    I64 *_t884 = malloc(sizeof(I64));
    *_t884 = 0;
    void *_t885 = ptr_add(buf, DEREF(total));
    U8 *_t886 = U8_from_i64(_t884);
    I64_delete(_t884, &(Bool){1});
    I64 *_t887 = malloc(sizeof(I64));
    *_t887 = 1;
    memcpy(_t885, _t886, DEREF(_t887));
    U8_delete(_t886, &(Bool){1});
    I64_delete(_t887, &(Bool){1});
    U64 *_t888 = U64_clone(total);
    U64 *_t889 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t890 = malloc(sizeof(Str));
    _t890->c_str = buf;
    _t890->count = DEREF(_t888);
    _t890->cap = DEREF(_t889);
    U64_delete(_t888, &(Bool){1});
    U64_delete(_t889, &(Bool){1});
    return _t890;
}

I64 * I64_neg(I64 * a) {
    I64 *_t891 = malloc(sizeof(I64));
    *_t891 = 0;
    I64 *_t892 = malloc(sizeof(I64)); *_t892 = I64_sub(DEREF(_t891), DEREF(a));
    I64_delete(_t891, &(Bool){1});
    return _t892;
}

I64 * I64_abs(I64 * a) {
    I64 *_t895 = malloc(sizeof(I64));
    *_t895 = 0;
    Bool *_t896 = I64_lt(a, _t895);
    I64_delete(_t895, &(Bool){1});
    if (DEREF(_t896)) {
        I64 *_t893 = malloc(sizeof(I64));
        *_t893 = 0;
        I64 *_t894 = malloc(sizeof(I64)); *_t894 = I64_sub(DEREF(_t893), DEREF(a));
        I64_delete(_t893, &(Bool){1});
        Bool_delete(_t896, &(Bool){1});
        return _t894;
    }
    Bool_delete(_t896, &(Bool){1});
    I64 *_t897 = I64_clone(a);
    return _t897;
}

U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

Bool * I64_lt(I64 * a, I64 * b) {
    I64 *_t899 = malloc(sizeof(I64));
    *_t899 = 0;
    I64 *_t900 = malloc(sizeof(I64));
    *_t900 = 1;
    I64 *_t901 = malloc(sizeof(I64)); *_t901 = I64_cmp(DEREF(a), DEREF(b));
    I64 *_t902 = malloc(sizeof(I64)); *_t902 = I64_sub(DEREF(_t899), DEREF(_t900));
    I64_delete(_t899, &(Bool){1});
    I64_delete(_t900, &(Bool){1});
    Bool *_t903 = malloc(sizeof(Bool)); *_t903 = I64_eq(DEREF(_t901), DEREF(_t902));
    I64_delete(_t901, &(Bool){1});
    I64_delete(_t902, &(Bool){1});
    return _t903;
}

Bool * I64_gt(I64 * a, I64 * b) {
    I64 *_t904 = malloc(sizeof(I64)); *_t904 = I64_cmp(DEREF(a), DEREF(b));
    I64 *_t905 = malloc(sizeof(I64));
    *_t905 = 1;
    Bool *_t906 = malloc(sizeof(Bool)); *_t906 = I64_eq(DEREF(_t904), DEREF(_t905));
    I64_delete(_t904, &(Bool){1});
    I64_delete(_t905, &(Bool){1});
    return _t906;
}

Bool * I64_neq(I64 * a, I64 * b) {
    Bool *_t907 = malloc(sizeof(Bool)); *_t907 = I64_eq(DEREF(a), DEREF(b));
    Bool *_t908 = malloc(sizeof(Bool)); *_t908 = Bool_not(DEREF(_t907));
    Bool_delete(_t907, &(Bool){1});
    return _t908;
}

Bool * I64_lte(I64 * a, I64 * b) {
    Bool *_t909 = I64_gt(a, b);
    Bool *_t910 = malloc(sizeof(Bool)); *_t910 = Bool_not(DEREF(_t909));
    Bool_delete(_t909, &(Bool){1});
    return _t910;
}

Bool * I64_gte(I64 * a, I64 * b) {
    Bool *_t911 = I64_lt(a, b);
    Bool *_t912 = malloc(sizeof(Bool)); *_t912 = Bool_not(DEREF(_t911));
    Bool_delete(_t911, &(Bool){1});
    return _t912;
}

Range * Range_new(U64 start, U64 end) {
    U64 *_t913 = U64_clone(&(U64){start});
    U64 *_t914 = U64_clone(&(U64){end});
    Range *_t915 = malloc(sizeof(Range));
    _t915->start = DEREF(_t913);
    _t915->end = DEREF(_t914);
    U64_delete(_t913, &(Bool){1});
    U64_delete(_t914, &(Bool){1});
    return _t915;
}

U64 * Range_len(Range * self) {
    Bool *_t917 = U64_lte(&self->start, &self->end);
    if (DEREF(_t917)) {
        U64 *_t916 = malloc(sizeof(U64)); *_t916 = U64_sub(self->end, self->start);
        Bool_delete(_t917, &(Bool){1});
        return _t916;
    }
    Bool_delete(_t917, &(Bool){1});
    U64 *_t918 = malloc(sizeof(U64)); *_t918 = U64_sub(self->start, self->end);
    return _t918;
}

U64 * Range_get(Range * self, U64 i) {
    Bool *_t920 = U64_lte(&self->start, &self->end);
    if (DEREF(_t920)) {
        U64 *_t919 = malloc(sizeof(U64)); *_t919 = U64_add(self->start, i);
        Bool_delete(_t920, &(Bool){1});
        return _t919;
    }
    Bool_delete(_t920, &(Bool){1});
    U64 *_t921 = malloc(sizeof(U64)); *_t921 = U64_sub(self->start, i);
    return _t921;
}

Range * Range_clone(Range * val) {
    Range *_t922 = malloc(sizeof(Range));
    _t922->start = val->start;
    _t922->end = val->end;
    return _t922;
}

void Range_delete(Range * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Range_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Range);
    return r;
}

Str * Bool_to_str(Bool * b) {
    if (DEREF(b)) {
        Str *_t924 = Str_lit("true", 4ULL);
        return _t924;
    } else {
        Str *_t925 = Str_lit("false", 5ULL);
        return _t925;
    }
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool *_t930 = malloc(sizeof(Bool)); *_t930 = Bool_eq(DEREF(a), DEREF(b));
    if (DEREF(_t930)) {
        I64 *_t926 = malloc(sizeof(I64));
        *_t926 = 0;
        Bool_delete(_t930, &(Bool){1});
        return _t926;
    }
    Bool_delete(_t930, &(Bool){1});
    if (DEREF(b)) {
        I64 *_t927 = malloc(sizeof(I64));
        *_t927 = 0;
        I64 *_t928 = malloc(sizeof(I64));
        *_t928 = 1;
        I64 *_t929 = malloc(sizeof(I64)); *_t929 = I64_sub(DEREF(_t927), DEREF(_t928));
        I64_delete(_t927, &(Bool){1});
        I64_delete(_t928, &(Bool){1});
        return _t929;
    }
    I64 *_t931 = malloc(sizeof(I64));
    *_t931 = 1;
    return _t931;
}

U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

Bool * Bool_lt(Bool * a, Bool * b) {
    I64 *_t933 = malloc(sizeof(I64));
    *_t933 = 0;
    I64 *_t934 = malloc(sizeof(I64));
    *_t934 = 1;
    I64 *_t935 = Bool_cmp(a, b);
    I64 *_t936 = malloc(sizeof(I64)); *_t936 = I64_sub(DEREF(_t933), DEREF(_t934));
    I64_delete(_t933, &(Bool){1});
    I64_delete(_t934, &(Bool){1});
    Bool *_t937 = malloc(sizeof(Bool)); *_t937 = I64_eq(DEREF(_t935), DEREF(_t936));
    I64_delete(_t935, &(Bool){1});
    I64_delete(_t936, &(Bool){1});
    return _t937;
}

Bool * Bool_gt(Bool * a, Bool * b) {
    I64 *_t938 = Bool_cmp(a, b);
    I64 *_t939 = malloc(sizeof(I64));
    *_t939 = 1;
    Bool *_t940 = malloc(sizeof(Bool)); *_t940 = I64_eq(DEREF(_t938), DEREF(_t939));
    I64_delete(_t938, &(Bool){1});
    I64_delete(_t939, &(Bool){1});
    return _t940;
}

Bool * Bool_neq(Bool * a, Bool * b) {
    Bool *_t941 = malloc(sizeof(Bool)); *_t941 = Bool_eq(DEREF(a), DEREF(b));
    Bool *_t942 = malloc(sizeof(Bool)); *_t942 = Bool_not(DEREF(_t941));
    Bool_delete(_t941, &(Bool){1});
    return _t942;
}

Bool * Bool_lte(Bool * a, Bool * b) {
    Bool *_t943 = Bool_gt(a, b);
    Bool *_t944 = malloc(sizeof(Bool)); *_t944 = Bool_not(DEREF(_t943));
    Bool_delete(_t943, &(Bool){1});
    return _t944;
}

Bool * Bool_gte(Bool * a, Bool * b) {
    Bool *_t945 = Bool_lt(a, b);
    Bool *_t946 = malloc(sizeof(Bool)); *_t946 = Bool_not(DEREF(_t945));
    Bool_delete(_t945, &(Bool){1});
    return _t946;
}

void println(Array * parts) {
    {
        U64 *_fi947 = malloc(sizeof(U64));
        *_fi947 = 0;
        while (1) {
            U64 *_t949 = Array_len(parts);
            Bool *_wcond948 = U64_lt(_fi947, _t949);
            U64_delete(_t949, &(Bool){1});
            if (DEREF(_wcond948)) {
            } else {
                Bool_delete(_wcond948, &(Bool){1});
                break;
            }
            Bool_delete(_wcond948, &(Bool){1});
            Str *s = Array_get(parts, _fi947);
            I64 *_t950 = malloc(sizeof(I64));
            *_t950 = 1;
            U64 *_t951 = malloc(sizeof(U64)); *_t951 = U64_add(DEREF(_fi947), DEREF(_t950));
            I64_delete(_t950, &(Bool){1});
            *_fi947 = DEREF(_t951);
            U64_delete(_t951, &(Bool){1});
            print_single(s);
        }
        U64_delete(_fi947, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    {
        U64 *_fi952 = malloc(sizeof(U64));
        *_fi952 = 0;
        while (1) {
            U64 *_t954 = Array_len(parts);
            Bool *_wcond953 = U64_lt(_fi952, _t954);
            U64_delete(_t954, &(Bool){1});
            if (DEREF(_wcond953)) {
            } else {
                Bool_delete(_wcond953, &(Bool){1});
                break;
            }
            Bool_delete(_wcond953, &(Bool){1});
            Str *s = Array_get(parts, _fi952);
            I64 *_t955 = malloc(sizeof(I64));
            *_t955 = 1;
            U64 *_t956 = malloc(sizeof(U64)); *_t956 = U64_add(DEREF(_fi952), DEREF(_t955));
            I64_delete(_t955, &(Bool){1});
            *_fi952 = DEREF(_t956);
            U64_delete(_t956, &(Bool){1});
            print_single(s);
        }
        U64_delete(_fi952, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 *total = malloc(sizeof(U64));
    *total = 0;
    {
        U64 *_fi957 = malloc(sizeof(U64));
        *_fi957 = 0;
        while (1) {
            U64 *_t959 = Array_len(parts);
            Bool *_wcond958 = U64_lt(_fi957, _t959);
            U64_delete(_t959, &(Bool){1});
            if (DEREF(_wcond958)) {
            } else {
                Bool_delete(_wcond958, &(Bool){1});
                break;
            }
            Bool_delete(_wcond958, &(Bool){1});
            Str *s = Array_get(parts, _fi957);
            I64 *_t960 = malloc(sizeof(I64));
            *_t960 = 1;
            U64 *_t961 = malloc(sizeof(U64)); *_t961 = U64_add(DEREF(_fi957), DEREF(_t960));
            I64_delete(_t960, &(Bool){1});
            *_fi957 = DEREF(_t961);
            U64_delete(_t961, &(Bool){1});
            U64 *_t962 = Str_len(s);
            U64 *_t963 = malloc(sizeof(U64)); *_t963 = U64_add(DEREF(total), DEREF(_t962));
            U64_delete(_t962, &(Bool){1});
            *total = DEREF(_t963);
            U64_delete(_t963, &(Bool){1});
        }
        U64_delete(_fi957, &(Bool){1});
    }
    U8 *buf = malloc(DEREF(total));
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    {
        U64 *_fi964 = malloc(sizeof(U64));
        *_fi964 = 0;
        while (1) {
            U64 *_t966 = Array_len(parts);
            Bool *_wcond965 = U64_lt(_fi964, _t966);
            U64_delete(_t966, &(Bool){1});
            if (DEREF(_wcond965)) {
            } else {
                Bool_delete(_wcond965, &(Bool){1});
                break;
            }
            Bool_delete(_wcond965, &(Bool){1});
            Str *s = Array_get(parts, _fi964);
            I64 *_t967 = malloc(sizeof(I64));
            *_t967 = 1;
            U64 *_t968 = malloc(sizeof(U64)); *_t968 = U64_add(DEREF(_fi964), DEREF(_t967));
            I64_delete(_t967, &(Bool){1});
            *_fi964 = DEREF(_t968);
            U64_delete(_t968, &(Bool){1});
            void *_t969 = ptr_add(buf, DEREF(offset));
            U64 *_t970 = Str_len(s);
            memcpy(_t969, s->c_str, DEREF(_t970));
            U64_delete(_t970, &(Bool){1});
            U64 *_t971 = Str_len(s);
            U64 *_t972 = malloc(sizeof(U64)); *_t972 = U64_add(DEREF(offset), DEREF(_t971));
            U64_delete(_t971, &(Bool){1});
            *offset = DEREF(_t972);
            U64_delete(_t972, &(Bool){1});
        }
        U64_delete(_fi964, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 *_t973 = U64_clone(total);
    U64 *_t974 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t975 = malloc(sizeof(Str));
    _t975->c_str = buf;
    _t975->count = DEREF(_t973);
    _t975->cap = DEREF(_t974);
    U64_delete(_t973, &(Bool){1});
    U64_delete(_t974, &(Bool){1});
    return _t975;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 *status = check_cmd_status(DEREF(pid));
        I64 *_t976 = malloc(sizeof(I64));
        *_t976 = 0;
        I64 *_t977 = malloc(sizeof(I64));
        *_t977 = 1;
        I64 *_t978 = malloc(sizeof(I64)); *_t978 = I64_sub(DEREF(_t976), DEREF(_t977));
        I64_delete(_t976, &(Bool){1});
        I64_delete(_t977, &(Bool){1});
        Bool *_t979 = I64_neq(status, _t978);
        I64_delete(_t978, &(Bool){1});
        if (DEREF(_t979)) {
            Bool_delete(_t979, &(Bool){1});
            return status;
        }
        Bool_delete(_t979, &(Bool){1});
        I64_delete(status, &(Bool){1});
        I64 *_t980 = malloc(sizeof(I64));
        *_t980 = 50;
        sleep_ms(DEREF(_t980));
        I64_delete(_t980, &(Bool){1});
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t986 = Array_len(args);
        Bool *_wcond981 = U64_lt(i, _t986);
        U64_delete(_t986, &(Bool){1});
        if (DEREF(_wcond981)) {
        } else {
            Bool_delete(_wcond981, &(Bool){1});
            break;
        }
        Bool_delete(_wcond981, &(Bool){1});
        Str *arg = Array_get(args, i);
        I64 *_t987 = malloc(sizeof(I64));
        *_t987 = 0;
        Bool *_t988 = U64_gt(i, _t987);
        I64_delete(_t987, &(Bool){1});
        if (DEREF(_t988)) {
            Str *_t982 = Str_lit(" '", 2ULL);
            Str *_t983 = Str_concat(cmd, _t982);
            Str_delete(_t982, &(Bool){1});
            Str *_t984 = Str_concat(_t983, arg);
            Str_delete(_t983, &(Bool){1});
            Str *_t985 = Str_lit("'", 1ULL);
            cmd = Str_concat(_t984, _t985);
            Str_delete(_t984, &(Bool){1});
            Str_delete(_t985, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        Bool_delete(_t988, &(Bool){1});
        I64 *_t989 = malloc(sizeof(I64));
        *_t989 = 1;
        U64 *_t990 = malloc(sizeof(U64)); *_t990 = U64_add(DEREF(i), DEREF(_t989));
        I64_delete(_t989, &(Bool){1});
        *i = DEREF(_t990);
        U64_delete(_t990, &(Bool){1});
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    Str *_t991 = Str_lit(" > ", 3ULL);
    Str *_t992 = Str_concat(cmd, _t991);
    Str_delete(_t991, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t993 = Str_concat(_t992, tmpf);
    Str_delete(_t992, &(Bool){1});
    Str *_t994 = Str_lit(" 2>&1", 5ULL);
    Str *_t995 = Str_concat(_t993, _t994);
    Str_delete(_t993, &(Bool){1});
    Str_delete(_t994, &(Bool){1});
    I64 *pid = spawn_cmd(_t995);
    Str_delete(_t995, &(Bool){1});
    I64 *ec = wait_cmd(pid);
    I64_delete(pid, &(Bool){1});
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 *_t996 = Str_size();
    memcpy(output, content, DEREF(_t996));
    U64_delete(_t996, &(Bool){1});
    free(content);
    return ec;
}

void panic(Str * loc_str, Array * parts) {
    Str *_t997 = Str_lit("Str", 3ULL);
    I64 *_t998 = Str_size();
    I64 *_t999 = malloc(sizeof(I64));
    *_t999 = 3;
    Array *_va16 = Array_new(_t997, _t998, _t999);
    Str_delete(_t997, &(Bool){1});
    I64_delete(_t998, &(Bool){1});
    I64_delete(_t999, &(Bool){1});
    I64 *_t1000 = malloc(sizeof(I64));
    *_t1000 = 0;
    Str *_t1001 = Str_clone(loc_str);
    Array_set(_va16, _t1000, _t1001);
    I64_delete(_t1000, &(Bool){1});
    I64 *_t1002 = malloc(sizeof(I64));
    *_t1002 = 1;
    Str *_t1003 = Str_lit(": panic: ", 9ULL);
    Array_set(_va16, _t1002, _t1003);
    I64_delete(_t1002, &(Bool){1});
    I64 *_t1004 = malloc(sizeof(I64));
    *_t1004 = 2;
    Str *_t1005 = format(parts);
    Array_set(_va16, _t1004, _t1005);
    I64_delete(_t1004, &(Bool){1});
    println(_va16);
    I64 *_t1006 = malloc(sizeof(I64));
    *_t1006 = 1;
    exit(DEREF(_t1006));
    I64_delete(_t1006, &(Bool){1});
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t1007 = Str_lit("Str", 3ULL);
    I64 *_t1008 = Str_size();
    I64 *_t1009 = malloc(sizeof(I64));
    *_t1009 = 2;
    Array *_va17 = Array_new(_t1007, _t1008, _t1009);
    Str_delete(_t1007, &(Bool){1});
    I64_delete(_t1008, &(Bool){1});
    I64_delete(_t1009, &(Bool){1});
    I64 *_t1010 = malloc(sizeof(I64));
    *_t1010 = 0;
    Str *_t1011 = Str_lit("TODO: ", 6ULL);
    Array_set(_va17, _t1010, _t1011);
    I64_delete(_t1010, &(Bool){1});
    I64 *_t1012 = malloc(sizeof(I64));
    *_t1012 = 1;
    Str *_t1013 = format(parts);
    Array_set(_va17, _t1012, _t1013);
    I64_delete(_t1012, &(Bool){1});
    panic(loc_str, _va17);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t1014 = Str_lit("Str", 3ULL);
    I64 *_t1015 = Str_size();
    I64 *_t1016 = malloc(sizeof(I64));
    *_t1016 = 1;
    Array *_va18 = Array_new(_t1014, _t1015, _t1016);
    Str_delete(_t1014, &(Bool){1});
    I64_delete(_t1015, &(Bool){1});
    I64_delete(_t1016, &(Bool){1});
    I64 *_t1017 = malloc(sizeof(I64));
    *_t1017 = 0;
    Str *_t1018 = Str_lit("unreachable", 11ULL);
    Array_set(_va18, _t1017, _t1018);
    I64_delete(_t1017, &(Bool){1});
    panic(loc_str, _va18);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool *_t1026 = malloc(sizeof(Bool)); *_t1026 = Bool_not(DEREF(cond));
    if (DEREF(_t1026)) {
        Str *_t1019 = Str_lit("Str", 3ULL);
        I64 *_t1020 = Str_size();
        I64 *_t1021 = malloc(sizeof(I64));
        *_t1021 = 2;
        Array *_va19 = Array_new(_t1019, _t1020, _t1021);
        Str_delete(_t1019, &(Bool){1});
        I64_delete(_t1020, &(Bool){1});
        I64_delete(_t1021, &(Bool){1});
        I64 *_t1022 = malloc(sizeof(I64));
        *_t1022 = 0;
        Str *_t1023 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va19, _t1022, _t1023);
        I64_delete(_t1022, &(Bool){1});
        I64 *_t1024 = malloc(sizeof(I64));
        *_t1024 = 1;
        Str *_t1025 = format(parts);
        Array_set(_va19, _t1024, _t1025);
        I64_delete(_t1024, &(Bool){1});
        panic(loc_str, _va19);
    }
    Bool_delete(_t1026, &(Bool){1});
    Bool *_t1027 = malloc(sizeof(Bool));
    *_t1027 = 1;
    return _t1027;
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t1028 = Str_lit("Str", 3ULL);
    I64 *_t1029 = Str_size();
    I64 *_t1030 = malloc(sizeof(I64));
    *_t1030 = 0;
    Array *_va20 = Array_new(_t1028, _t1029, _t1030);
    Str_delete(_t1028, &(Bool){1});
    I64_delete(_t1029, &(Bool){1});
    I64_delete(_t1030, &(Bool){1});
    Bool *_t1031 = assertm(loc_str, cond, _va20);
    return _t1031;
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t1032 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool *_t1033 = assertm(loc_str, cond, _t1032);
    Bool_delete(_t1033, &(Bool){1});
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool *_t1047 = I64_neq(a, b);
    if (DEREF(_t1047)) {
        Str *_t1034 = Str_lit("Str", 3ULL);
        I64 *_t1035 = Str_size();
        I64 *_t1036 = malloc(sizeof(I64));
        *_t1036 = 5;
        Array *_va21 = Array_new(_t1034, _t1035, _t1036);
        Str_delete(_t1034, &(Bool){1});
        I64_delete(_t1035, &(Bool){1});
        I64_delete(_t1036, &(Bool){1});
        I64 *_t1037 = malloc(sizeof(I64));
        *_t1037 = 0;
        Str *_t1038 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va21, _t1037, _t1038);
        I64_delete(_t1037, &(Bool){1});
        I64 *_t1039 = malloc(sizeof(I64));
        *_t1039 = 1;
        Str *_t1040 = I64_to_str(a);
        Array_set(_va21, _t1039, _t1040);
        I64_delete(_t1039, &(Bool){1});
        I64 *_t1041 = malloc(sizeof(I64));
        *_t1041 = 2;
        Str *_t1042 = Str_lit("', found '", 10ULL);
        Array_set(_va21, _t1041, _t1042);
        I64_delete(_t1041, &(Bool){1});
        I64 *_t1043 = malloc(sizeof(I64));
        *_t1043 = 3;
        Str *_t1044 = I64_to_str(b);
        Array_set(_va21, _t1043, _t1044);
        I64_delete(_t1043, &(Bool){1});
        I64 *_t1045 = malloc(sizeof(I64));
        *_t1045 = 4;
        Str *_t1046 = Str_lit("'", 1ULL);
        Array_set(_va21, _t1045, _t1046);
        I64_delete(_t1045, &(Bool){1});
        panic(loc_str, _va21);
    }
    Bool_delete(_t1047, &(Bool){1});
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool *_t1061 = Str_eq(a, b);
    Bool *_t1062 = malloc(sizeof(Bool)); *_t1062 = Bool_not(DEREF(_t1061));
    Bool_delete(_t1061, &(Bool){1});
    if (DEREF(_t1062)) {
        Str *_t1048 = Str_lit("Str", 3ULL);
        I64 *_t1049 = Str_size();
        I64 *_t1050 = malloc(sizeof(I64));
        *_t1050 = 5;
        Array *_va22 = Array_new(_t1048, _t1049, _t1050);
        Str_delete(_t1048, &(Bool){1});
        I64_delete(_t1049, &(Bool){1});
        I64_delete(_t1050, &(Bool){1});
        I64 *_t1051 = malloc(sizeof(I64));
        *_t1051 = 0;
        Str *_t1052 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va22, _t1051, _t1052);
        I64_delete(_t1051, &(Bool){1});
        I64 *_t1053 = malloc(sizeof(I64));
        *_t1053 = 1;
        Str *_t1054 = Str_clone(a);
        Array_set(_va22, _t1053, _t1054);
        I64_delete(_t1053, &(Bool){1});
        I64 *_t1055 = malloc(sizeof(I64));
        *_t1055 = 2;
        Str *_t1056 = Str_lit("', found '", 10ULL);
        Array_set(_va22, _t1055, _t1056);
        I64_delete(_t1055, &(Bool){1});
        I64 *_t1057 = malloc(sizeof(I64));
        *_t1057 = 3;
        Str *_t1058 = Str_clone(b);
        Array_set(_va22, _t1057, _t1058);
        I64_delete(_t1057, &(Bool){1});
        I64 *_t1059 = malloc(sizeof(I64));
        *_t1059 = 4;
        Str *_t1060 = Str_lit("'", 1ULL);
        Array_set(_va22, _t1059, _t1060);
        I64_delete(_t1059, &(Bool){1});
        panic(loc_str, _va22);
    }
    Bool_delete(_t1062, &(Bool){1});
}

void dyn_call_delete(Str *type_name, void *val, void *arg2) {
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) { Array_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) { Map_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) { Set_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) { Str_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) { Vec_delete(val, arg2); return; }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) { EnumDef_delete(val, arg2); return; }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { U8_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) { I16_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) { F32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { U32_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { U64_delete(val, arg2); return; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64_delete(val, arg2); return; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) { Range_delete(val, arg2); return; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool_delete(val, arg2); return; }
    fprintf(stderr, "dyn_call: unknown type for delete\n");
    exit(1);
}

void *dyn_call_clone(Str *type_name, void *val) {
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) return (void *)Array_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Map", 3ULL) == 0) return (void *)Map_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Set", 3ULL) == 0) return (void *)Set_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return (void *)Str_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Vec", 3ULL) == 0) return (void *)Vec_clone(val);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "EnumDef", 7ULL) == 0) return (void *)EnumDef_clone(val);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return (void *)U8_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) return (void *)I16_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return (void *)I32_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return (void *)F32_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return (void *)U32_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return (void *)U64_clone(val);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return (void *)I64_clone(val);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) return (void *)Range_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return (void *)Bool_clone(val);
    fprintf(stderr, "dyn_call: unknown type for clone\n");
    exit(1);
}

void *dyn_call_cmp(Str *type_name, void *val, void *arg2) {
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return (void *)Str_cmp(val, arg2);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = U8_cmp(*(U8 *)val, *(U8 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I16_cmp(*(I16 *)val, *(I16 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I32_cmp(*(I32 *)val, *(I32 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = F32_cmp(*(F32 *)val, *(F32 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = U32_cmp(*(U32 *)val, *(U32 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = U64_cmp(*(U64 *)val, *(U64 *)arg2); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I64_cmp(*(I64 *)val, *(I64 *)arg2); return _r; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return (void *)Bool_cmp(val, arg2);
    fprintf(stderr, "dyn_call: unknown type for cmp\n");
    exit(1);
}

Bool *dyn_has_cmp(Str *type_name) {
    (void)type_name;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool *r = malloc(sizeof(Bool)); *r = 1; return r; }
    Bool *r = malloc(sizeof(Bool)); *r = 0; return r;
}

