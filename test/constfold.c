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
        Array *_fc_Array_457 = parts;
        (void)_fc_Array_457;
        (void)_fc_Array_457;
        U32 _fi_USize_457 = 0;
        (void)_fi_USize_457;
        while (1) {
            U32 hoisted__U32_459; { U32 *_hp = (U32 *)Array_len(_fc_Array_457); hoisted__U32_459 = *_hp; free(_hp); }
            Bool _wcond_Bool_458 = U32_lt(&_fi_USize_457, &hoisted__U32_459);
            (void)_wcond_Bool_458;
            if (_wcond_Bool_458) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_457, &_fi_USize_457);
            U32 hoisted__U32_460 = 1;
            U32 hoisted__U32_461 = U32_add(_fi_USize_457, hoisted__U32_460);
            _fi_USize_457 = hoisted__U32_461;
            U32 hoisted__U32_462 = Str_len(s);
            U32 hoisted__U32_463 = U32_add(total, hoisted__U32_462);
            total = hoisted__U32_463;
        }
    }
    Str *out = Str_with_capacity(&total);
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
    Bool hoisted__Bool_475 = U32_gte(i, &self->count);
    if (hoisted__Bool_475) {
        Str hoisted__Str_469 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_470 = Type_Struct(&hoisted__Str_469);
        Str_delete(&hoisted__Str_469, &(Bool){0});
        U32 hoisted__U32_471 = 1;
        Array *_va_Array_10 = Array_new(hoisted__Type_470, &hoisted__U32_471);
        (void)_va_Array_10;
        Type_delete(hoisted__Type_470, &(Bool){1});
        U32 hoisted__U32_472 = 0;
        Str hoisted__Str_473 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_10, &hoisted__U32_472, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_473; _oa; }));
        Str hoisted__Str_474 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_474, _va_Array_10);
        Str_delete(&hoisted__Str_474, &(Bool){0});
    }
    void *hoisted__v_476 = ptr_add(self->c_str, DEREF(i));
    return hoisted__v_476;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_486 = U32_lt(&b->count, &a->count);
    if (hoisted__Bool_486) {
        min_len = b->count;
    }
    {
        U32 _re_U32_478 = U32_clone(&min_len);
        (void)_re_U32_478;
        U32 _rc_U32_478 = 0;
        (void)_rc_U32_478;
        Bool hoisted__Bool_485 = U32_lte(&_rc_U32_478, &_re_U32_478);
        if (hoisted__Bool_485) {
            while (1) {
                Bool _wcond_Bool_479 = U32_lt(&_rc_U32_478, &_re_U32_478);
                (void)_wcond_Bool_479;
                if (_wcond_Bool_479) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_478);
                U32_inc(&_rc_U32_478);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_480 = 0;
                Bool hoisted__Bool_481 = I64_neq(&c, &hoisted__I64_480);
                if (hoisted__Bool_481) {
                    return c;
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_482 = U32_gt(&_rc_U32_478, &_re_U32_478);
                (void)_wcond_Bool_482;
                if (_wcond_Bool_482) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_478);
                U32_dec(&_rc_U32_478);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_483 = 0;
                Bool hoisted__Bool_484 = I64_neq(&c, &hoisted__I64_483);
                if (hoisted__Bool_484) {
                    return c;
                }
            }
        }
    }
    I64 hoisted__I64_487 = U32_cmp(a->count, b->count);
    return hoisted__I64_487;
}

Str * Str_with_capacity(U32 * n) {
    U32 hoisted__U32_489 = 1;
    U32 hoisted__U64_490 = U32_add(DEREF(n), hoisted__U32_489);
    void * buf = malloc(hoisted__U64_490);
    I32 hoisted__I32_491 = 0;
    U64 hoisted__U64_492 = 1;
    memset(buf, hoisted__I32_491, hoisted__U64_492);
    I32_delete(&hoisted__I32_491, &(Bool){0});
    I64 hoisted__I64_493 = 0;
    Str *hoisted__Str_494 = malloc(sizeof(Str));
    hoisted__Str_494->c_str = buf;
    hoisted__Str_494->count = hoisted__I64_493;
    hoisted__Str_494->cap = DEREF(n);
    return hoisted__Str_494;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_507 = U32_gte(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_507) {
        Str hoisted__Str_495 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_496 = Type_Struct(&hoisted__Str_495);
        Str_delete(&hoisted__Str_495, &(Bool){0});
        U32 hoisted__U32_497 = 1;
        Array *_va_Array_11 = Array_new(hoisted__Type_496, &hoisted__U32_497);
        (void)_va_Array_11;
        Type_delete(hoisted__Type_496, &(Bool){1});
        U32 hoisted__U32_498 = 0;
        Str hoisted__Str_499 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_11, &hoisted__U32_498, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_499; _oa; }));
        Str hoisted__Str_500 = (Str){.c_str = (void *)"./src/core/str.til:85:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_500, _va_Array_11);
        Str_delete(&hoisted__Str_500, &(Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_508 = U32_gt(&new_len, &self->cap);
    if (hoisted__Bool_508) {
        Str hoisted__Str_501 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_502 = Type_Struct(&hoisted__Str_501);
        Str_delete(&hoisted__Str_501, &(Bool){0});
        U32 hoisted__U32_503 = 1;
        Array *_va_Array_12 = Array_new(hoisted__Type_502, &hoisted__U32_503);
        (void)_va_Array_12;
        Type_delete(hoisted__Type_502, &(Bool){1});
        U32 hoisted__U32_504 = 0;
        Str hoisted__Str_505 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_12, &hoisted__U32_504, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_505; _oa; }));
        Str hoisted__Str_506 = (Str){.c_str = (void *)"./src/core/str.til:89:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_506, _va_Array_12);
        Str_delete(&hoisted__Str_506, &(Bool){0});
    }
    void *hoisted__v_509 = ptr_add(self->c_str, self->count);
    memcpy(hoisted__v_509, s->c_str, s->count);
    U32 hoisted__U32_510 = U32_clone(&new_len);
    self->count = hoisted__U32_510;
    void *hoisted__v_511 = ptr_add(self->c_str, new_len);
    I32 hoisted__I32_512 = 0;
    U64 hoisted__U64_513 = 1;
    memset(hoisted__v_511, hoisted__I32_512, hoisted__U64_513);
    I32_delete(&hoisted__I32_512, &(Bool){0});
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_514 = 1;
    U32 hoisted__U64_515 = U32_add(val->count, hoisted__U32_514);
    void * new_data = malloc(hoisted__U64_515);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_516 = ptr_add(new_data, val->count);
    I32 hoisted__I32_517 = 0;
    U64 hoisted__U64_518 = 1;
    memset(hoisted__v_516, hoisted__I32_517, hoisted__U64_518);
    I32_delete(&hoisted__I32_517, &(Bool){0});
    Str *hoisted__Str_519 = malloc(sizeof(Str));
    hoisted__Str_519->c_str = new_data;
    hoisted__Str_519->count = val->count;
    hoisted__Str_519->cap = val->count;
    return hoisted__Str_519;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool hoisted__Bool_520 = U32_lt(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_520) {
        free(self->c_str);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_586 = 0;
    Bool hoisted__Bool_587 = U32_eq(self->count, hoisted__U32_586);
    return hoisted__Bool_587;
}

U32 Str_size(void) {
    I64 hoisted__I64_878 = 16;
    return hoisted__I64_878;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_879 = Str_cmp(a, b);
    I64 hoisted__I64_880 = 0;
    Bool hoisted__Bool_881 = I64_eq(hoisted__I64_879, hoisted__I64_880);
    return hoisted__Bool_881;
}

U32 * Dynamic_size(void) {
    I64 hoisted__I64_927 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_927; return _r; }
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 * val) {
    I64 hoisted__I64_1006 = 0;
    Bool hoisted__Bool_1007 = I64_eq(DEREF(val), hoisted__I64_1006);
    if (hoisted__Bool_1007) {
        U64 hoisted__U64_970 = 2;
        void * buf = malloc(hoisted__U64_970);
        I64 hoisted__I64_971 = 48;
        U64 hoisted__U64_972 = 1;
        memcpy(buf, &hoisted__I64_971, hoisted__U64_972);
        U64 hoisted__U64_973 = 1;
        void *hoisted__v_974 = ptr_add(buf, hoisted__U64_973);
        I32 hoisted__I32_975 = 0;
        U64 hoisted__U64_976 = 1;
        memset(hoisted__v_974, hoisted__I32_975, hoisted__U64_976);
        I32_delete(&hoisted__I32_975, &(Bool){0});
        I64 hoisted__I64_977 = 1;
        I64 hoisted__I64_978 = 1;
        Str *hoisted__Str_979 = malloc(sizeof(Str));
        hoisted__Str_979->c_str = buf;
        hoisted__Str_979->count = hoisted__I64_977;
        hoisted__Str_979->cap = hoisted__I64_978;
        return hoisted__Str_979;
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_1008 = 0;
    Bool hoisted__Bool_1009 = I64_lt(val, &hoisted__I64_1008);
    if (hoisted__Bool_1009) {
        Bool hoisted__Bool_980 = 1;
        is_neg = hoisted__Bool_980;
        I64 hoisted__I64_981 = 0;
        I64 hoisted__I64_982 = I64_sub(hoisted__I64_981, DEREF(val));
        v = hoisted__I64_982;
    }
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_984 = 0;
        Bool _wcond_Bool_983 = I64_gt(&tmp, &hoisted__I64_984);
        (void)_wcond_Bool_983;
        if (_wcond_Bool_983) {
        } else {
            break;
        }
        U64 hoisted__U64_985 = 1;
        U64 hoisted__U64_986 = U64_add(ndigits, hoisted__U64_985);
        ndigits = hoisted__U64_986;
        I64 hoisted__I64_987 = 10;
        I64 hoisted__I64_988 = I64_div(tmp, hoisted__I64_987);
        tmp = hoisted__I64_988;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_989 = 1;
        U64 hoisted__U64_990 = U64_add(total, hoisted__U64_989);
        total = hoisted__U64_990;
    }
    U64 hoisted__U64_1010 = 1;
    U64 hoisted__U64_1011 = U64_add(total, hoisted__U64_1010);
    void * buf = malloc(hoisted__U64_1011);
    if (is_neg) {
        I64 hoisted__I64_991 = 45;
        U64 hoisted__U64_992 = 1;
        memcpy(buf, &hoisted__I64_991, hoisted__U64_992);
    }
    U64 hoisted__U64_1012 = 1;
    U64 i = U64_sub(total, hoisted__U64_1012);
    while (1) {
        I64 hoisted__I64_994 = 0;
        Bool _wcond_Bool_993 = I64_gt(&v, &hoisted__I64_994);
        (void)_wcond_Bool_993;
        if (_wcond_Bool_993) {
        } else {
            break;
        }
        I64 hoisted__I64_995 = 10;
        I64 hoisted__I64_996 = I64_mod(v, hoisted__I64_995);
        I64 hoisted__I64_997 = 48;
        I64 hoisted__I64_998 = I64_add(hoisted__I64_996, hoisted__I64_997);
        void *hoisted__v_999 = ptr_add(buf, i);
        U8 hoisted__U8_1000 = I64_to_u8(hoisted__I64_998);
        U64 hoisted__U64_1001 = 1;
        memcpy(hoisted__v_999, &hoisted__U8_1000, hoisted__U64_1001);
        U8_delete(&hoisted__U8_1000, &(Bool){0});
        I64 hoisted__I64_1002 = 10;
        I64 hoisted__I64_1003 = I64_div(v, hoisted__I64_1002);
        v = hoisted__I64_1003;
        U64 hoisted__U64_1004 = 1;
        U64 hoisted__U64_1005 = U64_sub(i, hoisted__U64_1004);
        i = hoisted__U64_1005;
    }
    void *hoisted__v_1013 = ptr_add(buf, total);
    I32 hoisted__I32_1014 = 0;
    U64 hoisted__U64_1015 = 1;
    memset(hoisted__v_1013, hoisted__I32_1014, hoisted__U64_1015);
    I32_delete(&hoisted__I32_1014, &(Bool){0});
    Str *hoisted__Str_1016 = malloc(sizeof(Str));
    hoisted__Str_1016->c_str = buf;
    hoisted__Str_1016->count = total;
    hoisted__Str_1016->cap = total;
    return hoisted__Str_1016;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 hoisted__I64_1034 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_1034; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1044 = 0;
    I64 hoisted__I64_1045 = 1;
    I64 hoisted__I64_1046 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1047 = I64_sub(hoisted__I64_1044, hoisted__I64_1045);
    Bool hoisted__Bool_1048 = I64_eq(hoisted__I64_1046, hoisted__I64_1047);
    return hoisted__Bool_1048;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1049 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1050 = 1;
    Bool hoisted__Bool_1051 = I64_eq(hoisted__I64_1049, hoisted__I64_1050);
    return hoisted__Bool_1051;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1052 = I64_eq(DEREF(a), DEREF(b));
    Bool hoisted__Bool_1053 = not(hoisted__Bool_1052);
    return hoisted__Bool_1053;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1066 = Bool_eq(DEREF(a), DEREF(b));
    if (hoisted__Bool_1066) {
        I64 hoisted__I64_1062 = 0;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1062; return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1063 = 0;
        I64 hoisted__I64_1064 = 1;
        I64 hoisted__I64_1065 = I64_sub(hoisted__I64_1063, hoisted__I64_1064);
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1065; return _r; }
    }
    I64 hoisted__I64_1067 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1067; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 hoisted__I64_1068 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_1068; return _r; }
}

Primitive *Primitive_I16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I16 };
    return r;
}
Bool Primitive_eq(Primitive * self, Primitive * other) {
    Bool hoisted__Bool_1227 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1227) {
        Bool hoisted__Bool_1226 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        return hoisted__Bool_1226;
    }
    Bool hoisted__Bool_1228 = 0;
    return hoisted__Bool_1228;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1232 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1232) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
    }
    Str hoisted__Str_1233 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_1233);
    Str_delete(&hoisted__Str_1233, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
}

U32 Primitive_size(void) {
    I64 hoisted__I64_1234 = 4;
    return hoisted__I64_1234;
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
Type *Type_I8() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_I8;
    return r;
}
Type *Type_Primitive(Primitive * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Primitive;
    { Primitive * _tmp = Primitive_clone(val); r->data.Primitive = *_tmp; free(_tmp); }
    return r;
}
void Type_delete(Type * self, Bool * call_free) {
    Bool hoisted__Bool_1293 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1293) {
        Str *hoisted__Str_1285 = get_payload(self);
        Bool hoisted__Bool_1286 = 0;
        Str_delete(hoisted__Str_1285, &hoisted__Bool_1286);
    }
    Bool hoisted__Bool_1294 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1294) {
        Str *hoisted__Str_1287 = get_payload(self);
        Bool hoisted__Bool_1288 = 0;
        Str_delete(hoisted__Str_1287, &hoisted__Bool_1288);
    }
    Bool hoisted__Bool_1295 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1295) {
        Str *hoisted__Str_1289 = get_payload(self);
        Bool hoisted__Bool_1290 = 0;
        Str_delete(hoisted__Str_1289, &hoisted__Bool_1290);
    }
    Bool hoisted__Bool_1296 = is(self, &(Type){.tag = Type_TAG_Primitive});
    if (hoisted__Bool_1296) {
        Primitive *hoisted__Primitive_1291 = get_payload(self);
        Bool hoisted__Bool_1292 = 0;
        Primitive_delete(hoisted__Primitive_1291, &hoisted__Bool_1292);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1375 = is(self, &(Type){.tag = Type_TAG_Unknown});
    if (hoisted__Bool_1375) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown; return _r; }
    }
    Bool hoisted__Bool_1376 = is(self, &(Type){.tag = Type_TAG_None});
    if (hoisted__Bool_1376) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None; return _r; }
    }
    Bool hoisted__Bool_1377 = is(self, &(Type){.tag = Type_TAG_I64});
    if (hoisted__Bool_1377) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64; return _r; }
    }
    Bool hoisted__Bool_1378 = is(self, &(Type){.tag = Type_TAG_U8});
    if (hoisted__Bool_1378) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8; return _r; }
    }
    Bool hoisted__Bool_1379 = is(self, &(Type){.tag = Type_TAG_I32});
    if (hoisted__Bool_1379) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32; return _r; }
    }
    Bool hoisted__Bool_1380 = is(self, &(Type){.tag = Type_TAG_U32});
    if (hoisted__Bool_1380) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32; return _r; }
    }
    Bool hoisted__Bool_1381 = is(self, &(Type){.tag = Type_TAG_U64});
    if (hoisted__Bool_1381) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64; return _r; }
    }
    Bool hoisted__Bool_1382 = is(self, &(Type){.tag = Type_TAG_F32});
    if (hoisted__Bool_1382) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32; return _r; }
    }
    Bool hoisted__Bool_1383 = is(self, &(Type){.tag = Type_TAG_Bool});
    if (hoisted__Bool_1383) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool; return _r; }
    }
    Bool hoisted__Bool_1384 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1384) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Type *hoisted__Type_1372 = Type_Struct(_clone_payload_Struct_9);
        return hoisted__Type_1372;
    }
    Bool hoisted__Bool_1385 = is(self, &(Type){.tag = Type_TAG_StructDef});
    if (hoisted__Bool_1385) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef; return _r; }
    }
    Bool hoisted__Bool_1386 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1386) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Type *hoisted__Type_1373 = Type_Enum(_clone_payload_Enum_11);
        return hoisted__Type_1373;
    }
    Bool hoisted__Bool_1387 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    if (hoisted__Bool_1387) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef; return _r; }
    }
    Bool hoisted__Bool_1388 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    if (hoisted__Bool_1388) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef; return _r; }
    }
    Bool hoisted__Bool_1389 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    if (hoisted__Bool_1389) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr; return _r; }
    }
    Bool hoisted__Bool_1390 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    if (hoisted__Bool_1390) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic; return _r; }
    }
    Bool hoisted__Bool_1391 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1391) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Type *hoisted__Type_1374 = Type_Custom(_clone_payload_Custom_16);
        return hoisted__Type_1374;
    }
    Bool hoisted__Bool_1392 = is(self, &(Type){.tag = Type_TAG_I8});
    if (hoisted__Bool_1392) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8; return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Type *hoisted__Type_1393 = Type_Primitive(_clone_payload_Primitive_18);
    return hoisted__Type_1393;
}

U32 Type_size(void) {
    I64 hoisted__I64_1394 = 24;
    return hoisted__I64_1394;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_2603 = Str_is_empty(elem_type);
    if (hoisted__Bool_2603) {
        Str hoisted__Str_2597 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2598 = Type_Struct(&hoisted__Str_2597);
        Str_delete(&hoisted__Str_2597, &(Bool){0});
        U32 hoisted__U32_2599 = 1;
        Array *_va_Array_75 = Array_new(hoisted__Type_2598, &hoisted__U32_2599);
        (void)_va_Array_75;
        Type_delete(hoisted__Type_2598, &(Bool){1});
        U32 hoisted__U32_2600 = 0;
        Str hoisted__Str_2601 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_75, &hoisted__U32_2600, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2601; _oa; }));
        Str hoisted__Str_2602 = (Str){.c_str = (void *)"./src/core/array.til:23:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2602, _va_Array_75);
        Str_delete(&hoisted__Str_2602, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_2604 = calloc(DEREF(cap), elem_size);
    void * hoisted__v_2605 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    void * hoisted__v_2606 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    Array *hoisted__Array_2607 = malloc(sizeof(Array));
    hoisted__Array_2607->data = hoisted__v_2604;
    hoisted__Array_2607->cap = DEREF(cap);
    hoisted__Array_2607->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); hoisted__Array_2607->elem_type = *_ca; free(_ca); }
    hoisted__Array_2607->elem_clone = hoisted__v_2605;
    hoisted__Array_2607->elem_delete = hoisted__v_2606;
    return hoisted__Array_2607;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_2608 = Array_new_type_name(elem_type, cap);
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_2608;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    Bool hoisted__Bool_2623 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2623) {
        Str hoisted__Str_2609 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2610 = Type_Struct(&hoisted__Str_2609);
        Str_delete(&hoisted__Str_2609, &(Bool){0});
        U32 hoisted__U32_2611 = 5;
        Array *_va_Array_76 = Array_new(hoisted__Type_2610, &hoisted__U32_2611);
        (void)_va_Array_76;
        Type_delete(hoisted__Type_2610, &(Bool){1});
        U32 hoisted__U32_2612 = 0;
        Str hoisted__Str_2613 = (Str){.c_str = (void *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_76, &hoisted__U32_2612, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2613; _oa; }));
        U32 hoisted__U32_2614 = 1;
        Str *hoisted__Str_2615 = U32_to_str(i);
        Array_set(_va_Array_76, &hoisted__U32_2614, hoisted__Str_2615);
        U32 hoisted__U32_2616 = 2;
        Str hoisted__Str_2617 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_76, &hoisted__U32_2616, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2617; _oa; }));
        U32 hoisted__U32_2618 = 3;
        Str *hoisted__Str_2619 = U32_to_str(&self->cap);
        Array_set(_va_Array_76, &hoisted__U32_2618, hoisted__Str_2619);
        U32 hoisted__U32_2620 = 4;
        Str hoisted__Str_2621 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_76, &hoisted__U32_2620, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2621; _oa; }));
        Str hoisted__Str_2622 = (Str){.c_str = (void *)"./src/core/array.til:41:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2622, _va_Array_76);
        Str_delete(&hoisted__Str_2622, &(Bool){0});
    }
    U32 hoisted__U64_2624 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2625 = ptr_add(self->data, hoisted__U64_2624);
    return hoisted__v_2625;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_2640 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2640) {
        Str hoisted__Str_2626 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2627 = Type_Struct(&hoisted__Str_2626);
        Str_delete(&hoisted__Str_2626, &(Bool){0});
        U32 hoisted__U32_2628 = 5;
        Array *_va_Array_77 = Array_new(hoisted__Type_2627, &hoisted__U32_2628);
        (void)_va_Array_77;
        Type_delete(hoisted__Type_2627, &(Bool){1});
        U32 hoisted__U32_2629 = 0;
        Str hoisted__Str_2630 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_77, &hoisted__U32_2629, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2630; _oa; }));
        U32 hoisted__U32_2631 = 1;
        Str *hoisted__Str_2632 = U32_to_str(i);
        Array_set(_va_Array_77, &hoisted__U32_2631, hoisted__Str_2632);
        U32 hoisted__U32_2633 = 2;
        Str hoisted__Str_2634 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_77, &hoisted__U32_2633, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2634; _oa; }));
        U32 hoisted__U32_2635 = 3;
        Str *hoisted__Str_2636 = U32_to_str(&self->cap);
        Array_set(_va_Array_77, &hoisted__U32_2635, hoisted__Str_2636);
        U32 hoisted__U32_2637 = 4;
        Str hoisted__Str_2638 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_77, &hoisted__U32_2637, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2638; _oa; }));
        Str hoisted__Str_2639 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2639, _va_Array_77);
        Str_delete(&hoisted__Str_2639, &(Bool){0});
    }
    U32 hoisted__U64_2641 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2642 = ptr_add(self->data, hoisted__U64_2641);
    Bool hoisted__Bool_2643 = 0;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2642, &hoisted__Bool_2643);
    U32 hoisted__U64_2644 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2645 = ptr_add(self->data, hoisted__U64_2644);
    memcpy(hoisted__v_2645, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_2646 = self->cap;
        (void)_re_U32_2646;
        U32 _rc_U32_2646 = 0;
        (void)_rc_U32_2646;
        Bool hoisted__Bool_2655 = U32_lte(&_rc_U32_2646, &_re_U32_2646);
        if (hoisted__Bool_2655) {
            while (1) {
                Bool _wcond_Bool_2647 = U32_lt(&_rc_U32_2646, &_re_U32_2646);
                (void)_wcond_Bool_2647;
                if (_wcond_Bool_2647) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2646);
                U32_inc(&_rc_U32_2646);
                U32 hoisted__U64_2648 = U32_mul(i, self->elem_size);
                void *hoisted__v_2649 = ptr_add(self->data, hoisted__U64_2648);
                Bool hoisted__Bool_2650 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2649, &hoisted__Bool_2650);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2651 = U32_gt(&_rc_U32_2646, &_re_U32_2646);
                (void)_wcond_Bool_2651;
                if (_wcond_Bool_2651) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2646);
                U32_dec(&_rc_U32_2646);
                U32 hoisted__U64_2652 = U32_mul(i, self->elem_size);
                void *hoisted__v_2653 = ptr_add(self->data, hoisted__U64_2652);
                Bool hoisted__Bool_2654 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2653, &hoisted__Bool_2654);
            }
        }
    }
    free(self->data);
    Bool hoisted__Bool_2656 = 0;
    Str_delete(&self->elem_type, &hoisted__Bool_2656);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_2669 = U32_mul(self->cap, self->elem_size);
    void * new_data = malloc(hoisted__U64_2669);
    {
        U32 _re_U32_2657 = self->cap;
        (void)_re_U32_2657;
        U32 _rc_U32_2657 = 0;
        (void)_rc_U32_2657;
        Bool hoisted__Bool_2668 = U32_lte(&_rc_U32_2657, &_re_U32_2657);
        if (hoisted__Bool_2668) {
            while (1) {
                Bool _wcond_Bool_2658 = U32_lt(&_rc_U32_2657, &_re_U32_2657);
                (void)_wcond_Bool_2658;
                if (_wcond_Bool_2658) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2657);
                U32_inc(&_rc_U32_2657);
                U32 hoisted__U64_2659 = U32_mul(i, self->elem_size);
                void *hoisted__v_2660 = ptr_add(self->data, hoisted__U64_2659);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2660);
                U32 hoisted__U64_2661 = U32_mul(i, self->elem_size);
                void *hoisted__v_2662 = ptr_add(new_data, hoisted__U64_2661);
                memcpy(hoisted__v_2662, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2663 = U32_gt(&_rc_U32_2657, &_re_U32_2657);
                (void)_wcond_Bool_2663;
                if (_wcond_Bool_2663) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2657);
                U32_dec(&_rc_U32_2657);
                U32 hoisted__U64_2664 = U32_mul(i, self->elem_size);
                void *hoisted__v_2665 = ptr_add(self->data, hoisted__U64_2664);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2665);
                U32 hoisted__U64_2666 = U32_mul(i, self->elem_size);
                void *hoisted__v_2667 = ptr_add(new_data, hoisted__U64_2666);
                memcpy(hoisted__v_2667, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_2670 = malloc(sizeof(Array));
    hoisted__Array_2670->data = new_data;
    hoisted__Array_2670->cap = self->cap;
    hoisted__Array_2670->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); hoisted__Array_2670->elem_type = *_ca; free(_ca); }
    hoisted__Array_2670->elem_clone = (void *)self->elem_clone;
    hoisted__Array_2670->elem_delete = (void *)self->elem_delete;
    return hoisted__Array_2670;
}

U32 Array_size(void) {
    I64 hoisted__I64_2671 = 48;
    return hoisted__I64_2671;
}

void panic(Str * loc_str, Array * parts) {
    Str hoisted__Str_2910 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_2911 = Type_Struct(&hoisted__Str_2910);
    Str_delete(&hoisted__Str_2910, &(Bool){0});
    U32 hoisted__U32_2912 = 3;
    Array *_va_Array_94 = Array_new(hoisted__Type_2911, &hoisted__U32_2912);
    (void)_va_Array_94;
    Type_delete(hoisted__Type_2911, &(Bool){1});
    U32 hoisted__U32_2913 = 0;
    Str *hoisted__Str_2914 = Str_clone(loc_str);
    Array_set(_va_Array_94, &hoisted__U32_2913, hoisted__Str_2914);
    U32 hoisted__U32_2915 = 1;
    Str hoisted__Str_2916 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_94, &hoisted__U32_2915, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2916; _oa; }));
    Array *hoisted__Array_2917 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_2918 = 2;
    Str *hoisted__Str_2919 = format(hoisted__Array_2917);
    Array_set(_va_Array_94, &hoisted__U32_2918, hoisted__Str_2919);
    println(_va_Array_94);
    I64 hoisted__I64_2920 = 1;
    exit(hoisted__I64_2920);
}

void UNREACHABLE(Str * loc_str) {
    Str hoisted__Str_2929 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_2930 = Type_Struct(&hoisted__Str_2929);
    Str_delete(&hoisted__Str_2929, &(Bool){0});
    U32 hoisted__U32_2931 = 1;
    Array *_va_Array_96 = Array_new(hoisted__Type_2930, &hoisted__U32_2931);
    (void)_va_Array_96;
    Type_delete(hoisted__Type_2930, &(Bool){1});
    U32 hoisted__U32_2932 = 0;
    Str hoisted__Str_2933 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_96, &hoisted__U32_2932, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2933; _oa; }));
    panic(loc_str, _va_Array_96);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_2939 = not(DEREF(cond));
    if (hoisted__Bool_2939) {
        Str hoisted__Str_2934 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2935 = Type_Struct(&hoisted__Str_2934);
        Str_delete(&hoisted__Str_2934, &(Bool){0});
        U32 hoisted__U32_2936 = 1;
        Array *_va_Array_97 = Array_new(hoisted__Type_2935, &hoisted__U32_2936);
        (void)_va_Array_97;
        Type_delete(hoisted__Type_2935, &(Bool){1});
        U32 hoisted__U32_2937 = 0;
        Str hoisted__Str_2938 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_97, &hoisted__U32_2937, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2938; _oa; }));
        panic(loc_str, _va_Array_97);
    }
    Bool hoisted__Bool_2940 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_2940; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_2963 = I64_neq(a, b);
    if (hoisted__Bool_2963) {
        Str hoisted__Str_2950 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2951 = Type_Struct(&hoisted__Str_2950);
        Str_delete(&hoisted__Str_2950, &(Bool){0});
        U32 hoisted__U32_2952 = 5;
        Array *_va_Array_99 = Array_new(hoisted__Type_2951, &hoisted__U32_2952);
        (void)_va_Array_99;
        Type_delete(hoisted__Type_2951, &(Bool){1});
        U32 hoisted__U32_2953 = 0;
        Str hoisted__Str_2954 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_99, &hoisted__U32_2953, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2954; _oa; }));
        U32 hoisted__U32_2955 = 1;
        Str *hoisted__Str_2956 = I64_to_str(a);
        Array_set(_va_Array_99, &hoisted__U32_2955, hoisted__Str_2956);
        U32 hoisted__U32_2957 = 2;
        Str hoisted__Str_2958 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_99, &hoisted__U32_2957, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2958; _oa; }));
        U32 hoisted__U32_2959 = 3;
        Str *hoisted__Str_2960 = I64_to_str(b);
        Array_set(_va_Array_99, &hoisted__U32_2959, hoisted__Str_2960);
        U32 hoisted__U32_2961 = 4;
        Str hoisted__Str_2962 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_99, &hoisted__U32_2961, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2962; _oa; }));
        panic(loc_str, _va_Array_99);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_2977 = Str_eq(a, b);
    Bool hoisted__Bool_2978 = not(hoisted__Bool_2977);
    if (hoisted__Bool_2978) {
        Str hoisted__Str_2964 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2965 = Type_Struct(&hoisted__Str_2964);
        Str_delete(&hoisted__Str_2964, &(Bool){0});
        U32 hoisted__U32_2966 = 5;
        Array *_va_Array_100 = Array_new(hoisted__Type_2965, &hoisted__U32_2966);
        (void)_va_Array_100;
        Type_delete(hoisted__Type_2965, &(Bool){1});
        U32 hoisted__U32_2967 = 0;
        Str hoisted__Str_2968 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_100, &hoisted__U32_2967, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2968; _oa; }));
        U32 hoisted__U32_2969 = 1;
        Str *hoisted__Str_2970 = Str_clone(a);
        Array_set(_va_Array_100, &hoisted__U32_2969, hoisted__Str_2970);
        U32 hoisted__U32_2971 = 2;
        Str hoisted__Str_2972 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_100, &hoisted__U32_2971, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2972; _oa; }));
        U32 hoisted__U32_2973 = 3;
        Str *hoisted__Str_2974 = Str_clone(b);
        Array_set(_va_Array_100, &hoisted__U32_2973, hoisted__Str_2974);
        U32 hoisted__U32_2975 = 4;
        Str hoisted__Str_2976 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_100, &hoisted__U32_2975, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2976; _oa; }));
        panic(loc_str, _va_Array_100);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_2979 = parts;
        (void)_fc_Array_2979;
        (void)_fc_Array_2979;
        U32 _fi_USize_2979 = 0;
        (void)_fi_USize_2979;
        while (1) {
            U32 hoisted__U32_2981; { U32 *_hp = (U32 *)Array_len(_fc_Array_2979); hoisted__U32_2981 = *_hp; free(_hp); }
            Bool _wcond_Bool_2980 = U32_lt(&_fi_USize_2979, &hoisted__U32_2981);
            (void)_wcond_Bool_2980;
            if (_wcond_Bool_2980) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_2979, &_fi_USize_2979);
            U32 hoisted__U32_2982 = 1;
            U32 hoisted__U32_2983 = U32_add(_fi_USize_2979, hoisted__U32_2982);
            _fi_USize_2979 = hoisted__U32_2983;
            print_single(s);
        }
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_3175 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3176 = 3;
    assert_eq(&hoisted__Str_3175, &result, &hoisted__I64_3176);
    Str_delete(&hoisted__Str_3175, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_3183 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3184 = 15;
    assert_eq(&hoisted__Str_3183, &result, &hoisted__I64_3184);
    Str_delete(&hoisted__Str_3183, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_3191 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3192 = 26;
    assert_eq(&hoisted__Str_3191, &result, &hoisted__I64_3192);
    Str_delete(&hoisted__Str_3191, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3195 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3196 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3195, &result, &hoisted__Str_3196);
    Str_delete(&hoisted__Str_3195, &(Bool){0});
    Str_delete(&hoisted__Str_3196, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3527 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3527, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_3527, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_3528 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3528, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_3528, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_3530 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3531 = 8;
    assert_eq(&hoisted__Str_3530, &result, &hoisted__I64_3531);
    Str_delete(&hoisted__Str_3530, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_3534 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3535 = 1;
    Bool_delete(assert(&hoisted__Str_3534, &hoisted__Bool_3535), &(Bool){1});
    Str_delete(&hoisted__Str_3534, &(Bool){0});
    Str hoisted__Str_3539 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3540 = 1;
    Bool_delete(assert(&hoisted__Str_3539, &hoisted__Bool_3540), &(Bool){1});
    Str_delete(&hoisted__Str_3539, &(Bool){0});
}

CfVec2 * CfVec2_magic(void) {
    I64 hoisted__I64_3542 = 42;
    I64 hoisted__I64_3543 = 99;
    CfVec2 hoisted__CfVec2_3544 = (CfVec2){.x = hoisted__I64_3542, .y = hoisted__I64_3543};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3544; return _r; }
}

CfVec2 * CfVec2_at(I64 * x, I64 * y) {
    CfVec2 hoisted__CfVec2_3545 = (CfVec2){.x = DEREF(x), .y = DEREF(y)};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3545; return _r; }
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_3546 = (CfVec2){.x = self->x, .y = self->y};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3546; return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    I64 hoisted__I64_3547 = 16;
    return hoisted__I64_3547;
}

void test_struct_fold_simple(void) {
    CfVec2 *v = CfVec2_magic();
    Str hoisted__Str_3548 = (Str){.c_str = (void *)"test/constfold.til:122:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3549 = 42;
    assert_eq(&hoisted__Str_3548, &v->x, &hoisted__I64_3549);
    Str_delete(&hoisted__Str_3548, &(Bool){0});
    Str hoisted__Str_3550 = (Str){.c_str = (void *)"test/constfold.til:123:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3551 = 99;
    assert_eq(&hoisted__Str_3550, &v->y, &hoisted__I64_3551);
    Str_delete(&hoisted__Str_3550, &(Bool){0});
    CfVec2_delete(v, &(Bool){1});
}

void test_struct_fold_values(void) {
    I64 hoisted__I64_3552 = 10;
    I64 hoisted__I64_3553 = 20;
    CfVec2 *p = CfVec2_at(&hoisted__I64_3552, &hoisted__I64_3553);
    Str hoisted__Str_3554 = (Str){.c_str = (void *)"test/constfold.til:129:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3555 = 10;
    assert_eq(&hoisted__Str_3554, &p->x, &hoisted__I64_3555);
    Str_delete(&hoisted__Str_3554, &(Bool){0});
    Str hoisted__Str_3556 = (Str){.c_str = (void *)"test/constfold.til:130:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3557 = 20;
    assert_eq(&hoisted__Str_3556, &p->y, &hoisted__I64_3557);
    Str_delete(&hoisted__Str_3556, &(Bool){0});
    CfVec2_delete(p, &(Bool){1});
}

CfRect * CfRect_sample(void) {
    I64 hoisted__I64_3558 = 5;
    I64 hoisted__I64_3559 = 10;
    I64 hoisted__I64_3560 = 100;
    I64 hoisted__I64_3561 = 200;
    CfRect hoisted__CfRect_3562 = (CfRect){.top_left = (CfVec2){.x = hoisted__I64_3558, .y = hoisted__I64_3559}, .bottom_right = (CfVec2){.x = hoisted__I64_3560, .y = hoisted__I64_3561}};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_3562; return _r; }
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_3563 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_3563; return _r; }
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    I64 hoisted__I64_3564 = 32;
    return hoisted__I64_3564;
}

void test_struct_fold_nested(void) {
    CfRect *r = CfRect_sample();
    Str hoisted__Str_3565 = (Str){.c_str = (void *)"test/constfold.til:146:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3566 = 5;
    assert_eq(&hoisted__Str_3565, &r->top_left.x, &hoisted__I64_3566);
    Str_delete(&hoisted__Str_3565, &(Bool){0});
    Str hoisted__Str_3567 = (Str){.c_str = (void *)"test/constfold.til:147:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3568 = 10;
    assert_eq(&hoisted__Str_3567, &r->top_left.y, &hoisted__I64_3568);
    Str_delete(&hoisted__Str_3567, &(Bool){0});
    Str hoisted__Str_3569 = (Str){.c_str = (void *)"test/constfold.til:148:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3570 = 100;
    assert_eq(&hoisted__Str_3569, &r->bottom_right.x, &hoisted__I64_3570);
    Str_delete(&hoisted__Str_3569, &(Bool){0});
    Str hoisted__Str_3571 = (Str){.c_str = (void *)"test/constfold.til:149:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3572 = 200;
    assert_eq(&hoisted__Str_3571, &r->bottom_right.y, &hoisted__I64_3572);
    Str_delete(&hoisted__Str_3571, &(Bool){0});
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
    Bool hoisted__Bool_3577 = is(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3577) {
        Bool hoisted__Bool_3574 = is(other, &(Color){.tag = Color_TAG_Red});
        return hoisted__Bool_3574;
    }
    Bool hoisted__Bool_3578 = is(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3578) {
        Bool hoisted__Bool_3575 = is(other, &(Color){.tag = Color_TAG_Green});
        return hoisted__Bool_3575;
    }
    Bool hoisted__Bool_3579 = is(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3579) {
        Bool hoisted__Bool_3576 = is(other, &(Color){.tag = Color_TAG_Blue});
        return hoisted__Bool_3576;
    }
    Bool hoisted__Bool_3580 = 0;
    return hoisted__Bool_3580;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_3588 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3588) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
    }
    Bool hoisted__Bool_3589 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3589) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green; return _r; }
    }
    Bool hoisted__Bool_3590 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3590) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue; return _r; }
    }
    Str hoisted__Str_3591 = (Str){.c_str = (void *)"Color.clone:154:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_3591);
    Str_delete(&hoisted__Str_3591, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
}

U32 Color_size(void) {
    I64 hoisted__I64_3592 = 4;
    return hoisted__I64_3592;
}


void test_enum_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Str hoisted__Str_3593 = (Str){.c_str = (void *)"test/constfold.til:159:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3594 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    Bool_delete(assert(&hoisted__Str_3593, &hoisted__Bool_3594), &(Bool){1});
    Str_delete(&hoisted__Str_3593, &(Bool){0});
    Bool hoisted__Bool_3596 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_3597 = (Str){.c_str = (void *)"test/constfold.til:160:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3598 = not(hoisted__Bool_3596);
    Bool_delete(assert(&hoisted__Str_3597, &hoisted__Bool_3598), &(Bool){1});
    Str_delete(&hoisted__Str_3597, &(Bool){0});
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
    { Str * _tmp = Str_clone(val); r->data.Name = *_tmp; free(_tmp); }
    return r;
}
Token *Token_Eof() {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Eof;
    return r;
}
Bool Token_is(Token * self, Token * other) {
    Bool hoisted__Bool_3600 = is(self, other);
    return hoisted__Bool_3600;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_3618 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3618) {
        I64 *hoisted__I64_3614 = get_payload(self);
        Bool hoisted__Bool_3615 = 0;
        I64_delete(hoisted__I64_3614, &hoisted__Bool_3615);
    }
    Bool hoisted__Bool_3619 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3619) {
        Str *hoisted__Str_3616 = get_payload(self);
        Bool hoisted__Bool_3617 = 0;
        Str_delete(hoisted__Str_3616, &hoisted__Bool_3617);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_3647 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3647) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_3645 = Token_Num(_clone_payload_Num_0);
        return hoisted__Token_3645;
    }
    Bool hoisted__Bool_3648 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3648) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Token *hoisted__Token_3646 = Token_Name(_clone_payload_Name_1);
        return hoisted__Token_3646;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof; return _r; }
}

U32 Token_size(void) {
    I64 hoisted__I64_3649 = 24;
    return hoisted__I64_3649;
}


void test_enum_payload_fold(void) {
    I64 hoisted__I64_3650 = 42;
    Token *t = Token_Num(&hoisted__I64_3650);
    Str hoisted__Str_3651 = (Str){.c_str = (void *)"test/constfold.til:168:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3652 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    Bool_delete(assert(&hoisted__Str_3651, &hoisted__Bool_3652), &(Bool){1});
    Str_delete(&hoisted__Str_3651, &(Bool){0});
    Bool hoisted__Bool_3654 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_3655 = (Str){.c_str = (void *)"test/constfold.til:169:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3656 = not(hoisted__Bool_3654);
    Bool_delete(assert(&hoisted__Str_3655, &hoisted__Bool_3656), &(Bool){1});
    Str_delete(&hoisted__Str_3655, &(Bool){0});
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
    I64 hoisted__I64_921 = 0;
    I64 hoisted__I64_922 = 1;
    I64 hoisted__I64_923 = I64_sub(hoisted__I64_921, hoisted__I64_922);
    CAP_LIT = I64_to_usize(hoisted__I64_923);
    I64 hoisted__I64_924 = 0;
    I64 hoisted__I64_925 = 2;
    I64 hoisted__I64_926 = I64_sub(hoisted__I64_924, hoisted__I64_925);
    CAP_VIEW = I64_to_usize(hoisted__I64_926);
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
