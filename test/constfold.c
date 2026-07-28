#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>

#include "ext.h"

typedef struct TilClosure TilClosure;
struct TilClosure {
    void *call;
    void *env;
    void (*drop)(void *);
};

typedef struct Str Str;
typedef struct OutOfBounds OutOfBounds;
typedef struct Array__Str Array__Str;
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
    Type_TAG_FuncPtrSig,
    Type_TAG_Body
} Type_tag;
typedef struct Type Type;
typedef struct Range Range;
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


typedef struct Str {
    I8 *c_str;
    USize count;
    USize cap;
} Str;


typedef struct OutOfBounds {
    char _;
} OutOfBounds;


typedef struct Array__Str {
    U8 *data;
    USize cap;
} Array__Str;


typedef struct Dynamic {
    char _;
} Dynamic;










struct Primitive {
    U8 tag;
};

struct Type {
    U8 tag;
    union {
        Str Struct;
        Str Enum;
        Str Custom;
        Primitive Primitive;
        Str FuncPtrSig;
        void *_til_payload_align;
    } data;
};

typedef struct Range {
    U64 start;
    U64 end;
} Range;


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
    U8 tag;
};

struct Token {
    U8 tag;
    union {
        I64 Num;
        Str Name;
        void *_til_payload_align;
    } data;
};

Str * format(Array__Str * parts);
USize Str_len(Str * self);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(USize n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
USize Str_size(void);
Bool Str_neq(Str * a, Str * b);
USize OutOfBounds_size(void);
Array__Str * Array__Str_new(USize cap);
USize Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, USize * i);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
USize Array__Str_size(void);
USize Dynamic_size(void);
USize U8_size(void);
USize U32_size(void);
Str * U64_to_str(U64 val);
USize U64_size(void);
USize I8_size(void);
USize I32_size(void);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
USize I64_size(void);
USize F32_size(void);
USize Bool_size(void);
USize Primitive_size(void);
USize Type_size(void);
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
USize Range_size(void);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_variadic_fold(void);
void test_variadic_direct_fold(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
void test_fold_f32(void);
void CfVec2_delete(CfVec2 * self, Bool call_free);
USize CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
void CfRect_delete(CfRect * self, Bool call_free);
USize CfRect_size(void);
void test_struct_fold_nested(void);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
USize CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
USize Color_size(void);
void test_enum_fold(void);
void Token_delete(Token * self, Bool call_free);
USize Token_size(void);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
void assert_eq__I64(I64 a, I64 b, Str * loc);
void assert_eq__Str(Str * a, Str * b, Str * loc);
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

Str * format(Array__Str * parts);
USize Str_len(Str * self);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(USize n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
USize Str_size(void);
Bool Str_neq(Str * a, Str * b);
USize OutOfBounds_size(void);
Array__Str * Array__Str_new(USize cap);
USize Array__Str_len(Array__Str * self);
Str * Array__Str_unsafe_get(Array__Str * self, USize * i);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
USize Array__Str_size(void);
USize Dynamic_size(void);
USize U8_size(void);
USize U32_size(void);
Str * U64_to_str(U64 val);
USize U64_size(void);
USize I8_size(void);
USize I32_size(void);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
USize I64_size(void);
USize F32_size(void);
USize Bool_size(void);
USize Primitive_size(void);
USize Type_size(void);
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
USize Range_size(void);
void test_simple_add(void);
void test_nested_arithmetic(void);
void test_deeply_nested(void);
void test_string_concat(void);
void test_variadic_fold(void);
void test_variadic_direct_fold(void);
void test_lolalalo(void);
void test_fold_variable(void);
void test_loc_folded(void);
void test_fold_f32(void);
void CfVec2_delete(CfVec2 * self, Bool call_free);
USize CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
void CfRect_delete(CfRect * self, Bool call_free);
USize CfRect_size(void);
void test_struct_fold_nested(void);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
USize CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
USize Color_size(void);
void test_enum_fold(void);
Token * Token_Num(I64 * val);
Token * Token_Name(Str * val);
Token * Token_Eof(void);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool call_free);
USize Token_size(void);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
void assert_eq__I64(I64 a, I64 b, Str * loc);
void assert_eq__Str(Str * a, Str * b, Str * loc);
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
Type *Type_Body();
Bool Color_eq(Color *, Color *);
Color *Color_Red();
Color *Color_Green();
Color *Color_Blue();
Token *Token_Num(I64 *);
Token *Token_Name(Str *);
Token *Token_Eof();


#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
#define TIL_CAP_LIT ((USize)-1)
#define TIL_CAP_VIEW ((USize)-2)
void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
void print_flush() {
    putchar('\n');
}

static Str _til_str_lits[70] = {
    (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"StructDef", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"EnumDef", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"FunctionDef", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Fn", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Dynamic", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I16", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U16", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I8", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U8", .count = 2ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U32", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I32", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"U64", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"I64", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"F32", .count = 3ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Bool", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"Body", .count = 4ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"?", .count = 1ULL, .cap = TIL_CAP_LIT},
};
#define TIL_LIT_GUARD(p) do { UPtr _g = (UPtr)(const void *)(p); if (_g >= (UPtr)(const void *)_til_str_lits && _g < (UPtr)(const void *)(_til_str_lits + 70)) { fprintf(stderr, "panic: write through a shared string literal\n"); exit(1); } } while (0)

U32 CAP_LIT;
U32 CAP_VIEW;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_55 = parts;
        (void)_fc_Array__Str_55;
        (void)_fc_Array__Str_55;
        U32 _fi_USize_55 = 0;
        (void)_fi_USize_55;
        while (1) {
            USize hoisted__U32_57 = (_fc_Array__Str_55->cap);
            Bool _wcond_Bool_56 = ((Bool)(_fi_USize_55 < hoisted__U32_57));
            (void)_wcond_Bool_56;
            if (_wcond_Bool_56) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_55->data) + (((U32)(_fi_USize_55 * 16))))));
            U32 hoisted__U32_58 = 1;
            U32 hoisted__U32_59 = ((U32)(_fi_USize_55 + hoisted__U32_58));
            _fi_USize_55 = hoisted__U32_59;
            USize hoisted__U32_60 = (s->count);
            U32 hoisted__U32_61 = ((U32)(total + hoisted__U32_60));
            total = hoisted__U32_61;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_62 = parts;
        (void)_fc_Array__Str_62;
        (void)_fc_Array__Str_62;
        U32 _fi_USize_62 = 0;
        (void)_fi_USize_62;
        while (1) {
            USize hoisted__U32_64 = (_fc_Array__Str_62->cap);
            Bool _wcond_Bool_63 = ((Bool)(_fi_USize_62 < hoisted__U32_64));
            (void)_wcond_Bool_63;
            if (_wcond_Bool_63) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_62->data) + (((U32)(_fi_USize_62 * 16))))));
            U32 hoisted__U32_65 = 1;
            U32 hoisted__U32_66 = ((U32)(_fi_USize_62 + hoisted__U32_65));
            _fi_USize_62 = hoisted__U32_66;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

USize Str_len(Str * self) {
    return self->count;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_93 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_93) {
        Bool hoisted__Bool_91 = 0;
        return hoisted__Bool_91;
    }
    Bool hoisted__Bool_94 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_94) {
        Bool hoisted__Bool_92 = 1;
        return hoisted__Bool_92;
    }
    I32 hoisted__I32_95 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_96 = 0;
    Bool hoisted__Bool_97 = ((Bool)(hoisted__I32_95 == hoisted__I32_96));
    return hoisted__Bool_97;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_99 = 0;
    Bool hoisted__Bool_100 = ((Bool)(n == hoisted__U32_99));
    if (hoisted__Bool_100) {
        static Str hoisted__Str_98 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_98; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_101 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_101)));
    I32 hoisted__I32_102 = 0;
    U64 hoisted__U64_103 = 1ULL;
    memset(buf, hoisted__I32_102, hoisted__U64_103);
    I64 hoisted__I64_104 = 0;
    Str *hoisted__Str_105 = malloc(sizeof(Str));
    hoisted__Str_105->c_str = buf;
    hoisted__Str_105->count = hoisted__I64_104;
    hoisted__Str_105->cap = n;
    return hoisted__Str_105;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_116 = 0;
    Bool hoisted__Bool_117 = ((Bool)(s->count == hoisted__U32_116));
    if (hoisted__Bool_117) {
        return;
    }
    Bool hoisted__Bool_118 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_118) {
        U32 hoisted__U32_108 = 1;
        Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_108);
        (void)_va_Array_1;
        I64 _va_Array_1_ek = 0;
        (void)_va_Array_1_ek;
        U32 hoisted__U32_109 = 0;
        static Str hoisted__Str_110 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_1, hoisted__U32_109, &hoisted__Str_110, &_va_Array_1_ek);
        static Str hoisted__Str_111 = (Str){.c_str = (void *)"./src/core/str.til:124:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_1, &hoisted__Str_111);
        Str_delete(&hoisted__Str_111, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_119 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_119) {
        U32 hoisted__U32_112 = 1;
        Array__Str *_va_Array_2 = Array__Str_new(hoisted__U32_112);
        (void)_va_Array_2;
        I64 _va_Array_2_ek = 0;
        (void)_va_Array_2_ek;
        U32 hoisted__U32_113 = 0;
        static Str hoisted__Str_114 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_2, hoisted__U32_113, &hoisted__Str_114, &_va_Array_2_ek);
        static Str hoisted__Str_115 = (Str){.c_str = (void *)"./src/core/str.til:128:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_2, &hoisted__Str_115);
        Str_delete(&hoisted__Str_115, (Bool){0});
    }
    void *hoisted__v_120 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_120, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_121 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_122 = 0;
    U64 hoisted__U64_123 = 1ULL;
    memset(hoisted__v_121, hoisted__I32_122, hoisted__U64_123);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_125 = 0;
    Bool hoisted__Bool_126 = ((Bool)(val->count == hoisted__U32_125));
    if (hoisted__Bool_126) {
        static Str hoisted__Str_124 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_124; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_127 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_127)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_128 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_129 = 0;
    U64 hoisted__U64_130 = 1ULL;
    memset(hoisted__v_128, hoisted__I32_129, hoisted__U64_130);
    Str *hoisted__Str_131 = malloc(sizeof(Str));
    hoisted__Str_131->c_str = new_data;
    hoisted__Str_131->count = val->count;
    hoisted__Str_131->cap = val->count;
    return hoisted__Str_131;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_132 = Str_clone(self);
    return hoisted__Str_132;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_133 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_133) {
        free(self->c_str);
    }
    Bool hoisted__Bool_134 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_135 = ((Bool)((call_free) && (hoisted__Bool_134)));
    if (hoisted__Bool_135) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

USize Str_size(void) {
    U32 hoisted__U32_502 = 16;
    return hoisted__U32_502;
    __builtin_unreachable();
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_511 = Str_eq(a, b);
    Bool hoisted__Bool_512 = ((Bool)(!(hoisted__Bool_511)));
    return hoisted__Bool_512;
    __builtin_unreachable();
}

USize OutOfBounds_size(void) {
    U32 hoisted__U32_603 = 1;
    return hoisted__U32_603;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_615 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_616 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_616->data = hoisted__v_615;
    hoisted__Array__Str_616->cap = cap;
    return hoisted__Array__Str_616;
    __builtin_unreachable();
}

USize Array__Str_len(Array__Str * self) {
    return self->cap;
    __builtin_unreachable();
}

Str * Array__Str_unsafe_get(Array__Str * self, USize * i) {
    U32 hoisted__U32_617 = 16;
    U32 hoisted__U32_618 = ((U32)(DEREF(i) * hoisted__U32_617));
    void *hoisted__v_619 = ((void *)((U8 *)(self->data) + (hoisted__U32_618)));
    return hoisted__v_619;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_625 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Bool hoisted__Bool_626 = 0;
    Str_delete(hoisted__Str_625, hoisted__Bool_626);
    Str *hoisted__Str_627 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    U32 hoisted__U32_628 = 16;
    memcpy(hoisted__Str_627, val, hoisted__U32_628);
    I32 hoisted__I32_629 = 0;
    U32 hoisted__U32_630 = 16;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_629, hoisted__U32_630); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_632 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_632) {
        I64 hoisted__I64_631 = 1;
        *_err_kind = hoisted__I64_631;
    }
    I64 hoisted__I64_633 = 0;
    Bool hoisted__Bool_634 = ((Bool)(DEREF(_err_kind) == hoisted__I64_633));
    if (hoisted__Bool_634) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_635 = self->cap;
        (void)_re_U32_635;
        U32 _rc_U32_635 = 0;
        (void)_rc_U32_635;
        Bool hoisted__Bool_646 = ((Bool)(_rc_U32_635 <= _re_U32_635));
        if (hoisted__Bool_646) {
            while (1) {
                Bool _wcond_Bool_636 = ((Bool)(_rc_U32_635 < _re_U32_635));
                (void)_wcond_Bool_636;
                if (_wcond_Bool_636) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_635);
                (++_rc_U32_635);
                U32 hoisted__U32_637 = 16;
                U32 hoisted__U32_638 = ((U32)(i * hoisted__U32_637));
                Str *hoisted__Str_639 = ((void *)((U8 *)(self->data) + (hoisted__U32_638)));
                Bool hoisted__Bool_640 = 0;
                Str_delete(hoisted__Str_639, hoisted__Bool_640);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_641 = ((Bool)(_rc_U32_635 > _re_U32_635));
                (void)_wcond_Bool_641;
                if (_wcond_Bool_641) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_635);
                (--_rc_U32_635);
                U32 hoisted__U32_642 = 16;
                U32 hoisted__U32_643 = ((U32)(i * hoisted__U32_642));
                Str *hoisted__Str_644 = ((void *)((U8 *)(self->data) + (hoisted__U32_643)));
                Bool hoisted__Bool_645 = 0;
                Str_delete(hoisted__Str_644, hoisted__Bool_645);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_667 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_667)));
    {
        U32 _re_U32_647 = self->cap;
        (void)_re_U32_647;
        U32 _rc_U32_647 = 0;
        (void)_rc_U32_647;
        Bool hoisted__Bool_666 = ((Bool)(_rc_U32_647 <= _re_U32_647));
        if (hoisted__Bool_666) {
            while (1) {
                Bool _wcond_Bool_648 = ((Bool)(_rc_U32_647 < _re_U32_647));
                (void)_wcond_Bool_648;
                if (_wcond_Bool_648) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_647);
                (++_rc_U32_647);
                U32 hoisted__U32_649 = 16;
                U32 hoisted__U32_650 = ((U32)(i * hoisted__U32_649));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_650)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_651 = 16;
                U32 hoisted__U32_652 = ((U32)(i * hoisted__U32_651));
                void *hoisted__v_653 = ((void *)((U8 *)(new_data) + (hoisted__U32_652)));
                U32 hoisted__U32_654 = 16;
                memcpy(hoisted__v_653, cloned, hoisted__U32_654);
                I32 hoisted__I32_655 = 0;
                U32 hoisted__U32_656 = 16;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_655, hoisted__U32_656); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_657 = ((Bool)(_rc_U32_647 > _re_U32_647));
                (void)_wcond_Bool_657;
                if (_wcond_Bool_657) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_647);
                (--_rc_U32_647);
                U32 hoisted__U32_658 = 16;
                U32 hoisted__U32_659 = ((U32)(i * hoisted__U32_658));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_659)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_660 = 16;
                U32 hoisted__U32_661 = ((U32)(i * hoisted__U32_660));
                void *hoisted__v_662 = ((void *)((U8 *)(new_data) + (hoisted__U32_661)));
                U32 hoisted__U32_663 = 16;
                memcpy(hoisted__v_662, cloned, hoisted__U32_663);
                I32 hoisted__I32_664 = 0;
                U32 hoisted__U32_665 = 16;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_664, hoisted__U32_665); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_668 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_668->data = new_data;
    hoisted__Array__Str_668->cap = self->cap;
    return hoisted__Array__Str_668;
    __builtin_unreachable();
}

USize Array__Str_size(void) {
    U32 hoisted__U32_669 = 16;
    return hoisted__U32_669;
    __builtin_unreachable();
}

USize Dynamic_size(void) {
    U32 hoisted__U32_961 = 8;
    return hoisted__U32_961;
    __builtin_unreachable();
}

USize U8_size(void) {
    U32 hoisted__U32_1069 = 1;
    return hoisted__U32_1069;
    __builtin_unreachable();
}

USize U32_size(void) {
    U32 hoisted__U32_1223 = 4;
    return hoisted__U32_1223;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1292 = U64_to_str_ext(val);
    return hoisted__Str_1292;
    __builtin_unreachable();
}

USize U64_size(void) {
    U32 hoisted__U32_1297 = 8;
    return hoisted__U32_1297;
    __builtin_unreachable();
}

USize I8_size(void) {
    U32 hoisted__U32_1382 = 1;
    return hoisted__U32_1382;
    __builtin_unreachable();
}

USize I32_size(void) {
    U32 hoisted__U32_1531 = 4;
    return hoisted__U32_1531;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1653 = 0;
    Bool hoisted__Bool_1654 = ((Bool)(val < hoisted__I64_1653));
    if (hoisted__Bool_1654) {
        U64 hoisted__U64_1645 = 0ULL;
        U64 hoisted__U64_1646 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_1645 - hoisted__U64_1646));
        U32 hoisted__U32_1647 = 2;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1647);
        (void)_va_Array_39;
        I64 _va_Array_39_ek = 0;
        (void)_va_Array_39_ek;
        U32 hoisted__U32_1648 = 0;
        static Str hoisted__Str_1649 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_39, hoisted__U32_1648, &hoisted__Str_1649, &_va_Array_39_ek);
        U32 hoisted__U32_1650 = 1;
        Str *hoisted__Str_1651 = U64_to_str(mag);
        Array__Str_set(_va_Array_39, hoisted__U32_1650, hoisted__Str_1651, &_va_Array_39_ek);
        Str *hoisted__Str_1652 = format(_va_Array_39);
        return hoisted__Str_1652;
    }
    U64 hoisted__U64_1655 = (U64)(val);
    Str *hoisted__Str_1656 = U64_to_str(hoisted__U64_1655);
    return hoisted__Str_1656;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I64_size(void) {
    U32 hoisted__U32_1670 = 8;
    return hoisted__U32_1670;
    __builtin_unreachable();
}

USize F32_size(void) {
    U32 hoisted__U32_1799 = 4;
    return hoisted__U32_1799;
    __builtin_unreachable();
}

USize Bool_size(void) {
    U32 hoisted__U32_1861 = 1;
    return hoisted__U32_1861;
    __builtin_unreachable();
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
USize Primitive_size(void) {
    U32 hoisted__U32_1911 = 1;
    return hoisted__U32_1911;
    __builtin_unreachable();
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
    if (val->cap != TIL_CAP_LIT) { free(val); }
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
    if (val->cap != TIL_CAP_LIT) { free(val); }
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
    if (val->cap != TIL_CAP_LIT) { free(val); }
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
    if (val->cap != TIL_CAP_LIT) { free(val); }
    return r;
}
Type *Type_Body() {
    Type *r = malloc(sizeof(Type));
    r->tag = Type_TAG_Body;
    return r;
}
USize Type_size(void) {
    U32 hoisted__U32_2053 = 24;
    return hoisted__U32_2053;
    __builtin_unreachable();
}


__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_5532 = 3;
    Array__Str *_va_Array_148 = Array__Str_new(hoisted__U32_5532);
    (void)_va_Array_148;
    I64 _va_Array_148_ek = 0;
    (void)_va_Array_148_ek;
    U32 hoisted__U32_5533 = 0;
    Str *hoisted__Str_5534 = Str_clone(loc);
    Array__Str_set(_va_Array_148, hoisted__U32_5533, hoisted__Str_5534, &_va_Array_148_ek);
    U32 hoisted__U32_5535 = 1;
    Array__Str_set(_va_Array_148, hoisted__U32_5535, &_til_str_lits[0], &_va_Array_148_ek);
    Array__Str *hoisted__Array__Str_5537 = Array__Str_clone(parts);
    U32 hoisted__U32_5538 = 2;
    Str *hoisted__Str_5539 = format(hoisted__Array__Str_5537);
    Array__Str_set(_va_Array_148, hoisted__U32_5538, hoisted__Str_5539, &_va_Array_148_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_148);
    I64 hoisted__I64_5540 = 1;
    exit(hoisted__I64_5540);
}

__attribute__((noreturn)) void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_5547 = 1;
    Array__Str *_va_Array_150 = Array__Str_new(hoisted__U32_5547);
    (void)_va_Array_150;
    I64 _va_Array_150_ek = 0;
    (void)_va_Array_150_ek;
    U32 hoisted__U32_5548 = 0;
    Array__Str_set(_va_Array_150, hoisted__U32_5548, &_til_str_lits[1], &_va_Array_150_ek);
    panic(_va_Array_150, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_5553 = ((Bool)(!(cond)));
    if (hoisted__Bool_5553) {
        U32 hoisted__U32_5550 = 1;
        Array__Str *_va_Array_151 = Array__Str_new(hoisted__U32_5550);
        (void)_va_Array_151;
        I64 _va_Array_151_ek = 0;
        (void)_va_Array_151_ek;
        U32 hoisted__U32_5551 = 0;
        Array__Str_set(_va_Array_151, hoisted__U32_5551, &_til_str_lits[2], &_va_Array_151_ek);
        panic(_va_Array_151, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_5561 = parts;
        (void)_fc_Array__Str_5561;
        (void)_fc_Array__Str_5561;
        U32 _fi_USize_5561 = 0;
        (void)_fi_USize_5561;
        while (1) {
            USize hoisted__U32_5563 = (_fc_Array__Str_5561->cap);
            Bool _wcond_Bool_5562 = ((Bool)(_fi_USize_5561 < hoisted__U32_5563));
            (void)_wcond_Bool_5562;
            if (_wcond_Bool_5562) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_5561->data) + (((U32)(_fi_USize_5561 * 16))))));
            U32 hoisted__U32_5564 = 1;
            U32 hoisted__U32_5565 = ((U32)(_fi_USize_5561 + hoisted__U32_5564));
            _fi_USize_5561 = hoisted__U32_5565;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

USize Range_size(void) {
    U32 hoisted__U32_5604 = 16;
    return hoisted__U32_5604;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_5618 = 3;
    assert_eq__I64(result, hoisted__I64_5618, &_til_str_lits[3]);
    Str_delete(&_til_str_lits[3], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_5626 = 15;
    assert_eq__I64(result, hoisted__I64_5626, &_til_str_lits[4]);
    Str_delete(&_til_str_lits[4], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_5634 = 26;
    assert_eq__I64(result, hoisted__I64_5634, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&result, &_til_str_lits[6], &_til_str_lits[7]);
    Str_delete(&_til_str_lits[6], (Bool){0});
    Str_delete(&_til_str_lits[7], (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r, &_til_str_lits[6], &_til_str_lits[8]);
    Str_delete(&_til_str_lits[6], (Bool){0});
    Str_delete(&_til_str_lits[8], (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r2, &_til_str_lits[9], &_til_str_lits[10]);
    Str_delete(&_til_str_lits[9], (Bool){0});
    Str_delete(&_til_str_lits[10], (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d, &_til_str_lits[11], &_til_str_lits[12]);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lits[11], (Bool){0});
    Str_delete(&_til_str_lits[12], (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d2, &_til_str_lits[13], &_til_str_lits[14]);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lits[13], (Bool){0});
    Str_delete(&_til_str_lits[14], (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_5703 = 106;
    assert_eq__I64(d3, hoisted__I64_5703, &_til_str_lits[15]);
    Str_delete(&_til_str_lits[15], (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lits[18]);
    Str_delete(&_til_str_lits[18], (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lits[19]);
    Str_delete(&_til_str_lits[19], (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_6196 = 8;
    assert_eq__I64(result, hoisted__I64_6196, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6200 = 1;
    assert(hoisted__Bool_6200, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
    Bool hoisted__Bool_6204 = 1;
    assert(hoisted__Bool_6204, &_til_str_lits[22]);
    Str_delete(&_til_str_lits[22], (Bool){0});
}

void test_fold_f32(void) {
    assert_eq__Str(&_til_str_lits[23], &_til_str_lits[23], &_til_str_lits[24]);
    Str_delete(&_til_str_lits[23], (Bool){0});
    Str_delete(&_til_str_lits[23], (Bool){0});
    Str_delete(&_til_str_lits[24], (Bool){0});
    assert_eq__Str(&_til_str_lits[25], &_til_str_lits[25], &_til_str_lits[26]);
    Str_delete(&_til_str_lits[25], (Bool){0});
    Str_delete(&_til_str_lits[25], (Bool){0});
    Str_delete(&_til_str_lits[26], (Bool){0});
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize CfVec2_size(void) {
    U32 hoisted__U32_6248 = 16;
    return hoisted__U32_6248;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_6249 = 42;
    assert_eq__I64(v.x, hoisted__I64_6249, &_til_str_lits[27]);
    Str_delete(&_til_str_lits[27], (Bool){0});
    I64 hoisted__I64_6251 = 99;
    assert_eq__I64(v.y, hoisted__I64_6251, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6255 = 10;
    assert_eq__I64(p.x, hoisted__I64_6255, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    I64 hoisted__I64_6257 = 20;
    assert_eq__I64(p.y, hoisted__I64_6257, &_til_str_lits[30]);
    Str_delete(&_til_str_lits[30], (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize CfRect_size(void) {
    U32 hoisted__U32_6290 = 32;
    return hoisted__U32_6290;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_6291 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_6291, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    I64 hoisted__I64_6293 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_6293, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_6295 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6295, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_6297 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6297, &_til_str_lits[34]);
    Str_delete(&_til_str_lits[34], (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize CfVec3f_size(void) {
    U32 hoisted__U32_6335 = 12;
    return hoisted__U32_6335;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_6339 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_6339, &_til_str_lits[35], &_til_str_lits[36]);
    Str_delete(hoisted__Str_6339, 1);
    Str_delete(&_til_str_lits[35], (Bool){0});
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str *hoisted__Str_6342 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_6342, &_til_str_lits[37], &_til_str_lits[38]);
    Str_delete(hoisted__Str_6342, 1);
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str *hoisted__Str_6345 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_6345, &_til_str_lits[39], &_til_str_lits[40]);
    Str_delete(hoisted__Str_6345, 1);
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str_delete(&_til_str_lits[40], (Bool){0});
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
    Bool hoisted__Bool_6348 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_6348;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_6356 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_6356) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
        return _r; }
    }
    Bool hoisted__Bool_6357 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_6357) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
        return _r; }
    }
    Bool hoisted__Bool_6358 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_6358) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
        return _r; }
    }
    static Str hoisted__Str_6359 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_6359);
    Str_delete(&hoisted__Str_6359, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

USize Color_size(void) {
    U32 hoisted__U32_6360 = 1;
    return hoisted__U32_6360;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_6361 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_6361, &_til_str_lits[41]);
    Str_delete(&_til_str_lits[41], (Bool){0});
    Bool hoisted__Bool_6363 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_6364 = ((Bool)(!(hoisted__Bool_6363)));
    assert(hoisted__Bool_6364, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
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
    if (val->cap != TIL_CAP_LIT) { free(val); }
    return r;
}
Token *Token_Eof() {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Eof;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_6383 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_6383) {
        I64 *hoisted__I64_6379 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6380 = 0;
        I64_delete(hoisted__I64_6379, hoisted__Bool_6380);
    }
    Bool hoisted__Bool_6384 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_6384) {
        Str *hoisted__Str_6381 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6382 = 0;
        Str_delete(hoisted__Str_6381, hoisted__Bool_6382);
    }
    if (call_free) {
        free(self);
    }
}

USize Token_size(void) {
    U32 hoisted__U32_6411 = 24;
    return hoisted__U32_6411;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_6413 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    assert(hoisted__Bool_6413, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
    Bool hoisted__Bool_6415 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    Bool hoisted__Bool_6416 = ((Bool)(!(hoisted__Bool_6415)));
    assert(hoisted__Bool_6416, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_6418 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_6418, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Bool hoisted__Bool_6420 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_6421 = ((Bool)(!(hoisted__Bool_6420)));
    assert(hoisted__Bool_6421, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_6425 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    assert(hoisted__Bool_6425, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
    Bool hoisted__Bool_6427 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    Bool hoisted__Bool_6428 = ((Bool)(!(hoisted__Bool_6427)));
    assert(hoisted__Bool_6428, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_6496 = ((Bool)(a != b));
    if (hoisted__Bool_6496) {
        U32 hoisted__U32_6485 = 5;
        Array__Str *_va_Array_188 = Array__Str_new(hoisted__U32_6485);
        (void)_va_Array_188;
        I64 _va_Array_188_ek = 0;
        (void)_va_Array_188_ek;
        U32 hoisted__U32_6486 = 0;
        Array__Str_set(_va_Array_188, hoisted__U32_6486, &_til_str_lits[49], &_va_Array_188_ek);
        U32 hoisted__U32_6488 = 1;
        Str *hoisted__Str_6489 = I64_to_str(a);
        Array__Str_set(_va_Array_188, hoisted__U32_6488, hoisted__Str_6489, &_va_Array_188_ek);
        U32 hoisted__U32_6490 = 2;
        Array__Str_set(_va_Array_188, hoisted__U32_6490, &_til_str_lits[50], &_va_Array_188_ek);
        U32 hoisted__U32_6492 = 3;
        Str *hoisted__Str_6493 = I64_to_str(b);
        Array__Str_set(_va_Array_188, hoisted__U32_6492, hoisted__Str_6493, &_va_Array_188_ek);
        U32 hoisted__U32_6494 = 4;
        Array__Str_set(_va_Array_188, hoisted__U32_6494, &_til_str_lits[51], &_va_Array_188_ek);
        panic(_va_Array_188, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_6508 = Str_neq(a, b);
    if (hoisted__Bool_6508) {
        U32 hoisted__U32_6497 = 5;
        Array__Str *_va_Array_189 = Array__Str_new(hoisted__U32_6497);
        (void)_va_Array_189;
        I64 _va_Array_189_ek = 0;
        (void)_va_Array_189_ek;
        U32 hoisted__U32_6498 = 0;
        Array__Str_set(_va_Array_189, hoisted__U32_6498, &_til_str_lits[49], &_va_Array_189_ek);
        U32 hoisted__U32_6500 = 1;
        Str *hoisted__Str_6501 = Str_to_str(a);
        Array__Str_set(_va_Array_189, hoisted__U32_6500, hoisted__Str_6501, &_va_Array_189_ek);
        U32 hoisted__U32_6502 = 2;
        Array__Str_set(_va_Array_189, hoisted__U32_6502, &_til_str_lits[50], &_va_Array_189_ek);
        U32 hoisted__U32_6504 = 3;
        Str *hoisted__Str_6505 = Str_to_str(b);
        Array__Str_set(_va_Array_189, hoisted__U32_6504, hoisted__Str_6505, &_va_Array_189_ek);
        U32 hoisted__U32_6506 = 4;
        Array__Str_set(_va_Array_189, hoisted__U32_6506, &_til_str_lits[51], &_va_Array_189_ek);
        panic(_va_Array_189, loc);
    }
}

int main(void) {
    CAP_LIT = 4294967295;
    CAP_VIEW = 4294967294;
    test_simple_add();
    fprintf(stderr, "  pass: %s\n", "test_simple_add");
    test_nested_arithmetic();
    fprintf(stderr, "  pass: %s\n", "test_nested_arithmetic");
    test_deeply_nested();
    fprintf(stderr, "  pass: %s\n", "test_deeply_nested");
    test_string_concat();
    fprintf(stderr, "  pass: %s\n", "test_string_concat");
    test_variadic_fold();
    fprintf(stderr, "  pass: %s\n", "test_variadic_fold");
    test_variadic_direct_fold();
    fprintf(stderr, "  pass: %s\n", "test_variadic_direct_fold");
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
    fprintf(stderr, "18/18 tests passed\n");
    return 0;
}
