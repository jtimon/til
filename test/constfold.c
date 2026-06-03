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
    U32 hoisted__U32_259 = 4;
    (void)hoisted__U32_259;
    return hoisted__U32_259;
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_381 = 0;
    (void)hoisted__U32_381;
    U64 hoisted__U64_382 = ((U64 (*)(I32 *, U32))(void *)hasher)(&self, hoisted__U32_381);
    (void)hoisted__U64_382;
    return hoisted__U64_382;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_425 = 1;
    (void)hoisted__U32_425;
    return hoisted__U32_425;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_426 = 0;
    (void)hoisted__U32_426;
    U64 hoisted__U64_427 = ((U64 (*)(I8 *, U32))(void *)hasher)(&self, hoisted__U32_426);
    (void)hoisted__U64_427;
    return hoisted__U64_427;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_456 = 1;
    (void)hoisted__U32_456;
    return hoisted__U32_456;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_529 = 0;
    (void)hoisted__U32_529;
    U64 hoisted__U64_530 = ((U64 (*)(U8 *, U32))(void *)hasher)(&self, hoisted__U32_529);
    (void)hoisted__U64_530;
    return hoisted__U64_530;
}

Str * format(Array * parts) {
    U32 total = 0;
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
                Array *_va_Array_24 = Array_new(hoisted__Type_822, hoisted__U32_823);
                (void)_va_Array_24;
                Type_delete(hoisted__Type_822, 1);
                U32 hoisted__U32_824 = 0;
                (void)hoisted__U32_824;
                Str hoisted__Str_825 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_825;
                Array_set(_va_Array_24, hoisted__U32_824, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_825; _oa; }));
                Str hoisted__Str_826 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_826;
                panic(&hoisted__Str_826, _va_Array_24);
                Str_delete(&hoisted__Str_826, (Bool){0});
            }
            U32 hoisted__U32_831 = 1;
            (void)hoisted__U32_831;
            U32 hoisted__U32_832 = U32_add(_fi_USize_819, hoisted__U32_831);
            (void)hoisted__U32_832;
            _fi_USize_819 = hoisted__U32_832;
            U32 hoisted__U32_833 = Str_len(s);
            (void)hoisted__U32_833;
            U32 hoisted__U32_834 = U32_add(total, hoisted__U32_833);
            (void)hoisted__U32_834;
            total = hoisted__U32_834;
        }
        OutOfBounds_delete(_forin_OutOfBounds_819, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array *_fc_Array_835 = parts;
        (void)_fc_Array_835;
        (void)_fc_Array_835;
        U32 _fi_USize_835 = 0;
        (void)_fi_USize_835;
        I64 _forin_err_kind_835 = 0;
        (void)_forin_err_kind_835;
        OutOfBounds *_forin_OutOfBounds_835 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_835->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_835;
        while (1) {
            U32 hoisted__U32_843 = Array_len(_fc_Array_835);
            (void)hoisted__U32_843;
            Bool _wcond_Bool_836 = U32_lt(_fi_USize_835, hoisted__U32_843);
            (void)_wcond_Bool_836;
            if (_wcond_Bool_836) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_835, &_fi_USize_835, &_forin_err_kind_835, _forin_OutOfBounds_835);
            I64 hoisted__I64_844 = 0;
            (void)hoisted__I64_844;
            Bool hoisted__Bool_845 = I64_eq(_forin_err_kind_835, hoisted__I64_844);
            (void)hoisted__Bool_845;
            Bool hoisted__Bool_846 = not(hoisted__Bool_845);
            (void)hoisted__Bool_846;
            if (hoisted__Bool_846) {
                Type *hoisted__Type_838 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_838;
                U32 hoisted__U32_839 = 1;
                (void)hoisted__U32_839;
                Array *_va_Array_25 = Array_new(hoisted__Type_838, hoisted__U32_839);
                (void)_va_Array_25;
                Type_delete(hoisted__Type_838, 1);
                U32 hoisted__U32_840 = 0;
                (void)hoisted__U32_840;
                Str hoisted__Str_841 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_841;
                Array_set(_va_Array_25, hoisted__U32_840, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_841; _oa; }));
                Str hoisted__Str_842 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_842;
                panic(&hoisted__Str_842, _va_Array_25);
                Str_delete(&hoisted__Str_842, (Bool){0});
            }
            U32 hoisted__U32_847 = 1;
            (void)hoisted__U32_847;
            U32 hoisted__U32_848 = U32_add(_fi_USize_835, hoisted__U32_847);
            (void)hoisted__U32_848;
            _fi_USize_835 = hoisted__U32_848;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_835, 1);
    }
    Array_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_855 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_855;
    if (hoisted__Bool_855) {
        Type *hoisted__Type_850 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_850;
        U32 hoisted__U32_851 = 1;
        (void)hoisted__U32_851;
        Array *_va_Array_26 = Array_new(hoisted__Type_850, hoisted__U32_851);
        (void)_va_Array_26;
        Type_delete(hoisted__Type_850, 1);
        U32 hoisted__U32_852 = 0;
        (void)hoisted__U32_852;
        Str hoisted__Str_853 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_853;
        Array_set(_va_Array_26, hoisted__U32_852, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_853; _oa; }));
        Str hoisted__Str_854 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_854;
        panic(&hoisted__Str_854, _va_Array_26);
        Str_delete(&hoisted__Str_854, (Bool){0});
    }
    void *hoisted__v_856 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_856;
    (void)hoisted__v_856;
    return hoisted__v_856;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_866 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_866;
    if (hoisted__Bool_866) {
        min_len = b->count;
    }
    {
        U32 _re_U32_858 = U32_clone(&min_len);
        (void)_re_U32_858;
        U32 _rc_U32_858 = 0;
        (void)_rc_U32_858;
        Bool hoisted__Bool_865 = U32_lte(_rc_U32_858, _re_U32_858);
        (void)hoisted__Bool_865;
        if (hoisted__Bool_865) {
            while (1) {
                Bool _wcond_Bool_859 = U32_lt(_rc_U32_858, _re_U32_858);
                (void)_wcond_Bool_859;
                if (_wcond_Bool_859) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_858);
                U32_inc(&_rc_U32_858);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_860 = 0;
                (void)hoisted__I64_860;
                Bool hoisted__Bool_861 = I64_neq(c, hoisted__I64_860);
                (void)hoisted__Bool_861;
                if (hoisted__Bool_861) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_862 = U32_gt(_rc_U32_858, _re_U32_858);
                (void)_wcond_Bool_862;
                if (_wcond_Bool_862) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_858);
                U32_dec(&_rc_U32_858);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_863 = 0;
                (void)hoisted__I64_863;
                Bool hoisted__Bool_864 = I64_neq(c, hoisted__I64_863);
                (void)hoisted__Bool_864;
                if (hoisted__Bool_864) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_867 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_867;
    return hoisted__I64_867;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_869 = 1;
    (void)hoisted__U32_869;
    U32 hoisted__U64_870 = U32_add(n, hoisted__U32_869);
    (void)hoisted__U64_870;
    void * buf = malloc(hoisted__U64_870);
    I32 hoisted__I32_871 = 0;
    (void)hoisted__I32_871;
    U64 hoisted__U64_872 = 1ULL;
    (void)hoisted__U64_872;
    memset(buf, hoisted__I32_871, hoisted__U64_872);
    I32_delete(&hoisted__I32_871, 0);
    I64 hoisted__I64_873 = 0;
    (void)hoisted__I64_873;
    Str *hoisted__Str_874 = malloc(sizeof(Str));
    hoisted__Str_874->c_str = buf;
    hoisted__Str_874->count = hoisted__I64_873;
    hoisted__Str_874->cap = n;
    (void)hoisted__Str_874;
    return hoisted__Str_874;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_889 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_889;
    if (hoisted__Bool_889) {
        Type *hoisted__Type_878 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_878;
        U32 hoisted__U32_879 = 1;
        (void)hoisted__U32_879;
        Array *_va_Array_27 = Array_new(hoisted__Type_878, hoisted__U32_879);
        (void)_va_Array_27;
        Type_delete(hoisted__Type_878, 1);
        U32 hoisted__U32_880 = 0;
        (void)hoisted__U32_880;
        Str hoisted__Str_881 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_881;
        Array_set(_va_Array_27, hoisted__U32_880, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_881; _oa; }));
        Str hoisted__Str_882 = (Str){.c_str = (void *)"./src/core/str.til:91:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_882;
        panic(&hoisted__Str_882, _va_Array_27);
        Str_delete(&hoisted__Str_882, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_890 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_890;
    if (hoisted__Bool_890) {
        Type *hoisted__Type_884 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_884;
        U32 hoisted__U32_885 = 1;
        (void)hoisted__U32_885;
        Array *_va_Array_28 = Array_new(hoisted__Type_884, hoisted__U32_885);
        (void)_va_Array_28;
        Type_delete(hoisted__Type_884, 1);
        U32 hoisted__U32_886 = 0;
        (void)hoisted__U32_886;
        Str hoisted__Str_887 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_887;
        Array_set(_va_Array_28, hoisted__U32_886, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_887; _oa; }));
        Str hoisted__Str_888 = (Str){.c_str = (void *)"./src/core/str.til:95:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_888;
        panic(&hoisted__Str_888, _va_Array_28);
        Str_delete(&hoisted__Str_888, (Bool){0});
    }
    void *hoisted__v_891 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_891;
    (void)hoisted__v_891;
    memcpy(hoisted__v_891, s->c_str, s->count);
    U32 hoisted__U32_892 = U32_clone(&new_len);
    (void)hoisted__U32_892;
    self->count = hoisted__U32_892;
    void *hoisted__v_893 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_893;
    (void)hoisted__v_893;
    I32 hoisted__I32_894 = 0;
    (void)hoisted__I32_894;
    U64 hoisted__U64_895 = 1ULL;
    (void)hoisted__U64_895;
    memset(hoisted__v_893, hoisted__I32_894, hoisted__U64_895);
    I32_delete(&hoisted__I32_894, 0);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_896 = 1;
    (void)hoisted__U32_896;
    U32 hoisted__U64_897 = U32_add(val->count, hoisted__U32_896);
    (void)hoisted__U64_897;
    void * new_data = malloc(hoisted__U64_897);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_898 = ptr_add(new_data, val->count);
    (void)hoisted__v_898;
    (void)hoisted__v_898;
    I32 hoisted__I32_899 = 0;
    (void)hoisted__I32_899;
    U64 hoisted__U64_900 = 1ULL;
    (void)hoisted__U64_900;
    memset(hoisted__v_898, hoisted__I32_899, hoisted__U64_900);
    I32_delete(&hoisted__I32_899, 0);
    Str *hoisted__Str_901 = malloc(sizeof(Str));
    hoisted__Str_901->c_str = new_data;
    hoisted__Str_901->count = val->count;
    hoisted__Str_901->cap = val->count;
    (void)hoisted__Str_901;
    return hoisted__Str_901;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_902 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_902;
    if (hoisted__Bool_902) {
        free(self->c_str);
    }
    if (call_free) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_1015 = 0;
    (void)hoisted__U32_1015;
    Bool hoisted__Bool_1016 = U32_eq(self->count, hoisted__U32_1015);
    (void)hoisted__Bool_1016;
    return hoisted__Bool_1016;
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_1109 = ((U64 (*)(I8 *, U32))(void *)hasher)(self->c_str, self->count);
    (void)hoisted__U64_1109;
    return hoisted__U64_1109;
}

U32 Str_size(void) {
    U32 hoisted__U32_1233 = 16;
    (void)hoisted__U32_1233;
    return hoisted__U32_1233;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1234 = Str_cmp(a, b);
    (void)hoisted__I64_1234;
    I64 hoisted__I64_1235 = 0;
    (void)hoisted__I64_1235;
    Bool hoisted__Bool_1236 = I64_eq(hoisted__I64_1234, hoisted__I64_1235);
    (void)hoisted__Bool_1236;
    return hoisted__Bool_1236;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1307 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1307->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1307;
    return hoisted__OutOfBounds_1307;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1308 = 0;
    (void)hoisted__Bool_1308;
    Str_delete(&self->msg, hoisted__Bool_1308);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1309 = 0;
    (void)hoisted__U32_1309;
    U64 hoisted__U64_1310 = ((U64 (*)(OutOfBounds *, U32))(void *)hasher)(self, hoisted__U32_1309);
    (void)hoisted__U64_1310;
    return hoisted__U64_1310;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1311 = 16;
    (void)hoisted__U32_1311;
    return hoisted__U32_1311;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1319 = 8;
    (void)hoisted__U32_1319;
    return hoisted__U32_1319;
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1530 = 0;
    (void)hoisted__I64_1530;
    Bool hoisted__Bool_1531 = I64_eq(val, hoisted__I64_1530);
    (void)hoisted__Bool_1531;
    if (hoisted__Bool_1531) {
        U64 hoisted__U64_1494 = 2ULL;
        (void)hoisted__U64_1494;
        void * buf = malloc(hoisted__U64_1494);
        I64 hoisted__I64_1495 = 48;
        (void)hoisted__I64_1495;
        U64 hoisted__U64_1496 = 1ULL;
        (void)hoisted__U64_1496;
        memcpy(buf, &hoisted__I64_1495, hoisted__U64_1496);
        U64 hoisted__U64_1497 = 1ULL;
        (void)hoisted__U64_1497;
        void *hoisted__v_1498 = ptr_add(buf, hoisted__U64_1497);
        (void)hoisted__v_1498;
        (void)hoisted__v_1498;
        I32 hoisted__I32_1499 = 0;
        (void)hoisted__I32_1499;
        U64 hoisted__U64_1500 = 1ULL;
        (void)hoisted__U64_1500;
        memset(hoisted__v_1498, hoisted__I32_1499, hoisted__U64_1500);
        I32_delete(&hoisted__I32_1499, 0);
        I64 hoisted__I64_1501 = 1;
        (void)hoisted__I64_1501;
        I64 hoisted__I64_1502 = 1;
        (void)hoisted__I64_1502;
        Str *hoisted__Str_1503 = malloc(sizeof(Str));
        hoisted__Str_1503->c_str = buf;
        hoisted__Str_1503->count = hoisted__I64_1501;
        hoisted__Str_1503->cap = hoisted__I64_1502;
        (void)hoisted__Str_1503;
        { Str * _ret_val = hoisted__Str_1503;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1532 = 0;
    (void)hoisted__I64_1532;
    Bool hoisted__Bool_1533 = I64_lt(val, hoisted__I64_1532);
    (void)hoisted__Bool_1533;
    if (hoisted__Bool_1533) {
        Bool hoisted__Bool_1504 = 1;
        (void)hoisted__Bool_1504;
        is_neg = hoisted__Bool_1504;
        I64 hoisted__I64_1505 = 0;
        (void)hoisted__I64_1505;
        I64 hoisted__I64_1506 = I64_sub(hoisted__I64_1505, val);
        (void)hoisted__I64_1506;
        v = hoisted__I64_1506;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1508 = 0;
        (void)hoisted__I64_1508;
        Bool _wcond_Bool_1507 = I64_gt(tmp, hoisted__I64_1508);
        (void)_wcond_Bool_1507;
        if (_wcond_Bool_1507) {
        } else {
            break;
        }
        U64 hoisted__U64_1509 = 1ULL;
        (void)hoisted__U64_1509;
        U64 hoisted__U64_1510 = U64_add(ndigits, hoisted__U64_1509);
        (void)hoisted__U64_1510;
        ndigits = hoisted__U64_1510;
        I64 hoisted__I64_1511 = 10;
        (void)hoisted__I64_1511;
        I64 hoisted__I64_1512 = I64_div(tmp, hoisted__I64_1511);
        (void)hoisted__I64_1512;
        tmp = hoisted__I64_1512;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1513 = 1ULL;
        (void)hoisted__U64_1513;
        U64 hoisted__U64_1514 = U64_add(total, hoisted__U64_1513);
        (void)hoisted__U64_1514;
        total = hoisted__U64_1514;
    }
    U64 hoisted__U64_1534 = 1ULL;
    (void)hoisted__U64_1534;
    U64 hoisted__U64_1535 = U64_add(total, hoisted__U64_1534);
    (void)hoisted__U64_1535;
    void * buf = malloc(hoisted__U64_1535);
    if (is_neg) {
        I64 hoisted__I64_1515 = 45;
        (void)hoisted__I64_1515;
        U64 hoisted__U64_1516 = 1ULL;
        (void)hoisted__U64_1516;
        memcpy(buf, &hoisted__I64_1515, hoisted__U64_1516);
    }
    U64 hoisted__U64_1536 = 1ULL;
    (void)hoisted__U64_1536;
    U64 i = U64_sub(total, hoisted__U64_1536);
    while (1) {
        I64 hoisted__I64_1518 = 0;
        (void)hoisted__I64_1518;
        Bool _wcond_Bool_1517 = I64_gt(v, hoisted__I64_1518);
        (void)_wcond_Bool_1517;
        if (_wcond_Bool_1517) {
        } else {
            break;
        }
        I64 hoisted__I64_1519 = 10;
        (void)hoisted__I64_1519;
        I64 hoisted__I64_1520 = I64_mod(v, hoisted__I64_1519);
        (void)hoisted__I64_1520;
        I64 hoisted__I64_1521 = 48;
        (void)hoisted__I64_1521;
        I64 hoisted__I64_1522 = I64_add(hoisted__I64_1520, hoisted__I64_1521);
        (void)hoisted__I64_1522;
        void *hoisted__v_1523 = ptr_add(buf, i);
        (void)hoisted__v_1523;
        (void)hoisted__v_1523;
        U8 hoisted__U8_1524 = I64_to_u8(hoisted__I64_1522);
        (void)hoisted__U8_1524;
        U64 hoisted__U64_1525 = 1ULL;
        (void)hoisted__U64_1525;
        memcpy(hoisted__v_1523, &hoisted__U8_1524, hoisted__U64_1525);
        U8_delete(&hoisted__U8_1524, 0);
        I64 hoisted__I64_1526 = 10;
        (void)hoisted__I64_1526;
        I64 hoisted__I64_1527 = I64_div(v, hoisted__I64_1526);
        (void)hoisted__I64_1527;
        v = hoisted__I64_1527;
        U64 hoisted__U64_1528 = 1ULL;
        (void)hoisted__U64_1528;
        U64 hoisted__U64_1529 = U64_sub(i, hoisted__U64_1528);
        (void)hoisted__U64_1529;
        i = hoisted__U64_1529;
    }
    void *hoisted__v_1537 = ptr_add(buf, total);
    (void)hoisted__v_1537;
    (void)hoisted__v_1537;
    I32 hoisted__I32_1538 = 0;
    (void)hoisted__I32_1538;
    U64 hoisted__U64_1539 = 1ULL;
    (void)hoisted__U64_1539;
    memset(hoisted__v_1537, hoisted__I32_1538, hoisted__U64_1539);
    I32_delete(&hoisted__I32_1538, 0);
    Str *hoisted__Str_1540 = malloc(sizeof(Str));
    hoisted__Str_1540->c_str = buf;
    hoisted__Str_1540->count = total;
    hoisted__Str_1540->cap = total;
    (void)hoisted__Str_1540;
    return hoisted__Str_1540;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1560 = 8;
    (void)hoisted__U32_1560;
    return hoisted__U32_1560;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1691 = 0;
    (void)hoisted__U32_1691;
    U64 hoisted__U64_1692 = ((U64 (*)(I64 *, U32))(void *)hasher)(&self, hoisted__U32_1691);
    (void)hoisted__U64_1692;
    return hoisted__U64_1692;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1695 = I64_cmp(a, b);
    (void)hoisted__I64_1695;
    I64 hoisted__I64_1696 = -1;
    (void)hoisted__I64_1696;
    Bool hoisted__Bool_1697 = I64_eq(hoisted__I64_1695, hoisted__I64_1696);
    (void)hoisted__Bool_1697;
    return hoisted__Bool_1697;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1698 = I64_cmp(a, b);
    (void)hoisted__I64_1698;
    I64 hoisted__I64_1699 = 1;
    (void)hoisted__I64_1699;
    Bool hoisted__Bool_1700 = I64_eq(hoisted__I64_1698, hoisted__I64_1699);
    (void)hoisted__Bool_1700;
    return hoisted__Bool_1700;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1701 = I64_eq(a, b);
    (void)hoisted__Bool_1701;
    Bool hoisted__Bool_1702 = not(hoisted__Bool_1701);
    (void)hoisted__Bool_1702;
    return hoisted__Bool_1702;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1720 = Bool_eq(a, b);
    (void)hoisted__Bool_1720;
    if (hoisted__Bool_1720) {
        I64 hoisted__I64_1718 = 0;
        (void)hoisted__I64_1718;
        { I64 _ret_val = hoisted__I64_1718;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1719 = -1;
        (void)hoisted__I64_1719;
        return hoisted__I64_1719;
    }
    I64 hoisted__I64_1721 = 1;
    (void)hoisted__I64_1721;
    return hoisted__I64_1721;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1722 = 1;
    (void)hoisted__U32_1722;
    return hoisted__U32_1722;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1723 = 0;
    (void)hoisted__U32_1723;
    U64 hoisted__U64_1724 = ((U64 (*)(Bool *, U32))(void *)hasher)(&self, hoisted__U32_1723);
    (void)hoisted__U64_1724;
    return hoisted__U64_1724;
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
    Bool hoisted__Bool_1878 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1878;
    if (hoisted__Bool_1878) {
        Bool hoisted__Bool_1868 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1868;
        { Bool _ret_val = hoisted__Bool_1868;
                return _ret_val; }
    }
    Bool hoisted__Bool_1879 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1879;
    if (hoisted__Bool_1879) {
        Bool hoisted__Bool_1869 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1869;
        { Bool _ret_val = hoisted__Bool_1869;
                return _ret_val; }
    }
    Bool hoisted__Bool_1880 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1880;
    if (hoisted__Bool_1880) {
        Bool hoisted__Bool_1870 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_1870;
        { Bool _ret_val = hoisted__Bool_1870;
                return _ret_val; }
    }
    Bool hoisted__Bool_1881 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1881;
    if (hoisted__Bool_1881) {
        Bool hoisted__Bool_1871 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_1871;
        { Bool _ret_val = hoisted__Bool_1871;
                return _ret_val; }
    }
    Bool hoisted__Bool_1882 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1882;
    if (hoisted__Bool_1882) {
        Bool hoisted__Bool_1872 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_1872;
        { Bool _ret_val = hoisted__Bool_1872;
                return _ret_val; }
    }
    Bool hoisted__Bool_1883 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1883;
    if (hoisted__Bool_1883) {
        Bool hoisted__Bool_1873 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_1873;
        { Bool _ret_val = hoisted__Bool_1873;
                return _ret_val; }
    }
    Bool hoisted__Bool_1884 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1884;
    if (hoisted__Bool_1884) {
        Bool hoisted__Bool_1874 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_1874;
        { Bool _ret_val = hoisted__Bool_1874;
                return _ret_val; }
    }
    Bool hoisted__Bool_1885 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1885;
    if (hoisted__Bool_1885) {
        Bool hoisted__Bool_1875 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_1875;
        { Bool _ret_val = hoisted__Bool_1875;
                return _ret_val; }
    }
    Bool hoisted__Bool_1886 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1886;
    if (hoisted__Bool_1886) {
        Bool hoisted__Bool_1876 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_1876;
        { Bool _ret_val = hoisted__Bool_1876;
                return _ret_val; }
    }
    Bool hoisted__Bool_1887 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1887;
    if (hoisted__Bool_1887) {
        Bool hoisted__Bool_1877 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_1877;
        { Bool _ret_val = hoisted__Bool_1877;
                return _ret_val; }
    }
    Bool hoisted__Bool_1888 = 0;
    (void)hoisted__Bool_1888;
    return hoisted__Bool_1888;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1910 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1910;
    if (hoisted__Bool_1910) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1911 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1911;
    if (hoisted__Bool_1911) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_1912 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1912;
    if (hoisted__Bool_1912) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_1913 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1913;
    if (hoisted__Bool_1913) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1914 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1914;
    if (hoisted__Bool_1914) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1915 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1915;
    if (hoisted__Bool_1915) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1916 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1916;
    if (hoisted__Bool_1916) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1917 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1917;
    if (hoisted__Bool_1917) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1918 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1918;
    if (hoisted__Bool_1918) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1919 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1919;
    if (hoisted__Bool_1919) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_1920 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1920;
    UNREACHABLE(&hoisted__Str_1920);
    Str_delete(&hoisted__Str_1920, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1921 = 4;
    (void)hoisted__U32_1921;
    return hoisted__U32_1921;
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
    Bool hoisted__Bool_1967 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1967;
    if (hoisted__Bool_1967) {
        Str *hoisted__Str_1959 = get_payload(self);
        (void)hoisted__Str_1959;
        (void)hoisted__Str_1959;
        Bool hoisted__Bool_1960 = 0;
        (void)hoisted__Bool_1960;
        Str_delete(hoisted__Str_1959, hoisted__Bool_1960);
    }
    Bool hoisted__Bool_1968 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1968;
    if (hoisted__Bool_1968) {
        Str *hoisted__Str_1961 = get_payload(self);
        (void)hoisted__Str_1961;
        (void)hoisted__Str_1961;
        Bool hoisted__Bool_1962 = 0;
        (void)hoisted__Bool_1962;
        Str_delete(hoisted__Str_1961, hoisted__Bool_1962);
    }
    Bool hoisted__Bool_1969 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1969;
    if (hoisted__Bool_1969) {
        Str *hoisted__Str_1963 = get_payload(self);
        (void)hoisted__Str_1963;
        (void)hoisted__Str_1963;
        Bool hoisted__Bool_1964 = 0;
        (void)hoisted__Bool_1964;
        Str_delete(hoisted__Str_1963, hoisted__Bool_1964);
    }
    Bool hoisted__Bool_1970 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1970;
    if (hoisted__Bool_1970) {
        Primitive *hoisted__Primitive_1965 = get_payload(self);
        (void)hoisted__Primitive_1965;
        (void)hoisted__Primitive_1965;
        Bool hoisted__Bool_1966 = 0;
        (void)hoisted__Bool_1966;
        Primitive_delete(hoisted__Primitive_1965, hoisted__Bool_1966);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2036 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2036;
    if (hoisted__Bool_2036) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2037 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2037;
    if (hoisted__Bool_2037) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2038 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2038;
    if (hoisted__Bool_2038) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2030 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2030;
        Type *hoisted__Type_2031 = Type_Struct(hoisted__Str_2030);
        (void)hoisted__Type_2031;
        { Type * _ret_val = hoisted__Type_2031;
                return _ret_val; }
    }
    Bool hoisted__Bool_2039 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2039;
    if (hoisted__Bool_2039) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2040 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2040;
    if (hoisted__Bool_2040) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2032 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2032;
        Type *hoisted__Type_2033 = Type_Enum(hoisted__Str_2032);
        (void)hoisted__Type_2033;
        { Type * _ret_val = hoisted__Type_2033;
                return _ret_val; }
    }
    Bool hoisted__Bool_2041 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2041;
    if (hoisted__Bool_2041) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2042 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2042;
    if (hoisted__Bool_2042) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2043 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2043;
    if (hoisted__Bool_2043) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2044 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2044;
    if (hoisted__Bool_2044) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2045 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2045;
    if (hoisted__Bool_2045) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2034 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2034;
        Type *hoisted__Type_2035 = Type_Custom(hoisted__Str_2034);
        (void)hoisted__Type_2035;
        { Type * _ret_val = hoisted__Type_2035;
                return _ret_val; }
    }
    Primitive *_clone_payload_Primitive_10 = get_payload(self);
    (void)_clone_payload_Primitive_10;
    (void)_clone_payload_Primitive_10;
    Primitive hoisted__Primitive_2046 = DEREF(_clone_payload_Primitive_10);
    (void)hoisted__Primitive_2046;
    Type *hoisted__Type_2047 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2046; _oa; }));
    (void)hoisted__Type_2047;
    return hoisted__Type_2047;
}

U32 Type_size(void) {
    U32 hoisted__U32_2048 = 24;
    (void)hoisted__U32_2048;
    return hoisted__U32_2048;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3745 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3745;
    if (hoisted__Bool_3745) {
        Type *hoisted__Type_3740 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3740;
        U32 hoisted__U32_3741 = 1;
        (void)hoisted__U32_3741;
        Array *_va_Array_110 = Array_new(hoisted__Type_3740, hoisted__U32_3741);
        (void)_va_Array_110;
        Type_delete(hoisted__Type_3740, 1);
        U32 hoisted__U32_3742 = 0;
        (void)hoisted__U32_3742;
        Str hoisted__Str_3743 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3743;
        Array_set(_va_Array_110, hoisted__U32_3742, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3743; _oa; }));
        Str hoisted__Str_3744 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3744;
        panic(&hoisted__Str_3744, _va_Array_110);
        Str_delete(&hoisted__Str_3744, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3746 = calloc(cap, elem_size);
    (void)hoisted__v_3746;
    void * hoisted__v_3747 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3747;
    void * hoisted__v_3748 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3748;
    Array *hoisted__Array_3749 = malloc(sizeof(Array));
    hoisted__Array_3749->data = hoisted__v_3746;
    hoisted__Array_3749->cap = cap;
    hoisted__Array_3749->elem_size = elem_size;
    hoisted__Array_3749->elem_clone = hoisted__v_3747;
    hoisted__Array_3749->elem_delete = hoisted__v_3748;
    (void)hoisted__Array_3749;
    return hoisted__Array_3749;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3750 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3750;
    Str_delete(elem_type, 1);
    return hoisted__Array_3750;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3771 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3771;
    if (hoisted__Bool_3771) {
        Type *hoisted__Type_3752 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3752;
        U32 hoisted__U32_3753 = 6;
        (void)hoisted__U32_3753;
        Array *_va_Array_111 = Array_new(hoisted__Type_3752, hoisted__U32_3753);
        (void)_va_Array_111;
        Type_delete(hoisted__Type_3752, 1);
        U32 hoisted__U32_3754 = 0;
        (void)hoisted__U32_3754;
        Str hoisted__Str_3755 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3755;
        Array_set(_va_Array_111, hoisted__U32_3754, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3755; _oa; }));
        U32 hoisted__U32_3756 = 1;
        (void)hoisted__U32_3756;
        Str hoisted__Str_3757 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3757;
        Array_set(_va_Array_111, hoisted__U32_3756, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3757; _oa; }));
        U32 hoisted__U32_3758 = 2;
        (void)hoisted__U32_3758;
        Str *hoisted__Str_3759 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3759;
        Array_set(_va_Array_111, hoisted__U32_3758, hoisted__Str_3759);
        U32 hoisted__U32_3760 = 3;
        (void)hoisted__U32_3760;
        Str hoisted__Str_3761 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3761;
        Array_set(_va_Array_111, hoisted__U32_3760, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3761; _oa; }));
        U32 hoisted__U32_3762 = 4;
        (void)hoisted__U32_3762;
        Str *hoisted__Str_3763 = U32_to_str(self->cap);
        (void)hoisted__Str_3763;
        Array_set(_va_Array_111, hoisted__U32_3762, hoisted__Str_3763);
        U32 hoisted__U32_3764 = 5;
        (void)hoisted__U32_3764;
        Str hoisted__Str_3765 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3765;
        Array_set(_va_Array_111, hoisted__U32_3764, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3765; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3766 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_111); hoisted__OutOfBounds_3766->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3766;
        U32 hoisted__U32_3767 = 16;
        (void)hoisted__U32_3767;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3766, hoisted__U32_3767);
        OutOfBounds_delete(hoisted__OutOfBounds_3766, 1);
        I64 hoisted__I64_3768 = 3;
        (void)hoisted__I64_3768;
        *_err_kind = hoisted__I64_3768;
    }
    I64 hoisted__I64_3772 = 0;
    (void)hoisted__I64_3772;
    Bool hoisted__Bool_3773 = I64_eq(DEREF(_err_kind), hoisted__I64_3772);
    (void)hoisted__Bool_3773;
    if (hoisted__Bool_3773) {
        U32 hoisted__U64_3769 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3769;
        void *hoisted__v_3770 = ptr_add(self->data, hoisted__U64_3769);
        (void)hoisted__v_3770;
        (void)hoisted__v_3770;
        { void * _ret_val = hoisted__v_3770;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3788 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3788;
    if (hoisted__Bool_3788) {
        Type *hoisted__Type_3775 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3775;
        U32 hoisted__U32_3776 = 5;
        (void)hoisted__U32_3776;
        Array *_va_Array_112 = Array_new(hoisted__Type_3775, hoisted__U32_3776);
        (void)_va_Array_112;
        Type_delete(hoisted__Type_3775, 1);
        U32 hoisted__U32_3777 = 0;
        (void)hoisted__U32_3777;
        Str hoisted__Str_3778 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3778;
        Array_set(_va_Array_112, hoisted__U32_3777, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3778; _oa; }));
        U32 hoisted__U32_3779 = 1;
        (void)hoisted__U32_3779;
        Str *hoisted__Str_3780 = U32_to_str(i);
        (void)hoisted__Str_3780;
        Array_set(_va_Array_112, hoisted__U32_3779, hoisted__Str_3780);
        U32 hoisted__U32_3781 = 2;
        (void)hoisted__U32_3781;
        Str hoisted__Str_3782 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3782;
        Array_set(_va_Array_112, hoisted__U32_3781, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3782; _oa; }));
        U32 hoisted__U32_3783 = 3;
        (void)hoisted__U32_3783;
        Str *hoisted__Str_3784 = U32_to_str(self->cap);
        (void)hoisted__Str_3784;
        Array_set(_va_Array_112, hoisted__U32_3783, hoisted__Str_3784);
        U32 hoisted__U32_3785 = 4;
        (void)hoisted__U32_3785;
        Str hoisted__Str_3786 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3786;
        Array_set(_va_Array_112, hoisted__U32_3785, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3786; _oa; }));
        Str hoisted__Str_3787 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3787;
        panic(&hoisted__Str_3787, _va_Array_112);
        Str_delete(&hoisted__Str_3787, (Bool){0});
    }
    U32 hoisted__U64_3789 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3789;
    void *hoisted__v_3790 = ptr_add(self->data, hoisted__U64_3789);
    (void)hoisted__v_3790;
    (void)hoisted__v_3790;
    Bool hoisted__Bool_3791 = 0;
    (void)hoisted__Bool_3791;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3790, hoisted__Bool_3791);
    U32 hoisted__U64_3792 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3792;
    void *hoisted__v_3793 = ptr_add(self->data, hoisted__U64_3792);
    (void)hoisted__v_3793;
    (void)hoisted__v_3793;
    memcpy(hoisted__v_3793, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3794 = self->cap;
        (void)_re_U32_3794;
        U32 _rc_U32_3794 = 0;
        (void)_rc_U32_3794;
        Bool hoisted__Bool_3803 = U32_lte(_rc_U32_3794, _re_U32_3794);
        (void)hoisted__Bool_3803;
        if (hoisted__Bool_3803) {
            while (1) {
                Bool _wcond_Bool_3795 = U32_lt(_rc_U32_3794, _re_U32_3794);
                (void)_wcond_Bool_3795;
                if (_wcond_Bool_3795) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3794);
                U32_inc(&_rc_U32_3794);
                U32 hoisted__U64_3796 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3796;
                void *hoisted__v_3797 = ptr_add(self->data, hoisted__U64_3796);
                (void)hoisted__v_3797;
                (void)hoisted__v_3797;
                Bool hoisted__Bool_3798 = 0;
                (void)hoisted__Bool_3798;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3797, hoisted__Bool_3798);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3799 = U32_gt(_rc_U32_3794, _re_U32_3794);
                (void)_wcond_Bool_3799;
                if (_wcond_Bool_3799) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3794);
                U32_dec(&_rc_U32_3794);
                U32 hoisted__U64_3800 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3800;
                void *hoisted__v_3801 = ptr_add(self->data, hoisted__U64_3800);
                (void)hoisted__v_3801;
                (void)hoisted__v_3801;
                Bool hoisted__Bool_3802 = 0;
                (void)hoisted__Bool_3802;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3801, hoisted__Bool_3802);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3816 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3816;
    void * new_data = malloc(hoisted__U64_3816);
    {
        U32 _re_U32_3804 = self->cap;
        (void)_re_U32_3804;
        U32 _rc_U32_3804 = 0;
        (void)_rc_U32_3804;
        Bool hoisted__Bool_3815 = U32_lte(_rc_U32_3804, _re_U32_3804);
        (void)hoisted__Bool_3815;
        if (hoisted__Bool_3815) {
            while (1) {
                Bool _wcond_Bool_3805 = U32_lt(_rc_U32_3804, _re_U32_3804);
                (void)_wcond_Bool_3805;
                if (_wcond_Bool_3805) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3804);
                U32_inc(&_rc_U32_3804);
                U32 hoisted__U64_3806 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3806;
                void *hoisted__v_3807 = ptr_add(self->data, hoisted__U64_3806);
                (void)hoisted__v_3807;
                (void)hoisted__v_3807;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3807);
                U32 hoisted__U64_3808 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3808;
                void *hoisted__v_3809 = ptr_add(new_data, hoisted__U64_3808);
                (void)hoisted__v_3809;
                (void)hoisted__v_3809;
                memcpy(hoisted__v_3809, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3810 = U32_gt(_rc_U32_3804, _re_U32_3804);
                (void)_wcond_Bool_3810;
                if (_wcond_Bool_3810) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3804);
                U32_dec(&_rc_U32_3804);
                U32 hoisted__U64_3811 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3811;
                void *hoisted__v_3812 = ptr_add(self->data, hoisted__U64_3811);
                (void)hoisted__v_3812;
                (void)hoisted__v_3812;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3812);
                U32 hoisted__U64_3813 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3813;
                void *hoisted__v_3814 = ptr_add(new_data, hoisted__U64_3813);
                (void)hoisted__v_3814;
                (void)hoisted__v_3814;
                memcpy(hoisted__v_3814, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3817 = malloc(sizeof(Array));
    hoisted__Array_3817->data = new_data;
    hoisted__Array_3817->cap = self->cap;
    hoisted__Array_3817->elem_size = self->elem_size;
    hoisted__Array_3817->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3817->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3817;
    return hoisted__Array_3817;
}

U32 Array_size(void) {
    U32 hoisted__U32_3818 = 32;
    (void)hoisted__U32_3818;
    return hoisted__U32_3818;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4192 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4192;
    U32 hoisted__U32_4193 = 3;
    (void)hoisted__U32_4193;
    Array *_va_Array_144 = Array_new(hoisted__Type_4192, hoisted__U32_4193);
    (void)_va_Array_144;
    Type_delete(hoisted__Type_4192, 1);
    U32 hoisted__U32_4194 = 0;
    (void)hoisted__U32_4194;
    Str *hoisted__Str_4195 = Str_clone(loc_str);
    (void)hoisted__Str_4195;
    Array_set(_va_Array_144, hoisted__U32_4194, hoisted__Str_4195);
    U32 hoisted__U32_4196 = 1;
    (void)hoisted__U32_4196;
    Str hoisted__Str_4197 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4197;
    Array_set(_va_Array_144, hoisted__U32_4196, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4197; _oa; }));
    Array *hoisted__Array_4198 = Array_clone(parts);
    (void)hoisted__Array_4198;
    Array_delete(parts, 1);
    U32 hoisted__U32_4199 = 2;
    (void)hoisted__U32_4199;
    Str *hoisted__Str_4200 = format(hoisted__Array_4198);
    (void)hoisted__Str_4200;
    Array_set(_va_Array_144, hoisted__U32_4199, hoisted__Str_4200);
    println(_va_Array_144);
    I64 hoisted__I64_4201 = 1;
    (void)hoisted__I64_4201;
    exit(hoisted__I64_4201);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4211 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4211;
    U32 hoisted__U32_4212 = 1;
    (void)hoisted__U32_4212;
    Array *_va_Array_146 = Array_new(hoisted__Type_4211, hoisted__U32_4212);
    (void)_va_Array_146;
    Type_delete(hoisted__Type_4211, 1);
    U32 hoisted__U32_4213 = 0;
    (void)hoisted__U32_4213;
    Str hoisted__Str_4214 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4214;
    Array_set(_va_Array_146, hoisted__U32_4213, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4214; _oa; }));
    panic(loc_str, _va_Array_146);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4220 = not(cond);
    (void)hoisted__Bool_4220;
    if (hoisted__Bool_4220) {
        Type *hoisted__Type_4216 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4216;
        U32 hoisted__U32_4217 = 1;
        (void)hoisted__U32_4217;
        Array *_va_Array_147 = Array_new(hoisted__Type_4216, hoisted__U32_4217);
        (void)_va_Array_147;
        Type_delete(hoisted__Type_4216, 1);
        U32 hoisted__U32_4218 = 0;
        (void)hoisted__U32_4218;
        Str hoisted__Str_4219 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4219;
        Array_set(_va_Array_147, hoisted__U32_4218, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4219; _oa; }));
        panic(loc_str, _va_Array_147);
    }
    Bool hoisted__Bool_4221 = 1;
    (void)hoisted__Bool_4221;
    return hoisted__Bool_4221;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4244 = I64_neq(a, b);
    (void)hoisted__Bool_4244;
    if (hoisted__Bool_4244) {
        Type *hoisted__Type_4232 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4232;
        U32 hoisted__U32_4233 = 5;
        (void)hoisted__U32_4233;
        Array *_va_Array_149 = Array_new(hoisted__Type_4232, hoisted__U32_4233);
        (void)_va_Array_149;
        Type_delete(hoisted__Type_4232, 1);
        U32 hoisted__U32_4234 = 0;
        (void)hoisted__U32_4234;
        Str hoisted__Str_4235 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4235;
        Array_set(_va_Array_149, hoisted__U32_4234, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4235; _oa; }));
        U32 hoisted__U32_4236 = 1;
        (void)hoisted__U32_4236;
        Str *hoisted__Str_4237 = I64_to_str(a);
        (void)hoisted__Str_4237;
        Array_set(_va_Array_149, hoisted__U32_4236, hoisted__Str_4237);
        U32 hoisted__U32_4238 = 2;
        (void)hoisted__U32_4238;
        Str hoisted__Str_4239 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4239;
        Array_set(_va_Array_149, hoisted__U32_4238, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4239; _oa; }));
        U32 hoisted__U32_4240 = 3;
        (void)hoisted__U32_4240;
        Str *hoisted__Str_4241 = I64_to_str(b);
        (void)hoisted__Str_4241;
        Array_set(_va_Array_149, hoisted__U32_4240, hoisted__Str_4241);
        U32 hoisted__U32_4242 = 4;
        (void)hoisted__U32_4242;
        Str hoisted__Str_4243 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4243;
        Array_set(_va_Array_149, hoisted__U32_4242, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4243; _oa; }));
        panic(loc_str, _va_Array_149);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4258 = Str_eq(a, b);
    (void)hoisted__Bool_4258;
    Bool hoisted__Bool_4259 = not(hoisted__Bool_4258);
    (void)hoisted__Bool_4259;
    if (hoisted__Bool_4259) {
        Type *hoisted__Type_4246 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4246;
        U32 hoisted__U32_4247 = 5;
        (void)hoisted__U32_4247;
        Array *_va_Array_150 = Array_new(hoisted__Type_4246, hoisted__U32_4247);
        (void)_va_Array_150;
        Type_delete(hoisted__Type_4246, 1);
        U32 hoisted__U32_4248 = 0;
        (void)hoisted__U32_4248;
        Str hoisted__Str_4249 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4249;
        Array_set(_va_Array_150, hoisted__U32_4248, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4249; _oa; }));
        U32 hoisted__U32_4250 = 1;
        (void)hoisted__U32_4250;
        Str *hoisted__Str_4251 = Str_clone(a);
        (void)hoisted__Str_4251;
        Array_set(_va_Array_150, hoisted__U32_4250, hoisted__Str_4251);
        U32 hoisted__U32_4252 = 2;
        (void)hoisted__U32_4252;
        Str hoisted__Str_4253 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4253;
        Array_set(_va_Array_150, hoisted__U32_4252, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4253; _oa; }));
        U32 hoisted__U32_4254 = 3;
        (void)hoisted__U32_4254;
        Str *hoisted__Str_4255 = Str_clone(b);
        (void)hoisted__Str_4255;
        Array_set(_va_Array_150, hoisted__U32_4254, hoisted__Str_4255);
        U32 hoisted__U32_4256 = 4;
        (void)hoisted__U32_4256;
        Str hoisted__Str_4257 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4257;
        Array_set(_va_Array_150, hoisted__U32_4256, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4257; _oa; }));
        panic(loc_str, _va_Array_150);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4260 = parts;
        (void)_fc_Array_4260;
        (void)_fc_Array_4260;
        U32 _fi_USize_4260 = 0;
        (void)_fi_USize_4260;
        I64 _forin_err_kind_4260 = 0;
        (void)_forin_err_kind_4260;
        OutOfBounds *_forin_OutOfBounds_4260 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4260->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4260;
        while (1) {
            U32 hoisted__U32_4268 = Array_len(_fc_Array_4260);
            (void)hoisted__U32_4268;
            Bool _wcond_Bool_4261 = U32_lt(_fi_USize_4260, hoisted__U32_4268);
            (void)_wcond_Bool_4261;
            if (_wcond_Bool_4261) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4260, &_fi_USize_4260, &_forin_err_kind_4260, _forin_OutOfBounds_4260);
            I64 hoisted__I64_4269 = 0;
            (void)hoisted__I64_4269;
            Bool hoisted__Bool_4270 = I64_eq(_forin_err_kind_4260, hoisted__I64_4269);
            (void)hoisted__Bool_4270;
            Bool hoisted__Bool_4271 = not(hoisted__Bool_4270);
            (void)hoisted__Bool_4271;
            if (hoisted__Bool_4271) {
                Type *hoisted__Type_4263 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4263;
                U32 hoisted__U32_4264 = 1;
                (void)hoisted__U32_4264;
                Array *_va_Array_151 = Array_new(hoisted__Type_4263, hoisted__U32_4264);
                (void)_va_Array_151;
                Type_delete(hoisted__Type_4263, 1);
                U32 hoisted__U32_4265 = 0;
                (void)hoisted__U32_4265;
                Str hoisted__Str_4266 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4266;
                Array_set(_va_Array_151, hoisted__U32_4265, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4266; _oa; }));
                Str hoisted__Str_4267 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4267;
                panic(&hoisted__Str_4267, _va_Array_151);
                Str_delete(&hoisted__Str_4267, (Bool){0});
            }
            U32 hoisted__U32_4272 = 1;
            (void)hoisted__U32_4272;
            U32 hoisted__U32_4273 = U32_add(_fi_USize_4260, hoisted__U32_4272);
            (void)hoisted__U32_4273;
            _fi_USize_4260 = hoisted__U32_4273;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4260, 1);
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
    Str hoisted__Str_4530 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4530;
    I64 hoisted__I64_4531 = 3;
    (void)hoisted__I64_4531;
    assert_eq(&hoisted__Str_4530, result, hoisted__I64_4531);
    Str_delete(&hoisted__Str_4530, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4538 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4538;
    I64 hoisted__I64_4539 = 15;
    (void)hoisted__I64_4539;
    assert_eq(&hoisted__Str_4538, result, hoisted__I64_4539);
    Str_delete(&hoisted__Str_4538, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4546 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4546;
    I64 hoisted__I64_4547 = 26;
    (void)hoisted__I64_4547;
    assert_eq(&hoisted__Str_4546, result, hoisted__I64_4547);
    Str_delete(&hoisted__Str_4546, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4550 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4550;
    Str hoisted__Str_4551 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4551;
    assert_eq_str(&hoisted__Str_4550, &result, &hoisted__Str_4551);
    Str_delete(&hoisted__Str_4550, (Bool){0});
    Str_delete(&hoisted__Str_4551, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4882 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4882;
    assert_eq_str(&hoisted__Str_4882, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4882, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4883 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4883;
    assert_eq_str(&hoisted__Str_4883, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4883, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4885 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4885;
    I64 hoisted__I64_4886 = 8;
    (void)hoisted__I64_4886;
    assert_eq(&hoisted__Str_4885, result, hoisted__I64_4886);
    Str_delete(&hoisted__Str_4885, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4889 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4889;
    Bool hoisted__Bool_4890 = 1;
    (void)hoisted__Bool_4890;
    assert(&hoisted__Str_4889, hoisted__Bool_4890);
    Str_delete(&hoisted__Str_4889, (Bool){0});
    Str hoisted__Str_4893 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4893;
    Bool hoisted__Bool_4894 = 1;
    (void)hoisted__Bool_4894;
    assert(&hoisted__Str_4893, hoisted__Bool_4894);
    Str_delete(&hoisted__Str_4893, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4899 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4899;
    Str hoisted__Str_4900 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4900;
    Str hoisted__Str_4901 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4901;
    assert_eq_str(&hoisted__Str_4899, &hoisted__Str_4900, &hoisted__Str_4901);
    Str_delete(&hoisted__Str_4899, (Bool){0});
    Str_delete(&hoisted__Str_4900, (Bool){0});
    Str_delete(&hoisted__Str_4901, (Bool){0});
    Str hoisted__Str_4904 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4904;
    Str hoisted__Str_4905 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4905;
    Str hoisted__Str_4906 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4906;
    assert_eq_str(&hoisted__Str_4904, &hoisted__Str_4905, &hoisted__Str_4906);
    Str_delete(&hoisted__Str_4904, (Bool){0});
    Str_delete(&hoisted__Str_4905, (Bool){0});
    Str_delete(&hoisted__Str_4906, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4911 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4911;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4911;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_4912 = 0;
    (void)hoisted__U32_4912;
    U64 hoisted__U64_4913 = ((U64 (*)(CfVec2 *, U32))(void *)hasher)(self, hoisted__U32_4912);
    (void)hoisted__U64_4913;
    return hoisted__U64_4913;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4914 = 16;
    (void)hoisted__U32_4914;
    return hoisted__U32_4914;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4915 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4915;
    I64 hoisted__I64_4916 = 42;
    (void)hoisted__I64_4916;
    assert_eq(&hoisted__Str_4915, v.x, hoisted__I64_4916);
    Str_delete(&hoisted__Str_4915, (Bool){0});
    Str hoisted__Str_4917 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4917;
    I64 hoisted__I64_4918 = 99;
    (void)hoisted__I64_4918;
    assert_eq(&hoisted__Str_4917, v.y, hoisted__I64_4918);
    Str_delete(&hoisted__Str_4917, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4921 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4921;
    I64 hoisted__I64_4922 = 10;
    (void)hoisted__I64_4922;
    assert_eq(&hoisted__Str_4921, p.x, hoisted__I64_4922);
    Str_delete(&hoisted__Str_4921, (Bool){0});
    Str hoisted__Str_4923 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4923;
    I64 hoisted__I64_4924 = 20;
    (void)hoisted__I64_4924;
    assert_eq(&hoisted__Str_4923, p.y, hoisted__I64_4924);
    Str_delete(&hoisted__Str_4923, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4930 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4930;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4930;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_4931 = 0;
    (void)hoisted__U32_4931;
    U64 hoisted__U64_4932 = ((U64 (*)(CfRect *, U32))(void *)hasher)(self, hoisted__U32_4931);
    (void)hoisted__U64_4932;
    return hoisted__U64_4932;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4933 = 32;
    (void)hoisted__U32_4933;
    return hoisted__U32_4933;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4934 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4934;
    I64 hoisted__I64_4935 = 5;
    (void)hoisted__I64_4935;
    assert_eq(&hoisted__Str_4934, r.top_left.x, hoisted__I64_4935);
    Str_delete(&hoisted__Str_4934, (Bool){0});
    Str hoisted__Str_4936 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4936;
    I64 hoisted__I64_4937 = 10;
    (void)hoisted__I64_4937;
    assert_eq(&hoisted__Str_4936, r.top_left.y, hoisted__I64_4937);
    Str_delete(&hoisted__Str_4936, (Bool){0});
    Str hoisted__Str_4938 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4938;
    I64 hoisted__I64_4939 = 100;
    (void)hoisted__I64_4939;
    assert_eq(&hoisted__Str_4938, r.bottom_right.x, hoisted__I64_4939);
    Str_delete(&hoisted__Str_4938, (Bool){0});
    Str hoisted__Str_4940 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4940;
    I64 hoisted__I64_4941 = 200;
    (void)hoisted__I64_4941;
    assert_eq(&hoisted__Str_4940, r.bottom_right.y, hoisted__I64_4941);
    Str_delete(&hoisted__Str_4940, (Bool){0});
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
    Bool hoisted__Bool_4946 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4946;
    if (hoisted__Bool_4946) {
        Bool hoisted__Bool_4943 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4943;
        { Bool _ret_val = hoisted__Bool_4943;
                return _ret_val; }
    }
    Bool hoisted__Bool_4947 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4947;
    if (hoisted__Bool_4947) {
        Bool hoisted__Bool_4944 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4944;
        { Bool _ret_val = hoisted__Bool_4944;
                return _ret_val; }
    }
    Bool hoisted__Bool_4948 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4948;
    if (hoisted__Bool_4948) {
        Bool hoisted__Bool_4945 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4945;
        { Bool _ret_val = hoisted__Bool_4945;
                return _ret_val; }
    }
    Bool hoisted__Bool_4949 = 0;
    (void)hoisted__Bool_4949;
    return hoisted__Bool_4949;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4957 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4957;
    if (hoisted__Bool_4957) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4958 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4958;
    if (hoisted__Bool_4958) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4959 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4959;
    if (hoisted__Bool_4959) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4960 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4960;
    UNREACHABLE(&hoisted__Str_4960);
    Str_delete(&hoisted__Str_4960, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4961 = 4;
    (void)hoisted__U32_4961;
    return hoisted__U32_4961;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_4962 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4962;
    Bool hoisted__Bool_4963 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4963;
    assert(&hoisted__Str_4962, hoisted__Bool_4963);
    Str_delete(&hoisted__Str_4962, (Bool){0});
    Bool hoisted__Bool_4964 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4964;
    Str hoisted__Str_4965 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4965;
    Bool hoisted__Bool_4966 = not(hoisted__Bool_4964);
    (void)hoisted__Bool_4966;
    assert(&hoisted__Str_4965, hoisted__Bool_4966);
    Str_delete(&hoisted__Str_4965, (Bool){0});
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
    Bool hoisted__Bool_4967 = is(self, other);
    (void)hoisted__Bool_4967;
    return hoisted__Bool_4967;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_4985 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4985;
    if (hoisted__Bool_4985) {
        I64 *hoisted__I64_4981 = get_payload(self);
        (void)hoisted__I64_4981;
        (void)hoisted__I64_4981;
        Bool hoisted__Bool_4982 = 0;
        (void)hoisted__Bool_4982;
        I64_delete(hoisted__I64_4981, hoisted__Bool_4982);
    }
    Bool hoisted__Bool_4986 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4986;
    if (hoisted__Bool_4986) {
        Str *hoisted__Str_4983 = get_payload(self);
        (void)hoisted__Str_4983;
        (void)hoisted__Str_4983;
        Bool hoisted__Bool_4984 = 0;
        (void)hoisted__Bool_4984;
        Str_delete(hoisted__Str_4983, hoisted__Bool_4984);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_5015 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5015;
    if (hoisted__Bool_5015) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_5012 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_5012;
        { Token * _ret_val = hoisted__Token_5012;
                return _ret_val; }
    }
    Bool hoisted__Bool_5016 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5016;
    if (hoisted__Bool_5016) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_5013 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_5013;
        Token *hoisted__Token_5014 = Token_Name(hoisted__Str_5013);
        (void)hoisted__Token_5014;
        { Token * _ret_val = hoisted__Token_5014;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_5017 = 24;
    (void)hoisted__U32_5017;
    return hoisted__U32_5017;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_5019 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5019;
    Bool hoisted__Bool_5020 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5020;
    assert(&hoisted__Str_5019, hoisted__Bool_5020);
    Str_delete(&hoisted__Str_5019, (Bool){0});
    Bool hoisted__Bool_5021 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5021;
    Token_delete(t, 1);
    Str hoisted__Str_5022 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5022;
    Bool hoisted__Bool_5023 = not(hoisted__Bool_5021);
    (void)hoisted__Bool_5023;
    assert(&hoisted__Str_5022, hoisted__Bool_5023);
    Str_delete(&hoisted__Str_5022, (Bool){0});
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_5024 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5024;
    Bool hoisted__Bool_5025 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5025;
    assert(&hoisted__Str_5024, hoisted__Bool_5025);
    Str_delete(&hoisted__Str_5024, (Bool){0});
    Bool hoisted__Bool_5026 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5026;
    Str hoisted__Str_5027 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5027;
    Bool hoisted__Bool_5028 = not(hoisted__Bool_5026);
    (void)hoisted__Bool_5028;
    assert(&hoisted__Str_5027, hoisted__Bool_5028);
    Str_delete(&hoisted__Str_5027, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_5031 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5031;
    Bool hoisted__Bool_5032 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5032;
    assert(&hoisted__Str_5031, hoisted__Bool_5032);
    Str_delete(&hoisted__Str_5031, (Bool){0});
    Bool hoisted__Bool_5033 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5033;
    Token_delete(t, 1);
    Str hoisted__Str_5034 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5034;
    Bool hoisted__Bool_5035 = not(hoisted__Bool_5033);
    (void)hoisted__Bool_5035;
    assert(&hoisted__Str_5034, hoisted__Bool_5035);
    Str_delete(&hoisted__Str_5034, (Bool){0});
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
