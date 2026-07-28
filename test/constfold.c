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

typedef TilClosure *HashFn;

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
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(USize n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
USize Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * _self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
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
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
USize U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
USize U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
USize U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
USize I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
USize I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
USize I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
USize F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
USize Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
USize Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
USize Type_size(void);
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
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
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool call_free);
U64 CfVec2_hash(CfVec2 * self, HashFn hasher);
USize CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
USize CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
USize CfVec3f_size(void);
void test_struct_fold_f32(void);
Bool Color_eq(Color * self, Color * other);
void Color_delete(Color * self, Bool call_free);
Color * Color_clone(Color * self);
USize Color_size(void);
void test_enum_fold(void);
void Token_delete(Token * self, Bool call_free);
Token * Token_clone(Token * self);
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
I64 Str_cmp(Str * a, Str * b);
Bool Str_eq(Str * a, Str * b);
Str * Str_with_capacity(USize n);
void Str_push_str(Str * self, Str * s);
Str * Str_clone(Str * val);
Str * Str_to_str(Str * self);
void Str_delete(Str * self, Bool call_free);
U64 Str_hash(Str * self, HashFn hasher);
USize Str_size(void);
Bool Str_neq(Str * a, Str * b);
OutOfBounds * OutOfBounds_clone(OutOfBounds * _self);
void OutOfBounds_delete(OutOfBounds * self, Bool call_free);
U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher);
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
void * Dynamic_clone(void * self);
void Dynamic_delete(void * self, Bool call_free);
void U8_delete(U8 * self, Bool call_free);
USize U8_size(void);
U64 U8_hash(U8 self, HashFn hasher);
void U32_delete(U32 * self, Bool call_free);
USize U32_size(void);
U64 U32_hash(U32 self, HashFn hasher);
Str * U64_to_str(U64 val);
void U64_delete(U64 * self, Bool call_free);
USize U64_size(void);
U64 U64_hash(U64 self, HashFn hasher);
void I8_delete(I8 * self, Bool call_free);
USize I8_size(void);
U64 I8_hash(I8 self, HashFn hasher);
void I32_delete(I32 * self, Bool call_free);
USize I32_size(void);
U64 I32_hash(I32 self, HashFn hasher);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
USize I64_size(void);
U64 I64_hash(I64 self, HashFn hasher);
void F32_delete(F32 * self, Bool call_free);
USize F32_size(void);
U64 F32_hash(F32 self, HashFn hasher);
I64 Bool_cmp(Bool a, Bool b);
void Bool_delete(Bool * self, Bool call_free);
USize Bool_size(void);
U64 Bool_hash(Bool self, HashFn hasher);
Bool Primitive_eq(Primitive * self, Primitive * other);
void Primitive_delete(Primitive * self, Bool call_free);
Primitive * Primitive_clone(Primitive * self);
USize Primitive_size(void);
void Type_delete(Type * self, Bool call_free);
Type * Type_clone(Type * self);
USize Type_size(void);
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Str * loc);
void assert(Bool cond, Str * loc);
void println(Array__Str * parts);
Range * Range_clone(Range * val);
void Range_delete(Range * self, Bool call_free);
U64 Range_hash(Range * self, HashFn hasher);
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
CfVec2 * CfVec2_clone(CfVec2 * self);
void CfVec2_delete(CfVec2 * self, Bool call_free);
U64 CfVec2_hash(CfVec2 * self, HashFn hasher);
USize CfVec2_size(void);
void test_struct_fold_simple(void);
void test_struct_fold_values(void);
CfRect * CfRect_clone(CfRect * self);
void CfRect_delete(CfRect * self, Bool call_free);
U64 CfRect_hash(CfRect * self, HashFn hasher);
USize CfRect_size(void);
void test_struct_fold_nested(void);
CfVec3f * CfVec3f_clone(CfVec3f * self);
void CfVec3f_delete(CfVec3f * self, Bool call_free);
U64 CfVec3f_hash(CfVec3f * self, HashFn hasher);
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
Token * Token_clone(Token * self);
USize Token_size(void);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
void assert_eq__I64(I64 a, I64 b, Str * loc);
void assert_eq__Str(Str * a, Str * b, Str * loc);
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

I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_81 = ((Bool)(b->count < a->count));
    if (hoisted__Bool_81) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_82 = 0;
    Bool hoisted__Bool_83 = ((Bool)(c < hoisted__I32_82));
    if (hoisted__Bool_83) {
        I64 hoisted__I64_79 = -1;
        return hoisted__I64_79;
    }
    I32 hoisted__I32_84 = 0;
    Bool hoisted__Bool_85 = ((Bool)(c > hoisted__I32_84));
    if (hoisted__Bool_85) {
        I64 hoisted__I64_80 = 1;
        return hoisted__I64_80;
    }
    I64 hoisted__I64_86 = U32_cmp(a->count, b->count);
    return hoisted__I64_86;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_89 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_89) {
        Bool hoisted__Bool_87 = 0;
        return hoisted__Bool_87;
    }
    Bool hoisted__Bool_90 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_90) {
        Bool hoisted__Bool_88 = 1;
        return hoisted__Bool_88;
    }
    I32 hoisted__I32_91 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_92 = 0;
    Bool hoisted__Bool_93 = ((Bool)(hoisted__I32_91 == hoisted__I32_92));
    return hoisted__Bool_93;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_95 = 0;
    Bool hoisted__Bool_96 = ((Bool)(n == hoisted__U32_95));
    if (hoisted__Bool_96) {
        static Str hoisted__Str_94 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_94; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_97 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_97)));
    I32 hoisted__I32_98 = 0;
    U64 hoisted__U64_99 = 1ULL;
    memset(buf, hoisted__I32_98, hoisted__U64_99);
    I64 hoisted__I64_100 = 0;
    Str *hoisted__Str_101 = malloc(sizeof(Str));
    hoisted__Str_101->c_str = buf;
    hoisted__Str_101->count = hoisted__I64_100;
    hoisted__Str_101->cap = n;
    return hoisted__Str_101;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_112 = 0;
    Bool hoisted__Bool_113 = ((Bool)(s->count == hoisted__U32_112));
    if (hoisted__Bool_113) {
        return;
    }
    Bool hoisted__Bool_114 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_114) {
        U32 hoisted__U32_104 = 1;
        Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_104);
        (void)_va_Array_1;
        I64 _va_Array_1_ek = 0;
        (void)_va_Array_1_ek;
        U32 hoisted__U32_105 = 0;
        static Str hoisted__Str_106 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_1, hoisted__U32_105, &hoisted__Str_106, &_va_Array_1_ek);
        static Str hoisted__Str_107 = (Str){.c_str = (void *)"./src/core/str.til:118:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_1, &hoisted__Str_107);
        Str_delete(&hoisted__Str_107, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_115 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_115) {
        U32 hoisted__U32_108 = 1;
        Array__Str *_va_Array_2 = Array__Str_new(hoisted__U32_108);
        (void)_va_Array_2;
        I64 _va_Array_2_ek = 0;
        (void)_va_Array_2_ek;
        U32 hoisted__U32_109 = 0;
        static Str hoisted__Str_110 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_2, hoisted__U32_109, &hoisted__Str_110, &_va_Array_2_ek);
        static Str hoisted__Str_111 = (Str){.c_str = (void *)"./src/core/str.til:122:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_2, &hoisted__Str_111);
        Str_delete(&hoisted__Str_111, (Bool){0});
    }
    void *hoisted__v_116 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_116, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_117 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_118 = 0;
    U64 hoisted__U64_119 = 1ULL;
    memset(hoisted__v_117, hoisted__I32_118, hoisted__U64_119);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_121 = 0;
    Bool hoisted__Bool_122 = ((Bool)(val->count == hoisted__U32_121));
    if (hoisted__Bool_122) {
        static Str hoisted__Str_120 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_120; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_123 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_123)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_124 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_125 = 0;
    U64 hoisted__U64_126 = 1ULL;
    memset(hoisted__v_124, hoisted__I32_125, hoisted__U64_126);
    Str *hoisted__Str_127 = malloc(sizeof(Str));
    hoisted__Str_127->c_str = new_data;
    hoisted__Str_127->count = val->count;
    hoisted__Str_127->cap = val->count;
    return hoisted__Str_127;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_128 = Str_clone(self);
    return hoisted__Str_128;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_129 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_129) {
        free(self->c_str);
    }
    Bool hoisted__Bool_130 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_131 = ((Bool)((call_free) && (hoisted__Bool_130)));
    if (hoisted__Bool_131) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

U64 Str_hash(Str * self, HashFn hasher) {
    U64 hoisted__U64_326 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, self->c_str, self->count); });
    return hoisted__U64_326;
    __builtin_unreachable();
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

OutOfBounds * OutOfBounds_clone(OutOfBounds * _self) {
    (void)_self;
    OutOfBounds *hoisted__OutOfBounds_589 = malloc(sizeof(OutOfBounds));
    return hoisted__OutOfBounds_589;
    __builtin_unreachable();
}

void OutOfBounds_delete(OutOfBounds * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 OutOfBounds_hash(OutOfBounds * self, HashFn hasher) {
    U32 hoisted__U32_590 = 0;
    U64 hoisted__U64_591 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, OutOfBounds *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_590); });
    return hoisted__U64_591;
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

USize Array__Str_len(Array__Str * self) {
    return self->cap;
    __builtin_unreachable();
}

Str * Array__Str_unsafe_get(Array__Str * self, USize * i) {
    U32 hoisted__U32_613 = 16;
    U32 hoisted__U32_614 = ((U32)(DEREF(i) * hoisted__U32_613));
    void *hoisted__v_615 = ((void *)((U8 *)(self->data) + (hoisted__U32_614)));
    return hoisted__v_615;
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
        (void)_re_U32_631;
        U32 _rc_U32_631 = 0;
        (void)_rc_U32_631;
        Bool hoisted__Bool_642 = ((Bool)(_rc_U32_631 <= _re_U32_631));
        if (hoisted__Bool_642) {
            while (1) {
                Bool _wcond_Bool_632 = ((Bool)(_rc_U32_631 < _re_U32_631));
                (void)_wcond_Bool_632;
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
                (void)_wcond_Bool_637;
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
    U32 hoisted__U32_663 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_663)));
    {
        U32 _re_U32_643 = self->cap;
        (void)_re_U32_643;
        U32 _rc_U32_643 = 0;
        (void)_rc_U32_643;
        Bool hoisted__Bool_662 = ((Bool)(_rc_U32_643 <= _re_U32_643));
        if (hoisted__Bool_662) {
            while (1) {
                Bool _wcond_Bool_644 = ((Bool)(_rc_U32_643 < _re_U32_643));
                (void)_wcond_Bool_644;
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
                U32 hoisted__U32_650 = 16;
                memcpy(hoisted__v_649, cloned, hoisted__U32_650);
                I32 hoisted__I32_651 = 0;
                U32 hoisted__U32_652 = 16;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_651, hoisted__U32_652); };
                Str_delete(cloned, 1);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_653 = ((Bool)(_rc_U32_643 > _re_U32_643));
                (void)_wcond_Bool_653;
                if (_wcond_Bool_653) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_643);
                (--_rc_U32_643);
                U32 hoisted__U32_654 = 16;
                U32 hoisted__U32_655 = ((U32)(i * hoisted__U32_654));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_655)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_656 = 16;
                U32 hoisted__U32_657 = ((U32)(i * hoisted__U32_656));
                void *hoisted__v_658 = ((void *)((U8 *)(new_data) + (hoisted__U32_657)));
                U32 hoisted__U32_659 = 16;
                memcpy(hoisted__v_658, cloned, hoisted__U32_659);
                I32 hoisted__I32_660 = 0;
                U32 hoisted__U32_661 = 16;
                if ((cloned)->cap != TIL_CAP_LIT) { memset(cloned, hoisted__I32_660, hoisted__U32_661); };
                Str_delete(cloned, 1);
            }
        }
    }
    Array__Str *hoisted__Array__Str_664 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_664->data = new_data;
    hoisted__Array__Str_664->cap = self->cap;
    return hoisted__Array__Str_664;
    __builtin_unreachable();
}

USize Array__Str_size(void) {
    U32 hoisted__U32_665 = 16;
    return hoisted__U32_665;
    __builtin_unreachable();
}

USize Dynamic_size(void) {
    U32 hoisted__U32_957 = 8;
    return hoisted__U32_957;
    __builtin_unreachable();
}

void * Dynamic_clone(void * self) {
    U8 *out = malloc(8);
    U32 hoisted__U32_958 = 8;
    memcpy(out, self, hoisted__U32_958);
    return out;
    __builtin_unreachable();
}

void Dynamic_delete(void * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void U8_delete(U8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U8_size(void) {
    U32 hoisted__U32_1065 = 1;
    return hoisted__U32_1065;
    __builtin_unreachable();
}

U64 U8_hash(U8 self, HashFn hasher) {
    U32 hoisted__U32_1132 = 1;
    U64 hoisted__U64_1133 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1132); });
    return hoisted__U64_1133;
    __builtin_unreachable();
}

void U32_delete(U32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U32_size(void) {
    U32 hoisted__U32_1219 = 4;
    return hoisted__U32_1219;
    __builtin_unreachable();
}

U64 U32_hash(U32 self, HashFn hasher) {
    U32 hoisted__U32_1286 = 4;
    U64 hoisted__U64_1287 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1286); });
    return hoisted__U64_1287;
    __builtin_unreachable();
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1288 = U64_to_str_ext(val);
    return hoisted__Str_1288;
    __builtin_unreachable();
}

void U64_delete(U64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize U64_size(void) {
    U32 hoisted__U32_1293 = 8;
    return hoisted__U32_1293;
    __builtin_unreachable();
}

U64 U64_hash(U64 self, HashFn hasher) {
    U32 hoisted__U32_1360 = 8;
    U64 hoisted__U64_1361 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, U64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1360); });
    return hoisted__U64_1361;
    __builtin_unreachable();
}

void I8_delete(I8 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I8_size(void) {
    U32 hoisted__U32_1378 = 1;
    return hoisted__U32_1378;
    __builtin_unreachable();
}

U64 I8_hash(I8 self, HashFn hasher) {
    U32 hoisted__U32_1379 = 1;
    U64 hoisted__U64_1380 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I8 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1379); });
    return hoisted__U64_1380;
    __builtin_unreachable();
}

void I32_delete(I32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I32_size(void) {
    U32 hoisted__U32_1527 = 4;
    return hoisted__U32_1527;
    __builtin_unreachable();
}

U64 I32_hash(I32 self, HashFn hasher) {
    U32 hoisted__U32_1639 = 4;
    U64 hoisted__U64_1640 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1639); });
    return hoisted__U64_1640;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1649 = 0;
    Bool hoisted__Bool_1650 = ((Bool)(val < hoisted__I64_1649));
    if (hoisted__Bool_1650) {
        U64 hoisted__U64_1641 = 0ULL;
        U64 hoisted__U64_1642 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_1641 - hoisted__U64_1642));
        U32 hoisted__U32_1643 = 2;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1643);
        (void)_va_Array_39;
        I64 _va_Array_39_ek = 0;
        (void)_va_Array_39_ek;
        U32 hoisted__U32_1644 = 0;
        static Str hoisted__Str_1645 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_39, hoisted__U32_1644, &hoisted__Str_1645, &_va_Array_39_ek);
        U32 hoisted__U32_1646 = 1;
        Str *hoisted__Str_1647 = U64_to_str(mag);
        Array__Str_set(_va_Array_39, hoisted__U32_1646, hoisted__Str_1647, &_va_Array_39_ek);
        Str *hoisted__Str_1648 = format(_va_Array_39);
        return hoisted__Str_1648;
    }
    U64 hoisted__U64_1651 = (U64)(val);
    Str *hoisted__Str_1652 = U64_to_str(hoisted__U64_1651);
    return hoisted__Str_1652;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize I64_size(void) {
    U32 hoisted__U32_1666 = 8;
    return hoisted__U32_1666;
    __builtin_unreachable();
}

U64 I64_hash(I64 self, HashFn hasher) {
    U32 hoisted__U32_1792 = 8;
    U64 hoisted__U64_1793 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, I64 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1792); });
    return hoisted__U64_1793;
    __builtin_unreachable();
}

void F32_delete(F32 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize F32_size(void) {
    U32 hoisted__U32_1795 = 4;
    return hoisted__U32_1795;
    __builtin_unreachable();
}

U64 F32_hash(F32 self, HashFn hasher) {
    U32 hoisted__U32_1811 = 4;
    U64 hoisted__U64_1812 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, F32 *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1811); });
    return hoisted__U64_1812;
    __builtin_unreachable();
}

I64 Bool_cmp(Bool a, Bool b) {
    Bool hoisted__Bool_1855 = ((Bool)(a == b));
    if (hoisted__Bool_1855) {
        I64 hoisted__I64_1853 = 0;
        return hoisted__I64_1853;
    }
    if (b) {
        I64 hoisted__I64_1854 = -1;
        return hoisted__I64_1854;
    }
    I64 hoisted__I64_1856 = 1;
    return hoisted__I64_1856;
    __builtin_unreachable();
}

void Bool_delete(Bool * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

USize Bool_size(void) {
    U32 hoisted__U32_1857 = 1;
    return hoisted__U32_1857;
    __builtin_unreachable();
}

U64 Bool_hash(Bool self, HashFn hasher) {
    U32 hoisted__U32_1858 = 1;
    U64 hoisted__U64_1859 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Bool *, U32))til_closure->call)(til_closure->env, &self, hoisted__U32_1858); });
    return hoisted__U64_1859;
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
Bool Primitive_eq(Primitive * self, Primitive * other) {
    Bool hoisted__Bool_1874 = ((Bool)((((Primitive *)(self))->tag) == (((Primitive *)(other))->tag)));
    return hoisted__Bool_1874;
    __builtin_unreachable();
}

void Primitive_delete(Primitive * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Primitive * Primitive_clone(Primitive * self) {
    Bool hoisted__Bool_1896 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I16});
    if (hoisted__Bool_1896) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
        return _r; }
    }
    Bool hoisted__Bool_1897 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U16});
    if (hoisted__Bool_1897) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U16;
        return _r; }
    }
    Bool hoisted__Bool_1898 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I8});
    if (hoisted__Bool_1898) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I8;
        return _r; }
    }
    Bool hoisted__Bool_1899 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U8});
    if (hoisted__Bool_1899) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U8;
        return _r; }
    }
    Bool hoisted__Bool_1900 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U32});
    if (hoisted__Bool_1900) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U32;
        return _r; }
    }
    Bool hoisted__Bool_1901 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I32});
    if (hoisted__Bool_1901) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I32;
        return _r; }
    }
    Bool hoisted__Bool_1902 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_U64});
    if (hoisted__Bool_1902) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_U64;
        return _r; }
    }
    Bool hoisted__Bool_1903 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_I64});
    if (hoisted__Bool_1903) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I64;
        return _r; }
    }
    Bool hoisted__Bool_1904 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_F32});
    if (hoisted__Bool_1904) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_F32;
        return _r; }
    }
    Bool hoisted__Bool_1905 = Primitive_eq(self, &(Primitive){.tag = Primitive_TAG_Bool});
    if (hoisted__Bool_1905) {
        { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_Bool;
        return _r; }
    }
    static Str hoisted__Str_1906 = (Str){.c_str = (void *)"Primitive.clone:16:1", .count = 20ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_1906);
    Str_delete(&hoisted__Str_1906, (Bool){0});
    { Primitive *_r = malloc(sizeof(Primitive)); _r->tag = Primitive_TAG_I16;
    return _r; }
    __builtin_unreachable();
}

USize Primitive_size(void) {
    U32 hoisted__U32_1907 = 1;
    return hoisted__U32_1907;
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
void Type_delete(Type * self, Bool call_free) {
    Bool hoisted__Bool_1960 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag)));
    if (hoisted__Bool_1960) {
        Str *hoisted__Str_1950 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_1951 = 0;
        Str_delete(hoisted__Str_1950, hoisted__Bool_1951);
    }
    Bool hoisted__Bool_1961 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag)));
    if (hoisted__Bool_1961) {
        Str *hoisted__Str_1952 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_1953 = 0;
        Str_delete(hoisted__Str_1952, hoisted__Bool_1953);
    }
    Bool hoisted__Bool_1962 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag)));
    if (hoisted__Bool_1962) {
        Str *hoisted__Str_1954 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_1955 = 0;
        Str_delete(hoisted__Str_1954, hoisted__Bool_1955);
    }
    Bool hoisted__Bool_1963 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag)));
    if (hoisted__Bool_1963) {
        Primitive *hoisted__Primitive_1956 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_1957 = 0;
        Primitive_delete(hoisted__Primitive_1956, hoisted__Bool_1957);
    }
    Bool hoisted__Bool_1964 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag)));
    if (hoisted__Bool_1964) {
        Str *hoisted__Str_1958 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        Bool hoisted__Bool_1959 = 0;
        Str_delete(hoisted__Str_1958, hoisted__Bool_1959);
    }
    if (call_free) {
        free(self);
    }
}

Type * Type_clone(Type * self) {
    Bool hoisted__Bool_2037 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Unknown}))->tag)));
    if (hoisted__Bool_2037) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Unknown;
        return _r; }
    }
    Bool hoisted__Bool_2038 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_None}))->tag)));
    if (hoisted__Bool_2038) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_None;
        return _r; }
    }
    Bool hoisted__Bool_2039 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Struct}))->tag)));
    if (hoisted__Bool_2039) {
        Str *_clone_payload_Struct_2 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Struct_2;
        (void)_clone_payload_Struct_2;
        Str *hoisted__Str_2027 = Str_clone(_clone_payload_Struct_2);
        Type *hoisted__Type_2028 = Type_Struct(hoisted__Str_2027);
        return hoisted__Type_2028;
    }
    Bool hoisted__Bool_2040 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_StructDef}))->tag)));
    if (hoisted__Bool_2040) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_StructDef;
        return _r; }
    }
    Bool hoisted__Bool_2041 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Enum}))->tag)));
    if (hoisted__Bool_2041) {
        Str *_clone_payload_Enum_4 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Enum_4;
        (void)_clone_payload_Enum_4;
        Str *hoisted__Str_2029 = Str_clone(_clone_payload_Enum_4);
        Type *hoisted__Type_2030 = Type_Enum(hoisted__Str_2029);
        return hoisted__Type_2030;
    }
    Bool hoisted__Bool_2042 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_EnumDef}))->tag)));
    if (hoisted__Bool_2042) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_EnumDef;
        return _r; }
    }
    Bool hoisted__Bool_2043 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncDef}))->tag)));
    if (hoisted__Bool_2043) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncDef;
        return _r; }
    }
    Bool hoisted__Bool_2044 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncPtr}))->tag)));
    if (hoisted__Bool_2044) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_FuncPtr;
        return _r; }
    }
    Bool hoisted__Bool_2045 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Dynamic}))->tag)));
    if (hoisted__Bool_2045) {
        { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Dynamic;
        return _r; }
    }
    Bool hoisted__Bool_2046 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Custom}))->tag)));
    if (hoisted__Bool_2046) {
        Str *_clone_payload_Custom_9 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Custom_9;
        (void)_clone_payload_Custom_9;
        Str *hoisted__Str_2031 = Str_clone(_clone_payload_Custom_9);
        Type *hoisted__Type_2032 = Type_Custom(hoisted__Str_2031);
        return hoisted__Type_2032;
    }
    Bool hoisted__Bool_2047 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_Primitive}))->tag)));
    if (hoisted__Bool_2047) {
        Primitive *_clone_payload_Primitive_10 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_Primitive_10;
        (void)_clone_payload_Primitive_10;
        Primitive hoisted__Primitive_2033 = DEREF(_clone_payload_Primitive_10);
        Type *hoisted__Type_2034 = Type_Primitive(({ Primitive *_oa = malloc(sizeof(Primitive)); *_oa = hoisted__Primitive_2033; _oa; }));
        return hoisted__Type_2034;
    }
    Bool hoisted__Bool_2048 = ((Bool)((((Type *)(self))->tag) == (((Type *)(&(Type){.tag = Type_TAG_FuncPtrSig}))->tag)));
    if (hoisted__Bool_2048) {
        Str *_clone_payload_FuncPtrSig_11 = ((void *)((U8 *)(self) + offsetof(Type, data)));
        (void)_clone_payload_FuncPtrSig_11;
        (void)_clone_payload_FuncPtrSig_11;
        Str *hoisted__Str_2035 = Str_clone(_clone_payload_FuncPtrSig_11);
        Type *hoisted__Type_2036 = Type_FuncPtrSig(hoisted__Str_2035);
        return hoisted__Type_2036;
    }
    { Type *_r = malloc(sizeof(Type)); _r->tag = Type_TAG_Body;
    return _r; }
    __builtin_unreachable();
}

USize Type_size(void) {
    U32 hoisted__U32_2049 = 24;
    return hoisted__U32_2049;
    __builtin_unreachable();
}


__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_5528 = 3;
    Array__Str *_va_Array_148 = Array__Str_new(hoisted__U32_5528);
    (void)_va_Array_148;
    I64 _va_Array_148_ek = 0;
    (void)_va_Array_148_ek;
    U32 hoisted__U32_5529 = 0;
    Str *hoisted__Str_5530 = Str_clone(loc);
    Array__Str_set(_va_Array_148, hoisted__U32_5529, hoisted__Str_5530, &_va_Array_148_ek);
    U32 hoisted__U32_5531 = 1;
    Array__Str_set(_va_Array_148, hoisted__U32_5531, &_til_str_lits[0], &_va_Array_148_ek);
    Array__Str *hoisted__Array__Str_5533 = Array__Str_clone(parts);
    U32 hoisted__U32_5534 = 2;
    Str *hoisted__Str_5535 = format(hoisted__Array__Str_5533);
    Array__Str_set(_va_Array_148, hoisted__U32_5534, hoisted__Str_5535, &_va_Array_148_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_148);
    I64 hoisted__I64_5536 = 1;
    exit(hoisted__I64_5536);
}

__attribute__((noreturn)) void UNREACHABLE(Str * loc) {
    U32 hoisted__U32_5543 = 1;
    Array__Str *_va_Array_150 = Array__Str_new(hoisted__U32_5543);
    (void)_va_Array_150;
    I64 _va_Array_150_ek = 0;
    (void)_va_Array_150_ek;
    U32 hoisted__U32_5544 = 0;
    Array__Str_set(_va_Array_150, hoisted__U32_5544, &_til_str_lits[1], &_va_Array_150_ek);
    panic(_va_Array_150, loc);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_5549 = ((Bool)(!(cond)));
    if (hoisted__Bool_5549) {
        U32 hoisted__U32_5546 = 1;
        Array__Str *_va_Array_151 = Array__Str_new(hoisted__U32_5546);
        (void)_va_Array_151;
        I64 _va_Array_151_ek = 0;
        (void)_va_Array_151_ek;
        U32 hoisted__U32_5547 = 0;
        Array__Str_set(_va_Array_151, hoisted__U32_5547, &_til_str_lits[2], &_va_Array_151_ek);
        panic(_va_Array_151, loc);
    }
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_5557 = parts;
        (void)_fc_Array__Str_5557;
        (void)_fc_Array__Str_5557;
        U32 _fi_USize_5557 = 0;
        (void)_fi_USize_5557;
        while (1) {
            USize hoisted__U32_5559 = (_fc_Array__Str_5557->cap);
            Bool _wcond_Bool_5558 = ((Bool)(_fi_USize_5557 < hoisted__U32_5559));
            (void)_wcond_Bool_5558;
            if (_wcond_Bool_5558) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_5557->data) + (((U32)(_fi_USize_5557 * 16))))));
            U32 hoisted__U32_5560 = 1;
            U32 hoisted__U32_5561 = ((U32)(_fi_USize_5557 + hoisted__U32_5560));
            _fi_USize_5557 = hoisted__U32_5561;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

Range * Range_clone(Range * val) {
    Range hoisted__Range_5574 = (Range){.start = val->start, .end = val->end};
    { Range *_r = malloc(sizeof(Range)); *_r = hoisted__Range_5574;
    return _r; }
    __builtin_unreachable();
}

void Range_delete(Range * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 Range_hash(Range * self, HashFn hasher) {
    U32 hoisted__U32_5575 = 0;
    U64 hoisted__U64_5576 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, Range *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_5575); });
    return hoisted__U64_5576;
    __builtin_unreachable();
}

USize Range_size(void) {
    U32 hoisted__U32_5600 = 16;
    return hoisted__U32_5600;
    __builtin_unreachable();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_5614 = 3;
    assert_eq__I64(result, hoisted__I64_5614, &_til_str_lits[3]);
    Str_delete(&_til_str_lits[3], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_5622 = 15;
    assert_eq__I64(result, hoisted__I64_5622, &_til_str_lits[4]);
    Str_delete(&_til_str_lits[4], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_5630 = 26;
    assert_eq__I64(result, hoisted__I64_5630, &_til_str_lits[5]);
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
    I64 hoisted__I64_5699 = 106;
    assert_eq__I64(d3, hoisted__I64_5699, &_til_str_lits[15]);
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
    I64 hoisted__I64_6192 = 8;
    assert_eq__I64(result, hoisted__I64_6192, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6196 = 1;
    assert(hoisted__Bool_6196, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
    Bool hoisted__Bool_6200 = 1;
    assert(hoisted__Bool_6200, &_til_str_lits[22]);
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

CfVec2 * CfVec2_clone(CfVec2 * self) {
    CfVec2 hoisted__CfVec2_6218 = (CfVec2){.x = self->x, .y = self->y};
    { CfVec2 *_r = malloc(sizeof(CfVec2)); *_r = hoisted__CfVec2_6218;
    return _r; }
    __builtin_unreachable();
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec2_hash(CfVec2 * self, HashFn hasher) {
    U32 hoisted__U32_6219 = 0;
    U64 hoisted__U64_6220 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec2 *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6219); });
    return hoisted__U64_6220;
    __builtin_unreachable();
}

USize CfVec2_size(void) {
    U32 hoisted__U32_6244 = 16;
    return hoisted__U32_6244;
    __builtin_unreachable();
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_6245 = 42;
    assert_eq__I64(v.x, hoisted__I64_6245, &_til_str_lits[27]);
    Str_delete(&_til_str_lits[27], (Bool){0});
    I64 hoisted__I64_6247 = 99;
    assert_eq__I64(v.y, hoisted__I64_6247, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6251 = 10;
    assert_eq__I64(p.x, hoisted__I64_6251, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    I64 hoisted__I64_6253 = 20;
    assert_eq__I64(p.y, hoisted__I64_6253, &_til_str_lits[30]);
    Str_delete(&_til_str_lits[30], (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

CfRect * CfRect_clone(CfRect * self) {
    CfRect hoisted__CfRect_6260 = (CfRect){.top_left = self->top_left, .bottom_right = self->bottom_right};
    { CfRect *_r = malloc(sizeof(CfRect)); *_r = hoisted__CfRect_6260;
    return _r; }
    __builtin_unreachable();
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfRect_hash(CfRect * self, HashFn hasher) {
    U32 hoisted__U32_6261 = 0;
    U64 hoisted__U64_6262 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfRect *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6261); });
    return hoisted__U64_6262;
    __builtin_unreachable();
}

USize CfRect_size(void) {
    U32 hoisted__U32_6286 = 32;
    return hoisted__U32_6286;
    __builtin_unreachable();
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_6287 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_6287, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    I64 hoisted__I64_6289 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_6289, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_6291 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6291, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_6293 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6293, &_til_str_lits[34]);
    Str_delete(&_til_str_lits[34], (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

CfVec3f * CfVec3f_clone(CfVec3f * self) {
    CfVec3f hoisted__CfVec3f_6296 = (CfVec3f){.x = self->x, .y = self->y, .z = self->z};
    { CfVec3f *_r = malloc(sizeof(CfVec3f)); *_r = hoisted__CfVec3f_6296;
    return _r; }
    __builtin_unreachable();
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

U64 CfVec3f_hash(CfVec3f * self, HashFn hasher) {
    U32 hoisted__U32_6297 = 0;
    U64 hoisted__U64_6298 = ({ TilClosure *til_closure = (TilClosure *)(hasher); ((U64 (*)(void *, CfVec3f *, U32))til_closure->call)(til_closure->env, self, hoisted__U32_6297); });
    return hoisted__U64_6298;
    __builtin_unreachable();
}

USize CfVec3f_size(void) {
    U32 hoisted__U32_6331 = 12;
    return hoisted__U32_6331;
    __builtin_unreachable();
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_6335 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_6335, &_til_str_lits[35], &_til_str_lits[36]);
    Str_delete(hoisted__Str_6335, 1);
    Str_delete(&_til_str_lits[35], (Bool){0});
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str *hoisted__Str_6338 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_6338, &_til_str_lits[37], &_til_str_lits[38]);
    Str_delete(hoisted__Str_6338, 1);
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str *hoisted__Str_6341 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_6341, &_til_str_lits[39], &_til_str_lits[40]);
    Str_delete(hoisted__Str_6341, 1);
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
    Bool hoisted__Bool_6344 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_6344;
    __builtin_unreachable();
}

void Color_delete(Color * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

Color * Color_clone(Color * self) {
    Bool hoisted__Bool_6352 = Color_eq(self, &(Color){.tag = Color_TAG_Red});
    if (hoisted__Bool_6352) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
        return _r; }
    }
    Bool hoisted__Bool_6353 = Color_eq(self, &(Color){.tag = Color_TAG_Green});
    if (hoisted__Bool_6353) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Green;
        return _r; }
    }
    Bool hoisted__Bool_6354 = Color_eq(self, &(Color){.tag = Color_TAG_Blue});
    if (hoisted__Bool_6354) {
        { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Blue;
        return _r; }
    }
    static Str hoisted__Str_6355 = (Str){.c_str = (void *)"Color.clone:235:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&hoisted__Str_6355);
    Str_delete(&hoisted__Str_6355, (Bool){0});
    { Color *_r = malloc(sizeof(Color)); _r->tag = Color_TAG_Red;
    return _r; }
    __builtin_unreachable();
}

USize Color_size(void) {
    U32 hoisted__U32_6356 = 1;
    return hoisted__U32_6356;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_6357 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_6357, &_til_str_lits[41]);
    Str_delete(&_til_str_lits[41], (Bool){0});
    Bool hoisted__Bool_6359 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_6360 = ((Bool)(!(hoisted__Bool_6359)));
    assert(hoisted__Bool_6360, &_til_str_lits[42]);
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
    Bool hoisted__Bool_6379 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_6379) {
        I64 *hoisted__I64_6375 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6376 = 0;
        I64_delete(hoisted__I64_6375, hoisted__Bool_6376);
    }
    Bool hoisted__Bool_6380 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_6380) {
        Str *hoisted__Str_6377 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_6378 = 0;
        Str_delete(hoisted__Str_6377, hoisted__Bool_6378);
    }
    if (call_free) {
        free(self);
    }
}

Token * Token_clone(Token * self) {
    Bool hoisted__Bool_6405 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_6405) {
        I64 *_clone_payload_Num_0 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)_clone_payload_Num_0;
        (void)_clone_payload_Num_0;
        Token *hoisted__Token_6402 = Token_Num(_clone_payload_Num_0);
        return hoisted__Token_6402;
    }
    Bool hoisted__Bool_6406 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_6406) {
        Str *_clone_payload_Name_1 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        (void)_clone_payload_Name_1;
        (void)_clone_payload_Name_1;
        Str *hoisted__Str_6403 = Str_clone(_clone_payload_Name_1);
        Token *hoisted__Token_6404 = Token_Name(hoisted__Str_6403);
        return hoisted__Token_6404;
    }
    { Token *_r = malloc(sizeof(Token)); _r->tag = Token_TAG_Eof;
    return _r; }
    __builtin_unreachable();
}

USize Token_size(void) {
    U32 hoisted__U32_6407 = 24;
    return hoisted__U32_6407;
    __builtin_unreachable();
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_6409 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    assert(hoisted__Bool_6409, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
    Bool hoisted__Bool_6411 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    Bool hoisted__Bool_6412 = ((Bool)(!(hoisted__Bool_6411)));
    assert(hoisted__Bool_6412, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_6414 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_6414, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Bool hoisted__Bool_6416 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_6417 = ((Bool)(!(hoisted__Bool_6416)));
    assert(hoisted__Bool_6417, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_6421 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Num}))->tag));
    assert(hoisted__Bool_6421, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
    Bool hoisted__Bool_6423 = ((Bool)(((Token *)(t))->tag == ((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag));
    Bool hoisted__Bool_6424 = ((Bool)(!(hoisted__Bool_6423)));
    assert(hoisted__Bool_6424, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Token_delete(t, 1);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_6492 = ((Bool)(a != b));
    if (hoisted__Bool_6492) {
        U32 hoisted__U32_6481 = 5;
        Array__Str *_va_Array_188 = Array__Str_new(hoisted__U32_6481);
        (void)_va_Array_188;
        I64 _va_Array_188_ek = 0;
        (void)_va_Array_188_ek;
        U32 hoisted__U32_6482 = 0;
        Array__Str_set(_va_Array_188, hoisted__U32_6482, &_til_str_lits[49], &_va_Array_188_ek);
        U32 hoisted__U32_6484 = 1;
        Str *hoisted__Str_6485 = I64_to_str(a);
        Array__Str_set(_va_Array_188, hoisted__U32_6484, hoisted__Str_6485, &_va_Array_188_ek);
        U32 hoisted__U32_6486 = 2;
        Array__Str_set(_va_Array_188, hoisted__U32_6486, &_til_str_lits[50], &_va_Array_188_ek);
        U32 hoisted__U32_6488 = 3;
        Str *hoisted__Str_6489 = I64_to_str(b);
        Array__Str_set(_va_Array_188, hoisted__U32_6488, hoisted__Str_6489, &_va_Array_188_ek);
        U32 hoisted__U32_6490 = 4;
        Array__Str_set(_va_Array_188, hoisted__U32_6490, &_til_str_lits[51], &_va_Array_188_ek);
        panic(_va_Array_188, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_6504 = Str_neq(a, b);
    if (hoisted__Bool_6504) {
        U32 hoisted__U32_6493 = 5;
        Array__Str *_va_Array_189 = Array__Str_new(hoisted__U32_6493);
        (void)_va_Array_189;
        I64 _va_Array_189_ek = 0;
        (void)_va_Array_189_ek;
        U32 hoisted__U32_6494 = 0;
        Array__Str_set(_va_Array_189, hoisted__U32_6494, &_til_str_lits[49], &_va_Array_189_ek);
        U32 hoisted__U32_6496 = 1;
        Str *hoisted__Str_6497 = Str_to_str(a);
        Array__Str_set(_va_Array_189, hoisted__U32_6496, hoisted__Str_6497, &_va_Array_189_ek);
        U32 hoisted__U32_6498 = 2;
        Array__Str_set(_va_Array_189, hoisted__U32_6498, &_til_str_lits[50], &_va_Array_189_ek);
        U32 hoisted__U32_6500 = 3;
        Str *hoisted__Str_6501 = Str_to_str(b);
        Array__Str_set(_va_Array_189, hoisted__U32_6500, hoisted__Str_6501, &_va_Array_189_ek);
        U32 hoisted__U32_6502 = 4;
        Array__Str_set(_va_Array_189, hoisted__U32_6502, &_til_str_lits[51], &_va_Array_189_ek);
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
