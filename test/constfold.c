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
    U32 hoisted__U32_1284 = 16;
    (void)hoisted__U32_1284;
    return hoisted__U32_1284;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1285 = Str_cmp(a, b);
    (void)hoisted__I64_1285;
    I64 hoisted__I64_1286 = 0;
    (void)hoisted__I64_1286;
    Bool hoisted__Bool_1287 = I64_eq(hoisted__I64_1285, hoisted__I64_1286);
    (void)hoisted__Bool_1287;
    return hoisted__Bool_1287;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1385 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1385->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1385;
    return hoisted__OutOfBounds_1385;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1386 = 0;
    (void)hoisted__Bool_1386;
    Str_delete(&self->msg, hoisted__Bool_1386);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1387 = 0;
    (void)hoisted__U32_1387;
    U64 hoisted__U64_1388 = ((U64 (*)(OutOfBounds *, U32))(void *)hasher)(self, hoisted__U32_1387);
    (void)hoisted__U64_1388;
    return hoisted__U64_1388;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1389 = 16;
    (void)hoisted__U32_1389;
    return hoisted__U32_1389;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1397 = 8;
    (void)hoisted__U32_1397;
    return hoisted__U32_1397;
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1602 = 0;
    (void)hoisted__I64_1602;
    Bool hoisted__Bool_1603 = I64_eq(val, hoisted__I64_1602);
    (void)hoisted__Bool_1603;
    if (hoisted__Bool_1603) {
        U64 hoisted__U64_1566 = 2ULL;
        (void)hoisted__U64_1566;
        void * buf = malloc(hoisted__U64_1566);
        I64 hoisted__I64_1567 = 48;
        (void)hoisted__I64_1567;
        U64 hoisted__U64_1568 = 1ULL;
        (void)hoisted__U64_1568;
        memcpy(buf, &hoisted__I64_1567, hoisted__U64_1568);
        U64 hoisted__U64_1569 = 1ULL;
        (void)hoisted__U64_1569;
        void *hoisted__v_1570 = ptr_add(buf, hoisted__U64_1569);
        (void)hoisted__v_1570;
        (void)hoisted__v_1570;
        I32 hoisted__I32_1571 = 0;
        (void)hoisted__I32_1571;
        U64 hoisted__U64_1572 = 1ULL;
        (void)hoisted__U64_1572;
        memset(hoisted__v_1570, hoisted__I32_1571, hoisted__U64_1572);
        I64 hoisted__I64_1573 = 1;
        (void)hoisted__I64_1573;
        I64 hoisted__I64_1574 = 1;
        (void)hoisted__I64_1574;
        Str *hoisted__Str_1575 = malloc(sizeof(Str));
        hoisted__Str_1575->c_str = buf;
        hoisted__Str_1575->count = hoisted__I64_1573;
        hoisted__Str_1575->cap = hoisted__I64_1574;
        (void)hoisted__Str_1575;
        { Str * _ret_val = hoisted__Str_1575;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1604 = 0;
    (void)hoisted__I64_1604;
    Bool hoisted__Bool_1605 = I64_lt(val, hoisted__I64_1604);
    (void)hoisted__Bool_1605;
    if (hoisted__Bool_1605) {
        Bool hoisted__Bool_1576 = 1;
        (void)hoisted__Bool_1576;
        is_neg = hoisted__Bool_1576;
        I64 hoisted__I64_1577 = 0;
        (void)hoisted__I64_1577;
        I64 hoisted__I64_1578 = I64_sub(hoisted__I64_1577, val);
        (void)hoisted__I64_1578;
        v = hoisted__I64_1578;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1580 = 0;
        (void)hoisted__I64_1580;
        Bool _wcond_Bool_1579 = I64_gt(tmp, hoisted__I64_1580);
        (void)_wcond_Bool_1579;
        if (_wcond_Bool_1579) {
        } else {
            break;
        }
        U64 hoisted__U64_1581 = 1ULL;
        (void)hoisted__U64_1581;
        U64 hoisted__U64_1582 = U64_add(ndigits, hoisted__U64_1581);
        (void)hoisted__U64_1582;
        ndigits = hoisted__U64_1582;
        I64 hoisted__I64_1583 = 10;
        (void)hoisted__I64_1583;
        I64 hoisted__I64_1584 = I64_div(tmp, hoisted__I64_1583);
        (void)hoisted__I64_1584;
        tmp = hoisted__I64_1584;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1585 = 1ULL;
        (void)hoisted__U64_1585;
        U64 hoisted__U64_1586 = U64_add(total, hoisted__U64_1585);
        (void)hoisted__U64_1586;
        total = hoisted__U64_1586;
    }
    U64 hoisted__U64_1606 = 1ULL;
    (void)hoisted__U64_1606;
    U64 hoisted__U64_1607 = U64_add(total, hoisted__U64_1606);
    (void)hoisted__U64_1607;
    void * buf = malloc(hoisted__U64_1607);
    if (is_neg) {
        I64 hoisted__I64_1587 = 45;
        (void)hoisted__I64_1587;
        U64 hoisted__U64_1588 = 1ULL;
        (void)hoisted__U64_1588;
        memcpy(buf, &hoisted__I64_1587, hoisted__U64_1588);
    }
    U64 hoisted__U64_1608 = 1ULL;
    (void)hoisted__U64_1608;
    U64 i = U64_sub(total, hoisted__U64_1608);
    while (1) {
        I64 hoisted__I64_1590 = 0;
        (void)hoisted__I64_1590;
        Bool _wcond_Bool_1589 = I64_gt(v, hoisted__I64_1590);
        (void)_wcond_Bool_1589;
        if (_wcond_Bool_1589) {
        } else {
            break;
        }
        I64 hoisted__I64_1591 = 10;
        (void)hoisted__I64_1591;
        I64 hoisted__I64_1592 = I64_mod(v, hoisted__I64_1591);
        (void)hoisted__I64_1592;
        I64 hoisted__I64_1593 = 48;
        (void)hoisted__I64_1593;
        I64 hoisted__I64_1594 = I64_add(hoisted__I64_1592, hoisted__I64_1593);
        (void)hoisted__I64_1594;
        void *hoisted__v_1595 = ptr_add(buf, i);
        (void)hoisted__v_1595;
        (void)hoisted__v_1595;
        U8 hoisted__U8_1596 = I64_to_u8(hoisted__I64_1594);
        (void)hoisted__U8_1596;
        U64 hoisted__U64_1597 = 1ULL;
        (void)hoisted__U64_1597;
        memcpy(hoisted__v_1595, &hoisted__U8_1596, hoisted__U64_1597);
        I64 hoisted__I64_1598 = 10;
        (void)hoisted__I64_1598;
        I64 hoisted__I64_1599 = I64_div(v, hoisted__I64_1598);
        (void)hoisted__I64_1599;
        v = hoisted__I64_1599;
        U64 hoisted__U64_1600 = 1ULL;
        (void)hoisted__U64_1600;
        U64 hoisted__U64_1601 = U64_sub(i, hoisted__U64_1600);
        (void)hoisted__U64_1601;
        i = hoisted__U64_1601;
    }
    void *hoisted__v_1609 = ptr_add(buf, total);
    (void)hoisted__v_1609;
    (void)hoisted__v_1609;
    I32 hoisted__I32_1610 = 0;
    (void)hoisted__I32_1610;
    U64 hoisted__U64_1611 = 1ULL;
    (void)hoisted__U64_1611;
    memset(hoisted__v_1609, hoisted__I32_1610, hoisted__U64_1611);
    Str *hoisted__Str_1612 = malloc(sizeof(Str));
    hoisted__Str_1612->c_str = buf;
    hoisted__Str_1612->count = total;
    hoisted__Str_1612->cap = total;
    (void)hoisted__Str_1612;
    return hoisted__Str_1612;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1632 = 8;
    (void)hoisted__U32_1632;
    return hoisted__U32_1632;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1763 = 0;
    (void)hoisted__U32_1763;
    U64 hoisted__U64_1764 = ((U64 (*)(I64 *, U32))(void *)hasher)(&self, hoisted__U32_1763);
    (void)hoisted__U64_1764;
    return hoisted__U64_1764;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1767 = I64_cmp(a, b);
    (void)hoisted__I64_1767;
    I64 hoisted__I64_1768 = -1;
    (void)hoisted__I64_1768;
    Bool hoisted__Bool_1769 = I64_eq(hoisted__I64_1767, hoisted__I64_1768);
    (void)hoisted__Bool_1769;
    return hoisted__Bool_1769;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1770 = I64_cmp(a, b);
    (void)hoisted__I64_1770;
    I64 hoisted__I64_1771 = 1;
    (void)hoisted__I64_1771;
    Bool hoisted__Bool_1772 = I64_eq(hoisted__I64_1770, hoisted__I64_1771);
    (void)hoisted__Bool_1772;
    return hoisted__Bool_1772;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1773 = I64_eq(a, b);
    (void)hoisted__Bool_1773;
    Bool hoisted__Bool_1774 = not(hoisted__Bool_1773);
    (void)hoisted__Bool_1774;
    return hoisted__Bool_1774;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1792 = Bool_eq(a, b);
    (void)hoisted__Bool_1792;
    if (hoisted__Bool_1792) {
        I64 hoisted__I64_1790 = 0;
        (void)hoisted__I64_1790;
        { I64 _ret_val = hoisted__I64_1790;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1791 = -1;
        (void)hoisted__I64_1791;
        return hoisted__I64_1791;
    }
    I64 hoisted__I64_1793 = 1;
    (void)hoisted__I64_1793;
    return hoisted__I64_1793;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1794 = 1;
    (void)hoisted__U32_1794;
    return hoisted__U32_1794;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1795 = 0;
    (void)hoisted__U32_1795;
    U64 hoisted__U64_1796 = ((U64 (*)(Bool *, U32))(void *)hasher)(&self, hoisted__U32_1795);
    (void)hoisted__U64_1796;
    return hoisted__U64_1796;
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
    Bool hoisted__Bool_1950 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1950;
    if (hoisted__Bool_1950) {
        Bool hoisted__Bool_1940 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1940;
        { Bool _ret_val = hoisted__Bool_1940;
                return _ret_val; }
    }
    Bool hoisted__Bool_1951 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1951;
    if (hoisted__Bool_1951) {
        Bool hoisted__Bool_1941 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1941;
        { Bool _ret_val = hoisted__Bool_1941;
                return _ret_val; }
    }
    Bool hoisted__Bool_1952 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1952;
    if (hoisted__Bool_1952) {
        Bool hoisted__Bool_1942 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_1942;
        { Bool _ret_val = hoisted__Bool_1942;
                return _ret_val; }
    }
    Bool hoisted__Bool_1953 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1953;
    if (hoisted__Bool_1953) {
        Bool hoisted__Bool_1943 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_1943;
        { Bool _ret_val = hoisted__Bool_1943;
                return _ret_val; }
    }
    Bool hoisted__Bool_1954 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1954;
    if (hoisted__Bool_1954) {
        Bool hoisted__Bool_1944 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_1944;
        { Bool _ret_val = hoisted__Bool_1944;
                return _ret_val; }
    }
    Bool hoisted__Bool_1955 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1955;
    if (hoisted__Bool_1955) {
        Bool hoisted__Bool_1945 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_1945;
        { Bool _ret_val = hoisted__Bool_1945;
                return _ret_val; }
    }
    Bool hoisted__Bool_1956 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1956;
    if (hoisted__Bool_1956) {
        Bool hoisted__Bool_1946 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_1946;
        { Bool _ret_val = hoisted__Bool_1946;
                return _ret_val; }
    }
    Bool hoisted__Bool_1957 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1957;
    if (hoisted__Bool_1957) {
        Bool hoisted__Bool_1947 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_1947;
        { Bool _ret_val = hoisted__Bool_1947;
                return _ret_val; }
    }
    Bool hoisted__Bool_1958 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1958;
    if (hoisted__Bool_1958) {
        Bool hoisted__Bool_1948 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_1948;
        { Bool _ret_val = hoisted__Bool_1948;
                return _ret_val; }
    }
    Bool hoisted__Bool_1959 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1959;
    if (hoisted__Bool_1959) {
        Bool hoisted__Bool_1949 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_1949;
        { Bool _ret_val = hoisted__Bool_1949;
                return _ret_val; }
    }
    Bool hoisted__Bool_1960 = 0;
    (void)hoisted__Bool_1960;
    return hoisted__Bool_1960;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1982 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1982;
    if (hoisted__Bool_1982) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1983 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1983;
    if (hoisted__Bool_1983) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_1984 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1984;
    if (hoisted__Bool_1984) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_1985 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1985;
    if (hoisted__Bool_1985) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1986 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1986;
    if (hoisted__Bool_1986) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1987 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1987;
    if (hoisted__Bool_1987) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1988 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1988;
    if (hoisted__Bool_1988) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1989 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1989;
    if (hoisted__Bool_1989) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1990 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1990;
    if (hoisted__Bool_1990) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1991 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1991;
    if (hoisted__Bool_1991) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_1992 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1992;
    UNREACHABLE(&hoisted__Str_1992);
    Str_delete(&hoisted__Str_1992, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1993 = 4;
    (void)hoisted__U32_1993;
    return hoisted__U32_1993;
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
    Bool hoisted__Bool_2045 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2045;
    if (hoisted__Bool_2045) {
        Str *hoisted__Str_2035 = get_payload(self);
        (void)hoisted__Str_2035;
        (void)hoisted__Str_2035;
        Bool hoisted__Bool_2036 = 0;
        (void)hoisted__Bool_2036;
        Str_delete(hoisted__Str_2035, hoisted__Bool_2036);
    }
    Bool hoisted__Bool_2046 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2046;
    if (hoisted__Bool_2046) {
        Str *hoisted__Str_2037 = get_payload(self);
        (void)hoisted__Str_2037;
        (void)hoisted__Str_2037;
        Bool hoisted__Bool_2038 = 0;
        (void)hoisted__Bool_2038;
        Str_delete(hoisted__Str_2037, hoisted__Bool_2038);
    }
    Bool hoisted__Bool_2047 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2047;
    if (hoisted__Bool_2047) {
        Str *hoisted__Str_2039 = get_payload(self);
        (void)hoisted__Str_2039;
        (void)hoisted__Str_2039;
        Bool hoisted__Bool_2040 = 0;
        (void)hoisted__Bool_2040;
        Str_delete(hoisted__Str_2039, hoisted__Bool_2040);
    }
    Bool hoisted__Bool_2048 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2048;
    if (hoisted__Bool_2048) {
        Primitive *hoisted__Primitive_2041 = get_payload(self);
        (void)hoisted__Primitive_2041;
        (void)hoisted__Primitive_2041;
        Bool hoisted__Bool_2042 = 0;
        (void)hoisted__Bool_2042;
        Primitive_delete(hoisted__Primitive_2041, hoisted__Bool_2042);
    }
    Bool hoisted__Bool_2049 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2049;
    if (hoisted__Bool_2049) {
        Str *hoisted__Str_2043 = get_payload(self);
        (void)hoisted__Str_2043;
        (void)hoisted__Str_2043;
        Bool hoisted__Bool_2044 = 0;
        (void)hoisted__Bool_2044;
        Str_delete(hoisted__Str_2043, hoisted__Bool_2044);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2128 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2128;
    if (hoisted__Bool_2128) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2129 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2129;
    if (hoisted__Bool_2129) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2130 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2130;
    if (hoisted__Bool_2130) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2120 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2120;
        Type *hoisted__Type_2121 = Type_Struct(hoisted__Str_2120);
        (void)hoisted__Type_2121;
        { Type * _ret_val = hoisted__Type_2121;
                return _ret_val; }
    }
    Bool hoisted__Bool_2131 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2131;
    if (hoisted__Bool_2131) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2132 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2132;
    if (hoisted__Bool_2132) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2122 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2122;
        Type *hoisted__Type_2123 = Type_Enum(hoisted__Str_2122);
        (void)hoisted__Type_2123;
        { Type * _ret_val = hoisted__Type_2123;
                return _ret_val; }
    }
    Bool hoisted__Bool_2133 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2133;
    if (hoisted__Bool_2133) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2134 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2134;
    if (hoisted__Bool_2134) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2135 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2135;
    if (hoisted__Bool_2135) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2136 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2136;
    if (hoisted__Bool_2136) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2137 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2137;
    if (hoisted__Bool_2137) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2124 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2124;
        Type *hoisted__Type_2125 = Type_Custom(hoisted__Str_2124);
        (void)hoisted__Type_2125;
        { Type * _ret_val = hoisted__Type_2125;
                return _ret_val; }
    }
    Bool hoisted__Bool_2138 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2138;
    if (hoisted__Bool_2138) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2126 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2126;
        Type *hoisted__Type_2127 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2126; _oa; }));
        (void)hoisted__Type_2127;
        { Type * _ret_val = hoisted__Type_2127;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2139 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2139;
    Type *hoisted__Type_2140 = Type_FuncPtrSig(hoisted__Str_2139);
    (void)hoisted__Type_2140;
    return hoisted__Type_2140;
}

U32 Type_size(void) {
    U32 hoisted__U32_2141 = 24;
    (void)hoisted__U32_2141;
    return hoisted__U32_2141;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3808 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3808;
    if (hoisted__Bool_3808) {
        Type *hoisted__Type_3803 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3803;
        U32 hoisted__U32_3804 = 1;
        (void)hoisted__U32_3804;
        Array *_va_Array_114 = Array_new(hoisted__Type_3803, hoisted__U32_3804);
        (void)_va_Array_114;
        Type_delete(hoisted__Type_3803, 1);
        U32 hoisted__U32_3805 = 0;
        (void)hoisted__U32_3805;
        Str hoisted__Str_3806 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3806;
        Array_set(_va_Array_114, hoisted__U32_3805, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3806; _oa; }));
        Str hoisted__Str_3807 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3807;
        panic(&hoisted__Str_3807, _va_Array_114);
        Str_delete(&hoisted__Str_3807, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3809 = calloc(cap, elem_size);
    (void)hoisted__v_3809;
    void * hoisted__v_3810 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3810;
    void * hoisted__v_3811 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3811;
    Array *hoisted__Array_3812 = malloc(sizeof(Array));
    hoisted__Array_3812->data = hoisted__v_3809;
    hoisted__Array_3812->cap = cap;
    hoisted__Array_3812->elem_size = elem_size;
    hoisted__Array_3812->elem_clone = hoisted__v_3810;
    hoisted__Array_3812->elem_delete = hoisted__v_3811;
    (void)hoisted__Array_3812;
    return hoisted__Array_3812;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3813 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3813;
    Str_delete(elem_type, 1);
    return hoisted__Array_3813;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3834 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3834;
    if (hoisted__Bool_3834) {
        Type *hoisted__Type_3815 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3815;
        U32 hoisted__U32_3816 = 6;
        (void)hoisted__U32_3816;
        Array *_va_Array_115 = Array_new(hoisted__Type_3815, hoisted__U32_3816);
        (void)_va_Array_115;
        Type_delete(hoisted__Type_3815, 1);
        U32 hoisted__U32_3817 = 0;
        (void)hoisted__U32_3817;
        Str hoisted__Str_3818 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3818;
        Array_set(_va_Array_115, hoisted__U32_3817, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3818; _oa; }));
        U32 hoisted__U32_3819 = 1;
        (void)hoisted__U32_3819;
        Str hoisted__Str_3820 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3820;
        Array_set(_va_Array_115, hoisted__U32_3819, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3820; _oa; }));
        U32 hoisted__U32_3821 = 2;
        (void)hoisted__U32_3821;
        Str *hoisted__Str_3822 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3822;
        Array_set(_va_Array_115, hoisted__U32_3821, hoisted__Str_3822);
        U32 hoisted__U32_3823 = 3;
        (void)hoisted__U32_3823;
        Str hoisted__Str_3824 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3824;
        Array_set(_va_Array_115, hoisted__U32_3823, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3824; _oa; }));
        U32 hoisted__U32_3825 = 4;
        (void)hoisted__U32_3825;
        Str *hoisted__Str_3826 = U32_to_str(self->cap);
        (void)hoisted__Str_3826;
        Array_set(_va_Array_115, hoisted__U32_3825, hoisted__Str_3826);
        U32 hoisted__U32_3827 = 5;
        (void)hoisted__U32_3827;
        Str hoisted__Str_3828 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3828;
        Array_set(_va_Array_115, hoisted__U32_3827, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3828; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3829 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_115); hoisted__OutOfBounds_3829->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3829;
        U32 hoisted__U32_3830 = 16;
        (void)hoisted__U32_3830;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3829, hoisted__U32_3830);
        OutOfBounds_delete(hoisted__OutOfBounds_3829, 1);
        I64 hoisted__I64_3831 = 3;
        (void)hoisted__I64_3831;
        *_err_kind = hoisted__I64_3831;
    }
    I64 hoisted__I64_3835 = 0;
    (void)hoisted__I64_3835;
    Bool hoisted__Bool_3836 = I64_eq(DEREF(_err_kind), hoisted__I64_3835);
    (void)hoisted__Bool_3836;
    if (hoisted__Bool_3836) {
        U32 hoisted__U64_3832 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3832;
        void *hoisted__v_3833 = ptr_add(self->data, hoisted__U64_3832);
        (void)hoisted__v_3833;
        (void)hoisted__v_3833;
        { void * _ret_val = hoisted__v_3833;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3851 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3851;
    if (hoisted__Bool_3851) {
        Type *hoisted__Type_3838 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3838;
        U32 hoisted__U32_3839 = 5;
        (void)hoisted__U32_3839;
        Array *_va_Array_116 = Array_new(hoisted__Type_3838, hoisted__U32_3839);
        (void)_va_Array_116;
        Type_delete(hoisted__Type_3838, 1);
        U32 hoisted__U32_3840 = 0;
        (void)hoisted__U32_3840;
        Str hoisted__Str_3841 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3841;
        Array_set(_va_Array_116, hoisted__U32_3840, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3841; _oa; }));
        U32 hoisted__U32_3842 = 1;
        (void)hoisted__U32_3842;
        Str *hoisted__Str_3843 = U32_to_str(i);
        (void)hoisted__Str_3843;
        Array_set(_va_Array_116, hoisted__U32_3842, hoisted__Str_3843);
        U32 hoisted__U32_3844 = 2;
        (void)hoisted__U32_3844;
        Str hoisted__Str_3845 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3845;
        Array_set(_va_Array_116, hoisted__U32_3844, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3845; _oa; }));
        U32 hoisted__U32_3846 = 3;
        (void)hoisted__U32_3846;
        Str *hoisted__Str_3847 = U32_to_str(self->cap);
        (void)hoisted__Str_3847;
        Array_set(_va_Array_116, hoisted__U32_3846, hoisted__Str_3847);
        U32 hoisted__U32_3848 = 4;
        (void)hoisted__U32_3848;
        Str hoisted__Str_3849 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3849;
        Array_set(_va_Array_116, hoisted__U32_3848, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3849; _oa; }));
        Str hoisted__Str_3850 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3850;
        panic(&hoisted__Str_3850, _va_Array_116);
        Str_delete(&hoisted__Str_3850, (Bool){0});
    }
    U32 hoisted__U64_3852 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3852;
    void *hoisted__v_3853 = ptr_add(self->data, hoisted__U64_3852);
    (void)hoisted__v_3853;
    (void)hoisted__v_3853;
    Bool hoisted__Bool_3854 = 0;
    (void)hoisted__Bool_3854;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3853, hoisted__Bool_3854);
    U32 hoisted__U64_3855 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3855;
    void *hoisted__v_3856 = ptr_add(self->data, hoisted__U64_3855);
    (void)hoisted__v_3856;
    (void)hoisted__v_3856;
    memcpy(hoisted__v_3856, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3857 = self->cap;
        (void)_re_U32_3857;
        U32 _rc_U32_3857 = 0;
        (void)_rc_U32_3857;
        Bool hoisted__Bool_3866 = U32_lte(_rc_U32_3857, _re_U32_3857);
        (void)hoisted__Bool_3866;
        if (hoisted__Bool_3866) {
            while (1) {
                Bool _wcond_Bool_3858 = U32_lt(_rc_U32_3857, _re_U32_3857);
                (void)_wcond_Bool_3858;
                if (_wcond_Bool_3858) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3857);
                U32_inc(&_rc_U32_3857);
                U32 hoisted__U64_3859 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3859;
                void *hoisted__v_3860 = ptr_add(self->data, hoisted__U64_3859);
                (void)hoisted__v_3860;
                (void)hoisted__v_3860;
                Bool hoisted__Bool_3861 = 0;
                (void)hoisted__Bool_3861;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3860, hoisted__Bool_3861);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3862 = U32_gt(_rc_U32_3857, _re_U32_3857);
                (void)_wcond_Bool_3862;
                if (_wcond_Bool_3862) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3857);
                U32_dec(&_rc_U32_3857);
                U32 hoisted__U64_3863 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3863;
                void *hoisted__v_3864 = ptr_add(self->data, hoisted__U64_3863);
                (void)hoisted__v_3864;
                (void)hoisted__v_3864;
                Bool hoisted__Bool_3865 = 0;
                (void)hoisted__Bool_3865;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3864, hoisted__Bool_3865);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3879 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3879;
    void * new_data = malloc(hoisted__U64_3879);
    {
        U32 _re_U32_3867 = self->cap;
        (void)_re_U32_3867;
        U32 _rc_U32_3867 = 0;
        (void)_rc_U32_3867;
        Bool hoisted__Bool_3878 = U32_lte(_rc_U32_3867, _re_U32_3867);
        (void)hoisted__Bool_3878;
        if (hoisted__Bool_3878) {
            while (1) {
                Bool _wcond_Bool_3868 = U32_lt(_rc_U32_3867, _re_U32_3867);
                (void)_wcond_Bool_3868;
                if (_wcond_Bool_3868) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3867);
                U32_inc(&_rc_U32_3867);
                U32 hoisted__U64_3869 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3869;
                void *hoisted__v_3870 = ptr_add(self->data, hoisted__U64_3869);
                (void)hoisted__v_3870;
                (void)hoisted__v_3870;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3870);
                U32 hoisted__U64_3871 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3871;
                void *hoisted__v_3872 = ptr_add(new_data, hoisted__U64_3871);
                (void)hoisted__v_3872;
                (void)hoisted__v_3872;
                memcpy(hoisted__v_3872, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3873 = U32_gt(_rc_U32_3867, _re_U32_3867);
                (void)_wcond_Bool_3873;
                if (_wcond_Bool_3873) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3867);
                U32_dec(&_rc_U32_3867);
                U32 hoisted__U64_3874 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3874;
                void *hoisted__v_3875 = ptr_add(self->data, hoisted__U64_3874);
                (void)hoisted__v_3875;
                (void)hoisted__v_3875;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3875);
                U32 hoisted__U64_3876 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3876;
                void *hoisted__v_3877 = ptr_add(new_data, hoisted__U64_3876);
                (void)hoisted__v_3877;
                (void)hoisted__v_3877;
                memcpy(hoisted__v_3877, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3880 = malloc(sizeof(Array));
    hoisted__Array_3880->data = new_data;
    hoisted__Array_3880->cap = self->cap;
    hoisted__Array_3880->elem_size = self->elem_size;
    hoisted__Array_3880->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3880->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3880;
    return hoisted__Array_3880;
}

U32 Array_size(void) {
    U32 hoisted__U32_3881 = 32;
    (void)hoisted__U32_3881;
    return hoisted__U32_3881;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4255 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4255;
    U32 hoisted__U32_4256 = 3;
    (void)hoisted__U32_4256;
    Array *_va_Array_148 = Array_new(hoisted__Type_4255, hoisted__U32_4256);
    (void)_va_Array_148;
    Type_delete(hoisted__Type_4255, 1);
    U32 hoisted__U32_4257 = 0;
    (void)hoisted__U32_4257;
    Str *hoisted__Str_4258 = Str_clone(loc_str);
    (void)hoisted__Str_4258;
    Array_set(_va_Array_148, hoisted__U32_4257, hoisted__Str_4258);
    U32 hoisted__U32_4259 = 1;
    (void)hoisted__U32_4259;
    Str hoisted__Str_4260 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4260;
    Array_set(_va_Array_148, hoisted__U32_4259, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4260; _oa; }));
    Array *hoisted__Array_4261 = Array_clone(parts);
    (void)hoisted__Array_4261;
    U32 hoisted__U32_4262 = 2;
    (void)hoisted__U32_4262;
    Str *hoisted__Str_4263 = format(hoisted__Array_4261);
    (void)hoisted__Str_4263;
    Array_set(_va_Array_148, hoisted__U32_4262, hoisted__Str_4263);
    Array_delete(parts, 1);
    println(_va_Array_148);
    I64 hoisted__I64_4264 = 1;
    (void)hoisted__I64_4264;
    exit(hoisted__I64_4264);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4274 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4274;
    U32 hoisted__U32_4275 = 1;
    (void)hoisted__U32_4275;
    Array *_va_Array_150 = Array_new(hoisted__Type_4274, hoisted__U32_4275);
    (void)_va_Array_150;
    Type_delete(hoisted__Type_4274, 1);
    U32 hoisted__U32_4276 = 0;
    (void)hoisted__U32_4276;
    Str hoisted__Str_4277 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4277;
    Array_set(_va_Array_150, hoisted__U32_4276, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4277; _oa; }));
    panic(loc_str, _va_Array_150);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4283 = not(cond);
    (void)hoisted__Bool_4283;
    if (hoisted__Bool_4283) {
        Type *hoisted__Type_4279 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4279;
        U32 hoisted__U32_4280 = 1;
        (void)hoisted__U32_4280;
        Array *_va_Array_151 = Array_new(hoisted__Type_4279, hoisted__U32_4280);
        (void)_va_Array_151;
        Type_delete(hoisted__Type_4279, 1);
        U32 hoisted__U32_4281 = 0;
        (void)hoisted__U32_4281;
        Str hoisted__Str_4282 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4282;
        Array_set(_va_Array_151, hoisted__U32_4281, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4282; _oa; }));
        panic(loc_str, _va_Array_151);
    }
    Bool hoisted__Bool_4284 = 1;
    (void)hoisted__Bool_4284;
    return hoisted__Bool_4284;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4307 = I64_neq(a, b);
    (void)hoisted__Bool_4307;
    if (hoisted__Bool_4307) {
        Type *hoisted__Type_4295 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4295;
        U32 hoisted__U32_4296 = 5;
        (void)hoisted__U32_4296;
        Array *_va_Array_153 = Array_new(hoisted__Type_4295, hoisted__U32_4296);
        (void)_va_Array_153;
        Type_delete(hoisted__Type_4295, 1);
        U32 hoisted__U32_4297 = 0;
        (void)hoisted__U32_4297;
        Str hoisted__Str_4298 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4298;
        Array_set(_va_Array_153, hoisted__U32_4297, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4298; _oa; }));
        U32 hoisted__U32_4299 = 1;
        (void)hoisted__U32_4299;
        Str *hoisted__Str_4300 = I64_to_str(a);
        (void)hoisted__Str_4300;
        Array_set(_va_Array_153, hoisted__U32_4299, hoisted__Str_4300);
        U32 hoisted__U32_4301 = 2;
        (void)hoisted__U32_4301;
        Str hoisted__Str_4302 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4302;
        Array_set(_va_Array_153, hoisted__U32_4301, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4302; _oa; }));
        U32 hoisted__U32_4303 = 3;
        (void)hoisted__U32_4303;
        Str *hoisted__Str_4304 = I64_to_str(b);
        (void)hoisted__Str_4304;
        Array_set(_va_Array_153, hoisted__U32_4303, hoisted__Str_4304);
        U32 hoisted__U32_4305 = 4;
        (void)hoisted__U32_4305;
        Str hoisted__Str_4306 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4306;
        Array_set(_va_Array_153, hoisted__U32_4305, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4306; _oa; }));
        panic(loc_str, _va_Array_153);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4321 = Str_eq(a, b);
    (void)hoisted__Bool_4321;
    Bool hoisted__Bool_4322 = not(hoisted__Bool_4321);
    (void)hoisted__Bool_4322;
    if (hoisted__Bool_4322) {
        Type *hoisted__Type_4309 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4309;
        U32 hoisted__U32_4310 = 5;
        (void)hoisted__U32_4310;
        Array *_va_Array_154 = Array_new(hoisted__Type_4309, hoisted__U32_4310);
        (void)_va_Array_154;
        Type_delete(hoisted__Type_4309, 1);
        U32 hoisted__U32_4311 = 0;
        (void)hoisted__U32_4311;
        Str hoisted__Str_4312 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4312;
        Array_set(_va_Array_154, hoisted__U32_4311, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4312; _oa; }));
        U32 hoisted__U32_4313 = 1;
        (void)hoisted__U32_4313;
        Str *hoisted__Str_4314 = Str_clone(a);
        (void)hoisted__Str_4314;
        Array_set(_va_Array_154, hoisted__U32_4313, hoisted__Str_4314);
        U32 hoisted__U32_4315 = 2;
        (void)hoisted__U32_4315;
        Str hoisted__Str_4316 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4316;
        Array_set(_va_Array_154, hoisted__U32_4315, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4316; _oa; }));
        U32 hoisted__U32_4317 = 3;
        (void)hoisted__U32_4317;
        Str *hoisted__Str_4318 = Str_clone(b);
        (void)hoisted__Str_4318;
        Array_set(_va_Array_154, hoisted__U32_4317, hoisted__Str_4318);
        U32 hoisted__U32_4319 = 4;
        (void)hoisted__U32_4319;
        Str hoisted__Str_4320 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4320;
        Array_set(_va_Array_154, hoisted__U32_4319, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4320; _oa; }));
        panic(loc_str, _va_Array_154);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4323 = parts;
        (void)_fc_Array_4323;
        (void)_fc_Array_4323;
        U32 _fi_USize_4323 = 0;
        (void)_fi_USize_4323;
        I64 _forin_err_kind_4323 = 0;
        (void)_forin_err_kind_4323;
        OutOfBounds *_forin_OutOfBounds_4323 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4323->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4323;
        while (1) {
            U32 hoisted__U32_4331 = Array_len(_fc_Array_4323);
            (void)hoisted__U32_4331;
            Bool _wcond_Bool_4324 = U32_lt(_fi_USize_4323, hoisted__U32_4331);
            (void)_wcond_Bool_4324;
            if (_wcond_Bool_4324) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4323, &_fi_USize_4323, &_forin_err_kind_4323, _forin_OutOfBounds_4323);
            I64 hoisted__I64_4332 = 0;
            (void)hoisted__I64_4332;
            Bool hoisted__Bool_4333 = I64_eq(_forin_err_kind_4323, hoisted__I64_4332);
            (void)hoisted__Bool_4333;
            Bool hoisted__Bool_4334 = not(hoisted__Bool_4333);
            (void)hoisted__Bool_4334;
            if (hoisted__Bool_4334) {
                Type *hoisted__Type_4326 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4326;
                U32 hoisted__U32_4327 = 1;
                (void)hoisted__U32_4327;
                Array *_va_Array_155 = Array_new(hoisted__Type_4326, hoisted__U32_4327);
                (void)_va_Array_155;
                Type_delete(hoisted__Type_4326, 1);
                U32 hoisted__U32_4328 = 0;
                (void)hoisted__U32_4328;
                Str hoisted__Str_4329 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4329;
                Array_set(_va_Array_155, hoisted__U32_4328, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4329; _oa; }));
                Str hoisted__Str_4330 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4330;
                panic(&hoisted__Str_4330, _va_Array_155);
                Str_delete(&hoisted__Str_4330, (Bool){0});
            }
            U32 hoisted__U32_4335 = 1;
            (void)hoisted__U32_4335;
            U32 hoisted__U32_4336 = U32_add(_fi_USize_4323, hoisted__U32_4335);
            (void)hoisted__U32_4336;
            _fi_USize_4323 = hoisted__U32_4336;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4323, 1);
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
    Str hoisted__Str_4643 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4643;
    I64 hoisted__I64_4644 = 3;
    (void)hoisted__I64_4644;
    assert_eq(&hoisted__Str_4643, result, hoisted__I64_4644);
    Str_delete(&hoisted__Str_4643, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4651 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4651;
    I64 hoisted__I64_4652 = 15;
    (void)hoisted__I64_4652;
    assert_eq(&hoisted__Str_4651, result, hoisted__I64_4652);
    Str_delete(&hoisted__Str_4651, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4659 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4659;
    I64 hoisted__I64_4660 = 26;
    (void)hoisted__I64_4660;
    assert_eq(&hoisted__Str_4659, result, hoisted__I64_4660);
    Str_delete(&hoisted__Str_4659, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4663 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4663;
    Str hoisted__Str_4664 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4664;
    assert_eq_str(&hoisted__Str_4663, &result, &hoisted__Str_4664);
    Str_delete(&hoisted__Str_4663, (Bool){0});
    Str_delete(&hoisted__Str_4664, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4995 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4995;
    assert_eq_str(&hoisted__Str_4995, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4995, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4996 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4996;
    assert_eq_str(&hoisted__Str_4996, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4996, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4998 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4998;
    I64 hoisted__I64_4999 = 8;
    (void)hoisted__I64_4999;
    assert_eq(&hoisted__Str_4998, result, hoisted__I64_4999);
    Str_delete(&hoisted__Str_4998, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_5002 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5002;
    Bool hoisted__Bool_5003 = 1;
    (void)hoisted__Bool_5003;
    assert(&hoisted__Str_5002, hoisted__Bool_5003);
    Str_delete(&hoisted__Str_5002, (Bool){0});
    Str hoisted__Str_5006 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5006;
    Bool hoisted__Bool_5007 = 1;
    (void)hoisted__Bool_5007;
    assert(&hoisted__Str_5006, hoisted__Bool_5007);
    Str_delete(&hoisted__Str_5006, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_5012 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5012;
    Str hoisted__Str_5013 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5013;
    Str hoisted__Str_5014 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5014;
    assert_eq_str(&hoisted__Str_5012, &hoisted__Str_5013, &hoisted__Str_5014);
    Str_delete(&hoisted__Str_5012, (Bool){0});
    Str_delete(&hoisted__Str_5013, (Bool){0});
    Str_delete(&hoisted__Str_5014, (Bool){0});
    Str hoisted__Str_5017 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5017;
    Str hoisted__Str_5018 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5018;
    Str hoisted__Str_5019 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5019;
    assert_eq_str(&hoisted__Str_5017, &hoisted__Str_5018, &hoisted__Str_5019);
    Str_delete(&hoisted__Str_5017, (Bool){0});
    Str_delete(&hoisted__Str_5018, (Bool){0});
    Str_delete(&hoisted__Str_5019, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_5024 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_5024;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_5024;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_5025 = 0;
    (void)hoisted__U32_5025;
    U64 hoisted__U64_5026 = ((U64 (*)(CfVec2 *, U32))(void *)hasher)(self, hoisted__U32_5025);
    (void)hoisted__U64_5026;
    return hoisted__U64_5026;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_5027 = 16;
    (void)hoisted__U32_5027;
    return hoisted__U32_5027;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_5028 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5028;
    I64 hoisted__I64_5029 = 42;
    (void)hoisted__I64_5029;
    assert_eq(&hoisted__Str_5028, v.x, hoisted__I64_5029);
    Str_delete(&hoisted__Str_5028, (Bool){0});
    Str hoisted__Str_5030 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5030;
    I64 hoisted__I64_5031 = 99;
    (void)hoisted__I64_5031;
    assert_eq(&hoisted__Str_5030, v.y, hoisted__I64_5031);
    Str_delete(&hoisted__Str_5030, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_5034 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5034;
    I64 hoisted__I64_5035 = 10;
    (void)hoisted__I64_5035;
    assert_eq(&hoisted__Str_5034, p.x, hoisted__I64_5035);
    Str_delete(&hoisted__Str_5034, (Bool){0});
    Str hoisted__Str_5036 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5036;
    I64 hoisted__I64_5037 = 20;
    (void)hoisted__I64_5037;
    assert_eq(&hoisted__Str_5036, p.y, hoisted__I64_5037);
    Str_delete(&hoisted__Str_5036, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_5043 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_5043;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_5043;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_5044 = 0;
    (void)hoisted__U32_5044;
    U64 hoisted__U64_5045 = ((U64 (*)(CfRect *, U32))(void *)hasher)(self, hoisted__U32_5044);
    (void)hoisted__U64_5045;
    return hoisted__U64_5045;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_5046 = 32;
    (void)hoisted__U32_5046;
    return hoisted__U32_5046;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_5047 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5047;
    I64 hoisted__I64_5048 = 5;
    (void)hoisted__I64_5048;
    assert_eq(&hoisted__Str_5047, r.top_left.x, hoisted__I64_5048);
    Str_delete(&hoisted__Str_5047, (Bool){0});
    Str hoisted__Str_5049 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5049;
    I64 hoisted__I64_5050 = 10;
    (void)hoisted__I64_5050;
    assert_eq(&hoisted__Str_5049, r.top_left.y, hoisted__I64_5050);
    Str_delete(&hoisted__Str_5049, (Bool){0});
    Str hoisted__Str_5051 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5051;
    I64 hoisted__I64_5052 = 100;
    (void)hoisted__I64_5052;
    assert_eq(&hoisted__Str_5051, r.bottom_right.x, hoisted__I64_5052);
    Str_delete(&hoisted__Str_5051, (Bool){0});
    Str hoisted__Str_5053 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5053;
    I64 hoisted__I64_5054 = 200;
    (void)hoisted__I64_5054;
    assert_eq(&hoisted__Str_5053, r.bottom_right.y, hoisted__I64_5054);
    Str_delete(&hoisted__Str_5053, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_5056 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_5056;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_5056;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_5057 = 0;
    (void)hoisted__U32_5057;
    U64 hoisted__U64_5058 = ((U64 (*)(CfVec3f *, U32))(void *)hasher)(self, hoisted__U32_5057);
    (void)hoisted__U64_5058;
    return hoisted__U64_5058;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_5059 = 12;
    (void)hoisted__U32_5059;
    return hoisted__U32_5059;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str hoisted__Str_5063 = (Str){.c_str = (void *)"test/constfold.til:185:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5063;
    Str *hoisted__Str_5064 = F32_to_str(v.x);
    (void)hoisted__Str_5064;
    Str hoisted__Str_5065 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5065;
    assert_eq_str(&hoisted__Str_5063, hoisted__Str_5064, &hoisted__Str_5065);
    Str_delete(&hoisted__Str_5063, (Bool){0});
    Str_delete(hoisted__Str_5064, 1);
    Str_delete(&hoisted__Str_5065, (Bool){0});
    Str hoisted__Str_5066 = (Str){.c_str = (void *)"test/constfold.til:186:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5066;
    Str *hoisted__Str_5067 = F32_to_str(v.y);
    (void)hoisted__Str_5067;
    Str hoisted__Str_5068 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5068;
    assert_eq_str(&hoisted__Str_5066, hoisted__Str_5067, &hoisted__Str_5068);
    Str_delete(&hoisted__Str_5066, (Bool){0});
    Str_delete(hoisted__Str_5067, 1);
    Str_delete(&hoisted__Str_5068, (Bool){0});
    Str hoisted__Str_5069 = (Str){.c_str = (void *)"test/constfold.til:187:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5069;
    Str *hoisted__Str_5070 = F32_to_str(v.z);
    (void)hoisted__Str_5070;
    Str hoisted__Str_5071 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5071;
    assert_eq_str(&hoisted__Str_5069, hoisted__Str_5070, &hoisted__Str_5071);
    Str_delete(&hoisted__Str_5069, (Bool){0});
    Str_delete(hoisted__Str_5070, 1);
    Str_delete(&hoisted__Str_5071, (Bool){0});
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
    Bool hoisted__Bool_5076 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5076;
    if (hoisted__Bool_5076) {
        Bool hoisted__Bool_5073 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_5073;
        { Bool _ret_val = hoisted__Bool_5073;
                return _ret_val; }
    }
    Bool hoisted__Bool_5077 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5077;
    if (hoisted__Bool_5077) {
        Bool hoisted__Bool_5074 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_5074;
        { Bool _ret_val = hoisted__Bool_5074;
                return _ret_val; }
    }
    Bool hoisted__Bool_5078 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_5078;
    if (hoisted__Bool_5078) {
        Bool hoisted__Bool_5075 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_5075;
        { Bool _ret_val = hoisted__Bool_5075;
                return _ret_val; }
    }
    Bool hoisted__Bool_5079 = 0;
    (void)hoisted__Bool_5079;
    return hoisted__Bool_5079;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_5087 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5087;
    if (hoisted__Bool_5087) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_5088 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5088;
    if (hoisted__Bool_5088) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_5089 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_5089;
    if (hoisted__Bool_5089) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_5090 = (Str){.c_str = (void *)"Color.clone:192:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5090;
    UNREACHABLE(&hoisted__Str_5090);
    Str_delete(&hoisted__Str_5090, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_5091 = 4;
    (void)hoisted__U32_5091;
    return hoisted__U32_5091;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_5092 = (Str){.c_str = (void *)"test/constfold.til:197:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5092;
    Bool hoisted__Bool_5093 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5093;
    assert(&hoisted__Str_5092, hoisted__Bool_5093);
    Str_delete(&hoisted__Str_5092, (Bool){0});
    Bool hoisted__Bool_5094 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5094;
    Str hoisted__Str_5095 = (Str){.c_str = (void *)"test/constfold.til:198:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5095;
    Bool hoisted__Bool_5096 = not(hoisted__Bool_5094);
    (void)hoisted__Bool_5096;
    assert(&hoisted__Str_5095, hoisted__Bool_5096);
    Str_delete(&hoisted__Str_5095, (Bool){0});
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
    Bool hoisted__Bool_5097 = is(self, other);
    (void)hoisted__Bool_5097;
    return hoisted__Bool_5097;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_5115 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5115;
    if (hoisted__Bool_5115) {
        I64 *hoisted__I64_5111 = get_payload(self);
        (void)hoisted__I64_5111;
        (void)hoisted__I64_5111;
        Bool hoisted__Bool_5112 = 0;
        (void)hoisted__Bool_5112;
        I64_delete(hoisted__I64_5111, hoisted__Bool_5112);
    }
    Bool hoisted__Bool_5116 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5116;
    if (hoisted__Bool_5116) {
        Str *hoisted__Str_5113 = get_payload(self);
        (void)hoisted__Str_5113;
        (void)hoisted__Str_5113;
        Bool hoisted__Bool_5114 = 0;
        (void)hoisted__Bool_5114;
        Str_delete(hoisted__Str_5113, hoisted__Bool_5114);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_5145 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5145;
    if (hoisted__Bool_5145) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_5142 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_5142;
        { Token * _ret_val = hoisted__Token_5142;
                return _ret_val; }
    }
    Bool hoisted__Bool_5146 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5146;
    if (hoisted__Bool_5146) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_5143 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_5143;
        Token *hoisted__Token_5144 = Token_Name(hoisted__Str_5143);
        (void)hoisted__Token_5144;
        { Token * _ret_val = hoisted__Token_5144;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_5147 = 24;
    (void)hoisted__U32_5147;
    return hoisted__U32_5147;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_5149 = (Str){.c_str = (void *)"test/constfold.til:206:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5149;
    Bool hoisted__Bool_5150 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5150;
    assert(&hoisted__Str_5149, hoisted__Bool_5150);
    Str_delete(&hoisted__Str_5149, (Bool){0});
    Bool hoisted__Bool_5151 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5151;
    Str hoisted__Str_5152 = (Str){.c_str = (void *)"test/constfold.til:207:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5152;
    Bool hoisted__Bool_5153 = not(hoisted__Bool_5151);
    (void)hoisted__Bool_5153;
    assert(&hoisted__Str_5152, hoisted__Bool_5153);
    Str_delete(&hoisted__Str_5152, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_5154 = (Str){.c_str = (void *)"test/constfold.til:216:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5154;
    Bool hoisted__Bool_5155 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5155;
    assert(&hoisted__Str_5154, hoisted__Bool_5155);
    Str_delete(&hoisted__Str_5154, (Bool){0});
    Bool hoisted__Bool_5156 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5156;
    Str hoisted__Str_5157 = (Str){.c_str = (void *)"test/constfold.til:217:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5157;
    Bool hoisted__Bool_5158 = not(hoisted__Bool_5156);
    (void)hoisted__Bool_5158;
    assert(&hoisted__Str_5157, hoisted__Bool_5158);
    Str_delete(&hoisted__Str_5157, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_5161 = (Str){.c_str = (void *)"test/constfold.til:228:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5161;
    Bool hoisted__Bool_5162 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5162;
    assert(&hoisted__Str_5161, hoisted__Bool_5162);
    Str_delete(&hoisted__Str_5161, (Bool){0});
    Bool hoisted__Bool_5163 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5163;
    Str hoisted__Str_5164 = (Str){.c_str = (void *)"test/constfold.til:229:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5164;
    Bool hoisted__Bool_5165 = not(hoisted__Bool_5163);
    (void)hoisted__Bool_5165;
    assert(&hoisted__Str_5164, hoisted__Bool_5165);
    Str_delete(&hoisted__Str_5164, (Bool){0});
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
