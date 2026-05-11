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
    I64 _t_I64_55 = 4;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_55; return _r; }
}

Bool U32_lt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_56 = 0;
    I64 _t_I64_57 = 1;
    I64 _t_I64_58 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_58;
    I64 _t_I64_59 = I64_sub(_t_I64_56, _t_I64_57);
    (void)_t_I64_59;
    ;
    ;
    Bool _t_Bool_60 = I64_eq(_t_I64_58, _t_I64_59);
    (void)_t_Bool_60;
    ;
    ;
    return _t_Bool_60;
}

Bool U32_gt(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_61 = U32_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_61;
    I64 _t_I64_62 = 1;
    Bool _t_Bool_63 = I64_eq(_t_I64_61, _t_I64_62);
    (void)_t_Bool_63;
    ;
    ;
    return _t_Bool_63;
}

Bool U32_lte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_66 = U32_gt(a, b);
    (void)_t_Bool_66;
    Bool _t_Bool_67 = not(_t_Bool_66);
    (void)_t_Bool_67;
    ;
    return _t_Bool_67;
}

Bool U32_gte(U32 * a, U32 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_68 = U32_lt(a, b);
    (void)_t_Bool_68;
    Bool _t_Bool_69 = not(_t_Bool_68);
    (void)_t_Bool_69;
    ;
    return _t_Bool_69;
}

void I32_delete(I32 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I32_size(void) {
    I64 _t_I64_95 = 4;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_95; return _r; }
}

void U8_delete(U8 * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U8_size(void) {
    I64 _t_I64_123 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_123; return _r; }
}

Str * format(Array * parts) {
    (void)parts;
    U32 total = 0;
    {
        Array *_fc_Array_389 = parts;
        (void)_fc_Array_389;
        (void)_fc_Array_389;
        U32 _fi_USize_389 = 0;
        while (1) {
            U32 _t_U32_391; { U32 *_hp = (U32 *)Array_len(_fc_Array_389); _t_U32_391 = *_hp; free(_hp); }
            (void)_t_U32_391;
            Bool _wcond_Bool_390 = U32_lt(&_fi_USize_389, &_t_U32_391);
            (void)_wcond_Bool_390;
            ;
            if (_wcond_Bool_390) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_389, &_fi_USize_389);
            U32 _t_U32_392 = 1;
            U32 _t_U32_393 = U32_add(_fi_USize_389, _t_U32_392);
            (void)_t_U32_393;
            ;
            _fi_USize_389 = _t_U32_393;
            ;
            U32 _t_U32_394 = Str_len(s);
            (void)_t_U32_394;
            U32 _t_U32_395 = U32_add(total, _t_U32_394);
            (void)_t_U32_395;
            ;
            total = _t_U32_395;
            ;
        }
        ;
    }
    Str *out = Str_with_capacity(&total);
    ;
    {
        Array *_fc_Array_396 = parts;
        (void)_fc_Array_396;
        (void)_fc_Array_396;
        U32 _fi_USize_396 = 0;
        while (1) {
            U32 _t_U32_398; { U32 *_hp = (U32 *)Array_len(_fc_Array_396); _t_U32_398 = *_hp; free(_hp); }
            (void)_t_U32_398;
            Bool _wcond_Bool_397 = U32_lt(&_fi_USize_396, &_t_U32_398);
            (void)_wcond_Bool_397;
            ;
            if (_wcond_Bool_397) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_396, &_fi_USize_396);
            U32 _t_U32_399 = 1;
            U32 _t_U32_400 = U32_add(_fi_USize_396, _t_U32_399);
            (void)_t_U32_400;
            ;
            _fi_USize_396 = _t_U32_400;
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
    Bool _t_Bool_407 = U32_gte(i, &self->count);
    (void)_t_Bool_407;
    if (_t_Bool_407) {
        Str _t_Str_401 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_401;
        Type *_t_Type_402 = Type_Struct(&_t_Str_401);
        (void)_t_Type_402;
        Str_delete(&_t_Str_401, &(Bool){0});
        U32 _t_U32_403 = 1;
        Array *_va_Array_9 = Array_new(_t_Type_402, &_t_U32_403);
        (void)_va_Array_9;
        Type_delete(_t_Type_402, &(Bool){1});
        ;
        U32 _t_U32_404 = 0;
        Str _t_Str_405 = (Str){.c_str = (U8 *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_405;
        Array_set(_va_Array_9, &_t_U32_404, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_405; _oa; }));
        ;
        Str _t_Str_406 = (Str){.c_str = (U8 *)"./src/core/str.til:39:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_406;
        panic(&_t_Str_406, _va_Array_9);
        Str_delete(&_t_Str_406, &(Bool){0});
    }
    ;
    void *_t_v_408 = ptr_add(self->c_str, DEREF(i));
    (void)_t_v_408;
    (void)_t_v_408;
    return _t_v_408;
}

I64 Str_cmp(Str * a, Str * b) {
    (void)a;
    (void)b;
    U32 min_len = a->count;
    Bool _t_Bool_418 = U32_lt(&b->count, &a->count);
    (void)_t_Bool_418;
    if (_t_Bool_418) {
        min_len = b->count;
    }
    ;
    {
        U32 _re_U32_410 = U32_clone(&min_len);
        (void)_re_U32_410;
        U32 _rc_U32_410 = 0;
        Bool _t_Bool_417 = U32_lte(&_rc_U32_410, &_re_U32_410);
        (void)_t_Bool_417;
        if (_t_Bool_417) {
            while (1) {
                Bool _wcond_Bool_411 = U32_lt(&_rc_U32_410, &_re_U32_410);
                (void)_wcond_Bool_411;
                if (_wcond_Bool_411) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_410);
                U32_inc(&_rc_U32_410);
                U8 *ab = Str_get(a, &i);
                U8 *bb = Str_get(b, &i);
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                ;
                I64 _t_I64_412 = 0;
                Bool _t_Bool_413 = I64_neq(&c, &_t_I64_412);
                (void)_t_Bool_413;
                ;
                if (_t_Bool_413) {
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
                Bool _wcond_Bool_414 = U32_gt(&_rc_U32_410, &_re_U32_410);
                (void)_wcond_Bool_414;
                if (_wcond_Bool_414) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_410);
                U32_dec(&_rc_U32_410);
                U8 *ab = Str_get(a, &i);
                U8 *bb = Str_get(b, &i);
                I64 c = U8_cmp(DEREF(ab), DEREF(bb));
                ;
                I64 _t_I64_415 = 0;
                Bool _t_Bool_416 = I64_neq(&c, &_t_I64_415);
                (void)_t_Bool_416;
                ;
                if (_t_Bool_416) {
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
    I64 _t_I64_419 = U32_cmp(a->count, b->count);
    (void)_t_I64_419;
    return _t_I64_419;
}

Str * Str_with_capacity(U32 * n) {
    (void)n;
    U32 _t_U32_421 = 1;
    U32 _t_U64_422 = U32_add(DEREF(n), _t_U32_421);
    (void)_t_U64_422;
    ;
    void * buf = malloc(_t_U64_422);
    ;
    I32 _t_I32_423 = 0;
    U64 _t_U64_424 = 1;
    memset(buf, _t_I32_423, _t_U64_424);
    ;
    ;
    I64 _t_I64_425 = 0;
    Str *_t_Str_426 = malloc(sizeof(Str));
    _t_Str_426->c_str = buf;
    _t_Str_426->count = _t_I64_425;
    _t_Str_426->cap = DEREF(n);
    (void)_t_Str_426;
    ;
    return _t_Str_426;
}

void Str_push_str(Str * self, Str * s) {
    (void)self;
    (void)s;
    Bool _t_Bool_439 = U32_gte(&self->cap, &CAP_VIEW);
    (void)_t_Bool_439;
    if (_t_Bool_439) {
        Str _t_Str_427 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_427;
        Type *_t_Type_428 = Type_Struct(&_t_Str_427);
        (void)_t_Type_428;
        Str_delete(&_t_Str_427, &(Bool){0});
        U32 _t_U32_429 = 1;
        Array *_va_Array_10 = Array_new(_t_Type_428, &_t_U32_429);
        (void)_va_Array_10;
        Type_delete(_t_Type_428, &(Bool){1});
        ;
        U32 _t_U32_430 = 0;
        Str _t_Str_431 = (Str){.c_str = (U8 *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_431;
        Array_set(_va_Array_10, &_t_U32_430, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_431; _oa; }));
        ;
        Str _t_Str_432 = (Str){.c_str = (U8 *)"./src/core/str.til:82:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_432;
        panic(&_t_Str_432, _va_Array_10);
        Str_delete(&_t_Str_432, &(Bool){0});
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    Bool _t_Bool_440 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_440;
    if (_t_Bool_440) {
        Str _t_Str_433 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_433;
        Type *_t_Type_434 = Type_Struct(&_t_Str_433);
        (void)_t_Type_434;
        Str_delete(&_t_Str_433, &(Bool){0});
        U32 _t_U32_435 = 1;
        Array *_va_Array_11 = Array_new(_t_Type_434, &_t_U32_435);
        (void)_va_Array_11;
        Type_delete(_t_Type_434, &(Bool){1});
        ;
        U32 _t_U32_436 = 0;
        Str _t_Str_437 = (Str){.c_str = (U8 *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_437;
        Array_set(_va_Array_11, &_t_U32_436, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_437; _oa; }));
        ;
        Str _t_Str_438 = (Str){.c_str = (U8 *)"./src/core/str.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_438;
        panic(&_t_Str_438, _va_Array_11);
        Str_delete(&_t_Str_438, &(Bool){0});
    }
    ;
    void *_t_v_441 = ptr_add(self->c_str, self->count);
    (void)_t_v_441;
    (void)_t_v_441;
    memcpy(_t_v_441, s->c_str, s->count);
    U32 _t_U32_442 = U32_clone(&new_len);
    (void)_t_U32_442;
    self->count = _t_U32_442;
    ;
    void *_t_v_443 = ptr_add(self->c_str, new_len);
    (void)_t_v_443;
    (void)_t_v_443;
    I32 _t_I32_444 = 0;
    U64 _t_U64_445 = 1;
    memset(_t_v_443, _t_I32_444, _t_U64_445);
    ;
    ;
    ;
}

Str * Str_clone(Str * val) {
    (void)val;
    U32 _t_U32_446 = 1;
    U32 _t_U64_447 = U32_add(val->count, _t_U32_446);
    (void)_t_U64_447;
    ;
    void * new_data = malloc(_t_U64_447);
    ;
    memcpy(new_data, val->c_str, val->count);
    void *_t_v_448 = ptr_add(new_data, val->count);
    (void)_t_v_448;
    (void)_t_v_448;
    I32 _t_I32_449 = 0;
    U64 _t_U64_450 = 1;
    memset(_t_v_448, _t_I32_449, _t_U64_450);
    ;
    ;
    Str *_t_Str_451 = malloc(sizeof(Str));
    _t_Str_451->c_str = new_data;
    _t_Str_451->count = val->count;
    _t_Str_451->cap = val->count;
    (void)_t_Str_451;
    return _t_Str_451;
}

void Str_delete(Str * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    Bool _t_Bool_452 = U32_lt(&self->cap, &CAP_VIEW);
    (void)_t_Bool_452;
    if (_t_Bool_452) {
        free(self->c_str);
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    (void)self;
    U32 _t_U32_518 = 0;
    Bool _t_Bool_519 = U32_eq(self->count, _t_U32_518);
    (void)_t_Bool_519;
    ;
    return _t_Bool_519;
}

U32 Str_size(void) {
    I64 _t_I64_810 = 16;
    return _t_I64_810;
}

Bool Str_eq(Str * a, Str * b) {
    (void)a;
    (void)b;
    I64 _t_I64_811 = Str_cmp(a, b);
    (void)_t_I64_811;
    I64 _t_I64_812 = 0;
    Bool _t_Bool_813 = I64_eq(_t_I64_811, _t_I64_812);
    (void)_t_Bool_813;
    ;
    ;
    return _t_Bool_813;
}

U32 * Dynamic_size(void) {
    I64 _t_I64_859 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_859; return _r; }
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
    Bool _t_Bool_2425 = Str_is_empty(elem_type);
    (void)_t_Bool_2425;
    if (_t_Bool_2425) {
        Str _t_Str_2419 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2419;
        Type *_t_Type_2420 = Type_Struct(&_t_Str_2419);
        (void)_t_Type_2420;
        Str_delete(&_t_Str_2419, &(Bool){0});
        U32 _t_U32_2421 = 1;
        Array *_va_Array_73 = Array_new(_t_Type_2420, &_t_U32_2421);
        (void)_va_Array_73;
        Type_delete(_t_Type_2420, &(Bool){1});
        ;
        U32 _t_U32_2422 = 0;
        Str _t_Str_2423 = (Str){.c_str = (U8 *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2423;
        Array_set(_va_Array_73, &_t_U32_2422, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2423; _oa; }));
        ;
        Str _t_Str_2424 = (Str){.c_str = (U8 *)"./src/core/array.til:23:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2424;
        panic(&_t_Str_2424, _va_Array_73);
        Str_delete(&_t_Str_2424, &(Bool){0});
    }
    ;
    U32 elem_size = dyn_size_of(elem_type);
    void * _t_v_2426 = calloc(DEREF(cap), elem_size);
    (void)_t_v_2426;
    void * _t_v_2427 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2427;
    void * _t_v_2428 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2428;
    Array *_t_Array_2429 = malloc(sizeof(Array));
    _t_Array_2429->data = _t_v_2426;
    _t_Array_2429->cap = DEREF(cap);
    _t_Array_2429->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); _t_Array_2429->elem_type = *_ca; free(_ca); }
    _t_Array_2429->elem_clone = _t_v_2427;
    _t_Array_2429->elem_delete = _t_v_2428;
    (void)_t_Array_2429;
    ;
    return _t_Array_2429;
}

Array * Array_new(Type * T, U32 * cap) {
    (void)T;
    (void)cap;
    Str *elem_type = dyn_type_to_str(T);
    Array *_t_Array_2430 = Array_new_type_name(elem_type, cap);
    (void)_t_Array_2430;
    Str_delete(elem_type, &(Bool){1});
    return _t_Array_2430;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_2445 = U32_gte(i, &self->cap);
    (void)_t_Bool_2445;
    if (_t_Bool_2445) {
        Str _t_Str_2431 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2431;
        Type *_t_Type_2432 = Type_Struct(&_t_Str_2431);
        (void)_t_Type_2432;
        Str_delete(&_t_Str_2431, &(Bool){0});
        U32 _t_U32_2433 = 5;
        Array *_va_Array_74 = Array_new(_t_Type_2432, &_t_U32_2433);
        (void)_va_Array_74;
        Type_delete(_t_Type_2432, &(Bool){1});
        ;
        U32 _t_U32_2434 = 0;
        Str _t_Str_2435 = (Str){.c_str = (U8 *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2435;
        Array_set(_va_Array_74, &_t_U32_2434, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2435; _oa; }));
        ;
        U32 _t_U32_2436 = 1;
        Str *_t_Str_2437 = U32_to_str(i);
        (void)_t_Str_2437;
        Array_set(_va_Array_74, &_t_U32_2436, _t_Str_2437);
        ;
        U32 _t_U32_2438 = 2;
        Str _t_Str_2439 = (Str){.c_str = (U8 *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2439;
        Array_set(_va_Array_74, &_t_U32_2438, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2439; _oa; }));
        ;
        U32 _t_U32_2440 = 3;
        Str *_t_Str_2441 = U32_to_str(&self->cap);
        (void)_t_Str_2441;
        Array_set(_va_Array_74, &_t_U32_2440, _t_Str_2441);
        ;
        U32 _t_U32_2442 = 4;
        Str _t_Str_2443 = (Str){.c_str = (U8 *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2443;
        Array_set(_va_Array_74, &_t_U32_2442, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2443; _oa; }));
        ;
        Str _t_Str_2444 = (Str){.c_str = (U8 *)"./src/core/array.til:41:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2444;
        panic(&_t_Str_2444, _va_Array_74);
        Str_delete(&_t_Str_2444, &(Bool){0});
    }
    ;
    U32 _t_U64_2446 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2446;
    void *_t_v_2447 = ptr_add(self->data, _t_U64_2446);
    (void)_t_v_2447;
    (void)_t_v_2447;
    ;
    return _t_v_2447;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_2462 = U32_gte(i, &self->cap);
    (void)_t_Bool_2462;
    if (_t_Bool_2462) {
        Str _t_Str_2448 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2448;
        Type *_t_Type_2449 = Type_Struct(&_t_Str_2448);
        (void)_t_Type_2449;
        Str_delete(&_t_Str_2448, &(Bool){0});
        U32 _t_U32_2450 = 5;
        Array *_va_Array_75 = Array_new(_t_Type_2449, &_t_U32_2450);
        (void)_va_Array_75;
        Type_delete(_t_Type_2449, &(Bool){1});
        ;
        U32 _t_U32_2451 = 0;
        Str _t_Str_2452 = (Str){.c_str = (U8 *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2452;
        Array_set(_va_Array_75, &_t_U32_2451, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2452; _oa; }));
        ;
        U32 _t_U32_2453 = 1;
        Str *_t_Str_2454 = U32_to_str(i);
        (void)_t_Str_2454;
        Array_set(_va_Array_75, &_t_U32_2453, _t_Str_2454);
        ;
        U32 _t_U32_2455 = 2;
        Str _t_Str_2456 = (Str){.c_str = (U8 *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2456;
        Array_set(_va_Array_75, &_t_U32_2455, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2456; _oa; }));
        ;
        U32 _t_U32_2457 = 3;
        Str *_t_Str_2458 = U32_to_str(&self->cap);
        (void)_t_Str_2458;
        Array_set(_va_Array_75, &_t_U32_2457, _t_Str_2458);
        ;
        U32 _t_U32_2459 = 4;
        Str _t_Str_2460 = (Str){.c_str = (U8 *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2460;
        Array_set(_va_Array_75, &_t_U32_2459, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2460; _oa; }));
        ;
        Str _t_Str_2461 = (Str){.c_str = (U8 *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2461;
        panic(&_t_Str_2461, _va_Array_75);
        Str_delete(&_t_Str_2461, &(Bool){0});
    }
    ;
    U32 _t_U64_2463 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2463;
    void *_t_v_2464 = ptr_add(self->data, _t_U64_2463);
    (void)_t_v_2464;
    (void)_t_v_2464;
    Bool _t_Bool_2465 = 0;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2464, &_t_Bool_2465);
    ;
    ;
    U32 _t_U64_2466 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2466;
    void *_t_v_2467 = ptr_add(self->data, _t_U64_2466);
    (void)_t_v_2467;
    (void)_t_v_2467;
    memcpy(_t_v_2467, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_2468 = self->cap;
        (void)_re_U32_2468;
        U32 _rc_U32_2468 = 0;
        Bool _t_Bool_2477 = U32_lte(&_rc_U32_2468, &_re_U32_2468);
        (void)_t_Bool_2477;
        if (_t_Bool_2477) {
            while (1) {
                Bool _wcond_Bool_2469 = U32_lt(&_rc_U32_2468, &_re_U32_2468);
                (void)_wcond_Bool_2469;
                if (_wcond_Bool_2469) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2468);
                U32_inc(&_rc_U32_2468);
                U32 _t_U64_2470 = U32_mul(i, self->elem_size);
                (void)_t_U64_2470;
                ;
                void *_t_v_2471 = ptr_add(self->data, _t_U64_2470);
                (void)_t_v_2471;
                (void)_t_v_2471;
                Bool _t_Bool_2472 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2471, &_t_Bool_2472);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2473 = U32_gt(&_rc_U32_2468, &_re_U32_2468);
                (void)_wcond_Bool_2473;
                if (_wcond_Bool_2473) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2468);
                U32_dec(&_rc_U32_2468);
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
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_2478 = 0;
    Str_delete(&self->elem_type, &_t_Bool_2478);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_2491 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_2491;
    void * new_data = malloc(_t_U64_2491);
    ;
    {
        U32 _re_U32_2479 = self->cap;
        (void)_re_U32_2479;
        U32 _rc_U32_2479 = 0;
        Bool _t_Bool_2490 = U32_lte(&_rc_U32_2479, &_re_U32_2479);
        (void)_t_Bool_2490;
        if (_t_Bool_2490) {
            while (1) {
                Bool _wcond_Bool_2480 = U32_lt(&_rc_U32_2479, &_re_U32_2479);
                (void)_wcond_Bool_2480;
                if (_wcond_Bool_2480) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2479);
                U32_inc(&_rc_U32_2479);
                U32 _t_U64_2481 = U32_mul(i, self->elem_size);
                (void)_t_U64_2481;
                void *_t_v_2482 = ptr_add(self->data, _t_U64_2481);
                (void)_t_v_2482;
                (void)_t_v_2482;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2482);
                ;
                U32 _t_U64_2483 = U32_mul(i, self->elem_size);
                (void)_t_U64_2483;
                ;
                void *_t_v_2484 = ptr_add(new_data, _t_U64_2483);
                (void)_t_v_2484;
                (void)_t_v_2484;
                memcpy(_t_v_2484, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2485 = U32_gt(&_rc_U32_2479, &_re_U32_2479);
                (void)_wcond_Bool_2485;
                if (_wcond_Bool_2485) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2479);
                U32_dec(&_rc_U32_2479);
                U32 _t_U64_2486 = U32_mul(i, self->elem_size);
                (void)_t_U64_2486;
                void *_t_v_2487 = ptr_add(self->data, _t_U64_2486);
                (void)_t_v_2487;
                (void)_t_v_2487;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2487);
                ;
                U32 _t_U64_2488 = U32_mul(i, self->elem_size);
                (void)_t_U64_2488;
                ;
                void *_t_v_2489 = ptr_add(new_data, _t_U64_2488);
                (void)_t_v_2489;
                (void)_t_v_2489;
                memcpy(_t_v_2489, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_2492 = malloc(sizeof(Array));
    _t_Array_2492->data = new_data;
    _t_Array_2492->cap = self->cap;
    _t_Array_2492->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_2492->elem_type = *_ca; free(_ca); }
    _t_Array_2492->elem_clone = (void *)self->elem_clone;
    _t_Array_2492->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_2492;
    return _t_Array_2492;
}

U32 Array_size(void) {
    I64 _t_I64_2493 = 48;
    return _t_I64_2493;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str _t_Str_2732 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_2732;
    Type *_t_Type_2733 = Type_Struct(&_t_Str_2732);
    (void)_t_Type_2733;
    Str_delete(&_t_Str_2732, &(Bool){0});
    U32 _t_U32_2734 = 3;
    Array *_va_Array_92 = Array_new(_t_Type_2733, &_t_U32_2734);
    (void)_va_Array_92;
    Type_delete(_t_Type_2733, &(Bool){1});
    ;
    U32 _t_U32_2735 = 0;
    Str *_t_Str_2736 = Str_clone(loc_str);
    (void)_t_Str_2736;
    Array_set(_va_Array_92, &_t_U32_2735, _t_Str_2736);
    ;
    U32 _t_U32_2737 = 1;
    Str _t_Str_2738 = (Str){.c_str = (U8 *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_2738;
    Array_set(_va_Array_92, &_t_U32_2737, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2738; _oa; }));
    ;
    Array *_t_Array_2739 = Array_clone(parts);
    (void)_t_Array_2739;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2740 = 2;
    Str *_t_Str_2741 = format(_t_Array_2739);
    (void)_t_Str_2741;
    Array_set(_va_Array_92, &_t_U32_2740, _t_Str_2741);
    ;
    println(_va_Array_92);
    I64 _t_I64_2742 = 1;
    exit(_t_I64_2742);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2761 = not(DEREF(cond));
    (void)_t_Bool_2761;
    if (_t_Bool_2761) {
        Str _t_Str_2756 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2756;
        Type *_t_Type_2757 = Type_Struct(&_t_Str_2756);
        (void)_t_Type_2757;
        Str_delete(&_t_Str_2756, &(Bool){0});
        U32 _t_U32_2758 = 1;
        Array *_va_Array_95 = Array_new(_t_Type_2757, &_t_U32_2758);
        (void)_va_Array_95;
        Type_delete(_t_Type_2757, &(Bool){1});
        ;
        U32 _t_U32_2759 = 0;
        Str _t_Str_2760 = (Str){.c_str = (U8 *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2760;
        Array_set(_va_Array_95, &_t_U32_2759, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2760; _oa; }));
        ;
        panic(loc_str, _va_Array_95);
    }
    ;
    Bool _t_Bool_2762 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2762; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2785 = I64_neq(a, b);
    (void)_t_Bool_2785;
    if (_t_Bool_2785) {
        Str _t_Str_2772 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2772;
        Type *_t_Type_2773 = Type_Struct(&_t_Str_2772);
        (void)_t_Type_2773;
        Str_delete(&_t_Str_2772, &(Bool){0});
        U32 _t_U32_2774 = 5;
        Array *_va_Array_97 = Array_new(_t_Type_2773, &_t_U32_2774);
        (void)_va_Array_97;
        Type_delete(_t_Type_2773, &(Bool){1});
        ;
        U32 _t_U32_2775 = 0;
        Str _t_Str_2776 = (Str){.c_str = (U8 *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2776;
        Array_set(_va_Array_97, &_t_U32_2775, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2776; _oa; }));
        ;
        U32 _t_U32_2777 = 1;
        Str *_t_Str_2778 = I64_to_str(a);
        (void)_t_Str_2778;
        Array_set(_va_Array_97, &_t_U32_2777, _t_Str_2778);
        ;
        U32 _t_U32_2779 = 2;
        Str _t_Str_2780 = (Str){.c_str = (U8 *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2780;
        Array_set(_va_Array_97, &_t_U32_2779, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2780; _oa; }));
        ;
        U32 _t_U32_2781 = 3;
        Str *_t_Str_2782 = I64_to_str(b);
        (void)_t_Str_2782;
        Array_set(_va_Array_97, &_t_U32_2781, _t_Str_2782);
        ;
        U32 _t_U32_2783 = 4;
        Str _t_Str_2784 = (Str){.c_str = (U8 *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2784;
        Array_set(_va_Array_97, &_t_U32_2783, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2784; _oa; }));
        ;
        panic(loc_str, _va_Array_97);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2799 = Str_eq(a, b);
    (void)_t_Bool_2799;
    Bool _t_Bool_2800 = not(_t_Bool_2799);
    (void)_t_Bool_2800;
    ;
    if (_t_Bool_2800) {
        Str _t_Str_2786 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2786;
        Type *_t_Type_2787 = Type_Struct(&_t_Str_2786);
        (void)_t_Type_2787;
        Str_delete(&_t_Str_2786, &(Bool){0});
        U32 _t_U32_2788 = 5;
        Array *_va_Array_98 = Array_new(_t_Type_2787, &_t_U32_2788);
        (void)_va_Array_98;
        Type_delete(_t_Type_2787, &(Bool){1});
        ;
        U32 _t_U32_2789 = 0;
        Str _t_Str_2790 = (Str){.c_str = (U8 *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2790;
        Array_set(_va_Array_98, &_t_U32_2789, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2790; _oa; }));
        ;
        U32 _t_U32_2791 = 1;
        Str *_t_Str_2792 = Str_clone(a);
        (void)_t_Str_2792;
        Array_set(_va_Array_98, &_t_U32_2791, _t_Str_2792);
        ;
        U32 _t_U32_2793 = 2;
        Str _t_Str_2794 = (Str){.c_str = (U8 *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2794;
        Array_set(_va_Array_98, &_t_U32_2793, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2794; _oa; }));
        ;
        U32 _t_U32_2795 = 3;
        Str *_t_Str_2796 = Str_clone(b);
        (void)_t_Str_2796;
        Array_set(_va_Array_98, &_t_U32_2795, _t_Str_2796);
        ;
        U32 _t_U32_2797 = 4;
        Str _t_Str_2798 = (Str){.c_str = (U8 *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)_t_Str_2798;
        Array_set(_va_Array_98, &_t_U32_2797, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2798; _oa; }));
        ;
        panic(loc_str, _va_Array_98);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2801 = parts;
        (void)_fc_Array_2801;
        (void)_fc_Array_2801;
        U32 _fi_USize_2801 = 0;
        while (1) {
            U32 _t_U32_2803; { U32 *_hp = (U32 *)Array_len(_fc_Array_2801); _t_U32_2803 = *_hp; free(_hp); }
            (void)_t_U32_2803;
            Bool _wcond_Bool_2802 = U32_lt(&_fi_USize_2801, &_t_U32_2803);
            (void)_wcond_Bool_2802;
            ;
            if (_wcond_Bool_2802) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2801, &_fi_USize_2801);
            U32 _t_U32_2804 = 1;
            U32 _t_U32_2805 = U32_add(_fi_USize_2801, _t_U32_2804);
            (void)_t_U32_2805;
            ;
            _fi_USize_2801 = _t_U32_2805;
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
    Str _t_Str_2999 = (Str){.c_str = (U8 *)"src/test/constfold.til:15:15", .count = 28ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_2999;
    I64 _t_I64_3000 = 3;
    assert_eq(&_t_Str_2999, &result, &_t_I64_3000);
    ;
    Str_delete(&_t_Str_2999, &(Bool){0});
    ;
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str _t_Str_3007 = (Str){.c_str = (U8 *)"src/test/constfold.til:21:15", .count = 28ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3007;
    I64 _t_I64_3008 = 15;
    assert_eq(&_t_Str_3007, &result, &_t_I64_3008);
    ;
    Str_delete(&_t_Str_3007, &(Bool){0});
    ;
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str _t_Str_3015 = (Str){.c_str = (U8 *)"src/test/constfold.til:27:15", .count = 28ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3015;
    I64 _t_I64_3016 = 26;
    assert_eq(&_t_Str_3015, &result, &_t_I64_3016);
    ;
    Str_delete(&_t_Str_3015, &(Bool){0});
    ;
}

void test_string_concat(void) {
    Str _t_Str_3017 = (Str){.c_str = (U8 *)"hello", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3017;
    Str _t_Str_3018 = (Str){.c_str = (U8 *)" world", .count = 6ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3018;
    Str *result = Str_lit("hello world", 11ULL);
    Str_delete(&_t_Str_3017, &(Bool){0});
    Str_delete(&_t_Str_3018, &(Bool){0});
    Str _t_Str_3019 = (Str){.c_str = (U8 *)"src/test/constfold.til:33:19", .count = 28ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3019;
    Str _t_Str_3020 = (Str){.c_str = (U8 *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3020;
    assert_eq_str(&_t_Str_3019, result, &_t_Str_3020);
    Str_delete(&_t_Str_3019, &(Bool){0});
    Str_delete(&_t_Str_3020, &(Bool){0});
    Str_delete(result, &(Bool){1});
}

void test_lolalalo(void) {
    Str _t_Str_3043 = (Str){.c_str = (U8 *)"lo", .count = 2ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3043;
    Str _t_Str_3044 = (Str){.c_str = (U8 *)"la", .count = 2ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3044;
    Str *lo_la = Str_lit("lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", 224ULL);
    Str_delete(&_t_Str_3043, &(Bool){0});
    Str_delete(&_t_Str_3044, &(Bool){0});
    Str _t_Str_3045 = (Str){.c_str = (U8 *)"la", .count = 2ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3045;
    Str _t_Str_3046 = (Str){.c_str = (U8 *)"lo", .count = 2ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3046;
    Str *la_lo = Str_lit("lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", 224ULL);
    Str_delete(&_t_Str_3045, &(Bool){0});
    Str_delete(&_t_Str_3046, &(Bool){0});
    Str _t_Str_3047 = (Str){.c_str = (U8 *)"lolalolo", .count = 8ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3047;
    Str _t_Str_3048 = (Str){.c_str = (U8 *)"src/test/constfold.til:62:12", .count = 28ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3048;
    Bool _t_Bool_3049 = 1;
    Str_delete(&_t_Str_3047, &(Bool){0});
    assert(&_t_Str_3048, &_t_Bool_3049);
    ;
    Str_delete(&_t_Str_3048, &(Bool){0});
    Str _t_Str_3051 = (Str){.c_str = (U8 *)"lalalala", .count = 8ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3051;
    Str _t_Str_3052 = (Str){.c_str = (U8 *)"src/test/constfold.til:63:12", .count = 28ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3052;
    Bool _t_Bool_3053 = 1;
    Str_delete(&_t_Str_3051, &(Bool){0});
    assert(&_t_Str_3052, &_t_Bool_3053);
    ;
    Str_delete(&_t_Str_3052, &(Bool){0});
    Str _t_Str_3055 = (Str){.c_str = (U8 *)"lolei", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3055;
    Str _t_Str_3056 = (Str){.c_str = (U8 *)"src/test/constfold.til:65:12", .count = 28ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3056;
    Bool _t_Bool_3057 = 1;
    Str_delete(&_t_Str_3055, &(Bool){0});
    Str_delete(lo_la, &(Bool){1});
    assert(&_t_Str_3056, &_t_Bool_3057);
    ;
    Str_delete(&_t_Str_3056, &(Bool){0});
    Str _t_Str_3059 = (Str){.c_str = (U8 *)"lalei", .count = 5ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3059;
    Str _t_Str_3060 = (Str){.c_str = (U8 *)"src/test/constfold.til:66:12", .count = 28ULL, .cap = TIL_CAP_LIT};
    (void)_t_Str_3060;
    Bool _t_Bool_3061 = 1;
    Str_delete(&_t_Str_3059, &(Bool){0});
    Str_delete(la_lo, &(Bool){1});
    assert(&_t_Str_3060, &_t_Bool_3061);
    ;
    Str_delete(&_t_Str_3060, &(Bool){0});
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
    I64 _t_I64_853 = 0;
    I64 _t_I64_854 = 1;
    I64 _t_I64_855 = I64_sub(_t_I64_853, _t_I64_854);
    (void)_t_I64_855;
    CAP_LIT = I64_to_usize(_t_I64_855);
    I64 _t_I64_856 = 0;
    I64 _t_I64_857 = 2;
    I64 _t_I64_858 = I64_sub(_t_I64_856, _t_I64_857);
    (void)_t_I64_858;
    CAP_VIEW = I64_to_usize(_t_I64_858);
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
