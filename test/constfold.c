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
    void *(*clone)(void *);
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
void adopt_from(void * dest, void * src, UPtr size);
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
        Array__Str *_fc_Array__Str_338 = parts;
        U32 _fi_USize_338 = 0;
        while (1) {
            USize hoisted__U32_340 = (_fc_Array__Str_338->cap);
            Bool _wcond_Bool_339 = ((Bool)(_fi_USize_338 < hoisted__U32_340));
            if (_wcond_Bool_339) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_338->data) + (((U32)(_fi_USize_338 * 16))))));
            U32 hoisted__U32_341 = 1;
            U32 hoisted__U32_342 = ((U32)(_fi_USize_338 + hoisted__U32_341));
            _fi_USize_338 = hoisted__U32_342;
            USize hoisted__U32_343 = (s->count);
            U32 hoisted__U32_344 = ((U32)(total + hoisted__U32_343));
            total = hoisted__U32_344;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_345 = parts;
        U32 _fi_USize_345 = 0;
        while (1) {
            USize hoisted__U32_347 = (_fc_Array__Str_345->cap);
            Bool _wcond_Bool_346 = ((Bool)(_fi_USize_345 < hoisted__U32_347));
            if (_wcond_Bool_346) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_345->data) + (((U32)(_fi_USize_345 * 16))))));
            U32 hoisted__U32_348 = 1;
            U32 hoisted__U32_349 = ((U32)(_fi_USize_345 + hoisted__U32_348));
            _fi_USize_345 = hoisted__U32_349;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_376 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_376) {
        Bool hoisted__Bool_374 = 0;
        return hoisted__Bool_374;
    }
    Bool hoisted__Bool_377 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_377) {
        Bool hoisted__Bool_375 = 1;
        return hoisted__Bool_375;
    }
    I32 hoisted__I32_378 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_379 = 0;
    Bool hoisted__Bool_380 = ((Bool)(hoisted__I32_378 == hoisted__I32_379));
    return hoisted__Bool_380;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_382 = 0;
    Bool hoisted__Bool_383 = ((Bool)(n == hoisted__U32_382));
    if (hoisted__Bool_383) {
        static Str hoisted__Str_381 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_381; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_384 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_384)));
    I32 hoisted__I32_385 = 0;
    U64 hoisted__U64_386 = 1ULL;
    memset(buf, hoisted__I32_385, hoisted__U64_386);
    I64 hoisted__I64_387 = 0;
    Str *hoisted__Str_388 = malloc(sizeof(Str));
    hoisted__Str_388->c_str = buf;
    hoisted__Str_388->count = hoisted__I64_387;
    hoisted__Str_388->cap = n;
    return hoisted__Str_388;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_399 = 0;
    Bool hoisted__Bool_400 = ((Bool)(s->count == hoisted__U32_399));
    if (hoisted__Bool_400) {
        return;
    }
    Bool hoisted__Bool_401 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_401) {
        U32 hoisted__U32_391 = 1;
        Array__Str *_va_Array_5 = Array__Str_new(hoisted__U32_391);
        I64 _va_Array_5_ek = 0;
        U32 hoisted__U32_392 = 0;
        static Str hoisted__Str_393 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_5, hoisted__U32_392, &hoisted__Str_393, &_va_Array_5_ek);
        static Str hoisted__Str_394 = (Str){.c_str = (void *)"./src/core/str.til:124:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_5, &hoisted__Str_394);
        Str_delete(&hoisted__Str_394, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_402 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_402) {
        U32 hoisted__U32_395 = 1;
        Array__Str *_va_Array_6 = Array__Str_new(hoisted__U32_395);
        I64 _va_Array_6_ek = 0;
        U32 hoisted__U32_396 = 0;
        static Str hoisted__Str_397 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_6, hoisted__U32_396, &hoisted__Str_397, &_va_Array_6_ek);
        static Str hoisted__Str_398 = (Str){.c_str = (void *)"./src/core/str.til:128:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_6, &hoisted__Str_398);
        Str_delete(&hoisted__Str_398, (Bool){0});
    }
    void *hoisted__v_403 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_403, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_404 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_405 = 0;
    U64 hoisted__U64_406 = 1ULL;
    memset(hoisted__v_404, hoisted__I32_405, hoisted__U64_406);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_408 = 0;
    Bool hoisted__Bool_409 = ((Bool)(val->count == hoisted__U32_408));
    if (hoisted__Bool_409) {
        static Str hoisted__Str_407 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_407; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_410 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_410)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_411 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_412 = 0;
    U64 hoisted__U64_413 = 1ULL;
    memset(hoisted__v_411, hoisted__I32_412, hoisted__U64_413);
    Str *hoisted__Str_414 = malloc(sizeof(Str));
    hoisted__Str_414->c_str = new_data;
    hoisted__Str_414->count = val->count;
    hoisted__Str_414->cap = val->count;
    return hoisted__Str_414;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_415 = Str_clone(self);
    return hoisted__Str_415;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_416 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_416) {
        free(self->c_str);
    }
    Bool hoisted__Bool_417 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_418 = ((Bool)((call_free) && (hoisted__Bool_417)));
    if (hoisted__Bool_418) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_802 = Str_eq(a, b);
    Bool hoisted__Bool_803 = ((Bool)(!(hoisted__Bool_802)));
    return hoisted__Bool_803;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_940 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_941 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_941->data = hoisted__v_940;
    hoisted__Array__Str_941->cap = cap;
    return hoisted__Array__Str_941;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_950 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Bool hoisted__Bool_951 = 0;
    Str_delete(hoisted__Str_950, hoisted__Bool_951);
    Str *hoisted__Str_952 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    adopt__Str(hoisted__Str_952, val);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_954 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_954) {
        I64 hoisted__I64_953 = 1;
        *_err_kind = hoisted__I64_953;
    }
    I64 hoisted__I64_955 = 0;
    Bool hoisted__Bool_956 = ((Bool)(DEREF(_err_kind) == hoisted__I64_955));
    if (hoisted__Bool_956) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_957 = self->cap;
        U32 _rc_U32_957 = 0;
        Bool hoisted__Bool_968 = ((Bool)(_rc_U32_957 <= _re_U32_957));
        if (hoisted__Bool_968) {
            while (1) {
                Bool _wcond_Bool_958 = ((Bool)(_rc_U32_957 < _re_U32_957));
                if (_wcond_Bool_958) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_957);
                (++_rc_U32_957);
                U32 hoisted__U32_959 = 16;
                U32 hoisted__U32_960 = ((U32)(i * hoisted__U32_959));
                Str *hoisted__Str_961 = ((void *)((U8 *)(self->data) + (hoisted__U32_960)));
                Bool hoisted__Bool_962 = 0;
                Str_delete(hoisted__Str_961, hoisted__Bool_962);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_963 = ((Bool)(_rc_U32_957 > _re_U32_957));
                if (_wcond_Bool_963) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_957);
                (--_rc_U32_957);
                U32 hoisted__U32_964 = 16;
                U32 hoisted__U32_965 = ((U32)(i * hoisted__U32_964));
                Str *hoisted__Str_966 = ((void *)((U8 *)(self->data) + (hoisted__U32_965)));
                Bool hoisted__Bool_967 = 0;
                Str_delete(hoisted__Str_966, hoisted__Bool_967);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1023 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_1023)));
    {
        U32 _re_U32_1009 = self->cap;
        U32 _rc_U32_1009 = 0;
        Bool hoisted__Bool_1022 = ((Bool)(_rc_U32_1009 <= _re_U32_1009));
        if (hoisted__Bool_1022) {
            while (1) {
                Bool _wcond_Bool_1010 = ((Bool)(_rc_U32_1009 < _re_U32_1009));
                if (_wcond_Bool_1010) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_1009);
                (++_rc_U32_1009);
                U32 hoisted__U32_1011 = 16;
                U32 hoisted__U32_1012 = ((U32)(i * hoisted__U32_1011));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_1012)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1013 = 16;
                U32 hoisted__U32_1014 = ((U32)(i * hoisted__U32_1013));
                void *hoisted__v_1015 = ((void *)((U8 *)(new_data) + (hoisted__U32_1014)));
                adopt__Str(hoisted__v_1015, cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1016 = ((Bool)(_rc_U32_1009 > _re_U32_1009));
                if (_wcond_Bool_1016) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_1009);
                (--_rc_U32_1009);
                U32 hoisted__U32_1017 = 16;
                U32 hoisted__U32_1018 = ((U32)(i * hoisted__U32_1017));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_1018)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1019 = 16;
                U32 hoisted__U32_1020 = ((U32)(i * hoisted__U32_1019));
                void *hoisted__v_1021 = ((void *)((U8 *)(new_data) + (hoisted__U32_1020)));
                adopt__Str(hoisted__v_1021, cloned);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1024 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1024->data = new_data;
    hoisted__Array__Str_1024->cap = self->cap;
    return hoisted__Array__Str_1024;
    __builtin_unreachable();
}

void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_1277 = 16;
    memcpy(dest, src, hoisted__U32_1277);
    if ((src)->cap != TIL_CAP_LIT) { free(src); };
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1649 = U64_to_str_ext(val);
    return hoisted__Str_1649;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_2010 = 0;
    Bool hoisted__Bool_2011 = ((Bool)(val < hoisted__I64_2010));
    if (hoisted__Bool_2011) {
        U64 hoisted__U64_2002 = 0ULL;
        U64 hoisted__U64_2003 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_2002 - hoisted__U64_2003));
        U32 hoisted__U32_2004 = 2;
        Array__Str *_va_Array_43 = Array__Str_new(hoisted__U32_2004);
        I64 _va_Array_43_ek = 0;
        U32 hoisted__U32_2005 = 0;
        static Str hoisted__Str_2006 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_43, hoisted__U32_2005, &hoisted__Str_2006, &_va_Array_43_ek);
        U32 hoisted__U32_2007 = 1;
        Str *hoisted__Str_2008 = U64_to_str(mag);
        Array__Str_set(_va_Array_43, hoisted__U32_2007, hoisted__Str_2008, &_va_Array_43_ek);
        Str *hoisted__Str_2009 = format(_va_Array_43);
        return hoisted__Str_2009;
    }
    U64 hoisted__U64_2012 = (U64)(val);
    Str *hoisted__Str_2013 = U64_to_str(hoisted__U64_2012);
    return hoisted__Str_2013;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6295 = 3;
    Array__Str *_va_Array_170 = Array__Str_new(hoisted__U32_6295);
    I64 _va_Array_170_ek = 0;
    U32 hoisted__U32_6296 = 0;
    Str *hoisted__Str_6297 = Str_clone(loc);
    Array__Str_set(_va_Array_170, hoisted__U32_6296, hoisted__Str_6297, &_va_Array_170_ek);
    U32 hoisted__U32_6298 = 1;
    Array__Str_set(_va_Array_170, hoisted__U32_6298, &_til_str_lits[0], &_va_Array_170_ek);
    Array__Str *hoisted__Array__Str_6300 = Array__Str_clone(parts);
    U32 hoisted__U32_6301 = 2;
    Str *hoisted__Str_6302 = format(hoisted__Array__Str_6300);
    Array__Str_set(_va_Array_170, hoisted__U32_6301, hoisted__Str_6302, &_va_Array_170_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_170);
    I64 hoisted__I64_6303 = 1;
    exit(hoisted__I64_6303);
}

__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc) {
    USize hoisted__U32_6325 = (parts->cap);
    U32 hoisted__U32_6326 = 0;
    Bool hoisted__Bool_6327 = ((Bool)(hoisted__U32_6325 == hoisted__U32_6326));
    if (hoisted__Bool_6327) {
        U32 hoisted__U32_6316 = 1;
        Array__Str *_va_Array_173 = Array__Str_new(hoisted__U32_6316);
        I64 _va_Array_173_ek = 0;
        U32 hoisted__U32_6317 = 0;
        Array__Str_set(_va_Array_173, hoisted__U32_6317, &_til_str_lits[1], &_va_Array_173_ek);
        panic(_va_Array_173, loc);
    } else {
        U32 hoisted__U32_6319 = 2;
        Array__Str *_va_Array_174 = Array__Str_new(hoisted__U32_6319);
        I64 _va_Array_174_ek = 0;
        U32 hoisted__U32_6320 = 0;
        Array__Str_set(_va_Array_174, hoisted__U32_6320, &_til_str_lits[2], &_va_Array_174_ek);
        Array__Str *hoisted__Array__Str_6322 = Array__Str_clone(parts);
        U32 hoisted__U32_6323 = 1;
        Str *hoisted__Str_6324 = format(hoisted__Array__Str_6322);
        Array__Str_set(_va_Array_174, hoisted__U32_6323, hoisted__Str_6324, &_va_Array_174_ek);
        panic(_va_Array_174, loc);
    }
    Array__Str_delete(parts, 1);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6331 = ((Bool)(!(cond)));
    if (hoisted__Bool_6331) {
        U32 hoisted__U32_6328 = 1;
        Array__Str *_va_Array_175 = Array__Str_new(hoisted__U32_6328);
        I64 _va_Array_175_ek = 0;
        U32 hoisted__U32_6329 = 0;
        Array__Str_set(_va_Array_175, hoisted__U32_6329, &_til_str_lits[3], &_va_Array_175_ek);
        panic(_va_Array_175, loc);
    }
}

void expect(Bool cond, Array__Str * parts, Str * loc) {
    Bool hoisted__Bool_6338 = ((Bool)(!(cond)));
    if (hoisted__Bool_6338) {
        U32 hoisted__U32_6332 = 2;
        Array__Str *_va_Array_176 = Array__Str_new(hoisted__U32_6332);
        I64 _va_Array_176_ek = 0;
        U32 hoisted__U32_6333 = 0;
        Array__Str_set(_va_Array_176, hoisted__U32_6333, &_til_str_lits[4], &_va_Array_176_ek);
        Array__Str *hoisted__Array__Str_6335 = Array__Str_clone(parts);
        U32 hoisted__U32_6336 = 1;
        Str *hoisted__Str_6337 = format(hoisted__Array__Str_6335);
        Array__Str_set(_va_Array_176, hoisted__U32_6336, hoisted__Str_6337, &_va_Array_176_ek);
        panic(_va_Array_176, loc);
    }
    Array__Str_delete(parts, 1);
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6339 = parts;
        U32 _fi_USize_6339 = 0;
        while (1) {
            USize hoisted__U32_6341 = (_fc_Array__Str_6339->cap);
            Bool _wcond_Bool_6340 = ((Bool)(_fi_USize_6339 < hoisted__U32_6341));
            if (_wcond_Bool_6340) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_6339->data) + (((U32)(_fi_USize_6339 * 16))))));
            U32 hoisted__U32_6342 = 1;
            U32 hoisted__U32_6343 = ((U32)(_fi_USize_6339 + hoisted__U32_6342));
            _fi_USize_6339 = hoisted__U32_6343;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void adopt_from(void * dest, void * src, UPtr size) {
    memcpy(dest, src, size);
    I32 hoisted__I32_6349 = 0;
    memset(src, hoisted__I32_6349, size);
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6412 = 3;
    assert_eq__I64(result, hoisted__I64_6412, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6420 = 15;
    assert_eq__I64(result, hoisted__I64_6420, &_til_str_lits[6]);
    Str_delete(&_til_str_lits[6], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6428 = 26;
    assert_eq__I64(result, hoisted__I64_6428, &_til_str_lits[7]);
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
    I64 hoisted__I64_6497 = 106;
    assert_eq__I64(d3, hoisted__I64_6497, &_til_str_lits[17]);
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
    I64 hoisted__I64_6990 = 8;
    assert_eq__I64(result, hoisted__I64_6990, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6994 = 1;
    assert(hoisted__Bool_6994, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
    Bool hoisted__Bool_6998 = 1;
    assert(hoisted__Bool_6998, &_til_str_lits[22]);
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
    I64 hoisted__I64_7058 = 42;
    assert_eq__I64(v.x, hoisted__I64_7058, &_til_str_lits[27]);
    Str_delete(&_til_str_lits[27], (Bool){0});
    I64 hoisted__I64_7060 = 99;
    assert_eq__I64(v.y, hoisted__I64_7060, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_7064 = 10;
    assert_eq__I64(p.x, hoisted__I64_7064, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    I64 hoisted__I64_7066 = 20;
    assert_eq__I64(p.y, hoisted__I64_7066, &_til_str_lits[30]);
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
    I64 hoisted__I64_7115 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_7115, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    I64 hoisted__I64_7117 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_7117, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_7119 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_7119, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_7121 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_7121, &_til_str_lits[34]);
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
    Str *hoisted__Str_7177 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_7177, &_til_str_lits[35], &_til_str_lits[36]);
    Str_delete(hoisted__Str_7177, 1);
    Str_delete(&_til_str_lits[35], (Bool){0});
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str *hoisted__Str_7180 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_7180, &_til_str_lits[37], &_til_str_lits[38]);
    Str_delete(hoisted__Str_7180, 1);
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str *hoisted__Str_7183 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_7183, &_til_str_lits[39], &_til_str_lits[40]);
    Str_delete(hoisted__Str_7183, 1);
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str_delete(&_til_str_lits[40], (Bool){0});
    CfVec3f_delete(&v, (Bool){0});
}

Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_7186 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_7186;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7233 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_7233, &_til_str_lits[41]);
    Str_delete(&_til_str_lits[41], (Bool){0});
    Bool hoisted__Bool_7235 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_7236 = ((Bool)(!(hoisted__Bool_7235)));
    assert(hoisted__Bool_7236, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7255 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_7255) {
        I64 *hoisted__I64_7251 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7252 = 0;
        I64_delete(hoisted__I64_7251, hoisted__Bool_7252);
    }
    Bool hoisted__Bool_7256 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_7256) {
        Str *hoisted__Str_7253 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7254 = 0;
        Str_delete(hoisted__Str_7253, hoisted__Bool_7254);
    }
    if (call_free) {
        free(self);
    }
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7318 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7318, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
    Bool hoisted__Bool_7320 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7321 = ((Bool)(!(hoisted__Bool_7320)));
    assert(hoisted__Bool_7321, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7323 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_7323, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Bool hoisted__Bool_7325 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_7326 = ((Bool)(!(hoisted__Bool_7325)));
    assert(hoisted__Bool_7326, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7330 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7330, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
    Bool hoisted__Bool_7332 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7333 = ((Bool)(!(hoisted__Bool_7332)));
    assert(hoisted__Bool_7333, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Token_delete(t, 1);
}

void test_const_and_or_fold(void) {
    U32 hoisted__U32_7341 = 1;
    Array__Str *_va_Array_213 = Array__Str_new(hoisted__U32_7341);
    I64 _va_Array_213_ek = 0;
    U32 hoisted__U32_7342 = 0;
    Array__Str_set(_va_Array_213, hoisted__U32_7342, &_til_str_lits[49], &_va_Array_213_ek);
    Bool hoisted__Bool_7344 = 1;
    expect(hoisted__Bool_7344, _va_Array_213, &_til_str_lits[50]);
    Str_delete(&_til_str_lits[50], (Bool){0});
    U32 hoisted__U32_7346 = 1;
    Array__Str *_va_Array_214 = Array__Str_new(hoisted__U32_7346);
    I64 _va_Array_214_ek = 0;
    U32 hoisted__U32_7347 = 0;
    Array__Str_set(_va_Array_214, hoisted__U32_7347, &_til_str_lits[51], &_va_Array_214_ek);
    Bool hoisted__Bool_7350 = 1;
    expect(hoisted__Bool_7350, _va_Array_214, &_til_str_lits[52]);
    Str_delete(&_til_str_lits[52], (Bool){0});
    U32 hoisted__U32_7352 = 1;
    Array__Str *_va_Array_215 = Array__Str_new(hoisted__U32_7352);
    I64 _va_Array_215_ek = 0;
    U32 hoisted__U32_7353 = 0;
    Array__Str_set(_va_Array_215, hoisted__U32_7353, &_til_str_lits[53], &_va_Array_215_ek);
    Bool hoisted__Bool_7355 = 1;
    expect(hoisted__Bool_7355, _va_Array_215, &_til_str_lits[54]);
    Str_delete(&_til_str_lits[54], (Bool){0});
    U32 hoisted__U32_7357 = 1;
    Array__Str *_va_Array_216 = Array__Str_new(hoisted__U32_7357);
    I64 _va_Array_216_ek = 0;
    U32 hoisted__U32_7358 = 0;
    Array__Str_set(_va_Array_216, hoisted__U32_7358, &_til_str_lits[55], &_va_Array_216_ek);
    Bool hoisted__Bool_7361 = 1;
    expect(hoisted__Bool_7361, _va_Array_216, &_til_str_lits[56]);
    Str_delete(&_til_str_lits[56], (Bool){0});
    U32 hoisted__U32_7363 = 1;
    Array__Str *_va_Array_217 = Array__Str_new(hoisted__U32_7363);
    I64 _va_Array_217_ek = 0;
    U32 hoisted__U32_7364 = 0;
    Array__Str_set(_va_Array_217, hoisted__U32_7364, &_til_str_lits[57], &_va_Array_217_ek);
    Bool hoisted__Bool_7366 = 1;
    expect(hoisted__Bool_7366, _va_Array_217, &_til_str_lits[58]);
    Str_delete(&_til_str_lits[58], (Bool){0});
    U32 hoisted__U32_7368 = 1;
    Array__Str *_va_Array_218 = Array__Str_new(hoisted__U32_7368);
    I64 _va_Array_218_ek = 0;
    U32 hoisted__U32_7369 = 0;
    Array__Str_set(_va_Array_218, hoisted__U32_7369, &_til_str_lits[59], &_va_Array_218_ek);
    Bool hoisted__Bool_7372 = 1;
    expect(hoisted__Bool_7372, _va_Array_218, &_til_str_lits[60]);
    Str_delete(&_til_str_lits[60], (Bool){0});
    U32 hoisted__U32_7374 = 1;
    Array__Str *_va_Array_219 = Array__Str_new(hoisted__U32_7374);
    I64 _va_Array_219_ek = 0;
    U32 hoisted__U32_7375 = 0;
    Array__Str_set(_va_Array_219, hoisted__U32_7375, &_til_str_lits[61], &_va_Array_219_ek);
    Bool hoisted__Bool_7377 = 1;
    expect(hoisted__Bool_7377, _va_Array_219, &_til_str_lits[62]);
    Str_delete(&_til_str_lits[62], (Bool){0});
    U32 hoisted__U32_7379 = 1;
    Array__Str *_va_Array_220 = Array__Str_new(hoisted__U32_7379);
    I64 _va_Array_220_ek = 0;
    U32 hoisted__U32_7380 = 0;
    Array__Str_set(_va_Array_220, hoisted__U32_7380, &_til_str_lits[63], &_va_Array_220_ek);
    Bool hoisted__Bool_7383 = 1;
    expect(hoisted__Bool_7383, _va_Array_220, &_til_str_lits[64]);
    Str_delete(&_til_str_lits[64], (Bool){0});
    U32 hoisted__U32_7385 = 1;
    Array__Str *_va_Array_221 = Array__Str_new(hoisted__U32_7385);
    I64 _va_Array_221_ek = 0;
    U32 hoisted__U32_7386 = 0;
    Array__Str_set(_va_Array_221, hoisted__U32_7386, &_til_str_lits[65], &_va_Array_221_ek);
    Bool hoisted__Bool_7388 = 1;
    expect(hoisted__Bool_7388, _va_Array_221, &_til_str_lits[66]);
    Str_delete(&_til_str_lits[66], (Bool){0});
    Bool _m_Bool_7335 = 0;
    {
        Bool hoisted__Bool_7340 = 0;
        if (hoisted__Bool_7340) {
            Bool hoisted__Bool_7337 = 1;
            _m_Bool_7335 = hoisted__Bool_7337;
        } else {
            Bool hoisted__Bool_7338 = 1;
            _m_Bool_7335 = hoisted__Bool_7338;
        }
    }
    U32 hoisted__U32_7390 = 1;
    Array__Str *_va_Array_222 = Array__Str_new(hoisted__U32_7390);
    I64 _va_Array_222_ek = 0;
    U32 hoisted__U32_7391 = 0;
    Array__Str_set(_va_Array_222, hoisted__U32_7391, &_til_str_lits[67], &_va_Array_222_ek);
    expect(_m_Bool_7335, _va_Array_222, &_til_str_lits[68]);
    Str_delete(&_til_str_lits[68], (Bool){0});
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7742 = ((Bool)(a != b));
    if (hoisted__Bool_7742) {
        U32 hoisted__U32_7731 = 5;
        Array__Str *_va_Array_227 = Array__Str_new(hoisted__U32_7731);
        I64 _va_Array_227_ek = 0;
        U32 hoisted__U32_7732 = 0;
        Array__Str_set(_va_Array_227, hoisted__U32_7732, &_til_str_lits[69], &_va_Array_227_ek);
        U32 hoisted__U32_7734 = 1;
        Str *hoisted__Str_7735 = I64_to_str(a);
        Array__Str_set(_va_Array_227, hoisted__U32_7734, hoisted__Str_7735, &_va_Array_227_ek);
        U32 hoisted__U32_7736 = 2;
        Array__Str_set(_va_Array_227, hoisted__U32_7736, &_til_str_lits[70], &_va_Array_227_ek);
        U32 hoisted__U32_7738 = 3;
        Str *hoisted__Str_7739 = I64_to_str(b);
        Array__Str_set(_va_Array_227, hoisted__U32_7738, hoisted__Str_7739, &_va_Array_227_ek);
        U32 hoisted__U32_7740 = 4;
        Array__Str_set(_va_Array_227, hoisted__U32_7740, &_til_str_lits[71], &_va_Array_227_ek);
        panic(_va_Array_227, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7754 = Str_neq(a, b);
    if (hoisted__Bool_7754) {
        U32 hoisted__U32_7743 = 5;
        Array__Str *_va_Array_228 = Array__Str_new(hoisted__U32_7743);
        I64 _va_Array_228_ek = 0;
        U32 hoisted__U32_7744 = 0;
        Array__Str_set(_va_Array_228, hoisted__U32_7744, &_til_str_lits[69], &_va_Array_228_ek);
        U32 hoisted__U32_7746 = 1;
        Str *hoisted__Str_7747 = Str_to_str(a);
        Array__Str_set(_va_Array_228, hoisted__U32_7746, hoisted__Str_7747, &_va_Array_228_ek);
        U32 hoisted__U32_7748 = 2;
        Array__Str_set(_va_Array_228, hoisted__U32_7748, &_til_str_lits[70], &_va_Array_228_ek);
        U32 hoisted__U32_7750 = 3;
        Str *hoisted__Str_7751 = Str_to_str(b);
        Array__Str_set(_va_Array_228, hoisted__U32_7750, hoisted__Str_7751, &_va_Array_228_ek);
        U32 hoisted__U32_7752 = 4;
        Array__Str_set(_va_Array_228, hoisted__U32_7752, &_til_str_lits[71], &_va_Array_228_ek);
        panic(_va_Array_228, loc);
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
