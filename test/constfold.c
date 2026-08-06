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
        Array__Str *_fc_Array__Str_352 = parts;
        U32 _fi_USize_352 = 0;
        while (1) {
            USize hoisted__U32_354 = (_fc_Array__Str_352->cap);
            Bool _wcond_Bool_353 = ((Bool)(_fi_USize_352 < hoisted__U32_354));
            if (_wcond_Bool_353) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_352->data) + (((U32)(_fi_USize_352 * 16))))));
            U32 hoisted__U32_355 = 1;
            U32 hoisted__U32_356 = ((U32)(_fi_USize_352 + hoisted__U32_355));
            _fi_USize_352 = hoisted__U32_356;
            USize hoisted__U32_357 = (s->count);
            U32 hoisted__U32_358 = ((U32)(total + hoisted__U32_357));
            total = hoisted__U32_358;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_359 = parts;
        U32 _fi_USize_359 = 0;
        while (1) {
            USize hoisted__U32_361 = (_fc_Array__Str_359->cap);
            Bool _wcond_Bool_360 = ((Bool)(_fi_USize_359 < hoisted__U32_361));
            if (_wcond_Bool_360) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_359->data) + (((U32)(_fi_USize_359 * 16))))));
            U32 hoisted__U32_362 = 1;
            U32 hoisted__U32_363 = ((U32)(_fi_USize_359 + hoisted__U32_362));
            _fi_USize_359 = hoisted__U32_363;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
    __builtin_unreachable();
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_390 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_390) {
        Bool hoisted__Bool_388 = 0;
        return hoisted__Bool_388;
    }
    Bool hoisted__Bool_391 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_391) {
        Bool hoisted__Bool_389 = 1;
        return hoisted__Bool_389;
    }
    I32 hoisted__I32_392 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_393 = 0;
    Bool hoisted__Bool_394 = ((Bool)(hoisted__I32_392 == hoisted__I32_393));
    return hoisted__Bool_394;
    __builtin_unreachable();
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_396 = 0;
    Bool hoisted__Bool_397 = ((Bool)(n == hoisted__U32_396));
    if (hoisted__Bool_397) {
        static Str hoisted__Str_395 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_395; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_398 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_398)));
    I32 hoisted__I32_399 = 0;
    U64 hoisted__U64_400 = 1ULL;
    memset(buf, hoisted__I32_399, hoisted__U64_400);
    I64 hoisted__I64_401 = 0;
    Str *hoisted__Str_402 = malloc(sizeof(Str));
    hoisted__Str_402->c_str = buf;
    hoisted__Str_402->count = hoisted__I64_401;
    hoisted__Str_402->cap = n;
    return hoisted__Str_402;
    __builtin_unreachable();
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_413 = 0;
    Bool hoisted__Bool_414 = ((Bool)(s->count == hoisted__U32_413));
    if (hoisted__Bool_414) {
        return;
    }
    Bool hoisted__Bool_415 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_415) {
        U32 hoisted__U32_405 = 1;
        Array__Str *_va_Array_5 = Array__Str_new(hoisted__U32_405);
        I64 _va_Array_5_ek = 0;
        U32 hoisted__U32_406 = 0;
        static Str hoisted__Str_407 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_5, hoisted__U32_406, &hoisted__Str_407, &_va_Array_5_ek);
        static Str hoisted__Str_408 = (Str){.c_str = (void *)"./src/core/str.til:124:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_5, &hoisted__Str_408);
        Str_delete(&hoisted__Str_408, (Bool){0});
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_416 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_416) {
        U32 hoisted__U32_409 = 1;
        Array__Str *_va_Array_6 = Array__Str_new(hoisted__U32_409);
        I64 _va_Array_6_ek = 0;
        U32 hoisted__U32_410 = 0;
        static Str hoisted__Str_411 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_6, hoisted__U32_410, &hoisted__Str_411, &_va_Array_6_ek);
        static Str hoisted__Str_412 = (Str){.c_str = (void *)"./src/core/str.til:128:13", .count = 25ULL, .cap = TIL_CAP_LIT};
        panic(_va_Array_6, &hoisted__Str_412);
        Str_delete(&hoisted__Str_412, (Bool){0});
    }
    void *hoisted__v_417 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_417, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_418 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_419 = 0;
    U64 hoisted__U64_420 = 1ULL;
    memset(hoisted__v_418, hoisted__I32_419, hoisted__U64_420);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_422 = 0;
    Bool hoisted__Bool_423 = ((Bool)(val->count == hoisted__U32_422));
    if (hoisted__Bool_423) {
        static Str hoisted__Str_421 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT};
        { Str *_r = malloc(sizeof(Str)); *_r = hoisted__Str_421; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_424 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_424)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_425 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_426 = 0;
    U64 hoisted__U64_427 = 1ULL;
    memset(hoisted__v_425, hoisted__I32_426, hoisted__U64_427);
    Str *hoisted__Str_428 = malloc(sizeof(Str));
    hoisted__Str_428->c_str = new_data;
    hoisted__Str_428->count = val->count;
    hoisted__Str_428->cap = val->count;
    return hoisted__Str_428;
    __builtin_unreachable();
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_429 = Str_clone(self);
    return hoisted__Str_429;
    __builtin_unreachable();
}

void Str_delete(Str * self, Bool call_free) {
    Bool hoisted__Bool_430 = ((Bool)(self->cap < CAP_VIEW));
    if (hoisted__Bool_430) {
        free(self->c_str);
    }
    Bool hoisted__Bool_431 = ((Bool)(self->cap != CAP_LIT));
    Bool hoisted__Bool_432 = ((Bool)((call_free) && (hoisted__Bool_431)));
    if (hoisted__Bool_432) {
        if ((self)->cap != TIL_CAP_LIT) { free(self); };
    }
}

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_816 = Str_eq(a, b);
    Bool hoisted__Bool_817 = ((Bool)(!(hoisted__Bool_816)));
    return hoisted__Bool_817;
    __builtin_unreachable();
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_954 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_955 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_955->data = hoisted__v_954;
    hoisted__Array__Str_955->cap = cap;
    return hoisted__Array__Str_955;
    __builtin_unreachable();
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_964 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Bool hoisted__Bool_965 = 0;
    Str_delete(hoisted__Str_964, hoisted__Bool_965);
    Str *hoisted__Str_966 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    adopt__Str(hoisted__Str_966, val);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
    Bool hoisted__Bool_968 = ((Bool)(i >= self->cap));
    if (hoisted__Bool_968) {
        I64 hoisted__I64_967 = 1;
        *_err_kind = hoisted__I64_967;
    }
    I64 hoisted__I64_969 = 0;
    Bool hoisted__Bool_970 = ((Bool)(DEREF(_err_kind) == hoisted__I64_969));
    if (hoisted__Bool_970) {
        Array__Str_unsafe_set(self, i, val);
    } else {
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_971 = self->cap;
        U32 _rc_U32_971 = 0;
        Bool hoisted__Bool_982 = ((Bool)(_rc_U32_971 <= _re_U32_971));
        if (hoisted__Bool_982) {
            while (1) {
                Bool _wcond_Bool_972 = ((Bool)(_rc_U32_971 < _re_U32_971));
                if (_wcond_Bool_972) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_971);
                (++_rc_U32_971);
                U32 hoisted__U32_973 = 16;
                U32 hoisted__U32_974 = ((U32)(i * hoisted__U32_973));
                Str *hoisted__Str_975 = ((void *)((U8 *)(self->data) + (hoisted__U32_974)));
                Bool hoisted__Bool_976 = 0;
                Str_delete(hoisted__Str_975, hoisted__Bool_976);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_977 = ((Bool)(_rc_U32_971 > _re_U32_971));
                if (_wcond_Bool_977) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_971);
                (--_rc_U32_971);
                U32 hoisted__U32_978 = 16;
                U32 hoisted__U32_979 = ((U32)(i * hoisted__U32_978));
                Str *hoisted__Str_980 = ((void *)((U8 *)(self->data) + (hoisted__U32_979)));
                Bool hoisted__Bool_981 = 0;
                Str_delete(hoisted__Str_980, hoisted__Bool_981);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_1037 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_1037)));
    {
        U32 _re_U32_1023 = self->cap;
        U32 _rc_U32_1023 = 0;
        Bool hoisted__Bool_1036 = ((Bool)(_rc_U32_1023 <= _re_U32_1023));
        if (hoisted__Bool_1036) {
            while (1) {
                Bool _wcond_Bool_1024 = ((Bool)(_rc_U32_1023 < _re_U32_1023));
                if (_wcond_Bool_1024) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_1023);
                (++_rc_U32_1023);
                U32 hoisted__U32_1025 = 16;
                U32 hoisted__U32_1026 = ((U32)(i * hoisted__U32_1025));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_1026)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1027 = 16;
                U32 hoisted__U32_1028 = ((U32)(i * hoisted__U32_1027));
                void *hoisted__v_1029 = ((void *)((U8 *)(new_data) + (hoisted__U32_1028)));
                adopt__Str(hoisted__v_1029, cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_1030 = ((Bool)(_rc_U32_1023 > _re_U32_1023));
                if (_wcond_Bool_1030) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_1023);
                (--_rc_U32_1023);
                U32 hoisted__U32_1031 = 16;
                U32 hoisted__U32_1032 = ((U32)(i * hoisted__U32_1031));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_1032)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_1033 = 16;
                U32 hoisted__U32_1034 = ((U32)(i * hoisted__U32_1033));
                void *hoisted__v_1035 = ((void *)((U8 *)(new_data) + (hoisted__U32_1034)));
                adopt__Str(hoisted__v_1035, cloned);
            }
        }
    }
    Array__Str *hoisted__Array__Str_1038 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1038->data = new_data;
    hoisted__Array__Str_1038->cap = self->cap;
    return hoisted__Array__Str_1038;
    __builtin_unreachable();
}

void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_1305 = 16;
    memcpy(dest, src, hoisted__U32_1305);
    if ((src)->cap != TIL_CAP_LIT) { free(src); };
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_1678 = U64_to_str_ext(val);
    return hoisted__Str_1678;
    __builtin_unreachable();
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_2039 = 0;
    Bool hoisted__Bool_2040 = ((Bool)(val < hoisted__I64_2039));
    if (hoisted__Bool_2040) {
        U64 hoisted__U64_2031 = 0ULL;
        U64 hoisted__U64_2032 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_2031 - hoisted__U64_2032));
        U32 hoisted__U32_2033 = 2;
        Array__Str *_va_Array_43 = Array__Str_new(hoisted__U32_2033);
        I64 _va_Array_43_ek = 0;
        U32 hoisted__U32_2034 = 0;
        static Str hoisted__Str_2035 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_43, hoisted__U32_2034, &hoisted__Str_2035, &_va_Array_43_ek);
        U32 hoisted__U32_2036 = 1;
        Str *hoisted__Str_2037 = U64_to_str(mag);
        Array__Str_set(_va_Array_43, hoisted__U32_2036, hoisted__Str_2037, &_va_Array_43_ek);
        Str *hoisted__Str_2038 = format(_va_Array_43);
        return hoisted__Str_2038;
    }
    U64 hoisted__U64_2041 = (U64)(val);
    Str *hoisted__Str_2042 = U64_to_str(hoisted__U64_2041);
    return hoisted__Str_2042;
    __builtin_unreachable();
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_6409 = 3;
    Array__Str *_va_Array_170 = Array__Str_new(hoisted__U32_6409);
    I64 _va_Array_170_ek = 0;
    U32 hoisted__U32_6410 = 0;
    Str *hoisted__Str_6411 = Str_clone(loc);
    Array__Str_set(_va_Array_170, hoisted__U32_6410, hoisted__Str_6411, &_va_Array_170_ek);
    U32 hoisted__U32_6412 = 1;
    Array__Str_set(_va_Array_170, hoisted__U32_6412, &_til_str_lits[0], &_va_Array_170_ek);
    Array__Str *hoisted__Array__Str_6414 = Array__Str_clone(parts);
    U32 hoisted__U32_6415 = 2;
    Str *hoisted__Str_6416 = format(hoisted__Array__Str_6414);
    Array__Str_set(_va_Array_170, hoisted__U32_6415, hoisted__Str_6416, &_va_Array_170_ek);
    Array__Str_delete(parts, 1);
    println(_va_Array_170);
    I64 hoisted__I64_6417 = 1;
    exit(hoisted__I64_6417);
}

__attribute__((noreturn)) void UNREACHABLE(Array__Str * parts, Str * loc) {
    USize hoisted__U32_6439 = (parts->cap);
    U32 hoisted__U32_6440 = 0;
    Bool hoisted__Bool_6441 = ((Bool)(hoisted__U32_6439 == hoisted__U32_6440));
    if (hoisted__Bool_6441) {
        U32 hoisted__U32_6430 = 1;
        Array__Str *_va_Array_173 = Array__Str_new(hoisted__U32_6430);
        I64 _va_Array_173_ek = 0;
        U32 hoisted__U32_6431 = 0;
        Array__Str_set(_va_Array_173, hoisted__U32_6431, &_til_str_lits[1], &_va_Array_173_ek);
        panic(_va_Array_173, loc);
    } else {
        U32 hoisted__U32_6433 = 2;
        Array__Str *_va_Array_174 = Array__Str_new(hoisted__U32_6433);
        I64 _va_Array_174_ek = 0;
        U32 hoisted__U32_6434 = 0;
        Array__Str_set(_va_Array_174, hoisted__U32_6434, &_til_str_lits[2], &_va_Array_174_ek);
        Array__Str *hoisted__Array__Str_6436 = Array__Str_clone(parts);
        U32 hoisted__U32_6437 = 1;
        Str *hoisted__Str_6438 = format(hoisted__Array__Str_6436);
        Array__Str_set(_va_Array_174, hoisted__U32_6437, hoisted__Str_6438, &_va_Array_174_ek);
        panic(_va_Array_174, loc);
    }
    Array__Str_delete(parts, 1);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_6445 = ((Bool)(!(cond)));
    if (hoisted__Bool_6445) {
        U32 hoisted__U32_6442 = 1;
        Array__Str *_va_Array_175 = Array__Str_new(hoisted__U32_6442);
        I64 _va_Array_175_ek = 0;
        U32 hoisted__U32_6443 = 0;
        Array__Str_set(_va_Array_175, hoisted__U32_6443, &_til_str_lits[3], &_va_Array_175_ek);
        panic(_va_Array_175, loc);
    }
}

void expect(Bool cond, Array__Str * parts, Str * loc) {
    Bool hoisted__Bool_6452 = ((Bool)(!(cond)));
    if (hoisted__Bool_6452) {
        U32 hoisted__U32_6446 = 2;
        Array__Str *_va_Array_176 = Array__Str_new(hoisted__U32_6446);
        I64 _va_Array_176_ek = 0;
        U32 hoisted__U32_6447 = 0;
        Array__Str_set(_va_Array_176, hoisted__U32_6447, &_til_str_lits[4], &_va_Array_176_ek);
        Array__Str *hoisted__Array__Str_6449 = Array__Str_clone(parts);
        U32 hoisted__U32_6450 = 1;
        Str *hoisted__Str_6451 = format(hoisted__Array__Str_6449);
        Array__Str_set(_va_Array_176, hoisted__U32_6450, hoisted__Str_6451, &_va_Array_176_ek);
        panic(_va_Array_176, loc);
    }
    Array__Str_delete(parts, 1);
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_6453 = parts;
        U32 _fi_USize_6453 = 0;
        while (1) {
            USize hoisted__U32_6455 = (_fc_Array__Str_6453->cap);
            Bool _wcond_Bool_6454 = ((Bool)(_fi_USize_6453 < hoisted__U32_6455));
            if (_wcond_Bool_6454) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_6453->data) + (((U32)(_fi_USize_6453 * 16))))));
            U32 hoisted__U32_6456 = 1;
            U32 hoisted__U32_6457 = ((U32)(_fi_USize_6453 + hoisted__U32_6456));
            _fi_USize_6453 = hoisted__U32_6457;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_6525 = 3;
    assert_eq__I64(result, hoisted__I64_6525, &_til_str_lits[5]);
    Str_delete(&_til_str_lits[5], (Bool){0});
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6533 = 15;
    assert_eq__I64(result, hoisted__I64_6533, &_til_str_lits[6]);
    Str_delete(&_til_str_lits[6], (Bool){0});
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6541 = 26;
    assert_eq__I64(result, hoisted__I64_6541, &_til_str_lits[7]);
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
    I64 hoisted__I64_6610 = 106;
    assert_eq__I64(d3, hoisted__I64_6610, &_til_str_lits[17]);
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
    I64 hoisted__I64_7103 = 8;
    assert_eq__I64(result, hoisted__I64_7103, &_til_str_lits[20]);
    Str_delete(&_til_str_lits[20], (Bool){0});
}

void test_loc_folded(void) {
    Bool hoisted__Bool_7107 = 1;
    assert(hoisted__Bool_7107, &_til_str_lits[21]);
    Str_delete(&_til_str_lits[21], (Bool){0});
    Bool hoisted__Bool_7111 = 1;
    assert(hoisted__Bool_7111, &_til_str_lits[22]);
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
    I64 hoisted__I64_7171 = 42;
    assert_eq__I64(v.x, hoisted__I64_7171, &_til_str_lits[27]);
    Str_delete(&_til_str_lits[27], (Bool){0});
    I64 hoisted__I64_7173 = 99;
    assert_eq__I64(v.y, hoisted__I64_7173, &_til_str_lits[28]);
    Str_delete(&_til_str_lits[28], (Bool){0});
    CfVec2_delete(&v, (Bool){0});
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_7177 = 10;
    assert_eq__I64(p.x, hoisted__I64_7177, &_til_str_lits[29]);
    Str_delete(&_til_str_lits[29], (Bool){0});
    I64 hoisted__I64_7179 = 20;
    assert_eq__I64(p.y, hoisted__I64_7179, &_til_str_lits[30]);
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
    I64 hoisted__I64_7228 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_7228, &_til_str_lits[31]);
    Str_delete(&_til_str_lits[31], (Bool){0});
    I64 hoisted__I64_7230 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_7230, &_til_str_lits[32]);
    Str_delete(&_til_str_lits[32], (Bool){0});
    I64 hoisted__I64_7232 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_7232, &_til_str_lits[33]);
    Str_delete(&_til_str_lits[33], (Bool){0});
    I64 hoisted__I64_7234 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_7234, &_til_str_lits[34]);
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
    Str *hoisted__Str_7290 = F32_to_str(v.x);
    assert_eq__Str(hoisted__Str_7290, &_til_str_lits[35], &_til_str_lits[36]);
    Str_delete(hoisted__Str_7290, 1);
    Str_delete(&_til_str_lits[35], (Bool){0});
    Str_delete(&_til_str_lits[36], (Bool){0});
    Str *hoisted__Str_7293 = F32_to_str(v.y);
    assert_eq__Str(hoisted__Str_7293, &_til_str_lits[37], &_til_str_lits[38]);
    Str_delete(hoisted__Str_7293, 1);
    Str_delete(&_til_str_lits[37], (Bool){0});
    Str_delete(&_til_str_lits[38], (Bool){0});
    Str *hoisted__Str_7296 = F32_to_str(v.z);
    assert_eq__Str(hoisted__Str_7296, &_til_str_lits[39], &_til_str_lits[40]);
    Str_delete(hoisted__Str_7296, 1);
    Str_delete(&_til_str_lits[39], (Bool){0});
    Str_delete(&_til_str_lits[40], (Bool){0});
    CfVec3f_delete(&v, (Bool){0});
}

Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_7299 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_7299;
    __builtin_unreachable();
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_7346 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_7346, &_til_str_lits[41]);
    Str_delete(&_til_str_lits[41], (Bool){0});
    Bool hoisted__Bool_7348 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_7349 = ((Bool)(!(hoisted__Bool_7348)));
    assert(hoisted__Bool_7349, &_til_str_lits[42]);
    Str_delete(&_til_str_lits[42], (Bool){0});
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_7368 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_7368) {
        I64 *hoisted__I64_7364 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7365 = 0;
        I64_delete(hoisted__I64_7364, hoisted__Bool_7365);
    }
    Bool hoisted__Bool_7369 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_7369) {
        Str *hoisted__Str_7366 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Bool hoisted__Bool_7367 = 0;
        Str_delete(hoisted__Str_7366, hoisted__Bool_7367);
    }
    if (call_free) {
        free(self);
    }
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_7431 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7431, &_til_str_lits[43]);
    Str_delete(&_til_str_lits[43], (Bool){0});
    Bool hoisted__Bool_7433 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7434 = ((Bool)(!(hoisted__Bool_7433)));
    assert(hoisted__Bool_7434, &_til_str_lits[44]);
    Str_delete(&_til_str_lits[44], (Bool){0});
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_7436 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_7436, &_til_str_lits[45]);
    Str_delete(&_til_str_lits[45], (Bool){0});
    Bool hoisted__Bool_7438 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_7439 = ((Bool)(!(hoisted__Bool_7438)));
    assert(hoisted__Bool_7439, &_til_str_lits[46]);
    Str_delete(&_til_str_lits[46], (Bool){0});
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_7443 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_7443, &_til_str_lits[47]);
    Str_delete(&_til_str_lits[47], (Bool){0});
    Bool hoisted__Bool_7445 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_7446 = ((Bool)(!(hoisted__Bool_7445)));
    assert(hoisted__Bool_7446, &_til_str_lits[48]);
    Str_delete(&_til_str_lits[48], (Bool){0});
    Token_delete(t, 1);
}

void test_const_and_or_fold(void) {
    U32 hoisted__U32_7454 = 1;
    Array__Str *_va_Array_213 = Array__Str_new(hoisted__U32_7454);
    I64 _va_Array_213_ek = 0;
    U32 hoisted__U32_7455 = 0;
    Array__Str_set(_va_Array_213, hoisted__U32_7455, &_til_str_lits[49], &_va_Array_213_ek);
    Bool hoisted__Bool_7457 = 1;
    expect(hoisted__Bool_7457, _va_Array_213, &_til_str_lits[50]);
    Str_delete(&_til_str_lits[50], (Bool){0});
    U32 hoisted__U32_7459 = 1;
    Array__Str *_va_Array_214 = Array__Str_new(hoisted__U32_7459);
    I64 _va_Array_214_ek = 0;
    U32 hoisted__U32_7460 = 0;
    Array__Str_set(_va_Array_214, hoisted__U32_7460, &_til_str_lits[51], &_va_Array_214_ek);
    Bool hoisted__Bool_7463 = 1;
    expect(hoisted__Bool_7463, _va_Array_214, &_til_str_lits[52]);
    Str_delete(&_til_str_lits[52], (Bool){0});
    U32 hoisted__U32_7465 = 1;
    Array__Str *_va_Array_215 = Array__Str_new(hoisted__U32_7465);
    I64 _va_Array_215_ek = 0;
    U32 hoisted__U32_7466 = 0;
    Array__Str_set(_va_Array_215, hoisted__U32_7466, &_til_str_lits[53], &_va_Array_215_ek);
    Bool hoisted__Bool_7468 = 1;
    expect(hoisted__Bool_7468, _va_Array_215, &_til_str_lits[54]);
    Str_delete(&_til_str_lits[54], (Bool){0});
    U32 hoisted__U32_7470 = 1;
    Array__Str *_va_Array_216 = Array__Str_new(hoisted__U32_7470);
    I64 _va_Array_216_ek = 0;
    U32 hoisted__U32_7471 = 0;
    Array__Str_set(_va_Array_216, hoisted__U32_7471, &_til_str_lits[55], &_va_Array_216_ek);
    Bool hoisted__Bool_7474 = 1;
    expect(hoisted__Bool_7474, _va_Array_216, &_til_str_lits[56]);
    Str_delete(&_til_str_lits[56], (Bool){0});
    U32 hoisted__U32_7476 = 1;
    Array__Str *_va_Array_217 = Array__Str_new(hoisted__U32_7476);
    I64 _va_Array_217_ek = 0;
    U32 hoisted__U32_7477 = 0;
    Array__Str_set(_va_Array_217, hoisted__U32_7477, &_til_str_lits[57], &_va_Array_217_ek);
    Bool hoisted__Bool_7479 = 1;
    expect(hoisted__Bool_7479, _va_Array_217, &_til_str_lits[58]);
    Str_delete(&_til_str_lits[58], (Bool){0});
    U32 hoisted__U32_7481 = 1;
    Array__Str *_va_Array_218 = Array__Str_new(hoisted__U32_7481);
    I64 _va_Array_218_ek = 0;
    U32 hoisted__U32_7482 = 0;
    Array__Str_set(_va_Array_218, hoisted__U32_7482, &_til_str_lits[59], &_va_Array_218_ek);
    Bool hoisted__Bool_7485 = 1;
    expect(hoisted__Bool_7485, _va_Array_218, &_til_str_lits[60]);
    Str_delete(&_til_str_lits[60], (Bool){0});
    U32 hoisted__U32_7487 = 1;
    Array__Str *_va_Array_219 = Array__Str_new(hoisted__U32_7487);
    I64 _va_Array_219_ek = 0;
    U32 hoisted__U32_7488 = 0;
    Array__Str_set(_va_Array_219, hoisted__U32_7488, &_til_str_lits[61], &_va_Array_219_ek);
    Bool hoisted__Bool_7490 = 1;
    expect(hoisted__Bool_7490, _va_Array_219, &_til_str_lits[62]);
    Str_delete(&_til_str_lits[62], (Bool){0});
    U32 hoisted__U32_7492 = 1;
    Array__Str *_va_Array_220 = Array__Str_new(hoisted__U32_7492);
    I64 _va_Array_220_ek = 0;
    U32 hoisted__U32_7493 = 0;
    Array__Str_set(_va_Array_220, hoisted__U32_7493, &_til_str_lits[63], &_va_Array_220_ek);
    Bool hoisted__Bool_7496 = 1;
    expect(hoisted__Bool_7496, _va_Array_220, &_til_str_lits[64]);
    Str_delete(&_til_str_lits[64], (Bool){0});
    U32 hoisted__U32_7498 = 1;
    Array__Str *_va_Array_221 = Array__Str_new(hoisted__U32_7498);
    I64 _va_Array_221_ek = 0;
    U32 hoisted__U32_7499 = 0;
    Array__Str_set(_va_Array_221, hoisted__U32_7499, &_til_str_lits[65], &_va_Array_221_ek);
    Bool hoisted__Bool_7501 = 1;
    expect(hoisted__Bool_7501, _va_Array_221, &_til_str_lits[66]);
    Str_delete(&_til_str_lits[66], (Bool){0});
    Bool _m_Bool_7448 = 0;
    {
        Bool hoisted__Bool_7453 = 0;
        if (hoisted__Bool_7453) {
            Bool hoisted__Bool_7450 = 1;
            _m_Bool_7448 = hoisted__Bool_7450;
        } else {
            Bool hoisted__Bool_7451 = 1;
            _m_Bool_7448 = hoisted__Bool_7451;
        }
    }
    U32 hoisted__U32_7503 = 1;
    Array__Str *_va_Array_222 = Array__Str_new(hoisted__U32_7503);
    I64 _va_Array_222_ek = 0;
    U32 hoisted__U32_7504 = 0;
    Array__Str_set(_va_Array_222, hoisted__U32_7504, &_til_str_lits[67], &_va_Array_222_ek);
    expect(_m_Bool_7448, _va_Array_222, &_til_str_lits[68]);
    Str_delete(&_til_str_lits[68], (Bool){0});
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_7869 = ((Bool)(a != b));
    if (hoisted__Bool_7869) {
        U32 hoisted__U32_7858 = 5;
        Array__Str *_va_Array_227 = Array__Str_new(hoisted__U32_7858);
        I64 _va_Array_227_ek = 0;
        U32 hoisted__U32_7859 = 0;
        Array__Str_set(_va_Array_227, hoisted__U32_7859, &_til_str_lits[69], &_va_Array_227_ek);
        U32 hoisted__U32_7861 = 1;
        Str *hoisted__Str_7862 = I64_to_str(a);
        Array__Str_set(_va_Array_227, hoisted__U32_7861, hoisted__Str_7862, &_va_Array_227_ek);
        U32 hoisted__U32_7863 = 2;
        Array__Str_set(_va_Array_227, hoisted__U32_7863, &_til_str_lits[70], &_va_Array_227_ek);
        U32 hoisted__U32_7865 = 3;
        Str *hoisted__Str_7866 = I64_to_str(b);
        Array__Str_set(_va_Array_227, hoisted__U32_7865, hoisted__Str_7866, &_va_Array_227_ek);
        U32 hoisted__U32_7867 = 4;
        Array__Str_set(_va_Array_227, hoisted__U32_7867, &_til_str_lits[71], &_va_Array_227_ek);
        panic(_va_Array_227, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_7881 = Str_neq(a, b);
    if (hoisted__Bool_7881) {
        U32 hoisted__U32_7870 = 5;
        Array__Str *_va_Array_228 = Array__Str_new(hoisted__U32_7870);
        I64 _va_Array_228_ek = 0;
        U32 hoisted__U32_7871 = 0;
        Array__Str_set(_va_Array_228, hoisted__U32_7871, &_til_str_lits[69], &_va_Array_228_ek);
        U32 hoisted__U32_7873 = 1;
        Str *hoisted__Str_7874 = Str_to_str(a);
        Array__Str_set(_va_Array_228, hoisted__U32_7873, hoisted__Str_7874, &_va_Array_228_ek);
        U32 hoisted__U32_7875 = 2;
        Array__Str_set(_va_Array_228, hoisted__U32_7875, &_til_str_lits[70], &_va_Array_228_ek);
        U32 hoisted__U32_7877 = 3;
        Str *hoisted__Str_7878 = Str_to_str(b);
        Array__Str_set(_va_Array_228, hoisted__U32_7877, hoisted__Str_7878, &_va_Array_228_ek);
        U32 hoisted__U32_7879 = 4;
        Array__Str_set(_va_Array_228, hoisted__U32_7879, &_til_str_lits[71], &_va_Array_228_ek);
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
