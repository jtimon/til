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
    U64 hoisted__U64_848 = 1;
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
    Bool hoisted__Bool_863 = U32_gte(&self->cap, &CAP_VIEW);
    (void)hoisted__Bool_863;
    if (hoisted__Bool_863) {
        Type *hoisted__Type_852 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_852;
        U32 hoisted__U32_853 = 1;
        (void)hoisted__U32_853;
        Array *_va_Array_27 = Array_new(hoisted__Type_852, &hoisted__U32_853);
        (void)_va_Array_27;
        Type_delete(hoisted__Type_852, &(Bool){1});
        U32 hoisted__U32_854 = 0;
        (void)hoisted__U32_854;
        Str hoisted__Str_855 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_855;
        Array_set(_va_Array_27, &hoisted__U32_854, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_855; _oa; }));
        Str hoisted__Str_856 = (Str){.c_str = (void *)"./src/core/str.til:85:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_856;
        panic(&hoisted__Str_856, _va_Array_27);
        Str_delete(&hoisted__Str_856, &(Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_864 = U32_gt(&new_len, &self->cap);
    (void)hoisted__Bool_864;
    if (hoisted__Bool_864) {
        Type *hoisted__Type_858 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_858;
        U32 hoisted__U32_859 = 1;
        (void)hoisted__U32_859;
        Array *_va_Array_28 = Array_new(hoisted__Type_858, &hoisted__U32_859);
        (void)_va_Array_28;
        Type_delete(hoisted__Type_858, &(Bool){1});
        U32 hoisted__U32_860 = 0;
        (void)hoisted__U32_860;
        Str hoisted__Str_861 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_861;
        Array_set(_va_Array_28, &hoisted__U32_860, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_861; _oa; }));
        Str hoisted__Str_862 = (Str){.c_str = (void *)"./src/core/str.til:89:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_862;
        panic(&hoisted__Str_862, _va_Array_28);
        Str_delete(&hoisted__Str_862, &(Bool){0});
    }
    void *hoisted__v_865 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_865;
    (void)hoisted__v_865;
    memcpy(hoisted__v_865, s->c_str, s->count);
    U32 hoisted__U32_866 = U32_clone(&new_len);
    (void)hoisted__U32_866;
    self->count = hoisted__U32_866;
    void *hoisted__v_867 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_867;
    (void)hoisted__v_867;
    I32 hoisted__I32_868 = 0;
    (void)hoisted__I32_868;
    U64 hoisted__U64_869 = 1;
    (void)hoisted__U64_869;
    memset(hoisted__v_867, hoisted__I32_868, hoisted__U64_869);
    I32_delete(&hoisted__I32_868, &(Bool){0});
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_870 = 1;
    (void)hoisted__U32_870;
    U32 hoisted__U64_871 = U32_add(val->count, hoisted__U32_870);
    (void)hoisted__U64_871;
    void * new_data = malloc(hoisted__U64_871);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_872 = ptr_add(new_data, val->count);
    (void)hoisted__v_872;
    (void)hoisted__v_872;
    I32 hoisted__I32_873 = 0;
    (void)hoisted__I32_873;
    U64 hoisted__U64_874 = 1;
    (void)hoisted__U64_874;
    memset(hoisted__v_872, hoisted__I32_873, hoisted__U64_874);
    I32_delete(&hoisted__I32_873, &(Bool){0});
    Str *hoisted__Str_875 = malloc(sizeof(Str));
    hoisted__Str_875->c_str = new_data;
    hoisted__Str_875->count = val->count;
    hoisted__Str_875->cap = val->count;
    (void)hoisted__Str_875;
    return hoisted__Str_875;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool hoisted__Bool_876 = U32_lt(&self->cap, &CAP_VIEW);
    (void)hoisted__Bool_876;
    if (hoisted__Bool_876) {
        free(self->c_str);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_989 = 0;
    (void)hoisted__U32_989;
    Bool hoisted__Bool_990 = U32_eq(self->count, hoisted__U32_989);
    (void)hoisted__Bool_990;
    return hoisted__Bool_990;
}

U32 Str_size(void) {
    U32 hoisted__U32_1221 = 16;
    (void)hoisted__U32_1221;
    return hoisted__U32_1221;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1222 = Str_cmp(a, b);
    (void)hoisted__I64_1222;
    I64 hoisted__I64_1223 = 0;
    (void)hoisted__I64_1223;
    Bool hoisted__Bool_1224 = I64_eq(hoisted__I64_1222, hoisted__I64_1223);
    (void)hoisted__Bool_1224;
    return hoisted__Bool_1224;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1309 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1309->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1309;
    return hoisted__OutOfBounds_1309;
}

void OutOfBounds_delete(OutOfBounds * self, Bool * call_free) {
    Bool hoisted__Bool_1310 = 0;
    (void)hoisted__Bool_1310;
    Str_delete(&self->msg, &hoisted__Bool_1310);
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1311 = 16;
    (void)hoisted__U32_1311;
    return hoisted__U32_1311;
}

U32 * Dynamic_size(void) {
    U32 hoisted__U32_1314 = 8;
    (void)hoisted__U32_1314;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1314;
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
    I64 hoisted__I64_1518 = 0;
    (void)hoisted__I64_1518;
    Bool hoisted__Bool_1519 = I64_eq(DEREF(val), hoisted__I64_1518);
    (void)hoisted__Bool_1519;
    if (hoisted__Bool_1519) {
        U64 hoisted__U64_1482 = 2;
        (void)hoisted__U64_1482;
        void * buf = malloc(hoisted__U64_1482);
        I64 hoisted__I64_1483 = 48;
        (void)hoisted__I64_1483;
        U64 hoisted__U64_1484 = 1;
        (void)hoisted__U64_1484;
        memcpy(buf, &hoisted__I64_1483, hoisted__U64_1484);
        U64 hoisted__U64_1485 = 1;
        (void)hoisted__U64_1485;
        void *hoisted__v_1486 = ptr_add(buf, hoisted__U64_1485);
        (void)hoisted__v_1486;
        (void)hoisted__v_1486;
        I32 hoisted__I32_1487 = 0;
        (void)hoisted__I32_1487;
        U64 hoisted__U64_1488 = 1;
        (void)hoisted__U64_1488;
        memset(hoisted__v_1486, hoisted__I32_1487, hoisted__U64_1488);
        I32_delete(&hoisted__I32_1487, &(Bool){0});
        I64 hoisted__I64_1489 = 1;
        (void)hoisted__I64_1489;
        I64 hoisted__I64_1490 = 1;
        (void)hoisted__I64_1490;
        Str *hoisted__Str_1491 = malloc(sizeof(Str));
        hoisted__Str_1491->c_str = buf;
        hoisted__Str_1491->count = hoisted__I64_1489;
        hoisted__Str_1491->cap = hoisted__I64_1490;
        (void)hoisted__Str_1491;
        { Str * _ret_val = hoisted__Str_1491;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_1520 = 0;
    (void)hoisted__I64_1520;
    Bool hoisted__Bool_1521 = I64_lt(val, &hoisted__I64_1520);
    (void)hoisted__Bool_1521;
    if (hoisted__Bool_1521) {
        Bool hoisted__Bool_1492 = 1;
        (void)hoisted__Bool_1492;
        is_neg = hoisted__Bool_1492;
        I64 hoisted__I64_1493 = 0;
        (void)hoisted__I64_1493;
        I64 hoisted__I64_1494 = I64_sub(hoisted__I64_1493, DEREF(val));
        (void)hoisted__I64_1494;
        v = hoisted__I64_1494;
    }
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1496 = 0;
        (void)hoisted__I64_1496;
        Bool _wcond_Bool_1495 = I64_gt(&tmp, &hoisted__I64_1496);
        (void)_wcond_Bool_1495;
        if (_wcond_Bool_1495) {
        } else {
            break;
        }
        U64 hoisted__U64_1497 = 1;
        (void)hoisted__U64_1497;
        U64 hoisted__U64_1498 = U64_add(ndigits, hoisted__U64_1497);
        (void)hoisted__U64_1498;
        ndigits = hoisted__U64_1498;
        I64 hoisted__I64_1499 = 10;
        (void)hoisted__I64_1499;
        I64 hoisted__I64_1500 = I64_div(tmp, hoisted__I64_1499);
        (void)hoisted__I64_1500;
        tmp = hoisted__I64_1500;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1501 = 1;
        (void)hoisted__U64_1501;
        U64 hoisted__U64_1502 = U64_add(total, hoisted__U64_1501);
        (void)hoisted__U64_1502;
        total = hoisted__U64_1502;
    }
    U64 hoisted__U64_1522 = 1;
    (void)hoisted__U64_1522;
    U64 hoisted__U64_1523 = U64_add(total, hoisted__U64_1522);
    (void)hoisted__U64_1523;
    void * buf = malloc(hoisted__U64_1523);
    if (is_neg) {
        I64 hoisted__I64_1503 = 45;
        (void)hoisted__I64_1503;
        U64 hoisted__U64_1504 = 1;
        (void)hoisted__U64_1504;
        memcpy(buf, &hoisted__I64_1503, hoisted__U64_1504);
    }
    U64 hoisted__U64_1524 = 1;
    (void)hoisted__U64_1524;
    U64 i = U64_sub(total, hoisted__U64_1524);
    while (1) {
        I64 hoisted__I64_1506 = 0;
        (void)hoisted__I64_1506;
        Bool _wcond_Bool_1505 = I64_gt(&v, &hoisted__I64_1506);
        (void)_wcond_Bool_1505;
        if (_wcond_Bool_1505) {
        } else {
            break;
        }
        I64 hoisted__I64_1507 = 10;
        (void)hoisted__I64_1507;
        I64 hoisted__I64_1508 = I64_mod(v, hoisted__I64_1507);
        (void)hoisted__I64_1508;
        I64 hoisted__I64_1509 = 48;
        (void)hoisted__I64_1509;
        I64 hoisted__I64_1510 = I64_add(hoisted__I64_1508, hoisted__I64_1509);
        (void)hoisted__I64_1510;
        void *hoisted__v_1511 = ptr_add(buf, i);
        (void)hoisted__v_1511;
        (void)hoisted__v_1511;
        U8 hoisted__U8_1512 = I64_to_u8(hoisted__I64_1510);
        (void)hoisted__U8_1512;
        U64 hoisted__U64_1513 = 1;
        (void)hoisted__U64_1513;
        memcpy(hoisted__v_1511, &hoisted__U8_1512, hoisted__U64_1513);
        U8_delete(&hoisted__U8_1512, &(Bool){0});
        I64 hoisted__I64_1514 = 10;
        (void)hoisted__I64_1514;
        I64 hoisted__I64_1515 = I64_div(v, hoisted__I64_1514);
        (void)hoisted__I64_1515;
        v = hoisted__I64_1515;
        U64 hoisted__U64_1516 = 1;
        (void)hoisted__U64_1516;
        U64 hoisted__U64_1517 = U64_sub(i, hoisted__U64_1516);
        (void)hoisted__U64_1517;
        i = hoisted__U64_1517;
    }
    void *hoisted__v_1525 = ptr_add(buf, total);
    (void)hoisted__v_1525;
    (void)hoisted__v_1525;
    I32 hoisted__I32_1526 = 0;
    (void)hoisted__I32_1526;
    U64 hoisted__U64_1527 = 1;
    (void)hoisted__U64_1527;
    memset(hoisted__v_1525, hoisted__I32_1526, hoisted__U64_1527);
    I32_delete(&hoisted__I32_1526, &(Bool){0});
    Str *hoisted__Str_1528 = malloc(sizeof(Str));
    hoisted__Str_1528->c_str = buf;
    hoisted__Str_1528->count = total;
    hoisted__Str_1528->cap = total;
    (void)hoisted__Str_1528;
    return hoisted__Str_1528;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    U32 hoisted__U32_1546 = 8;
    (void)hoisted__U32_1546;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1546;
    return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1679 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1679;
    I64 hoisted__I64_1680 = -1;
    (void)hoisted__I64_1680;
    Bool hoisted__Bool_1681 = I64_eq(hoisted__I64_1679, hoisted__I64_1680);
    (void)hoisted__Bool_1681;
    return hoisted__Bool_1681;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1682 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1682;
    I64 hoisted__I64_1683 = 1;
    (void)hoisted__I64_1683;
    Bool hoisted__Bool_1684 = I64_eq(hoisted__I64_1682, hoisted__I64_1683);
    (void)hoisted__Bool_1684;
    return hoisted__Bool_1684;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1685 = I64_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1685;
    Bool hoisted__Bool_1686 = not(hoisted__Bool_1685);
    (void)hoisted__Bool_1686;
    return hoisted__Bool_1686;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1700 = Bool_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1700;
    if (hoisted__Bool_1700) {
        I64 hoisted__I64_1698 = 0;
        (void)hoisted__I64_1698;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1698;
                return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1699 = -1;
        (void)hoisted__I64_1699;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1699;
        return _r; }
    }
    I64 hoisted__I64_1701 = 1;
    (void)hoisted__I64_1701;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1701;
    return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    U32 hoisted__U32_1702 = 1;
    (void)hoisted__U32_1702;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1702;
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
    Bool hoisted__Bool_1841 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1841;
    if (hoisted__Bool_1841) {
        Bool hoisted__Bool_1839 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1839;
        { Bool _ret_val = hoisted__Bool_1839;
                return _ret_val; }
    }
    Bool hoisted__Bool_1842 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1842;
    if (hoisted__Bool_1842) {
        Bool hoisted__Bool_1840 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1840;
        { Bool _ret_val = hoisted__Bool_1840;
                return _ret_val; }
    }
    Bool hoisted__Bool_1843 = 0;
    (void)hoisted__Bool_1843;
    return hoisted__Bool_1843;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1849 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1849;
    if (hoisted__Bool_1849) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1850 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1850;
    if (hoisted__Bool_1850) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Str hoisted__Str_1851 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1851;
    UNREACHABLE(&hoisted__Str_1851);
    Str_delete(&hoisted__Str_1851, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1852 = 4;
    (void)hoisted__U32_1852;
    return hoisted__U32_1852;
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
    Bool hoisted__Bool_1915 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1915;
    if (hoisted__Bool_1915) {
        Str *hoisted__Str_1907 = get_payload(self);
        (void)hoisted__Str_1907;
        (void)hoisted__Str_1907;
        Bool hoisted__Bool_1908 = 0;
        (void)hoisted__Bool_1908;
        Str_delete(hoisted__Str_1907, &hoisted__Bool_1908);
    }
    Bool hoisted__Bool_1916 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1916;
    if (hoisted__Bool_1916) {
        Str *hoisted__Str_1909 = get_payload(self);
        (void)hoisted__Str_1909;
        (void)hoisted__Str_1909;
        Bool hoisted__Bool_1910 = 0;
        (void)hoisted__Bool_1910;
        Str_delete(hoisted__Str_1909, &hoisted__Bool_1910);
    }
    Bool hoisted__Bool_1917 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1917;
    if (hoisted__Bool_1917) {
        Str *hoisted__Str_1911 = get_payload(self);
        (void)hoisted__Str_1911;
        (void)hoisted__Str_1911;
        Bool hoisted__Bool_1912 = 0;
        (void)hoisted__Bool_1912;
        Str_delete(hoisted__Str_1911, &hoisted__Bool_1912);
    }
    Bool hoisted__Bool_1918 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1918;
    if (hoisted__Bool_1918) {
        Primitive *hoisted__Primitive_1913 = get_payload(self);
        (void)hoisted__Primitive_1913;
        (void)hoisted__Primitive_1913;
        Bool hoisted__Bool_1914 = 0;
        (void)hoisted__Bool_1914;
        Primitive_delete(hoisted__Primitive_1913, &hoisted__Bool_1914);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2000 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2000;
    if (hoisted__Bool_2000) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2001 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2001;
    if (hoisted__Bool_2001) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2002 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)hoisted__Bool_2002;
    if (hoisted__Bool_2002) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2003 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)hoisted__Bool_2003;
    if (hoisted__Bool_2003) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2004 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)hoisted__Bool_2004;
    if (hoisted__Bool_2004) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2005 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)hoisted__Bool_2005;
    if (hoisted__Bool_2005) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2006 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)hoisted__Bool_2006;
    if (hoisted__Bool_2006) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2007 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)hoisted__Bool_2007;
    if (hoisted__Bool_2007) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2008 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)hoisted__Bool_2008;
    if (hoisted__Bool_2008) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool;
                return _r; }
    }
    Bool hoisted__Bool_2009 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2009;
    if (hoisted__Bool_2009) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_1994 = Str_clone(_clone_payload_Struct_9);
        (void)hoisted__Str_1994;
        Type *hoisted__Type_1995 = Type_Struct(hoisted__Str_1994);
        (void)hoisted__Type_1995;
        { Type * _ret_val = hoisted__Type_1995;
                return _ret_val; }
    }
    Bool hoisted__Bool_2010 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2010;
    if (hoisted__Bool_2010) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2011 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2011;
    if (hoisted__Bool_2011) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_1996 = Str_clone(_clone_payload_Enum_11);
        (void)hoisted__Str_1996;
        Type *hoisted__Type_1997 = Type_Enum(hoisted__Str_1996);
        (void)hoisted__Type_1997;
        { Type * _ret_val = hoisted__Type_1997;
                return _ret_val; }
    }
    Bool hoisted__Bool_2012 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2012;
    if (hoisted__Bool_2012) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2013 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2013;
    if (hoisted__Bool_2013) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2014 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2014;
    if (hoisted__Bool_2014) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2015 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2015;
    if (hoisted__Bool_2015) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2016 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2016;
    if (hoisted__Bool_2016) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_1998 = Str_clone(_clone_payload_Custom_16);
        (void)hoisted__Str_1998;
        Type *hoisted__Type_1999 = Type_Custom(hoisted__Str_1998);
        (void)hoisted__Type_1999;
        { Type * _ret_val = hoisted__Type_1999;
                return _ret_val; }
    }
    Bool hoisted__Bool_2017 = is(self, &(Type){.tag = Type_TAG_I8});
    (void)hoisted__Bool_2017;
    if (hoisted__Bool_2017) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8;
                return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive *hoisted__Primitive_2018 = Primitive_clone(_clone_payload_Primitive_18);
    (void)hoisted__Primitive_2018;
    Type *hoisted__Type_2019 = Type_Primitive(hoisted__Primitive_2018);
    (void)hoisted__Type_2019;
    return hoisted__Type_2019;
}

U32 Type_size(void) {
    U32 hoisted__U32_2020 = 24;
    (void)hoisted__U32_2020;
    return hoisted__U32_2020;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_3591 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3591;
    if (hoisted__Bool_3591) {
        Type *hoisted__Type_3586 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3586;
        U32 hoisted__U32_3587 = 1;
        (void)hoisted__U32_3587;
        Array *_va_Array_103 = Array_new(hoisted__Type_3586, &hoisted__U32_3587);
        (void)_va_Array_103;
        Type_delete(hoisted__Type_3586, &(Bool){1});
        U32 hoisted__U32_3588 = 0;
        (void)hoisted__U32_3588;
        Str hoisted__Str_3589 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3589;
        Array_set(_va_Array_103, &hoisted__U32_3588, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3589; _oa; }));
        Str hoisted__Str_3590 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3590;
        panic(&hoisted__Str_3590, _va_Array_103);
        Str_delete(&hoisted__Str_3590, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3592 = calloc(DEREF(cap), elem_size);
    (void)hoisted__v_3592;
    void * hoisted__v_3593 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3593;
    void * hoisted__v_3594 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3594;
    Array *hoisted__Array_3595 = malloc(sizeof(Array));
    hoisted__Array_3595->data = hoisted__v_3592;
    hoisted__Array_3595->cap = DEREF(cap);
    hoisted__Array_3595->elem_size = elem_size;
    hoisted__Array_3595->elem_clone = hoisted__v_3593;
    hoisted__Array_3595->elem_delete = hoisted__v_3594;
    (void)hoisted__Array_3595;
    return hoisted__Array_3595;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3596 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3596;
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_3596;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap;
    return _r; }
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3617 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3617;
    if (hoisted__Bool_3617) {
        Type *hoisted__Type_3598 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3598;
        U32 hoisted__U32_3599 = 6;
        (void)hoisted__U32_3599;
        Array *_va_Array_104 = Array_new(hoisted__Type_3598, &hoisted__U32_3599);
        (void)_va_Array_104;
        Type_delete(hoisted__Type_3598, &(Bool){1});
        U32 hoisted__U32_3600 = 0;
        (void)hoisted__U32_3600;
        Str hoisted__Str_3601 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3601;
        Array_set(_va_Array_104, &hoisted__U32_3600, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3601; _oa; }));
        U32 hoisted__U32_3602 = 1;
        (void)hoisted__U32_3602;
        Str hoisted__Str_3603 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3603;
        Array_set(_va_Array_104, &hoisted__U32_3602, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3603; _oa; }));
        U32 hoisted__U32_3604 = 2;
        (void)hoisted__U32_3604;
        Str *hoisted__Str_3605 = U32_to_str(i);
        (void)hoisted__Str_3605;
        Array_set(_va_Array_104, &hoisted__U32_3604, hoisted__Str_3605);
        U32 hoisted__U32_3606 = 3;
        (void)hoisted__U32_3606;
        Str hoisted__Str_3607 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3607;
        Array_set(_va_Array_104, &hoisted__U32_3606, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3607; _oa; }));
        U32 hoisted__U32_3608 = 4;
        (void)hoisted__U32_3608;
        Str *hoisted__Str_3609 = U32_to_str(&self->cap);
        (void)hoisted__Str_3609;
        Array_set(_va_Array_104, &hoisted__U32_3608, hoisted__Str_3609);
        U32 hoisted__U32_3610 = 5;
        (void)hoisted__U32_3610;
        Str hoisted__Str_3611 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3611;
        Array_set(_va_Array_104, &hoisted__U32_3610, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3611; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3612 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_104); hoisted__OutOfBounds_3612->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3612;
        U32 hoisted__U32_3613 = 16;
        (void)hoisted__U32_3613;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3612, hoisted__U32_3613);
        OutOfBounds_delete(hoisted__OutOfBounds_3612, &(Bool){1});
        I64 hoisted__I64_3614 = 3;
        (void)hoisted__I64_3614;
        *_err_kind = hoisted__I64_3614;
    }
    I64 hoisted__I64_3618 = 0;
    (void)hoisted__I64_3618;
    Bool hoisted__Bool_3619 = I64_eq(DEREF(_err_kind), hoisted__I64_3618);
    (void)hoisted__Bool_3619;
    if (hoisted__Bool_3619) {
        U32 hoisted__U64_3615 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3615;
        void *hoisted__v_3616 = ptr_add(self->data, hoisted__U64_3615);
        (void)hoisted__v_3616;
        (void)hoisted__v_3616;
        { void * _ret_val = hoisted__v_3616;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_3634 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3634;
    if (hoisted__Bool_3634) {
        Type *hoisted__Type_3621 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3621;
        U32 hoisted__U32_3622 = 5;
        (void)hoisted__U32_3622;
        Array *_va_Array_105 = Array_new(hoisted__Type_3621, &hoisted__U32_3622);
        (void)_va_Array_105;
        Type_delete(hoisted__Type_3621, &(Bool){1});
        U32 hoisted__U32_3623 = 0;
        (void)hoisted__U32_3623;
        Str hoisted__Str_3624 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3624;
        Array_set(_va_Array_105, &hoisted__U32_3623, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3624; _oa; }));
        U32 hoisted__U32_3625 = 1;
        (void)hoisted__U32_3625;
        Str *hoisted__Str_3626 = U32_to_str(i);
        (void)hoisted__Str_3626;
        Array_set(_va_Array_105, &hoisted__U32_3625, hoisted__Str_3626);
        U32 hoisted__U32_3627 = 2;
        (void)hoisted__U32_3627;
        Str hoisted__Str_3628 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3628;
        Array_set(_va_Array_105, &hoisted__U32_3627, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3628; _oa; }));
        U32 hoisted__U32_3629 = 3;
        (void)hoisted__U32_3629;
        Str *hoisted__Str_3630 = U32_to_str(&self->cap);
        (void)hoisted__Str_3630;
        Array_set(_va_Array_105, &hoisted__U32_3629, hoisted__Str_3630);
        U32 hoisted__U32_3631 = 4;
        (void)hoisted__U32_3631;
        Str hoisted__Str_3632 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3632;
        Array_set(_va_Array_105, &hoisted__U32_3631, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3632; _oa; }));
        Str hoisted__Str_3633 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3633;
        panic(&hoisted__Str_3633, _va_Array_105);
        Str_delete(&hoisted__Str_3633, &(Bool){0});
    }
    U32 hoisted__U64_3635 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3635;
    void *hoisted__v_3636 = ptr_add(self->data, hoisted__U64_3635);
    (void)hoisted__v_3636;
    (void)hoisted__v_3636;
    Bool hoisted__Bool_3637 = 0;
    (void)hoisted__Bool_3637;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3636, &hoisted__Bool_3637);
    U32 hoisted__U64_3638 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3638;
    void *hoisted__v_3639 = ptr_add(self->data, hoisted__U64_3638);
    (void)hoisted__v_3639;
    (void)hoisted__v_3639;
    memcpy(hoisted__v_3639, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_3640 = self->cap;
        (void)_re_U32_3640;
        U32 _rc_U32_3640 = 0;
        (void)_rc_U32_3640;
        Bool hoisted__Bool_3649 = U32_lte(&_rc_U32_3640, &_re_U32_3640);
        (void)hoisted__Bool_3649;
        if (hoisted__Bool_3649) {
            while (1) {
                Bool _wcond_Bool_3641 = U32_lt(&_rc_U32_3640, &_re_U32_3640);
                (void)_wcond_Bool_3641;
                if (_wcond_Bool_3641) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3640);
                U32_inc(&_rc_U32_3640);
                U32 hoisted__U64_3642 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3642;
                void *hoisted__v_3643 = ptr_add(self->data, hoisted__U64_3642);
                (void)hoisted__v_3643;
                (void)hoisted__v_3643;
                Bool hoisted__Bool_3644 = 0;
                (void)hoisted__Bool_3644;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3643, &hoisted__Bool_3644);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3645 = U32_gt(&_rc_U32_3640, &_re_U32_3640);
                (void)_wcond_Bool_3645;
                if (_wcond_Bool_3645) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3640);
                U32_dec(&_rc_U32_3640);
                U32 hoisted__U64_3646 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3646;
                void *hoisted__v_3647 = ptr_add(self->data, hoisted__U64_3646);
                (void)hoisted__v_3647;
                (void)hoisted__v_3647;
                Bool hoisted__Bool_3648 = 0;
                (void)hoisted__Bool_3648;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3647, &hoisted__Bool_3648);
            }
        }
    }
    free(self->data);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3662 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3662;
    void * new_data = malloc(hoisted__U64_3662);
    {
        U32 _re_U32_3650 = self->cap;
        (void)_re_U32_3650;
        U32 _rc_U32_3650 = 0;
        (void)_rc_U32_3650;
        Bool hoisted__Bool_3661 = U32_lte(&_rc_U32_3650, &_re_U32_3650);
        (void)hoisted__Bool_3661;
        if (hoisted__Bool_3661) {
            while (1) {
                Bool _wcond_Bool_3651 = U32_lt(&_rc_U32_3650, &_re_U32_3650);
                (void)_wcond_Bool_3651;
                if (_wcond_Bool_3651) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3650);
                U32_inc(&_rc_U32_3650);
                U32 hoisted__U64_3652 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3652;
                void *hoisted__v_3653 = ptr_add(self->data, hoisted__U64_3652);
                (void)hoisted__v_3653;
                (void)hoisted__v_3653;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3653);
                U32 hoisted__U64_3654 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3654;
                void *hoisted__v_3655 = ptr_add(new_data, hoisted__U64_3654);
                (void)hoisted__v_3655;
                (void)hoisted__v_3655;
                memcpy(hoisted__v_3655, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3656 = U32_gt(&_rc_U32_3650, &_re_U32_3650);
                (void)_wcond_Bool_3656;
                if (_wcond_Bool_3656) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3650);
                U32_dec(&_rc_U32_3650);
                U32 hoisted__U64_3657 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3657;
                void *hoisted__v_3658 = ptr_add(self->data, hoisted__U64_3657);
                (void)hoisted__v_3658;
                (void)hoisted__v_3658;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3658);
                U32 hoisted__U64_3659 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3659;
                void *hoisted__v_3660 = ptr_add(new_data, hoisted__U64_3659);
                (void)hoisted__v_3660;
                (void)hoisted__v_3660;
                memcpy(hoisted__v_3660, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3663 = malloc(sizeof(Array));
    hoisted__Array_3663->data = new_data;
    hoisted__Array_3663->cap = self->cap;
    hoisted__Array_3663->elem_size = self->elem_size;
    hoisted__Array_3663->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3663->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3663;
    return hoisted__Array_3663;
}

U32 Array_size(void) {
    U32 hoisted__U32_3664 = 32;
    (void)hoisted__U32_3664;
    return hoisted__U32_3664;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_3902 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_3902;
    U32 hoisted__U32_3903 = 3;
    (void)hoisted__U32_3903;
    Array *_va_Array_122 = Array_new(hoisted__Type_3902, &hoisted__U32_3903);
    (void)_va_Array_122;
    Type_delete(hoisted__Type_3902, &(Bool){1});
    U32 hoisted__U32_3904 = 0;
    (void)hoisted__U32_3904;
    Str *hoisted__Str_3905 = Str_clone(loc_str);
    (void)hoisted__Str_3905;
    Array_set(_va_Array_122, &hoisted__U32_3904, hoisted__Str_3905);
    U32 hoisted__U32_3906 = 1;
    (void)hoisted__U32_3906;
    Str hoisted__Str_3907 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3907;
    Array_set(_va_Array_122, &hoisted__U32_3906, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3907; _oa; }));
    Array *hoisted__Array_3908 = Array_clone(parts);
    (void)hoisted__Array_3908;
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_3909 = 2;
    (void)hoisted__U32_3909;
    Str *hoisted__Str_3910 = format(hoisted__Array_3908);
    (void)hoisted__Str_3910;
    Array_set(_va_Array_122, &hoisted__U32_3909, hoisted__Str_3910);
    println(_va_Array_122);
    I64 hoisted__I64_3911 = 1;
    (void)hoisted__I64_3911;
    exit(hoisted__I64_3911);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_3921 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_3921;
    U32 hoisted__U32_3922 = 1;
    (void)hoisted__U32_3922;
    Array *_va_Array_124 = Array_new(hoisted__Type_3921, &hoisted__U32_3922);
    (void)_va_Array_124;
    Type_delete(hoisted__Type_3921, &(Bool){1});
    U32 hoisted__U32_3923 = 0;
    (void)hoisted__U32_3923;
    Str hoisted__Str_3924 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3924;
    Array_set(_va_Array_124, &hoisted__U32_3923, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3924; _oa; }));
    panic(loc_str, _va_Array_124);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_3930 = not(DEREF(cond));
    (void)hoisted__Bool_3930;
    if (hoisted__Bool_3930) {
        Type *hoisted__Type_3926 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3926;
        U32 hoisted__U32_3927 = 1;
        (void)hoisted__U32_3927;
        Array *_va_Array_125 = Array_new(hoisted__Type_3926, &hoisted__U32_3927);
        (void)_va_Array_125;
        Type_delete(hoisted__Type_3926, &(Bool){1});
        U32 hoisted__U32_3928 = 0;
        (void)hoisted__U32_3928;
        Str hoisted__Str_3929 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3929;
        Array_set(_va_Array_125, &hoisted__U32_3928, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3929; _oa; }));
        panic(loc_str, _va_Array_125);
    }
    Bool hoisted__Bool_3931 = 1;
    (void)hoisted__Bool_3931;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_3931;
    return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_3954 = I64_neq(a, b);
    (void)hoisted__Bool_3954;
    if (hoisted__Bool_3954) {
        Type *hoisted__Type_3942 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3942;
        U32 hoisted__U32_3943 = 5;
        (void)hoisted__U32_3943;
        Array *_va_Array_127 = Array_new(hoisted__Type_3942, &hoisted__U32_3943);
        (void)_va_Array_127;
        Type_delete(hoisted__Type_3942, &(Bool){1});
        U32 hoisted__U32_3944 = 0;
        (void)hoisted__U32_3944;
        Str hoisted__Str_3945 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3945;
        Array_set(_va_Array_127, &hoisted__U32_3944, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3945; _oa; }));
        U32 hoisted__U32_3946 = 1;
        (void)hoisted__U32_3946;
        Str *hoisted__Str_3947 = I64_to_str(a);
        (void)hoisted__Str_3947;
        Array_set(_va_Array_127, &hoisted__U32_3946, hoisted__Str_3947);
        U32 hoisted__U32_3948 = 2;
        (void)hoisted__U32_3948;
        Str hoisted__Str_3949 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3949;
        Array_set(_va_Array_127, &hoisted__U32_3948, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3949; _oa; }));
        U32 hoisted__U32_3950 = 3;
        (void)hoisted__U32_3950;
        Str *hoisted__Str_3951 = I64_to_str(b);
        (void)hoisted__Str_3951;
        Array_set(_va_Array_127, &hoisted__U32_3950, hoisted__Str_3951);
        U32 hoisted__U32_3952 = 4;
        (void)hoisted__U32_3952;
        Str hoisted__Str_3953 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3953;
        Array_set(_va_Array_127, &hoisted__U32_3952, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3953; _oa; }));
        panic(loc_str, _va_Array_127);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_3968 = Str_eq(a, b);
    (void)hoisted__Bool_3968;
    Bool hoisted__Bool_3969 = not(hoisted__Bool_3968);
    (void)hoisted__Bool_3969;
    if (hoisted__Bool_3969) {
        Type *hoisted__Type_3956 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3956;
        U32 hoisted__U32_3957 = 5;
        (void)hoisted__U32_3957;
        Array *_va_Array_128 = Array_new(hoisted__Type_3956, &hoisted__U32_3957);
        (void)_va_Array_128;
        Type_delete(hoisted__Type_3956, &(Bool){1});
        U32 hoisted__U32_3958 = 0;
        (void)hoisted__U32_3958;
        Str hoisted__Str_3959 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3959;
        Array_set(_va_Array_128, &hoisted__U32_3958, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3959; _oa; }));
        U32 hoisted__U32_3960 = 1;
        (void)hoisted__U32_3960;
        Str *hoisted__Str_3961 = Str_clone(a);
        (void)hoisted__Str_3961;
        Array_set(_va_Array_128, &hoisted__U32_3960, hoisted__Str_3961);
        U32 hoisted__U32_3962 = 2;
        (void)hoisted__U32_3962;
        Str hoisted__Str_3963 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3963;
        Array_set(_va_Array_128, &hoisted__U32_3962, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3963; _oa; }));
        U32 hoisted__U32_3964 = 3;
        (void)hoisted__U32_3964;
        Str *hoisted__Str_3965 = Str_clone(b);
        (void)hoisted__Str_3965;
        Array_set(_va_Array_128, &hoisted__U32_3964, hoisted__Str_3965);
        U32 hoisted__U32_3966 = 4;
        (void)hoisted__U32_3966;
        Str hoisted__Str_3967 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3967;
        Array_set(_va_Array_128, &hoisted__U32_3966, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3967; _oa; }));
        panic(loc_str, _va_Array_128);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_3970 = parts;
        (void)_fc_Array_3970;
        (void)_fc_Array_3970;
        U32 _fi_USize_3970 = 0;
        (void)_fi_USize_3970;
        I64 _forin_err_kind_3970 = 0;
        (void)_forin_err_kind_3970;
        OutOfBounds *_forin_OutOfBounds_3970 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_3970->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_3970;
        while (1) {
            U32 hoisted__U32_3978; { U32 *_hp = (U32 *)Array_len(_fc_Array_3970); hoisted__U32_3978 = *_hp; free(_hp); }
            (void)hoisted__U32_3978;
            Bool _wcond_Bool_3971 = U32_lt(&_fi_USize_3970, &hoisted__U32_3978);
            (void)_wcond_Bool_3971;
            if (_wcond_Bool_3971) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_3970, &_fi_USize_3970, &_forin_err_kind_3970, _forin_OutOfBounds_3970);
            I64 hoisted__I64_3979 = 0;
            (void)hoisted__I64_3979;
            Bool hoisted__Bool_3980 = I64_eq(_forin_err_kind_3970, hoisted__I64_3979);
            (void)hoisted__Bool_3980;
            Bool hoisted__Bool_3981 = not(hoisted__Bool_3980);
            (void)hoisted__Bool_3981;
            if (hoisted__Bool_3981) {
                Type *hoisted__Type_3973 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_3973;
                U32 hoisted__U32_3974 = 1;
                (void)hoisted__U32_3974;
                Array *_va_Array_129 = Array_new(hoisted__Type_3973, &hoisted__U32_3974);
                (void)_va_Array_129;
                Type_delete(hoisted__Type_3973, &(Bool){1});
                U32 hoisted__U32_3975 = 0;
                (void)hoisted__U32_3975;
                Str hoisted__Str_3976 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_3976;
                Array_set(_va_Array_129, &hoisted__U32_3975, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3976; _oa; }));
                Str hoisted__Str_3977 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_3977;
                panic(&hoisted__Str_3977, _va_Array_129);
                Str_delete(&hoisted__Str_3977, &(Bool){0});
            }
            U32 hoisted__U32_3982 = 1;
            (void)hoisted__U32_3982;
            U32 hoisted__U32_3983 = U32_add(_fi_USize_3970, hoisted__U32_3982);
            (void)hoisted__U32_3983;
            _fi_USize_3970 = hoisted__U32_3983;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_3970, &(Bool){1});
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
    Str hoisted__Str_4135 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4135;
    I64 hoisted__I64_4136 = 3;
    (void)hoisted__I64_4136;
    assert_eq(&hoisted__Str_4135, &result, &hoisted__I64_4136);
    Str_delete(&hoisted__Str_4135, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4143 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4143;
    I64 hoisted__I64_4144 = 15;
    (void)hoisted__I64_4144;
    assert_eq(&hoisted__Str_4143, &result, &hoisted__I64_4144);
    Str_delete(&hoisted__Str_4143, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4151 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4151;
    I64 hoisted__I64_4152 = 26;
    (void)hoisted__I64_4152;
    assert_eq(&hoisted__Str_4151, &result, &hoisted__I64_4152);
    Str_delete(&hoisted__Str_4151, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4155 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4155;
    Str hoisted__Str_4156 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4156;
    assert_eq_str(&hoisted__Str_4155, &result, &hoisted__Str_4156);
    Str_delete(&hoisted__Str_4155, &(Bool){0});
    Str_delete(&hoisted__Str_4156, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4487 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4487;
    assert_eq_str(&hoisted__Str_4487, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4487, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_4488 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4488;
    assert_eq_str(&hoisted__Str_4488, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4488, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4490 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4490;
    I64 hoisted__I64_4491 = 8;
    (void)hoisted__I64_4491;
    assert_eq(&hoisted__Str_4490, &result, &hoisted__I64_4491);
    Str_delete(&hoisted__Str_4490, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4494 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4494;
    Bool hoisted__Bool_4495 = 1;
    (void)hoisted__Bool_4495;
    Bool_delete(assert(&hoisted__Str_4494, &hoisted__Bool_4495), &(Bool){1});
    Str_delete(&hoisted__Str_4494, &(Bool){0});
    Str hoisted__Str_4499 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4499;
    Bool hoisted__Bool_4500 = 1;
    (void)hoisted__Bool_4500;
    Bool_delete(assert(&hoisted__Str_4499, &hoisted__Bool_4500), &(Bool){1});
    Str_delete(&hoisted__Str_4499, &(Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4506 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4506;
    Str hoisted__Str_4507 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4507;
    Str hoisted__Str_4508 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4508;
    assert_eq_str(&hoisted__Str_4506, &hoisted__Str_4507, &hoisted__Str_4508);
    Str_delete(&hoisted__Str_4506, &(Bool){0});
    Str_delete(&hoisted__Str_4507, &(Bool){0});
    Str_delete(&hoisted__Str_4508, &(Bool){0});
    Str hoisted__Str_4511 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4511;
    Str hoisted__Str_4512 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4512;
    Str hoisted__Str_4513 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4513;
    assert_eq_str(&hoisted__Str_4511, &hoisted__Str_4512, &hoisted__Str_4513);
    Str_delete(&hoisted__Str_4511, &(Bool){0});
    Str_delete(&hoisted__Str_4512, &(Bool){0});
    Str_delete(&hoisted__Str_4513, &(Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4518 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4518;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4518;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4519 = 16;
    (void)hoisted__U32_4519;
    return hoisted__U32_4519;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4520 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4520;
    I64 hoisted__I64_4521 = 42;
    (void)hoisted__I64_4521;
    assert_eq(&hoisted__Str_4520, &v.x, &hoisted__I64_4521);
    Str_delete(&hoisted__Str_4520, &(Bool){0});
    Str hoisted__Str_4522 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4522;
    I64 hoisted__I64_4523 = 99;
    (void)hoisted__I64_4523;
    assert_eq(&hoisted__Str_4522, &v.y, &hoisted__I64_4523);
    Str_delete(&hoisted__Str_4522, &(Bool){0});
    CfVec2_delete(&v, &(Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4526 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4526;
    I64 hoisted__I64_4527 = 10;
    (void)hoisted__I64_4527;
    assert_eq(&hoisted__Str_4526, &p.x, &hoisted__I64_4527);
    Str_delete(&hoisted__Str_4526, &(Bool){0});
    Str hoisted__Str_4528 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4528;
    I64 hoisted__I64_4529 = 20;
    (void)hoisted__I64_4529;
    assert_eq(&hoisted__Str_4528, &p.y, &hoisted__I64_4529);
    Str_delete(&hoisted__Str_4528, &(Bool){0});
    CfVec2_delete(&p, &(Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4535 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4535;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4535;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4536 = 32;
    (void)hoisted__U32_4536;
    return hoisted__U32_4536;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4537 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4537;
    I64 hoisted__I64_4538 = 5;
    (void)hoisted__I64_4538;
    assert_eq(&hoisted__Str_4537, &r.top_left.x, &hoisted__I64_4538);
    Str_delete(&hoisted__Str_4537, &(Bool){0});
    Str hoisted__Str_4539 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4539;
    I64 hoisted__I64_4540 = 10;
    (void)hoisted__I64_4540;
    assert_eq(&hoisted__Str_4539, &r.top_left.y, &hoisted__I64_4540);
    Str_delete(&hoisted__Str_4539, &(Bool){0});
    Str hoisted__Str_4541 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4541;
    I64 hoisted__I64_4542 = 100;
    (void)hoisted__I64_4542;
    assert_eq(&hoisted__Str_4541, &r.bottom_right.x, &hoisted__I64_4542);
    Str_delete(&hoisted__Str_4541, &(Bool){0});
    Str hoisted__Str_4543 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4543;
    I64 hoisted__I64_4544 = 200;
    (void)hoisted__I64_4544;
    assert_eq(&hoisted__Str_4543, &r.bottom_right.y, &hoisted__I64_4544);
    Str_delete(&hoisted__Str_4543, &(Bool){0});
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
    Bool hoisted__Bool_4549 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4549;
    if (hoisted__Bool_4549) {
        Bool hoisted__Bool_4546 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4546;
        { Bool _ret_val = hoisted__Bool_4546;
                return _ret_val; }
    }
    Bool hoisted__Bool_4550 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4550;
    if (hoisted__Bool_4550) {
        Bool hoisted__Bool_4547 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4547;
        { Bool _ret_val = hoisted__Bool_4547;
                return _ret_val; }
    }
    Bool hoisted__Bool_4551 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4551;
    if (hoisted__Bool_4551) {
        Bool hoisted__Bool_4548 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4548;
        { Bool _ret_val = hoisted__Bool_4548;
                return _ret_val; }
    }
    Bool hoisted__Bool_4552 = 0;
    (void)hoisted__Bool_4552;
    return hoisted__Bool_4552;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4560 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4560;
    if (hoisted__Bool_4560) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4561 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4561;
    if (hoisted__Bool_4561) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4562 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4562;
    if (hoisted__Bool_4562) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4563 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4563;
    UNREACHABLE(&hoisted__Str_4563);
    Str_delete(&hoisted__Str_4563, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4564 = 4;
    (void)hoisted__U32_4564;
    return hoisted__U32_4564;
}


void test_enum_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Str hoisted__Str_4565 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4565;
    Bool hoisted__Bool_4566 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4566;
    Bool_delete(assert(&hoisted__Str_4565, &hoisted__Bool_4566), &(Bool){1});
    Str_delete(&hoisted__Str_4565, &(Bool){0});
    Bool hoisted__Bool_4568 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4568;
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_4569 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4569;
    Bool hoisted__Bool_4570 = not(hoisted__Bool_4568);
    (void)hoisted__Bool_4570;
    Bool_delete(assert(&hoisted__Str_4569, &hoisted__Bool_4570), &(Bool){1});
    Str_delete(&hoisted__Str_4569, &(Bool){0});
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
    Bool hoisted__Bool_4572 = is(self, other);
    (void)hoisted__Bool_4572;
    return hoisted__Bool_4572;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_4590 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4590;
    if (hoisted__Bool_4590) {
        I64 *hoisted__I64_4586 = get_payload(self);
        (void)hoisted__I64_4586;
        (void)hoisted__I64_4586;
        Bool hoisted__Bool_4587 = 0;
        (void)hoisted__Bool_4587;
        I64_delete(hoisted__I64_4586, &hoisted__Bool_4587);
    }
    Bool hoisted__Bool_4591 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4591;
    if (hoisted__Bool_4591) {
        Str *hoisted__Str_4588 = get_payload(self);
        (void)hoisted__Str_4588;
        (void)hoisted__Str_4588;
        Bool hoisted__Bool_4589 = 0;
        (void)hoisted__Bool_4589;
        Str_delete(hoisted__Str_4588, &hoisted__Bool_4589);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4620 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4620;
    if (hoisted__Bool_4620) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4617 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4617;
        { Token * _ret_val = hoisted__Token_4617;
                return _ret_val; }
    }
    Bool hoisted__Bool_4621 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4621;
    if (hoisted__Bool_4621) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4618 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4618;
        Token *hoisted__Token_4619 = Token_Name(hoisted__Str_4618);
        (void)hoisted__Token_4619;
        { Token * _ret_val = hoisted__Token_4619;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4622 = 24;
    (void)hoisted__U32_4622;
    return hoisted__U32_4622;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_4624 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4624;
    Bool hoisted__Bool_4625 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4625;
    Bool_delete(assert(&hoisted__Str_4624, &hoisted__Bool_4625), &(Bool){1});
    Str_delete(&hoisted__Str_4624, &(Bool){0});
    Bool hoisted__Bool_4627 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4627;
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_4628 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4628;
    Bool hoisted__Bool_4629 = not(hoisted__Bool_4627);
    (void)hoisted__Bool_4629;
    Bool_delete(assert(&hoisted__Str_4628, &hoisted__Bool_4629), &(Bool){1});
    Str_delete(&hoisted__Str_4628, &(Bool){0});
}

void test_enum_return_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Green});
    Str hoisted__Str_4631 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4631;
    Bool hoisted__Bool_4632 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4632;
    Bool_delete(assert(&hoisted__Str_4631, &hoisted__Bool_4632), &(Bool){1});
    Str_delete(&hoisted__Str_4631, &(Bool){0});
    Bool hoisted__Bool_4634 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4634;
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_4635 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4635;
    Bool hoisted__Bool_4636 = not(hoisted__Bool_4634);
    (void)hoisted__Bool_4636;
    Bool_delete(assert(&hoisted__Str_4635, &hoisted__Bool_4636), &(Bool){1});
    Str_delete(&hoisted__Str_4635, &(Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_4640 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4640;
    Bool hoisted__Bool_4641 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4641;
    Bool_delete(assert(&hoisted__Str_4640, &hoisted__Bool_4641), &(Bool){1});
    Str_delete(&hoisted__Str_4640, &(Bool){0});
    Bool hoisted__Bool_4643 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4643;
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_4644 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4644;
    Bool hoisted__Bool_4645 = not(hoisted__Bool_4643);
    (void)hoisted__Bool_4645;
    Bool_delete(assert(&hoisted__Str_4644, &hoisted__Bool_4645), &(Bool){1});
    Str_delete(&hoisted__Str_4644, &(Bool){0});
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
