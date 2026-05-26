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
I64 struct_field_count(Str *type_name);
Str *struct_field_name(Str *type_name, I64 *index);
I64 struct_field_is_mut(Str *type_name, I64 *index);
Str *struct_field_type(Str *type_name, I64 *index);
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
U32 ELEM_POD;
U32 ELEM_BOXED;
U32 ELEM_FN;
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
    I64 hoisted__I64_56 = U32_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_57 = -1;
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
        Array *_fc_Array_441 = parts;
        (void)_fc_Array_441;
        (void)_fc_Array_441;
        U32 _fi_USize_441 = 0;
        (void)_fi_USize_441;
        while (1) {
            U32 hoisted__U32_443; { U32 *_hp = (U32 *)Array_len(_fc_Array_441); hoisted__U32_443 = *_hp; free(_hp); }
            Bool _wcond_Bool_442 = U32_lt(&_fi_USize_441, &hoisted__U32_443);
            (void)_wcond_Bool_442;
            if (_wcond_Bool_442) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_441, &_fi_USize_441);
            U32 hoisted__U32_444 = 1;
            U32 hoisted__U32_445 = U32_add(_fi_USize_441, hoisted__U32_444);
            _fi_USize_441 = hoisted__U32_445;
            U32 hoisted__U32_446 = Str_len(s);
            U32 hoisted__U32_447 = U32_add(total, hoisted__U32_446);
            total = hoisted__U32_447;
        }
    }
    Str *out = Str_with_capacity(&total);
    {
        Array *_fc_Array_448 = parts;
        (void)_fc_Array_448;
        (void)_fc_Array_448;
        U32 _fi_USize_448 = 0;
        (void)_fi_USize_448;
        while (1) {
            U32 hoisted__U32_450; { U32 *_hp = (U32 *)Array_len(_fc_Array_448); hoisted__U32_450 = *_hp; free(_hp); }
            Bool _wcond_Bool_449 = U32_lt(&_fi_USize_448, &hoisted__U32_450);
            (void)_wcond_Bool_449;
            if (_wcond_Bool_449) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_448, &_fi_USize_448);
            U32 hoisted__U32_451 = 1;
            U32 hoisted__U32_452 = U32_add(_fi_USize_448, hoisted__U32_451);
            _fi_USize_448 = hoisted__U32_452;
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
    Bool hoisted__Bool_459 = U32_gte(i, &self->count);
    if (hoisted__Bool_459) {
        Str hoisted__Str_453 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_454 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_453; _oa; }));
        U32 hoisted__U32_455 = 1;
        Array *_va_Array_10 = Array_new(hoisted__Type_454, &hoisted__U32_455);
        (void)_va_Array_10;
        Type_delete(hoisted__Type_454, &(Bool){1});
        U32 hoisted__U32_456 = 0;
        Str hoisted__Str_457 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_10, &hoisted__U32_456, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_457; _oa; }));
        Str hoisted__Str_458 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_458, _va_Array_10);
        Str_delete(&hoisted__Str_458, &(Bool){0});
    }
    void *hoisted__v_460 = ptr_add(self->c_str, DEREF(i));
    return hoisted__v_460;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_470 = U32_lt(&b->count, &a->count);
    if (hoisted__Bool_470) {
        min_len = b->count;
    }
    {
        U32 _re_U32_462 = U32_clone(&min_len);
        (void)_re_U32_462;
        U32 _rc_U32_462 = 0;
        (void)_rc_U32_462;
        Bool hoisted__Bool_469 = U32_lte(&_rc_U32_462, &_re_U32_462);
        if (hoisted__Bool_469) {
            while (1) {
                Bool _wcond_Bool_463 = U32_lt(&_rc_U32_462, &_re_U32_462);
                (void)_wcond_Bool_463;
                if (_wcond_Bool_463) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_462);
                U32_inc(&_rc_U32_462);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_464 = 0;
                Bool hoisted__Bool_465 = I64_neq(&c, &hoisted__I64_464);
                if (hoisted__Bool_465) {
                    return c;
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_466 = U32_gt(&_rc_U32_462, &_re_U32_462);
                (void)_wcond_Bool_466;
                if (_wcond_Bool_466) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_462);
                U32_dec(&_rc_U32_462);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_467 = 0;
                Bool hoisted__Bool_468 = I64_neq(&c, &hoisted__I64_467);
                if (hoisted__Bool_468) {
                    return c;
                }
            }
        }
    }
    I64 hoisted__I64_471 = U32_cmp(a->count, b->count);
    return hoisted__I64_471;
}

Str * Str_with_capacity(U32 * n) {
    U32 hoisted__U32_473 = 1;
    U32 hoisted__U64_474 = U32_add(DEREF(n), hoisted__U32_473);
    void * buf = malloc(hoisted__U64_474);
    I32 hoisted__I32_475 = 0;
    U64 hoisted__U64_476 = 1;
    memset(buf, hoisted__I32_475, hoisted__U64_476);
    I32_delete(&hoisted__I32_475, &(Bool){0});
    I64 hoisted__I64_477 = 0;
    Str *hoisted__Str_478 = malloc(sizeof(Str));
    hoisted__Str_478->c_str = buf;
    hoisted__Str_478->count = hoisted__I64_477;
    hoisted__Str_478->cap = DEREF(n);
    return hoisted__Str_478;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_491 = U32_gte(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_491) {
        Str hoisted__Str_479 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_480 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_479; _oa; }));
        U32 hoisted__U32_481 = 1;
        Array *_va_Array_11 = Array_new(hoisted__Type_480, &hoisted__U32_481);
        (void)_va_Array_11;
        Type_delete(hoisted__Type_480, &(Bool){1});
        U32 hoisted__U32_482 = 0;
        Str hoisted__Str_483 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_11, &hoisted__U32_482, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_483; _oa; }));
        Str hoisted__Str_484 = (Str){.c_str = (void *)"./src/core/str.til:85:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_484, _va_Array_11);
        Str_delete(&hoisted__Str_484, &(Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_492 = U32_gt(&new_len, &self->cap);
    if (hoisted__Bool_492) {
        Str hoisted__Str_485 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_486 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_485; _oa; }));
        U32 hoisted__U32_487 = 1;
        Array *_va_Array_12 = Array_new(hoisted__Type_486, &hoisted__U32_487);
        (void)_va_Array_12;
        Type_delete(hoisted__Type_486, &(Bool){1});
        U32 hoisted__U32_488 = 0;
        Str hoisted__Str_489 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_12, &hoisted__U32_488, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_489; _oa; }));
        Str hoisted__Str_490 = (Str){.c_str = (void *)"./src/core/str.til:89:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_490, _va_Array_12);
        Str_delete(&hoisted__Str_490, &(Bool){0});
    }
    void *hoisted__v_493 = ptr_add(self->c_str, self->count);
    memcpy(hoisted__v_493, s->c_str, s->count);
    U32 hoisted__U32_494 = U32_clone(&new_len);
    self->count = hoisted__U32_494;
    void *hoisted__v_495 = ptr_add(self->c_str, new_len);
    I32 hoisted__I32_496 = 0;
    U64 hoisted__U64_497 = 1;
    memset(hoisted__v_495, hoisted__I32_496, hoisted__U64_497);
    I32_delete(&hoisted__I32_496, &(Bool){0});
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_498 = 1;
    U32 hoisted__U64_499 = U32_add(val->count, hoisted__U32_498);
    void * new_data = malloc(hoisted__U64_499);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_500 = ptr_add(new_data, val->count);
    I32 hoisted__I32_501 = 0;
    U64 hoisted__U64_502 = 1;
    memset(hoisted__v_500, hoisted__I32_501, hoisted__U64_502);
    I32_delete(&hoisted__I32_501, &(Bool){0});
    Str *hoisted__Str_503 = malloc(sizeof(Str));
    hoisted__Str_503->c_str = new_data;
    hoisted__Str_503->count = val->count;
    hoisted__Str_503->cap = val->count;
    return hoisted__Str_503;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool hoisted__Bool_504 = U32_lt(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_504) {
        free(self->c_str);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_569 = 0;
    Bool hoisted__Bool_570 = U32_eq(self->count, hoisted__U32_569);
    return hoisted__Bool_570;
}

U32 Str_size(void) {
    U32 hoisted__U32_839 = 16;
    return hoisted__U32_839;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_840 = Str_cmp(a, b);
    I64 hoisted__I64_841 = 0;
    Bool hoisted__Bool_842 = I64_eq(hoisted__I64_840, hoisted__I64_841);
    return hoisted__Bool_842;
}

U32 * Dynamic_size(void) {
    U32 hoisted__U32_929 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_929; return _r; }
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 * val) {
    I64 hoisted__I64_1007 = 0;
    Bool hoisted__Bool_1008 = I64_eq(DEREF(val), hoisted__I64_1007);
    if (hoisted__Bool_1008) {
        U64 hoisted__U64_971 = 2;
        void * buf = malloc(hoisted__U64_971);
        I64 hoisted__I64_972 = 48;
        U64 hoisted__U64_973 = 1;
        memcpy(buf, &hoisted__I64_972, hoisted__U64_973);
        U64 hoisted__U64_974 = 1;
        void *hoisted__v_975 = ptr_add(buf, hoisted__U64_974);
        I32 hoisted__I32_976 = 0;
        U64 hoisted__U64_977 = 1;
        memset(hoisted__v_975, hoisted__I32_976, hoisted__U64_977);
        I32_delete(&hoisted__I32_976, &(Bool){0});
        I64 hoisted__I64_978 = 1;
        I64 hoisted__I64_979 = 1;
        Str *hoisted__Str_980 = malloc(sizeof(Str));
        hoisted__Str_980->c_str = buf;
        hoisted__Str_980->count = hoisted__I64_978;
        hoisted__Str_980->cap = hoisted__I64_979;
        return hoisted__Str_980;
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_1009 = 0;
    Bool hoisted__Bool_1010 = I64_lt(val, &hoisted__I64_1009);
    if (hoisted__Bool_1010) {
        Bool hoisted__Bool_981 = 1;
        is_neg = hoisted__Bool_981;
        I64 hoisted__I64_982 = 0;
        I64 hoisted__I64_983 = I64_sub(hoisted__I64_982, DEREF(val));
        v = hoisted__I64_983;
    }
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_985 = 0;
        Bool _wcond_Bool_984 = I64_gt(&tmp, &hoisted__I64_985);
        (void)_wcond_Bool_984;
        if (_wcond_Bool_984) {
        } else {
            break;
        }
        U64 hoisted__U64_986 = 1;
        U64 hoisted__U64_987 = U64_add(ndigits, hoisted__U64_986);
        ndigits = hoisted__U64_987;
        I64 hoisted__I64_988 = 10;
        I64 hoisted__I64_989 = I64_div(tmp, hoisted__I64_988);
        tmp = hoisted__I64_989;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_990 = 1;
        U64 hoisted__U64_991 = U64_add(total, hoisted__U64_990);
        total = hoisted__U64_991;
    }
    U64 hoisted__U64_1011 = 1;
    U64 hoisted__U64_1012 = U64_add(total, hoisted__U64_1011);
    void * buf = malloc(hoisted__U64_1012);
    if (is_neg) {
        I64 hoisted__I64_992 = 45;
        U64 hoisted__U64_993 = 1;
        memcpy(buf, &hoisted__I64_992, hoisted__U64_993);
    }
    U64 hoisted__U64_1013 = 1;
    U64 i = U64_sub(total, hoisted__U64_1013);
    while (1) {
        I64 hoisted__I64_995 = 0;
        Bool _wcond_Bool_994 = I64_gt(&v, &hoisted__I64_995);
        (void)_wcond_Bool_994;
        if (_wcond_Bool_994) {
        } else {
            break;
        }
        I64 hoisted__I64_996 = 10;
        I64 hoisted__I64_997 = I64_mod(v, hoisted__I64_996);
        I64 hoisted__I64_998 = 48;
        I64 hoisted__I64_999 = I64_add(hoisted__I64_997, hoisted__I64_998);
        void *hoisted__v_1000 = ptr_add(buf, i);
        U8 hoisted__U8_1001 = I64_to_u8(hoisted__I64_999);
        U64 hoisted__U64_1002 = 1;
        memcpy(hoisted__v_1000, &hoisted__U8_1001, hoisted__U64_1002);
        U8_delete(&hoisted__U8_1001, &(Bool){0});
        I64 hoisted__I64_1003 = 10;
        I64 hoisted__I64_1004 = I64_div(v, hoisted__I64_1003);
        v = hoisted__I64_1004;
        U64 hoisted__U64_1005 = 1;
        U64 hoisted__U64_1006 = U64_sub(i, hoisted__U64_1005);
        i = hoisted__U64_1006;
    }
    void *hoisted__v_1014 = ptr_add(buf, total);
    I32 hoisted__I32_1015 = 0;
    U64 hoisted__U64_1016 = 1;
    memset(hoisted__v_1014, hoisted__I32_1015, hoisted__U64_1016);
    I32_delete(&hoisted__I32_1015, &(Bool){0});
    Str *hoisted__Str_1017 = malloc(sizeof(Str));
    hoisted__Str_1017->c_str = buf;
    hoisted__Str_1017->count = total;
    hoisted__Str_1017->cap = total;
    return hoisted__Str_1017;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    U32 hoisted__U32_1035 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1035; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1047 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1048 = -1;
    Bool hoisted__Bool_1049 = I64_eq(hoisted__I64_1047, hoisted__I64_1048);
    return hoisted__Bool_1049;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1050 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1051 = 1;
    Bool hoisted__Bool_1052 = I64_eq(hoisted__I64_1050, hoisted__I64_1051);
    return hoisted__Bool_1052;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1053 = I64_eq(DEREF(a), DEREF(b));
    Bool hoisted__Bool_1054 = not(hoisted__Bool_1053);
    return hoisted__Bool_1054;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1065 = Bool_eq(DEREF(a), DEREF(b));
    if (hoisted__Bool_1065) {
        I64 hoisted__I64_1063 = 0;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1063; return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1064 = -1;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1064; return _r; }
    }
    I64 hoisted__I64_1066 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1066; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    U32 hoisted__U32_1067 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1067; return _r; }
}

Primitive *Primitive_I16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I16 };
    return r;
}
Bool Primitive_eq(Primitive * self, Primitive * other) {
    Bool hoisted__Bool_1205 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1205) {
        Bool hoisted__Bool_1204 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        return hoisted__Bool_1204;
    }
    Bool hoisted__Bool_1206 = 0;
    return hoisted__Bool_1206;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1210 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1210) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
    }
    Str hoisted__Str_1211 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_1211);
    Str_delete(&hoisted__Str_1211, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1212 = 4;
    return hoisted__U32_1212;
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
    Bool hoisted__Bool_1271 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1271) {
        Str *hoisted__Str_1263 = get_payload(self);
        Bool hoisted__Bool_1264 = 0;
        Str_delete(hoisted__Str_1263, &hoisted__Bool_1264);
    }
    Bool hoisted__Bool_1272 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1272) {
        Str *hoisted__Str_1265 = get_payload(self);
        Bool hoisted__Bool_1266 = 0;
        Str_delete(hoisted__Str_1265, &hoisted__Bool_1266);
    }
    Bool hoisted__Bool_1273 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1273) {
        Str *hoisted__Str_1267 = get_payload(self);
        Bool hoisted__Bool_1268 = 0;
        Str_delete(hoisted__Str_1267, &hoisted__Bool_1268);
    }
    Bool hoisted__Bool_1274 = is(self, &(Type){.tag = Type_TAG_Primitive});
    if (hoisted__Bool_1274) {
        Primitive *hoisted__Primitive_1269 = get_payload(self);
        Bool hoisted__Bool_1270 = 0;
        Primitive_delete(hoisted__Primitive_1269, &hoisted__Bool_1270);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1356 = is(self, &(Type){.tag = Type_TAG_Unknown});
    if (hoisted__Bool_1356) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown; return _r; }
    }
    Bool hoisted__Bool_1357 = is(self, &(Type){.tag = Type_TAG_None});
    if (hoisted__Bool_1357) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None; return _r; }
    }
    Bool hoisted__Bool_1358 = is(self, &(Type){.tag = Type_TAG_I64});
    if (hoisted__Bool_1358) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64; return _r; }
    }
    Bool hoisted__Bool_1359 = is(self, &(Type){.tag = Type_TAG_U8});
    if (hoisted__Bool_1359) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8; return _r; }
    }
    Bool hoisted__Bool_1360 = is(self, &(Type){.tag = Type_TAG_I32});
    if (hoisted__Bool_1360) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32; return _r; }
    }
    Bool hoisted__Bool_1361 = is(self, &(Type){.tag = Type_TAG_U32});
    if (hoisted__Bool_1361) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32; return _r; }
    }
    Bool hoisted__Bool_1362 = is(self, &(Type){.tag = Type_TAG_U64});
    if (hoisted__Bool_1362) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64; return _r; }
    }
    Bool hoisted__Bool_1363 = is(self, &(Type){.tag = Type_TAG_F32});
    if (hoisted__Bool_1363) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32; return _r; }
    }
    Bool hoisted__Bool_1364 = is(self, &(Type){.tag = Type_TAG_Bool});
    if (hoisted__Bool_1364) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool; return _r; }
    }
    Bool hoisted__Bool_1365 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1365) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_1350 = Str_clone(_clone_payload_Struct_9);
        Type *hoisted__Type_1351 = Type_Struct(hoisted__Str_1350);
        return hoisted__Type_1351;
    }
    Bool hoisted__Bool_1366 = is(self, &(Type){.tag = Type_TAG_StructDef});
    if (hoisted__Bool_1366) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef; return _r; }
    }
    Bool hoisted__Bool_1367 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1367) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_1352 = Str_clone(_clone_payload_Enum_11);
        Type *hoisted__Type_1353 = Type_Enum(hoisted__Str_1352);
        return hoisted__Type_1353;
    }
    Bool hoisted__Bool_1368 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    if (hoisted__Bool_1368) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef; return _r; }
    }
    Bool hoisted__Bool_1369 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    if (hoisted__Bool_1369) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef; return _r; }
    }
    Bool hoisted__Bool_1370 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    if (hoisted__Bool_1370) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr; return _r; }
    }
    Bool hoisted__Bool_1371 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    if (hoisted__Bool_1371) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic; return _r; }
    }
    Bool hoisted__Bool_1372 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1372) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_1354 = Str_clone(_clone_payload_Custom_16);
        Type *hoisted__Type_1355 = Type_Custom(hoisted__Str_1354);
        return hoisted__Type_1355;
    }
    Bool hoisted__Bool_1373 = is(self, &(Type){.tag = Type_TAG_I8});
    if (hoisted__Bool_1373) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8; return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive *hoisted__Primitive_1374 = Primitive_clone(_clone_payload_Primitive_18);
    Type *hoisted__Type_1375 = Type_Primitive(hoisted__Primitive_1374);
    return hoisted__Type_1375;
}

U32 Type_size(void) {
    U32 hoisted__U32_1376 = 24;
    return hoisted__U32_1376;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_2804 = Str_is_empty(elem_type);
    if (hoisted__Bool_2804) {
        Str hoisted__Str_2798 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2799 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2798; _oa; }));
        U32 hoisted__U32_2800 = 1;
        Array *_va_Array_77 = Array_new(hoisted__Type_2799, &hoisted__U32_2800);
        (void)_va_Array_77;
        Type_delete(hoisted__Type_2799, &(Bool){1});
        U32 hoisted__U32_2801 = 0;
        Str hoisted__Str_2802 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_77, &hoisted__U32_2801, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2802; _oa; }));
        Str hoisted__Str_2803 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2803, _va_Array_77);
        Str_delete(&hoisted__Str_2803, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_2805 = calloc(DEREF(cap), elem_size);
    void * hoisted__v_2806 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    void * hoisted__v_2807 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    Array *hoisted__Array_2808 = malloc(sizeof(Array));
    hoisted__Array_2808->data = hoisted__v_2805;
    hoisted__Array_2808->cap = DEREF(cap);
    hoisted__Array_2808->elem_size = elem_size;
    hoisted__Array_2808->elem_clone = hoisted__v_2806;
    hoisted__Array_2808->elem_delete = hoisted__v_2807;
    return hoisted__Array_2808;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_2809 = Array_new_type_name(elem_type, cap);
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_2809;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    Bool hoisted__Bool_2824 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2824) {
        Str hoisted__Str_2810 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2811 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2810; _oa; }));
        U32 hoisted__U32_2812 = 5;
        Array *_va_Array_78 = Array_new(hoisted__Type_2811, &hoisted__U32_2812);
        (void)_va_Array_78;
        Type_delete(hoisted__Type_2811, &(Bool){1});
        U32 hoisted__U32_2813 = 0;
        Str hoisted__Str_2814 = (Str){.c_str = (void *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_78, &hoisted__U32_2813, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2814; _oa; }));
        U32 hoisted__U32_2815 = 1;
        Str *hoisted__Str_2816 = U32_to_str(i);
        Array_set(_va_Array_78, &hoisted__U32_2815, hoisted__Str_2816);
        U32 hoisted__U32_2817 = 2;
        Str hoisted__Str_2818 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_78, &hoisted__U32_2817, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2818; _oa; }));
        U32 hoisted__U32_2819 = 3;
        Str *hoisted__Str_2820 = U32_to_str(&self->cap);
        Array_set(_va_Array_78, &hoisted__U32_2819, hoisted__Str_2820);
        U32 hoisted__U32_2821 = 4;
        Str hoisted__Str_2822 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_78, &hoisted__U32_2821, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2822; _oa; }));
        Str hoisted__Str_2823 = (Str){.c_str = (void *)"./src/core/array.til:40:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2823, _va_Array_78);
        Str_delete(&hoisted__Str_2823, &(Bool){0});
    }
    U32 hoisted__U64_2825 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2826 = ptr_add(self->data, hoisted__U64_2825);
    return hoisted__v_2826;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_2841 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2841) {
        Str hoisted__Str_2827 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2828 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2827; _oa; }));
        U32 hoisted__U32_2829 = 5;
        Array *_va_Array_79 = Array_new(hoisted__Type_2828, &hoisted__U32_2829);
        (void)_va_Array_79;
        Type_delete(hoisted__Type_2828, &(Bool){1});
        U32 hoisted__U32_2830 = 0;
        Str hoisted__Str_2831 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_79, &hoisted__U32_2830, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2831; _oa; }));
        U32 hoisted__U32_2832 = 1;
        Str *hoisted__Str_2833 = U32_to_str(i);
        Array_set(_va_Array_79, &hoisted__U32_2832, hoisted__Str_2833);
        U32 hoisted__U32_2834 = 2;
        Str hoisted__Str_2835 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_79, &hoisted__U32_2834, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2835; _oa; }));
        U32 hoisted__U32_2836 = 3;
        Str *hoisted__Str_2837 = U32_to_str(&self->cap);
        Array_set(_va_Array_79, &hoisted__U32_2836, hoisted__Str_2837);
        U32 hoisted__U32_2838 = 4;
        Str hoisted__Str_2839 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_79, &hoisted__U32_2838, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2839; _oa; }));
        Str hoisted__Str_2840 = (Str){.c_str = (void *)"./src/core/array.til:49:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2840, _va_Array_79);
        Str_delete(&hoisted__Str_2840, &(Bool){0});
    }
    U32 hoisted__U64_2842 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2843 = ptr_add(self->data, hoisted__U64_2842);
    Bool hoisted__Bool_2844 = 0;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2843, &hoisted__Bool_2844);
    U32 hoisted__U64_2845 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2846 = ptr_add(self->data, hoisted__U64_2845);
    memcpy(hoisted__v_2846, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_2847 = self->cap;
        (void)_re_U32_2847;
        U32 _rc_U32_2847 = 0;
        (void)_rc_U32_2847;
        Bool hoisted__Bool_2856 = U32_lte(&_rc_U32_2847, &_re_U32_2847);
        if (hoisted__Bool_2856) {
            while (1) {
                Bool _wcond_Bool_2848 = U32_lt(&_rc_U32_2847, &_re_U32_2847);
                (void)_wcond_Bool_2848;
                if (_wcond_Bool_2848) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2847);
                U32_inc(&_rc_U32_2847);
                U32 hoisted__U64_2849 = U32_mul(i, self->elem_size);
                void *hoisted__v_2850 = ptr_add(self->data, hoisted__U64_2849);
                Bool hoisted__Bool_2851 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2850, &hoisted__Bool_2851);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2852 = U32_gt(&_rc_U32_2847, &_re_U32_2847);
                (void)_wcond_Bool_2852;
                if (_wcond_Bool_2852) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2847);
                U32_dec(&_rc_U32_2847);
                U32 hoisted__U64_2853 = U32_mul(i, self->elem_size);
                void *hoisted__v_2854 = ptr_add(self->data, hoisted__U64_2853);
                Bool hoisted__Bool_2855 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2854, &hoisted__Bool_2855);
            }
        }
    }
    free(self->data);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_2869 = U32_mul(self->cap, self->elem_size);
    void * new_data = malloc(hoisted__U64_2869);
    {
        U32 _re_U32_2857 = self->cap;
        (void)_re_U32_2857;
        U32 _rc_U32_2857 = 0;
        (void)_rc_U32_2857;
        Bool hoisted__Bool_2868 = U32_lte(&_rc_U32_2857, &_re_U32_2857);
        if (hoisted__Bool_2868) {
            while (1) {
                Bool _wcond_Bool_2858 = U32_lt(&_rc_U32_2857, &_re_U32_2857);
                (void)_wcond_Bool_2858;
                if (_wcond_Bool_2858) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2857);
                U32_inc(&_rc_U32_2857);
                U32 hoisted__U64_2859 = U32_mul(i, self->elem_size);
                void *hoisted__v_2860 = ptr_add(self->data, hoisted__U64_2859);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2860);
                U32 hoisted__U64_2861 = U32_mul(i, self->elem_size);
                void *hoisted__v_2862 = ptr_add(new_data, hoisted__U64_2861);
                memcpy(hoisted__v_2862, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2863 = U32_gt(&_rc_U32_2857, &_re_U32_2857);
                (void)_wcond_Bool_2863;
                if (_wcond_Bool_2863) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2857);
                U32_dec(&_rc_U32_2857);
                U32 hoisted__U64_2864 = U32_mul(i, self->elem_size);
                void *hoisted__v_2865 = ptr_add(self->data, hoisted__U64_2864);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2865);
                U32 hoisted__U64_2866 = U32_mul(i, self->elem_size);
                void *hoisted__v_2867 = ptr_add(new_data, hoisted__U64_2866);
                memcpy(hoisted__v_2867, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_2870 = malloc(sizeof(Array));
    hoisted__Array_2870->data = new_data;
    hoisted__Array_2870->cap = self->cap;
    hoisted__Array_2870->elem_size = self->elem_size;
    hoisted__Array_2870->elem_clone = (void *)self->elem_clone;
    hoisted__Array_2870->elem_delete = (void *)self->elem_delete;
    return hoisted__Array_2870;
}

U32 Array_size(void) {
    U32 hoisted__U32_2871 = 32;
    return hoisted__U32_2871;
}

void panic(Str * loc_str, Array * parts) {
    Str hoisted__Str_3108 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_3109 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3108; _oa; }));
    U32 hoisted__U32_3110 = 3;
    Array *_va_Array_96 = Array_new(hoisted__Type_3109, &hoisted__U32_3110);
    (void)_va_Array_96;
    Type_delete(hoisted__Type_3109, &(Bool){1});
    U32 hoisted__U32_3111 = 0;
    Str *hoisted__Str_3112 = Str_clone(loc_str);
    Array_set(_va_Array_96, &hoisted__U32_3111, hoisted__Str_3112);
    U32 hoisted__U32_3113 = 1;
    Str hoisted__Str_3114 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_96, &hoisted__U32_3113, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3114; _oa; }));
    Array *hoisted__Array_3115 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_3116 = 2;
    Str *hoisted__Str_3117 = format(hoisted__Array_3115);
    Array_set(_va_Array_96, &hoisted__U32_3116, hoisted__Str_3117);
    println(_va_Array_96);
    I64 hoisted__I64_3118 = 1;
    exit(hoisted__I64_3118);
}

void UNREACHABLE(Str * loc_str) {
    Str hoisted__Str_3127 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_3128 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3127; _oa; }));
    U32 hoisted__U32_3129 = 1;
    Array *_va_Array_98 = Array_new(hoisted__Type_3128, &hoisted__U32_3129);
    (void)_va_Array_98;
    Type_delete(hoisted__Type_3128, &(Bool){1});
    U32 hoisted__U32_3130 = 0;
    Str hoisted__Str_3131 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_98, &hoisted__U32_3130, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3131; _oa; }));
    panic(loc_str, _va_Array_98);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_3137 = not(DEREF(cond));
    if (hoisted__Bool_3137) {
        Str hoisted__Str_3132 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_3133 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3132; _oa; }));
        U32 hoisted__U32_3134 = 1;
        Array *_va_Array_99 = Array_new(hoisted__Type_3133, &hoisted__U32_3134);
        (void)_va_Array_99;
        Type_delete(hoisted__Type_3133, &(Bool){1});
        U32 hoisted__U32_3135 = 0;
        Str hoisted__Str_3136 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_99, &hoisted__U32_3135, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3136; _oa; }));
        panic(loc_str, _va_Array_99);
    }
    Bool hoisted__Bool_3138 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_3138; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_3161 = I64_neq(a, b);
    if (hoisted__Bool_3161) {
        Str hoisted__Str_3148 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_3149 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3148; _oa; }));
        U32 hoisted__U32_3150 = 5;
        Array *_va_Array_101 = Array_new(hoisted__Type_3149, &hoisted__U32_3150);
        (void)_va_Array_101;
        Type_delete(hoisted__Type_3149, &(Bool){1});
        U32 hoisted__U32_3151 = 0;
        Str hoisted__Str_3152 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_101, &hoisted__U32_3151, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3152; _oa; }));
        U32 hoisted__U32_3153 = 1;
        Str *hoisted__Str_3154 = I64_to_str(a);
        Array_set(_va_Array_101, &hoisted__U32_3153, hoisted__Str_3154);
        U32 hoisted__U32_3155 = 2;
        Str hoisted__Str_3156 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_101, &hoisted__U32_3155, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3156; _oa; }));
        U32 hoisted__U32_3157 = 3;
        Str *hoisted__Str_3158 = I64_to_str(b);
        Array_set(_va_Array_101, &hoisted__U32_3157, hoisted__Str_3158);
        U32 hoisted__U32_3159 = 4;
        Str hoisted__Str_3160 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_101, &hoisted__U32_3159, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3160; _oa; }));
        panic(loc_str, _va_Array_101);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_3175 = Str_eq(a, b);
    Bool hoisted__Bool_3176 = not(hoisted__Bool_3175);
    if (hoisted__Bool_3176) {
        Str hoisted__Str_3162 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_3163 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3162; _oa; }));
        U32 hoisted__U32_3164 = 5;
        Array *_va_Array_102 = Array_new(hoisted__Type_3163, &hoisted__U32_3164);
        (void)_va_Array_102;
        Type_delete(hoisted__Type_3163, &(Bool){1});
        U32 hoisted__U32_3165 = 0;
        Str hoisted__Str_3166 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_102, &hoisted__U32_3165, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3166; _oa; }));
        U32 hoisted__U32_3167 = 1;
        Str *hoisted__Str_3168 = Str_clone(a);
        Array_set(_va_Array_102, &hoisted__U32_3167, hoisted__Str_3168);
        U32 hoisted__U32_3169 = 2;
        Str hoisted__Str_3170 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_102, &hoisted__U32_3169, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3170; _oa; }));
        U32 hoisted__U32_3171 = 3;
        Str *hoisted__Str_3172 = Str_clone(b);
        Array_set(_va_Array_102, &hoisted__U32_3171, hoisted__Str_3172);
        U32 hoisted__U32_3173 = 4;
        Str hoisted__Str_3174 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_102, &hoisted__U32_3173, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3174; _oa; }));
        panic(loc_str, _va_Array_102);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_3177 = parts;
        (void)_fc_Array_3177;
        (void)_fc_Array_3177;
        U32 _fi_USize_3177 = 0;
        (void)_fi_USize_3177;
        while (1) {
            U32 hoisted__U32_3179; { U32 *_hp = (U32 *)Array_len(_fc_Array_3177); hoisted__U32_3179 = *_hp; free(_hp); }
            Bool _wcond_Bool_3178 = U32_lt(&_fi_USize_3177, &hoisted__U32_3179);
            (void)_wcond_Bool_3178;
            if (_wcond_Bool_3178) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_3177, &_fi_USize_3177);
            U32 hoisted__U32_3180 = 1;
            U32 hoisted__U32_3181 = U32_add(_fi_USize_3177, hoisted__U32_3180);
            _fi_USize_3177 = hoisted__U32_3181;
            print_single(s);
        }
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_3366 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3367 = 3;
    assert_eq(&hoisted__Str_3366, &result, &hoisted__I64_3367);
    Str_delete(&hoisted__Str_3366, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_3374 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3375 = 15;
    assert_eq(&hoisted__Str_3374, &result, &hoisted__I64_3375);
    Str_delete(&hoisted__Str_3374, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_3382 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3383 = 26;
    assert_eq(&hoisted__Str_3382, &result, &hoisted__I64_3383);
    Str_delete(&hoisted__Str_3382, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3386 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3387 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3386, &result, &hoisted__Str_3387);
    Str_delete(&hoisted__Str_3386, &(Bool){0});
    Str_delete(&hoisted__Str_3387, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3718 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3718, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_3718, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_3719 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3719, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_3719, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_3721 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3722 = 8;
    assert_eq(&hoisted__Str_3721, &result, &hoisted__I64_3722);
    Str_delete(&hoisted__Str_3721, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_3725 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3726 = 1;
    Bool_delete(assert(&hoisted__Str_3725, &hoisted__Bool_3726), &(Bool){1});
    Str_delete(&hoisted__Str_3725, &(Bool){0});
    Str hoisted__Str_3730 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3731 = 1;
    Bool_delete(assert(&hoisted__Str_3730, &hoisted__Bool_3731), &(Bool){1});
    Str_delete(&hoisted__Str_3730, &(Bool){0});
}

CfVec2 * CfVec2_magic(void) {
    I64 hoisted__I64_3733 = 42;
    I64 hoisted__I64_3734 = 99;
    CfVec2 hoisted__CfVec2_3735 = (CfVec2){.x = hoisted__I64_3733, .y = hoisted__I64_3734};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3735; return _r; }
}

CfVec2 * CfVec2_at(I64 * x, I64 * y) {
    CfVec2 hoisted__CfVec2_3736 = (CfVec2){.x = DEREF(x), .y = DEREF(y)};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3736; return _r; }
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_3737 = (CfVec2){.x = self->x, .y = self->y};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3737; return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_3738 = 16;
    return hoisted__U32_3738;
}

void test_struct_fold_simple(void) {
    CfVec2 *v = CfVec2_magic();
    Str hoisted__Str_3739 = (Str){.c_str = (void *)"test/constfold.til:122:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3740 = 42;
    assert_eq(&hoisted__Str_3739, &v->x, &hoisted__I64_3740);
    Str_delete(&hoisted__Str_3739, &(Bool){0});
    Str hoisted__Str_3741 = (Str){.c_str = (void *)"test/constfold.til:123:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3742 = 99;
    assert_eq(&hoisted__Str_3741, &v->y, &hoisted__I64_3742);
    Str_delete(&hoisted__Str_3741, &(Bool){0});
    CfVec2_delete(v, &(Bool){1});
}

void test_struct_fold_values(void) {
    I64 hoisted__I64_3743 = 10;
    I64 hoisted__I64_3744 = 20;
    CfVec2 *p = CfVec2_at(&hoisted__I64_3743, &hoisted__I64_3744);
    Str hoisted__Str_3745 = (Str){.c_str = (void *)"test/constfold.til:129:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3746 = 10;
    assert_eq(&hoisted__Str_3745, &p->x, &hoisted__I64_3746);
    Str_delete(&hoisted__Str_3745, &(Bool){0});
    Str hoisted__Str_3747 = (Str){.c_str = (void *)"test/constfold.til:130:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3748 = 20;
    assert_eq(&hoisted__Str_3747, &p->y, &hoisted__I64_3748);
    Str_delete(&hoisted__Str_3747, &(Bool){0});
    CfVec2_delete(p, &(Bool){1});
}

CfRect * CfRect_sample(void) {
    I64 hoisted__I64_3749 = 5;
    I64 hoisted__I64_3750 = 10;
    I64 hoisted__I64_3751 = 100;
    I64 hoisted__I64_3752 = 200;
    CfRect hoisted__CfRect_3753 = (CfRect){.top_left = (CfVec2){.x = hoisted__I64_3749, .y = hoisted__I64_3750}, .bottom_right = (CfVec2){.x = hoisted__I64_3751, .y = hoisted__I64_3752}};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_3753; return _r; }
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_3754 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_3754; return _r; }
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_3755 = 32;
    return hoisted__U32_3755;
}

void test_struct_fold_nested(void) {
    CfRect *r = CfRect_sample();
    Str hoisted__Str_3756 = (Str){.c_str = (void *)"test/constfold.til:146:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3757 = 5;
    assert_eq(&hoisted__Str_3756, &r->top_left.x, &hoisted__I64_3757);
    Str_delete(&hoisted__Str_3756, &(Bool){0});
    Str hoisted__Str_3758 = (Str){.c_str = (void *)"test/constfold.til:147:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3759 = 10;
    assert_eq(&hoisted__Str_3758, &r->top_left.y, &hoisted__I64_3759);
    Str_delete(&hoisted__Str_3758, &(Bool){0});
    Str hoisted__Str_3760 = (Str){.c_str = (void *)"test/constfold.til:148:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3761 = 100;
    assert_eq(&hoisted__Str_3760, &r->bottom_right.x, &hoisted__I64_3761);
    Str_delete(&hoisted__Str_3760, &(Bool){0});
    Str hoisted__Str_3762 = (Str){.c_str = (void *)"test/constfold.til:149:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3763 = 200;
    assert_eq(&hoisted__Str_3762, &r->bottom_right.y, &hoisted__I64_3763);
    Str_delete(&hoisted__Str_3762, &(Bool){0});
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
    Bool hoisted__Bool_3768 = is(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3768) {
        Bool hoisted__Bool_3765 = is(other, &(Color){.tag = Color_TAG_Red});
        return hoisted__Bool_3765;
    }
    Bool hoisted__Bool_3769 = is(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3769) {
        Bool hoisted__Bool_3766 = is(other, &(Color){.tag = Color_TAG_Green});
        return hoisted__Bool_3766;
    }
    Bool hoisted__Bool_3770 = is(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3770) {
        Bool hoisted__Bool_3767 = is(other, &(Color){.tag = Color_TAG_Blue});
        return hoisted__Bool_3767;
    }
    Bool hoisted__Bool_3771 = 0;
    return hoisted__Bool_3771;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_3779 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3779) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
    }
    Bool hoisted__Bool_3780 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3780) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green; return _r; }
    }
    Bool hoisted__Bool_3781 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3781) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue; return _r; }
    }
    Str hoisted__Str_3782 = (Str){.c_str = (void *)"Color.clone:154:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_3782);
    Str_delete(&hoisted__Str_3782, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_3783 = 4;
    return hoisted__U32_3783;
}


void test_enum_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Str hoisted__Str_3784 = (Str){.c_str = (void *)"test/constfold.til:159:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3785 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    Bool_delete(assert(&hoisted__Str_3784, &hoisted__Bool_3785), &(Bool){1});
    Str_delete(&hoisted__Str_3784, &(Bool){0});
    Bool hoisted__Bool_3787 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_3788 = (Str){.c_str = (void *)"test/constfold.til:160:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3789 = not(hoisted__Bool_3787);
    Bool_delete(assert(&hoisted__Str_3788, &hoisted__Bool_3789), &(Bool){1});
    Str_delete(&hoisted__Str_3788, &(Bool){0});
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
    Bool hoisted__Bool_3791 = is(self, other);
    return hoisted__Bool_3791;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_3809 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3809) {
        I64 *hoisted__I64_3805 = get_payload(self);
        Bool hoisted__Bool_3806 = 0;
        I64_delete(hoisted__I64_3805, &hoisted__Bool_3806);
    }
    Bool hoisted__Bool_3810 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3810) {
        Str *hoisted__Str_3807 = get_payload(self);
        Bool hoisted__Bool_3808 = 0;
        Str_delete(hoisted__Str_3807, &hoisted__Bool_3808);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_3839 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3839) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_3836 = Token_Num(_clone_payload_Num_0);
        return hoisted__Token_3836;
    }
    Bool hoisted__Bool_3840 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3840) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_3837 = Str_clone(_clone_payload_Name_1);
        Token *hoisted__Token_3838 = Token_Name(hoisted__Str_3837);
        return hoisted__Token_3838;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof; return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_3841 = 24;
    return hoisted__U32_3841;
}


void test_enum_payload_fold(void) {
    I64 hoisted__I64_3842 = 42;
    Token *t = Token_Num(&hoisted__I64_3842);
    Str hoisted__Str_3843 = (Str){.c_str = (void *)"test/constfold.til:168:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3844 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    Bool_delete(assert(&hoisted__Str_3843, &hoisted__Bool_3844), &(Bool){1});
    Str_delete(&hoisted__Str_3843, &(Bool){0});
    Bool hoisted__Bool_3846 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_3847 = (Str){.c_str = (void *)"test/constfold.til:169:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3848 = not(hoisted__Bool_3846);
    Bool_delete(assert(&hoisted__Str_3847, &hoisted__Bool_3848), &(Bool){1});
    Str_delete(&hoisted__Str_3847, &(Bool){0});
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

I64 struct_field_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) {
        return 5LL;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        return 2LL;
    }
    fprintf(stderr, "struct_field_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *struct_field_name(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"c_str", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"count", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"data", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"cap", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"elem_size", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"elem_clone", .count = 10ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"elem_delete", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"top_left", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"bottom_right", .count = 12ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    fprintf(stderr, "struct_field_name: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 struct_field_is_mut(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
    }
    fprintf(stderr, "struct_field_is_mut: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *struct_field_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) {
    }
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) {
    }
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0) {
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0) {
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CloneFn", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"DeleteFn", .count = 8ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"CfVec2", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    fprintf(stderr, "struct_field_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
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
    CAP_LIT = 4294967295;
    CAP_VIEW = 4294967294;
    ELEM_POD = 0;
    ELEM_BOXED = 1;
    ELEM_FN = 2;
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
