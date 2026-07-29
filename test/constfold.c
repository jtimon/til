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
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
USize Array__Str_size(void);
void adopt__Str(void * dest, Str * src);
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
__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc);
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
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
USize Array__Str_size(void);
void adopt__Str(void * dest, Str * src);
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
__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc);
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

static Str _til_str_lits[71] = {
    (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"unreachable: ", .count = 13ULL, .cap = TIL_CAP_LIT},
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
#define TIL_LIT_GUARD(p) do { UPtr _g = (UPtr)(const void *)(p); if (_g >= (UPtr)(const void *)_til_str_lits && _g < (UPtr)(const void *)(_til_str_lits + 71)) { fprintf(stderr, "panic: write through a shared string literal\n"); exit(1); } } while (0)

U32 CAP_LIT;
U32 CAP_VIEW;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_50 = parts;
        U32 _fi_USize_50 = 0;
        while (1) {
            USize hoisted__U32_52 = (_fc_Array__Str_50->cap);
            Bool _wcond_Bool_51 = ((Bool)(_fi_USize_50 < hoisted__U32_52));
            if (_wcond_Bool_51) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_50->data) + (((U32)(_fi_USize_50 * 16))))));
            U32 hoisted__U32_53 = 1;
            U32 hoisted__U32_54 = ((U32)(_fi_USize_50 + hoisted__U32_53));
            _fi_USize_50 = hoisted__U32_54;
            USize hoisted__U32_55 = (s->count);
            U32 hoisted__U32_56 = ((U32)(total + hoisted__U32_55));
            total = hoisted__U32_56;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_57 = parts;
        U32 _fi_USize_57 = 0;
        while (1) {
            USize hoisted__U32_59 = (_fc_Array__Str_57->cap);
            Bool _wcond_Bool_58 = ((Bool)(_fi_USize_57 < hoisted__U32_59));
            if (_wcond_Bool_58) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_57->data) + (((U32)(_fi_USize_57 * 16))))));
            U32 hoisted__U32_60 = 1;
            U32 hoisted__U32_61 = ((U32)(_fi_USize_57 + hoisted__U32_60));
            _fi_USize_57 = hoisted__U32_61;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_88 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_88) {
        Bool hoisted__Bool_86 = 0;
        return hoisted__Bool_86;
    }
    Bool hoisted__Bool_89 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_89) {
        Bool hoisted__Bool_87 = 1;
        return hoisted__Bool_87;
    }
    I32 hoisted__I32_90 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_91 = 0;
    Bool hoisted__Bool_92 = ((Bool)(hoisted__I32_90 == hoisted__I32_91));
    return hoisted__Bool_92;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_94 = 0;
    Bool hoisted__Bool_95 = ((Bool)(n == hoisted__U32_94));
    if (hoisted__Bool_95) {
        static Str hoisted__Str_93 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_93; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_96 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_96)));
    I32 hoisted__I32_97 = 0;
    U64 hoisted__U64_98 = 1ULL;
    memset(buf, hoisted__I32_97, hoisted__U64_98);
    I64 hoisted__I64_99 = 0;
    Str *hoisted__Str_100 = malloc(sizeof(Str));
    hoisted__Str_100->c_str = buf;
    hoisted__Str_100->count = hoisted__I64_99;
    hoisted__Str_100->cap = n;
    return hoisted__Str_100;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_111 = 0;
    Bool hoisted__Bool_112 = ((Bool)(s->count == hoisted__U32_111));
    if (hoisted__Bool_112) {
        return;
    }
    Bool hoisted__Bool_113 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_113) {
        U32 hoisted__U32_103 = 1;
        Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_103);
        I64 _va_Array_1_ek = 0;
        U32 hoisted__U32_104 = 0;
        static Str hoisted__Str_105 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_1, hoisted__U32_104, &hoisted__Str_105, &_va_Array_1_ek);
        static Str hoisted__Str_106 = (Str){.c_str = (void *)"./src/core/str.til:124:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_1, &hoisted__Str_106);
        Str_delete(&hoisted__Str_106, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_114 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_114) {
        U32 hoisted__U32_107 = 1;
        Array__Str *_va_Array_2 = Array__Str_new(hoisted__U32_107);
        I64 _va_Array_2_ek = 0;
        U32 hoisted__U32_108 = 0;
        static Str hoisted__Str_109 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_2, hoisted__U32_108, &hoisted__Str_109, &_va_Array_2_ek);
        static Str hoisted__Str_110 = (Str){.c_str = (void *)"./src/core/str.til:128:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_2, &hoisted__Str_110);
        Str_delete(&hoisted__Str_110, (Bool){0});
    }
    void *hoisted__v_115 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_115, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_116 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_117 = 0;
    U64 hoisted__U64_118 = 1ULL;
    memset(hoisted__v_116, hoisted__I32_117, hoisted__U64_118);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_120 = 0;
    Bool hoisted__Bool_121 = ((Bool)(val->count == hoisted__U32_120));
    if (hoisted__Bool_121) {
        static Str hoisted__Str_119 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_119; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_122 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_122)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_123 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_124 = 0;
    U64 hoisted__U64_125 = 1ULL;
    memset(hoisted__v_123, hoisted__I32_124, hoisted__U64_125);
    Str *hoisted__Str_126 = malloc(sizeof(Str));
    hoisted__Str_126->c_str = new_data;
    hoisted__Str_126->count = val->count;
    hoisted__Str_126->cap = val->count;
    return hoisted__Str_126;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_127 = Str_clone(self);
    return hoisted__Str_127;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_128 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_128) {
        free(self->c_str);
    }
    Bool hoisted__Bool_129 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_130 = ((Bool)((call_free) && (hoisted__Bool_129)));
    if (hoisted__Bool_130) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

USize Str_size(void) {
    U32 hoisted__U32_498 = 16;
    return hoisted__U32_498;
    __builtin_unreachable();
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_507 = Str_eq(a, b);
    Bool hoisted__Bool_508 = ((Bool)(!(hoisted__Bool_507)));
    return hoisted__Bool_508;
    __builtin_unreachable();
}

USize OutOfBounds_size(void) {
    U32 hoisted__U32_599 = 1;
    return hoisted__U32_599;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_611 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_612 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_612->data = hoisted__v_611;
    hoisted__Array__Str_612->cap = cap;
    return hoisted__Array__Str_612;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_621 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Bool hoisted__Bool_622 = 0;
    Str_delete(hoisted__Str_621, hoisted__Bool_622);
    Str *hoisted__Str_623 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    U32 hoisted__U32_624 = 16;
    memcpy(hoisted__Str_623, val, hoisted__U32_624);
    I32 hoisted__I32_625 = 0;
    U32 hoisted__U32_626 = 16;
    if ((val)->cap != TIL_CAP_LIT) { memset(val, hoisted__I32_625, hoisted__U32_626); };
    Str_delete(val, 1);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_628 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_628) {
        I64 hoisted__I64_627 = 1;
        *_err_kind = hoisted__I64_627;
    }
    I64 hoisted__I64_629 = 0;
    Bool hoisted__Bool_630 = ((Bool)(DEREF(_err_kind) == hoisted__I64_629));
    if (hoisted__Bool_630) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_631 = self->cap;
        U32 _rc_U32_631 = 0;
        Bool hoisted__Bool_642 = ((Bool)(_rc_U32_631 <= _re_U32_631));
        if (hoisted__Bool_642) {
            while (1) {
                Bool _wcond_Bool_632 = ((Bool)(_rc_U32_631 < _re_U32_631));
                if (_wcond_Bool_632) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_631);
                (++_rc_U32_631);
                U32 hoisted__U32_633 = 16;
                U32 hoisted__U32_634 = ((U32)(i * hoisted__U32_633));
                Str *hoisted__Str_635 = ((void *)((U8 *)(self->data) + (hoisted__U32_634)));
                Bool hoisted__Bool_636 = 0;
                Str_delete(hoisted__Str_635, hoisted__Bool_636);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_637 = ((Bool)(_rc_U32_631 > _re_U32_631));
                if (_wcond_Bool_637) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_631);
                (--_rc_U32_631);
                U32 hoisted__U32_638 = 16;
                U32 hoisted__U32_639 = ((U32)(i * hoisted__U32_638));
                Str *hoisted__Str_640 = ((void *)((U8 *)(self->data) + (hoisted__U32_639)));
                Bool hoisted__Bool_641 = 0;
                Str_delete(hoisted__Str_640, hoisted__Bool_641);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_657 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_657)));
    {
        U32 _re_U32_643 = self->cap;
        U32 _rc_U32_643 = 0;
        Bool hoisted__Bool_656 = ((Bool)(_rc_U32_643 <= _re_U32_643));
        if (hoisted__Bool_656) {
            while (1) {
                Bool _wcond_Bool_644 = ((Bool)(_rc_U32_643 < _re_U32_643));
                if (_wcond_Bool_644) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_643);
                (++_rc_U32_643);
                U32 hoisted__U32_645 = 16;
                U32 hoisted__U32_646 = ((U32)(i * hoisted__U32_645));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_646)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_647 = 16;
                U32 hoisted__U32_648 = ((U32)(i * hoisted__U32_647));
                void *hoisted__v_649 = ((void *)((U8 *)(new_data) + (hoisted__U32_648)));
                adopt__Str(hoisted__v_649, cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_650 = ((Bool)(_rc_U32_643 > _re_U32_643));
                if (_wcond_Bool_650) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_643);
                (--_rc_U32_643);
                U32 hoisted__U32_651 = 16;
                U32 hoisted__U32_652 = ((U32)(i * hoisted__U32_651));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_652)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_653 = 16;
                U32 hoisted__U32_654 = ((U32)(i * hoisted__U32_653));
                void *hoisted__v_655 = ((void *)((U8 *)(new_data) + (hoisted__U32_654)));
                adopt__Str(hoisted__v_655, cloned);
            }
        }
    }
    Array__Str *hoisted__Array__Str_658 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_658->data = new_data;
    hoisted__Array__Str_658->cap = self->cap;
    return hoisted__Array__Str_658;
    __builtin_unreachable();
}

USize Array__Str_size(void) {
    U32 hoisted__U32_659 = 16;
    return hoisted__U32_659;
    __builtin_unreachable();
}

void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_940 = 16;
    memcpy(dest, src, hoisted__U32_940);
    if ((src)->cap != TIL_CAP_LIT) { free(src); };
}

USize Dynamic_size(void) {
    U32 hoisted__U32_943 = 8;
    return hoisted__U32_943;
    __builtin_unreachable();
}

USize U8_size(void) {
    U32 hoisted__U32_1051 = 1;
    return hoisted__U32_1051;
    __builtin_unreachable();
}

USize U32_size(void) {
    U32 hoisted__U32_1205 = 4;
    return hoisted__U32_1205;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1274 = U64_to_str_ext(val);
    return hoisted__Str_1274;
    __builtin_unreachable();
}

USize U64_size(void) {
    U32 hoisted__U32_1279 = 8;
    return hoisted__U32_1279;
    __builtin_unreachable();
}

USize I8_size(void) {
    U32 hoisted__U32_1364 = 1;
    return hoisted__U32_1364;
    __builtin_unreachable();
}

USize I32_size(void) {
    U32 hoisted__U32_1513 = 4;
    return hoisted__U32_1513;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1635 = 0;
    Bool hoisted__Bool_1636 = ((Bool)(val < hoisted__I64_1635));
    if (hoisted__Bool_1636) {
        U64 hoisted__U64_1627 = 0ULL;
        U64 hoisted__U64_1628 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_1627 - hoisted__U64_1628));
        U32 hoisted__U32_1629 = 2;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1629);
        I64 _va_Array_39_ek = 0;
        U32 hoisted__U32_1630 = 0;
        static Str hoisted__Str_1631 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_39, hoisted__U32_1630, &hoisted__Str_1631, &_va_Array_39_ek);
        U32 hoisted__U32_1632 = 1;
        Str *hoisted__Str_1633 = U64_to_str(mag);
        Array__Str_set(_va_Array_39, hoisted__U32_1632, hoisted__Str_1633, &_va_Array_39_ek);
        Str *hoisted__Str_1634 = format(_va_Array_39);
        return hoisted__Str_1634;
    }
    U64 hoisted__U64_1637 = (U64)(val);
    Str *hoisted__Str_1638 = U64_to_str(hoisted__U64_1637);
    return hoisted__Str_1638;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I64_size(void) {
    U32 hoisted__U32_1652 = 8;
    return hoisted__U32_1652;
    __builtin_unreachable();
}

USize F32_size(void) {
    U32 hoisted__U32_1781 = 4;
    return hoisted__U32_1781;
    __builtin_unreachable();
}

USize Bool_size(void) {
    U32 hoisted__U32_1843 = 1;
    return hoisted__U32_1843;
    __builtin_unreachable();
}

USize Primitive_size(void) {
    U32 hoisted__U32_1955 = 1;
    return hoisted__U32_1955;
    __builtin_unreachable();
}


USize Type_size(void) {
    U32 hoisted__U32_2190 = 24;
    return hoisted__U32_2190;
    __builtin_unreachable();
}


__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_5793 = 3;
    Array__Str *_va_Array_152 = Array__Str_new(hoisted__U32_5793);
    I64 _va_Array_152_ek = 0;
    U32 hoisted__U32_5794 = 0;
    Str *hoisted__Str_5795 = Str_clone(loc);
    Array__Str_set(_va_Array_152, hoisted__U32_5794, hoisted__Str_5795, &_va_Array_152_ek);
    U32 hoisted__U32_5796 = 1;
    Array__Str_set(_va_Array_152, hoisted__U32_5796, &_til_str_lits[0], &_va_Array_152_ek);
    Array__Str *hoisted__Array__Str_5798 = Array__Str_clone(parts);
    U32 hoisted__U32_5799 = 2;
    Str *hoisted__Str_5800 = format(hoisted__Array__Str_5798);
    Array__Str_set(_va_Array_152, hoisted__U32_5799, hoisted__Str_5800, &_va_Array_152_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_152);
    I64 hoisted__I64_5801 = 1;
    exit(hoisted__I64_5801);
}

__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc) {
    USize hoisted__U32_5817 = (parts->cap);
    U32 hoisted__U32_5818 = 0;
    Bool hoisted__Bool_5819 = ((Bool)(hoisted__U32_5817 == hoisted__U32_5818));
    if (hoisted__Bool_5819) {
        U32 hoisted__U32_5808 = 1;
        Array__Str *_va_Array_154 = Array__Str_new(hoisted__U32_5808);
        I64 _va_Array_154_ek = 0;
        U32 hoisted__U32_5809 = 0;
        Array__Str_set(_va_Array_154, hoisted__U32_5809, &_til_str_lits[1], &_va_Array_154_ek);
        panic(_va_Array_154, loc);
    } else {
        U32 hoisted__U32_5811 = 2;
        Array__Str *_va_Array_155 = Array__Str_new(hoisted__U32_5811);
        I64 _va_Array_155_ek = 0;
        U32 hoisted__U32_5812 = 0;
        Array__Str_set(_va_Array_155, hoisted__U32_5812, &_til_str_lits[2], &_va_Array_155_ek);
        Array__Str *hoisted__Array__Str_5814 = Array__Str_clone(parts);
        U32 hoisted__U32_5815 = 1;
        Str *hoisted__Str_5816 = format(hoisted__Array__Str_5814);
        Array__Str_set(_va_Array_155, hoisted__U32_5815, hoisted__Str_5816, &_va_Array_155_ek);
        panic(_va_Array_155, loc);
    }
    Array__Str_delete(parts, 1);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_5823 = ((Bool)(!(cond)));
    if (hoisted__Bool_5823) {
        U32 hoisted__U32_5820 = 1;
        Array__Str *_va_Array_156 = Array__Str_new(hoisted__U32_5820);
        I64 _va_Array_156_ek = 0;
        U32 hoisted__U32_5821 = 0;
        Array__Str_set(_va_Array_156, hoisted__U32_5821, &_til_str_lits[3], &_va_Array_156_ek);
        panic(_va_Array_156, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_5831 = parts;
        U32 _fi_USize_5831 = 0;
        while (1) {
            USize hoisted__U32_5833 = (_fc_Array__Str_5831->cap);
            Bool _wcond_Bool_5832 = ((Bool)(_fi_USize_5831 < hoisted__U32_5833));
            if (_wcond_Bool_5832) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_5831->data) + (((U32)(_fi_USize_5831 * 16))))));
            U32 hoisted__U32_5834 = 1;
            U32 hoisted__U32_5835 = ((U32)(_fi_USize_5831 + hoisted__U32_5834));
            _fi_USize_5831 = hoisted__U32_5835;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

USize Range_size(void) {
    U32 hoisted__U32_5874 = 16;
    return hoisted__U32_5874;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_5888 = 3;
    assert_eq__I64(result, hoisted__I64_5888, &_til_str_lits[4]);
    Str_delete(&_til_str_lits[4], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_5896 = 15;
    assert_eq__I64(result, hoisted__I64_5896, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_5904 = 26;
    assert_eq__I64(result, hoisted__I64_5904, &_til_str_lits[6]);
    Str_delete(&_til_str_lits[6], (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&result, &_til_str_lits[7], &_til_str_lits[8]);
    Str_delete(&_til_str_lits[7], (Bool){0});
    Str_delete(&_til_str_lits[8], (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r, &_til_str_lits[7], &_til_str_lits[9]);
    Str_delete(&_til_str_lits[7], (Bool){0});
    Str_delete(&_til_str_lits[9], (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r2, &_til_str_lits[10], &_til_str_lits[11]);
    Str_delete(&_til_str_lits[10], (Bool){0});
    Str_delete(&_til_str_lits[11], (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d, &_til_str_lits[12], &_til_str_lits[13]);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lits[12], (Bool){0});
    Str_delete(&_til_str_lits[13], (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d2, &_til_str_lits[14], &_til_str_lits[15]);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lits[14], (Bool){0});
    Str_delete(&_til_str_lits[15], (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_5973 = 106;
    assert_eq__I64(d3, hoisted__I64_5973, &_til_str_lits[16]);
    Str_delete(&_til_str_lits[16], (Bool){0});
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&lola_rec, &lola_it, &_til_str_lits[19]);
    Str_delete(&_til_str_lits[19], (Bool){0});
    Str_delete(&lola_it, (Bool){0});
    Str_delete(&lola_rec, (Bool){0});
    assert_eq__Str(&lalo_rec, &lalo_it, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
    Str_delete(&lalo_it, (Bool){0});
    Str_delete(&lalo_rec, (Bool){0});
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_6466 = 8;
    assert_eq__I64(result, hoisted__I64_6466, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6470 = 1;
    assert(hoisted__Bool_6470, &_til_str_lits[22]);
    Str_delete(&_til_str_lits[22], (Bool){0});
    Bool hoisted__Bool_6474 = 1;
    assert(hoisted__Bool_6474, &_til_str_lits[23]);
    Str_delete(&_til_str_lits[23], (Bool){0});
}

void test_fold_f32(void) {
    assert_eq__Str(&_til_str_lits[24], &_til_str_lits[24], &_til_str_lits[25]);
    Str_delete(&_til_str_lits[24], (Bool){0});
    Str_delete(&_til_str_lits[24], (Bool){0});
    Str_delete(&_til_str_lits[25], (Bool){0});
    assert_eq__Str(&_til_str_lits[26], &_til_str_lits[26], &_til_str_lits[27]);
    Str_delete(&_til_str_lits[26], (Bool){0});
    Str_delete(&_til_str_lits[26], (Bool){0});
    Str_delete(&_til_str_lits[27], (Bool){0});
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize CfVec2_size(void) {
    U32 hoisted__U32_6518 = 16;
    return hoisted__U32_6518;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_6519 = 42;
    assert_eq__I64(v.x, hoisted__I64_6519, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    I64 hoisted__I64_6521 = 99;
    assert_eq__I64(v.y, hoisted__I64_6521, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6525 = 10;
    assert_eq__I64(p.x, hoisted__I64_6525, &_til_str_lits[30]);
    Str_delete(&_til_str_lits[30], (Bool){0});
    I64 hoisted__I64_6527 = 20;
    assert_eq__I64(p.y, hoisted__I64_6527, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize CfRect_size(void) {
    U32 hoisted__U32_6560 = 32;
    return hoisted__U32_6560;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_6561 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_6561, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_6563 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_6563, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_6565 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6565, &_til_str_lits[34]);
    Str_delete(&_til_str_lits[34], (Bool){0});
    I64 hoisted__I64_6567 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6567, &_til_str_lits[35]);
    Str_delete(&_til_str_lits[35], (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize CfVec3f_size(void) {
    U32 hoisted__U32_6605 = 12;
    return hoisted__U32_6605;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_6609 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_6609, &_til_str_lits[36], &_til_str_lits[37]);
    Str_delete(hoisted__Str_6609, 1);
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str *hoisted__Str_6612 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_6612, &_til_str_lits[38], &_til_str_lits[39]);
    Str_delete(hoisted__Str_6612, 1);
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str *hoisted__Str_6615 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_6615, &_til_str_lits[40], &_til_str_lits[41]);
    Str_delete(hoisted__Str_6615, 1);
    Str_delete(&_til_str_lits[40], (Bool){0});
    Str_delete(&_til_str_lits[41], (Bool){0});
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
    Bool hoisted__Bool_6618 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_6618;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_6645 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_6645) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
        return _r; }
    }
    Bool hoisted__Bool_6646 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_6646) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
        return _r; }
    }
    Bool hoisted__Bool_6647 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_6647) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
        return _r; }
    }
    U32 hoisted__U32_6648 = 0;
    Array__Str *_va_Array_191 = Array__Str_new(hoisted__U32_6648);
    I64 _va_Array_191_ek = 0;
    (void)_va_Array_191_ek;
    static Str hoisted__Str_6649 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(_va_Array_191, &hoisted__Str_6649);
    Str_delete(&hoisted__Str_6649, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

USize Color_size(void) {
    U32 hoisted__U32_6650 = 1;
    return hoisted__U32_6650;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_6665 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_6665, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
    Bool hoisted__Bool_6667 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_6668 = ((Bool)(!(hoisted__Bool_6667)));
    assert(hoisted__Bool_6668, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
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
    Bool hoisted__Bool_6687 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_6687) {
        I64 *hoisted__I64_6683 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6684 = 0;
        I64_delete(hoisted__I64_6683, hoisted__Bool_6684);
    }
    Bool hoisted__Bool_6688 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_6688) {
        Str *hoisted__Str_6685 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6686 = 0;
        Str_delete(hoisted__Str_6685, hoisted__Bool_6686);
    }
    if (call_free) {
        free(self);
    }
}

USize Token_size(void) {
    U32 hoisted__U32_6734 = 24;
    return hoisted__U32_6734;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_6750 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_6750, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Bool hoisted__Bool_6752 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_6753 = ((Bool)(!(hoisted__Bool_6752)));
    assert(hoisted__Bool_6753, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_6755 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_6755, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
    Bool hoisted__Bool_6757 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_6758 = ((Bool)(!(hoisted__Bool_6757)));
    assert(hoisted__Bool_6758, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_6762 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_6762, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Bool hoisted__Bool_6764 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_6765 = ((Bool)(!(hoisted__Bool_6764)));
    assert(hoisted__Bool_6765, &_til_str_lits[49]);
    Str_delete(&_til_str_lits[49], (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_6827 = ((Bool)(a != b));
    if (hoisted__Bool_6827) {
        U32 hoisted__U32_6816 = 5;
        Array__Str *_va_Array_194 = Array__Str_new(hoisted__U32_6816);
        I64 _va_Array_194_ek = 0;
        U32 hoisted__U32_6817 = 0;
        Array__Str_set(_va_Array_194, hoisted__U32_6817, &_til_str_lits[50], &_va_Array_194_ek);
        U32 hoisted__U32_6819 = 1;
        Str *hoisted__Str_6820 = I64_to_str(a);
        Array__Str_set(_va_Array_194, hoisted__U32_6819, hoisted__Str_6820, &_va_Array_194_ek);
        U32 hoisted__U32_6821 = 2;
        Array__Str_set(_va_Array_194, hoisted__U32_6821, &_til_str_lits[51], &_va_Array_194_ek);
        U32 hoisted__U32_6823 = 3;
        Str *hoisted__Str_6824 = I64_to_str(b);
        Array__Str_set(_va_Array_194, hoisted__U32_6823, hoisted__Str_6824, &_va_Array_194_ek);
        U32 hoisted__U32_6825 = 4;
        Array__Str_set(_va_Array_194, hoisted__U32_6825, &_til_str_lits[52], &_va_Array_194_ek);
        panic(_va_Array_194, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_6839 = Str_neq(a, b);
    if (hoisted__Bool_6839) {
        U32 hoisted__U32_6828 = 5;
        Array__Str *_va_Array_195 = Array__Str_new(hoisted__U32_6828);
        I64 _va_Array_195_ek = 0;
        U32 hoisted__U32_6829 = 0;
        Array__Str_set(_va_Array_195, hoisted__U32_6829, &_til_str_lits[50], &_va_Array_195_ek);
        U32 hoisted__U32_6831 = 1;
        Str *hoisted__Str_6832 = Str_to_str(a);
        Array__Str_set(_va_Array_195, hoisted__U32_6831, hoisted__Str_6832, &_va_Array_195_ek);
        U32 hoisted__U32_6833 = 2;
        Array__Str_set(_va_Array_195, hoisted__U32_6833, &_til_str_lits[51], &_va_Array_195_ek);
        U32 hoisted__U32_6835 = 3;
        Str *hoisted__Str_6836 = Str_to_str(b);
        Array__Str_set(_va_Array_195, hoisted__U32_6835, hoisted__Str_6836, &_va_Array_195_ek);
        U32 hoisted__U32_6837 = 4;
        Array__Str_set(_va_Array_195, hoisted__U32_6837, &_til_str_lits[52], &_va_Array_195_ek);
        panic(_va_Array_195, loc);
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
