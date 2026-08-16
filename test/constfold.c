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
typedef struct Array__Str Array__Str;
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


typedef struct Array__Str {
    U8 *data;
    USize cap;
} Array__Str;










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
void test_mixed_fold(void);
void test_fold_reads_global_const(void);
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

static struct {
    Str h000000001505;
    Str h00000002b5cc;
    Str h15a1180c089b;
    Str h00000b8791fb;
    Str h00017c7b7650;
    Str h44abcb58cde4;
    Str h3fd43551c8c1;
} _til_str_lits = {
    .h000000001505 = (Str){.c_str = (void *)"", .count = 0ULL, .cap = TIL_CAP_LIT},
    .h00000002b5cc = (Str){.c_str = (void *)"'", .count = 1ULL, .cap = TIL_CAP_LIT},
    .h15a1180c089b = (Str){.c_str = (void *)"', found '", .count = 10ULL, .cap = TIL_CAP_LIT},
    .h00000b8791fb = (Str){.c_str = (void *)"3.5", .count = 3ULL, .cap = TIL_CAP_LIT},
    .h00017c7b7650 = (Str){.c_str = (void *)"6.25", .count = 4ULL, .cap = TIL_CAP_LIT},
    .h44abcb58cde4 = (Str){.c_str = (void *)"assert_eq failed: expected '", .count = 28ULL, .cap = TIL_CAP_LIT},
    .h3fd43551c8c1 = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT},
};

/* til source locations: line numbers shift with source edits; the code hunks are above */
static Str hoisted__Str_Str_push_str_3 = (Str){.c_str = (void *)"./src/core/str.til:124:13", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_Str_push_str_7 = (Str){.c_str = (void *)"./src/core/str.til:128:13", .count = 25ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_10 = (Str){.c_str = (void *)"test/constfold.til:281:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_16 = (Str){.c_str = (void *)"test/constfold.til:282:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_21 = (Str){.c_str = (void *)"test/constfold.til:283:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_27 = (Str){.c_str = (void *)"test/constfold.til:284:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_32 = (Str){.c_str = (void *)"test/constfold.til:285:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_38 = (Str){.c_str = (void *)"test/constfold.til:286:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_43 = (Str){.c_str = (void *)"test/constfold.til:287:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_49 = (Str){.c_str = (void *)"test/constfold.til:288:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_54 = (Str){.c_str = (void *)"test/constfold.til:289:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_const_and_or_fold_58 = (Str){.c_str = (void *)"test/constfold.til:290:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_deeply_nested_7 = (Str){.c_str = (void *)"test/constfold.til:27:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_fold_1 = (Str){.c_str = (void *)"test/constfold.til:240:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_fold_4 = (Str){.c_str = (void *)"test/constfold.til:241:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_payload_fold_2 = (Str){.c_str = (void *)"test/constfold.til:249:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_payload_fold_5 = (Str){.c_str = (void *)"test/constfold.til:250:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_payload_return_fold_2 = (Str){.c_str = (void *)"test/constfold.til:271:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_payload_return_fold_5 = (Str){.c_str = (void *)"test/constfold.til:272:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_return_fold_1 = (Str){.c_str = (void *)"test/constfold.til:259:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_enum_return_fold_4 = (Str){.c_str = (void *)"test/constfold.til:260:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_fold_f32_4 = (Str){.c_str = (void *)"test/constfold.til:154:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_fold_f32_9 = (Str){.c_str = (void *)"test/constfold.til:156:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_fold_reads_global_const_3 = (Str){.c_str = (void *)"test/constfold.til:315:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_fold_variable_2 = (Str){.c_str = (void *)"test/constfold.til:137:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_loc_folded_3 = (Str){.c_str = (void *)"test/constfold.til:142:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_loc_folded_7 = (Str){.c_str = (void *)"test/constfold.til:143:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_lolalalo_8 = (Str){.c_str = (void *)"test/constfold.til:129:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_lolalalo_9 = (Str){.c_str = (void *)"test/constfold.til:130:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_mixed_fold_4 = (Str){.c_str = (void *)"test/constfold.til:297:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_nested_arithmetic_7 = (Str){.c_str = (void *)"test/constfold.til:21:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_simple_add_3 = (Str){.c_str = (void *)"test/constfold.til:15:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_string_concat_3 = (Str){.c_str = (void *)"test/constfold.til:33:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_f32_11 = (Str){.c_str = (void *)"test/constfold.til:230:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_f32_5 = (Str){.c_str = (void *)"test/constfold.til:228:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_f32_8 = (Str){.c_str = (void *)"test/constfold.til:229:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_nested_1 = (Str){.c_str = (void *)"test/constfold.til:202:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_nested_3 = (Str){.c_str = (void *)"test/constfold.til:203:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_nested_5 = (Str){.c_str = (void *)"test/constfold.til:204:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_nested_7 = (Str){.c_str = (void *)"test/constfold.til:205:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_simple_1 = (Str){.c_str = (void *)"test/constfold.til:178:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_simple_3 = (Str){.c_str = (void *)"test/constfold.til:179:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_values_3 = (Str){.c_str = (void *)"test/constfold.til:185:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_struct_fold_values_5 = (Str){.c_str = (void *)"test/constfold.til:186:5", .count = 24ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_direct_fold_12 = (Str){.c_str = (void *)"test/constfold.til:72:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_direct_fold_21 = (Str){.c_str = (void *)"test/constfold.til:74:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_direct_fold_31 = (Str){.c_str = (void *)"test/constfold.til:76:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_fold_3 = (Str){.c_str = (void *)"test/constfold.til:49:5", .count = 23ULL, .cap = TIL_CAP_LIT};
static Str hoisted__Str_test_variadic_fold_8 = (Str){.c_str = (void *)"test/constfold.til:51:5", .count = 23ULL, .cap = TIL_CAP_LIT};

U32 CAP_LIT;
U32 CAP_VIEW;

Str * format(Array__Str * parts) {
    U32 total = 0;
    {
        Array__Str *_fc_Array__Str_0 = parts;
        U32 _fi_USize_0 = 0;
        while (1) {
            USize hoisted__U32_2 = (_fc_Array__Str_0->cap);
            Bool _wcond_Bool_1 = ((Bool)(_fi_USize_0 < hoisted__U32_2));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_0->data) + (((U32)(_fi_USize_0 * 16))))));
            U32 hoisted__U32_3 = 1;
            U32 hoisted__U32_4 = ((U32)(_fi_USize_0 + hoisted__U32_3));
            _fi_USize_0 = hoisted__U32_4;
            USize hoisted__U32_5 = (s->count);
            U32 hoisted__U32_6 = ((U32)(total + hoisted__U32_5));
            total = hoisted__U32_6;
        }
    }
    Str *out = Str_with_capacity(total);
    {
        Array__Str *_fc_Array__Str_7 = parts;
        U32 _fi_USize_7 = 0;
        while (1) {
            USize hoisted__U32_9 = (_fc_Array__Str_7->cap);
            Bool _wcond_Bool_8 = ((Bool)(_fi_USize_7 < hoisted__U32_9));
            if (_wcond_Bool_8) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_7->data) + (((U32)(_fi_USize_7 * 16))))));
            U32 hoisted__U32_10 = 1;
            U32 hoisted__U32_11 = ((U32)(_fi_USize_7 + hoisted__U32_10));
            _fi_USize_7 = hoisted__U32_11;
            Str_push_str(out, s);
        }
    }
    Array__Str_delete(parts, 1);
    return out;
}

Bool Str_eq(Str * a, Str * b) {
    Bool hoisted__Bool_2 = ((Bool)(a->count != b->count));
    if (hoisted__Bool_2) {
        Bool hoisted__Bool_0 = 0;
        return hoisted__Bool_0;
    }
    Bool hoisted__Bool_3 = ptr_eq(a->c_str, b->c_str);
    if (hoisted__Bool_3) {
        Bool hoisted__Bool_1 = 1;
        return hoisted__Bool_1;
    }
    I32 hoisted__I32_4 = memcmp(a->c_str, b->c_str, a->count);
    I32 hoisted__I32_5 = 0;
    Bool hoisted__Bool_6 = ((Bool)(hoisted__I32_4 == hoisted__I32_5));
    return hoisted__Bool_6;
}

Str * Str_with_capacity(USize n) {
    U32 hoisted__U32_1 = 0;
    Bool hoisted__Bool_2 = ((Bool)(n == hoisted__U32_1));
    if (hoisted__Bool_2) {
        { Str *_r = malloc(sizeof(Str)); *_r = _til_str_lits.h000000001505; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_3 = 1;
    I8 *buf = malloc(((U32)(n + hoisted__U32_3)));
    I32 hoisted__I32_4 = 0;
    U64 hoisted__U64_5 = 1ULL;
    memset(buf, hoisted__I32_4, hoisted__U64_5);
    I64 hoisted__I64_6 = 0;
    Str *hoisted__Str_Str_with_capacity_7 = malloc(sizeof(Str));
    hoisted__Str_Str_with_capacity_7->c_str = buf;
    hoisted__Str_Str_with_capacity_7->count = hoisted__I64_6;
    hoisted__Str_Str_with_capacity_7->cap = n;
    return hoisted__Str_Str_with_capacity_7;
}

void Str_push_str(Str * self, Str * s) {
    U32 hoisted__U32_8 = 0;
    Bool hoisted__Bool_9 = ((Bool)(s->count == hoisted__U32_8));
    if (hoisted__Bool_9) {
        return;
    }
    Bool hoisted__Bool_10 = ((Bool)(self->cap >= CAP_VIEW));
    if (hoisted__Bool_10) {
        U32 hoisted__U32_0 = 1;
        Array__Str *_va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        static Str hoisted__Str_Str_push_str_2 = (Str){.c_str = (void *)"Str.push_str: cannot mutate a string view or literal", .count = 52ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_0, hoisted__U32_1, &hoisted__Str_Str_push_str_2, &_va_Array_0_ek);
        panic(_va_Array_0, &hoisted__Str_Str_push_str_3);
        Str_delete(&hoisted__Str_Str_push_str_3, 0);
    }
    U32 new_len = ((U32)(self->count + s->count));
    Bool hoisted__Bool_11 = ((Bool)(new_len > self->cap));
    if (hoisted__Bool_11) {
        U32 hoisted__U32_4 = 1;
        Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_4);
        I64 _va_Array_1_ek = 0;
        U32 hoisted__U32_5 = 0;
        static Str hoisted__Str_Str_push_str_6 = (Str){.c_str = (void *)"Str.push_str: capacity exceeded", .count = 31ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_1, hoisted__U32_5, &hoisted__Str_Str_push_str_6, &_va_Array_1_ek);
        panic(_va_Array_1, &hoisted__Str_Str_push_str_7);
        Str_delete(&hoisted__Str_Str_push_str_7, 0);
    }
    void *hoisted__v_12 = ((void *)((U8 *)(self->c_str) + (self->count)));
    memcpy(hoisted__v_12, s->c_str, s->count);
    self->count = (new_len);
    void *hoisted__v_13 = ((void *)((U8 *)(self->c_str) + (new_len)));
    I32 hoisted__I32_14 = 0;
    U64 hoisted__U64_15 = 1ULL;
    memset(hoisted__v_13, hoisted__I32_14, hoisted__U64_15);
}

Str * Str_clone(Str * val) {
    U32 hoisted__U32_1 = 0;
    Bool hoisted__Bool_2 = ((Bool)(val->count == hoisted__U32_1));
    if (hoisted__Bool_2) {
        { Str *_r = malloc(sizeof(Str)); *_r = _til_str_lits.h000000001505; if (_r->cap == TIL_CAP_LIT) { _r->cap = TIL_CAP_VIEW; };
        return _r; }
    }
    U32 hoisted__U32_3 = 1;
    I8 *new_data = malloc(((U32)(val->count + hoisted__U32_3)));
    memcpy(new_data, val->c_str, val->count);
    void *hoisted__v_4 = ((void *)((U8 *)(new_data) + (val->count)));
    I32 hoisted__I32_5 = 0;
    U64 hoisted__U64_6 = 1ULL;
    memset(hoisted__v_4, hoisted__I32_5, hoisted__U64_6);
    Str *hoisted__Str_Str_clone_7 = malloc(sizeof(Str));
    hoisted__Str_Str_clone_7->c_str = new_data;
    hoisted__Str_Str_clone_7->count = val->count;
    hoisted__Str_Str_clone_7->cap = val->count;
    return hoisted__Str_Str_clone_7;
}

Str * Str_to_str(Str * self) {
    Str *hoisted__Str_Str_to_str_0 = Str_clone(self);
    return hoisted__Str_Str_to_str_0;
}

void Str_delete(Str * self, Bool call_free) {
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

Bool Str_neq(Str * a, Str * b) {
    Bool hoisted__Bool_0 = Str_eq(a, b);
    Bool hoisted__Bool_1 = ((Bool)(!(hoisted__Bool_0)));
    return hoisted__Bool_1;
}

Array__Str * Array__Str_new(USize cap) {
    void * hoisted__v_0 = calloc(cap, 16);
    Array__Str *hoisted__Array__Str_1 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_1->data = hoisted__v_0;
    hoisted__Array__Str_1->cap = cap;
    return hoisted__Array__Str_1;
}

void Array__Str_unsafe_set(Array__Str * self, USize i, Str * val) {
    Str *hoisted__Str_Array__Str_unsafe_set_0 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    Str_delete(hoisted__Str_Array__Str_unsafe_set_0, 0);
    Str *hoisted__Str_Array__Str_unsafe_set_1 = ((Str *)((void *)((U8 *)(self->data) + (((U32)(i * 16))))));
    adopt__Str(hoisted__Str_Array__Str_unsafe_set_1, val);
}

void Array__Str_set(Array__Str * self, USize i, Str * val, I64 * _err_kind) {
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
        Str_delete(val, 1);
    }
}

void Array__Str_delete(Array__Str * self, Bool call_free) {
    {
        U32 _re_U32_0 = self->cap;
        U32 _rc_U32_0 = 0;
        Bool hoisted__Bool_9 = ((Bool)(_rc_U32_0 <= _re_U32_0));
        if (hoisted__Bool_9) {
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
                Str *hoisted__Str_Array__Str_delete_4 = ((void *)((U8 *)(self->data) + (hoisted__U32_3)));
                Str_delete(hoisted__Str_Array__Str_delete_4, 0);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_5 = ((Bool)(_rc_U32_0 > _re_U32_0));
                if (_wcond_Bool_5) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_0);
                (--_rc_U32_0);
                U32 hoisted__U32_6 = 16;
                U32 hoisted__U32_7 = ((U32)(i * hoisted__U32_6));
                Str *hoisted__Str_Array__Str_delete_8 = ((void *)((U8 *)(self->data) + (hoisted__U32_7)));
                Str_delete(hoisted__Str_Array__Str_delete_8, 0);
            }
        }
    }
    free(self->data);
    if (call_free) {
        free(self);
    }
}

Array__Str * Array__Str_clone(Array__Str * self) {
    U32 hoisted__U32_14 = 16;
    U8 *new_data = malloc(((U32)(self->cap * hoisted__U32_14)));
    {
        U32 _re_U32_0 = self->cap;
        U32 _rc_U32_0 = 0;
        Bool hoisted__Bool_13 = ((Bool)(_rc_U32_0 <= _re_U32_0));
        if (hoisted__Bool_13) {
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
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_3)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_4 = 16;
                U32 hoisted__U32_5 = ((U32)(i * hoisted__U32_4));
                void *hoisted__v_6 = ((void *)((U8 *)(new_data) + (hoisted__U32_5)));
                adopt__Str(hoisted__v_6, cloned);
            }
        } else {
            while (1) {
                Bool _wcond_Bool_7 = ((Bool)(_rc_U32_0 > _re_U32_0));
                if (_wcond_Bool_7) {
                } else {
                    break;
                }
                U32 i = (_rc_U32_0);
                (--_rc_U32_0);
                U32 hoisted__U32_8 = 16;
                U32 hoisted__U32_9 = ((U32)(i * hoisted__U32_8));
                Str *src = ((void *)((U8 *)(self->data) + (hoisted__U32_9)));
                Str *cloned = Str_clone(src);
                U32 hoisted__U32_10 = 16;
                U32 hoisted__U32_11 = ((U32)(i * hoisted__U32_10));
                void *hoisted__v_12 = ((void *)((U8 *)(new_data) + (hoisted__U32_11)));
                adopt__Str(hoisted__v_12, cloned);
            }
        }
    }
    Array__Str *hoisted__Array__Str_15 = malloc(sizeof(Array__Str));
    hoisted__Array__Str_15->data = new_data;
    hoisted__Array__Str_15->cap = self->cap;
    return hoisted__Array__Str_15;
}

void adopt__Str(void * dest, Str * src) {
    U32 hoisted__U32_0 = 16;
    memcpy(dest, src, hoisted__U32_0);
    if ((src)->cap != TIL_CAP_LIT) { free(src); };
}

Str * U64_to_str(U64 val) {
    /* TODO: nested func U64_to_str_ext */
    Str *hoisted__Str_U64_to_str_0 = U64_to_str_ext(val);
    return hoisted__Str_U64_to_str_0;
}

Str * I64_to_str(I64 val) {
    I64 hoisted__I64_8 = 0;
    Bool hoisted__Bool_9 = ((Bool)(val < hoisted__I64_8));
    if (hoisted__Bool_9) {
        U64 hoisted__U64_0 = 0ULL;
        U64 hoisted__U64_1 = (U64)(val);
        U64 mag = ((U64)(hoisted__U64_0 - hoisted__U64_1));
        U32 hoisted__U32_2 = 2;
        Array__Str *_va_Array_0 = Array__Str_new(hoisted__U32_2);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_3 = 0;
        static Str hoisted__Str_I64_to_str_4 = (Str){.c_str = (void *)"-", .count = 1ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_0, hoisted__U32_3, &hoisted__Str_I64_to_str_4, &_va_Array_0_ek);
        U32 hoisted__U32_5 = 1;
        Str *hoisted__Str_I64_to_str_6 = U64_to_str(mag);
        Array__Str_set(_va_Array_0, hoisted__U32_5, hoisted__Str_I64_to_str_6, &_va_Array_0_ek);
        Str *hoisted__Str_I64_to_str_7 = format(_va_Array_0);
        return hoisted__Str_I64_to_str_7;
    }
    U64 hoisted__U64_10 = (U64)(val);
    Str *hoisted__Str_I64_to_str_11 = U64_to_str(hoisted__U64_10);
    return hoisted__Str_I64_to_str_11;
}

void I64_delete(I64 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

__attribute__((noreturn)) void panic(Array__Str * parts, Str * loc) {
    U32 hoisted__U32_0 = 3;
    Array__Str *_va_Array_0 = Array__Str_new(hoisted__U32_0);
    I64 _va_Array_0_ek = 0;
    U32 hoisted__U32_1 = 0;
    Str *hoisted__Str_panic_2 = Str_clone(loc);
    Array__Str_set(_va_Array_0, hoisted__U32_1, hoisted__Str_panic_2, &_va_Array_0_ek);
    U32 hoisted__U32_3 = 1;
    static Str hoisted__Str_panic_4 = (Str){.c_str = (void *)": panic: ", .count = 9ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_0, hoisted__U32_3, &hoisted__Str_panic_4, &_va_Array_0_ek);
    Array__Str *hoisted__Array__Str_5 = Array__Str_clone(parts);
    U32 hoisted__U32_6 = 2;
    Str *hoisted__Str_panic_7 = format(hoisted__Array__Str_5);
    Array__Str_set(_va_Array_0, hoisted__U32_6, hoisted__Str_panic_7, &_va_Array_0_ek);
    println(_va_Array_0);
    Array__Str_delete(parts, 1);
    I64 hoisted__I64_8 = 1;
    exit(hoisted__I64_8);
}

void assert(Bool cond, Str * loc) {
    Bool hoisted__Bool_3 = ((Bool)(!(cond)));
    if (hoisted__Bool_3) {
        U32 hoisted__U32_0 = 1;
        Array__Str *_va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        static Str hoisted__Str_assert_2 = (Str){.c_str = (void *)"assert failed", .count = 13ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_0, hoisted__U32_1, &hoisted__Str_assert_2, &_va_Array_0_ek);
        panic(_va_Array_0, loc);
    }
}

void expect(Bool cond, Array__Str * parts, Str * loc) {
    Bool hoisted__Bool_6 = ((Bool)(!(cond)));
    if (hoisted__Bool_6) {
        U32 hoisted__U32_0 = 2;
        Array__Str *_va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        static Str hoisted__Str_expect_2 = (Str){.c_str = (void *)"assert failed: ", .count = 15ULL, .cap = TIL_CAP_LIT};
        Array__Str_set(_va_Array_0, hoisted__U32_1, &hoisted__Str_expect_2, &_va_Array_0_ek);
        Array__Str *hoisted__Array__Str_3 = Array__Str_clone(parts);
        U32 hoisted__U32_4 = 1;
        Str *hoisted__Str_expect_5 = format(hoisted__Array__Str_3);
        Array__Str_set(_va_Array_0, hoisted__U32_4, hoisted__Str_expect_5, &_va_Array_0_ek);
        panic(_va_Array_0, loc);
    }
    Array__Str_delete(parts, 1);
}

void println(Array__Str * parts) {
    {
        Array__Str *_fc_Array__Str_0 = parts;
        U32 _fi_USize_0 = 0;
        while (1) {
            USize hoisted__U32_2 = (_fc_Array__Str_0->cap);
            Bool _wcond_Bool_1 = ((Bool)(_fi_USize_0 < hoisted__U32_2));
            if (_wcond_Bool_1) {
            } else {
                break;
            }
            Str *s = ((Str *)((void *)((U8 *)(_fc_Array__Str_0->data) + (((U32)(_fi_USize_0 * 16))))));
            U32 hoisted__U32_3 = 1;
            U32 hoisted__U32_4 = ((U32)(_fi_USize_0 + hoisted__U32_3));
            _fi_USize_0 = hoisted__U32_4;
            print_single(s);
        }
    }
    Array__Str_delete(parts, 1);
    print_flush();
}

void test_simple_add(void) {
    I64 result = 3;
    I64 hoisted__I64_2 = 3;
    assert_eq__I64(result, hoisted__I64_2, &hoisted__Str_test_simple_add_3);
    Str_delete(&hoisted__Str_test_simple_add_3, 0);
}

void test_nested_arithmetic(void) {
    I64 result = 15;
    I64 hoisted__I64_6 = 15;
    assert_eq__I64(result, hoisted__I64_6, &hoisted__Str_test_nested_arithmetic_7);
    Str_delete(&hoisted__Str_test_nested_arithmetic_7, 0);
}

void test_deeply_nested(void) {
    I64 result = 26;
    I64 hoisted__I64_6 = 26;
    assert_eq__I64(result, hoisted__I64_6, &hoisted__Str_test_deeply_nested_7);
    Str_delete(&hoisted__Str_test_deeply_nested_7, 0);
}

void test_string_concat(void) {
    static Str result = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&result, &_til_str_lits.h3fd43551c8c1, &hoisted__Str_test_string_concat_3);
    Str_delete(&_til_str_lits.h3fd43551c8c1, 0);
    Str_delete(&hoisted__Str_test_string_concat_3, 0);
    Str_delete(&result, 0);
}

void test_variadic_fold(void) {
    static Str r = (Str){.c_str = (void *)"hello world", .count = 11ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r, &_til_str_lits.h3fd43551c8c1, &hoisted__Str_test_variadic_fold_3);
    Str_delete(&_til_str_lits.h3fd43551c8c1, 0);
    Str_delete(&hoisted__Str_test_variadic_fold_3, 0);
    Str_delete(&r, 0);
    static Str r2 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_test_variadic_fold_7 = (Str){.c_str = (void *)"a-b-c", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&r2, &hoisted__Str_test_variadic_fold_7, &hoisted__Str_test_variadic_fold_8);
    Str_delete(&hoisted__Str_test_variadic_fold_7, 0);
    Str_delete(&hoisted__Str_test_variadic_fold_8, 0);
    Str_delete(&r2, 0);
}

void test_variadic_direct_fold(void) {
    static Str d = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_test_variadic_direct_fold_11 = (Str){.c_str = (void *)"x-y-z", .count = 5ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d, &hoisted__Str_test_variadic_direct_fold_11, &hoisted__Str_test_variadic_direct_fold_12);
    Str_delete(&d, 0);
    Str_delete(&hoisted__Str_test_variadic_direct_fold_11, 0);
    Str_delete(&hoisted__Str_test_variadic_direct_fold_12, 0);
    static Str d2 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    static Str hoisted__Str_test_variadic_direct_fold_20 = (Str){.c_str = (void *)"abc", .count = 3ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&d2, &hoisted__Str_test_variadic_direct_fold_20, &hoisted__Str_test_variadic_direct_fold_21);
    Str_delete(&d2, 0);
    Str_delete(&hoisted__Str_test_variadic_direct_fold_20, 0);
    Str_delete(&hoisted__Str_test_variadic_direct_fold_21, 0);
    I64 d3 = 106;
    I64 hoisted__I64_30 = 106;
    assert_eq__I64(d3, hoisted__I64_30, &hoisted__Str_test_variadic_direct_fold_31);
    Str_delete(&hoisted__Str_test_variadic_direct_fold_31, 0);
}

void test_lolalalo(void) {
    static Str lola_rec = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lola_it = (Str){.c_str = (void *)"lolololo\nlololola\nlololalo\nlololala\nlololeilo\nlololeila\nlolalolo\nlolalola\nlolalalo\nlolalala\nlolaleilo\nlolaleila\nlalololo\nlalolola\nlalolalo\nlalolala\nlaloleilo\nlaloleila\nlalalolo\nlalalola\nlalalalo\nlalalala\nlalaleilo\nlalaleila\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_rec = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    static Str lalo_it = (Str){.c_str = (void *)"lalalala\nlalalalo\nlalalola\nlalalolo\nlalaleila\nlalaleilo\nlalolala\nlalolalo\nlalolola\nlalololo\nlaloleila\nlaloleilo\nlolalala\nlolalalo\nlolalola\nlolalolo\nlolaleila\nlolaleilo\nlololala\nlololalo\nlololola\nlolololo\nlololeila\nlololeilo\n", .count = 224ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(&lola_rec, &lola_it, &hoisted__Str_test_lolalalo_8);
    Str_delete(&hoisted__Str_test_lolalalo_8, 0);
    Str_delete(&lola_it, 0);
    Str_delete(&lola_rec, 0);
    assert_eq__Str(&lalo_rec, &lalo_it, &hoisted__Str_test_lolalalo_9);
    Str_delete(&hoisted__Str_test_lolalalo_9, 0);
    Str_delete(&lalo_it, 0);
    Str_delete(&lalo_rec, 0);
}

void test_fold_variable(void) {
    I64 result = 8;
    I64 hoisted__I64_1 = 8;
    assert_eq__I64(result, hoisted__I64_1, &hoisted__Str_test_fold_variable_2);
    Str_delete(&hoisted__Str_test_fold_variable_2, 0);
}

void test_loc_folded(void) {
    Bool hoisted__Bool_2 = 1;
    assert(hoisted__Bool_2, &hoisted__Str_test_loc_folded_3);
    Str_delete(&hoisted__Str_test_loc_folded_3, 0);
    Bool hoisted__Bool_6 = 1;
    assert(hoisted__Bool_6, &hoisted__Str_test_loc_folded_7);
    Str_delete(&hoisted__Str_test_loc_folded_7, 0);
}

void test_fold_f32(void) {
    assert_eq__Str(&_til_str_lits.h00017c7b7650, &_til_str_lits.h00017c7b7650, &hoisted__Str_test_fold_f32_4);
    Str_delete(&_til_str_lits.h00017c7b7650, 0);
    Str_delete(&_til_str_lits.h00017c7b7650, 0);
    Str_delete(&hoisted__Str_test_fold_f32_4, 0);
    assert_eq__Str(&_til_str_lits.h00000b8791fb, &_til_str_lits.h00000b8791fb, &hoisted__Str_test_fold_f32_9);
    Str_delete(&_til_str_lits.h00000b8791fb, 0);
    Str_delete(&_til_str_lits.h00000b8791fb, 0);
    Str_delete(&hoisted__Str_test_fold_f32_9, 0);
}

void CfVec2_delete(CfVec2 * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void test_struct_fold_simple(void) {
    CfVec2 v = (CfVec2){.x = 42, .y = 99};
    I64 hoisted__I64_0 = 42;
    assert_eq__I64(v.x, hoisted__I64_0, &hoisted__Str_test_struct_fold_simple_1);
    Str_delete(&hoisted__Str_test_struct_fold_simple_1, 0);
    I64 hoisted__I64_2 = 99;
    assert_eq__I64(v.y, hoisted__I64_2, &hoisted__Str_test_struct_fold_simple_3);
    Str_delete(&hoisted__Str_test_struct_fold_simple_3, 0);
    CfVec2_delete(&v, 0);
}

void test_struct_fold_values(void) {
    CfVec2 p = (CfVec2){.x = 10, .y = 20};
    I64 hoisted__I64_2 = 10;
    assert_eq__I64(p.x, hoisted__I64_2, &hoisted__Str_test_struct_fold_values_3);
    Str_delete(&hoisted__Str_test_struct_fold_values_3, 0);
    I64 hoisted__I64_4 = 20;
    assert_eq__I64(p.y, hoisted__I64_4, &hoisted__Str_test_struct_fold_values_5);
    Str_delete(&hoisted__Str_test_struct_fold_values_5, 0);
    CfVec2_delete(&p, 0);
}

void CfRect_delete(CfRect * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void test_struct_fold_nested(void) {
    CfRect r = (CfRect){.top_left = (CfVec2){.x = 5, .y = 10}, .bottom_right = (CfVec2){.x = 100, .y = 200}};
    I64 hoisted__I64_0 = 5;
    assert_eq__I64(r.top_left.x, hoisted__I64_0, &hoisted__Str_test_struct_fold_nested_1);
    Str_delete(&hoisted__Str_test_struct_fold_nested_1, 0);
    I64 hoisted__I64_2 = 10;
    assert_eq__I64(r.top_left.y, hoisted__I64_2, &hoisted__Str_test_struct_fold_nested_3);
    Str_delete(&hoisted__Str_test_struct_fold_nested_3, 0);
    I64 hoisted__I64_4 = 100;
    assert_eq__I64(r.bottom_right.x, hoisted__I64_4, &hoisted__Str_test_struct_fold_nested_5);
    Str_delete(&hoisted__Str_test_struct_fold_nested_5, 0);
    I64 hoisted__I64_6 = 200;
    assert_eq__I64(r.bottom_right.y, hoisted__I64_6, &hoisted__Str_test_struct_fold_nested_7);
    Str_delete(&hoisted__Str_test_struct_fold_nested_7, 0);
    CfRect_delete(&r, 0);
}

void CfVec3f_delete(CfVec3f * self, Bool call_free) {
    if (call_free) {
        free(self);
    }
}

void test_struct_fold_f32(void) {
    CfVec3f v = (CfVec3f){.x = 3, .y = 4, .z = 5};
    Str *hoisted__Str_test_struct_fold_f32_3 = F32_to_str(v.x);
    static Str hoisted__Str_test_struct_fold_f32_4 = (Str){.c_str = (void *)"3", .count = 1ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(hoisted__Str_test_struct_fold_f32_3, &hoisted__Str_test_struct_fold_f32_4, &hoisted__Str_test_struct_fold_f32_5);
    Str_delete(hoisted__Str_test_struct_fold_f32_3, 1);
    Str_delete(&hoisted__Str_test_struct_fold_f32_4, 0);
    Str_delete(&hoisted__Str_test_struct_fold_f32_5, 0);
    Str *hoisted__Str_test_struct_fold_f32_6 = F32_to_str(v.y);
    static Str hoisted__Str_test_struct_fold_f32_7 = (Str){.c_str = (void *)"4", .count = 1ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(hoisted__Str_test_struct_fold_f32_6, &hoisted__Str_test_struct_fold_f32_7, &hoisted__Str_test_struct_fold_f32_8);
    Str_delete(hoisted__Str_test_struct_fold_f32_6, 1);
    Str_delete(&hoisted__Str_test_struct_fold_f32_7, 0);
    Str_delete(&hoisted__Str_test_struct_fold_f32_8, 0);
    Str *hoisted__Str_test_struct_fold_f32_9 = F32_to_str(v.z);
    static Str hoisted__Str_test_struct_fold_f32_10 = (Str){.c_str = (void *)"5", .count = 1ULL, .cap = TIL_CAP_LIT};
    assert_eq__Str(hoisted__Str_test_struct_fold_f32_9, &hoisted__Str_test_struct_fold_f32_10, &hoisted__Str_test_struct_fold_f32_11);
    Str_delete(&hoisted__Str_test_struct_fold_f32_10, 0);
    Str_delete(&hoisted__Str_test_struct_fold_f32_11, 0);
    Str_delete(hoisted__Str_test_struct_fold_f32_9, 1);
    CfVec3f_delete(&v, 0);
}

Bool Color_eq(Color * self, Color * other) {
    Bool hoisted__Bool_0 = ((Bool)((((Color *)(self))->tag) == (((Color *)(other))->tag)));
    return hoisted__Bool_0;
}


void test_enum_fold(void) {
    Color c = (Color){.tag = Color_TAG_Red};
    Bool hoisted__Bool_0 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    assert(hoisted__Bool_0, &hoisted__Str_test_enum_fold_1);
    Str_delete(&hoisted__Str_test_enum_fold_1, 0);
    Bool hoisted__Bool_2 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    Bool hoisted__Bool_3 = ((Bool)(!(hoisted__Bool_2)));
    assert(hoisted__Bool_3, &hoisted__Str_test_enum_fold_4);
    Str_delete(&hoisted__Str_test_enum_fold_4, 0);
}

Token *Token_Num(I64 * val) {
    Token *r = malloc(sizeof(Token));
    r->tag = Token_TAG_Num;
    r->data.Num = *val;
    return r;
}
void Token_delete(Token * self, Bool call_free) {
    Bool hoisted__Bool_2 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    if (hoisted__Bool_2) {
        I64 *hoisted__I64_0 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        I64_delete(hoisted__I64_0, 0);
    }
    Bool hoisted__Bool_3 = ((Bool)((((Token *)(self))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Name}))->tag)));
    if (hoisted__Bool_3) {
        Str *hoisted__Str_Token_delete_1 = ((void *)((U8 *)(self) + offsetof(Token, data)));
        Str_delete(hoisted__Str_Token_delete_1, 0);
    }
    if (call_free) {
        free(self);
    }
}


void test_enum_payload_fold(void) {
    Token *t = Token_Num(&(I64){42});
    Bool hoisted__Bool_1 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_1, &hoisted__Str_test_enum_payload_fold_2);
    Str_delete(&hoisted__Str_test_enum_payload_fold_2, 0);
    Bool hoisted__Bool_3 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_4 = ((Bool)(!(hoisted__Bool_3)));
    assert(hoisted__Bool_4, &hoisted__Str_test_enum_payload_fold_5);
    Str_delete(&hoisted__Str_test_enum_payload_fold_5, 0);
    Token_delete(t, 1);
}

void test_enum_return_fold(void) {
    Color c = (Color){.tag = Color_TAG_Green};
    Bool hoisted__Bool_0 = Color_eq(&c, &(Color){.tag = Color_TAG_Green});
    assert(hoisted__Bool_0, &hoisted__Str_test_enum_return_fold_1);
    Str_delete(&hoisted__Str_test_enum_return_fold_1, 0);
    Bool hoisted__Bool_2 = Color_eq(&c, &(Color){.tag = Color_TAG_Red});
    Bool hoisted__Bool_3 = ((Bool)(!(hoisted__Bool_2)));
    assert(hoisted__Bool_3, &hoisted__Str_test_enum_return_fold_4);
    Str_delete(&hoisted__Str_test_enum_return_fold_4, 0);
}

void test_enum_payload_return_fold(void) {
    Token *t = Token_Num(&(I64){7});
    Bool hoisted__Bool_1 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Num}))->tag)));
    assert(hoisted__Bool_1, &hoisted__Str_test_enum_payload_return_fold_2);
    Str_delete(&hoisted__Str_test_enum_payload_return_fold_2, 0);
    Bool hoisted__Bool_3 = ((Bool)((((Token *)(t))->tag) == (((Token *)(&(Token){.tag = Token_TAG_Eof}))->tag)));
    Bool hoisted__Bool_4 = ((Bool)(!(hoisted__Bool_3)));
    assert(hoisted__Bool_4, &hoisted__Str_test_enum_payload_return_fold_5);
    Str_delete(&hoisted__Str_test_enum_payload_return_fold_5, 0);
    Token_delete(t, 1);
}

void test_const_and_or_fold(void) {
    U32 hoisted__U32_6 = 1;
    Array__Str *_va_Array_0 = Array__Str_new(hoisted__U32_6);
    I64 _va_Array_0_ek = 0;
    U32 hoisted__U32_7 = 0;
    static Str hoisted__Str_test_const_and_or_fold_8 = (Str){.c_str = (void *)"and(T,T)", .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_0, hoisted__U32_7, &hoisted__Str_test_const_and_or_fold_8, &_va_Array_0_ek);
    Bool hoisted__Bool_9 = 1;
    expect(hoisted__Bool_9, _va_Array_0, &hoisted__Str_test_const_and_or_fold_10);
    Str_delete(&hoisted__Str_test_const_and_or_fold_10, 0);
    U32 hoisted__U32_11 = 1;
    Array__Str *_va_Array_1 = Array__Str_new(hoisted__U32_11);
    I64 _va_Array_1_ek = 0;
    U32 hoisted__U32_12 = 0;
    static Str hoisted__Str_test_const_and_or_fold_13 = (Str){.c_str = (void *)"and(T,F)", .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_1, hoisted__U32_12, &hoisted__Str_test_const_and_or_fold_13, &_va_Array_1_ek);
    Bool hoisted__Bool_15 = 1;
    expect(hoisted__Bool_15, _va_Array_1, &hoisted__Str_test_const_and_or_fold_16);
    Str_delete(&hoisted__Str_test_const_and_or_fold_16, 0);
    U32 hoisted__U32_17 = 1;
    Array__Str *_va_Array_2 = Array__Str_new(hoisted__U32_17);
    I64 _va_Array_2_ek = 0;
    U32 hoisted__U32_18 = 0;
    static Str hoisted__Str_test_const_and_or_fold_19 = (Str){.c_str = (void *)"and x3 T", .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_2, hoisted__U32_18, &hoisted__Str_test_const_and_or_fold_19, &_va_Array_2_ek);
    Bool hoisted__Bool_20 = 1;
    expect(hoisted__Bool_20, _va_Array_2, &hoisted__Str_test_const_and_or_fold_21);
    Str_delete(&hoisted__Str_test_const_and_or_fold_21, 0);
    U32 hoisted__U32_22 = 1;
    Array__Str *_va_Array_3 = Array__Str_new(hoisted__U32_22);
    I64 _va_Array_3_ek = 0;
    U32 hoisted__U32_23 = 0;
    static Str hoisted__Str_test_const_and_or_fold_24 = (Str){.c_str = (void *)"and x3 with F", .count = 13ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_3, hoisted__U32_23, &hoisted__Str_test_const_and_or_fold_24, &_va_Array_3_ek);
    Bool hoisted__Bool_26 = 1;
    expect(hoisted__Bool_26, _va_Array_3, &hoisted__Str_test_const_and_or_fold_27);
    Str_delete(&hoisted__Str_test_const_and_or_fold_27, 0);
    U32 hoisted__U32_28 = 1;
    Array__Str *_va_Array_4 = Array__Str_new(hoisted__U32_28);
    I64 _va_Array_4_ek = 0;
    U32 hoisted__U32_29 = 0;
    static Str hoisted__Str_test_const_and_or_fold_30 = (Str){.c_str = (void *)"or(F,T)", .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_4, hoisted__U32_29, &hoisted__Str_test_const_and_or_fold_30, &_va_Array_4_ek);
    Bool hoisted__Bool_31 = 1;
    expect(hoisted__Bool_31, _va_Array_4, &hoisted__Str_test_const_and_or_fold_32);
    Str_delete(&hoisted__Str_test_const_and_or_fold_32, 0);
    U32 hoisted__U32_33 = 1;
    Array__Str *_va_Array_5 = Array__Str_new(hoisted__U32_33);
    I64 _va_Array_5_ek = 0;
    U32 hoisted__U32_34 = 0;
    static Str hoisted__Str_test_const_and_or_fold_35 = (Str){.c_str = (void *)"or(F,F)", .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_5, hoisted__U32_34, &hoisted__Str_test_const_and_or_fold_35, &_va_Array_5_ek);
    Bool hoisted__Bool_37 = 1;
    expect(hoisted__Bool_37, _va_Array_5, &hoisted__Str_test_const_and_or_fold_38);
    Str_delete(&hoisted__Str_test_const_and_or_fold_38, 0);
    U32 hoisted__U32_39 = 1;
    Array__Str *_va_Array_6 = Array__Str_new(hoisted__U32_39);
    I64 _va_Array_6_ek = 0;
    U32 hoisted__U32_40 = 0;
    static Str hoisted__Str_test_const_and_or_fold_41 = (Str){.c_str = (void *)"or x3 with T", .count = 12ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_6, hoisted__U32_40, &hoisted__Str_test_const_and_or_fold_41, &_va_Array_6_ek);
    Bool hoisted__Bool_42 = 1;
    expect(hoisted__Bool_42, _va_Array_6, &hoisted__Str_test_const_and_or_fold_43);
    Str_delete(&hoisted__Str_test_const_and_or_fold_43, 0);
    U32 hoisted__U32_44 = 1;
    Array__Str *_va_Array_7 = Array__Str_new(hoisted__U32_44);
    I64 _va_Array_7_ek = 0;
    U32 hoisted__U32_45 = 0;
    static Str hoisted__Str_test_const_and_or_fold_46 = (Str){.c_str = (void *)"or x3 F", .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_7, hoisted__U32_45, &hoisted__Str_test_const_and_or_fold_46, &_va_Array_7_ek);
    Bool hoisted__Bool_48 = 1;
    expect(hoisted__Bool_48, _va_Array_7, &hoisted__Str_test_const_and_or_fold_49);
    Str_delete(&hoisted__Str_test_const_and_or_fold_49, 0);
    U32 hoisted__U32_50 = 1;
    Array__Str *_va_Array_8 = Array__Str_new(hoisted__U32_50);
    I64 _va_Array_8_ek = 0;
    U32 hoisted__U32_51 = 0;
    static Str hoisted__Str_test_const_and_or_fold_52 = (Str){.c_str = (void *)"T.and(T)", .count = 8ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_8, hoisted__U32_51, &hoisted__Str_test_const_and_or_fold_52, &_va_Array_8_ek);
    Bool hoisted__Bool_53 = 1;
    expect(hoisted__Bool_53, _va_Array_8, &hoisted__Str_test_const_and_or_fold_54);
    Str_delete(&hoisted__Str_test_const_and_or_fold_54, 0);
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
    Array__Str *_va_Array_9 = Array__Str_new(hoisted__U32_55);
    I64 _va_Array_9_ek = 0;
    U32 hoisted__U32_56 = 0;
    static Str hoisted__Str_test_const_and_or_fold_57 = (Str){.c_str = (void *)"F.or(T)", .count = 7ULL, .cap = TIL_CAP_LIT};
    Array__Str_set(_va_Array_9, hoisted__U32_56, &hoisted__Str_test_const_and_or_fold_57, &_va_Array_9_ek);
    expect(_m_Bool_0, _va_Array_9, &hoisted__Str_test_const_and_or_fold_58);
    Str_delete(&hoisted__Str_test_const_and_or_fold_58, 0);
}

void test_mixed_fold(void) {
    I64 result = 10;
    I64 hoisted__I64_3 = 10;
    assert_eq__I64(result, hoisted__I64_3, &hoisted__Str_test_mixed_fold_4);
    Str_delete(&hoisted__Str_test_mixed_fold_4, 0);
}

void test_fold_reads_global_const(void) {
    I64 hoisted__I64_1 = 2;
    I64 hoisted__I64_2 = 2;
    assert_eq__I64(hoisted__I64_1, hoisted__I64_2, &hoisted__Str_test_fold_reads_global_const_3);
    Str_delete(&hoisted__Str_test_fold_reads_global_const_3, 0);
}

void assert_eq__I64(I64 a, I64 b, Str * loc) {
    Bool hoisted__Bool_11 = ((Bool)(a != b));
    if (hoisted__Bool_11) {
        U32 hoisted__U32_0 = 5;
        Array__Str *_va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        Array__Str_set(_va_Array_0, hoisted__U32_1, &_til_str_lits.h44abcb58cde4, &_va_Array_0_ek);
        U32 hoisted__U32_3 = 1;
        Str *hoisted__Str_assert_eq__I64_4 = I64_to_str(a);
        Array__Str_set(_va_Array_0, hoisted__U32_3, hoisted__Str_assert_eq__I64_4, &_va_Array_0_ek);
        U32 hoisted__U32_5 = 2;
        Array__Str_set(_va_Array_0, hoisted__U32_5, &_til_str_lits.h15a1180c089b, &_va_Array_0_ek);
        U32 hoisted__U32_7 = 3;
        Str *hoisted__Str_assert_eq__I64_8 = I64_to_str(b);
        Array__Str_set(_va_Array_0, hoisted__U32_7, hoisted__Str_assert_eq__I64_8, &_va_Array_0_ek);
        U32 hoisted__U32_9 = 4;
        Array__Str_set(_va_Array_0, hoisted__U32_9, &_til_str_lits.h00000002b5cc, &_va_Array_0_ek);
        panic(_va_Array_0, loc);
    }
}

void assert_eq__Str(Str * a, Str * b, Str * loc) {
    Bool hoisted__Bool_11 = Str_neq(a, b);
    if (hoisted__Bool_11) {
        U32 hoisted__U32_0 = 5;
        Array__Str *_va_Array_0 = Array__Str_new(hoisted__U32_0);
        I64 _va_Array_0_ek = 0;
        U32 hoisted__U32_1 = 0;
        Array__Str_set(_va_Array_0, hoisted__U32_1, &_til_str_lits.h44abcb58cde4, &_va_Array_0_ek);
        U32 hoisted__U32_3 = 1;
        Str *hoisted__Str_assert_eq__Str_4 = Str_to_str(a);
        Array__Str_set(_va_Array_0, hoisted__U32_3, hoisted__Str_assert_eq__Str_4, &_va_Array_0_ek);
        U32 hoisted__U32_5 = 2;
        Array__Str_set(_va_Array_0, hoisted__U32_5, &_til_str_lits.h15a1180c089b, &_va_Array_0_ek);
        U32 hoisted__U32_7 = 3;
        Str *hoisted__Str_assert_eq__Str_8 = Str_to_str(b);
        Array__Str_set(_va_Array_0, hoisted__U32_7, hoisted__Str_assert_eq__Str_8, &_va_Array_0_ek);
        U32 hoisted__U32_9 = 4;
        Array__Str_set(_va_Array_0, hoisted__U32_9, &_til_str_lits.h00000002b5cc, &_va_Array_0_ek);
        panic(_va_Array_0, loc);
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
    test_mixed_fold();
    fprintf(stderr, "  pass: %s\n", "test_mixed_fold");
    test_fold_reads_global_const();
    fprintf(stderr, "  pass: %s\n", "test_fold_reads_global_const");
    fprintf(stderr, "21/21 tests passed\n");
    return 0;
}
