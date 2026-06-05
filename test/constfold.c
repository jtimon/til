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
    Type_TAG_Primitive,
    Type_TAG_FuncPtrSig
} Type_tag;
typedef struct Type Type;
typedef struct Array Array;
typedef struct CfVec2 CfVec2;
typedef struct CfRect CfRect;
typedef struct CfVec3f CfVec3f;
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
        Str FuncPtrSig;
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


typedef struct CfVec3f {
    F32 x;
    F32 y;
    F32 z;
} CfVec3f;


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
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
U32 CfVec3f_size(void);
void test_struct_fold_f32(void);
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
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
U32 CfVec3f_size(void);
void test_struct_fold_f32(void);
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
Type *Type_FuncPtrSig(Str *);
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
    U32 hoisted__U32_1278 = 16;
    (void)hoisted__U32_1278;
    return hoisted__U32_1278;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1279 = Str_cmp(a, b);
    (void)hoisted__I64_1279;
    I64 hoisted__I64_1280 = 0;
    (void)hoisted__I64_1280;
    Bool hoisted__Bool_1281 = I64_eq(hoisted__I64_1279, hoisted__I64_1280);
    (void)hoisted__Bool_1281;
    return hoisted__Bool_1281;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1379 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1379->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1379;
    return hoisted__OutOfBounds_1379;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1380 = 0;
    (void)hoisted__Bool_1380;
    Str_delete(&self->msg, hoisted__Bool_1380);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1381 = 0;
    (void)hoisted__U32_1381;
    U64 hoisted__U64_1382 = ((U64 (*)(OutOfBounds *, U32))(void *)hasher)(self, hoisted__U32_1381);
    (void)hoisted__U64_1382;
    return hoisted__U64_1382;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1383 = 16;
    (void)hoisted__U32_1383;
    return hoisted__U32_1383;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1391 = 8;
    (void)hoisted__U32_1391;
    return hoisted__U32_1391;
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1596 = 0;
    (void)hoisted__I64_1596;
    Bool hoisted__Bool_1597 = I64_eq(val, hoisted__I64_1596);
    (void)hoisted__Bool_1597;
    if (hoisted__Bool_1597) {
        U64 hoisted__U64_1560 = 2ULL;
        (void)hoisted__U64_1560;
        void * buf = malloc(hoisted__U64_1560);
        I64 hoisted__I64_1561 = 48;
        (void)hoisted__I64_1561;
        U64 hoisted__U64_1562 = 1ULL;
        (void)hoisted__U64_1562;
        memcpy(buf, &hoisted__I64_1561, hoisted__U64_1562);
        U64 hoisted__U64_1563 = 1ULL;
        (void)hoisted__U64_1563;
        void *hoisted__v_1564 = ptr_add(buf, hoisted__U64_1563);
        (void)hoisted__v_1564;
        (void)hoisted__v_1564;
        I32 hoisted__I32_1565 = 0;
        (void)hoisted__I32_1565;
        U64 hoisted__U64_1566 = 1ULL;
        (void)hoisted__U64_1566;
        memset(hoisted__v_1564, hoisted__I32_1565, hoisted__U64_1566);
        I64 hoisted__I64_1567 = 1;
        (void)hoisted__I64_1567;
        I64 hoisted__I64_1568 = 1;
        (void)hoisted__I64_1568;
        Str *hoisted__Str_1569 = malloc(sizeof(Str));
        hoisted__Str_1569->c_str = buf;
        hoisted__Str_1569->count = hoisted__I64_1567;
        hoisted__Str_1569->cap = hoisted__I64_1568;
        (void)hoisted__Str_1569;
        { Str * _ret_val = hoisted__Str_1569;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1598 = 0;
    (void)hoisted__I64_1598;
    Bool hoisted__Bool_1599 = I64_lt(val, hoisted__I64_1598);
    (void)hoisted__Bool_1599;
    if (hoisted__Bool_1599) {
        Bool hoisted__Bool_1570 = 1;
        (void)hoisted__Bool_1570;
        is_neg = hoisted__Bool_1570;
        I64 hoisted__I64_1571 = 0;
        (void)hoisted__I64_1571;
        I64 hoisted__I64_1572 = I64_sub(hoisted__I64_1571, val);
        (void)hoisted__I64_1572;
        v = hoisted__I64_1572;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1574 = 0;
        (void)hoisted__I64_1574;
        Bool _wcond_Bool_1573 = I64_gt(tmp, hoisted__I64_1574);
        (void)_wcond_Bool_1573;
        if (_wcond_Bool_1573) {
        } else {
            break;
        }
        U64 hoisted__U64_1575 = 1ULL;
        (void)hoisted__U64_1575;
        U64 hoisted__U64_1576 = U64_add(ndigits, hoisted__U64_1575);
        (void)hoisted__U64_1576;
        ndigits = hoisted__U64_1576;
        I64 hoisted__I64_1577 = 10;
        (void)hoisted__I64_1577;
        I64 hoisted__I64_1578 = I64_div(tmp, hoisted__I64_1577);
        (void)hoisted__I64_1578;
        tmp = hoisted__I64_1578;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1579 = 1ULL;
        (void)hoisted__U64_1579;
        U64 hoisted__U64_1580 = U64_add(total, hoisted__U64_1579);
        (void)hoisted__U64_1580;
        total = hoisted__U64_1580;
    }
    U64 hoisted__U64_1600 = 1ULL;
    (void)hoisted__U64_1600;
    U64 hoisted__U64_1601 = U64_add(total, hoisted__U64_1600);
    (void)hoisted__U64_1601;
    void * buf = malloc(hoisted__U64_1601);
    if (is_neg) {
        I64 hoisted__I64_1581 = 45;
        (void)hoisted__I64_1581;
        U64 hoisted__U64_1582 = 1ULL;
        (void)hoisted__U64_1582;
        memcpy(buf, &hoisted__I64_1581, hoisted__U64_1582);
    }
    U64 hoisted__U64_1602 = 1ULL;
    (void)hoisted__U64_1602;
    U64 i = U64_sub(total, hoisted__U64_1602);
    while (1) {
        I64 hoisted__I64_1584 = 0;
        (void)hoisted__I64_1584;
        Bool _wcond_Bool_1583 = I64_gt(v, hoisted__I64_1584);
        (void)_wcond_Bool_1583;
        if (_wcond_Bool_1583) {
        } else {
            break;
        }
        I64 hoisted__I64_1585 = 10;
        (void)hoisted__I64_1585;
        I64 hoisted__I64_1586 = I64_mod(v, hoisted__I64_1585);
        (void)hoisted__I64_1586;
        I64 hoisted__I64_1587 = 48;
        (void)hoisted__I64_1587;
        I64 hoisted__I64_1588 = I64_add(hoisted__I64_1586, hoisted__I64_1587);
        (void)hoisted__I64_1588;
        void *hoisted__v_1589 = ptr_add(buf, i);
        (void)hoisted__v_1589;
        (void)hoisted__v_1589;
        U8 hoisted__U8_1590 = I64_to_u8(hoisted__I64_1588);
        (void)hoisted__U8_1590;
        U64 hoisted__U64_1591 = 1ULL;
        (void)hoisted__U64_1591;
        memcpy(hoisted__v_1589, &hoisted__U8_1590, hoisted__U64_1591);
        I64 hoisted__I64_1592 = 10;
        (void)hoisted__I64_1592;
        I64 hoisted__I64_1593 = I64_div(v, hoisted__I64_1592);
        (void)hoisted__I64_1593;
        v = hoisted__I64_1593;
        U64 hoisted__U64_1594 = 1ULL;
        (void)hoisted__U64_1594;
        U64 hoisted__U64_1595 = U64_sub(i, hoisted__U64_1594);
        (void)hoisted__U64_1595;
        i = hoisted__U64_1595;
    }
    void *hoisted__v_1603 = ptr_add(buf, total);
    (void)hoisted__v_1603;
    (void)hoisted__v_1603;
    I32 hoisted__I32_1604 = 0;
    (void)hoisted__I32_1604;
    U64 hoisted__U64_1605 = 1ULL;
    (void)hoisted__U64_1605;
    memset(hoisted__v_1603, hoisted__I32_1604, hoisted__U64_1605);
    Str *hoisted__Str_1606 = malloc(sizeof(Str));
    hoisted__Str_1606->c_str = buf;
    hoisted__Str_1606->count = total;
    hoisted__Str_1606->cap = total;
    (void)hoisted__Str_1606;
    return hoisted__Str_1606;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1626 = 8;
    (void)hoisted__U32_1626;
    return hoisted__U32_1626;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1757 = 0;
    (void)hoisted__U32_1757;
    U64 hoisted__U64_1758 = ((U64 (*)(I64 *, U32))(void *)hasher)(&self, hoisted__U32_1757);
    (void)hoisted__U64_1758;
    return hoisted__U64_1758;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1761 = I64_cmp(a, b);
    (void)hoisted__I64_1761;
    I64 hoisted__I64_1762 = -1;
    (void)hoisted__I64_1762;
    Bool hoisted__Bool_1763 = I64_eq(hoisted__I64_1761, hoisted__I64_1762);
    (void)hoisted__Bool_1763;
    return hoisted__Bool_1763;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1764 = I64_cmp(a, b);
    (void)hoisted__I64_1764;
    I64 hoisted__I64_1765 = 1;
    (void)hoisted__I64_1765;
    Bool hoisted__Bool_1766 = I64_eq(hoisted__I64_1764, hoisted__I64_1765);
    (void)hoisted__Bool_1766;
    return hoisted__Bool_1766;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1767 = I64_eq(a, b);
    (void)hoisted__Bool_1767;
    Bool hoisted__Bool_1768 = not(hoisted__Bool_1767);
    (void)hoisted__Bool_1768;
    return hoisted__Bool_1768;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1786 = Bool_eq(a, b);
    (void)hoisted__Bool_1786;
    if (hoisted__Bool_1786) {
        I64 hoisted__I64_1784 = 0;
        (void)hoisted__I64_1784;
        { I64 _ret_val = hoisted__I64_1784;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1785 = -1;
        (void)hoisted__I64_1785;
        return hoisted__I64_1785;
    }
    I64 hoisted__I64_1787 = 1;
    (void)hoisted__I64_1787;
    return hoisted__I64_1787;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1788 = 1;
    (void)hoisted__U32_1788;
    return hoisted__U32_1788;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1789 = 0;
    (void)hoisted__U32_1789;
    U64 hoisted__U64_1790 = ((U64 (*)(Bool *, U32))(void *)hasher)(&self, hoisted__U32_1789);
    (void)hoisted__U64_1790;
    return hoisted__U64_1790;
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
    Bool hoisted__Bool_1944 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1944;
    if (hoisted__Bool_1944) {
        Bool hoisted__Bool_1934 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1934;
        { Bool _ret_val = hoisted__Bool_1934;
                return _ret_val; }
    }
    Bool hoisted__Bool_1945 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1945;
    if (hoisted__Bool_1945) {
        Bool hoisted__Bool_1935 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1935;
        { Bool _ret_val = hoisted__Bool_1935;
                return _ret_val; }
    }
    Bool hoisted__Bool_1946 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1946;
    if (hoisted__Bool_1946) {
        Bool hoisted__Bool_1936 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_1936;
        { Bool _ret_val = hoisted__Bool_1936;
                return _ret_val; }
    }
    Bool hoisted__Bool_1947 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1947;
    if (hoisted__Bool_1947) {
        Bool hoisted__Bool_1937 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_1937;
        { Bool _ret_val = hoisted__Bool_1937;
                return _ret_val; }
    }
    Bool hoisted__Bool_1948 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1948;
    if (hoisted__Bool_1948) {
        Bool hoisted__Bool_1938 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_1938;
        { Bool _ret_val = hoisted__Bool_1938;
                return _ret_val; }
    }
    Bool hoisted__Bool_1949 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1949;
    if (hoisted__Bool_1949) {
        Bool hoisted__Bool_1939 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_1939;
        { Bool _ret_val = hoisted__Bool_1939;
                return _ret_val; }
    }
    Bool hoisted__Bool_1950 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1950;
    if (hoisted__Bool_1950) {
        Bool hoisted__Bool_1940 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_1940;
        { Bool _ret_val = hoisted__Bool_1940;
                return _ret_val; }
    }
    Bool hoisted__Bool_1951 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1951;
    if (hoisted__Bool_1951) {
        Bool hoisted__Bool_1941 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_1941;
        { Bool _ret_val = hoisted__Bool_1941;
                return _ret_val; }
    }
    Bool hoisted__Bool_1952 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1952;
    if (hoisted__Bool_1952) {
        Bool hoisted__Bool_1942 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_1942;
        { Bool _ret_val = hoisted__Bool_1942;
                return _ret_val; }
    }
    Bool hoisted__Bool_1953 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1953;
    if (hoisted__Bool_1953) {
        Bool hoisted__Bool_1943 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_1943;
        { Bool _ret_val = hoisted__Bool_1943;
                return _ret_val; }
    }
    Bool hoisted__Bool_1954 = 0;
    (void)hoisted__Bool_1954;
    return hoisted__Bool_1954;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1976 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1976;
    if (hoisted__Bool_1976) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1977 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1977;
    if (hoisted__Bool_1977) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_1978 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1978;
    if (hoisted__Bool_1978) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_1979 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1979;
    if (hoisted__Bool_1979) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1980 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1980;
    if (hoisted__Bool_1980) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1981 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1981;
    if (hoisted__Bool_1981) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1982 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1982;
    if (hoisted__Bool_1982) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1983 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1983;
    if (hoisted__Bool_1983) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1984 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1984;
    if (hoisted__Bool_1984) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1985 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1985;
    if (hoisted__Bool_1985) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_1986 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1986;
    UNREACHABLE(&hoisted__Str_1986);
    Str_delete(&hoisted__Str_1986, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1987 = 4;
    (void)hoisted__U32_1987;
    return hoisted__U32_1987;
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
Type *Type_FuncPtrSig(Str * val) {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_FuncPtrSig;
    r->data.FuncPtrSig = *val;
    free(val);
    return r;
}
void Type_delete(Type * self, Bool call_free) {
    Bool hoisted__Bool_2039 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2039;
    if (hoisted__Bool_2039) {
        Str *hoisted__Str_2029 = get_payload(self);
        (void)hoisted__Str_2029;
        (void)hoisted__Str_2029;
        Bool hoisted__Bool_2030 = 0;
        (void)hoisted__Bool_2030;
        Str_delete(hoisted__Str_2029, hoisted__Bool_2030);
    }
    Bool hoisted__Bool_2040 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2040;
    if (hoisted__Bool_2040) {
        Str *hoisted__Str_2031 = get_payload(self);
        (void)hoisted__Str_2031;
        (void)hoisted__Str_2031;
        Bool hoisted__Bool_2032 = 0;
        (void)hoisted__Bool_2032;
        Str_delete(hoisted__Str_2031, hoisted__Bool_2032);
    }
    Bool hoisted__Bool_2041 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2041;
    if (hoisted__Bool_2041) {
        Str *hoisted__Str_2033 = get_payload(self);
        (void)hoisted__Str_2033;
        (void)hoisted__Str_2033;
        Bool hoisted__Bool_2034 = 0;
        (void)hoisted__Bool_2034;
        Str_delete(hoisted__Str_2033, hoisted__Bool_2034);
    }
    Bool hoisted__Bool_2042 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2042;
    if (hoisted__Bool_2042) {
        Primitive *hoisted__Primitive_2035 = get_payload(self);
        (void)hoisted__Primitive_2035;
        (void)hoisted__Primitive_2035;
        Bool hoisted__Bool_2036 = 0;
        (void)hoisted__Bool_2036;
        Primitive_delete(hoisted__Primitive_2035, hoisted__Bool_2036);
    }
    Bool hoisted__Bool_2043 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2043;
    if (hoisted__Bool_2043) {
        Str *hoisted__Str_2037 = get_payload(self);
        (void)hoisted__Str_2037;
        (void)hoisted__Str_2037;
        Bool hoisted__Bool_2038 = 0;
        (void)hoisted__Bool_2038;
        Str_delete(hoisted__Str_2037, hoisted__Bool_2038);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2122 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2122;
    if (hoisted__Bool_2122) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2123 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2123;
    if (hoisted__Bool_2123) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2124 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2124;
    if (hoisted__Bool_2124) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2114 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2114;
        Type *hoisted__Type_2115 = Type_Struct(hoisted__Str_2114);
        (void)hoisted__Type_2115;
        { Type * _ret_val = hoisted__Type_2115;
                return _ret_val; }
    }
    Bool hoisted__Bool_2125 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2125;
    if (hoisted__Bool_2125) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2126 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2126;
    if (hoisted__Bool_2126) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2116 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2116;
        Type *hoisted__Type_2117 = Type_Enum(hoisted__Str_2116);
        (void)hoisted__Type_2117;
        { Type * _ret_val = hoisted__Type_2117;
                return _ret_val; }
    }
    Bool hoisted__Bool_2127 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2127;
    if (hoisted__Bool_2127) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2128 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2128;
    if (hoisted__Bool_2128) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2129 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2129;
    if (hoisted__Bool_2129) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2130 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2130;
    if (hoisted__Bool_2130) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2131 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2131;
    if (hoisted__Bool_2131) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2118 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2118;
        Type *hoisted__Type_2119 = Type_Custom(hoisted__Str_2118);
        (void)hoisted__Type_2119;
        { Type * _ret_val = hoisted__Type_2119;
                return _ret_val; }
    }
    Bool hoisted__Bool_2132 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2132;
    if (hoisted__Bool_2132) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2120 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2120;
        Type *hoisted__Type_2121 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2120; _oa; }));
        (void)hoisted__Type_2121;
        { Type * _ret_val = hoisted__Type_2121;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2133 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2133;
    Type *hoisted__Type_2134 = Type_FuncPtrSig(hoisted__Str_2133);
    (void)hoisted__Type_2134;
    return hoisted__Type_2134;
}

U32 Type_size(void) {
    U32 hoisted__U32_2135 = 24;
    (void)hoisted__U32_2135;
    return hoisted__U32_2135;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3799 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3799;
    if (hoisted__Bool_3799) {
        Type *hoisted__Type_3794 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3794;
        U32 hoisted__U32_3795 = 1;
        (void)hoisted__U32_3795;
        Array *_va_Array_114 = Array_new(hoisted__Type_3794, hoisted__U32_3795);
        (void)_va_Array_114;
        Type_delete(hoisted__Type_3794, 1);
        U32 hoisted__U32_3796 = 0;
        (void)hoisted__U32_3796;
        Str hoisted__Str_3797 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3797;
        Array_set(_va_Array_114, hoisted__U32_3796, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3797; _oa; }));
        Str hoisted__Str_3798 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3798;
        panic(&hoisted__Str_3798, _va_Array_114);
        Str_delete(&hoisted__Str_3798, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3800 = calloc(cap, elem_size);
    (void)hoisted__v_3800;
    void * hoisted__v_3801 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3801;
    void * hoisted__v_3802 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3802;
    Array *hoisted__Array_3803 = malloc(sizeof(Array));
    hoisted__Array_3803->data = hoisted__v_3800;
    hoisted__Array_3803->cap = cap;
    hoisted__Array_3803->elem_size = elem_size;
    hoisted__Array_3803->elem_clone = hoisted__v_3801;
    hoisted__Array_3803->elem_delete = hoisted__v_3802;
    (void)hoisted__Array_3803;
    return hoisted__Array_3803;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3804 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3804;
    Str_delete(elem_type, 1);
    return hoisted__Array_3804;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3825 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3825;
    if (hoisted__Bool_3825) {
        Type *hoisted__Type_3806 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3806;
        U32 hoisted__U32_3807 = 6;
        (void)hoisted__U32_3807;
        Array *_va_Array_115 = Array_new(hoisted__Type_3806, hoisted__U32_3807);
        (void)_va_Array_115;
        Type_delete(hoisted__Type_3806, 1);
        U32 hoisted__U32_3808 = 0;
        (void)hoisted__U32_3808;
        Str hoisted__Str_3809 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3809;
        Array_set(_va_Array_115, hoisted__U32_3808, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3809; _oa; }));
        U32 hoisted__U32_3810 = 1;
        (void)hoisted__U32_3810;
        Str hoisted__Str_3811 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3811;
        Array_set(_va_Array_115, hoisted__U32_3810, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3811; _oa; }));
        U32 hoisted__U32_3812 = 2;
        (void)hoisted__U32_3812;
        Str *hoisted__Str_3813 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3813;
        Array_set(_va_Array_115, hoisted__U32_3812, hoisted__Str_3813);
        U32 hoisted__U32_3814 = 3;
        (void)hoisted__U32_3814;
        Str hoisted__Str_3815 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3815;
        Array_set(_va_Array_115, hoisted__U32_3814, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3815; _oa; }));
        U32 hoisted__U32_3816 = 4;
        (void)hoisted__U32_3816;
        Str *hoisted__Str_3817 = U32_to_str(self->cap);
        (void)hoisted__Str_3817;
        Array_set(_va_Array_115, hoisted__U32_3816, hoisted__Str_3817);
        U32 hoisted__U32_3818 = 5;
        (void)hoisted__U32_3818;
        Str hoisted__Str_3819 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3819;
        Array_set(_va_Array_115, hoisted__U32_3818, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3819; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3820 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_115); hoisted__OutOfBounds_3820->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3820;
        U32 hoisted__U32_3821 = 16;
        (void)hoisted__U32_3821;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3820, hoisted__U32_3821);
        OutOfBounds_delete(hoisted__OutOfBounds_3820, 1);
        I64 hoisted__I64_3822 = 3;
        (void)hoisted__I64_3822;
        *_err_kind = hoisted__I64_3822;
    }
    I64 hoisted__I64_3826 = 0;
    (void)hoisted__I64_3826;
    Bool hoisted__Bool_3827 = I64_eq(DEREF(_err_kind), hoisted__I64_3826);
    (void)hoisted__Bool_3827;
    if (hoisted__Bool_3827) {
        U32 hoisted__U64_3823 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3823;
        void *hoisted__v_3824 = ptr_add(self->data, hoisted__U64_3823);
        (void)hoisted__v_3824;
        (void)hoisted__v_3824;
        { void * _ret_val = hoisted__v_3824;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3842 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3842;
    if (hoisted__Bool_3842) {
        Type *hoisted__Type_3829 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3829;
        U32 hoisted__U32_3830 = 5;
        (void)hoisted__U32_3830;
        Array *_va_Array_116 = Array_new(hoisted__Type_3829, hoisted__U32_3830);
        (void)_va_Array_116;
        Type_delete(hoisted__Type_3829, 1);
        U32 hoisted__U32_3831 = 0;
        (void)hoisted__U32_3831;
        Str hoisted__Str_3832 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3832;
        Array_set(_va_Array_116, hoisted__U32_3831, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3832; _oa; }));
        U32 hoisted__U32_3833 = 1;
        (void)hoisted__U32_3833;
        Str *hoisted__Str_3834 = U32_to_str(i);
        (void)hoisted__Str_3834;
        Array_set(_va_Array_116, hoisted__U32_3833, hoisted__Str_3834);
        U32 hoisted__U32_3835 = 2;
        (void)hoisted__U32_3835;
        Str hoisted__Str_3836 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3836;
        Array_set(_va_Array_116, hoisted__U32_3835, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3836; _oa; }));
        U32 hoisted__U32_3837 = 3;
        (void)hoisted__U32_3837;
        Str *hoisted__Str_3838 = U32_to_str(self->cap);
        (void)hoisted__Str_3838;
        Array_set(_va_Array_116, hoisted__U32_3837, hoisted__Str_3838);
        U32 hoisted__U32_3839 = 4;
        (void)hoisted__U32_3839;
        Str hoisted__Str_3840 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3840;
        Array_set(_va_Array_116, hoisted__U32_3839, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3840; _oa; }));
        Str hoisted__Str_3841 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3841;
        panic(&hoisted__Str_3841, _va_Array_116);
        Str_delete(&hoisted__Str_3841, (Bool){0});
    }
    U32 hoisted__U64_3843 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3843;
    void *hoisted__v_3844 = ptr_add(self->data, hoisted__U64_3843);
    (void)hoisted__v_3844;
    (void)hoisted__v_3844;
    Bool hoisted__Bool_3845 = 0;
    (void)hoisted__Bool_3845;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3844, hoisted__Bool_3845);
    U32 hoisted__U64_3846 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3846;
    void *hoisted__v_3847 = ptr_add(self->data, hoisted__U64_3846);
    (void)hoisted__v_3847;
    (void)hoisted__v_3847;
    memcpy(hoisted__v_3847, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3848 = self->cap;
        (void)_re_U32_3848;
        U32 _rc_U32_3848 = 0;
        (void)_rc_U32_3848;
        Bool hoisted__Bool_3857 = U32_lte(_rc_U32_3848, _re_U32_3848);
        (void)hoisted__Bool_3857;
        if (hoisted__Bool_3857) {
            while (1) {
                Bool _wcond_Bool_3849 = U32_lt(_rc_U32_3848, _re_U32_3848);
                (void)_wcond_Bool_3849;
                if (_wcond_Bool_3849) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3848);
                U32_inc(&_rc_U32_3848);
                U32 hoisted__U64_3850 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3850;
                void *hoisted__v_3851 = ptr_add(self->data, hoisted__U64_3850);
                (void)hoisted__v_3851;
                (void)hoisted__v_3851;
                Bool hoisted__Bool_3852 = 0;
                (void)hoisted__Bool_3852;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3851, hoisted__Bool_3852);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3853 = U32_gt(_rc_U32_3848, _re_U32_3848);
                (void)_wcond_Bool_3853;
                if (_wcond_Bool_3853) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3848);
                U32_dec(&_rc_U32_3848);
                U32 hoisted__U64_3854 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3854;
                void *hoisted__v_3855 = ptr_add(self->data, hoisted__U64_3854);
                (void)hoisted__v_3855;
                (void)hoisted__v_3855;
                Bool hoisted__Bool_3856 = 0;
                (void)hoisted__Bool_3856;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3855, hoisted__Bool_3856);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3870 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3870;
    void * new_data = malloc(hoisted__U64_3870);
    {
        U32 _re_U32_3858 = self->cap;
        (void)_re_U32_3858;
        U32 _rc_U32_3858 = 0;
        (void)_rc_U32_3858;
        Bool hoisted__Bool_3869 = U32_lte(_rc_U32_3858, _re_U32_3858);
        (void)hoisted__Bool_3869;
        if (hoisted__Bool_3869) {
            while (1) {
                Bool _wcond_Bool_3859 = U32_lt(_rc_U32_3858, _re_U32_3858);
                (void)_wcond_Bool_3859;
                if (_wcond_Bool_3859) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3858);
                U32_inc(&_rc_U32_3858);
                U32 hoisted__U64_3860 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3860;
                void *hoisted__v_3861 = ptr_add(self->data, hoisted__U64_3860);
                (void)hoisted__v_3861;
                (void)hoisted__v_3861;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3861);
                U32 hoisted__U64_3862 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3862;
                void *hoisted__v_3863 = ptr_add(new_data, hoisted__U64_3862);
                (void)hoisted__v_3863;
                (void)hoisted__v_3863;
                memcpy(hoisted__v_3863, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3864 = U32_gt(_rc_U32_3858, _re_U32_3858);
                (void)_wcond_Bool_3864;
                if (_wcond_Bool_3864) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3858);
                U32_dec(&_rc_U32_3858);
                U32 hoisted__U64_3865 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3865;
                void *hoisted__v_3866 = ptr_add(self->data, hoisted__U64_3865);
                (void)hoisted__v_3866;
                (void)hoisted__v_3866;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3866);
                U32 hoisted__U64_3867 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3867;
                void *hoisted__v_3868 = ptr_add(new_data, hoisted__U64_3867);
                (void)hoisted__v_3868;
                (void)hoisted__v_3868;
                memcpy(hoisted__v_3868, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3871 = malloc(sizeof(Array));
    hoisted__Array_3871->data = new_data;
    hoisted__Array_3871->cap = self->cap;
    hoisted__Array_3871->elem_size = self->elem_size;
    hoisted__Array_3871->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3871->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3871;
    return hoisted__Array_3871;
}

U32 Array_size(void) {
    U32 hoisted__U32_3872 = 32;
    (void)hoisted__U32_3872;
    return hoisted__U32_3872;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4246 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4246;
    U32 hoisted__U32_4247 = 3;
    (void)hoisted__U32_4247;
    Array *_va_Array_148 = Array_new(hoisted__Type_4246, hoisted__U32_4247);
    (void)_va_Array_148;
    Type_delete(hoisted__Type_4246, 1);
    U32 hoisted__U32_4248 = 0;
    (void)hoisted__U32_4248;
    Str *hoisted__Str_4249 = Str_clone(loc_str);
    (void)hoisted__Str_4249;
    Array_set(_va_Array_148, hoisted__U32_4248, hoisted__Str_4249);
    U32 hoisted__U32_4250 = 1;
    (void)hoisted__U32_4250;
    Str hoisted__Str_4251 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4251;
    Array_set(_va_Array_148, hoisted__U32_4250, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4251; _oa; }));
    Array *hoisted__Array_4252 = Array_clone(parts);
    (void)hoisted__Array_4252;
    U32 hoisted__U32_4253 = 2;
    (void)hoisted__U32_4253;
    Str *hoisted__Str_4254 = format(hoisted__Array_4252);
    (void)hoisted__Str_4254;
    Array_set(_va_Array_148, hoisted__U32_4253, hoisted__Str_4254);
    Array_delete(parts, 1);
    println(_va_Array_148);
    I64 hoisted__I64_4255 = 1;
    (void)hoisted__I64_4255;
    exit(hoisted__I64_4255);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4265 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4265;
    U32 hoisted__U32_4266 = 1;
    (void)hoisted__U32_4266;
    Array *_va_Array_150 = Array_new(hoisted__Type_4265, hoisted__U32_4266);
    (void)_va_Array_150;
    Type_delete(hoisted__Type_4265, 1);
    U32 hoisted__U32_4267 = 0;
    (void)hoisted__U32_4267;
    Str hoisted__Str_4268 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4268;
    Array_set(_va_Array_150, hoisted__U32_4267, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4268; _oa; }));
    panic(loc_str, _va_Array_150);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4274 = not(cond);
    (void)hoisted__Bool_4274;
    if (hoisted__Bool_4274) {
        Type *hoisted__Type_4270 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4270;
        U32 hoisted__U32_4271 = 1;
        (void)hoisted__U32_4271;
        Array *_va_Array_151 = Array_new(hoisted__Type_4270, hoisted__U32_4271);
        (void)_va_Array_151;
        Type_delete(hoisted__Type_4270, 1);
        U32 hoisted__U32_4272 = 0;
        (void)hoisted__U32_4272;
        Str hoisted__Str_4273 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4273;
        Array_set(_va_Array_151, hoisted__U32_4272, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4273; _oa; }));
        panic(loc_str, _va_Array_151);
    }
    Bool hoisted__Bool_4275 = 1;
    (void)hoisted__Bool_4275;
    return hoisted__Bool_4275;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4298 = I64_neq(a, b);
    (void)hoisted__Bool_4298;
    if (hoisted__Bool_4298) {
        Type *hoisted__Type_4286 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4286;
        U32 hoisted__U32_4287 = 5;
        (void)hoisted__U32_4287;
        Array *_va_Array_153 = Array_new(hoisted__Type_4286, hoisted__U32_4287);
        (void)_va_Array_153;
        Type_delete(hoisted__Type_4286, 1);
        U32 hoisted__U32_4288 = 0;
        (void)hoisted__U32_4288;
        Str hoisted__Str_4289 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4289;
        Array_set(_va_Array_153, hoisted__U32_4288, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4289; _oa; }));
        U32 hoisted__U32_4290 = 1;
        (void)hoisted__U32_4290;
        Str *hoisted__Str_4291 = I64_to_str(a);
        (void)hoisted__Str_4291;
        Array_set(_va_Array_153, hoisted__U32_4290, hoisted__Str_4291);
        U32 hoisted__U32_4292 = 2;
        (void)hoisted__U32_4292;
        Str hoisted__Str_4293 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4293;
        Array_set(_va_Array_153, hoisted__U32_4292, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4293; _oa; }));
        U32 hoisted__U32_4294 = 3;
        (void)hoisted__U32_4294;
        Str *hoisted__Str_4295 = I64_to_str(b);
        (void)hoisted__Str_4295;
        Array_set(_va_Array_153, hoisted__U32_4294, hoisted__Str_4295);
        U32 hoisted__U32_4296 = 4;
        (void)hoisted__U32_4296;
        Str hoisted__Str_4297 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4297;
        Array_set(_va_Array_153, hoisted__U32_4296, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4297; _oa; }));
        panic(loc_str, _va_Array_153);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4312 = Str_eq(a, b);
    (void)hoisted__Bool_4312;
    Bool hoisted__Bool_4313 = not(hoisted__Bool_4312);
    (void)hoisted__Bool_4313;
    if (hoisted__Bool_4313) {
        Type *hoisted__Type_4300 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4300;
        U32 hoisted__U32_4301 = 5;
        (void)hoisted__U32_4301;
        Array *_va_Array_154 = Array_new(hoisted__Type_4300, hoisted__U32_4301);
        (void)_va_Array_154;
        Type_delete(hoisted__Type_4300, 1);
        U32 hoisted__U32_4302 = 0;
        (void)hoisted__U32_4302;
        Str hoisted__Str_4303 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4303;
        Array_set(_va_Array_154, hoisted__U32_4302, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4303; _oa; }));
        U32 hoisted__U32_4304 = 1;
        (void)hoisted__U32_4304;
        Str *hoisted__Str_4305 = Str_clone(a);
        (void)hoisted__Str_4305;
        Array_set(_va_Array_154, hoisted__U32_4304, hoisted__Str_4305);
        U32 hoisted__U32_4306 = 2;
        (void)hoisted__U32_4306;
        Str hoisted__Str_4307 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4307;
        Array_set(_va_Array_154, hoisted__U32_4306, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4307; _oa; }));
        U32 hoisted__U32_4308 = 3;
        (void)hoisted__U32_4308;
        Str *hoisted__Str_4309 = Str_clone(b);
        (void)hoisted__Str_4309;
        Array_set(_va_Array_154, hoisted__U32_4308, hoisted__Str_4309);
        U32 hoisted__U32_4310 = 4;
        (void)hoisted__U32_4310;
        Str hoisted__Str_4311 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4311;
        Array_set(_va_Array_154, hoisted__U32_4310, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4311; _oa; }));
        panic(loc_str, _va_Array_154);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4314 = parts;
        (void)_fc_Array_4314;
        (void)_fc_Array_4314;
        U32 _fi_USize_4314 = 0;
        (void)_fi_USize_4314;
        I64 _forin_err_kind_4314 = 0;
        (void)_forin_err_kind_4314;
        OutOfBounds *_forin_OutOfBounds_4314 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4314->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4314;
        while (1) {
            U32 hoisted__U32_4322 = Array_len(_fc_Array_4314);
            (void)hoisted__U32_4322;
            Bool _wcond_Bool_4315 = U32_lt(_fi_USize_4314, hoisted__U32_4322);
            (void)_wcond_Bool_4315;
            if (_wcond_Bool_4315) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4314, &_fi_USize_4314, &_forin_err_kind_4314, _forin_OutOfBounds_4314);
            I64 hoisted__I64_4323 = 0;
            (void)hoisted__I64_4323;
            Bool hoisted__Bool_4324 = I64_eq(_forin_err_kind_4314, hoisted__I64_4323);
            (void)hoisted__Bool_4324;
            Bool hoisted__Bool_4325 = not(hoisted__Bool_4324);
            (void)hoisted__Bool_4325;
            if (hoisted__Bool_4325) {
                Type *hoisted__Type_4317 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4317;
                U32 hoisted__U32_4318 = 1;
                (void)hoisted__U32_4318;
                Array *_va_Array_155 = Array_new(hoisted__Type_4317, hoisted__U32_4318);
                (void)_va_Array_155;
                Type_delete(hoisted__Type_4317, 1);
                U32 hoisted__U32_4319 = 0;
                (void)hoisted__U32_4319;
                Str hoisted__Str_4320 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4320;
                Array_set(_va_Array_155, hoisted__U32_4319, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4320; _oa; }));
                Str hoisted__Str_4321 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4321;
                panic(&hoisted__Str_4321, _va_Array_155);
                Str_delete(&hoisted__Str_4321, (Bool){0});
            }
            U32 hoisted__U32_4326 = 1;
            (void)hoisted__U32_4326;
            U32 hoisted__U32_4327 = U32_add(_fi_USize_4314, hoisted__U32_4326);
            (void)hoisted__U32_4327;
            _fi_USize_4314 = hoisted__U32_4327;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4314, 1);
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
    Str hoisted__Str_4634 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4634;
    I64 hoisted__I64_4635 = 3;
    (void)hoisted__I64_4635;
    assert_eq(&hoisted__Str_4634, result, hoisted__I64_4635);
    Str_delete(&hoisted__Str_4634, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4642 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4642;
    I64 hoisted__I64_4643 = 15;
    (void)hoisted__I64_4643;
    assert_eq(&hoisted__Str_4642, result, hoisted__I64_4643);
    Str_delete(&hoisted__Str_4642, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4650 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4650;
    I64 hoisted__I64_4651 = 26;
    (void)hoisted__I64_4651;
    assert_eq(&hoisted__Str_4650, result, hoisted__I64_4651);
    Str_delete(&hoisted__Str_4650, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4654 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4654;
    Str hoisted__Str_4655 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4655;
    assert_eq_str(&hoisted__Str_4654, &result, &hoisted__Str_4655);
    Str_delete(&hoisted__Str_4654, (Bool){0});
    Str_delete(&hoisted__Str_4655, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4986 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4986;
    assert_eq_str(&hoisted__Str_4986, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4986, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4987 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4987;
    assert_eq_str(&hoisted__Str_4987, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4987, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4989 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4989;
    I64 hoisted__I64_4990 = 8;
    (void)hoisted__I64_4990;
    assert_eq(&hoisted__Str_4989, result, hoisted__I64_4990);
    Str_delete(&hoisted__Str_4989, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4993 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4993;
    Bool hoisted__Bool_4994 = 1;
    (void)hoisted__Bool_4994;
    assert(&hoisted__Str_4993, hoisted__Bool_4994);
    Str_delete(&hoisted__Str_4993, (Bool){0});
    Str hoisted__Str_4997 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4997;
    Bool hoisted__Bool_4998 = 1;
    (void)hoisted__Bool_4998;
    assert(&hoisted__Str_4997, hoisted__Bool_4998);
    Str_delete(&hoisted__Str_4997, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_5003 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5003;
    Str hoisted__Str_5004 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5004;
    Str hoisted__Str_5005 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5005;
    assert_eq_str(&hoisted__Str_5003, &hoisted__Str_5004, &hoisted__Str_5005);
    Str_delete(&hoisted__Str_5003, (Bool){0});
    Str_delete(&hoisted__Str_5004, (Bool){0});
    Str_delete(&hoisted__Str_5005, (Bool){0});
    Str hoisted__Str_5008 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5008;
    Str hoisted__Str_5009 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5009;
    Str hoisted__Str_5010 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5010;
    assert_eq_str(&hoisted__Str_5008, &hoisted__Str_5009, &hoisted__Str_5010);
    Str_delete(&hoisted__Str_5008, (Bool){0});
    Str_delete(&hoisted__Str_5009, (Bool){0});
    Str_delete(&hoisted__Str_5010, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_5015 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_5015;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_5015;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_5016 = 0;
    (void)hoisted__U32_5016;
    U64 hoisted__U64_5017 = ((U64 (*)(CfVec2 *, U32))(void *)hasher)(self, hoisted__U32_5016);
    (void)hoisted__U64_5017;
    return hoisted__U64_5017;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_5018 = 16;
    (void)hoisted__U32_5018;
    return hoisted__U32_5018;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_5019 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5019;
    I64 hoisted__I64_5020 = 42;
    (void)hoisted__I64_5020;
    assert_eq(&hoisted__Str_5019, v.x, hoisted__I64_5020);
    Str_delete(&hoisted__Str_5019, (Bool){0});
    Str hoisted__Str_5021 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5021;
    I64 hoisted__I64_5022 = 99;
    (void)hoisted__I64_5022;
    assert_eq(&hoisted__Str_5021, v.y, hoisted__I64_5022);
    Str_delete(&hoisted__Str_5021, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_5025 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5025;
    I64 hoisted__I64_5026 = 10;
    (void)hoisted__I64_5026;
    assert_eq(&hoisted__Str_5025, p.x, hoisted__I64_5026);
    Str_delete(&hoisted__Str_5025, (Bool){0});
    Str hoisted__Str_5027 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5027;
    I64 hoisted__I64_5028 = 20;
    (void)hoisted__I64_5028;
    assert_eq(&hoisted__Str_5027, p.y, hoisted__I64_5028);
    Str_delete(&hoisted__Str_5027, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_5034 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_5034;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_5034;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_5035 = 0;
    (void)hoisted__U32_5035;
    U64 hoisted__U64_5036 = ((U64 (*)(CfRect *, U32))(void *)hasher)(self, hoisted__U32_5035);
    (void)hoisted__U64_5036;
    return hoisted__U64_5036;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_5037 = 32;
    (void)hoisted__U32_5037;
    return hoisted__U32_5037;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_5038 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5038;
    I64 hoisted__I64_5039 = 5;
    (void)hoisted__I64_5039;
    assert_eq(&hoisted__Str_5038, r.top_left.x, hoisted__I64_5039);
    Str_delete(&hoisted__Str_5038, (Bool){0});
    Str hoisted__Str_5040 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5040;
    I64 hoisted__I64_5041 = 10;
    (void)hoisted__I64_5041;
    assert_eq(&hoisted__Str_5040, r.top_left.y, hoisted__I64_5041);
    Str_delete(&hoisted__Str_5040, (Bool){0});
    Str hoisted__Str_5042 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5042;
    I64 hoisted__I64_5043 = 100;
    (void)hoisted__I64_5043;
    assert_eq(&hoisted__Str_5042, r.bottom_right.x, hoisted__I64_5043);
    Str_delete(&hoisted__Str_5042, (Bool){0});
    Str hoisted__Str_5044 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5044;
    I64 hoisted__I64_5045 = 200;
    (void)hoisted__I64_5045;
    assert_eq(&hoisted__Str_5044, r.bottom_right.y, hoisted__I64_5045);
    Str_delete(&hoisted__Str_5044, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_5047 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_5047;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_5047;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_5048 = 0;
    (void)hoisted__U32_5048;
    U64 hoisted__U64_5049 = ((U64 (*)(CfVec3f *, U32))(void *)hasher)(self, hoisted__U32_5048);
    (void)hoisted__U64_5049;
    return hoisted__U64_5049;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_5050 = 12;
    (void)hoisted__U32_5050;
    return hoisted__U32_5050;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str hoisted__Str_5054 = (Str){.c_str = (void *)"test/constfold.til:185:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5054;
    Str *hoisted__Str_5055 = F32_to_str(v.x);
    (void)hoisted__Str_5055;
    Str hoisted__Str_5056 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5056;
    assert_eq_str(&hoisted__Str_5054, hoisted__Str_5055, &hoisted__Str_5056);
    Str_delete(&hoisted__Str_5054, (Bool){0});
    Str_delete(hoisted__Str_5055, 1);
    Str_delete(&hoisted__Str_5056, (Bool){0});
    Str hoisted__Str_5057 = (Str){.c_str = (void *)"test/constfold.til:186:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5057;
    Str *hoisted__Str_5058 = F32_to_str(v.y);
    (void)hoisted__Str_5058;
    Str hoisted__Str_5059 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5059;
    assert_eq_str(&hoisted__Str_5057, hoisted__Str_5058, &hoisted__Str_5059);
    Str_delete(&hoisted__Str_5057, (Bool){0});
    Str_delete(hoisted__Str_5058, 1);
    Str_delete(&hoisted__Str_5059, (Bool){0});
    Str hoisted__Str_5060 = (Str){.c_str = (void *)"test/constfold.til:187:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5060;
    Str *hoisted__Str_5061 = F32_to_str(v.z);
    (void)hoisted__Str_5061;
    Str hoisted__Str_5062 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5062;
    assert_eq_str(&hoisted__Str_5060, hoisted__Str_5061, &hoisted__Str_5062);
    Str_delete(&hoisted__Str_5060, (Bool){0});
    Str_delete(hoisted__Str_5061, 1);
    Str_delete(&hoisted__Str_5062, (Bool){0});
    CfVec3f_delete(&v, (Bool){0});
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
    Bool hoisted__Bool_5067 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5067;
    if (hoisted__Bool_5067) {
        Bool hoisted__Bool_5064 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_5064;
        { Bool _ret_val = hoisted__Bool_5064;
                return _ret_val; }
    }
    Bool hoisted__Bool_5068 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5068;
    if (hoisted__Bool_5068) {
        Bool hoisted__Bool_5065 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_5065;
        { Bool _ret_val = hoisted__Bool_5065;
                return _ret_val; }
    }
    Bool hoisted__Bool_5069 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_5069;
    if (hoisted__Bool_5069) {
        Bool hoisted__Bool_5066 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_5066;
        { Bool _ret_val = hoisted__Bool_5066;
                return _ret_val; }
    }
    Bool hoisted__Bool_5070 = 0;
    (void)hoisted__Bool_5070;
    return hoisted__Bool_5070;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_5078 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5078;
    if (hoisted__Bool_5078) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_5079 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5079;
    if (hoisted__Bool_5079) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_5080 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_5080;
    if (hoisted__Bool_5080) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_5081 = (Str){.c_str = (void *)"Color.clone:192:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5081;
    UNREACHABLE(&hoisted__Str_5081);
    Str_delete(&hoisted__Str_5081, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_5082 = 4;
    (void)hoisted__U32_5082;
    return hoisted__U32_5082;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_5083 = (Str){.c_str = (void *)"test/constfold.til:197:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5083;
    Bool hoisted__Bool_5084 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5084;
    assert(&hoisted__Str_5083, hoisted__Bool_5084);
    Str_delete(&hoisted__Str_5083, (Bool){0});
    Bool hoisted__Bool_5085 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5085;
    Str hoisted__Str_5086 = (Str){.c_str = (void *)"test/constfold.til:198:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5086;
    Bool hoisted__Bool_5087 = not(hoisted__Bool_5085);
    (void)hoisted__Bool_5087;
    assert(&hoisted__Str_5086, hoisted__Bool_5087);
    Str_delete(&hoisted__Str_5086, (Bool){0});
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
    Bool hoisted__Bool_5088 = is(self, other);
    (void)hoisted__Bool_5088;
    return hoisted__Bool_5088;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_5106 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5106;
    if (hoisted__Bool_5106) {
        I64 *hoisted__I64_5102 = get_payload(self);
        (void)hoisted__I64_5102;
        (void)hoisted__I64_5102;
        Bool hoisted__Bool_5103 = 0;
        (void)hoisted__Bool_5103;
        I64_delete(hoisted__I64_5102, hoisted__Bool_5103);
    }
    Bool hoisted__Bool_5107 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5107;
    if (hoisted__Bool_5107) {
        Str *hoisted__Str_5104 = get_payload(self);
        (void)hoisted__Str_5104;
        (void)hoisted__Str_5104;
        Bool hoisted__Bool_5105 = 0;
        (void)hoisted__Bool_5105;
        Str_delete(hoisted__Str_5104, hoisted__Bool_5105);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_5136 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5136;
    if (hoisted__Bool_5136) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_5133 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_5133;
        { Token * _ret_val = hoisted__Token_5133;
                return _ret_val; }
    }
    Bool hoisted__Bool_5137 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5137;
    if (hoisted__Bool_5137) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_5134 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_5134;
        Token *hoisted__Token_5135 = Token_Name(hoisted__Str_5134);
        (void)hoisted__Token_5135;
        { Token * _ret_val = hoisted__Token_5135;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_5138 = 24;
    (void)hoisted__U32_5138;
    return hoisted__U32_5138;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_5140 = (Str){.c_str = (void *)"test/constfold.til:206:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5140;
    Bool hoisted__Bool_5141 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5141;
    assert(&hoisted__Str_5140, hoisted__Bool_5141);
    Str_delete(&hoisted__Str_5140, (Bool){0});
    Bool hoisted__Bool_5142 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5142;
    Str hoisted__Str_5143 = (Str){.c_str = (void *)"test/constfold.til:207:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5143;
    Bool hoisted__Bool_5144 = not(hoisted__Bool_5142);
    (void)hoisted__Bool_5144;
    assert(&hoisted__Str_5143, hoisted__Bool_5144);
    Str_delete(&hoisted__Str_5143, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_5145 = (Str){.c_str = (void *)"test/constfold.til:216:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5145;
    Bool hoisted__Bool_5146 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5146;
    assert(&hoisted__Str_5145, hoisted__Bool_5146);
    Str_delete(&hoisted__Str_5145, (Bool){0});
    Bool hoisted__Bool_5147 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5147;
    Str hoisted__Str_5148 = (Str){.c_str = (void *)"test/constfold.til:217:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5148;
    Bool hoisted__Bool_5149 = not(hoisted__Bool_5147);
    (void)hoisted__Bool_5149;
    assert(&hoisted__Str_5148, hoisted__Bool_5149);
    Str_delete(&hoisted__Str_5148, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_5152 = (Str){.c_str = (void *)"test/constfold.til:228:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5152;
    Bool hoisted__Bool_5153 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5153;
    assert(&hoisted__Str_5152, hoisted__Bool_5153);
    Str_delete(&hoisted__Str_5152, (Bool){0});
    Bool hoisted__Bool_5154 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5154;
    Str hoisted__Str_5155 = (Str){.c_str = (void *)"test/constfold.til:229:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5155;
    Bool hoisted__Bool_5156 = not(hoisted__Bool_5154);
    (void)hoisted__Bool_5156;
    assert(&hoisted__Str_5155, hoisted__Bool_5156);
    Str_delete(&hoisted__Str_5155, (Bool){0});
    Token_delete(t, 1);
}

void *F32_to_str_dyn(void *_a0) {
    return (void *)F32_to_str(*(F32 *)_a0);
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
void CfVec3f_delete_dyn(void *_a0, Bool _a1) {
    CfVec3f_delete(_a0, _a1);
}
U64 CfVec3f_hash_dyn(void *_a0, void *_a1) {
    return CfVec3f_hash(_a0, _a1);
}
U32 CfVec3f_size_dyn(void) {
    return CfVec3f_size();
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)F32_to_str_dyn;
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
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "FuncPtrSig", 10ULL) == 0) return (void*)Type_FuncPtrSig;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)CfVec3f_clone;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)CfVec3f_delete_dyn;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)CfVec3f_hash_dyn;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)CfVec3f_size_dyn;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) return sizeof(CfVec3f);
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        return 3LL;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"x", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"y", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"z", .count = 1ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return 1;
        if (*index == 1LL) return 1;
        if (*index == 2LL) return 1;
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
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0) {
        if (*index == 0LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 1LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
        if (*index == 2LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        return 12LL;
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
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"FuncPtrSig", .count = 10ULL, .cap = TIL_CAP_LIT}; _lit; });
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
        if (*index == 11LL) return 1;
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
        if (*index == 11LL) return ({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; });
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
    case Type_TAG_FuncPtrSig: return Str_clone(&type->data.FuncPtrSig);
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
    test_struct_fold_f32();
    fprintf(stderr, "  pass: %s\n", "test_struct_fold_f32");
    test_enum_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_fold");
    test_enum_payload_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_payload_fold");
    test_enum_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_return_fold");
    test_enum_payload_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_payload_return_fold");
    fprintf(stderr, "16/16 tests passed\n");
    return 0;
}
