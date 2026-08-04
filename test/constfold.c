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
        Array__Str *_fc_Array__Str_85 = parts;
        U32 _fi_USize_85 = 0;
        while (1) {
            USize hoisted__U32_87 = (_fc_Array__Str_85->cap);
            Bool _wcond_Bool_86 = ((Bool)(_fi_USize_85 < hoisted__U32_87));
            if (_wcond_Bool_86) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_85->data) + (((U32)(_fi_USize_85 * 16))))));
            U32 hoisted__U32_88 = 1;
            U32 hoisted__U32_89 = ((U32)(_fi_USize_85 + hoisted__U32_88));
            _fi_USize_85 = hoisted__U32_89;
            USize hoisted__U32_90 = (s->count);
            U32 hoisted__U32_91 = ((U32)(total + hoisted__U32_90));
            total = hoisted__U32_91;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_92 = parts;
        U32 _fi_USize_92 = 0;
        while (1) {
            USize hoisted__U32_94 = (_fc_Array__Str_92->cap);
            Bool _wcond_Bool_93 = ((Bool)(_fi_USize_92 < hoisted__U32_94));
            if (_wcond_Bool_93) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_92->data) + (((U32)(_fi_USize_92 * 16))))));
            U32 hoisted__U32_95 = 1;
            U32 hoisted__U32_96 = ((U32)(_fi_USize_92 + hoisted__U32_95));
            _fi_USize_92 = hoisted__U32_96;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_123 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_123) {
        Bool hoisted__Bool_121 = 0;
        return hoisted__Bool_121;
    }
    Bool hoisted__Bool_124 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_124) {
        Bool hoisted__Bool_122 = 1;
        return hoisted__Bool_122;
    }
    I32 hoisted__I32_125 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_126 = 0;
    Bool hoisted__Bool_127 = ((Bool)(hoisted__I32_125 == hoisted__I32_126));
    return hoisted__Bool_127;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_129 = 0;
    Bool hoisted__Bool_130 = ((Bool)(n == hoisted__U32_129));
    if (hoisted__Bool_130) {
        static Str hoisted__Str_128 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_128; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_131 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_131)));
    I32 hoisted__I32_132 = 0;
    U64 hoisted__U64_133 = 1ULL;
    memset(buf, hoisted__I32_132, hoisted__U64_133);
    I64 hoisted__I64_134 = 0;
    Str *hoisted__Str_135 = malloc(sizeof(Str));
    hoisted__Str_135->c_str = buf;
    hoisted__Str_135->count = hoisted__I64_134;
    hoisted__Str_135->cap = n;
    return hoisted__Str_135;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_146 = 0;
    Bool hoisted__Bool_147 = ((Bool)(s->count == hoisted__U32_146));
    if (hoisted__Bool_147) {
        return;
    }
    Bool hoisted__Bool_148 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_148) {
        U32 hoisted__U32_138 = 1;
        Array__Str *_va_Array_6 = Array__Str_new(hoisted__U32_138);
        I64 _va_Array_6_ek = 0;
        U32 hoisted__U32_139 = 0;
        static Str hoisted__Str_140 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_6, hoisted__U32_139, &hoisted__Str_140, &_va_Array_6_ek);
        static Str hoisted__Str_141 = (Str){.c_str = (void *)"./src/core/str.til:124:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_6, &hoisted__Str_141);
        Str_delete(&hoisted__Str_141, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_149 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_149) {
        U32 hoisted__U32_142 = 1;
        Array__Str *_va_Array_7 = Array__Str_new(hoisted__U32_142);
        I64 _va_Array_7_ek = 0;
        U32 hoisted__U32_143 = 0;
        static Str hoisted__Str_144 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_7, hoisted__U32_143, &hoisted__Str_144, &_va_Array_7_ek);
        static Str hoisted__Str_145 = (Str){.c_str = (void *)"./src/core/str.til:128:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_7, &hoisted__Str_145);
        Str_delete(&hoisted__Str_145, (Bool){0});
    }
    void *hoisted__v_150 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_150, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_151 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_152 = 0;
    U64 hoisted__U64_153 = 1ULL;
    memset(hoisted__v_151, hoisted__I32_152, hoisted__U64_153);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_155 = 0;
    Bool hoisted__Bool_156 = ((Bool)(val->count == hoisted__U32_155));
    if (hoisted__Bool_156) {
        static Str hoisted__Str_154 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_154; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_157 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_157)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_158 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_159 = 0;
    U64 hoisted__U64_160 = 1ULL;
    memset(hoisted__v_158, hoisted__I32_159, hoisted__U64_160);
    Str *hoisted__Str_161 = malloc(sizeof(Str));
    hoisted__Str_161->c_str = new_data;
    hoisted__Str_161->count = val->count;
    hoisted__Str_161->cap = val->count;
    return hoisted__Str_161;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_162 = Str_clone(self);
    return hoisted__Str_162;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_163 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_163) {
        free(self->c_str);
    }
    Bool hoisted__Bool_164 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_165 = ((Bool)((call_free) && (hoisted__Bool_164)));
    if (hoisted__Bool_165) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_549 = Str_eq(a, b);
    Bool hoisted__Bool_550 = ((Bool)(!(hoisted__Bool_549)));
    return hoisted__Bool_550;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_687 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_688 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_688->data = hoisted__v_687;
    hoisted__Array__Str_688->cap = cap;
    return hoisted__Array__Str_688;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_697 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Bool hoisted__Bool_698 = 0;
    Str_delete(hoisted__Str_697, hoisted__Bool_698);
    Str *hoisted__Str_699 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    adopt__Str(hoisted__Str_699, val);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_701 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_701) {
        I64 hoisted__I64_700 = 1;
        *_err_kind = hoisted__I64_700;
    }
    I64 hoisted__I64_702 = 0;
    Bool hoisted__Bool_703 = ((Bool)(DEREF(_err_kind) == hoisted__I64_702));
    if (hoisted__Bool_703) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_742 = self->cap;
        U32 _rc_U32_742 = 0;
        Bool hoisted__Bool_753 = ((Bool)(_rc_U32_742 <= _re_U32_742));
        if (hoisted__Bool_753) {
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
                Str *hoisted__Str_746 = ((void *)((U8 *)(self->data) + (hoisted__U32_745)));
                Bool hoisted__Bool_747 = 0;
                Str_delete(hoisted__Str_746, hoisted__Bool_747);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_748 = ((Bool)(_rc_U32_742 > _re_U32_742));
                if (_wcond_Bool_748) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_742);
                (--_rc_U32_742);
                U32 hoisted__U32_749 = 16;
                U32 hoisted__U32_750 = ((U32)(i * hoisted__U32_749));
                Str *hoisted__Str_751 = ((void *)((U8 *)(self->data) + (hoisted__U32_750)));
                Bool hoisted__Bool_752 = 0;
                Str_delete(hoisted__Str_751, hoisted__Bool_752);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_768 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_768)));
    {
        U32 _re_U32_754 = self->cap;
        U32 _rc_U32_754 = 0;
        Bool hoisted__Bool_767 = ((Bool)(_rc_U32_754 <= _re_U32_754));
        if (hoisted__Bool_767) {
            while (1) {
                Bool _wcond_Bool_755 = ((Bool)(_rc_U32_754 < _re_U32_754));
                if (_wcond_Bool_755) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_754);
                (++_rc_U32_754);
                U32 hoisted__U32_756 = 16;
                U32 hoisted__U32_757 = ((U32)(i * hoisted__U32_756));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_757)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_758 = 16;
                U32 hoisted__U32_759 = ((U32)(i * hoisted__U32_758));
                void *hoisted__v_760 = ((void *)((U8 *)(new_data) + (hoisted__U32_759)));
                adopt__Str(hoisted__v_760, cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_761 = ((Bool)(_rc_U32_754 > _re_U32_754));
                if (_wcond_Bool_761) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_754);
                (--_rc_U32_754);
                U32 hoisted__U32_762 = 16;
                U32 hoisted__U32_763 = ((U32)(i * hoisted__U32_762));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_763)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_764 = 16;
                U32 hoisted__U32_765 = ((U32)(i * hoisted__U32_764));
                void *hoisted__v_766 = ((void *)((U8 *)(new_data) + (hoisted__U32_765)));
                adopt__Str(hoisted__v_766, cloned);
            }
        }
    }
    Array__Str *hoisted__Array__Str_769 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_769->data = new_data;
    hoisted__Array__Str_769->cap = self->cap;
    return hoisted__Array__Str_769;
    __builtin_unreachable();
}

void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_1086 = 16;
    memcpy(dest, src, hoisted__U32_1086);
    if ((src)->cap != TIL_CAP_LIT) { free(src); };
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1411 = U64_to_str_ext(val);
    return hoisted__Str_1411;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1772 = 0;
    Bool hoisted__Bool_1773 = ((Bool)(val < hoisted__I64_1772));
    if (hoisted__Bool_1773) {
        U64 hoisted__U64_1764 = 0ULL;
        U64 hoisted__U64_1765 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_1764 - hoisted__U64_1765));
        U32 hoisted__U32_1766 = 2;
        Array__Str *_va_Array_54 = Array__Str_new(hoisted__U32_1766);
        I64 _va_Array_54_ek = 0;
        U32 hoisted__U32_1767 = 0;
        static Str hoisted__Str_1768 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_54, hoisted__U32_1767, &hoisted__Str_1768, &_va_Array_54_ek);
        U32 hoisted__U32_1769 = 1;
        Str *hoisted__Str_1770 = U64_to_str(mag);
        Array__Str_set(_va_Array_54, hoisted__U32_1769, hoisted__Str_1770, &_va_Array_54_ek);
        Str *hoisted__Str_1771 = format(_va_Array_54);
        return hoisted__Str_1771;
    }
    U64 hoisted__U64_1774 = (U64)(val);
    Str *hoisted__Str_1775 = U64_to_str(hoisted__U64_1774);
    return hoisted__Str_1775;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6568 = 3;
    Array__Str *_va_Array_226 = Array__Str_new(hoisted__U32_6568);
    I64 _va_Array_226_ek = 0;
    U32 hoisted__U32_6569 = 0;
    Str *hoisted__Str_6570 = Str_clone(loc);
    Array__Str_set(_va_Array_226, hoisted__U32_6569, hoisted__Str_6570, &_va_Array_226_ek);
    U32 hoisted__U32_6571 = 1;
    Array__Str_set(_va_Array_226, hoisted__U32_6571, &_til_str_lits[0], &_va_Array_226_ek);
    Array__Str *hoisted__Array__Str_6573 = Array__Str_clone(parts);
    U32 hoisted__U32_6574 = 2;
    Str *hoisted__Str_6575 = format(hoisted__Array__Str_6573);
    Array__Str_set(_va_Array_226, hoisted__U32_6574, hoisted__Str_6575, &_va_Array_226_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_226);
    I64 hoisted__I64_6576 = 1;
    exit(hoisted__I64_6576);
}

__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc) {
    USize hoisted__U32_6592 = (parts->cap);
    U32 hoisted__U32_6593 = 0;
    Bool hoisted__Bool_6594 = ((Bool)(hoisted__U32_6592 == hoisted__U32_6593));
    if (hoisted__Bool_6594) {
        U32 hoisted__U32_6583 = 1;
        Array__Str *_va_Array_228 = Array__Str_new(hoisted__U32_6583);
        I64 _va_Array_228_ek = 0;
        U32 hoisted__U32_6584 = 0;
        Array__Str_set(_va_Array_228, hoisted__U32_6584, &_til_str_lits[1], &_va_Array_228_ek);
        panic(_va_Array_228, loc);
    } else {
        U32 hoisted__U32_6586 = 2;
        Array__Str *_va_Array_229 = Array__Str_new(hoisted__U32_6586);
        I64 _va_Array_229_ek = 0;
        U32 hoisted__U32_6587 = 0;
        Array__Str_set(_va_Array_229, hoisted__U32_6587, &_til_str_lits[2], &_va_Array_229_ek);
        Array__Str *hoisted__Array__Str_6589 = Array__Str_clone(parts);
        U32 hoisted__U32_6590 = 1;
        Str *hoisted__Str_6591 = format(hoisted__Array__Str_6589);
        Array__Str_set(_va_Array_229, hoisted__U32_6590, hoisted__Str_6591, &_va_Array_229_ek);
        panic(_va_Array_229, loc);
    }
    Array__Str_delete(parts, 1);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6598 = ((Bool)(!(cond)));
    if (hoisted__Bool_6598) {
        U32 hoisted__U32_6595 = 1;
        Array__Str *_va_Array_230 = Array__Str_new(hoisted__U32_6595);
        I64 _va_Array_230_ek = 0;
        U32 hoisted__U32_6596 = 0;
        Array__Str_set(_va_Array_230, hoisted__U32_6596, &_til_str_lits[3], &_va_Array_230_ek);
        panic(_va_Array_230, loc);
    }
}

void expect(Bool cond, Array__Str * parts, Str * loc) {
    Bool hoisted__Bool_6605 = ((Bool)(!(cond)));
    if (hoisted__Bool_6605) {
        U32 hoisted__U32_6599 = 2;
        Array__Str *_va_Array_231 = Array__Str_new(hoisted__U32_6599);
        I64 _va_Array_231_ek = 0;
        U32 hoisted__U32_6600 = 0;
        Array__Str_set(_va_Array_231, hoisted__U32_6600, &_til_str_lits[4], &_va_Array_231_ek);
        Array__Str *hoisted__Array__Str_6602 = Array__Str_clone(parts);
        U32 hoisted__U32_6603 = 1;
        Str *hoisted__Str_6604 = format(hoisted__Array__Str_6602);
        Array__Str_set(_va_Array_231, hoisted__U32_6603, hoisted__Str_6604, &_va_Array_231_ek);
        panic(_va_Array_231, loc);
    }
    Array__Str_delete(parts, 1);
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6606 = parts;
        U32 _fi_USize_6606 = 0;
        while (1) {
            USize hoisted__U32_6608 = (_fc_Array__Str_6606->cap);
            Bool _wcond_Bool_6607 = ((Bool)(_fi_USize_6606 < hoisted__U32_6608));
            if (_wcond_Bool_6607) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_6606->data) + (((U32)(_fi_USize_6606 * 16))))));
            U32 hoisted__U32_6609 = 1;
            U32 hoisted__U32_6610 = ((U32)(_fi_USize_6606 + hoisted__U32_6609));
            _fi_USize_6606 = hoisted__U32_6610;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6678 = 3;
    assert_eq__I64(result, hoisted__I64_6678, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6686 = 15;
    assert_eq__I64(result, hoisted__I64_6686, &_til_str_lits[6]);
    Str_delete(&_til_str_lits[6], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6694 = 26;
    assert_eq__I64(result, hoisted__I64_6694, &_til_str_lits[7]);
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
    I64 hoisted__I64_6763 = 106;
    assert_eq__I64(d3, hoisted__I64_6763, &_til_str_lits[17]);
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
    I64 hoisted__I64_7256 = 8;
    assert_eq__I64(result, hoisted__I64_7256, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_7260 = 1;
    assert(hoisted__Bool_7260, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
    Bool hoisted__Bool_7264 = 1;
    assert(hoisted__Bool_7264, &_til_str_lits[22]);
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
    I64 hoisted__I64_7324 = 42;
    assert_eq__I64(v.x, hoisted__I64_7324, &_til_str_lits[27]);
    Str_delete(&_til_str_lits[27], (Bool){0});
    I64 hoisted__I64_7326 = 99;
    assert_eq__I64(v.y, hoisted__I64_7326, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_7330 = 10;
    assert_eq__I64(p.x, hoisted__I64_7330, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    I64 hoisted__I64_7332 = 20;
    assert_eq__I64(p.y, hoisted__I64_7332, &_til_str_lits[30]);
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
    I64 hoisted__I64_7381 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_7381, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    I64 hoisted__I64_7383 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_7383, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_7385 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_7385, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_7387 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_7387, &_til_str_lits[34]);
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
    Str *hoisted__Str_7443 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_7443, &_til_str_lits[35], &_til_str_lits[36]);
    Str_delete(hoisted__Str_7443, 1);
    Str_delete(&_til_str_lits[35], (Bool){0});
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str *hoisted__Str_7446 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_7446, &_til_str_lits[37], &_til_str_lits[38]);
    Str_delete(hoisted__Str_7446, 1);
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str *hoisted__Str_7449 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_7449, &_til_str_lits[39], &_til_str_lits[40]);
    Str_delete(hoisted__Str_7449, 1);
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str_delete(&_til_str_lits[40], (Bool){0});
    CfVec3f_delete(&v, (Bool){0});
}

Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_7452 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_7452;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7499 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_7499, &_til_str_lits[41]);
    Str_delete(&_til_str_lits[41], (Bool){0});
    Bool hoisted__Bool_7501 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_7502 = ((Bool)(!(hoisted__Bool_7501)));
    assert(hoisted__Bool_7502, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7521 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_7521) {
        I64 *hoisted__I64_7517 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7518 = 0;
        I64_delete(hoisted__I64_7517, hoisted__Bool_7518);
    }
    Bool hoisted__Bool_7522 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_7522) {
        Str *hoisted__Str_7519 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7520 = 0;
        Str_delete(hoisted__Str_7519, hoisted__Bool_7520);
    }
    if (call_free) {
        free(self);
    }
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7584 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7584, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
    Bool hoisted__Bool_7586 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7587 = ((Bool)(!(hoisted__Bool_7586)));
    assert(hoisted__Bool_7587, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7589 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_7589, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Bool hoisted__Bool_7591 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_7592 = ((Bool)(!(hoisted__Bool_7591)));
    assert(hoisted__Bool_7592, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7596 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7596, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
    Bool hoisted__Bool_7598 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7599 = ((Bool)(!(hoisted__Bool_7598)));
    assert(hoisted__Bool_7599, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Token_delete(t, 1);
}

void test_const_and_or_fold(void) {
    U32 hoisted__U32_7607 = 1;
    Array__Str *_va_Array_268 = Array__Str_new(hoisted__U32_7607);
    I64 _va_Array_268_ek = 0;
    U32 hoisted__U32_7608 = 0;
    Array__Str_set(_va_Array_268, hoisted__U32_7608, &_til_str_lits[49], &_va_Array_268_ek);
    Bool hoisted__Bool_7610 = 1;
    expect(hoisted__Bool_7610, _va_Array_268, &_til_str_lits[50]);
    Str_delete(&_til_str_lits[50], (Bool){0});
    U32 hoisted__U32_7612 = 1;
    Array__Str *_va_Array_269 = Array__Str_new(hoisted__U32_7612);
    I64 _va_Array_269_ek = 0;
    U32 hoisted__U32_7613 = 0;
    Array__Str_set(_va_Array_269, hoisted__U32_7613, &_til_str_lits[51], &_va_Array_269_ek);
    Bool hoisted__Bool_7616 = 1;
    expect(hoisted__Bool_7616, _va_Array_269, &_til_str_lits[52]);
    Str_delete(&_til_str_lits[52], (Bool){0});
    U32 hoisted__U32_7618 = 1;
    Array__Str *_va_Array_270 = Array__Str_new(hoisted__U32_7618);
    I64 _va_Array_270_ek = 0;
    U32 hoisted__U32_7619 = 0;
    Array__Str_set(_va_Array_270, hoisted__U32_7619, &_til_str_lits[53], &_va_Array_270_ek);
    Bool hoisted__Bool_7621 = 1;
    expect(hoisted__Bool_7621, _va_Array_270, &_til_str_lits[54]);
    Str_delete(&_til_str_lits[54], (Bool){0});
    U32 hoisted__U32_7623 = 1;
    Array__Str *_va_Array_271 = Array__Str_new(hoisted__U32_7623);
    I64 _va_Array_271_ek = 0;
    U32 hoisted__U32_7624 = 0;
    Array__Str_set(_va_Array_271, hoisted__U32_7624, &_til_str_lits[55], &_va_Array_271_ek);
    Bool hoisted__Bool_7627 = 1;
    expect(hoisted__Bool_7627, _va_Array_271, &_til_str_lits[56]);
    Str_delete(&_til_str_lits[56], (Bool){0});
    U32 hoisted__U32_7629 = 1;
    Array__Str *_va_Array_272 = Array__Str_new(hoisted__U32_7629);
    I64 _va_Array_272_ek = 0;
    U32 hoisted__U32_7630 = 0;
    Array__Str_set(_va_Array_272, hoisted__U32_7630, &_til_str_lits[57], &_va_Array_272_ek);
    Bool hoisted__Bool_7632 = 1;
    expect(hoisted__Bool_7632, _va_Array_272, &_til_str_lits[58]);
    Str_delete(&_til_str_lits[58], (Bool){0});
    U32 hoisted__U32_7634 = 1;
    Array__Str *_va_Array_273 = Array__Str_new(hoisted__U32_7634);
    I64 _va_Array_273_ek = 0;
    U32 hoisted__U32_7635 = 0;
    Array__Str_set(_va_Array_273, hoisted__U32_7635, &_til_str_lits[59], &_va_Array_273_ek);
    Bool hoisted__Bool_7638 = 1;
    expect(hoisted__Bool_7638, _va_Array_273, &_til_str_lits[60]);
    Str_delete(&_til_str_lits[60], (Bool){0});
    U32 hoisted__U32_7640 = 1;
    Array__Str *_va_Array_274 = Array__Str_new(hoisted__U32_7640);
    I64 _va_Array_274_ek = 0;
    U32 hoisted__U32_7641 = 0;
    Array__Str_set(_va_Array_274, hoisted__U32_7641, &_til_str_lits[61], &_va_Array_274_ek);
    Bool hoisted__Bool_7643 = 1;
    expect(hoisted__Bool_7643, _va_Array_274, &_til_str_lits[62]);
    Str_delete(&_til_str_lits[62], (Bool){0});
    U32 hoisted__U32_7645 = 1;
    Array__Str *_va_Array_275 = Array__Str_new(hoisted__U32_7645);
    I64 _va_Array_275_ek = 0;
    U32 hoisted__U32_7646 = 0;
    Array__Str_set(_va_Array_275, hoisted__U32_7646, &_til_str_lits[63], &_va_Array_275_ek);
    Bool hoisted__Bool_7649 = 1;
    expect(hoisted__Bool_7649, _va_Array_275, &_til_str_lits[64]);
    Str_delete(&_til_str_lits[64], (Bool){0});
    U32 hoisted__U32_7651 = 1;
    Array__Str *_va_Array_276 = Array__Str_new(hoisted__U32_7651);
    I64 _va_Array_276_ek = 0;
    U32 hoisted__U32_7652 = 0;
    Array__Str_set(_va_Array_276, hoisted__U32_7652, &_til_str_lits[65], &_va_Array_276_ek);
    Bool hoisted__Bool_7654 = 1;
    expect(hoisted__Bool_7654, _va_Array_276, &_til_str_lits[66]);
    Str_delete(&_til_str_lits[66], (Bool){0});
    Bool _m_Bool_7601 = 0;
    {
        Bool hoisted__Bool_7606 = 0;
        if (hoisted__Bool_7606) {
            Bool hoisted__Bool_7603 = 1;
            _m_Bool_7601 = hoisted__Bool_7603;
        } else {
            Bool hoisted__Bool_7604 = 1;
            _m_Bool_7601 = hoisted__Bool_7604;
        }
    }
    U32 hoisted__U32_7656 = 1;
    Array__Str *_va_Array_277 = Array__Str_new(hoisted__U32_7656);
    I64 _va_Array_277_ek = 0;
    U32 hoisted__U32_7657 = 0;
    Array__Str_set(_va_Array_277, hoisted__U32_7657, &_til_str_lits[67], &_va_Array_277_ek);
    expect(_m_Bool_7601, _va_Array_277, &_til_str_lits[68]);
    Str_delete(&_til_str_lits[68], (Bool){0});
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7755 = ((Bool)(a != b));
    if (hoisted__Bool_7755) {
        U32 hoisted__U32_7744 = 5;
        Array__Str *_va_Array_283 = Array__Str_new(hoisted__U32_7744);
        I64 _va_Array_283_ek = 0;
        U32 hoisted__U32_7745 = 0;
        Array__Str_set(_va_Array_283, hoisted__U32_7745, &_til_str_lits[69], &_va_Array_283_ek);
        U32 hoisted__U32_7747 = 1;
        Str *hoisted__Str_7748 = I64_to_str(a);
        Array__Str_set(_va_Array_283, hoisted__U32_7747, hoisted__Str_7748, &_va_Array_283_ek);
        U32 hoisted__U32_7749 = 2;
        Array__Str_set(_va_Array_283, hoisted__U32_7749, &_til_str_lits[70], &_va_Array_283_ek);
        U32 hoisted__U32_7751 = 3;
        Str *hoisted__Str_7752 = I64_to_str(b);
        Array__Str_set(_va_Array_283, hoisted__U32_7751, hoisted__Str_7752, &_va_Array_283_ek);
        U32 hoisted__U32_7753 = 4;
        Array__Str_set(_va_Array_283, hoisted__U32_7753, &_til_str_lits[71], &_va_Array_283_ek);
        panic(_va_Array_283, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7767 = Str_neq(a, b);
    if (hoisted__Bool_7767) {
        U32 hoisted__U32_7756 = 5;
        Array__Str *_va_Array_284 = Array__Str_new(hoisted__U32_7756);
        I64 _va_Array_284_ek = 0;
        U32 hoisted__U32_7757 = 0;
        Array__Str_set(_va_Array_284, hoisted__U32_7757, &_til_str_lits[69], &_va_Array_284_ek);
        U32 hoisted__U32_7759 = 1;
        Str *hoisted__Str_7760 = Str_to_str(a);
        Array__Str_set(_va_Array_284, hoisted__U32_7759, hoisted__Str_7760, &_va_Array_284_ek);
        U32 hoisted__U32_7761 = 2;
        Array__Str_set(_va_Array_284, hoisted__U32_7761, &_til_str_lits[70], &_va_Array_284_ek);
        U32 hoisted__U32_7763 = 3;
        Str *hoisted__Str_7764 = Str_to_str(b);
        Array__Str_set(_va_Array_284, hoisted__U32_7763, hoisted__Str_7764, &_va_Array_284_ek);
        U32 hoisted__U32_7765 = 4;
        Array__Str_set(_va_Array_284, hoisted__U32_7765, &_til_str_lits[71], &_va_Array_284_ek);
        panic(_va_Array_284, loc);
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
