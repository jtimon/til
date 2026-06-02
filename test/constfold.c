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
    U32 hoisted__U32_111 = 0;
    (void)hoisted__U32_111;
    U64 hoisted__U64_112 = ((U64 (*)(U64 *, U32))(void *)hasher)(&self, hoisted__U32_111);
    (void)hoisted__U64_112;
    return hoisted__U64_112;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_127 = U32_to_i64(val);
    (void)hoisted__I64_127;
    Str *hoisted__Str_128 = I64_to_str(hoisted__I64_127);
    (void)hoisted__Str_128;
    return hoisted__Str_128;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_129 = 1;
    (void)hoisted__U32_129;
    U32 hoisted__U32_130 = U32_add(DEREF(self), hoisted__U32_129);
    (void)hoisted__U32_130;
    *self = hoisted__U32_130;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_131 = 1;
    (void)hoisted__U32_131;
    U32 hoisted__U32_132 = U32_sub(DEREF(self), hoisted__U32_131);
    (void)hoisted__U32_132;
    *self = hoisted__U32_132;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_139 = 4;
    (void)hoisted__U32_139;
    return hoisted__U32_139;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_213 = 0;
    (void)hoisted__U32_213;
    U64 hoisted__U64_214 = ((U64 (*)(U32 *, U32))(void *)hasher)(&self, hoisted__U32_213);
    (void)hoisted__U64_214;
    return hoisted__U64_214;
}

Bool U32_lt(U32 a, U32 b) {
    I64 hoisted__I64_217 = U32_cmp(a, b);
    (void)hoisted__I64_217;
    I64 hoisted__I64_218 = -1;
    (void)hoisted__I64_218;
    Bool hoisted__Bool_219 = I64_eq(hoisted__I64_217, hoisted__I64_218);
    (void)hoisted__Bool_219;
    return hoisted__Bool_219;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_220 = U32_cmp(a, b);
    (void)hoisted__I64_220;
    I64 hoisted__I64_221 = 1;
    (void)hoisted__I64_221;
    Bool hoisted__Bool_222 = I64_eq(hoisted__I64_220, hoisted__I64_221);
    (void)hoisted__Bool_222;
    return hoisted__Bool_222;
}

Bool U32_lte(U32 a, U32 b) {
    Bool hoisted__Bool_225 = U32_gt(a, b);
    (void)hoisted__Bool_225;
    Bool hoisted__Bool_226 = not(hoisted__Bool_225);
    (void)hoisted__Bool_226;
    return hoisted__Bool_226;
}

Bool U32_gte(U32 a, U32 b) {
    Bool hoisted__Bool_227 = U32_lt(a, b);
    (void)hoisted__Bool_227;
    Bool hoisted__Bool_228 = not(hoisted__Bool_227);
    (void)hoisted__Bool_228;
    return hoisted__Bool_228;
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
    U32 hoisted__U32_380 = 0;
    (void)hoisted__U32_380;
    U64 hoisted__U64_381 = ((U64 (*)(I32 *, U32))(void *)hasher)(&self, hoisted__U32_380);
    (void)hoisted__U64_381;
    return hoisted__U64_381;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_420 = 1;
    (void)hoisted__U32_420;
    return hoisted__U32_420;
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_421 = 0;
    (void)hoisted__U32_421;
    U64 hoisted__U64_422 = ((U64 (*)(I8 *, U32))(void *)hasher)(&self, hoisted__U32_421);
    (void)hoisted__U64_422;
    return hoisted__U64_422;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_449 = 1;
    (void)hoisted__U32_449;
    return hoisted__U32_449;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_523 = 0;
    (void)hoisted__U32_523;
    U64 hoisted__U64_524 = ((U64 (*)(U8 *, U32))(void *)hasher)(&self, hoisted__U32_523);
    (void)hoisted__U64_524;
    return hoisted__U64_524;
}

Str * format(Array * parts) {
    U32 total = 0;
    {
        Array *_fc_Array_813 = parts;
        (void)_fc_Array_813;
        (void)_fc_Array_813;
        U32 _fi_USize_813 = 0;
        (void)_fi_USize_813;
        I64 _forin_err_kind_813 = 0;
        (void)_forin_err_kind_813;
        OutOfBounds *_forin_OutOfBounds_813 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_813->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_813;
        while (1) {
            U32 hoisted__U32_821 = Array_len(_fc_Array_813);
            (void)hoisted__U32_821;
            Bool _wcond_Bool_814 = U32_lt(_fi_USize_813, hoisted__U32_821);
            (void)_wcond_Bool_814;
            if (_wcond_Bool_814) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_813, &_fi_USize_813, &_forin_err_kind_813, _forin_OutOfBounds_813);
            I64 hoisted__I64_822 = 0;
            (void)hoisted__I64_822;
            Bool hoisted__Bool_823 = I64_eq(_forin_err_kind_813, hoisted__I64_822);
            (void)hoisted__Bool_823;
            Bool hoisted__Bool_824 = not(hoisted__Bool_823);
            (void)hoisted__Bool_824;
            if (hoisted__Bool_824) {
                Type *hoisted__Type_816 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_816;
                U32 hoisted__U32_817 = 1;
                (void)hoisted__U32_817;
                Array *_va_Array_24 = Array_new(hoisted__Type_816, hoisted__U32_817);
                (void)_va_Array_24;
                Type_delete(hoisted__Type_816, 1);
                U32 hoisted__U32_818 = 0;
                (void)hoisted__U32_818;
                Str hoisted__Str_819 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_819;
                Array_set(_va_Array_24, hoisted__U32_818, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_819; _oa; }));
                Str hoisted__Str_820 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_820;
                panic(&hoisted__Str_820, _va_Array_24);
                Str_delete(&hoisted__Str_820, (Bool){0});
            }
            U32 hoisted__U32_825 = 1;
            (void)hoisted__U32_825;
            U32 hoisted__U32_826 = U32_add(_fi_USize_813, hoisted__U32_825);
            (void)hoisted__U32_826;
            _fi_USize_813 = hoisted__U32_826;
            U32 hoisted__U32_827 = Str_len(s);
            (void)hoisted__U32_827;
            U32 hoisted__U32_828 = U32_add(total, hoisted__U32_827);
            (void)hoisted__U32_828;
            total = hoisted__U32_828;
        }
        OutOfBounds_delete(_forin_OutOfBounds_813, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array *_fc_Array_829 = parts;
        (void)_fc_Array_829;
        (void)_fc_Array_829;
        U32 _fi_USize_829 = 0;
        (void)_fi_USize_829;
        I64 _forin_err_kind_829 = 0;
        (void)_forin_err_kind_829;
        OutOfBounds *_forin_OutOfBounds_829 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_829->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_829;
        while (1) {
            U32 hoisted__U32_837 = Array_len(_fc_Array_829);
            (void)hoisted__U32_837;
            Bool _wcond_Bool_830 = U32_lt(_fi_USize_829, hoisted__U32_837);
            (void)_wcond_Bool_830;
            if (_wcond_Bool_830) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_829, &_fi_USize_829, &_forin_err_kind_829, _forin_OutOfBounds_829);
            I64 hoisted__I64_838 = 0;
            (void)hoisted__I64_838;
            Bool hoisted__Bool_839 = I64_eq(_forin_err_kind_829, hoisted__I64_838);
            (void)hoisted__Bool_839;
            Bool hoisted__Bool_840 = not(hoisted__Bool_839);
            (void)hoisted__Bool_840;
            if (hoisted__Bool_840) {
                Type *hoisted__Type_832 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_832;
                U32 hoisted__U32_833 = 1;
                (void)hoisted__U32_833;
                Array *_va_Array_25 = Array_new(hoisted__Type_832, hoisted__U32_833);
                (void)_va_Array_25;
                Type_delete(hoisted__Type_832, 1);
                U32 hoisted__U32_834 = 0;
                (void)hoisted__U32_834;
                Str hoisted__Str_835 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_835;
                Array_set(_va_Array_25, hoisted__U32_834, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_835; _oa; }));
                Str hoisted__Str_836 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_836;
                panic(&hoisted__Str_836, _va_Array_25);
                Str_delete(&hoisted__Str_836, (Bool){0});
            }
            U32 hoisted__U32_841 = 1;
            (void)hoisted__U32_841;
            U32 hoisted__U32_842 = U32_add(_fi_USize_829, hoisted__U32_841);
            (void)hoisted__U32_842;
            _fi_USize_829 = hoisted__U32_842;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_829, 1);
    }
    Array_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_849 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_849;
    if (hoisted__Bool_849) {
        Type *hoisted__Type_844 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_844;
        U32 hoisted__U32_845 = 1;
        (void)hoisted__U32_845;
        Array *_va_Array_26 = Array_new(hoisted__Type_844, hoisted__U32_845);
        (void)_va_Array_26;
        Type_delete(hoisted__Type_844, 1);
        U32 hoisted__U32_846 = 0;
        (void)hoisted__U32_846;
        Str hoisted__Str_847 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_847;
        Array_set(_va_Array_26, hoisted__U32_846, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_847; _oa; }));
        Str hoisted__Str_848 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_848;
        panic(&hoisted__Str_848, _va_Array_26);
        Str_delete(&hoisted__Str_848, (Bool){0});
    }
    void *hoisted__v_850 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_850;
    (void)hoisted__v_850;
    return hoisted__v_850;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_860 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_860;
    if (hoisted__Bool_860) {
        min_len = b->count;
    }
    {
        U32 _re_U32_852 = U32_clone(&min_len);
        (void)_re_U32_852;
        U32 _rc_U32_852 = 0;
        (void)_rc_U32_852;
        Bool hoisted__Bool_859 = U32_lte(_rc_U32_852, _re_U32_852);
        (void)hoisted__Bool_859;
        if (hoisted__Bool_859) {
            while (1) {
                Bool _wcond_Bool_853 = U32_lt(_rc_U32_852, _re_U32_852);
                (void)_wcond_Bool_853;
                if (_wcond_Bool_853) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_852);
                U32_inc(&_rc_U32_852);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_854 = 0;
                (void)hoisted__I64_854;
                Bool hoisted__Bool_855 = I64_neq(c, hoisted__I64_854);
                (void)hoisted__Bool_855;
                if (hoisted__Bool_855) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_856 = U32_gt(_rc_U32_852, _re_U32_852);
                (void)_wcond_Bool_856;
                if (_wcond_Bool_856) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_852);
                U32_dec(&_rc_U32_852);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_857 = 0;
                (void)hoisted__I64_857;
                Bool hoisted__Bool_858 = I64_neq(c, hoisted__I64_857);
                (void)hoisted__Bool_858;
                if (hoisted__Bool_858) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_861 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_861;
    return hoisted__I64_861;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_863 = 1;
    (void)hoisted__U32_863;
    U32 hoisted__U64_864 = U32_add(n, hoisted__U32_863);
    (void)hoisted__U64_864;
    void * buf = malloc(hoisted__U64_864);
    I32 hoisted__I32_865 = 0;
    (void)hoisted__I32_865;
    U64 hoisted__U64_866 = 1ULL;
    (void)hoisted__U64_866;
    memset(buf, hoisted__I32_865, hoisted__U64_866);
    I32_delete(&hoisted__I32_865, 0);
    I64 hoisted__I64_867 = 0;
    (void)hoisted__I64_867;
    Str *hoisted__Str_868 = malloc(sizeof(Str));
    hoisted__Str_868->c_str = buf;
    hoisted__Str_868->count = hoisted__I64_867;
    hoisted__Str_868->cap = n;
    (void)hoisted__Str_868;
    return hoisted__Str_868;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_883 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_883;
    if (hoisted__Bool_883) {
        Type *hoisted__Type_872 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_872;
        U32 hoisted__U32_873 = 1;
        (void)hoisted__U32_873;
        Array *_va_Array_27 = Array_new(hoisted__Type_872, hoisted__U32_873);
        (void)_va_Array_27;
        Type_delete(hoisted__Type_872, 1);
        U32 hoisted__U32_874 = 0;
        (void)hoisted__U32_874;
        Str hoisted__Str_875 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_875;
        Array_set(_va_Array_27, hoisted__U32_874, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_875; _oa; }));
        Str hoisted__Str_876 = (Str){.c_str = (void *)"./src/core/str.til:91:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_876;
        panic(&hoisted__Str_876, _va_Array_27);
        Str_delete(&hoisted__Str_876, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_884 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_884;
    if (hoisted__Bool_884) {
        Type *hoisted__Type_878 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_878;
        U32 hoisted__U32_879 = 1;
        (void)hoisted__U32_879;
        Array *_va_Array_28 = Array_new(hoisted__Type_878, hoisted__U32_879);
        (void)_va_Array_28;
        Type_delete(hoisted__Type_878, 1);
        U32 hoisted__U32_880 = 0;
        (void)hoisted__U32_880;
        Str hoisted__Str_881 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_881;
        Array_set(_va_Array_28, hoisted__U32_880, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_881; _oa; }));
        Str hoisted__Str_882 = (Str){.c_str = (void *)"./src/core/str.til:95:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_882;
        panic(&hoisted__Str_882, _va_Array_28);
        Str_delete(&hoisted__Str_882, (Bool){0});
    }
    void *hoisted__v_885 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_885;
    (void)hoisted__v_885;
    memcpy(hoisted__v_885, s->c_str, s->count);
    U32 hoisted__U32_886 = U32_clone(&new_len);
    (void)hoisted__U32_886;
    self->count = hoisted__U32_886;
    void *hoisted__v_887 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_887;
    (void)hoisted__v_887;
    I32 hoisted__I32_888 = 0;
    (void)hoisted__I32_888;
    U64 hoisted__U64_889 = 1ULL;
    (void)hoisted__U64_889;
    memset(hoisted__v_887, hoisted__I32_888, hoisted__U64_889);
    I32_delete(&hoisted__I32_888, 0);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_890 = 1;
    (void)hoisted__U32_890;
    U32 hoisted__U64_891 = U32_add(val->count, hoisted__U32_890);
    (void)hoisted__U64_891;
    void * new_data = malloc(hoisted__U64_891);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_892 = ptr_add(new_data, val->count);
    (void)hoisted__v_892;
    (void)hoisted__v_892;
    I32 hoisted__I32_893 = 0;
    (void)hoisted__I32_893;
    U64 hoisted__U64_894 = 1ULL;
    (void)hoisted__U64_894;
    memset(hoisted__v_892, hoisted__I32_893, hoisted__U64_894);
    I32_delete(&hoisted__I32_893, 0);
    Str *hoisted__Str_895 = malloc(sizeof(Str));
    hoisted__Str_895->c_str = new_data;
    hoisted__Str_895->count = val->count;
    hoisted__Str_895->cap = val->count;
    (void)hoisted__Str_895;
    return hoisted__Str_895;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_896 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_896;
    if (hoisted__Bool_896) {
        free(self->c_str);
    }
    if (call_free) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_1009 = 0;
    (void)hoisted__U32_1009;
    Bool hoisted__Bool_1010 = U32_eq(self->count, hoisted__U32_1009);
    (void)hoisted__Bool_1010;
    return hoisted__Bool_1010;
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_1103 = ((U64 (*)(I8 *, U32))(void *)hasher)(self->c_str, self->count);
    (void)hoisted__U64_1103;
    return hoisted__U64_1103;
}

U32 Str_size(void) {
    U32 hoisted__U32_1224 = 16;
    (void)hoisted__U32_1224;
    return hoisted__U32_1224;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1225 = Str_cmp(a, b);
    (void)hoisted__I64_1225;
    I64 hoisted__I64_1226 = 0;
    (void)hoisted__I64_1226;
    Bool hoisted__Bool_1227 = I64_eq(hoisted__I64_1225, hoisted__I64_1226);
    (void)hoisted__Bool_1227;
    return hoisted__Bool_1227;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1298 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1298->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1298;
    return hoisted__OutOfBounds_1298;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1299 = 0;
    (void)hoisted__Bool_1299;
    Str_delete(&self->msg, hoisted__Bool_1299);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1300 = 0;
    (void)hoisted__U32_1300;
    U64 hoisted__U64_1301 = ((U64 (*)(OutOfBounds *, U32))(void *)hasher)(self, hoisted__U32_1300);
    (void)hoisted__U64_1301;
    return hoisted__U64_1301;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1302 = 16;
    (void)hoisted__U32_1302;
    return hoisted__U32_1302;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1310 = 8;
    (void)hoisted__U32_1310;
    return hoisted__U32_1310;
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1517 = 0;
    (void)hoisted__I64_1517;
    Bool hoisted__Bool_1518 = I64_eq(val, hoisted__I64_1517);
    (void)hoisted__Bool_1518;
    if (hoisted__Bool_1518) {
        U64 hoisted__U64_1481 = 2ULL;
        (void)hoisted__U64_1481;
        void * buf = malloc(hoisted__U64_1481);
        I64 hoisted__I64_1482 = 48;
        (void)hoisted__I64_1482;
        U64 hoisted__U64_1483 = 1ULL;
        (void)hoisted__U64_1483;
        memcpy(buf, &hoisted__I64_1482, hoisted__U64_1483);
        U64 hoisted__U64_1484 = 1ULL;
        (void)hoisted__U64_1484;
        void *hoisted__v_1485 = ptr_add(buf, hoisted__U64_1484);
        (void)hoisted__v_1485;
        (void)hoisted__v_1485;
        I32 hoisted__I32_1486 = 0;
        (void)hoisted__I32_1486;
        U64 hoisted__U64_1487 = 1ULL;
        (void)hoisted__U64_1487;
        memset(hoisted__v_1485, hoisted__I32_1486, hoisted__U64_1487);
        I32_delete(&hoisted__I32_1486, 0);
        I64 hoisted__I64_1488 = 1;
        (void)hoisted__I64_1488;
        I64 hoisted__I64_1489 = 1;
        (void)hoisted__I64_1489;
        Str *hoisted__Str_1490 = malloc(sizeof(Str));
        hoisted__Str_1490->c_str = buf;
        hoisted__Str_1490->count = hoisted__I64_1488;
        hoisted__Str_1490->cap = hoisted__I64_1489;
        (void)hoisted__Str_1490;
        { Str * _ret_val = hoisted__Str_1490;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1519 = 0;
    (void)hoisted__I64_1519;
    Bool hoisted__Bool_1520 = I64_lt(val, hoisted__I64_1519);
    (void)hoisted__Bool_1520;
    if (hoisted__Bool_1520) {
        Bool hoisted__Bool_1491 = 1;
        (void)hoisted__Bool_1491;
        is_neg = hoisted__Bool_1491;
        I64 hoisted__I64_1492 = 0;
        (void)hoisted__I64_1492;
        I64 hoisted__I64_1493 = I64_sub(hoisted__I64_1492, val);
        (void)hoisted__I64_1493;
        v = hoisted__I64_1493;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1495 = 0;
        (void)hoisted__I64_1495;
        Bool _wcond_Bool_1494 = I64_gt(tmp, hoisted__I64_1495);
        (void)_wcond_Bool_1494;
        if (_wcond_Bool_1494) {
        } else {
            break;
        }
        U64 hoisted__U64_1496 = 1ULL;
        (void)hoisted__U64_1496;
        U64 hoisted__U64_1497 = U64_add(ndigits, hoisted__U64_1496);
        (void)hoisted__U64_1497;
        ndigits = hoisted__U64_1497;
        I64 hoisted__I64_1498 = 10;
        (void)hoisted__I64_1498;
        I64 hoisted__I64_1499 = I64_div(tmp, hoisted__I64_1498);
        (void)hoisted__I64_1499;
        tmp = hoisted__I64_1499;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1500 = 1ULL;
        (void)hoisted__U64_1500;
        U64 hoisted__U64_1501 = U64_add(total, hoisted__U64_1500);
        (void)hoisted__U64_1501;
        total = hoisted__U64_1501;
    }
    U64 hoisted__U64_1521 = 1ULL;
    (void)hoisted__U64_1521;
    U64 hoisted__U64_1522 = U64_add(total, hoisted__U64_1521);
    (void)hoisted__U64_1522;
    void * buf = malloc(hoisted__U64_1522);
    if (is_neg) {
        I64 hoisted__I64_1502 = 45;
        (void)hoisted__I64_1502;
        U64 hoisted__U64_1503 = 1ULL;
        (void)hoisted__U64_1503;
        memcpy(buf, &hoisted__I64_1502, hoisted__U64_1503);
    }
    U64 hoisted__U64_1523 = 1ULL;
    (void)hoisted__U64_1523;
    U64 i = U64_sub(total, hoisted__U64_1523);
    while (1) {
        I64 hoisted__I64_1505 = 0;
        (void)hoisted__I64_1505;
        Bool _wcond_Bool_1504 = I64_gt(v, hoisted__I64_1505);
        (void)_wcond_Bool_1504;
        if (_wcond_Bool_1504) {
        } else {
            break;
        }
        I64 hoisted__I64_1506 = 10;
        (void)hoisted__I64_1506;
        I64 hoisted__I64_1507 = I64_mod(v, hoisted__I64_1506);
        (void)hoisted__I64_1507;
        I64 hoisted__I64_1508 = 48;
        (void)hoisted__I64_1508;
        I64 hoisted__I64_1509 = I64_add(hoisted__I64_1507, hoisted__I64_1508);
        (void)hoisted__I64_1509;
        void *hoisted__v_1510 = ptr_add(buf, i);
        (void)hoisted__v_1510;
        (void)hoisted__v_1510;
        U8 hoisted__U8_1511 = I64_to_u8(hoisted__I64_1509);
        (void)hoisted__U8_1511;
        U64 hoisted__U64_1512 = 1ULL;
        (void)hoisted__U64_1512;
        memcpy(hoisted__v_1510, &hoisted__U8_1511, hoisted__U64_1512);
        U8_delete(&hoisted__U8_1511, 0);
        I64 hoisted__I64_1513 = 10;
        (void)hoisted__I64_1513;
        I64 hoisted__I64_1514 = I64_div(v, hoisted__I64_1513);
        (void)hoisted__I64_1514;
        v = hoisted__I64_1514;
        U64 hoisted__U64_1515 = 1ULL;
        (void)hoisted__U64_1515;
        U64 hoisted__U64_1516 = U64_sub(i, hoisted__U64_1515);
        (void)hoisted__U64_1516;
        i = hoisted__U64_1516;
    }
    void *hoisted__v_1524 = ptr_add(buf, total);
    (void)hoisted__v_1524;
    (void)hoisted__v_1524;
    I32 hoisted__I32_1525 = 0;
    (void)hoisted__I32_1525;
    U64 hoisted__U64_1526 = 1ULL;
    (void)hoisted__U64_1526;
    memset(hoisted__v_1524, hoisted__I32_1525, hoisted__U64_1526);
    I32_delete(&hoisted__I32_1525, 0);
    Str *hoisted__Str_1527 = malloc(sizeof(Str));
    hoisted__Str_1527->c_str = buf;
    hoisted__Str_1527->count = total;
    hoisted__Str_1527->cap = total;
    (void)hoisted__Str_1527;
    return hoisted__Str_1527;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1545 = 8;
    (void)hoisted__U32_1545;
    return hoisted__U32_1545;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1676 = 0;
    (void)hoisted__U32_1676;
    U64 hoisted__U64_1677 = ((U64 (*)(I64 *, U32))(void *)hasher)(&self, hoisted__U32_1676);
    (void)hoisted__U64_1677;
    return hoisted__U64_1677;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1680 = I64_cmp(a, b);
    (void)hoisted__I64_1680;
    I64 hoisted__I64_1681 = -1;
    (void)hoisted__I64_1681;
    Bool hoisted__Bool_1682 = I64_eq(hoisted__I64_1680, hoisted__I64_1681);
    (void)hoisted__Bool_1682;
    return hoisted__Bool_1682;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1683 = I64_cmp(a, b);
    (void)hoisted__I64_1683;
    I64 hoisted__I64_1684 = 1;
    (void)hoisted__I64_1684;
    Bool hoisted__Bool_1685 = I64_eq(hoisted__I64_1683, hoisted__I64_1684);
    (void)hoisted__Bool_1685;
    return hoisted__Bool_1685;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1686 = I64_eq(a, b);
    (void)hoisted__Bool_1686;
    Bool hoisted__Bool_1687 = not(hoisted__Bool_1686);
    (void)hoisted__Bool_1687;
    return hoisted__Bool_1687;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1705 = Bool_eq(a, b);
    (void)hoisted__Bool_1705;
    if (hoisted__Bool_1705) {
        I64 hoisted__I64_1703 = 0;
        (void)hoisted__I64_1703;
        { I64 _ret_val = hoisted__I64_1703;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1704 = -1;
        (void)hoisted__I64_1704;
        return hoisted__I64_1704;
    }
    I64 hoisted__I64_1706 = 1;
    (void)hoisted__I64_1706;
    return hoisted__I64_1706;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1707 = 1;
    (void)hoisted__U32_1707;
    return hoisted__U32_1707;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1708 = 0;
    (void)hoisted__U32_1708;
    U64 hoisted__U64_1709 = ((U64 (*)(Bool *, U32))(void *)hasher)(&self, hoisted__U32_1708);
    (void)hoisted__U64_1709;
    return hoisted__U64_1709;
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
    Bool hoisted__Bool_1855 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1855;
    if (hoisted__Bool_1855) {
        Bool hoisted__Bool_1853 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1853;
        { Bool _ret_val = hoisted__Bool_1853;
                return _ret_val; }
    }
    Bool hoisted__Bool_1856 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1856;
    if (hoisted__Bool_1856) {
        Bool hoisted__Bool_1854 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1854;
        { Bool _ret_val = hoisted__Bool_1854;
                return _ret_val; }
    }
    Bool hoisted__Bool_1857 = 0;
    (void)hoisted__Bool_1857;
    return hoisted__Bool_1857;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1863 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1863;
    if (hoisted__Bool_1863) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1864 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1864;
    if (hoisted__Bool_1864) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Str hoisted__Str_1865 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1865;
    UNREACHABLE(&hoisted__Str_1865);
    Str_delete(&hoisted__Str_1865, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1866 = 4;
    (void)hoisted__U32_1866;
    return hoisted__U32_1866;
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
void Type_delete(Type * self, Bool call_free) {
    Bool hoisted__Bool_1929 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1929;
    if (hoisted__Bool_1929) {
        Str *hoisted__Str_1921 = get_payload(self);
        (void)hoisted__Str_1921;
        (void)hoisted__Str_1921;
        Bool hoisted__Bool_1922 = 0;
        (void)hoisted__Bool_1922;
        Str_delete(hoisted__Str_1921, hoisted__Bool_1922);
    }
    Bool hoisted__Bool_1930 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1930;
    if (hoisted__Bool_1930) {
        Str *hoisted__Str_1923 = get_payload(self);
        (void)hoisted__Str_1923;
        (void)hoisted__Str_1923;
        Bool hoisted__Bool_1924 = 0;
        (void)hoisted__Bool_1924;
        Str_delete(hoisted__Str_1923, hoisted__Bool_1924);
    }
    Bool hoisted__Bool_1931 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1931;
    if (hoisted__Bool_1931) {
        Str *hoisted__Str_1925 = get_payload(self);
        (void)hoisted__Str_1925;
        (void)hoisted__Str_1925;
        Bool hoisted__Bool_1926 = 0;
        (void)hoisted__Bool_1926;
        Str_delete(hoisted__Str_1925, hoisted__Bool_1926);
    }
    Bool hoisted__Bool_1932 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1932;
    if (hoisted__Bool_1932) {
        Primitive *hoisted__Primitive_1927 = get_payload(self);
        (void)hoisted__Primitive_1927;
        (void)hoisted__Primitive_1927;
        Bool hoisted__Bool_1928 = 0;
        (void)hoisted__Bool_1928;
        Primitive_delete(hoisted__Primitive_1927, hoisted__Bool_1928);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2014 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2014;
    if (hoisted__Bool_2014) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2015 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2015;
    if (hoisted__Bool_2015) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2016 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)hoisted__Bool_2016;
    if (hoisted__Bool_2016) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2017 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)hoisted__Bool_2017;
    if (hoisted__Bool_2017) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2018 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)hoisted__Bool_2018;
    if (hoisted__Bool_2018) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2019 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)hoisted__Bool_2019;
    if (hoisted__Bool_2019) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2020 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)hoisted__Bool_2020;
    if (hoisted__Bool_2020) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2021 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)hoisted__Bool_2021;
    if (hoisted__Bool_2021) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2022 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)hoisted__Bool_2022;
    if (hoisted__Bool_2022) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool;
                return _r; }
    }
    Bool hoisted__Bool_2023 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2023;
    if (hoisted__Bool_2023) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_2008 = Str_clone(_clone_payload_Struct_9);
        (void)hoisted__Str_2008;
        Type *hoisted__Type_2009 = Type_Struct(hoisted__Str_2008);
        (void)hoisted__Type_2009;
        { Type * _ret_val = hoisted__Type_2009;
                return _ret_val; }
    }
    Bool hoisted__Bool_2024 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2024;
    if (hoisted__Bool_2024) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2025 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2025;
    if (hoisted__Bool_2025) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_2010 = Str_clone(_clone_payload_Enum_11);
        (void)hoisted__Str_2010;
        Type *hoisted__Type_2011 = Type_Enum(hoisted__Str_2010);
        (void)hoisted__Type_2011;
        { Type * _ret_val = hoisted__Type_2011;
                return _ret_val; }
    }
    Bool hoisted__Bool_2026 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2026;
    if (hoisted__Bool_2026) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2027 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2027;
    if (hoisted__Bool_2027) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2028 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2028;
    if (hoisted__Bool_2028) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2029 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2029;
    if (hoisted__Bool_2029) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2030 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2030;
    if (hoisted__Bool_2030) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_2012 = Str_clone(_clone_payload_Custom_16);
        (void)hoisted__Str_2012;
        Type *hoisted__Type_2013 = Type_Custom(hoisted__Str_2012);
        (void)hoisted__Type_2013;
        { Type * _ret_val = hoisted__Type_2013;
                return _ret_val; }
    }
    Bool hoisted__Bool_2031 = is(self, &(Type){.tag = Type_TAG_I8});
    (void)hoisted__Bool_2031;
    if (hoisted__Bool_2031) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8;
                return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive hoisted__Primitive_2032 = DEREF(_clone_payload_Primitive_18);
    (void)hoisted__Primitive_2032;
    Type *hoisted__Type_2033 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2032; _oa; }));
    (void)hoisted__Type_2033;
    return hoisted__Type_2033;
}

U32 Type_size(void) {
    U32 hoisted__U32_2034 = 24;
    (void)hoisted__U32_2034;
    return hoisted__U32_2034;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3731 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3731;
    if (hoisted__Bool_3731) {
        Type *hoisted__Type_3726 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3726;
        U32 hoisted__U32_3727 = 1;
        (void)hoisted__U32_3727;
        Array *_va_Array_113 = Array_new(hoisted__Type_3726, hoisted__U32_3727);
        (void)_va_Array_113;
        Type_delete(hoisted__Type_3726, 1);
        U32 hoisted__U32_3728 = 0;
        (void)hoisted__U32_3728;
        Str hoisted__Str_3729 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3729;
        Array_set(_va_Array_113, hoisted__U32_3728, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3729; _oa; }));
        Str hoisted__Str_3730 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3730;
        panic(&hoisted__Str_3730, _va_Array_113);
        Str_delete(&hoisted__Str_3730, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3732 = calloc(cap, elem_size);
    (void)hoisted__v_3732;
    void * hoisted__v_3733 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3733;
    void * hoisted__v_3734 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3734;
    Array *hoisted__Array_3735 = malloc(sizeof(Array));
    hoisted__Array_3735->data = hoisted__v_3732;
    hoisted__Array_3735->cap = cap;
    hoisted__Array_3735->elem_size = elem_size;
    hoisted__Array_3735->elem_clone = hoisted__v_3733;
    hoisted__Array_3735->elem_delete = hoisted__v_3734;
    (void)hoisted__Array_3735;
    return hoisted__Array_3735;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3736 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3736;
    Str_delete(elem_type, 1);
    return hoisted__Array_3736;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3757 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3757;
    if (hoisted__Bool_3757) {
        Type *hoisted__Type_3738 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3738;
        U32 hoisted__U32_3739 = 6;
        (void)hoisted__U32_3739;
        Array *_va_Array_114 = Array_new(hoisted__Type_3738, hoisted__U32_3739);
        (void)_va_Array_114;
        Type_delete(hoisted__Type_3738, 1);
        U32 hoisted__U32_3740 = 0;
        (void)hoisted__U32_3740;
        Str hoisted__Str_3741 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3741;
        Array_set(_va_Array_114, hoisted__U32_3740, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3741; _oa; }));
        U32 hoisted__U32_3742 = 1;
        (void)hoisted__U32_3742;
        Str hoisted__Str_3743 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3743;
        Array_set(_va_Array_114, hoisted__U32_3742, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3743; _oa; }));
        U32 hoisted__U32_3744 = 2;
        (void)hoisted__U32_3744;
        Str *hoisted__Str_3745 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3745;
        Array_set(_va_Array_114, hoisted__U32_3744, hoisted__Str_3745);
        U32 hoisted__U32_3746 = 3;
        (void)hoisted__U32_3746;
        Str hoisted__Str_3747 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3747;
        Array_set(_va_Array_114, hoisted__U32_3746, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3747; _oa; }));
        U32 hoisted__U32_3748 = 4;
        (void)hoisted__U32_3748;
        Str *hoisted__Str_3749 = U32_to_str(self->cap);
        (void)hoisted__Str_3749;
        Array_set(_va_Array_114, hoisted__U32_3748, hoisted__Str_3749);
        U32 hoisted__U32_3750 = 5;
        (void)hoisted__U32_3750;
        Str hoisted__Str_3751 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3751;
        Array_set(_va_Array_114, hoisted__U32_3750, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3751; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3752 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_114); hoisted__OutOfBounds_3752->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3752;
        U32 hoisted__U32_3753 = 16;
        (void)hoisted__U32_3753;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3752, hoisted__U32_3753);
        OutOfBounds_delete(hoisted__OutOfBounds_3752, 1);
        I64 hoisted__I64_3754 = 3;
        (void)hoisted__I64_3754;
        *_err_kind = hoisted__I64_3754;
    }
    I64 hoisted__I64_3758 = 0;
    (void)hoisted__I64_3758;
    Bool hoisted__Bool_3759 = I64_eq(DEREF(_err_kind), hoisted__I64_3758);
    (void)hoisted__Bool_3759;
    if (hoisted__Bool_3759) {
        U32 hoisted__U64_3755 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3755;
        void *hoisted__v_3756 = ptr_add(self->data, hoisted__U64_3755);
        (void)hoisted__v_3756;
        (void)hoisted__v_3756;
        { void * _ret_val = hoisted__v_3756;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3774 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3774;
    if (hoisted__Bool_3774) {
        Type *hoisted__Type_3761 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3761;
        U32 hoisted__U32_3762 = 5;
        (void)hoisted__U32_3762;
        Array *_va_Array_115 = Array_new(hoisted__Type_3761, hoisted__U32_3762);
        (void)_va_Array_115;
        Type_delete(hoisted__Type_3761, 1);
        U32 hoisted__U32_3763 = 0;
        (void)hoisted__U32_3763;
        Str hoisted__Str_3764 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3764;
        Array_set(_va_Array_115, hoisted__U32_3763, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3764; _oa; }));
        U32 hoisted__U32_3765 = 1;
        (void)hoisted__U32_3765;
        Str *hoisted__Str_3766 = U32_to_str(i);
        (void)hoisted__Str_3766;
        Array_set(_va_Array_115, hoisted__U32_3765, hoisted__Str_3766);
        U32 hoisted__U32_3767 = 2;
        (void)hoisted__U32_3767;
        Str hoisted__Str_3768 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3768;
        Array_set(_va_Array_115, hoisted__U32_3767, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3768; _oa; }));
        U32 hoisted__U32_3769 = 3;
        (void)hoisted__U32_3769;
        Str *hoisted__Str_3770 = U32_to_str(self->cap);
        (void)hoisted__Str_3770;
        Array_set(_va_Array_115, hoisted__U32_3769, hoisted__Str_3770);
        U32 hoisted__U32_3771 = 4;
        (void)hoisted__U32_3771;
        Str hoisted__Str_3772 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3772;
        Array_set(_va_Array_115, hoisted__U32_3771, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3772; _oa; }));
        Str hoisted__Str_3773 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3773;
        panic(&hoisted__Str_3773, _va_Array_115);
        Str_delete(&hoisted__Str_3773, (Bool){0});
    }
    U32 hoisted__U64_3775 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3775;
    void *hoisted__v_3776 = ptr_add(self->data, hoisted__U64_3775);
    (void)hoisted__v_3776;
    (void)hoisted__v_3776;
    Bool hoisted__Bool_3777 = 0;
    (void)hoisted__Bool_3777;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3776, hoisted__Bool_3777);
    U32 hoisted__U64_3778 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3778;
    void *hoisted__v_3779 = ptr_add(self->data, hoisted__U64_3778);
    (void)hoisted__v_3779;
    (void)hoisted__v_3779;
    memcpy(hoisted__v_3779, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3780 = self->cap;
        (void)_re_U32_3780;
        U32 _rc_U32_3780 = 0;
        (void)_rc_U32_3780;
        Bool hoisted__Bool_3789 = U32_lte(_rc_U32_3780, _re_U32_3780);
        (void)hoisted__Bool_3789;
        if (hoisted__Bool_3789) {
            while (1) {
                Bool _wcond_Bool_3781 = U32_lt(_rc_U32_3780, _re_U32_3780);
                (void)_wcond_Bool_3781;
                if (_wcond_Bool_3781) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3780);
                U32_inc(&_rc_U32_3780);
                U32 hoisted__U64_3782 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3782;
                void *hoisted__v_3783 = ptr_add(self->data, hoisted__U64_3782);
                (void)hoisted__v_3783;
                (void)hoisted__v_3783;
                Bool hoisted__Bool_3784 = 0;
                (void)hoisted__Bool_3784;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3783, hoisted__Bool_3784);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3785 = U32_gt(_rc_U32_3780, _re_U32_3780);
                (void)_wcond_Bool_3785;
                if (_wcond_Bool_3785) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3780);
                U32_dec(&_rc_U32_3780);
                U32 hoisted__U64_3786 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3786;
                void *hoisted__v_3787 = ptr_add(self->data, hoisted__U64_3786);
                (void)hoisted__v_3787;
                (void)hoisted__v_3787;
                Bool hoisted__Bool_3788 = 0;
                (void)hoisted__Bool_3788;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3787, hoisted__Bool_3788);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3802 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3802;
    void * new_data = malloc(hoisted__U64_3802);
    {
        U32 _re_U32_3790 = self->cap;
        (void)_re_U32_3790;
        U32 _rc_U32_3790 = 0;
        (void)_rc_U32_3790;
        Bool hoisted__Bool_3801 = U32_lte(_rc_U32_3790, _re_U32_3790);
        (void)hoisted__Bool_3801;
        if (hoisted__Bool_3801) {
            while (1) {
                Bool _wcond_Bool_3791 = U32_lt(_rc_U32_3790, _re_U32_3790);
                (void)_wcond_Bool_3791;
                if (_wcond_Bool_3791) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3790);
                U32_inc(&_rc_U32_3790);
                U32 hoisted__U64_3792 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3792;
                void *hoisted__v_3793 = ptr_add(self->data, hoisted__U64_3792);
                (void)hoisted__v_3793;
                (void)hoisted__v_3793;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3793);
                U32 hoisted__U64_3794 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3794;
                void *hoisted__v_3795 = ptr_add(new_data, hoisted__U64_3794);
                (void)hoisted__v_3795;
                (void)hoisted__v_3795;
                memcpy(hoisted__v_3795, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3796 = U32_gt(_rc_U32_3790, _re_U32_3790);
                (void)_wcond_Bool_3796;
                if (_wcond_Bool_3796) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3790);
                U32_dec(&_rc_U32_3790);
                U32 hoisted__U64_3797 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3797;
                void *hoisted__v_3798 = ptr_add(self->data, hoisted__U64_3797);
                (void)hoisted__v_3798;
                (void)hoisted__v_3798;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3798);
                U32 hoisted__U64_3799 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3799;
                void *hoisted__v_3800 = ptr_add(new_data, hoisted__U64_3799);
                (void)hoisted__v_3800;
                (void)hoisted__v_3800;
                memcpy(hoisted__v_3800, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3803 = malloc(sizeof(Array));
    hoisted__Array_3803->data = new_data;
    hoisted__Array_3803->cap = self->cap;
    hoisted__Array_3803->elem_size = self->elem_size;
    hoisted__Array_3803->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3803->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3803;
    return hoisted__Array_3803;
}

U32 Array_size(void) {
    U32 hoisted__U32_3804 = 32;
    (void)hoisted__U32_3804;
    return hoisted__U32_3804;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4177 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4177;
    U32 hoisted__U32_4178 = 3;
    (void)hoisted__U32_4178;
    Array *_va_Array_147 = Array_new(hoisted__Type_4177, hoisted__U32_4178);
    (void)_va_Array_147;
    Type_delete(hoisted__Type_4177, 1);
    U32 hoisted__U32_4179 = 0;
    (void)hoisted__U32_4179;
    Str *hoisted__Str_4180 = Str_clone(loc_str);
    (void)hoisted__Str_4180;
    Array_set(_va_Array_147, hoisted__U32_4179, hoisted__Str_4180);
    U32 hoisted__U32_4181 = 1;
    (void)hoisted__U32_4181;
    Str hoisted__Str_4182 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4182;
    Array_set(_va_Array_147, hoisted__U32_4181, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4182; _oa; }));
    Array *hoisted__Array_4183 = Array_clone(parts);
    (void)hoisted__Array_4183;
    Array_delete(parts, 1);
    U32 hoisted__U32_4184 = 2;
    (void)hoisted__U32_4184;
    Str *hoisted__Str_4185 = format(hoisted__Array_4183);
    (void)hoisted__Str_4185;
    Array_set(_va_Array_147, hoisted__U32_4184, hoisted__Str_4185);
    println(_va_Array_147);
    I64 hoisted__I64_4186 = 1;
    (void)hoisted__I64_4186;
    exit(hoisted__I64_4186);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4196 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4196;
    U32 hoisted__U32_4197 = 1;
    (void)hoisted__U32_4197;
    Array *_va_Array_149 = Array_new(hoisted__Type_4196, hoisted__U32_4197);
    (void)_va_Array_149;
    Type_delete(hoisted__Type_4196, 1);
    U32 hoisted__U32_4198 = 0;
    (void)hoisted__U32_4198;
    Str hoisted__Str_4199 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4199;
    Array_set(_va_Array_149, hoisted__U32_4198, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4199; _oa; }));
    panic(loc_str, _va_Array_149);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4205 = not(cond);
    (void)hoisted__Bool_4205;
    if (hoisted__Bool_4205) {
        Type *hoisted__Type_4201 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4201;
        U32 hoisted__U32_4202 = 1;
        (void)hoisted__U32_4202;
        Array *_va_Array_150 = Array_new(hoisted__Type_4201, hoisted__U32_4202);
        (void)_va_Array_150;
        Type_delete(hoisted__Type_4201, 1);
        U32 hoisted__U32_4203 = 0;
        (void)hoisted__U32_4203;
        Str hoisted__Str_4204 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4204;
        Array_set(_va_Array_150, hoisted__U32_4203, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4204; _oa; }));
        panic(loc_str, _va_Array_150);
    }
    Bool hoisted__Bool_4206 = 1;
    (void)hoisted__Bool_4206;
    return hoisted__Bool_4206;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4229 = I64_neq(a, b);
    (void)hoisted__Bool_4229;
    if (hoisted__Bool_4229) {
        Type *hoisted__Type_4217 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4217;
        U32 hoisted__U32_4218 = 5;
        (void)hoisted__U32_4218;
        Array *_va_Array_152 = Array_new(hoisted__Type_4217, hoisted__U32_4218);
        (void)_va_Array_152;
        Type_delete(hoisted__Type_4217, 1);
        U32 hoisted__U32_4219 = 0;
        (void)hoisted__U32_4219;
        Str hoisted__Str_4220 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4220;
        Array_set(_va_Array_152, hoisted__U32_4219, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4220; _oa; }));
        U32 hoisted__U32_4221 = 1;
        (void)hoisted__U32_4221;
        Str *hoisted__Str_4222 = I64_to_str(a);
        (void)hoisted__Str_4222;
        Array_set(_va_Array_152, hoisted__U32_4221, hoisted__Str_4222);
        U32 hoisted__U32_4223 = 2;
        (void)hoisted__U32_4223;
        Str hoisted__Str_4224 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4224;
        Array_set(_va_Array_152, hoisted__U32_4223, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4224; _oa; }));
        U32 hoisted__U32_4225 = 3;
        (void)hoisted__U32_4225;
        Str *hoisted__Str_4226 = I64_to_str(b);
        (void)hoisted__Str_4226;
        Array_set(_va_Array_152, hoisted__U32_4225, hoisted__Str_4226);
        U32 hoisted__U32_4227 = 4;
        (void)hoisted__U32_4227;
        Str hoisted__Str_4228 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4228;
        Array_set(_va_Array_152, hoisted__U32_4227, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4228; _oa; }));
        panic(loc_str, _va_Array_152);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4243 = Str_eq(a, b);
    (void)hoisted__Bool_4243;
    Bool hoisted__Bool_4244 = not(hoisted__Bool_4243);
    (void)hoisted__Bool_4244;
    if (hoisted__Bool_4244) {
        Type *hoisted__Type_4231 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4231;
        U32 hoisted__U32_4232 = 5;
        (void)hoisted__U32_4232;
        Array *_va_Array_153 = Array_new(hoisted__Type_4231, hoisted__U32_4232);
        (void)_va_Array_153;
        Type_delete(hoisted__Type_4231, 1);
        U32 hoisted__U32_4233 = 0;
        (void)hoisted__U32_4233;
        Str hoisted__Str_4234 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4234;
        Array_set(_va_Array_153, hoisted__U32_4233, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4234; _oa; }));
        U32 hoisted__U32_4235 = 1;
        (void)hoisted__U32_4235;
        Str *hoisted__Str_4236 = Str_clone(a);
        (void)hoisted__Str_4236;
        Array_set(_va_Array_153, hoisted__U32_4235, hoisted__Str_4236);
        U32 hoisted__U32_4237 = 2;
        (void)hoisted__U32_4237;
        Str hoisted__Str_4238 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4238;
        Array_set(_va_Array_153, hoisted__U32_4237, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4238; _oa; }));
        U32 hoisted__U32_4239 = 3;
        (void)hoisted__U32_4239;
        Str *hoisted__Str_4240 = Str_clone(b);
        (void)hoisted__Str_4240;
        Array_set(_va_Array_153, hoisted__U32_4239, hoisted__Str_4240);
        U32 hoisted__U32_4241 = 4;
        (void)hoisted__U32_4241;
        Str hoisted__Str_4242 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4242;
        Array_set(_va_Array_153, hoisted__U32_4241, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4242; _oa; }));
        panic(loc_str, _va_Array_153);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4245 = parts;
        (void)_fc_Array_4245;
        (void)_fc_Array_4245;
        U32 _fi_USize_4245 = 0;
        (void)_fi_USize_4245;
        I64 _forin_err_kind_4245 = 0;
        (void)_forin_err_kind_4245;
        OutOfBounds *_forin_OutOfBounds_4245 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4245->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4245;
        while (1) {
            U32 hoisted__U32_4253 = Array_len(_fc_Array_4245);
            (void)hoisted__U32_4253;
            Bool _wcond_Bool_4246 = U32_lt(_fi_USize_4245, hoisted__U32_4253);
            (void)_wcond_Bool_4246;
            if (_wcond_Bool_4246) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4245, &_fi_USize_4245, &_forin_err_kind_4245, _forin_OutOfBounds_4245);
            I64 hoisted__I64_4254 = 0;
            (void)hoisted__I64_4254;
            Bool hoisted__Bool_4255 = I64_eq(_forin_err_kind_4245, hoisted__I64_4254);
            (void)hoisted__Bool_4255;
            Bool hoisted__Bool_4256 = not(hoisted__Bool_4255);
            (void)hoisted__Bool_4256;
            if (hoisted__Bool_4256) {
                Type *hoisted__Type_4248 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4248;
                U32 hoisted__U32_4249 = 1;
                (void)hoisted__U32_4249;
                Array *_va_Array_154 = Array_new(hoisted__Type_4248, hoisted__U32_4249);
                (void)_va_Array_154;
                Type_delete(hoisted__Type_4248, 1);
                U32 hoisted__U32_4250 = 0;
                (void)hoisted__U32_4250;
                Str hoisted__Str_4251 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4251;
                Array_set(_va_Array_154, hoisted__U32_4250, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4251; _oa; }));
                Str hoisted__Str_4252 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4252;
                panic(&hoisted__Str_4252, _va_Array_154);
                Str_delete(&hoisted__Str_4252, (Bool){0});
            }
            U32 hoisted__U32_4257 = 1;
            (void)hoisted__U32_4257;
            U32 hoisted__U32_4258 = U32_add(_fi_USize_4245, hoisted__U32_4257);
            (void)hoisted__U32_4258;
            _fi_USize_4245 = hoisted__U32_4258;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4245, 1);
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
    Str hoisted__Str_4513 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4513;
    I64 hoisted__I64_4514 = 3;
    (void)hoisted__I64_4514;
    assert_eq(&hoisted__Str_4513, result, hoisted__I64_4514);
    Str_delete(&hoisted__Str_4513, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4521 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4521;
    I64 hoisted__I64_4522 = 15;
    (void)hoisted__I64_4522;
    assert_eq(&hoisted__Str_4521, result, hoisted__I64_4522);
    Str_delete(&hoisted__Str_4521, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4529 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4529;
    I64 hoisted__I64_4530 = 26;
    (void)hoisted__I64_4530;
    assert_eq(&hoisted__Str_4529, result, hoisted__I64_4530);
    Str_delete(&hoisted__Str_4529, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4533 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4533;
    Str hoisted__Str_4534 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4534;
    assert_eq_str(&hoisted__Str_4533, &result, &hoisted__Str_4534);
    Str_delete(&hoisted__Str_4533, (Bool){0});
    Str_delete(&hoisted__Str_4534, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4865 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4865;
    assert_eq_str(&hoisted__Str_4865, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4865, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4866 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4866;
    assert_eq_str(&hoisted__Str_4866, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4866, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4868 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4868;
    I64 hoisted__I64_4869 = 8;
    (void)hoisted__I64_4869;
    assert_eq(&hoisted__Str_4868, result, hoisted__I64_4869);
    Str_delete(&hoisted__Str_4868, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4872 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4872;
    Bool hoisted__Bool_4873 = 1;
    (void)hoisted__Bool_4873;
    assert(&hoisted__Str_4872, hoisted__Bool_4873);
    Str_delete(&hoisted__Str_4872, (Bool){0});
    Str hoisted__Str_4876 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4876;
    Bool hoisted__Bool_4877 = 1;
    (void)hoisted__Bool_4877;
    assert(&hoisted__Str_4876, hoisted__Bool_4877);
    Str_delete(&hoisted__Str_4876, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4882 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4882;
    Str hoisted__Str_4883 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4883;
    Str hoisted__Str_4884 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4884;
    assert_eq_str(&hoisted__Str_4882, &hoisted__Str_4883, &hoisted__Str_4884);
    Str_delete(&hoisted__Str_4882, (Bool){0});
    Str_delete(&hoisted__Str_4883, (Bool){0});
    Str_delete(&hoisted__Str_4884, (Bool){0});
    Str hoisted__Str_4887 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4887;
    Str hoisted__Str_4888 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4888;
    Str hoisted__Str_4889 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4889;
    assert_eq_str(&hoisted__Str_4887, &hoisted__Str_4888, &hoisted__Str_4889);
    Str_delete(&hoisted__Str_4887, (Bool){0});
    Str_delete(&hoisted__Str_4888, (Bool){0});
    Str_delete(&hoisted__Str_4889, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4894 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4894;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4894;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_4895 = 0;
    (void)hoisted__U32_4895;
    U64 hoisted__U64_4896 = ((U64 (*)(CfVec2 *, U32))(void *)hasher)(self, hoisted__U32_4895);
    (void)hoisted__U64_4896;
    return hoisted__U64_4896;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4897 = 16;
    (void)hoisted__U32_4897;
    return hoisted__U32_4897;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4898 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4898;
    I64 hoisted__I64_4899 = 42;
    (void)hoisted__I64_4899;
    assert_eq(&hoisted__Str_4898, v.x, hoisted__I64_4899);
    Str_delete(&hoisted__Str_4898, (Bool){0});
    Str hoisted__Str_4900 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4900;
    I64 hoisted__I64_4901 = 99;
    (void)hoisted__I64_4901;
    assert_eq(&hoisted__Str_4900, v.y, hoisted__I64_4901);
    Str_delete(&hoisted__Str_4900, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4904 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4904;
    I64 hoisted__I64_4905 = 10;
    (void)hoisted__I64_4905;
    assert_eq(&hoisted__Str_4904, p.x, hoisted__I64_4905);
    Str_delete(&hoisted__Str_4904, (Bool){0});
    Str hoisted__Str_4906 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4906;
    I64 hoisted__I64_4907 = 20;
    (void)hoisted__I64_4907;
    assert_eq(&hoisted__Str_4906, p.y, hoisted__I64_4907);
    Str_delete(&hoisted__Str_4906, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4913 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4913;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4913;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_4914 = 0;
    (void)hoisted__U32_4914;
    U64 hoisted__U64_4915 = ((U64 (*)(CfRect *, U32))(void *)hasher)(self, hoisted__U32_4914);
    (void)hoisted__U64_4915;
    return hoisted__U64_4915;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4916 = 32;
    (void)hoisted__U32_4916;
    return hoisted__U32_4916;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4917 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4917;
    I64 hoisted__I64_4918 = 5;
    (void)hoisted__I64_4918;
    assert_eq(&hoisted__Str_4917, r.top_left.x, hoisted__I64_4918);
    Str_delete(&hoisted__Str_4917, (Bool){0});
    Str hoisted__Str_4919 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4919;
    I64 hoisted__I64_4920 = 10;
    (void)hoisted__I64_4920;
    assert_eq(&hoisted__Str_4919, r.top_left.y, hoisted__I64_4920);
    Str_delete(&hoisted__Str_4919, (Bool){0});
    Str hoisted__Str_4921 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4921;
    I64 hoisted__I64_4922 = 100;
    (void)hoisted__I64_4922;
    assert_eq(&hoisted__Str_4921, r.bottom_right.x, hoisted__I64_4922);
    Str_delete(&hoisted__Str_4921, (Bool){0});
    Str hoisted__Str_4923 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4923;
    I64 hoisted__I64_4924 = 200;
    (void)hoisted__I64_4924;
    assert_eq(&hoisted__Str_4923, r.bottom_right.y, hoisted__I64_4924);
    Str_delete(&hoisted__Str_4923, (Bool){0});
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
    Bool hoisted__Bool_4929 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4929;
    if (hoisted__Bool_4929) {
        Bool hoisted__Bool_4926 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4926;
        { Bool _ret_val = hoisted__Bool_4926;
                return _ret_val; }
    }
    Bool hoisted__Bool_4930 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4930;
    if (hoisted__Bool_4930) {
        Bool hoisted__Bool_4927 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4927;
        { Bool _ret_val = hoisted__Bool_4927;
                return _ret_val; }
    }
    Bool hoisted__Bool_4931 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4931;
    if (hoisted__Bool_4931) {
        Bool hoisted__Bool_4928 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4928;
        { Bool _ret_val = hoisted__Bool_4928;
                return _ret_val; }
    }
    Bool hoisted__Bool_4932 = 0;
    (void)hoisted__Bool_4932;
    return hoisted__Bool_4932;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4940 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4940;
    if (hoisted__Bool_4940) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4941 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4941;
    if (hoisted__Bool_4941) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4942 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4942;
    if (hoisted__Bool_4942) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4943 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4943;
    UNREACHABLE(&hoisted__Str_4943);
    Str_delete(&hoisted__Str_4943, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4944 = 4;
    (void)hoisted__U32_4944;
    return hoisted__U32_4944;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_4945 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4945;
    Bool hoisted__Bool_4946 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4946;
    assert(&hoisted__Str_4945, hoisted__Bool_4946);
    Str_delete(&hoisted__Str_4945, (Bool){0});
    Bool hoisted__Bool_4947 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4947;
    Str hoisted__Str_4948 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4948;
    Bool hoisted__Bool_4949 = not(hoisted__Bool_4947);
    (void)hoisted__Bool_4949;
    assert(&hoisted__Str_4948, hoisted__Bool_4949);
    Str_delete(&hoisted__Str_4948, (Bool){0});
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
    Bool hoisted__Bool_4950 = is(self, other);
    (void)hoisted__Bool_4950;
    return hoisted__Bool_4950;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_4968 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4968;
    if (hoisted__Bool_4968) {
        I64 *hoisted__I64_4964 = get_payload(self);
        (void)hoisted__I64_4964;
        (void)hoisted__I64_4964;
        Bool hoisted__Bool_4965 = 0;
        (void)hoisted__Bool_4965;
        I64_delete(hoisted__I64_4964, hoisted__Bool_4965);
    }
    Bool hoisted__Bool_4969 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4969;
    if (hoisted__Bool_4969) {
        Str *hoisted__Str_4966 = get_payload(self);
        (void)hoisted__Str_4966;
        (void)hoisted__Str_4966;
        Bool hoisted__Bool_4967 = 0;
        (void)hoisted__Bool_4967;
        Str_delete(hoisted__Str_4966, hoisted__Bool_4967);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4998 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4998;
    if (hoisted__Bool_4998) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4995 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4995;
        { Token * _ret_val = hoisted__Token_4995;
                return _ret_val; }
    }
    Bool hoisted__Bool_4999 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4999;
    if (hoisted__Bool_4999) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4996 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4996;
        Token *hoisted__Token_4997 = Token_Name(hoisted__Str_4996);
        (void)hoisted__Token_4997;
        { Token * _ret_val = hoisted__Token_4997;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_5000 = 24;
    (void)hoisted__U32_5000;
    return hoisted__U32_5000;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_5002 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5002;
    Bool hoisted__Bool_5003 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5003;
    assert(&hoisted__Str_5002, hoisted__Bool_5003);
    Str_delete(&hoisted__Str_5002, (Bool){0});
    Bool hoisted__Bool_5004 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5004;
    Token_delete(t, 1);
    Str hoisted__Str_5005 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5005;
    Bool hoisted__Bool_5006 = not(hoisted__Bool_5004);
    (void)hoisted__Bool_5006;
    assert(&hoisted__Str_5005, hoisted__Bool_5006);
    Str_delete(&hoisted__Str_5005, (Bool){0});
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_5007 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5007;
    Bool hoisted__Bool_5008 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5008;
    assert(&hoisted__Str_5007, hoisted__Bool_5008);
    Str_delete(&hoisted__Str_5007, (Bool){0});
    Bool hoisted__Bool_5009 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5009;
    Str hoisted__Str_5010 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5010;
    Bool hoisted__Bool_5011 = not(hoisted__Bool_5009);
    (void)hoisted__Bool_5011;
    assert(&hoisted__Str_5010, hoisted__Bool_5011);
    Str_delete(&hoisted__Str_5010, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_5014 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5014;
    Bool hoisted__Bool_5015 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5015;
    assert(&hoisted__Str_5014, hoisted__Bool_5015);
    Str_delete(&hoisted__Str_5014, (Bool){0});
    Bool hoisted__Bool_5016 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5016;
    Token_delete(t, 1);
    Str hoisted__Str_5017 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5017;
    Bool hoisted__Bool_5018 = not(hoisted__Bool_5016);
    (void)hoisted__Bool_5018;
    assert(&hoisted__Str_5017, hoisted__Bool_5018);
    Str_delete(&hoisted__Str_5017, (Bool){0});
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
