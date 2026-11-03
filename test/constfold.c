#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>

#if !defined(TIL_USIZE32) && !defined(TIL_USIZE64)
#define TIL_USIZE32 1
#endif
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
    TIL_OWN_PTR(I8) c_str;
    USize count;
    USize cap;
} Str;


typedef struct Array__Str {
    TIL_OWN_PTR(U8) data;
    USize cap;
} Array__Str;


typedef struct Vec__Str {
    TIL_OWN_PTR(U8) data;
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
    TIL_OWN_PTR(U8) data;
    USize cap;
} Array__I64;


typedef struct Vec__I64 {
    TIL_OWN_PTR(U8) data;
    USize count;
    USize cap;
} Vec__I64;


typedef struct Vec__CfNestedValues {
    TIL_OWN_PTR(U8) data;
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
static I64 cf_abort_if_nonempty(Str * first, Str * second);
static I64 cf_abort_owned_args(Str * first, Str * second);
static I64 cf_abort_owned_branch(Str * first, Str * second);
static I64 cf_abort_after_release(Str * first, Str * second);
static Bool cf_abort_runtime_guard(void);
static void test_constfold_abort_owned_args(void);
static void test_constfold_abort_branch_locals(void);
static void test_constfold_abort_after_release(void);
static I64 cf_runtime_input(void);
static I64 cf_shadow_parameter(I64 CF_SHADOW);
static I64 cf_shadow_local(I64 value);
static I64 cf_shadow_ref(I64 value);
static void test_runtime_bindings_shadow_global_constants(void);
static void test_block_constants_do_not_escape_their_scope(void);
static void test_serialized_binding_keeps_assignment(void);
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
#define TIL_CAP_LIT ((USize)0 - (USize)1)
#define TIL_CAP_VIEW ((USize)0 - (USize)2)
static void print_single(Str *s) {
    fwrite(TIL_OWN_GET(I8, s->c_str), 1, (size_t)s->count, stdout);
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
} *_til_str_lits_cage;
#define _til_str_lits (*_til_str_lits_cage)
static void til_str_lits_init(void) __attribute__((constructor));
static void til_str_lits_init(void) {
    static const struct { size_t offset; const char *text; USize count; } entries[] = {
        {offsetof(__typeof__(*_til_str_lits_cage), h000000001505), "", 0ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h00000002b5cc), "'", 1ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h15a1180c089b), "', found '", 10ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h00000b8791fb), "3.5", 3ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h00017c7b7650), "6.25", 4ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h00000002b606), "a", 1ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h00310f176c2b), "alpha", 5ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h44abcb58cde4), "assert_eq failed: expected '", 28ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h00000002b607), "b", 1ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h00017c9489a1), "beta", 4ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), hd0b1c236fb8f), "changed", 7ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h3fd43551c8c1), "hello world", 11ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h00000002b617), "r", 1ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), hd0e435b6dffc), "uncaught throw 'KeyNotFound'", 28ULL},
        {offsetof(__typeof__(*_til_str_lits_cage), h4d3ab87300de), "uncaught throw 'OutOfBounds'", 28ULL},
    };
    _til_str_lits_cage = malloc(sizeof(*_til_str_lits_cage));
    for (size_t i = 0; i < sizeof(entries) / sizeof(entries[0]); ++i) {
        Str *slot = (Str *)((unsigned char *)_til_str_lits_cage + entries[i].offset);
        *slot = (Str){.c_str = {til_cage_lit(entries[i].text, entries[i].count)}, .count = entries[i].count, .cap = TIL_CAP_LIT};
    }
}

/* til source locations, in the --usize=32 cage */
static struct {
    Str hoisted__Str_Str_push_str_3;
    Str hoisted__Str_Str_push_str_7;
    Str hoisted__Str_test_block_constants_do_not_escape_their_scope_11;
    Str hoisted__Str_test_block_constants_do_not_escape_their_scope_15;
    Str hoisted__Str_test_block_constants_do_not_escape_their_scope_19;
    Str hoisted__Str_test_block_constants_do_not_escape_their_scope_3;
    Str hoisted__Str_test_block_constants_do_not_escape_their_scope_7;
    Str hoisted__Str_test_collection_return_fold_102;
    Str hoisted__Str_test_collection_return_fold_105;
    Str hoisted__Str_test_collection_return_fold_110;
    Str hoisted__Str_test_collection_return_fold_115;
    Str hoisted__Str_test_collection_return_fold_118;
    Str hoisted__Str_test_collection_return_fold_129;
    Str hoisted__Str_test_collection_return_fold_134;
    Str hoisted__Str_test_collection_return_fold_14;
    Str hoisted__Str_test_collection_return_fold_143;
    Str hoisted__Str_test_collection_return_fold_148;
    Str hoisted__Str_test_collection_return_fold_150;
    Str hoisted__Str_test_collection_return_fold_155;
    Str hoisted__Str_test_collection_return_fold_19;
    Str hoisted__Str_test_collection_return_fold_24;
    Str hoisted__Str_test_collection_return_fold_29;
    Str hoisted__Str_test_collection_return_fold_34;
    Str hoisted__Str_test_collection_return_fold_39;
    Str hoisted__Str_test_collection_return_fold_4;
    Str hoisted__Str_test_collection_return_fold_44;
    Str hoisted__Str_test_collection_return_fold_49;
    Str hoisted__Str_test_collection_return_fold_54;
    Str hoisted__Str_test_collection_return_fold_59;
    Str hoisted__Str_test_collection_return_fold_64;
    Str hoisted__Str_test_collection_return_fold_69;
    Str hoisted__Str_test_collection_return_fold_72;
    Str hoisted__Str_test_collection_return_fold_74;
    Str hoisted__Str_test_collection_return_fold_79;
    Str hoisted__Str_test_collection_return_fold_84;
    Str hoisted__Str_test_collection_return_fold_87;
    Str hoisted__Str_test_collection_return_fold_89;
    Str hoisted__Str_test_collection_return_fold_9;
    Str hoisted__Str_test_collection_return_fold_92;
    Str hoisted__Str_test_collection_return_fold_97;
    Str hoisted__Str_test_const_and_or_fold_10;
    Str hoisted__Str_test_const_and_or_fold_16;
    Str hoisted__Str_test_const_and_or_fold_21;
    Str hoisted__Str_test_const_and_or_fold_27;
    Str hoisted__Str_test_const_and_or_fold_32;
    Str hoisted__Str_test_const_and_or_fold_38;
    Str hoisted__Str_test_const_and_or_fold_43;
    Str hoisted__Str_test_const_and_or_fold_49;
    Str hoisted__Str_test_const_and_or_fold_54;
    Str hoisted__Str_test_const_and_or_fold_58;
    Str hoisted__Str_test_constfold_abort_after_release_3;
    Str hoisted__Str_test_constfold_abort_after_release_9;
    Str hoisted__Str_test_constfold_abort_branch_locals_3;
    Str hoisted__Str_test_constfold_abort_branch_locals_9;
    Str hoisted__Str_test_constfold_abort_owned_args_3;
    Str hoisted__Str_test_constfold_abort_owned_args_9;
    Str hoisted__Str_test_deeply_nested_7;
    Str hoisted__Str_test_enum_fold_1;
    Str hoisted__Str_test_enum_fold_4;
    Str hoisted__Str_test_enum_literal_fold_10;
    Str hoisted__Str_test_enum_literal_fold_5;
    Str hoisted__Str_test_enum_literal_fold_7;
    Str hoisted__Str_test_enum_payload_fold_2;
    Str hoisted__Str_test_enum_payload_fold_5;
    Str hoisted__Str_test_enum_payload_return_fold_2;
    Str hoisted__Str_test_enum_payload_return_fold_5;
    Str hoisted__Str_test_enum_return_fold_1;
    Str hoisted__Str_test_enum_return_fold_4;
    Str hoisted__Str_test_explicit_tag_enum_return_fold_1;
    Str hoisted__Str_test_explicit_tag_enum_return_fold_3;
    Str hoisted__Str_test_explicit_tag_enum_return_fold_6;
    Str hoisted__Str_test_fold_f32_4;
    Str hoisted__Str_test_fold_f32_9;
    Str hoisted__Str_test_fold_reads_global_const_3;
    Str hoisted__Str_test_fold_variable_2;
    Str hoisted__Str_test_loc_folded_3;
    Str hoisted__Str_test_loc_folded_7;
    Str hoisted__Str_test_lolalalo_8;
    Str hoisted__Str_test_lolalalo_9;
    Str hoisted__Str_test_mixed_fold_4;
    Str hoisted__Str_test_nested_arithmetic_7;
    Str hoisted__Str_test_nested_enum_payload_return_fold_1;
    Str hoisted__Str_test_nested_enum_payload_return_fold_3;
    Str hoisted__Str_test_nested_enum_payload_return_fold_5;
    Str hoisted__Str_test_runtime_bindings_shadow_global_constants_12;
    Str hoisted__Str_test_runtime_bindings_shadow_global_constants_16;
    Str hoisted__Str_test_runtime_bindings_shadow_global_constants_2;
    Str hoisted__Str_test_runtime_bindings_shadow_global_constants_20;
    Str hoisted__Str_test_runtime_bindings_shadow_global_constants_5;
    Str hoisted__Str_test_runtime_bindings_shadow_global_constants_8;
    Str hoisted__Str_test_serialized_values_are_compositional_12;
    Str hoisted__Str_test_serialized_values_are_compositional_14;
    Str hoisted__Str_test_serialized_values_are_compositional_17;
    Str hoisted__Str_test_serialized_values_are_compositional_2;
    Str hoisted__Str_test_serialized_values_are_compositional_21;
    Str hoisted__Str_test_serialized_values_are_compositional_6;
    Str hoisted__Str_test_serialized_values_are_compositional_9;
    Str hoisted__Str_test_simple_add_3;
    Str hoisted__Str_test_static_global_initializers_1;
    Str hoisted__Str_test_static_global_initializers_11;
    Str hoisted__Str_test_static_global_initializers_13;
    Str hoisted__Str_test_static_global_initializers_15;
    Str hoisted__Str_test_static_global_initializers_17;
    Str hoisted__Str_test_static_global_initializers_19;
    Str hoisted__Str_test_static_global_initializers_3;
    Str hoisted__Str_test_static_global_initializers_5;
    Str hoisted__Str_test_static_global_initializers_7;
    Str hoisted__Str_test_static_global_initializers_9;
    Str hoisted__Str_test_string_concat_3;
    Str hoisted__Str_test_struct_fold_f32_11;
    Str hoisted__Str_test_struct_fold_f32_5;
    Str hoisted__Str_test_struct_fold_f32_8;
    Str hoisted__Str_test_struct_fold_nested_1;
    Str hoisted__Str_test_struct_fold_nested_3;
    Str hoisted__Str_test_struct_fold_nested_5;
    Str hoisted__Str_test_struct_fold_nested_7;
    Str hoisted__Str_test_struct_fold_simple_1;
    Str hoisted__Str_test_struct_fold_simple_3;
    Str hoisted__Str_test_struct_fold_values_11;
    Str hoisted__Str_test_struct_fold_values_13;
    Str hoisted__Str_test_struct_fold_values_3;
    Str hoisted__Str_test_struct_fold_values_5;
    Str hoisted__Str_test_struct_fold_values_7;
    Str hoisted__Str_test_struct_fold_values_9;
    Str hoisted__Str_test_variadic_direct_fold_12;
    Str hoisted__Str_test_variadic_direct_fold_21;
    Str hoisted__Str_test_variadic_direct_fold_31;
    Str hoisted__Str_test_variadic_fold_3;
    Str hoisted__Str_test_variadic_fold_8;
} *_til_loc_lits_cage;
static void til_loc_lits_init(void) __attribute__((constructor));
static void til_loc_lits_init(void) {
    static const struct { size_t offset; const char *text; USize count; } entries[] = {
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_Str_push_str_3), "./src/core/str.til:217:13", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_Str_push_str_7), "./src/core/str.til:221:13", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_block_constants_do_not_escape_their_scope_11), "test/constfold.til:650:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_block_constants_do_not_escape_their_scope_15), "test/constfold.til:655:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_block_constants_do_not_escape_their_scope_19), "test/constfold.til:660:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_block_constants_do_not_escape_their_scope_3), "test/constfold.til:653:9", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_block_constants_do_not_escape_their_scope_7), "test/constfold.til:658:9", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_102), "test/constfold.til:444:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_105), "test/constfold.til:447:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_110), "test/constfold.til:448:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_115), "test/constfold.til:449:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_118), "test/constfold.til:452:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_129), "test/constfold.til:455:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_134), "test/constfold.til:456:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_14), "test/constfold.til:443:25", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_143), "test/constfold.til:461:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_148), "test/constfold.til:462:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_150), "test/constfold.til:465:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_155), "test/constfold.til:466:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_19), "test/constfold.til:444:25", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_24), "test/constfold.til:448:25", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_29), "test/constfold.til:449:25", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_34), "test/constfold.til:453:9", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_39), "test/constfold.til:454:9", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_4), "test/constfold.til:434:26", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_44), "test/constfold.til:455:39", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_49), "test/constfold.til:456:40", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_54), "test/constfold.til:460:9", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_59), "test/constfold.til:461:24", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_64), "test/constfold.til:462:25", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_69), "test/constfold.til:466:32", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_72), "test/constfold.til:432:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_74), "test/constfold.til:433:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_79), "test/constfold.til:434:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_84), "test/constfold.til:435:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_87), "test/constfold.til:438:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_89), "test/constfold.til:439:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_9), "test/constfold.til:435:26", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_92), "test/constfold.til:442:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_collection_return_fold_97), "test/constfold.til:443:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_10), "test/constfold.til:505:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_16), "test/constfold.til:506:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_21), "test/constfold.til:507:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_27), "test/constfold.til:508:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_32), "test/constfold.til:509:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_38), "test/constfold.til:510:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_43), "test/constfold.til:511:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_49), "test/constfold.til:512:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_54), "test/constfold.til:513:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_const_and_or_fold_58), "test/constfold.til:514:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_constfold_abort_after_release_3), "test/constfold.til:602:9", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_constfold_abort_after_release_9), "test/constfold.til:604:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_constfold_abort_branch_locals_3), "test/constfold.til:594:9", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_constfold_abort_branch_locals_9), "test/constfold.til:596:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_constfold_abort_owned_args_3), "test/constfold.til:586:9", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_constfold_abort_owned_args_9), "test/constfold.til:588:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_deeply_nested_7), "test/constfold.til:27:5", 23ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_fold_1), "test/constfold.til:250:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_fold_4), "test/constfold.til:251:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_literal_fold_10), "test/constfold.til:267:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_literal_fold_5), "test/constfold.til:265:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_literal_fold_7), "test/constfold.til:266:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_payload_fold_2), "test/constfold.til:275:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_payload_fold_5), "test/constfold.til:276:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_payload_return_fold_2), "test/constfold.til:297:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_payload_return_fold_5), "test/constfold.til:298:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_return_fold_1), "test/constfold.til:285:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_enum_return_fold_4), "test/constfold.til:286:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_explicit_tag_enum_return_fold_1), "test/constfold.til:331:32", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_explicit_tag_enum_return_fold_3), "test/constfold.til:332:11", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_explicit_tag_enum_return_fold_6), "test/constfold.til:335:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_fold_f32_4), "test/constfold.til:154:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_fold_f32_9), "test/constfold.til:156:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_fold_reads_global_const_3), "test/constfold.til:539:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_fold_variable_2), "test/constfold.til:137:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_loc_folded_3), "test/constfold.til:142:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_loc_folded_7), "test/constfold.til:143:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_lolalalo_8), "test/constfold.til:129:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_lolalalo_9), "test/constfold.til:130:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_mixed_fold_4), "test/constfold.til:521:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_nested_arithmetic_7), "test/constfold.til:21:5", 23ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_nested_enum_payload_return_fold_1), "test/constfold.til:343:36", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_nested_enum_payload_return_fold_3), "test/constfold.til:344:15", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_nested_enum_payload_return_fold_5), "test/constfold.til:346:11", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_runtime_bindings_shadow_global_constants_12), "test/constfold.til:643:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_runtime_bindings_shadow_global_constants_16), "test/constfold.til:644:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_runtime_bindings_shadow_global_constants_2), "test/constfold.til:639:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_runtime_bindings_shadow_global_constants_20), "test/constfold.til:645:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_runtime_bindings_shadow_global_constants_5), "test/constfold.til:640:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_runtime_bindings_shadow_global_constants_8), "test/constfold.til:641:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_serialized_values_are_compositional_12), "test/constfold.til:475:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_serialized_values_are_compositional_14), "test/constfold.til:476:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_serialized_values_are_compositional_17), "test/constfold.til:478:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_serialized_values_are_compositional_2), "test/constfold.til:470:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_serialized_values_are_compositional_21), "test/constfold.til:479:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_serialized_values_are_compositional_6), "test/constfold.til:471:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_serialized_values_are_compositional_9), "test/constfold.til:474:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_simple_add_3), "test/constfold.til:15:5", 23ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_1), "test/constfold.til:488:28", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_11), "test/constfold.til:484:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_13), "test/constfold.til:485:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_15), "test/constfold.til:486:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_17), "test/constfold.til:491:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_19), "test/constfold.til:496:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_3), "test/constfold.til:489:11", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_5), "test/constfold.til:493:32", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_7), "test/constfold.til:494:11", 25ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_static_global_initializers_9), "test/constfold.til:483:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_string_concat_3), "test/constfold.til:33:5", 23ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_f32_11), "test/constfold.til:240:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_f32_5), "test/constfold.til:238:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_f32_8), "test/constfold.til:239:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_nested_1), "test/constfold.til:212:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_nested_3), "test/constfold.til:213:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_nested_5), "test/constfold.til:214:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_nested_7), "test/constfold.til:215:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_simple_1), "test/constfold.til:184:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_simple_3), "test/constfold.til:185:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_values_11), "test/constfold.til:195:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_values_13), "test/constfold.til:196:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_values_3), "test/constfold.til:191:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_values_5), "test/constfold.til:192:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_values_7), "test/constfold.til:193:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_struct_fold_values_9), "test/constfold.til:194:5", 24ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_variadic_direct_fold_12), "test/constfold.til:72:5", 23ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_variadic_direct_fold_21), "test/constfold.til:74:5", 23ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_variadic_direct_fold_31), "test/constfold.til:76:5", 23ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_variadic_fold_3), "test/constfold.til:49:5", 23ULL},
        {offsetof(__typeof__(*_til_loc_lits_cage), hoisted__Str_test_variadic_fold_8), "test/constfold.til:51:5", 23ULL},
    };
    _til_loc_lits_cage = malloc(sizeof(*_til_loc_lits_cage));
    for (size_t i = 0; i < sizeof(entries) / sizeof(entries[0]); ++i) {
        Str *slot = (Str *)((unsigned char *)_til_loc_lits_cage + entries[i].offset);
        *slot = (Str){.c_str = {til_cage_lit(entries[i].text, entries[i].count)}, .count = entries[i].count, .cap = TIL_CAP_LIT};
    }
}
#define hoisted__Str_Str_push_str_3 (_til_loc_lits_cage->hoisted__Str_Str_push_str_3)
#define hoisted__Str_Str_push_str_7 (_til_loc_lits_cage->hoisted__Str_Str_push_str_7)
#define hoisted__Str_test_block_constants_do_not_escape_their_scope_11 (_til_loc_lits_cage->hoisted__Str_test_block_constants_do_not_escape_their_scope_11)
#define hoisted__Str_test_block_constants_do_not_escape_their_scope_15 (_til_loc_lits_cage->hoisted__Str_test_block_constants_do_not_escape_their_scope_15)
#define hoisted__Str_test_block_constants_do_not_escape_their_scope_19 (_til_loc_lits_cage->hoisted__Str_test_block_constants_do_not_escape_their_scope_19)
#define hoisted__Str_test_block_constants_do_not_escape_their_scope_3 (_til_loc_lits_cage->hoisted__Str_test_block_constants_do_not_escape_their_scope_3)
#define hoisted__Str_test_block_constants_do_not_escape_their_scope_7 (_til_loc_lits_cage->hoisted__Str_test_block_constants_do_not_escape_their_scope_7)
#define hoisted__Str_test_collection_return_fold_102 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_102)
#define hoisted__Str_test_collection_return_fold_105 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_105)
#define hoisted__Str_test_collection_return_fold_110 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_110)
#define hoisted__Str_test_collection_return_fold_115 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_115)
#define hoisted__Str_test_collection_return_fold_118 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_118)
#define hoisted__Str_test_collection_return_fold_129 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_129)
#define hoisted__Str_test_collection_return_fold_134 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_134)
#define hoisted__Str_test_collection_return_fold_14 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_14)
#define hoisted__Str_test_collection_return_fold_143 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_143)
#define hoisted__Str_test_collection_return_fold_148 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_148)
#define hoisted__Str_test_collection_return_fold_150 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_150)
#define hoisted__Str_test_collection_return_fold_155 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_155)
#define hoisted__Str_test_collection_return_fold_19 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_19)
#define hoisted__Str_test_collection_return_fold_24 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_24)
#define hoisted__Str_test_collection_return_fold_29 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_29)
#define hoisted__Str_test_collection_return_fold_34 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_34)
#define hoisted__Str_test_collection_return_fold_39 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_39)
#define hoisted__Str_test_collection_return_fold_4 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_4)
#define hoisted__Str_test_collection_return_fold_44 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_44)
#define hoisted__Str_test_collection_return_fold_49 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_49)
#define hoisted__Str_test_collection_return_fold_54 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_54)
#define hoisted__Str_test_collection_return_fold_59 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_59)
#define hoisted__Str_test_collection_return_fold_64 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_64)
#define hoisted__Str_test_collection_return_fold_69 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_69)
#define hoisted__Str_test_collection_return_fold_72 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_72)
#define hoisted__Str_test_collection_return_fold_74 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_74)
#define hoisted__Str_test_collection_return_fold_79 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_79)
#define hoisted__Str_test_collection_return_fold_84 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_84)
#define hoisted__Str_test_collection_return_fold_87 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_87)
#define hoisted__Str_test_collection_return_fold_89 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_89)
#define hoisted__Str_test_collection_return_fold_9 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_9)
#define hoisted__Str_test_collection_return_fold_92 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_92)
#define hoisted__Str_test_collection_return_fold_97 (_til_loc_lits_cage->hoisted__Str_test_collection_return_fold_97)
#define hoisted__Str_test_const_and_or_fold_10 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_10)
#define hoisted__Str_test_const_and_or_fold_16 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_16)
#define hoisted__Str_test_const_and_or_fold_21 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_21)
#define hoisted__Str_test_const_and_or_fold_27 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_27)
#define hoisted__Str_test_const_and_or_fold_32 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_32)
#define hoisted__Str_test_const_and_or_fold_38 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_38)
#define hoisted__Str_test_const_and_or_fold_43 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_43)
#define hoisted__Str_test_const_and_or_fold_49 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_49)
#define hoisted__Str_test_const_and_or_fold_54 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_54)
#define hoisted__Str_test_const_and_or_fold_58 (_til_loc_lits_cage->hoisted__Str_test_const_and_or_fold_58)
#define hoisted__Str_test_constfold_abort_after_release_3 (_til_loc_lits_cage->hoisted__Str_test_constfold_abort_after_release_3)
#define hoisted__Str_test_constfold_abort_after_release_9 (_til_loc_lits_cage->hoisted__Str_test_constfold_abort_after_release_9)
#define hoisted__Str_test_constfold_abort_branch_locals_3 (_til_loc_lits_cage->hoisted__Str_test_constfold_abort_branch_locals_3)
#define hoisted__Str_test_constfold_abort_branch_locals_9 (_til_loc_lits_cage->hoisted__Str_test_constfold_abort_branch_locals_9)
#define hoisted__Str_test_constfold_abort_owned_args_3 (_til_loc_lits_cage->hoisted__Str_test_constfold_abort_owned_args_3)
#define hoisted__Str_test_constfold_abort_owned_args_9 (_til_loc_lits_cage->hoisted__Str_test_constfold_abort_owned_args_9)
#define hoisted__Str_test_deeply_nested_7 (_til_loc_lits_cage->hoisted__Str_test_deeply_nested_7)
#define hoisted__Str_test_enum_fold_1 (_til_loc_lits_cage->hoisted__Str_test_enum_fold_1)
#define hoisted__Str_test_enum_fold_4 (_til_loc_lits_cage->hoisted__Str_test_enum_fold_4)
#define hoisted__Str_test_enum_literal_fold_10 (_til_loc_lits_cage->hoisted__Str_test_enum_literal_fold_10)
#define hoisted__Str_test_enum_literal_fold_5 (_til_loc_lits_cage->hoisted__Str_test_enum_literal_fold_5)
#define hoisted__Str_test_enum_literal_fold_7 (_til_loc_lits_cage->hoisted__Str_test_enum_literal_fold_7)
#define hoisted__Str_test_enum_payload_fold_2 (_til_loc_lits_cage->hoisted__Str_test_enum_payload_fold_2)
#define hoisted__Str_test_enum_payload_fold_5 (_til_loc_lits_cage->hoisted__Str_test_enum_payload_fold_5)
#define hoisted__Str_test_enum_payload_return_fold_2 (_til_loc_lits_cage->hoisted__Str_test_enum_payload_return_fold_2)
#define hoisted__Str_test_enum_payload_return_fold_5 (_til_loc_lits_cage->hoisted__Str_test_enum_payload_return_fold_5)
#define hoisted__Str_test_enum_return_fold_1 (_til_loc_lits_cage->hoisted__Str_test_enum_return_fold_1)
#define hoisted__Str_test_enum_return_fold_4 (_til_loc_lits_cage->hoisted__Str_test_enum_return_fold_4)
#define hoisted__Str_test_explicit_tag_enum_return_fold_1 (_til_loc_lits_cage->hoisted__Str_test_explicit_tag_enum_return_fold_1)
#define hoisted__Str_test_explicit_tag_enum_return_fold_3 (_til_loc_lits_cage->hoisted__Str_test_explicit_tag_enum_return_fold_3)
#define hoisted__Str_test_explicit_tag_enum_return_fold_6 (_til_loc_lits_cage->hoisted__Str_test_explicit_tag_enum_return_fold_6)
#define hoisted__Str_test_fold_f32_4 (_til_loc_lits_cage->hoisted__Str_test_fold_f32_4)
#define hoisted__Str_test_fold_f32_9 (_til_loc_lits_cage->hoisted__Str_test_fold_f32_9)
#define hoisted__Str_test_fold_reads_global_const_3 (_til_loc_lits_cage->hoisted__Str_test_fold_reads_global_const_3)
#define hoisted__Str_test_fold_variable_2 (_til_loc_lits_cage->hoisted__Str_test_fold_variable_2)
#define hoisted__Str_test_loc_folded_3 (_til_loc_lits_cage->hoisted__Str_test_loc_folded_3)
#define hoisted__Str_test_loc_folded_7 (_til_loc_lits_cage->hoisted__Str_test_loc_folded_7)
#define hoisted__Str_test_lolalalo_8 (_til_loc_lits_cage->hoisted__Str_test_lolalalo_8)
#define hoisted__Str_test_lolalalo_9 (_til_loc_lits_cage->hoisted__Str_test_lolalalo_9)
#define hoisted__Str_test_mixed_fold_4 (_til_loc_lits_cage->hoisted__Str_test_mixed_fold_4)
#define hoisted__Str_test_nested_arithmetic_7 (_til_loc_lits_cage->hoisted__Str_test_nested_arithmetic_7)
#define hoisted__Str_test_nested_enum_payload_return_fold_1 (_til_loc_lits_cage->hoisted__Str_test_nested_enum_payload_return_fold_1)
#define hoisted__Str_test_nested_enum_payload_return_fold_3 (_til_loc_lits_cage->hoisted__Str_test_nested_enum_payload_return_fold_3)
#define hoisted__Str_test_nested_enum_payload_return_fold_5 (_til_loc_lits_cage->hoisted__Str_test_nested_enum_payload_return_fold_5)
#define hoisted__Str_test_runtime_bindings_shadow_global_constants_12 (_til_loc_lits_cage->hoisted__Str_test_runtime_bindings_shadow_global_constants_12)
#define hoisted__Str_test_runtime_bindings_shadow_global_constants_16 (_til_loc_lits_cage->hoisted__Str_test_runtime_bindings_shadow_global_constants_16)
#define hoisted__Str_test_runtime_bindings_shadow_global_constants_2 (_til_loc_lits_cage->hoisted__Str_test_runtime_bindings_shadow_global_constants_2)
#define hoisted__Str_test_runtime_bindings_shadow_global_constants_20 (_til_loc_lits_cage->hoisted__Str_test_runtime_bindings_shadow_global_constants_20)
#define hoisted__Str_test_runtime_bindings_shadow_global_constants_5 (_til_loc_lits_cage->hoisted__Str_test_runtime_bindings_shadow_global_constants_5)
#define hoisted__Str_test_runtime_bindings_shadow_global_constants_8 (_til_loc_lits_cage->hoisted__Str_test_runtime_bindings_shadow_global_constants_8)
#define hoisted__Str_test_serialized_values_are_compositional_12 (_til_loc_lits_cage->hoisted__Str_test_serialized_values_are_compositional_12)
#define hoisted__Str_test_serialized_values_are_compositional_14 (_til_loc_lits_cage->hoisted__Str_test_serialized_values_are_compositional_14)
#define hoisted__Str_test_serialized_values_are_compositional_17 (_til_loc_lits_cage->hoisted__Str_test_serialized_values_are_compositional_17)
#define hoisted__Str_test_serialized_values_are_compositional_2 (_til_loc_lits_cage->hoisted__Str_test_serialized_values_are_compositional_2)
#define hoisted__Str_test_serialized_values_are_compositional_21 (_til_loc_lits_cage->hoisted__Str_test_serialized_values_are_compositional_21)
#define hoisted__Str_test_serialized_values_are_compositional_6 (_til_loc_lits_cage->hoisted__Str_test_serialized_values_are_compositional_6)
#define hoisted__Str_test_serialized_values_are_compositional_9 (_til_loc_lits_cage->hoisted__Str_test_serialized_values_are_compositional_9)
#define hoisted__Str_test_simple_add_3 (_til_loc_lits_cage->hoisted__Str_test_simple_add_3)
#define hoisted__Str_test_static_global_initializers_1 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_1)
#define hoisted__Str_test_static_global_initializers_11 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_11)
#define hoisted__Str_test_static_global_initializers_13 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_13)
#define hoisted__Str_test_static_global_initializers_15 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_15)
#define hoisted__Str_test_static_global_initializers_17 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_17)
#define hoisted__Str_test_static_global_initializers_19 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_19)
#define hoisted__Str_test_static_global_initializers_3 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_3)
#define hoisted__Str_test_static_global_initializers_5 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_5)
#define hoisted__Str_test_static_global_initializers_7 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_7)
#define hoisted__Str_test_static_global_initializers_9 (_til_loc_lits_cage->hoisted__Str_test_static_global_initializers_9)
#define hoisted__Str_test_string_concat_3 (_til_loc_lits_cage->hoisted__Str_test_string_concat_3)
#define hoisted__Str_test_struct_fold_f32_11 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_f32_11)
#define hoisted__Str_test_struct_fold_f32_5 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_f32_5)
#define hoisted__Str_test_struct_fold_f32_8 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_f32_8)
#define hoisted__Str_test_struct_fold_nested_1 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_nested_1)
#define hoisted__Str_test_struct_fold_nested_3 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_nested_3)
#define hoisted__Str_test_struct_fold_nested_5 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_nested_5)
#define hoisted__Str_test_struct_fold_nested_7 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_nested_7)
#define hoisted__Str_test_struct_fold_simple_1 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_simple_1)
#define hoisted__Str_test_struct_fold_simple_3 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_simple_3)
#define hoisted__Str_test_struct_fold_values_11 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_values_11)
#define hoisted__Str_test_struct_fold_values_13 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_values_13)
#define hoisted__Str_test_struct_fold_values_3 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_values_3)
#define hoisted__Str_test_struct_fold_values_5 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_values_5)
#define hoisted__Str_test_struct_fold_values_7 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_values_7)
#define hoisted__Str_test_struct_fold_values_9 (_til_loc_lits_cage->hoisted__Str_test_struct_fold_values_9)
#define hoisted__Str_test_variadic_direct_fold_12 (_til_loc_lits_cage->hoisted__Str_test_variadic_direct_fold_12)
#define hoisted__Str_test_variadic_direct_fold_21 (_til_loc_lits_cage->hoisted__Str_test_variadic_direct_fold_21)
#define hoisted__Str_test_variadic_direct_fold_31 (_til_loc_lits_cage->hoisted__Str_test_variadic_direct_fold_31)
#define hoisted__Str_test_variadic_fold_3 (_til_loc_lits_cage->hoisted__Str_test_variadic_fold_3)
#define hoisted__Str_test_variadic_fold_8 (_til_loc_lits_cage->hoisted__Str_test_variadic_fold_8)

static TilCPtr _til_precomputed_sequence_22_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        I64 *a = calloc(4ULL, sizeof(I64));
        a[0] = (I64)(11);
        a[1] = (I64)(22);
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static Vec__I64 *_til_precomputed_sequence_22_get(void) {
    static Vec__I64 t;
    static Bool built;
    if (built == 0) {
        t = (Vec__I64){.data = _til_precomputed_sequence_22_data_cptr(), .count = 2ULL, .cap = 4ULL};
        built = 1;
    }
    return &t;
}
static TilCPtr _til_precomputed_sequence_23_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        I64 *a = calloc(4ULL, sizeof(I64));
        a[0] = (I64)(11);
        a[1] = (I64)(22);
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static Vec__I64 *_til_precomputed_sequence_23_get(void) {
    static Vec__I64 t;
    static Bool built;
    if (built == 0) {
        t = (Vec__I64){.data = _til_precomputed_sequence_23_data_cptr(), .count = 2ULL, .cap = 4ULL};
        built = 1;
    }
    return &t;
}
static Vec__I64 *_til_precomputed_sequence_24_get(void) {
    static Vec__I64 t;
    static Bool built;
    if (built == 0) {
        t = (Vec__I64){.data = {0}, .count = 0ULL, .cap = 0ULL};
        built = 1;
    }
    return &t;
}
static TilCPtr _til_precomputed_sequence_25_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        I64 *a = calloc(3ULL, sizeof(I64));
        a[0] = (I64)(3);
        a[1] = (I64)(5);
        a[2] = (I64)(8);
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static Array__I64 *_til_precomputed_sequence_25_get(void) {
    static Array__I64 t;
    static Bool built;
    if (built == 0) {
        t = (Array__I64){.data = _til_precomputed_sequence_25_data_cptr(), .cap = 3ULL};
        built = 1;
    }
    return &t;
}
static TilCPtr _til_precomputed_sequence_26_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        Str *a = calloc(4ULL, sizeof(Str));
        a[0] = (Str){.c_str = TIL_OWN_LIT("a", 1ULL), .count = 1ULL, .cap = TIL_CAP_LIT};
        a[1] = (Str){.c_str = TIL_OWN_LIT("b", 1ULL), .count = 1ULL, .cap = TIL_CAP_LIT};
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static Vec__Str *_til_precomputed_sequence_26_get(void) {
    static Vec__Str t;
    static Bool built;
    if (built == 0) {
        t = (Vec__Str){.data = _til_precomputed_sequence_26_data_cptr(), .count = 2ULL, .cap = 4ULL};
        built = 1;
    }
    return &t;
}
static TilCPtr _til_precomputed_sequence_27_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        I64 *a = calloc(4ULL, sizeof(I64));
        a[0] = (I64)(10);
        a[1] = (I64)(20);
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static Vec__I64 *_til_precomputed_sequence_27_get(void) {
    static Vec__I64 t;
    static Bool built;
    if (built == 0) {
        t = (Vec__I64){.data = _til_precomputed_sequence_27_data_cptr(), .count = 2ULL, .cap = 4ULL};
        built = 1;
    }
    return &t;
}
static TilCPtr _til_precomputed_sequence_28_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        I64 *a = calloc(2ULL, sizeof(I64));
        a[0] = (I64)(1);
        a[1] = (I64)(2);
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static TilCPtr _til_precomputed_sequence_29_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        I64 *a = calloc(1ULL, sizeof(I64));
        a[0] = (I64)(3);
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static TilCPtr _til_precomputed_sequence_30_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        CfNestedValues *a = calloc(2ULL, sizeof(CfNestedValues));
        a[0] = (CfNestedValues){.values = {.data = _til_precomputed_sequence_28_data_cptr(), .count = 2ULL, .cap = 2ULL}};
        a[1] = (CfNestedValues){.values = {.data = _til_precomputed_sequence_29_data_cptr(), .count = 1ULL, .cap = 1ULL}};
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static Vec__CfNestedValues *_til_precomputed_sequence_30_get(void) {
    static Vec__CfNestedValues t;
    static Bool built;
    if (built == 0) {
        t = (Vec__CfNestedValues){.data = _til_precomputed_sequence_30_data_cptr(), .count = 2ULL, .cap = 2ULL};
        built = 1;
    }
    return &t;
}
static TilCPtr _til_precomputed_sequence_31_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        Str *a = calloc(2ULL, sizeof(Str));
        a[0] = (Str){.c_str = TIL_OWN_LIT("alpha", 5ULL), .count = 5ULL, .cap = TIL_CAP_LIT};
        a[1] = (Str){.c_str = TIL_OWN_LIT("beta", 4ULL), .count = 4ULL, .cap = TIL_CAP_LIT};
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static Vec__Str *_til_precomputed_sequence_31_get(void) {
    static Vec__Str t;
    static Bool built;
    if (built == 0) {
        t = (Vec__Str){.data = _til_precomputed_sequence_31_data_cptr(), .count = 2ULL, .cap = 2ULL};
        built = 1;
    }
    return &t;
}
static TilCPtr _til_precomputed_sequence_32_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        Str *a = calloc(2ULL, sizeof(Str));
        a[0] = (Str){.c_str = TIL_OWN_LIT("alpha", 5ULL), .count = 5ULL, .cap = TIL_CAP_LIT};
        a[1] = (Str){.c_str = TIL_OWN_LIT("beta", 4ULL), .count = 4ULL, .cap = TIL_CAP_LIT};
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static Vec__Str *_til_precomputed_sequence_32_get(void) {
    static Vec__Str t;
    static Bool built;
    if (built == 0) {
        t = (Vec__Str){.data = _til_precomputed_sequence_32_data_cptr(), .count = 2ULL, .cap = 2ULL};
        built = 1;
    }
    return &t;
}
static TilCPtr _til_precomputed_sequence_33_data_cptr(void) {
    static TilCPtr built;
    if (built.off == 0) {
        I64 *a = calloc(4ULL, sizeof(I64));
        a[0] = (I64)(11);
        a[1] = (I64)(22);
        built = TIL_OWN_ENC(a);
    }
    return built;
}
static Vec__I64 *_til_precomputed_sequence_33_get(void) {
    static Vec__I64 t;
    static Bool built;
    if (built == 0) {
        t = (Vec__I64){.data = _til_precomputed_sequence_33_data_cptr(), .count = 2ULL, .cap = 4ULL};
        built = 1;
    }
    return &t;
}

USize CAP_LIT = 4294967295;
USize CAP_VIEW = 4294967294;
static I64 STATIC_SCALAR = 42;
static Str STATIC_STR;
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
            if (!(_wcond_Bool_1)) {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (_fc_Array__Str_0->data))) + (((U64)(((U64)(_fi_USize_0)) * 12ULL))))));
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
            if (!(_wcond_Bool_8)) {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (_fc_Array__Str_7->data))) + (((U64)(((U64)(_fi_USize_7)) * 12ULL))))));
            U32 hoisted__U32_10 = 1;
            U32 hoisted__U32_11 = ((U32)(_fi_USize_7 + hoisted__U32_10));
            _fi_USize_7 = hoisted__U32_11;
            Str_push_str(&out, s);
        }
    }
    Array__Str_delete(parts, 0);
    { Str _ret = out; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static I64 Str_cmp(Str * a, Str * b) {
    U32 min_len = a->count;
    Bool hoisted__Bool_4 = ((Bool)(b->count < a->count));
    if (hoisted__Bool_4) {
        min_len = b->count;
    }
    I32 c = memcmp(TIL_OWN_GET(I8, (a->c_str)), TIL_OWN_GET(I8, (b->c_str)), min_len);
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
    Bool hoisted__Bool_8 = ptr_eq(TIL_OWN_GET(I8, (a->c_str)), TIL_OWN_GET(I8, (b->c_str)));
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
    I8 *hoisted__I8_13 = ((I8 *)((void *)((U8 *)(TIL_OWN_GET(I8, (a->c_str))) + (hoisted__U32_11))));
    I8 *hoisted__I8_14 = ((I8 *)((void *)((U8 *)(TIL_OWN_GET(I8, (b->c_str))) + (hoisted__U32_12))));
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
    I8 *hoisted__I8_19 = ((I8 *)((void *)((U8 *)(TIL_OWN_GET(I8, (a->c_str))) + (last))));
    I8 *hoisted__I8_20 = ((I8 *)((void *)((U8 *)(TIL_OWN_GET(I8, (b->c_str))) + (last))));
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
    void *hoisted__v_27 = ((void *)((U8 *)(TIL_OWN_GET(I8, (a->c_str))) + (hoisted__U64_24)));
    void *hoisted__v_28 = ((void *)((U8 *)(TIL_OWN_GET(I8, (b->c_str))) + (hoisted__U64_25)));
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
    TIL_OWN_SET((hoisted__Str_Str_with_capacity_6.c_str), (buf));
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
        Str hoisted__Str_Str_push_str_2 = (Str){.c_str = TIL_OWN_LIT("Str.push_str: cannot mutate a string view or literal", 52ULL), .count = 52ULL, .cap = TIL_CAP_LIT};
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
        Str hoisted__Str_Str_push_str_6 = (Str){.c_str = TIL_OWN_LIT("Str.push_str: capacity exceeded", 31ULL), .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_1, hoisted__U32_5, &hoisted__Str_Str_push_str_6, &_va_Array_1_ek);
        panic(&_va_Array_1, &hoisted__Str_Str_push_str_7);
    }
    void *hoisted__v_12 = ((void *)((U8 *)(TIL_OWN_GET(I8, (self->c_str))) + (self->count)));
    memcpy(hoisted__v_12, TIL_OWN_GET(I8, (s->c_str)), s->count);
    self->count = (new_len);
    void *hoisted__v_13 = ((void *)((U8 *)(TIL_OWN_GET(I8, (self->c_str))) + (new_len)));
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
    memcpy(new_data, TIL_OWN_GET(I8, (val->c_str)), val->count);
    void *hoisted__v_4 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_5 = 0;
    U64 hoisted__U64_6 = 1ULL;
    memset(hoisted__v_4, hoisted__I32_5, hoisted__U64_6);
    Str hoisted__Str_Str_clone_7 = {0};
    TIL_OWN_SET((hoisted__Str_Str_clone_7.c_str), (new_data));
    hoisted__Str_Str_clone_7.count = val->count;
    hoisted__Str_Str_clone_7.cap = val->count;
    { Str _ret = hoisted__Str_Str_clone_7; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static Str Str_to_str(Str * self) {
    Str hoisted__Str_Str_to_str_0 = Str_clone(self);
    { Str _ret = hoisted__Str_Str_to_str_0; if (_ret.cap == TIL_CAP_LIT) { _ret.cap = TIL_CAP_VIEW; } return _ret; }
}

static void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_5 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_5) {
        free(TIL_OWN_GET(I8, (self->c_str)));
    }
    Bool _m_Bool_0 = 0;
    {
        Bool hoisted__Bool_3 = 1;
        Bool hoisted__Bool_4 = ((Bool)(call_free == hoisted__Bool_3));
        if (hoisted__Bool_4) {
            Bool hoisted__Bool_1 = ((Bool)(self->cap != CAP_LIT));
            _m_Bool_0 = hoisted__Bool_1;
        } else {
            Bool hoisted__Bool_2 = 0;
            _m_Bool_0 = hoisted__Bool_2;
        }
    }
    if (_m_Bool_0) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

static Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_0 = Str_eq(a, b);
    Bool hoisted__Bool_1 = ((Bool)(!(hoisted__Bool_0)));
    return hoisted__Bool_1;
}

static Array__Str Array__Str_new(USize cap) {
    void * hoisted__v_1 = calloc(((U64)(cap)), 12ULL);
    Array__Str hoisted__Array__Str_2 = {0};
    TIL_OWN_SET((hoisted__Array__Str_2.data), (hoisted__v_1));
    hoisted__Array__Str_2.cap = cap;
    return hoisted__Array__Str_2;
}

static void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_Array__Str_unsafe_set_0 = ((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (((U64)(((U64)(i)) * 12ULL))))));
    Str_delete(hoisted__Str_Array__Str_unsafe_set_0, 0);
    Str *hoisted__Str_Array__Str_unsafe_set_1 = ((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (((U64)(((U64)(i)) * 12ULL))))));
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
        Str_delete(val, 0);
    }
}

static void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_0 = self->cap;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (!(_wcond_Bool_1)) {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U64 hoisted__U64_3 = ((U64)(i));
            U64 hoisted__U64_4 = 12ULL;
            U64 hoisted__U64_5 = ((U64)(hoisted__U64_3 * hoisted__U64_4));
            Str *hoisted__Str_Array__Str_delete_6 = ((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (hoisted__U64_5)));
            Str_delete(hoisted__Str_Array__Str_delete_6, 0);
        }
    }
    free(TIL_OWN_GET(U8, (self->data)));
    if (call_free) {
        free(self);
    }
}

static Array__Str Array__Str_clone(Array__Str * self) {
    U64 hoisted__U64_12 = ((U64)(self->cap));
    U64 hoisted__U64_13 = 12ULL;
    U8 *new_data = malloc(((U64)(hoisted__U64_12 * hoisted__U64_13)));
    {
        U32 _re_U32_0 = self->cap;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (!(_wcond_Bool_1)) {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U64 hoisted__U64_3 = ((U64)(i));
            U64 hoisted__U64_4 = 12ULL;
            U64 hoisted__U64_5 = ((U64)(hoisted__U64_3 * hoisted__U64_4));
            Str *src = ((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (hoisted__U64_5)));
            Str cloned = Str_clone(src);
            U64 hoisted__U64_7 = ((U64)(i));
            U64 hoisted__U64_8 = 12ULL;
            U64 hoisted__U64_9 = ((U64)(hoisted__U64_7 * hoisted__U64_8));
            void *hoisted__v_10 = ((void *)((U8 *)(new_data) + (hoisted__U64_9)));
            adopt__Str(hoisted__v_10, &cloned);
        }
    }
    Array__Str hoisted__Array__Str_14 = {0};
    TIL_OWN_SET((hoisted__Array__Str_14.data), (new_data));
    hoisted__Array__Str_14.cap = self->cap;
    return hoisted__Array__Str_14;
}

static void Vec__Str_clear(Vec__Str * self) {
    {
        U32 _re_U32_0 = self->count;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (!(_wcond_Bool_1)) {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U64 hoisted__U64_3 = ((U64)(i));
            U64 hoisted__U64_4 = 12ULL;
            U64 hoisted__U64_5 = ((U64)(hoisted__U64_3 * hoisted__U64_4));
            Str *hoisted__Str_Vec__Str_clear_6 = ((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (hoisted__U64_5)));
            Str_delete(hoisted__Str_Vec__Str_clear_6, 0);
        }
    }
    U32 hoisted__U32_7 = 0;
    self->count = hoisted__U32_7;
}

static void Vec__Str_unsafe_set(Vec__Str * self, USize i, Str * val) {
    Str *hoisted__Str_Vec__Str_unsafe_set_0 = ((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (((U64)(((U64)(i)) * 12ULL))))));
    Str_delete(hoisted__Str_Vec__Str_unsafe_set_0, 0);
    Str *hoisted__Str_Vec__Str_unsafe_set_1 = ((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (((U64)(((U64)(i)) * 12ULL))))));
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
        Str_delete(val, 0);
    }
}

static void Vec__Str_delete(Vec__Str * self, Bool call_free) {
    Vec__Str_clear(self);
    free(TIL_OWN_GET(U8, (self->data)));
    if (call_free) {
        free(self);
    }
}

static Vec__Str Vec__Str_clone(Vec__Str * self) {
    U32 hoisted__U32_12 = 0;
    Bool hoisted__Bool_13 = ((Bool)(self->cap == hoisted__U32_12));
    if (hoisted__Bool_13) {
        Vec__Str hoisted__Vec__Str_0 = {0};
        TIL_OWN_SET((hoisted__Vec__Str_0.data), (NULL));
        hoisted__Vec__Str_0.count = 0;
        hoisted__Vec__Str_0.cap = 0;
        return hoisted__Vec__Str_0;
    }
    U64 hoisted__U64_15 = ((U64)(self->cap));
    U64 hoisted__U64_16 = 12ULL;
    U8 *new_data = malloc(((U64)(hoisted__U64_15 * hoisted__U64_16)));
    {
        U32 _re_U32_1 = self->count;
        U32 _rc_U32_1 = 0;
        while (1) {
            Bool _wcond_Bool_2 = ((Bool)(_rc_U32_1 < _re_U32_1));
            if (!(_wcond_Bool_2)) {
                break;
            }
            U32 i = (_rc_U32_1);
            (++_rc_U32_1);
            U64 hoisted__U64_4 = ((U64)(i));
            U64 hoisted__U64_5 = 12ULL;
            U64 hoisted__U64_6 = ((U64)(hoisted__U64_4 * hoisted__U64_5));
            Str *src = ((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (hoisted__U64_6)));
            Str cloned = Str_clone(src);
            U64 hoisted__U64_8 = ((U64)(i));
            U64 hoisted__U64_9 = 12ULL;
            U64 hoisted__U64_10 = ((U64)(hoisted__U64_8 * hoisted__U64_9));
            void *hoisted__v_11 = ((void *)((U8 *)(new_data) + (hoisted__U64_10)));
            adopt__Str(hoisted__v_11, &cloned);
        }
    }
    Vec__Str hoisted__Vec__Str_17 = {0};
    TIL_OWN_SET((hoisted__Vec__Str_17.data), (new_data));
    hoisted__Vec__Str_17.count = self->count;
    hoisted__Vec__Str_17.cap = self->cap;
    return hoisted__Vec__Str_17;
}

static void adopt__Str(void * dest, Str * src) {
    U64 hoisted__U64_1 = 12ULL;
    memcpy(dest, src, hoisted__U64_1);
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
        Str hoisted__Str_I64_to_str_4 = (Str){.c_str = TIL_OWN_LIT("-", 1ULL), .count = 1ULL, .cap = TIL_CAP_LIT};
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

static __attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_0 = 3;
    Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
    I64 _va_Array_0_ek = 0;
    U32 hoisted__U32_1 = 0;
    Str hoisted__Str_panic_2 = Str_clone(loc);
    Array__Str_set(&_va_Array_0, hoisted__U32_1, &hoisted__Str_panic_2, &_va_Array_0_ek);
    U32 hoisted__U32_3 = 1;
    Str hoisted__Str_panic_4 = (Str){.c_str = TIL_OWN_LIT(": panic: ", 9ULL), .count = 9ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_0, hoisted__U32_3, &hoisted__Str_panic_4, &_va_Array_0_ek);
    Array__Str hoisted__Array__Str_5 = Array__Str_clone(parts);
    U32 hoisted__U32_6 = 2;
    Str hoisted__Str_panic_7 = format(&hoisted__Array__Str_5);
    Array__Str_set(&_va_Array_0, hoisted__U32_6, &hoisted__Str_panic_7, &_va_Array_0_ek);
    println(&_va_Array_0);
    Array__Str_delete(parts, 0);
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
        Str hoisted__Str_UNREACHABLE_2 = (Str){.c_str = TIL_OWN_LIT("unreachable", 11ULL), .count = 11ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &hoisted__Str_UNREACHABLE_2, &_va_Array_0_ek);
        panic(&_va_Array_0, loc);
    } else {
        U32 hoisted__U32_3 = 2;
        Array__Str _va_Array_1 = Array__Str_new(hoisted__U32_3);
        I64 _va_Array_1_ek = 0;
        U32 hoisted__U32_4 = 0;
        Str hoisted__Str_UNREACHABLE_5 = (Str){.c_str = TIL_OWN_LIT("unreachable: ", 13ULL), .count = 13ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_1, hoisted__U32_4, &hoisted__Str_UNREACHABLE_5, &_va_Array_1_ek);
        Array__Str hoisted__Array__Str_6 = Array__Str_clone(parts);
        U32 hoisted__U32_7 = 1;
        Str hoisted__Str_UNREACHABLE_8 = format(&hoisted__Array__Str_6);
        Array__Str_set(&_va_Array_1, hoisted__U32_7, &hoisted__Str_UNREACHABLE_8, &_va_Array_1_ek);
        panic(&_va_Array_1, loc);
    }
}

static void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_3 = ((Bool)(!(cond)));
    if (hoisted__Bool_3) {
        U32 hoisted__U32_0 = 1;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        Str hoisted__Str_assert_2 = (Str){.c_str = TIL_OWN_LIT("assert failed", 13ULL), .count = 13ULL, .cap = TIL_CAP_LIT};
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
        Str hoisted__Str_expect_2 = (Str){.c_str = TIL_OWN_LIT("assert failed: ", 15ULL), .count = 15ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &hoisted__Str_expect_2, &_va_Array_0_ek);
        Array__Str hoisted__Array__Str_3 = Array__Str_clone(parts);
        U32 hoisted__U32_4 = 1;
        Str hoisted__Str_expect_5 = format(&hoisted__Array__Str_3);
        Array__Str_set(&_va_Array_0, hoisted__U32_4, &hoisted__Str_expect_5, &_va_Array_0_ek);
        panic(&_va_Array_0, loc);
    }
    Array__Str_delete(parts, 0);
}

static void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_0 = parts;
        USize _fi_USize_0 = 0;
        while (1) {
            U32 hoisted__U32_2 = (_fc_Array__Str_0->cap);
            Bool _wcond_Bool_1 = ((Bool)(_fi_USize_0 < hoisted__U32_2));
            if (!(_wcond_Bool_1)) {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (_fc_Array__Str_0->data))) + (((U64)(((U64)(_fi_USize_0)) * 12ULL))))));
            U32 hoisted__U32_3 = 1;
            U32 hoisted__U32_4 = ((U32)(_fi_USize_0 + hoisted__U32_3));
            _fi_USize_0 = hoisted__U32_4;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 0);
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
    Str result = (Str){.c_str = TIL_OWN_LIT("hello world", 11ULL), .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&result, &_til_str_lits.h3fd43551c8c1, &hoisted__Str_test_string_concat_3);
}

static void test_variadic_fold(void) {
    Str r = (Str){.c_str = TIL_OWN_LIT("hello world", 11ULL), .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r, &_til_str_lits.h3fd43551c8c1, &hoisted__Str_test_variadic_fold_3);
    Str r2 = (Str){.c_str = TIL_OWN_LIT("a-b-c", 5ULL), .count = 5ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_test_variadic_fold_7 = (Str){.c_str = TIL_OWN_LIT("a-b-c", 5ULL), .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r2, &hoisted__Str_test_variadic_fold_7, &hoisted__Str_test_variadic_fold_8);
}

static void test_variadic_direct_fold(void) {
    Str d = (Str){.c_str = TIL_OWN_LIT("x-y-z", 5ULL), .count = 5ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_test_variadic_direct_fold_11 = (Str){.c_str = TIL_OWN_LIT("x-y-z", 5ULL), .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d, &hoisted__Str_test_variadic_direct_fold_11, &hoisted__Str_test_variadic_direct_fold_12);
    Str d2 = (Str){.c_str = TIL_OWN_LIT("abc", 3ULL), .count = 3ULL, .cap = TIL_CAP_LIT};
    Str hoisted__Str_test_variadic_direct_fold_20 = (Str){.c_str = TIL_OWN_LIT("abc", 3ULL), .count = 3ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d2, &hoisted__Str_test_variadic_direct_fold_20, &hoisted__Str_test_variadic_direct_fold_21);
    I64 d3 = 106;
    I64 hoisted__I64_30 = 106;
    assert_eq__I64(d3, hoisted__I64_30, &hoisted__Str_test_variadic_direct_fold_31);
}

static void test_lolalalo(void) {
    Str lola_rec = (Str){.c_str = TIL_OWN_LIT("lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", 224ULL), .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lola_it = (Str){.c_str = TIL_OWN_LIT("lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", 224ULL), .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_rec = (Str){.c_str = TIL_OWN_LIT("lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", 224ULL), .count = 224ULL, .cap = TIL_CAP_LIT};
    Str lalo_it = (Str){.c_str = TIL_OWN_LIT("lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", 224ULL), .count = 224ULL, .cap = TIL_CAP_LIT};
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
    Str hoisted__Str_test_struct_fold_f32_4 = (Str){.c_str = TIL_OWN_LIT("3", 1ULL), .count = 1ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&hoisted__Str_test_struct_fold_f32_3, &hoisted__Str_test_struct_fold_f32_4, &hoisted__Str_test_struct_fold_f32_5);
    Str_delete(&hoisted__Str_test_struct_fold_f32_3, 0);
    Str hoisted__Str_test_struct_fold_f32_6 = ({ Str *_hp = (Str *)F32_to_str(v.y); Str _hv = *_hp; if (_hp->cap != TIL_CAP_LIT) { free(_hp); } if (_hv.cap == TIL_CAP_LIT) { _hv.cap = TIL_CAP_VIEW; } _hv; });
    Str hoisted__Str_test_struct_fold_f32_7 = (Str){.c_str = TIL_OWN_LIT("4", 1ULL), .count = 1ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&hoisted__Str_test_struct_fold_f32_6, &hoisted__Str_test_struct_fold_f32_7, &hoisted__Str_test_struct_fold_f32_8);
    Str_delete(&hoisted__Str_test_struct_fold_f32_6, 0);
    Str hoisted__Str_test_struct_fold_f32_9 = ({ Str *_hp = (Str *)F32_to_str(v.z); Str _hv = *_hp; if (_hp->cap != TIL_CAP_LIT) { free(_hp); } if (_hv.cap == TIL_CAP_LIT) { _hv.cap = TIL_CAP_VIEW; } _hv; });
    Str hoisted__Str_test_struct_fold_f32_10 = (Str){.c_str = TIL_OWN_LIT("5", 1ULL), .count = 1ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&hoisted__Str_test_struct_fold_f32_9, &hoisted__Str_test_struct_fold_f32_10, &hoisted__Str_test_struct_fold_f32_11);
    Str_delete(&hoisted__Str_test_struct_fold_f32_9, 0);
}

static Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_0 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_0;
}

static Color Color_clone(Color * self) {
    switch ((DEREF(self)).tag) {
    case Color_TAG_Red: {
        return (Color){.tag = Color_TAG_Red};
    }
    case Color_TAG_Green: {
        return (Color){.tag = Color_TAG_Green};
    }
    default: {
        return (Color){.tag = Color_TAG_Blue};
    }
    }
    __builtin_unreachable();
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
    Str _m_Str_0 = (Str){.c_str = TIL_OWN_LIT("", 0ULL), .count = 0ULL, .cap = TIL_CAP_LIT};
    {
        Bool hoisted__Bool_3 = ((Bool)(1));
        if (hoisted__Bool_3) {
            { Str _new = _til_str_lits.h00000002b617; Str_delete(&_m_Str_0, (Bool){0}); _m_Str_0 = _new; }
        } else {
            Bool hoisted__Bool_2 = ((Bool)(0));
            if (hoisted__Bool_2) {
                { Str _new = (Str){.c_str = TIL_OWN_LIT("g", 1ULL), .count=1ULL, .cap=TIL_CAP_LIT}; Str_delete(&_m_Str_0, (Bool){0}); _m_Str_0 = _new; }
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
    Str_delete(&_m_Str_0, 0);
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
    switch ((DEREF(self)).tag) {
    case Token_TAG_Name: {
        Str *hoisted__Str_Token_delete_0 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Str_delete(hoisted__Str_Token_delete_0, 0);
        break;
    }
    default: {
        break;
    }
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
    Token_delete(&t, 0);
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
    Token_delete(&t, 0);
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
    switch ((DEREF(self)).tag) {
    case WideToken_TAG_Num: {
        I64 *_clone_payload_Num_0 = ((void *)((U8 *)(self) + offsetof(WideToken, data)));
        WideToken hoisted__WideToken_0 = WideToken_Num(_clone_payload_Num_0);
        return hoisted__WideToken_0;
    }
    default: {
        return (WideToken){.tag = WideToken_TAG_Eof};
    }
    }
    __builtin_unreachable();
}


static NestedToken NestedToken_Inner(WideToken * val) {
    NestedToken r;
    r.data = val;
    return r;
}
static void NestedToken_delete(NestedToken * self, Bool call_free) {
    switch ((int)((DEREF(self)).data != NULL)) {
    case 1: {
        WideToken *hoisted__WideToken_0 = ((void *)((NestedToken *)(self))->data);
        WideToken_delete(hoisted__WideToken_0, 1);
        break;
    }
    default: {
        break;
    }
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
        UNREACHABLE(&_va_Array_0, &hoisted__Str_test_explicit_tag_enum_return_fold_3);
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
            UNREACHABLE(&_va_Array_0, &hoisted__Str_test_nested_enum_payload_return_fold_3);
        }
        }
        break;
    }
    default: {
        U32 hoisted__U32_4 = 0;
        Array__Str _va_Array_1 = Array__Str_new(hoisted__U32_4);
        UNREACHABLE(&_va_Array_1, &hoisted__Str_test_nested_enum_payload_return_fold_5);
    }
    }
    NestedToken_delete(&nested, 0);
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
    Vec__I64 values = Vec__I64_clone(_til_precomputed_sequence_23_get());
    U32 hoisted__U32_70 = 2;
    U32 hoisted__U32_71 = 2;
    assert_eq__USize(hoisted__U32_70, hoisted__U32_71, &hoisted__Str_test_collection_return_fold_72);
    U32 hoisted__U32_73 = 4;
    assert_eq__USize(values.cap, hoisted__U32_73, &hoisted__Str_test_collection_return_fold_74);
    U32 hoisted__U32_75 = 0;
    I64 *_bang_ret_0 = (((Bool)((U32)(hoisted__U32_75) < values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(TIL_OWN_GET(U8, (values.data))) + (((U64)(((U64)((U32)(hoisted__U32_75))) * 8ULL)))))) : (_err_kind = 1, (I64 *)NULL));
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
    I64 *_bang_ret_1 = (((Bool)((U32)(hoisted__U32_80) < values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(TIL_OWN_GET(U8, (values.data))) + (((U64)(((U64)((U32)(hoisted__U32_80))) * 8ULL)))))) : (_err_kind = 1, (I64 *)NULL));
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
    Vec__I64_delete(&values, 0);
    Vec__I64 empty = Vec__I64_clone(_til_precomputed_sequence_24_get());
    U32 hoisted__U32_85 = 0;
    U32 hoisted__U32_86 = 0;
    assert_eq__USize(hoisted__U32_85, hoisted__U32_86, &hoisted__Str_test_collection_return_fold_87);
    U32 hoisted__U32_88 = 0;
    assert_eq__USize(empty.cap, hoisted__U32_88, &hoisted__Str_test_collection_return_fold_89);
    Vec__I64_delete(&empty, 0);
    Array__I64 fixed = Array__I64_clone(_til_precomputed_sequence_25_get());
    U32 hoisted__U32_90 = 3;
    U32 hoisted__U32_91 = 3;
    assert_eq__USize(hoisted__U32_90, hoisted__U32_91, &hoisted__Str_test_collection_return_fold_92);
    U32 hoisted__U32_93 = 0;
    I64 *_bang_ret_2 = (((Bool)((U32)(hoisted__U32_93) < fixed.cap)) ? (I64 *)((I64 *)((void *)((U8 *)(TIL_OWN_GET(U8, (fixed.data))) + (((U64)(((U64)((U32)(hoisted__U32_93))) * 8ULL)))))) : (_err_kind = 1, (I64 *)NULL));
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
    I64 *_bang_ret_3 = (((Bool)((U32)(hoisted__U32_98) < fixed.cap)) ? (I64 *)((I64 *)((void *)((U8 *)(TIL_OWN_GET(U8, (fixed.data))) + (((U64)(((U64)((U32)(hoisted__U32_98))) * 8ULL)))))) : (_err_kind = 1, (I64 *)NULL));
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
    Array__I64_delete(&fixed, 0);
    Map__Str_I64 table = {0};
    table.keys = Vec__Str_clone(_til_precomputed_sequence_26_get());
    table.values = Vec__I64_clone(_til_precomputed_sequence_27_get());
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
    Map__Str_I64_delete(&table, 0);
    Vec__CfNestedValues nested = Vec__CfNestedValues_clone(_til_precomputed_sequence_30_get());
    U32 hoisted__U32_116 = 2;
    U32 hoisted__U32_117 = 2;
    assert_eq__USize(hoisted__U32_116, hoisted__U32_117, &hoisted__Str_test_collection_return_fold_118);
    U32 hoisted__U32_119 = 0;
    CfNestedValues *first_nested = (((Bool)((U32)(hoisted__U32_119) < nested.count)) ? (CfNestedValues *)((CfNestedValues *)((void *)((U8 *)(TIL_OWN_GET(U8, (nested.data))) + (((U64)(((U64)((U32)(hoisted__U32_119))) * 12ULL)))))) : (_err_kind = 1, (CfNestedValues *)NULL));
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
    CfNestedValues *second_nested = (((Bool)((U32)(hoisted__U32_122) < nested.count)) ? (CfNestedValues *)((CfNestedValues *)((void *)((U8 *)(TIL_OWN_GET(U8, (nested.data))) + (((U64)(((U64)((U32)(hoisted__U32_122))) * 12ULL)))))) : (_err_kind = 1, (CfNestedValues *)NULL));
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
    I64 *_bang_ret_6 = (((Bool)((U32)(hoisted__U32_125) < first_nested->values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(TIL_OWN_GET(U8, (first_nested->values.data))) + (((U64)(((U64)((U32)(hoisted__U32_125))) * 8ULL)))))) : (_err_kind = 1, (I64 *)NULL));
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
    I64 *_bang_ret_7 = (((Bool)((U32)(hoisted__U32_130) < second_nested->values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(TIL_OWN_GET(U8, (second_nested->values.data))) + (((U64)(((U64)((U32)(hoisted__U32_130))) * 8ULL)))))) : (_err_kind = 1, (I64 *)NULL));
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
    Vec__Str left = Vec__Str_clone(_til_precomputed_sequence_31_get());
    Vec__Str right = Vec__Str_clone(_til_precomputed_sequence_32_get());
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
    Str *_bang_ret_8 = (((Bool)((U32)(hoisted__U32_139) < left.count)) ? (Str *)((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (left.data))) + (((U64)(((U64)((U32)(hoisted__U32_139))) * 12ULL)))))) : (_err_kind = 1, (Str *)NULL));
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
    Vec__Str_delete(&left, 0);
    U32 hoisted__U32_144 = 0;
    Str *_bang_ret_9 = (((Bool)((U32)(hoisted__U32_144) < right.count)) ? (Str *)((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (right.data))) + (((U64)(((U64)((U32)(hoisted__U32_144))) * 12ULL)))))) : (_err_kind = 1, (Str *)NULL));
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
    Vec__Str_delete(&right, 0);
    Vec__I64 macro_values = Vec__I64_clone(_til_precomputed_sequence_33_get());
    U32 hoisted__U32_149 = 4;
    assert_eq__USize(macro_values.cap, hoisted__U32_149, &hoisted__Str_test_collection_return_fold_150);
    U32 hoisted__U32_151 = 1;
    I64 *_bang_ret_10 = (((Bool)((U32)(hoisted__U32_151) < macro_values.count)) ? (I64 *)((I64 *)((void *)((U8 *)(TIL_OWN_GET(U8, (macro_values.data))) + (((U64)(((U64)((U32)(hoisted__U32_151))) * 8ULL)))))) : (_err_kind = 1, (I64 *)NULL));
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
    Vec__CfNestedValues_delete(&nested, 0);
    I64 hoisted__I64_154 = 22;
    assert_eq__I64(DEREF(_bang_ret_10), hoisted__I64_154, &hoisted__Str_test_collection_return_fold_155);
    Vec__I64_delete(&macro_values, 0);
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
    Str hoisted__Str_test_static_global_initializers_10 = (Str){.c_str = TIL_OWN_LIT("static-folded", 13ULL), .count = 13ULL, .cap = TIL_CAP_LIT};
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
        UNREACHABLE(&_va_Array_0, &hoisted__Str_test_static_global_initializers_3);
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
        UNREACHABLE(&_va_Array_1, &hoisted__Str_test_static_global_initializers_7);
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
    Str hoisted__Str_test_const_and_or_fold_8 = (Str){.c_str = TIL_OWN_LIT("and(T,T)", 8ULL), .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_0, hoisted__U32_7, &hoisted__Str_test_const_and_or_fold_8, &_va_Array_0_ek);
    Bool hoisted__Bool_9 = 1;
    expect(hoisted__Bool_9, &_va_Array_0, &hoisted__Str_test_const_and_or_fold_10);
    U32 hoisted__U32_11 = 1;
    Array__Str _va_Array_1 = Array__Str_new(hoisted__U32_11);
    I64 _va_Array_1_ek = 0;
    U32 hoisted__U32_12 = 0;
    Str hoisted__Str_test_const_and_or_fold_13 = (Str){.c_str = TIL_OWN_LIT("and(T,F)", 8ULL), .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_1, hoisted__U32_12, &hoisted__Str_test_const_and_or_fold_13, &_va_Array_1_ek);
    Bool hoisted__Bool_15 = 1;
    expect(hoisted__Bool_15, &_va_Array_1, &hoisted__Str_test_const_and_or_fold_16);
    U32 hoisted__U32_17 = 1;
    Array__Str _va_Array_2 = Array__Str_new(hoisted__U32_17);
    I64 _va_Array_2_ek = 0;
    U32 hoisted__U32_18 = 0;
    Str hoisted__Str_test_const_and_or_fold_19 = (Str){.c_str = TIL_OWN_LIT("and x3 T", 8ULL), .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_2, hoisted__U32_18, &hoisted__Str_test_const_and_or_fold_19, &_va_Array_2_ek);
    Bool hoisted__Bool_20 = 1;
    expect(hoisted__Bool_20, &_va_Array_2, &hoisted__Str_test_const_and_or_fold_21);
    U32 hoisted__U32_22 = 1;
    Array__Str _va_Array_3 = Array__Str_new(hoisted__U32_22);
    I64 _va_Array_3_ek = 0;
    U32 hoisted__U32_23 = 0;
    Str hoisted__Str_test_const_and_or_fold_24 = (Str){.c_str = TIL_OWN_LIT("and x3 with F", 13ULL), .count = 13ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_3, hoisted__U32_23, &hoisted__Str_test_const_and_or_fold_24, &_va_Array_3_ek);
    Bool hoisted__Bool_26 = 1;
    expect(hoisted__Bool_26, &_va_Array_3, &hoisted__Str_test_const_and_or_fold_27);
    U32 hoisted__U32_28 = 1;
    Array__Str _va_Array_4 = Array__Str_new(hoisted__U32_28);
    I64 _va_Array_4_ek = 0;
    U32 hoisted__U32_29 = 0;
    Str hoisted__Str_test_const_and_or_fold_30 = (Str){.c_str = TIL_OWN_LIT("or(F,T)", 7ULL), .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_4, hoisted__U32_29, &hoisted__Str_test_const_and_or_fold_30, &_va_Array_4_ek);
    Bool hoisted__Bool_31 = 1;
    expect(hoisted__Bool_31, &_va_Array_4, &hoisted__Str_test_const_and_or_fold_32);
    U32 hoisted__U32_33 = 1;
    Array__Str _va_Array_5 = Array__Str_new(hoisted__U32_33);
    I64 _va_Array_5_ek = 0;
    U32 hoisted__U32_34 = 0;
    Str hoisted__Str_test_const_and_or_fold_35 = (Str){.c_str = TIL_OWN_LIT("or(F,F)", 7ULL), .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_5, hoisted__U32_34, &hoisted__Str_test_const_and_or_fold_35, &_va_Array_5_ek);
    Bool hoisted__Bool_37 = 1;
    expect(hoisted__Bool_37, &_va_Array_5, &hoisted__Str_test_const_and_or_fold_38);
    U32 hoisted__U32_39 = 1;
    Array__Str _va_Array_6 = Array__Str_new(hoisted__U32_39);
    I64 _va_Array_6_ek = 0;
    U32 hoisted__U32_40 = 0;
    Str hoisted__Str_test_const_and_or_fold_41 = (Str){.c_str = TIL_OWN_LIT("or x3 with T", 12ULL), .count = 12ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_6, hoisted__U32_40, &hoisted__Str_test_const_and_or_fold_41, &_va_Array_6_ek);
    Bool hoisted__Bool_42 = 1;
    expect(hoisted__Bool_42, &_va_Array_6, &hoisted__Str_test_const_and_or_fold_43);
    U32 hoisted__U32_44 = 1;
    Array__Str _va_Array_7 = Array__Str_new(hoisted__U32_44);
    I64 _va_Array_7_ek = 0;
    U32 hoisted__U32_45 = 0;
    Str hoisted__Str_test_const_and_or_fold_46 = (Str){.c_str = TIL_OWN_LIT("or x3 F", 7ULL), .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_7, hoisted__U32_45, &hoisted__Str_test_const_and_or_fold_46, &_va_Array_7_ek);
    Bool hoisted__Bool_48 = 1;
    expect(hoisted__Bool_48, &_va_Array_7, &hoisted__Str_test_const_and_or_fold_49);
    U32 hoisted__U32_50 = 1;
    Array__Str _va_Array_8 = Array__Str_new(hoisted__U32_50);
    I64 _va_Array_8_ek = 0;
    U32 hoisted__U32_51 = 0;
    Str hoisted__Str_test_const_and_or_fold_52 = (Str){.c_str = TIL_OWN_LIT("T.and(T)", 8ULL), .count = 8ULL, .cap = TIL_CAP_LIT};
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
    Str hoisted__Str_test_const_and_or_fold_57 = (Str){.c_str = TIL_OWN_LIT("F.or(T)", 7ULL), .count = 7ULL, .cap = TIL_CAP_LIT};
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

static I64 cf_abort_if_nonempty(Str * first, Str * second) {
    U32 hoisted__U32_1 = (first->count);
    U32 hoisted__U32_2 = (second->count);
    U32 hoisted__U32_3 = ((U32)(hoisted__U32_1 + hoisted__U32_2));
    U32 hoisted__U32_4 = 0;
    Bool hoisted__Bool_5 = ((Bool)(hoisted__U32_3 > hoisted__U32_4));
    if (hoisted__Bool_5) {
        I64 hoisted__I64_0 = 1;
        exit(hoisted__I64_0);
    }
    I64 hoisted__I64_6 = 0;
    return hoisted__I64_6;
}

static I64 cf_abort_owned_args(Str * first, Str * second) {
    I64 hoisted__I64_0 = cf_abort_if_nonempty(first, second);
    Str_delete(first, 0);
    Str_delete(second, 0);
    return hoisted__I64_0;
}

static I64 cf_abort_owned_branch(Str * first, Str * second) {
    U32 hoisted__U32_6 = (first->count);
    U32 hoisted__U32_7 = 0;
    Bool hoisted__Bool_8 = ((Bool)(hoisted__U32_6 > hoisted__U32_7));
    if (hoisted__Bool_8) {
        U32 hoisted__U32_0 = 2;
        Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        Str hoisted__Str_cf_abort_owned_branch_2 = (Str){.c_str = TIL_OWN_LIT("branch ", 7ULL), .count = 7ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(&_va_Array_0, hoisted__U32_1, &hoisted__Str_cf_abort_owned_branch_2, &_va_Array_0_ek);
        U32 hoisted__U32_3 = 1;
        Str hoisted__Str_cf_abort_owned_branch_4 = Str_clone(first);
        Array__Str_set(&_va_Array_0, hoisted__U32_3, &hoisted__Str_cf_abort_owned_branch_4, &_va_Array_0_ek);
        Str text = format(&_va_Array_0);
        I64 hoisted__I64_5 = cf_abort_if_nonempty(&text, second);
        Str_delete(&text, 0);
        Str_delete(first, 0);
        Str_delete(second, 0);
        return hoisted__I64_5;
    }
    Str_delete(first, 0);
    Str_delete(second, 0);
    I64 hoisted__I64_9 = 0;
    return hoisted__I64_9;
}

static I64 cf_abort_after_release(Str * first, Str * second) {
    U32 hoisted__U32_2 = 2;
    Array__Str _va_Array_0 = Array__Str_new(hoisted__U32_2);
    I64 _va_Array_0_ek = 0;
    U32 hoisted__U32_3 = 0;
    Str hoisted__Str_cf_abort_after_release_4 = Str_clone(first);
    Array__Str_set(&_va_Array_0, hoisted__U32_3, &hoisted__Str_cf_abort_after_release_4, &_va_Array_0_ek);
    U32 hoisted__U32_5 = 1;
    Str hoisted__Str_cf_abort_after_release_6 = (Str){.c_str = TIL_OWN_LIT(" released", 9ULL), .count = 9ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(&_va_Array_0, hoisted__U32_5, &hoisted__Str_cf_abort_after_release_6, &_va_Array_0_ek);
    Str released = format(&_va_Array_0);
    Str_delete(first, 0);
    U32 size = (released.count);
    Str_delete(&released, 0);
    U32 hoisted__U32_7 = 0;
    Bool hoisted__Bool_8 = ((Bool)(size > hoisted__U32_7));
    if (hoisted__Bool_8) {
        I64 hoisted__I64_1 = cf_abort_if_nonempty(&_til_str_lits.h000000001505, second);
        Str_delete(second, 0);
        return hoisted__I64_1;
    }
    Str_delete(second, 0);
    I64 hoisted__I64_9 = 0;
    return hoisted__I64_9;
}

static Bool cf_abort_runtime_guard(void) {
    noop_proc();
    Bool hoisted__Bool_0 = 0;
    return hoisted__Bool_0;
}

static void test_constfold_abort_owned_args(void) {
    Bool hoisted__Bool_4 = cf_abort_runtime_guard();
    if (hoisted__Bool_4) {
        Str hoisted__Str_test_constfold_abort_owned_args_0 = (Str){.c_str = TIL_OWN_LIT("first allocation", 16ULL), .count = 16ULL, .cap = TIL_CAP_LIT};
        Str hoisted__Str_test_constfold_abort_owned_args_1 = (Str){.c_str = TIL_OWN_LIT("second allocation", 17ULL), .count = 17ULL, .cap = TIL_CAP_LIT};
        I64 result = cf_abort_owned_args(&hoisted__Str_test_constfold_abort_owned_args_0, &hoisted__Str_test_constfold_abort_owned_args_1);
        I64 hoisted__I64_2 = 0;
        assert_eq__I64(result, hoisted__I64_2, &hoisted__Str_test_constfold_abort_owned_args_3);
    }
    I64 hoisted__I64_7 = 0;
    I64 hoisted__I64_8 = 0;
    assert_eq__I64(hoisted__I64_7, hoisted__I64_8, &hoisted__Str_test_constfold_abort_owned_args_9);
}

static void test_constfold_abort_branch_locals(void) {
    Bool hoisted__Bool_4 = cf_abort_runtime_guard();
    if (hoisted__Bool_4) {
        Str hoisted__Str_test_constfold_abort_branch_locals_0 = (Str){.c_str = TIL_OWN_LIT("first branch allocation", 23ULL), .count = 23ULL, .cap = TIL_CAP_LIT};
        Str hoisted__Str_test_constfold_abort_branch_locals_1 = (Str){.c_str = TIL_OWN_LIT("second branch allocation", 24ULL), .count = 24ULL, .cap = TIL_CAP_LIT};
        I64 result = cf_abort_owned_branch(&hoisted__Str_test_constfold_abort_branch_locals_0, &hoisted__Str_test_constfold_abort_branch_locals_1);
        I64 hoisted__I64_2 = 0;
        assert_eq__I64(result, hoisted__I64_2, &hoisted__Str_test_constfold_abort_branch_locals_3);
    }
    I64 hoisted__I64_7 = 0;
    I64 hoisted__I64_8 = 0;
    assert_eq__I64(hoisted__I64_7, hoisted__I64_8, &hoisted__Str_test_constfold_abort_branch_locals_9);
}

static void test_constfold_abort_after_release(void) {
    Bool hoisted__Bool_4 = cf_abort_runtime_guard();
    if (hoisted__Bool_4) {
        Str hoisted__Str_test_constfold_abort_after_release_0 = (Str){.c_str = TIL_OWN_LIT("already released", 16ULL), .count = 16ULL, .cap = TIL_CAP_LIT};
        Str hoisted__Str_test_constfold_abort_after_release_1 = (Str){.c_str = TIL_OWN_LIT("remaining allocation", 20ULL), .count = 20ULL, .cap = TIL_CAP_LIT};
        I64 result = cf_abort_after_release(&hoisted__Str_test_constfold_abort_after_release_0, &hoisted__Str_test_constfold_abort_after_release_1);
        I64 hoisted__I64_2 = 0;
        assert_eq__I64(result, hoisted__I64_2, &hoisted__Str_test_constfold_abort_after_release_3);
    }
    I64 hoisted__I64_7 = 0;
    I64 hoisted__I64_8 = 0;
    assert_eq__I64(hoisted__I64_7, hoisted__I64_8, &hoisted__Str_test_constfold_abort_after_release_9);
}

static I64 cf_runtime_input(void) {
    noop_proc();
    I64 hoisted__I64_0 = 5;
    return hoisted__I64_0;
}

static I64 cf_shadow_parameter(I64 CF_SHADOW) {
    I64 hoisted__I64_0 = 2;
    I64 hoisted__I64_1 = ((I64)((U64)(CF_SHADOW) * hoisted__I64_0));
    return hoisted__I64_1;
}

static I64 cf_shadow_local(I64 value) {
    I64 CF_SHADOW = (value);
    I64 hoisted__I64_0 = 3;
    I64 hoisted__I64_1 = ((I64)((U64)(CF_SHADOW) * hoisted__I64_0));
    return hoisted__I64_1;
}

static I64 cf_shadow_ref(I64 value) {
    I64 *CF_REF_SHADOW = &value;
    I64 hoisted__I64_0 = 4;
    I64 hoisted__I64_1 = ((I64)((U64)(DEREF(CF_REF_SHADOW)) * hoisted__I64_0));
    return hoisted__I64_1;
}

static void test_runtime_bindings_shadow_global_constants(void) {
    I64 value = cf_runtime_input();
    I64 hoisted__I64_0 = cf_shadow_parameter(value);
    I64 hoisted__I64_1 = 10;
    assert_eq__I64(hoisted__I64_0, hoisted__I64_1, &hoisted__Str_test_runtime_bindings_shadow_global_constants_2);
    I64 hoisted__I64_3 = cf_shadow_local(value);
    I64 hoisted__I64_4 = 15;
    assert_eq__I64(hoisted__I64_3, hoisted__I64_4, &hoisted__Str_test_runtime_bindings_shadow_global_constants_5);
    I64 hoisted__I64_6 = cf_shadow_ref(value);
    I64 hoisted__I64_7 = 20;
    assert_eq__I64(hoisted__I64_6, hoisted__I64_7, &hoisted__Str_test_runtime_bindings_shadow_global_constants_8);
    I64 hoisted__I64_10 = 14;
    I64 hoisted__I64_11 = 14;
    assert_eq__I64(hoisted__I64_10, hoisted__I64_11, &hoisted__Str_test_runtime_bindings_shadow_global_constants_12);
    I64 hoisted__I64_14 = 34;
    I64 hoisted__I64_15 = 34;
    assert_eq__I64(hoisted__I64_14, hoisted__I64_15, &hoisted__Str_test_runtime_bindings_shadow_global_constants_16);
    I64 hoisted__I64_18 = 194;
    I64 hoisted__I64_19 = 194;
    assert_eq__I64(hoisted__I64_18, hoisted__I64_19, &hoisted__Str_test_runtime_bindings_shadow_global_constants_20);
}

static void test_block_constants_do_not_escape_their_scope(void) {
    I64 hoisted__I64_9 = 22;
    I64 hoisted__I64_10 = 22;
    assert_eq__I64(hoisted__I64_9, hoisted__I64_10, &hoisted__Str_test_block_constants_do_not_escape_their_scope_11);
    {
        I64 hoisted__I64_1 = 34;
        I64 hoisted__I64_2 = 34;
        assert_eq__I64(hoisted__I64_1, hoisted__I64_2, &hoisted__Str_test_block_constants_do_not_escape_their_scope_3);
    }
    I64 hoisted__I64_13 = 33;
    I64 hoisted__I64_14 = 33;
    assert_eq__I64(hoisted__I64_13, hoisted__I64_14, &hoisted__Str_test_block_constants_do_not_escape_their_scope_15);
    {
        I64 CF_SHADOW = cf_runtime_input();
        I64 hoisted__I64_4 = 2;
        I64 hoisted__I64_5 = ((I64)((U64)(CF_SHADOW) * hoisted__I64_4));
        I64 hoisted__I64_6 = 10;
        assert_eq__I64(hoisted__I64_5, hoisted__I64_6, &hoisted__Str_test_block_constants_do_not_escape_their_scope_7);
    }
    I64 hoisted__I64_17 = 22;
    I64 hoisted__I64_18 = 22;
    assert_eq__I64(hoisted__I64_17, hoisted__I64_18, &hoisted__Str_test_block_constants_do_not_escape_their_scope_19);
}

static void test_serialized_binding_keeps_assignment(void) {
    I64 _written_only = 1;
    (void)_written_only;
    I64 hoisted__I64_0 = cf_runtime_input();
    _written_only = hoisted__I64_0;
}

static void Array__I64_delete(Array__I64 * self, Bool call_free) {
    free(TIL_OWN_GET(U8, (self->data)));
    if (call_free) {
        free(self);
    }
}

static Array__I64 Array__I64_clone(Array__I64 * self) {
    U64 hoisted__U64_12 = ((U64)(self->cap));
    U64 hoisted__U64_13 = 8ULL;
    U8 *new_data = malloc(((U64)(hoisted__U64_12 * hoisted__U64_13)));
    {
        U32 _re_U32_0 = self->cap;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (!(_wcond_Bool_1)) {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U64 hoisted__U64_3 = ((U64)(i));
            U64 hoisted__U64_4 = 8ULL;
            U64 hoisted__U64_5 = ((U64)(hoisted__U64_3 * hoisted__U64_4));
            I64 *src = ((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (hoisted__U64_5)));
            I64 cloned = (DEREF(src));
            U64 hoisted__U64_7 = ((U64)(i));
            U64 hoisted__U64_8 = 8ULL;
            U64 hoisted__U64_9 = ((U64)(hoisted__U64_7 * hoisted__U64_8));
            void *hoisted__v_10 = ((void *)((U8 *)(new_data) + (hoisted__U64_9)));
            adopt__I64(hoisted__v_10, cloned);
        }
    }
    Array__I64 hoisted__Array__I64_14 = {0};
    TIL_OWN_SET((hoisted__Array__I64_14.data), (new_data));
    hoisted__Array__I64_14.cap = self->cap;
    return hoisted__Array__I64_14;
}

static I64 * Map__Str_I64_get(Map__Str_I64 * self, Str * key, I64 * _err_kind) {
    USize lo = 0;
    USize hi = self->keys.count;
    while (1) {
        Bool _wcond_Bool_0 = ((Bool)(lo < hi));
        if (!(_wcond_Bool_0)) {
            break;
        }
        U32 hoisted__U32_7 = ((U32)(hi - lo));
        U32 hoisted__U32_8 = 2;
        U32 hoisted__U32_9 = ({ U32 _cf_a = hoisted__U32_7; U32 _cf_b = hoisted__U32_8; (U32)((_cf_b == 0) ? 0 : (_cf_a / _cf_b)); });
        USize mid = ((U32)(lo + hoisted__U32_9));
        Str *hoisted__Str_Map__Str_I64_get_10 = ((Str *)((void *)((U8 *)(TIL_OWN_GET(U8, (self->keys.data))) + (((U64)(((U64)(mid)) * 12ULL))))));
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
                I64 *hoisted__I64_4 = ((I64 *)((void *)((U8 *)(TIL_OWN_GET(U8, (self->values.data))) + (((U64)(((U64)(mid)) * 8ULL))))));
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
    U32 hoisted__U32_7 = 0;
    self->count = hoisted__U32_7;
}

static void Vec__I64_delete(Vec__I64 * self, Bool call_free) {
    Vec__I64_clear(self);
    free(TIL_OWN_GET(U8, (self->data)));
    if (call_free) {
        free(self);
    }
}

static Vec__I64 Vec__I64_clone(Vec__I64 * self) {
    U32 hoisted__U32_12 = 0;
    Bool hoisted__Bool_13 = ((Bool)(self->cap == hoisted__U32_12));
    if (hoisted__Bool_13) {
        Vec__I64 hoisted__Vec__I64_0 = {0};
        TIL_OWN_SET((hoisted__Vec__I64_0.data), (NULL));
        hoisted__Vec__I64_0.count = 0;
        hoisted__Vec__I64_0.cap = 0;
        return hoisted__Vec__I64_0;
    }
    U64 hoisted__U64_15 = ((U64)(self->cap));
    U64 hoisted__U64_16 = 8ULL;
    U8 *new_data = malloc(((U64)(hoisted__U64_15 * hoisted__U64_16)));
    {
        U32 _re_U32_1 = self->count;
        U32 _rc_U32_1 = 0;
        while (1) {
            Bool _wcond_Bool_2 = ((Bool)(_rc_U32_1 < _re_U32_1));
            if (!(_wcond_Bool_2)) {
                break;
            }
            U32 i = (_rc_U32_1);
            (++_rc_U32_1);
            U64 hoisted__U64_4 = ((U64)(i));
            U64 hoisted__U64_5 = 8ULL;
            U64 hoisted__U64_6 = ((U64)(hoisted__U64_4 * hoisted__U64_5));
            I64 *src = ((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (hoisted__U64_6)));
            I64 cloned = (DEREF(src));
            U64 hoisted__U64_8 = ((U64)(i));
            U64 hoisted__U64_9 = 8ULL;
            U64 hoisted__U64_10 = ((U64)(hoisted__U64_8 * hoisted__U64_9));
            void *hoisted__v_11 = ((void *)((U8 *)(new_data) + (hoisted__U64_10)));
            adopt__I64(hoisted__v_11, cloned);
        }
    }
    Vec__I64 hoisted__Vec__I64_17 = {0};
    TIL_OWN_SET((hoisted__Vec__I64_17.data), (new_data));
    hoisted__Vec__I64_17.count = self->count;
    hoisted__Vec__I64_17.cap = self->cap;
    return hoisted__Vec__I64_17;
}

static void Vec__CfNestedValues_clear(Vec__CfNestedValues * self) {
    {
        U32 _re_U32_0 = self->count;
        U32 _rc_U32_0 = 0;
        while (1) {
            Bool _wcond_Bool_1 = ((Bool)(_rc_U32_0 < _re_U32_0));
            if (!(_wcond_Bool_1)) {
                break;
            }
            U32 i = (_rc_U32_0);
            (++_rc_U32_0);
            U64 hoisted__U64_3 = ((U64)(i));
            U64 hoisted__U64_4 = 12ULL;
            U64 hoisted__U64_5 = ((U64)(hoisted__U64_3 * hoisted__U64_4));
            CfNestedValues *hoisted__CfNestedValues_6 = ((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (hoisted__U64_5)));
            CfNestedValues_delete(hoisted__CfNestedValues_6, 0);
        }
    }
    U32 hoisted__U32_7 = 0;
    self->count = hoisted__U32_7;
}

static void Vec__CfNestedValues_delete(Vec__CfNestedValues * self, Bool call_free) {
    Vec__CfNestedValues_clear(self);
    free(TIL_OWN_GET(U8, (self->data)));
    if (call_free) {
        free(self);
    }
}

static Vec__CfNestedValues Vec__CfNestedValues_clone(Vec__CfNestedValues * self) {
    U32 hoisted__U32_12 = 0;
    Bool hoisted__Bool_13 = ((Bool)(self->cap == hoisted__U32_12));
    if (hoisted__Bool_13) {
        Vec__CfNestedValues hoisted__Vec__CfNestedValues_0 = {0};
        TIL_OWN_SET((hoisted__Vec__CfNestedValues_0.data), (NULL));
        hoisted__Vec__CfNestedValues_0.count = 0;
        hoisted__Vec__CfNestedValues_0.cap = 0;
        return hoisted__Vec__CfNestedValues_0;
    }
    U64 hoisted__U64_15 = ((U64)(self->cap));
    U64 hoisted__U64_16 = 12ULL;
    U8 *new_data = malloc(((U64)(hoisted__U64_15 * hoisted__U64_16)));
    {
        U32 _re_U32_1 = self->count;
        U32 _rc_U32_1 = 0;
        while (1) {
            Bool _wcond_Bool_2 = ((Bool)(_rc_U32_1 < _re_U32_1));
            if (!(_wcond_Bool_2)) {
                break;
            }
            U32 i = (_rc_U32_1);
            (++_rc_U32_1);
            U64 hoisted__U64_4 = ((U64)(i));
            U64 hoisted__U64_5 = 12ULL;
            U64 hoisted__U64_6 = ((U64)(hoisted__U64_4 * hoisted__U64_5));
            CfNestedValues *src = ((void *)((U8 *)(TIL_OWN_GET(U8, (self->data))) + (hoisted__U64_6)));
            CfNestedValues cloned = CfNestedValues_clone(src);
            U64 hoisted__U64_8 = ((U64)(i));
            U64 hoisted__U64_9 = 12ULL;
            U64 hoisted__U64_10 = ((U64)(hoisted__U64_8 * hoisted__U64_9));
            void *hoisted__v_11 = ((void *)((U8 *)(new_data) + (hoisted__U64_10)));
            adopt__CfNestedValues(hoisted__v_11, &cloned);
        }
    }
    Vec__CfNestedValues hoisted__Vec__CfNestedValues_17 = {0};
    TIL_OWN_SET((hoisted__Vec__CfNestedValues_17.data), (new_data));
    hoisted__Vec__CfNestedValues_17.count = self->count;
    hoisted__Vec__CfNestedValues_17.cap = self->cap;
    return hoisted__Vec__CfNestedValues_17;
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
    U64 hoisted__U64_1 = 8ULL;
    memcpy(dest, &src, hoisted__U64_1);
    ((void)src);
}

static void adopt__CfNestedValues(void * dest, CfNestedValues * src) {
    U64 hoisted__U64_1 = 12ULL;
    memcpy(dest, src, hoisted__U64_1);
    ((void)src);
}

int main(void) {
    STATIC_STR = (Str){.c_str = TIL_OWN_LIT("static-folded", 13ULL), .count=13ULL, .cap=TIL_CAP_LIT};
    STATIC_NICHE = NestedToken_Inner(({ WideToken *_oa = malloc(TIL_BOX(WideToken)); *_oa = WideToken_Num(&(I64){9}); _oa; }));
    CF_COMPOSED_VALUES = Vec__I64_clone(_til_precomputed_sequence_22_get());
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
    test_constfold_abort_owned_args();
    fprintf(stderr, "  pass: %s\n", "test_constfold_abort_owned_args");
    test_constfold_abort_branch_locals();
    fprintf(stderr, "  pass: %s\n", "test_constfold_abort_branch_locals");
    test_constfold_abort_after_release();
    fprintf(stderr, "  pass: %s\n", "test_constfold_abort_after_release");
    test_runtime_bindings_shadow_global_constants();
    fprintf(stderr, "  pass: %s\n", "test_runtime_bindings_shadow_global_constants");
    test_block_constants_do_not_escape_their_scope();
    fprintf(stderr, "  pass: %s\n", "test_block_constants_do_not_escape_their_scope");
    test_serialized_binding_keeps_assignment();
    fprintf(stderr, "  pass: %s\n", "test_serialized_binding_keeps_assignment");
    fprintf(stderr, "33/33 tests passed\n");
    return 0;
}
