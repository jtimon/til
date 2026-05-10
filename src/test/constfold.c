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
    (void)_t_I64_27;
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
    (void)_t_I64_99;
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
    (void)_t_I64_127;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_127; return _r; }
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

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_522 = 0;
    (void)_t_U32_522;
    Bool _t_Bool_523 = U32_eq(self->count, _t_U32_522);
    (void)_t_Bool_523;
    ;
    return _t_Bool_523;
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
        Bool _t_Bool_1193 = 0;
        (void)_t_Bool_1193;
        Str_delete(_t_Str_1192, &_t_Bool_1193);
        ;
    }
    ;
    Bool _t_Bool_1199 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1199;
    if (_t_Bool_1199) {
        Str *_t_Str_1194 = get_payload(self);
        (void)_t_Str_1194;
        Bool _t_Bool_1195 = 0;
        (void)_t_Bool_1195;
        Str_delete(_t_Str_1194, &_t_Bool_1195);
        ;
    }
    ;
    Bool _t_Bool_1200 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)_t_Bool_1200;
    if (_t_Bool_1200) {
        Str *_t_Str_1196 = get_payload(self);
        (void)_t_Str_1196;
        Bool _t_Bool_1197 = 0;
        (void)_t_Bool_1197;
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
    Type *_t_Type_1284 = Type_Custom(_clone_payload_Custom_17);
    (void)_t_Type_1284;
    return _t_Type_1284;
}

U32 Type_size(void) {
    I64 _t_I64_1285 = 24;
    (void)_t_I64_1285;
    return _t_I64_1285;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    (void)elem_type;
    (void)cap;
    Bool _t_Bool_2408 = Str_is_empty(elem_type);
    (void)_t_Bool_2408;
    if (_t_Bool_2408) {
        Str *_t_Str_2402 = Str_lit("Str", 3ULL);
        (void)_t_Str_2402;
        Type *_t_Type_2403 = Type_Struct(_t_Str_2402);
        (void)_t_Type_2403;
        Str_delete(_t_Str_2402, &(Bool){1});
        U32 _t_U32_2404 = 1;
        (void)_t_U32_2404;
        Array *_va_Array_73 = Array_new(_t_Type_2403, &_t_U32_2404);
        (void)_va_Array_73;
        Type_delete(_t_Type_2403, &(Bool){1});
        ;
        U32 _t_U32_2405 = 0;
        (void)_t_U32_2405;
        Str *_t_Str_2406 = Str_lit("Array.new: elem_type required", 29ULL);
        (void)_t_Str_2406;
        Array_set(_va_Array_73, &_t_U32_2405, _t_Str_2406);
        ;
        Str *_t_Str_2407 = Str_lit("./src/core/array.til:23:41", 26ULL);
        (void)_t_Str_2407;
        panic(_t_Str_2407, _va_Array_73);
        Str_delete(_t_Str_2407, &(Bool){1});
    }
    ;
    U32 elem_size = dyn_size_of(elem_type);
    (void)elem_size;
    void * _t_v_2409 = calloc(DEREF(cap), elem_size);
    (void)_t_v_2409;
    void * _t_v_2410 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2410;
    void * _t_v_2411 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2411;
    Array *_t_Array_2412 = malloc(sizeof(Array));
    _t_Array_2412->data = _t_v_2409;
    _t_Array_2412->cap = DEREF(cap);
    _t_Array_2412->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); _t_Array_2412->elem_type = *_ca; free(_ca); }
    _t_Array_2412->elem_clone = _t_v_2410;
    _t_Array_2412->elem_delete = _t_v_2411;
    (void)_t_Array_2412;
    ;
    return _t_Array_2412;
}

Array * Array_new(Type * T, U32 * cap) {
    (void)T;
    (void)cap;
    Str *elem_type = dyn_type_to_str(T);
    (void)elem_type;
    Array *_t_Array_2413 = Array_new_type_name(elem_type, cap);
    (void)_t_Array_2413;
    Str_delete(elem_type, &(Bool){1});
    return _t_Array_2413;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_2428 = U32_gte(i, &self->cap);
    (void)_t_Bool_2428;
    if (_t_Bool_2428) {
        Str *_t_Str_2414 = Str_lit("Str", 3ULL);
        (void)_t_Str_2414;
        Type *_t_Type_2415 = Type_Struct(_t_Str_2414);
        (void)_t_Type_2415;
        Str_delete(_t_Str_2414, &(Bool){1});
        U32 _t_U32_2416 = 5;
        (void)_t_U32_2416;
        Array *_va_Array_74 = Array_new(_t_Type_2415, &_t_U32_2416);
        (void)_va_Array_74;
        Type_delete(_t_Type_2415, &(Bool){1});
        ;
        U32 _t_U32_2417 = 0;
        (void)_t_U32_2417;
        Str *_t_Str_2418 = Str_lit("Array.get: index ", 17ULL);
        (void)_t_Str_2418;
        Array_set(_va_Array_74, &_t_U32_2417, _t_Str_2418);
        ;
        U32 _t_U32_2419 = 1;
        (void)_t_U32_2419;
        Str *_t_Str_2420 = U32_to_str(i);
        (void)_t_Str_2420;
        Array_set(_va_Array_74, &_t_U32_2419, _t_Str_2420);
        ;
        U32 _t_U32_2421 = 2;
        (void)_t_U32_2421;
        Str *_t_Str_2422 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2422;
        Array_set(_va_Array_74, &_t_U32_2421, _t_Str_2422);
        ;
        U32 _t_U32_2423 = 3;
        (void)_t_U32_2423;
        Str *_t_Str_2424 = U32_to_str(&self->cap);
        (void)_t_Str_2424;
        Array_set(_va_Array_74, &_t_U32_2423, _t_Str_2424);
        ;
        U32 _t_U32_2425 = 4;
        (void)_t_U32_2425;
        Str *_t_Str_2426 = Str_lit(")", 1ULL);
        (void)_t_Str_2426;
        Array_set(_va_Array_74, &_t_U32_2425, _t_Str_2426);
        ;
        Str *_t_Str_2427 = Str_lit("./src/core/array.til:41:19", 26ULL);
        (void)_t_Str_2427;
        panic(_t_Str_2427, _va_Array_74);
        Str_delete(_t_Str_2427, &(Bool){1});
    }
    ;
    U32 _t_U64_2429 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2429;
    void *_t_v_2430 = ptr_add(self->data, _t_U64_2429);
    (void)_t_v_2430;
    ;
    return _t_v_2430;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_2445 = U32_gte(i, &self->cap);
    (void)_t_Bool_2445;
    if (_t_Bool_2445) {
        Str *_t_Str_2431 = Str_lit("Str", 3ULL);
        (void)_t_Str_2431;
        Type *_t_Type_2432 = Type_Struct(_t_Str_2431);
        (void)_t_Type_2432;
        Str_delete(_t_Str_2431, &(Bool){1});
        U32 _t_U32_2433 = 5;
        (void)_t_U32_2433;
        Array *_va_Array_75 = Array_new(_t_Type_2432, &_t_U32_2433);
        (void)_va_Array_75;
        Type_delete(_t_Type_2432, &(Bool){1});
        ;
        U32 _t_U32_2434 = 0;
        (void)_t_U32_2434;
        Str *_t_Str_2435 = Str_lit("Array.set: index ", 17ULL);
        (void)_t_Str_2435;
        Array_set(_va_Array_75, &_t_U32_2434, _t_Str_2435);
        ;
        U32 _t_U32_2436 = 1;
        (void)_t_U32_2436;
        Str *_t_Str_2437 = U32_to_str(i);
        (void)_t_Str_2437;
        Array_set(_va_Array_75, &_t_U32_2436, _t_Str_2437);
        ;
        U32 _t_U32_2438 = 2;
        (void)_t_U32_2438;
        Str *_t_Str_2439 = Str_lit(" out of bounds (len ", 20ULL);
        (void)_t_Str_2439;
        Array_set(_va_Array_75, &_t_U32_2438, _t_Str_2439);
        ;
        U32 _t_U32_2440 = 3;
        (void)_t_U32_2440;
        Str *_t_Str_2441 = U32_to_str(&self->cap);
        (void)_t_Str_2441;
        Array_set(_va_Array_75, &_t_U32_2440, _t_Str_2441);
        ;
        U32 _t_U32_2442 = 4;
        (void)_t_U32_2442;
        Str *_t_Str_2443 = Str_lit(")", 1ULL);
        (void)_t_Str_2443;
        Array_set(_va_Array_75, &_t_U32_2442, _t_Str_2443);
        ;
        Str *_t_Str_2444 = Str_lit("./src/core/array.til:50:19", 26ULL);
        (void)_t_Str_2444;
        panic(_t_Str_2444, _va_Array_75);
        Str_delete(_t_Str_2444, &(Bool){1});
    }
    ;
    U32 _t_U64_2446 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2446;
    void *_t_v_2447 = ptr_add(self->data, _t_U64_2446);
    (void)_t_v_2447;
    Bool _t_Bool_2448 = 0;
    (void)_t_Bool_2448;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2447, &_t_Bool_2448);
    ;
    ;
    U32 _t_U64_2449 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2449;
    void *_t_v_2450 = ptr_add(self->data, _t_U64_2449);
    (void)_t_v_2450;
    memcpy(_t_v_2450, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_2451 = self->cap;
        (void)_re_U32_2451;
        U32 _rc_U32_2451 = 0;
        (void)_rc_U32_2451;
        Bool _t_Bool_2460 = U32_lte(&_rc_U32_2451, &_re_U32_2451);
        (void)_t_Bool_2460;
        if (_t_Bool_2460) {
            while (1) {
                Bool _wcond_Bool_2452 = U32_lt(&_rc_U32_2451, &_re_U32_2451);
                (void)_wcond_Bool_2452;
                if (_wcond_Bool_2452) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2451);
                (void)i;
                U32_inc(&_rc_U32_2451);
                U32 _t_U64_2453 = U32_mul(i, self->elem_size);
                (void)_t_U64_2453;
                ;
                void *_t_v_2454 = ptr_add(self->data, _t_U64_2453);
                (void)_t_v_2454;
                Bool _t_Bool_2455 = 0;
                (void)_t_Bool_2455;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2454, &_t_Bool_2455);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2456 = U32_gt(&_rc_U32_2451, &_re_U32_2451);
                (void)_wcond_Bool_2456;
                if (_wcond_Bool_2456) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2451);
                (void)i;
                U32_dec(&_rc_U32_2451);
                U32 _t_U64_2457 = U32_mul(i, self->elem_size);
                (void)_t_U64_2457;
                ;
                void *_t_v_2458 = ptr_add(self->data, _t_U64_2457);
                (void)_t_v_2458;
                Bool _t_Bool_2459 = 0;
                (void)_t_Bool_2459;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2458, &_t_Bool_2459);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_2461 = 0;
    (void)_t_Bool_2461;
    Str_delete(&self->elem_type, &_t_Bool_2461);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_2474 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_2474;
    void * new_data = malloc(_t_U64_2474);
    (void)new_data;
    ;
    {
        U32 _re_U32_2462 = self->cap;
        (void)_re_U32_2462;
        U32 _rc_U32_2462 = 0;
        (void)_rc_U32_2462;
        Bool _t_Bool_2473 = U32_lte(&_rc_U32_2462, &_re_U32_2462);
        (void)_t_Bool_2473;
        if (_t_Bool_2473) {
            while (1) {
                Bool _wcond_Bool_2463 = U32_lt(&_rc_U32_2462, &_re_U32_2462);
                (void)_wcond_Bool_2463;
                if (_wcond_Bool_2463) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2462);
                (void)i;
                U32_inc(&_rc_U32_2462);
                U32 _t_U64_2464 = U32_mul(i, self->elem_size);
                (void)_t_U64_2464;
                void *_t_v_2465 = ptr_add(self->data, _t_U64_2464);
                (void)_t_v_2465;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2465);
                (void)cloned;
                ;
                U32 _t_U64_2466 = U32_mul(i, self->elem_size);
                (void)_t_U64_2466;
                ;
                void *_t_v_2467 = ptr_add(new_data, _t_U64_2466);
                (void)_t_v_2467;
                memcpy(_t_v_2467, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2468 = U32_gt(&_rc_U32_2462, &_re_U32_2462);
                (void)_wcond_Bool_2468;
                if (_wcond_Bool_2468) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2462);
                (void)i;
                U32_dec(&_rc_U32_2462);
                U32 _t_U64_2469 = U32_mul(i, self->elem_size);
                (void)_t_U64_2469;
                void *_t_v_2470 = ptr_add(self->data, _t_U64_2469);
                (void)_t_v_2470;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2470);
                (void)cloned;
                ;
                U32 _t_U64_2471 = U32_mul(i, self->elem_size);
                (void)_t_U64_2471;
                ;
                void *_t_v_2472 = ptr_add(new_data, _t_U64_2471);
                (void)_t_v_2472;
                memcpy(_t_v_2472, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_2475 = malloc(sizeof(Array));
    _t_Array_2475->data = new_data;
    _t_Array_2475->cap = self->cap;
    _t_Array_2475->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_2475->elem_type = *_ca; free(_ca); }
    _t_Array_2475->elem_clone = (void *)self->elem_clone;
    _t_Array_2475->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_2475;
    return _t_Array_2475;
}

U32 Array_size(void) {
    I64 _t_I64_2476 = 48;
    (void)_t_I64_2476;
    return _t_I64_2476;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str *_t_Str_2715 = Str_lit("Str", 3ULL);
    (void)_t_Str_2715;
    Type *_t_Type_2716 = Type_Struct(_t_Str_2715);
    (void)_t_Type_2716;
    Str_delete(_t_Str_2715, &(Bool){1});
    U32 _t_U32_2717 = 3;
    (void)_t_U32_2717;
    Array *_va_Array_92 = Array_new(_t_Type_2716, &_t_U32_2717);
    (void)_va_Array_92;
    Type_delete(_t_Type_2716, &(Bool){1});
    ;
    U32 _t_U32_2718 = 0;
    (void)_t_U32_2718;
    Str *_t_Str_2719 = Str_clone(loc_str);
    (void)_t_Str_2719;
    Array_set(_va_Array_92, &_t_U32_2718, _t_Str_2719);
    ;
    U32 _t_U32_2720 = 1;
    (void)_t_U32_2720;
    Str *_t_Str_2721 = Str_lit(": panic: ", 9ULL);
    (void)_t_Str_2721;
    Array_set(_va_Array_92, &_t_U32_2720, _t_Str_2721);
    ;
    Array *_t_Array_2722 = Array_clone(parts);
    (void)_t_Array_2722;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2723 = 2;
    (void)_t_U32_2723;
    Str *_t_Str_2724 = format(_t_Array_2722);
    (void)_t_Str_2724;
    Array_set(_va_Array_92, &_t_U32_2723, _t_Str_2724);
    ;
    println(_va_Array_92);
    I64 _t_I64_2725 = 1;
    (void)_t_I64_2725;
    exit(_t_I64_2725);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2744 = not(DEREF(cond));
    (void)_t_Bool_2744;
    if (_t_Bool_2744) {
        Str *_t_Str_2739 = Str_lit("Str", 3ULL);
        (void)_t_Str_2739;
        Type *_t_Type_2740 = Type_Struct(_t_Str_2739);
        (void)_t_Type_2740;
        Str_delete(_t_Str_2739, &(Bool){1});
        U32 _t_U32_2741 = 1;
        (void)_t_U32_2741;
        Array *_va_Array_95 = Array_new(_t_Type_2740, &_t_U32_2741);
        (void)_va_Array_95;
        Type_delete(_t_Type_2740, &(Bool){1});
        ;
        U32 _t_U32_2742 = 0;
        (void)_t_U32_2742;
        Str *_t_Str_2743 = Str_lit("assert failed", 13ULL);
        (void)_t_Str_2743;
        Array_set(_va_Array_95, &_t_U32_2742, _t_Str_2743);
        ;
        panic(loc_str, _va_Array_95);
    }
    ;
    Bool _t_Bool_2745 = 1;
    (void)_t_Bool_2745;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2745; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2768 = I64_neq(a, b);
    (void)_t_Bool_2768;
    if (_t_Bool_2768) {
        Str *_t_Str_2755 = Str_lit("Str", 3ULL);
        (void)_t_Str_2755;
        Type *_t_Type_2756 = Type_Struct(_t_Str_2755);
        (void)_t_Type_2756;
        Str_delete(_t_Str_2755, &(Bool){1});
        U32 _t_U32_2757 = 5;
        (void)_t_U32_2757;
        Array *_va_Array_97 = Array_new(_t_Type_2756, &_t_U32_2757);
        (void)_va_Array_97;
        Type_delete(_t_Type_2756, &(Bool){1});
        ;
        U32 _t_U32_2758 = 0;
        (void)_t_U32_2758;
        Str *_t_Str_2759 = Str_lit("assert_eq failed: expected '", 28ULL);
        (void)_t_Str_2759;
        Array_set(_va_Array_97, &_t_U32_2758, _t_Str_2759);
        ;
        U32 _t_U32_2760 = 1;
        (void)_t_U32_2760;
        Str *_t_Str_2761 = I64_to_str(a);
        (void)_t_Str_2761;
        Array_set(_va_Array_97, &_t_U32_2760, _t_Str_2761);
        ;
        U32 _t_U32_2762 = 2;
        (void)_t_U32_2762;
        Str *_t_Str_2763 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2763;
        Array_set(_va_Array_97, &_t_U32_2762, _t_Str_2763);
        ;
        U32 _t_U32_2764 = 3;
        (void)_t_U32_2764;
        Str *_t_Str_2765 = I64_to_str(b);
        (void)_t_Str_2765;
        Array_set(_va_Array_97, &_t_U32_2764, _t_Str_2765);
        ;
        U32 _t_U32_2766 = 4;
        (void)_t_U32_2766;
        Str *_t_Str_2767 = Str_lit("'", 1ULL);
        (void)_t_Str_2767;
        Array_set(_va_Array_97, &_t_U32_2766, _t_Str_2767);
        ;
        panic(loc_str, _va_Array_97);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2782 = Str_eq(a, b);
    (void)_t_Bool_2782;
    Bool _t_Bool_2783 = not(_t_Bool_2782);
    (void)_t_Bool_2783;
    ;
    if (_t_Bool_2783) {
        Str *_t_Str_2769 = Str_lit("Str", 3ULL);
        (void)_t_Str_2769;
        Type *_t_Type_2770 = Type_Struct(_t_Str_2769);
        (void)_t_Type_2770;
        Str_delete(_t_Str_2769, &(Bool){1});
        U32 _t_U32_2771 = 5;
        (void)_t_U32_2771;
        Array *_va_Array_98 = Array_new(_t_Type_2770, &_t_U32_2771);
        (void)_va_Array_98;
        Type_delete(_t_Type_2770, &(Bool){1});
        ;
        U32 _t_U32_2772 = 0;
        (void)_t_U32_2772;
        Str *_t_Str_2773 = Str_lit("assert_eq_str failed: expected '", 32ULL);
        (void)_t_Str_2773;
        Array_set(_va_Array_98, &_t_U32_2772, _t_Str_2773);
        ;
        U32 _t_U32_2774 = 1;
        (void)_t_U32_2774;
        Str *_t_Str_2775 = Str_clone(a);
        (void)_t_Str_2775;
        Array_set(_va_Array_98, &_t_U32_2774, _t_Str_2775);
        ;
        U32 _t_U32_2776 = 2;
        (void)_t_U32_2776;
        Str *_t_Str_2777 = Str_lit("', found '", 10ULL);
        (void)_t_Str_2777;
        Array_set(_va_Array_98, &_t_U32_2776, _t_Str_2777);
        ;
        U32 _t_U32_2778 = 3;
        (void)_t_U32_2778;
        Str *_t_Str_2779 = Str_clone(b);
        (void)_t_Str_2779;
        Array_set(_va_Array_98, &_t_U32_2778, _t_Str_2779);
        ;
        U32 _t_U32_2780 = 4;
        (void)_t_U32_2780;
        Str *_t_Str_2781 = Str_lit("'", 1ULL);
        (void)_t_Str_2781;
        Array_set(_va_Array_98, &_t_U32_2780, _t_Str_2781);
        ;
        panic(loc_str, _va_Array_98);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2784 = parts;
        (void)_fc_Array_2784;
        U32 _fi_USize_2784 = 0;
        (void)_fi_USize_2784;
        while (1) {
            U32 _t_U32_2786; { U32 *_hp = (U32 *)Array_len(_fc_Array_2784); _t_U32_2786 = *_hp; free(_hp); }
            (void)_t_U32_2786;
            Bool _wcond_Bool_2785 = U32_lt(&_fi_USize_2784, &_t_U32_2786);
            (void)_wcond_Bool_2785;
            ;
            if (_wcond_Bool_2785) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2784, &_fi_USize_2784);
            (void)s;
            U32 _t_U32_2787 = 1;
            (void)_t_U32_2787;
            U32 _t_U32_2788 = U32_add(_fi_USize_2784, _t_U32_2787);
            (void)_t_U32_2788;
            ;
            _fi_USize_2784 = _t_U32_2788;
            ;
            print_single(s);
        }
        ;
    }
    Array_delete(parts, &(Bool){0});
    print_flush();
}

void test_simple_add(void) {
    I64 _t_I64_2980 = 1;
    (void)_t_I64_2980;
    I64 _t_I64_2981 = 2;
    (void)_t_I64_2981;
    I64 result = 3;
    (void)result;
    ;
    ;
    Str *_t_Str_2982 = Str_lit("src/test/constfold.til:15:15", 28ULL);
    (void)_t_Str_2982;
    I64 _t_I64_2983 = 3;
    (void)_t_I64_2983;
    assert_eq(_t_Str_2982, &result, &_t_I64_2983);
    ;
    Str_delete(_t_Str_2982, &(Bool){1});
    ;
}

void test_nested_arithmetic(void) {
    I64 _t_I64_2984 = 1;
    (void)_t_I64_2984;
    I64 _t_I64_2985 = 2;
    (void)_t_I64_2985;
    I64 _t_I64_2986 = 10;
    (void)_t_I64_2986;
    I64 _t_I64_2987 = 5;
    (void)_t_I64_2987;
    I64 _t_I64_2988 = 3;
    (void)_t_I64_2988;
    ;
    ;
    I64 _t_I64_2989 = 5;
    (void)_t_I64_2989;
    ;
    ;
    I64 result = 15;
    (void)result;
    ;
    ;
    Str *_t_Str_2990 = Str_lit("src/test/constfold.til:21:15", 28ULL);
    (void)_t_Str_2990;
    I64 _t_I64_2991 = 15;
    (void)_t_I64_2991;
    assert_eq(_t_Str_2990, &result, &_t_I64_2991);
    ;
    Str_delete(_t_Str_2990, &(Bool){1});
    ;
}

void test_deeply_nested(void) {
    I64 _t_I64_2992 = 2;
    (void)_t_I64_2992;
    I64 _t_I64_2993 = 3;
    (void)_t_I64_2993;
    I64 _t_I64_2994 = 4;
    (void)_t_I64_2994;
    I64 _t_I64_2995 = 5;
    (void)_t_I64_2995;
    I64 _t_I64_2996 = 6;
    (void)_t_I64_2996;
    ;
    ;
    I64 _t_I64_2997 = 20;
    (void)_t_I64_2997;
    ;
    ;
    I64 result = 26;
    (void)result;
    ;
    ;
    Str *_t_Str_2998 = Str_lit("src/test/constfold.til:27:15", 28ULL);
    (void)_t_Str_2998;
    I64 _t_I64_2999 = 26;
    (void)_t_I64_2999;
    assert_eq(_t_Str_2998, &result, &_t_I64_2999);
    ;
    Str_delete(_t_Str_2998, &(Bool){1});
    ;
}

void test_string_concat(void) {
    Str *_t_Str_3000 = Str_lit("hello", 5ULL);
    (void)_t_Str_3000;
    Str *_t_Str_3001 = Str_lit(" world", 6ULL);
    (void)_t_Str_3001;
    Str *result = Str_lit("hello world", 11ULL);
    (void)result;
    Str_delete(_t_Str_3000, &(Bool){1});
    Str_delete(_t_Str_3001, &(Bool){1});
    Str *_t_Str_3002 = Str_lit("src/test/constfold.til:33:19", 28ULL);
    (void)_t_Str_3002;
    Str *_t_Str_3003 = Str_lit("hello world", 11ULL);
    (void)_t_Str_3003;
    assert_eq_str(_t_Str_3002, result, _t_Str_3003);
    Str_delete(_t_Str_3002, &(Bool){1});
    Str_delete(_t_Str_3003, &(Bool){1});
    Str_delete(result, &(Bool){1});
}

void test_lolalalo(void) {
    Str *_t_Str_3026 = Str_lit("lo", 2ULL);
    (void)_t_Str_3026;
    Str *_t_Str_3027 = Str_lit("la", 2ULL);
    (void)_t_Str_3027;
    Str *lo_la = Str_lit("lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", 248ULL);
    (void)lo_la;
    Str_delete(_t_Str_3026, &(Bool){1});
    Str_delete(_t_Str_3027, &(Bool){1});
    Str *_t_Str_3028 = Str_lit("la", 2ULL);
    (void)_t_Str_3028;
    Str *_t_Str_3029 = Str_lit("lo", 2ULL);
    (void)_t_Str_3029;
    Str *la_lo = Str_lit("lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", 248ULL);
    (void)la_lo;
    Str_delete(_t_Str_3028, &(Bool){1});
    Str_delete(_t_Str_3029, &(Bool){1});
    Str *_t_Str_3030 = Str_lit("lolalolo", 8ULL);
    (void)_t_Str_3030;
    Str *_t_Str_3031 = Str_lit("src/test/constfold.til:62:12", 28ULL);
    (void)_t_Str_3031;
    Bool _t_Bool_3032 = 1;
    (void)_t_Bool_3032;
    Str_delete(_t_Str_3030, &(Bool){1});
    Bool _t_Bool_3033; { Bool *_hp = (Bool *)assert(_t_Str_3031, &_t_Bool_3032); _t_Bool_3033 = *_hp; free(_hp); }
    (void)_t_Bool_3033;
    ;
    ;
    Str_delete(_t_Str_3031, &(Bool){1});
    Str *_t_Str_3034 = Str_lit("lalalala", 8ULL);
    (void)_t_Str_3034;
    Str *_t_Str_3035 = Str_lit("src/test/constfold.til:63:12", 28ULL);
    (void)_t_Str_3035;
    Bool _t_Bool_3036 = 1;
    (void)_t_Bool_3036;
    Str_delete(_t_Str_3034, &(Bool){1});
    Bool _t_Bool_3037; { Bool *_hp = (Bool *)assert(_t_Str_3035, &_t_Bool_3036); _t_Bool_3037 = *_hp; free(_hp); }
    (void)_t_Bool_3037;
    ;
    ;
    Str_delete(_t_Str_3035, &(Bool){1});
    Str *_t_Str_3038 = Str_lit("lolei", 5ULL);
    (void)_t_Str_3038;
    Str *_t_Str_3039 = Str_lit("src/test/constfold.til:65:12", 28ULL);
    (void)_t_Str_3039;
    Bool _t_Bool_3040 = 1;
    (void)_t_Bool_3040;
    Str_delete(_t_Str_3038, &(Bool){1});
    Str_delete(lo_la, &(Bool){1});
    Bool _t_Bool_3041; { Bool *_hp = (Bool *)assert(_t_Str_3039, &_t_Bool_3040); _t_Bool_3041 = *_hp; free(_hp); }
    (void)_t_Bool_3041;
    ;
    ;
    Str_delete(_t_Str_3039, &(Bool){1});
    Str *_t_Str_3042 = Str_lit("lalei", 5ULL);
    (void)_t_Str_3042;
    Str *_t_Str_3043 = Str_lit("src/test/constfold.til:66:12", 28ULL);
    (void)_t_Str_3043;
    Bool _t_Bool_3044 = 1;
    (void)_t_Bool_3044;
    Str_delete(_t_Str_3042, &(Bool){1});
    Str_delete(la_lo, &(Bool){1});
    Bool _t_Bool_3045; { Bool *_hp = (Bool *)assert(_t_Str_3043, &_t_Bool_3044); _t_Bool_3045 = *_hp; free(_hp); }
    (void)_t_Bool_3045;
    ;
    ;
    Str_delete(_t_Str_3043, &(Bool){1});
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
    test_string_concat();
    fprintf(stderr, "  pass: %s\n", "test_string_concat");
    test_lolalalo();
    fprintf(stderr, "  pass: %s\n", "test_lolalalo");
    fprintf(stderr, "5/5 tests passed\n");
    return 0;
}
