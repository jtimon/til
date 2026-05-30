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
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
Bool U32_lt(U32 a, U32 b);
Bool U32_gt(U32 a, U32 b);
Bool U32_lte(U32 a, U32 b);
Bool U32_gte(U32 a, U32 b);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
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
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U32 OutOfBounds_size(void);
U32 Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool _cf);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
Bool I64_lt(I64 a, I64 b);
Bool I64_gt(I64 a, I64 b);
Bool I64_neq(I64 a, I64 b);
I64 Bool_cmp(Bool a, Bool b);
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

void F32_delete(F32 * self, Bool call_free);
U32 F32_size(void);
void U64_delete(U64 * self, Bool call_free);
U32 U64_size(void);
Str * U32_to_str(U32 val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool call_free);
U32 U32_size(void);
Bool U32_lt(U32 a, U32 b);
Bool U32_gt(U32 a, U32 b);
Bool U32_lte(U32 a, U32 b);
Bool U32_gte(U32 a, U32 b);
void I32_delete(I32 * self, Bool call_free);
U32 I32_size(void);
void I8_delete(I8 * self, Bool call_free);
U32 I8_size(void);
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
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U32 OutOfBounds_size(void);
U32 Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool _cf);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
U32 I64_size(void);
Bool I64_lt(I64 a, I64 b);
Bool I64_gt(I64 a, I64 b);
Bool I64_neq(I64 a, I64 b);
I64 Bool_cmp(Bool a, Bool b);
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

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U64_size(void) {
    U32 hoisted__U32_35 = 8;
    (void)hoisted__U32_35;
    return hoisted__U32_35;
}

Str * U32_to_str(U32 val) {
    I64 hoisted__I64_123 = U32_to_i64(val);
    (void)hoisted__I64_123;
    Str *hoisted__Str_124 = I64_to_str(hoisted__I64_123);
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

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U32_size(void) {
    U32 hoisted__U32_135 = 4;
    (void)hoisted__U32_135;
    return hoisted__U32_135;
}

Bool U32_lt(U32 a, U32 b) {
    I64 hoisted__I64_211 = U32_cmp(a, b);
    (void)hoisted__I64_211;
    I64 hoisted__I64_212 = -1;
    (void)hoisted__I64_212;
    Bool hoisted__Bool_213 = I64_eq(hoisted__I64_211, hoisted__I64_212);
    (void)hoisted__Bool_213;
    return hoisted__Bool_213;
}

Bool U32_gt(U32 a, U32 b) {
    I64 hoisted__I64_214 = U32_cmp(a, b);
    (void)hoisted__I64_214;
    I64 hoisted__I64_215 = 1;
    (void)hoisted__I64_215;
    Bool hoisted__Bool_216 = I64_eq(hoisted__I64_214, hoisted__I64_215);
    (void)hoisted__Bool_216;
    return hoisted__Bool_216;
}

Bool U32_lte(U32 a, U32 b) {
    Bool hoisted__Bool_219 = U32_gt(a, b);
    (void)hoisted__Bool_219;
    Bool hoisted__Bool_220 = not(hoisted__Bool_219);
    (void)hoisted__Bool_220;
    return hoisted__Bool_220;
}

Bool U32_gte(U32 a, U32 b) {
    Bool hoisted__Bool_221 = U32_lt(a, b);
    (void)hoisted__Bool_221;
    Bool hoisted__Bool_222 = not(hoisted__Bool_221);
    (void)hoisted__Bool_222;
    return hoisted__Bool_222;
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I32_size(void) {
    U32 hoisted__U32_247 = 4;
    (void)hoisted__U32_247;
    return hoisted__U32_247;
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I8_size(void) {
    U32 hoisted__U32_412 = 1;
    (void)hoisted__U32_412;
    return hoisted__U32_412;
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 U8_size(void) {
    U32 hoisted__U32_439 = 1;
    (void)hoisted__U32_439;
    return hoisted__U32_439;
}

Str * format(Array * parts) {
    U32 total = 0;
    {
        Array *_fc_Array_801 = parts;
        (void)_fc_Array_801;
        (void)_fc_Array_801;
        U32 _fi_USize_801 = 0;
        (void)_fi_USize_801;
        I64 _forin_err_kind_801 = 0;
        (void)_forin_err_kind_801;
        OutOfBounds *_forin_OutOfBounds_801 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_801->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_801;
        while (1) {
            U32 hoisted__U32_809 = Array_len(_fc_Array_801);
            (void)hoisted__U32_809;
            Bool _wcond_Bool_802 = U32_lt(_fi_USize_801, hoisted__U32_809);
            (void)_wcond_Bool_802;
            if (_wcond_Bool_802) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_801, &_fi_USize_801, &_forin_err_kind_801, _forin_OutOfBounds_801);
            I64 hoisted__I64_810 = 0;
            (void)hoisted__I64_810;
            Bool hoisted__Bool_811 = I64_eq(_forin_err_kind_801, hoisted__I64_810);
            (void)hoisted__Bool_811;
            Bool hoisted__Bool_812 = not(hoisted__Bool_811);
            (void)hoisted__Bool_812;
            if (hoisted__Bool_812) {
                Type *hoisted__Type_804 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_804;
                U32 hoisted__U32_805 = 1;
                (void)hoisted__U32_805;
                Array *_va_Array_24 = Array_new(hoisted__Type_804, hoisted__U32_805);
                (void)_va_Array_24;
                Type_delete(hoisted__Type_804, 1);
                U32 hoisted__U32_806 = 0;
                (void)hoisted__U32_806;
                Str hoisted__Str_807 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_807;
                Array_set(_va_Array_24, hoisted__U32_806, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_807; _oa; }));
                Str hoisted__Str_808 = (Str){.c_str = (void *)"./src/core/str.til:18:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_808;
                panic(&hoisted__Str_808, _va_Array_24);
                Str_delete(&hoisted__Str_808, (Bool){0});
            }
            U32 hoisted__U32_813 = 1;
            (void)hoisted__U32_813;
            U32 hoisted__U32_814 = U32_add(_fi_USize_801, hoisted__U32_813);
            (void)hoisted__U32_814;
            _fi_USize_801 = hoisted__U32_814;
            U32 hoisted__U32_815 = Str_len(s);
            (void)hoisted__U32_815;
            U32 hoisted__U32_816 = U32_add(total, hoisted__U32_815);
            (void)hoisted__U32_816;
            total = hoisted__U32_816;
        }
        OutOfBounds_delete(_forin_OutOfBounds_801, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array *_fc_Array_817 = parts;
        (void)_fc_Array_817;
        (void)_fc_Array_817;
        U32 _fi_USize_817 = 0;
        (void)_fi_USize_817;
        I64 _forin_err_kind_817 = 0;
        (void)_forin_err_kind_817;
        OutOfBounds *_forin_OutOfBounds_817 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_817->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_817;
        while (1) {
            U32 hoisted__U32_825 = Array_len(_fc_Array_817);
            (void)hoisted__U32_825;
            Bool _wcond_Bool_818 = U32_lt(_fi_USize_817, hoisted__U32_825);
            (void)_wcond_Bool_818;
            if (_wcond_Bool_818) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_817, &_fi_USize_817, &_forin_err_kind_817, _forin_OutOfBounds_817);
            I64 hoisted__I64_826 = 0;
            (void)hoisted__I64_826;
            Bool hoisted__Bool_827 = I64_eq(_forin_err_kind_817, hoisted__I64_826);
            (void)hoisted__Bool_827;
            Bool hoisted__Bool_828 = not(hoisted__Bool_827);
            (void)hoisted__Bool_828;
            if (hoisted__Bool_828) {
                Type *hoisted__Type_820 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_820;
                U32 hoisted__U32_821 = 1;
                (void)hoisted__U32_821;
                Array *_va_Array_25 = Array_new(hoisted__Type_820, hoisted__U32_821);
                (void)_va_Array_25;
                Type_delete(hoisted__Type_820, 1);
                U32 hoisted__U32_822 = 0;
                (void)hoisted__U32_822;
                Str hoisted__Str_823 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_823;
                Array_set(_va_Array_25, hoisted__U32_822, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_823; _oa; }));
                Str hoisted__Str_824 = (Str){.c_str = (void *)"./src/core/str.til:22:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_824;
                panic(&hoisted__Str_824, _va_Array_25);
                Str_delete(&hoisted__Str_824, (Bool){0});
            }
            U32 hoisted__U32_829 = 1;
            (void)hoisted__U32_829;
            U32 hoisted__U32_830 = U32_add(_fi_USize_817, hoisted__U32_829);
            (void)hoisted__U32_830;
            _fi_USize_817 = hoisted__U32_830;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_817, 1);
    }
    Array_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_837 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_837;
    if (hoisted__Bool_837) {
        Type *hoisted__Type_832 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_832;
        U32 hoisted__U32_833 = 1;
        (void)hoisted__U32_833;
        Array *_va_Array_26 = Array_new(hoisted__Type_832, hoisted__U32_833);
        (void)_va_Array_26;
        Type_delete(hoisted__Type_832, 1);
        U32 hoisted__U32_834 = 0;
        (void)hoisted__U32_834;
        Str hoisted__Str_835 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_835;
        Array_set(_va_Array_26, hoisted__U32_834, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_835; _oa; }));
        Str hoisted__Str_836 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_836;
        panic(&hoisted__Str_836, _va_Array_26);
        Str_delete(&hoisted__Str_836, (Bool){0});
    }
    void *hoisted__v_838 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_838;
    (void)hoisted__v_838;
    return hoisted__v_838;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_848 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_848;
    if (hoisted__Bool_848) {
        min_len = b->count;
    }
    {
        U32 _re_U32_840 = U32_clone(&min_len);
        (void)_re_U32_840;
        U32 _rc_U32_840 = 0;
        (void)_rc_U32_840;
        Bool hoisted__Bool_847 = U32_lte(_rc_U32_840, _re_U32_840);
        (void)hoisted__Bool_847;
        if (hoisted__Bool_847) {
            while (1) {
                Bool _wcond_Bool_841 = U32_lt(_rc_U32_840, _re_U32_840);
                (void)_wcond_Bool_841;
                if (_wcond_Bool_841) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_840);
                U32_inc(&_rc_U32_840);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_842 = 0;
                (void)hoisted__I64_842;
                Bool hoisted__Bool_843 = I64_neq(c, hoisted__I64_842);
                (void)hoisted__Bool_843;
                if (hoisted__Bool_843) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_844 = U32_gt(_rc_U32_840, _re_U32_840);
                (void)_wcond_Bool_844;
                if (_wcond_Bool_844) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_840);
                U32_dec(&_rc_U32_840);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_845 = 0;
                (void)hoisted__I64_845;
                Bool hoisted__Bool_846 = I64_neq(c, hoisted__I64_845);
                (void)hoisted__Bool_846;
                if (hoisted__Bool_846) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_849 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_849;
    return hoisted__I64_849;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_851 = 1;
    (void)hoisted__U32_851;
    U32 hoisted__U64_852 = U32_add(n, hoisted__U32_851);
    (void)hoisted__U64_852;
    void * buf = malloc(hoisted__U64_852);
    I32 hoisted__I32_853 = 0;
    (void)hoisted__I32_853;
    U64 hoisted__U64_854 = 1ULL;
    (void)hoisted__U64_854;
    memset(buf, hoisted__I32_853, hoisted__U64_854);
    I32_delete(&hoisted__I32_853, 0);
    I64 hoisted__I64_855 = 0;
    (void)hoisted__I64_855;
    Str *hoisted__Str_856 = malloc(sizeof(Str));
    hoisted__Str_856->c_str = buf;
    hoisted__Str_856->count = hoisted__I64_855;
    hoisted__Str_856->cap = n;
    (void)hoisted__Str_856;
    return hoisted__Str_856;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_871 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_871;
    if (hoisted__Bool_871) {
        Type *hoisted__Type_860 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_860;
        U32 hoisted__U32_861 = 1;
        (void)hoisted__U32_861;
        Array *_va_Array_27 = Array_new(hoisted__Type_860, hoisted__U32_861);
        (void)_va_Array_27;
        Type_delete(hoisted__Type_860, 1);
        U32 hoisted__U32_862 = 0;
        (void)hoisted__U32_862;
        Str hoisted__Str_863 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_863;
        Array_set(_va_Array_27, hoisted__U32_862, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_863; _oa; }));
        Str hoisted__Str_864 = (Str){.c_str = (void *)"./src/core/str.til:91:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_864;
        panic(&hoisted__Str_864, _va_Array_27);
        Str_delete(&hoisted__Str_864, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_872 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_872;
    if (hoisted__Bool_872) {
        Type *hoisted__Type_866 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_866;
        U32 hoisted__U32_867 = 1;
        (void)hoisted__U32_867;
        Array *_va_Array_28 = Array_new(hoisted__Type_866, hoisted__U32_867);
        (void)_va_Array_28;
        Type_delete(hoisted__Type_866, 1);
        U32 hoisted__U32_868 = 0;
        (void)hoisted__U32_868;
        Str hoisted__Str_869 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_869;
        Array_set(_va_Array_28, hoisted__U32_868, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_869; _oa; }));
        Str hoisted__Str_870 = (Str){.c_str = (void *)"./src/core/str.til:95:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_870;
        panic(&hoisted__Str_870, _va_Array_28);
        Str_delete(&hoisted__Str_870, (Bool){0});
    }
    void *hoisted__v_873 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_873;
    (void)hoisted__v_873;
    memcpy(hoisted__v_873, s->c_str, s->count);
    U32 hoisted__U32_874 = U32_clone(&new_len);
    (void)hoisted__U32_874;
    self->count = hoisted__U32_874;
    void *hoisted__v_875 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_875;
    (void)hoisted__v_875;
    I32 hoisted__I32_876 = 0;
    (void)hoisted__I32_876;
    U64 hoisted__U64_877 = 1ULL;
    (void)hoisted__U64_877;
    memset(hoisted__v_875, hoisted__I32_876, hoisted__U64_877);
    I32_delete(&hoisted__I32_876, 0);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_878 = 1;
    (void)hoisted__U32_878;
    U32 hoisted__U64_879 = U32_add(val->count, hoisted__U32_878);
    (void)hoisted__U64_879;
    void * new_data = malloc(hoisted__U64_879);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_880 = ptr_add(new_data, val->count);
    (void)hoisted__v_880;
    (void)hoisted__v_880;
    I32 hoisted__I32_881 = 0;
    (void)hoisted__I32_881;
    U64 hoisted__U64_882 = 1ULL;
    (void)hoisted__U64_882;
    memset(hoisted__v_880, hoisted__I32_881, hoisted__U64_882);
    I32_delete(&hoisted__I32_881, 0);
    Str *hoisted__Str_883 = malloc(sizeof(Str));
    hoisted__Str_883->c_str = new_data;
    hoisted__Str_883->count = val->count;
    hoisted__Str_883->cap = val->count;
    (void)hoisted__Str_883;
    return hoisted__Str_883;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_884 = U32_lt(self->cap, CAP_VIEW);
    (void)hoisted__Bool_884;
    if (hoisted__Bool_884) {
        free(self->c_str);
    }
    if (call_free) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_997 = 0;
    (void)hoisted__U32_997;
    Bool hoisted__Bool_998 = U32_eq(self->count, hoisted__U32_997);
    (void)hoisted__Bool_998;
    return hoisted__Bool_998;
}

U32 Str_size(void) {
    U32 hoisted__U32_1229 = 16;
    (void)hoisted__U32_1229;
    return hoisted__U32_1229;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1230 = Str_cmp(a, b);
    (void)hoisted__I64_1230;
    I64 hoisted__I64_1231 = 0;
    (void)hoisted__I64_1231;
    Bool hoisted__Bool_1232 = I64_eq(hoisted__I64_1230, hoisted__I64_1231);
    (void)hoisted__Bool_1232;
    return hoisted__Bool_1232;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1303 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1303->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1303;
    return hoisted__OutOfBounds_1303;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1304 = 0;
    (void)hoisted__Bool_1304;
    Str_delete(&self->msg, hoisted__Bool_1304);
    if (call_free) {
        free(self);
    }
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1305 = 16;
    (void)hoisted__U32_1305;
    return hoisted__U32_1305;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1308 = 8;
    (void)hoisted__U32_1308;
    return hoisted__U32_1308;
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
        I32_delete(&hoisted__I32_1481, 0);
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
        U8_delete(&hoisted__U8_1506, 0);
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
    I32_delete(&hoisted__I32_1520, 0);
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
    U32 hoisted__U32_1540 = 8;
    (void)hoisted__U32_1540;
    return hoisted__U32_1540;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1673 = I64_cmp(a, b);
    (void)hoisted__I64_1673;
    I64 hoisted__I64_1674 = -1;
    (void)hoisted__I64_1674;
    Bool hoisted__Bool_1675 = I64_eq(hoisted__I64_1673, hoisted__I64_1674);
    (void)hoisted__Bool_1675;
    return hoisted__Bool_1675;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1676 = I64_cmp(a, b);
    (void)hoisted__I64_1676;
    I64 hoisted__I64_1677 = 1;
    (void)hoisted__I64_1677;
    Bool hoisted__Bool_1678 = I64_eq(hoisted__I64_1676, hoisted__I64_1677);
    (void)hoisted__Bool_1678;
    return hoisted__Bool_1678;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1679 = I64_eq(a, b);
    (void)hoisted__Bool_1679;
    Bool hoisted__Bool_1680 = not(hoisted__Bool_1679);
    (void)hoisted__Bool_1680;
    return hoisted__Bool_1680;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1694 = Bool_eq(a, b);
    (void)hoisted__Bool_1694;
    if (hoisted__Bool_1694) {
        I64 hoisted__I64_1692 = 0;
        (void)hoisted__I64_1692;
        { I64 _ret_val = hoisted__I64_1692;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1693 = -1;
        (void)hoisted__I64_1693;
        return hoisted__I64_1693;
    }
    I64 hoisted__I64_1695 = 1;
    (void)hoisted__I64_1695;
    return hoisted__I64_1695;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1696 = 1;
    (void)hoisted__U32_1696;
    return hoisted__U32_1696;
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
    Bool hoisted__Bool_1837 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1837;
    if (hoisted__Bool_1837) {
        Bool hoisted__Bool_1835 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1835;
        { Bool _ret_val = hoisted__Bool_1835;
                return _ret_val; }
    }
    Bool hoisted__Bool_1838 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1838;
    if (hoisted__Bool_1838) {
        Bool hoisted__Bool_1836 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1836;
        { Bool _ret_val = hoisted__Bool_1836;
                return _ret_val; }
    }
    Bool hoisted__Bool_1839 = 0;
    (void)hoisted__Bool_1839;
    return hoisted__Bool_1839;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1845 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1845;
    if (hoisted__Bool_1845) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1846 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1846;
    if (hoisted__Bool_1846) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Str hoisted__Str_1847 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1847;
    UNREACHABLE(&hoisted__Str_1847);
    Str_delete(&hoisted__Str_1847, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1848 = 4;
    (void)hoisted__U32_1848;
    return hoisted__U32_1848;
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
    Bool hoisted__Bool_1911 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1911;
    if (hoisted__Bool_1911) {
        Str *hoisted__Str_1903 = get_payload(self);
        (void)hoisted__Str_1903;
        (void)hoisted__Str_1903;
        Bool hoisted__Bool_1904 = 0;
        (void)hoisted__Bool_1904;
        Str_delete(hoisted__Str_1903, hoisted__Bool_1904);
    }
    Bool hoisted__Bool_1912 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1912;
    if (hoisted__Bool_1912) {
        Str *hoisted__Str_1905 = get_payload(self);
        (void)hoisted__Str_1905;
        (void)hoisted__Str_1905;
        Bool hoisted__Bool_1906 = 0;
        (void)hoisted__Bool_1906;
        Str_delete(hoisted__Str_1905, hoisted__Bool_1906);
    }
    Bool hoisted__Bool_1913 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1913;
    if (hoisted__Bool_1913) {
        Str *hoisted__Str_1907 = get_payload(self);
        (void)hoisted__Str_1907;
        (void)hoisted__Str_1907;
        Bool hoisted__Bool_1908 = 0;
        (void)hoisted__Bool_1908;
        Str_delete(hoisted__Str_1907, hoisted__Bool_1908);
    }
    Bool hoisted__Bool_1914 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1914;
    if (hoisted__Bool_1914) {
        Primitive *hoisted__Primitive_1909 = get_payload(self);
        (void)hoisted__Primitive_1909;
        (void)hoisted__Primitive_1909;
        Bool hoisted__Bool_1910 = 0;
        (void)hoisted__Bool_1910;
        Primitive_delete(hoisted__Primitive_1909, hoisted__Bool_1910);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1996 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_1996;
    if (hoisted__Bool_1996) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_1997 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_1997;
    if (hoisted__Bool_1997) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_1998 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)hoisted__Bool_1998;
    if (hoisted__Bool_1998) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1999 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)hoisted__Bool_1999;
    if (hoisted__Bool_1999) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_2000 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)hoisted__Bool_2000;
    if (hoisted__Bool_2000) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_2001 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)hoisted__Bool_2001;
    if (hoisted__Bool_2001) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_2002 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)hoisted__Bool_2002;
    if (hoisted__Bool_2002) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_2003 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)hoisted__Bool_2003;
    if (hoisted__Bool_2003) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_2004 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)hoisted__Bool_2004;
    if (hoisted__Bool_2004) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool;
                return _r; }
    }
    Bool hoisted__Bool_2005 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2005;
    if (hoisted__Bool_2005) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_1990 = Str_clone(_clone_payload_Struct_9);
        (void)hoisted__Str_1990;
        Type *hoisted__Type_1991 = Type_Struct(hoisted__Str_1990);
        (void)hoisted__Type_1991;
        { Type * _ret_val = hoisted__Type_1991;
                return _ret_val; }
    }
    Bool hoisted__Bool_2006 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2006;
    if (hoisted__Bool_2006) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2007 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2007;
    if (hoisted__Bool_2007) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_1992 = Str_clone(_clone_payload_Enum_11);
        (void)hoisted__Str_1992;
        Type *hoisted__Type_1993 = Type_Enum(hoisted__Str_1992);
        (void)hoisted__Type_1993;
        { Type * _ret_val = hoisted__Type_1993;
                return _ret_val; }
    }
    Bool hoisted__Bool_2008 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2008;
    if (hoisted__Bool_2008) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2009 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2009;
    if (hoisted__Bool_2009) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2010 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2010;
    if (hoisted__Bool_2010) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2011 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2011;
    if (hoisted__Bool_2011) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2012 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2012;
    if (hoisted__Bool_2012) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_1994 = Str_clone(_clone_payload_Custom_16);
        (void)hoisted__Str_1994;
        Type *hoisted__Type_1995 = Type_Custom(hoisted__Str_1994);
        (void)hoisted__Type_1995;
        { Type * _ret_val = hoisted__Type_1995;
                return _ret_val; }
    }
    Bool hoisted__Bool_2013 = is(self, &(Type){.tag = Type_TAG_I8});
    (void)hoisted__Bool_2013;
    if (hoisted__Bool_2013) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8;
                return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive hoisted__Primitive_2014 = DEREF(_clone_payload_Primitive_18);
    (void)hoisted__Primitive_2014;
    Type *hoisted__Type_2015 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2014; _oa; }));
    (void)hoisted__Type_2015;
    return hoisted__Type_2015;
}

U32 Type_size(void) {
    U32 hoisted__U32_2016 = 24;
    (void)hoisted__U32_2016;
    return hoisted__U32_2016;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3667 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3667;
    if (hoisted__Bool_3667) {
        Type *hoisted__Type_3662 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3662;
        U32 hoisted__U32_3663 = 1;
        (void)hoisted__U32_3663;
        Array *_va_Array_112 = Array_new(hoisted__Type_3662, hoisted__U32_3663);
        (void)_va_Array_112;
        Type_delete(hoisted__Type_3662, 1);
        U32 hoisted__U32_3664 = 0;
        (void)hoisted__U32_3664;
        Str hoisted__Str_3665 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3665;
        Array_set(_va_Array_112, hoisted__U32_3664, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3665; _oa; }));
        Str hoisted__Str_3666 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3666;
        panic(&hoisted__Str_3666, _va_Array_112);
        Str_delete(&hoisted__Str_3666, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3668 = calloc(cap, elem_size);
    (void)hoisted__v_3668;
    void * hoisted__v_3669 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3669;
    void * hoisted__v_3670 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3670;
    Array *hoisted__Array_3671 = malloc(sizeof(Array));
    hoisted__Array_3671->data = hoisted__v_3668;
    hoisted__Array_3671->cap = cap;
    hoisted__Array_3671->elem_size = elem_size;
    hoisted__Array_3671->elem_clone = hoisted__v_3669;
    hoisted__Array_3671->elem_delete = hoisted__v_3670;
    (void)hoisted__Array_3671;
    return hoisted__Array_3671;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3672 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3672;
    Str_delete(elem_type, 1);
    return hoisted__Array_3672;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3693 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3693;
    if (hoisted__Bool_3693) {
        Type *hoisted__Type_3674 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3674;
        U32 hoisted__U32_3675 = 6;
        (void)hoisted__U32_3675;
        Array *_va_Array_113 = Array_new(hoisted__Type_3674, hoisted__U32_3675);
        (void)_va_Array_113;
        Type_delete(hoisted__Type_3674, 1);
        U32 hoisted__U32_3676 = 0;
        (void)hoisted__U32_3676;
        Str hoisted__Str_3677 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3677;
        Array_set(_va_Array_113, hoisted__U32_3676, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3677; _oa; }));
        U32 hoisted__U32_3678 = 1;
        (void)hoisted__U32_3678;
        Str hoisted__Str_3679 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3679;
        Array_set(_va_Array_113, hoisted__U32_3678, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3679; _oa; }));
        U32 hoisted__U32_3680 = 2;
        (void)hoisted__U32_3680;
        Str *hoisted__Str_3681 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3681;
        Array_set(_va_Array_113, hoisted__U32_3680, hoisted__Str_3681);
        U32 hoisted__U32_3682 = 3;
        (void)hoisted__U32_3682;
        Str hoisted__Str_3683 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3683;
        Array_set(_va_Array_113, hoisted__U32_3682, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3683; _oa; }));
        U32 hoisted__U32_3684 = 4;
        (void)hoisted__U32_3684;
        Str *hoisted__Str_3685 = U32_to_str(self->cap);
        (void)hoisted__Str_3685;
        Array_set(_va_Array_113, hoisted__U32_3684, hoisted__Str_3685);
        U32 hoisted__U32_3686 = 5;
        (void)hoisted__U32_3686;
        Str hoisted__Str_3687 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3687;
        Array_set(_va_Array_113, hoisted__U32_3686, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3687; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3688 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_113); hoisted__OutOfBounds_3688->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3688;
        U32 hoisted__U32_3689 = 16;
        (void)hoisted__U32_3689;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3688, hoisted__U32_3689);
        OutOfBounds_delete(hoisted__OutOfBounds_3688, 1);
        I64 hoisted__I64_3690 = 3;
        (void)hoisted__I64_3690;
        *_err_kind = hoisted__I64_3690;
    }
    I64 hoisted__I64_3694 = 0;
    (void)hoisted__I64_3694;
    Bool hoisted__Bool_3695 = I64_eq(DEREF(_err_kind), hoisted__I64_3694);
    (void)hoisted__Bool_3695;
    if (hoisted__Bool_3695) {
        U32 hoisted__U64_3691 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3691;
        void *hoisted__v_3692 = ptr_add(self->data, hoisted__U64_3691);
        (void)hoisted__v_3692;
        (void)hoisted__v_3692;
        { void * _ret_val = hoisted__v_3692;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3710 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3710;
    if (hoisted__Bool_3710) {
        Type *hoisted__Type_3697 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3697;
        U32 hoisted__U32_3698 = 5;
        (void)hoisted__U32_3698;
        Array *_va_Array_114 = Array_new(hoisted__Type_3697, hoisted__U32_3698);
        (void)_va_Array_114;
        Type_delete(hoisted__Type_3697, 1);
        U32 hoisted__U32_3699 = 0;
        (void)hoisted__U32_3699;
        Str hoisted__Str_3700 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3700;
        Array_set(_va_Array_114, hoisted__U32_3699, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3700; _oa; }));
        U32 hoisted__U32_3701 = 1;
        (void)hoisted__U32_3701;
        Str *hoisted__Str_3702 = U32_to_str(i);
        (void)hoisted__Str_3702;
        Array_set(_va_Array_114, hoisted__U32_3701, hoisted__Str_3702);
        U32 hoisted__U32_3703 = 2;
        (void)hoisted__U32_3703;
        Str hoisted__Str_3704 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3704;
        Array_set(_va_Array_114, hoisted__U32_3703, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3704; _oa; }));
        U32 hoisted__U32_3705 = 3;
        (void)hoisted__U32_3705;
        Str *hoisted__Str_3706 = U32_to_str(self->cap);
        (void)hoisted__Str_3706;
        Array_set(_va_Array_114, hoisted__U32_3705, hoisted__Str_3706);
        U32 hoisted__U32_3707 = 4;
        (void)hoisted__U32_3707;
        Str hoisted__Str_3708 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3708;
        Array_set(_va_Array_114, hoisted__U32_3707, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3708; _oa; }));
        Str hoisted__Str_3709 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3709;
        panic(&hoisted__Str_3709, _va_Array_114);
        Str_delete(&hoisted__Str_3709, (Bool){0});
    }
    U32 hoisted__U64_3711 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3711;
    void *hoisted__v_3712 = ptr_add(self->data, hoisted__U64_3711);
    (void)hoisted__v_3712;
    (void)hoisted__v_3712;
    Bool hoisted__Bool_3713 = 0;
    (void)hoisted__Bool_3713;
    ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3712, hoisted__Bool_3713);
    U32 hoisted__U64_3714 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3714;
    void *hoisted__v_3715 = ptr_add(self->data, hoisted__U64_3714);
    (void)hoisted__v_3715;
    (void)hoisted__v_3715;
    memcpy(hoisted__v_3715, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3716 = self->cap;
        (void)_re_U32_3716;
        U32 _rc_U32_3716 = 0;
        (void)_rc_U32_3716;
        Bool hoisted__Bool_3725 = U32_lte(_rc_U32_3716, _re_U32_3716);
        (void)hoisted__Bool_3725;
        if (hoisted__Bool_3725) {
            while (1) {
                Bool _wcond_Bool_3717 = U32_lt(_rc_U32_3716, _re_U32_3716);
                (void)_wcond_Bool_3717;
                if (_wcond_Bool_3717) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3716);
                U32_inc(&_rc_U32_3716);
                U32 hoisted__U64_3718 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3718;
                void *hoisted__v_3719 = ptr_add(self->data, hoisted__U64_3718);
                (void)hoisted__v_3719;
                (void)hoisted__v_3719;
                Bool hoisted__Bool_3720 = 0;
                (void)hoisted__Bool_3720;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3719, hoisted__Bool_3720);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3721 = U32_gt(_rc_U32_3716, _re_U32_3716);
                (void)_wcond_Bool_3721;
                if (_wcond_Bool_3721) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3716);
                U32_dec(&_rc_U32_3716);
                U32 hoisted__U64_3722 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3722;
                void *hoisted__v_3723 = ptr_add(self->data, hoisted__U64_3722);
                (void)hoisted__v_3723;
                (void)hoisted__v_3723;
                Bool hoisted__Bool_3724 = 0;
                (void)hoisted__Bool_3724;
                ((void (*)(void *, Bool))(void *)(self->elem_delete))(hoisted__v_3723, hoisted__Bool_3724);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3738 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3738;
    void * new_data = malloc(hoisted__U64_3738);
    {
        U32 _re_U32_3726 = self->cap;
        (void)_re_U32_3726;
        U32 _rc_U32_3726 = 0;
        (void)_rc_U32_3726;
        Bool hoisted__Bool_3737 = U32_lte(_rc_U32_3726, _re_U32_3726);
        (void)hoisted__Bool_3737;
        if (hoisted__Bool_3737) {
            while (1) {
                Bool _wcond_Bool_3727 = U32_lt(_rc_U32_3726, _re_U32_3726);
                (void)_wcond_Bool_3727;
                if (_wcond_Bool_3727) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3726);
                U32_inc(&_rc_U32_3726);
                U32 hoisted__U64_3728 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3728;
                void *hoisted__v_3729 = ptr_add(self->data, hoisted__U64_3728);
                (void)hoisted__v_3729;
                (void)hoisted__v_3729;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3729);
                U32 hoisted__U64_3730 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3730;
                void *hoisted__v_3731 = ptr_add(new_data, hoisted__U64_3730);
                (void)hoisted__v_3731;
                (void)hoisted__v_3731;
                memcpy(hoisted__v_3731, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3732 = U32_gt(_rc_U32_3726, _re_U32_3726);
                (void)_wcond_Bool_3732;
                if (_wcond_Bool_3732) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3726);
                U32_dec(&_rc_U32_3726);
                U32 hoisted__U64_3733 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3733;
                void *hoisted__v_3734 = ptr_add(self->data, hoisted__U64_3733);
                (void)hoisted__v_3734;
                (void)hoisted__v_3734;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3734);
                U32 hoisted__U64_3735 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3735;
                void *hoisted__v_3736 = ptr_add(new_data, hoisted__U64_3735);
                (void)hoisted__v_3736;
                (void)hoisted__v_3736;
                memcpy(hoisted__v_3736, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3739 = malloc(sizeof(Array));
    hoisted__Array_3739->data = new_data;
    hoisted__Array_3739->cap = self->cap;
    hoisted__Array_3739->elem_size = self->elem_size;
    hoisted__Array_3739->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3739->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3739;
    return hoisted__Array_3739;
}

U32 Array_size(void) {
    U32 hoisted__U32_3740 = 32;
    (void)hoisted__U32_3740;
    return hoisted__U32_3740;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4084 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4084;
    U32 hoisted__U32_4085 = 3;
    (void)hoisted__U32_4085;
    Array *_va_Array_143 = Array_new(hoisted__Type_4084, hoisted__U32_4085);
    (void)_va_Array_143;
    Type_delete(hoisted__Type_4084, 1);
    U32 hoisted__U32_4086 = 0;
    (void)hoisted__U32_4086;
    Str *hoisted__Str_4087 = Str_clone(loc_str);
    (void)hoisted__Str_4087;
    Array_set(_va_Array_143, hoisted__U32_4086, hoisted__Str_4087);
    U32 hoisted__U32_4088 = 1;
    (void)hoisted__U32_4088;
    Str hoisted__Str_4089 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4089;
    Array_set(_va_Array_143, hoisted__U32_4088, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4089; _oa; }));
    Array *hoisted__Array_4090 = Array_clone(parts);
    (void)hoisted__Array_4090;
    Array_delete(parts, 1);
    U32 hoisted__U32_4091 = 2;
    (void)hoisted__U32_4091;
    Str *hoisted__Str_4092 = format(hoisted__Array_4090);
    (void)hoisted__Str_4092;
    Array_set(_va_Array_143, hoisted__U32_4091, hoisted__Str_4092);
    println(_va_Array_143);
    I64 hoisted__I64_4093 = 1;
    (void)hoisted__I64_4093;
    exit(hoisted__I64_4093);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4103 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4103;
    U32 hoisted__U32_4104 = 1;
    (void)hoisted__U32_4104;
    Array *_va_Array_145 = Array_new(hoisted__Type_4103, hoisted__U32_4104);
    (void)_va_Array_145;
    Type_delete(hoisted__Type_4103, 1);
    U32 hoisted__U32_4105 = 0;
    (void)hoisted__U32_4105;
    Str hoisted__Str_4106 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4106;
    Array_set(_va_Array_145, hoisted__U32_4105, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4106; _oa; }));
    panic(loc_str, _va_Array_145);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4112 = not(cond);
    (void)hoisted__Bool_4112;
    if (hoisted__Bool_4112) {
        Type *hoisted__Type_4108 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4108;
        U32 hoisted__U32_4109 = 1;
        (void)hoisted__U32_4109;
        Array *_va_Array_146 = Array_new(hoisted__Type_4108, hoisted__U32_4109);
        (void)_va_Array_146;
        Type_delete(hoisted__Type_4108, 1);
        U32 hoisted__U32_4110 = 0;
        (void)hoisted__U32_4110;
        Str hoisted__Str_4111 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4111;
        Array_set(_va_Array_146, hoisted__U32_4110, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4111; _oa; }));
        panic(loc_str, _va_Array_146);
    }
    Bool hoisted__Bool_4113 = 1;
    (void)hoisted__Bool_4113;
    return hoisted__Bool_4113;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4136 = I64_neq(a, b);
    (void)hoisted__Bool_4136;
    if (hoisted__Bool_4136) {
        Type *hoisted__Type_4124 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4124;
        U32 hoisted__U32_4125 = 5;
        (void)hoisted__U32_4125;
        Array *_va_Array_148 = Array_new(hoisted__Type_4124, hoisted__U32_4125);
        (void)_va_Array_148;
        Type_delete(hoisted__Type_4124, 1);
        U32 hoisted__U32_4126 = 0;
        (void)hoisted__U32_4126;
        Str hoisted__Str_4127 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4127;
        Array_set(_va_Array_148, hoisted__U32_4126, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4127; _oa; }));
        U32 hoisted__U32_4128 = 1;
        (void)hoisted__U32_4128;
        Str *hoisted__Str_4129 = I64_to_str(a);
        (void)hoisted__Str_4129;
        Array_set(_va_Array_148, hoisted__U32_4128, hoisted__Str_4129);
        U32 hoisted__U32_4130 = 2;
        (void)hoisted__U32_4130;
        Str hoisted__Str_4131 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4131;
        Array_set(_va_Array_148, hoisted__U32_4130, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4131; _oa; }));
        U32 hoisted__U32_4132 = 3;
        (void)hoisted__U32_4132;
        Str *hoisted__Str_4133 = I64_to_str(b);
        (void)hoisted__Str_4133;
        Array_set(_va_Array_148, hoisted__U32_4132, hoisted__Str_4133);
        U32 hoisted__U32_4134 = 4;
        (void)hoisted__U32_4134;
        Str hoisted__Str_4135 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4135;
        Array_set(_va_Array_148, hoisted__U32_4134, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4135; _oa; }));
        panic(loc_str, _va_Array_148);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4150 = Str_eq(a, b);
    (void)hoisted__Bool_4150;
    Bool hoisted__Bool_4151 = not(hoisted__Bool_4150);
    (void)hoisted__Bool_4151;
    if (hoisted__Bool_4151) {
        Type *hoisted__Type_4138 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4138;
        U32 hoisted__U32_4139 = 5;
        (void)hoisted__U32_4139;
        Array *_va_Array_149 = Array_new(hoisted__Type_4138, hoisted__U32_4139);
        (void)_va_Array_149;
        Type_delete(hoisted__Type_4138, 1);
        U32 hoisted__U32_4140 = 0;
        (void)hoisted__U32_4140;
        Str hoisted__Str_4141 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4141;
        Array_set(_va_Array_149, hoisted__U32_4140, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4141; _oa; }));
        U32 hoisted__U32_4142 = 1;
        (void)hoisted__U32_4142;
        Str *hoisted__Str_4143 = Str_clone(a);
        (void)hoisted__Str_4143;
        Array_set(_va_Array_149, hoisted__U32_4142, hoisted__Str_4143);
        U32 hoisted__U32_4144 = 2;
        (void)hoisted__U32_4144;
        Str hoisted__Str_4145 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4145;
        Array_set(_va_Array_149, hoisted__U32_4144, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4145; _oa; }));
        U32 hoisted__U32_4146 = 3;
        (void)hoisted__U32_4146;
        Str *hoisted__Str_4147 = Str_clone(b);
        (void)hoisted__Str_4147;
        Array_set(_va_Array_149, hoisted__U32_4146, hoisted__Str_4147);
        U32 hoisted__U32_4148 = 4;
        (void)hoisted__U32_4148;
        Str hoisted__Str_4149 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4149;
        Array_set(_va_Array_149, hoisted__U32_4148, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4149; _oa; }));
        panic(loc_str, _va_Array_149);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4152 = parts;
        (void)_fc_Array_4152;
        (void)_fc_Array_4152;
        U32 _fi_USize_4152 = 0;
        (void)_fi_USize_4152;
        I64 _forin_err_kind_4152 = 0;
        (void)_forin_err_kind_4152;
        OutOfBounds *_forin_OutOfBounds_4152 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4152->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4152;
        while (1) {
            U32 hoisted__U32_4160 = Array_len(_fc_Array_4152);
            (void)hoisted__U32_4160;
            Bool _wcond_Bool_4153 = U32_lt(_fi_USize_4152, hoisted__U32_4160);
            (void)_wcond_Bool_4153;
            if (_wcond_Bool_4153) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4152, &_fi_USize_4152, &_forin_err_kind_4152, _forin_OutOfBounds_4152);
            I64 hoisted__I64_4161 = 0;
            (void)hoisted__I64_4161;
            Bool hoisted__Bool_4162 = I64_eq(_forin_err_kind_4152, hoisted__I64_4161);
            (void)hoisted__Bool_4162;
            Bool hoisted__Bool_4163 = not(hoisted__Bool_4162);
            (void)hoisted__Bool_4163;
            if (hoisted__Bool_4163) {
                Type *hoisted__Type_4155 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4155;
                U32 hoisted__U32_4156 = 1;
                (void)hoisted__U32_4156;
                Array *_va_Array_150 = Array_new(hoisted__Type_4155, hoisted__U32_4156);
                (void)_va_Array_150;
                Type_delete(hoisted__Type_4155, 1);
                U32 hoisted__U32_4157 = 0;
                (void)hoisted__U32_4157;
                Str hoisted__Str_4158 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4158;
                Array_set(_va_Array_150, hoisted__U32_4157, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4158; _oa; }));
                Str hoisted__Str_4159 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4159;
                panic(&hoisted__Str_4159, _va_Array_150);
                Str_delete(&hoisted__Str_4159, (Bool){0});
            }
            U32 hoisted__U32_4164 = 1;
            (void)hoisted__U32_4164;
            U32 hoisted__U32_4165 = U32_add(_fi_USize_4152, hoisted__U32_4164);
            (void)hoisted__U32_4165;
            _fi_USize_4152 = hoisted__U32_4165;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4152, 1);
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
    Str hoisted__Str_4416 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4416;
    I64 hoisted__I64_4417 = 3;
    (void)hoisted__I64_4417;
    assert_eq(&hoisted__Str_4416, result, hoisted__I64_4417);
    Str_delete(&hoisted__Str_4416, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4424 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4424;
    I64 hoisted__I64_4425 = 15;
    (void)hoisted__I64_4425;
    assert_eq(&hoisted__Str_4424, result, hoisted__I64_4425);
    Str_delete(&hoisted__Str_4424, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4432 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4432;
    I64 hoisted__I64_4433 = 26;
    (void)hoisted__I64_4433;
    assert_eq(&hoisted__Str_4432, result, hoisted__I64_4433);
    Str_delete(&hoisted__Str_4432, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4436 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4436;
    Str hoisted__Str_4437 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4437;
    assert_eq_str(&hoisted__Str_4436, &result, &hoisted__Str_4437);
    Str_delete(&hoisted__Str_4436, (Bool){0});
    Str_delete(&hoisted__Str_4437, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4768 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4768;
    assert_eq_str(&hoisted__Str_4768, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4768, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4769 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4769;
    assert_eq_str(&hoisted__Str_4769, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4769, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4771 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4771;
    I64 hoisted__I64_4772 = 8;
    (void)hoisted__I64_4772;
    assert_eq(&hoisted__Str_4771, result, hoisted__I64_4772);
    Str_delete(&hoisted__Str_4771, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4775 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4775;
    Bool hoisted__Bool_4776 = 1;
    (void)hoisted__Bool_4776;
    assert(&hoisted__Str_4775, hoisted__Bool_4776);
    Str_delete(&hoisted__Str_4775, (Bool){0});
    Str hoisted__Str_4779 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4779;
    Bool hoisted__Bool_4780 = 1;
    (void)hoisted__Bool_4780;
    assert(&hoisted__Str_4779, hoisted__Bool_4780);
    Str_delete(&hoisted__Str_4779, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4785 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4785;
    Str hoisted__Str_4786 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4786;
    Str hoisted__Str_4787 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4787;
    assert_eq_str(&hoisted__Str_4785, &hoisted__Str_4786, &hoisted__Str_4787);
    Str_delete(&hoisted__Str_4785, (Bool){0});
    Str_delete(&hoisted__Str_4786, (Bool){0});
    Str_delete(&hoisted__Str_4787, (Bool){0});
    Str hoisted__Str_4790 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4790;
    Str hoisted__Str_4791 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4791;
    Str hoisted__Str_4792 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4792;
    assert_eq_str(&hoisted__Str_4790, &hoisted__Str_4791, &hoisted__Str_4792);
    Str_delete(&hoisted__Str_4790, (Bool){0});
    Str_delete(&hoisted__Str_4791, (Bool){0});
    Str_delete(&hoisted__Str_4792, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4797 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4797;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4797;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4798 = 16;
    (void)hoisted__U32_4798;
    return hoisted__U32_4798;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4799 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4799;
    I64 hoisted__I64_4800 = 42;
    (void)hoisted__I64_4800;
    assert_eq(&hoisted__Str_4799, v.x, hoisted__I64_4800);
    Str_delete(&hoisted__Str_4799, (Bool){0});
    Str hoisted__Str_4801 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4801;
    I64 hoisted__I64_4802 = 99;
    (void)hoisted__I64_4802;
    assert_eq(&hoisted__Str_4801, v.y, hoisted__I64_4802);
    Str_delete(&hoisted__Str_4801, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4805 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4805;
    I64 hoisted__I64_4806 = 10;
    (void)hoisted__I64_4806;
    assert_eq(&hoisted__Str_4805, p.x, hoisted__I64_4806);
    Str_delete(&hoisted__Str_4805, (Bool){0});
    Str hoisted__Str_4807 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4807;
    I64 hoisted__I64_4808 = 20;
    (void)hoisted__I64_4808;
    assert_eq(&hoisted__Str_4807, p.y, hoisted__I64_4808);
    Str_delete(&hoisted__Str_4807, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4814 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4814;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4814;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4815 = 32;
    (void)hoisted__U32_4815;
    return hoisted__U32_4815;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4816 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4816;
    I64 hoisted__I64_4817 = 5;
    (void)hoisted__I64_4817;
    assert_eq(&hoisted__Str_4816, r.top_left.x, hoisted__I64_4817);
    Str_delete(&hoisted__Str_4816, (Bool){0});
    Str hoisted__Str_4818 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4818;
    I64 hoisted__I64_4819 = 10;
    (void)hoisted__I64_4819;
    assert_eq(&hoisted__Str_4818, r.top_left.y, hoisted__I64_4819);
    Str_delete(&hoisted__Str_4818, (Bool){0});
    Str hoisted__Str_4820 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4820;
    I64 hoisted__I64_4821 = 100;
    (void)hoisted__I64_4821;
    assert_eq(&hoisted__Str_4820, r.bottom_right.x, hoisted__I64_4821);
    Str_delete(&hoisted__Str_4820, (Bool){0});
    Str hoisted__Str_4822 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4822;
    I64 hoisted__I64_4823 = 200;
    (void)hoisted__I64_4823;
    assert_eq(&hoisted__Str_4822, r.bottom_right.y, hoisted__I64_4823);
    Str_delete(&hoisted__Str_4822, (Bool){0});
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
    Bool hoisted__Bool_4828 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4828;
    if (hoisted__Bool_4828) {
        Bool hoisted__Bool_4825 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4825;
        { Bool _ret_val = hoisted__Bool_4825;
                return _ret_val; }
    }
    Bool hoisted__Bool_4829 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4829;
    if (hoisted__Bool_4829) {
        Bool hoisted__Bool_4826 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4826;
        { Bool _ret_val = hoisted__Bool_4826;
                return _ret_val; }
    }
    Bool hoisted__Bool_4830 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4830;
    if (hoisted__Bool_4830) {
        Bool hoisted__Bool_4827 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4827;
        { Bool _ret_val = hoisted__Bool_4827;
                return _ret_val; }
    }
    Bool hoisted__Bool_4831 = 0;
    (void)hoisted__Bool_4831;
    return hoisted__Bool_4831;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4839 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4839;
    if (hoisted__Bool_4839) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4840 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4840;
    if (hoisted__Bool_4840) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4841 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4841;
    if (hoisted__Bool_4841) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4842 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4842;
    UNREACHABLE(&hoisted__Str_4842);
    Str_delete(&hoisted__Str_4842, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4843 = 4;
    (void)hoisted__U32_4843;
    return hoisted__U32_4843;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_4844 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4844;
    Bool hoisted__Bool_4845 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4845;
    assert(&hoisted__Str_4844, hoisted__Bool_4845);
    Str_delete(&hoisted__Str_4844, (Bool){0});
    Bool hoisted__Bool_4846 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4846;
    Color_delete(&c, 0);
    Str hoisted__Str_4847 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4847;
    Bool hoisted__Bool_4848 = not(hoisted__Bool_4846);
    (void)hoisted__Bool_4848;
    assert(&hoisted__Str_4847, hoisted__Bool_4848);
    Str_delete(&hoisted__Str_4847, (Bool){0});
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
    Bool hoisted__Bool_4849 = is(self, other);
    (void)hoisted__Bool_4849;
    return hoisted__Bool_4849;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_4867 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4867;
    if (hoisted__Bool_4867) {
        I64 *hoisted__I64_4863 = get_payload(self);
        (void)hoisted__I64_4863;
        (void)hoisted__I64_4863;
        Bool hoisted__Bool_4864 = 0;
        (void)hoisted__Bool_4864;
        I64_delete(hoisted__I64_4863, hoisted__Bool_4864);
    }
    Bool hoisted__Bool_4868 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4868;
    if (hoisted__Bool_4868) {
        Str *hoisted__Str_4865 = get_payload(self);
        (void)hoisted__Str_4865;
        (void)hoisted__Str_4865;
        Bool hoisted__Bool_4866 = 0;
        (void)hoisted__Bool_4866;
        Str_delete(hoisted__Str_4865, hoisted__Bool_4866);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4897 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4897;
    if (hoisted__Bool_4897) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4894 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4894;
        { Token * _ret_val = hoisted__Token_4894;
                return _ret_val; }
    }
    Bool hoisted__Bool_4898 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4898;
    if (hoisted__Bool_4898) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4895 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4895;
        Token *hoisted__Token_4896 = Token_Name(hoisted__Str_4895);
        (void)hoisted__Token_4896;
        { Token * _ret_val = hoisted__Token_4896;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4899 = 24;
    (void)hoisted__U32_4899;
    return hoisted__U32_4899;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_4901 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4901;
    Bool hoisted__Bool_4902 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4902;
    assert(&hoisted__Str_4901, hoisted__Bool_4902);
    Str_delete(&hoisted__Str_4901, (Bool){0});
    Bool hoisted__Bool_4903 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4903;
    Token_delete(t, 1);
    Str hoisted__Str_4904 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4904;
    Bool hoisted__Bool_4905 = not(hoisted__Bool_4903);
    (void)hoisted__Bool_4905;
    assert(&hoisted__Str_4904, hoisted__Bool_4905);
    Str_delete(&hoisted__Str_4904, (Bool){0});
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_4906 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4906;
    Bool hoisted__Bool_4907 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4907;
    assert(&hoisted__Str_4906, hoisted__Bool_4907);
    Str_delete(&hoisted__Str_4906, (Bool){0});
    Bool hoisted__Bool_4908 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4908;
    Color_delete(({ Color *_oa = malloc(sizeof(Color)); *_oa = c; _oa; }), 1);
    Str hoisted__Str_4909 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4909;
    Bool hoisted__Bool_4910 = not(hoisted__Bool_4908);
    (void)hoisted__Bool_4910;
    assert(&hoisted__Str_4909, hoisted__Bool_4910);
    Str_delete(&hoisted__Str_4909, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_4913 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4913;
    Bool hoisted__Bool_4914 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4914;
    assert(&hoisted__Str_4913, hoisted__Bool_4914);
    Str_delete(&hoisted__Str_4913, (Bool){0});
    Bool hoisted__Bool_4915 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4915;
    Token_delete(t, 1);
    Str hoisted__Str_4916 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4916;
    Bool hoisted__Bool_4917 = not(hoisted__Bool_4915);
    (void)hoisted__Bool_4917;
    assert(&hoisted__Str_4916, hoisted__Bool_4917);
    Str_delete(&hoisted__Str_4916, (Bool){0});
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)F32_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)F32_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U64_clone_dyn;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U32_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U32_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U32_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U32_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U32_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U32_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I32_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I32_size_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I8_delete_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I8_size_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U8_clone_dyn;
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
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I64_delete_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I64_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I64_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I64_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I64_neq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Bool_eq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Bool_cmp_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Bool_clone_dyn;
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
