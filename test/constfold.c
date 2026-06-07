#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#include "ext.h"

typedef struct TilClosure TilClosure;
struct TilClosure {
    void *call;
    void *env;
    void (*drop)(void *);
};

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

typedef TilClosure *CloneFn;
typedef TilClosure *DeleteFn;
typedef TilClosure *HashFn;







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
    TilClosure * elem_clone;
    TilClosure * elem_delete;
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
static void * default_clone__til_closure_call(void *til_env, void * v);
static __attribute__((unused)) TilClosure default_clone__til_closure;
void default_delete(void * _v, Bool _cf);
static void default_delete__til_closure_call(void *til_env, void * _v, Bool _cf);
static __attribute__((unused)) TilClosure default_delete__til_closure;
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
    U64 hoisted__U64_13 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_12); });
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
    U64 hoisted__U64_113 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_112); });
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
    U64 hoisted__U64_216 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_215); });
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
    U64 hoisted__U64_376 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_375); });
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
    U64 hoisted__U64_415 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_414); });
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
    U64 hoisted__U64_518 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_517); });
    (void)hoisted__U64_518;
    return hoisted__U64_518;
}

Str * format(Array * parts) {
    U32 total = 0;
    {
        Array *_fc_Array_782 = parts;
        (void)_fc_Array_782;
        (void)_fc_Array_782;
        U32 _fi_USize_782 = 0;
        (void)_fi_USize_782;
        I64 _forin_err_kind_782 = 0;
        (void)_forin_err_kind_782;
        OutOfBounds *_forin_OutOfBounds_782 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_782->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_782;
        while (1) {
            U32 hoisted__U32_790 = Array_len(_fc_Array_782);
            (void)hoisted__U32_790;
            Bool _wcond_Bool_783 = U32_lt(_fi_USize_782, hoisted__U32_790);
            (void)_wcond_Bool_783;
            if (_wcond_Bool_783) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_782, &_fi_USize_782, &_forin_err_kind_782, _forin_OutOfBounds_782);
            I64 hoisted__I64_791 = 0;
            (void)hoisted__I64_791;
            Bool hoisted__Bool_792 = I64_eq(_forin_err_kind_782, hoisted__I64_791);
            (void)hoisted__Bool_792;
            Bool hoisted__Bool_793 = not(hoisted__Bool_792);
            (void)hoisted__Bool_793;
            if (hoisted__Bool_793) {
                Type *hoisted__Type_785 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_785;
                U32 hoisted__U32_786 = 1;
                (void)hoisted__U32_786;
                Array *_va_Array_23 = Array_new(hoisted__Type_785, hoisted__U32_786);
                (void)_va_Array_23;
                Type_delete(hoisted__Type_785, 1);
                U32 hoisted__U32_787 = 0;
                (void)hoisted__U32_787;
                Str hoisted__Str_788 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_788;
                Array_set(_va_Array_23, hoisted__U32_787, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_788; _oa; }));
                Str hoisted__Str_789 = (Str){.c_str = (void *)"./src/core/str.til:19:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_789;
                panic(&hoisted__Str_789, _va_Array_23);
                Str_delete(&hoisted__Str_789, (Bool){0});
            }
            U32 hoisted__U32_794 = 1;
            (void)hoisted__U32_794;
            U32 hoisted__U32_795 = U32_add(_fi_USize_782, hoisted__U32_794);
            (void)hoisted__U32_795;
            _fi_USize_782 = hoisted__U32_795;
            U32 hoisted__U32_796 = Str_len(s);
            (void)hoisted__U32_796;
            U32 hoisted__U32_797 = U32_add(total, hoisted__U32_796);
            (void)hoisted__U32_797;
            total = hoisted__U32_797;
        }
        OutOfBounds_delete(_forin_OutOfBounds_782, 1);
    }
    Str *out = Str_with_capacity(total);
    {
        Array *_fc_Array_798 = parts;
        (void)_fc_Array_798;
        (void)_fc_Array_798;
        U32 _fi_USize_798 = 0;
        (void)_fi_USize_798;
        I64 _forin_err_kind_798 = 0;
        (void)_forin_err_kind_798;
        OutOfBounds *_forin_OutOfBounds_798 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_798->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_798;
        while (1) {
            U32 hoisted__U32_806 = Array_len(_fc_Array_798);
            (void)hoisted__U32_806;
            Bool _wcond_Bool_799 = U32_lt(_fi_USize_798, hoisted__U32_806);
            (void)_wcond_Bool_799;
            if (_wcond_Bool_799) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_798, &_fi_USize_798, &_forin_err_kind_798, _forin_OutOfBounds_798);
            I64 hoisted__I64_807 = 0;
            (void)hoisted__I64_807;
            Bool hoisted__Bool_808 = I64_eq(_forin_err_kind_798, hoisted__I64_807);
            (void)hoisted__Bool_808;
            Bool hoisted__Bool_809 = not(hoisted__Bool_808);
            (void)hoisted__Bool_809;
            if (hoisted__Bool_809) {
                Type *hoisted__Type_801 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_801;
                U32 hoisted__U32_802 = 1;
                (void)hoisted__U32_802;
                Array *_va_Array_24 = Array_new(hoisted__Type_801, hoisted__U32_802);
                (void)_va_Array_24;
                Type_delete(hoisted__Type_801, 1);
                U32 hoisted__U32_803 = 0;
                (void)hoisted__U32_803;
                Str hoisted__Str_804 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_804;
                Array_set(_va_Array_24, hoisted__U32_803, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_804; _oa; }));
                Str hoisted__Str_805 = (Str){.c_str = (void *)"./src/core/str.til:23:9", .count = 23ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_805;
                panic(&hoisted__Str_805, _va_Array_24);
                Str_delete(&hoisted__Str_805, (Bool){0});
            }
            U32 hoisted__U32_810 = 1;
            (void)hoisted__U32_810;
            U32 hoisted__U32_811 = U32_add(_fi_USize_798, hoisted__U32_810);
            (void)hoisted__U32_811;
            _fi_USize_798 = hoisted__U32_811;
            Str_push_str(out, s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_798, 1);
    }
    Array_delete(parts, 1);
    return out;
}

U32 Str_len(Str * self) {
    return self->count;
}

I8 * Str_get(Str * self, U32 * i) {
    Bool hoisted__Bool_818 = U32_gte(DEREF(i), self->count);
    (void)hoisted__Bool_818;
    if (hoisted__Bool_818) {
        Type *hoisted__Type_813 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_813;
        U32 hoisted__U32_814 = 1;
        (void)hoisted__U32_814;
        Array *_va_Array_25 = Array_new(hoisted__Type_813, hoisted__U32_814);
        (void)_va_Array_25;
        Type_delete(hoisted__Type_813, 1);
        U32 hoisted__U32_815 = 0;
        (void)hoisted__U32_815;
        Str hoisted__Str_816 = (Str){.c_str = (void *)"Str.get: index out of bounds", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_816;
        Array_set(_va_Array_25, hoisted__U32_815, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_816; _oa; }));
        Str hoisted__Str_817 = (Str){.c_str = (void *)"./src/core/str.til:43:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_817;
        panic(&hoisted__Str_817, _va_Array_25);
        Str_delete(&hoisted__Str_817, (Bool){0});
    }
    void *hoisted__v_819 = ptr_add(self->c_str, DEREF(i));
    (void)hoisted__v_819;
    (void)hoisted__v_819;
    return hoisted__v_819;
}

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_829 = U32_lt(b->count, a->count);
    (void)hoisted__Bool_829;
    if (hoisted__Bool_829) {
        min_len = b->count;
    }
    {
        U32 _re_U32_821 = U32_clone(&min_len);
        (void)_re_U32_821;
        U32 _rc_U32_821 = 0;
        (void)_rc_U32_821;
        Bool hoisted__Bool_828 = U32_lte(_rc_U32_821, _re_U32_821);
        (void)hoisted__Bool_828;
        if (hoisted__Bool_828) {
            while (1) {
                Bool _wcond_Bool_822 = U32_lt(_rc_U32_821, _re_U32_821);
                (void)_wcond_Bool_822;
                if (_wcond_Bool_822) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_821);
                U32_inc(&_rc_U32_821);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_823 = 0;
                (void)hoisted__I64_823;
                Bool hoisted__Bool_824 = I64_neq(c, hoisted__I64_823);
                (void)hoisted__Bool_824;
                if (hoisted__Bool_824) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        } else {
            while (1) {
                Bool _wcond_Bool_825 = U32_gt(_rc_U32_821, _re_U32_821);
                (void)_wcond_Bool_825;
                if (_wcond_Bool_825) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_821);
                U32_dec(&_rc_U32_821);
                I8 *ab = Str_get(a, &i);
                I8 *bb = Str_get(b, &i);
                I64 c = I8_cmp(DEREF(ab), DEREF(bb));
                I64 hoisted__I64_826 = 0;
                (void)hoisted__I64_826;
                Bool hoisted__Bool_827 = I64_neq(c, hoisted__I64_826);
                (void)hoisted__Bool_827;
                if (hoisted__Bool_827) {
                    { I64 _ret_val = c;
                                                                                                                        return _ret_val; }
                }
            }
        }
    }
    I64 hoisted__I64_830 = U32_cmp(a->count, b->count);
    (void)hoisted__I64_830;
    return hoisted__I64_830;
}

Str * Str_with_capacity(U32 n) {
    U32 hoisted__U32_832 = 1;
    (void)hoisted__U32_832;
    U32 hoisted__U64_833 = U32_add(n, hoisted__U32_832);
    (void)hoisted__U64_833;
    void * buf = malloc(hoisted__U64_833);
    I32 hoisted__I32_834 = 0;
    (void)hoisted__I32_834;
    U64 hoisted__U64_835 = 1ULL;
    (void)hoisted__U64_835;
    memset(buf, hoisted__I32_834, hoisted__U64_835);
    I64 hoisted__I64_836 = 0;
    (void)hoisted__I64_836;
    Str *hoisted__Str_837 = malloc(sizeof(Str));
    hoisted__Str_837->c_str = buf;
    hoisted__Str_837->count = hoisted__I64_836;
    hoisted__Str_837->cap = n;
    (void)hoisted__Str_837;
    return hoisted__Str_837;
}

void Str_push_str(Str * self, Str * s) {
    Bool hoisted__Bool_852 = U32_gte(self->cap, CAP_VIEW);
    (void)hoisted__Bool_852;
    if (hoisted__Bool_852) {
        Type *hoisted__Type_841 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_841;
        U32 hoisted__U32_842 = 1;
        (void)hoisted__U32_842;
        Array *_va_Array_26 = Array_new(hoisted__Type_841, hoisted__U32_842);
        (void)_va_Array_26;
        Type_delete(hoisted__Type_841, 1);
        U32 hoisted__U32_843 = 0;
        (void)hoisted__U32_843;
        Str hoisted__Str_844 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_844;
        Array_set(_va_Array_26, hoisted__U32_843, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_844; _oa; }));
        Str hoisted__Str_845 = (Str){.c_str = (void *)"./src/core/str.til:92:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_845;
        panic(&hoisted__Str_845, _va_Array_26);
        Str_delete(&hoisted__Str_845, (Bool){0});
    }
    U32 new_len = U32_add(self->count, s->count);
    Bool hoisted__Bool_853 = U32_gt(new_len, self->cap);
    (void)hoisted__Bool_853;
    if (hoisted__Bool_853) {
        Type *hoisted__Type_847 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_847;
        U32 hoisted__U32_848 = 1;
        (void)hoisted__U32_848;
        Array *_va_Array_27 = Array_new(hoisted__Type_847, hoisted__U32_848);
        (void)_va_Array_27;
        Type_delete(hoisted__Type_847, 1);
        U32 hoisted__U32_849 = 0;
        (void)hoisted__U32_849;
        Str hoisted__Str_850 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_850;
        Array_set(_va_Array_27, hoisted__U32_849, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_850; _oa; }));
        Str hoisted__Str_851 = (Str){.c_str = (void *)"./src/core/str.til:96:19", .count = 24ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_851;
        panic(&hoisted__Str_851, _va_Array_27);
        Str_delete(&hoisted__Str_851, (Bool){0});
    }
    void *hoisted__v_854 = ptr_add(self->c_str, self->count);
    (void)hoisted__v_854;
    (void)hoisted__v_854;
    memcpy(hoisted__v_854, s->c_str, s->count);
    self->count = U32_clone(&new_len);
    void *hoisted__v_855 = ptr_add(self->c_str, new_len);
    (void)hoisted__v_855;
    (void)hoisted__v_855;
    I32 hoisted__I32_856 = 0;
    (void)hoisted__I32_856;
    U64 hoisted__U64_857 = 1ULL;
    (void)hoisted__U64_857;
    memset(hoisted__v_855, hoisted__I32_856, hoisted__U64_857);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_858 = 1;
    (void)hoisted__U32_858;
    U32 hoisted__U64_859 = U32_add(val->count, hoisted__U32_858);
    (void)hoisted__U64_859;
    void * new_data = malloc(hoisted__U64_859);
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_860 = ptr_add(new_data, val->count);
    (void)hoisted__v_860;
    (void)hoisted__v_860;
    I32 hoisted__I32_861 = 0;
    (void)hoisted__I32_861;
    U64 hoisted__U64_862 = 1ULL;
    (void)hoisted__U64_862;
    memset(hoisted__v_860, hoisted__I32_861, hoisted__U64_862);
    Str *hoisted__Str_863 = malloc(sizeof(Str));
    hoisted__Str_863->c_str = new_data;
    hoisted__Str_863->count = val->count;
    hoisted__Str_863->cap = val->count;
    (void)hoisted__Str_863;
    return hoisted__Str_863;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_864 = U32_lt(self->cap, CAP_STATIC);
    (void)hoisted__Bool_864;
    if (hoisted__Bool_864) {
        free(self->c_str);
    }
    Bool hoisted__Bool_865 = U32_neq(self->cap, CAP_STATIC);
    (void)hoisted__Bool_865;
    Bool hoisted__Bool_866 = and(call_free, hoisted__Bool_865);
    (void)hoisted__Bool_866;
    if (hoisted__Bool_866) {
        free(self);
    }
}

Bool Str_is_empty(Str * self) {
    U32 hoisted__U32_979 = 0;
    (void)hoisted__U32_979;
    Bool hoisted__Bool_980 = U32_eq(self->count, hoisted__U32_979);
    (void)hoisted__Bool_980;
    return hoisted__Bool_980;
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_1073 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    (void)hoisted__U64_1073;
    return hoisted__U64_1073;
}

U32 Str_size(void) {
    U32 hoisted__U32_1260 = 16;
    (void)hoisted__U32_1260;
    return hoisted__U32_1260;
}

Bool Str_eq(Str * a, Str * b) {
    I64 hoisted__I64_1261 = Str_cmp(a, b);
    (void)hoisted__I64_1261;
    I64 hoisted__I64_1262 = 0;
    (void)hoisted__I64_1262;
    Bool hoisted__Bool_1263 = I64_eq(hoisted__I64_1261, hoisted__I64_1262);
    (void)hoisted__Bool_1263;
    return hoisted__Bool_1263;
}

OutOfBounds * OutOfBounds_clone(OutOfBounds * self) {
    OutOfBounds *hoisted__OutOfBounds_1361 = malloc(sizeof(OutOfBounds));
    { Str *_ca = Str_clone(&self->msg); hoisted__OutOfBounds_1361->msg = *_ca; free(_ca); }
    (void)hoisted__OutOfBounds_1361;
    return hoisted__OutOfBounds_1361;
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    Bool hoisted__Bool_1362 = 0;
    (void)hoisted__Bool_1362;
    Str_delete(&self->msg, hoisted__Bool_1362);
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_1363 = 0;
    (void)hoisted__U32_1363;
    U64 hoisted__U64_1364 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_1363); });
    (void)hoisted__U64_1364;
    return hoisted__U64_1364;
}

U32 OutOfBounds_size(void) {
    U32 hoisted__U32_1365 = 16;
    (void)hoisted__U32_1365;
    return hoisted__U32_1365;
}

U32 Dynamic_size(void) {
    U32 hoisted__U32_1374 = 8;
    (void)hoisted__U32_1374;
    return hoisted__U32_1374;
}

void * default_clone(void * v) {
    return v;
}
static void * default_clone__til_closure_call(void *til_env, void * v) {
    (void)til_env;
    return default_clone(v);
}
static __attribute__((unused)) TilClosure default_clone__til_closure = { (void *)default_clone__til_closure_call, NULL, NULL };

void default_delete(void * _v, Bool _cf) {
    (void)_v;
    (void)_cf;
}
static void default_delete__til_closure_call(void *til_env, void * _v, Bool _cf) {
    (void)til_env;
    default_delete(_v, _cf);
}
static __attribute__((unused)) TilClosure default_delete__til_closure = { (void *)default_delete__til_closure_call, NULL, NULL };

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1579 = 0;
    (void)hoisted__I64_1579;
    Bool hoisted__Bool_1580 = I64_eq(val, hoisted__I64_1579);
    (void)hoisted__Bool_1580;
    if (hoisted__Bool_1580) {
        U64 hoisted__U64_1543 = 2ULL;
        (void)hoisted__U64_1543;
        void * buf = malloc(hoisted__U64_1543);
        I64 hoisted__I64_1544 = 48;
        (void)hoisted__I64_1544;
        U64 hoisted__U64_1545 = 1ULL;
        (void)hoisted__U64_1545;
        memcpy(buf, &hoisted__I64_1544, hoisted__U64_1545);
        U64 hoisted__U64_1546 = 1ULL;
        (void)hoisted__U64_1546;
        void *hoisted__v_1547 = ptr_add(buf, hoisted__U64_1546);
        (void)hoisted__v_1547;
        (void)hoisted__v_1547;
        I32 hoisted__I32_1548 = 0;
        (void)hoisted__I32_1548;
        U64 hoisted__U64_1549 = 1ULL;
        (void)hoisted__U64_1549;
        memset(hoisted__v_1547, hoisted__I32_1548, hoisted__U64_1549);
        I64 hoisted__I64_1550 = 1;
        (void)hoisted__I64_1550;
        I64 hoisted__I64_1551 = 1;
        (void)hoisted__I64_1551;
        Str *hoisted__Str_1552 = malloc(sizeof(Str));
        hoisted__Str_1552->c_str = buf;
        hoisted__Str_1552->count = hoisted__I64_1550;
        hoisted__Str_1552->cap = hoisted__I64_1551;
        (void)hoisted__Str_1552;
        { Str * _ret_val = hoisted__Str_1552;
                return _ret_val; }
    }
    Bool is_neg = 0;
    I64 v = I64_clone(&val);
    I64 hoisted__I64_1581 = 0;
    (void)hoisted__I64_1581;
    Bool hoisted__Bool_1582 = I64_lt(val, hoisted__I64_1581);
    (void)hoisted__Bool_1582;
    if (hoisted__Bool_1582) {
        Bool hoisted__Bool_1553 = 1;
        (void)hoisted__Bool_1553;
        is_neg = hoisted__Bool_1553;
        I64 hoisted__I64_1554 = 0;
        (void)hoisted__I64_1554;
        I64 hoisted__I64_1555 = I64_sub(hoisted__I64_1554, val);
        (void)hoisted__I64_1555;
        v = hoisted__I64_1555;
    }
    U64 ndigits = 0ULL;
    I64 tmp = I64_clone(&v);
    while (1) {
        I64 hoisted__I64_1557 = 0;
        (void)hoisted__I64_1557;
        Bool _wcond_Bool_1556 = I64_gt(tmp, hoisted__I64_1557);
        (void)_wcond_Bool_1556;
        if (_wcond_Bool_1556) {
        } else {
            break;
        }
        U64 hoisted__U64_1558 = 1ULL;
        (void)hoisted__U64_1558;
        U64 hoisted__U64_1559 = U64_add(ndigits, hoisted__U64_1558);
        (void)hoisted__U64_1559;
        ndigits = hoisted__U64_1559;
        I64 hoisted__I64_1560 = 10;
        (void)hoisted__I64_1560;
        I64 hoisted__I64_1561 = I64_div(tmp, hoisted__I64_1560);
        (void)hoisted__I64_1561;
        tmp = hoisted__I64_1561;
    }
    U64 total = U64_clone(&ndigits);
    if (is_neg) {
        U64 hoisted__U64_1562 = 1ULL;
        (void)hoisted__U64_1562;
        U64 hoisted__U64_1563 = U64_add(total, hoisted__U64_1562);
        (void)hoisted__U64_1563;
        total = hoisted__U64_1563;
    }
    U64 hoisted__U64_1583 = 1ULL;
    (void)hoisted__U64_1583;
    U64 hoisted__U64_1584 = U64_add(total, hoisted__U64_1583);
    (void)hoisted__U64_1584;
    void * buf = malloc(hoisted__U64_1584);
    if (is_neg) {
        I64 hoisted__I64_1564 = 45;
        (void)hoisted__I64_1564;
        U64 hoisted__U64_1565 = 1ULL;
        (void)hoisted__U64_1565;
        memcpy(buf, &hoisted__I64_1564, hoisted__U64_1565);
    }
    U64 hoisted__U64_1585 = 1ULL;
    (void)hoisted__U64_1585;
    U64 i = U64_sub(total, hoisted__U64_1585);
    while (1) {
        I64 hoisted__I64_1567 = 0;
        (void)hoisted__I64_1567;
        Bool _wcond_Bool_1566 = I64_gt(v, hoisted__I64_1567);
        (void)_wcond_Bool_1566;
        if (_wcond_Bool_1566) {
        } else {
            break;
        }
        I64 hoisted__I64_1568 = 10;
        (void)hoisted__I64_1568;
        I64 hoisted__I64_1569 = I64_mod(v, hoisted__I64_1568);
        (void)hoisted__I64_1569;
        I64 hoisted__I64_1570 = 48;
        (void)hoisted__I64_1570;
        I64 hoisted__I64_1571 = I64_add(hoisted__I64_1569, hoisted__I64_1570);
        (void)hoisted__I64_1571;
        void *hoisted__v_1572 = ptr_add(buf, i);
        (void)hoisted__v_1572;
        (void)hoisted__v_1572;
        U8 hoisted__U8_1573 = I64_to_u8(hoisted__I64_1571);
        (void)hoisted__U8_1573;
        U64 hoisted__U64_1574 = 1ULL;
        (void)hoisted__U64_1574;
        memcpy(hoisted__v_1572, &hoisted__U8_1573, hoisted__U64_1574);
        I64 hoisted__I64_1575 = 10;
        (void)hoisted__I64_1575;
        I64 hoisted__I64_1576 = I64_div(v, hoisted__I64_1575);
        (void)hoisted__I64_1576;
        v = hoisted__I64_1576;
        U64 hoisted__U64_1577 = 1ULL;
        (void)hoisted__U64_1577;
        U64 hoisted__U64_1578 = U64_sub(i, hoisted__U64_1577);
        (void)hoisted__U64_1578;
        i = hoisted__U64_1578;
    }
    void *hoisted__v_1586 = ptr_add(buf, total);
    (void)hoisted__v_1586;
    (void)hoisted__v_1586;
    I32 hoisted__I32_1587 = 0;
    (void)hoisted__I32_1587;
    U64 hoisted__U64_1588 = 1ULL;
    (void)hoisted__U64_1588;
    memset(hoisted__v_1586, hoisted__I32_1587, hoisted__U64_1588);
    Str *hoisted__Str_1589 = malloc(sizeof(Str));
    hoisted__Str_1589->c_str = buf;
    hoisted__Str_1589->count = total;
    hoisted__Str_1589->cap = total;
    (void)hoisted__Str_1589;
    return hoisted__Str_1589;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 I64_size(void) {
    U32 hoisted__U32_1609 = 8;
    (void)hoisted__U32_1609;
    return hoisted__U32_1609;
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1740 = 0;
    (void)hoisted__U32_1740;
    U64 hoisted__U64_1741 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1740); });
    (void)hoisted__U64_1741;
    return hoisted__U64_1741;
}

Bool I64_lt(I64 a, I64 b) {
    I64 hoisted__I64_1744 = I64_cmp(a, b);
    (void)hoisted__I64_1744;
    I64 hoisted__I64_1745 = -1;
    (void)hoisted__I64_1745;
    Bool hoisted__Bool_1746 = I64_eq(hoisted__I64_1744, hoisted__I64_1745);
    (void)hoisted__Bool_1746;
    return hoisted__Bool_1746;
}

Bool I64_gt(I64 a, I64 b) {
    I64 hoisted__I64_1747 = I64_cmp(a, b);
    (void)hoisted__I64_1747;
    I64 hoisted__I64_1748 = 1;
    (void)hoisted__I64_1748;
    Bool hoisted__Bool_1749 = I64_eq(hoisted__I64_1747, hoisted__I64_1748);
    (void)hoisted__Bool_1749;
    return hoisted__Bool_1749;
}

Bool I64_neq(I64 a, I64 b) {
    Bool hoisted__Bool_1750 = I64_eq(a, b);
    (void)hoisted__Bool_1750;
    Bool hoisted__Bool_1751 = not(hoisted__Bool_1750);
    (void)hoisted__Bool_1751;
    return hoisted__Bool_1751;
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1769 = Bool_eq(a, b);
    (void)hoisted__Bool_1769;
    if (hoisted__Bool_1769) {
        I64 hoisted__I64_1767 = 0;
        (void)hoisted__I64_1767;
        { I64 _ret_val = hoisted__I64_1767;
                return _ret_val; }
    }
    if (b) {
        I64 hoisted__I64_1768 = -1;
        (void)hoisted__I64_1768;
        return hoisted__I64_1768;
    }
    I64 hoisted__I64_1770 = 1;
    (void)hoisted__I64_1770;
    return hoisted__I64_1770;
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U32 Bool_size(void) {
    U32 hoisted__U32_1771 = 1;
    (void)hoisted__U32_1771;
    return hoisted__U32_1771;
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1772 = 0;
    (void)hoisted__U32_1772;
    U64 hoisted__U64_1773 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1772); });
    (void)hoisted__U64_1773;
    return hoisted__U64_1773;
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
    Bool hoisted__Bool_1929 = is(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1929;
    if (hoisted__Bool_1929) {
        Bool hoisted__Bool_1919 = is(other, &(Primitive){.tag = Primitive_TAG_I16});
        (void)hoisted__Bool_1919;
        { Bool _ret_val = hoisted__Bool_1919;
                return _ret_val; }
    }
    Bool hoisted__Bool_1930 = is(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1930;
    if (hoisted__Bool_1930) {
        Bool hoisted__Bool_1920 = is(other, &(Primitive){.tag = Primitive_TAG_U16});
        (void)hoisted__Bool_1920;
        { Bool _ret_val = hoisted__Bool_1920;
                return _ret_val; }
    }
    Bool hoisted__Bool_1931 = is(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1931;
    if (hoisted__Bool_1931) {
        Bool hoisted__Bool_1921 = is(other, &(Primitive){.tag = Primitive_TAG_I8});
        (void)hoisted__Bool_1921;
        { Bool _ret_val = hoisted__Bool_1921;
                return _ret_val; }
    }
    Bool hoisted__Bool_1932 = is(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1932;
    if (hoisted__Bool_1932) {
        Bool hoisted__Bool_1922 = is(other, &(Primitive){.tag = Primitive_TAG_U8});
        (void)hoisted__Bool_1922;
        { Bool _ret_val = hoisted__Bool_1922;
                return _ret_val; }
    }
    Bool hoisted__Bool_1933 = is(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1933;
    if (hoisted__Bool_1933) {
        Bool hoisted__Bool_1923 = is(other, &(Primitive){.tag = Primitive_TAG_U32});
        (void)hoisted__Bool_1923;
        { Bool _ret_val = hoisted__Bool_1923;
                return _ret_val; }
    }
    Bool hoisted__Bool_1934 = is(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1934;
    if (hoisted__Bool_1934) {
        Bool hoisted__Bool_1924 = is(other, &(Primitive){.tag = Primitive_TAG_I32});
        (void)hoisted__Bool_1924;
        { Bool _ret_val = hoisted__Bool_1924;
                return _ret_val; }
    }
    Bool hoisted__Bool_1935 = is(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1935;
    if (hoisted__Bool_1935) {
        Bool hoisted__Bool_1925 = is(other, &(Primitive){.tag = Primitive_TAG_U64});
        (void)hoisted__Bool_1925;
        { Bool _ret_val = hoisted__Bool_1925;
                return _ret_val; }
    }
    Bool hoisted__Bool_1936 = is(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1936;
    if (hoisted__Bool_1936) {
        Bool hoisted__Bool_1926 = is(other, &(Primitive){.tag = Primitive_TAG_I64});
        (void)hoisted__Bool_1926;
        { Bool _ret_val = hoisted__Bool_1926;
                return _ret_val; }
    }
    Bool hoisted__Bool_1937 = is(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1937;
    if (hoisted__Bool_1937) {
        Bool hoisted__Bool_1927 = is(other, &(Primitive){.tag = Primitive_TAG_F32});
        (void)hoisted__Bool_1927;
        { Bool _ret_val = hoisted__Bool_1927;
                return _ret_val; }
    }
    Bool hoisted__Bool_1938 = is(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1938;
    if (hoisted__Bool_1938) {
        Bool hoisted__Bool_1928 = is(other, &(Primitive){.tag = Primitive_TAG_Bool});
        (void)hoisted__Bool_1928;
        { Bool _ret_val = hoisted__Bool_1928;
                return _ret_val; }
    }
    Bool hoisted__Bool_1939 = 0;
    (void)hoisted__Bool_1939;
    return hoisted__Bool_1939;
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1961 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    (void)hoisted__Bool_1961;
    if (hoisted__Bool_1961) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
                return _r; }
    }
    Bool hoisted__Bool_1962 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    (void)hoisted__Bool_1962;
    if (hoisted__Bool_1962) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
                return _r; }
    }
    Bool hoisted__Bool_1963 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    (void)hoisted__Bool_1963;
    if (hoisted__Bool_1963) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
                return _r; }
    }
    Bool hoisted__Bool_1964 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    (void)hoisted__Bool_1964;
    if (hoisted__Bool_1964) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
                return _r; }
    }
    Bool hoisted__Bool_1965 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    (void)hoisted__Bool_1965;
    if (hoisted__Bool_1965) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
                return _r; }
    }
    Bool hoisted__Bool_1966 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    (void)hoisted__Bool_1966;
    if (hoisted__Bool_1966) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
                return _r; }
    }
    Bool hoisted__Bool_1967 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    (void)hoisted__Bool_1967;
    if (hoisted__Bool_1967) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
                return _r; }
    }
    Bool hoisted__Bool_1968 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    (void)hoisted__Bool_1968;
    if (hoisted__Bool_1968) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
                return _r; }
    }
    Bool hoisted__Bool_1969 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    (void)hoisted__Bool_1969;
    if (hoisted__Bool_1969) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
                return _r; }
    }
    Bool hoisted__Bool_1970 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    (void)hoisted__Bool_1970;
    if (hoisted__Bool_1970) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
                return _r; }
    }
    Str hoisted__Str_1971 = (Str){.c_str = (void *)"Primitive.clone:20:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_1971;
    UNREACHABLE(&hoisted__Str_1971);
    Str_delete(&hoisted__Str_1971, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
}

U32 Primitive_size(void) {
    U32 hoisted__U32_1972 = 4;
    (void)hoisted__U32_1972;
    return hoisted__U32_1972;
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
    Bool hoisted__Bool_2024 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2024;
    if (hoisted__Bool_2024) {
        Str *hoisted__Str_2014 = get_payload(self);
        (void)hoisted__Str_2014;
        (void)hoisted__Str_2014;
        Bool hoisted__Bool_2015 = 0;
        (void)hoisted__Bool_2015;
        Str_delete(hoisted__Str_2014, hoisted__Bool_2015);
    }
    Bool hoisted__Bool_2025 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2025;
    if (hoisted__Bool_2025) {
        Str *hoisted__Str_2016 = get_payload(self);
        (void)hoisted__Str_2016;
        (void)hoisted__Str_2016;
        Bool hoisted__Bool_2017 = 0;
        (void)hoisted__Bool_2017;
        Str_delete(hoisted__Str_2016, hoisted__Bool_2017);
    }
    Bool hoisted__Bool_2026 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2026;
    if (hoisted__Bool_2026) {
        Str *hoisted__Str_2018 = get_payload(self);
        (void)hoisted__Str_2018;
        (void)hoisted__Str_2018;
        Bool hoisted__Bool_2019 = 0;
        (void)hoisted__Bool_2019;
        Str_delete(hoisted__Str_2018, hoisted__Bool_2019);
    }
    Bool hoisted__Bool_2027 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2027;
    if (hoisted__Bool_2027) {
        Primitive *hoisted__Primitive_2020 = get_payload(self);
        (void)hoisted__Primitive_2020;
        (void)hoisted__Primitive_2020;
        Bool hoisted__Bool_2021 = 0;
        (void)hoisted__Bool_2021;
        Primitive_delete(hoisted__Primitive_2020, hoisted__Bool_2021);
    }
    Bool hoisted__Bool_2028 = is(self, &(Type){.tag = Type_TAG_FuncPtrSig});
    (void)hoisted__Bool_2028;
    if (hoisted__Bool_2028) {
        Str *hoisted__Str_2022 = get_payload(self);
        (void)hoisted__Str_2022;
        (void)hoisted__Str_2022;
        Bool hoisted__Bool_2023 = 0;
        (void)hoisted__Bool_2023;
        Str_delete(hoisted__Str_2022, hoisted__Bool_2023);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2107 = is(self, &(Type){.tag = Type_TAG_Unknown});
    (void)hoisted__Bool_2107;
    if (hoisted__Bool_2107) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
                return _r; }
    }
    Bool hoisted__Bool_2108 = is(self, &(Type){.tag = Type_TAG_None});
    (void)hoisted__Bool_2108;
    if (hoisted__Bool_2108) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
                return _r; }
    }
    Bool hoisted__Bool_2109 = is(self, &(Type){.tag = Type_TAG_Struct});
    (void)hoisted__Bool_2109;
    if (hoisted__Bool_2109) {
        Str *_clone_payload_Struct_2 = get_payload(self);
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2099 = Str_clone(_clone_payload_Struct_2);
        (void)hoisted__Str_2099;
        Type *hoisted__Type_2100 = Type_Struct(hoisted__Str_2099);
        (void)hoisted__Type_2100;
        { Type * _ret_val = hoisted__Type_2100;
                return _ret_val; }
    }
    Bool hoisted__Bool_2110 = is(self, &(Type){.tag = Type_TAG_StructDef});
    (void)hoisted__Bool_2110;
    if (hoisted__Bool_2110) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
                return _r; }
    }
    Bool hoisted__Bool_2111 = is(self, &(Type){.tag = Type_TAG_Enum});
    (void)hoisted__Bool_2111;
    if (hoisted__Bool_2111) {
        Str *_clone_payload_Enum_4 = get_payload(self);
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2101 = Str_clone(_clone_payload_Enum_4);
        (void)hoisted__Str_2101;
        Type *hoisted__Type_2102 = Type_Enum(hoisted__Str_2101);
        (void)hoisted__Type_2102;
        { Type * _ret_val = hoisted__Type_2102;
                return _ret_val; }
    }
    Bool hoisted__Bool_2112 = is(self, &(Type){.tag = Type_TAG_EnumDef});
    (void)hoisted__Bool_2112;
    if (hoisted__Bool_2112) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
                return _r; }
    }
    Bool hoisted__Bool_2113 = is(self, &(Type){.tag = Type_TAG_FuncDef});
    (void)hoisted__Bool_2113;
    if (hoisted__Bool_2113) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
                return _r; }
    }
    Bool hoisted__Bool_2114 = is(self, &(Type){.tag = Type_TAG_FuncPtr});
    (void)hoisted__Bool_2114;
    if (hoisted__Bool_2114) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
                return _r; }
    }
    Bool hoisted__Bool_2115 = is(self, &(Type){.tag = Type_TAG_Dynamic});
    (void)hoisted__Bool_2115;
    if (hoisted__Bool_2115) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
                return _r; }
    }
    Bool hoisted__Bool_2116 = is(self, &(Type){.tag = Type_TAG_Custom});
    (void)hoisted__Bool_2116;
    if (hoisted__Bool_2116) {
        Str *_clone_payload_Custom_9 = get_payload(self);
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2103 = Str_clone(_clone_payload_Custom_9);
        (void)hoisted__Str_2103;
        Type *hoisted__Type_2104 = Type_Custom(hoisted__Str_2103);
        (void)hoisted__Type_2104;
        { Type * _ret_val = hoisted__Type_2104;
                return _ret_val; }
    }
    Bool hoisted__Bool_2117 = is(self, &(Type){.tag = Type_TAG_Primitive});
    (void)hoisted__Bool_2117;
    if (hoisted__Bool_2117) {
        Primitive *_clone_payload_Primitive_10 = get_payload(self);
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2105 = DEREF(_clone_payload_Primitive_10);
        (void)hoisted__Primitive_2105;
        Type *hoisted__Type_2106 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2105; _oa; }));
        (void)hoisted__Type_2106;
        { Type * _ret_val = hoisted__Type_2106;
                return _ret_val; }
    }
    Str *_clone_payload_FuncPtrSig_11 = get_payload(self);
    (void)_clone_payload_FuncPtrSig_11;
    (void)_clone_payload_FuncPtrSig_11;
    Str *hoisted__Str_2118 = Str_clone(_clone_payload_FuncPtrSig_11);
    (void)hoisted__Str_2118;
    Type *hoisted__Type_2119 = Type_FuncPtrSig(hoisted__Str_2118);
    (void)hoisted__Type_2119;
    return hoisted__Type_2119;
}

U32 Type_size(void) {
    U32 hoisted__U32_2120 = 24;
    (void)hoisted__U32_2120;
    return hoisted__U32_2120;
}


Array * Array_new_type_name(Str * elem_type, U32 cap) {
    Bool hoisted__Bool_3798 = Str_is_empty(elem_type);
    (void)hoisted__Bool_3798;
    if (hoisted__Bool_3798) {
        Type *hoisted__Type_3793 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3793;
        U32 hoisted__U32_3794 = 1;
        (void)hoisted__U32_3794;
        Array *_va_Array_113 = Array_new(hoisted__Type_3793, hoisted__U32_3794);
        (void)_va_Array_113;
        Type_delete(hoisted__Type_3793, 1);
        U32 hoisted__U32_3795 = 0;
        (void)hoisted__U32_3795;
        Str hoisted__Str_3796 = (Str){.c_str = (void *)"Array.new: elem_type required", .count = 29ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3796;
        Array_set(_va_Array_113, hoisted__U32_3795, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3796; _oa; }));
        Str hoisted__Str_3797 = (Str){.c_str = (void *)"./src/core/array.til:22:41", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3797;
        panic(&hoisted__Str_3797, _va_Array_113);
        Str_delete(&hoisted__Str_3797, (Bool){0});
    }
    U32 elem_size = dyn_size_of(elem_type);
    void * hoisted__v_3799 = calloc(cap, elem_size);
    (void)hoisted__v_3799;
    void * hoisted__v_3800 = dyn_fn(elem_type, &(Str){.c_str=(void*)"clone", .count=5ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3800;
    void * hoisted__v_3801 = dyn_fn(elem_type, &(Str){.c_str=(void*)"delete", .count=6ULL, .cap=TIL_CAP_LIT});
    (void)hoisted__v_3801;
    Array *hoisted__Array_3802 = malloc(sizeof(Array));
    hoisted__Array_3802->data = hoisted__v_3799;
    hoisted__Array_3802->cap = cap;
    hoisted__Array_3802->elem_size = elem_size;
    hoisted__Array_3802->elem_clone = hoisted__v_3800;
    hoisted__Array_3802->elem_delete = hoisted__v_3801;
    (void)hoisted__Array_3802;
    return hoisted__Array_3802;
}

Array * Array_new(Type * T, U32 cap) {
    Str *elem_type = dyn_type_to_str(T);
    Array *hoisted__Array_3803 = Array_new_type_name(elem_type, cap);
    (void)hoisted__Array_3803;
    Str_delete(elem_type, 1);
    return hoisted__Array_3803;
}

U32 Array_len(Array * self) {
    return self->cap;
}

void * Array_get(Array * self, U32 * i, I64 * _err_kind, OutOfBounds * _err_OutOfBounds) {
    Bool hoisted__Bool_3824 = U32_gte(DEREF(i), self->cap);
    (void)hoisted__Bool_3824;
    if (hoisted__Bool_3824) {
        Type *hoisted__Type_3805 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3805;
        U32 hoisted__U32_3806 = 6;
        (void)hoisted__U32_3806;
        Array *_va_Array_114 = Array_new(hoisted__Type_3805, hoisted__U32_3806);
        (void)_va_Array_114;
        Type_delete(hoisted__Type_3805, 1);
        U32 hoisted__U32_3807 = 0;
        (void)hoisted__U32_3807;
        Str hoisted__Str_3808 = (Str){.c_str = (void *)"./src/core/array.til:41:44", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3808;
        Array_set(_va_Array_114, hoisted__U32_3807, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3808; _oa; }));
        U32 hoisted__U32_3809 = 1;
        (void)hoisted__U32_3809;
        Str hoisted__Str_3810 = (Str){.c_str = (void *)":Array.get: index ", .count = 18ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3810;
        Array_set(_va_Array_114, hoisted__U32_3809, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3810; _oa; }));
        U32 hoisted__U32_3811 = 2;
        (void)hoisted__U32_3811;
        Str *hoisted__Str_3812 = U32_to_str(DEREF(i));
        (void)hoisted__Str_3812;
        Array_set(_va_Array_114, hoisted__U32_3811, hoisted__Str_3812);
        U32 hoisted__U32_3813 = 3;
        (void)hoisted__U32_3813;
        Str hoisted__Str_3814 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3814;
        Array_set(_va_Array_114, hoisted__U32_3813, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3814; _oa; }));
        U32 hoisted__U32_3815 = 4;
        (void)hoisted__U32_3815;
        Str *hoisted__Str_3816 = U32_to_str(self->cap);
        (void)hoisted__Str_3816;
        Array_set(_va_Array_114, hoisted__U32_3815, hoisted__Str_3816);
        U32 hoisted__U32_3817 = 5;
        (void)hoisted__U32_3817;
        Str hoisted__Str_3818 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3818;
        Array_set(_va_Array_114, hoisted__U32_3817, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3818; _oa; }));
        OutOfBounds *hoisted__OutOfBounds_3819 = malloc(sizeof(OutOfBounds));
        { Str *_ca = format(_va_Array_114); hoisted__OutOfBounds_3819->msg = *_ca; free(_ca); }
        (void)hoisted__OutOfBounds_3819;
        U32 hoisted__U32_3820 = 16;
        (void)hoisted__U32_3820;
        swap(_err_OutOfBounds, hoisted__OutOfBounds_3819, hoisted__U32_3820);
        OutOfBounds_delete(hoisted__OutOfBounds_3819, 1);
        I64 hoisted__I64_3821 = 3;
        (void)hoisted__I64_3821;
        *_err_kind = hoisted__I64_3821;
    }
    I64 hoisted__I64_3825 = 0;
    (void)hoisted__I64_3825;
    Bool hoisted__Bool_3826 = I64_eq(DEREF(_err_kind), hoisted__I64_3825);
    (void)hoisted__Bool_3826;
    if (hoisted__Bool_3826) {
        U32 hoisted__U64_3822 = U32_mul(DEREF(i), self->elem_size);
        (void)hoisted__U64_3822;
        void *hoisted__v_3823 = ptr_add(self->data, hoisted__U64_3822);
        (void)hoisted__v_3823;
        (void)hoisted__v_3823;
        { void * _ret_val = hoisted__v_3823;
                return _ret_val; }
    }
    return NULL;
}

void Array_set(Array * self, U32 i, void * val) {
    Bool hoisted__Bool_3841 = U32_gte(i, self->cap);
    (void)hoisted__Bool_3841;
    if (hoisted__Bool_3841) {
        Type *hoisted__Type_3828 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_3828;
        U32 hoisted__U32_3829 = 5;
        (void)hoisted__U32_3829;
        Array *_va_Array_115 = Array_new(hoisted__Type_3828, hoisted__U32_3829);
        (void)_va_Array_115;
        Type_delete(hoisted__Type_3828, 1);
        U32 hoisted__U32_3830 = 0;
        (void)hoisted__U32_3830;
        Str hoisted__Str_3831 = (Str){.c_str = (void *)"Array.set: index ", .count = 17ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3831;
        Array_set(_va_Array_115, hoisted__U32_3830, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3831; _oa; }));
        U32 hoisted__U32_3832 = 1;
        (void)hoisted__U32_3832;
        Str *hoisted__Str_3833 = U32_to_str(i);
        (void)hoisted__Str_3833;
        Array_set(_va_Array_115, hoisted__U32_3832, hoisted__Str_3833);
        U32 hoisted__U32_3834 = 2;
        (void)hoisted__U32_3834;
        Str hoisted__Str_3835 = (Str){.c_str = (void *)" out of bounds (len ", .count = 20ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3835;
        Array_set(_va_Array_115, hoisted__U32_3834, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3835; _oa; }));
        U32 hoisted__U32_3836 = 3;
        (void)hoisted__U32_3836;
        Str *hoisted__Str_3837 = U32_to_str(self->cap);
        (void)hoisted__Str_3837;
        Array_set(_va_Array_115, hoisted__U32_3836, hoisted__Str_3837);
        U32 hoisted__U32_3838 = 4;
        (void)hoisted__U32_3838;
        Str hoisted__Str_3839 = (Str){.c_str = (void *)")", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3839;
        Array_set(_va_Array_115, hoisted__U32_3838, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_3839; _oa; }));
        Str hoisted__Str_3840 = (Str){.c_str = (void *)"./src/core/array.til:50:19", .count = 26ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_3840;
        panic(&hoisted__Str_3840, _va_Array_115);
        Str_delete(&hoisted__Str_3840, (Bool){0});
    }
    U32 hoisted__U64_3842 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3842;
    void *hoisted__v_3843 = ptr_add(self->data, hoisted__U64_3842);
    (void)hoisted__v_3843;
    (void)hoisted__v_3843;
    Bool hoisted__Bool_3844 = 0;
    (void)hoisted__Bool_3844;
    ({ TilClosure *til_closure = (TilClosure *)(self->elem_delete); ((void (*)(void *, void *, Bool))til_closure->call)(til_closure->env, hoisted__v_3843, hoisted__Bool_3844); });
    U32 hoisted__U64_3845 = U32_mul(i, self->elem_size);
    (void)hoisted__U64_3845;
    void *hoisted__v_3846 = ptr_add(self->data, hoisted__U64_3845);
    (void)hoisted__v_3846;
    (void)hoisted__v_3846;
    memcpy(hoisted__v_3846, val, self->elem_size);
    free(val);
}

void Array_delete(Array * self, Bool call_free) {
    {
        U32 _re_U32_3847 = self->cap;
        (void)_re_U32_3847;
        U32 _rc_U32_3847 = 0;
        (void)_rc_U32_3847;
        Bool hoisted__Bool_3856 = U32_lte(_rc_U32_3847, _re_U32_3847);
        (void)hoisted__Bool_3856;
        if (hoisted__Bool_3856) {
            while (1) {
                Bool _wcond_Bool_3848 = U32_lt(_rc_U32_3847, _re_U32_3847);
                (void)_wcond_Bool_3848;
                if (_wcond_Bool_3848) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3847);
                U32_inc(&_rc_U32_3847);
                U32 hoisted__U64_3849 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3849;
                void *hoisted__v_3850 = ptr_add(self->data, hoisted__U64_3849);
                (void)hoisted__v_3850;
                (void)hoisted__v_3850;
                Bool hoisted__Bool_3851 = 0;
                (void)hoisted__Bool_3851;
                ({ TilClosure *til_closure = (TilClosure *)(self->elem_delete); ((void (*)(void *, void *, Bool))til_closure->call)(til_closure->env, hoisted__v_3850, hoisted__Bool_3851); });
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3852 = U32_gt(_rc_U32_3847, _re_U32_3847);
                (void)_wcond_Bool_3852;
                if (_wcond_Bool_3852) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3847);
                U32_dec(&_rc_U32_3847);
                U32 hoisted__U64_3853 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3853;
                void *hoisted__v_3854 = ptr_add(self->data, hoisted__U64_3853);
                (void)hoisted__v_3854;
                (void)hoisted__v_3854;
                Bool hoisted__Bool_3855 = 0;
                (void)hoisted__Bool_3855;
                ({ TilClosure *til_closure = (TilClosure *)(self->elem_delete); ((void (*)(void *, void *, Bool))til_closure->call)(til_closure->env, hoisted__v_3854, hoisted__Bool_3855); });
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array * Array_clone(Array * self) {
    U32 hoisted__U64_3869 = U32_mul(self->cap, self->elem_size);
    (void)hoisted__U64_3869;
    void * new_data = malloc(hoisted__U64_3869);
    {
        U32 _re_U32_3857 = self->cap;
        (void)_re_U32_3857;
        U32 _rc_U32_3857 = 0;
        (void)_rc_U32_3857;
        Bool hoisted__Bool_3868 = U32_lte(_rc_U32_3857, _re_U32_3857);
        (void)hoisted__Bool_3868;
        if (hoisted__Bool_3868) {
            while (1) {
                Bool _wcond_Bool_3858 = U32_lt(_rc_U32_3857, _re_U32_3857);
                (void)_wcond_Bool_3858;
                if (_wcond_Bool_3858) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3857);
                U32_inc(&_rc_U32_3857);
                U32 hoisted__U64_3859 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3859;
                void *hoisted__v_3860 = ptr_add(self->data, hoisted__U64_3859);
                (void)hoisted__v_3860;
                (void)hoisted__v_3860;
                void * cloned = ({ TilClosure *til_closure = (TilClosure *)(self->elem_clone); ((void * (*)(void *, void *))til_closure->call)(til_closure->env, hoisted__v_3860); });
                U32 hoisted__U64_3861 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3861;
                void *hoisted__v_3862 = ptr_add(new_data, hoisted__U64_3861);
                (void)hoisted__v_3862;
                (void)hoisted__v_3862;
                memcpy(hoisted__v_3862, cloned, self->elem_size);
                free(cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_3863 = U32_gt(_rc_U32_3857, _re_U32_3857);
                (void)_wcond_Bool_3863;
                if (_wcond_Bool_3863) {
                } else {
                    break;
                }
                U32 i = U32_clone(&_rc_U32_3857);
                U32_dec(&_rc_U32_3857);
                U32 hoisted__U64_3864 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3864;
                void *hoisted__v_3865 = ptr_add(self->data, hoisted__U64_3864);
                (void)hoisted__v_3865;
                (void)hoisted__v_3865;
                void * cloned = ({ TilClosure *til_closure = (TilClosure *)(self->elem_clone); ((void * (*)(void *, void *))til_closure->call)(til_closure->env, hoisted__v_3865); });
                U32 hoisted__U64_3866 = U32_mul(i, self->elem_size);
                (void)hoisted__U64_3866;
                void *hoisted__v_3867 = ptr_add(new_data, hoisted__U64_3866);
                (void)hoisted__v_3867;
                (void)hoisted__v_3867;
                memcpy(hoisted__v_3867, cloned, self->elem_size);
                free(cloned);
            }
        }
    }
    Array *hoisted__Array_3870 = malloc(sizeof(Array));
    hoisted__Array_3870->data = new_data;
    hoisted__Array_3870->cap = self->cap;
    hoisted__Array_3870->elem_size = self->elem_size;
    hoisted__Array_3870->elem_clone = (void *)self->elem_clone;
    hoisted__Array_3870->elem_delete = (void *)self->elem_delete;
    (void)hoisted__Array_3870;
    return hoisted__Array_3870;
}

U32 Array_size(void) {
    U32 hoisted__U32_3871 = 32;
    (void)hoisted__U32_3871;
    return hoisted__U32_3871;
}

void panic(Str * loc_str, Array * parts) {
    Type *hoisted__Type_4235 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4235;
    U32 hoisted__U32_4236 = 3;
    (void)hoisted__U32_4236;
    Array *_va_Array_147 = Array_new(hoisted__Type_4235, hoisted__U32_4236);
    (void)_va_Array_147;
    Type_delete(hoisted__Type_4235, 1);
    U32 hoisted__U32_4237 = 0;
    (void)hoisted__U32_4237;
    Str *hoisted__Str_4238 = Str_clone(loc_str);
    (void)hoisted__Str_4238;
    Array_set(_va_Array_147, hoisted__U32_4237, hoisted__Str_4238);
    U32 hoisted__U32_4239 = 1;
    (void)hoisted__U32_4239;
    Str hoisted__Str_4240 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4240;
    Array_set(_va_Array_147, hoisted__U32_4239, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4240; _oa; }));
    Array *hoisted__Array_4241 = Array_clone(parts);
    (void)hoisted__Array_4241;
    U32 hoisted__U32_4242 = 2;
    (void)hoisted__U32_4242;
    Str *hoisted__Str_4243 = format(hoisted__Array_4241);
    (void)hoisted__Str_4243;
    Array_set(_va_Array_147, hoisted__U32_4242, hoisted__Str_4243);
    Array_delete(parts, 1);
    println(_va_Array_147);
    I64 hoisted__I64_4244 = 1;
    (void)hoisted__I64_4244;
    exit(hoisted__I64_4244);
}

void UNREACHABLE(Str * loc_str) {
    Type *hoisted__Type_4254 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
    (void)hoisted__Type_4254;
    U32 hoisted__U32_4255 = 1;
    (void)hoisted__U32_4255;
    Array *_va_Array_149 = Array_new(hoisted__Type_4254, hoisted__U32_4255);
    (void)_va_Array_149;
    Type_delete(hoisted__Type_4254, 1);
    U32 hoisted__U32_4256 = 0;
    (void)hoisted__U32_4256;
    Str hoisted__Str_4257 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4257;
    Array_set(_va_Array_149, hoisted__U32_4256, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4257; _oa; }));
    panic(loc_str, _va_Array_149);
}

Bool assert(Str * loc_str, Bool cond) {
    Bool hoisted__Bool_4263 = not(cond);
    (void)hoisted__Bool_4263;
    if (hoisted__Bool_4263) {
        Type *hoisted__Type_4259 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4259;
        U32 hoisted__U32_4260 = 1;
        (void)hoisted__U32_4260;
        Array *_va_Array_150 = Array_new(hoisted__Type_4259, hoisted__U32_4260);
        (void)_va_Array_150;
        Type_delete(hoisted__Type_4259, 1);
        U32 hoisted__U32_4261 = 0;
        (void)hoisted__U32_4261;
        Str hoisted__Str_4262 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4262;
        Array_set(_va_Array_150, hoisted__U32_4261, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4262; _oa; }));
        panic(loc_str, _va_Array_150);
    }
    Bool hoisted__Bool_4264 = 1;
    (void)hoisted__Bool_4264;
    return hoisted__Bool_4264;
}

void assert_eq(Str * loc_str, I64 a, I64 b) {
    Bool hoisted__Bool_4287 = I64_neq(a, b);
    (void)hoisted__Bool_4287;
    if (hoisted__Bool_4287) {
        Type *hoisted__Type_4275 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4275;
        U32 hoisted__U32_4276 = 5;
        (void)hoisted__U32_4276;
        Array *_va_Array_152 = Array_new(hoisted__Type_4275, hoisted__U32_4276);
        (void)_va_Array_152;
        Type_delete(hoisted__Type_4275, 1);
        U32 hoisted__U32_4277 = 0;
        (void)hoisted__U32_4277;
        Str hoisted__Str_4278 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4278;
        Array_set(_va_Array_152, hoisted__U32_4277, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4278; _oa; }));
        U32 hoisted__U32_4279 = 1;
        (void)hoisted__U32_4279;
        Str *hoisted__Str_4280 = I64_to_str(a);
        (void)hoisted__Str_4280;
        Array_set(_va_Array_152, hoisted__U32_4279, hoisted__Str_4280);
        U32 hoisted__U32_4281 = 2;
        (void)hoisted__U32_4281;
        Str hoisted__Str_4282 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4282;
        Array_set(_va_Array_152, hoisted__U32_4281, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4282; _oa; }));
        U32 hoisted__U32_4283 = 3;
        (void)hoisted__U32_4283;
        Str *hoisted__Str_4284 = I64_to_str(b);
        (void)hoisted__Str_4284;
        Array_set(_va_Array_152, hoisted__U32_4283, hoisted__Str_4284);
        U32 hoisted__U32_4285 = 4;
        (void)hoisted__U32_4285;
        Str hoisted__Str_4286 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4286;
        Array_set(_va_Array_152, hoisted__U32_4285, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4286; _oa; }));
        panic(loc_str, _va_Array_152);
    }
}

void assert_eq_str(Str * loc_str, Str * a, Str * b) {
    Bool hoisted__Bool_4301 = Str_eq(a, b);
    (void)hoisted__Bool_4301;
    Bool hoisted__Bool_4302 = not(hoisted__Bool_4301);
    (void)hoisted__Bool_4302;
    if (hoisted__Bool_4302) {
        Type *hoisted__Type_4289 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
        (void)hoisted__Type_4289;
        U32 hoisted__U32_4290 = 5;
        (void)hoisted__U32_4290;
        Array *_va_Array_153 = Array_new(hoisted__Type_4289, hoisted__U32_4290);
        (void)_va_Array_153;
        Type_delete(hoisted__Type_4289, 1);
        U32 hoisted__U32_4291 = 0;
        (void)hoisted__U32_4291;
        Str hoisted__Str_4292 = (Str){.c_str = (void *)"assert_eq_str failed: expected '", .count = 32ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4292;
        Array_set(_va_Array_153, hoisted__U32_4291, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4292; _oa; }));
        U32 hoisted__U32_4293 = 1;
        (void)hoisted__U32_4293;
        Str *hoisted__Str_4294 = Str_clone(a);
        (void)hoisted__Str_4294;
        Array_set(_va_Array_153, hoisted__U32_4293, hoisted__Str_4294);
        U32 hoisted__U32_4295 = 2;
        (void)hoisted__U32_4295;
        Str hoisted__Str_4296 = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4296;
        Array_set(_va_Array_153, hoisted__U32_4295, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4296; _oa; }));
        U32 hoisted__U32_4297 = 3;
        (void)hoisted__U32_4297;
        Str *hoisted__Str_4298 = Str_clone(b);
        (void)hoisted__Str_4298;
        Array_set(_va_Array_153, hoisted__U32_4297, hoisted__Str_4298);
        U32 hoisted__U32_4299 = 4;
        (void)hoisted__U32_4299;
        Str hoisted__Str_4300 = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT};
        (void)hoisted__Str_4300;
        Array_set(_va_Array_153, hoisted__U32_4299, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4300; _oa; }));
        panic(loc_str, _va_Array_153);
    }
}

void println(Array * parts) {
    {
        Array *_fc_Array_4303 = parts;
        (void)_fc_Array_4303;
        (void)_fc_Array_4303;
        U32 _fi_USize_4303 = 0;
        (void)_fi_USize_4303;
        I64 _forin_err_kind_4303 = 0;
        (void)_forin_err_kind_4303;
        OutOfBounds *_forin_OutOfBounds_4303 = malloc(sizeof(OutOfBounds));
        _forin_OutOfBounds_4303->msg = (Str){.c_str=(void*)"", .count=0ULL, .cap=TIL_CAP_LIT};
        (void)_forin_OutOfBounds_4303;
        while (1) {
            U32 hoisted__U32_4311 = Array_len(_fc_Array_4303);
            (void)hoisted__U32_4311;
            Bool _wcond_Bool_4304 = U32_lt(_fi_USize_4303, hoisted__U32_4311);
            (void)_wcond_Bool_4304;
            if (_wcond_Bool_4304) {
            } else {
                break;
            }
            Str *s = Array_get(_fc_Array_4303, &_fi_USize_4303, &_forin_err_kind_4303, _forin_OutOfBounds_4303);
            I64 hoisted__I64_4312 = 0;
            (void)hoisted__I64_4312;
            Bool hoisted__Bool_4313 = I64_eq(_forin_err_kind_4303, hoisted__I64_4312);
            (void)hoisted__Bool_4313;
            Bool hoisted__Bool_4314 = not(hoisted__Bool_4313);
            (void)hoisted__Bool_4314;
            if (hoisted__Bool_4314) {
                Type *hoisted__Type_4306 = Type_Struct(({ Str *_lit = malloc(sizeof(Str)); *_lit = (Str){.c_str = (void *)"Str", .count = 3ULL, .cap = TIL_CAP_LIT}; _lit; }));
                (void)hoisted__Type_4306;
                U32 hoisted__U32_4307 = 1;
                (void)hoisted__U32_4307;
                Array *_va_Array_154 = Array_new(hoisted__Type_4306, hoisted__U32_4307);
                (void)_va_Array_154;
                Type_delete(hoisted__Type_4306, 1);
                U32 hoisted__U32_4308 = 0;
                (void)hoisted__U32_4308;
                Str hoisted__Str_4309 = (Str){.c_str = (void *)"OutOfBounds", .count = 11ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4309;
                Array_set(_va_Array_154, hoisted__U32_4308, ({ Str *_oa = malloc(sizeof(Str)); *_oa = hoisted__Str_4309; _oa; }));
                Str hoisted__Str_4310 = (Str){.c_str = (void *)"./src/core/io.til:15:9", .count = 22ULL, .cap = TIL_CAP_LIT};
                (void)hoisted__Str_4310;
                panic(&hoisted__Str_4310, _va_Array_154);
                Str_delete(&hoisted__Str_4310, (Bool){0});
            }
            U32 hoisted__U32_4315 = 1;
            (void)hoisted__U32_4315;
            U32 hoisted__U32_4316 = U32_add(_fi_USize_4303, hoisted__U32_4315);
            (void)hoisted__U32_4316;
            _fi_USize_4303 = hoisted__U32_4316;
            print_single(s);
        }
        OutOfBounds_delete(_forin_OutOfBounds_4303, 1);
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
    Str hoisted__Str_4622 = (Str){.c_str = (void *)"test/constfold.til:15:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4622;
    I64 hoisted__I64_4623 = 3;
    (void)hoisted__I64_4623;
    assert_eq(&hoisted__Str_4622, result, hoisted__I64_4623);
    Str_delete(&hoisted__Str_4622, (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    Str hoisted__Str_4630 = (Str){.c_str = (void *)"test/constfold.til:21:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4630;
    I64 hoisted__I64_4631 = 15;
    (void)hoisted__I64_4631;
    assert_eq(&hoisted__Str_4630, result, hoisted__I64_4631);
    Str_delete(&hoisted__Str_4630, (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    Str hoisted__Str_4638 = (Str){.c_str = (void *)"test/constfold.til:27:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4638;
    I64 hoisted__I64_4639 = 26;
    (void)hoisted__I64_4639;
    assert_eq(&hoisted__Str_4638, result, hoisted__I64_4639);
    Str_delete(&hoisted__Str_4638, (Bool){0});
}

void test_string_concat(void) {
    Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4642 = (Str){.c_str = (void *)"test/constfold.til:33:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4642;
    Str hoisted__Str_4643 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4643;
    assert_eq_str(&hoisted__Str_4642, &result, &hoisted__Str_4643);
    Str_delete(&hoisted__Str_4642, (Bool){0});
    Str_delete(&hoisted__Str_4643, (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_4974 = (Str){.c_str = (void *)"test/constfold.til:86:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4974;
    assert_eq_str(&hoisted__Str_4974, &lola_rec, &lola_it);
    Str_delete(&hoisted__Str_4974, (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    Str hoisted__Str_4975 = (Str){.c_str = (void *)"test/constfold.til:87:19", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4975;
    assert_eq_str(&hoisted__Str_4975, &lalo_rec, &lalo_it);
    Str_delete(&hoisted__Str_4975, (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    Str hoisted__Str_4977 = (Str){.c_str = (void *)"test/constfold.til:94:15", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4977;
    I64 hoisted__I64_4978 = 8;
    (void)hoisted__I64_4978;
    assert_eq(&hoisted__Str_4977, result, hoisted__I64_4978);
    Str_delete(&hoisted__Str_4977, (Bool){0});
}

void test_loc_folded(void) {
    Str hoisted__Str_4981 = (Str){.c_str = (void *)"test/constfold.til:99:12", .count = 24ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4981;
    Bool hoisted__Bool_4982 = 1;
    (void)hoisted__Bool_4982;
    assert(&hoisted__Str_4981, hoisted__Bool_4982);
    Str_delete(&hoisted__Str_4981, (Bool){0});
    Str hoisted__Str_4985 = (Str){.c_str = (void *)"test/constfold.til:100:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4985;
    Bool hoisted__Bool_4986 = 1;
    (void)hoisted__Bool_4986;
    assert(&hoisted__Str_4985, hoisted__Bool_4986);
    Str_delete(&hoisted__Str_4985, (Bool){0});
}

void test_fold_f32(void) {
    Str hoisted__Str_4991 = (Str){.c_str = (void *)"test/constfold.til:111:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4991;
    Str hoisted__Str_4992 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4992;
    Str hoisted__Str_4993 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4993;
    assert_eq_str(&hoisted__Str_4991, &hoisted__Str_4992, &hoisted__Str_4993);
    Str_delete(&hoisted__Str_4991, (Bool){0});
    Str_delete(&hoisted__Str_4992, (Bool){0});
    Str_delete(&hoisted__Str_4993, (Bool){0});
    Str hoisted__Str_4996 = (Str){.c_str = (void *)"test/constfold.til:113:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4996;
    Str hoisted__Str_4997 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4997;
    Str hoisted__Str_4998 = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_4998;
    assert_eq_str(&hoisted__Str_4996, &hoisted__Str_4997, &hoisted__Str_4998);
    Str_delete(&hoisted__Str_4996, (Bool){0});
    Str_delete(&hoisted__Str_4997, (Bool){0});
    Str_delete(&hoisted__Str_4998, (Bool){0});
}

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_5003 = (CfVec2){.x = self->x, .y = self->y};
    (void)hoisted__CfVec2_5003;
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_5003;
    return _r; }
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_5004 = 0;
    (void)hoisted__U32_5004;
    U64 hoisted__U64_5005 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_5004); });
    (void)hoisted__U64_5005;
    return hoisted__U64_5005;
}

U32 CfVec2_size(void) {
    U32 hoisted__U32_5006 = 16;
    (void)hoisted__U32_5006;
    return hoisted__U32_5006;
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    Str hoisted__Str_5007 = (Str){.c_str = (void *)"test/constfold.til:135:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5007;
    I64 hoisted__I64_5008 = 42;
    (void)hoisted__I64_5008;
    assert_eq(&hoisted__Str_5007, v.x, hoisted__I64_5008);
    Str_delete(&hoisted__Str_5007, (Bool){0});
    Str hoisted__Str_5009 = (Str){.c_str = (void *)"test/constfold.til:136:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5009;
    I64 hoisted__I64_5010 = 99;
    (void)hoisted__I64_5010;
    assert_eq(&hoisted__Str_5009, v.y, hoisted__I64_5010);
    Str_delete(&hoisted__Str_5009, (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    Str hoisted__Str_5013 = (Str){.c_str = (void *)"test/constfold.til:142:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5013;
    I64 hoisted__I64_5014 = 10;
    (void)hoisted__I64_5014;
    assert_eq(&hoisted__Str_5013, p.x, hoisted__I64_5014);
    Str_delete(&hoisted__Str_5013, (Bool){0});
    Str hoisted__Str_5015 = (Str){.c_str = (void *)"test/constfold.til:143:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5015;
    I64 hoisted__I64_5016 = 20;
    (void)hoisted__I64_5016;
    assert_eq(&hoisted__Str_5015, p.y, hoisted__I64_5016);
    Str_delete(&hoisted__Str_5015, (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_5022 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    (void)hoisted__CfRect_5022;
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_5022;
    return _r; }
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_5023 = 0;
    (void)hoisted__U32_5023;
    U64 hoisted__U64_5024 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_5023); });
    (void)hoisted__U64_5024;
    return hoisted__U64_5024;
}

U32 CfRect_size(void) {
    U32 hoisted__U32_5025 = 32;
    (void)hoisted__U32_5025;
    return hoisted__U32_5025;
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    Str hoisted__Str_5026 = (Str){.c_str = (void *)"test/constfold.til:159:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5026;
    I64 hoisted__I64_5027 = 5;
    (void)hoisted__I64_5027;
    assert_eq(&hoisted__Str_5026, r.top_left.x, hoisted__I64_5027);
    Str_delete(&hoisted__Str_5026, (Bool){0});
    Str hoisted__Str_5028 = (Str){.c_str = (void *)"test/constfold.til:160:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5028;
    I64 hoisted__I64_5029 = 10;
    (void)hoisted__I64_5029;
    assert_eq(&hoisted__Str_5028, r.top_left.y, hoisted__I64_5029);
    Str_delete(&hoisted__Str_5028, (Bool){0});
    Str hoisted__Str_5030 = (Str){.c_str = (void *)"test/constfold.til:161:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5030;
    I64 hoisted__I64_5031 = 100;
    (void)hoisted__I64_5031;
    assert_eq(&hoisted__Str_5030, r.bottom_right.x, hoisted__I64_5031);
    Str_delete(&hoisted__Str_5030, (Bool){0});
    Str hoisted__Str_5032 = (Str){.c_str = (void *)"test/constfold.til:162:15", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5032;
    I64 hoisted__I64_5033 = 200;
    (void)hoisted__I64_5033;
    assert_eq(&hoisted__Str_5032, r.bottom_right.y, hoisted__I64_5033);
    Str_delete(&hoisted__Str_5032, (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_5035 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    (void)hoisted__CfVec3f_5035;
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_5035;
    return _r; }
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_5036 = 0;
    (void)hoisted__U32_5036;
    U64 hoisted__U64_5037 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_5036); });
    (void)hoisted__U64_5037;
    return hoisted__U64_5037;
}

U32 CfVec3f_size(void) {
    U32 hoisted__U32_5038 = 12;
    (void)hoisted__U32_5038;
    return hoisted__U32_5038;
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str hoisted__Str_5042 = (Str){.c_str = (void *)"test/constfold.til:185:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5042;
    Str *hoisted__Str_5043 = F32_to_str(v.x);
    (void)hoisted__Str_5043;
    Str hoisted__Str_5044 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5044;
    assert_eq_str(&hoisted__Str_5042, hoisted__Str_5043, &hoisted__Str_5044);
    Str_delete(&hoisted__Str_5042, (Bool){0});
    Str_delete(hoisted__Str_5043, 1);
    Str_delete(&hoisted__Str_5044, (Bool){0});
    Str hoisted__Str_5045 = (Str){.c_str = (void *)"test/constfold.til:186:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5045;
    Str *hoisted__Str_5046 = F32_to_str(v.y);
    (void)hoisted__Str_5046;
    Str hoisted__Str_5047 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5047;
    assert_eq_str(&hoisted__Str_5045, hoisted__Str_5046, &hoisted__Str_5047);
    Str_delete(&hoisted__Str_5045, (Bool){0});
    Str_delete(hoisted__Str_5046, 1);
    Str_delete(&hoisted__Str_5047, (Bool){0});
    Str hoisted__Str_5048 = (Str){.c_str = (void *)"test/constfold.til:187:19", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5048;
    Str *hoisted__Str_5049 = F32_to_str(v.z);
    (void)hoisted__Str_5049;
    Str hoisted__Str_5050 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5050;
    assert_eq_str(&hoisted__Str_5048, hoisted__Str_5049, &hoisted__Str_5050);
    Str_delete(&hoisted__Str_5048, (Bool){0});
    Str_delete(hoisted__Str_5049, 1);
    Str_delete(&hoisted__Str_5050, (Bool){0});
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
    Bool hoisted__Bool_5055 = is(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5055;
    if (hoisted__Bool_5055) {
        Bool hoisted__Bool_5052 = is(other, &(Color){.tag = Color_TAG_Red});
        (void)hoisted__Bool_5052;
        { Bool _ret_val = hoisted__Bool_5052;
                return _ret_val; }
    }
    Bool hoisted__Bool_5056 = is(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5056;
    if (hoisted__Bool_5056) {
        Bool hoisted__Bool_5053 = is(other, &(Color){.tag = Color_TAG_Green});
        (void)hoisted__Bool_5053;
        { Bool _ret_val = hoisted__Bool_5053;
                return _ret_val; }
    }
    Bool hoisted__Bool_5057 = is(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_5057;
    if (hoisted__Bool_5057) {
        Bool hoisted__Bool_5054 = is(other, &(Color){.tag = Color_TAG_Blue});
        (void)hoisted__Bool_5054;
        { Bool _ret_val = hoisted__Bool_5054;
                return _ret_val; }
    }
    Bool hoisted__Bool_5058 = 0;
    (void)hoisted__Bool_5058;
    return hoisted__Bool_5058;
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_5066 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5066;
    if (hoisted__Bool_5066) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
                return _r; }
    }
    Bool hoisted__Bool_5067 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5067;
    if (hoisted__Bool_5067) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
                return _r; }
    }
    Bool hoisted__Bool_5068 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    (void)hoisted__Bool_5068;
    if (hoisted__Bool_5068) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
                return _r; }
    }
    Str hoisted__Str_5069 = (Str){.c_str = (void *)"Color.clone:192:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5069;
    UNREACHABLE(&hoisted__Str_5069);
    Str_delete(&hoisted__Str_5069, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
}

U32 Color_size(void) {
    U32 hoisted__U32_5070 = 4;
    (void)hoisted__U32_5070;
    return hoisted__U32_5070;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Str hoisted__Str_5071 = (Str){.c_str = (void *)"test/constfold.til:197:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5071;
    Bool hoisted__Bool_5072 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5072;
    assert(&hoisted__Str_5071, hoisted__Bool_5072);
    Str_delete(&hoisted__Str_5071, (Bool){0});
    Bool hoisted__Bool_5073 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5073;
    Str hoisted__Str_5074 = (Str){.c_str = (void *)"test/constfold.til:198:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5074;
    Bool hoisted__Bool_5075 = not(hoisted__Bool_5073);
    (void)hoisted__Bool_5075;
    assert(&hoisted__Str_5074, hoisted__Bool_5075);
    Str_delete(&hoisted__Str_5074, (Bool){0});
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
    Bool hoisted__Bool_5076 = is(self, other);
    (void)hoisted__Bool_5076;
    return hoisted__Bool_5076;
}

void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_5094 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5094;
    if (hoisted__Bool_5094) {
        I64 *hoisted__I64_5090 = get_payload(self);
        (void)hoisted__I64_5090;
        (void)hoisted__I64_5090;
        Bool hoisted__Bool_5091 = 0;
        (void)hoisted__Bool_5091;
        I64_delete(hoisted__I64_5090, hoisted__Bool_5091);
    }
    Bool hoisted__Bool_5095 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5095;
    if (hoisted__Bool_5095) {
        Str *hoisted__Str_5092 = get_payload(self);
        (void)hoisted__Str_5092;
        (void)hoisted__Str_5092;
        Bool hoisted__Bool_5093 = 0;
        (void)hoisted__Bool_5093;
        Str_delete(hoisted__Str_5092, hoisted__Bool_5093);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_5124 = is(self, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5124;
    if (hoisted__Bool_5124) {
        I64 *_clone_payload_Num_0 = get_payload(self);
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_5121 = Token_Num(_clone_payload_Num_0);
        (void)hoisted__Token_5121;
        { Token * _ret_val = hoisted__Token_5121;
                return _ret_val; }
    }
    Bool hoisted__Bool_5125 = is(self, &(Token){.tag = Token_TAG_Name});
    (void)hoisted__Bool_5125;
    if (hoisted__Bool_5125) {
        Str *_clone_payload_Name_1 = get_payload(self);
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_5122 = Str_clone(_clone_payload_Name_1);
        (void)hoisted__Str_5122;
        Token *hoisted__Token_5123 = Token_Name(hoisted__Str_5122);
        (void)hoisted__Token_5123;
        { Token * _ret_val = hoisted__Token_5123;
                return _ret_val; }
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
}

U32 Token_size(void) {
    U32 hoisted__U32_5126 = 24;
    (void)hoisted__U32_5126;
    return hoisted__U32_5126;
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Str hoisted__Str_5128 = (Str){.c_str = (void *)"test/constfold.til:206:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5128;
    Bool hoisted__Bool_5129 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5129;
    assert(&hoisted__Str_5128, hoisted__Bool_5129);
    Str_delete(&hoisted__Str_5128, (Bool){0});
    Bool hoisted__Bool_5130 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5130;
    Str hoisted__Str_5131 = (Str){.c_str = (void *)"test/constfold.til:207:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5131;
    Bool hoisted__Bool_5132 = not(hoisted__Bool_5130);
    (void)hoisted__Bool_5132;
    assert(&hoisted__Str_5131, hoisted__Bool_5132);
    Str_delete(&hoisted__Str_5131, (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Str hoisted__Str_5133 = (Str){.c_str = (void *)"test/constfold.til:216:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5133;
    Bool hoisted__Bool_5134 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    (void)hoisted__Bool_5134;
    assert(&hoisted__Str_5133, hoisted__Bool_5134);
    Str_delete(&hoisted__Str_5133, (Bool){0});
    Bool hoisted__Bool_5135 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    (void)hoisted__Bool_5135;
    Str hoisted__Str_5136 = (Str){.c_str = (void *)"test/constfold.til:217:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5136;
    Bool hoisted__Bool_5137 = not(hoisted__Bool_5135);
    (void)hoisted__Bool_5137;
    assert(&hoisted__Str_5136, hoisted__Bool_5137);
    Str_delete(&hoisted__Str_5136, (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Str hoisted__Str_5140 = (Str){.c_str = (void *)"test/constfold.til:228:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5140;
    Bool hoisted__Bool_5141 = Token_is(t, &(Token){.tag = Token_TAG_Num});
    (void)hoisted__Bool_5141;
    assert(&hoisted__Str_5140, hoisted__Bool_5141);
    Str_delete(&hoisted__Str_5140, (Bool){0});
    Bool hoisted__Bool_5142 = Token_is(t, &(Token){.tag = Token_TAG_Eof});
    (void)hoisted__Bool_5142;
    Str hoisted__Str_5143 = (Str){.c_str = (void *)"test/constfold.til:229:12", .count = 25ULL, .cap = TIL_CAP_LIT};
    (void)hoisted__Str_5143;
    Bool hoisted__Bool_5144 = not(hoisted__Bool_5142);
    (void)hoisted__Bool_5144;
    assert(&hoisted__Str_5143, hoisted__Bool_5144);
    Str_delete(&hoisted__Str_5143, (Bool){0});
    Token_delete(t, 1);
}

void *F32_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)F32_to_str(*(F32 *)_a0);
}
static __attribute__((unused)) TilClosure F32_to_str_dyn__til_closure = { (void *)F32_to_str_dyn, NULL, NULL };
I64 F32_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return F32_cmp(*(F32 *)_a0, *(F32 *)_a1);
}
static __attribute__((unused)) TilClosure F32_cmp_dyn__til_closure = { (void *)F32_cmp_dyn, NULL, NULL };
void *F32_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    F32 *_r = malloc(sizeof(F32)); *_r = F32_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure F32_clone_dyn__til_closure = { (void *)F32_clone_dyn, NULL, NULL };
void F32_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    F32_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure F32_delete_dyn__til_closure = { (void *)F32_delete_dyn, NULL, NULL };
U32 F32_size_dyn(void *til_env) {
    (void)til_env;
    return F32_size();
}
static __attribute__((unused)) TilClosure F32_size_dyn__til_closure = { (void *)F32_size_dyn, NULL, NULL };
U64 F32_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return F32_hash(*(F32 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure F32_hash_dyn__til_closure = { (void *)F32_hash_dyn, NULL, NULL };
U64 U64_add_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U64_add(*(U64 *)_a0, *(U64 *)_a1);
}
static __attribute__((unused)) TilClosure U64_add_dyn__til_closure = { (void *)U64_add_dyn, NULL, NULL };
U64 U64_sub_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U64_sub(*(U64 *)_a0, *(U64 *)_a1);
}
static __attribute__((unused)) TilClosure U64_sub_dyn__til_closure = { (void *)U64_sub_dyn, NULL, NULL };
I64 U64_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U64_cmp(*(U64 *)_a0, *(U64 *)_a1);
}
static __attribute__((unused)) TilClosure U64_cmp_dyn__til_closure = { (void *)U64_cmp_dyn, NULL, NULL };
void *U64_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U64 *_r = malloc(sizeof(U64)); *_r = U64_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure U64_clone_dyn__til_closure = { (void *)U64_clone_dyn, NULL, NULL };
void U64_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    U64_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure U64_delete_dyn__til_closure = { (void *)U64_delete_dyn, NULL, NULL };
U32 U64_size_dyn(void *til_env) {
    (void)til_env;
    return U64_size();
}
static __attribute__((unused)) TilClosure U64_size_dyn__til_closure = { (void *)U64_size_dyn, NULL, NULL };
U64 U64_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U64_hash(*(U64 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure U64_hash_dyn__til_closure = { (void *)U64_hash_dyn, NULL, NULL };
I64 U32_to_i64_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return U32_to_i64(*(U32 *)_a0);
}
static __attribute__((unused)) TilClosure U32_to_i64_dyn__til_closure = { (void *)U32_to_i64_dyn, NULL, NULL };
void *U32_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)U32_to_str(*(U32 *)_a0);
}
static __attribute__((unused)) TilClosure U32_to_str_dyn__til_closure = { (void *)U32_to_str_dyn, NULL, NULL };
U32 U32_add_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_add(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_add_dyn__til_closure = { (void *)U32_add_dyn, NULL, NULL };
U32 U32_sub_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_sub(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_sub_dyn__til_closure = { (void *)U32_sub_dyn, NULL, NULL };
U32 U32_mul_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_mul(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_mul_dyn__til_closure = { (void *)U32_mul_dyn, NULL, NULL };
void U32_inc_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U32_inc(_a0);
}
static __attribute__((unused)) TilClosure U32_inc_dyn__til_closure = { (void *)U32_inc_dyn, NULL, NULL };
void U32_dec_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U32_dec(_a0);
}
static __attribute__((unused)) TilClosure U32_dec_dyn__til_closure = { (void *)U32_dec_dyn, NULL, NULL };
Bool U32_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_eq(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_eq_dyn__til_closure = { (void *)U32_eq_dyn, NULL, NULL };
I64 U32_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_cmp(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_cmp_dyn__til_closure = { (void *)U32_cmp_dyn, NULL, NULL };
void *U32_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U32 *_r = malloc(sizeof(U32)); *_r = U32_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure U32_clone_dyn__til_closure = { (void *)U32_clone_dyn, NULL, NULL };
void U32_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    U32_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure U32_delete_dyn__til_closure = { (void *)U32_delete_dyn, NULL, NULL };
U32 U32_size_dyn(void *til_env) {
    (void)til_env;
    return U32_size();
}
static __attribute__((unused)) TilClosure U32_size_dyn__til_closure = { (void *)U32_size_dyn, NULL, NULL };
U64 U32_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_hash(*(U32 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure U32_hash_dyn__til_closure = { (void *)U32_hash_dyn, NULL, NULL };
Bool U32_lt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_lt(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_lt_dyn__til_closure = { (void *)U32_lt_dyn, NULL, NULL };
Bool U32_gt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_gt(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_gt_dyn__til_closure = { (void *)U32_gt_dyn, NULL, NULL };
Bool U32_neq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_neq(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_neq_dyn__til_closure = { (void *)U32_neq_dyn, NULL, NULL };
Bool U32_lte_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_lte(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_lte_dyn__til_closure = { (void *)U32_lte_dyn, NULL, NULL };
Bool U32_gte_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U32_gte(*(U32 *)_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure U32_gte_dyn__til_closure = { (void *)U32_gte_dyn, NULL, NULL };
I64 I32_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I32_cmp(*(I32 *)_a0, *(I32 *)_a1);
}
static __attribute__((unused)) TilClosure I32_cmp_dyn__til_closure = { (void *)I32_cmp_dyn, NULL, NULL };
void *I32_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    I32 *_r = malloc(sizeof(I32)); *_r = I32_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure I32_clone_dyn__til_closure = { (void *)I32_clone_dyn, NULL, NULL };
void I32_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    I32_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure I32_delete_dyn__til_closure = { (void *)I32_delete_dyn, NULL, NULL };
U32 I32_size_dyn(void *til_env) {
    (void)til_env;
    return I32_size();
}
static __attribute__((unused)) TilClosure I32_size_dyn__til_closure = { (void *)I32_size_dyn, NULL, NULL };
U64 I32_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I32_hash(*(I32 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure I32_hash_dyn__til_closure = { (void *)I32_hash_dyn, NULL, NULL };
I64 I8_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I8_cmp(*(I8 *)_a0, *(I8 *)_a1);
}
static __attribute__((unused)) TilClosure I8_cmp_dyn__til_closure = { (void *)I8_cmp_dyn, NULL, NULL };
void *I8_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    I8 *_r = malloc(sizeof(I8)); *_r = I8_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure I8_clone_dyn__til_closure = { (void *)I8_clone_dyn, NULL, NULL };
void I8_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    I8_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure I8_delete_dyn__til_closure = { (void *)I8_delete_dyn, NULL, NULL };
U32 I8_size_dyn(void *til_env) {
    (void)til_env;
    return I8_size();
}
static __attribute__((unused)) TilClosure I8_size_dyn__til_closure = { (void *)I8_size_dyn, NULL, NULL };
U64 I8_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I8_hash(*(I8 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure I8_hash_dyn__til_closure = { (void *)I8_hash_dyn, NULL, NULL };
I64 U8_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U8_cmp(*(U8 *)_a0, *(U8 *)_a1);
}
static __attribute__((unused)) TilClosure U8_cmp_dyn__til_closure = { (void *)U8_cmp_dyn, NULL, NULL };
void *U8_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    U8 *_r = malloc(sizeof(U8)); *_r = U8_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure U8_clone_dyn__til_closure = { (void *)U8_clone_dyn, NULL, NULL };
void U8_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    U8_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure U8_delete_dyn__til_closure = { (void *)U8_delete_dyn, NULL, NULL };
U32 U8_size_dyn(void *til_env) {
    (void)til_env;
    return U8_size();
}
static __attribute__((unused)) TilClosure U8_size_dyn__til_closure = { (void *)U8_size_dyn, NULL, NULL };
U64 U8_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return U8_hash(*(U8 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure U8_hash_dyn__til_closure = { (void *)U8_hash_dyn, NULL, NULL };
U32 Str_len_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return Str_len(_a0);
}
static __attribute__((unused)) TilClosure Str_len_dyn__til_closure = { (void *)Str_len_dyn, NULL, NULL };
void *Str_get_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return (void *)Str_get(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_get_dyn__til_closure = { (void *)Str_get_dyn, NULL, NULL };
I64 Str_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_cmp(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_cmp_dyn__til_closure = { (void *)Str_cmp_dyn, NULL, NULL };
void *Str_with_capacity_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Str_with_capacity(*(U32 *)_a0);
}
static __attribute__((unused)) TilClosure Str_with_capacity_dyn__til_closure = { (void *)Str_with_capacity_dyn, NULL, NULL };
void Str_push_str_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    Str_push_str(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_push_str_dyn__til_closure = { (void *)Str_push_str_dyn, NULL, NULL };
void *Str_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Str_clone(_a0);
}
static __attribute__((unused)) TilClosure Str_clone_dyn__til_closure = { (void *)Str_clone_dyn, NULL, NULL };
void Str_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Str_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_delete_dyn__til_closure = { (void *)Str_delete_dyn, NULL, NULL };
Bool Str_is_empty_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return Str_is_empty(_a0);
}
static __attribute__((unused)) TilClosure Str_is_empty_dyn__til_closure = { (void *)Str_is_empty_dyn, NULL, NULL };
U64 Str_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_hash_dyn__til_closure = { (void *)Str_hash_dyn, NULL, NULL };
U32 Str_size_dyn(void *til_env) {
    (void)til_env;
    return Str_size();
}
static __attribute__((unused)) TilClosure Str_size_dyn__til_closure = { (void *)Str_size_dyn, NULL, NULL };
Bool Str_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Str_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure Str_eq_dyn__til_closure = { (void *)Str_eq_dyn, NULL, NULL };
void *OutOfBounds_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)OutOfBounds_clone(_a0);
}
static __attribute__((unused)) TilClosure OutOfBounds_clone_dyn__til_closure = { (void *)OutOfBounds_clone_dyn, NULL, NULL };
void OutOfBounds_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    OutOfBounds_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure OutOfBounds_delete_dyn__til_closure = { (void *)OutOfBounds_delete_dyn, NULL, NULL };
U64 OutOfBounds_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return OutOfBounds_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure OutOfBounds_hash_dyn__til_closure = { (void *)OutOfBounds_hash_dyn, NULL, NULL };
U32 OutOfBounds_size_dyn(void *til_env) {
    (void)til_env;
    return OutOfBounds_size();
}
static __attribute__((unused)) TilClosure OutOfBounds_size_dyn__til_closure = { (void *)OutOfBounds_size_dyn, NULL, NULL };
U32 Dynamic_size_dyn(void *til_env) {
    (void)til_env;
    return Dynamic_size();
}
static __attribute__((unused)) TilClosure Dynamic_size_dyn__til_closure = { (void *)Dynamic_size_dyn, NULL, NULL };
void *I64_to_str_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)I64_to_str(*(I64 *)_a0);
}
static __attribute__((unused)) TilClosure I64_to_str_dyn__til_closure = { (void *)I64_to_str_dyn, NULL, NULL };
U8 I64_to_u8_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return I64_to_u8(*(I64 *)_a0);
}
static __attribute__((unused)) TilClosure I64_to_u8_dyn__til_closure = { (void *)I64_to_u8_dyn, NULL, NULL };
I64 I64_add_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_add(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_add_dyn__til_closure = { (void *)I64_add_dyn, NULL, NULL };
I64 I64_sub_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_sub(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_sub_dyn__til_closure = { (void *)I64_sub_dyn, NULL, NULL };
I64 I64_div_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_div(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_div_dyn__til_closure = { (void *)I64_div_dyn, NULL, NULL };
I64 I64_mod_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_mod(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_mod_dyn__til_closure = { (void *)I64_mod_dyn, NULL, NULL };
Bool I64_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_eq(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_eq_dyn__til_closure = { (void *)I64_eq_dyn, NULL, NULL };
I64 I64_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_cmp(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_cmp_dyn__til_closure = { (void *)I64_cmp_dyn, NULL, NULL };
void *I64_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    I64 *_r = malloc(sizeof(I64)); *_r = I64_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure I64_clone_dyn__til_closure = { (void *)I64_clone_dyn, NULL, NULL };
void I64_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    I64_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure I64_delete_dyn__til_closure = { (void *)I64_delete_dyn, NULL, NULL };
U32 I64_size_dyn(void *til_env) {
    (void)til_env;
    return I64_size();
}
static __attribute__((unused)) TilClosure I64_size_dyn__til_closure = { (void *)I64_size_dyn, NULL, NULL };
U64 I64_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_hash(*(I64 *)_a0, _a1);
}
static __attribute__((unused)) TilClosure I64_hash_dyn__til_closure = { (void *)I64_hash_dyn, NULL, NULL };
Bool I64_lt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_lt(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_lt_dyn__til_closure = { (void *)I64_lt_dyn, NULL, NULL };
Bool I64_gt_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_gt(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_gt_dyn__til_closure = { (void *)I64_gt_dyn, NULL, NULL };
Bool I64_neq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return I64_neq(*(I64 *)_a0, *(I64 *)_a1);
}
static __attribute__((unused)) TilClosure I64_neq_dyn__til_closure = { (void *)I64_neq_dyn, NULL, NULL };
Bool Bool_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Bool_eq(*(Bool *)_a0, *(Bool *)_a1);
}
static __attribute__((unused)) TilClosure Bool_eq_dyn__til_closure = { (void *)Bool_eq_dyn, NULL, NULL };
I64 Bool_cmp_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Bool_cmp(*(Bool *)_a0, *(Bool *)_a1);
}
static __attribute__((unused)) TilClosure Bool_cmp_dyn__til_closure = { (void *)Bool_cmp_dyn, NULL, NULL };
void *Bool_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    Bool *_r = malloc(sizeof(Bool)); *_r = Bool_clone(_a0); return _r;
}
static __attribute__((unused)) TilClosure Bool_clone_dyn__til_closure = { (void *)Bool_clone_dyn, NULL, NULL };
void Bool_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Bool_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Bool_delete_dyn__til_closure = { (void *)Bool_delete_dyn, NULL, NULL };
U32 Bool_size_dyn(void *til_env) {
    (void)til_env;
    return Bool_size();
}
static __attribute__((unused)) TilClosure Bool_size_dyn__til_closure = { (void *)Bool_size_dyn, NULL, NULL };
U64 Bool_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Bool_hash(*(Bool *)_a0, _a1);
}
static __attribute__((unused)) TilClosure Bool_hash_dyn__til_closure = { (void *)Bool_hash_dyn, NULL, NULL };
Bool Primitive_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Primitive_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure Primitive_eq_dyn__til_closure = { (void *)Primitive_eq_dyn, NULL, NULL };
void Primitive_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Primitive_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Primitive_delete_dyn__til_closure = { (void *)Primitive_delete_dyn, NULL, NULL };
void *Primitive_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Primitive_clone(_a0);
}
static __attribute__((unused)) TilClosure Primitive_clone_dyn__til_closure = { (void *)Primitive_clone_dyn, NULL, NULL };
U32 Primitive_size_dyn(void *til_env) {
    (void)til_env;
    return Primitive_size();
}
static __attribute__((unused)) TilClosure Primitive_size_dyn__til_closure = { (void *)Primitive_size_dyn, NULL, NULL };
void *Type_Unknown_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_Unknown();
}
static __attribute__((unused)) TilClosure Type_Unknown_dyn__til_closure = { (void *)Type_Unknown_dyn, NULL, NULL };
void *Type_None_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_None();
}
static __attribute__((unused)) TilClosure Type_None_dyn__til_closure = { (void *)Type_None_dyn, NULL, NULL };
void *Type_Struct_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_Struct(_a0);
}
static __attribute__((unused)) TilClosure Type_Struct_dyn__til_closure = { (void *)Type_Struct_dyn, NULL, NULL };
void *Type_StructDef_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_StructDef();
}
static __attribute__((unused)) TilClosure Type_StructDef_dyn__til_closure = { (void *)Type_StructDef_dyn, NULL, NULL };
void *Type_Enum_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_Enum(_a0);
}
static __attribute__((unused)) TilClosure Type_Enum_dyn__til_closure = { (void *)Type_Enum_dyn, NULL, NULL };
void *Type_EnumDef_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_EnumDef();
}
static __attribute__((unused)) TilClosure Type_EnumDef_dyn__til_closure = { (void *)Type_EnumDef_dyn, NULL, NULL };
void *Type_FuncDef_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_FuncDef();
}
static __attribute__((unused)) TilClosure Type_FuncDef_dyn__til_closure = { (void *)Type_FuncDef_dyn, NULL, NULL };
void *Type_FuncPtr_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_FuncPtr();
}
static __attribute__((unused)) TilClosure Type_FuncPtr_dyn__til_closure = { (void *)Type_FuncPtr_dyn, NULL, NULL };
void *Type_Dynamic_dyn(void *til_env) {
    (void)til_env;
    return (void *)Type_Dynamic();
}
static __attribute__((unused)) TilClosure Type_Dynamic_dyn__til_closure = { (void *)Type_Dynamic_dyn, NULL, NULL };
void *Type_Custom_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_Custom(_a0);
}
static __attribute__((unused)) TilClosure Type_Custom_dyn__til_closure = { (void *)Type_Custom_dyn, NULL, NULL };
void *Type_Primitive_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_Primitive(_a0);
}
static __attribute__((unused)) TilClosure Type_Primitive_dyn__til_closure = { (void *)Type_Primitive_dyn, NULL, NULL };
void *Type_FuncPtrSig_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_FuncPtrSig(_a0);
}
static __attribute__((unused)) TilClosure Type_FuncPtrSig_dyn__til_closure = { (void *)Type_FuncPtrSig_dyn, NULL, NULL };
void Type_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Type_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Type_delete_dyn__til_closure = { (void *)Type_delete_dyn, NULL, NULL };
void *Type_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Type_clone(_a0);
}
static __attribute__((unused)) TilClosure Type_clone_dyn__til_closure = { (void *)Type_clone_dyn, NULL, NULL };
U32 Type_size_dyn(void *til_env) {
    (void)til_env;
    return Type_size();
}
static __attribute__((unused)) TilClosure Type_size_dyn__til_closure = { (void *)Type_size_dyn, NULL, NULL };
void *Array_new_type_name_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return (void *)Array_new_type_name(_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure Array_new_type_name_dyn__til_closure = { (void *)Array_new_type_name_dyn, NULL, NULL };
void *Array_new_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return (void *)Array_new(_a0, *(U32 *)_a1);
}
static __attribute__((unused)) TilClosure Array_new_dyn__til_closure = { (void *)Array_new_dyn, NULL, NULL };
U32 Array_len_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return Array_len(_a0);
}
static __attribute__((unused)) TilClosure Array_len_dyn__til_closure = { (void *)Array_len_dyn, NULL, NULL };
void *Array_get_dyn(void *til_env, void *_a0, void *_a1, void *_a2, void *_a3) {
    (void)til_env;
    return (void *)Array_get(_a0, _a1, _a2, _a3);
}
static __attribute__((unused)) TilClosure Array_get_dyn__til_closure = { (void *)Array_get_dyn, NULL, NULL };
void Array_set_dyn(void *til_env, void *_a0, void *_a1, void *_a2) {
    (void)til_env;
    Array_set(_a0, *(U32 *)_a1, _a2);
}
static __attribute__((unused)) TilClosure Array_set_dyn__til_closure = { (void *)Array_set_dyn, NULL, NULL };
void Array_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Array_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Array_delete_dyn__til_closure = { (void *)Array_delete_dyn, NULL, NULL };
void *Array_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Array_clone(_a0);
}
static __attribute__((unused)) TilClosure Array_clone_dyn__til_closure = { (void *)Array_clone_dyn, NULL, NULL };
U32 Array_size_dyn(void *til_env) {
    (void)til_env;
    return Array_size();
}
static __attribute__((unused)) TilClosure Array_size_dyn__til_closure = { (void *)Array_size_dyn, NULL, NULL };
void *CfVec2_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)CfVec2_clone(_a0);
}
static __attribute__((unused)) TilClosure CfVec2_clone_dyn__til_closure = { (void *)CfVec2_clone_dyn, NULL, NULL };
void CfVec2_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    CfVec2_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfVec2_delete_dyn__til_closure = { (void *)CfVec2_delete_dyn, NULL, NULL };
U64 CfVec2_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return CfVec2_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfVec2_hash_dyn__til_closure = { (void *)CfVec2_hash_dyn, NULL, NULL };
U32 CfVec2_size_dyn(void *til_env) {
    (void)til_env;
    return CfVec2_size();
}
static __attribute__((unused)) TilClosure CfVec2_size_dyn__til_closure = { (void *)CfVec2_size_dyn, NULL, NULL };
void *CfRect_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)CfRect_clone(_a0);
}
static __attribute__((unused)) TilClosure CfRect_clone_dyn__til_closure = { (void *)CfRect_clone_dyn, NULL, NULL };
void CfRect_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    CfRect_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfRect_delete_dyn__til_closure = { (void *)CfRect_delete_dyn, NULL, NULL };
U64 CfRect_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return CfRect_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfRect_hash_dyn__til_closure = { (void *)CfRect_hash_dyn, NULL, NULL };
U32 CfRect_size_dyn(void *til_env) {
    (void)til_env;
    return CfRect_size();
}
static __attribute__((unused)) TilClosure CfRect_size_dyn__til_closure = { (void *)CfRect_size_dyn, NULL, NULL };
void *CfVec3f_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)CfVec3f_clone(_a0);
}
static __attribute__((unused)) TilClosure CfVec3f_clone_dyn__til_closure = { (void *)CfVec3f_clone_dyn, NULL, NULL };
void CfVec3f_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    CfVec3f_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfVec3f_delete_dyn__til_closure = { (void *)CfVec3f_delete_dyn, NULL, NULL };
U64 CfVec3f_hash_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return CfVec3f_hash(_a0, _a1);
}
static __attribute__((unused)) TilClosure CfVec3f_hash_dyn__til_closure = { (void *)CfVec3f_hash_dyn, NULL, NULL };
U32 CfVec3f_size_dyn(void *til_env) {
    (void)til_env;
    return CfVec3f_size();
}
static __attribute__((unused)) TilClosure CfVec3f_size_dyn__til_closure = { (void *)CfVec3f_size_dyn, NULL, NULL };
Bool Color_eq_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Color_eq(_a0, _a1);
}
static __attribute__((unused)) TilClosure Color_eq_dyn__til_closure = { (void *)Color_eq_dyn, NULL, NULL };
void Color_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Color_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Color_delete_dyn__til_closure = { (void *)Color_delete_dyn, NULL, NULL };
void *Color_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Color_clone(_a0);
}
static __attribute__((unused)) TilClosure Color_clone_dyn__til_closure = { (void *)Color_clone_dyn, NULL, NULL };
U32 Color_size_dyn(void *til_env) {
    (void)til_env;
    return Color_size();
}
static __attribute__((unused)) TilClosure Color_size_dyn__til_closure = { (void *)Color_size_dyn, NULL, NULL };
void *Token_Num_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Token_Num(_a0);
}
static __attribute__((unused)) TilClosure Token_Num_dyn__til_closure = { (void *)Token_Num_dyn, NULL, NULL };
void *Token_Name_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Token_Name(_a0);
}
static __attribute__((unused)) TilClosure Token_Name_dyn__til_closure = { (void *)Token_Name_dyn, NULL, NULL };
void *Token_Eof_dyn(void *til_env) {
    (void)til_env;
    return (void *)Token_Eof();
}
static __attribute__((unused)) TilClosure Token_Eof_dyn__til_closure = { (void *)Token_Eof_dyn, NULL, NULL };
Bool Token_is_dyn(void *til_env, void *_a0, void *_a1) {
    (void)til_env;
    return Token_is(_a0, _a1);
}
static __attribute__((unused)) TilClosure Token_is_dyn__til_closure = { (void *)Token_is_dyn, NULL, NULL };
void Token_delete_dyn(void *til_env, void *_a0, Bool _a1) {
    (void)til_env;
    Token_delete(_a0, _a1);
}
static __attribute__((unused)) TilClosure Token_delete_dyn__til_closure = { (void *)Token_delete_dyn, NULL, NULL };
void *Token_clone_dyn(void *til_env, void *_a0) {
    (void)til_env;
    return (void *)Token_clone(_a0);
}
static __attribute__((unused)) TilClosure Token_clone_dyn__til_closure = { (void *)Token_clone_dyn, NULL, NULL };
U32 Token_size_dyn(void *til_env) {
    (void)til_env;
    return Token_size();
}
static __attribute__((unused)) TilClosure Token_size_dyn__til_closure = { (void *)Token_size_dyn, NULL, NULL };
void *dyn_fn(Str *type_name, Str *method) {
    (void)type_name; (void)method;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&F32_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&F32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&F32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&F32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&F32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "F32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&F32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)&U64_add_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)&U64_sub_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U64_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_i64", 6ULL) == 0) return (void*)&U32_to_i64_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&U32_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)&U32_add_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)&U32_sub_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mul", 3ULL) == 0) return (void*)&U32_mul_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "inc", 3ULL) == 0) return (void*)&U32_inc_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "dec", 3ULL) == 0) return (void*)&U32_dec_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&U32_eq_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U32_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)&U32_lt_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)&U32_gt_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)&U32_neq_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "lte", 3ULL) == 0) return (void*)&U32_lte_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "U32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "gte", 3ULL) == 0) return (void*)&U32_gte_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I32_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I32_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I32_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I32_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I32", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I32_hash_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I8_cmp_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I8_clone_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I8_delete_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I8_size_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "I8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I8_hash_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&U8_cmp_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&U8_clone_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&U8_delete_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&U8_size_dyn__til_closure;
    if (type_name->count == 2ULL && memcmp(type_name->c_str, "U8", 2ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&U8_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)&Str_len_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)&Str_get_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&Str_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "with_capacity", 13ULL) == 0) return (void*)&Str_with_capacity_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "push_str", 8ULL) == 0) return (void*)&Str_push_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Str_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Str_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 8ULL && memcmp(method->c_str, "is_empty", 8ULL) == 0) return (void*)&Str_is_empty_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Str_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Str_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "Str", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Str_eq_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&OutOfBounds_clone_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&OutOfBounds_delete_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&OutOfBounds_hash_dyn__til_closure;
    if (type_name->count == 11ULL && memcmp(type_name->c_str, "OutOfBounds", 11ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&OutOfBounds_size_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "Dynamic", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Dynamic_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "to_str", 6ULL) == 0) return (void*)&I64_to_str_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "to_u8", 5ULL) == 0) return (void*)&I64_to_u8_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "add", 3ULL) == 0) return (void*)&I64_add_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "sub", 3ULL) == 0) return (void*)&I64_sub_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "div", 3ULL) == 0) return (void*)&I64_div_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "mod", 3ULL) == 0) return (void*)&I64_mod_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&I64_eq_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&I64_cmp_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&I64_clone_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&I64_delete_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&I64_size_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&I64_hash_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "lt", 2ULL) == 0) return (void*)&I64_lt_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "gt", 2ULL) == 0) return (void*)&I64_gt_dyn__til_closure;
    if (type_name->count == 3ULL && memcmp(type_name->c_str, "I64", 3ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "neq", 3ULL) == 0) return (void*)&I64_neq_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Bool_eq_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "cmp", 3ULL) == 0) return (void*)&Bool_cmp_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Bool_clone_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Bool_delete_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Bool_size_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Bool", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&Bool_hash_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Primitive_eq_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Primitive_delete_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Primitive_clone_dyn__til_closure;
    if (type_name->count == 9ULL && memcmp(type_name->c_str, "Primitive", 9ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Primitive_size_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Unknown", 7ULL) == 0) return (void*)&Type_Unknown_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "None", 4ULL) == 0) return (void*)&Type_None_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Struct", 6ULL) == 0) return (void*)&Type_Struct_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "StructDef", 9ULL) == 0) return (void*)&Type_StructDef_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Enum", 4ULL) == 0) return (void*)&Type_Enum_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "EnumDef", 7ULL) == 0) return (void*)&Type_EnumDef_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncDef", 7ULL) == 0) return (void*)&Type_FuncDef_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "FuncPtr", 7ULL) == 0) return (void*)&Type_FuncPtr_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 7ULL && memcmp(method->c_str, "Dynamic", 7ULL) == 0) return (void*)&Type_Dynamic_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "Custom", 6ULL) == 0) return (void*)&Type_Custom_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 9ULL && memcmp(method->c_str, "Primitive", 9ULL) == 0) return (void*)&Type_Primitive_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 10ULL && memcmp(method->c_str, "FuncPtrSig", 10ULL) == 0) return (void*)&Type_FuncPtrSig_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Type_delete_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Type_clone_dyn__til_closure;
    if (type_name->count == 4ULL && memcmp(type_name->c_str, "Type", 4ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Type_size_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 13ULL && memcmp(method->c_str, "new_type_name", 13ULL) == 0) return (void*)&Array_new_type_name_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "new", 3ULL) == 0) return (void*)&Array_new_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "len", 3ULL) == 0) return (void*)&Array_len_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "get", 3ULL) == 0) return (void*)&Array_get_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "set", 3ULL) == 0) return (void*)&Array_set_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Array_delete_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Array_clone_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Array", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Array_size_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&CfVec2_clone_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&CfVec2_delete_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&CfVec2_hash_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfVec2", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&CfVec2_size_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&CfRect_clone_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&CfRect_delete_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&CfRect_hash_dyn__til_closure;
    if (type_name->count == 6ULL && memcmp(type_name->c_str, "CfRect", 6ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&CfRect_size_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&CfVec3f_clone_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&CfVec3f_delete_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "hash", 4ULL) == 0) return (void*)&CfVec3f_hash_dyn__til_closure;
    if (type_name->count == 7ULL && memcmp(type_name->c_str, "CfVec3f", 7ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&CfVec3f_size_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "eq", 2ULL) == 0) return (void*)&Color_eq_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Color_delete_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Color_clone_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Color", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Color_size_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Num", 3ULL) == 0) return (void*)&Token_Num_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "Name", 4ULL) == 0) return (void*)&Token_Name_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 3ULL && memcmp(method->c_str, "Eof", 3ULL) == 0) return (void*)&Token_Eof_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 2ULL && memcmp(method->c_str, "is", 2ULL) == 0) return (void*)&Token_is_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 6ULL && memcmp(method->c_str, "delete", 6ULL) == 0) return (void*)&Token_delete_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 5ULL && memcmp(method->c_str, "clone", 5ULL) == 0) return (void*)&Token_clone_dyn__til_closure;
    if (type_name->count == 5ULL && memcmp(type_name->c_str, "Token", 5ULL) == 0 && method->count == 4ULL && memcmp(method->c_str, "size", 4ULL) == 0) return (void*)&Token_size_dyn__til_closure;
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
