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
        Array__Str *_fc_Array__Str_326 = parts;
        U32 _fi_USize_326 = 0;
        while (1) {
            USize hoisted__U32_328 = (_fc_Array__Str_326->cap);
            Bool _wcond_Bool_327 = ((Bool)(_fi_USize_326 < hoisted__U32_328));
            if (_wcond_Bool_327) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_326->data) + (((U32)(_fi_USize_326 * 16))))));
            U32 hoisted__U32_329 = 1;
            U32 hoisted__U32_330 = ((U32)(_fi_USize_326 + hoisted__U32_329));
            _fi_USize_326 = hoisted__U32_330;
            USize hoisted__U32_331 = (s->count);
            U32 hoisted__U32_332 = ((U32)(total + hoisted__U32_331));
            total = hoisted__U32_332;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_333 = parts;
        U32 _fi_USize_333 = 0;
        while (1) {
            USize hoisted__U32_335 = (_fc_Array__Str_333->cap);
            Bool _wcond_Bool_334 = ((Bool)(_fi_USize_333 < hoisted__U32_335));
            if (_wcond_Bool_334) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_333->data) + (((U32)(_fi_USize_333 * 16))))));
            U32 hoisted__U32_336 = 1;
            U32 hoisted__U32_337 = ((U32)(_fi_USize_333 + hoisted__U32_336));
            _fi_USize_333 = hoisted__U32_337;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_364 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_364) {
        Bool hoisted__Bool_362 = 0;
        return hoisted__Bool_362;
    }
    Bool hoisted__Bool_365 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_365) {
        Bool hoisted__Bool_363 = 1;
        return hoisted__Bool_363;
    }
    I32 hoisted__I32_366 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_367 = 0;
    Bool hoisted__Bool_368 = ((Bool)(hoisted__I32_366 == hoisted__I32_367));
    return hoisted__Bool_368;
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_370 = 0;
    Bool hoisted__Bool_371 = ((Bool)(n == hoisted__U32_370));
    if (hoisted__Bool_371) {
        static Str hoisted__Str_369 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_369; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_372 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_372)));
    I32 hoisted__I32_373 = 0;
    U64 hoisted__U64_374 = 1ULL;
    memset(buf, hoisted__I32_373, hoisted__U64_374);
    I64 hoisted__I64_375 = 0;
    Str *hoisted__Str_376 = malloc(sizeof(Str));
    hoisted__Str_376->c_str = buf;
    hoisted__Str_376->count = hoisted__I64_375;
    hoisted__Str_376->cap = n;
    return hoisted__Str_376;
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_387 = 0;
    Bool hoisted__Bool_388 = ((Bool)(s->count == hoisted__U32_387));
    if (hoisted__Bool_388) {
        return;
    }
    Bool hoisted__Bool_389 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_389) {
        U32 hoisted__U32_379 = 1;
        Array__Str *_va_Array_5 = Array__Str_new(hoisted__U32_379);
        I64 _va_Array_5_ek = 0;
        U32 hoisted__U32_380 = 0;
        static Str hoisted__Str_381 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_5, hoisted__U32_380, &hoisted__Str_381, &_va_Array_5_ek);
        static Str hoisted__Str_382 = (Str){.c_str = (void *)"./src/core/str.til:124:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_5, &hoisted__Str_382);
        Str_delete(&hoisted__Str_382, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_390 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_390) {
        U32 hoisted__U32_383 = 1;
        Array__Str *_va_Array_6 = Array__Str_new(hoisted__U32_383);
        I64 _va_Array_6_ek = 0;
        U32 hoisted__U32_384 = 0;
        static Str hoisted__Str_385 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_6, hoisted__U32_384, &hoisted__Str_385, &_va_Array_6_ek);
        static Str hoisted__Str_386 = (Str){.c_str = (void *)"./src/core/str.til:128:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_6, &hoisted__Str_386);
        Str_delete(&hoisted__Str_386, (Bool){0});
    }
    void *hoisted__v_391 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_391, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_392 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_393 = 0;
    U64 hoisted__U64_394 = 1ULL;
    memset(hoisted__v_392, hoisted__I32_393, hoisted__U64_394);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_396 = 0;
    Bool hoisted__Bool_397 = ((Bool)(val->count == hoisted__U32_396));
    if (hoisted__Bool_397) {
        static Str hoisted__Str_395 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_395; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_398 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_398)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_399 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_400 = 0;
    U64 hoisted__U64_401 = 1ULL;
    memset(hoisted__v_399, hoisted__I32_400, hoisted__U64_401);
    Str *hoisted__Str_402 = malloc(sizeof(Str));
    hoisted__Str_402->c_str = new_data;
    hoisted__Str_402->count = val->count;
    hoisted__Str_402->cap = val->count;
    return hoisted__Str_402;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_403 = Str_clone(self);
    return hoisted__Str_403;
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_404 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_404) {
        free(self->c_str);
    }
    Bool hoisted__Bool_405 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_406 = ((Bool)((call_free) && (hoisted__Bool_405)));
    if (hoisted__Bool_406) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_790 = Str_eq(a, b);
    Bool hoisted__Bool_791 = ((Bool)(!(hoisted__Bool_790)));
    return hoisted__Bool_791;
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_928 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_929 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_929->data = hoisted__v_928;
    hoisted__Array__Str_929->cap = cap;
    return hoisted__Array__Str_929;
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_938 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Str_delete(hoisted__Str_938, 0);
    Str *hoisted__Str_939 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    adopt__Str(hoisted__Str_939, val);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_941 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_941) {
        I64 hoisted__I64_940 = 1;
        *_err_kind = hoisted__I64_940;
    }
    I64 hoisted__I64_942 = 0;
    Bool hoisted__Bool_943 = ((Bool)(DEREF(_err_kind) == hoisted__I64_942));
    if (hoisted__Bool_943) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_944 = self->cap;
        U32 _rc_U32_944 = 0;
        Bool hoisted__Bool_953 = ((Bool)(_rc_U32_944 <= _re_U32_944));
        if (hoisted__Bool_953) {
            while (1) {
                Bool _wcond_Bool_945 = ((Bool)(_rc_U32_944 < _re_U32_944));
                if (_wcond_Bool_945) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_944);
                (++_rc_U32_944);
                U32 hoisted__U32_946 = 16;
                U32 hoisted__U32_947 = ((U32)(i * hoisted__U32_946));
                Str *hoisted__Str_948 = ((void *)((U8 *)(self->data) + (hoisted__U32_947)));
                Str_delete(hoisted__Str_948, 0);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_949 = ((Bool)(_rc_U32_944 > _re_U32_944));
                if (_wcond_Bool_949) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_944);
                (--_rc_U32_944);
                U32 hoisted__U32_950 = 16;
                U32 hoisted__U32_951 = ((U32)(i * hoisted__U32_950));
                Str *hoisted__Str_952 = ((void *)((U8 *)(self->data) + (hoisted__U32_951)));
                Str_delete(hoisted__Str_952, 0);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1008 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_1008)));
    {
        U32 _re_U32_994 = self->cap;
        U32 _rc_U32_994 = 0;
        Bool hoisted__Bool_1007 = ((Bool)(_rc_U32_994 <= _re_U32_994));
        if (hoisted__Bool_1007) {
            while (1) {
                Bool _wcond_Bool_995 = ((Bool)(_rc_U32_994 < _re_U32_994));
                if (_wcond_Bool_995) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_994);
                (++_rc_U32_994);
                U32 hoisted__U32_996 = 16;
                U32 hoisted__U32_997 = ((U32)(i * hoisted__U32_996));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_997)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_998 = 16;
                U32 hoisted__U32_999 = ((U32)(i * hoisted__U32_998));
                void *hoisted__v_1000 = ((void *)((U8 *)(new_data) + (hoisted__U32_999)));
                adopt__Str(hoisted__v_1000, cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1001 = ((Bool)(_rc_U32_994 > _re_U32_994));
                if (_wcond_Bool_1001) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_994);
                (--_rc_U32_994);
                U32 hoisted__U32_1002 = 16;
                U32 hoisted__U32_1003 = ((U32)(i * hoisted__U32_1002));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_1003)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1004 = 16;
                U32 hoisted__U32_1005 = ((U32)(i * hoisted__U32_1004));
                void *hoisted__v_1006 = ((void *)((U8 *)(new_data) + (hoisted__U32_1005)));
                adopt__Str(hoisted__v_1006, cloned);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1009 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1009->data = new_data;
    hoisted__Array__Str_1009->cap = self->cap;
    return hoisted__Array__Str_1009;
}

void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_1253 = 16;
    memcpy(dest, src, hoisted__U32_1253);
    if ((src)->cap != TIL_CAP_LIT) { free(src); };
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1626 = U64_to_str_ext(val);
    return hoisted__Str_1626;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_1987 = 0;
    Bool hoisted__Bool_1988 = ((Bool)(val < hoisted__I64_1987));
    if (hoisted__Bool_1988) {
        U64 hoisted__U64_1979 = 0ULL;
        U64 hoisted__U64_1980 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_1979 - hoisted__U64_1980));
        U32 hoisted__U32_1981 = 2;
        Array__Str *_va_Array_43 = Array__Str_new(hoisted__U32_1981);
        I64 _va_Array_43_ek = 0;
        U32 hoisted__U32_1982 = 0;
        static Str hoisted__Str_1983 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_43, hoisted__U32_1982, &hoisted__Str_1983, &_va_Array_43_ek);
        U32 hoisted__U32_1984 = 1;
        Str *hoisted__Str_1985 = U64_to_str(mag);
        Array__Str_set(_va_Array_43, hoisted__U32_1984, hoisted__Str_1985, &_va_Array_43_ek);
        Str *hoisted__Str_1986 = format(_va_Array_43);
        return hoisted__Str_1986;
    }
    U64 hoisted__U64_1989 = (U64)(val);
    Str *hoisted__Str_1990 = U64_to_str(hoisted__U64_1989);
    return hoisted__Str_1990;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6095 = 3;
    Array__Str *_va_Array_170 = Array__Str_new(hoisted__U32_6095);
    I64 _va_Array_170_ek = 0;
    U32 hoisted__U32_6096 = 0;
    Str *hoisted__Str_6097 = Str_clone(loc);
    Array__Str_set(_va_Array_170, hoisted__U32_6096, hoisted__Str_6097, &_va_Array_170_ek);
    U32 hoisted__U32_6098 = 1;
    Array__Str_set(_va_Array_170, hoisted__U32_6098, &_til_str_lits[0], &_va_Array_170_ek);
    Array__Str *hoisted__Array__Str_6100 = Array__Str_clone(parts);
    U32 hoisted__U32_6101 = 2;
    Str *hoisted__Str_6102 = format(hoisted__Array__Str_6100);
    Array__Str_set(_va_Array_170, hoisted__U32_6101, hoisted__Str_6102, &_va_Array_170_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_170);
    I64 hoisted__I64_6103 = 1;
    exit(hoisted__I64_6103);
}

__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc) {
    USize hoisted__U32_6125 = (parts->cap);
    U32 hoisted__U32_6126 = 0;
    Bool hoisted__Bool_6127 = ((Bool)(hoisted__U32_6125 == hoisted__U32_6126));
    if (hoisted__Bool_6127) {
        U32 hoisted__U32_6116 = 1;
        Array__Str *_va_Array_173 = Array__Str_new(hoisted__U32_6116);
        I64 _va_Array_173_ek = 0;
        U32 hoisted__U32_6117 = 0;
        Array__Str_set(_va_Array_173, hoisted__U32_6117, &_til_str_lits[1], &_va_Array_173_ek);
        panic(_va_Array_173, loc);
    } else {
        U32 hoisted__U32_6119 = 2;
        Array__Str *_va_Array_174 = Array__Str_new(hoisted__U32_6119);
        I64 _va_Array_174_ek = 0;
        U32 hoisted__U32_6120 = 0;
        Array__Str_set(_va_Array_174, hoisted__U32_6120, &_til_str_lits[2], &_va_Array_174_ek);
        Array__Str *hoisted__Array__Str_6122 = Array__Str_clone(parts);
        U32 hoisted__U32_6123 = 1;
        Str *hoisted__Str_6124 = format(hoisted__Array__Str_6122);
        Array__Str_set(_va_Array_174, hoisted__U32_6123, hoisted__Str_6124, &_va_Array_174_ek);
        panic(_va_Array_174, loc);
    }
    Array__Str_delete(parts, 1);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6131 = ((Bool)(!(cond)));
    if (hoisted__Bool_6131) {
        U32 hoisted__U32_6128 = 1;
        Array__Str *_va_Array_175 = Array__Str_new(hoisted__U32_6128);
        I64 _va_Array_175_ek = 0;
        U32 hoisted__U32_6129 = 0;
        Array__Str_set(_va_Array_175, hoisted__U32_6129, &_til_str_lits[3], &_va_Array_175_ek);
        panic(_va_Array_175, loc);
    }
}

void expect(Bool cond, Array__Str * parts, Str * loc) {
    Bool hoisted__Bool_6138 = ((Bool)(!(cond)));
    if (hoisted__Bool_6138) {
        U32 hoisted__U32_6132 = 2;
        Array__Str *_va_Array_176 = Array__Str_new(hoisted__U32_6132);
        I64 _va_Array_176_ek = 0;
        U32 hoisted__U32_6133 = 0;
        Array__Str_set(_va_Array_176, hoisted__U32_6133, &_til_str_lits[4], &_va_Array_176_ek);
        Array__Str *hoisted__Array__Str_6135 = Array__Str_clone(parts);
        U32 hoisted__U32_6136 = 1;
        Str *hoisted__Str_6137 = format(hoisted__Array__Str_6135);
        Array__Str_set(_va_Array_176, hoisted__U32_6136, hoisted__Str_6137, &_va_Array_176_ek);
        panic(_va_Array_176, loc);
    }
    Array__Str_delete(parts, 1);
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6139 = parts;
        U32 _fi_USize_6139 = 0;
        while (1) {
            USize hoisted__U32_6141 = (_fc_Array__Str_6139->cap);
            Bool _wcond_Bool_6140 = ((Bool)(_fi_USize_6139 < hoisted__U32_6141));
            if (_wcond_Bool_6140) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_6139->data) + (((U32)(_fi_USize_6139 * 16))))));
            U32 hoisted__U32_6142 = 1;
            U32 hoisted__U32_6143 = ((U32)(_fi_USize_6139 + hoisted__U32_6142));
            _fi_USize_6139 = hoisted__U32_6143;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void adopt_from(void * dest, void * src, UPtr size) {
    memcpy(dest, src, size);
    I32 hoisted__I32_6149 = 0;
    memset(src, hoisted__I32_6149, size);
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6212 = 3;
    assert_eq__I64(result, hoisted__I64_6212, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6220 = 15;
    assert_eq__I64(result, hoisted__I64_6220, &_til_str_lits[6]);
    Str_delete(&_til_str_lits[6], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6228 = 26;
    assert_eq__I64(result, hoisted__I64_6228, &_til_str_lits[7]);
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
    I64 hoisted__I64_6297 = 106;
    assert_eq__I64(d3, hoisted__I64_6297, &_til_str_lits[17]);
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
    I64 hoisted__I64_6790 = 8;
    assert_eq__I64(result, hoisted__I64_6790, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_6794 = 1;
    assert(hoisted__Bool_6794, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
    Bool hoisted__Bool_6798 = 1;
    assert(hoisted__Bool_6798, &_til_str_lits[22]);
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
    I64 hoisted__I64_6858 = 42;
    assert_eq__I64(v.x, hoisted__I64_6858, &_til_str_lits[27]);
    Str_delete(&_til_str_lits[27], (Bool){0});
    I64 hoisted__I64_6860 = 99;
    assert_eq__I64(v.y, hoisted__I64_6860, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    CfVec2_delete(&v, 0);
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_6864 = 10;
    assert_eq__I64(p.x, hoisted__I64_6864, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    I64 hoisted__I64_6866 = 20;
    assert_eq__I64(p.y, hoisted__I64_6866, &_til_str_lits[30]);
    Str_delete(&_til_str_lits[30], (Bool){0});
    CfVec2_delete(&p, 0);
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_6915 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_6915, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    I64 hoisted__I64_6917 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_6917, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_6919 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_6919, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_6921 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6921, &_til_str_lits[34]);
    Str_delete(&_til_str_lits[34], (Bool){0});
    CfRect_delete(&r, 0);
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_6977 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_6977, &_til_str_lits[35], &_til_str_lits[36]);
    Str_delete(hoisted__Str_6977, 1);
    Str_delete(&_til_str_lits[35], (Bool){0});
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str *hoisted__Str_6980 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_6980, &_til_str_lits[37], &_til_str_lits[38]);
    Str_delete(hoisted__Str_6980, 1);
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str *hoisted__Str_6983 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_6983, &_til_str_lits[39], &_til_str_lits[40]);
    Str_delete(hoisted__Str_6983, 1);
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str_delete(&_til_str_lits[40], (Bool){0});
    CfVec3f_delete(&v, 0);
}

Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_6986 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_6986;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7033 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_7033, &_til_str_lits[41]);
    Str_delete(&_til_str_lits[41], (Bool){0});
    Bool hoisted__Bool_7035 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_7036 = ((Bool)(!(hoisted__Bool_7035)));
    assert(hoisted__Bool_7036, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7053 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_7053) {
        I64 *hoisted__I64_7051 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        I64_delete(hoisted__I64_7051, 0);
    }
    Bool hoisted__Bool_7054 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_7054) {
        Str *hoisted__Str_7052 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Str_delete(hoisted__Str_7052, 0);
    }
    if (call_free) {
        free(self);
    }
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7116 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7116, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
    Bool hoisted__Bool_7118 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7119 = ((Bool)(!(hoisted__Bool_7118)));
    assert(hoisted__Bool_7119, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7121 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_7121, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Bool hoisted__Bool_7123 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_7124 = ((Bool)(!(hoisted__Bool_7123)));
    assert(hoisted__Bool_7124, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7128 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7128, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
    Bool hoisted__Bool_7130 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7131 = ((Bool)(!(hoisted__Bool_7130)));
    assert(hoisted__Bool_7131, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Token_delete(t, 1);
}

void test_const_and_or_fold(void) {
    U32 hoisted__U32_7139 = 1;
    Array__Str *_va_Array_213 = Array__Str_new(hoisted__U32_7139);
    I64 _va_Array_213_ek = 0;
    U32 hoisted__U32_7140 = 0;
    Array__Str_set(_va_Array_213, hoisted__U32_7140, &_til_str_lits[49], &_va_Array_213_ek);
    Bool hoisted__Bool_7142 = 1;
    expect(hoisted__Bool_7142, _va_Array_213, &_til_str_lits[50]);
    Str_delete(&_til_str_lits[50], (Bool){0});
    U32 hoisted__U32_7144 = 1;
    Array__Str *_va_Array_214 = Array__Str_new(hoisted__U32_7144);
    I64 _va_Array_214_ek = 0;
    U32 hoisted__U32_7145 = 0;
    Array__Str_set(_va_Array_214, hoisted__U32_7145, &_til_str_lits[51], &_va_Array_214_ek);
    Bool hoisted__Bool_7148 = 1;
    expect(hoisted__Bool_7148, _va_Array_214, &_til_str_lits[52]);
    Str_delete(&_til_str_lits[52], (Bool){0});
    U32 hoisted__U32_7150 = 1;
    Array__Str *_va_Array_215 = Array__Str_new(hoisted__U32_7150);
    I64 _va_Array_215_ek = 0;
    U32 hoisted__U32_7151 = 0;
    Array__Str_set(_va_Array_215, hoisted__U32_7151, &_til_str_lits[53], &_va_Array_215_ek);
    Bool hoisted__Bool_7153 = 1;
    expect(hoisted__Bool_7153, _va_Array_215, &_til_str_lits[54]);
    Str_delete(&_til_str_lits[54], (Bool){0});
    U32 hoisted__U32_7155 = 1;
    Array__Str *_va_Array_216 = Array__Str_new(hoisted__U32_7155);
    I64 _va_Array_216_ek = 0;
    U32 hoisted__U32_7156 = 0;
    Array__Str_set(_va_Array_216, hoisted__U32_7156, &_til_str_lits[55], &_va_Array_216_ek);
    Bool hoisted__Bool_7159 = 1;
    expect(hoisted__Bool_7159, _va_Array_216, &_til_str_lits[56]);
    Str_delete(&_til_str_lits[56], (Bool){0});
    U32 hoisted__U32_7161 = 1;
    Array__Str *_va_Array_217 = Array__Str_new(hoisted__U32_7161);
    I64 _va_Array_217_ek = 0;
    U32 hoisted__U32_7162 = 0;
    Array__Str_set(_va_Array_217, hoisted__U32_7162, &_til_str_lits[57], &_va_Array_217_ek);
    Bool hoisted__Bool_7164 = 1;
    expect(hoisted__Bool_7164, _va_Array_217, &_til_str_lits[58]);
    Str_delete(&_til_str_lits[58], (Bool){0});
    U32 hoisted__U32_7166 = 1;
    Array__Str *_va_Array_218 = Array__Str_new(hoisted__U32_7166);
    I64 _va_Array_218_ek = 0;
    U32 hoisted__U32_7167 = 0;
    Array__Str_set(_va_Array_218, hoisted__U32_7167, &_til_str_lits[59], &_va_Array_218_ek);
    Bool hoisted__Bool_7170 = 1;
    expect(hoisted__Bool_7170, _va_Array_218, &_til_str_lits[60]);
    Str_delete(&_til_str_lits[60], (Bool){0});
    U32 hoisted__U32_7172 = 1;
    Array__Str *_va_Array_219 = Array__Str_new(hoisted__U32_7172);
    I64 _va_Array_219_ek = 0;
    U32 hoisted__U32_7173 = 0;
    Array__Str_set(_va_Array_219, hoisted__U32_7173, &_til_str_lits[61], &_va_Array_219_ek);
    Bool hoisted__Bool_7175 = 1;
    expect(hoisted__Bool_7175, _va_Array_219, &_til_str_lits[62]);
    Str_delete(&_til_str_lits[62], (Bool){0});
    U32 hoisted__U32_7177 = 1;
    Array__Str *_va_Array_220 = Array__Str_new(hoisted__U32_7177);
    I64 _va_Array_220_ek = 0;
    U32 hoisted__U32_7178 = 0;
    Array__Str_set(_va_Array_220, hoisted__U32_7178, &_til_str_lits[63], &_va_Array_220_ek);
    Bool hoisted__Bool_7181 = 1;
    expect(hoisted__Bool_7181, _va_Array_220, &_til_str_lits[64]);
    Str_delete(&_til_str_lits[64], (Bool){0});
    U32 hoisted__U32_7183 = 1;
    Array__Str *_va_Array_221 = Array__Str_new(hoisted__U32_7183);
    I64 _va_Array_221_ek = 0;
    U32 hoisted__U32_7184 = 0;
    Array__Str_set(_va_Array_221, hoisted__U32_7184, &_til_str_lits[65], &_va_Array_221_ek);
    Bool hoisted__Bool_7186 = 1;
    expect(hoisted__Bool_7186, _va_Array_221, &_til_str_lits[66]);
    Str_delete(&_til_str_lits[66], (Bool){0});
    Bool _m_Bool_7133 = 0;
    {
        Bool hoisted__Bool_7138 = 0;
        if (hoisted__Bool_7138) {
            Bool hoisted__Bool_7135 = 1;
            _m_Bool_7133 = hoisted__Bool_7135;
        } else {
            Bool hoisted__Bool_7136 = 1;
            _m_Bool_7133 = hoisted__Bool_7136;
        }
    }
    U32 hoisted__U32_7188 = 1;
    Array__Str *_va_Array_222 = Array__Str_new(hoisted__U32_7188);
    I64 _va_Array_222_ek = 0;
    U32 hoisted__U32_7189 = 0;
    Array__Str_set(_va_Array_222, hoisted__U32_7189, &_til_str_lits[67], &_va_Array_222_ek);
    expect(_m_Bool_7133, _va_Array_222, &_til_str_lits[68]);
    Str_delete(&_til_str_lits[68], (Bool){0});
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7528 = ((Bool)(a != b));
    if (hoisted__Bool_7528) {
        U32 hoisted__U32_7517 = 5;
        Array__Str *_va_Array_227 = Array__Str_new(hoisted__U32_7517);
        I64 _va_Array_227_ek = 0;
        U32 hoisted__U32_7518 = 0;
        Array__Str_set(_va_Array_227, hoisted__U32_7518, &_til_str_lits[69], &_va_Array_227_ek);
        U32 hoisted__U32_7520 = 1;
        Str *hoisted__Str_7521 = I64_to_str(a);
        Array__Str_set(_va_Array_227, hoisted__U32_7520, hoisted__Str_7521, &_va_Array_227_ek);
        U32 hoisted__U32_7522 = 2;
        Array__Str_set(_va_Array_227, hoisted__U32_7522, &_til_str_lits[70], &_va_Array_227_ek);
        U32 hoisted__U32_7524 = 3;
        Str *hoisted__Str_7525 = I64_to_str(b);
        Array__Str_set(_va_Array_227, hoisted__U32_7524, hoisted__Str_7525, &_va_Array_227_ek);
        U32 hoisted__U32_7526 = 4;
        Array__Str_set(_va_Array_227, hoisted__U32_7526, &_til_str_lits[71], &_va_Array_227_ek);
        panic(_va_Array_227, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7540 = Str_neq(a, b);
    if (hoisted__Bool_7540) {
        U32 hoisted__U32_7529 = 5;
        Array__Str *_va_Array_228 = Array__Str_new(hoisted__U32_7529);
        I64 _va_Array_228_ek = 0;
        U32 hoisted__U32_7530 = 0;
        Array__Str_set(_va_Array_228, hoisted__U32_7530, &_til_str_lits[69], &_va_Array_228_ek);
        U32 hoisted__U32_7532 = 1;
        Str *hoisted__Str_7533 = Str_to_str(a);
        Array__Str_set(_va_Array_228, hoisted__U32_7532, hoisted__Str_7533, &_va_Array_228_ek);
        U32 hoisted__U32_7534 = 2;
        Array__Str_set(_va_Array_228, hoisted__U32_7534, &_til_str_lits[70], &_va_Array_228_ek);
        U32 hoisted__U32_7536 = 3;
        Str *hoisted__Str_7537 = Str_to_str(b);
        Array__Str_set(_va_Array_228, hoisted__U32_7536, hoisted__Str_7537, &_va_Array_228_ek);
        U32 hoisted__U32_7538 = 4;
        Array__Str_set(_va_Array_228, hoisted__U32_7538, &_til_str_lits[71], &_va_Array_228_ek);
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
