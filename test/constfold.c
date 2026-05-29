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
    U32 hoisted__U32_1203 = 16;
    (void)hoisted__U32_1203;
    return hoisted__U32_1203;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1204 = Str_cmp(a, b);
    (void)hoisted__I64_1204;
    I64 hoisted__I64_1205 = 0;
    (void)hoisted__I64_1205;
    Bool hoisted__Bool_1206 = I64_eq(hoisted__I64_1204, hoisted__I64_1205);
    (void)hoisted__Bool_1206;
    return hoisted__Bool_1206;
}

U32 * Dynamic_size(void) {
    U32 hoisted__U32_1293 = 8;
    (void)hoisted__U32_1293;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1293;
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
    I64 hoisted__I64_1497 = 0;
    (void)hoisted__I64_1497;
    Bool hoisted__Bool_1498 = I64_eq(DEREF(val), hoisted__I64_1497);
    (void)hoisted__Bool_1498;
    if (hoisted__Bool_1498) {
        U64 hoisted__U64_1461 = 2;
        (void)hoisted__U64_1461;
        void * buf = malloc(hoisted__U64_1461);
        I64 hoisted__I64_1462 = 48;
        (void)hoisted__I64_1462;
        U64 hoisted__U64_1463 = 1;
        (void)hoisted__U64_1463;
        memcpy(buf, &hoisted__I64_1462, hoisted__U64_1463);
        U64 hoisted__U64_1464 = 1;
        (void)hoisted__U64_1464;
        void *hoisted__v_1465 = ptr_add(buf, hoisted__U64_1464);
        (void)hoisted__v_1465;
        (void)hoisted__v_1465;
        I32 hoisted__I32_1466 = 0;
        (void)hoisted__I32_1466;
        U64 hoisted__U64_1467 = 1;
        (void)hoisted__U64_1467;
        memset(hoisted__v_1465, hoisted__I32_1466, hoisted__U64_1467);
        I32_delete(&hoisted__I32_1466, &(Bool){0});
        I64 hoisted__I64_1468 = 1;
        (void)hoisted__I64_1468;
        I64 hoisted__I64_1469 = 1;
        (void)hoisted__I64_1469;
        Str *hoisted__Str_1470 = malloc(sizeof(Str));
        hoisted__Str_1470->c_str = buf;
        hoisted__Str_1470->count = hoisted__I64_1468;
        hoisted__Str_1470->cap = hoisted__I64_1469;
        (void)hoisted__Str_1470;
        { Str * _ret_val = hoisted__Str_1470;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_1499 = 0;
    (void)hoisted__I64_1499;
    Bool hoisted__Bool_1500 = I64_lt(val, &hoisted__I64_1499);
    (void)hoisted__Bool_1500;
    if (hoisted__Bool_1500) {
        Bool hoisted__Bool_1471 = 1;
        (void)hoisted__Bool_1471;
        is_neg = hoisted__Bool_1471;
        I64 hoisted__I64_1472 = 0;
        (void)hoisted__I64_1472;
        I64 hoisted__I64_1473 = I64_sub(hoisted__I64_1472, DEREF(val));
        (void)hoisted__I64_1473;
        v = hoisted__I64_1473;
    }
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1475 = 0;
        (void)hoisted__I64_1475;
        Bool _wcond_Bool_1474 = I64_gt(&tmp, &hoisted__I64_1475);
        (void)_wcond_Bool_1474;
        if (_wcond_Bool_1474) {
        } else {
            break;
        }
        U64 hoisted__U64_1476 = 1;
        (void)hoisted__U64_1476;
        U64 hoisted__U64_1477 = U64_add(ndigits, hoisted__U64_1476);
        (void)hoisted__U64_1477;
        ndigits = hoisted__U64_1477;
        I64 hoisted__I64_1478 = 10;
        (void)hoisted__I64_1478;
        I64 hoisted__I64_1479 = I64_div(tmp, hoisted__I64_1478);
        (void)hoisted__I64_1479;
        tmp = hoisted__I64_1479;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1480 = 1;
        (void)hoisted__U64_1480;
        U64 hoisted__U64_1481 = U64_add(total, hoisted__U64_1480);
        (void)hoisted__U64_1481;
        total = hoisted__U64_1481;
    }
    U64 hoisted__U64_1501 = 1;
    (void)hoisted__U64_1501;
    U64 hoisted__U64_1502 = U64_add(total, hoisted__U64_1501);
    (void)hoisted__U64_1502;
    void * buf = malloc(hoisted__U64_1502);
    if (is_neg) {
        I64 hoisted__I64_1482 = 45;
        (void)hoisted__I64_1482;
        U64 hoisted__U64_1483 = 1;
        (void)hoisted__U64_1483;
        memcpy(buf, &hoisted__I64_1482, hoisted__U64_1483);
    }
    U64 hoisted__U64_1503 = 1;
    (void)hoisted__U64_1503;
    U64 i = U64_sub(total, hoisted__U64_1503);
    while (1) {
        I64 hoisted__I64_1485 = 0;
        (void)hoisted__I64_1485;
        Bool _wcond_Bool_1484 = I64_gt(&v, &hoisted__I64_1485);
        (void)_wcond_Bool_1484;
        if (_wcond_Bool_1484) {
        } else {
            break;
        }
        I64 hoisted__I64_1486 = 10;
        (void)hoisted__I64_1486;
        I64 hoisted__I64_1487 = I64_mod(v, hoisted__I64_1486);
        (void)hoisted__I64_1487;
        I64 hoisted__I64_1488 = 48;
        (void)hoisted__I64_1488;
        I64 hoisted__I64_1489 = I64_add(hoisted__I64_1487, hoisted__I64_1488);
        (void)hoisted__I64_1489;
        void *hoisted__v_1490 = ptr_add(buf, i);
        (void)hoisted__v_1490;
        (void)hoisted__v_1490;
        U8 hoisted__U8_1491 = I64_to_u8(hoisted__I64_1489);
        (void)hoisted__U8_1491;
        U64 hoisted__U64_1492 = 1;
        (void)hoisted__U64_1492;
        memcpy(hoisted__v_1490, &hoisted__U8_1491, hoisted__U64_1492);
        U8_delete(&hoisted__U8_1491, &(Bool){0});
        I64 hoisted__I64_1493 = 10;
        (void)hoisted__I64_1493;
        I64 hoisted__I64_1494 = I64_div(v, hoisted__I64_1493);
        (void)hoisted__I64_1494;
        v = hoisted__I64_1494;
        U64 hoisted__U64_1495 = 1;
        (void)hoisted__U64_1495;
        U64 hoisted__U64_1496 = U64_sub(i, hoisted__U64_1495);
        (void)hoisted__U64_1496;
        i = hoisted__U64_1496;
    }
    void *hoisted__v_1504 = ptr_add(buf, total);
    (void)hoisted__v_1504;
    (void)hoisted__v_1504;
    I32 hoisted__I32_1505 = 0;
    (void)hoisted__I32_1505;
    U64 hoisted__U64_1506 = 1;
    (void)hoisted__U64_1506;
    memset(hoisted__v_1504, hoisted__I32_1505, hoisted__U64_1506);
    I32_delete(&hoisted__I32_1505, &(Bool){0});
    Str *hoisted__Str_1507 = malloc(sizeof(Str));
    hoisted__Str_1507->c_str = buf;
    hoisted__Str_1507->count = total;
    hoisted__Str_1507->cap = total;
    (void)hoisted__Str_1507;
    return hoisted__Str_1507;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    U32 hoisted__U32_1525 = 8;
    (void)hoisted__U32_1525;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1525;
    return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1658 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1658;
    I64 hoisted__I64_1659 = -1;
    (void)hoisted__I64_1659;
    Bool hoisted__Bool_1660 = I64_eq(hoisted__I64_1658, hoisted__I64_1659);
    (void)hoisted__Bool_1660;
    return hoisted__Bool_1660;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1661 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1661;
    I64 hoisted__I64_1662 = 1;
    (void)hoisted__I64_1662;
    Bool hoisted__Bool_1663 = I64_eq(hoisted__I64_1661, hoisted__I64_1662);
    (void)hoisted__Bool_1663;
    return hoisted__Bool_1663;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1664 = I64_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1664;
    Bool hoisted__Bool_1665 = not(hoisted__Bool_1664);
    (void)hoisted__Bool_1665;
    return hoisted__Bool_1665;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1679 = Bool_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1679;
    if (hoisted__Bool_1679) {
        I64 hoisted__I64_1677 = 0;
        (void)hoisted__I64_1677;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1677;
                return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1678 = -1;
        (void)hoisted__I64_1678;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1678;
        return _r; }
    }
    I64 hoisted__I64_1680 = 1;
    (void)hoisted__I64_1680;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1680;
    return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    U32 hoisted__U32_1681 = 1;
    (void)hoisted__U32_1681;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1681;
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
    Bool hoisted__Bool_1820 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1820;
    if (hoisted__Bool_1820) {
        Bool hoisted__Bool_1818 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1818;
        { Bool _ret_val = hoisted__Bool_1818;
                return _ret_val; }
    }
    Bool hoisted__Bool_1821 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1821;
    if (hoisted__Bool_1821) {
        Bool hoisted__Bool_1819 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1819;
        { Bool _ret_val = hoisted__Bool_1819;
                return _ret_val; }
    }
    Bool hoisted__Bool_1822 = 0;
    (void)hoisted__Bool_1822;
    return hoisted__Bool_1822;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1828 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1828;
    if (hoisted__Bool_1828) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1829 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1829;
    if (hoisted__Bool_1829) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Str hoisted__Str_1830 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1830;
    UNREACHABLE(&hoisted__Str_1830);
    Str_delete(&hoisted__Str_1830, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1831 = 4;
    (void)hoisted__U32_1831;
    return hoisted__U32_1831;
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
    Bool hoisted__Bool_1894 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1894;
    if (hoisted__Bool_1894) {
        Str *hoisted__Str_1886 = get_payload(self);
        (void)hoisted__Str_1886;
        (void)hoisted__Str_1886;
        Bool hoisted__Bool_1887 = 0;
        (void)hoisted__Bool_1887;
        Str_delete(hoisted__Str_1886, &hoisted__Bool_1887);
    }
    Bool hoisted__Bool_1895 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1895;
    if (hoisted__Bool_1895) {
        Str *hoisted__Str_1888 = get_payload(self);
        (void)hoisted__Str_1888;
        (void)hoisted__Str_1888;
        Bool hoisted__Bool_1889 = 0;
        (void)hoisted__Bool_1889;
        Str_delete(hoisted__Str_1888, &hoisted__Bool_1889);
    }
    Bool hoisted__Bool_1896 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1896;
    if (hoisted__Bool_1896) {
        Str *hoisted__Str_1890 = get_payload(self);
        (void)hoisted__Str_1890;
        (void)hoisted__Str_1890;
        Bool hoisted__Bool_1891 = 0;
        (void)hoisted__Bool_1891;
        Str_delete(hoisted__Str_1890, &hoisted__Bool_1891);
    }
    Bool hoisted__Bool_1897 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1897;
    if (hoisted__Bool_1897) {
        Primitive *hoisted__Primitive_1892 = get_payload(self);
        (void)hoisted__Primitive_1892;
        (void)hoisted__Primitive_1892;
        Bool hoisted__Bool_1893 = 0;
        (void)hoisted__Bool_1893;
        Primitive_delete(hoisted__Primitive_1892, &hoisted__Bool_1893);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1979 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_1979;
    if (hoisted__Bool_1979) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_1980 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_1980;
    if (hoisted__Bool_1980) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_1981 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)hoisted__Bool_1981;
    if (hoisted__Bool_1981) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1982 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)hoisted__Bool_1982;
    if (hoisted__Bool_1982) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1983 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)hoisted__Bool_1983;
    if (hoisted__Bool_1983) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1984 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)hoisted__Bool_1984;
    if (hoisted__Bool_1984) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1985 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)hoisted__Bool_1985;
    if (hoisted__Bool_1985) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1986 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)hoisted__Bool_1986;
    if (hoisted__Bool_1986) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1987 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)hoisted__Bool_1987;
    if (hoisted__Bool_1987) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool;
                return _r; }
    }
    Bool hoisted__Bool_1988 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1988;
    if (hoisted__Bool_1988) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_1973 = Str_clone(_clone_payload_Struct_9);
        (void)hoisted__Str_1973;
        Type *hoisted__Type_1974 = Type_Struct(hoisted__Str_1973);
        (void)hoisted__Type_1974;
        { Type * _ret_val = hoisted__Type_1974;
                return _ret_val; }
    }
    Bool hoisted__Bool_1989 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_1989;
    if (hoisted__Bool_1989) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_1990 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1990;
    if (hoisted__Bool_1990) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_1975 = Str_clone(_clone_payload_Enum_11);
        (void)hoisted__Str_1975;
        Type *hoisted__Type_1976 = Type_Enum(hoisted__Str_1975);
        (void)hoisted__Type_1976;
        { Type * _ret_val = hoisted__Type_1976;
                return _ret_val; }
    }
    Bool hoisted__Bool_1991 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_1991;
    if (hoisted__Bool_1991) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_1992 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_1992;
    if (hoisted__Bool_1992) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_1993 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_1993;
    if (hoisted__Bool_1993) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_1994 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_1994;
    if (hoisted__Bool_1994) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_1995 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1995;
    if (hoisted__Bool_1995) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_1977 = Str_clone(_clone_payload_Custom_16);
        (void)hoisted__Str_1977;
        Type *hoisted__Type_1978 = Type_Custom(hoisted__Str_1977);
        (void)hoisted__Type_1978;
        { Type * _ret_val = hoisted__Type_1978;
                return _ret_val; }
    }
    Bool hoisted__Bool_1996 = is(self, &(Type){.tag = Type_TAG_I8});
    (void)hoisted__Bool_1996;
    if (hoisted__Bool_1996) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8;
                return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive *hoisted__Primitive_1997 = Primitive_clone(_clone_payload_Primitive_18);
    (void)hoisted__Primitive_1997;
    Type *hoisted__Type_1998 = Type_Primitive(hoisted__Primitive_1997);
    (void)hoisted__Type_1998;
    return hoisted__Type_1998;
}

U32 Type_size(void) {
    U32 hoisted__U32_1999 = 24;
    (void)hoisted__U32_1999;
    return hoisted__U32_1999;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_3563 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3563;
    if (hoisted__Bool_3563) {
        Type *hoisted__Type_3558 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3558;
        U32 hoisted__U32_3559 = 1;
        (void)hoisted__U32_3559;
        Array *_va_Array_101 = Array_new(hoisted__Type_3558, &hoisted__U32_3559);
        (void)_va_Array_101;
        Type_delete(hoisted__Type_3558, &(Bool){1});
        U32 hoisted__U32_3560 = 0;
        (void)hoisted__U32_3560;
        Str hoisted__Str_3561 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3561;
        Array_set(_va_Array_101, &hoisted__U32_3560, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3561; _oa; }));
        Str hoisted__Str_3562 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3562;
        panic(&hoisted__Str_3562, _va_Array_101);
        Str_delete(&hoisted__Str_3562, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3564 = calloc(DEREF(cap), elem_size);
    (void)hoisted__v_3564;
    void * hoisted__v_3565 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3565;
    void * hoisted__v_3566 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3566;
    Array *hoisted__Array_3567 = malloc(sizeof(Array));
    hoisted__Array_3567->data = hoisted__v_3564;
    hoisted__Array_3567->cap = DEREF(cap);
    hoisted__Array_3567->elem_size = elem_size;
    hoisted__Array_3567->elem_clone = hoisted__v_3565;
    hoisted__Array_3567->elem_delete = hoisted__v_3566;
    (void)hoisted__Array_3567;
    return hoisted__Array_3567;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3568 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3568;
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_3568;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap;
    return _r; }
}

void * Array_get(Array * self, U32 * i) {
    Bool hoisted__Bool_3583 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3583;
    if (hoisted__Bool_3583) {
        Type *hoisted__Type_3570 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3570;
        U32 hoisted__U32_3571 = 5;
        (void)hoisted__U32_3571;
        Array *_va_Array_102 = Array_new(hoisted__Type_3570, &hoisted__U32_3571);
        (void)_va_Array_102;
        Type_delete(hoisted__Type_3570, &(Bool){1});
        U32 hoisted__U32_3572 = 0;
        (void)hoisted__U32_3572;
        Str hoisted__Str_3573 = (Str){.c_str = (void *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3573;
        Array_set(_va_Array_102, &hoisted__U32_3572, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3573; _oa; }));
        U32 hoisted__U32_3574 = 1;
        (void)hoisted__U32_3574;
        Str *hoisted__Str_3575 = U32_to_str(i);
        (void)hoisted__Str_3575;
        Array_set(_va_Array_102, &hoisted__U32_3574, hoisted__Str_3575);
        U32 hoisted__U32_3576 = 2;
        (void)hoisted__U32_3576;
        Str hoisted__Str_3577 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3577;
        Array_set(_va_Array_102, &hoisted__U32_3576, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3577; _oa; }));
        U32 hoisted__U32_3578 = 3;
        (void)hoisted__U32_3578;
        Str *hoisted__Str_3579 = U32_to_str(&self->cap);
        (void)hoisted__Str_3579;
        Array_set(_va_Array_102, &hoisted__U32_3578, hoisted__Str_3579);
        U32 hoisted__U32_3580 = 4;
        (void)hoisted__U32_3580;
        Str hoisted__Str_3581 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3581;
        Array_set(_va_Array_102, &hoisted__U32_3580, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3581; _oa; }));
        Str hoisted__Str_3582 = (Str){.c_str = (void *)"./src/core/array.til:40:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3582;
        panic(&hoisted__Str_3582, _va_Array_102);
        Str_delete(&hoisted__Str_3582, &(Bool){0});
    }
    U32 hoisted__U64_3584 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3584;
    void *hoisted__v_3585 = ptr_add(self->data, hoisted__U64_3584);
    (void)hoisted__v_3585;
    (void)hoisted__v_3585;
    return hoisted__v_3585;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_3600 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3600;
    if (hoisted__Bool_3600) {
        Type *hoisted__Type_3587 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3587;
        U32 hoisted__U32_3588 = 5;
        (void)hoisted__U32_3588;
        Array *_va_Array_103 = Array_new(hoisted__Type_3587, &hoisted__U32_3588);
        (void)_va_Array_103;
        Type_delete(hoisted__Type_3587, &(Bool){1});
        U32 hoisted__U32_3589 = 0;
        (void)hoisted__U32_3589;
        Str hoisted__Str_3590 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3590;
        Array_set(_va_Array_103, &hoisted__U32_3589, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3590; _oa; }));
        U32 hoisted__U32_3591 = 1;
        (void)hoisted__U32_3591;
        Str *hoisted__Str_3592 = U32_to_str(i);
        (void)hoisted__Str_3592;
        Array_set(_va_Array_103, &hoisted__U32_3591, hoisted__Str_3592);
        U32 hoisted__U32_3593 = 2;
        (void)hoisted__U32_3593;
        Str hoisted__Str_3594 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3594;
        Array_set(_va_Array_103, &hoisted__U32_3593, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3594; _oa; }));
        U32 hoisted__U32_3595 = 3;
        (void)hoisted__U32_3595;
        Str *hoisted__Str_3596 = U32_to_str(&self->cap);
        (void)hoisted__Str_3596;
        Array_set(_va_Array_103, &hoisted__U32_3595, hoisted__Str_3596);
        U32 hoisted__U32_3597 = 4;
        (void)hoisted__U32_3597;
        Str hoisted__Str_3598 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3598;
        Array_set(_va_Array_103, &hoisted__U32_3597, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3598; _oa; }));
        Str hoisted__Str_3599 = (Str){.c_str = (void *)"./src/core/array.til:49:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3599;
        panic(&hoisted__Str_3599, _va_Array_103);
        Str_delete(&hoisted__Str_3599, &(Bool){0});
    }
    U32 hoisted__U64_3601 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3601;
    void *hoisted__v_3602 = ptr_add(self->data, hoisted__U64_3601);
    (void)hoisted__v_3602;
    (void)hoisted__v_3602;
    Bool hoisted__Bool_3603 = 0;
    (void)hoisted__Bool_3603;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3602, &hoisted__Bool_3603);
    U32 hoisted__U64_3604 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3604;
    void *hoisted__v_3605 = ptr_add(self->data, hoisted__U64_3604);
    (void)hoisted__v_3605;
    (void)hoisted__v_3605;
    memcpy(hoisted__v_3605, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_3606 = self->cap;
        (void)_re_U32_3606;
        U32 _rc_U32_3606 = 0;
        (void)_rc_U32_3606;
        Bool hoisted__Bool_3615 = U32_lte(&_rc_U32_3606, &_re_U32_3606);
        (void)hoisted__Bool_3615;
        if (hoisted__Bool_3615) {
            while (1) {
                Bool _wcond_Bool_3607 = U32_lt(&_rc_U32_3606, &_re_U32_3606);
                (void)_wcond_Bool_3607;
                if (_wcond_Bool_3607) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3606);
                U32_inc(&_rc_U32_3606);
                U32 hoisted__U64_3608 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3608;
                void *hoisted__v_3609 = ptr_add(self->data, hoisted__U64_3608);
                (void)hoisted__v_3609;
                (void)hoisted__v_3609;
                Bool hoisted__Bool_3610 = 0;
                (void)hoisted__Bool_3610;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3609, &hoisted__Bool_3610);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3611 = U32_gt(&_rc_U32_3606, &_re_U32_3606);
                (void)_wcond_Bool_3611;
                if (_wcond_Bool_3611) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3606);
                U32_dec(&_rc_U32_3606);
                U32 hoisted__U64_3612 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3612;
                void *hoisted__v_3613 = ptr_add(self->data, hoisted__U64_3612);
                (void)hoisted__v_3613;
                (void)hoisted__v_3613;
                Bool hoisted__Bool_3614 = 0;
                (void)hoisted__Bool_3614;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3613, &hoisted__Bool_3614);
            }
        }
    }
    free(self->data);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3628 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3628;
    void * new_data = malloc(hoisted__U64_3628);
    {
        U32 _re_U32_3616 = self->cap;
        (void)_re_U32_3616;
        U32 _rc_U32_3616 = 0;
        (void)_rc_U32_3616;
        Bool hoisted__Bool_3627 = U32_lte(&_rc_U32_3616, &_re_U32_3616);
        (void)hoisted__Bool_3627;
        if (hoisted__Bool_3627) {
            while (1) {
                Bool _wcond_Bool_3617 = U32_lt(&_rc_U32_3616, &_re_U32_3616);
                (void)_wcond_Bool_3617;
                if (_wcond_Bool_3617) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3616);
                U32_inc(&_rc_U32_3616);
                U32 hoisted__U64_3618 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3618;
                void *hoisted__v_3619 = ptr_add(self->data, hoisted__U64_3618);
                (void)hoisted__v_3619;
                (void)hoisted__v_3619;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3619);
                U32 hoisted__U64_3620 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3620;
                void *hoisted__v_3621 = ptr_add(new_data, hoisted__U64_3620);
                (void)hoisted__v_3621;
                (void)hoisted__v_3621;
                memcpy(hoisted__v_3621, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3622 = U32_gt(&_rc_U32_3616, &_re_U32_3616);
                (void)_wcond_Bool_3622;
                if (_wcond_Bool_3622) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3616);
                U32_dec(&_rc_U32_3616);
                U32 hoisted__U64_3623 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3623;
                void *hoisted__v_3624 = ptr_add(self->data, hoisted__U64_3623);
                (void)hoisted__v_3624;
                (void)hoisted__v_3624;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3624);
                U32 hoisted__U64_3625 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3625;
                void *hoisted__v_3626 = ptr_add(new_data, hoisted__U64_3625);
                (void)hoisted__v_3626;
                (void)hoisted__v_3626;
                memcpy(hoisted__v_3626, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3629 = malloc(sizeof(Array));
    hoisted__Array_3629->data = new_data;
    hoisted__Array_3629->cap = self->cap;
    hoisted__Array_3629->elem_size = self->elem_size;
    hoisted__Array_3629->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3629->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3629;
    return hoisted__Array_3629;
}

U32 Array_size(void) {
    U32 hoisted__U32_3630 = 32;
    (void)hoisted__U32_3630;
    return hoisted__U32_3630;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_3868 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_3868;
    U32 hoisted__U32_3869 = 3;
    (void)hoisted__U32_3869;
    Array *_va_Array_120 = Array_new(hoisted__Type_3868, &hoisted__U32_3869);
    (void)_va_Array_120;
    Type_delete(hoisted__Type_3868, &(Bool){1});
    U32 hoisted__U32_3870 = 0;
    (void)hoisted__U32_3870;
    Str *hoisted__Str_3871 = Str_clone(loc_str);
    (void)hoisted__Str_3871;
    Array_set(_va_Array_120, &hoisted__U32_3870, hoisted__Str_3871);
    U32 hoisted__U32_3872 = 1;
    (void)hoisted__U32_3872;
    Str hoisted__Str_3873 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3873;
    Array_set(_va_Array_120, &hoisted__U32_3872, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3873; _oa; }));
    Array *hoisted__Array_3874 = Array_clone(parts);
    (void)hoisted__Array_3874;
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_3875 = 2;
    (void)hoisted__U32_3875;
    Str *hoisted__Str_3876 = format(hoisted__Array_3874);
    (void)hoisted__Str_3876;
    Array_set(_va_Array_120, &hoisted__U32_3875, hoisted__Str_3876);
    println(_va_Array_120);
    I64 hoisted__I64_3877 = 1;
    (void)hoisted__I64_3877;
    exit(hoisted__I64_3877);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_3887 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_3887;
    U32 hoisted__U32_3888 = 1;
    (void)hoisted__U32_3888;
    Array *_va_Array_122 = Array_new(hoisted__Type_3887, &hoisted__U32_3888);
    (void)_va_Array_122;
    Type_delete(hoisted__Type_3887, &(Bool){1});
    U32 hoisted__U32_3889 = 0;
    (void)hoisted__U32_3889;
    Str hoisted__Str_3890 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3890;
    Array_set(_va_Array_122, &hoisted__U32_3889, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3890; _oa; }));
    panic(loc_str, _va_Array_122);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_3896 = not(DEREF(cond));
    (void)hoisted__Bool_3896;
    if (hoisted__Bool_3896) {
        Type *hoisted__Type_3892 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3892;
        U32 hoisted__U32_3893 = 1;
        (void)hoisted__U32_3893;
        Array *_va_Array_123 = Array_new(hoisted__Type_3892, &hoisted__U32_3893);
        (void)_va_Array_123;
        Type_delete(hoisted__Type_3892, &(Bool){1});
        U32 hoisted__U32_3894 = 0;
        (void)hoisted__U32_3894;
        Str hoisted__Str_3895 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3895;
        Array_set(_va_Array_123, &hoisted__U32_3894, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3895; _oa; }));
        panic(loc_str, _va_Array_123);
    }
    Bool hoisted__Bool_3897 = 1;
    (void)hoisted__Bool_3897;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_3897;
    return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_3920 = I64_neq(a, b);
    (void)hoisted__Bool_3920;
    if (hoisted__Bool_3920) {
        Type *hoisted__Type_3908 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3908;
        U32 hoisted__U32_3909 = 5;
        (void)hoisted__U32_3909;
        Array *_va_Array_125 = Array_new(hoisted__Type_3908, &hoisted__U32_3909);
        (void)_va_Array_125;
        Type_delete(hoisted__Type_3908, &(Bool){1});
        U32 hoisted__U32_3910 = 0;
        (void)hoisted__U32_3910;
        Str hoisted__Str_3911 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3911;
        Array_set(_va_Array_125, &hoisted__U32_3910, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3911; _oa; }));
        U32 hoisted__U32_3912 = 1;
        (void)hoisted__U32_3912;
        Str *hoisted__Str_3913 = I64_to_str(a);
        (void)hoisted__Str_3913;
        Array_set(_va_Array_125, &hoisted__U32_3912, hoisted__Str_3913);
        U32 hoisted__U32_3914 = 2;
        (void)hoisted__U32_3914;
        Str hoisted__Str_3915 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3915;
        Array_set(_va_Array_125, &hoisted__U32_3914, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3915; _oa; }));
        U32 hoisted__U32_3916 = 3;
        (void)hoisted__U32_3916;
        Str *hoisted__Str_3917 = I64_to_str(b);
        (void)hoisted__Str_3917;
        Array_set(_va_Array_125, &hoisted__U32_3916, hoisted__Str_3917);
        U32 hoisted__U32_3918 = 4;
        (void)hoisted__U32_3918;
        Str hoisted__Str_3919 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3919;
        Array_set(_va_Array_125, &hoisted__U32_3918, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3919; _oa; }));
        panic(loc_str, _va_Array_125);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_3934 = Str_eq(a, b);
    (void)hoisted__Bool_3934;
    Bool hoisted__Bool_3935 = not(hoisted__Bool_3934);
    (void)hoisted__Bool_3935;
    if (hoisted__Bool_3935) {
        Type *hoisted__Type_3922 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3922;
        U32 hoisted__U32_3923 = 5;
        (void)hoisted__U32_3923;
        Array *_va_Array_126 = Array_new(hoisted__Type_3922, &hoisted__U32_3923);
        (void)_va_Array_126;
        Type_delete(hoisted__Type_3922, &(Bool){1});
        U32 hoisted__U32_3924 = 0;
        (void)hoisted__U32_3924;
        Str hoisted__Str_3925 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3925;
        Array_set(_va_Array_126, &hoisted__U32_3924, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3925; _oa; }));
        U32 hoisted__U32_3926 = 1;
        (void)hoisted__U32_3926;
        Str *hoisted__Str_3927 = Str_clone(a);
        (void)hoisted__Str_3927;
        Array_set(_va_Array_126, &hoisted__U32_3926, hoisted__Str_3927);
        U32 hoisted__U32_3928 = 2;
        (void)hoisted__U32_3928;
        Str hoisted__Str_3929 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3929;
        Array_set(_va_Array_126, &hoisted__U32_3928, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3929; _oa; }));
        U32 hoisted__U32_3930 = 3;
        (void)hoisted__U32_3930;
        Str *hoisted__Str_3931 = Str_clone(b);
        (void)hoisted__Str_3931;
        Array_set(_va_Array_126, &hoisted__U32_3930, hoisted__Str_3931);
        U32 hoisted__U32_3932 = 4;
        (void)hoisted__U32_3932;
        Str hoisted__Str_3933 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3933;
        Array_set(_va_Array_126, &hoisted__U32_3932, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3933; _oa; }));
        panic(loc_str, _va_Array_126);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_3936 = parts;
        (void)_fc_Array_3936;
        (void)_fc_Array_3936;
        U32 _fi_USize_3936 = 0;
        (void)_fi_USize_3936;
        while (1) {
            U32 hoisted__U32_3938; { U32 *_hp = (U32 *)Array_len(_fc_Array_3936); hoisted__U32_3938 = *_hp; free(_hp); }
            (void)hoisted__U32_3938;
            Bool _wcond_Bool_3937 = U32_lt(&_fi_USize_3936, &hoisted__U32_3938);
            (void)_wcond_Bool_3937;
            if (_wcond_Bool_3937) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_3936, &_fi_USize_3936);
            U32 hoisted__U32_3939 = 1;
            (void)hoisted__U32_3939;
            U32 hoisted__U32_3940 = U32_add(_fi_USize_3936, hoisted__U32_3939);
            (void)hoisted__U32_3940;
            _fi_USize_3936 = hoisted__U32_3940;
            print_single(s);
        }
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_4083 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4083;
    I64 hoisted__I64_4084 = 3;
    (void)hoisted__I64_4084;
    assert_eq(&hoisted__Str_4083, &result, &hoisted__I64_4084);
    Str_delete(&hoisted__Str_4083, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4091 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4091;
    I64 hoisted__I64_4092 = 15;
    (void)hoisted__I64_4092;
    assert_eq(&hoisted__Str_4091, &result, &hoisted__I64_4092);
    Str_delete(&hoisted__Str_4091, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4099 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4099;
    I64 hoisted__I64_4100 = 26;
    (void)hoisted__I64_4100;
    assert_eq(&hoisted__Str_4099, &result, &hoisted__I64_4100);
    Str_delete(&hoisted__Str_4099, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4103 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4103;
    Str hoisted__Str_4104 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4104;
    assert_eq_str(&hoisted__Str_4103, &result, &hoisted__Str_4104);
    Str_delete(&hoisted__Str_4103, &(Bool){0});
    Str_delete(&hoisted__Str_4104, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4435 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4435;
    assert_eq_str(&hoisted__Str_4435, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4435, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_4436 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4436;
    assert_eq_str(&hoisted__Str_4436, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4436, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4438 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4438;
    I64 hoisted__I64_4439 = 8;
    (void)hoisted__I64_4439;
    assert_eq(&hoisted__Str_4438, &result, &hoisted__I64_4439);
    Str_delete(&hoisted__Str_4438, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4442 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4442;
    Bool hoisted__Bool_4443 = 1;
    (void)hoisted__Bool_4443;
    Bool_delete(assert(&hoisted__Str_4442, &hoisted__Bool_4443), &(Bool){1});
    Str_delete(&hoisted__Str_4442, &(Bool){0});
    Str hoisted__Str_4447 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4447;
    Bool hoisted__Bool_4448 = 1;
    (void)hoisted__Bool_4448;
    Bool_delete(assert(&hoisted__Str_4447, &hoisted__Bool_4448), &(Bool){1});
    Str_delete(&hoisted__Str_4447, &(Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4454 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4454;
    Str hoisted__Str_4455 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4455;
    Str hoisted__Str_4456 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4456;
    assert_eq_str(&hoisted__Str_4454, &hoisted__Str_4455, &hoisted__Str_4456);
    Str_delete(&hoisted__Str_4454, &(Bool){0});
    Str_delete(&hoisted__Str_4455, &(Bool){0});
    Str_delete(&hoisted__Str_4456, &(Bool){0});
    Str hoisted__Str_4459 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4459;
    Str hoisted__Str_4460 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4460;
    Str hoisted__Str_4461 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4461;
    assert_eq_str(&hoisted__Str_4459, &hoisted__Str_4460, &hoisted__Str_4461);
    Str_delete(&hoisted__Str_4459, &(Bool){0});
    Str_delete(&hoisted__Str_4460, &(Bool){0});
    Str_delete(&hoisted__Str_4461, &(Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4466 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4466;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4466;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4467 = 16;
    (void)hoisted__U32_4467;
    return hoisted__U32_4467;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4468 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4468;
    I64 hoisted__I64_4469 = 42;
    (void)hoisted__I64_4469;
    assert_eq(&hoisted__Str_4468, &v.x, &hoisted__I64_4469);
    Str_delete(&hoisted__Str_4468, &(Bool){0});
    Str hoisted__Str_4470 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4470;
    I64 hoisted__I64_4471 = 99;
    (void)hoisted__I64_4471;
    assert_eq(&hoisted__Str_4470, &v.y, &hoisted__I64_4471);
    Str_delete(&hoisted__Str_4470, &(Bool){0});
    CfVec2_delete(&v, &(Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4474 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4474;
    I64 hoisted__I64_4475 = 10;
    (void)hoisted__I64_4475;
    assert_eq(&hoisted__Str_4474, &p.x, &hoisted__I64_4475);
    Str_delete(&hoisted__Str_4474, &(Bool){0});
    Str hoisted__Str_4476 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4476;
    I64 hoisted__I64_4477 = 20;
    (void)hoisted__I64_4477;
    assert_eq(&hoisted__Str_4476, &p.y, &hoisted__I64_4477);
    Str_delete(&hoisted__Str_4476, &(Bool){0});
    CfVec2_delete(&p, &(Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4483 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4483;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4483;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4484 = 32;
    (void)hoisted__U32_4484;
    return hoisted__U32_4484;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4485 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4485;
    I64 hoisted__I64_4486 = 5;
    (void)hoisted__I64_4486;
    assert_eq(&hoisted__Str_4485, &r.top_left.x, &hoisted__I64_4486);
    Str_delete(&hoisted__Str_4485, &(Bool){0});
    Str hoisted__Str_4487 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4487;
    I64 hoisted__I64_4488 = 10;
    (void)hoisted__I64_4488;
    assert_eq(&hoisted__Str_4487, &r.top_left.y, &hoisted__I64_4488);
    Str_delete(&hoisted__Str_4487, &(Bool){0});
    Str hoisted__Str_4489 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4489;
    I64 hoisted__I64_4490 = 100;
    (void)hoisted__I64_4490;
    assert_eq(&hoisted__Str_4489, &r.bottom_right.x, &hoisted__I64_4490);
    Str_delete(&hoisted__Str_4489, &(Bool){0});
    Str hoisted__Str_4491 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4491;
    I64 hoisted__I64_4492 = 200;
    (void)hoisted__I64_4492;
    assert_eq(&hoisted__Str_4491, &r.bottom_right.y, &hoisted__I64_4492);
    Str_delete(&hoisted__Str_4491, &(Bool){0});
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
    Bool hoisted__Bool_4497 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4497;
    if (hoisted__Bool_4497) {
        Bool hoisted__Bool_4494 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4494;
        { Bool _ret_val = hoisted__Bool_4494;
                return _ret_val; }
    }
    Bool hoisted__Bool_4498 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4498;
    if (hoisted__Bool_4498) {
        Bool hoisted__Bool_4495 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4495;
        { Bool _ret_val = hoisted__Bool_4495;
                return _ret_val; }
    }
    Bool hoisted__Bool_4499 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4499;
    if (hoisted__Bool_4499) {
        Bool hoisted__Bool_4496 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4496;
        { Bool _ret_val = hoisted__Bool_4496;
                return _ret_val; }
    }
    Bool hoisted__Bool_4500 = 0;
    (void)hoisted__Bool_4500;
    return hoisted__Bool_4500;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4508 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4508;
    if (hoisted__Bool_4508) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4509 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4509;
    if (hoisted__Bool_4509) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4510 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4510;
    if (hoisted__Bool_4510) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4511 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4511;
    UNREACHABLE(&hoisted__Str_4511);
    Str_delete(&hoisted__Str_4511, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4512 = 4;
    (void)hoisted__U32_4512;
    return hoisted__U32_4512;
}


void test_enum_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Str hoisted__Str_4513 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4513;
    Bool hoisted__Bool_4514 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4514;
    Bool_delete(assert(&hoisted__Str_4513, &hoisted__Bool_4514), &(Bool){1});
    Str_delete(&hoisted__Str_4513, &(Bool){0});
    Bool hoisted__Bool_4516 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4516;
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_4517 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4517;
    Bool hoisted__Bool_4518 = not(hoisted__Bool_4516);
    (void)hoisted__Bool_4518;
    Bool_delete(assert(&hoisted__Str_4517, &hoisted__Bool_4518), &(Bool){1});
    Str_delete(&hoisted__Str_4517, &(Bool){0});
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
    Bool hoisted__Bool_4520 = is(self, other);
    (void)hoisted__Bool_4520;
    return hoisted__Bool_4520;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_4538 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4538;
    if (hoisted__Bool_4538) {
        I64 *hoisted__I64_4534 = get_payload(self);
        (void)hoisted__I64_4534;
        (void)hoisted__I64_4534;
        Bool hoisted__Bool_4535 = 0;
        (void)hoisted__Bool_4535;
        I64_delete(hoisted__I64_4534, &hoisted__Bool_4535);
    }
    Bool hoisted__Bool_4539 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4539;
    if (hoisted__Bool_4539) {
        Str *hoisted__Str_4536 = get_payload(self);
        (void)hoisted__Str_4536;
        (void)hoisted__Str_4536;
        Bool hoisted__Bool_4537 = 0;
        (void)hoisted__Bool_4537;
        Str_delete(hoisted__Str_4536, &hoisted__Bool_4537);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4568 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4568;
    if (hoisted__Bool_4568) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4565 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4565;
        { Token * _ret_val = hoisted__Token_4565;
                return _ret_val; }
    }
    Bool hoisted__Bool_4569 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4569;
    if (hoisted__Bool_4569) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4566 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4566;
        Token *hoisted__Token_4567 = Token_Name(hoisted__Str_4566);
        (void)hoisted__Token_4567;
        { Token * _ret_val = hoisted__Token_4567;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4570 = 24;
    (void)hoisted__U32_4570;
    return hoisted__U32_4570;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_4572 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4572;
    Bool hoisted__Bool_4573 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4573;
    Bool_delete(assert(&hoisted__Str_4572, &hoisted__Bool_4573), &(Bool){1});
    Str_delete(&hoisted__Str_4572, &(Bool){0});
    Bool hoisted__Bool_4575 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4575;
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_4576 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4576;
    Bool hoisted__Bool_4577 = not(hoisted__Bool_4575);
    (void)hoisted__Bool_4577;
    Bool_delete(assert(&hoisted__Str_4576, &hoisted__Bool_4577), &(Bool){1});
    Str_delete(&hoisted__Str_4576, &(Bool){0});
}

void test_enum_return_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Green});
    Str hoisted__Str_4579 = (Str){.c_str = (void *)"test/constfold.til:191:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4579;
    Bool hoisted__Bool_4580 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4580;
    Bool_delete(assert(&hoisted__Str_4579, &hoisted__Bool_4580), &(Bool){1});
    Str_delete(&hoisted__Str_4579, &(Bool){0});
    Bool hoisted__Bool_4582 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4582;
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_4583 = (Str){.c_str = (void *)"test/constfold.til:192:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4583;
    Bool hoisted__Bool_4584 = not(hoisted__Bool_4582);
    (void)hoisted__Bool_4584;
    Bool_delete(assert(&hoisted__Str_4583, &hoisted__Bool_4584), &(Bool){1});
    Str_delete(&hoisted__Str_4583, &(Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_4588 = (Str){.c_str = (void *)"test/constfold.til:203:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4588;
    Bool hoisted__Bool_4589 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4589;
    Bool_delete(assert(&hoisted__Str_4588, &hoisted__Bool_4589), &(Bool){1});
    Str_delete(&hoisted__Str_4588, &(Bool){0});
    Bool hoisted__Bool_4591 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4591;
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_4592 = (Str){.c_str = (void *)"test/constfold.til:204:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4592;
    Bool hoisted__Bool_4593 = not(hoisted__Bool_4591);
    (void)hoisted__Bool_4593;
    Bool_delete(assert(&hoisted__Str_4592, &hoisted__Bool_4593), &(Bool){1});
    Str_delete(&hoisted__Str_4592, &(Bool){0});
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
