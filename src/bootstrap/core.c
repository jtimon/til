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
Bool dyn_has_method(Str *, Str *);
Array * array(Str *, Array *);
Vec * vec(Str *, Array *);
I64 * spawn_cmd(Str *);
I64 check_cmd_status(I64);
void sleep_ms(I64);
Str * readfile(Str *);
void writefile(Str *, Str *);
I64 file_mtime(Str *);
I64 clock_ms(void);
I64 get_thread_count(void);

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
static __attribute__((unused)) Str * U8_to_str(U8 * val);
static __attribute__((unused)) U8 * U8_from_i64(I64 * val);
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
U8 U8_clone(U8 * val);
void U8_delete(U8 * self, Bool * call_free);
static __attribute__((unused)) U64 * U8_size(void);
static __attribute__((unused)) Bool * U8_lt(U8 * a, U8 * b);
static __attribute__((unused)) Bool * U8_gt(U8 * a, U8 * b);
static __attribute__((unused)) Bool * U8_neq(U8 * a, U8 * b);
static __attribute__((unused)) Bool * U8_lte(U8 * a, U8 * b);
static __attribute__((unused)) Bool * U8_gte(U8 * a, U8 * b);
I64 I16_to_i64(I16 val);
static __attribute__((unused)) Str * I16_to_str(I16 * val);
static __attribute__((unused)) I16 * I16_from_i64(I64 * val);
I16 I16_add(I16 a, I16 b);
I16 I16_sub(I16 a, I16 b);
I16 I16_mul(I16 a, I16 b);
I16 I16_div(I16 a, I16 b);
I16 I16_mod(I16 a, I16 b);
I16 I16_inc(I16 a);
I16 I16_dec(I16 a);
Bool I16_eq(I16 a, I16 b);
I64 I16_cmp(I16 a, I16 b);
static __attribute__((unused)) I16 * I16_neg(I16 * a);
static __attribute__((unused)) I16 * I16_abs(I16 * a);
I16 I16_and(I16 a, I16 b);
I16 I16_or(I16 a, I16 b);
I16 I16_xor(I16 a, I16 b);
I16 I16_clone(I16 * val);
void I16_delete(I16 * self, Bool * call_free);
static __attribute__((unused)) U64 * I16_size(void);
static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b);
static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b);
I64 I32_to_i64(I32 val);
static __attribute__((unused)) Str * I32_to_str(I32 * val);
static __attribute__((unused)) I32 * I32_from_i64(I64 * val);
I32 I32_add(I32 a, I32 b);
I32 I32_sub(I32 a, I32 b);
I32 I32_mul(I32 a, I32 b);
I32 I32_div(I32 a, I32 b);
I32 I32_mod(I32 a, I32 b);
I32 I32_inc(I32 a);
I32 I32_dec(I32 a);
Bool I32_eq(I32 a, I32 b);
I64 I32_cmp(I32 a, I32 b);
static __attribute__((unused)) I32 * I32_neg(I32 * a);
static __attribute__((unused)) I32 * I32_abs(I32 * a);
I32 I32_and(I32 a, I32 b);
I32 I32_or(I32 a, I32 b);
I32 I32_xor(I32 a, I32 b);
I32 I32_clone(I32 * val);
void I32_delete(I32 * self, Bool * call_free);
static __attribute__((unused)) U64 * I32_size(void);
static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b);
static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b);
static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b);
static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b);
static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b);
I64 F32_to_i64(F32 val);
Str * F32_to_str(F32 val);
static __attribute__((unused)) F32 * F32_from_i64(I64 * val);
F32 F32_add(F32 a, F32 b);
F32 F32_sub(F32 a, F32 b);
F32 F32_mul(F32 a, F32 b);
F32 F32_div(F32 a, F32 b);
Bool F32_eq(F32 a, F32 b);
I64 F32_cmp(F32 a, F32 b);
F32 F32_clone(F32 * val);
void F32_delete(F32 * self, Bool * call_free);
static __attribute__((unused)) U64 * F32_size(void);
static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b);
static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b);
static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b);
static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b);
static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b);
I64 U32_to_i64(U32 val);
static __attribute__((unused)) Str * U32_to_str(U32 * val);
static __attribute__((unused)) U32 * U32_from_i64(I64 * val);
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
U32 U32_clone(U32 * val);
void U32_delete(U32 * self, Bool * call_free);
static __attribute__((unused)) U64 * U32_size(void);
static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b);
static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b);
I64 U64_to_i64(U64 val);
Str * U64_to_str(U64 val);
static __attribute__((unused)) U64 * U64_from_i64(I64 * val);
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
U64 U64_clone(U64 * val);
void U64_delete(U64 * self, Bool * call_free);
static __attribute__((unused)) U64 * U64_size(void);
static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b);
static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b);
static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b);
static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b);
static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b);
static __attribute__((unused)) Str * I64_to_str(I64 * val);
I64 I64_add(I64 a, I64 b);
I64 I64_sub(I64 a, I64 b);
I64 I64_mul(I64 a, I64 b);
I64 I64_div(I64 a, I64 b);
I64 I64_mod(I64 a, I64 b);
I64 I64_inc(I64 a);
I64 I64_dec(I64 a);
Bool I64_eq(I64 a, I64 b);
I64 I64_cmp(I64 a, I64 b);
static __attribute__((unused)) I64 * I64_neg(I64 * a);
static __attribute__((unused)) I64 * I64_abs(I64 * a);
I64 I64_and(I64 a, I64 b);
I64 I64_or(I64 a, I64 b);
I64 I64_xor(I64 a, I64 b);
I64 I64_clone(I64 * val);
void I64_delete(I64 * self, Bool * call_free);
static __attribute__((unused)) U64 * I64_size(void);
static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b);
static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b);
static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b);
static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b);
static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b);
Range * Range_new(U64 start, U64 end);
U64 * Range_len(Range * self);
U64 * Range_get(Range * self, U64 i);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool * call_free);
U64 * Range_size(void);
static __attribute__((unused)) Str * Bool_to_str(Bool * b);
Bool Bool_eq(Bool a, Bool b);
static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b);
Bool Bool_clone(Bool * val);
void Bool_delete(Bool * self, Bool * call_free);
static __attribute__((unused)) U64 * Bool_size(void);
static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b);
static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b);
static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b);
static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b);
static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b);
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

Bool dyn_has_cmp(Str *type_name);


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
    U64 _t1 = U64_clone(cap);
    U64 _t2 = U64_clone(elem_size);
    Array *_t3 = malloc(sizeof(Array));
    _t3->data = _t0;
    _t3->cap = _t1;
    _t3->elem_size = _t2;
    { Str *_ca = Str_clone(elem_type); _t3->elem_type = *_ca; free(_ca); }
    ;
    ;
    return _t3;
}

U64 * Array_len(Array * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U64 * i) {
    (void)self;
    Bool _t18; { Bool *_hp = U64_gte(i, &self->cap); _t18 = *_hp; free(_hp); }
    if (_t18) {
        Str *_t4 = Str_lit("Str", 3ULL);
        U64 _t5; { U64 *_hp = Str_size(); _t5 = *_hp; free(_hp); }
        U64 _t6 = 5;
        Array *_va0 = Array_new(_t4, &(U64){_t5}, &(U64){_t6});
        Str_delete(_t4, &(Bool){1});
        ;
        ;
        U64 _t7 = 0;
        Str *_t8 = Str_lit("index ", 6ULL);
        Array_set(_va0, &(U64){_t7}, _t8);
        ;
        U64 _t9 = 1;
        Str *_t10 = U64_to_str(DEREF(i));
        Array_set(_va0, &(U64){_t9}, _t10);
        ;
        U64 _t11 = 2;
        Str *_t12 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va0, &(U64){_t11}, _t12);
        ;
        U64 _t13 = 3;
        Str *_t14 = U64_to_str(self->cap);
        Array_set(_va0, &(U64){_t13}, _t14);
        ;
        U64 _t15 = 4;
        Str *_t16 = Str_lit(")", 1ULL);
        Array_set(_va0, &(U64){_t15}, _t16);
        ;
        Str *_t17 = Str_lit("Array.get", 9ULL);
        panic(_t17, _va0);
        Str_delete(_t17, &(Bool){1});
        Array_delete(_va0, &(Bool){1});
    }
    ;
    U64 *_t19 = malloc(sizeof(U64)); *_t19 = U64_mul(DEREF(i), self->elem_size);
    void *_t20 = ptr_add(self->data, DEREF(_t19));
    U64_delete(_t19, &(Bool){1});
    return _t20;
}

void Array_set(Array * self, U64 * i, void * val) {
    (void)self;
    Bool _t35; { Bool *_hp = U64_gte(i, &self->cap); _t35 = *_hp; free(_hp); }
    if (_t35) {
        Str *_t21 = Str_lit("Str", 3ULL);
        U64 _t22; { U64 *_hp = Str_size(); _t22 = *_hp; free(_hp); }
        U64 _t23 = 5;
        Array *_va1 = Array_new(_t21, &(U64){_t22}, &(U64){_t23});
        Str_delete(_t21, &(Bool){1});
        ;
        ;
        U64 _t24 = 0;
        Str *_t25 = Str_lit("index ", 6ULL);
        Array_set(_va1, &(U64){_t24}, _t25);
        ;
        U64 _t26 = 1;
        Str *_t27 = U64_to_str(DEREF(i));
        Array_set(_va1, &(U64){_t26}, _t27);
        ;
        U64 _t28 = 2;
        Str *_t29 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va1, &(U64){_t28}, _t29);
        ;
        U64 _t30 = 3;
        Str *_t31 = U64_to_str(self->cap);
        Array_set(_va1, &(U64){_t30}, _t31);
        ;
        U64 _t32 = 4;
        Str *_t33 = Str_lit(")", 1ULL);
        Array_set(_va1, &(U64){_t32}, _t33);
        ;
        Str *_t34 = Str_lit("Array.set", 9ULL);
        panic(_t34, _va1);
        Str_delete(_t34, &(Bool){1});
        Array_delete(_va1, &(Bool){1});
    }
    ;
    U64 *_t36 = malloc(sizeof(U64)); *_t36 = U64_mul(DEREF(i), self->elem_size);
    void *_t37 = ptr_add(self->data, DEREF(_t36));
    Bool _t38 = 0;
    dyn_call_delete(&self->elem_type, _t37, &(Bool){_t38});
    U64_delete(_t36, &(Bool){1});
    ;
    U64 *_t39 = malloc(sizeof(U64)); *_t39 = U64_mul(DEREF(i), self->elem_size);
    void *_t40 = ptr_add(self->data, DEREF(_t39));
    memcpy(_t40, val, self->elem_size);
    U64_delete(_t39, &(Bool){1});
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    {
        U64 _fi41 = 0;
        while (1) {
            U64 _t43 = 0;
            Range *_t44 = Range_new(_t43, self->cap);
            ;
            U64 _t45; { U64 *_hp = Range_len(_t44); _t45 = *_hp; free(_hp); }
            Range_delete(_t44, &(Bool){1});
            Bool _wcond42; { Bool *_hp = U64_lt(&(U64){_fi41}, &(U64){_t45}); _wcond42 = *_hp; free(_hp); }
            ;
            if (_wcond42) {
            } else {
                ;
                break;
            }
            ;
            U64 _t46 = 0;
            Range *_t47 = Range_new(_t46, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t47, _fi41); i = *_hp; free(_hp); }
            Range_delete(_t47, &(Bool){1});
            U64 _t48 = 1;
            U64 _t49 = U64_add(_fi41, _t48);
            ;
            _fi41 = _t49;
            ;
            U64 *_t50 = malloc(sizeof(U64)); *_t50 = U64_mul(i, self->elem_size);
            ;
            void *_t51 = ptr_add(self->data, DEREF(_t50));
            Bool _t52 = 0;
            dyn_call_delete(&self->elem_type, _t51, &(Bool){_t52});
            U64_delete(_t50, &(Bool){1});
            ;
        }
        ;
    }
    free(self->data);
    Bool _t53 = 0;
    Str_delete(&self->elem_type, &(Bool){_t53});
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U64 _t67 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t67);
    ;
    {
        U64 _fi54 = 0;
        while (1) {
            U64 _t56 = 0;
            Range *_t57 = Range_new(_t56, self->cap);
            ;
            U64 _t58; { U64 *_hp = Range_len(_t57); _t58 = *_hp; free(_hp); }
            Range_delete(_t57, &(Bool){1});
            Bool _wcond55; { Bool *_hp = U64_lt(&(U64){_fi54}, &(U64){_t58}); _wcond55 = *_hp; free(_hp); }
            ;
            if (_wcond55) {
            } else {
                ;
                break;
            }
            ;
            U64 _t59 = 0;
            Range *_t60 = Range_new(_t59, self->cap);
            ;
            U64 i; { U64 *_hp = Range_get(_t60, _fi54); i = *_hp; free(_hp); }
            Range_delete(_t60, &(Bool){1});
            U64 _t61 = 1;
            U64 _t62 = U64_add(_fi54, _t61);
            ;
            _fi54 = _t62;
            ;
            U64 *_t63 = malloc(sizeof(U64)); *_t63 = U64_mul(i, self->elem_size);
            void *_t64 = ptr_add(self->data, DEREF(_t63));
            void *cloned = dyn_call_clone(&self->elem_type, _t64);
            U64_delete(_t63, &(Bool){1});
            U64 *_t65 = malloc(sizeof(U64)); *_t65 = U64_mul(i, self->elem_size);
            ;
            void *_t66 = ptr_add(new_data, DEREF(_t65));
            memcpy(_t66, cloned, self->elem_size);
            U64_delete(_t65, &(Bool){1});
            free(cloned);
        }
        ;
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
    Bool _t82; { Bool *_hp = Str_is_empty(key_type); _t82 = *_hp; free(_hp); }
    Bool _t83 = Bool_not(_t82);
    ;
    if (_t83) {
        Bool _t80 = dyn_has_cmp(key_type);
        Bool _t81 = Bool_not(_t80);
        ;
        if (_t81) {
            Str *_t70 = Str_lit("Str", 3ULL);
            U64 _t71; { U64 *_hp = Str_size(); _t71 = *_hp; free(_hp); }
            U64 _t72 = 3;
            Array *_va2 = Array_new(_t70, &(U64){_t71}, &(U64){_t72});
            Str_delete(_t70, &(Bool){1});
            ;
            ;
            U64 _t73 = 0;
            Str *_t74 = Str_lit("type ", 5ULL);
            Array_set(_va2, &(U64){_t73}, _t74);
            ;
            U64 _t75 = 1;
            Str *_t76 = Str_clone(key_type);
            Array_set(_va2, &(U64){_t75}, _t76);
            ;
            U64 _t77 = 2;
            Str *_t78 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va2, &(U64){_t77}, _t78);
            ;
            Str *_t79 = Str_lit("Map.new", 7ULL);
            panic(_t79, _va2);
            Str_delete(_t79, &(Bool){1});
            Array_delete(_va2, &(Bool){1});
        }
        ;
    }
    ;
    void *_t84 = malloc(DEREF(key_size));
    void *_t85 = malloc(DEREF(val_size));
    U64 _t86 = 0;
    I64 _t87 = 1;
    U64 _t88 = U64_clone(key_size);
    U64 _t89 = U64_clone(val_size);
    Map *_t90 = malloc(sizeof(Map));
    _t90->key_data = _t84;
    _t90->val_data = _t85;
    _t90->count = _t86;
    _t90->cap = _t87;
    _t90->key_size = _t88;
    { Str *_ca = Str_clone(key_type); _t90->key_type = *_ca; free(_ca); }
    _t90->val_size = _t89;
    { Str *_ca = Str_clone(val_type); _t90->val_type = *_ca; free(_ca); }
    ;
    ;
    ;
    ;
    return _t90;
}

U64 * Map_len(Map * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Map_has(Map * self, void * key) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond91; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond91 = *_hp; free(_hp); }
        if (_wcond91) {
        } else {
            ;
            break;
        }
        ;
        U64 _t98 = U64_sub(hi, lo);
        U64 _t99 = 2;
        U64 _t100 = U64_div(_t98, _t99);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t100);
        ;
        U64 *_t101 = malloc(sizeof(U64)); *_t101 = U64_mul(DEREF(mid), self->key_size);
        void *_t102 = ptr_add(self->key_data, DEREF(_t101));
        I64 *c = dyn_call_cmp(&self->key_type, _t102, key);
        U64_delete(_t101, &(Bool){1});
        I64 _t103 = 0;
        Bool _t104; { Bool *_hp = I64_lt(c, &(I64){_t103}); _t104 = *_hp; free(_hp); }
        ;
        if (_t104) {
            U64 _t92 = 1;
            U64 _t93 = U64_add(DEREF(mid), _t92);
            ;
            lo = _t93;
            ;
        } else {
            I64 _t96 = 0;
            Bool _t97; { Bool *_hp = I64_gt(c, &(I64){_t96}); _t97 = *_hp; free(_hp); }
            ;
            if (_t97) {
                U64 _t94 = U64_clone(mid);
                hi = _t94;
                ;
            } else {
                Bool _t95 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t95; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t105 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t105; return _r; }
}

void * Map_get(Map * self, void * key) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond106; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond106 = *_hp; free(_hp); }
        if (_wcond106) {
        } else {
            ;
            break;
        }
        ;
        U64 _t114 = U64_sub(hi, lo);
        U64 _t115 = 2;
        U64 _t116 = U64_div(_t114, _t115);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t116);
        ;
        U64 *_t117 = malloc(sizeof(U64)); *_t117 = U64_mul(DEREF(mid), self->key_size);
        void *_t118 = ptr_add(self->key_data, DEREF(_t117));
        I64 *c = dyn_call_cmp(&self->key_type, _t118, key);
        U64_delete(_t117, &(Bool){1});
        I64 _t119 = 0;
        Bool _t120; { Bool *_hp = I64_lt(c, &(I64){_t119}); _t120 = *_hp; free(_hp); }
        ;
        if (_t120) {
            U64 _t107 = 1;
            U64 _t108 = U64_add(DEREF(mid), _t107);
            ;
            lo = _t108;
            ;
        } else {
            I64 _t112 = 0;
            Bool _t113; { Bool *_hp = I64_gt(c, &(I64){_t112}); _t113 = *_hp; free(_hp); }
            ;
            if (_t113) {
                U64 _t109 = U64_clone(mid);
                hi = _t109;
                ;
            } else {
                U64 *_t110 = malloc(sizeof(U64)); *_t110 = U64_mul(DEREF(mid), self->val_size);
                void *_t111 = ptr_add(self->val_data, DEREF(_t110));
                U64_delete(_t110, &(Bool){1});
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                return _t111;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Str *_t121 = Str_lit("Str", 3ULL);
    U64 _t122; { U64 *_hp = Str_size(); _t122 = *_hp; free(_hp); }
    U64 _t123 = 1;
    Array *_va3 = Array_new(_t121, &(U64){_t122}, &(U64){_t123});
    Str_delete(_t121, &(Bool){1});
    ;
    ;
    U64 _t124 = 0;
    Str *_t125 = Str_lit("key not found", 13ULL);
    Array_set(_va3, &(U64){_t124}, _t125);
    ;
    Str *_t126 = Str_lit("Map.get", 7ULL);
    panic(_t126, _va3);
    Str_delete(_t126, &(Bool){1});
    Array_delete(_va3, &(Bool){1});
    U64 *_t127 = malloc(sizeof(U64));
    *_t127 = 0;
    void *_t128 = ptr_add(self->val_data, DEREF(_t127));
    U64_delete(_t127, &(Bool){1});
    return _t128;
}

void Map_set(Map * self, void * key, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond129; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond129 = *_hp; free(_hp); }
        if (_wcond129) {
        } else {
            ;
            break;
        }
        ;
        U64 _t138 = U64_sub(hi, lo);
        U64 _t139 = 2;
        U64 _t140 = U64_div(_t138, _t139);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t140);
        ;
        U64 *_t141 = malloc(sizeof(U64)); *_t141 = U64_mul(DEREF(mid), self->key_size);
        void *_t142 = ptr_add(self->key_data, DEREF(_t141));
        I64 *c = dyn_call_cmp(&self->key_type, _t142, key);
        U64_delete(_t141, &(Bool){1});
        I64 _t143 = 0;
        Bool _t144; { Bool *_hp = I64_lt(c, &(I64){_t143}); _t144 = *_hp; free(_hp); }
        ;
        if (_t144) {
            U64 _t130 = 1;
            U64 _t131 = U64_add(DEREF(mid), _t130);
            ;
            lo = _t131;
            ;
        } else {
            I64 _t136 = 0;
            Bool _t137; { Bool *_hp = I64_gt(c, &(I64){_t136}); _t137 = *_hp; free(_hp); }
            ;
            if (_t137) {
                U64 _t132 = U64_clone(mid);
                hi = _t132;
                ;
            } else {
                Bool _t133 = 1;
                found = _t133;
                ;
                U64 _t134 = U64_clone(mid);
                lo = _t134;
                ;
                U64 _t135 = U64_clone(mid);
                hi = _t135;
                ;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    if (found) {
        Bool _t149; { Bool *_hp = Str_is_empty(&self->key_type); _t149 = *_hp; free(_hp); }
        Bool _t150 = Bool_not(_t149);
        ;
        if (_t150) {
            Bool _t145 = 0;
            dyn_call_delete(&self->key_type, key, &(Bool){_t145});
            ;
        }
        ;
        free(key);
        Bool _t151; { Bool *_hp = Str_is_empty(&self->val_type); _t151 = *_hp; free(_hp); }
        Bool _t152 = Bool_not(_t151);
        ;
        if (_t152) {
            U64 *_t146 = malloc(sizeof(U64)); *_t146 = U64_mul(lo, self->val_size);
            void *_t147 = ptr_add(self->val_data, DEREF(_t146));
            Bool _t148 = 0;
            dyn_call_delete(&self->val_type, _t147, &(Bool){_t148});
            U64_delete(_t146, &(Bool){1});
            ;
        }
        ;
        U64 *_t153 = malloc(sizeof(U64)); *_t153 = U64_mul(lo, self->val_size);
        void *_t154 = ptr_add(self->val_data, DEREF(_t153));
        memcpy(_t154, val, self->val_size);
        U64_delete(_t153, &(Bool){1});
        free(val);
    } else {
        Bool _t161 = U64_eq(self->count, self->cap);
        if (_t161) {
            U64 _t155 = 2;
            U64 new_cap = U64_mul(self->cap, _t155);
            ;
            U64 _t156 = U64_mul(new_cap, self->key_size);
            void *_t157 = realloc(self->key_data, _t156);
            ;
            self->key_data = _t157;
            U64 _t158 = U64_mul(new_cap, self->val_size);
            void *_t159 = realloc(self->val_data, _t158);
            ;
            self->val_data = _t159;
            U64 _t160 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t160;
            ;
        }
        ;
        U64 _t162 = 1;
        U64 _t163 = U64_add(lo, _t162);
        ;
        U64 *_t164 = malloc(sizeof(U64)); *_t164 = U64_mul(_t163, self->key_size);
        ;
        U64 *_t165 = malloc(sizeof(U64)); *_t165 = U64_mul(lo, self->key_size);
        U64 _t166 = U64_sub(self->count, lo);
        void *_t167 = ptr_add(self->key_data, DEREF(_t164));
        void *_t168 = ptr_add(self->key_data, DEREF(_t165));
        U64 _t169 = U64_mul(_t166, self->key_size);
        ;
        memmove(_t167, _t168, _t169);
        U64_delete(_t164, &(Bool){1});
        U64_delete(_t165, &(Bool){1});
        ;
        U64 _t170 = 1;
        U64 _t171 = U64_add(lo, _t170);
        ;
        U64 *_t172 = malloc(sizeof(U64)); *_t172 = U64_mul(_t171, self->val_size);
        ;
        U64 *_t173 = malloc(sizeof(U64)); *_t173 = U64_mul(lo, self->val_size);
        U64 _t174 = U64_sub(self->count, lo);
        void *_t175 = ptr_add(self->val_data, DEREF(_t172));
        void *_t176 = ptr_add(self->val_data, DEREF(_t173));
        U64 _t177 = U64_mul(_t174, self->val_size);
        ;
        memmove(_t175, _t176, _t177);
        U64_delete(_t172, &(Bool){1});
        U64_delete(_t173, &(Bool){1});
        ;
        U64 *_t178 = malloc(sizeof(U64)); *_t178 = U64_mul(lo, self->key_size);
        void *_t179 = ptr_add(self->key_data, DEREF(_t178));
        memcpy(_t179, key, self->key_size);
        U64_delete(_t178, &(Bool){1});
        U64 *_t180 = malloc(sizeof(U64)); *_t180 = U64_mul(lo, self->val_size);
        void *_t181 = ptr_add(self->val_data, DEREF(_t180));
        memcpy(_t181, val, self->val_size);
        U64_delete(_t180, &(Bool){1});
        free(key);
        free(val);
        U64 _t182 = 1;
        U64 _t183 = U64_add(self->count, _t182);
        ;
        self->count = _t183;
        ;
    }
    ;
    ;
}

void Map_delete(Map * self, Bool * call_free) {
    (void)self;
    Bool _t210; { Bool *_hp = Str_is_empty(&self->key_type); _t210 = *_hp; free(_hp); }
    Bool _t211 = Bool_not(_t210);
    ;
    if (_t211) {
        {
            U64 _fi184 = 0;
            while (1) {
                U64 _t186 = 0;
                Range *_t187 = Range_new(_t186, self->count);
                ;
                U64 _t188; { U64 *_hp = Range_len(_t187); _t188 = *_hp; free(_hp); }
                Range_delete(_t187, &(Bool){1});
                Bool _wcond185; { Bool *_hp = U64_lt(&(U64){_fi184}, &(U64){_t188}); _wcond185 = *_hp; free(_hp); }
                ;
                if (_wcond185) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t189 = 0;
                Range *_t190 = Range_new(_t189, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t190, _fi184); i = *_hp; free(_hp); }
                Range_delete(_t190, &(Bool){1});
                U64 _t191 = 1;
                U64 _t192 = U64_add(_fi184, _t191);
                ;
                _fi184 = _t192;
                ;
                U64 *_t193 = malloc(sizeof(U64)); *_t193 = U64_mul(i, self->key_size);
                ;
                void *_t194 = ptr_add(self->key_data, DEREF(_t193));
                Bool _t195 = 0;
                dyn_call_delete(&self->key_type, _t194, &(Bool){_t195});
                U64_delete(_t193, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    Bool _t212; { Bool *_hp = Str_is_empty(&self->val_type); _t212 = *_hp; free(_hp); }
    Bool _t213 = Bool_not(_t212);
    ;
    if (_t213) {
        {
            U64 _fi196 = 0;
            while (1) {
                U64 _t198 = 0;
                Range *_t199 = Range_new(_t198, self->count);
                ;
                U64 _t200; { U64 *_hp = Range_len(_t199); _t200 = *_hp; free(_hp); }
                Range_delete(_t199, &(Bool){1});
                Bool _wcond197; { Bool *_hp = U64_lt(&(U64){_fi196}, &(U64){_t200}); _wcond197 = *_hp; free(_hp); }
                ;
                if (_wcond197) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t201 = 0;
                Range *_t202 = Range_new(_t201, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t202, _fi196); i = *_hp; free(_hp); }
                Range_delete(_t202, &(Bool){1});
                U64 _t203 = 1;
                U64 _t204 = U64_add(_fi196, _t203);
                ;
                _fi196 = _t204;
                ;
                U64 *_t205 = malloc(sizeof(U64)); *_t205 = U64_mul(i, self->val_size);
                ;
                void *_t206 = ptr_add(self->val_data, DEREF(_t205));
                Bool _t207 = 0;
                dyn_call_delete(&self->val_type, _t206, &(Bool){_t207});
                U64_delete(_t205, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->key_data);
    free(self->val_data);
    Bool _t214; { Bool *_hp = Str_is_empty(&self->key_type); _t214 = *_hp; free(_hp); }
    Bool _t215 = Bool_not(_t214);
    ;
    if (_t215) {
        Bool _t208 = 0;
        Str_delete(&self->key_type, &(Bool){_t208});
        ;
    }
    ;
    Bool _t216; { Bool *_hp = Str_is_empty(&self->val_type); _t216 = *_hp; free(_hp); }
    Bool _t217 = Bool_not(_t216);
    ;
    if (_t217) {
        Bool _t209 = 0;
        Str_delete(&self->val_type, &(Bool){_t209});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Map * Map_clone(Map * self) {
    (void)self;
    U64 _t235 = U64_mul(self->cap, self->key_size);
    U8 *new_keys = malloc(_t235);
    ;
    U64 _t236 = U64_mul(self->cap, self->val_size);
    U8 *new_vals = malloc(_t236);
    ;
    {
        U64 _fi218 = 0;
        while (1) {
            U64 _t220 = 0;
            Range *_t221 = Range_new(_t220, self->count);
            ;
            U64 _t222; { U64 *_hp = Range_len(_t221); _t222 = *_hp; free(_hp); }
            Range_delete(_t221, &(Bool){1});
            Bool _wcond219; { Bool *_hp = U64_lt(&(U64){_fi218}, &(U64){_t222}); _wcond219 = *_hp; free(_hp); }
            ;
            if (_wcond219) {
            } else {
                ;
                break;
            }
            ;
            U64 _t223 = 0;
            Range *_t224 = Range_new(_t223, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t224, _fi218); i = *_hp; free(_hp); }
            Range_delete(_t224, &(Bool){1});
            U64 _t225 = 1;
            U64 _t226 = U64_add(_fi218, _t225);
            ;
            _fi218 = _t226;
            ;
            U64 *_t227 = malloc(sizeof(U64)); *_t227 = U64_mul(i, self->key_size);
            void *_t228 = ptr_add(self->key_data, DEREF(_t227));
            void *ck = dyn_call_clone(&self->key_type, _t228);
            U64_delete(_t227, &(Bool){1});
            U64 *_t229 = malloc(sizeof(U64)); *_t229 = U64_mul(i, self->key_size);
            void *_t230 = ptr_add(new_keys, DEREF(_t229));
            memcpy(_t230, ck, self->key_size);
            U64_delete(_t229, &(Bool){1});
            free(ck);
            U64 *_t231 = malloc(sizeof(U64)); *_t231 = U64_mul(i, self->val_size);
            void *_t232 = ptr_add(self->val_data, DEREF(_t231));
            void *cv = dyn_call_clone(&self->val_type, _t232);
            U64_delete(_t231, &(Bool){1});
            U64 *_t233 = malloc(sizeof(U64)); *_t233 = U64_mul(i, self->val_size);
            ;
            void *_t234 = ptr_add(new_vals, DEREF(_t233));
            memcpy(_t234, cv, self->val_size);
            U64_delete(_t233, &(Bool){1});
            free(cv);
        }
        ;
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
    Bool _t251; { Bool *_hp = Str_is_empty(elem_type); _t251 = *_hp; free(_hp); }
    Bool _t252 = Bool_not(_t251);
    ;
    if (_t252) {
        Bool _t249 = dyn_has_cmp(elem_type);
        Bool _t250 = Bool_not(_t249);
        ;
        if (_t250) {
            Str *_t239 = Str_lit("Str", 3ULL);
            U64 _t240; { U64 *_hp = Str_size(); _t240 = *_hp; free(_hp); }
            U64 _t241 = 3;
            Array *_va4 = Array_new(_t239, &(U64){_t240}, &(U64){_t241});
            Str_delete(_t239, &(Bool){1});
            ;
            ;
            U64 _t242 = 0;
            Str *_t243 = Str_lit("type ", 5ULL);
            Array_set(_va4, &(U64){_t242}, _t243);
            ;
            U64 _t244 = 1;
            Str *_t245 = Str_clone(elem_type);
            Array_set(_va4, &(U64){_t244}, _t245);
            ;
            U64 _t246 = 2;
            Str *_t247 = Str_lit(" must implement cmp", 19ULL);
            Array_set(_va4, &(U64){_t246}, _t247);
            ;
            Str *_t248 = Str_lit("Set.new", 7ULL);
            panic(_t248, _va4);
            Str_delete(_t248, &(Bool){1});
            Array_delete(_va4, &(Bool){1});
        }
        ;
    }
    ;
    void *_t253 = malloc(DEREF(elem_size));
    U64 _t254 = 0;
    I64 _t255 = 1;
    U64 _t256 = U64_clone(elem_size);
    Set *_t257 = malloc(sizeof(Set));
    _t257->data = _t253;
    _t257->count = _t254;
    _t257->cap = _t255;
    _t257->elem_size = _t256;
    { Str *_ca = Str_clone(elem_type); _t257->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t257;
}

U64 * Set_len(Set * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

Bool * Set_has(Set * self, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    while (1) {
        Bool _wcond258; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond258 = *_hp; free(_hp); }
        if (_wcond258) {
        } else {
            ;
            break;
        }
        ;
        U64 _t265 = U64_sub(hi, lo);
        U64 _t266 = 2;
        U64 _t267 = U64_div(_t265, _t266);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t267);
        ;
        U64 *_t268 = malloc(sizeof(U64)); *_t268 = U64_mul(DEREF(mid), self->elem_size);
        void *_t269 = ptr_add(self->data, DEREF(_t268));
        I64 *c = dyn_call_cmp(&self->elem_type, _t269, val);
        U64_delete(_t268, &(Bool){1});
        I64 _t270 = 0;
        Bool _t271; { Bool *_hp = I64_lt(c, &(I64){_t270}); _t271 = *_hp; free(_hp); }
        ;
        if (_t271) {
            U64 _t259 = 1;
            U64 _t260 = U64_add(DEREF(mid), _t259);
            ;
            lo = _t260;
            ;
        } else {
            I64 _t263 = 0;
            Bool _t264; { Bool *_hp = I64_gt(c, &(I64){_t263}); _t264 = *_hp; free(_hp); }
            ;
            if (_t264) {
                U64 _t261 = U64_clone(mid);
                hi = _t261;
                ;
            } else {
                Bool _t262 = 1;
                ;
                ;
                I64_delete(c, &(Bool){1});
                U64_delete(mid, &(Bool){1});
                ;
                ;
                { Bool *_r = malloc(sizeof(Bool)); *_r = _t262; return _r; }
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    ;
    Bool _t272 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t272; return _r; }
}

void Set_add(Set * self, void * val) {
    (void)self;
    U64 lo = 0;
    U64 hi = self->count;
    Bool found = 0;
    while (1) {
        Bool _wcond273; { Bool *_hp = U64_lt(&(U64){lo}, &(U64){hi}); _wcond273 = *_hp; free(_hp); }
        if (_wcond273) {
        } else {
            ;
            break;
        }
        ;
        U64 _t282 = U64_sub(hi, lo);
        U64 _t283 = 2;
        U64 _t284 = U64_div(_t282, _t283);
        ;
        ;
        U64 *mid = malloc(sizeof(U64)); *mid = U64_add(lo, _t284);
        ;
        U64 *_t285 = malloc(sizeof(U64)); *_t285 = U64_mul(DEREF(mid), self->elem_size);
        void *_t286 = ptr_add(self->data, DEREF(_t285));
        I64 *c = dyn_call_cmp(&self->elem_type, _t286, val);
        U64_delete(_t285, &(Bool){1});
        I64 _t287 = 0;
        Bool _t288; { Bool *_hp = I64_lt(c, &(I64){_t287}); _t288 = *_hp; free(_hp); }
        ;
        if (_t288) {
            U64 _t274 = 1;
            U64 _t275 = U64_add(DEREF(mid), _t274);
            ;
            lo = _t275;
            ;
        } else {
            I64 _t280 = 0;
            Bool _t281; { Bool *_hp = I64_gt(c, &(I64){_t280}); _t281 = *_hp; free(_hp); }
            ;
            if (_t281) {
                U64 _t276 = U64_clone(mid);
                hi = _t276;
                ;
            } else {
                Bool _t277 = 1;
                found = _t277;
                ;
                U64 _t278 = U64_clone(mid);
                lo = _t278;
                ;
                U64 _t279 = U64_clone(mid);
                hi = _t279;
                ;
            }
            ;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64_delete(mid, &(Bool){1});
    }
    ;
    if (found) {
        Bool _t290; { Bool *_hp = Str_is_empty(&self->elem_type); _t290 = *_hp; free(_hp); }
        Bool _t291 = Bool_not(_t290);
        ;
        if (_t291) {
            Bool _t289 = 0;
            dyn_call_delete(&self->elem_type, val, &(Bool){_t289});
            ;
        }
        ;
        free(val);
    } else {
        Bool _t296 = U64_eq(self->count, self->cap);
        if (_t296) {
            U64 _t292 = 2;
            U64 new_cap = U64_mul(self->cap, _t292);
            ;
            U64 _t293 = U64_mul(new_cap, self->elem_size);
            void *_t294 = realloc(self->data, _t293);
            ;
            self->data = _t294;
            U64 _t295 = U64_clone(&(U64){new_cap});
            ;
            self->cap = _t295;
            ;
        }
        ;
        U64 _t297 = 1;
        U64 _t298 = U64_add(lo, _t297);
        ;
        U64 *_t299 = malloc(sizeof(U64)); *_t299 = U64_mul(_t298, self->elem_size);
        ;
        U64 *_t300 = malloc(sizeof(U64)); *_t300 = U64_mul(lo, self->elem_size);
        U64 _t301 = U64_sub(self->count, lo);
        void *_t302 = ptr_add(self->data, DEREF(_t299));
        void *_t303 = ptr_add(self->data, DEREF(_t300));
        U64 _t304 = U64_mul(_t301, self->elem_size);
        ;
        memmove(_t302, _t303, _t304);
        U64_delete(_t299, &(Bool){1});
        U64_delete(_t300, &(Bool){1});
        ;
        U64 *_t305 = malloc(sizeof(U64)); *_t305 = U64_mul(lo, self->elem_size);
        void *_t306 = ptr_add(self->data, DEREF(_t305));
        memcpy(_t306, val, self->elem_size);
        U64_delete(_t305, &(Bool){1});
        free(val);
        U64 _t307 = 1;
        U64 _t308 = U64_add(self->count, _t307);
        ;
        self->count = _t308;
        ;
    }
    ;
    ;
}

void Set_delete(Set * self, Bool * call_free) {
    (void)self;
    Bool _t322; { Bool *_hp = Str_is_empty(&self->elem_type); _t322 = *_hp; free(_hp); }
    Bool _t323 = Bool_not(_t322);
    ;
    if (_t323) {
        {
            U64 _fi309 = 0;
            while (1) {
                U64 _t311 = 0;
                Range *_t312 = Range_new(_t311, self->count);
                ;
                U64 _t313; { U64 *_hp = Range_len(_t312); _t313 = *_hp; free(_hp); }
                Range_delete(_t312, &(Bool){1});
                Bool _wcond310; { Bool *_hp = U64_lt(&(U64){_fi309}, &(U64){_t313}); _wcond310 = *_hp; free(_hp); }
                ;
                if (_wcond310) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t314 = 0;
                Range *_t315 = Range_new(_t314, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t315, _fi309); i = *_hp; free(_hp); }
                Range_delete(_t315, &(Bool){1});
                U64 _t316 = 1;
                U64 _t317 = U64_add(_fi309, _t316);
                ;
                _fi309 = _t317;
                ;
                U64 *_t318 = malloc(sizeof(U64)); *_t318 = U64_mul(i, self->elem_size);
                ;
                void *_t319 = ptr_add(self->data, DEREF(_t318));
                Bool _t320 = 0;
                dyn_call_delete(&self->elem_type, _t319, &(Bool){_t320});
                U64_delete(_t318, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t324; { Bool *_hp = Str_is_empty(&self->elem_type); _t324 = *_hp; free(_hp); }
    Bool _t325 = Bool_not(_t324);
    ;
    if (_t325) {
        Bool _t321 = 0;
        Str_delete(&self->elem_type, &(Bool){_t321});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Set * Set_clone(Set * self) {
    (void)self;
    U64 _t339 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t339);
    ;
    {
        U64 _fi326 = 0;
        while (1) {
            U64 _t328 = 0;
            Range *_t329 = Range_new(_t328, self->count);
            ;
            U64 _t330; { U64 *_hp = Range_len(_t329); _t330 = *_hp; free(_hp); }
            Range_delete(_t329, &(Bool){1});
            Bool _wcond327; { Bool *_hp = U64_lt(&(U64){_fi326}, &(U64){_t330}); _wcond327 = *_hp; free(_hp); }
            ;
            if (_wcond327) {
            } else {
                ;
                break;
            }
            ;
            U64 _t331 = 0;
            Range *_t332 = Range_new(_t331, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t332, _fi326); i = *_hp; free(_hp); }
            Range_delete(_t332, &(Bool){1});
            U64 _t333 = 1;
            U64 _t334 = U64_add(_fi326, _t333);
            ;
            _fi326 = _t334;
            ;
            U64 *_t335 = malloc(sizeof(U64)); *_t335 = U64_mul(i, self->elem_size);
            void *_t336 = ptr_add(self->data, DEREF(_t335));
            void *cloned = dyn_call_clone(&self->elem_type, _t336);
            U64_delete(_t335, &(Bool){1});
            U64 *_t337 = malloc(sizeof(U64)); *_t337 = U64_mul(i, self->elem_size);
            ;
            void *_t338 = ptr_add(new_data, DEREF(_t337));
            memcpy(_t338, cloned, self->elem_size);
            U64_delete(_t337, &(Bool){1});
            free(cloned);
        }
        ;
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
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

U8 * Str_get(Str * self, U64 * i) {
    (void)self;
    Bool _t348; { Bool *_hp = U64_gte(i, &self->count); _t348 = *_hp; free(_hp); }
    if (_t348) {
        Str *_t342 = Str_lit("Str", 3ULL);
        U64 _t343; { U64 *_hp = Str_size(); _t343 = *_hp; free(_hp); }
        U64 _t344 = 1;
        Array *_va5 = Array_new(_t342, &(U64){_t343}, &(U64){_t344});
        Str_delete(_t342, &(Bool){1});
        ;
        ;
        U64 _t345 = 0;
        Str *_t346 = Str_lit("index out of bounds", 19ULL);
        Array_set(_va5, &(U64){_t345}, _t346);
        ;
        Str *_t347 = Str_lit("Str.get", 7ULL);
        panic(_t347, _va5);
        Str_delete(_t347, &(Bool){1});
        Array_delete(_va5, &(Bool){1});
    }
    ;
    void *_t349 = ptr_add(self->c_str, DEREF(i));
    return _t349;
}

I64 * Str_cmp(Str * a, Str * b) {
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    U64 min_len = a->count;
    Bool _t355; { Bool *_hp = U64_lt(&b->count, &a->count); _t355 = *_hp; free(_hp); }
    if (_t355) {
        min_len = b->count;
    }
    ;
    while (1) {
        Bool _wcond350; { Bool *_hp = U64_lt(i, &(U64){min_len}); _wcond350 = *_hp; free(_hp); }
        if (_wcond350) {
        } else {
            ;
            break;
        }
        ;
        U8 *ab = Str_get(a, i);
        U8 *bb = Str_get(b, i);
        I64 *c = malloc(sizeof(I64)); *c = U8_cmp(DEREF(ab), DEREF(bb));
        I64 _t351 = 0;
        Bool _t352; { Bool *_hp = I64_neq(c, &(I64){_t351}); _t352 = *_hp; free(_hp); }
        ;
        if (_t352) {
            ;
            U64_delete(i, &(Bool){1});
            ;
            return c;
        }
        ;
        I64_delete(c, &(Bool){1});
        U64 _t353 = 1;
        U64 _t354 = U64_add(DEREF(i), _t353);
        ;
        *i = _t354;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t356 = U64_cmp(a->count, b->count);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t356; return _r; }
}

Str * Str_concat(Str * a, Str * b) {
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(a->count, b->count);
    U64 _t357 = 1;
    U64 _t358 = U64_add(DEREF(new_len), _t357);
    ;
    U8 *new_data = malloc(_t358);
    ;
    memcpy(new_data, a->c_str, a->count);
    void *_t359 = ptr_add(new_data, a->count);
    memcpy(_t359, b->c_str, b->count);
    I64 _t360 = 0;
    void *_t361 = ptr_add(new_data, DEREF(new_len));
    U8 _t362; { U8 *_hp = U8_from_i64(&(I64){_t360}); _t362 = *_hp; free(_hp); }
    ;
    U64 _t363 = 1;
    memcpy(_t361, &(U8){_t362}, _t363);
    ;
    ;
    U64 _t364 = U64_clone(new_len);
    U64 _t365 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t366 = malloc(sizeof(Str));
    _t366->c_str = new_data;
    _t366->count = _t364;
    _t366->cap = _t365;
    ;
    ;
    return _t366;
}

Str * Str_with_capacity(U64 * n) {
    U64 _t367 = 1;
    U64 _t368 = U64_add(DEREF(n), _t367);
    ;
    U8 *buf = malloc(_t368);
    ;
    I64 _t369 = 0;
    U8 _t370; { U8 *_hp = U8_from_i64(&(I64){_t369}); _t370 = *_hp; free(_hp); }
    ;
    U64 _t371 = 1;
    memcpy(buf, &(U8){_t370}, _t371);
    ;
    ;
    I64 _t372 = 0;
    U64 _t373 = U64_clone(n);
    Str *_t374 = malloc(sizeof(Str));
    _t374->c_str = buf;
    _t374->count = _t372;
    _t374->cap = _t373;
    ;
    ;
    return _t374;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    Bool _t387; { Bool *_hp = U64_gte(&self->cap, CAP_VIEW); _t387 = *_hp; free(_hp); }
    if (_t387) {
        Str *_t375 = Str_lit("Str", 3ULL);
        U64 _t376; { U64 *_hp = Str_size(); _t376 = *_hp; free(_hp); }
        U64 _t377 = 1;
        Array *_va6 = Array_new(_t375, &(U64){_t376}, &(U64){_t377});
        Str_delete(_t375, &(Bool){1});
        ;
        ;
        U64 _t378 = 0;
        Str *_t379 = Str_lit("cannot mutate a string view or literal", 38ULL);
        Array_set(_va6, &(U64){_t378}, _t379);
        ;
        Str *_t380 = Str_lit("Str.push_str", 12ULL);
        panic(_t380, _va6);
        Str_delete(_t380, &(Bool){1});
        Array_delete(_va6, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool _t388; { Bool *_hp = U64_gt(new_len, &self->cap); _t388 = *_hp; free(_hp); }
    if (_t388) {
        Str *_t381 = Str_lit("Str", 3ULL);
        U64 _t382; { U64 *_hp = Str_size(); _t382 = *_hp; free(_hp); }
        U64 _t383 = 1;
        Array *_va7 = Array_new(_t381, &(U64){_t382}, &(U64){_t383});
        Str_delete(_t381, &(Bool){1});
        ;
        ;
        U64 _t384 = 0;
        Str *_t385 = Str_lit("capacity exceeded", 17ULL);
        Array_set(_va7, &(U64){_t384}, _t385);
        ;
        Str *_t386 = Str_lit("Str.push_str", 12ULL);
        panic(_t386, _va7);
        Str_delete(_t386, &(Bool){1});
        Array_delete(_va7, &(Bool){1});
    }
    ;
    void *_t389 = ptr_add(self->c_str, self->count);
    memcpy(_t389, s->c_str, s->count);
    U64 _t390 = U64_clone(new_len);
    self->count = _t390;
    ;
    I64 _t391 = 0;
    void *_t392 = ptr_add(self->c_str, DEREF(new_len));
    U8 _t393; { U8 *_hp = U8_from_i64(&(I64){_t391}); _t393 = *_hp; free(_hp); }
    ;
    U64 _t394 = 1;
    memcpy(_t392, &(U8){_t393}, _t394);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    U64 _t395 = 1;
    U64 _t396 = U64_add(val->count, _t395);
    ;
    U8 *new_data = malloc(_t396);
    ;
    memcpy(new_data, val->c_str, val->count);
    I64 _t397 = 0;
    void *_t398 = ptr_add(new_data, val->count);
    U8 _t399; { U8 *_hp = U8_from_i64(&(I64){_t397}); _t399 = *_hp; free(_hp); }
    ;
    U64 _t400 = 1;
    memcpy(_t398, &(U8){_t399}, _t400);
    ;
    ;
    Str *_t401 = malloc(sizeof(Str));
    _t401->c_str = new_data;
    _t401->count = val->count;
    _t401->cap = val->count;
    return _t401;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    Bool _t402; { Bool *_hp = U64_lt(&self->cap, CAP_VIEW); _t402 = *_hp; free(_hp); }
    if (_t402) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t403 = Str_clone(val);
    return _t403;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    U64 ln = U64_clone(n);
    Bool _t405; { Bool *_hp = U64_gt(st, &s->count); _t405 = *_hp; free(_hp); }
    if (_t405) {
        *st = s->count;
    }
    ;
    U64 _t406 = U64_add(DEREF(st), ln);
    Bool _t407; { Bool *_hp = U64_gt(&(U64){_t406}, &s->count); _t407 = *_hp; free(_hp); }
    ;
    if (_t407) {
        U64 _t404 = U64_sub(s->count, DEREF(st));
        ln = _t404;
        ;
    }
    ;
    void *_t408 = ptr_add(s->c_str, DEREF(st));
    U64 _t409 = U64_clone(&(U64){ln});
    ;
    U64 _t410 = U64_clone(CAP_VIEW);
    Str *_t411 = malloc(sizeof(Str));
    _t411->c_str = _t408;
    _t411->count = _t409;
    _t411->cap = _t410;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t411;
}

Bool * Str_contains(Str * a, Str * b) {
    U64 _t425 = 0;
    Bool _t426 = U64_eq(b->count, _t425);
    ;
    if (_t426) {
        Bool _t412 = 1;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t412; return _r; }
    }
    ;
    Bool _t427; { Bool *_hp = U64_gt(&b->count, &a->count); _t427 = *_hp; free(_hp); }
    if (_t427) {
        Bool _t413 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t413; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t422 = U64_sub(a->count, b->count);
        Bool _wcond414; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t422}); _wcond414 = *_hp; free(_hp); }
        ;
        if (_wcond414) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond415; { Bool *_hp = U64_lt(j, &b->count); _wcond415 = *_hp; free(_hp); }
            if (_wcond415) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t417 = malloc(sizeof(U64)); *_t417 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(a, _t417);
            U8 *bc = Str_get(b, j);
            Bool _t418; { Bool *_hp = U8_neq(ac, bc); _t418 = *_hp; free(_hp); }
            U64_delete(_t417, &(Bool){1});
            if (_t418) {
                Bool _t416 = 0;
                found = _t416;
                ;
            }
            ;
            U64 _t419 = 1;
            U64 _t420 = U64_add(DEREF(j), _t419);
            ;
            *j = _t420;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t421 = 1;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t421; return _r; }
        }
        ;
        U64 _t423 = 1;
        U64 _t424 = U64_add(i, _t423);
        ;
        i = _t424;
        ;
    }
    ;
    Bool _t428 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t428; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool _t435; { Bool *_hp = U64_gt(&b->count, &a->count); _t435 = *_hp; free(_hp); }
    if (_t435) {
        Bool _t429 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t429; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond430; { Bool *_hp = U64_lt(i, &b->count); _wcond430 = *_hp; free(_hp); }
        if (_wcond430) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool _t432; { Bool *_hp = U8_neq(ac, bc); _t432 = *_hp; free(_hp); }
        if (_t432) {
            Bool _t431 = 0;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t431; return _r; }
        }
        ;
        U64 _t433 = 1;
        U64 _t434 = U64_add(DEREF(i), _t433);
        ;
        *i = _t434;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t436 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t436; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool _t444; { Bool *_hp = U64_gt(&b->count, &a->count); _t444 = *_hp; free(_hp); }
    if (_t444) {
        Bool _t437 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t437; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond438; { Bool *_hp = U64_lt(i, &b->count); _wcond438 = *_hp; free(_hp); }
        if (_wcond438) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t440 = malloc(sizeof(U64)); *_t440 = U64_add(offset, DEREF(i));
        U8 *ac = Str_get(a, _t440);
        U8 *bc = Str_get(b, i);
        Bool _t441; { Bool *_hp = U8_neq(ac, bc); _t441 = *_hp; free(_hp); }
        U64_delete(_t440, &(Bool){1});
        if (_t441) {
            Bool _t439 = 0;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t439; return _r; }
        }
        ;
        U64 _t442 = 1;
        U64 _t443 = U64_add(DEREF(i), _t442);
        ;
        *i = _t443;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t445 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t445; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t446 = 0;
    Bool _t447 = U64_eq(self->count, _t446);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t447; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    U64 _t465 = 0;
    Bool _t466 = U64_eq(needle->count, _t465);
    ;
    if (_t466) {
        I64 _t448 = 0;
        I64 _t449 = 1;
        I64 _t450 = I64_sub(_t448, _t449);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t450; return _r; }
    }
    ;
    Bool _t467; { Bool *_hp = U64_gt(&needle->count, &self->count); _t467 = *_hp; free(_hp); }
    if (_t467) {
        I64 _t451 = 0;
        I64 _t452 = 1;
        I64 _t453 = I64_sub(_t451, _t452);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t453; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t462 = U64_sub(self->count, needle->count);
        Bool _wcond454; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t462}); _wcond454 = *_hp; free(_hp); }
        ;
        if (_wcond454) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond455; { Bool *_hp = U64_lt(j, &needle->count); _wcond455 = *_hp; free(_hp); }
            if (_wcond455) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t457 = malloc(sizeof(U64)); *_t457 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t457);
            U8 *bc = Str_get(needle, j);
            Bool _t458; { Bool *_hp = U8_neq(ac, bc); _t458 = *_hp; free(_hp); }
            U64_delete(_t457, &(Bool){1});
            if (_t458) {
                Bool _t456 = 0;
                found = _t456;
                ;
            }
            ;
            U64 _t459 = 1;
            U64 _t460 = U64_add(DEREF(j), _t459);
            ;
            *j = _t460;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t461 = U64_to_i64(i);
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t461; return _r; }
        }
        ;
        U64 _t463 = 1;
        U64 _t464 = U64_add(i, _t463);
        ;
        i = _t464;
        ;
    }
    ;
    I64 _t468 = 0;
    I64 _t469 = 1;
    I64 _t470 = I64_sub(_t468, _t469);
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t470; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    U64 _t488 = 0;
    Bool _t489 = U64_eq(needle->count, _t488);
    ;
    if (_t489) {
        I64 _t471 = 0;
        I64 _t472 = 1;
        I64 _t473 = I64_sub(_t471, _t472);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t473; return _r; }
    }
    ;
    Bool _t490; { Bool *_hp = U64_gt(&needle->count, &self->count); _t490 = *_hp; free(_hp); }
    if (_t490) {
        I64 _t474 = 0;
        I64 _t475 = 1;
        I64 _t476 = I64_sub(_t474, _t475);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t476; return _r; }
    }
    ;
    I64 _t491 = 0;
    I64 _t492 = 1;
    I64 last = I64_sub(_t491, _t492);
    ;
    ;
    U64 i = 0;
    while (1) {
        U64 _t485 = U64_sub(self->count, needle->count);
        Bool _wcond477; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t485}); _wcond477 = *_hp; free(_hp); }
        ;
        if (_wcond477) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond478; { Bool *_hp = U64_lt(j, &needle->count); _wcond478 = *_hp; free(_hp); }
            if (_wcond478) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t480 = malloc(sizeof(U64)); *_t480 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t480);
            U8 *bc = Str_get(needle, j);
            Bool _t481; { Bool *_hp = U8_neq(ac, bc); _t481 = *_hp; free(_hp); }
            U64_delete(_t480, &(Bool){1});
            if (_t481) {
                Bool _t479 = 0;
                found = _t479;
                ;
            }
            ;
            U64 _t482 = 1;
            U64 _t483 = U64_add(DEREF(j), _t482);
            ;
            *j = _t483;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t484 = U64_to_i64(i);
            last = _t484;
            ;
        }
        ;
        U64 _t486 = 1;
        U64 _t487 = U64_add(i, _t486);
        ;
        i = _t487;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    U64 _t508 = 0;
    Bool _t509 = U64_eq(from->count, _t508);
    ;
    if (_t509) {
        Str *_t493 = Str_clone(self);
        ;
        return _t493;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 start = 0;
    while (1) {
        U64 _t495 = U64_sub(self->count, from->count);
        Bool _wcond494; { Bool *_hp = U64_lte(&(U64){start}, &(U64){_t495}); _wcond494 = *_hp; free(_hp); }
        ;
        if (_wcond494) {
        } else {
            ;
            break;
        }
        ;
        U64 _t496 = U64_sub(self->count, start);
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t496});
        ;
        I64 pos; { I64 *_hp = Str_find(rest, from); pos = *_hp; free(_hp); }
        I64 _t497 = 0;
        I64 _t498 = 1;
        I64 _t499 = I64_sub(_t497, _t498);
        ;
        ;
        Bool _t500 = I64_eq(pos, _t499);
        ;
        if (_t500) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t501; { U64 *_hp = U64_from_i64(&(I64){pos}); _t501 = *_hp; free(_hp); }
        Str *_t502 = Str_substr(self, &(U64){start}, &(U64){_t501});
        ;
        result = Str_concat(result, _t502);
        Str_delete(_t502, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t503; { U64 *_hp = U64_from_i64(&(I64){pos}); _t503 = *_hp; free(_hp); }
        ;
        U64 _t504 = U64_add(start, _t503);
        ;
        U64 _t505 = U64_add(_t504, from->count);
        ;
        start = _t505;
        ;
    }
    Bool _t510; { Bool *_hp = U64_lt(&(U64){start}, &self->count); _t510 = *_hp; free(_hp); }
    if (_t510) {
        U64 _t506 = U64_sub(self->count, start);
        Str *_t507 = Str_substr(self, &(U64){start}, &(U64){_t506});
        ;
        result = Str_concat(result, _t507);
        Str_delete(_t507, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    U64 _t511 = 1;
    Str *_t512 = Str_substr(self, i, &(U64){_t511});
    ;
    return _t512;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    Bool _t515; { Bool *_hp = Str_starts_with(self, prefix); _t515 = *_hp; free(_hp); }
    if (_t515) {
        U64 _t513 = U64_sub(self->count, prefix->count);
        Str *_t514 = Str_substr(self, &prefix->count, &(U64){_t513});
        ;
        ;
        return _t514;
    }
    ;
    Str *_t516 = Str_clone(self);
    return _t516;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    Bool _t520; { Bool *_hp = Str_ends_with(self, suffix); _t520 = *_hp; free(_hp); }
    if (_t520) {
        U64 _t517 = 0;
        U64 _t518 = U64_sub(self->count, suffix->count);
        Str *_t519 = Str_substr(self, &(U64){_t517}, &(U64){_t518});
        ;
        ;
        ;
        return _t519;
    }
    ;
    Str *_t521 = Str_clone(self);
    return _t521;
}

Str * Str_from_byte(U8 * byte) {
    U64 _t522 = 2;
    U8 *buf = malloc(_t522);
    ;
    U64 _t523 = 1;
    memcpy(buf, byte, _t523);
    ;
    U64 *_t524 = malloc(sizeof(U64));
    *_t524 = 1;
    I64 _t525 = 0;
    void *_t526 = ptr_add(buf, DEREF(_t524));
    U8 _t527; { U8 *_hp = U8_from_i64(&(I64){_t525}); _t527 = *_hp; free(_hp); }
    ;
    U64 _t528 = 1;
    memcpy(_t526, &(U8){_t527}, _t528);
    U64_delete(_t524, &(Bool){1});
    ;
    ;
    I64 _t529 = 1;
    I64 _t530 = 1;
    Str *_t531 = malloc(sizeof(Str));
    _t531->c_str = buf;
    _t531->count = _t529;
    _t531->cap = _t530;
    ;
    ;
    return _t531;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t572 = 0;
    Bool _t573 = U64_eq(self->count, _t572);
    ;
    if (_t573) {
        Str *_t532 = Str_lit("Str", 3ULL);
        U64 _t533; { U64 *_hp = Str_size(); _t533 = *_hp; free(_hp); }
        U64 _t534 = 1;
        Array *_va8 = Array_new(_t532, &(U64){_t533}, &(U64){_t534});
        Str_delete(_t532, &(Bool){1});
        ;
        ;
        U64 _t535 = 0;
        Str *_t536 = Str_lit("empty string", 12ULL);
        Array_set(_va8, &(U64){_t535}, _t536);
        ;
        Str *_t537 = Str_lit("Str.to_i64", 10ULL);
        panic(_t537, _va8);
        Str_delete(_t537, &(Bool){1});
        Array_delete(_va8, &(Bool){1});
    }
    ;
    I64 result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool neg = 0;
    U64 *_t574 = malloc(sizeof(U64));
    *_t574 = 0;
    U8 *first = Str_get(self, _t574);
    I64 _t575 = 45;
    U8 _t576; { U8 *_hp = U8_from_i64(&(I64){_t575}); _t576 = *_hp; free(_hp); }
    ;
    Bool _t577 = U8_eq(DEREF(first), _t576);
    U64_delete(_t574, &(Bool){1});
    ;
    if (_t577) {
        Bool _t538 = 1;
        neg = _t538;
        ;
        I64 _t539 = 1;
        U64 _t540; { U64 *_hp = U64_from_i64(&(I64){_t539}); _t540 = *_hp; free(_hp); }
        ;
        *i = _t540;
        ;
    }
    ;
    Bool _t578 = U64_eq(DEREF(i), self->count);
    if (_t578) {
        Str *_t541 = Str_lit("Str", 3ULL);
        U64 _t542; { U64 *_hp = Str_size(); _t542 = *_hp; free(_hp); }
        U64 _t543 = 1;
        Array *_va9 = Array_new(_t541, &(U64){_t542}, &(U64){_t543});
        Str_delete(_t541, &(Bool){1});
        ;
        ;
        U64 _t544 = 0;
        Str *_t545 = Str_lit("no digits", 9ULL);
        Array_set(_va9, &(U64){_t544}, _t545);
        ;
        Str *_t546 = Str_lit("Str.to_i64", 10ULL);
        panic(_t546, _va9);
        Str_delete(_t546, &(Bool){1});
        Array_delete(_va9, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond547; { Bool *_hp = U64_lt(i, &self->count); _wcond547 = *_hp; free(_hp); }
        if (_wcond547) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        I64 _t558 = U8_to_i64(DEREF(ch));
        I64 _t559 = 48;
        I64 d = I64_sub(_t558, _t559);
        ;
        ;
        I64 _t560 = 0;
        I64 _t561 = 9;
        Bool _t562; { Bool *_hp = I64_lt(&(I64){d}, &(I64){_t560}); _t562 = *_hp; free(_hp); }
        ;
        Bool _t563; { Bool *_hp = I64_gt(&(I64){d}, &(I64){_t561}); _t563 = *_hp; free(_hp); }
        ;
        Bool _t564 = Bool_or(_t562, _t563);
        ;
        ;
        if (_t564) {
            Str *_t548 = Str_lit("Str", 3ULL);
            U64 _t549; { U64 *_hp = Str_size(); _t549 = *_hp; free(_hp); }
            U64 _t550 = 3;
            Array *_va10 = Array_new(_t548, &(U64){_t549}, &(U64){_t550});
            Str_delete(_t548, &(Bool){1});
            ;
            ;
            U64 _t551 = 0;
            Str *_t552 = Str_lit("invalid char in '", 17ULL);
            Array_set(_va10, &(U64){_t551}, _t552);
            ;
            U64 _t553 = 1;
            Str *_t554 = Str_clone(self);
            Array_set(_va10, &(U64){_t553}, _t554);
            ;
            U64 _t555 = 2;
            Str *_t556 = Str_lit("'", 1ULL);
            Array_set(_va10, &(U64){_t555}, _t556);
            ;
            Str *_t557 = Str_lit("Str.to_i64", 10ULL);
            panic(_t557, _va10);
            Str_delete(_t557, &(Bool){1});
            Array_delete(_va10, &(Bool){1});
        }
        ;
        I64 _t565 = 10;
        I64 _t566 = I64_mul(result, _t565);
        ;
        I64 _t567 = I64_add(_t566, d);
        ;
        ;
        result = _t567;
        ;
        U64 _t568 = 1;
        U64 _t569 = U64_add(DEREF(i), _t568);
        ;
        *i = _t569;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t570 = 0;
        I64 _t571 = I64_sub(_t570, result);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t571; return _r; }
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = result; return _r; }
}

U64 *Str_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Str);
    return r;
}

Bool * Str_eq(Str * a, Str * b) {
    I64 _t580; { I64 *_hp = Str_cmp(a, b); _t580 = *_hp; free(_hp); }
    I64 _t581 = 0;
    Bool _t582 = I64_eq(_t580, _t581);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t582; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    I64 _t583 = 0;
    I64 _t584 = 1;
    I64 _t585; { I64 *_hp = Str_cmp(a, b); _t585 = *_hp; free(_hp); }
    I64 _t586 = I64_sub(_t583, _t584);
    ;
    ;
    Bool _t587 = I64_eq(_t585, _t586);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t587; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    I64 _t588; { I64 *_hp = Str_cmp(a, b); _t588 = *_hp; free(_hp); }
    I64 _t589 = 1;
    Bool _t590 = I64_eq(_t588, _t589);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t590; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    Bool _t591; { Bool *_hp = Str_eq(a, b); _t591 = *_hp; free(_hp); }
    Bool _t592 = Bool_not(_t591);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t592; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    Bool _t593; { Bool *_hp = Str_gt(a, b); _t593 = *_hp; free(_hp); }
    Bool _t594 = Bool_not(_t593);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t594; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    Bool _t595; { Bool *_hp = Str_lt(a, b); _t595 = *_hp; free(_hp); }
    Bool _t596 = Bool_not(_t595);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t596; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t597 = malloc(DEREF(elem_size));
    U64 _t598 = 0;
    I64 _t599 = 1;
    U64 _t600 = U64_clone(elem_size);
    Vec *_t601 = malloc(sizeof(Vec));
    _t601->data = _t597;
    _t601->count = _t598;
    _t601->cap = _t599;
    _t601->elem_size = _t600;
    { Str *_ca = Str_clone(elem_type); _t601->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t601;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    Bool _t606 = U64_eq(self->count, self->cap);
    if (_t606) {
        U64 _t602 = 2;
        U64 new_cap = U64_mul(self->cap, _t602);
        ;
        U64 _t603 = U64_mul(new_cap, self->elem_size);
        void *_t604 = realloc(self->data, _t603);
        ;
        self->data = _t604;
        U64 _t605 = U64_clone(&(U64){new_cap});
        ;
        self->cap = _t605;
        ;
    }
    ;
    U64 *_t607 = malloc(sizeof(U64)); *_t607 = U64_mul(self->count, self->elem_size);
    void *_t608 = ptr_add(self->data, DEREF(_t607));
    memcpy(_t608, val, self->elem_size);
    U64_delete(_t607, &(Bool){1});
    free(val);
    U64 _t609 = 1;
    U64 _t610 = U64_add(self->count, _t609);
    ;
    self->count = _t610;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    Bool _t625; { Bool *_hp = U64_gte(i, &self->count); _t625 = *_hp; free(_hp); }
    if (_t625) {
        Str *_t611 = Str_lit("Str", 3ULL);
        U64 _t612; { U64 *_hp = Str_size(); _t612 = *_hp; free(_hp); }
        U64 _t613 = 5;
        Array *_va11 = Array_new(_t611, &(U64){_t612}, &(U64){_t613});
        Str_delete(_t611, &(Bool){1});
        ;
        ;
        U64 _t614 = 0;
        Str *_t615 = Str_lit("index ", 6ULL);
        Array_set(_va11, &(U64){_t614}, _t615);
        ;
        U64 _t616 = 1;
        Str *_t617 = U64_to_str(DEREF(i));
        Array_set(_va11, &(U64){_t616}, _t617);
        ;
        U64 _t618 = 2;
        Str *_t619 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va11, &(U64){_t618}, _t619);
        ;
        U64 _t620 = 3;
        Str *_t621 = U64_to_str(self->count);
        Array_set(_va11, &(U64){_t620}, _t621);
        ;
        U64 _t622 = 4;
        Str *_t623 = Str_lit(")", 1ULL);
        Array_set(_va11, &(U64){_t622}, _t623);
        ;
        Str *_t624 = Str_lit("Vec.get", 7ULL);
        panic(_t624, _va11);
        Str_delete(_t624, &(Bool){1});
        Array_delete(_va11, &(Bool){1});
    }
    ;
    U64 *_t626 = malloc(sizeof(U64)); *_t626 = U64_mul(DEREF(i), self->elem_size);
    void *_t627 = ptr_add(self->data, DEREF(_t626));
    U64_delete(_t626, &(Bool){1});
    return _t627;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    Bool _t641; { Bool *_hp = Str_is_empty(&self->elem_type); _t641 = *_hp; free(_hp); }
    Bool _t642 = Bool_not(_t641);
    ;
    if (_t642) {
        {
            U64 _fi628 = 0;
            while (1) {
                U64 _t630 = 0;
                Range *_t631 = Range_new(_t630, self->count);
                ;
                U64 _t632; { U64 *_hp = Range_len(_t631); _t632 = *_hp; free(_hp); }
                Range_delete(_t631, &(Bool){1});
                Bool _wcond629; { Bool *_hp = U64_lt(&(U64){_fi628}, &(U64){_t632}); _wcond629 = *_hp; free(_hp); }
                ;
                if (_wcond629) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t633 = 0;
                Range *_t634 = Range_new(_t633, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t634, _fi628); i = *_hp; free(_hp); }
                Range_delete(_t634, &(Bool){1});
                U64 _t635 = 1;
                U64 _t636 = U64_add(_fi628, _t635);
                ;
                _fi628 = _t636;
                ;
                U64 *_t637 = malloc(sizeof(U64)); *_t637 = U64_mul(i, self->elem_size);
                ;
                void *_t638 = ptr_add(self->data, DEREF(_t637));
                Bool _t639 = 0;
                dyn_call_delete(&self->elem_type, _t638, &(Bool){_t639});
                U64_delete(_t637, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t643; { Bool *_hp = Str_is_empty(&self->elem_type); _t643 = *_hp; free(_hp); }
    Bool _t644 = Bool_not(_t643);
    ;
    if (_t644) {
        Bool _t640 = 0;
        Str_delete(&self->elem_type, &(Bool){_t640});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t658 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t658);
    ;
    {
        U64 _fi645 = 0;
        while (1) {
            U64 _t647 = 0;
            Range *_t648 = Range_new(_t647, self->count);
            ;
            U64 _t649; { U64 *_hp = Range_len(_t648); _t649 = *_hp; free(_hp); }
            Range_delete(_t648, &(Bool){1});
            Bool _wcond646; { Bool *_hp = U64_lt(&(U64){_fi645}, &(U64){_t649}); _wcond646 = *_hp; free(_hp); }
            ;
            if (_wcond646) {
            } else {
                ;
                break;
            }
            ;
            U64 _t650 = 0;
            Range *_t651 = Range_new(_t650, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t651, _fi645); i = *_hp; free(_hp); }
            Range_delete(_t651, &(Bool){1});
            U64 _t652 = 1;
            U64 _t653 = U64_add(_fi645, _t652);
            ;
            _fi645 = _t653;
            ;
            U64 *_t654 = malloc(sizeof(U64)); *_t654 = U64_mul(i, self->elem_size);
            void *_t655 = ptr_add(self->data, DEREF(_t654));
            void *cloned = dyn_call_clone(&self->elem_type, _t655);
            U64_delete(_t654, &(Bool){1});
            U64 *_t656 = malloc(sizeof(U64)); *_t656 = U64_mul(i, self->elem_size);
            ;
            void *_t657 = ptr_add(new_data, DEREF(_t656));
            memcpy(_t657, cloned, self->elem_size);
            U64_delete(_t656, &(Bool){1});
            free(cloned);
        }
        ;
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
    U64 _t678; { U64 *_hp = Str_size(); _t678 = *_hp; free(_hp); }
    Vec *parts = Vec_new(_t677, &(U64){_t678});
    Str_delete(_t677, &(Bool){1});
    ;
    U64 _t679; { U64 *_hp = Str_len(delim); _t679 = *_hp; free(_hp); }
    U64 _t680 = 0;
    Bool _t681 = U64_eq(_t679, _t680);
    ;
    ;
    if (_t681) {
        Str *_t661 = Str_clone(s);
        Vec_push(parts, _t661);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    U64 pos = 0;
    while (1) {
        U64 _t671; { U64 *_hp = Str_len(s); _t671 = *_hp; free(_hp); }
        U64 _t672; { U64 *_hp = Str_len(delim); _t672 = *_hp; free(_hp); }
        U64 _t673 = U64_sub(_t671, _t672);
        ;
        ;
        Bool _wcond662; { Bool *_hp = U64_lte(&(U64){pos}, &(U64){_t673}); _wcond662 = *_hp; free(_hp); }
        ;
        if (_wcond662) {
        } else {
            ;
            break;
        }
        ;
        U64 _t674; { U64 *_hp = Str_len(delim); _t674 = *_hp; free(_hp); }
        Str *_t675 = Str_substr(s, &(U64){pos}, &(U64){_t674});
        ;
        Bool _t676; { Bool *_hp = Str_eq(_t675, delim); _t676 = *_hp; free(_hp); }
        Str_delete(_t675, &(Bool){1});
        if (_t676) {
            U64 _t663 = U64_sub(pos, start);
            Str *_t664 = Str_substr(s, &(U64){start}, &(U64){_t663});
            ;
            Str *_t665 = Str_clone(_t664);
            Str_delete(_t664, &(Bool){1});
            Vec_push(parts, _t665);
            U64 _t666; { U64 *_hp = Str_len(delim); _t666 = *_hp; free(_hp); }
            U64 _t667 = U64_add(pos, _t666);
            ;
            start = _t667;
            ;
            U64 _t668 = U64_clone(&(U64){start});
            pos = _t668;
            ;
        } else {
            U64 _t669 = 1;
            U64 _t670 = U64_add(pos, _t669);
            ;
            pos = _t670;
            ;
        }
        ;
    }
    ;
    U64 _t682; { U64 *_hp = Str_len(s); _t682 = *_hp; free(_hp); }
    U64 _t683 = U64_sub(_t682, start);
    ;
    Str *_t684 = Str_substr(s, &(U64){start}, &(U64){_t683});
    ;
    ;
    Str *_t685 = Str_clone(_t684);
    Str_delete(_t684, &(Bool){1});
    Vec_push(parts, _t685);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 _t693; { U64 *_hp = Vec_len(parts); _t693 = *_hp; free(_hp); }
    U64 _t694 = 0;
    Bool _t695 = U64_eq(_t693, _t694);
    ;
    ;
    if (_t695) {
        Str *_t686 = Str_lit("", 0ULL);
        ;
        return _t686;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t688; { U64 *_hp = Vec_len(parts); _t688 = *_hp; free(_hp); }
        Bool _wcond687; { Bool *_hp = U64_lt(i, &(U64){_t688}); _wcond687 = *_hp; free(_hp); }
        ;
        if (_wcond687) {
        } else {
            ;
            break;
        }
        ;
        U64 _t689 = 0;
        Bool _t690; { Bool *_hp = U64_gt(i, &(U64){_t689}); _t690 = *_hp; free(_hp); }
        ;
        if (_t690) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        U64 _t691 = 1;
        U64 _t692 = U64_add(DEREF(i), _t691);
        ;
        *i = _t692;
        ;
    }
    U64_delete(i, &(Bool){1});
    return result;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    (void)self;
    EnumDef *_t696 = malloc(sizeof(EnumDef));
    return _t696;
}

void EnumDef_delete(EnumDef * self, Bool * call_free) {
    (void)self;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *EnumDef_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(EnumDef);
    return r;
}

static __attribute__((unused)) Str * U8_to_str(U8 * val) {
    I64 _t698 = U8_to_i64(DEREF(val));
    Str *_t699 = I64_to_str(&(I64){_t698});
    ;
    return _t699;
}

static __attribute__((unused)) U8 * U8_from_i64(I64 * val) {
    I64 _t706 = 0;
    I64 _t707 = 255;
    Bool _t708; { Bool *_hp = I64_lt(val, &(I64){_t706}); _t708 = *_hp; free(_hp); }
    ;
    Bool _t709; { Bool *_hp = I64_gt(val, &(I64){_t707}); _t709 = *_hp; free(_hp); }
    ;
    Bool _t710 = Bool_or(_t708, _t709);
    ;
    ;
    if (_t710) {
        Str *_t700 = Str_lit("Str", 3ULL);
        U64 _t701; { U64 *_hp = Str_size(); _t701 = *_hp; free(_hp); }
        U64 _t702 = 1;
        Array *_va12 = Array_new(_t700, &(U64){_t701}, &(U64){_t702});
        Str_delete(_t700, &(Bool){1});
        ;
        ;
        U64 _t703 = 0;
        Str *_t704 = Str_lit("value out of range (0-255)", 26ULL);
        Array_set(_va12, &(U64){_t703}, _t704);
        ;
        Str *_t705 = Str_lit("U8.from_i64", 11ULL);
        panic(_t705, _va12);
        Str_delete(_t705, &(Bool){1});
        Array_delete(_va12, &(Bool){1});
    }
    ;
    /* TODO: nested func U8_from_i64_ext */
    U8 _t711 = U8_from_i64_ext(val);
    { U8 *_r = malloc(sizeof(U8)); *_r = _t711; return _r; }
}

static U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

static __attribute__((unused)) Bool * U8_lt(U8 * a, U8 * b) {
    I64 _t713 = 0;
    I64 _t714 = 1;
    I64 _t715 = U8_cmp(DEREF(a), DEREF(b));
    I64 _t716 = I64_sub(_t713, _t714);
    ;
    ;
    Bool _t717 = I64_eq(_t715, _t716);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t717; return _r; }
}

static __attribute__((unused)) Bool * U8_gt(U8 * a, U8 * b) {
    I64 _t718 = U8_cmp(DEREF(a), DEREF(b));
    I64 _t719 = 1;
    Bool _t720 = I64_eq(_t718, _t719);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t720; return _r; }
}

static __attribute__((unused)) Bool * U8_neq(U8 * a, U8 * b) {
    Bool _t721 = U8_eq(DEREF(a), DEREF(b));
    Bool _t722 = Bool_not(_t721);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t722; return _r; }
}

static __attribute__((unused)) Bool * U8_lte(U8 * a, U8 * b) {
    Bool _t723; { Bool *_hp = U8_gt(a, b); _t723 = *_hp; free(_hp); }
    Bool _t724 = Bool_not(_t723);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t724; return _r; }
}

static __attribute__((unused)) Bool * U8_gte(U8 * a, U8 * b) {
    Bool _t725; { Bool *_hp = U8_lt(a, b); _t725 = *_hp; free(_hp); }
    Bool _t726 = Bool_not(_t725);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t726; return _r; }
}

static __attribute__((unused)) Str * I16_to_str(I16 * val) {
    I64 _t727 = I16_to_i64(DEREF(val));
    Str *_t728 = I64_to_str(&(I64){_t727});
    ;
    return _t728;
}

static __attribute__((unused)) I16 * I16_from_i64(I64 * val) {
    I64 _t735 = 32768;
    I64 _t736; { I64 *_hp = I64_neg(&(I64){_t735}); _t736 = *_hp; free(_hp); }
    ;
    I64 _t737 = 32767;
    Bool _t738; { Bool *_hp = I64_lt(val, &(I64){_t736}); _t738 = *_hp; free(_hp); }
    ;
    Bool _t739; { Bool *_hp = I64_gt(val, &(I64){_t737}); _t739 = *_hp; free(_hp); }
    ;
    Bool _t740 = Bool_or(_t738, _t739);
    ;
    ;
    if (_t740) {
        Str *_t729 = Str_lit("Str", 3ULL);
        U64 _t730; { U64 *_hp = Str_size(); _t730 = *_hp; free(_hp); }
        U64 _t731 = 1;
        Array *_va13 = Array_new(_t729, &(U64){_t730}, &(U64){_t731});
        Str_delete(_t729, &(Bool){1});
        ;
        ;
        U64 _t732 = 0;
        Str *_t733 = Str_lit("value out of range (-32768 to 32767)", 36ULL);
        Array_set(_va13, &(U64){_t732}, _t733);
        ;
        Str *_t734 = Str_lit("I16.from_i64", 12ULL);
        panic(_t734, _va13);
        Str_delete(_t734, &(Bool){1});
        Array_delete(_va13, &(Bool){1});
    }
    ;
    /* TODO: nested func I16_from_i64_ext */
    I16 _t741 = I16_from_i64_ext(val);
    { I16 *_r = malloc(sizeof(I16)); *_r = _t741; return _r; }
}

static __attribute__((unused)) I16 * I16_neg(I16 * a) {
    I64 _t742 = 0;
    I64 _t743 = I16_to_i64(DEREF(a));
    I64 _t744 = I64_sub(_t742, _t743);
    ;
    ;
    I16 _t745; { I16 *_hp = I16_from_i64(&(I64){_t744}); _t745 = *_hp; free(_hp); }
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t745; return _r; }
}

static __attribute__((unused)) I16 * I16_abs(I16 * a) {
    I64 _t750 = I16_to_i64(DEREF(a));
    I64 _t751 = 0;
    Bool _t752; { Bool *_hp = I64_lt(&(I64){_t750}, &(I64){_t751}); _t752 = *_hp; free(_hp); }
    ;
    ;
    if (_t752) {
        I64 _t746 = 0;
        I64 _t747 = I16_to_i64(DEREF(a));
        I64 _t748 = I64_sub(_t746, _t747);
        ;
        ;
        I16 _t749; { I16 *_hp = I16_from_i64(&(I64){_t748}); _t749 = *_hp; free(_hp); }
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t749; return _r; }
    }
    ;
    I16 _t753 = I16_clone(a);
    { I16 *_r = malloc(sizeof(I16)); *_r = _t753; return _r; }
}

static U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b) {
    I64 _t755 = 0;
    I64 _t756 = 1;
    I64 _t757 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t758 = I64_sub(_t755, _t756);
    ;
    ;
    Bool _t759 = I64_eq(_t757, _t758);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t759; return _r; }
}

static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b) {
    I64 _t760 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t761 = 1;
    Bool _t762 = I64_eq(_t760, _t761);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t762; return _r; }
}

static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b) {
    Bool _t763 = I16_eq(DEREF(a), DEREF(b));
    Bool _t764 = Bool_not(_t763);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t764; return _r; }
}

static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b) {
    Bool _t765; { Bool *_hp = I16_gt(a, b); _t765 = *_hp; free(_hp); }
    Bool _t766 = Bool_not(_t765);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t766; return _r; }
}

static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b) {
    Bool _t767; { Bool *_hp = I16_lt(a, b); _t767 = *_hp; free(_hp); }
    Bool _t768 = Bool_not(_t767);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t768; return _r; }
}

static __attribute__((unused)) Str * I32_to_str(I32 * val) {
    I64 _t769 = I32_to_i64(DEREF(val));
    Str *_t770 = I64_to_str(&(I64){_t769});
    ;
    return _t770;
}

static __attribute__((unused)) I32 * I32_from_i64(I64 * val) {
    I64 _t777 = 2147483648;
    I64 _t778; { I64 *_hp = I64_neg(&(I64){_t777}); _t778 = *_hp; free(_hp); }
    ;
    I64 _t779 = 2147483647;
    Bool _t780; { Bool *_hp = I64_lt(val, &(I64){_t778}); _t780 = *_hp; free(_hp); }
    ;
    Bool _t781; { Bool *_hp = I64_gt(val, &(I64){_t779}); _t781 = *_hp; free(_hp); }
    ;
    Bool _t782 = Bool_or(_t780, _t781);
    ;
    ;
    if (_t782) {
        Str *_t771 = Str_lit("Str", 3ULL);
        U64 _t772; { U64 *_hp = Str_size(); _t772 = *_hp; free(_hp); }
        U64 _t773 = 1;
        Array *_va14 = Array_new(_t771, &(U64){_t772}, &(U64){_t773});
        Str_delete(_t771, &(Bool){1});
        ;
        ;
        U64 _t774 = 0;
        Str *_t775 = Str_lit("value out of range (-2147483648 to 2147483647)", 46ULL);
        Array_set(_va14, &(U64){_t774}, _t775);
        ;
        Str *_t776 = Str_lit("I32.from_i64", 12ULL);
        panic(_t776, _va14);
        Str_delete(_t776, &(Bool){1});
        Array_delete(_va14, &(Bool){1});
    }
    ;
    /* TODO: nested func I32_from_i64_ext */
    I32 _t783 = I32_from_i64_ext(val);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t783; return _r; }
}

static __attribute__((unused)) I32 * I32_neg(I32 * a) {
    I64 _t784 = 0;
    I64 _t785 = I32_to_i64(DEREF(a));
    I64 _t786 = I64_sub(_t784, _t785);
    ;
    ;
    I32 _t787; { I32 *_hp = I32_from_i64(&(I64){_t786}); _t787 = *_hp; free(_hp); }
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t787; return _r; }
}

static __attribute__((unused)) I32 * I32_abs(I32 * a) {
    I64 _t792 = I32_to_i64(DEREF(a));
    I64 _t793 = 0;
    Bool _t794; { Bool *_hp = I64_lt(&(I64){_t792}, &(I64){_t793}); _t794 = *_hp; free(_hp); }
    ;
    ;
    if (_t794) {
        I64 _t788 = 0;
        I64 _t789 = I32_to_i64(DEREF(a));
        I64 _t790 = I64_sub(_t788, _t789);
        ;
        ;
        I32 _t791; { I32 *_hp = I32_from_i64(&(I64){_t790}); _t791 = *_hp; free(_hp); }
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t791; return _r; }
    }
    ;
    I32 _t795 = I32_clone(a);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t795; return _r; }
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b) {
    I64 _t797 = 0;
    I64 _t798 = 1;
    I64 _t799 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t800 = I64_sub(_t797, _t798);
    ;
    ;
    Bool _t801 = I64_eq(_t799, _t800);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t801; return _r; }
}

static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b) {
    I64 _t802 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t803 = 1;
    Bool _t804 = I64_eq(_t802, _t803);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t804; return _r; }
}

static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b) {
    Bool _t805 = I32_eq(DEREF(a), DEREF(b));
    Bool _t806 = Bool_not(_t805);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t806; return _r; }
}

static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b) {
    Bool _t807; { Bool *_hp = I32_gt(a, b); _t807 = *_hp; free(_hp); }
    Bool _t808 = Bool_not(_t807);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t808; return _r; }
}

static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b) {
    Bool _t809; { Bool *_hp = I32_lt(a, b); _t809 = *_hp; free(_hp); }
    Bool _t810 = Bool_not(_t809);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t810; return _r; }
}

static __attribute__((unused)) F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 _t811 = F32_from_i64_ext(val);
    { F32 *_r = malloc(sizeof(F32)); *_r = _t811; return _r; }
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b) {
    I64 _t813 = 0;
    I64 _t814 = 1;
    I64 _t815 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t816 = I64_sub(_t813, _t814);
    ;
    ;
    Bool _t817 = I64_eq(_t815, _t816);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t817; return _r; }
}

static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b) {
    I64 _t818 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t819 = 1;
    Bool _t820 = I64_eq(_t818, _t819);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t820; return _r; }
}

static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b) {
    Bool _t821 = F32_eq(DEREF(a), DEREF(b));
    Bool _t822 = Bool_not(_t821);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t822; return _r; }
}

static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b) {
    Bool _t823; { Bool *_hp = F32_gt(a, b); _t823 = *_hp; free(_hp); }
    Bool _t824 = Bool_not(_t823);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t824; return _r; }
}

static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b) {
    Bool _t825; { Bool *_hp = F32_lt(a, b); _t825 = *_hp; free(_hp); }
    Bool _t826 = Bool_not(_t825);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t826; return _r; }
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    I64 _t827 = U32_to_i64(DEREF(val));
    Str *_t828 = I64_to_str(&(I64){_t827});
    ;
    return _t828;
}

static __attribute__((unused)) U32 * U32_from_i64(I64 * val) {
    I64 _t835 = 0;
    I64 _t836 = 4294967295;
    Bool _t837; { Bool *_hp = I64_lt(val, &(I64){_t835}); _t837 = *_hp; free(_hp); }
    ;
    Bool _t838; { Bool *_hp = I64_gt(val, &(I64){_t836}); _t838 = *_hp; free(_hp); }
    ;
    Bool _t839 = Bool_or(_t837, _t838);
    ;
    ;
    if (_t839) {
        Str *_t829 = Str_lit("Str", 3ULL);
        U64 _t830; { U64 *_hp = Str_size(); _t830 = *_hp; free(_hp); }
        U64 _t831 = 1;
        Array *_va15 = Array_new(_t829, &(U64){_t830}, &(U64){_t831});
        Str_delete(_t829, &(Bool){1});
        ;
        ;
        U64 _t832 = 0;
        Str *_t833 = Str_lit("value out of range (0-4294967295)", 33ULL);
        Array_set(_va15, &(U64){_t832}, _t833);
        ;
        Str *_t834 = Str_lit("U32.from_i64", 12ULL);
        panic(_t834, _va15);
        Str_delete(_t834, &(Bool){1});
        Array_delete(_va15, &(Bool){1});
    }
    ;
    /* TODO: nested func U32_from_i64_ext */
    U32 _t840 = U32_from_i64_ext(val);
    { U32 *_r = malloc(sizeof(U32)); *_r = _t840; return _r; }
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    I64 _t842 = 0;
    I64 _t843 = 1;
    I64 _t844 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t845 = I64_sub(_t842, _t843);
    ;
    ;
    Bool _t846 = I64_eq(_t844, _t845);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t846; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    I64 _t847 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t848 = 1;
    Bool _t849 = I64_eq(_t847, _t848);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t849; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    Bool _t850 = U32_eq(DEREF(a), DEREF(b));
    Bool _t851 = Bool_not(_t850);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t851; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    Bool _t852; { Bool *_hp = U32_gt(a, b); _t852 = *_hp; free(_hp); }
    Bool _t853 = Bool_not(_t852);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t853; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    Bool _t854; { Bool *_hp = U32_lt(a, b); _t854 = *_hp; free(_hp); }
    Bool _t855 = Bool_not(_t854);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t855; return _r; }
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t856 = U64_to_str_ext(val);
    return _t856;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 _t857 = U64_from_i64_ext(val);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t857; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    I64 _t859 = 0;
    I64 _t860 = 1;
    I64 _t861 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t862 = I64_sub(_t859, _t860);
    ;
    ;
    Bool _t863 = I64_eq(_t861, _t862);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t863; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    I64 _t864 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t865 = 1;
    Bool _t866 = I64_eq(_t864, _t865);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t866; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    Bool _t867 = U64_eq(DEREF(a), DEREF(b));
    Bool _t868 = Bool_not(_t867);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t868; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    Bool _t869; { Bool *_hp = U64_gt(a, b); _t869 = *_hp; free(_hp); }
    Bool _t870 = Bool_not(_t869);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t870; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    Bool _t871; { Bool *_hp = U64_lt(a, b); _t871 = *_hp; free(_hp); }
    Bool _t872 = Bool_not(_t871);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t872; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    I64 _t912 = 0;
    Bool _t913 = I64_eq(DEREF(val), _t912);
    ;
    if (_t913) {
        U64 _t873 = 2;
        U8 *buf = malloc(_t873);
        ;
        I64 _t874 = 48;
        U8 _t875; { U8 *_hp = U8_from_i64(&(I64){_t874}); _t875 = *_hp; free(_hp); }
        ;
        U64 _t876 = 1;
        memcpy(buf, &(U8){_t875}, _t876);
        ;
        ;
        U64 *_t877 = malloc(sizeof(U64));
        *_t877 = 1;
        I64 _t878 = 0;
        void *_t879 = ptr_add(buf, DEREF(_t877));
        U8 _t880; { U8 *_hp = U8_from_i64(&(I64){_t878}); _t880 = *_hp; free(_hp); }
        ;
        U64 _t881 = 1;
        memcpy(_t879, &(U8){_t880}, _t881);
        U64_delete(_t877, &(Bool){1});
        ;
        ;
        I64 _t882 = 1;
        I64 _t883 = 1;
        Str *_t884 = malloc(sizeof(Str));
        _t884->c_str = buf;
        _t884->count = _t882;
        _t884->cap = _t883;
        ;
        ;
        ;
        return _t884;
    }
    ;
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 _t914 = 0;
    Bool _t915; { Bool *_hp = I64_lt(val, &(I64){_t914}); _t915 = *_hp; free(_hp); }
    ;
    if (_t915) {
        Bool _t885 = 1;
        is_neg = _t885;
        ;
        I64 _t886 = 0;
        I64 _t887 = I64_sub(_t886, DEREF(val));
        ;
        v = _t887;
        ;
    }
    ;
    U64 ndigits = 0;
    I64 tmp = I64_clone(&(I64){v});
    while (1) {
        I64 _t889 = 0;
        Bool _wcond888; { Bool *_hp = I64_gt(&(I64){tmp}, &(I64){_t889}); _wcond888 = *_hp; free(_hp); }
        ;
        if (_wcond888) {
        } else {
            ;
            break;
        }
        ;
        U64 _t890 = 1;
        U64 _t891 = U64_add(ndigits, _t890);
        ;
        ndigits = _t891;
        ;
        I64 _t892 = 10;
        I64 _t893 = I64_div(tmp, _t892);
        ;
        tmp = _t893;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    ;
    if (is_neg) {
        U64 _t894 = 1;
        U64 _t895 = U64_add(DEREF(total), _t894);
        ;
        *total = _t895;
        ;
    }
    U64 _t916 = 1;
    U64 _t917 = U64_add(DEREF(total), _t916);
    ;
    U8 *buf = malloc(_t917);
    ;
    if (is_neg) {
        I64 _t896 = 45;
        U8 _t897; { U8 *_hp = U8_from_i64(&(I64){_t896}); _t897 = *_hp; free(_hp); }
        ;
        U64 _t898 = 1;
        memcpy(buf, &(U8){_t897}, _t898);
        ;
        ;
    }
    ;
    U64 _t918 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t918);
    ;
    while (1) {
        I64 _t900 = 0;
        Bool _wcond899; { Bool *_hp = I64_gt(&(I64){v}, &(I64){_t900}); _wcond899 = *_hp; free(_hp); }
        ;
        if (_wcond899) {
        } else {
            ;
            break;
        }
        ;
        I64 _t901 = 10;
        I64 _t902 = I64_mod(v, _t901);
        ;
        I64 _t903 = 48;
        I64 _t904 = I64_add(_t902, _t903);
        ;
        ;
        void *_t905 = ptr_add(buf, DEREF(i));
        U8 _t906; { U8 *_hp = U8_from_i64(&(I64){_t904}); _t906 = *_hp; free(_hp); }
        ;
        U64 _t907 = 1;
        memcpy(_t905, &(U8){_t906}, _t907);
        ;
        ;
        I64 _t908 = 10;
        I64 _t909 = I64_div(v, _t908);
        ;
        v = _t909;
        ;
        U64 _t910 = 1;
        U64 _t911 = U64_sub(DEREF(i), _t910);
        ;
        *i = _t911;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    I64 _t919 = 0;
    void *_t920 = ptr_add(buf, DEREF(total));
    U8 _t921; { U8 *_hp = U8_from_i64(&(I64){_t919}); _t921 = *_hp; free(_hp); }
    ;
    U64 _t922 = 1;
    memcpy(_t920, &(U8){_t921}, _t922);
    ;
    ;
    U64 _t923 = U64_clone(total);
    U64 _t924 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t925 = malloc(sizeof(Str));
    _t925->c_str = buf;
    _t925->count = _t923;
    _t925->cap = _t924;
    ;
    ;
    return _t925;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    I64 _t926 = 0;
    I64 _t927 = I64_sub(_t926, DEREF(a));
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t927; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    I64 _t930 = 0;
    Bool _t931; { Bool *_hp = I64_lt(a, &(I64){_t930}); _t931 = *_hp; free(_hp); }
    ;
    if (_t931) {
        I64 _t928 = 0;
        I64 _t929 = I64_sub(_t928, DEREF(a));
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t929; return _r; }
    }
    ;
    I64 _t932 = I64_clone(a);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t932; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    I64 _t934 = 0;
    I64 _t935 = 1;
    I64 _t936 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t937 = I64_sub(_t934, _t935);
    ;
    ;
    Bool _t938 = I64_eq(_t936, _t937);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t938; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    I64 _t939 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t940 = 1;
    Bool _t941 = I64_eq(_t939, _t940);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t941; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    Bool _t942 = I64_eq(DEREF(a), DEREF(b));
    Bool _t943 = Bool_not(_t942);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t943; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    Bool _t944; { Bool *_hp = I64_gt(a, b); _t944 = *_hp; free(_hp); }
    Bool _t945 = Bool_not(_t944);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t945; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    Bool _t946; { Bool *_hp = I64_lt(a, b); _t946 = *_hp; free(_hp); }
    Bool _t947 = Bool_not(_t946);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t947; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    U64 _t948 = U64_clone(&(U64){start});
    U64 _t949 = U64_clone(&(U64){end});
    Range *_t950 = malloc(sizeof(Range));
    _t950->start = _t948;
    _t950->end = _t949;
    ;
    ;
    return _t950;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t952; { Bool *_hp = U64_lte(&self->start, &self->end); _t952 = *_hp; free(_hp); }
    if (_t952) {
        U64 _t951 = U64_sub(self->end, self->start);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t951; return _r; }
    }
    ;
    U64 _t953 = U64_sub(self->start, self->end);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t953; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    Bool _t955; { Bool *_hp = U64_lte(&self->start, &self->end); _t955 = *_hp; free(_hp); }
    if (_t955) {
        U64 _t954 = U64_add(self->start, i);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t954; return _r; }
    }
    ;
    U64 _t956 = U64_sub(self->start, i);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t956; return _r; }
}

Range * Range_clone(Range * val) {
    Range *_t957 = malloc(sizeof(Range));
    _t957->start = val->start;
    _t957->end = val->end;
    return _t957;
}

void Range_delete(Range * self, Bool * call_free) {
    (void)self;
    if (DEREF(call_free)) {
        free(self);
    }
}

U64 *Range_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Range);
    return r;
}

static __attribute__((unused)) Str * Bool_to_str(Bool * b) {
    if (DEREF(b)) {
        Str *_t959 = Str_lit("true", 4ULL);
        return _t959;
    } else {
        Str *_t960 = Str_lit("false", 5ULL);
        return _t960;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool _t965 = Bool_eq(DEREF(a), DEREF(b));
    if (_t965) {
        I64 _t961 = 0;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t961; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t962 = 0;
        I64 _t963 = 1;
        I64 _t964 = I64_sub(_t962, _t963);
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t964; return _r; }
    }
    I64 _t966 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t966; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    I64 _t968 = 0;
    I64 _t969 = 1;
    I64 _t970; { I64 *_hp = Bool_cmp(a, b); _t970 = *_hp; free(_hp); }
    I64 _t971 = I64_sub(_t968, _t969);
    ;
    ;
    Bool _t972 = I64_eq(_t970, _t971);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t972; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    I64 _t973; { I64 *_hp = Bool_cmp(a, b); _t973 = *_hp; free(_hp); }
    I64 _t974 = 1;
    Bool _t975 = I64_eq(_t973, _t974);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t975; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    Bool _t976 = Bool_eq(DEREF(a), DEREF(b));
    Bool _t977 = Bool_not(_t976);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t977; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    Bool _t978; { Bool *_hp = Bool_gt(a, b); _t978 = *_hp; free(_hp); }
    Bool _t979 = Bool_not(_t978);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t979; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    Bool _t980; { Bool *_hp = Bool_lt(a, b); _t980 = *_hp; free(_hp); }
    Bool _t981 = Bool_not(_t980);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t981; return _r; }
}

void println(Array * parts) {
    {
        U64 *_fi982 = malloc(sizeof(U64));
        *_fi982 = 0;
        while (1) {
            U64 _t984; { U64 *_hp = Array_len(parts); _t984 = *_hp; free(_hp); }
            Bool _wcond983; { Bool *_hp = U64_lt(_fi982, &(U64){_t984}); _wcond983 = *_hp; free(_hp); }
            ;
            if (_wcond983) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi982);
            U64 _t985 = 1;
            U64 _t986 = U64_add(DEREF(_fi982), _t985);
            ;
            *_fi982 = _t986;
            ;
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
            U64 _t989; { U64 *_hp = Array_len(parts); _t989 = *_hp; free(_hp); }
            Bool _wcond988; { Bool *_hp = U64_lt(_fi987, &(U64){_t989}); _wcond988 = *_hp; free(_hp); }
            ;
            if (_wcond988) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi987);
            U64 _t990 = 1;
            U64 _t991 = U64_add(DEREF(_fi987), _t990);
            ;
            *_fi987 = _t991;
            ;
            print_single(s);
        }
        U64_delete(_fi987, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 total = 0;
    {
        U64 *_fi992 = malloc(sizeof(U64));
        *_fi992 = 0;
        while (1) {
            U64 _t994; { U64 *_hp = Array_len(parts); _t994 = *_hp; free(_hp); }
            Bool _wcond993; { Bool *_hp = U64_lt(_fi992, &(U64){_t994}); _wcond993 = *_hp; free(_hp); }
            ;
            if (_wcond993) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi992);
            U64 _t995 = 1;
            U64 _t996 = U64_add(DEREF(_fi992), _t995);
            ;
            *_fi992 = _t996;
            ;
            U64 _t997; { U64 *_hp = Str_len(s); _t997 = *_hp; free(_hp); }
            U64 _t998 = U64_add(total, _t997);
            ;
            total = _t998;
            ;
        }
        U64_delete(_fi992, &(Bool){1});
    }
    U8 *buf = malloc(total);
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    {
        U64 *_fi999 = malloc(sizeof(U64));
        *_fi999 = 0;
        while (1) {
            U64 _t1001; { U64 *_hp = Array_len(parts); _t1001 = *_hp; free(_hp); }
            Bool _wcond1000; { Bool *_hp = U64_lt(_fi999, &(U64){_t1001}); _wcond1000 = *_hp; free(_hp); }
            ;
            if (_wcond1000) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi999);
            U64 _t1002 = 1;
            U64 _t1003 = U64_add(DEREF(_fi999), _t1002);
            ;
            *_fi999 = _t1003;
            ;
            void *_t1004 = ptr_add(buf, DEREF(offset));
            U64 _t1005; { U64 *_hp = Str_len(s); _t1005 = *_hp; free(_hp); }
            memcpy(_t1004, s->c_str, _t1005);
            ;
            U64 _t1006; { U64 *_hp = Str_len(s); _t1006 = *_hp; free(_hp); }
            U64 _t1007 = U64_add(DEREF(offset), _t1006);
            ;
            *offset = _t1007;
            ;
        }
        U64_delete(_fi999, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t1008 = U64_clone(&(U64){total});
    U64 _t1009 = U64_clone(&(U64){total});
    ;
    Str *_t1010 = malloc(sizeof(Str));
    _t1010->c_str = buf;
    _t1010->count = _t1008;
    _t1010->cap = _t1009;
    ;
    ;
    return _t1010;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        I64 _t1011 = 0;
        I64 _t1012 = 1;
        I64 _t1013 = I64_sub(_t1011, _t1012);
        ;
        ;
        Bool _t1014; { Bool *_hp = I64_neq(&(I64){status}, &(I64){_t1013}); _t1014 = *_hp; free(_hp); }
        ;
        if (_t1014) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t1015 = 50;
        sleep_ms(_t1015);
        ;
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t1021; { U64 *_hp = Array_len(args); _t1021 = *_hp; free(_hp); }
        Bool _wcond1016; { Bool *_hp = U64_lt(i, &(U64){_t1021}); _wcond1016 = *_hp; free(_hp); }
        ;
        if (_wcond1016) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        U64 _t1022 = 0;
        Bool _t1023; { Bool *_hp = U64_gt(i, &(U64){_t1022}); _t1023 = *_hp; free(_hp); }
        ;
        if (_t1023) {
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
        ;
        U64 _t1024 = 1;
        U64 _t1025 = U64_add(DEREF(i), _t1024);
        ;
        *i = _t1025;
        ;
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
    I64 pid; { I64 *_hp = spawn_cmd(_t1030); pid = *_hp; free(_hp); }
    Str_delete(_t1030, &(Bool){1});
    I64 ec; { I64 *_hp = wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    ;
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 _t1031; { U64 *_hp = Str_size(); _t1031 = *_hp; free(_hp); }
    memcpy(output, content, _t1031);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    Str *_t1032 = Str_lit("Str", 3ULL);
    U64 _t1033; { U64 *_hp = Str_size(); _t1033 = *_hp; free(_hp); }
    U64 _t1034 = 3;
    Array *_va16 = Array_new(_t1032, &(U64){_t1033}, &(U64){_t1034});
    Str_delete(_t1032, &(Bool){1});
    ;
    ;
    U64 _t1035 = 0;
    Str *_t1036 = Str_clone(loc_str);
    Array_set(_va16, &(U64){_t1035}, _t1036);
    ;
    U64 _t1037 = 1;
    Str *_t1038 = Str_lit(": panic: ", 9ULL);
    Array_set(_va16, &(U64){_t1037}, _t1038);
    ;
    U64 _t1039 = 2;
    Str *_t1040 = format(parts);
    Array_set(_va16, &(U64){_t1039}, _t1040);
    ;
    println(_va16);
    I64 _t1041 = 1;
    exit(_t1041);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t1042 = Str_lit("Str", 3ULL);
    U64 _t1043; { U64 *_hp = Str_size(); _t1043 = *_hp; free(_hp); }
    U64 _t1044 = 2;
    Array *_va17 = Array_new(_t1042, &(U64){_t1043}, &(U64){_t1044});
    Str_delete(_t1042, &(Bool){1});
    ;
    ;
    U64 _t1045 = 0;
    Str *_t1046 = Str_lit("TODO: ", 6ULL);
    Array_set(_va17, &(U64){_t1045}, _t1046);
    ;
    U64 _t1047 = 1;
    Str *_t1048 = format(parts);
    Array_set(_va17, &(U64){_t1047}, _t1048);
    ;
    panic(loc_str, _va17);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t1049 = Str_lit("Str", 3ULL);
    U64 _t1050; { U64 *_hp = Str_size(); _t1050 = *_hp; free(_hp); }
    U64 _t1051 = 1;
    Array *_va18 = Array_new(_t1049, &(U64){_t1050}, &(U64){_t1051});
    Str_delete(_t1049, &(Bool){1});
    ;
    ;
    U64 _t1052 = 0;
    Str *_t1053 = Str_lit("unreachable", 11ULL);
    Array_set(_va18, &(U64){_t1052}, _t1053);
    ;
    panic(loc_str, _va18);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool _t1061 = Bool_not(DEREF(cond));
    if (_t1061) {
        Str *_t1054 = Str_lit("Str", 3ULL);
        U64 _t1055; { U64 *_hp = Str_size(); _t1055 = *_hp; free(_hp); }
        U64 _t1056 = 2;
        Array *_va19 = Array_new(_t1054, &(U64){_t1055}, &(U64){_t1056});
        Str_delete(_t1054, &(Bool){1});
        ;
        ;
        U64 _t1057 = 0;
        Str *_t1058 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va19, &(U64){_t1057}, _t1058);
        ;
        U64 _t1059 = 1;
        Str *_t1060 = format(parts);
        Array_set(_va19, &(U64){_t1059}, _t1060);
        ;
        panic(loc_str, _va19);
    }
    ;
    Bool _t1062 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1062; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t1063 = Str_lit("Str", 3ULL);
    U64 _t1064; { U64 *_hp = Str_size(); _t1064 = *_hp; free(_hp); }
    U64 _t1065 = 0;
    Array *_va20 = Array_new(_t1063, &(U64){_t1064}, &(U64){_t1065});
    Str_delete(_t1063, &(Bool){1});
    ;
    ;
    Bool _t1066; { Bool *_hp = assertm(loc_str, cond, _va20); _t1066 = *_hp; free(_hp); }
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1066; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t1067 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool _t1068; { Bool *_hp = assertm(loc_str, cond, _t1067); _t1068 = *_hp; free(_hp); }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool _t1082; { Bool *_hp = I64_neq(a, b); _t1082 = *_hp; free(_hp); }
    if (_t1082) {
        Str *_t1069 = Str_lit("Str", 3ULL);
        U64 _t1070; { U64 *_hp = Str_size(); _t1070 = *_hp; free(_hp); }
        U64 _t1071 = 5;
        Array *_va21 = Array_new(_t1069, &(U64){_t1070}, &(U64){_t1071});
        Str_delete(_t1069, &(Bool){1});
        ;
        ;
        U64 _t1072 = 0;
        Str *_t1073 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va21, &(U64){_t1072}, _t1073);
        ;
        U64 _t1074 = 1;
        Str *_t1075 = I64_to_str(a);
        Array_set(_va21, &(U64){_t1074}, _t1075);
        ;
        U64 _t1076 = 2;
        Str *_t1077 = Str_lit("', found '", 10ULL);
        Array_set(_va21, &(U64){_t1076}, _t1077);
        ;
        U64 _t1078 = 3;
        Str *_t1079 = I64_to_str(b);
        Array_set(_va21, &(U64){_t1078}, _t1079);
        ;
        U64 _t1080 = 4;
        Str *_t1081 = Str_lit("'", 1ULL);
        Array_set(_va21, &(U64){_t1080}, _t1081);
        ;
        panic(loc_str, _va21);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool _t1096; { Bool *_hp = Str_eq(a, b); _t1096 = *_hp; free(_hp); }
    Bool _t1097 = Bool_not(_t1096);
    ;
    if (_t1097) {
        Str *_t1083 = Str_lit("Str", 3ULL);
        U64 _t1084; { U64 *_hp = Str_size(); _t1084 = *_hp; free(_hp); }
        U64 _t1085 = 5;
        Array *_va22 = Array_new(_t1083, &(U64){_t1084}, &(U64){_t1085});
        Str_delete(_t1083, &(Bool){1});
        ;
        ;
        U64 _t1086 = 0;
        Str *_t1087 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va22, &(U64){_t1086}, _t1087);
        ;
        U64 _t1088 = 1;
        Str *_t1089 = Str_clone(a);
        Array_set(_va22, &(U64){_t1088}, _t1089);
        ;
        U64 _t1090 = 2;
        Str *_t1091 = Str_lit("', found '", 10ULL);
        Array_set(_va22, &(U64){_t1090}, _t1091);
        ;
        U64 _t1092 = 3;
        Str *_t1093 = Str_clone(b);
        Array_set(_va22, &(U64){_t1092}, _t1093);
        ;
        U64 _t1094 = 4;
        Str *_t1095 = Str_lit("'", 1ULL);
        Array_set(_va22, &(U64){_t1094}, _t1095);
        ;
        panic(loc_str, _va22);
    }
    ;
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
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) { U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) { I16 *_r = malloc(sizeof(I16)); *_r = I16_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) { I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) { F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) { U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) { U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(val); return _r; }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) { I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(val); return _r; }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Range", 5ULL) == 0) return (void *)Range_clone(val);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) { Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(val); return _r; }
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

Bool dyn_has_cmp(Str *type_name) {
    (void)type_name;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return 1;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I16", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return 1;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return 1;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return 1;
    return 0;
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

