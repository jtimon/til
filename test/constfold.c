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
    U32 hoisted__U32_1315 = 8;
    (void)hoisted__U32_1315;
    return hoisted__U32_1315;
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1523 = 0;
    (void)hoisted__I64_1523;
    Bool hoisted__Bool_1524 = I64_eq(val, hoisted__I64_1523);
    (void)hoisted__Bool_1524;
    if (hoisted__Bool_1524) {
        U64 hoisted__U64_1487 = 2ULL;
        (void)hoisted__U64_1487;
        void * buf = malloc(hoisted__U64_1487);
        I64 hoisted__I64_1488 = 48;
        (void)hoisted__I64_1488;
        U64 hoisted__U64_1489 = 1ULL;
        (void)hoisted__U64_1489;
        memcpy(buf, &hoisted__I64_1488, hoisted__U64_1489);
        U64 hoisted__U64_1490 = 1ULL;
        (void)hoisted__U64_1490;
        void *hoisted__v_1491 = ptr_add(buf, hoisted__U64_1490);
        (void)hoisted__v_1491;
        (void)hoisted__v_1491;
        I32 hoisted__I32_1492 = 0;
        (void)hoisted__I32_1492;
        U64 hoisted__U64_1493 = 1ULL;
        (void)hoisted__U64_1493;
        memset(hoisted__v_1491, hoisted__I32_1492, hoisted__U64_1493);
        I32_delete(&hoisted__I32_1492, 0);
        I64 hoisted__I64_1494 = 1;
        (void)hoisted__I64_1494;
        I64 hoisted__I64_1495 = 1;
        (void)hoisted__I64_1495;
        Str *hoisted__Str_1496 = malloc(sizeof(Str));
        hoisted__Str_1496->c_str = buf;
        hoisted__Str_1496->count = hoisted__I64_1494;
        hoisted__Str_1496->cap = hoisted__I64_1495;
        (void)hoisted__Str_1496;
        { Str * _ret_val = hoisted__Str_1496;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1525 = 0;
    (void)hoisted__I64_1525;
    Bool hoisted__Bool_1526 = I64_lt(val, hoisted__I64_1525);
    (void)hoisted__Bool_1526;
    if (hoisted__Bool_1526) {
        Bool hoisted__Bool_1497 = 1;
        (void)hoisted__Bool_1497;
        is_neg = hoisted__Bool_1497;
        I64 hoisted__I64_1498 = 0;
        (void)hoisted__I64_1498;
        I64 hoisted__I64_1499 = I64_sub(hoisted__I64_1498, val);
        (void)hoisted__I64_1499;
        v = hoisted__I64_1499;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1501 = 0;
        (void)hoisted__I64_1501;
        Bool _wcond_Bool_1500 = I64_gt(tmp, hoisted__I64_1501);
        (void)_wcond_Bool_1500;
        if (_wcond_Bool_1500) {
        } else {
            break;
        }
        U64 hoisted__U64_1502 = 1ULL;
        (void)hoisted__U64_1502;
        U64 hoisted__U64_1503 = U64_add(ndigits, hoisted__U64_1502);
        (void)hoisted__U64_1503;
        ndigits = hoisted__U64_1503;
        I64 hoisted__I64_1504 = 10;
        (void)hoisted__I64_1504;
        I64 hoisted__I64_1505 = I64_div(tmp, hoisted__I64_1504);
        (void)hoisted__I64_1505;
        tmp = hoisted__I64_1505;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1506 = 1ULL;
        (void)hoisted__U64_1506;
        U64 hoisted__U64_1507 = U64_add(total, hoisted__U64_1506);
        (void)hoisted__U64_1507;
        total = hoisted__U64_1507;
    }
    U64 hoisted__U64_1527 = 1ULL;
    (void)hoisted__U64_1527;
    U64 hoisted__U64_1528 = U64_add(total, hoisted__U64_1527);
    (void)hoisted__U64_1528;
    void * buf = malloc(hoisted__U64_1528);
    if (is_neg) {
        I64 hoisted__I64_1508 = 45;
        (void)hoisted__I64_1508;
        U64 hoisted__U64_1509 = 1ULL;
        (void)hoisted__U64_1509;
        memcpy(buf, &hoisted__I64_1508, hoisted__U64_1509);
    }
    U64 hoisted__U64_1529 = 1ULL;
    (void)hoisted__U64_1529;
    U64 i = U64_sub(total, hoisted__U64_1529);
    while (1) {
        I64 hoisted__I64_1511 = 0;
        (void)hoisted__I64_1511;
        Bool _wcond_Bool_1510 = I64_gt(v, hoisted__I64_1511);
        (void)_wcond_Bool_1510;
        if (_wcond_Bool_1510) {
        } else {
            break;
        }
        I64 hoisted__I64_1512 = 10;
        (void)hoisted__I64_1512;
        I64 hoisted__I64_1513 = I64_mod(v, hoisted__I64_1512);
        (void)hoisted__I64_1513;
        I64 hoisted__I64_1514 = 48;
        (void)hoisted__I64_1514;
        I64 hoisted__I64_1515 = I64_add(hoisted__I64_1513, hoisted__I64_1514);
        (void)hoisted__I64_1515;
        void *hoisted__v_1516 = ptr_add(buf, i);
        (void)hoisted__v_1516;
        (void)hoisted__v_1516;
        U8 hoisted__U8_1517 = I64_to_u8(hoisted__I64_1515);
        (void)hoisted__U8_1517;
        U64 hoisted__U64_1518 = 1ULL;
        (void)hoisted__U64_1518;
        memcpy(hoisted__v_1516, &hoisted__U8_1517, hoisted__U64_1518);
        U8_delete(&hoisted__U8_1517, 0);
        I64 hoisted__I64_1519 = 10;
        (void)hoisted__I64_1519;
        I64 hoisted__I64_1520 = I64_div(v, hoisted__I64_1519);
        (void)hoisted__I64_1520;
        v = hoisted__I64_1520;
        U64 hoisted__U64_1521 = 1ULL;
        (void)hoisted__U64_1521;
        U64 hoisted__U64_1522 = U64_sub(i, hoisted__U64_1521);
        (void)hoisted__U64_1522;
        i = hoisted__U64_1522;
    }
    void *hoisted__v_1530 = ptr_add(buf, total);
    (void)hoisted__v_1530;
    (void)hoisted__v_1530;
    I32 hoisted__I32_1531 = 0;
    (void)hoisted__I32_1531;
    U64 hoisted__U64_1532 = 1ULL;
    (void)hoisted__U64_1532;
    memset(hoisted__v_1530, hoisted__I32_1531, hoisted__U64_1532);
    I32_delete(&hoisted__I32_1531, 0);
    Str *hoisted__Str_1533 = malloc(sizeof(Str));
    hoisted__Str_1533->c_str = buf;
    hoisted__Str_1533->count = total;
    hoisted__Str_1533->cap = total;
    (void)hoisted__Str_1533;
    return hoisted__Str_1533;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1547 = 8;
    (void)hoisted__U32_1547;
    U64 hoisted__U64_1548 = ((U64 (*)(I64 *, U32))(void *)hasher)(&self, hoisted__U32_1547);
    (void)hoisted__U64_1548;
    return hoisted__U64_1548;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1554 = 8;
    (void)hoisted__U32_1554;
    return hoisted__U32_1554;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1687 = I64_cmp(a, b);
    (void)hoisted__I64_1687;
    I64 hoisted__I64_1688 = -1;
    (void)hoisted__I64_1688;
    Bool hoisted__Bool_1689 = I64_eq(hoisted__I64_1687, hoisted__I64_1688);
    (void)hoisted__Bool_1689;
    return hoisted__Bool_1689;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1690 = I64_cmp(a, b);
    (void)hoisted__I64_1690;
    I64 hoisted__I64_1691 = 1;
    (void)hoisted__I64_1691;
    Bool hoisted__Bool_1692 = I64_eq(hoisted__I64_1690, hoisted__I64_1691);
    (void)hoisted__Bool_1692;
    return hoisted__Bool_1692;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1693 = I64_eq(a, b);
    (void)hoisted__Bool_1693;
    Bool hoisted__Bool_1694 = not(hoisted__Bool_1693);
    (void)hoisted__Bool_1694;
    return hoisted__Bool_1694;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1708 = Bool_eq(a, b);
    (void)hoisted__Bool_1708;
    if (hoisted__Bool_1708) {
        I64 hoisted__I64_1706 = 0;
        (void)hoisted__I64_1706;
        { I64 _ret_val = hoisted__I64_1706;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1707 = -1;
        (void)hoisted__I64_1707;
        return hoisted__I64_1707;
    }
    I64 hoisted__I64_1709 = 1;
    (void)hoisted__I64_1709;
    return hoisted__I64_1709;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1711 = 1;
    (void)hoisted__U32_1711;
    U64 hoisted__U64_1712 = ((U64 (*)(Bool *, U32))(void *)hasher)(&self, hoisted__U32_1711);
    (void)hoisted__U64_1712;
    return hoisted__U64_1712;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1713 = 1;
    (void)hoisted__U32_1713;
    return hoisted__U32_1713;
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
    Bool hoisted__Bool_1854 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1854;
    if (hoisted__Bool_1854) {
        Bool hoisted__Bool_1852 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1852;
        { Bool _ret_val = hoisted__Bool_1852;
                return _ret_val; }
    }
    Bool hoisted__Bool_1855 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1855;
    if (hoisted__Bool_1855) {
        Bool hoisted__Bool_1853 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1853;
        { Bool _ret_val = hoisted__Bool_1853;
                return _ret_val; }
    }
    Bool hoisted__Bool_1856 = 0;
    (void)hoisted__Bool_1856;
    return hoisted__Bool_1856;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1862 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1862;
    if (hoisted__Bool_1862) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1863 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1863;
    if (hoisted__Bool_1863) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Str hoisted__Str_1864 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1864;
    UNREACHABLE(&hoisted__Str_1864);
    Str_delete(&hoisted__Str_1864, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1865 = 4;
    (void)hoisted__U32_1865;
    return hoisted__U32_1865;
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
    Bool hoisted__Bool_1928 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1928;
    if (hoisted__Bool_1928) {
        Str *hoisted__Str_1920 = get_payload(self);
        (void)hoisted__Str_1920;
        (void)hoisted__Str_1920;
        Bool hoisted__Bool_1921 = 0;
        (void)hoisted__Bool_1921;
        Str_delete(hoisted__Str_1920, hoisted__Bool_1921);
    }
    Bool hoisted__Bool_1929 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1929;
    if (hoisted__Bool_1929) {
        Str *hoisted__Str_1922 = get_payload(self);
        (void)hoisted__Str_1922;
        (void)hoisted__Str_1922;
        Bool hoisted__Bool_1923 = 0;
        (void)hoisted__Bool_1923;
        Str_delete(hoisted__Str_1922, hoisted__Bool_1923);
    }
    Bool hoisted__Bool_1930 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1930;
    if (hoisted__Bool_1930) {
        Str *hoisted__Str_1924 = get_payload(self);
        (void)hoisted__Str_1924;
        (void)hoisted__Str_1924;
        Bool hoisted__Bool_1925 = 0;
        (void)hoisted__Bool_1925;
        Str_delete(hoisted__Str_1924, hoisted__Bool_1925);
    }
    Bool hoisted__Bool_1931 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1931;
    if (hoisted__Bool_1931) {
        Primitive *hoisted__Primitive_1926 = get_payload(self);
        (void)hoisted__Primitive_1926;
        (void)hoisted__Primitive_1926;
        Bool hoisted__Bool_1927 = 0;
        (void)hoisted__Bool_1927;
        Primitive_delete(hoisted__Primitive_1926, hoisted__Bool_1927);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2013 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2013;
    if (hoisted__Bool_2013) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2014 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2014;
    if (hoisted__Bool_2014) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2015 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)hoisted__Bool_2015;
    if (hoisted__Bool_2015) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_2016 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)hoisted__Bool_2016;
    if (hoisted__Bool_2016) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2017 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)hoisted__Bool_2017;
    if (hoisted__Bool_2017) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2018 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)hoisted__Bool_2018;
    if (hoisted__Bool_2018) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2019 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)hoisted__Bool_2019;
    if (hoisted__Bool_2019) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2020 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)hoisted__Bool_2020;
    if (hoisted__Bool_2020) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2021 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)hoisted__Bool_2021;
    if (hoisted__Bool_2021) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool;
                return _r; }
    }
    Bool hoisted__Bool_2022 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2022;
    if (hoisted__Bool_2022) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_2007 = Str_clone(_clone_payload_Struct_9);
        (void)hoisted__Str_2007;
        Type *hoisted__Type_2008 = Type_Struct(hoisted__Str_2007);
        (void)hoisted__Type_2008;
        { Type * _ret_val = hoisted__Type_2008;
                return _ret_val; }
    }
    Bool hoisted__Bool_2023 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2023;
    if (hoisted__Bool_2023) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2024 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2024;
    if (hoisted__Bool_2024) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_2009 = Str_clone(_clone_payload_Enum_11);
        (void)hoisted__Str_2009;
        Type *hoisted__Type_2010 = Type_Enum(hoisted__Str_2009);
        (void)hoisted__Type_2010;
        { Type * _ret_val = hoisted__Type_2010;
                return _ret_val; }
    }
    Bool hoisted__Bool_2025 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2025;
    if (hoisted__Bool_2025) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2026 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2026;
    if (hoisted__Bool_2026) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2027 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2027;
    if (hoisted__Bool_2027) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2028 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2028;
    if (hoisted__Bool_2028) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2029 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2029;
    if (hoisted__Bool_2029) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_2011 = Str_clone(_clone_payload_Custom_16);
        (void)hoisted__Str_2011;
        Type *hoisted__Type_2012 = Type_Custom(hoisted__Str_2011);
        (void)hoisted__Type_2012;
        { Type * _ret_val = hoisted__Type_2012;
                return _ret_val; }
    }
    Bool hoisted__Bool_2030 = is(self, &(Type){.tag = Type_TAG_I8});
    (void)hoisted__Bool_2030;
    if (hoisted__Bool_2030) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8;
                return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive hoisted__Primitive_2031 = DEREF(_clone_payload_Primitive_18);
    (void)hoisted__Primitive_2031;
    Type *hoisted__Type_2032 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2031; _oa; }));
    (void)hoisted__Type_2032;
    return hoisted__Type_2032;
}

U32 Type_size(void) {
    U32 hoisted__U32_2033 = 24;
    (void)hoisted__U32_2033;
    return hoisted__U32_2033;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3684 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3684;
    if (hoisted__Bool_3684) {
        Type *hoisted__Type_3679 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3679;
        U32 hoisted__U32_3680 = 1;
        (void)hoisted__U32_3680;
        Array *_va_Array_112 = Array_new(hoisted__Type_3679, hoisted__U32_3680);
        (void)_va_Array_112;
        Type_delete(hoisted__Type_3679, 1);
        U32 hoisted__U32_3681 = 0;
        (void)hoisted__U32_3681;
        Str hoisted__Str_3682 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3682;
        Array_set(_va_Array_112, hoisted__U32_3681, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3682; _oa; }));
        Str hoisted__Str_3683 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3683;
        panic(&hoisted__Str_3683, _va_Array_112);
        Str_delete(&hoisted__Str_3683, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3685 = calloc(cap, elem_size);
    (void)hoisted__v_3685;
    void * hoisted__v_3686 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3686;
    void * hoisted__v_3687 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3687;
    Array *hoisted__Array_3688 = malloc(sizeof(Array));
    hoisted__Array_3688->data = hoisted__v_3685;
    hoisted__Array_3688->cap = cap;
    hoisted__Array_3688->elem_size = elem_size;
    hoisted__Array_3688->elem_clone = hoisted__v_3686;
    hoisted__Array_3688->elem_delete = hoisted__v_3687;
    (void)hoisted__Array_3688;
    return hoisted__Array_3688;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3689 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3689;
    Str_delete(elem_type, 1);
    return hoisted__Array_3689;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3710 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3710;
    if (hoisted__Bool_3710) {
        Type *hoisted__Type_3691 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3691;
        U32 hoisted__U32_3692 = 6;
        (void)hoisted__U32_3692;
        Array *_va_Array_113 = Array_new(hoisted__Type_3691, hoisted__U32_3692);
        (void)_va_Array_113;
        Type_delete(hoisted__Type_3691, 1);
        U32 hoisted__U32_3693 = 0;
        (void)hoisted__U32_3693;
        Str hoisted__Str_3694 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3694;
        Array_set(_va_Array_113, hoisted__U32_3693, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3694; _oa; }));
        U32 hoisted__U32_3695 = 1;
        (void)hoisted__U32_3695;
        Str hoisted__Str_3696 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3696;
        Array_set(_va_Array_113, hoisted__U32_3695, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3696; _oa; }));
        U32 hoisted__U32_3697 = 2;
        (void)hoisted__U32_3697;
        Str *hoisted__Str_3698 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3698;
        Array_set(_va_Array_113, hoisted__U32_3697, hoisted__Str_3698);
        U32 hoisted__U32_3699 = 3;
        (void)hoisted__U32_3699;
        Str hoisted__Str_3700 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3700;
        Array_set(_va_Array_113, hoisted__U32_3699, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3700; _oa; }));
        U32 hoisted__U32_3701 = 4;
        (void)hoisted__U32_3701;
        Str *hoisted__Str_3702 = U32_to_str(self->cap);
        (void)hoisted__Str_3702;
        Array_set(_va_Array_113, hoisted__U32_3701, hoisted__Str_3702);
        U32 hoisted__U32_3703 = 5;
        (void)hoisted__U32_3703;
        Str hoisted__Str_3704 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3704;
        Array_set(_va_Array_113, hoisted__U32_3703, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3704; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3705 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_113); hoisted__OutOfBounds_3705->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3705;
        U32 hoisted__U32_3706 = 16;
        (void)hoisted__U32_3706;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3705, hoisted__U32_3706);
        OutOfBounds_delete(hoisted__OutOfBounds_3705, 1);
        I64 hoisted__I64_3707 = 3;
        (void)hoisted__I64_3707;
        *_err_kind = hoisted__I64_3707;
    }
    I64 hoisted__I64_3711 = 0;
    (void)hoisted__I64_3711;
    Bool hoisted__Bool_3712 = I64_eq(DEREF(_err_kind), hoisted__I64_3711);
    (void)hoisted__Bool_3712;
    if (hoisted__Bool_3712) {
        U32 hoisted__U64_3708 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3708;
        void *hoisted__v_3709 = ptr_add(self->data, hoisted__U64_3708);
        (void)hoisted__v_3709;
        (void)hoisted__v_3709;
        { void * _ret_val = hoisted__v_3709;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3727 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3727;
    if (hoisted__Bool_3727) {
        Type *hoisted__Type_3714 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3714;
        U32 hoisted__U32_3715 = 5;
        (void)hoisted__U32_3715;
        Array *_va_Array_114 = Array_new(hoisted__Type_3714, hoisted__U32_3715);
        (void)_va_Array_114;
        Type_delete(hoisted__Type_3714, 1);
        U32 hoisted__U32_3716 = 0;
        (void)hoisted__U32_3716;
        Str hoisted__Str_3717 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3717;
        Array_set(_va_Array_114, hoisted__U32_3716, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3717; _oa; }));
        U32 hoisted__U32_3718 = 1;
        (void)hoisted__U32_3718;
        Str *hoisted__Str_3719 = U32_to_str(i);
        (void)hoisted__Str_3719;
        Array_set(_va_Array_114, hoisted__U32_3718, hoisted__Str_3719);
        U32 hoisted__U32_3720 = 2;
        (void)hoisted__U32_3720;
        Str hoisted__Str_3721 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3721;
        Array_set(_va_Array_114, hoisted__U32_3720, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3721; _oa; }));
        U32 hoisted__U32_3722 = 3;
        (void)hoisted__U32_3722;
        Str *hoisted__Str_3723 = U32_to_str(self->cap);
        (void)hoisted__Str_3723;
        Array_set(_va_Array_114, hoisted__U32_3722, hoisted__Str_3723);
        U32 hoisted__U32_3724 = 4;
        (void)hoisted__U32_3724;
        Str hoisted__Str_3725 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3725;
        Array_set(_va_Array_114, hoisted__U32_3724, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3725; _oa; }));
        Str hoisted__Str_3726 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3726;
        panic(&hoisted__Str_3726, _va_Array_114);
        Str_delete(&hoisted__Str_3726, (Bool){0});
    }
    U32 hoisted__U64_3728 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3728;
    void *hoisted__v_3729 = ptr_add(self->data, hoisted__U64_3728);
    (void)hoisted__v_3729;
    (void)hoisted__v_3729;
    Bool hoisted__Bool_3730 = 0;
    (void)hoisted__Bool_3730;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3729, hoisted__Bool_3730);
    U32 hoisted__U64_3731 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3731;
    void *hoisted__v_3732 = ptr_add(self->data, hoisted__U64_3731);
    (void)hoisted__v_3732;
    (void)hoisted__v_3732;
    memcpy(hoisted__v_3732, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3733 = self->cap;
        (void)_re_U32_3733;
        U32 _rc_U32_3733 = 0;
        (void)_rc_U32_3733;
        Bool hoisted__Bool_3742 = U32_lte(_rc_U32_3733, _re_U32_3733);
        (void)hoisted__Bool_3742;
        if (hoisted__Bool_3742) {
            while (1) {
                Bool _wcond_Bool_3734 = U32_lt(_rc_U32_3733, _re_U32_3733);
                (void)_wcond_Bool_3734;
                if (_wcond_Bool_3734) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3733);
                U32_inc(&_rc_U32_3733);
                U32 hoisted__U64_3735 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3735;
                void *hoisted__v_3736 = ptr_add(self->data, hoisted__U64_3735);
                (void)hoisted__v_3736;
                (void)hoisted__v_3736;
                Bool hoisted__Bool_3737 = 0;
                (void)hoisted__Bool_3737;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3736, hoisted__Bool_3737);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3738 = U32_gt(_rc_U32_3733, _re_U32_3733);
                (void)_wcond_Bool_3738;
                if (_wcond_Bool_3738) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3733);
                U32_dec(&_rc_U32_3733);
                U32 hoisted__U64_3739 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3739;
                void *hoisted__v_3740 = ptr_add(self->data, hoisted__U64_3739);
                (void)hoisted__v_3740;
                (void)hoisted__v_3740;
                Bool hoisted__Bool_3741 = 0;
                (void)hoisted__Bool_3741;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3740, hoisted__Bool_3741);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3755 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3755;
    void * new_data = malloc(hoisted__U64_3755);
    {
        U32 _re_U32_3743 = self->cap;
        (void)_re_U32_3743;
        U32 _rc_U32_3743 = 0;
        (void)_rc_U32_3743;
        Bool hoisted__Bool_3754 = U32_lte(_rc_U32_3743, _re_U32_3743);
        (void)hoisted__Bool_3754;
        if (hoisted__Bool_3754) {
            while (1) {
                Bool _wcond_Bool_3744 = U32_lt(_rc_U32_3743, _re_U32_3743);
                (void)_wcond_Bool_3744;
                if (_wcond_Bool_3744) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3743);
                U32_inc(&_rc_U32_3743);
                U32 hoisted__U64_3745 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3745;
                void *hoisted__v_3746 = ptr_add(self->data, hoisted__U64_3745);
                (void)hoisted__v_3746;
                (void)hoisted__v_3746;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3746);
                U32 hoisted__U64_3747 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3747;
                void *hoisted__v_3748 = ptr_add(new_data, hoisted__U64_3747);
                (void)hoisted__v_3748;
                (void)hoisted__v_3748;
                memcpy(hoisted__v_3748, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3749 = U32_gt(_rc_U32_3743, _re_U32_3743);
                (void)_wcond_Bool_3749;
                if (_wcond_Bool_3749) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3743);
                U32_dec(&_rc_U32_3743);
                U32 hoisted__U64_3750 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3750;
                void *hoisted__v_3751 = ptr_add(self->data, hoisted__U64_3750);
                (void)hoisted__v_3751;
                (void)hoisted__v_3751;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3751);
                U32 hoisted__U64_3752 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3752;
                void *hoisted__v_3753 = ptr_add(new_data, hoisted__U64_3752);
                (void)hoisted__v_3753;
                (void)hoisted__v_3753;
                memcpy(hoisted__v_3753, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3756 = malloc(sizeof(Array));
    hoisted__Array_3756->data = new_data;
    hoisted__Array_3756->cap = self->cap;
    hoisted__Array_3756->elem_size = self->elem_size;
    hoisted__Array_3756->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3756->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3756;
    return hoisted__Array_3756;
}

U32 Array_size(void) {
    U32 hoisted__U32_3757 = 32;
    (void)hoisted__U32_3757;
    return hoisted__U32_3757;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4101 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4101;
    U32 hoisted__U32_4102 = 3;
    (void)hoisted__U32_4102;
    Array *_va_Array_143 = Array_new(hoisted__Type_4101, hoisted__U32_4102);
    (void)_va_Array_143;
    Type_delete(hoisted__Type_4101, 1);
    U32 hoisted__U32_4103 = 0;
    (void)hoisted__U32_4103;
    Str *hoisted__Str_4104 = Str_clone(loc_str);
    (void)hoisted__Str_4104;
    Array_set(_va_Array_143, hoisted__U32_4103, hoisted__Str_4104);
    U32 hoisted__U32_4105 = 1;
    (void)hoisted__U32_4105;
    Str hoisted__Str_4106 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4106;
    Array_set(_va_Array_143, hoisted__U32_4105, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4106; _oa; }));
    Array *hoisted__Array_4107 = Array_clone(parts);
    (void)hoisted__Array_4107;
    Array_delete(parts, 1);
    U32 hoisted__U32_4108 = 2;
    (void)hoisted__U32_4108;
    Str *hoisted__Str_4109 = format(hoisted__Array_4107);
    (void)hoisted__Str_4109;
    Array_set(_va_Array_143, hoisted__U32_4108, hoisted__Str_4109);
    println(_va_Array_143);
    I64 hoisted__I64_4110 = 1;
    (void)hoisted__I64_4110;
    exit(hoisted__I64_4110);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4120 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4120;
    U32 hoisted__U32_4121 = 1;
    (void)hoisted__U32_4121;
    Array *_va_Array_145 = Array_new(hoisted__Type_4120, hoisted__U32_4121);
    (void)_va_Array_145;
    Type_delete(hoisted__Type_4120, 1);
    U32 hoisted__U32_4122 = 0;
    (void)hoisted__U32_4122;
    Str hoisted__Str_4123 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4123;
    Array_set(_va_Array_145, hoisted__U32_4122, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4123; _oa; }));
    panic(loc_str, _va_Array_145);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4129 = not(cond);
    (void)hoisted__Bool_4129;
    if (hoisted__Bool_4129) {
        Type *hoisted__Type_4125 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4125;
        U32 hoisted__U32_4126 = 1;
        (void)hoisted__U32_4126;
        Array *_va_Array_146 = Array_new(hoisted__Type_4125, hoisted__U32_4126);
        (void)_va_Array_146;
        Type_delete(hoisted__Type_4125, 1);
        U32 hoisted__U32_4127 = 0;
        (void)hoisted__U32_4127;
        Str hoisted__Str_4128 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4128;
        Array_set(_va_Array_146, hoisted__U32_4127, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4128; _oa; }));
        panic(loc_str, _va_Array_146);
    }
    Bool hoisted__Bool_4130 = 1;
    (void)hoisted__Bool_4130;
    return hoisted__Bool_4130;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4153 = I64_neq(a, b);
    (void)hoisted__Bool_4153;
    if (hoisted__Bool_4153) {
        Type *hoisted__Type_4141 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4141;
        U32 hoisted__U32_4142 = 5;
        (void)hoisted__U32_4142;
        Array *_va_Array_148 = Array_new(hoisted__Type_4141, hoisted__U32_4142);
        (void)_va_Array_148;
        Type_delete(hoisted__Type_4141, 1);
        U32 hoisted__U32_4143 = 0;
        (void)hoisted__U32_4143;
        Str hoisted__Str_4144 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4144;
        Array_set(_va_Array_148, hoisted__U32_4143, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4144; _oa; }));
        U32 hoisted__U32_4145 = 1;
        (void)hoisted__U32_4145;
        Str *hoisted__Str_4146 = I64_to_str(a);
        (void)hoisted__Str_4146;
        Array_set(_va_Array_148, hoisted__U32_4145, hoisted__Str_4146);
        U32 hoisted__U32_4147 = 2;
        (void)hoisted__U32_4147;
        Str hoisted__Str_4148 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4148;
        Array_set(_va_Array_148, hoisted__U32_4147, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4148; _oa; }));
        U32 hoisted__U32_4149 = 3;
        (void)hoisted__U32_4149;
        Str *hoisted__Str_4150 = I64_to_str(b);
        (void)hoisted__Str_4150;
        Array_set(_va_Array_148, hoisted__U32_4149, hoisted__Str_4150);
        U32 hoisted__U32_4151 = 4;
        (void)hoisted__U32_4151;
        Str hoisted__Str_4152 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4152;
        Array_set(_va_Array_148, hoisted__U32_4151, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4152; _oa; }));
        panic(loc_str, _va_Array_148);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4167 = Str_eq(a, b);
    (void)hoisted__Bool_4167;
    Bool hoisted__Bool_4168 = not(hoisted__Bool_4167);
    (void)hoisted__Bool_4168;
    if (hoisted__Bool_4168) {
        Type *hoisted__Type_4155 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4155;
        U32 hoisted__U32_4156 = 5;
        (void)hoisted__U32_4156;
        Array *_va_Array_149 = Array_new(hoisted__Type_4155, hoisted__U32_4156);
        (void)_va_Array_149;
        Type_delete(hoisted__Type_4155, 1);
        U32 hoisted__U32_4157 = 0;
        (void)hoisted__U32_4157;
        Str hoisted__Str_4158 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4158;
        Array_set(_va_Array_149, hoisted__U32_4157, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4158; _oa; }));
        U32 hoisted__U32_4159 = 1;
        (void)hoisted__U32_4159;
        Str *hoisted__Str_4160 = Str_clone(a);
        (void)hoisted__Str_4160;
        Array_set(_va_Array_149, hoisted__U32_4159, hoisted__Str_4160);
        U32 hoisted__U32_4161 = 2;
        (void)hoisted__U32_4161;
        Str hoisted__Str_4162 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4162;
        Array_set(_va_Array_149, hoisted__U32_4161, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4162; _oa; }));
        U32 hoisted__U32_4163 = 3;
        (void)hoisted__U32_4163;
        Str *hoisted__Str_4164 = Str_clone(b);
        (void)hoisted__Str_4164;
        Array_set(_va_Array_149, hoisted__U32_4163, hoisted__Str_4164);
        U32 hoisted__U32_4165 = 4;
        (void)hoisted__U32_4165;
        Str hoisted__Str_4166 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4166;
        Array_set(_va_Array_149, hoisted__U32_4165, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4166; _oa; }));
        panic(loc_str, _va_Array_149);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4169 = parts;
        (void)_fc_Array_4169;
        (void)_fc_Array_4169;
        U32 _fi_USize_4169 = 0;
        (void)_fi_USize_4169;
        I64 _forin_err_kind_4169 = 0;
        (void)_forin_err_kind_4169;
        OutOfBounds *_forin_OutOfBounds_4169 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4169->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4169;
        while (1) {
            U32 hoisted__U32_4177 = Array_len(_fc_Array_4169);
            (void)hoisted__U32_4177;
            Bool _wcond_Bool_4170 = U32_lt(_fi_USize_4169, hoisted__U32_4177);
            (void)_wcond_Bool_4170;
            if (_wcond_Bool_4170) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4169, &_fi_USize_4169, &_forin_err_kind_4169, _forin_OutOfBounds_4169);
            I64 hoisted__I64_4178 = 0;
            (void)hoisted__I64_4178;
            Bool hoisted__Bool_4179 = I64_eq(_forin_err_kind_4169, hoisted__I64_4178);
            (void)hoisted__Bool_4179;
            Bool hoisted__Bool_4180 = not(hoisted__Bool_4179);
            (void)hoisted__Bool_4180;
            if (hoisted__Bool_4180) {
                Type *hoisted__Type_4172 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4172;
                U32 hoisted__U32_4173 = 1;
                (void)hoisted__U32_4173;
                Array *_va_Array_150 = Array_new(hoisted__Type_4172, hoisted__U32_4173);
                (void)_va_Array_150;
                Type_delete(hoisted__Type_4172, 1);
                U32 hoisted__U32_4174 = 0;
                (void)hoisted__U32_4174;
                Str hoisted__Str_4175 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4175;
                Array_set(_va_Array_150, hoisted__U32_4174, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4175; _oa; }));
                Str hoisted__Str_4176 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4176;
                panic(&hoisted__Str_4176, _va_Array_150);
                Str_delete(&hoisted__Str_4176, (Bool){0});
            }
            U32 hoisted__U32_4181 = 1;
            (void)hoisted__U32_4181;
            U32 hoisted__U32_4182 = U32_add(_fi_USize_4169, hoisted__U32_4181);
            (void)hoisted__U32_4182;
            _fi_USize_4169 = hoisted__U32_4182;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4169, 1);
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
    Str hoisted__Str_4436 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4436;
    I64 hoisted__I64_4437 = 3;
    (void)hoisted__I64_4437;
    assert_eq(&hoisted__Str_4436, result, hoisted__I64_4437);
    Str_delete(&hoisted__Str_4436, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4444 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4444;
    I64 hoisted__I64_4445 = 15;
    (void)hoisted__I64_4445;
    assert_eq(&hoisted__Str_4444, result, hoisted__I64_4445);
    Str_delete(&hoisted__Str_4444, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4452 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4452;
    I64 hoisted__I64_4453 = 26;
    (void)hoisted__I64_4453;
    assert_eq(&hoisted__Str_4452, result, hoisted__I64_4453);
    Str_delete(&hoisted__Str_4452, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4456 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4456;
    Str hoisted__Str_4457 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4457;
    assert_eq_str(&hoisted__Str_4456, &result, &hoisted__Str_4457);
    Str_delete(&hoisted__Str_4456, (Bool){0});
    Str_delete(&hoisted__Str_4457, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4788 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4788;
    assert_eq_str(&hoisted__Str_4788, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4788, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4789 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4789;
    assert_eq_str(&hoisted__Str_4789, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4789, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4791 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4791;
    I64 hoisted__I64_4792 = 8;
    (void)hoisted__I64_4792;
    assert_eq(&hoisted__Str_4791, result, hoisted__I64_4792);
    Str_delete(&hoisted__Str_4791, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4795 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4795;
    Bool hoisted__Bool_4796 = 1;
    (void)hoisted__Bool_4796;
    assert(&hoisted__Str_4795, hoisted__Bool_4796);
    Str_delete(&hoisted__Str_4795, (Bool){0});
    Str hoisted__Str_4799 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4799;
    Bool hoisted__Bool_4800 = 1;
    (void)hoisted__Bool_4800;
    assert(&hoisted__Str_4799, hoisted__Bool_4800);
    Str_delete(&hoisted__Str_4799, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4805 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4805;
    Str hoisted__Str_4806 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4806;
    Str hoisted__Str_4807 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4807;
    assert_eq_str(&hoisted__Str_4805, &hoisted__Str_4806, &hoisted__Str_4807);
    Str_delete(&hoisted__Str_4805, (Bool){0});
    Str_delete(&hoisted__Str_4806, (Bool){0});
    Str_delete(&hoisted__Str_4807, (Bool){0});
    Str hoisted__Str_4810 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4810;
    Str hoisted__Str_4811 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4811;
    Str hoisted__Str_4812 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4812;
    assert_eq_str(&hoisted__Str_4810, &hoisted__Str_4811, &hoisted__Str_4812);
    Str_delete(&hoisted__Str_4810, (Bool){0});
    Str_delete(&hoisted__Str_4811, (Bool){0});
    Str_delete(&hoisted__Str_4812, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4817 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4817;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4817;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4818 = 16;
    (void)hoisted__U32_4818;
    return hoisted__U32_4818;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4819 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4819;
    I64 hoisted__I64_4820 = 42;
    (void)hoisted__I64_4820;
    assert_eq(&hoisted__Str_4819, v.x, hoisted__I64_4820);
    Str_delete(&hoisted__Str_4819, (Bool){0});
    Str hoisted__Str_4821 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4821;
    I64 hoisted__I64_4822 = 99;
    (void)hoisted__I64_4822;
    assert_eq(&hoisted__Str_4821, v.y, hoisted__I64_4822);
    Str_delete(&hoisted__Str_4821, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4825 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4825;
    I64 hoisted__I64_4826 = 10;
    (void)hoisted__I64_4826;
    assert_eq(&hoisted__Str_4825, p.x, hoisted__I64_4826);
    Str_delete(&hoisted__Str_4825, (Bool){0});
    Str hoisted__Str_4827 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4827;
    I64 hoisted__I64_4828 = 20;
    (void)hoisted__I64_4828;
    assert_eq(&hoisted__Str_4827, p.y, hoisted__I64_4828);
    Str_delete(&hoisted__Str_4827, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4834 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4834;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4834;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4835 = 32;
    (void)hoisted__U32_4835;
    return hoisted__U32_4835;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4836 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4836;
    I64 hoisted__I64_4837 = 5;
    (void)hoisted__I64_4837;
    assert_eq(&hoisted__Str_4836, r.top_left.x, hoisted__I64_4837);
    Str_delete(&hoisted__Str_4836, (Bool){0});
    Str hoisted__Str_4838 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4838;
    I64 hoisted__I64_4839 = 10;
    (void)hoisted__I64_4839;
    assert_eq(&hoisted__Str_4838, r.top_left.y, hoisted__I64_4839);
    Str_delete(&hoisted__Str_4838, (Bool){0});
    Str hoisted__Str_4840 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4840;
    I64 hoisted__I64_4841 = 100;
    (void)hoisted__I64_4841;
    assert_eq(&hoisted__Str_4840, r.bottom_right.x, hoisted__I64_4841);
    Str_delete(&hoisted__Str_4840, (Bool){0});
    Str hoisted__Str_4842 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4842;
    I64 hoisted__I64_4843 = 200;
    (void)hoisted__I64_4843;
    assert_eq(&hoisted__Str_4842, r.bottom_right.y, hoisted__I64_4843);
    Str_delete(&hoisted__Str_4842, (Bool){0});
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
    Bool hoisted__Bool_4848 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4848;
    if (hoisted__Bool_4848) {
        Bool hoisted__Bool_4845 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4845;
        { Bool _ret_val = hoisted__Bool_4845;
                return _ret_val; }
    }
    Bool hoisted__Bool_4849 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4849;
    if (hoisted__Bool_4849) {
        Bool hoisted__Bool_4846 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4846;
        { Bool _ret_val = hoisted__Bool_4846;
                return _ret_val; }
    }
    Bool hoisted__Bool_4850 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4850;
    if (hoisted__Bool_4850) {
        Bool hoisted__Bool_4847 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4847;
        { Bool _ret_val = hoisted__Bool_4847;
                return _ret_val; }
    }
    Bool hoisted__Bool_4851 = 0;
    (void)hoisted__Bool_4851;
    return hoisted__Bool_4851;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4859 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4859;
    if (hoisted__Bool_4859) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4860 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4860;
    if (hoisted__Bool_4860) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4861 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4861;
    if (hoisted__Bool_4861) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4862 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4862;
    UNREACHABLE(&hoisted__Str_4862);
    Str_delete(&hoisted__Str_4862, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4863 = 4;
    (void)hoisted__U32_4863;
    return hoisted__U32_4863;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_4864 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4864;
    Bool hoisted__Bool_4865 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4865;
    assert(&hoisted__Str_4864, hoisted__Bool_4865);
    Str_delete(&hoisted__Str_4864, (Bool){0});
    Bool hoisted__Bool_4866 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4866;
    Color_delete(&c, 0);
    Str hoisted__Str_4867 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4867;
    Bool hoisted__Bool_4868 = not(hoisted__Bool_4866);
    (void)hoisted__Bool_4868;
    assert(&hoisted__Str_4867, hoisted__Bool_4868);
    Str_delete(&hoisted__Str_4867, (Bool){0});
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
    Bool hoisted__Bool_4869 = is(self, other);
    (void)hoisted__Bool_4869;
    return hoisted__Bool_4869;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_4887 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4887;
    if (hoisted__Bool_4887) {
        I64 *hoisted__I64_4883 = get_payload(self);
        (void)hoisted__I64_4883;
        (void)hoisted__I64_4883;
        Bool hoisted__Bool_4884 = 0;
        (void)hoisted__Bool_4884;
        I64_delete(hoisted__I64_4883, hoisted__Bool_4884);
    }
    Bool hoisted__Bool_4888 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4888;
    if (hoisted__Bool_4888) {
        Str *hoisted__Str_4885 = get_payload(self);
        (void)hoisted__Str_4885;
        (void)hoisted__Str_4885;
        Bool hoisted__Bool_4886 = 0;
        (void)hoisted__Bool_4886;
        Str_delete(hoisted__Str_4885, hoisted__Bool_4886);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4917 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4917;
    if (hoisted__Bool_4917) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4914 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4914;
        { Token * _ret_val = hoisted__Token_4914;
                return _ret_val; }
    }
    Bool hoisted__Bool_4918 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4918;
    if (hoisted__Bool_4918) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4915 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4915;
        Token *hoisted__Token_4916 = Token_Name(hoisted__Str_4915);
        (void)hoisted__Token_4916;
        { Token * _ret_val = hoisted__Token_4916;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4919 = 24;
    (void)hoisted__U32_4919;
    return hoisted__U32_4919;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_4921 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4921;
    Bool hoisted__Bool_4922 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4922;
    assert(&hoisted__Str_4921, hoisted__Bool_4922);
    Str_delete(&hoisted__Str_4921, (Bool){0});
    Bool hoisted__Bool_4923 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4923;
    Token_delete(t, 1);
    Str hoisted__Str_4924 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4924;
    Bool hoisted__Bool_4925 = not(hoisted__Bool_4923);
    (void)hoisted__Bool_4925;
    assert(&hoisted__Str_4924, hoisted__Bool_4925);
    Str_delete(&hoisted__Str_4924, (Bool){0});
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_4926 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4926;
    Bool hoisted__Bool_4927 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4927;
    assert(&hoisted__Str_4926, hoisted__Bool_4927);
    Str_delete(&hoisted__Str_4926, (Bool){0});
    Bool hoisted__Bool_4928 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4928;
    Color_delete(({ Color *_oa = malloc(sizeof(Color)); *_oa = c; _oa; }), 1);
    Str hoisted__Str_4929 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4929;
    Bool hoisted__Bool_4930 = not(hoisted__Bool_4928);
    (void)hoisted__Bool_4930;
    assert(&hoisted__Str_4929, hoisted__Bool_4930);
    Str_delete(&hoisted__Str_4929, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_4933 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4933;
    Bool hoisted__Bool_4934 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4934;
    assert(&hoisted__Str_4933, hoisted__Bool_4934);
    Str_delete(&hoisted__Str_4933, (Bool){0});
    Bool hoisted__Bool_4935 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4935;
    Token_delete(t, 1);
    Str hoisted__Str_4936 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4936;
    Bool hoisted__Bool_4937 = not(hoisted__Bool_4935);
    (void)hoisted__Bool_4937;
    assert(&hoisted__Str_4936, hoisted__Bool_4937);
    Str_delete(&hoisted__Str_4936, (Bool){0});
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
