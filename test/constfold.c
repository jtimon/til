#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef struct Str Str;
typedef struct OutOfBounds OutOfBounds;
typedef struct Dynamic Dynamic;
typedef enum {
    Primitive_TAG_I16,
    Primitive_TAG_U16
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


typedef struct OutOfBounds {
    Str msg;
} OutOfBounds;


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

void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
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
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool * call_free);
U32 OutOfBounds_size(void);
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
void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
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
void swap(void * a, void * b, U64 size);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
void test_fold_f32(void);
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool * call_free);
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
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
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
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

void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
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
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool * call_free);
U32 OutOfBounds_size(void);
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
void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
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
void swap(void * a, void * b, U64 size);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
void test_fold_f32(void);
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool * call_free);
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
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
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
Bool Primitive_eq(Primitive *, Primitive *);
Primitive *Primitive_I16();
Primitive *Primitive_U16();
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
I64 enum_variant_count(Str *type_name);
Str *enum_variant_name(Str *type_name, I64 *index);
I64 enum_variant_has_payload(Str *type_name, I64 *index);
Str *enum_variant_payload_type(Str *type_name, I64 *index);
I64 func_sig_param_count(Str *type_name);
Str *func_sig_param_type(Str *type_name, I64 *index);
I64 func_sig_return_count(Str *type_name);
Str *func_sig_return_type(Str *type_name, I64 *index);
I64 func_sig_throw_count(Str *type_name);
Str *func_sig_throw_type(Str *type_name, I64 *index);
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

void F32_delete(F32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * F32_size(void) {
    U32 hoisted__U32_1 = 4;
    (void)hoisted__U32_1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1;
    return _r; }
}

void U64_delete(U64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U64_size(void) {
    U32 hoisted__U32_35 = 8;
    (void)hoisted__U32_35;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_35;
    return _r; }
}

Str * U32_to_str(U32 * val) {
    I64 hoisted__I64_123 = U32_to_i64(DEREF(val));
    (void)hoisted__I64_123;
    Str *hoisted__Str_124 = I64_to_str(&hoisted__I64_123);
    (void)hoisted__Str_124;
    return hoisted__Str_124;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_125 = 1;
    (void)hoisted__U32_125;
    U32 hoisted__U32_126 = U32_add(DEREF(self), hoisted__U32_125);
    (void)hoisted__U32_126;
    *self = hoisted__U32_126;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_127 = 1;
    (void)hoisted__U32_127;
    U32 hoisted__U32_128 = U32_sub(DEREF(self), hoisted__U32_127);
    (void)hoisted__U32_128;
    *self = hoisted__U32_128;
}

void U32_delete(U32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U32_size(void) {
    U32 hoisted__U32_135 = 4;
    (void)hoisted__U32_135;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_135;
    return _r; }
}

Bool U32_lt(U32 * a, U32 * b) {
    I64 hoisted__I64_211 = U32_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_211;
    I64 hoisted__I64_212 = -1;
    (void)hoisted__I64_212;
    Bool hoisted__Bool_213 = I64_eq(hoisted__I64_211, hoisted__I64_212);
    (void)hoisted__Bool_213;
    return hoisted__Bool_213;
}

Bool U32_gt(U32 * a, U32 * b) {
    I64 hoisted__I64_214 = U32_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_214;
    I64 hoisted__I64_215 = 1;
    (void)hoisted__I64_215;
    Bool hoisted__Bool_216 = I64_eq(hoisted__I64_214, hoisted__I64_215);
    (void)hoisted__Bool_216;
    return hoisted__Bool_216;
}

Bool U32_lte(U32 * a, U32 * b) {
    Bool hoisted__Bool_219 = U32_gt(a, b);
    (void)hoisted__Bool_219;
    Bool hoisted__Bool_220 = not(hoisted__Bool_219);
    (void)hoisted__Bool_220;
    return hoisted__Bool_220;
}

Bool U32_gte(U32 * a, U32 * b) {
    Bool hoisted__Bool_221 = U32_lt(a, b);
    (void)hoisted__Bool_221;
    Bool hoisted__Bool_222 = not(hoisted__Bool_221);
    (void)hoisted__Bool_222;
    return hoisted__Bool_222;
}

void I32_delete(I32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I32_size(void) {
    U32 hoisted__U32_247 = 4;
    (void)hoisted__U32_247;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_247;
    return _r; }
}

void I8_delete(I8 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I8_size(void) {
    U32 hoisted__U32_412 = 1;
    (void)hoisted__U32_412;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_412;
    return _r; }
}

void U8_delete(U8 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U8_size(void) {
    U32 hoisted__U32_439 = 1;
    (void)hoisted__U32_439;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_439;
    return _r; }
}

Str * format(Array * parts) {
    U32 total = 0;
    {
        Array *_fc_Array_795 = parts;
        (void)_fc_Array_795;
        (void)_fc_Array_795;
        U32 _fi_USize_795 = 0;
        (void)_fi_USize_795;
        I64 _forin_err_kind_795 = 0;
        (void)_forin_err_kind_795;
        OutOfBounds *_forin_OutOfBounds_795 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_795->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_795;
        while (1) {
            U32 hoisted__U32_803; { U32 *_hp = (U32 *)Array_len(_fc_Array_795); hoisted__U32_803 = *_hp; free(_hp); }
            (void)hoisted__U32_803;
            Bool _wcond_Bool_796 = U32_lt(&_fi_USize_795, &hoisted__U32_803);
            (void)_wcond_Bool_796;
            if (_wcond_Bool_796) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_795, &_fi_USize_795, &_forin_err_kind_795, _forin_OutOfBounds_795);
            I64 hoisted__I64_804 = 0;
            (void)hoisted__I64_804;
            Bool hoisted__Bool_805 = I64_eq(_forin_err_kind_795, hoisted__I64_804);
            (void)hoisted__Bool_805;
            Bool hoisted__Bool_806 = not(hoisted__Bool_805);
            (void)hoisted__Bool_806;
            if (hoisted__Bool_806) {
                Type *hoisted__Type_798 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_798;
                U32 hoisted__U32_799 = 1;
                (void)hoisted__U32_799;
                Array *_va_Array_24 = Array_new(hoisted__Type_798, &hoisted__U32_799);
                (void)_va_Array_24;
                Type_delete(hoisted__Type_798, &(Bool){1});
                U32 hoisted__U32_800 = 0;
                (void)hoisted__U32_800;
                Str hoisted__Str_801 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_801;
                Array_set(_va_Array_24, &hoisted__U32_800, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_801; _oa; }));
                Str hoisted__Str_802 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_802;
                panic(&hoisted__Str_802, _va_Array_24);
                Str_delete(&hoisted__Str_802, &(Bool){0});
            }
            U32 hoisted__U32_807 = 1;
            (void)hoisted__U32_807;
            U32 hoisted__U32_808 = U32_add(_fi_USize_795, hoisted__U32_807);
            (void)hoisted__U32_808;
            _fi_USize_795 = hoisted__U32_808;
            U32 hoisted__U32_809 = Str_len(s);
            (void)hoisted__U32_809;
            U32 hoisted__U32_810 = U32_add(total, hoisted__U32_809);
            (void)hoisted__U32_810;
            total = hoisted__U32_810;
        }
        OutOfBounds_delete(_forin_OutOfBounds_795, &(Bool){1});
    }
    Str *out = Str_with_capacity(&total);
    {
        Array *_fc_Array_811 = parts;
        (void)_fc_Array_811;
        (void)_fc_Array_811;
        U32 _fi_USize_811 = 0;
        (void)_fi_USize_811;
        I64 _forin_err_kind_811 = 0;
        (void)_forin_err_kind_811;
        OutOfBounds *_forin_OutOfBounds_811 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_811->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_811;
        while (1) {
            U32 hoisted__U32_819; { U32 *_hp = (U32 *)Array_len(_fc_Array_811); hoisted__U32_819 = *_hp; free(_hp); }
            (void)hoisted__U32_819;
            Bool _wcond_Bool_812 = U32_lt(&_fi_USize_811, &hoisted__U32_819);
            (void)_wcond_Bool_812;
            if (_wcond_Bool_812) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_811, &_fi_USize_811, &_forin_err_kind_811, _forin_OutOfBounds_811);
            I64 hoisted__I64_820 = 0;
            (void)hoisted__I64_820;
            Bool hoisted__Bool_821 = I64_eq(_forin_err_kind_811, hoisted__I64_820);
            (void)hoisted__Bool_821;
            Bool hoisted__Bool_822 = not(hoisted__Bool_821);
            (void)hoisted__Bool_822;
            if (hoisted__Bool_822) {
                Type *hoisted__Type_814 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_814;
                U32 hoisted__U32_815 = 1;
                (void)hoisted__U32_815;
                Array *_va_Array_25 = Array_new(hoisted__Type_814, &hoisted__U32_815);
                (void)_va_Array_25;
                Type_delete(hoisted__Type_814, &(Bool){1});
                U32 hoisted__U32_816 = 0;
                (void)hoisted__U32_816;
                Str hoisted__Str_817 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_817;
                Array_set(_va_Array_25, &hoisted__U32_816, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_817; _oa; }));
                Str hoisted__Str_818 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_818;
                panic(&hoisted__Str_818, _va_Array_25);
                Str_delete(&hoisted__Str_818, &(Bool){0});
            }
            U32 hoisted__U32_823 = 1;
            (void)hoisted__U32_823;
            U32 hoisted__U32_824 = U32_add(_fi_USize_811, hoisted__U32_823);
            (void)hoisted__U32_824;
            _fi_USize_811 = hoisted__U32_824;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_811, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_831 = U32_gte(i, &self->count);
    (void)hoisted__Bool_831;
    if (hoisted__Bool_831) {
        Type *hoisted__Type_826 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_826;
        U32 hoisted__U32_827 = 1;
        (void)hoisted__U32_827;
        Array *_va_Array_26 = Array_new(hoisted__Type_826, &hoisted__U32_827);
        (void)_va_Array_26;
        Type_delete(hoisted__Type_826, &(Bool){1});
        U32 hoisted__U32_828 = 0;
        (void)hoisted__U32_828;
        Str hoisted__Str_829 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_829;
        Array_set(_va_Array_26, &hoisted__U32_828, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_829; _oa; }));
        Str hoisted__Str_830 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_830;
        panic(&hoisted__Str_830, _va_Array_26);
        Str_delete(&hoisted__Str_830, &(Bool){0});
    }
    void *hoisted__v_832 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_832;
    (void)hoisted__v_832;
    return hoisted__v_832;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_842 = U32_lt(&b->count, &a->count);
    (void)hoisted__Bool_842;
    if (hoisted__Bool_842) {
        min_len = b->count;
    }
    {
        U32 _re_U32_834 = U32_clone(&min_len);
        (void)_re_U32_834;
        U32 _rc_U32_834 = 0;
        (void)_rc_U32_834;
        Bool hoisted__Bool_841 = U32_lte(&_rc_U32_834, &_re_U32_834);
        (void)hoisted__Bool_841;
        if (hoisted__Bool_841) {
            while (1) {
                Bool _wcond_Bool_835 = U32_lt(&_rc_U32_834, &_re_U32_834);
                (void)_wcond_Bool_835;
                if (_wcond_Bool_835) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_834);
                U32_inc(&_rc_U32_834);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_836 = 0;
                (void)hoisted__I64_836;
                Bool hoisted__Bool_837 = I64_neq(&c, &hoisted__I64_836);
                (void)hoisted__Bool_837;
                if (hoisted__Bool_837) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_838 = U32_gt(&_rc_U32_834, &_re_U32_834);
                (void)_wcond_Bool_838;
                if (_wcond_Bool_838) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_834);
                U32_dec(&_rc_U32_834);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_839 = 0;
                (void)hoisted__I64_839;
                Bool hoisted__Bool_840 = I64_neq(&c, &hoisted__I64_839);
                (void)hoisted__Bool_840;
                if (hoisted__Bool_840) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_843 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_843;
    return hoisted__I64_843;
}

Str * Str_with_capacity(U32 * n) {
    U32 hoisted__U32_845 = 1;
    (void)hoisted__U32_845;
    U32 hoisted__U64_846 = U32_add(DEREF(n), hoisted__U32_845);
    (void)hoisted__U64_846;
    void * buf = malloc(hoisted__U64_846);
    I32 hoisted__I32_847 = 0;
    (void)hoisted__I32_847;
    U64 hoisted__U64_848 = 1ULL;
    (void)hoisted__U64_848;
    memset(buf, hoisted__I32_847, hoisted__U64_848);
    I32_delete(&hoisted__I32_847, &(Bool){0});
    I64 hoisted__I64_849 = 0;
    (void)hoisted__I64_849;
    Str *hoisted__Str_850 = malloc(sizeof(Str));
    hoisted__Str_850->c_str = buf;
    hoisted__Str_850->count = hoisted__I64_849;
    hoisted__Str_850->cap = DEREF(n);
    (void)hoisted__Str_850;
    return hoisted__Str_850;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_865 = U32_gte(&self->cap, &CAP_VIEW);
    (void)hoisted__Bool_865;
    if (hoisted__Bool_865) {
        Type *hoisted__Type_854 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_854;
        U32 hoisted__U32_855 = 1;
        (void)hoisted__U32_855;
        Array *_va_Array_27 = Array_new(hoisted__Type_854, &hoisted__U32_855);
        (void)_va_Array_27;
        Type_delete(hoisted__Type_854, &(Bool){1});
        U32 hoisted__U32_856 = 0;
        (void)hoisted__U32_856;
        Str hoisted__Str_857 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_857;
        Array_set(_va_Array_27, &hoisted__U32_856, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_857; _oa; }));
        Str hoisted__Str_858 = (Str){.c_str = (void *)"./src/core/str.til:91:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_858;
        panic(&hoisted__Str_858, _va_Array_27);
        Str_delete(&hoisted__Str_858, &(Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_866 = U32_gt(&new_len, &self->cap);
    (void)hoisted__Bool_866;
    if (hoisted__Bool_866) {
        Type *hoisted__Type_860 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_860;
        U32 hoisted__U32_861 = 1;
        (void)hoisted__U32_861;
        Array *_va_Array_28 = Array_new(hoisted__Type_860, &hoisted__U32_861);
        (void)_va_Array_28;
        Type_delete(hoisted__Type_860, &(Bool){1});
        U32 hoisted__U32_862 = 0;
        (void)hoisted__U32_862;
        Str hoisted__Str_863 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_863;
        Array_set(_va_Array_28, &hoisted__U32_862, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_863; _oa; }));
        Str hoisted__Str_864 = (Str){.c_str = (void *)"./src/core/str.til:95:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_864;
        panic(&hoisted__Str_864, _va_Array_28);
        Str_delete(&hoisted__Str_864, &(Bool){0});
    }
    void *hoisted__v_867 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_867;
    (void)hoisted__v_867;
    memcpy(hoisted__v_867, s->c_str, s->count);
    U32 hoisted__U32_868 = U32_clone(&new_len);
    (void)hoisted__U32_868;
    self->count = hoisted__U32_868;
    void *hoisted__v_869 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_869;
    (void)hoisted__v_869;
    I32 hoisted__I32_870 = 0;
    (void)hoisted__I32_870;
    U64 hoisted__U64_871 = 1ULL;
    (void)hoisted__U64_871;
    memset(hoisted__v_869, hoisted__I32_870, hoisted__U64_871);
    I32_delete(&hoisted__I32_870, &(Bool){0});
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_872 = 1;
    (void)hoisted__U32_872;
    U32 hoisted__U64_873 = U32_add(val->count, hoisted__U32_872);
    (void)hoisted__U64_873;
    void * new_data = malloc(hoisted__U64_873);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_874 = ptr_add(new_data, val->count);
    (void)hoisted__v_874;
    (void)hoisted__v_874;
    I32 hoisted__I32_875 = 0;
    (void)hoisted__I32_875;
    U64 hoisted__U64_876 = 1ULL;
    (void)hoisted__U64_876;
    memset(hoisted__v_874, hoisted__I32_875, hoisted__U64_876);
    I32_delete(&hoisted__I32_875, &(Bool){0});
    Str *hoisted__Str_877 = malloc(sizeof(Str));
    hoisted__Str_877->c_str = new_data;
    hoisted__Str_877->count = val->count;
    hoisted__Str_877->cap = val->count;
    (void)hoisted__Str_877;
    return hoisted__Str_877;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool hoisted__Bool_878 = U32_lt(&self->cap, &CAP_VIEW);
    (void)hoisted__Bool_878;
    if (hoisted__Bool_878) {
        free(self->c_str);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_991 = 0;
    (void)hoisted__U32_991;
    Bool hoisted__Bool_992 = U32_eq(self->count, hoisted__U32_991);
    (void)hoisted__Bool_992;
    return hoisted__Bool_992;
}

U32 Str_size(void) {
    U32 hoisted__U32_1225 = 16;
    (void)hoisted__U32_1225;
    return hoisted__U32_1225;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1226 = Str_cmp(a, b);
    (void)hoisted__I64_1226;
    I64 hoisted__I64_1227 = 0;
    (void)hoisted__I64_1227;
    Bool hoisted__Bool_1228 = I64_eq(hoisted__I64_1226, hoisted__I64_1227);
    (void)hoisted__Bool_1228;
    return hoisted__Bool_1228;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1272 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1272->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1272;
    return hoisted__OutOfBounds_1272;
}

void OutOfBounds_delete(OutOfBounds * self, Bool * call_free) {
    Bool hoisted__Bool_1273 = 0;
    (void)hoisted__Bool_1273;
    Str_delete(&self->msg, &hoisted__Bool_1273);
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1274 = 16;
    (void)hoisted__U32_1274;
    return hoisted__U32_1274;
}

U32 * Dynamic_size(void) {
    U32 hoisted__U32_1277 = 8;
    (void)hoisted__U32_1277;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1277;
    return _r; }
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 * val) {
    I64 hoisted__I64_1481 = 0;
    (void)hoisted__I64_1481;
    Bool hoisted__Bool_1482 = I64_eq(DEREF(val), hoisted__I64_1481);
    (void)hoisted__Bool_1482;
    if (hoisted__Bool_1482) {
        U64 hoisted__U64_1445 = 2ULL;
        (void)hoisted__U64_1445;
        void * buf = malloc(hoisted__U64_1445);
        I64 hoisted__I64_1446 = 48;
        (void)hoisted__I64_1446;
        U64 hoisted__U64_1447 = 1ULL;
        (void)hoisted__U64_1447;
        memcpy(buf, &hoisted__I64_1446, hoisted__U64_1447);
        U64 hoisted__U64_1448 = 1ULL;
        (void)hoisted__U64_1448;
        void *hoisted__v_1449 = ptr_add(buf, hoisted__U64_1448);
        (void)hoisted__v_1449;
        (void)hoisted__v_1449;
        I32 hoisted__I32_1450 = 0;
        (void)hoisted__I32_1450;
        U64 hoisted__U64_1451 = 1ULL;
        (void)hoisted__U64_1451;
        memset(hoisted__v_1449, hoisted__I32_1450, hoisted__U64_1451);
        I32_delete(&hoisted__I32_1450, &(Bool){0});
        I64 hoisted__I64_1452 = 1;
        (void)hoisted__I64_1452;
        I64 hoisted__I64_1453 = 1;
        (void)hoisted__I64_1453;
        Str *hoisted__Str_1454 = malloc(sizeof(Str));
        hoisted__Str_1454->c_str = buf;
        hoisted__Str_1454->count = hoisted__I64_1452;
        hoisted__Str_1454->cap = hoisted__I64_1453;
        (void)hoisted__Str_1454;
        { Str * _ret_val = hoisted__Str_1454;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_1483 = 0;
    (void)hoisted__I64_1483;
    Bool hoisted__Bool_1484 = I64_lt(val, &hoisted__I64_1483);
    (void)hoisted__Bool_1484;
    if (hoisted__Bool_1484) {
        Bool hoisted__Bool_1455 = 1;
        (void)hoisted__Bool_1455;
        is_neg = hoisted__Bool_1455;
        I64 hoisted__I64_1456 = 0;
        (void)hoisted__I64_1456;
        I64 hoisted__I64_1457 = I64_sub(hoisted__I64_1456, DEREF(val));
        (void)hoisted__I64_1457;
        v = hoisted__I64_1457;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1459 = 0;
        (void)hoisted__I64_1459;
        Bool _wcond_Bool_1458 = I64_gt(&tmp, &hoisted__I64_1459);
        (void)_wcond_Bool_1458;
        if (_wcond_Bool_1458) {
        } else {
            break;
        }
        U64 hoisted__U64_1460 = 1ULL;
        (void)hoisted__U64_1460;
        U64 hoisted__U64_1461 = U64_add(ndigits, hoisted__U64_1460);
        (void)hoisted__U64_1461;
        ndigits = hoisted__U64_1461;
        I64 hoisted__I64_1462 = 10;
        (void)hoisted__I64_1462;
        I64 hoisted__I64_1463 = I64_div(tmp, hoisted__I64_1462);
        (void)hoisted__I64_1463;
        tmp = hoisted__I64_1463;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1464 = 1ULL;
        (void)hoisted__U64_1464;
        U64 hoisted__U64_1465 = U64_add(total, hoisted__U64_1464);
        (void)hoisted__U64_1465;
        total = hoisted__U64_1465;
    }
    U64 hoisted__U64_1485 = 1ULL;
    (void)hoisted__U64_1485;
    U64 hoisted__U64_1486 = U64_add(total, hoisted__U64_1485);
    (void)hoisted__U64_1486;
    void * buf = malloc(hoisted__U64_1486);
    if (is_neg) {
        I64 hoisted__I64_1466 = 45;
        (void)hoisted__I64_1466;
        U64 hoisted__U64_1467 = 1ULL;
        (void)hoisted__U64_1467;
        memcpy(buf, &hoisted__I64_1466, hoisted__U64_1467);
    }
    U64 hoisted__U64_1487 = 1ULL;
    (void)hoisted__U64_1487;
    U64 i = U64_sub(total, hoisted__U64_1487);
    while (1) {
        I64 hoisted__I64_1469 = 0;
        (void)hoisted__I64_1469;
        Bool _wcond_Bool_1468 = I64_gt(&v, &hoisted__I64_1469);
        (void)_wcond_Bool_1468;
        if (_wcond_Bool_1468) {
        } else {
            break;
        }
        I64 hoisted__I64_1470 = 10;
        (void)hoisted__I64_1470;
        I64 hoisted__I64_1471 = I64_mod(v, hoisted__I64_1470);
        (void)hoisted__I64_1471;
        I64 hoisted__I64_1472 = 48;
        (void)hoisted__I64_1472;
        I64 hoisted__I64_1473 = I64_add(hoisted__I64_1471, hoisted__I64_1472);
        (void)hoisted__I64_1473;
        void *hoisted__v_1474 = ptr_add(buf, i);
        (void)hoisted__v_1474;
        (void)hoisted__v_1474;
        U8 hoisted__U8_1475 = I64_to_u8(hoisted__I64_1473);
        (void)hoisted__U8_1475;
        U64 hoisted__U64_1476 = 1ULL;
        (void)hoisted__U64_1476;
        memcpy(hoisted__v_1474, &hoisted__U8_1475, hoisted__U64_1476);
        U8_delete(&hoisted__U8_1475, &(Bool){0});
        I64 hoisted__I64_1477 = 10;
        (void)hoisted__I64_1477;
        I64 hoisted__I64_1478 = I64_div(v, hoisted__I64_1477);
        (void)hoisted__I64_1478;
        v = hoisted__I64_1478;
        U64 hoisted__U64_1479 = 1ULL;
        (void)hoisted__U64_1479;
        U64 hoisted__U64_1480 = U64_sub(i, hoisted__U64_1479);
        (void)hoisted__U64_1480;
        i = hoisted__U64_1480;
    }
    void *hoisted__v_1488 = ptr_add(buf, total);
    (void)hoisted__v_1488;
    (void)hoisted__v_1488;
    I32 hoisted__I32_1489 = 0;
    (void)hoisted__I32_1489;
    U64 hoisted__U64_1490 = 1ULL;
    (void)hoisted__U64_1490;
    memset(hoisted__v_1488, hoisted__I32_1489, hoisted__U64_1490);
    I32_delete(&hoisted__I32_1489, &(Bool){0});
    Str *hoisted__Str_1491 = malloc(sizeof(Str));
    hoisted__Str_1491->c_str = buf;
    hoisted__Str_1491->count = total;
    hoisted__Str_1491->cap = total;
    (void)hoisted__Str_1491;
    return hoisted__Str_1491;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    U32 hoisted__U32_1509 = 8;
    (void)hoisted__U32_1509;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1509;
    return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1642 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1642;
    I64 hoisted__I64_1643 = -1;
    (void)hoisted__I64_1643;
    Bool hoisted__Bool_1644 = I64_eq(hoisted__I64_1642, hoisted__I64_1643);
    (void)hoisted__Bool_1644;
    return hoisted__Bool_1644;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1645 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1645;
    I64 hoisted__I64_1646 = 1;
    (void)hoisted__I64_1646;
    Bool hoisted__Bool_1647 = I64_eq(hoisted__I64_1645, hoisted__I64_1646);
    (void)hoisted__Bool_1647;
    return hoisted__Bool_1647;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1648 = I64_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1648;
    Bool hoisted__Bool_1649 = not(hoisted__Bool_1648);
    (void)hoisted__Bool_1649;
    return hoisted__Bool_1649;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1663 = Bool_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1663;
    if (hoisted__Bool_1663) {
        I64 hoisted__I64_1661 = 0;
        (void)hoisted__I64_1661;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1661;
                return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1662 = -1;
        (void)hoisted__I64_1662;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1662;
        return _r; }
    }
    I64 hoisted__I64_1664 = 1;
    (void)hoisted__I64_1664;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1664;
    return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    U32 hoisted__U32_1665 = 1;
    (void)hoisted__U32_1665;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1665;
    return _r; }
}

Primitive *Primitive_I16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I16 };
    return r;
}
Primitive *Primitive_U16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_U16 };
    return r;
}
Bool Primitive_eq(Primitive * self, Primitive * other) {
    Bool hoisted__Bool_1804 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1804;
    if (hoisted__Bool_1804) {
        Bool hoisted__Bool_1802 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1802;
        { Bool _ret_val = hoisted__Bool_1802;
                return _ret_val; }
    }
    Bool hoisted__Bool_1805 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1805;
    if (hoisted__Bool_1805) {
        Bool hoisted__Bool_1803 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1803;
        { Bool _ret_val = hoisted__Bool_1803;
                return _ret_val; }
    }
    Bool hoisted__Bool_1806 = 0;
    (void)hoisted__Bool_1806;
    return hoisted__Bool_1806;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1812 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1812;
    if (hoisted__Bool_1812) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1813 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1813;
    if (hoisted__Bool_1813) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Str hoisted__Str_1814 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1814;
    UNREACHABLE(&hoisted__Str_1814);
    Str_delete(&hoisted__Str_1814, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1815 = 4;
    (void)hoisted__U32_1815;
    return hoisted__U32_1815;
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
    Bool hoisted__Bool_1878 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1878;
    if (hoisted__Bool_1878) {
        Str *hoisted__Str_1870 = get_payload(self);
        (void)hoisted__Str_1870;
        (void)hoisted__Str_1870;
        Bool hoisted__Bool_1871 = 0;
        (void)hoisted__Bool_1871;
        Str_delete(hoisted__Str_1870, &hoisted__Bool_1871);
    }
    Bool hoisted__Bool_1879 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1879;
    if (hoisted__Bool_1879) {
        Str *hoisted__Str_1872 = get_payload(self);
        (void)hoisted__Str_1872;
        (void)hoisted__Str_1872;
        Bool hoisted__Bool_1873 = 0;
        (void)hoisted__Bool_1873;
        Str_delete(hoisted__Str_1872, &hoisted__Bool_1873);
    }
    Bool hoisted__Bool_1880 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1880;
    if (hoisted__Bool_1880) {
        Str *hoisted__Str_1874 = get_payload(self);
        (void)hoisted__Str_1874;
        (void)hoisted__Str_1874;
        Bool hoisted__Bool_1875 = 0;
        (void)hoisted__Bool_1875;
        Str_delete(hoisted__Str_1874, &hoisted__Bool_1875);
    }
    Bool hoisted__Bool_1881 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1881;
    if (hoisted__Bool_1881) {
        Primitive *hoisted__Primitive_1876 = get_payload(self);
        (void)hoisted__Primitive_1876;
        (void)hoisted__Primitive_1876;
        Bool hoisted__Bool_1877 = 0;
        (void)hoisted__Bool_1877;
        Primitive_delete(hoisted__Primitive_1876, &hoisted__Bool_1877);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1963 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_1963;
    if (hoisted__Bool_1963) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_1964 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_1964;
    if (hoisted__Bool_1964) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_1965 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)hoisted__Bool_1965;
    if (hoisted__Bool_1965) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1966 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)hoisted__Bool_1966;
    if (hoisted__Bool_1966) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1967 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)hoisted__Bool_1967;
    if (hoisted__Bool_1967) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1968 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)hoisted__Bool_1968;
    if (hoisted__Bool_1968) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1969 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)hoisted__Bool_1969;
    if (hoisted__Bool_1969) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1970 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)hoisted__Bool_1970;
    if (hoisted__Bool_1970) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1971 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)hoisted__Bool_1971;
    if (hoisted__Bool_1971) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool;
                return _r; }
    }
    Bool hoisted__Bool_1972 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1972;
    if (hoisted__Bool_1972) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_1957 = Str_clone(_clone_payload_Struct_9);
        (void)hoisted__Str_1957;
        Type *hoisted__Type_1958 = Type_Struct(hoisted__Str_1957);
        (void)hoisted__Type_1958;
        { Type * _ret_val = hoisted__Type_1958;
                return _ret_val; }
    }
    Bool hoisted__Bool_1973 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_1973;
    if (hoisted__Bool_1973) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_1974 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1974;
    if (hoisted__Bool_1974) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_1959 = Str_clone(_clone_payload_Enum_11);
        (void)hoisted__Str_1959;
        Type *hoisted__Type_1960 = Type_Enum(hoisted__Str_1959);
        (void)hoisted__Type_1960;
        { Type * _ret_val = hoisted__Type_1960;
                return _ret_val; }
    }
    Bool hoisted__Bool_1975 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_1975;
    if (hoisted__Bool_1975) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_1976 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_1976;
    if (hoisted__Bool_1976) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_1977 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_1977;
    if (hoisted__Bool_1977) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_1978 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_1978;
    if (hoisted__Bool_1978) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_1979 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1979;
    if (hoisted__Bool_1979) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_1961 = Str_clone(_clone_payload_Custom_16);
        (void)hoisted__Str_1961;
        Type *hoisted__Type_1962 = Type_Custom(hoisted__Str_1961);
        (void)hoisted__Type_1962;
        { Type * _ret_val = hoisted__Type_1962;
                return _ret_val; }
    }
    Bool hoisted__Bool_1980 = is(self, &(Type){.tag = Type_TAG_I8});
    (void)hoisted__Bool_1980;
    if (hoisted__Bool_1980) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8;
                return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive *hoisted__Primitive_1981 = Primitive_clone(_clone_payload_Primitive_18);
    (void)hoisted__Primitive_1981;
    Type *hoisted__Type_1982 = Type_Primitive(hoisted__Primitive_1981);
    (void)hoisted__Type_1982;
    return hoisted__Type_1982;
}

U32 Type_size(void) {
    U32 hoisted__U32_1983 = 24;
    (void)hoisted__U32_1983;
    return hoisted__U32_1983;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_3550 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3550;
    if (hoisted__Bool_3550) {
        Type *hoisted__Type_3545 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3545;
        U32 hoisted__U32_3546 = 1;
        (void)hoisted__U32_3546;
        Array *_va_Array_102 = Array_new(hoisted__Type_3545, &hoisted__U32_3546);
        (void)_va_Array_102;
        Type_delete(hoisted__Type_3545, &(Bool){1});
        U32 hoisted__U32_3547 = 0;
        (void)hoisted__U32_3547;
        Str hoisted__Str_3548 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3548;
        Array_set(_va_Array_102, &hoisted__U32_3547, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3548; _oa; }));
        Str hoisted__Str_3549 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3549;
        panic(&hoisted__Str_3549, _va_Array_102);
        Str_delete(&hoisted__Str_3549, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3551 = calloc(DEREF(cap), elem_size);
    (void)hoisted__v_3551;
    void * hoisted__v_3552 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3552;
    void * hoisted__v_3553 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3553;
    Array *hoisted__Array_3554 = malloc(sizeof(Array));
    hoisted__Array_3554->data = hoisted__v_3551;
    hoisted__Array_3554->cap = DEREF(cap);
    hoisted__Array_3554->elem_size = elem_size;
    hoisted__Array_3554->elem_clone = hoisted__v_3552;
    hoisted__Array_3554->elem_delete = hoisted__v_3553;
    (void)hoisted__Array_3554;
    return hoisted__Array_3554;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3555 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3555;
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_3555;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap;
    return _r; }
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3576 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3576;
    if (hoisted__Bool_3576) {
        Type *hoisted__Type_3557 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3557;
        U32 hoisted__U32_3558 = 6;
        (void)hoisted__U32_3558;
        Array *_va_Array_103 = Array_new(hoisted__Type_3557, &hoisted__U32_3558);
        (void)_va_Array_103;
        Type_delete(hoisted__Type_3557, &(Bool){1});
        U32 hoisted__U32_3559 = 0;
        (void)hoisted__U32_3559;
        Str hoisted__Str_3560 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3560;
        Array_set(_va_Array_103, &hoisted__U32_3559, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3560; _oa; }));
        U32 hoisted__U32_3561 = 1;
        (void)hoisted__U32_3561;
        Str hoisted__Str_3562 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3562;
        Array_set(_va_Array_103, &hoisted__U32_3561, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3562; _oa; }));
        U32 hoisted__U32_3563 = 2;
        (void)hoisted__U32_3563;
        Str *hoisted__Str_3564 = U32_to_str(i);
        (void)hoisted__Str_3564;
        Array_set(_va_Array_103, &hoisted__U32_3563, hoisted__Str_3564);
        U32 hoisted__U32_3565 = 3;
        (void)hoisted__U32_3565;
        Str hoisted__Str_3566 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3566;
        Array_set(_va_Array_103, &hoisted__U32_3565, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3566; _oa; }));
        U32 hoisted__U32_3567 = 4;
        (void)hoisted__U32_3567;
        Str *hoisted__Str_3568 = U32_to_str(&self->cap);
        (void)hoisted__Str_3568;
        Array_set(_va_Array_103, &hoisted__U32_3567, hoisted__Str_3568);
        U32 hoisted__U32_3569 = 5;
        (void)hoisted__U32_3569;
        Str hoisted__Str_3570 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3570;
        Array_set(_va_Array_103, &hoisted__U32_3569, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3570; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3571 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_103); hoisted__OutOfBounds_3571->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3571;
        U32 hoisted__U32_3572 = 16;
        (void)hoisted__U32_3572;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3571, hoisted__U32_3572);
        OutOfBounds_delete(hoisted__OutOfBounds_3571, &(Bool){1});
        I64 hoisted__I64_3573 = 3;
        (void)hoisted__I64_3573;
        *_err_kind = hoisted__I64_3573;
    }
    I64 hoisted__I64_3577 = 0;
    (void)hoisted__I64_3577;
    Bool hoisted__Bool_3578 = I64_eq(DEREF(_err_kind), hoisted__I64_3577);
    (void)hoisted__Bool_3578;
    if (hoisted__Bool_3578) {
        U32 hoisted__U64_3574 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3574;
        void *hoisted__v_3575 = ptr_add(self->data, hoisted__U64_3574);
        (void)hoisted__v_3575;
        (void)hoisted__v_3575;
        { void * _ret_val = hoisted__v_3575;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_3593 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3593;
    if (hoisted__Bool_3593) {
        Type *hoisted__Type_3580 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3580;
        U32 hoisted__U32_3581 = 5;
        (void)hoisted__U32_3581;
        Array *_va_Array_104 = Array_new(hoisted__Type_3580, &hoisted__U32_3581);
        (void)_va_Array_104;
        Type_delete(hoisted__Type_3580, &(Bool){1});
        U32 hoisted__U32_3582 = 0;
        (void)hoisted__U32_3582;
        Str hoisted__Str_3583 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3583;
        Array_set(_va_Array_104, &hoisted__U32_3582, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3583; _oa; }));
        U32 hoisted__U32_3584 = 1;
        (void)hoisted__U32_3584;
        Str *hoisted__Str_3585 = U32_to_str(i);
        (void)hoisted__Str_3585;
        Array_set(_va_Array_104, &hoisted__U32_3584, hoisted__Str_3585);
        U32 hoisted__U32_3586 = 2;
        (void)hoisted__U32_3586;
        Str hoisted__Str_3587 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3587;
        Array_set(_va_Array_104, &hoisted__U32_3586, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3587; _oa; }));
        U32 hoisted__U32_3588 = 3;
        (void)hoisted__U32_3588;
        Str *hoisted__Str_3589 = U32_to_str(&self->cap);
        (void)hoisted__Str_3589;
        Array_set(_va_Array_104, &hoisted__U32_3588, hoisted__Str_3589);
        U32 hoisted__U32_3590 = 4;
        (void)hoisted__U32_3590;
        Str hoisted__Str_3591 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3591;
        Array_set(_va_Array_104, &hoisted__U32_3590, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3591; _oa; }));
        Str hoisted__Str_3592 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3592;
        panic(&hoisted__Str_3592, _va_Array_104);
        Str_delete(&hoisted__Str_3592, &(Bool){0});
    }
    U32 hoisted__U64_3594 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3594;
    void *hoisted__v_3595 = ptr_add(self->data, hoisted__U64_3594);
    (void)hoisted__v_3595;
    (void)hoisted__v_3595;
    Bool hoisted__Bool_3596 = 0;
    (void)hoisted__Bool_3596;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3595, &hoisted__Bool_3596);
    U32 hoisted__U64_3597 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3597;
    void *hoisted__v_3598 = ptr_add(self->data, hoisted__U64_3597);
    (void)hoisted__v_3598;
    (void)hoisted__v_3598;
    memcpy(hoisted__v_3598, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_3599 = self->cap;
        (void)_re_U32_3599;
        U32 _rc_U32_3599 = 0;
        (void)_rc_U32_3599;
        Bool hoisted__Bool_3608 = U32_lte(&_rc_U32_3599, &_re_U32_3599);
        (void)hoisted__Bool_3608;
        if (hoisted__Bool_3608) {
            while (1) {
                Bool _wcond_Bool_3600 = U32_lt(&_rc_U32_3599, &_re_U32_3599);
                (void)_wcond_Bool_3600;
                if (_wcond_Bool_3600) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3599);
                U32_inc(&_rc_U32_3599);
                U32 hoisted__U64_3601 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3601;
                void *hoisted__v_3602 = ptr_add(self->data, hoisted__U64_3601);
                (void)hoisted__v_3602;
                (void)hoisted__v_3602;
                Bool hoisted__Bool_3603 = 0;
                (void)hoisted__Bool_3603;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3602, &hoisted__Bool_3603);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3604 = U32_gt(&_rc_U32_3599, &_re_U32_3599);
                (void)_wcond_Bool_3604;
                if (_wcond_Bool_3604) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3599);
                U32_dec(&_rc_U32_3599);
                U32 hoisted__U64_3605 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3605;
                void *hoisted__v_3606 = ptr_add(self->data, hoisted__U64_3605);
                (void)hoisted__v_3606;
                (void)hoisted__v_3606;
                Bool hoisted__Bool_3607 = 0;
                (void)hoisted__Bool_3607;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3606, &hoisted__Bool_3607);
            }
        }
    }
    free(self->data);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3621 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3621;
    void * new_data = malloc(hoisted__U64_3621);
    {
        U32 _re_U32_3609 = self->cap;
        (void)_re_U32_3609;
        U32 _rc_U32_3609 = 0;
        (void)_rc_U32_3609;
        Bool hoisted__Bool_3620 = U32_lte(&_rc_U32_3609, &_re_U32_3609);
        (void)hoisted__Bool_3620;
        if (hoisted__Bool_3620) {
            while (1) {
                Bool _wcond_Bool_3610 = U32_lt(&_rc_U32_3609, &_re_U32_3609);
                (void)_wcond_Bool_3610;
                if (_wcond_Bool_3610) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3609);
                U32_inc(&_rc_U32_3609);
                U32 hoisted__U64_3611 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3611;
                void *hoisted__v_3612 = ptr_add(self->data, hoisted__U64_3611);
                (void)hoisted__v_3612;
                (void)hoisted__v_3612;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3612);
                U32 hoisted__U64_3613 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3613;
                void *hoisted__v_3614 = ptr_add(new_data, hoisted__U64_3613);
                (void)hoisted__v_3614;
                (void)hoisted__v_3614;
                memcpy(hoisted__v_3614, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3615 = U32_gt(&_rc_U32_3609, &_re_U32_3609);
                (void)_wcond_Bool_3615;
                if (_wcond_Bool_3615) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3609);
                U32_dec(&_rc_U32_3609);
                U32 hoisted__U64_3616 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3616;
                void *hoisted__v_3617 = ptr_add(self->data, hoisted__U64_3616);
                (void)hoisted__v_3617;
                (void)hoisted__v_3617;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3617);
                U32 hoisted__U64_3618 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3618;
                void *hoisted__v_3619 = ptr_add(new_data, hoisted__U64_3618);
                (void)hoisted__v_3619;
                (void)hoisted__v_3619;
                memcpy(hoisted__v_3619, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3622 = malloc(sizeof(Array));
    hoisted__Array_3622->data = new_data;
    hoisted__Array_3622->cap = self->cap;
    hoisted__Array_3622->elem_size = self->elem_size;
    hoisted__Array_3622->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3622->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3622;
    return hoisted__Array_3622;
}

U32 Array_size(void) {
    U32 hoisted__U32_3623 = 32;
    (void)hoisted__U32_3623;
    return hoisted__U32_3623;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_3861 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_3861;
    U32 hoisted__U32_3862 = 3;
    (void)hoisted__U32_3862;
    Array *_va_Array_121 = Array_new(hoisted__Type_3861, &hoisted__U32_3862);
    (void)_va_Array_121;
    Type_delete(hoisted__Type_3861, &(Bool){1});
    U32 hoisted__U32_3863 = 0;
    (void)hoisted__U32_3863;
    Str *hoisted__Str_3864 = Str_clone(loc_str);
    (void)hoisted__Str_3864;
    Array_set(_va_Array_121, &hoisted__U32_3863, hoisted__Str_3864);
    U32 hoisted__U32_3865 = 1;
    (void)hoisted__U32_3865;
    Str hoisted__Str_3866 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3866;
    Array_set(_va_Array_121, &hoisted__U32_3865, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3866; _oa; }));
    Array *hoisted__Array_3867 = Array_clone(parts);
    (void)hoisted__Array_3867;
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_3868 = 2;
    (void)hoisted__U32_3868;
    Str *hoisted__Str_3869 = format(hoisted__Array_3867);
    (void)hoisted__Str_3869;
    Array_set(_va_Array_121, &hoisted__U32_3868, hoisted__Str_3869);
    println(_va_Array_121);
    I64 hoisted__I64_3870 = 1;
    (void)hoisted__I64_3870;
    exit(hoisted__I64_3870);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_3880 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_3880;
    U32 hoisted__U32_3881 = 1;
    (void)hoisted__U32_3881;
    Array *_va_Array_123 = Array_new(hoisted__Type_3880, &hoisted__U32_3881);
    (void)_va_Array_123;
    Type_delete(hoisted__Type_3880, &(Bool){1});
    U32 hoisted__U32_3882 = 0;
    (void)hoisted__U32_3882;
    Str hoisted__Str_3883 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3883;
    Array_set(_va_Array_123, &hoisted__U32_3882, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3883; _oa; }));
    panic(loc_str, _va_Array_123);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_3889 = not(DEREF(cond));
    (void)hoisted__Bool_3889;
    if (hoisted__Bool_3889) {
        Type *hoisted__Type_3885 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3885;
        U32 hoisted__U32_3886 = 1;
        (void)hoisted__U32_3886;
        Array *_va_Array_124 = Array_new(hoisted__Type_3885, &hoisted__U32_3886);
        (void)_va_Array_124;
        Type_delete(hoisted__Type_3885, &(Bool){1});
        U32 hoisted__U32_3887 = 0;
        (void)hoisted__U32_3887;
        Str hoisted__Str_3888 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3888;
        Array_set(_va_Array_124, &hoisted__U32_3887, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3888; _oa; }));
        panic(loc_str, _va_Array_124);
    }
    Bool hoisted__Bool_3890 = 1;
    (void)hoisted__Bool_3890;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_3890;
    return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_3913 = I64_neq(a, b);
    (void)hoisted__Bool_3913;
    if (hoisted__Bool_3913) {
        Type *hoisted__Type_3901 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3901;
        U32 hoisted__U32_3902 = 5;
        (void)hoisted__U32_3902;
        Array *_va_Array_126 = Array_new(hoisted__Type_3901, &hoisted__U32_3902);
        (void)_va_Array_126;
        Type_delete(hoisted__Type_3901, &(Bool){1});
        U32 hoisted__U32_3903 = 0;
        (void)hoisted__U32_3903;
        Str hoisted__Str_3904 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3904;
        Array_set(_va_Array_126, &hoisted__U32_3903, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3904; _oa; }));
        U32 hoisted__U32_3905 = 1;
        (void)hoisted__U32_3905;
        Str *hoisted__Str_3906 = I64_to_str(a);
        (void)hoisted__Str_3906;
        Array_set(_va_Array_126, &hoisted__U32_3905, hoisted__Str_3906);
        U32 hoisted__U32_3907 = 2;
        (void)hoisted__U32_3907;
        Str hoisted__Str_3908 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3908;
        Array_set(_va_Array_126, &hoisted__U32_3907, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3908; _oa; }));
        U32 hoisted__U32_3909 = 3;
        (void)hoisted__U32_3909;
        Str *hoisted__Str_3910 = I64_to_str(b);
        (void)hoisted__Str_3910;
        Array_set(_va_Array_126, &hoisted__U32_3909, hoisted__Str_3910);
        U32 hoisted__U32_3911 = 4;
        (void)hoisted__U32_3911;
        Str hoisted__Str_3912 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3912;
        Array_set(_va_Array_126, &hoisted__U32_3911, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3912; _oa; }));
        panic(loc_str, _va_Array_126);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_3927 = Str_eq(a, b);
    (void)hoisted__Bool_3927;
    Bool hoisted__Bool_3928 = not(hoisted__Bool_3927);
    (void)hoisted__Bool_3928;
    if (hoisted__Bool_3928) {
        Type *hoisted__Type_3915 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3915;
        U32 hoisted__U32_3916 = 5;
        (void)hoisted__U32_3916;
        Array *_va_Array_127 = Array_new(hoisted__Type_3915, &hoisted__U32_3916);
        (void)_va_Array_127;
        Type_delete(hoisted__Type_3915, &(Bool){1});
        U32 hoisted__U32_3917 = 0;
        (void)hoisted__U32_3917;
        Str hoisted__Str_3918 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3918;
        Array_set(_va_Array_127, &hoisted__U32_3917, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3918; _oa; }));
        U32 hoisted__U32_3919 = 1;
        (void)hoisted__U32_3919;
        Str *hoisted__Str_3920 = Str_clone(a);
        (void)hoisted__Str_3920;
        Array_set(_va_Array_127, &hoisted__U32_3919, hoisted__Str_3920);
        U32 hoisted__U32_3921 = 2;
        (void)hoisted__U32_3921;
        Str hoisted__Str_3922 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3922;
        Array_set(_va_Array_127, &hoisted__U32_3921, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3922; _oa; }));
        U32 hoisted__U32_3923 = 3;
        (void)hoisted__U32_3923;
        Str *hoisted__Str_3924 = Str_clone(b);
        (void)hoisted__Str_3924;
        Array_set(_va_Array_127, &hoisted__U32_3923, hoisted__Str_3924);
        U32 hoisted__U32_3925 = 4;
        (void)hoisted__U32_3925;
        Str hoisted__Str_3926 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3926;
        Array_set(_va_Array_127, &hoisted__U32_3925, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3926; _oa; }));
        panic(loc_str, _va_Array_127);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_3929 = parts;
        (void)_fc_Array_3929;
        (void)_fc_Array_3929;
        U32 _fi_USize_3929 = 0;
        (void)_fi_USize_3929;
        I64 _forin_err_kind_3929 = 0;
        (void)_forin_err_kind_3929;
        OutOfBounds *_forin_OutOfBounds_3929 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_3929->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_3929;
        while (1) {
            U32 hoisted__U32_3937; { U32 *_hp = (U32 *)Array_len(_fc_Array_3929); hoisted__U32_3937 = *_hp; free(_hp); }
            (void)hoisted__U32_3937;
            Bool _wcond_Bool_3930 = U32_lt(&_fi_USize_3929, &hoisted__U32_3937);
            (void)_wcond_Bool_3930;
            if (_wcond_Bool_3930) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_3929, &_fi_USize_3929, &_forin_err_kind_3929, _forin_OutOfBounds_3929);
            I64 hoisted__I64_3938 = 0;
            (void)hoisted__I64_3938;
            Bool hoisted__Bool_3939 = I64_eq(_forin_err_kind_3929, hoisted__I64_3938);
            (void)hoisted__Bool_3939;
            Bool hoisted__Bool_3940 = not(hoisted__Bool_3939);
            (void)hoisted__Bool_3940;
            if (hoisted__Bool_3940) {
                Type *hoisted__Type_3932 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_3932;
                U32 hoisted__U32_3933 = 1;
                (void)hoisted__U32_3933;
                Array *_va_Array_128 = Array_new(hoisted__Type_3932, &hoisted__U32_3933);
                (void)_va_Array_128;
                Type_delete(hoisted__Type_3932, &(Bool){1});
                U32 hoisted__U32_3934 = 0;
                (void)hoisted__U32_3934;
                Str hoisted__Str_3935 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_3935;
                Array_set(_va_Array_128, &hoisted__U32_3934, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3935; _oa; }));
                Str hoisted__Str_3936 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_3936;
                panic(&hoisted__Str_3936, _va_Array_128);
                Str_delete(&hoisted__Str_3936, &(Bool){0});
            }
            U32 hoisted__U32_3941 = 1;
            (void)hoisted__U32_3941;
            U32 hoisted__U32_3942 = U32_add(_fi_USize_3929, hoisted__U32_3941);
            (void)hoisted__U32_3942;
            _fi_USize_3929 = hoisted__U32_3942;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_3929, &(Bool){1});
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void swap(void * a, void * b, U64 size) {
    void * tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_4193 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4193;
    I64 hoisted__I64_4194 = 3;
    (void)hoisted__I64_4194;
    assert_eq(&hoisted__Str_4193, &result, &hoisted__I64_4194);
    Str_delete(&hoisted__Str_4193, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4201 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4201;
    I64 hoisted__I64_4202 = 15;
    (void)hoisted__I64_4202;
    assert_eq(&hoisted__Str_4201, &result, &hoisted__I64_4202);
    Str_delete(&hoisted__Str_4201, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4209 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4209;
    I64 hoisted__I64_4210 = 26;
    (void)hoisted__I64_4210;
    assert_eq(&hoisted__Str_4209, &result, &hoisted__I64_4210);
    Str_delete(&hoisted__Str_4209, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4213 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4213;
    Str hoisted__Str_4214 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4214;
    assert_eq_str(&hoisted__Str_4213, &result, &hoisted__Str_4214);
    Str_delete(&hoisted__Str_4213, &(Bool){0});
    Str_delete(&hoisted__Str_4214, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4545 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4545;
    assert_eq_str(&hoisted__Str_4545, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4545, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_4546 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4546;
    assert_eq_str(&hoisted__Str_4546, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4546, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4548 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4548;
    I64 hoisted__I64_4549 = 8;
    (void)hoisted__I64_4549;
    assert_eq(&hoisted__Str_4548, &result, &hoisted__I64_4549);
    Str_delete(&hoisted__Str_4548, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4552 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4552;
    Bool hoisted__Bool_4553 = 1;
    (void)hoisted__Bool_4553;
    Bool_delete(assert(&hoisted__Str_4552, &hoisted__Bool_4553), &(Bool){1});
    Str_delete(&hoisted__Str_4552, &(Bool){0});
    Str hoisted__Str_4557 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4557;
    Bool hoisted__Bool_4558 = 1;
    (void)hoisted__Bool_4558;
    Bool_delete(assert(&hoisted__Str_4557, &hoisted__Bool_4558), &(Bool){1});
    Str_delete(&hoisted__Str_4557, &(Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4564 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4564;
    Str hoisted__Str_4565 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4565;
    Str hoisted__Str_4566 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4566;
    assert_eq_str(&hoisted__Str_4564, &hoisted__Str_4565, &hoisted__Str_4566);
    Str_delete(&hoisted__Str_4564, &(Bool){0});
    Str_delete(&hoisted__Str_4565, &(Bool){0});
    Str_delete(&hoisted__Str_4566, &(Bool){0});
    Str hoisted__Str_4569 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4569;
    Str hoisted__Str_4570 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4570;
    Str hoisted__Str_4571 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4571;
    assert_eq_str(&hoisted__Str_4569, &hoisted__Str_4570, &hoisted__Str_4571);
    Str_delete(&hoisted__Str_4569, &(Bool){0});
    Str_delete(&hoisted__Str_4570, &(Bool){0});
    Str_delete(&hoisted__Str_4571, &(Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4576 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4576;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4576;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4577 = 16;
    (void)hoisted__U32_4577;
    return hoisted__U32_4577;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4578 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4578;
    I64 hoisted__I64_4579 = 42;
    (void)hoisted__I64_4579;
    assert_eq(&hoisted__Str_4578, &v.x, &hoisted__I64_4579);
    Str_delete(&hoisted__Str_4578, &(Bool){0});
    Str hoisted__Str_4580 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4580;
    I64 hoisted__I64_4581 = 99;
    (void)hoisted__I64_4581;
    assert_eq(&hoisted__Str_4580, &v.y, &hoisted__I64_4581);
    Str_delete(&hoisted__Str_4580, &(Bool){0});
    CfVec2_delete(&v, &(Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4584 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4584;
    I64 hoisted__I64_4585 = 10;
    (void)hoisted__I64_4585;
    assert_eq(&hoisted__Str_4584, &p.x, &hoisted__I64_4585);
    Str_delete(&hoisted__Str_4584, &(Bool){0});
    Str hoisted__Str_4586 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4586;
    I64 hoisted__I64_4587 = 20;
    (void)hoisted__I64_4587;
    assert_eq(&hoisted__Str_4586, &p.y, &hoisted__I64_4587);
    Str_delete(&hoisted__Str_4586, &(Bool){0});
    CfVec2_delete(&p, &(Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4593 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4593;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4593;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4594 = 32;
    (void)hoisted__U32_4594;
    return hoisted__U32_4594;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4595 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4595;
    I64 hoisted__I64_4596 = 5;
    (void)hoisted__I64_4596;
    assert_eq(&hoisted__Str_4595, &r.top_left.x, &hoisted__I64_4596);
    Str_delete(&hoisted__Str_4595, &(Bool){0});
    Str hoisted__Str_4597 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4597;
    I64 hoisted__I64_4598 = 10;
    (void)hoisted__I64_4598;
    assert_eq(&hoisted__Str_4597, &r.top_left.y, &hoisted__I64_4598);
    Str_delete(&hoisted__Str_4597, &(Bool){0});
    Str hoisted__Str_4599 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4599;
    I64 hoisted__I64_4600 = 100;
    (void)hoisted__I64_4600;
    assert_eq(&hoisted__Str_4599, &r.bottom_right.x, &hoisted__I64_4600);
    Str_delete(&hoisted__Str_4599, &(Bool){0});
    Str hoisted__Str_4601 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4601;
    I64 hoisted__I64_4602 = 200;
    (void)hoisted__I64_4602;
    assert_eq(&hoisted__Str_4601, &r.bottom_right.y, &hoisted__I64_4602);
    Str_delete(&hoisted__Str_4601, &(Bool){0});
    CfRect_delete(&r, &(Bool){0});
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
    Bool hoisted__Bool_4607 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4607;
    if (hoisted__Bool_4607) {
        Bool hoisted__Bool_4604 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4604;
        { Bool _ret_val = hoisted__Bool_4604;
                return _ret_val; }
    }
    Bool hoisted__Bool_4608 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4608;
    if (hoisted__Bool_4608) {
        Bool hoisted__Bool_4605 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4605;
        { Bool _ret_val = hoisted__Bool_4605;
                return _ret_val; }
    }
    Bool hoisted__Bool_4609 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4609;
    if (hoisted__Bool_4609) {
        Bool hoisted__Bool_4606 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4606;
        { Bool _ret_val = hoisted__Bool_4606;
                return _ret_val; }
    }
    Bool hoisted__Bool_4610 = 0;
    (void)hoisted__Bool_4610;
    return hoisted__Bool_4610;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4618 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4618;
    if (hoisted__Bool_4618) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4619 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4619;
    if (hoisted__Bool_4619) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4620 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4620;
    if (hoisted__Bool_4620) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4621 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4621;
    UNREACHABLE(&hoisted__Str_4621);
    Str_delete(&hoisted__Str_4621, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4622 = 4;
    (void)hoisted__U32_4622;
    return hoisted__U32_4622;
}


void test_enum_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Str hoisted__Str_4623 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4623;
    Bool hoisted__Bool_4624 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4624;
    Bool_delete(assert(&hoisted__Str_4623, &hoisted__Bool_4624), &(Bool){1});
    Str_delete(&hoisted__Str_4623, &(Bool){0});
    Bool hoisted__Bool_4626 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4626;
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_4627 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4627;
    Bool hoisted__Bool_4628 = not(hoisted__Bool_4626);
    (void)hoisted__Bool_4628;
    Bool_delete(assert(&hoisted__Str_4627, &hoisted__Bool_4628), &(Bool){1});
    Str_delete(&hoisted__Str_4627, &(Bool){0});
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
    Bool hoisted__Bool_4630 = is(self, other);
    (void)hoisted__Bool_4630;
    return hoisted__Bool_4630;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_4648 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4648;
    if (hoisted__Bool_4648) {
        I64 *hoisted__I64_4644 = get_payload(self);
        (void)hoisted__I64_4644;
        (void)hoisted__I64_4644;
        Bool hoisted__Bool_4645 = 0;
        (void)hoisted__Bool_4645;
        I64_delete(hoisted__I64_4644, &hoisted__Bool_4645);
    }
    Bool hoisted__Bool_4649 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4649;
    if (hoisted__Bool_4649) {
        Str *hoisted__Str_4646 = get_payload(self);
        (void)hoisted__Str_4646;
        (void)hoisted__Str_4646;
        Bool hoisted__Bool_4647 = 0;
        (void)hoisted__Bool_4647;
        Str_delete(hoisted__Str_4646, &hoisted__Bool_4647);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4678 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4678;
    if (hoisted__Bool_4678) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4675 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4675;
        { Token * _ret_val = hoisted__Token_4675;
                return _ret_val; }
    }
    Bool hoisted__Bool_4679 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4679;
    if (hoisted__Bool_4679) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4676 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4676;
        Token *hoisted__Token_4677 = Token_Name(hoisted__Str_4676);
        (void)hoisted__Token_4677;
        { Token * _ret_val = hoisted__Token_4677;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4680 = 24;
    (void)hoisted__U32_4680;
    return hoisted__U32_4680;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_4682 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4682;
    Bool hoisted__Bool_4683 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4683;
    Bool_delete(assert(&hoisted__Str_4682, &hoisted__Bool_4683), &(Bool){1});
    Str_delete(&hoisted__Str_4682, &(Bool){0});
    Bool hoisted__Bool_4685 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4685;
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_4686 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4686;
    Bool hoisted__Bool_4687 = not(hoisted__Bool_4685);
    (void)hoisted__Bool_4687;
    Bool_delete(assert(&hoisted__Str_4686, &hoisted__Bool_4687), &(Bool){1});
    Str_delete(&hoisted__Str_4686, &(Bool){0});
}

void test_enum_return_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Green});
    Str hoisted__Str_4689 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4689;
    Bool hoisted__Bool_4690 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4690;
    Bool_delete(assert(&hoisted__Str_4689, &hoisted__Bool_4690), &(Bool){1});
    Str_delete(&hoisted__Str_4689, &(Bool){0});
    Bool hoisted__Bool_4692 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4692;
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_4693 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4693;
    Bool hoisted__Bool_4694 = not(hoisted__Bool_4692);
    (void)hoisted__Bool_4694;
    Bool_delete(assert(&hoisted__Str_4693, &hoisted__Bool_4694), &(Bool){1});
    Str_delete(&hoisted__Str_4693, &(Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_4698 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4698;
    Bool hoisted__Bool_4699 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4699;
    Bool_delete(assert(&hoisted__Str_4698, &hoisted__Bool_4699), &(Bool){1});
    Str_delete(&hoisted__Str_4698, &(Bool){0});
    Bool hoisted__Bool_4701 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4701;
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_4702 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4702;
    Bool hoisted__Bool_4703 = not(hoisted__Bool_4701);
    (void)hoisted__Bool_4703;
    Bool_delete(assert(&hoisted__Str_4702, &hoisted__Bool_4703), &(Bool){1});
    Str_delete(&hoisted__Str_4702, &(Bool){0});
}

void *F32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = F32_cmp(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_clone_dyn(void *_a0) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(_a0); return _r;
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
void *OutOfBounds_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = OutOfBounds_size(); return _r;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)F32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)F32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)F32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)F32_size;
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
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)OutOfBounds_clone;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)OutOfBounds_delete;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)OutOfBounds_size_dyn;
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
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)CfVec2_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)CfVec2_delete;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)CfVec2_size_dyn;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) return sizeof(F32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0) return sizeof(U64);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0) return sizeof(U32);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0) return sizeof(I32);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0) return sizeof(I8);
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0) return sizeof(U8);
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0) return sizeof(Str);
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) return sizeof(OutOfBounds);
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
        return 0LL;
    }
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
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        return 1LL;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
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
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"msg", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
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
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return 1;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0) {
    }
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
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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

I64 enum_variant_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        return 2LL;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        return 19LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        return 3LL;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        return 3LL;
    }
    fprintf(stderr, "enum_variant_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *enum_variant_name(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 12LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 13LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 14LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 15LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 16LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 17LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 18LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Red", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Green", .count = 5ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Blue", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Num", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Name", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Eof", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    fprintf(stderr, "enum_variant_name: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 enum_variant_has_payload(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 1;
        if (*index == 10LL) return 0;
        if (*index == 11LL) return 1;
        if (*index == 12LL) return 0;
        if (*index == 13LL) return 0;
        if (*index == 14LL) return 0;
        if (*index == 15LL) return 0;
        if (*index == 16LL) return 1;
        if (*index == 17LL) return 0;
        if (*index == 18LL) return 1;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 0;
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 0;
    }
    fprintf(stderr, "enum_variant_has_payload: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *enum_variant_payload_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 12LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 13LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 14LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 15LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 16LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 17LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 18LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    fprintf(stderr, "enum_variant_payload_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 func_sig_param_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        return 1LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
        return 2LL;
    }
    fprintf(stderr, "func_sig_param_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *func_sig_param_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    fprintf(stderr, "func_sig_param_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 func_sig_return_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        return 1LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
        return 0LL;
    }
    fprintf(stderr, "func_sig_return_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *func_sig_return_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
    }
    fprintf(stderr, "func_sig_return_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

I64 func_sig_throw_count(Str *type_name) {
    (void)type_name;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
        return 0LL;
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
        return 0LL;
    }
    fprintf(stderr, "func_sig_throw_count: type '%.*s' not found\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *func_sig_throw_type(Str *type_name, I64 *index) {
    (void)type_name; (void)index;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CloneFn", 7ULL) == 0) {
    }
    if (type_name->count == 8ULL && memcmp(type_name->c_str, "DeleteFn", 8ULL) == 0) {
    }
    fprintf(stderr, "func_sig_throw_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
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
        case Primitive_TAG_U16: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    test_fold_f32();
    fprintf(stderr, "  pass: %s\n", "test_fold_f32");
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
    test_enum_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_return_fold");
    test_enum_payload_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_payload_return_fold");
    fprintf(stderr, "15/15 tests passed\n");
    return 0;
}
