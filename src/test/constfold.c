#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

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


void U64_delete(U64 * self, Bool * call_free);
U32 * U64_size(void);
Str * U32_to_str(U32 * val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool * call_free);
U32 * U32_size(void);
Bool U32_lt(U32 * a, U32 * b);
Bool U32_gt(U32 * a, U32 * b);
Bool U32_lte(U32 * a, U32 * b);
Bool U32_gte(U32 * a, U32 * b);
void I32_delete(I32 * self, Bool * call_free);
U32 * I32_size(void);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
U8 * Str_get(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Bool Str_is_empty(Str * self);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
Str * I64_to_str(I64 * val);
void I64_delete(I64 * self, Bool * call_free);
U32 * I64_size(void);
Bool I64_lt(I64 * a, I64 * b);
Bool I64_gt(I64 * a, I64 * b);
Bool I64_neq(I64 * a, I64 * b);
I64 * Bool_cmp(Bool * a, Bool * b);
void Bool_delete(Bool * self, Bool * call_free);
U32 * Bool_size(void);
void Type_delete(Type * self, Bool * call_free);
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
void assert_eq_str(Str * loc_str, Str * a, Str * b);
void println(Array * parts);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_lolalalo(void);
#include "ext.h"


Str *Str_lit(const char *s, unsigned long long len);
void print_single(Str *s);
void print_flush();

void U64_delete(U64 * self, Bool * call_free);
U32 * U64_size(void);
Str * U32_to_str(U32 * val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool * call_free);
U32 * U32_size(void);
Bool U32_lt(U32 * a, U32 * b);
Bool U32_gt(U32 * a, U32 * b);
Bool U32_lte(U32 * a, U32 * b);
Bool U32_gte(U32 * a, U32 * b);
void I32_delete(I32 * self, Bool * call_free);
U32 * I32_size(void);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
U8 * Str_get(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Bool Str_is_empty(Str * self);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
Str * I64_to_str(I64 * val);
void I64_delete(I64 * self, Bool * call_free);
U32 * I64_size(void);
Bool I64_lt(I64 * a, I64 * b);
Bool I64_gt(I64 * a, I64 * b);
Bool I64_neq(I64 * a, I64 * b);
I64 * Bool_cmp(Bool * a, Bool * b);
void Bool_delete(Bool * self, Bool * call_free);
U32 * Bool_size(void);
void Type_delete(Type * self, Bool * call_free);
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
void assert_eq_str(Str * loc_str, Str * a, Str * b);
void println(Array * parts);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_lolalalo(void);
Bool * Type_eq(Type *, Type *);
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

void U64_delete(U64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U64_size(void) {
    I64 _t_I64_27 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_27; return _r; }
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
    U32 _t_U32_45 = U32_add(DEREF(self), _t_U32_44);
    (void)_t_U32_45;
    ;
    *self = _t_U32_45;
    ;
}

void U32_dec(U32 * self) {
    (void)self;
    U32 _t_U32_46 = 1;
    U32 _t_U32_47 = U32_sub(DEREF(self), _t_U32_46);
    (void)_t_U32_47;
    ;
    *self = _t_U32_47;
    ;
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
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_57; return _r; }
}

Bool U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_58 = 0;
    I64 _t_I64_59 = 1;
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
    Bool _t_Bool_65 = I64_eq(_t_I64_63, _t_I64_64);
    (void)_t_Bool_65;
    ;
    ;
    return _t_Bool_65;
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

void I32_delete(I32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I32_size(void) {
    I64 _t_I64_99 = 4;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_99; return _r; }
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
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_127; return _r; }
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    {
        Array *_fc_Array_393 = parts;
        (void)_fc_Array_393;
        (void)_fc_Array_393;
        U32 _fi_USize_393 = 0;
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
            U32 _t_U32_396 = 1;
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
    ;
    {
        Array *_fc_Array_400 = parts;
        (void)_fc_Array_400;
        (void)_fc_Array_400;
        U32 _fi_USize_400 = 0;
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
            U32 _t_U32_403 = 1;
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
        Array *_va_Array_9 = Array_new(_t_Type_406, &_t_U32_407);
        (void)_va_Array_9;
        Type_delete(_t_Type_406, &(Bool){1});
        ;
        U32 _t_U32_408 = 0;
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
    (void)_t_v_412;
    return _t_v_412;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
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
                U32_inc(&_rc_U32_414);
                U8 *ab = Str_get(a, &i);
                U8 *bb = Str_get(b, &i);
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                ;
                I64 _t_I64_416 = 0;
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
                U32_dec(&_rc_U32_414);
                U8 *ab = Str_get(a, &i);
                U8 *bb = Str_get(b, &i);
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                ;
                I64 _t_I64_419 = 0;
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

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_425 = 1;
    U32 _t_U64_426 = U32_add(DEREF(n), _t_U32_425);
    (void)_t_U64_426;
    ;
    void * buf = malloc(_t_U64_426);
    ;
    I32 _t_I32_427 = 0;
    U64 _t_U64_428 = 1;
    memset(buf, _t_I32_427, _t_U64_428);
    ;
    ;
    I64 _t_I64_429 = 0;
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
        Array *_va_Array_10 = Array_new(_t_Type_432, &_t_U32_433);
        (void)_va_Array_10;
        Type_delete(_t_Type_432, &(Bool){1});
        ;
        U32 _t_U32_434 = 0;
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
    Bool _t_Bool_444 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_444;
    if (_t_Bool_444) {
        Str *_t_Str_437 = Str_lit("Str", 3ULL);
        (void)_t_Str_437;
        Type *_t_Type_438 = Type_Struct(_t_Str_437);
        (void)_t_Type_438;
        Str_delete(_t_Str_437, &(Bool){1});
        U32 _t_U32_439 = 1;
        Array *_va_Array_11 = Array_new(_t_Type_438, &_t_U32_439);
        (void)_va_Array_11;
        Type_delete(_t_Type_438, &(Bool){1});
        ;
        U32 _t_U32_440 = 0;
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
    (void)_t_v_445;
    memcpy(_t_v_445, s->c_str, s->count);
    U32 _t_U32_446 = U32_clone(&new_len);
    (void)_t_U32_446;
    self->count = _t_U32_446;
    ;
    void *_t_v_447 = ptr_add(self->c_str, new_len);
    (void)_t_v_447;
    (void)_t_v_447;
    I32 _t_I32_448 = 0;
    U64 _t_U64_449 = 1;
    memset(_t_v_447, _t_I32_448, _t_U64_449);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_450 = 1;
    U32 _t_U64_451 = U32_add(val->count, _t_U32_450);
    (void)_t_U64_451;
    ;
    void * new_data = malloc(_t_U64_451);
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_452 = ptr_add(new_data, val->count);
    (void)_t_v_452;
    (void)_t_v_452;
    I32 _t_I32_453 = 0;
    U64 _t_U64_454 = 1;
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

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_522 = 0;
    Bool _t_Bool_523 = U32_eq(self->count, _t_U32_522);
    (void)_t_Bool_523;
    ;
    return _t_Bool_523;
}

U32 Str_size(void) {
    I64 _t_I64_808 = 16;
    return _t_I64_808;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_809 = Str_cmp(a, b);
    (void)_t_I64_809;
    I64 _t_I64_810 = 0;
    Bool _t_Bool_811 = I64_eq(_t_I64_809, _t_I64_810);
    (void)_t_Bool_811;
    ;
    ;
    return _t_Bool_811;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_857 = 8;
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

Str * I64_to_str(I64 * val) {
    (void)val;
    I64 _t_I64_938 = 0;
    Bool _t_Bool_939 = I64_eq(DEREF(val), _t_I64_938);
    (void)_t_Bool_939;
    ;
    if (_t_Bool_939) {
        U64 _t_U64_902 = 2;
        void * buf = malloc(_t_U64_902);
        ;
        I64 _t_I64_903 = 48;
        U64 _t_U64_904 = 1;
        memcpy(buf, &_t_I64_903, _t_U64_904);
        ;
        ;
        U64 _t_U64_905 = 1;
        void *_t_v_906 = ptr_add(buf, _t_U64_905);
        (void)_t_v_906;
        (void)_t_v_906;
        I32 _t_I32_907 = 0;
        U64 _t_U64_908 = 1;
        memset(_t_v_906, _t_I32_907, _t_U64_908);
        ;
        ;
        ;
        I64 _t_I64_909 = 1;
        I64 _t_I64_910 = 1;
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
    I64 v = I64_clone(val);
    I64 _t_I64_940 = 0;
    Bool _t_Bool_941 = I64_lt(val, &_t_I64_940);
    (void)_t_Bool_941;
    ;
    if (_t_Bool_941) {
        Bool _t_Bool_912 = 1;
        is_neg = _t_Bool_912;
        ;
        I64 _t_I64_913 = 0;
        I64 _t_I64_914 = I64_sub(_t_I64_913, DEREF(val));
        (void)_t_I64_914;
        ;
        v = _t_I64_914;
        ;
    }
    ;
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 _t_I64_916 = 0;
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
        U64 _t_U64_918 = U64_add(ndigits, _t_U64_917);
        (void)_t_U64_918;
        ;
        ndigits = _t_U64_918;
        ;
        I64 _t_I64_919 = 10;
        I64 _t_I64_920 = I64_div(tmp, _t_I64_919);
        (void)_t_I64_920;
        ;
        tmp = _t_I64_920;
        ;
    }
    ;
    U64 total = U64_clone(&ndigits);
    ;
    if (is_neg) {
        U64 _t_U64_921 = 1;
        U64 _t_U64_922 = U64_add(total, _t_U64_921);
        (void)_t_U64_922;
        ;
        total = _t_U64_922;
        ;
    }
    U64 _t_U64_942 = 1;
    U64 _t_U64_943 = U64_add(total, _t_U64_942);
    (void)_t_U64_943;
    ;
    void * buf = malloc(_t_U64_943);
    ;
    if (is_neg) {
        I64 _t_I64_923 = 45;
        U64 _t_U64_924 = 1;
        memcpy(buf, &_t_I64_923, _t_U64_924);
        ;
        ;
    }
    ;
    U64 _t_U64_944 = 1;
    U64 i = U64_sub(total, _t_U64_944);
    ;
    while (1) {
        I64 _t_I64_926 = 0;
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
        I64 _t_I64_928 = I64_mod(v, _t_I64_927);
        (void)_t_I64_928;
        ;
        I64 _t_I64_929 = 48;
        I64 _t_I64_930 = I64_add(_t_I64_928, _t_I64_929);
        (void)_t_I64_930;
        ;
        ;
        void *_t_v_931 = ptr_add(buf, i);
        (void)_t_v_931;
        (void)_t_v_931;
        U8 _t_U8_932 = I64_to_u8(_t_I64_930);
        (void)_t_U8_932;
        ;
        U64 _t_U64_933 = 1;
        memcpy(_t_v_931, &_t_U8_932, _t_U64_933);
        ;
        ;
        I64 _t_I64_934 = 10;
        I64 _t_I64_935 = I64_div(v, _t_I64_934);
        (void)_t_I64_935;
        ;
        v = _t_I64_935;
        ;
        U64 _t_U64_936 = 1;
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
    (void)_t_v_945;
    I32 _t_I32_946 = 0;
    U64 _t_U64_947 = 1;
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

void I64_delete(I64 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 _t_I64_966 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_966; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_967 = 0;
    I64 _t_I64_968 = 1;
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

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_987 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_987;
    if (_t_Bool_987) {
        I64 _t_I64_983 = 0;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_983; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_984 = 0;
        I64 _t_I64_985 = 1;
        I64 _t_I64_986 = I64_sub(_t_I64_984, _t_I64_985);
        (void)_t_I64_986;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_986; return _r; }
    }
    I64 _t_I64_988 = 1;
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
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_989; return _r; }
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
void Type_delete(Type * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_1198 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)_t_Bool_1198;
    if (_t_Bool_1198) {
        Str *_t_Str_1192 = get_payload(self);
        (void)_t_Str_1192;
        (void)_t_Str_1192;
        Bool _t_Bool_1193 = 0;
        Str_delete(_t_Str_1192, &_t_Bool_1193);
        ;
    }
    ;
    Bool _t_Bool_1199 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1199;
    if (_t_Bool_1199) {
        Str *_t_Str_1194 = get_payload(self);
        (void)_t_Str_1194;
        (void)_t_Str_1194;
        Bool _t_Bool_1195 = 0;
        Str_delete(_t_Str_1194, &_t_Bool_1195);
        ;
    }
    ;
    Bool _t_Bool_1200 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)_t_Bool_1200;
    if (_t_Bool_1200) {
        Str *_t_Str_1196 = get_payload(self);
        (void)_t_Str_1196;
        (void)_t_Str_1196;
        Bool _t_Bool_1197 = 0;
        Str_delete(_t_Str_1196, &_t_Bool_1197);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    (void)self;
    Bool _t_Bool_1267 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)_t_Bool_1267;
    if (_t_Bool_1267) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown; return _r; }
    }
    ;
    Bool _t_Bool_1268 = is(self, &(Type){.tag = Type_TAG_None});
    (void)_t_Bool_1268;
    if (_t_Bool_1268) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None; return _r; }
    }
    ;
    Bool _t_Bool_1269 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)_t_Bool_1269;
    if (_t_Bool_1269) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64; return _r; }
    }
    ;
    Bool _t_Bool_1270 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)_t_Bool_1270;
    if (_t_Bool_1270) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8; return _r; }
    }
    ;
    Bool _t_Bool_1271 = is(self, &(Type){.tag = Type_TAG_I16});
    (void)_t_Bool_1271;
    if (_t_Bool_1271) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I16; return _r; }
    }
    ;
    Bool _t_Bool_1272 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)_t_Bool_1272;
    if (_t_Bool_1272) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32; return _r; }
    }
    ;
    Bool _t_Bool_1273 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)_t_Bool_1273;
    if (_t_Bool_1273) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32; return _r; }
    }
    ;
    Bool _t_Bool_1274 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)_t_Bool_1274;
    if (_t_Bool_1274) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64; return _r; }
    }
    ;
    Bool _t_Bool_1275 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)_t_Bool_1275;
    if (_t_Bool_1275) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32; return _r; }
    }
    ;
    Bool _t_Bool_1276 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)_t_Bool_1276;
    if (_t_Bool_1276) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool; return _r; }
    }
    ;
    Bool _t_Bool_1277 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)_t_Bool_1277;
    if (_t_Bool_1277) {
        Str *_clone_payload_Struct_10 = get_payload(self);
        (void)_clone_payload_Struct_10;
        (void)_clone_payload_Struct_10;
        Type *_t_Type_1265 = Type_Struct(_clone_payload_Struct_10);
        (void)_t_Type_1265;
        ;
        return _t_Type_1265;
    }
    ;
    Bool _t_Bool_1278 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)_t_Bool_1278;
    if (_t_Bool_1278) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef; return _r; }
    }
    ;
    Bool _t_Bool_1279 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1279;
    if (_t_Bool_1279) {
        Str *_clone_payload_Enum_12 = get_payload(self);
        (void)_clone_payload_Enum_12;
        (void)_clone_payload_Enum_12;
        Type *_t_Type_1266 = Type_Enum(_clone_payload_Enum_12);
        (void)_t_Type_1266;
        ;
        return _t_Type_1266;
    }
    ;
    Bool _t_Bool_1280 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)_t_Bool_1280;
    if (_t_Bool_1280) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef; return _r; }
    }
    ;
    Bool _t_Bool_1281 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)_t_Bool_1281;
    if (_t_Bool_1281) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef; return _r; }
    }
    ;
    Bool _t_Bool_1282 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)_t_Bool_1282;
    if (_t_Bool_1282) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr; return _r; }
    }
    ;
    Bool _t_Bool_1283 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)_t_Bool_1283;
    if (_t_Bool_1283) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic; return _r; }
    }
    ;
    Str *_clone_payload_Custom_17 = get_payload(self);
    (void)_clone_payload_Custom_17;
    (void)_clone_payload_Custom_17;
    Type *_t_Type_1284 = Type_Custom(_clone_payload_Custom_17);
    (void)_t_Type_1284;
    return _t_Type_1284;
}

U32 Type_size(void) {
    I64 _t_I64_1285 = 24;
    return _t_I64_1285;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    (void)elem_type;
    (void)cap;
    Bool _t_Bool_2429 = Str_is_empty(elem_type);
    (void)_t_Bool_2429;
    if (_t_Bool_2429) {
        Str *_t_Str_2423 = Str_lit("Str", 3ULL);
        (void)_t_Str_2423;
        Type *_t_Type_2424 = Type_Struct(_t_Str_2423);
        (void)_t_Type_2424;
        Str_delete(_t_Str_2423, &(Bool){1});
        U32 _t_U32_2425 = 1;
        Array *_va_Array_73 = Array_new(_t_Type_2424, &_t_U32_2425);
        (void)_va_Array_73;
        Type_delete(_t_Type_2424, &(Bool){1});
        ;
        U32 _t_U32_2426 = 0;
        Str *_t_Str_2427 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_2427;
        Array_set(_va_Array_73, &_t_U32_2426, _t_Str_2427);
        ;
        Str *_t_Str_2428 = Str_lit("./src/core/array.til:23:41", 26ULL);
        (void)_t_Str_2428;
        panic(_t_Str_2428, _va_Array_73);
        Str_delete(_t_Str_2428, &(Bool){1});
    }
    ;
    U32 elem_size = dyn_size_of(elem_type);
    void * _t_v_2430 = calloc(DEREF(cap), elem_size);
    (void)_t_v_2430;
    void * _t_v_2431 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2431;
    void * _t_v_2432 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2432;
    Array *_t_Array_2433 = malloc(sizeof(Array));
    _t_Array_2433->data = _t_v_2430;
    _t_Array_2433->cap = DEREF(cap);
    _t_Array_2433->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); _t_Array_2433->elem_type = *_ca; free(_ca); }
    _t_Array_2433->elem_clone = _t_v_2431;
    _t_Array_2433->elem_delete = _t_v_2432;
    (void)_t_Array_2433;
    ;
    return _t_Array_2433;
}

Array * Array_new(Type * T, U32 * cap) {
    (void)T;
    (void)cap;
    Str *elem_type = dyn_type_to_str(T);
    Array *_t_Array_2434 = Array_new_type_name(elem_type, cap);
    (void)_t_Array_2434;
    Str_delete(elem_type, &(Bool){1});
    return _t_Array_2434;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_2449 = U32_gte(i, &self->cap);
    (void)_t_Bool_2449;
    if (_t_Bool_2449) {
        Str *_t_Str_2435 = Str_lit("Str", 3ULL);
        (void)_t_Str_2435;
        Type *_t_Type_2436 = Type_Struct(_t_Str_2435);
        (void)_t_Type_2436;
        Str_delete(_t_Str_2435, &(Bool){1});
        U32 _t_U32_2437 = 5;
        Array *_va_Array_74 = Array_new(_t_Type_2436, &_t_U32_2437);
        (void)_va_Array_74;
        Type_delete(_t_Type_2436, &(Bool){1});
        ;
        U32 _t_U32_2438 = 0;
        Str *_t_Str_2439 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_2439;
        Array_set(_va_Array_74, &_t_U32_2438, _t_Str_2439);
        ;
        U32 _t_U32_2440 = 1;
        Str *_t_Str_2441 = U32_to_str(i);
        (void)_t_Str_2441;
        Array_set(_va_Array_74, &_t_U32_2440, _t_Str_2441);
        ;
        U32 _t_U32_2442 = 2;
        Str *_t_Str_2443 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2443;
        Array_set(_va_Array_74, &_t_U32_2442, _t_Str_2443);
        ;
        U32 _t_U32_2444 = 3;
        Str *_t_Str_2445 = U32_to_str(&self->cap);
        (void)_t_Str_2445;
        Array_set(_va_Array_74, &_t_U32_2444, _t_Str_2445);
        ;
        U32 _t_U32_2446 = 4;
        Str *_t_Str_2447 = Str_lit(")", 1ULL);
        (void)_t_Str_2447;
        Array_set(_va_Array_74, &_t_U32_2446, _t_Str_2447);
        ;
        Str *_t_Str_2448 = Str_lit("./src/core/array.til:41:19", 26ULL);
        (void)_t_Str_2448;
        panic(_t_Str_2448, _va_Array_74);
        Str_delete(_t_Str_2448, &(Bool){1});
    }
    ;
    U32 _t_U64_2450 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2450;
    void *_t_v_2451 = ptr_add(self->data, _t_U64_2450);
    (void)_t_v_2451;
    (void)_t_v_2451;
    ;
    return _t_v_2451;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_2466 = U32_gte(i, &self->cap);
    (void)_t_Bool_2466;
    if (_t_Bool_2466) {
        Str *_t_Str_2452 = Str_lit("Str", 3ULL);
        (void)_t_Str_2452;
        Type *_t_Type_2453 = Type_Struct(_t_Str_2452);
        (void)_t_Type_2453;
        Str_delete(_t_Str_2452, &(Bool){1});
        U32 _t_U32_2454 = 5;
        Array *_va_Array_75 = Array_new(_t_Type_2453, &_t_U32_2454);
        (void)_va_Array_75;
        Type_delete(_t_Type_2453, &(Bool){1});
        ;
        U32 _t_U32_2455 = 0;
        Str *_t_Str_2456 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_2456;
        Array_set(_va_Array_75, &_t_U32_2455, _t_Str_2456);
        ;
        U32 _t_U32_2457 = 1;
        Str *_t_Str_2458 = U32_to_str(i);
        (void)_t_Str_2458;
        Array_set(_va_Array_75, &_t_U32_2457, _t_Str_2458);
        ;
        U32 _t_U32_2459 = 2;
        Str *_t_Str_2460 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2460;
        Array_set(_va_Array_75, &_t_U32_2459, _t_Str_2460);
        ;
        U32 _t_U32_2461 = 3;
        Str *_t_Str_2462 = U32_to_str(&self->cap);
        (void)_t_Str_2462;
        Array_set(_va_Array_75, &_t_U32_2461, _t_Str_2462);
        ;
        U32 _t_U32_2463 = 4;
        Str *_t_Str_2464 = Str_lit(")", 1ULL);
        (void)_t_Str_2464;
        Array_set(_va_Array_75, &_t_U32_2463, _t_Str_2464);
        ;
        Str *_t_Str_2465 = Str_lit("./src/core/array.til:50:19", 26ULL);
        (void)_t_Str_2465;
        panic(_t_Str_2465, _va_Array_75);
        Str_delete(_t_Str_2465, &(Bool){1});
    }
    ;
    U32 _t_U64_2467 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2467;
    void *_t_v_2468 = ptr_add(self->data, _t_U64_2467);
    (void)_t_v_2468;
    (void)_t_v_2468;
    Bool _t_Bool_2469 = 0;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2468, &_t_Bool_2469);
    ;
    ;
    U32 _t_U64_2470 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2470;
    void *_t_v_2471 = ptr_add(self->data, _t_U64_2470);
    (void)_t_v_2471;
    (void)_t_v_2471;
    memcpy(_t_v_2471, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_2472 = self->cap;
        (void)_re_U32_2472;
        U32 _rc_U32_2472 = 0;
        Bool _t_Bool_2481 = U32_lte(&_rc_U32_2472, &_re_U32_2472);
        (void)_t_Bool_2481;
        if (_t_Bool_2481) {
            while (1) {
                Bool _wcond_Bool_2473 = U32_lt(&_rc_U32_2472, &_re_U32_2472);
                (void)_wcond_Bool_2473;
                if (_wcond_Bool_2473) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2472);
                U32_inc(&_rc_U32_2472);
                U32 _t_U64_2474 = U32_mul(i, self->elem_size);
                (void)_t_U64_2474;
                ;
                void *_t_v_2475 = ptr_add(self->data, _t_U64_2474);
                (void)_t_v_2475;
                (void)_t_v_2475;
                Bool _t_Bool_2476 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2475, &_t_Bool_2476);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2477 = U32_gt(&_rc_U32_2472, &_re_U32_2472);
                (void)_wcond_Bool_2477;
                if (_wcond_Bool_2477) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2472);
                U32_dec(&_rc_U32_2472);
                U32 _t_U64_2478 = U32_mul(i, self->elem_size);
                (void)_t_U64_2478;
                ;
                void *_t_v_2479 = ptr_add(self->data, _t_U64_2478);
                (void)_t_v_2479;
                (void)_t_v_2479;
                Bool _t_Bool_2480 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2479, &_t_Bool_2480);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_2482 = 0;
    Str_delete(&self->elem_type, &_t_Bool_2482);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_2495 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_2495;
    void * new_data = malloc(_t_U64_2495);
    ;
    {
        U32 _re_U32_2483 = self->cap;
        (void)_re_U32_2483;
        U32 _rc_U32_2483 = 0;
        Bool _t_Bool_2494 = U32_lte(&_rc_U32_2483, &_re_U32_2483);
        (void)_t_Bool_2494;
        if (_t_Bool_2494) {
            while (1) {
                Bool _wcond_Bool_2484 = U32_lt(&_rc_U32_2483, &_re_U32_2483);
                (void)_wcond_Bool_2484;
                if (_wcond_Bool_2484) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2483);
                U32_inc(&_rc_U32_2483);
                U32 _t_U64_2485 = U32_mul(i, self->elem_size);
                (void)_t_U64_2485;
                void *_t_v_2486 = ptr_add(self->data, _t_U64_2485);
                (void)_t_v_2486;
                (void)_t_v_2486;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2486);
                ;
                U32 _t_U64_2487 = U32_mul(i, self->elem_size);
                (void)_t_U64_2487;
                ;
                void *_t_v_2488 = ptr_add(new_data, _t_U64_2487);
                (void)_t_v_2488;
                (void)_t_v_2488;
                memcpy(_t_v_2488, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2489 = U32_gt(&_rc_U32_2483, &_re_U32_2483);
                (void)_wcond_Bool_2489;
                if (_wcond_Bool_2489) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2483);
                U32_dec(&_rc_U32_2483);
                U32 _t_U64_2490 = U32_mul(i, self->elem_size);
                (void)_t_U64_2490;
                void *_t_v_2491 = ptr_add(self->data, _t_U64_2490);
                (void)_t_v_2491;
                (void)_t_v_2491;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2491);
                ;
                U32 _t_U64_2492 = U32_mul(i, self->elem_size);
                (void)_t_U64_2492;
                ;
                void *_t_v_2493 = ptr_add(new_data, _t_U64_2492);
                (void)_t_v_2493;
                (void)_t_v_2493;
                memcpy(_t_v_2493, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_2496 = malloc(sizeof(Array));
    _t_Array_2496->data = new_data;
    _t_Array_2496->cap = self->cap;
    _t_Array_2496->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_2496->elem_type = *_ca; free(_ca); }
    _t_Array_2496->elem_clone = (void *)self->elem_clone;
    _t_Array_2496->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_2496;
    return _t_Array_2496;
}

U32 Array_size(void) {
    I64 _t_I64_2497 = 48;
    return _t_I64_2497;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2736 = Str_lit("Str", 3ULL);
    (void)_t_Str_2736;
    Type *_t_Type_2737 = Type_Struct(_t_Str_2736);
    (void)_t_Type_2737;
    Str_delete(_t_Str_2736, &(Bool){1});
    U32 _t_U32_2738 = 3;
    Array *_va_Array_92 = Array_new(_t_Type_2737, &_t_U32_2738);
    (void)_va_Array_92;
    Type_delete(_t_Type_2737, &(Bool){1});
    ;
    U32 _t_U32_2739 = 0;
    Str *_t_Str_2740 = Str_clone(loc_str);
    (void)_t_Str_2740;
    Array_set(_va_Array_92, &_t_U32_2739, _t_Str_2740);
    ;
    U32 _t_U32_2741 = 1;
    Str *_t_Str_2742 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2742;
    Array_set(_va_Array_92, &_t_U32_2741, _t_Str_2742);
    ;
    Array *_t_Array_2743 = Array_clone(parts);
    (void)_t_Array_2743;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2744 = 2;
    Str *_t_Str_2745 = format(_t_Array_2743);
    (void)_t_Str_2745;
    Array_set(_va_Array_92, &_t_U32_2744, _t_Str_2745);
    ;
    println(_va_Array_92);
    I64 _t_I64_2746 = 1;
    exit(_t_I64_2746);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2765 = not(DEREF(cond));
    (void)_t_Bool_2765;
    if (_t_Bool_2765) {
        Str *_t_Str_2760 = Str_lit("Str", 3ULL);
        (void)_t_Str_2760;
        Type *_t_Type_2761 = Type_Struct(_t_Str_2760);
        (void)_t_Type_2761;
        Str_delete(_t_Str_2760, &(Bool){1});
        U32 _t_U32_2762 = 1;
        Array *_va_Array_95 = Array_new(_t_Type_2761, &_t_U32_2762);
        (void)_va_Array_95;
        Type_delete(_t_Type_2761, &(Bool){1});
        ;
        U32 _t_U32_2763 = 0;
        Str *_t_Str_2764 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2764;
        Array_set(_va_Array_95, &_t_U32_2763, _t_Str_2764);
        ;
        panic(loc_str, _va_Array_95);
    }
    ;
    Bool _t_Bool_2766 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2766; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2789 = I64_neq(a, b);
    (void)_t_Bool_2789;
    if (_t_Bool_2789) {
        Str *_t_Str_2776 = Str_lit("Str", 3ULL);
        (void)_t_Str_2776;
        Type *_t_Type_2777 = Type_Struct(_t_Str_2776);
        (void)_t_Type_2777;
        Str_delete(_t_Str_2776, &(Bool){1});
        U32 _t_U32_2778 = 5;
        Array *_va_Array_97 = Array_new(_t_Type_2777, &_t_U32_2778);
        (void)_va_Array_97;
        Type_delete(_t_Type_2777, &(Bool){1});
        ;
        U32 _t_U32_2779 = 0;
        Str *_t_Str_2780 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2780;
        Array_set(_va_Array_97, &_t_U32_2779, _t_Str_2780);
        ;
        U32 _t_U32_2781 = 1;
        Str *_t_Str_2782 = I64_to_str(a);
        (void)_t_Str_2782;
        Array_set(_va_Array_97, &_t_U32_2781, _t_Str_2782);
        ;
        U32 _t_U32_2783 = 2;
        Str *_t_Str_2784 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2784;
        Array_set(_va_Array_97, &_t_U32_2783, _t_Str_2784);
        ;
        U32 _t_U32_2785 = 3;
        Str *_t_Str_2786 = I64_to_str(b);
        (void)_t_Str_2786;
        Array_set(_va_Array_97, &_t_U32_2785, _t_Str_2786);
        ;
        U32 _t_U32_2787 = 4;
        Str *_t_Str_2788 = Str_lit("'", 1ULL);
        (void)_t_Str_2788;
        Array_set(_va_Array_97, &_t_U32_2787, _t_Str_2788);
        ;
        panic(loc_str, _va_Array_97);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2803 = Str_eq(a, b);
    (void)_t_Bool_2803;
    Bool _t_Bool_2804 = not(_t_Bool_2803);
    (void)_t_Bool_2804;
    ;
    if (_t_Bool_2804) {
        Str *_t_Str_2790 = Str_lit("Str", 3ULL);
        (void)_t_Str_2790;
        Type *_t_Type_2791 = Type_Struct(_t_Str_2790);
        (void)_t_Type_2791;
        Str_delete(_t_Str_2790, &(Bool){1});
        U32 _t_U32_2792 = 5;
        Array *_va_Array_98 = Array_new(_t_Type_2791, &_t_U32_2792);
        (void)_va_Array_98;
        Type_delete(_t_Type_2791, &(Bool){1});
        ;
        U32 _t_U32_2793 = 0;
        Str *_t_Str_2794 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t_Str_2794;
        Array_set(_va_Array_98, &_t_U32_2793, _t_Str_2794);
        ;
        U32 _t_U32_2795 = 1;
        Str *_t_Str_2796 = Str_clone(a);
        (void)_t_Str_2796;
        Array_set(_va_Array_98, &_t_U32_2795, _t_Str_2796);
        ;
        U32 _t_U32_2797 = 2;
        Str *_t_Str_2798 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2798;
        Array_set(_va_Array_98, &_t_U32_2797, _t_Str_2798);
        ;
        U32 _t_U32_2799 = 3;
        Str *_t_Str_2800 = Str_clone(b);
        (void)_t_Str_2800;
        Array_set(_va_Array_98, &_t_U32_2799, _t_Str_2800);
        ;
        U32 _t_U32_2801 = 4;
        Str *_t_Str_2802 = Str_lit("'", 1ULL);
        (void)_t_Str_2802;
        Array_set(_va_Array_98, &_t_U32_2801, _t_Str_2802);
        ;
        panic(loc_str, _va_Array_98);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2805 = parts;
        (void)_fc_Array_2805;
        (void)_fc_Array_2805;
        U32 _fi_USize_2805 = 0;
        while (1) {
            U32 _t_U32_2807; { U32 *_hp = (U32 *)Array_len(_fc_Array_2805); _t_U32_2807 = *_hp; free(_hp); }
            (void)_t_U32_2807;
            Bool _wcond_Bool_2806 = U32_lt(&_fi_USize_2805, &_t_U32_2807);
            (void)_wcond_Bool_2806;
            ;
            if (_wcond_Bool_2806) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2805, &_fi_USize_2805);
            U32 _t_U32_2808 = 1;
            U32 _t_U32_2809 = U32_add(_fi_USize_2805, _t_U32_2808);
            (void)_t_U32_2809;
            ;
            _fi_USize_2805 = _t_U32_2809;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    Str *_t_Str_3003 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_3003;
    I64 _t_I64_3004 = 3;
    assert_eq(_t_Str_3003, &result, &_t_I64_3004);
    ;
    Str_delete(_t_Str_3003, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str *_t_Str_3011 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_3011;
    I64 _t_I64_3012 = 15;
    assert_eq(_t_Str_3011, &result, &_t_I64_3012);
    ;
    Str_delete(_t_Str_3011, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str *_t_Str_3019 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_3019;
    I64 _t_I64_3020 = 26;
    assert_eq(_t_Str_3019, &result, &_t_I64_3020);
    ;
    Str_delete(_t_Str_3019, &(Bool){1});
    ;
}

void test_string_concat(void) {
    Str *_t_Str_3021 = Str_lit("hello", 5ULL);
    (void)_t_Str_3021;
    Str *_t_Str_3022 = Str_lit(" world", 6ULL);
    (void)_t_Str_3022;
    Str *result = Str_lit("hello world", 11ULL);
    Str_delete(_t_Str_3021, &(Bool){1});
    Str_delete(_t_Str_3022, &(Bool){1});
    Str *_t_Str_3023 = Str_lit("src/test/constfold.til:33:19", 28ULL);
    (void)_t_Str_3023;
    Str *_t_Str_3024 = Str_lit("hello world", 11ULL);
    (void)_t_Str_3024;
    assert_eq_str(_t_Str_3023, result, _t_Str_3024);
    Str_delete(_t_Str_3023, &(Bool){1});
    Str_delete(_t_Str_3024, &(Bool){1});
    Str_delete(result, &(Bool){1});
}

void test_lolalalo(void) {
    Str *_t_Str_3047 = Str_lit("lo", 2ULL);
    (void)_t_Str_3047;
    Str *_t_Str_3048 = Str_lit("la", 2ULL);
    (void)_t_Str_3048;
    Str *lo_la = Str_lit("lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", 224ULL);
    Str_delete(_t_Str_3047, &(Bool){1});
    Str_delete(_t_Str_3048, &(Bool){1});
    Str *_t_Str_3049 = Str_lit("la", 2ULL);
    (void)_t_Str_3049;
    Str *_t_Str_3050 = Str_lit("lo", 2ULL);
    (void)_t_Str_3050;
    Str *la_lo = Str_lit("lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", 224ULL);
    Str_delete(_t_Str_3049, &(Bool){1});
    Str_delete(_t_Str_3050, &(Bool){1});
    Str *_t_Str_3051 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_3051;
    Str *_t_Str_3052 = Str_lit("src/test/constfold.til:62:12", 28ULL);
    (void)_t_Str_3052;
    Bool _t_Bool_3053 = 1;
    Str_delete(_t_Str_3051, &(Bool){1});
    assert(_t_Str_3052, &_t_Bool_3053);
    ;
    Str_delete(_t_Str_3052, &(Bool){1});
    Str *_t_Str_3055 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_3055;
    Str *_t_Str_3056 = Str_lit("src/test/constfold.til:63:12", 28ULL);
    (void)_t_Str_3056;
    Bool _t_Bool_3057 = 1;
    Str_delete(_t_Str_3055, &(Bool){1});
    assert(_t_Str_3056, &_t_Bool_3057);
    ;
    Str_delete(_t_Str_3056, &(Bool){1});
    Str *_t_Str_3059 = Str_lit("lolei", 5ULL);
    (void)_t_Str_3059;
    Str *_t_Str_3060 = Str_lit("src/test/constfold.til:65:12", 28ULL);
    (void)_t_Str_3060;
    Bool _t_Bool_3061 = 1;
    Str_delete(_t_Str_3059, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    assert(_t_Str_3060, &_t_Bool_3061);
    ;
    Str_delete(_t_Str_3060, &(Bool){1});
    Str *_t_Str_3063 = Str_lit("lalei", 5ULL);
    (void)_t_Str_3063;
    Str *_t_Str_3064 = Str_lit("src/test/constfold.til:66:12", 28ULL);
    (void)_t_Str_3064;
    Bool _t_Bool_3065 = 1;
    Str_delete(_t_Str_3063, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    assert(_t_Str_3064, &_t_Bool_3065);
    ;
    Str_delete(_t_Str_3064, &(Bool){1});
}

void *U64_add_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_add(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_sub_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_sub(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U64_cmp(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_clone_dyn(void *_a0) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(_a0); return _r;
}
void *U32_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = U32_to_i64(*(U32 *)_a0); return _r;
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
void *U32_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_eq(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U32_cmp(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_clone_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(_a0); return _r;
}
void *U32_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_lt(_a0, _a1); return _r;
}
void *U32_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_gt(_a0, _a1); return _r;
}
void *U32_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_lte(_a0, _a1); return _r;
}
void *U32_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_gte(_a0, _a1); return _r;
}
void *I32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I32_cmp(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_clone_dyn(void *_a0) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(_a0); return _r;
}
void *U8_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U8_cmp(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_clone_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(_a0); return _r;
}
void *Str_len_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = Str_len(_a0); return _r;
}
void *Str_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = Str_cmp(_a0, _a1); return _r;
}
void *Str_is_empty_dyn(void *_a0) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_is_empty(_a0); return _r;
}
void *Str_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Str_size(); return _r;
}
void *Str_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_eq(_a0, _a1); return _r;
}
void *I64_to_u8_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = I64_to_u8(*(I64 *)_a0); return _r;
}
void *I64_to_usize_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = I64_to_usize(*(I64 *)_a0); return _r;
}
void *I64_add_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_add(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_sub_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_sub(*(I64 *)_a0, *(I64 *)_a1); return _r;
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
void *I64_clone_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(_a0); return _r;
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
void *Bool_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_eq(*(Bool *)_a0, *(Bool *)_a1); return _r;
}
void *Bool_clone_dyn(void *_a0) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(_a0); return _r;
}
void *Type_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Type_size(); return _r;
}
void *Array_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Array_size(); return _r;
}
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U64_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U64_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)U32_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)U32_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U32_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U32_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)U32_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)U32_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)U32_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)U32_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U32_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U32_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U32_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U32_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U32_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I32_size;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U8_delete;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U8_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Str_len_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Str_get;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Str_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)Str_with_capacity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)Str_push_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Str_clone;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Str_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_empty", 8ULL) == 0) return (void*)Str_is_empty_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Str_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Str_eq_dyn;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Dynamic_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)I64_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "to_u8", 5ULL) == 0) return (void*)I64_to_u8_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "to_usize", 8ULL) == 0) return (void*)I64_to_usize_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)I64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)I64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)I64_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)I64_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)I64_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I64_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I64_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I64_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I64_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I64_neq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Bool_eq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Bool_cmp;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Bool_clone_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Bool_delete;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Bool_size;
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
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Type_delete;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return sizeof(U64);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return sizeof(U32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return sizeof(I32);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return sizeof(U8);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return sizeof(Str);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return sizeof(Dynamic);
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
    I64 _t_I64_852 = 1;
    I64 _t_I64_853 = I64_sub(_t_I64_851, _t_I64_852);
    (void)_t_I64_853;
    CAP_LIT = I64_to_usize(_t_I64_853);
    I64 _t_I64_854 = 0;
    I64 _t_I64_855 = 2;
    I64 _t_I64_856 = I64_sub(_t_I64_854, _t_I64_855);
    (void)_t_I64_856;
    CAP_VIEW = I64_to_usize(_t_I64_856);
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
    test_string_concat();
    fprintf(stderr, "  pass: %s\n", "test_string_concat");
    test_lolalalo();
    fprintf(stderr, "  pass: %s\n", "test_lolalalo");
    fprintf(stderr, "5/5 tests passed\n");
    return 0;
}
