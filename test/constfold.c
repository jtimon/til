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
        Array *_fc_Array_431 = parts;
        (void)_fc_Array_431;
        (void)_fc_Array_431;
        U32 _fi_USize_431 = 0;
        (void)_fi_USize_431;
        while (1) {
            U32 hoisted__U32_433; { U32 *_hp = (U32 *)Array_len(_fc_Array_431); hoisted__U32_433 = *_hp; free(_hp); }
            Bool _wcond_Bool_432 = U32_lt(&_fi_USize_431, &hoisted__U32_433);
            (void)_wcond_Bool_432;
            if (_wcond_Bool_432) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_431, &_fi_USize_431);
            U32 hoisted__U32_434 = 1;
            U32 hoisted__U32_435 = U32_add(_fi_USize_431, hoisted__U32_434);
            _fi_USize_431 = hoisted__U32_435;
            U32 hoisted__U32_436 = Str_len(s);
            U32 hoisted__U32_437 = U32_add(total, hoisted__U32_436);
            total = hoisted__U32_437;
        }
    }
    Str *out = Str_with_capacity(&total);
    {
        Array *_fc_Array_438 = parts;
        (void)_fc_Array_438;
        (void)_fc_Array_438;
        U32 _fi_USize_438 = 0;
        (void)_fi_USize_438;
        while (1) {
            U32 hoisted__U32_440; { U32 *_hp = (U32 *)Array_len(_fc_Array_438); hoisted__U32_440 = *_hp; free(_hp); }
            Bool _wcond_Bool_439 = U32_lt(&_fi_USize_438, &hoisted__U32_440);
            (void)_wcond_Bool_439;
            if (_wcond_Bool_439) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_438, &_fi_USize_438);
            U32 hoisted__U32_441 = 1;
            U32 hoisted__U32_442 = U32_add(_fi_USize_438, hoisted__U32_441);
            _fi_USize_438 = hoisted__U32_442;
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
    Bool hoisted__Bool_449 = U32_gte(i, &self->count);
    if (hoisted__Bool_449) {
        Str hoisted__Str_443 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_444 = Type_Struct(&hoisted__Str_443);
        Str_delete(&hoisted__Str_443, &(Bool){0});
        U32 hoisted__U32_445 = 1;
        Array *_va_Array_9 = Array_new(hoisted__Type_444, &hoisted__U32_445);
        (void)_va_Array_9;
        Type_delete(hoisted__Type_444, &(Bool){1});
        U32 hoisted__U32_446 = 0;
        Str hoisted__Str_447 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_9, &hoisted__U32_446, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_447; _oa; }));
        Str hoisted__Str_448 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_448, _va_Array_9);
        Str_delete(&hoisted__Str_448, &(Bool){0});
    }
    void *hoisted__v_450 = ptr_add(self->c_str, DEREF(i));
    return hoisted__v_450;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_460 = U32_lt(&b->count, &a->count);
    if (hoisted__Bool_460) {
        min_len = b->count;
    }
    {
        U32 _re_U32_452 = U32_clone(&min_len);
        (void)_re_U32_452;
        U32 _rc_U32_452 = 0;
        (void)_rc_U32_452;
        Bool hoisted__Bool_459 = U32_lte(&_rc_U32_452, &_re_U32_452);
        if (hoisted__Bool_459) {
            while (1) {
                Bool _wcond_Bool_453 = U32_lt(&_rc_U32_452, &_re_U32_452);
                (void)_wcond_Bool_453;
                if (_wcond_Bool_453) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_452);
                U32_inc(&_rc_U32_452);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_454 = 0;
                Bool hoisted__Bool_455 = I64_neq(&c, &hoisted__I64_454);
                if (hoisted__Bool_455) {
                    return c;
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_456 = U32_gt(&_rc_U32_452, &_re_U32_452);
                (void)_wcond_Bool_456;
                if (_wcond_Bool_456) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_452);
                U32_dec(&_rc_U32_452);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_457 = 0;
                Bool hoisted__Bool_458 = I64_neq(&c, &hoisted__I64_457);
                if (hoisted__Bool_458) {
                    return c;
                }
            }
        }
    }
    I64 hoisted__I64_461 = U32_cmp(a->count, b->count);
    return hoisted__I64_461;
}

Str * Str_with_capacity(U32 * n) {
    U32 hoisted__U32_463 = 1;
    U32 hoisted__U64_464 = U32_add(DEREF(n), hoisted__U32_463);
    void * buf = malloc(hoisted__U64_464);
    I32 hoisted__I32_465 = 0;
    U64 hoisted__U64_466 = 1;
    memset(buf, hoisted__I32_465, hoisted__U64_466);
    I64 hoisted__I64_467 = 0;
    Str *hoisted__Str_468 = malloc(sizeof(Str));
    hoisted__Str_468->c_str = buf;
    hoisted__Str_468->count = hoisted__I64_467;
    hoisted__Str_468->cap = DEREF(n);
    return hoisted__Str_468;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_481 = U32_gte(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_481) {
        Str hoisted__Str_469 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_470 = Type_Struct(&hoisted__Str_469);
        Str_delete(&hoisted__Str_469, &(Bool){0});
        U32 hoisted__U32_471 = 1;
        Array *_va_Array_10 = Array_new(hoisted__Type_470, &hoisted__U32_471);
        (void)_va_Array_10;
        Type_delete(hoisted__Type_470, &(Bool){1});
        U32 hoisted__U32_472 = 0;
        Str hoisted__Str_473 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_10, &hoisted__U32_472, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_473; _oa; }));
        Str hoisted__Str_474 = (Str){.c_str = (void *)"./src/core/str.til:85:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_474, _va_Array_10);
        Str_delete(&hoisted__Str_474, &(Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_482 = U32_gt(&new_len, &self->cap);
    if (hoisted__Bool_482) {
        Str hoisted__Str_475 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_476 = Type_Struct(&hoisted__Str_475);
        Str_delete(&hoisted__Str_475, &(Bool){0});
        U32 hoisted__U32_477 = 1;
        Array *_va_Array_11 = Array_new(hoisted__Type_476, &hoisted__U32_477);
        (void)_va_Array_11;
        Type_delete(hoisted__Type_476, &(Bool){1});
        U32 hoisted__U32_478 = 0;
        Str hoisted__Str_479 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_11, &hoisted__U32_478, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_479; _oa; }));
        Str hoisted__Str_480 = (Str){.c_str = (void *)"./src/core/str.til:89:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_480, _va_Array_11);
        Str_delete(&hoisted__Str_480, &(Bool){0});
    }
    void *hoisted__v_483 = ptr_add(self->c_str, self->count);
    memcpy(hoisted__v_483, s->c_str, s->count);
    U32 hoisted__U32_484 = U32_clone(&new_len);
    self->count = hoisted__U32_484;
    void *hoisted__v_485 = ptr_add(self->c_str, new_len);
    I32 hoisted__I32_486 = 0;
    U64 hoisted__U64_487 = 1;
    memset(hoisted__v_485, hoisted__I32_486, hoisted__U64_487);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_488 = 1;
    U32 hoisted__U64_489 = U32_add(val->count, hoisted__U32_488);
    void * new_data = malloc(hoisted__U64_489);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_490 = ptr_add(new_data, val->count);
    I32 hoisted__I32_491 = 0;
    U64 hoisted__U64_492 = 1;
    memset(hoisted__v_490, hoisted__I32_491, hoisted__U64_492);
    Str *hoisted__Str_493 = malloc(sizeof(Str));
    hoisted__Str_493->c_str = new_data;
    hoisted__Str_493->count = val->count;
    hoisted__Str_493->cap = val->count;
    return hoisted__Str_493;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool hoisted__Bool_494 = U32_lt(&self->cap, &CAP_VIEW);
    if (hoisted__Bool_494) {
        free(self->c_str);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_560 = 0;
    Bool hoisted__Bool_561 = U32_eq(self->count, hoisted__U32_560);
    return hoisted__Bool_561;
}

U32 Str_size(void) {
    I64 hoisted__I64_852 = 16;
    return hoisted__I64_852;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_853 = Str_cmp(a, b);
    I64 hoisted__I64_854 = 0;
    Bool hoisted__Bool_855 = I64_eq(hoisted__I64_853, hoisted__I64_854);
    return hoisted__Bool_855;
}

U32 * Dynamic_size(void) {
    I64 hoisted__I64_901 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_901; return _r; }
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 * val) {
    I64 hoisted__I64_980 = 0;
    Bool hoisted__Bool_981 = I64_eq(DEREF(val), hoisted__I64_980);
    if (hoisted__Bool_981) {
        U64 hoisted__U64_944 = 2;
        void * buf = malloc(hoisted__U64_944);
        I64 hoisted__I64_945 = 48;
        U64 hoisted__U64_946 = 1;
        memcpy(buf, &hoisted__I64_945, hoisted__U64_946);
        U64 hoisted__U64_947 = 1;
        void *hoisted__v_948 = ptr_add(buf, hoisted__U64_947);
        I32 hoisted__I32_949 = 0;
        U64 hoisted__U64_950 = 1;
        memset(hoisted__v_948, hoisted__I32_949, hoisted__U64_950);
        I64 hoisted__I64_951 = 1;
        I64 hoisted__I64_952 = 1;
        Str *hoisted__Str_953 = malloc(sizeof(Str));
        hoisted__Str_953->c_str = buf;
        hoisted__Str_953->count = hoisted__I64_951;
        hoisted__Str_953->cap = hoisted__I64_952;
        return hoisted__Str_953;
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_982 = 0;
    Bool hoisted__Bool_983 = I64_lt(val, &hoisted__I64_982);
    if (hoisted__Bool_983) {
        Bool hoisted__Bool_954 = 1;
        is_neg = hoisted__Bool_954;
        I64 hoisted__I64_955 = 0;
        I64 hoisted__I64_956 = I64_sub(hoisted__I64_955, DEREF(val));
        v = hoisted__I64_956;
    }
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_958 = 0;
        Bool _wcond_Bool_957 = I64_gt(&tmp, &hoisted__I64_958);
        (void)_wcond_Bool_957;
        if (_wcond_Bool_957) {
        } else {
            break;
        }
        U64 hoisted__U64_959 = 1;
        U64 hoisted__U64_960 = U64_add(ndigits, hoisted__U64_959);
        ndigits = hoisted__U64_960;
        I64 hoisted__I64_961 = 10;
        I64 hoisted__I64_962 = I64_div(tmp, hoisted__I64_961);
        tmp = hoisted__I64_962;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_963 = 1;
        U64 hoisted__U64_964 = U64_add(total, hoisted__U64_963);
        total = hoisted__U64_964;
    }
    U64 hoisted__U64_984 = 1;
    U64 hoisted__U64_985 = U64_add(total, hoisted__U64_984);
    void * buf = malloc(hoisted__U64_985);
    if (is_neg) {
        I64 hoisted__I64_965 = 45;
        U64 hoisted__U64_966 = 1;
        memcpy(buf, &hoisted__I64_965, hoisted__U64_966);
    }
    U64 hoisted__U64_986 = 1;
    U64 i = U64_sub(total, hoisted__U64_986);
    while (1) {
        I64 hoisted__I64_968 = 0;
        Bool _wcond_Bool_967 = I64_gt(&v, &hoisted__I64_968);
        (void)_wcond_Bool_967;
        if (_wcond_Bool_967) {
        } else {
            break;
        }
        I64 hoisted__I64_969 = 10;
        I64 hoisted__I64_970 = I64_mod(v, hoisted__I64_969);
        I64 hoisted__I64_971 = 48;
        I64 hoisted__I64_972 = I64_add(hoisted__I64_970, hoisted__I64_971);
        void *hoisted__v_973 = ptr_add(buf, i);
        U8 hoisted__U8_974 = I64_to_u8(hoisted__I64_972);
        U64 hoisted__U64_975 = 1;
        memcpy(hoisted__v_973, &hoisted__U8_974, hoisted__U64_975);
        I64 hoisted__I64_976 = 10;
        I64 hoisted__I64_977 = I64_div(v, hoisted__I64_976);
        v = hoisted__I64_977;
        U64 hoisted__U64_978 = 1;
        U64 hoisted__U64_979 = U64_sub(i, hoisted__U64_978);
        i = hoisted__U64_979;
    }
    void *hoisted__v_987 = ptr_add(buf, total);
    I32 hoisted__I32_988 = 0;
    U64 hoisted__U64_989 = 1;
    memset(hoisted__v_987, hoisted__I32_988, hoisted__U64_989);
    Str *hoisted__Str_990 = malloc(sizeof(Str));
    hoisted__Str_990->c_str = buf;
    hoisted__Str_990->count = total;
    hoisted__Str_990->cap = total;
    return hoisted__Str_990;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    I64 hoisted__I64_1008 = 8;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_1008; return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1018 = 0;
    I64 hoisted__I64_1019 = 1;
    I64 hoisted__I64_1020 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1021 = I64_sub(hoisted__I64_1018, hoisted__I64_1019);
    Bool hoisted__Bool_1022 = I64_eq(hoisted__I64_1020, hoisted__I64_1021);
    return hoisted__Bool_1022;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1023 = I64_cmp(DEREF(a), DEREF(b));
    I64 hoisted__I64_1024 = 1;
    Bool hoisted__Bool_1025 = I64_eq(hoisted__I64_1023, hoisted__I64_1024);
    return hoisted__Bool_1025;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1026 = I64_eq(DEREF(a), DEREF(b));
    Bool hoisted__Bool_1027 = not(hoisted__Bool_1026);
    return hoisted__Bool_1027;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1040 = Bool_eq(DEREF(a), DEREF(b));
    if (hoisted__Bool_1040) {
        I64 hoisted__I64_1036 = 0;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1036; return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1037 = 0;
        I64 hoisted__I64_1038 = 1;
        I64 hoisted__I64_1039 = I64_sub(hoisted__I64_1037, hoisted__I64_1038);
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1039; return _r; }
    }
    I64 hoisted__I64_1041 = 1;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1041; return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    I64 hoisted__I64_1042 = 1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__I64_1042; return _r; }
}

Primitive *Primitive_I16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I16 };
    return r;
}
Bool Primitive_eq(Primitive * self, Primitive * other) {
    Bool hoisted__Bool_1201 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1201) {
        Bool hoisted__Bool_1200 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        return hoisted__Bool_1200;
    }
    Bool hoisted__Bool_1202 = 0;
    return hoisted__Bool_1202;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1206 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1206) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
    }
    Str hoisted__Str_1207 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_1207);
    Str_delete(&hoisted__Str_1207, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16; return _r; }
}

U32 Primitive_size(void) {
    I64 hoisted__I64_1208 = 4;
    return hoisted__I64_1208;
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
    Bool hoisted__Bool_1267 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1267) {
        Str *hoisted__Str_1259 = get_payload(self);
        Bool hoisted__Bool_1260 = 0;
        Str_delete(hoisted__Str_1259, &hoisted__Bool_1260);
    }
    Bool hoisted__Bool_1268 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1268) {
        Str *hoisted__Str_1261 = get_payload(self);
        Bool hoisted__Bool_1262 = 0;
        Str_delete(hoisted__Str_1261, &hoisted__Bool_1262);
    }
    Bool hoisted__Bool_1269 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1269) {
        Str *hoisted__Str_1263 = get_payload(self);
        Bool hoisted__Bool_1264 = 0;
        Str_delete(hoisted__Str_1263, &hoisted__Bool_1264);
    }
    Bool hoisted__Bool_1270 = is(self, &(Type){.tag = Type_TAG_Primitive});
    if (hoisted__Bool_1270) {
        Primitive *hoisted__Primitive_1265 = get_payload(self);
        Bool hoisted__Bool_1266 = 0;
        Primitive_delete(hoisted__Primitive_1265, &hoisted__Bool_1266);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1349 = is(self, &(Type){.tag = Type_TAG_Unknown});
    if (hoisted__Bool_1349) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown; return _r; }
    }
    Bool hoisted__Bool_1350 = is(self, &(Type){.tag = Type_TAG_None});
    if (hoisted__Bool_1350) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None; return _r; }
    }
    Bool hoisted__Bool_1351 = is(self, &(Type){.tag = Type_TAG_I64});
    if (hoisted__Bool_1351) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64; return _r; }
    }
    Bool hoisted__Bool_1352 = is(self, &(Type){.tag = Type_TAG_U8});
    if (hoisted__Bool_1352) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8; return _r; }
    }
    Bool hoisted__Bool_1353 = is(self, &(Type){.tag = Type_TAG_I32});
    if (hoisted__Bool_1353) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32; return _r; }
    }
    Bool hoisted__Bool_1354 = is(self, &(Type){.tag = Type_TAG_U32});
    if (hoisted__Bool_1354) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32; return _r; }
    }
    Bool hoisted__Bool_1355 = is(self, &(Type){.tag = Type_TAG_U64});
    if (hoisted__Bool_1355) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64; return _r; }
    }
    Bool hoisted__Bool_1356 = is(self, &(Type){.tag = Type_TAG_F32});
    if (hoisted__Bool_1356) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32; return _r; }
    }
    Bool hoisted__Bool_1357 = is(self, &(Type){.tag = Type_TAG_Bool});
    if (hoisted__Bool_1357) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool; return _r; }
    }
    Bool hoisted__Bool_1358 = is(self, &(Type){.tag = Type_TAG_Struct});
    if (hoisted__Bool_1358) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Type *hoisted__Type_1346 = Type_Struct(_clone_payload_Struct_9);
        return hoisted__Type_1346;
    }
    Bool hoisted__Bool_1359 = is(self, &(Type){.tag = Type_TAG_StructDef});
    if (hoisted__Bool_1359) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef; return _r; }
    }
    Bool hoisted__Bool_1360 = is(self, &(Type){.tag = Type_TAG_Enum});
    if (hoisted__Bool_1360) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Type *hoisted__Type_1347 = Type_Enum(_clone_payload_Enum_11);
        return hoisted__Type_1347;
    }
    Bool hoisted__Bool_1361 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    if (hoisted__Bool_1361) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef; return _r; }
    }
    Bool hoisted__Bool_1362 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    if (hoisted__Bool_1362) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef; return _r; }
    }
    Bool hoisted__Bool_1363 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    if (hoisted__Bool_1363) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr; return _r; }
    }
    Bool hoisted__Bool_1364 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    if (hoisted__Bool_1364) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic; return _r; }
    }
    Bool hoisted__Bool_1365 = is(self, &(Type){.tag = Type_TAG_Custom});
    if (hoisted__Bool_1365) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Type *hoisted__Type_1348 = Type_Custom(_clone_payload_Custom_16);
        return hoisted__Type_1348;
    }
    Bool hoisted__Bool_1366 = is(self, &(Type){.tag = Type_TAG_I8});
    if (hoisted__Bool_1366) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8; return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Type *hoisted__Type_1367 = Type_Primitive(_clone_payload_Primitive_18);
    return hoisted__Type_1367;
}

U32 Type_size(void) {
    I64 hoisted__I64_1368 = 24;
    return hoisted__I64_1368;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_2511 = Str_is_empty(elem_type);
    if (hoisted__Bool_2511) {
        Str hoisted__Str_2505 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2506 = Type_Struct(&hoisted__Str_2505);
        Str_delete(&hoisted__Str_2505, &(Bool){0});
        U32 hoisted__U32_2507 = 1;
        Array *_va_Array_74 = Array_new(hoisted__Type_2506, &hoisted__U32_2507);
        (void)_va_Array_74;
        Type_delete(hoisted__Type_2506, &(Bool){1});
        U32 hoisted__U32_2508 = 0;
        Str hoisted__Str_2509 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_74, &hoisted__U32_2508, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2509; _oa; }));
        Str hoisted__Str_2510 = (Str){.c_str = (void *)"./src/core/array.til:23:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2510, _va_Array_74);
        Str_delete(&hoisted__Str_2510, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_2512 = calloc(DEREF(cap), elem_size);
    void * hoisted__v_2513 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    void * hoisted__v_2514 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    Array *hoisted__Array_2515 = malloc(sizeof(Array));
    hoisted__Array_2515->data = hoisted__v_2512;
    hoisted__Array_2515->cap = DEREF(cap);
    hoisted__Array_2515->elem_size = elem_size;
    { Str *_ca = Str_clone(elem_type); hoisted__Array_2515->elem_type = *_ca; free(_ca); }
    hoisted__Array_2515->elem_clone = hoisted__v_2513;
    hoisted__Array_2515->elem_delete = hoisted__v_2514;
    return hoisted__Array_2515;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_2516 = Array_new_type_name(elem_type, cap);
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_2516;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap; return _r; }
}

void * Array_get(Array * self, U32 * i) {
    Bool hoisted__Bool_2531 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2531) {
        Str hoisted__Str_2517 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2518 = Type_Struct(&hoisted__Str_2517);
        Str_delete(&hoisted__Str_2517, &(Bool){0});
        U32 hoisted__U32_2519 = 5;
        Array *_va_Array_75 = Array_new(hoisted__Type_2518, &hoisted__U32_2519);
        (void)_va_Array_75;
        Type_delete(hoisted__Type_2518, &(Bool){1});
        U32 hoisted__U32_2520 = 0;
        Str hoisted__Str_2521 = (Str){.c_str = (void *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_75, &hoisted__U32_2520, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2521; _oa; }));
        U32 hoisted__U32_2522 = 1;
        Str *hoisted__Str_2523 = U32_to_str(i);
        Array_set(_va_Array_75, &hoisted__U32_2522, hoisted__Str_2523);
        U32 hoisted__U32_2524 = 2;
        Str hoisted__Str_2525 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_75, &hoisted__U32_2524, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2525; _oa; }));
        U32 hoisted__U32_2526 = 3;
        Str *hoisted__Str_2527 = U32_to_str(&self->cap);
        Array_set(_va_Array_75, &hoisted__U32_2526, hoisted__Str_2527);
        U32 hoisted__U32_2528 = 4;
        Str hoisted__Str_2529 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_75, &hoisted__U32_2528, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2529; _oa; }));
        Str hoisted__Str_2530 = (Str){.c_str = (void *)"./src/core/array.til:41:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2530, _va_Array_75);
        Str_delete(&hoisted__Str_2530, &(Bool){0});
    }
    U32 hoisted__U64_2532 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2533 = ptr_add(self->data, hoisted__U64_2532);
    return hoisted__v_2533;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_2548 = U32_gte(i, &self->cap);
    if (hoisted__Bool_2548) {
        Str hoisted__Str_2534 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2535 = Type_Struct(&hoisted__Str_2534);
        Str_delete(&hoisted__Str_2534, &(Bool){0});
        U32 hoisted__U32_2536 = 5;
        Array *_va_Array_76 = Array_new(hoisted__Type_2535, &hoisted__U32_2536);
        (void)_va_Array_76;
        Type_delete(hoisted__Type_2535, &(Bool){1});
        U32 hoisted__U32_2537 = 0;
        Str hoisted__Str_2538 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_76, &hoisted__U32_2537, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2538; _oa; }));
        U32 hoisted__U32_2539 = 1;
        Str *hoisted__Str_2540 = U32_to_str(i);
        Array_set(_va_Array_76, &hoisted__U32_2539, hoisted__Str_2540);
        U32 hoisted__U32_2541 = 2;
        Str hoisted__Str_2542 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_76, &hoisted__U32_2541, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2542; _oa; }));
        U32 hoisted__U32_2543 = 3;
        Str *hoisted__Str_2544 = U32_to_str(&self->cap);
        Array_set(_va_Array_76, &hoisted__U32_2543, hoisted__Str_2544);
        U32 hoisted__U32_2545 = 4;
        Str hoisted__Str_2546 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_76, &hoisted__U32_2545, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2546; _oa; }));
        Str hoisted__Str_2547 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        panic(&hoisted__Str_2547, _va_Array_76);
        Str_delete(&hoisted__Str_2547, &(Bool){0});
    }
    U32 hoisted__U64_2549 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2550 = ptr_add(self->data, hoisted__U64_2549);
    Bool hoisted__Bool_2551 = 0;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2550, &hoisted__Bool_2551);
    U32 hoisted__U64_2552 = U32_mul(DEREF(i), self->elem_size);
    void *hoisted__v_2553 = ptr_add(self->data, hoisted__U64_2552);
    memcpy(hoisted__v_2553, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_2554 = self->cap;
        (void)_re_U32_2554;
        U32 _rc_U32_2554 = 0;
        (void)_rc_U32_2554;
        Bool hoisted__Bool_2563 = U32_lte(&_rc_U32_2554, &_re_U32_2554);
        if (hoisted__Bool_2563) {
            while (1) {
                Bool _wcond_Bool_2555 = U32_lt(&_rc_U32_2554, &_re_U32_2554);
                (void)_wcond_Bool_2555;
                if (_wcond_Bool_2555) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2554);
                U32_inc(&_rc_U32_2554);
                U32 hoisted__U64_2556 = U32_mul(i, self->elem_size);
                void *hoisted__v_2557 = ptr_add(self->data, hoisted__U64_2556);
                Bool hoisted__Bool_2558 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2557, &hoisted__Bool_2558);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2559 = U32_gt(&_rc_U32_2554, &_re_U32_2554);
                (void)_wcond_Bool_2559;
                if (_wcond_Bool_2559) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2554);
                U32_dec(&_rc_U32_2554);
                U32 hoisted__U64_2560 = U32_mul(i, self->elem_size);
                void *hoisted__v_2561 = ptr_add(self->data, hoisted__U64_2560);
                Bool hoisted__Bool_2562 = 0;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_2561, &hoisted__Bool_2562);
            }
        }
    }
    free(self->data);
    Bool hoisted__Bool_2564 = 0;
    Str_delete(&self->elem_type, &hoisted__Bool_2564);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_2577 = U32_mul(self->cap, self->elem_size);
    void * new_data = malloc(hoisted__U64_2577);
    {
        U32 _re_U32_2565 = self->cap;
        (void)_re_U32_2565;
        U32 _rc_U32_2565 = 0;
        (void)_rc_U32_2565;
        Bool hoisted__Bool_2576 = U32_lte(&_rc_U32_2565, &_re_U32_2565);
        if (hoisted__Bool_2576) {
            while (1) {
                Bool _wcond_Bool_2566 = U32_lt(&_rc_U32_2565, &_re_U32_2565);
                (void)_wcond_Bool_2566;
                if (_wcond_Bool_2566) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2565);
                U32_inc(&_rc_U32_2565);
                U32 hoisted__U64_2567 = U32_mul(i, self->elem_size);
                void *hoisted__v_2568 = ptr_add(self->data, hoisted__U64_2567);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2568);
                U32 hoisted__U64_2569 = U32_mul(i, self->elem_size);
                void *hoisted__v_2570 = ptr_add(new_data, hoisted__U64_2569);
                memcpy(hoisted__v_2570, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_2571 = U32_gt(&_rc_U32_2565, &_re_U32_2565);
                (void)_wcond_Bool_2571;
                if (_wcond_Bool_2571) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_2565);
                U32_dec(&_rc_U32_2565);
                U32 hoisted__U64_2572 = U32_mul(i, self->elem_size);
                void *hoisted__v_2573 = ptr_add(self->data, hoisted__U64_2572);
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_2573);
                U32 hoisted__U64_2574 = U32_mul(i, self->elem_size);
                void *hoisted__v_2575 = ptr_add(new_data, hoisted__U64_2574);
                memcpy(hoisted__v_2575, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_2578 = malloc(sizeof(Array));
    hoisted__Array_2578->data = new_data;
    hoisted__Array_2578->cap = self->cap;
    hoisted__Array_2578->elem_size = self->elem_size;
    { Str *_ca = Str_clone(&self->elem_type); hoisted__Array_2578->elem_type = *_ca; free(_ca); }
    hoisted__Array_2578->elem_clone = (void *)self->elem_clone;
    hoisted__Array_2578->elem_delete = (void *)self->elem_delete;
    return hoisted__Array_2578;
}

U32 Array_size(void) {
    I64 hoisted__I64_2579 = 48;
    return hoisted__I64_2579;
}

void panic(Str * loc_str, Array * parts) {
    Str hoisted__Str_2818 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_2819 = Type_Struct(&hoisted__Str_2818);
    Str_delete(&hoisted__Str_2818, &(Bool){0});
    U32 hoisted__U32_2820 = 3;
    Array *_va_Array_93 = Array_new(hoisted__Type_2819, &hoisted__U32_2820);
    (void)_va_Array_93;
    Type_delete(hoisted__Type_2819, &(Bool){1});
    U32 hoisted__U32_2821 = 0;
    Str *hoisted__Str_2822 = Str_clone(loc_str);
    Array_set(_va_Array_93, &hoisted__U32_2821, hoisted__Str_2822);
    U32 hoisted__U32_2823 = 1;
    Str hoisted__Str_2824 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_93, &hoisted__U32_2823, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2824; _oa; }));
    Array *hoisted__Array_2825 = Array_clone(parts);
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_2826 = 2;
    Str *hoisted__Str_2827 = format(hoisted__Array_2825);
    Array_set(_va_Array_93, &hoisted__U32_2826, hoisted__Str_2827);
    println(_va_Array_93);
    I64 hoisted__I64_2828 = 1;
    exit(hoisted__I64_2828);
}

void UNREACHABLE(Str * loc_str) {
    Str hoisted__Str_2837 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    Type *hoisted__Type_2838 = Type_Struct(&hoisted__Str_2837);
    Str_delete(&hoisted__Str_2837, &(Bool){0});
    U32 hoisted__U32_2839 = 1;
    Array *_va_Array_95 = Array_new(hoisted__Type_2838, &hoisted__U32_2839);
    (void)_va_Array_95;
    Type_delete(hoisted__Type_2838, &(Bool){1});
    U32 hoisted__U32_2840 = 0;
    Str hoisted__Str_2841 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    Array_set(_va_Array_95, &hoisted__U32_2840, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2841; _oa; }));
    panic(loc_str, _va_Array_95);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_2847 = not(DEREF(cond));
    if (hoisted__Bool_2847) {
        Str hoisted__Str_2842 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2843 = Type_Struct(&hoisted__Str_2842);
        Str_delete(&hoisted__Str_2842, &(Bool){0});
        U32 hoisted__U32_2844 = 1;
        Array *_va_Array_96 = Array_new(hoisted__Type_2843, &hoisted__U32_2844);
        (void)_va_Array_96;
        Type_delete(hoisted__Type_2843, &(Bool){1});
        U32 hoisted__U32_2845 = 0;
        Str hoisted__Str_2846 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_96, &hoisted__U32_2845, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2846; _oa; }));
        panic(loc_str, _va_Array_96);
    }
    Bool hoisted__Bool_2848 = 1;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_2848; return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_2871 = I64_neq(a, b);
    if (hoisted__Bool_2871) {
        Str hoisted__Str_2858 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2859 = Type_Struct(&hoisted__Str_2858);
        Str_delete(&hoisted__Str_2858, &(Bool){0});
        U32 hoisted__U32_2860 = 5;
        Array *_va_Array_98 = Array_new(hoisted__Type_2859, &hoisted__U32_2860);
        (void)_va_Array_98;
        Type_delete(hoisted__Type_2859, &(Bool){1});
        U32 hoisted__U32_2861 = 0;
        Str hoisted__Str_2862 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_98, &hoisted__U32_2861, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2862; _oa; }));
        U32 hoisted__U32_2863 = 1;
        Str *hoisted__Str_2864 = I64_to_str(a);
        Array_set(_va_Array_98, &hoisted__U32_2863, hoisted__Str_2864);
        U32 hoisted__U32_2865 = 2;
        Str hoisted__Str_2866 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_98, &hoisted__U32_2865, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2866; _oa; }));
        U32 hoisted__U32_2867 = 3;
        Str *hoisted__Str_2868 = I64_to_str(b);
        Array_set(_va_Array_98, &hoisted__U32_2867, hoisted__Str_2868);
        U32 hoisted__U32_2869 = 4;
        Str hoisted__Str_2870 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_98, &hoisted__U32_2869, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2870; _oa; }));
        panic(loc_str, _va_Array_98);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_2885 = Str_eq(a, b);
    Bool hoisted__Bool_2886 = not(hoisted__Bool_2885);
    if (hoisted__Bool_2886) {
        Str hoisted__Str_2872 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        Type *hoisted__Type_2873 = Type_Struct(&hoisted__Str_2872);
        Str_delete(&hoisted__Str_2872, &(Bool){0});
        U32 hoisted__U32_2874 = 5;
        Array *_va_Array_99 = Array_new(hoisted__Type_2873, &hoisted__U32_2874);
        (void)_va_Array_99;
        Type_delete(hoisted__Type_2873, &(Bool){1});
        U32 hoisted__U32_2875 = 0;
        Str hoisted__Str_2876 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_99, &hoisted__U32_2875, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2876; _oa; }));
        U32 hoisted__U32_2877 = 1;
        Str *hoisted__Str_2878 = Str_clone(a);
        Array_set(_va_Array_99, &hoisted__U32_2877, hoisted__Str_2878);
        U32 hoisted__U32_2879 = 2;
        Str hoisted__Str_2880 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_99, &hoisted__U32_2879, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2880; _oa; }));
        U32 hoisted__U32_2881 = 3;
        Str *hoisted__Str_2882 = Str_clone(b);
        Array_set(_va_Array_99, &hoisted__U32_2881, hoisted__Str_2882);
        U32 hoisted__U32_2883 = 4;
        Str hoisted__Str_2884 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array_set(_va_Array_99, &hoisted__U32_2883, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_2884; _oa; }));
        panic(loc_str, _va_Array_99);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_2887 = parts;
        (void)_fc_Array_2887;
        (void)_fc_Array_2887;
        U32 _fi_USize_2887 = 0;
        (void)_fi_USize_2887;
        while (1) {
            U32 hoisted__U32_2889; { U32 *_hp = (U32 *)Array_len(_fc_Array_2887); hoisted__U32_2889 = *_hp; free(_hp); }
            Bool _wcond_Bool_2888 = U32_lt(&_fi_USize_2887, &hoisted__U32_2889);
            (void)_wcond_Bool_2888;
            if (_wcond_Bool_2888) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_2887, &_fi_USize_2887);
            U32 hoisted__U32_2890 = 1;
            U32 hoisted__U32_2891 = U32_add(_fi_USize_2887, hoisted__U32_2890);
            _fi_USize_2887 = hoisted__U32_2891;
            print_single(s);
        }
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_3085 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3086 = 3;
    assert_eq(&hoisted__Str_3085, &result, &hoisted__I64_3086);
    Str_delete(&hoisted__Str_3085, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_3093 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3094 = 15;
    assert_eq(&hoisted__Str_3093, &result, &hoisted__I64_3094);
    Str_delete(&hoisted__Str_3093, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_3101 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3102 = 26;
    assert_eq(&hoisted__Str_3101, &result, &hoisted__I64_3102);
    Str_delete(&hoisted__Str_3101, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3105 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3106 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3105, &result, &hoisted__Str_3106);
    Str_delete(&hoisted__Str_3105, &(Bool){0});
    Str_delete(&hoisted__Str_3106, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_3437 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3437, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_3437, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_3438 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    assert_eq_str(&hoisted__Str_3438, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_3438, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_3440 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3441 = 8;
    assert_eq(&hoisted__Str_3440, &result, &hoisted__I64_3441);
    Str_delete(&hoisted__Str_3440, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_3444 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3445 = 1;
    Bool_delete(assert(&hoisted__Str_3444, &hoisted__Bool_3445), &(Bool){1});
    Str_delete(&hoisted__Str_3444, &(Bool){0});
    Str hoisted__Str_3449 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3450 = 1;
    Bool_delete(assert(&hoisted__Str_3449, &hoisted__Bool_3450), &(Bool){1});
    Str_delete(&hoisted__Str_3449, &(Bool){0});
}

CfVec2 * CfVec2_magic(void) {
    I64 hoisted__I64_3452 = 42;
    I64 hoisted__I64_3453 = 99;
    CfVec2 hoisted__CfVec2_3454 = (CfVec2){.x = hoisted__I64_3452, .y = hoisted__I64_3453};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3454; return _r; }
}

CfVec2 * CfVec2_at(I64 * x, I64 * y) {
    CfVec2 hoisted__CfVec2_3455 = (CfVec2){.x = DEREF(x), .y = DEREF(y)};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3455; return _r; }
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    I64 hoisted__I64_3456 = I64_clone(&self->x);
    I64 hoisted__I64_3457 = I64_clone(&self->y);
    CfVec2 hoisted__CfVec2_3458 = (CfVec2){.x = hoisted__I64_3456, .y = hoisted__I64_3457};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_3458; return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    Bool hoisted__Bool_3459 = 0;
    I64_delete(&self->x, &hoisted__Bool_3459);
    Bool hoisted__Bool_3460 = 0;
    I64_delete(&self->y, &hoisted__Bool_3460);
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    I64 hoisted__I64_3461 = 16;
    return hoisted__I64_3461;
}

void test_struct_fold_simple(void) {
    CfVec2 *v = CfVec2_magic();
    Str hoisted__Str_3462 = (Str){.c_str = (void *)"test/constfold.til:122:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3463 = 42;
    assert_eq(&hoisted__Str_3462, &v->x, &hoisted__I64_3463);
    Str_delete(&hoisted__Str_3462, &(Bool){0});
    Str hoisted__Str_3464 = (Str){.c_str = (void *)"test/constfold.til:123:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3465 = 99;
    assert_eq(&hoisted__Str_3464, &v->y, &hoisted__I64_3465);
    Str_delete(&hoisted__Str_3464, &(Bool){0});
    CfVec2_delete(v, &(Bool){1});
}

void test_struct_fold_values(void) {
    I64 hoisted__I64_3466 = 10;
    I64 hoisted__I64_3467 = 20;
    CfVec2 *p = CfVec2_at(&hoisted__I64_3466, &hoisted__I64_3467);
    Str hoisted__Str_3468 = (Str){.c_str = (void *)"test/constfold.til:129:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3469 = 10;
    assert_eq(&hoisted__Str_3468, &p->x, &hoisted__I64_3469);
    Str_delete(&hoisted__Str_3468, &(Bool){0});
    Str hoisted__Str_3470 = (Str){.c_str = (void *)"test/constfold.til:130:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3471 = 20;
    assert_eq(&hoisted__Str_3470, &p->y, &hoisted__I64_3471);
    Str_delete(&hoisted__Str_3470, &(Bool){0});
    CfVec2_delete(p, &(Bool){1});
}

CfRect * CfRect_sample(void) {
    I64 hoisted__I64_3472 = 5;
    I64 hoisted__I64_3473 = 10;
    I64 hoisted__I64_3474 = 100;
    I64 hoisted__I64_3475 = 200;
    CfRect hoisted__CfRect_3476 = (CfRect){.top_left = (CfVec2){.x = hoisted__I64_3472, .y = hoisted__I64_3473}, .bottom_right = (CfVec2){.x = hoisted__I64_3474, .y = hoisted__I64_3475}};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_3476; return _r; }
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect *hoisted__CfRect_3477 = malloc(sizeof(CfRect));
    { CfVec2 *_ca = CfVec2_clone(&self->top_left); hoisted__CfRect_3477->top_left = *_ca; free(_ca); }
    { CfVec2 *_ca = CfVec2_clone(&self->bottom_right); hoisted__CfRect_3477->bottom_right = *_ca; free(_ca); }
    return hoisted__CfRect_3477;
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    Bool hoisted__Bool_3478 = 0;
    CfVec2_delete(&self->top_left, &hoisted__Bool_3478);
    Bool hoisted__Bool_3479 = 0;
    CfVec2_delete(&self->bottom_right, &hoisted__Bool_3479);
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    I64 hoisted__I64_3480 = 32;
    return hoisted__I64_3480;
}

void test_struct_fold_nested(void) {
    CfRect *r = CfRect_sample();
    Str hoisted__Str_3481 = (Str){.c_str = (void *)"test/constfold.til:146:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3482 = 5;
    assert_eq(&hoisted__Str_3481, &r->top_left.x, &hoisted__I64_3482);
    Str_delete(&hoisted__Str_3481, &(Bool){0});
    Str hoisted__Str_3483 = (Str){.c_str = (void *)"test/constfold.til:147:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3484 = 10;
    assert_eq(&hoisted__Str_3483, &r->top_left.y, &hoisted__I64_3484);
    Str_delete(&hoisted__Str_3483, &(Bool){0});
    Str hoisted__Str_3485 = (Str){.c_str = (void *)"test/constfold.til:148:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3486 = 100;
    assert_eq(&hoisted__Str_3485, &r->bottom_right.x, &hoisted__I64_3486);
    Str_delete(&hoisted__Str_3485, &(Bool){0});
    Str hoisted__Str_3487 = (Str){.c_str = (void *)"test/constfold.til:149:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    I64 hoisted__I64_3488 = 200;
    assert_eq(&hoisted__Str_3487, &r->bottom_right.y, &hoisted__I64_3488);
    Str_delete(&hoisted__Str_3487, &(Bool){0});
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
    Bool hoisted__Bool_3493 = is(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3493) {
        Bool hoisted__Bool_3490 = is(other, &(Color){.tag = Color_TAG_Red});
        return hoisted__Bool_3490;
    }
    Bool hoisted__Bool_3494 = is(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3494) {
        Bool hoisted__Bool_3491 = is(other, &(Color){.tag = Color_TAG_Green});
        return hoisted__Bool_3491;
    }
    Bool hoisted__Bool_3495 = is(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3495) {
        Bool hoisted__Bool_3492 = is(other, &(Color){.tag = Color_TAG_Blue});
        return hoisted__Bool_3492;
    }
    Bool hoisted__Bool_3496 = 0;
    return hoisted__Bool_3496;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_3504 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_3504) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
    }
    Bool hoisted__Bool_3505 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_3505) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green; return _r; }
    }
    Bool hoisted__Bool_3506 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_3506) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue; return _r; }
    }
    Str hoisted__Str_3507 = (Str){.c_str = (void *)"Color.clone:154:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_3507);
    Str_delete(&hoisted__Str_3507, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red; return _r; }
}

U32 Color_size(void) {
    I64 hoisted__I64_3508 = 4;
    return hoisted__I64_3508;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_3509 = (Str){.c_str = (void *)"test/constfold.til:159:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3510 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool_delete(assert(&hoisted__Str_3509, &hoisted__Bool_3510), &(Bool){1});
    Str_delete(&hoisted__Str_3509, &(Bool){0});
    Bool hoisted__Bool_3512 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Color_delete(&c, &(Bool){0});
    Str hoisted__Str_3513 = (Str){.c_str = (void *)"test/constfold.til:160:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3514 = not(hoisted__Bool_3512);
    Bool_delete(assert(&hoisted__Str_3513, &hoisted__Bool_3514), &(Bool){1});
    Str_delete(&hoisted__Str_3513, &(Bool){0});
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
    Bool hoisted__Bool_3516 = is(self, other);
    return hoisted__Bool_3516;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_3534 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3534) {
        I64 *hoisted__I64_3530 = get_payload(self);
        Bool hoisted__Bool_3531 = 0;
        I64_delete(hoisted__I64_3530, &hoisted__Bool_3531);
    }
    Bool hoisted__Bool_3535 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3535) {
        Str *hoisted__Str_3532 = get_payload(self);
        Bool hoisted__Bool_3533 = 0;
        Str_delete(hoisted__Str_3532, &hoisted__Bool_3533);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_3563 = is(self, &(Token){.tag = Token_TAG_Num});
    if (hoisted__Bool_3563) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_3561 = Token_Num(_clone_payload_Num_0);
        return hoisted__Token_3561;
    }
    Bool hoisted__Bool_3564 = is(self, &(Token){.tag = Token_TAG_Name});
    if (hoisted__Bool_3564) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Token *hoisted__Token_3562 = Token_Name(_clone_payload_Name_1);
        return hoisted__Token_3562;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof; return _r; }
}

U32 Token_size(void) {
    I64 hoisted__I64_3565 = 24;
    return hoisted__I64_3565;
}


void test_enum_payload_fold(void) {
    I64 hoisted__I64_3566 = 42;
    Token t; { Token *_hp = (Token *)Token_Num(&hoisted__I64_3566); t = *_hp; free(_hp); }
    Str hoisted__Str_3567 = (Str){.c_str = (void *)"test/constfold.til:168:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3568 = Token_is(&t, &(Token){.tag = Token_TAG_Num});
    Bool_delete(assert(&hoisted__Str_3567, &hoisted__Bool_3568), &(Bool){1});
    Str_delete(&hoisted__Str_3567, &(Bool){0});
    Bool hoisted__Bool_3570 = Token_is(&t, &(Token){.tag = Token_TAG_Eof});
    Token_delete(&t, &(Bool){0});
    Str hoisted__Str_3571 = (Str){.c_str = (void *)"test/constfold.til:169:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    Bool hoisted__Bool_3572 = not(hoisted__Bool_3570);
    Bool_delete(assert(&hoisted__Str_3571, &hoisted__Bool_3572), &(Bool){1});
    Str_delete(&hoisted__Str_3571, &(Bool){0});
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
    I64 hoisted__I64_895 = 0;
    I64 hoisted__I64_896 = 1;
    I64 hoisted__I64_897 = I64_sub(hoisted__I64_895, hoisted__I64_896);
    CAP_LIT = I64_to_usize(hoisted__I64_897);
    I64 hoisted__I64_898 = 0;
    I64 hoisted__I64_899 = 2;
    I64 hoisted__I64_900 = I64_sub(hoisted__I64_898, hoisted__I64_899);
    CAP_VIEW = I64_to_usize(hoisted__I64_900);
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
