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
typedef struct Range Range;
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
Str * U64_to_str(U64 val);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc);
void assert(Bool cond, Str * loc);
void expect(Bool cond, Array__Str * parts, Str * loc);
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
void test_enum_fold(void);
void Token_delete(Token * self, Bool call_free);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
void test_const_and_or_fold(void);
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
Str * U64_to_str(U64 val);
Str * I64_to_str(I64 val);
void I64_delete(I64 * self, Bool call_free);
__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc);
__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc);
void assert(Bool cond, Str * loc);
void expect(Bool cond, Array__Str * parts, Str * loc);
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
void test_enum_fold(void);
Token * Token_Num(I64 * val);
void Token_delete(Token * self, Bool call_free);
void test_enum_payload_fold(void);
void test_enum_return_fold(void);
void test_enum_payload_return_fold(void);
void test_const_and_or_fold(void);
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

static Str _til_str_lits[72] = {
    (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"unreachable", .count = 11ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"unreachable: ", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"assert failed: ", .count = 15ULL, .cap = TIL_CAP_LIT},
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
    (Str){.c_str = (void *)"and(T,T)", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:281:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"and(T,F)", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:282:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"and x3 T", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:283:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"and x3 with F", .count = 13ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:284:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"or(F,T)", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:285:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"or(F,F)", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:286:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"or x3 with T", .count = 12ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:287:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"or x3 F", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:288:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"T.and(T)", .count = 8ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:289:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"F.or(T)", .count = 7ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"test/constfold.til:290:5", .count = 24ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT},
    (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT},
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
    Bool hoisted__Bool_511 = Str_eq(a, b);
    Bool hoisted__Bool_512 = ((Bool)(!(hoisted__Bool_511)));
    return hoisted__Bool_512;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_649 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_650 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_650->data = hoisted__v_649;
    hoisted__Array__Str_650->cap = cap;
    return hoisted__Array__Str_650;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_659 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Bool hoisted__Bool_660 = 0;
    Str_delete(hoisted__Str_659, hoisted__Bool_660);
    Str *hoisted__Str_661 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    adopt__Str(hoisted__Str_661, val);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_663 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_663) {
        I64 hoisted__I64_662 = 1;
        *_err_kind = hoisted__I64_662;
    }
    I64 hoisted__I64_664 = 0;
    Bool hoisted__Bool_665 = ((Bool)(DEREF(_err_kind) == hoisted__I64_664));
    if (hoisted__Bool_665) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_666 = self->cap;
        U32 _rc_U32_666 = 0;
        Bool hoisted__Bool_677 = ((Bool)(_rc_U32_666 <= _re_U32_666));
        if (hoisted__Bool_677) {
            while (1) {
                Bool _wcond_Bool_667 = ((Bool)(_rc_U32_666 < _re_U32_666));
                if (_wcond_Bool_667) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_666);
                (++_rc_U32_666);
                U32 hoisted__U32_668 = 16;
                U32 hoisted__U32_669 = ((U32)(i * hoisted__U32_668));
                Str *hoisted__Str_670 = ((void *)((U8 *)(self->data) + (hoisted__U32_669)));
                Bool hoisted__Bool_671 = 0;
                Str_delete(hoisted__Str_670, hoisted__Bool_671);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_672 = ((Bool)(_rc_U32_666 > _re_U32_666));
                if (_wcond_Bool_672) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_666);
                (--_rc_U32_666);
                U32 hoisted__U32_673 = 16;
                U32 hoisted__U32_674 = ((U32)(i * hoisted__U32_673));
                Str *hoisted__Str_675 = ((void *)((U8 *)(self->data) + (hoisted__U32_674)));
                Bool hoisted__Bool_676 = 0;
                Str_delete(hoisted__Str_675, hoisted__Bool_676);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_692 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_692)));
    {
        U32 _re_U32_678 = self->cap;
        U32 _rc_U32_678 = 0;
        Bool hoisted__Bool_691 = ((Bool)(_rc_U32_678 <= _re_U32_678));
        if (hoisted__Bool_691) {
            while (1) {
                Bool _wcond_Bool_679 = ((Bool)(_rc_U32_678 < _re_U32_678));
                if (_wcond_Bool_679) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_678);
                (++_rc_U32_678);
                U32 hoisted__U32_680 = 16;
                U32 hoisted__U32_681 = ((U32)(i * hoisted__U32_680));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_681)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_682 = 16;
                U32 hoisted__U32_683 = ((U32)(i * hoisted__U32_682));
                void *hoisted__v_684 = ((void *)((U8 *)(new_data) + (hoisted__U32_683)));
                adopt__Str(hoisted__v_684, cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_685 = ((Bool)(_rc_U32_678 > _re_U32_678));
                if (_wcond_Bool_685) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_678);
                (--_rc_U32_678);
                U32 hoisted__U32_686 = 16;
                U32 hoisted__U32_687 = ((U32)(i * hoisted__U32_686));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_687)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_688 = 16;
                U32 hoisted__U32_689 = ((U32)(i * hoisted__U32_688));
                void *hoisted__v_690 = ((void *)((U8 *)(new_data) + (hoisted__U32_689)));
                adopt__Str(hoisted__v_690, cloned);
            }
        }
    }
    Array__Str *hoisted__Array__Str_693 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_693->data = new_data;
    hoisted__Array__Str_693->cap = self->cap;
    return hoisted__Array__Str_693;
    __builtin_unreachable();
}

void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_972 = 16;
    memcpy(dest, src, hoisted__U32_972);
    if ((src)->cap != TIL_CAP_LIT) { free(src); };
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1296 = U64_to_str_ext(val);
    return hoisted__Str_1296;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1657 = 0;
    Bool hoisted__Bool_1658 = ((Bool)(val < hoisted__I64_1657));
    if (hoisted__Bool_1658) {
        U64 hoisted__U64_1649 = 0ULL;
        U64 hoisted__U64_1650 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_1649 - hoisted__U64_1650));
        U32 hoisted__U32_1651 = 2;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1651);
        I64 _va_Array_39_ek = 0;
        U32 hoisted__U32_1652 = 0;
        static Str hoisted__Str_1653 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_39, hoisted__U32_1652, &hoisted__Str_1653, &_va_Array_39_ek);
        U32 hoisted__U32_1654 = 1;
        Str *hoisted__Str_1655 = U64_to_str(mag);
        Array__Str_set(_va_Array_39, hoisted__U32_1654, hoisted__Str_1655, &_va_Array_39_ek);
        Str *hoisted__Str_1656 = format(_va_Array_39);
        return hoisted__Str_1656;
    }
    U64 hoisted__U64_1659 = (U64)(val);
    Str *hoisted__Str_1660 = U64_to_str(hoisted__U64_1659);
    return hoisted__Str_1660;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6086 = 3;
    Array__Str *_va_Array_166 = Array__Str_new(hoisted__U32_6086);
    I64 _va_Array_166_ek = 0;
    U32 hoisted__U32_6087 = 0;
    Str *hoisted__Str_6088 = Str_clone(loc);
    Array__Str_set(_va_Array_166, hoisted__U32_6087, hoisted__Str_6088, &_va_Array_166_ek);
    U32 hoisted__U32_6089 = 1;
    Array__Str_set(_va_Array_166, hoisted__U32_6089, &_til_str_lits[0], &_va_Array_166_ek);
    Array__Str *hoisted__Array__Str_6091 = Array__Str_clone(parts);
    U32 hoisted__U32_6092 = 2;
    Str *hoisted__Str_6093 = format(hoisted__Array__Str_6091);
    Array__Str_set(_va_Array_166, hoisted__U32_6092, hoisted__Str_6093, &_va_Array_166_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_166);
    I64 hoisted__I64_6094 = 1;
    exit(hoisted__I64_6094);
}

__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc) {
    USize hoisted__U32_6110 = (parts->cap);
    U32 hoisted__U32_6111 = 0;
    Bool hoisted__Bool_6112 = ((Bool)(hoisted__U32_6110 == hoisted__U32_6111));
    if (hoisted__Bool_6112) {
        U32 hoisted__U32_6101 = 1;
        Array__Str *_va_Array_168 = Array__Str_new(hoisted__U32_6101);
        I64 _va_Array_168_ek = 0;
        U32 hoisted__U32_6102 = 0;
        Array__Str_set(_va_Array_168, hoisted__U32_6102, &_til_str_lits[1], &_va_Array_168_ek);
        panic(_va_Array_168, loc);
    } else {
        U32 hoisted__U32_6104 = 2;
        Array__Str *_va_Array_169 = Array__Str_new(hoisted__U32_6104);
        I64 _va_Array_169_ek = 0;
        U32 hoisted__U32_6105 = 0;
        Array__Str_set(_va_Array_169, hoisted__U32_6105, &_til_str_lits[2], &_va_Array_169_ek);
        Array__Str *hoisted__Array__Str_6107 = Array__Str_clone(parts);
        U32 hoisted__U32_6108 = 1;
        Str *hoisted__Str_6109 = format(hoisted__Array__Str_6107);
        Array__Str_set(_va_Array_169, hoisted__U32_6108, hoisted__Str_6109, &_va_Array_169_ek);
        panic(_va_Array_169, loc);
    }
    Array__Str_delete(parts, 1);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6116 = ((Bool)(!(cond)));
    if (hoisted__Bool_6116) {
        U32 hoisted__U32_6113 = 1;
        Array__Str *_va_Array_170 = Array__Str_new(hoisted__U32_6113);
        I64 _va_Array_170_ek = 0;
        U32 hoisted__U32_6114 = 0;
        Array__Str_set(_va_Array_170, hoisted__U32_6114, &_til_str_lits[3], &_va_Array_170_ek);
        panic(_va_Array_170, loc);
    }
}

void expect(Bool cond, Array__Str * parts, Str * loc) {
    Bool hoisted__Bool_6123 = ((Bool)(!(cond)));
    if (hoisted__Bool_6123) {
        U32 hoisted__U32_6117 = 2;
        Array__Str *_va_Array_171 = Array__Str_new(hoisted__U32_6117);
        I64 _va_Array_171_ek = 0;
        U32 hoisted__U32_6118 = 0;
        Array__Str_set(_va_Array_171, hoisted__U32_6118, &_til_str_lits[4], &_va_Array_171_ek);
        Array__Str *hoisted__Array__Str_6120 = Array__Str_clone(parts);
        U32 hoisted__U32_6121 = 1;
        Str *hoisted__Str_6122 = format(hoisted__Array__Str_6120);
        Array__Str_set(_va_Array_171, hoisted__U32_6121, hoisted__Str_6122, &_va_Array_171_ek);
        panic(_va_Array_171, loc);
    }
    Array__Str_delete(parts, 1);
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6124 = parts;
        U32 _fi_USize_6124 = 0;
        while (1) {
            USize hoisted__U32_6126 = (_fc_Array__Str_6124->cap);
            Bool _wcond_Bool_6125 = ((Bool)(_fi_USize_6124 < hoisted__U32_6126));
            if (_wcond_Bool_6125) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_6124->data) + (((U32)(_fi_USize_6124 * 16))))));
            U32 hoisted__U32_6127 = 1;
            U32 hoisted__U32_6128 = ((U32)(_fi_USize_6124 + hoisted__U32_6127));
            _fi_USize_6124 = hoisted__U32_6128;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6196 = 3;
    assert_eq__I64(result, hoisted__I64_6196, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6204 = 15;
    assert_eq__I64(result, hoisted__I64_6204, &_til_str_lits[6]);
    Str_delete(&_til_str_lits[6], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6212 = 26;
    assert_eq__I64(result, hoisted__I64_6212, &_til_str_lits[7]);
    Str_delete(&_til_str_lits[7], (Bool){0});
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&result, &_til_str_lits[8], &_til_str_lits[9]);
    Str_delete(&_til_str_lits[8], (Bool){0});
    Str_delete(&_til_str_lits[9], (Bool){0});
    Str_delete(&result, (Bool){0});
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r, &_til_str_lits[8], &_til_str_lits[10]);
    Str_delete(&_til_str_lits[8], (Bool){0});
    Str_delete(&_til_str_lits[10], (Bool){0});
    Str_delete(&r, (Bool){0});
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r2, &_til_str_lits[11], &_til_str_lits[12]);
    Str_delete(&_til_str_lits[11], (Bool){0});
    Str_delete(&_til_str_lits[12], (Bool){0});
    Str_delete(&r2, (Bool){0});
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d, &_til_str_lits[13], &_til_str_lits[14]);
    Str_delete(&d, (Bool){0});
    Str_delete(&_til_str_lits[13], (Bool){0});
    Str_delete(&_til_str_lits[14], (Bool){0});
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d2, &_til_str_lits[15], &_til_str_lits[16]);
    Str_delete(&d2, (Bool){0});
    Str_delete(&_til_str_lits[15], (Bool){0});
    Str_delete(&_til_str_lits[16], (Bool){0});
    I64 d3 = 106;
    I64 hoisted__I64_6281 = 106;
    assert_eq__I64(d3, hoisted__I64_6281, &_til_str_lits[17]);
    Str_delete(&_til_str_lits[17], (Bool){0});
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
    I64 hoisted__I64_6774 = 8;
    assert_eq__I64(result, hoisted__I64_6774, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6778 = 1;
    assert(hoisted__Bool_6778, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
    Bool hoisted__Bool_6782 = 1;
    assert(hoisted__Bool_6782, &_til_str_lits[22]);
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

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_6842 = 42;
    assert_eq__I64(v.x, hoisted__I64_6842, &_til_str_lits[27]);
    Str_delete(&_til_str_lits[27], (Bool){0});
    I64 hoisted__I64_6844 = 99;
    assert_eq__I64(v.y, hoisted__I64_6844, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6848 = 10;
    assert_eq__I64(p.x, hoisted__I64_6848, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    I64 hoisted__I64_6850 = 20;
    assert_eq__I64(p.y, hoisted__I64_6850, &_til_str_lits[30]);
    Str_delete(&_til_str_lits[30], (Bool){0});
    CfVec2_delete(&p, (Bool){0});
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_6899 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_6899, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    I64 hoisted__I64_6901 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_6901, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_6903 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6903, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_6905 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6905, &_til_str_lits[34]);
    Str_delete(&_til_str_lits[34], (Bool){0});
    CfRect_delete(&r, (Bool){0});
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_6961 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_6961, &_til_str_lits[35], &_til_str_lits[36]);
    Str_delete(hoisted__Str_6961, 1);
    Str_delete(&_til_str_lits[35], (Bool){0});
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str *hoisted__Str_6964 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_6964, &_til_str_lits[37], &_til_str_lits[38]);
    Str_delete(hoisted__Str_6964, 1);
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str *hoisted__Str_6967 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_6967, &_til_str_lits[39], &_til_str_lits[40]);
    Str_delete(hoisted__Str_6967, 1);
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str_delete(&_til_str_lits[40], (Bool){0});
    CfVec3f_delete(&v, (Bool){0});
}

Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_6970 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_6970;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7017 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_7017, &_til_str_lits[41]);
    Str_delete(&_til_str_lits[41], (Bool){0});
    Bool hoisted__Bool_7019 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_7020 = ((Bool)(!(hoisted__Bool_7019)));
    assert(hoisted__Bool_7020, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7039 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_7039) {
        I64 *hoisted__I64_7035 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7036 = 0;
        I64_delete(hoisted__I64_7035, hoisted__Bool_7036);
    }
    Bool hoisted__Bool_7040 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_7040) {
        Str *hoisted__Str_7037 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7038 = 0;
        Str_delete(hoisted__Str_7037, hoisted__Bool_7038);
    }
    if (call_free) {
        free(self);
    }
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7102 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7102, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
    Bool hoisted__Bool_7104 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7105 = ((Bool)(!(hoisted__Bool_7104)));
    assert(hoisted__Bool_7105, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7107 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_7107, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Bool hoisted__Bool_7109 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_7110 = ((Bool)(!(hoisted__Bool_7109)));
    assert(hoisted__Bool_7110, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7114 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7114, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
    Bool hoisted__Bool_7116 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7117 = ((Bool)(!(hoisted__Bool_7116)));
    assert(hoisted__Bool_7117, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Token_delete(t, 1);
}

void test_const_and_or_fold(void) {
    U32 hoisted__U32_7125 = 1;
    Array__Str *_va_Array_208 = Array__Str_new(hoisted__U32_7125);
    I64 _va_Array_208_ek = 0;
    U32 hoisted__U32_7126 = 0;
    Array__Str_set(_va_Array_208, hoisted__U32_7126, &_til_str_lits[49], &_va_Array_208_ek);
    Bool hoisted__Bool_7128 = 1;
    expect(hoisted__Bool_7128, _va_Array_208, &_til_str_lits[50]);
    Str_delete(&_til_str_lits[50], (Bool){0});
    U32 hoisted__U32_7130 = 1;
    Array__Str *_va_Array_209 = Array__Str_new(hoisted__U32_7130);
    I64 _va_Array_209_ek = 0;
    U32 hoisted__U32_7131 = 0;
    Array__Str_set(_va_Array_209, hoisted__U32_7131, &_til_str_lits[51], &_va_Array_209_ek);
    Bool hoisted__Bool_7134 = 1;
    expect(hoisted__Bool_7134, _va_Array_209, &_til_str_lits[52]);
    Str_delete(&_til_str_lits[52], (Bool){0});
    U32 hoisted__U32_7136 = 1;
    Array__Str *_va_Array_210 = Array__Str_new(hoisted__U32_7136);
    I64 _va_Array_210_ek = 0;
    U32 hoisted__U32_7137 = 0;
    Array__Str_set(_va_Array_210, hoisted__U32_7137, &_til_str_lits[53], &_va_Array_210_ek);
    Bool hoisted__Bool_7139 = 1;
    expect(hoisted__Bool_7139, _va_Array_210, &_til_str_lits[54]);
    Str_delete(&_til_str_lits[54], (Bool){0});
    U32 hoisted__U32_7141 = 1;
    Array__Str *_va_Array_211 = Array__Str_new(hoisted__U32_7141);
    I64 _va_Array_211_ek = 0;
    U32 hoisted__U32_7142 = 0;
    Array__Str_set(_va_Array_211, hoisted__U32_7142, &_til_str_lits[55], &_va_Array_211_ek);
    Bool hoisted__Bool_7145 = 1;
    expect(hoisted__Bool_7145, _va_Array_211, &_til_str_lits[56]);
    Str_delete(&_til_str_lits[56], (Bool){0});
    U32 hoisted__U32_7147 = 1;
    Array__Str *_va_Array_212 = Array__Str_new(hoisted__U32_7147);
    I64 _va_Array_212_ek = 0;
    U32 hoisted__U32_7148 = 0;
    Array__Str_set(_va_Array_212, hoisted__U32_7148, &_til_str_lits[57], &_va_Array_212_ek);
    Bool hoisted__Bool_7150 = 1;
    expect(hoisted__Bool_7150, _va_Array_212, &_til_str_lits[58]);
    Str_delete(&_til_str_lits[58], (Bool){0});
    U32 hoisted__U32_7152 = 1;
    Array__Str *_va_Array_213 = Array__Str_new(hoisted__U32_7152);
    I64 _va_Array_213_ek = 0;
    U32 hoisted__U32_7153 = 0;
    Array__Str_set(_va_Array_213, hoisted__U32_7153, &_til_str_lits[59], &_va_Array_213_ek);
    Bool hoisted__Bool_7156 = 1;
    expect(hoisted__Bool_7156, _va_Array_213, &_til_str_lits[60]);
    Str_delete(&_til_str_lits[60], (Bool){0});
    U32 hoisted__U32_7158 = 1;
    Array__Str *_va_Array_214 = Array__Str_new(hoisted__U32_7158);
    I64 _va_Array_214_ek = 0;
    U32 hoisted__U32_7159 = 0;
    Array__Str_set(_va_Array_214, hoisted__U32_7159, &_til_str_lits[61], &_va_Array_214_ek);
    Bool hoisted__Bool_7161 = 1;
    expect(hoisted__Bool_7161, _va_Array_214, &_til_str_lits[62]);
    Str_delete(&_til_str_lits[62], (Bool){0});
    U32 hoisted__U32_7163 = 1;
    Array__Str *_va_Array_215 = Array__Str_new(hoisted__U32_7163);
    I64 _va_Array_215_ek = 0;
    U32 hoisted__U32_7164 = 0;
    Array__Str_set(_va_Array_215, hoisted__U32_7164, &_til_str_lits[63], &_va_Array_215_ek);
    Bool hoisted__Bool_7167 = 1;
    expect(hoisted__Bool_7167, _va_Array_215, &_til_str_lits[64]);
    Str_delete(&_til_str_lits[64], (Bool){0});
    U32 hoisted__U32_7169 = 1;
    Array__Str *_va_Array_216 = Array__Str_new(hoisted__U32_7169);
    I64 _va_Array_216_ek = 0;
    U32 hoisted__U32_7170 = 0;
    Array__Str_set(_va_Array_216, hoisted__U32_7170, &_til_str_lits[65], &_va_Array_216_ek);
    Bool hoisted__Bool_7172 = 1;
    expect(hoisted__Bool_7172, _va_Array_216, &_til_str_lits[66]);
    Str_delete(&_til_str_lits[66], (Bool){0});
    Bool _m_Bool_7119 = 0;
    {
        Bool hoisted__Bool_7124 = 0;
        if (hoisted__Bool_7124) {
            Bool hoisted__Bool_7121 = 1;
            _m_Bool_7119 = hoisted__Bool_7121;
        } else {
            Bool hoisted__Bool_7122 = 1;
            _m_Bool_7119 = hoisted__Bool_7122;
        }
    }
    U32 hoisted__U32_7174 = 1;
    Array__Str *_va_Array_217 = Array__Str_new(hoisted__U32_7174);
    I64 _va_Array_217_ek = 0;
    U32 hoisted__U32_7175 = 0;
    Array__Str_set(_va_Array_217, hoisted__U32_7175, &_til_str_lits[67], &_va_Array_217_ek);
    expect(_m_Bool_7119, _va_Array_217, &_til_str_lits[68]);
    Str_delete(&_til_str_lits[68], (Bool){0});
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7235 = ((Bool)(a != b));
    if (hoisted__Bool_7235) {
        U32 hoisted__U32_7224 = 5;
        Array__Str *_va_Array_218 = Array__Str_new(hoisted__U32_7224);
        I64 _va_Array_218_ek = 0;
        U32 hoisted__U32_7225 = 0;
        Array__Str_set(_va_Array_218, hoisted__U32_7225, &_til_str_lits[69], &_va_Array_218_ek);
        U32 hoisted__U32_7227 = 1;
        Str *hoisted__Str_7228 = I64_to_str(a);
        Array__Str_set(_va_Array_218, hoisted__U32_7227, hoisted__Str_7228, &_va_Array_218_ek);
        U32 hoisted__U32_7229 = 2;
        Array__Str_set(_va_Array_218, hoisted__U32_7229, &_til_str_lits[70], &_va_Array_218_ek);
        U32 hoisted__U32_7231 = 3;
        Str *hoisted__Str_7232 = I64_to_str(b);
        Array__Str_set(_va_Array_218, hoisted__U32_7231, hoisted__Str_7232, &_va_Array_218_ek);
        U32 hoisted__U32_7233 = 4;
        Array__Str_set(_va_Array_218, hoisted__U32_7233, &_til_str_lits[71], &_va_Array_218_ek);
        panic(_va_Array_218, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7247 = Str_neq(a, b);
    if (hoisted__Bool_7247) {
        U32 hoisted__U32_7236 = 5;
        Array__Str *_va_Array_219 = Array__Str_new(hoisted__U32_7236);
        I64 _va_Array_219_ek = 0;
        U32 hoisted__U32_7237 = 0;
        Array__Str_set(_va_Array_219, hoisted__U32_7237, &_til_str_lits[69], &_va_Array_219_ek);
        U32 hoisted__U32_7239 = 1;
        Str *hoisted__Str_7240 = Str_to_str(a);
        Array__Str_set(_va_Array_219, hoisted__U32_7239, hoisted__Str_7240, &_va_Array_219_ek);
        U32 hoisted__U32_7241 = 2;
        Array__Str_set(_va_Array_219, hoisted__U32_7241, &_til_str_lits[70], &_va_Array_219_ek);
        U32 hoisted__U32_7243 = 3;
        Str *hoisted__Str_7244 = Str_to_str(b);
        Array__Str_set(_va_Array_219, hoisted__U32_7243, hoisted__Str_7244, &_va_Array_219_ek);
        U32 hoisted__U32_7245 = 4;
        Array__Str_set(_va_Array_219, hoisted__U32_7245, &_til_str_lits[71], &_va_Array_219_ek);
        panic(_va_Array_219, loc);
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
    test_const_and_or_fold();
    fprintf(stderr, "  pass: %s\n", "test_const_and_or_fold");
    fprintf(stderr, "19/19 tests passed\n");
    return 0;
}
