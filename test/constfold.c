#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef struct Str Str;
typedef struct Dynamic Dynamic;
typedef enum {
    Primitive_TAG_I16
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
Bool Primitive_eq(Primitive *, Primitive *);
Primitive *Primitive_I16();
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
        Str hoisted__Str_807 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_807;
        Type *hoisted__Type_808 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_807; _oa; }));
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
        Str hoisted__Str_833 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_833;
        Type *hoisted__Type_834 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_833; _oa; }));
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
        Str hoisted__Str_839 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_839;
        Type *hoisted__Type_840 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_839; _oa; }));
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
    U32 hoisted__U32_923 = 0;
    (void)hoisted__U32_923;
    Bool hoisted__Bool_924 = U32_eq(self->count, hoisted__U32_923);
    (void)hoisted__Bool_924;
    return hoisted__Bool_924;
}

U32 Str_size(void) {
    U32 hoisted__U32_1143 = 16;
    (void)hoisted__U32_1143;
    return hoisted__U32_1143;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1144 = Str_cmp(a, b);
    (void)hoisted__I64_1144;
    I64 hoisted__I64_1145 = 0;
    (void)hoisted__I64_1145;
    Bool hoisted__Bool_1146 = I64_eq(hoisted__I64_1144, hoisted__I64_1145);
    (void)hoisted__Bool_1146;
    return hoisted__Bool_1146;
}

U32 * Dynamic_size(void) {
    U32 hoisted__U32_1233 = 8;
    (void)hoisted__U32_1233;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1233;
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
    I64 hoisted__I64_1437 = 0;
    (void)hoisted__I64_1437;
    Bool hoisted__Bool_1438 = I64_eq(DEREF(val), hoisted__I64_1437);
    (void)hoisted__Bool_1438;
    if (hoisted__Bool_1438) {
        U64 hoisted__U64_1401 = 2;
        (void)hoisted__U64_1401;
        void * buf = malloc(hoisted__U64_1401);
        I64 hoisted__I64_1402 = 48;
        (void)hoisted__I64_1402;
        U64 hoisted__U64_1403 = 1;
        (void)hoisted__U64_1403;
        memcpy(buf, &hoisted__I64_1402, hoisted__U64_1403);
        U64 hoisted__U64_1404 = 1;
        (void)hoisted__U64_1404;
        void *hoisted__v_1405 = ptr_add(buf, hoisted__U64_1404);
        (void)hoisted__v_1405;
        (void)hoisted__v_1405;
        I32 hoisted__I32_1406 = 0;
        (void)hoisted__I32_1406;
        U64 hoisted__U64_1407 = 1;
        (void)hoisted__U64_1407;
        memset(hoisted__v_1405, hoisted__I32_1406, hoisted__U64_1407);
        I32_delete(&hoisted__I32_1406, &(Bool){0});
        I64 hoisted__I64_1408 = 1;
        (void)hoisted__I64_1408;
        I64 hoisted__I64_1409 = 1;
        (void)hoisted__I64_1409;
        Str *hoisted__Str_1410 = malloc(sizeof(Str));
        hoisted__Str_1410->c_str = buf;
        hoisted__Str_1410->count = hoisted__I64_1408;
        hoisted__Str_1410->cap = hoisted__I64_1409;
        (void)hoisted__Str_1410;
        { Str * _ret_val = hoisted__Str_1410;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(val);
    I64 hoisted__I64_1439 = 0;
    (void)hoisted__I64_1439;
    Bool hoisted__Bool_1440 = I64_lt(val, &hoisted__I64_1439);
    (void)hoisted__Bool_1440;
    if (hoisted__Bool_1440) {
        Bool hoisted__Bool_1411 = 1;
        (void)hoisted__Bool_1411;
        is_neg = hoisted__Bool_1411;
        I64 hoisted__I64_1412 = 0;
        (void)hoisted__I64_1412;
        I64 hoisted__I64_1413 = I64_sub(hoisted__I64_1412, DEREF(val));
        (void)hoisted__I64_1413;
        v = hoisted__I64_1413;
    }
    U64 ndigits = 0;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1415 = 0;
        (void)hoisted__I64_1415;
        Bool _wcond_Bool_1414 = I64_gt(&tmp, &hoisted__I64_1415);
        (void)_wcond_Bool_1414;
        if (_wcond_Bool_1414) {
        } else {
            break;
        }
        U64 hoisted__U64_1416 = 1;
        (void)hoisted__U64_1416;
        U64 hoisted__U64_1417 = U64_add(ndigits, hoisted__U64_1416);
        (void)hoisted__U64_1417;
        ndigits = hoisted__U64_1417;
        I64 hoisted__I64_1418 = 10;
        (void)hoisted__I64_1418;
        I64 hoisted__I64_1419 = I64_div(tmp, hoisted__I64_1418);
        (void)hoisted__I64_1419;
        tmp = hoisted__I64_1419;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1420 = 1;
        (void)hoisted__U64_1420;
        U64 hoisted__U64_1421 = U64_add(total, hoisted__U64_1420);
        (void)hoisted__U64_1421;
        total = hoisted__U64_1421;
    }
    U64 hoisted__U64_1441 = 1;
    (void)hoisted__U64_1441;
    U64 hoisted__U64_1442 = U64_add(total, hoisted__U64_1441);
    (void)hoisted__U64_1442;
    void * buf = malloc(hoisted__U64_1442);
    if (is_neg) {
        I64 hoisted__I64_1422 = 45;
        (void)hoisted__I64_1422;
        U64 hoisted__U64_1423 = 1;
        (void)hoisted__U64_1423;
        memcpy(buf, &hoisted__I64_1422, hoisted__U64_1423);
    }
    U64 hoisted__U64_1443 = 1;
    (void)hoisted__U64_1443;
    U64 i = U64_sub(total, hoisted__U64_1443);
    while (1) {
        I64 hoisted__I64_1425 = 0;
        (void)hoisted__I64_1425;
        Bool _wcond_Bool_1424 = I64_gt(&v, &hoisted__I64_1425);
        (void)_wcond_Bool_1424;
        if (_wcond_Bool_1424) {
        } else {
            break;
        }
        I64 hoisted__I64_1426 = 10;
        (void)hoisted__I64_1426;
        I64 hoisted__I64_1427 = I64_mod(v, hoisted__I64_1426);
        (void)hoisted__I64_1427;
        I64 hoisted__I64_1428 = 48;
        (void)hoisted__I64_1428;
        I64 hoisted__I64_1429 = I64_add(hoisted__I64_1427, hoisted__I64_1428);
        (void)hoisted__I64_1429;
        void *hoisted__v_1430 = ptr_add(buf, i);
        (void)hoisted__v_1430;
        (void)hoisted__v_1430;
        U8 hoisted__U8_1431 = I64_to_u8(hoisted__I64_1429);
        (void)hoisted__U8_1431;
        U64 hoisted__U64_1432 = 1;
        (void)hoisted__U64_1432;
        memcpy(hoisted__v_1430, &hoisted__U8_1431, hoisted__U64_1432);
        U8_delete(&hoisted__U8_1431, &(Bool){0});
        I64 hoisted__I64_1433 = 10;
        (void)hoisted__I64_1433;
        I64 hoisted__I64_1434 = I64_div(v, hoisted__I64_1433);
        (void)hoisted__I64_1434;
        v = hoisted__I64_1434;
        U64 hoisted__U64_1435 = 1;
        (void)hoisted__U64_1435;
        U64 hoisted__U64_1436 = U64_sub(i, hoisted__U64_1435);
        (void)hoisted__U64_1436;
        i = hoisted__U64_1436;
    }
    void *hoisted__v_1444 = ptr_add(buf, total);
    (void)hoisted__v_1444;
    (void)hoisted__v_1444;
    I32 hoisted__I32_1445 = 0;
    (void)hoisted__I32_1445;
    U64 hoisted__U64_1446 = 1;
    (void)hoisted__U64_1446;
    memset(hoisted__v_1444, hoisted__I32_1445, hoisted__U64_1446);
    I32_delete(&hoisted__I32_1445, &(Bool){0});
    Str *hoisted__Str_1447 = malloc(sizeof(Str));
    hoisted__Str_1447->c_str = buf;
    hoisted__Str_1447->count = total;
    hoisted__Str_1447->cap = total;
    (void)hoisted__Str_1447;
    return hoisted__Str_1447;
}

void I64_delete(I64 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * I64_size(void) {
    U32 hoisted__U32_1465 = 8;
    (void)hoisted__U32_1465;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1465;
    return _r; }
}

Bool I64_lt(I64 * a, I64 * b) {
    I64 hoisted__I64_1598 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1598;
    I64 hoisted__I64_1599 = -1;
    (void)hoisted__I64_1599;
    Bool hoisted__Bool_1600 = I64_eq(hoisted__I64_1598, hoisted__I64_1599);
    (void)hoisted__Bool_1600;
    return hoisted__Bool_1600;
}

Bool I64_gt(I64 * a, I64 * b) {
    I64 hoisted__I64_1601 = I64_cmp(DEREF(a), DEREF(b));
    (void)hoisted__I64_1601;
    I64 hoisted__I64_1602 = 1;
    (void)hoisted__I64_1602;
    Bool hoisted__Bool_1603 = I64_eq(hoisted__I64_1601, hoisted__I64_1602);
    (void)hoisted__Bool_1603;
    return hoisted__Bool_1603;
}

Bool I64_neq(I64 * a, I64 * b) {
    Bool hoisted__Bool_1604 = I64_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1604;
    Bool hoisted__Bool_1605 = not(hoisted__Bool_1604);
    (void)hoisted__Bool_1605;
    return hoisted__Bool_1605;
}

I64 * Bool_cmp(Bool * a, Bool * b) {
    Bool hoisted__Bool_1619 = Bool_eq(DEREF(a), DEREF(b));
    (void)hoisted__Bool_1619;
    if (hoisted__Bool_1619) {
        I64 hoisted__I64_1617 = 0;
        (void)hoisted__I64_1617;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1617;
                return _r; }
    }
    if (DEREF(b)) {
        I64 hoisted__I64_1618 = -1;
        (void)hoisted__I64_1618;
        { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1618;
        return _r; }
    }
    I64 hoisted__I64_1620 = 1;
    (void)hoisted__I64_1620;
    { I64 *_r = malloc(sizeof(I64)); *_r = hoisted__I64_1620;
    return _r; }
}

void Bool_delete(Bool * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 * Bool_size(void) {
    U32 hoisted__U32_1621 = 1;
    (void)hoisted__U32_1621;
    { U32 *_r = malloc(sizeof(U32)); *_r = hoisted__U32_1621;
    return _r; }
}

Primitive *Primitive_I16() {
    Primitive *r = malloc(sizeof(Primitive));
    *r = (Primitive){ .tag = Primitive_TAG_I16 };
    return r;
}
Bool Primitive_eq(Primitive * self, Primitive * other) {
    Bool hoisted__Bool_1759 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1759;
    if (hoisted__Bool_1759) {
        Bool hoisted__Bool_1758 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1758;
        { Bool _ret_val = hoisted__Bool_1758;
                return _ret_val; }
    }
    Bool hoisted__Bool_1760 = 0;
    (void)hoisted__Bool_1760;
    return hoisted__Bool_1760;
}

void Primitive_delete(Primitive * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1764 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1764;
    if (hoisted__Bool_1764) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Str hoisted__Str_1765 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1765;
    UNREACHABLE(&hoisted__Str_1765);
    Str_delete(&hoisted__Str_1765, &(Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1766 = 4;
    (void)hoisted__U32_1766;
    return hoisted__U32_1766;
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
    Bool hoisted__Bool_1825 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1825;
    if (hoisted__Bool_1825) {
        Str *hoisted__Str_1817 = get_payload(self);
        (void)hoisted__Str_1817;
        (void)hoisted__Str_1817;
        Bool hoisted__Bool_1818 = 0;
        (void)hoisted__Bool_1818;
        Str_delete(hoisted__Str_1817, &hoisted__Bool_1818);
    }
    Bool hoisted__Bool_1826 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1826;
    if (hoisted__Bool_1826) {
        Str *hoisted__Str_1819 = get_payload(self);
        (void)hoisted__Str_1819;
        (void)hoisted__Str_1819;
        Bool hoisted__Bool_1820 = 0;
        (void)hoisted__Bool_1820;
        Str_delete(hoisted__Str_1819, &hoisted__Bool_1820);
    }
    Bool hoisted__Bool_1827 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1827;
    if (hoisted__Bool_1827) {
        Str *hoisted__Str_1821 = get_payload(self);
        (void)hoisted__Str_1821;
        (void)hoisted__Str_1821;
        Bool hoisted__Bool_1822 = 0;
        (void)hoisted__Bool_1822;
        Str_delete(hoisted__Str_1821, &hoisted__Bool_1822);
    }
    Bool hoisted__Bool_1828 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_1828;
    if (hoisted__Bool_1828) {
        Primitive *hoisted__Primitive_1823 = get_payload(self);
        (void)hoisted__Primitive_1823;
        (void)hoisted__Primitive_1823;
        Bool hoisted__Bool_1824 = 0;
        (void)hoisted__Bool_1824;
        Primitive_delete(hoisted__Primitive_1823, &hoisted__Bool_1824);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_1910 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_1910;
    if (hoisted__Bool_1910) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_1911 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_1911;
    if (hoisted__Bool_1911) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_1912 = is(self, &(Type){.tag = Type_TAG_I64});
    (void)hoisted__Bool_1912;
    if (hoisted__Bool_1912) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1913 = is(self, &(Type){.tag = Type_TAG_U8});
    (void)hoisted__Bool_1913;
    if (hoisted__Bool_1913) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1914 = is(self, &(Type){.tag = Type_TAG_I32});
    (void)hoisted__Bool_1914;
    if (hoisted__Bool_1914) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1915 = is(self, &(Type){.tag = Type_TAG_U32});
    (void)hoisted__Bool_1915;
    if (hoisted__Bool_1915) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1916 = is(self, &(Type){.tag = Type_TAG_U64});
    (void)hoisted__Bool_1916;
    if (hoisted__Bool_1916) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1917 = is(self, &(Type){.tag = Type_TAG_F32});
    (void)hoisted__Bool_1917;
    if (hoisted__Bool_1917) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1918 = is(self, &(Type){.tag = Type_TAG_Bool});
    (void)hoisted__Bool_1918;
    if (hoisted__Bool_1918) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Bool;
                return _r; }
    }
    Bool hoisted__Bool_1919 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_1919;
    if (hoisted__Bool_1919) {
        Str *_clone_payload_Struct_9 = get_payload(self);
        (void)_clone_payload_Struct_9;
        (void)_clone_payload_Struct_9;
        Str *hoisted__Str_1904 = Str_clone(_clone_payload_Struct_9);
        (void)hoisted__Str_1904;
        Type *hoisted__Type_1905 = Type_Struct(hoisted__Str_1904);
        (void)hoisted__Type_1905;
        { Type * _ret_val = hoisted__Type_1905;
                return _ret_val; }
    }
    Bool hoisted__Bool_1920 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_1920;
    if (hoisted__Bool_1920) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_1921 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_1921;
    if (hoisted__Bool_1921) {
        Str *_clone_payload_Enum_11 = get_payload(self);
        (void)_clone_payload_Enum_11;
        (void)_clone_payload_Enum_11;
        Str *hoisted__Str_1906 = Str_clone(_clone_payload_Enum_11);
        (void)hoisted__Str_1906;
        Type *hoisted__Type_1907 = Type_Enum(hoisted__Str_1906);
        (void)hoisted__Type_1907;
        { Type * _ret_val = hoisted__Type_1907;
                return _ret_val; }
    }
    Bool hoisted__Bool_1922 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_1922;
    if (hoisted__Bool_1922) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_1923 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_1923;
    if (hoisted__Bool_1923) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_1924 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_1924;
    if (hoisted__Bool_1924) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_1925 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_1925;
    if (hoisted__Bool_1925) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_1926 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_1926;
    if (hoisted__Bool_1926) {
        Str *_clone_payload_Custom_16 = get_payload(self);
        (void)_clone_payload_Custom_16;
        (void)_clone_payload_Custom_16;
        Str *hoisted__Str_1908 = Str_clone(_clone_payload_Custom_16);
        (void)hoisted__Str_1908;
        Type *hoisted__Type_1909 = Type_Custom(hoisted__Str_1908);
        (void)hoisted__Type_1909;
        { Type * _ret_val = hoisted__Type_1909;
                return _ret_val; }
    }
    Bool hoisted__Bool_1927 = is(self, &(Type){.tag = Type_TAG_I8});
    (void)hoisted__Bool_1927;
    if (hoisted__Bool_1927) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_I8;
                return _r; }
    }
    Primitive *_clone_payload_Primitive_18 = get_payload(self);
    (void)_clone_payload_Primitive_18;
    (void)_clone_payload_Primitive_18;
    Primitive *hoisted__Primitive_1928 = Primitive_clone(_clone_payload_Primitive_18);
    (void)hoisted__Primitive_1928;
    Type *hoisted__Type_1929 = Type_Primitive(hoisted__Primitive_1928);
    (void)hoisted__Type_1929;
    return hoisted__Type_1929;
}

U32 Type_size(void) {
    U32 hoisted__U32_1930 = 24;
    (void)hoisted__U32_1930;
    return hoisted__U32_1930;
}


Array * Array_new_type_name(Str * elem_type, U32 * cap) {
    Bool hoisted__Bool_3463 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3463;
    if (hoisted__Bool_3463) {
        Str hoisted__Str_3457 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3457;
        Type *hoisted__Type_3458 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3457; _oa; }));
        (void)hoisted__Type_3458;
        U32 hoisted__U32_3459 = 1;
        (void)hoisted__U32_3459;
        Array *_va_Array_101 = Array_new(hoisted__Type_3458, &hoisted__U32_3459);
        (void)_va_Array_101;
        Type_delete(hoisted__Type_3458, &(Bool){1});
        U32 hoisted__U32_3460 = 0;
        (void)hoisted__U32_3460;
        Str hoisted__Str_3461 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3461;
        Array_set(_va_Array_101, &hoisted__U32_3460, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3461; _oa; }));
        Str hoisted__Str_3462 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3462;
        panic(&hoisted__Str_3462, _va_Array_101);
        Str_delete(&hoisted__Str_3462, &(Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3464 = calloc(DEREF(cap), elem_size);
    (void)hoisted__v_3464;
    void * hoisted__v_3465 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3465;
    void * hoisted__v_3466 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3466;
    Array *hoisted__Array_3467 = malloc(sizeof(Array));
    hoisted__Array_3467->data = hoisted__v_3464;
    hoisted__Array_3467->cap = DEREF(cap);
    hoisted__Array_3467->elem_size = elem_size;
    hoisted__Array_3467->elem_clone = hoisted__v_3465;
    hoisted__Array_3467->elem_delete = hoisted__v_3466;
    (void)hoisted__Array_3467;
    return hoisted__Array_3467;
}

Array * Array_new(Type * T, U32 * cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3468 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3468;
    Str_delete(elem_type, &(Bool){1});
    return hoisted__Array_3468;
}

U32 * Array_len(Array * self) {
    { U32 *_r = malloc(sizeof(U32)); *_r = self->cap;
    return _r; }
}

void * Array_get(Array * self, U32 * i) {
    Bool hoisted__Bool_3483 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3483;
    if (hoisted__Bool_3483) {
        Str hoisted__Str_3469 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3469;
        Type *hoisted__Type_3470 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3469; _oa; }));
        (void)hoisted__Type_3470;
        U32 hoisted__U32_3471 = 5;
        (void)hoisted__U32_3471;
        Array *_va_Array_102 = Array_new(hoisted__Type_3470, &hoisted__U32_3471);
        (void)_va_Array_102;
        Type_delete(hoisted__Type_3470, &(Bool){1});
        U32 hoisted__U32_3472 = 0;
        (void)hoisted__U32_3472;
        Str hoisted__Str_3473 = (Str){.c_str = (void *)"Array.get: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3473;
        Array_set(_va_Array_102, &hoisted__U32_3472, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3473; _oa; }));
        U32 hoisted__U32_3474 = 1;
        (void)hoisted__U32_3474;
        Str *hoisted__Str_3475 = U32_to_str(i);
        (void)hoisted__Str_3475;
        Array_set(_va_Array_102, &hoisted__U32_3474, hoisted__Str_3475);
        U32 hoisted__U32_3476 = 2;
        (void)hoisted__U32_3476;
        Str hoisted__Str_3477 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3477;
        Array_set(_va_Array_102, &hoisted__U32_3476, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3477; _oa; }));
        U32 hoisted__U32_3478 = 3;
        (void)hoisted__U32_3478;
        Str *hoisted__Str_3479 = U32_to_str(&self->cap);
        (void)hoisted__Str_3479;
        Array_set(_va_Array_102, &hoisted__U32_3478, hoisted__Str_3479);
        U32 hoisted__U32_3480 = 4;
        (void)hoisted__U32_3480;
        Str hoisted__Str_3481 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3481;
        Array_set(_va_Array_102, &hoisted__U32_3480, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3481; _oa; }));
        Str hoisted__Str_3482 = (Str){.c_str = (void *)"./src/core/array.til:40:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3482;
        panic(&hoisted__Str_3482, _va_Array_102);
        Str_delete(&hoisted__Str_3482, &(Bool){0});
    }
    U32 hoisted__U64_3484 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3484;
    void *hoisted__v_3485 = ptr_add(self->data, hoisted__U64_3484);
    (void)hoisted__v_3485;
    (void)hoisted__v_3485;
    return hoisted__v_3485;
}

void Array_set(Array * self, U32 * i, void * val) {
    Bool hoisted__Bool_3500 = U32_gte(i, &self->cap);
    (void)hoisted__Bool_3500;
    if (hoisted__Bool_3500) {
        Str hoisted__Str_3486 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3486;
        Type *hoisted__Type_3487 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3486; _oa; }));
        (void)hoisted__Type_3487;
        U32 hoisted__U32_3488 = 5;
        (void)hoisted__U32_3488;
        Array *_va_Array_103 = Array_new(hoisted__Type_3487, &hoisted__U32_3488);
        (void)_va_Array_103;
        Type_delete(hoisted__Type_3487, &(Bool){1});
        U32 hoisted__U32_3489 = 0;
        (void)hoisted__U32_3489;
        Str hoisted__Str_3490 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3490;
        Array_set(_va_Array_103, &hoisted__U32_3489, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3490; _oa; }));
        U32 hoisted__U32_3491 = 1;
        (void)hoisted__U32_3491;
        Str *hoisted__Str_3492 = U32_to_str(i);
        (void)hoisted__Str_3492;
        Array_set(_va_Array_103, &hoisted__U32_3491, hoisted__Str_3492);
        U32 hoisted__U32_3493 = 2;
        (void)hoisted__U32_3493;
        Str hoisted__Str_3494 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3494;
        Array_set(_va_Array_103, &hoisted__U32_3493, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3494; _oa; }));
        U32 hoisted__U32_3495 = 3;
        (void)hoisted__U32_3495;
        Str *hoisted__Str_3496 = U32_to_str(&self->cap);
        (void)hoisted__Str_3496;
        Array_set(_va_Array_103, &hoisted__U32_3495, hoisted__Str_3496);
        U32 hoisted__U32_3497 = 4;
        (void)hoisted__U32_3497;
        Str hoisted__Str_3498 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3498;
        Array_set(_va_Array_103, &hoisted__U32_3497, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3498; _oa; }));
        Str hoisted__Str_3499 = (Str){.c_str = (void *)"./src/core/array.til:49:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3499;
        panic(&hoisted__Str_3499, _va_Array_103);
        Str_delete(&hoisted__Str_3499, &(Bool){0});
    }
    U32 hoisted__U64_3501 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3501;
    void *hoisted__v_3502 = ptr_add(self->data, hoisted__U64_3501);
    (void)hoisted__v_3502;
    (void)hoisted__v_3502;
    Bool hoisted__Bool_3503 = 0;
    (void)hoisted__Bool_3503;
    ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3502, &hoisted__Bool_3503);
    U32 hoisted__U64_3504 = U32_mul(DEREF(i), self->elem_size);
    (void)hoisted__U64_3504;
    void *hoisted__v_3505 = ptr_add(self->data, hoisted__U64_3504);
    (void)hoisted__v_3505;
    (void)hoisted__v_3505;
    memcpy(hoisted__v_3505, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool * call_free) {
    {
        U32 _re_U32_3506 = self->cap;
        (void)_re_U32_3506;
        U32 _rc_U32_3506 = 0;
        (void)_rc_U32_3506;
        Bool hoisted__Bool_3515 = U32_lte(&_rc_U32_3506, &_re_U32_3506);
        (void)hoisted__Bool_3515;
        if (hoisted__Bool_3515) {
            while (1) {
                Bool _wcond_Bool_3507 = U32_lt(&_rc_U32_3506, &_re_U32_3506);
                (void)_wcond_Bool_3507;
                if (_wcond_Bool_3507) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3506);
                U32_inc(&_rc_U32_3506);
                U32 hoisted__U64_3508 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3508;
                void *hoisted__v_3509 = ptr_add(self->data, hoisted__U64_3508);
                (void)hoisted__v_3509;
                (void)hoisted__v_3509;
                Bool hoisted__Bool_3510 = 0;
                (void)hoisted__Bool_3510;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3509, &hoisted__Bool_3510);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3511 = U32_gt(&_rc_U32_3506, &_re_U32_3506);
                (void)_wcond_Bool_3511;
                if (_wcond_Bool_3511) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3506);
                U32_dec(&_rc_U32_3506);
                U32 hoisted__U64_3512 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3512;
                void *hoisted__v_3513 = ptr_add(self->data, hoisted__U64_3512);
                (void)hoisted__v_3513;
                (void)hoisted__v_3513;
                Bool hoisted__Bool_3514 = 0;
                (void)hoisted__Bool_3514;
                ((void (*)(void *, Bool *))(void *)(self->elem_delete))(hoisted__v_3513, &hoisted__Bool_3514);
            }
        }
    }
    free(self->data);
    if (DEREF(call_free)) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3528 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3528;
    void * new_data = malloc(hoisted__U64_3528);
    {
        U32 _re_U32_3516 = self->cap;
        (void)_re_U32_3516;
        U32 _rc_U32_3516 = 0;
        (void)_rc_U32_3516;
        Bool hoisted__Bool_3527 = U32_lte(&_rc_U32_3516, &_re_U32_3516);
        (void)hoisted__Bool_3527;
        if (hoisted__Bool_3527) {
            while (1) {
                Bool _wcond_Bool_3517 = U32_lt(&_rc_U32_3516, &_re_U32_3516);
                (void)_wcond_Bool_3517;
                if (_wcond_Bool_3517) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3516);
                U32_inc(&_rc_U32_3516);
                U32 hoisted__U64_3518 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3518;
                void *hoisted__v_3519 = ptr_add(self->data, hoisted__U64_3518);
                (void)hoisted__v_3519;
                (void)hoisted__v_3519;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3519);
                U32 hoisted__U64_3520 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3520;
                void *hoisted__v_3521 = ptr_add(new_data, hoisted__U64_3520);
                (void)hoisted__v_3521;
                (void)hoisted__v_3521;
                memcpy(hoisted__v_3521, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3522 = U32_gt(&_rc_U32_3516, &_re_U32_3516);
                (void)_wcond_Bool_3522;
                if (_wcond_Bool_3522) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3516);
                U32_dec(&_rc_U32_3516);
                U32 hoisted__U64_3523 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3523;
                void *hoisted__v_3524 = ptr_add(self->data, hoisted__U64_3523);
                (void)hoisted__v_3524;
                (void)hoisted__v_3524;
                void * cloned = ((void * (*)(void *))(void *)(self->elem_clone))(hoisted__v_3524);
                U32 hoisted__U64_3525 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3525;
                void *hoisted__v_3526 = ptr_add(new_data, hoisted__U64_3525);
                (void)hoisted__v_3526;
                (void)hoisted__v_3526;
                memcpy(hoisted__v_3526, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3529 = malloc(sizeof(Array));
    hoisted__Array_3529->data = new_data;
    hoisted__Array_3529->cap = self->cap;
    hoisted__Array_3529->elem_size = self->elem_size;
    hoisted__Array_3529->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3529->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3529;
    return hoisted__Array_3529;
}

U32 Array_size(void) {
    U32 hoisted__U32_3530 = 32;
    (void)hoisted__U32_3530;
    return hoisted__U32_3530;
}

void panic(Str * loc_str, Array * parts) {
    Str hoisted__Str_3767 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3767;
    Type *hoisted__Type_3768 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3767; _oa; }));
    (void)hoisted__Type_3768;
    U32 hoisted__U32_3769 = 3;
    (void)hoisted__U32_3769;
    Array *_va_Array_120 = Array_new(hoisted__Type_3768, &hoisted__U32_3769);
    (void)_va_Array_120;
    Type_delete(hoisted__Type_3768, &(Bool){1});
    U32 hoisted__U32_3770 = 0;
    (void)hoisted__U32_3770;
    Str *hoisted__Str_3771 = Str_clone(loc_str);
    (void)hoisted__Str_3771;
    Array_set(_va_Array_120, &hoisted__U32_3770, hoisted__Str_3771);
    U32 hoisted__U32_3772 = 1;
    (void)hoisted__U32_3772;
    Str hoisted__Str_3773 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3773;
    Array_set(_va_Array_120, &hoisted__U32_3772, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3773; _oa; }));
    Array *hoisted__Array_3774 = Array_clone(parts);
    (void)hoisted__Array_3774;
    Array_delete(parts, &(Bool){1});
    U32 hoisted__U32_3775 = 2;
    (void)hoisted__U32_3775;
    Str *hoisted__Str_3776 = format(hoisted__Array_3774);
    (void)hoisted__Str_3776;
    Array_set(_va_Array_120, &hoisted__U32_3775, hoisted__Str_3776);
    println(_va_Array_120);
    I64 hoisted__I64_3777 = 1;
    (void)hoisted__I64_3777;
    exit(hoisted__I64_3777);
}

void UNREACHABLE(Str * loc_str) {
    Str hoisted__Str_3786 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3786;
    Type *hoisted__Type_3787 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3786; _oa; }));
    (void)hoisted__Type_3787;
    U32 hoisted__U32_3788 = 1;
    (void)hoisted__U32_3788;
    Array *_va_Array_122 = Array_new(hoisted__Type_3787, &hoisted__U32_3788);
    (void)_va_Array_122;
    Type_delete(hoisted__Type_3787, &(Bool){1});
    U32 hoisted__U32_3789 = 0;
    (void)hoisted__U32_3789;
    Str hoisted__Str_3790 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_3790;
    Array_set(_va_Array_122, &hoisted__U32_3789, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3790; _oa; }));
    panic(loc_str, _va_Array_122);
}

Bool * assert(Str * loc_str, Bool * cond) {
    Bool hoisted__Bool_3796 = not(DEREF(cond));
    (void)hoisted__Bool_3796;
    if (hoisted__Bool_3796) {
        Str hoisted__Str_3791 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3791;
        Type *hoisted__Type_3792 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3791; _oa; }));
        (void)hoisted__Type_3792;
        U32 hoisted__U32_3793 = 1;
        (void)hoisted__U32_3793;
        Array *_va_Array_123 = Array_new(hoisted__Type_3792, &hoisted__U32_3793);
        (void)_va_Array_123;
        Type_delete(hoisted__Type_3792, &(Bool){1});
        U32 hoisted__U32_3794 = 0;
        (void)hoisted__U32_3794;
        Str hoisted__Str_3795 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3795;
        Array_set(_va_Array_123, &hoisted__U32_3794, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3795; _oa; }));
        panic(loc_str, _va_Array_123);
    }
    Bool hoisted__Bool_3797 = 1;
    (void)hoisted__Bool_3797;
    { Bool *_r = malloc(sizeof(Bool)); *_r = hoisted__Bool_3797;
    return _r; }
}

void assert_eq(Str * loc_str, I64 * a, I64 * b) {
    Bool hoisted__Bool_3820 = I64_neq(a, b);
    (void)hoisted__Bool_3820;
    if (hoisted__Bool_3820) {
        Str hoisted__Str_3807 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3807;
        Type *hoisted__Type_3808 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3807; _oa; }));
        (void)hoisted__Type_3808;
        U32 hoisted__U32_3809 = 5;
        (void)hoisted__U32_3809;
        Array *_va_Array_125 = Array_new(hoisted__Type_3808, &hoisted__U32_3809);
        (void)_va_Array_125;
        Type_delete(hoisted__Type_3808, &(Bool){1});
        U32 hoisted__U32_3810 = 0;
        (void)hoisted__U32_3810;
        Str hoisted__Str_3811 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3811;
        Array_set(_va_Array_125, &hoisted__U32_3810, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3811; _oa; }));
        U32 hoisted__U32_3812 = 1;
        (void)hoisted__U32_3812;
        Str *hoisted__Str_3813 = I64_to_str(a);
        (void)hoisted__Str_3813;
        Array_set(_va_Array_125, &hoisted__U32_3812, hoisted__Str_3813);
        U32 hoisted__U32_3814 = 2;
        (void)hoisted__U32_3814;
        Str hoisted__Str_3815 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3815;
        Array_set(_va_Array_125, &hoisted__U32_3814, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3815; _oa; }));
        U32 hoisted__U32_3816 = 3;
        (void)hoisted__U32_3816;
        Str *hoisted__Str_3817 = I64_to_str(b);
        (void)hoisted__Str_3817;
        Array_set(_va_Array_125, &hoisted__U32_3816, hoisted__Str_3817);
        U32 hoisted__U32_3818 = 4;
        (void)hoisted__U32_3818;
        Str hoisted__Str_3819 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3819;
        Array_set(_va_Array_125, &hoisted__U32_3818, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3819; _oa; }));
        panic(loc_str, _va_Array_125);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_3834 = Str_eq(a, b);
    (void)hoisted__Bool_3834;
    Bool hoisted__Bool_3835 = not(hoisted__Bool_3834);
    (void)hoisted__Bool_3835;
    if (hoisted__Bool_3835) {
        Str hoisted__Str_3821 = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3821;
        Type *hoisted__Type_3822 = Type_Struct(({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3821; _oa; }));
        (void)hoisted__Type_3822;
        U32 hoisted__U32_3823 = 5;
        (void)hoisted__U32_3823;
        Array *_va_Array_126 = Array_new(hoisted__Type_3822, &hoisted__U32_3823);
        (void)_va_Array_126;
        Type_delete(hoisted__Type_3822, &(Bool){1});
        U32 hoisted__U32_3824 = 0;
        (void)hoisted__U32_3824;
        Str hoisted__Str_3825 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3825;
        Array_set(_va_Array_126, &hoisted__U32_3824, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3825; _oa; }));
        U32 hoisted__U32_3826 = 1;
        (void)hoisted__U32_3826;
        Str *hoisted__Str_3827 = Str_clone(a);
        (void)hoisted__Str_3827;
        Array_set(_va_Array_126, &hoisted__U32_3826, hoisted__Str_3827);
        U32 hoisted__U32_3828 = 2;
        (void)hoisted__U32_3828;
        Str hoisted__Str_3829 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3829;
        Array_set(_va_Array_126, &hoisted__U32_3828, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3829; _oa; }));
        U32 hoisted__U32_3830 = 3;
        (void)hoisted__U32_3830;
        Str *hoisted__Str_3831 = Str_clone(b);
        (void)hoisted__Str_3831;
        Array_set(_va_Array_126, &hoisted__U32_3830, hoisted__Str_3831);
        U32 hoisted__U32_3832 = 4;
        (void)hoisted__U32_3832;
        Str hoisted__Str_3833 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3833;
        Array_set(_va_Array_126, &hoisted__U32_3832, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3833; _oa; }));
        panic(loc_str, _va_Array_126);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_3836 = parts;
        (void)_fc_Array_3836;
        (void)_fc_Array_3836;
        U32 _fi_USize_3836 = 0;
        (void)_fi_USize_3836;
        while (1) {
            U32 hoisted__U32_3838; { U32 *_hp = (U32 *)Array_len(_fc_Array_3836); hoisted__U32_3838 = *_hp; free(_hp); }
            (void)hoisted__U32_3838;
            Bool _wcond_Bool_3837 = U32_lt(&_fi_USize_3836, &hoisted__U32_3838);
            (void)_wcond_Bool_3837;
            if (_wcond_Bool_3837) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_3836, &_fi_USize_3836);
            U32 hoisted__U32_3839 = 1;
            (void)hoisted__U32_3839;
            U32 hoisted__U32_3840 = U32_add(_fi_USize_3836, hoisted__U32_3839);
            (void)hoisted__U32_3840;
            _fi_USize_3836 = hoisted__U32_3840;
            print_single(s);
        }
    }
    Array_delete(parts, &(Bool){1});
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    Str hoisted__Str_4025 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4025;
    I64 hoisted__I64_4026 = 3;
    (void)hoisted__I64_4026;
    assert_eq(&hoisted__Str_4025, &result, &hoisted__I64_4026);
    Str_delete(&hoisted__Str_4025, &(Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4033 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4033;
    I64 hoisted__I64_4034 = 15;
    (void)hoisted__I64_4034;
    assert_eq(&hoisted__Str_4033, &result, &hoisted__I64_4034);
    Str_delete(&hoisted__Str_4033, &(Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4041 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4041;
    I64 hoisted__I64_4042 = 26;
    (void)hoisted__I64_4042;
    assert_eq(&hoisted__Str_4041, &result, &hoisted__I64_4042);
    Str_delete(&hoisted__Str_4041, &(Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4045 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4045;
    Str hoisted__Str_4046 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4046;
    assert_eq_str(&hoisted__Str_4045, &result, &hoisted__Str_4046);
    Str_delete(&hoisted__Str_4045, &(Bool){0});
    Str_delete(&hoisted__Str_4046, &(Bool){0});
    Str_delete(&result, &(Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4377 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4377;
    assert_eq_str(&hoisted__Str_4377, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4377, &(Bool){0});
    Str_delete(&lola_it, &(Bool){0});
    Str_delete(&lola_rec, &(Bool){0});
    Str hoisted__Str_4378 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4378;
    assert_eq_str(&hoisted__Str_4378, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4378, &(Bool){0});
    Str_delete(&lalo_it, &(Bool){0});
    Str_delete(&lalo_rec, &(Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4380 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4380;
    I64 hoisted__I64_4381 = 8;
    (void)hoisted__I64_4381;
    assert_eq(&hoisted__Str_4380, &result, &hoisted__I64_4381);
    Str_delete(&hoisted__Str_4380, &(Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4384 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4384;
    Bool hoisted__Bool_4385 = 1;
    (void)hoisted__Bool_4385;
    Bool_delete(assert(&hoisted__Str_4384, &hoisted__Bool_4385), &(Bool){1});
    Str_delete(&hoisted__Str_4384, &(Bool){0});
    Str hoisted__Str_4389 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4389;
    Bool hoisted__Bool_4390 = 1;
    (void)hoisted__Bool_4390;
    Bool_delete(assert(&hoisted__Str_4389, &hoisted__Bool_4390), &(Bool){1});
    Str_delete(&hoisted__Str_4389, &(Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4396 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4396;
    Str hoisted__Str_4397 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4397;
    Str hoisted__Str_4398 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4398;
    assert_eq_str(&hoisted__Str_4396, &hoisted__Str_4397, &hoisted__Str_4398);
    Str_delete(&hoisted__Str_4396, &(Bool){0});
    Str_delete(&hoisted__Str_4397, &(Bool){0});
    Str_delete(&hoisted__Str_4398, &(Bool){0});
    Str hoisted__Str_4401 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4401;
    Str hoisted__Str_4402 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4402;
    Str hoisted__Str_4403 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4403;
    assert_eq_str(&hoisted__Str_4401, &hoisted__Str_4402, &hoisted__Str_4403);
    Str_delete(&hoisted__Str_4401, &(Bool){0});
    Str_delete(&hoisted__Str_4402, &(Bool){0});
    Str_delete(&hoisted__Str_4403, &(Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_4408 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_4408;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_4408;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_4409 = 16;
    (void)hoisted__U32_4409;
    return hoisted__U32_4409;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_4410 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4410;
    I64 hoisted__I64_4411 = 42;
    (void)hoisted__I64_4411;
    assert_eq(&hoisted__Str_4410, &v.x, &hoisted__I64_4411);
    Str_delete(&hoisted__Str_4410, &(Bool){0});
    Str hoisted__Str_4412 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4412;
    I64 hoisted__I64_4413 = 99;
    (void)hoisted__I64_4413;
    assert_eq(&hoisted__Str_4412, &v.y, &hoisted__I64_4413);
    Str_delete(&hoisted__Str_4412, &(Bool){0});
    CfVec2_delete(&v, &(Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_4416 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4416;
    I64 hoisted__I64_4417 = 10;
    (void)hoisted__I64_4417;
    assert_eq(&hoisted__Str_4416, &p.x, &hoisted__I64_4417);
    Str_delete(&hoisted__Str_4416, &(Bool){0});
    Str hoisted__Str_4418 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4418;
    I64 hoisted__I64_4419 = 20;
    (void)hoisted__I64_4419;
    assert_eq(&hoisted__Str_4418, &p.y, &hoisted__I64_4419);
    Str_delete(&hoisted__Str_4418, &(Bool){0});
    CfVec2_delete(&p, &(Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_4425 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_4425;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_4425;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

U32 CfRect_size(void) {
    U32 hoisted__U32_4426 = 32;
    (void)hoisted__U32_4426;
    return hoisted__U32_4426;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_4427 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4427;
    I64 hoisted__I64_4428 = 5;
    (void)hoisted__I64_4428;
    assert_eq(&hoisted__Str_4427, &r.top_left.x, &hoisted__I64_4428);
    Str_delete(&hoisted__Str_4427, &(Bool){0});
    Str hoisted__Str_4429 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4429;
    I64 hoisted__I64_4430 = 10;
    (void)hoisted__I64_4430;
    assert_eq(&hoisted__Str_4429, &r.top_left.y, &hoisted__I64_4430);
    Str_delete(&hoisted__Str_4429, &(Bool){0});
    Str hoisted__Str_4431 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4431;
    I64 hoisted__I64_4432 = 100;
    (void)hoisted__I64_4432;
    assert_eq(&hoisted__Str_4431, &r.bottom_right.x, &hoisted__I64_4432);
    Str_delete(&hoisted__Str_4431, &(Bool){0});
    Str hoisted__Str_4433 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4433;
    I64 hoisted__I64_4434 = 200;
    (void)hoisted__I64_4434;
    assert_eq(&hoisted__Str_4433, &r.bottom_right.y, &hoisted__I64_4434);
    Str_delete(&hoisted__Str_4433, &(Bool){0});
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
    Bool hoisted__Bool_4439 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4439;
    if (hoisted__Bool_4439) {
        Bool hoisted__Bool_4436 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_4436;
        { Bool _ret_val = hoisted__Bool_4436;
                return _ret_val; }
    }
    Bool hoisted__Bool_4440 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4440;
    if (hoisted__Bool_4440) {
        Bool hoisted__Bool_4437 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_4437;
        { Bool _ret_val = hoisted__Bool_4437;
                return _ret_val; }
    }
    Bool hoisted__Bool_4441 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4441;
    if (hoisted__Bool_4441) {
        Bool hoisted__Bool_4438 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_4438;
        { Bool _ret_val = hoisted__Bool_4438;
                return _ret_val; }
    }
    Bool hoisted__Bool_4442 = 0;
    (void)hoisted__Bool_4442;
    return hoisted__Bool_4442;
}

void Color_delete(Color * self, Bool * call_free) {
    if (DEREF(call_free)) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_4450 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4450;
    if (hoisted__Bool_4450) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_4451 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4451;
    if (hoisted__Bool_4451) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_4452 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_4452;
    if (hoisted__Bool_4452) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_4453 = (Str){.c_str = (void *)"Color.clone:167:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4453;
    UNREACHABLE(&hoisted__Str_4453);
    Str_delete(&hoisted__Str_4453, &(Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_4454 = 4;
    (void)hoisted__U32_4454;
    return hoisted__U32_4454;
}


void test_enum_fold(void) {
    Color *c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Str hoisted__Str_4455 = (Str){.c_str = (void *)"test/constfold.til:172:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4455;
    Bool hoisted__Bool_4456 = Color_eq(c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_4456;
    Bool_delete(assert(&hoisted__Str_4455, &hoisted__Bool_4456), &(Bool){1});
    Str_delete(&hoisted__Str_4455, &(Bool){0});
    Bool hoisted__Bool_4458 = Color_eq(c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_4458;
    Color_delete(c, &(Bool){1});
    Str hoisted__Str_4459 = (Str){.c_str = (void *)"test/constfold.til:173:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4459;
    Bool hoisted__Bool_4460 = not(hoisted__Bool_4458);
    (void)hoisted__Bool_4460;
    Bool_delete(assert(&hoisted__Str_4459, &hoisted__Bool_4460), &(Bool){1});
    Str_delete(&hoisted__Str_4459, &(Bool){0});
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
    Bool hoisted__Bool_4462 = is(self, other);
    (void)hoisted__Bool_4462;
    return hoisted__Bool_4462;
}

void Token_delete(Token * self, Bool * call_free) {
    Bool hoisted__Bool_4480 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4480;
    if (hoisted__Bool_4480) {
        I64 *hoisted__I64_4476 = get_payload(self);
        (void)hoisted__I64_4476;
        (void)hoisted__I64_4476;
        Bool hoisted__Bool_4477 = 0;
        (void)hoisted__Bool_4477;
        I64_delete(hoisted__I64_4476, &hoisted__Bool_4477);
    }
    Bool hoisted__Bool_4481 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4481;
    if (hoisted__Bool_4481) {
        Str *hoisted__Str_4478 = get_payload(self);
        (void)hoisted__Str_4478;
        (void)hoisted__Str_4478;
        Bool hoisted__Bool_4479 = 0;
        (void)hoisted__Bool_4479;
        Str_delete(hoisted__Str_4478, &hoisted__Bool_4479);
    }
    if (DEREF(call_free)) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_4510 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4510;
    if (hoisted__Bool_4510) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_4507 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_4507;
        { Token * _ret_val = hoisted__Token_4507;
                return _ret_val; }
    }
    Bool hoisted__Bool_4511 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_4511;
    if (hoisted__Bool_4511) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_4508 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_4508;
        Token *hoisted__Token_4509 = Token_Name(hoisted__Str_4508);
        (void)hoisted__Token_4509;
        { Token * _ret_val = hoisted__Token_4509;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_4512 = 24;
    (void)hoisted__U32_4512;
    return hoisted__U32_4512;
}


void test_enum_payload_fold(void) {
    I64 hoisted__I64_4513 = 42;
    (void)hoisted__I64_4513;
    Token *t = Token_Num(&hoisted__I64_4513);
    Str hoisted__Str_4514 = (Str){.c_str = (void *)"test/constfold.til:181:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4514;
    Bool hoisted__Bool_4515 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_4515;
    Bool_delete(assert(&hoisted__Str_4514, &hoisted__Bool_4515), &(Bool){1});
    Str_delete(&hoisted__Str_4514, &(Bool){0});
    Bool hoisted__Bool_4517 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_4517;
    Token_delete(t, &(Bool){1});
    Str hoisted__Str_4518 = (Str){.c_str = (void *)"test/constfold.til:182:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4518;
    Bool hoisted__Bool_4519 = not(hoisted__Bool_4517);
    (void)hoisted__Bool_4519;
    Bool_delete(assert(&hoisted__Str_4518, &hoisted__Bool_4519), &(Bool){1});
    Str_delete(&hoisted__Str_4518, &(Bool){0});
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
        return 1LL;
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
    fprintf(stderr, "13/13 tests passed\n");
    return 0;
}
