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
        Array__Str *_fc_Array__Str_79 = parts;
        U32 _fi_USize_79 = 0;
        while (1) {
            USize hoisted__U32_81 = (_fc_Array__Str_79->cap);
            Bool _wcond_Bool_80 = ((Bool)(_fi_USize_79 < hoisted__U32_81));
            if (_wcond_Bool_80) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_79->data) + (((U32)(_fi_USize_79 * 16))))));
            U32 hoisted__U32_82 = 1;
            U32 hoisted__U32_83 = ((U32)(_fi_USize_79 + hoisted__U32_82));
            _fi_USize_79 = hoisted__U32_83;
            USize hoisted__U32_84 = (s->count);
            U32 hoisted__U32_85 = ((U32)(total + hoisted__U32_84));
            total = hoisted__U32_85;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_86 = parts;
        U32 _fi_USize_86 = 0;
        while (1) {
            USize hoisted__U32_88 = (_fc_Array__Str_86->cap);
            Bool _wcond_Bool_87 = ((Bool)(_fi_USize_86 < hoisted__U32_88));
            if (_wcond_Bool_87) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_86->data) + (((U32)(_fi_USize_86 * 16))))));
            U32 hoisted__U32_89 = 1;
            U32 hoisted__U32_90 = ((U32)(_fi_USize_86 + hoisted__U32_89));
            _fi_USize_86 = hoisted__U32_90;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_117 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_117) {
        Bool hoisted__Bool_115 = 0;
        return hoisted__Bool_115;
    }
    Bool hoisted__Bool_118 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_118) {
        Bool hoisted__Bool_116 = 1;
        return hoisted__Bool_116;
    }
    I32 hoisted__I32_119 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_120 = 0;
    Bool hoisted__Bool_121 = ((Bool)(hoisted__I32_119 == hoisted__I32_120));
    return hoisted__Bool_121;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_123 = 0;
    Bool hoisted__Bool_124 = ((Bool)(n == hoisted__U32_123));
    if (hoisted__Bool_124) {
        static Str hoisted__Str_122 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_122; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_125 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_125)));
    I32 hoisted__I32_126 = 0;
    U64 hoisted__U64_127 = 1ULL;
    memset(buf, hoisted__I32_126, hoisted__U64_127);
    I64 hoisted__I64_128 = 0;
    Str *hoisted__Str_129 = malloc(sizeof(Str));
    hoisted__Str_129->c_str = buf;
    hoisted__Str_129->count = hoisted__I64_128;
    hoisted__Str_129->cap = n;
    return hoisted__Str_129;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_140 = 0;
    Bool hoisted__Bool_141 = ((Bool)(s->count == hoisted__U32_140));
    if (hoisted__Bool_141) {
        return;
    }
    Bool hoisted__Bool_142 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_142) {
        U32 hoisted__U32_132 = 1;
        Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_132);
        I64 _va_Array_1_ek = 0;
        U32 hoisted__U32_133 = 0;
        static Str hoisted__Str_134 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_1, hoisted__U32_133, &hoisted__Str_134, &_va_Array_1_ek);
        static Str hoisted__Str_135 = (Str){.c_str = (void *)"./src/core/str.til:124:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_1, &hoisted__Str_135);
        Str_delete(&hoisted__Str_135, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_143 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_143) {
        U32 hoisted__U32_136 = 1;
        Array__Str *_va_Array_2 = Array__Str_new(hoisted__U32_136);
        I64 _va_Array_2_ek = 0;
        U32 hoisted__U32_137 = 0;
        static Str hoisted__Str_138 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_2, hoisted__U32_137, &hoisted__Str_138, &_va_Array_2_ek);
        static Str hoisted__Str_139 = (Str){.c_str = (void *)"./src/core/str.til:128:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_2, &hoisted__Str_139);
        Str_delete(&hoisted__Str_139, (Bool){0});
    }
    void *hoisted__v_144 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_144, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_145 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_146 = 0;
    U64 hoisted__U64_147 = 1ULL;
    memset(hoisted__v_145, hoisted__I32_146, hoisted__U64_147);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_149 = 0;
    Bool hoisted__Bool_150 = ((Bool)(val->count == hoisted__U32_149));
    if (hoisted__Bool_150) {
        static Str hoisted__Str_148 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_148; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_151 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_151)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_152 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_153 = 0;
    U64 hoisted__U64_154 = 1ULL;
    memset(hoisted__v_152, hoisted__I32_153, hoisted__U64_154);
    Str *hoisted__Str_155 = malloc(sizeof(Str));
    hoisted__Str_155->c_str = new_data;
    hoisted__Str_155->count = val->count;
    hoisted__Str_155->cap = val->count;
    return hoisted__Str_155;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_156 = Str_clone(self);
    return hoisted__Str_156;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_157 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_157) {
        free(self->c_str);
    }
    Bool hoisted__Bool_158 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_159 = ((Bool)((call_free) && (hoisted__Bool_158)));
    if (hoisted__Bool_159) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_543 = Str_eq(a, b);
    Bool hoisted__Bool_544 = ((Bool)(!(hoisted__Bool_543)));
    return hoisted__Bool_544;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_681 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_682 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_682->data = hoisted__v_681;
    hoisted__Array__Str_682->cap = cap;
    return hoisted__Array__Str_682;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_691 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Bool hoisted__Bool_692 = 0;
    Str_delete(hoisted__Str_691, hoisted__Bool_692);
    Str *hoisted__Str_693 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    adopt__Str(hoisted__Str_693, val);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_695 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_695) {
        I64 hoisted__I64_694 = 1;
        *_err_kind = hoisted__I64_694;
    }
    I64 hoisted__I64_696 = 0;
    Bool hoisted__Bool_697 = ((Bool)(DEREF(_err_kind) == hoisted__I64_696));
    if (hoisted__Bool_697) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_698 = self->cap;
        U32 _rc_U32_698 = 0;
        Bool hoisted__Bool_709 = ((Bool)(_rc_U32_698 <= _re_U32_698));
        if (hoisted__Bool_709) {
            while (1) {
                Bool _wcond_Bool_699 = ((Bool)(_rc_U32_698 < _re_U32_698));
                if (_wcond_Bool_699) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_698);
                (++_rc_U32_698);
                U32 hoisted__U32_700 = 16;
                U32 hoisted__U32_701 = ((U32)(i * hoisted__U32_700));
                Str *hoisted__Str_702 = ((void *)((U8 *)(self->data) + (hoisted__U32_701)));
                Bool hoisted__Bool_703 = 0;
                Str_delete(hoisted__Str_702, hoisted__Bool_703);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_704 = ((Bool)(_rc_U32_698 > _re_U32_698));
                if (_wcond_Bool_704) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_698);
                (--_rc_U32_698);
                U32 hoisted__U32_705 = 16;
                U32 hoisted__U32_706 = ((U32)(i * hoisted__U32_705));
                Str *hoisted__Str_707 = ((void *)((U8 *)(self->data) + (hoisted__U32_706)));
                Bool hoisted__Bool_708 = 0;
                Str_delete(hoisted__Str_707, hoisted__Bool_708);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_756 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_756)));
    {
        U32 _re_U32_742 = self->cap;
        U32 _rc_U32_742 = 0;
        Bool hoisted__Bool_755 = ((Bool)(_rc_U32_742 <= _re_U32_742));
        if (hoisted__Bool_755) {
            while (1) {
                Bool _wcond_Bool_743 = ((Bool)(_rc_U32_742 < _re_U32_742));
                if (_wcond_Bool_743) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_742);
                (++_rc_U32_742);
                U32 hoisted__U32_744 = 16;
                U32 hoisted__U32_745 = ((U32)(i * hoisted__U32_744));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_745)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_746 = 16;
                U32 hoisted__U32_747 = ((U32)(i * hoisted__U32_746));
                void *hoisted__v_748 = ((void *)((U8 *)(new_data) + (hoisted__U32_747)));
                adopt__Str(hoisted__v_748, cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_749 = ((Bool)(_rc_U32_742 > _re_U32_742));
                if (_wcond_Bool_749) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_742);
                (--_rc_U32_742);
                U32 hoisted__U32_750 = 16;
                U32 hoisted__U32_751 = ((U32)(i * hoisted__U32_750));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_751)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_752 = 16;
                U32 hoisted__U32_753 = ((U32)(i * hoisted__U32_752));
                void *hoisted__v_754 = ((void *)((U8 *)(new_data) + (hoisted__U32_753)));
                adopt__Str(hoisted__v_754, cloned);
            }
        }
    }
    Array__Str *hoisted__Array__Str_757 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_757->data = new_data;
    hoisted__Array__Str_757->cap = self->cap;
    return hoisted__Array__Str_757;
    __builtin_unreachable();
}

void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_1024 = 16;
    memcpy(dest, src, hoisted__U32_1024);
    if ((src)->cap != TIL_CAP_LIT) { free(src); };
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1396 = U64_to_str_ext(val);
    return hoisted__Str_1396;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1757 = 0;
    Bool hoisted__Bool_1758 = ((Bool)(val < hoisted__I64_1757));
    if (hoisted__Bool_1758) {
        U64 hoisted__U64_1749 = 0ULL;
        U64 hoisted__U64_1750 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_1749 - hoisted__U64_1750));
        U32 hoisted__U32_1751 = 2;
        Array__Str *_va_Array_39 = Array__Str_new(hoisted__U32_1751);
        I64 _va_Array_39_ek = 0;
        U32 hoisted__U32_1752 = 0;
        static Str hoisted__Str_1753 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_39, hoisted__U32_1752, &hoisted__Str_1753, &_va_Array_39_ek);
        U32 hoisted__U32_1754 = 1;
        Str *hoisted__Str_1755 = U64_to_str(mag);
        Array__Str_set(_va_Array_39, hoisted__U32_1754, hoisted__Str_1755, &_va_Array_39_ek);
        Str *hoisted__Str_1756 = format(_va_Array_39);
        return hoisted__Str_1756;
    }
    U64 hoisted__U64_1759 = (U64)(val);
    Str *hoisted__Str_1760 = U64_to_str(hoisted__U64_1759);
    return hoisted__Str_1760;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6126 = 3;
    Array__Str *_va_Array_166 = Array__Str_new(hoisted__U32_6126);
    I64 _va_Array_166_ek = 0;
    U32 hoisted__U32_6127 = 0;
    Str *hoisted__Str_6128 = Str_clone(loc);
    Array__Str_set(_va_Array_166, hoisted__U32_6127, hoisted__Str_6128, &_va_Array_166_ek);
    U32 hoisted__U32_6129 = 1;
    Array__Str_set(_va_Array_166, hoisted__U32_6129, &_til_str_lits[0], &_va_Array_166_ek);
    Array__Str *hoisted__Array__Str_6131 = Array__Str_clone(parts);
    U32 hoisted__U32_6132 = 2;
    Str *hoisted__Str_6133 = format(hoisted__Array__Str_6131);
    Array__Str_set(_va_Array_166, hoisted__U32_6132, hoisted__Str_6133, &_va_Array_166_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_166);
    I64 hoisted__I64_6134 = 1;
    exit(hoisted__I64_6134);
}

__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc) {
    USize hoisted__U32_6156 = (parts->cap);
    U32 hoisted__U32_6157 = 0;
    Bool hoisted__Bool_6158 = ((Bool)(hoisted__U32_6156 == hoisted__U32_6157));
    if (hoisted__Bool_6158) {
        U32 hoisted__U32_6147 = 1;
        Array__Str *_va_Array_169 = Array__Str_new(hoisted__U32_6147);
        I64 _va_Array_169_ek = 0;
        U32 hoisted__U32_6148 = 0;
        Array__Str_set(_va_Array_169, hoisted__U32_6148, &_til_str_lits[1], &_va_Array_169_ek);
        panic(_va_Array_169, loc);
    } else {
        U32 hoisted__U32_6150 = 2;
        Array__Str *_va_Array_170 = Array__Str_new(hoisted__U32_6150);
        I64 _va_Array_170_ek = 0;
        U32 hoisted__U32_6151 = 0;
        Array__Str_set(_va_Array_170, hoisted__U32_6151, &_til_str_lits[2], &_va_Array_170_ek);
        Array__Str *hoisted__Array__Str_6153 = Array__Str_clone(parts);
        U32 hoisted__U32_6154 = 1;
        Str *hoisted__Str_6155 = format(hoisted__Array__Str_6153);
        Array__Str_set(_va_Array_170, hoisted__U32_6154, hoisted__Str_6155, &_va_Array_170_ek);
        panic(_va_Array_170, loc);
    }
    Array__Str_delete(parts, 1);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6162 = ((Bool)(!(cond)));
    if (hoisted__Bool_6162) {
        U32 hoisted__U32_6159 = 1;
        Array__Str *_va_Array_171 = Array__Str_new(hoisted__U32_6159);
        I64 _va_Array_171_ek = 0;
        U32 hoisted__U32_6160 = 0;
        Array__Str_set(_va_Array_171, hoisted__U32_6160, &_til_str_lits[3], &_va_Array_171_ek);
        panic(_va_Array_171, loc);
    }
}

void expect(Bool cond, Array__Str * parts, Str * loc) {
    Bool hoisted__Bool_6169 = ((Bool)(!(cond)));
    if (hoisted__Bool_6169) {
        U32 hoisted__U32_6163 = 2;
        Array__Str *_va_Array_172 = Array__Str_new(hoisted__U32_6163);
        I64 _va_Array_172_ek = 0;
        U32 hoisted__U32_6164 = 0;
        Array__Str_set(_va_Array_172, hoisted__U32_6164, &_til_str_lits[4], &_va_Array_172_ek);
        Array__Str *hoisted__Array__Str_6166 = Array__Str_clone(parts);
        U32 hoisted__U32_6167 = 1;
        Str *hoisted__Str_6168 = format(hoisted__Array__Str_6166);
        Array__Str_set(_va_Array_172, hoisted__U32_6167, hoisted__Str_6168, &_va_Array_172_ek);
        panic(_va_Array_172, loc);
    }
    Array__Str_delete(parts, 1);
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6170 = parts;
        U32 _fi_USize_6170 = 0;
        while (1) {
            USize hoisted__U32_6172 = (_fc_Array__Str_6170->cap);
            Bool _wcond_Bool_6171 = ((Bool)(_fi_USize_6170 < hoisted__U32_6172));
            if (_wcond_Bool_6171) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_6170->data) + (((U32)(_fi_USize_6170 * 16))))));
            U32 hoisted__U32_6173 = 1;
            U32 hoisted__U32_6174 = ((U32)(_fi_USize_6170 + hoisted__U32_6173));
            _fi_USize_6170 = hoisted__U32_6174;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6242 = 3;
    assert_eq__I64(result, hoisted__I64_6242, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6250 = 15;
    assert_eq__I64(result, hoisted__I64_6250, &_til_str_lits[6]);
    Str_delete(&_til_str_lits[6], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6258 = 26;
    assert_eq__I64(result, hoisted__I64_6258, &_til_str_lits[7]);
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
    I64 hoisted__I64_6327 = 106;
    assert_eq__I64(d3, hoisted__I64_6327, &_til_str_lits[17]);
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
    I64 hoisted__I64_6820 = 8;
    assert_eq__I64(result, hoisted__I64_6820, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6824 = 1;
    assert(hoisted__Bool_6824, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
    Bool hoisted__Bool_6828 = 1;
    assert(hoisted__Bool_6828, &_til_str_lits[22]);
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
    I64 hoisted__I64_6888 = 42;
    assert_eq__I64(v.x, hoisted__I64_6888, &_til_str_lits[27]);
    Str_delete(&_til_str_lits[27], (Bool){0});
    I64 hoisted__I64_6890 = 99;
    assert_eq__I64(v.y, hoisted__I64_6890, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6894 = 10;
    assert_eq__I64(p.x, hoisted__I64_6894, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    I64 hoisted__I64_6896 = 20;
    assert_eq__I64(p.y, hoisted__I64_6896, &_til_str_lits[30]);
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
    I64 hoisted__I64_6945 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_6945, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    I64 hoisted__I64_6947 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_6947, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_6949 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6949, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_6951 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6951, &_til_str_lits[34]);
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
    Str *hoisted__Str_7007 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_7007, &_til_str_lits[35], &_til_str_lits[36]);
    Str_delete(hoisted__Str_7007, 1);
    Str_delete(&_til_str_lits[35], (Bool){0});
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str *hoisted__Str_7010 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_7010, &_til_str_lits[37], &_til_str_lits[38]);
    Str_delete(hoisted__Str_7010, 1);
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str *hoisted__Str_7013 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_7013, &_til_str_lits[39], &_til_str_lits[40]);
    Str_delete(hoisted__Str_7013, 1);
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str_delete(&_til_str_lits[40], (Bool){0});
    CfVec3f_delete(&v, (Bool){0});
}

Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_7016 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_7016;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7063 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_7063, &_til_str_lits[41]);
    Str_delete(&_til_str_lits[41], (Bool){0});
    Bool hoisted__Bool_7065 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_7066 = ((Bool)(!(hoisted__Bool_7065)));
    assert(hoisted__Bool_7066, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7085 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_7085) {
        I64 *hoisted__I64_7081 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7082 = 0;
        I64_delete(hoisted__I64_7081, hoisted__Bool_7082);
    }
    Bool hoisted__Bool_7086 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_7086) {
        Str *hoisted__Str_7083 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7084 = 0;
        Str_delete(hoisted__Str_7083, hoisted__Bool_7084);
    }
    if (call_free) {
        free(self);
    }
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7148 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7148, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
    Bool hoisted__Bool_7150 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7151 = ((Bool)(!(hoisted__Bool_7150)));
    assert(hoisted__Bool_7151, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7153 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_7153, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Bool hoisted__Bool_7155 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_7156 = ((Bool)(!(hoisted__Bool_7155)));
    assert(hoisted__Bool_7156, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7160 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7160, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
    Bool hoisted__Bool_7162 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7163 = ((Bool)(!(hoisted__Bool_7162)));
    assert(hoisted__Bool_7163, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Token_delete(t, 1);
}

void test_const_and_or_fold(void) {
    U32 hoisted__U32_7171 = 1;
    Array__Str *_va_Array_209 = Array__Str_new(hoisted__U32_7171);
    I64 _va_Array_209_ek = 0;
    U32 hoisted__U32_7172 = 0;
    Array__Str_set(_va_Array_209, hoisted__U32_7172, &_til_str_lits[49], &_va_Array_209_ek);
    Bool hoisted__Bool_7174 = 1;
    expect(hoisted__Bool_7174, _va_Array_209, &_til_str_lits[50]);
    Str_delete(&_til_str_lits[50], (Bool){0});
    U32 hoisted__U32_7176 = 1;
    Array__Str *_va_Array_210 = Array__Str_new(hoisted__U32_7176);
    I64 _va_Array_210_ek = 0;
    U32 hoisted__U32_7177 = 0;
    Array__Str_set(_va_Array_210, hoisted__U32_7177, &_til_str_lits[51], &_va_Array_210_ek);
    Bool hoisted__Bool_7180 = 1;
    expect(hoisted__Bool_7180, _va_Array_210, &_til_str_lits[52]);
    Str_delete(&_til_str_lits[52], (Bool){0});
    U32 hoisted__U32_7182 = 1;
    Array__Str *_va_Array_211 = Array__Str_new(hoisted__U32_7182);
    I64 _va_Array_211_ek = 0;
    U32 hoisted__U32_7183 = 0;
    Array__Str_set(_va_Array_211, hoisted__U32_7183, &_til_str_lits[53], &_va_Array_211_ek);
    Bool hoisted__Bool_7185 = 1;
    expect(hoisted__Bool_7185, _va_Array_211, &_til_str_lits[54]);
    Str_delete(&_til_str_lits[54], (Bool){0});
    U32 hoisted__U32_7187 = 1;
    Array__Str *_va_Array_212 = Array__Str_new(hoisted__U32_7187);
    I64 _va_Array_212_ek = 0;
    U32 hoisted__U32_7188 = 0;
    Array__Str_set(_va_Array_212, hoisted__U32_7188, &_til_str_lits[55], &_va_Array_212_ek);
    Bool hoisted__Bool_7191 = 1;
    expect(hoisted__Bool_7191, _va_Array_212, &_til_str_lits[56]);
    Str_delete(&_til_str_lits[56], (Bool){0});
    U32 hoisted__U32_7193 = 1;
    Array__Str *_va_Array_213 = Array__Str_new(hoisted__U32_7193);
    I64 _va_Array_213_ek = 0;
    U32 hoisted__U32_7194 = 0;
    Array__Str_set(_va_Array_213, hoisted__U32_7194, &_til_str_lits[57], &_va_Array_213_ek);
    Bool hoisted__Bool_7196 = 1;
    expect(hoisted__Bool_7196, _va_Array_213, &_til_str_lits[58]);
    Str_delete(&_til_str_lits[58], (Bool){0});
    U32 hoisted__U32_7198 = 1;
    Array__Str *_va_Array_214 = Array__Str_new(hoisted__U32_7198);
    I64 _va_Array_214_ek = 0;
    U32 hoisted__U32_7199 = 0;
    Array__Str_set(_va_Array_214, hoisted__U32_7199, &_til_str_lits[59], &_va_Array_214_ek);
    Bool hoisted__Bool_7202 = 1;
    expect(hoisted__Bool_7202, _va_Array_214, &_til_str_lits[60]);
    Str_delete(&_til_str_lits[60], (Bool){0});
    U32 hoisted__U32_7204 = 1;
    Array__Str *_va_Array_215 = Array__Str_new(hoisted__U32_7204);
    I64 _va_Array_215_ek = 0;
    U32 hoisted__U32_7205 = 0;
    Array__Str_set(_va_Array_215, hoisted__U32_7205, &_til_str_lits[61], &_va_Array_215_ek);
    Bool hoisted__Bool_7207 = 1;
    expect(hoisted__Bool_7207, _va_Array_215, &_til_str_lits[62]);
    Str_delete(&_til_str_lits[62], (Bool){0});
    U32 hoisted__U32_7209 = 1;
    Array__Str *_va_Array_216 = Array__Str_new(hoisted__U32_7209);
    I64 _va_Array_216_ek = 0;
    U32 hoisted__U32_7210 = 0;
    Array__Str_set(_va_Array_216, hoisted__U32_7210, &_til_str_lits[63], &_va_Array_216_ek);
    Bool hoisted__Bool_7213 = 1;
    expect(hoisted__Bool_7213, _va_Array_216, &_til_str_lits[64]);
    Str_delete(&_til_str_lits[64], (Bool){0});
    U32 hoisted__U32_7215 = 1;
    Array__Str *_va_Array_217 = Array__Str_new(hoisted__U32_7215);
    I64 _va_Array_217_ek = 0;
    U32 hoisted__U32_7216 = 0;
    Array__Str_set(_va_Array_217, hoisted__U32_7216, &_til_str_lits[65], &_va_Array_217_ek);
    Bool hoisted__Bool_7218 = 1;
    expect(hoisted__Bool_7218, _va_Array_217, &_til_str_lits[66]);
    Str_delete(&_til_str_lits[66], (Bool){0});
    Bool _m_Bool_7165 = 0;
    {
        Bool hoisted__Bool_7170 = 0;
        if (hoisted__Bool_7170) {
            Bool hoisted__Bool_7167 = 1;
            _m_Bool_7165 = hoisted__Bool_7167;
        } else {
            Bool hoisted__Bool_7168 = 1;
            _m_Bool_7165 = hoisted__Bool_7168;
        }
    }
    U32 hoisted__U32_7220 = 1;
    Array__Str *_va_Array_218 = Array__Str_new(hoisted__U32_7220);
    I64 _va_Array_218_ek = 0;
    U32 hoisted__U32_7221 = 0;
    Array__Str_set(_va_Array_218, hoisted__U32_7221, &_til_str_lits[67], &_va_Array_218_ek);
    expect(_m_Bool_7165, _va_Array_218, &_til_str_lits[68]);
    Str_delete(&_til_str_lits[68], (Bool){0});
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7313 = ((Bool)(a != b));
    if (hoisted__Bool_7313) {
        U32 hoisted__U32_7302 = 5;
        Array__Str *_va_Array_219 = Array__Str_new(hoisted__U32_7302);
        I64 _va_Array_219_ek = 0;
        U32 hoisted__U32_7303 = 0;
        Array__Str_set(_va_Array_219, hoisted__U32_7303, &_til_str_lits[69], &_va_Array_219_ek);
        U32 hoisted__U32_7305 = 1;
        Str *hoisted__Str_7306 = I64_to_str(a);
        Array__Str_set(_va_Array_219, hoisted__U32_7305, hoisted__Str_7306, &_va_Array_219_ek);
        U32 hoisted__U32_7307 = 2;
        Array__Str_set(_va_Array_219, hoisted__U32_7307, &_til_str_lits[70], &_va_Array_219_ek);
        U32 hoisted__U32_7309 = 3;
        Str *hoisted__Str_7310 = I64_to_str(b);
        Array__Str_set(_va_Array_219, hoisted__U32_7309, hoisted__Str_7310, &_va_Array_219_ek);
        U32 hoisted__U32_7311 = 4;
        Array__Str_set(_va_Array_219, hoisted__U32_7311, &_til_str_lits[71], &_va_Array_219_ek);
        panic(_va_Array_219, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7325 = Str_neq(a, b);
    if (hoisted__Bool_7325) {
        U32 hoisted__U32_7314 = 5;
        Array__Str *_va_Array_220 = Array__Str_new(hoisted__U32_7314);
        I64 _va_Array_220_ek = 0;
        U32 hoisted__U32_7315 = 0;
        Array__Str_set(_va_Array_220, hoisted__U32_7315, &_til_str_lits[69], &_va_Array_220_ek);
        U32 hoisted__U32_7317 = 1;
        Str *hoisted__Str_7318 = Str_to_str(a);
        Array__Str_set(_va_Array_220, hoisted__U32_7317, hoisted__Str_7318, &_va_Array_220_ek);
        U32 hoisted__U32_7319 = 2;
        Array__Str_set(_va_Array_220, hoisted__U32_7319, &_til_str_lits[70], &_va_Array_220_ek);
        U32 hoisted__U32_7321 = 3;
        Str *hoisted__Str_7322 = Str_to_str(b);
        Array__Str_set(_va_Array_220, hoisted__U32_7321, hoisted__Str_7322, &_va_Array_220_ek);
        U32 hoisted__U32_7323 = 4;
        Array__Str_set(_va_Array_220, hoisted__U32_7323, &_til_str_lits[71], &_va_Array_220_ek);
        panic(_va_Array_220, loc);
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
