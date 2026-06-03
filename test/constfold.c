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
    U32 hoisted__U32_216 = 0;
    (void)hoisted__U32_216;
    U64 hoisted__U64_217 = ((U64 (*)(U32 *, U32))(void *)hasher)(&self, hoisted__U32_216);
    (void)hoisted__U64_217;
    return hoisted__U64_217;
}

Bool U32_lt(U32 a, U32 b) {
    I64 hoisted__I64_220 = U32_cmp(a, b);
    (void)hoisted__I64_220;
    I64 hoisted__I64_221 = -1;
    (void)hoisted__I64_221;
    Bool hoisted__Bool_222 = I64_eq(hoisted__I64_220, hoisted__I64_221);
    (void)hoisted__Bool_222;
    return hoisted__Bool_222;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_223 = U32_cmp(a, b);
    (void)hoisted__I64_223;
    I64 hoisted__I64_224 = 1;
    (void)hoisted__I64_224;
    Bool hoisted__Bool_225 = I64_eq(hoisted__I64_223, hoisted__I64_224);
    (void)hoisted__Bool_225;
    return hoisted__Bool_225;
}

Bool U32_lte(U32 a, U32 b) {
    Bool hoisted__Bool_228 = U32_gt(a, b);
    (void)hoisted__Bool_228;
    Bool hoisted__Bool_229 = not(hoisted__Bool_228);
    (void)hoisted__Bool_229;
    return hoisted__Bool_229;
}

Bool U32_gte(U32 a, U32 b) {
    Bool hoisted__Bool_230 = U32_lt(a, b);
    (void)hoisted__Bool_230;
    Bool hoisted__Bool_231 = not(hoisted__Bool_230);
    (void)hoisted__Bool_231;
    return hoisted__Bool_231;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_260 = 4;
    (void)hoisted__U32_260;
    return hoisted__U32_260;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_387 = 0;
    (void)hoisted__U32_387;
    U64 hoisted__U64_388 = ((U64 (*)(I32 *, U32))(void *)hasher)(&self, hoisted__U32_387);
    (void)hoisted__U64_388;
    return hoisted__U64_388;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_431 = 1;
    (void)hoisted__U32_431;
    return hoisted__U32_431;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_432 = 0;
    (void)hoisted__U32_432;
    U64 hoisted__U64_433 = ((U64 (*)(I8 *, U32))(void *)hasher)(&self, hoisted__U32_432);
    (void)hoisted__U64_433;
    return hoisted__U64_433;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_462 = 1;
    (void)hoisted__U32_462;
    return hoisted__U32_462;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_536 = 0;
    (void)hoisted__U32_536;
    U64 hoisted__U64_537 = ((U64 (*)(U8 *, U32))(void *)hasher)(&self, hoisted__U32_536);
    (void)hoisted__U64_537;
    return hoisted__U64_537;
}

Str * format(Array * parts) {
    U32 total = 0;
    {
        Array *_fc_Array_826 = parts;
        (void)_fc_Array_826;
        (void)_fc_Array_826;
        U32 _fi_USize_826 = 0;
        (void)_fi_USize_826;
        I64 _forin_err_kind_826 = 0;
        (void)_forin_err_kind_826;
        OutOfBounds *_forin_OutOfBounds_826 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_826->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_826;
        while (1) {
            U32 hoisted__U32_834 = Array_len(_fc_Array_826);
            (void)hoisted__U32_834;
            Bool _wcond_Bool_827 = U32_lt(_fi_USize_826, hoisted__U32_834);
            (void)_wcond_Bool_827;
            if (_wcond_Bool_827) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_826, &_fi_USize_826, &_forin_err_kind_826, _forin_OutOfBounds_826);
            I64 hoisted__I64_835 = 0;
            (void)hoisted__I64_835;
            Bool hoisted__Bool_836 = I64_eq(_forin_err_kind_826, hoisted__I64_835);
            (void)hoisted__Bool_836;
            Bool hoisted__Bool_837 = not(hoisted__Bool_836);
            (void)hoisted__Bool_837;
            if (hoisted__Bool_837) {
                Type *hoisted__Type_829 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_829;
                U32 hoisted__U32_830 = 1;
                (void)hoisted__U32_830;
                Array *_va_Array_24 = Array_new(hoisted__Type_829, hoisted__U32_830);
                (void)_va_Array_24;
                Type_delete(hoisted__Type_829, 1);
                U32 hoisted__U32_831 = 0;
                (void)hoisted__U32_831;
                Str hoisted__Str_832 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_832;
                Array_set(_va_Array_24, hoisted__U32_831, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_832; _oa; }));
                Str hoisted__Str_833 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_833;
                panic(&hoisted__Str_833, _va_Array_24);
                Str_delete(&hoisted__Str_833, (Bool){0});
            }
            U32 hoisted__U32_838 = 1;
            (void)hoisted__U32_838;
            U32 hoisted__U32_839 = U32_add(_fi_USize_826, hoisted__U32_838);
            (void)hoisted__U32_839;
            _fi_USize_826 = hoisted__U32_839;
            U32 hoisted__U32_840 = Str_len(s);
            (void)hoisted__U32_840;
            U32 hoisted__U32_841 = U32_add(total, hoisted__U32_840);
            (void)hoisted__U32_841;
            total = hoisted__U32_841;
        }
        OutOfBounds_delete(_forin_OutOfBounds_826, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array *_fc_Array_842 = parts;
        (void)_fc_Array_842;
        (void)_fc_Array_842;
        U32 _fi_USize_842 = 0;
        (void)_fi_USize_842;
        I64 _forin_err_kind_842 = 0;
        (void)_forin_err_kind_842;
        OutOfBounds *_forin_OutOfBounds_842 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_842->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_842;
        while (1) {
            U32 hoisted__U32_850 = Array_len(_fc_Array_842);
            (void)hoisted__U32_850;
            Bool _wcond_Bool_843 = U32_lt(_fi_USize_842, hoisted__U32_850);
            (void)_wcond_Bool_843;
            if (_wcond_Bool_843) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_842, &_fi_USize_842, &_forin_err_kind_842, _forin_OutOfBounds_842);
            I64 hoisted__I64_851 = 0;
            (void)hoisted__I64_851;
            Bool hoisted__Bool_852 = I64_eq(_forin_err_kind_842, hoisted__I64_851);
            (void)hoisted__Bool_852;
            Bool hoisted__Bool_853 = not(hoisted__Bool_852);
            (void)hoisted__Bool_853;
            if (hoisted__Bool_853) {
                Type *hoisted__Type_845 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_845;
                U32 hoisted__U32_846 = 1;
                (void)hoisted__U32_846;
                Array *_va_Array_25 = Array_new(hoisted__Type_845, hoisted__U32_846);
                (void)_va_Array_25;
                Type_delete(hoisted__Type_845, 1);
                U32 hoisted__U32_847 = 0;
                (void)hoisted__U32_847;
                Str hoisted__Str_848 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_848;
                Array_set(_va_Array_25, hoisted__U32_847, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_848; _oa; }));
                Str hoisted__Str_849 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_849;
                panic(&hoisted__Str_849, _va_Array_25);
                Str_delete(&hoisted__Str_849, (Bool){0});
            }
            U32 hoisted__U32_854 = 1;
            (void)hoisted__U32_854;
            U32 hoisted__U32_855 = U32_add(_fi_USize_842, hoisted__U32_854);
            (void)hoisted__U32_855;
            _fi_USize_842 = hoisted__U32_855;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_842, 1);
    }
    Array_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_862 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_862;
    if (hoisted__Bool_862) {
        Type *hoisted__Type_857 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_857;
        U32 hoisted__U32_858 = 1;
        (void)hoisted__U32_858;
        Array *_va_Array_26 = Array_new(hoisted__Type_857, hoisted__U32_858);
        (void)_va_Array_26;
        Type_delete(hoisted__Type_857, 1);
        U32 hoisted__U32_859 = 0;
        (void)hoisted__U32_859;
        Str hoisted__Str_860 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_860;
        Array_set(_va_Array_26, hoisted__U32_859, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_860; _oa; }));
        Str hoisted__Str_861 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_861;
        panic(&hoisted__Str_861, _va_Array_26);
        Str_delete(&hoisted__Str_861, (Bool){0});
    }
    void *hoisted__v_863 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_863;
    (void)hoisted__v_863;
    return hoisted__v_863;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_873 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_873;
    if (hoisted__Bool_873) {
        min_len = b->count;
    }
    {
        U32 _re_U32_865 = U32_clone(&min_len);
        (void)_re_U32_865;
        U32 _rc_U32_865 = 0;
        (void)_rc_U32_865;
        Bool hoisted__Bool_872 = U32_lte(_rc_U32_865, _re_U32_865);
        (void)hoisted__Bool_872;
        if (hoisted__Bool_872) {
            while (1) {
                Bool _wcond_Bool_866 = U32_lt(_rc_U32_865, _re_U32_865);
                (void)_wcond_Bool_866;
                if (_wcond_Bool_866) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_865);
                U32_inc(&_rc_U32_865);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_867 = 0;
                (void)hoisted__I64_867;
                Bool hoisted__Bool_868 = I64_neq(c, hoisted__I64_867);
                (void)hoisted__Bool_868;
                if (hoisted__Bool_868) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_869 = U32_gt(_rc_U32_865, _re_U32_865);
                (void)_wcond_Bool_869;
                if (_wcond_Bool_869) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_865);
                U32_dec(&_rc_U32_865);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_870 = 0;
                (void)hoisted__I64_870;
                Bool hoisted__Bool_871 = I64_neq(c, hoisted__I64_870);
                (void)hoisted__Bool_871;
                if (hoisted__Bool_871) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_874 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_874;
    return hoisted__I64_874;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_876 = 1;
    (void)hoisted__U32_876;
    U32 hoisted__U64_877 = U32_add(n, hoisted__U32_876);
    (void)hoisted__U64_877;
    void * buf = malloc(hoisted__U64_877);
    I32 hoisted__I32_878 = 0;
    (void)hoisted__I32_878;
    U64 hoisted__U64_879 = 1ULL;
    (void)hoisted__U64_879;
    memset(buf, hoisted__I32_878, hoisted__U64_879);
    I32_delete(&hoisted__I32_878, 0);
    I64 hoisted__I64_880 = 0;
    (void)hoisted__I64_880;
    Str *hoisted__Str_881 = malloc(sizeof(Str));
    hoisted__Str_881->c_str = buf;
    hoisted__Str_881->count = hoisted__I64_880;
    hoisted__Str_881->cap = n;
    (void)hoisted__Str_881;
    return hoisted__Str_881;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_896 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_896;
    if (hoisted__Bool_896) {
        Type *hoisted__Type_885 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_885;
        U32 hoisted__U32_886 = 1;
        (void)hoisted__U32_886;
        Array *_va_Array_27 = Array_new(hoisted__Type_885, hoisted__U32_886);
        (void)_va_Array_27;
        Type_delete(hoisted__Type_885, 1);
        U32 hoisted__U32_887 = 0;
        (void)hoisted__U32_887;
        Str hoisted__Str_888 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_888;
        Array_set(_va_Array_27, hoisted__U32_887, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_888; _oa; }));
        Str hoisted__Str_889 = (Str){.c_str = (void *)"./src/core/str.til:91:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_889;
        panic(&hoisted__Str_889, _va_Array_27);
        Str_delete(&hoisted__Str_889, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_897 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_897;
    if (hoisted__Bool_897) {
        Type *hoisted__Type_891 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_891;
        U32 hoisted__U32_892 = 1;
        (void)hoisted__U32_892;
        Array *_va_Array_28 = Array_new(hoisted__Type_891, hoisted__U32_892);
        (void)_va_Array_28;
        Type_delete(hoisted__Type_891, 1);
        U32 hoisted__U32_893 = 0;
        (void)hoisted__U32_893;
        Str hoisted__Str_894 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_894;
        Array_set(_va_Array_28, hoisted__U32_893, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_894; _oa; }));
        Str hoisted__Str_895 = (Str){.c_str = (void *)"./src/core/str.til:95:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_895;
        panic(&hoisted__Str_895, _va_Array_28);
        Str_delete(&hoisted__Str_895, (Bool){0});
    }
    void *hoisted__v_898 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_898;
    (void)hoisted__v_898;
    memcpy(hoisted__v_898, s->c_str, s->count);
    U32 hoisted__U32_899 = U32_clone(&new_len);
    (void)hoisted__U32_899;
    self->count = hoisted__U32_899;
    void *hoisted__v_900 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_900;
    (void)hoisted__v_900;
    I32 hoisted__I32_901 = 0;
    (void)hoisted__I32_901;
    U64 hoisted__U64_902 = 1ULL;
    (void)hoisted__U64_902;
    memset(hoisted__v_900, hoisted__I32_901, hoisted__U64_902);
    I32_delete(&hoisted__I32_901, 0);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_903 = 1;
    (void)hoisted__U32_903;
    U32 hoisted__U64_904 = U32_add(val->count, hoisted__U32_903);
    (void)hoisted__U64_904;
    void * new_data = malloc(hoisted__U64_904);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_905 = ptr_add(new_data, val->count);
    (void)hoisted__v_905;
    (void)hoisted__v_905;
    I32 hoisted__I32_906 = 0;
    (void)hoisted__I32_906;
    U64 hoisted__U64_907 = 1ULL;
    (void)hoisted__U64_907;
    memset(hoisted__v_905, hoisted__I32_906, hoisted__U64_907);
    I32_delete(&hoisted__I32_906, 0);
    Str *hoisted__Str_908 = malloc(sizeof(Str));
    hoisted__Str_908->c_str = new_data;
    hoisted__Str_908->count = val->count;
    hoisted__Str_908->cap = val->count;
    (void)hoisted__Str_908;
    return hoisted__Str_908;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_909 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_909;
    if (hoisted__Bool_909) {
        free(self->c_str);
    }
    if (call_free) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_1022 = 0;
    (void)hoisted__U32_1022;
    Bool hoisted__Bool_1023 = U32_eq(self->count, hoisted__U32_1022);
    (void)hoisted__Bool_1023;
    return hoisted__Bool_1023;
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_1116 = ((U64 (*)(I8 *, U32))(void *)hasher)(self->c_str, self->count);
    (void)hoisted__U64_1116;
    return hoisted__U64_1116;
}

U32 Str_size(void) {
    U32 hoisted__U32_1240 = 16;
    (void)hoisted__U32_1240;
    return hoisted__U32_1240;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1241 = Str_cmp(a, b);
    (void)hoisted__I64_1241;
    I64 hoisted__I64_1242 = 0;
    (void)hoisted__I64_1242;
    Bool hoisted__Bool_1243 = I64_eq(hoisted__I64_1241, hoisted__I64_1242);
    (void)hoisted__Bool_1243;
    return hoisted__Bool_1243;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1314 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1314->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1314;
    return hoisted__OutOfBounds_1314;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1315 = 0;
    (void)hoisted__Bool_1315;
    Str_delete(&self->msg, hoisted__Bool_1315);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1316 = 0;
    (void)hoisted__U32_1316;
    U64 hoisted__U64_1317 = ((U64 (*)(OutOfBounds *, U32))(void *)hasher)(self, hoisted__U32_1316);
    (void)hoisted__U64_1317;
    return hoisted__U64_1317;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1318 = 16;
    (void)hoisted__U32_1318;
    return hoisted__U32_1318;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1326 = 8;
    (void)hoisted__U32_1326;
    return hoisted__U32_1326;
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1537 = 0;
    (void)hoisted__I64_1537;
    Bool hoisted__Bool_1538 = I64_eq(val, hoisted__I64_1537);
    (void)hoisted__Bool_1538;
    if (hoisted__Bool_1538) {
        U64 hoisted__U64_1501 = 2ULL;
        (void)hoisted__U64_1501;
        void * buf = malloc(hoisted__U64_1501);
        I64 hoisted__I64_1502 = 48;
        (void)hoisted__I64_1502;
        U64 hoisted__U64_1503 = 1ULL;
        (void)hoisted__U64_1503;
        memcpy(buf, &hoisted__I64_1502, hoisted__U64_1503);
        U64 hoisted__U64_1504 = 1ULL;
        (void)hoisted__U64_1504;
        void *hoisted__v_1505 = ptr_add(buf, hoisted__U64_1504);
        (void)hoisted__v_1505;
        (void)hoisted__v_1505;
        I32 hoisted__I32_1506 = 0;
        (void)hoisted__I32_1506;
        U64 hoisted__U64_1507 = 1ULL;
        (void)hoisted__U64_1507;
        memset(hoisted__v_1505, hoisted__I32_1506, hoisted__U64_1507);
        I32_delete(&hoisted__I32_1506, 0);
        I64 hoisted__I64_1508 = 1;
        (void)hoisted__I64_1508;
        I64 hoisted__I64_1509 = 1;
        (void)hoisted__I64_1509;
        Str *hoisted__Str_1510 = malloc(sizeof(Str));
        hoisted__Str_1510->c_str = buf;
        hoisted__Str_1510->count = hoisted__I64_1508;
        hoisted__Str_1510->cap = hoisted__I64_1509;
        (void)hoisted__Str_1510;
        { Str * _ret_val = hoisted__Str_1510;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1539 = 0;
    (void)hoisted__I64_1539;
    Bool hoisted__Bool_1540 = I64_lt(val, hoisted__I64_1539);
    (void)hoisted__Bool_1540;
    if (hoisted__Bool_1540) {
        Bool hoisted__Bool_1511 = 1;
        (void)hoisted__Bool_1511;
        is_neg = hoisted__Bool_1511;
        I64 hoisted__I64_1512 = 0;
        (void)hoisted__I64_1512;
        I64 hoisted__I64_1513 = I64_sub(hoisted__I64_1512, val);
        (void)hoisted__I64_1513;
        v = hoisted__I64_1513;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1515 = 0;
        (void)hoisted__I64_1515;
        Bool _wcond_Bool_1514 = I64_gt(tmp, hoisted__I64_1515);
        (void)_wcond_Bool_1514;
        if (_wcond_Bool_1514) {
        } else {
            break;
        }
        U64 hoisted__U64_1516 = 1ULL;
        (void)hoisted__U64_1516;
        U64 hoisted__U64_1517 = U64_add(ndigits, hoisted__U64_1516);
        (void)hoisted__U64_1517;
        ndigits = hoisted__U64_1517;
        I64 hoisted__I64_1518 = 10;
        (void)hoisted__I64_1518;
        I64 hoisted__I64_1519 = I64_div(tmp, hoisted__I64_1518);
        (void)hoisted__I64_1519;
        tmp = hoisted__I64_1519;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1520 = 1ULL;
        (void)hoisted__U64_1520;
        U64 hoisted__U64_1521 = U64_add(total, hoisted__U64_1520);
        (void)hoisted__U64_1521;
        total = hoisted__U64_1521;
    }
    U64 hoisted__U64_1541 = 1ULL;
    (void)hoisted__U64_1541;
    U64 hoisted__U64_1542 = U64_add(total, hoisted__U64_1541);
    (void)hoisted__U64_1542;
    void * buf = malloc(hoisted__U64_1542);
    if (is_neg) {
        I64 hoisted__I64_1522 = 45;
        (void)hoisted__I64_1522;
        U64 hoisted__U64_1523 = 1ULL;
        (void)hoisted__U64_1523;
        memcpy(buf, &hoisted__I64_1522, hoisted__U64_1523);
    }
    U64 hoisted__U64_1543 = 1ULL;
    (void)hoisted__U64_1543;
    U64 i = U64_sub(total, hoisted__U64_1543);
    while (1) {
        I64 hoisted__I64_1525 = 0;
        (void)hoisted__I64_1525;
        Bool _wcond_Bool_1524 = I64_gt(v, hoisted__I64_1525);
        (void)_wcond_Bool_1524;
        if (_wcond_Bool_1524) {
        } else {
            break;
        }
        I64 hoisted__I64_1526 = 10;
        (void)hoisted__I64_1526;
        I64 hoisted__I64_1527 = I64_mod(v, hoisted__I64_1526);
        (void)hoisted__I64_1527;
        I64 hoisted__I64_1528 = 48;
        (void)hoisted__I64_1528;
        I64 hoisted__I64_1529 = I64_add(hoisted__I64_1527, hoisted__I64_1528);
        (void)hoisted__I64_1529;
        void *hoisted__v_1530 = ptr_add(buf, i);
        (void)hoisted__v_1530;
        (void)hoisted__v_1530;
        U8 hoisted__U8_1531 = I64_to_u8(hoisted__I64_1529);
        (void)hoisted__U8_1531;
        U64 hoisted__U64_1532 = 1ULL;
        (void)hoisted__U64_1532;
        memcpy(hoisted__v_1530, &hoisted__U8_1531, hoisted__U64_1532);
        U8_delete(&hoisted__U8_1531, 0);
        I64 hoisted__I64_1533 = 10;
        (void)hoisted__I64_1533;
        I64 hoisted__I64_1534 = I64_div(v, hoisted__I64_1533);
        (void)hoisted__I64_1534;
        v = hoisted__I64_1534;
        U64 hoisted__U64_1535 = 1ULL;
        (void)hoisted__U64_1535;
        U64 hoisted__U64_1536 = U64_sub(i, hoisted__U64_1535);
        (void)hoisted__U64_1536;
        i = hoisted__U64_1536;
    }
    void *hoisted__v_1544 = ptr_add(buf, total);
    (void)hoisted__v_1544;
    (void)hoisted__v_1544;
    I32 hoisted__I32_1545 = 0;
    (void)hoisted__I32_1545;
    U64 hoisted__U64_1546 = 1ULL;
    (void)hoisted__U64_1546;
    memset(hoisted__v_1544, hoisted__I32_1545, hoisted__U64_1546);
    I32_delete(&hoisted__I32_1545, 0);
    Str *hoisted__Str_1547 = malloc(sizeof(Str));
    hoisted__Str_1547->c_str = buf;
    hoisted__Str_1547->count = total;
    hoisted__Str_1547->cap = total;
    (void)hoisted__Str_1547;
    return hoisted__Str_1547;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1567 = 8;
    (void)hoisted__U32_1567;
    return hoisted__U32_1567;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1698 = 0;
    (void)hoisted__U32_1698;
    U64 hoisted__U64_1699 = ((U64 (*)(I64 *, U32))(void *)hasher)(&self, hoisted__U32_1698);
    (void)hoisted__U64_1699;
    return hoisted__U64_1699;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1702 = I64_cmp(a, b);
    (void)hoisted__I64_1702;
    I64 hoisted__I64_1703 = -1;
    (void)hoisted__I64_1703;
    Bool hoisted__Bool_1704 = I64_eq(hoisted__I64_1702, hoisted__I64_1703);
    (void)hoisted__Bool_1704;
    return hoisted__Bool_1704;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1705 = I64_cmp(a, b);
    (void)hoisted__I64_1705;
    I64 hoisted__I64_1706 = 1;
    (void)hoisted__I64_1706;
    Bool hoisted__Bool_1707 = I64_eq(hoisted__I64_1705, hoisted__I64_1706);
    (void)hoisted__Bool_1707;
    return hoisted__Bool_1707;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1708 = I64_eq(a, b);
    (void)hoisted__Bool_1708;
    Bool hoisted__Bool_1709 = not(hoisted__Bool_1708);
    (void)hoisted__Bool_1709;
    return hoisted__Bool_1709;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1727 = Bool_eq(a, b);
    (void)hoisted__Bool_1727;
    if (hoisted__Bool_1727) {
        I64 hoisted__I64_1725 = 0;
        (void)hoisted__I64_1725;
        { I64 _ret_val = hoisted__I64_1725;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1726 = -1;
        (void)hoisted__I64_1726;
        return hoisted__I64_1726;
    }
    I64 hoisted__I64_1728 = 1;
    (void)hoisted__I64_1728;
    return hoisted__I64_1728;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1729 = 1;
    (void)hoisted__U32_1729;
    return hoisted__U32_1729;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1730 = 0;
    (void)hoisted__U32_1730;
    U64 hoisted__U64_1731 = ((U64 (*)(Bool *, U32))(void *)hasher)(&self, hoisted__U32_1730);
    (void)hoisted__U64_1731;
    return hoisted__U64_1731;
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
    Bool hoisted__Bool_1885 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1885;
    if (hoisted__Bool_1885) {
        Bool hoisted__Bool_1875 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1875;
        { Bool _ret_val = hoisted__Bool_1875;
                return _ret_val; }
    }
    Bool hoisted__Bool_1886 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1886;
    if (hoisted__Bool_1886) {
        Bool hoisted__Bool_1876 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1876;
        { Bool _ret_val = hoisted__Bool_1876;
                return _ret_val; }
    }
    Bool hoisted__Bool_1887 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1887;
    if (hoisted__Bool_1887) {
        Bool hoisted__Bool_1877 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_1877;
        { Bool _ret_val = hoisted__Bool_1877;
                return _ret_val; }
    }
    Bool hoisted__Bool_1888 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1888;
    if (hoisted__Bool_1888) {
        Bool hoisted__Bool_1878 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_1878;
        { Bool _ret_val = hoisted__Bool_1878;
                return _ret_val; }
    }
    Bool hoisted__Bool_1889 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1889;
    if (hoisted__Bool_1889) {
        Bool hoisted__Bool_1879 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_1879;
        { Bool _ret_val = hoisted__Bool_1879;
                return _ret_val; }
    }
    Bool hoisted__Bool_1890 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1890;
    if (hoisted__Bool_1890) {
        Bool hoisted__Bool_1880 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_1880;
        { Bool _ret_val = hoisted__Bool_1880;
                return _ret_val; }
    }
    Bool hoisted__Bool_1891 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1891;
    if (hoisted__Bool_1891) {
        Bool hoisted__Bool_1881 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_1881;
        { Bool _ret_val = hoisted__Bool_1881;
                return _ret_val; }
    }
    Bool hoisted__Bool_1892 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1892;
    if (hoisted__Bool_1892) {
        Bool hoisted__Bool_1882 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_1882;
        { Bool _ret_val = hoisted__Bool_1882;
                return _ret_val; }
    }
    Bool hoisted__Bool_1893 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1893;
    if (hoisted__Bool_1893) {
        Bool hoisted__Bool_1883 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_1883;
        { Bool _ret_val = hoisted__Bool_1883;
                return _ret_val; }
    }
    Bool hoisted__Bool_1894 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1894;
    if (hoisted__Bool_1894) {
        Bool hoisted__Bool_1884 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_1884;
        { Bool _ret_val = hoisted__Bool_1884;
                return _ret_val; }
    }
    Bool hoisted__Bool_1895 = 0;
    (void)hoisted__Bool_1895;
    return hoisted__Bool_1895;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1917 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1917;
    if (hoisted__Bool_1917) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1918 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1918;
    if (hoisted__Bool_1918) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_1919 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1919;
    if (hoisted__Bool_1919) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_1920 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1920;
    if (hoisted__Bool_1920) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1921 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1921;
    if (hoisted__Bool_1921) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1922 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1922;
    if (hoisted__Bool_1922) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1923 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1923;
    if (hoisted__Bool_1923) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1924 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1924;
    if (hoisted__Bool_1924) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1925 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1925;
    if (hoisted__Bool_1925) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1926 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1926;
    if (hoisted__Bool_1926) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_1927 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1927;
    UNREACHABLE(&hoisted__Str_1927);
    Str_delete(&hoisted__Str_1927, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1928 = 4;
    (void)hoisted__U32_1928;
    return hoisted__U32_1928;
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
    Bool hoisted__Bool_1974 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1974;
    if (hoisted__Bool_1974) {
        Str *hoisted__Str_1966 = get_payload(self);
        (void)hoisted__Str_1966;
        (void)hoisted__Str_1966;
        Bool hoisted__Bool_1967 = 0;
        (void)hoisted__Bool_1967;
        Str_delete(hoisted__Str_1966, hoisted__Bool_1967);
    }
    Bool hoisted__Bool_1975 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1975;
    if (hoisted__Bool_1975) {
        Str *hoisted__Str_1968 = get_payload(self);
        (void)hoisted__Str_1968;
        (void)hoisted__Str_1968;
        Bool hoisted__Bool_1969 = 0;
        (void)hoisted__Bool_1969;
        Str_delete(hoisted__Str_1968, hoisted__Bool_1969);
    }
    Bool hoisted__Bool_1976 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1976;
    if (hoisted__Bool_1976) {
        Str *hoisted__Str_1970 = get_payload(self);
        (void)hoisted__Str_1970;
        (void)hoisted__Str_1970;
        Bool hoisted__Bool_1971 = 0;
        (void)hoisted__Bool_1971;
        Str_delete(hoisted__Str_1970, hoisted__Bool_1971);
    }
    Bool hoisted__Bool_1977 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1977;
    if (hoisted__Bool_1977) {
        Primitive *hoisted__Primitive_1972 = get_payload(self);
        (void)hoisted__Primitive_1972;
        (void)hoisted__Primitive_1972;
        Bool hoisted__Bool_1973 = 0;
        (void)hoisted__Bool_1973;
        Primitive_delete(hoisted__Primitive_1972, hoisted__Bool_1973);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2043 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2043;
    if (hoisted__Bool_2043) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2044 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2044;
    if (hoisted__Bool_2044) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2045 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2045;
    if (hoisted__Bool_2045) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2037 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2037;
        Type *hoisted__Type_2038 = Type_Struct(hoisted__Str_2037);
        (void)hoisted__Type_2038;
        { Type * _ret_val = hoisted__Type_2038;
                return _ret_val; }
    }
    Bool hoisted__Bool_2046 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2046;
    if (hoisted__Bool_2046) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2047 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2047;
    if (hoisted__Bool_2047) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2039 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2039;
        Type *hoisted__Type_2040 = Type_Enum(hoisted__Str_2039);
        (void)hoisted__Type_2040;
        { Type * _ret_val = hoisted__Type_2040;
                return _ret_val; }
    }
    Bool hoisted__Bool_2048 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2048;
    if (hoisted__Bool_2048) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2049 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2049;
    if (hoisted__Bool_2049) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2050 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2050;
    if (hoisted__Bool_2050) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2051 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2051;
    if (hoisted__Bool_2051) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2052 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2052;
    if (hoisted__Bool_2052) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2041 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2041;
        Type *hoisted__Type_2042 = Type_Custom(hoisted__Str_2041);
        (void)hoisted__Type_2042;
        { Type * _ret_val = hoisted__Type_2042;
                return _ret_val; }
    }
    Primitive *_clone_payload_Primitive_10 = get_payload(self);
    (void)_clone_payload_Primitive_10;
    (void)_clone_payload_Primitive_10;
    Primitive hoisted__Primitive_2053 = DEREF(_clone_payload_Primitive_10);
    (void)hoisted__Primitive_2053;
    Type *hoisted__Type_2054 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2053; _oa; }));
    (void)hoisted__Type_2054;
    return hoisted__Type_2054;
}

U32 Type_size(void) {
    U32 hoisted__U32_2055 = 24;
    (void)hoisted__U32_2055;
    return hoisted__U32_2055;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3751 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3751;
    if (hoisted__Bool_3751) {
        Type *hoisted__Type_3746 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3746;
        U32 hoisted__U32_3747 = 1;
        (void)hoisted__U32_3747;
        Array *_va_Array_110 = Array_new(hoisted__Type_3746, hoisted__U32_3747);
        (void)_va_Array_110;
        Type_delete(hoisted__Type_3746, 1);
        U32 hoisted__U32_3748 = 0;
        (void)hoisted__U32_3748;
        Str hoisted__Str_3749 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3749;
        Array_set(_va_Array_110, hoisted__U32_3748, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3749; _oa; }));
        Str hoisted__Str_3750 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3750;
        panic(&hoisted__Str_3750, _va_Array_110);
        Str_delete(&hoisted__Str_3750, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3752 = calloc(cap, elem_size);
    (void)hoisted__v_3752;
    void * hoisted__v_3753 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3753;
    void * hoisted__v_3754 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3754;
    Array *hoisted__Array_3755 = malloc(sizeof(Array));
    hoisted__Array_3755->data = hoisted__v_3752;
    hoisted__Array_3755->cap = cap;
    hoisted__Array_3755->elem_size = elem_size;
    hoisted__Array_3755->elem_clone = hoisted__v_3753;
    hoisted__Array_3755->elem_delete = hoisted__v_3754;
    (void)hoisted__Array_3755;
    return hoisted__Array_3755;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3756 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3756;
    Str_delete(elem_type, 1);
    return hoisted__Array_3756;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3777 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3777;
    if (hoisted__Bool_3777) {
        Type *hoisted__Type_3758 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3758;
        U32 hoisted__U32_3759 = 6;
        (void)hoisted__U32_3759;
        Array *_va_Array_111 = Array_new(hoisted__Type_3758, hoisted__U32_3759);
        (void)_va_Array_111;
        Type_delete(hoisted__Type_3758, 1);
        U32 hoisted__U32_3760 = 0;
        (void)hoisted__U32_3760;
        Str hoisted__Str_3761 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3761;
        Array_set(_va_Array_111, hoisted__U32_3760, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3761; _oa; }));
        U32 hoisted__U32_3762 = 1;
        (void)hoisted__U32_3762;
        Str hoisted__Str_3763 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3763;
        Array_set(_va_Array_111, hoisted__U32_3762, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3763; _oa; }));
        U32 hoisted__U32_3764 = 2;
        (void)hoisted__U32_3764;
        Str *hoisted__Str_3765 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3765;
        Array_set(_va_Array_111, hoisted__U32_3764, hoisted__Str_3765);
        U32 hoisted__U32_3766 = 3;
        (void)hoisted__U32_3766;
        Str hoisted__Str_3767 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3767;
        Array_set(_va_Array_111, hoisted__U32_3766, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3767; _oa; }));
        U32 hoisted__U32_3768 = 4;
        (void)hoisted__U32_3768;
        Str *hoisted__Str_3769 = U32_to_str(self->cap);
        (void)hoisted__Str_3769;
        Array_set(_va_Array_111, hoisted__U32_3768, hoisted__Str_3769);
        U32 hoisted__U32_3770 = 5;
        (void)hoisted__U32_3770;
        Str hoisted__Str_3771 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3771;
        Array_set(_va_Array_111, hoisted__U32_3770, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3771; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3772 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_111); hoisted__OutOfBounds_3772->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3772;
        U32 hoisted__U32_3773 = 16;
        (void)hoisted__U32_3773;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3772, hoisted__U32_3773);
        OutOfBounds_delete(hoisted__OutOfBounds_3772, 1);
        I64 hoisted__I64_3774 = 3;
        (void)hoisted__I64_3774;
        *_err_kind = hoisted__I64_3774;
    }
    I64 hoisted__I64_3778 = 0;
    (void)hoisted__I64_3778;
    Bool hoisted__Bool_3779 = I64_eq(DEREF(_err_kind), hoisted__I64_3778);
    (void)hoisted__Bool_3779;
    if (hoisted__Bool_3779) {
        U32 hoisted__U64_3775 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3775;
        void *hoisted__v_3776 = ptr_add(self->data, hoisted__U64_3775);
        (void)hoisted__v_3776;
        (void)hoisted__v_3776;
        { void * _ret_val = hoisted__v_3776;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3794 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3794;
    if (hoisted__Bool_3794) {
        Type *hoisted__Type_3781 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3781;
        U32 hoisted__U32_3782 = 5;
        (void)hoisted__U32_3782;
        Array *_va_Array_112 = Array_new(hoisted__Type_3781, hoisted__U32_3782);
        (void)_va_Array_112;
        Type_delete(hoisted__Type_3781, 1);
        U32 hoisted__U32_3783 = 0;
        (void)hoisted__U32_3783;
        Str hoisted__Str_3784 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3784;
        Array_set(_va_Array_112, hoisted__U32_3783, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3784; _oa; }));
        U32 hoisted__U32_3785 = 1;
        (void)hoisted__U32_3785;
        Str *hoisted__Str_3786 = U32_to_str(i);
        (void)hoisted__Str_3786;
        Array_set(_va_Array_112, hoisted__U32_3785, hoisted__Str_3786);
        U32 hoisted__U32_3787 = 2;
        (void)hoisted__U32_3787;
        Str hoisted__Str_3788 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3788;
        Array_set(_va_Array_112, hoisted__U32_3787, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3788; _oa; }));
        U32 hoisted__U32_3789 = 3;
        (void)hoisted__U32_3789;
        Str *hoisted__Str_3790 = U32_to_str(self->cap);
        (void)hoisted__Str_3790;
        Array_set(_va_Array_112, hoisted__U32_3789, hoisted__Str_3790);
        U32 hoisted__U32_3791 = 4;
        (void)hoisted__U32_3791;
        Str hoisted__Str_3792 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3792;
        Array_set(_va_Array_112, hoisted__U32_3791, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3792; _oa; }));
        Str hoisted__Str_3793 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3793;
        panic(&hoisted__Str_3793, _va_Array_112);
        Str_delete(&hoisted__Str_3793, (Bool){0});
    }
    U32 hoisted__U64_3795 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3795;
    void *hoisted__v_3796 = ptr_add(self->data, hoisted__U64_3795);
    (void)hoisted__v_3796;
    (void)hoisted__v_3796;
    Bool hoisted__Bool_3797 = 0;
    (void)hoisted__Bool_3797;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3796, hoisted__Bool_3797);
    U32 hoisted__U64_3798 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3798;
    void *hoisted__v_3799 = ptr_add(self->data, hoisted__U64_3798);
    (void)hoisted__v_3799;
    (void)hoisted__v_3799;
    memcpy(hoisted__v_3799, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3800 = self->cap;
        (void)_re_U32_3800;
        U32 _rc_U32_3800 = 0;
        (void)_rc_U32_3800;
        Bool hoisted__Bool_3809 = U32_lte(_rc_U32_3800, _re_U32_3800);
        (void)hoisted__Bool_3809;
        if (hoisted__Bool_3809) {
            while (1) {
                Bool _wcond_Bool_3801 = U32_lt(_rc_U32_3800, _re_U32_3800);
                (void)_wcond_Bool_3801;
                if (_wcond_Bool_3801) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3800);
                U32_inc(&_rc_U32_3800);
                U32 hoisted__U64_3802 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3802;
                void *hoisted__v_3803 = ptr_add(self->data, hoisted__U64_3802);
                (void)hoisted__v_3803;
                (void)hoisted__v_3803;
                Bool hoisted__Bool_3804 = 0;
                (void)hoisted__Bool_3804;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3803, hoisted__Bool_3804);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3805 = U32_gt(_rc_U32_3800, _re_U32_3800);
                (void)_wcond_Bool_3805;
                if (_wcond_Bool_3805) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3800);
                U32_dec(&_rc_U32_3800);
                U32 hoisted__U64_3806 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3806;
                void *hoisted__v_3807 = ptr_add(self->data, hoisted__U64_3806);
                (void)hoisted__v_3807;
                (void)hoisted__v_3807;
                Bool hoisted__Bool_3808 = 0;
                (void)hoisted__Bool_3808;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3807, hoisted__Bool_3808);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3822 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3822;
    void * new_data = malloc(hoisted__U64_3822);
    {
        U32 _re_U32_3810 = self->cap;
        (void)_re_U32_3810;
        U32 _rc_U32_3810 = 0;
        (void)_rc_U32_3810;
        Bool hoisted__Bool_3821 = U32_lte(_rc_U32_3810, _re_U32_3810);
        (void)hoisted__Bool_3821;
        if (hoisted__Bool_3821) {
            while (1) {
                Bool _wcond_Bool_3811 = U32_lt(_rc_U32_3810, _re_U32_3810);
                (void)_wcond_Bool_3811;
                if (_wcond_Bool_3811) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3810);
                U32_inc(&_rc_U32_3810);
                U32 hoisted__U64_3812 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3812;
                void *hoisted__v_3813 = ptr_add(self->data, hoisted__U64_3812);
                (void)hoisted__v_3813;
                (void)hoisted__v_3813;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3813);
                U32 hoisted__U64_3814 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3814;
                void *hoisted__v_3815 = ptr_add(new_data, hoisted__U64_3814);
                (void)hoisted__v_3815;
                (void)hoisted__v_3815;
                memcpy(hoisted__v_3815, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3816 = U32_gt(_rc_U32_3810, _re_U32_3810);
                (void)_wcond_Bool_3816;
                if (_wcond_Bool_3816) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3810);
                U32_dec(&_rc_U32_3810);
                U32 hoisted__U64_3817 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3817;
                void *hoisted__v_3818 = ptr_add(self->data, hoisted__U64_3817);
                (void)hoisted__v_3818;
                (void)hoisted__v_3818;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3818);
                U32 hoisted__U64_3819 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3819;
                void *hoisted__v_3820 = ptr_add(new_data, hoisted__U64_3819);
                (void)hoisted__v_3820;
                (void)hoisted__v_3820;
                memcpy(hoisted__v_3820, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3823 = malloc(sizeof(Array));
    hoisted__Array_3823->data = new_data;
    hoisted__Array_3823->cap = self->cap;
    hoisted__Array_3823->elem_size = self->elem_size;
    hoisted__Array_3823->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3823->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3823;
    return hoisted__Array_3823;
}

U32 Array_size(void) {
    U32 hoisted__U32_3824 = 32;
    (void)hoisted__U32_3824;
    return hoisted__U32_3824;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4198 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4198;
    U32 hoisted__U32_4199 = 3;
    (void)hoisted__U32_4199;
    Array *_va_Array_144 = Array_new(hoisted__Type_4198, hoisted__U32_4199);
    (void)_va_Array_144;
    Type_delete(hoisted__Type_4198, 1);
    U32 hoisted__U32_4200 = 0;
    (void)hoisted__U32_4200;
    Str *hoisted__Str_4201 = Str_clone(loc_str);
    (void)hoisted__Str_4201;
    Array_set(_va_Array_144, hoisted__U32_4200, hoisted__Str_4201);
    U32 hoisted__U32_4202 = 1;
    (void)hoisted__U32_4202;
    Str hoisted__Str_4203 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4203;
    Array_set(_va_Array_144, hoisted__U32_4202, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4203; _oa; }));
    Array *hoisted__Array_4204 = Array_clone(parts);
    (void)hoisted__Array_4204;
    Array_delete(parts, 1);
    U32 hoisted__U32_4205 = 2;
    (void)hoisted__U32_4205;
    Str *hoisted__Str_4206 = format(hoisted__Array_4204);
    (void)hoisted__Str_4206;
    Array_set(_va_Array_144, hoisted__U32_4205, hoisted__Str_4206);
    println(_va_Array_144);
    I64 hoisted__I64_4207 = 1;
    (void)hoisted__I64_4207;
    exit(hoisted__I64_4207);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4217 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4217;
    U32 hoisted__U32_4218 = 1;
    (void)hoisted__U32_4218;
    Array *_va_Array_146 = Array_new(hoisted__Type_4217, hoisted__U32_4218);
    (void)_va_Array_146;
    Type_delete(hoisted__Type_4217, 1);
    U32 hoisted__U32_4219 = 0;
    (void)hoisted__U32_4219;
    Str hoisted__Str_4220 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4220;
    Array_set(_va_Array_146, hoisted__U32_4219, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4220; _oa; }));
    panic(loc_str, _va_Array_146);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4226 = not(cond);
    (void)hoisted__Bool_4226;
    if (hoisted__Bool_4226) {
        Type *hoisted__Type_4222 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4222;
        U32 hoisted__U32_4223 = 1;
        (void)hoisted__U32_4223;
        Array *_va_Array_147 = Array_new(hoisted__Type_4222, hoisted__U32_4223);
        (void)_va_Array_147;
        Type_delete(hoisted__Type_4222, 1);
        U32 hoisted__U32_4224 = 0;
        (void)hoisted__U32_4224;
        Str hoisted__Str_4225 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4225;
        Array_set(_va_Array_147, hoisted__U32_4224, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4225; _oa; }));
        panic(loc_str, _va_Array_147);
    }
    Bool hoisted__Bool_4227 = 1;
    (void)hoisted__Bool_4227;
    return hoisted__Bool_4227;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4250 = I64_neq(a, b);
    (void)hoisted__Bool_4250;
    if (hoisted__Bool_4250) {
        Type *hoisted__Type_4238 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4238;
        U32 hoisted__U32_4239 = 5;
        (void)hoisted__U32_4239;
        Array *_va_Array_149 = Array_new(hoisted__Type_4238, hoisted__U32_4239);
        (void)_va_Array_149;
        Type_delete(hoisted__Type_4238, 1);
        U32 hoisted__U32_4240 = 0;
        (void)hoisted__U32_4240;
        Str hoisted__Str_4241 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4241;
        Array_set(_va_Array_149, hoisted__U32_4240, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4241; _oa; }));
        U32 hoisted__U32_4242 = 1;
        (void)hoisted__U32_4242;
        Str *hoisted__Str_4243 = I64_to_str(a);
        (void)hoisted__Str_4243;
        Array_set(_va_Array_149, hoisted__U32_4242, hoisted__Str_4243);
        U32 hoisted__U32_4244 = 2;
        (void)hoisted__U32_4244;
        Str hoisted__Str_4245 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4245;
        Array_set(_va_Array_149, hoisted__U32_4244, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4245; _oa; }));
        U32 hoisted__U32_4246 = 3;
        (void)hoisted__U32_4246;
        Str *hoisted__Str_4247 = I64_to_str(b);
        (void)hoisted__Str_4247;
        Array_set(_va_Array_149, hoisted__U32_4246, hoisted__Str_4247);
        U32 hoisted__U32_4248 = 4;
        (void)hoisted__U32_4248;
        Str hoisted__Str_4249 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4249;
        Array_set(_va_Array_149, hoisted__U32_4248, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4249; _oa; }));
        panic(loc_str, _va_Array_149);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4264 = Str_eq(a, b);
    (void)hoisted__Bool_4264;
    Bool hoisted__Bool_4265 = not(hoisted__Bool_4264);
    (void)hoisted__Bool_4265;
    if (hoisted__Bool_4265) {
        Type *hoisted__Type_4252 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4252;
        U32 hoisted__U32_4253 = 5;
        (void)hoisted__U32_4253;
        Array *_va_Array_150 = Array_new(hoisted__Type_4252, hoisted__U32_4253);
        (void)_va_Array_150;
        Type_delete(hoisted__Type_4252, 1);
        U32 hoisted__U32_4254 = 0;
        (void)hoisted__U32_4254;
        Str hoisted__Str_4255 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4255;
        Array_set(_va_Array_150, hoisted__U32_4254, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4255; _oa; }));
        U32 hoisted__U32_4256 = 1;
        (void)hoisted__U32_4256;
        Str *hoisted__Str_4257 = Str_clone(a);
        (void)hoisted__Str_4257;
        Array_set(_va_Array_150, hoisted__U32_4256, hoisted__Str_4257);
        U32 hoisted__U32_4258 = 2;
        (void)hoisted__U32_4258;
        Str hoisted__Str_4259 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4259;
        Array_set(_va_Array_150, hoisted__U32_4258, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4259; _oa; }));
        U32 hoisted__U32_4260 = 3;
        (void)hoisted__U32_4260;
        Str *hoisted__Str_4261 = Str_clone(b);
        (void)hoisted__Str_4261;
        Array_set(_va_Array_150, hoisted__U32_4260, hoisted__Str_4261);
        U32 hoisted__U32_4262 = 4;
        (void)hoisted__U32_4262;
        Str hoisted__Str_4263 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4263;
        Array_set(_va_Array_150, hoisted__U32_4262, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4263; _oa; }));
        panic(loc_str, _va_Array_150);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4266 = parts;
        (void)_fc_Array_4266;
        (void)_fc_Array_4266;
        U32 _fi_USize_4266 = 0;
        (void)_fi_USize_4266;
        I64 _forin_err_kind_4266 = 0;
        (void)_forin_err_kind_4266;
        OutOfBounds *_forin_OutOfBounds_4266 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4266->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4266;
        while (1) {
            U32 hoisted__U32_4274 = Array_len(_fc_Array_4266);
            (void)hoisted__U32_4274;
            Bool _wcond_Bool_4267 = U32_lt(_fi_USize_4266, hoisted__U32_4274);
            (void)_wcond_Bool_4267;
            if (_wcond_Bool_4267) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4266, &_fi_USize_4266, &_forin_err_kind_4266, _forin_OutOfBounds_4266);
            I64 hoisted__I64_4275 = 0;
            (void)hoisted__I64_4275;
            Bool hoisted__Bool_4276 = I64_eq(_forin_err_kind_4266, hoisted__I64_4275);
            (void)hoisted__Bool_4276;
            Bool hoisted__Bool_4277 = not(hoisted__Bool_4276);
            (void)hoisted__Bool_4277;
            if (hoisted__Bool_4277) {
                Type *hoisted__Type_4269 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4269;
                U32 hoisted__U32_4270 = 1;
                (void)hoisted__U32_4270;
                Array *_va_Array_151 = Array_new(hoisted__Type_4269, hoisted__U32_4270);
                (void)_va_Array_151;
                Type_delete(hoisted__Type_4269, 1);
                U32 hoisted__U32_4271 = 0;
                (void)hoisted__U32_4271;
                Str hoisted__Str_4272 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4272;
                Array_set(_va_Array_151, hoisted__U32_4271, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4272; _oa; }));
                Str hoisted__Str_4273 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4273;
                panic(&hoisted__Str_4273, _va_Array_151);
                Str_delete(&hoisted__Str_4273, (Bool){0});
            }
            U32 hoisted__U32_4278 = 1;
            (void)hoisted__U32_4278;
            U32 hoisted__U32_4279 = U32_add(_fi_USize_4266, hoisted__U32_4278);
            (void)hoisted__U32_4279;
            _fi_USize_4266 = hoisted__U32_4279;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4266, 1);
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
    Str hoisted__Str_4536 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4536;
    I64 hoisted__I64_4537 = 3;
    (void)hoisted__I64_4537;
    assert_eq(&hoisted__Str_4536, result, hoisted__I64_4537);
    Str_delete(&hoisted__Str_4536, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4544 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4544;
    I64 hoisted__I64_4545 = 15;
    (void)hoisted__I64_4545;
    assert_eq(&hoisted__Str_4544, result, hoisted__I64_4545);
    Str_delete(&hoisted__Str_4544, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4552 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4552;
    I64 hoisted__I64_4553 = 26;
    (void)hoisted__I64_4553;
    assert_eq(&hoisted__Str_4552, result, hoisted__I64_4553);
    Str_delete(&hoisted__Str_4552, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4556 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4556;
    Str hoisted__Str_4557 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4557;
    assert_eq_str(&hoisted__Str_4556, &result, &hoisted__Str_4557);
    Str_delete(&hoisted__Str_4556, (Bool){0});
    Str_delete(&hoisted__Str_4557, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4888 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4888;
    assert_eq_str(&hoisted__Str_4888, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4888, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4889 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4889;
    assert_eq_str(&hoisted__Str_4889, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4889, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4891 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4891;
    I64 hoisted__I64_4892 = 8;
    (void)hoisted__I64_4892;
    assert_eq(&hoisted__Str_4891, result, hoisted__I64_4892);
    Str_delete(&hoisted__Str_4891, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4895 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4895;
    Bool hoisted__Bool_4896 = 1;
    (void)hoisted__Bool_4896;
    assert(&hoisted__Str_4895, hoisted__Bool_4896);
    Str_delete(&hoisted__Str_4895, (Bool){0});
    Str hoisted__Str_4899 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4899;
    Bool hoisted__Bool_4900 = 1;
    (void)hoisted__Bool_4900;
    assert(&hoisted__Str_4899, hoisted__Bool_4900);
    Str_delete(&hoisted__Str_4899, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4905 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4905;
    Str hoisted__Str_4906 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4906;
    Str hoisted__Str_4907 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4907;
    assert_eq_str(&hoisted__Str_4905, &hoisted__Str_4906, &hoisted__Str_4907);
    Str_delete(&hoisted__Str_4905, (Bool){0});
    Str_delete(&hoisted__Str_4906, (Bool){0});
    Str_delete(&hoisted__Str_4907, (Bool){0});
    Str hoisted__Str_4910 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4910;
    Str hoisted__Str_4911 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4911;
    Str hoisted__Str_4912 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4912;
    assert_eq_str(&hoisted__Str_4910, &hoisted__Str_4911, &hoisted__Str_4912);
    Str_delete(&hoisted__Str_4910, (Bool){0});
    Str_delete(&hoisted__Str_4911, (Bool){0});
    Str_delete(&hoisted__Str_4912, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4917 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4917;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4917;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_4918 = 0;
    (void)hoisted__U32_4918;
    U64 hoisted__U64_4919 = ((U64 (*)(CfVec2 *, U32))(void *)hasher)(self, hoisted__U32_4918);
    (void)hoisted__U64_4919;
    return hoisted__U64_4919;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4920 = 16;
    (void)hoisted__U32_4920;
    return hoisted__U32_4920;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4921 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4921;
    I64 hoisted__I64_4922 = 42;
    (void)hoisted__I64_4922;
    assert_eq(&hoisted__Str_4921, v.x, hoisted__I64_4922);
    Str_delete(&hoisted__Str_4921, (Bool){0});
    Str hoisted__Str_4923 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4923;
    I64 hoisted__I64_4924 = 99;
    (void)hoisted__I64_4924;
    assert_eq(&hoisted__Str_4923, v.y, hoisted__I64_4924);
    Str_delete(&hoisted__Str_4923, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4927 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4927;
    I64 hoisted__I64_4928 = 10;
    (void)hoisted__I64_4928;
    assert_eq(&hoisted__Str_4927, p.x, hoisted__I64_4928);
    Str_delete(&hoisted__Str_4927, (Bool){0});
    Str hoisted__Str_4929 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4929;
    I64 hoisted__I64_4930 = 20;
    (void)hoisted__I64_4930;
    assert_eq(&hoisted__Str_4929, p.y, hoisted__I64_4930);
    Str_delete(&hoisted__Str_4929, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4936 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4936;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4936;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_4937 = 0;
    (void)hoisted__U32_4937;
    U64 hoisted__U64_4938 = ((U64 (*)(CfRect *, U32))(void *)hasher)(self, hoisted__U32_4937);
    (void)hoisted__U64_4938;
    return hoisted__U64_4938;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4939 = 32;
    (void)hoisted__U32_4939;
    return hoisted__U32_4939;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4940 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4940;
    I64 hoisted__I64_4941 = 5;
    (void)hoisted__I64_4941;
    assert_eq(&hoisted__Str_4940, r.top_left.x, hoisted__I64_4941);
    Str_delete(&hoisted__Str_4940, (Bool){0});
    Str hoisted__Str_4942 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4942;
    I64 hoisted__I64_4943 = 10;
    (void)hoisted__I64_4943;
    assert_eq(&hoisted__Str_4942, r.top_left.y, hoisted__I64_4943);
    Str_delete(&hoisted__Str_4942, (Bool){0});
    Str hoisted__Str_4944 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4944;
    I64 hoisted__I64_4945 = 100;
    (void)hoisted__I64_4945;
    assert_eq(&hoisted__Str_4944, r.bottom_right.x, hoisted__I64_4945);
    Str_delete(&hoisted__Str_4944, (Bool){0});
    Str hoisted__Str_4946 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4946;
    I64 hoisted__I64_4947 = 200;
    (void)hoisted__I64_4947;
    assert_eq(&hoisted__Str_4946, r.bottom_right.y, hoisted__I64_4947);
    Str_delete(&hoisted__Str_4946, (Bool){0});
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
    Bool hoisted__Bool_4952 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4952;
    if (hoisted__Bool_4952) {
        Bool hoisted__Bool_4949 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4949;
        { Bool _ret_val = hoisted__Bool_4949;
                return _ret_val; }
    }
    Bool hoisted__Bool_4953 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4953;
    if (hoisted__Bool_4953) {
        Bool hoisted__Bool_4950 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4950;
        { Bool _ret_val = hoisted__Bool_4950;
                return _ret_val; }
    }
    Bool hoisted__Bool_4954 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4954;
    if (hoisted__Bool_4954) {
        Bool hoisted__Bool_4951 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4951;
        { Bool _ret_val = hoisted__Bool_4951;
                return _ret_val; }
    }
    Bool hoisted__Bool_4955 = 0;
    (void)hoisted__Bool_4955;
    return hoisted__Bool_4955;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4963 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4963;
    if (hoisted__Bool_4963) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4964 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4964;
    if (hoisted__Bool_4964) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4965 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4965;
    if (hoisted__Bool_4965) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4966 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4966;
    UNREACHABLE(&hoisted__Str_4966);
    Str_delete(&hoisted__Str_4966, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4967 = 4;
    (void)hoisted__U32_4967;
    return hoisted__U32_4967;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_4968 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4968;
    Bool hoisted__Bool_4969 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4969;
    assert(&hoisted__Str_4968, hoisted__Bool_4969);
    Str_delete(&hoisted__Str_4968, (Bool){0});
    Bool hoisted__Bool_4970 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4970;
    Str hoisted__Str_4971 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4971;
    Bool hoisted__Bool_4972 = not(hoisted__Bool_4970);
    (void)hoisted__Bool_4972;
    assert(&hoisted__Str_4971, hoisted__Bool_4972);
    Str_delete(&hoisted__Str_4971, (Bool){0});
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
    Bool hoisted__Bool_4973 = is(self, other);
    (void)hoisted__Bool_4973;
    return hoisted__Bool_4973;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_4991 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4991;
    if (hoisted__Bool_4991) {
        I64 *hoisted__I64_4987 = get_payload(self);
        (void)hoisted__I64_4987;
        (void)hoisted__I64_4987;
        Bool hoisted__Bool_4988 = 0;
        (void)hoisted__Bool_4988;
        I64_delete(hoisted__I64_4987, hoisted__Bool_4988);
    }
    Bool hoisted__Bool_4992 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4992;
    if (hoisted__Bool_4992) {
        Str *hoisted__Str_4989 = get_payload(self);
        (void)hoisted__Str_4989;
        (void)hoisted__Str_4989;
        Bool hoisted__Bool_4990 = 0;
        (void)hoisted__Bool_4990;
        Str_delete(hoisted__Str_4989, hoisted__Bool_4990);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_5021 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5021;
    if (hoisted__Bool_5021) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_5018 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_5018;
        { Token * _ret_val = hoisted__Token_5018;
                return _ret_val; }
    }
    Bool hoisted__Bool_5022 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5022;
    if (hoisted__Bool_5022) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_5019 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_5019;
        Token *hoisted__Token_5020 = Token_Name(hoisted__Str_5019);
        (void)hoisted__Token_5020;
        { Token * _ret_val = hoisted__Token_5020;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_5023 = 24;
    (void)hoisted__U32_5023;
    return hoisted__U32_5023;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_5025 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5025;
    Bool hoisted__Bool_5026 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5026;
    assert(&hoisted__Str_5025, hoisted__Bool_5026);
    Str_delete(&hoisted__Str_5025, (Bool){0});
    Bool hoisted__Bool_5027 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5027;
    Token_delete(t, 1);
    Str hoisted__Str_5028 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5028;
    Bool hoisted__Bool_5029 = not(hoisted__Bool_5027);
    (void)hoisted__Bool_5029;
    assert(&hoisted__Str_5028, hoisted__Bool_5029);
    Str_delete(&hoisted__Str_5028, (Bool){0});
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_5030 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5030;
    Bool hoisted__Bool_5031 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5031;
    assert(&hoisted__Str_5030, hoisted__Bool_5031);
    Str_delete(&hoisted__Str_5030, (Bool){0});
    Bool hoisted__Bool_5032 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5032;
    Str hoisted__Str_5033 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5033;
    Bool hoisted__Bool_5034 = not(hoisted__Bool_5032);
    (void)hoisted__Bool_5034;
    assert(&hoisted__Str_5033, hoisted__Bool_5034);
    Str_delete(&hoisted__Str_5033, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_5037 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5037;
    Bool hoisted__Bool_5038 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5038;
    assert(&hoisted__Str_5037, hoisted__Bool_5038);
    Str_delete(&hoisted__Str_5037, (Bool){0});
    Bool hoisted__Bool_5039 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5039;
    Token_delete(t, 1);
    Str hoisted__Str_5040 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5040;
    Bool hoisted__Bool_5041 = not(hoisted__Bool_5039);
    (void)hoisted__Bool_5041;
    assert(&hoisted__Str_5040, hoisted__Bool_5041);
    Str_delete(&hoisted__Str_5040, (Bool){0});
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
