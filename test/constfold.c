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
Bool U32_neq(U32 a, U32 b);
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
Bool U32_neq(U32 a, U32 b);
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
#define TIL_CAP_STATIC ((USize)-3)
void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
void print_flush() {
    putchar('\n');
}

U32 CAP_LIT;
U32 CAP_VIEW;
U32 CAP_STATIC;
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

Bool U32_neq(U32 a, U32 b) {
    Bool hoisted__Bool_225 = U32_eq(a, b);
    (void)hoisted__Bool_225;
    Bool hoisted__Bool_226 = not(hoisted__Bool_225);
    (void)hoisted__Bool_226;
    return hoisted__Bool_226;
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
        Array *_fc_Array_803 = parts;
        (void)_fc_Array_803;
        (void)_fc_Array_803;
        U32 _fi_USize_803 = 0;
        (void)_fi_USize_803;
        I64 _forin_err_kind_803 = 0;
        (void)_forin_err_kind_803;
        OutOfBounds *_forin_OutOfBounds_803 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_803->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_803;
        while (1) {
            U32 hoisted__U32_811 = Array_len(_fc_Array_803);
            (void)hoisted__U32_811;
            Bool _wcond_Bool_804 = U32_lt(_fi_USize_803, hoisted__U32_811);
            (void)_wcond_Bool_804;
            if (_wcond_Bool_804) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_803, &_fi_USize_803, &_forin_err_kind_803, _forin_OutOfBounds_803);
            I64 hoisted__I64_812 = 0;
            (void)hoisted__I64_812;
            Bool hoisted__Bool_813 = I64_eq(_forin_err_kind_803, hoisted__I64_812);
            (void)hoisted__Bool_813;
            Bool hoisted__Bool_814 = not(hoisted__Bool_813);
            (void)hoisted__Bool_814;
            if (hoisted__Bool_814) {
                Type *hoisted__Type_806 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_806;
                U32 hoisted__U32_807 = 1;
                (void)hoisted__U32_807;
                Array *_va_Array_24 = Array_new(hoisted__Type_806, hoisted__U32_807);
                (void)_va_Array_24;
                Type_delete(hoisted__Type_806, 1);
                U32 hoisted__U32_808 = 0;
                (void)hoisted__U32_808;
                Str hoisted__Str_809 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_809;
                Array_set(_va_Array_24, hoisted__U32_808, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_809; _oa; }));
                Str hoisted__Str_810 = (Str){.c_str = (void *)"./src/core/str.til:19:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_810;
                panic(&hoisted__Str_810, _va_Array_24);
                Str_delete(&hoisted__Str_810, (Bool){0});
            }
            U32 hoisted__U32_815 = 1;
            (void)hoisted__U32_815;
            U32 hoisted__U32_816 = U32_add(_fi_USize_803, hoisted__U32_815);
            (void)hoisted__U32_816;
            _fi_USize_803 = hoisted__U32_816;
            U32 hoisted__U32_817 = Str_len(s);
            (void)hoisted__U32_817;
            U32 hoisted__U32_818 = U32_add(total, hoisted__U32_817);
            (void)hoisted__U32_818;
            total = hoisted__U32_818;
        }
        OutOfBounds_delete(_forin_OutOfBounds_803, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array *_fc_Array_819 = parts;
        (void)_fc_Array_819;
        (void)_fc_Array_819;
        U32 _fi_USize_819 = 0;
        (void)_fi_USize_819;
        I64 _forin_err_kind_819 = 0;
        (void)_forin_err_kind_819;
        OutOfBounds *_forin_OutOfBounds_819 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_819->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_819;
        while (1) {
            U32 hoisted__U32_827 = Array_len(_fc_Array_819);
            (void)hoisted__U32_827;
            Bool _wcond_Bool_820 = U32_lt(_fi_USize_819, hoisted__U32_827);
            (void)_wcond_Bool_820;
            if (_wcond_Bool_820) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_819, &_fi_USize_819, &_forin_err_kind_819, _forin_OutOfBounds_819);
            I64 hoisted__I64_828 = 0;
            (void)hoisted__I64_828;
            Bool hoisted__Bool_829 = I64_eq(_forin_err_kind_819, hoisted__I64_828);
            (void)hoisted__Bool_829;
            Bool hoisted__Bool_830 = not(hoisted__Bool_829);
            (void)hoisted__Bool_830;
            if (hoisted__Bool_830) {
                Type *hoisted__Type_822 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_822;
                U32 hoisted__U32_823 = 1;
                (void)hoisted__U32_823;
                Array *_va_Array_25 = Array_new(hoisted__Type_822, hoisted__U32_823);
                (void)_va_Array_25;
                Type_delete(hoisted__Type_822, 1);
                U32 hoisted__U32_824 = 0;
                (void)hoisted__U32_824;
                Str hoisted__Str_825 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_825;
                Array_set(_va_Array_25, hoisted__U32_824, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_825; _oa; }));
                Str hoisted__Str_826 = (Str){.c_str = (void *)"./src/core/str.til:23:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_826;
                panic(&hoisted__Str_826, _va_Array_25);
                Str_delete(&hoisted__Str_826, (Bool){0});
            }
            U32 hoisted__U32_831 = 1;
            (void)hoisted__U32_831;
            U32 hoisted__U32_832 = U32_add(_fi_USize_819, hoisted__U32_831);
            (void)hoisted__U32_832;
            _fi_USize_819 = hoisted__U32_832;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_819, 1);
    }
    Array_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_839 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_839;
    if (hoisted__Bool_839) {
        Type *hoisted__Type_834 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_834;
        U32 hoisted__U32_835 = 1;
        (void)hoisted__U32_835;
        Array *_va_Array_26 = Array_new(hoisted__Type_834, hoisted__U32_835);
        (void)_va_Array_26;
        Type_delete(hoisted__Type_834, 1);
        U32 hoisted__U32_836 = 0;
        (void)hoisted__U32_836;
        Str hoisted__Str_837 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_837;
        Array_set(_va_Array_26, hoisted__U32_836, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_837; _oa; }));
        Str hoisted__Str_838 = (Str){.c_str = (void *)"./src/core/str.til:43:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_838;
        panic(&hoisted__Str_838, _va_Array_26);
        Str_delete(&hoisted__Str_838, (Bool){0});
    }
    void *hoisted__v_840 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_840;
    (void)hoisted__v_840;
    return hoisted__v_840;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_850 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_850;
    if (hoisted__Bool_850) {
        min_len = b->count;
    }
    {
        U32 _re_U32_842 = U32_clone(&min_len);
        (void)_re_U32_842;
        U32 _rc_U32_842 = 0;
        (void)_rc_U32_842;
        Bool hoisted__Bool_849 = U32_lte(_rc_U32_842, _re_U32_842);
        (void)hoisted__Bool_849;
        if (hoisted__Bool_849) {
            while (1) {
                Bool _wcond_Bool_843 = U32_lt(_rc_U32_842, _re_U32_842);
                (void)_wcond_Bool_843;
                if (_wcond_Bool_843) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_842);
                U32_inc(&_rc_U32_842);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_844 = 0;
                (void)hoisted__I64_844;
                Bool hoisted__Bool_845 = I64_neq(c, hoisted__I64_844);
                (void)hoisted__Bool_845;
                if (hoisted__Bool_845) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_846 = U32_gt(_rc_U32_842, _re_U32_842);
                (void)_wcond_Bool_846;
                if (_wcond_Bool_846) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_842);
                U32_dec(&_rc_U32_842);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_847 = 0;
                (void)hoisted__I64_847;
                Bool hoisted__Bool_848 = I64_neq(c, hoisted__I64_847);
                (void)hoisted__Bool_848;
                if (hoisted__Bool_848) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_851 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_851;
    return hoisted__I64_851;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_853 = 1;
    (void)hoisted__U32_853;
    U32 hoisted__U64_854 = U32_add(n, hoisted__U32_853);
    (void)hoisted__U64_854;
    void * buf = malloc(hoisted__U64_854);
    I32 hoisted__I32_855 = 0;
    (void)hoisted__I32_855;
    U64 hoisted__U64_856 = 1ULL;
    (void)hoisted__U64_856;
    memset(buf, hoisted__I32_855, hoisted__U64_856);
    I64 hoisted__I64_857 = 0;
    (void)hoisted__I64_857;
    Str *hoisted__Str_858 = malloc(sizeof(Str));
    hoisted__Str_858->c_str = buf;
    hoisted__Str_858->count = hoisted__I64_857;
    hoisted__Str_858->cap = n;
    (void)hoisted__Str_858;
    return hoisted__Str_858;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_873 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_873;
    if (hoisted__Bool_873) {
        Type *hoisted__Type_862 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_862;
        U32 hoisted__U32_863 = 1;
        (void)hoisted__U32_863;
        Array *_va_Array_27 = Array_new(hoisted__Type_862, hoisted__U32_863);
        (void)_va_Array_27;
        Type_delete(hoisted__Type_862, 1);
        U32 hoisted__U32_864 = 0;
        (void)hoisted__U32_864;
        Str hoisted__Str_865 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_865;
        Array_set(_va_Array_27, hoisted__U32_864, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_865; _oa; }));
        Str hoisted__Str_866 = (Str){.c_str = (void *)"./src/core/str.til:92:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_866;
        panic(&hoisted__Str_866, _va_Array_27);
        Str_delete(&hoisted__Str_866, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_874 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_874;
    if (hoisted__Bool_874) {
        Type *hoisted__Type_868 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_868;
        U32 hoisted__U32_869 = 1;
        (void)hoisted__U32_869;
        Array *_va_Array_28 = Array_new(hoisted__Type_868, hoisted__U32_869);
        (void)_va_Array_28;
        Type_delete(hoisted__Type_868, 1);
        U32 hoisted__U32_870 = 0;
        (void)hoisted__U32_870;
        Str hoisted__Str_871 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_871;
        Array_set(_va_Array_28, hoisted__U32_870, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_871; _oa; }));
        Str hoisted__Str_872 = (Str){.c_str = (void *)"./src/core/str.til:96:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_872;
        panic(&hoisted__Str_872, _va_Array_28);
        Str_delete(&hoisted__Str_872, (Bool){0});
    }
    void *hoisted__v_875 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_875;
    (void)hoisted__v_875;
    memcpy(hoisted__v_875, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_876 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_876;
    (void)hoisted__v_876;
    I32 hoisted__I32_877 = 0;
    (void)hoisted__I32_877;
    U64 hoisted__U64_878 = 1ULL;
    (void)hoisted__U64_878;
    memset(hoisted__v_876, hoisted__I32_877, hoisted__U64_878);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_879 = 1;
    (void)hoisted__U32_879;
    U32 hoisted__U64_880 = U32_add(val->count, hoisted__U32_879);
    (void)hoisted__U64_880;
    void * new_data = malloc(hoisted__U64_880);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_881 = ptr_add(new_data, val->count);
    (void)hoisted__v_881;
    (void)hoisted__v_881;
    I32 hoisted__I32_882 = 0;
    (void)hoisted__I32_882;
    U64 hoisted__U64_883 = 1ULL;
    (void)hoisted__U64_883;
    memset(hoisted__v_881, hoisted__I32_882, hoisted__U64_883);
    Str *hoisted__Str_884 = malloc(sizeof(Str));
    hoisted__Str_884->c_str = new_data;
    hoisted__Str_884->count = val->count;
    hoisted__Str_884->cap = val->count;
    (void)hoisted__Str_884;
    return hoisted__Str_884;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_885 = U32_lt(self->cap, CAP_STATIC);
    (void)hoisted__Bool_885;
    if (hoisted__Bool_885) {
        free(self->c_str);
    }
    Bool hoisted__Bool_886 = U32_neq(self->cap, CAP_STATIC);
    (void)hoisted__Bool_886;
    Bool hoisted__Bool_887 = and(call_free, hoisted__Bool_886);
    (void)hoisted__Bool_887;
    if (hoisted__Bool_887) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_1000 = 0;
    (void)hoisted__U32_1000;
    Bool hoisted__Bool_1001 = U32_eq(self->count, hoisted__U32_1000);
    (void)hoisted__Bool_1001;
    return hoisted__Bool_1001;
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_1094 = ((U64 (*)(I8 *, U32))(void *)hasher)(self->c_str, self->count);
    (void)hoisted__U64_1094;
    return hoisted__U64_1094;
}

U32 Str_size(void) {
    U32 hoisted__U32_1281 = 16;
    (void)hoisted__U32_1281;
    return hoisted__U32_1281;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1282 = Str_cmp(a, b);
    (void)hoisted__I64_1282;
    I64 hoisted__I64_1283 = 0;
    (void)hoisted__I64_1283;
    Bool hoisted__Bool_1284 = I64_eq(hoisted__I64_1282, hoisted__I64_1283);
    (void)hoisted__Bool_1284;
    return hoisted__Bool_1284;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1382 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1382->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1382;
    return hoisted__OutOfBounds_1382;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1383 = 0;
    (void)hoisted__Bool_1383;
    Str_delete(&self->msg, hoisted__Bool_1383);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1384 = 0;
    (void)hoisted__U32_1384;
    U64 hoisted__U64_1385 = ((U64 (*)(OutOfBounds *, U32))(void *)hasher)(self, hoisted__U32_1384);
    (void)hoisted__U64_1385;
    return hoisted__U64_1385;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1386 = 16;
    (void)hoisted__U32_1386;
    return hoisted__U32_1386;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1395 = 8;
    (void)hoisted__U32_1395;
    return hoisted__U32_1395;
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1600 = 0;
    (void)hoisted__I64_1600;
    Bool hoisted__Bool_1601 = I64_eq(val, hoisted__I64_1600);
    (void)hoisted__Bool_1601;
    if (hoisted__Bool_1601) {
        U64 hoisted__U64_1564 = 2ULL;
        (void)hoisted__U64_1564;
        void * buf = malloc(hoisted__U64_1564);
        I64 hoisted__I64_1565 = 48;
        (void)hoisted__I64_1565;
        U64 hoisted__U64_1566 = 1ULL;
        (void)hoisted__U64_1566;
        memcpy(buf, &hoisted__I64_1565, hoisted__U64_1566);
        U64 hoisted__U64_1567 = 1ULL;
        (void)hoisted__U64_1567;
        void *hoisted__v_1568 = ptr_add(buf, hoisted__U64_1567);
        (void)hoisted__v_1568;
        (void)hoisted__v_1568;
        I32 hoisted__I32_1569 = 0;
        (void)hoisted__I32_1569;
        U64 hoisted__U64_1570 = 1ULL;
        (void)hoisted__U64_1570;
        memset(hoisted__v_1568, hoisted__I32_1569, hoisted__U64_1570);
        I64 hoisted__I64_1571 = 1;
        (void)hoisted__I64_1571;
        I64 hoisted__I64_1572 = 1;
        (void)hoisted__I64_1572;
        Str *hoisted__Str_1573 = malloc(sizeof(Str));
        hoisted__Str_1573->c_str = buf;
        hoisted__Str_1573->count = hoisted__I64_1571;
        hoisted__Str_1573->cap = hoisted__I64_1572;
        (void)hoisted__Str_1573;
        { Str * _ret_val = hoisted__Str_1573;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1602 = 0;
    (void)hoisted__I64_1602;
    Bool hoisted__Bool_1603 = I64_lt(val, hoisted__I64_1602);
    (void)hoisted__Bool_1603;
    if (hoisted__Bool_1603) {
        Bool hoisted__Bool_1574 = 1;
        (void)hoisted__Bool_1574;
        is_neg = hoisted__Bool_1574;
        I64 hoisted__I64_1575 = 0;
        (void)hoisted__I64_1575;
        I64 hoisted__I64_1576 = I64_sub(hoisted__I64_1575, val);
        (void)hoisted__I64_1576;
        v = hoisted__I64_1576;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1578 = 0;
        (void)hoisted__I64_1578;
        Bool _wcond_Bool_1577 = I64_gt(tmp, hoisted__I64_1578);
        (void)_wcond_Bool_1577;
        if (_wcond_Bool_1577) {
        } else {
            break;
        }
        U64 hoisted__U64_1579 = 1ULL;
        (void)hoisted__U64_1579;
        U64 hoisted__U64_1580 = U64_add(ndigits, hoisted__U64_1579);
        (void)hoisted__U64_1580;
        ndigits = hoisted__U64_1580;
        I64 hoisted__I64_1581 = 10;
        (void)hoisted__I64_1581;
        I64 hoisted__I64_1582 = I64_div(tmp, hoisted__I64_1581);
        (void)hoisted__I64_1582;
        tmp = hoisted__I64_1582;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1583 = 1ULL;
        (void)hoisted__U64_1583;
        U64 hoisted__U64_1584 = U64_add(total, hoisted__U64_1583);
        (void)hoisted__U64_1584;
        total = hoisted__U64_1584;
    }
    U64 hoisted__U64_1604 = 1ULL;
    (void)hoisted__U64_1604;
    U64 hoisted__U64_1605 = U64_add(total, hoisted__U64_1604);
    (void)hoisted__U64_1605;
    void * buf = malloc(hoisted__U64_1605);
    if (is_neg) {
        I64 hoisted__I64_1585 = 45;
        (void)hoisted__I64_1585;
        U64 hoisted__U64_1586 = 1ULL;
        (void)hoisted__U64_1586;
        memcpy(buf, &hoisted__I64_1585, hoisted__U64_1586);
    }
    U64 hoisted__U64_1606 = 1ULL;
    (void)hoisted__U64_1606;
    U64 i = U64_sub(total, hoisted__U64_1606);
    while (1) {
        I64 hoisted__I64_1588 = 0;
        (void)hoisted__I64_1588;
        Bool _wcond_Bool_1587 = I64_gt(v, hoisted__I64_1588);
        (void)_wcond_Bool_1587;
        if (_wcond_Bool_1587) {
        } else {
            break;
        }
        I64 hoisted__I64_1589 = 10;
        (void)hoisted__I64_1589;
        I64 hoisted__I64_1590 = I64_mod(v, hoisted__I64_1589);
        (void)hoisted__I64_1590;
        I64 hoisted__I64_1591 = 48;
        (void)hoisted__I64_1591;
        I64 hoisted__I64_1592 = I64_add(hoisted__I64_1590, hoisted__I64_1591);
        (void)hoisted__I64_1592;
        void *hoisted__v_1593 = ptr_add(buf, i);
        (void)hoisted__v_1593;
        (void)hoisted__v_1593;
        U8 hoisted__U8_1594 = I64_to_u8(hoisted__I64_1592);
        (void)hoisted__U8_1594;
        U64 hoisted__U64_1595 = 1ULL;
        (void)hoisted__U64_1595;
        memcpy(hoisted__v_1593, &hoisted__U8_1594, hoisted__U64_1595);
        I64 hoisted__I64_1596 = 10;
        (void)hoisted__I64_1596;
        I64 hoisted__I64_1597 = I64_div(v, hoisted__I64_1596);
        (void)hoisted__I64_1597;
        v = hoisted__I64_1597;
        U64 hoisted__U64_1598 = 1ULL;
        (void)hoisted__U64_1598;
        U64 hoisted__U64_1599 = U64_sub(i, hoisted__U64_1598);
        (void)hoisted__U64_1599;
        i = hoisted__U64_1599;
    }
    void *hoisted__v_1607 = ptr_add(buf, total);
    (void)hoisted__v_1607;
    (void)hoisted__v_1607;
    I32 hoisted__I32_1608 = 0;
    (void)hoisted__I32_1608;
    U64 hoisted__U64_1609 = 1ULL;
    (void)hoisted__U64_1609;
    memset(hoisted__v_1607, hoisted__I32_1608, hoisted__U64_1609);
    Str *hoisted__Str_1610 = malloc(sizeof(Str));
    hoisted__Str_1610->c_str = buf;
    hoisted__Str_1610->count = total;
    hoisted__Str_1610->cap = total;
    (void)hoisted__Str_1610;
    return hoisted__Str_1610;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1630 = 8;
    (void)hoisted__U32_1630;
    return hoisted__U32_1630;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1761 = 0;
    (void)hoisted__U32_1761;
    U64 hoisted__U64_1762 = ((U64 (*)(I64 *, U32))(void *)hasher)(&self, hoisted__U32_1761);
    (void)hoisted__U64_1762;
    return hoisted__U64_1762;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1765 = I64_cmp(a, b);
    (void)hoisted__I64_1765;
    I64 hoisted__I64_1766 = -1;
    (void)hoisted__I64_1766;
    Bool hoisted__Bool_1767 = I64_eq(hoisted__I64_1765, hoisted__I64_1766);
    (void)hoisted__Bool_1767;
    return hoisted__Bool_1767;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1768 = I64_cmp(a, b);
    (void)hoisted__I64_1768;
    I64 hoisted__I64_1769 = 1;
    (void)hoisted__I64_1769;
    Bool hoisted__Bool_1770 = I64_eq(hoisted__I64_1768, hoisted__I64_1769);
    (void)hoisted__Bool_1770;
    return hoisted__Bool_1770;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1771 = I64_eq(a, b);
    (void)hoisted__Bool_1771;
    Bool hoisted__Bool_1772 = not(hoisted__Bool_1771);
    (void)hoisted__Bool_1772;
    return hoisted__Bool_1772;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1790 = Bool_eq(a, b);
    (void)hoisted__Bool_1790;
    if (hoisted__Bool_1790) {
        I64 hoisted__I64_1788 = 0;
        (void)hoisted__I64_1788;
        { I64 _ret_val = hoisted__I64_1788;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1789 = -1;
        (void)hoisted__I64_1789;
        return hoisted__I64_1789;
    }
    I64 hoisted__I64_1791 = 1;
    (void)hoisted__I64_1791;
    return hoisted__I64_1791;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1792 = 1;
    (void)hoisted__U32_1792;
    return hoisted__U32_1792;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1793 = 0;
    (void)hoisted__U32_1793;
    U64 hoisted__U64_1794 = ((U64 (*)(Bool *, U32))(void *)hasher)(&self, hoisted__U32_1793);
    (void)hoisted__U64_1794;
    return hoisted__U64_1794;
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
    Bool hoisted__Bool_1946 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1946;
    if (hoisted__Bool_1946) {
        Bool hoisted__Bool_1936 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1936;
        { Bool _ret_val = hoisted__Bool_1936;
                return _ret_val; }
    }
    Bool hoisted__Bool_1947 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1947;
    if (hoisted__Bool_1947) {
        Bool hoisted__Bool_1937 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1937;
        { Bool _ret_val = hoisted__Bool_1937;
                return _ret_val; }
    }
    Bool hoisted__Bool_1948 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1948;
    if (hoisted__Bool_1948) {
        Bool hoisted__Bool_1938 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_1938;
        { Bool _ret_val = hoisted__Bool_1938;
                return _ret_val; }
    }
    Bool hoisted__Bool_1949 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1949;
    if (hoisted__Bool_1949) {
        Bool hoisted__Bool_1939 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_1939;
        { Bool _ret_val = hoisted__Bool_1939;
                return _ret_val; }
    }
    Bool hoisted__Bool_1950 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1950;
    if (hoisted__Bool_1950) {
        Bool hoisted__Bool_1940 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_1940;
        { Bool _ret_val = hoisted__Bool_1940;
                return _ret_val; }
    }
    Bool hoisted__Bool_1951 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1951;
    if (hoisted__Bool_1951) {
        Bool hoisted__Bool_1941 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_1941;
        { Bool _ret_val = hoisted__Bool_1941;
                return _ret_val; }
    }
    Bool hoisted__Bool_1952 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1952;
    if (hoisted__Bool_1952) {
        Bool hoisted__Bool_1942 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_1942;
        { Bool _ret_val = hoisted__Bool_1942;
                return _ret_val; }
    }
    Bool hoisted__Bool_1953 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1953;
    if (hoisted__Bool_1953) {
        Bool hoisted__Bool_1943 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_1943;
        { Bool _ret_val = hoisted__Bool_1943;
                return _ret_val; }
    }
    Bool hoisted__Bool_1954 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1954;
    if (hoisted__Bool_1954) {
        Bool hoisted__Bool_1944 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_1944;
        { Bool _ret_val = hoisted__Bool_1944;
                return _ret_val; }
    }
    Bool hoisted__Bool_1955 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1955;
    if (hoisted__Bool_1955) {
        Bool hoisted__Bool_1945 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_1945;
        { Bool _ret_val = hoisted__Bool_1945;
                return _ret_val; }
    }
    Bool hoisted__Bool_1956 = 0;
    (void)hoisted__Bool_1956;
    return hoisted__Bool_1956;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1978 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1978;
    if (hoisted__Bool_1978) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1979 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1979;
    if (hoisted__Bool_1979) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_1980 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1980;
    if (hoisted__Bool_1980) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_1981 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1981;
    if (hoisted__Bool_1981) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1982 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1982;
    if (hoisted__Bool_1982) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1983 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1983;
    if (hoisted__Bool_1983) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1984 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1984;
    if (hoisted__Bool_1984) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1985 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1985;
    if (hoisted__Bool_1985) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1986 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1986;
    if (hoisted__Bool_1986) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1987 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1987;
    if (hoisted__Bool_1987) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_1988 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1988;
    UNREACHABLE(&hoisted__Str_1988);
    Str_delete(&hoisted__Str_1988, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1989 = 4;
    (void)hoisted__U32_1989;
    return hoisted__U32_1989;
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
    Bool hoisted__Bool_2041 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2041;
    if (hoisted__Bool_2041) {
        Str *hoisted__Str_2031 = get_payload(self);
        (void)hoisted__Str_2031;
        (void)hoisted__Str_2031;
        Bool hoisted__Bool_2032 = 0;
        (void)hoisted__Bool_2032;
        Str_delete(hoisted__Str_2031, hoisted__Bool_2032);
    }
    Bool hoisted__Bool_2042 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2042;
    if (hoisted__Bool_2042) {
        Str *hoisted__Str_2033 = get_payload(self);
        (void)hoisted__Str_2033;
        (void)hoisted__Str_2033;
        Bool hoisted__Bool_2034 = 0;
        (void)hoisted__Bool_2034;
        Str_delete(hoisted__Str_2033, hoisted__Bool_2034);
    }
    Bool hoisted__Bool_2043 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2043;
    if (hoisted__Bool_2043) {
        Str *hoisted__Str_2035 = get_payload(self);
        (void)hoisted__Str_2035;
        (void)hoisted__Str_2035;
        Bool hoisted__Bool_2036 = 0;
        (void)hoisted__Bool_2036;
        Str_delete(hoisted__Str_2035, hoisted__Bool_2036);
    }
    Bool hoisted__Bool_2044 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2044;
    if (hoisted__Bool_2044) {
        Primitive *hoisted__Primitive_2037 = get_payload(self);
        (void)hoisted__Primitive_2037;
        (void)hoisted__Primitive_2037;
        Bool hoisted__Bool_2038 = 0;
        (void)hoisted__Bool_2038;
        Primitive_delete(hoisted__Primitive_2037, hoisted__Bool_2038);
    }
    Bool hoisted__Bool_2045 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2045;
    if (hoisted__Bool_2045) {
        Str *hoisted__Str_2039 = get_payload(self);
        (void)hoisted__Str_2039;
        (void)hoisted__Str_2039;
        Bool hoisted__Bool_2040 = 0;
        (void)hoisted__Bool_2040;
        Str_delete(hoisted__Str_2039, hoisted__Bool_2040);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2124 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2124;
    if (hoisted__Bool_2124) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2125 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2125;
    if (hoisted__Bool_2125) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2126 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2126;
    if (hoisted__Bool_2126) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2116 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2116;
        Type *hoisted__Type_2117 = Type_Struct(hoisted__Str_2116);
        (void)hoisted__Type_2117;
        { Type * _ret_val = hoisted__Type_2117;
                return _ret_val; }
    }
    Bool hoisted__Bool_2127 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2127;
    if (hoisted__Bool_2127) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2128 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2128;
    if (hoisted__Bool_2128) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2118 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2118;
        Type *hoisted__Type_2119 = Type_Enum(hoisted__Str_2118);
        (void)hoisted__Type_2119;
        { Type * _ret_val = hoisted__Type_2119;
                return _ret_val; }
    }
    Bool hoisted__Bool_2129 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2129;
    if (hoisted__Bool_2129) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2130 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2130;
    if (hoisted__Bool_2130) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2131 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2131;
    if (hoisted__Bool_2131) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2132 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2132;
    if (hoisted__Bool_2132) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2133 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2133;
    if (hoisted__Bool_2133) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2120 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2120;
        Type *hoisted__Type_2121 = Type_Custom(hoisted__Str_2120);
        (void)hoisted__Type_2121;
        { Type * _ret_val = hoisted__Type_2121;
                return _ret_val; }
    }
    Bool hoisted__Bool_2134 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2134;
    if (hoisted__Bool_2134) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2122 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2122;
        Type *hoisted__Type_2123 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2122; _oa; }));
        (void)hoisted__Type_2123;
        { Type * _ret_val = hoisted__Type_2123;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2135 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2135;
    Type *hoisted__Type_2136 = Type_FuncPtrSig(hoisted__Str_2135);
    (void)hoisted__Type_2136;
    return hoisted__Type_2136;
}

U32 Type_size(void) {
    U32 hoisted__U32_2137 = 24;
    (void)hoisted__U32_2137;
    return hoisted__U32_2137;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3816 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3816;
    if (hoisted__Bool_3816) {
        Type *hoisted__Type_3811 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3811;
        U32 hoisted__U32_3812 = 1;
        (void)hoisted__U32_3812;
        Array *_va_Array_114 = Array_new(hoisted__Type_3811, hoisted__U32_3812);
        (void)_va_Array_114;
        Type_delete(hoisted__Type_3811, 1);
        U32 hoisted__U32_3813 = 0;
        (void)hoisted__U32_3813;
        Str hoisted__Str_3814 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3814;
        Array_set(_va_Array_114, hoisted__U32_3813, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3814; _oa; }));
        Str hoisted__Str_3815 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3815;
        panic(&hoisted__Str_3815, _va_Array_114);
        Str_delete(&hoisted__Str_3815, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3817 = calloc(cap, elem_size);
    (void)hoisted__v_3817;
    void * hoisted__v_3818 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3818;
    void * hoisted__v_3819 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3819;
    Array *hoisted__Array_3820 = malloc(sizeof(Array));
    hoisted__Array_3820->data = hoisted__v_3817;
    hoisted__Array_3820->cap = cap;
    hoisted__Array_3820->elem_size = elem_size;
    hoisted__Array_3820->elem_clone = hoisted__v_3818;
    hoisted__Array_3820->elem_delete = hoisted__v_3819;
    (void)hoisted__Array_3820;
    return hoisted__Array_3820;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3821 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3821;
    Str_delete(elem_type, 1);
    return hoisted__Array_3821;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3842 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3842;
    if (hoisted__Bool_3842) {
        Type *hoisted__Type_3823 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3823;
        U32 hoisted__U32_3824 = 6;
        (void)hoisted__U32_3824;
        Array *_va_Array_115 = Array_new(hoisted__Type_3823, hoisted__U32_3824);
        (void)_va_Array_115;
        Type_delete(hoisted__Type_3823, 1);
        U32 hoisted__U32_3825 = 0;
        (void)hoisted__U32_3825;
        Str hoisted__Str_3826 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3826;
        Array_set(_va_Array_115, hoisted__U32_3825, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3826; _oa; }));
        U32 hoisted__U32_3827 = 1;
        (void)hoisted__U32_3827;
        Str hoisted__Str_3828 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3828;
        Array_set(_va_Array_115, hoisted__U32_3827, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3828; _oa; }));
        U32 hoisted__U32_3829 = 2;
        (void)hoisted__U32_3829;
        Str *hoisted__Str_3830 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3830;
        Array_set(_va_Array_115, hoisted__U32_3829, hoisted__Str_3830);
        U32 hoisted__U32_3831 = 3;
        (void)hoisted__U32_3831;
        Str hoisted__Str_3832 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3832;
        Array_set(_va_Array_115, hoisted__U32_3831, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3832; _oa; }));
        U32 hoisted__U32_3833 = 4;
        (void)hoisted__U32_3833;
        Str *hoisted__Str_3834 = U32_to_str(self->cap);
        (void)hoisted__Str_3834;
        Array_set(_va_Array_115, hoisted__U32_3833, hoisted__Str_3834);
        U32 hoisted__U32_3835 = 5;
        (void)hoisted__U32_3835;
        Str hoisted__Str_3836 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3836;
        Array_set(_va_Array_115, hoisted__U32_3835, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3836; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3837 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_115); hoisted__OutOfBounds_3837->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3837;
        U32 hoisted__U32_3838 = 16;
        (void)hoisted__U32_3838;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3837, hoisted__U32_3838);
        OutOfBounds_delete(hoisted__OutOfBounds_3837, 1);
        I64 hoisted__I64_3839 = 3;
        (void)hoisted__I64_3839;
        *_err_kind = hoisted__I64_3839;
    }
    I64 hoisted__I64_3843 = 0;
    (void)hoisted__I64_3843;
    Bool hoisted__Bool_3844 = I64_eq(DEREF(_err_kind), hoisted__I64_3843);
    (void)hoisted__Bool_3844;
    if (hoisted__Bool_3844) {
        U32 hoisted__U64_3840 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3840;
        void *hoisted__v_3841 = ptr_add(self->data, hoisted__U64_3840);
        (void)hoisted__v_3841;
        (void)hoisted__v_3841;
        { void * _ret_val = hoisted__v_3841;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3859 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3859;
    if (hoisted__Bool_3859) {
        Type *hoisted__Type_3846 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3846;
        U32 hoisted__U32_3847 = 5;
        (void)hoisted__U32_3847;
        Array *_va_Array_116 = Array_new(hoisted__Type_3846, hoisted__U32_3847);
        (void)_va_Array_116;
        Type_delete(hoisted__Type_3846, 1);
        U32 hoisted__U32_3848 = 0;
        (void)hoisted__U32_3848;
        Str hoisted__Str_3849 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3849;
        Array_set(_va_Array_116, hoisted__U32_3848, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3849; _oa; }));
        U32 hoisted__U32_3850 = 1;
        (void)hoisted__U32_3850;
        Str *hoisted__Str_3851 = U32_to_str(i);
        (void)hoisted__Str_3851;
        Array_set(_va_Array_116, hoisted__U32_3850, hoisted__Str_3851);
        U32 hoisted__U32_3852 = 2;
        (void)hoisted__U32_3852;
        Str hoisted__Str_3853 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3853;
        Array_set(_va_Array_116, hoisted__U32_3852, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3853; _oa; }));
        U32 hoisted__U32_3854 = 3;
        (void)hoisted__U32_3854;
        Str *hoisted__Str_3855 = U32_to_str(self->cap);
        (void)hoisted__Str_3855;
        Array_set(_va_Array_116, hoisted__U32_3854, hoisted__Str_3855);
        U32 hoisted__U32_3856 = 4;
        (void)hoisted__U32_3856;
        Str hoisted__Str_3857 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3857;
        Array_set(_va_Array_116, hoisted__U32_3856, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3857; _oa; }));
        Str hoisted__Str_3858 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3858;
        panic(&hoisted__Str_3858, _va_Array_116);
        Str_delete(&hoisted__Str_3858, (Bool){0});
    }
    U32 hoisted__U64_3860 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3860;
    void *hoisted__v_3861 = ptr_add(self->data, hoisted__U64_3860);
    (void)hoisted__v_3861;
    (void)hoisted__v_3861;
    Bool hoisted__Bool_3862 = 0;
    (void)hoisted__Bool_3862;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3861, hoisted__Bool_3862);
    U32 hoisted__U64_3863 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3863;
    void *hoisted__v_3864 = ptr_add(self->data, hoisted__U64_3863);
    (void)hoisted__v_3864;
    (void)hoisted__v_3864;
    memcpy(hoisted__v_3864, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3865 = self->cap;
        (void)_re_U32_3865;
        U32 _rc_U32_3865 = 0;
        (void)_rc_U32_3865;
        Bool hoisted__Bool_3874 = U32_lte(_rc_U32_3865, _re_U32_3865);
        (void)hoisted__Bool_3874;
        if (hoisted__Bool_3874) {
            while (1) {
                Bool _wcond_Bool_3866 = U32_lt(_rc_U32_3865, _re_U32_3865);
                (void)_wcond_Bool_3866;
                if (_wcond_Bool_3866) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3865);
                U32_inc(&_rc_U32_3865);
                U32 hoisted__U64_3867 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3867;
                void *hoisted__v_3868 = ptr_add(self->data, hoisted__U64_3867);
                (void)hoisted__v_3868;
                (void)hoisted__v_3868;
                Bool hoisted__Bool_3869 = 0;
                (void)hoisted__Bool_3869;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3868, hoisted__Bool_3869);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3870 = U32_gt(_rc_U32_3865, _re_U32_3865);
                (void)_wcond_Bool_3870;
                if (_wcond_Bool_3870) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3865);
                U32_dec(&_rc_U32_3865);
                U32 hoisted__U64_3871 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3871;
                void *hoisted__v_3872 = ptr_add(self->data, hoisted__U64_3871);
                (void)hoisted__v_3872;
                (void)hoisted__v_3872;
                Bool hoisted__Bool_3873 = 0;
                (void)hoisted__Bool_3873;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3872, hoisted__Bool_3873);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3887 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3887;
    void * new_data = malloc(hoisted__U64_3887);
    {
        U32 _re_U32_3875 = self->cap;
        (void)_re_U32_3875;
        U32 _rc_U32_3875 = 0;
        (void)_rc_U32_3875;
        Bool hoisted__Bool_3886 = U32_lte(_rc_U32_3875, _re_U32_3875);
        (void)hoisted__Bool_3886;
        if (hoisted__Bool_3886) {
            while (1) {
                Bool _wcond_Bool_3876 = U32_lt(_rc_U32_3875, _re_U32_3875);
                (void)_wcond_Bool_3876;
                if (_wcond_Bool_3876) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3875);
                U32_inc(&_rc_U32_3875);
                U32 hoisted__U64_3877 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3877;
                void *hoisted__v_3878 = ptr_add(self->data, hoisted__U64_3877);
                (void)hoisted__v_3878;
                (void)hoisted__v_3878;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3878);
                U32 hoisted__U64_3879 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3879;
                void *hoisted__v_3880 = ptr_add(new_data, hoisted__U64_3879);
                (void)hoisted__v_3880;
                (void)hoisted__v_3880;
                memcpy(hoisted__v_3880, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3881 = U32_gt(_rc_U32_3875, _re_U32_3875);
                (void)_wcond_Bool_3881;
                if (_wcond_Bool_3881) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3875);
                U32_dec(&_rc_U32_3875);
                U32 hoisted__U64_3882 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3882;
                void *hoisted__v_3883 = ptr_add(self->data, hoisted__U64_3882);
                (void)hoisted__v_3883;
                (void)hoisted__v_3883;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3883);
                U32 hoisted__U64_3884 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3884;
                void *hoisted__v_3885 = ptr_add(new_data, hoisted__U64_3884);
                (void)hoisted__v_3885;
                (void)hoisted__v_3885;
                memcpy(hoisted__v_3885, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3888 = malloc(sizeof(Array));
    hoisted__Array_3888->data = new_data;
    hoisted__Array_3888->cap = self->cap;
    hoisted__Array_3888->elem_size = self->elem_size;
    hoisted__Array_3888->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3888->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3888;
    return hoisted__Array_3888;
}

U32 Array_size(void) {
    U32 hoisted__U32_3889 = 32;
    (void)hoisted__U32_3889;
    return hoisted__U32_3889;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4253 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4253;
    U32 hoisted__U32_4254 = 3;
    (void)hoisted__U32_4254;
    Array *_va_Array_148 = Array_new(hoisted__Type_4253, hoisted__U32_4254);
    (void)_va_Array_148;
    Type_delete(hoisted__Type_4253, 1);
    U32 hoisted__U32_4255 = 0;
    (void)hoisted__U32_4255;
    Str *hoisted__Str_4256 = Str_clone(loc_str);
    (void)hoisted__Str_4256;
    Array_set(_va_Array_148, hoisted__U32_4255, hoisted__Str_4256);
    U32 hoisted__U32_4257 = 1;
    (void)hoisted__U32_4257;
    Str hoisted__Str_4258 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4258;
    Array_set(_va_Array_148, hoisted__U32_4257, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4258; _oa; }));
    Array *hoisted__Array_4259 = Array_clone(parts);
    (void)hoisted__Array_4259;
    U32 hoisted__U32_4260 = 2;
    (void)hoisted__U32_4260;
    Str *hoisted__Str_4261 = format(hoisted__Array_4259);
    (void)hoisted__Str_4261;
    Array_set(_va_Array_148, hoisted__U32_4260, hoisted__Str_4261);
    Array_delete(parts, 1);
    println(_va_Array_148);
    I64 hoisted__I64_4262 = 1;
    (void)hoisted__I64_4262;
    exit(hoisted__I64_4262);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4272 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4272;
    U32 hoisted__U32_4273 = 1;
    (void)hoisted__U32_4273;
    Array *_va_Array_150 = Array_new(hoisted__Type_4272, hoisted__U32_4273);
    (void)_va_Array_150;
    Type_delete(hoisted__Type_4272, 1);
    U32 hoisted__U32_4274 = 0;
    (void)hoisted__U32_4274;
    Str hoisted__Str_4275 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4275;
    Array_set(_va_Array_150, hoisted__U32_4274, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4275; _oa; }));
    panic(loc_str, _va_Array_150);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4281 = not(cond);
    (void)hoisted__Bool_4281;
    if (hoisted__Bool_4281) {
        Type *hoisted__Type_4277 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4277;
        U32 hoisted__U32_4278 = 1;
        (void)hoisted__U32_4278;
        Array *_va_Array_151 = Array_new(hoisted__Type_4277, hoisted__U32_4278);
        (void)_va_Array_151;
        Type_delete(hoisted__Type_4277, 1);
        U32 hoisted__U32_4279 = 0;
        (void)hoisted__U32_4279;
        Str hoisted__Str_4280 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4280;
        Array_set(_va_Array_151, hoisted__U32_4279, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4280; _oa; }));
        panic(loc_str, _va_Array_151);
    }
    Bool hoisted__Bool_4282 = 1;
    (void)hoisted__Bool_4282;
    return hoisted__Bool_4282;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4305 = I64_neq(a, b);
    (void)hoisted__Bool_4305;
    if (hoisted__Bool_4305) {
        Type *hoisted__Type_4293 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4293;
        U32 hoisted__U32_4294 = 5;
        (void)hoisted__U32_4294;
        Array *_va_Array_153 = Array_new(hoisted__Type_4293, hoisted__U32_4294);
        (void)_va_Array_153;
        Type_delete(hoisted__Type_4293, 1);
        U32 hoisted__U32_4295 = 0;
        (void)hoisted__U32_4295;
        Str hoisted__Str_4296 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4296;
        Array_set(_va_Array_153, hoisted__U32_4295, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4296; _oa; }));
        U32 hoisted__U32_4297 = 1;
        (void)hoisted__U32_4297;
        Str *hoisted__Str_4298 = I64_to_str(a);
        (void)hoisted__Str_4298;
        Array_set(_va_Array_153, hoisted__U32_4297, hoisted__Str_4298);
        U32 hoisted__U32_4299 = 2;
        (void)hoisted__U32_4299;
        Str hoisted__Str_4300 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4300;
        Array_set(_va_Array_153, hoisted__U32_4299, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4300; _oa; }));
        U32 hoisted__U32_4301 = 3;
        (void)hoisted__U32_4301;
        Str *hoisted__Str_4302 = I64_to_str(b);
        (void)hoisted__Str_4302;
        Array_set(_va_Array_153, hoisted__U32_4301, hoisted__Str_4302);
        U32 hoisted__U32_4303 = 4;
        (void)hoisted__U32_4303;
        Str hoisted__Str_4304 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4304;
        Array_set(_va_Array_153, hoisted__U32_4303, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4304; _oa; }));
        panic(loc_str, _va_Array_153);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4319 = Str_eq(a, b);
    (void)hoisted__Bool_4319;
    Bool hoisted__Bool_4320 = not(hoisted__Bool_4319);
    (void)hoisted__Bool_4320;
    if (hoisted__Bool_4320) {
        Type *hoisted__Type_4307 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4307;
        U32 hoisted__U32_4308 = 5;
        (void)hoisted__U32_4308;
        Array *_va_Array_154 = Array_new(hoisted__Type_4307, hoisted__U32_4308);
        (void)_va_Array_154;
        Type_delete(hoisted__Type_4307, 1);
        U32 hoisted__U32_4309 = 0;
        (void)hoisted__U32_4309;
        Str hoisted__Str_4310 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4310;
        Array_set(_va_Array_154, hoisted__U32_4309, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4310; _oa; }));
        U32 hoisted__U32_4311 = 1;
        (void)hoisted__U32_4311;
        Str *hoisted__Str_4312 = Str_clone(a);
        (void)hoisted__Str_4312;
        Array_set(_va_Array_154, hoisted__U32_4311, hoisted__Str_4312);
        U32 hoisted__U32_4313 = 2;
        (void)hoisted__U32_4313;
        Str hoisted__Str_4314 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4314;
        Array_set(_va_Array_154, hoisted__U32_4313, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4314; _oa; }));
        U32 hoisted__U32_4315 = 3;
        (void)hoisted__U32_4315;
        Str *hoisted__Str_4316 = Str_clone(b);
        (void)hoisted__Str_4316;
        Array_set(_va_Array_154, hoisted__U32_4315, hoisted__Str_4316);
        U32 hoisted__U32_4317 = 4;
        (void)hoisted__U32_4317;
        Str hoisted__Str_4318 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4318;
        Array_set(_va_Array_154, hoisted__U32_4317, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4318; _oa; }));
        panic(loc_str, _va_Array_154);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4321 = parts;
        (void)_fc_Array_4321;
        (void)_fc_Array_4321;
        U32 _fi_USize_4321 = 0;
        (void)_fi_USize_4321;
        I64 _forin_err_kind_4321 = 0;
        (void)_forin_err_kind_4321;
        OutOfBounds *_forin_OutOfBounds_4321 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4321->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4321;
        while (1) {
            U32 hoisted__U32_4329 = Array_len(_fc_Array_4321);
            (void)hoisted__U32_4329;
            Bool _wcond_Bool_4322 = U32_lt(_fi_USize_4321, hoisted__U32_4329);
            (void)_wcond_Bool_4322;
            if (_wcond_Bool_4322) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4321, &_fi_USize_4321, &_forin_err_kind_4321, _forin_OutOfBounds_4321);
            I64 hoisted__I64_4330 = 0;
            (void)hoisted__I64_4330;
            Bool hoisted__Bool_4331 = I64_eq(_forin_err_kind_4321, hoisted__I64_4330);
            (void)hoisted__Bool_4331;
            Bool hoisted__Bool_4332 = not(hoisted__Bool_4331);
            (void)hoisted__Bool_4332;
            if (hoisted__Bool_4332) {
                Type *hoisted__Type_4324 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4324;
                U32 hoisted__U32_4325 = 1;
                (void)hoisted__U32_4325;
                Array *_va_Array_155 = Array_new(hoisted__Type_4324, hoisted__U32_4325);
                (void)_va_Array_155;
                Type_delete(hoisted__Type_4324, 1);
                U32 hoisted__U32_4326 = 0;
                (void)hoisted__U32_4326;
                Str hoisted__Str_4327 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4327;
                Array_set(_va_Array_155, hoisted__U32_4326, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4327; _oa; }));
                Str hoisted__Str_4328 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4328;
                panic(&hoisted__Str_4328, _va_Array_155);
                Str_delete(&hoisted__Str_4328, (Bool){0});
            }
            U32 hoisted__U32_4333 = 1;
            (void)hoisted__U32_4333;
            U32 hoisted__U32_4334 = U32_add(_fi_USize_4321, hoisted__U32_4333);
            (void)hoisted__U32_4334;
            _fi_USize_4321 = hoisted__U32_4334;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4321, 1);
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
    Str hoisted__Str_4640 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4640;
    I64 hoisted__I64_4641 = 3;
    (void)hoisted__I64_4641;
    assert_eq(&hoisted__Str_4640, result, hoisted__I64_4641);
    Str_delete(&hoisted__Str_4640, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4648 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4648;
    I64 hoisted__I64_4649 = 15;
    (void)hoisted__I64_4649;
    assert_eq(&hoisted__Str_4648, result, hoisted__I64_4649);
    Str_delete(&hoisted__Str_4648, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4656 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4656;
    I64 hoisted__I64_4657 = 26;
    (void)hoisted__I64_4657;
    assert_eq(&hoisted__Str_4656, result, hoisted__I64_4657);
    Str_delete(&hoisted__Str_4656, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4660 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4660;
    Str hoisted__Str_4661 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4661;
    assert_eq_str(&hoisted__Str_4660, &result, &hoisted__Str_4661);
    Str_delete(&hoisted__Str_4660, (Bool){0});
    Str_delete(&hoisted__Str_4661, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4992 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4992;
    assert_eq_str(&hoisted__Str_4992, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4992, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4993 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4993;
    assert_eq_str(&hoisted__Str_4993, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4993, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4995 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4995;
    I64 hoisted__I64_4996 = 8;
    (void)hoisted__I64_4996;
    assert_eq(&hoisted__Str_4995, result, hoisted__I64_4996);
    Str_delete(&hoisted__Str_4995, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4999 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4999;
    Bool hoisted__Bool_5000 = 1;
    (void)hoisted__Bool_5000;
    assert(&hoisted__Str_4999, hoisted__Bool_5000);
    Str_delete(&hoisted__Str_4999, (Bool){0});
    Str hoisted__Str_5003 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5003;
    Bool hoisted__Bool_5004 = 1;
    (void)hoisted__Bool_5004;
    assert(&hoisted__Str_5003, hoisted__Bool_5004);
    Str_delete(&hoisted__Str_5003, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_5009 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5009;
    Str hoisted__Str_5010 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5010;
    Str hoisted__Str_5011 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5011;
    assert_eq_str(&hoisted__Str_5009, &hoisted__Str_5010, &hoisted__Str_5011);
    Str_delete(&hoisted__Str_5009, (Bool){0});
    Str_delete(&hoisted__Str_5010, (Bool){0});
    Str_delete(&hoisted__Str_5011, (Bool){0});
    Str hoisted__Str_5014 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5014;
    Str hoisted__Str_5015 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5015;
    Str hoisted__Str_5016 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5016;
    assert_eq_str(&hoisted__Str_5014, &hoisted__Str_5015, &hoisted__Str_5016);
    Str_delete(&hoisted__Str_5014, (Bool){0});
    Str_delete(&hoisted__Str_5015, (Bool){0});
    Str_delete(&hoisted__Str_5016, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_5021 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_5021;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_5021;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_5022 = 0;
    (void)hoisted__U32_5022;
    U64 hoisted__U64_5023 = ((U64 (*)(CfVec2 *, U32))(void *)hasher)(self, hoisted__U32_5022);
    (void)hoisted__U64_5023;
    return hoisted__U64_5023;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_5024 = 16;
    (void)hoisted__U32_5024;
    return hoisted__U32_5024;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_5025 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5025;
    I64 hoisted__I64_5026 = 42;
    (void)hoisted__I64_5026;
    assert_eq(&hoisted__Str_5025, v.x, hoisted__I64_5026);
    Str_delete(&hoisted__Str_5025, (Bool){0});
    Str hoisted__Str_5027 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5027;
    I64 hoisted__I64_5028 = 99;
    (void)hoisted__I64_5028;
    assert_eq(&hoisted__Str_5027, v.y, hoisted__I64_5028);
    Str_delete(&hoisted__Str_5027, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_5031 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5031;
    I64 hoisted__I64_5032 = 10;
    (void)hoisted__I64_5032;
    assert_eq(&hoisted__Str_5031, p.x, hoisted__I64_5032);
    Str_delete(&hoisted__Str_5031, (Bool){0});
    Str hoisted__Str_5033 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5033;
    I64 hoisted__I64_5034 = 20;
    (void)hoisted__I64_5034;
    assert_eq(&hoisted__Str_5033, p.y, hoisted__I64_5034);
    Str_delete(&hoisted__Str_5033, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_5040 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_5040;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_5040;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_5041 = 0;
    (void)hoisted__U32_5041;
    U64 hoisted__U64_5042 = ((U64 (*)(CfRect *, U32))(void *)hasher)(self, hoisted__U32_5041);
    (void)hoisted__U64_5042;
    return hoisted__U64_5042;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_5043 = 32;
    (void)hoisted__U32_5043;
    return hoisted__U32_5043;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_5044 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5044;
    I64 hoisted__I64_5045 = 5;
    (void)hoisted__I64_5045;
    assert_eq(&hoisted__Str_5044, r.top_left.x, hoisted__I64_5045);
    Str_delete(&hoisted__Str_5044, (Bool){0});
    Str hoisted__Str_5046 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5046;
    I64 hoisted__I64_5047 = 10;
    (void)hoisted__I64_5047;
    assert_eq(&hoisted__Str_5046, r.top_left.y, hoisted__I64_5047);
    Str_delete(&hoisted__Str_5046, (Bool){0});
    Str hoisted__Str_5048 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5048;
    I64 hoisted__I64_5049 = 100;
    (void)hoisted__I64_5049;
    assert_eq(&hoisted__Str_5048, r.bottom_right.x, hoisted__I64_5049);
    Str_delete(&hoisted__Str_5048, (Bool){0});
    Str hoisted__Str_5050 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5050;
    I64 hoisted__I64_5051 = 200;
    (void)hoisted__I64_5051;
    assert_eq(&hoisted__Str_5050, r.bottom_right.y, hoisted__I64_5051);
    Str_delete(&hoisted__Str_5050, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_5053 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_5053;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_5053;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_5054 = 0;
    (void)hoisted__U32_5054;
    U64 hoisted__U64_5055 = ((U64 (*)(CfVec3f *, U32))(void *)hasher)(self, hoisted__U32_5054);
    (void)hoisted__U64_5055;
    return hoisted__U64_5055;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_5056 = 12;
    (void)hoisted__U32_5056;
    return hoisted__U32_5056;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str hoisted__Str_5060 = (Str){.c_str = (void *)"test/constfold.til:185:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5060;
    Str *hoisted__Str_5061 = F32_to_str(v.x);
    (void)hoisted__Str_5061;
    Str hoisted__Str_5062 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5062;
    assert_eq_str(&hoisted__Str_5060, hoisted__Str_5061, &hoisted__Str_5062);
    Str_delete(&hoisted__Str_5060, (Bool){0});
    Str_delete(hoisted__Str_5061, 1);
    Str_delete(&hoisted__Str_5062, (Bool){0});
    Str hoisted__Str_5063 = (Str){.c_str = (void *)"test/constfold.til:186:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5063;
    Str *hoisted__Str_5064 = F32_to_str(v.y);
    (void)hoisted__Str_5064;
    Str hoisted__Str_5065 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5065;
    assert_eq_str(&hoisted__Str_5063, hoisted__Str_5064, &hoisted__Str_5065);
    Str_delete(&hoisted__Str_5063, (Bool){0});
    Str_delete(hoisted__Str_5064, 1);
    Str_delete(&hoisted__Str_5065, (Bool){0});
    Str hoisted__Str_5066 = (Str){.c_str = (void *)"test/constfold.til:187:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5066;
    Str *hoisted__Str_5067 = F32_to_str(v.z);
    (void)hoisted__Str_5067;
    Str hoisted__Str_5068 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5068;
    assert_eq_str(&hoisted__Str_5066, hoisted__Str_5067, &hoisted__Str_5068);
    Str_delete(&hoisted__Str_5066, (Bool){0});
    Str_delete(hoisted__Str_5067, 1);
    Str_delete(&hoisted__Str_5068, (Bool){0});
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
    Bool hoisted__Bool_5073 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5073;
    if (hoisted__Bool_5073) {
        Bool hoisted__Bool_5070 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_5070;
        { Bool _ret_val = hoisted__Bool_5070;
                return _ret_val; }
    }
    Bool hoisted__Bool_5074 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5074;
    if (hoisted__Bool_5074) {
        Bool hoisted__Bool_5071 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_5071;
        { Bool _ret_val = hoisted__Bool_5071;
                return _ret_val; }
    }
    Bool hoisted__Bool_5075 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_5075;
    if (hoisted__Bool_5075) {
        Bool hoisted__Bool_5072 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_5072;
        { Bool _ret_val = hoisted__Bool_5072;
                return _ret_val; }
    }
    Bool hoisted__Bool_5076 = 0;
    (void)hoisted__Bool_5076;
    return hoisted__Bool_5076;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_5084 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5084;
    if (hoisted__Bool_5084) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_5085 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5085;
    if (hoisted__Bool_5085) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_5086 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_5086;
    if (hoisted__Bool_5086) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_5087 = (Str){.c_str = (void *)"Color.clone:192:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5087;
    UNREACHABLE(&hoisted__Str_5087);
    Str_delete(&hoisted__Str_5087, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_5088 = 4;
    (void)hoisted__U32_5088;
    return hoisted__U32_5088;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_5089 = (Str){.c_str = (void *)"test/constfold.til:197:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5089;
    Bool hoisted__Bool_5090 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5090;
    assert(&hoisted__Str_5089, hoisted__Bool_5090);
    Str_delete(&hoisted__Str_5089, (Bool){0});
    Bool hoisted__Bool_5091 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5091;
    Str hoisted__Str_5092 = (Str){.c_str = (void *)"test/constfold.til:198:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5092;
    Bool hoisted__Bool_5093 = not(hoisted__Bool_5091);
    (void)hoisted__Bool_5093;
    assert(&hoisted__Str_5092, hoisted__Bool_5093);
    Str_delete(&hoisted__Str_5092, (Bool){0});
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
    Bool hoisted__Bool_5094 = is(self, other);
    (void)hoisted__Bool_5094;
    return hoisted__Bool_5094;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_5112 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5112;
    if (hoisted__Bool_5112) {
        I64 *hoisted__I64_5108 = get_payload(self);
        (void)hoisted__I64_5108;
        (void)hoisted__I64_5108;
        Bool hoisted__Bool_5109 = 0;
        (void)hoisted__Bool_5109;
        I64_delete(hoisted__I64_5108, hoisted__Bool_5109);
    }
    Bool hoisted__Bool_5113 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5113;
    if (hoisted__Bool_5113) {
        Str *hoisted__Str_5110 = get_payload(self);
        (void)hoisted__Str_5110;
        (void)hoisted__Str_5110;
        Bool hoisted__Bool_5111 = 0;
        (void)hoisted__Bool_5111;
        Str_delete(hoisted__Str_5110, hoisted__Bool_5111);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_5142 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5142;
    if (hoisted__Bool_5142) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_5139 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_5139;
        { Token * _ret_val = hoisted__Token_5139;
                return _ret_val; }
    }
    Bool hoisted__Bool_5143 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5143;
    if (hoisted__Bool_5143) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_5140 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_5140;
        Token *hoisted__Token_5141 = Token_Name(hoisted__Str_5140);
        (void)hoisted__Token_5141;
        { Token * _ret_val = hoisted__Token_5141;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_5144 = 24;
    (void)hoisted__U32_5144;
    return hoisted__U32_5144;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_5146 = (Str){.c_str = (void *)"test/constfold.til:206:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5146;
    Bool hoisted__Bool_5147 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5147;
    assert(&hoisted__Str_5146, hoisted__Bool_5147);
    Str_delete(&hoisted__Str_5146, (Bool){0});
    Bool hoisted__Bool_5148 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5148;
    Str hoisted__Str_5149 = (Str){.c_str = (void *)"test/constfold.til:207:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5149;
    Bool hoisted__Bool_5150 = not(hoisted__Bool_5148);
    (void)hoisted__Bool_5150;
    assert(&hoisted__Str_5149, hoisted__Bool_5150);
    Str_delete(&hoisted__Str_5149, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_5151 = (Str){.c_str = (void *)"test/constfold.til:216:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5151;
    Bool hoisted__Bool_5152 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5152;
    assert(&hoisted__Str_5151, hoisted__Bool_5152);
    Str_delete(&hoisted__Str_5151, (Bool){0});
    Bool hoisted__Bool_5153 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5153;
    Str hoisted__Str_5154 = (Str){.c_str = (void *)"test/constfold.til:217:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5154;
    Bool hoisted__Bool_5155 = not(hoisted__Bool_5153);
    (void)hoisted__Bool_5155;
    assert(&hoisted__Str_5154, hoisted__Bool_5155);
    Str_delete(&hoisted__Str_5154, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_5158 = (Str){.c_str = (void *)"test/constfold.til:228:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5158;
    Bool hoisted__Bool_5159 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5159;
    assert(&hoisted__Str_5158, hoisted__Bool_5159);
    Str_delete(&hoisted__Str_5158, (Bool){0});
    Bool hoisted__Bool_5160 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5160;
    Str hoisted__Str_5161 = (Str){.c_str = (void *)"test/constfold.til:229:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5161;
    Bool hoisted__Bool_5162 = not(hoisted__Bool_5160);
    (void)hoisted__Bool_5162;
    assert(&hoisted__Str_5161, hoisted__Bool_5162);
    Str_delete(&hoisted__Str_5161, (Bool){0});
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
Bool U32_neq_dyn(void *_a0, void *_a1) {
    return U32_neq(*(U32 *)_a0, *(U32 *)_a1);
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)U32_neq_dyn;
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
    static Str _dts_0 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_1 = (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_2 = (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_3 = (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_4 = (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_5 = (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_6 = (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_7 = (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_8 = (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_9 = (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_10 = (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_11 = (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_12 = (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_13 = (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_14 = (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_15 = (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_STATIC};
    static Str _dts_16 = (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_STATIC};
    switch (type->tag) {
    case Type_TAG_Unknown: return &_dts_0;
    case Type_TAG_None: return &_dts_0;
    case Type_TAG_Struct: return Str_clone(&type->data.Struct);
    case Type_TAG_StructDef: return &_dts_1;
    case Type_TAG_Enum: return Str_clone(&type->data.Enum);
    case Type_TAG_EnumDef: return &_dts_2;
    case Type_TAG_FuncDef: return &_dts_3;
    case Type_TAG_FuncPtr: return &_dts_4;
    case Type_TAG_Dynamic: return &_dts_5;
    case Type_TAG_Custom: return Str_clone(&type->data.Custom);
    case Type_TAG_Primitive:
        switch (type->data.Primitive.tag) {
        case Primitive_TAG_I16: return &_dts_6;
        case Primitive_TAG_U16: return &_dts_7;
        case Primitive_TAG_I8: return &_dts_8;
        case Primitive_TAG_U8: return &_dts_9;
        case Primitive_TAG_U32: return &_dts_10;
        case Primitive_TAG_I32: return &_dts_11;
        case Primitive_TAG_U64: return &_dts_12;
        case Primitive_TAG_I64: return &_dts_13;
        case Primitive_TAG_F32: return &_dts_14;
        case Primitive_TAG_Bool: return &_dts_15;
        }
        break;
    case Type_TAG_FuncPtrSig: return Str_clone(&type->data.FuncPtrSig);
    default: break;
    }
    return &_dts_16;
}

int main(void) {
    CAP_LIT = 4294967295;
    CAP_VIEW = 4294967294;
    CAP_STATIC = 4294967293;
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
