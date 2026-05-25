#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef struct Str Str;
typedef struct Dynamic Dynamic;
typedef enum {
    Primitive_TAG_I16
} Primitive_tag;
typedef struct Primitive Primitive;
typedef enum {
    Type_TAG_Unknown,
    Type_TAG_None,
    Type_TAG_I64,
    Type_TAG_U8,
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
    Type_TAG_Custom,
    Type_TAG_I8,
    Type_TAG_Primitive
} Type_tag;
typedef struct Type Type;
typedef struct Array Array;
typedef struct CfVec2 CfVec2;
typedef struct CfRect CfRect;
typedef enum {
    Color_TAG_Red,
    Color_TAG_Green,
    Color_TAG_Blue
} Color_tag;
typedef struct Color Color;
typedef enum {
    Token_TAG_Num,
    Token_TAG_Name,
    Token_TAG_Eof
} Token_tag;
typedef struct Token Token;

typedef void * (*CloneFn)(void *);
typedef void (*DeleteFn)(void *, Bool *);






typedef struct Str {
    I8 *c_str;
    U32 count;
    U32 cap;
} Str;


typedef struct Dynamic {
    char _;
} Dynamic;




struct Primitive {
    Primitive_tag tag;
};

struct Type {
    Type_tag tag;
    union {
        Str Struct;
        Str Enum;
        Str Custom;
        Primitive Primitive;
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


typedef struct CfVec2 {
    I64 x;
    I64 y;
} CfVec2;


typedef struct CfRect {
    CfVec2 top_left;
    CfVec2 bottom_right;
} CfRect;


struct Color {
    Color_tag tag;
};

struct Token {
    Token_tag tag;
    union {
        I64 Num;
        Str Name;
    } data;
};

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
void I8_delete(I8 * self, Bool * call_free);
U32 * I8_size(void);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
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
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool * call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
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
void UNREACHABLE(Str * loc_str);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
void println(Array * parts);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
CfVec2 * CfVec2_magic(void);
CfVec2 * CfVec2_at(I64 * x, I64 * y);
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool * call_free);
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_sample(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool * call_free);
U32 CfRect_size(void);
void test_struct_fold_nested(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool * call_free);
Color * Color_clone(Color * self);
U32 Color_size(void);
void test_enum_fold(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool * call_free);
Token * Token_clone(Token * self);
U32 Token_size(void);
void test_enum_payload_fold(void);
Bool Color_eq(Color *, Color *);
Color *Color_Red();
Color *Color_Green();
Color *Color_Blue();
Bool * Token_eq(Token *, Token *);
Token *Token_Num(I64 *);
Token *Token_Name(Str *);
Token *Token_Eof();
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
void I8_delete(I8 * self, Bool * call_free);
U32 * I8_size(void);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
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
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool * call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
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
void UNREACHABLE(Str * loc_str);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
void println(Array * parts);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
CfVec2 * CfVec2_magic(void);
CfVec2 * CfVec2_at(I64 * x, I64 * y);
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool * call_free);
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_sample(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool * call_free);
U32 CfRect_size(void);
void test_struct_fold_nested(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool * call_free);
Color * Color_clone(Color * self);
U32 Color_size(void);
void test_enum_fold(void);
Token * Token_Num(I64 * val);
Token * Token_Name(Str * val);
Token * Token_Eof(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool * call_free);
Token * Token_clone(Token * self);
U32 Token_size(void);
void test_enum_payload_fold(void);
Bool Primitive_eq(Primitive *, Primitive *);
Primitive *Primitive_I16();
Bool * Type_eq(Type *, Type *);
Type *Type_Unknown();
Type *Type_None();
Type *Type_I64();
Type *Type_U8();
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
Type *Type_I8();
Type *Type_Primitive(Primitive *);
Bool Color_eq(Color *, Color *);
Color *Color_Red();
Color *Color_Green();
Color *Color_Blue();
Bool * Token_eq(Token *, Token *);
Token *Token_Num(I64 *);
Token *Token_Name(Str *);
Token *Token_Eof();

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
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U64_size(void) {
    U32 hoisted__U32_26 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_26; return _r; }
}

Str * U32_to_str(U32 * val) {
    I64 hoisted__I64_41 = U32_to_i64(DEREF(val));
    Str *hoisted__Str_42 = I64_to_str(&hoisted__I64_41);
    return hoisted__Str_42;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_43 = 1;
    U32 hoisted__U32_44 = U32_add(DEREF(self), hoisted__U32_43);
    *self = hoisted__U32_44;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_45 = 1;
    U32 hoisted__U32_46 = U32_sub(DEREF(self), hoisted__U32_45);
    *self = hoisted__U32_46;
}

void U32_delete(U32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U32_size(void) {
    U32 hoisted__U32_53 = 4;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_53; return _r; }
}

Bool U32_lt(U32 * a, U32 * b) {
    I64 hoisted__I64_54 = 0;
    I64 hoisted__I64_55 = 1;
    I64 hoisted__I64_56 = U32_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_57 = I64_sub(hoisted__I64_54, hoisted__I64_55);
    Bool hoisted__Bool_58 = I64_eq(hoisted__I64_56, hoisted__I64_57);
    return hoisted__Bool_58;
}

Bool U32_gt(U32 * a, U32 * b) {
    I64 hoisted__I64_59 = U32_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_60 = 1;
    Bool hoisted__Bool_61 = I64_eq(hoisted__I64_59, hoisted__I64_60);
    return hoisted__Bool_61;
}

Bool U32_lte(U32 * a, U32 * b) {
    Bool hoisted__Bool_64 = U32_gt(a, b);
    Bool hoisted__Bool_65 = not(hoisted__Bool_64);
    return hoisted__Bool_65;
}

Bool U32_gte(U32 * a, U32 * b) {
    Bool hoisted__Bool_66 = U32_lt(a, b);
    Bool hoisted__Bool_67 = not(hoisted__Bool_66);
    return hoisted__Bool_67;
}

void I32_delete(I32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I32_size(void) {
    U32 hoisted__U32_92 = 4;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_92; return _r; }
}

void I8_delete(I8 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I8_size(void) {
    U32 hoisted__U32_131 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_131; return _r; }
}

void U8_delete(U8 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U8_size(void) {
    U32 hoisted__U32_158 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_158; return _r; }
}

Str * format(Array * parts) {
    U32 total = 0;
    {
        Array *_fc_Array_464 = parts;
        (void)_fc_Array_464;
        (void)_fc_Array_464;
        U32 _fi_USize_464 = 0;
        (void)_fi_USize_464;
        while (1) {
            U32 hoisted__U32_466; { U32 *_hp = (U32 *)Array_len(_fc_Array_464); hoisted__U32_466 = *_hp; free(_hp); }
            Bool _wcond_Bool_465 = U32_lt(&_fi_USize_464, &hoisted__U32_466);
            (void)_wcond_Bool_465;
            if (_wcond_Bool_465) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_464, &_fi_USize_464);
            U32 hoisted__U32_467 = 1;
            U32 hoisted__U32_468 = U32_add(_fi_USize_464, hoisted__U32_467);
            _fi_USize_464 = hoisted__U32_468;
            U32 hoisted__U32_469 = Str_len(s);
            U32 hoisted__U32_470 = U32_add(total, hoisted__U32_469);
            total = hoisted__U32_470;
        }
    }
    Str *out = Str_with_capacity(&total);
    {
        Array *_fc_Array_471 = parts;
        (void)_fc_Array_471;
        (void)_fc_Array_471;
        U32 _fi_USize_471 = 0;
        (void)_fi_USize_471;
        while (1) {
            U32 hoisted__U32_473; { U32 *_hp = (U32 *)Array_len(_fc_Array_471); hoisted__U32_473 = *_hp; free(_hp); }
            Bool _wcond_Bool_472 = U32_lt(&_fi_USize_471, &hoisted__U32_473);
            (void)_wcond_Bool_472;
            if (_wcond_Bool_472) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_471, &_fi_USize_471);
            U32 hoisted__U32_474 = 1;
            U32 hoisted__U32_475 = U32_add(_fi_USize_471, hoisted__U32_474);
            _fi_USize_471 = hoisted__U32_475;
            Str_push_str(out, s);
        }
    }
    Array_delete(parts, &(Bool){1});
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_482 = U32_gte(i, &self->count);
    if (hoisted__Bool_482) {
        Str hoisted__Str_476 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_477 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_476; _oa; }));
        U32 hoisted__U32_478 = 1;
        Array *_va_Array_10 = Array_new(hoisted__Type_477, &hoisted__U32_478);
        (void)_va_Array_10;
        Type_delete(hoisted__Type_477, &(Bool){1});
        U32 hoisted__U32_479 = 0;
        Str hoisted__Str_480 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_10, &hoisted__U32_479, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_480; _oa; }));
        Str hoisted__Str_481 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_481, _va_Array_10);
        Str_delete(&hoisted__Str_481, &(Bool){0});
    }
    void *hoisted__v_483 = ptr_add(self->c_str, DEREF(i));
    return hoisted__v_483;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_493 = U32_lt(&b->count, &a->count);
    if (hoisted__Bool_493) {
        min_len = b->count;
    }
    {
        U32 _re_U32_485 = U32_clone(&min_len);
        (void)_re_U32_485;
        U32 _rc_U32_485 = 0;
        (void)_rc_U32_485;
        Bool hoisted__Bool_492 = U32_lte(&_rc_U32_485, &_re_U32_485);
        if (hoisted__Bool_492) {
            while (1) {
                Bool _wcond_Bool_486 = U32_lt(&_rc_U32_485, &_re_U32_485);
                (void)_wcond_Bool_486;
                if (_wcond_Bool_486) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_485);
                U32_inc(&_rc_U32_485);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_487 = 0;
                Bool hoisted__Bool_488 = I64_neq(&c, &hoisted__I64_487);
                if (hoisted__Bool_488) {
                    return c;
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_489 = U32_gt(&_rc_U32_485, &_re_U32_485);
                (void)_wcond_Bool_489;
                if (_wcond_Bool_489) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_485);
                U32_dec(&_rc_U32_485);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_490 = 0;
                Bool hoisted__Bool_491 = I64_neq(&c, &hoisted__I64_490);
                if (hoisted__Bool_491) {
                    return c;
                }
            }
        }
    }
    I64 hoisted__I64_494 = U32_cmp(a->count, b->count);
    return hoisted__I64_494;
}

Str * Str_with_capacity(U32 * n) {
    U32 hoisted__U32_496 = 1;
    U32 hoisted__U64_497 = U32_add(DEREF(n), hoisted__U32_496);
    void * buf = malloc(hoisted__U64_497);
    I32 hoisted__I32_498 = 0;
    U64 hoisted__U64_499 = 1;
    memset(buf, hoisted__I32_498, hoisted__U64_499);
    I32_delete(&hoisted__I32_498, &(Bool){0});
    I64 hoisted__I64_500 = 0;
    Str *hoisted__Str_501 = malloc(sizeof(Str));
    hoisted__Str_501->c_str = buf;
    hoisted__Str_501->count = hoisted__I64_500;
    hoisted__Str_501->cap = DEREF(n);
    return hoisted__Str_501;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_514 = U32_gte(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_514) {
        Str hoisted__Str_502 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_503 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_502; _oa; }));
        U32 hoisted__U32_504 = 1;
        Array *_va_Array_11 = Array_new(hoisted__Type_503, &hoisted__U32_504);
        (void)_va_Array_11;
        Type_delete(hoisted__Type_503, &(Bool){1});
        U32 hoisted__U32_505 = 0;
        Str hoisted__Str_506 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_11, &hoisted__U32_505, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_506; _oa; }));
        Str hoisted__Str_507 = (Str){.c_str = (void *)"./src/core/str.til:85:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_507, _va_Array_11);
        Str_delete(&hoisted__Str_507, &(Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_515 = U32_gt(&new_len, &self->cap);
    if (hoisted__Bool_515) {
        Str hoisted__Str_508 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_509 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_508; _oa; }));
        U32 hoisted__U32_510 = 1;
        Array *_va_Array_12 = Array_new(hoisted__Type_509, &hoisted__U32_510);
        (void)_va_Array_12;
        Type_delete(hoisted__Type_509, &(Bool){1});
        U32 hoisted__U32_511 = 0;
        Str hoisted__Str_512 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_12, &hoisted__U32_511, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_512; _oa; }));
        Str hoisted__Str_513 = (Str){.c_str = (void *)"./src/core/str.til:89:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_513, _va_Array_12);
        Str_delete(&hoisted__Str_513, &(Bool){0});
    }
    void *hoisted__v_516 = ptr_add(self->c_str, self->count);
    memcpy(hoisted__v_516, s->c_str, s->count);
    U32 hoisted__U32_517 = U32_clone(&new_len);
    self->count = hoisted__U32_517;
    void *hoisted__v_518 = ptr_add(self->c_str, new_len);
    I32 hoisted__I32_519 = 0;
    U64 hoisted__U64_520 = 1;
    memset(hoisted__v_518, hoisted__I32_519, hoisted__U64_520);
    I32_delete(&hoisted__I32_519, &(Bool){0});
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_521 = 1;
    U32 hoisted__U64_522 = U32_add(val->count, hoisted__U32_521);
    void * new_data = malloc(hoisted__U64_522);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_523 = ptr_add(new_data, val->count);
    I32 hoisted__I32_524 = 0;
    U64 hoisted__U64_525 = 1;
    memset(hoisted__v_523, hoisted__I32_524, hoisted__U64_525);
    I32_delete(&hoisted__I32_524, &(Bool){0});
    Str *hoisted__Str_526 = malloc(sizeof(Str));
    hoisted__Str_526->c_str = new_data;
    hoisted__Str_526->count = val->count;
    hoisted__Str_526->cap = val->count;
    return hoisted__Str_526;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool hoisted__Bool_527 = U32_lt(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_527) {
        free(self->c_str);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_592 = 0;
    Bool hoisted__Bool_593 = U32_eq(self->count, hoisted__U32_592);
    return hoisted__Bool_593;
}

U32 Str_size(void) {
    U32 hoisted__U32_864 = 16;
    return hoisted__U32_864;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_865 = Str_cmp(a, b);
    I64 hoisted__I64_866 = 0;
    Bool hoisted__Bool_867 = I64_eq(hoisted__I64_865, hoisted__I64_866);
    return hoisted__Bool_867;
}

U32 * Dynamic_size(void) {
    U32 hoisted__U32_954 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_954; return _r; }
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 * val) {
    I64 hoisted__I64_1032 = 0;
    Bool hoisted__Bool_1033 = I64_eq(DEREF(val), hoisted__I64_1032);
    if (hoisted__Bool_1033) {
        U64 hoisted__U64_996 = 2;
        void * buf = malloc(hoisted__U64_996);
        I64 hoisted__I64_997 = 48;
        U64 hoisted__U64_998 = 1;
        memcpy(buf, &hoisted__I64_997, hoisted__U64_998);
        U64 hoisted__U64_999 = 1;
        void *hoisted__v_1000 = ptr_add(buf, hoisted__U64_999);
        I32 hoisted__I32_1001 = 0;
        U64 hoisted__U64_1002 = 1;
        memset(hoisted__v_1000, hoisted__I32_1001, hoisted__U64_1002);
        I32_delete(&hoisted__I32_1001, &(Bool){0});
        I64 hoisted__I64_1003 = 1;
        I64 hoisted__I64_1004 = 1;
        Str *hoisted__Str_1005 = malloc(sizeof(Str));
        hoisted__Str_1005->c_str = buf;
        hoisted__Str_1005->count = hoisted__I64_1003;
        hoisted__Str_1005->cap = hoisted__I64_1004;
        return hoisted__Str_1005;
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_1034 = 0;
    Bool hoisted__Bool_1035 = I64_lt(val, &hoisted__I64_1034);
    if (hoisted__Bool_1035) {
        Bool hoisted__Bool_1006 = 1;
        is_neg = hoisted__Bool_1006;
        I64 hoisted__I64_1007 = 0;
        I64 hoisted__I64_1008 = I64_sub(hoisted__I64_1007, DEREF(val));
        v = hoisted__I64_1008;
    }
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1010 = 0;
        Bool _wcond_Bool_1009 = I64_gt(&tmp, &hoisted__I64_1010);
        (void)_wcond_Bool_1009;
        if (_wcond_Bool_1009) {
        } else {
            break;
        }
        U64 hoisted__U64_1011 = 1;
        U64 hoisted__U64_1012 = U64_add(ndigits, hoisted__U64_1011);
        ndigits = hoisted__U64_1012;
        I64 hoisted__I64_1013 = 10;
        I64 hoisted__I64_1014 = I64_div(tmp, hoisted__I64_1013);
        tmp = hoisted__I64_1014;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1015 = 1;
        U64 hoisted__U64_1016 = U64_add(total, hoisted__U64_1015);
        total = hoisted__U64_1016;
    }
    U64 hoisted__U64_1036 = 1;
    U64 hoisted__U64_1037 = U64_add(total, hoisted__U64_1036);
    void * buf = malloc(hoisted__U64_1037);
    if (is_neg) {
        I64 hoisted__I64_1017 = 45;
        U64 hoisted__U64_1018 = 1;
        memcpy(buf, &hoisted__I64_1017, hoisted__U64_1018);
    }
    U64 hoisted__U64_1038 = 1;
    U64 i = U64_sub(total, hoisted__U64_1038);
    while (1) {
        I64 hoisted__I64_1020 = 0;
        Bool _wcond_Bool_1019 = I64_gt(&v, &hoisted__I64_1020);
        (void)_wcond_Bool_1019;
        if (_wcond_Bool_1019) {
        } else {
            break;
        }
        I64 hoisted__I64_1021 = 10;
        I64 hoisted__I64_1022 = I64_mod(v, hoisted__I64_1021);
        I64 hoisted__I64_1023 = 48;
        I64 hoisted__I64_1024 = I64_add(hoisted__I64_1022, hoisted__I64_1023);
        void *hoisted__v_1025 = ptr_add(buf, i);
        U8 hoisted__U8_1026 = I64_to_u8(hoisted__I64_1024);
        U64 hoisted__U64_1027 = 1;
        memcpy(hoisted__v_1025, &hoisted__U8_1026, hoisted__U64_1027);
        U8_delete(&hoisted__U8_1026, &(Bool){0});
        I64 hoisted__I64_1028 = 10;
        I64 hoisted__I64_1029 = I64_div(v, hoisted__I64_1028);
        v = hoisted__I64_1029;
        U64 hoisted__U64_1030 = 1;
        U64 hoisted__U64_1031 = U64_sub(i, hoisted__U64_1030);
        i = hoisted__U64_1031;
    }
    void *hoisted__v_1039 = ptr_add(buf, total);
    I32 hoisted__I32_1040 = 0;
    U64 hoisted__U64_1041 = 1;
    memset(hoisted__v_1039, hoisted__I32_1040, hoisted__U64_1041);
    I32_delete(&hoisted__I32_1040, &(Bool){0});
    Str *hoisted__Str_1042 = malloc(sizeof(Str));
    hoisted__Str_1042->c_str = buf;
    hoisted__Str_1042->count = total;
    hoisted__Str_1042->cap = total;
    return hoisted__Str_1042;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    U32 hoisted__U32_1060 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1060; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1070 = 0;
    I64 hoisted__I64_1071 = 1;
    I64 hoisted__I64_1072 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1073 = I64_sub(hoisted__I64_1070, hoisted__I64_1071);
    Bool hoisted__Bool_1074 = I64_eq(hoisted__I64_1072, hoisted__I64_1073);
    return hoisted__Bool_1074;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1075 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1076 = 1;
    Bool hoisted__Bool_1077 = I64_eq(hoisted__I64_1075, hoisted__I64_1076);
    return hoisted__Bool_1077;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1078 = I64_eq(DEREF(a), DEREF(b));
    Bool hoisted__Bool_1079 = not(hoisted__Bool_1078);
    return hoisted__Bool_1079;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1090 = Bool_eq(DEREF(a), DEREF(b));
    if (hoisted__Bool_1090) {
        I64 hoisted__I64_1088 = 0;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1088; return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1089 = -1;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1089; return _r; }
    }
    I64 hoisted__I64_1091 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1091; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    U32 hoisted__U32_1092 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1092; return _r; }
}

Primitive *Primitive_I16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I16 };
    return r;
}
Bool Primitive_eq(Primitive * self, Primitive * other) {
    Bool hoisted__Bool_1251 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1251) {
        Bool hoisted__Bool_1250 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        return hoisted__Bool_1250;
    }
    Bool hoisted__Bool_1252 = 0;
    return hoisted__Bool_1252;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1256 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1256) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
    }
    Str hoisted__Str_1257 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_1257);
    Str_delete(&hoisted__Str_1257, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1258 = 4;
    return hoisted__U32_1258;
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
    r->data.Struct = *val;
    free(val);
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
    r->data.Enum = *val;
    free(val);
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
    r->data.Custom = *val;
    free(val);
    return r;
}
Type *Type_I8() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_I8;
    return r;
}
Type *Type_Primitive(Primitive * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Primitive;
    r->data.Primitive = *val;
    free(val);
    return r;
}
void Type_delete(Type * self, Bool * call_free) {
    Bool hoisted__Bool_1317 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1317) {
        Str *hoisted__Str_1309 = get_payload(self);
        Bool hoisted__Bool_1310 = 0;
        Str_delete(hoisted__Str_1309, &hoisted__Bool_1310);
    }
    Bool hoisted__Bool_1318 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1318) {
        Str *hoisted__Str_1311 = get_payload(self);
        Bool hoisted__Bool_1312 = 0;
        Str_delete(hoisted__Str_1311, &hoisted__Bool_1312);
    }
    Bool hoisted__Bool_1319 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1319) {
        Str *hoisted__Str_1313 = get_payload(self);
        Bool hoisted__Bool_1314 = 0;
        Str_delete(hoisted__Str_1313, &hoisted__Bool_1314);
    }
    Bool hoisted__Bool_1320 = is(self, &(Type){.tag = Type_TAG_Primitive});
    if (hoisted__Bool_1320) {
        Primitive *hoisted__Primitive_1315 = get_payload(self);
        Bool hoisted__Bool_1316 = 0;
        Primitive_delete(hoisted__Primitive_1315, &hoisted__Bool_1316);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1402 = is(self, &(Type){.tag = Type_TAG_Unknown});
    if (hoisted__Bool_1402) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown; return _r; }
    }
    Bool hoisted__Bool_1403 = is(self, &(Type){.tag = Type_TAG_None});
    if (hoisted__Bool_1403) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None; return _r; }
    }
    Bool hoisted__Bool_1404 = is(self, &(Type){.tag = Type_TAG_I64});
    if (hoisted__Bool_1404) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64; return _r; }
    }
    Bool hoisted__Bool_1405 = is(self, &(Type){.tag = Type_TAG_U8});
    if (hoisted__Bool_1405) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8; return _r; }
    }
    Bool hoisted__Bool_1406 = is(self, &(Type){.tag = Type_TAG_I32});
    if (hoisted__Bool_1406) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32; return _r; }
    }
    Bool hoisted__Bool_1407 = is(self, &(Type){.tag = Type_TAG_U32});
    if (hoisted__Bool_1407) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32; return _r; }
    }
    Bool hoisted__Bool_1408 = is(self, &(Type){.tag = Type_TAG_U64});
    if (hoisted__Bool_1408) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64; return _r; }
    }
    Bool hoisted__Bool_1409 = is(self, &(Type){.tag = Type_TAG_F32});
    if (hoisted__Bool_1409) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32; return _r; }
    }
    Bool hoisted__Bool_1410 = is(self, &(Type){.tag = Type_TAG_Bool});
    if (hoisted__Bool_1410) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool; return _r; }
    }
    Bool hoisted__Bool_1411 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1411) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_1396 = Str_clone(_clone_payload_Struct_9);
        Type *hoisted__Type_1397 = Type_Struct(hoisted__Str_1396);
        return hoisted__Type_1397;
    }
    Bool hoisted__Bool_1412 = is(self, &(Type){.tag = Type_TAG_StructDef});
    if (hoisted__Bool_1412) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef; return _r; }
    }
    Bool hoisted__Bool_1413 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1413) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_1398 = Str_clone(_clone_payload_Enum_11);
        Type *hoisted__Type_1399 = Type_Enum(hoisted__Str_1398);
        return hoisted__Type_1399;
    }
    Bool hoisted__Bool_1414 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    if (hoisted__Bool_1414) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef; return _r; }
    }
    Bool hoisted__Bool_1415 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    if (hoisted__Bool_1415) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef; return _r; }
    }
    Bool hoisted__Bool_1416 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    if (hoisted__Bool_1416) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr; return _r; }
    }
    Bool hoisted__Bool_1417 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    if (hoisted__Bool_1417) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic; return _r; }
    }
    Bool hoisted__Bool_1418 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1418) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_1400 = Str_clone(_clone_payload_Custom_16);
        Type *hoisted__Type_1401 = Type_Custom(hoisted__Str_1400);
        return hoisted__Type_1401;
    }
    Bool hoisted__Bool_1419 = is(self, &(Type){.tag = Type_TAG_I8});
    if (hoisted__Bool_1419) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8; return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive *hoisted__Primitive_1420 = Primitive_clone(_clone_payload_Primitive_18);
    Type *hoisted__Type_1421 = Type_Primitive(hoisted__Primitive_1420);
    return hoisted__Type_1421;
}

U32 Type_size(void) {
    U32 hoisted__U32_1422 = 24;
    return hoisted__U32_1422;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_2856 = Str_is_empty(elem_type);
    if (hoisted__Bool_2856) {
        Str hoisted__Str_2850 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2851 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2850; _oa; }));
        U32 hoisted__U32_2852 = 1;
        Array *_va_Array_77 = Array_new(hoisted__Type_2851, &hoisted__U32_2852);
        (void)_va_Array_77;
        Type_delete(hoisted__Type_2851, &(Bool){1});
        U32 hoisted__U32_2853 = 0;
        Str hoisted__Str_2854 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_77, &hoisted__U32_2853, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2854; _oa; }));
        Str hoisted__Str_2855 = (Str){.c_str = (void *)"./src/core/array.til:23:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2855, _va_Array_77);
        Str_delete(&hoisted__Str_2855, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_2857 = calloc(DEREF(cap), elem_size);
    void * hoisted__v_2858 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    void * hoisted__v_2859 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    Array *hoisted__Array_2860 = malloc(sizeof(Array));
    hoisted__Array_2860->data = hoisted__v_2857;
    hoisted__Array_2860->cap = DEREF(cap);
    hoisted__Array_2860->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); hoisted__Array_2860->elem_type = *_ca; free(_ca); }
    hoisted__Array_2860->elem_clone = hoisted__v_2858;
    hoisted__Array_2860->elem_delete = hoisted__v_2859;
    return hoisted__Array_2860;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_2861 = Array_new_type_name(elem_type, cap);
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_2861;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    Bool hoisted__Bool_2876 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2876) {
        Str hoisted__Str_2862 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2863 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2862; _oa; }));
        U32 hoisted__U32_2864 = 5;
        Array *_va_Array_78 = Array_new(hoisted__Type_2863, &hoisted__U32_2864);
        (void)_va_Array_78;
        Type_delete(hoisted__Type_2863, &(Bool){1});
        U32 hoisted__U32_2865 = 0;
        Str hoisted__Str_2866 = (Str){.c_str = (void *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_78, &hoisted__U32_2865, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2866; _oa; }));
        U32 hoisted__U32_2867 = 1;
        Str *hoisted__Str_2868 = U32_to_str(i);
        Array_set(_va_Array_78, &hoisted__U32_2867, hoisted__Str_2868);
        U32 hoisted__U32_2869 = 2;
        Str hoisted__Str_2870 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_78, &hoisted__U32_2869, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2870; _oa; }));
        U32 hoisted__U32_2871 = 3;
        Str *hoisted__Str_2872 = U32_to_str(&self->cap);
        Array_set(_va_Array_78, &hoisted__U32_2871, hoisted__Str_2872);
        U32 hoisted__U32_2873 = 4;
        Str hoisted__Str_2874 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_78, &hoisted__U32_2873, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2874; _oa; }));
        Str hoisted__Str_2875 = (Str){.c_str = (void *)"./src/core/array.til:41:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2875, _va_Array_78);
        Str_delete(&hoisted__Str_2875, &(Bool){0});
    }
    U32 hoisted__U64_2877 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2878 = ptr_add(self->data, hoisted__U64_2877);
    return hoisted__v_2878;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_2893 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2893) {
        Str hoisted__Str_2879 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2880 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2879; _oa; }));
        U32 hoisted__U32_2881 = 5;
        Array *_va_Array_79 = Array_new(hoisted__Type_2880, &hoisted__U32_2881);
        (void)_va_Array_79;
        Type_delete(hoisted__Type_2880, &(Bool){1});
        U32 hoisted__U32_2882 = 0;
        Str hoisted__Str_2883 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_79, &hoisted__U32_2882, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2883; _oa; }));
        U32 hoisted__U32_2884 = 1;
        Str *hoisted__Str_2885 = U32_to_str(i);
        Array_set(_va_Array_79, &hoisted__U32_2884, hoisted__Str_2885);
        U32 hoisted__U32_2886 = 2;
        Str hoisted__Str_2887 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_79, &hoisted__U32_2886, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2887; _oa; }));
        U32 hoisted__U32_2888 = 3;
        Str *hoisted__Str_2889 = U32_to_str(&self->cap);
        Array_set(_va_Array_79, &hoisted__U32_2888, hoisted__Str_2889);
        U32 hoisted__U32_2890 = 4;
        Str hoisted__Str_2891 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_79, &hoisted__U32_2890, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2891; _oa; }));
        Str hoisted__Str_2892 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2892, _va_Array_79);
        Str_delete(&hoisted__Str_2892, &(Bool){0});
    }
    U32 hoisted__U64_2894 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2895 = ptr_add(self->data, hoisted__U64_2894);
    Bool hoisted__Bool_2896 = 0;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2895, &hoisted__Bool_2896);
    U32 hoisted__U64_2897 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2898 = ptr_add(self->data, hoisted__U64_2897);
    memcpy(hoisted__v_2898, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_2899 = self->cap;
        (void)_re_U32_2899;
        U32 _rc_U32_2899 = 0;
        (void)_rc_U32_2899;
        Bool hoisted__Bool_2908 = U32_lte(&_rc_U32_2899, &_re_U32_2899);
        if (hoisted__Bool_2908) {
            while (1) {
                Bool _wcond_Bool_2900 = U32_lt(&_rc_U32_2899, &_re_U32_2899);
                (void)_wcond_Bool_2900;
                if (_wcond_Bool_2900) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2899);
                U32_inc(&_rc_U32_2899);
                U32 hoisted__U64_2901 = U32_mul(i, self->elem_size);
                void *hoisted__v_2902 = ptr_add(self->data, hoisted__U64_2901);
                Bool hoisted__Bool_2903 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2902, &hoisted__Bool_2903);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2904 = U32_gt(&_rc_U32_2899, &_re_U32_2899);
                (void)_wcond_Bool_2904;
                if (_wcond_Bool_2904) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2899);
                U32_dec(&_rc_U32_2899);
                U32 hoisted__U64_2905 = U32_mul(i, self->elem_size);
                void *hoisted__v_2906 = ptr_add(self->data, hoisted__U64_2905);
                Bool hoisted__Bool_2907 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2906, &hoisted__Bool_2907);
            }
        }
    }
    free(self->data);
    Bool hoisted__Bool_2909 = 0;
    Str_delete(&self->elem_type, &hoisted__Bool_2909);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_2922 = U32_mul(self->cap, self->elem_size);
    void * new_data = malloc(hoisted__U64_2922);
    {
        U32 _re_U32_2910 = self->cap;
        (void)_re_U32_2910;
        U32 _rc_U32_2910 = 0;
        (void)_rc_U32_2910;
        Bool hoisted__Bool_2921 = U32_lte(&_rc_U32_2910, &_re_U32_2910);
        if (hoisted__Bool_2921) {
            while (1) {
                Bool _wcond_Bool_2911 = U32_lt(&_rc_U32_2910, &_re_U32_2910);
                (void)_wcond_Bool_2911;
                if (_wcond_Bool_2911) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2910);
                U32_inc(&_rc_U32_2910);
                U32 hoisted__U64_2912 = U32_mul(i, self->elem_size);
                void *hoisted__v_2913 = ptr_add(self->data, hoisted__U64_2912);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2913);
                U32 hoisted__U64_2914 = U32_mul(i, self->elem_size);
                void *hoisted__v_2915 = ptr_add(new_data, hoisted__U64_2914);
                memcpy(hoisted__v_2915, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2916 = U32_gt(&_rc_U32_2910, &_re_U32_2910);
                (void)_wcond_Bool_2916;
                if (_wcond_Bool_2916) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2910);
                U32_dec(&_rc_U32_2910);
                U32 hoisted__U64_2917 = U32_mul(i, self->elem_size);
                void *hoisted__v_2918 = ptr_add(self->data, hoisted__U64_2917);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2918);
                U32 hoisted__U64_2919 = U32_mul(i, self->elem_size);
                void *hoisted__v_2920 = ptr_add(new_data, hoisted__U64_2919);
                memcpy(hoisted__v_2920, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_2923 = malloc(sizeof(Array));
    hoisted__Array_2923->data = new_data;
    hoisted__Array_2923->cap = self->cap;
    hoisted__Array_2923->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); hoisted__Array_2923->elem_type = *_ca; free(_ca); }
    hoisted__Array_2923->elem_clone = (void *)self->elem_clone;
    hoisted__Array_2923->elem_delete = (void *)self->elem_delete;
    return hoisted__Array_2923;
}

U32 Array_size(void) {
    U32 hoisted__U32_2924 = 48;
    return hoisted__U32_2924;
}

void panic(Str * loc_str, Array * parts) {
    Str hoisted__Str_3161 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_3162 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3161; _oa; }));
    U32 hoisted__U32_3163 = 3;
    Array *_va_Array_96 = Array_new(hoisted__Type_3162, &hoisted__U32_3163);
    (void)_va_Array_96;
    Type_delete(hoisted__Type_3162, &(Bool){1});
    U32 hoisted__U32_3164 = 0;
    Str *hoisted__Str_3165 = Str_clone(loc_str);
    Array_set(_va_Array_96, &hoisted__U32_3164, hoisted__Str_3165);
    U32 hoisted__U32_3166 = 1;
    Str hoisted__Str_3167 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_96, &hoisted__U32_3166, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3167; _oa; }));
    Array *hoisted__Array_3168 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_3169 = 2;
    Str *hoisted__Str_3170 = format(hoisted__Array_3168);
    Array_set(_va_Array_96, &hoisted__U32_3169, hoisted__Str_3170);
    println(_va_Array_96);
    I64 hoisted__I64_3171 = 1;
    exit(hoisted__I64_3171);
}

void UNREACHABLE(Str * loc_str) {
    Str hoisted__Str_3180 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_3181 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3180; _oa; }));
    U32 hoisted__U32_3182 = 1;
    Array *_va_Array_98 = Array_new(hoisted__Type_3181, &hoisted__U32_3182);
    (void)_va_Array_98;
    Type_delete(hoisted__Type_3181, &(Bool){1});
    U32 hoisted__U32_3183 = 0;
    Str hoisted__Str_3184 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_98, &hoisted__U32_3183, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3184; _oa; }));
    panic(loc_str, _va_Array_98);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_3190 = not(DEREF(cond));
    if (hoisted__Bool_3190) {
        Str hoisted__Str_3185 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_3186 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3185; _oa; }));
        U32 hoisted__U32_3187 = 1;
        Array *_va_Array_99 = Array_new(hoisted__Type_3186, &hoisted__U32_3187);
        (void)_va_Array_99;
        Type_delete(hoisted__Type_3186, &(Bool){1});
        U32 hoisted__U32_3188 = 0;
        Str hoisted__Str_3189 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_99, &hoisted__U32_3188, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3189; _oa; }));
        panic(loc_str, _va_Array_99);
    }
    Bool hoisted__Bool_3191 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_3191; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_3214 = I64_neq(a, b);
    if (hoisted__Bool_3214) {
        Str hoisted__Str_3201 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_3202 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3201; _oa; }));
        U32 hoisted__U32_3203 = 5;
        Array *_va_Array_101 = Array_new(hoisted__Type_3202, &hoisted__U32_3203);
        (void)_va_Array_101;
        Type_delete(hoisted__Type_3202, &(Bool){1});
        U32 hoisted__U32_3204 = 0;
        Str hoisted__Str_3205 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_101, &hoisted__U32_3204, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3205; _oa; }));
        U32 hoisted__U32_3206 = 1;
        Str *hoisted__Str_3207 = I64_to_str(a);
        Array_set(_va_Array_101, &hoisted__U32_3206, hoisted__Str_3207);
        U32 hoisted__U32_3208 = 2;
        Str hoisted__Str_3209 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_101, &hoisted__U32_3208, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3209; _oa; }));
        U32 hoisted__U32_3210 = 3;
        Str *hoisted__Str_3211 = I64_to_str(b);
        Array_set(_va_Array_101, &hoisted__U32_3210, hoisted__Str_3211);
        U32 hoisted__U32_3212 = 4;
        Str hoisted__Str_3213 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_101, &hoisted__U32_3212, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3213; _oa; }));
        panic(loc_str, _va_Array_101);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_3228 = Str_eq(a, b);
    Bool hoisted__Bool_3229 = not(hoisted__Bool_3228);
    if (hoisted__Bool_3229) {
        Str hoisted__Str_3215 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_3216 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3215; _oa; }));
        U32 hoisted__U32_3217 = 5;
        Array *_va_Array_102 = Array_new(hoisted__Type_3216, &hoisted__U32_3217);
        (void)_va_Array_102;
        Type_delete(hoisted__Type_3216, &(Bool){1});
        U32 hoisted__U32_3218 = 0;
        Str hoisted__Str_3219 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_102, &hoisted__U32_3218, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3219; _oa; }));
        U32 hoisted__U32_3220 = 1;
        Str *hoisted__Str_3221 = Str_clone(a);
        Array_set(_va_Array_102, &hoisted__U32_3220, hoisted__Str_3221);
        U32 hoisted__U32_3222 = 2;
        Str hoisted__Str_3223 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_102, &hoisted__U32_3222, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3223; _oa; }));
        U32 hoisted__U32_3224 = 3;
        Str *hoisted__Str_3225 = Str_clone(b);
        Array_set(_va_Array_102, &hoisted__U32_3224, hoisted__Str_3225);
        U32 hoisted__U32_3226 = 4;
        Str hoisted__Str_3227 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_102, &hoisted__U32_3226, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3227; _oa; }));
        panic(loc_str, _va_Array_102);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_3230 = parts;
        (void)_fc_Array_3230;
        (void)_fc_Array_3230;
        U32 _fi_USize_3230 = 0;
        (void)_fi_USize_3230;
        while (1) {
            U32 hoisted__U32_3232; { U32 *_hp = (U32 *)Array_len(_fc_Array_3230); hoisted__U32_3232 = *_hp; free(_hp); }
            Bool _wcond_Bool_3231 = U32_lt(&_fi_USize_3230, &hoisted__U32_3232);
            (void)_wcond_Bool_3231;
            if (_wcond_Bool_3231) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_3230, &_fi_USize_3230);
            U32 hoisted__U32_3233 = 1;
            U32 hoisted__U32_3234 = U32_add(_fi_USize_3230, hoisted__U32_3233);
            _fi_USize_3230 = hoisted__U32_3234;
            print_single(s);
        }
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_3425 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3426 = 3;
    assert_eq(&hoisted__Str_3425, &result, &hoisted__I64_3426);
    Str_delete(&hoisted__Str_3425, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_3433 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3434 = 15;
    assert_eq(&hoisted__Str_3433, &result, &hoisted__I64_3434);
    Str_delete(&hoisted__Str_3433, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_3441 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3442 = 26;
    assert_eq(&hoisted__Str_3441, &result, &hoisted__I64_3442);
    Str_delete(&hoisted__Str_3441, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3445 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3446 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3445, &result, &hoisted__Str_3446);
    Str_delete(&hoisted__Str_3445, &(Bool){0});
    Str_delete(&hoisted__Str_3446, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3777 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3777, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_3777, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_3778 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3778, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_3778, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_3780 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3781 = 8;
    assert_eq(&hoisted__Str_3780, &result, &hoisted__I64_3781);
    Str_delete(&hoisted__Str_3780, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_3784 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3785 = 1;
    Bool_delete(assert(&hoisted__Str_3784, &hoisted__Bool_3785), &(Bool){1});
    Str_delete(&hoisted__Str_3784, &(Bool){0});
    Str hoisted__Str_3789 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3790 = 1;
    Bool_delete(assert(&hoisted__Str_3789, &hoisted__Bool_3790), &(Bool){1});
    Str_delete(&hoisted__Str_3789, &(Bool){0});
}

CfVec2 * CfVec2_magic(void) {
    I64 hoisted__I64_3792 = 42;
    I64 hoisted__I64_3793 = 99;
    CfVec2 hoisted__CfVec2_3794 = (CfVec2){.x = hoisted__I64_3792, .y = hoisted__I64_3793};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3794; return _r; }
}

CfVec2 * CfVec2_at(I64 * x, I64 * y) {
    CfVec2 hoisted__CfVec2_3795 = (CfVec2){.x = DEREF(x), .y = DEREF(y)};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3795; return _r; }
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_3796 = (CfVec2){.x = self->x, .y = self->y};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3796; return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_3797 = 16;
    return hoisted__U32_3797;
}

void test_struct_fold_simple(void) {
    CfVec2 *v = CfVec2_magic();
    Str hoisted__Str_3798 = (Str){.c_str = (void *)"test/constfold.til:122:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3799 = 42;
    assert_eq(&hoisted__Str_3798, &v->x, &hoisted__I64_3799);
    Str_delete(&hoisted__Str_3798, &(Bool){0});
    Str hoisted__Str_3800 = (Str){.c_str = (void *)"test/constfold.til:123:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3801 = 99;
    assert_eq(&hoisted__Str_3800, &v->y, &hoisted__I64_3801);
    Str_delete(&hoisted__Str_3800, &(Bool){0});
    CfVec2_delete(v, &(Bool){1});
}

void test_struct_fold_values(void) {
    I64 hoisted__I64_3802 = 10;
    I64 hoisted__I64_3803 = 20;
    CfVec2 *p = CfVec2_at(&hoisted__I64_3802, &hoisted__I64_3803);
    Str hoisted__Str_3804 = (Str){.c_str = (void *)"test/constfold.til:129:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3805 = 10;
    assert_eq(&hoisted__Str_3804, &p->x, &hoisted__I64_3805);
    Str_delete(&hoisted__Str_3804, &(Bool){0});
    Str hoisted__Str_3806 = (Str){.c_str = (void *)"test/constfold.til:130:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3807 = 20;
    assert_eq(&hoisted__Str_3806, &p->y, &hoisted__I64_3807);
    Str_delete(&hoisted__Str_3806, &(Bool){0});
    CfVec2_delete(p, &(Bool){1});
}

CfRect * CfRect_sample(void) {
    I64 hoisted__I64_3808 = 5;
    I64 hoisted__I64_3809 = 10;
    I64 hoisted__I64_3810 = 100;
    I64 hoisted__I64_3811 = 200;
    CfRect hoisted__CfRect_3812 = (CfRect){.top_left = (CfVec2){.x = hoisted__I64_3808, .y = hoisted__I64_3809}, .bottom_right = (CfVec2){.x = hoisted__I64_3810, .y = hoisted__I64_3811}};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_3812; return _r; }
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_3813 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_3813; return _r; }
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_3814 = 32;
    return hoisted__U32_3814;
}

void test_struct_fold_nested(void) {
    CfRect *r = CfRect_sample();
    Str hoisted__Str_3815 = (Str){.c_str = (void *)"test/constfold.til:146:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3816 = 5;
    assert_eq(&hoisted__Str_3815, &r->top_left.x, &hoisted__I64_3816);
    Str_delete(&hoisted__Str_3815, &(Bool){0});
    Str hoisted__Str_3817 = (Str){.c_str = (void *)"test/constfold.til:147:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3818 = 10;
    assert_eq(&hoisted__Str_3817, &r->top_left.y, &hoisted__I64_3818);
    Str_delete(&hoisted__Str_3817, &(Bool){0});
    Str hoisted__Str_3819 = (Str){.c_str = (void *)"test/constfold.til:148:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3820 = 100;
    assert_eq(&hoisted__Str_3819, &r->bottom_right.x, &hoisted__I64_3820);
    Str_delete(&hoisted__Str_3819, &(Bool){0});
    Str hoisted__Str_3821 = (Str){.c_str = (void *)"test/constfold.til:149:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3822 = 200;
    assert_eq(&hoisted__Str_3821, &r->bottom_right.y, &hoisted__I64_3822);
    Str_delete(&hoisted__Str_3821, &(Bool){0});
    CfRect_delete(r, &(Bool){1});
}

Color *Color_Red() {
    Color *r = malloc(sizeof(Color));
    *r = (Color){ .tag = Color_TAG_Red };
    return r;
}
Color *Color_Green() {
    Color *r = malloc(sizeof(Color));
    *r = (Color){ .tag = Color_TAG_Green };
    return r;
}
Color *Color_Blue() {
    Color *r = malloc(sizeof(Color));
    *r = (Color){ .tag = Color_TAG_Blue };
    return r;
}
Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_3827 = is(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3827) {
        Bool hoisted__Bool_3824 = is(other, &(Color){.tag = Color_TAG_Red});
        return hoisted__Bool_3824;
    }
    Bool hoisted__Bool_3828 = is(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3828) {
        Bool hoisted__Bool_3825 = is(other, &(Color){.tag = Color_TAG_Green});
        return hoisted__Bool_3825;
    }
    Bool hoisted__Bool_3829 = is(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3829) {
        Bool hoisted__Bool_3826 = is(other, &(Color){.tag = Color_TAG_Blue});
        return hoisted__Bool_3826;
    }
    Bool hoisted__Bool_3830 = 0;
    return hoisted__Bool_3830;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_3838 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3838) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
    }
    Bool hoisted__Bool_3839 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3839) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green; return _r; }
    }
    Bool hoisted__Bool_3840 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3840) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue; return _r; }
    }
    Str hoisted__Str_3841 = (Str){.c_str = (void *)"Color.clone:154:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_3841);
    Str_delete(&hoisted__Str_3841, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_3842 = 4;
    return hoisted__U32_3842;
}


void test_enum_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Str hoisted__Str_3843 = (Str){.c_str = (void *)"test/constfold.til:159:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3844 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    Bool_delete(assert(&hoisted__Str_3843, &hoisted__Bool_3844), &(Bool){1});
    Str_delete(&hoisted__Str_3843, &(Bool){0});
    Bool hoisted__Bool_3846 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_3847 = (Str){.c_str = (void *)"test/constfold.til:160:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3848 = not(hoisted__Bool_3846);
    Bool_delete(assert(&hoisted__Str_3847, &hoisted__Bool_3848), &(Bool){1});
    Str_delete(&hoisted__Str_3847, &(Bool){0});
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
Token *Token_Name(Str * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Name;
    r->data.Name = *val;
    free(val);
    return r;
}
Token *Token_Eof() {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Eof;
    return r;
}
Bool Token_is(Token * self, Token * other) {
    Bool hoisted__Bool_3850 = is(self, other);
    return hoisted__Bool_3850;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_3868 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3868) {
        I64 *hoisted__I64_3864 = get_payload(self);
        Bool hoisted__Bool_3865 = 0;
        I64_delete(hoisted__I64_3864, &hoisted__Bool_3865);
    }
    Bool hoisted__Bool_3869 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3869) {
        Str *hoisted__Str_3866 = get_payload(self);
        Bool hoisted__Bool_3867 = 0;
        Str_delete(hoisted__Str_3866, &hoisted__Bool_3867);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_3898 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3898) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_3895 = Token_Num(_clone_payload_Num_0);
        return hoisted__Token_3895;
    }
    Bool hoisted__Bool_3899 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3899) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_3896 = Str_clone(_clone_payload_Name_1);
        Token *hoisted__Token_3897 = Token_Name(hoisted__Str_3896);
        return hoisted__Token_3897;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof; return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_3900 = 24;
    return hoisted__U32_3900;
}


void test_enum_payload_fold(void) {
    I64 hoisted__I64_3901 = 42;
    Token *t = Token_Num(&hoisted__I64_3901);
    Str hoisted__Str_3902 = (Str){.c_str = (void *)"test/constfold.til:168:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3903 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    Bool_delete(assert(&hoisted__Str_3902, &hoisted__Bool_3903), &(Bool){1});
    Str_delete(&hoisted__Str_3902, &(Bool){0});
    Bool hoisted__Bool_3905 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_3906 = (Str){.c_str = (void *)"test/constfold.til:169:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3907 = not(hoisted__Bool_3905);
    Bool_delete(assert(&hoisted__Str_3906, &hoisted__Bool_3907), &(Bool){1});
    Str_delete(&hoisted__Str_3906, &(Bool){0});
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
void *I8_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I8_cmp(*(I8 *)_a0, *(I8 *)_a1); return _r;
}
void *I8_clone_dyn(void *_a0) {
    I8 *_r = malloc(sizeof(I8)); *_r = I8_clone(_a0); return _r;
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
void *Primitive_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Primitive_eq(_a0, _a1); return _r;
}
void *Primitive_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Primitive_size(); return _r;
}
void *Type_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Type_size(); return _r;
}
void *Array_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Array_size(); return _r;
}
void *CfVec2_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = CfVec2_size(); return _r;
}
void *CfRect_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = CfRect_size(); return _r;
}
void *Color_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Color_eq(_a0, _a1); return _r;
}
void *Color_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Color_size(); return _r;
}
void *Token_is_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Token_is(_a0, _a1); return _r;
}
void *Token_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Token_size(); return _r;
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
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I8_delete;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I8_size;
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
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Primitive_eq_dyn;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Primitive_delete;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Primitive_clone;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Primitive_size_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Unknown", 7ULL) == 0) return (void*)Type_Unknown;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "None", 4ULL) == 0) return (void*)Type_None;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "I64", 3ULL) == 0) return (void*)Type_I64;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "U8", 2ULL) == 0) return (void*)Type_U8;
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
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "I8", 2ULL) == 0) return (void*)Type_I8;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "Primitive", 9ULL) == 0) return (void*)Type_Primitive;
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
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "magic", 5ULL) == 0) return (void*)CfVec2_magic;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "at", 2ULL) == 0) return (void*)CfVec2_at;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)CfVec2_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)CfVec2_delete;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)CfVec2_size_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "sample", 6ULL) == 0) return (void*)CfRect_sample;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)CfRect_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)CfRect_delete;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)CfRect_size_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Color_eq_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Color_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Color_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Color_size_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Num", 3ULL) == 0) return (void*)Token_Num;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Name", 4ULL) == 0) return (void*)Token_Name;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Eof", 3ULL) == 0) return (void*)Token_Eof;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "is", 2ULL) == 0) return (void*)Token_is_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Token_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Token_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Token_size_dyn;
    fprintf(stderr, "dyn_fn: unknown %s.%s\n", (char*)type_name->c_str, (char*)method->c_str);
    exit(1);
}

U32 dyn_size_of(Str *type_name) {
    (void)type_name;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return 8;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return sizeof(U64);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return sizeof(U32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return sizeof(I32);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) return sizeof(I8);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return sizeof(U8);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return sizeof(Str);
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return sizeof(Dynamic);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) return sizeof(I64);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) return sizeof(Bool);
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) return sizeof(Primitive);
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) return sizeof(Type);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) return sizeof(Array);
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) return sizeof(CfVec2);
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) return sizeof(CfRect);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) return sizeof(Color);
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) return sizeof(Token);
    fprintf(stderr, "dyn_size_of: unknown type %.*s\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *dyn_type_to_str(Type *type) {
    switch (type->tag) {
    case Type_TAG_Unknown: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_None: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_I64: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_U8: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_I32: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_U32: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_U64: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_F32: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Bool: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Struct: return Str_clone(&type->data.Struct);
    case Type_TAG_StructDef: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Enum: return Str_clone(&type->data.Enum);
    case Type_TAG_EnumDef: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_FuncDef: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_FuncPtr: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Dynamic: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Custom: return Str_clone(&type->data.Custom);
    case Type_TAG_I8: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Primitive:
        switch (type->data.Primitive.tag) {
        case Primitive_TAG_I16: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        }
        break;
    default: break;
    }
    return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
}

int main(void) {
    I64 hoisted__I64_952 = -1;
    CAP_LIT = I64_to_usize(hoisted__I64_952);
    I64 hoisted__I64_953 = -2;
    CAP_VIEW = I64_to_usize(hoisted__I64_953);
    __til_docs_blob__ = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
    (void)__til_docs_blob__;
    __til_info_blob__ = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
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
    test_fold_variable();
    fprintf(stderr, "  pass: %s\n", "test_fold_variable");
    test_loc_folded();
    fprintf(stderr, "  pass: %s\n", "test_loc_folded");
    test_struct_fold_simple();
    fprintf(stderr, "  pass: %s\n", "test_struct_fold_simple");
    test_struct_fold_values();
    fprintf(stderr, "  pass: %s\n", "test_struct_fold_values");
    test_struct_fold_nested();
    fprintf(stderr, "  pass: %s\n", "test_struct_fold_nested");
    test_enum_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_fold");
    test_enum_payload_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_payload_fold");
    fprintf(stderr, "12/12 tests passed\n");
    return 0;
}
