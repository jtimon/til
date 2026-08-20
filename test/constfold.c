#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>

#include "ext.h"

typedef struct Str Str;
typedef struct Array__Str Array__Str;
typedef struct Vec__Str Vec__Str;
typedef struct CfVec2 CfVec2;
typedef struct CfRect CfRect;
typedef struct CfVec3f CfVec3f;
enum {
    Color_TAG_Red,
    Color_TAG_Green,
    Color_TAG_Blue
};
typedef struct Color Color;
enum {
    Token_TAG_Num,
    Token_TAG_Name,
    Token_TAG_Eof
};
typedef struct Token Token;
enum {
    WideToken_TAG_Num = 4294967297,
    WideToken_TAG_Eof = 4294967300
};
typedef struct WideToken WideToken;
typedef struct NestedToken NestedToken;
typedef struct CfNestedValues CfNestedValues;
typedef struct Array__I64 Array__I64;
typedef struct Map__Str_I64 Map__Str_I64;
typedef struct Vec__I64 Vec__I64;
typedef struct Vec__CfNestedValues Vec__CfNestedValues;


typedef struct Str {
    I8 *c_str;
    USize count;
    USize cap;
} Str;


typedef struct Array__Str {
    U8 *data;
    USize cap;
} Array__Str;


typedef struct Vec__Str {
    U8 *data;
    USize count;
    USize cap;
} Vec__Str;










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

struct WideToken {
    U64 tag;
    union {
        I64 Num;
        void *_til_payload_align;
    } data;
};

struct NestedToken {
    WideToken *data;
};

typedef struct Array__I64 {
    U8 *data;
    USize cap;
} Array__I64;


typedef struct Vec__I64 {
    U8 *data;
    USize count;
    USize cap;
} Vec__I64;


typedef struct Vec__CfNestedValues {
    U8 *data;
    USize count;
    USize cap;
} Vec__CfNestedValues;


typedef struct CfNestedValues {
    Vec__I64 values;
} CfNestedValues;


typedef struct Map__Str_I64 {
    Vec__Str keys;
    Vec__I64 values;
} Map__Str_I64;



static void print_single(Str *s);
static void print_flush();

static Str format(Array__Str * parts);
static I64 Str_cmp(Str * a, Str * b);
static Bool Str_eq(Str * a, Str * b);
static Str Str_with_capacity(USize n);
static void Str_push_str(Str * self, Str * s);
Str Str_clone(Str * val);
static Str Str_to_str(Str * self);
static void Str_delete(Str * self, Bool call_free);
static Bool Str_neq(Str * a, Str * b);
static Array__Str Array__Str_new(USize cap);
static void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val);
static void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind);
static void Array__Str_delete(Array__Str * self, Bool call_free);
static Array__Str Array__Str_clone(Array__Str * self);
static void Vec__Str_clear(Vec__Str * self);
static void Vec__Str_unsafe_set(Vec__Str * self, USize i, Str * val);
static void Vec__Str_set(Vec__Str * self, USize i, Str * val, I64 * _err_kind);
static void Vec__Str_delete(Vec__Str * self, Bool call_free);
static Vec__Str Vec__Str_clone(Vec__Str * self);
static void adopt__Str(void * dest, Str * src);
static Str U32_to_str(U32 val);
static Str U64_to_str(U64 val);
static Str I64_to_str(I64 val);
static void I64_delete(I64 * self, Bool call_free);
static UPtr usize_to_uptr(USize val);
static __attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
static __attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc);
static void assert(Bool cond, Str * loc);
static void expect(Bool cond, Array__Str * parts, Str * loc);
static void println(Array__Str * parts);
static void test_simple_add(void);
static void test_nested_arithmetic(void);
static void test_deeply_nested(void);
static void test_string_concat(void);
static void test_variadic_fold(void);
static void test_variadic_direct_fold(void);
static void test_lolalalo(void);
static void test_fold_variable(void);
static void test_loc_folded(void);
static void test_fold_f32(void);
static void test_struct_fold_simple(void);
static void test_struct_fold_values(void);
static void test_struct_fold_nested(void);
static void test_struct_fold_f32(void);
static Bool Color_eq(Color * self, Color * other);
static Color Color_clone(Color * self);
static void test_enum_fold(void);
static void test_enum_literal_fold(void);
static Token Token_Num(I64 * val);
static void Token_delete(Token * self, Bool call_free);
static void test_enum_payload_fold(void);
static void test_enum_return_fold(void);
static void test_enum_payload_return_fold(void);
static WideToken WideToken_Num(I64 * val);
static void WideToken_delete(WideToken * self, Bool call_free);
static WideToken WideToken_clone(WideToken * self);
static NestedToken NestedToken_Inner(WideToken * val);
static void NestedToken_delete(NestedToken * self, Bool call_free);
static void test_explicit_tag_enum_return_fold(void);
static void test_nested_enum_payload_return_fold(void);
static CfNestedValues CfNestedValues_clone(CfNestedValues * self);
static void CfNestedValues_delete(CfNestedValues * self, Bool call_free);
static void test_collection_return_fold(void);
static void test_serialized_values_are_compositional(void);
static void test_static_global_initializers(void);
static void test_const_and_or_fold(void);
static void test_mixed_fold(void);
static void test_fold_reads_global_const(void);
static void Array__I64_delete(Array__I64 * self, Bool call_free);
static Array__I64 Array__I64_clone(Array__I64 * self);
static I64 * Map__Str_I64_get(Map__Str_I64 * self, Str * key, I64 * _err_kind);
static void Map__Str_I64_delete(Map__Str_I64 * self, Bool call_free);
static void Vec__I64_clear(Vec__I64 * self);
static void Vec__I64_delete(Vec__I64 * self, Bool call_free);
static Vec__I64 Vec__I64_clone(Vec__I64 * self);
static void Vec__CfNestedValues_clear(Vec__CfNestedValues * self);
static void Vec__CfNestedValues_delete(Vec__CfNestedValues * self, Bool call_free);
static Vec__CfNestedValues Vec__CfNestedValues_clone(Vec__CfNestedValues * self);
static void assert_eq__I64(I64 a, I64 b, Str * loc);
static void assert_eq__Str(Str * a, Str * b, Str * loc);
static void assert_eq__USize(USize a, USize b, Str * loc);
static void adopt__I64(void * dest, I64 src);
static void adopt__CfNestedValues(void * dest, CfNestedValues * src);


#define DEREF(p) (*(p ? p : (fprintf(stderr, "panic: null deref\n"), exit(1), p)))
#define TIL_BOX(T) (sizeof(T) < sizeof(void *) ? sizeof(void *) : sizeof(T))
#define TIL_CAP_LIT ((USize)-1)
#define TIL_CAP_VIEW ((USize)-2)
static void print_single(Str *s) {
    fwrite(s->c_str, 1, (size_t)s->count, stdout);
}
static void print_flush() {
    putchar('\n');
}

static struct {
    Str h000000001505;
    Str h00000002b5cc;
    Str h15a1180c089b;
    Str h00000b8791fb;
    Str h00017c7b7650;
    Str h00000002b606;
    Str h00310f176c2b;
    Str h44abcb58cde4;
    Str h00000002b607;
    Str h00017c9489a1;
    Str hd0b1c236fb8f;
    Str h3fd43551c8c1;
    Str h00000002b617;
    Str hd0e435b6dffc;
    Str h4d3ab87300de;
} _til_str_lits = {
    .h000000001505 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT},
    .h00000002b5cc = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT},
    .h15a1180c089b = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT},
    .h00000b8791fb = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT},
    .h00017c7b7650 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT},
    .h00000002b606 = (Str){.c_str = (void *)"a", .count = 1ULL, .cap = TIL_CAP_LIT},
    .h00310f176c2b = (Str){.c_str = (void *)"alpha", .count = 5ULL, .cap = TIL_CAP_LIT},
    .h44abcb58cde4 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT},
    .h00000002b607 = (Str){.c_str = (void *)"b", .count = 1ULL, .cap = TIL_CAP_LIT},
    .h00017c9489a1 = (Str){.c_str = (void *)"beta", .count = 4ULL, .cap = TIL_CAP_LIT},
    .hd0b1c236fb8f = (Str){.c_str = (void *)"changed", .count = 7ULL, .cap = TIL_CAP_LIT},
    .h3fd43551c8c1 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT},
    .h00000002b617 = (Str){.c_str = (void *)"r", .count = 1ULL, .cap = TIL_CAP_LIT},
    .hd0e435b6dffc = (Str){.c_str = (void *)"uncaught throw 'KeyNotFound'", .count = 28ULL, .cap = TIL_CAP_LIT},
    .h4d3ab87300de = (Str){.c_str = (void *)"uncaught throw 'OutOfBounds'", .count = 28ULL, .cap = TIL_CAP_LIT},
};
#define TIL_LIT_GUARD(p) do { UPtr _g = (UPtr)(const void *)(p); if (_g >= (UPtr)(const void *)&_til_str_lits && _g < (UPtr)(const void *)(&_til_str_lits + 1)) { fprintf(stderr, "panic: write through a shared string literal\n"); exit(1); } } while (0)

/* til source locations: line numbers shift with source edits; the code hunks are above */
static Str hoisted__Str_Str_push_str_3 = (Str){.c_str = (void *)"./src/core/str.til:129:13", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_Str_push_str_7 = (Str){.c_str = (void *)"./src/core/str.til:133:13", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_102 = (Str){.c_str = (void *)"test/constfold.til:444:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_105 = (Str){.c_str = (void *)"test/constfold.til:447:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_110 = (Str){.c_str = (void *)"test/constfold.til:448:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_115 = (Str){.c_str = (void *)"test/constfold.til:449:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_118 = (Str){.c_str = (void *)"test/constfold.til:452:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_129 = (Str){.c_str = (void *)"test/constfold.til:455:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_134 = (Str){.c_str = (void *)"test/constfold.til:456:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_14 = (Str){.c_str = (void *)"test/constfold.til:443:25", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_143 = (Str){.c_str = (void *)"test/constfold.til:461:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_148 = (Str){.c_str = (void *)"test/constfold.til:462:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_150 = (Str){.c_str = (void *)"test/constfold.til:465:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_155 = (Str){.c_str = (void *)"test/constfold.til:466:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_19 = (Str){.c_str = (void *)"test/constfold.til:444:25", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_24 = (Str){.c_str = (void *)"test/constfold.til:448:25", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_29 = (Str){.c_str = (void *)"test/constfold.til:449:25", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_34 = (Str){.c_str = (void *)"test/constfold.til:453:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_39 = (Str){.c_str = (void *)"test/constfold.til:454:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_4 = (Str){.c_str = (void *)"test/constfold.til:434:26", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_44 = (Str){.c_str = (void *)"test/constfold.til:455:39", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_49 = (Str){.c_str = (void *)"test/constfold.til:456:40", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_54 = (Str){.c_str = (void *)"test/constfold.til:460:9", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_59 = (Str){.c_str = (void *)"test/constfold.til:461:24", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_64 = (Str){.c_str = (void *)"test/constfold.til:462:25", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_69 = (Str){.c_str = (void *)"test/constfold.til:466:32", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_72 = (Str){.c_str = (void *)"test/constfold.til:432:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_74 = (Str){.c_str = (void *)"test/constfold.til:433:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_79 = (Str){.c_str = (void *)"test/constfold.til:434:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_84 = (Str){.c_str = (void *)"test/constfold.til:435:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_87 = (Str){.c_str = (void *)"test/constfold.til:438:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_89 = (Str){.c_str = (void *)"test/constfold.til:439:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_9 = (Str){.c_str = (void *)"test/constfold.til:435:26", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_92 = (Str){.c_str = (void *)"test/constfold.til:442:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_collection_return_fold_97 = (Str){.c_str = (void *)"test/constfold.til:443:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_10 = (Str){.c_str = (void *)"test/constfold.til:505:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_16 = (Str){.c_str = (void *)"test/constfold.til:506:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_21 = (Str){.c_str = (void *)"test/constfold.til:507:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_27 = (Str){.c_str = (void *)"test/constfold.til:508:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_32 = (Str){.c_str = (void *)"test/constfold.til:509:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_38 = (Str){.c_str = (void *)"test/constfold.til:510:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_43 = (Str){.c_str = (void *)"test/constfold.til:511:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_49 = (Str){.c_str = (void *)"test/constfold.til:512:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_54 = (Str){.c_str = (void *)"test/constfold.til:513:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_58 = (Str){.c_str = (void *)"test/constfold.til:514:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_deeply_nested_7 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_fold_1 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_fold_4 = (Str){.c_str = (void *)"test/constfold.til:251:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_literal_fold_10 = (Str){.c_str = (void *)"test/constfold.til:267:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_literal_fold_5 = (Str){.c_str = (void *)"test/constfold.til:265:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_literal_fold_7 = (Str){.c_str = (void *)"test/constfold.til:266:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_payload_fold_2 = (Str){.c_str = (void *)"test/constfold.til:275:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_payload_fold_5 = (Str){.c_str = (void *)"test/constfold.til:276:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_payload_return_fold_2 = (Str){.c_str = (void *)"test/constfold.til:297:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_payload_return_fold_5 = (Str){.c_str = (void *)"test/constfold.til:298:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_return_fold_1 = (Str){.c_str = (void *)"test/constfold.til:285:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_return_fold_4 = (Str){.c_str = (void *)"test/constfold.til:286:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_explicit_tag_enum_return_fold_1 = (Str){.c_str = (void *)"test/constfold.til:331:32", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_explicit_tag_enum_return_fold_3 = (Str){.c_str = (void *)"test/constfold.til:332:11", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_explicit_tag_enum_return_fold_6 = (Str){.c_str = (void *)"test/constfold.til:335:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_fold_f32_4 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_fold_f32_9 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_fold_reads_global_const_3 = (Str){.c_str = (void *)"test/constfold.til:539:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_fold_variable_2 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_loc_folded_3 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_loc_folded_7 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_lolalalo_8 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_lolalalo_9 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_mixed_fold_4 = (Str){.c_str = (void *)"test/constfold.til:521:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_nested_arithmetic_7 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_nested_enum_payload_return_fold_1 = (Str){.c_str = (void *)"test/constfold.til:343:36", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_nested_enum_payload_return_fold_3 = (Str){.c_str = (void *)"test/constfold.til:344:15", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_nested_enum_payload_return_fold_5 = (Str){.c_str = (void *)"test/constfold.til:346:11", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_serialized_values_are_compositional_12 = (Str){.c_str = (void *)"test/constfold.til:475:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_serialized_values_are_compositional_14 = (Str){.c_str = (void *)"test/constfold.til:476:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_serialized_values_are_compositional_17 = (Str){.c_str = (void *)"test/constfold.til:478:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_serialized_values_are_compositional_2 = (Str){.c_str = (void *)"test/constfold.til:470:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_serialized_values_are_compositional_21 = (Str){.c_str = (void *)"test/constfold.til:479:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_serialized_values_are_compositional_6 = (Str){.c_str = (void *)"test/constfold.til:471:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_serialized_values_are_compositional_9 = (Str){.c_str = (void *)"test/constfold.til:474:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_simple_add_3 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_1 = (Str){.c_str = (void *)"test/constfold.til:488:28", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_11 = (Str){.c_str = (void *)"test/constfold.til:484:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_13 = (Str){.c_str = (void *)"test/constfold.til:485:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_15 = (Str){.c_str = (void *)"test/constfold.til:486:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_17 = (Str){.c_str = (void *)"test/constfold.til:491:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_19 = (Str){.c_str = (void *)"test/constfold.til:496:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_3 = (Str){.c_str = (void *)"test/constfold.til:489:11", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_5 = (Str){.c_str = (void *)"test/constfold.til:493:32", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_7 = (Str){.c_str = (void *)"test/constfold.til:494:11", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_static_global_initializers_9 = (Str){.c_str = (void *)"test/constfold.til:483:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_string_concat_3 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_f32_11 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_f32_5 = (Str){.c_str = (void *)"test/constfold.til:238:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_f32_8 = (Str){.c_str = (void *)"test/constfold.til:239:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_nested_1 = (Str){.c_str = (void *)"test/constfold.til:212:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_nested_3 = (Str){.c_str = (void *)"test/constfold.til:213:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_nested_5 = (Str){.c_str = (void *)"test/constfold.til:214:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_nested_7 = (Str){.c_str = (void *)"test/constfold.til:215:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_simple_1 = (Str){.c_str = (void *)"test/constfold.til:184:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_simple_3 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_values_11 = (Str){.c_str = (void *)"test/constfold.til:195:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_values_13 = (Str){.c_str = (void *)"test/constfold.til:196:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_values_3 = (Str){.c_str = (void *)"test/constfold.til:191:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_values_5 = (Str){.c_str = (void *)"test/constfold.til:192:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_values_7 = (Str){.c_str = (void *)"test/constfold.til:193:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_values_9 = (Str){.c_str = (void *)"test/constfold.til:194:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_direct_fold_12 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_direct_fold_21 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_direct_fold_31 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_fold_3 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_fold_8 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};

static I64 _til_precomputed_sequence_22_data[4] = {11, 22};
static Vec__I64 _til_precomputed_sequence_22 = {.data = (U8 *)_til_precomputed_sequence_22_data, .count = 2ULL, .cap = 4ULL};
static I64 _til_precomputed_sequence_23_data[4] = {11, 22};
static Vec__I64 _til_precomputed_sequence_23 = {.data = (U8 *)_til_precomputed_sequence_23_data, .count = 2ULL, .cap = 4ULL};
static Vec__I64 _til_precomputed_sequence_24 = {.data = NULL, .count = 0ULL, .cap = 0ULL};
static I64 _til_precomputed_sequence_25_data[3] = {3, 5, 8};
static Array__I64 _til_precomputed_sequence_25 = {.data = (U8 *)_til_precomputed_sequence_25_data, .cap = 3ULL};
static Str _til_precomputed_sequence_26_data[4] = {{.c_str = (I8 *)"a", .count = 1ULL, .cap = TIL_CAP_LIT}, {.c_str = (I8 *)"b", .count = 1ULL, .cap = TIL_CAP_LIT}};
static Vec__Str _til_precomputed_sequence_26 = {.data = (U8 *)_til_precomputed_sequence_26_data, .count = 2ULL, .cap = 4ULL};
static I64 _til_precomputed_sequence_27_data[4] = {10, 20};
static Vec__I64 _til_precomputed_sequence_27 = {.data = (U8 *)_til_precomputed_sequence_27_data, .count = 2ULL, .cap = 4ULL};
static I64 _til_precomputed_sequence_28_data[2] = {1, 2};
static I64 _til_precomputed_sequence_29_data[1] = {3};
static CfNestedValues _til_precomputed_sequence_30_data[2] = {{.values = {.data = (U8 *)_til_precomputed_sequence_28_data, .count = 2ULL, .cap = 2ULL}}, {.values = {.data = (U8 *)_til_precomputed_sequence_29_data, .count = 1ULL, .cap = 1ULL}}};
static Vec__CfNestedValues _til_precomputed_sequence_30 = {.data = (U8 *)_til_precomputed_sequence_30_data, .count = 2ULL, .cap = 2ULL};
static Str _til_precomputed_sequence_31_data[2] = {{.c_str = (I8 *)"alpha", .count = 5ULL, .cap = TIL_CAP_LIT}, {.c_str = (I8 *)"beta", .count = 4ULL, .cap = TIL_CAP_LIT}};
static Vec__Str _til_precomputed_sequence_31 = {.data = (U8 *)_til_precomputed_sequence_31_data, .count = 2ULL, .cap = 2ULL};
static Str _til_precomputed_sequence_32_data[2] = {{.c_str = (I8 *)"alpha", .count = 5ULL, .cap = TIL_CAP_LIT}, {.c_str = (I8 *)"beta", .count = 4ULL, .cap = TIL_CAP_LIT}};
static Vec__Str _til_precomputed_sequence_32 = {.data = (U8 *)_til_precomputed_sequence_32_data, .count = 2ULL, .cap = 2ULL};
static I64 _til_precomputed_sequence_33_data[4] = {11, 22};
static Vec__I64 _til_precomputed_sequence_33 = {.data = (U8 *)_til_precomputed_sequence_33_data, .count = 2ULL, .cap = 4ULL};

USize CAP_LIT = 4294967295;
USize CAP_VIEW = 4294967294;
static I64 STATIC_SCALAR = 42;
static Str STATIC_STR = {.c_str = (I8 *)"static-folded", .count = 13ULL, .cap = TIL_CAP_LIT};
static CfVec2 STATIC_POINT = {.x = 42, .y = 99};
static Color STATIC_COLOR = {.tag = Color_TAG_Green};
static Token STATIC_TOKEN = {.tag = Token_TAG_Num, .data = {.Num = 13}};
static NestedToken STATIC_NICHE;
static Vec__I64 CF_COMPOSED_VALUES;
static U32 CF_COMPOSED_COUNT = 2;
I64 CfVec2_forward = 43;
I64 CfVec2_answer = 42;
CfVec2 CfVec2_sample_value = {.x = 6, .y = 7};
I64 WideToken_answer = 42;
WideToken WideToken_sample_value = {.tag = WideToken_TAG_Num, .data = {.Num = 12}};

static Str format(Array__Str * parts) {
    USize total = 0;
    {
        Array__Str *_fc_Array__Str_0 = parts;
        USize _fi_USize_0 = 0;
        while (1) {
            U32 hoisted__U32_2 = (_fc_Array__Str_0->cap);
            Bool _wcond_Bool_1 = ((Bool)(_fi_USize_0 < hoisted__U32_2));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_0->data) + (usize_to_uptr(((U32)(_fi_USize_0 * 16)))))));
            U32 hoisted__U32_3 = 1;
            U32 hoisted__U32_4 = ((U32)(_fi_USize_0 + hoisted__U32_3));
            _fi_USize_0 = hoisted__U32_4;
            U32 hoisted__U32_5 = (s->count);
            U32 hoisted__U32_6 = ((U32)(total + hoisted__U32_5));
            total = hoisted__U32_6;
        }
    }
    Str out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_7 = parts;
        USize _fi_USize_7 = 0;
        while (1) {
            U32 hoisted__U32_9 = (_fc_Array__Str_7->cap);
            Bool _wcond_Bool_8 = ((Bool)(_fi_USize_7 < hoisted__U32_9));
            if (_wcond_Bool_8) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_7->data) + (usize_to_uptr(((U32)(_fi_USize_7 * 16)))))));
            U32 hoisted__U32_10 = 1;
            U32 hoisted__U32_11 = ((U32)(_fi_USize_7 + hoisted__U32_10));
            _fi_USize_7 = hoisted__U32_11;
            Str_push_str(&out, s);
        }
    }
    Array__Str_delete(parts, (Bool){0});
    { Str _ret = out; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_4 = ((Bool)(b->count < a->count));
    if (hoisted__Bool_4) {
        min_len = b->count;
    }
    I32 c = memcmp(a->c_str, b->c_str, min_len);
    I32 hoisted__I32_5 = 0;
    Bool hoisted__Bool_6 = ((Bool)(c < hoisted__I32_5));
    if (hoisted__Bool_6) {
        I64 hoisted__I64_0 = -1;
        return hoisted__I64_0;
    }
    I32 hoisted__I32_7 = 0;
    Bool hoisted__Bool_8 = ((Bool)(c > hoisted__I32_7));
    if (hoisted__Bool_8) {
        I64 hoisted__I64_1 = 1;
        return hoisted__I64_1;
    }
    Bool hoisted__Bool_9 = ((Bool)(a->count < b->count));
    if (hoisted__Bool_9) {
        I64 hoisted__I64_2 = -1;
        return hoisted__I64_2;
    }
    Bool hoisted__Bool_10 = ((Bool)(a->count > b->count));
    if (hoisted__Bool_10) {
        I64 hoisted__I64_3 = 1;
        return hoisted__I64_3;
    }
    I64 hoisted__I64_11 = 0;
    return hoisted__I64_11;
}

static Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_7 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_7) {
        Bool hoisted__Bool_0 = 0;
        return hoisted__Bool_0;
    }
    Bool hoisted__Bool_8 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_8) {
        Bool hoisted__Bool_1 = 1;
        return hoisted__Bool_1;
    }
    U32 hoisted__U32_9 = 0;
    Bool hoisted__Bool_10 = ((Bool)(a->count == hoisted__U32_9));
    if (hoisted__Bool_10) {
        Bool hoisted__Bool_2 = 1;
        return hoisted__Bool_2;
    }
    U32 hoisted__U32_11 = 0;
    U32 hoisted__U32_12 = 0;
    I8 *hoisted__I8_13 = ((I8 *)((void *)((U8 *)(a->c_str) + (hoisted__U32_11))));
    I8 *hoisted__I8_14 = ((I8 *)((void *)((U8 *)(b->c_str) + (hoisted__U32_12))));
    Bool hoisted__Bool_15 = ((Bool)(DEREF(hoisted__I8_13) != DEREF(hoisted__I8_14)));
    if (hoisted__Bool_15) {
        Bool hoisted__Bool_3 = 0;
        return hoisted__Bool_3;
    }
    U32 hoisted__U32_16 = 1;
    Bool hoisted__Bool_17 = ((Bool)(a->count == hoisted__U32_16));
    if (hoisted__Bool_17) {
        Bool hoisted__Bool_4 = 1;
        return hoisted__Bool_4;
    }
    U32 hoisted__U32_18 = 1;
    U32 last = ((U32)(a->count - hoisted__U32_18));
    I8 *hoisted__I8_19 = ((I8 *)((void *)((U8 *)(a->c_str) + (last))));
    I8 *hoisted__I8_20 = ((I8 *)((void *)((U8 *)(b->c_str) + (last))));
    Bool hoisted__Bool_21 = ((Bool)(DEREF(hoisted__I8_19) != DEREF(hoisted__I8_20)));
    if (hoisted__Bool_21) {
        Bool hoisted__Bool_5 = 0;
        return hoisted__Bool_5;
    }
    U32 hoisted__U32_22 = 2;
    Bool hoisted__Bool_23 = ((Bool)(a->count == hoisted__U32_22));
    if (hoisted__Bool_23) {
        Bool hoisted__Bool_6 = 1;
        return hoisted__Bool_6;
    }
    U64 hoisted__U64_24 = 1ULL;
    U64 hoisted__U64_25 = 1ULL;
    U32 hoisted__U32_26 = 2;
    void *hoisted__v_27 = ((void *)((U8 *)(a->c_str) + (hoisted__U64_24)));
    void *hoisted__v_28 = ((void *)((U8 *)(b->c_str) + (hoisted__U64_25)));
    U32 hoisted__U32_29 = ((U32)(a->count - hoisted__U32_26));
    I32 hoisted__I32_30 = memcmp(hoisted__v_27, hoisted__v_28, hoisted__U32_29);
    I32 hoisted__I32_31 = 0;
    Bool hoisted__Bool_32 = ((Bool)(hoisted__I32_30 == hoisted__I32_31));
    return hoisted__Bool_32;
}

static Str Str_with_capacity(USize n) {
    U32 hoisted__U32_1 = 0;
    Bool hoisted__Bool_2 = ((Bool)(n == hoisted__U32_1));
    if (hoisted__Bool_2) {
        { Str _ret = _til_str_lits.h000000001505; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
    }
    U32 hoisted__U32_3 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_3)));
    I32 hoisted__I32_4 = 0;
    U64 hoisted__U64_5 = 1ULL;
    memset(buf, hoisted__I32_4, hoisted__U64_5);
    Str hoisted__Str_Str_with_capacity_6 = {0};
    hoisted__Str_Str_with_capacity_6.c_str = buf;
    hoisted__Str_Str_with_capacity_6.count = 0;
    hoisted__Str_Str_with_capacity_6.cap = n;
    { Str _ret = hoisted__Str_Str_with_capacity_6; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_8 = 0;
    Bool hoisted__Bool_9 = ((Bool)(s->count == hoisted__U32_8));
    if (hoisted__Bool_9) {
        return;
    }
    Bool hoisted__Bool_10 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_10) {
        U32 hoisted__U32_0 = 1;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        static Str hoisted__Str_Str_push_str_2 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &hoisted__Str_Str_push_str_2, &_va_Array_0_ek);
        panic(&_va_Array_0, &hoisted__Str_Str_push_str_3);
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_11 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_11) {
        U32 hoisted__U32_4 = 1;
        Array__Str _va_Array_1 = Array__Str_new(hoisted__U32_4);
        I64 _va_Array_1_ek = 0;
        U32 hoisted__U32_5 = 0;
        static Str hoisted__Str_Str_push_str_6 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_1, hoisted__U32_5, &hoisted__Str_Str_push_str_6, &_va_Array_1_ek);
        panic(&_va_Array_1, &hoisted__Str_Str_push_str_7);
    }
    void *hoisted__v_12 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_12, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_13 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_14 = 0;
    U64 hoisted__U64_15 = 1ULL;
    memset(hoisted__v_13, hoisted__I32_14, hoisted__U64_15);
}

Str Str_clone(Str * val) {
    U32 hoisted__U32_1 = 0;
    Bool hoisted__Bool_2 = ((Bool)(val->count == hoisted__U32_1));
    if (hoisted__Bool_2) {
        { Str _ret = _til_str_lits.h000000001505; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
    }
    U32 hoisted__U32_3 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_3)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_4 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_5 = 0;
    U64 hoisted__U64_6 = 1ULL;
    memset(hoisted__v_4, hoisted__I32_5, hoisted__U64_6);
    Str hoisted__Str_Str_clone_7 = {0};
    hoisted__Str_Str_clone_7.c_str = new_data;
    hoisted__Str_Str_clone_7.count = val->count;
    hoisted__Str_Str_clone_7.cap = val->count;
    { Str _ret = hoisted__Str_Str_clone_7; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static Str Str_to_str(Str * self) {
    Str hoisted__Str_Str_to_str_0 = Str_clone(self);
    { Str _ret = hoisted__Str_Str_to_str_0; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_0 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_0) {
        free(self->c_str);
    }
    Bool hoisted__Bool_1 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_2 = ((Bool)((call_free) && (hoisted__Bool_1)));
    if (hoisted__Bool_2) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

static Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_0 = Str_eq(a, b);
    Bool hoisted__Bool_1 = ((Bool)(!(hoisted__Bool_0)));
    return hoisted__Bool_1;
}

static Array__Str Array__Str_new(USize cap) {
    U32 hoisted__U32_0 = 16;
    void * hoisted__v_1 = calloc(usize_to_uptr(cap), usize_to_uptr(hoisted__U32_0));
    Array__Str hoisted__Array__Str_2 = {0};
    hoisted__Array__Str_2.data = hoisted__v_1;
    hoisted__Array__Str_2.cap = cap;
    return hoisted__Array__Str_2;
}

static void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_Array__Str_unsafe_set_0 = ((Str *)((void *)((U8 *)(self->data) + (usize_to_uptr(((U32)(i * 16)))))));
    Str_delete(hoisted__Str_Array__Str_unsafe_set_0, 0);
    Str *hoisted__Str_Array__Str_unsafe_set_1 = ((Str *)((void *)((U8 *)(self->data) + (usize_to_uptr(((U32)(i * 16)))))));
    adopt__Str(hoisted__Str_Array__Str_unsafe_set_1, val);
}

static void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_1 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_1) {
        I64 hoisted__I64_0 = 1;
        *_err_kind = hoisted__I64_0;
    }
    I64 hoisted__I64_2 = 0;
    Bool hoisted__Bool_3 = ((Bool)(DEREF(_err_kind) == hoisted__I64_2));
    if (hoisted__Bool_3) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, (Bool){0});
    }
}

static void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_0 = self->cap;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U32 hoisted__U32_2 = 16;
            U32 hoisted__U32_3 = ((U32)(i * hoisted__U32_2));
            U64 hoisted__U64_4 = usize_to_uptr(hoisted__U32_3);
            Str *hoisted__Str_Array__Str_delete_5 = ((void *)((U8 *)(self->data) + (hoisted__U64_4)));
            Str_delete(hoisted__Str_Array__Str_delete_5, 0);
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

static Array__Str Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_9 = 16;
    U32 hoisted__U32_10 = ((U32)(self->cap * hoisted__U32_9));
    U8 *new_data = malloc(usize_to_uptr(hoisted__U32_10));
    {
        U32 _re_U32_0 = self->cap;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U32 hoisted__U32_2 = 16;
            U32 hoisted__U32_3 = ((U32)(i * hoisted__U32_2));
            U64 hoisted__U64_4 = usize_to_uptr(hoisted__U32_3);
            Str *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4)));
            Str cloned = Str_clone(src);
            U32 hoisted__U32_5 = 16;
            U32 hoisted__U32_6 = ((U32)(i * hoisted__U32_5));
            U64 hoisted__U64_7 = usize_to_uptr(hoisted__U32_6);
            void *hoisted__v_8 = ((void *)((U8 *)(new_data) + (hoisted__U64_7)));
            adopt__Str(hoisted__v_8, &cloned);
        }
    }
    Array__Str hoisted__Array__Str_11 = {0};
    hoisted__Array__Str_11.data = new_data;
    hoisted__Array__Str_11.cap = self->cap;
    return hoisted__Array__Str_11;
}

static void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_0 = self->count;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U32 hoisted__U32_2 = 16;
            U32 hoisted__U32_3 = ((U32)(i * hoisted__U32_2));
            Str *hoisted__Str_Vec__Str_clear_4 = ((void *)((U8 *)(self->data) + (hoisted__U32_3)));
            Str_delete(hoisted__Str_Vec__Str_clear_4, 0);
        }
    }
    U32 hoisted__U32_5 = 0;
    self->count = hoisted__U32_5;
}

static void Vec__Str_unsafe_set(Vec__Str * self, USize i, Str * val) {
    Str *hoisted__Str_Vec__Str_unsafe_set_0 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Str_delete(hoisted__Str_Vec__Str_unsafe_set_0, 0);
    Str *hoisted__Str_Vec__Str_unsafe_set_1 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    adopt__Str(hoisted__Str_Vec__Str_unsafe_set_1, val);
}

static void Vec__Str_set(Vec__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_1 = ((Bool)(i >= self->count));
    if (hoisted__Bool_1) {
        I64 hoisted__I64_0 = 1;
        *_err_kind = hoisted__I64_0;
    }
    I64 hoisted__I64_2 = 0;
    Bool hoisted__Bool_3 = ((Bool)(DEREF(_err_kind) == hoisted__I64_2));
    if (hoisted__Bool_3) {
        Vec__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, (Bool){0});
    }
}

static void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

static Vec__Str Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_8 = 0;
    Bool hoisted__Bool_9 = ((Bool)(self->cap == hoisted__U32_8));
    if (hoisted__Bool_9) {
        Vec__Str hoisted__Vec__Str_0 = {0};
        hoisted__Vec__Str_0.data = NULL;
        hoisted__Vec__Str_0.count = 0;
        hoisted__Vec__Str_0.cap = 0;
        return hoisted__Vec__Str_0;
    }
    U32 hoisted__U32_10 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_10)));
    {
        U32 _re_U32_1 = self->count;
        U32 _rc_U32_1 = 0;
        while (1) {
            Bool _wcond_Bool_2 = ((Bool)(_rc_U32_1 < _re_U32_1));
            if (_wcond_Bool_2) {
            } else {
                break;
            }
            U32 i = (_rc_U32_1);
            (++_rc_U32_1);
            U32 hoisted__U32_3 = 16;
            U32 hoisted__U32_4 = ((U32)(i * hoisted__U32_3));
            Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4)));
            Str cloned = Str_clone(src);
            U32 hoisted__U32_5 = 16;
            U32 hoisted__U32_6 = ((U32)(i * hoisted__U32_5));
            void *hoisted__v_7 = ((void *)((U8 *)(new_data) + (hoisted__U32_6)));
            adopt__Str(hoisted__v_7, &cloned);
        }
    }
    Vec__Str hoisted__Vec__Str_11 = {0};
    hoisted__Vec__Str_11.data = new_data;
    hoisted__Vec__Str_11.count = self->count;
    hoisted__Vec__Str_11.cap = self->cap;
    return hoisted__Vec__Str_11;
}

static void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_0 = 16;
    memcpy(dest, src, hoisted__U32_0);
    ((void)src);
}

static Str U32_to_str(U32 val) {
    I64 hoisted__I64_0 = U32_to_i64(val);
    Str hoisted__Str_U32_to_str_1 = I64_to_str(hoisted__I64_0);
    { Str _ret = hoisted__Str_U32_to_str_1; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static Str U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str hoisted__Str_U64_to_str_0 = ({ Str *_hp = (Str *)U64_to_str_ext(val); Str _hv = *_hp; if (_hp->cap != TIL_CAP_LIT) { free(_hp); } if (_hv.cap == TIL_CAP_LIT) { _hv.cap = TIL_CAP_VIEW; } _hv; });
    { Str _ret = hoisted__Str_U64_to_str_0; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static Str I64_to_str(I64 val) {
    I64 hoisted__I64_8 = 0;
    Bool hoisted__Bool_9 = ((Bool)(val < hoisted__I64_8));
    if (hoisted__Bool_9) {
        U64 hoisted__U64_0 = 0ULL;
        U64 hoisted__U64_1 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_0 - hoisted__U64_1));
        U32 hoisted__U32_2 = 2;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_2);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_3 = 0;
        static Str hoisted__Str_I64_to_str_4 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_0, hoisted__U32_3, &hoisted__Str_I64_to_str_4, &_va_Array_0_ek);
        U32 hoisted__U32_5 = 1;
        Str hoisted__Str_I64_to_str_6 = U64_to_str(mag);
        Array__Str_set(&_va_Array_0, hoisted__U32_5, &hoisted__Str_I64_to_str_6, &_va_Array_0_ek);
        Str hoisted__Str_I64_to_str_7 = format(&_va_Array_0);
        { Str _ret = hoisted__Str_I64_to_str_7; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
    }
    U64 hoisted__U64_10 = (U64)(val);
    Str hoisted__Str_I64_to_str_11 = U64_to_str(hoisted__U64_10);
    { Str _ret = hoisted__Str_I64_to_str_11; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

static UPtr usize_to_uptr(USize val) {
    U64 hoisted__U64_0 = (U64)(val);
    return hoisted__U64_0;
}

static __attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_0 = 3;
    Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
    I64 _va_Array_0_ek = 0;
    U32 hoisted__U32_1 = 0;
    Str hoisted__Str_panic_2 = Str_clone(loc);
    Array__Str_set(&_va_Array_0, hoisted__U32_1, &hoisted__Str_panic_2, &_va_Array_0_ek);
    U32 hoisted__U32_3 = 1;
    static Str hoisted__Str_panic_4 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_0, hoisted__U32_3, &hoisted__Str_panic_4, &_va_Array_0_ek);
    Array__Str hoisted__Array__Str_5 = Array__Str_clone(parts);
    U32 hoisted__U32_6 = 2;
    Str hoisted__Str_panic_7 = format(&hoisted__Array__Str_5);
    Array__Str_set(&_va_Array_0, hoisted__U32_6, &hoisted__Str_panic_7, &_va_Array_0_ek);
    println(&_va_Array_0);
    Array__Str_delete(parts, (Bool){0});
    I64 hoisted__I64_8 = 1;
    exit(hoisted__I64_8);
}

static __attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_9 = (parts->cap);
    U32 hoisted__U32_10 = 0;
    Bool hoisted__Bool_11 = ((Bool)(hoisted__U32_9 == hoisted__U32_10));
    if (hoisted__Bool_11) {
        U32 hoisted__U32_0 = 1;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        static Str hoisted__Str_UNREACHABLE_2 = (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &hoisted__Str_UNREACHABLE_2, &_va_Array_0_ek);
        panic(&_va_Array_0, loc);
    } else {
        U32 hoisted__U32_3 = 2;
        Array__Str _va_Array_1 = Array__Str_new(hoisted__U32_3);
        I64 _va_Array_1_ek = 0;
        U32 hoisted__U32_4 = 0;
        static Str hoisted__Str_UNREACHABLE_5 = (Str){.c_str = (void *)"unreachable: ", .count = 13ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_1, hoisted__U32_4, &hoisted__Str_UNREACHABLE_5, &_va_Array_1_ek);
        Array__Str hoisted__Array__Str_6 = Array__Str_clone(parts);
        U32 hoisted__U32_7 = 1;
        Str hoisted__Str_UNREACHABLE_8 = format(&hoisted__Array__Str_6);
        Array__Str_set(&_va_Array_1, hoisted__U32_7, &hoisted__Str_UNREACHABLE_8, &_va_Array_1_ek);
        panic(&_va_Array_1, loc);
    }
    Array__Str_delete(parts, (Bool){0});
}

static void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_3 = ((Bool)(!(cond)));
    if (hoisted__Bool_3) {
        U32 hoisted__U32_0 = 1;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        static Str hoisted__Str_assert_2 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &hoisted__Str_assert_2, &_va_Array_0_ek);
        panic(&_va_Array_0, loc);
    }
}

static void expect(Bool cond, Array__Str * parts, Str * loc) {
    Bool hoisted__Bool_6 = ((Bool)(!(cond)));
    if (hoisted__Bool_6) {
        U32 hoisted__U32_0 = 2;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        static Str hoisted__Str_expect_2 = (Str){.c_str = (void *)"assert failed: ", .count = 15ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &hoisted__Str_expect_2, &_va_Array_0_ek);
        Array__Str hoisted__Array__Str_3 = Array__Str_clone(parts);
        U32 hoisted__U32_4 = 1;
        Str hoisted__Str_expect_5 = format(&hoisted__Array__Str_3);
        Array__Str_set(&_va_Array_0, hoisted__U32_4, &hoisted__Str_expect_5, &_va_Array_0_ek);
        panic(&_va_Array_0, loc);
    }
    Array__Str_delete(parts, (Bool){0});
}

static void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_0 = parts;
        USize _fi_USize_0 = 0;
        while (1) {
            U32 hoisted__U32_2 = (_fc_Array__Str_0->cap);
            Bool _wcond_Bool_1 = ((Bool)(_fi_USize_0 < hoisted__U32_2));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_0->data) + (usize_to_uptr(((U32)(_fi_USize_0 * 16)))))));
            U32 hoisted__U32_3 = 1;
            U32 hoisted__U32_4 = ((U32)(_fi_USize_0 + hoisted__U32_3));
            _fi_USize_0 = hoisted__U32_4;
            print_single(s);
        }
    }
    Array__Str_delete(parts, (Bool){0});
    print_flush();
}

static void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_2 = 3;
    assert_eq__I64(result, hoisted__I64_2, &hoisted__Str_test_simple_add_3);
}

static void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6 = 15;
    assert_eq__I64(result, hoisted__I64_6, &hoisted__Str_test_nested_arithmetic_7);
}

static void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6 = 26;
    assert_eq__I64(result, hoisted__I64_6, &hoisted__Str_test_deeply_nested_7);
}

static void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&result, &_til_str_lits.h3fd43551c8c1, &hoisted__Str_test_string_concat_3);
}

static void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r, &_til_str_lits.h3fd43551c8c1, &hoisted__Str_test_variadic_fold_3);
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_test_variadic_fold_7 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r2, &hoisted__Str_test_variadic_fold_7, &hoisted__Str_test_variadic_fold_8);
}

static void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_test_variadic_direct_fold_11 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d, &hoisted__Str_test_variadic_direct_fold_11, &hoisted__Str_test_variadic_direct_fold_12);
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_test_variadic_direct_fold_20 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d2, &hoisted__Str_test_variadic_direct_fold_20, &hoisted__Str_test_variadic_direct_fold_21);
    I64 d3 = 106;
    I64 hoisted__I64_30 = 106;
    assert_eq__I64(d3, hoisted__I64_30, &hoisted__Str_test_variadic_direct_fold_31);
}

static void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_test_lolalalo_8);
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_test_lolalalo_9);
}

static void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_1 = 8;
    assert_eq__I64(result, hoisted__I64_1, &hoisted__Str_test_fold_variable_2);
}

static void test_loc_folded(void) {
    Bool hoisted__Bool_2 = 1;
    assert(hoisted__Bool_2, &hoisted__Str_test_loc_folded_3);
    Bool hoisted__Bool_6 = 1;
    assert(hoisted__Bool_6, &hoisted__Str_test_loc_folded_7);
}

static void test_fold_f32(void) {
    assert_eq__Str(&_til_str_lits.h00017c7b7650, &_til_str_lits.h00017c7b7650, &hoisted__Str_test_fold_f32_4);
    assert_eq__Str(&_til_str_lits.h00000b8791fb, &_til_str_lits.h00000b8791fb, &hoisted__Str_test_fold_f32_9);
}

static void test_struct_fold_simple(void) {
    CfVec2 v = {0};
    v.x = 42;
    v.y = 99;
    I64 hoisted__I64_0 = 42;
    assert_eq__I64(v.x, hoisted__I64_0, &hoisted__Str_test_struct_fold_simple_1);
    I64 hoisted__I64_2 = 99;
    assert_eq__I64(v.y, hoisted__I64_2, &hoisted__Str_test_struct_fold_simple_3);
}

static void test_struct_fold_values(void) {
    CfVec2 p = {0};
    p.x = 10;
    p.y = 20;
    I64 hoisted__I64_2 = 10;
    assert_eq__I64(p.x, hoisted__I64_2, &hoisted__Str_test_struct_fold_values_3);
    I64 hoisted__I64_4 = 20;
    assert_eq__I64(p.y, hoisted__I64_4, &hoisted__Str_test_struct_fold_values_5);
    I64 hoisted__I64_6 = 42;
    assert_eq__I64(CfVec2_answer, hoisted__I64_6, &hoisted__Str_test_struct_fold_values_7);
    I64 hoisted__I64_8 = 43;
    assert_eq__I64(CfVec2_forward, hoisted__I64_8, &hoisted__Str_test_struct_fold_values_9);
    I64 hoisted__I64_10 = 6;
    assert_eq__I64(CfVec2_sample_value.x, hoisted__I64_10, &hoisted__Str_test_struct_fold_values_11);
    I64 hoisted__I64_12 = 7;
    assert_eq__I64(CfVec2_sample_value.y, hoisted__I64_12, &hoisted__Str_test_struct_fold_values_13);
}

static void test_struct_fold_nested(void) {
    CfRect r = {0};
    r.top_left = ({ CfVec2 _sc1 = {0};     _sc1.x = 5;
    _sc1.y = 10;
 _sc1; });
    r.bottom_right = ({ CfVec2 _sc2 = {0};     _sc2.x = 100;
    _sc2.y = 200;
 _sc2; });
    I64 hoisted__I64_0 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_0, &hoisted__Str_test_struct_fold_nested_1);
    I64 hoisted__I64_2 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_2, &hoisted__Str_test_struct_fold_nested_3);
    I64 hoisted__I64_4 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_4, &hoisted__Str_test_struct_fold_nested_5);
    I64 hoisted__I64_6 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6, &hoisted__Str_test_struct_fold_nested_7);
}

static void test_struct_fold_f32(void) {
    CfVec3f v = {0};
    v.x = 3;
    v.y = 4;
    v.z = 5;
    Str hoisted__Str_test_struct_fold_f32_3 = ({ Str *_hp = (Str *)F32_to_str(v.x); Str _hv = *_hp; if (_hp->cap != TIL_CAP_LIT) { free(_hp); } if (_hv.cap == TIL_CAP_LIT) { _hv.cap = TIL_CAP_VIEW; } _hv; });
    static Str hoisted__Str_test_struct_fold_f32_4 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&hoisted__Str_test_struct_fold_f32_3, &hoisted__Str_test_struct_fold_f32_4, &hoisted__Str_test_struct_fold_f32_5);
    Str_delete(&hoisted__Str_test_struct_fold_f32_3, (Bool){0});
    Str hoisted__Str_test_struct_fold_f32_6 = ({ Str *_hp = (Str *)F32_to_str(v.y); Str _hv = *_hp; if (_hp->cap != TIL_CAP_LIT) { free(_hp); } if (_hv.cap == TIL_CAP_LIT) { _hv.cap = TIL_CAP_VIEW; } _hv; });
    static Str hoisted__Str_test_struct_fold_f32_7 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&hoisted__Str_test_struct_fold_f32_6, &hoisted__Str_test_struct_fold_f32_7, &hoisted__Str_test_struct_fold_f32_8);
    Str_delete(&hoisted__Str_test_struct_fold_f32_6, (Bool){0});
    Str hoisted__Str_test_struct_fold_f32_9 = ({ Str *_hp = (Str *)F32_to_str(v.z); Str _hv = *_hp; if (_hp->cap != TIL_CAP_LIT) { free(_hp); } if (_hv.cap == TIL_CAP_LIT) { _hv.cap = TIL_CAP_VIEW; } _hv; });
    static Str hoisted__Str_test_struct_fold_f32_10 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&hoisted__Str_test_struct_fold_f32_9, &hoisted__Str_test_struct_fold_f32_10, &hoisted__Str_test_struct_fold_f32_11);
    Str_delete(&hoisted__Str_test_struct_fold_f32_9, (Bool){0});
}

static Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_0 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_0;
}

static Color Color_clone(Color * self) {
    Bool hoisted__Bool_0 = ((Bool)((((Color *)(self))->tag) == Color_TAG_Red));
    if (hoisted__Bool_0) {
        return (Color){.tag = Color_TAG_Red};
    }
    Bool hoisted__Bool_1 = ((Bool)((((Color *)(self))->tag) == Color_TAG_Green));
    if (hoisted__Bool_1) {
        return (Color){.tag = Color_TAG_Green};
    }
    Bool hoisted__Bool_2 = ((Bool)((((Color *)(self))->tag) == Color_TAG_Blue));
    if (hoisted__Bool_2) {
        return (Color){.tag = Color_TAG_Blue};
    }
    U32 hoisted__U32_3 = 0;
    Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_3);
    I64 _va_Array_0_ek = 0;
    (void)_va_Array_0_ek;
    static Str hoisted__Str_Color_clone_4 = (Str){.c_str = (void *)"Color.clone:245:1", .count = 17ULL, .cap = TIL_CAP_LIT};
    UNREACHABLE(&_va_Array_0, &hoisted__Str_Color_clone_4);
    return (Color){.tag = Color_TAG_Red};
}


static void test_enum_fold(void) {
    Color c = Color_clone(&(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_0 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_0, &hoisted__Str_test_enum_fold_1);
    Bool hoisted__Bool_2 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_3 = ((Bool)(!(hoisted__Bool_2)));
    assert(hoisted__Bool_3, &hoisted__Str_test_enum_fold_4);
}

static void test_enum_literal_fold(void) {
    Str _m_Str_0 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
    {
        Bool hoisted__Bool_3 = ((Bool)(1));
        if (hoisted__Bool_3) {
            { Str _new = _til_str_lits.h00000002b617; Str_delete(&_m_Str_0, (Bool){0}); _m_Str_0 = _new; }
        } else {
            Bool hoisted__Bool_2 = ((Bool)(0));
            if (hoisted__Bool_2) {
                { Str _new = (Str){.c_str=(void*)"g", .count=1ULL, .cap=TIL_CAP_LIT}; Str_delete(&_m_Str_0, (Bool){0}); _m_Str_0 = _new; }
            } else {
                Bool hoisted__Bool_1 = ((Bool)(0));
                if (hoisted__Bool_1) {
                    { Str _new = _til_str_lits.h00000002b607; Str_delete(&_m_Str_0, (Bool){0}); _m_Str_0 = _new; }
                } else {
                    { Str _new = _til_str_lits.h00000002b607; Str_delete(&_m_Str_0, (Bool){0}); _m_Str_0 = _new; }
                }
            }
        }
    }
    assert_eq__Str(&_m_Str_0, &_til_str_lits.h00000002b617, &hoisted__Str_test_enum_literal_fold_5);
    Str_delete(&_m_Str_0, (Bool){0});
    Bool hoisted__Bool_6 = ((Bool)(1));
    assert(hoisted__Bool_6, &hoisted__Str_test_enum_literal_fold_7);
    Bool hoisted__Bool_8 = ((Bool)(0));
    Bool hoisted__Bool_9 = ((Bool)(!(hoisted__Bool_8)));
    assert(hoisted__Bool_9, &hoisted__Str_test_enum_literal_fold_10);
}

static Token Token_Num(I64 * val) {
    Token r = {0};
    r.tag = Token_TAG_Num;
    r.data.Num = *val;
    return r;
}
static void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_1 = ((Bool)((((Token *)(self))->tag) == Token_TAG_Name));
    if (hoisted__Bool_1) {
        Str *hoisted__Str_Token_delete_0 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Str_delete(hoisted__Str_Token_delete_0, 0);
    }
    if (call_free) {
        free(self);
    }
}


static void test_enum_payload_fold(void) {
    Token t = Token_Num(&(I64){42});
    Bool hoisted__Bool_1 = ((Bool)((((Token *)(&t))->tag) == Token_TAG_Num));
    assert(hoisted__Bool_1, &hoisted__Str_test_enum_payload_fold_2);
    Bool hoisted__Bool_3 = ((Bool)((((Token *)(&t))->tag) == Token_TAG_Eof));
    Bool hoisted__Bool_4 = ((Bool)(!(hoisted__Bool_3)));
    assert(hoisted__Bool_4, &hoisted__Str_test_enum_payload_fold_5);
    Token_delete(&t, (Bool){0});
}

static void test_enum_return_fold(void) {
    Color c = Color_clone(&(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_0 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_0, &hoisted__Str_test_enum_return_fold_1);
    Bool hoisted__Bool_2 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_3 = ((Bool)(!(hoisted__Bool_2)));
    assert(hoisted__Bool_3, &hoisted__Str_test_enum_return_fold_4);
}

static void test_enum_payload_return_fold(void) {
    Token t = Token_Num(&(I64){7});
    Bool hoisted__Bool_1 = ((Bool)((((Token *)(&t))->tag) == Token_TAG_Num));
    assert(hoisted__Bool_1, &hoisted__Str_test_enum_payload_return_fold_2);
    Bool hoisted__Bool_3 = ((Bool)((((Token *)(&t))->tag) == Token_TAG_Eof));
    Bool hoisted__Bool_4 = ((Bool)(!(hoisted__Bool_3)));
    assert(hoisted__Bool_4, &hoisted__Str_test_enum_payload_return_fold_5);
    Token_delete(&t, (Bool){0});
}

static WideToken WideToken_Num(I64 * val) {
    WideToken r = {0};
    r.tag = WideToken_TAG_Num;
    r.data.Num = *val;
    return r;
}
static void WideToken_delete(WideToken * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

static WideToken WideToken_clone(WideToken * self) {
    Bool hoisted__Bool_1 = ((Bool)((((WideToken *)(self))->tag) == WideToken_TAG_Num));
    if (hoisted__Bool_1) {
        I64 *_clone_payload_Num_0 = ((void *)((U8 *)(self) + offsetof(WideToken, data)));
        WideToken hoisted__WideToken_0 = WideToken_Num(_clone_payload_Num_0);
        return hoisted__WideToken_0;
    }
    return (WideToken){.tag = WideToken_TAG_Eof};
}


static NestedToken NestedToken_Inner(WideToken * val) {
    NestedToken r;
    r.data = val;
    return r;
}
static void NestedToken_delete(NestedToken * self, Bool call_free) {
    Bool hoisted__Bool_1 = ((Bool)((((NestedToken *)(self))->data != NULL) == 1));
    if (hoisted__Bool_1) {
        WideToken *hoisted__WideToken_0 = ((void *)((NestedToken *)(self))->data);
        WideToken_delete(hoisted__WideToken_0, 1);
    }
    if (call_free) {
        free(self);
    }
}


static void test_explicit_tag_enum_return_fold(void) {
    WideToken number = WideToken_Num(&(I64){7});
    switch ((number).tag) {
    case WideToken_TAG_Num: {
        I64 *value = ((void *)((U8 *)(&number) + offsetof(WideToken, data)));
        I64 hoisted__I64_0 = 7;
        assert_eq__I64(DEREF(value), hoisted__I64_0, &hoisted__Str_test_explicit_tag_enum_return_fold_1);
        break;
    }
    default: {
        U32 hoisted__U32_2 = 0;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_2);
        (void)_va_Array_0;
        I64 _va_Array_0_ek = 0;
        (void)_va_Array_0_ek;
        UNREACHABLE(&_va_Array_0, &hoisted__Str_test_explicit_tag_enum_return_fold_3);
        break;
    }
    }
    WideToken eof = WideToken_clone(&(WideToken){.tag = WideToken_TAG_Eof});
    Bool hoisted__Bool_5 = ((Bool)((((WideToken *)(&eof))->tag) == WideToken_TAG_Eof));
    assert(hoisted__Bool_5, &hoisted__Str_test_explicit_tag_enum_return_fold_6);
}

static void test_nested_enum_payload_return_fold(void) {
    NestedToken nested = NestedToken_Inner(({ WideToken *_oa = malloc(TIL_BOX(WideToken)); *_oa = WideToken_Num(&(I64){9}); _oa; }));
    switch ((int)((nested).data != NULL)) {
    case 1: {
        WideToken *inner_token = ((void *)((NestedToken *)(&nested))->data);
        switch ((DEREF(inner_token)).tag) {
        case WideToken_TAG_Num: {
            I64 *value = ((void *)((U8 *)(inner_token) + offsetof(WideToken, data)));
            I64 hoisted__I64_0 = 9;
            assert_eq__I64(DEREF(value), hoisted__I64_0, &hoisted__Str_test_nested_enum_payload_return_fold_1);
            break;
        }
        default: {
            U32 hoisted__U32_2 = 0;
            Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_2);
            (void)_va_Array_0;
            I64 _va_Array_0_ek = 0;
            (void)_va_Array_0_ek;
            UNREACHABLE(&_va_Array_0, &hoisted__Str_test_nested_enum_payload_return_fold_3);
            break;
        }
        }
        break;
    }
    default: {
        U32 hoisted__U32_4 = 0;
        Array__Str _va_Array_1 = Array__Str_new(hoisted__U32_4);
        (void)_va_Array_1;
        I64 _va_Array_1_ek = 0;
        (void)_va_Array_1_ek;
        UNREACHABLE(&_va_Array_1, &hoisted__Str_test_nested_enum_payload_return_fold_5);
        break;
    }
    }
    NestedToken_delete(&nested, (Bool){0});
}

static CfNestedValues CfNestedValues_clone(CfNestedValues * self) {
    CfNestedValues hoisted__CfNestedValues_0 = {0};
    hoisted__CfNestedValues_0.values = Vec__I64_clone(&self->values);
    return hoisted__CfNestedValues_0;
}

static void CfNestedValues_delete(CfNestedValues * self, Bool call_free) {
    Vec__I64_delete(&self->values, 0);
    if (call_free) {
        free(self);
    }
}

static void test_collection_return_fold(void) {
    I64 _err_kind = 0;
    Vec__I64 values = Vec__I64_clone(&_til_precomputed_sequence_23);
    U32 hoisted__U32_70 = 2;
    U32 hoisted__U32_71 = 2;
    assert_eq__USize(hoisted__U32_70, hoisted__U32_71, &hoisted__Str_test_collection_return_fold_72);
    U32 hoisted__U32_73 = 4;
    assert_eq__USize(values.cap, hoisted__U32_73, &hoisted__Str_test_collection_return_fold_74);
    U32 hoisted__U32_75 = 0;
    I64 *_bang_ret_0 = (((Bool)(hoisted__U32_75 < values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(values.data) + (((U32)(hoisted__U32_75 * 8)))))) : (_err_kind = 1, (I64 *)NULL));
    I64 hoisted__I64_76 = 1;
    Bool hoisted__Bool_77 = ((Bool)(_err_kind == hoisted__I64_76));
    if (hoisted__Bool_77) {
        I64 hoisted__I64_0 = 0;
        _err_kind = hoisted__I64_0;
        U32 hoisted__U32_1 = 1;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_1);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_2 = 0;
        Array__Str_set(&_va_Array_0, hoisted__U32_2, &_til_str_lits.h4d3ab87300de, &_va_Array_0_ek);
        panic(&_va_Array_0, &hoisted__Str_test_collection_return_fold_4);
    }
    I64 hoisted__I64_78 = 11;
    assert_eq__I64(DEREF(_bang_ret_0), hoisted__I64_78, &hoisted__Str_test_collection_return_fold_79);
    U32 hoisted__U32_80 = 1;
    I64 *_bang_ret_1 = (((Bool)(hoisted__U32_80 < values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(values.data) + (((U32)(hoisted__U32_80 * 8)))))) : (_err_kind = 1, (I64 *)NULL));
    I64 hoisted__I64_81 = 1;
    Bool hoisted__Bool_82 = ((Bool)(_err_kind == hoisted__I64_81));
    if (hoisted__Bool_82) {
        I64 hoisted__I64_5 = 0;
        _err_kind = hoisted__I64_5;
        U32 hoisted__U32_6 = 1;
        Array__Str _va_Array_1 = Array__Str_new(hoisted__U32_6);
        I64 _va_Array_1_ek = 0;
        U32 hoisted__U32_7 = 0;
        Array__Str_set(&_va_Array_1, hoisted__U32_7, &_til_str_lits.h4d3ab87300de, &_va_Array_1_ek);
        panic(&_va_Array_1, &hoisted__Str_test_collection_return_fold_9);
    }
    I64 hoisted__I64_83 = 22;
    assert_eq__I64(DEREF(_bang_ret_1), hoisted__I64_83, &hoisted__Str_test_collection_return_fold_84);
    Vec__I64_delete(&values, (Bool){0});
    Vec__I64 empty = Vec__I64_clone(&_til_precomputed_sequence_24);
    U32 hoisted__U32_85 = 0;
    U32 hoisted__U32_86 = 0;
    assert_eq__USize(hoisted__U32_85, hoisted__U32_86, &hoisted__Str_test_collection_return_fold_87);
    U32 hoisted__U32_88 = 0;
    assert_eq__USize(empty.cap, hoisted__U32_88, &hoisted__Str_test_collection_return_fold_89);
    Vec__I64_delete(&empty, (Bool){0});
    Array__I64 fixed = Array__I64_clone(&_til_precomputed_sequence_25);
    U32 hoisted__U32_90 = 3;
    U32 hoisted__U32_91 = 3;
    assert_eq__USize(hoisted__U32_90, hoisted__U32_91, &hoisted__Str_test_collection_return_fold_92);
    U32 hoisted__U32_93 = 0;
    I64 *_bang_ret_2 = (((Bool)(hoisted__U32_93 < fixed.cap)) ? (I64 *)((I64 *)((void *)((U8 *)(fixed.data) + (usize_to_uptr(((U32)(hoisted__U32_93 * 8))))))) : (_err_kind = 1, (I64 *)NULL));
    I64 hoisted__I64_94 = 1;
    Bool hoisted__Bool_95 = ((Bool)(_err_kind == hoisted__I64_94));
    if (hoisted__Bool_95) {
        I64 hoisted__I64_10 = 0;
        _err_kind = hoisted__I64_10;
        U32 hoisted__U32_11 = 1;
        Array__Str _va_Array_2 = Array__Str_new(hoisted__U32_11);
        I64 _va_Array_2_ek = 0;
        U32 hoisted__U32_12 = 0;
        Array__Str_set(&_va_Array_2, hoisted__U32_12, &_til_str_lits.h4d3ab87300de, &_va_Array_2_ek);
        panic(&_va_Array_2, &hoisted__Str_test_collection_return_fold_14);
    }
    I64 hoisted__I64_96 = 3;
    assert_eq__I64(DEREF(_bang_ret_2), hoisted__I64_96, &hoisted__Str_test_collection_return_fold_97);
    U32 hoisted__U32_98 = 2;
    I64 *_bang_ret_3 = (((Bool)(hoisted__U32_98 < fixed.cap)) ? (I64 *)((I64 *)((void *)((U8 *)(fixed.data) + (usize_to_uptr(((U32)(hoisted__U32_98 * 8))))))) : (_err_kind = 1, (I64 *)NULL));
    I64 hoisted__I64_99 = 1;
    Bool hoisted__Bool_100 = ((Bool)(_err_kind == hoisted__I64_99));
    if (hoisted__Bool_100) {
        I64 hoisted__I64_15 = 0;
        _err_kind = hoisted__I64_15;
        U32 hoisted__U32_16 = 1;
        Array__Str _va_Array_3 = Array__Str_new(hoisted__U32_16);
        I64 _va_Array_3_ek = 0;
        U32 hoisted__U32_17 = 0;
        Array__Str_set(&_va_Array_3, hoisted__U32_17, &_til_str_lits.h4d3ab87300de, &_va_Array_3_ek);
        panic(&_va_Array_3, &hoisted__Str_test_collection_return_fold_19);
    }
    I64 hoisted__I64_101 = 8;
    assert_eq__I64(DEREF(_bang_ret_3), hoisted__I64_101, &hoisted__Str_test_collection_return_fold_102);
    Array__I64_delete(&fixed, (Bool){0});
    Map__Str_I64 table = {0};
    table.keys = Vec__Str_clone(&_til_precomputed_sequence_26);
    table.values = Vec__I64_clone(&_til_precomputed_sequence_27);
    U32 hoisted__U32_103 = 2;
    U32 hoisted__U32_104 = 2;
    assert_eq__USize(hoisted__U32_103, hoisted__U32_104, &hoisted__Str_test_collection_return_fold_105);
    I64 *_bang_ret_4 = Map__Str_I64_get(&table, &_til_str_lits.h00000002b606, &_err_kind);
    I64 hoisted__I64_107 = 4;
    Bool hoisted__Bool_108 = ((Bool)(_err_kind == hoisted__I64_107));
    if (hoisted__Bool_108) {
        I64 hoisted__I64_20 = 0;
        _err_kind = hoisted__I64_20;
        U32 hoisted__U32_21 = 1;
        Array__Str _va_Array_4 = Array__Str_new(hoisted__U32_21);
        I64 _va_Array_4_ek = 0;
        U32 hoisted__U32_22 = 0;
        Array__Str_set(&_va_Array_4, hoisted__U32_22, &_til_str_lits.hd0e435b6dffc, &_va_Array_4_ek);
        panic(&_va_Array_4, &hoisted__Str_test_collection_return_fold_24);
    }
    I64 hoisted__I64_109 = 10;
    assert_eq__I64(DEREF(_bang_ret_4), hoisted__I64_109, &hoisted__Str_test_collection_return_fold_110);
    I64 *_bang_ret_5 = Map__Str_I64_get(&table, &_til_str_lits.h00000002b607, &_err_kind);
    I64 hoisted__I64_112 = 4;
    Bool hoisted__Bool_113 = ((Bool)(_err_kind == hoisted__I64_112));
    if (hoisted__Bool_113) {
        I64 hoisted__I64_25 = 0;
        _err_kind = hoisted__I64_25;
        U32 hoisted__U32_26 = 1;
        Array__Str _va_Array_5 = Array__Str_new(hoisted__U32_26);
        I64 _va_Array_5_ek = 0;
        U32 hoisted__U32_27 = 0;
        Array__Str_set(&_va_Array_5, hoisted__U32_27, &_til_str_lits.hd0e435b6dffc, &_va_Array_5_ek);
        panic(&_va_Array_5, &hoisted__Str_test_collection_return_fold_29);
    }
    I64 hoisted__I64_114 = 20;
    assert_eq__I64(DEREF(_bang_ret_5), hoisted__I64_114, &hoisted__Str_test_collection_return_fold_115);
    Map__Str_I64_delete(&table, (Bool){0});
    Vec__CfNestedValues nested = Vec__CfNestedValues_clone(&_til_precomputed_sequence_30);
    U32 hoisted__U32_116 = 2;
    U32 hoisted__U32_117 = 2;
    assert_eq__USize(hoisted__U32_116, hoisted__U32_117, &hoisted__Str_test_collection_return_fold_118);
    U32 hoisted__U32_119 = 0;
    CfNestedValues *first_nested = (((Bool)(hoisted__U32_119 < nested.count)) ? (CfNestedValues *)((CfNestedValues *)((void *)((U8 *)(nested.data) + (((U32)(hoisted__U32_119 * 16)))))) : (_err_kind = 1, (CfNestedValues *)NULL));
    I64 hoisted__I64_120 = 1;
    Bool hoisted__Bool_121 = ((Bool)(_err_kind == hoisted__I64_120));
    if (hoisted__Bool_121) {
        I64 hoisted__I64_30 = 0;
        _err_kind = hoisted__I64_30;
        U32 hoisted__U32_31 = 1;
        Array__Str _va_Array_6 = Array__Str_new(hoisted__U32_31);
        I64 _va_Array_6_ek = 0;
        U32 hoisted__U32_32 = 0;
        Array__Str_set(&_va_Array_6, hoisted__U32_32, &_til_str_lits.h4d3ab87300de, &_va_Array_6_ek);
        panic(&_va_Array_6, &hoisted__Str_test_collection_return_fold_34);
    }
    U32 hoisted__U32_122 = 1;
    CfNestedValues *second_nested = (((Bool)(hoisted__U32_122 < nested.count)) ? (CfNestedValues *)((CfNestedValues *)((void *)((U8 *)(nested.data) + (((U32)(hoisted__U32_122 * 16)))))) : (_err_kind = 1, (CfNestedValues *)NULL));
    I64 hoisted__I64_123 = 1;
    Bool hoisted__Bool_124 = ((Bool)(_err_kind == hoisted__I64_123));
    if (hoisted__Bool_124) {
        I64 hoisted__I64_35 = 0;
        _err_kind = hoisted__I64_35;
        U32 hoisted__U32_36 = 1;
        Array__Str _va_Array_7 = Array__Str_new(hoisted__U32_36);
        I64 _va_Array_7_ek = 0;
        U32 hoisted__U32_37 = 0;
        Array__Str_set(&_va_Array_7, hoisted__U32_37, &_til_str_lits.h4d3ab87300de, &_va_Array_7_ek);
        panic(&_va_Array_7, &hoisted__Str_test_collection_return_fold_39);
    }
    U32 hoisted__U32_125 = 1;
    I64 *_bang_ret_6 = (((Bool)(hoisted__U32_125 < first_nested->values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(first_nested->values.data) + (((U32)(hoisted__U32_125 * 8)))))) : (_err_kind = 1, (I64 *)NULL));
    I64 hoisted__I64_126 = 1;
    Bool hoisted__Bool_127 = ((Bool)(_err_kind == hoisted__I64_126));
    if (hoisted__Bool_127) {
        I64 hoisted__I64_40 = 0;
        _err_kind = hoisted__I64_40;
        U32 hoisted__U32_41 = 1;
        Array__Str _va_Array_8 = Array__Str_new(hoisted__U32_41);
        I64 _va_Array_8_ek = 0;
        U32 hoisted__U32_42 = 0;
        Array__Str_set(&_va_Array_8, hoisted__U32_42, &_til_str_lits.h4d3ab87300de, &_va_Array_8_ek);
        panic(&_va_Array_8, &hoisted__Str_test_collection_return_fold_44);
    }
    I64 hoisted__I64_128 = 2;
    assert_eq__I64(DEREF(_bang_ret_6), hoisted__I64_128, &hoisted__Str_test_collection_return_fold_129);
    U32 hoisted__U32_130 = 0;
    I64 *_bang_ret_7 = (((Bool)(hoisted__U32_130 < second_nested->values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(second_nested->values.data) + (((U32)(hoisted__U32_130 * 8)))))) : (_err_kind = 1, (I64 *)NULL));
    I64 hoisted__I64_131 = 1;
    Bool hoisted__Bool_132 = ((Bool)(_err_kind == hoisted__I64_131));
    if (hoisted__Bool_132) {
        I64 hoisted__I64_45 = 0;
        _err_kind = hoisted__I64_45;
        U32 hoisted__U32_46 = 1;
        Array__Str _va_Array_9 = Array__Str_new(hoisted__U32_46);
        I64 _va_Array_9_ek = 0;
        U32 hoisted__U32_47 = 0;
        Array__Str_set(&_va_Array_9, hoisted__U32_47, &_til_str_lits.h4d3ab87300de, &_va_Array_9_ek);
        panic(&_va_Array_9, &hoisted__Str_test_collection_return_fold_49);
    }
    I64 hoisted__I64_133 = 3;
    assert_eq__I64(DEREF(_bang_ret_7), hoisted__I64_133, &hoisted__Str_test_collection_return_fold_134);
    Vec__Str left = Vec__Str_clone(&_til_precomputed_sequence_31);
    Vec__Str right = Vec__Str_clone(&_til_precomputed_sequence_32);
    U32 hoisted__U32_135 = 0;
    Vec__Str_set(&left, hoisted__U32_135, &_til_str_lits.hd0b1c236fb8f, &_err_kind);
    I64 hoisted__I64_137 = 1;
    Bool hoisted__Bool_138 = ((Bool)(_err_kind == hoisted__I64_137));
    if (hoisted__Bool_138) {
        I64 hoisted__I64_50 = 0;
        _err_kind = hoisted__I64_50;
        U32 hoisted__U32_51 = 1;
        Array__Str _va_Array_10 = Array__Str_new(hoisted__U32_51);
        I64 _va_Array_10_ek = 0;
        U32 hoisted__U32_52 = 0;
        Array__Str_set(&_va_Array_10, hoisted__U32_52, &_til_str_lits.h4d3ab87300de, &_va_Array_10_ek);
        panic(&_va_Array_10, &hoisted__Str_test_collection_return_fold_54);
    }
    U32 hoisted__U32_139 = 0;
    Str *_bang_ret_8 = (((Bool)(hoisted__U32_139 < left.count)) ? (Str *)((Str *)((void *)((U8 *)(left.data) + (((U32)(hoisted__U32_139 * 16)))))) : (_err_kind = 1, (Str *)NULL));
    I64 hoisted__I64_140 = 1;
    Bool hoisted__Bool_141 = ((Bool)(_err_kind == hoisted__I64_140));
    if (hoisted__Bool_141) {
        I64 hoisted__I64_55 = 0;
        _err_kind = hoisted__I64_55;
        U32 hoisted__U32_56 = 1;
        Array__Str _va_Array_11 = Array__Str_new(hoisted__U32_56);
        I64 _va_Array_11_ek = 0;
        U32 hoisted__U32_57 = 0;
        Array__Str_set(&_va_Array_11, hoisted__U32_57, &_til_str_lits.h4d3ab87300de, &_va_Array_11_ek);
        panic(&_va_Array_11, &hoisted__Str_test_collection_return_fold_59);
    }
    assert_eq__Str(_bang_ret_8, &_til_str_lits.hd0b1c236fb8f, &hoisted__Str_test_collection_return_fold_143);
    Vec__Str_delete(&left, (Bool){0});
    U32 hoisted__U32_144 = 0;
    Str *_bang_ret_9 = (((Bool)(hoisted__U32_144 < right.count)) ? (Str *)((Str *)((void *)((U8 *)(right.data) + (((U32)(hoisted__U32_144 * 16)))))) : (_err_kind = 1, (Str *)NULL));
    I64 hoisted__I64_145 = 1;
    Bool hoisted__Bool_146 = ((Bool)(_err_kind == hoisted__I64_145));
    if (hoisted__Bool_146) {
        I64 hoisted__I64_60 = 0;
        _err_kind = hoisted__I64_60;
        U32 hoisted__U32_61 = 1;
        Array__Str _va_Array_12 = Array__Str_new(hoisted__U32_61);
        I64 _va_Array_12_ek = 0;
        U32 hoisted__U32_62 = 0;
        Array__Str_set(&_va_Array_12, hoisted__U32_62, &_til_str_lits.h4d3ab87300de, &_va_Array_12_ek);
        panic(&_va_Array_12, &hoisted__Str_test_collection_return_fold_64);
    }
    assert_eq__Str(_bang_ret_9, &_til_str_lits.h00310f176c2b, &hoisted__Str_test_collection_return_fold_148);
    Vec__Str_delete(&right, (Bool){0});
    Vec__I64 macro_values = Vec__I64_clone(&_til_precomputed_sequence_33);
    U32 hoisted__U32_149 = 4;
    assert_eq__USize(macro_values.cap, hoisted__U32_149, &hoisted__Str_test_collection_return_fold_150);
    U32 hoisted__U32_151 = 1;
    I64 *_bang_ret_10 = (((Bool)(hoisted__U32_151 < macro_values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(macro_values.data) + (((U32)(hoisted__U32_151 * 8)))))) : (_err_kind = 1, (I64 *)NULL));
    I64 hoisted__I64_152 = 1;
    Bool hoisted__Bool_153 = ((Bool)(_err_kind == hoisted__I64_152));
    if (hoisted__Bool_153) {
        I64 hoisted__I64_65 = 0;
        _err_kind = hoisted__I64_65;
        U32 hoisted__U32_66 = 1;
        Array__Str _va_Array_13 = Array__Str_new(hoisted__U32_66);
        I64 _va_Array_13_ek = 0;
        U32 hoisted__U32_67 = 0;
        Array__Str_set(&_va_Array_13, hoisted__U32_67, &_til_str_lits.h4d3ab87300de, &_va_Array_13_ek);
        panic(&_va_Array_13, &hoisted__Str_test_collection_return_fold_69);
    }
    Vec__CfNestedValues_delete(&nested, (Bool){0});
    I64 hoisted__I64_154 = 22;
    assert_eq__I64(DEREF(_bang_ret_10), hoisted__I64_154, &hoisted__Str_test_collection_return_fold_155);
    Vec__I64_delete(&macro_values, (Bool){0});
}

static void test_serialized_values_are_compositional(void) {
    U32 hoisted__U32_0 = 2;
    U32 hoisted__U32_1 = 2;
    assert_eq__USize(hoisted__U32_0, hoisted__U32_1, &hoisted__Str_test_serialized_values_are_compositional_2);
    I64 hoisted__I64_4 = 33;
    I64 hoisted__I64_5 = 33;
    assert_eq__I64(hoisted__I64_4, hoisted__I64_5, &hoisted__Str_test_serialized_values_are_compositional_6);
    U32 hoisted__U32_7 = 2;
    U32 hoisted__U32_8 = 2;
    assert_eq__USize(hoisted__U32_7, hoisted__U32_8, &hoisted__Str_test_serialized_values_are_compositional_9);
    U32 hoisted__U32_10 = 2;
    U32 hoisted__U32_11 = 2;
    assert_eq__USize(hoisted__U32_10, hoisted__U32_11, &hoisted__Str_test_serialized_values_are_compositional_12);
    U32 hoisted__U32_13 = 2;
    assert_eq__USize(CF_COMPOSED_COUNT, hoisted__U32_13, &hoisted__Str_test_serialized_values_are_compositional_14);
    I64 hoisted__I64_15 = 42;
    I64 hoisted__I64_16 = 42;
    assert_eq__I64(hoisted__I64_15, hoisted__I64_16, &hoisted__Str_test_serialized_values_are_compositional_17);
    I64 hoisted__I64_19 = 17;
    I64 hoisted__I64_20 = 17;
    assert_eq__I64(hoisted__I64_19, hoisted__I64_20, &hoisted__Str_test_serialized_values_are_compositional_21);
}

static void test_static_global_initializers(void) {
    I64 hoisted__I64_8 = 42;
    assert_eq__I64(STATIC_SCALAR, hoisted__I64_8, &hoisted__Str_test_static_global_initializers_9);
    static Str hoisted__Str_test_static_global_initializers_10 = (Str){.c_str = (void *)"static-folded", .count = 13ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&STATIC_STR, &hoisted__Str_test_static_global_initializers_10, &hoisted__Str_test_static_global_initializers_11);
    I64 hoisted__I64_12 = 42;
    assert_eq__I64(STATIC_POINT.x, hoisted__I64_12, &hoisted__Str_test_static_global_initializers_13);
    Bool hoisted__Bool_14 = Color_eq(&STATIC_COLOR, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_14, &hoisted__Str_test_static_global_initializers_15);
    switch ((STATIC_TOKEN).tag) {
    case Token_TAG_Num: {
        I64 *value = ((void *)((U8 *)(&STATIC_TOKEN) + offsetof(Token, data)));
        I64 hoisted__I64_0 = 13;
        assert_eq__I64(DEREF(value), hoisted__I64_0, &hoisted__Str_test_static_global_initializers_1);
        break;
    }
    default: {
        U32 hoisted__U32_2 = 0;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_2);
        (void)_va_Array_0;
        I64 _va_Array_0_ek = 0;
        (void)_va_Array_0_ek;
        UNREACHABLE(&_va_Array_0, &hoisted__Str_test_static_global_initializers_3);
        break;
    }
    }
    I64 hoisted__I64_16 = 42;
    assert_eq__I64(WideToken_answer, hoisted__I64_16, &hoisted__Str_test_static_global_initializers_17);
    switch ((WideToken_sample_value).tag) {
    case WideToken_TAG_Num: {
        I64 *value = ((void *)((U8 *)(&WideToken_sample_value) + offsetof(WideToken, data)));
        I64 hoisted__I64_4 = 12;
        assert_eq__I64(DEREF(value), hoisted__I64_4, &hoisted__Str_test_static_global_initializers_5);
        break;
    }
    default: {
        U32 hoisted__U32_6 = 0;
        Array__Str _va_Array_1 = Array__Str_new(hoisted__U32_6);
        (void)_va_Array_1;
        I64 _va_Array_1_ek = 0;
        (void)_va_Array_1_ek;
        UNREACHABLE(&_va_Array_1, &hoisted__Str_test_static_global_initializers_7);
        break;
    }
    }
    Bool hoisted__Bool_18 = ((Bool)((((NestedToken *)(&STATIC_NICHE))->data != NULL) == 1));
    assert(hoisted__Bool_18, &hoisted__Str_test_static_global_initializers_19);
}

static void test_const_and_or_fold(void) {
    U32 hoisted__U32_6 = 1;
    Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_6);
    I64 _va_Array_0_ek = 0;
    U32 hoisted__U32_7 = 0;
    static Str hoisted__Str_test_const_and_or_fold_8 = (Str){.c_str = (void *)"and(T,T)", .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_0, hoisted__U32_7, &hoisted__Str_test_const_and_or_fold_8, &_va_Array_0_ek);
    Bool hoisted__Bool_9 = 1;
    expect(hoisted__Bool_9, &_va_Array_0, &hoisted__Str_test_const_and_or_fold_10);
    U32 hoisted__U32_11 = 1;
    Array__Str _va_Array_1 = Array__Str_new(hoisted__U32_11);
    I64 _va_Array_1_ek = 0;
    U32 hoisted__U32_12 = 0;
    static Str hoisted__Str_test_const_and_or_fold_13 = (Str){.c_str = (void *)"and(T,F)", .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_1, hoisted__U32_12, &hoisted__Str_test_const_and_or_fold_13, &_va_Array_1_ek);
    Bool hoisted__Bool_15 = 1;
    expect(hoisted__Bool_15, &_va_Array_1, &hoisted__Str_test_const_and_or_fold_16);
    U32 hoisted__U32_17 = 1;
    Array__Str _va_Array_2 = Array__Str_new(hoisted__U32_17);
    I64 _va_Array_2_ek = 0;
    U32 hoisted__U32_18 = 0;
    static Str hoisted__Str_test_const_and_or_fold_19 = (Str){.c_str = (void *)"and x3 T", .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_2, hoisted__U32_18, &hoisted__Str_test_const_and_or_fold_19, &_va_Array_2_ek);
    Bool hoisted__Bool_20 = 1;
    expect(hoisted__Bool_20, &_va_Array_2, &hoisted__Str_test_const_and_or_fold_21);
    U32 hoisted__U32_22 = 1;
    Array__Str _va_Array_3 = Array__Str_new(hoisted__U32_22);
    I64 _va_Array_3_ek = 0;
    U32 hoisted__U32_23 = 0;
    static Str hoisted__Str_test_const_and_or_fold_24 = (Str){.c_str = (void *)"and x3 with F", .count = 13ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_3, hoisted__U32_23, &hoisted__Str_test_const_and_or_fold_24, &_va_Array_3_ek);
    Bool hoisted__Bool_26 = 1;
    expect(hoisted__Bool_26, &_va_Array_3, &hoisted__Str_test_const_and_or_fold_27);
    U32 hoisted__U32_28 = 1;
    Array__Str _va_Array_4 = Array__Str_new(hoisted__U32_28);
    I64 _va_Array_4_ek = 0;
    U32 hoisted__U32_29 = 0;
    static Str hoisted__Str_test_const_and_or_fold_30 = (Str){.c_str = (void *)"or(F,T)", .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_4, hoisted__U32_29, &hoisted__Str_test_const_and_or_fold_30, &_va_Array_4_ek);
    Bool hoisted__Bool_31 = 1;
    expect(hoisted__Bool_31, &_va_Array_4, &hoisted__Str_test_const_and_or_fold_32);
    U32 hoisted__U32_33 = 1;
    Array__Str _va_Array_5 = Array__Str_new(hoisted__U32_33);
    I64 _va_Array_5_ek = 0;
    U32 hoisted__U32_34 = 0;
    static Str hoisted__Str_test_const_and_or_fold_35 = (Str){.c_str = (void *)"or(F,F)", .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_5, hoisted__U32_34, &hoisted__Str_test_const_and_or_fold_35, &_va_Array_5_ek);
    Bool hoisted__Bool_37 = 1;
    expect(hoisted__Bool_37, &_va_Array_5, &hoisted__Str_test_const_and_or_fold_38);
    U32 hoisted__U32_39 = 1;
    Array__Str _va_Array_6 = Array__Str_new(hoisted__U32_39);
    I64 _va_Array_6_ek = 0;
    U32 hoisted__U32_40 = 0;
    static Str hoisted__Str_test_const_and_or_fold_41 = (Str){.c_str = (void *)"or x3 with T", .count = 12ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_6, hoisted__U32_40, &hoisted__Str_test_const_and_or_fold_41, &_va_Array_6_ek);
    Bool hoisted__Bool_42 = 1;
    expect(hoisted__Bool_42, &_va_Array_6, &hoisted__Str_test_const_and_or_fold_43);
    U32 hoisted__U32_44 = 1;
    Array__Str _va_Array_7 = Array__Str_new(hoisted__U32_44);
    I64 _va_Array_7_ek = 0;
    U32 hoisted__U32_45 = 0;
    static Str hoisted__Str_test_const_and_or_fold_46 = (Str){.c_str = (void *)"or x3 F", .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_7, hoisted__U32_45, &hoisted__Str_test_const_and_or_fold_46, &_va_Array_7_ek);
    Bool hoisted__Bool_48 = 1;
    expect(hoisted__Bool_48, &_va_Array_7, &hoisted__Str_test_const_and_or_fold_49);
    U32 hoisted__U32_50 = 1;
    Array__Str _va_Array_8 = Array__Str_new(hoisted__U32_50);
    I64 _va_Array_8_ek = 0;
    U32 hoisted__U32_51 = 0;
    static Str hoisted__Str_test_const_and_or_fold_52 = (Str){.c_str = (void *)"T.and(T)", .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_8, hoisted__U32_51, &hoisted__Str_test_const_and_or_fold_52, &_va_Array_8_ek);
    Bool hoisted__Bool_53 = 1;
    expect(hoisted__Bool_53, &_va_Array_8, &hoisted__Str_test_const_and_or_fold_54);
    Bool _m_Bool_0 = 0;
    {
        Bool hoisted__Bool_5 = 0;
        if (hoisted__Bool_5) {
            Bool hoisted__Bool_2 = 1;
            _m_Bool_0 = hoisted__Bool_2;
        } else {
            Bool hoisted__Bool_3 = 1;
            _m_Bool_0 = hoisted__Bool_3;
        }
    }
    U32 hoisted__U32_55 = 1;
    Array__Str _va_Array_9 = Array__Str_new(hoisted__U32_55);
    I64 _va_Array_9_ek = 0;
    U32 hoisted__U32_56 = 0;
    static Str hoisted__Str_test_const_and_or_fold_57 = (Str){.c_str = (void *)"F.or(T)", .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_9, hoisted__U32_56, &hoisted__Str_test_const_and_or_fold_57, &_va_Array_9_ek);
    expect(_m_Bool_0, &_va_Array_9, &hoisted__Str_test_const_and_or_fold_58);
}

static void test_mixed_fold(void) {
    I64 result = 10;
    I64 hoisted__I64_3 = 10;
    assert_eq__I64(result, hoisted__I64_3, &hoisted__Str_test_mixed_fold_4);
}

static void test_fold_reads_global_const(void) {
    I64 hoisted__I64_1 = 2;
    I64 hoisted__I64_2 = 2;
    assert_eq__I64(hoisted__I64_1, hoisted__I64_2, &hoisted__Str_test_fold_reads_global_const_3);
}

static void Array__I64_delete(Array__I64 * self, Bool call_free) {
    {
        U32 _re_U32_0 = self->cap;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U32 hoisted__U32_2 = 8;
            U32 hoisted__U32_3 = ((U32)(i * hoisted__U32_2));
            U64 hoisted__U64_4 = usize_to_uptr(hoisted__U32_3);
            I64 *hoisted__I64_5 = ((void *)((U8 *)(self->data) + (hoisted__U64_4)));
            I64_delete(hoisted__I64_5, 0);
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

static Array__I64 Array__I64_clone(Array__I64 * self) {
    U32 hoisted__U32_9 = 8;
    U32 hoisted__U32_10 = ((U32)(self->cap * hoisted__U32_9));
    U8 *new_data = malloc(usize_to_uptr(hoisted__U32_10));
    {
        U32 _re_U32_0 = self->cap;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U32 hoisted__U32_2 = 8;
            U32 hoisted__U32_3 = ((U32)(i * hoisted__U32_2));
            U64 hoisted__U64_4 = usize_to_uptr(hoisted__U32_3);
            I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U64_4)));
            I64 cloned = (DEREF(src));
            U32 hoisted__U32_5 = 8;
            U32 hoisted__U32_6 = ((U32)(i * hoisted__U32_5));
            U64 hoisted__U64_7 = usize_to_uptr(hoisted__U32_6);
            void *hoisted__v_8 = ((void *)((U8 *)(new_data) + (hoisted__U64_7)));
            adopt__I64(hoisted__v_8, cloned);
        }
    }
    Array__I64 hoisted__Array__I64_11 = {0};
    hoisted__Array__I64_11.data = new_data;
    hoisted__Array__I64_11.cap = self->cap;
    return hoisted__Array__I64_11;
}

static I64 * Map__Str_I64_get(Map__Str_I64 * self, Str * key, I64 * _err_kind) {
    USize lo = 0;
    USize hi = self->keys.count;
    while (1) {
        Bool _wcond_Bool_0 = ((Bool)(lo < hi));
        if (_wcond_Bool_0) {
        } else {
            break;
        }
        U32 hoisted__U32_7 = ((U32)(hi - lo));
        U32 hoisted__U32_8 = 2;
        U32 hoisted__U32_9 = ({ U32 _cf_a = hoisted__U32_7; U32 _cf_b = hoisted__U32_8; (U32)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        USize mid = ((U32)(lo + hoisted__U32_9));
        Str *hoisted__Str_Map__Str_I64_get_10 = ((Str *)((void *)((U8 *)(self->keys.data) + (((U32)(mid * 16))))));
        I64 c = Str_cmp(hoisted__Str_Map__Str_I64_get_10, key);
        I64 hoisted__I64_11 = 0;
        Bool hoisted__Bool_12 = ((Bool)(c < hoisted__I64_11));
        if (hoisted__Bool_12) {
            U32 hoisted__U32_1 = 1;
            U32 hoisted__U32_2 = ((U32)(mid + hoisted__U32_1));
            lo = hoisted__U32_2;
        } else {
            I64 hoisted__I64_5 = 0;
            Bool hoisted__Bool_6 = ((Bool)(c > hoisted__I64_5));
            if (hoisted__Bool_6) {
                U32 hoisted__U32_3 = (mid);
                hi = hoisted__U32_3;
            } else {
                I64 *hoisted__I64_4 = ((I64 *)((void *)((U8 *)(self->values.data) + (((U32)(mid * 8))))));
                return hoisted__I64_4;
            }
        }
    }
    I64 hoisted__I64_13 = 4;
    *_err_kind = hoisted__I64_13;
    return NULL;
}

static void Map__Str_I64_delete(Map__Str_I64 * self, Bool call_free) {
    Vec__Str_delete(&self->keys, 0);
    Vec__I64_delete(&self->values, 0);
    if (call_free) {
        free(self);
    }
}

static void Vec__I64_clear(Vec__I64 * self) {
    {
        U32 _re_U32_0 = self->count;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U32 hoisted__U32_2 = 8;
            U32 hoisted__U32_3 = ((U32)(i * hoisted__U32_2));
            I64 *hoisted__I64_4 = ((void *)((U8 *)(self->data) + (hoisted__U32_3)));
            I64_delete(hoisted__I64_4, 0);
        }
    }
    U32 hoisted__U32_5 = 0;
    self->count = hoisted__U32_5;
}

static void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

static Vec__I64 Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_8 = 0;
    Bool hoisted__Bool_9 = ((Bool)(self->cap == hoisted__U32_8));
    if (hoisted__Bool_9) {
        Vec__I64 hoisted__Vec__I64_0 = {0};
        hoisted__Vec__I64_0.data = NULL;
        hoisted__Vec__I64_0.count = 0;
        hoisted__Vec__I64_0.cap = 0;
        return hoisted__Vec__I64_0;
    }
    U32 hoisted__U32_10 = 8;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_10)));
    {
        U32 _re_U32_1 = self->count;
        U32 _rc_U32_1 = 0;
        while (1) {
            Bool _wcond_Bool_2 = ((Bool)(_rc_U32_1 < _re_U32_1));
            if (_wcond_Bool_2) {
            } else {
                break;
            }
            U32 i = (_rc_U32_1);
            (++_rc_U32_1);
            U32 hoisted__U32_3 = 8;
            U32 hoisted__U32_4 = ((U32)(i * hoisted__U32_3));
            I64 *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4)));
            I64 cloned = (DEREF(src));
            U32 hoisted__U32_5 = 8;
            U32 hoisted__U32_6 = ((U32)(i * hoisted__U32_5));
            void *hoisted__v_7 = ((void *)((U8 *)(new_data) + (hoisted__U32_6)));
            adopt__I64(hoisted__v_7, cloned);
        }
    }
    Vec__I64 hoisted__Vec__I64_11 = {0};
    hoisted__Vec__I64_11.data = new_data;
    hoisted__Vec__I64_11.count = self->count;
    hoisted__Vec__I64_11.cap = self->cap;
    return hoisted__Vec__I64_11;
}

static void Vec__CfNestedValues_clear(Vec__CfNestedValues * self) {
    {
        U32 _re_U32_0 = self->count;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U32 hoisted__U32_2 = 16;
            U32 hoisted__U32_3 = ((U32)(i * hoisted__U32_2));
            CfNestedValues *hoisted__CfNestedValues_4 = ((void *)((U8 *)(self->data) + (hoisted__U32_3)));
            CfNestedValues_delete(hoisted__CfNestedValues_4, 0);
        }
    }
    U32 hoisted__U32_5 = 0;
    self->count = hoisted__U32_5;
}

static void Vec__CfNestedValues_delete(Vec__CfNestedValues * self, Bool call_free) {
    Vec__CfNestedValues_clear(self);
    free(self->data);
    if (call_free) {
        free(self);
    }
}

static Vec__CfNestedValues Vec__CfNestedValues_clone(Vec__CfNestedValues * self) {
    U32 hoisted__U32_8 = 0;
    Bool hoisted__Bool_9 = ((Bool)(self->cap == hoisted__U32_8));
    if (hoisted__Bool_9) {
        Vec__CfNestedValues hoisted__Vec__CfNestedValues_0 = {0};
        hoisted__Vec__CfNestedValues_0.data = NULL;
        hoisted__Vec__CfNestedValues_0.count = 0;
        hoisted__Vec__CfNestedValues_0.cap = 0;
        return hoisted__Vec__CfNestedValues_0;
    }
    U32 hoisted__U32_10 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_10)));
    {
        U32 _re_U32_1 = self->count;
        U32 _rc_U32_1 = 0;
        while (1) {
            Bool _wcond_Bool_2 = ((Bool)(_rc_U32_1 < _re_U32_1));
            if (_wcond_Bool_2) {
            } else {
                break;
            }
            U32 i = (_rc_U32_1);
            (++_rc_U32_1);
            U32 hoisted__U32_3 = 16;
            U32 hoisted__U32_4 = ((U32)(i * hoisted__U32_3));
            CfNestedValues *src = ((void *)((U8 *)(self->data) + (hoisted__U32_4)));
            CfNestedValues cloned = CfNestedValues_clone(src);
            U32 hoisted__U32_5 = 16;
            U32 hoisted__U32_6 = ((U32)(i * hoisted__U32_5));
            void *hoisted__v_7 = ((void *)((U8 *)(new_data) + (hoisted__U32_6)));
            adopt__CfNestedValues(hoisted__v_7, &cloned);
        }
    }
    Vec__CfNestedValues hoisted__Vec__CfNestedValues_11 = {0};
    hoisted__Vec__CfNestedValues_11.data = new_data;
    hoisted__Vec__CfNestedValues_11.count = self->count;
    hoisted__Vec__CfNestedValues_11.cap = self->cap;
    return hoisted__Vec__CfNestedValues_11;
}

static void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_11 = ((Bool)(a != b));
    if (hoisted__Bool_11) {
        U32 hoisted__U32_0 = 5;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &_til_str_lits.h44abcb58cde4, &_va_Array_0_ek);
        U32 hoisted__U32_3 = 1;
        Str hoisted__Str_assert_eq__I64_4 = I64_to_str(a);
        Array__Str_set(&_va_Array_0, hoisted__U32_3, &hoisted__Str_assert_eq__I64_4, &_va_Array_0_ek);
        U32 hoisted__U32_5 = 2;
        Array__Str_set(&_va_Array_0, hoisted__U32_5, &_til_str_lits.h15a1180c089b, &_va_Array_0_ek);
        U32 hoisted__U32_7 = 3;
        Str hoisted__Str_assert_eq__I64_8 = I64_to_str(b);
        Array__Str_set(&_va_Array_0, hoisted__U32_7, &hoisted__Str_assert_eq__I64_8, &_va_Array_0_ek);
        U32 hoisted__U32_9 = 4;
        Array__Str_set(&_va_Array_0, hoisted__U32_9, &_til_str_lits.h00000002b5cc, &_va_Array_0_ek);
        panic(&_va_Array_0, loc);
    }
}

static void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_11 = Str_neq(a, b);
    if (hoisted__Bool_11) {
        U32 hoisted__U32_0 = 5;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &_til_str_lits.h44abcb58cde4, &_va_Array_0_ek);
        U32 hoisted__U32_3 = 1;
        Str hoisted__Str_assert_eq__Str_4 = Str_to_str(a);
        Array__Str_set(&_va_Array_0, hoisted__U32_3, &hoisted__Str_assert_eq__Str_4, &_va_Array_0_ek);
        U32 hoisted__U32_5 = 2;
        Array__Str_set(&_va_Array_0, hoisted__U32_5, &_til_str_lits.h15a1180c089b, &_va_Array_0_ek);
        U32 hoisted__U32_7 = 3;
        Str hoisted__Str_assert_eq__Str_8 = Str_to_str(b);
        Array__Str_set(&_va_Array_0, hoisted__U32_7, &hoisted__Str_assert_eq__Str_8, &_va_Array_0_ek);
        U32 hoisted__U32_9 = 4;
        Array__Str_set(&_va_Array_0, hoisted__U32_9, &_til_str_lits.h00000002b5cc, &_va_Array_0_ek);
        panic(&_va_Array_0, loc);
    }
}

static void assert_eq__USize(USize a, USize b, Str * loc) {
    Bool hoisted__Bool_11 = ((Bool)(a != b));
    if (hoisted__Bool_11) {
        U32 hoisted__U32_0 = 5;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &_til_str_lits.h44abcb58cde4, &_va_Array_0_ek);
        U32 hoisted__U32_3 = 1;
        Str hoisted__Str_assert_eq__USize_4 = U32_to_str(a);
        Array__Str_set(&_va_Array_0, hoisted__U32_3, &hoisted__Str_assert_eq__USize_4, &_va_Array_0_ek);
        U32 hoisted__U32_5 = 2;
        Array__Str_set(&_va_Array_0, hoisted__U32_5, &_til_str_lits.h15a1180c089b, &_va_Array_0_ek);
        U32 hoisted__U32_7 = 3;
        Str hoisted__Str_assert_eq__USize_8 = U32_to_str(b);
        Array__Str_set(&_va_Array_0, hoisted__U32_7, &hoisted__Str_assert_eq__USize_8, &_va_Array_0_ek);
        U32 hoisted__U32_9 = 4;
        Array__Str_set(&_va_Array_0, hoisted__U32_9, &_til_str_lits.h00000002b5cc, &_va_Array_0_ek);
        panic(&_va_Array_0, loc);
    }
}

static void adopt__I64(void * dest, I64 src) {
    U32 hoisted__U32_0 = 8;
    memcpy(dest, &src, hoisted__U32_0);
    ((void)src);
}

static void adopt__CfNestedValues(void * dest, CfNestedValues * src) {
    U32 hoisted__U32_0 = 16;
    memcpy(dest, src, hoisted__U32_0);
    ((void)src);
}

int main(void) {
    STATIC_NICHE = NestedToken_Inner(({ WideToken *_oa = malloc(TIL_BOX(WideToken)); *_oa = WideToken_Num(&(I64){9}); _oa; }));
    CF_COMPOSED_VALUES = Vec__I64_clone(&_til_precomputed_sequence_22);
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
    test_enum_literal_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_literal_fold");
    test_enum_payload_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_payload_fold");
    test_enum_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_return_fold");
    test_enum_payload_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_enum_payload_return_fold");
    test_explicit_tag_enum_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_explicit_tag_enum_return_fold");
    test_nested_enum_payload_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_nested_enum_payload_return_fold");
    test_collection_return_fold();
    fprintf(stderr, "  pass: %s\n", "test_collection_return_fold");
    test_serialized_values_are_compositional();
    fprintf(stderr, "  pass: %s\n", "test_serialized_values_are_compositional");
    test_static_global_initializers();
    fprintf(stderr, "  pass: %s\n", "test_static_global_initializers");
    test_const_and_or_fold();
    fprintf(stderr, "  pass: %s\n", "test_const_and_or_fold");
    test_mixed_fold();
    fprintf(stderr, "  pass: %s\n", "test_mixed_fold");
    test_fold_reads_global_const();
    fprintf(stderr, "  pass: %s\n", "test_fold_reads_global_const");
    fprintf(stderr, "27/27 tests passed\n");
    return 0;
}
