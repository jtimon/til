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
typedef struct Range Range;

Bool Bool_and(Bool, Bool);
Bool Bool_or(Bool, Bool);
Bool Bool_not(Bool);
Bool is_null(void *);
void * ptr_add(void *, U64);
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
static Str * U8_to_str(U8 * val);
static U8 * U8_from_i64(I64 * val);
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
static U64 * U8_size(void);
static Bool * U8_lt(U8 * a, U8 * b);
static Bool * U8_gt(U8 * a, U8 * b);
static Bool * U8_neq(U8 * a, U8 * b);
static Bool * U8_lte(U8 * a, U8 * b);
static Bool * U8_gte(U8 * a, U8 * b);
I64 I16_to_i64(I16 val);
static Str * I16_to_str(I16 * val);
static I16 * I16_from_i64(I64 * val);
I16 I16_add(I16 a, I16 b);
I16 I16_sub(I16 a, I16 b);
I16 I16_mul(I16 a, I16 b);
I16 I16_div(I16 a, I16 b);
I16 I16_mod(I16 a, I16 b);
I16 I16_inc(I16 a);
I16 I16_dec(I16 a);
Bool I16_eq(I16 a, I16 b);
I64 I16_cmp(I16 a, I16 b);
static I16 * I16_neg(I16 * a);
static I16 * I16_abs(I16 * a);
I16 I16_and(I16 a, I16 b);
I16 I16_or(I16 a, I16 b);
I16 I16_xor(I16 a, I16 b);
I16 * I16_clone(I16 * val);
void I16_delete(I16 * self, Bool * call_free);
static U64 * I16_size(void);
static Bool * I16_lt(I16 * a, I16 * b);
static Bool * I16_gt(I16 * a, I16 * b);
static Bool * I16_neq(I16 * a, I16 * b);
static Bool * I16_lte(I16 * a, I16 * b);
static Bool * I16_gte(I16 * a, I16 * b);
I64 I32_to_i64(I32 val);
static Str * I32_to_str(I32 * val);
static I32 * I32_from_i64(I64 * val);
I32 I32_add(I32 a, I32 b);
I32 I32_sub(I32 a, I32 b);
I32 I32_mul(I32 a, I32 b);
I32 I32_div(I32 a, I32 b);
I32 I32_mod(I32 a, I32 b);
I32 I32_inc(I32 a);
I32 I32_dec(I32 a);
Bool I32_eq(I32 a, I32 b);
I64 I32_cmp(I32 a, I32 b);
static I32 * I32_neg(I32 * a);
static I32 * I32_abs(I32 * a);
I32 I32_and(I32 a, I32 b);
I32 I32_or(I32 a, I32 b);
I32 I32_xor(I32 a, I32 b);
I32 * I32_clone(I32 * val);
void I32_delete(I32 * self, Bool * call_free);
static U64 * I32_size(void);
static Bool * I32_lt(I32 * a, I32 * b);
static Bool * I32_gt(I32 * a, I32 * b);
static Bool * I32_neq(I32 * a, I32 * b);
static Bool * I32_lte(I32 * a, I32 * b);
static Bool * I32_gte(I32 * a, I32 * b);
I64 F32_to_i64(F32 val);
Str * F32_to_str(F32 val);
static F32 * F32_from_i64(I64 * val);
F32 F32_add(F32 a, F32 b);
F32 F32_sub(F32 a, F32 b);
F32 F32_mul(F32 a, F32 b);
F32 F32_div(F32 a, F32 b);
Bool F32_eq(F32 a, F32 b);
I64 F32_cmp(F32 a, F32 b);
F32 * F32_clone(F32 * val);
void F32_delete(F32 * self, Bool * call_free);
static U64 * F32_size(void);
static Bool * F32_lt(F32 * a, F32 * b);
static Bool * F32_gt(F32 * a, F32 * b);
static Bool * F32_neq(F32 * a, F32 * b);
static Bool * F32_lte(F32 * a, F32 * b);
static Bool * F32_gte(F32 * a, F32 * b);
I64 U32_to_i64(U32 val);
static Str * U32_to_str(U32 * val);
static U32 * U32_from_i64(I64 * val);
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
static U64 * U32_size(void);
static Bool * U32_lt(U32 * a, U32 * b);
static Bool * U32_gt(U32 * a, U32 * b);
static Bool * U32_neq(U32 * a, U32 * b);
static Bool * U32_lte(U32 * a, U32 * b);
static Bool * U32_gte(U32 * a, U32 * b);
I64 U64_to_i64(U64 val);
Str * U64_to_str(U64 val);
static U64 * U64_from_i64(I64 * val);
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
static U64 * U64_size(void);
static Bool * U64_lt(U64 * a, U64 * b);
static Bool * U64_gt(U64 * a, U64 * b);
static Bool * U64_neq(U64 * a, U64 * b);
static Bool * U64_lte(U64 * a, U64 * b);
static Bool * U64_gte(U64 * a, U64 * b);
static Str * I64_to_str(I64 * val);
I64 I64_add(I64 a, I64 b);
I64 I64_sub(I64 a, I64 b);
I64 I64_mul(I64 a, I64 b);
I64 I64_div(I64 a, I64 b);
I64 I64_mod(I64 a, I64 b);
I64 I64_inc(I64 a);
I64 I64_dec(I64 a);
Bool I64_eq(I64 a, I64 b);
I64 I64_cmp(I64 a, I64 b);
static I64 * I64_neg(I64 * a);
static I64 * I64_abs(I64 * a);
I64 I64_and(I64 a, I64 b);
I64 I64_or(I64 a, I64 b);
I64 I64_xor(I64 a, I64 b);
I64 * I64_clone(I64 * val);
void I64_delete(I64 * self, Bool * call_free);
static U64 * I64_size(void);
static Bool * I64_lt(I64 * a, I64 * b);
static Bool * I64_gt(I64 * a, I64 * b);
static Bool * I64_neq(I64 * a, I64 * b);
static Bool * I64_lte(I64 * a, I64 * b);
static Bool * I64_gte(I64 * a, I64 * b);
Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
static Str * Bool_to_str(Bool * b);
Bool Bool_eq(Bool a, Bool b);
static I64 * Bool_cmp(Bool * a, Bool * b);
Bool * Bool_clone(Bool * val);
void Bool_delete(Bool * self, Bool * call_free);
static U64 * Bool_size(void);
static Bool * Bool_lt(Bool * a, Bool * b);
static Bool * Bool_gt(Bool * a, Bool * b);
static Bool * Bool_neq(Bool * a, Bool * b);
static Bool * Bool_lte(Bool * a, Bool * b);
static Bool * Bool_gte(Bool * a, Bool * b);
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









typedef struct Range {
    U64 start;
    U64 end;
} Range;



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

static I64 *_t1098;
static I64 *_t1099;
static I64 *_t1100;
static U64 *CAP_LIT;
static I64 *_t1101;
static I64 *_t1102;
static I64 *_t1103;
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
        U64 *_t5 = Str_size();
        U64 *_t6 = malloc(sizeof(U64));
        *_t6 = 5;
        Array *_va0 = Array_new(_t4, _t5, _t6);
        Str_delete(_t4, &(Bool){1});
        U64_delete(_t5, &(Bool){1});
        U64_delete(_t6, &(Bool){1});
        U64 *_t7 = malloc(sizeof(U64));
        *_t7 = 0;
        Str *_t8 = Str_lit("index ", 6ULL);
        Array_set(_va0, _t7, _t8);
        U64_delete(_t7, &(Bool){1});
        U64 *_t9 = malloc(sizeof(U64));
        *_t9 = 1;
        Str *_t10 = U64_to_str(DEREF(i));
        Array_set(_va0, _t9, _t10);
        U64_delete(_t9, &(Bool){1});
        U64 *_t11 = malloc(sizeof(U64));
        *_t11 = 2;
        Str *_t12 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va0, _t11, _t12);
        U64_delete(_t11, &(Bool){1});
        U64 *_t13 = malloc(sizeof(U64));
        *_t13 = 3;
        Str *_t14 = U64_to_str(self->cap);
        Array_set(_va0, _t13, _t14);
        U64_delete(_t13, &(Bool){1});
        U64 *_t15 = malloc(sizeof(U64));
        *_t15 = 4;
        Str *_t16 = Str_lit(")", 1ULL);
        Array_set(_va0, _t15, _t16);
        U64_delete(_t15, &(Bool){1});
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
        U64 *_t22 = Str_size();
        U64 *_t23 = malloc(sizeof(U64));
        *_t23 = 5;
        Array *_va1 = Array_new(_t21, _t22, _t23);
        Str_delete(_t21, &(Bool){1});
        U64_delete(_t22, &(Bool){1});
        U64_delete(_t23, &(Bool){1});
        U64 *_t24 = malloc(sizeof(U64));
        *_t24 = 0;
        Str *_t25 = Str_lit("index ", 6ULL);
        Array_set(_va1, _t24, _t25);
        U64_delete(_t24, &(Bool){1});
        U64 *_t26 = malloc(sizeof(U64));
        *_t26 = 1;
        Str *_t27 = U64_to_str(DEREF(i));
        Array_set(_va1, _t26, _t27);
        U64_delete(_t26, &(Bool){1});
        U64 *_t28 = malloc(sizeof(U64));
        *_t28 = 2;
        Str *_t29 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va1, _t28, _t29);
        U64_delete(_t28, &(Bool){1});
        U64 *_t30 = malloc(sizeof(U64));
        *_t30 = 3;
        Str *_t31 = U64_to_str(self->cap);
        Array_set(_va1, _t30, _t31);
        U64_delete(_t30, &(Bool){1});
        U64 *_t32 = malloc(sizeof(U64));
        *_t32 = 4;
        Str *_t33 = Str_lit(")", 1ULL);
        Array_set(_va1, _t32, _t33);
        U64_delete(_t32, &(Bool){1});
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
    Bool *_t82 = Str_is_empty(key_type);
    Bool *_t83 = malloc(sizeof(Bool)); *_t83 = Bool_not(DEREF(_t82));
    Bool_delete(_t82, &(Bool){1});
    if (DEREF(_t83)) {
        Bool *_t80 = dyn_has_cmp(key_type);
        Bool *_t81 = malloc(sizeof(Bool)); *_t81 = Bool_not(DEREF(_t80));
        Bool_delete(_t80, &(Bool){1});
        if (DEREF(_t81)) {
            Str *_t70 = Str_lit("Str", 3ULL);
            U64 *_t71 = Str_size();
            U64 *_t72 = malloc(sizeof(U64));
            *_t72 = 3;
            Array *_va2 = Array_new(_t70, _t71, _t72);
            Str_delete(_t70, &(Bool){1});
            U64_delete(_t71, &(Bool){1});
            U64_delete(_t72, &(Bool){1});
            U64 *_t73 = malloc(sizeof(U64));
            *_t73 = 0;
            Str *_t74 = Str_lit("type ", 5ULL);
            Array_set(_va2, _t73, _t74);
            U64_delete(_t73, &(Bool){1});
            U64 *_t75 = malloc(sizeof(U64));
            *_t75 = 1;
            Str *_t76 = Str_clone(key_type);
            Array_set(_va2, _t75, _t76);
            U64_delete(_t75, &(Bool){1});
            U64 *_t77 = malloc(sizeof(U64));
            *_t77 = 2;
            Str *_t78 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va2, _t77, _t78);
            U64_delete(_t77, &(Bool){1});
            Str *_t79 = Str_lit("Map.new", 7ULL);
            panic(_t79, _va2);
            Str_delete(_t79, &(Bool){1});
            Array_delete(_va2, &(Bool){1});
        }
        Bool_delete(_t81, &(Bool){1});
    }
    Bool_delete(_t83, &(Bool){1});
    void *_t84 = malloc(DEREF(key_size));
    void *_t85 = malloc(DEREF(val_size));
    U64 *_t86 = malloc(sizeof(U64));
    *_t86 = 0;
    I64 *_t87 = malloc(sizeof(I64));
    *_t87 = 1;
    U64 *_t88 = U64_clone(key_size);
    U64 *_t89 = U64_clone(val_size);
    Map *_t90 = malloc(sizeof(Map));
    _t90->key_data = _t84;
    _t90->val_data = _t85;
    _t90->count = DEREF(_t86);
    _t90->cap = DEREF(_t87);
    _t90->key_size = DEREF(_t88);
    { Str *_ca = Str_clone(key_type); _t90->key_type = *_ca; free(_ca); }
    _t90->val_size = DEREF(_t89);
    { Str *_ca = Str_clone(val_type); _t90->val_type = *_ca; free(_ca); }
    U64_delete(_t86, &(Bool){1});
    I64_delete(_t87, &(Bool){1});
    U64_delete(_t88, &(Bool){1});
    U64_delete(_t89, &(Bool){1});
    return _t90;
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
        Bool *_wcond91 = U64_lt(lo, hi);
        if (DEREF(_wcond91)) {
        } else {
            Bool_delete(_wcond91, &(Bool){1});
            break;
        }
        Bool_delete(_wcond91, &(Bool){1});
        U64 *_t98 = malloc(sizeof(U64)); *_t98 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t99 = malloc(sizeof(I64));
        *_t99 = 2;
        U64 *_t100 = malloc(sizeof(U64)); *_t100 = U64_div(DEREF(_t98), DEREF(_t99));
        U64_delete(_t98, &(Bool){1});
        I64_delete(_t99, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t100));
        U64_delete(_t100, &(Bool){1});
        U64 *_t101 = malloc(sizeof(U64)); *_t101 = U64_mul(DEREF(mid), self->key_size);
        void *_t102 = ptr_add(self->key_data, DEREF(_t101));
        I64 *c = dyn_call_cmp(&self->key_type, _t102, key);
        U64_delete(_t101, &(Bool){1});
        I64 *_t103 = malloc(sizeof(I64));
        *_t103 = 0;
        Bool *_t104 = I64_lt(c, _t103);
        I64_delete(_t103, &(Bool){1});
        if (DEREF(_t104)) {
            I64 *_t92 = malloc(sizeof(I64));
            *_t92 = 1;
            U64 *_t93 = malloc(sizeof(U64)); *_t93 = U64_add(DEREF(mid), DEREF(_t92));
            I64_delete(_t92, &(Bool){1});
            *lo = DEREF(_t93);
            U64_delete(_t93, &(Bool){1});
        } else {
            I64 *_t96 = malloc(sizeof(I64));
            *_t96 = 0;
            Bool *_t97 = I64_gt(c, _t96);
            I64_delete(_t96, &(Bool){1});
            if (DEREF(_t97)) {
                U64 *_t94 = U64_clone(mid);
                *hi = DEREF(_t94);
                U64_delete(_t94, &(Bool){1});
            } else {
                Bool *_t95 = malloc(sizeof(Bool));
                *_t95 = 1;
                Bool_delete(_t97, &(Bool){1});
                Bool_delete(_t104, &(Bool){1});
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                U64_delete(hi, &(Bool){1});
                U64_delete(lo, &(Bool){1});
                return _t95;
            }
            Bool_delete(_t97, &(Bool){1});
        }
        Bool_delete(_t104, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    U64_delete(lo, &(Bool){1});
    Bool *_t105 = malloc(sizeof(Bool));
    *_t105 = 0;
    return _t105;
}

void * Map_get(Map * self, void * key) {
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    while (1) {
        Bool *_wcond106 = U64_lt(lo, hi);
        if (DEREF(_wcond106)) {
        } else {
            Bool_delete(_wcond106, &(Bool){1});
            break;
        }
        Bool_delete(_wcond106, &(Bool){1});
        U64 *_t114 = malloc(sizeof(U64)); *_t114 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t115 = malloc(sizeof(I64));
        *_t115 = 2;
        U64 *_t116 = malloc(sizeof(U64)); *_t116 = U64_div(DEREF(_t114), DEREF(_t115));
        U64_delete(_t114, &(Bool){1});
        I64_delete(_t115, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t116));
        U64_delete(_t116, &(Bool){1});
        U64 *_t117 = malloc(sizeof(U64)); *_t117 = U64_mul(DEREF(mid), self->key_size);
        void *_t118 = ptr_add(self->key_data, DEREF(_t117));
        I64 *c = dyn_call_cmp(&self->key_type, _t118, key);
        U64_delete(_t117, &(Bool){1});
        I64 *_t119 = malloc(sizeof(I64));
        *_t119 = 0;
        Bool *_t120 = I64_lt(c, _t119);
        I64_delete(_t119, &(Bool){1});
        if (DEREF(_t120)) {
            I64 *_t107 = malloc(sizeof(I64));
            *_t107 = 1;
            U64 *_t108 = malloc(sizeof(U64)); *_t108 = U64_add(DEREF(mid), DEREF(_t107));
            I64_delete(_t107, &(Bool){1});
            *lo = DEREF(_t108);
            U64_delete(_t108, &(Bool){1});
        } else {
            I64 *_t112 = malloc(sizeof(I64));
            *_t112 = 0;
            Bool *_t113 = I64_gt(c, _t112);
            I64_delete(_t112, &(Bool){1});
            if (DEREF(_t113)) {
                U64 *_t109 = U64_clone(mid);
                *hi = DEREF(_t109);
                U64_delete(_t109, &(Bool){1});
            } else {
                U64 *_t110 = malloc(sizeof(U64)); *_t110 = U64_mul(DEREF(mid), self->val_size);
                void *_t111 = ptr_add(self->val_data, DEREF(_t110));
                U64_delete(_t110, &(Bool){1});
                Bool_delete(_t113, &(Bool){1});
                Bool_delete(_t120, &(Bool){1});
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                U64_delete(hi, &(Bool){1});
                U64_delete(lo, &(Bool){1});
                return _t111;
            }
            Bool_delete(_t113, &(Bool){1});
        }
        Bool_delete(_t120, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    U64_delete(lo, &(Bool){1});
    Str *_t121 = Str_lit("Str", 3ULL);
    U64 *_t122 = Str_size();
    U64 *_t123 = malloc(sizeof(U64));
    *_t123 = 1;
    Array *_va3 = Array_new(_t121, _t122, _t123);
    Str_delete(_t121, &(Bool){1});
    U64_delete(_t122, &(Bool){1});
    U64_delete(_t123, &(Bool){1});
    U64 *_t124 = malloc(sizeof(U64));
    *_t124 = 0;
    Str *_t125 = Str_lit("key not found", 13ULL);
    Array_set(_va3, _t124, _t125);
    U64_delete(_t124, &(Bool){1});
    Str *_t126 = Str_lit("Map.get", 7ULL);
    panic(_t126, _va3);
    Str_delete(_t126, &(Bool){1});
    Array_delete(_va3, &(Bool){1});
    I64 *_t127 = malloc(sizeof(I64));
    *_t127 = 0;
    void *_t128 = ptr_add(self->val_data, DEREF(_t127));
    I64_delete(_t127, &(Bool){1});
    return _t128;
}

void Map_set(Map * self, void * key, void * val) {
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    Bool *found = malloc(sizeof(Bool));
    *found = 0;
    while (1) {
        Bool *_wcond129 = U64_lt(lo, hi);
        if (DEREF(_wcond129)) {
        } else {
            Bool_delete(_wcond129, &(Bool){1});
            break;
        }
        Bool_delete(_wcond129, &(Bool){1});
        U64 *_t138 = malloc(sizeof(U64)); *_t138 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t139 = malloc(sizeof(I64));
        *_t139 = 2;
        U64 *_t140 = malloc(sizeof(U64)); *_t140 = U64_div(DEREF(_t138), DEREF(_t139));
        U64_delete(_t138, &(Bool){1});
        I64_delete(_t139, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t140));
        U64_delete(_t140, &(Bool){1});
        U64 *_t141 = malloc(sizeof(U64)); *_t141 = U64_mul(DEREF(mid), self->key_size);
        void *_t142 = ptr_add(self->key_data, DEREF(_t141));
        I64 *c = dyn_call_cmp(&self->key_type, _t142, key);
        U64_delete(_t141, &(Bool){1});
        I64 *_t143 = malloc(sizeof(I64));
        *_t143 = 0;
        Bool *_t144 = I64_lt(c, _t143);
        I64_delete(_t143, &(Bool){1});
        if (DEREF(_t144)) {
            I64 *_t130 = malloc(sizeof(I64));
            *_t130 = 1;
            U64 *_t131 = malloc(sizeof(U64)); *_t131 = U64_add(DEREF(mid), DEREF(_t130));
            I64_delete(_t130, &(Bool){1});
            *lo = DEREF(_t131);
            U64_delete(_t131, &(Bool){1});
        } else {
            I64 *_t136 = malloc(sizeof(I64));
            *_t136 = 0;
            Bool *_t137 = I64_gt(c, _t136);
            I64_delete(_t136, &(Bool){1});
            if (DEREF(_t137)) {
                U64 *_t132 = U64_clone(mid);
                *hi = DEREF(_t132);
                U64_delete(_t132, &(Bool){1});
            } else {
                Bool *_t133 = malloc(sizeof(Bool));
                *_t133 = 1;
                *found = DEREF(_t133);
                Bool_delete(_t133, &(Bool){1});
                U64 *_t134 = U64_clone(mid);
                *lo = DEREF(_t134);
                U64_delete(_t134, &(Bool){1});
                U64 *_t135 = U64_clone(mid);
                *hi = DEREF(_t135);
                U64_delete(_t135, &(Bool){1});
            }
            Bool_delete(_t137, &(Bool){1});
        }
        Bool_delete(_t144, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    if (DEREF(found)) {
        Bool *_t149 = Str_is_empty(&self->key_type);
        Bool *_t150 = malloc(sizeof(Bool)); *_t150 = Bool_not(DEREF(_t149));
        Bool_delete(_t149, &(Bool){1});
        if (DEREF(_t150)) {
            Bool *_t145 = malloc(sizeof(Bool));
            *_t145 = 0;
            dyn_call_delete(&self->key_type, key, _t145);
            Bool_delete(_t145, &(Bool){1});
        }
        Bool_delete(_t150, &(Bool){1});
        free(key);
        Bool *_t151 = Str_is_empty(&self->val_type);
        Bool *_t152 = malloc(sizeof(Bool)); *_t152 = Bool_not(DEREF(_t151));
        Bool_delete(_t151, &(Bool){1});
        if (DEREF(_t152)) {
            U64 *_t146 = malloc(sizeof(U64)); *_t146 = U64_mul(DEREF(lo), self->val_size);
            void *_t147 = ptr_add(self->val_data, DEREF(_t146));
            Bool *_t148 = malloc(sizeof(Bool));
            *_t148 = 0;
            dyn_call_delete(&self->val_type, _t147, _t148);
            U64_delete(_t146, &(Bool){1});
            Bool_delete(_t148, &(Bool){1});
        }
        Bool_delete(_t152, &(Bool){1});
        U64 *_t153 = malloc(sizeof(U64)); *_t153 = U64_mul(DEREF(lo), self->val_size);
        void *_t154 = ptr_add(self->val_data, DEREF(_t153));
        memcpy(_t154, val, self->val_size);
        U64_delete(_t153, &(Bool){1});
        free(val);
    } else {
        Bool *_t161 = malloc(sizeof(Bool)); *_t161 = U64_eq(self->count, self->cap);
        if (DEREF(_t161)) {
            I64 *_t155 = malloc(sizeof(I64));
            *_t155 = 2;
            U64 *new_cap = malloc(sizeof(U64)); *new_cap = U64_mul(self->cap, DEREF(_t155));
            I64_delete(_t155, &(Bool){1});
            U64 *_t156 = malloc(sizeof(U64)); *_t156 = U64_mul(DEREF(new_cap), self->key_size);
            void *_t157 = realloc(self->key_data, DEREF(_t156));
            U64_delete(_t156, &(Bool){1});
            self->key_data = _t157;
            U64 *_t158 = malloc(sizeof(U64)); *_t158 = U64_mul(DEREF(new_cap), self->val_size);
            void *_t159 = realloc(self->val_data, DEREF(_t158));
            U64_delete(_t158, &(Bool){1});
            self->val_data = _t159;
            U64 *_t160 = U64_clone(new_cap);
            U64_delete(new_cap, &(Bool){1});
            self->cap = DEREF(_t160);
            U64_delete(_t160, &(Bool){1});
        }
        Bool_delete(_t161, &(Bool){1});
        I64 *_t162 = malloc(sizeof(I64));
        *_t162 = 1;
        U64 *_t163 = malloc(sizeof(U64)); *_t163 = U64_add(DEREF(lo), DEREF(_t162));
        I64_delete(_t162, &(Bool){1});
        U64 *_t164 = malloc(sizeof(U64)); *_t164 = U64_mul(DEREF(_t163), self->key_size);
        U64_delete(_t163, &(Bool){1});
        U64 *_t165 = malloc(sizeof(U64)); *_t165 = U64_mul(DEREF(lo), self->key_size);
        U64 *_t166 = malloc(sizeof(U64)); *_t166 = U64_sub(self->count, DEREF(lo));
        void *_t167 = ptr_add(self->key_data, DEREF(_t164));
        void *_t168 = ptr_add(self->key_data, DEREF(_t165));
        U64 *_t169 = malloc(sizeof(U64)); *_t169 = U64_mul(DEREF(_t166), self->key_size);
        U64_delete(_t166, &(Bool){1});
        memmove(_t167, _t168, DEREF(_t169));
        U64_delete(_t164, &(Bool){1});
        U64_delete(_t165, &(Bool){1});
        U64_delete(_t169, &(Bool){1});
        I64 *_t170 = malloc(sizeof(I64));
        *_t170 = 1;
        U64 *_t171 = malloc(sizeof(U64)); *_t171 = U64_add(DEREF(lo), DEREF(_t170));
        I64_delete(_t170, &(Bool){1});
        U64 *_t172 = malloc(sizeof(U64)); *_t172 = U64_mul(DEREF(_t171), self->val_size);
        U64_delete(_t171, &(Bool){1});
        U64 *_t173 = malloc(sizeof(U64)); *_t173 = U64_mul(DEREF(lo), self->val_size);
        U64 *_t174 = malloc(sizeof(U64)); *_t174 = U64_sub(self->count, DEREF(lo));
        void *_t175 = ptr_add(self->val_data, DEREF(_t172));
        void *_t176 = ptr_add(self->val_data, DEREF(_t173));
        U64 *_t177 = malloc(sizeof(U64)); *_t177 = U64_mul(DEREF(_t174), self->val_size);
        U64_delete(_t174, &(Bool){1});
        memmove(_t175, _t176, DEREF(_t177));
        U64_delete(_t172, &(Bool){1});
        U64_delete(_t173, &(Bool){1});
        U64_delete(_t177, &(Bool){1});
        U64 *_t178 = malloc(sizeof(U64)); *_t178 = U64_mul(DEREF(lo), self->key_size);
        void *_t179 = ptr_add(self->key_data, DEREF(_t178));
        memcpy(_t179, key, self->key_size);
        U64_delete(_t178, &(Bool){1});
        U64 *_t180 = malloc(sizeof(U64)); *_t180 = U64_mul(DEREF(lo), self->val_size);
        void *_t181 = ptr_add(self->val_data, DEREF(_t180));
        memcpy(_t181, val, self->val_size);
        U64_delete(_t180, &(Bool){1});
        free(key);
        free(val);
        I64 *_t182 = malloc(sizeof(I64));
        *_t182 = 1;
        U64 *_t183 = malloc(sizeof(U64)); *_t183 = U64_add(self->count, DEREF(_t182));
        I64_delete(_t182, &(Bool){1});
        self->count = DEREF(_t183);
        U64_delete(_t183, &(Bool){1});
    }
    Bool_delete(found, &(Bool){1});
    U64_delete(lo, &(Bool){1});
}

void Map_delete(Map * self, Bool * call_free) {
    Bool *_t210 = Str_is_empty(&self->key_type);
    Bool *_t211 = malloc(sizeof(Bool)); *_t211 = Bool_not(DEREF(_t210));
    Bool_delete(_t210, &(Bool){1});
    if (DEREF(_t211)) {
        {
            U64 *_fi184 = malloc(sizeof(U64));
            *_fi184 = 0;
            while (1) {
                I64 *_t186 = malloc(sizeof(I64));
                *_t186 = 0;
                Range *_t187 = Range_new(DEREF(_t186), self->count);
                I64_delete(_t186, &(Bool){1});
                U64 *_t188 = Range_len(_t187);
                Range_delete(_t187, &(Bool){1});
                Bool *_wcond185 = U64_lt(_fi184, _t188);
                U64_delete(_t188, &(Bool){1});
                if (DEREF(_wcond185)) {
                } else {
                    Bool_delete(_wcond185, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond185, &(Bool){1});
                I64 *_t189 = malloc(sizeof(I64));
                *_t189 = 0;
                Range *_t190 = Range_new(DEREF(_t189), self->count);
                I64_delete(_t189, &(Bool){1});
                U64 *i = Range_get(_t190, DEREF(_fi184));
                Range_delete(_t190, &(Bool){1});
                I64 *_t191 = malloc(sizeof(I64));
                *_t191 = 1;
                U64 *_t192 = malloc(sizeof(U64)); *_t192 = U64_add(DEREF(_fi184), DEREF(_t191));
                I64_delete(_t191, &(Bool){1});
                *_fi184 = DEREF(_t192);
                U64_delete(_t192, &(Bool){1});
                U64 *_t193 = malloc(sizeof(U64)); *_t193 = U64_mul(DEREF(i), self->key_size);
                U64_delete(i, &(Bool){1});
                void *_t194 = ptr_add(self->key_data, DEREF(_t193));
                Bool *_t195 = malloc(sizeof(Bool));
                *_t195 = 0;
                dyn_call_delete(&self->key_type, _t194, _t195);
                U64_delete(_t193, &(Bool){1});
                Bool_delete(_t195, &(Bool){1});
            }
            U64_delete(_fi184, &(Bool){1});
        }
    }
    Bool_delete(_t211, &(Bool){1});
    Bool *_t212 = Str_is_empty(&self->val_type);
    Bool *_t213 = malloc(sizeof(Bool)); *_t213 = Bool_not(DEREF(_t212));
    Bool_delete(_t212, &(Bool){1});
    if (DEREF(_t213)) {
        {
            U64 *_fi196 = malloc(sizeof(U64));
            *_fi196 = 0;
            while (1) {
                I64 *_t198 = malloc(sizeof(I64));
                *_t198 = 0;
                Range *_t199 = Range_new(DEREF(_t198), self->count);
                I64_delete(_t198, &(Bool){1});
                U64 *_t200 = Range_len(_t199);
                Range_delete(_t199, &(Bool){1});
                Bool *_wcond197 = U64_lt(_fi196, _t200);
                U64_delete(_t200, &(Bool){1});
                if (DEREF(_wcond197)) {
                } else {
                    Bool_delete(_wcond197, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond197, &(Bool){1});
                I64 *_t201 = malloc(sizeof(I64));
                *_t201 = 0;
                Range *_t202 = Range_new(DEREF(_t201), self->count);
                I64_delete(_t201, &(Bool){1});
                U64 *i = Range_get(_t202, DEREF(_fi196));
                Range_delete(_t202, &(Bool){1});
                I64 *_t203 = malloc(sizeof(I64));
                *_t203 = 1;
                U64 *_t204 = malloc(sizeof(U64)); *_t204 = U64_add(DEREF(_fi196), DEREF(_t203));
                I64_delete(_t203, &(Bool){1});
                *_fi196 = DEREF(_t204);
                U64_delete(_t204, &(Bool){1});
                U64 *_t205 = malloc(sizeof(U64)); *_t205 = U64_mul(DEREF(i), self->val_size);
                U64_delete(i, &(Bool){1});
                void *_t206 = ptr_add(self->val_data, DEREF(_t205));
                Bool *_t207 = malloc(sizeof(Bool));
                *_t207 = 0;
                dyn_call_delete(&self->val_type, _t206, _t207);
                U64_delete(_t205, &(Bool){1});
                Bool_delete(_t207, &(Bool){1});
            }
            U64_delete(_fi196, &(Bool){1});
        }
    }
    Bool_delete(_t213, &(Bool){1});
    free(self->key_data);
    free(self->val_data);
    Bool *_t214 = Str_is_empty(&self->key_type);
    Bool *_t215 = malloc(sizeof(Bool)); *_t215 = Bool_not(DEREF(_t214));
    Bool_delete(_t214, &(Bool){1});
    if (DEREF(_t215)) {
        Bool *_t208 = malloc(sizeof(Bool));
        *_t208 = 0;
        Str_delete(&self->key_type, _t208);
        Bool_delete(_t208, &(Bool){1});
    }
    Bool_delete(_t215, &(Bool){1});
    Bool *_t216 = Str_is_empty(&self->val_type);
    Bool *_t217 = malloc(sizeof(Bool)); *_t217 = Bool_not(DEREF(_t216));
    Bool_delete(_t216, &(Bool){1});
    if (DEREF(_t217)) {
        Bool *_t209 = malloc(sizeof(Bool));
        *_t209 = 0;
        Str_delete(&self->val_type, _t209);
        Bool_delete(_t209, &(Bool){1});
    }
    Bool_delete(_t217, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    U64 *_t235 = malloc(sizeof(U64)); *_t235 = U64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(DEREF(_t235));
    U64_delete(_t235, &(Bool){1});
    U64 *_t236 = malloc(sizeof(U64)); *_t236 = U64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(DEREF(_t236));
    U64_delete(_t236, &(Bool){1});
    {
        U64 *_fi218 = malloc(sizeof(U64));
        *_fi218 = 0;
        while (1) {
            I64 *_t220 = malloc(sizeof(I64));
            *_t220 = 0;
            Range *_t221 = Range_new(DEREF(_t220), self->count);
            I64_delete(_t220, &(Bool){1});
            U64 *_t222 = Range_len(_t221);
            Range_delete(_t221, &(Bool){1});
            Bool *_wcond219 = U64_lt(_fi218, _t222);
            U64_delete(_t222, &(Bool){1});
            if (DEREF(_wcond219)) {
            } else {
                Bool_delete(_wcond219, &(Bool){1});
                break;
            }
            Bool_delete(_wcond219, &(Bool){1});
            I64 *_t223 = malloc(sizeof(I64));
            *_t223 = 0;
            Range *_t224 = Range_new(DEREF(_t223), self->count);
            I64_delete(_t223, &(Bool){1});
            U64 *i = Range_get(_t224, DEREF(_fi218));
            Range_delete(_t224, &(Bool){1});
            I64 *_t225 = malloc(sizeof(I64));
            *_t225 = 1;
            U64 *_t226 = malloc(sizeof(U64)); *_t226 = U64_add(DEREF(_fi218), DEREF(_t225));
            I64_delete(_t225, &(Bool){1});
            *_fi218 = DEREF(_t226);
            U64_delete(_t226, &(Bool){1});
            U64 *_t227 = malloc(sizeof(U64)); *_t227 = U64_mul(DEREF(i), self->key_size);
            void *_t228 = ptr_add(self->key_data, DEREF(_t227));
            void *ck = dyn_call_clone(&self->key_type, _t228);
            U64_delete(_t227, &(Bool){1});
            U64 *_t229 = malloc(sizeof(U64)); *_t229 = U64_mul(DEREF(i), self->key_size);
            void *_t230 = ptr_add(new_keys, DEREF(_t229));
            memcpy(_t230, ck, self->key_size);
            U64_delete(_t229, &(Bool){1});
            free(ck);
            U64 *_t231 = malloc(sizeof(U64)); *_t231 = U64_mul(DEREF(i), self->val_size);
            void *_t232 = ptr_add(self->val_data, DEREF(_t231));
            void *cv = dyn_call_clone(&self->val_type, _t232);
            U64_delete(_t231, &(Bool){1});
            U64 *_t233 = malloc(sizeof(U64)); *_t233 = U64_mul(DEREF(i), self->val_size);
            U64_delete(i, &(Bool){1});
            void *_t234 = ptr_add(new_vals, DEREF(_t233));
            memcpy(_t234, cv, self->val_size);
            U64_delete(_t233, &(Bool){1});
            free(cv);
        }
        U64_delete(_fi218, &(Bool){1});
    }
    Map *_t237 = malloc(sizeof(Map));
    _t237->key_data = new_keys;
    _t237->val_data = new_vals;
    _t237->count = self->count;
    _t237->cap = self->cap;
    _t237->key_size = self->key_size;
    { Str *_ca = Str_clone(&self->key_type); _t237->key_type = *_ca; free(_ca); }
    _t237->val_size = self->val_size;
    { Str *_ca = Str_clone(&self->val_type); _t237->val_type = *_ca; free(_ca); }
    return _t237;
}

U64 *Map_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Map);
    return r;
}

Set * Set_new(Str * elem_type, U64 * elem_size) {
    Bool *_t251 = Str_is_empty(elem_type);
    Bool *_t252 = malloc(sizeof(Bool)); *_t252 = Bool_not(DEREF(_t251));
    Bool_delete(_t251, &(Bool){1});
    if (DEREF(_t252)) {
        Bool *_t249 = dyn_has_cmp(elem_type);
        Bool *_t250 = malloc(sizeof(Bool)); *_t250 = Bool_not(DEREF(_t249));
        Bool_delete(_t249, &(Bool){1});
        if (DEREF(_t250)) {
            Str *_t239 = Str_lit("Str", 3ULL);
            U64 *_t240 = Str_size();
            U64 *_t241 = malloc(sizeof(U64));
            *_t241 = 3;
            Array *_va4 = Array_new(_t239, _t240, _t241);
            Str_delete(_t239, &(Bool){1});
            U64_delete(_t240, &(Bool){1});
            U64_delete(_t241, &(Bool){1});
            U64 *_t242 = malloc(sizeof(U64));
            *_t242 = 0;
            Str *_t243 = Str_lit("type ", 5ULL);
            Array_set(_va4, _t242, _t243);
            U64_delete(_t242, &(Bool){1});
            U64 *_t244 = malloc(sizeof(U64));
            *_t244 = 1;
            Str *_t245 = Str_clone(elem_type);
            Array_set(_va4, _t244, _t245);
            U64_delete(_t244, &(Bool){1});
            U64 *_t246 = malloc(sizeof(U64));
            *_t246 = 2;
            Str *_t247 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va4, _t246, _t247);
            U64_delete(_t246, &(Bool){1});
            Str *_t248 = Str_lit("Set.new", 7ULL);
            panic(_t248, _va4);
            Str_delete(_t248, &(Bool){1});
            Array_delete(_va4, &(Bool){1});
        }
        Bool_delete(_t250, &(Bool){1});
    }
    Bool_delete(_t252, &(Bool){1});
    void *_t253 = malloc(DEREF(elem_size));
    U64 *_t254 = malloc(sizeof(U64));
    *_t254 = 0;
    I64 *_t255 = malloc(sizeof(I64));
    *_t255 = 1;
    U64 *_t256 = U64_clone(elem_size);
    Set *_t257 = malloc(sizeof(Set));
    _t257->data = _t253;
    _t257->count = DEREF(_t254);
    _t257->cap = DEREF(_t255);
    _t257->elem_size = DEREF(_t256);
    { Str *_ca = Str_clone(elem_type); _t257->elem_type = *_ca; free(_ca); }
    U64_delete(_t254, &(Bool){1});
    I64_delete(_t255, &(Bool){1});
    U64_delete(_t256, &(Bool){1});
    return _t257;
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
        Bool *_wcond258 = U64_lt(lo, hi);
        if (DEREF(_wcond258)) {
        } else {
            Bool_delete(_wcond258, &(Bool){1});
            break;
        }
        Bool_delete(_wcond258, &(Bool){1});
        U64 *_t265 = malloc(sizeof(U64)); *_t265 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t266 = malloc(sizeof(I64));
        *_t266 = 2;
        U64 *_t267 = malloc(sizeof(U64)); *_t267 = U64_div(DEREF(_t265), DEREF(_t266));
        U64_delete(_t265, &(Bool){1});
        I64_delete(_t266, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t267));
        U64_delete(_t267, &(Bool){1});
        U64 *_t268 = malloc(sizeof(U64)); *_t268 = U64_mul(DEREF(mid), self->elem_size);
        void *_t269 = ptr_add(self->data, DEREF(_t268));
        I64 *c = dyn_call_cmp(&self->elem_type, _t269, val);
        U64_delete(_t268, &(Bool){1});
        I64 *_t270 = malloc(sizeof(I64));
        *_t270 = 0;
        Bool *_t271 = I64_lt(c, _t270);
        I64_delete(_t270, &(Bool){1});
        if (DEREF(_t271)) {
            I64 *_t259 = malloc(sizeof(I64));
            *_t259 = 1;
            U64 *_t260 = malloc(sizeof(U64)); *_t260 = U64_add(DEREF(mid), DEREF(_t259));
            I64_delete(_t259, &(Bool){1});
            *lo = DEREF(_t260);
            U64_delete(_t260, &(Bool){1});
        } else {
            I64 *_t263 = malloc(sizeof(I64));
            *_t263 = 0;
            Bool *_t264 = I64_gt(c, _t263);
            I64_delete(_t263, &(Bool){1});
            if (DEREF(_t264)) {
                U64 *_t261 = U64_clone(mid);
                *hi = DEREF(_t261);
                U64_delete(_t261, &(Bool){1});
            } else {
                Bool *_t262 = malloc(sizeof(Bool));
                *_t262 = 1;
                Bool_delete(_t264, &(Bool){1});
                Bool_delete(_t271, &(Bool){1});
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                U64_delete(hi, &(Bool){1});
                U64_delete(lo, &(Bool){1});
                return _t262;
            }
            Bool_delete(_t264, &(Bool){1});
        }
        Bool_delete(_t271, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    U64_delete(lo, &(Bool){1});
    Bool *_t272 = malloc(sizeof(Bool));
    *_t272 = 0;
    return _t272;
}

void Set_add(Set * self, void * val) {
    U64 *lo = malloc(sizeof(U64));
    *lo = 0;
    U64 *hi = malloc(sizeof(U64));
    *hi = self->count;
    Bool *found = malloc(sizeof(Bool));
    *found = 0;
    while (1) {
        Bool *_wcond273 = U64_lt(lo, hi);
        if (DEREF(_wcond273)) {
        } else {
            Bool_delete(_wcond273, &(Bool){1});
            break;
        }
        Bool_delete(_wcond273, &(Bool){1});
        U64 *_t282 = malloc(sizeof(U64)); *_t282 = U64_sub(DEREF(hi), DEREF(lo));
        I64 *_t283 = malloc(sizeof(I64));
        *_t283 = 2;
        U64 *_t284 = malloc(sizeof(U64)); *_t284 = U64_div(DEREF(_t282), DEREF(_t283));
        U64_delete(_t282, &(Bool){1});
        I64_delete(_t283, &(Bool){1});
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(DEREF(lo), DEREF(_t284));
        U64_delete(_t284, &(Bool){1});
        U64 *_t285 = malloc(sizeof(U64)); *_t285 = U64_mul(DEREF(mid), self->elem_size);
        void *_t286 = ptr_add(self->data, DEREF(_t285));
        I64 *c = dyn_call_cmp(&self->elem_type, _t286, val);
        U64_delete(_t285, &(Bool){1});
        I64 *_t287 = malloc(sizeof(I64));
        *_t287 = 0;
        Bool *_t288 = I64_lt(c, _t287);
        I64_delete(_t287, &(Bool){1});
        if (DEREF(_t288)) {
            I64 *_t274 = malloc(sizeof(I64));
            *_t274 = 1;
            U64 *_t275 = malloc(sizeof(U64)); *_t275 = U64_add(DEREF(mid), DEREF(_t274));
            I64_delete(_t274, &(Bool){1});
            *lo = DEREF(_t275);
            U64_delete(_t275, &(Bool){1});
        } else {
            I64 *_t280 = malloc(sizeof(I64));
            *_t280 = 0;
            Bool *_t281 = I64_gt(c, _t280);
            I64_delete(_t280, &(Bool){1});
            if (DEREF(_t281)) {
                U64 *_t276 = U64_clone(mid);
                *hi = DEREF(_t276);
                U64_delete(_t276, &(Bool){1});
            } else {
                Bool *_t277 = malloc(sizeof(Bool));
                *_t277 = 1;
                *found = DEREF(_t277);
                Bool_delete(_t277, &(Bool){1});
                U64 *_t278 = U64_clone(mid);
                *lo = DEREF(_t278);
                U64_delete(_t278, &(Bool){1});
                U64 *_t279 = U64_clone(mid);
                *hi = DEREF(_t279);
                U64_delete(_t279, &(Bool){1});
            }
            Bool_delete(_t281, &(Bool){1});
        }
        Bool_delete(_t288, &(Bool){1});
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    U64_delete(hi, &(Bool){1});
    if (DEREF(found)) {
        Bool *_t290 = Str_is_empty(&self->elem_type);
        Bool *_t291 = malloc(sizeof(Bool)); *_t291 = Bool_not(DEREF(_t290));
        Bool_delete(_t290, &(Bool){1});
        if (DEREF(_t291)) {
            Bool *_t289 = malloc(sizeof(Bool));
            *_t289 = 0;
            dyn_call_delete(&self->elem_type, val, _t289);
            Bool_delete(_t289, &(Bool){1});
        }
        Bool_delete(_t291, &(Bool){1});
        free(val);
    } else {
        Bool *_t296 = malloc(sizeof(Bool)); *_t296 = U64_eq(self->count, self->cap);
        if (DEREF(_t296)) {
            I64 *_t292 = malloc(sizeof(I64));
            *_t292 = 2;
            U64 *new_cap = malloc(sizeof(U64)); *new_cap = U64_mul(self->cap, DEREF(_t292));
            I64_delete(_t292, &(Bool){1});
            U64 *_t293 = malloc(sizeof(U64)); *_t293 = U64_mul(DEREF(new_cap), self->elem_size);
            void *_t294 = realloc(self->data, DEREF(_t293));
            U64_delete(_t293, &(Bool){1});
            self->data = _t294;
            U64 *_t295 = U64_clone(new_cap);
            U64_delete(new_cap, &(Bool){1});
            self->cap = DEREF(_t295);
            U64_delete(_t295, &(Bool){1});
        }
        Bool_delete(_t296, &(Bool){1});
        I64 *_t297 = malloc(sizeof(I64));
        *_t297 = 1;
        U64 *_t298 = malloc(sizeof(U64)); *_t298 = U64_add(DEREF(lo), DEREF(_t297));
        I64_delete(_t297, &(Bool){1});
        U64 *_t299 = malloc(sizeof(U64)); *_t299 = U64_mul(DEREF(_t298), self->elem_size);
        U64_delete(_t298, &(Bool){1});
        U64 *_t300 = malloc(sizeof(U64)); *_t300 = U64_mul(DEREF(lo), self->elem_size);
        U64 *_t301 = malloc(sizeof(U64)); *_t301 = U64_sub(self->count, DEREF(lo));
        void *_t302 = ptr_add(self->data, DEREF(_t299));
        void *_t303 = ptr_add(self->data, DEREF(_t300));
        U64 *_t304 = malloc(sizeof(U64)); *_t304 = U64_mul(DEREF(_t301), self->elem_size);
        U64_delete(_t301, &(Bool){1});
        memmove(_t302, _t303, DEREF(_t304));
        U64_delete(_t299, &(Bool){1});
        U64_delete(_t300, &(Bool){1});
        U64_delete(_t304, &(Bool){1});
        U64 *_t305 = malloc(sizeof(U64)); *_t305 = U64_mul(DEREF(lo), self->elem_size);
        void *_t306 = ptr_add(self->data, DEREF(_t305));
        memcpy(_t306, val, self->elem_size);
        U64_delete(_t305, &(Bool){1});
        free(val);
        I64 *_t307 = malloc(sizeof(I64));
        *_t307 = 1;
        U64 *_t308 = malloc(sizeof(U64)); *_t308 = U64_add(self->count, DEREF(_t307));
        I64_delete(_t307, &(Bool){1});
        self->count = DEREF(_t308);
        U64_delete(_t308, &(Bool){1});
    }
    Bool_delete(found, &(Bool){1});
    U64_delete(lo, &(Bool){1});
}

void Set_delete(Set * self, Bool * call_free) {
    Bool *_t322 = Str_is_empty(&self->elem_type);
    Bool *_t323 = malloc(sizeof(Bool)); *_t323 = Bool_not(DEREF(_t322));
    Bool_delete(_t322, &(Bool){1});
    if (DEREF(_t323)) {
        {
            U64 *_fi309 = malloc(sizeof(U64));
            *_fi309 = 0;
            while (1) {
                I64 *_t311 = malloc(sizeof(I64));
                *_t311 = 0;
                Range *_t312 = Range_new(DEREF(_t311), self->count);
                I64_delete(_t311, &(Bool){1});
                U64 *_t313 = Range_len(_t312);
                Range_delete(_t312, &(Bool){1});
                Bool *_wcond310 = U64_lt(_fi309, _t313);
                U64_delete(_t313, &(Bool){1});
                if (DEREF(_wcond310)) {
                } else {
                    Bool_delete(_wcond310, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond310, &(Bool){1});
                I64 *_t314 = malloc(sizeof(I64));
                *_t314 = 0;
                Range *_t315 = Range_new(DEREF(_t314), self->count);
                I64_delete(_t314, &(Bool){1});
                U64 *i = Range_get(_t315, DEREF(_fi309));
                Range_delete(_t315, &(Bool){1});
                I64 *_t316 = malloc(sizeof(I64));
                *_t316 = 1;
                U64 *_t317 = malloc(sizeof(U64)); *_t317 = U64_add(DEREF(_fi309), DEREF(_t316));
                I64_delete(_t316, &(Bool){1});
                *_fi309 = DEREF(_t317);
                U64_delete(_t317, &(Bool){1});
                U64 *_t318 = malloc(sizeof(U64)); *_t318 = U64_mul(DEREF(i), self->elem_size);
                U64_delete(i, &(Bool){1});
                void *_t319 = ptr_add(self->data, DEREF(_t318));
                Bool *_t320 = malloc(sizeof(Bool));
                *_t320 = 0;
                dyn_call_delete(&self->elem_type, _t319, _t320);
                U64_delete(_t318, &(Bool){1});
                Bool_delete(_t320, &(Bool){1});
            }
            U64_delete(_fi309, &(Bool){1});
        }
    }
    Bool_delete(_t323, &(Bool){1});
    free(self->data);
    Bool *_t324 = Str_is_empty(&self->elem_type);
    Bool *_t325 = malloc(sizeof(Bool)); *_t325 = Bool_not(DEREF(_t324));
    Bool_delete(_t324, &(Bool){1});
    if (DEREF(_t325)) {
        Bool *_t321 = malloc(sizeof(Bool));
        *_t321 = 0;
        Str_delete(&self->elem_type, _t321);
        Bool_delete(_t321, &(Bool){1});
    }
    Bool_delete(_t325, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    U64 *_t339 = malloc(sizeof(U64)); *_t339 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t339));
    U64_delete(_t339, &(Bool){1});
    {
        U64 *_fi326 = malloc(sizeof(U64));
        *_fi326 = 0;
        while (1) {
            I64 *_t328 = malloc(sizeof(I64));
            *_t328 = 0;
            Range *_t329 = Range_new(DEREF(_t328), self->count);
            I64_delete(_t328, &(Bool){1});
            U64 *_t330 = Range_len(_t329);
            Range_delete(_t329, &(Bool){1});
            Bool *_wcond327 = U64_lt(_fi326, _t330);
            U64_delete(_t330, &(Bool){1});
            if (DEREF(_wcond327)) {
            } else {
                Bool_delete(_wcond327, &(Bool){1});
                break;
            }
            Bool_delete(_wcond327, &(Bool){1});
            I64 *_t331 = malloc(sizeof(I64));
            *_t331 = 0;
            Range *_t332 = Range_new(DEREF(_t331), self->count);
            I64_delete(_t331, &(Bool){1});
            U64 *i = Range_get(_t332, DEREF(_fi326));
            Range_delete(_t332, &(Bool){1});
            I64 *_t333 = malloc(sizeof(I64));
            *_t333 = 1;
            U64 *_t334 = malloc(sizeof(U64)); *_t334 = U64_add(DEREF(_fi326), DEREF(_t333));
            I64_delete(_t333, &(Bool){1});
            *_fi326 = DEREF(_t334);
            U64_delete(_t334, &(Bool){1});
            U64 *_t335 = malloc(sizeof(U64)); *_t335 = U64_mul(DEREF(i), self->elem_size);
            void *_t336 = ptr_add(self->data, DEREF(_t335));
            void *cloned = dyn_call_clone(&self->elem_type, _t336);
            U64_delete(_t335, &(Bool){1});
            U64 *_t337 = malloc(sizeof(U64)); *_t337 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t338 = ptr_add(new_data, DEREF(_t337));
            memcpy(_t338, cloned, self->elem_size);
            U64_delete(_t337, &(Bool){1});
            free(cloned);
        }
        U64_delete(_fi326, &(Bool){1});
    }
    Set *_t340 = malloc(sizeof(Set));
    _t340->data = new_data;
    _t340->count = self->count;
    _t340->cap = self->cap;
    _t340->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t340->elem_type = *_ca; free(_ca); }
    return _t340;
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
    Bool *_t348 = U64_gte(i, &self->count);
    if (DEREF(_t348)) {
        Str *_t342 = Str_lit("Str", 3ULL);
        U64 *_t343 = Str_size();
        U64 *_t344 = malloc(sizeof(U64));
        *_t344 = 1;
        Array *_va5 = Array_new(_t342, _t343, _t344);
        Str_delete(_t342, &(Bool){1});
        U64_delete(_t343, &(Bool){1});
        U64_delete(_t344, &(Bool){1});
        U64 *_t345 = malloc(sizeof(U64));
        *_t345 = 0;
        Str *_t346 = Str_lit("index out of bounds", 19ULL);
        Array_set(_va5, _t345, _t346);
        U64_delete(_t345, &(Bool){1});
        Str *_t347 = Str_lit("Str.get", 7ULL);
        panic(_t347, _va5);
        Str_delete(_t347, &(Bool){1});
        Array_delete(_va5, &(Bool){1});
    }
    Bool_delete(_t348, &(Bool){1});
    void *_t349 = ptr_add(self->c_str, DEREF(i));
    return _t349;
}

I64 * Str_cmp(Str * a, Str * b) {
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    U64 *min_len = malloc(sizeof(U64));
    *min_len = a->count;
    Bool *_t355 = U64_lt(&b->count, &a->count);
    if (DEREF(_t355)) {
        *min_len = b->count;
    }
    Bool_delete(_t355, &(Bool){1});
    while (1) {
        Bool *_wcond350 = U64_lt(i, min_len);
        if (DEREF(_wcond350)) {
        } else {
            Bool_delete(_wcond350, &(Bool){1});
            break;
        }
        Bool_delete(_wcond350, &(Bool){1});
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 *_t351 = malloc(sizeof(I64));
        *_t351 = 0;
        Bool *_t352 = I64_neq(c, _t351);
        I64_delete(_t351, &(Bool){1});
        if (DEREF(_t352)) {
            Bool_delete(_t352, &(Bool){1});
            U64_delete(i, &(Bool){1});
            U64_delete(min_len, &(Bool){1});
            return c;
        }
        Bool_delete(_t352, &(Bool){1});
        I64_delete(c, &(Bool){1});
        I64 *_t353 = malloc(sizeof(I64));
        *_t353 = 1;
        U64 *_t354 = malloc(sizeof(U64)); *_t354 = U64_add(DEREF(i), DEREF(_t353));
        I64_delete(_t353, &(Bool){1});
        *i = DEREF(_t354);
        U64_delete(_t354, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    U64_delete(min_len, &(Bool){1});
    I64 *_t356 = malloc(sizeof(I64)); *_t356 = U64_cmp(a->count, b->count);
    return _t356;
}

Str * Str_concat(Str * a, Str * b) {
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    I64 *_t357 = malloc(sizeof(I64));
    *_t357 = 1;
    U64 *_t358 = malloc(sizeof(U64)); *_t358 = U64_add(DEREF(new_len), DEREF(_t357));
    I64_delete(_t357, &(Bool){1});
    U8 *new_data = malloc(DEREF(_t358));
    U64_delete(_t358, &(Bool){1});
    memcpy(new_data, a->c_str, a->count);
    void *_t359 = ptr_add(new_data, a->count);
    memcpy(_t359, b->c_str, b->count);
    I64 *_t360 = malloc(sizeof(I64));
    *_t360 = 0;
    void *_t361 = ptr_add(new_data, DEREF(new_len));
    U8 *_t362 = U8_from_i64(_t360);
    I64_delete(_t360, &(Bool){1});
    I64 *_t363 = malloc(sizeof(I64));
    *_t363 = 1;
    memcpy(_t361, _t362, DEREF(_t363));
    U8_delete(_t362, &(Bool){1});
    I64_delete(_t363, &(Bool){1});
    U64 *_t364 = U64_clone(new_len);
    U64 *_t365 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t366 = malloc(sizeof(Str));
    _t366->c_str = new_data;
    _t366->count = DEREF(_t364);
    _t366->cap = DEREF(_t365);
    U64_delete(_t364, &(Bool){1});
    U64_delete(_t365, &(Bool){1});
    return _t366;
}

Str * Str_with_capacity(U64 * n) {
    I64 *_t367 = malloc(sizeof(I64));
    *_t367 = 1;
    U64 *_t368 = malloc(sizeof(U64)); *_t368 = U64_add(DEREF(n), DEREF(_t367));
    I64_delete(_t367, &(Bool){1});
    U8 *buf = malloc(DEREF(_t368));
    U64_delete(_t368, &(Bool){1});
    I64 *_t369 = malloc(sizeof(I64));
    *_t369 = 0;
    U8 *_t370 = U8_from_i64(_t369);
    I64_delete(_t369, &(Bool){1});
    I64 *_t371 = malloc(sizeof(I64));
    *_t371 = 1;
    memcpy(buf, _t370, DEREF(_t371));
    U8_delete(_t370, &(Bool){1});
    I64_delete(_t371, &(Bool){1});
    I64 *_t372 = malloc(sizeof(I64));
    *_t372 = 0;
    U64 *_t373 = U64_clone(n);
    Str *_t374 = malloc(sizeof(Str));
    _t374->c_str = buf;
    _t374->count = DEREF(_t372);
    _t374->cap = DEREF(_t373);
    I64_delete(_t372, &(Bool){1});
    U64_delete(_t373, &(Bool){1});
    return _t374;
}

void Str_push_str(Str * self, Str * s) {
    Bool *_t387 = U64_gte(&self->cap, CAP_VIEW);
    if (DEREF(_t387)) {
        Str *_t375 = Str_lit("Str", 3ULL);
        U64 *_t376 = Str_size();
        U64 *_t377 = malloc(sizeof(U64));
        *_t377 = 1;
        Array *_va6 = Array_new(_t375, _t376, _t377);
        Str_delete(_t375, &(Bool){1});
        U64_delete(_t376, &(Bool){1});
        U64_delete(_t377, &(Bool){1});
        U64 *_t378 = malloc(sizeof(U64));
        *_t378 = 0;
        Str *_t379 = Str_lit("cannot mutate a string view or literal", 38ULL);
        Array_set(_va6, _t378, _t379);
        U64_delete(_t378, &(Bool){1});
        Str *_t380 = Str_lit("Str.push_str", 12ULL);
        panic(_t380, _va6);
        Str_delete(_t380, &(Bool){1});
        Array_delete(_va6, &(Bool){1});
    }
    Bool_delete(_t387, &(Bool){1});
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool *_t388 = U64_gt(new_len, &self->cap);
    if (DEREF(_t388)) {
        Str *_t381 = Str_lit("Str", 3ULL);
        U64 *_t382 = Str_size();
        U64 *_t383 = malloc(sizeof(U64));
        *_t383 = 1;
        Array *_va7 = Array_new(_t381, _t382, _t383);
        Str_delete(_t381, &(Bool){1});
        U64_delete(_t382, &(Bool){1});
        U64_delete(_t383, &(Bool){1});
        U64 *_t384 = malloc(sizeof(U64));
        *_t384 = 0;
        Str *_t385 = Str_lit("capacity exceeded", 17ULL);
        Array_set(_va7, _t384, _t385);
        U64_delete(_t384, &(Bool){1});
        Str *_t386 = Str_lit("Str.push_str", 12ULL);
        panic(_t386, _va7);
        Str_delete(_t386, &(Bool){1});
        Array_delete(_va7, &(Bool){1});
    }
    Bool_delete(_t388, &(Bool){1});
    void *_t389 = ptr_add(self->c_str, self->count);
    memcpy(_t389, s->c_str, s->count);
    U64 *_t390 = U64_clone(new_len);
    self->count = DEREF(_t390);
    U64_delete(_t390, &(Bool){1});
    I64 *_t391 = malloc(sizeof(I64));
    *_t391 = 0;
    void *_t392 = ptr_add(self->c_str, DEREF(new_len));
    U8 *_t393 = U8_from_i64(_t391);
    I64_delete(_t391, &(Bool){1});
    I64 *_t394 = malloc(sizeof(I64));
    *_t394 = 1;
    memcpy(_t392, _t393, DEREF(_t394));
    U8_delete(_t393, &(Bool){1});
    I64_delete(_t394, &(Bool){1});
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    I64 *_t395 = malloc(sizeof(I64));
    *_t395 = 1;
    U64 *_t396 = malloc(sizeof(U64)); *_t396 = U64_add(val->count, DEREF(_t395));
    I64_delete(_t395, &(Bool){1});
    U8 *new_data = malloc(DEREF(_t396));
    U64_delete(_t396, &(Bool){1});
    memcpy(new_data, val->c_str, val->count);
    I64 *_t397 = malloc(sizeof(I64));
    *_t397 = 0;
    void *_t398 = ptr_add(new_data, val->count);
    U8 *_t399 = U8_from_i64(_t397);
    I64_delete(_t397, &(Bool){1});
    I64 *_t400 = malloc(sizeof(I64));
    *_t400 = 1;
    memcpy(_t398, _t399, DEREF(_t400));
    U8_delete(_t399, &(Bool){1});
    I64_delete(_t400, &(Bool){1});
    Str *_t401 = malloc(sizeof(Str));
    _t401->c_str = new_data;
    _t401->count = val->count;
    _t401->cap = val->count;
    return _t401;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool *_t402 = U64_lt(&self->cap, CAP_VIEW);
    if (DEREF(_t402)) {
        free(self->c_str);
    }
    Bool_delete(_t402, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t403 = Str_clone(val);
    return _t403;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = U64_clone(start);
    U64 *ln = U64_clone(n);
    Bool *_t405 = U64_gt(st, &s->count);
    if (DEREF(_t405)) {
        *st = s->count;
    }
    Bool_delete(_t405, &(Bool){1});
    U64 *_t406 = malloc(sizeof(U64)); *_t406 = U64_add(DEREF(st), DEREF(ln));
    Bool *_t407 = U64_gt(_t406, &s->count);
    U64_delete(_t406, &(Bool){1});
    if (DEREF(_t407)) {
        U64 *_t404 = malloc(sizeof(U64)); *_t404 = U64_sub(s->count, DEREF(st));
        *ln = DEREF(_t404);
        U64_delete(_t404, &(Bool){1});
    }
    Bool_delete(_t407, &(Bool){1});
    void *_t408 = ptr_add(s->c_str, DEREF(st));
    U64 *_t409 = U64_clone(ln);
    U64_delete(ln, &(Bool){1});
    U64 *_t410 = U64_clone(CAP_VIEW);
    Str *_t411 = malloc(sizeof(Str));
    _t411->c_str = _t408;
    _t411->count = DEREF(_t409);
    _t411->cap = DEREF(_t410);
    U64_delete(_t409, &(Bool){1});
    U64_delete(_t410, &(Bool){1});
    U64_delete(st, &(Bool){1});
    return _t411;
}

Bool * Str_contains(Str * a, Str * b) {
    I64 *_t425 = malloc(sizeof(I64));
    *_t425 = 0;
    Bool *_t426 = malloc(sizeof(Bool)); *_t426 = U64_eq(b->count, DEREF(_t425));
    I64_delete(_t425, &(Bool){1});
    if (DEREF(_t426)) {
        Bool *_t412 = malloc(sizeof(Bool));
        *_t412 = 1;
        Bool_delete(_t426, &(Bool){1});
        return _t412;
    }
    Bool_delete(_t426, &(Bool){1});
    Bool *_t427 = U64_gt(&b->count, &a->count);
    if (DEREF(_t427)) {
        Bool *_t413 = malloc(sizeof(Bool));
        *_t413 = 0;
        Bool_delete(_t427, &(Bool){1});
        return _t413;
    }
    Bool_delete(_t427, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t422 = malloc(sizeof(U64)); *_t422 = U64_sub(a->count, b->count);
        Bool *_wcond414 = U64_lte(i, _t422);
        U64_delete(_t422, &(Bool){1});
        if (DEREF(_wcond414)) {
        } else {
            Bool_delete(_wcond414, &(Bool){1});
            break;
        }
        Bool_delete(_wcond414, &(Bool){1});
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond415 = U64_lt(j, &b->count);
            if (DEREF(_wcond415)) {
            } else {
                Bool_delete(_wcond415, &(Bool){1});
                break;
            }
            Bool_delete(_wcond415, &(Bool){1});
            U64 *_t417 = malloc(sizeof(U64)); *_t417 = U64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(a, _t417);
            U8 *bc = Str_get(b, j);
            Bool *_t418 = U8_neq(ac, bc);
            U64_delete(_t417, &(Bool){1});
            if (DEREF(_t418)) {
                Bool *_t416 = malloc(sizeof(Bool));
                *_t416 = 0;
                *found = DEREF(_t416);
                Bool_delete(_t416, &(Bool){1});
            }
            Bool_delete(_t418, &(Bool){1});
            I64 *_t419 = malloc(sizeof(I64));
            *_t419 = 1;
            U64 *_t420 = malloc(sizeof(U64)); *_t420 = U64_add(DEREF(j), DEREF(_t419));
            I64_delete(_t419, &(Bool){1});
            *j = DEREF(_t420);
            U64_delete(_t420, &(Bool){1});
        }
        U64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            Bool *_t421 = malloc(sizeof(Bool));
            *_t421 = 1;
            Bool_delete(found, &(Bool){1});
            U64_delete(i, &(Bool){1});
            return _t421;
        }
        Bool_delete(found, &(Bool){1});
        I64 *_t423 = malloc(sizeof(I64));
        *_t423 = 1;
        U64 *_t424 = malloc(sizeof(U64)); *_t424 = U64_add(DEREF(i), DEREF(_t423));
        I64_delete(_t423, &(Bool){1});
        *i = DEREF(_t424);
        U64_delete(_t424, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    Bool *_t428 = malloc(sizeof(Bool));
    *_t428 = 0;
    return _t428;
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool *_t435 = U64_gt(&b->count, &a->count);
    if (DEREF(_t435)) {
        Bool *_t429 = malloc(sizeof(Bool));
        *_t429 = 0;
        Bool_delete(_t435, &(Bool){1});
        return _t429;
    }
    Bool_delete(_t435, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool *_wcond430 = U64_lt(i, &b->count);
        if (DEREF(_wcond430)) {
        } else {
            Bool_delete(_wcond430, &(Bool){1});
            break;
        }
        Bool_delete(_wcond430, &(Bool){1});
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool *_t432 = U8_neq(ac, bc);
        if (DEREF(_t432)) {
            Bool *_t431 = malloc(sizeof(Bool));
            *_t431 = 0;
            Bool_delete(_t432, &(Bool){1});
            U64_delete(i, &(Bool){1});
            return _t431;
        }
        Bool_delete(_t432, &(Bool){1});
        I64 *_t433 = malloc(sizeof(I64));
        *_t433 = 1;
        U64 *_t434 = malloc(sizeof(U64)); *_t434 = U64_add(DEREF(i), DEREF(_t433));
        I64_delete(_t433, &(Bool){1});
        *i = DEREF(_t434);
        U64_delete(_t434, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    Bool *_t436 = malloc(sizeof(Bool));
    *_t436 = 1;
    return _t436;
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool *_t444 = U64_gt(&b->count, &a->count);
    if (DEREF(_t444)) {
        Bool *_t437 = malloc(sizeof(Bool));
        *_t437 = 0;
        Bool_delete(_t444, &(Bool){1});
        return _t437;
    }
    Bool_delete(_t444, &(Bool){1});
    U64 *offset = malloc(sizeof(U64)); *offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool *_wcond438 = U64_lt(i, &b->count);
        if (DEREF(_wcond438)) {
        } else {
            Bool_delete(_wcond438, &(Bool){1});
            break;
        }
        Bool_delete(_wcond438, &(Bool){1});
        U64 *_t440 = malloc(sizeof(U64)); *_t440 = U64_add(DEREF(offset), DEREF(i));
        U8 *ac = Str_get(a, _t440);
        U8 *bc = Str_get(b, i);
        Bool *_t441 = U8_neq(ac, bc);
        U64_delete(_t440, &(Bool){1});
        if (DEREF(_t441)) {
            Bool *_t439 = malloc(sizeof(Bool));
            *_t439 = 0;
            Bool_delete(_t441, &(Bool){1});
            U64_delete(i, &(Bool){1});
            U64_delete(offset, &(Bool){1});
            return _t439;
        }
        Bool_delete(_t441, &(Bool){1});
        I64 *_t442 = malloc(sizeof(I64));
        *_t442 = 1;
        U64 *_t443 = malloc(sizeof(U64)); *_t443 = U64_add(DEREF(i), DEREF(_t442));
        I64_delete(_t442, &(Bool){1});
        *i = DEREF(_t443);
        U64_delete(_t443, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    U64_delete(offset, &(Bool){1});
    Bool *_t445 = malloc(sizeof(Bool));
    *_t445 = 1;
    return _t445;
}

Bool * Str_is_empty(Str * self) {
    I64 *_t446 = malloc(sizeof(I64));
    *_t446 = 0;
    Bool *_t447 = malloc(sizeof(Bool)); *_t447 = U64_eq(self->count, DEREF(_t446));
    I64_delete(_t446, &(Bool){1});
    return _t447;
}

I64 * Str_find(Str * self, Str * needle) {
    I64 *_t465 = malloc(sizeof(I64));
    *_t465 = 0;
    Bool *_t466 = malloc(sizeof(Bool)); *_t466 = U64_eq(needle->count, DEREF(_t465));
    I64_delete(_t465, &(Bool){1});
    if (DEREF(_t466)) {
        I64 *_t448 = malloc(sizeof(I64));
        *_t448 = 0;
        I64 *_t449 = malloc(sizeof(I64));
        *_t449 = 1;
        I64 *_t450 = malloc(sizeof(I64)); *_t450 = I64_sub(DEREF(_t448), DEREF(_t449));
        I64_delete(_t448, &(Bool){1});
        I64_delete(_t449, &(Bool){1});
        Bool_delete(_t466, &(Bool){1});
        return _t450;
    }
    Bool_delete(_t466, &(Bool){1});
    Bool *_t467 = U64_gt(&needle->count, &self->count);
    if (DEREF(_t467)) {
        I64 *_t451 = malloc(sizeof(I64));
        *_t451 = 0;
        I64 *_t452 = malloc(sizeof(I64));
        *_t452 = 1;
        I64 *_t453 = malloc(sizeof(I64)); *_t453 = I64_sub(DEREF(_t451), DEREF(_t452));
        I64_delete(_t451, &(Bool){1});
        I64_delete(_t452, &(Bool){1});
        Bool_delete(_t467, &(Bool){1});
        return _t453;
    }
    Bool_delete(_t467, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t462 = malloc(sizeof(U64)); *_t462 = U64_sub(self->count, needle->count);
        Bool *_wcond454 = U64_lte(i, _t462);
        U64_delete(_t462, &(Bool){1});
        if (DEREF(_wcond454)) {
        } else {
            Bool_delete(_wcond454, &(Bool){1});
            break;
        }
        Bool_delete(_wcond454, &(Bool){1});
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond455 = U64_lt(j, &needle->count);
            if (DEREF(_wcond455)) {
            } else {
                Bool_delete(_wcond455, &(Bool){1});
                break;
            }
            Bool_delete(_wcond455, &(Bool){1});
            U64 *_t457 = malloc(sizeof(U64)); *_t457 = U64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(self, _t457);
            U8 *bc = Str_get(needle, j);
            Bool *_t458 = U8_neq(ac, bc);
            U64_delete(_t457, &(Bool){1});
            if (DEREF(_t458)) {
                Bool *_t456 = malloc(sizeof(Bool));
                *_t456 = 0;
                *found = DEREF(_t456);
                Bool_delete(_t456, &(Bool){1});
            }
            Bool_delete(_t458, &(Bool){1});
            I64 *_t459 = malloc(sizeof(I64));
            *_t459 = 1;
            U64 *_t460 = malloc(sizeof(U64)); *_t460 = U64_add(DEREF(j), DEREF(_t459));
            I64_delete(_t459, &(Bool){1});
            *j = DEREF(_t460);
            U64_delete(_t460, &(Bool){1});
        }
        U64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            I64 *_t461 = malloc(sizeof(I64)); *_t461 = U64_to_i64(DEREF(i));
            Bool_delete(found, &(Bool){1});
            U64_delete(i, &(Bool){1});
            return _t461;
        }
        Bool_delete(found, &(Bool){1});
        I64 *_t463 = malloc(sizeof(I64));
        *_t463 = 1;
        U64 *_t464 = malloc(sizeof(U64)); *_t464 = U64_add(DEREF(i), DEREF(_t463));
        I64_delete(_t463, &(Bool){1});
        *i = DEREF(_t464);
        U64_delete(_t464, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    I64 *_t468 = malloc(sizeof(I64));
    *_t468 = 0;
    I64 *_t469 = malloc(sizeof(I64));
    *_t469 = 1;
    I64 *_t470 = malloc(sizeof(I64)); *_t470 = I64_sub(DEREF(_t468), DEREF(_t469));
    I64_delete(_t468, &(Bool){1});
    I64_delete(_t469, &(Bool){1});
    return _t470;
}

I64 * Str_rfind(Str * self, Str * needle) {
    I64 *_t488 = malloc(sizeof(I64));
    *_t488 = 0;
    Bool *_t489 = malloc(sizeof(Bool)); *_t489 = U64_eq(needle->count, DEREF(_t488));
    I64_delete(_t488, &(Bool){1});
    if (DEREF(_t489)) {
        I64 *_t471 = malloc(sizeof(I64));
        *_t471 = 0;
        I64 *_t472 = malloc(sizeof(I64));
        *_t472 = 1;
        I64 *_t473 = malloc(sizeof(I64)); *_t473 = I64_sub(DEREF(_t471), DEREF(_t472));
        I64_delete(_t471, &(Bool){1});
        I64_delete(_t472, &(Bool){1});
        Bool_delete(_t489, &(Bool){1});
        return _t473;
    }
    Bool_delete(_t489, &(Bool){1});
    Bool *_t490 = U64_gt(&needle->count, &self->count);
    if (DEREF(_t490)) {
        I64 *_t474 = malloc(sizeof(I64));
        *_t474 = 0;
        I64 *_t475 = malloc(sizeof(I64));
        *_t475 = 1;
        I64 *_t476 = malloc(sizeof(I64)); *_t476 = I64_sub(DEREF(_t474), DEREF(_t475));
        I64_delete(_t474, &(Bool){1});
        I64_delete(_t475, &(Bool){1});
        Bool_delete(_t490, &(Bool){1});
        return _t476;
    }
    Bool_delete(_t490, &(Bool){1});
    I64 *_t491 = malloc(sizeof(I64));
    *_t491 = 0;
    I64 *_t492 = malloc(sizeof(I64));
    *_t492 = 1;
    I64 *last = malloc(sizeof(I64)); *last = I64_sub(DEREF(_t491), DEREF(_t492));
    I64_delete(_t491, &(Bool){1});
    I64_delete(_t492, &(Bool){1});
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t485 = malloc(sizeof(U64)); *_t485 = U64_sub(self->count, needle->count);
        Bool *_wcond477 = U64_lte(i, _t485);
        U64_delete(_t485, &(Bool){1});
        if (DEREF(_wcond477)) {
        } else {
            Bool_delete(_wcond477, &(Bool){1});
            break;
        }
        Bool_delete(_wcond477, &(Bool){1});
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool *found = malloc(sizeof(Bool));
        *found = 1;
        while (1) {
            Bool *_wcond478 = U64_lt(j, &needle->count);
            if (DEREF(_wcond478)) {
            } else {
                Bool_delete(_wcond478, &(Bool){1});
                break;
            }
            Bool_delete(_wcond478, &(Bool){1});
            U64 *_t480 = malloc(sizeof(U64)); *_t480 = U64_add(DEREF(i), DEREF(j));
            U8 *ac = Str_get(self, _t480);
            U8 *bc = Str_get(needle, j);
            Bool *_t481 = U8_neq(ac, bc);
            U64_delete(_t480, &(Bool){1});
            if (DEREF(_t481)) {
                Bool *_t479 = malloc(sizeof(Bool));
                *_t479 = 0;
                *found = DEREF(_t479);
                Bool_delete(_t479, &(Bool){1});
            }
            Bool_delete(_t481, &(Bool){1});
            I64 *_t482 = malloc(sizeof(I64));
            *_t482 = 1;
            U64 *_t483 = malloc(sizeof(U64)); *_t483 = U64_add(DEREF(j), DEREF(_t482));
            I64_delete(_t482, &(Bool){1});
            *j = DEREF(_t483);
            U64_delete(_t483, &(Bool){1});
        }
        U64_delete(j, &(Bool){1});
        if (DEREF(found)) {
            I64 *_t484 = malloc(sizeof(I64)); *_t484 = U64_to_i64(DEREF(i));
            *last = DEREF(_t484);
            I64_delete(_t484, &(Bool){1});
        }
        Bool_delete(found, &(Bool){1});
        I64 *_t486 = malloc(sizeof(I64));
        *_t486 = 1;
        U64 *_t487 = malloc(sizeof(U64)); *_t487 = U64_add(DEREF(i), DEREF(_t486));
        I64_delete(_t486, &(Bool){1});
        *i = DEREF(_t487);
        U64_delete(_t487, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    return last;
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    I64 *_t508 = malloc(sizeof(I64));
    *_t508 = 0;
    Bool *_t509 = malloc(sizeof(Bool)); *_t509 = U64_eq(from->count, DEREF(_t508));
    I64_delete(_t508, &(Bool){1});
    if (DEREF(_t509)) {
        Str *_t493 = Str_clone(self);
        Bool_delete(_t509, &(Bool){1});
        return _t493;
    }
    Bool_delete(_t509, &(Bool){1});
    Str *result = Str_lit("", 0ULL);
    U64 *start = malloc(sizeof(U64));
    *start = 0;
    while (1) {
        U64 *_t495 = malloc(sizeof(U64)); *_t495 = U64_sub(self->count, from->count);
        Bool *_wcond494 = U64_lte(start, _t495);
        U64_delete(_t495, &(Bool){1});
        if (DEREF(_wcond494)) {
        } else {
            Bool_delete(_wcond494, &(Bool){1});
            break;
        }
        Bool_delete(_wcond494, &(Bool){1});
        U64 *_t496 = malloc(sizeof(U64)); *_t496 = U64_sub(self->count, DEREF(start));
        Str *rest = Str_substr(self, start, _t496);
        U64_delete(_t496, &(Bool){1});
        I64 *pos = Str_find(rest, from);
        I64 *_t497 = malloc(sizeof(I64));
        *_t497 = 0;
        I64 *_t498 = malloc(sizeof(I64));
        *_t498 = 1;
        I64 *_t499 = malloc(sizeof(I64)); *_t499 = I64_sub(DEREF(_t497), DEREF(_t498));
        I64_delete(_t497, &(Bool){1});
        I64_delete(_t498, &(Bool){1});
        Bool *_t500 = malloc(sizeof(Bool)); *_t500 = I64_eq(DEREF(pos), DEREF(_t499));
        I64_delete(_t499, &(Bool){1});
        if (DEREF(_t500)) {
            result = Str_concat(result, rest);
            Bool_delete(_t500, &(Bool){1});
            I64_delete(pos, &(Bool){1});
            Str_delete(rest, &(Bool){1});
            U64_delete(start, &(Bool){1});
            return result;
        }
        Bool_delete(_t500, &(Bool){1});
        Str_delete(rest, &(Bool){1});
        U64 *_t501 = U64_from_i64(pos);
        Str *_t502 = Str_substr(self, start, _t501);
        U64_delete(_t501, &(Bool){1});
        result = Str_concat(result, _t502);
        Str_delete(_t502, &(Bool){1});
        result = Str_concat(result, to);
        U64 *_t503 = U64_from_i64(pos);
        I64_delete(pos, &(Bool){1});
        U64 *_t504 = malloc(sizeof(U64)); *_t504 = U64_add(DEREF(start), DEREF(_t503));
        U64_delete(_t503, &(Bool){1});
        U64 *_t505 = malloc(sizeof(U64)); *_t505 = U64_add(DEREF(_t504), from->count);
        U64_delete(_t504, &(Bool){1});
        *start = DEREF(_t505);
        U64_delete(_t505, &(Bool){1});
    }
    Bool *_t510 = U64_lt(start, &self->count);
    if (DEREF(_t510)) {
        U64 *_t506 = malloc(sizeof(U64)); *_t506 = U64_sub(self->count, DEREF(start));
        Str *_t507 = Str_substr(self, start, _t506);
        U64_delete(_t506, &(Bool){1});
        result = Str_concat(result, _t507);
        Str_delete(_t507, &(Bool){1});
    }
    Bool_delete(_t510, &(Bool){1});
    U64_delete(start, &(Bool){1});
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    I64 *_t511 = malloc(sizeof(I64));
    *_t511 = 1;
    Str *_t512 = Str_substr(self, i, _t511);
    I64_delete(_t511, &(Bool){1});
    return _t512;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    Bool *_t515 = Str_starts_with(self, prefix);
    if (DEREF(_t515)) {
        U64 *_t513 = malloc(sizeof(U64)); *_t513 = U64_sub(self->count, prefix->count);
        Str *_t514 = Str_substr(self, &prefix->count, _t513);
        U64_delete(_t513, &(Bool){1});
        Bool_delete(_t515, &(Bool){1});
        return _t514;
    }
    Bool_delete(_t515, &(Bool){1});
    Str *_t516 = Str_clone(self);
    return _t516;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    Bool *_t520 = Str_ends_with(self, suffix);
    if (DEREF(_t520)) {
        I64 *_t517 = malloc(sizeof(I64));
        *_t517 = 0;
        U64 *_t518 = malloc(sizeof(U64)); *_t518 = U64_sub(self->count, suffix->count);
        Str *_t519 = Str_substr(self, _t517, _t518);
        I64_delete(_t517, &(Bool){1});
        U64_delete(_t518, &(Bool){1});
        Bool_delete(_t520, &(Bool){1});
        return _t519;
    }
    Bool_delete(_t520, &(Bool){1});
    Str *_t521 = Str_clone(self);
    return _t521;
}

Str * Str_from_byte(U8 * byte) {
    I64 *_t522 = malloc(sizeof(I64));
    *_t522 = 2;
    U8 *buf = malloc(DEREF(_t522));
    I64_delete(_t522, &(Bool){1});
    I64 *_t523 = malloc(sizeof(I64));
    *_t523 = 1;
    memcpy(buf, byte, DEREF(_t523));
    I64_delete(_t523, &(Bool){1});
    I64 *_t524 = malloc(sizeof(I64));
    *_t524 = 1;
    I64 *_t525 = malloc(sizeof(I64));
    *_t525 = 0;
    void *_t526 = ptr_add(buf, DEREF(_t524));
    U8 *_t527 = U8_from_i64(_t525);
    I64_delete(_t525, &(Bool){1});
    I64 *_t528 = malloc(sizeof(I64));
    *_t528 = 1;
    memcpy(_t526, _t527, DEREF(_t528));
    I64_delete(_t524, &(Bool){1});
    U8_delete(_t527, &(Bool){1});
    I64_delete(_t528, &(Bool){1});
    I64 *_t529 = malloc(sizeof(I64));
    *_t529 = 1;
    I64 *_t530 = malloc(sizeof(I64));
    *_t530 = 1;
    Str *_t531 = malloc(sizeof(Str));
    _t531->c_str = buf;
    _t531->count = DEREF(_t529);
    _t531->cap = DEREF(_t530);
    I64_delete(_t529, &(Bool){1});
    I64_delete(_t530, &(Bool){1});
    return _t531;
}

I64 * Str_to_i64(Str * self) {
    I64 *_t572 = malloc(sizeof(I64));
    *_t572 = 0;
    Bool *_t573 = malloc(sizeof(Bool)); *_t573 = U64_eq(self->count, DEREF(_t572));
    I64_delete(_t572, &(Bool){1});
    if (DEREF(_t573)) {
        Str *_t532 = Str_lit("Str", 3ULL);
        U64 *_t533 = Str_size();
        U64 *_t534 = malloc(sizeof(U64));
        *_t534 = 1;
        Array *_va8 = Array_new(_t532, _t533, _t534);
        Str_delete(_t532, &(Bool){1});
        U64_delete(_t533, &(Bool){1});
        U64_delete(_t534, &(Bool){1});
        U64 *_t535 = malloc(sizeof(U64));
        *_t535 = 0;
        Str *_t536 = Str_lit("empty string", 12ULL);
        Array_set(_va8, _t535, _t536);
        U64_delete(_t535, &(Bool){1});
        Str *_t537 = Str_lit("Str.to_i64", 10ULL);
        panic(_t537, _va8);
        Str_delete(_t537, &(Bool){1});
        Array_delete(_va8, &(Bool){1});
    }
    Bool_delete(_t573, &(Bool){1});
    I64 *result = malloc(sizeof(I64));
    *result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool *neg = malloc(sizeof(Bool));
    *neg = 0;
    I64 *_t574 = malloc(sizeof(I64));
    *_t574 = 0;
    U8 *first = Str_get(self, _t574);
    I64 *_t575 = malloc(sizeof(I64));
    *_t575 = 45;
    U8 *_t576 = U8_from_i64(_t575);
    I64_delete(_t575, &(Bool){1});
    Bool *_t577 = malloc(sizeof(Bool)); *_t577 = U8_eq(DEREF(first), DEREF(_t576));
    I64_delete(_t574, &(Bool){1});
    U8_delete(_t576, &(Bool){1});
    if (DEREF(_t577)) {
        Bool *_t538 = malloc(sizeof(Bool));
        *_t538 = 1;
        *neg = DEREF(_t538);
        Bool_delete(_t538, &(Bool){1});
        I64 *_t539 = malloc(sizeof(I64));
        *_t539 = 1;
        U64 *_t540 = U64_from_i64(_t539);
        I64_delete(_t539, &(Bool){1});
        *i = DEREF(_t540);
        U64_delete(_t540, &(Bool){1});
    }
    Bool_delete(_t577, &(Bool){1});
    Bool *_t578 = malloc(sizeof(Bool)); *_t578 = U64_eq(DEREF(i), self->count);
    if (DEREF(_t578)) {
        Str *_t541 = Str_lit("Str", 3ULL);
        U64 *_t542 = Str_size();
        U64 *_t543 = malloc(sizeof(U64));
        *_t543 = 1;
        Array *_va9 = Array_new(_t541, _t542, _t543);
        Str_delete(_t541, &(Bool){1});
        U64_delete(_t542, &(Bool){1});
        U64_delete(_t543, &(Bool){1});
        U64 *_t544 = malloc(sizeof(U64));
        *_t544 = 0;
        Str *_t545 = Str_lit("no digits", 9ULL);
        Array_set(_va9, _t544, _t545);
        U64_delete(_t544, &(Bool){1});
        Str *_t546 = Str_lit("Str.to_i64", 10ULL);
        panic(_t546, _va9);
        Str_delete(_t546, &(Bool){1});
        Array_delete(_va9, &(Bool){1});
    }
    Bool_delete(_t578, &(Bool){1});
    while (1) {
        Bool *_wcond547 = U64_lt(i, &self->count);
        if (DEREF(_wcond547)) {
        } else {
            Bool_delete(_wcond547, &(Bool){1});
            break;
        }
        Bool_delete(_wcond547, &(Bool){1});
        U8 *ch = Str_get(self, i);
        I64 *_t558 = malloc(sizeof(I64)); *_t558 = U8_to_i64(DEREF(ch));
        I64 *_t559 = malloc(sizeof(I64));
        *_t559 = 48;
        I64 *d = malloc(sizeof(I64)); *d = I64_sub(DEREF(_t558), DEREF(_t559));
        I64_delete(_t558, &(Bool){1});
        I64_delete(_t559, &(Bool){1});
        I64 *_t560 = malloc(sizeof(I64));
        *_t560 = 0;
        I64 *_t561 = malloc(sizeof(I64));
        *_t561 = 9;
        Bool *_t562 = I64_lt(d, _t560);
        I64_delete(_t560, &(Bool){1});
        Bool *_t563 = I64_gt(d, _t561);
        I64_delete(_t561, &(Bool){1});
        Bool *_t564 = malloc(sizeof(Bool)); *_t564 = Bool_or(DEREF(_t562), DEREF(_t563));
        Bool_delete(_t562, &(Bool){1});
        Bool_delete(_t563, &(Bool){1});
        if (DEREF(_t564)) {
            Str *_t548 = Str_lit("Str", 3ULL);
            U64 *_t549 = Str_size();
            U64 *_t550 = malloc(sizeof(U64));
            *_t550 = 3;
            Array *_va10 = Array_new(_t548, _t549, _t550);
            Str_delete(_t548, &(Bool){1});
            U64_delete(_t549, &(Bool){1});
            U64_delete(_t550, &(Bool){1});
            U64 *_t551 = malloc(sizeof(U64));
            *_t551 = 0;
            Str *_t552 = Str_lit("invalid char in '", 17ULL);
            Array_set(_va10, _t551, _t552);
            U64_delete(_t551, &(Bool){1});
            U64 *_t553 = malloc(sizeof(U64));
            *_t553 = 1;
            Str *_t554 = Str_clone(self);
            Array_set(_va10, _t553, _t554);
            U64_delete(_t553, &(Bool){1});
            U64 *_t555 = malloc(sizeof(U64));
            *_t555 = 2;
            Str *_t556 = Str_lit("'", 1ULL);
            Array_set(_va10, _t555, _t556);
            U64_delete(_t555, &(Bool){1});
            Str *_t557 = Str_lit("Str.to_i64", 10ULL);
            panic(_t557, _va10);
            Str_delete(_t557, &(Bool){1});
            Array_delete(_va10, &(Bool){1});
        }
        Bool_delete(_t564, &(Bool){1});
        I64 *_t565 = malloc(sizeof(I64));
        *_t565 = 10;
        I64 *_t566 = malloc(sizeof(I64)); *_t566 = I64_mul(DEREF(result), DEREF(_t565));
        I64_delete(_t565, &(Bool){1});
        I64 *_t567 = malloc(sizeof(I64)); *_t567 = I64_add(DEREF(_t566), DEREF(d));
        I64_delete(_t566, &(Bool){1});
        I64_delete(d, &(Bool){1});
        *result = DEREF(_t567);
        I64_delete(_t567, &(Bool){1});
        I64 *_t568 = malloc(sizeof(I64));
        *_t568 = 1;
        U64 *_t569 = malloc(sizeof(U64)); *_t569 = U64_add(DEREF(i), DEREF(_t568));
        I64_delete(_t568, &(Bool){1});
        *i = DEREF(_t569);
        U64_delete(_t569, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    if (DEREF(neg)) {
        I64 *_t570 = malloc(sizeof(I64));
        *_t570 = 0;
        I64 *_t571 = malloc(sizeof(I64)); *_t571 = I64_sub(DEREF(_t570), DEREF(result));
        I64_delete(_t570, &(Bool){1});
        Bool_delete(neg, &(Bool){1});
        I64_delete(result, &(Bool){1});
        return _t571;
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
    I64 *_t580 = Str_cmp(a, b);
    I64 *_t581 = malloc(sizeof(I64));
    *_t581 = 0;
    Bool *_t582 = malloc(sizeof(Bool)); *_t582 = I64_eq(DEREF(_t580), DEREF(_t581));
    I64_delete(_t580, &(Bool){1});
    I64_delete(_t581, &(Bool){1});
    return _t582;
}

Bool * Str_lt(Str * a, Str * b) {
    I64 *_t583 = malloc(sizeof(I64));
    *_t583 = 0;
    I64 *_t584 = malloc(sizeof(I64));
    *_t584 = 1;
    I64 *_t585 = Str_cmp(a, b);
    I64 *_t586 = malloc(sizeof(I64)); *_t586 = I64_sub(DEREF(_t583), DEREF(_t584));
    I64_delete(_t583, &(Bool){1});
    I64_delete(_t584, &(Bool){1});
    Bool *_t587 = malloc(sizeof(Bool)); *_t587 = I64_eq(DEREF(_t585), DEREF(_t586));
    I64_delete(_t585, &(Bool){1});
    I64_delete(_t586, &(Bool){1});
    return _t587;
}

Bool * Str_gt(Str * a, Str * b) {
    I64 *_t588 = Str_cmp(a, b);
    I64 *_t589 = malloc(sizeof(I64));
    *_t589 = 1;
    Bool *_t590 = malloc(sizeof(Bool)); *_t590 = I64_eq(DEREF(_t588), DEREF(_t589));
    I64_delete(_t588, &(Bool){1});
    I64_delete(_t589, &(Bool){1});
    return _t590;
}

Bool * Str_neq(Str * a, Str * b) {
    Bool *_t591 = Str_eq(a, b);
    Bool *_t592 = malloc(sizeof(Bool)); *_t592 = Bool_not(DEREF(_t591));
    Bool_delete(_t591, &(Bool){1});
    return _t592;
}

Bool * Str_lte(Str * a, Str * b) {
    Bool *_t593 = Str_gt(a, b);
    Bool *_t594 = malloc(sizeof(Bool)); *_t594 = Bool_not(DEREF(_t593));
    Bool_delete(_t593, &(Bool){1});
    return _t594;
}

Bool * Str_gte(Str * a, Str * b) {
    Bool *_t595 = Str_lt(a, b);
    Bool *_t596 = malloc(sizeof(Bool)); *_t596 = Bool_not(DEREF(_t595));
    Bool_delete(_t595, &(Bool){1});
    return _t596;
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t597 = malloc(DEREF(elem_size));
    U64 *_t598 = malloc(sizeof(U64));
    *_t598 = 0;
    I64 *_t599 = malloc(sizeof(I64));
    *_t599 = 1;
    U64 *_t600 = U64_clone(elem_size);
    Vec *_t601 = malloc(sizeof(Vec));
    _t601->data = _t597;
    _t601->count = DEREF(_t598);
    _t601->cap = DEREF(_t599);
    _t601->elem_size = DEREF(_t600);
    { Str *_ca = Str_clone(elem_type); _t601->elem_type = *_ca; free(_ca); }
    U64_delete(_t598, &(Bool){1});
    I64_delete(_t599, &(Bool){1});
    U64_delete(_t600, &(Bool){1});
    return _t601;
}

U64 * Vec_len(Vec * self) {
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    Bool *_t606 = malloc(sizeof(Bool)); *_t606 = U64_eq(self->count, self->cap);
    if (DEREF(_t606)) {
        I64 *_t602 = malloc(sizeof(I64));
        *_t602 = 2;
        U64 *new_cap = malloc(sizeof(U64)); *new_cap = U64_mul(self->cap, DEREF(_t602));
        I64_delete(_t602, &(Bool){1});
        U64 *_t603 = malloc(sizeof(U64)); *_t603 = U64_mul(DEREF(new_cap), self->elem_size);
        void *_t604 = realloc(self->data, DEREF(_t603));
        U64_delete(_t603, &(Bool){1});
        self->data = _t604;
        U64 *_t605 = U64_clone(new_cap);
        U64_delete(new_cap, &(Bool){1});
        self->cap = DEREF(_t605);
        U64_delete(_t605, &(Bool){1});
    }
    Bool_delete(_t606, &(Bool){1});
    U64 *_t607 = malloc(sizeof(U64)); *_t607 = U64_mul(self->count, self->elem_size);
    void *_t608 = ptr_add(self->data, DEREF(_t607));
    memcpy(_t608, val, self->elem_size);
    U64_delete(_t607, &(Bool){1});
    free(val);
    I64 *_t609 = malloc(sizeof(I64));
    *_t609 = 1;
    U64 *_t610 = malloc(sizeof(U64)); *_t610 = U64_add(self->count, DEREF(_t609));
    I64_delete(_t609, &(Bool){1});
    self->count = DEREF(_t610);
    U64_delete(_t610, &(Bool){1});
}

void * Vec_get(Vec * self, U64 * i) {
    Bool *_t625 = U64_gte(i, &self->count);
    if (DEREF(_t625)) {
        Str *_t611 = Str_lit("Str", 3ULL);
        U64 *_t612 = Str_size();
        U64 *_t613 = malloc(sizeof(U64));
        *_t613 = 5;
        Array *_va11 = Array_new(_t611, _t612, _t613);
        Str_delete(_t611, &(Bool){1});
        U64_delete(_t612, &(Bool){1});
        U64_delete(_t613, &(Bool){1});
        U64 *_t614 = malloc(sizeof(U64));
        *_t614 = 0;
        Str *_t615 = Str_lit("index ", 6ULL);
        Array_set(_va11, _t614, _t615);
        U64_delete(_t614, &(Bool){1});
        U64 *_t616 = malloc(sizeof(U64));
        *_t616 = 1;
        Str *_t617 = U64_to_str(DEREF(i));
        Array_set(_va11, _t616, _t617);
        U64_delete(_t616, &(Bool){1});
        U64 *_t618 = malloc(sizeof(U64));
        *_t618 = 2;
        Str *_t619 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va11, _t618, _t619);
        U64_delete(_t618, &(Bool){1});
        U64 *_t620 = malloc(sizeof(U64));
        *_t620 = 3;
        Str *_t621 = U64_to_str(self->count);
        Array_set(_va11, _t620, _t621);
        U64_delete(_t620, &(Bool){1});
        U64 *_t622 = malloc(sizeof(U64));
        *_t622 = 4;
        Str *_t623 = Str_lit(")", 1ULL);
        Array_set(_va11, _t622, _t623);
        U64_delete(_t622, &(Bool){1});
        Str *_t624 = Str_lit("Vec.get", 7ULL);
        panic(_t624, _va11);
        Str_delete(_t624, &(Bool){1});
        Array_delete(_va11, &(Bool){1});
    }
    Bool_delete(_t625, &(Bool){1});
    U64 *_t626 = malloc(sizeof(U64)); *_t626 = U64_mul(DEREF(i), self->elem_size);
    void *_t627 = ptr_add(self->data, DEREF(_t626));
    U64_delete(_t626, &(Bool){1});
    return _t627;
}

void Vec_delete(Vec * self, Bool * call_free) {
    Bool *_t641 = Str_is_empty(&self->elem_type);
    Bool *_t642 = malloc(sizeof(Bool)); *_t642 = Bool_not(DEREF(_t641));
    Bool_delete(_t641, &(Bool){1});
    if (DEREF(_t642)) {
        {
            U64 *_fi628 = malloc(sizeof(U64));
            *_fi628 = 0;
            while (1) {
                I64 *_t630 = malloc(sizeof(I64));
                *_t630 = 0;
                Range *_t631 = Range_new(DEREF(_t630), self->count);
                I64_delete(_t630, &(Bool){1});
                U64 *_t632 = Range_len(_t631);
                Range_delete(_t631, &(Bool){1});
                Bool *_wcond629 = U64_lt(_fi628, _t632);
                U64_delete(_t632, &(Bool){1});
                if (DEREF(_wcond629)) {
                } else {
                    Bool_delete(_wcond629, &(Bool){1});
                    break;
                }
                Bool_delete(_wcond629, &(Bool){1});
                I64 *_t633 = malloc(sizeof(I64));
                *_t633 = 0;
                Range *_t634 = Range_new(DEREF(_t633), self->count);
                I64_delete(_t633, &(Bool){1});
                U64 *i = Range_get(_t634, DEREF(_fi628));
                Range_delete(_t634, &(Bool){1});
                I64 *_t635 = malloc(sizeof(I64));
                *_t635 = 1;
                U64 *_t636 = malloc(sizeof(U64)); *_t636 = U64_add(DEREF(_fi628), DEREF(_t635));
                I64_delete(_t635, &(Bool){1});
                *_fi628 = DEREF(_t636);
                U64_delete(_t636, &(Bool){1});
                U64 *_t637 = malloc(sizeof(U64)); *_t637 = U64_mul(DEREF(i), self->elem_size);
                U64_delete(i, &(Bool){1});
                void *_t638 = ptr_add(self->data, DEREF(_t637));
                Bool *_t639 = malloc(sizeof(Bool));
                *_t639 = 0;
                dyn_call_delete(&self->elem_type, _t638, _t639);
                U64_delete(_t637, &(Bool){1});
                Bool_delete(_t639, &(Bool){1});
            }
            U64_delete(_fi628, &(Bool){1});
        }
    }
    Bool_delete(_t642, &(Bool){1});
    free(self->data);
    Bool *_t643 = Str_is_empty(&self->elem_type);
    Bool *_t644 = malloc(sizeof(Bool)); *_t644 = Bool_not(DEREF(_t643));
    Bool_delete(_t643, &(Bool){1});
    if (DEREF(_t644)) {
        Bool *_t640 = malloc(sizeof(Bool));
        *_t640 = 0;
        Str_delete(&self->elem_type, _t640);
        Bool_delete(_t640, &(Bool){1});
    }
    Bool_delete(_t644, &(Bool){1});
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    U64 *_t658 = malloc(sizeof(U64)); *_t658 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(DEREF(_t658));
    U64_delete(_t658, &(Bool){1});
    {
        U64 *_fi645 = malloc(sizeof(U64));
        *_fi645 = 0;
        while (1) {
            I64 *_t647 = malloc(sizeof(I64));
            *_t647 = 0;
            Range *_t648 = Range_new(DEREF(_t647), self->count);
            I64_delete(_t647, &(Bool){1});
            U64 *_t649 = Range_len(_t648);
            Range_delete(_t648, &(Bool){1});
            Bool *_wcond646 = U64_lt(_fi645, _t649);
            U64_delete(_t649, &(Bool){1});
            if (DEREF(_wcond646)) {
            } else {
                Bool_delete(_wcond646, &(Bool){1});
                break;
            }
            Bool_delete(_wcond646, &(Bool){1});
            I64 *_t650 = malloc(sizeof(I64));
            *_t650 = 0;
            Range *_t651 = Range_new(DEREF(_t650), self->count);
            I64_delete(_t650, &(Bool){1});
            U64 *i = Range_get(_t651, DEREF(_fi645));
            Range_delete(_t651, &(Bool){1});
            I64 *_t652 = malloc(sizeof(I64));
            *_t652 = 1;
            U64 *_t653 = malloc(sizeof(U64)); *_t653 = U64_add(DEREF(_fi645), DEREF(_t652));
            I64_delete(_t652, &(Bool){1});
            *_fi645 = DEREF(_t653);
            U64_delete(_t653, &(Bool){1});
            U64 *_t654 = malloc(sizeof(U64)); *_t654 = U64_mul(DEREF(i), self->elem_size);
            void *_t655 = ptr_add(self->data, DEREF(_t654));
            void *cloned = dyn_call_clone(&self->elem_type, _t655);
            U64_delete(_t654, &(Bool){1});
            U64 *_t656 = malloc(sizeof(U64)); *_t656 = U64_mul(DEREF(i), self->elem_size);
            U64_delete(i, &(Bool){1});
            void *_t657 = ptr_add(new_data, DEREF(_t656));
            memcpy(_t657, cloned, self->elem_size);
            U64_delete(_t656, &(Bool){1});
            free(cloned);
        }
        U64_delete(_fi645, &(Bool){1});
    }
    Vec *_t659 = malloc(sizeof(Vec));
    _t659->data = new_data;
    _t659->count = self->count;
    _t659->cap = self->cap;
    _t659->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t659->elem_type = *_ca; free(_ca); }
    return _t659;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    Str *_t677 = Str_lit("Str", 3ULL);
    U64 *_t678 = Str_size();
    Vec *parts = Vec_new(_t677, _t678);
    Str_delete(_t677, &(Bool){1});
    U64_delete(_t678, &(Bool){1});
    U64 *_t679 = Str_len(delim);
    I64 *_t680 = malloc(sizeof(I64));
    *_t680 = 0;
    Bool *_t681 = malloc(sizeof(Bool)); *_t681 = U64_eq(DEREF(_t679), DEREF(_t680));
    U64_delete(_t679, &(Bool){1});
    I64_delete(_t680, &(Bool){1});
    if (DEREF(_t681)) {
        Str *_t661 = Str_clone(s);
        Vec_push(parts, _t661);
        Bool_delete(_t681, &(Bool){1});
        return parts;
    }
    Bool_delete(_t681, &(Bool){1});
    U64 *start = malloc(sizeof(U64));
    *start = 0;
    U64 *pos = malloc(sizeof(U64));
    *pos = 0;
    while (1) {
        U64 *_t671 = Str_len(s);
        U64 *_t672 = Str_len(delim);
        U64 *_t673 = malloc(sizeof(U64)); *_t673 = U64_sub(DEREF(_t671), DEREF(_t672));
        U64_delete(_t671, &(Bool){1});
        U64_delete(_t672, &(Bool){1});
        Bool *_wcond662 = U64_lte(pos, _t673);
        U64_delete(_t673, &(Bool){1});
        if (DEREF(_wcond662)) {
        } else {
            Bool_delete(_wcond662, &(Bool){1});
            break;
        }
        Bool_delete(_wcond662, &(Bool){1});
        U64 *_t674 = Str_len(delim);
        Str *_t675 = Str_substr(s, pos, _t674);
        U64_delete(_t674, &(Bool){1});
        Bool *_t676 = Str_eq(_t675, delim);
        Str_delete(_t675, &(Bool){1});
        if (DEREF(_t676)) {
            U64 *_t663 = malloc(sizeof(U64)); *_t663 = U64_sub(DEREF(pos), DEREF(start));
            Str *_t664 = Str_substr(s, start, _t663);
            U64_delete(_t663, &(Bool){1});
            Str *_t665 = Str_clone(_t664);
            Str_delete(_t664, &(Bool){1});
            Vec_push(parts, _t665);
            U64 *_t666 = Str_len(delim);
            U64 *_t667 = malloc(sizeof(U64)); *_t667 = U64_add(DEREF(pos), DEREF(_t666));
            U64_delete(_t666, &(Bool){1});
            *start = DEREF(_t667);
            U64_delete(_t667, &(Bool){1});
            U64 *_t668 = U64_clone(start);
            *pos = DEREF(_t668);
            U64_delete(_t668, &(Bool){1});
        } else {
            I64 *_t669 = malloc(sizeof(I64));
            *_t669 = 1;
            U64 *_t670 = malloc(sizeof(U64)); *_t670 = U64_add(DEREF(pos), DEREF(_t669));
            I64_delete(_t669, &(Bool){1});
            *pos = DEREF(_t670);
            U64_delete(_t670, &(Bool){1});
        }
        Bool_delete(_t676, &(Bool){1});
    }
    U64_delete(pos, &(Bool){1});
    U64 *_t682 = Str_len(s);
    U64 *_t683 = malloc(sizeof(U64)); *_t683 = U64_sub(DEREF(_t682), DEREF(start));
    U64_delete(_t682, &(Bool){1});
    Str *_t684 = Str_substr(s, start, _t683);
    U64_delete(_t683, &(Bool){1});
    U64_delete(start, &(Bool){1});
    Str *_t685 = Str_clone(_t684);
    Str_delete(_t684, &(Bool){1});
    Vec_push(parts, _t685);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 *_t693 = Vec_len(parts);
    I64 *_t694 = malloc(sizeof(I64));
    *_t694 = 0;
    Bool *_t695 = malloc(sizeof(Bool)); *_t695 = U64_eq(DEREF(_t693), DEREF(_t694));
    U64_delete(_t693, &(Bool){1});
    I64_delete(_t694, &(Bool){1});
    if (DEREF(_t695)) {
        Str *_t686 = Str_lit("", 0ULL);
        Bool_delete(_t695, &(Bool){1});
        return _t686;
    }
    Bool_delete(_t695, &(Bool){1});
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t688 = Vec_len(parts);
        Bool *_wcond687 = U64_lt(i, _t688);
        U64_delete(_t688, &(Bool){1});
        if (DEREF(_wcond687)) {
        } else {
            Bool_delete(_wcond687, &(Bool){1});
            break;
        }
        Bool_delete(_wcond687, &(Bool){1});
        I64 *_t689 = malloc(sizeof(I64));
        *_t689 = 0;
        Bool *_t690 = U64_gt(i, _t689);
        I64_delete(_t689, &(Bool){1});
        if (DEREF(_t690)) {
            result = Str_concat(result, sep);
        }
        Bool_delete(_t690, &(Bool){1});
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        I64 *_t691 = malloc(sizeof(I64));
        *_t691 = 1;
        U64 *_t692 = malloc(sizeof(U64)); *_t692 = U64_add(DEREF(i), DEREF(_t691));
        I64_delete(_t691, &(Bool){1});
        *i = DEREF(_t692);
        U64_delete(_t692, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    return result;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    EnumDef *_t696 = malloc(sizeof(EnumDef));
    return _t696;
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

static Str * U8_to_str(U8 * val) {
    I64 *_t698 = malloc(sizeof(I64)); *_t698 = U8_to_i64(DEREF(val));
    Str *_t699 = I64_to_str(_t698);
    I64_delete(_t698, &(Bool){1});
    return _t699;
}

static U8 * U8_from_i64(I64 * val) {
    I64 *_t706 = malloc(sizeof(I64));
    *_t706 = 0;
    I64 *_t707 = malloc(sizeof(I64));
    *_t707 = 255;
    Bool *_t708 = I64_lt(val, _t706);
    I64_delete(_t706, &(Bool){1});
    Bool *_t709 = I64_gt(val, _t707);
    I64_delete(_t707, &(Bool){1});
    Bool *_t710 = malloc(sizeof(Bool)); *_t710 = Bool_or(DEREF(_t708), DEREF(_t709));
    Bool_delete(_t708, &(Bool){1});
    Bool_delete(_t709, &(Bool){1});
    if (DEREF(_t710)) {
        Str *_t700 = Str_lit("Str", 3ULL);
        U64 *_t701 = Str_size();
        U64 *_t702 = malloc(sizeof(U64));
        *_t702 = 1;
        Array *_va12 = Array_new(_t700, _t701, _t702);
        Str_delete(_t700, &(Bool){1});
        U64_delete(_t701, &(Bool){1});
        U64_delete(_t702, &(Bool){1});
        U64 *_t703 = malloc(sizeof(U64));
        *_t703 = 0;
        Str *_t704 = Str_lit("value out of range (0-255)", 26ULL);
        Array_set(_va12, _t703, _t704);
        U64_delete(_t703, &(Bool){1});
        Str *_t705 = Str_lit("U8.from_i64", 11ULL);
        panic(_t705, _va12);
        Str_delete(_t705, &(Bool){1});
        Array_delete(_va12, &(Bool){1});
    }
    Bool_delete(_t710, &(Bool){1});
    /* TODO: nested func U8_from_i64_ext */
    U8 *_t711 = U8_from_i64_ext(val);
    return _t711;
}

static U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

static Bool * U8_lt(U8 * a, U8 * b) {
    I64 *_t713 = malloc(sizeof(I64));
    *_t713 = 0;
    I64 *_t714 = malloc(sizeof(I64));
    *_t714 = 1;
    I64 *_t715 = malloc(sizeof(I64)); *_t715 = U8_cmp(DEREF(a), DEREF(b));
    I64 *_t716 = malloc(sizeof(I64)); *_t716 = I64_sub(DEREF(_t713), DEREF(_t714));
    I64_delete(_t713, &(Bool){1});
    I64_delete(_t714, &(Bool){1});
    Bool *_t717 = malloc(sizeof(Bool)); *_t717 = I64_eq(DEREF(_t715), DEREF(_t716));
    I64_delete(_t715, &(Bool){1});
    I64_delete(_t716, &(Bool){1});
    return _t717;
}

static Bool * U8_gt(U8 * a, U8 * b) {
    I64 *_t718 = malloc(sizeof(I64)); *_t718 = U8_cmp(DEREF(a), DEREF(b));
    I64 *_t719 = malloc(sizeof(I64));
    *_t719 = 1;
    Bool *_t720 = malloc(sizeof(Bool)); *_t720 = I64_eq(DEREF(_t718), DEREF(_t719));
    I64_delete(_t718, &(Bool){1});
    I64_delete(_t719, &(Bool){1});
    return _t720;
}

static Bool * U8_neq(U8 * a, U8 * b) {
    Bool *_t721 = malloc(sizeof(Bool)); *_t721 = U8_eq(DEREF(a), DEREF(b));
    Bool *_t722 = malloc(sizeof(Bool)); *_t722 = Bool_not(DEREF(_t721));
    Bool_delete(_t721, &(Bool){1});
    return _t722;
}

static Bool * U8_lte(U8 * a, U8 * b) {
    Bool *_t723 = U8_gt(a, b);
    Bool *_t724 = malloc(sizeof(Bool)); *_t724 = Bool_not(DEREF(_t723));
    Bool_delete(_t723, &(Bool){1});
    return _t724;
}

static Bool * U8_gte(U8 * a, U8 * b) {
    Bool *_t725 = U8_lt(a, b);
    Bool *_t726 = malloc(sizeof(Bool)); *_t726 = Bool_not(DEREF(_t725));
    Bool_delete(_t725, &(Bool){1});
    return _t726;
}

static Str * I16_to_str(I16 * val) {
    I64 *_t727 = malloc(sizeof(I64)); *_t727 = I16_to_i64(DEREF(val));
    Str *_t728 = I64_to_str(_t727);
    I64_delete(_t727, &(Bool){1});
    return _t728;
}

static I16 * I16_from_i64(I64 * val) {
    I64 *_t735 = malloc(sizeof(I64));
    *_t735 = 32768;
    I64 *_t736 = I64_neg(_t735);
    I64_delete(_t735, &(Bool){1});
    I64 *_t737 = malloc(sizeof(I64));
    *_t737 = 32767;
    Bool *_t738 = I64_lt(val, _t736);
    I64_delete(_t736, &(Bool){1});
    Bool *_t739 = I64_gt(val, _t737);
    I64_delete(_t737, &(Bool){1});
    Bool *_t740 = malloc(sizeof(Bool)); *_t740 = Bool_or(DEREF(_t738), DEREF(_t739));
    Bool_delete(_t738, &(Bool){1});
    Bool_delete(_t739, &(Bool){1});
    if (DEREF(_t740)) {
        Str *_t729 = Str_lit("Str", 3ULL);
        U64 *_t730 = Str_size();
        U64 *_t731 = malloc(sizeof(U64));
        *_t731 = 1;
        Array *_va13 = Array_new(_t729, _t730, _t731);
        Str_delete(_t729, &(Bool){1});
        U64_delete(_t730, &(Bool){1});
        U64_delete(_t731, &(Bool){1});
        U64 *_t732 = malloc(sizeof(U64));
        *_t732 = 0;
        Str *_t733 = Str_lit("value out of range (-32768 to 32767)", 36ULL);
        Array_set(_va13, _t732, _t733);
        U64_delete(_t732, &(Bool){1});
        Str *_t734 = Str_lit("I16.from_i64", 12ULL);
        panic(_t734, _va13);
        Str_delete(_t734, &(Bool){1});
        Array_delete(_va13, &(Bool){1});
    }
    Bool_delete(_t740, &(Bool){1});
    /* TODO: nested func I16_from_i64_ext */
    I16 *_t741 = I16_from_i64_ext(val);
    return _t741;
}

static I16 * I16_neg(I16 * a) {
    I64 *_t742 = malloc(sizeof(I64));
    *_t742 = 0;
    I64 *_t743 = malloc(sizeof(I64)); *_t743 = I16_to_i64(DEREF(a));
    I64 *_t744 = malloc(sizeof(I64)); *_t744 = I64_sub(DEREF(_t742), DEREF(_t743));
    I64_delete(_t742, &(Bool){1});
    I64_delete(_t743, &(Bool){1});
    I16 *_t745 = I16_from_i64(_t744);
    I64_delete(_t744, &(Bool){1});
    return _t745;
}

static I16 * I16_abs(I16 * a) {
    I64 *_t750 = malloc(sizeof(I64)); *_t750 = I16_to_i64(DEREF(a));
    I64 *_t751 = malloc(sizeof(I64));
    *_t751 = 0;
    Bool *_t752 = I64_lt(_t750, _t751);
    I64_delete(_t750, &(Bool){1});
    I64_delete(_t751, &(Bool){1});
    if (DEREF(_t752)) {
        I64 *_t746 = malloc(sizeof(I64));
        *_t746 = 0;
        I64 *_t747 = malloc(sizeof(I64)); *_t747 = I16_to_i64(DEREF(a));
        I64 *_t748 = malloc(sizeof(I64)); *_t748 = I64_sub(DEREF(_t746), DEREF(_t747));
        I64_delete(_t746, &(Bool){1});
        I64_delete(_t747, &(Bool){1});
        I16 *_t749 = I16_from_i64(_t748);
        I64_delete(_t748, &(Bool){1});
        Bool_delete(_t752, &(Bool){1});
        return _t749;
    }
    Bool_delete(_t752, &(Bool){1});
    I16 *_t753 = I16_clone(a);
    return _t753;
}

static U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

static Bool * I16_lt(I16 * a, I16 * b) {
    I64 *_t755 = malloc(sizeof(I64));
    *_t755 = 0;
    I64 *_t756 = malloc(sizeof(I64));
    *_t756 = 1;
    I64 *_t757 = malloc(sizeof(I64)); *_t757 = I16_cmp(DEREF(a), DEREF(b));
    I64 *_t758 = malloc(sizeof(I64)); *_t758 = I64_sub(DEREF(_t755), DEREF(_t756));
    I64_delete(_t755, &(Bool){1});
    I64_delete(_t756, &(Bool){1});
    Bool *_t759 = malloc(sizeof(Bool)); *_t759 = I64_eq(DEREF(_t757), DEREF(_t758));
    I64_delete(_t757, &(Bool){1});
    I64_delete(_t758, &(Bool){1});
    return _t759;
}

static Bool * I16_gt(I16 * a, I16 * b) {
    I64 *_t760 = malloc(sizeof(I64)); *_t760 = I16_cmp(DEREF(a), DEREF(b));
    I64 *_t761 = malloc(sizeof(I64));
    *_t761 = 1;
    Bool *_t762 = malloc(sizeof(Bool)); *_t762 = I64_eq(DEREF(_t760), DEREF(_t761));
    I64_delete(_t760, &(Bool){1});
    I64_delete(_t761, &(Bool){1});
    return _t762;
}

static Bool * I16_neq(I16 * a, I16 * b) {
    Bool *_t763 = malloc(sizeof(Bool)); *_t763 = I16_eq(DEREF(a), DEREF(b));
    Bool *_t764 = malloc(sizeof(Bool)); *_t764 = Bool_not(DEREF(_t763));
    Bool_delete(_t763, &(Bool){1});
    return _t764;
}

static Bool * I16_lte(I16 * a, I16 * b) {
    Bool *_t765 = I16_gt(a, b);
    Bool *_t766 = malloc(sizeof(Bool)); *_t766 = Bool_not(DEREF(_t765));
    Bool_delete(_t765, &(Bool){1});
    return _t766;
}

static Bool * I16_gte(I16 * a, I16 * b) {
    Bool *_t767 = I16_lt(a, b);
    Bool *_t768 = malloc(sizeof(Bool)); *_t768 = Bool_not(DEREF(_t767));
    Bool_delete(_t767, &(Bool){1});
    return _t768;
}

static Str * I32_to_str(I32 * val) {
    I64 *_t769 = malloc(sizeof(I64)); *_t769 = I32_to_i64(DEREF(val));
    Str *_t770 = I64_to_str(_t769);
    I64_delete(_t769, &(Bool){1});
    return _t770;
}

static I32 * I32_from_i64(I64 * val) {
    I64 *_t777 = malloc(sizeof(I64));
    *_t777 = 2147483648;
    I64 *_t778 = I64_neg(_t777);
    I64_delete(_t777, &(Bool){1});
    I64 *_t779 = malloc(sizeof(I64));
    *_t779 = 2147483647;
    Bool *_t780 = I64_lt(val, _t778);
    I64_delete(_t778, &(Bool){1});
    Bool *_t781 = I64_gt(val, _t779);
    I64_delete(_t779, &(Bool){1});
    Bool *_t782 = malloc(sizeof(Bool)); *_t782 = Bool_or(DEREF(_t780), DEREF(_t781));
    Bool_delete(_t780, &(Bool){1});
    Bool_delete(_t781, &(Bool){1});
    if (DEREF(_t782)) {
        Str *_t771 = Str_lit("Str", 3ULL);
        U64 *_t772 = Str_size();
        U64 *_t773 = malloc(sizeof(U64));
        *_t773 = 1;
        Array *_va14 = Array_new(_t771, _t772, _t773);
        Str_delete(_t771, &(Bool){1});
        U64_delete(_t772, &(Bool){1});
        U64_delete(_t773, &(Bool){1});
        U64 *_t774 = malloc(sizeof(U64));
        *_t774 = 0;
        Str *_t775 = Str_lit("value out of range (-2147483648 to 2147483647)", 46ULL);
        Array_set(_va14, _t774, _t775);
        U64_delete(_t774, &(Bool){1});
        Str *_t776 = Str_lit("I32.from_i64", 12ULL);
        panic(_t776, _va14);
        Str_delete(_t776, &(Bool){1});
        Array_delete(_va14, &(Bool){1});
    }
    Bool_delete(_t782, &(Bool){1});
    /* TODO: nested func I32_from_i64_ext */
    I32 *_t783 = I32_from_i64_ext(val);
    return _t783;
}

static I32 * I32_neg(I32 * a) {
    I64 *_t784 = malloc(sizeof(I64));
    *_t784 = 0;
    I64 *_t785 = malloc(sizeof(I64)); *_t785 = I32_to_i64(DEREF(a));
    I64 *_t786 = malloc(sizeof(I64)); *_t786 = I64_sub(DEREF(_t784), DEREF(_t785));
    I64_delete(_t784, &(Bool){1});
    I64_delete(_t785, &(Bool){1});
    I32 *_t787 = I32_from_i64(_t786);
    I64_delete(_t786, &(Bool){1});
    return _t787;
}

static I32 * I32_abs(I32 * a) {
    I64 *_t792 = malloc(sizeof(I64)); *_t792 = I32_to_i64(DEREF(a));
    I64 *_t793 = malloc(sizeof(I64));
    *_t793 = 0;
    Bool *_t794 = I64_lt(_t792, _t793);
    I64_delete(_t792, &(Bool){1});
    I64_delete(_t793, &(Bool){1});
    if (DEREF(_t794)) {
        I64 *_t788 = malloc(sizeof(I64));
        *_t788 = 0;
        I64 *_t789 = malloc(sizeof(I64)); *_t789 = I32_to_i64(DEREF(a));
        I64 *_t790 = malloc(sizeof(I64)); *_t790 = I64_sub(DEREF(_t788), DEREF(_t789));
        I64_delete(_t788, &(Bool){1});
        I64_delete(_t789, &(Bool){1});
        I32 *_t791 = I32_from_i64(_t790);
        I64_delete(_t790, &(Bool){1});
        Bool_delete(_t794, &(Bool){1});
        return _t791;
    }
    Bool_delete(_t794, &(Bool){1});
    I32 *_t795 = I32_clone(a);
    return _t795;
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static Bool * I32_lt(I32 * a, I32 * b) {
    I64 *_t797 = malloc(sizeof(I64));
    *_t797 = 0;
    I64 *_t798 = malloc(sizeof(I64));
    *_t798 = 1;
    I64 *_t799 = malloc(sizeof(I64)); *_t799 = I32_cmp(DEREF(a), DEREF(b));
    I64 *_t800 = malloc(sizeof(I64)); *_t800 = I64_sub(DEREF(_t797), DEREF(_t798));
    I64_delete(_t797, &(Bool){1});
    I64_delete(_t798, &(Bool){1});
    Bool *_t801 = malloc(sizeof(Bool)); *_t801 = I64_eq(DEREF(_t799), DEREF(_t800));
    I64_delete(_t799, &(Bool){1});
    I64_delete(_t800, &(Bool){1});
    return _t801;
}

static Bool * I32_gt(I32 * a, I32 * b) {
    I64 *_t802 = malloc(sizeof(I64)); *_t802 = I32_cmp(DEREF(a), DEREF(b));
    I64 *_t803 = malloc(sizeof(I64));
    *_t803 = 1;
    Bool *_t804 = malloc(sizeof(Bool)); *_t804 = I64_eq(DEREF(_t802), DEREF(_t803));
    I64_delete(_t802, &(Bool){1});
    I64_delete(_t803, &(Bool){1});
    return _t804;
}

static Bool * I32_neq(I32 * a, I32 * b) {
    Bool *_t805 = malloc(sizeof(Bool)); *_t805 = I32_eq(DEREF(a), DEREF(b));
    Bool *_t806 = malloc(sizeof(Bool)); *_t806 = Bool_not(DEREF(_t805));
    Bool_delete(_t805, &(Bool){1});
    return _t806;
}

static Bool * I32_lte(I32 * a, I32 * b) {
    Bool *_t807 = I32_gt(a, b);
    Bool *_t808 = malloc(sizeof(Bool)); *_t808 = Bool_not(DEREF(_t807));
    Bool_delete(_t807, &(Bool){1});
    return _t808;
}

static Bool * I32_gte(I32 * a, I32 * b) {
    Bool *_t809 = I32_lt(a, b);
    Bool *_t810 = malloc(sizeof(Bool)); *_t810 = Bool_not(DEREF(_t809));
    Bool_delete(_t809, &(Bool){1});
    return _t810;
}

static F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 *_t811 = F32_from_i64_ext(val);
    return _t811;
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static Bool * F32_lt(F32 * a, F32 * b) {
    I64 *_t813 = malloc(sizeof(I64));
    *_t813 = 0;
    I64 *_t814 = malloc(sizeof(I64));
    *_t814 = 1;
    I64 *_t815 = malloc(sizeof(I64)); *_t815 = F32_cmp(DEREF(a), DEREF(b));
    I64 *_t816 = malloc(sizeof(I64)); *_t816 = I64_sub(DEREF(_t813), DEREF(_t814));
    I64_delete(_t813, &(Bool){1});
    I64_delete(_t814, &(Bool){1});
    Bool *_t817 = malloc(sizeof(Bool)); *_t817 = I64_eq(DEREF(_t815), DEREF(_t816));
    I64_delete(_t815, &(Bool){1});
    I64_delete(_t816, &(Bool){1});
    return _t817;
}

static Bool * F32_gt(F32 * a, F32 * b) {
    I64 *_t818 = malloc(sizeof(I64)); *_t818 = F32_cmp(DEREF(a), DEREF(b));
    I64 *_t819 = malloc(sizeof(I64));
    *_t819 = 1;
    Bool *_t820 = malloc(sizeof(Bool)); *_t820 = I64_eq(DEREF(_t818), DEREF(_t819));
    I64_delete(_t818, &(Bool){1});
    I64_delete(_t819, &(Bool){1});
    return _t820;
}

static Bool * F32_neq(F32 * a, F32 * b) {
    Bool *_t821 = malloc(sizeof(Bool)); *_t821 = F32_eq(DEREF(a), DEREF(b));
    Bool *_t822 = malloc(sizeof(Bool)); *_t822 = Bool_not(DEREF(_t821));
    Bool_delete(_t821, &(Bool){1});
    return _t822;
}

static Bool * F32_lte(F32 * a, F32 * b) {
    Bool *_t823 = F32_gt(a, b);
    Bool *_t824 = malloc(sizeof(Bool)); *_t824 = Bool_not(DEREF(_t823));
    Bool_delete(_t823, &(Bool){1});
    return _t824;
}

static Bool * F32_gte(F32 * a, F32 * b) {
    Bool *_t825 = F32_lt(a, b);
    Bool *_t826 = malloc(sizeof(Bool)); *_t826 = Bool_not(DEREF(_t825));
    Bool_delete(_t825, &(Bool){1});
    return _t826;
}

static Str * U32_to_str(U32 * val) {
    I64 *_t827 = malloc(sizeof(I64)); *_t827 = U32_to_i64(DEREF(val));
    Str *_t828 = I64_to_str(_t827);
    I64_delete(_t827, &(Bool){1});
    return _t828;
}

static U32 * U32_from_i64(I64 * val) {
    I64 *_t835 = malloc(sizeof(I64));
    *_t835 = 0;
    I64 *_t836 = malloc(sizeof(I64));
    *_t836 = 4294967295;
    Bool *_t837 = I64_lt(val, _t835);
    I64_delete(_t835, &(Bool){1});
    Bool *_t838 = I64_gt(val, _t836);
    I64_delete(_t836, &(Bool){1});
    Bool *_t839 = malloc(sizeof(Bool)); *_t839 = Bool_or(DEREF(_t837), DEREF(_t838));
    Bool_delete(_t837, &(Bool){1});
    Bool_delete(_t838, &(Bool){1});
    if (DEREF(_t839)) {
        Str *_t829 = Str_lit("Str", 3ULL);
        U64 *_t830 = Str_size();
        U64 *_t831 = malloc(sizeof(U64));
        *_t831 = 1;
        Array *_va15 = Array_new(_t829, _t830, _t831);
        Str_delete(_t829, &(Bool){1});
        U64_delete(_t830, &(Bool){1});
        U64_delete(_t831, &(Bool){1});
        U64 *_t832 = malloc(sizeof(U64));
        *_t832 = 0;
        Str *_t833 = Str_lit("value out of range (0-4294967295)", 33ULL);
        Array_set(_va15, _t832, _t833);
        U64_delete(_t832, &(Bool){1});
        Str *_t834 = Str_lit("U32.from_i64", 12ULL);
        panic(_t834, _va15);
        Str_delete(_t834, &(Bool){1});
        Array_delete(_va15, &(Bool){1});
    }
    Bool_delete(_t839, &(Bool){1});
    /* TODO: nested func U32_from_i64_ext */
    U32 *_t840 = U32_from_i64_ext(val);
    return _t840;
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static Bool * U32_lt(U32 * a, U32 * b) {
    I64 *_t842 = malloc(sizeof(I64));
    *_t842 = 0;
    I64 *_t843 = malloc(sizeof(I64));
    *_t843 = 1;
    I64 *_t844 = malloc(sizeof(I64)); *_t844 = U32_cmp(DEREF(a), DEREF(b));
    I64 *_t845 = malloc(sizeof(I64)); *_t845 = I64_sub(DEREF(_t842), DEREF(_t843));
    I64_delete(_t842, &(Bool){1});
    I64_delete(_t843, &(Bool){1});
    Bool *_t846 = malloc(sizeof(Bool)); *_t846 = I64_eq(DEREF(_t844), DEREF(_t845));
    I64_delete(_t844, &(Bool){1});
    I64_delete(_t845, &(Bool){1});
    return _t846;
}

static Bool * U32_gt(U32 * a, U32 * b) {
    I64 *_t847 = malloc(sizeof(I64)); *_t847 = U32_cmp(DEREF(a), DEREF(b));
    I64 *_t848 = malloc(sizeof(I64));
    *_t848 = 1;
    Bool *_t849 = malloc(sizeof(Bool)); *_t849 = I64_eq(DEREF(_t847), DEREF(_t848));
    I64_delete(_t847, &(Bool){1});
    I64_delete(_t848, &(Bool){1});
    return _t849;
}

static Bool * U32_neq(U32 * a, U32 * b) {
    Bool *_t850 = malloc(sizeof(Bool)); *_t850 = U32_eq(DEREF(a), DEREF(b));
    Bool *_t851 = malloc(sizeof(Bool)); *_t851 = Bool_not(DEREF(_t850));
    Bool_delete(_t850, &(Bool){1});
    return _t851;
}

static Bool * U32_lte(U32 * a, U32 * b) {
    Bool *_t852 = U32_gt(a, b);
    Bool *_t853 = malloc(sizeof(Bool)); *_t853 = Bool_not(DEREF(_t852));
    Bool_delete(_t852, &(Bool){1});
    return _t853;
}

static Bool * U32_gte(U32 * a, U32 * b) {
    Bool *_t854 = U32_lt(a, b);
    Bool *_t855 = malloc(sizeof(Bool)); *_t855 = Bool_not(DEREF(_t854));
    Bool_delete(_t854, &(Bool){1});
    return _t855;
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t856 = U64_to_str_ext(&(U64){val});
    return _t856;
}

static U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 *_t857 = U64_from_i64_ext(val);
    return _t857;
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static Bool * U64_lt(U64 * a, U64 * b) {
    I64 *_t859 = malloc(sizeof(I64));
    *_t859 = 0;
    I64 *_t860 = malloc(sizeof(I64));
    *_t860 = 1;
    I64 *_t861 = malloc(sizeof(I64)); *_t861 = U64_cmp(DEREF(a), DEREF(b));
    I64 *_t862 = malloc(sizeof(I64)); *_t862 = I64_sub(DEREF(_t859), DEREF(_t860));
    I64_delete(_t859, &(Bool){1});
    I64_delete(_t860, &(Bool){1});
    Bool *_t863 = malloc(sizeof(Bool)); *_t863 = I64_eq(DEREF(_t861), DEREF(_t862));
    I64_delete(_t861, &(Bool){1});
    I64_delete(_t862, &(Bool){1});
    return _t863;
}

static Bool * U64_gt(U64 * a, U64 * b) {
    I64 *_t864 = malloc(sizeof(I64)); *_t864 = U64_cmp(DEREF(a), DEREF(b));
    I64 *_t865 = malloc(sizeof(I64));
    *_t865 = 1;
    Bool *_t866 = malloc(sizeof(Bool)); *_t866 = I64_eq(DEREF(_t864), DEREF(_t865));
    I64_delete(_t864, &(Bool){1});
    I64_delete(_t865, &(Bool){1});
    return _t866;
}

static Bool * U64_neq(U64 * a, U64 * b) {
    Bool *_t867 = malloc(sizeof(Bool)); *_t867 = U64_eq(DEREF(a), DEREF(b));
    Bool *_t868 = malloc(sizeof(Bool)); *_t868 = Bool_not(DEREF(_t867));
    Bool_delete(_t867, &(Bool){1});
    return _t868;
}

static Bool * U64_lte(U64 * a, U64 * b) {
    Bool *_t869 = U64_gt(a, b);
    Bool *_t870 = malloc(sizeof(Bool)); *_t870 = Bool_not(DEREF(_t869));
    Bool_delete(_t869, &(Bool){1});
    return _t870;
}

static Bool * U64_gte(U64 * a, U64 * b) {
    Bool *_t871 = U64_lt(a, b);
    Bool *_t872 = malloc(sizeof(Bool)); *_t872 = Bool_not(DEREF(_t871));
    Bool_delete(_t871, &(Bool){1});
    return _t872;
}

static Str * I64_to_str(I64 * val) {
    I64 *_t912 = malloc(sizeof(I64));
    *_t912 = 0;
    Bool *_t913 = malloc(sizeof(Bool)); *_t913 = I64_eq(DEREF(val), DEREF(_t912));
    I64_delete(_t912, &(Bool){1});
    if (DEREF(_t913)) {
        I64 *_t873 = malloc(sizeof(I64));
        *_t873 = 2;
        U8 *buf = malloc(DEREF(_t873));
        I64_delete(_t873, &(Bool){1});
        I64 *_t874 = malloc(sizeof(I64));
        *_t874 = 48;
        U8 *_t875 = U8_from_i64(_t874);
        I64_delete(_t874, &(Bool){1});
        I64 *_t876 = malloc(sizeof(I64));
        *_t876 = 1;
        memcpy(buf, _t875, DEREF(_t876));
        U8_delete(_t875, &(Bool){1});
        I64_delete(_t876, &(Bool){1});
        I64 *_t877 = malloc(sizeof(I64));
        *_t877 = 1;
        I64 *_t878 = malloc(sizeof(I64));
        *_t878 = 0;
        void *_t879 = ptr_add(buf, DEREF(_t877));
        U8 *_t880 = U8_from_i64(_t878);
        I64_delete(_t878, &(Bool){1});
        I64 *_t881 = malloc(sizeof(I64));
        *_t881 = 1;
        memcpy(_t879, _t880, DEREF(_t881));
        I64_delete(_t877, &(Bool){1});
        U8_delete(_t880, &(Bool){1});
        I64_delete(_t881, &(Bool){1});
        I64 *_t882 = malloc(sizeof(I64));
        *_t882 = 1;
        I64 *_t883 = malloc(sizeof(I64));
        *_t883 = 1;
        Str *_t884 = malloc(sizeof(Str));
        _t884->c_str = buf;
        _t884->count = DEREF(_t882);
        _t884->cap = DEREF(_t883);
        I64_delete(_t882, &(Bool){1});
        I64_delete(_t883, &(Bool){1});
        Bool_delete(_t913, &(Bool){1});
        return _t884;
    }
    Bool_delete(_t913, &(Bool){1});
    Bool *is_neg = malloc(sizeof(Bool));
    *is_neg = 0;
    I64 *v = I64_clone(val);
    I64 *_t914 = malloc(sizeof(I64));
    *_t914 = 0;
    Bool *_t915 = I64_lt(val, _t914);
    I64_delete(_t914, &(Bool){1});
    if (DEREF(_t915)) {
        Bool *_t885 = malloc(sizeof(Bool));
        *_t885 = 1;
        *is_neg = DEREF(_t885);
        Bool_delete(_t885, &(Bool){1});
        I64 *_t886 = malloc(sizeof(I64));
        *_t886 = 0;
        I64 *_t887 = malloc(sizeof(I64)); *_t887 = I64_sub(DEREF(_t886), DEREF(val));
        I64_delete(_t886, &(Bool){1});
        *v = DEREF(_t887);
        I64_delete(_t887, &(Bool){1});
    }
    Bool_delete(_t915, &(Bool){1});
    U64 *ndigits = malloc(sizeof(U64));
    *ndigits = 0;
    I64 *tmp = I64_clone(v);
    while (1) {
        I64 *_t889 = malloc(sizeof(I64));
        *_t889 = 0;
        Bool *_wcond888 = I64_gt(tmp, _t889);
        I64_delete(_t889, &(Bool){1});
        if (DEREF(_wcond888)) {
        } else {
            Bool_delete(_wcond888, &(Bool){1});
            break;
        }
        Bool_delete(_wcond888, &(Bool){1});
        I64 *_t890 = malloc(sizeof(I64));
        *_t890 = 1;
        U64 *_t891 = malloc(sizeof(U64)); *_t891 = U64_add(DEREF(ndigits), DEREF(_t890));
        I64_delete(_t890, &(Bool){1});
        *ndigits = DEREF(_t891);
        U64_delete(_t891, &(Bool){1});
        I64 *_t892 = malloc(sizeof(I64));
        *_t892 = 10;
        I64 *_t893 = malloc(sizeof(I64)); *_t893 = I64_div(DEREF(tmp), DEREF(_t892));
        I64_delete(_t892, &(Bool){1});
        *tmp = DEREF(_t893);
        I64_delete(_t893, &(Bool){1});
    }
    I64_delete(tmp, &(Bool){1});
    U64 *total = U64_clone(ndigits);
    U64_delete(ndigits, &(Bool){1});
    if (DEREF(is_neg)) {
        I64 *_t894 = malloc(sizeof(I64));
        *_t894 = 1;
        U64 *_t895 = malloc(sizeof(U64)); *_t895 = U64_add(DEREF(total), DEREF(_t894));
        I64_delete(_t894, &(Bool){1});
        *total = DEREF(_t895);
        U64_delete(_t895, &(Bool){1});
    }
    I64 *_t916 = malloc(sizeof(I64));
    *_t916 = 1;
    U64 *_t917 = malloc(sizeof(U64)); *_t917 = U64_add(DEREF(total), DEREF(_t916));
    I64_delete(_t916, &(Bool){1});
    U8 *buf = malloc(DEREF(_t917));
    U64_delete(_t917, &(Bool){1});
    if (DEREF(is_neg)) {
        I64 *_t896 = malloc(sizeof(I64));
        *_t896 = 45;
        U8 *_t897 = U8_from_i64(_t896);
        I64_delete(_t896, &(Bool){1});
        I64 *_t898 = malloc(sizeof(I64));
        *_t898 = 1;
        memcpy(buf, _t897, DEREF(_t898));
        U8_delete(_t897, &(Bool){1});
        I64_delete(_t898, &(Bool){1});
    }
    Bool_delete(is_neg, &(Bool){1});
    I64 *_t918 = malloc(sizeof(I64));
    *_t918 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), DEREF(_t918));
    I64_delete(_t918, &(Bool){1});
    while (1) {
        I64 *_t900 = malloc(sizeof(I64));
        *_t900 = 0;
        Bool *_wcond899 = I64_gt(v, _t900);
        I64_delete(_t900, &(Bool){1});
        if (DEREF(_wcond899)) {
        } else {
            Bool_delete(_wcond899, &(Bool){1});
            break;
        }
        Bool_delete(_wcond899, &(Bool){1});
        I64 *_t901 = malloc(sizeof(I64));
        *_t901 = 10;
        I64 *_t902 = malloc(sizeof(I64)); *_t902 = I64_mod(DEREF(v), DEREF(_t901));
        I64_delete(_t901, &(Bool){1});
        I64 *_t903 = malloc(sizeof(I64));
        *_t903 = 48;
        I64 *_t904 = malloc(sizeof(I64)); *_t904 = I64_add(DEREF(_t902), DEREF(_t903));
        I64_delete(_t902, &(Bool){1});
        I64_delete(_t903, &(Bool){1});
        void *_t905 = ptr_add(buf, DEREF(i));
        U8 *_t906 = U8_from_i64(_t904);
        I64_delete(_t904, &(Bool){1});
        I64 *_t907 = malloc(sizeof(I64));
        *_t907 = 1;
        memcpy(_t905, _t906, DEREF(_t907));
        U8_delete(_t906, &(Bool){1});
        I64_delete(_t907, &(Bool){1});
        I64 *_t908 = malloc(sizeof(I64));
        *_t908 = 10;
        I64 *_t909 = malloc(sizeof(I64)); *_t909 = I64_div(DEREF(v), DEREF(_t908));
        I64_delete(_t908, &(Bool){1});
        *v = DEREF(_t909);
        I64_delete(_t909, &(Bool){1});
        I64 *_t910 = malloc(sizeof(I64));
        *_t910 = 1;
        U64 *_t911 = malloc(sizeof(U64)); *_t911 = U64_sub(DEREF(i), DEREF(_t910));
        I64_delete(_t910, &(Bool){1});
        *i = DEREF(_t911);
        U64_delete(_t911, &(Bool){1});
    }
    U64_delete(i, &(Bool){1});
    I64_delete(v, &(Bool){1});
    I64 *_t919 = malloc(sizeof(I64));
    *_t919 = 0;
    void *_t920 = ptr_add(buf, DEREF(total));
    U8 *_t921 = U8_from_i64(_t919);
    I64_delete(_t919, &(Bool){1});
    I64 *_t922 = malloc(sizeof(I64));
    *_t922 = 1;
    memcpy(_t920, _t921, DEREF(_t922));
    U8_delete(_t921, &(Bool){1});
    I64_delete(_t922, &(Bool){1});
    U64 *_t923 = U64_clone(total);
    U64 *_t924 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t925 = malloc(sizeof(Str));
    _t925->c_str = buf;
    _t925->count = DEREF(_t923);
    _t925->cap = DEREF(_t924);
    U64_delete(_t923, &(Bool){1});
    U64_delete(_t924, &(Bool){1});
    return _t925;
}

static I64 * I64_neg(I64 * a) {
    I64 *_t926 = malloc(sizeof(I64));
    *_t926 = 0;
    I64 *_t927 = malloc(sizeof(I64)); *_t927 = I64_sub(DEREF(_t926), DEREF(a));
    I64_delete(_t926, &(Bool){1});
    return _t927;
}

static I64 * I64_abs(I64 * a) {
    I64 *_t930 = malloc(sizeof(I64));
    *_t930 = 0;
    Bool *_t931 = I64_lt(a, _t930);
    I64_delete(_t930, &(Bool){1});
    if (DEREF(_t931)) {
        I64 *_t928 = malloc(sizeof(I64));
        *_t928 = 0;
        I64 *_t929 = malloc(sizeof(I64)); *_t929 = I64_sub(DEREF(_t928), DEREF(a));
        I64_delete(_t928, &(Bool){1});
        Bool_delete(_t931, &(Bool){1});
        return _t929;
    }
    Bool_delete(_t931, &(Bool){1});
    I64 *_t932 = I64_clone(a);
    return _t932;
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static Bool * I64_lt(I64 * a, I64 * b) {
    I64 *_t934 = malloc(sizeof(I64));
    *_t934 = 0;
    I64 *_t935 = malloc(sizeof(I64));
    *_t935 = 1;
    I64 *_t936 = malloc(sizeof(I64)); *_t936 = I64_cmp(DEREF(a), DEREF(b));
    I64 *_t937 = malloc(sizeof(I64)); *_t937 = I64_sub(DEREF(_t934), DEREF(_t935));
    I64_delete(_t934, &(Bool){1});
    I64_delete(_t935, &(Bool){1});
    Bool *_t938 = malloc(sizeof(Bool)); *_t938 = I64_eq(DEREF(_t936), DEREF(_t937));
    I64_delete(_t936, &(Bool){1});
    I64_delete(_t937, &(Bool){1});
    return _t938;
}

static Bool * I64_gt(I64 * a, I64 * b) {
    I64 *_t939 = malloc(sizeof(I64)); *_t939 = I64_cmp(DEREF(a), DEREF(b));
    I64 *_t940 = malloc(sizeof(I64));
    *_t940 = 1;
    Bool *_t941 = malloc(sizeof(Bool)); *_t941 = I64_eq(DEREF(_t939), DEREF(_t940));
    I64_delete(_t939, &(Bool){1});
    I64_delete(_t940, &(Bool){1});
    return _t941;
}

static Bool * I64_neq(I64 * a, I64 * b) {
    Bool *_t942 = malloc(sizeof(Bool)); *_t942 = I64_eq(DEREF(a), DEREF(b));
    Bool *_t943 = malloc(sizeof(Bool)); *_t943 = Bool_not(DEREF(_t942));
    Bool_delete(_t942, &(Bool){1});
    return _t943;
}

static Bool * I64_lte(I64 * a, I64 * b) {
    Bool *_t944 = I64_gt(a, b);
    Bool *_t945 = malloc(sizeof(Bool)); *_t945 = Bool_not(DEREF(_t944));
    Bool_delete(_t944, &(Bool){1});
    return _t945;
}

static Bool * I64_gte(I64 * a, I64 * b) {
    Bool *_t946 = I64_lt(a, b);
    Bool *_t947 = malloc(sizeof(Bool)); *_t947 = Bool_not(DEREF(_t946));
    Bool_delete(_t946, &(Bool){1});
    return _t947;
}

Range * Range_new(U64 start, U64 end) {
    U64 *_t948 = U64_clone(&(U64){start});
    U64 *_t949 = U64_clone(&(U64){end});
    Range *_t950 = malloc(sizeof(Range));
    _t950->start = DEREF(_t948);
    _t950->end = DEREF(_t949);
    U64_delete(_t948, &(Bool){1});
    U64_delete(_t949, &(Bool){1});
    return _t950;
}

U64 * Range_len(Range * self) {
    Bool *_t952 = U64_lte(&self->start, &self->end);
    if (DEREF(_t952)) {
        U64 *_t951 = malloc(sizeof(U64)); *_t951 = U64_sub(self->end, self->start);
        Bool_delete(_t952, &(Bool){1});
        return _t951;
    }
    Bool_delete(_t952, &(Bool){1});
    U64 *_t953 = malloc(sizeof(U64)); *_t953 = U64_sub(self->start, self->end);
    return _t953;
}

U64 * Range_get(Range * self, U64 i) {
    Bool *_t955 = U64_lte(&self->start, &self->end);
    if (DEREF(_t955)) {
        U64 *_t954 = malloc(sizeof(U64)); *_t954 = U64_add(self->start, i);
        Bool_delete(_t955, &(Bool){1});
        return _t954;
    }
    Bool_delete(_t955, &(Bool){1});
    U64 *_t956 = malloc(sizeof(U64)); *_t956 = U64_sub(self->start, i);
    return _t956;
}

Range * Range_clone(Range * val) {
    Range *_t957 = malloc(sizeof(Range));
    _t957->start = val->start;
    _t957->end = val->end;
    return _t957;
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

static Str * Bool_to_str(Bool * b) {
    if (DEREF(b)) {
        Str *_t959 = Str_lit("true", 4ULL);
        return _t959;
    } else {
        Str *_t960 = Str_lit("false", 5ULL);
        return _t960;
    }
}

static I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool *_t965 = malloc(sizeof(Bool)); *_t965 = Bool_eq(DEREF(a), DEREF(b));
    if (DEREF(_t965)) {
        I64 *_t961 = malloc(sizeof(I64));
        *_t961 = 0;
        Bool_delete(_t965, &(Bool){1});
        return _t961;
    }
    Bool_delete(_t965, &(Bool){1});
    if (DEREF(b)) {
        I64 *_t962 = malloc(sizeof(I64));
        *_t962 = 0;
        I64 *_t963 = malloc(sizeof(I64));
        *_t963 = 1;
        I64 *_t964 = malloc(sizeof(I64)); *_t964 = I64_sub(DEREF(_t962), DEREF(_t963));
        I64_delete(_t962, &(Bool){1});
        I64_delete(_t963, &(Bool){1});
        return _t964;
    }
    I64 *_t966 = malloc(sizeof(I64));
    *_t966 = 1;
    return _t966;
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static Bool * Bool_lt(Bool * a, Bool * b) {
    I64 *_t968 = malloc(sizeof(I64));
    *_t968 = 0;
    I64 *_t969 = malloc(sizeof(I64));
    *_t969 = 1;
    I64 *_t970 = Bool_cmp(a, b);
    I64 *_t971 = malloc(sizeof(I64)); *_t971 = I64_sub(DEREF(_t968), DEREF(_t969));
    I64_delete(_t968, &(Bool){1});
    I64_delete(_t969, &(Bool){1});
    Bool *_t972 = malloc(sizeof(Bool)); *_t972 = I64_eq(DEREF(_t970), DEREF(_t971));
    I64_delete(_t970, &(Bool){1});
    I64_delete(_t971, &(Bool){1});
    return _t972;
}

static Bool * Bool_gt(Bool * a, Bool * b) {
    I64 *_t973 = Bool_cmp(a, b);
    I64 *_t974 = malloc(sizeof(I64));
    *_t974 = 1;
    Bool *_t975 = malloc(sizeof(Bool)); *_t975 = I64_eq(DEREF(_t973), DEREF(_t974));
    I64_delete(_t973, &(Bool){1});
    I64_delete(_t974, &(Bool){1});
    return _t975;
}

static Bool * Bool_neq(Bool * a, Bool * b) {
    Bool *_t976 = malloc(sizeof(Bool)); *_t976 = Bool_eq(DEREF(a), DEREF(b));
    Bool *_t977 = malloc(sizeof(Bool)); *_t977 = Bool_not(DEREF(_t976));
    Bool_delete(_t976, &(Bool){1});
    return _t977;
}

static Bool * Bool_lte(Bool * a, Bool * b) {
    Bool *_t978 = Bool_gt(a, b);
    Bool *_t979 = malloc(sizeof(Bool)); *_t979 = Bool_not(DEREF(_t978));
    Bool_delete(_t978, &(Bool){1});
    return _t979;
}

static Bool * Bool_gte(Bool * a, Bool * b) {
    Bool *_t980 = Bool_lt(a, b);
    Bool *_t981 = malloc(sizeof(Bool)); *_t981 = Bool_not(DEREF(_t980));
    Bool_delete(_t980, &(Bool){1});
    return _t981;
}

void println(Array * parts) {
    {
        U64 *_fi982 = malloc(sizeof(U64));
        *_fi982 = 0;
        while (1) {
            U64 *_t984 = Array_len(parts);
            Bool *_wcond983 = U64_lt(_fi982, _t984);
            U64_delete(_t984, &(Bool){1});
            if (DEREF(_wcond983)) {
            } else {
                Bool_delete(_wcond983, &(Bool){1});
                break;
            }
            Bool_delete(_wcond983, &(Bool){1});
            Str *s = Array_get(parts, _fi982);
            I64 *_t985 = malloc(sizeof(I64));
            *_t985 = 1;
            U64 *_t986 = malloc(sizeof(U64)); *_t986 = U64_add(DEREF(_fi982), DEREF(_t985));
            I64_delete(_t985, &(Bool){1});
            *_fi982 = DEREF(_t986);
            U64_delete(_t986, &(Bool){1});
            print_single(s);
        }
        U64_delete(_fi982, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    {
        U64 *_fi987 = malloc(sizeof(U64));
        *_fi987 = 0;
        while (1) {
            U64 *_t989 = Array_len(parts);
            Bool *_wcond988 = U64_lt(_fi987, _t989);
            U64_delete(_t989, &(Bool){1});
            if (DEREF(_wcond988)) {
            } else {
                Bool_delete(_wcond988, &(Bool){1});
                break;
            }
            Bool_delete(_wcond988, &(Bool){1});
            Str *s = Array_get(parts, _fi987);
            I64 *_t990 = malloc(sizeof(I64));
            *_t990 = 1;
            U64 *_t991 = malloc(sizeof(U64)); *_t991 = U64_add(DEREF(_fi987), DEREF(_t990));
            I64_delete(_t990, &(Bool){1});
            *_fi987 = DEREF(_t991);
            U64_delete(_t991, &(Bool){1});
            print_single(s);
        }
        U64_delete(_fi987, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 *total = malloc(sizeof(U64));
    *total = 0;
    {
        U64 *_fi992 = malloc(sizeof(U64));
        *_fi992 = 0;
        while (1) {
            U64 *_t994 = Array_len(parts);
            Bool *_wcond993 = U64_lt(_fi992, _t994);
            U64_delete(_t994, &(Bool){1});
            if (DEREF(_wcond993)) {
            } else {
                Bool_delete(_wcond993, &(Bool){1});
                break;
            }
            Bool_delete(_wcond993, &(Bool){1});
            Str *s = Array_get(parts, _fi992);
            I64 *_t995 = malloc(sizeof(I64));
            *_t995 = 1;
            U64 *_t996 = malloc(sizeof(U64)); *_t996 = U64_add(DEREF(_fi992), DEREF(_t995));
            I64_delete(_t995, &(Bool){1});
            *_fi992 = DEREF(_t996);
            U64_delete(_t996, &(Bool){1});
            U64 *_t997 = Str_len(s);
            U64 *_t998 = malloc(sizeof(U64)); *_t998 = U64_add(DEREF(total), DEREF(_t997));
            U64_delete(_t997, &(Bool){1});
            *total = DEREF(_t998);
            U64_delete(_t998, &(Bool){1});
        }
        U64_delete(_fi992, &(Bool){1});
    }
    U8 *buf = malloc(DEREF(total));
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    {
        U64 *_fi999 = malloc(sizeof(U64));
        *_fi999 = 0;
        while (1) {
            U64 *_t1001 = Array_len(parts);
            Bool *_wcond1000 = U64_lt(_fi999, _t1001);
            U64_delete(_t1001, &(Bool){1});
            if (DEREF(_wcond1000)) {
            } else {
                Bool_delete(_wcond1000, &(Bool){1});
                break;
            }
            Bool_delete(_wcond1000, &(Bool){1});
            Str *s = Array_get(parts, _fi999);
            I64 *_t1002 = malloc(sizeof(I64));
            *_t1002 = 1;
            U64 *_t1003 = malloc(sizeof(U64)); *_t1003 = U64_add(DEREF(_fi999), DEREF(_t1002));
            I64_delete(_t1002, &(Bool){1});
            *_fi999 = DEREF(_t1003);
            U64_delete(_t1003, &(Bool){1});
            void *_t1004 = ptr_add(buf, DEREF(offset));
            U64 *_t1005 = Str_len(s);
            memcpy(_t1004, s->c_str, DEREF(_t1005));
            U64_delete(_t1005, &(Bool){1});
            U64 *_t1006 = Str_len(s);
            U64 *_t1007 = malloc(sizeof(U64)); *_t1007 = U64_add(DEREF(offset), DEREF(_t1006));
            U64_delete(_t1006, &(Bool){1});
            *offset = DEREF(_t1007);
            U64_delete(_t1007, &(Bool){1});
        }
        U64_delete(_fi999, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 *_t1008 = U64_clone(total);
    U64 *_t1009 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t1010 = malloc(sizeof(Str));
    _t1010->c_str = buf;
    _t1010->count = DEREF(_t1008);
    _t1010->cap = DEREF(_t1009);
    U64_delete(_t1008, &(Bool){1});
    U64_delete(_t1009, &(Bool){1});
    return _t1010;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 *status = check_cmd_status(DEREF(pid));
        I64 *_t1011 = malloc(sizeof(I64));
        *_t1011 = 0;
        I64 *_t1012 = malloc(sizeof(I64));
        *_t1012 = 1;
        I64 *_t1013 = malloc(sizeof(I64)); *_t1013 = I64_sub(DEREF(_t1011), DEREF(_t1012));
        I64_delete(_t1011, &(Bool){1});
        I64_delete(_t1012, &(Bool){1});
        Bool *_t1014 = I64_neq(status, _t1013);
        I64_delete(_t1013, &(Bool){1});
        if (DEREF(_t1014)) {
            Bool_delete(_t1014, &(Bool){1});
            return status;
        }
        Bool_delete(_t1014, &(Bool){1});
        I64_delete(status, &(Bool){1});
        I64 *_t1015 = malloc(sizeof(I64));
        *_t1015 = 50;
        sleep_ms(DEREF(_t1015));
        I64_delete(_t1015, &(Bool){1});
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 *_t1021 = Array_len(args);
        Bool *_wcond1016 = U64_lt(i, _t1021);
        U64_delete(_t1021, &(Bool){1});
        if (DEREF(_wcond1016)) {
        } else {
            Bool_delete(_wcond1016, &(Bool){1});
            break;
        }
        Bool_delete(_wcond1016, &(Bool){1});
        Str *arg = Array_get(args, i);
        I64 *_t1022 = malloc(sizeof(I64));
        *_t1022 = 0;
        Bool *_t1023 = U64_gt(i, _t1022);
        I64_delete(_t1022, &(Bool){1});
        if (DEREF(_t1023)) {
            Str *_t1017 = Str_lit(" '", 2ULL);
            Str *_t1018 = Str_concat(cmd, _t1017);
            Str_delete(_t1017, &(Bool){1});
            Str *_t1019 = Str_concat(_t1018, arg);
            Str_delete(_t1018, &(Bool){1});
            Str *_t1020 = Str_lit("'", 1ULL);
            cmd = Str_concat(_t1019, _t1020);
            Str_delete(_t1019, &(Bool){1});
            Str_delete(_t1020, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        Bool_delete(_t1023, &(Bool){1});
        I64 *_t1024 = malloc(sizeof(I64));
        *_t1024 = 1;
        U64 *_t1025 = malloc(sizeof(U64)); *_t1025 = U64_add(DEREF(i), DEREF(_t1024));
        I64_delete(_t1024, &(Bool){1});
        *i = DEREF(_t1025);
        U64_delete(_t1025, &(Bool){1});
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    Str *_t1026 = Str_lit(" > ", 3ULL);
    Str *_t1027 = Str_concat(cmd, _t1026);
    Str_delete(_t1026, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t1028 = Str_concat(_t1027, tmpf);
    Str_delete(_t1027, &(Bool){1});
    Str *_t1029 = Str_lit(" 2>&1", 5ULL);
    Str *_t1030 = Str_concat(_t1028, _t1029);
    Str_delete(_t1028, &(Bool){1});
    Str_delete(_t1029, &(Bool){1});
    I64 *pid = spawn_cmd(_t1030);
    Str_delete(_t1030, &(Bool){1});
    I64 *ec = wait_cmd(pid);
    I64_delete(pid, &(Bool){1});
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 *_t1031 = Str_size();
    memcpy(output, content, DEREF(_t1031));
    U64_delete(_t1031, &(Bool){1});
    free(content);
    return ec;
}

void panic(Str * loc_str, Array * parts) {
    Str *_t1032 = Str_lit("Str", 3ULL);
    U64 *_t1033 = Str_size();
    U64 *_t1034 = malloc(sizeof(U64));
    *_t1034 = 3;
    Array *_va16 = Array_new(_t1032, _t1033, _t1034);
    Str_delete(_t1032, &(Bool){1});
    U64_delete(_t1033, &(Bool){1});
    U64_delete(_t1034, &(Bool){1});
    U64 *_t1035 = malloc(sizeof(U64));
    *_t1035 = 0;
    Str *_t1036 = Str_clone(loc_str);
    Array_set(_va16, _t1035, _t1036);
    U64_delete(_t1035, &(Bool){1});
    U64 *_t1037 = malloc(sizeof(U64));
    *_t1037 = 1;
    Str *_t1038 = Str_lit(": panic: ", 9ULL);
    Array_set(_va16, _t1037, _t1038);
    U64_delete(_t1037, &(Bool){1});
    U64 *_t1039 = malloc(sizeof(U64));
    *_t1039 = 2;
    Str *_t1040 = format(parts);
    Array_set(_va16, _t1039, _t1040);
    U64_delete(_t1039, &(Bool){1});
    println(_va16);
    I64 *_t1041 = malloc(sizeof(I64));
    *_t1041 = 1;
    exit(DEREF(_t1041));
    I64_delete(_t1041, &(Bool){1});
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t1042 = Str_lit("Str", 3ULL);
    U64 *_t1043 = Str_size();
    U64 *_t1044 = malloc(sizeof(U64));
    *_t1044 = 2;
    Array *_va17 = Array_new(_t1042, _t1043, _t1044);
    Str_delete(_t1042, &(Bool){1});
    U64_delete(_t1043, &(Bool){1});
    U64_delete(_t1044, &(Bool){1});
    U64 *_t1045 = malloc(sizeof(U64));
    *_t1045 = 0;
    Str *_t1046 = Str_lit("TODO: ", 6ULL);
    Array_set(_va17, _t1045, _t1046);
    U64_delete(_t1045, &(Bool){1});
    U64 *_t1047 = malloc(sizeof(U64));
    *_t1047 = 1;
    Str *_t1048 = format(parts);
    Array_set(_va17, _t1047, _t1048);
    U64_delete(_t1047, &(Bool){1});
    panic(loc_str, _va17);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t1049 = Str_lit("Str", 3ULL);
    U64 *_t1050 = Str_size();
    U64 *_t1051 = malloc(sizeof(U64));
    *_t1051 = 1;
    Array *_va18 = Array_new(_t1049, _t1050, _t1051);
    Str_delete(_t1049, &(Bool){1});
    U64_delete(_t1050, &(Bool){1});
    U64_delete(_t1051, &(Bool){1});
    U64 *_t1052 = malloc(sizeof(U64));
    *_t1052 = 0;
    Str *_t1053 = Str_lit("unreachable", 11ULL);
    Array_set(_va18, _t1052, _t1053);
    U64_delete(_t1052, &(Bool){1});
    panic(loc_str, _va18);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool *_t1061 = malloc(sizeof(Bool)); *_t1061 = Bool_not(DEREF(cond));
    if (DEREF(_t1061)) {
        Str *_t1054 = Str_lit("Str", 3ULL);
        U64 *_t1055 = Str_size();
        U64 *_t1056 = malloc(sizeof(U64));
        *_t1056 = 2;
        Array *_va19 = Array_new(_t1054, _t1055, _t1056);
        Str_delete(_t1054, &(Bool){1});
        U64_delete(_t1055, &(Bool){1});
        U64_delete(_t1056, &(Bool){1});
        U64 *_t1057 = malloc(sizeof(U64));
        *_t1057 = 0;
        Str *_t1058 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va19, _t1057, _t1058);
        U64_delete(_t1057, &(Bool){1});
        U64 *_t1059 = malloc(sizeof(U64));
        *_t1059 = 1;
        Str *_t1060 = format(parts);
        Array_set(_va19, _t1059, _t1060);
        U64_delete(_t1059, &(Bool){1});
        panic(loc_str, _va19);
    }
    Bool_delete(_t1061, &(Bool){1});
    Bool *_t1062 = malloc(sizeof(Bool));
    *_t1062 = 1;
    return _t1062;
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t1063 = Str_lit("Str", 3ULL);
    U64 *_t1064 = Str_size();
    U64 *_t1065 = malloc(sizeof(U64));
    *_t1065 = 0;
    Array *_va20 = Array_new(_t1063, _t1064, _t1065);
    Str_delete(_t1063, &(Bool){1});
    U64_delete(_t1064, &(Bool){1});
    U64_delete(_t1065, &(Bool){1});
    Bool *_t1066 = assertm(loc_str, cond, _va20);
    return _t1066;
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t1067 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool *_t1068 = assertm(loc_str, cond, _t1067);
    Bool_delete(_t1068, &(Bool){1});
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool *_t1082 = I64_neq(a, b);
    if (DEREF(_t1082)) {
        Str *_t1069 = Str_lit("Str", 3ULL);
        U64 *_t1070 = Str_size();
        U64 *_t1071 = malloc(sizeof(U64));
        *_t1071 = 5;
        Array *_va21 = Array_new(_t1069, _t1070, _t1071);
        Str_delete(_t1069, &(Bool){1});
        U64_delete(_t1070, &(Bool){1});
        U64_delete(_t1071, &(Bool){1});
        U64 *_t1072 = malloc(sizeof(U64));
        *_t1072 = 0;
        Str *_t1073 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va21, _t1072, _t1073);
        U64_delete(_t1072, &(Bool){1});
        U64 *_t1074 = malloc(sizeof(U64));
        *_t1074 = 1;
        Str *_t1075 = I64_to_str(a);
        Array_set(_va21, _t1074, _t1075);
        U64_delete(_t1074, &(Bool){1});
        U64 *_t1076 = malloc(sizeof(U64));
        *_t1076 = 2;
        Str *_t1077 = Str_lit("', found '", 10ULL);
        Array_set(_va21, _t1076, _t1077);
        U64_delete(_t1076, &(Bool){1});
        U64 *_t1078 = malloc(sizeof(U64));
        *_t1078 = 3;
        Str *_t1079 = I64_to_str(b);
        Array_set(_va21, _t1078, _t1079);
        U64_delete(_t1078, &(Bool){1});
        U64 *_t1080 = malloc(sizeof(U64));
        *_t1080 = 4;
        Str *_t1081 = Str_lit("'", 1ULL);
        Array_set(_va21, _t1080, _t1081);
        U64_delete(_t1080, &(Bool){1});
        panic(loc_str, _va21);
    }
    Bool_delete(_t1082, &(Bool){1});
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool *_t1096 = Str_eq(a, b);
    Bool *_t1097 = malloc(sizeof(Bool)); *_t1097 = Bool_not(DEREF(_t1096));
    Bool_delete(_t1096, &(Bool){1});
    if (DEREF(_t1097)) {
        Str *_t1083 = Str_lit("Str", 3ULL);
        U64 *_t1084 = Str_size();
        U64 *_t1085 = malloc(sizeof(U64));
        *_t1085 = 5;
        Array *_va22 = Array_new(_t1083, _t1084, _t1085);
        Str_delete(_t1083, &(Bool){1});
        U64_delete(_t1084, &(Bool){1});
        U64_delete(_t1085, &(Bool){1});
        U64 *_t1086 = malloc(sizeof(U64));
        *_t1086 = 0;
        Str *_t1087 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va22, _t1086, _t1087);
        U64_delete(_t1086, &(Bool){1});
        U64 *_t1088 = malloc(sizeof(U64));
        *_t1088 = 1;
        Str *_t1089 = Str_clone(a);
        Array_set(_va22, _t1088, _t1089);
        U64_delete(_t1088, &(Bool){1});
        U64 *_t1090 = malloc(sizeof(U64));
        *_t1090 = 2;
        Str *_t1091 = Str_lit("', found '", 10ULL);
        Array_set(_va22, _t1090, _t1091);
        U64_delete(_t1090, &(Bool){1});
        U64 *_t1092 = malloc(sizeof(U64));
        *_t1092 = 3;
        Str *_t1093 = Str_clone(b);
        Array_set(_va22, _t1092, _t1093);
        U64_delete(_t1092, &(Bool){1});
        U64 *_t1094 = malloc(sizeof(U64));
        *_t1094 = 4;
        Str *_t1095 = Str_lit("'", 1ULL);
        Array_set(_va22, _t1094, _t1095);
        U64_delete(_t1094, &(Bool){1});
        panic(loc_str, _va22);
    }
    Bool_delete(_t1097, &(Bool){1});
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

__attribute__((constructor))
static void _til_lib_init(void) {
    _t1098 = malloc(sizeof(I64));
    *_t1098 = 0;
    _t1099 = malloc(sizeof(I64));
    *_t1099 = 1;
    _t1100 = malloc(sizeof(I64)); *_t1100 = I64_sub(DEREF(_t1098), DEREF(_t1099));
    CAP_LIT = U64_from_i64(_t1100);
    _t1101 = malloc(sizeof(I64));
    *_t1101 = 0;
    _t1102 = malloc(sizeof(I64));
    *_t1102 = 2;
    _t1103 = malloc(sizeof(I64)); *_t1103 = I64_sub(DEREF(_t1101), DEREF(_t1102));
    CAP_VIEW = U64_from_i64(_t1103);
}

