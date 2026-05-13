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
        Array_set(_va_Array_9, &_t_U32_404, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_405; _oa; }));
        ;
        Str _t_Str_406 = (Str){.c_str = (U8 *)"./src/core/str.til:39:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&_t_Str_406, _va_Array_9);
        Str_delete(&_t_Str_406, &(Bool){0});
        free(_va_Array_9);
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
        Array_set(_va_Array_10, &_t_U32_430, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_431; _oa; }));
        ;
        Str _t_Str_432 = (Str){.c_str = (U8 *)"./src/core/str.til:82:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&_t_Str_432, _va_Array_10);
        Str_delete(&_t_Str_432, &(Bool){0});
        free(_va_Array_10);
    }
    ;
    U32 new_len = U32_add(self->count, s->count);
    Bool _t_Bool_440 = U32_gt(&new_len, &self->cap);
    (void)_t_Bool_440;
    if (_t_Bool_440) {
        Str _t_Str_433 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
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
        Array_set(_va_Array_11, &_t_U32_436, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_437; _oa; }));
        ;
        Str _t_Str_438 = (Str){.c_str = (U8 *)"./src/core/str.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&_t_Str_438, _va_Array_11);
        Str_delete(&_t_Str_438, &(Bool){0});
        free(_va_Array_11);
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
    I64 _t_I64_976 = 0;
    I64 _t_I64_977 = 1;
    I64 _t_I64_978 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_978;
    I64 _t_I64_979 = I64_sub(_t_I64_976, _t_I64_977);
    (void)_t_I64_979;
    ;
    ;
    Bool _t_Bool_980 = I64_eq(_t_I64_978, _t_I64_979);
    (void)_t_Bool_980;
    ;
    ;
    return _t_Bool_980;
}

Bool I64_gt(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    I64 _t_I64_981 = I64_cmp(DEREF(a), DEREF(b));
    (void)_t_I64_981;
    I64 _t_I64_982 = 1;
    Bool _t_Bool_983 = I64_eq(_t_I64_981, _t_I64_982);
    (void)_t_Bool_983;
    ;
    ;
    return _t_Bool_983;
}

Bool I64_neq(I64 * a, I64 * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_984 = I64_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_984;
    Bool _t_Bool_985 = not(_t_Bool_984);
    (void)_t_Bool_985;
    ;
    return _t_Bool_985;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    (void)a;
    (void)b;
    Bool _t_Bool_998 = Bool_eq(DEREF(a), DEREF(b));
    (void)_t_Bool_998;
    if (_t_Bool_998) {
        I64 _t_I64_994 = 0;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_994; return _r; }
    }
    ;
    if (DEREF(b)) {
        I64 _t_I64_995 = 0;
        I64 _t_I64_996 = 1;
        I64 _t_I64_997 = I64_sub(_t_I64_995, _t_I64_996);
        (void)_t_I64_997;
        ;
        ;
        { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_997; return _r; }
    }
    I64 _t_I64_999 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = _t_I64_999; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 _t_I64_1000 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = _t_I64_1000; return _r; }
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
    Bool _t_Bool_1209 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)_t_Bool_1209;
    if (_t_Bool_1209) {
        Str *_t_Str_1203 = get_payload(self);
        (void)_t_Str_1203;
        (void)_t_Str_1203;
        Bool _t_Bool_1204 = 0;
        Str_delete(_t_Str_1203, &_t_Bool_1204);
        ;
    }
    ;
    Bool _t_Bool_1210 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1210;
    if (_t_Bool_1210) {
        Str *_t_Str_1205 = get_payload(self);
        (void)_t_Str_1205;
        (void)_t_Str_1205;
        Bool _t_Bool_1206 = 0;
        Str_delete(_t_Str_1205, &_t_Bool_1206);
        ;
    }
    ;
    Bool _t_Bool_1211 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)_t_Bool_1211;
    if (_t_Bool_1211) {
        Str *_t_Str_1207 = get_payload(self);
        (void)_t_Str_1207;
        (void)_t_Str_1207;
        Bool _t_Bool_1208 = 0;
        Str_delete(_t_Str_1207, &_t_Bool_1208);
        ;
    }
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    (void)self;
    Bool _t_Bool_1278 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)_t_Bool_1278;
    if (_t_Bool_1278) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown; return _r; }
    }
    ;
    Bool _t_Bool_1279 = is(self, &(Type){.tag = Type_TAG_None});
    (void)_t_Bool_1279;
    if (_t_Bool_1279) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None; return _r; }
    }
    ;
    Bool _t_Bool_1280 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)_t_Bool_1280;
    if (_t_Bool_1280) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64; return _r; }
    }
    ;
    Bool _t_Bool_1281 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)_t_Bool_1281;
    if (_t_Bool_1281) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8; return _r; }
    }
    ;
    Bool _t_Bool_1282 = is(self, &(Type){.tag = Type_TAG_I16});
    (void)_t_Bool_1282;
    if (_t_Bool_1282) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I16; return _r; }
    }
    ;
    Bool _t_Bool_1283 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)_t_Bool_1283;
    if (_t_Bool_1283) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32; return _r; }
    }
    ;
    Bool _t_Bool_1284 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)_t_Bool_1284;
    if (_t_Bool_1284) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32; return _r; }
    }
    ;
    Bool _t_Bool_1285 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)_t_Bool_1285;
    if (_t_Bool_1285) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64; return _r; }
    }
    ;
    Bool _t_Bool_1286 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)_t_Bool_1286;
    if (_t_Bool_1286) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32; return _r; }
    }
    ;
    Bool _t_Bool_1287 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)_t_Bool_1287;
    if (_t_Bool_1287) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool; return _r; }
    }
    ;
    Bool _t_Bool_1288 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)_t_Bool_1288;
    if (_t_Bool_1288) {
        Str *_clone_payload_Struct_10 = get_payload(self);
        (void)_clone_payload_Struct_10;
        (void)_clone_payload_Struct_10;
        Type *_t_Type_1276 = Type_Struct(_clone_payload_Struct_10);
        (void)_t_Type_1276;
        ;
        return _t_Type_1276;
    }
    ;
    Bool _t_Bool_1289 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)_t_Bool_1289;
    if (_t_Bool_1289) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef; return _r; }
    }
    ;
    Bool _t_Bool_1290 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)_t_Bool_1290;
    if (_t_Bool_1290) {
        Str *_clone_payload_Enum_12 = get_payload(self);
        (void)_clone_payload_Enum_12;
        (void)_clone_payload_Enum_12;
        Type *_t_Type_1277 = Type_Enum(_clone_payload_Enum_12);
        (void)_t_Type_1277;
        ;
        return _t_Type_1277;
    }
    ;
    Bool _t_Bool_1291 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)_t_Bool_1291;
    if (_t_Bool_1291) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef; return _r; }
    }
    ;
    Bool _t_Bool_1292 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)_t_Bool_1292;
    if (_t_Bool_1292) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef; return _r; }
    }
    ;
    Bool _t_Bool_1293 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)_t_Bool_1293;
    if (_t_Bool_1293) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr; return _r; }
    }
    ;
    Bool _t_Bool_1294 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)_t_Bool_1294;
    if (_t_Bool_1294) {
        ;
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic; return _r; }
    }
    ;
    Str *_clone_payload_Custom_17 = get_payload(self);
    (void)_clone_payload_Custom_17;
    (void)_clone_payload_Custom_17;
    Type *_t_Type_1295 = Type_Custom(_clone_payload_Custom_17);
    (void)_t_Type_1295;
    return _t_Type_1295;
}

U32 Type_size(void) {
    I64 _t_I64_1296 = 24;
    return _t_I64_1296;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    (void)elem_type;
    (void)cap;
    Bool _t_Bool_2443 = Str_is_empty(elem_type);
    (void)_t_Bool_2443;
    if (_t_Bool_2443) {
        Str _t_Str_2437 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *_t_Type_2438 = Type_Struct(&_t_Str_2437);
        (void)_t_Type_2438;
        Str_delete(&_t_Str_2437, &(Bool){0});
        U32 _t_U32_2439 = 1;
        Array *_va_Array_73 = Array_new(_t_Type_2438, &_t_U32_2439);
        (void)_va_Array_73;
        Type_delete(_t_Type_2438, &(Bool){1});
        ;
        U32 _t_U32_2440 = 0;
        Str _t_Str_2441 = (Str){.c_str = (U8 *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_73, &_t_U32_2440, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2441; _oa; }));
        ;
        Str _t_Str_2442 = (Str){.c_str = (U8 *)"./src/core/array.til:23:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&_t_Str_2442, _va_Array_73);
        Str_delete(&_t_Str_2442, &(Bool){0});
        free(_va_Array_73);
    }
    ;
    U32 elem_size = dyn_size_of(elem_type);
    void * _t_v_2444 = calloc(DEREF(cap), elem_size);
    (void)_t_v_2444;
    void * _t_v_2445 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2445;
    void * _t_v_2446 = dyn_fn(elem_type, &(Str){.c_str=(U8*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)_t_v_2446;
    Array *_t_Array_2447 = malloc(sizeof(Array));
    _t_Array_2447->data = _t_v_2444;
    _t_Array_2447->cap = DEREF(cap);
    _t_Array_2447->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); _t_Array_2447->elem_type = *_ca; free(_ca); }
    _t_Array_2447->elem_clone = _t_v_2445;
    _t_Array_2447->elem_delete = _t_v_2446;
    (void)_t_Array_2447;
    ;
    return _t_Array_2447;
}

Array * Array_new(Type * T, U32 * cap) {
    (void)T;
    (void)cap;
    Str *elem_type = dyn_type_to_str(T);
    Array *_t_Array_2448 = Array_new_type_name(elem_type, cap);
    (void)_t_Array_2448;
    Str_delete(elem_type, &(Bool){1});
    return _t_Array_2448;
}

U32 * Array_len(Array * self) {
    (void)self;
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    (void)self;
    (void)i;
    Bool _t_Bool_2463 = U32_gte(i, &self->cap);
    (void)_t_Bool_2463;
    if (_t_Bool_2463) {
        Str _t_Str_2449 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *_t_Type_2450 = Type_Struct(&_t_Str_2449);
        (void)_t_Type_2450;
        Str_delete(&_t_Str_2449, &(Bool){0});
        U32 _t_U32_2451 = 5;
        Array *_va_Array_74 = Array_new(_t_Type_2450, &_t_U32_2451);
        (void)_va_Array_74;
        Type_delete(_t_Type_2450, &(Bool){1});
        ;
        U32 _t_U32_2452 = 0;
        Str _t_Str_2453 = (Str){.c_str = (U8 *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_74, &_t_U32_2452, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2453; _oa; }));
        ;
        U32 _t_U32_2454 = 1;
        Str *_t_Str_2455 = U32_to_str(i);
        (void)_t_Str_2455;
        Array_set(_va_Array_74, &_t_U32_2454, _t_Str_2455);
        ;
        U32 _t_U32_2456 = 2;
        Str _t_Str_2457 = (Str){.c_str = (U8 *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_74, &_t_U32_2456, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2457; _oa; }));
        ;
        U32 _t_U32_2458 = 3;
        Str *_t_Str_2459 = U32_to_str(&self->cap);
        (void)_t_Str_2459;
        Array_set(_va_Array_74, &_t_U32_2458, _t_Str_2459);
        ;
        U32 _t_U32_2460 = 4;
        Str _t_Str_2461 = (Str){.c_str = (U8 *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_74, &_t_U32_2460, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2461; _oa; }));
        ;
        Str _t_Str_2462 = (Str){.c_str = (U8 *)"./src/core/array.til:41:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&_t_Str_2462, _va_Array_74);
        Str_delete(&_t_Str_2462, &(Bool){0});
        free(_va_Array_74);
    }
    ;
    U32 _t_U64_2464 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2464;
    void *_t_v_2465 = ptr_add(self->data, _t_U64_2464);
    (void)_t_v_2465;
    (void)_t_v_2465;
    ;
    return _t_v_2465;
}

void Array_set(Array * self, U32 * i, void * val) {
    (void)self;
    (void)i;
    (void)val;
    Bool _t_Bool_2480 = U32_gte(i, &self->cap);
    (void)_t_Bool_2480;
    if (_t_Bool_2480) {
        Str _t_Str_2466 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *_t_Type_2467 = Type_Struct(&_t_Str_2466);
        (void)_t_Type_2467;
        Str_delete(&_t_Str_2466, &(Bool){0});
        U32 _t_U32_2468 = 5;
        Array *_va_Array_75 = Array_new(_t_Type_2467, &_t_U32_2468);
        (void)_va_Array_75;
        Type_delete(_t_Type_2467, &(Bool){1});
        ;
        U32 _t_U32_2469 = 0;
        Str _t_Str_2470 = (Str){.c_str = (U8 *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_75, &_t_U32_2469, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2470; _oa; }));
        ;
        U32 _t_U32_2471 = 1;
        Str *_t_Str_2472 = U32_to_str(i);
        (void)_t_Str_2472;
        Array_set(_va_Array_75, &_t_U32_2471, _t_Str_2472);
        ;
        U32 _t_U32_2473 = 2;
        Str _t_Str_2474 = (Str){.c_str = (U8 *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_75, &_t_U32_2473, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2474; _oa; }));
        ;
        U32 _t_U32_2475 = 3;
        Str *_t_Str_2476 = U32_to_str(&self->cap);
        (void)_t_Str_2476;
        Array_set(_va_Array_75, &_t_U32_2475, _t_Str_2476);
        ;
        U32 _t_U32_2477 = 4;
        Str _t_Str_2478 = (Str){.c_str = (U8 *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_75, &_t_U32_2477, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2478; _oa; }));
        ;
        Str _t_Str_2479 = (Str){.c_str = (U8 *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&_t_Str_2479, _va_Array_75);
        Str_delete(&_t_Str_2479, &(Bool){0});
        free(_va_Array_75);
    }
    ;
    U32 _t_U64_2481 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2481;
    void *_t_v_2482 = ptr_add(self->data, _t_U64_2481);
    (void)_t_v_2482;
    (void)_t_v_2482;
    Bool _t_Bool_2483 = 0;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2482, &_t_Bool_2483);
    ;
    ;
    U32 _t_U64_2484 = U32_mul(DEREF(i), self->elem_size);
    (void)_t_U64_2484;
    void *_t_v_2485 = ptr_add(self->data, _t_U64_2484);
    (void)_t_v_2485;
    (void)_t_v_2485;
    memcpy(_t_v_2485, val, self->elem_size);
    ;
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    (void)self;
    (void)call_free;
    {
        U32 _re_U32_2486 = self->cap;
        (void)_re_U32_2486;
        U32 _rc_U32_2486 = 0;
        Bool _t_Bool_2495 = U32_lte(&_rc_U32_2486, &_re_U32_2486);
        (void)_t_Bool_2495;
        if (_t_Bool_2495) {
            while (1) {
                Bool _wcond_Bool_2487 = U32_lt(&_rc_U32_2486, &_re_U32_2486);
                (void)_wcond_Bool_2487;
                if (_wcond_Bool_2487) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2486);
                U32_inc(&_rc_U32_2486);
                U32 _t_U64_2488 = U32_mul(i, self->elem_size);
                (void)_t_U64_2488;
                ;
                void *_t_v_2489 = ptr_add(self->data, _t_U64_2488);
                (void)_t_v_2489;
                (void)_t_v_2489;
                Bool _t_Bool_2490 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2489, &_t_Bool_2490);
                ;
                ;
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2491 = U32_gt(&_rc_U32_2486, &_re_U32_2486);
                (void)_wcond_Bool_2491;
                if (_wcond_Bool_2491) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2486);
                U32_dec(&_rc_U32_2486);
                U32 _t_U64_2492 = U32_mul(i, self->elem_size);
                (void)_t_U64_2492;
                ;
                void *_t_v_2493 = ptr_add(self->data, _t_U64_2492);
                (void)_t_v_2493;
                (void)_t_v_2493;
                Bool _t_Bool_2494 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(_t_v_2493, &_t_Bool_2494);
                ;
                ;
            }
        }
        ;
        ;
        ;
    }
    free(self->data);
    Bool _t_Bool_2496 = 0;
    Str_delete(&self->elem_type, &_t_Bool_2496);
    ;
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    (void)self;
    U32 _t_U64_2509 = U32_mul(self->cap, self->elem_size);
    (void)_t_U64_2509;
    void * new_data = malloc(_t_U64_2509);
    ;
    {
        U32 _re_U32_2497 = self->cap;
        (void)_re_U32_2497;
        U32 _rc_U32_2497 = 0;
        Bool _t_Bool_2508 = U32_lte(&_rc_U32_2497, &_re_U32_2497);
        (void)_t_Bool_2508;
        if (_t_Bool_2508) {
            while (1) {
                Bool _wcond_Bool_2498 = U32_lt(&_rc_U32_2497, &_re_U32_2497);
                (void)_wcond_Bool_2498;
                if (_wcond_Bool_2498) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2497);
                U32_inc(&_rc_U32_2497);
                U32 _t_U64_2499 = U32_mul(i, self->elem_size);
                (void)_t_U64_2499;
                void *_t_v_2500 = ptr_add(self->data, _t_U64_2499);
                (void)_t_v_2500;
                (void)_t_v_2500;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2500);
                ;
                U32 _t_U64_2501 = U32_mul(i, self->elem_size);
                (void)_t_U64_2501;
                ;
                void *_t_v_2502 = ptr_add(new_data, _t_U64_2501);
                (void)_t_v_2502;
                (void)_t_v_2502;
                memcpy(_t_v_2502, cloned, self->elem_size);
                ;
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2503 = U32_gt(&_rc_U32_2497, &_re_U32_2497);
                (void)_wcond_Bool_2503;
                if (_wcond_Bool_2503) {
                } else {
                    ;
                    break;
                }
                ;
                U32 i = U32_clone(&_rc_U32_2497);
                U32_dec(&_rc_U32_2497);
                U32 _t_U64_2504 = U32_mul(i, self->elem_size);
                (void)_t_U64_2504;
                void *_t_v_2505 = ptr_add(self->data, _t_U64_2504);
                (void)_t_v_2505;
                (void)_t_v_2505;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(_t_v_2505);
                ;
                U32 _t_U64_2506 = U32_mul(i, self->elem_size);
                (void)_t_U64_2506;
                ;
                void *_t_v_2507 = ptr_add(new_data, _t_U64_2506);
                (void)_t_v_2507;
                (void)_t_v_2507;
                memcpy(_t_v_2507, cloned, self->elem_size);
                ;
                free(cloned);
            }
        }
        ;
        ;
        ;
    }
    Array *_t_Array_2510 = malloc(sizeof(Array));
    _t_Array_2510->data = new_data;
    _t_Array_2510->cap = self->cap;
    _t_Array_2510->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); _t_Array_2510->elem_type = *_ca; free(_ca); }
    _t_Array_2510->elem_clone = (void *)self->elem_clone;
    _t_Array_2510->elem_delete = (void *)self->elem_delete;
    (void)_t_Array_2510;
    return _t_Array_2510;
}

U32 Array_size(void) {
    I64 _t_I64_2511 = 48;
    return _t_I64_2511;
}

void panic(Str * loc_str, Array * parts) {
    (void)loc_str;
    (void)parts;
    Str _t_Str_2750 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *_t_Type_2751 = Type_Struct(&_t_Str_2750);
    (void)_t_Type_2751;
    Str_delete(&_t_Str_2750, &(Bool){0});
    U32 _t_U32_2752 = 3;
    Array *_va_Array_92 = Array_new(_t_Type_2751, &_t_U32_2752);
    (void)_va_Array_92;
    Type_delete(_t_Type_2751, &(Bool){1});
    ;
    U32 _t_U32_2753 = 0;
    Str *_t_Str_2754 = Str_clone(loc_str);
    (void)_t_Str_2754;
    Array_set(_va_Array_92, &_t_U32_2753, _t_Str_2754);
    ;
    U32 _t_U32_2755 = 1;
    Str _t_Str_2756 = (Str){.c_str = (U8 *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_92, &_t_U32_2755, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2756; _oa; }));
    ;
    Array *_t_Array_2757 = Array_clone(parts);
    (void)_t_Array_2757;
    Array_delete(parts, &(Bool){0});
    U32 _t_U32_2758 = 2;
    Str *_t_Str_2759 = format(_t_Array_2757);
    (void)_t_Str_2759;
    Array_set(_va_Array_92, &_t_U32_2758, _t_Str_2759);
    ;
    println(_va_Array_92);
    free(_va_Array_92);
    I64 _t_I64_2760 = 1;
    exit(_t_I64_2760);
    ;
}

Bool * assert(Str * loc_str, Bool * cond) {
    (void)loc_str;
    (void)cond;
    Bool _t_Bool_2779 = not(DEREF(cond));
    (void)_t_Bool_2779;
    if (_t_Bool_2779) {
        Str _t_Str_2774 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *_t_Type_2775 = Type_Struct(&_t_Str_2774);
        (void)_t_Type_2775;
        Str_delete(&_t_Str_2774, &(Bool){0});
        U32 _t_U32_2776 = 1;
        Array *_va_Array_95 = Array_new(_t_Type_2775, &_t_U32_2776);
        (void)_va_Array_95;
        Type_delete(_t_Type_2775, &(Bool){1});
        ;
        U32 _t_U32_2777 = 0;
        Str _t_Str_2778 = (Str){.c_str = (U8 *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_95, &_t_U32_2777, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2778; _oa; }));
        ;
        panic(loc_str, _va_Array_95);
        free(_va_Array_95);
    }
    ;
    Bool _t_Bool_2780 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = _t_Bool_2780; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2803 = I64_neq(a, b);
    (void)_t_Bool_2803;
    if (_t_Bool_2803) {
        Str _t_Str_2790 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *_t_Type_2791 = Type_Struct(&_t_Str_2790);
        (void)_t_Type_2791;
        Str_delete(&_t_Str_2790, &(Bool){0});
        U32 _t_U32_2792 = 5;
        Array *_va_Array_97 = Array_new(_t_Type_2791, &_t_U32_2792);
        (void)_va_Array_97;
        Type_delete(_t_Type_2791, &(Bool){1});
        ;
        U32 _t_U32_2793 = 0;
        Str _t_Str_2794 = (Str){.c_str = (U8 *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_97, &_t_U32_2793, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2794; _oa; }));
        ;
        U32 _t_U32_2795 = 1;
        Str *_t_Str_2796 = I64_to_str(a);
        (void)_t_Str_2796;
        Array_set(_va_Array_97, &_t_U32_2795, _t_Str_2796);
        ;
        U32 _t_U32_2797 = 2;
        Str _t_Str_2798 = (Str){.c_str = (U8 *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_97, &_t_U32_2797, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2798; _oa; }));
        ;
        U32 _t_U32_2799 = 3;
        Str *_t_Str_2800 = I64_to_str(b);
        (void)_t_Str_2800;
        Array_set(_va_Array_97, &_t_U32_2799, _t_Str_2800);
        ;
        U32 _t_U32_2801 = 4;
        Str _t_Str_2802 = (Str){.c_str = (U8 *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_97, &_t_U32_2801, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2802; _oa; }));
        ;
        panic(loc_str, _va_Array_97);
        free(_va_Array_97);
    }
    ;
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    (void)loc_str;
    (void)a;
    (void)b;
    Bool _t_Bool_2817 = Str_eq(a, b);
    (void)_t_Bool_2817;
    Bool _t_Bool_2818 = not(_t_Bool_2817);
    (void)_t_Bool_2818;
    ;
    if (_t_Bool_2818) {
        Str _t_Str_2804 = (Str){.c_str = (U8 *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *_t_Type_2805 = Type_Struct(&_t_Str_2804);
        (void)_t_Type_2805;
        Str_delete(&_t_Str_2804, &(Bool){0});
        U32 _t_U32_2806 = 5;
        Array *_va_Array_98 = Array_new(_t_Type_2805, &_t_U32_2806);
        (void)_va_Array_98;
        Type_delete(_t_Type_2805, &(Bool){1});
        ;
        U32 _t_U32_2807 = 0;
        Str _t_Str_2808 = (Str){.c_str = (U8 *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_98, &_t_U32_2807, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2808; _oa; }));
        ;
        U32 _t_U32_2809 = 1;
        Str *_t_Str_2810 = Str_clone(a);
        (void)_t_Str_2810;
        Array_set(_va_Array_98, &_t_U32_2809, _t_Str_2810);
        ;
        U32 _t_U32_2811 = 2;
        Str _t_Str_2812 = (Str){.c_str = (U8 *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_98, &_t_U32_2811, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2812; _oa; }));
        ;
        U32 _t_U32_2813 = 3;
        Str *_t_Str_2814 = Str_clone(b);
        (void)_t_Str_2814;
        Array_set(_va_Array_98, &_t_U32_2813, _t_Str_2814);
        ;
        U32 _t_U32_2815 = 4;
        Str _t_Str_2816 = (Str){.c_str = (U8 *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_98, &_t_U32_2815, ({ Str *_oa = malloc(sizeof(Str)); *_oa = _t_Str_2816; _oa; }));
        ;
        panic(loc_str, _va_Array_98);
        free(_va_Array_98);
    }
    ;
}

void println(Array * parts) {
    (void)parts;
    {
        Array *_fc_Array_2819 = parts;
        (void)_fc_Array_2819;
        (void)_fc_Array_2819;
        U32 _fi_USize_2819 = 0;
        while (1) {
            U32 _t_U32_2821; { U32 *_hp = (U32 *)Array_len(_fc_Array_2819); _t_U32_2821 = *_hp; free(_hp); }
            (void)_t_U32_2821;
            Bool _wcond_Bool_2820 = U32_lt(&_fi_USize_2819, &_t_U32_2821);
            (void)_wcond_Bool_2820;
            ;
            if (_wcond_Bool_2820) {
            } else {
                ;
                break;
            }
            ;
            Str *s = Array_get(_fc_Array_2819, &_fi_USize_2819);
            U32 _t_U32_2822 = 1;
            U32 _t_U32_2823 = U32_add(_fi_USize_2819, _t_U32_2822);
            (void)_t_U32_2823;
            ;
            _fi_USize_2819 = _t_U32_2823;
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
    Str _t_Str_3017 = (Str){.c_str = (U8 *)"src/test/constfold.til:15:15", .count = 28ULL, .cap = TIL_CAP_LIT};
    I64 _t_I64_3018 = 3;
    assert_eq(&_t_Str_3017, &result, &_t_I64_3018);
    ;
    Str_delete(&_t_Str_3017, &(Bool){0});
    ;
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str _t_Str_3025 = (Str){.c_str = (U8 *)"src/test/constfold.til:21:15", .count = 28ULL, .cap = TIL_CAP_LIT};
    I64 _t_I64_3026 = 15;
    assert_eq(&_t_Str_3025, &result, &_t_I64_3026);
    ;
    Str_delete(&_t_Str_3025, &(Bool){0});
    ;
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str _t_Str_3033 = (Str){.c_str = (U8 *)"src/test/constfold.til:27:15", .count = 28ULL, .cap = TIL_CAP_LIT};
    I64 _t_I64_3034 = 26;
    assert_eq(&_t_Str_3033, &result, &_t_I64_3034);
    ;
    Str_delete(&_t_Str_3033, &(Bool){0});
    ;
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (U8 *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str _t_Str_3037 = (Str){.c_str = (U8 *)"src/test/constfold.til:33:19", .count = 28ULL, .cap = TIL_CAP_LIT};
    Str _t_Str_3038 = (Str){.c_str = (U8 *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&_t_Str_3037, &result, &_t_Str_3038);
    Str_delete(&_t_Str_3037, &(Bool){0});
    Str_delete(&_t_Str_3038, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str _t_Str_3066 = (Str){.c_str = (U8 *)"src/test/constfold.til:62:12", .count = 28ULL, .cap = TIL_CAP_LIT};
    Bool _t_Bool_3067 = 1;
    assert(&_t_Str_3066, &_t_Bool_3067);
    ;
    Str_delete(&_t_Str_3066, &(Bool){0});
    Str _t_Str_3070 = (Str){.c_str = (U8 *)"src/test/constfold.til:63:12", .count = 28ULL, .cap = TIL_CAP_LIT};
    Bool _t_Bool_3071 = 1;
    assert(&_t_Str_3070, &_t_Bool_3071);
    ;
    Str_delete(&_t_Str_3070, &(Bool){0});
    Str _t_Str_3074 = (Str){.c_str = (U8 *)"src/test/constfold.til:65:12", .count = 28ULL, .cap = TIL_CAP_LIT};
    Bool _t_Bool_3075 = 1;
    assert(&_t_Str_3074, &_t_Bool_3075);
    ;
    Str_delete(&_t_Str_3074, &(Bool){0});
    Str _t_Str_3078 = (Str){.c_str = (U8 *)"src/test/constfold.til:66:12", .count = 28ULL, .cap = TIL_CAP_LIT};
    Bool _t_Bool_3079 = 1;
    assert(&_t_Str_3078, &_t_Bool_3079);
    ;
    Str_delete(&_t_Str_3078, &(Bool){0});
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
    case Type_TAG_Unknown: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_None: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_I64: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_U8: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_I16: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_I32: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_U32: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_U64: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_F32: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Bool: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Struct: return Str_clone(&type->data.Struct);
    case Type_TAG_StructDef: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Enum: return Str_clone(&type->data.Enum);
    case Type_TAG_EnumDef: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_FuncDef: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_FuncPtr: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Dynamic: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Custom: return Str_clone(&type->data.Custom);
    }
    return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (U8 *)"?", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    __til_info_blob__ = (Str){.c_str=(U8*)"", .count=0ULL, .cap=TIL_CAP_LIT};
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
