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
    I64 hoisted__I64_27 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_27; return _r; }
}

Str * U32_to_str(U32 * val) {
    I64 hoisted__I64_42 = U32_to_i64(DEREF(val));
    Str *hoisted__Str_43 = I64_to_str(&hoisted__I64_42);
    return hoisted__Str_43;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_44 = 1;
    U32 hoisted__U32_45 = U32_add(DEREF(self), hoisted__U32_44);
    *self = hoisted__U32_45;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_46 = 1;
    U32 hoisted__U32_47 = U32_sub(DEREF(self), hoisted__U32_46);
    *self = hoisted__U32_47;
}

void U32_delete(U32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U32_size(void) {
    I64 hoisted__I64_55 = 4;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_55; return _r; }
}

Bool U32_lt(U32 * a, U32 * b) {
    I64 hoisted__I64_56 = 0;
    I64 hoisted__I64_57 = 1;
    I64 hoisted__I64_58 = U32_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_59 = I64_sub(hoisted__I64_56, hoisted__I64_57);
    Bool hoisted__Bool_60 = I64_eq(hoisted__I64_58, hoisted__I64_59);
    return hoisted__Bool_60;
}

Bool U32_gt(U32 * a, U32 * b) {
    I64 hoisted__I64_61 = U32_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_62 = 1;
    Bool hoisted__Bool_63 = I64_eq(hoisted__I64_61, hoisted__I64_62);
    return hoisted__Bool_63;
}

Bool U32_lte(U32 * a, U32 * b) {
    Bool hoisted__Bool_66 = U32_gt(a, b);
    Bool hoisted__Bool_67 = not(hoisted__Bool_66);
    return hoisted__Bool_67;
}

Bool U32_gte(U32 * a, U32 * b) {
    Bool hoisted__Bool_68 = U32_lt(a, b);
    Bool hoisted__Bool_69 = not(hoisted__Bool_68);
    return hoisted__Bool_69;
}

void I32_delete(I32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I32_size(void) {
    I64 hoisted__I64_95 = 4;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_95; return _r; }
}

void I8_delete(I8 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I8_size(void) {
    I64 hoisted__I64_137 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_137; return _r; }
}

void U8_delete(U8 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U8_size(void) {
    I64 hoisted__I64_165 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_165; return _r; }
}

Str * format(Array * parts) {
    U32 total = 0;
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
            U32 hoisted__U32_476 = Str_len(s);
            U32 hoisted__U32_477 = U32_add(total, hoisted__U32_476);
            total = hoisted__U32_477;
        }
    }
    Str *out = Str_with_capacity(&total);
    {
        Array *_fc_Array_478 = parts;
        (void)_fc_Array_478;
        (void)_fc_Array_478;
        U32 _fi_USize_478 = 0;
        (void)_fi_USize_478;
        while (1) {
            U32 hoisted__U32_480; { U32 *_hp = (U32 *)Array_len(_fc_Array_478); hoisted__U32_480 = *_hp; free(_hp); }
            Bool _wcond_Bool_479 = U32_lt(&_fi_USize_478, &hoisted__U32_480);
            (void)_wcond_Bool_479;
            if (_wcond_Bool_479) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_478, &_fi_USize_478);
            U32 hoisted__U32_481 = 1;
            U32 hoisted__U32_482 = U32_add(_fi_USize_478, hoisted__U32_481);
            _fi_USize_478 = hoisted__U32_482;
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
    Bool hoisted__Bool_489 = U32_gte(i, &self->count);
    if (hoisted__Bool_489) {
        Str hoisted__Str_483 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_484 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_483; _oa; }));
        U32 hoisted__U32_485 = 1;
        Array *_va_Array_10 = Array_new(hoisted__Type_484, &hoisted__U32_485);
        (void)_va_Array_10;
        Type_delete(hoisted__Type_484, &(Bool){1});
        U32 hoisted__U32_486 = 0;
        Str hoisted__Str_487 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_10, &hoisted__U32_486, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_487; _oa; }));
        Str hoisted__Str_488 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_488, _va_Array_10);
        Str_delete(&hoisted__Str_488, &(Bool){0});
    }
    void *hoisted__v_490 = ptr_add(self->c_str, DEREF(i));
    return hoisted__v_490;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_500 = U32_lt(&b->count, &a->count);
    if (hoisted__Bool_500) {
        min_len = b->count;
    }
    {
        U32 _re_U32_492 = U32_clone(&min_len);
        (void)_re_U32_492;
        U32 _rc_U32_492 = 0;
        (void)_rc_U32_492;
        Bool hoisted__Bool_499 = U32_lte(&_rc_U32_492, &_re_U32_492);
        if (hoisted__Bool_499) {
            while (1) {
                Bool _wcond_Bool_493 = U32_lt(&_rc_U32_492, &_re_U32_492);
                (void)_wcond_Bool_493;
                if (_wcond_Bool_493) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_492);
                U32_inc(&_rc_U32_492);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_494 = 0;
                Bool hoisted__Bool_495 = I64_neq(&c, &hoisted__I64_494);
                if (hoisted__Bool_495) {
                    return c;
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_496 = U32_gt(&_rc_U32_492, &_re_U32_492);
                (void)_wcond_Bool_496;
                if (_wcond_Bool_496) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_492);
                U32_dec(&_rc_U32_492);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_497 = 0;
                Bool hoisted__Bool_498 = I64_neq(&c, &hoisted__I64_497);
                if (hoisted__Bool_498) {
                    return c;
                }
            }
        }
    }
    I64 hoisted__I64_501 = U32_cmp(a->count, b->count);
    return hoisted__I64_501;
}

Str * Str_with_capacity(U32 * n) {
    U32 hoisted__U32_503 = 1;
    U32 hoisted__U64_504 = U32_add(DEREF(n), hoisted__U32_503);
    void * buf = malloc(hoisted__U64_504);
    I32 hoisted__I32_505 = 0;
    U64 hoisted__U64_506 = 1;
    memset(buf, hoisted__I32_505, hoisted__U64_506);
    I32_delete(&hoisted__I32_505, &(Bool){0});
    I64 hoisted__I64_507 = 0;
    Str *hoisted__Str_508 = malloc(sizeof(Str));
    hoisted__Str_508->c_str = buf;
    hoisted__Str_508->count = hoisted__I64_507;
    hoisted__Str_508->cap = DEREF(n);
    return hoisted__Str_508;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_521 = U32_gte(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_521) {
        Str hoisted__Str_509 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_510 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_509; _oa; }));
        U32 hoisted__U32_511 = 1;
        Array *_va_Array_11 = Array_new(hoisted__Type_510, &hoisted__U32_511);
        (void)_va_Array_11;
        Type_delete(hoisted__Type_510, &(Bool){1});
        U32 hoisted__U32_512 = 0;
        Str hoisted__Str_513 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_11, &hoisted__U32_512, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_513; _oa; }));
        Str hoisted__Str_514 = (Str){.c_str = (void *)"./src/core/str.til:85:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_514, _va_Array_11);
        Str_delete(&hoisted__Str_514, &(Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_522 = U32_gt(&new_len, &self->cap);
    if (hoisted__Bool_522) {
        Str hoisted__Str_515 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_516 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_515; _oa; }));
        U32 hoisted__U32_517 = 1;
        Array *_va_Array_12 = Array_new(hoisted__Type_516, &hoisted__U32_517);
        (void)_va_Array_12;
        Type_delete(hoisted__Type_516, &(Bool){1});
        U32 hoisted__U32_518 = 0;
        Str hoisted__Str_519 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_12, &hoisted__U32_518, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_519; _oa; }));
        Str hoisted__Str_520 = (Str){.c_str = (void *)"./src/core/str.til:89:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_520, _va_Array_12);
        Str_delete(&hoisted__Str_520, &(Bool){0});
    }
    void *hoisted__v_523 = ptr_add(self->c_str, self->count);
    memcpy(hoisted__v_523, s->c_str, s->count);
    U32 hoisted__U32_524 = U32_clone(&new_len);
    self->count = hoisted__U32_524;
    void *hoisted__v_525 = ptr_add(self->c_str, new_len);
    I32 hoisted__I32_526 = 0;
    U64 hoisted__U64_527 = 1;
    memset(hoisted__v_525, hoisted__I32_526, hoisted__U64_527);
    I32_delete(&hoisted__I32_526, &(Bool){0});
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_528 = 1;
    U32 hoisted__U64_529 = U32_add(val->count, hoisted__U32_528);
    void * new_data = malloc(hoisted__U64_529);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_530 = ptr_add(new_data, val->count);
    I32 hoisted__I32_531 = 0;
    U64 hoisted__U64_532 = 1;
    memset(hoisted__v_530, hoisted__I32_531, hoisted__U64_532);
    I32_delete(&hoisted__I32_531, &(Bool){0});
    Str *hoisted__Str_533 = malloc(sizeof(Str));
    hoisted__Str_533->c_str = new_data;
    hoisted__Str_533->count = val->count;
    hoisted__Str_533->cap = val->count;
    return hoisted__Str_533;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool hoisted__Bool_534 = U32_lt(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_534) {
        free(self->c_str);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_599 = 0;
    Bool hoisted__Bool_600 = U32_eq(self->count, hoisted__U32_599);
    return hoisted__Bool_600;
}

U32 Str_size(void) {
    I64 hoisted__I64_891 = 16;
    return hoisted__I64_891;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_892 = Str_cmp(a, b);
    I64 hoisted__I64_893 = 0;
    Bool hoisted__Bool_894 = I64_eq(hoisted__I64_892, hoisted__I64_893);
    return hoisted__Bool_894;
}

U32 * Dynamic_size(void) {
    I64 hoisted__I64_940 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_940; return _r; }
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 * val) {
    I64 hoisted__I64_1019 = 0;
    Bool hoisted__Bool_1020 = I64_eq(DEREF(val), hoisted__I64_1019);
    if (hoisted__Bool_1020) {
        U64 hoisted__U64_983 = 2;
        void * buf = malloc(hoisted__U64_983);
        I64 hoisted__I64_984 = 48;
        U64 hoisted__U64_985 = 1;
        memcpy(buf, &hoisted__I64_984, hoisted__U64_985);
        U64 hoisted__U64_986 = 1;
        void *hoisted__v_987 = ptr_add(buf, hoisted__U64_986);
        I32 hoisted__I32_988 = 0;
        U64 hoisted__U64_989 = 1;
        memset(hoisted__v_987, hoisted__I32_988, hoisted__U64_989);
        I32_delete(&hoisted__I32_988, &(Bool){0});
        I64 hoisted__I64_990 = 1;
        I64 hoisted__I64_991 = 1;
        Str *hoisted__Str_992 = malloc(sizeof(Str));
        hoisted__Str_992->c_str = buf;
        hoisted__Str_992->count = hoisted__I64_990;
        hoisted__Str_992->cap = hoisted__I64_991;
        return hoisted__Str_992;
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_1021 = 0;
    Bool hoisted__Bool_1022 = I64_lt(val, &hoisted__I64_1021);
    if (hoisted__Bool_1022) {
        Bool hoisted__Bool_993 = 1;
        is_neg = hoisted__Bool_993;
        I64 hoisted__I64_994 = 0;
        I64 hoisted__I64_995 = I64_sub(hoisted__I64_994, DEREF(val));
        v = hoisted__I64_995;
    }
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_997 = 0;
        Bool _wcond_Bool_996 = I64_gt(&tmp, &hoisted__I64_997);
        (void)_wcond_Bool_996;
        if (_wcond_Bool_996) {
        } else {
            break;
        }
        U64 hoisted__U64_998 = 1;
        U64 hoisted__U64_999 = U64_add(ndigits, hoisted__U64_998);
        ndigits = hoisted__U64_999;
        I64 hoisted__I64_1000 = 10;
        I64 hoisted__I64_1001 = I64_div(tmp, hoisted__I64_1000);
        tmp = hoisted__I64_1001;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1002 = 1;
        U64 hoisted__U64_1003 = U64_add(total, hoisted__U64_1002);
        total = hoisted__U64_1003;
    }
    U64 hoisted__U64_1023 = 1;
    U64 hoisted__U64_1024 = U64_add(total, hoisted__U64_1023);
    void * buf = malloc(hoisted__U64_1024);
    if (is_neg) {
        I64 hoisted__I64_1004 = 45;
        U64 hoisted__U64_1005 = 1;
        memcpy(buf, &hoisted__I64_1004, hoisted__U64_1005);
    }
    U64 hoisted__U64_1025 = 1;
    U64 i = U64_sub(total, hoisted__U64_1025);
    while (1) {
        I64 hoisted__I64_1007 = 0;
        Bool _wcond_Bool_1006 = I64_gt(&v, &hoisted__I64_1007);
        (void)_wcond_Bool_1006;
        if (_wcond_Bool_1006) {
        } else {
            break;
        }
        I64 hoisted__I64_1008 = 10;
        I64 hoisted__I64_1009 = I64_mod(v, hoisted__I64_1008);
        I64 hoisted__I64_1010 = 48;
        I64 hoisted__I64_1011 = I64_add(hoisted__I64_1009, hoisted__I64_1010);
        void *hoisted__v_1012 = ptr_add(buf, i);
        U8 hoisted__U8_1013 = I64_to_u8(hoisted__I64_1011);
        U64 hoisted__U64_1014 = 1;
        memcpy(hoisted__v_1012, &hoisted__U8_1013, hoisted__U64_1014);
        U8_delete(&hoisted__U8_1013, &(Bool){0});
        I64 hoisted__I64_1015 = 10;
        I64 hoisted__I64_1016 = I64_div(v, hoisted__I64_1015);
        v = hoisted__I64_1016;
        U64 hoisted__U64_1017 = 1;
        U64 hoisted__U64_1018 = U64_sub(i, hoisted__U64_1017);
        i = hoisted__U64_1018;
    }
    void *hoisted__v_1026 = ptr_add(buf, total);
    I32 hoisted__I32_1027 = 0;
    U64 hoisted__U64_1028 = 1;
    memset(hoisted__v_1026, hoisted__I32_1027, hoisted__U64_1028);
    I32_delete(&hoisted__I32_1027, &(Bool){0});
    Str *hoisted__Str_1029 = malloc(sizeof(Str));
    hoisted__Str_1029->c_str = buf;
    hoisted__Str_1029->count = total;
    hoisted__Str_1029->cap = total;
    return hoisted__Str_1029;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 hoisted__I64_1047 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_1047; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1057 = 0;
    I64 hoisted__I64_1058 = 1;
    I64 hoisted__I64_1059 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1060 = I64_sub(hoisted__I64_1057, hoisted__I64_1058);
    Bool hoisted__Bool_1061 = I64_eq(hoisted__I64_1059, hoisted__I64_1060);
    return hoisted__Bool_1061;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1062 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1063 = 1;
    Bool hoisted__Bool_1064 = I64_eq(hoisted__I64_1062, hoisted__I64_1063);
    return hoisted__Bool_1064;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1065 = I64_eq(DEREF(a), DEREF(b));
    Bool hoisted__Bool_1066 = not(hoisted__Bool_1065);
    return hoisted__Bool_1066;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1079 = Bool_eq(DEREF(a), DEREF(b));
    if (hoisted__Bool_1079) {
        I64 hoisted__I64_1075 = 0;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1075; return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1076 = 0;
        I64 hoisted__I64_1077 = 1;
        I64 hoisted__I64_1078 = I64_sub(hoisted__I64_1076, hoisted__I64_1077);
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1078; return _r; }
    }
    I64 hoisted__I64_1080 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1080; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 hoisted__I64_1081 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_1081; return _r; }
}

Primitive *Primitive_I16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I16 };
    return r;
}
Bool Primitive_eq(Primitive * self, Primitive * other) {
    Bool hoisted__Bool_1240 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1240) {
        Bool hoisted__Bool_1239 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        return hoisted__Bool_1239;
    }
    Bool hoisted__Bool_1241 = 0;
    return hoisted__Bool_1241;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1245 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1245) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
    }
    Str hoisted__Str_1246 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_1246);
    Str_delete(&hoisted__Str_1246, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
}

U32 Primitive_size(void) {
    I64 hoisted__I64_1247 = 4;
    return hoisted__I64_1247;
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
    Bool hoisted__Bool_1306 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1306) {
        Str *hoisted__Str_1298 = get_payload(self);
        Bool hoisted__Bool_1299 = 0;
        Str_delete(hoisted__Str_1298, &hoisted__Bool_1299);
    }
    Bool hoisted__Bool_1307 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1307) {
        Str *hoisted__Str_1300 = get_payload(self);
        Bool hoisted__Bool_1301 = 0;
        Str_delete(hoisted__Str_1300, &hoisted__Bool_1301);
    }
    Bool hoisted__Bool_1308 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1308) {
        Str *hoisted__Str_1302 = get_payload(self);
        Bool hoisted__Bool_1303 = 0;
        Str_delete(hoisted__Str_1302, &hoisted__Bool_1303);
    }
    Bool hoisted__Bool_1309 = is(self, &(Type){.tag = Type_TAG_Primitive});
    if (hoisted__Bool_1309) {
        Primitive *hoisted__Primitive_1304 = get_payload(self);
        Bool hoisted__Bool_1305 = 0;
        Primitive_delete(hoisted__Primitive_1304, &hoisted__Bool_1305);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1391 = is(self, &(Type){.tag = Type_TAG_Unknown});
    if (hoisted__Bool_1391) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown; return _r; }
    }
    Bool hoisted__Bool_1392 = is(self, &(Type){.tag = Type_TAG_None});
    if (hoisted__Bool_1392) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None; return _r; }
    }
    Bool hoisted__Bool_1393 = is(self, &(Type){.tag = Type_TAG_I64});
    if (hoisted__Bool_1393) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64; return _r; }
    }
    Bool hoisted__Bool_1394 = is(self, &(Type){.tag = Type_TAG_U8});
    if (hoisted__Bool_1394) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8; return _r; }
    }
    Bool hoisted__Bool_1395 = is(self, &(Type){.tag = Type_TAG_I32});
    if (hoisted__Bool_1395) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32; return _r; }
    }
    Bool hoisted__Bool_1396 = is(self, &(Type){.tag = Type_TAG_U32});
    if (hoisted__Bool_1396) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32; return _r; }
    }
    Bool hoisted__Bool_1397 = is(self, &(Type){.tag = Type_TAG_U64});
    if (hoisted__Bool_1397) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64; return _r; }
    }
    Bool hoisted__Bool_1398 = is(self, &(Type){.tag = Type_TAG_F32});
    if (hoisted__Bool_1398) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32; return _r; }
    }
    Bool hoisted__Bool_1399 = is(self, &(Type){.tag = Type_TAG_Bool});
    if (hoisted__Bool_1399) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool; return _r; }
    }
    Bool hoisted__Bool_1400 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1400) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_1385 = Str_clone(_clone_payload_Struct_9);
        Type *hoisted__Type_1386 = Type_Struct(hoisted__Str_1385);
        return hoisted__Type_1386;
    }
    Bool hoisted__Bool_1401 = is(self, &(Type){.tag = Type_TAG_StructDef});
    if (hoisted__Bool_1401) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef; return _r; }
    }
    Bool hoisted__Bool_1402 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1402) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_1387 = Str_clone(_clone_payload_Enum_11);
        Type *hoisted__Type_1388 = Type_Enum(hoisted__Str_1387);
        return hoisted__Type_1388;
    }
    Bool hoisted__Bool_1403 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    if (hoisted__Bool_1403) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef; return _r; }
    }
    Bool hoisted__Bool_1404 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    if (hoisted__Bool_1404) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef; return _r; }
    }
    Bool hoisted__Bool_1405 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    if (hoisted__Bool_1405) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr; return _r; }
    }
    Bool hoisted__Bool_1406 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    if (hoisted__Bool_1406) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic; return _r; }
    }
    Bool hoisted__Bool_1407 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1407) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_1389 = Str_clone(_clone_payload_Custom_16);
        Type *hoisted__Type_1390 = Type_Custom(hoisted__Str_1389);
        return hoisted__Type_1390;
    }
    Bool hoisted__Bool_1408 = is(self, &(Type){.tag = Type_TAG_I8});
    if (hoisted__Bool_1408) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8; return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive *hoisted__Primitive_1409 = Primitive_clone(_clone_payload_Primitive_18);
    Type *hoisted__Type_1410 = Type_Primitive(hoisted__Primitive_1409);
    return hoisted__Type_1410;
}

U32 Type_size(void) {
    I64 hoisted__I64_1411 = 24;
    return hoisted__I64_1411;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_2855 = Str_is_empty(elem_type);
    if (hoisted__Bool_2855) {
        Str hoisted__Str_2849 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2850 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2849; _oa; }));
        U32 hoisted__U32_2851 = 1;
        Array *_va_Array_76 = Array_new(hoisted__Type_2850, &hoisted__U32_2851);
        (void)_va_Array_76;
        Type_delete(hoisted__Type_2850, &(Bool){1});
        U32 hoisted__U32_2852 = 0;
        Str hoisted__Str_2853 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_76, &hoisted__U32_2852, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2853; _oa; }));
        Str hoisted__Str_2854 = (Str){.c_str = (void *)"./src/core/array.til:23:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2854, _va_Array_76);
        Str_delete(&hoisted__Str_2854, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_2856 = calloc(DEREF(cap), elem_size);
    void * hoisted__v_2857 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    void * hoisted__v_2858 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    Array *hoisted__Array_2859 = malloc(sizeof(Array));
    hoisted__Array_2859->data = hoisted__v_2856;
    hoisted__Array_2859->cap = DEREF(cap);
    hoisted__Array_2859->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); hoisted__Array_2859->elem_type = *_ca; free(_ca); }
    hoisted__Array_2859->elem_clone = hoisted__v_2857;
    hoisted__Array_2859->elem_delete = hoisted__v_2858;
    return hoisted__Array_2859;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_2860 = Array_new_type_name(elem_type, cap);
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_2860;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    Bool hoisted__Bool_2875 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2875) {
        Str hoisted__Str_2861 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2862 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2861; _oa; }));
        U32 hoisted__U32_2863 = 5;
        Array *_va_Array_77 = Array_new(hoisted__Type_2862, &hoisted__U32_2863);
        (void)_va_Array_77;
        Type_delete(hoisted__Type_2862, &(Bool){1});
        U32 hoisted__U32_2864 = 0;
        Str hoisted__Str_2865 = (Str){.c_str = (void *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_77, &hoisted__U32_2864, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2865; _oa; }));
        U32 hoisted__U32_2866 = 1;
        Str *hoisted__Str_2867 = U32_to_str(i);
        Array_set(_va_Array_77, &hoisted__U32_2866, hoisted__Str_2867);
        U32 hoisted__U32_2868 = 2;
        Str hoisted__Str_2869 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_77, &hoisted__U32_2868, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2869; _oa; }));
        U32 hoisted__U32_2870 = 3;
        Str *hoisted__Str_2871 = U32_to_str(&self->cap);
        Array_set(_va_Array_77, &hoisted__U32_2870, hoisted__Str_2871);
        U32 hoisted__U32_2872 = 4;
        Str hoisted__Str_2873 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_77, &hoisted__U32_2872, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2873; _oa; }));
        Str hoisted__Str_2874 = (Str){.c_str = (void *)"./src/core/array.til:41:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2874, _va_Array_77);
        Str_delete(&hoisted__Str_2874, &(Bool){0});
    }
    U32 hoisted__U64_2876 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2877 = ptr_add(self->data, hoisted__U64_2876);
    return hoisted__v_2877;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_2892 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2892) {
        Str hoisted__Str_2878 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2879 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2878; _oa; }));
        U32 hoisted__U32_2880 = 5;
        Array *_va_Array_78 = Array_new(hoisted__Type_2879, &hoisted__U32_2880);
        (void)_va_Array_78;
        Type_delete(hoisted__Type_2879, &(Bool){1});
        U32 hoisted__U32_2881 = 0;
        Str hoisted__Str_2882 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_78, &hoisted__U32_2881, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2882; _oa; }));
        U32 hoisted__U32_2883 = 1;
        Str *hoisted__Str_2884 = U32_to_str(i);
        Array_set(_va_Array_78, &hoisted__U32_2883, hoisted__Str_2884);
        U32 hoisted__U32_2885 = 2;
        Str hoisted__Str_2886 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_78, &hoisted__U32_2885, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2886; _oa; }));
        U32 hoisted__U32_2887 = 3;
        Str *hoisted__Str_2888 = U32_to_str(&self->cap);
        Array_set(_va_Array_78, &hoisted__U32_2887, hoisted__Str_2888);
        U32 hoisted__U32_2889 = 4;
        Str hoisted__Str_2890 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_78, &hoisted__U32_2889, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2890; _oa; }));
        Str hoisted__Str_2891 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2891, _va_Array_78);
        Str_delete(&hoisted__Str_2891, &(Bool){0});
    }
    U32 hoisted__U64_2893 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2894 = ptr_add(self->data, hoisted__U64_2893);
    Bool hoisted__Bool_2895 = 0;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2894, &hoisted__Bool_2895);
    U32 hoisted__U64_2896 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2897 = ptr_add(self->data, hoisted__U64_2896);
    memcpy(hoisted__v_2897, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_2898 = self->cap;
        (void)_re_U32_2898;
        U32 _rc_U32_2898 = 0;
        (void)_rc_U32_2898;
        Bool hoisted__Bool_2907 = U32_lte(&_rc_U32_2898, &_re_U32_2898);
        if (hoisted__Bool_2907) {
            while (1) {
                Bool _wcond_Bool_2899 = U32_lt(&_rc_U32_2898, &_re_U32_2898);
                (void)_wcond_Bool_2899;
                if (_wcond_Bool_2899) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2898);
                U32_inc(&_rc_U32_2898);
                U32 hoisted__U64_2900 = U32_mul(i, self->elem_size);
                void *hoisted__v_2901 = ptr_add(self->data, hoisted__U64_2900);
                Bool hoisted__Bool_2902 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2901, &hoisted__Bool_2902);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2903 = U32_gt(&_rc_U32_2898, &_re_U32_2898);
                (void)_wcond_Bool_2903;
                if (_wcond_Bool_2903) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2898);
                U32_dec(&_rc_U32_2898);
                U32 hoisted__U64_2904 = U32_mul(i, self->elem_size);
                void *hoisted__v_2905 = ptr_add(self->data, hoisted__U64_2904);
                Bool hoisted__Bool_2906 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2905, &hoisted__Bool_2906);
            }
        }
    }
    free(self->data);
    Bool hoisted__Bool_2908 = 0;
    Str_delete(&self->elem_type, &hoisted__Bool_2908);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_2921 = U32_mul(self->cap, self->elem_size);
    void * new_data = malloc(hoisted__U64_2921);
    {
        U32 _re_U32_2909 = self->cap;
        (void)_re_U32_2909;
        U32 _rc_U32_2909 = 0;
        (void)_rc_U32_2909;
        Bool hoisted__Bool_2920 = U32_lte(&_rc_U32_2909, &_re_U32_2909);
        if (hoisted__Bool_2920) {
            while (1) {
                Bool _wcond_Bool_2910 = U32_lt(&_rc_U32_2909, &_re_U32_2909);
                (void)_wcond_Bool_2910;
                if (_wcond_Bool_2910) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2909);
                U32_inc(&_rc_U32_2909);
                U32 hoisted__U64_2911 = U32_mul(i, self->elem_size);
                void *hoisted__v_2912 = ptr_add(self->data, hoisted__U64_2911);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2912);
                U32 hoisted__U64_2913 = U32_mul(i, self->elem_size);
                void *hoisted__v_2914 = ptr_add(new_data, hoisted__U64_2913);
                memcpy(hoisted__v_2914, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2915 = U32_gt(&_rc_U32_2909, &_re_U32_2909);
                (void)_wcond_Bool_2915;
                if (_wcond_Bool_2915) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2909);
                U32_dec(&_rc_U32_2909);
                U32 hoisted__U64_2916 = U32_mul(i, self->elem_size);
                void *hoisted__v_2917 = ptr_add(self->data, hoisted__U64_2916);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2917);
                U32 hoisted__U64_2918 = U32_mul(i, self->elem_size);
                void *hoisted__v_2919 = ptr_add(new_data, hoisted__U64_2918);
                memcpy(hoisted__v_2919, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_2922 = malloc(sizeof(Array));
    hoisted__Array_2922->data = new_data;
    hoisted__Array_2922->cap = self->cap;
    hoisted__Array_2922->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); hoisted__Array_2922->elem_type = *_ca; free(_ca); }
    hoisted__Array_2922->elem_clone = (void *)self->elem_clone;
    hoisted__Array_2922->elem_delete = (void *)self->elem_delete;
    return hoisted__Array_2922;
}

U32 Array_size(void) {
    I64 hoisted__I64_2923 = 48;
    return hoisted__I64_2923;
}

void panic(Str * loc_str, Array * parts) {
    Str hoisted__Str_3162 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_3163 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3162; _oa; }));
    U32 hoisted__U32_3164 = 3;
    Array *_va_Array_95 = Array_new(hoisted__Type_3163, &hoisted__U32_3164);
    (void)_va_Array_95;
    Type_delete(hoisted__Type_3163, &(Bool){1});
    U32 hoisted__U32_3165 = 0;
    Str *hoisted__Str_3166 = Str_clone(loc_str);
    Array_set(_va_Array_95, &hoisted__U32_3165, hoisted__Str_3166);
    U32 hoisted__U32_3167 = 1;
    Str hoisted__Str_3168 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_95, &hoisted__U32_3167, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3168; _oa; }));
    Array *hoisted__Array_3169 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_3170 = 2;
    Str *hoisted__Str_3171 = format(hoisted__Array_3169);
    Array_set(_va_Array_95, &hoisted__U32_3170, hoisted__Str_3171);
    println(_va_Array_95);
    I64 hoisted__I64_3172 = 1;
    exit(hoisted__I64_3172);
}

void UNREACHABLE(Str * loc_str) {
    Str hoisted__Str_3181 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_3182 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3181; _oa; }));
    U32 hoisted__U32_3183 = 1;
    Array *_va_Array_97 = Array_new(hoisted__Type_3182, &hoisted__U32_3183);
    (void)_va_Array_97;
    Type_delete(hoisted__Type_3182, &(Bool){1});
    U32 hoisted__U32_3184 = 0;
    Str hoisted__Str_3185 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_97, &hoisted__U32_3184, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3185; _oa; }));
    panic(loc_str, _va_Array_97);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_3191 = not(DEREF(cond));
    if (hoisted__Bool_3191) {
        Str hoisted__Str_3186 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_3187 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3186; _oa; }));
        U32 hoisted__U32_3188 = 1;
        Array *_va_Array_98 = Array_new(hoisted__Type_3187, &hoisted__U32_3188);
        (void)_va_Array_98;
        Type_delete(hoisted__Type_3187, &(Bool){1});
        U32 hoisted__U32_3189 = 0;
        Str hoisted__Str_3190 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_98, &hoisted__U32_3189, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3190; _oa; }));
        panic(loc_str, _va_Array_98);
    }
    Bool hoisted__Bool_3192 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_3192; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_3215 = I64_neq(a, b);
    if (hoisted__Bool_3215) {
        Str hoisted__Str_3202 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_3203 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3202; _oa; }));
        U32 hoisted__U32_3204 = 5;
        Array *_va_Array_100 = Array_new(hoisted__Type_3203, &hoisted__U32_3204);
        (void)_va_Array_100;
        Type_delete(hoisted__Type_3203, &(Bool){1});
        U32 hoisted__U32_3205 = 0;
        Str hoisted__Str_3206 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_100, &hoisted__U32_3205, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3206; _oa; }));
        U32 hoisted__U32_3207 = 1;
        Str *hoisted__Str_3208 = I64_to_str(a);
        Array_set(_va_Array_100, &hoisted__U32_3207, hoisted__Str_3208);
        U32 hoisted__U32_3209 = 2;
        Str hoisted__Str_3210 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_100, &hoisted__U32_3209, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3210; _oa; }));
        U32 hoisted__U32_3211 = 3;
        Str *hoisted__Str_3212 = I64_to_str(b);
        Array_set(_va_Array_100, &hoisted__U32_3211, hoisted__Str_3212);
        U32 hoisted__U32_3213 = 4;
        Str hoisted__Str_3214 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_100, &hoisted__U32_3213, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3214; _oa; }));
        panic(loc_str, _va_Array_100);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_3229 = Str_eq(a, b);
    Bool hoisted__Bool_3230 = not(hoisted__Bool_3229);
    if (hoisted__Bool_3230) {
        Str hoisted__Str_3216 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_3217 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3216; _oa; }));
        U32 hoisted__U32_3218 = 5;
        Array *_va_Array_101 = Array_new(hoisted__Type_3217, &hoisted__U32_3218);
        (void)_va_Array_101;
        Type_delete(hoisted__Type_3217, &(Bool){1});
        U32 hoisted__U32_3219 = 0;
        Str hoisted__Str_3220 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_101, &hoisted__U32_3219, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3220; _oa; }));
        U32 hoisted__U32_3221 = 1;
        Str *hoisted__Str_3222 = Str_clone(a);
        Array_set(_va_Array_101, &hoisted__U32_3221, hoisted__Str_3222);
        U32 hoisted__U32_3223 = 2;
        Str hoisted__Str_3224 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_101, &hoisted__U32_3223, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3224; _oa; }));
        U32 hoisted__U32_3225 = 3;
        Str *hoisted__Str_3226 = Str_clone(b);
        Array_set(_va_Array_101, &hoisted__U32_3225, hoisted__Str_3226);
        U32 hoisted__U32_3227 = 4;
        Str hoisted__Str_3228 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_101, &hoisted__U32_3227, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3228; _oa; }));
        panic(loc_str, _va_Array_101);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_3231 = parts;
        (void)_fc_Array_3231;
        (void)_fc_Array_3231;
        U32 _fi_USize_3231 = 0;
        (void)_fi_USize_3231;
        while (1) {
            U32 hoisted__U32_3233; { U32 *_hp = (U32 *)Array_len(_fc_Array_3231); hoisted__U32_3233 = *_hp; free(_hp); }
            Bool _wcond_Bool_3232 = U32_lt(&_fi_USize_3231, &hoisted__U32_3233);
            (void)_wcond_Bool_3232;
            if (_wcond_Bool_3232) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_3231, &_fi_USize_3231);
            U32 hoisted__U32_3234 = 1;
            U32 hoisted__U32_3235 = U32_add(_fi_USize_3231, hoisted__U32_3234);
            _fi_USize_3231 = hoisted__U32_3235;
            print_single(s);
        }
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_3428 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3429 = 3;
    assert_eq(&hoisted__Str_3428, &result, &hoisted__I64_3429);
    Str_delete(&hoisted__Str_3428, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_3436 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3437 = 15;
    assert_eq(&hoisted__Str_3436, &result, &hoisted__I64_3437);
    Str_delete(&hoisted__Str_3436, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_3444 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3445 = 26;
    assert_eq(&hoisted__Str_3444, &result, &hoisted__I64_3445);
    Str_delete(&hoisted__Str_3444, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3448 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3449 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3448, &result, &hoisted__Str_3449);
    Str_delete(&hoisted__Str_3448, &(Bool){0});
    Str_delete(&hoisted__Str_3449, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3780 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3780, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_3780, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_3781 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3781, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_3781, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_3783 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3784 = 8;
    assert_eq(&hoisted__Str_3783, &result, &hoisted__I64_3784);
    Str_delete(&hoisted__Str_3783, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_3787 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3788 = 1;
    Bool_delete(assert(&hoisted__Str_3787, &hoisted__Bool_3788), &(Bool){1});
    Str_delete(&hoisted__Str_3787, &(Bool){0});
    Str hoisted__Str_3792 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3793 = 1;
    Bool_delete(assert(&hoisted__Str_3792, &hoisted__Bool_3793), &(Bool){1});
    Str_delete(&hoisted__Str_3792, &(Bool){0});
}

CfVec2 * CfVec2_magic(void) {
    I64 hoisted__I64_3795 = 42;
    I64 hoisted__I64_3796 = 99;
    CfVec2 hoisted__CfVec2_3797 = (CfVec2){.x = hoisted__I64_3795, .y = hoisted__I64_3796};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3797; return _r; }
}

CfVec2 * CfVec2_at(I64 * x, I64 * y) {
    CfVec2 hoisted__CfVec2_3798 = (CfVec2){.x = DEREF(x), .y = DEREF(y)};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3798; return _r; }
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_3799 = (CfVec2){.x = self->x, .y = self->y};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3799; return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    I64 hoisted__I64_3800 = 16;
    return hoisted__I64_3800;
}

void test_struct_fold_simple(void) {
    CfVec2 *v = CfVec2_magic();
    Str hoisted__Str_3801 = (Str){.c_str = (void *)"test/constfold.til:122:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3802 = 42;
    assert_eq(&hoisted__Str_3801, &v->x, &hoisted__I64_3802);
    Str_delete(&hoisted__Str_3801, &(Bool){0});
    Str hoisted__Str_3803 = (Str){.c_str = (void *)"test/constfold.til:123:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3804 = 99;
    assert_eq(&hoisted__Str_3803, &v->y, &hoisted__I64_3804);
    Str_delete(&hoisted__Str_3803, &(Bool){0});
    CfVec2_delete(v, &(Bool){1});
}

void test_struct_fold_values(void) {
    I64 hoisted__I64_3805 = 10;
    I64 hoisted__I64_3806 = 20;
    CfVec2 *p = CfVec2_at(&hoisted__I64_3805, &hoisted__I64_3806);
    Str hoisted__Str_3807 = (Str){.c_str = (void *)"test/constfold.til:129:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3808 = 10;
    assert_eq(&hoisted__Str_3807, &p->x, &hoisted__I64_3808);
    Str_delete(&hoisted__Str_3807, &(Bool){0});
    Str hoisted__Str_3809 = (Str){.c_str = (void *)"test/constfold.til:130:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3810 = 20;
    assert_eq(&hoisted__Str_3809, &p->y, &hoisted__I64_3810);
    Str_delete(&hoisted__Str_3809, &(Bool){0});
    CfVec2_delete(p, &(Bool){1});
}

CfRect * CfRect_sample(void) {
    I64 hoisted__I64_3811 = 5;
    I64 hoisted__I64_3812 = 10;
    I64 hoisted__I64_3813 = 100;
    I64 hoisted__I64_3814 = 200;
    CfRect hoisted__CfRect_3815 = (CfRect){.top_left = (CfVec2){.x = hoisted__I64_3811, .y = hoisted__I64_3812}, .bottom_right = (CfVec2){.x = hoisted__I64_3813, .y = hoisted__I64_3814}};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_3815; return _r; }
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_3816 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_3816; return _r; }
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    I64 hoisted__I64_3817 = 32;
    return hoisted__I64_3817;
}

void test_struct_fold_nested(void) {
    CfRect *r = CfRect_sample();
    Str hoisted__Str_3818 = (Str){.c_str = (void *)"test/constfold.til:146:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3819 = 5;
    assert_eq(&hoisted__Str_3818, &r->top_left.x, &hoisted__I64_3819);
    Str_delete(&hoisted__Str_3818, &(Bool){0});
    Str hoisted__Str_3820 = (Str){.c_str = (void *)"test/constfold.til:147:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3821 = 10;
    assert_eq(&hoisted__Str_3820, &r->top_left.y, &hoisted__I64_3821);
    Str_delete(&hoisted__Str_3820, &(Bool){0});
    Str hoisted__Str_3822 = (Str){.c_str = (void *)"test/constfold.til:148:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3823 = 100;
    assert_eq(&hoisted__Str_3822, &r->bottom_right.x, &hoisted__I64_3823);
    Str_delete(&hoisted__Str_3822, &(Bool){0});
    Str hoisted__Str_3824 = (Str){.c_str = (void *)"test/constfold.til:149:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3825 = 200;
    assert_eq(&hoisted__Str_3824, &r->bottom_right.y, &hoisted__I64_3825);
    Str_delete(&hoisted__Str_3824, &(Bool){0});
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
    Bool hoisted__Bool_3830 = is(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3830) {
        Bool hoisted__Bool_3827 = is(other, &(Color){.tag = Color_TAG_Red});
        return hoisted__Bool_3827;
    }
    Bool hoisted__Bool_3831 = is(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3831) {
        Bool hoisted__Bool_3828 = is(other, &(Color){.tag = Color_TAG_Green});
        return hoisted__Bool_3828;
    }
    Bool hoisted__Bool_3832 = is(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3832) {
        Bool hoisted__Bool_3829 = is(other, &(Color){.tag = Color_TAG_Blue});
        return hoisted__Bool_3829;
    }
    Bool hoisted__Bool_3833 = 0;
    return hoisted__Bool_3833;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_3841 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3841) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
    }
    Bool hoisted__Bool_3842 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3842) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green; return _r; }
    }
    Bool hoisted__Bool_3843 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3843) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue; return _r; }
    }
    Str hoisted__Str_3844 = (Str){.c_str = (void *)"Color.clone:154:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_3844);
    Str_delete(&hoisted__Str_3844, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
}

U32 Color_size(void) {
    I64 hoisted__I64_3845 = 4;
    return hoisted__I64_3845;
}


void test_enum_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Str hoisted__Str_3846 = (Str){.c_str = (void *)"test/constfold.til:159:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3847 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    Bool_delete(assert(&hoisted__Str_3846, &hoisted__Bool_3847), &(Bool){1});
    Str_delete(&hoisted__Str_3846, &(Bool){0});
    Bool hoisted__Bool_3849 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_3850 = (Str){.c_str = (void *)"test/constfold.til:160:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3851 = not(hoisted__Bool_3849);
    Bool_delete(assert(&hoisted__Str_3850, &hoisted__Bool_3851), &(Bool){1});
    Str_delete(&hoisted__Str_3850, &(Bool){0});
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
    Bool hoisted__Bool_3853 = is(self, other);
    return hoisted__Bool_3853;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_3871 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3871) {
        I64 *hoisted__I64_3867 = get_payload(self);
        Bool hoisted__Bool_3868 = 0;
        I64_delete(hoisted__I64_3867, &hoisted__Bool_3868);
    }
    Bool hoisted__Bool_3872 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3872) {
        Str *hoisted__Str_3869 = get_payload(self);
        Bool hoisted__Bool_3870 = 0;
        Str_delete(hoisted__Str_3869, &hoisted__Bool_3870);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_3901 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3901) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_3898 = Token_Num(_clone_payload_Num_0);
        return hoisted__Token_3898;
    }
    Bool hoisted__Bool_3902 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3902) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_3899 = Str_clone(_clone_payload_Name_1);
        Token *hoisted__Token_3900 = Token_Name(hoisted__Str_3899);
        return hoisted__Token_3900;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof; return _r; }
}

U32 Token_size(void) {
    I64 hoisted__I64_3903 = 24;
    return hoisted__I64_3903;
}


void test_enum_payload_fold(void) {
    I64 hoisted__I64_3904 = 42;
    Token *t = Token_Num(&hoisted__I64_3904);
    Str hoisted__Str_3905 = (Str){.c_str = (void *)"test/constfold.til:168:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3906 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    Bool_delete(assert(&hoisted__Str_3905, &hoisted__Bool_3906), &(Bool){1});
    Str_delete(&hoisted__Str_3905, &(Bool){0});
    Bool hoisted__Bool_3908 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_3909 = (Str){.c_str = (void *)"test/constfold.til:169:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3910 = not(hoisted__Bool_3908);
    Bool_delete(assert(&hoisted__Str_3909, &hoisted__Bool_3910), &(Bool){1});
    Str_delete(&hoisted__Str_3909, &(Bool){0});
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
    I64 hoisted__I64_934 = 0;
    I64 hoisted__I64_935 = 1;
    I64 hoisted__I64_936 = I64_sub(hoisted__I64_934, hoisted__I64_935);
    CAP_LIT = I64_to_usize(hoisted__I64_936);
    I64 hoisted__I64_937 = 0;
    I64 hoisted__I64_938 = 2;
    I64 hoisted__I64_939 = I64_sub(hoisted__I64_937, hoisted__I64_938);
    CAP_VIEW = I64_to_usize(hoisted__I64_939);
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
