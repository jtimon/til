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

U64 F32_hash(F32 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
U64 U32_hash(U32 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
Bool U32_lt(U32 a, U32 b);
Bool U32_gt(U32 a, U32 b);
Bool U32_lte(U32 a, U32 b);
Bool U32_gte(U32 a, U32 b);
U64 I32_hash(I32 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
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
U32 OutOfBounds_size(void);
U32 Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool _cf);
Str * I64_to_str(I64 val);
U64 I64_hash(I64 self, HashFn hasher);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
Bool I64_lt(I64 a, I64 b);
Bool I64_gt(I64 a, I64 b);
Bool I64_neq(I64 a, I64 b);
I64 Bool_cmp(Bool a, Bool b);
U64 Bool_hash(Bool self, HashFn hasher);
void Bool_delete(Bool * self, Bool call_free);
U32 Bool_size(void);
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
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
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

U64 F32_hash(F32 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
U64 U32_hash(U32 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
Bool U32_lt(U32 a, U32 b);
Bool U32_gt(U32 a, U32 b);
Bool U32_lte(U32 a, U32 b);
Bool U32_gte(U32 a, U32 b);
U64 I32_hash(I32 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U8_delete(U8 * self, Bool call_free);
U32 U8_size(void);
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
U32 OutOfBounds_size(void);
U32 Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool _cf);
Str * I64_to_str(I64 val);
U64 I64_hash(I64 self, HashFn hasher);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
Bool I64_lt(I64 a, I64 b);
Bool I64_gt(I64 a, I64 b);
Bool I64_neq(I64 a, I64 b);
I64 Bool_cmp(Bool a, Bool b);
U64 Bool_hash(Bool self, HashFn hasher);
void Bool_delete(Bool * self, Bool call_free);
U32 Bool_size(void);
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
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
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

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_2 = 4;
    (void)hoisted__U32_2;
    U64 hoisted__U64_3 = ((U64 (*)(F32 *, U32))(void *)hasher)(&self, hoisted__U32_2);
    (void)hoisted__U64_3;
    return hoisted__U64_3;
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 F32_size(void) {
    U32 hoisted__U32_4 = 4;
    (void)hoisted__U32_4;
    return hoisted__U32_4;
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_36 = 8;
    (void)hoisted__U32_36;
    U64 hoisted__U64_37 = ((U64 (*)(U64 *, U32))(void *)hasher)(&self, hoisted__U32_36);
    (void)hoisted__U64_37;
    return hoisted__U64_37;
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U64_size(void) {
    U32 hoisted__U32_41 = 8;
    (void)hoisted__U32_41;
    return hoisted__U32_41;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_129 = U32_to_i64(val);
    (void)hoisted__I64_129;
    Str *hoisted__Str_130 = I64_to_str(hoisted__I64_129);
    (void)hoisted__Str_130;
    return hoisted__Str_130;
}

void U32_inc(U32 * self) {
    U32 hoisted__U32_131 = 1;
    (void)hoisted__U32_131;
    U32 hoisted__U32_132 = U32_add(DEREF(self), hoisted__U32_131);
    (void)hoisted__U32_132;
    *self = hoisted__U32_132;
}

void U32_dec(U32 * self) {
    U32 hoisted__U32_133 = 1;
    (void)hoisted__U32_133;
    U32 hoisted__U32_134 = U32_sub(DEREF(self), hoisted__U32_133);
    (void)hoisted__U32_134;
    *self = hoisted__U32_134;
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_137 = 4;
    (void)hoisted__U32_137;
    U64 hoisted__U64_138 = ((U64 (*)(U32 *, U32))(void *)hasher)(&self, hoisted__U32_137);
    (void)hoisted__U64_138;
    return hoisted__U64_138;
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_144 = 4;
    (void)hoisted__U32_144;
    return hoisted__U32_144;
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

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_252 = 4;
    (void)hoisted__U32_252;
    U64 hoisted__U64_253 = ((U64 (*)(I32 *, U32))(void *)hasher)(&self, hoisted__U32_252);
    (void)hoisted__U64_253;
    return hoisted__U64_253;
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

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_420 = 1;
    (void)hoisted__U32_420;
    U64 hoisted__U64_421 = ((U64 (*)(I8 *, U32))(void *)hasher)(&self, hoisted__U32_420);
    (void)hoisted__U64_421;
    return hoisted__U64_421;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_427 = 1;
    (void)hoisted__U32_427;
    return hoisted__U32_427;
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_450 = 1;
    (void)hoisted__U32_450;
    U64 hoisted__U64_451 = ((U64 (*)(U8 *, U32))(void *)hasher)(&self, hoisted__U32_450);
    (void)hoisted__U64_451;
    return hoisted__U64_451;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_457 = 1;
    (void)hoisted__U32_457;
    return hoisted__U32_457;
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
    U64 hoisted__U64_1115 = ((U64 (*)(I8 *, U32))(void *)hasher)(self->c_str, self->count);
    (void)hoisted__U64_1115;
    return hoisted__U64_1115;
}

U32 Str_size(void) {
    U32 hoisted__U32_1236 = 16;
    (void)hoisted__U32_1236;
    return hoisted__U32_1236;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1237 = Str_cmp(a, b);
    (void)hoisted__I64_1237;
    I64 hoisted__I64_1238 = 0;
    (void)hoisted__I64_1238;
    Bool hoisted__Bool_1239 = I64_eq(hoisted__I64_1237, hoisted__I64_1238);
    (void)hoisted__Bool_1239;
    return hoisted__Bool_1239;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1310 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1310->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1310;
    return hoisted__OutOfBounds_1310;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1311 = 0;
    (void)hoisted__Bool_1311;
    Str_delete(&self->msg, hoisted__Bool_1311);
    if (call_free) {
        free(self);
    }
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1312 = 16;
    (void)hoisted__U32_1312;
    return hoisted__U32_1312;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1318 = 8;
    (void)hoisted__U32_1318;
    return hoisted__U32_1318;
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1526 = 0;
    (void)hoisted__I64_1526;
    Bool hoisted__Bool_1527 = I64_eq(val, hoisted__I64_1526);
    (void)hoisted__Bool_1527;
    if (hoisted__Bool_1527) {
        U64 hoisted__U64_1490 = 2ULL;
        (void)hoisted__U64_1490;
        void * buf = malloc(hoisted__U64_1490);
        I64 hoisted__I64_1491 = 48;
        (void)hoisted__I64_1491;
        U64 hoisted__U64_1492 = 1ULL;
        (void)hoisted__U64_1492;
        memcpy(buf, &hoisted__I64_1491, hoisted__U64_1492);
        U64 hoisted__U64_1493 = 1ULL;
        (void)hoisted__U64_1493;
        void *hoisted__v_1494 = ptr_add(buf, hoisted__U64_1493);
        (void)hoisted__v_1494;
        (void)hoisted__v_1494;
        I32 hoisted__I32_1495 = 0;
        (void)hoisted__I32_1495;
        U64 hoisted__U64_1496 = 1ULL;
        (void)hoisted__U64_1496;
        memset(hoisted__v_1494, hoisted__I32_1495, hoisted__U64_1496);
        I32_delete(&hoisted__I32_1495, 0);
        I64 hoisted__I64_1497 = 1;
        (void)hoisted__I64_1497;
        I64 hoisted__I64_1498 = 1;
        (void)hoisted__I64_1498;
        Str *hoisted__Str_1499 = malloc(sizeof(Str));
        hoisted__Str_1499->c_str = buf;
        hoisted__Str_1499->count = hoisted__I64_1497;
        hoisted__Str_1499->cap = hoisted__I64_1498;
        (void)hoisted__Str_1499;
        { Str * _ret_val = hoisted__Str_1499;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1528 = 0;
    (void)hoisted__I64_1528;
    Bool hoisted__Bool_1529 = I64_lt(val, hoisted__I64_1528);
    (void)hoisted__Bool_1529;
    if (hoisted__Bool_1529) {
        Bool hoisted__Bool_1500 = 1;
        (void)hoisted__Bool_1500;
        is_neg = hoisted__Bool_1500;
        I64 hoisted__I64_1501 = 0;
        (void)hoisted__I64_1501;
        I64 hoisted__I64_1502 = I64_sub(hoisted__I64_1501, val);
        (void)hoisted__I64_1502;
        v = hoisted__I64_1502;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1504 = 0;
        (void)hoisted__I64_1504;
        Bool _wcond_Bool_1503 = I64_gt(tmp, hoisted__I64_1504);
        (void)_wcond_Bool_1503;
        if (_wcond_Bool_1503) {
        } else {
            break;
        }
        U64 hoisted__U64_1505 = 1ULL;
        (void)hoisted__U64_1505;
        U64 hoisted__U64_1506 = U64_add(ndigits, hoisted__U64_1505);
        (void)hoisted__U64_1506;
        ndigits = hoisted__U64_1506;
        I64 hoisted__I64_1507 = 10;
        (void)hoisted__I64_1507;
        I64 hoisted__I64_1508 = I64_div(tmp, hoisted__I64_1507);
        (void)hoisted__I64_1508;
        tmp = hoisted__I64_1508;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1509 = 1ULL;
        (void)hoisted__U64_1509;
        U64 hoisted__U64_1510 = U64_add(total, hoisted__U64_1509);
        (void)hoisted__U64_1510;
        total = hoisted__U64_1510;
    }
    U64 hoisted__U64_1530 = 1ULL;
    (void)hoisted__U64_1530;
    U64 hoisted__U64_1531 = U64_add(total, hoisted__U64_1530);
    (void)hoisted__U64_1531;
    void * buf = malloc(hoisted__U64_1531);
    if (is_neg) {
        I64 hoisted__I64_1511 = 45;
        (void)hoisted__I64_1511;
        U64 hoisted__U64_1512 = 1ULL;
        (void)hoisted__U64_1512;
        memcpy(buf, &hoisted__I64_1511, hoisted__U64_1512);
    }
    U64 hoisted__U64_1532 = 1ULL;
    (void)hoisted__U64_1532;
    U64 i = U64_sub(total, hoisted__U64_1532);
    while (1) {
        I64 hoisted__I64_1514 = 0;
        (void)hoisted__I64_1514;
        Bool _wcond_Bool_1513 = I64_gt(v, hoisted__I64_1514);
        (void)_wcond_Bool_1513;
        if (_wcond_Bool_1513) {
        } else {
            break;
        }
        I64 hoisted__I64_1515 = 10;
        (void)hoisted__I64_1515;
        I64 hoisted__I64_1516 = I64_mod(v, hoisted__I64_1515);
        (void)hoisted__I64_1516;
        I64 hoisted__I64_1517 = 48;
        (void)hoisted__I64_1517;
        I64 hoisted__I64_1518 = I64_add(hoisted__I64_1516, hoisted__I64_1517);
        (void)hoisted__I64_1518;
        void *hoisted__v_1519 = ptr_add(buf, i);
        (void)hoisted__v_1519;
        (void)hoisted__v_1519;
        U8 hoisted__U8_1520 = I64_to_u8(hoisted__I64_1518);
        (void)hoisted__U8_1520;
        U64 hoisted__U64_1521 = 1ULL;
        (void)hoisted__U64_1521;
        memcpy(hoisted__v_1519, &hoisted__U8_1520, hoisted__U64_1521);
        U8_delete(&hoisted__U8_1520, 0);
        I64 hoisted__I64_1522 = 10;
        (void)hoisted__I64_1522;
        I64 hoisted__I64_1523 = I64_div(v, hoisted__I64_1522);
        (void)hoisted__I64_1523;
        v = hoisted__I64_1523;
        U64 hoisted__U64_1524 = 1ULL;
        (void)hoisted__U64_1524;
        U64 hoisted__U64_1525 = U64_sub(i, hoisted__U64_1524);
        (void)hoisted__U64_1525;
        i = hoisted__U64_1525;
    }
    void *hoisted__v_1533 = ptr_add(buf, total);
    (void)hoisted__v_1533;
    (void)hoisted__v_1533;
    I32 hoisted__I32_1534 = 0;
    (void)hoisted__I32_1534;
    U64 hoisted__U64_1535 = 1ULL;
    (void)hoisted__U64_1535;
    memset(hoisted__v_1533, hoisted__I32_1534, hoisted__U64_1535);
    I32_delete(&hoisted__I32_1534, 0);
    Str *hoisted__Str_1536 = malloc(sizeof(Str));
    hoisted__Str_1536->c_str = buf;
    hoisted__Str_1536->count = total;
    hoisted__Str_1536->cap = total;
    (void)hoisted__Str_1536;
    return hoisted__Str_1536;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1550 = 8;
    (void)hoisted__U32_1550;
    U64 hoisted__U64_1551 = ((U64 (*)(I64 *, U32))(void *)hasher)(&self, hoisted__U32_1550);
    (void)hoisted__U64_1551;
    return hoisted__U64_1551;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1557 = 8;
    (void)hoisted__U32_1557;
    return hoisted__U32_1557;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1690 = I64_cmp(a, b);
    (void)hoisted__I64_1690;
    I64 hoisted__I64_1691 = -1;
    (void)hoisted__I64_1691;
    Bool hoisted__Bool_1692 = I64_eq(hoisted__I64_1690, hoisted__I64_1691);
    (void)hoisted__Bool_1692;
    return hoisted__Bool_1692;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1693 = I64_cmp(a, b);
    (void)hoisted__I64_1693;
    I64 hoisted__I64_1694 = 1;
    (void)hoisted__I64_1694;
    Bool hoisted__Bool_1695 = I64_eq(hoisted__I64_1693, hoisted__I64_1694);
    (void)hoisted__Bool_1695;
    return hoisted__Bool_1695;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1696 = I64_eq(a, b);
    (void)hoisted__Bool_1696;
    Bool hoisted__Bool_1697 = not(hoisted__Bool_1696);
    (void)hoisted__Bool_1697;
    return hoisted__Bool_1697;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1711 = Bool_eq(a, b);
    (void)hoisted__Bool_1711;
    if (hoisted__Bool_1711) {
        I64 hoisted__I64_1709 = 0;
        (void)hoisted__I64_1709;
        { I64 _ret_val = hoisted__I64_1709;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1710 = -1;
        (void)hoisted__I64_1710;
        return hoisted__I64_1710;
    }
    I64 hoisted__I64_1712 = 1;
    (void)hoisted__I64_1712;
    return hoisted__I64_1712;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1714 = 1;
    (void)hoisted__U32_1714;
    U64 hoisted__U64_1715 = ((U64 (*)(Bool *, U32))(void *)hasher)(&self, hoisted__U32_1714);
    (void)hoisted__U64_1715;
    return hoisted__U64_1715;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1716 = 1;
    (void)hoisted__U32_1716;
    return hoisted__U32_1716;
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
    Bool hoisted__Bool_1860 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1860;
    if (hoisted__Bool_1860) {
        Bool hoisted__Bool_1858 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1858;
        { Bool _ret_val = hoisted__Bool_1858;
                return _ret_val; }
    }
    Bool hoisted__Bool_1861 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1861;
    if (hoisted__Bool_1861) {
        Bool hoisted__Bool_1859 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1859;
        { Bool _ret_val = hoisted__Bool_1859;
                return _ret_val; }
    }
    Bool hoisted__Bool_1862 = 0;
    (void)hoisted__Bool_1862;
    return hoisted__Bool_1862;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1868 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1868;
    if (hoisted__Bool_1868) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1869 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1869;
    if (hoisted__Bool_1869) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Str hoisted__Str_1870 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1870;
    UNREACHABLE(&hoisted__Str_1870);
    Str_delete(&hoisted__Str_1870, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1871 = 4;
    (void)hoisted__U32_1871;
    return hoisted__U32_1871;
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
    Bool hoisted__Bool_1934 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1934;
    if (hoisted__Bool_1934) {
        Str *hoisted__Str_1926 = get_payload(self);
        (void)hoisted__Str_1926;
        (void)hoisted__Str_1926;
        Bool hoisted__Bool_1927 = 0;
        (void)hoisted__Bool_1927;
        Str_delete(hoisted__Str_1926, hoisted__Bool_1927);
    }
    Bool hoisted__Bool_1935 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1935;
    if (hoisted__Bool_1935) {
        Str *hoisted__Str_1928 = get_payload(self);
        (void)hoisted__Str_1928;
        (void)hoisted__Str_1928;
        Bool hoisted__Bool_1929 = 0;
        (void)hoisted__Bool_1929;
        Str_delete(hoisted__Str_1928, hoisted__Bool_1929);
    }
    Bool hoisted__Bool_1936 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1936;
    if (hoisted__Bool_1936) {
        Str *hoisted__Str_1930 = get_payload(self);
        (void)hoisted__Str_1930;
        (void)hoisted__Str_1930;
        Bool hoisted__Bool_1931 = 0;
        (void)hoisted__Bool_1931;
        Str_delete(hoisted__Str_1930, hoisted__Bool_1931);
    }
    Bool hoisted__Bool_1937 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1937;
    if (hoisted__Bool_1937) {
        Primitive *hoisted__Primitive_1932 = get_payload(self);
        (void)hoisted__Primitive_1932;
        (void)hoisted__Primitive_1932;
        Bool hoisted__Bool_1933 = 0;
        (void)hoisted__Bool_1933;
        Primitive_delete(hoisted__Primitive_1932, hoisted__Bool_1933);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2019 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2019;
    if (hoisted__Bool_2019) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2020 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2020;
    if (hoisted__Bool_2020) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2021 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)hoisted__Bool_2021;
    if (hoisted__Bool_2021) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2022 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)hoisted__Bool_2022;
    if (hoisted__Bool_2022) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2023 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)hoisted__Bool_2023;
    if (hoisted__Bool_2023) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2024 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)hoisted__Bool_2024;
    if (hoisted__Bool_2024) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2025 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)hoisted__Bool_2025;
    if (hoisted__Bool_2025) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2026 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)hoisted__Bool_2026;
    if (hoisted__Bool_2026) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2027 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)hoisted__Bool_2027;
    if (hoisted__Bool_2027) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool;
                return _r; }
    }
    Bool hoisted__Bool_2028 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2028;
    if (hoisted__Bool_2028) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_2013 = Str_clone(_clone_payload_Struct_9);
        (void)hoisted__Str_2013;
        Type *hoisted__Type_2014 = Type_Struct(hoisted__Str_2013);
        (void)hoisted__Type_2014;
        { Type * _ret_val = hoisted__Type_2014;
                return _ret_val; }
    }
    Bool hoisted__Bool_2029 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2029;
    if (hoisted__Bool_2029) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2030 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2030;
    if (hoisted__Bool_2030) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_2015 = Str_clone(_clone_payload_Enum_11);
        (void)hoisted__Str_2015;
        Type *hoisted__Type_2016 = Type_Enum(hoisted__Str_2015);
        (void)hoisted__Type_2016;
        { Type * _ret_val = hoisted__Type_2016;
                return _ret_val; }
    }
    Bool hoisted__Bool_2031 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2031;
    if (hoisted__Bool_2031) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2032 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2032;
    if (hoisted__Bool_2032) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2033 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2033;
    if (hoisted__Bool_2033) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2034 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2034;
    if (hoisted__Bool_2034) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2035 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2035;
    if (hoisted__Bool_2035) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_2017 = Str_clone(_clone_payload_Custom_16);
        (void)hoisted__Str_2017;
        Type *hoisted__Type_2018 = Type_Custom(hoisted__Str_2017);
        (void)hoisted__Type_2018;
        { Type * _ret_val = hoisted__Type_2018;
                return _ret_val; }
    }
    Bool hoisted__Bool_2036 = is(self, &(Type){.tag = Type_TAG_I8});
    (void)hoisted__Bool_2036;
    if (hoisted__Bool_2036) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8;
                return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive hoisted__Primitive_2037 = DEREF(_clone_payload_Primitive_18);
    (void)hoisted__Primitive_2037;
    Type *hoisted__Type_2038 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2037; _oa; }));
    (void)hoisted__Type_2038;
    return hoisted__Type_2038;
}

U32 Type_size(void) {
    U32 hoisted__U32_2039 = 24;
    (void)hoisted__U32_2039;
    return hoisted__U32_2039;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3699 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3699;
    if (hoisted__Bool_3699) {
        Type *hoisted__Type_3694 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3694;
        U32 hoisted__U32_3695 = 1;
        (void)hoisted__U32_3695;
        Array *_va_Array_113 = Array_new(hoisted__Type_3694, hoisted__U32_3695);
        (void)_va_Array_113;
        Type_delete(hoisted__Type_3694, 1);
        U32 hoisted__U32_3696 = 0;
        (void)hoisted__U32_3696;
        Str hoisted__Str_3697 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3697;
        Array_set(_va_Array_113, hoisted__U32_3696, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3697; _oa; }));
        Str hoisted__Str_3698 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3698;
        panic(&hoisted__Str_3698, _va_Array_113);
        Str_delete(&hoisted__Str_3698, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3700 = calloc(cap, elem_size);
    (void)hoisted__v_3700;
    void * hoisted__v_3701 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3701;
    void * hoisted__v_3702 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3702;
    Array *hoisted__Array_3703 = malloc(sizeof(Array));
    hoisted__Array_3703->data = hoisted__v_3700;
    hoisted__Array_3703->cap = cap;
    hoisted__Array_3703->elem_size = elem_size;
    hoisted__Array_3703->elem_clone = hoisted__v_3701;
    hoisted__Array_3703->elem_delete = hoisted__v_3702;
    (void)hoisted__Array_3703;
    return hoisted__Array_3703;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3704 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3704;
    Str_delete(elem_type, 1);
    return hoisted__Array_3704;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3725 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3725;
    if (hoisted__Bool_3725) {
        Type *hoisted__Type_3706 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3706;
        U32 hoisted__U32_3707 = 6;
        (void)hoisted__U32_3707;
        Array *_va_Array_114 = Array_new(hoisted__Type_3706, hoisted__U32_3707);
        (void)_va_Array_114;
        Type_delete(hoisted__Type_3706, 1);
        U32 hoisted__U32_3708 = 0;
        (void)hoisted__U32_3708;
        Str hoisted__Str_3709 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3709;
        Array_set(_va_Array_114, hoisted__U32_3708, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3709; _oa; }));
        U32 hoisted__U32_3710 = 1;
        (void)hoisted__U32_3710;
        Str hoisted__Str_3711 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3711;
        Array_set(_va_Array_114, hoisted__U32_3710, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3711; _oa; }));
        U32 hoisted__U32_3712 = 2;
        (void)hoisted__U32_3712;
        Str *hoisted__Str_3713 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3713;
        Array_set(_va_Array_114, hoisted__U32_3712, hoisted__Str_3713);
        U32 hoisted__U32_3714 = 3;
        (void)hoisted__U32_3714;
        Str hoisted__Str_3715 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3715;
        Array_set(_va_Array_114, hoisted__U32_3714, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3715; _oa; }));
        U32 hoisted__U32_3716 = 4;
        (void)hoisted__U32_3716;
        Str *hoisted__Str_3717 = U32_to_str(self->cap);
        (void)hoisted__Str_3717;
        Array_set(_va_Array_114, hoisted__U32_3716, hoisted__Str_3717);
        U32 hoisted__U32_3718 = 5;
        (void)hoisted__U32_3718;
        Str hoisted__Str_3719 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3719;
        Array_set(_va_Array_114, hoisted__U32_3718, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3719; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3720 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_114); hoisted__OutOfBounds_3720->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3720;
        U32 hoisted__U32_3721 = 16;
        (void)hoisted__U32_3721;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3720, hoisted__U32_3721);
        OutOfBounds_delete(hoisted__OutOfBounds_3720, 1);
        I64 hoisted__I64_3722 = 3;
        (void)hoisted__I64_3722;
        *_err_kind = hoisted__I64_3722;
    }
    I64 hoisted__I64_3726 = 0;
    (void)hoisted__I64_3726;
    Bool hoisted__Bool_3727 = I64_eq(DEREF(_err_kind), hoisted__I64_3726);
    (void)hoisted__Bool_3727;
    if (hoisted__Bool_3727) {
        U32 hoisted__U64_3723 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3723;
        void *hoisted__v_3724 = ptr_add(self->data, hoisted__U64_3723);
        (void)hoisted__v_3724;
        (void)hoisted__v_3724;
        { void * _ret_val = hoisted__v_3724;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3742 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3742;
    if (hoisted__Bool_3742) {
        Type *hoisted__Type_3729 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3729;
        U32 hoisted__U32_3730 = 5;
        (void)hoisted__U32_3730;
        Array *_va_Array_115 = Array_new(hoisted__Type_3729, hoisted__U32_3730);
        (void)_va_Array_115;
        Type_delete(hoisted__Type_3729, 1);
        U32 hoisted__U32_3731 = 0;
        (void)hoisted__U32_3731;
        Str hoisted__Str_3732 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3732;
        Array_set(_va_Array_115, hoisted__U32_3731, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3732; _oa; }));
        U32 hoisted__U32_3733 = 1;
        (void)hoisted__U32_3733;
        Str *hoisted__Str_3734 = U32_to_str(i);
        (void)hoisted__Str_3734;
        Array_set(_va_Array_115, hoisted__U32_3733, hoisted__Str_3734);
        U32 hoisted__U32_3735 = 2;
        (void)hoisted__U32_3735;
        Str hoisted__Str_3736 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3736;
        Array_set(_va_Array_115, hoisted__U32_3735, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3736; _oa; }));
        U32 hoisted__U32_3737 = 3;
        (void)hoisted__U32_3737;
        Str *hoisted__Str_3738 = U32_to_str(self->cap);
        (void)hoisted__Str_3738;
        Array_set(_va_Array_115, hoisted__U32_3737, hoisted__Str_3738);
        U32 hoisted__U32_3739 = 4;
        (void)hoisted__U32_3739;
        Str hoisted__Str_3740 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3740;
        Array_set(_va_Array_115, hoisted__U32_3739, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3740; _oa; }));
        Str hoisted__Str_3741 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3741;
        panic(&hoisted__Str_3741, _va_Array_115);
        Str_delete(&hoisted__Str_3741, (Bool){0});
    }
    U32 hoisted__U64_3743 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3743;
    void *hoisted__v_3744 = ptr_add(self->data, hoisted__U64_3743);
    (void)hoisted__v_3744;
    (void)hoisted__v_3744;
    Bool hoisted__Bool_3745 = 0;
    (void)hoisted__Bool_3745;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3744, hoisted__Bool_3745);
    U32 hoisted__U64_3746 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3746;
    void *hoisted__v_3747 = ptr_add(self->data, hoisted__U64_3746);
    (void)hoisted__v_3747;
    (void)hoisted__v_3747;
    memcpy(hoisted__v_3747, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3748 = self->cap;
        (void)_re_U32_3748;
        U32 _rc_U32_3748 = 0;
        (void)_rc_U32_3748;
        Bool hoisted__Bool_3757 = U32_lte(_rc_U32_3748, _re_U32_3748);
        (void)hoisted__Bool_3757;
        if (hoisted__Bool_3757) {
            while (1) {
                Bool _wcond_Bool_3749 = U32_lt(_rc_U32_3748, _re_U32_3748);
                (void)_wcond_Bool_3749;
                if (_wcond_Bool_3749) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3748);
                U32_inc(&_rc_U32_3748);
                U32 hoisted__U64_3750 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3750;
                void *hoisted__v_3751 = ptr_add(self->data, hoisted__U64_3750);
                (void)hoisted__v_3751;
                (void)hoisted__v_3751;
                Bool hoisted__Bool_3752 = 0;
                (void)hoisted__Bool_3752;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3751, hoisted__Bool_3752);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3753 = U32_gt(_rc_U32_3748, _re_U32_3748);
                (void)_wcond_Bool_3753;
                if (_wcond_Bool_3753) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3748);
                U32_dec(&_rc_U32_3748);
                U32 hoisted__U64_3754 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3754;
                void *hoisted__v_3755 = ptr_add(self->data, hoisted__U64_3754);
                (void)hoisted__v_3755;
                (void)hoisted__v_3755;
                Bool hoisted__Bool_3756 = 0;
                (void)hoisted__Bool_3756;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3755, hoisted__Bool_3756);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3770 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3770;
    void * new_data = malloc(hoisted__U64_3770);
    {
        U32 _re_U32_3758 = self->cap;
        (void)_re_U32_3758;
        U32 _rc_U32_3758 = 0;
        (void)_rc_U32_3758;
        Bool hoisted__Bool_3769 = U32_lte(_rc_U32_3758, _re_U32_3758);
        (void)hoisted__Bool_3769;
        if (hoisted__Bool_3769) {
            while (1) {
                Bool _wcond_Bool_3759 = U32_lt(_rc_U32_3758, _re_U32_3758);
                (void)_wcond_Bool_3759;
                if (_wcond_Bool_3759) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3758);
                U32_inc(&_rc_U32_3758);
                U32 hoisted__U64_3760 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3760;
                void *hoisted__v_3761 = ptr_add(self->data, hoisted__U64_3760);
                (void)hoisted__v_3761;
                (void)hoisted__v_3761;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3761);
                U32 hoisted__U64_3762 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3762;
                void *hoisted__v_3763 = ptr_add(new_data, hoisted__U64_3762);
                (void)hoisted__v_3763;
                (void)hoisted__v_3763;
                memcpy(hoisted__v_3763, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3764 = U32_gt(_rc_U32_3758, _re_U32_3758);
                (void)_wcond_Bool_3764;
                if (_wcond_Bool_3764) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3758);
                U32_dec(&_rc_U32_3758);
                U32 hoisted__U64_3765 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3765;
                void *hoisted__v_3766 = ptr_add(self->data, hoisted__U64_3765);
                (void)hoisted__v_3766;
                (void)hoisted__v_3766;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3766);
                U32 hoisted__U64_3767 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3767;
                void *hoisted__v_3768 = ptr_add(new_data, hoisted__U64_3767);
                (void)hoisted__v_3768;
                (void)hoisted__v_3768;
                memcpy(hoisted__v_3768, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3771 = malloc(sizeof(Array));
    hoisted__Array_3771->data = new_data;
    hoisted__Array_3771->cap = self->cap;
    hoisted__Array_3771->elem_size = self->elem_size;
    hoisted__Array_3771->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3771->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3771;
    return hoisted__Array_3771;
}

U32 Array_size(void) {
    U32 hoisted__U32_3772 = 32;
    (void)hoisted__U32_3772;
    return hoisted__U32_3772;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4143 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4143;
    U32 hoisted__U32_4144 = 3;
    (void)hoisted__U32_4144;
    Array *_va_Array_147 = Array_new(hoisted__Type_4143, hoisted__U32_4144);
    (void)_va_Array_147;
    Type_delete(hoisted__Type_4143, 1);
    U32 hoisted__U32_4145 = 0;
    (void)hoisted__U32_4145;
    Str *hoisted__Str_4146 = Str_clone(loc_str);
    (void)hoisted__Str_4146;
    Array_set(_va_Array_147, hoisted__U32_4145, hoisted__Str_4146);
    U32 hoisted__U32_4147 = 1;
    (void)hoisted__U32_4147;
    Str hoisted__Str_4148 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4148;
    Array_set(_va_Array_147, hoisted__U32_4147, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4148; _oa; }));
    Array *hoisted__Array_4149 = Array_clone(parts);
    (void)hoisted__Array_4149;
    Array_delete(parts, 1);
    U32 hoisted__U32_4150 = 2;
    (void)hoisted__U32_4150;
    Str *hoisted__Str_4151 = format(hoisted__Array_4149);
    (void)hoisted__Str_4151;
    Array_set(_va_Array_147, hoisted__U32_4150, hoisted__Str_4151);
    println(_va_Array_147);
    I64 hoisted__I64_4152 = 1;
    (void)hoisted__I64_4152;
    exit(hoisted__I64_4152);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4162 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4162;
    U32 hoisted__U32_4163 = 1;
    (void)hoisted__U32_4163;
    Array *_va_Array_149 = Array_new(hoisted__Type_4162, hoisted__U32_4163);
    (void)_va_Array_149;
    Type_delete(hoisted__Type_4162, 1);
    U32 hoisted__U32_4164 = 0;
    (void)hoisted__U32_4164;
    Str hoisted__Str_4165 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4165;
    Array_set(_va_Array_149, hoisted__U32_4164, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4165; _oa; }));
    panic(loc_str, _va_Array_149);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4171 = not(cond);
    (void)hoisted__Bool_4171;
    if (hoisted__Bool_4171) {
        Type *hoisted__Type_4167 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4167;
        U32 hoisted__U32_4168 = 1;
        (void)hoisted__U32_4168;
        Array *_va_Array_150 = Array_new(hoisted__Type_4167, hoisted__U32_4168);
        (void)_va_Array_150;
        Type_delete(hoisted__Type_4167, 1);
        U32 hoisted__U32_4169 = 0;
        (void)hoisted__U32_4169;
        Str hoisted__Str_4170 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4170;
        Array_set(_va_Array_150, hoisted__U32_4169, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4170; _oa; }));
        panic(loc_str, _va_Array_150);
    }
    Bool hoisted__Bool_4172 = 1;
    (void)hoisted__Bool_4172;
    return hoisted__Bool_4172;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4195 = I64_neq(a, b);
    (void)hoisted__Bool_4195;
    if (hoisted__Bool_4195) {
        Type *hoisted__Type_4183 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4183;
        U32 hoisted__U32_4184 = 5;
        (void)hoisted__U32_4184;
        Array *_va_Array_152 = Array_new(hoisted__Type_4183, hoisted__U32_4184);
        (void)_va_Array_152;
        Type_delete(hoisted__Type_4183, 1);
        U32 hoisted__U32_4185 = 0;
        (void)hoisted__U32_4185;
        Str hoisted__Str_4186 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4186;
        Array_set(_va_Array_152, hoisted__U32_4185, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4186; _oa; }));
        U32 hoisted__U32_4187 = 1;
        (void)hoisted__U32_4187;
        Str *hoisted__Str_4188 = I64_to_str(a);
        (void)hoisted__Str_4188;
        Array_set(_va_Array_152, hoisted__U32_4187, hoisted__Str_4188);
        U32 hoisted__U32_4189 = 2;
        (void)hoisted__U32_4189;
        Str hoisted__Str_4190 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4190;
        Array_set(_va_Array_152, hoisted__U32_4189, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4190; _oa; }));
        U32 hoisted__U32_4191 = 3;
        (void)hoisted__U32_4191;
        Str *hoisted__Str_4192 = I64_to_str(b);
        (void)hoisted__Str_4192;
        Array_set(_va_Array_152, hoisted__U32_4191, hoisted__Str_4192);
        U32 hoisted__U32_4193 = 4;
        (void)hoisted__U32_4193;
        Str hoisted__Str_4194 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4194;
        Array_set(_va_Array_152, hoisted__U32_4193, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4194; _oa; }));
        panic(loc_str, _va_Array_152);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4209 = Str_eq(a, b);
    (void)hoisted__Bool_4209;
    Bool hoisted__Bool_4210 = not(hoisted__Bool_4209);
    (void)hoisted__Bool_4210;
    if (hoisted__Bool_4210) {
        Type *hoisted__Type_4197 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4197;
        U32 hoisted__U32_4198 = 5;
        (void)hoisted__U32_4198;
        Array *_va_Array_153 = Array_new(hoisted__Type_4197, hoisted__U32_4198);
        (void)_va_Array_153;
        Type_delete(hoisted__Type_4197, 1);
        U32 hoisted__U32_4199 = 0;
        (void)hoisted__U32_4199;
        Str hoisted__Str_4200 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4200;
        Array_set(_va_Array_153, hoisted__U32_4199, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4200; _oa; }));
        U32 hoisted__U32_4201 = 1;
        (void)hoisted__U32_4201;
        Str *hoisted__Str_4202 = Str_clone(a);
        (void)hoisted__Str_4202;
        Array_set(_va_Array_153, hoisted__U32_4201, hoisted__Str_4202);
        U32 hoisted__U32_4203 = 2;
        (void)hoisted__U32_4203;
        Str hoisted__Str_4204 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4204;
        Array_set(_va_Array_153, hoisted__U32_4203, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4204; _oa; }));
        U32 hoisted__U32_4205 = 3;
        (void)hoisted__U32_4205;
        Str *hoisted__Str_4206 = Str_clone(b);
        (void)hoisted__Str_4206;
        Array_set(_va_Array_153, hoisted__U32_4205, hoisted__Str_4206);
        U32 hoisted__U32_4207 = 4;
        (void)hoisted__U32_4207;
        Str hoisted__Str_4208 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4208;
        Array_set(_va_Array_153, hoisted__U32_4207, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4208; _oa; }));
        panic(loc_str, _va_Array_153);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4211 = parts;
        (void)_fc_Array_4211;
        (void)_fc_Array_4211;
        U32 _fi_USize_4211 = 0;
        (void)_fi_USize_4211;
        I64 _forin_err_kind_4211 = 0;
        (void)_forin_err_kind_4211;
        OutOfBounds *_forin_OutOfBounds_4211 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4211->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4211;
        while (1) {
            U32 hoisted__U32_4219 = Array_len(_fc_Array_4211);
            (void)hoisted__U32_4219;
            Bool _wcond_Bool_4212 = U32_lt(_fi_USize_4211, hoisted__U32_4219);
            (void)_wcond_Bool_4212;
            if (_wcond_Bool_4212) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4211, &_fi_USize_4211, &_forin_err_kind_4211, _forin_OutOfBounds_4211);
            I64 hoisted__I64_4220 = 0;
            (void)hoisted__I64_4220;
            Bool hoisted__Bool_4221 = I64_eq(_forin_err_kind_4211, hoisted__I64_4220);
            (void)hoisted__Bool_4221;
            Bool hoisted__Bool_4222 = not(hoisted__Bool_4221);
            (void)hoisted__Bool_4222;
            if (hoisted__Bool_4222) {
                Type *hoisted__Type_4214 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4214;
                U32 hoisted__U32_4215 = 1;
                (void)hoisted__U32_4215;
                Array *_va_Array_154 = Array_new(hoisted__Type_4214, hoisted__U32_4215);
                (void)_va_Array_154;
                Type_delete(hoisted__Type_4214, 1);
                U32 hoisted__U32_4216 = 0;
                (void)hoisted__U32_4216;
                Str hoisted__Str_4217 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4217;
                Array_set(_va_Array_154, hoisted__U32_4216, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4217; _oa; }));
                Str hoisted__Str_4218 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4218;
                panic(&hoisted__Str_4218, _va_Array_154);
                Str_delete(&hoisted__Str_4218, (Bool){0});
            }
            U32 hoisted__U32_4223 = 1;
            (void)hoisted__U32_4223;
            U32 hoisted__U32_4224 = U32_add(_fi_USize_4211, hoisted__U32_4223);
            (void)hoisted__U32_4224;
            _fi_USize_4211 = hoisted__U32_4224;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4211, 1);
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
    Str hoisted__Str_4478 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4478;
    I64 hoisted__I64_4479 = 3;
    (void)hoisted__I64_4479;
    assert_eq(&hoisted__Str_4478, result, hoisted__I64_4479);
    Str_delete(&hoisted__Str_4478, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4486 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4486;
    I64 hoisted__I64_4487 = 15;
    (void)hoisted__I64_4487;
    assert_eq(&hoisted__Str_4486, result, hoisted__I64_4487);
    Str_delete(&hoisted__Str_4486, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4494 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4494;
    I64 hoisted__I64_4495 = 26;
    (void)hoisted__I64_4495;
    assert_eq(&hoisted__Str_4494, result, hoisted__I64_4495);
    Str_delete(&hoisted__Str_4494, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4498 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4498;
    Str hoisted__Str_4499 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4499;
    assert_eq_str(&hoisted__Str_4498, &result, &hoisted__Str_4499);
    Str_delete(&hoisted__Str_4498, (Bool){0});
    Str_delete(&hoisted__Str_4499, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4830 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4830;
    assert_eq_str(&hoisted__Str_4830, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4830, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4831 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4831;
    assert_eq_str(&hoisted__Str_4831, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4831, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4833 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4833;
    I64 hoisted__I64_4834 = 8;
    (void)hoisted__I64_4834;
    assert_eq(&hoisted__Str_4833, result, hoisted__I64_4834);
    Str_delete(&hoisted__Str_4833, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4837 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4837;
    Bool hoisted__Bool_4838 = 1;
    (void)hoisted__Bool_4838;
    assert(&hoisted__Str_4837, hoisted__Bool_4838);
    Str_delete(&hoisted__Str_4837, (Bool){0});
    Str hoisted__Str_4841 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4841;
    Bool hoisted__Bool_4842 = 1;
    (void)hoisted__Bool_4842;
    assert(&hoisted__Str_4841, hoisted__Bool_4842);
    Str_delete(&hoisted__Str_4841, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4847 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4847;
    Str hoisted__Str_4848 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4848;
    Str hoisted__Str_4849 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4849;
    assert_eq_str(&hoisted__Str_4847, &hoisted__Str_4848, &hoisted__Str_4849);
    Str_delete(&hoisted__Str_4847, (Bool){0});
    Str_delete(&hoisted__Str_4848, (Bool){0});
    Str_delete(&hoisted__Str_4849, (Bool){0});
    Str hoisted__Str_4852 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4852;
    Str hoisted__Str_4853 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4853;
    Str hoisted__Str_4854 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4854;
    assert_eq_str(&hoisted__Str_4852, &hoisted__Str_4853, &hoisted__Str_4854);
    Str_delete(&hoisted__Str_4852, (Bool){0});
    Str_delete(&hoisted__Str_4853, (Bool){0});
    Str_delete(&hoisted__Str_4854, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4859 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4859;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4859;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4860 = 16;
    (void)hoisted__U32_4860;
    return hoisted__U32_4860;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4861 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4861;
    I64 hoisted__I64_4862 = 42;
    (void)hoisted__I64_4862;
    assert_eq(&hoisted__Str_4861, v.x, hoisted__I64_4862);
    Str_delete(&hoisted__Str_4861, (Bool){0});
    Str hoisted__Str_4863 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4863;
    I64 hoisted__I64_4864 = 99;
    (void)hoisted__I64_4864;
    assert_eq(&hoisted__Str_4863, v.y, hoisted__I64_4864);
    Str_delete(&hoisted__Str_4863, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4867 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4867;
    I64 hoisted__I64_4868 = 10;
    (void)hoisted__I64_4868;
    assert_eq(&hoisted__Str_4867, p.x, hoisted__I64_4868);
    Str_delete(&hoisted__Str_4867, (Bool){0});
    Str hoisted__Str_4869 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4869;
    I64 hoisted__I64_4870 = 20;
    (void)hoisted__I64_4870;
    assert_eq(&hoisted__Str_4869, p.y, hoisted__I64_4870);
    Str_delete(&hoisted__Str_4869, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4876 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4876;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4876;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4877 = 32;
    (void)hoisted__U32_4877;
    return hoisted__U32_4877;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4878 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4878;
    I64 hoisted__I64_4879 = 5;
    (void)hoisted__I64_4879;
    assert_eq(&hoisted__Str_4878, r.top_left.x, hoisted__I64_4879);
    Str_delete(&hoisted__Str_4878, (Bool){0});
    Str hoisted__Str_4880 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4880;
    I64 hoisted__I64_4881 = 10;
    (void)hoisted__I64_4881;
    assert_eq(&hoisted__Str_4880, r.top_left.y, hoisted__I64_4881);
    Str_delete(&hoisted__Str_4880, (Bool){0});
    Str hoisted__Str_4882 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4882;
    I64 hoisted__I64_4883 = 100;
    (void)hoisted__I64_4883;
    assert_eq(&hoisted__Str_4882, r.bottom_right.x, hoisted__I64_4883);
    Str_delete(&hoisted__Str_4882, (Bool){0});
    Str hoisted__Str_4884 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4884;
    I64 hoisted__I64_4885 = 200;
    (void)hoisted__I64_4885;
    assert_eq(&hoisted__Str_4884, r.bottom_right.y, hoisted__I64_4885);
    Str_delete(&hoisted__Str_4884, (Bool){0});
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
    Bool hoisted__Bool_4890 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4890;
    if (hoisted__Bool_4890) {
        Bool hoisted__Bool_4887 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4887;
        { Bool _ret_val = hoisted__Bool_4887;
                return _ret_val; }
    }
    Bool hoisted__Bool_4891 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4891;
    if (hoisted__Bool_4891) {
        Bool hoisted__Bool_4888 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4888;
        { Bool _ret_val = hoisted__Bool_4888;
                return _ret_val; }
    }
    Bool hoisted__Bool_4892 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4892;
    if (hoisted__Bool_4892) {
        Bool hoisted__Bool_4889 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4889;
        { Bool _ret_val = hoisted__Bool_4889;
                return _ret_val; }
    }
    Bool hoisted__Bool_4893 = 0;
    (void)hoisted__Bool_4893;
    return hoisted__Bool_4893;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4901 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4901;
    if (hoisted__Bool_4901) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4902 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4902;
    if (hoisted__Bool_4902) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4903 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4903;
    if (hoisted__Bool_4903) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4904 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4904;
    UNREACHABLE(&hoisted__Str_4904);
    Str_delete(&hoisted__Str_4904, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4905 = 4;
    (void)hoisted__U32_4905;
    return hoisted__U32_4905;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_4906 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4906;
    Bool hoisted__Bool_4907 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4907;
    assert(&hoisted__Str_4906, hoisted__Bool_4907);
    Str_delete(&hoisted__Str_4906, (Bool){0});
    Bool hoisted__Bool_4908 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4908;
    Color_delete(&c, 0);
    Str hoisted__Str_4909 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4909;
    Bool hoisted__Bool_4910 = not(hoisted__Bool_4908);
    (void)hoisted__Bool_4910;
    assert(&hoisted__Str_4909, hoisted__Bool_4910);
    Str_delete(&hoisted__Str_4909, (Bool){0});
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
    Bool hoisted__Bool_4911 = is(self, other);
    (void)hoisted__Bool_4911;
    return hoisted__Bool_4911;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_4929 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4929;
    if (hoisted__Bool_4929) {
        I64 *hoisted__I64_4925 = get_payload(self);
        (void)hoisted__I64_4925;
        (void)hoisted__I64_4925;
        Bool hoisted__Bool_4926 = 0;
        (void)hoisted__Bool_4926;
        I64_delete(hoisted__I64_4925, hoisted__Bool_4926);
    }
    Bool hoisted__Bool_4930 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4930;
    if (hoisted__Bool_4930) {
        Str *hoisted__Str_4927 = get_payload(self);
        (void)hoisted__Str_4927;
        (void)hoisted__Str_4927;
        Bool hoisted__Bool_4928 = 0;
        (void)hoisted__Bool_4928;
        Str_delete(hoisted__Str_4927, hoisted__Bool_4928);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4959 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4959;
    if (hoisted__Bool_4959) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4956 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4956;
        { Token * _ret_val = hoisted__Token_4956;
                return _ret_val; }
    }
    Bool hoisted__Bool_4960 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4960;
    if (hoisted__Bool_4960) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4957 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4957;
        Token *hoisted__Token_4958 = Token_Name(hoisted__Str_4957);
        (void)hoisted__Token_4958;
        { Token * _ret_val = hoisted__Token_4958;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4961 = 24;
    (void)hoisted__U32_4961;
    return hoisted__U32_4961;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_4963 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4963;
    Bool hoisted__Bool_4964 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4964;
    assert(&hoisted__Str_4963, hoisted__Bool_4964);
    Str_delete(&hoisted__Str_4963, (Bool){0});
    Bool hoisted__Bool_4965 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4965;
    Token_delete(t, 1);
    Str hoisted__Str_4966 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4966;
    Bool hoisted__Bool_4967 = not(hoisted__Bool_4965);
    (void)hoisted__Bool_4967;
    assert(&hoisted__Str_4966, hoisted__Bool_4967);
    Str_delete(&hoisted__Str_4966, (Bool){0});
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_4968 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4968;
    Bool hoisted__Bool_4969 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4969;
    assert(&hoisted__Str_4968, hoisted__Bool_4969);
    Str_delete(&hoisted__Str_4968, (Bool){0});
    Bool hoisted__Bool_4970 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4970;
    Color_delete(({ Color *_oa = malloc(sizeof(Color)); *_oa = c; _oa; }), 1);
    Str hoisted__Str_4971 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4971;
    Bool hoisted__Bool_4972 = not(hoisted__Bool_4970);
    (void)hoisted__Bool_4972;
    assert(&hoisted__Str_4971, hoisted__Bool_4972);
    Str_delete(&hoisted__Str_4971, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_4975 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4975;
    Bool hoisted__Bool_4976 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4976;
    assert(&hoisted__Str_4975, hoisted__Bool_4976);
    Str_delete(&hoisted__Str_4975, (Bool){0});
    Bool hoisted__Bool_4977 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4977;
    Token_delete(t, 1);
    Str hoisted__Str_4978 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4978;
    Bool hoisted__Bool_4979 = not(hoisted__Bool_4977);
    (void)hoisted__Bool_4979;
    assert(&hoisted__Str_4978, hoisted__Bool_4979);
    Str_delete(&hoisted__Str_4978, (Bool){0});
}

I64 F32_cmp_dyn(void *_a0, void *_a1) {
    return F32_cmp(*(F32 *)_a0, *(F32 *)_a1);
}
void *F32_clone_dyn(void *_a0) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(_a0); return _r;
}
U64 F32_hash_dyn(void *_a0, void *_a1) {
    return F32_hash(*(F32 *)_a0, _a1);
}
void F32_delete_dyn(void *_a0, Bool _a1) {
    F32_delete(_a0, _a1);
}
U32 F32_size_dyn(void) {
    return F32_size();
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
U64 U64_hash_dyn(void *_a0, void *_a1) {
    return U64_hash(*(U64 *)_a0, _a1);
}
void U64_delete_dyn(void *_a0, Bool _a1) {
    U64_delete(_a0, _a1);
}
U32 U64_size_dyn(void) {
    return U64_size();
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
U64 U32_hash_dyn(void *_a0, void *_a1) {
    return U32_hash(*(U32 *)_a0, _a1);
}
void U32_delete_dyn(void *_a0, Bool _a1) {
    U32_delete(_a0, _a1);
}
U32 U32_size_dyn(void) {
    return U32_size();
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
U64 I32_hash_dyn(void *_a0, void *_a1) {
    return I32_hash(*(I32 *)_a0, _a1);
}
void I32_delete_dyn(void *_a0, Bool _a1) {
    I32_delete(_a0, _a1);
}
U32 I32_size_dyn(void) {
    return I32_size();
}
I64 I8_cmp_dyn(void *_a0, void *_a1) {
    return I8_cmp(*(I8 *)_a0, *(I8 *)_a1);
}
void *I8_clone_dyn(void *_a0) {
    I8 *_r = malloc(sizeof(I8)); *_r = I8_clone(_a0); return _r;
}
U64 I8_hash_dyn(void *_a0, void *_a1) {
    return I8_hash(*(I8 *)_a0, _a1);
}
void I8_delete_dyn(void *_a0, Bool _a1) {
    I8_delete(_a0, _a1);
}
U32 I8_size_dyn(void) {
    return I8_size();
}
I64 U8_cmp_dyn(void *_a0, void *_a1) {
    return U8_cmp(*(U8 *)_a0, *(U8 *)_a1);
}
void *U8_clone_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(_a0); return _r;
}
U64 U8_hash_dyn(void *_a0, void *_a1) {
    return U8_hash(*(U8 *)_a0, _a1);
}
void U8_delete_dyn(void *_a0, Bool _a1) {
    U8_delete(_a0, _a1);
}
U32 U8_size_dyn(void) {
    return U8_size();
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
U64 I64_hash_dyn(void *_a0, void *_a1) {
    return I64_hash(*(I64 *)_a0, _a1);
}
void I64_delete_dyn(void *_a0, Bool _a1) {
    I64_delete(_a0, _a1);
}
U32 I64_size_dyn(void) {
    return I64_size();
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
U64 Bool_hash_dyn(void *_a0, void *_a1) {
    return Bool_hash(*(Bool *)_a0, _a1);
}
void Bool_delete_dyn(void *_a0, Bool _a1) {
    Bool_delete(_a0, _a1);
}
U32 Bool_size_dyn(void) {
    return Bool_size();
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
U32 CfVec2_size_dyn(void) {
    return CfVec2_size();
}
void CfRect_delete_dyn(void *_a0, Bool _a1) {
    CfRect_delete(_a0, _a1);
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)F32_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)F32_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)F32_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)U64_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U64_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U64_size_dyn;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)U32_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U32_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U32_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U32_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U32_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U32_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U32_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)I32_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I32_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I32_size_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)I8_hash_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I8_delete_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I8_size_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)U8_hash_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U8_delete_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U8_size_dyn;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)I64_hash_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I64_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I64_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I64_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I64_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I64_neq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Bool_eq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Bool_cmp_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Bool_clone_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)Bool_hash_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Bool_delete_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Bool_size_dyn;
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
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)CfVec2_size_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)CfRect_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)CfRect_delete_dyn;
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
