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
    Primitive_TAG_U16,
    Primitive_TAG_I8,
    Primitive_TAG_U8,
    Primitive_TAG_U32,
    Primitive_TAG_I32,
    Primitive_TAG_U64,
    Primitive_TAG_I64,
    Primitive_TAG_F32,
    Primitive_TAG_Bool
} Primitive_tag;
typedef struct Primitive Primitive;
typedef enum {
    Type_TAG_Unknown,
    Type_TAG_None,
    Type_TAG_Struct,
    Type_TAG_StructDef,
    Type_TAG_Enum,
    Type_TAG_EnumDef,
    Type_TAG_FuncDef,
    Type_TAG_FuncPtr,
    Type_TAG_Dynamic,
    Type_TAG_Custom,
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
typedef void (*DeleteFn)(void *, Bool);
typedef U64 (*HashFn)(void *, U32);







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

void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Bool U32_lt(U32 a, U32 b);
Bool U32_gt(U32 a, U32 b);
Bool U32_lte(U32 a, U32 b);
Bool U32_gte(U32 a, U32 b);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * format(Array * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool call_free);
Bool Str_is_empty(Str * self);
U64 Str_hash(Str * self, HashFn hasher);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
U32 OutOfBounds_size(void);
U32 Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool _cf);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
Bool I64_lt(I64 a, I64 b);
Bool I64_gt(I64 a, I64 b);
Bool I64_neq(I64 a, I64 b);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
U32 Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
U32 Type_size(void);
Array * Array_new_type_name(Str * elem_type, U32 cap);
Array * Array_new(Type * T, U32 cap);
U32 Array_len(Array * self);
void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
void Array_set(Array * self, U32 i, void * val);
void Array_delete(Array * self, Bool call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
void panic(Str * loc_str, Array * parts);
void UNREACHABLE(Str * loc_str);
Bool assert(Str * loc_str, Bool cond);
void assert_eq(Str * loc_str, I64 a, I64 b);
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
void CfVec2_delete(CfVec2 * self, Bool call_free);
U64 CfVec2_hash(CfVec2 * self, HashFn hasher);
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
U32 CfRect_size(void);
void test_struct_fold_nested(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
U32 Color_size(void);
void test_enum_fold(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool call_free);
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

void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Bool U32_lt(U32 a, U32 b);
Bool U32_gt(U32 a, U32 b);
Bool U32_lte(U32 a, U32 b);
Bool U32_gte(U32 a, U32 b);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
Str * format(Array * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool call_free);
Bool Str_is_empty(Str * self);
U64 Str_hash(Str * self, HashFn hasher);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
U32 OutOfBounds_size(void);
U32 Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool _cf);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
Bool I64_lt(I64 a, I64 b);
Bool I64_gt(I64 a, I64 b);
Bool I64_neq(I64 a, I64 b);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
U32 Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
U32 Type_size(void);
Array * Array_new_type_name(Str * elem_type, U32 cap);
Array * Array_new(Type * T, U32 cap);
U32 Array_len(Array * self);
void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds);
void Array_set(Array * self, U32 i, void * val);
void Array_delete(Array * self, Bool call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
void panic(Str * loc_str, Array * parts);
void UNREACHABLE(Str * loc_str);
Bool assert(Str * loc_str, Bool cond);
void assert_eq(Str * loc_str, I64 a, I64 b);
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
void CfVec2_delete(CfVec2 * self, Bool call_free);
U64 CfVec2_hash(CfVec2 * self, HashFn hasher);
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
U32 CfRect_size(void);
void test_struct_fold_nested(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
U32 Color_size(void);
void test_enum_fold(void);
Token * Token_Num(I64 * val);
Token * Token_Name(Str * val);
Token * Token_Eof(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
U32 Token_size(void);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
Bool Primitive_eq(Primitive *, Primitive *);
Primitive *Primitive_I16();
Primitive *Primitive_U16();
Primitive *Primitive_I8();
Primitive *Primitive_U8();
Primitive *Primitive_U32();
Primitive *Primitive_I32();
Primitive *Primitive_U64();
Primitive *Primitive_I64();
Primitive *Primitive_F32();
Primitive *Primitive_Bool();
Bool * Type_eq(Type *, Type *);
Type *Type_Unknown();
Type *Type_None();
Type *Type_Struct(Str *);
Type *Type_StructDef();
Type *Type_Enum(Str *);
Type *Type_EnumDef();
Type *Type_FuncDef();
Type *Type_FuncPtr();
Type *Type_Dynamic();
Type *Type_Custom(Str *);
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

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 F32_size(void) {
    U32 hoisted__U32_1 = 4;
    (void)hoisted__U32_1;
    return hoisted__U32_1;
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_12 = 0;
    (void)hoisted__U32_12;
    U64 hoisted__U64_13 = ((U64 (*)(F32 *, U32))(void *)hasher)(&self, hoisted__U32_12);
    (void)hoisted__U64_13;
    return hoisted__U64_13;
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U64_size(void) {
    U32 hoisted__U32_37 = 8;
    (void)hoisted__U32_37;
    return hoisted__U32_37;
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_112 = 0;
    (void)hoisted__U32_112;
    U64 hoisted__U64_113 = ((U64 (*)(U64 *, U32))(void *)hasher)(&self, hoisted__U32_112);
    (void)hoisted__U64_113;
    return hoisted__U64_113;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_128 = U32_to_i64(val);
    (void)hoisted__I64_128;
    Str *hoisted__Str_129 = I64_to_str(hoisted__I64_128);
    (void)hoisted__Str_129;
    return hoisted__Str_129;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_130 = 1;
    (void)hoisted__U32_130;
    U32 hoisted__U32_131 = U32_add(DEREF(self), hoisted__U32_130);
    (void)hoisted__U32_131;
    *self = hoisted__U32_131;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_132 = 1;
    (void)hoisted__U32_132;
    U32 hoisted__U32_133 = U32_sub(DEREF(self), hoisted__U32_132);
    (void)hoisted__U32_133;
    *self = hoisted__U32_133;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_142 = 4;
    (void)hoisted__U32_142;
    return hoisted__U32_142;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_215 = 0;
    (void)hoisted__U32_215;
    U64 hoisted__U64_216 = ((U64 (*)(U32 *, U32))(void *)hasher)(&self, hoisted__U32_215);
    (void)hoisted__U64_216;
    return hoisted__U64_216;
}

Bool U32_lt(U32 a, U32 b) {
    I64 hoisted__I64_219 = U32_cmp(a, b);
    (void)hoisted__I64_219;
    I64 hoisted__I64_220 = -1;
    (void)hoisted__I64_220;
    Bool hoisted__Bool_221 = I64_eq(hoisted__I64_219, hoisted__I64_220);
    (void)hoisted__Bool_221;
    return hoisted__Bool_221;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_222 = U32_cmp(a, b);
    (void)hoisted__I64_222;
    I64 hoisted__I64_223 = 1;
    (void)hoisted__I64_223;
    Bool hoisted__Bool_224 = I64_eq(hoisted__I64_222, hoisted__I64_223);
    (void)hoisted__Bool_224;
    return hoisted__Bool_224;
}

Bool U32_lte(U32 a, U32 b) {
    Bool hoisted__Bool_227 = U32_gt(a, b);
    (void)hoisted__Bool_227;
    Bool hoisted__Bool_228 = not(hoisted__Bool_227);
    (void)hoisted__Bool_228;
    return hoisted__Bool_228;
}

Bool U32_gte(U32 a, U32 b) {
    Bool hoisted__Bool_229 = U32_lt(a, b);
    (void)hoisted__Bool_229;
    Bool hoisted__Bool_230 = not(hoisted__Bool_229);
    (void)hoisted__Bool_230;
    return hoisted__Bool_230;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_253 = 4;
    (void)hoisted__U32_253;
    return hoisted__U32_253;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_375 = 0;
    (void)hoisted__U32_375;
    U64 hoisted__U64_376 = ((U64 (*)(I32 *, U32))(void *)hasher)(&self, hoisted__U32_375);
    (void)hoisted__U64_376;
    return hoisted__U64_376;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_413 = 1;
    (void)hoisted__U32_413;
    return hoisted__U32_413;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_414 = 0;
    (void)hoisted__U32_414;
    U64 hoisted__U64_415 = ((U64 (*)(I8 *, U32))(void *)hasher)(&self, hoisted__U32_414);
    (void)hoisted__U64_415;
    return hoisted__U64_415;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_444 = 1;
    (void)hoisted__U32_444;
    return hoisted__U32_444;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_517 = 0;
    (void)hoisted__U32_517;
    U64 hoisted__U64_518 = ((U64 (*)(U8 *, U32))(void *)hasher)(&self, hoisted__U32_517);
    (void)hoisted__U64_518;
    return hoisted__U64_518;
}

Str * format(Array * parts) {
    U32 total = 0;
    {
        Array *_fc_Array_807 = parts;
        (void)_fc_Array_807;
        (void)_fc_Array_807;
        U32 _fi_USize_807 = 0;
        (void)_fi_USize_807;
        I64 _forin_err_kind_807 = 0;
        (void)_forin_err_kind_807;
        OutOfBounds *_forin_OutOfBounds_807 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_807->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_807;
        while (1) {
            U32 hoisted__U32_815 = Array_len(_fc_Array_807);
            (void)hoisted__U32_815;
            Bool _wcond_Bool_808 = U32_lt(_fi_USize_807, hoisted__U32_815);
            (void)_wcond_Bool_808;
            if (_wcond_Bool_808) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_807, &_fi_USize_807, &_forin_err_kind_807, _forin_OutOfBounds_807);
            I64 hoisted__I64_816 = 0;
            (void)hoisted__I64_816;
            Bool hoisted__Bool_817 = I64_eq(_forin_err_kind_807, hoisted__I64_816);
            (void)hoisted__Bool_817;
            Bool hoisted__Bool_818 = not(hoisted__Bool_817);
            (void)hoisted__Bool_818;
            if (hoisted__Bool_818) {
                Type *hoisted__Type_810 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_810;
                U32 hoisted__U32_811 = 1;
                (void)hoisted__U32_811;
                Array *_va_Array_24 = Array_new(hoisted__Type_810, hoisted__U32_811);
                (void)_va_Array_24;
                Type_delete(hoisted__Type_810, 1);
                U32 hoisted__U32_812 = 0;
                (void)hoisted__U32_812;
                Str hoisted__Str_813 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_813;
                Array_set(_va_Array_24, hoisted__U32_812, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_813; _oa; }));
                Str hoisted__Str_814 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_814;
                panic(&hoisted__Str_814, _va_Array_24);
                Str_delete(&hoisted__Str_814, (Bool){0});
            }
            U32 hoisted__U32_819 = 1;
            (void)hoisted__U32_819;
            U32 hoisted__U32_820 = U32_add(_fi_USize_807, hoisted__U32_819);
            (void)hoisted__U32_820;
            _fi_USize_807 = hoisted__U32_820;
            U32 hoisted__U32_821 = Str_len(s);
            (void)hoisted__U32_821;
            U32 hoisted__U32_822 = U32_add(total, hoisted__U32_821);
            (void)hoisted__U32_822;
            total = hoisted__U32_822;
        }
        OutOfBounds_delete(_forin_OutOfBounds_807, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array *_fc_Array_823 = parts;
        (void)_fc_Array_823;
        (void)_fc_Array_823;
        U32 _fi_USize_823 = 0;
        (void)_fi_USize_823;
        I64 _forin_err_kind_823 = 0;
        (void)_forin_err_kind_823;
        OutOfBounds *_forin_OutOfBounds_823 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_823->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_823;
        while (1) {
            U32 hoisted__U32_831 = Array_len(_fc_Array_823);
            (void)hoisted__U32_831;
            Bool _wcond_Bool_824 = U32_lt(_fi_USize_823, hoisted__U32_831);
            (void)_wcond_Bool_824;
            if (_wcond_Bool_824) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_823, &_fi_USize_823, &_forin_err_kind_823, _forin_OutOfBounds_823);
            I64 hoisted__I64_832 = 0;
            (void)hoisted__I64_832;
            Bool hoisted__Bool_833 = I64_eq(_forin_err_kind_823, hoisted__I64_832);
            (void)hoisted__Bool_833;
            Bool hoisted__Bool_834 = not(hoisted__Bool_833);
            (void)hoisted__Bool_834;
            if (hoisted__Bool_834) {
                Type *hoisted__Type_826 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_826;
                U32 hoisted__U32_827 = 1;
                (void)hoisted__U32_827;
                Array *_va_Array_25 = Array_new(hoisted__Type_826, hoisted__U32_827);
                (void)_va_Array_25;
                Type_delete(hoisted__Type_826, 1);
                U32 hoisted__U32_828 = 0;
                (void)hoisted__U32_828;
                Str hoisted__Str_829 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_829;
                Array_set(_va_Array_25, hoisted__U32_828, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_829; _oa; }));
                Str hoisted__Str_830 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_830;
                panic(&hoisted__Str_830, _va_Array_25);
                Str_delete(&hoisted__Str_830, (Bool){0});
            }
            U32 hoisted__U32_835 = 1;
            (void)hoisted__U32_835;
            U32 hoisted__U32_836 = U32_add(_fi_USize_823, hoisted__U32_835);
            (void)hoisted__U32_836;
            _fi_USize_823 = hoisted__U32_836;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_823, 1);
    }
    Array_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_843 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_843;
    if (hoisted__Bool_843) {
        Type *hoisted__Type_838 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_838;
        U32 hoisted__U32_839 = 1;
        (void)hoisted__U32_839;
        Array *_va_Array_26 = Array_new(hoisted__Type_838, hoisted__U32_839);
        (void)_va_Array_26;
        Type_delete(hoisted__Type_838, 1);
        U32 hoisted__U32_840 = 0;
        (void)hoisted__U32_840;
        Str hoisted__Str_841 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_841;
        Array_set(_va_Array_26, hoisted__U32_840, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_841; _oa; }));
        Str hoisted__Str_842 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_842;
        panic(&hoisted__Str_842, _va_Array_26);
        Str_delete(&hoisted__Str_842, (Bool){0});
    }
    void *hoisted__v_844 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_844;
    (void)hoisted__v_844;
    return hoisted__v_844;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_854 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_854;
    if (hoisted__Bool_854) {
        min_len = b->count;
    }
    {
        U32 _re_U32_846 = U32_clone(&min_len);
        (void)_re_U32_846;
        U32 _rc_U32_846 = 0;
        (void)_rc_U32_846;
        Bool hoisted__Bool_853 = U32_lte(_rc_U32_846, _re_U32_846);
        (void)hoisted__Bool_853;
        if (hoisted__Bool_853) {
            while (1) {
                Bool _wcond_Bool_847 = U32_lt(_rc_U32_846, _re_U32_846);
                (void)_wcond_Bool_847;
                if (_wcond_Bool_847) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_846);
                U32_inc(&_rc_U32_846);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_848 = 0;
                (void)hoisted__I64_848;
                Bool hoisted__Bool_849 = I64_neq(c, hoisted__I64_848);
                (void)hoisted__Bool_849;
                if (hoisted__Bool_849) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_850 = U32_gt(_rc_U32_846, _re_U32_846);
                (void)_wcond_Bool_850;
                if (_wcond_Bool_850) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_846);
                U32_dec(&_rc_U32_846);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_851 = 0;
                (void)hoisted__I64_851;
                Bool hoisted__Bool_852 = I64_neq(c, hoisted__I64_851);
                (void)hoisted__Bool_852;
                if (hoisted__Bool_852) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_855 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_855;
    return hoisted__I64_855;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_857 = 1;
    (void)hoisted__U32_857;
    U32 hoisted__U64_858 = U32_add(n, hoisted__U32_857);
    (void)hoisted__U64_858;
    void * buf = malloc(hoisted__U64_858);
    I32 hoisted__I32_859 = 0;
    (void)hoisted__I32_859;
    U64 hoisted__U64_860 = 1ULL;
    (void)hoisted__U64_860;
    memset(buf, hoisted__I32_859, hoisted__U64_860);
    I64 hoisted__I64_861 = 0;
    (void)hoisted__I64_861;
    Str *hoisted__Str_862 = malloc(sizeof(Str));
    hoisted__Str_862->c_str = buf;
    hoisted__Str_862->count = hoisted__I64_861;
    hoisted__Str_862->cap = n;
    (void)hoisted__Str_862;
    return hoisted__Str_862;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_877 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_877;
    if (hoisted__Bool_877) {
        Type *hoisted__Type_866 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_866;
        U32 hoisted__U32_867 = 1;
        (void)hoisted__U32_867;
        Array *_va_Array_27 = Array_new(hoisted__Type_866, hoisted__U32_867);
        (void)_va_Array_27;
        Type_delete(hoisted__Type_866, 1);
        U32 hoisted__U32_868 = 0;
        (void)hoisted__U32_868;
        Str hoisted__Str_869 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_869;
        Array_set(_va_Array_27, hoisted__U32_868, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_869; _oa; }));
        Str hoisted__Str_870 = (Str){.c_str = (void *)"./src/core/str.til:91:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_870;
        panic(&hoisted__Str_870, _va_Array_27);
        Str_delete(&hoisted__Str_870, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_878 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_878;
    if (hoisted__Bool_878) {
        Type *hoisted__Type_872 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_872;
        U32 hoisted__U32_873 = 1;
        (void)hoisted__U32_873;
        Array *_va_Array_28 = Array_new(hoisted__Type_872, hoisted__U32_873);
        (void)_va_Array_28;
        Type_delete(hoisted__Type_872, 1);
        U32 hoisted__U32_874 = 0;
        (void)hoisted__U32_874;
        Str hoisted__Str_875 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_875;
        Array_set(_va_Array_28, hoisted__U32_874, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_875; _oa; }));
        Str hoisted__Str_876 = (Str){.c_str = (void *)"./src/core/str.til:95:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_876;
        panic(&hoisted__Str_876, _va_Array_28);
        Str_delete(&hoisted__Str_876, (Bool){0});
    }
    void *hoisted__v_879 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_879;
    (void)hoisted__v_879;
    memcpy(hoisted__v_879, s->c_str, s->count);
    U32 hoisted__U32_880 = U32_clone(&new_len);
    (void)hoisted__U32_880;
    self->count = hoisted__U32_880;
    void *hoisted__v_881 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_881;
    (void)hoisted__v_881;
    I32 hoisted__I32_882 = 0;
    (void)hoisted__I32_882;
    U64 hoisted__U64_883 = 1ULL;
    (void)hoisted__U64_883;
    memset(hoisted__v_881, hoisted__I32_882, hoisted__U64_883);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_884 = 1;
    (void)hoisted__U32_884;
    U32 hoisted__U64_885 = U32_add(val->count, hoisted__U32_884);
    (void)hoisted__U64_885;
    void * new_data = malloc(hoisted__U64_885);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_886 = ptr_add(new_data, val->count);
    (void)hoisted__v_886;
    (void)hoisted__v_886;
    I32 hoisted__I32_887 = 0;
    (void)hoisted__I32_887;
    U64 hoisted__U64_888 = 1ULL;
    (void)hoisted__U64_888;
    memset(hoisted__v_886, hoisted__I32_887, hoisted__U64_888);
    Str *hoisted__Str_889 = malloc(sizeof(Str));
    hoisted__Str_889->c_str = new_data;
    hoisted__Str_889->count = val->count;
    hoisted__Str_889->cap = val->count;
    (void)hoisted__Str_889;
    return hoisted__Str_889;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_890 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_890;
    if (hoisted__Bool_890) {
        free(self->c_str);
    }
    if (call_free) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_1003 = 0;
    (void)hoisted__U32_1003;
    Bool hoisted__Bool_1004 = U32_eq(self->count, hoisted__U32_1003);
    (void)hoisted__Bool_1004;
    return hoisted__Bool_1004;
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_1097 = ((U64 (*)(I8 *, U32))(void *)hasher)(self->c_str, self->count);
    (void)hoisted__U64_1097;
    return hoisted__U64_1097;
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
    OutOfBounds *hoisted__OutOfBounds_1295 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1295->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1295;
    return hoisted__OutOfBounds_1295;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1296 = 0;
    (void)hoisted__Bool_1296;
    Str_delete(&self->msg, hoisted__Bool_1296);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1297 = 0;
    (void)hoisted__U32_1297;
    U64 hoisted__U64_1298 = ((U64 (*)(OutOfBounds *, U32))(void *)hasher)(self, hoisted__U32_1297);
    (void)hoisted__U64_1298;
    return hoisted__U64_1298;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1299 = 16;
    (void)hoisted__U32_1299;
    return hoisted__U32_1299;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1307 = 8;
    (void)hoisted__U32_1307;
    return hoisted__U32_1307;
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1512 = 0;
    (void)hoisted__I64_1512;
    Bool hoisted__Bool_1513 = I64_eq(val, hoisted__I64_1512);
    (void)hoisted__Bool_1513;
    if (hoisted__Bool_1513) {
        U64 hoisted__U64_1476 = 2ULL;
        (void)hoisted__U64_1476;
        void * buf = malloc(hoisted__U64_1476);
        I64 hoisted__I64_1477 = 48;
        (void)hoisted__I64_1477;
        U64 hoisted__U64_1478 = 1ULL;
        (void)hoisted__U64_1478;
        memcpy(buf, &hoisted__I64_1477, hoisted__U64_1478);
        U64 hoisted__U64_1479 = 1ULL;
        (void)hoisted__U64_1479;
        void *hoisted__v_1480 = ptr_add(buf, hoisted__U64_1479);
        (void)hoisted__v_1480;
        (void)hoisted__v_1480;
        I32 hoisted__I32_1481 = 0;
        (void)hoisted__I32_1481;
        U64 hoisted__U64_1482 = 1ULL;
        (void)hoisted__U64_1482;
        memset(hoisted__v_1480, hoisted__I32_1481, hoisted__U64_1482);
        I64 hoisted__I64_1483 = 1;
        (void)hoisted__I64_1483;
        I64 hoisted__I64_1484 = 1;
        (void)hoisted__I64_1484;
        Str *hoisted__Str_1485 = malloc(sizeof(Str));
        hoisted__Str_1485->c_str = buf;
        hoisted__Str_1485->count = hoisted__I64_1483;
        hoisted__Str_1485->cap = hoisted__I64_1484;
        (void)hoisted__Str_1485;
        { Str * _ret_val = hoisted__Str_1485;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1514 = 0;
    (void)hoisted__I64_1514;
    Bool hoisted__Bool_1515 = I64_lt(val, hoisted__I64_1514);
    (void)hoisted__Bool_1515;
    if (hoisted__Bool_1515) {
        Bool hoisted__Bool_1486 = 1;
        (void)hoisted__Bool_1486;
        is_neg = hoisted__Bool_1486;
        I64 hoisted__I64_1487 = 0;
        (void)hoisted__I64_1487;
        I64 hoisted__I64_1488 = I64_sub(hoisted__I64_1487, val);
        (void)hoisted__I64_1488;
        v = hoisted__I64_1488;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1490 = 0;
        (void)hoisted__I64_1490;
        Bool _wcond_Bool_1489 = I64_gt(tmp, hoisted__I64_1490);
        (void)_wcond_Bool_1489;
        if (_wcond_Bool_1489) {
        } else {
            break;
        }
        U64 hoisted__U64_1491 = 1ULL;
        (void)hoisted__U64_1491;
        U64 hoisted__U64_1492 = U64_add(ndigits, hoisted__U64_1491);
        (void)hoisted__U64_1492;
        ndigits = hoisted__U64_1492;
        I64 hoisted__I64_1493 = 10;
        (void)hoisted__I64_1493;
        I64 hoisted__I64_1494 = I64_div(tmp, hoisted__I64_1493);
        (void)hoisted__I64_1494;
        tmp = hoisted__I64_1494;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1495 = 1ULL;
        (void)hoisted__U64_1495;
        U64 hoisted__U64_1496 = U64_add(total, hoisted__U64_1495);
        (void)hoisted__U64_1496;
        total = hoisted__U64_1496;
    }
    U64 hoisted__U64_1516 = 1ULL;
    (void)hoisted__U64_1516;
    U64 hoisted__U64_1517 = U64_add(total, hoisted__U64_1516);
    (void)hoisted__U64_1517;
    void * buf = malloc(hoisted__U64_1517);
    if (is_neg) {
        I64 hoisted__I64_1497 = 45;
        (void)hoisted__I64_1497;
        U64 hoisted__U64_1498 = 1ULL;
        (void)hoisted__U64_1498;
        memcpy(buf, &hoisted__I64_1497, hoisted__U64_1498);
    }
    U64 hoisted__U64_1518 = 1ULL;
    (void)hoisted__U64_1518;
    U64 i = U64_sub(total, hoisted__U64_1518);
    while (1) {
        I64 hoisted__I64_1500 = 0;
        (void)hoisted__I64_1500;
        Bool _wcond_Bool_1499 = I64_gt(v, hoisted__I64_1500);
        (void)_wcond_Bool_1499;
        if (_wcond_Bool_1499) {
        } else {
            break;
        }
        I64 hoisted__I64_1501 = 10;
        (void)hoisted__I64_1501;
        I64 hoisted__I64_1502 = I64_mod(v, hoisted__I64_1501);
        (void)hoisted__I64_1502;
        I64 hoisted__I64_1503 = 48;
        (void)hoisted__I64_1503;
        I64 hoisted__I64_1504 = I64_add(hoisted__I64_1502, hoisted__I64_1503);
        (void)hoisted__I64_1504;
        void *hoisted__v_1505 = ptr_add(buf, i);
        (void)hoisted__v_1505;
        (void)hoisted__v_1505;
        U8 hoisted__U8_1506 = I64_to_u8(hoisted__I64_1504);
        (void)hoisted__U8_1506;
        U64 hoisted__U64_1507 = 1ULL;
        (void)hoisted__U64_1507;
        memcpy(hoisted__v_1505, &hoisted__U8_1506, hoisted__U64_1507);
        I64 hoisted__I64_1508 = 10;
        (void)hoisted__I64_1508;
        I64 hoisted__I64_1509 = I64_div(v, hoisted__I64_1508);
        (void)hoisted__I64_1509;
        v = hoisted__I64_1509;
        U64 hoisted__U64_1510 = 1ULL;
        (void)hoisted__U64_1510;
        U64 hoisted__U64_1511 = U64_sub(i, hoisted__U64_1510);
        (void)hoisted__U64_1511;
        i = hoisted__U64_1511;
    }
    void *hoisted__v_1519 = ptr_add(buf, total);
    (void)hoisted__v_1519;
    (void)hoisted__v_1519;
    I32 hoisted__I32_1520 = 0;
    (void)hoisted__I32_1520;
    U64 hoisted__U64_1521 = 1ULL;
    (void)hoisted__U64_1521;
    memset(hoisted__v_1519, hoisted__I32_1520, hoisted__U64_1521);
    Str *hoisted__Str_1522 = malloc(sizeof(Str));
    hoisted__Str_1522->c_str = buf;
    hoisted__Str_1522->count = total;
    hoisted__Str_1522->cap = total;
    (void)hoisted__Str_1522;
    return hoisted__Str_1522;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1542 = 8;
    (void)hoisted__U32_1542;
    return hoisted__U32_1542;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1673 = 0;
    (void)hoisted__U32_1673;
    U64 hoisted__U64_1674 = ((U64 (*)(I64 *, U32))(void *)hasher)(&self, hoisted__U32_1673);
    (void)hoisted__U64_1674;
    return hoisted__U64_1674;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1677 = I64_cmp(a, b);
    (void)hoisted__I64_1677;
    I64 hoisted__I64_1678 = -1;
    (void)hoisted__I64_1678;
    Bool hoisted__Bool_1679 = I64_eq(hoisted__I64_1677, hoisted__I64_1678);
    (void)hoisted__Bool_1679;
    return hoisted__Bool_1679;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1680 = I64_cmp(a, b);
    (void)hoisted__I64_1680;
    I64 hoisted__I64_1681 = 1;
    (void)hoisted__I64_1681;
    Bool hoisted__Bool_1682 = I64_eq(hoisted__I64_1680, hoisted__I64_1681);
    (void)hoisted__Bool_1682;
    return hoisted__Bool_1682;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1683 = I64_eq(a, b);
    (void)hoisted__Bool_1683;
    Bool hoisted__Bool_1684 = not(hoisted__Bool_1683);
    (void)hoisted__Bool_1684;
    return hoisted__Bool_1684;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1702 = Bool_eq(a, b);
    (void)hoisted__Bool_1702;
    if (hoisted__Bool_1702) {
        I64 hoisted__I64_1700 = 0;
        (void)hoisted__I64_1700;
        { I64 _ret_val = hoisted__I64_1700;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1701 = -1;
        (void)hoisted__I64_1701;
        return hoisted__I64_1701;
    }
    I64 hoisted__I64_1703 = 1;
    (void)hoisted__I64_1703;
    return hoisted__I64_1703;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1704 = 1;
    (void)hoisted__U32_1704;
    return hoisted__U32_1704;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1705 = 0;
    (void)hoisted__U32_1705;
    U64 hoisted__U64_1706 = ((U64 (*)(Bool *, U32))(void *)hasher)(&self, hoisted__U32_1705);
    (void)hoisted__U64_1706;
    return hoisted__U64_1706;
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
Primitive *Primitive_I8() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I8 };
    return r;
}
Primitive *Primitive_U8() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_U8 };
    return r;
}
Primitive *Primitive_U32() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_U32 };
    return r;
}
Primitive *Primitive_I32() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I32 };
    return r;
}
Primitive *Primitive_U64() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_U64 };
    return r;
}
Primitive *Primitive_I64() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I64 };
    return r;
}
Primitive *Primitive_F32() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_F32 };
    return r;
}
Primitive *Primitive_Bool() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_Bool };
    return r;
}
Bool Primitive_eq(Primitive * self, Primitive * other) {
    Bool hoisted__Bool_1860 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1860;
    if (hoisted__Bool_1860) {
        Bool hoisted__Bool_1850 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1850;
        { Bool _ret_val = hoisted__Bool_1850;
                return _ret_val; }
    }
    Bool hoisted__Bool_1861 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1861;
    if (hoisted__Bool_1861) {
        Bool hoisted__Bool_1851 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1851;
        { Bool _ret_val = hoisted__Bool_1851;
                return _ret_val; }
    }
    Bool hoisted__Bool_1862 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1862;
    if (hoisted__Bool_1862) {
        Bool hoisted__Bool_1852 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_1852;
        { Bool _ret_val = hoisted__Bool_1852;
                return _ret_val; }
    }
    Bool hoisted__Bool_1863 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1863;
    if (hoisted__Bool_1863) {
        Bool hoisted__Bool_1853 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_1853;
        { Bool _ret_val = hoisted__Bool_1853;
                return _ret_val; }
    }
    Bool hoisted__Bool_1864 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1864;
    if (hoisted__Bool_1864) {
        Bool hoisted__Bool_1854 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_1854;
        { Bool _ret_val = hoisted__Bool_1854;
                return _ret_val; }
    }
    Bool hoisted__Bool_1865 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1865;
    if (hoisted__Bool_1865) {
        Bool hoisted__Bool_1855 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_1855;
        { Bool _ret_val = hoisted__Bool_1855;
                return _ret_val; }
    }
    Bool hoisted__Bool_1866 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1866;
    if (hoisted__Bool_1866) {
        Bool hoisted__Bool_1856 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_1856;
        { Bool _ret_val = hoisted__Bool_1856;
                return _ret_val; }
    }
    Bool hoisted__Bool_1867 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1867;
    if (hoisted__Bool_1867) {
        Bool hoisted__Bool_1857 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_1857;
        { Bool _ret_val = hoisted__Bool_1857;
                return _ret_val; }
    }
    Bool hoisted__Bool_1868 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1868;
    if (hoisted__Bool_1868) {
        Bool hoisted__Bool_1858 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_1858;
        { Bool _ret_val = hoisted__Bool_1858;
                return _ret_val; }
    }
    Bool hoisted__Bool_1869 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1869;
    if (hoisted__Bool_1869) {
        Bool hoisted__Bool_1859 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_1859;
        { Bool _ret_val = hoisted__Bool_1859;
                return _ret_val; }
    }
    Bool hoisted__Bool_1870 = 0;
    (void)hoisted__Bool_1870;
    return hoisted__Bool_1870;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1892 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1892;
    if (hoisted__Bool_1892) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1893 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1893;
    if (hoisted__Bool_1893) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_1894 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1894;
    if (hoisted__Bool_1894) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_1895 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1895;
    if (hoisted__Bool_1895) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1896 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1896;
    if (hoisted__Bool_1896) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1897 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1897;
    if (hoisted__Bool_1897) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1898 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1898;
    if (hoisted__Bool_1898) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1899 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1899;
    if (hoisted__Bool_1899) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1900 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1900;
    if (hoisted__Bool_1900) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1901 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1901;
    if (hoisted__Bool_1901) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_1902 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1902;
    UNREACHABLE(&hoisted__Str_1902);
    Str_delete(&hoisted__Str_1902, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1903 = 4;
    (void)hoisted__U32_1903;
    return hoisted__U32_1903;
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
Type *Type_Primitive(Primitive * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Primitive;
    r->data.Primitive = *val;
    free(val);
    return r;
}
void Type_delete(Type * self, Bool call_free) {
    Bool hoisted__Bool_1949 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1949;
    if (hoisted__Bool_1949) {
        Str *hoisted__Str_1941 = get_payload(self);
        (void)hoisted__Str_1941;
        (void)hoisted__Str_1941;
        Bool hoisted__Bool_1942 = 0;
        (void)hoisted__Bool_1942;
        Str_delete(hoisted__Str_1941, hoisted__Bool_1942);
    }
    Bool hoisted__Bool_1950 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1950;
    if (hoisted__Bool_1950) {
        Str *hoisted__Str_1943 = get_payload(self);
        (void)hoisted__Str_1943;
        (void)hoisted__Str_1943;
        Bool hoisted__Bool_1944 = 0;
        (void)hoisted__Bool_1944;
        Str_delete(hoisted__Str_1943, hoisted__Bool_1944);
    }
    Bool hoisted__Bool_1951 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1951;
    if (hoisted__Bool_1951) {
        Str *hoisted__Str_1945 = get_payload(self);
        (void)hoisted__Str_1945;
        (void)hoisted__Str_1945;
        Bool hoisted__Bool_1946 = 0;
        (void)hoisted__Bool_1946;
        Str_delete(hoisted__Str_1945, hoisted__Bool_1946);
    }
    Bool hoisted__Bool_1952 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1952;
    if (hoisted__Bool_1952) {
        Primitive *hoisted__Primitive_1947 = get_payload(self);
        (void)hoisted__Primitive_1947;
        (void)hoisted__Primitive_1947;
        Bool hoisted__Bool_1948 = 0;
        (void)hoisted__Bool_1948;
        Primitive_delete(hoisted__Primitive_1947, hoisted__Bool_1948);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2018 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2018;
    if (hoisted__Bool_2018) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2019 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2019;
    if (hoisted__Bool_2019) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2020 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2020;
    if (hoisted__Bool_2020) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2012 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2012;
        Type *hoisted__Type_2013 = Type_Struct(hoisted__Str_2012);
        (void)hoisted__Type_2013;
        { Type * _ret_val = hoisted__Type_2013;
                return _ret_val; }
    }
    Bool hoisted__Bool_2021 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2021;
    if (hoisted__Bool_2021) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2022 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2022;
    if (hoisted__Bool_2022) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2014 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2014;
        Type *hoisted__Type_2015 = Type_Enum(hoisted__Str_2014);
        (void)hoisted__Type_2015;
        { Type * _ret_val = hoisted__Type_2015;
                return _ret_val; }
    }
    Bool hoisted__Bool_2023 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2023;
    if (hoisted__Bool_2023) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2024 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2024;
    if (hoisted__Bool_2024) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2025 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2025;
    if (hoisted__Bool_2025) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2026 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2026;
    if (hoisted__Bool_2026) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2027 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2027;
    if (hoisted__Bool_2027) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2016 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2016;
        Type *hoisted__Type_2017 = Type_Custom(hoisted__Str_2016);
        (void)hoisted__Type_2017;
        { Type * _ret_val = hoisted__Type_2017;
                return _ret_val; }
    }
    Primitive *_clone_payload_Primitive_10 = get_payload(self);
    (void)_clone_payload_Primitive_10;
    (void)_clone_payload_Primitive_10;
    Primitive hoisted__Primitive_2028 = DEREF(_clone_payload_Primitive_10);
    (void)hoisted__Primitive_2028;
    Type *hoisted__Type_2029 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2028; _oa; }));
    (void)hoisted__Type_2029;
    return hoisted__Type_2029;
}

U32 Type_size(void) {
    U32 hoisted__U32_2030 = 24;
    (void)hoisted__U32_2030;
    return hoisted__U32_2030;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3727 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3727;
    if (hoisted__Bool_3727) {
        Type *hoisted__Type_3722 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3722;
        U32 hoisted__U32_3723 = 1;
        (void)hoisted__U32_3723;
        Array *_va_Array_110 = Array_new(hoisted__Type_3722, hoisted__U32_3723);
        (void)_va_Array_110;
        Type_delete(hoisted__Type_3722, 1);
        U32 hoisted__U32_3724 = 0;
        (void)hoisted__U32_3724;
        Str hoisted__Str_3725 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3725;
        Array_set(_va_Array_110, hoisted__U32_3724, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3725; _oa; }));
        Str hoisted__Str_3726 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3726;
        panic(&hoisted__Str_3726, _va_Array_110);
        Str_delete(&hoisted__Str_3726, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3728 = calloc(cap, elem_size);
    (void)hoisted__v_3728;
    void * hoisted__v_3729 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3729;
    void * hoisted__v_3730 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3730;
    Array *hoisted__Array_3731 = malloc(sizeof(Array));
    hoisted__Array_3731->data = hoisted__v_3728;
    hoisted__Array_3731->cap = cap;
    hoisted__Array_3731->elem_size = elem_size;
    hoisted__Array_3731->elem_clone = hoisted__v_3729;
    hoisted__Array_3731->elem_delete = hoisted__v_3730;
    (void)hoisted__Array_3731;
    return hoisted__Array_3731;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3732 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3732;
    Str_delete(elem_type, 1);
    return hoisted__Array_3732;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3753 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3753;
    if (hoisted__Bool_3753) {
        Type *hoisted__Type_3734 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3734;
        U32 hoisted__U32_3735 = 6;
        (void)hoisted__U32_3735;
        Array *_va_Array_111 = Array_new(hoisted__Type_3734, hoisted__U32_3735);
        (void)_va_Array_111;
        Type_delete(hoisted__Type_3734, 1);
        U32 hoisted__U32_3736 = 0;
        (void)hoisted__U32_3736;
        Str hoisted__Str_3737 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3737;
        Array_set(_va_Array_111, hoisted__U32_3736, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3737; _oa; }));
        U32 hoisted__U32_3738 = 1;
        (void)hoisted__U32_3738;
        Str hoisted__Str_3739 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3739;
        Array_set(_va_Array_111, hoisted__U32_3738, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3739; _oa; }));
        U32 hoisted__U32_3740 = 2;
        (void)hoisted__U32_3740;
        Str *hoisted__Str_3741 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3741;
        Array_set(_va_Array_111, hoisted__U32_3740, hoisted__Str_3741);
        U32 hoisted__U32_3742 = 3;
        (void)hoisted__U32_3742;
        Str hoisted__Str_3743 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3743;
        Array_set(_va_Array_111, hoisted__U32_3742, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3743; _oa; }));
        U32 hoisted__U32_3744 = 4;
        (void)hoisted__U32_3744;
        Str *hoisted__Str_3745 = U32_to_str(self->cap);
        (void)hoisted__Str_3745;
        Array_set(_va_Array_111, hoisted__U32_3744, hoisted__Str_3745);
        U32 hoisted__U32_3746 = 5;
        (void)hoisted__U32_3746;
        Str hoisted__Str_3747 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3747;
        Array_set(_va_Array_111, hoisted__U32_3746, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3747; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3748 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_111); hoisted__OutOfBounds_3748->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3748;
        U32 hoisted__U32_3749 = 16;
        (void)hoisted__U32_3749;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3748, hoisted__U32_3749);
        OutOfBounds_delete(hoisted__OutOfBounds_3748, 1);
        I64 hoisted__I64_3750 = 3;
        (void)hoisted__I64_3750;
        *_err_kind = hoisted__I64_3750;
    }
    I64 hoisted__I64_3754 = 0;
    (void)hoisted__I64_3754;
    Bool hoisted__Bool_3755 = I64_eq(DEREF(_err_kind), hoisted__I64_3754);
    (void)hoisted__Bool_3755;
    if (hoisted__Bool_3755) {
        U32 hoisted__U64_3751 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3751;
        void *hoisted__v_3752 = ptr_add(self->data, hoisted__U64_3751);
        (void)hoisted__v_3752;
        (void)hoisted__v_3752;
        { void * _ret_val = hoisted__v_3752;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3770 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3770;
    if (hoisted__Bool_3770) {
        Type *hoisted__Type_3757 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3757;
        U32 hoisted__U32_3758 = 5;
        (void)hoisted__U32_3758;
        Array *_va_Array_112 = Array_new(hoisted__Type_3757, hoisted__U32_3758);
        (void)_va_Array_112;
        Type_delete(hoisted__Type_3757, 1);
        U32 hoisted__U32_3759 = 0;
        (void)hoisted__U32_3759;
        Str hoisted__Str_3760 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3760;
        Array_set(_va_Array_112, hoisted__U32_3759, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3760; _oa; }));
        U32 hoisted__U32_3761 = 1;
        (void)hoisted__U32_3761;
        Str *hoisted__Str_3762 = U32_to_str(i);
        (void)hoisted__Str_3762;
        Array_set(_va_Array_112, hoisted__U32_3761, hoisted__Str_3762);
        U32 hoisted__U32_3763 = 2;
        (void)hoisted__U32_3763;
        Str hoisted__Str_3764 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3764;
        Array_set(_va_Array_112, hoisted__U32_3763, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3764; _oa; }));
        U32 hoisted__U32_3765 = 3;
        (void)hoisted__U32_3765;
        Str *hoisted__Str_3766 = U32_to_str(self->cap);
        (void)hoisted__Str_3766;
        Array_set(_va_Array_112, hoisted__U32_3765, hoisted__Str_3766);
        U32 hoisted__U32_3767 = 4;
        (void)hoisted__U32_3767;
        Str hoisted__Str_3768 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3768;
        Array_set(_va_Array_112, hoisted__U32_3767, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3768; _oa; }));
        Str hoisted__Str_3769 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3769;
        panic(&hoisted__Str_3769, _va_Array_112);
        Str_delete(&hoisted__Str_3769, (Bool){0});
    }
    U32 hoisted__U64_3771 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3771;
    void *hoisted__v_3772 = ptr_add(self->data, hoisted__U64_3771);
    (void)hoisted__v_3772;
    (void)hoisted__v_3772;
    Bool hoisted__Bool_3773 = 0;
    (void)hoisted__Bool_3773;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3772, hoisted__Bool_3773);
    U32 hoisted__U64_3774 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3774;
    void *hoisted__v_3775 = ptr_add(self->data, hoisted__U64_3774);
    (void)hoisted__v_3775;
    (void)hoisted__v_3775;
    memcpy(hoisted__v_3775, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3776 = self->cap;
        (void)_re_U32_3776;
        U32 _rc_U32_3776 = 0;
        (void)_rc_U32_3776;
        Bool hoisted__Bool_3785 = U32_lte(_rc_U32_3776, _re_U32_3776);
        (void)hoisted__Bool_3785;
        if (hoisted__Bool_3785) {
            while (1) {
                Bool _wcond_Bool_3777 = U32_lt(_rc_U32_3776, _re_U32_3776);
                (void)_wcond_Bool_3777;
                if (_wcond_Bool_3777) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3776);
                U32_inc(&_rc_U32_3776);
                U32 hoisted__U64_3778 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3778;
                void *hoisted__v_3779 = ptr_add(self->data, hoisted__U64_3778);
                (void)hoisted__v_3779;
                (void)hoisted__v_3779;
                Bool hoisted__Bool_3780 = 0;
                (void)hoisted__Bool_3780;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3779, hoisted__Bool_3780);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3781 = U32_gt(_rc_U32_3776, _re_U32_3776);
                (void)_wcond_Bool_3781;
                if (_wcond_Bool_3781) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3776);
                U32_dec(&_rc_U32_3776);
                U32 hoisted__U64_3782 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3782;
                void *hoisted__v_3783 = ptr_add(self->data, hoisted__U64_3782);
                (void)hoisted__v_3783;
                (void)hoisted__v_3783;
                Bool hoisted__Bool_3784 = 0;
                (void)hoisted__Bool_3784;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3783, hoisted__Bool_3784);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3798 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3798;
    void * new_data = malloc(hoisted__U64_3798);
    {
        U32 _re_U32_3786 = self->cap;
        (void)_re_U32_3786;
        U32 _rc_U32_3786 = 0;
        (void)_rc_U32_3786;
        Bool hoisted__Bool_3797 = U32_lte(_rc_U32_3786, _re_U32_3786);
        (void)hoisted__Bool_3797;
        if (hoisted__Bool_3797) {
            while (1) {
                Bool _wcond_Bool_3787 = U32_lt(_rc_U32_3786, _re_U32_3786);
                (void)_wcond_Bool_3787;
                if (_wcond_Bool_3787) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3786);
                U32_inc(&_rc_U32_3786);
                U32 hoisted__U64_3788 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3788;
                void *hoisted__v_3789 = ptr_add(self->data, hoisted__U64_3788);
                (void)hoisted__v_3789;
                (void)hoisted__v_3789;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3789);
                U32 hoisted__U64_3790 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3790;
                void *hoisted__v_3791 = ptr_add(new_data, hoisted__U64_3790);
                (void)hoisted__v_3791;
                (void)hoisted__v_3791;
                memcpy(hoisted__v_3791, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3792 = U32_gt(_rc_U32_3786, _re_U32_3786);
                (void)_wcond_Bool_3792;
                if (_wcond_Bool_3792) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3786);
                U32_dec(&_rc_U32_3786);
                U32 hoisted__U64_3793 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3793;
                void *hoisted__v_3794 = ptr_add(self->data, hoisted__U64_3793);
                (void)hoisted__v_3794;
                (void)hoisted__v_3794;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3794);
                U32 hoisted__U64_3795 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3795;
                void *hoisted__v_3796 = ptr_add(new_data, hoisted__U64_3795);
                (void)hoisted__v_3796;
                (void)hoisted__v_3796;
                memcpy(hoisted__v_3796, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3799 = malloc(sizeof(Array));
    hoisted__Array_3799->data = new_data;
    hoisted__Array_3799->cap = self->cap;
    hoisted__Array_3799->elem_size = self->elem_size;
    hoisted__Array_3799->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3799->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3799;
    return hoisted__Array_3799;
}

U32 Array_size(void) {
    U32 hoisted__U32_3800 = 32;
    (void)hoisted__U32_3800;
    return hoisted__U32_3800;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4174 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4174;
    U32 hoisted__U32_4175 = 3;
    (void)hoisted__U32_4175;
    Array *_va_Array_144 = Array_new(hoisted__Type_4174, hoisted__U32_4175);
    (void)_va_Array_144;
    Type_delete(hoisted__Type_4174, 1);
    U32 hoisted__U32_4176 = 0;
    (void)hoisted__U32_4176;
    Str *hoisted__Str_4177 = Str_clone(loc_str);
    (void)hoisted__Str_4177;
    Array_set(_va_Array_144, hoisted__U32_4176, hoisted__Str_4177);
    U32 hoisted__U32_4178 = 1;
    (void)hoisted__U32_4178;
    Str hoisted__Str_4179 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4179;
    Array_set(_va_Array_144, hoisted__U32_4178, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4179; _oa; }));
    Array *hoisted__Array_4180 = Array_clone(parts);
    (void)hoisted__Array_4180;
    Array_delete(parts, 1);
    U32 hoisted__U32_4181 = 2;
    (void)hoisted__U32_4181;
    Str *hoisted__Str_4182 = format(hoisted__Array_4180);
    (void)hoisted__Str_4182;
    Array_set(_va_Array_144, hoisted__U32_4181, hoisted__Str_4182);
    println(_va_Array_144);
    I64 hoisted__I64_4183 = 1;
    (void)hoisted__I64_4183;
    exit(hoisted__I64_4183);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4193 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4193;
    U32 hoisted__U32_4194 = 1;
    (void)hoisted__U32_4194;
    Array *_va_Array_146 = Array_new(hoisted__Type_4193, hoisted__U32_4194);
    (void)_va_Array_146;
    Type_delete(hoisted__Type_4193, 1);
    U32 hoisted__U32_4195 = 0;
    (void)hoisted__U32_4195;
    Str hoisted__Str_4196 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4196;
    Array_set(_va_Array_146, hoisted__U32_4195, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4196; _oa; }));
    panic(loc_str, _va_Array_146);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4202 = not(cond);
    (void)hoisted__Bool_4202;
    if (hoisted__Bool_4202) {
        Type *hoisted__Type_4198 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4198;
        U32 hoisted__U32_4199 = 1;
        (void)hoisted__U32_4199;
        Array *_va_Array_147 = Array_new(hoisted__Type_4198, hoisted__U32_4199);
        (void)_va_Array_147;
        Type_delete(hoisted__Type_4198, 1);
        U32 hoisted__U32_4200 = 0;
        (void)hoisted__U32_4200;
        Str hoisted__Str_4201 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4201;
        Array_set(_va_Array_147, hoisted__U32_4200, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4201; _oa; }));
        panic(loc_str, _va_Array_147);
    }
    Bool hoisted__Bool_4203 = 1;
    (void)hoisted__Bool_4203;
    return hoisted__Bool_4203;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4226 = I64_neq(a, b);
    (void)hoisted__Bool_4226;
    if (hoisted__Bool_4226) {
        Type *hoisted__Type_4214 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4214;
        U32 hoisted__U32_4215 = 5;
        (void)hoisted__U32_4215;
        Array *_va_Array_149 = Array_new(hoisted__Type_4214, hoisted__U32_4215);
        (void)_va_Array_149;
        Type_delete(hoisted__Type_4214, 1);
        U32 hoisted__U32_4216 = 0;
        (void)hoisted__U32_4216;
        Str hoisted__Str_4217 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4217;
        Array_set(_va_Array_149, hoisted__U32_4216, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4217; _oa; }));
        U32 hoisted__U32_4218 = 1;
        (void)hoisted__U32_4218;
        Str *hoisted__Str_4219 = I64_to_str(a);
        (void)hoisted__Str_4219;
        Array_set(_va_Array_149, hoisted__U32_4218, hoisted__Str_4219);
        U32 hoisted__U32_4220 = 2;
        (void)hoisted__U32_4220;
        Str hoisted__Str_4221 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4221;
        Array_set(_va_Array_149, hoisted__U32_4220, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4221; _oa; }));
        U32 hoisted__U32_4222 = 3;
        (void)hoisted__U32_4222;
        Str *hoisted__Str_4223 = I64_to_str(b);
        (void)hoisted__Str_4223;
        Array_set(_va_Array_149, hoisted__U32_4222, hoisted__Str_4223);
        U32 hoisted__U32_4224 = 4;
        (void)hoisted__U32_4224;
        Str hoisted__Str_4225 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4225;
        Array_set(_va_Array_149, hoisted__U32_4224, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4225; _oa; }));
        panic(loc_str, _va_Array_149);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4240 = Str_eq(a, b);
    (void)hoisted__Bool_4240;
    Bool hoisted__Bool_4241 = not(hoisted__Bool_4240);
    (void)hoisted__Bool_4241;
    if (hoisted__Bool_4241) {
        Type *hoisted__Type_4228 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4228;
        U32 hoisted__U32_4229 = 5;
        (void)hoisted__U32_4229;
        Array *_va_Array_150 = Array_new(hoisted__Type_4228, hoisted__U32_4229);
        (void)_va_Array_150;
        Type_delete(hoisted__Type_4228, 1);
        U32 hoisted__U32_4230 = 0;
        (void)hoisted__U32_4230;
        Str hoisted__Str_4231 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4231;
        Array_set(_va_Array_150, hoisted__U32_4230, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4231; _oa; }));
        U32 hoisted__U32_4232 = 1;
        (void)hoisted__U32_4232;
        Str *hoisted__Str_4233 = Str_clone(a);
        (void)hoisted__Str_4233;
        Array_set(_va_Array_150, hoisted__U32_4232, hoisted__Str_4233);
        U32 hoisted__U32_4234 = 2;
        (void)hoisted__U32_4234;
        Str hoisted__Str_4235 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4235;
        Array_set(_va_Array_150, hoisted__U32_4234, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4235; _oa; }));
        U32 hoisted__U32_4236 = 3;
        (void)hoisted__U32_4236;
        Str *hoisted__Str_4237 = Str_clone(b);
        (void)hoisted__Str_4237;
        Array_set(_va_Array_150, hoisted__U32_4236, hoisted__Str_4237);
        U32 hoisted__U32_4238 = 4;
        (void)hoisted__U32_4238;
        Str hoisted__Str_4239 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4239;
        Array_set(_va_Array_150, hoisted__U32_4238, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4239; _oa; }));
        panic(loc_str, _va_Array_150);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4242 = parts;
        (void)_fc_Array_4242;
        (void)_fc_Array_4242;
        U32 _fi_USize_4242 = 0;
        (void)_fi_USize_4242;
        I64 _forin_err_kind_4242 = 0;
        (void)_forin_err_kind_4242;
        OutOfBounds *_forin_OutOfBounds_4242 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4242->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4242;
        while (1) {
            U32 hoisted__U32_4250 = Array_len(_fc_Array_4242);
            (void)hoisted__U32_4250;
            Bool _wcond_Bool_4243 = U32_lt(_fi_USize_4242, hoisted__U32_4250);
            (void)_wcond_Bool_4243;
            if (_wcond_Bool_4243) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4242, &_fi_USize_4242, &_forin_err_kind_4242, _forin_OutOfBounds_4242);
            I64 hoisted__I64_4251 = 0;
            (void)hoisted__I64_4251;
            Bool hoisted__Bool_4252 = I64_eq(_forin_err_kind_4242, hoisted__I64_4251);
            (void)hoisted__Bool_4252;
            Bool hoisted__Bool_4253 = not(hoisted__Bool_4252);
            (void)hoisted__Bool_4253;
            if (hoisted__Bool_4253) {
                Type *hoisted__Type_4245 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4245;
                U32 hoisted__U32_4246 = 1;
                (void)hoisted__U32_4246;
                Array *_va_Array_151 = Array_new(hoisted__Type_4245, hoisted__U32_4246);
                (void)_va_Array_151;
                Type_delete(hoisted__Type_4245, 1);
                U32 hoisted__U32_4247 = 0;
                (void)hoisted__U32_4247;
                Str hoisted__Str_4248 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4248;
                Array_set(_va_Array_151, hoisted__U32_4247, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4248; _oa; }));
                Str hoisted__Str_4249 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4249;
                panic(&hoisted__Str_4249, _va_Array_151);
                Str_delete(&hoisted__Str_4249, (Bool){0});
            }
            U32 hoisted__U32_4254 = 1;
            (void)hoisted__U32_4254;
            U32 hoisted__U32_4255 = U32_add(_fi_USize_4242, hoisted__U32_4254);
            (void)hoisted__U32_4255;
            _fi_USize_4242 = hoisted__U32_4255;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4242, 1);
    }
    Array_delete(parts, 1);
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
    Str hoisted__Str_4512 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4512;
    I64 hoisted__I64_4513 = 3;
    (void)hoisted__I64_4513;
    assert_eq(&hoisted__Str_4512, result, hoisted__I64_4513);
    Str_delete(&hoisted__Str_4512, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4520 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4520;
    I64 hoisted__I64_4521 = 15;
    (void)hoisted__I64_4521;
    assert_eq(&hoisted__Str_4520, result, hoisted__I64_4521);
    Str_delete(&hoisted__Str_4520, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4528 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4528;
    I64 hoisted__I64_4529 = 26;
    (void)hoisted__I64_4529;
    assert_eq(&hoisted__Str_4528, result, hoisted__I64_4529);
    Str_delete(&hoisted__Str_4528, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4532 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4532;
    Str hoisted__Str_4533 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4533;
    assert_eq_str(&hoisted__Str_4532, &result, &hoisted__Str_4533);
    Str_delete(&hoisted__Str_4532, (Bool){0});
    Str_delete(&hoisted__Str_4533, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4864 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4864;
    assert_eq_str(&hoisted__Str_4864, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4864, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4865 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4865;
    assert_eq_str(&hoisted__Str_4865, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4865, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4867 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4867;
    I64 hoisted__I64_4868 = 8;
    (void)hoisted__I64_4868;
    assert_eq(&hoisted__Str_4867, result, hoisted__I64_4868);
    Str_delete(&hoisted__Str_4867, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4871 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4871;
    Bool hoisted__Bool_4872 = 1;
    (void)hoisted__Bool_4872;
    assert(&hoisted__Str_4871, hoisted__Bool_4872);
    Str_delete(&hoisted__Str_4871, (Bool){0});
    Str hoisted__Str_4875 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4875;
    Bool hoisted__Bool_4876 = 1;
    (void)hoisted__Bool_4876;
    assert(&hoisted__Str_4875, hoisted__Bool_4876);
    Str_delete(&hoisted__Str_4875, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4881 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4881;
    Str hoisted__Str_4882 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4882;
    Str hoisted__Str_4883 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4883;
    assert_eq_str(&hoisted__Str_4881, &hoisted__Str_4882, &hoisted__Str_4883);
    Str_delete(&hoisted__Str_4881, (Bool){0});
    Str_delete(&hoisted__Str_4882, (Bool){0});
    Str_delete(&hoisted__Str_4883, (Bool){0});
    Str hoisted__Str_4886 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4886;
    Str hoisted__Str_4887 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4887;
    Str hoisted__Str_4888 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4888;
    assert_eq_str(&hoisted__Str_4886, &hoisted__Str_4887, &hoisted__Str_4888);
    Str_delete(&hoisted__Str_4886, (Bool){0});
    Str_delete(&hoisted__Str_4887, (Bool){0});
    Str_delete(&hoisted__Str_4888, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4893 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4893;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4893;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_4894 = 0;
    (void)hoisted__U32_4894;
    U64 hoisted__U64_4895 = ((U64 (*)(CfVec2 *, U32))(void *)hasher)(self, hoisted__U32_4894);
    (void)hoisted__U64_4895;
    return hoisted__U64_4895;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4896 = 16;
    (void)hoisted__U32_4896;
    return hoisted__U32_4896;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4897 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4897;
    I64 hoisted__I64_4898 = 42;
    (void)hoisted__I64_4898;
    assert_eq(&hoisted__Str_4897, v.x, hoisted__I64_4898);
    Str_delete(&hoisted__Str_4897, (Bool){0});
    Str hoisted__Str_4899 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4899;
    I64 hoisted__I64_4900 = 99;
    (void)hoisted__I64_4900;
    assert_eq(&hoisted__Str_4899, v.y, hoisted__I64_4900);
    Str_delete(&hoisted__Str_4899, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4903 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4903;
    I64 hoisted__I64_4904 = 10;
    (void)hoisted__I64_4904;
    assert_eq(&hoisted__Str_4903, p.x, hoisted__I64_4904);
    Str_delete(&hoisted__Str_4903, (Bool){0});
    Str hoisted__Str_4905 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4905;
    I64 hoisted__I64_4906 = 20;
    (void)hoisted__I64_4906;
    assert_eq(&hoisted__Str_4905, p.y, hoisted__I64_4906);
    Str_delete(&hoisted__Str_4905, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4912 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4912;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4912;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_4913 = 0;
    (void)hoisted__U32_4913;
    U64 hoisted__U64_4914 = ((U64 (*)(CfRect *, U32))(void *)hasher)(self, hoisted__U32_4913);
    (void)hoisted__U64_4914;
    return hoisted__U64_4914;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4915 = 32;
    (void)hoisted__U32_4915;
    return hoisted__U32_4915;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4916 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4916;
    I64 hoisted__I64_4917 = 5;
    (void)hoisted__I64_4917;
    assert_eq(&hoisted__Str_4916, r.top_left.x, hoisted__I64_4917);
    Str_delete(&hoisted__Str_4916, (Bool){0});
    Str hoisted__Str_4918 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4918;
    I64 hoisted__I64_4919 = 10;
    (void)hoisted__I64_4919;
    assert_eq(&hoisted__Str_4918, r.top_left.y, hoisted__I64_4919);
    Str_delete(&hoisted__Str_4918, (Bool){0});
    Str hoisted__Str_4920 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4920;
    I64 hoisted__I64_4921 = 100;
    (void)hoisted__I64_4921;
    assert_eq(&hoisted__Str_4920, r.bottom_right.x, hoisted__I64_4921);
    Str_delete(&hoisted__Str_4920, (Bool){0});
    Str hoisted__Str_4922 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4922;
    I64 hoisted__I64_4923 = 200;
    (void)hoisted__I64_4923;
    assert_eq(&hoisted__Str_4922, r.bottom_right.y, hoisted__I64_4923);
    Str_delete(&hoisted__Str_4922, (Bool){0});
    CfRect_delete(&r, (Bool){0});
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
    Bool hoisted__Bool_4928 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4928;
    if (hoisted__Bool_4928) {
        Bool hoisted__Bool_4925 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4925;
        { Bool _ret_val = hoisted__Bool_4925;
                return _ret_val; }
    }
    Bool hoisted__Bool_4929 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4929;
    if (hoisted__Bool_4929) {
        Bool hoisted__Bool_4926 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4926;
        { Bool _ret_val = hoisted__Bool_4926;
                return _ret_val; }
    }
    Bool hoisted__Bool_4930 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4930;
    if (hoisted__Bool_4930) {
        Bool hoisted__Bool_4927 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4927;
        { Bool _ret_val = hoisted__Bool_4927;
                return _ret_val; }
    }
    Bool hoisted__Bool_4931 = 0;
    (void)hoisted__Bool_4931;
    return hoisted__Bool_4931;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4939 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4939;
    if (hoisted__Bool_4939) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4940 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4940;
    if (hoisted__Bool_4940) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4941 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4941;
    if (hoisted__Bool_4941) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4942 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4942;
    UNREACHABLE(&hoisted__Str_4942);
    Str_delete(&hoisted__Str_4942, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4943 = 4;
    (void)hoisted__U32_4943;
    return hoisted__U32_4943;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_4944 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4944;
    Bool hoisted__Bool_4945 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4945;
    assert(&hoisted__Str_4944, hoisted__Bool_4945);
    Str_delete(&hoisted__Str_4944, (Bool){0});
    Bool hoisted__Bool_4946 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4946;
    Str hoisted__Str_4947 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4947;
    Bool hoisted__Bool_4948 = not(hoisted__Bool_4946);
    (void)hoisted__Bool_4948;
    assert(&hoisted__Str_4947, hoisted__Bool_4948);
    Str_delete(&hoisted__Str_4947, (Bool){0});
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
    Bool hoisted__Bool_4949 = is(self, other);
    (void)hoisted__Bool_4949;
    return hoisted__Bool_4949;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_4967 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4967;
    if (hoisted__Bool_4967) {
        I64 *hoisted__I64_4963 = get_payload(self);
        (void)hoisted__I64_4963;
        (void)hoisted__I64_4963;
        Bool hoisted__Bool_4964 = 0;
        (void)hoisted__Bool_4964;
        I64_delete(hoisted__I64_4963, hoisted__Bool_4964);
    }
    Bool hoisted__Bool_4968 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4968;
    if (hoisted__Bool_4968) {
        Str *hoisted__Str_4965 = get_payload(self);
        (void)hoisted__Str_4965;
        (void)hoisted__Str_4965;
        Bool hoisted__Bool_4966 = 0;
        (void)hoisted__Bool_4966;
        Str_delete(hoisted__Str_4965, hoisted__Bool_4966);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4997 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4997;
    if (hoisted__Bool_4997) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4994 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4994;
        { Token * _ret_val = hoisted__Token_4994;
                return _ret_val; }
    }
    Bool hoisted__Bool_4998 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4998;
    if (hoisted__Bool_4998) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4995 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4995;
        Token *hoisted__Token_4996 = Token_Name(hoisted__Str_4995);
        (void)hoisted__Token_4996;
        { Token * _ret_val = hoisted__Token_4996;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4999 = 24;
    (void)hoisted__U32_4999;
    return hoisted__U32_4999;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_5001 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5001;
    Bool hoisted__Bool_5002 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5002;
    assert(&hoisted__Str_5001, hoisted__Bool_5002);
    Str_delete(&hoisted__Str_5001, (Bool){0});
    Bool hoisted__Bool_5003 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5003;
    Token_delete(t, 1);
    Str hoisted__Str_5004 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5004;
    Bool hoisted__Bool_5005 = not(hoisted__Bool_5003);
    (void)hoisted__Bool_5005;
    assert(&hoisted__Str_5004, hoisted__Bool_5005);
    Str_delete(&hoisted__Str_5004, (Bool){0});
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_5006 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5006;
    Bool hoisted__Bool_5007 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5007;
    assert(&hoisted__Str_5006, hoisted__Bool_5007);
    Str_delete(&hoisted__Str_5006, (Bool){0});
    Bool hoisted__Bool_5008 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5008;
    Str hoisted__Str_5009 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5009;
    Bool hoisted__Bool_5010 = not(hoisted__Bool_5008);
    (void)hoisted__Bool_5010;
    assert(&hoisted__Str_5009, hoisted__Bool_5010);
    Str_delete(&hoisted__Str_5009, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_5013 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5013;
    Bool hoisted__Bool_5014 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5014;
    assert(&hoisted__Str_5013, hoisted__Bool_5014);
    Str_delete(&hoisted__Str_5013, (Bool){0});
    Bool hoisted__Bool_5015 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5015;
    Token_delete(t, 1);
    Str hoisted__Str_5016 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5016;
    Bool hoisted__Bool_5017 = not(hoisted__Bool_5015);
    (void)hoisted__Bool_5017;
    assert(&hoisted__Str_5016, hoisted__Bool_5017);
    Str_delete(&hoisted__Str_5016, (Bool){0});
}

I64 F32_cmp_dyn(void *_a0, void *_a1) {
    return F32_cmp(*(F32 *)_a0, *(F32 *)_a1);
}
void *F32_clone_dyn(void *_a0) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(_a0); return _r;
}
void F32_delete_dyn(void *_a0, Bool _a1) {
    F32_delete(_a0, _a1);
}
U32 F32_size_dyn(void) {
    return F32_size();
}
U64 F32_hash_dyn(void *_a0, void *_a1) {
    return F32_hash(*(F32 *)_a0, _a1);
}
U64 U64_add_dyn(void *_a0, void *_a1) {
    return U64_add(*(U64 *)_a0, *(U64 *)_a1);
}
U64 U64_sub_dyn(void *_a0, void *_a1) {
    return U64_sub(*(U64 *)_a0, *(U64 *)_a1);
}
I64 U64_cmp_dyn(void *_a0, void *_a1) {
    return U64_cmp(*(U64 *)_a0, *(U64 *)_a1);
}
void *U64_clone_dyn(void *_a0) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(_a0); return _r;
}
void U64_delete_dyn(void *_a0, Bool _a1) {
    U64_delete(_a0, _a1);
}
U32 U64_size_dyn(void) {
    return U64_size();
}
U64 U64_hash_dyn(void *_a0, void *_a1) {
    return U64_hash(*(U64 *)_a0, _a1);
}
I64 U32_to_i64_dyn(void *_a0) {
    return U32_to_i64(*(U32 *)_a0);
}
void *U32_to_str_dyn(void *_a0) {
    return (void *)U32_to_str(*(U32 *)_a0);
}
U32 U32_add_dyn(void *_a0, void *_a1) {
    return U32_add(*(U32 *)_a0, *(U32 *)_a1);
}
U32 U32_sub_dyn(void *_a0, void *_a1) {
    return U32_sub(*(U32 *)_a0, *(U32 *)_a1);
}
U32 U32_mul_dyn(void *_a0, void *_a1) {
    return U32_mul(*(U32 *)_a0, *(U32 *)_a1);
}
Bool U32_eq_dyn(void *_a0, void *_a1) {
    return U32_eq(*(U32 *)_a0, *(U32 *)_a1);
}
I64 U32_cmp_dyn(void *_a0, void *_a1) {
    return U32_cmp(*(U32 *)_a0, *(U32 *)_a1);
}
void *U32_clone_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(_a0); return _r;
}
void U32_delete_dyn(void *_a0, Bool _a1) {
    U32_delete(_a0, _a1);
}
U32 U32_size_dyn(void) {
    return U32_size();
}
U64 U32_hash_dyn(void *_a0, void *_a1) {
    return U32_hash(*(U32 *)_a0, _a1);
}
Bool U32_lt_dyn(void *_a0, void *_a1) {
    return U32_lt(*(U32 *)_a0, *(U32 *)_a1);
}
Bool U32_gt_dyn(void *_a0, void *_a1) {
    return U32_gt(*(U32 *)_a0, *(U32 *)_a1);
}
Bool U32_lte_dyn(void *_a0, void *_a1) {
    return U32_lte(*(U32 *)_a0, *(U32 *)_a1);
}
Bool U32_gte_dyn(void *_a0, void *_a1) {
    return U32_gte(*(U32 *)_a0, *(U32 *)_a1);
}
I64 I32_cmp_dyn(void *_a0, void *_a1) {
    return I32_cmp(*(I32 *)_a0, *(I32 *)_a1);
}
void *I32_clone_dyn(void *_a0) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(_a0); return _r;
}
void I32_delete_dyn(void *_a0, Bool _a1) {
    I32_delete(_a0, _a1);
}
U32 I32_size_dyn(void) {
    return I32_size();
}
U64 I32_hash_dyn(void *_a0, void *_a1) {
    return I32_hash(*(I32 *)_a0, _a1);
}
I64 I8_cmp_dyn(void *_a0, void *_a1) {
    return I8_cmp(*(I8 *)_a0, *(I8 *)_a1);
}
void *I8_clone_dyn(void *_a0) {
    I8 *_r = malloc(sizeof(I8)); *_r = I8_clone(_a0); return _r;
}
void I8_delete_dyn(void *_a0, Bool _a1) {
    I8_delete(_a0, _a1);
}
U32 I8_size_dyn(void) {
    return I8_size();
}
U64 I8_hash_dyn(void *_a0, void *_a1) {
    return I8_hash(*(I8 *)_a0, _a1);
}
I64 U8_cmp_dyn(void *_a0, void *_a1) {
    return U8_cmp(*(U8 *)_a0, *(U8 *)_a1);
}
void *U8_clone_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(_a0); return _r;
}
void U8_delete_dyn(void *_a0, Bool _a1) {
    U8_delete(_a0, _a1);
}
U32 U8_size_dyn(void) {
    return U8_size();
}
U64 U8_hash_dyn(void *_a0, void *_a1) {
    return U8_hash(*(U8 *)_a0, _a1);
}
U32 Str_len_dyn(void *_a0) {
    return Str_len(_a0);
}
I64 Str_cmp_dyn(void *_a0, void *_a1) {
    return Str_cmp(_a0, _a1);
}
void *Str_with_capacity_dyn(void *_a0) {
    return (void *)Str_with_capacity(*(U32 *)_a0);
}
void Str_delete_dyn(void *_a0, Bool _a1) {
    Str_delete(_a0, _a1);
}
Bool Str_is_empty_dyn(void *_a0) {
    return Str_is_empty(_a0);
}
U64 Str_hash_dyn(void *_a0, void *_a1) {
    return Str_hash(_a0, _a1);
}
U32 Str_size_dyn(void) {
    return Str_size();
}
Bool Str_eq_dyn(void *_a0, void *_a1) {
    return Str_eq(_a0, _a1);
}
void OutOfBounds_delete_dyn(void *_a0, Bool _a1) {
    OutOfBounds_delete(_a0, _a1);
}
U64 OutOfBounds_hash_dyn(void *_a0, void *_a1) {
    return OutOfBounds_hash(_a0, _a1);
}
U32 OutOfBounds_size_dyn(void) {
    return OutOfBounds_size();
}
U32 Dynamic_size_dyn(void) {
    return Dynamic_size();
}
void *I64_to_str_dyn(void *_a0) {
    return (void *)I64_to_str(*(I64 *)_a0);
}
U8 I64_to_u8_dyn(void *_a0) {
    return I64_to_u8(*(I64 *)_a0);
}
I64 I64_add_dyn(void *_a0, void *_a1) {
    return I64_add(*(I64 *)_a0, *(I64 *)_a1);
}
I64 I64_sub_dyn(void *_a0, void *_a1) {
    return I64_sub(*(I64 *)_a0, *(I64 *)_a1);
}
I64 I64_div_dyn(void *_a0, void *_a1) {
    return I64_div(*(I64 *)_a0, *(I64 *)_a1);
}
I64 I64_mod_dyn(void *_a0, void *_a1) {
    return I64_mod(*(I64 *)_a0, *(I64 *)_a1);
}
Bool I64_eq_dyn(void *_a0, void *_a1) {
    return I64_eq(*(I64 *)_a0, *(I64 *)_a1);
}
I64 I64_cmp_dyn(void *_a0, void *_a1) {
    return I64_cmp(*(I64 *)_a0, *(I64 *)_a1);
}
void *I64_clone_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(_a0); return _r;
}
void I64_delete_dyn(void *_a0, Bool _a1) {
    I64_delete(_a0, _a1);
}
U32 I64_size_dyn(void) {
    return I64_size();
}
U64 I64_hash_dyn(void *_a0, void *_a1) {
    return I64_hash(*(I64 *)_a0, _a1);
}
Bool I64_lt_dyn(void *_a0, void *_a1) {
    return I64_lt(*(I64 *)_a0, *(I64 *)_a1);
}
Bool I64_gt_dyn(void *_a0, void *_a1) {
    return I64_gt(*(I64 *)_a0, *(I64 *)_a1);
}
Bool I64_neq_dyn(void *_a0, void *_a1) {
    return I64_neq(*(I64 *)_a0, *(I64 *)_a1);
}
Bool Bool_eq_dyn(void *_a0, void *_a1) {
    return Bool_eq(*(Bool *)_a0, *(Bool *)_a1);
}
I64 Bool_cmp_dyn(void *_a0, void *_a1) {
    return Bool_cmp(*(Bool *)_a0, *(Bool *)_a1);
}
void *Bool_clone_dyn(void *_a0) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(_a0); return _r;
}
void Bool_delete_dyn(void *_a0, Bool _a1) {
    Bool_delete(_a0, _a1);
}
U32 Bool_size_dyn(void) {
    return Bool_size();
}
U64 Bool_hash_dyn(void *_a0, void *_a1) {
    return Bool_hash(*(Bool *)_a0, _a1);
}
Bool Primitive_eq_dyn(void *_a0, void *_a1) {
    return Primitive_eq(_a0, _a1);
}
void Primitive_delete_dyn(void *_a0, Bool _a1) {
    Primitive_delete(_a0, _a1);
}
U32 Primitive_size_dyn(void) {
    return Primitive_size();
}
void Type_delete_dyn(void *_a0, Bool _a1) {
    Type_delete(_a0, _a1);
}
U32 Type_size_dyn(void) {
    return Type_size();
}
void *Array_new_type_name_dyn(void *_a0, void *_a1) {
    return (void *)Array_new_type_name(_a0, *(U32 *)_a1);
}
void *Array_new_dyn(void *_a0, void *_a1) {
    return (void *)Array_new(_a0, *(U32 *)_a1);
}
U32 Array_len_dyn(void *_a0) {
    return Array_len(_a0);
}
void Array_set_dyn(void *_a0, void *_a1, void *_a2) {
    Array_set(_a0, *(U32 *)_a1, _a2);
}
void Array_delete_dyn(void *_a0, Bool _a1) {
    Array_delete(_a0, _a1);
}
U32 Array_size_dyn(void) {
    return Array_size();
}
void CfVec2_delete_dyn(void *_a0, Bool _a1) {
    CfVec2_delete(_a0, _a1);
}
U64 CfVec2_hash_dyn(void *_a0, void *_a1) {
    return CfVec2_hash(_a0, _a1);
}
U32 CfVec2_size_dyn(void) {
    return CfVec2_size();
}
void CfRect_delete_dyn(void *_a0, Bool _a1) {
    CfRect_delete(_a0, _a1);
}
U64 CfRect_hash_dyn(void *_a0, void *_a1) {
    return CfRect_hash(_a0, _a1);
}
U32 CfRect_size_dyn(void) {
    return CfRect_size();
}
Bool Color_eq_dyn(void *_a0, void *_a1) {
    return Color_eq(_a0, _a1);
}
void Color_delete_dyn(void *_a0, Bool _a1) {
    Color_delete(_a0, _a1);
}
U32 Color_size_dyn(void) {
    return Color_size();
}
Bool Token_is_dyn(void *_a0, void *_a1) {
    return Token_is(_a0, _a1);
}
void Token_delete_dyn(void *_a0, Bool _a1) {
    Token_delete(_a0, _a1);
}
U32 Token_size_dyn(void) {
    return Token_size();
}
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)F32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)F32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)F32_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)F32_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)F32_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U64_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U64_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)U64_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)U32_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)U32_to_str_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U32_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U32_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)U32_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)U32_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)U32_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)U32_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U32_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U32_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)U32_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U32_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U32_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U32_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U32_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I32_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I32_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)I32_hash_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I8_delete_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I8_size_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)I8_hash_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U8_delete_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U8_size_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)U8_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Str_len_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Str_get;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Str_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)Str_with_capacity_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)Str_push_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Str_clone;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Str_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_empty", 8ULL) == 0) return (void*)Str_is_empty_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)Str_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Str_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Str_eq_dyn;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)OutOfBounds_clone;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)OutOfBounds_delete_dyn;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)OutOfBounds_hash_dyn;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)OutOfBounds_size_dyn;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Dynamic_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)I64_to_str_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "to_u8", 5ULL) == 0) return (void*)I64_to_u8_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)I64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)I64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)I64_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)I64_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)I64_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I64_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I64_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)I64_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I64_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I64_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I64_neq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Bool_eq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Bool_cmp_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Bool_clone_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Bool_delete_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Bool_size_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)Bool_hash_dyn;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Primitive_eq_dyn;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Primitive_delete_dyn;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Primitive_clone;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Primitive_size_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Unknown", 7ULL) == 0) return (void*)Type_Unknown;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "None", 4ULL) == 0) return (void*)Type_None;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Struct", 6ULL) == 0) return (void*)Type_Struct;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "StructDef", 9ULL) == 0) return (void*)Type_StructDef;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Enum", 4ULL) == 0) return (void*)Type_Enum;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "EnumDef", 7ULL) == 0) return (void*)Type_EnumDef;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncDef", 7ULL) == 0) return (void*)Type_FuncDef;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncPtr", 7ULL) == 0) return (void*)Type_FuncPtr;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Dynamic", 7ULL) == 0) return (void*)Type_Dynamic;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Custom", 6ULL) == 0) return (void*)Type_Custom;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "Primitive", 9ULL) == 0) return (void*)Type_Primitive;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Type_delete_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Type_clone;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Type_size_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "new_type_name", 13ULL) == 0) return (void*)Array_new_type_name_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Array_new_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Array_len_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Array_get;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)Array_set_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Array_delete_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Array_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Array_size_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)CfVec2_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)CfVec2_delete_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)CfVec2_hash_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)CfVec2_size_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)CfRect_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)CfRect_delete_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)CfRect_hash_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)CfRect_size_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Color_eq_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Color_delete_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Color_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Color_size_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Num", 3ULL) == 0) return (void*)Token_Num;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Name", 4ULL) == 0) return (void*)Token_Name;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Eof", 3ULL) == 0) return (void*)Token_Eof;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "is", 2ULL) == 0) return (void*)Token_is_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Token_delete_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Token_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Token_size_dyn;
    fprintf(stderr, "dyn_fn: unknown %s.%s\n", (char*)type_name->c_str, (char*)method->c_str);
    exit(1);
}

U32 dyn_size_of(Str *type_name) {
    (void)type_name;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0) return sizeof(Dynamic);
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
        return 10LL;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        return 11LL;
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
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Unknown", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"None", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Struct", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Enum", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncPtr", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Custom", .count = 6ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 2LL) return 0;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 0;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 0;
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return 0;
        if (*index == 1LL) return 0;
        if (*index == 2LL) return 1;
        if (*index == 3LL) return 0;
        if (*index == 4LL) return 1;
        if (*index == 5LL) return 0;
        if (*index == 6LL) return 0;
        if (*index == 7LL) return 0;
        if (*index == 8LL) return 0;
        if (*index == 9LL) return 1;
        if (*index == 10LL) return 1;
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
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    }
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 3LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 4LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 5LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 6LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 7LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 8LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 9LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 10LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Primitive", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
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
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        return 1LL;
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
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
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
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "HashFn", 6ULL) == 0) {
    }
    fprintf(stderr, "func_sig_throw_type: type '%.*s' index out of range\n", (int)type_name->count, (char*)type_name->c_str);
    exit(1);
}

Str *dyn_type_to_str(Type *type) {
    switch (type->tag) {
    case Type_TAG_Unknown: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_None: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Struct: return Str_clone(&type->data.Struct);
    case Type_TAG_StructDef: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Enum: return Str_clone(&type->data.Enum);
    case Type_TAG_EnumDef: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_FuncDef: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_FuncPtr: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Dynamic: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT}; _lit; });
    case Type_TAG_Custom: return Str_clone(&type->data.Custom);
    case Type_TAG_Primitive:
        switch (type->data.Primitive.tag) {
        case Primitive_TAG_I16: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        case Primitive_TAG_U16: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        case Primitive_TAG_I8: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        case Primitive_TAG_U8: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT}; _lit; });
        case Primitive_TAG_U32: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        case Primitive_TAG_I32: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        case Primitive_TAG_U64: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        case Primitive_TAG_I64: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        case Primitive_TAG_F32: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        case Primitive_TAG_Bool: return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT}; _lit; });
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
