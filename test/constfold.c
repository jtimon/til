#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef struct Str Str;
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
typedef void (*DeleteFn)(void *, Bool *);







typedef struct Str {
    I8 *c_str;
    U32 count;
    U32 cap;
} Str;


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

void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
void U64_delete(U64 * self, Bool * call_free);
U32 * U64_size(void);
Str * U32_to_str(U32 * val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool * call_free);
U32 * U32_size(void);
Bool U32_lt(U32 * a, U32 * b);
Bool U32_gt(U32 * a, U32 * b);
Bool U32_lte(U32 * a, U32 * b);
Bool U32_gte(U32 * a, U32 * b);
void I32_delete(I32 * self, Bool * call_free);
U32 * I32_size(void);
void I8_delete(I8 * self, Bool * call_free);
U32 * I8_size(void);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Bool Str_is_empty(Str * self);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
Str * I64_to_str(I64 * val);
void I64_delete(I64 * self, Bool * call_free);
U32 * I64_size(void);
Bool I64_lt(I64 * a, I64 * b);
Bool I64_gt(I64 * a, I64 * b);
Bool I64_neq(I64 * a, I64 * b);
I64 * Bool_cmp(Bool * a, Bool * b);
void Bool_delete(Bool * self, Bool * call_free);
U32 * Bool_size(void);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool * call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
void Type_delete(Type * self, Bool * call_free);
Type * Type_clone(Type * self);
U32 Type_size(void);
Array * Array_new_type_name(Str * elem_type, U32 * cap);
Array * Array_new(Type * T, U32 * cap);
U32 * Array_len(Array * self);
void * Array_get(Array * self, U32 * i);
void Array_set(Array * self, U32 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
void panic(Str * loc_str, Array * parts);
void UNREACHABLE(Str * loc_str);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
void println(Array * parts);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
void test_fold_f32(void);
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool * call_free);
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool * call_free);
U32 CfRect_size(void);
void test_struct_fold_nested(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool * call_free);
Color * Color_clone(Color * self);
U32 Color_size(void);
void test_enum_fold(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool * call_free);
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

void F32_delete(F32 * self, Bool * call_free);
U32 * F32_size(void);
void U64_delete(U64 * self, Bool * call_free);
U32 * U64_size(void);
Str * U32_to_str(U32 * val);
void U32_inc(U32 * self);
void U32_dec(U32 * self);
void U32_delete(U32 * self, Bool * call_free);
U32 * U32_size(void);
Bool U32_lt(U32 * a, U32 * b);
Bool U32_gt(U32 * a, U32 * b);
Bool U32_lte(U32 * a, U32 * b);
Bool U32_gte(U32 * a, U32 * b);
void I32_delete(I32 * self, Bool * call_free);
U32 * I32_size(void);
void I8_delete(I8 * self, Bool * call_free);
U32 * I8_size(void);
void U8_delete(U8 * self, Bool * call_free);
U32 * U8_size(void);
Str * format(Array * parts);
U32 Str_len(Str * self);
I8 * Str_get(Str * self, U32 * i);
I64 Str_cmp(Str * a, Str * b);
Str * Str_with_capacity(U32 * n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
void Str_delete(Str * self, Bool * call_free);
Bool Str_is_empty(Str * self);
U32 Str_size(void);
Bool Str_eq(Str * a, Str * b);
U32 * Dynamic_size(void);
void * default_clone(void * v);
void default_delete(void * _v, Bool * _cf);
Str * I64_to_str(I64 * val);
void I64_delete(I64 * self, Bool * call_free);
U32 * I64_size(void);
Bool I64_lt(I64 * a, I64 * b);
Bool I64_gt(I64 * a, I64 * b);
Bool I64_neq(I64 * a, I64 * b);
I64 * Bool_cmp(Bool * a, Bool * b);
void Bool_delete(Bool * self, Bool * call_free);
U32 * Bool_size(void);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool * call_free);
Primitive * Primitive_clone(Primitive * self);
U32 Primitive_size(void);
void Type_delete(Type * self, Bool * call_free);
Type * Type_clone(Type * self);
U32 Type_size(void);
Array * Array_new_type_name(Str * elem_type, U32 * cap);
Array * Array_new(Type * T, U32 * cap);
U32 * Array_len(Array * self);
void * Array_get(Array * self, U32 * i);
void Array_set(Array * self, U32 * i, void * val);
void Array_delete(Array * self, Bool * call_free);
Array * Array_clone(Array * self);
U32 Array_size(void);
void panic(Str * loc_str, Array * parts);
void UNREACHABLE(Str * loc_str);
Bool * assert(Str * loc_str, Bool * cond);
void assert_eq(Str * loc_str, I64 * a, I64 * b);
void assert_eq_str(Str * loc_str, Str * a, Str * b);
void println(Array * parts);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
void test_fold_f32(void);
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool * call_free);
U32 CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool * call_free);
U32 CfRect_size(void);
void test_struct_fold_nested(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool * call_free);
Color * Color_clone(Color * self);
U32 Color_size(void);
void test_enum_fold(void);
Token * Token_Num(I64 * val);
Token * Token_Name(Str * val);
Token * Token_Eof(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool * call_free);
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

void F32_delete(F32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * F32_size(void) {
    U32 hoisted__U32_1 = 4;
    (void)hoisted__U32_1;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1;
    return _r; }
}

void U64_delete(U64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U64_size(void) {
    U32 hoisted__U32_35 = 8;
    (void)hoisted__U32_35;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_35;
    return _r; }
}

Str * U32_to_str(U32 * val) {
    I64 hoisted__I64_123 = U32_to_i64(DEREF(val));
    (void)hoisted__I64_123;
    Str *hoisted__Str_124 = I64_to_str(&hoisted__I64_123);
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

void U32_delete(U32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U32_size(void) {
    U32 hoisted__U32_135 = 4;
    (void)hoisted__U32_135;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_135;
    return _r; }
}

Bool U32_lt(U32 * a, U32 * b) {
    I64 hoisted__I64_211 = U32_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_211;
    I64 hoisted__I64_212 = -1;
    (void)hoisted__I64_212;
    Bool hoisted__Bool_213 = I64_eq(hoisted__I64_211, hoisted__I64_212);
    (void)hoisted__Bool_213;
    return hoisted__Bool_213;
}

Bool U32_gt(U32 * a, U32 * b) {
    I64 hoisted__I64_214 = U32_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_214;
    I64 hoisted__I64_215 = 1;
    (void)hoisted__I64_215;
    Bool hoisted__Bool_216 = I64_eq(hoisted__I64_214, hoisted__I64_215);
    (void)hoisted__Bool_216;
    return hoisted__Bool_216;
}

Bool U32_lte(U32 * a, U32 * b) {
    Bool hoisted__Bool_219 = U32_gt(a, b);
    (void)hoisted__Bool_219;
    Bool hoisted__Bool_220 = not(hoisted__Bool_219);
    (void)hoisted__Bool_220;
    return hoisted__Bool_220;
}

Bool U32_gte(U32 * a, U32 * b) {
    Bool hoisted__Bool_221 = U32_lt(a, b);
    (void)hoisted__Bool_221;
    Bool hoisted__Bool_222 = not(hoisted__Bool_221);
    (void)hoisted__Bool_222;
    return hoisted__Bool_222;
}

void I32_delete(I32 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I32_size(void) {
    U32 hoisted__U32_247 = 4;
    (void)hoisted__U32_247;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_247;
    return _r; }
}

void I8_delete(I8 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I8_size(void) {
    U32 hoisted__U32_412 = 1;
    (void)hoisted__U32_412;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_412;
    return _r; }
}

void U8_delete(U8 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * U8_size(void) {
    U32 hoisted__U32_439 = 1;
    (void)hoisted__U32_439;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_439;
    return _r; }
}

Str * format(Array * parts) {
    U32 total = 0;
    {
        Array *_fc_Array_795 = parts;
        (void)_fc_Array_795;
        (void)_fc_Array_795;
        U32 _fi_USize_795 = 0;
        (void)_fi_USize_795;
        while (1) {
            U32 hoisted__U32_797; { U32 *_hp = (U32 *)Array_len(_fc_Array_795); hoisted__U32_797 = *_hp; free(_hp); }
            (void)hoisted__U32_797;
            Bool _wcond_Bool_796 = U32_lt(&_fi_USize_795, &hoisted__U32_797);
            (void)_wcond_Bool_796;
            if (_wcond_Bool_796) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_795, &_fi_USize_795);
            U32 hoisted__U32_798 = 1;
            (void)hoisted__U32_798;
            U32 hoisted__U32_799 = U32_add(_fi_USize_795, hoisted__U32_798);
            (void)hoisted__U32_799;
            _fi_USize_795 = hoisted__U32_799;
            U32 hoisted__U32_800 = Str_len(s);
            (void)hoisted__U32_800;
            U32 hoisted__U32_801 = U32_add(total, hoisted__U32_800);
            (void)hoisted__U32_801;
            total = hoisted__U32_801;
        }
    }
    Str *out = Str_with_capacity(&total);
    {
        Array *_fc_Array_802 = parts;
        (void)_fc_Array_802;
        (void)_fc_Array_802;
        U32 _fi_USize_802 = 0;
        (void)_fi_USize_802;
        while (1) {
            U32 hoisted__U32_804; { U32 *_hp = (U32 *)Array_len(_fc_Array_802); hoisted__U32_804 = *_hp; free(_hp); }
            (void)hoisted__U32_804;
            Bool _wcond_Bool_803 = U32_lt(&_fi_USize_802, &hoisted__U32_804);
            (void)_wcond_Bool_803;
            if (_wcond_Bool_803) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_802, &_fi_USize_802);
            U32 hoisted__U32_805 = 1;
            (void)hoisted__U32_805;
            U32 hoisted__U32_806 = U32_add(_fi_USize_802, hoisted__U32_805);
            (void)hoisted__U32_806;
            _fi_USize_802 = hoisted__U32_806;
            Str_push_str(out, s);
        }
    }
    Array_delete(parts, &(Bool){1});
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_813 = U32_gte(i, &self->count);
    (void)hoisted__Bool_813;
    if (hoisted__Bool_813) {
        Type *hoisted__Type_808 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_808;
        U32 hoisted__U32_809 = 1;
        (void)hoisted__U32_809;
        Array *_va_Array_24 = Array_new(hoisted__Type_808, &hoisted__U32_809);
        (void)_va_Array_24;
        Type_delete(hoisted__Type_808, &(Bool){1});
        U32 hoisted__U32_810 = 0;
        (void)hoisted__U32_810;
        Str hoisted__Str_811 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_811;
        Array_set(_va_Array_24, &hoisted__U32_810, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_811; _oa; }));
        Str hoisted__Str_812 = (Str){.c_str = (void *)"./src/core/str.til:42:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_812;
        panic(&hoisted__Str_812, _va_Array_24);
        Str_delete(&hoisted__Str_812, &(Bool){0});
    }
    void *hoisted__v_814 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_814;
    (void)hoisted__v_814;
    return hoisted__v_814;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_824 = U32_lt(&b->count, &a->count);
    (void)hoisted__Bool_824;
    if (hoisted__Bool_824) {
        min_len = b->count;
    }
    {
        U32 _re_U32_816 = U32_clone(&min_len);
        (void)_re_U32_816;
        U32 _rc_U32_816 = 0;
        (void)_rc_U32_816;
        Bool hoisted__Bool_823 = U32_lte(&_rc_U32_816, &_re_U32_816);
        (void)hoisted__Bool_823;
        if (hoisted__Bool_823) {
            while (1) {
                Bool _wcond_Bool_817 = U32_lt(&_rc_U32_816, &_re_U32_816);
                (void)_wcond_Bool_817;
                if (_wcond_Bool_817) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_816);
                U32_inc(&_rc_U32_816);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_818 = 0;
                (void)hoisted__I64_818;
                Bool hoisted__Bool_819 = I64_neq(&c, &hoisted__I64_818);
                (void)hoisted__Bool_819;
                if (hoisted__Bool_819) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_820 = U32_gt(&_rc_U32_816, &_re_U32_816);
                (void)_wcond_Bool_820;
                if (_wcond_Bool_820) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_816);
                U32_dec(&_rc_U32_816);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_821 = 0;
                (void)hoisted__I64_821;
                Bool hoisted__Bool_822 = I64_neq(&c, &hoisted__I64_821);
                (void)hoisted__Bool_822;
                if (hoisted__Bool_822) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_825 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_825;
    return hoisted__I64_825;
}

Str * Str_with_capacity(U32 * n) {
    U32 hoisted__U32_827 = 1;
    (void)hoisted__U32_827;
    U32 hoisted__U64_828 = U32_add(DEREF(n), hoisted__U32_827);
    (void)hoisted__U64_828;
    void * buf = malloc(hoisted__U64_828);
    I32 hoisted__I32_829 = 0;
    (void)hoisted__I32_829;
    U64 hoisted__U64_830 = 1;
    (void)hoisted__U64_830;
    memset(buf, hoisted__I32_829, hoisted__U64_830);
    I32_delete(&hoisted__I32_829, &(Bool){0});
    I64 hoisted__I64_831 = 0;
    (void)hoisted__I64_831;
    Str *hoisted__Str_832 = malloc(sizeof(Str));
    hoisted__Str_832->c_str = buf;
    hoisted__Str_832->count = hoisted__I64_831;
    hoisted__Str_832->cap = DEREF(n);
    (void)hoisted__Str_832;
    return hoisted__Str_832;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_845 = U32_gte(&self->cap, &CAP_VIEW);
    (void)hoisted__Bool_845;
    if (hoisted__Bool_845) {
        Type *hoisted__Type_834 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_834;
        U32 hoisted__U32_835 = 1;
        (void)hoisted__U32_835;
        Array *_va_Array_25 = Array_new(hoisted__Type_834, &hoisted__U32_835);
        (void)_va_Array_25;
        Type_delete(hoisted__Type_834, &(Bool){1});
        U32 hoisted__U32_836 = 0;
        (void)hoisted__U32_836;
        Str hoisted__Str_837 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_837;
        Array_set(_va_Array_25, &hoisted__U32_836, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_837; _oa; }));
        Str hoisted__Str_838 = (Str){.c_str = (void *)"./src/core/str.til:85:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_838;
        panic(&hoisted__Str_838, _va_Array_25);
        Str_delete(&hoisted__Str_838, &(Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_846 = U32_gt(&new_len, &self->cap);
    (void)hoisted__Bool_846;
    if (hoisted__Bool_846) {
        Type *hoisted__Type_840 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_840;
        U32 hoisted__U32_841 = 1;
        (void)hoisted__U32_841;
        Array *_va_Array_26 = Array_new(hoisted__Type_840, &hoisted__U32_841);
        (void)_va_Array_26;
        Type_delete(hoisted__Type_840, &(Bool){1});
        U32 hoisted__U32_842 = 0;
        (void)hoisted__U32_842;
        Str hoisted__Str_843 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_843;
        Array_set(_va_Array_26, &hoisted__U32_842, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_843; _oa; }));
        Str hoisted__Str_844 = (Str){.c_str = (void *)"./src/core/str.til:89:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_844;
        panic(&hoisted__Str_844, _va_Array_26);
        Str_delete(&hoisted__Str_844, &(Bool){0});
    }
    void *hoisted__v_847 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_847;
    (void)hoisted__v_847;
    memcpy(hoisted__v_847, s->c_str, s->count);
    U32 hoisted__U32_848 = U32_clone(&new_len);
    (void)hoisted__U32_848;
    self->count = hoisted__U32_848;
    void *hoisted__v_849 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_849;
    (void)hoisted__v_849;
    I32 hoisted__I32_850 = 0;
    (void)hoisted__I32_850;
    U64 hoisted__U64_851 = 1;
    (void)hoisted__U64_851;
    memset(hoisted__v_849, hoisted__I32_850, hoisted__U64_851);
    I32_delete(&hoisted__I32_850, &(Bool){0});
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_852 = 1;
    (void)hoisted__U32_852;
    U32 hoisted__U64_853 = U32_add(val->count, hoisted__U32_852);
    (void)hoisted__U64_853;
    void * new_data = malloc(hoisted__U64_853);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_854 = ptr_add(new_data, val->count);
    (void)hoisted__v_854;
    (void)hoisted__v_854;
    I32 hoisted__I32_855 = 0;
    (void)hoisted__I32_855;
    U64 hoisted__U64_856 = 1;
    (void)hoisted__U64_856;
    memset(hoisted__v_854, hoisted__I32_855, hoisted__U64_856);
    I32_delete(&hoisted__I32_855, &(Bool){0});
    Str *hoisted__Str_857 = malloc(sizeof(Str));
    hoisted__Str_857->c_str = new_data;
    hoisted__Str_857->count = val->count;
    hoisted__Str_857->cap = val->count;
    (void)hoisted__Str_857;
    return hoisted__Str_857;
}

void Str_delete(Str * self, Bool * call_free) {
    Bool hoisted__Bool_858 = U32_lt(&self->cap, &CAP_VIEW);
    (void)hoisted__Bool_858;
    if (hoisted__Bool_858) {
        free(self->c_str);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_971 = 0;
    (void)hoisted__U32_971;
    Bool hoisted__Bool_972 = U32_eq(self->count, hoisted__U32_971);
    (void)hoisted__Bool_972;
    return hoisted__Bool_972;
}

U32 Str_size(void) {
    U32 hoisted__U32_1191 = 16;
    (void)hoisted__U32_1191;
    return hoisted__U32_1191;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1192 = Str_cmp(a, b);
    (void)hoisted__I64_1192;
    I64 hoisted__I64_1193 = 0;
    (void)hoisted__I64_1193;
    Bool hoisted__Bool_1194 = I64_eq(hoisted__I64_1192, hoisted__I64_1193);
    (void)hoisted__Bool_1194;
    return hoisted__Bool_1194;
}

U32 * Dynamic_size(void) {
    U32 hoisted__U32_1281 = 8;
    (void)hoisted__U32_1281;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1281;
    return _r; }
}

void * default_clone(void * v) {
    return v;
}

void default_delete(void * _v, Bool * _cf) {
    (void)_v;
    (void)_cf;
}

Str * I64_to_str(I64 * val) {
    I64 hoisted__I64_1485 = 0;
    (void)hoisted__I64_1485;
    Bool hoisted__Bool_1486 = I64_eq(DEREF(val), hoisted__I64_1485);
    (void)hoisted__Bool_1486;
    if (hoisted__Bool_1486) {
        U64 hoisted__U64_1449 = 2;
        (void)hoisted__U64_1449;
        void * buf = malloc(hoisted__U64_1449);
        I64 hoisted__I64_1450 = 48;
        (void)hoisted__I64_1450;
        U64 hoisted__U64_1451 = 1;
        (void)hoisted__U64_1451;
        memcpy(buf, &hoisted__I64_1450, hoisted__U64_1451);
        U64 hoisted__U64_1452 = 1;
        (void)hoisted__U64_1452;
        void *hoisted__v_1453 = ptr_add(buf, hoisted__U64_1452);
        (void)hoisted__v_1453;
        (void)hoisted__v_1453;
        I32 hoisted__I32_1454 = 0;
        (void)hoisted__I32_1454;
        U64 hoisted__U64_1455 = 1;
        (void)hoisted__U64_1455;
        memset(hoisted__v_1453, hoisted__I32_1454, hoisted__U64_1455);
        I32_delete(&hoisted__I32_1454, &(Bool){0});
        I64 hoisted__I64_1456 = 1;
        (void)hoisted__I64_1456;
        I64 hoisted__I64_1457 = 1;
        (void)hoisted__I64_1457;
        Str *hoisted__Str_1458 = malloc(sizeof(Str));
        hoisted__Str_1458->c_str = buf;
        hoisted__Str_1458->count = hoisted__I64_1456;
        hoisted__Str_1458->cap = hoisted__I64_1457;
        (void)hoisted__Str_1458;
        { Str * _ret_val = hoisted__Str_1458;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_1487 = 0;
    (void)hoisted__I64_1487;
    Bool hoisted__Bool_1488 = I64_lt(val, &hoisted__I64_1487);
    (void)hoisted__Bool_1488;
    if (hoisted__Bool_1488) {
        Bool hoisted__Bool_1459 = 1;
        (void)hoisted__Bool_1459;
        is_neg = hoisted__Bool_1459;
        I64 hoisted__I64_1460 = 0;
        (void)hoisted__I64_1460;
        I64 hoisted__I64_1461 = I64_sub(hoisted__I64_1460, DEREF(val));
        (void)hoisted__I64_1461;
        v = hoisted__I64_1461;
    }
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1463 = 0;
        (void)hoisted__I64_1463;
        Bool _wcond_Bool_1462 = I64_gt(&tmp, &hoisted__I64_1463);
        (void)_wcond_Bool_1462;
        if (_wcond_Bool_1462) {
        } else {
            break;
        }
        U64 hoisted__U64_1464 = 1;
        (void)hoisted__U64_1464;
        U64 hoisted__U64_1465 = U64_add(ndigits, hoisted__U64_1464);
        (void)hoisted__U64_1465;
        ndigits = hoisted__U64_1465;
        I64 hoisted__I64_1466 = 10;
        (void)hoisted__I64_1466;
        I64 hoisted__I64_1467 = I64_div(tmp, hoisted__I64_1466);
        (void)hoisted__I64_1467;
        tmp = hoisted__I64_1467;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1468 = 1;
        (void)hoisted__U64_1468;
        U64 hoisted__U64_1469 = U64_add(total, hoisted__U64_1468);
        (void)hoisted__U64_1469;
        total = hoisted__U64_1469;
    }
    U64 hoisted__U64_1489 = 1;
    (void)hoisted__U64_1489;
    U64 hoisted__U64_1490 = U64_add(total, hoisted__U64_1489);
    (void)hoisted__U64_1490;
    void * buf = malloc(hoisted__U64_1490);
    if (is_neg) {
        I64 hoisted__I64_1470 = 45;
        (void)hoisted__I64_1470;
        U64 hoisted__U64_1471 = 1;
        (void)hoisted__U64_1471;
        memcpy(buf, &hoisted__I64_1470, hoisted__U64_1471);
    }
    U64 hoisted__U64_1491 = 1;
    (void)hoisted__U64_1491;
    U64 i = U64_sub(total, hoisted__U64_1491);
    while (1) {
        I64 hoisted__I64_1473 = 0;
        (void)hoisted__I64_1473;
        Bool _wcond_Bool_1472 = I64_gt(&v, &hoisted__I64_1473);
        (void)_wcond_Bool_1472;
        if (_wcond_Bool_1472) {
        } else {
            break;
        }
        I64 hoisted__I64_1474 = 10;
        (void)hoisted__I64_1474;
        I64 hoisted__I64_1475 = I64_mod(v, hoisted__I64_1474);
        (void)hoisted__I64_1475;
        I64 hoisted__I64_1476 = 48;
        (void)hoisted__I64_1476;
        I64 hoisted__I64_1477 = I64_add(hoisted__I64_1475, hoisted__I64_1476);
        (void)hoisted__I64_1477;
        void *hoisted__v_1478 = ptr_add(buf, i);
        (void)hoisted__v_1478;
        (void)hoisted__v_1478;
        U8 hoisted__U8_1479 = I64_to_u8(hoisted__I64_1477);
        (void)hoisted__U8_1479;
        U64 hoisted__U64_1480 = 1;
        (void)hoisted__U64_1480;
        memcpy(hoisted__v_1478, &hoisted__U8_1479, hoisted__U64_1480);
        U8_delete(&hoisted__U8_1479, &(Bool){0});
        I64 hoisted__I64_1481 = 10;
        (void)hoisted__I64_1481;
        I64 hoisted__I64_1482 = I64_div(v, hoisted__I64_1481);
        (void)hoisted__I64_1482;
        v = hoisted__I64_1482;
        U64 hoisted__U64_1483 = 1;
        (void)hoisted__U64_1483;
        U64 hoisted__U64_1484 = U64_sub(i, hoisted__U64_1483);
        (void)hoisted__U64_1484;
        i = hoisted__U64_1484;
    }
    void *hoisted__v_1492 = ptr_add(buf, total);
    (void)hoisted__v_1492;
    (void)hoisted__v_1492;
    I32 hoisted__I32_1493 = 0;
    (void)hoisted__I32_1493;
    U64 hoisted__U64_1494 = 1;
    (void)hoisted__U64_1494;
    memset(hoisted__v_1492, hoisted__I32_1493, hoisted__U64_1494);
    I32_delete(&hoisted__I32_1493, &(Bool){0});
    Str *hoisted__Str_1495 = malloc(sizeof(Str));
    hoisted__Str_1495->c_str = buf;
    hoisted__Str_1495->count = total;
    hoisted__Str_1495->cap = total;
    (void)hoisted__Str_1495;
    return hoisted__Str_1495;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    U32 hoisted__U32_1513 = 8;
    (void)hoisted__U32_1513;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1513;
    return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1646 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1646;
    I64 hoisted__I64_1647 = -1;
    (void)hoisted__I64_1647;
    Bool hoisted__Bool_1648 = I64_eq(hoisted__I64_1646, hoisted__I64_1647);
    (void)hoisted__Bool_1648;
    return hoisted__Bool_1648;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1649 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1649;
    I64 hoisted__I64_1650 = 1;
    (void)hoisted__I64_1650;
    Bool hoisted__Bool_1651 = I64_eq(hoisted__I64_1649, hoisted__I64_1650);
    (void)hoisted__Bool_1651;
    return hoisted__Bool_1651;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1652 = I64_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1652;
    Bool hoisted__Bool_1653 = not(hoisted__Bool_1652);
    (void)hoisted__Bool_1653;
    return hoisted__Bool_1653;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1667 = Bool_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1667;
    if (hoisted__Bool_1667) {
        I64 hoisted__I64_1665 = 0;
        (void)hoisted__I64_1665;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1665;
                return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1666 = -1;
        (void)hoisted__I64_1666;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1666;
        return _r; }
    }
    I64 hoisted__I64_1668 = 1;
    (void)hoisted__I64_1668;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1668;
    return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    U32 hoisted__U32_1669 = 1;
    (void)hoisted__U32_1669;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1669;
    return _r; }
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
    Bool hoisted__Bool_1808 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1808;
    if (hoisted__Bool_1808) {
        Bool hoisted__Bool_1806 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1806;
        { Bool _ret_val = hoisted__Bool_1806;
                return _ret_val; }
    }
    Bool hoisted__Bool_1809 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1809;
    if (hoisted__Bool_1809) {
        Bool hoisted__Bool_1807 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1807;
        { Bool _ret_val = hoisted__Bool_1807;
                return _ret_val; }
    }
    Bool hoisted__Bool_1810 = 0;
    (void)hoisted__Bool_1810;
    return hoisted__Bool_1810;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1816 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1816;
    if (hoisted__Bool_1816) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1817 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1817;
    if (hoisted__Bool_1817) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Str hoisted__Str_1818 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1818;
    UNREACHABLE(&hoisted__Str_1818);
    Str_delete(&hoisted__Str_1818, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1819 = 4;
    (void)hoisted__U32_1819;
    return hoisted__U32_1819;
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
void Type_delete(Type * self, Bool * call_free) {
    Bool hoisted__Bool_1882 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1882;
    if (hoisted__Bool_1882) {
        Str *hoisted__Str_1874 = get_payload(self);
        (void)hoisted__Str_1874;
        (void)hoisted__Str_1874;
        Bool hoisted__Bool_1875 = 0;
        (void)hoisted__Bool_1875;
        Str_delete(hoisted__Str_1874, &hoisted__Bool_1875);
    }
    Bool hoisted__Bool_1883 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1883;
    if (hoisted__Bool_1883) {
        Str *hoisted__Str_1876 = get_payload(self);
        (void)hoisted__Str_1876;
        (void)hoisted__Str_1876;
        Bool hoisted__Bool_1877 = 0;
        (void)hoisted__Bool_1877;
        Str_delete(hoisted__Str_1876, &hoisted__Bool_1877);
    }
    Bool hoisted__Bool_1884 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1884;
    if (hoisted__Bool_1884) {
        Str *hoisted__Str_1878 = get_payload(self);
        (void)hoisted__Str_1878;
        (void)hoisted__Str_1878;
        Bool hoisted__Bool_1879 = 0;
        (void)hoisted__Bool_1879;
        Str_delete(hoisted__Str_1878, &hoisted__Bool_1879);
    }
    Bool hoisted__Bool_1885 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1885;
    if (hoisted__Bool_1885) {
        Primitive *hoisted__Primitive_1880 = get_payload(self);
        (void)hoisted__Primitive_1880;
        (void)hoisted__Primitive_1880;
        Bool hoisted__Bool_1881 = 0;
        (void)hoisted__Bool_1881;
        Primitive_delete(hoisted__Primitive_1880, &hoisted__Bool_1881);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1967 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_1967;
    if (hoisted__Bool_1967) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_1968 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_1968;
    if (hoisted__Bool_1968) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_1969 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)hoisted__Bool_1969;
    if (hoisted__Bool_1969) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1970 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)hoisted__Bool_1970;
    if (hoisted__Bool_1970) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1971 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)hoisted__Bool_1971;
    if (hoisted__Bool_1971) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1972 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)hoisted__Bool_1972;
    if (hoisted__Bool_1972) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1973 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)hoisted__Bool_1973;
    if (hoisted__Bool_1973) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1974 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)hoisted__Bool_1974;
    if (hoisted__Bool_1974) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1975 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)hoisted__Bool_1975;
    if (hoisted__Bool_1975) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool;
                return _r; }
    }
    Bool hoisted__Bool_1976 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1976;
    if (hoisted__Bool_1976) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_1961 = Str_clone(_clone_payload_Struct_9);
        (void)hoisted__Str_1961;
        Type *hoisted__Type_1962 = Type_Struct(hoisted__Str_1961);
        (void)hoisted__Type_1962;
        { Type * _ret_val = hoisted__Type_1962;
                return _ret_val; }
    }
    Bool hoisted__Bool_1977 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_1977;
    if (hoisted__Bool_1977) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_1978 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1978;
    if (hoisted__Bool_1978) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_1963 = Str_clone(_clone_payload_Enum_11);
        (void)hoisted__Str_1963;
        Type *hoisted__Type_1964 = Type_Enum(hoisted__Str_1963);
        (void)hoisted__Type_1964;
        { Type * _ret_val = hoisted__Type_1964;
                return _ret_val; }
    }
    Bool hoisted__Bool_1979 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_1979;
    if (hoisted__Bool_1979) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_1980 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_1980;
    if (hoisted__Bool_1980) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_1981 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_1981;
    if (hoisted__Bool_1981) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_1982 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_1982;
    if (hoisted__Bool_1982) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_1983 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1983;
    if (hoisted__Bool_1983) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_1965 = Str_clone(_clone_payload_Custom_16);
        (void)hoisted__Str_1965;
        Type *hoisted__Type_1966 = Type_Custom(hoisted__Str_1965);
        (void)hoisted__Type_1966;
        { Type * _ret_val = hoisted__Type_1966;
                return _ret_val; }
    }
    Bool hoisted__Bool_1984 = is(self, &(Type){.tag = Type_TAG_I8});
    (void)hoisted__Bool_1984;
    if (hoisted__Bool_1984) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8;
                return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive *hoisted__Primitive_1985 = Primitive_clone(_clone_payload_Primitive_18);
    (void)hoisted__Primitive_1985;
    Type *hoisted__Type_1986 = Type_Primitive(hoisted__Primitive_1985);
    (void)hoisted__Type_1986;
    return hoisted__Type_1986;
}

U32 Type_size(void) {
    U32 hoisted__U32_1987 = 24;
    (void)hoisted__U32_1987;
    return hoisted__U32_1987;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_3528 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3528;
    if (hoisted__Bool_3528) {
        Type *hoisted__Type_3523 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3523;
        U32 hoisted__U32_3524 = 1;
        (void)hoisted__U32_3524;
        Array *_va_Array_101 = Array_new(hoisted__Type_3523, &hoisted__U32_3524);
        (void)_va_Array_101;
        Type_delete(hoisted__Type_3523, &(Bool){1});
        U32 hoisted__U32_3525 = 0;
        (void)hoisted__U32_3525;
        Str hoisted__Str_3526 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3526;
        Array_set(_va_Array_101, &hoisted__U32_3525, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3526; _oa; }));
        Str hoisted__Str_3527 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3527;
        panic(&hoisted__Str_3527, _va_Array_101);
        Str_delete(&hoisted__Str_3527, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3529 = calloc(DEREF(cap), elem_size);
    (void)hoisted__v_3529;
    void * hoisted__v_3530 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3530;
    void * hoisted__v_3531 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3531;
    Array *hoisted__Array_3532 = malloc(sizeof(Array));
    hoisted__Array_3532->data = hoisted__v_3529;
    hoisted__Array_3532->cap = DEREF(cap);
    hoisted__Array_3532->elem_size = elem_size;
    hoisted__Array_3532->elem_clone = hoisted__v_3530;
    hoisted__Array_3532->elem_delete = hoisted__v_3531;
    (void)hoisted__Array_3532;
    return hoisted__Array_3532;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3533 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3533;
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_3533;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap;
    return _r; }
}

void * Array_get(Array * self, U32 * i) {
    Bool hoisted__Bool_3548 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3548;
    if (hoisted__Bool_3548) {
        Type *hoisted__Type_3535 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3535;
        U32 hoisted__U32_3536 = 5;
        (void)hoisted__U32_3536;
        Array *_va_Array_102 = Array_new(hoisted__Type_3535, &hoisted__U32_3536);
        (void)_va_Array_102;
        Type_delete(hoisted__Type_3535, &(Bool){1});
        U32 hoisted__U32_3537 = 0;
        (void)hoisted__U32_3537;
        Str hoisted__Str_3538 = (Str){.c_str = (void *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3538;
        Array_set(_va_Array_102, &hoisted__U32_3537, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3538; _oa; }));
        U32 hoisted__U32_3539 = 1;
        (void)hoisted__U32_3539;
        Str *hoisted__Str_3540 = U32_to_str(i);
        (void)hoisted__Str_3540;
        Array_set(_va_Array_102, &hoisted__U32_3539, hoisted__Str_3540);
        U32 hoisted__U32_3541 = 2;
        (void)hoisted__U32_3541;
        Str hoisted__Str_3542 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3542;
        Array_set(_va_Array_102, &hoisted__U32_3541, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3542; _oa; }));
        U32 hoisted__U32_3543 = 3;
        (void)hoisted__U32_3543;
        Str *hoisted__Str_3544 = U32_to_str(&self->cap);
        (void)hoisted__Str_3544;
        Array_set(_va_Array_102, &hoisted__U32_3543, hoisted__Str_3544);
        U32 hoisted__U32_3545 = 4;
        (void)hoisted__U32_3545;
        Str hoisted__Str_3546 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3546;
        Array_set(_va_Array_102, &hoisted__U32_3545, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3546; _oa; }));
        Str hoisted__Str_3547 = (Str){.c_str = (void *)"./src/core/array.til:40:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3547;
        panic(&hoisted__Str_3547, _va_Array_102);
        Str_delete(&hoisted__Str_3547, &(Bool){0});
    }
    U32 hoisted__U64_3549 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3549;
    void *hoisted__v_3550 = ptr_add(self->data, hoisted__U64_3549);
    (void)hoisted__v_3550;
    (void)hoisted__v_3550;
    return hoisted__v_3550;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_3565 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3565;
    if (hoisted__Bool_3565) {
        Type *hoisted__Type_3552 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3552;
        U32 hoisted__U32_3553 = 5;
        (void)hoisted__U32_3553;
        Array *_va_Array_103 = Array_new(hoisted__Type_3552, &hoisted__U32_3553);
        (void)_va_Array_103;
        Type_delete(hoisted__Type_3552, &(Bool){1});
        U32 hoisted__U32_3554 = 0;
        (void)hoisted__U32_3554;
        Str hoisted__Str_3555 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3555;
        Array_set(_va_Array_103, &hoisted__U32_3554, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3555; _oa; }));
        U32 hoisted__U32_3556 = 1;
        (void)hoisted__U32_3556;
        Str *hoisted__Str_3557 = U32_to_str(i);
        (void)hoisted__Str_3557;
        Array_set(_va_Array_103, &hoisted__U32_3556, hoisted__Str_3557);
        U32 hoisted__U32_3558 = 2;
        (void)hoisted__U32_3558;
        Str hoisted__Str_3559 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3559;
        Array_set(_va_Array_103, &hoisted__U32_3558, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3559; _oa; }));
        U32 hoisted__U32_3560 = 3;
        (void)hoisted__U32_3560;
        Str *hoisted__Str_3561 = U32_to_str(&self->cap);
        (void)hoisted__Str_3561;
        Array_set(_va_Array_103, &hoisted__U32_3560, hoisted__Str_3561);
        U32 hoisted__U32_3562 = 4;
        (void)hoisted__U32_3562;
        Str hoisted__Str_3563 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3563;
        Array_set(_va_Array_103, &hoisted__U32_3562, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3563; _oa; }));
        Str hoisted__Str_3564 = (Str){.c_str = (void *)"./src/core/array.til:49:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3564;
        panic(&hoisted__Str_3564, _va_Array_103);
        Str_delete(&hoisted__Str_3564, &(Bool){0});
    }
    U32 hoisted__U64_3566 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3566;
    void *hoisted__v_3567 = ptr_add(self->data, hoisted__U64_3566);
    (void)hoisted__v_3567;
    (void)hoisted__v_3567;
    Bool hoisted__Bool_3568 = 0;
    (void)hoisted__Bool_3568;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3567, &hoisted__Bool_3568);
    U32 hoisted__U64_3569 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3569;
    void *hoisted__v_3570 = ptr_add(self->data, hoisted__U64_3569);
    (void)hoisted__v_3570;
    (void)hoisted__v_3570;
    memcpy(hoisted__v_3570, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_3571 = self->cap;
        (void)_re_U32_3571;
        U32 _rc_U32_3571 = 0;
        (void)_rc_U32_3571;
        Bool hoisted__Bool_3580 = U32_lte(&_rc_U32_3571, &_re_U32_3571);
        (void)hoisted__Bool_3580;
        if (hoisted__Bool_3580) {
            while (1) {
                Bool _wcond_Bool_3572 = U32_lt(&_rc_U32_3571, &_re_U32_3571);
                (void)_wcond_Bool_3572;
                if (_wcond_Bool_3572) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3571);
                U32_inc(&_rc_U32_3571);
                U32 hoisted__U64_3573 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3573;
                void *hoisted__v_3574 = ptr_add(self->data, hoisted__U64_3573);
                (void)hoisted__v_3574;
                (void)hoisted__v_3574;
                Bool hoisted__Bool_3575 = 0;
                (void)hoisted__Bool_3575;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3574, &hoisted__Bool_3575);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3576 = U32_gt(&_rc_U32_3571, &_re_U32_3571);
                (void)_wcond_Bool_3576;
                if (_wcond_Bool_3576) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3571);
                U32_dec(&_rc_U32_3571);
                U32 hoisted__U64_3577 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3577;
                void *hoisted__v_3578 = ptr_add(self->data, hoisted__U64_3577);
                (void)hoisted__v_3578;
                (void)hoisted__v_3578;
                Bool hoisted__Bool_3579 = 0;
                (void)hoisted__Bool_3579;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3578, &hoisted__Bool_3579);
            }
        }
    }
    free(self->data);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3593 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3593;
    void * new_data = malloc(hoisted__U64_3593);
    {
        U32 _re_U32_3581 = self->cap;
        (void)_re_U32_3581;
        U32 _rc_U32_3581 = 0;
        (void)_rc_U32_3581;
        Bool hoisted__Bool_3592 = U32_lte(&_rc_U32_3581, &_re_U32_3581);
        (void)hoisted__Bool_3592;
        if (hoisted__Bool_3592) {
            while (1) {
                Bool _wcond_Bool_3582 = U32_lt(&_rc_U32_3581, &_re_U32_3581);
                (void)_wcond_Bool_3582;
                if (_wcond_Bool_3582) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3581);
                U32_inc(&_rc_U32_3581);
                U32 hoisted__U64_3583 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3583;
                void *hoisted__v_3584 = ptr_add(self->data, hoisted__U64_3583);
                (void)hoisted__v_3584;
                (void)hoisted__v_3584;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3584);
                U32 hoisted__U64_3585 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3585;
                void *hoisted__v_3586 = ptr_add(new_data, hoisted__U64_3585);
                (void)hoisted__v_3586;
                (void)hoisted__v_3586;
                memcpy(hoisted__v_3586, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3587 = U32_gt(&_rc_U32_3581, &_re_U32_3581);
                (void)_wcond_Bool_3587;
                if (_wcond_Bool_3587) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3581);
                U32_dec(&_rc_U32_3581);
                U32 hoisted__U64_3588 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3588;
                void *hoisted__v_3589 = ptr_add(self->data, hoisted__U64_3588);
                (void)hoisted__v_3589;
                (void)hoisted__v_3589;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3589);
                U32 hoisted__U64_3590 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3590;
                void *hoisted__v_3591 = ptr_add(new_data, hoisted__U64_3590);
                (void)hoisted__v_3591;
                (void)hoisted__v_3591;
                memcpy(hoisted__v_3591, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3594 = malloc(sizeof(Array));
    hoisted__Array_3594->data = new_data;
    hoisted__Array_3594->cap = self->cap;
    hoisted__Array_3594->elem_size = self->elem_size;
    hoisted__Array_3594->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3594->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3594;
    return hoisted__Array_3594;
}

U32 Array_size(void) {
    U32 hoisted__U32_3595 = 32;
    (void)hoisted__U32_3595;
    return hoisted__U32_3595;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_3833 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_3833;
    U32 hoisted__U32_3834 = 3;
    (void)hoisted__U32_3834;
    Array *_va_Array_120 = Array_new(hoisted__Type_3833, &hoisted__U32_3834);
    (void)_va_Array_120;
    Type_delete(hoisted__Type_3833, &(Bool){1});
    U32 hoisted__U32_3835 = 0;
    (void)hoisted__U32_3835;
    Str *hoisted__Str_3836 = Str_clone(loc_str);
    (void)hoisted__Str_3836;
    Array_set(_va_Array_120, &hoisted__U32_3835, hoisted__Str_3836);
    U32 hoisted__U32_3837 = 1;
    (void)hoisted__U32_3837;
    Str hoisted__Str_3838 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3838;
    Array_set(_va_Array_120, &hoisted__U32_3837, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3838; _oa; }));
    Array *hoisted__Array_3839 = Array_clone(parts);
    (void)hoisted__Array_3839;
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_3840 = 2;
    (void)hoisted__U32_3840;
    Str *hoisted__Str_3841 = format(hoisted__Array_3839);
    (void)hoisted__Str_3841;
    Array_set(_va_Array_120, &hoisted__U32_3840, hoisted__Str_3841);
    println(_va_Array_120);
    I64 hoisted__I64_3842 = 1;
    (void)hoisted__I64_3842;
    exit(hoisted__I64_3842);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_3852 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_3852;
    U32 hoisted__U32_3853 = 1;
    (void)hoisted__U32_3853;
    Array *_va_Array_122 = Array_new(hoisted__Type_3852, &hoisted__U32_3853);
    (void)_va_Array_122;
    Type_delete(hoisted__Type_3852, &(Bool){1});
    U32 hoisted__U32_3854 = 0;
    (void)hoisted__U32_3854;
    Str hoisted__Str_3855 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3855;
    Array_set(_va_Array_122, &hoisted__U32_3854, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3855; _oa; }));
    panic(loc_str, _va_Array_122);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_3861 = not(DEREF(cond));
    (void)hoisted__Bool_3861;
    if (hoisted__Bool_3861) {
        Type *hoisted__Type_3857 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3857;
        U32 hoisted__U32_3858 = 1;
        (void)hoisted__U32_3858;
        Array *_va_Array_123 = Array_new(hoisted__Type_3857, &hoisted__U32_3858);
        (void)_va_Array_123;
        Type_delete(hoisted__Type_3857, &(Bool){1});
        U32 hoisted__U32_3859 = 0;
        (void)hoisted__U32_3859;
        Str hoisted__Str_3860 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3860;
        Array_set(_va_Array_123, &hoisted__U32_3859, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3860; _oa; }));
        panic(loc_str, _va_Array_123);
    }
    Bool hoisted__Bool_3862 = 1;
    (void)hoisted__Bool_3862;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_3862;
    return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_3885 = I64_neq(a, b);
    (void)hoisted__Bool_3885;
    if (hoisted__Bool_3885) {
        Type *hoisted__Type_3873 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3873;
        U32 hoisted__U32_3874 = 5;
        (void)hoisted__U32_3874;
        Array *_va_Array_125 = Array_new(hoisted__Type_3873, &hoisted__U32_3874);
        (void)_va_Array_125;
        Type_delete(hoisted__Type_3873, &(Bool){1});
        U32 hoisted__U32_3875 = 0;
        (void)hoisted__U32_3875;
        Str hoisted__Str_3876 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3876;
        Array_set(_va_Array_125, &hoisted__U32_3875, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3876; _oa; }));
        U32 hoisted__U32_3877 = 1;
        (void)hoisted__U32_3877;
        Str *hoisted__Str_3878 = I64_to_str(a);
        (void)hoisted__Str_3878;
        Array_set(_va_Array_125, &hoisted__U32_3877, hoisted__Str_3878);
        U32 hoisted__U32_3879 = 2;
        (void)hoisted__U32_3879;
        Str hoisted__Str_3880 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3880;
        Array_set(_va_Array_125, &hoisted__U32_3879, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3880; _oa; }));
        U32 hoisted__U32_3881 = 3;
        (void)hoisted__U32_3881;
        Str *hoisted__Str_3882 = I64_to_str(b);
        (void)hoisted__Str_3882;
        Array_set(_va_Array_125, &hoisted__U32_3881, hoisted__Str_3882);
        U32 hoisted__U32_3883 = 4;
        (void)hoisted__U32_3883;
        Str hoisted__Str_3884 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3884;
        Array_set(_va_Array_125, &hoisted__U32_3883, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3884; _oa; }));
        panic(loc_str, _va_Array_125);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_3899 = Str_eq(a, b);
    (void)hoisted__Bool_3899;
    Bool hoisted__Bool_3900 = not(hoisted__Bool_3899);
    (void)hoisted__Bool_3900;
    if (hoisted__Bool_3900) {
        Type *hoisted__Type_3887 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3887;
        U32 hoisted__U32_3888 = 5;
        (void)hoisted__U32_3888;
        Array *_va_Array_126 = Array_new(hoisted__Type_3887, &hoisted__U32_3888);
        (void)_va_Array_126;
        Type_delete(hoisted__Type_3887, &(Bool){1});
        U32 hoisted__U32_3889 = 0;
        (void)hoisted__U32_3889;
        Str hoisted__Str_3890 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3890;
        Array_set(_va_Array_126, &hoisted__U32_3889, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3890; _oa; }));
        U32 hoisted__U32_3891 = 1;
        (void)hoisted__U32_3891;
        Str *hoisted__Str_3892 = Str_clone(a);
        (void)hoisted__Str_3892;
        Array_set(_va_Array_126, &hoisted__U32_3891, hoisted__Str_3892);
        U32 hoisted__U32_3893 = 2;
        (void)hoisted__U32_3893;
        Str hoisted__Str_3894 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3894;
        Array_set(_va_Array_126, &hoisted__U32_3893, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3894; _oa; }));
        U32 hoisted__U32_3895 = 3;
        (void)hoisted__U32_3895;
        Str *hoisted__Str_3896 = Str_clone(b);
        (void)hoisted__Str_3896;
        Array_set(_va_Array_126, &hoisted__U32_3895, hoisted__Str_3896);
        U32 hoisted__U32_3897 = 4;
        (void)hoisted__U32_3897;
        Str hoisted__Str_3898 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3898;
        Array_set(_va_Array_126, &hoisted__U32_3897, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3898; _oa; }));
        panic(loc_str, _va_Array_126);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_3901 = parts;
        (void)_fc_Array_3901;
        (void)_fc_Array_3901;
        U32 _fi_USize_3901 = 0;
        (void)_fi_USize_3901;
        while (1) {
            U32 hoisted__U32_3903; { U32 *_hp = (U32 *)Array_len(_fc_Array_3901); hoisted__U32_3903 = *_hp; free(_hp); }
            (void)hoisted__U32_3903;
            Bool _wcond_Bool_3902 = U32_lt(&_fi_USize_3901, &hoisted__U32_3903);
            (void)_wcond_Bool_3902;
            if (_wcond_Bool_3902) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_3901, &_fi_USize_3901);
            U32 hoisted__U32_3904 = 1;
            (void)hoisted__U32_3904;
            U32 hoisted__U32_3905 = U32_add(_fi_USize_3901, hoisted__U32_3904);
            (void)hoisted__U32_3905;
            _fi_USize_3901 = hoisted__U32_3905;
            print_single(s);
        }
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_4048 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4048;
    I64 hoisted__I64_4049 = 3;
    (void)hoisted__I64_4049;
    assert_eq(&hoisted__Str_4048, &result, &hoisted__I64_4049);
    Str_delete(&hoisted__Str_4048, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4056 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4056;
    I64 hoisted__I64_4057 = 15;
    (void)hoisted__I64_4057;
    assert_eq(&hoisted__Str_4056, &result, &hoisted__I64_4057);
    Str_delete(&hoisted__Str_4056, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4064 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4064;
    I64 hoisted__I64_4065 = 26;
    (void)hoisted__I64_4065;
    assert_eq(&hoisted__Str_4064, &result, &hoisted__I64_4065);
    Str_delete(&hoisted__Str_4064, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4068 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4068;
    Str hoisted__Str_4069 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4069;
    assert_eq_str(&hoisted__Str_4068, &result, &hoisted__Str_4069);
    Str_delete(&hoisted__Str_4068, &(Bool){0});
    Str_delete(&hoisted__Str_4069, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4400 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4400;
    assert_eq_str(&hoisted__Str_4400, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4400, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_4401 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4401;
    assert_eq_str(&hoisted__Str_4401, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4401, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4403 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4403;
    I64 hoisted__I64_4404 = 8;
    (void)hoisted__I64_4404;
    assert_eq(&hoisted__Str_4403, &result, &hoisted__I64_4404);
    Str_delete(&hoisted__Str_4403, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4407 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4407;
    Bool hoisted__Bool_4408 = 1;
    (void)hoisted__Bool_4408;
    Bool_delete(assert(&hoisted__Str_4407, &hoisted__Bool_4408), &(Bool){1});
    Str_delete(&hoisted__Str_4407, &(Bool){0});
    Str hoisted__Str_4412 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4412;
    Bool hoisted__Bool_4413 = 1;
    (void)hoisted__Bool_4413;
    Bool_delete(assert(&hoisted__Str_4412, &hoisted__Bool_4413), &(Bool){1});
    Str_delete(&hoisted__Str_4412, &(Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4419 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4419;
    Str hoisted__Str_4420 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4420;
    Str hoisted__Str_4421 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4421;
    assert_eq_str(&hoisted__Str_4419, &hoisted__Str_4420, &hoisted__Str_4421);
    Str_delete(&hoisted__Str_4419, &(Bool){0});
    Str_delete(&hoisted__Str_4420, &(Bool){0});
    Str_delete(&hoisted__Str_4421, &(Bool){0});
    Str hoisted__Str_4424 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4424;
    Str hoisted__Str_4425 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4425;
    Str hoisted__Str_4426 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4426;
    assert_eq_str(&hoisted__Str_4424, &hoisted__Str_4425, &hoisted__Str_4426);
    Str_delete(&hoisted__Str_4424, &(Bool){0});
    Str_delete(&hoisted__Str_4425, &(Bool){0});
    Str_delete(&hoisted__Str_4426, &(Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4431 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4431;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4431;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4432 = 16;
    (void)hoisted__U32_4432;
    return hoisted__U32_4432;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4433 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4433;
    I64 hoisted__I64_4434 = 42;
    (void)hoisted__I64_4434;
    assert_eq(&hoisted__Str_4433, &v.x, &hoisted__I64_4434);
    Str_delete(&hoisted__Str_4433, &(Bool){0});
    Str hoisted__Str_4435 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4435;
    I64 hoisted__I64_4436 = 99;
    (void)hoisted__I64_4436;
    assert_eq(&hoisted__Str_4435, &v.y, &hoisted__I64_4436);
    Str_delete(&hoisted__Str_4435, &(Bool){0});
    CfVec2_delete(&v, &(Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4439 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4439;
    I64 hoisted__I64_4440 = 10;
    (void)hoisted__I64_4440;
    assert_eq(&hoisted__Str_4439, &p.x, &hoisted__I64_4440);
    Str_delete(&hoisted__Str_4439, &(Bool){0});
    Str hoisted__Str_4441 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4441;
    I64 hoisted__I64_4442 = 20;
    (void)hoisted__I64_4442;
    assert_eq(&hoisted__Str_4441, &p.y, &hoisted__I64_4442);
    Str_delete(&hoisted__Str_4441, &(Bool){0});
    CfVec2_delete(&p, &(Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4448 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4448;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4448;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4449 = 32;
    (void)hoisted__U32_4449;
    return hoisted__U32_4449;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4450 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4450;
    I64 hoisted__I64_4451 = 5;
    (void)hoisted__I64_4451;
    assert_eq(&hoisted__Str_4450, &r.top_left.x, &hoisted__I64_4451);
    Str_delete(&hoisted__Str_4450, &(Bool){0});
    Str hoisted__Str_4452 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4452;
    I64 hoisted__I64_4453 = 10;
    (void)hoisted__I64_4453;
    assert_eq(&hoisted__Str_4452, &r.top_left.y, &hoisted__I64_4453);
    Str_delete(&hoisted__Str_4452, &(Bool){0});
    Str hoisted__Str_4454 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4454;
    I64 hoisted__I64_4455 = 100;
    (void)hoisted__I64_4455;
    assert_eq(&hoisted__Str_4454, &r.bottom_right.x, &hoisted__I64_4455);
    Str_delete(&hoisted__Str_4454, &(Bool){0});
    Str hoisted__Str_4456 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4456;
    I64 hoisted__I64_4457 = 200;
    (void)hoisted__I64_4457;
    assert_eq(&hoisted__Str_4456, &r.bottom_right.y, &hoisted__I64_4457);
    Str_delete(&hoisted__Str_4456, &(Bool){0});
    CfRect_delete(&r, &(Bool){0});
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
    Bool hoisted__Bool_4462 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4462;
    if (hoisted__Bool_4462) {
        Bool hoisted__Bool_4459 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4459;
        { Bool _ret_val = hoisted__Bool_4459;
                return _ret_val; }
    }
    Bool hoisted__Bool_4463 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4463;
    if (hoisted__Bool_4463) {
        Bool hoisted__Bool_4460 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4460;
        { Bool _ret_val = hoisted__Bool_4460;
                return _ret_val; }
    }
    Bool hoisted__Bool_4464 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4464;
    if (hoisted__Bool_4464) {
        Bool hoisted__Bool_4461 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4461;
        { Bool _ret_val = hoisted__Bool_4461;
                return _ret_val; }
    }
    Bool hoisted__Bool_4465 = 0;
    (void)hoisted__Bool_4465;
    return hoisted__Bool_4465;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4473 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4473;
    if (hoisted__Bool_4473) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4474 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4474;
    if (hoisted__Bool_4474) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4475 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4475;
    if (hoisted__Bool_4475) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4476 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4476;
    UNREACHABLE(&hoisted__Str_4476);
    Str_delete(&hoisted__Str_4476, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4477 = 4;
    (void)hoisted__U32_4477;
    return hoisted__U32_4477;
}


void test_enum_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Str hoisted__Str_4478 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4478;
    Bool hoisted__Bool_4479 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4479;
    Bool_delete(assert(&hoisted__Str_4478, &hoisted__Bool_4479), &(Bool){1});
    Str_delete(&hoisted__Str_4478, &(Bool){0});
    Bool hoisted__Bool_4481 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4481;
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_4482 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4482;
    Bool hoisted__Bool_4483 = not(hoisted__Bool_4481);
    (void)hoisted__Bool_4483;
    Bool_delete(assert(&hoisted__Str_4482, &hoisted__Bool_4483), &(Bool){1});
    Str_delete(&hoisted__Str_4482, &(Bool){0});
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
    Bool hoisted__Bool_4485 = is(self, other);
    (void)hoisted__Bool_4485;
    return hoisted__Bool_4485;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_4503 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4503;
    if (hoisted__Bool_4503) {
        I64 *hoisted__I64_4499 = get_payload(self);
        (void)hoisted__I64_4499;
        (void)hoisted__I64_4499;
        Bool hoisted__Bool_4500 = 0;
        (void)hoisted__Bool_4500;
        I64_delete(hoisted__I64_4499, &hoisted__Bool_4500);
    }
    Bool hoisted__Bool_4504 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4504;
    if (hoisted__Bool_4504) {
        Str *hoisted__Str_4501 = get_payload(self);
        (void)hoisted__Str_4501;
        (void)hoisted__Str_4501;
        Bool hoisted__Bool_4502 = 0;
        (void)hoisted__Bool_4502;
        Str_delete(hoisted__Str_4501, &hoisted__Bool_4502);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4533 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4533;
    if (hoisted__Bool_4533) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4530 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4530;
        { Token * _ret_val = hoisted__Token_4530;
                return _ret_val; }
    }
    Bool hoisted__Bool_4534 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4534;
    if (hoisted__Bool_4534) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4531 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4531;
        Token *hoisted__Token_4532 = Token_Name(hoisted__Str_4531);
        (void)hoisted__Token_4532;
        { Token * _ret_val = hoisted__Token_4532;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4535 = 24;
    (void)hoisted__U32_4535;
    return hoisted__U32_4535;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_4537 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4537;
    Bool hoisted__Bool_4538 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4538;
    Bool_delete(assert(&hoisted__Str_4537, &hoisted__Bool_4538), &(Bool){1});
    Str_delete(&hoisted__Str_4537, &(Bool){0});
    Bool hoisted__Bool_4540 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4540;
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_4541 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4541;
    Bool hoisted__Bool_4542 = not(hoisted__Bool_4540);
    (void)hoisted__Bool_4542;
    Bool_delete(assert(&hoisted__Str_4541, &hoisted__Bool_4542), &(Bool){1});
    Str_delete(&hoisted__Str_4541, &(Bool){0});
}

void test_enum_return_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Green});
    Str hoisted__Str_4544 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4544;
    Bool hoisted__Bool_4545 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4545;
    Bool_delete(assert(&hoisted__Str_4544, &hoisted__Bool_4545), &(Bool){1});
    Str_delete(&hoisted__Str_4544, &(Bool){0});
    Bool hoisted__Bool_4547 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4547;
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_4548 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4548;
    Bool hoisted__Bool_4549 = not(hoisted__Bool_4547);
    (void)hoisted__Bool_4549;
    Bool_delete(assert(&hoisted__Str_4548, &hoisted__Bool_4549), &(Bool){1});
    Str_delete(&hoisted__Str_4548, &(Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_4553 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4553;
    Bool hoisted__Bool_4554 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4554;
    Bool_delete(assert(&hoisted__Str_4553, &hoisted__Bool_4554), &(Bool){1});
    Str_delete(&hoisted__Str_4553, &(Bool){0});
    Bool hoisted__Bool_4556 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4556;
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_4557 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4557;
    Bool hoisted__Bool_4558 = not(hoisted__Bool_4556);
    (void)hoisted__Bool_4558;
    Bool_delete(assert(&hoisted__Str_4557, &hoisted__Bool_4558), &(Bool){1});
    Str_delete(&hoisted__Str_4557, &(Bool){0});
}

void *F32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = F32_cmp(*(F32 *)_a0, *(F32 *)_a1); return _r;
}
void *F32_clone_dyn(void *_a0) {
    F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(_a0); return _r;
}
void *U64_add_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_add(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_sub_dyn(void *_a0, void *_a1) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_sub(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U64_cmp(*(U64 *)_a0, *(U64 *)_a1); return _r;
}
void *U64_clone_dyn(void *_a0) {
    U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(_a0); return _r;
}
void *U32_to_i64_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = U32_to_i64(*(U32 *)_a0); return _r;
}
void *U32_add_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_add(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_sub_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_sub(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_mul_dyn(void *_a0, void *_a1) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_mul(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_eq(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U32_cmp(*(U32 *)_a0, *(U32 *)_a1); return _r;
}
void *U32_clone_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(_a0); return _r;
}
void *U32_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_lt(_a0, _a1); return _r;
}
void *U32_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_gt(_a0, _a1); return _r;
}
void *U32_lte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_lte(_a0, _a1); return _r;
}
void *U32_gte_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = U32_gte(_a0, _a1); return _r;
}
void *I32_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I32_cmp(*(I32 *)_a0, *(I32 *)_a1); return _r;
}
void *I32_clone_dyn(void *_a0) {
    I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(_a0); return _r;
}
void *I8_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I8_cmp(*(I8 *)_a0, *(I8 *)_a1); return _r;
}
void *I8_clone_dyn(void *_a0) {
    I8 *_r = malloc(sizeof(I8)); *_r = I8_clone(_a0); return _r;
}
void *U8_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = U8_cmp(*(U8 *)_a0, *(U8 *)_a1); return _r;
}
void *U8_clone_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(_a0); return _r;
}
void *Str_len_dyn(void *_a0) {
    U32 *_r = malloc(sizeof(U32)); *_r = Str_len(_a0); return _r;
}
void *Str_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = Str_cmp(_a0, _a1); return _r;
}
void *Str_is_empty_dyn(void *_a0) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_is_empty(_a0); return _r;
}
void *Str_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Str_size(); return _r;
}
void *Str_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Str_eq(_a0, _a1); return _r;
}
void *I64_to_u8_dyn(void *_a0) {
    U8 *_r = malloc(sizeof(U8)); *_r = I64_to_u8(*(I64 *)_a0); return _r;
}
void *I64_add_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_add(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_sub_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_sub(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_div_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_div(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_mod_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_mod(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_eq(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_cmp_dyn(void *_a0, void *_a1) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_cmp(*(I64 *)_a0, *(I64 *)_a1); return _r;
}
void *I64_clone_dyn(void *_a0) {
    I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(_a0); return _r;
}
void *I64_lt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_lt(_a0, _a1); return _r;
}
void *I64_gt_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_gt(_a0, _a1); return _r;
}
void *I64_neq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = I64_neq(_a0, _a1); return _r;
}
void *Bool_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_eq(*(Bool *)_a0, *(Bool *)_a1); return _r;
}
void *Bool_clone_dyn(void *_a0) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(_a0); return _r;
}
void *Primitive_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Primitive_eq(_a0, _a1); return _r;
}
void *Primitive_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Primitive_size(); return _r;
}
void *Type_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Type_size(); return _r;
}
void *Array_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Array_size(); return _r;
}
void *CfVec2_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = CfVec2_size(); return _r;
}
void *CfRect_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = CfRect_size(); return _r;
}
void *Color_eq_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Color_eq(_a0, _a1); return _r;
}
void *Color_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Color_size(); return _r;
}
void *Token_is_dyn(void *_a0, void *_a1) {
    Bool *_r = malloc(sizeof(Bool)); *_r = Token_is(_a0, _a1); return _r;
}
void *Token_size_dyn(void) {
    U32 *_r = malloc(sizeof(U32)); *_r = Token_size(); return _r;
}
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)F32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)F32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)F32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)F32_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U64_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U64_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)U32_to_i64_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)U32_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)U32_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)U32_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)U32_mul_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)U32_inc;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)U32_dec;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)U32_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U32_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)U32_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)U32_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)U32_lte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)U32_gte_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I32_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I32_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I32_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I32_size;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I8_delete;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I8_size;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)U8_cmp_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)U8_clone_dyn;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)U8_delete;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)U8_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Str_len_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Str_get;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Str_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)Str_with_capacity;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)Str_push_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Str_clone;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Str_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_empty", 8ULL) == 0) return (void*)Str_is_empty_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Str_size_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Str_eq_dyn;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Dynamic_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)I64_to_str;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "to_u8", 5ULL) == 0) return (void*)I64_to_u8_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)I64_add_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)I64_sub_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)I64_div_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)I64_mod_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)I64_eq_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)I64_cmp_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)I64_clone_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)I64_delete;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)I64_size;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)I64_lt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)I64_gt_dyn;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)I64_neq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Bool_eq_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)Bool_cmp;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Bool_clone_dyn;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Bool_delete;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Bool_size;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Primitive_eq_dyn;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Primitive_delete;
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
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Type_delete;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Type_clone;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Type_size_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "new_type_name", 13ULL) == 0) return (void*)Array_new_type_name;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)Array_new;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)Array_len;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)Array_get;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)Array_set;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Array_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Array_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Array_size_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)CfVec2_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)CfVec2_delete;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)CfVec2_size_dyn;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)CfRect_clone;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)CfRect_delete;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)CfRect_size_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)Color_eq_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Color_delete;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)Color_clone;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)Color_size_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Num", 3ULL) == 0) return (void*)Token_Num;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Name", 4ULL) == 0) return (void*)Token_Name;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Eof", 3ULL) == 0) return (void*)Token_Eof;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "is", 2ULL) == 0) return (void*)Token_is_dyn;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)Token_delete;
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
