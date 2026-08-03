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
Bool Str_neq(Str * a, Str * b);
Array__Str * Array__Str_new(USize cap);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
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
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
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
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
void CfRect_delete(CfRect * self, Bool call_free);
void test_struct_fold_nested(void);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
void test_enum_fold(void);
void Token_delete(Token * self, Bool call_free);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
void assert_eq__I64(I64 a, I64 b, Str * loc);
void assert_eq__Str(Str * a, Str * b, Str * loc);
Bool Color_eq(Color *, Color *);
Token *Token_Num(I64 *);
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
Bool Str_neq(Str * a, Str * b);
Array__Str * Array__Str_new(USize cap);
void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
void Array__Str_delete(Array__Str * self, Bool call_free);
Array__Str * Array__Str_clone(Array__Str * self);
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
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
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
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
void CfRect_delete(CfRect * self, Bool call_free);
void test_struct_fold_nested(void);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
void test_enum_fold(void);
Token * Token_Num(I64 * val);
Bool Token_is(Token * self, Token * other);
void Token_delete(Token * self, Bool call_free);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
void assert_eq__I64(I64 a, I64 b, Str * loc);
void assert_eq__Str(Str * a, Str * b, Str * loc);
Bool Color_eq(Color *, Color *);
Token *Token_Num(I64 *);


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

U32 CAP_LIT;
U32 CAP_VIEW;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_47 = parts;
        U32 _fi_USize_47 = 0;
        while (1) {
            USize hoisted__U32_49 = (_fc_Array__Str_47->cap);
            Bool _wcond_Bool_48 = ((Bool)(_fi_USize_47 < hoisted__U32_49));
            if (_wcond_Bool_48) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_47->data) + (((U32)(_fi_USize_47 * 16))))));
            U32 hoisted__U32_50 = 1;
            U32 hoisted__U32_51 = ((U32)(_fi_USize_47 + hoisted__U32_50));
            _fi_USize_47 = hoisted__U32_51;
            USize hoisted__U32_52 = (s->count);
            U32 hoisted__U32_53 = ((U32)(total + hoisted__U32_52));
            total = hoisted__U32_53;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_54 = parts;
        U32 _fi_USize_54 = 0;
        while (1) {
            USize hoisted__U32_56 = (_fc_Array__Str_54->cap);
            Bool _wcond_Bool_55 = ((Bool)(_fi_USize_54 < hoisted__U32_56));
            if (_wcond_Bool_55) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_54->data) + (((U32)(_fi_USize_54 * 16))))));
            U32 hoisted__U32_57 = 1;
            U32 hoisted__U32_58 = ((U32)(_fi_USize_54 + hoisted__U32_57));
            _fi_USize_54 = hoisted__U32_58;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_85 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_85) {
        Bool hoisted__Bool_83 = 0;
        return hoisted__Bool_83;
    }
    Bool hoisted__Bool_86 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_86) {
        Bool hoisted__Bool_84 = 1;
        return hoisted__Bool_84;
    }
    I32 hoisted__I32_87 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_88 = 0;
    Bool hoisted__Bool_89 = ((Bool)(hoisted__I32_87 == hoisted__I32_88));
    return hoisted__Bool_89;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_91 = 0;
    Bool hoisted__Bool_92 = ((Bool)(n == hoisted__U32_91));
    if (hoisted__Bool_92) {
        static Str hoisted__Str_90 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_90; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_93 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_93)));
    I32 hoisted__I32_94 = 0;
    U64 hoisted__U64_95 = 1ULL;
    memset(buf, hoisted__I32_94, hoisted__U64_95);
    I64 hoisted__I64_96 = 0;
    Str *hoisted__Str_97 = malloc(sizeof(Str));
    hoisted__Str_97->c_str = buf;
    hoisted__Str_97->count = hoisted__I64_96;
    hoisted__Str_97->cap = n;
    return hoisted__Str_97;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_108 = 0;
    Bool hoisted__Bool_109 = ((Bool)(s->count == hoisted__U32_108));
    if (hoisted__Bool_109) {
        return;
    }
    Bool hoisted__Bool_110 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_110) {
        U32 hoisted__U32_100 = 1;
        Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_100);
        I64 _va_Array_1_ek = 0;
        U32 hoisted__U32_101 = 0;
        static Str hoisted__Str_102 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_1, hoisted__U32_101, &hoisted__Str_102, &_va_Array_1_ek);
        static Str hoisted__Str_103 = (Str){.c_str = (void *)"./src/core/str.til:124:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_1, &hoisted__Str_103);
        Str_delete(&hoisted__Str_103, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_111 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_111) {
        U32 hoisted__U32_104 = 1;
        Array__Str *_va_Array_2 = Array__Str_new(hoisted__U32_104);
        I64 _va_Array_2_ek = 0;
        U32 hoisted__U32_105 = 0;
        static Str hoisted__Str_106 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_2, hoisted__U32_105, &hoisted__Str_106, &_va_Array_2_ek);
        static Str hoisted__Str_107 = (Str){.c_str = (void *)"./src/core/str.til:128:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_2, &hoisted__Str_107);
        Str_delete(&hoisted__Str_107, (Bool){0});
    }
    void *hoisted__v_112 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_112, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_113 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_114 = 0;
    U64 hoisted__U64_115 = 1ULL;
    memset(hoisted__v_113, hoisted__I32_114, hoisted__U64_115);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_117 = 0;
    Bool hoisted__Bool_118 = ((Bool)(val->count == hoisted__U32_117));
    if (hoisted__Bool_118) {
        static Str hoisted__Str_116 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_116; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_119 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_119)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_120 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_121 = 0;
    U64 hoisted__U64_122 = 1ULL;
    memset(hoisted__v_120, hoisted__I32_121, hoisted__U64_122);
    Str *hoisted__Str_123 = malloc(sizeof(Str));
    hoisted__Str_123->c_str = new_data;
    hoisted__Str_123->count = val->count;
    hoisted__Str_123->cap = val->count;
    return hoisted__Str_123;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_124 = Str_clone(self);
    return hoisted__Str_124;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_125 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_125) {
        free(self->c_str);
    }
    Bool hoisted__Bool_126 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_127 = ((Bool)((call_free) && (hoisted__Bool_126)));
    if (hoisted__Bool_127) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_504 = Str_eq(a, b);
    Bool hoisted__Bool_505 = ((Bool)(!(hoisted__Bool_504)));
    return hoisted__Bool_505;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_642 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_643 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_643->data = hoisted__v_642;
    hoisted__Array__Str_643->cap = cap;
    return hoisted__Array__Str_643;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_652 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Bool hoisted__Bool_653 = 0;
    Str_delete(hoisted__Str_652, hoisted__Bool_653);
    Str *hoisted__Str_654 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    adopt__Str(hoisted__Str_654, val);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_656 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_656) {
        I64 hoisted__I64_655 = 1;
        *_err_kind = hoisted__I64_655;
    }
    I64 hoisted__I64_657 = 0;
    Bool hoisted__Bool_658 = ((Bool)(DEREF(_err_kind) == hoisted__I64_657));
    if (hoisted__Bool_658) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_659 = self->cap;
        U32 _rc_U32_659 = 0;
        Bool hoisted__Bool_670 = ((Bool)(_rc_U32_659 <= _re_U32_659));
        if (hoisted__Bool_670) {
            while (1) {
                Bool _wcond_Bool_660 = ((Bool)(_rc_U32_659 < _re_U32_659));
                if (_wcond_Bool_660) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_659);
                (++_rc_U32_659);
                U32 hoisted__U32_661 = 16;
                U32 hoisted__U32_662 = ((U32)(i * hoisted__U32_661));
                Str *hoisted__Str_663 = ((void *)((U8 *)(self->data) + (hoisted__U32_662)));
                Bool hoisted__Bool_664 = 0;
                Str_delete(hoisted__Str_663, hoisted__Bool_664);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_665 = ((Bool)(_rc_U32_659 > _re_U32_659));
                if (_wcond_Bool_665) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_659);
                (--_rc_U32_659);
                U32 hoisted__U32_666 = 16;
                U32 hoisted__U32_667 = ((U32)(i * hoisted__U32_666));
                Str *hoisted__Str_668 = ((void *)((U8 *)(self->data) + (hoisted__U32_667)));
                Bool hoisted__Bool_669 = 0;
                Str_delete(hoisted__Str_668, hoisted__Bool_669);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_685 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_685)));
    {
        U32 _re_U32_671 = self->cap;
        U32 _rc_U32_671 = 0;
        Bool hoisted__Bool_684 = ((Bool)(_rc_U32_671 <= _re_U32_671));
        if (hoisted__Bool_684) {
            while (1) {
                Bool _wcond_Bool_672 = ((Bool)(_rc_U32_671 < _re_U32_671));
                if (_wcond_Bool_672) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_671);
                (++_rc_U32_671);
                U32 hoisted__U32_673 = 16;
                U32 hoisted__U32_674 = ((U32)(i * hoisted__U32_673));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_674)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_675 = 16;
                U32 hoisted__U32_676 = ((U32)(i * hoisted__U32_675));
                void *hoisted__v_677 = ((void *)((U8 *)(new_data) + (hoisted__U32_676)));
                adopt__Str(hoisted__v_677, cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_678 = ((Bool)(_rc_U32_671 > _re_U32_671));
                if (_wcond_Bool_678) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_671);
                (--_rc_U32_671);
                U32 hoisted__U32_679 = 16;
                U32 hoisted__U32_680 = ((U32)(i * hoisted__U32_679));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_680)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_681 = 16;
                U32 hoisted__U32_682 = ((U32)(i * hoisted__U32_681));
                void *hoisted__v_683 = ((void *)((U8 *)(new_data) + (hoisted__U32_682)));
                adopt__Str(hoisted__v_683, cloned);
            }
        }
    }
    Array__Str *hoisted__Array__Str_686 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_686->data = new_data;
    hoisted__Array__Str_686->cap = self->cap;
    return hoisted__Array__Str_686;
    __builtin_unreachable();
}

void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_965 = 16;
    memcpy(dest, src, hoisted__U32_965);
    if ((src)->cap != TIL_CAP_LIT) { free(src); };
}

USize Dynamic_size(void) {
    U32 hoisted__U32_968 = 8;
    return hoisted__U32_968;
    __builtin_unreachable();
}

USize U8_size(void) {
    U32 hoisted__U32_1078 = 1;
    return hoisted__U32_1078;
    __builtin_unreachable();
}

USize U32_size(void) {
    U32 hoisted__U32_1232 = 4;
    return hoisted__U32_1232;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1301 = U64_to_str_ext(val);
    return hoisted__Str_1301;
    __builtin_unreachable();
}

USize U64_size(void) {
    U32 hoisted__U32_1306 = 8;
    return hoisted__U32_1306;
    __builtin_unreachable();
}

USize I8_size(void) {
    U32 hoisted__U32_1391 = 1;
    return hoisted__U32_1391;
    __builtin_unreachable();
}

USize I32_size(void) {
    U32 hoisted__U32_1540 = 4;
    return hoisted__U32_1540;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1662 = 0;
    Bool hoisted__Bool_1663 = ((Bool)(val < hoisted__I64_1662));
    if (hoisted__Bool_1663) {
        U64 hoisted__U64_1654 = 0ULL;
        U64 hoisted__U64_1655 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_1654 - hoisted__U64_1655));
        U32 hoisted__U32_1656 = 2;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1656);
        I64 _va_Array_39_ek = 0;
        U32 hoisted__U32_1657 = 0;
        static Str hoisted__Str_1658 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_39, hoisted__U32_1657, &hoisted__Str_1658, &_va_Array_39_ek);
        U32 hoisted__U32_1659 = 1;
        Str *hoisted__Str_1660 = U64_to_str(mag);
        Array__Str_set(_va_Array_39, hoisted__U32_1659, hoisted__Str_1660, &_va_Array_39_ek);
        Str *hoisted__Str_1661 = format(_va_Array_39);
        return hoisted__Str_1661;
    }
    U64 hoisted__U64_1664 = (U64)(val);
    Str *hoisted__Str_1665 = U64_to_str(hoisted__U64_1664);
    return hoisted__Str_1665;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I64_size(void) {
    U32 hoisted__U32_1679 = 8;
    return hoisted__U32_1679;
    __builtin_unreachable();
}

USize F32_size(void) {
    U32 hoisted__U32_1808 = 4;
    return hoisted__U32_1808;
    __builtin_unreachable();
}

USize Bool_size(void) {
    U32 hoisted__U32_1902 = 1;
    return hoisted__U32_1902;
    __builtin_unreachable();
}



__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_5952 = 3;
    Array__Str *_va_Array_159 = Array__Str_new(hoisted__U32_5952);
    I64 _va_Array_159_ek = 0;
    U32 hoisted__U32_5953 = 0;
    Str *hoisted__Str_5954 = Str_clone(loc);
    Array__Str_set(_va_Array_159, hoisted__U32_5953, hoisted__Str_5954, &_va_Array_159_ek);
    U32 hoisted__U32_5955 = 1;
    Array__Str_set(_va_Array_159, hoisted__U32_5955, &_til_str_lits[0], &_va_Array_159_ek);
    Array__Str *hoisted__Array__Str_5957 = Array__Str_clone(parts);
    U32 hoisted__U32_5958 = 2;
    Str *hoisted__Str_5959 = format(hoisted__Array__Str_5957);
    Array__Str_set(_va_Array_159, hoisted__U32_5958, hoisted__Str_5959, &_va_Array_159_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_159);
    I64 hoisted__I64_5960 = 1;
    exit(hoisted__I64_5960);
}

__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc) {
    USize hoisted__U32_5976 = (parts->cap);
    U32 hoisted__U32_5977 = 0;
    Bool hoisted__Bool_5978 = ((Bool)(hoisted__U32_5976 == hoisted__U32_5977));
    if (hoisted__Bool_5978) {
        U32 hoisted__U32_5967 = 1;
        Array__Str *_va_Array_161 = Array__Str_new(hoisted__U32_5967);
        I64 _va_Array_161_ek = 0;
        U32 hoisted__U32_5968 = 0;
        Array__Str_set(_va_Array_161, hoisted__U32_5968, &_til_str_lits[1], &_va_Array_161_ek);
        panic(_va_Array_161, loc);
    } else {
        U32 hoisted__U32_5970 = 2;
        Array__Str *_va_Array_162 = Array__Str_new(hoisted__U32_5970);
        I64 _va_Array_162_ek = 0;
        U32 hoisted__U32_5971 = 0;
        Array__Str_set(_va_Array_162, hoisted__U32_5971, &_til_str_lits[2], &_va_Array_162_ek);
        Array__Str *hoisted__Array__Str_5973 = Array__Str_clone(parts);
        U32 hoisted__U32_5974 = 1;
        Str *hoisted__Str_5975 = format(hoisted__Array__Str_5973);
        Array__Str_set(_va_Array_162, hoisted__U32_5974, hoisted__Str_5975, &_va_Array_162_ek);
        panic(_va_Array_162, loc);
    }
    Array__Str_delete(parts, 1);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_5982 = ((Bool)(!(cond)));
    if (hoisted__Bool_5982) {
        U32 hoisted__U32_5979 = 1;
        Array__Str *_va_Array_163 = Array__Str_new(hoisted__U32_5979);
        I64 _va_Array_163_ek = 0;
        U32 hoisted__U32_5980 = 0;
        Array__Str_set(_va_Array_163, hoisted__U32_5980, &_til_str_lits[3], &_va_Array_163_ek);
        panic(_va_Array_163, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_5990 = parts;
        U32 _fi_USize_5990 = 0;
        while (1) {
            USize hoisted__U32_5992 = (_fc_Array__Str_5990->cap);
            Bool _wcond_Bool_5991 = ((Bool)(_fi_USize_5990 < hoisted__U32_5992));
            if (_wcond_Bool_5991) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_5990->data) + (((U32)(_fi_USize_5990 * 16))))));
            U32 hoisted__U32_5993 = 1;
            U32 hoisted__U32_5994 = ((U32)(_fi_USize_5990 + hoisted__U32_5993));
            _fi_USize_5990 = hoisted__U32_5994;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6062 = 3;
    assert_eq__I64(result, hoisted__I64_6062, &_til_str_lits[4]);
    Str_delete(&_til_str_lits[4], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6070 = 15;
    assert_eq__I64(result, hoisted__I64_6070, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6078 = 26;
    assert_eq__I64(result, hoisted__I64_6078, &_til_str_lits[6]);
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
    I64 hoisted__I64_6147 = 106;
    assert_eq__I64(d3, hoisted__I64_6147, &_til_str_lits[16]);
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
    I64 hoisted__I64_6640 = 8;
    assert_eq__I64(result, hoisted__I64_6640, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6644 = 1;
    assert(hoisted__Bool_6644, &_til_str_lits[22]);
    Str_delete(&_til_str_lits[22], (Bool){0});
    Bool hoisted__Bool_6648 = 1;
    assert(hoisted__Bool_6648, &_til_str_lits[23]);
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

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_6708 = 42;
    assert_eq__I64(v.x, hoisted__I64_6708, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    I64 hoisted__I64_6710 = 99;
    assert_eq__I64(v.y, hoisted__I64_6710, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6714 = 10;
    assert_eq__I64(p.x, hoisted__I64_6714, &_til_str_lits[30]);
    Str_delete(&_til_str_lits[30], (Bool){0});
    I64 hoisted__I64_6716 = 20;
    assert_eq__I64(p.y, hoisted__I64_6716, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_6765 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_6765, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_6767 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_6767, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_6769 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6769, &_til_str_lits[34]);
    Str_delete(&_til_str_lits[34], (Bool){0});
    I64 hoisted__I64_6771 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6771, &_til_str_lits[35]);
    Str_delete(&_til_str_lits[35], (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_6827 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_6827, &_til_str_lits[36], &_til_str_lits[37]);
    Str_delete(hoisted__Str_6827, 1);
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str *hoisted__Str_6830 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_6830, &_til_str_lits[38], &_til_str_lits[39]);
    Str_delete(hoisted__Str_6830, 1);
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str *hoisted__Str_6833 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_6833, &_til_str_lits[40], &_til_str_lits[41]);
    Str_delete(hoisted__Str_6833, 1);
    Str_delete(&_til_str_lits[40], (Bool){0});
    Str_delete(&_til_str_lits[41], (Bool){0});
    CfVec3f_delete(&v, (Bool){0});
}

Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_6836 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_6836;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_6863 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_6863) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
        return _r; }
    }
    Bool hoisted__Bool_6864 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_6864) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
        return _r; }
    }
    Bool hoisted__Bool_6865 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_6865) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
        return _r; }
    }
    U32 hoisted__U32_6866 = 0;
    Array__Str *_va_Array_198 = Array__Str_new(hoisted__U32_6866);
    I64 _va_Array_198_ek = 0;
    (void)_va_Array_198_ek;
    static Str hoisted__Str_6867 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(_va_Array_198, &hoisted__Str_6867);
    Str_delete(&hoisted__Str_6867, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_6883 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_6883, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
    Bool hoisted__Bool_6885 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_6886 = ((Bool)(!(hoisted__Bool_6885)));
    assert(hoisted__Bool_6886, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_6905 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_6905) {
        I64 *hoisted__I64_6901 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6902 = 0;
        I64_delete(hoisted__I64_6901, hoisted__Bool_6902);
    }
    Bool hoisted__Bool_6906 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_6906) {
        Str *hoisted__Str_6903 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6904 = 0;
        Str_delete(hoisted__Str_6903, hoisted__Bool_6904);
    }
    if (call_free) {
        free(self);
    }
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_6968 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_6968, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Bool hoisted__Bool_6970 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_6971 = ((Bool)(!(hoisted__Bool_6970)));
    assert(hoisted__Bool_6971, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_6973 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_6973, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
    Bool hoisted__Bool_6975 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_6976 = ((Bool)(!(hoisted__Bool_6975)));
    assert(hoisted__Bool_6976, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_6980 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_6980, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Bool hoisted__Bool_6982 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_6983 = ((Bool)(!(hoisted__Bool_6982)));
    assert(hoisted__Bool_6983, &_til_str_lits[49]);
    Str_delete(&_til_str_lits[49], (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7042 = ((Bool)(a != b));
    if (hoisted__Bool_7042) {
        U32 hoisted__U32_7031 = 5;
        Array__Str *_va_Array_201 = Array__Str_new(hoisted__U32_7031);
        I64 _va_Array_201_ek = 0;
        U32 hoisted__U32_7032 = 0;
        Array__Str_set(_va_Array_201, hoisted__U32_7032, &_til_str_lits[50], &_va_Array_201_ek);
        U32 hoisted__U32_7034 = 1;
        Str *hoisted__Str_7035 = I64_to_str(a);
        Array__Str_set(_va_Array_201, hoisted__U32_7034, hoisted__Str_7035, &_va_Array_201_ek);
        U32 hoisted__U32_7036 = 2;
        Array__Str_set(_va_Array_201, hoisted__U32_7036, &_til_str_lits[51], &_va_Array_201_ek);
        U32 hoisted__U32_7038 = 3;
        Str *hoisted__Str_7039 = I64_to_str(b);
        Array__Str_set(_va_Array_201, hoisted__U32_7038, hoisted__Str_7039, &_va_Array_201_ek);
        U32 hoisted__U32_7040 = 4;
        Array__Str_set(_va_Array_201, hoisted__U32_7040, &_til_str_lits[52], &_va_Array_201_ek);
        panic(_va_Array_201, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7054 = Str_neq(a, b);
    if (hoisted__Bool_7054) {
        U32 hoisted__U32_7043 = 5;
        Array__Str *_va_Array_202 = Array__Str_new(hoisted__U32_7043);
        I64 _va_Array_202_ek = 0;
        U32 hoisted__U32_7044 = 0;
        Array__Str_set(_va_Array_202, hoisted__U32_7044, &_til_str_lits[50], &_va_Array_202_ek);
        U32 hoisted__U32_7046 = 1;
        Str *hoisted__Str_7047 = Str_to_str(a);
        Array__Str_set(_va_Array_202, hoisted__U32_7046, hoisted__Str_7047, &_va_Array_202_ek);
        U32 hoisted__U32_7048 = 2;
        Array__Str_set(_va_Array_202, hoisted__U32_7048, &_til_str_lits[51], &_va_Array_202_ek);
        U32 hoisted__U32_7050 = 3;
        Str *hoisted__Str_7051 = Str_to_str(b);
        Array__Str_set(_va_Array_202, hoisted__U32_7050, hoisted__Str_7051, &_va_Array_202_ek);
        U32 hoisted__U32_7052 = 4;
        Array__Str_set(_va_Array_202, hoisted__U32_7052, &_til_str_lits[52], &_va_Array_202_ek);
        panic(_va_Array_202, loc);
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
