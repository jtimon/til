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
U8 I64_to_u8(I64 val);
I16 I64_to_i16(I64 val);
I32 I64_to_i32(I64 val);
U32 I64_to_u32(I64 val);
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

static I64 *_t1038;
static I64 *_t1039;
static I64 *_t1040;
static U64 *CAP_LIT;
static I64 *_t1041;
static I64 *_t1042;
static I64 *_t1043;
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
    void *_t360 = ptr_add(new_data, DEREF(new_len));
    I64 _t361 = 0;
    U64 _t362 = 1;
    memcpy(_t360, &(I64){_t361}, _t362);
    ;
    ;
    U64 _t363 = U64_clone(new_len);
    U64 _t364 = U64_clone(new_len);
    U64_delete(new_len, &(Bool){1});
    Str *_t365 = malloc(sizeof(Str));
    _t365->c_str = new_data;
    _t365->count = _t363;
    _t365->cap = _t364;
    ;
    ;
    return _t365;
}

Str * Str_with_capacity(U64 * n) {
    U64 _t366 = 1;
    U64 _t367 = U64_add(DEREF(n), _t366);
    ;
    U8 *buf = malloc(_t367);
    ;
    I64 _t368 = 0;
    U64 _t369 = 1;
    memcpy(buf, &(I64){_t368}, _t369);
    ;
    ;
    I64 _t370 = 0;
    U64 _t371 = U64_clone(n);
    Str *_t372 = malloc(sizeof(Str));
    _t372->c_str = buf;
    _t372->count = _t370;
    _t372->cap = _t371;
    ;
    ;
    return _t372;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    Bool _t385; { Bool *_hp = U64_gte(&self->cap, CAP_VIEW); _t385 = *_hp; free(_hp); }
    if (_t385) {
        Str *_t373 = Str_lit("Str", 3ULL);
        U64 _t374; { U64 *_hp = Str_size(); _t374 = *_hp; free(_hp); }
        U64 _t375 = 1;
        Array *_va6 = Array_new(_t373, &(U64){_t374}, &(U64){_t375});
        Str_delete(_t373, &(Bool){1});
        ;
        ;
        U64 _t376 = 0;
        Str *_t377 = Str_lit("cannot mutate a string view or literal", 38ULL);
        Array_set(_va6, &(U64){_t376}, _t377);
        ;
        Str *_t378 = Str_lit("Str.push_str", 12ULL);
        panic(_t378, _va6);
        Str_delete(_t378, &(Bool){1});
        Array_delete(_va6, &(Bool){1});
    }
    ;
    U64 *new_len = malloc(sizeof(U64)); *new_len = U64_add(self->count, s->count);
    Bool _t386; { Bool *_hp = U64_gt(new_len, &self->cap); _t386 = *_hp; free(_hp); }
    if (_t386) {
        Str *_t379 = Str_lit("Str", 3ULL);
        U64 _t380; { U64 *_hp = Str_size(); _t380 = *_hp; free(_hp); }
        U64 _t381 = 1;
        Array *_va7 = Array_new(_t379, &(U64){_t380}, &(U64){_t381});
        Str_delete(_t379, &(Bool){1});
        ;
        ;
        U64 _t382 = 0;
        Str *_t383 = Str_lit("capacity exceeded", 17ULL);
        Array_set(_va7, &(U64){_t382}, _t383);
        ;
        Str *_t384 = Str_lit("Str.push_str", 12ULL);
        panic(_t384, _va7);
        Str_delete(_t384, &(Bool){1});
        Array_delete(_va7, &(Bool){1});
    }
    ;
    void *_t387 = ptr_add(self->c_str, self->count);
    memcpy(_t387, s->c_str, s->count);
    U64 _t388 = U64_clone(new_len);
    self->count = _t388;
    ;
    void *_t389 = ptr_add(self->c_str, DEREF(new_len));
    I64 _t390 = 0;
    U64 _t391 = 1;
    memcpy(_t389, &(I64){_t390}, _t391);
    ;
    ;
    U64_delete(new_len, &(Bool){1});
}

Str * Str_clone(Str * val) {
    U64 _t392 = 1;
    U64 _t393 = U64_add(val->count, _t392);
    ;
    U8 *new_data = malloc(_t393);
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t394 = ptr_add(new_data, val->count);
    I64 _t395 = 0;
    U64 _t396 = 1;
    memcpy(_t394, &(I64){_t395}, _t396);
    ;
    ;
    Str *_t397 = malloc(sizeof(Str));
    _t397->c_str = new_data;
    _t397->count = val->count;
    _t397->cap = val->count;
    return _t397;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    Bool _t398; { Bool *_hp = U64_lt(&self->cap, CAP_VIEW); _t398 = *_hp; free(_hp); }
    if (_t398) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Str * Str_to_str(Str * val) {
    Str *_t399 = Str_clone(val);
    return _t399;
}

Str * Str_substr(Str * s, U64 * start, U64 * n) {
    U64 *st = malloc(sizeof(U64)); *st = U64_clone(start);
    U64 ln = U64_clone(n);
    Bool _t401; { Bool *_hp = U64_gt(st, &s->count); _t401 = *_hp; free(_hp); }
    if (_t401) {
        *st = s->count;
    }
    ;
    U64 _t402 = U64_add(DEREF(st), ln);
    Bool _t403; { Bool *_hp = U64_gt(&(U64){_t402}, &s->count); _t403 = *_hp; free(_hp); }
    ;
    if (_t403) {
        U64 _t400 = U64_sub(s->count, DEREF(st));
        ln = _t400;
        ;
    }
    ;
    void *_t404 = ptr_add(s->c_str, DEREF(st));
    U64 _t405 = U64_clone(&(U64){ln});
    ;
    U64 _t406 = U64_clone(CAP_VIEW);
    Str *_t407 = malloc(sizeof(Str));
    _t407->c_str = _t404;
    _t407->count = _t405;
    _t407->cap = _t406;
    ;
    ;
    U64_delete(st, &(Bool){1});
    return _t407;
}

Bool * Str_contains(Str * a, Str * b) {
    U64 _t421 = 0;
    Bool _t422 = U64_eq(b->count, _t421);
    ;
    if (_t422) {
        Bool _t408 = 1;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t408; return _r; }
    }
    ;
    Bool _t423; { Bool *_hp = U64_gt(&b->count, &a->count); _t423 = *_hp; free(_hp); }
    if (_t423) {
        Bool _t409 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t409; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t418 = U64_sub(a->count, b->count);
        Bool _wcond410; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t418}); _wcond410 = *_hp; free(_hp); }
        ;
        if (_wcond410) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond411; { Bool *_hp = U64_lt(j, &b->count); _wcond411 = *_hp; free(_hp); }
            if (_wcond411) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t413 = malloc(sizeof(U64)); *_t413 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(a, _t413);
            U8 *bc = Str_get(b, j);
            Bool _t414; { Bool *_hp = U8_neq(ac, bc); _t414 = *_hp; free(_hp); }
            U64_delete(_t413, &(Bool){1});
            if (_t414) {
                Bool _t412 = 0;
                found = _t412;
                ;
            }
            ;
            U64 _t415 = 1;
            U64 _t416 = U64_add(DEREF(j), _t415);
            ;
            *j = _t416;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            Bool _t417 = 1;
            ;
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t417; return _r; }
        }
        ;
        U64 _t419 = 1;
        U64 _t420 = U64_add(i, _t419);
        ;
        i = _t420;
        ;
    }
    ;
    Bool _t424 = 0;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t424; return _r; }
}

Bool * Str_starts_with(Str * a, Str * b) {
    Bool _t431; { Bool *_hp = U64_gt(&b->count, &a->count); _t431 = *_hp; free(_hp); }
    if (_t431) {
        Bool _t425 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t425; return _r; }
    }
    ;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond426; { Bool *_hp = U64_lt(i, &b->count); _wcond426 = *_hp; free(_hp); }
        if (_wcond426) {
        } else {
            ;
            break;
        }
        ;
        U8 *ac = Str_get(a, i);
        U8 *bc = Str_get(b, i);
        Bool _t428; { Bool *_hp = U8_neq(ac, bc); _t428 = *_hp; free(_hp); }
        if (_t428) {
            Bool _t427 = 0;
            ;
            U64_delete(i, &(Bool){1});
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t427; return _r; }
        }
        ;
        U64 _t429 = 1;
        U64 _t430 = U64_add(DEREF(i), _t429);
        ;
        *i = _t430;
        ;
    }
    U64_delete(i, &(Bool){1});
    Bool _t432 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t432; return _r; }
}

Bool * Str_ends_with(Str * a, Str * b) {
    Bool _t440; { Bool *_hp = U64_gt(&b->count, &a->count); _t440 = *_hp; free(_hp); }
    if (_t440) {
        Bool _t433 = 0;
        ;
        { Bool *_r = malloc(sizeof(Bool)); *_r = _t433; return _r; }
    }
    ;
    U64 offset = U64_sub(a->count, b->count);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        Bool _wcond434; { Bool *_hp = U64_lt(i, &b->count); _wcond434 = *_hp; free(_hp); }
        if (_wcond434) {
        } else {
            ;
            break;
        }
        ;
        U64 *_t436 = malloc(sizeof(U64)); *_t436 = U64_add(offset, DEREF(i));
        U8 *ac = Str_get(a, _t436);
        U8 *bc = Str_get(b, i);
        Bool _t437; { Bool *_hp = U8_neq(ac, bc); _t437 = *_hp; free(_hp); }
        U64_delete(_t436, &(Bool){1});
        if (_t437) {
            Bool _t435 = 0;
            ;
            U64_delete(i, &(Bool){1});
            ;
            { Bool *_r = malloc(sizeof(Bool)); *_r = _t435; return _r; }
        }
        ;
        U64 _t438 = 1;
        U64 _t439 = U64_add(DEREF(i), _t438);
        ;
        *i = _t439;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    Bool _t441 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t441; return _r; }
}

Bool * Str_is_empty(Str * self) {
    (void)self;
    U64 _t442 = 0;
    Bool _t443 = U64_eq(self->count, _t442);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t443; return _r; }
}

I64 * Str_find(Str * self, Str * needle) {
    (void)self;
    U64 _t461 = 0;
    Bool _t462 = U64_eq(needle->count, _t461);
    ;
    if (_t462) {
        I64 _t444 = 0;
        I64 _t445 = 1;
        I64 _t446 = I64_sub(_t444, _t445);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t446; return _r; }
    }
    ;
    Bool _t463; { Bool *_hp = U64_gt(&needle->count, &self->count); _t463 = *_hp; free(_hp); }
    if (_t463) {
        I64 _t447 = 0;
        I64 _t448 = 1;
        I64 _t449 = I64_sub(_t447, _t448);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t449; return _r; }
    }
    ;
    U64 i = 0;
    while (1) {
        U64 _t458 = U64_sub(self->count, needle->count);
        Bool _wcond450; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t458}); _wcond450 = *_hp; free(_hp); }
        ;
        if (_wcond450) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond451; { Bool *_hp = U64_lt(j, &needle->count); _wcond451 = *_hp; free(_hp); }
            if (_wcond451) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t453 = malloc(sizeof(U64)); *_t453 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t453);
            U8 *bc = Str_get(needle, j);
            Bool _t454; { Bool *_hp = U8_neq(ac, bc); _t454 = *_hp; free(_hp); }
            U64_delete(_t453, &(Bool){1});
            if (_t454) {
                Bool _t452 = 0;
                found = _t452;
                ;
            }
            ;
            U64 _t455 = 1;
            U64 _t456 = U64_add(DEREF(j), _t455);
            ;
            *j = _t456;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t457 = U64_to_i64(i);
            ;
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = _t457; return _r; }
        }
        ;
        U64 _t459 = 1;
        U64 _t460 = U64_add(i, _t459);
        ;
        i = _t460;
        ;
    }
    ;
    I64 _t464 = 0;
    I64 _t465 = 1;
    I64 _t466 = I64_sub(_t464, _t465);
    ;
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t466; return _r; }
}

I64 * Str_rfind(Str * self, Str * needle) {
    (void)self;
    U64 _t484 = 0;
    Bool _t485 = U64_eq(needle->count, _t484);
    ;
    if (_t485) {
        I64 _t467 = 0;
        I64 _t468 = 1;
        I64 _t469 = I64_sub(_t467, _t468);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t469; return _r; }
    }
    ;
    Bool _t486; { Bool *_hp = U64_gt(&needle->count, &self->count); _t486 = *_hp; free(_hp); }
    if (_t486) {
        I64 _t470 = 0;
        I64 _t471 = 1;
        I64 _t472 = I64_sub(_t470, _t471);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t472; return _r; }
    }
    ;
    I64 _t487 = 0;
    I64 _t488 = 1;
    I64 last = I64_sub(_t487, _t488);
    ;
    ;
    U64 i = 0;
    while (1) {
        U64 _t481 = U64_sub(self->count, needle->count);
        Bool _wcond473; { Bool *_hp = U64_lte(&(U64){i}, &(U64){_t481}); _wcond473 = *_hp; free(_hp); }
        ;
        if (_wcond473) {
        } else {
            ;
            break;
        }
        ;
        U64 *j = malloc(sizeof(U64));
        *j = 0;
        Bool found = 1;
        while (1) {
            Bool _wcond474; { Bool *_hp = U64_lt(j, &needle->count); _wcond474 = *_hp; free(_hp); }
            if (_wcond474) {
            } else {
                ;
                break;
            }
            ;
            U64 *_t476 = malloc(sizeof(U64)); *_t476 = U64_add(i, DEREF(j));
            U8 *ac = Str_get(self, _t476);
            U8 *bc = Str_get(needle, j);
            Bool _t477; { Bool *_hp = U8_neq(ac, bc); _t477 = *_hp; free(_hp); }
            U64_delete(_t476, &(Bool){1});
            if (_t477) {
                Bool _t475 = 0;
                found = _t475;
                ;
            }
            ;
            U64 _t478 = 1;
            U64 _t479 = U64_add(DEREF(j), _t478);
            ;
            *j = _t479;
            ;
        }
        U64_delete(j, &(Bool){1});
        if (found) {
            I64 _t480 = U64_to_i64(i);
            last = _t480;
            ;
        }
        ;
        U64 _t482 = 1;
        U64 _t483 = U64_add(i, _t482);
        ;
        i = _t483;
        ;
    }
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = last; return _r; }
}

Str * Str_replace(Str * self, Str * from, Str * to) {
    (void)self;
    U64 _t504 = 0;
    Bool _t505 = U64_eq(from->count, _t504);
    ;
    if (_t505) {
        Str *_t489 = Str_clone(self);
        ;
        return _t489;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 start = 0;
    while (1) {
        U64 _t491 = U64_sub(self->count, from->count);
        Bool _wcond490; { Bool *_hp = U64_lte(&(U64){start}, &(U64){_t491}); _wcond490 = *_hp; free(_hp); }
        ;
        if (_wcond490) {
        } else {
            ;
            break;
        }
        ;
        U64 _t492 = U64_sub(self->count, start);
        Str *rest = Str_substr(self, &(U64){start}, &(U64){_t492});
        ;
        I64 pos; { I64 *_hp = Str_find(rest, from); pos = *_hp; free(_hp); }
        I64 _t493 = 0;
        I64 _t494 = 1;
        I64 _t495 = I64_sub(_t493, _t494);
        ;
        ;
        Bool _t496 = I64_eq(pos, _t495);
        ;
        if (_t496) {
            result = Str_concat(result, rest);
            ;
            ;
            Str_delete(rest, &(Bool){1});
            ;
            return result;
        }
        ;
        Str_delete(rest, &(Bool){1});
        U64 _t497; { U64 *_hp = U64_from_i64(&(I64){pos}); _t497 = *_hp; free(_hp); }
        Str *_t498 = Str_substr(self, &(U64){start}, &(U64){_t497});
        ;
        result = Str_concat(result, _t498);
        Str_delete(_t498, &(Bool){1});
        result = Str_concat(result, to);
        U64 _t499; { U64 *_hp = U64_from_i64(&(I64){pos}); _t499 = *_hp; free(_hp); }
        ;
        U64 _t500 = U64_add(start, _t499);
        ;
        U64 _t501 = U64_add(_t500, from->count);
        ;
        start = _t501;
        ;
    }
    Bool _t506; { Bool *_hp = U64_lt(&(U64){start}, &self->count); _t506 = *_hp; free(_hp); }
    if (_t506) {
        U64 _t502 = U64_sub(self->count, start);
        Str *_t503 = Str_substr(self, &(U64){start}, &(U64){_t502});
        ;
        result = Str_concat(result, _t503);
        Str_delete(_t503, &(Bool){1});
    }
    ;
    ;
    return result;
}

Str * Str_get_char(Str * self, U64 * i) {
    (void)self;
    U64 _t507 = 1;
    Str *_t508 = Str_substr(self, i, &(U64){_t507});
    ;
    return _t508;
}

Str * Str_strip_prefix(Str * self, Str * prefix) {
    (void)self;
    Bool _t511; { Bool *_hp = Str_starts_with(self, prefix); _t511 = *_hp; free(_hp); }
    if (_t511) {
        U64 _t509 = U64_sub(self->count, prefix->count);
        Str *_t510 = Str_substr(self, &prefix->count, &(U64){_t509});
        ;
        ;
        return _t510;
    }
    ;
    Str *_t512 = Str_clone(self);
    return _t512;
}

Str * Str_strip_suffix(Str * self, Str * suffix) {
    (void)self;
    Bool _t516; { Bool *_hp = Str_ends_with(self, suffix); _t516 = *_hp; free(_hp); }
    if (_t516) {
        U64 _t513 = 0;
        U64 _t514 = U64_sub(self->count, suffix->count);
        Str *_t515 = Str_substr(self, &(U64){_t513}, &(U64){_t514});
        ;
        ;
        ;
        return _t515;
    }
    ;
    Str *_t517 = Str_clone(self);
    return _t517;
}

Str * Str_from_byte(U8 * byte) {
    U64 _t518 = 2;
    U8 *buf = malloc(_t518);
    ;
    U64 _t519 = 1;
    memcpy(buf, byte, _t519);
    ;
    U64 *_t520 = malloc(sizeof(U64));
    *_t520 = 1;
    void *_t521 = ptr_add(buf, DEREF(_t520));
    I64 _t522 = 0;
    U64 _t523 = 1;
    memcpy(_t521, &(I64){_t522}, _t523);
    U64_delete(_t520, &(Bool){1});
    ;
    ;
    I64 _t524 = 1;
    I64 _t525 = 1;
    Str *_t526 = malloc(sizeof(Str));
    _t526->c_str = buf;
    _t526->count = _t524;
    _t526->cap = _t525;
    ;
    ;
    return _t526;
}

I64 * Str_to_i64(Str * self) {
    (void)self;
    U64 _t567 = 0;
    Bool _t568 = U64_eq(self->count, _t567);
    ;
    if (_t568) {
        Str *_t527 = Str_lit("Str", 3ULL);
        U64 _t528; { U64 *_hp = Str_size(); _t528 = *_hp; free(_hp); }
        U64 _t529 = 1;
        Array *_va8 = Array_new(_t527, &(U64){_t528}, &(U64){_t529});
        Str_delete(_t527, &(Bool){1});
        ;
        ;
        U64 _t530 = 0;
        Str *_t531 = Str_lit("empty string", 12ULL);
        Array_set(_va8, &(U64){_t530}, _t531);
        ;
        Str *_t532 = Str_lit("Str.to_i64", 10ULL);
        panic(_t532, _va8);
        Str_delete(_t532, &(Bool){1});
        Array_delete(_va8, &(Bool){1});
    }
    ;
    I64 result = 0;
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    Bool neg = 0;
    U64 *_t569 = malloc(sizeof(U64));
    *_t569 = 0;
    U8 *first = Str_get(self, _t569);
    U8 _t570 = 45;
    Bool _t571 = U8_eq(DEREF(first), _t570);
    U64_delete(_t569, &(Bool){1});
    ;
    if (_t571) {
        Bool _t533 = 1;
        neg = _t533;
        ;
        I64 _t534 = 1;
        U64 _t535; { U64 *_hp = U64_from_i64(&(I64){_t534}); _t535 = *_hp; free(_hp); }
        ;
        *i = _t535;
        ;
    }
    ;
    Bool _t572 = U64_eq(DEREF(i), self->count);
    if (_t572) {
        Str *_t536 = Str_lit("Str", 3ULL);
        U64 _t537; { U64 *_hp = Str_size(); _t537 = *_hp; free(_hp); }
        U64 _t538 = 1;
        Array *_va9 = Array_new(_t536, &(U64){_t537}, &(U64){_t538});
        Str_delete(_t536, &(Bool){1});
        ;
        ;
        U64 _t539 = 0;
        Str *_t540 = Str_lit("no digits", 9ULL);
        Array_set(_va9, &(U64){_t539}, _t540);
        ;
        Str *_t541 = Str_lit("Str.to_i64", 10ULL);
        panic(_t541, _va9);
        Str_delete(_t541, &(Bool){1});
        Array_delete(_va9, &(Bool){1});
    }
    ;
    while (1) {
        Bool _wcond542; { Bool *_hp = U64_lt(i, &self->count); _wcond542 = *_hp; free(_hp); }
        if (_wcond542) {
        } else {
            ;
            break;
        }
        ;
        U8 *ch = Str_get(self, i);
        I64 _t553 = U8_to_i64(DEREF(ch));
        I64 _t554 = 48;
        I64 d = I64_sub(_t553, _t554);
        ;
        ;
        I64 _t555 = 0;
        I64 _t556 = 9;
        Bool _t557; { Bool *_hp = I64_lt(&(I64){d}, &(I64){_t555}); _t557 = *_hp; free(_hp); }
        ;
        Bool _t558; { Bool *_hp = I64_gt(&(I64){d}, &(I64){_t556}); _t558 = *_hp; free(_hp); }
        ;
        Bool _t559 = Bool_or(_t557, _t558);
        ;
        ;
        if (_t559) {
            Str *_t543 = Str_lit("Str", 3ULL);
            U64 _t544; { U64 *_hp = Str_size(); _t544 = *_hp; free(_hp); }
            U64 _t545 = 3;
            Array *_va10 = Array_new(_t543, &(U64){_t544}, &(U64){_t545});
            Str_delete(_t543, &(Bool){1});
            ;
            ;
            U64 _t546 = 0;
            Str *_t547 = Str_lit("invalid char in '", 17ULL);
            Array_set(_va10, &(U64){_t546}, _t547);
            ;
            U64 _t548 = 1;
            Str *_t549 = Str_clone(self);
            Array_set(_va10, &(U64){_t548}, _t549);
            ;
            U64 _t550 = 2;
            Str *_t551 = Str_lit("'", 1ULL);
            Array_set(_va10, &(U64){_t550}, _t551);
            ;
            Str *_t552 = Str_lit("Str.to_i64", 10ULL);
            panic(_t552, _va10);
            Str_delete(_t552, &(Bool){1});
            Array_delete(_va10, &(Bool){1});
        }
        ;
        I64 _t560 = 10;
        I64 _t561 = I64_mul(result, _t560);
        ;
        I64 _t562 = I64_add(_t561, d);
        ;
        ;
        result = _t562;
        ;
        U64 _t563 = 1;
        U64 _t564 = U64_add(DEREF(i), _t563);
        ;
        *i = _t564;
        ;
    }
    U64_delete(i, &(Bool){1});
    if (neg) {
        I64 _t565 = 0;
        I64 _t566 = I64_sub(_t565, result);
        ;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t566; return _r; }
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
    I64 _t574; { I64 *_hp = Str_cmp(a, b); _t574 = *_hp; free(_hp); }
    I64 _t575 = 0;
    Bool _t576 = I64_eq(_t574, _t575);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t576; return _r; }
}

Bool * Str_lt(Str * a, Str * b) {
    I64 _t577 = 0;
    I64 _t578 = 1;
    I64 _t579; { I64 *_hp = Str_cmp(a, b); _t579 = *_hp; free(_hp); }
    I64 _t580 = I64_sub(_t577, _t578);
    ;
    ;
    Bool _t581 = I64_eq(_t579, _t580);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t581; return _r; }
}

Bool * Str_gt(Str * a, Str * b) {
    I64 _t582; { I64 *_hp = Str_cmp(a, b); _t582 = *_hp; free(_hp); }
    I64 _t583 = 1;
    Bool _t584 = I64_eq(_t582, _t583);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t584; return _r; }
}

Bool * Str_neq(Str * a, Str * b) {
    Bool _t585; { Bool *_hp = Str_eq(a, b); _t585 = *_hp; free(_hp); }
    Bool _t586 = Bool_not(_t585);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t586; return _r; }
}

Bool * Str_lte(Str * a, Str * b) {
    Bool _t587; { Bool *_hp = Str_gt(a, b); _t587 = *_hp; free(_hp); }
    Bool _t588 = Bool_not(_t587);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t588; return _r; }
}

Bool * Str_gte(Str * a, Str * b) {
    Bool _t589; { Bool *_hp = Str_lt(a, b); _t589 = *_hp; free(_hp); }
    Bool _t590 = Bool_not(_t589);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t590; return _r; }
}

Vec * Vec_new(Str * elem_type, U64 * elem_size) {
    void *_t591 = malloc(DEREF(elem_size));
    U64 _t592 = 0;
    I64 _t593 = 1;
    U64 _t594 = U64_clone(elem_size);
    Vec *_t595 = malloc(sizeof(Vec));
    _t595->data = _t591;
    _t595->count = _t592;
    _t595->cap = _t593;
    _t595->elem_size = _t594;
    { Str *_ca = Str_clone(elem_type); _t595->elem_type = *_ca; free(_ca); }
    ;
    ;
    ;
    return _t595;
}

U64 * Vec_len(Vec * self) {
    (void)self;
    { U64 *_r = malloc(sizeof(U64)); *_r = self->count; return _r; }
}

void Vec_push(Vec * self, void * val) {
    (void)self;
    Bool _t600 = U64_eq(self->count, self->cap);
    if (_t600) {
        U64 _t596 = 2;
        U64 new_cap = U64_mul(self->cap, _t596);
        ;
        U64 _t597 = U64_mul(new_cap, self->elem_size);
        void *_t598 = realloc(self->data, _t597);
        ;
        self->data = _t598;
        U64 _t599 = U64_clone(&(U64){new_cap});
        ;
        self->cap = _t599;
        ;
    }
    ;
    U64 *_t601 = malloc(sizeof(U64)); *_t601 = U64_mul(self->count, self->elem_size);
    void *_t602 = ptr_add(self->data, DEREF(_t601));
    memcpy(_t602, val, self->elem_size);
    U64_delete(_t601, &(Bool){1});
    free(val);
    U64 _t603 = 1;
    U64 _t604 = U64_add(self->count, _t603);
    ;
    self->count = _t604;
    ;
}

void * Vec_get(Vec * self, U64 * i) {
    (void)self;
    Bool _t619; { Bool *_hp = U64_gte(i, &self->count); _t619 = *_hp; free(_hp); }
    if (_t619) {
        Str *_t605 = Str_lit("Str", 3ULL);
        U64 _t606; { U64 *_hp = Str_size(); _t606 = *_hp; free(_hp); }
        U64 _t607 = 5;
        Array *_va11 = Array_new(_t605, &(U64){_t606}, &(U64){_t607});
        Str_delete(_t605, &(Bool){1});
        ;
        ;
        U64 _t608 = 0;
        Str *_t609 = Str_lit("index ", 6ULL);
        Array_set(_va11, &(U64){_t608}, _t609);
        ;
        U64 _t610 = 1;
        Str *_t611 = U64_to_str(DEREF(i));
        Array_set(_va11, &(U64){_t610}, _t611);
        ;
        U64 _t612 = 2;
        Str *_t613 = Str_lit(" out of bounds (len ", 20ULL);
        Array_set(_va11, &(U64){_t612}, _t613);
        ;
        U64 _t614 = 3;
        Str *_t615 = U64_to_str(self->count);
        Array_set(_va11, &(U64){_t614}, _t615);
        ;
        U64 _t616 = 4;
        Str *_t617 = Str_lit(")", 1ULL);
        Array_set(_va11, &(U64){_t616}, _t617);
        ;
        Str *_t618 = Str_lit("Vec.get", 7ULL);
        panic(_t618, _va11);
        Str_delete(_t618, &(Bool){1});
        Array_delete(_va11, &(Bool){1});
    }
    ;
    U64 *_t620 = malloc(sizeof(U64)); *_t620 = U64_mul(DEREF(i), self->elem_size);
    void *_t621 = ptr_add(self->data, DEREF(_t620));
    U64_delete(_t620, &(Bool){1});
    return _t621;
}

void Vec_delete(Vec * self, Bool * call_free) {
    (void)self;
    Bool _t635; { Bool *_hp = Str_is_empty(&self->elem_type); _t635 = *_hp; free(_hp); }
    Bool _t636 = Bool_not(_t635);
    ;
    if (_t636) {
        {
            U64 _fi622 = 0;
            while (1) {
                U64 _t624 = 0;
                Range *_t625 = Range_new(_t624, self->count);
                ;
                U64 _t626; { U64 *_hp = Range_len(_t625); _t626 = *_hp; free(_hp); }
                Range_delete(_t625, &(Bool){1});
                Bool _wcond623; { Bool *_hp = U64_lt(&(U64){_fi622}, &(U64){_t626}); _wcond623 = *_hp; free(_hp); }
                ;
                if (_wcond623) {
                } else {
                    ;
                    break;
                }
                ;
                U64 _t627 = 0;
                Range *_t628 = Range_new(_t627, self->count);
                ;
                U64 i; { U64 *_hp = Range_get(_t628, _fi622); i = *_hp; free(_hp); }
                Range_delete(_t628, &(Bool){1});
                U64 _t629 = 1;
                U64 _t630 = U64_add(_fi622, _t629);
                ;
                _fi622 = _t630;
                ;
                U64 *_t631 = malloc(sizeof(U64)); *_t631 = U64_mul(i, self->elem_size);
                ;
                void *_t632 = ptr_add(self->data, DEREF(_t631));
                Bool _t633 = 0;
                dyn_call_delete(&self->elem_type, _t632, &(Bool){_t633});
                U64_delete(_t631, &(Bool){1});
                ;
            }
            ;
        }
    }
    ;
    free(self->data);
    Bool _t637; { Bool *_hp = Str_is_empty(&self->elem_type); _t637 = *_hp; free(_hp); }
    Bool _t638 = Bool_not(_t637);
    ;
    if (_t638) {
        Bool _t634 = 0;
        Str_delete(&self->elem_type, &(Bool){_t634});
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Vec * Vec_clone(Vec * self) {
    (void)self;
    U64 _t652 = U64_mul(self->cap, self->elem_size);
    U8 *new_data = malloc(_t652);
    ;
    {
        U64 _fi639 = 0;
        while (1) {
            U64 _t641 = 0;
            Range *_t642 = Range_new(_t641, self->count);
            ;
            U64 _t643; { U64 *_hp = Range_len(_t642); _t643 = *_hp; free(_hp); }
            Range_delete(_t642, &(Bool){1});
            Bool _wcond640; { Bool *_hp = U64_lt(&(U64){_fi639}, &(U64){_t643}); _wcond640 = *_hp; free(_hp); }
            ;
            if (_wcond640) {
            } else {
                ;
                break;
            }
            ;
            U64 _t644 = 0;
            Range *_t645 = Range_new(_t644, self->count);
            ;
            U64 i; { U64 *_hp = Range_get(_t645, _fi639); i = *_hp; free(_hp); }
            Range_delete(_t645, &(Bool){1});
            U64 _t646 = 1;
            U64 _t647 = U64_add(_fi639, _t646);
            ;
            _fi639 = _t647;
            ;
            U64 *_t648 = malloc(sizeof(U64)); *_t648 = U64_mul(i, self->elem_size);
            void *_t649 = ptr_add(self->data, DEREF(_t648));
            void *cloned = dyn_call_clone(&self->elem_type, _t649);
            U64_delete(_t648, &(Bool){1});
            U64 *_t650 = malloc(sizeof(U64)); *_t650 = U64_mul(i, self->elem_size);
            ;
            void *_t651 = ptr_add(new_data, DEREF(_t650));
            memcpy(_t651, cloned, self->elem_size);
            U64_delete(_t650, &(Bool){1});
            free(cloned);
        }
        ;
    }
    Vec *_t653 = malloc(sizeof(Vec));
    _t653->data = new_data;
    _t653->count = self->count;
    _t653->cap = self->cap;
    _t653->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t653->elem_type = *_ca; free(_ca); }
    return _t653;
}

U64 *Vec_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Vec);
    return r;
}

Vec * split(Str * s, Str * delim) {
    Str *_t671 = Str_lit("Str", 3ULL);
    U64 _t672; { U64 *_hp = Str_size(); _t672 = *_hp; free(_hp); }
    Vec *parts = Vec_new(_t671, &(U64){_t672});
    Str_delete(_t671, &(Bool){1});
    ;
    U64 _t673; { U64 *_hp = Str_len(delim); _t673 = *_hp; free(_hp); }
    U64 _t674 = 0;
    Bool _t675 = U64_eq(_t673, _t674);
    ;
    ;
    if (_t675) {
        Str *_t655 = Str_clone(s);
        Vec_push(parts, _t655);
        ;
        return parts;
    }
    ;
    U64 start = 0;
    U64 pos = 0;
    while (1) {
        U64 _t665; { U64 *_hp = Str_len(s); _t665 = *_hp; free(_hp); }
        U64 _t666; { U64 *_hp = Str_len(delim); _t666 = *_hp; free(_hp); }
        U64 _t667 = U64_sub(_t665, _t666);
        ;
        ;
        Bool _wcond656; { Bool *_hp = U64_lte(&(U64){pos}, &(U64){_t667}); _wcond656 = *_hp; free(_hp); }
        ;
        if (_wcond656) {
        } else {
            ;
            break;
        }
        ;
        U64 _t668; { U64 *_hp = Str_len(delim); _t668 = *_hp; free(_hp); }
        Str *_t669 = Str_substr(s, &(U64){pos}, &(U64){_t668});
        ;
        Bool _t670; { Bool *_hp = Str_eq(_t669, delim); _t670 = *_hp; free(_hp); }
        Str_delete(_t669, &(Bool){1});
        if (_t670) {
            U64 _t657 = U64_sub(pos, start);
            Str *_t658 = Str_substr(s, &(U64){start}, &(U64){_t657});
            ;
            Str *_t659 = Str_clone(_t658);
            Str_delete(_t658, &(Bool){1});
            Vec_push(parts, _t659);
            U64 _t660; { U64 *_hp = Str_len(delim); _t660 = *_hp; free(_hp); }
            U64 _t661 = U64_add(pos, _t660);
            ;
            start = _t661;
            ;
            U64 _t662 = U64_clone(&(U64){start});
            pos = _t662;
            ;
        } else {
            U64 _t663 = 1;
            U64 _t664 = U64_add(pos, _t663);
            ;
            pos = _t664;
            ;
        }
        ;
    }
    ;
    U64 _t676; { U64 *_hp = Str_len(s); _t676 = *_hp; free(_hp); }
    U64 _t677 = U64_sub(_t676, start);
    ;
    Str *_t678 = Str_substr(s, &(U64){start}, &(U64){_t677});
    ;
    ;
    Str *_t679 = Str_clone(_t678);
    Str_delete(_t678, &(Bool){1});
    Vec_push(parts, _t679);
    return parts;
}

Str * join(Vec * parts, Str * sep) {
    U64 _t687; { U64 *_hp = Vec_len(parts); _t687 = *_hp; free(_hp); }
    U64 _t688 = 0;
    Bool _t689 = U64_eq(_t687, _t688);
    ;
    ;
    if (_t689) {
        Str *_t680 = Str_lit("", 0ULL);
        ;
        return _t680;
    }
    ;
    Str *result = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t682; { U64 *_hp = Vec_len(parts); _t682 = *_hp; free(_hp); }
        Bool _wcond681; { Bool *_hp = U64_lt(i, &(U64){_t682}); _wcond681 = *_hp; free(_hp); }
        ;
        if (_wcond681) {
        } else {
            ;
            break;
        }
        ;
        U64 _t683 = 0;
        Bool _t684; { Bool *_hp = U64_gt(i, &(U64){_t683}); _t684 = *_hp; free(_hp); }
        ;
        if (_t684) {
            result = Str_concat(result, sep);
        }
        ;
        Str *p = Vec_get(parts, i);
        result = Str_concat(result, p);
        U64 _t685 = 1;
        U64 _t686 = U64_add(DEREF(i), _t685);
        ;
        *i = _t686;
        ;
    }
    U64_delete(i, &(Bool){1});
    return result;
}

EnumDef * EnumDef_clone(EnumDef * self) {
    (void)self;
    EnumDef *_t690 = malloc(sizeof(EnumDef));
    return _t690;
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
    I64 _t692 = U8_to_i64(DEREF(val));
    Str *_t693 = I64_to_str(&(I64){_t692});
    ;
    return _t693;
}

static U64 *U8_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U8);
    return r;
}

static __attribute__((unused)) Bool * U8_lt(U8 * a, U8 * b) {
    I64 _t695 = 0;
    I64 _t696 = 1;
    I64 _t697 = U8_cmp(DEREF(a), DEREF(b));
    I64 _t698 = I64_sub(_t695, _t696);
    ;
    ;
    Bool _t699 = I64_eq(_t697, _t698);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t699; return _r; }
}

static __attribute__((unused)) Bool * U8_gt(U8 * a, U8 * b) {
    I64 _t700 = U8_cmp(DEREF(a), DEREF(b));
    I64 _t701 = 1;
    Bool _t702 = I64_eq(_t700, _t701);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t702; return _r; }
}

static __attribute__((unused)) Bool * U8_neq(U8 * a, U8 * b) {
    Bool _t703 = U8_eq(DEREF(a), DEREF(b));
    Bool _t704 = Bool_not(_t703);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t704; return _r; }
}

static __attribute__((unused)) Bool * U8_lte(U8 * a, U8 * b) {
    Bool _t705; { Bool *_hp = U8_gt(a, b); _t705 = *_hp; free(_hp); }
    Bool _t706 = Bool_not(_t705);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t706; return _r; }
}

static __attribute__((unused)) Bool * U8_gte(U8 * a, U8 * b) {
    Bool _t707; { Bool *_hp = U8_lt(a, b); _t707 = *_hp; free(_hp); }
    Bool _t708 = Bool_not(_t707);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t708; return _r; }
}

static __attribute__((unused)) Str * I16_to_str(I16 * val) {
    I64 _t709 = I16_to_i64(DEREF(val));
    Str *_t710 = I64_to_str(&(I64){_t709});
    ;
    return _t710;
}

static __attribute__((unused)) I16 * I16_neg(I16 * a) {
    I64 _t711 = 0;
    I64 _t712 = I16_to_i64(DEREF(a));
    I64 _t713 = I64_sub(_t711, _t712);
    ;
    ;
    I16 _t714 = I64_to_i16(_t713);
    ;
    { I16 *_r = malloc(sizeof(I16)); *_r = _t714; return _r; }
}

static __attribute__((unused)) I16 * I16_abs(I16 * a) {
    I64 _t719 = I16_to_i64(DEREF(a));
    I64 _t720 = 0;
    Bool _t721; { Bool *_hp = I64_lt(&(I64){_t719}, &(I64){_t720}); _t721 = *_hp; free(_hp); }
    ;
    ;
    if (_t721) {
        I64 _t715 = 0;
        I64 _t716 = I16_to_i64(DEREF(a));
        I64 _t717 = I64_sub(_t715, _t716);
        ;
        ;
        I16 _t718 = I64_to_i16(_t717);
        ;
        ;
        { I16 *_r = malloc(sizeof(I16)); *_r = _t718; return _r; }
    }
    ;
    I16 _t722 = I16_clone(a);
    { I16 *_r = malloc(sizeof(I16)); *_r = _t722; return _r; }
}

static U64 *I16_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I16);
    return r;
}

static __attribute__((unused)) Bool * I16_lt(I16 * a, I16 * b) {
    I64 _t724 = 0;
    I64 _t725 = 1;
    I64 _t726 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t727 = I64_sub(_t724, _t725);
    ;
    ;
    Bool _t728 = I64_eq(_t726, _t727);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t728; return _r; }
}

static __attribute__((unused)) Bool * I16_gt(I16 * a, I16 * b) {
    I64 _t729 = I16_cmp(DEREF(a), DEREF(b));
    I64 _t730 = 1;
    Bool _t731 = I64_eq(_t729, _t730);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t731; return _r; }
}

static __attribute__((unused)) Bool * I16_neq(I16 * a, I16 * b) {
    Bool _t732 = I16_eq(DEREF(a), DEREF(b));
    Bool _t733 = Bool_not(_t732);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t733; return _r; }
}

static __attribute__((unused)) Bool * I16_lte(I16 * a, I16 * b) {
    Bool _t734; { Bool *_hp = I16_gt(a, b); _t734 = *_hp; free(_hp); }
    Bool _t735 = Bool_not(_t734);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t735; return _r; }
}

static __attribute__((unused)) Bool * I16_gte(I16 * a, I16 * b) {
    Bool _t736; { Bool *_hp = I16_lt(a, b); _t736 = *_hp; free(_hp); }
    Bool _t737 = Bool_not(_t736);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t737; return _r; }
}

static __attribute__((unused)) Str * I32_to_str(I32 * val) {
    I64 _t738 = I32_to_i64(DEREF(val));
    Str *_t739 = I64_to_str(&(I64){_t738});
    ;
    return _t739;
}

static __attribute__((unused)) I32 * I32_neg(I32 * a) {
    I64 _t740 = 0;
    I64 _t741 = I32_to_i64(DEREF(a));
    I64 _t742 = I64_sub(_t740, _t741);
    ;
    ;
    I32 _t743 = I64_to_i32(_t742);
    ;
    { I32 *_r = malloc(sizeof(I32)); *_r = _t743; return _r; }
}

static __attribute__((unused)) I32 * I32_abs(I32 * a) {
    I64 _t748 = I32_to_i64(DEREF(a));
    I64 _t749 = 0;
    Bool _t750; { Bool *_hp = I64_lt(&(I64){_t748}, &(I64){_t749}); _t750 = *_hp; free(_hp); }
    ;
    ;
    if (_t750) {
        I64 _t744 = 0;
        I64 _t745 = I32_to_i64(DEREF(a));
        I64 _t746 = I64_sub(_t744, _t745);
        ;
        ;
        I32 _t747 = I64_to_i32(_t746);
        ;
        ;
        { I32 *_r = malloc(sizeof(I32)); *_r = _t747; return _r; }
    }
    ;
    I32 _t751 = I32_clone(a);
    { I32 *_r = malloc(sizeof(I32)); *_r = _t751; return _r; }
}

static U64 *I32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I32);
    return r;
}

static __attribute__((unused)) Bool * I32_lt(I32 * a, I32 * b) {
    I64 _t753 = 0;
    I64 _t754 = 1;
    I64 _t755 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t756 = I64_sub(_t753, _t754);
    ;
    ;
    Bool _t757 = I64_eq(_t755, _t756);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t757; return _r; }
}

static __attribute__((unused)) Bool * I32_gt(I32 * a, I32 * b) {
    I64 _t758 = I32_cmp(DEREF(a), DEREF(b));
    I64 _t759 = 1;
    Bool _t760 = I64_eq(_t758, _t759);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t760; return _r; }
}

static __attribute__((unused)) Bool * I32_neq(I32 * a, I32 * b) {
    Bool _t761 = I32_eq(DEREF(a), DEREF(b));
    Bool _t762 = Bool_not(_t761);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t762; return _r; }
}

static __attribute__((unused)) Bool * I32_lte(I32 * a, I32 * b) {
    Bool _t763; { Bool *_hp = I32_gt(a, b); _t763 = *_hp; free(_hp); }
    Bool _t764 = Bool_not(_t763);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t764; return _r; }
}

static __attribute__((unused)) Bool * I32_gte(I32 * a, I32 * b) {
    Bool _t765; { Bool *_hp = I32_lt(a, b); _t765 = *_hp; free(_hp); }
    Bool _t766 = Bool_not(_t765);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t766; return _r; }
}

static __attribute__((unused)) F32 * F32_from_i64(I64 * val) {
    /* TODO: nested func F32_from_i64_ext */
    F32 _t767 = F32_from_i64_ext(val);
    { F32 *_r = malloc(sizeof(F32)); *_r = _t767; return _r; }
}

static U64 *F32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(F32);
    return r;
}

static __attribute__((unused)) Bool * F32_lt(F32 * a, F32 * b) {
    I64 _t769 = 0;
    I64 _t770 = 1;
    I64 _t771 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t772 = I64_sub(_t769, _t770);
    ;
    ;
    Bool _t773 = I64_eq(_t771, _t772);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t773; return _r; }
}

static __attribute__((unused)) Bool * F32_gt(F32 * a, F32 * b) {
    I64 _t774 = F32_cmp(DEREF(a), DEREF(b));
    I64 _t775 = 1;
    Bool _t776 = I64_eq(_t774, _t775);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t776; return _r; }
}

static __attribute__((unused)) Bool * F32_neq(F32 * a, F32 * b) {
    Bool _t777 = F32_eq(DEREF(a), DEREF(b));
    Bool _t778 = Bool_not(_t777);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t778; return _r; }
}

static __attribute__((unused)) Bool * F32_lte(F32 * a, F32 * b) {
    Bool _t779; { Bool *_hp = F32_gt(a, b); _t779 = *_hp; free(_hp); }
    Bool _t780 = Bool_not(_t779);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t780; return _r; }
}

static __attribute__((unused)) Bool * F32_gte(F32 * a, F32 * b) {
    Bool _t781; { Bool *_hp = F32_lt(a, b); _t781 = *_hp; free(_hp); }
    Bool _t782 = Bool_not(_t781);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t782; return _r; }
}

static __attribute__((unused)) Str * U32_to_str(U32 * val) {
    I64 _t783 = U32_to_i64(DEREF(val));
    Str *_t784 = I64_to_str(&(I64){_t783});
    ;
    return _t784;
}

static U64 *U32_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U32);
    return r;
}

static __attribute__((unused)) Bool * U32_lt(U32 * a, U32 * b) {
    I64 _t786 = 0;
    I64 _t787 = 1;
    I64 _t788 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t789 = I64_sub(_t786, _t787);
    ;
    ;
    Bool _t790 = I64_eq(_t788, _t789);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t790; return _r; }
}

static __attribute__((unused)) Bool * U32_gt(U32 * a, U32 * b) {
    I64 _t791 = U32_cmp(DEREF(a), DEREF(b));
    I64 _t792 = 1;
    Bool _t793 = I64_eq(_t791, _t792);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t793; return _r; }
}

static __attribute__((unused)) Bool * U32_neq(U32 * a, U32 * b) {
    Bool _t794 = U32_eq(DEREF(a), DEREF(b));
    Bool _t795 = Bool_not(_t794);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t795; return _r; }
}

static __attribute__((unused)) Bool * U32_lte(U32 * a, U32 * b) {
    Bool _t796; { Bool *_hp = U32_gt(a, b); _t796 = *_hp; free(_hp); }
    Bool _t797 = Bool_not(_t796);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t797; return _r; }
}

static __attribute__((unused)) Bool * U32_gte(U32 * a, U32 * b) {
    Bool _t798; { Bool *_hp = U32_lt(a, b); _t798 = *_hp; free(_hp); }
    Bool _t799 = Bool_not(_t798);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t799; return _r; }
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *_t800 = U64_to_str_ext(val);
    return _t800;
}

static __attribute__((unused)) U64 * U64_from_i64(I64 * val) {
    /* TODO: nested func U64_from_i64_ext */
    U64 _t801 = U64_from_i64_ext(val);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t801; return _r; }
}

static U64 *U64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(U64);
    return r;
}

static __attribute__((unused)) Bool * U64_lt(U64 * a, U64 * b) {
    I64 _t803 = 0;
    I64 _t804 = 1;
    I64 _t805 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t806 = I64_sub(_t803, _t804);
    ;
    ;
    Bool _t807 = I64_eq(_t805, _t806);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t807; return _r; }
}

static __attribute__((unused)) Bool * U64_gt(U64 * a, U64 * b) {
    I64 _t808 = U64_cmp(DEREF(a), DEREF(b));
    I64 _t809 = 1;
    Bool _t810 = I64_eq(_t808, _t809);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t810; return _r; }
}

static __attribute__((unused)) Bool * U64_neq(U64 * a, U64 * b) {
    Bool _t811 = U64_eq(DEREF(a), DEREF(b));
    Bool _t812 = Bool_not(_t811);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t812; return _r; }
}

static __attribute__((unused)) Bool * U64_lte(U64 * a, U64 * b) {
    Bool _t813; { Bool *_hp = U64_gt(a, b); _t813 = *_hp; free(_hp); }
    Bool _t814 = Bool_not(_t813);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t814; return _r; }
}

static __attribute__((unused)) Bool * U64_gte(U64 * a, U64 * b) {
    Bool _t815; { Bool *_hp = U64_lt(a, b); _t815 = *_hp; free(_hp); }
    Bool _t816 = Bool_not(_t815);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t816; return _r; }
}

static __attribute__((unused)) Str * I64_to_str(I64 * val) {
    I64 _t853 = 0;
    Bool _t854 = I64_eq(DEREF(val), _t853);
    ;
    if (_t854) {
        U64 _t817 = 2;
        U8 *buf = malloc(_t817);
        ;
        I64 _t818 = 48;
        U64 _t819 = 1;
        memcpy(buf, &(I64){_t818}, _t819);
        ;
        ;
        U64 *_t820 = malloc(sizeof(U64));
        *_t820 = 1;
        void *_t821 = ptr_add(buf, DEREF(_t820));
        I64 _t822 = 0;
        U64 _t823 = 1;
        memcpy(_t821, &(I64){_t822}, _t823);
        U64_delete(_t820, &(Bool){1});
        ;
        ;
        I64 _t824 = 1;
        I64 _t825 = 1;
        Str *_t826 = malloc(sizeof(Str));
        _t826->c_str = buf;
        _t826->count = _t824;
        _t826->cap = _t825;
        ;
        ;
        ;
        return _t826;
    }
    ;
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 _t855 = 0;
    Bool _t856; { Bool *_hp = I64_lt(val, &(I64){_t855}); _t856 = *_hp; free(_hp); }
    ;
    if (_t856) {
        Bool _t827 = 1;
        is_neg = _t827;
        ;
        I64 _t828 = 0;
        I64 _t829 = I64_sub(_t828, DEREF(val));
        ;
        v = _t829;
        ;
    }
    ;
    U64 ndigits = 0;
    I64 tmp = I64_clone(&(I64){v});
    while (1) {
        I64 _t831 = 0;
        Bool _wcond830; { Bool *_hp = I64_gt(&(I64){tmp}, &(I64){_t831}); _wcond830 = *_hp; free(_hp); }
        ;
        if (_wcond830) {
        } else {
            ;
            break;
        }
        ;
        U64 _t832 = 1;
        U64 _t833 = U64_add(ndigits, _t832);
        ;
        ndigits = _t833;
        ;
        I64 _t834 = 10;
        I64 _t835 = I64_div(tmp, _t834);
        ;
        tmp = _t835;
        ;
    }
    ;
    U64 *total = malloc(sizeof(U64)); *total = U64_clone(&(U64){ndigits});
    ;
    if (is_neg) {
        U64 _t836 = 1;
        U64 _t837 = U64_add(DEREF(total), _t836);
        ;
        *total = _t837;
        ;
    }
    U64 _t857 = 1;
    U64 _t858 = U64_add(DEREF(total), _t857);
    ;
    U8 *buf = malloc(_t858);
    ;
    if (is_neg) {
        I64 _t838 = 45;
        U64 _t839 = 1;
        memcpy(buf, &(I64){_t838}, _t839);
        ;
        ;
    }
    ;
    U64 _t859 = 1;
    U64 *i = malloc(sizeof(U64)); *i = U64_sub(DEREF(total), _t859);
    ;
    while (1) {
        I64 _t841 = 0;
        Bool _wcond840; { Bool *_hp = I64_gt(&(I64){v}, &(I64){_t841}); _wcond840 = *_hp; free(_hp); }
        ;
        if (_wcond840) {
        } else {
            ;
            break;
        }
        ;
        I64 _t842 = 10;
        I64 _t843 = I64_mod(v, _t842);
        ;
        I64 _t844 = 48;
        I64 _t845 = I64_add(_t843, _t844);
        ;
        ;
        void *_t846 = ptr_add(buf, DEREF(i));
        U8 _t847 = I64_to_u8(_t845);
        ;
        U64 _t848 = 1;
        memcpy(_t846, &(U8){_t847}, _t848);
        ;
        ;
        I64 _t849 = 10;
        I64 _t850 = I64_div(v, _t849);
        ;
        v = _t850;
        ;
        U64 _t851 = 1;
        U64 _t852 = U64_sub(DEREF(i), _t851);
        ;
        *i = _t852;
        ;
    }
    U64_delete(i, &(Bool){1});
    ;
    void *_t860 = ptr_add(buf, DEREF(total));
    I64 _t861 = 0;
    U64 _t862 = 1;
    memcpy(_t860, &(I64){_t861}, _t862);
    ;
    ;
    U64 _t863 = U64_clone(total);
    U64 _t864 = U64_clone(total);
    U64_delete(total, &(Bool){1});
    Str *_t865 = malloc(sizeof(Str));
    _t865->c_str = buf;
    _t865->count = _t863;
    _t865->cap = _t864;
    ;
    ;
    return _t865;
}

static __attribute__((unused)) I64 * I64_neg(I64 * a) {
    I64 _t866 = 0;
    I64 _t867 = I64_sub(_t866, DEREF(a));
    ;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t867; return _r; }
}

static __attribute__((unused)) I64 * I64_abs(I64 * a) {
    I64 _t870 = 0;
    Bool _t871; { Bool *_hp = I64_lt(a, &(I64){_t870}); _t871 = *_hp; free(_hp); }
    ;
    if (_t871) {
        I64 _t868 = 0;
        I64 _t869 = I64_sub(_t868, DEREF(a));
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t869; return _r; }
    }
    ;
    I64 _t872 = I64_clone(a);
    { I64 *_r = malloc(sizeof(I64)); *_r = _t872; return _r; }
}

static U64 *I64_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(I64);
    return r;
}

static __attribute__((unused)) Bool * I64_lt(I64 * a, I64 * b) {
    I64 _t874 = 0;
    I64 _t875 = 1;
    I64 _t876 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t877 = I64_sub(_t874, _t875);
    ;
    ;
    Bool _t878 = I64_eq(_t876, _t877);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t878; return _r; }
}

static __attribute__((unused)) Bool * I64_gt(I64 * a, I64 * b) {
    I64 _t879 = I64_cmp(DEREF(a), DEREF(b));
    I64 _t880 = 1;
    Bool _t881 = I64_eq(_t879, _t880);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t881; return _r; }
}

static __attribute__((unused)) Bool * I64_neq(I64 * a, I64 * b) {
    Bool _t882 = I64_eq(DEREF(a), DEREF(b));
    Bool _t883 = Bool_not(_t882);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t883; return _r; }
}

static __attribute__((unused)) Bool * I64_lte(I64 * a, I64 * b) {
    Bool _t884; { Bool *_hp = I64_gt(a, b); _t884 = *_hp; free(_hp); }
    Bool _t885 = Bool_not(_t884);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t885; return _r; }
}

static __attribute__((unused)) Bool * I64_gte(I64 * a, I64 * b) {
    Bool _t886; { Bool *_hp = I64_lt(a, b); _t886 = *_hp; free(_hp); }
    Bool _t887 = Bool_not(_t886);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t887; return _r; }
}

Range * Range_new(U64 start, U64 end) {
    U64 _t888 = U64_clone(&(U64){start});
    U64 _t889 = U64_clone(&(U64){end});
    Range *_t890 = malloc(sizeof(Range));
    _t890->start = _t888;
    _t890->end = _t889;
    ;
    ;
    return _t890;
}

U64 * Range_len(Range * self) {
    (void)self;
    Bool _t892; { Bool *_hp = U64_lte(&self->start, &self->end); _t892 = *_hp; free(_hp); }
    if (_t892) {
        U64 _t891 = U64_sub(self->end, self->start);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t891; return _r; }
    }
    ;
    U64 _t893 = U64_sub(self->start, self->end);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t893; return _r; }
}

U64 * Range_get(Range * self, U64 i) {
    (void)self;
    Bool _t895; { Bool *_hp = U64_lte(&self->start, &self->end); _t895 = *_hp; free(_hp); }
    if (_t895) {
        U64 _t894 = U64_add(self->start, i);
        ;
        { U64 *_r = malloc(sizeof(U64)); *_r = _t894; return _r; }
    }
    ;
    U64 _t896 = U64_sub(self->start, i);
    { U64 *_r = malloc(sizeof(U64)); *_r = _t896; return _r; }
}

Range * Range_clone(Range * val) {
    Range *_t897 = malloc(sizeof(Range));
    _t897->start = val->start;
    _t897->end = val->end;
    return _t897;
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
        Str *_t899 = Str_lit("true", 4ULL);
        return _t899;
    } else {
        Str *_t900 = Str_lit("false", 5ULL);
        return _t900;
    }
}

static __attribute__((unused)) I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool _t905 = Bool_eq(DEREF(a), DEREF(b));
    if (_t905) {
        I64 _t901 = 0;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t901; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t902 = 0;
        I64 _t903 = 1;
        I64 _t904 = I64_sub(_t902, _t903);
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t904; return _r; }
    }
    I64 _t906 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t906; return _r; }
}

static U64 *Bool_size(void) {
    U64 *r = malloc(sizeof(U64));
    *r = (U64)sizeof(Bool);
    return r;
}

static __attribute__((unused)) Bool * Bool_lt(Bool * a, Bool * b) {
    I64 _t908 = 0;
    I64 _t909 = 1;
    I64 _t910; { I64 *_hp = Bool_cmp(a, b); _t910 = *_hp; free(_hp); }
    I64 _t911 = I64_sub(_t908, _t909);
    ;
    ;
    Bool _t912 = I64_eq(_t910, _t911);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t912; return _r; }
}

static __attribute__((unused)) Bool * Bool_gt(Bool * a, Bool * b) {
    I64 _t913; { I64 *_hp = Bool_cmp(a, b); _t913 = *_hp; free(_hp); }
    I64 _t914 = 1;
    Bool _t915 = I64_eq(_t913, _t914);
    ;
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t915; return _r; }
}

static __attribute__((unused)) Bool * Bool_neq(Bool * a, Bool * b) {
    Bool _t916 = Bool_eq(DEREF(a), DEREF(b));
    Bool _t917 = Bool_not(_t916);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t917; return _r; }
}

static __attribute__((unused)) Bool * Bool_lte(Bool * a, Bool * b) {
    Bool _t918; { Bool *_hp = Bool_gt(a, b); _t918 = *_hp; free(_hp); }
    Bool _t919 = Bool_not(_t918);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t919; return _r; }
}

static __attribute__((unused)) Bool * Bool_gte(Bool * a, Bool * b) {
    Bool _t920; { Bool *_hp = Bool_lt(a, b); _t920 = *_hp; free(_hp); }
    Bool _t921 = Bool_not(_t920);
    ;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t921; return _r; }
}

void println(Array * parts) {
    {
        U64 *_fi922 = malloc(sizeof(U64));
        *_fi922 = 0;
        while (1) {
            U64 _t924; { U64 *_hp = Array_len(parts); _t924 = *_hp; free(_hp); }
            Bool _wcond923; { Bool *_hp = U64_lt(_fi922, &(U64){_t924}); _wcond923 = *_hp; free(_hp); }
            ;
            if (_wcond923) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi922);
            U64 _t925 = 1;
            U64 _t926 = U64_add(DEREF(_fi922), _t925);
            ;
            *_fi922 = _t926;
            ;
            print_single(s);
        }
        U64_delete(_fi922, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void print(Array * parts) {
    {
        U64 *_fi927 = malloc(sizeof(U64));
        *_fi927 = 0;
        while (1) {
            U64 _t929; { U64 *_hp = Array_len(parts); _t929 = *_hp; free(_hp); }
            Bool _wcond928; { Bool *_hp = U64_lt(_fi927, &(U64){_t929}); _wcond928 = *_hp; free(_hp); }
            ;
            if (_wcond928) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi927);
            U64 _t930 = 1;
            U64 _t931 = U64_add(DEREF(_fi927), _t930);
            ;
            *_fi927 = _t931;
            ;
            print_single(s);
        }
        U64_delete(_fi927, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
}

Str * format(Array * parts) {
    U64 total = 0;
    {
        U64 *_fi932 = malloc(sizeof(U64));
        *_fi932 = 0;
        while (1) {
            U64 _t934; { U64 *_hp = Array_len(parts); _t934 = *_hp; free(_hp); }
            Bool _wcond933; { Bool *_hp = U64_lt(_fi932, &(U64){_t934}); _wcond933 = *_hp; free(_hp); }
            ;
            if (_wcond933) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi932);
            U64 _t935 = 1;
            U64 _t936 = U64_add(DEREF(_fi932), _t935);
            ;
            *_fi932 = _t936;
            ;
            U64 _t937; { U64 *_hp = Str_len(s); _t937 = *_hp; free(_hp); }
            U64 _t938 = U64_add(total, _t937);
            ;
            total = _t938;
            ;
        }
        U64_delete(_fi932, &(Bool){1});
    }
    U8 *buf = malloc(total);
    U64 *offset = malloc(sizeof(U64));
    *offset = 0;
    {
        U64 *_fi939 = malloc(sizeof(U64));
        *_fi939 = 0;
        while (1) {
            U64 _t941; { U64 *_hp = Array_len(parts); _t941 = *_hp; free(_hp); }
            Bool _wcond940; { Bool *_hp = U64_lt(_fi939, &(U64){_t941}); _wcond940 = *_hp; free(_hp); }
            ;
            if (_wcond940) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(parts, _fi939);
            U64 _t942 = 1;
            U64 _t943 = U64_add(DEREF(_fi939), _t942);
            ;
            *_fi939 = _t943;
            ;
            void *_t944 = ptr_add(buf, DEREF(offset));
            U64 _t945; { U64 *_hp = Str_len(s); _t945 = *_hp; free(_hp); }
            memcpy(_t944, s->c_str, _t945);
            ;
            U64 _t946; { U64 *_hp = Str_len(s); _t946 = *_hp; free(_hp); }
            U64 _t947 = U64_add(DEREF(offset), _t946);
            ;
            *offset = _t947;
            ;
        }
        U64_delete(_fi939, &(Bool){1});
    }
    U64_delete(offset, &(Bool){1});
    Array_delete(parts, &(Bool){1});
    U64 _t948 = U64_clone(&(U64){total});
    U64 _t949 = U64_clone(&(U64){total});
    ;
    Str *_t950 = malloc(sizeof(Str));
    _t950->c_str = buf;
    _t950->count = _t948;
    _t950->cap = _t949;
    ;
    ;
    return _t950;
}

I64 * wait_cmd(I64 * pid) {
    while (1) {
        I64 status = check_cmd_status(DEREF(pid));
        I64 _t951 = 0;
        I64 _t952 = 1;
        I64 _t953 = I64_sub(_t951, _t952);
        ;
        ;
        Bool _t954; { Bool *_hp = I64_neq(&(I64){status}, &(I64){_t953}); _t954 = *_hp; free(_hp); }
        ;
        if (_t954) {
            ;
            { I64 *_r = malloc(sizeof(I64)); *_r = status; return _r; }
        }
        ;
        ;
        I64 _t955 = 50;
        sleep_ms(_t955);
        ;
    }
}

I64 * run_cmd(Str * output, Array * args) {
    Str *cmd = Str_lit("", 0ULL);
    U64 *i = malloc(sizeof(U64));
    *i = 0;
    while (1) {
        U64 _t961; { U64 *_hp = Array_len(args); _t961 = *_hp; free(_hp); }
        Bool _wcond956; { Bool *_hp = U64_lt(i, &(U64){_t961}); _wcond956 = *_hp; free(_hp); }
        ;
        if (_wcond956) {
        } else {
            ;
            break;
        }
        ;
        Str *arg = Array_get(args, i);
        U64 _t962 = 0;
        Bool _t963; { Bool *_hp = U64_gt(i, &(U64){_t962}); _t963 = *_hp; free(_hp); }
        ;
        if (_t963) {
            Str *_t957 = Str_lit(" '", 2ULL);
            Str *_t958 = Str_concat(cmd, _t957);
            Str_delete(_t957, &(Bool){1});
            Str *_t959 = Str_concat(_t958, arg);
            Str_delete(_t958, &(Bool){1});
            Str *_t960 = Str_lit("'", 1ULL);
            cmd = Str_concat(_t959, _t960);
            Str_delete(_t959, &(Bool){1});
            Str_delete(_t960, &(Bool){1});
        } else {
            cmd = Str_clone(arg);
        }
        ;
        U64 _t964 = 1;
        U64 _t965 = U64_add(DEREF(i), _t964);
        ;
        *i = _t965;
        ;
    }
    Array_delete(args, &(Bool){1});
    U64_delete(i, &(Bool){1});
    Str *tmpf = Str_lit("tmp/_run_cmd_out", 16ULL);
    Str *_t966 = Str_lit(" > ", 3ULL);
    Str *_t967 = Str_concat(cmd, _t966);
    Str_delete(_t966, &(Bool){1});
    Str_delete(cmd, &(Bool){1});
    Str *_t968 = Str_concat(_t967, tmpf);
    Str_delete(_t967, &(Bool){1});
    Str *_t969 = Str_lit(" 2>&1", 5ULL);
    Str *_t970 = Str_concat(_t968, _t969);
    Str_delete(_t968, &(Bool){1});
    Str_delete(_t969, &(Bool){1});
    I64 pid; { I64 *_hp = spawn_cmd(_t970); pid = *_hp; free(_hp); }
    Str_delete(_t970, &(Bool){1});
    I64 ec; { I64 *_hp = wait_cmd(&(I64){pid}); ec = *_hp; free(_hp); }
    ;
    Str *content = readfile(tmpf);
    Str_delete(tmpf, &(Bool){1});
    U64 _t971; { U64 *_hp = Str_size(); _t971 = *_hp; free(_hp); }
    memcpy(output, content, _t971);
    ;
    free(content);
    { I64 *_r = malloc(sizeof(I64)); *_r = ec; return _r; }
}

void panic(Str * loc_str, Array * parts) {
    Str *_t972 = Str_lit("Str", 3ULL);
    U64 _t973; { U64 *_hp = Str_size(); _t973 = *_hp; free(_hp); }
    U64 _t974 = 3;
    Array *_va12 = Array_new(_t972, &(U64){_t973}, &(U64){_t974});
    Str_delete(_t972, &(Bool){1});
    ;
    ;
    U64 _t975 = 0;
    Str *_t976 = Str_clone(loc_str);
    Array_set(_va12, &(U64){_t975}, _t976);
    ;
    U64 _t977 = 1;
    Str *_t978 = Str_lit(": panic: ", 9ULL);
    Array_set(_va12, &(U64){_t977}, _t978);
    ;
    U64 _t979 = 2;
    Str *_t980 = format(parts);
    Array_set(_va12, &(U64){_t979}, _t980);
    ;
    println(_va12);
    I64 _t981 = 1;
    exit(_t981);
    ;
}

void TODO(Str * loc_str, Array * parts) {
    Str *_t982 = Str_lit("Str", 3ULL);
    U64 _t983; { U64 *_hp = Str_size(); _t983 = *_hp; free(_hp); }
    U64 _t984 = 2;
    Array *_va13 = Array_new(_t982, &(U64){_t983}, &(U64){_t984});
    Str_delete(_t982, &(Bool){1});
    ;
    ;
    U64 _t985 = 0;
    Str *_t986 = Str_lit("TODO: ", 6ULL);
    Array_set(_va13, &(U64){_t985}, _t986);
    ;
    U64 _t987 = 1;
    Str *_t988 = format(parts);
    Array_set(_va13, &(U64){_t987}, _t988);
    ;
    panic(loc_str, _va13);
}

void UNREACHABLE(Str * loc_str) {
    Str *_t989 = Str_lit("Str", 3ULL);
    U64 _t990; { U64 *_hp = Str_size(); _t990 = *_hp; free(_hp); }
    U64 _t991 = 1;
    Array *_va14 = Array_new(_t989, &(U64){_t990}, &(U64){_t991});
    Str_delete(_t989, &(Bool){1});
    ;
    ;
    U64 _t992 = 0;
    Str *_t993 = Str_lit("unreachable", 11ULL);
    Array_set(_va14, &(U64){_t992}, _t993);
    ;
    panic(loc_str, _va14);
}

Bool * assertm(Str * loc_str, Bool * cond, Array * parts) {
    Bool _t1001 = Bool_not(DEREF(cond));
    if (_t1001) {
        Str *_t994 = Str_lit("Str", 3ULL);
        U64 _t995; { U64 *_hp = Str_size(); _t995 = *_hp; free(_hp); }
        U64 _t996 = 2;
        Array *_va15 = Array_new(_t994, &(U64){_t995}, &(U64){_t996});
        Str_delete(_t994, &(Bool){1});
        ;
        ;
        U64 _t997 = 0;
        Str *_t998 = Str_lit("assert failed: ", 15ULL);
        Array_set(_va15, &(U64){_t997}, _t998);
        ;
        U64 _t999 = 1;
        Str *_t1000 = format(parts);
        Array_set(_va15, &(U64){_t999}, _t1000);
        ;
        panic(loc_str, _va15);
    }
    ;
    Bool _t1002 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1002; return _r; }
}

Bool * assert(Str * loc_str, Bool * cond) {
    Str *_t1003 = Str_lit("Str", 3ULL);
    U64 _t1004; { U64 *_hp = Str_size(); _t1004 = *_hp; free(_hp); }
    U64 _t1005 = 0;
    Array *_va16 = Array_new(_t1003, &(U64){_t1004}, &(U64){_t1005});
    Str_delete(_t1003, &(Bool){1});
    ;
    ;
    Bool _t1006; { Bool *_hp = assertm(loc_str, cond, _va16); _t1006 = *_hp; free(_hp); }
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t1006; return _r; }
}

void test_expect(Str * loc_str, Bool * cond, Array * parts) {
    Array *_t1007 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    Bool _t1008; { Bool *_hp = assertm(loc_str, cond, _t1007); _t1008 = *_hp; free(_hp); }
    ;
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool _t1022; { Bool *_hp = I64_neq(a, b); _t1022 = *_hp; free(_hp); }
    if (_t1022) {
        Str *_t1009 = Str_lit("Str", 3ULL);
        U64 _t1010; { U64 *_hp = Str_size(); _t1010 = *_hp; free(_hp); }
        U64 _t1011 = 5;
        Array *_va17 = Array_new(_t1009, &(U64){_t1010}, &(U64){_t1011});
        Str_delete(_t1009, &(Bool){1});
        ;
        ;
        U64 _t1012 = 0;
        Str *_t1013 = Str_lit("assert_eq failed: expected '", 28ULL);
        Array_set(_va17, &(U64){_t1012}, _t1013);
        ;
        U64 _t1014 = 1;
        Str *_t1015 = I64_to_str(a);
        Array_set(_va17, &(U64){_t1014}, _t1015);
        ;
        U64 _t1016 = 2;
        Str *_t1017 = Str_lit("', found '", 10ULL);
        Array_set(_va17, &(U64){_t1016}, _t1017);
        ;
        U64 _t1018 = 3;
        Str *_t1019 = I64_to_str(b);
        Array_set(_va17, &(U64){_t1018}, _t1019);
        ;
        U64 _t1020 = 4;
        Str *_t1021 = Str_lit("'", 1ULL);
        Array_set(_va17, &(U64){_t1020}, _t1021);
        ;
        panic(loc_str, _va17);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool _t1036; { Bool *_hp = Str_eq(a, b); _t1036 = *_hp; free(_hp); }
    Bool _t1037 = Bool_not(_t1036);
    ;
    if (_t1037) {
        Str *_t1023 = Str_lit("Str", 3ULL);
        U64 _t1024; { U64 *_hp = Str_size(); _t1024 = *_hp; free(_hp); }
        U64 _t1025 = 5;
        Array *_va18 = Array_new(_t1023, &(U64){_t1024}, &(U64){_t1025});
        Str_delete(_t1023, &(Bool){1});
        ;
        ;
        U64 _t1026 = 0;
        Str *_t1027 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        Array_set(_va18, &(U64){_t1026}, _t1027);
        ;
        U64 _t1028 = 1;
        Str *_t1029 = Str_clone(a);
        Array_set(_va18, &(U64){_t1028}, _t1029);
        ;
        U64 _t1030 = 2;
        Str *_t1031 = Str_lit("', found '", 10ULL);
        Array_set(_va18, &(U64){_t1030}, _t1031);
        ;
        U64 _t1032 = 3;
        Str *_t1033 = Str_clone(b);
        Array_set(_va18, &(U64){_t1032}, _t1033);
        ;
        U64 _t1034 = 4;
        Str *_t1035 = Str_lit("'", 1ULL);
        Array_set(_va18, &(U64){_t1034}, _t1035);
        ;
        panic(loc_str, _va18);
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
    _t1038 = malloc(sizeof(I64));
    *_t1038 = 0;
    _t1039 = malloc(sizeof(I64));
    *_t1039 = 1;
    _t1040 = malloc(sizeof(I64)); *_t1040 = I64_sub(DEREF(_t1038), DEREF(_t1039));
    CAP_LIT = U64_from_i64(_t1040);
    _t1041 = malloc(sizeof(I64));
    *_t1041 = 0;
    _t1042 = malloc(sizeof(I64));
    *_t1042 = 2;
    _t1043 = malloc(sizeof(I64)); *_t1043 = I64_sub(DEREF(_t1041), DEREF(_t1042));
    CAP_VIEW = U64_from_i64(_t1043);
}

